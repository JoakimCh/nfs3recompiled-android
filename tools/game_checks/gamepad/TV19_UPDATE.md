# Resume: ARMv7 tv19-profile — shared device roles and remote keyboards

Version96 / 0.78-armv7-tv19-profile. Optimized non-debug ARMv7, shell-profileable,
original package/certificate. Install over tv18. Source already patched; never
reapply history patches. No native renderer/math changes; libmain BuildID may
match tv18 because this update is Java/SDL Android bridge code only.

User TV report: phone worked, TV Select acted Back, D-pad and controller remap
failed. Screenshot setup listed virtual-remote, virtual-search, RC600U, Zero2 in
that order, only one real gamepad. Old automatic slots took first2 accepted
Android source-flag devices; test selection didn't assign a player. This strongly
supports wrong slot assignment; exact TV device capabilities/keyboard fallback
routes weren't captured. Don't claim physical tv19 validation or exact automatic
classification of those hardware devices without evidence.

User NFS2 patch reference contained SDL_HINT_TV_REMOTE_AS_JOYSTICK=0 and reconnect
fixes. SDL3.4.2 Android implementation filters devices with <2axes and nohat when
that hint is0. User explicitly requires button-only controllers supported, TV
remotes treated as keyboard navigation, never occupying controller slots.

New InputDevicePolicy pure capability rules and InputDeviceRoles Android adapter
are the single shared eligibility decision for GamepadSlots, setup, haptics,
NFS input classification and SDLControllerManager.isDeviceSDLJoystick. It no
longer trusts source flags alone. Native SDL Android discovery receives only
accepted controller devices; SDL Java polling removes existing entries when
role no longer qualifies. No model/name blacklist and no Zero2 special repair.
Role initialization happens in LauncherActivity, ControllerSetupActivity and
NFS3Activity before SDL startup. Cache per device descriptor/id, invalidated
on device lifecycle or role preference change. User roles stored by hash of
VID/PID/descriptor (input_role_), default/controller/remote. Explicit controller
role can recover unusual button-only layouts or inaccurate capability reports.

Default policy: ignore virtual devices/ordinary alphabetic keyboards; navigation
and media devices without joystick axes/hats are remotes, even if advertising
gamepad buttons. >=2 actual game buttons qualifies button-only controller (no
axis requirement); axes/hats plus buttons qualify wheels/pads, axis-only declared
joysticks with no navigation qualify. Navigation-only devices are remotes;
unclassified devices never auto-fill slots. Capability heuristics can be
ambiguous; UI exposes explicit role choice to correct rather than hard exclude.
The broad SDL no-axes filter is deliberately not enabled: NFS sets
SDL_TV_REMOTE_AS_JOYSTICK=1 because shared Java policy has already excluded remotes,
while accepted button-only pads must reach SDL native AddJoystick.

ControllerSetupActivity shows Player1/2 resolved assignment above device list.
Device rows show role and assigned player. Controller rows alone offer Test /
configure and Player1/2 assignment. Remote/keyboard rows only offer Device role,
not controller testing/binding/player assignment. Role choice Default, Game
controller (including button-only), Remote/keyboard. Player choices use NEW
input_player_<n>_descriptor/name preferences, not obsolete gamepad_slot prefs.
Pins are descriptor-based, avoid duplicate pads, reserve disconnected pinned
slots; Reset to automatic restores connection order among eligible controllers.
Testing selection explicitly separate from player assignment. Existing per-pad
button profiles and in-game config preserved. All changes apply on next launch.
Roles/pins device-specific and intentionally not in portable settings exports.

RemoteNavigation pure state engine translates remote arrows19..22, OK/Enter/A
into Android ENTER66 and Back/B/Escape into ESC111. NFS3Activity intercepts before
SDL controller/keyboard dispatch, consumes translated event once, calls SDL
keyboard native entrypoints. Escape uses existing keyboard-aware systemBack path
and min100ms hold. Other media keys retain OS/keyboard behavior. Joystick-style
remote hat or X/Y directions translate to the same keyboard arrows, not virtual
D-pad buttons. Per-source/per-key reference counts handle simultaneous devices
and overlapping key/axis reports; direction hysteresis .49 press/.30 release,
400ms initial/120ms repeat, no Enter/Back repeats. Android OS repeat downs don't
duplicate presses. Repeat handler only runs while arrows are held (no periodic
wakeups during controller-only play). Unplug/change releases that remote's keys;
pause releases all and stops callbacks. Ordinary physical keyboard independent.
Remote keys are available to normal keyboard mappings, never gamepad bindings.

This is unified role classification/discovery, NOT a complete migration of the
setup's raw-input display to native SDL. Existing tester still displays Android
keys/axes and shared ControllerProfile actions; game retains precise A/B Android
bridge and generic hats from tv18. Don't claim tester now displays SDL mappings.
A later full raw/mapped SDL tester migration is a separate task if requested.

Checks pass: InputDevicePolicyCheck tests phantom TV capabilities, real button-
only pads, wheels/joysticks, explicit roles; RemoteNavigation tests keyboard
codes, duplicate/overlapping devices/axes, repeats, hysteresis, unplug/pause cleanup
and idle repeat state. AutomaticControlsCheck tests new pins independently of
legacy ignored preferences; existing Java profile/touch/config/buffer checks
pass. Actual native SDL controller regressions pass (unchanged C++). Production
release compilation includes shared classifier in SDL Java bridge. Signed APK
version/ABI/original cert/nondebug/profileable/16KB alignment/BuildID/JNI checked.
No physical-device or emulator UI execution available. User hardware remains to
be tried normally; don't request extra profiling or claim TV symptom fixed by
physical proof. Setup roles/player labels allow correction without ADB captures.

Keep checkpoints lean (ARCHIVE_POLICY.md), APK and exact symbols separate. Preserve
original private key/password confidential. tools/tv19 setup/build/finish/package
pinned JDK21,Gradle9.3.1,SDK36/buildtools36,NDK28.2.13676358,CMake3.22.1,SDL3.4.2.
Kotlin incremental off. If workspace generated immutable transforms/ART cache
fails, stop builds and remove only generated cache/dex directories then rebuild;
no product workaround needed. Existing renderer/touch/ARM precision fixes retained.
Input diagnostics defaults OFF; inventory now includes role and native trace
retains profile state. Current text evidence evidence/tv19; bulky history excluded.
