# tv8-profile: first profile-guided rendering experiment

Release 0.78-armv7-tv8-profile, version85, original package/certificate.
Install over tv7-profile; data and gamepad settings remain. Release optimized,
non-debug, profileable. No game arithmetic, shaders, vertex format, precision,
resolution, detail or controller changes.

The phone profile has6914 cpu-clock:u samples. drawPending including callees
accounts for14.07%, glDrawArrays10.88% (overlapping), submitPolygons5.86%.
These are CPU shares, not FPS, GPU execution time or expected speedups.

Changes:
1. Move four vertex-attribute pointer definitions and four enables from every
   drawPending submission to initGl after shader linking. The renderer's VAO,
   VBO object and attribute locations are fixed. VAO is rebound for every
   submission; replacing VBO storage via glBufferData does not change bindings.
2. Coalesce only contiguous batches in one ThrashDraw when all actual state
   fields match. Compare texture, mip levels, format, wrap, depth test/function/
   write, blend, cull/mode, chromakey, clip rectangle, fog table, gamma bits.
   End offsets are deliberately excluded. Compare fields explicitly to avoid
   struct padding; compare gamma bits to preserve signed zero/NaN distinctions.
   Never reorder triangles or merge across submissions, clears or uploads.
   Batches in the game-thread Watcher/snapshot are unchanged; only GL draws merge.

Validation: tools/render_batch_checks/check.cpp uses the actual Batch method
and run-selection helper. Every individual state boundary is checked, along
with signed zero/NaN, A-A-B-A ordering, triangle coverage and state for1,000,000
synthetic batches. Synthetic draws reduced to510655, which is NOT a game
measurement or FPS prediction. Android ARMv7 release compilation and signed
APK cert/version/ABI/non-debug/profileable/alignment checks are performed.
GL-thread output is not validated by the old THRASH harness, which drops that
work. Hardware visuals/performance remain untested. No speedup is claimed.

Next: user installs and plays normally, checks visuals/crashes and optionally
records the same race/settings using the profiling helper. Evaluate actual
CPU cost before expanding changes. If neighbors rarely match, discard merge
rather than assuming benefit. No ADB or exhaustive testing requested by default.

Host test command from source root:
 g++ -std=c++17 -O2 -DWITH_MMX -I include -I sdl3/include tools/render_batch_checks/check.cpp -o batch-check
 ./batch-check

Build: assembleRelease -Parmv7Tv -PprofileNative with JDK21, Gradle9.3.1,
SDK36/buildtools36.0.0, NDK28.2.13676358, CMake3.22.1, SDL release-3.4.2.
The pruned toolchain was recreated; ZIP symlinks/permissions had to be restored.
Full native symbols must match this build; do not use tv7 symbols for tv8.
