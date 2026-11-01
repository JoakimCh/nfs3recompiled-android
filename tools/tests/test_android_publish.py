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


def archive(files):
    data = io.BytesIO()
    with zipfile.ZipFile(data, 'w') as zipped:
        for name, value in files.items():
            zipped.writestr(name, json.dumps(value) if isinstance(value, dict) else value)
    return zipfile.ZipFile(io.BytesIO(data.getvalue()))


class ReleasePromotionTests(unittest.TestCase):
    def fixture(self, wrong_hash=False, wrong_symbols=False, failed_tests=False):
        metadata = {
            'version': 'test', 'versionCode': 105, 'apk': 'nfs3-test-release.apk',
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
        symbol_metadata = dict(metadata, native_build_id='other') if wrong_symbols else metadata
        with archive({'metadata/release.json': symbol_metadata,
                      'armeabi-v7a/libmain.so': b'symbols'}) as symbols:
            symbols_bytes = symbols.fp.getvalue()
        artifacts = [archive({'nfs3-test-release.json': metadata, 'nfs3-test-release.apk': b'apk',
                              'validation.json': validation}),
                     archive({'nfs3-test-symbols.zip': symbols_bytes})]
        for artifact in artifacts:
            self.addCleanup(artifact.close)
        return artifacts

    def test_preserves_exact_files(self):
        with tempfile.TemporaryDirectory() as temp, patch.object(publish, 'artifact', side_effect=self.fixture()):
            result = publish.prepare('owner/repo', {'head_sha': 'a' * 40}, Path(temp))
            self.assertEqual((Path(temp) / result['apk']).read_bytes(), b'apk')
            self.assertEqual(len(list(Path(temp).iterdir())), 4)

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

    def publish_main(self, failed_upload=False):
        env = {'GITHUB_REPOSITORY': 'owner/repo', 'RELEASE_BUILD_BRANCH': 'feature/test',
               'RELEASE_RUN_ID': '3', 'RELEASE_TYPE': 'prerelease', 'GITHUB_STEP_SUMMARY': ''}
        def call(*args):
            if failed_upload and args[:2] == ('release', 'upload'):
                raise subprocess.CalledProcessError(1, ['gh', *map(str, args)])
            return b''
        with patch.dict(os.environ, env), \
             patch.object(publish, 'choose_run', return_value=self.run_fixture(3)), \
             patch.object(publish, 'artifact', side_effect=self.fixture()), \
             patch.object(publish, 'unused_tag'), \
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

    def test_failed_upload_leaves_draft_unpublished(self):
        calls = self.publish_main(failed_upload=True)
        self.assertEqual([c[1] for c in calls], ['create', 'upload'])


if __name__ == '__main__':
    unittest.main()
