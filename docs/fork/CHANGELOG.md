# Fork changes

## Unreleased release publishing

Added a manual Publish APK release workflow. It promotes an existing successful
signed APK run to a prerelease or release with its matching symbols, verification
metadata and checksums. No rebuild or signing credentials are needed. Expired
artifacts, inconsistent metadata and existing tags stop publication. Ten release
helper tests and workflow structure checks passed; hosted publication remains
untested. The workflow uses the built-in token with explicit job permissions.

## Unreleased build automation

Added shared setup/tests/check/APK/signing commands, complete Linux workspace
bootstrap, cached manual workflow modes and feature-branch support. Launcher-only
tests skip native configuration; native builds use bounded Ninja job pools.
Signing credentials are checked early and used only in APK mode. Added tooling
filesystem regressions and recovery/status documentation. Local tests/check/APK
modes passed. The first hosted APK run also passed, including all 14 launcher
tests, cold setup, signing and artifact uploads; see BUILD_STATUS.md.

## tv28 — version 105

Joakim reported testing build 28 without problems on 2026-11-01.

Simplified launcher labels and help, clarified file deletion, and shortened the
race pause shortcut description. Controller bindings use readable button names;
raw Android input details can be expanded when troubleshooting. Obsolete
controller instructions were removed. Updated the revised wording in all 18
launcher translations. Ordinary controls help and the revised controller-page
descriptions now use translatable resources; controller setup follows the chosen
launcher language. Added translation maintenance guidance in TRANSLATIONS.md.

Launcher settings backups now include per-controller menu controls, race pause
shortcuts, device types, saved player assignments and touch editor snapping.
Controller identities are preserved exactly, including disconnected devices.
Version 1 backups remain importable without clearing these newer settings.
Version 2 can also back up and restore a default setup. Imports validate stored
types and stop if the automatic backup cannot be written. Game file references
and launcher language remain local.

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
