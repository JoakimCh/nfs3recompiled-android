#include "native_snd.h"

/* The race's sound set up and ended, native (native_snd.cpp says how): the
 * slots emptied, the engines started, the race's banks and its music's
 * state reset as a race starts; the master volume faded out over the game's
 * own delay loop as it ends, everything stopped and the menus' volumes back;
 * a cop car's sounds stopped as it leaves. */
namespace nfs3hp
{
namespace snd
{

/* 0x4121b0: cop car eax's sounds stopped (its slot 4 on too, unless edx),
 * its source reset for car edx. */
void copRemove(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.ebp = cpu.esp = kept.frame(3);
    cpu.ecx = cpu.eax;
    cpu.eax <<= 3;
    cpu.ebx = cpu.eax;
    cpu.eax = (cpu.eax << 3) - cpu.ebx;
    if (at(app, cpu.eax + 0x570b78) != 0)
    {
        if (cpu.edx == 0)
        {
            cpu.eax = cpu.ecx + 4;
            if (!call(app, cpu, 0x416f60))
                return;
        }
        cpu.eax = cpu.ecx;
        if (!call(app, cpu, 0x411ca0))
            return;
        cpu.eax = cpu.ecx + 0x16;
        if (!call(app, cpu, 0x416f60))
            return;
        cpu.eax = cpu.ecx + 0x1b;
        if (!call(app, cpu, 0x416f60))
            return;
        cpu.esi = at(app, 0x552608) - 1;
        put(app, 0x552608, cpu.esi);
        if (i32(cpu.esi) < 0)
        {
            cpu.eax = 0;
            put(app, 0x552608, cpu.eax);
        }
    }
    cpu.ecx <<= 3;
    cpu.eax = cpu.ecx;
    cpu.ecx = (cpu.ecx << 3) - cpu.eax;
    cpu.eax = cpu.ecx + 0x570b78;
    if (!call(app, cpu, 0x411620))
        return;
    leave(cpu, kept, kEcx | kEsi);
}

/* 0x4127b0: car eax's +0x624 compared with 0, the flags its caller tests --
 * which no caller does now: nothing. */
void carFlagTest(App*, CPU& cpu)
{
    cpu.esp += 4;
}

/* 0x4129a0: the race's 0x6fd2b4. */
void raceValue(App* app, CPU& cpu)
{
    cpu.eax = at(app, 0x6fd2b4);
    cpu.esp += 4;
}

/* 0x4129b0: nothing. */
void soundNothing(App*, CPU& cpu)
{
    cpu.esp += 4;
}

/* 0x414800: the slots 1..0x27 emptied. */
void slotsEmpty(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.ebp = cpu.esp = kept.frame(2);
    cpu.eax = 0;
    do
    {
        ++cpu.eax;
        cpu.edx = 0xffffffff;
        put(app, cpu.eax * 8 + 0x570de0, cpu.edx);
        put(app, cpu.eax * 8 + 0x570de4, cpu.edx);
    } while (i32(cpu.eax) < 0x27);
    leave(cpu, kept, kEdx);
}

/* 0x4136e0: the race's first bank (<audio dir> and 0x536a20's name) loaded
 * into slot 0. */
void raceBankLoad(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.ebp = kept.frame(6);
    cpu.esp = cpu.ebp - 0x64;
    const reg32 name = cpu.ebp - 0x64;
    cpu.ebx = 0x10;
    copyString(app, cpu, name, 0x7a2ab4);
    cpu.edx = 0;
    appendString(app, cpu, name, 0x536a20);
    cpu.edi = name;
    cpu.eax = name;
    if (!call(app, cpu, 0x410b50))
        return;
    leave(cpu, kept, kEbx | kEcx | kEdx | kEsi | kEdi);
}

/* 0x4129c0: the race's sound set up: the slots emptied, the engines started,
 * the cops' radio's banks picked (by the car, the second set for 0x6fd4c0),
 * the speech reset; for each of 8 cars (0x4a33d0 between) its sounds'
 * state cleared; the music's state, a random pick of 0x6fd4b4, the volumes
 * kept for the end, the master volume at 0x78. */
void raceSoundInit(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.ebp = cpu.esp = kept.frame(6);
    if (at(app, 0x55290c) != 0)
    {
        putByte(app, 0x552858, 4);
        if (!call(app, cpu, 0x414800) || !call(app, cpu, 0x414830))
            return;
        cpu.ecx = at(app, 0x6fd4ac);
        if (i32(cpu.ecx) < 0xa)
        {
            cpu.ebx = at(app, 0x6fd4c0);
            cpu.eax = cpu.ecx * 8;
            const reg32 set = cpu.ebx == 0 ? 0x552864 : 0x5528b4;
            cpu.edx = at(app, cpu.eax + set);
            cpu.eax = at(app, cpu.eax + set + 4);
            put(app, 0x571240, cpu.edx);
            put(app, 0x571238, cpu.eax);
        }
        else
        {
            cpu.esi = 0xffffffff;
            put(app, 0x571238, cpu.esi);
            put(app, 0x571240, cpu.esi);
        }
        cpu.eax = 0;
        put(app, 0x552860, cpu.eax);
        put(app, 0x55285c, cpu.eax);
    }
    if (!call(app, cpu, 0x4c8370))
        return;
    cpu.edx = 0;
    do
    {
        if (!call(app, cpu, 0x4a33d0))
            return;
        cpu.esi = 0x200;
        ++cpu.edx;
        setByte0(cpu.ebx, 0);
        cpu.ecx = 0;
        for (const reg32 table : {0x570f47u, 0x570ddfu, 0x570f3fu, 0x571097u, 0x57106fu, 0x5710c7u})
            putByte(app, cpu.edx + table, 0);
        put(app, cpu.edx * 4 + 0x5710ec, cpu.ecx);
        put(app, cpu.edx * 4 + 0x571074, cpu.ecx);
        put(app, cpu.edx * 4 + 0x5710cc, cpu.esi);
    } while (i32(cpu.edx) < 8);
    cpu.eax = 0;
    do
    {
        setByte0(cpu.edx, 0x40);
        ++cpu.eax;
        putByte(app, 0x57126b, 0x40);
    } while (i32(cpu.eax) < 0x27);
    setByte0(cpu.ecx, 4);
    setByte1(cpu.edx, 0);
    cpu.edi = 0xffffffff;
    putByte(app, 0x552930, 0);
    putByte(app, 0x552859, 0);
    putByte(app, 0x55285a, 0);
    if (!call(app, cpu, 0x4129a0))
        return;
    put(app, 0x552904, cpu.eax);
    putByte(app, 0x552834, reg8(cpu.ecx));
    put(app, 0x552838, cpu.edi);
    putByte(app, 0x552850, reg8(cpu.edx >> 8));
    cpu.eax = 0;
    cpu.edx = 0;
    put(app, 0x55283c, cpu.eax);
    put(app, 0x552840, cpu.eax);
    if (!call(app, cpu, 0x4e0d88))
        return;
    cpu.ecx = at(app, 0x6fd4b4);
    udiv(cpu, cpu.ecx);
    setByte0(cpu.eax, 1);
    putByte(app, 0x552908, 1);
    putByte(app, 0x552909, 1);
    cpu.eax = at(app, 0x6fbbf4);
    put(app, 0x552c34, cpu.edx);
    put(app, 0x552920, cpu.eax);
    cpu.eax = at(app, 0x6fbbf8);
    cpu.ecx = 0;
    put(app, 0x552924, cpu.eax);
    cpu.eax = 0x78;
    put(app, 0x552c38, cpu.ecx);
    if (!call(app, cpu, 0x4e73d0))
        return;
    leave(cpu, kept, kEbx | kEcx | kEdx | kEsi | kEdi);
}

/* 0x412b50: the race's sound ended: the master volume faded out a step at a
 * time over the game's own delay (0x2fffd turns of a loop a step, which the
 * code burns as it did), the sounds stopped, the banks removed and their
 * copies freed, the bus down, the music stopped, the master volume back,
 * the speech ended, the menus' volumes and music setting back. */
void raceSoundEnd(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.ebp = cpu.esp = kept.frame(2);
    cpu.edx = 0x7f;
    cpu.eax = 0;
    for (;;)
    {
        // The delay: the generated code's loop, a safepoint a turn.
        volatile reg32 turns = cpu.eax + 1;
        while (turns < 0x2fffd)
        {
            safepoint(app, cpu);
            turns = turns + 1;
        }
        cpu.eax = cpu.edx;
        if (!call(app, cpu, 0x4e73d0))
            return;
        --cpu.edx;
        if (i32(cpu.edx) < 0)
            break;
        cpu.eax = 0;
    }
    if (at(app, 0x55290c) != 0)
    {
        if (!call(app, cpu, 0x4e9010))
            return;
        cpu.eax = 0xffffffff;
        if (!call(app, cpu, 0x4e8c1c) || !call(app, cpu, 0x410ad0))
            return;
    }
    if (byte(app, 0x552930) != 0 && !call(app, cpu, 0x418790))
        return;
    if (!call(app, cpu, 0x4109d0))
        return;
    cpu.eax = 0x7f;
    if (!call(app, cpu, 0x4e73d0) || !call(app, cpu, 0x4c8440))
        return;
    put(app, 0x6fbbf4, at(app, 0x552920));
    put(app, 0x6fbbf8, at(app, 0x552924));
    cpu.eax = at(app, 0x552918);
    put(app, 0x552910, cpu.eax);
    leave(cpu, kept, kEdx);
}

}  // namespace snd
}  // namespace nfs3hp
