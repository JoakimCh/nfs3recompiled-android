#!/bin/sh
# Builds game_checks and runs it: the natives of src/nfs3hp/native_game.cpp,
# native_watcom.cpp, native_watcom_heap.cpp, native_mmx.cpp,
# native_frontend_text.cpp, native_frontend_screen.cpp and the controls'
# native_controls_*.cpp against the
# game's code for them, made afresh from nfs3hp/nfs3.exe by the port's own
# generator (generate.py, which needs capstone; PYTHON=... for one that has
# it, and reads the whole game, a minute or so) -- once with the default FPU
# (doubles) and once with WITH_PEDANTIC_FPU (80 bits).  CASES=n for more or
# fewer cases a function, JOBS=n compilers at once.  What the natives ask of
# DirectInput controls_host.cpp answers as the game's code asked it, through
# the objects' tables.
#
# Everything but the natives is built once into build/<fpu>/base/, and the
# natives beside it, which mutations.py links its mutants with.
set -e
here=$(cd "$(dirname "$0")" && pwd)
root=$(cd "$here/../.." && pwd)
build=${BUILD:-"$here/build"}
mkdir -p "$build"
${PYTHON:-python3} "$here/generate.py" "$build/generated" > "$build/generate.log" 2>&1
for fpu in double 80-bit; do
    out="$build/$fpu"
    mkdir -p "$out/base"
    find "$out" -name '*.o' -delete
    flags="-std=c++17 -O1 -fno-strict-aliasing -DWITH_MMX -w"
    sources="$build/generated/game_functions.cpp $build/generated/game_data.cpp $root/src/lib/cpu.cpp $here/game_checks.cpp $here/controls_host.cpp"
    if [ "$fpu" = 80-bit ]; then
        flags="$flags -DWITH_PEDANTIC_FPU"
        sources="$sources $root/src/lib/x87soft.cpp"
    fi
    includes="-I$build/generated -I$root/sdl3/include -I$root/include -I$root/src/nfs3hp"
    printf '%s\n' $sources | xargs -P "${JOBS:-4}" -I{} \
        sh -c '${CXX:-c++} $1 $2 -c "$3" -o "$4/$(basename "$3" .cpp).o"' _ "$flags" "$includes" {} "$out/base"
    for native in native_game native_watcom native_watcom_heap native_mmx native_frontend_text \
                  native_frontend_screen native_controls_input native_controls_devices native_controls_race \
                  native_controls_pipeline; do
        ${CXX:-c++} $flags $includes -c "$root/src/nfs3hp/$native.cpp" -o "$out/$native.o"
    done
    ${CXX:-c++} "$out"/base/*.o "$out/native_game.o" "$out/native_watcom.o" "$out/native_watcom_heap.o" \
        "$out/native_mmx.o" "$out/native_frontend_text.o" "$out/native_frontend_screen.o" \
        "$out/native_controls_input.o" "$out/native_controls_devices.o" "$out/native_controls_race.o" \
        "$out/native_controls_pipeline.o" \
        -o "$out/game_checks"
    echo "== $fpu FPU"
    "$out/game_checks" ${CASES:-20000}
done
