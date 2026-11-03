# Verified build state

Update this file when a result changes. Record the source and evidence; distinguish
automated checks from device feedback. Older session details remain in Git history
and [release metadata](releases/). Usage is in [BUILD.md](BUILD.md).

## Workflow action upgrades (not yet tested)

After merging `launcher-tweaks` into main, pinned the Node 24 actions:
setup-java v6.1.0, checkout v7.0.1, and upload-artifact
v7.0.2. Artifact uploads explicitly retain ZIP archives for compatibility
with the publisher. The JDK/toolchain and signing identity are unchanged.

No tests, builds or workflow dispatches were run for this action update.
The repository retention limit still needs its owner to raise it to 90 days;
the workflow requests 14 days for APKs/reports and 90 days for symbols.

## Latest verified APK: 0.78.32 / code 109 (universal)

[Run 41719407758](https://github.com/JoakimCh/nfs3recompiled-android/actions/runs/41719407758)
on 2026-11-03 built clean source
`c69b914bc1d11af7058adc7ec56d132f8bdb8da4` on `launcher-tweaks`.
That source has now been merged into main.

- All 40 tooling tests and 20 launcher tests passed, with no launcher failures,
  errors or skipped tests.
- Both ARMv7 (`armeabi-v7a`) and ARMv8 (`arm64-v8a`) compiled and linked.
- The universal APK passed signing, package/version, selected ABI/ELF,
  resource, ZIP alignment and matching native symbol verification.
- Reports, the signed APK and exact symbols uploaded successfully. Warm Gradle,
  Android-tool and SDL caches restored successfully.
- Artifacts were capped at one day, expiring at 2026-11-04 21:10:49 UTC.
  Raising retention does not extend these existing artifacts.
- No device-test result or hosted release-promotion result for this revision
  has been reported. The action upgrades above are newer than this verified run.

The APK contains the adaptive menu grid, Exit, running architecture label,
intro preference, Tweaks/unlocks grouping and mirror detail toggle. Both new
preferences default off and travel in backup format 4; older imports preserve
them. Device checks should cover narrow/wide layouts, larger fonts, gamepad
navigation, Exit, intro versus attract playback, mirror detail and backups.

## Publisher and documentation update

The publisher accepts `apk-fast`, preserving skipped-test metadata and handling
release notes without a test count. Normal `apk` builds still require passing
tests; existing artifact checks remain in place. Documentation was consolidated
and superseded status removed.

All 36 tooling tests passed locally on 2026-11-02, including fast promotion,
metadata preservation, release-note handling and rejection of invalid builds.
No APK rebuild was needed. Hosted promotion from a fast build remains unverified.

## Previously verified APK: 0.78.31 / code 108

Source: `12503d4e4c9b8a5292d2d8cb4faef1236ae3f28c` on main, clean tree.
Includes the race-pause reliability fix and expandable gamepad testing panel.
Metadata: [releases/0.78.31.json](releases/0.78.31.json).

- All 32 tooling and 19 launcher tests passed locally. Launcher coverage includes
  panel visibility, stopping with Back, assignment feedback and held-button release.
- The native SDL gamepad regression passed: both button orders, a one-second gap,
  rapid polls, menu entry, release/repress, no repeated activation and existing
  racing/per-player behavior. It reproduced the missed pause before the fix.
- ARMv7 compilation/linking and APK assembly passed. Packaging used
  `apk-fast --unsigned` after the separate test run, then `sign` with the restored
  original private files. The generated build validation records skipped tests
  for that packaging command; the separate successful tests are recorded here.
- Original certificate, package/version, ARMv7 libraries, 16 KiB alignment,
  non-debuggable/profileable state and matching symbols were verified.
  All 313 packaged resource fields matched; all 19 language resource sets parsed.
- The signed APK was delivered. No device-test result for this revision has
  been reported.

## Device feedback

Joakim reported that the two-button pause/assignment build worked before the
first-button feedback and latest reliability changes. Its exact APK/run identity
was not recorded, so it does not validate 0.78.31.
The original local tv28 APK was also reported working without problems;
[releases/tv28.json](releases/tv28.json) identifies that binary.

## Workflow and setup evidence

| Check | Evidence |
| --- | --- |
| Cold hosted APK build and signing | [Run 41324391872](https://github.com/JoakimCh/nfs3recompiled-android/actions/runs/41324391872), source `5f68209a56b0dc4d26974b80191466f761655f3d`; tv28, 3 tooling and 14 launcher tests, APK/symbol/report uploads passed |
| Release publication and built-in token permissions | [Run 41326807799](https://github.com/JoakimCh/nfs3recompiled-android/actions/runs/41326807799), workflow source `e93c02e5891770b86a0bee0be76ea8b096157731`; all five release assets published |
| Changelog-based release notes | Local helper checks and a tv28 preview passed; Joakim later reported the revised workflow worked and liked the notes. Retry run ID was not recorded |
| Local shared runner | Tests, native check and signed APK modes passed; isolated launcher bootstrap passed without an NDK. Source `f674acd863ccb3f86bc4052a00e58d39e849f0b9`; later 0.78.31 evidence is above |
| Fast-mode tooling | Earlier 32-test suite covered runner/signing paths and fast metadata; local unsigned fast packaging passed for 0.78.31. Hosted fast mode remains unverified |

The hosted APK run saved caches after cold setup. Warm hosted cache restoration
and standalone hosted `tests`/`check` modes have not been verified here.
Repository artifact retention was observed at one day; inspect each run's expiry.

## Remaining checks

- Verify hosted release promotion from an `apk-fast` build.
- Validate the updated action versions in a new main workflow run.
- Device-test 0.78.32 on ARMv7 and ARMv8, including the new launcher settings
  and the existing pause/gamepad controls.
- For toolchain/native math changes, retain the known `trackVertices` discrepancy:
  tv27 compared 45 vertex functions across eight FPU modes with both NDKs;
  output was identical, with 44 passing and the same NaN/finite discrepancy in
  the remaining function. See [releases/tv27.json](releases/tv27.json).

