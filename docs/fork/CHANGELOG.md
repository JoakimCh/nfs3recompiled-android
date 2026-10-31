# Fork changelog

Entries describe the final behavior of each release. Detailed reasoning lives
in DECISIONS.md; experiment outcomes live in PERFORMANCE.md. Release identities
are under tools/release_checks. Dates are omitted where the original record does
not establish them; do not invent a precise chronology.

## tv23 — version 100 — 2026-10-31

Advanced split into pinned Unlocks, Performance and Debug tabs. Added five
independent, wrapping car toggles; moved unlock information above the controls.
Opaque shader selection is under Performance, labeled Experimental. Removed
restart reminders. Owner approved the interface; clean build, seven launcher
checks and final packaged resource checks passed.

## tv22 — version 99 — 2026-10-31

Integrated onto upstream alphaG0.78, preserving new menu/sound decompilation and
the fork README. Added bonus cars/Empire City unlock switches, the generic-axis
remote classifier refinement and Advanced cleanup. Stats/overlay default off;
controller recording removed; device capability report retained in gamepad setup.
Owner reported this APK works.

## tv21 — version 98

Fixed stale packaged Android R fields causing the gamepad page to crash. Added
the mandatory final APK resource gate and launcher Java crash capture/reporting.

## tv19–tv20

Unified device roles across Android/SDL: remotes navigate as keyboards and stay
out of gamepad slots; button-only controllers remain supported. Added explicit
roles/player assignment, capability report and redesigned gamepad setup.

## tv17–tv18

Replaced the Zero2-specific repair with generic per-controller menu testing and
configuration. Default hats and X/Y both navigate. Confirm/back each use one
button; removed Start/Select aliases and separate assignment-cancel button.

## tv12–tv13

Touch follows the game's live racing bindings. Simplified launcher control
settings and retained in-game remapping. Owner verified two-pad split screen.

## tv11

Added conservative opaque shader optimization and removed ineffective batch
merging. Owner later reported improved TV frame rate; gain was not quantified.

## tv7–tv10

Added phone-friendly profiling, performance counters, overlay, phase timing and
draw-boundary diagnostics. Tried adjacent batch merging; later removed it.

## tv5–tv6

Improved axis menu navigation and native gamepad remapping. Fixed A/B aliasing,
duplicate/queued menu actions and missing vertical-axis capture.

## tv1–tv4

Established the ARMv7 release build and crash reporting. Fixed packed-data
alignment crashes, specialized eligible vector arithmetic, and restored the
cheaper original mirror view. Preserve precise fallback math paths.
