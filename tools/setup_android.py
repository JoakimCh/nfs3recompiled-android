#!/usr/bin/env python3
"""Prepare reusable Android tools. Setup never runs tests, builds or signing."""
import argparse
import hashlib
import json
import os
from pathlib import Path
import platform
import re
import shlex
import shutil
import subprocess
import sys
import tarfile
import tempfile
import urllib.parse
import xml.etree.ElementTree as ET
import zipfile

ROOT = Path(__file__).resolve().parents[1]
CONFIG = ROOT / 'tools/android-toolchain.json'


def output(command, env):
    return subprocess.check_output(list(map(str, command)), env=env,
                                   stderr=subprocess.STDOUT, text=True).strip()


def digest(path, algorithm='sha256'):
    with Path(path).open('rb') as stream:
        return hashlib.file_digest(stream, algorithm).hexdigest()


def download(url, path, env):
    path = Path(path)
    path.parent.mkdir(parents=True, exist_ok=True)
    partial = path.with_name(path.name + '.part')
    print('Downloading ' + path.name, flush=True)
    subprocess.run(['curl', '-fsSL', '--retry', '2', '--connect-timeout', '60',
                    '--max-time', '600', '-o', str(partial), url], env=env, check=True)
    partial.replace(path)


def verified_download(url, path, expected, env, algorithm='sha256'):
    path = Path(path)
    if not path.exists() or digest(path, algorithm) != expected:
        download(url, path, env)
    if digest(path, algorithm) != expected:
        raise RuntimeError('Checksum mismatch: ' + str(path))
    return path


def linux_bootstrap():
    if platform.system() != 'Linux' or platform.machine() not in ('x86_64', 'AMD64'):
        raise RuntimeError('Automatic downloads require Linux x86_64. Supply compatible installed tools on this host.')


def unpack(archive, destination, cache):
    destination = Path(destination)
    destination.parent.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(prefix='install-', dir=cache) as temporary:
        staging = Path(temporary) / 'unpacked'
        staging.mkdir()
        if zipfile.is_zipfile(archive):
            with zipfile.ZipFile(archive) as bundle:
                for member in bundle.infolist():
                    if not (staging / member.filename).resolve().is_relative_to(staging.resolve()):
                        raise RuntimeError('Unsafe archive path')
                bundle.extractall(staging)
                for member in bundle.infolist():
                    path = staging / member.filename
                    mode = (member.external_attr >> 16) & 0o777
                    if mode and path.is_file():
                        path.chmod(mode)
        else:
            with tarfile.open(archive) as bundle:
                bundle.extractall(staging, filter='data')
        children = list(staging.iterdir())
        source = children[0] if len(children) == 1 and children[0].is_dir() else staging
        if destination.exists():
            raise RuntimeError('Incomplete cached tool directory; remove it and retry: ' + str(destination))
        shutil.move(str(source), destination)


def local_properties():
    path = ROOT / 'android/local.properties'
    if not path.exists():
        return {}
    return dict(line.split('=', 1) for line in path.read_text().splitlines()
                if '=' in line and not line.lstrip().startswith('#'))


def java_env(home, env):
    env = dict(env)
    env['JAVA_HOME'] = str(home)
    env['PATH'] = str(home / 'bin') + os.pathsep + env.get('PATH', '')
    env['LD_LIBRARY_PATH'] = os.pathsep.join([str(home / 'lib'), str(home / 'lib/server'),
                                            env.get('LD_LIBRARY_PATH', '')])
    return env


def compatible_java(home, env):
    try:
        text = output([home / 'bin/java', '-version'], java_env(home, env))
        match = re.search(r'version "(\d+)', text)
        return bool(match and 25 <= int(match.group(1)) <= 27)
    except (OSError, subprocess.CalledProcessError):
        return False


