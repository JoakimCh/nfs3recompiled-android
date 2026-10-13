#!/usr/bin/env python3
"""Count the port's native and generated functions, exactly.

Reads src/nfs3hp/disassembly (what disassemble_nfs3hp.py wrote, and the
tools/apply_native_*.py hooks patched) and sorts every function of nfs3.exe into:

  native whole      the generated code has no body, only `/* sub_X: native, ... */`
                    (GAME_NATIVES, WATCOM_NATIVES, MMX_NATIVES, ...)
  native, hooked    the generated function stays, but opens with a call to a native
                    one (`/* port: native (tools/apply_native_X.py) */`) and runs it
                    unless it says no; counted per tools/apply_native_*.py
  generated only    everything else

eacsnd and voodoo2a are native whole: their exports are only declared in the
generated code, and bound to the port's functions of the same names.

Usage: tools/count_functions.py [--list] [--json]
  --list   print each function with its class
  --json   machine-readable output
"""
import argparse
import json
import re
import sys
from collections import Counter
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
SRC = ROOT / "src/nfs3hp/disassembly"

DEFINITION = re.compile(r"^void Application::(\w+)\(", re.M)
NATIVE_WHOLE = re.compile(r"^/\* (\w+): native(?:, ([^*]*?))? \*/", re.M)
HOOK = re.compile(r"/\* port: native \(tools/(\w+)\.py\) \*/")
EXPORT = re.compile(r"^void (\w+)\(win32::WinApplication\* app, x86::CPU& cpu\);", re.M)


def read(path):
    return path.read_text(encoding="utf-8", errors="replace")


def scan_nfs3hp():
    whole = {}      # function -> native stand-in
    hooked = {}     # function -> hook tool
    generated = []  # function names without a hook
    for path in sorted(SRC.glob("nfs3hp.*.cpp")):
        text = read(path)
        for m in NATIVE_WHOLE.finditer(text):
            whole[m.group(1)] = (m.group(2) or "").strip()
        defs = list(DEFINITION.finditer(text))
        for i, m in enumerate(defs):
            end = defs[i + 1].start() if i + 1 < len(defs) else len(text)
            body = text[m.start():end]
            hooks = HOOK.findall(body)
            if hooks:
                hooked[m.group(1)] = hooks[0]
            else:
                generated.append(m.group(1))
    return whole, hooked, generated


def exports(module):
    path = SRC / (module + ".cpp")
    return sorted(set(EXPORT.findall(read(path)))) if path.exists() else []


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--list", action="store_true")
    ap.add_argument("--json", action="store_true")
    args = ap.parse_args()
    if not SRC.is_dir():
        sys.exit("no %s" % SRC)

    whole, hooked, generated = scan_nfs3hp()
    dupes = set(whole) & (set(hooked) | set(generated))
    by_tool = Counter(hooked.values())
    eacsnd, voodoo = exports("eacsnd"), exports("voodoo2a")

    result = {
        "nfs3hp": {
            "generated_bodies": len(hooked) + len(generated),
            "generated_only": len(generated),
            "native_hooked": len(hooked),
            "native_hooked_by_tool": dict(sorted(by_tool.items())),
            "native_whole": len(whole),
            "native_total": len(hooked) + len(whole),
            "functions_total": len(hooked) + len(generated) + len(whole),
        },
        "eacsnd_native_exports": len(eacsnd),
        "voodoo2a_native_exports": len(voodoo),
    }
    if dupes:
        result["warning_native_whole_also_has_body"] = sorted(dupes)

    if args.json:
        print(json.dumps(result, indent=2))
    else:
        n = result["nfs3hp"]
        print("nfs3.exe (nfs3hp)")
        print("  functions in all             %6d" % n["functions_total"])
        print("  generated, no native         %6d" % n["generated_only"])
        print("  native, hooked (body stays)  %6d" % n["native_hooked"])
        for tool, count in sorted(by_tool.items()):
            print("      %-26s %4d" % (tool, count))
        print("  native whole (no body)       %6d" % n["native_whole"])
        print("  native in all                %6d" % n["native_total"])
        print("  generated bodies in all      %6d" % n["generated_bodies"])
        print("eacsnd   native exports (no generated code)  %3d" % len(eacsnd))
        print("voodoo2a native exports (no generated code)  %3d" % len(voodoo))
        if dupes:
            print("warning: native whole yet with a body:", ", ".join(sorted(dupes)))

    if args.list:
        for f, s in sorted(whole.items()):
            print("native-whole  %-12s %s" % (f, s))
        for f, t in sorted(hooked.items()):
            print("native-hooked %-12s %s" % (f, t))
        for f in sorted(generated):
            print("generated     %s" % f)


if __name__ == "__main__":
    main()
