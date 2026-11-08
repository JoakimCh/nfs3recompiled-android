#!/usr/bin/env python3
"""Run the initial desktop live-replay benchmark in an isolated demo fixture.

Build nfs3hp with -DNFS_RENDER_BENCHMARK=ON first. No APK or phone is required.
This measures a simulated replay, not a fixed draw-command capture or GPU-only time.
"""

import argparse
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys

from benchmark_replay_info import inspect_replay, inspect_assets, file_identity, SETTINGS_BYTES
from make_install_win import build as install_slots


ROOT = Path(__file__).resolve().parents[1]


def case_child(root, name):
    matches = [path for path in root.iterdir() if path.name.casefold() == name.casefold()]
    if len(matches) != 1:
        raise ValueError(f"Expected exactly one {name} in {root}")
    return matches[0]


def prepare(demo, replay, target):
    target.mkdir()
    for name in ("fedata", "gamedata"):
        shutil.copytree(case_child(demo, name), target / name)
    # The final demo ships these two HUD sheets under names differing from
    # their own nextmenu links. Retail's parser follows those links even for
    # this single-player benchmark. Supply aliases in the disposable fixture.
    menus = case_child(target / "fedata", "menus")
    for alias, source in (("ps2p1c1r.mnu", "ps2p1c2r.mnu"),
                          ("ps2p1r1c.mnu", "ps2p1r2c.mnu")):
        if not any(path.name.casefold() == alias for path in menus.iterdir()):
            shutil.copyfile(case_child(menus, source), menus / alias)
    # The executable is statted by the original integrity checks; the code that
    # executes is compiled into the benchmark binary, not this copied image.
    for name in ("nfs3.exe", "eacsnd.dll", "softtria.dll", "voodoo2a.dll"):
        shutil.copy2(ROOT / "nfs3hp" / name, target / name)
    (target / "install.win").write_bytes(
        ("\r\n".join(install_slots("english", markers=True)) + "\r\n").encode("ascii"))
    shutil.copyfile(replay, target / "replay.rp3")
    config = case_child(target / "fedata", "config")
    (config / "config.dat").write_bytes(replay.read_bytes()[:SETTINGS_BYTES])


def positive(value):
    number = int(value)
    if number < 1:
        raise argparse.ArgumentTypeError("must be positive")
    return number


