"""Shared Android fork version mapping and artifact names, including historical TV builds."""
import json
import re


def revision_of(version):
    numeric = re.fullmatch(r'\d+\.\d+\.(\d+)', version)
    legacy = re.fullmatch(r'\d+\.\d+-armv7-tv(\d+)(?:-profile)?', version)
    match = numeric or legacy
    if not match:
        raise RuntimeError('Cannot identify the fork revision from APK version: ' + version)
    return int(match[1])


TARGET_ABIS = {
    'armv7': ('armeabi-v7a',),
    'armv8': ('arm64-v8a',),
    'both': ('armeabi-v7a', 'arm64-v8a'),
}


def artifact_names(version, target='armv7'):
    if target not in TARGET_ABIS:
        raise RuntimeError('Unknown Android target: ' + target)
    if not re.fullmatch(r'[\w.\-]+', version):
        raise RuntimeError('Invalid APK version name.')
    if re.fullmatch(r'\d+\.\d+\.\d+', version):
        stem = f'nfs3-{version}-' + ('universal' if target == 'both' else target)
        return {'apk': stem + '.apk', 'report': stem + '-release.json',
                'symbols': stem + '-symbols.zip'}
    stem = 'nfs3-' + version
    return {'apk': stem + '-release.apk', 'report': stem + '-release.json',
            'symbols': stem + '-symbols.zip'}


def published_version(filename):
    numeric = re.fullmatch(r'nfs3-(\d+\.\d+\.\d+)-(?:armv7|armv8|universal)\.apk', filename)
    legacy = re.fullmatch(r'nfs3-(\d+\.\d+-armv7-tv\d+(?:-profile)?)-release\.apk', filename)
    match = numeric or legacy
    return match[1] if match else None


def release_config(root):
    config = json.loads((root / 'tools/android-release.json').read_text())
    if (not re.fullmatch(r'\d+\.\d+\.\d+', config['versionName'])
            or type(config['versionCode']) is not int or config['versionCode'] <= 0
            or type(config['revision']) is not int
            or revision_of(config['versionName']) != config['revision']):
        raise RuntimeError('Invalid numeric Android release mapping.')
    return config

