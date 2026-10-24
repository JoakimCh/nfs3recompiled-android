#include "native_snd.h"

/* The race's own sounds that play by themselves, native (native_snd.h says
 * how): the engines' sounds started in their slots as the race begins (the
 * second player's too in the split screen); a far-off effect of the
 * crowd's bank aimed by where the car is and played after a while; an effect
 * of that bank at random; the car bank's effect 15.
 *
 * The game's state: 0x571118 the far-off effect (6 or 7, 10 more to the
 * other side), 0x552934 the ticks before it plays (-1: none aimed). */
namespace nfs3hp
{
namespace snd
{

namespace
{

constexpr reg32 kSplitScreen = 0x6fd3b0, kFarEffect = 0x571118, kFarTicks = 0x552934, kCrowdBank = 0x571154;
constexpr reg32 kRandom = 0x4e0d88, kPlayEffect = 0x4182b0;

/* fld dword [at]; fmul qword [0x536b90]; fistp: the code's float scaled to an
 * integer. */
reg32 scaled(App* app, CPU& cpu, reg32 at)
{
    x86::FPU& fpu = cpu.fpu;
    fpu.push(x86::Float(app->getMemory<float>(at)));
    fpu.st(0) = fpu.mul(fpu.st(0), x86::Float(app->getMemory<double>(0x536b90)));
    const reg32 n = reg32(fpu.toInteger<i32>(fpu.st(0)));
    fpu.pop();
    return n;
}

}  // namespace

/* 0x414830: the engines' sounds as the race starts, where their slots are
 * empty: effects 0 and 1 of the first bank and 0 of the car's bank in slots
 * 0, 1 and 9 -- and the second player's (0x57122c's bank, on the right) in
 * 2, 3 and 10 in the split screen. */
void engineSoundsStart(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.ebp = cpu.esp = kept.frame(6);
    if (at(app, 0x570de8) == 0xffffffff)
    {
        cpu.esi = at(app, kSplitScreen) == 1 ? 0x3fff : 0;
        cpu.eax = at(app, 0x571124);
        cpu.ebx = cpu.esi;
        cpu.ecx = 0;
        cpu.edx = 0;
        if (!call(app, cpu, kPlayEffect, {0x40}))
            return;
        cpu.edx = 1;
        put(app, 0x570de8, cpu.eax);
        cpu.ebx = 0;
        cpu.ecx = 0;
        cpu.eax = at(app, 0x571124);
        put(app, 0x570dec, cpu.ebx);
        cpu.ebx = cpu.esi;
        cpu.edi = 1;
        if (!call(app, cpu, kPlayEffect, {0x40}))
            return;
        put(app, 0x570df8, cpu.eax);
        cpu.ebx = cpu.esi;
        cpu.ecx = 0;
        cpu.edx = 0;
        cpu.eax = at(app, 0x57113c);
        put(app, 0x570dfc, cpu.edi);
        if (!call(app, cpu, kPlayEffect, {0x40}))
            return;
        put(app, 0x570e48, cpu.eax);
        cpu.eax = 0;
        put(app, 0x570e4c, cpu.eax);
    }
    if (at(app, kSplitScreen) == 1 && at(app, 0x570df0) == 0xffffffff)
    {
        cpu.ebx = 0xc000;
        cpu.eax = at(app, 0x57122c);
        cpu.ecx = 0;
        cpu.edx = 0;
        cpu.esi = 1;
        if (!call(app, cpu, kPlayEffect, {0x40}))
            return;
        cpu.edx = 1;
        put(app, 0x570df0, cpu.eax);
        cpu.ebx = 0;
        cpu.ecx = 0;
        cpu.eax = at(app, 0x57122c);
        put(app, 0x570df4, cpu.ebx);
        cpu.ebx = 0xc000;
        cpu.edi = 0;
        if (!call(app, cpu, kPlayEffect, {0x40}))
            return;
        cpu.ebx = 0xc000;
        put(app, 0x570e00, cpu.eax);
        cpu.ecx = 0;
        cpu.edx = 0;
        cpu.eax = at(app, 0x57113c);
        put(app, 0x570e04, cpu.esi);
        if (!call(app, cpu, kPlayEffect, {0x40}))
            return;
        put(app, 0x570e50, cpu.eax);
        put(app, 0x570e54, cpu.edi);
    }
    leave(cpu, kept, kEbx | kEcx | kEdx | kEsi | kEdi);
}

/* 0x414e10: the far-off effect aimed, if none is: from the player's car
 * (0x5efa48's, its place at +0x98 and +0xa0, scaled) to the point (eax,
 * edx) -- 6 when far, 7 when near, 10 more when the point is behind -- to
 * play in half the distance's ticks. */
void farEffectAim(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const unsigned pushed = kEbx | kEcx;
    cpu.ebp = kept.frame(3);
    cpu.esp = cpu.ebp - 0xc;
    cpu.ebx = cpu.eax;
    cpu.ecx = cpu.edx;
    if (at(app, kFarTicks) != 0xffffffff)
        return leave(cpu, kept, pushed);
    cpu.eax = at(app, at(app, 0x6fd4f4) * 4 + 0x5efa48);
    cpu.edx = at(app, cpu.eax + 0x98);
    put(app, cpu.ebp - 0xc, cpu.edx);
    cpu.edx = at(app, cpu.eax + 0x9c);
    cpu.eax = at(app, cpu.eax + 0xa0);
    put(app, cpu.ebp - 4, cpu.eax);
    cpu.eax = scaled(app, cpu, cpu.ebp - 0xc);
    cpu.eax -= cpu.ebx;
    put(app, cpu.ebp - 8, cpu.edx);
    cpu.ebx = cpu.eax;
    cpu.eax = scaled(app, cpu, cpu.ebp - 4);
    cpu.edx = cpu.eax - cpu.ecx;
    cpu.eax = i32(cpu.ebx) > 0 ? cpu.ebx : 0u - cpu.ebx;
    if (i32(cpu.edx) <= 0)
        cpu.edx = 0u - cpu.edx;
    if (i32(cpu.eax) > i32(cpu.edx))
        cpu.edx = reg32(i32(cpu.edx) >> 2);
    else
        cpu.eax = reg32(i32(cpu.eax) >> 2);
    cpu.edx += cpu.eax;
    towardZero(cpu, 16);
    cpu.edx = cpu.eax;
    put(app, kFarEffect, i32(cpu.eax) > 0x2ee ? 6 : 7);
    cpu.eax = scaled(app, cpu, cpu.ebp - 4);
    if (i32(cpu.eax) > i32(cpu.ecx))
        put(app, kFarEffect, at(app, kFarEffect) + 0xa);
    cpu.edx = reg32(i32(cpu.edx) >> 1);
    put(app, kFarTicks, cpu.edx);
    leave(cpu, kept, pushed);
}

/* 0x414ef0: the far-off effect played, when the race has the crowd (0x6fd4cc):
 * panned at random to its side. */
void farEffectPlay(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.ebp = cpu.esp = kept.frame(5);
    if (at(app, 0x6fd4cc) != 0)
    {
        if (!call(app, cpu, kRandom))
            return;
        cpu.ecx = at(app, kFarEffect);
        cpu.eax &= 0x7fff;
        if (i32(cpu.ecx) > 7)
        {
            cpu.ebx = cpu.ecx - 0xa;
            cpu.eax += 0x4000;
            put(app, kFarEffect, cpu.ebx);
        }
        else
        {
            cpu.eax -= 0x4000;
            if (i32(cpu.eax) <= 0)
                cpu.eax = 0u - cpu.eax;
        }
        cpu.ecx = 0x7f;
        cpu.edx = at(app, kFarEffect);
        cpu.esi = at(app, kCrowdBank);
        cpu.ebx = cpu.eax;
        cpu.eax = cpu.esi;
        if (!call(app, cpu, kPlayEffect, {0x40}))
            return;
    }
    leave(cpu, kept, kEbx | kEcx | kEdx | kEsi);
}

/* 0x414f60: the far-off effect's tick: played when its ticks are up. */
void farEffectTick(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.ebp = cpu.esp = kept.frame(2);
    cpu.edx = at(app, kFarTicks);
    if (i32(cpu.edx) > 0)
        --cpu.edx;
    else if (cpu.edx == 0)
    {
        if (!call(app, cpu, 0x414ef0))
            return;
        cpu.edx = 0xffffffff;
    }
    put(app, kFarTicks, cpu.edx);
    leave(cpu, kept, kEdx);
}

/* 0x414f90: effect edx of the crowd's bank (below 0: one of 4 at random, at a
 * random volume of 0x5a on), at random pan -- the player's side in the split
 * screen, by eax. */
void crowdEffect(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.ebp = cpu.esp = kept.frame(5);
    cpu.esi = cpu.edx;
    const bool split = at(app, kSplitScreen) == 1;
    if (split)
    {
        setByte0(cpu.ebx, 1);
        cpu.eax = cpu.eax != 0 ? 0xc000 : 0x3fff;
        cpu.edi = cpu.eax;
    }
    else
        setByte0(cpu.ebx, 0);
    if (i32(cpu.esi) < 0)
    {
        if (!call(app, cpu, kRandom))
            return;
        cpu.ecx = 0x1e;
        cpu.esi = cpu.eax;
        cpu.edx = 0;
        if (!call(app, cpu, kRandom))
            return;
        udiv(cpu, cpu.ecx);
        cpu.esi &= 3;
        cpu.ecx = cpu.edx + 0x5a;
    }
    else
        cpu.ecx = 0x77;
    if (reg8(cpu.ebx) != 0)
        cpu.edx = cpu.edi;
    else
    {
        cpu.ebx = 0xffff;
        cpu.edx = 0;
        if (!call(app, cpu, kRandom))
            return;
        udiv(cpu, cpu.ebx);
    }
    cpu.eax = at(app, kCrowdBank);
    cpu.ebx = cpu.edx;
    cpu.edx = cpu.esi;
    if (!call(app, cpu, kPlayEffect, {0x40}))
        return;
    leave(cpu, kept, kEbx | kEcx | kEsi | kEdi);
}

/* 0x415010: the car bank's effect 15 at full volume -- the player's side in
 * the split screen, by eax. */
void carEffectFifteen(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.ebp = cpu.esp = kept.frame(4);
    if (at(app, kSplitScreen) == 1)
        cpu.ebx = cpu.eax != 0 ? 0xc000 : 0x3fff;
    else
        cpu.ebx = 0;
    cpu.ecx = 0x7f;
    cpu.edx = 0xf;
    cpu.eax = at(app, 0x57113c);
    if (!call(app, cpu, kPlayEffect, {0x40}))
        return;
    leave(cpu, kept, kEbx | kEcx | kEdx);
}

}  // namespace snd
}  // namespace nfs3hp
