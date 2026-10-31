# Resume: ARMv7 tv21-profile — packaged R class fix and launcher Java crash capture

Version98 / 0.78-armv7-tv21-profile. Optimized non-debug ARMv7, shell-profileable,
original package/certificate, install over tv20. Source already patched; never
reapply history patches. Native C++/renderer/math/input unchanged. libmain BuildID
may equal tv18–20 because this is Java/build/crash-report infrastructure only.

User: tv20 gamepad page crashes entering on Samsung A266B Android16; no crash
report. Device-capability export WORKS (attached nfs3-input-devices-1793399441899.zip),
valid schema1 with no gamepad connected, two media/power key devices as remote,
virtual/touch devices other. This is a PHONE inventory, not TV/RC600U evidence.
Do not infer RC600U capabilities from it. Compact findings in current evidence.

DEFINITE DELIVERY MISMATCH FOUND IN ACTUAL TV20 APK: resources contain
ui_input_button0x7f05001d and ui_input_indicator0x7f05001e, but packaged
Ldev/nfs3hp/port/R$drawable has neither field. It still holds ui_primary_button
at0x7f05001d although actual resource is0x7f05001f. Page's first button accesses
missing field -> NoSuchFieldError before controller enumeration. Java compilation
and resource-table checks separately passed, but runtime R dex was stale. No
phone stack supplied; binary mismatch establishes the failure without guessing
input-device behavior. New resource gate rejects old tv20 with exactly3 mismatches.
Fresh-resources Android-hosted no-controller startup already passed before fix,
which explains why source tests alone couldn't catch broken APK delivery.

FIX: build.py now deletes only generated app/build before release, preserves
native .cxx object cache. Fresh runtime resource class/dex packaged. finish.py
runs source/tools/game_checks/gamepad/check_apk_resources.py on SIGNED APK before
marking release verified. It resolves final APK resource IDs with aapt2, parses
actual DEX R fields with dexdump, and compares every app-owned non-styleable int
resource from compile R symbols. All296 checked in this release, no mismatches.
This gate is required for future nonminified releases, especially after changing
resources. Don't weaken to class timestamps/string presence/resource existence.
No UI layout rollback or controller mapping workarounds. tv20 report/UI retained.

WHY NO REPORT: CrashReports filtered only :game and ignored launcher process.
Now includes own main and own named processes for Java/native/ANR exits; can
collect prior-version exits with explicit installed-version caveat. Native trace
handling unchanged. On SDK26+ new NFS3Application installs JavaCrashLog before
activities, saves bounded UTF8 stack+causes/version/process/thread/time to synced
atomic .pending file, ALWAYS delegates to original Android exception handler.
No native signal handlers and no automatic uploads. One capture per process;
failed disk write must not interfere with original termination. CrashReports
packages saved Java stacks first, independently of Android30 exit-history API,
marks consumed logs, then uses OS history fallback. Old game-process native
report path retained. Existing Advanced Crash report now titled App crash report.
New Java captures apply from tv21 onward; old tv20 stack may be absent in OS.

VALIDATION: Robolectric4.17/JUnit4.13.2, release variant (AGP9 only creates tested
build type unit tests; testBuildType=release), JDK21 add-opens. Six Android-hosted
tests across SDK34/36 pass: no-controller startup/measure/layout/expand/pause-resume;
button-only controller startup/layout, Test state, Assign/Cancel arming, saved
button assignment and Back-stop; bounded saved Java exception collection ZIP,
original handler delegation and duplicate suppression. SDK native key names are
numeric in Robolectric; assert actual saved binding code rather than a symbolic
label unavailable in host runtime. No physical/emulator execution claimed.
JavaCrashLogCheck separately proves bounded stack/cause metadata, single capture,
handler delegation even on storage failure. Existing Java profile/policy/remote/
touch/config/buffer checks pass. Signed release version/ABI/cert/nondebug/
profileable/16KB alignment/BuildID/JNI checks plus final APK R gate pass.

Host UI task script tools/tv21/test-ui.py, tests in android/app/src/test/java.
Build release BEFORE signing; don't run build.py concurrently with test-ui or
other Gradle operations because it clears generated app/build. Save test XML/log
outside generated outputs before clean release. Unit-test dependencies stay out
of APK and checkpoint toolchain caches. .cxx keeps native rebuild efficient.
If immutable plugin transforms fail from workspace temp files, with builds stopped
remove only toolchain/gradle-home/caches/9.3.1/transforms and retry. Never alter
product behavior for generated cache failures. Pinned SDK36/NDK28.2.13676358/
CMake3.22.1/JDK21/Gradle9.3.1/SDL3.4.2 retained.

User previous TV feedback: both D-pad modes work with tv19; RC600U still default
controller/player1 and Zero2player2, role override available. Opaque shader
selection improves perceived TV frame rate, unquantified. No classifier/input/
renderer changes this release; don't claim RC600U fixed. Capability report still
available Advanced -> Save input device report, no game/recording required.
Native SDL live input report separate; tester raw inputs remain Android/shared
ControllerProfile, not full native SDL tester. tv20 ergonomic setup retained.

Checkpoints stay lean (ARCHIVE_POLICY.md); APK/matching full symbols separate.
Keep original private signing material confidential. Current text evidence only;
full tools/downloads/raw captures/build outputs excluded. Older source/history
in compact patches and history notes; never apply those to already patched source.
