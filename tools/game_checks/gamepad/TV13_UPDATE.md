# tv13: automatic launcher controls

Version90 / 0.78-armv7-tv13-profile. User requests removing redundant touch-key
and gamepad setup screens. In-game racing mappings remain the source of truth.

Removed TouchKeys, Gamepads and GamepadButtons destinations, their UI, assignment
capture/listener, launcher write/reset controls actions, and back-stack entries.
Controls retains touch layout/size/visibility, force feedback, and concise help.
Help/FAQ explain direct menu taps, X/Y plus D-pad navigation, A confirm/B back,
in-game remapping and automatic two-pad connection order.

GamepadButtons ignores saved launcher button overrides and Digital flags.
Existing fixed fallback defaults remain for actions still assigned to keys;
tv6 native assignment priority prevents a remapped button also sending its
fallback. No new native event path. Analog axes retain their values, and the
native digital buttons remain individually available for in-game capture.
The removed Digital mode used to synthesize keyboard driving from D-pad and
triggers, so simply hiding the selector would have left existing users in that
mode. Old true values now have no effect. The native game handles each bound
input according to its type. Legacy setters/table helpers remain for old-config
recognition and regression checks; they are not launcher settings.

GamepadSlots ignores saved pins and resolves attached devices automatically in
Android device-id / connection order. One pad cannot occupy both slots. Reconnects
may change order, as documented. Java/native descriptor routing is retained.

GamePreferences.getTouchKey returns defaults regardless of old overrides;
racing touch actions still use tv12 live effective bindings, and menu gestures
are unaffected. Launcher exports no longer carry obsolete touch key mappings,
pad mappings or digital mode flags; touch geometry and other current settings
are retained. No existing game config reset. driveWith continues to recognize
only built-in profiles; custom in-game mappings are left byte-for-byte intact.

Validation: host JVM runs actual production GamePreferences/GamepadButtons/
GamepadSlots/ControlProfile helpers against old Digital=true, stale pad pins,
custom launcher button/key preferences. Confirms distinct A/B menu defaults,
trigger axis-only behavior, automatic slots and no duplicate controller, and
custom config remains identical on launch with and without a physical pad.
Retained touch action/multitouch and device-shape upgrade tests pass. Real SDL3
virtual-pad checks pass axes/A/B/repeat/capture/Android-route/remap-priority/
unplug. Android instrumentation assertions updated for the removed modes,
but no physical-device/instrumentation run performed. XML and obsolete launcher
navigation checked. Release build and package/signature/ABI/alignment checks are
recorded under evidence/tv13. Renderer/native controller logic unchanged.

No extra profiling or device testing requested. Install normally over tv12.
