# ARMv7 TV fork

The integrated source includes the original project's alphaG0.78 changes plus
our ARMv7 and controller work. The owner confirmed tv22 works. The current test
build is versionCode 100 / tv23: Advanced now has Unlocks, Performance and Debug
tabs, independent bonus-car toggles, and pinned tabs above scrolling options.
The clean Android build and seven launcher checks pass; tv23 awaits device testing.

## Build

Use JDK 21, Gradle wrapper 9.3.1, Android SDK platform 36 / build-tools 36.0.0,
NDK 28.2.13676358 and CMake 3.22.1. SDK/NDK dependencies are pinned in Gradle.
Clone SDL release-3.4.2 into third_party/SDL (ignored in git):

```sh
git clone --depth 1 --branch release-3.4.2 https://github.com/libsdl-org/SDL.git third_party/SDL
cd android
./gradlew assembleRelease -Parmv7Tv --max-workers=2
# Optional shell profiling, still optimized and non-debug:
./gradlew assembleRelease -Parmv7Tv -PprofileNative --max-workers=2
```

Without -Parmv7Tv, the upstream ARM64 ABI/package is retained. The ARMv7 package
is dev.nfs3hp.port.armv7tv so it can coexist with upstream. Do not enable x87Exact
or wideFpu for this ARMv7 build. Native code preserves the existing math policy;
no fast-math experiment or frame merging is enabled. Opaque shader optimization
is on by default. Performance collection and overlay default off.

Before a release build after changing Android resources, remove android/app/build
(keep .cxx if desired). A stale generated R class previously compiled successfully
but crashed the controller page. Always run the final artifact gate:

```sh
python3 tools/game_checks/gamepad/check_apk_resources.py APK BUILD_TOOLS APP_COMPILE_R_TXT REPORT_JSON
```

Use the release's actual APK, SDK build-tools directory and generated app-owned
R.txt; do not substitute outputs from another variant. Run focused UI checks with
./gradlew testReleaseUnitTest -Parmv7Tv. Sign externally with the original private
certificate to update installed TV releases. Those credentials are intentionally
absent from GitHub. Verify signature, ABI, version, non-debug/profileable flags,
16 KiB ZIP alignment and native BuildID before delivering any APK. Retain exact
matching full native symbols separately for crash decoding.

## Current behavior

Shared Android/SDL device roles exclude remotes from player slots while keeping
button-only gamepads, sticks and wheels. Remotes navigate as keyboard inputs.
Per-device menu directions/confirm/back and explicit player assignment are in
Gamepad setup, with a capability report there. Touch follows in-game remapping;
stable virtual devices preserve custom bindings. No device-specific Zero2 fix.
Advanced groups independent bonus-car/Empire City toggles, performance tools
and debug/crash options in three tabs. Unlock information appears above the
compact car toggles. Opaque shader selection is under Performance, labeled
Experimental. Redundant restart reminders are removed. Controller event recording and
its duplicate report buttons have been removed.

## Integration and verification

The checkpoint was reconstructed on f908f336, then rebased onto the fork's
49d2dea0 (alphaG0.78 plus its README introduction). Git reported no conflicts.
Newer menu/sound code and generated disassembly are retained. See
INTEGRATION.md for focused verification and limitations. Historical per-release
notes under tools/ document earlier work; do not interpret old test results or
references to private checkpoint paths as current build instructions.
