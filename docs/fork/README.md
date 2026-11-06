# Fork documentation

See the [main README](../../README.md) for features and requirements.

- [Build, download and publish APKs](BUILD.md)
- [Verified builds and device feedback](BUILD_STATUS.md)
- [Changelog](CHANGELOG.md)
- [Performance findings](PERFORMANCE.md)
- [Launcher translations](TRANSLATIONS.md)
- [Workspace recovery and troubleshooting](WORKSPACE.md)

## Development notes

Read [AGENTS.md](../../AGENTS.md) before making changes.

Keep two stable virtual controllers so the game's custom bindings survive.
Replacing `config.dat` resets those bindings. Android and SDL must not deliver
the same button twice; classify devices by capabilities and user overrides.

Packed game data may be unaligned. Preserve upstream fixed single-precision
semantics and exceptional-value fallbacks. Use the opaque shader only for draws
known to be opaque.

Keep instructions in the relevant guide, build evidence in BUILD_STATUS.md and
release metadata, and versioned changes in the changelog. Update current notes
instead of appending session reports; older details remain in Git history.