def runtime(cache, jobs=2):
    """Resolve Java and current session networking; never persist proxy ports or secrets."""
    if sys.version_info < (3, 12):
        raise RuntimeError('Android bootstrap requires Python 3.12 or newer.')
    cache = Path(cache).expanduser().resolve()
    cache.mkdir(parents=True, exist_ok=True)
    config = json.loads(CONFIG.read_text())
    env = os.environ.copy()
    state_path = cache / 'environment.json'
    state = json.loads(state_path.read_text()) if state_path.exists() else {}
    java = shutil.which('java')
    candidates = [env.get('JAVA_HOME'), state.get('java_home'),
                  str(cache / ('jdk-' + str(config['jdk']))),
                  str(Path(java).resolve().parent.parent) if java else None]
    home = next((Path(p) for p in candidates if p and compatible_java(Path(p), env)), None)
    if home is None:
        linux_bootstrap()
        metadata = cache / 'downloads/jdk.json'
        download('https://api.adoptium.net/v3/assets/latest/' + str(config['jdk'])
                 + '/hotspot?architecture=x64&image_type=jdk&os=linux', metadata, env)
        package = json.loads(metadata.read_text())[0]['binary']['package']
        archive = verified_download(package['link'], cache / 'downloads' / package['name'],
                                    package['checksum'], env)
        home = cache / ('jdk-' + str(config['jdk']))
        unpack(archive, home, cache)
    env = java_env(home, env)
    if not compatible_java(home, env):
        raise RuntimeError('Use the selected JDK 25, or a compatible installed JDK 26/27.')
    temporary = cache / 'tmp'
    temporary.mkdir(exist_ok=True)
    env.update(TMPDIR=str(temporary), NFS_BUILD_CACHE=str(cache), CMAKE_BUILD_PARALLEL_LEVEL=str(jobs))
    env.setdefault('GRADLE_USER_HOME', str(cache / 'gradle'))
    flags = ['-XX:-UsePerfData', '-XX:ActiveProcessorCount=' + str(jobs),
             '-Djava.net.preferIPv4Stack=true', '-Djava.io.tmpdir=' + str(temporary)]
    ca = env.get('SSL_CERT_FILE') or env.get('REQUESTS_CA_BUNDLE')
    if ca and Path(ca).is_file():
        cacerts = home / 'lib/security/cacerts'
        trust = cache / 'java-truststore'
        marker = cache / 'java-truststore.sha256'
        fingerprint = digest(cacerts) + ':' + digest(ca)
        if not trust.exists() or not marker.exists() or marker.read_text() != fingerprint:
            shutil.copyfile(cacerts, trust)
            data = Path(ca).read_bytes()
            certificates = re.findall(rb'-----BEGIN CERTIFICATE-----.*?-----END CERTIFICATE-----', data, re.S)
            if not certificates:
                raise RuntimeError('Configured CA file contains no PEM certificates: ' + ca)
            for index, certificate in enumerate(certificates):
                with tempfile.NamedTemporaryFile(dir=temporary, suffix='.crt') as cert:
                    cert.write(certificate); cert.flush()
                    subprocess.run([str(home / 'bin/keytool'), '-importcert', '-noprompt',
                                    '-alias', 'nfs-environment-' + str(index), '-file', cert.name,
                                    '-keystore', str(trust), '-storepass', 'changeit'], env=env,
                                   stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL, check=True)
            marker.write_text(fingerprint)
        flags += ['-Djavax.net.ssl.trustStore=' + str(trust), '-Djavax.net.ssl.trustStorePassword=changeit']
    for protocol in ('http', 'https'):
        value = env.get(protocol.upper() + '_PROXY') or env.get(protocol + '_proxy')
        if not value:
            value = env.get('HTTPS_PROXY') or env.get('HTTP_PROXY')
        if value:
            proxy = urllib.parse.urlparse(value)
            if proxy.hostname:
                flags += ['-D' + protocol + '.proxyHost=' + proxy.hostname,
                          '-D' + protocol + '.proxyPort=' + str(proxy.port or (443 if proxy.scheme == 'https' else 80))]
    env['JAVA_TOOL_OPTIONS'] = ' '.join(filter(None, [env.get('JAVA_TOOL_OPTIONS', ''), shlex.join(flags)]))
    return env, [flag for flag in flags if flag.startswith('-D')], state


def sdk_installer(sdk, cache, env, config):
    candidates = [sdk / 'cmdline-tools/latest/bin/sdkmanager']
    candidates += sorted((sdk / 'cmdline-tools').glob('*/bin/sdkmanager'), reverse=True)
    # Installer 23's native bootstrap needs /proc/self/exe. Use the known Java installer here.
    restricted = platform.system() == 'Linux' and not Path('/proc/self/exe').exists()
    if restricted:
        candidates = [sdk / ('cmdline-tools/' + config['sdkCommandLineToolsFallback']) / 'bin/sdkmanager']
    found = next((p for p in candidates if p.is_file()), None)
    if found:
        return found
    linux_bootstrap()
    metadata = cache / 'downloads/android-repository.xml'
    download('https://dl.google.com/android/repository/repository2-3.xml', metadata, env)
    name = config['sdkCommandLineToolsFallback'] if restricted else 'latest'
    package = next(e for e in ET.parse(metadata).getroot().findall('remotePackage')
                   if e.get('path') == 'cmdline-tools;' + name)
    archive = next(e for e in package.findall('archives/archive') if e.findtext('host-os') == 'linux')
    checksum = archive.find('complete/checksum')
    filename = archive.findtext('complete/url')
    path = verified_download('https://dl.google.com/android/repository/' + filename,
                             cache / 'downloads' / filename, checksum.text, env,
                             checksum.get('type', 'sha1'))
    home = sdk / 'cmdline-tools' / name
    unpack(path, home, cache)
    for executable in (home / 'bin').iterdir():
        if executable.is_file(): executable.chmod(0o755)
    print('SDK installer: ' + name + (' (restricted workspace fallback)' if restricted else ''), flush=True)
    return home / 'bin/sdkmanager'


