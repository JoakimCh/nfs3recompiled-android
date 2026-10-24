#include "native_snd.h"

/* The pursuit's sound, native (native_snd.h says how): the music's
 * intensity following the chase's (Pathfinder's events and its control,
 * each change traced), the cops' warning beeps counted down, an effect of
 * the cops' bank.
 *
 * The game's state: 0x552844 each player's chase level, 0x55283c the beeps
 * left, 0x571110 the beep's sound, 0x552838 the music's level (-1: none
 * asked for, else 0 or 100), 0x552834 the event the music plays outside a
 * chase, 0x55284c the chase music on. */
namespace nfs3hp
{
namespace snd
{

namespace
{

constexpr reg32 kChaseLevel = 0x552844, kBeeps = 0x55283c, kBeepSound = 0x571110, kMusicLevel = 0x552838;
constexpr reg32 kCalmEvent = 0x552834, kChaseMusic = 0x55284c, kCopBank = 0x571160;
constexpr reg32 kTrace = 0x42d510, kPathEvent = 0x4e70fc, kPathControl = 0x4e705c;

/* The player's side in the split screen, else the middle. */
reg32 sideOf(App* app, reg32 second)
{
    if (at(app, 0x6fd3b0) != 1)
        return 0;
    return second != 0 ? 0xc000 : 0x3fff;
}

}  // namespace

/* 0x4188a0: player eax's beeps: when the last is done and there are more,
 * the next -- the high one (0x31) while below the chase's level. */
void copBeepTick(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.ebp = cpu.esp = kept.frame(6);
    cpu.edi = cpu.eax;
    cpu.ebx = sideOf(app, cpu.eax);
    cpu.esi = cpu.edi * 4;
    if (at(app, cpu.esi + kBeeps) != 0)
    {
        cpu.eax = at(app, cpu.esi + kBeepSound);
        if (!call(app, cpu, 0x4e8fd0))
            return;
        if (cpu.eax != 0)
        {
            cpu.edx = at(app, cpu.esi + kChaseLevel);
            cpu.ecx = 0x7f;
            cpu.edx = i32(cpu.edx) < s32(app, cpu.esi + kBeeps) ? 0x31 : 0x30;
            cpu.eax = at(app, kCopBank);
            if (!call(app, cpu, 0x4182b0, {0x40}))
                return;
            put(app, cpu.esi + kBeepSound, cpu.eax);
            put(app, cpu.edi * 4 + kBeeps, at(app, cpu.edi * 4 + kBeeps) - 1);
        }
    }
    leave(cpu, kept, kEbx | kEcx | kEdx | kEsi | kEdi);
}

/* 0x418930: player edx's beeps started: eax of them, the first high. */
void copBeepStart(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.ebp = cpu.esp = kept.frame(4);
    cpu.ebx = sideOf(app, cpu.edx);
    cpu.esi = cpu.edx * 4;
    cpu.ecx = 0x7f;
    cpu.edx = 0x31;
    put(app, cpu.esi + kBeeps, cpu.eax);
    cpu.eax = at(app, kCopBank);
    if (!call(app, cpu, 0x4182b0, {0x40}))
        return;
    put(app, cpu.esi + kBeepSound, cpu.eax);
    leave(cpu, kept, kEbx | kEcx | kEsi);
}

/* 0x418c30: effect eax of the cops' bank, at full volume. */
void copEffect(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.ebp = cpu.esp = kept.frame(5);
    cpu.ecx = 0x7f;
    cpu.esi = at(app, kCopBank);
    cpu.edx = cpu.eax;
    cpu.ebx = 0;
    cpu.eax = cpu.esi;
    if (!call(app, cpu, 0x4182b0, {0x40}))
        return;
    leave(cpu, kept, kEbx | kEcx | kEdx | kEsi);
}

/* 0x418c60: the music's event back after an interruption (the race's own
 * music on, playing, not muted): the chase's, or the calm one. */
void musicEventResume(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.ebp = cpu.esp = kept.frame(2);
    if (at(app, 0x552914) != 0 && at(app, 0x552910) != 0 && at(app, 0x6fbb54) == 0 && at(app, 0x6fbbf0) != 0
        && byte(app, 0x552590) == 0)
    {
        cpu.eax = 0;
        if (!call(app, cpu, 0x4e7208))
            return;
        if (at(app, kMusicLevel) != 0xffffffff)
        {
            cpu.eax = 1;
            cpu.edx = 0;
        }
        else
        {
            cpu.eax = 0;
            cpu.edx = 0;
            setByte0(cpu.eax, byte(app, kCalmEvent));
        }
        if (!call(app, cpu, kPathEvent))
            return;
    }
    leave(cpu, kept, kEdx);
}

/* 0x418990: player edx's chase at level eax: the beeps when it rises; the
 * race's music (player one's, its own music on) following -- the chase's
 * event when the chase starts, its level up at 4 and on, down at 2, the
 * calm event back when it ends. */
void chaseLevel(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const unsigned pushed = kEbx | kEcx | kEsi | kEdi;
    cpu.ebp = cpu.esp = kept.frame(5);
    cpu.ecx = cpu.eax;
    cpu.ebx = cpu.edx;
    auto trace = [&](reg32 text) { return call(app, cpu, kTrace, {0x64, 1, text}); };
    auto keep = [&] {
        put(app, cpu.ebx * 4 + kChaseLevel, cpu.ecx);
        leave(cpu, kept, pushed);
    };
    // The beeps for a rise; false when the level is as it was.
    auto rise = [&]() -> int {
        cpu.eax = cpu.ebx * 4;
        cpu.edx = at(app, cpu.eax + kChaseLevel);
        if (cpu.ecx == cpu.edx)
            return 0;
        if (i32(cpu.ecx) > i32(cpu.edx))
        {
            cpu.edx = cpu.ebx;
            cpu.eax = cpu.ecx;
            if (!call(app, cpu, 0x418930))
                return -1;
        }
        return 1;
    };
    const bool music = at(app, 0x552910) != 0 && at(app, 0x6fbb54) == 0 && at(app, 0x6fbbf0) != 0
                       && byte(app, 0x552590) == 0 && cpu.ebx != 1;
    if (!music)
    {
        const int r = rise();
        if (r < 0)
            return;
        if (r == 0)
            return leave(cpu, kept, pushed);
        return keep();
    }
    if (at(app, 0x552914) != 0)
    {
        if (cpu.ecx != 0 && at(app, kMusicLevel) != 0xffffffff && at(app, kChaseMusic) == 0)
        {
            cpu.esi = 0xffffffff;
            if (!trace(0x536bc0))
                return;
            cpu.eax = 0;
            setByte0(cpu.eax, byte(app, kCalmEvent));
            put(app, kMusicLevel, cpu.esi);
            if (!call(app, cpu, kPathEvent))
                return;
            if (cpu.ecx == at(app, cpu.ebx * 4 + kChaseLevel))
                return leave(cpu, kept, pushed);
        }
        if (cpu.ecx != 0 && at(app, kMusicLevel) == 0xffffffff && at(app, kChaseMusic) != 0)
        {
            if (i32(cpu.ecx) >= 4)
            {
                cpu.esi = 0x64;
                if (!trace(0x536bd0))
                    return;
                put(app, kMusicLevel, cpu.esi);
            }
            else
            {
                cpu.edi = 0;
                if (!trace(0x536be4))
                    return;
                put(app, kMusicLevel, cpu.edi);
            }
            cpu.eax = 1;
            cpu.edx = 0;
            if (!call(app, cpu, kPathEvent))
                return;
            cpu.eax = at(app, kMusicLevel);
            if (!call(app, cpu, kPathControl))
                return;
            if (cpu.ecx == at(app, cpu.ebx * 4 + kChaseLevel))
                return leave(cpu, kept, pushed);
        }
    }
    const int r = rise();
    if (r < 0)
        return;
    if (r == 0)
        return leave(cpu, kept, pushed);
    if (at(app, 0x552914) == 0)
        return keep();
    if (i32(cpu.ecx) > 1 && at(app, kMusicLevel) == 0xffffffff && at(app, kChaseMusic) != 0)
    {
        cpu.esi = 0;
        cpu.edx = 0;
        if (!trace(0x536bfc))
            return;
        cpu.eax = 1;
        put(app, kMusicLevel, cpu.esi);
        if (!call(app, cpu, kPathEvent))
            return;
        cpu.eax = 0;
        if (!call(app, cpu, kPathControl))
            return;
        return keep();
    }
    if (cpu.ecx == 2 && at(app, kMusicLevel) != 0 && at(app, kChaseMusic) != 0)
    {
        cpu.edx = 0;
        if (!trace(0x536c10))
            return;
        cpu.eax = 0;
        put(app, kMusicLevel, cpu.edx);
        if (!call(app, cpu, kPathControl))
            return;
        return keep();
    }
    if (cpu.ecx == 4 && at(app, kMusicLevel) != 0x64 && at(app, kChaseMusic) != 0)
    {
        if (!trace(0x536c20))
            return;
        cpu.eax = 0x64;
        put(app, kMusicLevel, cpu.eax);
        if (!call(app, cpu, kPathControl))
            return;
        return keep();
    }
    if (cpu.ecx == 0 && at(app, kMusicLevel) != 0xffffffff && at(app, kChaseMusic) != 0)
    {
        cpu.edi = 0xffffffff;
        cpu.edx = 0;
        if (!trace(0x536bc0))
            return;
        cpu.eax = 0;
        setByte0(cpu.eax, byte(app, kCalmEvent));
        put(app, kMusicLevel, cpu.edi);
        if (!call(app, cpu, kPathEvent))
            return;
    }
    keep();
}

}  // namespace snd
}  // namespace nfs3hp
