#!/usr/bin/env python3
"""Benchmark a fixed capture corpus and gate image changes with explicit tolerances.

Use --baseline-dir to compare timings against an earlier run of this same corpus.
This never regenerates reference images or accepts new baselines automatically.
"""
import argparse
import json
import math
import os
from pathlib import Path
import subprocess
import sys

from benchmark_replay_info import file_identity
from renderer_benchmark import positive, nonnegative, ROOT
from render_image_compare import compare_images


def performance_comparison(baseline, current, previous_options, options):
    if not baseline["correctness"]["passed"] or not current["correctness"]["passed"]:
        return {"valid": False, "reason": "A run failed image correctness"}
    for key in ("gl_renderer", "gl_version", "width", "height"):
        if not baseline["timing"].get(key) or not current["timing"].get(key):
            return {"valid": False, "reason": f"Missing {key}"}
        if baseline["timing"].get(key) != current["timing"].get(key):
            return {"valid": False, "reason": f"Different {key}"}
    for key in ("warmup", "iterations", "video_driver", "driver_environment"):
        if previous_options.get(key) != options.get(key):
            return {"valid": False, "reason": f"Different sampling/environment option: {key}"}
    before = baseline["timing"]["mean_completed_ms"]
    after = current["timing"]["mean_completed_ms"]
    if not before > 0 or not after > 0:
        return {"valid": False, "reason": "Invalid timing values"}
    return {"valid": True, "speedup": before / after, "completed_time_change_percent": (after / before - 1) * 100}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--binary", type=Path, required=True)
    parser.add_argument("--captures", type=Path, required=True, help="Directory made by --capture-frames")
    parser.add_argument("--output-dir", type=Path, required=True, help="New output directory")
    parser.add_argument("--baseline-dir", type=Path)
    parser.add_argument("--warmup", type=nonnegative, default=10)
    parser.add_argument("--iterations", type=positive, default=50)
    parser.add_argument("--shader", choices=("auto", "general"), default="auto")
    parser.add_argument("--video-driver", default="offscreen")
    parser.add_argument("--timeout", type=positive, default=120, help="Seconds per frame replay process")
    parser.add_argument("--channel-tolerance", type=int, default=0)
    parser.add_argument("--max-changed-fraction", type=float, default=0)
    args = parser.parse_args()
    try:
        if not 0 <= args.channel_tolerance <= 255 or not math.isfinite(args.max_changed_fraction) or not 0 <= args.max_changed_fraction <= 1:
            raise ValueError("Invalid correctness tolerances")
        if args.iterations > 100000 or args.warmup > 100000:
            raise ValueError("Warmup/iteration counts must not exceed 100000")
        binary, captures, output = (path.resolve() for path in (args.binary, args.captures, args.output_dir))
        if not binary.is_file() or not os.access(binary, os.X_OK):
            raise ValueError("Pass a built nfs_render_replay executable")
        manifest = json.loads((captures / "capture-manifest.json").read_text())
        names = manifest.get("frames", [])
        if not 1 <= len(names) <= 100 or len(set(names)) != len(names):
            raise ValueError("Invalid capture list")
        identities = {}
        for name in names:
            if Path(name).name != name or not name.endswith(".nfrc"):
                raise ValueError("Invalid capture filename")
            identities[name] = file_identity(captures / name)
            if identities[name] != manifest.get("files", {}).get(name):
                raise ValueError(f"Capture changed since recording: {name}")
        baseline = json.loads((args.baseline_dir / "summary.json").read_text()) if args.baseline_dir else None
        if baseline and baseline.get("captures") != identities:
            raise ValueError("Baseline and candidate must use exactly the same capture files")
        if output.exists():
            raise ValueError("Output directory exists; choose a new one")
        output.mkdir(parents=True)
        env = {key: value for key, value in os.environ.items() if not key.startswith("NFS_")}
        env["SDL_VIDEO_DRIVER"] = args.video_driver
        options = {key: getattr(args, key) for key in ("warmup", "iterations", "shader", "video_driver")}
        options["driver_environment"] = {key: env.get(key) for key in (
            "LP_NUM_THREADS", "LIBGL_ALWAYS_SOFTWARE", "MESA_LOADER_DRIVER_OVERRIDE", "GALLIUM_DRIVER",
            "MESA_NO_ERROR", "MESA_SHADER_CACHE_DISABLE", "EGL_PLATFORM")}
        summary = {"schema": 1, "workload": "fixed-render-commands", "binary": file_identity(binary),
                   "captures": identities, "options": options, "frames": [], "passed": True,
                   "policy": {"channels": "RGB", "channel_tolerance": args.channel_tolerance,
                              "max_changed_fraction": args.max_changed_fraction}}
        summary["source_commit"] = subprocess.run(["git", "rev-parse", "HEAD"], cwd=ROOT, text=True, capture_output=True).stdout.strip()
        summary["source_dirty"] = bool(subprocess.run(["git", "status", "--porcelain"], cwd=ROOT, text=True, capture_output=True).stdout)
        # Finish all timed processes before doing CPU-heavy image comparisons.
        for name in names:
            stem = Path(name).stem
            with (output / (stem + ".log")).open("w") as log:
                try:
                    run = subprocess.run([str(binary), "--capture", str(captures / name),
                                          "--output-prefix", str(output / stem), "--warmup", str(args.warmup),
                                          "--iterations", str(args.iterations), "--shader", args.shader],
                                         env=env, stdout=log, stderr=subprocess.STDOUT, timeout=args.timeout)
                    if run.returncode:
                        raise ValueError(f"Replay exited {run.returncode}")
                    timing = json.loads((output / (stem + ".json")).read_text())
                    if (timing.get("iterations") != args.iterations or timing.get("warmup") != args.warmup
                            or timing.get("shader") != args.shader or timing.get("workload") != "fixed-render-commands"
                            or len(timing.get("completed_ms", [])) != args.iterations
                            or not all(math.isfinite(value) and value > 0 for value in timing["completed_ms"])):
                        raise ValueError("Incomplete renderer timing report")
                    summary["frames"].append({"capture": name, "timing": timing})
                except (OSError, ValueError, subprocess.TimeoutExpired) as error:
                    summary["frames"].append({"capture": name, "error": str(error)})
                    summary["passed"] = False
        previous = {frame["capture"]: frame for frame in baseline["frames"]} if baseline else {}
        speedups = []
        for frame in summary["frames"]:
            if "error" in frame:
                print(f"FAIL {frame['capture']}: {frame['error']}")
                continue
            stem = Path(frame["capture"]).stem
            try:
                frame["correctness"] = compare_images(output / (stem + ".reference.ppm"), output / (stem + ".candidate.ppm"),
                                                      output / (stem + ".difference.ppm"),
                                                      channel_tolerance=args.channel_tolerance,
                                                      max_changed_fraction=args.max_changed_fraction)
                summary["passed"] &= frame["correctness"]["passed"]
                detail = ""
                if baseline:
                    old = previous.get(frame["capture"])
                    if old and "correctness" in old:
                        comparison = performance_comparison(old, frame, baseline["options"], options)
                    else:
                        comparison = {"valid": False, "reason": "No successful baseline frame"}
                    frame["performance_comparison"] = comparison
                    if comparison["valid"]:
                        speedups.append(comparison["speedup"])
                        detail = f", {comparison['completed_time_change_percent']:+.1f}% completion time vs baseline"
                    else:
                        detail = f", timing comparison unavailable: {comparison['reason']}"
                c = frame["correctness"]
                print(f"{'PASS' if c['passed'] else 'FAIL'} {frame['capture']}: "
                      f"{frame['timing']['mean_completed_ms']:.3f} ms completed, "
                      f"max RGB delta {c['max_channel_error']}, {c['over_tolerance_fraction']:.4%} beyond tolerance{detail}")
            except (OSError, ValueError) as error:
                frame["error"] = str(error); summary["passed"] = False
        if speedups and len(speedups) == len(names):
            summary["geomean_frame_speedup"] = math.exp(sum(math.log(value) for value in speedups) / len(speedups))
        (output / "summary.json").write_text(json.dumps(summary, indent=2) + "\n")
        print(f"{'PASS' if summary['passed'] else 'FAIL'}: summary and review images in {output}")
        return 0 if summary["passed"] else 1
    except (OSError, ValueError, KeyError, TypeError) as error:
        print(f"Renderer corpus benchmark failed: {error}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    sys.exit(main())