def nonnegative(value):
    number = int(value)
    if number < 0:
        raise argparse.ArgumentTypeError("must be nonnegative")
    return number


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--binary", type=Path, required=True)
    parser.add_argument("--demo-dir", type=Path, default=ROOT / "out/benchmark-assets/demo",
                        help="Extracted demo (default: tools/setup_benchmark.py output)")
    parser.add_argument("--replay", type=Path, default=ROOT / "tests/fixtures/renderer-benchmark/joakim.rp3",
                        help="Replay (default: included Rocky Pass / Corvette fixture)")
    parser.add_argument("--output-dir", type=Path, required=True, help="New directory; never reuses stale results")
    parser.add_argument("--warmup", type=nonnegative, default=300, help="Replay frames excluded before timing (default 300)")
    parser.add_argument("--frames", type=positive, default=300, help="Measured frame intervals (default 300)")
    parser.add_argument("--timeout", type=positive, default=180, help="Whole process limit in seconds")
    parser.add_argument("--sync", choices=("finish", "submit"), default="finish",
                        help="finish includes GPU completion; submit measures presentation intervals without forcing completion")
    parser.add_argument("--gl-thread", choices=("off", "on"), default="off")
    parser.add_argument("--video-driver", default="offscreen", help="SDL video driver; e.g. offscreen or x11")
    parser.add_argument("--capture-frames", type=positive, help="Save self-contained renderer captures instead of timing live replay")
    parser.add_argument("--capture-stride", type=positive, default=120, help="Frames between captures (default 120)")
    args = parser.parse_args()
    try:
        binary, demo, replay, output = (path.resolve() for path in (
            args.binary, args.demo_dir, args.replay, args.output_dir))
        if not binary.is_file() or not os.access(binary, os.X_OK):
            raise ValueError("Build an executable with NFS_RENDER_BENCHMARK=ON and pass it via --binary")
        if not demo.is_dir():
            raise ValueError("Demo data missing; run python3 tools/setup_benchmark.py or pass --demo-dir")
        metadata = inspect_replay(replay)
        metadata["assets"] = inspect_assets(demo, metadata)
        if not metadata["assets"]["core_scene_dependencies_found"]:
            raise ValueError("Replay has missing core scene assets or unresolved car IDs")
        if not metadata["traffic_disabled"]:
            raise ValueError("Initial demo fixture requires traffic disabled")
        if metadata["race_kind_raw"] != 0:
            raise ValueError("Initial demo fixture supports single-race replays only")
        if output.exists():
            raise ValueError("Choose a new --output-dir; existing outputs are preserved")
        output.mkdir(parents=True)
        fixture = output / "data"
        prepare(demo, replay, fixture)
        metadata["binary"] = file_identity(binary)
        metadata["options"] = {key: getattr(args, key) for key in (
            "warmup", "frames", "timeout", "sync", "gl_thread", "video_driver", "capture_frames", "capture_stride")}
        metadata["source_commit"] = subprocess.run(
            ["git", "rev-parse", "HEAD"], cwd=ROOT, text=True, capture_output=True).stdout.strip()
        metadata["source_dirty"] = bool(subprocess.run(
            ["git", "status", "--porcelain"], cwd=ROOT, text=True, capture_output=True).stdout)
        (output / "inputs.json").write_text(json.dumps(metadata, indent=2) + "\n")
        env = dict(os.environ)
        # Do not inherit diagnostics or gameplay overrides that alter the workload.
        for key in list(env):
            if key.startswith("NFS_"):
                del env[key]
        env.update({
            "NFS_BENCHMARK": "1", "NFS_AUTO_REPLAY": "1",
            "NFS_BENCH_WARMUP": str(args.warmup), "NFS_BENCH_FRAMES": str(args.frames),
            "NFS_BENCH_SYNC": args.sync, "NFS_GL_THREAD": "1" if args.gl_thread == "on" else "0",
            "NFS_BENCH_REPORT": str(output / "timing.json"),
            "NFS_BENCH_IMAGE": str(output / "frame.ppm"),
            "NFS_FPS_CAP": "0", "SDL_AUDIO_DRIVER": "dummy",
            "SDL_VIDEO_DRIVER": args.video_driver,
        })
        if args.capture_frames:
            if args.capture_frames > 100:
                raise ValueError("At most 100 capture frames per run")
            env.update({"NFS_CAPTURE_DIR": str(output), "NFS_CAPTURE_FRAMES": str(args.capture_frames),
                        "NFS_CAPTURE_STRIDE": str(args.capture_stride)})
        with (output / "run.log").open("w") as log:
            try:
                result = subprocess.run([str(binary), str(fixture)], cwd=fixture, env=env,
                                        stdout=log, stderr=subprocess.STDOUT, timeout=args.timeout)
            except subprocess.TimeoutExpired:
                raise ValueError(f"Benchmark timed out; inspect {output / 'run.log'}") from None
        if result.returncode != 0:
            raise ValueError(f"Benchmark exited {result.returncode}; inspect {output / 'run.log'}")
        if args.capture_frames:
            index = json.loads((output / "capture-index.json").read_text())
            if len(index.get("frames", [])) != args.capture_frames:
                raise ValueError("Capture count does not match the request")
            index["files"] = {name: file_identity(output / name) for name in index["frames"]}
            (output / "capture-manifest.json").write_text(json.dumps(index, indent=2) + "\n")
            print(f"Captured {args.capture_frames} renderer frames: {output}")
            return 0
        if not (output / "timing.json").is_file():
            raise ValueError(f"Game exited before completing the benchmark; inspect {output / 'run.log'}")
        timing = json.loads((output / "timing.json").read_text())
        if timing.get("status") != "complete" or timing.get("measured_frames") != args.frames:
            raise ValueError("Benchmark did not produce the requested measurement")
        image = output / "frame.ppm"
        if not image.is_file() or not timing.get("lit_pixels", 0):
            raise ValueError("Benchmark did not produce a nonblack frame")
        if timing.get("race_cars") != len(metadata["cars"]):
            raise ValueError("Running car count differs from the supplied replay")
        if timing.get("race_clock_end", 0) <= timing.get("race_clock_start", 0):
            raise ValueError("Replay clock did not advance during measurement; use more --frames")
        print(f"{timing['measured_frames']} frames: {timing['mean_fps']:.2f} FPS, "
              f"mean {timing['mean_frame_ms']:.2f} ms, p95 {timing['p95_frame_ms']:.2f} ms")
        print(f"Renderer: {timing['gl_renderer']}; outputs: {output}")
        return 0
    except (OSError, ValueError, KeyError) as error:
        print(f"Benchmark failed: {error}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    sys.exit(main())
