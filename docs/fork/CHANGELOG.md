# Fork changes

## tv27 — version 104

Updated the build toolchain and SDL from the shared tools/android-toolchain.json.
The Android SDL Java bridge is merged with the matching upstream release while
preserving fork-specific input routing. Runtime target SDK stays at 36.
Joakim reported testing the game without problems. The pre-existing host
trackVertices check discrepancy remains documented in WORKSPACE.md.

## tv26 — version 103 (test build)

Added an optional per-controller race pause combination under Gamepads → During
race: Back plus a selectable extra button. It overrides racing assignments only
when both are held, triggers once, and stays consumed through the pause menu
until both are released. Disabled by default; menu Back is unchanged. Racing
inputs remain immediate before the combination is completed.

## tv25 — version 102

Fixed gamepad-page content drawing over the header. The header stays fixed,
with controller content scrolling inside the area below it.

## tv24 — version 101

Gamepad setup uses the shared launcher header, back arrow and page background.
Added space above the input-report button. Fixed an unused recorder variable
that prevented the Android build after cleanup.

## tv23 — version 100

Advanced has pinned Unlocks, Performance and Debug tabs. Each bonus car has its
own compact toggle; unlock information appears first. Opaque shader selection
moved under Performance. Removed restart reminders. Joakim approved the interface.

## tv22 — version 99

Integrated the latest upstream menu/sound work. Added bonus-content switches,
improved remote classification and simplified Advanced. Performance capture and
overlay default off; controller recording was removed. Joakim reported it works.

## Earlier work

Added ARMv7 builds and fixed packed-data alignment crashes. Reworked controller
routing, player assignment and touch remapping. Added device reports, crash
reports and opaque shader optimization. Fixed a packaged resource mismatch that
crashed gamepad setup. Two-pad split screen was tested successfully.

## Cleanup branch

Consolidated the notes, removed obsolete recorder helpers/tests and made release
UI tests opt-in. No changes to controller routing or game math are intended.
