#include "native_snd.h"

#include <cstdint>

/* The track's own sounds, native (native_snd.cpp says how): of the sound
 * objects the track's sections hold near the listener (0x552600's lists,
 * 0x570dd0's sound table, 18 bytes an object), the two nearest -- kept in
 * the order they had (0x570dd4, 0x570dd8) -- each played in its slot (0x14
 * on, the second player's 0x22) at the volume its distance and range give,
 * from its place; some only within a stretch of the road, some every so
 * many laps, some fading in and out over their stretch.  The x87 as the
 * game's code has it. */
namespace nfs3hp
{
namespace snd
{

namespace
{

constexpr reg32 kFar = 0x27100000;

x86::Float f32(App* app, reg32 at) { return x86::Float(app->getMemory<float>(at)); }

/* fld dword [at]; fmul qword [scale]; fistp. */
reg32 scaledFloat(App* app, CPU& cpu, reg32 at, reg32 scale)
{
    x86::FPU& fpu = cpu.fpu;
    return reg32(fpu.toInteger<i32>(fpu.mul(f32(app, at), x86::Float(app->getMemory<double>(scale)))));
}

/* fild dword of `value`; fmul qword [scale]: a float of it. */
float scaledInt(App* app, CPU& cpu, reg32 value, reg32 scale)
{
    return float(cpu.fpu.mul(x86::Float(x86::sreg32(value)), x86::Float(app->getMemory<double>(scale))));
}

/* The code's sar of a word's dword by 16: the signed word 2 above it. */
reg32 high(App* app, reg32 address) { return reg32(i32(at(app, address)) >> 16); }

/* rep movsd, 8 words. */
void moveEntry(App* app, CPU& cpu, reg32 to, reg32 from)
{
    cpu.edi = to;
    cpu.esi = from;
    for (cpu.ecx = 8; cpu.ecx > 0; --cpu.ecx, cpu.esi += 4, cpu.edi += 4)
        put(app, cpu.edi, at(app, cpu.esi));
}

}  // namespace

/* 0x410e30: player eax's track sounds. */
void trackSounds(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const unsigned pushed = kEbx | kEcx | kEdx | kEsi | kEdi;
    const reg32 frame = kept.frame(6);
    cpu.esp = frame - 0xd8;
    cpu.ebp = frame - 0x82;
    const reg32 b = cpu.ebp, entries = b - 0x56;
    put(app, b + 0x6a, cpu.eax);
    cpu.ecx = 0x552600;
    cpu.edx = 0x570a78;
    cpu.ebx = at(app, 0x570dd0);
    put(app, b + 0x5a, cpu.ecx);
    put(app, b + 0x62, cpu.edx);
    if (cpu.ebx == 0)
        return leave(cpu, kept, pushed);
    if (!call(app, cpu, 0x41bc20))
        return;
    if (cpu.eax == 0)
        return leave(cpu, kept, pushed);
    cpu.esi = 2;
    cpu.eax = entries;
    cpu.edx = 0;
    put(app, b + 0x56, cpu.esi);
    for (; i32(cpu.edx) < s32(app, b + 0x56); ++cpu.edx)
    {
        cpu.eax += 0x20;
        put(app, cpu.eax - 4, 0xffffffff);
        put(app, cpu.eax - 0x10, kFar);
    }
    cpu.eax = 0;
    put(app, b + 0x52, cpu.eax);
    // The sections' lists of objects, each object a record (its length a
    // word first, its kind at +2: 3 a sound's).
    for (;; put(app, b + 0x5a, at(app, b + 0x5a) + 4))
    {
        cpu.eax = at(app, b + 0x5a);
        cpu.edx = at(app, cpu.eax);
        if (cpu.edx == 0)
            break;
        cpu.ecx = at(app, cpu.edx);
        cpu.eax = cpu.edx;
        if (cpu.ecx == 0)
            continue;
        cpu.edx = 0;
        cpu.eax = cpu.ecx + 8;
        cpu.edx = half(app, cpu.ecx + 6);
        put(app, b + 0x6e, cpu.eax);
        put(app, b + 0x4a, cpu.edx);
        for (;;)
        {
            cpu.ebx = at(app, b + 0x4a) - 1;
            put(app, b + 0x4a, cpu.ebx);
            if (cpu.ebx == 0xffffffff)
                break;
            cpu.eax = at(app, b + 0x6e);
            if (byte(app, cpu.eax + 2) == 3)
            {
                cpu.edx = at(app, b + 0x52);
                cpu.eax = (cpu.edx * 9) * 2 + at(app, 0x570dd0);
                cpu.edx = high(app, cpu.eax + 2);
                if (i32(cpu.edx) > -1)
                {
                    // Its place (0x40f6d0's, at this tick), how near.
                    cpu.edx = at(app, b + 0x6e);
                    cpu.ecx = b + 0x2e;
                    cpu.ebx = at(app, 0x7d3684);
                    cpu.esi = reg32(shalf(app, cpu.eax));
                    put(app, b + 0x42, cpu.edx);
                    setByte0(cpu.ebx, reg8(cpu.ebx) & 0xfe);
                    cpu.eax = high(app, cpu.eax);
                    cpu.ebx += cpu.eax;
                    cpu.eax = at(app, b + 0x6e);
                    cpu.edx = 1;
                    if (!call(app, cpu, 0x40f6d0, {b + 0x3e, b + 0x3a}))
                        return;
                    const reg32 l = at(app, b + 0x62);
                    cpu.eax = scaledFloat(app, cpu, l, 0x536930);
                    cpu.edx = at(app, b + 0x2e) - cpu.eax;
                    cpu.eax = scaledFloat(app, cpu, l + 8, 0x536930);
                    cpu.ecx = at(app, b + 0x36) - cpu.eax;
                    cpu.esi <<= 16;
                    cpu.eax = cpu.ecx;
                    if (i32(cpu.edx) <= 0)
                        cpu.edx = 0u - cpu.edx;
                    if (i32(cpu.eax) <= 0)
                        cpu.eax = 0u - cpu.eax;
                    if (i32(cpu.edx) > i32(cpu.eax))
                        cpu.eax = reg32(i32(cpu.eax) >> 2);
                    else
                        cpu.edx = reg32(i32(cpu.edx) >> 2);
                    cpu.eax += cpu.edx;
                    cpu.edx = cpu.eax;
                    bool near = i32(cpu.eax) < i32(cpu.esi);
                    if (near)
                    {
                        cpu.eax = scaledFloat(app, cpu, l + 4, 0x536930);
                        cpu.ecx = at(app, b + 0x32) - cpu.eax;
                        cpu.eax = i32(cpu.ecx) > 0 ? cpu.ecx : 0u - cpu.ecx;
                        if (i32(cpu.eax) > i32(cpu.edx))
                            cpu.edx = reg32(i32(cpu.edx) >> 2);
                        else
                            cpu.eax = reg32(i32(cpu.eax) >> 2);
                        cpu.eax += cpu.edx;
                        put(app, b + 0x46, cpu.eax);
                        near = i32(cpu.eax) < i32(cpu.esi);
                    }
                    if (near)
                    {
                        // Among the nearest two, by distance.
                        cpu.edx = entries;
                        for (cpu.eax = 0;; cpu.edx += 0x20, ++cpu.eax)
                        {
                            cpu.edi = at(app, b + 0x56);
                            if (i32(cpu.eax) >= i32(cpu.edi))
                                break;
                            cpu.ecx = at(app, b + 0x46);
                            if (i32(cpu.ecx) >= s32(app, cpu.edx + 0x10))
                                continue;
                            for (cpu.ebx = cpu.edi - 1; i32(cpu.ebx) > i32(cpu.eax);)
                            {
                                const reg32 s = cpu.ebx << 5;
                                --cpu.ebx;
                                moveEntry(app, cpu, s + entries, s + b - 0x76);
                            }
                            cpu.eax = at(app, b + 0x46);
                            cpu.esi = b + 0x2e;
                            cpu.edi = cpu.edx + 4;
                            put(app, cpu.edx + 0x10, cpu.eax);
                            cpu.eax = at(app, b + 0x42);
                            for (reg32 k = 0; k < 3; ++k, cpu.esi += 4, cpu.edi += 4)
                                put(app, cpu.edi, at(app, cpu.esi));
                            put(app, cpu.edx, cpu.eax);
                            put(app, cpu.edx + 0x14, at(app, b + 0x3e));
                            put(app, cpu.edx + 0x18, at(app, b + 0x3a));
                            cpu.eax = at(app, b + 0x52);
                            put(app, cpu.edx + 0x1c, cpu.eax);
                            break;
                        }
                    }
                }
                put(app, b + 0x52, at(app, b + 0x52) + 1);
            }
            cpu.edx = at(app, b + 0x6e);
            cpu.eax = half(app, cpu.edx);
            cpu.edi = cpu.edx + cpu.eax;
            put(app, b + 0x6e, cpu.edi);
        }
    }
    // Kept in the slots they had.
    cpu.edx = at(app, b - 0x1a);
    if (cpu.edx == at(app, 0x570dd4) || at(app, b - 0x3a) == at(app, 0x570dd8))
    {
        moveEntry(app, cpu, b - 0x16, entries);
        moveEntry(app, cpu, entries, b - 0x36);
        moveEntry(app, cpu, b - 0x36, b - 0x16);
    }
    cpu.eax = at(app, b - 0x3a);
    cpu.esi = entries;
    cpu.ebx = 0;
    put(app, 0x570dd4, cpu.eax);
    cpu.eax = at(app, b - 0x1a);
    put(app, b + 0x72, cpu.ebx);
    put(app, 0x570dd8, cpu.eax);
    for (; cpu.eax = at(app, b + 0x72), i32(cpu.eax) < s32(app, b + 0x56);
         cpu.edx = at(app, b + 0x72) + 1, cpu.esi += 0x20, put(app, b + 0x72, cpu.edx))
    {
        const reg32 player = at(app, b + 0x6a), i = at(app, b + 0x72);
        cpu.eax = player != 0 ? 0x22 : 0x14;
        cpu.edx = i + cpu.eax;
        put(app, b + 0x5e, cpu.edx);
        auto stop = [&] {
            cpu.eax = at(app, b + 0x5e);
            return call(app, cpu, 0x416f60);
        };
        if (s32(app, cpu.esi + 0x10) >= i32(kFar))
        {
            if (!stop())
                return;
            continue;
        }
        // The object's sound: its range (a word), its effect, its stretch.
        cpu.edx = at(app, cpu.esi + 0x1c);
        cpu.edi = cpu.edx * 18 + at(app, 0x570dd0);
        cpu.eax = at(app, cpu.esi + 0x10);
        cpu.edx = cpu.eax;
        towardZero(cpu, 16);
        cpu.ecx = reg32(shalf(app, cpu.edi));
        cpu.ecx = reg32(mul(i32(cpu.ecx), i32(cpu.ecx)));
        put(app, b + 0x7a, cpu.eax);
        cpu.eax = reg32(mul(i32(cpu.eax), i32(cpu.eax)));
        cpu.edx = cpu.ecx - cpu.eax;
        cpu.eax = (cpu.edx << 7) - cpu.edx;
        idiv(cpu, cpu.ecx);
        for (reg32 k = 0; k < 12; k += 4)
            app->getMemory<float>(b + 0xa + k) = scaledInt(app, cpu, at(app, cpu.esi + 4 + k), 0x536938);
        cpu.edx = b + 0xa;
        put(app, b + 0x7a, cpu.eax);
        cpu.eax = at(app, b + 0x62);
        if (!call(app, cpu, 0x410d30))
            return;
        put(app, b + 0x66, cpu.eax);
        // Its direction: from its place a tick on, to its own.
        cpu.ecx = b + 0x2e;
        cpu.ebx = at(app, 0x7d3684) - 0x20 + high(app, cpu.edi);
        cpu.edx = 1;
        cpu.eax = at(app, cpu.esi);
        if (!call(app, cpu, 0x40f6d0, {b + 0x3e, b + 0x3a}))
            return;
        cpu.edx = at(app, b + 0x2e);
        cpu.eax = (at(app, cpu.esi + 4) - cpu.edx) * 2;
        cpu.ecx = at(app, b + 0x32);
        put(app, b + 0x16, cpu.eax);
        cpu.eax = (at(app, cpu.esi + 8) - cpu.ecx) * 2;
        cpu.ebx = at(app, b + 0x36);
        put(app, b + 0x1a, cpu.eax);
        cpu.eax = (at(app, cpu.esi + 0xc) - cpu.ebx) * 2;
        put(app, b + 0x1e, cpu.eax);
        for (reg32 k = 0; k < 12; k += 4)
            app->getMemory<float>(b + 0x22 + k) = scaledInt(app, cpu, at(app, b + 0x16 + k), 0x536938);
        put(app, b + 0x7e, at(app, b + 0x1e));
        cpu.edx = b + 0x22;
        cpu.eax = b + 0xa;
        if (!call(app, cpu, 0x4124d0))
            return;
        put(app, b + 0x4e, cpu.eax);
        cpu.eax = high(app, cpu.edi + 2);
        put(app, b + 0x76, cpu.eax);
        // Plays (pan, the side's bit) at a volume, ecx its ahead unless silent.
        auto play = [&](reg32 slotOrEffect, reg32 effect, bool lineSlot) {
            const reg32 side = player << 5, pan = at(app, b + 0x66), volume = at(app, b + 0x7a);
            cpu.ecx = volume != 0 || !lineSlot ? at(app, b + 0x4e) : 0;
            cpu.ebx = 0x40;
            cpu.edx = effect;
            cpu.eax = slotOrEffect;
            return call(app, cpu, 0x416fc0, {volume, pan, side});
        };
        cpu.eax = at(app, b + 0x5e);
        cpu.edx = at(app, cpu.eax * 8 + 0x570dec);
        cpu.eax = high(app, cpu.edi + 0xc);
        bool done = false;
        if (cpu.edx == cpu.eax || cpu.edx == high(app, cpu.edi + 0xe))
        {
            // The slot already playing one of its other effects: on with it.
            cpu.eax = at(app, b + 0x5e);
            cpu.eax = at(app, cpu.eax * 8 + 0x570de8);
            if (!call(app, cpu, 0x4e8fd0))
                return;
            if (cpu.eax == 0)
            {
                const reg32 effect = at(app, at(app, b + 0x5e) * 8 + 0x570dec);
                cpu.edi = at(app, b + 0x66);
                cpu.eax = at(app, b + 0x7a);
                cpu.ecx = at(app, b + 0x4e);
                const reg32 side = player << 5, pan = cpu.edi, volume = cpu.eax;
                cpu.eax = at(app, b + 0x72) + 0x14;
                cpu.ebx = 0x40;
                cpu.edx = effect;
                if (!call(app, cpu, 0x416fc0, {volume, pan, side}))
                    return;
                continue;
            }
        }
        if (!done && half(app, cpu.edi + 0xe) == 0xfffe)
        {
            // Once at these laps' stretches.
            cpu.eax = high(app, cpu.edi + 6);
            cpu.edx = at(app, cpu.esi + 0x14);
            if (cpu.eax == cpu.edx || high(app, cpu.edi + 8) == cpu.edx || high(app, cpu.edi + 0xa) == cpu.edx)
            {
                if (!play(0x13, 0u - high(app, cpu.edi + 0xe), true))
                    return;
                done = true;
            }
        }
        if (!done && half(app, cpu.edi + 0xe) == 0xfffd)
        {
            // Every so many laps.
            cpu.eax = at(app, cpu.esi + 0x14);
            cpu.ecx = high(app, cpu.edi + 6);
            idiv(cpu, cpu.ecx);
            if (cpu.edx == 0)
            {
                if (!play(0x13, 0u - high(app, cpu.edi + 0xe), true))
                    return;
                done = true;
            }
        }
        if (!done)
        {
            // Within its stretch, its own effect; fading in and out at its
            // ends.
            cpu.eax = high(app, cpu.edi + 0xc);
            bool set = false;
            if (i32(cpu.eax) > -1)
            {
                cpu.edx = high(app, cpu.edi + 4);
                cpu.ecx = at(app, cpu.esi + 0x14);
                if (i32(cpu.edx) <= i32(cpu.ecx))
                {
                    cpu.edx = high(app, cpu.edi + 6);
                    if (i32(cpu.edx) > i32(cpu.ecx))
                    {
                        put(app, b + 0x76, cpu.eax);
                        set = true;
                    }
                }
            }
            if (!set)
            {
                cpu.eax = high(app, cpu.edi + 0xe);
                if (i32(cpu.eax) > -1)
                {
                    cpu.edx = high(app, cpu.edi + 8);
                    cpu.ecx = at(app, cpu.esi + 0x18) - cpu.edx;
                    cpu.edx = cpu.ecx;
                    if (i32(cpu.edx) <= s32(app, cpu.esi + 0x14))
                    {
                        cpu.edx = high(app, cpu.edi + 0xa);
                        cpu.ecx = at(app, cpu.esi + 0x18);
                        cpu.ebx = at(app, cpu.esi + 0x14);
                        cpu.ecx -= cpu.edx;
                        if (i32(cpu.ecx) > i32(cpu.ebx))
                        {
                            put(app, b + 0x76, cpu.eax);
                            set = true;
                        }
                    }
                }
            }
            if (!set)
            {
                cpu.eax = high(app, cpu.edi + 4);
                if (i32(cpu.eax) > -1)
                {
                    cpu.edx = at(app, cpu.esi + 0x14);
                    bool divide = false;
                    if (i32(cpu.eax) >= i32(cpu.edx))
                        put(app, b + 0x76, 0xffffffff);
                    else
                    {
                        cpu.ecx = high(app, cpu.edi + 6);
                        if (i32(cpu.ecx) > i32(cpu.edx))
                        {
                            cpu.edi = at(app, b + 0x7a);
                            cpu.edx = reg32(mul(i32(cpu.edx - cpu.eax), i32(cpu.edi)));
                            cpu.ecx -= cpu.eax;
                            divide = true;
                        }
                        else
                        {
                            cpu.ebx = high(app, cpu.edi + 0xa);
                            cpu.eax = at(app, cpu.esi + 0x18) - cpu.ebx;
                            if (i32(cpu.eax) <= i32(cpu.edx))
                                put(app, b + 0x76, 0xffffffff);
                            else
                            {
                                cpu.ecx = high(app, cpu.edi + 8);
                                cpu.edx = at(app, cpu.esi + 0x18);
                                cpu.edi = at(app, cpu.esi + 0x14);
                                cpu.edx -= cpu.ecx;
                                if (i32(cpu.edx) < i32(cpu.edi))
                                {
                                    cpu.edx = at(app, b + 0x7a);
                                    cpu.eax -= cpu.edi;
                                    cpu.edx = reg32(mul(i32(cpu.edx), i32(cpu.eax)));
                                    cpu.ecx -= cpu.ebx;
                                    divide = true;
                                }
                            }
                        }
                    }
                    if (divide)
                    {
                        cpu.eax = cpu.edx;
                        idiv(cpu, cpu.ecx);
                        put(app, b + 0x7a, cpu.eax);
                    }
                }
            }
        }
        if (!done)
        {
            if (s32(app, b + 0x76) < 0)
            {
                if (!stop())
                    return;
                continue;
            }
            if (!play(at(app, b + 0x72) + 0x14, at(app, b + 0x76), true))
                return;
        }
    }
    leave(cpu, kept, pushed);
}

}  // namespace snd
}  // namespace nfs3hp
