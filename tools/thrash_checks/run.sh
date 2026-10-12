#!/bin/sh
# Builds thrash_checks and runs it: the natives of src/nfs3hp/native_thrash.cpp
# and native_watcom_heap.cpp against voodoo2a's generated code, made afresh
# from nfs3hp/voodoo2a.dll by the port's own generator (generate.py, which
# needs capstone; PYTHON=... for one that has it) -- once with the default FPU
# (doubles) and once with WITH_PEDANTIC_FPU (80 bits).  CASES=n for more or
# fewer cases an export, JOBS=n compilers at once.
#
# Everything but the two natives is built once into build/<fpu>/base/, and the
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
    sources="$(ls "$build"/generated/voodoo2a.*.cpp) $root/src/lib/cpu.cpp $here/thrash_checks.cpp"
    if [ "$fpu" = 80-bit ]; then
        flags="$flags -DWITH_PEDANTIC_FPU"
        sources="$sources $root/src/lib/x87soft.cpp"
    fi
    includes="-I$build/generated -I$root/sdl3/include -I$root/include -I$root/src/nfs3hp"
    printf '%s\n' $sources | xargs -P "${JOBS:-4}" -I{} \
        sh -c '${CXX:-c++} $1 $2 -c "$3" -o "$4/$(basename "$3" .cpp).o"' _ "$flags" "$includes" {} "$out/base"
    for native in native_thrash native_watcom_heap; do
        ${CXX:-c++} $flags $includes -c "$root/src/nfs3hp/$native.cpp" -o "$out/$native.o"
    done
    ${CXX:-c++} "$out"/base/*.o "$out/native_thrash.o" "$out/native_watcom_heap.o" -o "$out/thrash_checks"
    echo "== $fpu FPU"
    "$out/thrash_checks" ${CASES:-20000}
done
