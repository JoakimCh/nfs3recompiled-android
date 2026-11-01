# About this fork

Joakim's fork adds ARMv7 Android TV support and improves gamepad and touch
controls. It includes the original project's alphaG0.78 update.

The latest build is **tv27** (version 104). The ARMv7 package is `dev.nfs3hp.port.armv7tv`;
the normal build still targets ARM64. APK identities are in
[release details](releases/). Joakim reported testing tv27 without problems.

## What differs from upstream

- Two-player controller assignment, remote/gamepad separation and configurable
  menu controls. Button-only pads and axis-based D-pads are supported.
- An optional per-controller Back + extra-button combination opens the race
  pause menu even when the buttons are assigned to racing actions.
- Touch controls follow the game's racing assignments.
- ARMv7 alignment fixes and a conservative opaque-shader optimization.
- Advanced tabs for unlocks, performance and debugging. Each bonus car and
  Empire City can be unlocked separately.

## Useful context for future changes

The game checks its saved controller descriptions. Keeping two stable virtual
pads lets custom racing bindings survive; replacing config.dat would undo that.
Android and SDL must not deliver the same button twice. Device classification
uses capabilities and user overrides, rather than gamepad-model exceptions.

Packed game data may be unaligned. Math optimizations retain the established
precision and fallback paths. The opaque shader runs only when opacity is known;
other draws use the original shader.

[Build and signing](BUILD.md) · [Changes](CHANGELOG.md) ·
[Performance findings](PERFORMANCE.md) · [Translations](TRANSLATIONS.md)

Git is the source checkpoint. APKs, matching native symbols and the private
signing backup are stored separately. No source ZIP is needed to resume work.
