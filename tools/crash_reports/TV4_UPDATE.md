# tv4: packed-vector safety and lower rendering cost

APK version 0.78-armv7-tv4, version code 81. Same package/signing certificate
as tv1–tv3. Install over the old app; retain game data and crash reporting.

## Confirmed TV crash

The uploaded tv3 report is from MOKA R10G / CEPTER, Android 14, ARMv7-only.
It reports SIGBUS / BUS_ADRALN in vertices::addVectors at relative PC 0x4782e8
(offset 96); Build ID 004086cb6ac73bbe406e759d4e2c60baa1e0b0ef. The fault address
0x4203e176 is two-byte aligned. Stack: addVectors -> track::drawObjectList ->
drawTrack -> render::viewPass -> graphics::raceFrame. The earlier vertex-load
fix helped the user play, but this exposed another float-pointer access to
packed data. Do not label this as an x87 precision problem or GPU crash.

## Change

GuestFloats uses the engine's existing memcpy-backed MemoryAccessor<float>
for indexed reads and writes, replacing 39 host float-pointer views in the
native vertex/render/vector helper module. Bulk matrix transfers use byte
addresses. This prevents the compiler from assuming alignment on guest data.
The small/large packed-vertex copies from tv3 are retained.

Three views in the original trackVerticesWith projection loop remain as tv3:
a broad conversion there caused a synthetic directed-rounding edge mismatch,
so that unrelated loop was restored. This is not a guarantee that every
possible packed access in the entire game is now covered.

Vector add/subtract and scale dispatch to direct double arithmetic once per
call in the existing default double-backed mode. Single/other/wide/exact modes
retain the prior FPU arithmetic. No global float conversion or fast-math.

The ARMv7 app sets NFS_MIRROR_FULL=0 before starting SDL. This restores the
original shorter/coarser mirror instead of the full-detail second view,
reducing scene work while keeping the main camera settings unchanged. This
is a real quality/performance tradeoff; no on-TV FPS gain is measured here.

## Validation

Default double-backed FPU, GCC 13.3, -O2, no strict aliasing/contraction,
-frounding-math. All 45 rendering functions passed 100 randomized cases in
each of eight guest FPU modes: 36,000 comparisons. World::vectors now tests
byte offsets 0..3, including in-place output. The existing NaN payload/sign
exception is applied relative to the actual vector-output base, rather than
an assumed four-byte alignment; other memory differences remain failures.
The clean final log is evidence/tv4/tv4-validation-clean.log. Earlier failed
experiments and overlapping temporary logs are not the final result.
Wide/exact FPU configurations also passed syntax compilation only.

The retained benchmark mode now includes addVectors, subtractVectors and
scaleVectors. Compare tv3 vs tv4 with identical fixed finite 1,024-vector
fixtures, 200,000 calls, median of five alternating runs. Raw data and summary
are saved in the checkpoint. These are x86-64 CPU kernel timings, not ARMv7
FPS measurements or an estimate of overall game speed.

APK checks: same signing identity, ARMv7-only libraries, non-debug release,
16 KB zip alignment, updated version code, report collector retained.
No phone/TV/emulator run was available here. User should just play normally
and share the automatic report if it crashes again.
