"""Release promotion rejects mismatched files and never substitutes expired builds."""
import hashlib
import io
import json
import os
from pathlib import Path
import subprocess
import tempfile
import unittest
from unittest.mock import patch
import zipfile

from tools.release import publish_android as publish
from tools.release.release_identity import artifact_names, published_version, release_config, revision_of


def archive(files):
    data = io.BytesIO()
    with zipfile.ZipFile(data, 'w') as zipped:
        for name, value in files.items():
            zipped.writestr(name, json.dumps(value) if isinstance(value, dict) else value)
    return zipfile.ZipFile(io.BytesIO(data.getvalue()))


class ReleasePromotionTests(unittest.TestCase):
    def fixture(self, wrong_hash=False, wrong_symbols=False, failed_tests=False, version="test", fast=False, validation_updates=None):
        names = artifact_names(version)
        metadata = {
            'version': version, 'versionCode': 106 if version == '0.78.29' else 105, 'apk': names['apk'],
            'source_commit': 'a' * 40, 'uncommitted_changes': False,
            'certificate_sha256': publish.CERTIFICATE_SHA256,
            'resource_check': {'passed': True}, 'debuggable': False,
            'shell_profileable': True, 'zip_alignment_bytes': 16384,
            'apk_sha256': 'bad' if wrong_hash else hashlib.sha256(b'apk').hexdigest(),
            'native_build_id': '1234',
        }
        validation = {'source_commit': 'a' * 40, 'source_dirty': False, 'mode': 'apk',
                      'native_compiled': True, 'tests': {'tests': 14, 'failures': int(failed_tests),
                                                       'errors': 0, 'skipped': 0}}
        if fast:
            validation.update(mode='apk-fast', tests=None)
        validation.update(validation_updates or {})
        symbol_metadata = dict(metadata, native_build_id='other') if wrong_symbols else metadata
        with archive({'metadata/release.json': symbol_metadata,
                      'armeabi-v7a/libmain.so': b'symbols'}) as symbols:
            symbols_bytes = symbols.fp.getvalue()
        artifacts = [archive({names['report']: metadata, names['apk']: b'apk',
                              'validation.json': validation}),
                     archive({names['symbols']: symbols_bytes})]
        for artifact in artifacts:
            self.addCleanup(artifact.close)
        return artifacts

    def test_preserves_exact_files(self):
        with tempfile.TemporaryDirectory() as temp, patch.object(publish, 'artifact', side_effect=self.fixture()):
            result = publish.prepare('owner/repo', {'head_sha': 'a' * 40}, Path(temp))
            self.assertEqual((Path(temp) / result['apk']).read_bytes(), b'apk')
            self.assertEqual(len(list(Path(temp).iterdir())), 4)

    def test_numeric_artifacts_are_promoted_without_renaming_or_rebuilding(self):
        with tempfile.TemporaryDirectory() as temp, patch.object(publish, 'artifact', side_effect=self.fixture(version='0.78.29')):
            result = publish.prepare('owner/repo', {'head_sha': 'a' * 40}, Path(temp))
            self.assertEqual(result['apk'], 'nfs3-0.78.29-armv7.apk')
            self.assertEqual((Path(temp) / result['apk']).read_bytes(), b'apk')
            self.assertTrue((Path(temp) / 'nfs3-0.78.29-armv7-symbols.zip').is_file())

    def test_rejects_apk_hash_mismatch(self):
        with tempfile.TemporaryDirectory() as temp, patch.object(publish, 'artifact', side_effect=self.fixture(wrong_hash=True)):
            with self.assertRaisesRegex(RuntimeError, 'APK SHA-256 mismatch'):
                publish.prepare('owner/repo', {'head_sha': 'a' * 40}, Path(temp))

    def test_rejects_unrelated_symbols(self):
        with tempfile.TemporaryDirectory() as temp, patch.object(publish, 'artifact', side_effect=self.fixture(wrong_symbols=True)):
            with self.assertRaisesRegex(RuntimeError, 'Symbol metadata'):
                publish.prepare('owner/repo', {'head_sha': 'a' * 40}, Path(temp))

    def test_rejects_failed_tests(self):
        with tempfile.TemporaryDirectory() as temp, patch.object(publish, 'artifact', side_effect=self.fixture(failed_tests=True)):
            with self.assertRaisesRegex(RuntimeError, 'Build validation'):
                publish.prepare('owner/repo', {'head_sha': 'a' * 40}, Path(temp))

    def test_promotes_fast_apk_preserving_skipped_test_metadata(self):
        with tempfile.TemporaryDirectory() as temp, patch.object(publish, 'artifact', side_effect=self.fixture(fast=True)):
            result = publish.prepare('owner/repo', {'head_sha': 'a' * 40}, Path(temp))
            self.assertEqual((Path(temp) / result['apk']).read_bytes(), b'apk')
            self.assertTrue((Path(temp) / artifact_names(result['version'])['symbols']).is_file())
            validation = json.loads((Path(temp) / 'validation.json').read_bytes())
            self.assertEqual(validation['mode'], 'apk-fast')
            self.assertIsNone(validation['tests'])

    def test_fast_apk_still_requires_clean_native_build_and_explicit_skip(self):
        for update in ({'source_dirty': True}, {'source_commit': 'b' * 40},
                       {'native_compiled': False}, {'mode': 'check'},
                       {'tests': {'tests': 14, 'failures': 1, 'errors': 0, 'skipped': 0}}):
            with self.subTest(update=update), tempfile.TemporaryDirectory() as temp, \
                 patch.object(publish, 'artifact', side_effect=self.fixture(fast=True, validation_updates=update)):
                with self.assertRaisesRegex(RuntimeError, 'Build validation'):
                    publish.prepare('owner/repo', {'head_sha': 'a' * 40}, Path(temp))

    def test_normal_apk_cannot_skip_tests(self):
        with tempfile.TemporaryDirectory() as temp, \
             patch.object(publish, 'artifact', side_effect=self.fixture(validation_updates={'tests': None})):
            with self.assertRaisesRegex(RuntimeError, 'Build validation'):
                publish.prepare('owner/repo', {'head_sha': 'a' * 40}, Path(temp))

    def test_expired_artifact_fails_before_download(self):
        with patch.object(publish, 'pages', return_value=iter([
                {'name': 'armv7-apk', 'expired': True}])), patch.object(publish, 'gh') as gh:
            with self.assertRaisesRegex(RuntimeError, 'expired'):
                publish.artifact('owner/repo', {'id': 123}, 'armv7-apk')
            gh.assert_not_called()

    def test_existing_tag_is_never_overwritten(self):
        with patch.object(publish.subprocess, 'run', return_value=subprocess.CompletedProcess([], 0)):
            with self.assertRaisesRegex(RuntimeError, 'already exists'):
                publish.unused_tag('owner/repo', 'existing')

    def run_fixture(self, identity):
        return {'id': identity, 'workflow_id': 7, 'head_branch': 'feature/test',
                'head_repository': {'full_name': 'owner/repo'}, 'head_sha': 'a' * 40,
                'event': 'workflow_dispatch', 'status': 'completed', 'conclusion': 'success',
                'html_url': f'https://github.com/owner/repo/actions/runs/{identity}'}

    def test_latest_selection_skips_runs_without_successful_signing(self):
        with patch.object(publish, 'api', return_value={'id': 7}), \
             patch.object(publish, 'pages', return_value=iter([self.run_fixture(3), self.run_fixture(2)])), \
             patch.object(publish, 'signed_job', side_effect=[False, True]):
            self.assertEqual(publish.choose_run('owner/repo', 'feature/test', '')['id'], 2)

    def test_explicit_run_on_another_branch_is_rejected(self):
        with patch.object(publish, 'api', side_effect=[{'id': 7}, self.run_fixture(3)]), \
             patch.object(publish, 'signed_job') as signed:
            with self.assertRaisesRegex(RuntimeError, 'Selected run'):
                publish.choose_run('owner/repo', 'main', '3')
            signed.assert_not_called()

    def publish_main(self, failed_upload=False, fast=False):
        env = {'GITHUB_REPOSITORY': 'owner/repo', 'RELEASE_BUILD_BRANCH': 'feature/test',
               'RELEASE_RUN_ID': '3', 'RELEASE_TYPE': 'prerelease', 'GITHUB_STEP_SUMMARY': ''}
        def call(*args):
            if failed_upload and args[:2] == ('release', 'upload'):
                raise subprocess.CalledProcessError(1, ['gh', *map(str, args)])
            return b''
        with patch.dict(os.environ, env), \
             patch.object(publish, 'choose_run', return_value=self.run_fixture(3)), \
             patch.object(publish, 'artifact', side_effect=self.fixture(fast=fast)), \
             patch.object(publish, 'unused_tag'), \
             patch.object(publish, 'release_notes', return_value=('NFS III ARMv7 TV — tv28', 'Changes.')), \
             patch.object(publish, 'gh', side_effect=call) as gh:
            if failed_upload:
                with self.assertRaises(subprocess.CalledProcessError):
                    publish.main()
            else:
                publish.main()
            return [call.args for call in gh.call_args_list]

    def test_publication_targets_build_commit_and_preserves_latest_for_prerelease(self):
        calls = self.publish_main()
        create, upload, edit = calls
        self.assertEqual(create[:3], ('release', 'create', 'armv7-v105-run3'))
        self.assertEqual(create[create.index('--target') + 1], 'a' * 40)
        self.assertIn('--draft', create)
        self.assertIn('--prerelease', create)
        self.assertIn('--latest=false', edit)
        self.assertIn('--draft=false', edit)
        self.assertTrue(any(str(p).endswith('SHA256SUMS.txt') for p in upload))

    def test_fast_publication_handles_absent_test_count(self):
        calls = self.publish_main(fast=True)
        self.assertEqual([c[1] for c in calls], ['create', 'upload', 'edit'])

    def test_failed_upload_leaves_draft_unpublished(self):
        calls = self.publish_main(failed_upload=True)
        self.assertEqual([c[1] for c in calls], ['create', 'upload'])

    def test_invalid_changelog_stops_before_creating_a_draft(self):
        env = {'GITHUB_REPOSITORY': 'owner/repo', 'RELEASE_BUILD_BRANCH': 'feature/test',
               'RELEASE_RUN_ID': '3', 'RELEASE_TYPE': 'release'}
        with patch.dict(os.environ, env), \
             patch.object(publish, 'choose_run', return_value=self.run_fixture(3)), \
             patch.object(publish, 'artifact', side_effect=self.fixture()), \
             patch.object(publish, 'unused_tag'), \
             patch.object(publish, 'release_notes', side_effect=RuntimeError('Missing changelog')), \
             patch.object(publish, 'gh') as gh:
            with self.assertRaisesRegex(RuntimeError, 'Missing changelog'):
                publish.main()
            gh.assert_not_called()


