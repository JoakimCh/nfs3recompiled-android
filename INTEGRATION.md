# ARMv7/controller integration into the GitHub fork

Integrated 2026-10-31 from checkpoint tv21-source-r3 onto
JoakimCh/nfs3recompiled-android main at 49d2dea02ea67c4cc28a8fdf08646e0901e6ca0c.
The checkpoint's upstream base was f908f336a4dfd9c7116c872fb91018b5152a45ae.
The fork includes alphaG0.78 (4a65cd49) and the owner's README introduction.

## Merge

Reconstructed the cumulative source changes against the original base, then
rebased them onto the fork head. Git reported no conflicts. The only file changed
by both the upstream update and our checkpoint was src/lib/thrashrenderer.cpp;
its merged code passed host syntax checks and opaque-policy checks. Every file
changed only by upstream was verified byte-for-byte against the fork head.
All newer generated disassembly, decompiled menu/sound changes, upstream fixes
and the owner's README introduction remain. No historical/generated game code
was replaced wholesale with the checkpoint snapshot.

Private checkpoint signing credentials, toolchain/cache files and binaries not
already part of upstream were excluded. The source snapshot contained one local
Kotlin session marker; it was removed and android/.kotlin is now ignored.
Private signing paths/extensions are also ignored. The next ARMv7 version is
99/tv22 so an eventual build cannot be confused with released tv21.

## Focused validation performed

- Existing eight Java host checks passed: automatic controls/slots, touch state,
  control-profile migration/preservation, input buffer, controller profiles,
  device-role/remote policy, crash store and bonus-content file updates.
- Existing SDL 3.4.2 native gamepad regression check passed, including real SDL
  virtual pad axes/buttons/hats, menu/capture behavior, generic per-device
  profiles, simultaneous Android/SDL sources, two-player isolation, repeats,
  remapping priority, pause and disconnect cleanup.
- 72 packed-vertex bit-pattern/alignment checks passed with alignment sanitizer.
- Host syntax compilation passed for native_vertices.cpp,
  native_controls_host.cpp, native_controls_pipeline.cpp and thrashrenderer.cpp
  against the merged tree's generated declarations.
- Conservative opaque policy passed 1,000,000 randomized cases. Native performance
  checks passed with collection disabled and enabled; native input-trace helper
  checks passed. These are host correctness checks, not FPS measurements.
- git diff --check passed. Public payload is UTF-8 source/docs/tests only; no
  private release keys or passwords were added.

## Remaining validation

No Android APK or full Android/Compose compilation was performed for this
integration. The source-r2 bonus UI and source-r3 Advanced cleanup also remain
unbuilt. No physical phone/TV verification or GPU render comparison was done
here. Before delivering a new APK, perform the targeted Android page/lifecycle
checks and final packaged resource check in ARMV7_TV_BUILD.md, followed by normal
release metadata/signing/alignment verification. The previous hardware-tested
release remains tv21. This branch is suitable for review as a draft PR; the
above host checks do not establish device readiness.
