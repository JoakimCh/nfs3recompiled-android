# Performance findings

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

For the object specialization, five alternating baseline/candidate pairs using
NDK 30 Clang on Linux x86-64 measured median CPU time of 32.70 → 20.58 µs per call
(50,000 calls/run, 1,024 finite-input vertices/call, statistics disabled). This
37% reduction is an isolated host kernel result, not an ARM or whole-game FPS
measurement. ARMv7/ARMv8 native vertex text grows by 848/1,288 bytes. Track dispatch
remains unchanged because a trial altered a NaN-sensitive GCC comparison case.

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
settings the same. Account for the frame cap and heating. The overlay and report
include compatible/fast/retry vertex passes: verify that Fast actually ran. Counters
cover selected loop dispatches, not every vertex helper; a retry counts as both a
retry and a compatible pass. Performance collection adds overhead. No device FPS
gain has been measured for this experiment.

The report records the source/build, running ABI and effective arithmetic settings.
For native sampling, the [phone script](../../tools/profiling/record-phone.sh) runs
from an authorized ADB shell: `sh /sdcard/Download/record-phone.sh` during a race.
