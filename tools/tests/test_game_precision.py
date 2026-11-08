"""Exercise arithmetic selection and independent integer-conversion semantics."""
import os
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]

@unittest.skipUnless(shutil.which('c++'), 'Requires host C++ compiler')
class GamePrecisionTest(unittest.TestCase):
    def test_both_arithmetic_modes_preserve_integer_conversions(self):
        with tempfile.TemporaryDirectory(prefix='nfs-precision-') as directory:
            for single in (0, 1):
                with self.subTest(single=single):
                    binary = str(Path(directory) / ('check-' + str(single)))
                    subprocess.run(['c++', '-pipe', '-std=c++17', '-O2', '-ffp-contract=off',
                                    '-DNFS_GAME_SINGLE_PRECISION=' + str(single),
                                    '-I' + str(ROOT / 'include'),
                                    str(ROOT / 'tools/game_checks/precision/check.cpp'),
                                    '-o', binary], check=True, capture_output=True, text=True)
                    subprocess.run([binary], check=True)
