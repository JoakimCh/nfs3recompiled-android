/* include/mmx.h's MMX in plain C++ held against the x86's own MMX: each
 * instruction of it the game uses run both ways on the same operands --
 * random, and the lanes' edges (0, 1, -1, the largest and smallest of a
 * byte, a word, a dword) far more often than chance would give them -- and
 * the shifts by every count up to past 64 and by any.
 *
 *     c++ -std=c++17 -O1 -Iinclude tools/mmx_checks/mmx_checks.cpp && ./a.out [cases]
 *
 * Needs an x86 host and GCC or Clang: the reference is the x86's MMX unit
 * itself, by inline assembly on the mm registers -- compilers turn MMX's
 * intrinsics into SSE on x86-64. */
#include <mmx.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <random>

namespace
{

std::mt19937_64 g_random(1998);

/* The instruction run by the x86's MMX on a and b: a in the destination. */
#define MMX(instruction)                                                                  \
    [](x86::reg64 a, x86::reg64 b) {                                                      \
        x86::reg64 r;                                                                     \
        asm("movq %1, %%mm0\n\tmovq %2, %%mm1\n\t" instruction " %%mm1, %%mm0\n\t"           \
            "movq %%mm0, %0\n\temms"                                                      \
            : "=m"(r) : "m"(a), "m"(b) : "mm0", "mm1");                                 \
        return r;                                                                         \
    }

/* An operand: random, or its lanes from the edges. */
x86::reg64 anOperand()
{
    static const x86::reg16 edges16[] = {0, 1, 0xffff, 0x7fff, 0x8000, 0x7ffe, 0x8001, 0x00ff, 0xff00, 0x0080, 0xff7f, 0x0100};
    static const x86::reg8 edges8[] = {0, 1, 0xff, 0x7f, 0x80, 0x7e, 0x81};
    const unsigned kind = unsigned(g_random() % 4);
    x86::reg64 v = g_random();
    if (kind == 1)
        for (unsigned i = 0; i < 4; ++i)
            if (g_random() % 2)
                v = (v & ~(x86::reg64(0xffff) << (16 * i))) | x86::reg64(edges16[g_random() % 12]) << (16 * i);
    if (kind == 2)
        for (unsigned i = 0; i < 8; ++i)
            if (g_random() % 2)
                v = (v & ~(x86::reg64(0xff) << (8 * i))) | x86::reg64(edges8[g_random() % 7]) << (8 * i);
    if (kind == 3)
        v = g_random() % 2 ? x86::reg64(x86::reg32(g_random())) : v >> (g_random() % 64);
    return v;
}

/* A shift's count: up to past 64 mostly, anything now and then. */
x86::reg64 aCount()
{
    return g_random() % 8 ? g_random() % 72 : g_random();
}

unsigned g_failed = 0;

void check(const char* name, x86::reg64 a, x86::reg64 b, x86::reg64 mine, x86::reg64 mmx)
{
    if (mine != mmx && ++g_failed <= 20)
        std::printf("%s(%016llx, %016llx): %016llx, the x86's %016llx\n", name, (unsigned long long)a,
                    (unsigned long long)b, (unsigned long long)mine, (unsigned long long)mmx);
}

}  // namespace

int main(int argc, char** argv)
{
    namespace op = x86::mmx;
    const unsigned long cases = argc > 1 ? std::strtoul(argv[1], nullptr, 10) : 4000000;
    for (unsigned long i = 0; i < cases; ++i)
    {
        const x86::reg64 a = anOperand(), b = anOperand(), n = aCount();
#define BINARY(name) check(#name, a, b, op::name(a, b), MMX(#name)(a, b))
#define SHIFT(name) check(#name, a, n, op::name(a, n), MMX(#name)(a, n))
        BINARY(pand);
        BINARY(por);
        BINARY(pxor);
        BINARY(paddw);
        BINARY(paddd);
        BINARY(paddsw);
        BINARY(paddsb);
        BINARY(pmulhw);
        BINARY(pmaddwd);
        BINARY(punpcklbw);
        BINARY(punpckhbw);
        BINARY(punpcklwd);
        BINARY(punpckhwd);
        BINARY(punpckldq);
        BINARY(punpckhdq);
        BINARY(packuswb);
        BINARY(packsswb);
        BINARY(packssdw);
        SHIFT(psllw);
        SHIFT(pslld);
        SHIFT(psllq);
        SHIFT(psrlw);
        SHIFT(psrld);
        SHIFT(psrlq);
        SHIFT(psraw);
        SHIFT(psrad);
        // movd: a dword into a register, the rest 0.
        x86::reg64 moved;
        const x86::reg32 low = x86::reg32(a);
        asm("movq %2, %%mm0\n\tmovd %1, %%mm0\n\tmovq %%mm0, %0\n\temms" : "=m"(moved) : "r"(low), "m"(b) : "mm0");
        check("movd", a, b, op::movd(low), moved);
    }
    std::printf("%lu cases of 27 instructions: %s\n", cases, g_failed ? "FAILED" : "all as the x86's MMX");
    return g_failed ? 1 : 0;
}
