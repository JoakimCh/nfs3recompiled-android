#ifndef MMX_H_
#define MMX_H_

#include <x86.h>
#include <cstring>

namespace x86
{

/* An MMX register: 64 bits, as the generated code and the natives (via
 * reg64 and from_reg64) have it.  Its arithmetic is plain C++ (x86::mmx
 * below) on every host -- no SSE intrinsics, nothing to translate on ARM. */
struct regmmx
{
    reg64 reg;
    operator x86::reg64() const
    {
        return reg;
    }
};

static inline regmmx from_reg64(const x86::reg64& value)
{
    return regmmx{value};
}

/* MMX's arithmetic in plain C++: each instruction of it the game uses, on a
 * register's 64 bits -- four words, two dwords or eight bytes, the first in
 * the low bits -- as the instruction defines it: saturating where it
 * saturates, wrapping where it wraps, a shift past the lane's width all
 * zeroes (all sign, arithmetic).  The second operand is the source; a pack
 * or an unpack takes the first operand's lanes first. */
namespace mmx
{

inline reg16 word(reg64 v, unsigned i) { return reg16(v >> (16 * i)); }
inline reg32 dword(reg64 v, unsigned i) { return reg32(v >> (32 * i)); }
inline reg8 byte(reg64 v, unsigned i) { return reg8(v >> (8 * i)); }

inline reg64 words(reg16 w0, reg16 w1, reg16 w2, reg16 w3)
{
    return reg64(w0) | reg64(w1) << 16 | reg64(w2) << 32 | reg64(w3) << 48;
}

inline reg64 dwords(reg32 d0, reg32 d1)
{
    return reg64(d0) | reg64(d1) << 32;
}

inline sreg16 saturate16(sreg32 v) { return sreg16(v < -32768 ? -32768 : v > 32767 ? 32767 : v); }
inline sreg8 saturate8(sreg32 v) { return sreg8(v < -128 ? -128 : v > 127 ? 127 : v); }
inline reg8 saturateU8(sreg32 v) { return reg8(v < 0 ? 0 : v > 255 ? 255 : v); }

/* movd: a dword in, the rest 0; and out. */
inline reg64 movd(reg32 v) { return v; }

inline reg64 pand(reg64 a, reg64 b) { return a & b; }
inline reg64 por(reg64 a, reg64 b) { return a | b; }
inline reg64 pxor(reg64 a, reg64 b) { return a ^ b; }

inline reg64 paddw(reg64 a, reg64 b)
{
    return words(reg16(word(a, 0) + word(b, 0)), reg16(word(a, 1) + word(b, 1)), reg16(word(a, 2) + word(b, 2)),
                 reg16(word(a, 3) + word(b, 3)));
}

inline reg64 paddd(reg64 a, reg64 b)
{
    return dwords(dword(a, 0) + dword(b, 0), dword(a, 1) + dword(b, 1));
}

inline reg64 paddsw(reg64 a, reg64 b)
{
    reg16 r[4];
    for (unsigned i = 0; i < 4; ++i)
        r[i] = reg16(saturate16(sreg32(sreg16(word(a, i))) + sreg16(word(b, i))));
    return words(r[0], r[1], r[2], r[3]);
}

inline reg64 paddsb(reg64 a, reg64 b)
{
    reg64 r = 0;
    for (unsigned i = 0; i < 8; ++i)
        r |= reg64(reg8(saturate8(sreg32(sreg8(byte(a, i))) + sreg8(byte(b, i))))) << (8 * i);
    return r;
}

/* The high words of the four signed products. */
inline reg64 pmulhw(reg64 a, reg64 b)
{
    reg16 r[4];
    for (unsigned i = 0; i < 4; ++i)
        r[i] = reg16(reg32(sreg32(sreg16(word(a, i))) * sreg16(word(b, i))) >> 16);
    return words(r[0], r[1], r[2], r[3]);
}

/* Pairs of signed products added, as dwords: -32768 squared twice wraps. */
inline reg64 pmaddwd(reg64 a, reg64 b)
{
    reg32 r[2];
    for (unsigned i = 0; i < 2; ++i)
        r[i] = reg32(sreg32(sreg16(word(a, 2 * i))) * sreg16(word(b, 2 * i)))
               + reg32(sreg32(sreg16(word(a, 2 * i + 1))) * sreg16(word(b, 2 * i + 1)));
    return dwords(r[0], r[1]);
}

inline reg64 psllw(reg64 a, reg64 n)
{
    return n > 15 ? 0 : words(reg16(word(a, 0) << n), reg16(word(a, 1) << n), reg16(word(a, 2) << n),
                              reg16(word(a, 3) << n));
}

inline reg64 pslld(reg64 a, reg64 n)
{
    return n > 31 ? 0 : dwords(dword(a, 0) << n, dword(a, 1) << n);
}

inline reg64 psllq(reg64 a, reg64 n)
{
    return n > 63 ? 0 : a << n;
}

inline reg64 psrlw(reg64 a, reg64 n)
{
    return n > 15 ? 0 : words(reg16(word(a, 0) >> n), reg16(word(a, 1) >> n), reg16(word(a, 2) >> n),
                              reg16(word(a, 3) >> n));
}

inline reg64 psrld(reg64 a, reg64 n)
{
    return n > 31 ? 0 : dwords(dword(a, 0) >> n, dword(a, 1) >> n);
}

inline reg64 psrlq(reg64 a, reg64 n)
{
    return n > 63 ? 0 : a >> n;
}

inline reg64 psraw(reg64 a, reg64 n)
{
    const unsigned s = n > 15 ? 15 : unsigned(n);
    return words(reg16(sreg16(word(a, 0)) >> s), reg16(sreg16(word(a, 1)) >> s), reg16(sreg16(word(a, 2)) >> s),
                 reg16(sreg16(word(a, 3)) >> s));
}

inline reg64 psrad(reg64 a, reg64 n)
{
    const unsigned s = n > 31 ? 31 : unsigned(n);
    return dwords(reg32(sreg32(dword(a, 0)) >> s), reg32(sreg32(dword(a, 1)) >> s));
}

inline reg64 punpcklbw(reg64 a, reg64 b)
{
    reg64 r = 0;
    for (unsigned i = 0; i < 4; ++i)
        r |= reg64(byte(a, i)) << (16 * i) | reg64(byte(b, i)) << (16 * i + 8);
    return r;
}

inline reg64 punpckhbw(reg64 a, reg64 b)
{
    return punpcklbw(a >> 32, b >> 32);
}

inline reg64 punpcklwd(reg64 a, reg64 b)
{
    return words(word(a, 0), word(b, 0), word(a, 1), word(b, 1));
}

inline reg64 punpckhwd(reg64 a, reg64 b)
{
    return words(word(a, 2), word(b, 2), word(a, 3), word(b, 3));
}

inline reg64 punpckldq(reg64 a, reg64 b)
{
    return dwords(dword(a, 0), dword(b, 0));
}

inline reg64 punpckhdq(reg64 a, reg64 b)
{
    return dwords(dword(a, 1), dword(b, 1));
}

inline reg64 packuswb(reg64 a, reg64 b)
{
    reg64 r = 0;
    for (unsigned i = 0; i < 4; ++i)
        r |= reg64(saturateU8(sreg16(word(a, i)))) << (8 * i) | reg64(saturateU8(sreg16(word(b, i)))) << (8 * i + 32);
    return r;
}

inline reg64 packsswb(reg64 a, reg64 b)
{
    reg64 r = 0;
    for (unsigned i = 0; i < 4; ++i)
        r |= reg64(reg8(saturate8(sreg16(word(a, i))))) << (8 * i)
             | reg64(reg8(saturate8(sreg16(word(b, i))))) << (8 * i + 32);
    return r;
}

inline reg64 packssdw(reg64 a, reg64 b)
{
    return words(reg16(saturate16(sreg32(dword(a, 0)))), reg16(saturate16(sreg32(dword(a, 1)))),
                 reg16(saturate16(sreg32(dword(b, 0)))), reg16(saturate16(sreg32(dword(b, 1)))));
}

}  // namespace mmx

struct MMX
{
    regmmx mm0;
    regmmx mm1;
    regmmx mm2;
    regmmx mm3;
    regmmx mm4;
    regmmx mm5;
    regmmx mm6;
    regmmx mm7;
    void init()
    {
        memset(this, 0, sizeof(*this));
    }
};

}

#endif /* !MMX_H_ */
