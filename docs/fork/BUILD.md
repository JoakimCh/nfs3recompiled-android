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

Select `main` for the merged version, or a feature branch to build its changes.
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

## Publish an existing APK as a release

Use **Publish APK release** (`.github/workflows/publish-apk.yml`) after building
an APK. It publishes the existing signed file without rebuilding or using signing
credentials. Release downloads are separate from expiring Actions artifacts.

The workflow is available on `main`. To publish a build:

1. Open **Actions → Publish APK release → Run workflow**.
2. Select the workflow branch. Leave **Build branch** blank to use that branch,
   or enter the branch containing the APK build.
3. Leave **APK run ID** blank for that branch's latest successful signed APK run,
   or paste a specific run ID (the number after `/actions/runs/` in its URL).
4. Choose **prerelease** or **release**. A regular release becomes the latest release.
5. Start the workflow. Its summary links to the published release.

The workflow checks that the source commit, successful tests, signed APK hash
and symbol metadata agree. It uploads the APK, exact symbols, verification JSON
and checksums. The release tag identifies the version code and build run, for
example `armv7-v105-run41324391872`, and points to that build's exact source commit.
A prerelease does not replace the repository's latest regular release.
Selecting either type leaves the original build metadata unchanged.

Release titles use the TV version, such as **NFS III ARMv7 TV — tv28**. Notes come
from `docs/fork/CHANGELOG.md` at the **APK's source commit**, even when the workflow
itself runs from a newer commit. They include versioned entries after the previous
published ARMv7 release through the APK version: tv25–tv28 when updating from tv24.
The previous release's tag must be in the APK's source history. Regular releases
compare against the previous regular release; prereleases can compare against an
earlier prerelease too. Rebuilds of the same TV version use the preceding lower
version. With no earlier release, only the current version's changes are included.

Maintain a heading such as `## tv28 — version 105` for every TV version, matching
the APK's version name and version code. Keep these entries about game/launcher
changes. Put device feedback and validation records in BUILD_STATUS.md and
unreleased workflow work in separate Unreleased sections. Legacy personal
feedback and known maintenance-only notes are omitted when reading older entries.
Unreleased sections, future versions and the previous version's own changes are
excluded. Missing, empty or inconsistent entries stop publication before a draft
is created. Technical build information is collapsed below the changes.

The selected run must be a successful signed APK run from the build workflow on
the chosen branch. Missing or expired artifacts stop publication; the workflow
never silently substitutes an older APK. Publish before artifact expiry, or make
a new APK build. Published assets remain available on the repository's
[Releases page](https://github.com/JoakimCh/nfs3recompiled-android/releases).

Existing tags/releases are never overwritten. To recreate a deleted release from
the same APK run, delete its tag too (for example `armv7-v105-run41324391872`).
Deleting a release alone leaves the tag behind. A failed upload may leave a draft;
inspect and delete an incomplete draft before retrying. If its tag exists too,
remove it only after confirming it belongs to that failed attempt. The workflow
requests `actions: read` and `contents: write` for its publishing job. GitHub
automatically supplies a temporary `GITHUB_TOKEN`, passed to the CLI as `GH_TOKEN`.
No personal token, new secret or change to repository-wide default token
permissions is needed. It runs only when manually started.

The initial hosted publication succeeded. The revised changelog-based notes have
local test coverage and an exact-source preview; their first hosted run remains
pending. See BUILD_STATUS.md for the recorded evidence.

## Version naming: agreed plan for the next build

The next build should replace names such as `0.78-armv7-tv28-profile` with a
numeric version. This is an agreed convention, **not yet implemented**; the
current build and publishing scripts still use the TV naming described above.

| Item | Next-build example |
| --- | --- |
| App version and release title | `0.78.29` |
| APK filename | `nfs3-0.78.29-armv7.apk` |
| Symbols filename | `nfs3-0.78.29-armv7-symbols.zip` |
| Android version code | `106`, increased from tv28's `105` |

`0.78` identifies the upstream version; `29` identifies this fork's revision.
Architecture belongs in filenames and metadata. Profiling capability belongs in
build metadata, without a `profile` suffix in the version or release title.
The old suffix means local performance profiling is enabled; the build remains
non-debuggable. Removing the suffix does not require disabling profiling.

Implement the change together in Gradle, signing/output filenames, release title
generation, previous-release detection and changelog lookup. Use an explicit
version/code mapping instead of requiring `tvNN` in an APK name. Keep the existing
code/run-based release tags for traceability. Preserve the application ID and
signing identity, and continue increasing Android version codes.

The publishing workflow must still recognize old TV versions, filenames and
changelog headings, including when promoting an existing APK. Leave historical
APKs, tags and release metadata intact. Add the new version's changelog entry and
update the instructions above when the migration is implemented; do not change
only the version string while the scripts still depend on its old format.

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
