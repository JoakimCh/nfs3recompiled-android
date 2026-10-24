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


# The formatted output's entries -- vsprintf, sprintf, vfprintf -- as the
# other natives call them: by address, so through their stand-ins in
# game_checks.cpp on both sides, which print text of their own -- what the
# other natives hand them to format being made up.  The formatted output is
# tested itself with formats and arguments made to go together, and calls its
# own entries as it does (sprintf vsprintf, fprintf vfprintf).
# So are __tzset, exit and __MkTmpFile: the natives that call them (localtime,
# mktime, Error, tmpfile) are tested with their stand-ins -- the time zone
# made up, the game not left, a name made up -- and they are tested themselves.
# And _nrealloc, which __allocPOSIXHandle grows the handles' table with; and
# getche and __reporterror, the console's echo and the maths' error, whose
# stand-ins make up a key and _matherr's say.  Each with the natives that
# call it as they do, in the tests of their own.
STOOD_IN = {
    0x4df674: (0x4df690,),  # vsprintf: sprintf's
    0x4df690: (),
    0x4ff014: (0x4f4b80,),  # vfprintf: fprintf's
    0x4f4b80: (),           # fprintf: graphics::warnTextureMemory's
    0x4d37a0: (),           # graphics::shapeToPixels: the menus' art's
    0x515c2c: (),
    0x4dfd04: (),
    0x4ee168: (),
    0x5185c0: (0x4f8ce8, 0x518290, 0x52c178),  # _nrealloc: __setenv's, __wsetenv's, __wputenv's
    0x522e60: (),
    0x5243a7: (),
}


def force_feedback_car(text):
    """tools/apply_force_feedback_car.py's change, which forcePlayerCar has."""
    from tools.apply_force_feedback_car import SITES
    for _, instruction, old, new in SITES:
        start = text.index("    // " + instruction + "  ")
        stop = text.index("\n    // 00", start + 1)
        block = text[start:stop]
        assert block.count(old) == 1, instruction
        text = text[:start] + block.replace(old, new, 1) + text[stop:]
    return text


def music_stream(text):
    """tools/apply_music_stream.py's change, which raceMusicPrepare and
    raceMusicStart have: Pathfinder's start called by address here."""
    from tools.apply_music_stream import SITES
    for _, instruction, old, new, _ in SITES:
        old = old.replace("nfs3hp::snd::SNDpathstartstream", "sub_4e6f0c")
        new = new.replace("nfs3hp::snd::SNDpathstartstream", "sub_4e6f0c")
        if "    // " + instruction not in text:
            continue
        start = text.index("    // " + instruction)
        stop = text.index("\n    // 00", start + 1)
        block = text[start:stop]
        assert block.count(old) == 1, instruction
        text = text[:start] + block.replace(old, new, 1) + text[stop:]
    return text


# The port's own changes to the game's code that natives carry: made to the
# game's code for them too, so that each is held against what the port runs.
def port_sites(sites):
    """A tools/apply_*.py's SITES -- (file, instruction, old, new, ...) --
    made to the game's code where the instruction is in it."""
    def change(text):
        for site in sites:
            _, instruction, old, new = site[:4]
            anchor = "    // " + instruction
            if anchor not in text:
                continue
            start = text.index(anchor)
            stop = text.index("\n    // 00", start + 1)
            block = text[start:stop]
            assert block.count(old) == 1, instruction
            text = text[:start] + block.replace(old, new, 1) + text[stop:]
        return text
    return change


def widescreen(text):
    """tools/apply_widescreen.py's changes, which the Screen Size list's
    natives (graphics::listScreenModes, findScreenMode) have."""
    from tools.apply_widescreen import SITES
    return port_sites(SITES)(text)


