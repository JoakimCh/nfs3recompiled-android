"""The game's code for the menus' screens that are native whole, made afresh
from nfs3hp/nfs3.exe by the port's own generator.

    python3 generate.py <out.cpp>

The screens of disassemble_nfs3hp.py's MENU_NATIVES have no generated code in
src/nfs3hp/disassembly: their addresses are bound to the port's functions.
For frontend_checks.cpp to compare those with the game's code, it is written
here as the generator writes any function -- every call in it by address
(sub_...), as extract.py leaves the hooked ones' -- and extract.py takes it
from here.  The whole game is read, a minute or so.
"""
import io
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT))
sys.path.insert(0, str(ROOT / "disasm"))

from disasm import disassembler  # noqa: E402
from disasm.codegen import fpu as fpu_codegen  # noqa: E402
import disassemble_nfs3hp as nfs3hp  # noqa: E402


def main():
    out = Path(sys.argv[1])
    game = disassembler.disassemble("nfs3hp", str(ROOT / "nfs3hp/nfs3.exe"), nfs3hp.DATA_SEGMENTS,
                                    nfs3hp.KNOWN_SUBROUTINES, nfs3hp.SPLIT_INSTRUCTIONS,
                                    nfs3hp.THREAD_ROUTINES, nfs3hp.THREAD_SEGMENTS, nfs3hp.MERGE_ROUTINES)
    fpu_codegen.EXACT = True  # as Application.write has the game's arithmetic
    code = io.StringIO()
    written = set()
    for subroutine in game.subroutines:
        entry = subroutine.get_entry_point()
        if entry in nfs3hp.MENU_NATIVES:
            game.write_function(code, subroutine, "sub_%x" % entry, {}, nfs3hp.THREAD_SEGMENTS,
                                nfs3hp.SKIP_INSTRUCTIONS)
            written.add(entry)
    missing = set(nfs3hp.MENU_NATIVES) - written
    if missing:
        raise SystemExit("no function at %s" % " ".join("%x" % a for a in sorted(missing)))
    out.write_text(code.getvalue())


if __name__ == "__main__":
    main()
