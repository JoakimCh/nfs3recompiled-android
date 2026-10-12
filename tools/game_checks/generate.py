"""The game's code for the functions src/nfs3hp/native_game.cpp has natively,
made afresh from nfs3hp/nfs3.exe.

    python3 generate.py <out dir>

What disassemble_nfs3hp.py makes of nfs3.exe, without the port's hooks: each
function of its GAME_NATIVES as the game's code has it (game_functions.cpp),
every function those call by address named in a header of their own
(nfs3hp.h, for game_checks.cpp to stand in for), and the game's data
(game_data.cpp), which game_checks.cpp loads.  Needs capstone, as
disassemble_nfs3hp.py does; the whole of the game is read, which takes a
minute or so.
"""
import io
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT))
sys.path.insert(0, str(ROOT / "disasm"))

from disasm import disassembler  # noqa: E402
from disasm.codegen import fpu as fpu_codegen  # noqa: E402
import disassemble_nfs3hp as nfs3hp  # noqa: E402


def main():
    out = Path(sys.argv[1]).resolve()
    out.mkdir(parents=True, exist_ok=True)
    game = disassembler.disassemble("nfs3hp", str(ROOT / "nfs3hp/nfs3.exe"), nfs3hp.DATA_SEGMENTS,
                                    nfs3hp.KNOWN_SUBROUTINES, nfs3hp.SPLIT_INSTRUCTIONS,
                                    nfs3hp.THREAD_ROUTINES, nfs3hp.THREAD_SEGMENTS, nfs3hp.MERGE_ROUTINES)
    fpu_codegen.EXACT = True  # as Application.write has the game's arithmetic
    natives = nfs3hp.GAME_NATIVES
    code = io.StringIO()
    tested = []
    for subroutine in game.subroutines:
        entry = subroutine.get_entry_point()
        if entry in natives:
            game.write_function(code, subroutine, "sub_%x" % entry, {}, nfs3hp.THREAD_SEGMENTS,
                                nfs3hp.SKIP_INSTRUCTIONS)
            tested.append(entry)
    if sorted(tested) != sorted(natives):
        raise SystemExit("no function at %s" % sorted(set(natives) - set(tested)))
    text = code.getvalue()
    called = sorted(set(int(a, 16) for a in re.findall(r"\bsub_([0-9a-f]+)\(app", text)) - set(natives))

    with open(out / "game_functions.cpp", "w") as f:
        f.write('#include "nfs3hp.h"\n#include <lib/thread.h>\n\nnamespace nfs3hp\n{\n\n%s}\n' % text)
    with open(out / "nfs3hp.h", "w") as h:
        h.write("#ifndef NFS3HP_H_\n#define NFS3HP_H_\n#include <x86.h>\n#include <lib/winapp.h>\n\n"
                "namespace nfs3hp\n{\n\n")
        for address, name in sorted(natives.items()):
            h.write(game.native_declaration(address, name))
        h.write("\nclass Application : public win32::WinApplication\n{\npublic:\n"
                "    /* The game's code for the natives (game_functions.cpp). */\n")
        for address in sorted(natives):
            h.write("    static void sub_%x(WinApplication* app, x86::CPU& cpu);\n" % address)
        h.write("    /* What it calls by address: game_checks.cpp's stand-ins. */\n")
        for address in called:
            h.write("    static void sub_%x(WinApplication* app, x86::CPU& cpu);\n" % address)
        h.write("};\n\n}\n\n#endif\n")
    with open(out / "game_tested.inc", "w") as f:
        for address, name in sorted(natives.items()):
            f.write('{0x%x, "%s", &nfs3hp::Application::sub_%x, &nfs3hp::%s},\n' % (address, name, address, name))
    with open(out / "game_called.inc", "w") as f:
        for address in called:
            f.write("STAND_IN(%x)\n" % address)
    with open(out / "game_data.cpp", "w") as f:
        f.write('#include <x86.h>\n\n/* The game\'s data as it loads: its address, length and bytes. */\n')
        names = []
        for data, address, length, name, ro, is_code in game.sections:
            if data and not is_code:
                data = bytes(data[:length])
                names.append((address, len(data), name.decode()))
                f.write("extern const x86::reg8 kGame%s[] = {\n" % name.decode())
                for i in range(0, len(data), 32):
                    f.write("    %s,\n" % ", ".join("0x%02x" % b for b in data[i:i + 32]))
                f.write("};\n")
        f.write("extern const struct GameSegment { x86::reg32 address, length; const x86::reg8* bytes; } "
                "kGameSegments[] = {\n")
        for address, length, name in names:
            f.write("    {0x%x, %d, kGame%s},\n" % (address, length, name))
        f.write("};\nextern const unsigned kGameSegmentCount = %d;\n" % len(names))
    print("nfs3hp: %d functions tested, %d stood in for: %s" % (
        len(tested), len(called), " ".join("%x" % a for a in called)), file=sys.stderr)


if __name__ == "__main__":
    main()