def repair_sdk(package):
    if (package / 'source.properties').exists() or not package.is_dir():
        return
    candidates = [p for p in package.iterdir() if p.is_dir() and p.name.startswith('android-')
                  and (p / 'source.properties').exists() and not p.name.startswith('android-ndk')]
    if len(candidates) == 1:
        nested = candidates[0]
        if any((package / p.name).exists() for p in nested.iterdir()):
            raise RuntimeError('Cannot safely flatten SDK package: ' + str(package))
        for p in list(nested.iterdir()): shutil.move(str(p), package / p.name)
        nested.rmdir()
        print('Repaired SDK package layout: ' + package.name, flush=True)


def install_sdk(command, env, cache, accept):
    log = cache / 'logs/sdk-setup.log'
    log.parent.mkdir(exist_ok=True)
    with log.open('a') as stream:
        try:
            subprocess.run(list(map(str, command)), input=('y\n' * 1000 if accept else ''),
                           text=True, env=env, stdout=stream, stderr=subprocess.STDOUT, check=True)
        except subprocess.CalledProcessError:
            raise RuntimeError('SDK installation failed; see ' + str(log) + '\n'
                               + log.read_text(errors='replace')[-2000:]) from None


def cmake_and_ninja(cache, env, config):
    cmake = shutil.which('cmake', path=env['PATH'])
    configured = local_properties().get('cmake.dir')
    candidates = ([Path(configured)] if configured else [])
    if cmake: candidates.append(Path(cmake).resolve().parent.parent)
    for home in candidates:
        if ((home / 'bin/cmake').is_file() and (home / 'bin/ninja').is_file()
                and output([home / 'bin/cmake', '--version'], env).splitlines()[0] == 'cmake version ' + config['cmake']
                and output([home / 'bin/ninja', '--version'], env) == config['ninja']):
            return home
    linux_bootstrap()
    base = 'cmake-' + config['cmake'] + '-linux-x86_64'
    home = cache / base
    if not (home / 'bin/cmake').is_file():
        url = 'https://github.com/Kitware/CMake/releases/download/v' + config['cmake'] + '/'
        checksums = cache / 'downloads' / ('cmake-' + config['cmake'] + '-SHA-256.txt')
        download(url + checksums.name, checksums, env)
        filename = base + '.tar.gz'
        expected = next(line.split()[0] for line in checksums.read_text().splitlines()
                        if line.split()[-1].lstrip('*') == filename)
        archive = verified_download(url + filename, cache / 'downloads' / filename, expected, env)
        unpack(archive, home, cache)
    if output([home / 'bin/cmake', '--version'], env).splitlines()[0] != 'cmake version ' + config['cmake']:
        raise RuntimeError('Cached CMake version differs from the manifest.')
    ninja = home / 'bin/ninja'
    if not ninja.exists() or output([ninja, '--version'], env) != config['ninja']:
        archive = verified_download('https://github.com/ninja-build/ninja/releases/download/v'
                                    + config['ninja'] + '/ninja-linux.zip',
                                    cache / 'downloads' / ('ninja-' + config['ninja'] + '.zip'),
                                    config['ninjaSha256LinuxX64'], env)
        if ninja.is_symlink(): ninja.unlink()
        with zipfile.ZipFile(archive) as bundle:
            ninja.write_bytes(bundle.read('ninja'))
        ninja.chmod(0o755)
    return home


