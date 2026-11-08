#!/usr/bin/env python3
"""Sign and verify an Android fork release; passwords are read from a private file."""
import argparse
import hashlib
import json
import os
from pathlib import Path
import re
import subprocess
import tempfile
import zipfile

if __package__:
    from .release_identity import TARGET_ABIS, artifact_names, release_config
else:
    from release_identity import TARGET_ABIS, artifact_names, release_config

KEY_ALIAS = 'armv7-tv-release'
CERTIFICATE_SHA256 = '464eab8f658b68c234e80e85f5bcb6c5a79771600ac04c0f9d5458769c27b60e'


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--target', choices=TARGET_ABIS, default='armv7')
    parser.add_argument('--apk', type=Path, required=True)
    parser.add_argument('--sdk', type=Path, required=True)
    parser.add_argument('--keystore', type=Path, required=True)
    parser.add_argument('--password-file', type=Path, required=True)
    parser.add_argument('--output-dir', type=Path, required=True)
    args = parser.parse_args()
    root = Path(__file__).resolve().parents[2]
    toolchain = json.loads((root / 'tools/android-toolchain.json').read_text())
    bt = args.sdk.resolve() / 'build-tools' / toolchain['buildTools']
    env = os.environ.copy()
    env['LD_LIBRARY_PATH'] = str(bt / 'lib64') + ':' + env.get('LD_LIBRARY_PATH', '')

    def run(command):
        return subprocess.check_output(list(map(str, command)), env=env,
                                       stderr=subprocess.STDOUT, text=True)

    badging = run([bt / 'aapt', 'dump', 'badging', args.apk])
    version = re.search(r"versionName='([^']+)'", badging).group(1)
    code = int(re.search(r"versionCode='(\d+)'", badging).group(1))
    expected = release_config(root)
    if (code != expected['versionCode'] or version != expected['versionName']
            or "name='dev.nfs3hp.port.armv7tv'" not in badging):
        raise RuntimeError('Unexpected release package/version')
    if not re.fullmatch(r'[\w.\-]+', version):
        raise RuntimeError('Unexpected version name')
    out = args.output_dir.resolve()
    out.mkdir(parents=True, exist_ok=True)
    names = artifact_names(version, args.target)
    apk = out / names['apk']
    if apk == args.apk.resolve():
        raise RuntimeError('Input and output APK must differ')
    run([bt / 'zipalign', '-f', '-P', '16', '4', args.apk, apk])
    run([bt / 'apksigner', 'sign', '--ks', args.keystore,
         '--ks-key-alias', KEY_ALIAS, '--ks-pass',
         'file:' + str(args.password_file.resolve()), apk])
    certificate = CERTIFICATE_SHA256
    if certificate not in run([bt / 'apksigner', 'verify', '--verbose', '--print-certs', apk]):
        raise RuntimeError('Signing identity differs from installed TV releases')
    run([bt / 'zipalign', '-c', '-P', '16', '4', apk])
    manifest = run([bt / 'aapt', 'dump', 'xmltree', apk, 'AndroidManifest.xml'])
    precision_match = re.search(r'android:name[^\n]*"dev\.nfs3hp\.port\.GAME_PRECISION"[^\n]*\n[^\n]*android:value[^\n]*"(DOUBLE|SINGLE)"', manifest)
    if not precision_match:
        raise RuntimeError('APK lacks compile-time game precision metadata')
    precision = precision_match.group(1)
    if 'android:debuggable' in manifest or 'profileable' not in manifest or not re.search(r'android:shell[^\n]*0xffffffff', manifest):
        raise RuntimeError('Expected non-debug, shell-profileable release')
    readelf = (args.sdk.resolve() / 'ndk' / toolchain['ndk'] / 'toolchains/llvm/prebuilt'
               / 'linux-x86_64/bin/llvm-readelf')

    def build_id(file):
        return re.search(r'Build ID: (\w+)', run([readelf, '-n', file])).group(1)

    abis = TARGET_ABIS[args.target]
    identities = {}
    symbol_dirs = {}
    with tempfile.TemporaryDirectory(prefix='verify-', dir=out) as temporary:
        temp = Path(temporary)
        with zipfile.ZipFile(apk) as z:
            libraries = [n for n in z.namelist() if n.startswith('lib/') and n.endswith('.so')]
            if {n.split('/')[1] for n in libraries} != set(abis):
                raise RuntimeError('APK native ABIs differ from selected target')
            for name in libraries:
                data = z.read(name)
                abi = name.split('/')[1]
                elf_class, machine = (1, 40) if abi == 'armeabi-v7a' else (2, 183)
                if (data[:6] != b'\x7fELF' + bytes([elf_class, 1])
                        or int.from_bytes(data[18:20], 'little') != machine):
                    raise RuntimeError('Unexpected native ELF: ' + name)
            for abi in abis:
                required = {f'lib/{abi}/{name}' for name in ('libmain.so', 'libSDL3.so', 'libc++_shared.so')}
                if not required.issubset(libraries):
                    raise RuntimeError('Missing required native libraries for ' + abi)
                main_library = temp / (abi + '-libmain.so')
                main_library.write_bytes(z.read(f'lib/{abi}/libmain.so'))
                identities[abi] = build_id(main_library)
                candidates = (root / 'android/app/build/intermediates/cxx/RelWithDebInfo').glob('*/obj/' + abi)
                matches = [p for p in candidates if (p / 'libmain.so').is_file()
                           and build_id(p / 'libmain.so') == identities[abi]]
                if not matches:
                    raise RuntimeError('No exact matching unstripped native symbols for ' + abi)
                symbol_dirs[abi] = matches[0]
    symbols = out / names['symbols']
    with zipfile.ZipFile(symbols, 'w', zipfile.ZIP_DEFLATED, 6) as z:
        for abi in abis:
            for p in sorted(symbol_dirs[abi].glob('*.so')):
                z.write(p, abi + '/' + p.name)
        z.writestr('README.txt', 'Exact native symbols for ' + apk.name +
                   '\nNative BuildIDs: ' + json.dumps(identities, sort_keys=True) +
                   '\nNot needed to install or play.\n')
    resource_report = out / 'apk-resource-check.json'
    run(['python3', root / 'tools/game_checks/gamepad/check_apk_resources.py', apk, bt,
         root / 'android/app/build/intermediates/compile_symbol_list/release/generateReleaseRFile/R.txt',
         resource_report])
    source = run(['git', '-C', root, 'rev-parse', 'HEAD']).strip()
    summary = {'version': version, 'versionCode': code, 'revision': expected['revision'],
               'target': args.target, 'game_precision': precision, 'architectures': list(abis), 'source_commit': source,
               'uncommitted_changes': bool(run(['git', '-C', root, 'status', '--porcelain']).strip()),
               'apk': apk.name, 'apk_sha256': hashlib.sha256(apk.read_bytes()).hexdigest(),
               'native_build_ids': identities, 'certificate_sha256': certificate,
               'native_files': libraries, 'debuggable': False, 'shell_profileable': True,
               'zip_alignment_bytes': 16384, 'device_tested': False,
               'resource_check': json.loads(resource_report.read_text()), 'toolchain': toolchain}
    report = out / names['report']
    report.write_text(json.dumps(summary, indent=2) + '\n')
    with zipfile.ZipFile(symbols, 'a', zipfile.ZIP_DEFLATED) as z:
        z.write(report, 'metadata/release.json')
    print(json.dumps(summary, indent=2))


if __name__ == '__main__':
    main()

