# Verified build state

Current evidence is below; versioned changes are in [CHANGELOG.md](CHANGELOG.md),
artifact identities in [releases/](releases/), and older session details in Git history.

## Pending TV text-input fix — untested

The owner reports that the TV keyboard opens and accepts gamepad navigation,
but player-name characters and backspace do not reach the game. Local changes
handle IME text key events directly, synchronize deletion with the invisible
editor, and preserve complete multi-character commits in the Win32 message bridge.
Backspace/return character messages now precede subsequent queued text, so
composition replacements cannot insert their new text before deleting the old.
Regression tests were added but have not been run. No build or device validation
has been performed; the reported complete input failure still needs TV verification.

## 0.78.38 / code 115 — current main, APK pending

Merged into main at `a7a2c53` from `experiment-build-time-precision`, based on
previous main `d0d5cd58`.
DOUBLE (default) compiles out single-significand rounding and float/retry vertex
dispatch. SINGLE retains main's upstream policy. There is no launcher selector;
see [BUILD.md](BUILD.md) for CMake, Gradle and runner flags.

At `2942e020`, both modes passed 46 tooling tests and 30 launcher tests, with no
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

### Rendering cleanup

On 2026-11-08 both precision modes passed 46 tooling and 33 launcher tests after
the renderer cleanup (zero failures/errors/skips). The SINGLE run disabled the
Gradle build cache after clearing stale Kotlin compiler outputs. The renderer
also passed ARMv7/ARM64 native compilation, the
million-case opaque-classification check, and a Mesa llvmpipe GL comparison using
production shader and submission code: 320 paired scenes / 640 submissions,
bit-exact RGBA across 1,310,720 pixels. It covers depth quantization, shader
switches, fog/gamma, blending, depth, clipping, wrapping, chroma and alpha fallback.
The retired opaque environment override was set to zero during the GL check;
the built-in optimization remained available.

GL-call checks for eight state-identical batches pass: opaque-only uses one
program bind and four uniform calls; general-only uses one and ten; alternating
shaders use eight and fourteen. The old boundary-analysis pass and optional
opaque enable checks are removed. New overlay tests cover real-window FPS,
precision-specific counters, idle state, unavailable shaders and legacy preferences.

No APK, full native application link or device benchmark has been performed for
current 0.78.38 code. Signing/reporting code is updated, but a signed APK with the new
precision marker has not yet been verified. The latest verified version remains
0.78.37 below. Owner feedback favoring the old Extended mode motivates this work;
it does not measure the current code.

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
| [0.78.33](releases/0.78.33.json) | Rebuilt locally on 2026-11-08 for regression testing from exact commit `2915ab2`. Signed ARMv7 APK; 40 tooling tests, 23 launcher tests and 314 resource checks passed. Branch `log-warning-cleanup` contains that source. |
| 0.78.32 | [Hosted universal build](https://github.com/JoakimCh/nfs3recompiled-android/actions/runs/41719407758) passed; its one-day artifacts have expired. |
| [0.78.31](releases/0.78.31.json) | Signed local ARMv7 APK, launcher/controller/resource checks passed; device feedback was incomplete. |
| [tv28](releases/tv28.json) | Original local APK reported working. [Hosted publication](https://github.com/JoakimCh/nfs3recompiled-android/actions/runs/41326807799) also succeeded. |

The old selectable-arithmetic branch had a `trackVertices` NaN/finite discrepancy
at mode `047f`, case 99. It is not evidence against or proof of correctness for
the new fixed mode; see [PERFORMANCE.md](PERFORMANCE.md).