def race_precision(text):
    """tools/apply_race_precision.py's change, which the loading screen's, the
    loading bar's and the game's main's natives have: the race's x87 word
    through nfs3hp::raceControl."""
    from tools.apply_race_precision import LOAD, EXTENDED, SITES
    for _, instruction in SITES:
        anchor = "    // " + instruction
        if anchor not in text:
            continue
        start = text.index(anchor)
        stop = text.index("\n    // 00", start + 1)
        block = text[start:stop]
        assert block.count(LOAD) == 1, instruction
        text = text[:start] + block.replace(LOAD, EXTENDED, 1) + text[stop:]
    return text


PORT_CHANGES = {0x4710f0: force_feedback_car, 0x410030: music_stream, 0x4107c0: music_stream,
                0x4bed90: widescreen, 0x4bee80: widescreen,
                0x494fa0: race_precision, 0x495230: race_precision, 0x4a39f0: race_precision}


def stand_ins():
    """The addresses game_checks.cpp's tables of the game's functions stand in
    for: their rows, {0x..., "name", ...}, in it and its parts."""
    here = Path(__file__).parent
    found = set()
    for path in [here / "game_checks.cpp"] + sorted(here.glob("*.inc")):
        found |= {int(a, 16) for a in re.findall(r'^\s*\{(0x[0-9a-f]+), "[^"]*", k(?:Watcom|Cdecl|Stdcall)',
                                                   path.read_text(encoding="utf-8"), re.M)}
    return found


