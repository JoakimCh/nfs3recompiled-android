#include "native_snd.h"

/* The race's knocks and scrapes, native (native_snd.h says how): what a car
 * hit sounds like -- by what it hit and how hard, now and then at random, not
 * the same twice running where the game says so -- and how loud and high it
 * plays, near or far.
 *
 * The game's state: 0x552d80 the last crash effect picked, 0x571244 each
 * slot's last pitch (a byte). */
namespace nfs3hp
{
namespace snd
{

namespace
{

constexpr reg32 kLastCrash = 0x552d80, kSlotPitches = 0x571244, kSlots = 0x570de8;
constexpr reg32 kRandom = 0x4e0d88;

/* edx * 127 / 0xa0000 -- a force as a level -- at most 127: the code's
 * shl, sub, cdq and idiv, the divisor left in `by`. */
void forceLevel(CPU& cpu, reg32& by)
{
    cpu.eax = (cpu.edx << 7) - cpu.edx;
    cpu.edx = cpu.eax;
    by = 0xa0000;
    idiv(cpu, by);
    if (i32(cpu.eax) > 0x7f)
        cpu.eax = 0x7f;
}

}  // namespace

/* 0x414940: slot eax's pitch for effect edx at force ebx: the force's level
 * for the engines' slots (8, 9); else that level kept as the slot's, or the
 * one it has when the slot plays that effect already. */
void crashPitch(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.ebp = cpu.esp = kept.frame(2);
    cpu.ecx = cpu.eax;
    cpu.eax = cpu.ebx;
    if (cpu.ecx == 8 || cpu.ecx == 9)
    {
        cpu.edx = cpu.eax;
        forceLevel(cpu, cpu.ebx);
        return leave(cpu, kept, kEcx);
    }
    if (cpu.edx == at(app, cpu.ecx * 8 + kSlots + 4))
    {
        cpu.eax = byte(app, cpu.ecx + kSlotPitches);
        return leave(cpu, kept, kEcx);
    }
    cpu.edx = cpu.eax;
    forceLevel(cpu, cpu.ebx);
    putByte(app, cpu.ecx + kSlotPitches, reg8(cpu.eax));
    leave(cpu, kept, kEcx);
}

/* 0x4149e0: the crash effect for a hit of kind edx on material ebx at force
 * eax (0..127): 2 for none (kept as the last otherwise). */
void crashEffect(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.ebp = cpu.esp = kept.frame(2);
    cpu.ecx = cpu.eax;
    cpu.eax = 0x1d;
    auto finish = [&](reg32 effect) {
        cpu.eax = effect;
        if (cpu.eax != 2)
            put(app, kLastCrash, cpu.eax);
        leave(cpu, kept, kEcx);
    };
    // The random's low bit.
    auto randomBit = [&](bool& bit) {
        if (!call(app, cpu, kRandom))
            return false;
        bit = (cpu.eax & 1) != 0;
        return true;
    };
    const i32 force = i32(cpu.ecx);
    const reg32 kind = cpu.edx, material = cpu.ebx;
    bool bit;
    if (kind == 0xd)
    {
        cpu.eax = 2;
        return leave(cpu, kept, kEcx);
    }
    if (kind == 6 && material == 0x13)
        return finish(0x12);
    if (kind == 6 && material == 1)
        return finish(0x1f);
    if (kind == 5)
    {
        if (material == 0x10)
            return finish(0x1e);
        if (material == 0x11 || material == 0xa)
            return finish(0x1d);
        if (material == 8)
        {
            if (force > 0x6e)
                return finish(0x21);
            if (!randomBit(bit))
                return;
            return finish(bit ? 0x1e : 0x20);
        }
        if (material == 0x12)
        {
            if (!call(app, cpu, kRandom))
                return;
            static const reg32 picks[] = {0x23, 0x22, 0x20, 0x25};
            cpu.eax &= 3;
            return finish(picks[cpu.eax]);
        }
        if (material == 9)
        {
            if (!call(app, cpu, kRandom))
                return;
            return finish((cpu.eax & 1) + 0x18);
        }
        if (material == 0xb)
            return finish(0x63);
        if (material == 1 || material == 7)
        {
            reg32 effect = 0x1d;
            if (force > 0x50)
                effect = 0x21;
            else if (force > 0x16)
                effect = 0x22;
            else if (force > 0x10)
                effect = 0x20;
            cpu.eax = effect;
            cpu.edx = at(app, kLastCrash);
            // Not the same as the last, but for these.
            if (cpu.eax != cpu.edx || cpu.edx == 0x21)
                return finish(cpu.eax);
            if (cpu.edx < 0x20)
            {
                if (cpu.edx != 0x1d)
                    return finish(cpu.eax);
                if (!randomBit(bit))
                    return;
                return finish(bit ? 0x22 : 0x20);
            }
            if (cpu.edx == 0x20)
            {
                if (!randomBit(bit))
                    return;
                return finish(bit ? 0x1d : 0x22);
            }
            if (cpu.edx != 0x22)
                return finish(cpu.eax);
            if (!randomBit(bit))
                return;
            return finish(bit ? 0x1d : 0x20);
        }
    }
    reg32 effect = 0x1d;
    if (force > 0x5a)
        effect = 0x21;
    else if (force > 0x46)
        effect = 0x20;
    else if (force > 0x32)
        effect = 0x25;
    else if (force > 0x19)
        effect = 0x22;
    else
        effect = 0x1e;
    cpu.eax = effect;
    cpu.ecx = at(app, kLastCrash);
    if (cpu.eax != cpu.ecx || cpu.ecx == 0x21)
        return finish(cpu.eax);
    cpu.edx = cpu.ecx - 0x1e;
    switch (cpu.edx)
    {
    case 0:  // 0x1e
        return finish(0x22);
    case 2:  // 0x20
        if (!randomBit(bit))
            return;
        return finish(bit ? 0x25 : 0x22);
    case 4:  // 0x22
        if (!randomBit(bit))
            return;
        return finish(bit ? 0x1e : 0x25);
    case 7:  // 0x25
        if (!randomBit(bit))
            return;
        return finish(bit ? 0x1e : 0x22);
    default:
        return finish(cpu.eax);
    }
}

/* 0x414d70: the scrape effect for a hit of kind edx on material ebx. */
void scrapeEffect(App*, CPU& cpu)
{
    const reg32 kind = cpu.edx, material = cpu.ebx;
    reg32 effect = 0x2c;
    if (kind == 6 && material == 1)
        effect = 0x2a;
    if (kind == 6 && material == 2)
        effect = 0x2f;
    if (kind == 6 && material == 3)
        effect = 0x2d;
    if (kind == 6 && material == 4)
        effect = 0x2e;
    if (kind == 6 && material == 0xe)
        effect = 0x2b;
    if (kind == 6 && material == 0xf)
        effect = 0x2c;
    if (kind == 5 && (material == 1 || material == 7 || material == 0xe))
        effect = 0x28;
    if (kind == 6 && material == 7)
        effect = 0x29;
    if (kind == 5 && material == 0xf)
        effect = 0x2c;
    cpu.eax = effect;
    cpu.esp += 4;
}

/* 0x416d90 (stdcall 8): a car's knock in slot eax (below 0: a crash) of kind
 * edx on material ebx at force ecx, [esp+4] its distance, [esp+8] its pan:
 * the crash's effect picked and played in slot 0x1f (a big one's echo, 0x23,
 * with it); else the scrape played in the slot, as loud and high as the
 * force says -- or the slot stopped, no force. */
void carKnock(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const unsigned pushed = kEsi | kEdi;
    cpu.ebp = kept.frame(3);
    cpu.esp = cpu.ebp - 8;
    cpu.esi = cpu.eax;
    cpu.edi = cpu.edx;
    put(app, cpu.ebp - 4, cpu.ecx);
    cpu.eax = at(app, cpu.ebp + 0x10);
    const reg32 pan = at(app, cpu.ebp + 0x14);
    if (at(app, 0x55290c) == 0)
        return leave(cpu, kept, pushed, 8);
    cpu.eax += cpu.eax;
    if (i32(cpu.eax) < 0x15f9)
    {
        cpu.edx = 0x15f9 - cpu.eax;
        cpu.eax = (cpu.edx << 7) - cpu.edx;
        cpu.edx = cpu.eax;
        cpu.ecx = 0x15f9;
        idiv(cpu, 0x15f9);
        cpu.ecx = cpu.eax;
    }
    else
        cpu.ecx = 0;
    if (i32(cpu.esi) < 0)
    {
        cpu.edx = at(app, cpu.ebp - 4);
        forceLevel(cpu, cpu.esi);
        cpu.edx = cpu.edi;
        cpu.esi = cpu.eax;
        if (!call(app, cpu, 0x4149e0))
            return;
        cpu.edx = cpu.eax;
        if (cpu.eax == 2)
        {
            cpu.eax = 0;
            if (!call(app, cpu, 0x423b00))
                return;
            if (cpu.eax != 1)
                return leave(cpu, kept, pushed, 8);
        }
        if (cpu.edx == 0x63)
        {
            cpu.ebx = pan;
            cpu.edx = 1;
            cpu.eax = at(app, 0x571148);
            if (!call(app, cpu, 0x4182b0, {0x40}))
                return;
            return leave(cpu, kept, pushed, 8);
        }
        if (cpu.edx == 0x1f)
        {
            cpu.edx = reg32(mul(i32(cpu.ecx), i32(cpu.esi)));
            cpu.ebx = 0x7f;
            cpu.eax = cpu.edx;
            idiv(cpu, 0x7f);
            cpu.esi = cpu.eax + cpu.eax;
            if (i32(cpu.esi) > i32(cpu.ebx))
                cpu.esi = cpu.ebx;
            cpu.ebx = pan;
            cpu.edx = 0x1f;
            cpu.eax = cpu.edx;
            cpu.ebx = 0x40;
            cpu.edi = pan;
            if (!call(app, cpu, 0x417080, {pan}))
                return;
            cpu.ebx = 0x40;
            cpu.edx = 0x23;
            cpu.eax = 0x1f;
            cpu.ecx = cpu.esi;
            if (!call(app, cpu, 0x417080, {cpu.edi}))
                return;
            return leave(cpu, kept, pushed, 8);
        }
        cpu.eax = pan;
        cpu.ebx = 0x40;
        cpu.eax = 0x1f;
        if (!call(app, cpu, 0x417080, {pan}))
            return;
        return leave(cpu, kept, pushed, 8);
    }
    if (i32(at(app, cpu.ebp - 4)) <= 0)
    {
        cpu.eax = cpu.esi;
        if (!call(app, cpu, 0x416f60))
            return;
        return leave(cpu, kept, pushed, 8);
    }
    cpu.edx = cpu.edi;
    cpu.eax = cpu.esi;
    if (!call(app, cpu, 0x414d70))
        return;
    cpu.ebx = at(app, cpu.ebp - 4);
    cpu.edi = cpu.eax;
    put(app, cpu.ebp - 8, cpu.eax);
    cpu.edx = cpu.eax;
    cpu.eax = cpu.esi;
    if (!call(app, cpu, 0x414940))
        return;
    cpu.ebx = cpu.eax;
    if (cpu.esi == 8 || cpu.esi == 9 || cpu.edi == 0x2f || cpu.edi == 0x2e)
    {
        cpu.edx = at(app, cpu.ebp - 4);
        forceLevel(cpu, cpu.edi);
        cpu.edx = reg32(mul(i32(cpu.ecx), i32(cpu.eax)));
        cpu.ecx = 0x7f;
        cpu.eax = cpu.edx;
        idiv(cpu, 0x7f);
        cpu.edi = at(app, cpu.ebp - 8);
        cpu.ecx = cpu.eax;
        if (cpu.edi == 0x2e)
        {
            cpu.ebx = cpu.eax;
            if (i32(cpu.eax) > 0x40)
                cpu.ebx = 0x40;
        }
    }
    if (at(app, cpu.ebp - 8) == 0x2c)
    {
        cpu.ebx -= 0x3c;
        if (i32(cpu.ebx) < 0)
            cpu.ebx = 0;
    }
    cpu.edx = pan;
    cpu.eax = cpu.esi;
    cpu.edx = at(app, cpu.ebp - 8);
    if (!call(app, cpu, 0x417080, {pan}))
        return;
    leave(cpu, kept, pushed, 8);
}

}  // namespace snd
}  // namespace nfs3hp
