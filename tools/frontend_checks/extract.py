"""Copies generated functions out of src/nfs3hp/disassembly, without hooks.

    python3 extract.py <disassembly dir> <out.cpp> <mocks.inc> sub_... sub_...

Every port hook (`/* port: native (tools/apply_*.py) */`) is taken out of
them on the way: what is left is the generated code alone, for
frontend_checks.cpp to compare the decompiled functions with.  Each function
they call that is not among them goes to <mocks.inc> as a stand-in that
records the call (see frontend_checks.cpp).
"""
import re
import sys
from pathlib import Path

HOOK = re.compile(r"    if \(\w+\(app, cpu(?:\.sync\(\))?\)\) "
                  r"/\* port: native \(tools/apply_\w+\.py\) \*/\r?\n"
                  r"    \{\r?\n(?:        cpu\.reload\(\);\r?\n)?        return;\r?\n    \}\r?\n")
CALL = re.compile(r"\bsub_([0-9a-f]{6})\(app")


def main():
    source = Path(sys.argv[1])
    out = Path(sys.argv[2])
    mocks = Path(sys.argv[3])
    wanted = set(sys.argv[4:])
    found = {}
    for path in sorted(source.glob("nfs3hp.*.cpp")):
        lines = path.read_text(errors="replace").split("\n")
        i = 0
        while i < len(lines):
            m = re.match(r"^void Application::(sub_[0-9a-f]+)\(", lines[i])
            if m and m.group(1) in wanted:
                end = i + 1
                while lines[end].rstrip("\r") != "}":
                    end += 1
                found[m.group(1)] = HOOK.sub("", "\n".join(lines[i:end + 1]))
                i = end
            i += 1
    missing = wanted - set(found)
    if missing:
        raise SystemExit("not found: " + " ".join(sorted(missing)))
    called = set()
    with out.open("w") as f:
        f.write('#include "nfs3hp.h"\n\nnamespace nfs3hp\n{\n\n')
        # What the port's own changes to them call (tools/apply_text_entry.py).
        f.write("void textEntry(bool taking);\n\n")
        for name in sorted(found):
            if "/* port: native" in found[name]:
                raise SystemExit("a hook left in " + name)
            f.write(found[name] + "\n\n")
            called |= {"sub_" + c for c in CALL.findall(found[name])}
        f.write("}\n")
    with mocks.open("w") as f:
        f.write("// Written by extract.py: the generated functions' callees, recorded.\n")
        for name in sorted(called - set(found)):
            f.write("void Application::%s(WinApplication* app, x86::CPU& cpu) { mock(app, cpu, 0x%s); }\n"
                    % (name, name[4:]))
    with Path(str(mocks) + ".generated").open("w") as f:
        for name in sorted(found):
            f.write("{0x%s, &Application::%s},\n" % (name[4:], name))


if __name__ == "__main__":
    main()
