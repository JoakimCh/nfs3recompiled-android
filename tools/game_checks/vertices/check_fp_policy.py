"""Check the production vertex FP policy with both Android NDK compilers.

    python tools/game_checks/vertices/check_fp_policy.py --ndk PATH

Compile the real vertex translation unit at release optimization. ARMv7 must
use the compatible path without exception flags or unchecked float loops;
ARMv8 must retain strict FP operations and
its exception-based retry. No Android device or APK is needed. Linux host only.
"""
import argparse
from pathlib import Path
import subprocess

ROOT = Path(__file__).resolve().parents[3]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--ndk', type=Path, required=True)
    parser.add_argument('--output-dir', type=Path, default=ROOT / 'out/vertex-fp-policy')
    args = parser.parse_args()
    compilers = args.ndk / 'toolchains/llvm/prebuilt/linux-x86_64/bin'
    args.output_dir.mkdir(parents=True, exist_ok=True)
    for abi, target in [('armeabi-v7a', 'armv7a-linux-androideabi26'),
                        ('arm64-v8a', 'aarch64-linux-android26')]:
        output = args.output_dir / (abi + '.ll')
        command = [str(compilers / (target + '-clang++')), '-std=c++17', '-O2',
                   '-fno-strict-aliasing', '-ffp-contract=off', '-DWITH_MMX',
                   '-Werror=ignored-pragmas', '-Werror=unsupported-floating-point-opt',
                   '-S', '-emit-llvm', str(ROOT / 'src/nfs3hp/native_vertices.cpp'), '-o', str(output)]
        command += ['-I' + str(ROOT / path) for path in
                    ('include', 'sdl3/include', 'src/nfs3hp', 'src/nfs3hp/disassembly')]
        if abi == 'arm64-v8a':
            command.append('-frounding-math')
        else:
            command += ['-mthumb', '-mfpu=neon', '-mfloat-abi=softfp']
        subprocess.run(command, check=True)
        ir = output.read_text()
        retries = '@feclearexcept' in ir or '@fetestexcept' in ir
        strict = 'llvm.experimental.constrained.fmul' in ir and 'fpexcept.strict' in ir
        if abi == 'armeabi-v7a' and (retries or 'NFS_VERTEX_FAST' in ir or 'FloatMath' in ir):
            raise SystemExit('ARMv7 retained unchecked float loops or unsupported FP exception tracking')
        if abi == 'arm64-v8a' and not (retries and strict):
            raise SystemExit('ARMv8 lost its strict FP exception/retry semantics')
        print(abi + ': ' + ('fixed compatible arithmetic' if abi == 'armeabi-v7a'
                           else 'strict host FP operations and exception retry'), flush=True)


if __name__ == '__main__':
    main()
