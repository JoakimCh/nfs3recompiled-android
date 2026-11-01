# Android checks, builds and signing

Use GitHub Actions for routine tests and APK builds. Use the shared local command
when a workspace build is wanted. Both use
[android-toolchain.json](../../tools/android-toolchain.json).
See [BUILD_STATUS.md](BUILD_STATUS.md) for verified runs and device feedback.

## Run on GitHub

1. Open [the build workflow](https://github.com/JoakimCh/nfs3recompiled-android/actions/workflows/armv7-release.yml).
2. Choose **Run workflow**, then select the branch under **Use workflow from**.
3. Choose a mode and start the run:

| Mode | What it does | Output |
| --- | --- | --- |
| `tests` (default) | Tooling and launcher tests; no native build | Test reports |
| `check` | Tests, then native ARMv7 compilation and linking | Reports; no APK |
| `apk` | Tests, native build, packaging, signing and verification | Signed APK, reports and matching native symbols |

**APK mode already includes tests**; there is no need to run each mode in order.
Choose `tests` for launcher changes, `check` to check native compilation, and `apk`
when you want an installable build. These modes target ARMv7 TV; the normal
upstream build targets ARM64.

Select a branch containing the revised workflow, currently
`feature/launcher-wording-backups-translations`. Until it is merged, `main` has
the older workflow and inputs; the Actions sidebar may also show its older name.
No dedicated test branch is needed. The workflow runs manually, never on push.

With an authenticated GitHub CLI, the equivalent command is:

```sh
gh workflow run armv7-release.yml --ref BRANCH -f mode=apk
```

## Download the APK

Open the completed run and scroll to **Artifacts**. GitHub may require sign-in.

| Artifact | Contents |
| --- | --- |
| `armv7-apk` | ZIP containing the signed APK and verification metadata. Extract the APK to install it. |
| `armv7-native-symbols` | Matching symbols for decoding crashes. Keep them with the APK; they are not needed to play. |
| `armv7-MODE-reports` | Launcher test results and validation JSON. |

Check the run's branch, source commit and completed steps before using its output.
A skipped run has not validated anything. APK verification checks the original
signing certificate, package/version, ARMv7 libraries, 16K alignment,
non-debuggable/profileable state, packaged resources and matching native BuildID.
Device testing is still separate.

**Artifacts currently expire after one day.** The repository's retention limit
overrides the workflow's requested 14 days for APKs/reports and 90 days for symbols.
Check each run's expiry and save useful APKs with their matching symbols before
then. To retain them longer in Actions, increase the repository's artifact
retention limit under **Settings → Actions → General**. Never commit APKs or keys.

## Local builds

Run these commands from the repository root. Automatic bootstrap supports Linux
x86_64 with Python 3.12+, `curl`, `git` and `bash`. Other hosts need compatible
tools installed explicitly.

```sh
# Optional preparation only; each mode also prepares its own prerequisites.
python3 tools/android.py setup --accept-sdk-licenses

# Launcher and tooling tests; no NDK, CMake or SDL required.
python3 tools/android.py tests --accept-sdk-licenses

# Tests and native compilation; no APK or signing credentials.
python3 tools/android.py check --accept-sdk-licenses

# Tests, build and signing with the original release key.
python3 tools/android.py apk --accept-sdk-licenses \
  --keystore /private/armv7-tv-release.p12 \
  --password-file /private/password.txt
```

`--accept-sdk-licenses` accepts SDK licenses when installing packages. Omit it if
licenses are already accepted. `setup --tests-only` prepares only launcher tools.
Output goes to `out/`; change it with `--output-dir`.

The APK command checks signing credentials before downloading large tools.
`apk --unsigned` produces an intermediate that must be signed before installation.
To sign a prepared APK without rebuilding:

```sh
python3 tools/android.py sign \
  --keystore /private/armv7-tv-release.p12 \
  --password-file /private/password.txt
```

Keep the prepared APK and its matching native build outputs available: signing
also verifies resources and packages the exact symbols. Use `--apk PATH` to select
a different prepared APK.

## Tools and caches

Exact versions are selected for reproducibility, rather than requiring manual
installation of every tool. The bootstrap reuses compatible installed tools and
fetches missing ones with checksum verification. JDK 25 LTS is selected;
compatible installed JDK 26/27 is also accepted. Update the manifest deliberately,
then run checks and a device trial. Use the Gradle wrapper, not a global Gradle.

Set `NFS_BUILD_CACHE` or pass `--cache-dir /writable/cache` to reuse a local cache.
The default is `nfs3-build-cache` beside the repository. `JAVA_HOME`, `ANDROID_HOME`,
`ANDROID_SDK_ROOT` and `GRADLE_USER_HOME` override discovery. Machine paths stay
in ignored files; stale cached paths are checked before reuse. Run one setup
operation per cache at a time. Native compilation defaults to two jobs and one
link job; increase `--jobs` only when memory permits.

Actions caches Gradle/Robolectric dependencies, selected Android tools and pinned
SDL source. Launcher and native tool caches have separate keys. A first run or
cache miss downloads dependencies; caches are not release archives. Cold APK
setup succeeded in the run recorded in BUILD_STATUS.md; warm cache restoration
still needs a repeat run.

For workspace recovery and proxy/SDK troubleshooting, see [WORKSPACE.md](WORKSPACE.md).
Low-level Gradle remains available: `-Parmv7Tv -PprofileNative` selects the TV
package. `-PlauncherTestsOnly` is restricted to launcher tests and rejects APK tasks.

## Signing credentials

GitHub signing secrets are configured and verified. Only APK mode uses them:

- `ANDROID_KEYSTORE_BASE64`: base64 of the original `.p12`, not the recovery ZIP.
- `ANDROID_KEYSTORE_PASSWORD`: the original password.

The workflow checks the certificate before building, removes the temporary key,
then recreates it for final signing. Temporary files live outside caches and are
removed on exit. Local signing needs the original private files, kept outside the
repository. Never place credentials in Git, caches, logs or artifacts.

Public alias: `armv7-tv-release`. Certificate SHA-256:
`464eab8f658b68c234e80e85f5bcb6c5a79771600ac04c0f9d5458769c27b60e`.
