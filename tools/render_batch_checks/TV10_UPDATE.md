# tv10-profile: phase timings and draw-state boundaries

Release0.78-armv7-tv10-profile, version87. Same package/signing identity as tv9;
install over it, retaining game data, pad bindings, FPS cap and experiment values.
This is a measurement release; no speedup is claimed. Collection and overlay
use the existing Advanced switches and work with Debug mode off. Disabling both
skips timing and boundary analysis. Share/Save to Downloads exports schema v2.

User's actual TV tv9 profile matches BuildID d06bdbc26a04430f4ab0a76df50def12bee078d5:
5701 samples,0lost, PowerVR GLES driver, drawPending30.35% inclusive,
glDrawArrays24.80%, quadList8.96%, rotateVectors0.67%. Game and GL are separate
threads (same SDLThread name). CPU sampling cannot measure blocked/GPU time.
Earlier independent TV counters showed~23FPS at1920x1080,531draws/frame,
9.59ms submission CPU/frame. These runs are separate; don't combine their
denominators. The sustained phone counter run was2344x1080, not640x480 (menu).

## New measurements

All phase timings have call count, elapsed monotonic nanoseconds and calling
thread CPU nanoseconds. CPU is CLOCK_THREAD_CPUTIME_ID on Android. Values are
cumulative, sampled once/second. The instrumentation never changes guest CPU
registers, guest memory, floating precision, shaders, draw ordering or pacing.

* race_main: RAII scope over native graphics::raceFrame when entry eax==0,
  the main view pass. Includes its nested calls/early returns; not an entire
  game frame, simulation interval or all mirror passes.
* game_cycle: work between the end of one Renderer::paceFrame and the start
  of the next. Includes game logic, preparation, posting, queue waits and other
  work between those checkpoints, excluding the explicit cap sleep inside
  paceFrame. Unrelated/loading intervals >1s discarded. This is not exclusive
  preparation time, and spans may differ from presentation windows.
* queue_throttle: entire glthread::presentPosted body while threading is on,
  including mutex acquisition, predicate/wait bookkeeping and backpressure;
  nonblocking calls also counted. queue_finish similarly covers finish()'s
  lock/condition wait after its early guards.
* present: entire Renderer::presentFrame, including swap, final blit, stats and
  presentDone. Counts invocations even if a swap fails. swap: SDL_GL_SwapWindow
  itself. Neither measures GPU execution time, and swap time alone cannot tell
  GPU work apart from refresh/presentation throttling or scheduling delays.
* pace_sleep: requested cap sleep only, not other game-engine waits or vsync.
* gl_idle_wait: GL worker's condition-variable wait for jobs/release requests,
  only when initially no work is available. Includes wake/scheduler latency;
  does not measure every idle period or GPU idle time.

Time categories overlap: race/queue are inside game cycles, swap is inside
present. Game and GL work can run simultaneously. NEVER sum all phase times to
explain one frame. Elapsed minus CPU is not exclusively blocked time (includes
descheduling and measurement effects). Scopes carry an epoch; pause/resume
changes discard scopes crossing lifecycle transitions. Counters never reset
with the existing debug DrawCounters. Scope costs are small but unmeasured on
hardware; this release adds overhead. Overlay includes one new line showing
game-cycle CPU, queue-throttle elapsed and swap elapsed per presented frame,
with approximate short-window normalization.

## Batch boundaries

Each measured drawPending scans RAW adjacent saved Batch entries, even with
merging disabled. Never compares across submissions/uploads/clears. Adjacent
pairs and fully identical pairs counted, plus ALL differing state categories:
texture index, levels, format, wrap(S/T), depth(test/always/write), blending,
culling(enable/mode), chromakey, clip rectangle, fog-table index, gamma bits.
Several categories can differ for one pair, so reason totals overlap. End
offset and struct padding deliberately ignored. Signed zero and NaN payload
differences in gamma retained. This matches the existing exact merge predicate.

Boundary analysis is outside the existing drawPending submission timing; its
elapsed and CPU cost are recorded separately. Counts aggregate locally, then
use one protected counter update per submission. No per-triangle timers/locks
and no synchronous GPU readbacks. Identical pairs predict potential merges
within one submission; different state does not prove geometry could safely
be reordered or combined. Transparency/depth/order correctness remains essential.

## Schema v2

Original264 CSV fields retain indices and meanings. Metadata schema becomes
nfs3-performance-v2.39 columns appended, total303 fields, JNI length303.
Each phase prefix below expands to calls, elapsed_ns, cpu_ns in that order:

264 race_main;267 queue_throttle;270 queue_finish;273 present;
276 swap;279 pace_sleep;282 game_cycle.

285 adjacent_pairs;286 identical_pairs;287 break_texture;288 break_levels;
289 break_format;290 break_wrap;291 break_depth;292 break_blend;293 break_cull;
294 break_chroma;295 break_clip;296 break_fog;297 break_gamma;
298 boundary_analysis_elapsed_ns;299 boundary_analysis_cpu_ns;
300 gl_idle_wait_calls;301 gl_idle_wait_elapsed_ns;302 gl_idle_wait_cpu_ns.

Use differences between rows from one session; use call counts for per-call
cost and presentation counts for approximate per-frame cost. Compare raw
adjacent-pair reason percentages with adjacent_pairs, not rendered frames.
No new GPU timestamps were added: the existing API timing cannot prove GPU
saturation. No new forced flush/finish, blocking GPU query, shader or graphics
quality/resolution changes. Existing report retention/export behavior remains.

## Checks and next user step

Counter tests (UBSan): enabled/disabled, timing field triples, stale epochs,
Scope pause/resume rejection, game-cycle anchors, boundary counters, concurrent
snapshots, old interval histograms. Batch tests: exact bit per state category,
simultaneous reasons, gamma signed zero/NaN and end exclusion, equivalence to
sameState over1million synthetic batches, identical-pair totals equal expected
saved draws, unchanged triangle state/order/coverage. Actual Java formatter
extracted unchanged for arithmetic checks including new overlay values; CSV
39-name/303-index alignment checked. Android release build/signature/version/
ABI/profileable/alignment checks performed separately. No device UI, lifecycle,
timing accuracy or sharing runtime check available in this workspace.

Install over tv9, keep the current settings, play a race for a minute or two,
leave the game and Advanced > Share performance report. No new CPU profile
needed initially. Compare game-cycle CPU/elapsed, queue waits, GL idle and
present/swap to identify starvation/backpressure/presentation costs, and
inspect state-boundary frequencies before choosing a draw reduction strategy.
