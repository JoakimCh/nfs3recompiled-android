"""Image tolerances and comparable-workload performance summaries."""
from copy import deepcopy
import json
import hashlib
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
from render_image_compare import compare_pixels, read_ppm, write_ppm
from renderer_capture_benchmark import performance_comparison


class RenderImageCompareTest(unittest.TestCase):
    def test_exact_match_has_no_error_and_black_difference(self):
        image = bytes((10, 20, 30)) * 4
        result, heatmap = compare_pixels(image, image, 2, 2)
        self.assertTrue(result["passed"])
        self.assertTrue(result["exact"])
        self.assertEqual(result["rmse"], 0)
        self.assertIsNone(result["psnr_db"])
        self.assertEqual(heatmap, bytes(12))

    def test_small_rounding_changes_are_visible_but_can_be_allowed(self):
        original, changed = bytes((100, 100, 100)) * 4, bytes((101, 100, 99)) * 4
        strict, _ = compare_pixels(original, changed, 2, 2)
        tolerant, _ = compare_pixels(original, changed, 2, 2, channel_tolerance=1)
        self.assertFalse(strict["passed"])
        self.assertTrue(tolerant["passed"])
        self.assertFalse(tolerant["exact"])
        self.assertEqual(tolerant["different_fraction"], 1)
        self.assertEqual(tolerant["max_channel_error"], 1)

    def test_fraction_budget_counts_pixels_not_channels(self):
        original, changed = bytes(12), bytes((30, 50, 60)) + bytes(9)
        passed, heatmap = compare_pixels(original, changed, 2, 2, max_changed_fraction=0.25)
        failed, _ = compare_pixels(original, changed, 2, 2, max_changed_fraction=0.24)
        self.assertTrue(passed["passed"])
        self.assertFalse(failed["passed"])
        self.assertEqual(passed["different_pixels"], 1)
        self.assertEqual(passed["max_channel_error"], 60)
        self.assertEqual(heatmap[:3], bytes((255, 255, 255)))

    def test_bad_lengths_and_nonfinite_tolerance_are_rejected(self):
        with self.assertRaises(ValueError):
            compare_pixels(bytes(3), bytes(6), 1, 1)
        with self.assertRaises(ValueError):
            compare_pixels(bytes(3), bytes(3), 1, 1, max_changed_fraction=float("nan"))

    def test_ppm_does_not_swallow_whitespace_valued_pixels(self):
        with tempfile.TemporaryDirectory() as folder:
            path = Path(folder) / "image.ppm"
            pixels = b"\n #"
            path.write_bytes(b"P6\n# example\n1 1\n255\n" + pixels)
            self.assertEqual(read_ppm(path), (1, 1, pixels))

    def test_cli_writes_review_artifacts_and_fails_an_injected_change(self):
        with tempfile.TemporaryDirectory() as folder:
            root = Path(folder)
            write_ppm(root / "reference.ppm", 2, 2, bytes(12))
            write_ppm(root / "candidate.ppm", 2, 2, bytes((10, 0, 0)) + bytes(9))
            result = subprocess.run([sys.executable, str(TOOLS / "render_image_compare.py"),
                                     "--reference", str(root / "reference.ppm"),
                                     "--candidate", str(root / "candidate.ppm"),
                                     "--output-dir", str(root / "comparison")], capture_output=True, text=True)
            self.assertEqual(result.returncode, 1)
            report = json.loads((root / "comparison/comparison.json").read_text())
            self.assertFalse(report["passed"])
            self.assertEqual(report["different_pixels"], 1)
            self.assertTrue((root / "comparison/difference.ppm").is_file())


class RenderPerformanceComparisonTest(unittest.TestCase):
    def setUp(self):
        self.before = {"correctness": {"passed": True}, "timing": {
            "gl_renderer": "device", "gl_version": "version", "width": 10, "height": 10, "mean_completed_ms": 4}}
        self.after = deepcopy(self.before)
        self.after["timing"]["mean_completed_ms"] = 2
        self.options = {"warmup": 10, "iterations": 50, "video_driver": "offscreen", "driver_environment": {}}

    def test_same_workload_reports_speedup(self):
        result = performance_comparison(self.before, self.after, self.options, self.options)
        self.assertTrue(result["valid"])
        self.assertEqual(result["speedup"], 2)
        self.assertEqual(result["completed_time_change_percent"], -50)

    def test_visual_failure_cannot_be_presented_as_a_speedup(self):
        self.after["correctness"]["passed"] = False
        self.assertFalse(performance_comparison(self.before, self.after, self.options, self.options)["valid"])

    def test_different_device_or_sampling_is_not_comparable(self):
        self.after["timing"]["gl_renderer"] = "another device"
        self.assertFalse(performance_comparison(self.before, self.after, self.options, self.options)["valid"])
        self.after["timing"]["gl_renderer"] = "device"
        changed = dict(self.options, iterations=5)
        self.assertFalse(performance_comparison(self.before, self.after, self.options, changed)["valid"])


class RenderCorpusPreflightTest(unittest.TestCase):
    def test_changed_capture_is_rejected_before_launch_or_output(self):
        with tempfile.TemporaryDirectory() as folder:
            root = Path(folder)
            (root / "frame-0.nfrc").write_bytes(b"changed")
            (root / "capture-manifest.json").write_text(json.dumps({"frames": ["frame-0.nfrc"],
                "files": {"frame-0.nfrc": {"bytes": 3, "sha256": "wrong"}}}))
            result = subprocess.run([sys.executable, str(TOOLS / "renderer_capture_benchmark.py"),
                                     "--binary", sys.executable, "--captures", str(root),
                                     "--output-dir", str(root / "results")], capture_output=True, text=True)
            self.assertEqual(result.returncode, 1)
            self.assertIn("changed since recording", result.stderr)
            self.assertFalse((root / "results").exists())

    def test_baseline_from_another_corpus_is_rejected(self):
        with tempfile.TemporaryDirectory() as folder:
            root = Path(folder)
            data = b"not executed"
            (root / "frame-0.nfrc").write_bytes(data)
            identities = {"frame-0.nfrc": {"bytes": len(data), "sha256": hashlib.sha256(data).hexdigest()}}
            (root / "capture-manifest.json").write_text(json.dumps({"frames": ["frame-0.nfrc"], "files": identities}))
            (root / "summary.json").write_text(json.dumps({"captures": {"other corpus": {}}}))
            result = subprocess.run([sys.executable, str(TOOLS / "renderer_capture_benchmark.py"),
                                     "--binary", sys.executable, "--captures", str(root),
                                     "--baseline-dir", str(root), "--output-dir", str(root / "results")], capture_output=True, text=True)
            self.assertEqual(result.returncode, 1)
            self.assertIn("exactly the same capture", result.stderr)
            self.assertFalse((root / "results").exists())


if __name__ == "__main__":
    unittest.main()
