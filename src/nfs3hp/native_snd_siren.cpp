#include "native_snd.h"

/* The race's sirens and noises by distance, native (native_snd.h says
 * how): a siren of 5 (the cops' four, the fourth the player's own) that
 * warbles -- its two tones taking turns for so many ticks, picked at random
 * -- its volume, pitch and place set as it goes; the noises of a car near by
 * as loud as it is close.
 *
 * A siren's state, 5 words apart: 0x552d90 on, 0x552da4 which tone,
 * 0x552db8 the first tone's ticks, 0x552dcc the second's (-1: for ever),
 * 0x552de0 the ticks gone.  Its sound: 0x570e68 the fourth's, else
 * 0x570ec0 + 8 * the siren (the slots 0x1b on). */
namespace nfs3hp
{
namespace snd
{

namespace
{

constexpr reg32 kEffectsOn = 0x55290c, kSirenOn = 0x552d90, kSirenTone = 0x552da4, kSirenFirst = 0x552db8;
constexpr reg32 kSirenSecond = 0x552dcc, kSirenTicks = 0x552de0, kPlayerSiren = 0x570e68, kSirens = 0x570ec0;
constexpr reg32 kSlots = 0x570de8, kCopBank = 0x571160, kSplitScreen = 0x6fd3b0, kRandom = 0x4e0d88;
constexpr reg32 kSlotStop = 0x416f60, kSlotPlay = 0x417080, kPlayEffect = 0x4182b0;

/* Siren i's sound. */
reg32 sirenSound(App* app, reg32 i) { return i == 4 ? at(app, kPlayerSiren) : at(app, i * 8 + kSirens); }

/* sub_417cb0, sub_417db0, sub_417e00: siren eax's tone `effect` started --
 * the tone `tone` -- its sound kept. */
void sirenTone(App* app, CPU& cpu, reg32 tone, reg32 effect)
{
    const Kept kept(cpu);
    cpu.ebp = cpu.esp = kept.frame(5);
    cpu.esi = cpu.eax;
    put(app, cpu.eax * 4 + kSirenTone, tone);
    cpu.edx = effect;
    cpu.eax = at(app, kCopBank);
    cpu.ecx = 0;
    cpu.ebx = 0;
    if (!call(app, cpu, kPlayEffect, {0x40}))
        return;
    if (cpu.esi == 4)
        put(app, kPlayerSiren, cpu.eax);
    else
        put(app, cpu.esi * 8 + kSirens, cpu.eax);
    leave(cpu, kept, kEbx | kEcx | kEdx | kEsi);
}

}  // namespace

/* 0x417b80 (stdcall 8): the noise ecx of slot eax, effect edx, as loud as the
 * car is near -- [esp+4] its distance (0x15f9 and on: silent), [esp+8] its
 * pan -- or the slot stopped. */
void noiseByDistance(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const unsigned pushed = kEsi | kEdi;
    cpu.ebp = kept.frame(3);
    cpu.esp = cpu.ebp - 4;
    cpu.esi = cpu.eax;
    cpu.edi = cpu.edx;
    if (at(app, kEffectsOn) == 0)
        return leave(cpu, kept, pushed, 8);
    const reg32 distance = at(app, cpu.ebp + 0x10);
    bool play = false;
    if (i32(distance) < 0x15f9)
    {
        cpu.eax = 0x15f9 - distance;
        put(app, cpu.ebp - 4, cpu.eax);
        cpu.edx = at(app, cpu.ebp - 4);
        cpu.eax = (cpu.eax << 7) - cpu.edx;
        cpu.edx = cpu.eax;
        put(app, cpu.ebp - 4, 0x15f9);
        idiv(cpu, 0x15f9);
        play = cpu.eax != 0;
    }
    if (!play && cpu.esi != 0xffffffff)
    {
        if (at(app, cpu.esi * 8 + kSlots) != 0xffffffff)
        {
            cpu.eax = cpu.esi;
            if (!call(app, cpu, kSlotStop))
                return;
        }
        return leave(cpu, kept, pushed, 8);
    }
    cpu.eax = at(app, cpu.ebp + 0x14);
    cpu.edx = distance;
    cpu.ecx = reg32(i32(cpu.ecx) >> 4);
    const reg32 pan = cpu.eax;
    cpu.eax = cpu.esi;
    cpu.edx = cpu.edi;
    if (!call(app, cpu, 0x416d90, {distance, pan}))
        return;
    leave(cpu, kept, pushed, 8);
}

/* 0x417c00: the player's noise (slot 0x10, the second player's 0x11 by eax
 * in the split screen), effect 3, at pitch ebx, as loud as edx is short of
 * 0x15f9, pan ecx. */
void playerNoise(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const unsigned pushed = kEsi | kEdi;
    cpu.ebp = cpu.esp = kept.frame(3);
    cpu.esi = cpu.eax;
    if (at(app, kEffectsOn) == 0)
        return leave(cpu, kept, pushed);
    if (i32(cpu.edx) < 0x15f9)
    {
        cpu.eax = 0x15f9 - cpu.edx;
        cpu.edx = cpu.eax;
        cpu.eax = (cpu.eax << 7) - cpu.edx;
        cpu.edx = cpu.eax;
        cpu.edi = 0x15f9;
        idiv(cpu, 0x15f9);
    }
    else
        cpu.eax = 0;
    const reg32 slot = cpu.esi != 0 && at(app, kSplitScreen) == 1 ? 0x11 : 0x10;
    cpu.edx = 3;
    const reg32 pan = cpu.ecx;
    cpu.ecx = cpu.eax;
    cpu.eax = slot;
    if (!call(app, cpu, kSlotPlay, {pan}))
        return;
    leave(cpu, kept, pushed);
}

/* 0x417c70: the player's noise stopped (the second player's by eax in the
 * split screen). */
void playerNoiseStop(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.ebp = cpu.esp = kept.frame(1);
    if (at(app, kEffectsOn) != 0)
    {
        cpu.eax = cpu.eax != 0 && at(app, kSplitScreen) == 1 ? 0x11 : 0x10;
        if (!call(app, cpu, kSlotStop))
            return;
    }
    leave(cpu, kept, 0);
}

/* 0x417ca0: whether siren eax is on. */
void sirenIsOn(App* app, CPU& cpu)
{
    cpu.eax = at(app, cpu.eax * 4 + kSirenOn);
    cpu.esp += 4;
}

/* 0x417cb0: siren eax's first tone (effect 0). */
void sirenFirstTone(App* app, CPU& cpu) { sirenTone(app, cpu, 0, 0); }

/* 0x417db0: siren eax's second tone (effect 1). */
void sirenSecondTone(App* app, CPU& cpu) { sirenTone(app, cpu, 1, 1); }

/* 0x417e00: siren eax's one tone for ever (effect 9). */
void sirenSteadyTone(App* app, CPU& cpu) { sirenTone(app, cpu, 1, 9); }

/* 0x417d00: siren eax's first tone faded out, the second's turn. */
void sirenFirstDone(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.ebp = cpu.esp = kept.frame(4);
    cpu.edx = 1;
    cpu.ecx = 0;
    put(app, cpu.eax * 4 + kSirenTone, cpu.edx);
    put(app, cpu.eax * 4 + kSirenTicks, cpu.ecx);
    cpu.ebx = 0xffffffff;
    cpu.edx = 5;
    cpu.eax = sirenSound(app, cpu.eax);
    if (!call(app, cpu, 0x4e9420))
        return;
    leave(cpu, kept, kEbx | kEcx | kEdx);
}

/* 0x417e60: siren eax's second tone faded out, the first's turn. */
void sirenSecondDone(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.ebp = cpu.esp = kept.frame(3);
    cpu.edx = 0;
    put(app, cpu.eax * 4 + kSirenTone, cpu.edx);
    put(app, cpu.eax * 4 + kSirenTicks, cpu.edx);
    cpu.ebx = 0xffffffff;
    cpu.edx = 5;
    cpu.eax = sirenSound(app, cpu.eax);
    if (!call(app, cpu, 0x4e9420))
        return;
    leave(cpu, kept, kEbx | kEdx);
}

/* 0x417eb0: siren eax on, if it is not: steady (edx not 0), or warbling --
 * from either tone at random, for a random while. */
void sirenStart(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const unsigned pushed = kEbx | kEcx | kEsi | kEdi;
    cpu.ebp = cpu.esp = kept.frame(5);
    cpu.ecx = cpu.eax;
    cpu.ebx = cpu.eax * 4;
    if (at(app, cpu.ebx + kSirenOn) != 0)
        return leave(cpu, kept, pushed);
    cpu.edi = 1;
    put(app, cpu.ebx + kSirenOn, cpu.edi);
    if (cpu.edx != 0)
    {
        cpu.edx = 0xffffffff;
        put(app, cpu.ebx + kSirenTone, cpu.edi);
        put(app, cpu.ebx + kSirenSecond, cpu.edx);
        if (!call(app, cpu, 0x417e00))
            return;
        return leave(cpu, kept, pushed);
    }
    cpu.esi = 0x64;
    if (!call(app, cpu, kRandom))
        return;
    udiv(cpu, cpu.esi);
    if (cpu.edx > 0x32)
    {
        cpu.esi = 0x3c;
        cpu.edx = 0;
        put(app, cpu.ebx + kSirenTone, cpu.edi);
        if (!call(app, cpu, kRandom))
            return;
        udiv(cpu, cpu.esi);
        cpu.edx += 0x78;
        cpu.eax = cpu.ecx;
        put(app, cpu.ebx + kSirenSecond, cpu.edx);
        if (!call(app, cpu, 0x417db0))
            return;
        return leave(cpu, kept, pushed);
    }
    cpu.esi = 0x78;
    cpu.edx = 0;
    if (!call(app, cpu, kRandom))
        return;
    udiv(cpu, cpu.esi);
    cpu.edi = 0;
    put(app, cpu.ebx + kSirenTone, cpu.edi);
    cpu.edx += 0xf0;
    cpu.eax = cpu.ecx;
    put(app, cpu.ebx + kSirenFirst, cpu.edx);
    if (!call(app, cpu, 0x417cb0))
        return;
    leave(cpu, kept, pushed);
}

/* 0x417f60: siren eax off, faded out, its state as it starts. */
void sirenStop(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.ebp = cpu.esp = kept.frame(6);
    cpu.edx = cpu.eax;
    cpu.esi = 0xf0;
    cpu.ecx = 0;
    cpu.edi = 0x78;
    put(app, cpu.eax * 4 + kSirenOn, cpu.ecx);
    put(app, cpu.eax * 4 + kSirenTone, cpu.ecx);
    put(app, cpu.eax * 4 + kSirenFirst, cpu.esi);
    put(app, cpu.eax * 4 + kSirenSecond, cpu.edi);
    put(app, cpu.eax * 4 + kSirenTicks, cpu.ecx);
    cpu.ebx = 0xffffffff;
    cpu.edx = 5;
    cpu.eax = sirenSound(app, cpu.eax);
    if (!call(app, cpu, 0x4e9420))
        return;
    leave(cpu, kept, kEbx | kEcx | kEdx | kEsi | kEdi);
}

/* 0x417fd0: siren eax's tick: its tones turned when their ticks are up, its
 * volume edx, pitch ebx (16.10) and pan ecx set. */
void sirenTick(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const unsigned pushed = kEsi | kEdi;
    cpu.ebp = kept.frame(3);
    cpu.esp = cpu.ebp - 0xc;
    cpu.esi = cpu.eax;
    put(app, cpu.ebp - 0xc, cpu.edx);
    cpu.edi = cpu.ecx;
    cpu.ecx = cpu.eax * 4;
    if (at(app, cpu.ecx + kSirenOn) == 0)
        return leave(cpu, kept, pushed);
    if (at(app, cpu.ecx + kSirenTone) == 0)
    {
        cpu.edx = at(app, cpu.ecx + kSirenTicks) + 1;
        cpu.eax = cpu.edx;
        put(app, cpu.ecx + kSirenTicks, cpu.edx);
        if (cpu.eax == at(app, cpu.ecx + kSirenFirst))
        {
            cpu.eax = cpu.esi;
            cpu.edx = 0x3c;
            if (!call(app, cpu, 0x417d00))
                return;
            put(app, cpu.ebp - 4, cpu.edx);
            cpu.edx = 0;
            if (!call(app, cpu, kRandom))
                return;
            udiv(cpu, at(app, cpu.ebp - 4));
            cpu.edx += 0x78;
            cpu.eax = cpu.esi;
            put(app, cpu.ecx + kSirenSecond, cpu.edx);
            if (!call(app, cpu, 0x417db0))
                return;
        }
    }
    else
    {
        cpu.eax = at(app, cpu.ecx + kSirenTicks) + 1;
        cpu.edx = at(app, cpu.ecx + kSirenSecond);
        put(app, cpu.ecx + kSirenTicks, cpu.eax);
        if (cpu.eax == cpu.edx)
        {
            cpu.eax = cpu.esi;
            cpu.edx = 0x78;
            if (!call(app, cpu, 0x417e60))
                return;
            put(app, cpu.ebp - 4, cpu.edx);
            cpu.edx = 0;
            if (!call(app, cpu, kRandom))
                return;
            udiv(cpu, at(app, cpu.ebp - 4));
            cpu.edx += 0xf0;
            cpu.eax = cpu.esi;
            put(app, cpu.ecx + kSirenFirst, cpu.edx);
            if (!call(app, cpu, 0x417cb0))
                return;
        }
    }
    cpu.edx = cpu.ebx << 6;
    towardZero(cpu, 16);
    if (i32(cpu.eax) < 0)
        cpu.eax = 0;
    if (i32(cpu.eax) > 0x7f)
        cpu.eax = 0x7f;
    cpu.edx = cpu.eax;
    cpu.ebx = cpu.esi == 4 ? 0x10 : cpu.esi + 0x1b;
    cpu.eax = cpu.ebx * 8;
    put(app, cpu.ebp - 8, cpu.eax);
    cpu.eax = at(app, cpu.eax + kSlots);
    if (!call(app, cpu, 0x4e97e4))
        return;
    const reg32 v = at(app, 0x6fbbf4);
    cpu.eax = v;
    if (at(app, cpu.esi * 4 + kSirenSecond) == 0xffffffff)
    {
        cpu.ecx = v * 8 + v;
        cpu.eax = cpu.ecx;
        cpu.ecx = (cpu.ecx << 3) - cpu.eax;
    }
    else
    {
        cpu.ecx = v * 4 + v;
        cpu.eax = cpu.ecx;
        cpu.ecx = (cpu.ecx << 4) + cpu.eax;
    }
    cpu.edx = at(app, cpu.ebp - 0xc);
    cpu.edx = reg32(mul(i32(cpu.edx), i32(cpu.ecx)));
    cpu.eax = at(app, at(app, cpu.ebp - 8) + kSlots);
    cpu.edx = reg32(i32(cpu.edx) >> 14);
    if (!call(app, cpu, 0x4e95fc))
        return;
    cpu.esi = at(app, 0x6fbc00);
    cpu.eax = cpu.ebx * 8;
    if (cpu.esi == 2)
    {
        cpu.edx = cpu.edi;
        cpu.eax = at(app, cpu.eax + kSlots);
        cpu.ebx = 0;
        if (!call(app, cpu, 0x4e9850))
            return;
        return leave(cpu, kept, pushed);
    }
    if (at(app, 0x5525a4) != 0)
    {
        if (at(app, 0x55292c) != 0)
        {
            cpu.edx = cpu.edi;
            cpu.eax = at(app, cpu.eax + kSlots);
            cpu.ebx = 0;
        }
        else
        {
            cpu.eax = at(app, cpu.eax + kSlots);
            cpu.ebx = 0;
            cpu.edx = 0;
        }
        if (!call(app, cpu, 0x4e9850))
            return;
        return leave(cpu, kept, pushed);
    }
    if (at(app, 0x55292c) != 0)
    {
        cpu.edx = stereoPan(cpu.edi);
        cpu.eax = at(app, cpu.ebx * 8 + kSlots);
    }
    else
    {
        cpu.edx = 0x40;
        cpu.eax = at(app, cpu.eax + kSlots);
    }
    if (!call(app, cpu, 0x4e9950))
        return;
    leave(cpu, kept, pushed);
}

/* 0x4179d0 (stdcall 12): slot eax's noise edx -- 1 a car's, 0 the road's,
 * else another's -- at pitch ecx times ebx (16.16), as loud as [esp+4] (its
 * distance) is short of 0x15f (a car's) or 0x15f9, and as [esp+0xc] (its
 * speed) says; pan [esp+8].  Silent: the slot stopped. */
void noiseBySpeed(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const unsigned pushed = kEsi | kEdi;
    cpu.ebp = kept.frame(3);
    cpu.esp = cpu.ebp - 8;
    cpu.esi = cpu.eax;
    cpu.edi = cpu.edx;
    put(app, cpu.ebp - 8, cpu.ecx);
    if (at(app, kEffectsOn) == 0)
        return leave(cpu, kept, pushed, 0xc);
    const reg32 distance = at(app, cpu.ebp + 0x10);
    bool loudness = true;  // ecx made from eax at 0x417a69
    if (cpu.edi == 1)
    {
        cpu.ecx = distance;
        if (i32(cpu.ecx) < 0x15f)
        {
            cpu.edx = 0x15f - cpu.ecx;
            cpu.eax = (cpu.edx << 7) - cpu.edx;
            cpu.edx = cpu.eax;
            cpu.ecx = 0x15f;
            idiv(cpu, 0x15f);
        }
        else
        {
            cpu.ecx = 0;
            loudness = false;
        }
    }
    else
    {
        if (i32(distance) < 0x15f9)
        {
            cpu.edx = 0x15f9 - distance;
            cpu.ecx = distance;
            cpu.eax = (cpu.edx << 7) - cpu.edx;
            cpu.edx = cpu.eax;
            cpu.ecx = 0x15f9;
            idiv(cpu, 0x15f9);
        }
        else
            cpu.eax = 0;
        cpu.edx = reg32(mul(i32(cpu.ebx + 0x28), i32(cpu.eax)));
        towardZero(cpu, 7);
        if (i32(cpu.eax) > 0x7f)
            cpu.eax = 0x7f;
        if (i32(cpu.eax) < 0)
            cpu.eax = 0;
    }
    if (loudness)
        cpu.ecx = cpu.eax;
    cpu.eax = at(app, cpu.ebp + 0x18);
    cpu.edx = i32(cpu.eax) > 0 ? cpu.eax : 0u - cpu.eax;
    towardZero(cpu, 16);
    put(app, 0x57126c, cpu.eax);
    if (i32(cpu.eax) > 0x28)
        put(app, 0x57126c, 0x28);
    if (cpu.edi == 1)
    {
        cpu.edx = reg32(mul(s32(app, 0x57126c), i32(cpu.ecx)));
        cpu.ecx = 0x28;
        cpu.eax = cpu.edx;
        idiv(cpu, 0x28);
        cpu.ecx = cpu.eax * 8;
        cpu.edx = (cpu.ecx << 4) - cpu.ecx;
        cpu.ecx = 0x64;
        cpu.eax = cpu.edx;
        idiv(cpu, 0x64);
        cpu.ecx = cpu.eax;
    }
    if (cpu.edi == 0)
    {
        if (at(app, 0x55260c) != 0)
        {
            cpu.edx = reg32(mul(i32(0x15f9 - distance), i32(cpu.ecx)));
            cpu.ecx = at(app, 0x55260c);
            cpu.eax = cpu.edx;
            idiv(cpu, cpu.ecx);
            cpu.ecx = cpu.eax;
        }
        else
            cpu.ecx = 0;
        cpu.ecx <<= 3;
        cpu.edx = (cpu.ecx << 4) - cpu.ecx;
        cpu.ecx = 0x64;
        cpu.eax = cpu.edx;
        idiv(cpu, 0x64);
        cpu.ecx = cpu.eax;
        if (i32(cpu.eax) > 0x73)
            cpu.ecx = 0x73;
    }
    if (i32(cpu.ecx) > 0x7f)
        cpu.ecx = 0x7f;
    put(app, cpu.ebp - 4, cpu.ecx);
    if (cpu.ecx == 0 && cpu.esi != 0xffffffff)
    {
        if (at(app, cpu.esi * 8 + kSlots) != 0xffffffff)
        {
            cpu.eax = cpu.esi;
            if (!call(app, cpu, kSlotStop))
                return;
        }
        return leave(cpu, kept, pushed, 0xc);
    }
    cpu.edx = reg32(mul(s32(app, cpu.ebp - 8), i32(cpu.ebx)));
    const reg32 pan = at(app, cpu.ebp + 0x14);
    cpu.eax = pan;
    towardZero(cpu, 16);
    cpu.ecx = at(app, cpu.ebp - 4);
    cpu.ebx = cpu.eax;
    cpu.edx = cpu.edi;
    cpu.eax = cpu.esi;
    if (!call(app, cpu, kSlotPlay, {pan}))
        return;
    leave(cpu, kept, pushed, 0xc);
}

}  // namespace snd
}  // namespace nfs3hp
