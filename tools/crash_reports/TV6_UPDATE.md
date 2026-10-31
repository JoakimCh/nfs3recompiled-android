# ARMv7 TV release tv6 — A/B aliasing, duplicate actions and vertical D-pad

Version 0.78-armv7-tv6, code 83, original package and signing certificate.
Install over tv5. Existing data and control assignments remain.

The user reported successful X/Y menu navigation, but A and B both became A
in menus and the binding screen; another action appeared queued on the next
screen. Other buttons mapped correctly. X could be assigned, but Y could not.

## Corrections

1. One digital-button route per Android controller. Previously the backend
   ORed SDL's mapped buttons with the Android key fallback. An SDL South
   report combined with Android East produces both Return and Escape in the
   menu and both native buttons 1/2 in capture (the game picks button 1).
   This is a code-level reproduction of the reported failure, not a recorded
   trace of the user's actual device events. Once Android reports a button,
   its logical key identities own the digital buttons. NFS3Activity consumes
   recognized key events after forwarding them to this route; they do not
   also pass through SDL's button mapping or keyboard conversion. The route
   flag and sixteen held bits share one atomic word and are sampled once
   per poll. Clearing held keys on pause preserves route ownership, preventing
   delayed SDL state from producing a second press. Descriptor reassignment
   clears ownership. SDL retains analog axes/triggers and serves controllers
   that provide no Android key events. Digital/analog trigger reports merge
   into one trigger identity. Existing trigger suppression for native bindings
   remains.
2. Mapped left Y now reaches the existing virtual Y axis in all contexts,
   alongside combined trigger pedals. Previously mapped devices read left X
   and the triggers only; their left Y was used only by menu navigation.
   Larger absolute magnitude wins, preserving the trigger value on ties.
   Thus up/down can be captured as Y halves and used while driving. Axis count
   and device records stay unchanged, so this does not reset settings.
3. The English launcher hint now explains in-game assignments, their priority,
   fixed menu A/B, and X/Y navigation. The old text was informational; it was
   not a second event handler. Other translations retain their previous text.

## Validation

The actual gamepad.cpp is linked against SDL 3.4.2 with virtual mapped and
unmapped devices in tools/game_checks/gamepad/pad_check.cpp. Tests cover prior
menu/repeat/capture/ownership/unplug behavior plus positive/negative mapped Y
in racing and capture, and a deliberate conflicting SDL South + Android East.
That collision must emit exactly one Escape down/up, remain quiet across a
Menu-to-Pause transition and delayed SDL release, and expose only button 2
in capture. Capture can still poll analog trigger release without rendering.

Android ARMv7 release build and APK checks include same signing certificate,
version/package, non-debug manifest, ARM32-only libraries, alignment and JNI
agreement. No physical R10G/controller test is available here. If the hardware
itself reports identical Android codes for A and B, software cannot distinguish
them through this key route; that remains a possibility requiring actual input
reports. No graphics, math or networking changes were made in tv6.
