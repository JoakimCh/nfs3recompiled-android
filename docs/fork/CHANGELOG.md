# Fork changes

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
