"""voodoo2a's generated code, made afresh from nfs3hp/voodoo2a.dll.

    python3 generate.py <out dir>

What disassemble_nfs3hp.py makes of voodoo2a, without the port's hooks: the
code thrash_checks.cpp compares the natives with, the segments it loads, and
voodoo2a_methods.inc, every function's address and name, for the calls its
code makes through pointers.  The game's own sections and eacsnd's and
softtria's are read only for where voodoo2a goes after them.  Needs capstone,
as disassemble_nfs3hp.py does.
"""
import os
import shutil
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT))
sys.path.insert(0, str(ROOT / "disasm"))

from disasm import disassembler, dll  # noqa: E402
from disasm.application import Application  # noqa: E402
import disassemble_nfs3hp  # noqa: E402


def after(module):
    return module.sections[-1][1] + module.sections[-1][2]


def main():
    out = Path(sys.argv[1]).resolve()
    out.mkdir(parents=True, exist_ok=True)
    for old in out.glob("voodoo2a*"):
        old.unlink()
    game = Application("nfs3hp", str(ROOT / "nfs3hp/nfs3.exe"), 0)
    eacsnd = dll.DLL("eacsnd", str(ROOT / "nfs3hp/eacsnd.dll"), after(game))
    softtria = dll.DLL("softtria", str(ROOT / "nfs3hp/softtria.dll"), after(eacsnd))
    voodoo2a = disassembler.disassemble("voodoo2a", str(ROOT / "nfs3hp/voodoo2a.dll"), type=dll.DLL,
                                        data_segments=disassemble_nfs3hp.VOODOO2A_DATA_SEGMENTS,
                                        known_subroutines=disassemble_nfs3hp.VOODOO2A_KNOWN_SUBROUTINES,
                                        rebase_after=softtria)
    here = os.getcwd()
    with tempfile.TemporaryDirectory() as tmp:
        os.chdir(tmp)
        try:
            voodoo2a.write("nfs3hp")
        finally:
            os.chdir(here)
        made = Path(tmp) / "src/nfs3hp/disassembly"
        for path in made.glob("voodoo2a*"):
            if path.name != "voodoo2a.cpp":  # its exports' table: nothing here loads the DLL
                shutil.copy(path, out / path.name)
    with open(out / "voodoo2a_methods.inc", "w") as methods:
        for subroutine in sorted(voodoo2a.subroutines, key=lambda s: s.get_entry_point()):
            entry = subroutine.get_entry_point()
            methods.write("{0x%08x, &voodoo2a::sub_%x},\n" % (entry, entry))
    print("voodoo2a: %d functions" % len(voodoo2a.subroutines), file=sys.stderr)


if __name__ == "__main__":
    main()
