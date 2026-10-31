# tv12-profile: touch controls follow live game assignments

Version89,0.78-armv7-tv12-profile, same package/release certificate. Install over
tv11, keep game data, in-game mappings and working gamepad settings. Rendering
optimization from tv11 unchanged. User asked to fix touch buttons after remapping
inside the game and suggested reading its config file to find what to emulate.

Root cause: racing overlay controls emitted launcher-configured SDL keyboard
keys. Changing the game's Controls assignments made those keys stale; with pad
profiles, steering/pedal keys also fed hard-coded X/Y axes. This can activate
the wrong action or stop a touch button working after a remap.

Racing buttons now send stable13-action identities over JNI, using negative
tokens in the existing TouchKeyState ref-counting layer. Menu/preview keys,
pause/back and keyboard keep their existing route. Stable tokens make release
independent of remapping while a finger is held. Two fingers on one action
still produce one press and only release after the last finger lifts. Pulses
retain existing90ms duration and cancel on layout changes/focus loss/pause.

Native touch_input.h stores active+13held bits and lifecycle generation in one atomic word. Leaving
driving/menu/capture/replay/loading clears held state; concurrent UI down cannot
resurrect it. layoutTick supplies existing playerDriving&&!loading signal each
frame, before its UI-change early return. JNI writes only atomic action bits,
never guest memory or game files. No raw fake racing key presses reach SDL.

The game's native binding evaluators (buttonHeld,hatPointing,axisAmount,keyHeld,
controlHeld) check held touch actions against the CURRENT EFFECTIVE race table
at0x79c340. This is the same input table the game populated from its loaded
single/split settings; no stale disk-file cache or GUI snapshot is needed.
Action order right,left,gas,brake,handbrake,gearup,geardown,camera,horn,lookback,
recover,spikes,headlights maps to runtime slots1,0,2,3,6,8,9,46,7,45,5,11,10.
Camera/lookback are function-key slots, not regular12action slots. Only local
player one's effective mapping is queried; split player2 has separate slots.

When touch targets the queried binding, return full digital value255, using
the same guest return-stack adjustment and preserving other registers/flags.
keyHeld also retains its existing key0x37-clear side effect. Otherwise the
original physical-input evaluator runs unchanged. Canonical keyboard bindings
compare DI scan codes rather than their display-glyph byte; axes/POV keep exact
half/direction/device, buttons keep index/device. Unbound/unknown bindings stay
inactive. TouchSteering includes semantic left/right holds for existing digital
steering/replay behavior. Physical keyboard/gamepad state is never overwritten;
releasing touch leaves held physical input working normally.

This is binding-level emulation: assignments sharing the same physical binding
can activate together, just as that physical input would. No synthetic selection
of player2 settings, no rewrite of custom profiles or mappings. Changes follow
when the game applies them to its effective race table, including before a new
race and when it refreshes that table after options. No promise to force a config
edit ahead of the game's own application of it. Unbound controls remain unbound.

English touch-key hint now explains racing buttons follow game assignments;
menu key choices remain available. The touch-key screen hides the obsolete racing
key overrides and keeps menu keys; stored old preferences are retained, not reset.
Editor/preview uses legacy key identities so
existing layout/drag behavior and preview tests stay meaningful. No extra UI
toggle, file permission, polling thread or disk I/O introduced. Idle native path
reads only atomic bits and never guest bindings when no touch action is held.

Checks: touch_check.cpp (UBSan) covers all13actions, live keyboard->button->axis->
POV remapping while held, glyph normalization, lower/upper axis isolation,
distinct player2 slots, unbound/invalid input, release/menu/idle path and
concurrent lifecycle/UI updates. touch_entry_check.py extracts EXACT added
production entry branches into a focused fake-guest harness to verify guest
EAX/ESP return behavior, unchanged other registers/flags, key-clear side effect,
and no-touch fallthrough. It is not a full emulated-game differential test.
Actual TouchAction and TouchKeyState run on host JVM for action IDs, menu
exclusions, negative tokens, multitouch counts/cancellation. Existing real SDL3
virtual-gamepad tests pass: A/B identity, D-pad axes, repeat, capture, native
remapping priority and unplug; added actual Gamepad::touchSteering assertions.
Android release and signed APK/ABI/version/cert/nondebug/profileable/alignment
checks done separately. No device touch UI or full gameplay run available here.

Portable focused checks:
 g++ -std=c++17 -O2 -pthread -fsanitize=undefined -I include tools/game_checks/gamepad/touch_check.cpp -o touch-check
 ./touch-check
 python3 tools/game_checks/gamepad/touch_entry_check.py /path/to/check-work
Run TouchCheckHost.java with actual app TouchAction.java/TouchKeyState.java using
plain javac/java; no Android dependency. Existing gamepad/run.sh builds SDL host.

User should install and use normally. No exhaustive test/profiling request.
Source/checkpoint includes matching symbols, private original signing material
and previous history. Never print signing secrets; don't reapply saved patches.
