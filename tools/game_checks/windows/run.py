"""tools/game_checks/run.sh on Windows: the game's code for the natives made
afresh (generate.py), built with winbuild.py, and every native held against
it -- or the one named.

    python tools/game_checks/windows/run.py [cases] [name ...]

    python tools/game_checks/windows/run.py 3000 decompiled::resetSunLighting

A name ending in :: (graphics::) checks every function of that namespace.

Only the double-precision FPU build (run.sh also builds an 80-bit one)."""
import re, subprocess, sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import winbuild  # noqa: E402

BUILD = HERE / "build"


def main():
    cases = sys.argv[1] if len(sys.argv) > 1 else "20000"
    names = sys.argv[2:]
    generated = BUILD / "generated"
    r = subprocess.run([sys.executable, str(winbuild.ROOT / "tools/game_checks/generate.py"), str(generated)],
                       cwd=winbuild.ROOT, stdin=subprocess.DEVNULL)
    if r.returncode:
        sys.exit("generate.py failed")
    objects = BUILD / "obj"
    for obj in objects.glob("*.obj"):
        obj.unlink()
    errors = winbuild.compile_all(winbuild.base_sources(generated), objects, generated)
    if errors:
        sys.exit("\n".join(errors))
    exe = BUILD / "game_checks.exe"
    err = winbuild.link(sorted(objects.glob("*.obj")), exe)
    if err:
        sys.exit(err)
    if not names:
        sys.exit(subprocess.run([str(exe), cases]).returncode)
    tested = (generated / "game_tested.inc").read_text()
    wanted = []
    for name in names:
        wanted += sorted(set(n for n in re.findall(r'"([\w:]+)"', tested) if n.startswith(name))) \
            if name.endswith("::") else [name]
    failed = 0
    for name in wanted:
        r = subprocess.run([str(exe), cases, "all", name], capture_output=True, text=True)
        alike = r.returncode == 0 and "all alike" in r.stdout
        failed += not alike
        print("%-50s %s" % (name, "alike" if alike else "DIFFERS (exit %d)" % r.returncode), flush=True)
        if not alike:
            print("\n".join(l for l in r.stdout.splitlines() if l.strip())[-1500:])
    sys.exit(1 if failed else 0)


if __name__ == "__main__":
    main()
