# Verified build state

This file records evidence, not a substitute for checking the current source and
latest Actions run. A new context should read AGENTS.md, BUILD.md and this file.

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

## GitHub Actions: legacy workflow verified

[Successful run 41316976331](https://github.com/JoakimCh/nfs3recompiled-android/actions/runs/41316976331)
completed on 2026-11-01, building **tv27/version 104 from main**, source commit
`7349f4b97f2406360313b09c50ac4ed4d5482c1c`.

The signing-credential check, build, original-certificate verification and separate
APK/symbol artifact uploads succeeded. Launcher tests were skipped because the
old `run_tests` input was not enabled. This proves the repository's two signing
secrets worked at that time. Their values are not available through GitHub reads.

An earlier feature-branch run was skipped by the old main-only job condition. It
never checked credentials. The revised workflow removes that restriction.

## New automation: implementation awaiting validation

The branch adds `tests`, `check` and `apk` manual modes, caching, the complete local
bootstrap/wrapper, tests-only native exclusion and compilation job pools. These
new paths have **not yet been run**. Do not transfer the legacy workflow's verified
status to them. Keep execution manual, with `tests` as the default.

When execution is authorized, validate the three modes and local recovery path,
then update this section with actual run URLs, source commits, cache observations
and test counts. Retain failures as diagnostic evidence; do not infer success from
a queued, skipped or old run. After publication, confirm the branch contains the
intended workflow revision before directing the user to its mode selector.
