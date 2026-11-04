"""Native collector isolation: FPS must work while the detailed mutex is held."""
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


@unittest.skipUnless(sys.platform.startswith('linux') and shutil.which('c++'),
                     'Native collector checks require a Linux C++17 host compiler')
class PerfStatsTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.work = tempfile.TemporaryDirectory(prefix='nfs3-perfstats-')
        cls.binary = Path(cls.work.name) / 'check'
        try:
            subprocess.run(['c++', '-pipe', '-std=c++17', '-O2', '-pthread',
                            '-I' + str(ROOT / 'include'),
                            str(ROOT / 'tools/game_checks/perfstats/check.cpp'),
                            '-o', str(cls.binary)], check=True, capture_output=True, text=True)
        except Exception:
            cls.work.cleanup()
            raise

    @classmethod
    def tearDownClass(cls):
        cls.work.cleanup()

    def check_level(self, detailed, fps, expected):
        env = dict(os.environ, NFS_PERF_STATS=str(detailed), NFS_FPS_COUNTER=str(fps))
        result = subprocess.run([str(self.binary), expected], env=env, check=True,
                                capture_output=True, text=True, timeout=10)
        self.assertEqual(result.stdout.strip(), 'PASS ' + expected)

    def test_disabled_does_not_collect_or_lock(self):
        self.check_level(0, 0, 'disabled')

    def test_fps_counts_frames_without_detailed_work_or_locks(self):
        self.check_level(0, 1, 'fps')

    def test_verbose_collects_intervals_and_respects_pause(self):
        self.check_level(1, 0, 'detailed')

    def test_detailed_takes_precedence_over_fps_flag(self):
        self.check_level(1, 1, 'detailed')
