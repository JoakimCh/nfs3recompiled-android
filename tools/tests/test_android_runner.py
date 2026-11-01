"""Runner routing regressions; no SDK, downloads or builds required."""
import json
from pathlib import Path
from types import SimpleNamespace
import sys
import tempfile
import unittest
from unittest import mock

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import android


class AndroidRunnerTest(unittest.TestCase):
    def test_modes_run_the_expected_tests_build_and_signing(self):
        for mode, unsigned, task in (
            ('tests', False, None),
            ('check', False, ':app:buildCMakeRelWithDebInfo[armeabi-v7a]'),
            ('apk', True, ':app:assembleRelease'),
            ('apk-fast', True, ':app:assembleRelease'),
            ('apk', False, ':app:assembleRelease'),
            ('apk-fast', False, ':app:assembleRelease'),
        ):
            with self.subTest(mode=mode, unsigned=unsigned), tempfile.TemporaryDirectory() as directory:
                argv = ['android.py', mode, '--output-dir', directory]
                if unsigned:
                    argv.append('--unsigned')
                elif mode in ('apk', 'apk-fast'):
                    argv += ['--keystore', directory + '/key', '--password-file', directory + '/password']
                env = {'ANDROID_HOME': directory}
                results = {'tests': 14, 'failures': 0, 'errors': 0, 'skipped': 0}
                with mock.patch.object(sys, 'argv', argv), \
                     mock.patch.object(android.setup, 'prepare', return_value=(env, [])), \
                     mock.patch.object(android.setup, 'runtime', return_value=(env, None, None)), \
                     mock.patch.object(android, 'signing_files'), \
                     mock.patch.object(android, 'verify_signing') as verify, \
                     mock.patch.object(android, 'tests', return_value=results) as tests, \
                     mock.patch.object(android, 'gradle') as gradle, \
                     mock.patch.object(android, 'report') as report, \
                     mock.patch.object(android.subprocess, 'run') as run:
                    android.main()
                self.assertEqual(tests.call_count, 0 if mode == 'apk-fast' else 1)
                self.assertEqual(report.call_args.args[1], None if mode == 'apk-fast' else results)
                self.assertEqual(gradle.call_count, int(task is not None))
                if task:
                    self.assertEqual(gradle.call_args.args[0], [task])
                apk = mode in ('apk', 'apk-fast')
                self.assertEqual(verify.call_count, int(apk and not unsigned))
                commands = [call.args[0] for call in run.call_args_list]
                self.assertEqual(sum(any('check_apk_resources.py' in str(arg) for arg in cmd) for cmd in commands), int(apk))
                self.assertEqual(sum(any('sign_android.py' in str(arg) for arg in cmd) for cmd in commands), int(apk and not unsigned))

    def test_fast_report_marks_tests_as_not_run_and_keeps_apk_verification(self):
        with tempfile.TemporaryDirectory() as directory:
            output = Path(directory)
            (output / 'apk-resource-check.json').write_text('{"passed": true}')
            args = SimpleNamespace(mode='apk-fast', output_dir=output)
            with mock.patch.object(android.setup, 'output', side_effect=['source-sha', '']), \
                 mock.patch.object(android.setup, 'digest', return_value='apk-digest'):
                android.report(args, None)
            data = json.loads((output / 'validation.json').read_text())
            self.assertEqual(data['mode'], 'apk-fast')
            self.assertIsNone(data['tests'])
            self.assertTrue(data['native_compiled'])
            self.assertTrue(data['resource_check']['passed'])
            self.assertEqual(data['apk_sha256'], 'apk-digest')


if __name__ == '__main__':
    unittest.main()
