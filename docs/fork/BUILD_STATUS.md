# Verified build state

This file records evidence, not a substitute for checking the current source and
latest Actions run. A new context should read AGENTS.md, BUILD.md and this file.

## Release publishing: locally tested; hosted run pending

The manual `publish-apk.yml` workflow and `tools/release/publish_android.py` promote
an existing signed APK run to a prerelease or release. On 2026-11-01, all ten
release-helper tests and three setup tests passed. They covered publication
ordering with mocked GitHub calls, keeping a failed upload private as a draft,
source selection, mismatched files, expired artifacts and existing-tag refusal.
Workflow structure checks confirmed manual dispatch, prerelease default and the
built-in token with job-scoped permissions. Actual hosted release publication
has not run yet; no GitHub Release has been created by this implementation.
See [BUILD.md](BUILD.md#publish-an-existing-apk-as-a-release) for usage on `main`.

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
