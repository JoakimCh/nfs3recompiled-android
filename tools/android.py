#!/usr/bin/env python3
"""Shared ARMv7 Android commands for the workspace and GitHub Actions."""
import argparse
import base64
from contextlib import contextmanager
import hashlib
import json
import os
from pathlib import Path
import subprocess
import sys
import tempfile
import xml.etree.ElementTree as ET

import setup_android as setup
from release.sign_android import CERTIFICATE_SHA256, KEY_ALIAS

ROOT = setup.ROOT
APK = ROOT / 'android/app/build/outputs/apk/release/app-release-unsigned.apk'


def signing_files(args, parser):
    if not args.keystore or not args.password_file:
        parser.error('Signing needs --keystore and --password-file. Use GitHub Actions with its configured secrets, or explicitly choose --unsigned for an intermediate APK.')
    for path in (args.keystore, args.password_file):
        if not path.is_file(): parser.error('Signing file not found: ' + str(path))



@contextmanager
def signing_environment(args, parser):
    if not args.github_secrets:
        yield
        return
    if args.mode not in ('apk', 'apk-fast', 'sign', 'verify-signing') or args.unsigned:
        parser.error('--github-secrets is only for signed APK/signing commands')
    if args.keystore or args.password_file:
        parser.error('Choose GitHub secrets or signing file arguments, not both')
    encoded = os.environ.pop('ANDROID_KEYSTORE_BASE64', '')
    password = os.environ.pop('ANDROID_KEYSTORE_PASSWORD', '')
    if not encoded or not password:
        parser.error('Both Android signing repository secrets must be configured')
    temporary = os.environ.get('RUNNER_TEMP')
    if not temporary:
        parser.error('--github-secrets needs RUNNER_TEMP outside the build cache; use file arguments locally')
    temporary = Path(temporary).resolve()
    if temporary.is_relative_to(ROOT) or temporary.is_relative_to(args.cache_dir.expanduser().resolve()):
        parser.error('Signing temporary files must be outside the repository and build cache')
    try:
        key = base64.b64decode(''.join(encoded.split()), validate=True)
    except ValueError:
        raise RuntimeError('ANDROID_KEYSTORE_BASE64 is not valid base64') from None
    with tempfile.TemporaryDirectory(prefix='nfs3-signing-', dir=temporary) as directory:
        private = Path(directory)
        private.chmod(0o700)
        args.keystore = private / 'release.p12'
        args.password_file = private / 'password.txt'
        for path, data in ((args.keystore, key), (args.password_file, password.encode())):
            path.touch(mode=0o600)
            path.write_bytes(data)
        yield


def verify_signing(args, env):
    # Export the public certificate only. Passwords are read by keytool from a file.
    try:
        certificate = subprocess.check_output([
            str(Path(env['JAVA_HOME']) / 'bin/keytool'), '-exportcert', '-alias', KEY_ALIAS,
            '-keystore', str(args.keystore.resolve()), '-storepass:file', str(args.password_file.resolve())],
            env=env, stderr=subprocess.PIPE)
    except subprocess.CalledProcessError:
        raise RuntimeError('Keystore/password validation failed. Check the original release credentials.') from None
    if hashlib.sha256(certificate).hexdigest() != CERTIFICATE_SHA256:
        raise RuntimeError('The keystore certificate does not match the installed ARMv7 releases.')
    print('Original signing identity verified: ' + CERTIFICATE_SHA256, flush=True)


def gradle(tasks, args, env, flags, launcher_only=False):
    command = ['bash', str(ROOT / 'android/gradlew'), *tasks, '-Parmv7Tv', '-PprofileNative',
               '-PnativeJobs=' + str(args.jobs), '--no-daemon', '--max-workers=' + str(args.jobs),
               '--build-cache', '--console=plain', *flags]
    if launcher_only: command.append('-PlauncherTestsOnly')
    subprocess.run(command, cwd=ROOT / 'android', env=env, check=True)


def tests(args, env, flags):
    subprocess.run([sys.executable, '-m', 'unittest', 'discover', '-s', str(ROOT / 'tools/tests')],
                   cwd=ROOT, env=env, check=True)
    gradle([':app:testReleaseUnitTest'], args, env, flags, launcher_only=True)
    reports = list((ROOT / 'android/app/build/test-results/testReleaseUnitTest').glob('TEST-*.xml'))
    if not reports: raise RuntimeError('No launcher JUnit reports were produced.')
    roots = [ET.parse(path).getroot() for path in reports]
    result = {key: sum(int(root.get(key, 0)) for root in roots)
              for key in ('tests', 'failures', 'errors', 'skipped')}
    if not result['tests'] or result['failures'] or result['errors']:
        raise RuntimeError('Launcher test reports are not successful: ' + json.dumps(result))
    print('Launcher tests: ' + json.dumps(result), flush=True)
    return result


