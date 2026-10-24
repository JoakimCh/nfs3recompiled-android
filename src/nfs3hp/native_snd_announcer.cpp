#include "native_snd.h"

/* The race's announcer and its music, native (native_snd.h says how): per
 * car of a player each tick -- the keys that ask for a gap, a position or a
 * lap time spoken; the lap's lines (a new lap, the best one, the last lap,
 * the lap number, the position at the end) queued on the race voice
 * (0x4c85a0, a line of 9 words); the speech's tick; then the race music's
 * intensity by the position and the laps left (Pathfinder's control), its
 * event by where on the track the car is (0x4211c0's section), traced.
 *
 * The game's state: 0x5710c8 each player's last lap (a byte), 0x5710d0 the
 * lap's start, 0x5710f0 the lap's time, 0x552904 the best lap, 0x552860 and
 * 0x55285c the laps for the music, 0x552850 its intensity, 0x552834 its
 * event, 0x552d7c the long wait's mark. */
namespace nfs3hp
{
namespace snd
{

namespace
{

constexpr reg32 kQueue = 0x4c85a0, kRandom = 0x4e0d88, kTrace = 0x42d510, kVoice = 0x571178;

}  // namespace

/* 0x412d60: car eax's announcer and music tick. */
void raceAnnouncer(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    x86::FPU& fpu = cpu.fpu;
    const unsigned pushed = kEbx | kEcx | kEdx | kEsi | kEdi;
    cpu.ebp = kept.frame(6);
    cpu.esp = cpu.ebp - 0x3c;
    const reg32 b = cpu.ebp, line = b - 0x3c;
    auto f32 = [&](reg32 at) { return x86::Float(app->getMemory<float>(at)); };
    auto own = [&] { return reg32(byte(app, b - 4)); };
    auto side = [&] { return reg32(byte(app, b - 8)); };
    // The line's pan: the player's side in the split screen.
    auto sidePan = [&] { return side() != 0 ? 0xc000u : 0x3fffu; };
    cpu.ecx = cpu.eax;
    setByte0(cpu.eax, byte(app, cpu.eax + 0x1f0));
    putByte(app, b - 4, reg8(cpu.eax));
    cpu.eax = own();
    cpu.eax = at(app, cpu.eax * 4 + 0x5efac8);
    cpu.edx = at(app, cpu.ecx + 0x2c);
    cpu.esi = at(app, cpu.eax + 0x2bc);
    cpu.eax = cpu.edx != 0 ? reg32(byte(app, cpu.edx + 3)) : 0;
    cpu.edx = at(app, cpu.ecx + 0x1f0);
    putByte(app, cpu.edx + 0x5710a0, reg8(cpu.eax));
    if (!call(app, cpu, 0x40a330) || !call(app, cpu, 0x4129b0))
        return;
    if (at(app, 0x6fd3b0) == 1)
    {
        setByte0(cpu.eax, byte(app, b - 4));
        putByte(app, b - 8, reg8(cpu.eax));
    }
    else
    {
        setByte1(cpu.eax, 0);
        putByte(app, b - 8, 0);
    }
    // The keys: 0x13 the music on and off.
    cpu.edx = 1;
    cpu.eax = 0x13;
    if (!call(app, cpu, 0x48f7b0))
        return;
    if (cpu.eax != 0 && side() == 0)
    {
        cpu.eax = at(app, 0x552794) == 0 ? 1 : 0;
        put(app, 0x552794, cpu.eax);
    }
    if (at(app, 0x6fd3b8) == 3)
    {
        cpu.eax = side();
        if (!call(app, cpu, 0x4188a0))
            return;
    }
    if (at(app, 0x6fd3b0) != 1 && !((byte(app, cpu.ecx + 0x200) & 1) != 0 && at(app, cpu.ecx + 0x2c4) == 3)
        && at(app, 0x6fd520) != 0)
    {
        if ((byte(app, cpu.ecx + 0x200) & 0x20) == 0)
        {
            cpu.edx = 1;
            cpu.eax = 2;
            if (!call(app, cpu, 0x48f7b0))
                return;
            if (cpu.eax != 0)
            {
                cpu.ebx = 1;
                cpu.eax = cpu.ecx;
                cpu.edx = 0;
                if (!call(app, cpu, 0x4c9090))
                    return;
            }
            cpu.edx = 1;
            cpu.eax = 3;
            if (!call(app, cpu, 0x48f7b0))
                return;
            if (cpu.eax != 0)
            {
                cpu.edx = cpu.esi;
                cpu.eax = 0;
                if (!call(app, cpu, 0x4c9010))
                    return;
            }
        }
        cpu.edx = 1;
        cpu.eax = 4;
        if (!call(app, cpu, 0x48f7b0))
            return;
        if (cpu.eax != 0)
        {
            // The lap time: the revs' counter, unsigned, scaled for the
            // voice's units.
            cpu.eax = at(app, 0x6fbc68);
            const bool metric = cpu.eax == 1 || cpu.eax == 2 || (cpu.eax == 0 && at(app, 0x6fbb4c) == 0);
            const reg32 local = metric ? b - 0x10 : b - 0x14, scale = metric ? 0x536a18 : 0x536a1c;
            const x86::Float revs = f32(cpu.ecx + 0x4f4);
            if (fcomp(cpu, x86::Float(0.0), revs).below)
            {
                cpu.eax = at(app, cpu.ecx + 0x4f4);
                put(app, local, cpu.eax);
            }
            else
                app->getMemory<float>(local) = float(-revs);
            fpu.push(fpu.mul(f32(local), f32(scale)));
            cpu.eax = 0;
            if (!call(app, cpu, kChop))
                return;
            put(app, b - 0x18, reg32(fpu.toInteger<i32>(fpu.st(0))));
            fpu.pop();
            cpu.edx = at(app, b - 0x18);
            if (!call(app, cpu, 0x4c91a0))
                return;
        }
    }
    if (at(app, 0x6fd3b8) != 3)
    {
        // A new lap: the lap's line, the best lap's.
        cpu.eax = own();
        cpu.edx = byte(app, cpu.eax + 0x5710c8);
        cpu.ebx = at(app, cpu.ecx + 0x204);
        bool done = false;
        if (cpu.edx != cpu.ebx && i32(cpu.ebx) > 0)
        {
            cpu.edx = cpu.eax * 4;
            cpu.eax = at(app, 0x7d3684) - at(app, cpu.edx + 0x5710d0);
            cpu.ebx = at(app, cpu.edx + 0x5710d0);
            cpu.edi = at(app, 0x552904);
            if (i32(cpu.eax) < i32(cpu.edi) || cpu.edi == 0)
            {
                cpu.edx = 0x7f;
                cpu.ebx = 0x40;
                cpu.eax = at(app, kVoice);
                cpu.edi = at(app, 0x6fd3b0);
                put(app, b - 0x38, cpu.edx);
                put(app, b - 0x34, cpu.ebx);
                put(app, b - 0x2c, cpu.eax);
                cpu.eax = cpu.edi == 1 ? sidePan() : 0;
                put(app, b - 0x30, cpu.eax);
                if (!call(app, cpu, kRandom))
                    return;
                cpu.eax = (cpu.eax & 1) + 3;
                put(app, line, cpu.eax);
                cpu.eax = side();
                cpu.edx = 0;
                put(app, b - 0x28, cpu.eax);
                cpu.eax = line;
                put(app, b - 0x24, cpu.edx);
                if (!call(app, cpu, kQueue))
                    return;
                cpu.eax = own();
                cpu.ebx = at(app, cpu.eax * 4 + 0x5710d0);
                cpu.edx = at(app, 0x7d3684) - cpu.ebx;
                put(app, 0x552904, cpu.edx);
                put(app, cpu.eax * 4 + 0x5710f0, cpu.edx);
                done = true;
            }
        }
        if (!done)
        {
            cpu.eax = own();
            cpu.edx = byte(app, cpu.eax + 0x5710c8);
            cpu.edi = at(app, cpu.ecx + 0x204);
            if (cpu.edx != cpu.edi && i32(cpu.edi) > 1)
            {
                cpu.edx = cpu.eax * 4;
                cpu.eax = at(app, 0x7d3684);
                cpu.ebx = at(app, cpu.edx + 0x5710d0);
                cpu.edi = at(app, cpu.edx + 0x5710f0);
                cpu.eax -= cpu.ebx;
                if (i32(cpu.eax) < i32(cpu.edi))
                {
                    // Faster than the last lap.
                    cpu.edx = 0x40;
                    cpu.eax = at(app, kVoice);
                    cpu.ebx = at(app, 0x6fd3b0);
                    put(app, b - 0x2c, cpu.eax);
                    cpu.eax = 0x7f;
                    put(app, b - 0x34, cpu.edx);
                    put(app, b - 0x38, cpu.eax);
                    if (cpu.ebx == 1)
                    {
                        cpu.eax = sidePan();
                        put(app, b - 0x30, cpu.eax);
                    }
                    else
                    {
                        cpu.edi = 0;
                        put(app, b - 0x30, cpu.edi);
                    }
                    cpu.ebx = 3;
                    cpu.edx = 0;
                    if (!call(app, cpu, kRandom))
                        return;
                    udiv(cpu, cpu.ebx);
                    cpu.eax = side();
                    put(app, b - 0x28, cpu.eax);
                    cpu.eax = 0;
                    put(app, b - 0x24, cpu.eax);
                    cpu.eax = line;
                    put(app, line, cpu.edx);
                    if (!call(app, cpu, kQueue))
                        return;
                    cpu.eax = own();
                    cpu.edx = cpu.eax * 4;
                    cpu.eax = at(app, 0x7d3684);
                    cpu.ebx = at(app, cpu.edx + 0x5710d0);
                    cpu.eax -= cpu.ebx;
                    put(app, cpu.edx + 0x5710f0, cpu.eax);
                }
            }
        }
        // The race over: the position.
        cpu.eax = byte(app, own() + 0x5710c8);
        cpu.edi = at(app, cpu.ecx + 0x204);
        if (cpu.eax != cpu.edi && cpu.edi == at(app, 0x6fd4b4)
            && !(at(app, 0x6fd50c) != 0 && s32(app, 0x6fd3b0) > 1)
            && !(at(app, 0x6fd520) == 0 && at(app, 0x6fd3b0) == 0))
        {
            cpu.ebx = 0x7f;
            cpu.eax = at(app, kVoice);
            cpu.edi = 0x40;
            put(app, b - 0x2c, cpu.eax);
            put(app, b - 0x38, cpu.ebx);
            cpu.eax = at(app, 0x6fd3b0);
            put(app, b - 0x34, cpu.edi);
            if (cpu.eax == 1)
            {
                cpu.eax = sidePan();
                put(app, b - 0x30, cpu.eax);
            }
            else
            {
                cpu.edx = 0;
                put(app, b - 0x30, cpu.edx);
            }
            cpu.edx = side();
            cpu.ebx = cpu.edx;
            cpu.eax = cpu.esi;
            cpu.ebx <<= 4;
            if (!call(app, cpu, 0x412be0))
                return;
            cpu.eax += cpu.ebx;
            put(app, b - 0x28, cpu.edx);
            put(app, line, cpu.eax);
            cpu.ebx = 0;
            cpu.eax = line;
            put(app, b - 0x24, cpu.ebx);
            if (!call(app, cpu, kQueue))
                return;
        }
    }
    if (at(app, 0x6fd3b8) != 3)
    {
        // The last lap, or the lap's number.
        cpu.eax = at(app, 0x6fd4b4) - 1;
        cpu.edx = at(app, cpu.ecx + 0x204);
        bool queued = false;
        if (cpu.eax == cpu.edx)
        {
            cpu.eax ^= cpu.edx;
            cpu.eax = byte(app, own() + 0x5710c8);
            if (cpu.eax != cpu.edx)
            {
                cpu.edi = 0x7f;
                cpu.eax = at(app, kVoice);
                cpu.edx = at(app, 0x6fd3b0);
                put(app, b - 0x2c, cpu.eax);
                cpu.eax = 0x40;
                put(app, b - 0x38, cpu.edi);
                put(app, b - 0x34, cpu.eax);
                if (cpu.edx == 1)
                {
                    cpu.eax = sidePan();
                    put(app, b - 0x30, cpu.eax);
                }
                else
                {
                    cpu.ebx = 0;
                    put(app, b - 0x30, cpu.ebx);
                }
                if (!call(app, cpu, kRandom))
                    return;
                cpu.eax = (cpu.eax & 1) + 5;
                put(app, line, cpu.eax);
                cpu.eax = side();
                cpu.edi = 0;
                put(app, b - 0x28, cpu.eax);
                cpu.eax = line;
                put(app, b - 0x24, cpu.edi);
                if (!call(app, cpu, kQueue))
                    return;
                queued = true;
            }
        }
        if (!queued)
        {
            cpu.eax = byte(app, own() + 0x5710c8);
            cpu.edx = at(app, cpu.ecx + 0x204);
            if (cpu.eax != cpu.edx && cpu.edx != 0 && i32(at(app, 0x6fd4b4) - 1) > i32(cpu.edx))
            {
                cpu.edx = 0x40;
                cpu.eax = at(app, kVoice);
                cpu.ebx = at(app, 0x6fd3b0);
                put(app, b - 0x2c, cpu.eax);
                cpu.eax = 0x7f;
                put(app, b - 0x34, cpu.edx);
                put(app, b - 0x38, cpu.eax);
                if (cpu.ebx == 1)
                {
                    cpu.eax = sidePan();
                    put(app, b - 0x30, cpu.eax);
                }
                else
                {
                    cpu.edi = 0;
                    put(app, b - 0x30, cpu.edi);
                }
                cpu.eax = at(app, cpu.ecx + 0x204) + 6;
                put(app, line, cpu.eax);
                cpu.eax = side();
                put(app, b - 0x28, cpu.eax);
                cpu.eax = 0;
                put(app, b - 0x24, cpu.eax);
                cpu.eax = line;
                if (!call(app, cpu, kQueue))
                    return;
            }
        }
    }
    // The lap kept.
    cpu.eax = own();
    cpu.edx = byte(app, cpu.eax + 0x5710c8);
    cpu.ebx = at(app, cpu.ecx + 0x204);
    if (cpu.edx != cpu.ebx)
    {
        if (reg8(cpu.edx) == 0)
        {
            cpu.edx = cpu.eax * 4;
            cpu.eax = at(app, 0x7d3684);
            cpu.edi = at(app, cpu.edx + 0x5710d0);
            cpu.eax -= cpu.edi;
            put(app, cpu.edx + 0x5710f0, cpu.eax);
        }
        cpu.eax = own();
        setByte0(cpu.edx, byte(app, cpu.ecx + 0x204));
        putByte(app, cpu.eax + 0x5710c8, reg8(cpu.edx));
        cpu.edx = at(app, cpu.ecx + 0x238);
        put(app, cpu.eax * 4 + 0x5710d0, cpu.edx);
        cpu.eax = at(app, cpu.ecx + 0x204);
        put(app, 0x552860, cpu.eax);
        put(app, 0x55285c, cpu.eax);
    }
    cpu.eax = side();
    if (!call(app, cpu, 0x4c86d0))
        return;
    // The music: player one's (in the split screen, the one ahead's).
    bool ahead = false;
    if (at(app, 0x6fd3b0) == 1)
    {
        cpu.eax = at(app, 0x5efac8);
        cpu.edx = at(app, 0x5efacc);
        cpu.eax = at(app, cpu.eax + 0x2bc);
        ahead = i32(cpu.eax) >= s32(app, cpu.edx + 0x2bc);
    }
    setByte0(cpu.eax, ahead ? 1 : 0);
    if (at(app, 0x552910) == 0 || at(app, 0x6fbb54) != 0 || at(app, 0x6fbbf0) == 0 || byte(app, 0x552590) != 0
        || at(app, 0x552914) == 0)
        return leave(cpu, kept, pushed);
    if (at(app, 0x6fd3b0) == 1 && reg8(cpu.eax) != reg8(side()))
        return leave(cpu, kept, pushed);
    cpu.ebx = at(app, cpu.ecx + 0x628);
    if (cpu.ebx != 0 && s32(app, cpu.ebx + 0x2c) > 0)
        put(app, 0x55284c, 1);
    else
    {
        cpu.edx = 0;
        put(app, 0x55284c, cpu.edx);
    }
    // The intensity: by the laps left and the race's laps.
    cpu.ebx = at(app, 0x552860);
    cpu.eax = at(app, cpu.ecx + 0x204);
    cpu.edx = i32(cpu.eax) > i32(cpu.ebx) ? cpu.eax : cpu.ebx;
    cpu.ebx = at(app, 0x6fd4b4) - 1;
    cpu.eax = cpu.edx;
    const reg32 laps = at(app, 0x6fd4b4);
    if (cpu.edx == cpu.ebx || (i32(cpu.edx) > 5 && laps == 8))
        setByte0(cpu.edx, 0x64);
    else if (cpu.eax == 0 && laps != 2)
        setByte0(cpu.edx, 0);
    else if (cpu.eax == 1 && laps == 8)
        setByte0(cpu.edx, 0);
    else
        setByte0(cpu.edx, 0x32);
    cpu.ebx = at(app, 0x6fd520);
    if (cpu.ebx != 0)
    {
        if (cpu.ebx == 1)
        {
            cpu.ebx = cpu.eax * 4;
            if (cpu.eax <= 7)
            {
                reg8 level;
                if (cpu.esi == 1)
                {
                    switch (cpu.eax)
                    {
                    case 0: level = laps == 2 ? 0x32 : 0; break;
                    case 1: level = laps == 2 ? 0x64 : 0x32; break;
                    case 2:
                    case 3: level = laps == 4 ? 0x64 : 0x32; break;
                    default: level = 0x64; break;
                    }
                }
                else
                {
                    switch (cpu.eax)
                    {
                    case 0: level = 0; break;
                    case 1: level = laps == 2 ? 0x32 : 0; break;
                    case 2: level = laps == 4 ? 0x32 : 0; break;
                    case 3: level = laps == 4 ? 0x64 : 0; break;
                    case 7: level = 0x64; break;
                    default: level = 0x32; break;
                    }
                }
                setByte0(cpu.edx, level);
            }
        }
        else if (i32(cpu.esi) < 2 && reg8(cpu.edx) != 0x64)
        {
            const reg8 v = reg8(cpu.edx) + 0x64;
            setByte0(cpu.edx, v > 0x64 ? 0x64 : v);
        }
        else if (i32(cpu.esi) < 4 && i32(cpu.esi) >= 2)
        {
            const reg8 v = reg8(cpu.edx) + 0x32;
            setByte0(cpu.edx, v > 0x64 ? 0x64 : v);
        }
    }
    // Calm when the car is slow.
    fpu.push(f32(cpu.ecx + 0x4f4));
    if (!call(app, cpu, kChop))
        return;
    put(app, b - 0xc, reg32(fpu.toInteger<i32>(fpu.st(0))));
    fpu.pop();
    cpu.eax = at(app, b - 0xc);
    if (i32(cpu.eax) <= 0)
        cpu.eax = 0u - cpu.eax;
    cpu.eax += cpu.eax;
    if (i32(cpu.eax) < 0x32)
        setByte0(cpu.edx, 0);
    if (reg8(cpu.edx) != byte(app, 0x552850) && at(app, 0x552838) == 0xffffffff)
    {
        cpu.eax = reg8(cpu.edx);
        if (!call(app, cpu, 0x4e705c))
            return;
        putByte(app, 0x552850, reg8(cpu.edx));
    }
    // The long wait (0x8a0 over 600): the music's event resumed once.
    cpu.esi = at(app, cpu.ecx + 0x8a0);
    if (!call(app, cpu, kTrace, {0x64, 2, 0x5369d8, cpu.esi}))
        return;
    cpu.edi = at(app, cpu.ecx + 0x8a0);
    if (i32(cpu.edi) > 0x258 && byte(app, 0x552d7c) == 0)
    {
        setByte1(cpu.ebx, 1);
        cpu.eax = 0;
        putByte(app, 0x552d7c, 1);
        if (!call(app, cpu, 0x4e7208))
            return;
        if (at(app, 0x552838) != 0xffffffff)
        {
            cpu.eax = 1;
            cpu.edx = 0;
        }
        else
        {
            cpu.eax = 0;
            cpu.edx = 0;
            setByte0(cpu.eax, byte(app, 0x552834));
        }
        if (!call(app, cpu, 0x4e70fc))
            return;
    }
    else if (at(app, cpu.ecx + 0x8a0) == 0 && byte(app, 0x552d7c) != 0)
    {
        setByte1(cpu.eax, 0);
        putByte(app, 0x552d7c, 0);
    }
    // The section's event.
    cpu.eax = cpu.ecx;
    if (!call(app, cpu, 0x4211c0))
        return;
    setByte0(cpu.edx, reg8(cpu.eax));
    setByte1(cpu.edx, byte(app, 0x552834));
    const reg8 event = reg8(cpu.eax), was = reg8(cpu.edx >> 8);
    if (event == was)
        return leave(cpu, kept, pushed);
    if (s32(app, 0x7d36b0) > 0x258)
    {
        bool lap = false;
        if (at(app, cpu.ecx + 0x998) == 0)
        {
            cpu.ebx = 0;
            cpu.edi = at(app, 0x571238);
            setByte0(cpu.ebx, was);
            if (cpu.ebx == cpu.edi)
            {
                cpu.ebx = at(app, 0x571240);
                cpu.eax &= 0xff;
                lap = cpu.eax == cpu.ebx;
            }
        }
        if (!lap && at(app, cpu.ecx + 0x998) != 0)
        {
            cpu.eax = 0;
            cpu.edi = at(app, 0x571240);
            setByte0(cpu.eax, byte(app, 0x552834));
            if (cpu.eax == cpu.edi)
            {
                cpu.eax ^= cpu.edi;
                cpu.ebx = at(app, 0x571238);
                setByte0(cpu.eax, event);
                lap = cpu.eax == cpu.ebx;
            }
        }
        if (lap)
        {
            // Over the line: a lap on (or back, going backwards).
            cpu.eax = at(app, cpu.ecx + 0x998) != 0 ? 0xffffffff : 1;
            cpu.edi = at(app, 0x55285c) + cpu.eax;
            cpu.eax = at(app, cpu.ecx + 0x998);
            put(app, 0x55285c, cpu.edi);
            if (cpu.eax == 0)
                put(app, 0x552860, cpu.edi);
            if (s32(app, 0x552860) < 0)
            {
                cpu.esi = 0;
                put(app, 0x552860, cpu.esi);
            }
            cpu.edi = at(app, 0x6fd4b4);
            if (cpu.edi == at(app, 0x552860))
            {
                cpu.eax = cpu.edi - 1;
                put(app, 0x552860, cpu.eax);
            }
            cpu.eax = at(app, 0x55285c);
            cpu.ebx = at(app, 0x552860);
            cpu.esi = at(app, cpu.ecx + 0x204);
            if (!call(app, cpu, kTrace, {0x64, 1, 0x5369e8, cpu.esi, cpu.ebx, cpu.eax}))
                return;
        }
    }
    cpu.edi = at(app, 0x552838);
    putByte(app, 0x552834, event);
    if (cpu.edi == 0xffffffff)
    {
        cpu.eax = event;
        cpu.edx = 0;
        if (!call(app, cpu, 0x4e70fc))
            return;
    }
    leave(cpu, kept, pushed);
}

}  // namespace snd
}  // namespace nfs3hp