def prepare(cache, native=True, accept_licenses=False, jobs=2, update_sdl=False):
    cache = Path(cache).expanduser().resolve()
    config = json.loads(CONFIG.read_text())
    wrapper = (ROOT / 'android/gradle/wrapper/gradle-wrapper.properties').read_text()
    if 'gradle-' + config['gradle'] + '-bin.zip' not in wrapper:
        raise RuntimeError('Gradle wrapper and toolchain manifest disagree.')
    env, flags, state = runtime(cache, jobs)
    explicit_sdk = env.get('ANDROID_HOME') or env.get('ANDROID_SDK_ROOT')
    known_sdks = [state.get('sdk'), local_properties().get('sdk.dir')]
    known_sdk = next((p for p in known_sdks if p and Path(p).is_dir()), None)
    sdk = Path(explicit_sdk or known_sdk or str(cache / 'sdk')).expanduser().resolve()
    sdk.mkdir(parents=True, exist_ok=True)
    env.update(ANDROID_HOME=str(sdk), ANDROID_SDK_ROOT=str(sdk))
    packages = [(config['platformPackage'], sdk / 'platforms' / config['platformPackage'].split(';')[1], 'android.jar'),
                ('build-tools;' + config['buildTools'], sdk / 'build-tools' / config['buildTools'], 'aapt2'),
                ('platform-tools', sdk / 'platform-tools', 'adb')]
    if native:
        packages.append(('ndk;' + config['ndk'], sdk / 'ndk' / config['ndk'],
                         'toolchains/llvm/prebuilt/linux-x86_64/bin/clang'))
    for _, path, _ in packages: repair_sdk(path)
    missing = [name for name, path, sentinel in packages
               if not (path / 'source.properties').is_file() or not (path / sentinel).is_file()]
    if missing:
        installer = sdk_installer(sdk, cache, env, config)
        print('Installing SDK packages: ' + ', '.join(missing), flush=True)
        if accept_licenses:
            install_sdk([installer, '--sdk_root=' + str(sdk), '--licenses'], env, cache, True)
        install_sdk([installer, '--sdk_root=' + str(sdk), *missing], env, cache, accept_licenses)
        for _, path, _ in packages: repair_sdk(path)
    for name, path, sentinel in packages:
        if not (path / 'source.properties').is_file() or not (path / sentinel).is_file():
            raise RuntimeError('Incomplete SDK package ' + name + ': ' + str(path))
    properties = ROOT / 'android/local.properties'
    lines = properties.read_text().splitlines() if properties.exists() else []
    lines = [line for line in lines if not line.startswith('sdk.dir=')]
    lines.append('sdk.dir=' + sdk.as_posix())
    state.update(java_home=env['JAVA_HOME'], sdk=str(sdk))
    if native:
        home = cmake_and_ninja(cache, env, config)
        env['PATH'] = str(home / 'bin') + os.pathsep + env['PATH']
        lines = [line for line in lines if not line.startswith('cmake.dir=')]
        lines.append('cmake.dir=' + home.as_posix())
        state['cmake'] = str(home)
        sdl = ROOT / 'third_party/SDL'
        if not sdl.exists():
            sdl.parent.mkdir(exist_ok=True)
            subprocess.run(['git', 'clone', '--depth', '1', '--branch', 'release-' + config['sdl'],
                            'https://github.com/libsdl-org/SDL.git', str(sdl)], env=env, check=True)
        if output(['git', '-C', sdl, 'status', '--porcelain'], env):
            raise RuntimeError('SDL has local changes; review them before setup.')
        if output(['git', '-C', sdl, 'rev-parse', 'HEAD'], env) != config['sdlCommit']:
            if not update_sdl:
                raise RuntimeError('SDL revision differs; review it and use --update-sdl for a clean checkout.')
            subprocess.run(['git', '-C', str(sdl), 'fetch', '--depth', '1', 'origin',
                            'tag', 'release-' + config['sdl']], env=env, check=True)
            subprocess.run(['git', '-C', str(sdl), 'checkout', '--detach', config['sdlCommit']], env=env, check=True)
        if output(['git', '-C', sdl, 'rev-parse', 'HEAD'], env) != config['sdlCommit']:
            raise RuntimeError('SDL commit differs from the manifest.')
    properties.write_text('\n'.join(lines) + '\n')
    (cache / 'environment.json').write_text(json.dumps(state, indent=2) + '\n')
    print('Android setup ready: ' + ('native + launcher' if native else 'launcher only')
          + '; cache=' + str(cache), flush=True)
    return env, flags


def arguments(parser):
    parser.add_argument('--cache-dir', type=Path, default=Path(os.environ.get('NFS_BUILD_CACHE', ROOT.parent / 'nfs3-build-cache')))
    parser.add_argument('--accept-sdk-licenses', action='store_true', help='Accept Android SDK licenses during installation')
    parser.add_argument('--jobs', type=int, default=2)
    parser.add_argument('--update-sdl', action='store_true', help='Update a reviewed clean SDL checkout')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    arguments(parser)
    parser.add_argument('--tests-only', action='store_true')
    args = parser.parse_args()
    if args.jobs < 1: parser.error('--jobs must be positive')
    try:
        prepare(args.cache_dir, not args.tests_only, args.accept_sdk_licenses, args.jobs, args.update_sdl)
    except (OSError, RuntimeError, subprocess.CalledProcessError, ValueError) as error:
        raise SystemExit(str(error))


if __name__ == '__main__':
    main()
