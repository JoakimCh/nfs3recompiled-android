#include "native_guest.h"
#include <mmx.h>
#include <utility>

/* nfs3.exe's MMX, native: all of the game's code that uses it -- the SND
 * library's MMX routines, which the mixer is handed when the CPU has MMX
 * (adding a block into the accumulator at its volume, the accumulator into
 * the output, interpolating, decoding EA's XA ADPCM), and the memmove the
 * game's file reads copy with.  disassemble_nfs3hp.py binds each address to
 * the function of that name here (MMX_NATIVES), and the generated code calls
 * it by name.  tools/game_checks generates the game's code for them afresh
 * and holds each one against it.
 *
 * Each is its instructions as the game has them, with include/mmx.h's MMX:
 * the same operations on the same registers in the same order, the memory
 * read and written in the order its code reads and writes it.  The MMX
 * registers are the CPU's (cpu.mmx), part of what each leaves: the routines
 * read registers they never set -- an unpack's other half, the decoders'
 * history -- and leave theirs to the next, which reads them in turn; none
 * but clear and emms empties them.  The general registers are their callers'
 * still, the SND routines' by pushal and popal, the memmove's but the three
 * it moves on, as their code leaves them; their loops' counts are the x86's,
 * signed, run once at least where its code runs them so. */

namespace nfs3hp
{
namespace mmx
{

namespace
{

namespace op = x86::mmx;
using guest::at;
using guest::byte;
using guest::put;
using guest::putByte;

x86::reg16 at16(win32::WinApplication* app, x86::reg32 address)
{
    return app->getMemory<x86::reg16>(address);
}

void put16(win32::WinApplication* app, x86::reg32 address, x86::reg16 value)
{
    app->getMemory<x86::reg16>(address) = value;
}

x86::reg64 at64(win32::WinApplication* app, x86::reg32 address)
{
    return app->getMemory<x86::reg64>(address);
}

void put64(win32::WinApplication* app, x86::reg32 address, x86::reg64 value)
{
    app->getMemory<x86::reg64>(address) = value;
}

/* The MMX registers as the routine has them, back into the CPU when it is
 * done. */
struct Registers
{
    x86::CPU& cpu;
    x86::reg64 mm[8];

