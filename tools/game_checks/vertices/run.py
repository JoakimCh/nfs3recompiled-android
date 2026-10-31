"""native_vertices.cpp's natives held against the game's code on
Windows or a POSIX host, in every x87 mode the game can be in (vcheck.cpp):

    python tools/game_checks/vertices/run.py [cases per mode] [name ...]

The game's code made afresh (gen_vertices.py, needs capstone), built with the
NDK's clang-cl on Windows or CXX (default c++) on a POSIX host, into build/
here, and run. VCHECK_DUMP=1 lists every differing word of a
case, VCHECK_SHOW=<control word>:<case> the records a case starts from,
VCHECK_TRACE=1 each run as it starts. VCHECK_BENCH=<iterations> measures the
four matrix/vector kernels instead of checking them; synthetic host timings
are not device FPS. Do not use fast-math or floating-point contraction."""
import concurrent.futures
import os
import shlex
import subprocess
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[2]
sys.path.insert(0, str(ROOT / "tools/game_checks/windows"))
if os.name == "nt":
    import winbuild  # noqa: E402

BUILD = HERE / "build"
GEN = BUILD / "generated"
OBJ = BUILD / "obj"


def compile_one(source):
    if os.name != "nt":
        inc = ["-I" + str(p) for p in [GEN, HERE, ROOT / "sdl3/include", ROOT / "include", ROOT / "src/nfs3hp"]]
        cmd = shlex.split(os.environ.get("CXX", "c++")) + [
            "-std=c++17", "-O2", "-fno-strict-aliasing", "-ffp-contract=off",
            "-frounding-math", "-DWITH_MMX", "-w", "-c", str(source),
            "-o", str(OBJ / (source.stem + ".o"))] + inc
        r = subprocess.run(cmd, capture_output=True, text=True)
        return None if r.returncode == 0 else source.name + "\n" + r.stdout[-6000:] + r.stderr[-6000:]
    inc = ["/I" + str(p) for p in [GEN, HERE, ROOT / "sdl3/include", ROOT / "include", ROOT / "src/nfs3hp"]]
    cmd = [str(winbuild.NDK / "clang-cl.exe"), "/nologo", "/c", str(source), "/Fo" + str(OBJ / (source.stem + ".obj"))] \
        + winbuild.FLAGS + inc
    r = subprocess.run(cmd, capture_output=True, text=True, env=winbuild.env())
    return None if r.returncode == 0 else source.name + "\n" + r.stdout[-6000:] + r.stderr[-6000:]


def main():
    r = subprocess.run([sys.executable, str(HERE / "gen_vertices.py"), str(GEN)], stdin=subprocess.DEVNULL)
    if r.returncode:
        sys.exit("gen_vertices.py failed")
    OBJ.mkdir(parents=True, exist_ok=True)
    sources = [GEN / "game_functions.cpp", GEN / "game_data.cpp", ROOT / "src/lib/cpu.cpp",
               ROOT / "src/nfs3hp/native_vertices.cpp", HERE / "vcheck.cpp"]
    with concurrent.futures.ThreadPoolExecutor(8) as pool:
        errors = [e for e in pool.map(compile_one, sources) if e]
    if errors:
        sys.exit("\n".join(errors))
    if os.name == "nt":
        exe = BUILD / "vcheck.exe"
        err = winbuild.link([OBJ / (s.stem + ".obj") for s in sources], exe)
        if err:
            sys.exit(err)
    else:
        exe = BUILD / "vcheck"
        subprocess.run(shlex.split(os.environ.get("CXX", "c++")) +
                       [str(OBJ / (s.stem + ".o")) for s in sources] + ["-o", str(exe)], check=True)
    sys.exit(subprocess.run([str(exe)] + sys.argv[1:]).returncode)


if __name__ == "__main__":
    main()
