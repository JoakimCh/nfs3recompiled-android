#include "native_snd.h"

/* The race's sound in space, native (native_snd.cpp says how): where a
 * sound's source is from the listener -- its distance (the code's cheap
 * one, the largest of three plus a quarter of the others) and its angle --
 * and how far the listener moved since the last frame.  The x87's
 * arithmetic as the game's code has it, rounded as its control word says
 * (x86::FPU's add, sub, mul and fistp).
 *
 * The game's state: 0x570a60 each listener's last place (3 floats, 12 bytes
 * apart), 0x570dc0 its move since, scaled; 0x6fd4c4 the mirror (the angle's
 * side turned). */
namespace nfs3hp
{
namespace snd
{

namespace
{

constexpr reg32 kDot = 0x4e01f0;  // the game's dot product of two vectors: st(0)

x86::Float f32(App* app, reg32 at) { return x86::Float(app->getMemory<float>(at)); }
x86::Float f64(App* app, reg32 at) { return x86::Float(app->getMemory<double>(at)); }

/* fmul qword [scale]; fistp: st(0) scaled to an integer, popped. */
reg32 scaledTop(App* app, CPU& cpu, reg32 scale)
{
    x86::FPU& fpu = cpu.fpu;
    fpu.st(0) = fpu.mul(fpu.st(0), f64(app, scale));
    const reg32 n = reg32(fpu.toInteger<i32>(fpu.st(0)));
    fpu.pop();
    return n;
}

/* (b[k] - a[k]) * scale, fistp'd. */
reg32 scaledDifference(App* app, CPU& cpu, reg32 b, reg32 a, reg32 scale)
{
    cpu.fpu.push(cpu.fpu.sub(f32(app, b), f32(app, a)));
    return scaledTop(app, cpu, scale);
}

/* sub_410d30's and sub_410dc0's end: the angle of the two projections esi
 * (turned in the mirror) and eax, a 16-bit turn. */
bool angleOf(App* app, CPU& cpu, reg32& across)
{
    if (at(app, 0x6fd4c4) != 0)
        across = 0u - across;
    cpu.edx = cpu.eax;
    cpu.eax = across;
    cpu.edx = reg32(i32(cpu.edx) >> 8);
    cpu.eax = reg32(i32(cpu.eax) >> 8);
    if (!call(app, cpu, 0x4e8f28))
        return false;
    cpu.eax = (cpu.eax << 6) & 0xffff;
    return true;
}

}  // namespace

/* 0x410c40: listener eax's move from its last place to the one at edx,
 * scaled (0x536910), kept at 0x570dc0; the place kept.  eax left * 3. */
void listenerMove(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    x86::FPU& fpu = cpu.fpu;
    cpu.ebp = cpu.esp = kept.frame(2);
    cpu.ecx = cpu.eax;
    cpu.eax = (cpu.eax << 2) - cpu.ecx;
    const reg32 last = cpu.eax * 4 + 0x570a60, place = cpu.edx;
    const x86::Float k = f32(app, 0x536910);
    const x86::Float dx = fpu.mul(fpu.sub(f32(app, place), f32(app, last)), k);
    const x86::Float dy = fpu.mul(fpu.sub(f32(app, place + 4), f32(app, last + 4)), k);
    const x86::Float dz = fpu.mul(k, fpu.sub(f32(app, place + 8), f32(app, last + 8)));
    cpu.ecx = at(app, place);
    put(app, last, cpu.ecx);
    cpu.ecx = at(app, place + 4);
    put(app, last + 4, cpu.ecx);
    app->getMemory<float>(0x570dc0) = float(dx);
    app->getMemory<float>(0x570dc4) = float(dy);
    app->getMemory<float>(0x570dc8) = float(dz);
    cpu.ecx = at(app, place + 8);
    put(app, last + 8, cpu.ecx);
    leave(cpu, kept, kEcx);
}

/* 0x410cb0: the distance from the place at eax to the one at edx: each
 * axis's difference scaled (0x536918) and the largest of them plus a
 * quarter of each other, as the code goes about it. */
void sourceDistance(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.ebp = cpu.esp = kept.frame(4);
    cpu.ecx = cpu.eax;
    const reg32 a = cpu.ecx, b = cpu.edx;
    cpu.eax = scaledDifference(app, cpu, b, a, 0x536918);
    cpu.ebx = cpu.eax;
    cpu.eax = scaledDifference(app, cpu, b + 4, a + 4, 0x536918);
    cpu.esi = cpu.eax;
    cpu.eax = scaledDifference(app, cpu, b + 8, a + 8, 0x536918);
    cpu.edx = cpu.eax;
    if (i32(cpu.ebx) <= 0)
        cpu.ebx = 0u - cpu.ebx;
    cpu.eax = i32(cpu.esi) > 0 ? cpu.esi : 0u - cpu.esi;
    if (i32(cpu.edx) <= 0)
        cpu.edx = 0u - cpu.edx;
    if (i32(cpu.ebx) > i32(cpu.edx))
        cpu.edx = reg32(i32(cpu.edx) >> 2);
    else
        cpu.ebx = reg32(i32(cpu.ebx) >> 2);
    cpu.edx += cpu.ebx;
    if (i32(cpu.eax) > i32(cpu.edx))
        cpu.edx = reg32(i32(cpu.edx) >> 2);
    else
        cpu.eax = reg32(i32(cpu.eax) >> 2);
    cpu.eax += cpu.edx;
    leave(cpu, kept, kEbx | kEcx | kEsi);
}

/* 0x410d30: the angle of the place at edx from listener eax (its place,
 * then its axes at +0xc and +0x24), a 16-bit turn. */
void sourceAngle(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    x86::FPU& fpu = cpu.fpu;
    cpu.ebp = kept.frame(4);
    cpu.esp = cpu.ebp - 0xc;
    cpu.ecx = cpu.eax;
    const reg32 v = cpu.ebp - 0xc, b = cpu.edx, a = cpu.eax;
    app->getMemory<float>(v) = float(fpu.sub(f32(app, b), f32(app, a)));
    app->getMemory<float>(v + 4) = float(fpu.sub(f32(app, b + 4), f32(app, a + 4)));
    const x86::Float z = fpu.sub(f32(app, b + 8), f32(app, a + 8));
    cpu.edx = a + 0xc;
    app->getMemory<float>(v + 8) = float(z);
    cpu.eax = v;
    if (!call(app, cpu, kDot))
        return;
    cpu.edx = cpu.ecx + 0x24;
    cpu.eax = scaledTop(app, cpu, 0x536920);
    cpu.ebx = cpu.eax;
    cpu.esi = cpu.eax;
    cpu.eax = v;
    if (!call(app, cpu, kDot))
        return;
    cpu.eax = scaledTop(app, cpu, 0x536920);
    if (!angleOf(app, cpu, cpu.esi))
        return;
    leave(cpu, kept, kEbx | kEcx | kEsi);
}

/* 0x410dc0: the angle of the car at edx (its place at +0x13c) from listener
 * eax (its axes at +0xc and +0x24), a 16-bit turn. */
void carAngle(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.ebp = cpu.esp = kept.frame(5);
    cpu.ebx = cpu.eax;
    cpu.eax += 0xc;
    cpu.ecx = cpu.edx + 0x13c;
    cpu.edx = cpu.eax;
    cpu.eax = cpu.ecx;
    if (!call(app, cpu, kDot))
        return;
    cpu.edx = cpu.ebx + 0x24;
    cpu.eax = scaledTop(app, cpu, 0x536928);
    cpu.esi = cpu.eax;
    cpu.edi = cpu.eax;
    cpu.eax = cpu.ecx;
    if (!call(app, cpu, kDot))
        return;
    cpu.eax = scaledTop(app, cpu, 0x536928);
    if (!angleOf(app, cpu, cpu.edi))
        return;
    leave(cpu, kept, kEbx | kEcx | kEsi | kEdi);
}

namespace
{

/* fild of three ints at `from`, each times the double at `scale`, fstp'd to
 * the floats at `to` -- the code's stack shuffle, its products as the x87
 * makes them. */
void scaleInts(App* app, CPU& cpu, reg32 to, reg32 from, reg32 scale)
{
    x86::FPU& fpu = cpu.fpu;
    const x86::Float c = f64(app, scale);
    for (reg32 k = 0; k < 12; k += 4)
        app->getMemory<float>(to + k) = float(fpu.mul(x86::Float(x86::sreg32(at(app, from + k))), c));
}

}  // namespace

/* 0x4124d0: how far the place at eax is ahead (16.16, of 0xdc0000) along
 * the track: its cell (0x4970c0's) by the cell's direction (edx), less the
 * listener's own (0x570dcc's direction), from the listener's place. */
void placeAhead(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    x86::FPU& fpu = cpu.fpu;
    cpu.ebp = kept.frame(3);
    cpu.esp = cpu.ebp - 0x28;
    cpu.ecx = cpu.eax;
    const reg32 cell = cpu.ebp - 0x1c, v = cpu.ebp - 0x10, d = cpu.ebp - 0x28;
    for (reg32 k = 0; k < 12; k += 4)
    {
        fpu.push(fpu.sub(f32(app, cpu.ecx + k), f32(app, 0x570a78 + k)));
        cpu.eax = reg32(i32(scaledTop(app, cpu, 0x536960)) >> 8);
        if (k == 0)
            cpu.ebx = at(app, 0x570dcc);
        put(app, cell + k, cpu.eax);
    }
    cpu.eax = cell;
    cpu.ecx = 0;
    if (!call(app, cpu, 0x4970c0))
        return;
    if (cpu.edx != 0)
    {
        scaleInts(app, cpu, v, cell, 0x536968);
        put(app, cpu.ebp - 4, at(app, cell + 8));
        put(app, d, at(app, cpu.edx));
        put(app, d + 4, at(app, cpu.edx + 4));
        cpu.eax = at(app, cpu.edx + 8);
        cpu.edx = d;
        put(app, d + 8, cpu.eax);
        cpu.eax = v;
        if (!call(app, cpu, kDot))
            return;
        cpu.eax = scaledTop(app, cpu, 0x536960);
        cpu.ecx = cpu.eax;
    }
    if (cpu.ebx != 0)
    {
        scaleInts(app, cpu, v, cell, 0x536968);
        put(app, cpu.ebp - 4, at(app, cell + 8));
        cpu.eax = at(app, cell + 8);
        cpu.edx = cpu.ebx;
        cpu.eax = v;
        if (!call(app, cpu, kDot))
            return;
        cpu.eax = scaledTop(app, cpu, 0x536960);
        cpu.ecx -= cpu.eax;
    }
    cpu.eax = 0xdc0000;
    cpu.ebx = cpu.ecx + 0xdc0000;
    fixedDivide(cpu, cpu.ebx);
    leave(cpu, kept, kEbx | kEcx);
}

/* 0x412620: the place at edx (ints) from the listener at eax (its place in
 * floats, its axes at +0xc and +0x24): its distance (the cheap one) in eax,
 * and across each axis over that (16.16, -1..1) at ebx and ebx + 4. */
void placeAcross(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    x86::FPU& fpu = cpu.fpu;
    cpu.ebp = kept.frame(4);
    cpu.esp = cpu.ebp - 0x1c;
    cpu.ecx = cpu.eax;
    cpu.esi = cpu.ebx;
    const reg32 place = cpu.edx, v = cpu.ebp - 0x1c;
    fpu.push(f32(app, cpu.ecx));
    cpu.eax = scaledTop(app, cpu, 0x536970);
    cpu.ebx = at(app, place) - cpu.eax;
    fpu.push(f32(app, cpu.ecx + 4));
    cpu.eax = scaledTop(app, cpu, 0x536970);
    cpu.edi = at(app, place + 4) - cpu.eax;
    put(app, cpu.ebp - 8, cpu.ebx);
    fpu.push(f32(app, cpu.ecx + 8));
    cpu.eax = scaledTop(app, cpu, 0x536970);
    cpu.ebx = at(app, place + 8) - cpu.eax;
    cpu.eax = at(app, cpu.ebp - 8);
    if (i32(cpu.eax) <= 0)
        cpu.eax = 0u - cpu.eax;
    put(app, cpu.ebp - 4, cpu.eax);
    cpu.eax = i32(cpu.edi) > 0 ? cpu.edi : 0u - cpu.edi;
    if (i32(cpu.ebx) <= 0)
        cpu.ebx = 0u - cpu.ebx;
    cpu.edi = at(app, cpu.ebp - 4);
    if (i32(cpu.ebx) < i32(cpu.edi))
        cpu.ebx = reg32(i32(cpu.ebx) >> 2);
    else
        cpu.edi = reg32(i32(cpu.edi) >> 2);
    cpu.ebx += cpu.edi;
    if (i32(cpu.eax) > i32(cpu.ebx))
        cpu.ebx = reg32(i32(cpu.ebx) >> 2);
    else
        cpu.eax = reg32(i32(cpu.eax) >> 2);
    cpu.ebx += cpu.eax;
    const x86::Float c = f64(app, 0x536978);
    for (reg32 k = 0; k < 12; k += 4)
    {
        const x86::Float scaledInt = fpu.mul(x86::Float(x86::sreg32(at(app, place + k))), c);
        app->getMemory<float>(v + k) = float(fpu.sub(scaledInt, f32(app, cpu.ecx + k)));
    }
    cpu.eax = v;
    cpu.edx = cpu.ecx + 0xc;
    if (!call(app, cpu, kDot))
        return;
    cpu.edx = cpu.ecx + 0x24;
    cpu.eax = scaledTop(app, cpu, 0x536970);
    put(app, cpu.ebp - 0x10, cpu.eax);
    cpu.eax = v;
    if (!call(app, cpu, kDot))
        return;
    cpu.edi = cpu.ebx;
    cpu.eax = scaledTop(app, cpu, 0x536970);
    put(app, cpu.ebp - 0xc, cpu.eax);
    auto clamped = [](reg32 r) -> reg32 {
        if (i32(r) > 0x10000)
            return 0x10000;
        if (i32(r) < i32(0xffff0000))
            return 0xffff0000;
        return r;
    };
    if (cpu.ebx == 0)
    {
        put(app, cpu.esi + 4, cpu.ebx);
        put(app, cpu.esi, cpu.ebx);
    }
    else
    {
        cpu.eax = at(app, cpu.ebp - 0x10);
        fixedDivide(cpu, cpu.ebx);
        put(app, cpu.esi, clamped(cpu.eax));
        cpu.eax = at(app, cpu.ebp - 0xc);
        cpu.ebx = cpu.edi;
        fixedDivide(cpu, cpu.ebx);
        put(app, cpu.esi + 4, clamped(cpu.eax));
    }
    cpu.eax = cpu.edi;
    leave(cpu, kept, kEcx | kEsi | kEdi);
}

}  // namespace snd
}  // namespace nfs3hp
