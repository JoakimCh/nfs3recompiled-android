# tv3: packed object vertices on ARMv7

Version 0.78-armv7-tv3, code 80; same app ID/signing identity as tv1/tv2.
The user-provided tv2 report identifies Samsung SM-A266B, Android 16,
executing the ARM32 app. Do not mislabel this as a trace from the Cepter TV.

## Confirmed diagnosis

SIGBUS, BUS_ADRALN, SDLThread. Matching tv2 Build ID:
d59473651543cde10e0b25b578a5ec95e93b1c05.
Frame 0 relative PC 0x477db6: objectVerticesList, native_vertices.cpp:4743.
The instruction was VLDR s0,[r11], r11=0xddacfb8e (two-byte alignment).
The input guest vertex address was 0x11bcb8e. The matrix and translation
addresses were naturally aligned. The stack continues through viewObjectVertices,
drawObjectList, drawTrack, viewPass and raceFrame. This directly confirms a
packed geometry load fault during race rendering, rather than a precision or
GPU settings diagnosis.

## Fix

readPackedVertex copies three float bit patterns from byte storage into a
naturally aligned std::array. Use it in the small objectVerticesList loop and
the >20-vertex objectVerticesWith path. It preserves arithmetic/precision,
registers and output behavior. It does not disable memory protection or
change SIMD/FPU modes. The new ARM disassembly loads the packed bytes with
ordinary LDR instructions followed by VMOV, avoiding the faulting VLDR from
the packed source. Other untested faults remain possible; try a race normally.
The diagnostic report feature remains enabled without debug mode.

## Validation

- 72 float-bit-pattern checks across offsets 0..7, including NaNs, infinities,
  signed zero and subnormals, with undefined-behavior/alignment sanitizers.
- 3,200 differential rendering cases across eight FPU modes passed. The fixture
  randomly offsets object list inputs by two bytes, for both <=20 and >20 paths.
  The upstream comparator counted five NaN payload/sign-only words rather than
  failing them; no other differences were reported.
- ARM release built; inspected resulting input loads in ARM disassembly.
- APK signature matches tv1/tv2, debuggable=false, ARMv7-only, alignment verified.
- No runtime test on the phone or TV was available here.

The checkpoint retains tv2 and tv3 symbol archives, report, decoded stack,
fixed disassembly, and test output. Always match the report Build ID to its
symbol archive. If another crash occurs, request only the automatic report.
