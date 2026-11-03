# Fork changes

## Unreleased build automation

Manual workflows build ARMv7, ARMv8 or a universal APK and publish an existing
verified build with its matching symbols, metadata and checksums. All targets
share the fork package, release version and signing key. Promotion supports
older ARMv7 artifacts and preserves explicitly skipped tests in `apk-fast`.

Shared local and hosted commands provide tool bootstrap, launcher tests and
native builds with bounded job pools. Signing credentials are checked early and
kept outside caches. Workflow actions use pinned Node 24 releases; all artifacts
request 14-day retention. Release notes come from the APK source's versioned
changelog entries.

## 0.78.34 — version 111

Advanced → Performance groups race precision with an ARMv7-only experimental
fast-vertex switch. Extended precision and compatible ARMv7 calculations remain
the defaults. Selecting precision clears conflicting Debug overrides; Reset
performance settings restores the defaults. Broader arithmetic experiments stay
under Debug. Launcher notes about applying settings on a later launch are removed.

Performance reports identify the running ABI and effective arithmetic settings,
and append vertex compatible/fast/retry pass counters, also shown in the overlay.
Settings backup format 5 carries the new choices; older imports preserve them.

## 0.78.33 — version 110

File pickers use the Activity Result API and preserve outstanding requests across
activity recreation. Duplicate picker launches are blocked; cancellation allows
retrying. Advanced tabs use the supported Material component.

ARMv7 vertex calculations use emulated single-precision arithmetic where Clang
cannot guarantee host floating-point exception tracking. ARMv8 retains the strict
exception-based retry. Camera store defaults and announcer comparisons are
explicit, and launcher tests permit their native-library access.

## 0.78.32 — version 109

The launcher menu uses two columns when space permits, with Exit at the bottom
and the running ARMv7/ARMv8 architecture beside the version. Smaller windows and
larger text keep a single menu column.

Advanced has a Tweaks tab for startup preferences and unlocks. Skip game intro
is off by default and leaves attract-mode movies available. Performance adds
Full-detail rear-view mirror, off by default on both architectures. Launcher
backup format 4 carries both settings; imports of older formats preserve them.

## 0.78.31 — version 108

Gamepad input details and indicators expand with Test gamepad and collapse with
Stop testing. Removed the separate input-details toggle; assignment controls stay
visible. Updated all 18 translations.

The pause shortcut keeps Escape held while both assigned buttons are held, with
a minimum delivery hold for brief overlaps. Previously it released Escape on the
next input poll, so races could miss it. Either button order works with any gap
between presses. Leaving the race context releases Escape immediately; the pair
still triggers only once until both controls are released.

## 0.78.30 — version 107

Pause assignment shows the first button while waiting for the second, with prompts
and unsupported-input feedback beside the pair. Confirm, Back and the shortcut
share button-only validation and explanatory text. Directional menu assignments
retain button and axis support. Updated all 18 translations.

## 0.78.29 — version 106

Versions use a numeric format, with shorter ARMv7 filenames and numeric release
titles. Performance profiling remains available without a version suffix.

Menu assignment returns to navigation and consumes the press until release.
Pause shortcuts capture two independent, different buttons. Cancel keeps the old
pair; Disable clears it. Old Back-plus-extra settings migrate to fixed pairs, so
menu Back changes no longer affect them. Updated all 18 translations. Backup
format 3 includes both buttons and imports formats 1 and 2; format 2 imports
correctly replace existing pairs.

## tv28 — version 105

Simplified launcher labels/help, file-deletion wording and the pause description.
Controller bindings use readable button names; raw input details can be expanded.
Updated all 18 translations and made ordinary controls help translatable.
Controller setup follows the selected launcher language.

Settings backups include per-controller menu/pause controls, device types, player
assignments and touch snapping, preserving disconnected controller identities.
Version 1 imports preserve newer settings; format 2 can restore a default setup.
Imports validate types and stop if the automatic backup fails. Game file
references and launcher language stay local.

## tv27 — version 104

Updated the toolchain and SDL through tools/android-toolchain.json. Merged the
matching SDL Java bridge while preserving fork input routing. Target SDK stays 36.

## tv26 — version 103 (test build)

Added a per-controller race pause combination: Back plus a chosen extra button.
Both held overrides racing assignments once, staying consumed through the pause
menu until release. Disabled by default; menu Back and immediate racing inputs
remain unchanged before the combination is completed.

## tv25 — version 102

Fixed gamepad content drawing over the header; controls scroll below it.

## tv24 — version 101

Gamepad setup uses the shared header, back arrow and background. Added space
above the input-report button and fixed an unused variable blocking Android builds.

## tv23 — version 100

Advanced has pinned Unlocks, Performance and Debug tabs. Bonus cars have individual
toggles, with unlock information first. Opaque shader selection moved under
Performance. Removed restart reminders.

## tv22 — version 99

Integrated upstream menu/sound work. Added bonus-content switches, improved remote
classification and simplified Advanced. Performance capture/overlay default off;
controller recording was removed.

## Earlier work

Added ARMv7 support, packed-data alignment fixes, controller/player routing,
touch remapping, two-pad split screen, device/crash reports and opaque shader
optimization. Fixed packaged resource mismatches. Consolidated notes, removed
obsolete recorder helpers/tests and made release UI tests opt-in.

