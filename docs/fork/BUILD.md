# Android checks, builds and signing

Local and optional GitHub builds share [android-toolchain.json](../../tools/android-toolchain.json)
and `tools/android.py`. See [BUILD_STATUS.md](BUILD_STATUS.md) for verified results
and [WORKSPACE.md](WORKSPACE.md) for setup troubleshooting.

## Local builds

Run from the repository root. Automatic bootstrap supports Linux x86_64 with
Python 3.12+, `curl`, `git` and `bash`; other hosts need tools installed explicitly.

```sh
# Optional: each execution mode prepares its own prerequisites.
python3 tools/android.py setup --accept-sdk-licenses
python3 tools/android.py tests --accept-sdk-licenses
python3 tools/android.py check --target both --accept-sdk-licenses
python3 tools/android.py apk --target both --accept-sdk-licenses \
  --keystore /private/armv7-tv-release.p12 \
  --password-file /private/password.txt
```

| Mode | Work | Output |
| --- | --- | --- |
| `tests` | Tooling and launcher tests | Reports |
| `check` | Tests and native compilation/linking | Reports; no APK |
| `apk` | Tests, native build, packaging, signing and verification | Signed APK, reports and symbols |
| `apk-fast` | APK build and verification, skipping tooling and launcher tests | Signed APK, reports and symbols; `tests: null` |

`apk` includes tests; running every mode in sequence is unnecessary. Select
`--target armv7`, `armv8`, or `both` for one universal APK. The local default is
`armv7`; Android chooses the compatible runtime in a universal APK.
Outputs go to `out/`; use `--output-dir` to change it. Omit
`--accept-sdk-licenses` once accepted. `setup --tests-only` prepares launcher tools only.

Signing files are checked before large downloads. To build an unsigned
intermediate, use `apk --unsigned`. It cannot be installed until signed:

```sh
python3 tools/android.py sign --target both \
  --keystore /private/armv7-tv-release.p12 \
  --password-file /private/password.txt
```

Use the build's target when signing. Keep the prepared APK and exact native build
outputs for resource and symbol verification; `--apk PATH` selects another input.
When signing after documentation-only commits, retain the actual build commit
and unsigned APK hash in validation metadata; signing HEAD is not the build identity.

## Verification and signing identity

All fork targets use package `dev.nfs3hp.port.armv7tv` and the original release key.
Verification checks certificate, package/version, selected ABIs and ELF architecture,
16 KiB ZIP alignment, non-debuggable/profileable state, resources and exact native
Build IDs. Device testing and FPS measurements are separate. Preserve the APK,
release metadata and matching symbols together. Never commit binaries or keys.

Local signing files must remain outside source and caches. GitHub builds use
`ANDROID_KEYSTORE_BASE64` (the original `.p12`, not the recovery ZIP) and
`ANDROID_KEYSTORE_PASSWORD`; temporary files are removed after use.
Public alias: `armv7-tv-release`. Certificate SHA-256:
`464eab8f658b68c234e80e85f5bcb6c5a79771600ac04c0f9d5458769c27b60e`.

## Tools and caches

The bootstrap reuses compatible installed tools and verifies downloaded checksums.
Use the pinned Gradle wrapper and review toolchain upgrades deliberately.
`NFS_BUILD_CACHE` or `--cache-dir` controls the cache (default: `nfs3-build-cache`
beside the repository). `JAVA_HOME`, `ANDROID_HOME`, `ANDROID_SDK_ROOT` and
`GRADLE_USER_HOME` override discovery. Keep machine paths in ignored files.
Run one setup per cache; compilation defaults to two jobs and one link job.
Increase `--jobs` only with enough memory. Caches are not artifact archives.

The runner sets `-PforkRelease -PgameAbis=armeabi-v7a,arm64-v8a -PprofileNative`
for a universal build. `-Parmv7Tv` remains a legacy ARMv7 alias.
`-PlauncherTestsOnly` disables native configuration and rejects APK tasks.
Plain Gradle without fork flags uses the upstream package/version and defaults to ARM64.

## Optional GitHub builds

Open [Android checks and builds](https://github.com/JoakimCh/nfs3recompiled-android/actions/workflows/armv7-release.yml),
choose **Run workflow**, the intended branch, mode and native target. Modes match
the table above; defaults are `tests` and `both`. The historical workflow filename
serves all targets. With GitHub CLI:

```sh
gh workflow run armv7-release.yml --ref BRANCH -f mode=apk -f target=both
```

Check the completed steps and source commit; an old or skipped run is not validation.
Download these artifacts from the run (sign-in may be required):

| Artifact | Contents |
| --- | --- |
| `TARGET-apk` | ZIP containing signed APK and metadata; extract to install |
| `TARGET-native-symbols` | Matching crash symbols |
| `TARGET-MODE-reports` | Validation and available test reports |

`TARGET` is `armv7`, `armv8`, or `both`. Workflows request 14-day retention; set
the repository limit under **Settings → Actions → General** and inspect each
run's actual expiry. Retention changes do not extend existing artifacts.

## Publish an existing hosted APK

In [Publish APK release](https://github.com/JoakimCh/nfs3recompiled-android/actions/workflows/publish-apk.yml),
select the workflow/build branch, matching target and prerelease/release type.
Supply an APK run ID or leave it blank for the latest successful signed build of
that target and branch. The publisher reuses hosted artifacts without rebuilding
or signing; it does not upload a local APK.

Publication requires clean source, native compilation, verified matching APK/symbols,
and passing tests or explicit `apk-fast` skipped-test metadata. Missing, expired
or inconsistent artifacts stop publication. Regular releases become latest;
prereleases do not. [Published downloads](https://github.com/JoakimCh/nfs3recompiled-android/releases)
are retained beyond workflow artifact expiry.

Release notes use versioned changelog entries at the APK's source commit since
the preceding published fork version. Rebuilds compare with a lower version;
first releases include their own entry. Unreleased sections are excluded.
Existing releases/tags are not overwritten. Inspect a failed draft before retrying;
recreating an existing release requires deleting both its release and tag.
GitHub supplies the publishing token; no personal token is needed.

## Versions and changelog

[android-release.json](../../tools/android-release.json) defines fork `versionName`,
`versionCode` and `revision`. Update all three together and add a matching heading,
e.g. `## 0.78.37 — version 114`, to [CHANGELOG.md](CHANGELOG.md).
Keep validation in BUILD_STATUS.md and build automation in an Unreleased section.

Versions combine upstream version and fork revision. Files use
`nfs3-VERSION-TARGET.apk`, `nfs3-VERSION-TARGET-symbols.zip` and
`nfs3-VERSION-TARGET-release.json`, with `armv7`, `armv8` or `universal` as TARGET.
Hosted tags use `TARGET-vCODE-runRUN_ID` (`both` for universal).
Historical TV/profile names remain supported; profiling, package and signing
identity are unchanged. The fork version manifest does not set upstream's version.
