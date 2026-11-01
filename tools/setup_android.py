#!/usr/bin/env python3
"""Install the selected Android SDK packages, CMake and native SDL source.

Requires git, curl, JDK and Android command-line tools. Reuses installed tools
and the selected cache; never installs or reads signing credentials.
"""
import argparse
import hashlib
import json
import os
from pathlib import Path
import platform
import re
import shutil
import subprocess
import tarfile

ROOT = Path(__file__).resolve().parents[1]


def run(*args, **kwargs):
    return subprocess.check_output(list(map(str, args)), text=True, **kwargs).strip()


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--cache-dir', type=Path, default=Path(os.environ.get(
        'NFS_BUILD_CACHE', str(Path.home() / '.cache/nfs3-build'))))
    parser.add_argument('--update-sdl', action='store_true', help='Update a clean existing SDL checkout')
    args = parser.parse_args()
    config = json.loads((ROOT / 'tools/android-toolchain.json').read_text())
    wrapper = (ROOT / 'android/gradle/wrapper/gradle-wrapper.properties').read_text()
    if f"gradle-{config['gradle']}-bin.zip" not in wrapper:
        raise SystemExit('Gradle wrapper and android-toolchain.json disagree.')
    java = str(Path(os.environ['JAVA_HOME']) / 'bin/java') if os.environ.get('JAVA_HOME') else shutil.which('java')
    if not java:
        raise SystemExit(f"Install JDK {config['jdk']} LTS and set JAVA_HOME first.")
    version = run(java, '-version', stderr=subprocess.STDOUT)
    major = int(re.search(r'version "(\d+)', version).group(1))
    if not 25 <= major <= 27:
        raise SystemExit(f"Use JDK {config['jdk']} LTS (tested), or compatible JDK 26/27. Found {major}.")
    sdk_value = os.environ.get('ANDROID_HOME') or os.environ.get('ANDROID_SDK_ROOT')
    if not sdk_value:
        raise SystemExit('Set ANDROID_HOME to an SDK with Android command-line tools installed.')
    sdk = Path(sdk_value).resolve()
    sdkmanager = shutil.which('sdkmanager') or str(sdk / 'cmdline-tools/latest/bin/sdkmanager')
    subprocess.run([sdkmanager, '--sdk_root=' + str(sdk), config['platformPackage'],
                    'build-tools;' + config['buildTools'], 'ndk;' + config['ndk']], check=True)
    for p in [sdk / 'build-tools' / config['buildTools'], sdk / 'ndk' / config['ndk']]:
        if not (p / 'source.properties').is_file():
            raise SystemExit(f'Incomplete SDK installation: {p}. Repair it before building.')

    cmake = shutil.which('cmake')
    if not cmake or run(cmake, '--version').splitlines()[0] != 'cmake version ' + config['cmake']:
        if platform.system() != 'Linux' or platform.machine() not in ('x86_64', 'AMD64'):
            raise SystemExit(f"Install CMake {config['cmake']} and add it to PATH, then rerun.")
        cache = args.cache_dir.resolve()
        cache.mkdir(parents=True, exist_ok=True)
        base = f"cmake-{config['cmake']}-linux-x86_64"
        home = cache / base
        if not (home / 'bin/cmake').is_file():
            url = f"https://github.com/Kitware/CMake/releases/download/v{config['cmake']}/"
            archive = cache / (base + '.tar.gz')
            checksums = cache / f"cmake-{config['cmake']}-SHA-256.txt"
            for p in (archive, checksums):
                if not p.exists():
                    partial = p.with_name(p.name + '.part')
                    subprocess.run(['curl', '-fL', '--retry', '2', '-o', str(partial), url + p.name], check=True)
                    partial.replace(p)
            expected = next(line.split()[0] for line in checksums.read_text().splitlines()
                            if line.split()[-1].lstrip('*') == archive.name)
            if hashlib.sha256(archive.read_bytes()).hexdigest() != expected:
                raise SystemExit(f'Checksum mismatch: remove {archive} and rerun.')
            staging = cache / (base + '.extracting')
            if staging.exists():
                shutil.rmtree(staging)
            staging.mkdir()
            with tarfile.open(archive) as tar:
                tar.extractall(staging, filter='data')
            (staging / base).rename(home)
            staging.rmdir()
        cmake = str(home / 'bin/cmake')
    if run(cmake, '--version').splitlines()[0] != 'cmake version ' + config['cmake']:
        raise SystemExit('Cached CMake does not match the selected version.')
    properties = ROOT / 'android/local.properties'
    lines = properties.read_text().splitlines() if properties.exists() else []
    lines = [line for line in lines if not line.startswith(('sdk.dir=', 'cmake.dir='))]
    lines += ['sdk.dir=' + sdk.as_posix(), 'cmake.dir=' + Path(cmake).resolve().parent.parent.as_posix()]
    properties.write_text('\n'.join(lines) + '\n')

    sdl = ROOT / 'third_party/SDL'
    if not sdl.exists():
        sdl.parent.mkdir(exist_ok=True)
        subprocess.run(['git', 'clone', '--depth', '1', '--branch', 'release-' + config['sdl'],
                        'https://github.com/libsdl-org/SDL.git', str(sdl)], check=True)
    if run('git', '-C', sdl, 'rev-parse', 'HEAD') != config['sdlCommit']:
        if not args.update_sdl or run('git', '-C', sdl, 'status', '--porcelain'):
            raise SystemExit('SDL revision differs or has local changes. Review it; use --update-sdl only for a clean checkout.')
        subprocess.run(['git', '-C', str(sdl), 'fetch', '--depth', '1', 'origin',
                        'tag', 'release-' + config['sdl']], check=True)
        subprocess.run(['git', '-C', str(sdl), 'checkout', '--detach', config['sdlCommit']], check=True)
    if run('git', '-C', sdl, 'rev-parse', 'HEAD') != config['sdlCommit']:
        raise SystemExit('SDL commit does not match the selected toolchain.')
    print('Android tools and SDL are ready. Run the approved checks/build with android/gradlew.')


if __name__ == '__main__':
    main()