class ReleaseNotesTests(unittest.TestCase):
    changelog = """# Fork changes

## Unreleased build automation

Never include this automation work.

## tv29 — version 106

Future change.

## tv28 — version 105

Joakim reported testing build 28 without problems on 2026-11-01.

Improved settings backups and translated launcher wording.
Added translation maintenance guidance in TRANSLATIONS.md.

## tv27 — version 104

Updated SDL. Joakim reported testing the game without problems. Retained input routing.
The pre-existing host
trackVertices check discrepancy remains documented in WORKSPACE.md.

## tv26 — version 103 (test build)

Added a race pause shortcut.

## tv25 — version 102

Fixed the controller page header.

## tv24 — version 101

Older changes already released.
"""

    def sections(self):
        return publish.changelog_sections(self.changelog)

    def test_collects_full_range_and_omits_feedback_unreleased_future_and_baseline(self):
        notes = publish.changes_for_release(self.sections(), 28, 105, 24)
        for version in (25, 26, 27, 28):
            self.assertIn(f'### tv{version}', notes)
        for excluded in ('tv24', 'tv29', 'Joakim', 'Unreleased', 'automation work', 'Future change', 'TRANSLATIONS.md', 'WORKSPACE.md'):
            self.assertNotIn(excluded, notes)
        self.assertIn('Updated SDL. Retained input routing.', notes)

    def test_missing_intermediate_entry_and_wrong_code_stop_publication(self):
        sections = self.sections()
        del sections[26]
        with self.assertRaisesRegex(RuntimeError, 'tv26'):
            publish.changes_for_release(sections, 28, 105, 24)
        with self.assertRaisesRegex(RuntimeError, 'version/code'):
            publish.changes_for_release(self.sections(), 28, 999, 24)

    def test_missing_baseline_or_empty_changes_stop_publication(self):
        sections = self.sections()
        del sections[24]
        with self.assertRaisesRegex(RuntimeError, 'Previous release'):
            publish.changes_for_release(sections, 28, 105, 24)
        sections = self.sections()
        sections[28]['body'] = ''
        with self.assertRaisesRegex(RuntimeError, 'empty'):
            publish.changes_for_release(sections, 28, 105)

    def test_first_release_uses_only_current_version(self):
        notes = publish.changes_for_release(self.sections(), 28, 105)
        self.assertIn('### tv28', notes)
        self.assertNotIn('### tv27', notes)

    def test_duplicate_entries_are_rejected(self):
        with self.assertRaisesRegex(RuntimeError, 'Duplicate'):
            publish.changelog_sections(self.changelog + '\n## tv28 — version 105\nDuplicate.')

    def release(self, tv, prerelease=False):
        return {'draft': False, 'prerelease': prerelease, 'published_at': '2026-11-01',
                'tag_name': f'v0.78-tv{tv}', 'html_url': f'https://example.com/tv{tv}',
                'assets': [{'name': f'nfs3-0.78-armv7-tv{tv}-profile-release.apk'}]}

    def test_baseline_handles_legacy_tags_and_ignores_current_and_future_versions(self):
        releases = [self.release(30), self.release(28), self.release(24)]
        with patch.object(publish, 'pages', return_value=iter(releases)), \
             patch.object(publish, 'api', return_value={'status': 'ahead'}) as api:
            baseline = publish.previous_release('owner/repo', {'head_sha': 'a' * 40}, 28, 'release')
        self.assertEqual(baseline[0], 24)
        self.assertIn('v0.78-tv24...', api.call_args.args[0])

    def test_regular_release_includes_changes_since_previous_stable_not_prerelease(self):
        releases = [self.release(27, prerelease=True), self.release(24)]
        with patch.object(publish, 'pages', return_value=iter(releases)), \
             patch.object(publish, 'api', return_value={'status': 'ahead'}):
            self.assertEqual(publish.previous_release('o/r', {'head_sha': 'a' * 40}, 28, 'release')[0], 24)
        with patch.object(publish, 'pages', return_value=iter(releases)), \
             patch.object(publish, 'api', return_value={'status': 'ahead'}):
            self.assertEqual(publish.previous_release('o/r', {'head_sha': 'a' * 40}, 28, 'prerelease')[0], 27)

    def test_unrelated_source_history_is_rejected(self):
        with patch.object(publish, 'pages', return_value=iter([self.release(24)])), \
             patch.object(publish, 'api', return_value={'status': 'diverged'}):
            with self.assertRaisesRegex(RuntimeError, 'source history'):
                publish.previous_release('o/r', {'head_sha': 'a' * 40}, 28, 'release')

    def test_fetches_apk_source_and_renders_player_notes_with_collapsed_details(self):
        run = {'head_sha': 'a' * 40, 'html_url': 'https://example.com/build'}
        metadata = {'version': '0.78-armv7-tv28-profile', 'versionCode': 105, 'native_build_id': '1234'}
        with patch.object(publish, 'gh', return_value=self.changelog.encode()) as gh, \
             patch.object(publish, 'previous_release', return_value=(24, self.release(24))):
            title, body = publish.release_notes('o/r', run, metadata, 'release', 14)
        self.assertEqual(title, 'NFS III ARMv7 TV — tv28')
        self.assertIn('?ref=' + 'a' * 40, gh.call_args.args[1])
        self.assertIn('Accept: application/vnd.github.raw+json', gh.call_args.args)
        self.assertIn('### tv25', body)
        self.assertIn('<details>', body)
        self.assertNotIn('Device testing', body)
        self.assertNotIn('Joakim', body)
        self.assertLess(body.index('## Changes'), body.index('<details>'))

    def test_fast_release_notes_keep_changes_without_claiming_tests_passed(self):
        run = {'head_sha': 'a' * 40, 'html_url': 'https://example.com/build'}
        metadata = {'version': '0.78-armv7-tv28-profile', 'versionCode': 105, 'native_build_id': '1234'}
        with patch.object(publish, 'gh', return_value=self.changelog.encode()), \
             patch.object(publish, 'previous_release', return_value=(24, self.release(24))):
            title, normal = publish.release_notes('o/r', run, metadata, 'release', 14)
            fast_title, fast = publish.release_notes('o/r', run, metadata, 'release', None)
        self.assertEqual(title, fast_title)
        self.assertEqual(normal.split('<details>')[0], fast.split('<details>')[0])
        self.assertIn('[Build and automated checks](https://example.com/build)', fast)
        self.assertNotIn('tests passed', fast)
        self.assertNotIn('None', fast)

    def test_numeric_release_uses_legacy_baseline_and_numeric_title(self):
        source = self.changelog.replace('## tv29 — version 106', '## 0.78.29 — version 106')
        run = {'head_sha': 'a' * 40, 'html_url': 'https://example.com/build'}
        metadata = {'version': '0.78.29', 'versionCode': 106, 'native_build_id': '1234'}
        with patch.object(publish, 'gh', return_value=source.encode()), \
             patch.object(publish, 'previous_release', return_value=(28, self.release(28))):
            title, body = publish.release_notes('o/r', run, metadata, 'release', 14)
        self.assertEqual(title, '0.78.29')
        self.assertIn('### 0.78.29', body)
        self.assertNotIn('### tv28', body)
        self.assertIn('Changes since [tv28]', body)

    def test_numeric_baseline_is_recognized_for_later_release(self):
        numeric = self.release(29)
        numeric['assets'] = [{'name': 'nfs3-0.78.29-armv7.apk'}]
        with patch.object(publish, 'pages', return_value=iter([self.release(28), numeric])), \
             patch.object(publish, 'api', return_value={'status': 'ahead'}):
            self.assertEqual(publish.previous_release('o/r', {'head_sha': 'a' * 40}, 30, 'release')[0], 29)

    def test_same_revision_with_wrong_numeric_version_is_rejected(self):
        source = self.changelog.replace('## tv29 — version 106', '## 0.79.29 — version 106')
        metadata = {'version': '0.78.29', 'versionCode': 106, 'native_build_id': '1234'}
        with patch.object(publish, 'gh', return_value=source.encode()):
            with self.assertRaisesRegex(RuntimeError, 'APK version differs'):
                publish.release_notes('o/r', {'head_sha': 'a' * 40}, metadata, 'release', 14)


