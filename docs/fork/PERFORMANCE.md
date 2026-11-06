# Performance findings

## Current policy: upstream 0.78 integration

The fork adopts upstream `9c27ce73`'s fixed single-precision `fp::` API.
The signed universal build and automated checks passed; qualifications and exact
source are in [BUILD_STATUS.md](BUILD_STATUS.md). Device performance is unmeasured.

| Decision | Reason |
| --- | --- |
| Adopt upstream fixed single precision | Generated code and native helpers now use `fp::` without selecting an arithmetic mode at each operation. Retains wider exponents and exceptional-value handling; not a blanket conversion to C++ float. |
| Drop double object/vector/matrix dispatch | Its unrounded arithmetic is incompatible with the new single-precision policy. The old host timing result does not justify mixing policies. |
| Drop precision menu, FPU overrides and unchecked ARMv7 switch | Upstream removed the native precision environment switches. Keeping the controls would misreport behavior; unchecked float loops can mishandle exceptional values. Old preferences are cleared and old backup keys ignored. |
| Compare ARMv7 float implementations | This branch uses ordinary C++ floats with upstream-style libc retry; `fix-armv7-checked-vertices` uses ordered VFP instructions and FPSCR checks. Neither has a measured device speedup. The released 0.78.37 used the compatible fallback. ARM64 retains strict checked float/retry. |
| Keep packed-data access fixes | Required for unaligned guest data, especially ARMv7. These are correctness fixes. |
| Keep opaque shader and one-time vertex attribute setup | Independent of arithmetic changes. Opaque classification must remain: transparent/unknown draws need the original shader. Device gain needs remeasurement. |
| Keep cheaper mirror default, optional full detail | Avoiding extra rendering remains useful; this is a visual-quality choice. |
| Keep lightweight FPS and optional detailed recording | Needed for comparison. FPS-only avoids the detailed collector; disabled collection still has enable checks. |
| Keep diagnostics during integration | Upstream replay/function logs and crash reports help assess the substantial changes. The launcher menu is not the native hot path. |
| Continue dropping batch merging and broad projection conversion | Earlier real-race benefit was weak for merging; projection changes had rounding/NaN discrepancies. |

The precision selector and arithmetic overrides are gone. Range/alias checks,
NaN handling, transparent-draw classification and exception retries remain
necessary for correctness. The Debug tab retains logs, replay and crash tools;
removing that menu alone would not remove native checks or performance hooks.

## Overlay and recording

| Display | Recording off | Recording on |
| --- | --- | --- |
| Disabled | Performance collector off | Full statistics; no overlay |
| FPS | Lightweight frame counter | Full statistics; FPS display |
| Verbose | Full statistics and display | Full statistics and display, saved |

FPS-only samples an atomic frame counter once per second, skipping detailed
mutexes, timers, batch analysis and vertex counters. Overlay-only sessions do
not start a recording thread. Recording uses the detailed collector while keeping
the display choice. Reset disables both overlay and recording.

FPS includes loading stalls; Verbose interval statistics exclude gaps longer
than one second. Pause starts a fresh display window. Detailed collection adds
overhead; its device cost has not been measured. Vertex counters cover selected
loops, not every helper; retries also count as compatible passes.

Reports identify the source, running ABI and fixed arithmetic policy. For native
sampling, run the [phone script](../../tools/profiling/record-phone.sh) from an
authorized ADB shell during a race: `sh /sdcard/Download/record-phone.sh`.

## Comparing builds

Keep device, ABI, track, car, camera, resolution and mirror settings identical.
Account for the FPS cap, heating and recording overhead. Check split screen,
transparent geometry and long sessions as well as average FPS. Use upstream's
[replay tools](../../TECHNICAL.md#playing-on-a-phone) to compare deterministic
behavior; a replay recorded with different arithmetic may diverge.

## Lessons from removed experiments

- Adjacent batch merging had little real-race benefit; synthetic draw reductions
  overstated its value. Broad projection conversion changed rounding/NaN results.
- Double object dispatch reduced one x86-64 host kernel from 32.70 to 20.58 µs
  (five alternating pairs, 50,000 calls per run, 1,024 finite vertices). This was
  not a device FPS result and does not justify retaining incompatible arithmetic.
- Track dispatch introduced a GCC failure at mode `047f`, case 99: NaN instead
  of `3fc71d73`. Pinned Clang already failed that case without the specialization.
  NaN sign affecting bit-based projection branches was a hypothesis, not a traced
  cause. No gameplay glitch was tied to it. The old mode is no longer selectable.
- Earlier TV runs around 22 FPS at 1080p and 38 FPS at 720p used different workloads.
  They suggested rendering cost deserved investigation, not a measured speedup.

Historical experimental controls and detailed test logs remain in Git history;
[CHANGELOG.md](CHANGELOG.md) records when they were introduced and removed.
