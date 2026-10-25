"""tools/game_checks built on Windows: the same sources and
flags as run.sh, compiled by the NDK's clang-cl against Visual Studio Build
Tools' MSVC and the Windows SDK, linked by MSVC's link.exe.  POSIX's mmap,
the one thing of Linux game_checks.cpp uses, comes from shim/sys/mman.h."""
import concurrent.futures, os, subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
HERE = Path(__file__).resolve().parent
NDK = Path(os.environ.get("NDK_LLVM", r"D:\Android_SDK\ndk\28.2.13676358\toolchains\llvm\prebuilt\windows-x86_64\bin"))
MSVC = Path(os.environ.get("MSVC_ROOT",
            r"C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Tools\MSVC\14.44.35207"))
SDK = Path(r"C:\Program Files (x86)\Windows Kits\10")
SDKV = os.environ.get("WINSDK_VERSION", "10.0.26100.0")

# run.sh's natives.
NATIVES = ["native_game", "native_watcom", "native_watcom_heap", "native_mmx", "native_frontend_text",
           "native_frontend_screen", "native_controls_input", "native_controls_devices", "native_controls_race",
           "native_controls_pipeline", "native_controls_queue", "native_ea_threads", "native_ea_memory", "native_ea_files", "native_ea_support", "native_load_track", "native_load_cardb", "native_load_carmodels", "native_load_saves", "native_ea_net", "native_ea_formats", "native_frontend_glue", "native_frontend_draw", "native_racestart", "native_raceload", "native_trackdata", "native_physics", "native_handling", "native_drivetrain", "native_decompiled", "native_graphics", "port_snd_voices", "port_snd_play", "native_snd_stream", "native_snd_cdstream", "native_snd_path", "native_snd_strm", "native_snd_driver", "native_snd_fx", "native_snd_mixsetup", "native_snd_music", "port_sound_effects", "native_snd_mixfuncs", "native_snd_scenery", "native_snd_racebanks", "native_snd_announcer", "native_snd_ambient", "native_snd_player", "native_snd_tick", "native_snd_banks", "native_snd_copradio", "native_snd_racesetup", "native_snd_cops", "native_snd_3d", "native_snd_pursuit", "native_snd_speech", "native_snd_race", "native_snd_crash", "native_snd_siren", "native_snd_dead", "native_mixer"]

FLAGS = ["/std:c++17", "/O1", "/EHsc", "-fno-strict-aliasing", "/DWITH_MMX", "/w", "/MT", "/bigobj",
         "/D_CRT_SECURE_NO_WARNINGS", "/DNOMINMAX"]
# GAME_CHECKS_DEBUG=1: debug information in the objects and a .pdb by the exe,
# for lldb (the NDK's) to say where a case crashed.
DEBUG = os.environ.get("GAME_CHECKS_DEBUG") == "1"
if DEBUG:
    FLAGS = FLAGS + ["/Z7"]


def env():
    e = dict(os.environ)
    e["INCLUDE"] = ";".join(str(p) for p in [MSVC / "include", SDK / "Include" / SDKV / "ucrt",
                                              SDK / "Include" / SDKV / "um", SDK / "Include" / SDKV / "shared"])
    e["LIB"] = ";".join(str(p) for p in [MSVC / "lib/x64", SDK / "Lib" / SDKV / "ucrt/x64",
                                          SDK / "Lib" / SDKV / "um/x64"])
    return e


def includes(generated):
    return ["/I" + str(p) for p in [HERE / "shim", generated, ROOT / "tools/game_checks", ROOT / "sdl3/include",
                                    ROOT / "include", ROOT / "src/nfs3hp"]]


def compile_one(source, obj, generated):
    """None, or the compiler's complaint."""
    cmd = [str(NDK / "clang-cl.exe"), "/nologo", "/c", str(source), "/Fo" + str(obj)] + FLAGS + includes(generated)
    r = subprocess.run(cmd, capture_output=True, text=True, env=env())
    return "%s\n%s%s" % (source.name, r.stdout, r.stderr) if r.returncode else None


def compile_all(sources, out, generated):
    """Each source to out/<its name>.obj; the complaints, if any."""
    out.mkdir(parents=True, exist_ok=True)
    with concurrent.futures.ThreadPoolExecutor(8) as pool:
        return [e for e in pool.map(lambda s: compile_one(s, out / (s.stem + ".obj"), generated), sources) if e]


def link(objects, exe):
    r = subprocess.run([str(MSVC / "bin/Hostx64/x64/link.exe"), "/nologo", "/OUT:" + str(exe), "/STACK:16777216"] + (["/DEBUG"] if DEBUG else [])
                       + [str(o) for o in objects], capture_output=True, text=True, env=env())
    return None if r.returncode == 0 else (r.stdout + r.stderr)[-3000:]


def base_sources(generated, natives=NATIVES):
    return [generated / "game_functions.cpp", generated / "game_data.cpp", ROOT / "src/lib/cpu.cpp",
            ROOT / "tools/game_checks/game_checks.cpp", ROOT / "tools/game_checks/controls_host.cpp"] + \
           [ROOT / "src/nfs3hp" / (n + ".cpp") for n in natives]
