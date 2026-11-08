"""Replay preflight bounds, persistent IDs and output preservation."""
from pathlib import Path
import struct
import sys
import tempfile
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from benchmark_replay_info import inspect_replay, inspect_assets, bigf_entries, REPLAY_BYTES


class BenchmarkReplayTest(unittest.TestCase):
    def setUp(self):
        self.directory = tempfile.TemporaryDirectory(prefix="nfs-replay-info-")
        self.addCleanup(self.directory.cleanup)
        self.root = Path(self.directory.name)
        self.path = self.root / "race.rp3"
        self.data = bytearray(REPLAY_BYTES)
        for offset, value in ((0, 0x20f0), (0x1860, 2), (0x196c, 3),
                              (0x1974, 2), (0x19d0, 1), (0x1990, 2)):
            struct.pack_into("<I", self.data, offset, value)
        self.car_id = struct.pack("<4I", 19, 0, 0, 0)
        for offset in (0x1780, 0x17ec, 0x19ec):
            self.data[offset:offset + 16] = self.car_id
        struct.pack_into("<I", self.data, 0x1a00, 37)

    def write_replay(self):
        self.path.write_bytes(self.data)
        return inspect_replay(self.path)

    def test_truncated_file_rejected_before_reading_fields(self):
        self.path.write_bytes(self.data[:100])
        with self.assertRaisesRegex(ValueError, "shorter"):
            inspect_replay(self.path)

    def test_unknown_version_rejected(self):
        struct.pack_into("<I", self.data, 0x1860, 3)
        with self.assertRaisesRegex(ValueError, "version"):
            self.write_replay()

    def test_roster_cannot_run_beyond_settings_image(self):
        struct.pack_into("<I", self.data, 0x19d0, 0xffffffff)
        with self.assertRaisesRegex(ValueError, "Car count"):
            self.write_replay()

    def test_invalid_player_index_rejected(self):
        struct.pack_into("<I", self.data, 0x19b4, 1)
        with self.assertRaisesRegex(ValueError, "Player index"):
            self.write_replay()

    def test_metadata_inspection_preserves_original(self):
        report = self.write_replay()
        self.assertEqual(self.path.read_bytes(), self.data)
        self.assertEqual(report["cars"][0]["car_id"], self.car_id.hex())
        self.assertEqual(report["cars"][0]["saved_car_index"], 37)
        self.assertFalse(report["runtime_validated"])

    def test_asset_lookup_uses_id_instead_of_saved_list_index(self):
        report = self.write_replay()
        fec = bytearray(0x28)
        struct.pack_into("<H", fec, 4, 9)
        fec[0x18:0x28] = self.car_id
        name = b"fedata.eng\0"
        end = 16 + 8 + len(name)
        archive = b"BIGF" + struct.pack(">III", end + len(fec), 1, end)
        archive += struct.pack(">II", end, len(fec)) + name + fec
        folder = self.root / "GameData" / "CarModel" / "Corv"
        folder.mkdir(parents=True)
        (folder / "Car.VIV").write_bytes(archive)
        assets = inspect_assets(self.root, report)
        self.assertEqual(assets["unresolved_car_ids"], [])
        self.assertIn(self.car_id.hex(), assets["matched_models"])
        self.assertTrue(assets["missing_core_scene_assets"])
        self.assertFalse(assets["core_scene_dependencies_found"])

    def test_bigf_out_of_bounds_data_rejected(self):
        self.path.write_bytes(b"BIGF" + struct.pack(">III", 26, 1, 26)
                              + struct.pack(">II", 26, 100) + b"x\0")
        with self.assertRaisesRegex(ValueError, "entry"):
            bigf_entries(self.path)


if __name__ == "__main__":
    unittest.main()
