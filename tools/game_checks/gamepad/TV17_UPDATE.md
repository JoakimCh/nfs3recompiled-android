# TV17 generic controller setup

No added vendor-specific runtime mapping. The former Zero2 helper/slot-open repair
and test override are removed. ControllerSetupActivity tests Android events and
captures optional per-device directions and menu confirm/back. ControllerProfile
is pure Java and shares exact live state logic with gameplay. Profiles use Android
physical descriptor + VID/PID, independent of connection ID and player slot.

Native snapshots use mask bits0..5 (Up/Down/Left/Right/Confirm/Back), held8..13,
direction source suppression16..31, menu source suppression32..47, held-axis48,
automatic source direction suppression49..52. Canonical D-pad identity is shared
by menu and in-game capture. Face overrides apply only to Menu/Pause, preserving
racing button identity. Atomic JNI stores do not poll SDL from Android UI threads.

run.sh tests actual SDL production routing, missing-mapping virtual pad without
repair, axis/capture/source suppression, face swap, transitions, isolation and old
regressions. ControllerProfileCheck tests serialization/validation, arbitrary
buttons, hats/axes/hysteresis/diagonals, trigger rest, pause release and conflicts.
No device/emulator UI test was available. Release compile and package checks pass.
