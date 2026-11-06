# Performance findings

## Upstream 0.78 integration candidate (not tested)

Source: experimental branch `919280cf` plus upstream `9c27ce73` (four commits
since `4a65cd49`). Upstream changes 279 files, including regenerated functions,
native replacements, replay diagnostics and a fixed single-precision `fp::` API.
No tests, build or device measurements have been run for this integration.

| Decision | Reason |
| --- | --- |
| Adopt upstream fixed single precision | Generated code and native helpers now use `fp::` without selecting an arithmetic mode at each operation. Retains wider exponents and exceptional-value handling; not a blanket conversion to C++ float. |
| Drop double object/vector/matrix dispatch | Its unrounded arithmetic is incompatible with the new single-precision policy. The old host timing result does not justify mixing policies. |
| Drop precision menu, FPU overrides and unchecked ARMv7 switch | Upstream removed the native precision environment switches. Keeping the controls would misreport behavior; unchecked float loops can mishandle exceptional values. Old preferences are cleared and old backup keys ignored. |
| Keep ARMv7 compatible fallback and ARMv8 checked float/retry | Clang ARMv7 cannot honor the exception-tracking assumptions. Eligibility is now a compile-time platform choice; overlap and exceptional-value checks remain necessary. |
| Keep packed-data access fixes | Required for unaligned guest data, especially ARMv7. These are correctness fixes. |
| Keep opaque shader and one-time vertex attribute setup | Independent of arithmetic changes. Opaque classification must remain: transparent/unknown draws need the original shader. Device gain needs remeasurement. |
| Keep cheaper mirror default, optional full detail | Avoiding extra rendering remains useful; this is a visual-quality choice. |
| Keep lightweight FPS and optional detailed recording | Needed for comparison. FPS-only avoids the detailed collector; disabled collection still has enable checks. |
| Keep diagnostics during integration | Upstream replay/function logs and crash reports help assess the substantial changes. The launcher menu is not the native hot path. |
| Continue dropping batch merging and broad projection conversion | Earlier real-race benefit was weak for merging; projection changes had rounding/NaN discrepancies. |

The candidate removes arithmetic-policy dispatch, not all branches. Range checks,
NaN handling, transparent draw classification, in-place alias checks and retries
are correctness conditions. Removing the Debug tab alone would not remove them
or the independently enabled performance hooks. A later production build option
could compile out diagnostics, but should be evaluated separately with the same
race, device, ABI, resolution and settings. No FPS improvement is claimed here.

Before accepting this candidate: run the updated fixed-single vertex comparison
on both normal and ARMv7-style paths, inspect both ABI compiler policies, run
launcher/settings/controller regressions, and build both ABIs. Then compare
upstream and candidate on the same TV/phone races, including split screen,
mirrors, transparent geometry and long sessions. Historical expanded track NaN
failures must be reassessed against the new upstream reference, not presumed fixed.

## Historical findings before upstream 0.78 integration

The following results describe the old selectable-arithmetic branch only. Its
precision controls and double specialization are removed in the candidate.

| Approach | Result |
| --- | --- |
| Unlocking the 30 FPS cap | Revealed that the phone already ran well. This changes pacing, not rendering cost. |
| Adjacent batch merging | Little benefit during races; removed. Synthetic draw reductions overstated its usefulness. |
| Opaque shader selection | Retained, on by default. Joakim reported better TV FPS; the gain was not measured. Unknown/transparent draws use the original shader. |
| One-time vertex attribute setup | Retained. Removes repeated setup; no isolated FPS measurement. |
| Default-double vector specialization | Retained with precision fallbacks. No isolated whole-game speedup measured. |
| Default-double object specialization | Selects arithmetic once per batch using the existing template. ARM code removes repeated rounding checks; host kernel CPU time improved, Android FPS unmeasured. |
| Original, cheaper mirror view | Default on ARMv7 and ARMv8. Full-detail mirrors can be enabled under Advanced → Performance. |
| Broad projection-loop conversion | Reverted after a directed-rounding mismatch. |
| Packed-data access fixes | Fixed alignment crashes; primarily a stability improvement. |

