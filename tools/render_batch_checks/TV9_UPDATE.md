# tv9-profile: performance controls, overlay and shareable statistics

Release version 0.78-armv7-tv9-profile, code 86. Same ARMv7 package and private
release signing identity; install over tv8, retaining game data and bindings.
Non-debug, optimized and shell-profileable. No new FPS improvement is claimed.

Advanced now has independent collection and overlay switches, both initially
on in this measurement release. Neither needs Debug mode. Changes apply on
the next game launch. Merge identical rendering batches defaults on (tv8
behavior), can be turned off for comparison, and has a reset-to-defaults button.
The immutable vertex attribute setup optimization is always retained.

The non-interactive Android TextView overlay updates once a second: FPS,
mean presentation interval, p95 interval bound, GL draws/frame, merged
batches/frame, GL submission thread CPU ms/frame and game buffer dimensions.
The 1-ms histogram gives a bounded estimate, not an exact percentile. Frame
intervals are successful completed SDL swaps, including menus; they do not
measure GPU execution. Intervals >1 second are separately counted as gaps.
Pause clears the last-frame anchor, avoiding a background pause as one frame.
Submissions crossing snapshot boundaries make short-window per-frame ratios
approximate. Both overlay and collection overhead are included in measurements.

Header-only perfstats uses a private mutex-protected cumulative counter set,
not the existing game-thread DrawCounters that debug traces reset. One update
per drawPending, one per successful swap and one UI snapshot/second. No lock
or timer per triangle or per actual GL draw. No game math/input changes. When
both collection and overlay are off, timing/counter updates are skipped.
Submission elapsed is monotonic wall time including waits; submission CPU is
CLOCK_THREAD_CPUTIME_ID on the GL thread inside drawPending. Neither includes
the full game loop, present pass or GPU execution. Merge toggle is independent
of statistics and enabled state, read once from the environment per process.

Reports: Advanced > Share performance report > Share or Save to Downloads.
Game process saves metadata.json and cumulative samples.csv privately on a
worker thread; one row/sec plus a pause snapshot. Each append is closed.
A cross-process file lock gives report export a complete file snapshot, never
a partially written row. At most 14400 samples are saved per session (~4 hours);
the overlay continues beyond this limit. Latest session remains available after
a crash (roughly the last second can be lost). The previous session is retained
privately when a new collected session starts; the UI exports the latest only.
Only the last exported ZIP is retained, no game files included, no automatic
uploads. No storage permission required on Android 10+. Older versions use Share.

Report metadata includes version, device, Android, ABI, FPS cap, selected launcher
display preferences, Debug mode/options, overlay and batching states. Frame rows
include buffer dimensions. It does NOT automatically identify races, track, car,
camera, all in-game quality settings, CPU frequencies, thermal state or GPU time.
Keep comparable conditions when evaluating an experiment. Raw CPU profiling is
still optional and supported, but ordinary use/report export needs no laptop.

CSV order (264 fields): monotonic_ns, frames, intervals, interval_sum_ns,
batches, gl_draws, vertices, submissions, submission_elapsed_ns,
submission_thread_cpu_ns, excluded_gaps, width, height, frame_ms_bin_0..250.
Counters are cumulative within one process/session. Differences between rows
give window totals. FPS=1e9*delta(intervals)/delta(interval_sum_ns), average
frame ms=delta(interval_sum_ns)/1e6/delta(intervals), triangles=vertices/3,
merged=batches-gl_draws. Histogram bins 0..249 correspond to [i,i+1) ms;
250 covers 250..1000 ms. Avoid mixing presentation counts and triangle counts
across different windows. Raw monotonic timestamps can align phone CPU samples.

Validation: perf_check.cpp checks enabled/disabled capture, on/off experiment,
known frame intervals/histogram, counter totals, pause suppression, loading gap
handling, and consistent snapshots during 100000 concurrent submission updates;
UBSan enabled. Original million-batch state/order/coverage check retained.
The actual Java overlay formatter is extracted unchanged for a host check of
FPS, average/p95, draws, merges, CPU/frame, empty frames and overflow histogram.
Android release build and signed APK package/version/ABI/cert/profileable checks
are completed separately. No physical phone/TV UI, lifecycle or file-sharing
runtime test is available in this workspace; device behavior remains untested.

Next: install, play normally, then leave the game and export the report in
Advanced. To compare batching, disable Merge identical rendering batches,
relaunch and play similar conditions. Export each session before starting the
next collected session. There is no need to repeat simpleperf to get these stats.
