#include "native_snd.h"

/* The cops' radio by where they are, native (native_snd.h says how): a
 * car's radio heard from its place -- loud as it is near, panned to it (the
 * player's side in the split screen) -- and the line the radio says for an
 * event, picked at random among the event's, now and then another. */
namespace nfs3hp
{
namespace snd
{

namespace
{

constexpr reg32 kListener = 0x570a78, kRandom = 0x4e0d88;

/* The code's distance's square: towardZero(16) of eax, squared, at most
 * 0x15f9. */
void distanceSquared(CPU& cpu)
{
    cpu.edx = cpu.eax;
    towardZero(cpu, 16);
    cpu.eax = reg32(mul(i32(cpu.eax), i32(cpu.eax)));
    if (i32(cpu.eax) >= 0x15f9)
        cpu.eax = 0x15f9;
}

}  // namespace

/* 0x4127c0: car eax's radio, where its driver (0x4124d0's) speaks: heard
 * from the car's place. */
void carRadio(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const unsigned pushed = kEbx | kEcx | kEsi | kEdi;
    cpu.ebp = kept.frame(5);
    cpu.esp = cpu.ebp - 0x10;
    const reg32 place = cpu.ebp - 0x10;
    cpu.esi = cpu.eax;
    put(app, place, at(app, cpu.esi + 0x98));
    put(app, place + 4, at(app, cpu.esi + 0x9c));
    put(app, place + 8, at(app, cpu.esi + 0xa0));
    cpu.eax = at(app, cpu.esi + 0x624);
    cpu.edx = cpu.esi + 0xa4;
    cpu.ebx = at(app, cpu.eax + 0x1f0);
    cpu.eax = place;
    if (!call(app, cpu, 0x4124d0))
        return;
    put(app, cpu.ebp - 4, cpu.eax);
    if (i32(cpu.eax) < 0)
        return leave(cpu, kept, pushed);
    cpu.edx = place;
    cpu.eax = kListener;
    if (!call(app, cpu, 0x410cb0))
        return;
    cpu.edx = at(app, 0x6fd3b0);
    cpu.ecx = cpu.eax;
    if (cpu.edx == 1)
        cpu.edi = cpu.ebx != 0 ? 0xc000 : 0x3fff;
    else
    {
        cpu.edx = place;
        cpu.eax = kListener;
        if (!call(app, cpu, 0x410d30))
            return;
        cpu.edi = cpu.eax;
    }
    cpu.eax = cpu.ecx;
    distanceSquared(cpu);
    const reg32 player = cpu.ebx;
    cpu.ecx = cpu.eax;
    cpu.edx = cpu.edi;
    cpu.ebx = at(app, cpu.ebp - 4);
    cpu.eax = cpu.esi;
    if (!call(app, cpu, 0x4c89b0, {player}))
        return;
    leave(cpu, kept, pushed);
}

/* 0x412880: the cop radio of kind ebx for car eax's player (its +0x624's),
 * from that car's place. */
void playerCopRadio(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.ebp = kept.frame(3);
    cpu.esp = cpu.ebp - 0xc;
    const reg32 place = cpu.ebp - 0xc;
    cpu.ecx = cpu.eax;
    cpu.esi = cpu.ebx;
    const reg32 car = at(app, cpu.ecx + 0x624);
    put(app, place, at(app, car + 0x98));
    put(app, place + 4, at(app, car + 0x9c));
    cpu.eax = at(app, car + 0xa0);
    put(app, place + 8, cpu.eax);
    cpu.eax = car;
    cpu.edx = at(app, 0x6fd3b0);
    cpu.ecx = at(app, cpu.eax + 0x1f0);
    if (cpu.edx == 1)
    {
        cpu.edx = kListener;
        cpu.eax = cpu.ecx;
        cpu.ebx = 0;
        if (!call(app, cpu, 0x4229c0))
            return;
    }
    cpu.edx = place;
    cpu.eax = kListener;
    if (!call(app, cpu, 0x410cb0))
        return;
    distanceSquared(cpu);
    cpu.ebx = cpu.eax;
    cpu.edx = cpu.esi;
    cpu.eax = cpu.ecx;
    if (!call(app, cpu, 0x4c8b30))
        return;
    leave(cpu, kept, kEcx | kEsi);
}

/* 0x412be0: the radio's line for event eax: by the event (at random among
 * its own), in the split screen the player's; another (0x1c, or the event's
 * first) when 0x4cdee0 says it was the last. */
void copLineFor(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.ebp = cpu.esp = kept.frame(4);
    cpu.ecx = cpu.eax;
    auto done = [&] {
        cpu.eax = cpu.edx;
        leave(cpu, kept, kEbx | kEcx | kEdx);
    };
    // Random's remainder of `by`: past half (of 100) or not.
    auto pastHalf = [&](reg32& by, bool& past) {
        by = 0x64;
        cpu.edx = 0;
        if (!call(app, cpu, kRandom))
            return false;
        udiv(cpu, by);
        past = cpu.edx > 0x32;
        return true;
    };
    bool past;
    cpu.edx = at(app, 0x6fd3b0);
    if (cpu.edx == 1)
    {
        if (cpu.eax == cpu.edx)
        {
            if (!pastHalf(cpu.ecx, past))
                return;
            cpu.edx = past ? 0x20 : 0x21;
            return done();
        }
        cpu.ebx = cpu.ecx + 0x20;
        if (!call(app, cpu, 0x4cdee0))
            return;
        if (cpu.ecx != cpu.eax)
        {
            cpu.edx = cpu.ebx;
            return done();
        }
        if (!pastHalf(cpu.ecx, past))
            return;
        cpu.edx = past ? 0x29 : cpu.ebx;
        return done();
    }
    if (!call(app, cpu, 0x4cdee0))
        return;
    if (cpu.eax == 2)
    {
        cpu.edx = cpu.ecx == 1 ? 0x12 : 0x1c;
        return done();
    }
    if (cpu.ecx == 1)
    {
        cpu.ebx = 3;
        cpu.edx = 0;
        if (!call(app, cpu, kRandom))
            return;
        udiv(cpu, cpu.ebx);
        cpu.edx += 0x10;
    }
    else if (cpu.ecx == 2 || cpu.ecx == 3)
    {
        if (!call(app, cpu, kRandom))
            return;
        cpu.eax &= 1;
        cpu.edx = cpu.eax + (cpu.ecx == 2 ? 0x13 : 0x15);
    }
    else
        cpu.edx = cpu.ecx + 0x13;
    if (!call(app, cpu, 0x4cdee0))
        return;
    if (cpu.ecx != cpu.eax)
        return done();
    if (!pastHalf(cpu.ebx, past))
        return;
    if (past && s32(app, 0x6fd3b0) < 1)
    {
        cpu.edx = 0x1c;
        return done();
    }
    cpu.edx = cpu.ecx == 2 ? 0x13 : cpu.ecx == 3 ? 0x15 : cpu.ecx + 0x13;
    done();
}

}  // namespace snd
}  // namespace nfs3hp
