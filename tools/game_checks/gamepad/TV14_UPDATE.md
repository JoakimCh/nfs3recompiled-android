# tv14: independent D-pad input routing

Version91 / 0.78-armv7-tv14-profile. User reports axis-based D-pad works, but
button directions cannot navigate menus or bind in-game. Also confirms tv13
split screen with two gamepads works on their hardware.

Root cause reproduced in the host SDL3 virtual-gamepad harness: reporting an
Android face button set a single authoritative route for all fourteen digital
buttons. Subsequent directions arriving only through SDL were discarded by
physicalButton(), both in update() (menu navigation) and getState() (capture).
A new test applied to the original tv13 gamepad.cpp aborts on the first missing
SDL direction; it passes with the fix. This matches the reported symptom, but
no physical-device event trace was available to establish its exact route.

Changes in src/lib/sdl-backend/gamepad.cpp:
- Preserve face/shoulder/menu-button authority selected by Android, so the
  existing single-B-also-becomes-A regression remains fixed.
- Keep a separate D-pad authority bit. SDL directions remain available after
  face reports; only an actual Android direction report selects Android for
  the D-pad group. Then ignore stale/conflicting SDL direction reports.
- Pause clears held bits while retaining both known route bits. Descriptor
  changes still reset all ownership. Each player keeps independent state.
- For unmapped SDL joysticks, expose first-hat directions as virtual D-pad
  buttons 11..14 (zero-based indices10..13), including diagonals. Existing
  raw buttons remain available. Mapped SDL pads keep their mapped D-pad.
- Menu navigation and capture share the same physicalButton() decision.
  No additional keyboard-event path, config rewrite or device-shape change.

Validation: real SDL3 harness tests all4 SDL directions after Android face
reports, menu repeat/releases, capture polling between swaps, native in-game
assignment priority, raw hats/diagonals in player2, player isolation, all4
Android directions with conflicting SDL directions, late releases, pause clear,
A/B identity/no queued duplicate, axes, trigger capture, unplug. All pass.
Existing production Java default/profile/touch checks pass. No physical TV/phone
run or new performance measurement here. Renderer/game math unchanged.

Source checkpoint remains lean; save each released APK and matching full native
symbols separately. Keep the original private signing material and exact Build ID.
