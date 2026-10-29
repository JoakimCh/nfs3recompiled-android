"""tools/frontend_checks/run.sh on Windows: the main menu's code made afresh
(generate.py), the screens' generated functions taken out of the disassembly
(extract.py), built as tools/game_checks/windows/winbuild.py builds the game's
checks (POSIX's mmap from its shim), and run.  The functions and the sources
are run.sh's, read from it.

    python tools/frontend_checks/windows/run.py [rounds]

generate.py and extract.py run again only when what they read changed, only
the sources that changed are compiled again, and the functions are checked in
shares side by side, as many as the machine has threads (GAME_CHECKS_JOBS).

Only the double-precision FPU build: the phone's."""
import hashlib, re, subprocess, sys
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
    # generate.py and extract.py again only when what they read changed: the
    # generator and nfs3.exe, the disassembly the screens are taken from, the
    # functions asked for.
    key = hashlib.sha1(" ".join(functions).encode())
    for f in ([CHECKS / "generate.py", CHECKS / "extract.py", ROOT / "disassemble_nfs3hp.py", ROOT / "nfs3hp/nfs3.exe"]
              + sorted((ROOT / "disasm").rglob("*.py")) + sorted((ROOT / "tools").glob("apply_*.py"))
              + sorted((ROOT / "src/nfs3hp").glob("*.inc")) + [ROOT / "src/nfs3hp/decompiled.json"]
              + sorted(disassembly.iterdir())):
        key.update(f.name.encode())
        key.update(f.read_bytes())
    stamp = BUILD / "generate.key"
    if stamp.exists() and stamp.read_text() == key.hexdigest():
        print("generate.py, extract.py: nothing they read changed, their output kept", flush=True)
    else:
        for step in ([sys.executable, str(CHECKS / "generate.py"), str(BUILD / "natives.cpp")],
                     [sys.executable, str(CHECKS / "extract.py"), str(disassembly), str(BUILD / "generated.cpp"),
                      str(BUILD / "mocks.inc"), "--native", str(BUILD / "natives.cpp")] + functions):
            if subprocess.run(step, cwd=ROOT, stdin=subprocess.DEVNULL).returncode:
                sys.exit("%s failed" % Path(step[1]).name)
        stamp.write_text(key.hexdigest())
    includes = ["/I" + str(p) for p in [ROOT / "tools/game_checks/windows/shim", BUILD, CHECKS,
                                        ROOT / "tools/loading_checks/stub", ROOT / "third_party", ROOT / "include",
                                        disassembly, ROOT / "src/nfs3hp"]]
    winbuild.includes = lambda generated: includes
    objects = BUILD / "obj"
    errors = winbuild.compile_all(sources, objects, BUILD)
    if errors:
        sys.exit("\n".join(errors))
    exe = BUILD / "frontend_checks.exe"
    err = winbuild.link(sorted(objects.glob("*.obj")), exe)
    if err:
        sys.exit(err)
    # The functions in shares, every JOBS-th, side by side; each share's
    # differences printed, then the total.
    jobs = winbuild.JOBS
    runs = [subprocess.Popen([str(exe), str(ROOT / "nfs3hp/nfs3.exe"), rounds, "%d/%d" % (k, jobs)],
                             stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True) for k in range(jobs)]
    failed, functions = 0, 0
    for r in runs:
        out = r.communicate()[0]
        failed += r.returncode != 0
        for line in out.splitlines():
            m = re.match(r"(\d+) functions, \d+ cases each: ", line)
            if m:
                functions += int(m.group(1))
            elif " differ" in line or "FAILED" in line or "crash" in line.lower():
                print(line)
        if r.returncode not in (0, 1):
            print("a share stopped with exit %d" % r.returncode)
    print("%d functions, %s cases each: %s" % (functions, rounds, "FAILED" if failed else "all match"))
    sys.exit(1 if failed else 0)


if __name__ == "__main__":
    main()
