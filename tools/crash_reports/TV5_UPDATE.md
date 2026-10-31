# ARMv7 TV release tv5 — controller handling

Version 0.78-armv7-tv5, code 82. Same package and original signing key as tv1–tv4.
Install over tv4; keep the app's data. The tv4 rendering changes and crash reporter remain.

## Player-visible changes

* Left X/Y axes navigate game menus and the pause screen, including D-pads
  reported as axes. Real D-pad buttons continue to work. A 16000/10000
  press/release hysteresis rejects noise. Hold a direction to repeat after
  400 ms, then every 120 ms. Axes do not emit menu arrows while driving.
* A confirms, B goes back. Android button reports back up SDL's mapping;
  generic numbered buttons 1/2 also serve as A/B. Unmapped SDL joysticks use
  their first two buttons and axes. The TV remote retains its own path.
* The two virtual gamepads now expose sixteen stable button identities.
  In the game's Controls screen, choose an action, press A, release it,
  then press the desired button. Buttons used to enter capture must first
  be released. While capturing, the pad sends native buttons rather than
  menu Enter/Escape. The remote/keyboard Escape can cancel capture.
* During a race, a native button binding takes precedence over that button's
  old launcher keyboard/axis action. Remapped triggers stop operating their
  old pedal axis. Buttons without native bindings retain their old behavior.
  Menu A/B remain independent of racing assignments.
* Existing settings files have only the known old gamepad button masks
  upgraded. Custom bindings, axis ranges and force feedback are preserved;
  this prevents the game's device-list comparison resetting controls.

Button identity order (the game displays numbered buttons):
1 A/South, 2 B/East, 3 X/West, 4 Y/North, 5 L1, 6 R1, 7 L3, 8 R3,
9 Back/Select, 10 Start, 11 D-pad Up, 12 Down, 13 Left, 14 Right, 15 L2, 16 R2.
For an entirely unmapped joystick these are raw driver indices; numbered
Android key reports use the same index. Axis-only D-pads remain axes in-game.

## Implementation and checks

`gamepad_policy.h` validates the current guest menu and selected Controls
widget (on-key 0x43cf80, signed capture row at +0x3c), and recognizes native
button bindings (low byte 2, button index in bits 8–15, slot in bits 28–31).
`layoutTick` supplies that context and the active single/split-screen binding
masks. The guest game and its arithmetic are unchanged. `getState` continues
polling SDL while capturing because original sub_43be40 waits for button-up
without another rendered frame. Android fallback button state is atomic,
cleared on pause and slot reassignment, and combined with SDL state once.

Tests in tools/game_checks/gamepad:
* `pad_check.cpp` links the actual gamepad implementation against SDL 3.4.2
  with virtual mapped and unmapped joysticks. Covers axes, hysteresis,
  repeat, A/B, two-slot key ownership, Android fallback, capture gating,
  polling without rendering, native binding priority, trigger suppression
  and unplug key release. Also checks guest capture detection and button
  binding decoding. Force feedback is stubbed in this host input-only test.
* `ControlProfileUpgradeCheck.java` runs against the built release classes.
  Verifies fresh device masks, byte-for-byte preservation outside the two
  upgraded mask words (including a custom binding), idempotence, malformed
  file rejection and unknown device preservation.
* Android ARMv7 release build, same signing certificate, package/version,
  non-debug manifest, four ARM32 libraries, JNI export/DEX agreement and ZIP
  alignment checked. Current symbols are in evidence/tv5.

No physical Cepter R10G/controller run is available here. End-to-end UI
binding behavior on the user's device remains unverified. If a pad reports
unusual keys beyond these fallbacks, its exact key/axis reports may still
need a device-specific mapping. No changes to graphics, math or networking
were made in tv5.
