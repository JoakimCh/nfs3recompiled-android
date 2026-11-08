# Performance findings

## Build time DOUBLE and SINGLE comparison

The experiment branches from main `d0d5cd58`. DOUBLE is the default and uses
hardware double arithmetic across fixed helpers, emulated-FPU operations and
native vertex templates. Single-significand rounding and float/retry vertex
dispatch compile out. Integer conversions and guest float stores stay intact.
SINGLE retains main's upstream arithmetic, including compatible ARMv7 vertices
and checked float/retry on ARM64. [BUILD.md](BUILD.md) documents selection.

The owner measured the older Extended mode faster than Single with fast vertices,
which was faster than compatible Single. This motivates the experiment; it is
not a measurement of these new builds. Current automated evidence is in
[BUILD_STATUS.md](BUILD_STATUS.md). Device comparisons remain pending.

| Decision | Reason |
| --- | --- |
| Select arithmetic at build time | DOUBLE inlines plain double operations; SINGLE retains upstream 24-bit significand rounding with wider exponent handling. Neither needs a runtime precision selector. |
| Use one double vertex template in DOUBLE | The same formulae serve the whole double build. SINGLE keeps its own consistent policy rather than mixing arithmetic modes. |
| Drop precision menu, FPU overrides and unchecked ARMv7 switch | Upstream removed the native precision environment switches. Keeping the controls would misreport behavior; unchecked float loops can mishandle exceptional values. Old preferences are cleared and old backup keys ignored. |
| Compile out float/retry dispatch in DOUBLE | SINGLE retains main's compatible ARMv7 path and checked ARM64 float/retry path. Packed accesses and input/output overlap handling remain. |
| Keep packed-data access fixes | Required for unaligned guest data, especially ARMv7. These are correctness fixes. |
| Bake in opaque rendering and cache shader uniforms | The optimization is always enabled; the old toggle and environment override are removed. Each program initializes on first use and retains its own uniforms within a submission. Transparent/unknown draws and shader-link failures use the general path. Owner feedback favors the optimization; the cleanup needs device remeasurement. |
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

Both displays calculate FPS over the full sampling window, including loading
stalls. Verbose frame-time averages and p95 exclude gaps longer
than one second. Pause starts a fresh display window. Detailed collection adds
overhead; its device cost has not been measured. Vertex counters cover selected
loops, not every helper; retries also count as compatible passes. In DOUBLE
builds the existing compatible column counts direct hardware-double passes.

Reports identify the source, running ABI and fixed arithmetic policy. For native
sampling, run the [phone script](../../tools/profiling/record-phone.sh) from an
authorized ADB shell during a race: `sh /sdcard/Download/record-phone.sh`.

## Rendering diagnostics

The renderer prepares only shaders used by a submission, caches uniforms per
program across switches, and omits alpha/chroma uniforms from the opaque shader.
State comparisons remain where they avoid GL calls or select correct blending,
depth, clipping and transparency behavior. Draw order and batching are unchanged.

The obsolete batch-boundary comparison pass is removed. CSV schema v5 retains
its numeric positions as reserved zero columns. Verbose groups frame times,
draw/opaque load, CPU time and queue/swap elapsed time; these overlap and must
not be summed. DOUBLE shows direct double passes instead of inactive float/retry
counters. FPS-only still avoids the detailed collector.

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
  not a device FPS result and does not predict the new double build's FPS.
- Track dispatch introduced a GCC failure at mode `047f`, case 99: NaN instead
  of `3fc71d73`. Pinned Clang already failed that case without the specialization.
  NaN sign affecting bit-based projection branches was a hypothesis, not a traced
  cause. No gameplay glitch was tied to it. The old mode is no longer selectable.
- Earlier TV runs around 22 FPS at 1080p and 38 FPS at 720p used different workloads.
  They suggested rendering cost deserved investigation, not a measured speedup.

Historical experimental controls and detailed test logs remain in Git history;
[CHANGELOG.md](CHANGELOG.md) records when they were introduced and removed.
