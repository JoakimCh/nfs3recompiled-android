"""Whether thrash_checks catches what it is there to catch.

    python3 tools/thrash_checks/mutations.py [cases]

Each mutant runs on the export it touches and stops at the first case it gets
wrong; one that gets none wrong in `cases` (5000) is missed.

Builds thrash_checks again and again, each time with one mistake put into a
copy of src/nfs3hp/native_thrash.cpp or native_watcom_heap.cpp -- a vertex in
the wrong order, a Glide argument off, a check left out, the heap's
bookkeeping a step wrong -- and expects it to fail.  Only the mutant is
compiled; the rest is linked from what tools/thrash_checks/run.sh built, so
run that first.
"""
import subprocess
import sys
import tempfile
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[1]

THRASH = "native_thrash.cpp"
HEAP = "native_watcom_heap.cpp"

# (the export it is checked on, what, the file, [(the text, what it becomes), ...])
MUTATIONS = [
    ("THRASH_drawtristrip", "every triangle wound as the first", THRASH,
     [("            if (!((i & 1) ? triangleThrough(app, cpu, target, first, next, second)\n",
       "            if (!((i & 1) ? triangleThrough(app, cpu, target, first, second, next)\n")]),
    ("THRASH_drawtristrip", "where the next six start not kept", THRASH,
     [("            if (i % 6 == 5)\n                put(app, esp + 8,", "            if (false)\n                put(app, esp + 8,")]),
    ("THRASH_drawtri", "the second pass blended as the first", THRASH,
     [("        gl::alphaBlendFunction(app, cpu, 4, 4, 0, 0);\n", "        gl::alphaBlendFunction(app, cpu, 4, 0, 0, 0);\n")]),
    ("THRASH_drawtri", "the second pass weighted as the first", THRASH,
     [("        gl::texCombine(app, cpu, 0, 9, 0xd, 9, 0xd, 0, 0);\n", "        gl::texCombine(app, cpu, 0, 9, 5, 9, 5, 0, 0);\n")]),
    ("THRASH_drawquad", "a quad's diagonal smoothed", THRASH,
     [("                         { 1, 1, target == kSmoothTriangle ? 1u : 0u });\n", "                         { 1, 1, 1u });\n")]),
    ("THRASH_drawquad", "a quad's second half from the wrong corner", THRASH,
     [("            && triangleThrough(app, cpu, at(app, kQuadDraw), vc, vd, va);\n",
       "            && triangleThrough(app, cpu, at(app, kQuadDraw), vc, vd, vb);\n")]),
    ("THRASH_drawline", "a line drawn in two passes", THRASH,
     [("    if (target == kNoLine)\n        return true;\n", "")]),
    ("THRASH_drawlinestrip", "one line short", THRASH,
     [("        for (x86::sreg32 i = 0; i < count; ++i)\n        {\n            const win32::GrVertex to",
       "        for (x86::sreg32 i = 1; i < count; ++i)\n        {\n            const win32::GrVertex to")]),
    ("THRASH_drawpoint", "the point from the wrong argument", THRASH,
     [("    const win32::GrVertex v = convert(at(app, esp + 4));\n    if (!guestDraw(",
       "    const win32::GrVertex v = convert(at(app, esp + 8));\n    if (!guestDraw(")]),
    ("THRASH_drawpointmesh", "an index taken as 16 bytes a vertex", THRASH,
     [("        const win32::GrVertex v = convert(vertices + (at(app, point) << 5));\n",
       "        const win32::GrVertex v = convert(vertices + (at(app, point) << 4));\n")]),
    ("THRASH_drawpoint", "t where q goes", THRASH,
     [("{ 0x24, v.tmuvtx[0].sow }, { 0x28, v.tmuvtx[0].tow },", "{ 0x24, v.tmuvtx[0].sow }, { 0x2c, v.tmuvtx[0].tow },")]),
    ("THRASH_drawquad", "the smoothing flags before the vertices", THRASH,
     [("    for (const win32::GrVertex* v : vertices)\n    {\n        putVertex(app, vertex, *v);\n        put(app, slot, vertex);\n        vertex += 0x3c;\n        slot += 4;\n    }\n    for (const x86::reg32 argument : more)\n    {\n        put(app, slot, argument);\n        slot += 4;\n    }\n",
       "    for (const x86::reg32 argument : more)\n    {\n        put(app, slot, argument);\n        slot += 4;\n    }\n    for (const win32::GrVertex* v : vertices)\n    {\n        putVertex(app, vertex, *v);\n        put(app, slot, vertex);\n        vertex += 0x3c;\n        slot += 4;\n    }\n")]),
    ("THRASH_writerect", "a byte a pixel", THRASH,
     [("at(app, esp + 0x10), width * 2, at(app, esp + 0x14) });", "at(app, esp + 0x10), width, at(app, esp + 0x14) });")]),
    ("THRASH_writerect", "the hook not told the lock is over", THRASH,
     [("    if (cpu.terminate || !lockHook(app, cpu, 0))\n        return;\n    cpu.eax = result;\n    cpu.esp = esp + 4 + 0x14;",
       "    if (cpu.terminate)\n        return;\n    cpu.eax = result;\n    cpu.esp = esp + 4 + 0x14;")]),
    ("THRASH_is", "2.42 itself too old", THRASH,
     [("                    if (compareText(app, number, 0xa916ec) < 0)", "                    if (compareText(app, number, 0xa916ec) <= 0)")]),
    ("THRASH_is", "no board taken as 0", THRASH,
     [("            result = boards;  // no board, or -1 of them, is what it says\n", "")]),
    ("THRASH_is", "Glide's version written over the saved ebx", THRASH,
     [("    cpu.esp = esp - 0x54;\n    const x86::reg32 version = cpu.esp;", "    cpu.esp = esp - 0x50;\n    const x86::reg32 version = cpu.esp;")]),
    ("THRASH_modemessage", "closing alone gives back the caller's ebx", THRASH,
     [("        cpu.ebx = at(app, esp + 0x10);\n", "")]),
    ("THRASH_about", "a Glide function stored though the game stopped", THRASH,
     [("        const x86::reg32 function = stdcall(app, cpu, at(app, kGetProcAddress), { at(app, kGlideModule), name });\n        if (cpu.terminate)\n            return 0;\n        put(app, entry, function);",
       "        const x86::reg32 function = stdcall(app, cpu, at(app, kGetProcAddress), { at(app, kGlideModule), name });\n        put(app, entry, function);\n        if (cpu.terminate)\n            return 0;")]),
    ("THRASH_setvideomode", "DirectDraw released by the pointer read first", THRASH,
     [("    const x86::reg32 refuser = at(app, kDirectDraw);  // read again, as voodoo2a does\n    stdcall(app, cpu, at(app, at(app, refuser) + 8), { refuser });",
       "    stdcall(app, cpu, at(app, at(app, object)), { object });")]),
    ("malloc/free", "a remainder of 16 bytes kept whole", HEAP,
     [("    if (left >= 0x10)\n", "    if (left > 0x10)\n")]),
    ("malloc/free", "a freed block never joined to the one before", HEAP,
     [("    if (word(app, before) + before == block)\n", "    if (false)\n")]),
    ("malloc/free", "the heap grown by odd steps", HEAP,
     [("        size = word(app, h.blockSize) & ~x86::reg32(1);\n", "        size = word(app, h.blockSize);\n")]),
    ("malloc/free", "the miniheap a free found forgotten", HEAP,
     [("        put(app, h.freeRover, heap);\n", "")]),
    ("malloc/free", "the largest block before the rover not kept", HEAP,
     [("            if (largest > word(app, h.largestBefore))\n                put(app, h.largestBefore, largest);\n", "")]),
    ("malloc/free", "the rover past the last miniheap given back", HEAP,
     [("        if (after != 0)\n        {\n            put(app, h.rover, after);\n        }\n        else\n        {\n            put(app, h.largestBefore, 0);\n            put(app, h.rover, word(app, h.first));\n        }\n",
       "        put(app, h.rover, after);\n")]),
    ("malloc/free", "empty miniheaps kept", HEAP,
     [("    return shrink(app, cpu, h) && create(app, cpu, h, amount, result);", "    return create(app, cpu, h, amount, result);")]),
    ("malloc/free", "the heap's end mark one dword early", HEAP,
     [("    put(app, first + length, 0xffffffff);\n", "    put(app, first + length - 4, 0xffffffff);\n")]),
    ("THRASH_lockwindow", "the record's stride and pointer swapped", THRASH,
     [("            put(app, record, pixels);\n", "            put(app, record, stride);\n")]),
]


