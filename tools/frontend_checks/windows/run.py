"""tools/frontend_checks/run.sh on Windows: the main menu's code made afresh
(generate.py), the screens' generated functions taken out of the disassembly
(extract.py), built as tools/game_checks/windows/winbuild.py builds the game's
checks (POSIX's mmap from its shim), and run.  The functions and the sources
are run.sh's, read from it.

    python tools/frontend_checks/windows/run.py [rounds]

Only the double-precision FPU build: the phone's."""
import re, subprocess, sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
CHECKS = HERE.parent
ROOT = HERE.parents[2]
sys.path.insert(0, str(ROOT / "tools/game_checks/windows"))
import winbuild  # noqa: E402

BUILD = CHECKS / "build"


def from_run_sh():
    """run.sh's functions for extract.py and its sources, as it names them."""
    text = (CHECKS / "run.sh").read_text(encoding="utf-8").replace("\\\n", " ")
    extract = next(line for line in text.splitlines() if "extract.py" in line)
    functions = re.findall(r"\bsub_[0-9a-f]+\b", extract)
    compile_line = next(line for line in text.splitlines() if "${CXX:-c++}" in line)
    sources = [s.replace("$root", str(ROOT)).replace("$here", str(CHECKS)).replace("$build", str(BUILD))
               for s in re.findall(r'"(\$(?:root|here|build)/[^"]+\.cpp)"', compile_line)]
    return functions, [Path(s) for s in sources]


def main():
    rounds = sys.argv[1] if len(sys.argv) > 1 else "1000"
    BUILD.mkdir(parents=True, exist_ok=True)
    functions, sources = from_run_sh()
    disassembly = ROOT / "src/nfs3hp/disassembly"
    for step in ([sys.executable, str(CHECKS / "generate.py"), str(BUILD / "natives.cpp")],
                 [sys.executable, str(CHECKS / "extract.py"), str(disassembly), str(BUILD / "generated.cpp"),
                  str(BUILD / "mocks.inc"), "--native", str(BUILD / "natives.cpp")] + functions):
        if subprocess.run(step, cwd=ROOT, stdin=subprocess.DEVNULL).returncode:
            sys.exit("%s failed" % Path(step[1]).name)
    includes = ["/I" + str(p) for p in [ROOT / "tools/game_checks/windows/shim", BUILD, CHECKS,
                                        ROOT / "tools/loading_checks/stub", ROOT / "third_party", ROOT / "include",
                                        disassembly, ROOT / "src/nfs3hp"]]
    winbuild.includes = lambda generated: includes
    objects = BUILD / "obj"
    for obj in objects.glob("*.obj"):
        obj.unlink()
    errors = winbuild.compile_all(sources, objects, BUILD)
    if errors:
        sys.exit("\n".join(errors))
    exe = BUILD / "frontend_checks.exe"
    err = winbuild.link(sorted(objects.glob("*.obj")), exe)
    if err:
        sys.exit(err)
    sys.exit(subprocess.run([str(exe), str(ROOT / "nfs3hp/nfs3.exe"), rounds]).returncode)


if __name__ == "__main__":
    main()
