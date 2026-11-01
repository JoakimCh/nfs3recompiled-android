# Verified build state

This file records evidence, not a substitute for checking the current source and
latest Actions run. A new context should read AGENTS.md, BUILD.md and this file.

## Assignment feedback: untested

Selected next version: 0.78.30/code 107. Shortcut capture displays the pending
first button and an ellipsis beside the controls, with a local second-button
prompt and input feedback. Confirm, Back and both shortcut steps share validation
that rejects D-pad directions (including their existing logical aliases), D-pad
center and axis bindings. Directional menu assignments retain their prior input
support. Existing saved bindings are preserved.

The wording and all 18 translations were updated. Regression tests were added
for validation, nearby progress/error feedback and Confirm/Back rejection.
These changes are published on `feature/controller-pause-pair`. Tests and APK
builds have not been run for this revision.

## Controller assignment and two-button race pause: user feedback

Changes on `feature/controller-pause-pair` selected version 0.78.29/code 106:
assignment no longer starts input testing automatically, and race pause captures
two independent buttons. The saved pair is committed only when complete. Old
Back-plus-extra preferences migrate once, and backup format 3 carries both buttons
while accepting older exports.

Before publication, the standalone Java ControllerProfileCheck passed, including
arbitrary pairs, duplicate/alias rejection, unchanged pairs after menu Back edits,
button release and per-controller isolation. Java syntax parsing passed for all
seven changed launcher/test files, and all 19 resource sets parsed with matching
new keys. These checks do not substitute for Android compilation or Robolectric.
The native regression was extended for a non-Back pair and both press orders.
Android/Robolectric tests and the SDL native regression have not been run in this
workspace. Joakim subsequently reported the build worked, then requested a clearer
first-button cue. He also reported that his Zero 2 D-pad could not be assigned to
Confirm or Back in either mode. Button-only assignment remains the chosen policy;
the latest local changes add explicit feedback rather than axis support. The run
ID and device coverage of that successful build have not been recorded here.

## Numeric version migration

The numeric migration introduced `0.78.29`, Android version code `106`, fork
revision `29`. Current versions are defined in `tools/android-release.json`.
Gradle and signing use that mapping;
APKs use `nfs3-0.78.29-armv7.apk`. The package and certificate are unchanged.
Profiling remains enabled independently of the version string.

Before the workspace reset, all 29 tooling tests and all 14 launcher tests passed
locally. The Gradle merged manifest confirmed version 0.78.29/code 106, the existing
package ID, non-debuggable state and enabled profiling. A release-notes preview
matched the new changelog entry to the historical tv28 baseline.

The local changes were restored from this conversation after the workspace reset.
All 26 release-helper tests passed again before publication; launcher tests were not
rerun because the Android toolchain was not restored. At that point no numeric
APK had been built; the later user feedback on the two-button shortcut build is
recorded above. The new 0.78.30 feedback changes remain untested.

## Release publishing: initial hosted run verified; revised notes tested locally

