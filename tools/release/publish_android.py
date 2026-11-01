#!/usr/bin/env python3
"""Publish an existing verified Actions APK; never rebuild or load signing keys."""
import hashlib
import io
import json
import os
from pathlib import Path
import re
import subprocess
import tempfile
from urllib.parse import urlencode
import zipfile

if __package__:
    from .sign_android import CERTIFICATE_SHA256
else:
    from sign_android import CERTIFICATE_SHA256


def require(condition, message):
    if not condition:
        raise RuntimeError(message)


def gh(*args):
    return subprocess.check_output(['gh', *map(str, args)])


def api(path):
    return json.loads(gh('api', path))


def pages(path, key):
    separator = '&' if '?' in path else '?'
    page = 1
    while True:
        items = api(f'{path}{separator}per_page=100&page={page}')[key]
        yield from items
        if len(items) < 100:
            return
        page += 1


def signed_job(repo, run_id):
    jobs = pages(f'repos/{repo}/actions/runs/{run_id}/jobs', 'jobs')
    return any(job['conclusion'] == 'success' and any(
        step['name'] == 'Sign and verify APK' and step['conclusion'] == 'success'
        for step in job.get('steps', [])) for job in jobs)


def choose_run(repo, branch, requested):
    workflow = api(f'repos/{repo}/actions/workflows/armv7-release.yml')['id']
    if requested:
        require(re.fullmatch(r'[1-9][0-9]*', requested), 'Run ID must be a positive number.')
        candidates = [api(f'repos/{repo}/actions/runs/{requested}')]
    else:
        query = urlencode({'branch': branch, 'status': 'success', 'event': 'workflow_dispatch'})
        candidates = pages(f'repos/{repo}/actions/workflows/{workflow}/runs?{query}', 'workflow_runs')
    for run in candidates:
        valid = (run['workflow_id'] == workflow and run['head_branch'] == branch
                 and run['head_repository']['full_name'] == repo
                 and run['event'] == 'workflow_dispatch' and run['status'] == 'completed'
                 and run['conclusion'] == 'success' and signed_job(repo, run['id']))
        if valid:
            return run
        require(not requested, 'Selected run is not a successful signed APK build on this branch.')
    raise RuntimeError('No successful signed APK run found on the selected branch.')


def artifact(repo, run, name):
    matches = [a for a in pages(f"repos/{repo}/actions/runs/{run['id']}/artifacts", 'artifacts')
               if a['name'] == name]
    require(len(matches) == 1, f'Missing or ambiguous {name} artifact. Build an APK first.')
    item = matches[0]
    require(not item['expired'], f'{name} has expired. Build a new APK; older runs are not substituted.')
    data = gh('api', f"repos/{repo}/actions/artifacts/{item['id']}/zip")
    digest = item.get('digest')
    require(digest and digest == 'sha256:' + hashlib.sha256(data).hexdigest(),
            f'{name} archive digest is missing or does not match GitHub metadata.')
    return zipfile.ZipFile(io.BytesIO(data))


def member(archive, name):
    matches = [entry for entry in archive.infolist() if entry.filename == name]
    require(len(matches) == 1, f'Missing or duplicate artifact member: {name}')
    require(matches[0].file_size <= 512 * 1024 * 1024, f'Artifact member too large: {name}')
    return archive.read(matches[0])


def prepare(repo, run, directory):
    with artifact(repo, run, 'armv7-apk') as archive:
        reports = [n for n in archive.namelist() if re.fullmatch(r'nfs3-[\w.\-]+-release\.json', n)]
        require(len(reports) == 1, 'Expected exactly one signed release report.')
        metadata = json.loads(member(archive, reports[0]))
        version = metadata['version']
        require(re.fullmatch(r'[\w.\-]+', version), 'Invalid version name.')
        apk_name = f'nfs3-{version}-release.apk'
        require(metadata['apk'] == apk_name, 'APK name differs from release metadata.')
        require(metadata['source_commit'] == run['head_sha'] and metadata['uncommitted_changes'] is False,
                'Release metadata must match the clean source commit of the selected run.')
        require(metadata['certificate_sha256'] == CERTIFICATE_SHA256,
                'Unexpected signing certificate in release metadata.')
        require(metadata['resource_check']['passed'] is True
                and metadata['debuggable'] is False and metadata['shell_profileable'] is True
                and metadata['zip_alignment_bytes'] == 16384,
                'Release verification metadata is not successful.')
        apk_data = member(archive, apk_name)
        require(hashlib.sha256(apk_data).hexdigest() == metadata['apk_sha256'], 'APK SHA-256 mismatch.')
        validation = json.loads(member(archive, 'validation.json'))
        tests = validation['tests']
        require(validation['source_commit'] == run['head_sha'] and validation['source_dirty'] is False
                and validation['mode'] == 'apk' and validation['native_compiled'] is True
                and tests['tests'] > 0 and all(tests[k] == 0 for k in ('failures', 'errors', 'skipped')),
                'Build validation does not show a clean APK build with successful tests.')
        (directory / apk_name).write_bytes(apk_data)
        (directory / reports[0]).write_bytes(member(archive, reports[0]))
        (directory / 'validation.json').write_bytes(member(archive, 'validation.json'))
    symbols_name = f'nfs3-{version}-symbols.zip'
    with artifact(repo, run, 'armv7-native-symbols') as archive:
        symbols_data = member(archive, symbols_name)
    with zipfile.ZipFile(io.BytesIO(symbols_data)) as symbols:
        require(json.loads(member(symbols, 'metadata/release.json')) == metadata,
                'Symbol metadata does not match the signed APK.')
        require('armeabi-v7a/libmain.so' in symbols.namelist(), 'Native symbols are missing.')
    (directory / symbols_name).write_bytes(symbols_data)
    return metadata


