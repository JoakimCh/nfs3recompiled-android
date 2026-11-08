# Verified build state

Current evidence is below; versioned changes are in [CHANGELOG.md](CHANGELOG.md),
artifact identities in [releases/](releases/), and older session details in Git history.

## 0.78.38 / code 115 — build time precision experiment

Branch `experiment-build-time-precision` starts from main `d0d5cd58`.
DOUBLE (default) compiles out single-significand rounding and float/retry vertex
dispatch. SINGLE retains main's upstream policy. There is no launcher selector;
see [BUILD.md](BUILD.md) for CMake, Gradle and runner flags.

On 2026-11-08 both modes passed 46 tooling tests and 30 launcher tests, with no
failures, errors or skips. The new checks cover arithmetic selection, integer
rounding and invalid integer conversions, APK/report precision labels, and
rejection of mismatched release metadata. Both modes passed NDK policy inspection
and native vertex machine-code generation for ARMv7 and ARM64. DOUBLE output
contains hardware double arithmetic without the float/retry or single-rounding
helpers; SINGLE retains main's ABI-specific policy.

GCC host comparisons passed all 45 vertex functions at 200 cases each per mode
using freshly generated references compiled with the same policy. DOUBLE had two
accepted NaN-only output-word differences; SINGLE had one. Each mode stopped ten
particle cases at a stubbed callee, so those cases have partial coverage. These
checks establish consistency with the selected policy, not original-game physics
compatibility or a measured FPS improvement.

No APK, full native application link or device benchmark has been performed for
this experiment. Signing/reporting code is updated, but a signed APK with the new
precision marker has not yet been verified. The latest verified APK remains
0.78.37 below. Owner feedback favoring the old Extended mode motivates this work;
it does not measure the new candidate.

## 0.78.37 / code 114 — signed universal APK

Built locally on 2026-11-06 from clean, published source
`9590520b1677f9ae3d8b9a6e2c3b9f9894e30c1a` on
`integrate-upstream-vertex-cleanup`. This merges `vertex-double-dispatch`
(`919280cf`) with upstream `9c27ce73`. No GitHub build workflow was used.
The APK was subsequently signed with the original release key without rebuilding.
[Release metadata](releases/0.78.37.json) records hashes, certificate, toolchain,
native Build IDs and separate build/signing source commits.

| Check | Result |
| --- | --- |
| Tooling tests | 44 passed |
| Launcher tests | 29 passed; no failures, errors or skips |
| Native build | ARMv7 and ARM64 compiled and linked |
| NDK arithmetic policy | Both ABIs passed |
| SDL controller regression | Passed |
| APK verification | Original certificate, package/version, both ABI/ELF sets, 332 resource IDs, ZIP alignment and matching native symbols passed |
| Release configuration | Non-debuggable, shell-profileable; ARM64 ELF alignment at least 16 KiB, ARMv7 at least 4 KiB |
| Device correctness / FPS | Pending |

GCC host comparisons exercised 45 vertex functions at 200 cases each, normally
and with `NFS_VERTEX_NO_FLOAT_FAST_PATH` (ARMv7-style fallback). The normal path
had one accepted NaN-only output-word difference in `objectVerticesNearest`;
the fallback had none. Each path stopped 10 particle cases at a stubbed callee,
so those cases have partial coverage. These runs use upstream's fixed `007f`
mode; they do not validate the removed eight-mode experiment.

A final local runner invocation disabled Gradle's build cache after a transient
cache-packaging failure. It passed on the same clean source.

## Remaining validation

- Test this APK on ARMv7 TV and ARM64 phone: launcher layouts, larger fonts,
  gamepad assignment/pause, touch bindings, Exit, intro/attract playback,
  settings backups and log export.
- Compare upstream and fork on matching races, including split screen, mirrors,
  transparent geometry, replay determinism and long sessions. No FPS gain is claimed.
- If using hosted builds again, verify the updated action versions, requested
  14-day retention, standalone tests/check modes and `apk-fast` promotion.

## Historical evidence

| Revision | Evidence and limits |
| --- | --- |
| 0.78.36 / 0.78.35 | Dual-ABI native and automated checks passed; no APK or device benchmark. Double dispatch is removed in 0.78.37. |
| [0.78.34](releases/0.78.34.json) | Signed local ARMv7 APK. Owner saw no graphical differences among the experimental modes; perceived speed was not a controlled measurement. |
| 0.78.32 | [Hosted universal build](https://github.com/JoakimCh/nfs3recompiled-android/actions/runs/41719407758) passed; its one-day artifacts have expired. |
| [0.78.31](releases/0.78.31.json) | Signed local ARMv7 APK, launcher/controller/resource checks passed; device feedback was incomplete. |
| [tv28](releases/tv28.json) | Original local APK reported working. [Hosted publication](https://github.com/JoakimCh/nfs3recompiled-android/actions/runs/41326807799) also succeeded. |

The old selectable-arithmetic branch had a `trackVertices` NaN/finite discrepancy
at mode `047f`, case 99. It is not evidence against or proof of correctness for
the new fixed mode; see [PERFORMANCE.md](PERFORMANCE.md).