class ReleaseIdentityTests(unittest.TestCase):
    def test_filenames_and_revisions_support_numeric_and_historical_apks(self):
        for version in ['0.78.29', '0.78-armv7-tv28-profile', '0.78-armv7-tv24']:
            names = artifact_names(version)
            self.assertEqual(published_version(names['apk']), version)
            self.assertEqual(revision_of(version), 29 if version == '0.78.29' else 28 if 'tv28' in version else 24)
        self.assertIsNone(published_version('nfs3-0.78.29-arm64.apk'))
        with self.assertRaises(RuntimeError):
            artifact_names('../../bad')

    def test_release_manifest_rejects_inconsistent_version_revision_mapping(self):
        with tempfile.TemporaryDirectory() as temp:
            root = Path(temp)
            (root / 'tools').mkdir()
            path = root / 'tools/android-release.json'
            path.write_text(json.dumps({'versionName': '0.78.29', 'versionCode': 106, 'revision': 30}))
            with self.assertRaisesRegex(RuntimeError, 'mapping'):
                release_config(root)
            path.write_text(json.dumps({'versionName': '0.78.29', 'versionCode': 106, 'revision': 29}))
            self.assertEqual(release_config(root)['versionCode'], 106)


if __name__ == '__main__':
    unittest.main()

