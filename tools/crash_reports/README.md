# ARMv7 TV diagnostic release tv2

Target: Cepter R10G, Android 14. User wants an installable APK and minimal
manual work. Their tv1 APK renders the menu car but crashes as a race starts,
on different tracks and at lower graphics settings.

Version code 79, version 0.78-armv7-tv2. Same package and signing certificate
as tv1. This adds diagnostics; it does not claim to fix the race-start crash.

## How the user gets a report

Install over tv1 without uninstalling (retains imported game data), reproduce
the crash, and reopen the launcher. A dialog offers Share report or Save to
Downloads. Advanced > Crash report reopens the most recently captured report.
No developer mode, ADB or logging permission is needed. No report is uploaded
automatically. Saving to Downloads uses MediaStore on Android 10+.

CrashReports.java reads Android's ApplicationExitInfo for the app's :game
process. It collects crash/native-crash/ANR exits since the current app update,
and writes a ZIP atomically in the app's private crash-reports directory.
It uses a worker thread and keeps failures from blocking launcher startup.
The FileProvider is non-exported and scoped to that report directory.
Android may omit a retained trace; the ZIP then includes exit metadata and
an explicit trace-unavailable/error note. The reporter does not replace
Android's signal handlers or change native rendering/physics precision.

The automatic prompt is shown once for a newly collected exit. Closing the
prompt keeps the report available under Advanced. Device model/build/ABIs,
exit metadata and the retained trace are included. Game data is not included.

## Offline analysis after receiving the report

Native traces from Android 12+ are tombstone protobufs. The official AOSP
schema is saved as tombstone.proto, downloaded from:
https://android.googlesource.com/platform/system/core/+/refs/heads/main/debuggerd/proto/tombstone.proto
API documentation:
https://developer.android.com/reference/android/app/ApplicationExitInfo#getTraceInputStream()

Decode tombstone.pb using that schema (for example protobuf/grpc_tools).
Inspect the crashing thread, signal/code/fault address, frames, and mappings.
Use the matching tv2 native symbol archive saved in the checkpoint to resolve
relative PC addresses. The same compiler is NDK 28.2.13676358; llvm-symbolizer
or llvm-addr2line can resolve the .sym files. Retain the Build ID from the
verification evidence to avoid mixing symbol versions. Vendor GLES driver
frames may lack private symbols, but the caller and signal still help.

## Source comparison

Android upstream main was verified at f908f336a4dfd9c7116c872fb91018b5152a45ae,
the same baseline as tv1. Mac fork mnmt25/nfs-recompiled-mac was inspected at
ad67375. Its SIMDe layer adapts SSE intrinsics; Android's MMX is already portable
C++ here. The Mac page-size workaround disables memory protection on Apple
Silicon; it was not copied. No unverified SIMD or memory-protection workaround
was introduced into this diagnostic build.

## Build

Restore the checkpoint source and private signing identity. Fetch SDL
release-3.4.2 into third_party/SDL, then build:

    cd android
    ./gradlew assembleRelease -Parmv7Tv

Align and sign the resulting unsigned APK with the checkpoint key (alias
armv7-tv-release), as for tv1. Keep debugging disabled. Package version code
79 enables installation over tv1. Verify certificate, ARMv7-only libraries,
provider scope, release status, and native Build ID. Runtime collection still
needs the TV crash; compiling and package checks alone do not validate that
an OEM supplies the tombstone stream.