def unused_tag(repo, tag):
    result = subprocess.run(['gh', 'api', f'repos/{repo}/git/ref/tags/{tag}'],
                            stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    if result.returncode == 0:
        raise RuntimeError(f'Tag {tag} already exists; existing releases are never overwritten.')
    require(b'HTTP 404' in result.stderr, 'Could not check whether the release tag already exists.')


def main():
    repo = os.environ['GITHUB_REPOSITORY']
    branch = os.environ['RELEASE_BUILD_BRANCH'].strip()
    kind = os.environ['RELEASE_TYPE']
    require(branch and kind in ('prerelease', 'release'), 'Select a build branch and valid release type.')
    run = choose_run(repo, branch, os.environ.get('RELEASE_RUN_ID', '').strip())
    print(f"Selected APK run {run['id']} on {branch}, source {run['head_sha']}", flush=True)
    with tempfile.TemporaryDirectory(prefix='publish-apk-', dir=os.environ.get('RUNNER_TEMP')) as temp:
        directory = Path(temp)
        metadata = prepare(repo, run, directory)
        code = metadata['versionCode']
        require(type(code) is int and code > 0, 'Invalid APK version code.')
        tag = f"armv7-v{code}-run{run['id']}"
        unused_tag(repo, tag)
        assets = sorted(directory.iterdir())
        checksums = directory / 'SHA256SUMS.txt'
        checksums.write_text(''.join(f'{hashlib.sha256(p.read_bytes()).hexdigest()}  {p.name}\n' for p in assets))
        assets.append(checksums)
        notes = directory / 'release-notes.md'
        notes.write_text(
            f"ARMv7 TV build **{metadata['version']}**, version code {code}.\n\n"
            f"Source: `{run['head_sha']}` on `{branch}`.\n\n"
            f"Build and checks: {run['html_url']}\n\n"
            f"All {metadata_test_count(directory)} launcher tests, native build and original-certificate "
            "signing checks passed.\n\n"
            "Download the `.apk` to install. The symbols ZIP is for crash decoding; keep it "
            "with this APK. Verification JSON and SHA256SUMS.txt identify the exact files.\n\n"
            f"Native BuildID: `{metadata['native_build_id']}`.\n\n"
            "Device testing is separate from these automated checks; selecting a release "
            "type does not change the original build's device-test metadata.\n")
        # Upload everything while private, then publish. A failed upload leaves a draft.
        gh('release', 'create', tag, '--repo', repo, '--target', run['head_sha'],
           '--title', f"ARMv7 {metadata['version']} (run {run['id']})",
           '--notes-file', notes, '--draft', '--latest=false',
           *(['--prerelease'] if kind == 'prerelease' else []))
        gh('release', 'upload', tag, *assets, '--repo', repo)
        gh('release', 'edit', tag, '--repo', repo, '--draft=false',
           '--latest=true' if kind == 'release' else '--latest=false')
        url = f'https://github.com/{repo}/releases/tag/{tag}'
        print('Published: ' + url, flush=True)
        if os.environ.get('GITHUB_STEP_SUMMARY'):
            with open(os.environ['GITHUB_STEP_SUMMARY'], 'a') as summary:
                summary.write(f'Published [{tag}]({url}) from [APK run {run["id"]}]({run["html_url"]}).\n')


def metadata_test_count(directory):
    return json.loads((directory / 'validation.json').read_text())['tests']['tests']


if __name__ == '__main__':
    try:
        main()
    except (OSError, RuntimeError, ValueError, KeyError, zipfile.BadZipFile,
            subprocess.CalledProcessError) as error:
        raise SystemExit(str(error))