def main():
    cases = sys.argv[1] if len(sys.argv) > 1 else "5000"
    build = Path(__import__("os").environ.get("BUILD", HERE / "build"))
    double = build / "double"
    base = sorted((double / "base").glob("*.o"))
    if not base:
        raise SystemExit("run tools/thrash_checks/run.sh first")
    missed = 0
    with tempfile.TemporaryDirectory() as tmp:
        for export, what, name, edits in MUTATIONS:
            text = (ROOT / "src/nfs3hp" / name).read_text()
            for old, new in edits:
                if text.count(old) != 1:
                    raise SystemExit("mutation does not apply: " + what)
                text = text.replace(old, new)
            source = Path(tmp) / name
            source.write_text(text)
            obj = Path(tmp) / (source.stem + ".o")
            exe = Path(tmp) / "mutant"
            # Only the mutant is compiled; the rest is run.sh's, linked as it is.
            subprocess.run(["c++", "-std=c++17", "-O1", "-fno-strict-aliasing", "-DWITH_MMX", "-w",
                            "-I" + str(build / "generated"), "-I" + str(ROOT / "sdl3/include"),
                            "-I" + str(ROOT / "include"),
                            "-I" + str(ROOT / "src/nfs3hp"), "-c", str(source), "-o", str(obj)], check=True)
            other = double / ("native_watcom_heap.o" if name == THRASH else "native_thrash.o")
            subprocess.run(["c++"] + [str(p) for p in base] + [str(obj), str(other), "-o", str(exe)], check=True)
            result = subprocess.run([str(exe), cases, "--first", export], capture_output=True, text=True)
            caught = result.returncode != 0
            missed += 0 if caught else 1
            print("%-8s %s: %s" % ("caught" if caught else "MISSED", export, what), flush=True)
    print("%d of %d caught" % (len(MUTATIONS) - missed, len(MUTATIONS)))
    sys.exit(1 if missed else 0)


if __name__ == "__main__":
    main()
