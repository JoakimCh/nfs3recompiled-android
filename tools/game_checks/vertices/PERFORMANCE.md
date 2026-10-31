# Direct-double vector arithmetic experiment

Base: `f908f33` (alphaF0.78). This is a CPU-kernel optimization, not a completed
ARMv7 port or a fix for the race-loading crash in issue #5.

## Change

Select host-double arithmetic once at entry to dotProducts (0x4e0210),
multiplyMatrices (0x4e0280), rotateVectors (0x4e03b0), and transformPoints
(0x4e0430). The existing implementations checked the emulated FPU precision
inside each arithmetic operation. The new specialization retains operation
order, stores, guest registers and flags, and aliasing behavior. It does not
change physics precision, race defaults, or multiplayer settings.

Only the default double-backed FPU with kRoundNone takes this path. Single
precision, WITH_PEDANTIC_FPU, and WITH_WIDE_FPU retain their previous paths.
Floating-point contraction is disabled. There is no fast-math approximation.

## Validation

GCC 13.3.0, Linux x86-64, C++17, -O2, -fno-strict-aliasing,
-ffp-contract=off, -frounding-math, WITH_MMX.

The existing differential harness regenerated the original routines and ran
1,000 randomized cases in each of eight guest FPU control modes for each of
four functions: 32,000 comparisons passed. It compares guest memory (excluding
dead stack), registers, flags, live FPU state and outgoing calls. As in the
upstream harness, NaN payload/sign-only differences in floating-point outputs
are counted rather than failed: 19 such words were observed. This is not a
claim of exhaustive bitwise equivalence or full-game validation.

The unchanged track/object vertex paths also passed 3,200 regression cases.
Both experimental FPU configurations also passed syntax compilation; they
were not benchmarked or run through a new full differential suite.

Run from the repository root, with capstone installed for the selected Python:

```sh
python3 tools/game_checks/vertices/run.py 1000 dotProducts multiplyMatrices rotateVectors transformPoints
VCHECK_BENCH=200000 tools/game_checks/vertices/build/vcheck 0 dotProducts multiplyMatrices rotateVectors transformPoints
```

The runner now supports POSIX C++ compilers as well as its existing Windows
build. CXX selects the POSIX compiler. Benchmark fixtures use fixed finite
inputs, non-overlapping outputs, and the default 0x037f FPU mode. Timing
excludes data setup and differential memory snapshots.

## Host microbenchmark

Median of five runs, alternating baseline and optimized executables, 200,000
calls per run. Both executables use the same harness and compiler flags; the
baseline uses native_vertices.cpp from the base commit. Vector routines process
1,024 items per call; matrix multiplication processes one 3x3 matrix.

| Routine | Baseline ns/call | Optimized ns/call | Speedup |
| --- | ---: | ---: | ---: |
| Dot products | 2091.8 | 1773.8 | 1.18x |
| Matrix multiplication | 35.0 | 25.9 | 1.35x |
| Vector rotation | 7988.7 | 4388.3 | 1.82x |
| Point transformation | 7821.4 | 4726.6 | 1.65x |

These are x86-64 synthetic kernel timings, not ARMv7 results or game FPS.
The full-game benefit depends on how much frame time these routines consume.
No Android SDK/NDK toolchain or TV was used for this validation. No APK was
built, and the project's ARM64-only packaging is unchanged.

## Remaining TV work

Identify the TV model, SoC/GPU, Android version and supported ABIs. Build and
validate a separate armeabi-v7a configuration, then collect the race-loading
crash trace and a CPU profile during a reproducible race. Rewrite the measured
physics hotspots with explicit precision contracts and differential checks.
Do not globally change doubles to floats or enable fast-math: doing so can
change physics and network synchronization. Actual TV testing must establish
both compatibility and acceptable sustained frame rates.
