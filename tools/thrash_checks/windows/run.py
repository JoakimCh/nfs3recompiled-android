"""tools/thrash_checks on Windows: the new THRASH driver (src/nfs3hp/port_thrash.cpp)
against the old one over the port's Glide (reference/), both under
ThrashRenderer, built as tools/game_checks/windows/winbuild.py builds the game's
checks, and run.

    python tools/thrash_checks/windows/run.py [sessions] [--debug]

--debug builds without optimisation; THRASH_CHECKS_TRACE=1 in the environment
has the checks print every call, and a crash prints its stack either way.
Only the double-precision FPU build: the phone's."""
import subprocess, sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[2]
sys.path.insert(0, str(ROOT / "tools/game_checks/windows"))
import winbuild  # noqa: E402

BUILD = HERE / "build"
SOURCES = [
    ROOT / "tools/thrash_checks/thrash_checks.cpp",
    ROOT / "tools/thrash_checks/reference/driver.cpp",
    ROOT / "tools/thrash_checks/reference/glide2x.cpp",
    ROOT / "src/nfs3hp/port_thrash.cpp",
    ROOT / "src/nfs3hp/native_watcom_heap.cpp",
    ROOT / "src/lib/thrashrenderer.cpp",
    ROOT / "src/lib/glfuncs.cpp",
    ROOT / "src/lib/cpu.cpp",
]


def main():
    sessions = sys.argv[1] if len(sys.argv) > 1 else "2000"
    winbuild.FLAGS += ["/Zi"]
    if "--debug" in sys.argv:
        winbuild.FLAGS[winbuild.FLAGS.index("/O1")] = "/Od"
        sys.argv.remove("--debug")
    objects = BUILD / "obj"
    for obj in objects.glob("*.obj"):
        obj.unlink()
    errors = winbuild.compile_all(SOURCES, objects, HERE)
    if errors:
        sys.exit("\n".join(errors))
    exe = BUILD / "thrash_checks.exe"
    err = winbuild.link(sorted(objects.glob("*.obj")) + ["opengl32.lib", "dbghelp.lib", "/DEBUG"], exe)
    if err:
        sys.exit(err)
    sys.exit(subprocess.run([str(exe), sessions, str(ROOT / "nfs3hp/voodoo2a.dll")]).returncode)


if __name__ == "__main__":
    main()
