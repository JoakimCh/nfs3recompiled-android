# Resume: ARMv7 tv20-profile — device report and ergonomic setup

Version97 / 0.78-armv7-tv20-profile. Optimized non-debug ARMv7, shell-profileable,
original package/certificate. Install over tv19; settings preserved. Source already
patched; never reapply history patches. Native renderer/math unchanged; libmain
BuildID matches tv18/19 because this update is launcher/report Java/resources only.

USER HARDWARE FEEDBACK (2026-10-30): tv19 both D-pad modes now work on Cepter R10G
TV. Screenshot still shows RC600U classified Game controller(default)/Player1,
Zero2 Player2. Other IR_rca/rtk_keypad/virtual-remote/virtual-search Remote/keyboard.
Manual RC600U role override remains available. Don't claim its exact capability
reason until report arrives; no name blacklist or new classifier behavior added.
User also reports TV frame rate improves with opaque shader selection. This is
positive physical-device feedback for retained tv11 optimization, subjective and
unquantified: no FPS numbers or controlled comparison supplied. Preserve default
opaque optimization, don't claim measured percent gain. Evidence feedback JSON.

New InputDeviceReport, available Advanced -> Save input device report, plus setup
page link. Dialog Share / Save to Downloads creates nfs3-input-devices-<ms>.zip
with report.json and README. Works from launcher without starting game, enabling
recording or native SDL initialization. Schema1 reports app/version, Android/
manufacturer/model/hardware/build fingerprint/ABIs, every Android input device
(including virtuals), descriptor, VID/PID/hex, source flags+names, keyboard type,
controller number, vibrator/microphone/external status, all supported Android
keycodes up to platform max, all motion ranges with min/max/flat/fuzz/resolution/
source, exact classifier decision/reason and capability counts, saved role/effective
role, menu profiles, and resolved/saved player assignments. Snapshot only, no
recorded key/text input. Clear Android inventory provenance; live native SDL
mapping/routing still belongs to existing Controller input report.

InputDevicePolicy refactored into Decision enum with role/reason, preserving all
existing classification decisions. InputDeviceRoles.Capabilities supplies the
same counts/Decision to eligibility and diagnostics (no duplicated reason logic).
The report doesn't change roles/assignments. Scoped FileProvider device-reports/
path; ZIP written to partial then renamed, MediaStore pending copy/close/publish,
explicit user share intent only. Atomic export guard prevents concurrent writes.
API28/29 metadata and Downloads guarded for minSDK26. Generated snapshots stay in
app-private device-reports and user chooses external save/share. Failures toast;
per-device collection errors included rather than aborting entire inventory.

ControllerSetupActivity redesign: centered content max1000dp, dark panels, compact
side-by-side Player1/2 cards with Change dialog (Automatic or eligible controller).
Controllers first as expandable selection cards showing player membership; only
one selected device's controls shown. Remotes/other inputs collapsed behind count;
expand for role correction. Selected device panel has Test input, Menu controls,
Device role sections, six nonfocusable live indicators, Android raw-input line,
Start/Stop test and capture instructions. Fixed width Assign/Cancel and Default
buttons retain visible binding codes. Reset affects selected controller only.
TV focus3dp gold border; selected card1dp gold; active/capturing controls indicated.
Focus tags restored when lists rebuild. Remote Back cancels assignment/stops test
before leaving page. Pause stops test/releases state/clears indicators. Role/player
and live input behavior from tv19 preserved; actual capture path unchanged.

Checks: production Java profile/role policy/remote navigation/touch/config/buffer
host tests pass, classifier reason checks included. Release Gradle build/lint pass.
APK original certificate, version/ABI/4libs/nondebug/profileable/16KB alignment,
BuildID/JNI match. Current report/UI Java class mtimes verified. APK DEX has report
schema/reasons/entry and new setup sections. Optimized resource table resolves
focus/indicator drawables and FileProvider path; note aapt shortens filenames, so
don't assume literal res/drawable filenames inside APK. ZIP checksum/CRC policy
verified by packager. Physical-device/emulator new UI/export not executed here;
Android save/share requires user's normal device use. Do not claim end-to-end
hardware validation. Native C++ unchanged from prior checked input regression run.

NOT a complete migration of tester to native SDL: tester raw labels remain Android,
ControllerProfile actions and shared role policy agree with game/SDL Android
bridge. Button-only controllers still accepted; remotes keyboard only; explicit
roles/pins retained. tv19 full source notes in history/tv19-start-here.md.

Tools/tv20 setup/build/finish/package pin JDK21,Gradle9.3.1,SDK36/buildtools36,
NDK28.2.13676358,CMake3.22.1,SDL3.4.2. Kotlin incremental off. Stop builds before
removing generated transforms/dex/ART caches if workspace cache corruption recurs;
no product workaround needed. Checkpoints lean; APK/exact symbols separate. Keep
original private signing materials confidential. Renderer precision/ARM alignment,
touch live assignments, controller routing and user-tested split screen preserved.
Input recorder remains off by default. No new profiling requested.

TV19 permanent upload was interrupted before result returned; outcome unknown.
Never retry that uncertain old create just to recover IDs. TV20 files are a new
release and intended new creates. Local old tv19 files remain available if needed.
