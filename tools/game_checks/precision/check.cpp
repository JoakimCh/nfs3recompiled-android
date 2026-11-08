#include <fpu.h>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <limits>

int main()
{
    const double delta = std::ldexp(1.0, -30);
    const double expected = nfs_precision::single ? 1.0 : 1.0 + delta;
    assert(fp::add(1.0, delta) == expected);
    assert(fp::sub(1.0 + delta, 0.0) == expected);
    assert(fp::mul(1.0 + delta, 1.0) == expected);
    assert(fp::div(1.0 + delta, 1.0) == expected);
    const double root = std::sqrt(2.0);
    assert(fp::sqrt(2.0) == (nfs_precision::single ? double(float(root)) : root));
    x86::FPU fpu;
    fpu.init();
    // A guest requesting single precision must not undo a DOUBLE build.
    fpu.setControl(0x007f);
    assert(fpu.add(1.0, delta) == expected);
    assert(fpu.sub(1.0 + delta, 0.0) == expected);
    assert(fpu.mul(1.0 + delta, 1.0) == expected);
    assert(fpu.div(1.0 + delta, 1.0) == expected);
    assert(fpu.sqrt(2.0) == (nfs_precision::single ? double(float(root)) : root));
    assert(fpu.toInteger<int32_t>(3.7) == 4);
    fpu.setControl(0x0c7f); // truncation remains independent of arithmetic precision
    assert(fpu.toInteger<int32_t>(3.7) == 3);
    assert(fpu.toInteger<int32_t>(-3.7) == -3);
    fpu.setControl(0x047f); // round down
    assert(fpu.toInteger<int32_t>(-3.7) == -4);
    assert(fpu.toInteger<int32_t>(std::numeric_limits<double>::quiet_NaN()) == INT32_MIN);
    assert(fp::toInteger<int32_t>(std::numeric_limits<double>::infinity()) == INT32_MIN);
    assert(fp::toInteger<int32_t>(2147483648.0) == INT32_MIN);
    volatile float stored = float(1.0 + delta);
    assert(stored == 1.0f);
}