[Publication run 41326807799](https://github.com/JoakimCh/nfs3recompiled-android/actions/runs/41326807799)
succeeded on 2026-11-01 from workflow commit `e93c02e5891770b86a0bee0be76ea8b096157731`.
The publish step completed and created
[the tv28 release](https://github.com/JoakimCh/nfs3recompiled-android/releases/tag/armv7-v105-run41324391872)
with all five expected assets. Its APK SHA-256 matches the source build below.
This verifies the built-in token permissions and publication of existing artifacts.

The revised notes use the changelog from the APK's source commit, select the
previous published ARMv7 version in that source history, and omit personal
feedback. The title is simplified and build details are collapsed. All 23 tooling
tests passed locally (20 release helper tests and three setup tests), including
missing changelog entries, source/version matching, legacy tags, prerelease
baselines and rejection before publication. A preview using the actual tv28 source
and published release records selected tv24 as baseline and included tv25–tv28.
GitHub's comparison API confirmed that the tv24 tag is an ancestor of that source.
Joakim subsequently reported trying the revised release workflow and liking its
notes. That user report is recorded separately from the locally inspected checks;
the retry run ID has not been recorded here.

To recreate a release from the same APK run, delete its existing release and tag
before retrying. See
[BUILD.md](BUILD.md#publish-an-existing-apk-as-a-release) for usage on `main`.

## Application: tv28, version 105

- Built locally from application source commit `25f196cce192aeaffdab1636f8bed217ec324298`.
- Signed APK: `nfs3-0.78-armv7-tv28-profile-release.apk`.
- APK SHA-256: `44324da857215a38ec21a107e140260f4ea6262f7f74314ee85b20c4e1894e37`.
- Native BuildID: `b1318854f2c1a78da77910d5ef0e080cc82d14da`; matching symbols retained separately.
- Original ARMv7 signing certificate verified, all 301 packaged R fields matched,
  ARMv7-only ELF/16K alignment/non-debuggable/profileable checks passed.
- All 14 launcher tests passed: five backup tests, eight controller tests (APIs 34/36),
  one advanced-screen test. Controller UI test selectors were fixed locally before
  this successful run; that fix is included with the automation changes.
- On 2026-11-01, Joakim reported testing build 28 and finding no problems. Device model
  and individual feature coverage were not specified.
- Full application metadata: [releases/tv28.json](releases/tv28.json).

## GitHub Actions: current APK workflow verified

[APK run 41324391872](https://github.com/JoakimCh/nfs3recompiled-android/actions/runs/41324391872)
succeeded on 2026-11-01 on `feature/launcher-wording-backups-translations`, source
commit `5f68209a56b0dc4d26974b80191466f761655f3d`, with a clean working tree.
It built **tv28/version 105** in about seven minutes, including cache uploads.

- All three tooling tests and all 14 launcher tests passed, with no skipped tests.
- Native compilation, APK packaging, early signing-credential verification and
  final original-certificate signing/verification succeeded.
- All 301 packaged R fields matched. ARMv7 ABI, 16K alignment,
  non-debuggable/profileable state and matching native symbols were verified.
- All three artifact uploads succeeded: APK, symbols and test reports.
- Gradle, native tools and SDL caches were absent initially and saved successfully
  afterwards. This validates cold hosted APK setup. Warm restoration is untested.
- APK SHA-256: `cfb2d4683231634b6472da9cd75bd458694369c61bfd82d4a98d5a3cc2eaadbe`.
- Native BuildID: `23070215567f86d1a4c783977ec7ecb42e8ef1df`.
- The newly built APK has not been device tested; Joakim's successful device test
  above applies to the earlier local tv28 binary.

The repository capped all artifact retention at **one day**, overriding the
workflow's requested 14/90 days. This run's artifacts expire on 2026-11-02 at
17:04 Oslo time. Download the APK and exact symbols before expiry if needed.
See [BUILD.md](BUILD.md) for download and retention instructions.

Standalone hosted `tests` and `check` modes have not run. APK mode already passed
tests and native compilation, so those runs are optional checks of their separate
execution paths, not prerequisites for using this APK. A repeat run can verify
warm cache restoration. Record future runs against their actual source commits.

## Shared runner: local validation

Published automation commit: `f674acd863ccb3f86bc4052a00e58d39e849f0b9` on
`feature/launcher-wording-backups-translations`. Local checks on 2026-11-01:

- All three setup-helper tests passed, including safe SDK layout repair and
  archive path traversal rejection. Workflow structure checks passed.
- The shared bootstrap installed an isolated launcher-only SDK. A fresh Android
  test run with caching disabled passed all 14 tests, with no NDK installed.
- Tests mode passed again with installed tools and warm dependency caches.
- The launcher-only guard rejected an APK assembly request.
- Check mode passed launcher tests and compiled/linked the native game. The
  existing APK's size and modification time were unchanged.
- APK mode passed tests, packaging and signing with the original certificate.
  All 301 packaged R fields matched; ARMv7 ABI, 16K alignment,
  non-debuggable/profileable state and matching native symbols were verified.
- Simulated GitHub secret handling accepted wrapped base64, rejected a wrong
  password and removed temporary signing files on success and failure.

The rebuilt APK has SHA-256
`6eed8ff7da37fc300ab1c2f8a4c21425d8cfee7645e330e489a75565b6fc55a1`
and native BuildID `ef5e94be11704f3c0ce36bd9b7cf9db7b583e64f`.
It has not been device tested. Reports identify source commit `f674acd` and a
working tree with unrelated untracked content (and documentation edits during
packaging); no application source changes were included. This is distinct from
Joakim's successfully tested original tv28 binary above.

The local native checks reused installed tools; the isolated launcher bootstrap
installed fresh SDK packages using a verified cached installer. Cold native
bootstrap was subsequently exercised by the hosted APK run above.

## Earlier GitHub Actions runs

[Successful run 41316976331](https://github.com/JoakimCh/nfs3recompiled-android/actions/runs/41316976331)
completed on 2026-11-01, building **tv27/version 104 from main**, source commit
`7349f4b97f2406360313b09c50ac4ed4d5482c1c`.

The signing-credential check, build, original-certificate verification and separate
APK/symbol artifact uploads succeeded. Launcher tests were skipped because the
old `run_tests` input was not enabled. This proves the repository's two signing
secrets worked at that time. Their values are not available through GitHub reads.

An earlier feature-branch run was skipped by the old main-only job condition. It
never checked credentials. The revised workflow removes that restriction.
