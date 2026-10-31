# NFS III ARMv7 tv7-profile

Install nfs3-0.78-armv7-tv7-profile-release.apk over tv6. Same package and
original certificate; data and gamepad assignments remain. Code 84.
This is an optimized, non-debug release with `<profileable android:shell="true"/>`.
No automatic recorder is built into the game. Native libraries are identical
to tv6; no game, graphics, math, networking or controller behavior changes.

## Phone only: built-in System Tracing (easiest)

1. Enable Developer options. Open Developer options > System Tracing
   (Samsung wording/location may vary).
2. Enable its Quick Settings tile if available. Leave normal tracing categories
   enabled; include scheduling/CPU frequency/graphics categories when offered.
3. Start the game and begin a race. Start recording using the tracing tile.
4. Drive for about 30–60 seconds, stop using the tile, then share the saved trace.
   Send the actual trace file, not a screenshot. Android 10+ uses Perfetto format.

This does not require a laptop, root, USB debugging or a local ADB app.
It provides scheduling, frequency and system/frame timing information. It is
not equivalent to a full native-function callstack sample. A profileable flag
alone does not add every game function as a trace section.

## Phone only: native CPU samples using a local ADB shell (optional)

A local ADB app such as LADB can pair with the phone's own Wireless debugging
service. This supplies an ADB shell without a laptop. It needs pairing and
working wireless-debugging support. Device/OS compatibility is not guaranteed.
A normal terminal app does not have the same permissions.

1. Install this profileable APK; enable Wireless debugging and pair your local
   ADB app using its instructions. No root is required for supported profileable
   app sampling. A Wi-Fi connection is generally needed for Wireless debugging.
2. Extract record-phone.sh from this kit into the phone's Download folder.
3. Start a race, switch to the local ADB shell and enter:

   sh /sdcard/Download/record-phone.sh

4. Switch back to the running race within 15 seconds. Drive for 45 seconds.
5. Share the resulting Download/nfs3-<timestamp>.perf.data file here.

The script uses the system simpleperf, samples the :game process at 200 Hz
with DWARF callstacks (-g) and the user-space CPU-clock event, and writes a
new timestamped file. It does not alter device security settings or sysctls.
If simpleperf is absent or Android refuses the recording, keep the error text;
use System Tracing or Android Studio instead. The command is based on AOSP's
supported --app/-p recording options but has NOT been tested on the user's phone.
The 15-second preparation wait is only in the on-device helper, not in the game.

## Computer: Android Studio

Enable USB debugging, connect/authorize the phone, install this APK and run
it. In Android Studio Profiler select dev.nfs3hp.port.armv7tv:game and use
Callstack Sample (not Java/Kotlin method instrumentation). Capture about
30–60 seconds of actual racing and export the recording. UI labels vary by
Android Studio version. Matching unstripped ELF libraries are in symbols/;
keep their Build IDs with this APK. Native-debug-symbols.zip is also supplied.

## What to record

Use the ARMv7 APK on the phone, not an ARM64 build, and note track, car,
resolution, graphics settings, frame cap and phone model. A warm-up lap helps
separate loading/shader setup from steady racing. Do not compare profiler
recording FPS directly to unprofiled FPS: sampling has overhead. Phone CPU
hotspots can guide shared-code changes, but the TV may have different CPU,
GPU, memory bandwidth, thermal and driver bottlenecks.

## Build and verification

Gradle: assembleRelease -Parmv7Tv -PprofileNative
Without -PprofileNative the shell profiling flag is false. Debug remains off.
Matched symbols and native Build ID, original signing certificate, package,
version, ARM32-only libraries, APK alignment and profileable=true verified.
No physical-device capture has been performed here.

Primary documentation:
https://developer.android.com/topic/performance/tracing/on-device
https://developer.android.com/guide/topics/manifest/profileable-element
https://android.googlesource.com/platform/system/extras/+/refs/heads/main/simpleperf/doc/executable_commands_reference.md
https://github.com/tytydraco/LADB
