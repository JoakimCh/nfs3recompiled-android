# Experimental renderer benchmarks

Two desktop harnesses use the production renderer: a live Android/retail replay
for generating scenes, and self-contained frame captures for fixed-workload
performance/correctness checks. They compile separately from normal builds and
add no launcher controls.

The live mode measures **live-replay frame intervals**, including simulation, submission,
synchronization and the game's timer pacing. It is not a GPU-only test or a
fixed draw-command replay. Physics precision, scheduling and camera changes can
change the rendered workload. Compare images and clock ranges before drawing
performance conclusions; host software rendering does not predict TV FPS.

## Build and run

Requirements: desktop C++17 toolchain, CMake, SDL3 development files (the fork
pins 3.4.18), OpenGL development files, and Python 3.8+. Linux x86-64 with SDL's
offscreen driver and Mesa llvmpipe has been exercised; other hosts are unverified.
Set `SDL3_DIR`/`CMAKE_PREFIX_PATH` if SDL is installed outside standard locations.

```sh
python3 tools/setup_benchmark.py
cmake -S . -B out/replay-benchmark -DCMAKE_BUILD_TYPE=Release \
  -DNFS_RENDER_BENCHMARK=ON -DNFS_GAME_PRECISION=DOUBLE
cmake --build out/replay-benchmark --parallel 2
python3 tools/renderer_benchmark.py \
  --binary out/replay-benchmark/nfs3hp \
  --output-dir out/benchmark-run-01
```

Setup downloads the pinned demo ZIP, checks its SHA-256, and extracts only
FEDATA/GAMEDATA plus the original readme/license notices into ignored
`out/benchmark-assets/demo/`. It runs no Windows installer. Rerunning verifies
existing files against the pinned archive and refuses to overwrite changed data.
For offline setup, use `python3 tools/setup_benchmark.py --archive /path/to/demo.zip`.
An HTTPS mirror can be supplied with `--url`; the required checksum stays fixed.

The runner defaults to that demo folder and the included
[`joakim.rp3`](../../tests/fixtures/renderer-benchmark/joakim.rp3). Override
`--demo-dir` or `--replay` for another compatible fixture.

## Fixed renderer capture and replay

Record a few representative frames once using a trusted build:

```sh
python3 tools/renderer_benchmark.py --binary out/replay-benchmark/nfs3hp \
  --output-dir out/render-captures --warmup 300 \
  --capture-frames 3 --capture-stride 120
SDL_VIDEO_DRIVER=offscreen out/replay-benchmark/nfs_render_replay \
  --capture out/render-captures/frame-0.nfrc --output-prefix out/render-baseline/frame-0 \
  --warmup 10 --iterations 50
```

Choose a later warmup or larger stride for later race sections. Keep these
captures unchanged when testing renderer edits. Rebuild only `nfs_render_replay`
with `cmake --build out/replay-benchmark --target nfs_render_replay --parallel 2`;
the standalone player needs neither the game simulation nor demo files.

Each version-1 `.nfrc` file contains GL-ready initial texture data and mipmaps,
ordered uploads/releases, clears, vertices, batches, fog and a reference RGBA
image. Fields are serialized explicitly; vertex records use the renderer's
32-byte IEEE-float layout on little-endian hosts. Files are bounded at 256 MiB,
and malformed ranges, missing textures and frames without an initial full clear
are rejected. Captures contain game assets and remain local/ignored.

Replay calls production `upload`, `clearFrame` and `drawPending`; it has no shader
copy. Initial texture restoration is outside timing; uploads within the recorded
frame remain timed. Timings separate submission wall time from completion wall
time (`glFinish`), excluding simulation, presentation, reference readback and
file I/O. Completion wall time is not a hardware GPU timestamp.

Native output is `<prefix>.json`, `.reference.ppm` and `.candidate.ppm`. The JSON
records batches/vertices, device/version, samples and `rgba_mismatch_bytes`.
Zero means byte-exact RGBA reproduction. A nonzero value is reported rather than
silently replacing the baseline. The images cover the internal game render
target, before the final presentation blit and display adjustments; live-mode
window dimensions can differ from this internal resolution.

`--shader general` disables the opaque shader only inside this standalone test
process, using the production fallback. It permits comparison with `auto`
without reintroducing a launcher option or a production hot-path toggle.

Independent 4×4 GL regression scenes can run without demo downloads:

```sh
NFS_RENDER_REPLAY_BINARY="$PWD/out/replay-benchmark/nfs_render_replay" \
  python3 -m unittest discover -s tools/tests -p test_render_capture.py -v
```

They check independently expected pixels for opaque/transparent geometry,
partial clears, texture updates, releases and mipmap reallocation, plus malformed
captures and output preservation. Other GL implementations remain unverified.

## Live mode details

The runner copies FEDATA/GAMEDATA into an isolated output folder and adds the
repository's runtime files and generated `install.win`. It copies the replay
unchanged and seeds that folder's `config.dat` from its settings. Original demo
and replay files are never modified. Existing output directories are rejected.

| Option | Default | Purpose |
| --- | --- | --- |
| `--warmup` | 300 | Replay frames discarded before measurement; skips the opening camera in this fixture |
| `--frames` | 300 | Frame intervals measured after warmup |
| `--sync finish` | `finish` | Wait for GPU completion before each timestamp |
| `--sync submit` | | Do not force completion; timestamps still include presentation and queue behavior, not just submission CPU cost |
| `--gl-thread off/on` | `off` | Run GL on the game thread or the production GL worker |
| `--video-driver` | `offscreen` | SDL backend; use `x11`, for example, for a visible window where available |
| `--timeout` | 180 seconds | Fail if startup or measurement does not complete |

