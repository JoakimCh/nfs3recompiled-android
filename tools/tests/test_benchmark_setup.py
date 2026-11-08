"""Pinned downloads, safe extraction and preservation of existing demo data."""
import io
from pathlib import Path
import stat
import sys
import tempfile
import unittest
from unittest.mock import patch
import zipfile

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import setup_benchmark as setup


class BenchmarkSetupTest(unittest.TestCase):
    def setUp(self):
        self.directory = tempfile.TemporaryDirectory(prefix="nfs-benchmark-setup-")
        self.addCleanup(self.directory.cleanup)
        self.root = Path(self.directory.name)
        self.archive = self.root / "demo.zip"
        with zipfile.ZipFile(self.archive, "w") as archive:
            archive.writestr("gamedata/tracks/trk003/Tr03.frd", b"track")
            archive.writestr("gamedata/carmodel/Corv/car.viv", b"car")
            archive.writestr("fedata/config/", b"")
            archive.writestr("Setup/english/readme.txt", b"original readme")
            archive.writestr("Setup/english/license.txt", b"original notices")
            archive.writestr("setup.exe", b"never execute or extract")
        self.expected = setup.digest(self.archive)
        self.destination = self.root / "data"

    def test_unexpected_archive_rejected_before_creating_destination(self):
        with self.assertRaisesRegex(ValueError, "checksum mismatch"):
            setup.extract_or_verify(self.archive, self.destination)
        self.assertFalse(self.destination.exists())

    def test_only_data_and_notices_extracted_and_rerun_verified(self):
        with patch.object(setup, "DEMO_SHA256", self.expected):
            self.assertEqual(setup.extract_or_verify(self.archive, self.destination), "Prepared")
            self.assertEqual(setup.extract_or_verify(self.archive, self.destination), "Verified existing")
        self.assertTrue((self.destination / "fedata/config").is_dir())
        self.assertTrue((self.destination / "Setup/english/license.txt").is_file())
        self.assertFalse((self.destination / "setup.exe").exists())

    def test_changed_existing_data_is_not_overwritten(self):
        with patch.object(setup, "DEMO_SHA256", self.expected):
            setup.extract_or_verify(self.archive, self.destination)
            car = self.destination / "gamedata/carmodel/Corv/car.viv"
            car.write_bytes(b"user modifications")
            with self.assertRaisesRegex(ValueError, "Existing demo data differs"):
                setup.extract_or_verify(self.archive, self.destination)
            self.assertEqual(car.read_bytes(), b"user modifications")

    def test_unsafe_names_and_symlinks_rejected(self):
        for name in ("../outside", "/absolute", "C:/outside", "fedata/../../outside", "gamedata\\..\\outside"):
            with self.subTest(name=name):
                other = self.root / "unsafe.zip"
                with zipfile.ZipFile(other, "w") as archive:
                    archive.writestr(name, b"bad")
                with zipfile.ZipFile(other) as archive:
                    with self.assertRaisesRegex(ValueError, "Unsafe ZIP member"):
                        setup.selected_entries(archive)
        other = self.root / "symlink.zip"
        info = zipfile.ZipInfo("fedata/link")
        info.create_system = 3
        info.external_attr = (stat.S_IFLNK | 0o777) << 16
        with zipfile.ZipFile(other, "w") as archive:
            archive.writestr(info, "outside")
        with zipfile.ZipFile(other) as archive:
            with self.assertRaisesRegex(ValueError, "symlinks"):
                setup.selected_entries(archive)

    def test_existing_symlink_cannot_redirect_verification(self):
        with patch.object(setup, "DEMO_SHA256", self.expected):
            setup.extract_or_verify(self.archive, self.destination)
            car = self.destination / "gamedata/carmodel/Corv/car.viv"
            outside = self.root / "outside"
            outside.write_bytes(b"car")
            car.unlink()
            car.symlink_to(outside)
            with self.assertRaisesRegex(ValueError, "Symlink"):
                setup.extract_or_verify(self.archive, self.destination)
            self.assertEqual(outside.read_bytes(), b"car")

    def test_download_checksum_failure_leaves_no_cache_or_partial(self):
        response = io.BytesIO(b"wrong archive")
        response.geturl = lambda: setup.DEMO_URL
        destination = self.root / "cache/demo.zip"
        with patch.object(setup, "urlopen", return_value=response):
            with self.assertRaisesRegex(ValueError, "checksum mismatch"):
                setup.download(setup.DEMO_URL, destination)
        self.assertFalse(destination.exists())
        self.assertEqual(list(destination.parent.iterdir()), [])

    def test_download_accepts_only_the_pinned_bytes(self):
        response = io.BytesIO(self.archive.read_bytes())
        response.geturl = lambda: setup.DEMO_URL
        destination = self.root / "cache/demo.zip"
        with patch.object(setup, "DEMO_SHA256", self.expected), patch.object(setup, "urlopen", return_value=response):
            setup.download(setup.DEMO_URL, destination)
        self.assertEqual(setup.digest(destination), self.expected)


if __name__ == "__main__":
    unittest.main()
