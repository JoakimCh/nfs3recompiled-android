# Decisions and reasoning

This is a curated reasoning log. The changelog answers what changed; this file
answers why. Old hypotheses are not facts merely because they appear in history.

## D01 — Source checkpoint is Git, not a ZIP

Problem: transient workspaces lost source/context and checkpoint ZIPs accumulated
build output and symbols. Keep source, tests, pinned build requirements and these
notes in the fork. Keep APKs and exact native symbols outside source history.
Retain original signing material privately. A clone plus this index must be
sufficient to understand and rebuild source; it does not magically restore keys
or guarantee byte-identical binaries. Do not create another source ZIP by default.

## D02 — Preserve upstream history when integrating

Our base was alphaF0.78 (`f908f336`); the fork added alphaG0.78 and the owner's
README introduction (`49d2dea0`). Reconstruct changes on the old base, then merge
or rebase onto the new head. Do not overwrite the latest checkout with an old
snapshot. The first integration had one overlapping upstream/checkpoint file,
`src/lib/thrashrenderer.cpp`; every upstream-only change was verified retained.
See [integration history](history/INTEGRATION.md).

## D03 — ARMv7 crashes required alignment-safe access

A phone crash exposed packed vertex loads; the TV later faulted in vector
addition on a two-byte-aligned address. Use memcpy-backed packed/guest access,
not float pointer assumptions. Broad conversion of an unrelated projection loop
caused a directed-rounding regression, so that conversion was reverted. A fixed
crash site is not proof every packed access in the game is safe. Evidence:
[alignment notes](../../tools/crash_reports/ALIGNMENT_FIX.md) and
[tv4](../../tools/crash_reports/TV4_UPDATE.md).

## D04 — Keep the established game math contract

Specialize eligible default double-backed vector kernels once per call, retaining
operation order and fallback paths for other FPU modes. Disable contraction and
avoid global fast-math or a wholesale float conversion. Differential checks have
stated NaN-only exceptions; do not describe them as exhaustive bitwise equality.
Math preservation alone does not prove LAN compatibility. See
[vertex experiment](../../tools/game_checks/vertices/PERFORMANCE.md).

## D05 — Stable virtual controls, preserved game configuration

The game compares saved device descriptions and can reset bindings when their
shape changes. Keep two stable virtual pads, each with 16 button identities and
two axes, and migrate only recognized obsolete device descriptions. Do not
rewrite custom racing bindings into fixed presets. This retains part of the
original config.dat workaround; we have not removed DirectInput compatibility.
Touch evaluates the game's live action assignments instead of assuming fixed
keys. Owner-tested split screen works; do not generalize that to all pads.

## D06 — One owner for each digital input

Combining SDL and Android button identities caused A/B aliasing and duplicate
menu actions. Android-reported buttons own their route; do not also forward the
same event through SDL/keyboard conversion. Preserve analog input and SDL-only
fallbacks. Clear held state at lifecycle boundaries. Confirm and back each have
one configured button: Start/Select are not extra aliases. See
[tv6](../../tools/crash_reports/TV6_UPDATE.md).

## D07 — Capability-based device roles, not model fixes

TV remotes and phantom inputs must not occupy player slots. Share classification
between launcher and SDL bridge; route remote navigation as keyboard arrows,
Enter and Escape. Preserve button-only pads, hats, wheels and sticks. Standard
controller axes count separately from generic axes: the RC600U's GENERIC_1 plus
navigation/media evidence must not automatically make it a gamepad. Allow explicit
role overrides and descriptor-based assignment. A new eligible pad fills an
available slot; respect existing assignments/reservations. No Zero2 name/VID
special case remains. Test Android/SDL routing, not just Android tester labels.

## D08 — Conservative opaque shader; no geometry merging

A discard-free path can help the TV, but only when texture/vertex alpha and draw
state prove opacity. Unknown inputs use the original shader. Keep ordering,
depth, gamma/fog math and transparent behavior. Optional program failure falls
back. Adjacent batch merging did not improve practical FPS and was removed;
one-time VAO attribute setup was retained. See PERFORMANCE.md and
[tv11 details](../../tools/render_batch_checks/TV11_UPDATE.md).

## D09 — Minimal diagnostics by default

Stats and overlay are opt-in, independent of Debug mode. When both are off, do
not construct a performance session or activate native counters. Controller event
recording was removed after routing issues were resolved. Keep the on-demand
capability report in gamepad setup and crash reporting. Internal host trace
helpers may remain without becoming a player-facing recorder. Preserve user
preferences unless a requested migration explicitly changes them.

## D10 — Bonus unlocks change availability, not race achievements

config.dat is a validated 0x20f0-byte settings block. Five car bits at 0x1768 map
to El Niño, CLK-GTR, XJR-15, Pursuit Diablo SV and Pursuit El Niño, in that order.
Empire City uses a little-endian uint32 at 0x176c. The original cheat/reward logic
sets these availability fields; progress counters are separate. Change one car
bit without changing the others or unknown bits. Read current state, write a
unique sibling temporary file, sync, reread/verify allowed changes, check that
the original did not change, then atomically replace. No non-atomic fallback or
backup file. Relocking earned content is explicitly allowed by the owner.
Keep programmatic game-running/busy guards even though normal launcher flow
closes the game. See [implementation](../../android/app/src/main/java/dev/nfs3hp/port/BonusContent.java).

## D11 — Validate the packaged APK, not only build inputs

The tv20 controller page compiled but crashed because resource-table IDs and
packaged R dex disagreed. Clear generated app output before release resource
builds; retaining .cxx is fine. Every delivered APK must pass the existing final
resource-field gate. Stale ART/native intermediate files also broke a later
incremental packaging attempt; clean generated output resolved it without game
changes. Do not patch rendering or inputs to fix a build-cache failure.

## D12 — Keep Advanced compact and organized

Owner-approved tv23 uses pinned Unlocks / Performance / Debug tabs with separate
scroll bodies, compact adaptive per-car toggles and unlock information first.
Opaque shader optimization belongs under Performance, marked Experimental.
Redundant restart instructions are removed. Debug controls remain behind the
Debug-mode switch. No new launcher gamepad remapping layer is implied by this UI.
