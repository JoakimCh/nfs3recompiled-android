#include "native_snd.h"

/* The tracks' own scenery sounds, native (native_snd.h says how): for the
 * player's car each tick, by the track (0x6fd4ac) and where on it the car
 * is (its cell, +0x1c) -- the rain and the tunnel's echo; a sound that
 * plays all along a stretch, swelling and fading at random (slot 0x1a, the
 * second player's 0x24); and now and then, at random, the scenery's
 * effects of the ambience bank (0x571148): birds, trains, bells, voices,
 * some repeating a few times over (0x570f70's, 0x1c bytes a player).  Each
 * the code's own way, the random numbers drawn in its order.
 *
 * The game's state, per player: 0x570de0 the rain on (a byte), 0x570f50
 * its sound, 0x570f48 in a stretch (a byte), 0x570f40 a zone's sound
 * playing (a byte), 0x570f20 the stretch's volume and 0x571050 where it
 * heads, 0x571120 and 0x57111c the stretch's pan and where it heads. */
namespace nfs3hp
{
namespace snd
{

namespace
{

constexpr reg32 kRandom = 0x4e0d88, kPlay = 0x4182b0, kSlotPlay = 0x417080, kSlotStop = 0x416f60;
constexpr reg32 kAmbience = 0x571148;

}  // namespace

/* 0x415210: car eax's scenery sounds, edx its heading (a pan's). */
void scenerySounds(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const unsigned pushed = kEbx | kEcx | kEsi | kEdi;
    cpu.ebp = kept.frame(5);
    cpu.esp = cpu.ebp - 0x44;
    const reg32 b = cpu.ebp;
    put(app, b - 8, cpu.eax);
    put(app, b - 0x14, cpu.edx);
    const reg32 car = at(app, b - 8);
    auto cell = [&] { return at(app, car + 0x1c); };
    auto player = [&] { return at(app, car + 0x1f0); };
    auto track = [&] { return at(app, 0x6fd4ac); };
    auto random = [&] { return call(app, cpu, kRandom); };
    // random() % by, as the code's div leaves it in edx.
    auto randomOf = [&](reg32 by, reg32& in) {
        in = by;
        cpu.edx = 0;
        if (!random())
            return false;
        udiv(cpu, by);
        return true;
    };
    auto done = [&] { leave(cpu, kept, pushed); };
    cpu.edx = at(app, 0x6fd4f8);
    if (cpu.edx != at(app, 0x6fd4f4))
    {
        if (call(app, cpu, 0x42d510, {0x64, 2, 0x536b98}))
            done();
        return;
    }
    // In a tunnel (0x420bf0's, of the car's place), the rain (the same with
    // the player's weather, 0x564288).
    put(app, b - 0x44, at(app, car + 0x98));
    put(app, b - 0x40, at(app, car + 0x9c));
    put(app, b - 0x3c, at(app, car + 0xa0));
    cpu.ecx = cell();
    cpu.ebx = at(app, b - 0x3c);
    cpu.esi = at(app, b - 0x40);
    cpu.edi = at(app, b - 0x44);
    if (!call(app, cpu, 0x420bf0, {cpu.edi, cpu.esi, cpu.ebx, cpu.ecx}))
        return;
    cpu.edi = cpu.eax;
    cpu.esi = at(app, 0x6fd3b0) == 1 ? player() : 0;
    cpu.ecx = cell();
    cpu.ebx = at(app, b - 0x3c);
    cpu.eax = at(app, b - 0x40);
    const reg32 y = cpu.eax;
    cpu.ecx = at(app, b - 0x44);
    cpu.edx = at(app, cpu.esi * 4 + 0x564288);
    if (!call(app, cpu, 0x420bf0, {cpu.ecx, y, cpu.ebx, cell()}))
        return;
    put(app, b - 0x20, cpu.eax);
    if (cpu.edx != 0)
    {
        if (i32(cpu.edx) > 0x64)
            cpu.edx = 0x64;
        const reg32 rain = at(app, cpu.esi * 4 + 0x564288);
        const reg8 on = byte(app, cpu.esi + 0x570de0);
        if (rain != 0 && on == 0)
        {
            if (at(app, 0x6fd3b0) == 1)
                cpu.ebx = cpu.esi != 0 ? 0xc000 : 0x3fff;
            else
                cpu.ebx = 0;
            cpu.eax = (cpu.edx << 7) - cpu.edx;
            cpu.edx = cpu.eax;
            cpu.ecx = 0x64;
            idiv(cpu, 0x64);
            cpu.edx = at(app, 0x571154);
            cpu.ecx = cpu.eax;
            put(app, b - 4, cpu.edx);
            cpu.edx = 4;
            cpu.eax = at(app, b - 4);
            if (!call(app, cpu, kPlay, {0x40}))
                return;
            setByte0(cpu.edx, 1);
            put(app, cpu.esi * 4 + 0x570f50, cpu.eax);
            putByte(app, cpu.esi + 0x570de0, 1);
        }
        else if (rain == 0 && on != 0)
        {
            cpu.eax = cpu.esi * 4;
            cpu.ebx = 0xffffffff;
            cpu.edx = 5;
            cpu.eax = at(app, cpu.eax + 0x570f50);
            if (!call(app, cpu, 0x4e9420))
                return;
            setByte1(cpu.ebx, 0);
            putByte(app, cpu.esi + 0x570de0, 0);
        }
        else
        {
            cpu.eax = cpu.esi * 4;
            cpu.ecx = cpu.esi * 4;
            if (rain != 0 && on != 0)
            {
                cpu.ebx = at(app, 0x6fbbf4);
                cpu.eax = cpu.ebx * 9;
                cpu.ebx = cpu.eax;
                cpu.eax = (cpu.eax << 3) - cpu.ebx;
                cpu.edx = reg32(mul(i32(cpu.edx), i32(cpu.eax)));
                cpu.ebx = 0x64;
                cpu.eax = cpu.edx;
                idiv(cpu, 0x64);
                cpu.edx = reg32(i32(cpu.eax) >> 7);
                cpu.eax = at(app, cpu.ecx + 0x570f50);
                if (!call(app, cpu, 0x4e95fc))
                    return;
            }
        }
        if (at(app, b - 0x20) != 0 || byte(app, 0x552909) == 0)
        {
            cpu.eax = at(app, cpu.esi * 4 + 0x570f50);
            cpu.edx = 0;
            if (!call(app, cpu, 0x4e95fc))
                return;
        }
    }
    // The stretch's slot; the player's side in the split screen.
    cpu.edx = at(app, 0x6fd3b0);
    if (cpu.edx == 1)
    {
        cpu.ebx = player();
        put(app, b - 0xc, cpu.edx);
        cpu.eax = cpu.ebx != 0 ? 0xc000 : 0x3fff;
        put(app, b - 0x10, cpu.eax);
        cpu.esi = player() != 0 ? 0x24 : 0x1a;
    }
    else
    {
        cpu.eax = 0;
        cpu.esi = 0x1a;
        put(app, b - 0xc, cpu.eax);
    }
    auto split = [&] { return at(app, b - 0xc) != 0; };
    // A stretch entered: its sound started (`effect`), the old zone's
    // stopped; `slowPan` the pan's target drawn as 9 bits rather than as a
    // division.
    auto stretchStart = [&](reg32 effect, int variant) {
        cpu.eax = player();
        setByte0(cpu.edx, byte(app, cpu.eax + 0x570f48));
        if (byte(app, cpu.eax + 0x570f40) != 0)
        {
            cpu.eax = cpu.esi;
            if (!call(app, cpu, kSlotStop))
                return false;
            cpu.eax = player();
            putByte(app, cpu.eax + 0x570f40, reg8(cpu.edx));
        }
        if (variant == 0)
        {
            cpu.eax = car;
            cpu.ecx = 0;
            cpu.eax = player();
            cpu.edx = 1;
            put(app, 0x571120, cpu.ecx);
            put(app, cpu.eax * 4 + 0x570f20, cpu.edx);
            if (!random())
                return false;
            cpu.edx = cpu.eax;
            cpu.eax = player();
            cpu.edx &= 0x7f;
            cpu.ecx = 0xffff;
            put(app, cpu.eax * 4 + 0x571050, cpu.edx);
        }
        else
        {
            cpu.eax = player();
            cpu.edx = 1;
            cpu.ecx = 0;
            put(app, cpu.eax * 4 + 0x570f20, cpu.edx);
            cpu.edx = car;
            put(app, 0x571120, cpu.ecx);
            if (!random())
                return false;
            cpu.edx = at(app, cpu.edx + 0x1f0);
            cpu.eax &= 0x7f;
            if (variant != 2)
                cpu.ecx = 0xffff;
            put(app, cpu.edx * 4 + 0x571050, cpu.eax);
        }
        if (variant == 2)
        {
            if (!random())
                return false;
            cpu.eax &= 0x1ff;
            cpu.ebx = at(app, b - 0xc);
            put(app, 0x57111c, cpu.eax);
        }
        else
        {
            cpu.edx = 0;
            if (!random())
                return false;
            udiv(cpu, cpu.ecx);
            cpu.ebx = at(app, b - 0xc);
            put(app, 0x57111c, cpu.edx);
        }
        cpu.eax = cpu.ebx != 0 ? at(app, b - 0x10) : at(app, 0x571120);
        const reg32 pan = cpu.eax;
        cpu.eax = player();
        cpu.ebx = at(app, cpu.eax * 4 + 0x570f20);
        cpu.edx = effect;
        cpu.ecx = cpu.ebx;
        cpu.eax = cpu.esi;
        if (!call(app, cpu, kSlotPlay, {pan}))
            return false;
        cpu.eax = player();
        putByte(app, cpu.eax + 0x570f48, 1);
        return true;
    };
    // Out of every stretch of the track: no longer in one.
    auto stretchLeft = [&] {
        cpu.eax = player();
        if (byte(app, cpu.eax + 0x570f48) != 0)
        {
            setByte1(cpu.ecx, 0);
            putByte(app, cpu.eax + 0x570f48, 0);
        }
    };
    // One stretch of a track: from lo to hi, its effect.
    auto stretch = [&](reg32 lo, reg32 hi, reg32 forTrack, reg32 effect, int variant) {
        cpu.eax = car;
        cpu.edx = cell();
        const bool in = i32(cpu.edx) >= i32(lo) && i32(cpu.edx) <= i32(hi);
        if (in && track() == forTrack && byte(app, player() + 0x570f48) == 0)
            return stretchStart(effect, variant);
        if (!in && track() == forTrack)
            stretchLeft();
        return true;
    };
    if (!stretch(0x26c, 0x3a0, 8, 8, 0) || !stretch(0x28c, 0x3b1, 3, 6, 1) || !stretch(0x28a, 0x3ca, 7, 6, 2))
        return;
    if (track() == 4)
    {
        const i32 c = i32(cell());
        const bool in = (c >= 0x2c6 && c <= 0x2e4) || (c >= 0x34c && c <= 0x35a) || (c >= 0x3b2 && c <= 0x3d8);
        if (in)
        {
            if (byte(app, player() + 0x570f48) == 0 && !stretchStart(3, 1))
                return;
        }
        else
            stretchLeft();
    }
    // The stretch's sound: swelling and fading, its pan drifting; faded out
    // in a tunnel; else the zones' sounds (0x415050).
    cpu.eax = player();
    if (byte(app, cpu.eax + 0x570f48) != 0)
    {
        cpu.eax = track();
        cpu.edx = cpu.eax == 3 || cpu.eax == 7 ? 6 : cpu.eax == 4 ? 3 : 8;
        if (cpu.edi != 0)
        {
            cpu.edx = 0x32;
            cpu.eax = at(app, cpu.esi * 8 + 0x570de8);
            cpu.ebx = 0;
            if (!call(app, cpu, 0x4e9420))
                return;
            cpu.eax = player();
            cpu.ebx = 0;
            put(app, cpu.eax * 4 + 0x570f20, cpu.ebx);
            cpu.eax = player();
            put(app, cpu.eax * 4 + 0x571050, cpu.ebx);
        }
        else
        {
            cpu.eax = player();
            cpu.ecx = at(app, cpu.eax * 4 + 0x570f20);
            if (cpu.ecx == at(app, cpu.eax * 4 + 0x571050))
            {
                if (!random())
                    return;
                cpu.edx = cpu.eax;
                cpu.eax = player();
                cpu.edx &= 0x7f;
                put(app, cpu.eax * 4 + 0x571050, cpu.edx);
            }
            else
            {
                cpu.ecx = at(app, 0x57111c);
                cpu.eax = at(app, 0x571120);
                if (cpu.eax == cpu.ecx)
                {
                    if (!random())
                        return;
                    cpu.eax &= 0x1ff;
                    put(app, 0x57111c, cpu.eax);
                }
                else
                {
                    if (i32(cpu.eax) < i32(cpu.ecx))
                    {
                        ++cpu.eax;
                        put(app, 0x571120, cpu.eax);
                    }
                    else
                    {
                        cpu.ecx = cpu.eax - 1;
                        put(app, 0x571120, cpu.ecx);
                    }
                    cpu.ebx = at(app, 0x571120);
                    if (i32(cpu.ebx) < 0)
                    {
                        cpu.eax = 0;
                        put(app, 0x571120, cpu.eax);
                    }
                    else if (i32(cpu.ebx) > 0x1ff)
                        put(app, 0x571120, 0x1ff);
                }
                cpu.eax = player() << 2;
                cpu.ecx = at(app, cpu.eax + 0x570f20);
                if (i32(cpu.ecx) < s32(app, cpu.eax + 0x571050))
                    put(app, cpu.eax + 0x570f20, cpu.ecx + 1);
                else
                {
                    cpu.ebx = cpu.ecx - 1;
                    put(app, cpu.eax + 0x570f20, cpu.ebx);
                }
                cpu.eax = split() ? at(app, b - 0x10) : at(app, 0x571120) << 7;
                const reg32 pan = cpu.eax;
                cpu.eax = player();
                cpu.ebx = at(app, cpu.eax * 4 + 0x570f20);
                cpu.ecx = cpu.ebx;
                cpu.eax = cpu.esi;
                if (!call(app, cpu, kSlotPlay, {pan}))
                    return;
            }
        }
    }
    else if (at(app, cpu.eax * 4 + 0x570f20) != 0)
    {
        cpu.ecx = track();
        cpu.edx = cpu.ecx == 3 || cpu.ecx == 7 ? 6 : cpu.ecx == 4 ? 3 : 8;
        cpu.eax = player();
        cpu.ecx = at(app, cpu.eax * 4 + 0x570f20) - 1;
        cpu.ebx = at(app, b - 0xc);
        put(app, cpu.eax * 4 + 0x570f20, cpu.ecx);
        cpu.eax = cpu.ebx != 0 ? at(app, b - 0x10) : at(app, 0x571120);
        const reg32 pan = cpu.eax;
        cpu.eax = player();
        cpu.ebx = at(app, cpu.eax * 4 + 0x570f20);
        cpu.ecx = cpu.ebx;
        cpu.eax = cpu.esi;
        if (!call(app, cpu, kSlotPlay, {pan}))
            return;
    }
    else
    {
        cpu.eax = track();
        cpu.ebx = at(app, b - 0x14);
        cpu.edx = car;
        cpu.ecx = at(app, cpu.eax * 4 + 0x552d54);
        cpu.eax = cpu.esi;
        if (!call(app, cpu, 0x415050))
            return;
        if (cpu.eax != 0)
            putByte(app, player() + 0x570f40, 1);
        else if (byte(app, player() + 0x570f40) != 0)
        {
            cpu.eax = cpu.esi;
            if (!call(app, cpu, kSlotStop))
                return;
            cpu.eax = player();
            setByte1(cpu.ebx, 0);
            putByte(app, cpu.eax + 0x570f40, 0);
        }
    }
    // The scenery's effects, now and then.
    reg32 by;
    // The pan as most of them draw it: the side, or random % 0xffff into
    // ebx (through edx).
    auto randomPan = [&](bool viaEbx) {
        if (split())
        {
            cpu.edx = at(app, b - 0x10);
            return true;
        }
        cpu.ebx = 0xffff;
        if (viaEbx)
            cpu.edx = 0;
        if (!random())
            return false;
        udiv(cpu, cpu.ebx);
        return true;
    };
    // The pan as others draw it: a quarter turn at random, either side of
    // the heading (the mirror turning it), into ebx.
    auto sidePan = [&](bool mirrorFirst, bool viaEax) {
        if (split())
        {
            cpu.ebx = at(app, b - 0x10);
            return true;
        }
        const bool mirror = at(app, 0x6fd4c4) != 0;
        const reg32 add = mirror == mirrorFirst ? 0xc000 : 0x2000;
        if (!random())
            return false;
        if (viaEax)
        {
            cpu.eax &= 0x3fff;
            cpu.ebx = at(app, b - 0x14);
            cpu.eax += add;
            cpu.ebx += cpu.eax;
        }
        else
        {
            cpu.ebx = cpu.eax & 0x3fff;
            cpu.ebx += add;
            cpu.ebx += at(app, b - 0x14);
        }
        cpu.ebx &= 0xffff;
        return true;
    };
    // The pan fixed by the side: the heading and a quarter.
    auto fixedPan = [&](bool mirrorFirst) {
        if (split())
        {
            cpu.ebx = at(app, b - 0x10);
            return;
        }
        const bool mirror = at(app, 0x6fd4c4) != 0;
        cpu.ebx = at(app, b - 0x14) + (mirror == mirrorFirst ? 0xc000 : 0x3fff);
        cpu.ebx &= 0xffff;
    };
    auto play = [&](reg32 effect, reg32 pitch) {
        cpu.eax = at(app, kAmbience);
        cpu.edx = effect;
        return call(app, cpu, kPlay, {pitch});
    };
    auto inside = [&](reg32 lo, reg32 hi) { return i32(cell()) >= i32(lo) && i32(cell()) <= i32(hi); };
    // Track 8: two kinds of bird, now and then.
    cpu.esi = cell();
    if (inside(0x3d4, 0x45b) && track() == 8)
    {
        if (!randomOf(0x1f40, cpu.ecx))
            return;
        if (cpu.edx > 0x1f27)
        {
            if (!random())
                return;
            cpu.eax &= 0x7f;
            const reg32 pitch = cpu.eax;
            if (!randomOf(0x28, cpu.ecx))
                return;
            cpu.ebx = at(app, b - 0xc);
            cpu.ecx = cpu.edx + 0x32;
            if (!randomPan(true))
                return;
            cpu.eax = at(app, kAmbience);
            cpu.ebx = cpu.edx;
            cpu.edx = 0xb;
            if (!call(app, cpu, kPlay, {pitch}))
                return;
        }
        if (!randomOf(0x1f40, cpu.ecx))
            return;
        if (cpu.edx > 0x1edc)
        {
            if (!random())
                return;
            cpu.eax = (cpu.eax & 0x1f) + 0x40;
            const reg32 pitch = cpu.eax;
            if (!randomOf(0x28, cpu.ecx))
                return;
            cpu.esi = at(app, b - 0xc);
            cpu.ecx = cpu.edx + 0x32;
            if (!randomPan(true))
                return;
            cpu.eax = at(app, kAmbience);
            cpu.ebx = cpu.edx;
            cpu.edx = 9;
            if (!call(app, cpu, kPlay, {pitch}))
                return;
        }
    }
    // Track 8, away from two stretches: two more.
    cpu.eax = car;
    cpu.edx = cell();
    {
        const i32 c = i32(cpu.edx);
        const bool away = c > 0x4c2 || c < 0x49 || (c > 0x7e && c < 0xb1);
        if (away && track() == 8)
        {
            if (!randomOf(0x1f40, cpu.ecx))
                return;
            if (cpu.edx > 0x1e14)
            {
                if (!sidePan(true, true))
                    return;
                if (!random())
                    return;
                cpu.eax = (cpu.eax & 0x1f) + 0x40;
                const reg32 pitch = cpu.eax;
                if (!randomOf(0x28, cpu.ecx))
                    return;
                cpu.ecx = cpu.edx + 0x32;
                if (!play(2, pitch))
                    return;
            }
            if (!randomOf(0x1f40, cpu.ecx))
                return;
            if (cpu.edx > 0x1f2c)
            {
                if (!sidePan(true, false))
                    return;
                if (!randomOf(0x28, cpu.ecx))
                    return;
                cpu.ecx = cpu.edx + 0x1e;
                if (!play(1, 0x40))
                    return;
            }
        }
    }
    // Track 6: a repeating call (0x570f70's: times left, pan, ticks, gap,
    // effect, pitch, volume).
    cpu.eax = car;
    cpu.esi = cell();
    const reg32 repeat = 0x570f70 + player() * 0x1c;
    if (inside(0x2f0, 0x3de) && track() == 6)
    {
        cpu.eax = player() << 2;
        cpu.edx = cpu.eax;
        cpu.eax = (cpu.eax << 3) - cpu.edx;
        cpu.esi = 0x570f70 + cpu.eax;
        cpu.ebx = at(app, cpu.esi);
        if (cpu.ebx != 0)
        {
            setByte0(cpu.edx, 0);
            const reg16 ticks = reg16(half(app, cpu.esi + 8) - 1);
            cpu.edx = (cpu.edx & 0xffff0000) | ticks;
            putHalf(app, cpu.esi + 8, ticks);
            if (ticks == 0)
            {
                cpu.eax = byte(app, cpu.esi + 0xd);
                cpu.ecx = 0;
                const reg32 pitch = cpu.eax;
                cpu.eax = at(app, b - 0xc);
                setByte0(cpu.ecx, byte(app, cpu.esi + 0xe));
                if (cpu.eax != 0)
                    cpu.ebx = at(app, b - 0x10);
                else
                {
                    cpu.edx = at(app, b - 0x14);
                    cpu.ebx = (at(app, cpu.esi + 4) + cpu.edx) & 0xffff;
                }
                cpu.edx = 0;
                cpu.eax = at(app, kAmbience);
                setByte0(cpu.edx, byte(app, cpu.esi + 0xc));
                if (!call(app, cpu, kPlay, {pitch}))
                    return;
                cpu.ecx = at(app, cpu.esi) - 1;
                cpu.eax = (cpu.eax & 0xffff0000) | half(app, cpu.esi + 0xa);
                putHalf(app, cpu.esi + 8, reg16(cpu.eax));
                put(app, cpu.esi, cpu.ecx);
            }
        }
        else
        {
            if (!randomOf(0x1f40, cpu.ecx))
                return;
            if (cpu.edx > 0x1ef5)
            {
                if (!randomOf(3, cpu.ecx))
                    return;
                cpu.ecx = cpu.edx + 0x11;
                if (cpu.ecx == 0x13)
                {
                    if (!random())
                        return;
                    put(app, cpu.esi, 1);
                }
                else
                {
                    if (!randomOf(5, cpu.ebx))
                        return;
                    cpu.edx += 3;
                    put(app, cpu.esi, cpu.edx);
                }
                if (!random())
                    return;
                setByte1(cpu.eax, 0);
                setByte0(cpu.eax, reg8(cpu.eax) & 0xf);
                putByte(app, cpu.esi + 0xc, reg8(cpu.ecx));
                cpu.eax += 0x10;
                putHalf(app, cpu.esi + 0xa, reg16(cpu.eax));
                putHalf(app, cpu.esi + 8, reg16(cpu.eax));
                if (!random())
                    return;
                setByte0(cpu.eax, reg8((cpu.eax & 0x3f) + 0x40));
                putByte(app, cpu.esi + 0xd, reg8(cpu.eax));
                if (!random())
                    return;
                setByte0(cpu.eax, reg8((cpu.eax & 0x3f) + 0x40));
                cpu.ebx = at(app, b - 0xc);
                putByte(app, cpu.esi + 0xe, reg8(cpu.eax));
                if (cpu.ebx != 0)
                    cpu.eax = at(app, b - 0x10);
                else
                {
                    const bool mirror = at(app, 0x6fd4c4) != 0;
                    if (!random())
                        return;
                    cpu.eax = (cpu.eax & 0x3fff) + (mirror ? 0xc000 : 0x2000);
                }
                put(app, cpu.esi + 4, cpu.eax);
            }
        }
    }
    (void)repeat;
    // Track 6, out of tunnels, in three stretches: a gust.
    if (track() == 6 && cpu.edi == 0)
    {
        const i32 c = i32(cell());
        if ((c > 0xdf && c < 0x13d) || (c > 0x163 && c < 0x1a4) || (c > 0x311 && c < 0x352))
        {
            if (!randomOf(0xc8, cpu.ecx))
                return;
            if (cpu.edx > 0xbe)
            {
                if (split())
                    cpu.ebx = at(app, b - 0x10);
                else
                {
                    const bool mirror = at(app, 0x6fd4c4) != 0;
                    if (!random())
                        return;
                    cpu.ebx = cpu.eax & 0x3fff;
                    if (mirror)
                    {
                        cpu.edi = at(app, b - 0x14);
                        cpu.ebx += 0x2000;
                        cpu.ebx += cpu.edi;
                    }
                    else
                    {
                        cpu.edx = at(app, b - 0x14);
                        cpu.ebx += 0xc000;
                        cpu.ebx += cpu.edx;
                    }
                    cpu.ebx &= 0xffff;
                }
                if (!random())
                    return;
                cpu.eax &= 0x7f;
                const reg32 pitch = cpu.eax;
                if (!random())
                    return;
                cpu.eax &= 0x3f;
                cpu.ecx = cpu.eax + 0x40;
                if (!play(8, pitch))
                    return;
            }
        }
    }
    // Tracks 3 and 7: now and then.
    cpu.eax = car;
    cpu.ecx = cell();
    if (inside(0x28c, 0x3b1))
    {
        cpu.esi = track();
        if (cpu.esi == 3 || cpu.esi == 7)
        {
            if (!randomOf(0xfa0, cpu.ecx))
                return;
            if (cpu.edx > 0xf96)
            {
                if (!random())
                    return;
                cpu.eax = (cpu.eax & 0x3f) + 0x40;
                const reg32 pitch = cpu.eax;
                if (!random())
                    return;
                cpu.eax &= 0x3f;
                cpu.ecx = cpu.eax + 0x40;
                if (!randomPan(true))
                    return;
                cpu.eax = at(app, kAmbience);
                cpu.ebx = cpu.edx;
                cpu.edx = 3;
                if (!call(app, cpu, kPlay, {pitch}))
                    return;
            }
        }
    }
    // Track 4, at a gate when the car brakes: a horn, and the call's count.
    cpu.eax = car;
    cpu.edx = cell();
    if ((cpu.edx == 0x163 || cpu.edx == 0x164) && track() == 4 && at(app, car + 0x18c) == 0xa
        && half(app, car + 0x74) != 0)
    {
        cpu.eax = player() << 2;
        cpu.edx = cpu.eax;
        cpu.eax = ((cpu.eax << 3) - cpu.edx) + 0x570f70;
        cpu.ecx = 0x7f;
        put(app, cpu.eax, 0x140);
        cpu.edi = at(app, b - 0xc);
        putHalf(app, cpu.eax + 8, 0x10);
        cpu.ebx = cpu.edi != 0 ? at(app, b - 0x10) : 0;
        if (!play(0xa, 0x40))
            return;
    }
    // Track 4: the train, as it passes.
    cpu.eax = car;
    cpu.edx = cell();
    if (inside(0x12c, 0x1f4) && track() == 4)
    {
        cpu.eax = player() << 2;
        cpu.edx = cpu.eax;
        cpu.eax = (cpu.eax << 3) - cpu.edx;
        cpu.edx = 0x570f70 + cpu.eax;
        put(app, b - 0x18, cpu.edx);
        cpu.esi = at(app, cpu.edx);
        if (cpu.esi != 0)
        {
            const reg16 ticks = half(app, cpu.edx + 8);
            cpu.esi = (cpu.esi & 0xffff0000) | ticks;
            bool count = true;
            if (ticks != 0)
            {
                cpu.edi = cpu.esi - 1;
                putHalf(app, cpu.edx + 8, reg16(cpu.edi));
            }
            else
            {
                if (!randomOf(0x1f4, cpu.ecx))
                    return;
                cpu.eax = cpu.ecx;
                cpu.ecx = at(app, b - 0x18);
                cpu.eax -= at(app, cpu.ecx);
                if (i32(cpu.edx) > i32(cpu.eax))
                {
                    // Its place: 0x412988's, scaled.
                    x86::FPU& fpu = cpu.fpu;
                    cpu.edi = b - 0x38;
                    cpu.esi = 0x412988;
                    for (reg32 k = 0; k < 3; ++k, cpu.esi += 4, cpu.edi += 4)
                        put(app, cpu.edi, at(app, cpu.esi));
                    const x86::Float c = x86::Float(app->getMemory<double>(0x536ba8));
                    for (reg32 k = 0; k < 12; k += 4)
                        app->getMemory<float>(b - 0x2c + k)
                            = float(fpu.mul(x86::Float(x86::sreg32(at(app, b - 0x38 + k))), c));
                    put(app, b - 4, at(app, b - 0x30));
                    cpu.eax = at(app, b - 0x30);
                    cpu.edx = b - 0x2c;
                    cpu.eax = 0x570a78;
                    if (!call(app, cpu, 0x410cb0))
                        return;
                    cpu.edx = cpu.eax;
                    towardZero(cpu, 16);
                    cpu.eax = reg32(mul(i32(cpu.eax), i32(cpu.eax)));
                    if (i32(cpu.eax) > 0x57e)
                        cpu.eax = 0;
                    else
                    {
                        cpu.edx = 0x57e - cpu.eax;
                        cpu.eax = (cpu.edx << 7) - cpu.edx;
                        cpu.edx = cpu.eax;
                        cpu.ecx = 0x57e;
                        idiv(cpu, 0x57e);
                    }
                    cpu.ecx = cpu.eax;
                    if (split())
                        cpu.edx = at(app, b - 0x10);
                    else
                    {
                        cpu.edx = b - 0x2c;
                        cpu.eax = 0x570a78;
                        if (!call(app, cpu, 0x410d30))
                            return;
                        cpu.edx = cpu.eax;
                    }
                    if (!random())
                        return;
                    cpu.eax &= 1;
                    cpu.esi = cpu.eax + 6;
                    cpu.ebx = cpu.edx;
                    cpu.eax = at(app, kAmbience);
                    cpu.edx = cpu.esi;
                    if (!call(app, cpu, kPlay, {0x40}))
                        return;
                }
            }
            if (count)
            {
                cpu.eax = at(app, b - 0x18);
                put(app, cpu.eax, at(app, cpu.eax) - 1);
            }
        }
    }
    // Track 4, in three stretches: two kinds of noise.
    for (int kind = 0; kind < 2; ++kind)
    {
        const i32 c = i32(cell());
        const bool in = (c >= 0xeb && c <= 0x136) || (c >= 0x19f && c <= 0x24e) || (c >= 0x262 && c <= 0x3fa);
        if (!(in && track() == 4))
            continue;
        if (!randomOf(0x1f40, cpu.ecx))
            return;
        if (cpu.edx <= (kind == 0 ? 0x1edcu : 0x1f2cu))
            continue;
        if (!randomOf(0x4b, cpu.ecx))
            return;
        if (kind == 0)
        {
            cpu.esi = at(app, b - 0xc);
            cpu.ecx = cpu.edx + 5;
            if (!randomPan(true))
                return;
            cpu.eax = at(app, kAmbience);
            cpu.ebx = cpu.edx;
            cpu.edx = 5;
            if (!call(app, cpu, kPlay, {0x40}))
                return;
        }
        else
        {
            cpu.ecx = cpu.edx + 5;
            cpu.edx = at(app, b - 0xc);
            if (cpu.edx != 0)
                cpu.edx = at(app, b - 0x10);
            else
            {
                cpu.ebx = 0xffff;
                if (!random())
                    return;
                udiv(cpu, cpu.ebx);
            }
            if (!random())
                return;
            cpu.eax &= 1;
            cpu.esi = at(app, kAmbience);
            cpu.eax += 8;
            cpu.ebx = cpu.edx;
            cpu.edx = cpu.eax;
            cpu.eax = cpu.esi;
            if (!call(app, cpu, kPlay, {0x40}))
                return;
        }
    }
    // Track 0, in two stretches.
    {
        const i32 c = i32(cell());
        if (((c >= 0xeb && c <= 0x1e5) || (c >= 0x244 && c <= 0x352)) && track() == 0)
        {
            if (!randomOf(0x1f40, cpu.ecx))
                return;
            if (cpu.edx > 0x1e78)
            {
                if (!random())
                    return;
                cpu.eax &= 0x7f;
                const reg32 pitch = cpu.eax;
                if (!randomOf(0x64, cpu.ecx))
                    return;
                cpu.ecx = cpu.edx + 0x1c;
                cpu.edx = at(app, b - 0xc);
                if (cpu.edx != 0)
                    cpu.ebx = at(app, b - 0x10);
                else
                {
                    cpu.ebx = 0xffff;
                    if (!random())
                        return;
                    udiv(cpu, cpu.ebx);
                    cpu.ebx = cpu.edx;
                }
                if (!randomOf(3, cpu.esi))
                    return;
                cpu.eax = at(app, kAmbience);
                cpu.edx += 0xb;
                if (!call(app, cpu, kPlay, {pitch}))
                    return;
            }
        }
    }
    // Track 1, near the end.
    if (inside(0x409, 0x44c) && track() == 1)
    {
        if (!randomOf(0xfa0, cpu.ecx))
            return;
        if (cpu.edx > 0xf96)
        {
            if (split())
                cpu.ebx = at(app, b - 0x10);
            else
            {
                const bool mirror = at(app, 0x6fd4c4) != 0;
                if (!random())
                    return;
                cpu.ebx = cpu.eax & 0x3fff;
                if (mirror)
                {
                    cpu.edx = at(app, b - 0x14);
                    cpu.ebx += 0x2000;
                    cpu.ebx += cpu.edx;
                }
                else
                {
                    cpu.ecx = at(app, b - 0x14);
                    cpu.ebx += 0xc000;
                    cpu.ebx += cpu.ecx;
                }
                cpu.ebx &= 0xffff;
            }
            if (!random())
                return;
            cpu.eax = (cpu.eax & 0x1f) + 0x40;
            const reg32 pitch = cpu.eax;
            if (!randomOf(0x28, cpu.ecx))
                return;
            cpu.ecx = cpu.edx + 0x32;
            if (!play(0xb, pitch))
                return;
        }
    }
    // Tracks 1 and 5, braking at a spot: a call.
    cpu.eax = car;
    cpu.ebx = cell();
    if (cpu.ebx == 0xa6 || cpu.ebx == 0xa7)
    {
        cpu.edi = track();
        if ((cpu.edi == 1 || cpu.edi == 5) && at(app, car + 0x18c) == 0xa && half(app, car + 0x74) != 0)
        {
            cpu.ecx = 0x7f;
            cpu.ebx = at(app, b - 0xc);
            if (cpu.ebx != 0)
                cpu.ebx = at(app, b - 0x10);
            if (!play(3, 0x40))
                return;
        }
    }
    // Track 2: a call repeating, louder each time; or a single one.
    cpu.eax = car;
    cpu.esi = cell();
    if (inside(0x398, 0x42a) && track() == 2)
    {
        cpu.eax = player() << 2;
        cpu.edx = cpu.eax;
        cpu.eax = (cpu.eax << 3) - cpu.edx;
        cpu.esi = 0x570f70 + cpu.eax;
        cpu.edx = at(app, cpu.esi);
        if (cpu.edx != 0)
        {
            const reg16 ticks = reg16(half(app, cpu.esi + 8) - 1);
            cpu.ebx = (cpu.ebx & 0xffff0000) | ticks;
            putHalf(app, cpu.esi + 8, ticks);
            if (ticks == 0)
            {
                cpu.ebx = at(app, cpu.esi + 4);
                cpu.eax = byte(app, cpu.esi + 0xd);
                cpu.ecx = byte(app, cpu.esi + 0xe);
                const reg32 pitch = cpu.eax;
                cpu.edx = byte(app, cpu.esi + 0xc);
                cpu.eax = at(app, kAmbience);
                if (!call(app, cpu, kPlay, {pitch}))
                    return;
                setByte0(cpu.ecx, reg8(byte(app, cpu.esi + 0xd) + 4));
                cpu.eax = (cpu.eax & 0xffff0000) | half(app, cpu.esi + 0xa);
                putHalf(app, cpu.esi + 8, reg16(cpu.eax));
                putByte(app, cpu.esi + 0xd, reg8(cpu.ecx));
                if (reg8(cpu.ecx) > 0x7f)
                    putByte(app, cpu.esi + 0xd, 0x7f);
                put(app, cpu.esi, at(app, cpu.esi) - 1);
            }
        }
        if (!randomOf(0x1f40, cpu.ecx))
            return;
        if (cpu.edx > 0x1edc)
        {
            if (!randomOf(5, cpu.ecx))
                return;
            cpu.edx += 0xb;
            put(app, b - 0x1c, cpu.edx);
            if (i32(cpu.edx) >= 0xd && at(app, cpu.esi) == 0)
            {
                if (!randomOf(7, cpu.ecx))
                    return;
                ++cpu.edx;
                put(app, cpu.esi, cpu.edx);
                if (!random())
                    return;
                cpu.edx = cpu.eax;
                setByte1(cpu.edx, reg8(cpu.edx >> 8) ^ reg8(cpu.eax >> 8));
                cpu.eax = at(app, b - 0x1c);
                setByte0(cpu.edx, reg8(cpu.edx) & 0xf);
                cpu.eax -= 0xb;
                cpu.edx += 8;
                cpu.eax <<= 3;
                cpu.edx += cpu.eax;
                setByte0(cpu.eax, byte(app, b - 0x1c));
                putHalf(app, cpu.esi + 0xa, reg16(cpu.edx));
                putByte(app, cpu.esi + 0xc, reg8(cpu.eax));
                cpu.eax = at(app, b - 0xc);
                putHalf(app, cpu.esi + 8, reg16(cpu.edx));
                if (cpu.eax != 0)
                    cpu.edx = at(app, b - 0x10);
                else
                {
                    if (!randomOf(0xffff, cpu.ecx))
                        return;
                }
                put(app, cpu.esi + 4, cpu.edx);
                if (!random())
                    return;
                setByte0(cpu.eax, reg8((cpu.eax & 0x3f) + 0x40));
                putByte(app, cpu.esi + 0xd, reg8(cpu.eax));
                if (!random())
                    return;
                setByte0(cpu.eax, reg8((cpu.eax & 0x3f) + 0x3a));
                putByte(app, cpu.esi + 0xe, reg8(cpu.eax));
            }
            else
            {
                if (!random())
                    return;
                cpu.eax = (cpu.eax & 0x3f) + 0x40;
                const reg32 pitch = cpu.eax;
                if (!randomOf(0x30, cpu.ecx))
                    return;
                cpu.ecx += cpu.edx;
                cpu.edx = at(app, b - 0xc);
                if (cpu.edx != 0)
                    cpu.edx = at(app, b - 0x10);
                else
                {
                    cpu.ebx = 0xffff;
                    if (!random())
                        return;
                    udiv(cpu, cpu.ebx);
                }
                cpu.eax = at(app, kAmbience);
                cpu.ebx = cpu.edx;
                cpu.edx = at(app, b - 0x1c);
                if (!call(app, cpu, kPlay, {pitch}))
                    return;
            }
        }
    }
    // Track 5, in a stretch: now and then.
    {
        const i32 c = i32(cell());
        if (c > 0x1f4 && c < 0x2bc && track() == 5)
        {
            if (!randomOf(0x1388, cpu.ecx))
                return;
            if (cpu.edx > 0x1374)
            {
                if (!randomOf(0x25, cpu.ecx))
                    return;
                cpu.edi = at(app, b - 0xc);
                cpu.ecx = cpu.edx + 0x5a;
                if (!randomPan(true))
                    return;
                if (!random())
                    return;
                cpu.eax &= 1;
                cpu.esi = cpu.eax + 0xa;
                cpu.ebx = cpu.edx;
                cpu.eax = at(app, kAmbience);
                cpu.edx = cpu.esi;
                if (!call(app, cpu, kPlay, {0x40}))
                    return;
            }
        }
    }
    // Track 1: three more, by stretch.
    auto rare = [&](bool in, reg32 limit, reg32 effect, int pan) {
        if (!in || track() != 1)
            return true;
        if (!randomOf(0x1388, cpu.ecx))
            return false;
        if (cpu.edx <= limit)
            return true;
        cpu.ecx = 0x7f;
        if (pan == 0)
        {
            cpu.esi = at(app, b - 0xc);
            if (!randomPan(true))
                return false;
        }
        else
        {
            cpu.edi = at(app, b - 0xc);
            if (!randomPan(true))
                return false;
        }
        cpu.eax = at(app, kAmbience);
        cpu.ebx = cpu.edx;
        cpu.edx = effect;
        return call(app, cpu, kPlay, {0x40});
    };
    {
        const i32 c = i32(cell());
        if (!rare(c > 0xc8 && c < 0x13b, 0x1356, 0x12, 0))
            return;
    }
    {
        const i32 c = i32(cell());
        if (!rare((c > 0x168 && c < 0x1bd) || (c > 0x355 && c < 0x3b6), 0x137e, 0x10, 1))
            return;
    }
    // Track 1, at the start, on lap 3: a cheer.
    cpu.eax = car;
    cpu.edx = cell();
    if ((cpu.edx == 0xb || cpu.edx == 0xc) && track() == 1 && at(app, car + 0x638) == 3)
    {
        if (!randomOf(0x1388, cpu.ecx))
            return;
        if (cpu.edx > 0x1324)
        {
            fixedPan(true);
            if (!randomOf(0x50, cpu.ecx))
                return;
            cpu.ecx = 0x7f;
            if (!play(0xe, cpu.edx))
                return;
        }
    }
    // Track 4: once on its stretch after lap 9, once at its spot on lap 2.
    cpu.eax = car;
    cpu.edx = cell();
    if (i32(cpu.edx) > 0x13b && i32(cpu.edx) < 0x143 && track() == 4 && s32(app, car + 0x638) > 9
        && at(app, 0x552d84) == 0)
    {
        fixedPan(true);
        cpu.ecx = 0x7f;
        if (!play(0xd, 0x40))
            return;
        put(app, 0x552d84, 1);
    }
    cpu.eax = car;
    cpu.ebx = cell();
    if (!(i32(cpu.ebx) >= 0x13b && i32(cpu.ebx) <= 0x143) && track() == 4)
    {
        cpu.eax = 0;
        put(app, 0x552d84, cpu.eax);
    }
    cpu.eax = car;
    cpu.edx = cell();
    if (cpu.edx == 0x161 && track() == 4 && at(app, car + 0x638) == 2 && at(app, 0x552d88) == 0)
    {
        if (!random())
            return;
        cpu.ecx = 0x7f;
        cpu.eax &= 0x3f;
        cpu.edi = at(app, b - 0xc);
        const reg32 pitch = cpu.eax;
        cpu.ebx = cpu.edi != 0 ? at(app, b - 0x10) : 0;
        if (!play(0xf, pitch))
            return;
        put(app, 0x552d88, 1);
    }
    cpu.eax = car;
    if (cell() == 0x189 && at(app, car + 0x638) == 0xb && track() == 4)
    {
        cpu.esi = 0;
        put(app, 0x552d88, cpu.esi);
    }
    // Track 0: two more.
    cpu.eax = car;
    cpu.edi = cell();
    if (i32(cpu.edi) > 0x41 && i32(cpu.edi) < 0x55 && track() == 0)
    {
        if (!randomOf(0x1388, cpu.ecx))
            return;
        if (cpu.edx > 0x137e)
        {
            fixedPan(true);
            cpu.ecx = 0x7f;
            if (!play(0xa, 0x40))
                return;
        }
    }
    cpu.eax = car;
    cpu.edi = cell();
    if (i32(cpu.edi) > 0x3a7 && i32(cpu.edi) < 0x3ac && s32(app, car + 0x638) > 0xa && track() == 0)
    {
        if (!randomOf(0x1388, cpu.ecx))
            return;
        if (cpu.edx > 0x1374)
        {
            fixedPan(true);
            if (!random())
                return;
            cpu.eax &= 1;
            cpu.edx = cpu.eax + 0x10;
            cpu.ecx = 0x7f;
            cpu.eax = at(app, kAmbience);
            if (!call(app, cpu, kPlay, {0x40}))
                return;
        }
    }
    // Track 3, at either end: a call repeating, the pan moving on, quieter
    // each time; and now and then another.
    cpu.eax = car;
    cpu.edx = cell();
    auto ends = [&] {
        const i32 c = i32(cell());
        return (c >= 0x14 && c <= 0x190) || (c >= 0x578 && c <= 0x5c8);
    };
    if (ends() && track() == 3)
    {
        cpu.eax = player() << 2;
        cpu.edx = cpu.eax;
        cpu.eax = (cpu.eax << 3) - cpu.edx;
        cpu.esi = 0x570f70 + cpu.eax;
        cpu.eax = at(app, cpu.esi);
        if (cpu.eax != 0)
        {
            const reg16 ticks = reg16(half(app, cpu.esi + 8) - 1);
            cpu.edi = (cpu.edi & 0xffff0000) | ticks;
            putHalf(app, cpu.esi + 8, ticks);
            if (ticks == 0)
            {
                cpu.ebx = at(app, cpu.esi + 4);
                cpu.eax = byte(app, cpu.esi + 0xd);
                cpu.ecx = byte(app, cpu.esi + 0xe);
                const reg32 pitch = cpu.eax;
                cpu.edx = byte(app, cpu.esi + 0xc);
                cpu.eax = at(app, kAmbience);
                if (!call(app, cpu, kPlay, {pitch}))
                    return;
                cpu.edx = at(app, cpu.esi + 4) + 0xfa0;
                cpu.eax = (cpu.eax & 0xffff0000) | half(app, cpu.esi + 0xa);
                putHalf(app, cpu.esi + 8, reg16(cpu.eax));
                cpu.ecx = at(app, b - 0xc);
                put(app, cpu.esi + 4, cpu.edx);
                cpu.eax = cpu.ecx != 0 ? at(app, b - 0x10) : cpu.edx & 0xffff;
                put(app, cpu.esi + 4, cpu.eax);
                cpu.ebx = at(app, cpu.esi) - 1;
                setByte0(cpu.eax, reg8(byte(app, cpu.esi + 0xe) - 0xf));
                put(app, cpu.esi, cpu.ebx);
                putByte(app, cpu.esi + 0xe, reg8(cpu.eax));
            }
        }
        if (!randomOf(0x1f40, cpu.ecx))
            return;
        if (cpu.edx > 0x1f2c)
        {
            cpu.ebx = 0xa;
            if (at(app, cpu.esi) == 0)
            {
                if (!randomOf(3, cpu.ecx))
                    return;
                cpu.edx += cpu.ecx;
                put(app, cpu.esi, cpu.edx);
                if (!random())
                    return;
                setByte1(cpu.eax, 0);
                setByte0(cpu.eax, reg8(cpu.eax) & 0xf);
                cpu.eax += 0x10;
                putHalf(app, cpu.esi + 0xa, reg16(cpu.eax));
                putHalf(app, cpu.esi + 8, reg16(cpu.eax));
                cpu.eax = at(app, b - 0xc);
                putByte(app, cpu.esi + 0xc, reg8(cpu.ebx));
                if (cpu.eax != 0)
                    cpu.edx = at(app, b - 0x10);
                else if (!randomOf(0xffff, cpu.ecx))
                    return;
                putByte(app, cpu.esi + 0xd, 0x40);
                putByte(app, cpu.esi + 0xe, 0x7f);
                put(app, cpu.esi + 4, cpu.edx);
            }
        }
    }
    cpu.eax = car;
    cpu.edx = cell();
    if (ends() && track() == 3)
    {
        if (!randomOf(0x1388, cpu.ecx))
            return;
        if (cpu.edx > 0x136f)
        {
            if (!randomOf(0x2d, cpu.ecx))
                return;
            cpu.eax = at(app, b - 0xc);
            cpu.ecx = cpu.edx + 0x50;
            if (cpu.eax != 0)
                cpu.ebx = at(app, b - 0x10);
            else
            {
                cpu.ebx = 0xffff;
                cpu.edx = 0;
                if (!random())
                    return;
                udiv(cpu, cpu.ebx);
                cpu.ebx = cpu.edx;
            }
            if (!randomOf(3, cpu.esi))
                return;
            cpu.eax = at(app, kAmbience);
            cpu.edx += 0x11;
            if (!call(app, cpu, kPlay, {0x40}))
                return;
        }
    }
    // Track 3: the bells, once on the lap (0x552c34) before the last, once
    // more after.
    cpu.eax = car;
    cpu.edx = cell();
    if (inside(0x528, 0x55c) && track() == 3)
    {
        if (!randomOf(0x1388, cpu.ecx))
            return;
        if (cpu.edx > 0x1356 && at(app, 0x552c38) == 0)
        {
            cpu.eax = car;
            cpu.edi = at(app, 0x552c34);
            if (i32(cpu.edi) <= s32(app, car + 0x204))
            {
                fixedPan(false);
                cpu.ecx = 0x7f;
                if (!play(7, 0x40))
                    return;
                put(app, 0x552c38, 1);
            }
        }
    }
    cpu.eax = car;
    cpu.ebx = cell();
    if (i32(cpu.ebx) < 0x359 || i32(cpu.ebx) > 0x388 || track() != 3)
        return done();
    if (!randomOf(0x1388, cpu.ecx))
        return;
    if (cpu.edx <= 0x1356 || at(app, 0x552c38) != 1)
        return done();
    fixedPan(false);
    cpu.ecx = 0x7f;
    if (!play(8, 0x40))
        return;
    put(app, 0x552c38, 2);
    done();
}

}  // namespace snd
}  // namespace nfs3hp
