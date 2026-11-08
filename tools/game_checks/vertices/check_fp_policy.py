"""Check the production vertex FP policy with both Android NDK compilers.

    python tools/game_checks/vertices/check_fp_policy.py --ndk PATH

Compile both precision modes of the real vertex translation unit. DOUBLE must
contain double operations without single rounding or float/retry dispatch. SINGLE ARMv7 must
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
    parser.add_argument('--precision', choices=('DOUBLE', 'SINGLE', 'both'), default='both')
    parser.add_argument('--output-dir', type=Path, default=ROOT / 'out/vertex-fp-policy')
    args = parser.parse_args()
    compilers = args.ndk / 'toolchains/llvm/prebuilt/linux-x86_64/bin'
    args.output_dir.mkdir(parents=True, exist_ok=True)
    modes = ('DOUBLE', 'SINGLE') if args.precision == 'both' else (args.precision,)
    for precision in modes:
        for abi, target in [('armeabi-v7a', 'armv7a-linux-androideabi26'),
                            ('arm64-v8a', 'aarch64-linux-android26')]:
            output = args.output_dir / (abi + '-' + precision + '.ll')
            command = [str(compilers / (target + '-clang++')), '-std=c++17', '-O2',
                       '-fno-strict-aliasing', '-ffp-contract=off', '-DWITH_MMX',
                       '-DNFS_GAME_SINGLE_PRECISION=' + ('1' if precision == 'SINGLE' else '0'),
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
            if precision == 'DOUBLE':
                if retries or 'FloatMath' in ir or 'roundSingleSlow' in ir:
                    raise SystemExit(abi + ': DOUBLE retained single rounding or float/retry dispatch')
                if 'fmul double' not in ir and 'llvm.experimental.constrained.fmul.f64' not in ir:
                    raise SystemExit(abi + ': DOUBLE lost hardware double operations')
            elif abi == 'armeabi-v7a' and (retries or 'FloatMath' in ir):
                raise SystemExit('ARMv7 SINGLE retained unsupported exception tracking')
            elif abi == 'arm64-v8a' and not (retries and strict):
                raise SystemExit('ARM64 SINGLE lost strict exception/retry semantics')
            print(abi + ' ' + precision + ': passed', flush=True)


if __name__ == '__main__':
    main()
