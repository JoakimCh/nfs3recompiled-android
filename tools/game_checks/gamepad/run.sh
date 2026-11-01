#!/usr/bin/env bash
set -euo pipefail
# Usage: run.sh /absolute/path/to/SDL-source /absolute/path/to/work-dir
# Requires cmake, a host C++17 compiler and the SDL source pinned in tools/android-toolchain.json.
root=$(cd "$(dirname "$0")/../../.." && pwd)
sdl_source=$1
check_work=$2
mkdir -p "$check_work"
cmake -S "$sdl_source" -B "$check_work/sdl-host" -DSDL_SHARED=OFF -DSDL_STATIC=ON -DSDL_TESTS=OFF -DSDL_TEST_LIBRARY=OFF -DSDL_UNIX_CONSOLE_BUILD=ON -DSDL_X11=OFF -DSDL_WAYLAND=OFF -DSDL_ALSA=OFF -DSDL_PULSEAUDIO=OFF -DSDL_PIPEWIRE=OFF -DSDL_LIBUDEV=OFF
cmake --build "$check_work/sdl-host" -j 2
c++ -std=c++17 -O2 -DWITH_MMX -ffunction-sections -fdata-sections -I "$root/include" -I "$sdl_source/include" "$root/src/lib/sdl-backend/gamepad.cpp" "$root/tools/game_checks/gamepad/pad_check.cpp" "$check_work/sdl-host/libSDL3.a" -Wl,--gc-sections -pthread -ldl -lm -o "$check_work/pad-check"
"$check_work/pad-check"
