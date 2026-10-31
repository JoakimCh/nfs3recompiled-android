# tv15: controller input recorder (diagnostic release)

Version92 / 0.78-armv7-tv15-profile. User reports tv14 did not help D-pad buttons
in menus or remapping. Browser hardwaretester shows directions as buttons12..15.
Those may be normalized browser indices, not Android or raw SDL identities.
The tv14 regression was valid but did not establish this controller's cause.
Do not claim that tv14 fixed the device. Input routing is unchanged from tv14.

User authorized collecting real evidence. Advanced has Record controller input
(default ON for this diagnostic release, independent of Debug/performance flags)
and Controller input report (Share/Save to Downloads). No ADB or profiling.
Launch on affected device with pad connected, wait for menu, briefly hold each
D-pad direction and tap A/B once, return to launcher and export the report.

Report ZIP is scoped to files/input-reports; no game files or text entry.
- metadata.json: actual app/device/version, namespaces, context and timing notes.
- devices.json: Android device IDs/descriptors/vendor/product/controller number,
  source capabilities, supported key codes and motion ranges. Includes D-pad-only
  companion devices even when GamepadSlots does not select them.
- android-events.txt: dispatch-entry -> bridge consumption or forwarding ->
  actual SDL-pad-handler acceptance -> super return. Controller/direction key
  code+name, scan code, action/repeats/source/device/assigned slot. Non-controller
  text key codes are not recorded. Joystick/D-pad motion changes logged at1/16
  axis buckets; mouse/touch coordinates excluded. Inventory also logged on
  connection changes so earlier device identities survive a hotplug.
- native-input.txt: cached on game/SDL polling thread, copied via JNI. Device GUID,
  SDL mapping, raw SDL buttons (up to64), mapped SDL buttons, up to4hats, raw axes
  (first8, emitted when2048-unit bucket changes), Android route/held word,
  selected virtual physical mask, capture-blocked mask and native-bound mask.
  Includes synthesized keyboard events and final DirectInput-style buttons/axes.
  Capturing reads between renderer updates are recorded too.

Native context enum:0 Race,1 Menu,2 Pause,3 Capture. Virtual indices0..15 are
A,B,X,Y,L1,R1,L3,R3,Back,Start,Up,Down,Left,Right,L2,R2. Native raw/mapped masks
use SDL indices; Android keycodes are another namespace. Browser12..15 must not
be directly copied into those tables. JNI samples add copied_at_sdl_ms and Java
adds copied_at_android_uptime_ms for approximate clock alignment. Samples can
lag a short key press; Android entry captures down/up independently.

Both buffers retain512records; Java payload2048characters, native payload4096
bytes before ASCII escaping. Truncation reported with dropped counters. ASCII
escaping keeps arbitrary UTF8 device names safe for NewStringUTF. Java writes
changed snapshots every250ms with cross-process file locks; export copies only
four named files under that lock. Pause flushes, close drains worker, starting
another game replaces the session. Share before launching another game. Files
stay local until user chooses export. Disabling recording applies next launch;
no new native polls or background writer when disabled. Recording adds overhead,
so this diagnostic release should not be used for performance comparisons.

Checks: native UBSan trace tests disabled/no-op, duplicate suppression, bounds,
UTF8 escaping, reset and concurrent writer/reader; actual SDL virtual-pad tests
with recording enabled verify mapping/physical/menu/DI report contents plus all
retained routing tests. Java bounded buffer concurrency/escaping and existing
production defaults/profile/touch tests pass. Release build/signature/ABI/
profileable/alignment and exact APK/symbol Build ID match verified; JNI exports
verified. No physical-device capture/export test available here. Await user's
actual report before diagnosing another device-specific cause.

Lean checkpoint policy retained; exact symbols are separate. Renderer/math and
custom in-game bindings remain unchanged.
