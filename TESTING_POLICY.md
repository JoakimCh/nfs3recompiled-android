# Focused validation and recovery policy

Agreed with the user 2026-10-31. Retain existing test infrastructure, but keep each
change's validation proportional to the actual risk and scope. The user prefers
minimal manual testing and prompt, installable non-debug APKs.

- Every release: build, original signing certificate, version/ABI, non-debug and
  profileable status, alignment, native BuildID, and final APK resource-class
  consistency. Verify the artifact delivered, not just its separate build inputs.
- Input changes: run the existing relevant controller/profile/routing regressions.
- UI changes: run targeted page/lifecycle checks for the affected behavior.
- Rendering changes: use checks relevant to the changed renderer behavior.
- Documentation/checkpoint-only changes: verify archive contents and checksums;
  do not rebuild the APK or rerun game/UI suites.

After relevant checks pass, stop broadening or repeating tests unless changes,
failures or unresolved concerns justify it. Avoid adding frameworks, unrelated
features or speculative fixes to a small repair. Existing Robolectric/native/Java
checks remain reusable; do not recreate their infrastructure each session.
Report hardware validation separately from host/simulated checks. Do not invent
measured speedups from subjective feedback. Preserve precise game math, existing
controller fixes and user-tested split screen unless the task requires changes.

Recovery and builds

This repository contains the merged source, tests and build documentation. Start
with ARMV7_TV_BUILD.md. Older tools/**/TV*_UPDATE.md and SOURCE_UPDATE.md are
historical engineering notes, not evidence that the current revision was built.
Downloaded toolchains/dependencies and generated outputs remain ignored. Original
release signing materials are held separately and must never be pushed. If a
workspace resets, clone this fork/branch again; ask for a private checkpoint only
when its non-public signing material is specifically required for a signed APK.
