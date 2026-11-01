# Android checks, builds and signing

Read this file and [BUILD_STATUS.md](BUILD_STATUS.md) after a context reset.
The selected toolchain is in [android-toolchain.json](../../tools/android-toolchain.json).
Use the Gradle wrapper and shared commands below; do not reconstruct setup interactively.
Setup, tests, builds and publication still require the authorization described in AGENTS.md.

## Prefer GitHub Actions

Signing credentials are configured in this repository's Actions secrets. A signed
build on `main` succeeded on 2026-11-01; the exact run is in BUILD_STATUS.md.
The revised workflow in this branch adds these manual modes:

| Mode | Work | Deliverables |
| --- | --- | --- |
| `tests` (default) | Tooling tests, launcher compilation/resources and launcher tests | Test reports and validation JSON |
| `check` | Tests, then native ARMv7 compilation/linking | Reports and validation JSON; no APK |
| `apk` | Tests, native build, APK packaging, signing and verification | Signed APK, validation/release JSON and matching symbols |

Open [Actions](https://github.com/JoakimCh/nfs3recompiled-android/actions), select
**Android checks and builds**, then **Run workflow**. Select **Use workflow from**
the intended branch, select the mode and start the run. The workflow file remains
`.github/workflows/armv7-release.yml`. It already exists on the default branch,
which is required for manual dispatch. Select a branch containing the revised
workflow to use its new modes; `main` retains its previous UI until updated.
There is no main-only job restriction in the revised workflow and no push trigger.
A dedicated test branch is not required.

When tooling supports it, the equivalent CLI command is:

```sh
gh workflow run armv7-release.yml --ref BRANCH -f mode=tests
```

Use `check` or `apk` for the other modes. Do not assume the connected GitHub tool
can dispatch: inspect its current capabilities. If dispatch is unavailable, give
the user the exact workflow link, branch and mode, then monitor the run they start.
Do not repeatedly retry an unavailable action or install the local toolchain just
because dispatch needs a user click.

Before reporting success, inspect the jobs and relevant steps. Tests-only success
does not mean native compilation ran. A build check verifies compilation/linking;
APK mode additionally validates packaging, resources, signing and symbol identity.
A skipped job has verified nothing. An old run does not validate a newer commit.

## Download results

Open the completed run and scroll to **Artifacts**:

- `armv7-apk`: ZIP containing the signed APK and verification JSON. Extract the APK to install it.
- `armv7-native-symbols`: exact native symbols for crash decoding; not needed to play.
- `armv7-MODE-reports`: launcher test results and validation JSON, including on test failure where available.

Always match the run's branch and source commit to the requested changes. The
known successful `main` run built tv27, not tv28. Test/APK reports expire after
14 days; symbols after 90 days. Retain an APK and its exact symbols outside Actions
before expiry when that build will continue to be used. Never commit APKs or keys.

## Cache behavior

The workflow caches Gradle downloads/build state, Robolectric runtime dependencies,
selected SDK/build-tools/NDK/CMake/Ninja installations and pinned SDL source.
Launcher and native tool caches have separate keys, so a launcher-only cache cannot
prevent saving the larger native cache. The manifest controls tool cache versions.
Only selected tools are installed in the cache SDK; the entire runner SDK is not cached.

Caches are accelerators, not source or release archives. A miss must still work.
The initial cold run still downloads tools and dependencies. The wrapper uses
Ninja compile pools (`--jobs`, default 2) and one link job. It does not assume all
reported host CPUs can safely compile the generated game sources simultaneously.

## Local workspace fallback

Automatic bootstrap supports Linux x86_64 and requires Python 3.12+, `curl`, `git`
and `bash`. Other hosts need compatible tools installed explicitly; the cloud
bootstrap is not a Windows installer. Reuse compatible installed tools and caches.
JDK 25 LTS is selected; installed compatible JDK 26/27 is accepted. Tool updates
are deliberate manifest changes followed by checks and a device trial.

These commands are run from the repository root:

```sh
# Optional preparation only. This does not test, build or sign.
python3 tools/android.py setup --accept-sdk-licenses

# Launcher/tooling tests; skips native toolchain and SDL installation.
python3 tools/android.py tests --accept-sdk-licenses

# Tests plus native compilation; no APK or signing credentials.
python3 tools/android.py check --accept-sdk-licenses

# Tests, build and original release signing.
python3 tools/android.py apk --accept-sdk-licenses \
  --keystore /private/armv7-tv-release.p12 \
  --password-file /private/password.txt
```

`--accept-sdk-licenses` explicitly accepts SDK licenses when installation is needed.
Omit it when licenses are already accepted. `setup --tests-only` prepares just the
launcher tools. Each run mode prepares its own prerequisites automatically.

Set `NFS_BUILD_CACHE` or pass `--cache-dir /writable/cache` to reuse a cache.
The default is `nfs3-build-cache` beside the repository. `JAVA_HOME`, `ANDROID_HOME`,
`ANDROID_SDK_ROOT` and `GRADLE_USER_HOME` override discovery. Cached paths from a
previous workspace are only reused when present. Machine paths go into ignored
`android/local.properties` and the cache's `environment.json`, not source history.
Run one setup operation per cache at a time.

`--jobs 2` is the default. The same wrapper runs in Actions. It passes current
proxy/CA settings to Java and explicitly to Gradle, without saving proxy ports.
See [WORKSPACE.md](WORKSPACE.md) for the observed compatibility fixes.

The local APK command requires original signing files before downloading large
tools. An explicitly requested unsigned intermediate can be built with
`apk --unsigned`; it is not installable until signed. A prepared APK can be signed
without recompilation using `tools/android.py sign --keystore ... --password-file ...`.
The signing command still verifies packaged resources and exact native symbols.
Output is `out/` unless `--output-dir` is supplied.

Low-level Gradle commands remain available. `-Parmv7Tv -PprofileNative` selects
the TV package. The shared launcher-tests command adds `-PlauncherTestsOnly`, which
is restricted to the launcher test task and cannot produce an APK missing native
libraries. The normal upstream build remains ARM64; the shared modes/signing
workflow described here are specifically for ARMv7 TV.

## Signing identity

Only APK mode receives these GitHub repository secrets:

- `ANDROID_KEYSTORE_BASE64`: base64 of the original `.p12`, not the recovery ZIP.
- `ANDROID_KEYSTORE_PASSWORD`: the original password.

The workflow verifies the public signing certificate before the expensive build,
removes those temporary signing files, runs checks/build without them, then
recreates private temporary files only for final signing. These files live under
`RUNNER_TEMP`, outside caches, and are removed on exit. Tests/check modes do not
read signing secrets. Do not put keys, passwords or recovery ZIPs in Git, caches,
logs or build artifacts.

Public alias: `armv7-tv-release`. Expected certificate SHA-256:
`464eab8f658b68c234e80e85f5bcb6c5a79771600ac04c0f9d5458769c27b60e`.
The shared signer checks the package/version, certificate, ABI, alignment,
profileable/non-debug state, packaged R fields and matching native BuildID.

## Validation state

Local validation of the shared runner is recorded in [BUILD_STATUS.md](BUILD_STATUS.md).
The hosted workflow still needs manual runs of all three modes, including a warm
cache rerun. Keep local results distinct from hosted Actions results and from
Joakim's device test of the earlier tv28 APK.
