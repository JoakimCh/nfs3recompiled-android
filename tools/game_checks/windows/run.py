"""tools/game_checks/run.sh on Windows: the game's code for the natives made
afresh (generate.py), built with winbuild.py, and every native held against
it -- or the one named.

    python tools/game_checks/windows/run.py [cases] [name ...]

    python tools/game_checks/windows/run.py 1000 decompiled::resetSunLighting

A name ending in :: (graphics::) checks every function of that namespace.

generate.py runs again only when something it reads changed (generate_key),
only the sources that changed since are compiled again, the generated code in
PARTS files side by side, and the functions are checked as many at a time as
the machine has threads (GAME_CHECKS_JOBS to set it), each in a process of
its own, reported in the order asked.

Only the double-precision FPU build (run.sh also builds an 80-bit one)."""
import concurrent.futures, hashlib, re, shutil, subprocess, sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import winbuild  # noqa: E402

BUILD = HERE / "build"
ROOT = winbuild.ROOT
# game_functions.cpp, one file of tens of megabytes, compiled as this many
# parts side by side.
PARTS = 16


def generate_key():
    """What generate.py's output depends on: the files it reads whole, the
    rows game_checks' tables stand in for, and of each of the port's sources
    only what it looks for there -- the addresses a file names, the functions
    it defines, its namespaces and headers (named_addresses).  The same key,
    the same output."""
    h = hashlib.sha1()
    whole = [ROOT / "tools/game_checks/generate.py", ROOT / "tools/game_checks/entry_regs.py",
             ROOT / "disassemble_nfs3hp.py", ROOT / "nfs3hp/nfs3.exe", ROOT / "src/nfs3hp/decompiled.json"]
    whole += sorted((ROOT / "disasm").rglob("*.py")) + sorted((ROOT / "tools").glob("apply_*.py"))
    whole += sorted((ROOT / "src/nfs3hp").glob("*.inc"))
    for f in whole:
        h.update(f.name.encode())
        h.update(f.read_bytes())
    rows = re.compile(r'^\s*\{(0x[0-9a-f]+), "[^"]*", k(?:Watcom|Cdecl|Stdcall)', re.M)
    for f in [ROOT / "tools/game_checks/game_checks.cpp"] + sorted((ROOT / "tools/game_checks").glob("*.inc")):
        h.update(" ".join(sorted(rows.findall(f.read_text(encoding="utf-8")))).encode())
    for f in sorted((ROOT / "src/nfs3hp").glob("*.cpp")) + sorted((ROOT / "src/nfs3hp").glob("*.h")):
        code = re.sub(r"/\*.*?\*/|//[^\n]*", "", f.read_text(encoding="utf-8", errors="replace"), flags=re.S)
        h.update(f.name.encode())
        for found in (re.findall(r"\b0x[0-9a-f]{6}\b", code), re.findall(r"\bvoid (\w+)\(", code),
                      re.findall(r"\bnamespace (\w+)", code), re.findall(r'#include "([\w.]+\.h)"', code)):
            h.update((" ".join(sorted(set(found))) + "|").encode())
    return h.hexdigest()


def put(path, text):
    """`text` to `path` only when it differs: an unchanged file keeps its
    time, and what is built from it is not built again."""
    if not path.exists() or path.read_text(encoding="utf-8", errors="replace") != text:
        path.write_text(text, encoding="utf-8")


def split_functions(generated):
    """game_functions.cpp as PARTS files, cut between functions."""
    text = (generated / "game_functions.cpp").read_text(encoding="utf-8", errors="replace")
    head = '#include "nfs3hp.h"\n#include <lib/thread.h>\n\nnamespace nfs3hp\n{\n\n'
    assert text.startswith(head) and text.endswith("}\n"), "game_functions.cpp is not as split_functions knows it"
    body = text[len(head):-2]
    size = len(body) // PARTS + 1
    bounds, last = [0], 0
    for m in re.finditer(r"\nvoid Application::sub_", body):
        if m.start() + 1 - last >= size and len(bounds) < PARTS:
            last = m.start() + 1
            bounds.append(last)
    bounds.append(len(body))
    parts = []
    for i in range(PARTS):
        piece = body[bounds[i]:bounds[i + 1]] if i + 1 < len(bounds) else ""
        path = generated / ("game_functions_%02d.cpp" % i)
        put(path, head + piece + "}\n")
        parts.append(path)
    return parts


def build(generated):
    """generate.py's output, made again only when its key changed (into a
    fresh directory, copied over where a file differs), and the checker built
    from it; the checker's path."""
    key = generate_key()
    stamp = generated / "generate.key"
    if not stamp.exists() or stamp.read_text() != key:
        fresh = BUILD / "generated.new"
        shutil.rmtree(fresh, ignore_errors=True)
        r = subprocess.run([sys.executable, str(ROOT / "tools/game_checks/generate.py"), str(fresh)],
                           cwd=ROOT, stdin=subprocess.DEVNULL)
        if r.returncode:
            sys.exit("generate.py failed")
        generated.mkdir(parents=True, exist_ok=True)
        for f in fresh.iterdir():
            put(generated / f.name, f.read_text(encoding="utf-8", errors="replace"))
        shutil.rmtree(fresh, ignore_errors=True)
        stamp.write_text(key)
    else:
        print("generate.py: nothing it reads changed, its output kept", flush=True)
    sources = split_functions(generated) + [s for s in winbuild.base_sources(generated)
                                            if s.name != "game_functions.cpp"]
    objects = BUILD / ("obj_debug" if winbuild.DEBUG else "obj")
    errors = winbuild.compile_all(sources, objects, generated)
    if errors:
        sys.exit("\n".join(errors))
    exe = BUILD / ("game_checks_debug.exe" if winbuild.DEBUG else "game_checks.exe")
    err = winbuild.link(sorted(objects.glob("*.obj")), exe)
    if err:
        sys.exit(err)
    return exe


def main():
    cases = sys.argv[1] if len(sys.argv) > 1 else "20000"
    names = sys.argv[2:]
    generated = BUILD / "generated"
    exe = build(generated)
    if not names:
        sys.exit(subprocess.run([str(exe), cases]).returncode)
    tested = (generated / "game_tested.inc").read_text()
    wanted = []
    for name in names:
        wanted += sorted(set(n for n in re.findall(r'"([\w:]+)"', tested) if n.startswith(name))) \
            if name.endswith("::") else [name]

    def check(name):
        return subprocess.run([str(exe), cases, "all", name], capture_output=True, text=True)

    failed = 0
    with concurrent.futures.ThreadPoolExecutor(winbuild.JOBS) as pool:
        for name, r in zip(wanted, pool.map(check, wanted)):
            alike = r.returncode == 0 and "all alike" in r.stdout
            failed += not alike
            print("%-50s %s" % (name, "alike" if alike else "DIFFERS (exit %d)" % r.returncode), flush=True)
            if not alike:
                print("\n".join(l for l in r.stdout.splitlines() if l.strip())[-1500:])
    print("%d of %d alike" % (len(wanted) - failed, len(wanted)), flush=True)
    sys.exit(1 if failed else 0)


if __name__ == "__main__":
    main()
