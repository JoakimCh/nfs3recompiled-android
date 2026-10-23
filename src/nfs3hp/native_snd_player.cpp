#include "native_snd.h"

/* A player's own car's sound, native (native_snd.cpp says how): its engine
 * (0x417390), its knocks and scrapes as its collision list has them, the
 * engine's warning (effect 5 of the car's bank) going downhill backwards
 * now and then, the cop's siren and radio for a cop's car, or the horn's
 * noise -- each from the car's place, distance and angle.  The x87 as the
 * game's code has it. */
namespace nfs3hp
{
namespace snd
{

namespace
{

constexpr reg32 kListener = 0x570a78;

x86::Float f32(App* app, reg32 at) { return x86::Float(app->getMemory<float>(at)); }
x86::Float f64(App* app, reg32 at) { return x86::Float(app->getMemory<double>(at)); }

/* fild word of a byte of the track's cell table (0x5dd948's, 0x24 a cell)
 * at `field`, as the code builds it: eax's low word the byte widened. */
void cellByte(App* app, CPU& cpu, reg32 cellIndex, reg32 field, reg32 to)
{
    cpu.eax = cellIndex * 9;
    const reg16 v = reg16(i16(i8(byte(app, cpu.edx + cpu.eax * 4 + field))));
    cpu.eax = (cpu.eax & 0xffff0000) | v;
    put(app, cpu.ebp - 4, cpu.eax);
    app->getMemory<float>(to) = float(x86::Float(x86::sreg32(i16(v))));
}

}  // namespace

/* 0x4117a0: player eax's car's sounds, from its source (0x570ad8's). */
void playerCarSound(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    x86::FPU& fpu = cpu.fpu;
    const unsigned pushed = kEbx | kEcx | kEdx | kEsi | kEdi;
    cpu.ebp = kept.frame(6);
    cpu.esp = cpu.ebp - 0x40;
    const reg32 b = cpu.ebp, place = b - 0x34, up = b - 0x40;
    put(app, b - 0x18, cpu.eax);
    put(app, b - 0x20, kListener);
    cpu.edx = cpu.eax;
    cpu.eax = (((cpu.eax << 2) + cpu.edx) << 4) + 0x570ad8 + 0x18;
    cpu.esi = at(app, cpu.eax);
    put(app, b - 0x14, cpu.eax);
    if (cpu.esi == 0)
        return leave(cpu, kept, pushed);
    put(app, place, at(app, cpu.esi + 0x98));
    put(app, place + 4, at(app, cpu.esi + 0x9c));
    cpu.eax = at(app, cpu.esi + 0xa0);
    put(app, place + 8, cpu.eax);
    // The cell's up, and how much of it the car's own has: downhill below 0.
    cpu.edx = at(app, 0x5dd948);
    cellByte(app, cpu, at(app, cpu.esi + 0x1c), 0x14, up);
    cpu.ecx = at(app, cpu.esi + 0x1c);
    cellByte(app, cpu, cpu.ecx, 0x15, up + 4);
    cpu.ecx = at(app, cpu.esi + 0x1c);
    cellByte(app, cpu, cpu.ecx, 0x16, up + 8);
    cpu.edx = up;
    cpu.eax = cpu.esi + 0xd8;
    if (!call(app, cpu, 0x4e01f0))
        return;
    cpu.ecx = at(app, 0x6fd4c0);
    app->getMemory<float>(b - 0x24) = float(fpu.st(0));
    fpu.pop();
    if (cpu.ecx != 0)
        putByte(app, b - 0x21, byte(app, b - 0x21) ^ 0x80);
    bool reset = (byte(app, cpu.esi + 0x200) & 1) != 0 && at(app, cpu.esi + 0x2c4) == 3;
    if (!reset)
    {
        // fldz; fcomp; fnstsw; sahf; jbe: on unless 0 is above it.
        const Compared c = fcomp(cpu, x86::Float(0.0), f32(app, b - 0x24));
        reset = c.below || c.equal;
        if (!reset && half(app, cpu.esi + 0x164) == 0 && at(app, cpu.esi + 0x8d4) == 0
            && (byte(app, cpu.esi + 0x200) & 0x20) == 0)
        {
            cpu.eax = at(app, cpu.esi + 0x998) + 1;
            put(app, cpu.esi + 0x998, cpu.eax);
            if (i32(cpu.eax) >= 0x40 && i32(cpu.eax) < 0x94 && (byte(app, cpu.esi + 0x998) & 0x1f) == 0
                && !call(app, cpu, 0x418280))
                return;
        }
    }
    if (reset)
        put(app, cpu.esi + 0x998, 0);
    cpu.eax = place;
    cpu.edx = cpu.esi + 0xa4;
    if (!call(app, cpu, 0x4124d0))
        return;
    cpu.ebx = at(app, 0x6fd3b0);
    put(app, b - 0x1c, cpu.eax);
    if (cpu.ebx == 1)
        put(app, b - 0x10, at(app, b - 0x18) != 0 ? 0xc000 : 0x3fff);
    else
    {
        cpu.eax = at(app, b - 0x18) << 2;
        cpu.edx = at(app, cpu.eax + 0x5e10b8);
        if (cpu.edx != 0)
            cpu.eax = at(app, cpu.edx);
        else
        {
            cpu.ebx = at(app, cpu.eax + 0x5e10b0);
            cpu.eax = cpu.ebx != 0 ? at(app, cpu.ebx) : 0;
        }
        if (cpu.eax == 2)
        {
            cpu.edi = 0;
            put(app, b - 0x10, cpu.edi);
        }
        else
        {
            cpu.edx = place;
            cpu.eax = at(app, b - 0x20);
            if (!call(app, cpu, 0x410d30))
                return;
            put(app, b - 0x10, cpu.eax);
        }
    }
    cpu.edx = place;
    cpu.eax = at(app, b - 0x20);
    if (!call(app, cpu, 0x410cb0))
        return;
    cpu.edx = cpu.eax;
    towardZero(cpu, 16);
    cpu.edi = reg32(mul(i32(cpu.eax), i32(cpu.eax)));
    cpu.eax = at(app, cpu.esi + 0x220);
    cpu.edx = at(app, cpu.eax + 0x1c);
    cpu.eax = at(app, cpu.esi + 0x528);
    cpu.ecx = at(app, cpu.eax + 0x1c4) + (cpu.edx == 1 ? 0x3e8 : 0x7d0);
    if (half(app, cpu.esi + 0x164) > 5)
        cpu.ecx -= 0x1f4;
    cpu.edx = at(app, cpu.esi + 0x590);
    cpu.eax = (cpu.edx << 7) - cpu.edx;
    idiv(cpu, cpu.ecx);
    cpu.ebx = cpu.eax;
    cpu.edx = cpu.esi;
    cpu.eax = at(app, b - 0x20);
    if (!call(app, cpu, 0x410dc0))
        return;
    const reg32 angle = cpu.eax;
    cpu.ecx = at(app, b - 0x10);
    cpu.edx = cpu.edi;
    cpu.eax = cpu.esi;
    const reg32 pan = cpu.ecx;
    cpu.ecx = at(app, b - 0x1c);
    if (!call(app, cpu, 0x417390, {pan, angle}))
        return;
    // The car's knocks and scrapes: 24 bytes each from +0x7e0.
    cpu.ebx = 0;
    put(app, b - 8, cpu.ebx);
    for (; cpu.eax = at(app, b - 8), i32(cpu.eax) < s32(app, cpu.esi + 0x7dc); put(app, b - 8, at(app, b - 8) + 1))
    {
        const reg32 k = at(app, b - 8), entry = cpu.esi + k * 24;
        cpu.eax = k;
        cpu.edx = k;
        cpu.eax = entry;
        cpu.ecx = at(app, entry + 0x7e4);
        const bool second = at(app, b - 0x18) != 0;
        if (cpu.ecx == 8)
            cpu.eax = second ? 9 : cpu.ecx;
        else if (cpu.ecx == 0xa)
            cpu.eax = second ? 0xb : 0xa;
        if (cpu.ecx == 8 || cpu.ecx == 0xa)
            put(app, b - 0xc, cpu.eax);
        else
            put(app, b - 0xc, cpu.ecx);
        cpu.edx = k;
        cpu.eax = entry;
        cpu.ebx = at(app, entry + 0x7e0);
        const reg32 slot = at(app, b - 0xc);
        if ((cpu.ebx == 5 || cpu.ebx == 3) && i32(slot) > -1)
        {
            cpu.ecx = slot;
            cpu.eax = cpu.ecx;
            if (!call(app, cpu, 0x416f60))
                return;
            continue;
        }
        if (i32(slot) < 0 && at(app, 0x6fd3b0) != 1)
        {
            cpu.eax = at(app, b - 0x20);
            cpu.edx = cpu.esi + 0x178;
            if (!call(app, cpu, 0x410d30))
                return;
            const reg32 crashAngle = cpu.eax;
            cpu.edx = at(app, b - 8);
            cpu.eax = cpu.edx * 24;
            cpu.edx = cpu.esi + cpu.eax;
            cpu.eax = slot;
            put(app, b - 0x28, cpu.edx);
            cpu.ecx = at(app, cpu.edx + 0x7f0);
            cpu.ebx = at(app, cpu.edx + 0x7ec);
            cpu.edx = at(app, cpu.edx + 0x7e8);
            if (!call(app, cpu, 0x416d90, {cpu.edi, crashAngle}))
                return;
            cpu.eax = at(app, b - 0x28);
            cpu.edx = at(app, cpu.eax + 0x7f0);
            cpu.eax = (cpu.edx << 7) - cpu.edx;
            cpu.ecx = 0xa0000;
            idiv(cpu, 0xa0000);
            if (i32(cpu.eax) > 0x7f)
                cpu.eax = 0x7f;
            cpu.ecx = cpu.eax;
            if (i32(cpu.eax) > 0x7d)
            {
                cpu.edx = at(app, b - 8);
                cpu.eax = cpu.edx * 3;
                if (at(app, cpu.esi + cpu.eax * 8 + 0x7e8) != 6 && !call(app, cpu, 0x418c60))
                    return;
            }
            if (!call(app, cpu, 0x42d510, {0x64, 1, 0x536940, cpu.ecx}))
                return;
            continue;
        }
        cpu.edx = at(app, b - 8);
        cpu.ecx = at(app, b - 0x10);
        cpu.eax = cpu.edx * 3;
        const reg32 knockPan = cpu.ecx;
        cpu.ecx = at(app, cpu.esi + cpu.eax * 8 + 0x7f0);
        cpu.ebx = at(app, cpu.esi + cpu.eax * 8 + 0x7ec);
        cpu.edx = at(app, cpu.esi + cpu.eax * 8 + 0x7e8);
        cpu.eax = slot;
        if (!call(app, cpu, 0x416d90, {cpu.edi, knockPan}))
            return;
    }
    setByte1(cpu.ebx, byte(app, 0x6fd4fc));
    if ((byte(app, 0x6fd4fc) & 1) != 0)
        return leave(cpu, kept, pushed);
    if ((byte(app, cpu.esi + 0x200) & 0x20) != 0)
    {
        // A cop's car: its siren, and its radio.
        cpu.eax = at(app, 0x6fd3b0) == 1 ? at(app, cpu.esi + 0x1f0) + 2 : 4;
        if ((byte(app, cpu.esi + 0x710) & 0x10) != 0)
        {
            cpu.ebx = at(app, b - 0x1c);
            cpu.edx = at(app, b - 0x10);
            cpu.ecx = cpu.edi;
            if (!call(app, cpu, 0x411c50))
                return;
            cpu.eax = at(app, b - 0x14);
            put(app, cpu.eax + 0x20, 1);
        }
        else
        {
            cpu.edx = at(app, b - 0x14);
            if (at(app, cpu.edx + 0x20) != 0)
            {
                if (!call(app, cpu, 0x411ca0))
                    return;
                put(app, cpu.edx + 0x20, 0);
            }
        }
        cpu.ebx = at(app, b - 0x18);
        cpu.edx = at(app, b - 0x10);
        cpu.ecx = cpu.edi;
        const reg32 player = cpu.ebx;
        cpu.eax = cpu.esi;
        cpu.ebx = at(app, b - 0x1c);
        if (!call(app, cpu, 0x4c8810, {player}))
            return;
        return leave(cpu, kept, pushed);
    }
    if (byte(app, cpu.esi + 0x50e) != 0)
    {
        cpu.edx = at(app, b - 0x1c) << 6;
        towardZero(cpu, 16);
        cpu.ecx = at(app, b - 0x10);
        cpu.esi = at(app, cpu.esi + 0x1f0);
        cpu.ebx = cpu.eax;
        cpu.edx = cpu.edi;
        cpu.eax = cpu.esi;
        if (!call(app, cpu, 0x417c00))
            return;
        cpu.eax = at(app, b - 0x14);
        put(app, cpu.eax + 0x20, 1);
        return leave(cpu, kept, pushed);
    }
    cpu.eax = at(app, b - 0x14);
    if (at(app, cpu.eax + 0x20) != 0)
    {
        cpu.eax = at(app, cpu.esi + 0x1f0);
        if (!call(app, cpu, 0x417c70))
            return;
        cpu.eax = at(app, b - 0x14);
        put(app, cpu.eax + 0x20, 0);
    }
    leave(cpu, kept, pushed);
}

/* 0x417390 (stdcall 8): car eax's engine -- at distance edx, throttle ebx
 * times ecx (16.16), pan [esp+4], angle [esp+8]: the radio (0x4c8d10), the
 * cop chase (0x412d60) and the cars about (0x415210) first, the far-off
 * effect's tick; then its revs (+0x4f4) as the three engine sounds' (in
 * slots 0, 1 and 9, the second player's 2, 3 and 10) volume, pitch and pan
 * -- louder in a tunnel (the bus on), the gear change's effect now and
 * then. */
void carEngine(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    x86::FPU& fpu = cpu.fpu;
    const unsigned pushed = kEsi | kEdi;
    cpu.ebp = kept.frame(3);
    cpu.esp = cpu.ebp - 0x40;
    const reg32 b = cpu.ebp;
    cpu.esi = cpu.eax;
    put(app, b - 0x14, cpu.edx);
    put(app, b - 0x30, cpu.ebx);
    cpu.edx = at(app, b + 0x14);
    cpu.edi = at(app, 0x6fd3b0);
    setByte0(cpu.ebx, byte(app, cpu.eax + 0x1f0));
    cpu.eax = cpu.edi == 1 ? reg32(reg8(cpu.ebx)) : 0;
    if (!call(app, cpu, 0x4c8d10))
        return;
    cpu.eax = cpu.esi;
    if (!call(app, cpu, 0x412d60))
        return;
    cpu.eax = cpu.esi;
    if (!call(app, cpu, 0x415210))
        return;
    if ((at(app, 0x6fd3b0) != 1 || reg8(cpu.ebx) == 0) && !call(app, cpu, 0x414f60))
        return;
    if (at(app, 0x55290c) == 0)
        return leave(cpu, kept, pushed, 8);
    cpu.edi = at(app, b - 0x14);
    if (i32(cpu.edi) < 0x15f9)
    {
        cpu.edx = 0x15f9 - cpu.edi;
        cpu.eax = (cpu.edx << 7) - cpu.edx;
        cpu.edx = cpu.eax;
        cpu.ebx = 0x15f9;
        idiv(cpu, 0x15f9);
        put(app, b - 0x28, cpu.eax);
    }
    else
    {
        cpu.edx = 0;
        put(app, b - 0x28, cpu.edx);
    }
    // The revs: fld; __CHP; fistp.
    fpu.push(f32(app, cpu.esi + 0x4f4));
    if (!call(app, cpu, kChop))
        return;
    put(app, b - 0x24, reg32(fpu.toInteger<i32>(fpu.st(0))));
    fpu.pop();
    cpu.ebx = at(app, b - 0x24);
    cpu.eax = i32(cpu.ebx) > 0 ? cpu.ebx : 0u - cpu.ebx;
    cpu.edi = cpu.eax + cpu.eax;
    put(app, b - 0x20, cpu.edi);
    if (i32(cpu.edi) > 0x7f)
        put(app, b - 0x20, 0x7f);
    cpu.edx = at(app, b - 0x20);
    towardZero(cpu, 4);
    cpu.edx = cpu.eax;
    cpu.eax = 8 - cpu.edx;
    put(app, b - 0xc, cpu.eax);
    if (i32(cpu.eax) < 3)
        put(app, b - 0xc, 3);
    put(app, b - 0x10, 0x40);
    cpu.edx = reg32(mul(s32(app, b - 0x30), i32(cpu.ecx)));
    towardZero(cpu, 16);
    put(app, b - 8, cpu.eax);
    if (i32(cpu.eax) > 0x64)
        put(app, b - 8, 0x64);
    else if (i32(cpu.eax) < 0)
    {
        cpu.edx = 0;
        put(app, b - 8, cpu.edx);
    }
    // In a tunnel (0x420bf0's, of the car's place and cell): the bus up.
    cpu.eax = at(app, cpu.esi + 0x98);
    cpu.ecx = at(app, cpu.esi + 0x1c);
    put(app, b - 0x40, cpu.eax);
    cpu.eax = at(app, cpu.esi + 0x9c);
    put(app, b - 0x3c, cpu.eax);
    cpu.eax = at(app, cpu.esi + 0xa0);
    const reg32 z = cpu.eax, cell = cpu.ecx;
    put(app, b - 0x38, cpu.eax);
    cpu.eax = at(app, b - 0x3c);
    cpu.edx = at(app, b - 0x40);
    if (!call(app, cpu, 0x420bf0, {cpu.edx, cpu.eax, z, cell}))
        return;
    if (cpu.eax != 0)
    {
        if (byte(app, 0x552930) == 0 && at(app, 0x6fd3b0) != 1)
        {
            setByte0(cpu.edx, 1);
            if (!call(app, cpu, 0x418770))
                return;
            putByte(app, 0x552930, reg8(cpu.edx));
        }
        cpu.ebx = 0x5e;
        cpu.edi += 0x14;
        put(app, b - 0x10, cpu.ebx);
    }
    else if (byte(app, 0x552930) != 0 && at(app, 0x6fd3b0) != 1)
    {
        setByte0(cpu.ebx, 0);
        if (!call(app, cpu, 0x418790))
            return;
        putByte(app, 0x552930, reg8(cpu.ebx));
    }
    if (at(app, 0x6fd3b0) == 1)
    {
        setByte1(cpu.ebx, 1);
        cpu.ecx = at(app, cpu.esi + 0x1f0);
        putByte(app, b - 4, 1);
        cpu.eax = cpu.ecx != 0 ? 0xc000 : 0x3fff;
        cpu.ebx = at(app, cpu.esi + 0x1f0);
        put(app, b - 0x2c, cpu.eax);
    }
    else
    {
        setByte0(cpu.ecx, 0);
        putByte(app, b - 4, 0);
    }
    // The ground's kind (0x420840's, else the car's +0x18c): some lower the
    // pitch, some (now and then) the gear change's effect.
    cpu.edx = at(app, cpu.esi + 0x7c);
    cpu.eax = at(app, cpu.esi + 0x1c);
    if (!call(app, cpu, 0x420840))
        return;
    cpu.ecx = cpu.eax;
    if (cpu.eax == 0)
        cpu.ecx = at(app, cpu.esi + 0x18c);
    cpu.eax = cpu.ecx - 2;
    const reg32 ground = cpu.eax;
    const bool lower = ground <= 0xf && (ground == 0 || ground == 8 || ground == 9 || ground == 0xa || ground == 0xb);
    const bool gearKind = ground <= 0xf && (ground == 5 || ground == 0xa || ground == 0xe || ground == 0xf);
    if (lower)
    {
        cpu.edx = cpu.edi;
        cpu.eax = cpu.edi;
        towardZero(cpu, 2);
        cpu.edi += cpu.eax;
        put(app, b - 0x10, 0x18);
        if (ground == 0xa)
            cpu.edx = 0x18;
    }
    // The gear change's effect, by the revs' counter (0x552d8c).
    auto gearChange = [&](reg32 pitch, reg32 volume) {
        cpu.ebx = byte(app, b - 4) != 0 ? at(app, b - 0x2c) : 0;
        cpu.edx = at(app, 0x57113c);
        cpu.ecx = volume;
        put(app, b - 0x34, cpu.edx);
        cpu.edx = 0x1d;
        cpu.eax = at(app, b - 0x34);
        return call(app, cpu, 0x4182b0, {pitch});
    };
    if (gearKind)
    {
        setByte0(cpu.eax, reg8(byte(app, 0x552d8c) + 1));
        cpu.edx = 0;
        cpu.ebx = at(app, b - 0xc);
        setByte0(cpu.edx, reg8(cpu.eax));
        putByte(app, 0x552d8c, reg8(cpu.eax));
        cpu.eax = cpu.edx;
        idiv(cpu, cpu.ebx);
        putByte(app, 0x552d8c, reg8(cpu.edx));
        if (reg8(cpu.edx) == 0 && s32(app, cpu.esi + 0x15c) < 0x3e4ccccd && at(app, 0x6fd4ac) != 8)
        {
            const reg32 pitch = cpu.ecx == 7 || cpu.ecx == 0xc ? 0x28 : 0x40;
            cpu.eax = pitch;
            cpu.eax = at(app, b - 0x20);
            halve(cpu);
            if (!gearChange(pitch, cpu.eax))
                return;
        }
    }
    // Going fast off the ground: the effect too.
    auto above = [&](reg32 at, reg32 limit) {
        const Compared c = fcomp(cpu, f32(app, at), f64(app, limit));
        return !(c.below || c.equal);
    };
    if (at(app, cpu.esi + 0x99c) != 0 && half(app, cpu.esi + 0x164) == 0 && above(cpu.esi + 0x10c, 0x536bb0)
        && above(cpu.esi + 0xb8, 0x536bb8))
    {
        putByte(app, 0x552d8c, reg8(byte(app, 0x552d8c) + 1));
        cpu.edx = byte(app, 0x552d8c);
        cpu.ebx = at(app, b - 0xc);
        cpu.eax = cpu.edx;
        idiv(cpu, cpu.ebx);
        putByte(app, 0x552d8c, reg8(cpu.edx));
        if (reg8(cpu.edx) == 0 && s32(app, cpu.esi + 0x15c) < 0x3e4ccccd)
        {
            setByte1(cpu.ebx, byte(app, b - 4));
            if (!gearChange(0x40, at(app, b - 0x20)))
                return;
        }
    }
    if (s32(app, b - 0x14) > 4)
    {
        cpu.edx = ((cpu.edi << 2) - cpu.edi) * 2;
        cpu.ecx = 0xa;
        cpu.eax = cpu.edx;
        idiv(cpu, 0xa);
        cpu.edi = cpu.eax;
    }
    cpu.ecx = at(app, b - 0x14);
    if (i32(cpu.ecx) < 4)
        put(app, b - 0x18, 0x41);
    else if (i32(cpu.ecx) < 0x23)
        put(app, b - 0x18, 0xc);
    else
    {
        cpu.ecx = 0;
        put(app, b - 0x18, cpu.ecx);
    }
    if (i32(cpu.edi) > 0x7f)
        cpu.edi = 0x7f;
    // The load: the revs eased towards the car's (+0x508), the three
    // sounds' share of it (0x552a38's curve).
    cpu.ecx = at(app, cpu.esi + 0x1f0) << 2;
    cpu.edx = byte(app, cpu.esi + 0x508);
    cpu.ebx = at(app, cpu.ecx + 0x571078);
    cpu.edx -= cpu.ebx;
    cpu.eax = cpu.edx;
    if (i32(byte(app, cpu.esi + 0x508)) >= i32(cpu.ebx))
        halve(cpu);
    else
        towardZero(cpu, 3);
    cpu.edx = cpu.ebx + cpu.eax;
    put(app, cpu.ecx + 0x571078, cpu.edx);
    cpu.eax = at(app, at(app, cpu.esi + 0x1f0) * 4 + 0x571078);
    if (i32(cpu.eax) > 0xff)
        cpu.eax = 0xff;
    cpu.eax = reg32(i32(cpu.eax) >> 1);
    cpu.edx = byte(app, cpu.eax + 0x552a38);
    cpu.ebx = 0x80 - cpu.eax;
    put(app, b - 0x1c, cpu.edx);
    setByte0(cpu.ebx, byte(app, cpu.ebx + 0x552a38));
    cpu.edx = at(app, b - 8);
    cpu.ecx = at(app, b - 0x28);
    cpu.edx = reg32(mul(i32(cpu.edx + 0x28), i32(cpu.ecx)));
    towardZero(cpu, 7);
    cpu.ebx &= 0xff;
    if (i32(cpu.eax) > 0x7f)
        cpu.eax = 0x7f;
    if (i32(cpu.eax) < 0)
        cpu.eax = 0;
    cpu.ebx = reg32(mul(i32(cpu.ebx), i32(cpu.eax)));
    cpu.edi = reg32(mul(i32(cpu.edi), i32(cpu.eax)));
    cpu.edx = reg32(mul(s32(app, b - 0x1c), i32(cpu.eax)));
    cpu.ebx = reg32(i32(cpu.ebx) >> 7);
    cpu.edi = reg32(i32(cpu.edi) >> 7);
    cpu.edx = reg32(i32(cpu.edx) >> 7);
    cpu.eax = at(app, 0x6fd3a0);
    put(app, b - 0x1c, cpu.edx);
    if (i32(cpu.eax) >= 2)
    {
        cpu.edx = at(app, b + 0x10);
        cpu.ecx = stereoPan(cpu.edx);
    }
    else
        cpu.ecx = 0x40;
    if (at(app, 0x6fd3b0) == 1)
    {
        if (at(app, 0x55292c) == 0)
            cpu.ecx = 0x40;
        else
            cpu.ecx = at(app, cpu.esi + 0x1f0) != 0 ? 0 : 0x7f;
    }
    const bool second = at(app, 0x6fd3b0) == 1 && at(app, cpu.esi + 0x1f0) != 0;
    const reg32 first = second ? 0x570e50 : 0x570e48, low = second ? 0x570df0 : 0x570de8,
                third = second ? 0x570e00 : 0x570df8;
    // The three sounds: their volume, pitch and pan.
    cpu.edx = at(app, 0x6fbbf8);
    cpu.eax = ((cpu.edx << 2) - cpu.edx) << 3;
    cpu.edx = (cpu.edx + cpu.eax) * 2;
    cpu.edx = reg32(mul(i32(cpu.edx), i32(cpu.edi)));
    cpu.eax = at(app, first);
    cpu.edx = reg32(i32(cpu.edx) >> 14);
    if (!call(app, cpu, 0x4e95fc))
        return;
    cpu.edx = at(app, b - 0x10);
    cpu.eax = at(app, first);
    cpu.esi = at(app, b - 0x18);
    if (!call(app, cpu, 0x4e97e4))
        return;
    cpu.eax = at(app, first);
    cpu.edx = cpu.ecx;
    cpu.esi += 0x32;
    if (!call(app, cpu, 0x4e9950))
        return;
    if (second)
    {
        cpu.edx = reg32(mul(mul(s32(app, 0x6fbbf8), i32(cpu.esi)), s32(app, b - 0x1c)));
    }
    else
    {
        cpu.eax = reg32(mul(s32(app, 0x6fbbf8), i32(cpu.esi)));
        cpu.edx = reg32(mul(s32(app, b - 0x1c), i32(cpu.eax)));
    }
    cpu.eax = at(app, low);
    cpu.edx = reg32(i32(cpu.edx) >> 14);
    if (!call(app, cpu, 0x4e95fc))
        return;
    cpu.edx = at(app, b - 8);
    cpu.eax = at(app, low);
    if (!call(app, cpu, 0x4e97e4))
        return;
    cpu.eax = at(app, low);
    cpu.edx = cpu.ecx;
    if (!call(app, cpu, 0x4e9950))
        return;
    cpu.edx = reg32(mul(mul(s32(app, 0x6fbbf8), i32(cpu.esi)), i32(cpu.ebx)));
    cpu.eax = at(app, third);
    cpu.edx = reg32(i32(cpu.edx) >> 14);
    if (!call(app, cpu, 0x4e95fc))
        return;
    cpu.edx = at(app, b - 8);
    cpu.eax = at(app, third);
    if (!call(app, cpu, 0x4e97e4))
        return;
    cpu.eax = at(app, third);
    cpu.edx = cpu.ecx;
    if (!call(app, cpu, 0x4e9950))
        return;
    leave(cpu, kept, pushed, 8);
}

}  // namespace snd
}  // namespace nfs3hp
