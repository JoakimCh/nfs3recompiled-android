# Performance findings

| Approach | Result |
| --- | --- |
| Unlocking the 30 FPS cap | Revealed that the phone already ran well. This changes pacing, not rendering cost. |
| Adjacent batch merging | Little benefit during races; removed. Synthetic draw reductions overstated its usefulness. |
| Opaque shader selection | Retained, on by default. Joakim reported better TV FPS; the gain was not measured. Unknown/transparent draws use the original shader. |
| One-time vertex attribute setup | Retained. Removes repeated setup; no isolated FPS measurement. |
| Default-double vector specialization | Retained with precision fallbacks. No isolated whole-game speedup measured. |
| Original, cheaper mirror view | Retained for ARMv7. Trades mirror detail for less scene work. |
| Broad projection-loop conversion | Reverted after a directed-rounding mismatch. |
| Packed-data access fixes | Fixed alignment crashes; primarily a stability improvement. |

Historical TV runs showed roughly 22 FPS at 1080p and 38 FPS at 720p, but the
workloads differed. That suggested rendering cost was worth investigating; it
was not a controlled comparison. CPU profiles pointed toward draw submission,
but CPU sample shares and swap waits do not directly measure GPU execution time.

For another experiment, record the device, race/settings, source revision and
native BuildID alongside the result. Separate measured gains from impressions.
The performance report is available in Advanced. For native sampling, the
[phone script](../../tools/profiling/record-phone.sh) runs from an authorized
ADB shell: `sh /sdcard/Download/record-phone.sh` while a race is running.
