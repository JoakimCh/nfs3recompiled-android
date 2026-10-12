#!/bin/sh
# Builds frontend_checks and runs it: the decompiled screens of
# src/nfs3hp/native_frontend_options.cpp, _cars.cpp and _tracks.cpp against the
# generated functions they stand in for, taken out of this tree's
# src/nfs3hp/disassembly (or $1's) without their hooks.  $2 rounds of every
# function, 1000 by default.
set -e
here=$(cd "$(dirname "$0")" && pwd)
root=$(cd "$here/../.." && pwd)
build=${BUILD:-"$here/build"}
mkdir -p "$build"
disassembly="${1:-$root}/src/nfs3hp/disassembly"
python3 "$here/extract.py" "$disassembly" "$build/generated.cpp" "$build/mocks.inc" \
    sub_442aa0 sub_4374b0 sub_437590 sub_437250 sub_437300 sub_437390 sub_437420 \
    sub_437350 sub_4373e0 sub_437470 sub_437600 sub_4377c0 sub_4377d0 \
    sub_437e00 sub_438070 sub_438260 sub_437a90 sub_437990 sub_4379b0 sub_4379d0 sub_437a20 sub_437a70 \
    sub_43d4d0 sub_43d5f0 sub_43d3f0 sub_43d460 sub_43d410 \
    sub_43d9a0 sub_4432c0 sub_443430 sub_442db0 sub_443260 sub_443290 sub_443070 \
    sub_442e60 sub_442dd0 sub_442ef0 sub_442ff0 \
    sub_447dd0 sub_4481c0 sub_447b40 sub_447b60 sub_447c40 sub_447c70 sub_447ca0 sub_447cd0 sub_447d50 \
    sub_448440 sub_4484e0 sub_448430 sub_448610 sub_448770 sub_4485a0 sub_448570 \
    sub_4104b0 sub_4267a0 sub_4267f0 sub_426870 sub_426b00 sub_426d60 sub_426ef0 sub_426e20 \
    sub_426f80 sub_426ee0 sub_427040 sub_426c20 sub_426c40 sub_426c60 sub_426ce0 sub_427050 \
    sub_4270c0 sub_4272a0 sub_4272e0 sub_427190 sub_4272f0 sub_427370 sub_4273e0 sub_427470 \
    sub_427500 sub_427590 sub_427620 sub_4276b0 sub_427740 sub_4277d0 sub_4279b0 sub_427ac0 \
    sub_427c20 sub_427d00 sub_427d80 sub_427e10 sub_427ea0 sub_427f40 sub_427fb0 sub_428020 \
    sub_428060 sub_4281e0 sub_428360 sub_4283b0 sub_4dcaf0 sub_4dcb60 sub_4487e0 sub_4487d0 \
    sub_4489e0 sub_456200 sub_4568d0 sub_456890 sub_456990 sub_4c94e0 sub_4c9590 \
    sub_4dfd56
${CXX:-c++} -std=c++17 -O2 -fno-strict-aliasing -DWITH_MMX -w \
    -I"$here" -I"$root/tools/loading_checks/stub" -I"$root/third_party" -I"$root/include" \
    -I"$root/src/nfs3hp/disassembly" -I"$root/src/nfs3hp" \
    "$build/generated.cpp" "$root/src/nfs3hp/native_frontend.cpp" "$root/src/nfs3hp/native_frontend_options.cpp" \
    "$root/src/nfs3hp/native_frontend_cars.cpp" "$root/src/nfs3hp/native_frontend_tracks.cpp" \
    "$here/frontend_checks.cpp" -o "$build/frontend_checks"
"$build/frontend_checks" "$root/nfs3hp/nfs3.exe" "${2:-1000}"
