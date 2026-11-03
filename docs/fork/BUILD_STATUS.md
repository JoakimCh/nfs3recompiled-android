# Verified build state

Update this file when a result changes. Record the source and evidence; distinguish
automated checks from device feedback. Older session details remain in Git history
and [release metadata](releases/). Usage is in [BUILD.md](BUILD.md).

## Workflow action upgrades (not yet tested)

After merging `launcher-tweaks` into main, pinned the Node 24 actions:
setup-java v6.1.0, checkout v7.0.1, and upload-artifact
v7.0.2. Artifact uploads explicitly retain ZIP archives for compatibility
with the publisher. The JDK/toolchain and signing identity are unchanged.

The action upgrades and 14-day retention configuration await a workflow run.
The owner plans to set the repository retention limit to 14 days to match.

## Latest verified APK: 0.78.32 / code 109 (universal)

[Run 41719407758](https://github.com/JoakimCh/nfs3recompiled-android/actions/runs/41719407758)
on 2026-11-03 built clean source
`c69b914bc1d11af7058adc7ec56d132f8bdb8da4` on `launcher-tweaks`.
That source is merged into main.

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

## Earlier validation

- On 2026-11-02, all 36 tooling tests passed locally, including fast-build
  promotion, metadata preservation and rejection of invalid builds. Hosted
  promotion from `apk-fast` remains unverified.
- [0.78.31 / code 108](releases/0.78.31.json), source
  `12503d4e4c9b8a5292d2d8cb4faef1236ae3f28c`, passed 32 tooling tests,
  19 launcher tests, the native gamepad pause regression, ARMv7 packaging and
  signing/resource/symbol checks. Its pause fix and expanded gamepad test panel
  still need device feedback.

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

Warm cache restoration passed in the 0.78.32 run above. Standalone hosted
`tests`/`check` modes remain unverified. Check each artifact's actual expiry.

## Remaining checks

- Verify hosted release promotion from an `apk-fast` build.
- Validate the updated action versions in a new main workflow run.
- Device-test 0.78.32 on ARMv7 and ARMv8: narrow/wide layouts, larger fonts,
  gamepad navigation and pause, Exit, intro versus attract playback, mirror
  detail and settings backups.
- For toolchain/native math changes, retain the known `trackVertices` discrepancy:
  tv27 compared 45 vertex functions across eight FPU modes with both NDKs;
  output was identical, with 44 passing and the same NaN/finite discrepancy in
  the remaining function. See [releases/tv27.json](releases/tv27.json).

