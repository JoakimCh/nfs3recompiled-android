#include "native_snd.h"

/* The race's sound tick, native (native_snd.h says how): the listener put
 * where the player's camera is (0x4229c0) and its move worked out, then each
 * kind of the race's sounds updated in turn -- the cars about, the player's
 * own car, the cop cars' closeness, their sirens and engines -- for each
 * player in the split screen, or from the replay's camera (0x55fe30) where
 * one is used.
 *
 * The game's state: 0x570a78 the listener (its place, then its axes), 0x570ae4
 * and 0x570b34 each player's last place, 0x570af0 and 0x570b40 each player's
 * car, 0x570dcc the listener's direction, 0x55260c the cop cars' closeness. */
namespace nfs3hp
{
namespace snd
{

namespace
{

constexpr reg32 kListener = 0x570a78;

x86::Float f32(App* app, reg32 at) { return x86::Float(app->getMemory<float>(at)); }

/* fmul qword [scale]; fistp: st(0) scaled to an integer, popped. */
reg32 scaledTop(App* app, CPU& cpu, reg32 scale)
{
    x86::FPU& fpu = cpu.fpu;
    fpu.st(0) = fpu.mul(fpu.st(0), x86::Float(app->getMemory<double>(scale)));
    const reg32 n = reg32(fpu.toInteger<i32>(fpu.st(0)));
    fpu.pop();
    return n;
}

/* movsd, `count` times: esi's words to edi's, both moved on. */
void moveWords(App* app, CPU& cpu, reg32 count)
{
    for (; count > 0; --count, cpu.esi += 4, cpu.edi += 4)
        put(app, cpu.edi, at(app, cpu.esi));
}

/* The listener at player eax's camera, and its move since; its direction
 * that of the car ecx's (+0xa4), or the moved one's with the camera off it
 * (0x6fd3a0 2 and on). */
bool listenerAt(App* app, CPU& cpu, reg32 player, reg32 car)
{
    cpu.edx = kListener;
    cpu.ebx = 0;
    cpu.eax = player;
    if (!call(app, cpu, 0x4229c0))
        return false;
    cpu.edx = kListener;
    cpu.eax = player;
    cpu.ecx = at(app, car);
    if (!call(app, cpu, 0x410c40))
        return false;
    if (i32(at(app, 0x6fd3a0)) >= 2)
        put(app, 0x570dcc, 0x570dc0);
    else
    {
        cpu.ecx += 0xa4;
        put(app, 0x570dcc, cpu.ecx);
    }
    return true;
}

}  // namespace

/* 0x412220: the ebx cop cars nearest the listener (of the cars on the road,
 * 0x5efac8's, the cops' only -- in the split screen those of player eax --
 * within 0x4b0000) kept in cop sources edx on: those no longer near let go,
 * the new ones taken where a source is free. */
void copSourcesPick(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    x86::FPU& fpu = cpu.fpu;
    cpu.ebp = kept.frame(4);
    cpu.esp = cpu.ebp - 0x54;
    const reg32 b = cpu.ebp;
    // The nearest: (car, distance) pairs at ebp - 0x54.
    auto car = [&](reg32 i) { return b + i * 8 - 0x54; };
    auto distance = [&](reg32 i) { return b + i * 8 - 0x50; };
    put(app, b - 0x24, cpu.eax);
    put(app, b - 0x18, cpu.edx);
    cpu.ecx = cpu.ebx;
    cpu.eax = at(app, b - 0x18) << 3;
    cpu.edx = kListener;
    put(app, b - 0x14, cpu.edx);
    cpu.edx = cpu.eax;
    cpu.eax = (cpu.eax << 3) - cpu.edx;
    cpu.esi = 0x570b78 + cpu.eax;
    for (cpu.eax = 0; i32(cpu.eax) < i32(cpu.ecx);)
    {
        ++cpu.eax;
        cpu.ebx = 0;
        cpu.edi = 0x4b0000;
        put(app, b + cpu.eax * 8 - 0x5c, cpu.ebx);
        put(app, b + cpu.eax * 8 - 0x58, cpu.edi);
    }
    cpu.eax = 0;
    cpu.edx = 0x5efac8;
    put(app, b - 8, cpu.eax);
    for (;; cpu.edi = at(app, b - 8) + 1, cpu.edx += 4, put(app, b - 8, cpu.edi))
    {
        cpu.eax = at(app, b - 8);
        if (i32(cpu.eax) >= s32(app, 0x5efd9c))
            break;
        cpu.eax = at(app, cpu.edx);
        if ((byte(app, cpu.eax + 0x200) & 4) != 0)
        {
            if (s32(app, 0x6fd3b0) <= 1)
                continue;
            cpu.ebx = at(app, 0x6fd4f4);
            if (cpu.ebx == at(app, cpu.eax + 0x1f0))
                continue;
        }
        cpu.eax = at(app, cpu.edx);
        if ((byte(app, cpu.eax + 0x200) & 0x40) != 0 || byte(app, cpu.eax + 0x89) == 0)
            continue;
        cpu.ebx = at(app, cpu.eax + 0x98);
        put(app, b - 0x34, cpu.ebx);
        cpu.ebx = at(app, cpu.eax + 0x9c);
        cpu.eax = at(app, cpu.eax + 0xa0);
        put(app, b - 0x2c, cpu.eax);
        cpu.eax = at(app, b - 0x14);
        fpu.push(fpu.sub(f32(app, b - 0x34), f32(app, cpu.eax)));
        put(app, b - 0x30, cpu.ebx);
        cpu.eax = scaledTop(app, cpu, 0x536958);
        cpu.ebx = cpu.eax;
        cpu.eax = at(app, b - 0x14);
        fpu.push(fpu.sub(f32(app, b - 0x30), f32(app, cpu.eax + 4)));
        cpu.eax = scaledTop(app, cpu, 0x536958);
        cpu.edi = cpu.eax;
        cpu.eax = at(app, b - 0x14);
        fpu.push(fpu.sub(f32(app, b - 0x2c), f32(app, cpu.eax + 8)));
        cpu.eax = scaledTop(app, cpu, 0x536958);
        put(app, b - 0x10, cpu.eax);
        if (i32(cpu.ebx) <= 0)
            cpu.ebx = 0u - cpu.ebx;
        put(app, b - 0xc, cpu.ebx);
        cpu.ebx = i32(cpu.edi) > 0 ? cpu.edi : 0u - cpu.edi;
        cpu.eax = at(app, b - 0x10);
        if (i32(cpu.eax) <= 0)
            cpu.eax = 0u - cpu.eax;
        cpu.edi = at(app, b - 0xc);
        if (i32(cpu.eax) < i32(cpu.edi))
            cpu.eax = reg32(i32(cpu.eax) >> 2);
        else
            cpu.edi = reg32(i32(cpu.edi) >> 2);
        cpu.eax += cpu.edi;
        if (i32(cpu.eax) >= 0x4b0000)
            continue;
        if (i32(cpu.ebx) > i32(cpu.eax))
            cpu.eax = reg32(i32(cpu.eax) >> 2);
        else
            cpu.ebx = reg32(i32(cpu.ebx) >> 2);
        cpu.eax += cpu.ebx;
        put(app, b - 0x20, cpu.eax);
        if (i32(cpu.eax) >= 0x4b0000)
            continue;
        for (cpu.eax = 0; i32(cpu.eax) < i32(cpu.ecx); ++cpu.eax)
        {
            cpu.edi = at(app, b - 0x20);
            if (i32(cpu.edi) >= s32(app, distance(cpu.eax)))
                continue;
            // Moved down one to make room.
            cpu.ebx = cpu.ecx - 1;
            put(app, b - 4, cpu.ebx);
            for (;;)
            {
                cpu.edi = at(app, b - 4);
                if (i32(cpu.eax) >= i32(cpu.edi))
                    break;
                cpu.ebx = cpu.edi - 1;
                cpu.edi = at(app, car(cpu.edi - 1));
                put(app, car(cpu.ebx + 1), cpu.edi);
                cpu.edi = at(app, distance(cpu.ebx));
                put(app, b - 4, cpu.ebx);
                put(app, distance(cpu.ebx + 1), cpu.edi);
            }
            cpu.ebx = at(app, cpu.edx);
            put(app, car(cpu.eax), cpu.ebx);
            cpu.ebx = at(app, b - 0x20);
            put(app, distance(cpu.eax), cpu.ebx);
            break;
        }
    }
    // Sources whose car is not among the nearest: let go (-1); the nearest
    // a source has already: off the list.
    for (cpu.edx = 0; i32(cpu.edx) < i32(cpu.ecx); ++cpu.edx)
    {
        cpu.eax = cpu.edx * 8;
        cpu.ebx = cpu.eax;
        cpu.eax = (cpu.eax << 3) - cpu.ebx;
        if (at(app, cpu.esi + cpu.eax) == 0)
            continue;
        for (cpu.ebx = 0; i32(cpu.ebx) < i32(cpu.ecx); ++cpu.ebx)
        {
            put(app, b - 0x28, cpu.edx);
            cpu.eax = cpu.edx * 8;
            put(app, b - 0x28, cpu.eax);
            cpu.edi = at(app, b - 0x28);
            cpu.eax = (cpu.eax << 3) - cpu.edi;
            cpu.edi = cpu.esi + cpu.eax;
            cpu.eax = cpu.ebx * 8;
            put(app, b - 0x1c, cpu.eax);
            cpu.eax = at(app, cpu.eax + b - 0x54);
            if (cpu.eax == at(app, cpu.edi))
            {
                cpu.eax = at(app, b - 0x1c);
                cpu.edi = 0;
                put(app, cpu.eax + b - 0x54, cpu.edi);
                break;
            }
        }
        if (cpu.ebx == cpu.ecx)
        {
            cpu.eax = cpu.edx * 8;
            cpu.ebx = cpu.eax;
            cpu.eax = (cpu.eax << 3) - cpu.ebx;
            put(app, cpu.esi + cpu.eax, 0xffffffff);
        }
    }
    // The new ones into the free sources.
    for (cpu.edi = 0; i32(cpu.edi) < i32(cpu.ecx); ++cpu.edi)
    {
        if (at(app, car(cpu.edi)) == 0)
            continue;
        for (cpu.edx = 0; i32(cpu.edx) < i32(cpu.ecx); ++cpu.edx)
        {
            put(app, b - 0x28, cpu.edx);
            cpu.eax = cpu.edx * 8;
            put(app, b - 0x28, cpu.eax);
            cpu.ebx = at(app, b - 0x28);
            cpu.eax = (cpu.eax << 3) - cpu.ebx + cpu.esi;
            cpu.ebx = at(app, cpu.eax);
            if (cpu.ebx != 0 && cpu.ebx != 0xffffffff)
                continue;
            cpu.eax = at(app, car(cpu.edi));
            put(app, b - 0x28, cpu.eax);
            cpu.eax = at(app, b - 0x18);
            cpu.ebx = at(app, b - 0x24);
            cpu.eax += cpu.edx;
            cpu.edx = at(app, b - 0x28);
            if (!call(app, cpu, 0x4121b0))
                return;
            break;
        }
    }
    // The ones let go and not taken: reset.
    for (cpu.edi = 0; i32(cpu.edi) < i32(cpu.ecx); ++cpu.edi)
    {
        cpu.eax = cpu.edi * 8;
        cpu.edx = cpu.eax;
        cpu.eax = (cpu.eax << 3) - cpu.edx;
        if (at(app, cpu.esi + cpu.eax) != 0xffffffff)
            continue;
        cpu.eax = at(app, b - 0x18);
        cpu.ebx = at(app, b - 0x24);
        cpu.edx = 0;
        cpu.eax += cpu.edi;
        if (!call(app, cpu, 0x4121b0))
            return;
    }
    leave(cpu, kept, kEcx | kEsi | kEdi);
}

/* 0x411e60: cop source edx's sounds for player eax: from its car's place,
 * angle and distance -- the noise of its speed (by the gap in their +0x7c0
 * with the player's car, or its own +0x7c4), its knocks and scrapes, and
 * then its siren and radio (a cop), its engine (a racer), or a car's horn
 * now and then (+0x20 its ticks, +0x24 and +0x28 how long, +0x2c how many
 * times). */
void copCarSound(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    x86::FPU& fpu = cpu.fpu;
    const unsigned pushed = kEbx | kEcx | kEsi | kEdi;
    cpu.ebp = kept.frame(5);
    cpu.esp = cpu.ebp - 0x30;
    const reg32 b = cpu.ebp, place = b - 0x30;
    put(app, b - 0x18, cpu.eax);
    put(app, b - 4, cpu.edx);
    cpu.eax = cpu.edx * 8;
    cpu.edx = cpu.eax;
    cpu.eax = (cpu.eax << 3) - cpu.edx;
    cpu.esi = 0x570b78 + cpu.eax;
    cpu.edi = at(app, cpu.esi);
    if (cpu.edi == 0)
        return leave(cpu, kept, pushed);
    put(app, place, at(app, cpu.edi + 0x98));
    put(app, place + 4, at(app, cpu.edi + 0x9c));
    cpu.eax = at(app, cpu.edi + 0xa0);
    cpu.edx = cpu.edi + 0xa4;
    put(app, place + 8, cpu.eax);
    cpu.eax = place;
    if (!call(app, cpu, 0x4124d0))
        return;
    put(app, b - 0x10, cpu.eax);
    if (i32(cpu.eax) < 0)
        return leave(cpu, kept, pushed);
    if (at(app, 0x6fd3b0) == 1)
        cpu.eax = at(app, b - 0x18) != 0 ? 0xc000 : 0x3fff;
    else
    {
        cpu.edx = place;
        cpu.eax = kListener;
        if (!call(app, cpu, 0x410d30))
            return;
    }
    put(app, b - 8, cpu.eax);
    cpu.eax = at(app, b - 4);
    if (!call(app, cpu, 0x411db0))
        return;
    put(app, b - 0xc, cpu.eax);
    cpu.ecx = i32(cpu.eax) < 0x15f9 ? cpu.eax : 0x15f9;
    if (at(app, 0x570dcc) != 0)
    {
        cpu.edx = at(app, b - 0x18);
        cpu.eax = at(app, (((cpu.edx << 2) + cpu.edx) << 4) + 0x570af0);
        const float gap = float(fpu.sub(f32(app, cpu.edi + 0x7c0), f32(app, cpu.eax + 0x7c0)));
        app->getMemory<float>(b - 0x1c) = gap;
        // fldz; fcomp; jae: the gap as it is unless 0 is at or above it.
        if (fcomp(cpu, x86::Float(0.0), f32(app, b - 0x1c)).below)
        {
            cpu.eax = at(app, b - 0x1c);
            put(app, b - 0x20, cpu.eax);
        }
        else
            app->getMemory<float>(b - 0x20) = -gap;
        fpu.push(f32(app, b - 0x20));
    }
    else
        fpu.push(f32(app, cpu.edi + 0x7c4));
    cpu.eax = scaledTop(app, cpu, 0x536950);
    put(app, cpu.esi + 0xc, cpu.eax);
    cpu.edx = at(app, cpu.edi + 0x590);
    if (i32(cpu.edx) > 0x1770)
        cpu.edx = 0x1770;
    cpu.eax = at(app, at(app, at(app, cpu.esi) + 0x220) + 0x14);
    if ((byte(app, cpu.edi + 0x200) & 0x10) != 0)
        cpu.eax = 0x54;
    else
    {
        cpu.eax = at(app, at(app, cpu.edi + 0x528) + 0x1c4) + 0x7d0;
        put(app, b - 0x24, cpu.eax);
        cpu.eax = (cpu.edx << 7) - cpu.edx;
        cpu.edx = cpu.eax;
        cpu.ebx = at(app, b - 0x24);
        idiv(cpu, cpu.ebx);
    }
    cpu.eax -= 0xa;
    if (i32(cpu.eax) < 0)
        cpu.eax = 0;
    cpu.ebx = at(app, b - 0xc);
    cpu.edx = at(app, cpu.esi + 0xc);
    put(app, cpu.esi + 0x14, cpu.ecx);
    const reg32 speed = cpu.edx;
    cpu.ecx = at(app, b - 8);
    put(app, cpu.esi + 0x18, cpu.eax);
    const reg32 angle = cpu.ecx, near = cpu.ebx;
    setByte0(cpu.edx, byte(app, cpu.edi + 0x200));
    cpu.ecx = at(app, b - 0x10);
    cpu.ebx = cpu.eax;
    cpu.edx = (reg8(cpu.edx) & 0x10) != 0 ? 1 : 0;
    cpu.eax = at(app, b - 4) + 4;
    if (!call(app, cpu, 0x4179d0, {near, angle, speed}))
        return;
    // The car's knocks and scrapes, from the last.
    put(app, b - 0x14, at(app, cpu.edi + 0x7dc) - 1);
    for (; i32(at(app, b - 0x14)) >= 0; put(app, b - 0x14, at(app, b - 0x14) - 1))
    {
        cpu.eax = at(app, b - 0x14);
        cpu.edx = cpu.eax;
        cpu.eax = cpu.eax * 24 + cpu.edi;
        const reg32 knockAngle = at(app, b - 8), distance = at(app, b - 0xc);
        if (i32(at(app, cpu.eax + 0x7e4)) > -1)
        {
            cpu.ecx = knockAngle;
            cpu.ebx = distance;
            cpu.edx = at(app, cpu.eax + 0x7e8);
            cpu.ecx = at(app, cpu.eax + 0x7f0);
            cpu.ebx = at(app, cpu.eax + 0x7ec);
            cpu.eax = at(app, b - 4) + 0x16;
        }
        else
        {
            cpu.edx = knockAngle;
            cpu.ecx = distance;
            cpu.ebx = at(app, cpu.eax + 0x7ec);
            cpu.edx = at(app, cpu.eax + 0x7e8);
            cpu.ecx = at(app, cpu.eax + 0x7f0);
            cpu.eax = 0xffffffff;
        }
        if (!call(app, cpu, 0x417b80, {distance, knockAngle}))
            return;
    }
    cpu.eax = at(app, cpu.esi);
    setByte1(cpu.edx, byte(app, cpu.eax + 0x200));
    const reg8 kind = reg8(cpu.edx >> 8);
    if ((kind & 0x20) != 0)
    {
        if ((byte(app, cpu.eax + 0x710) & 0x10) != 0)
        {
            cpu.ecx = at(app, b - 0xc);
            cpu.ebx = at(app, b - 0x10);
            cpu.edx = at(app, b - 8);
            cpu.eax = at(app, b - 4);
            if (!call(app, cpu, 0x411c50))
                return;
            put(app, cpu.esi + 0x20, 1);
        }
        else if (at(app, cpu.esi + 0x20) != 0)
        {
            cpu.eax = at(app, b - 4);
            if (!call(app, cpu, 0x411ca0))
                return;
            put(app, cpu.esi + 0x20, 0);
        }
        cpu.edx = at(app, b - 0x18);
        cpu.ecx = at(app, b - 0xc);
        cpu.ebx = at(app, b - 0x10);
        const reg32 player = cpu.edx;
        cpu.eax = cpu.edi;
        cpu.edx = at(app, b - 8);
        if (!call(app, cpu, 0x4c8810, {player}))
            return;
        return leave(cpu, kept, pushed);
    }
    auto engine = [&] {
        cpu.ecx = at(app, b - 0xc);
        cpu.ebx = at(app, b - 0x10);
        cpu.edx = at(app, b - 8);
        cpu.eax = at(app, b - 4);
    };
    if ((kind & 4) != 0)
    {
        if (byte(app, cpu.edi + 0x50e) != 0)
        {
            engine();
            if (!call(app, cpu, 0x411cb0))
                return;
            put(app, cpu.esi + 0x20, 1);
        }
        else if (at(app, cpu.esi + 0x20) != 0)
        {
            cpu.eax = at(app, b - 4);
            if (!call(app, cpu, 0x411da0))
                return;
            put(app, cpu.esi + 0x20, 0);
        }
        return leave(cpu, kept, pushed);
    }
    cpu.ebx = at(app, cpu.esi + 0x20);
    if (i32(cpu.ebx) > 0)
    {
        if (s32(app, cpu.esi + 0x24) > 0)
        {
            cpu.edx = cpu.ebx - 1;
            put(app, cpu.esi + 0x20, cpu.edx);
        }
        if (at(app, cpu.esi + 0x20) == 0)
        {
            cpu.eax = at(app, b - 4);
            putByte(app, cpu.edi + 0x50e, 0);
            if (!call(app, cpu, 0x411da0))
                return;
            cpu.ebx = at(app, cpu.esi + 0x2c) - 1;
            put(app, cpu.esi + 0x2c, cpu.ebx);
            if (cpu.ebx != 0)
            {
                cpu.eax = at(app, cpu.esi + 0x28);
                put(app, cpu.esi + 0x20, cpu.eax);
            }
            return leave(cpu, kept, pushed);
        }
        engine();
        putByte(app, cpu.edi + 0x50e, 1);
        if (!call(app, cpu, 0x411cb0))
            return;
        return leave(cpu, kept, pushed);
    }
    if (i32(cpu.ebx) < 0)
    {
        cpu.edx = cpu.ebx + 1;
        put(app, cpu.esi + 0x20, cpu.edx);
        if (cpu.edx == 0)
        {
            cpu.eax = at(app, cpu.esi + 0x24);
            put(app, cpu.esi + 0x20, cpu.eax);
        }
    }
    leave(cpu, kept, pushed);
}

/* 0x411410: the race's sound tick. */
void raceSoundTick(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const unsigned pushed = kEbx | kEcx | kEdx | kEsi | kEdi;
    cpu.ebp = cpu.esp = kept.frame(6);
    if (at(app, 0x6fd3b0) == 1)
    {
        if (!listenerAt(app, cpu, 0, 0x570af0))
            return;
        cpu.ebx = 1;
        cpu.edx = 0;
        cpu.eax = 0;
        if (!call(app, cpu, 0x412220))
            return;
        cpu.eax = 0;
        cpu.edi = 0x570ae4;
        if (!call(app, cpu, 0x410e30))
            return;
        cpu.eax = 0;
        cpu.edx = 0;
        if (!call(app, cpu, 0x4117a0))
            return;
        cpu.eax = 1;
        cpu.esi = kListener;
        if (!call(app, cpu, 0x411e20))
            return;
        put(app, 0x55260c, cpu.eax);
        cpu.edx = 0;
        cpu.eax = 0;
        cpu.ebx = 0;
        if (!call(app, cpu, 0x411e60))
            return;
        cpu.edx = kListener;
        cpu.eax = 1;
        moveWords(app, cpu, 3);
        if (!call(app, cpu, 0x4229c0))
            return;
        cpu.edx = kListener;
        cpu.eax = 1;
        cpu.ecx = at(app, 0x570b40);
        if (!call(app, cpu, 0x410c40))
            return;
        if (i32(at(app, 0x6fd3a0)) >= 2)
            put(app, 0x570dcc, 0x570dc0);
        else
        {
            cpu.ecx += 0xa4;
            put(app, 0x570dcc, cpu.ecx);
        }
        cpu.eax = 1;
        if (!call(app, cpu, 0x4117a0))
            return;
        cpu.eax = 1;
        cpu.ebx = 1;
        if (!call(app, cpu, 0x410e30))
            return;
        cpu.edx = cpu.ebx;
        cpu.eax = cpu.ebx;
        if (!call(app, cpu, 0x412220))
            return;
        cpu.edx = 1;
        cpu.eax = cpu.edx;
        cpu.edi = 0x570b34;
        if (!call(app, cpu, 0x411e20))
            return;
        cpu.edx = 1;
        put(app, 0x55260c, cpu.eax);
        cpu.eax = cpu.edx;
        cpu.esi = kListener;
        if (!call(app, cpu, 0x411e60))
            return;
        moveWords(app, cpu, 3);
        return leave(cpu, kept, pushed);
    }
    if (at(app, 0x55fe30) == 0)
    {
        if (!listenerAt(app, cpu, 0, 0x570af0))
            return;
    }
    else
    {
        cpu.esi = 0x7a3d1c;
        cpu.edi = kListener;
        moveWords(app, cpu, 0x18);
        cpu.ecx = 0;
        cpu.edi = 0;
        put(app, 0x570dcc, cpu.edi);
    }
    cpu.ebx = 4;
    cpu.edx = 0;
    cpu.eax = 0;
    if (!call(app, cpu, 0x412220))
        return;
    cpu.eax = 0;
    if (!call(app, cpu, 0x410e30))
        return;
    cpu.edx = 0;
    cpu.eax = 4;
    if (!call(app, cpu, 0x411e20))
        return;
    put(app, 0x55260c, cpu.eax);
    cpu.eax = 0;
    cpu.edx = 0;
    if (!call(app, cpu, 0x4117a0))
        return;
    for (reg32 cop = 0; cop < 4; ++cop)
    {
        // The first with edx as 0x4117a0 leaves it.
        if (cop != 0)
            cpu.edx = cop;
        cpu.eax = 0;
        if (cop == 2)
            cpu.edi = 0x570ae4;
        if (cop == 3)
            cpu.esi = kListener;
        if (!call(app, cpu, 0x411e60))
            return;
    }
    moveWords(app, cpu, 3);
    leave(cpu, kept, pushed);
}

}  // namespace snd
}  // namespace nfs3hp
