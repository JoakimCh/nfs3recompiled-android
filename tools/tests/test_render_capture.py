"""Exercise production GL with independent tiny scenes, without game assets.

Set NFS_RENDER_REPLAY_BINARY to a built nfs_render_replay executable.
"""
import json
import os
from pathlib import Path
import struct
import subprocess
import tempfile
import unittest


def words(*values):
    return struct.pack("<" + "I" * len(values), *values)


def blob(value):
    return words(len(value)) + value


def texture(index=0, size=1, levels=1, pixels=b"\xff\xff", fresh=1):
    return words(index, size, levels, 0, fresh) + blob(pixels)


def clear(color, x=0, y=0, xx=4, yy=4):
    return words(1, color, x, y, xx, yy)


def quad(color, opaque=True, levels=1):
    points = ((0, 0), (4, 0), (4, 4), (0, 0), (4, 4), (0, 4))
    vertices = b"".join(struct.pack("<3fI3f4B", x, y, 0, color, 0, 0, 1, 1, 1, 0, 0)
                        for x, y in points)
    flags = 32 | (256 if opaque else 0)  # alpha blending, optional proven opacity
    batch = words(6, 0, levels, 1, flags, 0, 0, 0, 4, 4) + struct.pack("<fI", 1, 0)
    return (words(2, 6) + vertices + words(1) + batch + words(1) + bytes(64 * 4)
            + struct.pack("<4f3I", 0, 0, 0, 0, 0, 4, 4))


def capture(commands, reference, textures=None):
    if textures is None:
        textures = [texture()]
    return (b"NFRCP001" + words(4, 4, 0) + blob(b"independent regression scene")
            + words(len(textures)) + b"".join(textures) + words(len(commands))
            + b"".join(commands) + blob(reference))


@unittest.skipUnless(os.environ.get("NFS_RENDER_REPLAY_BINARY"), "Requires explicit NFS_RENDER_REPLAY_BINARY")
class RenderCaptureTest(unittest.TestCase):
    def setUp(self):
        self.directory = tempfile.TemporaryDirectory(prefix="nfs-render-capture-")
        self.addCleanup(self.directory.cleanup)
        self.root = Path(self.directory.name)
        self.binary = Path(os.environ["NFS_RENDER_REPLAY_BINARY"]).resolve()
        self.env = dict(os.environ, SDL_VIDEO_DRIVER="offscreen")

    def run_scene(self, data, name="result", shader="auto", success=True):
        source = self.root / (name + ".nfrc")
        source.write_bytes(data)
        prefix = self.root / name
        result = subprocess.run([str(self.binary), "--capture", str(source), "--output-prefix", str(prefix),
                                 "--warmup", "1", "--iterations", "3", "--shader", shader],
                                env=self.env, capture_output=True, text=True, timeout=30)
        if success:
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
            report = json.loads(prefix.with_suffix(".json").read_text())
            self.assertEqual(report["rgba_mismatch_bytes"], 0, result.stdout)
            return report
        self.assertNotEqual(result.returncode, 0)
        self.assertFalse(prefix.with_suffix(".json").exists())
        return result

    def test_opaque_quad_matches_independently_expected_red_in_both_shader_paths(self):
        frame = capture([clear(0), quad(0xff0000ff)], bytes((255, 0, 0, 255)) * 16)
        self.run_scene(frame, "auto")
        self.run_scene(frame, "general", shader="general")

    def test_transparent_blue_over_red(self):
        frame = capture([clear(0), quad(0xff0000ff), quad(0x80ff0000, opaque=False)],
                        bytes((127, 0, 128, 128)) * 16)
        self.run_scene(frame)

    def test_texture_updates_are_repeatable_after_initial_state_restore(self):
        commands = [clear(0), words(3) + texture(pixels=b"\xe0\x07", fresh=0), quad(0xffffffff)]
        self.run_scene(capture(commands, bytes((0, 255, 0, 255)) * 16))

    def test_release_and_reallocation_with_mipmaps(self):
        green = b"\xe0\x07" * 5  # 2x2 plus 1x1
        commands = [clear(0), words(4, 1, 0), words(3) + texture(size=2, levels=2, pixels=green),
                    quad(0xffffffff, levels=2)]
        self.run_scene(capture(commands, bytes((0, 255, 0, 255)) * 16))

    def test_partial_clear_keeps_other_pixels(self):
        row = bytes((0, 0, 255, 0)) * 2 + bytes((255, 0, 0, 255)) * 2
        self.run_scene(capture([clear(0), quad(0xff0000ff), clear(0xff, xx=2)], row * 4))

    def test_truncated_and_wrong_version_files_fail_before_rendering(self):
        frame = capture([clear(0), quad(0xff0000ff)], bytes((255, 0, 0, 255)) * 16)
        self.run_scene(frame[:-1], "truncated", success=False)
        self.run_scene(b"BADMAGIC" + frame[8:], "wrong-version", success=False)

    def test_missing_texture_and_missing_full_clear_are_rejected(self):
        reference = bytes((255, 0, 0, 255)) * 16
        self.run_scene(capture([clear(0), quad(0xff0000ff)], reference, textures=[]), "missing-texture", success=False)
        self.run_scene(capture([quad(0xff0000ff)], reference), "missing-clear", success=False)

    def test_existing_outputs_are_not_overwritten(self):
        frame = capture([clear(0), quad(0xff0000ff)], bytes((255, 0, 0, 255)) * 16)
        self.run_scene(frame)
        saved = (self.root / "result.json").read_bytes()
        source = self.root / "result.nfrc"
        result = subprocess.run([str(self.binary), "--capture", str(source), "--output-prefix", str(self.root / "result")],
                                env=self.env, capture_output=True, text=True, timeout=10)
        self.assertNotEqual(result.returncode, 0)
        self.assertEqual((self.root / "result.json").read_bytes(), saved)


if __name__ == "__main__":
    unittest.main()
