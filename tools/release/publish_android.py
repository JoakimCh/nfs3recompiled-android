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
from urllib.parse import quote, urlencode
import zipfile

if __package__:
    from .sign_android import CERTIFICATE_SHA256
    from .release_identity import artifact_names, published_version, revision_of
else:
    from sign_android import CERTIFICATE_SHA256
    from release_identity import artifact_names, published_version, revision_of


def require(condition, message):
    if not condition:
        raise RuntimeError(message)


def gh(*args):
    return subprocess.check_output(['gh', *map(str, args)])


def api(path):
    return json.loads(gh('api', path))


def pages(path, key=None):
    separator = '&' if '?' in path else '?'
    page = 1
    while True:
        response = api(f'{path}{separator}per_page=100&page={page}')
        items = response[key] if key else response
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
        names = artifact_names(version)
        require(reports[0] == names['report'], 'Release report name differs from APK version.')
        apk_name = names['apk']
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
    symbols_name = names['symbols']
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


def changelog_sections(text):
    """Read versioned entries only; Unreleased and historical prose are not releases."""
    headings = list(re.finditer(r'^## (.+)$', text, re.MULTILINE))
    sections = {}
    codes = set()
    for index, heading in enumerate(headings):
        match = re.fullmatch(r'(tv\d+|\d+\.\d+\.\d+) [-–—] version (\d+)(?: .*)?', heading[1].strip())
        if not match:
            continue
        label, code_text = match.groups()
        tv = int(label[2:]) if label.startswith('tv') else revision_of(label)
        code = int(code_text)
        require(tv not in sections and code not in codes, 'Duplicate changelog version.')
        end = headings[index + 1].start() if index + 1 < len(headings) else len(text)
        body = text[heading.end():end].strip()
        # Older entries mixed personal feedback into the change descriptions.
        # Keep feedback in BUILD_STATUS.md; release notes contain changes only.
        legacy_notes = (
            r'\bJoakim (?:reported|approved)\b[^.]*\.\s*',
            r'Added translation maintenance guidance in TRANSLATIONS\.md\.\s*',
            r'The pre-existing host\s+trackVertices check discrepancy remains documented in WORKSPACE\.md\.\s*',
        )
        for pattern in legacy_notes:
            body = re.sub(pattern, '', body)
        body = re.sub(r'\n{3,}', '\n\n', body).strip()
        sections[tv] = {'code': code, 'body': body, 'label': label}
        codes.add(code)
    return sections


def previous_release(repo, run, current_tv, kind):
    candidates = []
    for release in pages(f'repos/{repo}/releases'):
        if release['draft'] or (kind == 'release' and release['prerelease']):
            continue
        # Assets identify ARMv7 releases even when legacy tags use another format.
        versions = set()
        for asset in release.get('assets', []):
            version = published_version(asset['name'])
            if version:
                versions.add(revision_of(version))
        require(len(versions) <= 1, 'A published release contains ambiguous ARMv7 versions.')
        if versions and (tv := versions.pop()) < current_tv:
            candidates.append((tv, release))
    for tv, release in sorted(candidates, key=lambda item: (item[0], item[1]['published_at']), reverse=True):
        comparison = api(f"repos/{repo}/compare/{quote(release['tag_name'], safe='')}...{run['head_sha']}")
        if comparison['status'] in ('ahead', 'identical'):
            return tv, release
    require(not candidates, 'Cannot find a previous ARMv7 release in this build source history.')
    return None


def changes_for_release(sections, current_tv, code, previous_tv=None):
    current = sections.get(current_tv)
    require(current and current['code'] == code,
            'APK version/code is missing or inconsistent in its source changelog.')
    start = previous_tv + 1 if previous_tv is not None else current_tv
    require(start <= current_tv, 'Invalid previous-release version range.')
    if previous_tv is not None:
        require(previous_tv in sections, 'Previous release is missing from the source changelog.')
    entries = []
    for tv in range(current_tv, start - 1, -1):
        entry = sections.get(tv)
        require(entry and entry['body'], f'Missing or empty changelog changes for tv{tv}.')
        entries.append(f"### {entry['label']}\n\n{entry['body']}")
    return '\n\n'.join(entries)


def release_notes(repo, run, metadata, kind, test_count):
    # Fetch the APK source, not the newer workflow checkout or branch tip.
    source = gh('api', f"repos/{repo}/contents/docs/fork/CHANGELOG.md?ref={run['head_sha']}",
                '--header', 'Accept: application/vnd.github.raw+json').decode('utf-8')
    sections = changelog_sections(source)
    tv = revision_of(metadata['version'])
    current = sections.get(tv)
    expected_label = f'tv{tv}' if '-armv7-tv' in metadata['version'] else metadata['version']
    require(current and current['label'] == expected_label, 'APK version differs from its source changelog.')
    previous = previous_release(repo, run, tv, kind)
    changes = changes_for_release(sections, tv, metadata['versionCode'], previous[0] if previous else None)
    since = f"Changes since [{sections[previous[0]]['label']}]({previous[1]['html_url']}).\n\n" if previous else ''
    notes = (
        'Download the **.apk** below to install or update the game.\n\n'
        f'## Changes\n\n{since}{changes}\n\n'
        '<details>\n<summary>Build details</summary>\n\n'
        f"- Version: `{metadata['version']}` ({metadata['versionCode']}).\n"
        f"- Source: [`{run['head_sha'][:7]}`](https://github.com/{repo}/commit/{run['head_sha']}).\n"
        f"- [Build and automated checks]({run['html_url']}): {test_count} launcher tests passed.\n"
        f"- Native BuildID: `{metadata['native_build_id']}`.\n\n"
        'The symbols ZIP and JSON files are for troubleshooting and verification. '
        'SHA256SUMS.txt contains file checksums. Only the APK is needed to play.\n\n'
        '</details>\n')
    title = f'NFS III ARMv7 TV — tv{tv}' if '-armv7-tv' in metadata['version'] else metadata['version']
    return title, notes


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
        title, body = release_notes(repo, run, metadata, kind, metadata_test_count(directory))
        notes.write_text(body)
        # Upload everything while private, then publish. A failed upload leaves a draft.
        gh('release', 'create', tag, '--repo', repo, '--target', run['head_sha'],
           '--title', title,
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
