# tv16: complete the observed Zero2 SDL mapping

Version93 / 0.78-armv7-tv16-profile. The user's tv15 report establishes the loss
on Samsung SM-A266B / Android16, 8BitDo Zero2 (VID2dc8/PID3230).
Android sends HAT_X/Y motion, not DPAD key events. SDL's Android_OnHat translates
these into raw joystick buttons11Up/12Down/13Left/14Right and reports no hats.
All4 raw bits were recorded, but SDL's active mapping lacked every D-pad field:
raw nonzero -> mapped0 -> selected virtual physical0. Android authority was0
throughout those direction presses, so the earlier face-route hypothesis did
not explain this captured failure. A/B separately worked through Android bridge.
See evidence/tv16/controller-report-findings.json. Original report stays separate.

Repair in gamepad.cpp at device open, with pure android_pad_mapping.h helper:
- Only Android builds and the observed Zero2 VID/PID, >=15rawbuttons, native
  Android GUID four-axis capability0x000f (bytes14/15). HIDAPI/virtual signature
  layouts are not treated as Android raw numbering. This intentionally limits
  the repair to the observed backend/layout, not arbitrary joystick indices.
- Read active SDL mapping, append absent dpup:b11,dpdown:b12,dpleft:b13,
  dpright:b14, submit through SDL_AddGamepadMapping. Open SDL gamepad updates
  live, so existing menu/capture/native remap paths use normalized directions.
- Preserve every existing binding (including explicit/unbound directional
  fields), GUID, label hint and platform. Repeated completion is a no-op.
- No guest config/device-shape changes; A/B bridge, X/Y menus and two-pad
  assignment unchanged. No SDL vendored-source modification or global guess.

Validation replays the full captured mapping including positional-label hint
and Android platform; only the GUID is substituted for the host virtual device.
Before repair raw Down is true while normalized Down is false. After live SDL
update all4directions/releases/diagonals normalize, original A/B stay unchanged.
Actual production slot-open path with Android layout test override then passes
all4 menu and in-game capture checks on player2, with player1 isolated. Retained
axes, A/B, SDL/Android directions, raw hats, repeats, native remap priority,
delayed release/pause/unplug and diagnostic trace tests pass. Pure helper tests
preserve explicit/unbound fields, reject other VID/PID/malformed input, and prove
idempotence. Host override only bypasses the Android GUID signature check for
virtual replay; actual reported GUID satisfies that check. Physical phone/TV
execution of tv16 remains untested here. No claim about unrelated controllers.

Input recorder retained for troubleshooting but defaults OFF again to avoid
sampling overhead in normal play. An explicitly saved user choice is retained.
Enable it in Advanced before a new capture if needed. Existing saved tv15 report
is retained until another recorded game session starts. Renderer/math unchanged.
APK/source checks and matching full symbols are archived separately; source
checkpoint remains lean. No additional profiling/testing round requested.