    explicit Registers(x86::CPU& cpu)
        : cpu(cpu)
        , mm{cpu.mmx.mm0, cpu.mmx.mm1, cpu.mmx.mm2, cpu.mmx.mm3, cpu.mmx.mm4, cpu.mmx.mm5, cpu.mmx.mm6, cpu.mmx.mm7}
    {
    }
    ~Registers()
    {
        cpu.mmx.mm0 = x86::from_reg64(mm[0]);
        cpu.mmx.mm1 = x86::from_reg64(mm[1]);
        cpu.mmx.mm2 = x86::from_reg64(mm[2]);
        cpu.mmx.mm3 = x86::from_reg64(mm[3]);
        cpu.mmx.mm4 = x86::from_reg64(mm[4]);
        cpu.mmx.mm5 = x86::from_reg64(mm[5]);
        cpu.mmx.mm6 = x86::from_reg64(mm[6]);
        cpu.mmx.mm7 = x86::from_reg64(mm[7]);
    }
};

/* A cdecl argument: the i-th dword above the return address. */
x86::reg32 argument(win32::WinApplication* app, const x86::CPU& cpu, unsigned i)
{
    return at(app, cpu.esp + 4 + 4 * i);
}

/* Signed comparisons as the x86's jl and jg take them after a sub, or a cmp:
 * of the 32-bit values, before the subtraction. */
bool less(x86::reg32 a, x86::sreg32 b)
{
    return x86::sreg32(a) < b;
}

bool greater(x86::reg32 a, x86::sreg32 b)
{
    return x86::sreg32(a) > b;
}

/* The adds' loops' first steps: four (or eight) frames at a time, unless
 * the count is not a multiple and is under them -- then straight to the tail,
 * and the count less them. */
bool straightToTail(x86::reg32& count, x86::reg32 block)
{
    if ((count & (block - 1)) == 0)
        return false;
    const bool tail = less(count, x86::sreg32(block));
    count -= block;
    return tail;
}

/* 16.16 positions: the fraction's add and the whole's add with its carry. */
void step(x86::reg32& fraction, x86::reg32& position, x86::reg32 stepFraction, x86::reg32 stepWhole)
{
    const x86::reg32 sum = fraction + stepFraction;
    const x86::reg32 carry = sum < fraction ? 1 : 0;
    fraction = sum;
    position += stepWhole + carry;
}

/* The interpolators' rates: a 16.16 fraction as words, (f >> 16 | f) ^ 0xffff
 * -- once, or in both dwords. */
x86::reg64 rate(x86::reg32 fraction, x86::reg64 ones)
{
    return op::pxor(op::por(op::psrld(op::movd(fraction), 16), op::movd(fraction)), ones);
}

x86::reg64 rateTwice(x86::reg32 fraction, x86::reg64 ones)
{
    const x86::reg64 once = rate(fraction, ones);
    return op::por(op::psllq(once, 32), once);
}

/* The XA decoders' table of nibbles, shifted: 16 dwords for each shift. */
constexpr x86::reg32 kNibbles = 0xa0bea0;
/* XA's filters, two words each: the first sample's and the second's. */
constexpr x86::reg32 kFilterFirst = 0x56ad70, kFilterSecond = 0x56ad80;
/* outputStereo8's xor, 0x80 a byte: signed to unsigned. */
constexpr x86::reg32 kSignBits = 0x56ad00;

}  // namespace

/* 0x51f5dd: a mono block of 8-bit samples into the stereo accumulator, at
 * the two volumes' -- each sample the high byte of a word whose low byte is
 * what mm6 had -- four frames at a time, then one at a time; cdecl (volumes,
 * count, source, accumulator). */
void addMono8(win32::WinApplication* app, x86::CPU& cpu)
{
    {
        Registers r(cpu);
        x86::reg64* mm = r.mm;
        const x86::reg32 volumes = argument(app, cpu, 0);
        x86::reg32 count = argument(app, cpu, 1), source = argument(app, cpu, 2), target = argument(app, cpu, 3);
        mm[0] = at64(app, volumes);
        mm[1] = at64(app, volumes + 8);
        bool tail = straightToTail(count, 4);
        if (!tail)
        {
            bool more;
            do
            {
                mm[2] = mm[0];
                mm[4] = mm[1];
                mm[5] = op::movd(at(app, source));
                mm[6] = op::punpcklbw(mm[6], mm[5]);
                mm[2] = op::pmulhw(mm[2], mm[6]);
                mm[4] = op::pmulhw(mm[4], mm[6]);
                mm[3] = op::punpckhwd(mm[2], mm[4]);
                mm[2] = op::punpcklwd(mm[2], mm[4]);
                mm[2] = op::paddsw(mm[2], at64(app, target));
                mm[3] = op::paddsw(mm[3], at64(app, target + 8));
                put64(app, target, mm[2]);
                put64(app, target + 8, mm[3]);
                source += 4;
                target += 0x10;
                more = greater(count, 4);
                count -= 4;
            } while (more);
            tail = count != 0;
        }
        if (tail)
        {
            count = 0 - (count + 4);
            x86::reg32 eax = 0;
            bool more;
            do
            {
                mm[2] = mm[0];
                mm[4] = mm[1];
                eax = (eax & 0xffff00ff) | x86::reg32(byte(app, source)) << 8;
                mm[6] = op::movd(eax);
                mm[2] = op::pmulhw(mm[2], mm[6]);
                mm[4] = op::pmulhw(mm[4], mm[6]);
                mm[3] = op::punpckhwd(mm[2], mm[4]);
                mm[2] = op::punpcklwd(mm[2], mm[4]);
                mm[3] = op::movd(at(app, target));
                mm[3] = op::paddsw(mm[3], mm[2]);
                put(app, target, x86::reg32(mm[3]));
                source += 1;
                target += 4;
                more = less(count, -1);
                count += 1;
            } while (more);
        }
    }
    cpu.esp += 4;
}

/* 0x51f6c7: a stereo block of 8-bit samples into the accumulator, the same
 * way -- the low bytes mm4's and mm5's -- four frames, then one; cdecl
 * (volume, count, source, accumulator). */
void addStereo8(win32::WinApplication* app, x86::CPU& cpu)
{
    {
        Registers r(cpu);
        x86::reg64* mm = r.mm;
        const x86::reg32 volume = argument(app, cpu, 0);
        x86::reg32 count = argument(app, cpu, 1), source = argument(app, cpu, 2), target = argument(app, cpu, 3);
        const x86::reg32 low = count & 3;
        mm[0] = at64(app, volume);
        bool tail = straightToTail(count, 4);
        if (!tail)
        {
            bool more;
            do
            {
                mm[3] = at64(app, source);
                mm[1] = mm[0];
                mm[2] = mm[0];
                mm[4] = op::punpcklbw(mm[4], mm[3]);
                mm[5] = op::punpckhbw(mm[5], mm[3]);
                mm[1] = op::pmulhw(mm[1], mm[4]);
                mm[2] = op::pmulhw(mm[2], mm[5]);
                mm[1] = op::paddsw(mm[1], at64(app, target));
                mm[2] = op::paddsw(mm[2], at64(app, target + 8));
                put64(app, target, mm[1]);
                put64(app, target + 8, mm[2]);
                source += 8;
                target += 0x10;
                more = greater(count, 4);
                count -= 4;
            } while (more);
            tail = count != 0;
        }
        if (tail)
        {
            count = 0 - (count + 4);
            x86::reg32 eax = low;
            bool more;
            do
            {
                eax = (eax & 0xffffff00) | byte(app, source + 1);
                eax <<= 24;
                eax = (eax & 0xffff00ff) | x86::reg32(byte(app, source)) << 8;
                mm[1] = op::movd(eax);
                mm[1] = op::pmulhw(mm[1], mm[0]);
                mm[2] = op::movd(at(app, target));
                mm[1] = op::paddsw(mm[1], mm[2]);
                put(app, target, x86::reg32(mm[1]));
                source += 2;
                target += 4;
                more = less(count, -1);
                count += 1;
            } while (more);
        }
    }
    cpu.esp += 4;
}

/* 0x51f7ad: a mono block of 16-bit samples into the stereo accumulator at the
 * two volumes', four frames at a time, then one; cdecl (volumes, count,
 * source, accumulator). */
void addMono16(win32::WinApplication* app, x86::CPU& cpu)
{
    {
        Registers r(cpu);
        x86::reg64* mm = r.mm;
        const x86::reg32 volumes = argument(app, cpu, 0);
        x86::reg32 count = argument(app, cpu, 1), source = argument(app, cpu, 2), target = argument(app, cpu, 3);
        const x86::reg32 low = count & 3;
        mm[0] = at64(app, volumes);
        mm[1] = at64(app, volumes + 8);
        bool tail = straightToTail(count, 4);
        if (!tail)
        {
            bool more;
            do
            {
                mm[2] = mm[0];
                mm[4] = mm[1];
                mm[6] = at64(app, source);
                mm[2] = op::pmulhw(mm[2], mm[6]);
                mm[4] = op::pmulhw(mm[4], mm[6]);
                mm[3] = op::punpckhwd(mm[2], mm[4]);
                mm[2] = op::punpcklwd(mm[2], mm[4]);
                mm[2] = op::paddsw(mm[2], at64(app, target));
                mm[3] = op::paddsw(mm[3], at64(app, target + 8));
                put64(app, target, mm[2]);
                put64(app, target + 8, mm[3]);
                source += 8;
                target += 0x10;
                more = greater(count, 4);
                count -= 4;
            } while (more);
            tail = count != 0;
        }
        if (tail)
        {
            count = 0 - (count + 4);
            x86::reg32 eax = low;
            bool more;
            do
            {
                mm[2] = mm[0];
                mm[4] = mm[1];
                eax = (eax & 0xffff0000) | at16(app, source);
                mm[6] = op::movd(eax);
                mm[2] = op::pmulhw(mm[2], mm[6]);
                mm[4] = op::pmulhw(mm[4], mm[6]);
                mm[3] = op::punpckhwd(mm[2], mm[4]);
                mm[2] = op::punpcklwd(mm[2], mm[4]);
                mm[3] = op::movd(at(app, target));
                mm[3] = op::paddsw(mm[3], mm[2]);
                put(app, target, x86::reg32(mm[3]));
                source += 2;
                target += 4;
                more = less(count, -1);
                count += 1;
            } while (more);
        }
    }
    cpu.esp += 4;
}

/* 0x51f897: a stereo block of 16-bit samples into the accumulator at its
 * volume, eight frames at a time, then one; cdecl (volume, count, source,
 * accumulator). */
void addStereo16(win32::WinApplication* app, x86::CPU& cpu)
{
    {
        Registers r(cpu);
        x86::reg64* mm = r.mm;
        const x86::reg32 volume = argument(app, cpu, 0);
        x86::reg32 count = argument(app, cpu, 1), source = argument(app, cpu, 2), target = argument(app, cpu, 3);
        mm[0] = at64(app, volume);
        bool tail = straightToTail(count, 8);
        if (!tail)
        {
            bool more;
            do
            {
                for (unsigned i = 1; i <= 4; ++i)
                    mm[i] = mm[0];
                for (unsigned i = 1; i <= 4; ++i)
                    mm[i] = op::pmulhw(mm[i], at64(app, source + 8 * (i - 1)));
                for (unsigned i = 1; i <= 4; ++i)
                    mm[i] = op::paddsw(mm[i], at64(app, target + 8 * (i - 1)));
                for (unsigned i = 1; i <= 4; ++i)
                    put64(app, target + 8 * (i - 1), mm[i]);
                source += 0x20;
                target += 0x20;
                more = greater(count, 8);
                count -= 8;
            } while (more);
            tail = count != 0;
        }
        if (tail)
        {
            count = 0 - (count + 8);
            mm[1] = mm[0];
            bool more;
            do
            {
                mm[1] = op::movd(at(app, source));
                mm[1] = op::pmulhw(mm[1], mm[0]);
                mm[2] = op::movd(at(app, target));
                mm[1] = op::paddsw(mm[1], mm[2]);
                put(app, target, x86::reg32(mm[1]));
                source += 4;
                target += 4;
                more = less(count, -1);
                count += 1;
            } while (more);
        }
    }
    cpu.esp += 4;
}

/* 0x520830: the accumulator's frames, left and right added with saturation,
 * into 8-bit unsigned mono, last frame first; eax's high word rides along in
 * the registers' second words.  cdecl (count, accumulator, output). */
void outputMono8(win32::WinApplication* app, x86::CPU& cpu)
{
    {
        Registers r(cpu);
        x86::reg64* mm = r.mm;
        x86::reg32 count = argument(app, cpu, 0);
        const x86::reg32 source = argument(app, cpu, 1), target = argument(app, cpu, 2);
        x86::reg32 eax = cpu.eax;
        bool more;
        do
        {
            eax = (eax & 0xffff0000) | at16(app, source + count * 4 - 4);
            mm[0] = op::movd(eax);
            eax = (eax & 0xffff0000) | at16(app, source + count * 4 - 2);
            mm[1] = op::movd(eax);
            mm[0] = op::paddsw(mm[0], mm[1]);
            eax = x86::reg32(mm[0]) ^ 0x8000;
            putByte(app, count + target - 1, x86::reg8(eax >> 8));
            more = greater(count, 1);
            count -= 1;
        } while (more);
    }
    cpu.esp += 4;
}

/* 0x520870: the accumulator doubled with saturation into 8-bit unsigned
 * stereo -- the high bytes, packed, the sign flipped by 0x56ad00's -- 32
 * bytes at a time from the end; cdecl (frames, accumulator, output). */
void outputStereo8(win32::WinApplication* app, x86::CPU& cpu)
{
    {
        Registers r(cpu);
        x86::reg64* mm = r.mm;
        x86::reg32 count = argument(app, cpu, 0) << 1;
        const x86::reg32 source = argument(app, cpu, 1), target = argument(app, cpu, 2);
        bool more;
        do
        {
            for (unsigned i = 0; i < 8; ++i)
                mm[i] = at64(app, source + count * 2 - 8 * (i + 1));
            for (unsigned i = 0; i < 8; ++i)
                mm[i] = op::paddsw(mm[i], mm[i]);
            for (unsigned i = 0; i < 8; ++i)
                mm[i] = op::psrlw(mm[i], 8);
            for (unsigned i = 1; i < 8; i += 2)
                mm[i] = op::packuswb(mm[i], mm[i - 1]);
            mm[0] = at64(app, kSignBits);
            for (unsigned i = 1; i < 8; i += 2)
                mm[i] = op::pxor(mm[i], mm[0]);
            for (unsigned i = 1; i < 8; i += 2)
                put64(app, count + target - 8 * ((i + 1) / 2), mm[i]);
            more = greater(count, 0x20);
            count -= 0x20;
        } while (more);
    }
    cpu.esp += 4;
}

/* 0x520920: the accumulator doubled with saturation into 16-bit stereo, 64
 * bytes at a time from the end; cdecl (frames, accumulator, output). */
void outputStereo16(win32::WinApplication* app, x86::CPU& cpu)
{
    {
        Registers r(cpu);
        x86::reg64* mm = r.mm;
        x86::reg32 count = argument(app, cpu, 0) << 2;
        const x86::reg32 source = argument(app, cpu, 1), target = argument(app, cpu, 2);
        bool more;
        do
        {
            for (unsigned i = 0; i < 8; ++i)
                mm[i] = at64(app, count + source - 8 * (i + 1));
            for (unsigned i = 0; i < 8; ++i)
                mm[i] = op::paddsw(mm[i], mm[i]);
            for (unsigned i = 0; i < 8; ++i)
                put64(app, count + target - 8 * (i + 1), mm[i]);
            more = greater(count, 0x40);
            count -= 0x40;
        } while (more);
    }
    cpu.esp += 4;
}

/* 0x5209a0: the accumulator cleared, 64 bytes at a time while more than 15
 * dwords are left, then a dword at a time; MMX emptied.  cdecl
 * (accumulator, dwords). */
void clear(win32::WinApplication* app, x86::CPU& cpu)
{
    {
        Registers r(cpu);
        x86::reg64* mm = r.mm;
        x86::reg32 count = argument(app, cpu, 1), target = argument(app, cpu, 0);
        mm[0] = op::pxor(mm[0], mm[0]);
        if (greater(count, 0xf))
        {
            count -= 0xf;
            bool more;
            do
            {
                for (unsigned i = 0; i < 8; ++i)
                    put64(app, target + 8 * i, mm[0]);
                target += 0x40;
                more = greater(count, 0x10);
                count -= 0x10;
            } while (more);
            count += 0xf;
        }
        while (greater(count, 0))
        {
            put(app, target, x86::reg32(mm[0]));
            target += 4;
            count -= 1;
        }
        for (unsigned i = 0; i < 8; ++i)
            mm[i] = 0;  // emms
    }
    cpu.esp += 4;
}

/* 0x520a00: MMX emptied. */
void emms(win32::WinApplication* app, x86::CPU& cpu)
{
    NFS2_USE(app);
    cpu.mmx.init();
    cpu.esp += 4;
}

/* 0x520a10: the accumulator's frames, left and right added with saturation,
 * into 16-bit mono, last frame first; cdecl (count, accumulator, output). */
void outputMono16(win32::WinApplication* app, x86::CPU& cpu)
{
    {
        Registers r(cpu);
        x86::reg64* mm = r.mm;
        x86::reg32 count = argument(app, cpu, 0);
        const x86::reg32 source = argument(app, cpu, 1), target = argument(app, cpu, 2);
        x86::reg32 eax = cpu.eax;
        bool more;
        do
        {
            eax = (eax & 0xffff0000) | at16(app, source + count * 4 - 4);
            mm[0] = op::movd(eax);
            eax = (eax & 0xffff0000) | at16(app, source + count * 4 - 2);
            mm[1] = op::movd(eax);
            mm[0] = op::paddsw(mm[0], mm[1]);
            eax = x86::reg32(mm[0]);
            put16(app, target + count * 2 - 2, x86::reg16(eax));
            more = greater(count, 1);
            count -= 1;
        } while (more);
    }
    cpu.esp += 4;
}

/* The interpolators' arguments: cdecl (frames, source, output, the whole
 * position's dword, the fraction's, the step's whole, its fraction); both
 * positions written back at the end. */
struct Interpolation
{
    win32::WinApplication* app;
    const x86::CPU& cpu;
    x86::reg32 count, source, target, stepWhole, stepFraction, fraction, whole;

