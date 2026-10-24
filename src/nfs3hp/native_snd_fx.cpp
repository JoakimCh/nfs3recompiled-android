#include "native_snd.h"

/* EA's SND effects (cmn\seffect.c, cmn\sfxlevel.c, win\sdfxinit.c, the
 * reverb's start) and the mixer's start (mix\smixer.c), native (native_snd.h
 * says how).  One effect bus: its type, its two parameters and its master
 * level at 0xa0a25c (0x10 a bus); a voice sends to it at its own level (+0x39)
 * scaled by the bus's.  The reverb: 4 delay lines in 0xa0d2b4.. of prime
 * lengths, their state at 0xa181b0..0xa18200, their gains at 0x56ae3c. */
namespace nfs3hp
{
namespace snd
{

namespace
{

constexpr reg32 kBus = 0xa0a25c;            // the bus: type, -, param1, param2; its level at +4 (0xa0a260)
constexpr reg32 kRateWord = 0x9ef614;
constexpr reg32 kSetFx = 0x9ef654;          // what eacsnd's start calls for the bus
constexpr reg32 kReverbProcess = 0x5230b8, kReverbSend = 0x5230dc, kReverbEnd = 0x523118;
constexpr reg32 kFxFunctions = 0x9f6a60;    // the mixer's reverb, its send, its end
constexpr reg32 kEnter = 0x500e20, kLeave = 0x500e7c;

}  // namespace

/* 0x523200 (stdcall 4): the smallest prime from rate eax times the float
 * [esp+4] (truncated) on: a delay line's length. */
void reverbLength(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 f = kept.frame(5, 8);
    cpu.esp = f;
    put(app, f + 4, cpu.eax);
    x86::FPU& fpu = cpu.fpu;
    fpu.push(x86::Float(i32(cpu.eax)));
    fpu.st(0) = fpu.mul(fpu.st(0), x86::Float(app->getMemory<float>(kept.esp + 4)));
    if (!call(app, cpu, kChop))
        return;
    i32 n = fpu.toInteger<i32>(fpu.st(0));
    fpu.pop();
    for (;;)
    {
        i32 d = 2;
        if (d <= n)
            while (n % d != 0 && d < n)
                ++d;
        if (d == n)
            break;
        ++n;
    }
    put(app, f, reg32(n));
    kept.ret(cpu, reg32(n), 4);
}

/* 0x52325c: the reverb started for rate eax: its delay lines cleared, each
 * of the 4 a prime length on from the last (the time 0.1 s, each next the
 * last's times [0x551b00]), its gain 1 less [0x56ae30 on].  0. */
void reverbInit(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 f = kept.frame(4, 0xc);
    cpu.esp = f;
    const reg32 rate = cpu.eax;
    put(app, f + 8, 0x3dcccccd);
    for (reg32 at_ = 4; at_ <= 0xaf00; at_ += 4)
        put(app, 0xa0d2b0 + at_, 0);
    x86::FPU& fpu = cpu.fpu;
    reg32 line = 0xa0d2b4;
    cpu.ecx = line;
    for (reg32 k = 4; k <= 0x10; k += 4)
    {
        put(app, 0xa181d0 + k, line);
        cpu.edx = k;
        cpu.eax = rate;
        if (!call(app, cpu, 0x523200, {at(app, f + 8)}))
            return;
        const reg32 length = cpu.eax;
        fpu.push(x86::Float(app->getMemory<float>(0x56ae2c + k)));
        fpu.push(x86::Float(1.0f));
        fpu.st(1) = fpu.sub(fpu.st(0), fpu.st(1));
        fpu.pop();
        app->getMemory<float>(0x56ae3c + k) = float(fpu.st(0));
        fpu.pop();
        fpu.push(x86::Float(app->getMemory<float>(f + 8)));
        fpu.push(fpu.st(0));
        fpu.st(0) = fpu.mul(fpu.st(0), x86::Float(app->getMemory<double>(0x551b00)));
        const reg32 start = at(app, 0xa181d0 + k);
        line += length * 4;
        const reg32 last = length * 4 - 4 + start;
        put(app, 0xa181b0 + k, start);
        put(app, 0xa181c0 + k, start);
        put(app, 0xa181f0 + k, last);
        put(app, 0xa0d2a0 + k, last);
        put(app, 0xa181e0 + k, 0);
        fpu.st(1) = fpu.st(0);
        fpu.pop();
        app->getMemory<float>(f + 8) = float(fpu.st(0));
        fpu.pop();
        cpu.ecx = line;
    }
    kept.ret(cpu, 0);
}

/* 0x502ff0 (iSNDwinsetfx): the bus's effect type eax made the mixer's: none
 * (0), or one of the reverbs (5..120) -- the reverb started at the mixer's
 * rate, its functions the mixer's.  An error for another. */
void iSNDwinsetfx(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 type = cpu.eax;
    cpu.esp = kept.frame(3);
    if (type == 0)
    {
        kept.ret(cpu, 0);
        return;
    }
    bool mapped = false;
    for (const reg32 t : {5u, 10u, 20u, 30u, 40u, 50u, 100u, 110u, 120u})
        mapped = mapped || type == t;
    if (!mapped)
    {
        cpu.esi = 0x54eb00;
        cpu.edi = 0x54eb10;
        cpu.ebp = 0x24;
        if (!fail(app, cpu, kept.frame(3), 0x54eb00, 0x54eb10, 0x24, {0x54eb20, type}))
            return;
        kept.ret(cpu, cpu.eax);
        return;
    }
    cpu.esp = kept.frame(6);
    if (!callWith(app, cpu, 0x52325c, half(app, kRateWord), kReverbProcess, kReverbEnd, kReverbSend))
        return;
    put(app, kFxFunctions, kReverbProcess);
    put(app, kFxFunctions + 4, kReverbSend);
    put(app, kFxFunctions + 8, kReverbEnd);
    kept.ret(cpu, cpu.eax);
}

/* 0x5030ac: bus effect type edx set where eacsnd's start finds it, and now
 * when the library runs.  0. */
void setBusFx(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    put(app, kSetFx, 0x502ff0);
    if (byte(app, kInited) != 0 && !callWith(app, cpu, 0x502ff0, kept.edx))
        return;
    const reg32 ebx = cpu.ebx, ecx = cpu.ecx, edx = cpu.edx;
    kept.ret(cpu, 0);
    cpu.ebx = ebx;
    cpu.ecx = ecx;
    cpu.edx = edx;
}

/* 0x5030c4: nothing to do for the bus's level.  0. */
void busLevelSet(App*, CPU& cpu)
{
    cpu.eax = 0;
    cpu.esp += 4;
}

/* 0x5030d0 (SNDfxlevel): sound eax's send to bus edx at level ebx (0..127):
 * the voice's, or each playing voice's of its group -- scaled by the bus's
 * level.  What setVoiceSend gave back; -10 before SNDinit, -8 for no sound. */
void SNDfxlevel(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 f = kept.frame(4, 8);
    cpu.esp = f;
    const reg32 handle = cpu.eax, bus = cpu.edx;
    cpu.ecx = cpu.ebx;
    cpu.edx = 0;
    auto ret = [&](reg32 eax) {
        const reg32 ebx = cpu.ebx, edx = cpu.edx;
        kept.ret(cpu, eax);
        cpu.ebx = ebx;
        cpu.edx = edx;
    };
    if (byte(app, kInited) == 0)
        return ret(0xfffffff6);
    if (i32(bus) >= 1 || i32(bus) < 0)
    {
        cpu.ebx = 0x54eb4c;
        cpu.edi = 0x54eb5c;
        cpu.eax = 0x3a;
        if (!fail(app, cpu, f, 0x54eb4c, 0x54eb5c, 0x3a, {0x54eb68, bus}))
            return;
    }
    if (i32(cpu.ecx) > 0x7f || i32(cpu.ecx) < 0)
    {
        cpu.ebx = 0x54eb4c;
        cpu.edi = 0x54eb5c;
        cpu.eax = 0x3d;
        if (!fail(app, cpu, f, 0x54eb4c, 0x54eb5c, 0x3d, {0x54eb90, cpu.ecx}))
            return;
    }
    if (!call(app, cpu, kEnter))
        return;
    reg32 index;
    if (!callWith(app, cpu, 0x4ffc9c, handle))
        return;
    index = cpu.eax;
    if (i32(index) < 0)
    {
        if (!call(app, cpu, kLeave))
            return;
        return ret(0xfffffff8);
    }
    const reg32 v = voice(index);
    const reg32 group = byte(app, v + 0x3b);
    put(app, f + 4, group);
    // The send: the voice's level there times the bus's, over 0x3f01.
    auto send = [&](reg32 i, reg32 w) {
        putByte(app, w + bus + 0x39, reg8(cpu.ecx));
        const i32 level = quotient(mul(mul(sbyte(app, w + bus + 0x38), i32(cpu.ecx)), s32(app, kBus + 4 + bus * 0x10)), 0x3f01);
        cpu.ebx = reg32(level);
        if (!callWith(app, cpu, 0x523310, i, bus))
            return false;
        cpu.edx = cpu.eax;
        return true;
    };
    if (group == 0)
    {
        cpu.esi = index;
        if (!send(index, v))
            return;
    }
    else
    {
        put(app, f, bus * 0x10);
        for (reg32 i = 0; i < 0x10; ++i)
        {
            const reg32 w = voice(i);
            cpu.ebx = group;
            if (byte(app, w + 0x3b) != group || byte(app, w + 0xc) != 1 || s32(app, w) < 0)
                continue;
            // The code keeps the send in ecx: the next voice's level is it.
            const i32 level = quotient(mul(mul(sbyte(app, w + bus + 0x38), i32(cpu.ecx)), s32(app, kBus + 4 + bus * 0x10)), 0x3f01);
            putByte(app, w + bus + 0x39, reg8(cpu.ecx));
            cpu.ecx = reg32(level);
            cpu.ebx = reg32(level);
            cpu.edi = i;
            cpu.esi = w;
            if (!callWith(app, cpu, 0x523310, i, bus))
                return;
            cpu.edx = cpu.eax;
        }
        cpu.edi = 0x10;
    }
    if (!call(app, cpu, kLeave))
        return;
    ret(cpu.edx);
}

/* 0x4e9c70 (SNDfxinitbus, stdcall 4): bus eax set to effect type ebx with
 * parameters ecx and [esp+4] (-1 for 127), its master level edx (0 for no
 * effect).  What SNDfxmasterlevel gave. */
void SNDfxinitbus(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(3);
    const reg32 bus = cpu.eax, type = cpu.ebx;
    reg32 level = cpu.edx;
    reg32 first = cpu.ecx, second = at(app, kept.esp + 4);
    cpu.ebx = first;
    cpu.ecx = second;
    if (i32(bus) < 0 || i32(bus) >= 1)
    {
        cpu.edx = 0x54b41c;
        cpu.eax = 0x54b42c;
        cpu.edx = 0x52;
        if (!fail(app, cpu, kept.frame(3), 0x54b41c, 0x54b42c, 0x52, {0x54b43c, bus}))
            return;
    }
    if (first == 0xffffffff)
        first = 0x7f;
    else if (i32(first) < 0 || i32(first) > 0x7f)
    {
        cpu.eax = 0x5a;
        cpu.edx = 0x54b42c;
        if (!fail(app, cpu, kept.frame(3), 0x54b41c, 0x54b42c, 0x5a, {0x54b468, first}))
            return;
    }
    cpu.ebx = first;
    if (second == 0xffffffff)
        second = 0x7f;
    else if (i32(second) < 0 || i32(second) > 0x7f)
    {
        cpu.eax = 0x54b42c;
        cpu.edx = 0x62;
        if (!fail(app, cpu, kept.frame(3), 0x54b41c, 0x54b42c, 0x62, {0x54b48c, second}))
            return;
    }
    cpu.ecx = second;
    const reg32 b = kBus + bus * 0x10;
    put(app, b, type);
    put(app, b + 8, first);
    put(app, b + 0xc, second);
    if (!callWith(app, cpu, 0x5030ac, bus, type))
        return;
    const reg32 result = cpu.eax;
    if (byte(app, kInited) == 0)
    {
        if (i32(result) < 0)
        {
            cpu.ecx = 0x54b41c;
            cpu.ebx = 0x54b42c;
            cpu.eax = 0x7b;
            if (!fail(app, cpu, kept.frame(3), 0x54b41c, 0x54b42c, 0x7b, {0x54b4f8}))
                return;
        }
    }
    else if (i32(result) < 0)
    {
        cpu.edx = 0x54b41c;
        cpu.ecx = 0x54b42c;
        cpu.ebx = 0x74;
        if (!fail(app, cpu, kept.frame(3), 0x54b41c, 0x54b42c, 0x74, {0x54b4b0}))
            return;
    }
    if (type == 0)
        level = 0;
    if (!callWith(app, cpu, 0x4e9dfc, bus, level))
        return;
    const reg32 ebx = cpu.ebx, ecx = cpu.ecx, edx = cpu.edx;
    kept.ret(cpu, cpu.eax, 4);
    cpu.ebx = ebx;
    cpu.ecx = ecx;
    cpu.edx = edx;
}

/* 0x4e9dfc (SNDfxmasterlevel): bus eax's master level to edx (0..127), each
 * voice's send set again with it.  0. */
void SNDfxmasterlevel(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(5);
    const reg32 bus = cpu.eax, level = cpu.edx;
    if (i32(bus) < 0 || i32(bus) >= 1)
    {
        cpu.ecx = 0x54b41c;
        cpu.ebx = 0x54b540;
        cpu.esi = 0xc2;
        if (!fail(app, cpu, kept.frame(5), 0x54b41c, 0x54b540, 0xc2, {0x54b554, bus}))
            return;
    }
    if (i32(level) < 0 || i32(level) > 0x7f)
    {
        cpu.ebp = 0x54b41c;
        cpu.eax = 0x54b540;
        cpu.ecx = 0xc8;
        if (!fail(app, cpu, kept.frame(5), 0x54b41c, 0x54b540, 0xc8, {0x54b57c, level}))
            return;
    }
    put(app, kBus + 4 + bus * 0x10, level);
    if (!callWith(app, cpu, 0x5030c4, bus))
        return;
    if (i32(cpu.eax) < 0)
    {
        const reg32 edx = cpu.edx;
        kept.ret(cpu, cpu.eax);
        cpu.edx = edx;
        return;
    }
    for (reg32 i = 0; i < 0x10; ++i)
    {
        cpu.ebx = reg32(sbyte(app, voice(i) + 0x39 + bus));
        cpu.ecx = i + 1;
        cpu.esi = bus + (i + 1) * 0x60;
        if (!callWith(app, cpu, 0x5030d0, at(app, voice(i)), bus))
            return;
    }
    const reg32 edx = cpu.edx;
    kept.ret(cpu, 0);
    cpu.edx = edx;
}

/* 0x500008 (iSNDmixreinit): the mixer's output function and its frame's
 * bytes for format eax (8, 2, 4, 1).  0; an error for another. */
void iSNDmixreinit(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 format = cpu.eax & 0xff;
    cpu.esp = kept.frame(3);
    reg32 output, bytes;
    if (format & 8)
        output = 0x9f6b18, bytes = 0x400;
    else if (format & 2)
        output = 0x9f6b10, bytes = 0x200;
    else if (format & 4)
        output = 0x9f6b14, bytes = 0x200;
    else if (format & 1)
        output = 0x9f6b0c, bytes = 0x100;
    else
    {
        if (!fail(app, cpu, kept.frame(3), 0x54e184, 0x54e194, 0xbc, {0x54e1a4}))
            return;
        kept.ret(cpu, 0);
        return;
    }
    put(app, 0x9f6b20, at(app, output));
    putHalf(app, 0x9f6a58, reg16(bytes));
    kept.ret(cpu, 0);
}

/* 0x4ffd84: the mixer's functions, by whether the CPU has MMX
 * ([0x5643b4]): its volume functions, resamplers, outputs, clear, emms. */
void mixFunctions(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 mmx = at(app, 0x5643b4);
    putByte(app, 0x9f6a5b, reg8(mmx));
    struct Set { reg32 at, value; };
    if (mmx != 0)
    {
        static const Set sets[] = {
            {0x9f6adc, 0x51f580}, {0x9f6ae0, 0x51f680}, {0x9f6ae4, 0x51f750}, {0x9f6ae8, 0x51f850},
            {0x9f6afc, 0x51fc38}, {0x9f6b00, 0x52002c}, {0x9f6b04, 0x5203a0}, {0x9f6aec, 0x51fc38},
            {0x9f6af0, 0x52002c}, {0x9f6af4, 0x5203a0}, {0x9f6b08, 0x5207e4}, {0x9f6af8, 0x5207e4},
            {0x9f6b0c, 0x520830}, {0x9f6b10, 0x520870}, {0x9f6b18, 0x520920}, {0x9f6a5c, 0x5209a0},
            {0x9f6b24, 0x520a00}, {0x9f6b14, 0x520a10}};
        for (const Set& s : sets)
            put(app, s.at, s.value);
        putByte(app, 0x9f6a5a, 0);
        kept.ret(cpu, 0x520920);
        return;
    }
    static const Set sets[] = {
        {0x9f6adc, 0x520a40}, {0x9f6ae0, 0x520e00}, {0x9f6ae4, 0x520a40}, {0x9f6ae8, 0x520e00},
        {0x9f6aec, 0x5211c0}, {0x9f6af0, 0x521310}, {0x9f6af4, 0x5211c0}, {0x9f6af8, 0x521310},
        {0x9f6b00, 0x521800}, {0x9f6b08, 0x521800}, {0x9f6b10, 0x521840}, {0x9f6b24, 0x4ffd80},
        {0x9f6afc, 0x521bc4}, {0x9f6b04, 0x521bc4}, {0x9f6b0c, 0x521c10}, {0x9f6b14, 0x500910},
        {0x9f6a5c, 0x521c90}, {0x9f6b18, 0x521d00}};
    for (const Set& s : sets)
        put(app, s.at, s.value);
    putByte(app, 0x9f6a5a, 1);
    kept.ret(cpu, 0x520110);
}

/* 0x4fff18 (iSNDmixinit): the mixer started for mode eax, ended channels
 * told through edx: its tables, its 3 buffers 8-aligned, its functions, its
 * output; its channels free, its buffer cleared, the effect's start.  0. */
void iSNDmixinit(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 mode = cpu.eax, ended = cpu.edx;
    cpu.esp = kept.frame(4);
    cpu.ecx = mode;
    cpu.ebx = ended;
    for (const reg32 table : {0x521d80u, 0x521e60u, 0x521fc0u, 0x5220a0u})
        if (!call(app, cpu, table))
            return;
    put(app, 0x9fbca8, 0x9f6b28);
    put(app, 0x9fbcac, 0x9f7330);
    put(app, 0x9fbcb0, 0x9fb498);
    for (const reg32 buffer : {0x9fbca8u, 0x9fbcacu, 0x9fbcb0u})
        while (s32(app, buffer) % 8 != 0)
            put(app, buffer, at(app, buffer) + 1);
    cpu.esi = 8;
    cpu.edi = 0x9fb498;
    cpu.eax = at(app, 0x9fbcb0);
    cpu.edx = reg32(s32(app, 0x9fbcb0) % 8);
    if (!call(app, cpu, 0x4ffd84))
        return;
    // ebx and ecx as the tables' calls left them (the code set them before).
    put(app, kChannelEnded, cpu.ebx);
    if (!callWith(app, cpu, 0x500008, cpu.ecx))
        return;
    cpu.esi = kept.esi;
    cpu.edi = kept.edi;
    cpu.esp = kept.frame(2);
    for (reg32 i = 1; i <= 0x10; ++i)
        putByte(app, 0x9faed0 + i * kChannelSize, 0);
    cpu.eax = 0x10 * kChannelSize;
    cpu.edx &= 0xffffff00;
    cpu.ecx = at(app, 0x9fbca8);
    if (!call(app, cpu, at(app, 0x9f6a5c), {cpu.ecx, 0x200}))
        return;
    cpu.ebx = at(app, kFxFunctions);
    if (cpu.ebx != 0 && !call(app, cpu, cpu.ebx))
        return;
    const reg32 edx = cpu.edx;
    kept.ret(cpu, 0);
    cpu.edx = edx;
}

}  // namespace snd
}  // namespace nfs3hp
