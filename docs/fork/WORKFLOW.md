# Build, validation, release and recovery workflow

Read [current status](README.md) first. The source of truth is this fork's Git
history. Keep documentation changes separate from upstream-facing code changes.
Do not reapply old checkpoint patches to a checkout that already includes them.

## Build

Use JDK 21, Gradle wrapper 9.3.1, Android SDK platform 36 / build-tools 36.0.0,
NDK 28.2.13676358 and CMake 3.22.1. SDK/NDK dependencies are pinned in Gradle.
Clone SDL release-3.4.2 into third_party/SDL (ignored in git):

```sh
git clone --depth 1 --branch release-3.4.2 https://github.com/libsdl-org/SDL.git third_party/SDL
cd android
./gradlew assembleRelease -Parmv7Tv --max-workers=2
# Optional shell profiling, still optimized and non-debug:
./gradlew assembleRelease -Parmv7Tv -PprofileNative --max-workers=2
```

Without -Parmv7Tv, the upstream ARM64 ABI/package is retained. The ARMv7 package
is dev.nfs3hp.port.armv7tv so it can coexist with upstream. Do not enable x87Exact
or wideFpu for this ARMv7 build. Native code preserves the existing math policy;
no fast-math experiment or frame merging is enabled. Opaque shader optimization
is on by default. Performance collection and overlay default off.

Before a release build after changing Android resources, remove android/app/build
(keep .cxx if desired). A stale generated R class previously compiled successfully
but crashed the controller page. Always run the final artifact gate:

```sh
python3 tools/game_checks/gamepad/check_apk_resources.py APK BUILD_TOOLS APP_COMPILE_R_TXT REPORT_JSON
```

Use the release's actual APK, SDK build-tools directory and generated app-owned
R.txt; do not substitute outputs from another variant. Run focused UI checks with
./gradlew testReleaseUnitTest -Parmv7Tv. Sign externally with the original private
certificate to update installed TV releases. Those credentials are intentionally
absent from GitHub. Verify signature, ABI, version, non-debug/profileable flags,
16 KiB ZIP alignment and native BuildID before delivering any APK. Retain exact
matching full native symbols separately for crash decoding.


## Focused validation

- Every delivered APK: build, original certificate, package/version/ABI,
  non-debug and profileable status, ZIP alignment, native BuildID, and the actual
  packaged resource-field check. Verify the artifact delivered.
- Input changes: existing relevant controller/profile/routing checks.
- UI changes: targeted page/lifecycle checks for the behavior changed.
- Rendering changes: the relevant existing renderer/differential checks.
- Documentation-only changes: links, references and diff review; no APK rebuild.

After relevant checks pass, stop unless a new change/failure justifies more.
Do not recreate test infrastructure or launch unrelated experiments. Preserve
precise game math and owner-tested split screen. Distinguish host validation,
source-only work, built artifacts and physical tests. Never invent FPS gains.
Existing host Java checks include BonusContentCheck; Android tests include
ControllerSetupActivityTest and LauncherAdvancedTest. Native gamepad checks use
SDL 3.4.2. Read their existing commands before rebuilding a toolchain.

## Signing and automation

Public certificate SHA256:
`464eab8f658b68c234e80e85f5bcb6c5a79771600ac04c0f9d5458769c27b60e`.
Keystore alias: `armv7-tv-release`. This is the existing release identity, even
when an APK is called a test build. Keep it to update installed TV packages.
Never commit the .p12, password, encoded private key or recovery ZIP.

The manual Actions workflow is in .github/workflows/armv7-release.yml. It builds
only when explicitly dispatched on main; it does not automatically publish or
merge anything. Two repository Actions secrets are required:

- ANDROID_KEYSTORE_BASE64: base64 of the original .p12.
- ANDROID_KEYSTORE_PASSWORD: its password.

If GitHub asks, enable Actions for this fork before dispatching the workflow.
Secret installation is not completed by this documentation change. The available
GitHub connector cannot manage secrets; the local CLI has no credentials. With
an authenticated GitHub CLI on a trusted machine, these commands read values
from files without putting values into shell history:

```sh
base64 < /private/path/armv7-tv-release.p12 | gh secret set ANDROID_KEYSTORE_BASE64 --repo JoakimCh/nfs3recompiled-android
gh secret set ANDROID_KEYSTORE_PASSWORD --repo JoakimCh/nfs3recompiled-android < /private/path/password.txt
```

Alternatively use GitHub Settings → Secrets and variables → Actions. Keep an
independent private recovery copy; Actions secrets are not a downloadable key
backup. The signing helper takes file paths, never literal password arguments.
Without both secrets the workflow must fail rather than use a different key.

## Release artifacts

For each delivered APK retain: source commit; version/package/ABI; APK SHA256;
signing certificate fingerprint; native BuildID; validation summary; exact
matching unstripped native libraries. Store a small identity JSON under
`tools/release_checks/`. Keep APKs and symbol ZIPs outside source history.
The workflow uploads them as separate artifacts; Actions artifacts expire, so
copy versions worth retaining to a durable release/archive before expiration.
Do not assume an artifact can be recovered from its filename after it expires.

Native symbols are not needed to play, but retain the exact build for crash
and profile decoding. Rebuilding the same source is not guaranteed to reproduce
the same BuildID or symbols: toolchain versions, paths and inputs matter.

## Recover after a workspace reset

1. Clone this fork and read AGENTS.md plus docs/fork/README.md.
2. Check the latest release JSON and unresolved work before making changes.
3. Restore only required pinned tools and run focused checks.
4. For a signed APK, use configured Actions secrets or ask the owner to attach
   the small private signing-recovery ZIP. Do not request a full source ZIP or
   assume access to files from another conversation.
5. Update notes and push source promptly. Keep runtime caches and downloaded
   dependencies ignored. Store delivered APKs and exact symbols separately.

Old source checkpoints remain historical recovery copies, but new source ZIPs
are no longer the routine checkpoint. Existing private signing recovery should
be preserved until a replacement has actually been verified.
