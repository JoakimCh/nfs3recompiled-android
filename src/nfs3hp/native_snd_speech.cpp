#include "native_snd.h"

/* The race's speech, native (native_snd.h says how): what the cops' radio
 * and the race's voices say, each player's (two in the split screen) played
 * in turn from a queue, faded with the distance of whoever speaks.
 *
 * The game's state, per player: 0x7dd334 (8 apart) a line said, 0x7dd340
 * one to tell the game of, 0x7dd348 a line playing, 0x7dd350 the radio's
 * sound, 0x7dd358 the line's kind, 0x7dd368 a line to clear, 0x7dd370 the
 * line's sound, 0x7dd378 the lines queued, 0x7dd390 another sound, the
 * queues at 0x7dd398 and 0x7dd5d8 (0x24 bytes a line), 0x7dd818 (8 apart)
 * who speaks on the radio, 0x7dd81c the radio on; 0x560ac4 the radio's last
 * chatter. */
namespace nfs3hp
{
namespace snd
{

namespace
{

constexpr reg32 kStatus = 0x4e8fd0, kVolume = 0x4e95fc, kSpeechVolume = 0x6fbbfc;

}  // namespace

/* 0x4c86d0: player eax's speech tick: a line done ended (the game told,
 * where it asked), the next of the queue played and the queue moved up. */
void speechTick(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.ebp = cpu.esp = kept.frame(6);
    cpu.ecx = cpu.eax;
    if (!call(app, cpu, 0x4c8ac0))
        return;
    if (i32(cpu.ecx) > 1)
        cpu.ecx = 0;
    cpu.edx = cpu.ecx * 4;
    if (at(app, cpu.edx + 0x7dd348) != 0)
    {
        cpu.eax = at(app, cpu.edx + 0x7dd370);
        if (!call(app, cpu, kStatus))
            return;
        if (cpu.eax != 0)
        {
            cpu.esi = 0;
            cpu.edi = at(app, cpu.edx + 0x7dd340);
            put(app, cpu.edx + 0x7dd348, cpu.esi);
            if (cpu.edi != 0)
            {
                cpu.eax = 0xffffffff;
                cpu.ebx = 0;
                put(app, cpu.edx + 0x7dd340, cpu.esi);
                cpu.edx = cpu.ecx;
                if (!call(app, cpu, 0x482030))
                    return;
            }
            cpu.eax = cpu.ecx * 4;
            cpu.edx = at(app, cpu.eax + 0x7dd358);
            if (cpu.edx == 4)
            {
                cpu.esi = 0;
                put(app, cpu.eax + 0x7dd358, cpu.esi);
            }
        }
    }
    cpu.eax = cpu.ecx * 4;
    if (at(app, cpu.eax + 0x7dd378) != 0 && at(app, cpu.eax + 0x7dd348) == 0)
    {
        cpu.eax = cpu.ecx != 0 ? 0x7dd5d8 : 0x7dd398;
        if (!call(app, cpu, 0x4c85a0))
            return;
        cpu.ebx = at(app, cpu.ecx * 4 + 0x7dd378) - 1;
        put(app, cpu.ecx * 4 + 0x7dd378, cpu.ebx);
        if (cpu.ebx != 0)
        {
            for (cpu.ebx = 0; i32(cpu.ebx) < s32(app, cpu.ecx * 4 + 0x7dd378); ++cpu.ebx)
            {
                cpu.esi = cpu.ecx != 0 ? 0x7dd5d8 : 0x7dd398;
                cpu.edx = cpu.esi + (cpu.ebx + 1) * 0x24;
                cpu.eax = cpu.ebx * 0x24 + cpu.esi;
                for (reg32 k = 0; k < 0x20; k += 4)
                {
                    cpu.esi = at(app, cpu.edx + k);
                    put(app, cpu.eax + k, cpu.esi);
                }
                cpu.edx = at(app, cpu.edx + 0x20);
                put(app, cpu.eax + 0x20, cpu.edx);
            }
        }
    }
    leave(cpu, kept, kEbx | kEcx | kEdx | kEsi | kEdi);
}

/* 0x4c8810 (stdcall 4): player [esp+4]'s radio: when it is done, its line's
 * volume back; else, the speaker eax still the one, at distance ecx, pitch
 * ebx, pan edx -- its volume, pitch and place set. */
void radioTick(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const unsigned pushed = kEsi | kEdi;
    cpu.ebp = kept.frame(3);
    cpu.esp = cpu.ebp - 8;
    put(app, cpu.ebp - 4, cpu.eax);
    cpu.esi = cpu.edx;
    cpu.edi = cpu.ebx;
    cpu.ebx = at(app, cpu.ebp + 0x10);
    cpu.edx = cpu.ecx;
    cpu.ecx = cpu.ebx * 4;
    cpu.eax = at(app, cpu.ecx + 0x7dd350);
    if (!call(app, cpu, kStatus))
        return;
    if (cpu.eax != 0 && at(app, cpu.ebx * 8 + 0x7dd81c) != 0)
    {
        cpu.eax = cpu.ebx * 8;
        cpu.edx = 0;
        cpu.ebx = at(app, cpu.ecx + 0x7dd348);
        put(app, cpu.eax + 0x7dd81c, cpu.edx);
        if (cpu.ebx != 0)
        {
            cpu.edx = at(app, kSpeechVolume);
            cpu.eax = ((cpu.edx << 6) - cpu.edx) << 8;
            cpu.edx = reg32(i32(cpu.edx + cpu.eax) >> 14);
            cpu.eax = at(app, cpu.ecx + 0x7dd370);
            if (!call(app, cpu, kVolume))
                return;
        }
        return leave(cpu, kept, pushed, 4);
    }
    cpu.eax = cpu.ebx * 8;
    if (at(app, cpu.eax + 0x7dd81c) == 0)
        return leave(cpu, kept, pushed, 4);
    cpu.ecx = at(app, cpu.ebp - 4);
    if (cpu.ecx != at(app, cpu.eax + 0x7dd818))
        return leave(cpu, kept, pushed, 4);
    if (i32(cpu.edx) < 0x15f9)
    {
        cpu.eax = 0x15f9 - cpu.edx;
        cpu.edx = cpu.eax;
        cpu.eax = (cpu.eax << 7) - cpu.edx;
        cpu.edx = cpu.eax;
        cpu.ecx = 0x15f9;
        idiv(cpu, 0x15f9);
        cpu.edx = cpu.eax;
    }
    else
        cpu.edx = 0;
    cpu.eax = at(app, kSpeechVolume);
    put(app, cpu.ebp - 8, cpu.eax);
    cpu.ecx = cpu.eax;
    cpu.eax = (cpu.eax << 7) - cpu.ecx;
    cpu.edx = reg32(mul(i32(cpu.edx), i32(cpu.eax)));
    cpu.ecx = cpu.ebx * 4;
    cpu.edx = reg32(i32(cpu.edx) >> 14);
    cpu.eax = at(app, cpu.ecx + 0x7dd350);
    if (!call(app, cpu, kVolume))
        return;
    cpu.edx = cpu.edi << 6;
    towardZero(cpu, 16);
    cpu.edi = at(app, cpu.ecx + 0x7dd350);
    cpu.edx = cpu.eax;
    cpu.eax = cpu.edi;
    if (!call(app, cpu, 0x4e97e4))
        return;
    if (at(app, 0x5525a4) != 0)
    {
        if (at(app, 0x55292c) != 0)
        {
            cpu.edx = cpu.esi;
            cpu.eax = at(app, cpu.ecx + 0x7dd350);
            cpu.ebx = 0;
        }
        else
        {
            cpu.eax = at(app, cpu.ecx + 0x7dd350);
            cpu.ebx = 0;
            cpu.edx = 0;
        }
        if (!call(app, cpu, 0x4e9850))
            return;
        return leave(cpu, kept, pushed, 4);
    }
    if (at(app, 0x55292c) != 0)
    {
        cpu.edx = stereoPan(cpu.esi);
        cpu.eax = at(app, cpu.ebx * 4 + 0x7dd350);
    }
    else
    {
        cpu.edx = 0x40;
        cpu.eax = at(app, cpu.ecx + 0x7dd350);
    }
    if (!call(app, cpu, 0x4e9950))
        return;
    leave(cpu, kept, pushed, 4);
}

/* 0x4c89b0 (stdcall 4): player [esp+4]'s radio, if it is off, on: speaker
 * eax at distance ecx, pitch ebx, pan edx -- a chatter of 10 at random, not
 * the last one -- the lines playing lowered for it. */
void radioStart(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const unsigned pushed = kEsi | kEdi;
    cpu.ebp = kept.frame(3);
    cpu.esp = cpu.ebp - 8;
    put(app, cpu.ebp - 8, cpu.eax);
    cpu.edi = cpu.edx;
    put(app, cpu.ebp - 4, cpu.ebx);
    cpu.eax = at(app, cpu.ebp + 0x10);
    cpu.edx = at(app, cpu.eax * 8 + 0x7dd81c);
    if (cpu.edx != 0)
        return leave(cpu, kept, pushed, 4);
    cpu.ebx = 0xa;
    if (!call(app, cpu, 0x4e0d88))
        return;
    udiv(cpu, cpu.ebx);
    cpu.esi = cpu.edx;
    cpu.ebx = 0;
    while (cpu.esi == at(app, 0x560ac4))
    {
        cpu.esi = 0xa;
        cpu.edx = 0;
        if (!call(app, cpu, 0x4e0d88))
            return;
        udiv(cpu, cpu.esi);
        cpu.esi = cpu.edx;
    }
    cpu.ebx = 1;
    cpu.eax = at(app, cpu.ebp + 0x10);
    put(app, cpu.eax * 8 + 0x7dd81c, 1);
    cpu.edx = at(app, cpu.ebp - 8);
    put(app, cpu.eax * 8 + 0x7dd818, cpu.edx);
    cpu.edx = 0x15f9 - cpu.ecx;
    cpu.eax = (cpu.edx << 7) - cpu.edx;
    cpu.edx = cpu.eax;
    cpu.ecx = 0x15f9;
    idiv(cpu, 0x15f9);
    cpu.edx = at(app, cpu.ebp - 4) << 6;
    cpu.ebx = cpu.eax;
    towardZero(cpu, 16);
    cpu.ecx = i32(cpu.eax) > 0x7f ? 0x7f : cpu.eax;
    if (at(app, 0x7dd348) != 0)
    {
        cpu.edx = at(app, cpu.ebp + 0x10);
        if (cpu.edx == 0)
        {
            cpu.eax = at(app, 0x7dd370);
            if (!call(app, cpu, kVolume))
                return;
        }
    }
    if (at(app, 0x7dd34c) != 0)
    {
        cpu.edx = at(app, cpu.ebp + 0x10);
        if (cpu.edx == 0)
        {
            cpu.eax = at(app, 0x7dd374);
            if (!call(app, cpu, kVolume))
                return;
        }
    }
    cpu.eax = at(app, 0x571184);
    const reg32 pitch = cpu.ecx;
    cpu.edx = cpu.esi;
    cpu.ecx = cpu.ebx;
    cpu.ebx = cpu.edi;
    if (!call(app, cpu, 0x4182b0, {pitch}))
        return;
    cpu.edx = at(app, cpu.ebp + 0x10);
    put(app, 0x560ac4, cpu.esi);
    put(app, cpu.edx * 4 + 0x7dd350, cpu.eax);
    leave(cpu, kept, pushed, 4);
}

/* 0x4c8ac0: each player's line said, when its sound is done: marked over
 * (0x560118 cleared). */
void speechSaid(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.ebp = cpu.esp = kept.frame(5);
    for (cpu.edx = 0; i32(cpu.edx) < 2; ++cpu.edx)
    {
        cpu.ecx = cpu.edx * 4;
        cpu.eax = at(app, cpu.ecx + 0x7dd390);
        if (!call(app, cpu, kStatus))
            return;
        if (cpu.eax == 0)
            continue;
        cpu.eax = cpu.edx * 8;
        if (at(app, cpu.eax + 0x7dd334) == 0)
            continue;
        cpu.esi = at(app, cpu.ecx + 0x7dd368);
        if (cpu.esi != 0)
        {
            cpu.edi = 0;
            put(app, 0x560118, cpu.edi);
            put(app, cpu.eax + 0x7dd334, cpu.edi);
            put(app, cpu.ecx + 0x7dd368, cpu.edi);
        }
        else
        {
            put(app, 0x560118, cpu.esi);
            put(app, cpu.eax + 0x7dd334, cpu.esi);
        }
    }
    leave(cpu, kept, kEcx | kEdx | kEsi | kEdi);
}

/* 0x4c8b30: player eax's cop radio, of kind edx (1: a chase, 2, 3, else),
 * from distance ebx, unless the race is replayed: a line of its kind at
 * random, not the last one, at the distance's volume -- the lines playing
 * lowered for it. */
void copRadio(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const unsigned pushed = kEcx | kEsi | kEdi;
    cpu.ebp = kept.frame(4);
    cpu.esp = cpu.ebp - 8;
    cpu.esi = cpu.eax;
    cpu.eax = cpu.ebx;
    if (at(app, 0x6fd3a0) != 0)
        return leave(cpu, kept, pushed);
    if (cpu.edx == 1)
    {
        cpu.ebx = 3;
        cpu.edi = 0x20;
    }
    else if (cpu.edx == 2)
    {
        cpu.ebx = 1;
        cpu.edi = 0x13;
    }
    else if (cpu.edx == 3)
    {
        cpu.ebx = 2;
        cpu.edi = 0x11;
    }
    else
    {
        cpu.ebx = 2;
        cpu.edi = 0x10;
    }
    cpu.edx = 0x15f9 - cpu.eax;
    cpu.eax = (cpu.edx << 7) - cpu.edx;
    cpu.edx = cpu.eax;
    cpu.ecx = 0x15f9;
    idiv(cpu, 0x15f9);
    cpu.ecx = cpu.eax;
    cpu.edx = 0;
    put(app, cpu.esi * 4 + 0x7dd388, cpu.eax);
    if (!call(app, cpu, 0x4e0d88))
        return;
    udiv(cpu, cpu.ebx);
    cpu.eax = cpu.edi + cpu.edx;
    put(app, cpu.ebp - 4, cpu.eax);
    cpu.eax = 0;
    put(app, cpu.ebp - 8, cpu.eax);
    if (cpu.ebx != 1)
    {
        for (;;)
        {
            cpu.eax = at(app, cpu.ebp - 4);
            if (cpu.eax != at(app, 0x560ac8))
            {
                put(app, cpu.ebp - 8, 1);
                break;
            }
            cpu.edx = 0;
            if (!call(app, cpu, 0x4e0d88))
                return;
            udiv(cpu, cpu.ebx);
            cpu.eax = cpu.edi + cpu.edx;
            put(app, cpu.ebp - 4, cpu.eax);
        }
    }
    if (at(app, 0x6fd3b0) == 1)
        cpu.ebx = cpu.esi != 0 ? 0xc000 : 0x3fff;
    else
        cpu.ebx = 0;
    cpu.eax = 1;
    cpu.edx = at(app, 0x7dd348);
    put(app, cpu.esi * 8 + 0x7dd334, cpu.eax);
    if (cpu.edx != 0 && cpu.esi == 0)
    {
        cpu.eax = at(app, 0x7dd370);
        cpu.edx = 0;
        if (!call(app, cpu, kVolume))
            return;
    }
    if (at(app, 0x7dd34c) != 0 && cpu.esi == 0)
    {
        cpu.eax = at(app, 0x7dd374);
        cpu.edx = 0;
        if (!call(app, cpu, kVolume))
            return;
    }
    cpu.edx = 1;
    cpu.eax = at(app, 0x571184);
    put(app, 0x560118, cpu.edx);
    cpu.edx = at(app, cpu.ebp - 4);
    if (!call(app, cpu, 0x4182b0, {0x40}))
        return;
    cpu.edx = cpu.esi * 4;
    put(app, cpu.edx + 0x7dd390, cpu.eax);
    if (cpu.edi == 0x20)
        put(app, cpu.edx + 0x7dd368, 1);
    if (!call(app, cpu, 0x418c60))
        return;
    cpu.eax = at(app, cpu.ebp - 4);
    put(app, 0x560ac8, cpu.eax);
    leave(cpu, kept, pushed);
}

/* 0x4c8ca0: a line of the speech bank (0x571190) queued: effect eax, kind 2,
 * edx its delay, for player ebx (its side in the split screen). */
void queueSpeechLine(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.ebp = kept.frame(4);
    cpu.esp = cpu.ebp - 0x24;
    cpu.esi = 0x40;
    cpu.ecx = 0x7f;
    cpu.edi = at(app, 0x6fd3b0);
    put(app, cpu.ebp - 0x1c, cpu.esi);
    put(app, cpu.ebp - 0x20, cpu.ecx);
    if (cpu.edi == 1)
        cpu.ecx = cpu.ebx != 0 ? 0xc000 : 0x3fff;
    else
        cpu.ecx = 0;
    put(app, cpu.ebp - 0x18, cpu.ecx);
    put(app, cpu.ebp - 0x24, cpu.eax);
    put(app, cpu.ebp - 0x10, cpu.ebx);
    put(app, cpu.ebp - 8, cpu.edx);
    cpu.eax = at(app, 0x571190);
    cpu.ebx = 2;
    put(app, cpu.ebp - 0x14, cpu.eax);
    cpu.eax = cpu.ebp - 0x24;
    put(app, cpu.ebp - 0xc, cpu.ebx);
    if (!call(app, cpu, 0x4c85a0))
        return;
    leave(cpu, kept, kEcx | kEsi | kEdi);
}

/* 0x4c8370: the speech set up for the race: each player's lines, radio and
 * description cleared, the co-driver's script of the track (by its number,
 * its direction's file) loaded. */
void speechInit(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.ebp = kept.frame(5);
    cpu.esp = cpu.ebp - 0x64;
    const reg32 name = cpu.ebp - 0x64;
    cpu.eax = 0;
    do
    {
        ++cpu.eax;
        cpu.edx = 0;
        put(app, cpu.eax * 4 + 0x7dd344, cpu.edx);
        put(app, cpu.eax * 8 + 0x7dd814, cpu.edx);
        put(app, cpu.eax * 4 + 0x7dd374, cpu.edx);
        put(app, cpu.eax * 4 + 0x7dd364, cpu.edx);
    } while (i32(cpu.eax) < 2);
    cpu.ecx = at(app, 0x6fd4ac);
    cpu.edi = 0;
    cpu.eax = name;
    put(app, 0x560118, cpu.edi);
    put(app, 0x7dd838, cpu.edi);
    put(app, 0x7dd830, cpu.edi);
    if (!call(app, cpu, 0x4df690, {name, 0x54030c, 0x7a27b4, cpu.ecx, cpu.ecx}))
        return;
    cpu.esi = at(app, 0x6fd4c0) != 0 ? 0x540320 : 0x540328;
    cpu.edi = name;
    appendString(app, cpu, name, cpu.esi);
    cpu.edi = name;
    cpu.edx = 0;
    cpu.eax = name;
    if (!call(app, cpu, 0x4e0fe0))
        return;
    cpu.edi = 0;
    put(app, 0x7dd828, cpu.eax);
    put(app, 0x7dd384, cpu.eax);
    put(app, 0x7dd380, cpu.eax);
    put(app, 0x7dd364, cpu.edi);
    put(app, 0x7dd360, cpu.edi);
    leave(cpu, kept, kEcx | kEdx | kEsi | kEdi);
}

/* 0x4c8440: the co-driver's script freed. */
void speechFree(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.ebp = cpu.esp = kept.frame(3);
    cpu.edx = at(app, 0x7dd828);
    if (cpu.edx != 0)
    {
        cpu.eax = cpu.edx;
        cpu.ecx = 0;
        if (!call(app, cpu, 0x4e1890))
            return;
        put(app, 0x7dd828, cpu.ecx);
        put(app, 0x7dd384, cpu.ecx);
        put(app, 0x7dd380, cpu.ecx);
    }
    leave(cpu, kept, kEcx | kEdx);
}

/* 0x4c85a0: line eax (9 words: effect, volume, pitch, pan, bank, player,
 * kind, the game's, ...) said, or queued (16 at most) while the player's
 * line plays; held back while a line is being said (0x560118), silent over
 * the radio for kind 5. */
void speechLine(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const unsigned pushed = kEbx | kEcx | kEdx | kEsi | kEdi;
    cpu.ebp = cpu.esp = kept.frame(6);
    cpu.esi = cpu.eax;
    cpu.edi = at(app, cpu.eax + 0x14);
    if (i32(cpu.edi) > 1)
        cpu.edi = 0;
    cpu.eax = cpu.edi * 4;
    if (at(app, cpu.eax + 0x7dd348) == 0)
    {
        cpu.ecx = at(app, 0x560118);
        if (cpu.ecx != 0)
            return leave(cpu, kept, pushed);
        if (!(at(app, 0x7dd81c) != 0 && at(app, cpu.esi + 0x18) == 5))
            cpu.ecx = at(app, cpu.esi + 4);
        cpu.edx = at(app, cpu.esi + 8);
        cpu.ebx = at(app, cpu.esi + 0xc);
        const reg32 pitch = cpu.edx;
        cpu.eax = at(app, cpu.esi + 0x10);
        cpu.edx = at(app, cpu.esi);
        if (!call(app, cpu, 0x4182b0, {pitch}))
            return;
        cpu.ecx = cpu.eax;
        cpu.eax = cpu.edi * 4;
        put(app, cpu.eax + 0x7dd370, cpu.ecx);
        cpu.ecx = 1;
        put(app, cpu.eax + 0x7dd348, cpu.ecx);
        if (at(app, cpu.esi + 0x18) == 2)
        {
            cpu.edx = cpu.edi;
            put(app, cpu.eax + 0x7dd340, cpu.ecx);
            cpu.ebx = 0;
            cpu.eax = at(app, cpu.esi + 0x1c);
            if (!call(app, cpu, 0x482030))
                return;
        }
        cpu.ecx = at(app, cpu.esi + 0x18);
        if (cpu.ecx == 4 || cpu.ecx == 3)
        {
            cpu.edx = at(app, cpu.esi + 0x18);
            put(app, cpu.edi * 4 + 0x7dd358, cpu.edx);
        }
        return leave(cpu, kept, pushed);
    }
    cpu.edi = at(app, cpu.eax + 0x7dd378);
    if (i32(cpu.edi) >= 0x10)
        return leave(cpu, kept, pushed);
    cpu.ebx = cpu.edi;
    cpu.edx = cpu.edi + 1;
    put(app, cpu.eax + 0x7dd378, cpu.edx);
    cpu.ecx = at(app, cpu.esi + 0x14) != 0 ? 0x7dd5d8 : 0x7dd398;
    cpu.eax = cpu.ebx * 9;
    for (reg32 k = 0; k < 0x24; k += 4)
    {
        cpu.edx = at(app, cpu.esi + k);
        put(app, cpu.ecx + cpu.eax * 4 + k, cpu.edx);
    }
    leave(cpu, kept, pushed);
}

/* 0x4c8d10: player eax's co-driver (0x6fd49c on): along the track's script
 * of calls (0x7dd380's, its lap at 0x7dd360), as the car comes up to each
 * -- by its speed, a little ahead -- the call queued (0x4c8ca0); the script
 * started over on a new lap, or when the car stops or goes backwards. */
void coDriverTick(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    x86::FPU& fpu = cpu.fpu;
    const unsigned pushed = kEbx | kEcx | kEdx | kEsi | kEdi;
    cpu.ebp = kept.frame(6);
    cpu.esp = cpu.ebp - 0x14;
    const reg32 b = cpu.ebp;
    auto f32 = [&](reg32 at) { return x86::Float(app->getMemory<float>(at)); };
    cpu.ecx = cpu.eax;
    cpu.eax <<= 2;
    if (at(app, cpu.eax + 0x7dd380) == 0 || at(app, 0x6fd49c) == 0)
        return leave(cpu, kept, pushed);
    if (cpu.ecx == 0)
    {
        cpu.esi = at(app, 0x6fd4b4);
        if (i32(cpu.esi) <= s32(app, cpu.eax + 0x7dd360))
            return leave(cpu, kept, pushed);
    }
    if (cpu.ecx == 0 && at(app, 0x6fd3b0) != 1)
    {
        cpu.eax = at(app, 0x6fd4f4);
        cpu.ebx = at(app, cpu.eax * 4 + 0x5efa48);
    }
    else
        cpu.ebx = at(app, cpu.ecx * 4 + 0x5efa48);
    put(app, b - 8, at(app, cpu.ebx + 0x7c0));
    put(app, b - 0xc, at(app, cpu.ebx + 0x224));
    cpu.eax = at(app, cpu.ecx * 4 + 0x7dd380);
    cpu.edi = at(app, 0x5dd940);
    cpu.esi = at(app, cpu.eax);
    cpu.edx = at(app, cpu.eax + 4);
    // The revs, unsigned (fldz; fcomp; jae: as they are unless 0 is at or
    // above them), scaled and chopped.
    const x86::Float revs = f32(cpu.ebx + 0x4f4);
    if (fcomp(cpu, x86::Float(0.0), revs).below)
    {
        cpu.eax = at(app, cpu.ebx + 0x4f4);
        put(app, b - 0x10, cpu.eax);
    }
    else
        app->getMemory<float>(b - 0x10) = float(-revs);
    fpu.push(fpu.mul(f32(b - 0x10), f32(0x540330)));
    if (!call(app, cpu, kChop))
        return;
    put(app, b - 0x14, reg32(fpu.toInteger<i32>(fpu.st(0))));
    fpu.pop();
    if (i32(cpu.edx) < 2)
        cpu.edx = 2;
    if (at(app, 0x6fd4c0) != 0)
    {
        putByte(app, b - 5, byte(app, b - 5) ^ 0x80);
        cpu.eax = cpu.edi - cpu.esi;
        cpu.esi = cpu.eax;
    }
    // How far ahead: the speed (fistp'd) times the call's lead (16.16,
    // rounded), a sixth of it.
    fpu.push(fpu.mul(f32(b - 8), x86::Float(app->getMemory<double>(0x540334))));
    cpu.eax = reg32(fpu.toInteger<i32>(fpu.st(0)));
    fpu.pop();
    {
        const std::int64_t p = std::int64_t(i32(cpu.eax)) * i32(cpu.edx);
        const reg32 lo = reg32(p), hi = reg32(std::uint64_t(p) >> 32);
        cpu.eax = (lo >> 16) + (hi << 16) + ((lo >> 15) & 1);
    }
    cpu.edx = cpu.eax;
    towardZero(cpu, 16);
    cpu.edx = cpu.eax;
    put(app, b - 4, 6);
    cpu.eax = cpu.edx;
    idiv(cpu, 6);
    cpu.edx = cpu.eax;
    // fldz; fcomp; ja: backwards when 0 is above the speed.
    const Compared speed = fcomp(cpu, x86::Float(0.0), f32(b - 8));
    if (!(speed.below || speed.equal) || at(app, cpu.ebx + 0x998) != 0)
    {
        cpu.edx = at(app, at(app, cpu.ecx * 4 + 0x5efa48) + 0x204);
        put(app, cpu.ecx * 4 + 0x7dd360, cpu.edx);
        cpu.edx = at(app, 0x7dd828);
        put(app, cpu.ecx * 4 + 0x7dd380, cpu.edx);
        return leave(cpu, kept, pushed);
    }
    cpu.eax = cpu.ecx * 4;
    cpu.edi = reg32(mul(i32(cpu.edi), s32(app, cpu.eax + 0x7dd360)));
    cpu.esi += cpu.edi;
    cpu.edi = at(app, b - 0xc);
    cpu.edx += cpu.edi;
    // The script's next entry: 0x7dd380 moved on two words, read.
    auto next = [&] {
        cpu.eax = cpu.ecx * 4;
        cpu.edi = at(app, cpu.eax + 0x7dd380) + 4;
        put(app, cpu.eax + 0x7dd380, cpu.edi);
        cpu.ebx = at(app, cpu.edi);
        cpu.edx = cpu.edi;
    };
    bool passed = false;
    if (i32(cpu.esi) < i32(cpu.edi))
    {
        // Passed: skipped to the end of this entry's calls.
        put(app, cpu.eax + 0x7dd380, at(app, cpu.eax + 0x7dd380) + 4);
        do
            next();
        while (i32(cpu.ebx) > -1);
        passed = true;
    }
    else if (i32(cpu.edx) >= i32(cpu.esi))
    {
        put(app, cpu.eax + 0x7dd380, at(app, cpu.eax + 0x7dd380) + 4);
        for (;;)
        {
            next();
            if (i32(cpu.ebx) <= -1)
                break;
            cpu.esi = at(app, 0x6fd4c4);
            cpu.eax = cpu.ebx;
            if (cpu.esi != 0)
                cpu.eax = byte(app, cpu.ebx + 0x560ae2);
            if (cpu.eax == 0xf)
            {
                cpu.edx = at(app, cpu.ecx * 4 + 0x7dd380);
                cpu.ebx = at(app, cpu.edx + 4) == 0x11 ? 0xb : 3;
                cpu.esi = at(app, 0x6fd4c4);
                cpu.edx = cpu.ebx;
                if (cpu.esi != 0)
                    cpu.edx = cpu.ebx == 3 ? 0xb : 3;
            }
            else
                cpu.edx = reg32(i32(at(app, cpu.eax + 0x560ac9)) >> 24);
            if (cpu.eax == 0xc && s32(app, b - 0x14) <= 0x3c)
                continue;
            cpu.ebx = cpu.ecx;
            if (!call(app, cpu, 0x4c8ca0))
                return;
        }
        passed = true;
    }
    if (passed)
    {
        cpu.edx = cpu.edi + 4;
        put(app, cpu.eax + 0x7dd380, cpu.edx);
    }
    cpu.eax = cpu.ecx * 4;
    cpu.edx = at(app, cpu.eax + 0x7dd380);
    if (at(app, cpu.edx) == 0xfffffffe)
    {
        cpu.ebx = at(app, cpu.eax + 0x7dd360) + 1;
        cpu.edx = at(app, 0x7dd828);
        put(app, cpu.eax + 0x7dd380, cpu.edx);
        put(app, cpu.eax + 0x7dd360, cpu.ebx);
    }
    leave(cpu, kept, pushed);
}

/* 0x4c8f90: a line of the race voice bank (0x57119c) queued -- effect eax,
 * kind ebx, for player edx -- once the race is under way (0x7d3684). */
void queueRaceLine(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.ebp = kept.frame(4);
    cpu.esp = cpu.ebp - 0x24;
    if (s32(app, 0x7d3684) >= 0x200)
    {
        cpu.edi = 0x40;
        cpu.esi = 0x7f;
        cpu.ecx = at(app, 0x6fd3b0);
        put(app, cpu.ebp - 0x1c, cpu.edi);
        put(app, cpu.ebp - 0x20, cpu.esi);
        if (cpu.ecx == 1)
        {
            cpu.ecx = cpu.edx != 0 ? 0xc000 : 0x3fff;
            put(app, cpu.ebp - 0x18, cpu.ecx);
        }
        else
        {
            cpu.esi = 0;
            put(app, cpu.ebp - 0x18, cpu.esi);
        }
        put(app, cpu.ebp - 0x24, cpu.eax);
        put(app, cpu.ebp - 0x10, cpu.edx);
        cpu.eax = at(app, 0x57119c);
        put(app, cpu.ebp - 0xc, cpu.ebx);
        put(app, cpu.ebp - 0x14, cpu.eax);
        cpu.eax = cpu.ebp - 0x24;
        put(app, cpu.edx * 4 + 0x7dd358, cpu.ebx);
        if (!call(app, cpu, 0x4c85a0))
            return;
    }
    leave(cpu, kept, kEcx | kEsi | kEdi);
}

/* 0x4c9010: player eax's line for event edx, unless one is queued: for 1,
 * line 1 mostly, else 10 or 11; for 8, 7 or 8; else the event's own. */
void raceEventLine(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.ebp = cpu.esp = kept.frame(3);
    cpu.ecx = cpu.eax;
    cpu.eax = cpu.edx;
    cpu.edx = at(app, cpu.ecx * 4 + 0x7dd358);
    if (cpu.edx != 0)
        return leave(cpu, kept, kEbx | kEcx);
    if (cpu.eax == 1)
    {
        cpu.ebx = 0x64;
        if (!call(app, cpu, 0x4e0d88))
            return;
        udiv(cpu, cpu.ebx);
        if (cpu.edx > 0x46)
        {
            if (!call(app, cpu, 0x4e0d88))
                return;
            cpu.ebx = 4;
            cpu.eax = (cpu.eax & 1) + 0xa;
            cpu.edx = cpu.ecx;
        }
        else
        {
            cpu.ebx = 4;
            cpu.eax = 1;
            cpu.edx = cpu.ecx;
        }
    }
    else
    {
        cpu.ebx = 4;
        cpu.edx = cpu.ecx;
        if (cpu.eax == 8)
        {
            if (!call(app, cpu, 0x4e0d88))
                return;
            cpu.eax = (cpu.eax & 1) + 7;
        }
        else
            --cpu.eax;
        ++cpu.eax;
    }
    if (!call(app, cpu, 0x4c8f90))
        return;
    leave(cpu, kept, kEbx | kEcx);
}

/* 0x4c9090: the line for player edx about car eax's gap to the leader
 * (ebx: to be said): the gap (0x485a60's), or 0x380 with none, in eax. */
void gapLine(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const unsigned pushed = kEcx | kEsi | kEdi;
    cpu.ebp = kept.frame(4);
    cpu.esp = cpu.ebp - 4;
    cpu.esi = cpu.eax;
    cpu.edi = cpu.edx;
    put(app, cpu.ebp - 4, cpu.ebx);
    if ((byte(app, cpu.eax + 0x200) & 1) != 0 && at(app, cpu.esi + 0x2c4) == 3)
    {
        cpu.eax = 0;
        return leave(cpu, kept, pushed);
    }
    for (cpu.eax = 0; i32(cpu.eax) < s32(app, 0x5efda0); ++cpu.eax)
    {
        cpu.ebx = at(app, cpu.eax * 4 + 0x5efc48);
        if (at(app, cpu.ebx + 0x2bc) == 1)
        {
            cpu.edx = cpu.esi;
            cpu.eax = cpu.ebx;
            if (!call(app, cpu, 0x485a60))
                return;
            cpu.ecx = cpu.eax;
            break;
        }
    }
    auto done = [&] {
        cpu.eax = cpu.ecx;
        leave(cpu, kept, pushed);
    };
    if (at(app, cpu.edi * 4 + 0x7dd358) != 0)
        return done();
    if (at(app, cpu.esi + 8) == 0)
        cpu.ecx = 0x380;
    if (at(app, cpu.ebp - 4) == 0)
        return done();
    if (i32(cpu.ecx) < 0x40)
    {
        if (at(app, cpu.esi + 0x2bc) != 1)
            cpu.ecx = 0x40;
        else
        {
            if (!call(app, cpu, 0x4e0d88))
                return;
            cpu.ebx = 4;
            cpu.eax = (cpu.eax & 1) + 0xa;
            cpu.edx = cpu.edi;
            if (!call(app, cpu, 0x4c8f90))
                return;
            return done();
        }
    }
    if (i32(cpu.ecx) > 0x300)
    {
        if (!call(app, cpu, 0x4e0d88))
            return;
        cpu.ebx = 4;
        cpu.eax = (cpu.eax & 1) + 0x1d;
        cpu.edx = cpu.edi;
        if (!call(app, cpu, 0x4c8f90))
            return;
        return done();
    }
    if (!call(app, cpu, 0x4e0d88))
        return;
    cpu.ebx = cpu.eax;
    cpu.edx = cpu.ecx;
    towardZero(cpu, 6);
    cpu.ebx = ((cpu.ebx << 4) & 1) + 0x11;
    cpu.edx = cpu.edi;
    cpu.eax += cpu.ebx;
    cpu.ebx = 4;
    --cpu.eax;
    if (!call(app, cpu, 0x4c8f90))
        return;
    done();
}

/* 0x4c91a0: player eax's line for a lap time edx (seconds, less 3), unless
 * one is queued: by tens of seconds where the voice has them, else line
 * 0x4a. */
void lapTimeLine(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.ebp = cpu.esp = kept.frame(4);
    cpu.ecx = cpu.eax;
    cpu.ebx = at(app, cpu.eax * 4 + 0x7dd358);
    cpu.edx += 3;
    if (cpu.ebx != 0 || i32(cpu.edx) < 0x32)
        return leave(cpu, kept, kEbx | kEcx | kEsi);
    // By tens: as the code's two tests of the voice's language (0x6fbc68)
    // and the units (0x6fbb4c) go.
    auto tens = [&] {
        if (i32(cpu.edx) < 0xd2)
        {
            cpu.esi = at(app, 0x6fbc68);
            if (cpu.esi == 1 || cpu.esi == 2)
                return true;
            if (cpu.esi == 0 && at(app, 0x6fbb4c) == 0)
                return true;
        }
        if (i32(cpu.edx) >= 0x136)
            return false;
        cpu.esi = at(app, 0x6fbc68);
        if (cpu.esi == 1 || cpu.esi == 2)
            return false;
        if (cpu.esi != 0)
            return true;
        return at(app, 0x6fbb4c) != 0;
    };
    if (tens())
    {
        cpu.ebx = 0xa;
        cpu.eax = cpu.edx;
        idiv(cpu, 0xa);
        cpu.ebx = 4;
        cpu.eax += 0x2b;
    }
    else
    {
        cpu.ebx = 4;
        cpu.eax = 0x4a;
    }
    cpu.edx = cpu.ecx;
    if (!call(app, cpu, 0x4c8f90))
        return;
    leave(cpu, kept, kEbx | kEcx | kEsi);
}

/* 0x4c9240: the description bank eax (".bnk" added) loaded, if it is there
 * and none is: its handle kept (0x7dd844), the header copied out of the file
 * where SND asks (0x7dd84c); 1, or 0. */
void descriptionLoad(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const unsigned pushed = kEbx | kEcx | kEdx | kEsi | kEdi;
    cpu.ebp = kept.frame(6);
    cpu.esp = cpu.ebp - 0x104;
    const reg32 name = cpu.ebp - 0x104;
    auto none = [&] {
        cpu.eax = 0;
        leave(cpu, kept, pushed);
    };
    if (at(app, 0x55290c) == 0)
        return none();
    copyString(app, cpu, name, cpu.eax);
    appendString(app, cpu, name, 0x54033c);
    cpu.edi = name;
    cpu.eax = name;
    if (!call(app, cpu, 0x4e0e60))
        return;
    if (cpu.eax == 0 || at(app, 0x7dd838) != 0)
        return none();
    cpu.eax = name;
    cpu.edx = 0;
    if (!call(app, cpu, 0x4e0ec0))
        return;
    cpu.ecx = cpu.eax;
    cpu.ebx = cpu.eax;
    cpu.edx = cpu.eax;
    cpu.eax = cpu.ebp - 4;
    if (!call(app, cpu, 0x4e8d20))
        return;
    cpu.edi = cpu.eax;
    if (cpu.eax == 7)
    {
        cpu.eax = at(app, cpu.ebp - 4);
        if (!call(app, cpu, 0x4e8db0))
            return;
        cpu.ebx ^= cpu.ecx;
        cpu.edx = cpu.eax;
        cpu.eax = 0x540344;
        if (!call(app, cpu, 0x4e1620))
            return;
        cpu.edx = at(app, cpu.ebp - 4);
        cpu.ebx = cpu.eax;
        if (!call(app, cpu, 0x4e8e20))
            return;
        cpu.eax = cpu.ecx;
        if (!call(app, cpu, 0x4e1890))
            return;
    }
    if (i32(cpu.edi) < 0)
        return none();
    cpu.eax = at(app, cpu.ebp - 4);
    put(app, 0x7dd84c, cpu.ebx);
    cpu.ebx = 1;
    put(app, 0x7dd844, cpu.eax);
    put(app, 0x7dd838, cpu.ebx);
    cpu.eax = cpu.ebx;
    leave(cpu, kept, pushed);
}

/* 0x4c9340: the description's part eax spoken. */
void descriptionSpeak(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.ebp = cpu.esp = kept.frame(5);
    cpu.esi = cpu.eax;
    cpu.ecx = 0x7f;
    cpu.eax = at(app, 0x7dd844);
    cpu.edx = cpu.esi;
    cpu.ebx = 0;
    if (!call(app, cpu, 0x4184f0, {0x40}))
        return;
    cpu.edx = 1;
    put(app, 0x7dd82c, cpu.eax);
    put(app, 0x7dd834, cpu.esi);
    put(app, 0x7dd830, cpu.edx);
    leave(cpu, kept, kEbx | kEcx | kEdx | kEsi);
}

/* 0x4c9380: the description's tick: the next part spoken when one is done;
 * when they are (or it is stopped, 0x560af8), the bank removed and the
 * music back up. */
void descriptionTick(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const unsigned pushed = kEbx | kEdx | kEsi | kEdi;
    cpu.ebp = cpu.esp = kept.frame(5);
    if (at(app, 0x7dd830) == 0)
        return leave(cpu, kept, pushed);
    auto musicUp = [&] {
        put(app, 0x560af8, cpu.eax);
        cpu.eax = 0x64;
        if (!call(app, cpu, 0x4e7470))
            return;
        leave(cpu, kept, pushed);
    };
    if (at(app, 0x7dd83c) == 0x33)
    {
        if (at(app, 0x560af8) == 0)
        {
            cpu.eax = at(app, 0x7dd82c);
            if (!call(app, cpu, 0x4e8fd0))
                return;
            if (cpu.eax == 0)
                return leave(cpu, kept, pushed);
        }
        cpu.ebx = 0xffffffff;
        cpu.eax = at(app, 0x7dd82c);
        cpu.edx = 0;
        if (!call(app, cpu, 0x4e9420))
            return;
        cpu.eax = 0;
        cpu.edx = at(app, 0x6fbbe8);
        put(app, 0x7dd830, cpu.eax);
        return musicUp();
    }
    if (at(app, 0x560af8) != 0)
    {
        cpu.ebx = 0xffffffff;
        cpu.eax = at(app, 0x7dd82c);
        cpu.edx = 0;
        if (!call(app, cpu, 0x4e9420))
            return;
        cpu.eax = at(app, 0x7dd844);
        if (!call(app, cpu, 0x4e8c1c))
            return;
        cpu.esi = at(app, 0x7dd84c);
        if (cpu.esi != 0)
        {
            cpu.eax = cpu.esi;
            cpu.edi = 0;
            if (!call(app, cpu, 0x4e1890))
                return;
            put(app, 0x7dd84c, cpu.edi);
        }
        cpu.eax = 0;
        cpu.edx = at(app, 0x6fbbe8);
        put(app, 0x7dd830, cpu.eax);
        put(app, 0x7dd838, cpu.eax);
        return musicUp();
    }
    cpu.eax = at(app, 0x7dd82c);
    if (!call(app, cpu, 0x4e8fd0))
        return;
    if (cpu.eax == 0)
        return leave(cpu, kept, pushed);
    cpu.ebx = at(app, 0x7dd834) + 1;
    cpu.eax = at(app, 0x7dd844);
    cpu.edx = cpu.ebx;
    put(app, 0x7dd834, cpu.ebx);
    if (!call(app, cpu, 0x4fb1e0))
        return;
    if (cpu.eax != 0)
    {
        cpu.eax = at(app, 0x7dd834);
        if (!call(app, cpu, 0x4c9340))
            return;
        return leave(cpu, kept, pushed);
    }
    put(app, 0x560af8, 1);
    leave(cpu, kept, pushed);
}

/* 0x4c9490: the description, if it is spoken, stopped, the music back up. */
void descriptionStop(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.ebp = cpu.esp = kept.frame(2);
    if (at(app, 0x7dd830) != 0)
    {
        put(app, 0x560af8, 1);
        if (!call(app, cpu, 0x4c9380))
            return;
        cpu.eax = 0x64;
        cpu.edx = at(app, 0x6fbbe8);
        if (!call(app, cpu, 0x4e7470))
            return;
    }
    leave(cpu, kept, kEdx);
}

/* 0x4c95e0, 0x4c99f0: the spoken line's status. */
void spokenStatus(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.ebp = cpu.esp = kept.frame(1);
    cpu.eax = at(app, 0x7dd82c);
    if (!call(app, cpu, 0x4e8fd0))
        return;
    leave(cpu, kept, 0);
}

/* 0x4c95f0: a description spoken -- track ecx (eax) of the menus' (0x32) or
 * of the cars' (0x34) in language ebx, or (0x33) part eax of the one
 * loaded -- the music lowered for it. */
void descriptionStart(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const unsigned pushed = kEcx | kEsi | kEdi;
    const reg32 frame = kept.frame(4);
    cpu.esp = frame - 0x104;
    cpu.ebp = frame - 0x182;
    const reg32 name = cpu.ebp + 0x7e, kind = cpu.ebp + 0x17e;
    cpu.ecx = cpu.eax;
    put(app, kind, cpu.edx);
    cpu.edx = cpu.ebx;
    if (at(app, 0x7dd830) != 0 && !call(app, cpu, 0x4c9490))
        return;
    cpu.esi = at(app, kind);
    auto musicDown = [&] {
        cpu.eax = at(app, 0x6fbbe8);
        halve(cpu);
        cpu.edx = cpu.eax;
        cpu.eax = 0x64;
        if (!call(app, cpu, 0x4e7470))
            return false;
        cpu.eax = at(app, kind);
        put(app, 0x7dd83c, cpu.eax);
        return true;
    };
    if (cpu.esi == 0x33)
    {
        if (at(app, 0x7dd838) != 0)
        {
            if (!musicDown())
                return;
            cpu.eax = cpu.ecx;
            if (!call(app, cpu, 0x4c9340))
                return;
        }
        return leave(cpu, kept, pushed);
    }
    if ((cpu.esi != 0x32 && cpu.esi != 0x34) || i32(cpu.ecx) < 0 || i32(cpu.ecx) > 0x31)
        return leave(cpu, kept, pushed);
    const reg32 table = cpu.esi == 0x32 ? 0x560afc : 0x560b18;
    copyString(app, cpu, name, 0x7a28b4);
    cpu.eax = name;
    if (!call(app, cpu, 0x4529a0))
        return;
    cpu.eax = cpu.ecx;
    cpu.edi = name;
    if (!call(app, cpu, 0x4392b0))
        return;
    appendString(app, cpu, name, cpu.eax);
    cpu.eax = name;
    cpu.edi = name;
    if (!call(app, cpu, 0x4529a0))
        return;
    appendString(app, cpu, name, at(app, cpu.edx * 4 + table));
    cpu.eax = name;
    if (!call(app, cpu, 0x4c9240))
        return;
    if (cpu.eax != 0)
    {
        if (!musicDown())
            return;
        cpu.eax = 0;
        if (!call(app, cpu, 0x4c9340))
            return;
    }
    leave(cpu, kept, pushed);
}

/* 0x4c9860: the system tasks run, then the description's tick. */
void descriptionService(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.ebp = cpu.esp = kept.frame(1);
    cpu.eax = 0;
    if (!call(app, cpu, 0x4e7630) || !call(app, cpu, 0x4c9380))
        return;
    leave(cpu, kept, 0);
}

/* 0x4c9890: the race voice bank eax loaded -- from the units' folder (one of
 * five), "2" more in the split screen -- as bank 2 (0x7dd838 set) or 1. */
void raceVoiceLoad(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 frame = kept.frame(6);
    cpu.esp = frame - 0x100;
    cpu.ebp = frame - 0x17e;
    const reg32 name = cpu.ebp + 0x7e;
    cpu.edx = cpu.eax;
    cpu.eax = at(app, 0x6fbb4c);
    static const reg32 folders[] = {0x7a2b34, 0x7a2bb4, 0x7a2c34, 0x7a2cb4, 0x7a2d34, 0x7a2b34};
    if (cpu.eax <= 5)
        copyString(app, cpu, name, folders[cpu.eax]);
    cpu.edi = name;
    appendString(app, cpu, name, at(app, cpu.edx * 4 + 0x560b50));
    if (at(app, 0x6fd3b0) == 1)
        appendString(app, cpu, name, 0x540354);
    cpu.edi = name;
    const bool second = cpu.edx != 0;
    cpu.edx = second ? 2 : 1;
    cpu.eax = name;
    cpu.ebx = 0;
    if (!call(app, cpu, 0x410b50))
        return;
    if (second)
        put(app, 0x7dd838, 1);
    leave(cpu, kept, kEbx | kEcx | kEdx | kEsi | kEdi);
}

/* 0x4c9990: effect edx * 16 + eax of the car bank (eax above 4) or the first
 * bank, spoken at full volume. */
void carLineSpeak(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.ebp = cpu.esp = kept.frame(3);
    cpu.ecx = 0x7f;
    cpu.edx = (cpu.edx << 4) + cpu.eax;
    cpu.ebx = 0;
    cpu.eax = i32(cpu.eax) > 4 ? at(app, 0x57113c) : at(app, 0x571130);
    if (!call(app, cpu, 0x4184f0, {0x40}))
        return;
    put(app, 0x7dd82c, cpu.eax);
    leave(cpu, kept, kEbx | kEcx);
}

/* 0x4c99d0: the spoken line faded out. */
void spokenStop(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.ebp = cpu.esp = kept.frame(3);
    cpu.ebx = 0xffffffff;
    cpu.eax = at(app, 0x7dd82c);
    cpu.edx = 0;
    if (!call(app, cpu, 0x4e9420))
        return;
    leave(cpu, kept, kEbx | kEdx);
}

/* 0x4c9a00: the race voice banks removed and their header copies freed. */
void raceVoiceFree(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.ebp = cpu.esp = kept.frame(5);
    cpu.eax = at(app, 0x571130);
    if (!call(app, cpu, 0x4e8c1c))
        return;
    cpu.eax = at(app, 0x57113c);
    if (!call(app, cpu, 0x4e8c1c))
        return;
    cpu.edx = at(app, 0x571138);
    if (cpu.edx != 0)
    {
        cpu.eax = cpu.edx;
        cpu.ecx = 0;
        if (!call(app, cpu, 0x4e1890))
            return;
        put(app, 0x571138, cpu.ecx);
    }
    if (at(app, 0x7dd838) != 0)
    {
        cpu.eax = at(app, 0x57113c);
        if (!call(app, cpu, 0x4e8c1c))
            return;
        cpu.esi = at(app, 0x571144);
        if (cpu.esi != 0)
        {
            cpu.eax = cpu.esi;
            cpu.edi = 0;
            if (!call(app, cpu, 0x4e1890))
                return;
            put(app, 0x571144, cpu.edi);
        }
    }
    cpu.eax = 0;
    put(app, 0x7dd838, cpu.eax);
    leave(cpu, kept, kEcx | kEdx | kEsi | kEdi);
}

}  // namespace snd
}  // namespace nfs3hp
