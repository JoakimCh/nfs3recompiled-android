#include "native_snd.h"

/* The race's sound sources, native (native_snd.h says how): the players'
 * listeners and the four cars the cops' sounds follow, reset as a race
 * starts; a cop car's siren and engine played from its place; how close the
 * cop cars are.
 *
 * The game's state: 0x570ad8 the players' sources (0x50 bytes each, the car
 * at +0x18), 0x570b78 the cop cars' (0x38 bytes each: the car first, its
 * source from +0x18, its chase at +0x20..+0x2c), 0x552608 the sources with a
 * car (at most 4), 0x570a78 the listener's place, 0x552744 each car's
 * engine bank, 0x55276c each model's engine pitch (a byte). */
namespace nfs3hp
{
namespace snd
{

namespace
{

constexpr reg32 kSources = 0x552608, kPlayers = 0x570ad8, kCops = 0x570b78;

}  // namespace

/* 0x411620: source eax reset, for car edx (0: none). */
void sourceReset(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.ebp = cpu.esp = kept.frame(2);
    cpu.ecx = at(app, kSources);
    put(app, cpu.eax + 4, 0xffffffff);
    put(app, cpu.eax + 8, 0xffffffff);
    put(app, cpu.eax + 0x10, 0);
    put(app, cpu.eax + 0x20, 0);
    put(app, cpu.eax + 0x14, 0x15f9);
    put(app, cpu.eax + 0x18, 0);
    put(app, cpu.eax + 0x1c, 0xffffffff);
    put(app, cpu.eax, cpu.edx);
    if (cpu.edx != 0)
        ++cpu.ecx;
    if (i32(cpu.ecx) > 4)
        cpu.ecx = 4;
    put(app, kSources, cpu.ecx);
    leave(cpu, kept, kEcx);
}

/* 0x411680: the sources reset as a race starts: the players' (each with its
 * car -- the first's, or each player's own in the split screen) and the cop
 * cars'. */
void sourcesReset(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.ebp = cpu.esp = kept.frame(5);
    setByte1(cpu.eax, 4);
    cpu.ecx = kPlayers;
    cpu.esi = kCops;
    putByte(app, 0x552858, 4);
    cpu.eax = at(app, 0x6fd4ac);
    cpu.edx = 0;
    cpu.ebx = 0;
    cpu.eax = at(app, cpu.eax * 4 + 0x552744);
    put(app, kSources, cpu.edx);
    put(app, 0x570dd0, cpu.eax);
    for (; i32(cpu.ebx) < 2; cpu.ecx += 0x50, ++cpu.ebx)
    {
        put(app, cpu.ecx, 0xffffffff);
        cpu.eax = cpu.ecx + 0x18;
        put(app, cpu.ecx + 4, 0);
        cpu.edx = 0;
        put(app, cpu.ecx + 8, 0);
        if (!call(app, cpu, 0x411620))
            return;
        if (s32(app, 0x6fd3b0) <= 1)
        {
            if (i32(cpu.ebx) < s32(app, 0x5efda4))
            {
                cpu.eax = at(app, cpu.ebx * 4 + 0x5efa48);
                put(app, cpu.ecx + 0x18, cpu.eax);
            }
        }
        else if (cpu.ebx == 0)
        {
            cpu.edx = at(app, 0x5efda4);
            cpu.eax = at(app, 0x6fd4f4);
            if (i32(cpu.eax) < i32(cpu.edx))
            {
                cpu.eax = at(app, cpu.eax * 4 + 0x5efa48);
                put(app, cpu.ecx + 0x18, cpu.eax);
            }
        }
    }
    for (cpu.ecx = 0; i32(cpu.ecx) < 4; ++cpu.ecx, cpu.esi += 0x38)
    {
        cpu.eax = cpu.esi;
        cpu.edx = 0;
        if (!call(app, cpu, 0x411620))
            return;
    }
    cpu.eax = 0;
    put(app, 0x570dcc, cpu.eax);
    leave(cpu, kept, kEbx | kEcx | kEdx | kEsi);
}

/* 0x411750: the cop car of car eax, not chasing yet, set chasing -- ebx its
 * chase, edx its target, ecx (less) its distance. */
void copChaseSet(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.ebp = kept.frame(3);
    cpu.esp = cpu.ebp - 4;
    cpu.esi = cpu.eax;
    cpu.edi = cpu.edx;
    put(app, cpu.ebp - 4, cpu.ecx);
    cpu.eax = kCops;
    for (cpu.edx = 0; i32(cpu.edx) < 4; ++cpu.edx, cpu.eax += 0x38)
    {
        if (cpu.esi != at(app, cpu.eax) || at(app, cpu.eax + 0x20) != 0)
            continue;
        put(app, cpu.eax + 0x24, cpu.ebx);
        put(app, cpu.eax + 0x2c, cpu.edi);
        cpu.ecx = at(app, cpu.ebp - 4);
        put(app, cpu.eax + 0x20, cpu.ebx);
        put(app, cpu.eax + 0x28, cpu.ecx);
        cpu.ecx = 0u - cpu.ecx;
        put(app, cpu.eax + 0x28, cpu.ecx);
    }
    leave(cpu, kept, kEsi | kEdi);
}

/* 0x411c50: cop car eax's siren at distance ecx, pan edx, pitch ebx: on, or
 * its tick. */
void copSiren(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.ebp = cpu.esp = kept.frame(3);
    cpu.esi = cpu.eax;
    cpu.edi = cpu.edx;
    cpu.eax = 0x15f9 - cpu.ecx;
    cpu.edx = (cpu.eax << 7) - cpu.eax;
    cpu.ecx = 0x15f9;
    cpu.eax = cpu.edx;
    idiv(cpu, 0x15f9);
    cpu.edx = cpu.eax;
    if (i32(cpu.eax) < 0)
        cpu.edx ^= cpu.eax;
    cpu.eax = cpu.esi;
    if (!call(app, cpu, 0x417ca0))
        return;
    if (cpu.eax == 0)
    {
        cpu.eax = cpu.esi;
        cpu.edx = 0;
        if (!call(app, cpu, 0x417eb0))
            return;
        return leave(cpu, kept, kEsi | kEdi);
    }
    cpu.ecx = cpu.edi;
    cpu.eax = cpu.esi;
    if (!call(app, cpu, 0x417fd0))
        return;
    leave(cpu, kept, kEsi | kEdi);
}

/* 0x411ca0: siren eax stopped. */
void copSirenStop(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.ebp = cpu.esp = kept.frame(1);
    if (!call(app, cpu, 0x417f60))
        return;
    leave(cpu, kept, 0);
}

/* 0x411cb0: cop car eax's engine at distance ecx, pitch ebx, pan edx, in
 * slot 0x1b on: effect 3, or the cops' own (10, or 11 for three models)
 * with the model's pitch. */
void copEngine(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.ebp = kept.frame(3);
    cpu.esp = cpu.ebp - 4;
    cpu.edi = cpu.eax;
    put(app, cpu.ebp - 4, cpu.edx);
    cpu.edx = cpu.ebx;
    cpu.ebx = cpu.eax * 56;
    cpu.eax = at(app, cpu.ebx + kCops);
    cpu.ebx = at(app, at(app, cpu.eax + 0x220) + 0x14) - 0x32;
    if ((byte(app, cpu.eax + 0x200) & 0x10) == 0)
    {
        cpu.edx <<= 6;
        towardZero(cpu, 16);
        cpu.esi = 3;
    }
    else
    {
        const reg32 model = cpu.ebx + 0x32;
        cpu.eax = byte(app, cpu.ebx + 0x55276c);
        cpu.edx = reg32(mul(i32(cpu.edx), i32(cpu.eax)));
        towardZero(cpu, 16);
        cpu.esi = model == 0x35 || model == 0x3e || model == 0x40 ? 0xb : 0xa;
    }
    cpu.ebx = cpu.eax;
    cpu.edx = 0x15f9 - cpu.ecx;
    cpu.eax = (cpu.edx << 7) - cpu.edx;
    cpu.edx = cpu.eax;
    cpu.ecx = 0x15f9;
    idiv(cpu, 0x15f9);
    if (i32(cpu.ebx) > 0x7f)
        cpu.ebx = 0x7f;
    else if (i32(cpu.ebx) < 0)
        cpu.ebx = 0;
    cpu.edx = at(app, cpu.ebp - 4);
    cpu.edi += 0x1b;
    cpu.ecx = cpu.eax;
    const reg32 pan = cpu.edx;
    cpu.eax = cpu.edi;
    cpu.edx = cpu.esi;
    if (!call(app, cpu, 0x417080, {pan}))
        return;
    leave(cpu, kept, kEsi | kEdi);
}

/* 0x411da0: cop car eax's engine stopped. */
void copEngineStop(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.ebp = cpu.esp = kept.frame(1);
    cpu.eax += 0x1b;
    if (!call(app, cpu, 0x416f60))
        return;
    leave(cpu, kept, 0);
}

/* 0x411db0: cop car eax's distance from the listener, squared (0x15f9 with
 * no car). */
void copDistance(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.ebp = kept.frame(2);
    cpu.esp = cpu.ebp - 0xc;
    cpu.eax <<= 3;
    cpu.edx = cpu.eax;
    cpu.eax = (cpu.eax << 3) - cpu.edx + kCops;
    cpu.edx = at(app, cpu.eax);
    if (cpu.edx == 0)
    {
        cpu.eax = 0x15f9;
        return leave(cpu, kept, kEdx);
    }
    put(app, cpu.ebp - 0xc, at(app, cpu.edx + 0x98));
    put(app, cpu.ebp - 8, at(app, cpu.edx + 0x9c));
    cpu.eax = at(app, cpu.edx + 0xa0);
    cpu.edx = cpu.ebp - 0xc;
    put(app, cpu.ebp - 4, cpu.eax);
    cpu.eax = 0x570a78;
    if (!call(app, cpu, 0x410cb0))
        return;
    cpu.edx = cpu.eax;
    towardZero(cpu, 16);
    cpu.eax = reg32(mul(i32(cpu.eax), i32(cpu.eax)));
    leave(cpu, kept, kEdx);
}

/* 0x411e20: how close eax cop cars from edx on are, all told: each's 0x15f9
 * less its distance (squared), at most. */
void copsCloseness(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.ebp = cpu.esp = kept.frame(5);
    cpu.esi = cpu.eax;
    cpu.ebx = cpu.edx;
    cpu.ecx = 0;
    for (;;)
    {
        cpu.eax = cpu.ebx + cpu.esi;
        if (i32(cpu.edx) >= i32(cpu.eax))
            break;
        cpu.eax = cpu.edx;
        if (!call(app, cpu, 0x411db0))
            return;
        if (i32(cpu.eax) >= 0x15f9)
            cpu.eax = 0x15f9;
        cpu.edi = 0x15f9 - cpu.eax;
        ++cpu.edx;
        cpu.ecx += cpu.edi;
    }
    cpu.eax = cpu.ecx;
    leave(cpu, kept, kEbx | kEcx | kEsi | kEdi);
}

/* 0x415050: car edx's sound of the track's zones (ecx: their list, 6 words
 * each -- where it starts, is full, stops being full, ends; its effect; its
 * side -- to one below 0) in slot eax: as loud as the car is into its zone,
 * from its side (turned in the mirror) offset by ebx, or the player's side
 * in the split screen.  1 when one plays; 0, or with the view not the
 * player's (0x6fd4f8). */
void zoneSound(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const unsigned pushed = kEsi | kEdi;
    cpu.ebp = kept.frame(3);
    cpu.esp = cpu.ebp - 0xc;
    put(app, cpu.ebp - 0xc, cpu.eax);
    cpu.esi = cpu.edx;
    auto none = [&] {
        cpu.eax = 0;
        leave(cpu, kept, pushed);
    };
    if (cpu.ecx == 0)
        return none();
    cpu.edx = at(app, 0x6fd4f8);
    if (cpu.edx != at(app, 0x6fd4f4))
    {
        if (!call(app, cpu, 0x42d510, {0x64, 2, 0x536b98}))
            return;
        return none();
    }
    for (;; cpu.ecx += 0x18)
    {
        cpu.edi = at(app, cpu.ecx);
        if (i32(cpu.edi) <= -1)
            return none();
        cpu.eax = at(app, cpu.esi + 0x1c);
        if (i32(cpu.eax) < i32(cpu.edi))
            continue;
        cpu.edi = at(app, cpu.ecx + 0xc);
        if (i32(cpu.eax) > i32(cpu.edi))
            continue;
        break;
    }
    cpu.edx = at(app, cpu.ecx + 4);
    if (i32(cpu.eax) < i32(cpu.edx))
    {
        cpu.edi = at(app, cpu.ecx);
        cpu.eax -= cpu.edi;
        cpu.edx = cpu.eax;
        cpu.eax = (cpu.eax << 7) - cpu.edx;
        cpu.edx = cpu.eax;
        cpu.eax = at(app, cpu.ecx + 4) - cpu.edi;
        cpu.edi = cpu.eax;
        cpu.eax = cpu.edx;
        idiv(cpu, cpu.edi);
        cpu.edx = cpu.eax;
    }
    else if (i32(cpu.eax) > s32(app, cpu.ecx + 8))
    {
        cpu.edx = cpu.edi - cpu.eax;
        cpu.eax = (cpu.edx << 7) - cpu.edx;
        cpu.edx = cpu.eax;
        cpu.eax = cpu.edi;
        cpu.edi = at(app, cpu.ecx + 8);
        cpu.eax -= cpu.edi;
        cpu.edi = cpu.eax;
        cpu.eax = cpu.edx;
        idiv(cpu, cpu.edi);
        cpu.edx = cpu.eax;
    }
    else
        cpu.edx = 0x7f;
    cpu.eax = at(app, cpu.ecx + 0x14);
    if (at(app, 0x6fd4c4) != 0)
    {
        cpu.edi = 0u - cpu.eax;
        put(app, cpu.ebp - 4, cpu.edi);
    }
    else
        put(app, cpu.ebp - 4, cpu.eax);
    if (at(app, 0x6fd3b0) == 1)
        cpu.eax = at(app, cpu.esi + 0x1f0) != 0 ? 0xc000 : 0x3fff;
    else
    {
        cpu.eax = cpu.edx << 8;
        cpu.edi = at(app, cpu.ebp - 4);
        put(app, cpu.ebp - 8, cpu.eax);
        cpu.eax -= 0x3f00;
        const bool loud = i32(cpu.edx) >= 0x3f;
        if (i32(cpu.edi) < 0)
        {
            cpu.edi = at(app, cpu.esi + 0x1c);
            if (i32(cpu.edi) < s32(app, cpu.ecx + 4))
            {
                if (!loud)
                    cpu.eax = 0;
                else
                {
                    cpu.esi = 0x10000 - cpu.eax;
                    cpu.eax = cpu.esi;
                }
            }
            else if (i32(cpu.edi) > s32(app, cpu.ecx + 8))
                cpu.eax = loud ? at(app, cpu.ebp - 8) + 0x4100 : 0x8000;
            else
                cpu.eax = 0xc000;
            cpu.eax = (cpu.eax + cpu.ebx) & 0xffff;
        }
        else if (i32(cpu.edi) > 0)
        {
            cpu.edi = at(app, cpu.esi + 0x1c);
            if (i32(cpu.edi) < s32(app, cpu.ecx + 4))
            {
                if (!loud)
                    cpu.eax = 0;
            }
            else
            {
                cpu.esi = cpu.edi;
                if (i32(cpu.esi) > s32(app, cpu.ecx + 8))
                {
                    if (!loud)
                        cpu.eax = 0x8000;
                    else
                    {
                        cpu.esi = 0x8000 - cpu.eax;
                        cpu.eax = cpu.esi;
                    }
                }
                else
                    cpu.eax = 0x3fff;
            }
            cpu.eax = (cpu.eax + cpu.ebx) & 0xffff;
        }
        else
            cpu.eax = 0;
    }
    cpu.ebx = 0x40;
    const reg32 pan = cpu.eax;
    cpu.eax = at(app, cpu.ecx + 0x10);
    cpu.ecx = cpu.edx;
    cpu.edx = cpu.eax;
    cpu.eax = at(app, cpu.ebp - 0xc);
    if (!call(app, cpu, 0x417080, {pan}))
        return;
    cpu.eax = 1;
    leave(cpu, kept, pushed);
}

}  // namespace snd
}  // namespace nfs3hp
