"""Filesystem regressions for setup; no downloads, SDK or Java required."""
from pathlib import Path
import sys
import tempfile
import unittest
import zipfile

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import setup_android


class AndroidSetupTest(unittest.TestCase):
    def test_repairs_nested_sdk_without_replacing_package_metadata(self):
        with tempfile.TemporaryDirectory() as directory:
            package = Path(directory) / '37.0.0'
            nested = package / 'android-37.0'
            nested.mkdir(parents=True)
            (nested / 'source.properties').write_text('Pkg.Revision=37.0.0\n')
            (nested / 'aapt2').write_bytes(b'tool')
            (package / 'package.xml').write_text('preserve installer metadata')
            setup_android.repair_sdk(package)
            self.assertEqual((package / 'aapt2').read_bytes(), b'tool')
            self.assertEqual((package / 'package.xml').read_text(), 'preserve installer metadata')
            self.assertFalse(nested.exists())

    def test_sdk_repair_refuses_to_overwrite_an_existing_tool(self):
        with tempfile.TemporaryDirectory() as directory:
            package = Path(directory)
            nested = package / 'android-37.0'
            nested.mkdir()
            (nested / 'source.properties').write_text('Pkg.Revision=37.0.0\n')
            (nested / 'aapt2').write_bytes(b'new')
            (package / 'aapt2').write_bytes(b'existing')
            with self.assertRaises(RuntimeError):
                setup_android.repair_sdk(package)
            self.assertEqual((package / 'aapt2').read_bytes(), b'existing')
            self.assertTrue((nested / 'source.properties').exists())

    def test_archive_cannot_write_outside_its_install_directory(self):
        with tempfile.TemporaryDirectory() as directory:
            cache = Path(directory)
            archive = cache / 'tool.zip'
            with zipfile.ZipFile(archive, 'w') as bundle:
                bundle.writestr('../escaped', 'unexpected')
            with self.assertRaises(RuntimeError):
                setup_android.unpack(archive, cache / 'installed', cache)
            self.assertFalse((cache / 'escaped').exists())
            self.assertFalse((cache / 'installed').exists())


if __name__ == '__main__':
    unittest.main()