def main():
    out = Path(sys.argv[1]).resolve()
    out.mkdir(parents=True, exist_ok=True)
    game = disassembler.disassemble("nfs3hp", str(ROOT / "nfs3hp/nfs3.exe"), nfs3hp.DATA_SEGMENTS,
                                    nfs3hp.KNOWN_SUBROUTINES, nfs3hp.SPLIT_INSTRUCTIONS,
                                    nfs3hp.THREAD_ROUTINES, nfs3hp.THREAD_SEGMENTS, nfs3hp.MERGE_ROUTINES)
    fpu_codegen.EXACT = True  # as Application.write has the game's arithmetic
    # The menus' screens are frontend_checks' (tools/frontend_checks).
    # Not held against their code: the sound and graphics code's dead stubs (they only stop
    # the game), and the mix and a channel's ramp, whose native mixer was held
    # against the game's mix by mix on the phone (0.77's snd_check).
    natives = {address: name for address, name in nfs3hp.GAME_NATIVES.items()
               if address not in nfs3hp.MENU_NATIVES and not name.startswith(("snd::dead_", "graphics::dead_"))
               and name not in ("snd::mixerServe", "snd::mixerRamp")}
    stood_in_natives = stand_ins() & set(natives)
    code = io.StringIO()
    tested = []
    for subroutine in game.subroutines:
        entry = subroutine.get_entry_point()
        if entry in natives:
            function = io.StringIO()
            game.write_function(function, subroutine, "sub_%x" % entry, {}, nfs3hp.THREAD_SEGMENTS,
                                nfs3hp.SKIP_INSTRUCTIONS)
            text = function.getvalue()
            if entry in PORT_CHANGES:
                text = PORT_CHANGES[entry](text)
            # The natives game_checks.cpp stands in for, from the others: by
            # address too, as the natives call them.
            for address in stood_in_natives:
                if address != entry:
                    text = text.replace("sub_%x(app, cpu.sync());" % address,
                                        "app->dynamic_call(0x%x, cpu.sync());" % address)
                    text = text.replace("return sub_%x(app, cpu.handOver());" % address,
                                        "return app->dynamic_call(0x%x, cpu.handOver());" % address)
            for address, callers in STOOD_IN.items():
                if entry not in callers:
                    text = text.replace("sub_%x(app, cpu.sync());" % address,
                                        "app->dynamic_call(0x%x, cpu.sync());" % address)
            # The menus' natives that are frontend_checks' are called by
            # address too, to their stand-ins (loadScreenArt's menuCurrentName).
            for address, name in nfs3hp.MENU_NATIVES.items():
                text = text.replace("nfs3hp::%s(app, cpu.sync());" % name,
                                    "app->dynamic_call(0x%x, cpu.sync());" % address)
            # And one controls file's natives, from another's: by address, to
            # stand-ins, as the natives call them.
            own = [group for group in nfs3hp.CONTROLS_GROUPS if entry in group]
            for group in nfs3hp.CONTROLS_GROUPS:
                if own and group is not own[0]:
                    for address in group:
                        text = text.replace("sub_%x(app, cpu.sync());" % address,
                                            "app->dynamic_call(0x%x, cpu.sync());" % address)
            code.write(text)
            tested.append(entry)
    if sorted(tested) != sorted(natives):
        raise SystemExit("no function at %s" % sorted(set(natives) - set(tested)))
    text = code.getvalue()
    # Where a graphics native's code jumps out into another piece of the
    # game's code (return sub_X(app, cpu.handOver())), that piece is part of
    # it -- a tail, not a call -- and comes along as the game has it, however
    # the port binds it (closeDriver's way out, graphics::dead_ on the port).
    graphics = [address for address, name in natives.items() if name.startswith("graphics::")]
    tails = set()
    pieces = {subroutine.get_entry_point(): subroutine for subroutine in game.subroutines}
    pending = [text[text.index("void Application::sub_%x(" % a):] for a in graphics]
    while pending:
        body = pending.pop()
        end = body.find("\nvoid Application::", body.find("void Application::") + 1)
        body = body[:end] if end >= 0 else body
        for tail in set(int(a, 16) for a in re.findall(r"return sub_([0-9a-f]+)\(app, cpu\.handOver\(\)\)", body)):
            if tail in natives or tail in tails or tail not in pieces:
                continue
            tails.add(tail)
            function = io.StringIO()
            game.write_function(function, pieces[tail], "sub_%x" % tail, {}, nfs3hp.THREAD_SEGMENTS,
                                nfs3hp.SKIP_INSTRUCTIONS)
            text += function.getvalue()
            pending.append(function.getvalue())
    called = sorted(set(int(a, 16) for a in re.findall(r"\bsub_([0-9a-f]+)\(app", text)) - set(natives) - tails)

    with open(out / "game_functions.cpp", "w") as f:
        f.write('#include "nfs3hp.h"\n#include <lib/thread.h>\n\nnamespace nfs3hp\n{\n\n%s}\n' % text)
    with open(out / "nfs3hp.h", "w") as h:
        h.write("#ifndef NFS3HP_H_\n#define NFS3HP_H_\n#include <x86.h>\n#include <lib/winapp.h>\n\n"
                "namespace nfs3hp\n{\n\n")
        for address, name in sorted(natives.items()):
            h.write(game.native_declaration(address, name))
        h.write("/* The race music's hooks (music_stream). */\n"
                "void musicIndexOpened(win32::WinApplication* app, x86::reg32 path);\n"
                "void musicStreamFile(win32::WinApplication* app, x86::reg32 path);\n"
                "/* The Screen Size list's (widescreen). */\n"
                "bool widescreenMode(x86::reg32 width, x86::reg32 height);\n"
                "x86::reg32 dynamicSavedMode(x86::reg32 found, x86::reg32 width);\n"
                "/* The races' x87 word (race precision). */\n"
                "x86::reg16 raceControl(x86::reg16 word);\n")
        h.write("\nclass Application : public win32::WinApplication\n{\npublic:\n"
                "    /* The game's code for the natives (game_functions.cpp). */\n")
        for address in sorted(natives):
            h.write("    static void sub_%x(WinApplication* app, x86::CPU& cpu);\n" % address)
        h.write("    /* The graphics natives' tails, as the game has them. */\n")
        for address in sorted(tails):
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
    # The decompiled functions' (nfs3hp.decompiled_list()): every register
    # compared, what their callers count on not being known -- the x87's stack
    # too for one that uses it ("fpu"); the pages their globals are on
    # compared; those globals made up for every case.  What they call of the
    # game's that has no stand-in of its own gets one that keeps to Watcom's
    # convention, its four argument registers logged and eax its result --
    # and the words its ret takes off the stack, logged too.
    decompiled = nfs3hp.decompiled_list()
    with open(out / "decompiled_promises.inc", "w") as f:
        for entry in decompiled:
            fpu = ", true, kNoHeap, true" if entry.get("fpu") else ""
            f.write('{"%s", true, true, 0%s},\n' % (nfs3hp.decompiled_name(entry), fpu))
    pages = sorted({int(g, 16) & ~0xfff for entry in decompiled for g in entry["globals"]})
    with open(out / "decompiled_windows.inc", "w") as f:
        for page in pages:
            f.write("{0x%x, 0x%x},\n" % (page, page + 0x2000))
    with open(out / "decompiled_world.inc", "w") as f:
        for entry in decompiled:
            f.write('{"%s", {%s}, {%s}},\n' % (nfs3hp.decompiled_name(entry), ", ".join(entry["globals"]),
                                                ", ".join(entry.get("values", []))))
    words = {}
    for subroutine in game.subroutines:
        entry = subroutine.get_entry_point()
        if entry in called:
            function = io.StringIO()
            game.write_function(function, subroutine, "sub_%x" % entry, {}, nfs3hp.THREAD_SEGMENTS,
                                nfs3hp.SKIP_INSTRUCTIONS)
            rets = [int(n) for n in re.findall(r"cpu\.esp \+= 4\+(\d+) /\*", function.getvalue())]
            words[entry] = max(rets, default=0) // 4
    from entry_regs import Reader
    reader = Reader()
    with open(out / "decompiled_standins.inc", "w") as f:
        for address in called:
            # A ret that takes words off the stack: stdcall's, which the
            # stand-in takes off too.  Its register arguments: those its code
            # reads on entry (entry_regs.py).
            n = words.get(address, 0)
            f.write('{0x%x, "sub_%x", %s, %d, %d, kEax, -1, 0, kNothing},\n'
                    % (address, address, "kStdcall" if n else "kWatcom", reader.register_arguments(address), n))
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
        # The jump tables the tested code reads from among the game's code
        # (jmp [reg*4 + table]): their words, while they lead into the code.
        code = [(address, bytes(data[:length])) for data, address, length, name, ro, is_code in game.sections
                if data and is_code]
        for table in sorted(set(int(a) for a in re.findall(
                r"getMemory<x86::reg32>\((\d+) \+ cpu\.\w+ \* 4\); goto dynamic_jump", text))):
            for start, data in code:
                if start <= table < start + len(data):
                    words = []
                    while table + 4 * len(words) + 4 <= start + len(data) and len(words) < 256:
                        offset = table - start + 4 * len(words)
                        word = int.from_bytes(data[offset:offset + 4], "little")
                        if not start <= word < start + len(data):
                            break
                        words.append(word)
                    if words:
                        names.append((table, 4 * len(words), "Jumps%x" % table))
                        f.write("extern const x86::reg8 kGameJumps%x[] = {\n    %s,\n};\n" % (
                            table, ", ".join("0x%02x" % b for w in words for b in w.to_bytes(4, "little"))))
        f.write("extern const struct GameSegment { x86::reg32 address, length; const x86::reg8* bytes; } "
                "kGameSegments[] = {\n")
        for address, length, name in names:
            f.write("    {0x%x, %d, kGame%s},\n" % (address, length, name))
        f.write("};\nextern const unsigned kGameSegmentCount = %d;\n" % len(names))
    print("nfs3hp: %d functions tested, %d stood in for: %s" % (
        len(tested), len(called), " ".join("%x" % a for a in called)), file=sys.stderr)


if __name__ == "__main__":
    main()