Default-double mode does not need single-precision rounding after each operation.
The object specialization selects the existing DoubleMath template once per batch,
sharing the formulae and explicit float stores with the compatibility paths.

For the object specialization, five alternating baseline/candidate pairs using
NDK 30 Clang on Linux x86-64 measured median CPU time of 32.70 → 20.58 µs per call
(50,000 calls/run, 1,024 finite-input vertices/call, statistics disabled). This
37% reduction is an isolated host kernel result, not an ARM or whole-game FPS
measurement. ARMv7/ARMv8 native vertex text grows by 848/1,288 bytes. Track dispatch
remains unchanged because a trial altered a NaN-sensitive GCC comparison case.

### Why track dispatch was deferred

At 200 host cases per rounding mode, the track specialization made GCC fail a
previously passing case: mode `047f` (single precision, rounding down), case 99.
Native output was NaN (`7fc00000`) where the generated reference wrote
`3fc71d73` (about 1.55558622). Pinned Clang already fails that same case without
the specialization. Removing only the track dispatch restored the GCC check.

The failure mode does not select the new double path. A working hypothesis is
that changed inlining/register allocation alters NaN sign/payload propagation
in the existing path. Track projection inspects raw float bits as a signed
integer when choosing `1` versus `1/z`; NaN sign can therefore affect control
flow. The first divergent operation has not been traced, so this mechanism is
not established. Trace it and establish the intended original x87 behaviour
before revisiting track optimization. No gameplay glitch has been tied to this case.

Historical TV runs showed roughly 22 FPS at 1080p and 38 FPS at 720p, but the
workloads differed. That suggested rendering cost was worth investigating; it
was not a controlled comparison. CPU profiles pointed toward draw submission,
but CPU sample shares and swap waits do not directly measure GPU execution time.

Advanced → Performance offers Extended race precision (default) or Original
single precision. ARMv7 additionally offers Fast vertex calculations, off by
default and available with single-precision arithmetic. It omits exceptional-value
retries and may render incorrectly. ARMv8 retains its checked fast path. Selecting
precision clears conflicting Debug overrides; broader arithmetic experiments remain
under Debug. The effective mode is displayed. Reset restores Extended and Fast off.

For comparisons, keep the device, ABI, track, car, camera, resolution and mirror
settings the same. Account for the frame cap and heating. The Verbose overlay and report
include compatible/fast/retry vertex passes: verify that Fast actually ran. Counters
cover selected loop dispatches, not every vertex helper; a retry counts as both a
retry and a compatible pass. Performance collection adds overhead. No device FPS
gain has been measured for this experiment.

### Overlay and recording

| Display | Recording off | Recording on |
| --- | --- | --- |
| Disabled | Performance collector off | Full statistics; no overlay |
| FPS | Lightweight frame counter | Full statistics; FPS display |
| Verbose | Full statistics and display | Full statistics and display, saved |

Recording selects the detailed collector automatically without changing the display
choice. This permits an unobstructed capture and shares one detailed collector.
FPS-only uses one atomic frame counter updated by the GL thread, sampled once per
second. It skips detailed mutexes, profiling timers, batch analysis and vertex
counters; no recording thread is created. Residual enable checks and display work
remain. The old enabled overlay preference maps to Verbose; Reset disables both
overlay and recording. FPS uses completed swaps over the sampling window, including
loading stalls; Verbose interval statistics exclude gaps longer than one second.
A pause starts a fresh display window. Device overhead has not been measured.

The report records the source/build, running ABI and effective arithmetic settings.
For native sampling, the [phone script](../../tools/profiling/record-phone.sh) runs
from an authorized ADB shell: `sh /sdcard/Download/record-phone.sh` during a race.
