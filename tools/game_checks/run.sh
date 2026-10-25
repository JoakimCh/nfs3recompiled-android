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
                  native_controls_pipeline native_controls_queue native_ea_threads native_ea_memory native_ea_files native_ea_support native_load_track native_load_cardb native_load_carmodels native_load_saves native_ea_net native_ea_formats native_frontend_glue native_frontend_draw native_racestart native_raceload native_trackdata native_physics native_handling native_drivetrain native_decompiled native_graphics port_snd_voices port_snd_play native_snd_stream native_snd_cdstream native_snd_path native_snd_strm native_snd_driver native_snd_fx native_snd_mixsetup native_snd_music port_sound_effects native_snd_mixfuncs native_snd_scenery native_snd_racebanks native_snd_announcer native_snd_ambient native_snd_player native_snd_tick native_snd_banks native_snd_copradio native_snd_racesetup native_snd_cops native_snd_3d native_snd_pursuit native_snd_speech native_snd_race native_snd_crash native_snd_siren native_snd_dead native_mixer; do
        ${CXX:-c++} $flags $includes -c "$root/src/nfs3hp/$native.cpp" -o "$out/$native.o"
    done
    ${CXX:-c++} "$out"/base/*.o "$out/native_game.o" "$out/native_watcom.o" "$out/native_watcom_heap.o" \
        "$out/native_mmx.o" "$out/native_frontend_text.o" "$out/native_frontend_screen.o" \
        "$out/native_controls_input.o" "$out/native_controls_devices.o" "$out/native_controls_race.o" \
        "$out/native_controls_pipeline.o" "$out/native_controls_queue.o" "$out/native_ea_threads.o" "$out/native_ea_memory.o" "$out/native_ea_files.o" "$out/native_ea_support.o" "$out/native_load_track.o" "$out/native_load_cardb.o" "$out/native_load_carmodels.o" "$out/native_load_saves.o" "$out/native_ea_net.o" "$out/native_ea_formats.o" "$out/native_frontend_glue.o" "$out/native_frontend_draw.o" "$out/native_racestart.o" "$out/native_raceload.o" "$out/native_trackdata.o" "$out/native_physics.o" "$out/native_handling.o" "$out/native_drivetrain.o" "$out/native_decompiled.o" \
        "$out/native_graphics.o" "$out/port_snd_voices.o" "$out/port_snd_play.o" "$out/native_snd_stream.o" "$out/native_snd_cdstream.o" "$out/native_snd_path.o" "$out/native_snd_strm.o" "$out/native_snd_driver.o" "$out/native_snd_fx.o" "$out/native_snd_mixsetup.o" "$out/native_snd_music.o" "$out/port_sound_effects.o" "$out/native_snd_mixfuncs.o" "$out/native_snd_scenery.o" "$out/native_snd_racebanks.o" "$out/native_snd_announcer.o" "$out/native_snd_ambient.o" "$out/native_snd_player.o" "$out/native_snd_tick.o" "$out/native_snd_banks.o" "$out/native_snd_copradio.o" "$out/native_snd_racesetup.o" "$out/native_snd_cops.o" "$out/native_snd_3d.o" "$out/native_snd_pursuit.o" "$out/native_snd_speech.o" "$out/native_snd_race.o" "$out/native_snd_crash.o" "$out/native_snd_siren.o" "$out/native_snd_dead.o" "$out/native_mixer.o" \
        -o "$out/game_checks"
    echo "== $fpu FPU"
    "$out/game_checks" ${CASES:-20000}
done