Use another build directory and `-DNFS_GAME_PRECISION=SINGLE` to select the
other arithmetic policy. The binary reports its compiled policy; there is no
runtime precision switch. Only DOUBLE has been exercised with this harness.
Resolution, camera, detail and mirror settings currently come from the saved
settings and normal engine behavior; the report records actual window dimensions.

Outputs:

- `inputs.json`: replay/core-asset/binary hashes, options, source commit and dirty flag.
- `timing.json`: actual GL implementation, precision, dimensions, car count,
  race-clock range, warmup, individual frame intervals, mean/min/max and p50/p95.
- `frame.ppm`: final framebuffer, read after timing so readback/file I/O is excluded.
- `run.log`: loading, diagnostics and completion/failure information.
- `data/`: disposable run data and settings, retained for diagnosis.

Warmup zero still needs one baseline presentation before an interval can be
measured. The runner requires a completed report, the expected number of cars,
an advancing replay clock and a nonblack image. These checks catch startup and
measurement failures; visual correctness still needs inspection. A replay ending
before the requested measurement is a failure, not a shortened successful run.

## Demo and supplied replay

Inspected the [NFSHome final demo](https://www.nfshome.com/demos.php?download=4),
whose README says **Final Demo: Sept 1st 1998**. Archive SHA-256:
`425e240496a98b2a4543681b35dd92cc340c723b94c13d72755f44de4c90530b`.
It extracts to 133 files / 23,647,711 bytes; data folders account for 18,780,408 bytes.
The owner's benchmark replay is included in source at his request; downloaded
demo files and other private replays stay outside tracked source.

Redistribution review (2026-11-08): the archive's readme contains copyright and
trademark notices; its `license.txt` applies to Microsoft components. Neither
provides a grant to redistribute extracted EA assets. We did not establish
demo-specific permission to bundle them. EA's [current content policy](https://help.ea.com/en/articles/security-and-rules/ea-content-policy/)
also does not establish that permission for this 1998 package. The repository
therefore supplies a downloader, rather than redistributing the demo data.

| Assets | Observed contents |
| --- | --- |
| `gamedata/tracks/trk003/Tr03.frd` | Rocky Pass, 186 blocks under our loader's convention |
| `tr030.qfs`, `tr031.qfs` | 192 ARGB1555 textures each: 167 opaque, 25 with nonopaque texels; 2×2 through 128×128 |
| `TR030_8.QFS`, `tr031_8.qfs` | Corresponding 192-entry alternate-format sets |
| `sky.fsh`, horizons, cameras, collision | Background, environment and track inputs |
| `gamedata/carmodel/Corv/car.viv` | FCE header: 1,192 triangles, 878 vertices, 13 parts; TGA texture, cockpit and physics parameters |
| Pursuit Corvette archive | FCE header: 1,225 triangles, 907 vertices, 13 parts |
| `SFX.FSH`, `weather.fsh`, `hud98.fsh` | Effects, weather and HUD shapes |

Model totals are not simultaneously visible triangle counts. Stored texture
opacity alone does not establish opaque-shader eligibility; draw state matters.

The owner's `joakim.rp3` is version 2, 169,720 bytes: Rocky Pass, two laps,
eight Corvettes, traffic disabled, seed 28,909. Replay SHA-256:
`cc849bcc4e787379b23414b36080a0ef12132ac590fa97d42ebf94a66c65b07e`.
All eight roster IDs and saved selection IDs match the demo Corvette's ID 19.
The existing loader remaps saved list indices using those IDs. Matching IDs do
not prove the demo and retail physics/geometry are byte-identical.

Preflight metadata and core asset inspection can run without building:

```sh
python3 tools/benchmark_replay_info.py /path/to/joakim.rp3 \
  --demo-dir /path/to/extracted-demo --output /path/to/assets.json
```

This checks saved IDs and selected scene dependencies, not every runtime file
access or the replay input stream. The initial runner accepts single-race,
traffic-disabled replays with matching assets; this supplied fixture is the one
validated end to end.

## Bootstrap and measurement boundaries

The demo lacks retail main-menu/cursor assets and the frontend sound bank.
The benchmark bypasses menu navigation, initializes the language block needed
by loading/HUD code, disables cursor artwork and uses effects/music-disabled
paths. Audio mixing is excluded. Two demo HUD sheet filenames differ from their
own menu links; the disposable fixture provides aliases to the shipped sheets.
Normal importer validation remains unchanged.

Without time spent in menus, loading can finish before the first registered
controls-timer callback. The harness yields through the game's Sleep wrapper
for that real callback, with a bounded wait; it does not synthesize clock ticks.
Measurement starts only after replay mode, cars and an advancing race clock
are observed. The display cap is disabled and vsync-off requested, but native
simulation/timer pacing remains part of the workload. GL errors at readback,
timeouts, early exits and missing results fail the run.

Desktop build repairs include loading `glBlitFramebuffer`, isolating the Android
sampling profiler, making trace paths portable, and required includes/formatting
for GCC. Benchmark hooks compile out with `NFS_RENDER_BENCHMARK=OFF` (default).

The fixed-frame player is the preferred tool for renderer edits. Use live mode
to create new scenes and to assess whole-engine effects separately.
