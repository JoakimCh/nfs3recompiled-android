"""eacsnd's generated code, made afresh from nfs3hp/eacsnd.dll.

    python3 generate.py <out dir>

What disassemble_nfs3hp.py makes of eacsnd, without the port's hooks: the code
sound_checks.cpp compares the natives with, and the segments it loads.  The
game's own sections are read only for where eacsnd goes after them.  Needs
capstone, as disassemble_nfs3hp.py does.
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


def main():
    out = Path(sys.argv[1]).resolve()
    out.mkdir(parents=True, exist_ok=True)
    for old in out.glob("eacsnd*"):
        old.unlink()
    game = Application("nfs3hp", str(ROOT / "nfs3hp/nfs3.exe"), 0)
    eacsnd = disassembler.disassemble("eacsnd", str(ROOT / "nfs3hp/eacsnd.dll"), type=dll.DLL,
                                      data_segments=disassemble_nfs3hp.EACSND_DATA_SEGMENTS,
                                      rebase_after=game)
    here = os.getcwd()
    with tempfile.TemporaryDirectory() as tmp:
        os.chdir(tmp)
        try:
            eacsnd.write("nfs3hp")
        finally:
            os.chdir(here)
        made = Path(tmp) / "src/nfs3hp/disassembly"
        for path in made.glob("eacsnd*"):
            if path.name != "eacsnd.cpp":  # its exports' table: nothing here loads the DLL
                shutil.copy(path, out / path.name)
    print("eacsnd: %d functions" % len(eacsnd.subroutines), file=sys.stderr)


if __name__ == "__main__":
    main()