    Interpolation(win32::WinApplication* app, const x86::CPU& cpu)
        : app(app)
        , cpu(cpu)
        , count(argument(app, cpu, 0))
        , source(argument(app, cpu, 1))
        , target(argument(app, cpu, 2))
        , stepWhole(argument(app, cpu, 5))
        , stepFraction(argument(app, cpu, 6))
        , fraction(at(app, argument(app, cpu, 4)))
        , whole(at(app, argument(app, cpu, 3)))
    {
    }
    /* A frame on: the output on, the count down. */
    bool next(x86::reg32 size)
    {
        target += size;
        const bool more = greater(count, 1);
        count -= 1;
        return more;
    }
    /* The positions back where the arguments point, read again from the
     * stack as its code does. */
    void end()
    {
        put(app, argument(app, cpu, 4), fraction);
        put(app, argument(app, cpu, 3), whole);
    }
};

/* 0x5270f0: 8-bit mono interpolated between a frame and the next, by the
 * position's fraction, into 8 bits. */
void interpolateMono8(win32::WinApplication* app, x86::CPU& cpu)
{
    {
        Registers r(cpu);
        x86::reg64* mm = r.mm;
        mm[3] = op::movd(0xffff);
        Interpolation s(app, cpu);
        mm[1] = op::movd(s.fraction);
        mm[2] = op::movd(s.fraction);
        mm[1] = op::pxor(op::por(op::psrld(mm[1], 16), mm[2]), mm[3]);
        mm[4] = op::movd(s.stepFraction - 1);
        mm[5] = op::movd(s.stepFraction);
        mm[4] = op::pxor(op::por(op::psrld(mm[4], 16), mm[5]), mm[3]);
        do
        {
            mm[0] = op::punpcklbw(mm[0], op::movd(at(app, s.whole + s.source)));
            mm[2] = op::psrlw(mm[1], 1);
            mm[0] = op::pmaddwd(mm[0], mm[2]);
            mm[0] = op::psrlq(mm[0], 0x17);
            const x86::reg32 ecx = x86::reg32(mm[0]);
            mm[1] = op::paddw(mm[1], mm[4]);
            putByte(app, s.target, x86::reg8(ecx));
            step(s.fraction, s.whole, s.stepFraction, s.stepWhole);
        } while (s.next(1));
        s.end();
    }
    cpu.esp += 4;
}

/* 0x527170: 8-bit stereo, the same, into 8 bits with signed saturation; a
 * dword written for each two bytes. */
void interpolateStereo8(win32::WinApplication* app, x86::CPU& cpu)
{
    {
        Registers r(cpu);
        x86::reg64* mm = r.mm;
        mm[4] = op::movd(0xffff);
        Interpolation s(app, cpu);
        mm[2] = op::movd(s.fraction);
        mm[3] = op::movd(s.fraction);
        mm[2] = op::pxor(op::por(op::psrld(mm[2], 16), mm[3]), mm[4]);
        mm[5] = mm[2];
        mm[2] = op::por(op::psllq(mm[2], 32), mm[5]);
        mm[5] = op::movd(s.stepFraction - 1);
        mm[6] = op::movd(s.stepFraction);
        mm[5] = op::pxor(op::por(op::psrld(mm[5], 16), mm[6]), mm[4]);
        mm[4] = mm[5];
        mm[5] = op::por(op::psllq(mm[5], 32), mm[4]);
        do
        {
            mm[1] = op::movd(at(app, s.source + s.whole * 2));
            mm[3] = op::psrlw(mm[2], 1);
            mm[1] = op::punpcklbw(mm[1], op::movd(at(app, s.source + s.whole * 2 + 2)));
            mm[0] = op::punpcklbw(mm[0], mm[1]);
            mm[0] = op::pmaddwd(mm[0], mm[3]);
            mm[0] = op::psrad(mm[0], 0x17);
            mm[2] = op::paddw(mm[2], mm[5]);
            mm[0] = op::packssdw(mm[0], mm[1]);
            mm[0] = op::packsswb(mm[0], mm[1]);
            put(app, s.target, x86::reg32(mm[0]));
            step(s.fraction, s.whole, s.stepFraction, s.stepWhole);
        } while (s.next(2));
        s.end();
    }
    cpu.esp += 4;
}

/* 0x527210: 16-bit mono, the same, truncated into 16 bits. */
void interpolateMono16(win32::WinApplication* app, x86::CPU& cpu)
{
    {
        Registers r(cpu);
        x86::reg64* mm = r.mm;
        mm[3] = op::movd(0xffff);
        Interpolation s(app, cpu);
        mm[1] = op::movd(s.fraction);
        mm[2] = op::movd(s.fraction);
        mm[1] = op::pxor(op::por(op::psrld(mm[1], 16), mm[2]), mm[3]);
        mm[4] = op::movd(s.stepFraction - 1);
        mm[5] = op::movd(s.stepFraction);
        mm[4] = op::pxor(op::por(op::psrld(mm[4], 16), mm[5]), mm[3]);
        do
        {
            mm[0] = op::movd(at(app, s.source + s.whole * 2));
            mm[2] = op::psrlw(mm[1], 1);
            mm[0] = op::pmaddwd(mm[0], mm[2]);
            mm[0] = op::psrlq(mm[0], 0xf);
            const x86::reg32 ecx = x86::reg32(mm[0]);
            mm[1] = op::paddw(mm[1], mm[4]);
            put16(app, s.target, x86::reg16(ecx));
            step(s.fraction, s.whole, s.stepFraction, s.stepWhole);
        } while (s.next(2));
        s.end();
    }
    cpu.esp += 4;
}

/* 0x527290: 16-bit stereo, the same, into 16 bits with signed saturation. */
void interpolateStereo16(win32::WinApplication* app, x86::CPU& cpu)
{
    {
        Registers r(cpu);
        x86::reg64* mm = r.mm;
        mm[4] = op::movd(0xffff);
        Interpolation s(app, cpu);
        mm[2] = op::movd(s.fraction);
        mm[3] = op::movd(s.fraction);
        mm[2] = op::pxor(op::por(op::psrld(mm[2], 16), mm[3]), mm[4]);
        mm[5] = mm[2];
        mm[2] = op::por(op::psllq(mm[2], 32), mm[5]);
        mm[5] = op::movd(s.stepFraction - 1);
        mm[6] = op::movd(s.stepFraction);
        mm[5] = op::pxor(op::por(op::psrld(mm[5], 16), mm[6]), mm[4]);
        mm[4] = mm[5];
        mm[5] = op::por(op::psllq(mm[5], 32), mm[4]);
        do
        {
            mm[0] = op::movd(at(app, s.source + s.whole * 4));
            mm[0] = op::punpcklwd(mm[0], op::movd(at(app, s.source + s.whole * 4 + 4)));
            mm[3] = op::psrlw(mm[2], 1);
            mm[0] = op::pmaddwd(mm[0], mm[3]);
            mm[0] = op::psrad(mm[0], 0xf);
            mm[2] = op::paddw(mm[2], mm[5]);
            mm[0] = op::packssdw(mm[0], mm[1]);
            put(app, s.target, x86::reg32(mm[0]));
            step(s.fraction, s.whole, s.stepFraction, s.stepWhole);
        } while (s.next(4));
        s.end();
    }
    cpu.esp += 4;
}

/* 0x52d1a0: mono XA -- [+0] samples, whole blocks of 28 of 15 bytes each from
 * [+8], a header's filter and shift then 14 bytes of nibbles -- into 16-bit
 * samples, two to a dword, from [+0xc]; the last two samples, the filter's
 * history, kept in [+4] (mm3).  cdecl (the decoder's state). */
void xaMono(win32::WinApplication* app, x86::CPU& cpu)
{
    {
        Registers r(cpu);
        x86::reg64* mm = r.mm;
        const x86::reg32 state = argument(app, cpu, 0);
        x86::reg32 source = at(app, state + 8), target = at(app, state + 0xc);
        mm[3] = op::movd(at(app, state + 4));
        mm[4] = op::movd(0x7fff0000);
        mm[5] = op::movd(0x80000000);
        x86::reg32 edx = 0;
        while (greater(at(app, state), 0))
        {
            x86::reg32 eax = byte(app, source);
            put(app, state, at(app, state) - 0x1c);
            eax >>= 4;
            target += 0x38;
            mm[1] = op::movd(at(app, eax * 4 + kFilterFirst));
            mm[2] = op::movd(at(app, eax * 4 + kFilterSecond));
            eax = (eax & 0xffffff00) | byte(app, source);
            x86::reg32 ecx = 0xfffffff2;
            eax &= 0xf;
            source += 0xf;
            eax <<= 6;
            bool more;
            do
            {
                edx = (edx & 0xffffff00) | x86::reg8(byte(app, ecx + source) >> 4);
                mm[6] = op::pmaddwd(mm[3], mm[1]);
                mm[0] = op::movd(at(app, eax + edx * 4 + kNibbles));
                mm[6] = op::paddd(mm[6], mm[0]);
                mm[6] = op::pslld(mm[6], 8);
                edx = (edx & 0xffffff00) | (byte(app, ecx + source) & 0xf);
                mm[6] = op::punpcklwd(mm[6], mm[3]);
                mm[6] = op::psrlq(mm[6], 0x20);
                mm[3] = mm[6];
                mm[6] = op::pmaddwd(mm[6], mm[2]);
                mm[0] = op::movd(at(app, eax + edx * 4 + kNibbles));
                mm[6] = op::paddd(mm[6], mm[0]);
                mm[6] = op::psrlq(mm[6], 8);
                mm[3] = op::punpcklwd(mm[3], mm[6]);
                put(app, target + ecx * 4, x86::reg32(mm[3]));
                more = less(ecx, -1);
                ecx += 1;
            } while (more);
        }
        put(app, state + 4, x86::reg32(mm[3]));
        put(app, state + 0xc, target);
    }
    cpu.esp += 4;
}

/* 0x52d250: stereo XA -- 30-byte blocks of 28 frames from [+0xc], a header
 * for each side then their nibbles interleaved -- into 16-bit frames from
 * [+0x10], each two frames' middle words swapped after; the history in [+4]
 * and [+8] (mm3).  cdecl (the decoder's state). */
void xaStereo(win32::WinApplication* app, x86::CPU& cpu)
{
    {
        Registers r(cpu);
        x86::reg64* mm = r.mm;
        const x86::reg32 state = argument(app, cpu, 0);
        x86::reg32 source = at(app, state + 0xc), target = at(app, state + 0x10);
        mm[3] = op::movd(at(app, state + 4));
        mm[3] = op::punpckldq(mm[3], op::movd(at(app, state + 8)));
        mm[7] = op::movd(0xffff);
        mm[7] = op::punpckldq(mm[7], mm[7]);
        mm[5] = op::pslld(mm[7], 16);
        x86::reg32 edx = 0;
        while (greater(at(app, state), 0))
        {
            x86::reg32 eax = byte(app, source);
            put(app, state, at(app, state) - 0x1c);
            edx = eax;
            eax >>= 4;
            edx &= 0xf;
            target += 0x70;
            mm[1] = op::movd(at(app, eax * 4 + kFilterFirst));
            mm[1] = op::punpckldq(mm[1], op::movd(at(app, edx * 4 + kFilterFirst)));
            mm[2] = op::movd(at(app, eax * 4 + kFilterSecond));
            mm[2] = op::punpckldq(mm[2], op::movd(at(app, edx * 4 + kFilterSecond)));
            eax = (eax & 0xffffff00) | byte(app, source + 1);
            x86::reg32 ecx = 0xffffffe4;
            edx = eax;
            eax >>= 4;
            edx &= 0xf;
            source += 0x1e;
            edx <<= 6;
            eax <<= 6;
            const x86::reg32 right = edx;
            edx = 0;
            bool more;
            do
            {
                edx = (edx & 0xffffff00) | x86::reg8(byte(app, ecx + source) >> 4);
                mm[6] = mm[3];
                mm[0] = op::movd(at(app, eax + edx * 4 + kNibbles));
                mm[6] = op::pmaddwd(mm[6], mm[1]);
                edx = (edx & 0xffffff00) | (byte(app, ecx + source) & 0xf);
                mm[0] = op::punpckldq(mm[0], op::movd(at(app, right + edx * 4 + kNibbles)));
                mm[3] = op::pand(mm[3], mm[5]);
                mm[6] = op::paddd(mm[6], mm[0]);
                mm[6] = op::psrld(mm[6], 8);
                mm[6] = op::pand(mm[6], mm[7]);
                mm[3] = op::por(mm[3], mm[6]);
                edx = (edx & 0xffffff00) | x86::reg8(byte(app, ecx + source + 1) >> 4);
                mm[6] = mm[3];
                mm[0] = op::movd(at(app, eax + edx * 4 + kNibbles));
                edx = (edx & 0xffffff00) | (byte(app, ecx + source + 1) & 0xf);
                mm[0] = op::punpckldq(mm[0], op::movd(at(app, right + edx * 4 + kNibbles)));
                mm[6] = op::pmaddwd(mm[6], mm[2]);
                mm[3] = op::pand(mm[3], mm[7]);
                mm[6] = op::paddd(mm[6], mm[0]);
                mm[6] = op::pslld(mm[6], 8);
                mm[6] = op::pand(mm[6], mm[5]);
                mm[3] = op::por(mm[3], mm[6]);
                const x86::reg32 frames = target + ecx * 4;
                put64(app, frames, mm[3]);
                // push word [+2], push word [+4], pop word [+2], pop word [+4]
                const x86::reg16 second = at16(app, frames + 2), third = at16(app, frames + 4);
                put16(app, frames + 2, third);
                put16(app, frames + 4, second);
                more = less(ecx, -2);
                ecx += 2;
            } while (more);
        }
        put(app, state + 4, x86::reg32(mm[3]));
        mm[3] = op::psrlq(mm[3], 0x20);
        put(app, state + 8, x86::reg32(mm[3]));
        put(app, state + 0x10, target);
    }
    cpu.esp += 4;
}

namespace
{

/* The memmove's forward copy, eax to, edx from, ebx bytes: eax brought to 8
 * bytes by a byte, a word and a dword where there are as many; then 128
 * bytes at a time -- seven registers loaded ahead, as its code has them --
 * 32, 8, and the last 4, 2 and 1.  eax, edx and ebx left as it leaves them. */
void copyForward(win32::WinApplication* app, x86::CPU& cpu)
{
    Registers r(cpu);
    x86::reg64* mm = r.mm;
    x86::reg32 to = cpu.eax, from = cpu.edx, left = cpu.ebx;
    if (to & 7)
    {
        if ((to & 1) && !less(left, 1))
        {
            putByte(app, to, byte(app, from));
            from += 1, to += 1, left -= 1;
        }
        if ((to & 2) && !less(left, 2))
        {
            put16(app, to, at16(app, from));
            from += 2, to += 2, left -= 2;
        }
        if ((to & 4) && !less(left, 4))
        {
            put(app, to, at(app, from));
            from += 4, to += 4, left -= 4;
        }
    }
    auto negative = [](x86::reg32 v) { return x86::sreg32(v) < 0; };
    left -= 0x80;
    while (!negative(left))
    {
        mm[0] = at64(app, from);
        mm[4] = at64(app, from + 0x20);
        mm[5] = at64(app, from + 0x40);
        mm[6] = at64(app, from + 0x60);
        for (x86::reg32 block = 0; block < 0x80; block += 0x20)
        {
            for (unsigned i = 1; i <= 3; ++i)
                mm[i] = at64(app, from + block + 8 * i);
            put64(app, to + block, mm[block == 0 ? 0 : 3 + block / 0x20]);
            for (unsigned i = 1; i <= 3; ++i)
                put64(app, to + block + 8 * i, mm[i]);
        }
        from += 0x80, to += 0x80;
        left -= 0x80;
    }
    left += 0x60;
    while (!negative(left))
    {
        for (unsigned i = 0; i < 4; ++i)
            mm[i] = at64(app, from + 8 * i);
        for (unsigned i = 0; i < 4; ++i)
            put64(app, to + 8 * i, mm[i]);
        from += 0x20, to += 0x20;
        left -= 0x20;
    }
    left += 0x18;
    while (!negative(left))
    {
        mm[0] = at64(app, from);
        put64(app, to, mm[0]);
        from += 8, to += 8;
        left -= 8;
    }
    left += 8;
    if (left != 0)
    {
        if (left >= 4)
        {
            put(app, to, at(app, from));
            from += 4, to += 4, left -= 4;
        }
        if (left >= 2)
        {
            put16(app, to, at16(app, from));
            from += 2, to += 2, left -= 2;
        }
        if (left >= 1)
        {
            putByte(app, to, byte(app, from));
            from += 1, to += 1, left -= 1;
        }
    }
    cpu.eax = to;
    cpu.edx = from;
    cpu.ebx = left;
}

}  // namespace

/* 0x5033e5: the memmove's forward copy, eax to, edx from, ebx bytes. */
void copy(win32::WinApplication* app, x86::CPU& cpu)
{
    copyForward(app, cpu);
    cpu.esp += 4;
}

/* 0x5033e4: the same, eax from and edx to (xchg first). */
void copySwapped(win32::WinApplication* app, x86::CPU& cpu)
{
    std::swap(cpu.eax, cpu.edx);
    copyForward(app, cpu);
    cpu.esp += 4;
}

}  // namespace mmx
}  // namespace nfs3hp
