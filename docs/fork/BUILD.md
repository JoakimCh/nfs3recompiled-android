# Android checks, builds and signing

Use GitHub Actions for routine builds or `tools/android.py` for a requested local
build. Both use [android-toolchain.json](../../tools/android-toolchain.json).
See [BUILD_STATUS.md](BUILD_STATUS.md) for validation and pending changes;
[WORKSPACE.md](WORKSPACE.md) covers recovery and troubleshooting.

## Run on GitHub

Open [Build ARMv7 APK](https://github.com/JoakimCh/nfs3recompiled-android/actions/workflows/armv7-release.yml),
choose **Run workflow**, select the branch under **Use workflow from**, and choose:

| Mode | Work | Output |
| --- | --- | --- |
| `tests` (default) | Tooling and launcher tests | Reports |
| `check` | Tests and native ARMv7 compilation/linking | Reports; no APK |
| `apk` | Tests, native build, packaging, signing and verification | Signed APK, reports and symbols |
| `apk-fast` | Same APK build and verification, skipping tooling and launcher tests | Signed APK, reports and symbols |

`apk` includes tests; there is no need to run each mode in order. Fast builds
record `mode: apk-fast` and `tests: null`. All modes target ARMv7 TV; the ordinary
upstream build targets ARM64. Workflows run manually. Select `main` or a feature
branch; no dedicated test branch is needed. With an authenticated GitHub CLI:

```sh
gh workflow run armv7-release.yml --ref BRANCH -f mode=apk
```

## Download the APK

Open the completed run and scroll to **Artifacts**. GitHub may require sign-in.

| Artifact | Contents |
| --- | --- |
| `armv7-apk` | ZIP containing the signed APK and verification metadata; extract the APK to install |
| `armv7-native-symbols` | Exact symbols for decoding crashes; keep with the APK |
| `armv7-MODE-reports` | Validation JSON and available test reports |

Check the run's branch, source commit and completed steps. A skipped run is not
validation. APK verification checks certificate, package/version, ARMv7 libraries,
16 KiB alignment, non-debuggable/profileable state, resources and native BuildID.
Device testing is separate.

Artifacts were last observed to expire after **one day** because of the repository
retention limit. Check the run's expiry and preserve useful APKs and symbols.
Change retention under **Settings → Actions → General**, or publish a release for
lasting downloads. Never commit APKs or signing keys.

## Publish an existing APK as a release

Open [Publish APK release](https://github.com/JoakimCh/nfs3recompiled-android/actions/workflows/publish-apk.yml)
and choose **Run workflow**:

1. Select the workflow branch. **Build branch** defaults to that branch.
2. Leave **APK run ID** blank for its latest successful signed build, or enter
   the number after `/actions/runs/` in a specific run's URL.
3. Choose **prerelease** or **release**, then start. The summary links to the result.

The publisher accepts `apk` and `apk-fast`, preserving validation metadata.
Normal builds require passing tests; fast builds must explicitly record skipped
tests. Both require a clean source commit, native build and matching verified APK
and symbols. Publication uploads the existing files without rebuilding or signing.
Missing, expired or inconsistent artifacts stop publication without substituting
an older APK. A regular release becomes latest; a prerelease does not.

Notes use versioned changelog entries at the **APK's source commit**, since the
previous published ARMv7 version in its history. Regular releases compare with
regular releases; prereleases may also compare with prereleases. A rebuild uses
the preceding lower version; a first release includes only its own entry.
Missing or inconsistent entries stop publication. Unreleased sections are excluded.

Existing tags/releases are never overwritten. To recreate a release from the same
run, delete its release **and tag** first. Failed uploads may leave a draft;
inspect that draft and any matching tag before removing them and retrying.
The publishing job declares `actions: read` and `contents: write`; GitHub supplies
its temporary token automatically. No personal token or additional secret is needed.
Published downloads are on the [Releases page](https://github.com/JoakimCh/nfs3recompiled-android/releases).

## Versions and changelog

[android-release.json](../../tools/android-release.json) defines ARMv7
`versionName`, `versionCode` and fork `revision`. Update all three together,
increasing the code and revision, and add a matching changelog heading such as
`## 0.78.31 — version 108`. Keep entries about changes; put validation in
BUILD_STATUS.md and workflow work in an Unreleased section.

Numeric versions combine the upstream version and fork revision. Release titles
use that number; filenames are `nfs3-VERSION-armv7.apk`,
`nfs3-VERSION-armv7-symbols.zip` and `nfs3-VERSION-armv7-release.json`.
Tags retain `armv7-vCODE-runRUN_ID` for traceability. Historical TV names remain
supported. The old `profile` suffix described enabled performance profiling;
profiling remains enabled without the suffix. Package ID and signing identity
stay unchanged. This manifest does not control the ordinary ARM64 version.

## Local builds

Run from the repository root. Automatic bootstrap supports Linux x86_64 with
Python 3.12+, `curl`, `git` and `bash`; other hosts need tools installed explicitly.

```sh
# Optional preparation; every mode prepares its own prerequisites.
python3 tools/android.py setup --accept-sdk-licenses
python3 tools/android.py tests --accept-sdk-licenses
python3 tools/android.py check --accept-sdk-licenses
python3 tools/android.py apk --accept-sdk-licenses \
  --keystore /private/armv7-tv-release.p12 \
  --password-file /private/password.txt
```

Use `apk-fast` with the same signing arguments to skip tests. Omit
`--accept-sdk-licenses` when licenses are already accepted. `setup --tests-only`
prepares launcher tools only. Outputs go to `out/`; override with `--output-dir`.
Signing credentials are checked before large downloads. `apk --unsigned` creates
an intermediate that requires signing before installation. To sign without rebuilding:

```sh
python3 tools/android.py sign \
  --keystore /private/armv7-tv-release.p12 \
  --password-file /private/password.txt
```

Keep the prepared APK and matching native build outputs for resource verification
and exact symbols. `--apk PATH` selects a different prepared APK.

## Tools, caches and credentials

The bootstrap reuses compatible installed tools and downloads missing tools with
checksum verification. Selected versions live in the toolchain manifest; use the
Gradle wrapper. Review upgrades deliberately, then validate and try them on-device.

Use `NFS_BUILD_CACHE` or `--cache-dir` to preserve tools/dependencies. The default
is `nfs3-build-cache` beside the repository. `JAVA_HOME`, `ANDROID_HOME`,
`ANDROID_SDK_ROOT` and `GRADLE_USER_HOME` override discovery. Keep machine paths
in ignored files. Run one setup per cache at a time. Native compilation defaults
to two jobs and one link job; increase `--jobs` only with enough memory.
Actions caches dependencies, selected tools and pinned SDL. Caches are not archives.
Low-level Gradle flags are `-Parmv7Tv -PprofileNative`; `-PlauncherTestsOnly`
is restricted to launcher tests and rejects APK tasks.

Both APK modes use the configured GitHub secrets `ANDROID_KEYSTORE_BASE64`
(base64 of the original `.p12`, not the recovery ZIP) and
`ANDROID_KEYSTORE_PASSWORD`. The workflow verifies the certificate early and
removes temporary credentials outside caches. Local builds need the original
private files outside the repository. Never put credentials in Git, caches,
logs or artifacts. Public alias: `armv7-tv-release`. Certificate SHA-256:
`464eab8f658b68c234e80e85f5bcb6c5a79771600ac04c0f9d5458769c27b60e`.