def report(args, results):
    args.output_dir.mkdir(parents=True, exist_ok=True)
    data = {'mode': args.mode, 'source_commit': setup.output(['git', '-C', ROOT, 'rev-parse', 'HEAD'], os.environ.copy()),
            'source_dirty': bool(setup.output(['git', '-C', ROOT, 'status', '--porcelain'], os.environ.copy())),
            'tests': results, 'native_compiled': args.mode in ('check', 'apk', 'apk-fast'),
            'toolchain': json.loads(setup.CONFIG.read_text())}
    if args.mode in ('apk', 'apk-fast'):
        data.update(apk=str(APK.relative_to(ROOT)), unsigned=True,
                    apk_sha256=setup.digest(APK),
                    resource_check=json.loads((args.output_dir / 'apk-resource-check.json').read_text()))
    (args.output_dir / 'validation.json').write_text(json.dumps(data, indent=2) + '\n')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('mode', choices=('setup', 'tests', 'check', 'apk', 'apk-fast', 'sign', 'verify-signing'))
    setup.arguments(parser)
    parser.add_argument('--tests-only', action='store_true', help='Prepare only launcher tooling in setup mode')
    parser.add_argument('--unsigned', action='store_true', help='Explicitly leave an intermediate APK unsigned')
    parser.add_argument('--github-secrets', action='store_true', help='Read CI signing secrets into private temporary files and remove them afterwards')
    parser.add_argument('--keystore', type=Path)
    parser.add_argument('--password-file', type=Path)
    parser.add_argument('--apk', type=Path, default=APK)
    parser.add_argument('--output-dir', type=Path, default=ROOT / 'out')
    args = parser.parse_args()
    if args.jobs < 1: parser.error('--jobs must be positive')
    if args.tests_only and args.mode != 'setup': parser.error('--tests-only belongs to setup mode')
    if args.unsigned and args.mode not in ('apk', 'apk-fast'): parser.error('--unsigned belongs to apk/apk-fast modes')
    if args.mode != 'sign' and args.apk != APK: parser.error('--apk belongs to sign mode')
    if args.mode == 'sign' and not args.apk.is_file(): parser.error('Prepared APK not found: ' + str(args.apk))
    if args.unsigned and (args.keystore or args.password_file):
        parser.error('Choose signing files or --unsigned, not both')
    try:
        with signing_environment(args, parser):
            if args.mode in ('sign', 'verify-signing') or (args.mode in ('apk', 'apk-fast') and not args.unsigned):
                signing_files(args, parser)  # Fail before downloading a large toolchain.
            if args.mode in ('sign', 'verify-signing') or (args.mode in ('apk', 'apk-fast') and not args.unsigned):
                env, _, _ = setup.runtime(args.cache_dir, args.jobs)
                verify_signing(args, env)
            if args.mode == 'verify-signing': return
            native = args.mode not in ('tests',) and not (args.mode == 'setup' and args.tests_only)
            env, flags = setup.prepare(args.cache_dir, native, args.accept_sdk_licenses, args.jobs, args.update_sdl)
            if args.mode == 'setup': return
            if args.mode != 'sign':
                results = None
                if args.mode == 'apk-fast':
                    print('Fast APK build: tooling and launcher tests skipped.', flush=True)
                else:
                    results = tests(args, env, flags)
                if args.mode == 'check':
                    gradle([':app:buildCMakeRelWithDebInfo[armeabi-v7a]'], args, env, flags)
                elif args.mode in ('apk', 'apk-fast'):
                    gradle([':app:assembleRelease'], args, env, flags)
                    sdk = Path(env['ANDROID_HOME'])
                    config = json.loads(setup.CONFIG.read_text())
                    subprocess.run([sys.executable, str(ROOT / 'tools/game_checks/gamepad/check_apk_resources.py'),
                                    str(APK), str(sdk / 'build-tools' / config['buildTools']),
                                    str(ROOT / 'android/app/build/intermediates/compile_symbol_list/release/generateReleaseRFile/R.txt'),
                                    str(args.output_dir / 'apk-resource-check.json')], env=env, check=True)
                report(args, results)
            if args.mode == 'sign' or (args.mode in ('apk', 'apk-fast') and not args.unsigned):
                subprocess.run([sys.executable, str(ROOT / 'tools/release/sign_android.py'),
                                '--apk', str(args.apk.resolve()), '--sdk', env['ANDROID_HOME'],
                                '--keystore', str(args.keystore.resolve()), '--password-file', str(args.password_file.resolve()),
                                '--output-dir', str(args.output_dir.resolve())], cwd=ROOT, env=env, check=True)
            elif args.mode in ('apk', 'apk-fast'):
                print('Unsigned intermediate APK: ' + str(APK), flush=True)
    except (OSError, RuntimeError, ValueError, subprocess.CalledProcessError) as error:
        raise SystemExit(str(error))


if __name__ == '__main__':
    main()

