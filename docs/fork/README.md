# About this fork

Joakim's fork adds ARMv7 Android TV support and improves gamepad and touch
controls. It includes the original project's alphaG0.78 update.

The ARMv7 package is `dev.nfs3hp.port.armv7tv`; the ordinary build targets ARM64.
See [BUILD_STATUS.md](BUILD_STATUS.md) for verified builds and device feedback,
and [release details](releases/) for APK identities.

## What differs from upstream

- Two-player controller assignment, remote/gamepad separation and configurable
  menu controls. Button-only pads and axis-based D-pads are supported.
- An optional per-controller combination of two chosen buttons opens the race
  pause menu even when those buttons are assigned to racing actions.
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

[Build, download and publish APKs](BUILD.md) · [Verified build state](BUILD_STATUS.md) · [Changes](CHANGELOG.md) ·
[Workspace recovery](WORKSPACE.md) · [Performance findings](PERFORMANCE.md) ·
[Translations](TRANSLATIONS.md)

Git is the source checkpoint. APKs, matching native symbols and the private
signing backup are stored separately. No source ZIP is needed to resume work.

## Maintaining these notes

- Update current status entries instead of appending session reports.
- Keep build evidence in BUILD_STATUS.md and release JSON; use Git history for
  superseded investigations. Keep reusable instructions independent of versions.
- Keep changelog entries about changes, without test results or personal feedback.
- Give each topic one home and link to it rather than repeating it across guides.
