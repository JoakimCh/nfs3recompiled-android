#include "native_snd.h"

/* EA SND's mixer's own functions, native (native_snd.cpp says how): what the
 * MMX set's tables and set-ups hand a channel, and what the mixer's start and
 * the sample conversion call.  native_mixer.cpp mixes with most of them
 * itself; these are the entries the game's code and the natives still call
 * through the channels' pointers (iSNDmixstart: a channel's volume set-up and
 * its volume, its resampler's set-up and step), each instruction for
 * instruction. */
namespace nfs3hp
{
namespace snd
{

namespace
{

/* The volume as the MMX multiplies by it: the level in the top byte and,
 * as a word, the level times 256. */
reg32 level(reg32 v) { return (v << 24) | ((v << 8) & 0xffff); }

x86::Float fild(App* app, reg32 a) { return x86::Float(x86::sreg32(at(app, a))); }
x86::Float f64(App* app, reg32 a) { return x86::Float(app->getMemory<double>(a)); }
void fstp32(App* app, reg32 a, x86::Float v) { app->getMemory<float>(a) = float(v); }

}  // namespace

/* 0x51f580 (cdecl: state, the add's slot, the volume's slot): a mono
 * source's add and volume, MMX's own pair. */
void volumeMonoPair(App* app, CPU& cpu)
{
    const reg32 state = at(app, cpu.esp + 4), add = at(app, cpu.esp + 8), volume = at(app, cpu.esp + 0xc);
    put(app, state + 0x10, add);
    put(app, add, 0x51f5dd);
    put(app, state + 0x14, volume);
    put(app, volume, 0x51f5a4);
    cpu.esp += 4;
}

/* 0x51f5a4 and 0x51f774 (volumeMonoLevelsMmx; cdecl: state, left, right): a mono source's volume,
 * left twice, then right twice. */
void volumeMonoLevels(App* app, CPU& cpu)
{
    const reg32 state = at(app, cpu.esp + 4), left = at(app, cpu.esp + 8), right = at(app, cpu.esp + 0xc);
    put(app, state, level(left));
    put(app, state + 4, level(left));
    put(app, state + 8, level(right));
    put(app, state + 0xc, level(right));
    cpu.esp += 4;
}

void volumeMonoLevelsMmx(App* app, CPU& cpu) { volumeMonoLevels(app, cpu); }

/* 0x51f680 (cdecl: state, the add's slot, the volume's slot): a stereo
 * source's. */
void volumeStereoPair(App* app, CPU& cpu)
{
    const reg32 state = at(app, cpu.esp + 4), add = at(app, cpu.esp + 8), volume = at(app, cpu.esp + 0xc);
    put(app, state + 8, add);
    put(app, add, 0x51f6c7);
    put(app, state + 0xc, volume);
    put(app, volume, 0x51f6a4);
    cpu.esp += 4;
}

/* 0x51f6a4 and 0x51f874 (volumeStereoLevelsMmx; cdecl: state, left, right): a stereo source's
 * volume, right's level over left's word, twice. */
void volumeStereoLevels(App* app, CPU& cpu)
{
    const reg32 state = at(app, cpu.esp + 4), left = at(app, cpu.esp + 8), right = at(app, cpu.esp + 0xc);
    const reg32 v = (right << 24) | ((left << 8) & 0xffff);
    put(app, state, v);
    put(app, state + 4, v);
    cpu.esp += 4;
}

void volumeStereoLevelsMmx(App* app, CPU& cpu) { volumeStereoLevels(app, cpu); }

/* 0x51f520: a pan's two sides from angle eax (64ths of 0x4eac60's steps):
 * 0x4eac60's sine and cosine of eax >> 6, each moved by the rest (eax & 63)
 * towards the other -- [edx] and [ebx]. */
void panSides(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 f = kept.frame(3, 8);
    cpu.esp = f;
    const reg32 first = cpu.edx, second = cpu.ebx;
    cpu.ecx = cpu.eax & 0x3f;
    cpu.eax = reg32(i32(cpu.eax) >> 6);
    cpu.ebx = f + 4;
    cpu.edx = f;
    if (!call(app, cpu, 0x4eac60))
        return;
    const reg32 step = reg32(mul(i32(cpu.ecx), 0x6487e) >> 9);
    reg32 ecx = reg32(mul(s32(app, f + 4) >> 2, i32(step)) >> 0x15);
    put(app, first, at(app, f) + ecx);
    const reg32 edx = reg32(s32(app, f) >> 2);
    ecx = reg32(mul(i32(step), i32(edx)) >> 0x15);
    cpu.eax = at(app, f + 4) - ecx;
    put(app, second, cpu.eax);
    cpu.edx = edx;
    cpu.ecx = kept.ecx;
    cpu.esi = kept.esi;
    cpu.edi = kept.edi;
    cpu.esp = kept.esp + 4;
}

/* 0x4ffce0 (eacsnd's buffer position): a voice's place for DirectSound 3D at
 * ebx -- angle eax, elevation edx (64ths of 0x400ths of the circle) -- as
 * three floats: x, y and z from 0x4eac60's elevation and 0x51f520's pan. */
void bufferPosition(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 f = kept.frame(2, 0x18);
    cpu.esp = f;
    const reg32 angle = cpu.eax, to = cpu.ebx;
    cpu.ecx = to;
    cpu.eax = 0x400 - reg32(i32(cpu.edx & 0xffff) >> 6);
    cpu.ebx = f + 8;
    cpu.edx = f + 0xc;
    if (!call(app, cpu, 0x4eac60))
        return;
    cpu.ebx = f;
    cpu.edx = f + 4;
    cpu.eax = angle;
    if (!call(app, cpu, 0x51f520))
        return;
    auto& fpu = cpu.fpu;
    put(app, f + 0x14, at(app, f + 8));
    put(app, f + 0x10, at(app, f + 4));
    const x86::Float c1 = f64(app, 0x54e174);
    fstp32(app, to, fpu.mul(fpu.mul(fild(app, f + 0x14), fild(app, f + 0x10)), c1));
    put(app, f + 0x10, at(app, f + 0xc));
    fstp32(app, to + 4, fpu.mul(fild(app, f + 0x10), f64(app, 0x54e17c)));
    put(app, f + 0x10, at(app, f + 8));
    put(app, f + 0x14, at(app, f));
    fstp32(app, to + 8, fpu.mul(c1, fpu.mul(fild(app, f + 0x10), fild(app, f + 0x14))));
    cpu.eax = at(app, f);
    cpu.ecx = kept.ecx;
    cpu.esi = kept.esi;
    cpu.esp = kept.esp + 4;
}

/* 0x51fc38 (cdecl: state, the step setter's slot, the frames needed's, the
 * resampler's): an 8-bit mono source's resampler, its step setter given.
 * 0; edx the resampler's slot. */
void resample8MonoSetup(App* app, CPU& cpu)
{
    const reg32 s = at(app, cpu.esp + 4);
    put(app, s, 0);
    put(app, s + 4, 0);
    putByte(app, s + 0xe, 0);
    putByte(app, s + 0xd, 0);
    putByte(app, s + 0xf, 0);
    putByte(app, s + 0x10, 1);
    put(app, s + 0x14, at(app, cpu.esp + 8));
    put(app, s + 0x18, at(app, cpu.esp + 0xc));
    cpu.edx = at(app, cpu.esp + 0x10);
    put(app, s + 0x1c, cpu.edx);
    put(app, at(app, s + 0x14), 0x51fb94);
    cpu.eax = 0;
    cpu.esp += 4;
}

/* 0x51fb94 (cdecl: state, step): an 8-bit mono resampler's step set, and
 * by it its frames needed's and its resampler: up, the same, or down.  A
 * step across 1.0 (or from one) starts it afresh.  0; ecx the state, edx the
 * frames needed's slot. */
void resample8MonoStep(App* app, CPU& cpu)
{
    const reg32 s = at(app, cpu.esp + 4), step = at(app, cpu.esp + 8);
    const reg32 old = at(app, s + 8);
    if ((old >= 0x10000 || step >= 0x10000) && step != old && !(old > 0x10000 && step > 0x10000))
    {
        putByte(app, s + 0xe, 0);
        putByte(app, s + 0xf, 0);
        putByte(app, s + 0x10, 0);
        put(app, s + 4, 0);
        put(app, s, 0);
    }
    put(app, s + 8, step);
    reg32 needed = 0x51f930, resampler = 0x51f9ac;
    if (step < 0x10000)
        needed = 0x51f980, resampler = 0x51fa8c;
    else if (step == 0x10000)
        needed = 0x51f978, resampler = 0x51fa80;
    cpu.edx = at(app, s + 0x18);
    put(app, cpu.edx, needed);
    put(app, at(app, s + 0x1c), resampler);
    cpu.eax = 0;
    cpu.ecx = s;
    cpu.esp += 4;
}

/* 0x51f930 (cdecl: state, frames): the source frames `frames` take at a
 * step over 1.0, what is left over kept at +0x10. */
void resample8MonoNeededDown(App* app, CPU& cpu)
{
    const reg32 s = at(app, cpu.esp + 4), frames = at(app, cpu.esp + 8);
    const reg32 base = ((frames - 1) * at(app, s + 8) + at(app, s + 4)) >> 16;
    const reg32 used = base + 1;
    cpu.eax = used + reg32(sbyte(app, s + 0x10));
    if (byte(app, s + 0xf) == 0)
        ++cpu.eax;
    cpu.edx = ((at(app, s + 8) * frames + at(app, s + 4)) >> 16) - used;
    putByte(app, s + 0x10, reg8(cpu.edx));
    cpu.ecx = s;
    cpu.esp += 4;
}

namespace
{

/* 0x51f978 and its kin (cdecl: state, frames): at the step 1.0, as many. */
void neededSame(CPU& cpu, App* app)
{
    cpu.eax = at(app, cpu.esp + 8);
    cpu.esp += 4;
}

/* 0x51fa80 and its kin (cdecl: state, count, source, the target's slot): at
 * 1.0 the source itself is the target. */
void sameBlock(CPU& cpu, App* app)
{
    cpu.edx = at(app, cpu.esp + 0x10);
    cpu.eax = at(app, cpu.esp + 0xc);
    put(app, cpu.edx, cpu.eax);
    cpu.esp += 4;
}

}  // namespace

void resample8MonoNeededSame(App* app, CPU& cpu) { neededSame(cpu, app); }
void resample8StereoNeededSame(App* app, CPU& cpu) { neededSame(cpu, app); }
void resample16MonoNeededSame(App* app, CPU& cpu) { neededSame(cpu, app); }
void resample16StereoNeededSame(App* app, CPU& cpu) { neededSame(cpu, app); }
void resample8MonoSame(App* app, CPU& cpu) { sameBlock(cpu, app); }
void resample8StereoSame(App* app, CPU& cpu) { sameBlock(cpu, app); }
void resample16MonoSame(App* app, CPU& cpu) { sameBlock(cpu, app); }
void resample16StereoSame(App* app, CPU& cpu) { sameBlock(cpu, app); }

/* 0x51f980 (cdecl: state, frames): the source frames `frames` take at a
 * step under 1.0. */
void resample8MonoNeededUp(App* app, CPU& cpu)
{
    const reg32 s = at(app, cpu.esp + 4), frames = at(app, cpu.esp + 8);
    cpu.eax = (((frames - 1) * at(app, s + 8) + at(app, s + 4)) >> 16) + 1;
    if (byte(app, s + 0xf) == 0)
        ++cpu.eax;
    cpu.edx = reg32(sbyte(app, s + 0xe));
    cpu.eax -= cpu.edx;
    cpu.ecx = s;
    cpu.esp += 4;
}

namespace
{

/* The 8-bit resamplers' shared call: 0x5270f0 (cdecl: count, source,
 * target, state, the position's slot, the step's whole and its fraction),
 * the position kept as 16.16 and back; the position's fraction then at +4. */
bool resample8Run(App* app, CPU& cpu, reg32 f, reg32 s, reg32 count, reg32 source, reg32 target)
{
    cpu.ecx = at(app, s + 8) >> 16;
    cpu.edx = at(app, s + 8) << 16;
    put(app, f, at(app, s + 4) << 16);
    cpu.eax = f;
    cpu.ebx = s;
    cpu.ebp = target;
    cpu.esi = source;
    cpu.edi = count;
    if (!call(app, cpu, 0x5270f0, {count, source, target, s, f, cpu.ecx, cpu.edx}))
        return false;
    put(app, s + 4, at(app, f) >> 16);
    return true;
}

/* The last frame of a block, between source frames [s] and [s]+1 by the
 * fraction at +4, into the target at `last`. */
void resample8Last(App* app, CPU& cpu, reg32 s, reg32 source, reg32 last)
{
    const reg32 i = at(app, s);
    const reg32 fraction = at(app, s + 4);
    cpu.ecx = fraction;
    const reg32 a = reg32(mul(sbyte(app, source + i) << 8, i32(0xffff - fraction))) >> 16;
    cpu.edx = reg32(mul(sbyte(app, source + i + 1) << 8, i32(fraction))) >> 16;
    putByte(app, last, reg8(i32(a + cpu.edx) >> 8));
}

}  // namespace

/* 0x51f9ac (cdecl: state, count, source, the target's slot): an 8-bit mono
 * block resampled down (a step over 1.0): the frame left from the last block
 * first, all but the last frame by 0x5270f0, the last here; the next block's
 * start and what it has left over kept. */
void resample8MonoDown(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 f = kept.frame(4, 4);
    cpu.esp = f;
    const reg32 s = at(app, kept.esp + 4);
    reg32 count = at(app, kept.esp + 8), source = at(app, kept.esp + 0xc);
    cpu.eax = s;
    if (byte(app, s + 0xf) != 0)
    {
        --source;
        const reg8 kept8 = byte(app, s + 0xd);
        putByte(app, source, kept8);
        setByte0(cpu.eax, kept8);
    }
    const reg32 target = at(app, at(app, kept.esp + 0x10));
    if (--count != 0 && !resample8Run(app, cpu, f, s, count, source, target))
        return;
    resample8Last(app, cpu, s, source, count + target);
    putByte(app, s + 0xd, byte(app, source + at(app, s) + 1));
    const reg32 position = at(app, s + 4) + at(app, s + 8);
    put(app, s + 4, position);
    putHalf(app, s + 6, 0);
    put(app, s, at(app, s) + (position >> 16));
    cpu.eax = reg32(sbyte(app, s + 0x10));
    putByte(app, s + 0xf, 1);
    put(app, s, cpu.eax);
    leave(cpu, kept, kEbx | kEsi | kEdi);
}

/* 0x51fa8c (cdecl: state, count, source, the target's slot): an 8-bit mono
 * block resampled up (a step under 1.0): the frames kept from the last block
 * first, all but the last frame by 0x5270f0, the last here; whether the next
 * block needs this one's last frame kept. */
void resample8MonoUp(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 f = kept.frame(4, 4);
    cpu.esp = f;
    const reg32 s = at(app, kept.esp + 4);
    reg32 count = at(app, kept.esp + 8), source = at(app, kept.esp + 0xc);
    cpu.eax = s;
    if (byte(app, s + 0xf) != 0)
    {
        --source;
        const reg8 kept8 = byte(app, s + 0xd);
        putByte(app, source, kept8);
        setByte0(cpu.eax, kept8);
    }
    if (byte(app, s + 0xe) != 0)
    {
        --source;
        const reg8 kept8 = byte(app, s + 0xc);
        putByte(app, source, kept8);
        setByte0(cpu.eax, kept8);
    }
    const reg32 target = at(app, at(app, kept.esp + 0x10));
    put(app, s, 0);
    if (--count != 0 && !resample8Run(app, cpu, f, s, count, source, target))
        return;
    resample8Last(app, cpu, s, source, count + target);
    putByte(app, s + 0xd, byte(app, source + at(app, s) + 1));
    const reg32 position = at(app, s + 4) + at(app, s + 8);
    cpu.edx = at(app, s + 8);
    put(app, s + 4, position);
    putHalf(app, s + 6, 0);
    put(app, s, at(app, s) + (position >> 16));
    cpu.eax = at(app, s + 4);
    if (cpu.eax < cpu.edx)
        putByte(app, s + 0xe, 0);
    else
    {
        const reg8 last = byte(app, source + at(app, s));
        putByte(app, s + 0xe, 1);
        setByte0(cpu.eax, last);
        putByte(app, s + 0xc, last);
    }
    putByte(app, s + 0xf, 1);
    leave(cpu, kept, kEbx | kEsi | kEdi);
}

/* 0x52002c (cdecl: state, the step setter's slot, the frames needed's, the
 * resampler's): an 8-bit stereo source's resampler, its step setter given.
 * 0; edx the resampler's slot. */
void resample8StereoSetup(App* app, CPU& cpu)
{
    const reg32 s = at(app, cpu.esp + 4);
    put(app, s, 0);
    put(app, s + 4, 0);
    putByte(app, s + 0x10, 0);
    putByte(app, s + 0x11, 0);
    putByte(app, s + 0x12, 0);
    put(app, s + 0x14, at(app, cpu.esp + 8));
    put(app, s + 0x18, at(app, cpu.esp + 0xc));
    cpu.edx = at(app, cpu.esp + 0x10);
    put(app, s + 0x1c, cpu.edx);
    put(app, at(app, s + 0x14), 0x51ff88);
    cpu.eax = 0;
    cpu.esp += 4;
}

/* 0x51ff88 (cdecl: state, step): 0x51fb94's, for 8-bit stereo. */
void resample8StereoStep(App* app, CPU& cpu)
{
    const reg32 s = at(app, cpu.esp + 4), step = at(app, cpu.esp + 8);
    const reg32 old = at(app, s + 8);
    if ((old >= 0x10000 || step >= 0x10000) && step != old && !(old > 0x10000 && step > 0x10000))
    {
        putByte(app, s + 0x10, 0);
        putByte(app, s + 0x11, 0);
        putByte(app, s + 0x12, 0);
        put(app, s + 4, 0);
        put(app, s, 0);
    }
    put(app, s + 8, step);
    reg32 needed = 0x51fc80, resampler = 0x51fcfc;
    if (step < 0x10000)
        needed = 0x51fcd0, resampler = 0x51fe30;
    else if (step == 0x10000)
        needed = 0x51fcc8, resampler = 0x51fe24;
    cpu.edx = at(app, s + 0x18);
    put(app, cpu.edx, needed);
    put(app, at(app, s + 0x1c), resampler);
    cpu.eax = 0;
    cpu.ecx = s;
    cpu.esp += 4;
}

/* 0x51fc80 (cdecl: state, frames): 0x51f930's, for 8-bit stereo. */
void resample8StereoNeededDown(App* app, CPU& cpu)
{
    const reg32 s = at(app, cpu.esp + 4), frames = at(app, cpu.esp + 8);
    const reg32 used = (((frames - 1) * at(app, s + 8) + at(app, s + 4)) >> 16) + 1;
    cpu.eax = used + reg32(sbyte(app, s + 0x12));
    if (byte(app, s + 0x11) == 0)
        ++cpu.eax;
    cpu.edx = ((at(app, s + 8) * frames + at(app, s + 4)) >> 16) - used;
    putByte(app, s + 0x12, reg8(cpu.edx));
    cpu.ecx = s;
    cpu.esp += 4;
}

/* 0x51fcd0 (cdecl: state, frames): 0x51f980's, for 8-bit stereo. */
void resample8StereoNeededUp(App* app, CPU& cpu)
{
    const reg32 s = at(app, cpu.esp + 4), frames = at(app, cpu.esp + 8);
    cpu.eax = (((frames - 1) * at(app, s + 8) + at(app, s + 4)) >> 16) + 1;
    if (byte(app, s + 0x11) == 0)
        ++cpu.eax;
    cpu.edx = reg32(sbyte(app, s + 0x10));
    cpu.eax -= cpu.edx;
    cpu.ecx = s;
    cpu.esp += 4;
}

namespace
{

/* 0x527170 for the 8-bit stereo resamplers, as resample8Run 0x5270f0. */
bool resample8StereoRun(App* app, CPU& cpu, reg32 f, reg32 s, reg32 count, reg32 source, reg32 target)
{
    cpu.ecx = at(app, s + 8) >> 16;
    cpu.edx = at(app, s + 8) << 16;
    put(app, f, at(app, s + 4) << 16);
    cpu.eax = f;
    cpu.ebx = s;
    cpu.ebp = target;
    cpu.esi = source;
    cpu.edi = count;
    if (!call(app, cpu, 0x527170, {count, source, target, s, f, cpu.ecx, cpu.edx}))
        return false;
    put(app, s + 4, at(app, f) >> 16);
    return true;
}

/* An 8-bit stereo block's last frame, into `last`: left between source
 * frames [s] and [s]+1 (bytes +0, +2), right likewise (+1, +3); the next
 * frame's two bytes kept at +0xe and +0xf.  `scratch`: where 0x51fcfc keeps
 * the left's first sample (0 for 0x51fe30, which keeps none). */
void resample8StereoLast(App* app, CPU& cpu, reg32 s, reg32 source, reg32 last, reg32 scratch)
{
    const reg32 i = at(app, s), fraction = at(app, s + 4);
    const i32 first = sbyte(app, source + i * 2) << 8;
    if (scratch != 0)
        put(app, scratch, reg32(first));
    reg32 a = reg32(mul(first, i32(0xffff - fraction))) >> 16;
    reg32 d = reg32(mul(sbyte(app, source + i * 2 + 2) << 8, i32(fraction))) >> 16;
    putByte(app, last, reg8(i32(a + d) >> 8));
    a = reg32(mul(sbyte(app, source + i * 2 + 1) << 8, i32(0xffff - fraction))) >> 16;
    d = reg32(mul(sbyte(app, source + i * 2 + 3) << 8, i32(fraction))) >> 16;
    putByte(app, last + 1, reg8(i32(a + d) >> 8));
    cpu.ecx = fraction;
    cpu.edx = d;
    putByte(app, s + 0xe, byte(app, source + i * 2 + 2));
    putByte(app, s + 0xf, byte(app, source + i * 2 + 3));
}

}  // namespace

/* 0x51fcfc (cdecl: state, count, source, the target's slot): 0x51f9ac's,
 * for 8-bit stereo. */
void resample8StereoDown(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 f = kept.frame(4, 8);
    cpu.esp = f;
    const reg32 s = at(app, kept.esp + 4);
    reg32 count = at(app, kept.esp + 8), source = at(app, kept.esp + 0xc);
    cpu.eax = s;
    if (byte(app, s + 0x11) != 0)
    {
        const reg8 right = byte(app, s + 0xf), left = byte(app, s + 0xe);
        putByte(app, --source, right);
        putByte(app, --source, left);
        setByte0(cpu.eax, left);
    }
    const reg32 target = at(app, at(app, kept.esp + 0x10));
    if (--count != 0 && !resample8StereoRun(app, cpu, f, s, count, source, target))
        return;
    resample8StereoLast(app, cpu, s, source, target + count * 2, f + 4);
    const reg32 position = at(app, s + 4) + at(app, s + 8);
    put(app, s + 4, position);
    putHalf(app, s + 6, 0);
    cpu.edx = at(app, s) + (position >> 16);
    put(app, s, cpu.edx);
    cpu.eax = reg32(sbyte(app, s + 0x12));
    putByte(app, s + 0x11, 1);
    put(app, s, cpu.eax);
    leave(cpu, kept, kEbx | kEsi | kEdi);
}

/* 0x51fe30 (cdecl: state, count, source, the target's slot): 0x51fa8c's,
 * for 8-bit stereo. */
void resample8StereoUp(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 f = kept.frame(4, 4);
    cpu.esp = f;
    const reg32 s = at(app, kept.esp + 4);
    reg32 count = at(app, kept.esp + 8), source = at(app, kept.esp + 0xc);
    cpu.eax = s;
    if (byte(app, s + 0x11) != 0)
    {
        const reg8 right = byte(app, s + 0xf), left = byte(app, s + 0xe);
        putByte(app, --source, right);
        putByte(app, --source, left);
        setByte0(cpu.eax, left);
    }
    if (byte(app, s + 0x10) != 0)
    {
        const reg8 right = byte(app, s + 0xd), left = byte(app, s + 0xc);
        putByte(app, --source, right);
        putByte(app, --source, left);
        setByte0(cpu.eax, left);
    }
    const reg32 target = at(app, at(app, kept.esp + 0x10));
    put(app, s, 0);
    if (--count != 0 && !resample8StereoRun(app, cpu, f, s, count, source, target))
        return;
    resample8StereoLast(app, cpu, s, source, target + count * 2, 0);
    const reg32 position = at(app, s + 4) + at(app, s + 8);
    cpu.ecx = at(app, s + 8);
    put(app, s + 4, position);
    putHalf(app, s + 6, 0);
    cpu.edx = at(app, s) + (position >> 16);
    cpu.eax = at(app, s + 4);
    put(app, s, cpu.edx);
    if (cpu.eax < cpu.ecx)
        putByte(app, s + 0x10, 0);
    else
    {
        putByte(app, s + 0x10, 1);
        putByte(app, s + 0xc, byte(app, source + at(app, s) * 2));
        const reg8 right = byte(app, source + at(app, s) * 2 + 1);
        cpu.eax = at(app, s);
        setByte0(cpu.eax, right);
        putByte(app, s + 0xd, right);
    }
    putByte(app, s + 0x11, 1);
    leave(cpu, kept, kEbx | kEsi | kEdi);
}

/* 0x520070, 0x5200c0: a 16-bit mono resampler's frames needed, down and up
 * -- the same code as 8-bit stereo's (the same state). */
void resample16MonoNeededDown(App* app, CPU& cpu) { resample8StereoNeededDown(app, cpu); }
void resample16MonoNeededUp(App* app, CPU& cpu) { resample8StereoNeededUp(app, cpu); }

namespace
{

/* 0x527210 for the 16-bit mono resamplers, as resample8Run 0x5270f0. */
bool resample16MonoRun(App* app, CPU& cpu, reg32 f, reg32 s, reg32 count, reg32 source, reg32 target)
{
    cpu.ecx = at(app, s + 8) >> 16;
    cpu.edx = at(app, s + 8) << 16;
    put(app, f, at(app, s + 4) << 16);
    cpu.eax = f;
    cpu.ebx = s;
    cpu.ebp = target;
    cpu.esi = source;
    cpu.edi = count;
    if (!call(app, cpu, 0x527210, {count, source, target, s, f, cpu.ecx, cpu.edx}))
        return false;
    put(app, s + 4, at(app, f) >> 16);
    return true;
}

/* A 16-bit mono block's last frame at `last`, between source frames [s]
 * and [s]+1 by the fraction at +4: the first's share written, then the
 * second's added to it; the next frame kept at +0xe.  ecx the fraction, edx
 * the sum. */
void resample16MonoLast(App* app, CPU& cpu, reg32 s, reg32 source, reg32 last)
{
    const reg32 i = at(app, s), fraction = at(app, s + 4);
    cpu.ecx = fraction;
    putHalf(app, last, reg16(reg32(mul(shalf(app, source + i * 2), i32(0xffff - fraction))) >> 16));
    const reg32 second = reg32(mul(i32(fraction), shalf(app, source + i * 2 + 2))) >> 16;
    cpu.edx = reg32(shalf(app, last)) + second;
    putHalf(app, last, reg16(cpu.edx));
    putHalf(app, s + 0xe, half(app, source + at(app, s) * 2 + 2));
}

}  // namespace

/* 0x5200ec (cdecl: state, count, source, the target's slot): a 16-bit mono
 * block resampled down (a step over 1.0), as 0x51f9ac 8-bit. */
void resample16MonoDown(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 f = kept.frame(4, 4);
    cpu.esp = f;
    const reg32 s = at(app, kept.esp + 4);
    reg32 count = at(app, kept.esp + 8), source = at(app, kept.esp + 0xc);
    cpu.eax = s;
    if (byte(app, s + 0x11) != 0)
    {
        source -= 2;
        const reg16 kept16 = half(app, s + 0xe);
        putHalf(app, source, kept16);
        cpu.eax = (cpu.eax & 0xffff0000) | kept16;
    }
    const reg32 target = at(app, at(app, kept.esp + 0x10));
    if (--count != 0 && !resample16MonoRun(app, cpu, f, s, count, source, target))
        return;
    resample16MonoLast(app, cpu, s, source, target + count * 2);
    const reg32 position = at(app, s + 4) + at(app, s + 8);
    put(app, s + 4, position);
    putHalf(app, s + 6, 0);
    cpu.edx = at(app, s) + (position >> 16);
    put(app, s, cpu.edx);
    cpu.eax = reg32(sbyte(app, s + 0x12));
    putByte(app, s + 0x11, 1);
    put(app, s, cpu.eax);
    leave(cpu, kept, kEbx | kEsi | kEdi);
}

/* 0x5201e4 (cdecl: state, count, source, the target's slot): a 16-bit mono
 * block resampled up (a step under 1.0), as 0x51fa8c 8-bit. */
void resample16MonoUp(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 f = kept.frame(4, 4);
    cpu.esp = f;
    const reg32 s = at(app, kept.esp + 4);
    reg32 count = at(app, kept.esp + 8), source = at(app, kept.esp + 0xc);
    cpu.eax = s;
    if (byte(app, s + 0x11) != 0)
    {
        source -= 2;
        const reg16 kept16 = half(app, s + 0xe);
        putHalf(app, source, kept16);
        cpu.eax = (cpu.eax & 0xffff0000) | kept16;
    }
    if (byte(app, s + 0x10) != 0)
    {
        source -= 2;
        const reg16 kept16 = half(app, s + 0xc);
        putHalf(app, source, kept16);
        cpu.eax = (cpu.eax & 0xffff0000) | kept16;
    }
    const reg32 target = at(app, at(app, kept.esp + 0x10));
    put(app, s, 0);
    if (--count != 0 && !resample16MonoRun(app, cpu, f, s, count, source, target))
        return;
    resample16MonoLast(app, cpu, s, source, target + count * 2);
    const reg32 position = at(app, s + 4) + at(app, s + 8);
    cpu.ecx = at(app, s + 8);
    put(app, s + 4, position);
    putHalf(app, s + 6, 0);
    cpu.edx = at(app, s) + (position >> 16);
    cpu.eax = at(app, s + 4);
    put(app, s, cpu.edx);
    if (cpu.eax < cpu.ecx)
        putByte(app, s + 0x10, 0);
    else
    {
        putByte(app, s + 0x10, 1);
        const reg16 last = half(app, source + at(app, s) * 2);
        cpu.eax = (at(app, s) & 0xffff0000) | last;
        putHalf(app, s + 0xc, last);
    }
    putByte(app, s + 0x11, 1);
    leave(cpu, kept, kEbx | kEsi | kEdi);
}

/* 0x5203f0 (cdecl: state, frames): a 16-bit stereo resampler's frames
 * needed at a step over 1.0, as 0x51f930's with its state's flags at
 * +0x15 and +0x16. */
void resample16StereoNeededDown(App* app, CPU& cpu)
{
    const reg32 s = at(app, cpu.esp + 4), frames = at(app, cpu.esp + 8);
    const reg32 used = (((frames - 1) * at(app, s + 8) + at(app, s + 4)) >> 16) + 1;
    cpu.eax = used + reg32(sbyte(app, s + 0x16));
    if (byte(app, s + 0x15) == 0)
        ++cpu.eax;
    cpu.edx = ((at(app, s + 8) * frames + at(app, s + 4)) >> 16) - used;
    putByte(app, s + 0x16, reg8(cpu.edx));
    cpu.ecx = s;
    cpu.esp += 4;
}

/* 0x520440 (cdecl: state, frames): at a step under 1.0, as 0x51f980's. */
void resample16StereoNeededUp(App* app, CPU& cpu)
{
    const reg32 s = at(app, cpu.esp + 4), frames = at(app, cpu.esp + 8);
    cpu.eax = (((frames - 1) * at(app, s + 8) + at(app, s + 4)) >> 16) + 1;
    if (byte(app, s + 0x15) == 0)
        ++cpu.eax;
    cpu.edx = reg32(sbyte(app, s + 0x14));
    cpu.eax -= cpu.edx;
    cpu.ecx = s;
    cpu.esp += 4;
}

namespace
{

/* 0x527290 for the 16-bit stereo resamplers, as resample8Run 0x5270f0. */
bool resample16StereoRun(App* app, CPU& cpu, reg32 f, reg32 s, reg32 count, reg32 source, reg32 target)
{
    cpu.ecx = at(app, s + 8) >> 16;
    cpu.edx = at(app, s + 8) << 16;
    put(app, f, at(app, s + 4) << 16);
    cpu.eax = f;
    cpu.ebx = s;
    cpu.ebp = target;
    cpu.esi = source;
    cpu.edi = count;
    if (!call(app, cpu, 0x527290, {count, source, target, s, f, cpu.ecx, cpu.edx}))
        return false;
    put(app, s + 4, at(app, f) >> 16);
    return true;
}

/* A 16-bit stereo block's last frame at `last`: each side's first share
 * written, then its second's added; the next frame kept at +0x10 and
 * +0x12.  edx the right side's sum, ecx as `fractionLeft` says: the
 * fraction (down) or what 0x5205bc leaves there. */
void resample16StereoLast(App* app, CPU& cpu, reg32 s, reg32 source, reg32 last)
{
    const reg32 i = at(app, s), fraction = at(app, s + 4);
    const reg32 frame = source + i * 4;
    putHalf(app, last, reg16(reg32(mul(shalf(app, frame), i32(0xffff - fraction))) >> 16));
    reg32 second = reg32(mul(shalf(app, frame + 4), i32(fraction))) >> 16;
    putHalf(app, last, reg16(reg32(shalf(app, last)) + second));
    putHalf(app, last + 2, reg16(reg32(mul(shalf(app, frame + 2), i32(0xffff - fraction))) >> 16));
    second = reg32(mul(shalf(app, frame + 6), i32(fraction))) >> 16;
    cpu.edx = reg32(shalf(app, last + 2)) + second;
    putHalf(app, last + 2, reg16(cpu.edx));
    cpu.ecx = fraction;
    putHalf(app, s + 0x10, half(app, frame + 4));
    putHalf(app, s + 0x12, half(app, frame + 6));
}

/* What a 16-bit stereo block keeps before it: the last block's frame at
 * +0x10 when +0x15 says so (eax's low word the left's, edx's the right's). */
reg32 resample16StereoKept(App* app, CPU& cpu, reg32 s, reg32 source)
{
    cpu.eax = s;
    if (byte(app, s + 0x15) != 0)
    {
        source -= 2;
        const reg16 right = half(app, s + 0x12);
        putHalf(app, source, right);
        cpu.edx = (cpu.edx & 0xffff0000) | right;
        source -= 2;
        const reg16 left = half(app, s + 0x10);
        putHalf(app, source, left);
        cpu.eax = (cpu.eax & 0xffff0000) | left;
    }
    return source;
}

}  // namespace

/* 0x52046c (cdecl: state, count, source, the target's slot): a 16-bit
 * stereo block resampled down, as 0x51f9ac 8-bit mono. */
void resample16StereoDown(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 f = kept.frame(4, 4);
    cpu.esp = f;
    const reg32 s = at(app, kept.esp + 4);
    reg32 count = at(app, kept.esp + 8);
    const reg32 source = resample16StereoKept(app, cpu, s, at(app, kept.esp + 0xc));
    const reg32 target = at(app, at(app, kept.esp + 0x10));
    if (--count != 0 && !resample16StereoRun(app, cpu, f, s, count, source, target))
        return;
    resample16StereoLast(app, cpu, s, source, target + count * 4);
    const reg32 position = at(app, s + 4) + at(app, s + 8);
    put(app, s + 4, position);
    putHalf(app, s + 6, 0);
    put(app, s, at(app, s) + (position >> 16));
    cpu.eax = reg32(sbyte(app, s + 0x16));
    putByte(app, s + 0x15, 1);
    put(app, s, cpu.eax);
    leave(cpu, kept, kEbx | kEsi | kEdi);
}

/* 0x5205bc (cdecl: state, count, source, the target's slot): a 16-bit
 * stereo block resampled up, as 0x51fa8c 8-bit mono. */
void resample16StereoUp(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 f = kept.frame(4, 4);
    cpu.esp = f;
    const reg32 s = at(app, kept.esp + 4);
    reg32 count = at(app, kept.esp + 8);
    reg32 source = resample16StereoKept(app, cpu, s, at(app, kept.esp + 0xc));
    if (byte(app, s + 0x14) != 0)
    {
        source -= 2;
        putHalf(app, source, half(app, s + 0xe));
        source -= 2;
        const reg16 left = half(app, s + 0xc);
        putHalf(app, source, left);
        cpu.eax = (cpu.eax & 0xffff0000) | left;
    }
    const reg32 target = at(app, at(app, kept.esp + 0x10));
    put(app, s, 0);
    if (--count != 0 && !resample16StereoRun(app, cpu, f, s, count, source, target))
        return;
    resample16StereoLast(app, cpu, s, source, target + count * 4);
    const reg32 position = at(app, s + 4) + at(app, s + 8);
    cpu.ecx = at(app, s + 8);
    put(app, s + 4, position);
    putHalf(app, s + 6, 0);
    cpu.edx = at(app, s) + (position >> 16);
    cpu.eax = at(app, s + 4);
    put(app, s, cpu.edx);
    if (cpu.eax < cpu.ecx)
        putByte(app, s + 0x14, 0);
    else
    {
        putByte(app, s + 0x14, 1);
        putHalf(app, s + 0xc, half(app, source + at(app, s) * 4));
        const reg16 right = half(app, source + at(app, s) * 4 + 2);
        cpu.eax = (at(app, s) & 0xffff0000) | right;
        putHalf(app, s + 0xe, right);
    }
    putByte(app, s + 0x15, 1);
    leave(cpu, kept, kEbx | kEsi | kEdi);
}

namespace
{

/* The decoders' inlined memcpy -- mov eax, ecx; shr ecx, 2; rep movsd; mov
 * cl, al; and cl, 3; rep movsb -- of `bytes` from esi to edi: dwords, then
 * bytes; esi and edi past them, ecx 0, eax the count. */
void repCopy(App* app, CPU& cpu, reg32 bytes)
{
    cpu.eax = bytes;
    for (reg32 n = bytes >> 2; n != 0; --n)
    {
        put(app, cpu.edi, at(app, cpu.esi));
        cpu.esi += 4;
        cpu.edi += 4;
    }
    for (reg32 n = bytes & 3; n != 0; --n)
        putByte(app, cpu.edi++, byte(app, cpu.esi++));
    cpu.ecx = 0;
}

constexpr reg32 kFill = 0x4e0640;  // memset: eax where, edx the byte, ebx how many

}  // namespace

/* 0x52c8f0 (eax the state): a PCM sound's frames played so far. */
void pcmPlayed(App* app, CPU& cpu)
{
    cpu.eax = at(app, cpu.eax + 4);
    cpu.esp += 4;
}

/* 0x52c8f4: PCM played once (eax the state -- its data, frame, length and
 * frame's shift -- edx frames wanted, ebx where): its frames copied, those
 * past its end silence.  1; -1 at its end. */
void pcmOnceDecode(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 s = cpu.eax, wanted = cpu.edx, target = cpu.ebx;
    const reg32 frame = at(app, s + 4), length = at(app, s + 8);
    if (frame >= length)
    {
        cpu.eax = 0xffffffff;
        cpu.ebp = kept.ebp;
        cpu.esp = kept.esp + 4;
        return;
    }
    const reg32 f = kept.frame(1, 4);
    const reg8 shift = byte(app, s + 0xc) & 0x1f;
    put(app, s + 4, frame + wanted);
    if (frame + wanted < length)
    {
        cpu.edi = target;
        cpu.esi = at(app, s) + (frame << shift);
        cpu.edx = wanted << shift;
        repCopy(app, cpu, cpu.edx);
    }
    else
    {
        const reg32 left = length - frame;
        put(app, f, left);
        cpu.edi = target;
        cpu.esi = at(app, s) + (frame << shift);
        repCopy(app, cpu, left << shift);
        cpu.edx = 0;
        cpu.ebx = (wanted - left) << shift;
        cpu.eax = (left << shift) + target;
        cpu.esp = kept.frame(4, 4);
        if (!call(app, cpu, kFill))
            return;
    }
    cpu.eax = 1;
    cpu.ecx = kept.ecx;
    cpu.esi = kept.esi;
    cpu.edi = kept.edi;
    cpu.ebp = kept.ebp;
    cpu.esp = kept.esp + 4;
}

/* 0x52c9d0: PCM looped (eax the state -- data, frame, loop's start, last
 * frame, frame's shift -- edx frames wanted, ebx where): copied a stretch at
 * a time, back to the loop's start past the end.  1. */
void pcmLoopedDecode(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 s = cpu.eax;
    i32 wanted = i32(cpu.edx);
    reg32 target = cpu.ebx;
    cpu.edx = s;
    while (wanted > 0)
    {
        reg32 n = at(app, s + 0xc) - at(app, s + 4) + 1;
        if (wanted < i32(n))
            n = reg32(wanted);
        cpu.ebx = n;
        const reg8 shift = byte(app, s + 0x10) & 0x1f;
        cpu.esi = at(app, s) + (at(app, s + 4) << shift);
        cpu.edi = target;
        repCopy(app, cpu, n << shift);
        wanted -= i32(n);
        const reg32 frame = at(app, s + 4) + n;
        target += n << shift;
        put(app, s + 4, frame);
        if (frame > at(app, s + 0xc))
            put(app, s + 4, at(app, s + 8));
    }
    cpu.eax = 1;
    cpu.ecx = kept.ecx;
    cpu.esi = kept.esi;
    cpu.edi = kept.edi;
    cpu.ebp = kept.ebp;
    cpu.esp = kept.esp + 4;
}

/* 0x52ca80: PCM streamed (eax the state -- data, chunk's frames, frame,
 * frame's shift -- edx frames wanted, ebx where): each chunk copied, the
 * next asked of the refill ([0x5678b4]: eax the state, edx where its length
 * goes); none, and the rest is silence.  1; -1 with no data. */
void pcmStreamedDecode(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 f = kept.frame(4, 0xc);
    cpu.esp = f;
    const reg32 s = cpu.eax;
    put(app, f + 8, cpu.edx);
    put(app, f + 4, cpu.ebx);
    cpu.edx = at(app, s);
    cpu.ebp = s;
    if (cpu.edx == 0)
    {
        cpu.eax = 0xffffffff;
        leave(cpu, kept, kEcx | kEsi | kEdi);
        return;
    }
    put(app, f, s + 4);
    while (s32(app, f + 8) > 0)
    {
        if (s32(app, s + 8) >= s32(app, s + 4))
        {
            cpu.edx = at(app, f);
            cpu.eax = s;
            if (!call(app, cpu, at(app, 0x5678b4)))
                return;
            if (cpu.eax != 0 || at(app, s) == 0)
            {
                cpu.ebx = at(app, f + 8) << (byte(app, s + 0xc) & 0x1f);
                setByte0(cpu.ecx, byte(app, s + 0xc));
                cpu.eax = at(app, f + 4);
                cpu.edx = 0;
                if (!call(app, cpu, kFill))
                    return;
                put(app, s + 8, 0);
                cpu.eax = 1;
                put(app, s + 4, 0);
                leave(cpu, kept, kEcx | kEsi | kEdi);
                return;
            }
            put(app, s + 8, cpu.eax);
        }
        reg32 n = at(app, s + 4) - at(app, s + 8);
        if (i32(n) > s32(app, f + 8))
            n = at(app, f + 8);
        cpu.edx = n;
        const reg8 shift = byte(app, s + 0xc) & 0x1f;
        cpu.edi = at(app, f + 4);
        cpu.esi = at(app, s) + (at(app, s + 8) << shift);
        repCopy(app, cpu, n << shift);
        cpu.edi = at(app, f + 4);
        put(app, s + 8, at(app, s + 8) + n);
        cpu.eax = n << shift;
        setByte0(cpu.ecx, byte(app, s + 0xc));
        cpu.esi = at(app, f + 8) - n;
        cpu.ebx = cpu.edi + cpu.eax;
        put(app, f + 8, cpu.esi);
        put(app, f + 4, cpu.ebx);
    }
    cpu.eax = 1;
    leave(cpu, kept, kEcx | kEsi | kEdi);
}

/* 0x52cba0: PCM streamed from a file (eax the state -- data, chunk's
 * frames, frame, the stream, frame's shift as a word at +0x10, the frames
 * taken since the last release at +0x12 -- edx frames wanted, ebx where):
 * the frames taken last time given back (0x511998), each chunk copied, the
 * next asked of the stream (0x5118fc); none, and the rest is silence.  The
 * frames taken this time. */
void pcmFileDecode(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 f = kept.frame(4, 0xc);
    cpu.esp = f;
    const reg32 s = cpu.eax;
    cpu.ecx = s;
    put(app, f + 8, cpu.edx);
    put(app, f + 4, cpu.ebx);
    cpu.ebp = s;
    cpu.edx = (cpu.edx & 0xffff0000) | half(app, s + 0x12);
    if (half(app, s + 0x12) != 0)
    {
        cpu.edx = half(app, s + 0x12);
        cpu.eax = at(app, s + 0xc);
        if (!call(app, cpu, 0x511998))
            return;
        putHalf(app, cpu.ecx + 0x12, 0);
    }
    const auto shift = [&] { return reg8(shalf(app, s + 0x10)); };
    while (s32(app, f + 8) > 0)
    {
        if (s32(app, s + 8) >= s32(app, s + 4))
        {
            cpu.edx = f;
            cpu.eax = at(app, s + 0xc);
            if (!call(app, cpu, 0x5118fc))
                return;
            put(app, s, cpu.eax);
            if (cpu.eax == 0)
            {
                if (half(app, s + 0x12) != 0)
                {
                    cpu.ecx = reg32(shalf(app, s + 0x10));
                    cpu.ebx = at(app, f + 8) << (cpu.ecx & 0x1f);
                    cpu.eax = at(app, f + 4);
                    cpu.edx = 0;
                    if (!call(app, cpu, kFill))
                        return;
                }
                break;
            }
            put(app, s + 8, 0);
            put(app, s + 4, at(app, f));
        }
        reg32 n = at(app, s + 4) - at(app, s + 8);
        if (i32(n) > s32(app, f + 8))
            n = at(app, f + 8);
        cpu.edx = n;
        cpu.edi = at(app, f + 4);
        cpu.esi = at(app, s) + (at(app, s + 8) << (shift() & 0x1f));
        repCopy(app, cpu, n << (shift() & 0x1f));
        cpu.edi = at(app, f + 4);
        cpu.ecx = reg32(shalf(app, s + 0x10));
        const reg32 rest = at(app, f + 8) - n;
        put(app, f + 8, rest);
        put(app, s + 8, at(app, s + 8) + n);
        cpu.eax = n << (cpu.ecx & 0x1f);
        cpu.ebx = ((rest & 0xffff0000) | half(app, s + 0x12)) + n;
        cpu.ecx = cpu.edi + cpu.eax;
        putHalf(app, s + 0x12, reg16(cpu.ebx));
        put(app, f + 4, cpu.ecx);
    }
    cpu.eax = half(app, s + 0x12);
    leave(cpu, kept, kEcx | kEsi | kEdi);
}

/* 0x52ccb8 (eax the stream, ebx the frame's bytes, ecx the decoder's slot,
 * edx the state): PCM streamed from a file set up, after 0x52d160.  0x14,
 * the state's size. */
void pcmFileSetup(App* app, CPU& cpu)
{
    if (!call(app, cpu, 0x52d160))
        return;
    const reg32 s = cpu.edx;
    put(app, s, 0);
    put(app, s + 4, 0xffffffff);
    put(app, s + 8, 0);
    putHalf(app, s + 0x12, 0);
    cpu.ebx = reg32(i32(cpu.ebx) >> 1);
    put(app, s + 0xc, cpu.eax);
    putHalf(app, s + 0x10, reg16(cpu.ebx));
    cpu.eax = 0x14;
    put(app, cpu.ecx, 0x52cba0);
    cpu.esp += 4;
}

namespace
{

/* 0x527520 and its kin (stdcall, 4 words): PCM streamed from a file, `bytes`
 * a frame -- [esp+0xc] the decoder's slot, [esp+0x10] the second function's,
 * none. */
void pcmFileEntry(App* app, CPU& cpu, reg32 bytes)
{
    const reg32 esp = cpu.esp;
    cpu.ecx = at(app, esp + 0xc);
    cpu.ebx = at(app, esp + 0x10);
    put(app, cpu.ebx, 0);
    cpu.ebx = bytes;
    if (!call(app, cpu, 0x52ccb8))
        return;
    cpu.esp = esp + 4 + 0x10;
}

}  // namespace

void pcmFileMono(App* app, CPU& cpu) { pcmFileEntry(app, cpu, 1); }
void pcmFileStereo(App* app, CPU& cpu) { pcmFileEntry(app, cpu, 2); }
void pcmFileStereo2(App* app, CPU& cpu) { pcmFileEntry(app, cpu, 2); }
void pcmFileQuad(App* app, CPU& cpu) { pcmFileEntry(app, cpu, 4); }

namespace
{

constexpr reg32 kXaMono = 0x52d1a0;  // mmx::xaMono (cdecl: the state): [s] frames from [s+8] to [s+0xc]

/* The XA decoders' block's place: frame * 15 / 28 (15 bytes a block of 28
 * frames), cdq; idiv as the code has it -- ecx 0x1c, edx the remainder. */
reg32 xaBlockBytes(CPU& cpu, reg32 frame)
{
    cpu.eax = reg32(mul(i32(frame), 15));
    cpu.ecx = 0x1c;
    idiv(cpu, 0x1c);
    return cpu.eax;
}

}  // namespace

/* 0x528f70 (eax the state): an XA sound's frames played so far. */
void xaPlayed(App* app, CPU& cpu)
{
    cpu.eax = at(app, cpu.eax + 0x18);
    cpu.esp += 4;
}

/* 0x528f74: XA played once (eax the state -- at +0x18 the frame, +0x14 the
 * length, +0x10 the data, +0x1c the frames kept from the last block and
 * +0x1e them -- edx frames wanted, ebx where): the kept frames first, then
 * whole blocks by mmx::xaMono, what a block leaves over kept; past the end,
 * silence.  1; -1 at its end. */
void xaOnceDecode(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 s = cpu.eax;
    reg32 wanted = cpu.edx;
    cpu.edx = at(app, s + 0x18);
    cpu.ecx = at(app, s + 0x14);
    cpu.ebx = s;
    if (i32(cpu.edx) >= i32(cpu.ecx))
    {
        cpu.eax = 0xffffffff;
        cpu.ecx = kept.ecx;
        cpu.esp = kept.esp + 4;
        return;
    }
    put(app, s + 0xc, kept.ebx);
    const i32 held = shalf(app, s + 0x1c);
    if (i32(wanted) <= held)
    {
        i32 i = 0;
        for (; i < i32(wanted); ++i)
        {
            putHalf(app, at(app, s + 0xc), half(app, s + 0x1e + 2 * i));
            put(app, s + 0xc, at(app, s + 0xc) + 2);
        }
        cpu.edx = s;
        reg32 left = 0;
        for (; i < shalf(app, s + 0x1c); ++i)
        {
            cpu.edx += 2;
            ++left;
            putHalf(app, cpu.edx + 0x1c, half(app, s + 0x1e + 2 * i));
        }
        cpu.eax = 1;
        putHalf(app, s + 0x1c, reg16(left));
        cpu.ecx = kept.ecx;
        cpu.esp = kept.esp + 4;
        return;
    }
    for (i32 i = 0; i < held; ++i)
    {
        putHalf(app, at(app, s + 0xc), half(app, s + 0x1e + 2 * i));
        put(app, s + 0xc, at(app, s + 0xc) + 2);
    }
    reg32 rest = wanted - reg32(held);
    i32 left = s32(app, s + 0x14) - s32(app, s + 0x18);
    if (left < 0)
        left = 0;
    const reg32 n = i32(rest) >= left ? reg32(left) : rest;
    cpu.edx = at(app, s + 0x10) + xaBlockBytes(cpu, at(app, s + 0x18));
    put(app, s, n);
    put(app, s + 8, cpu.edx);
    cpu.edi = n;
    cpu.esi = rest;
    cpu.ebp = reg32(left);
    cpu.esp = kept.frame(4);
    if (!call(app, cpu, kXaMono, {s}))
        return;
    put(app, s + 0x18, at(app, s + 0x18) + n);
    cpu.eax = at(app, s);
    cpu.edx = at(app, s + 0x18) - cpu.eax;
    put(app, s + 0x18, cpu.edx);
    if (reg32(left) == n)
    {
        i32 silence = i32(rest - n - (cpu.edx - at(app, s + 0x14)));
        for (; silence > 0; --silence)
        {
            cpu.edx = 0;
            putHalf(app, at(app, s + 0xc), 0);
            put(app, s + 0xc, at(app, s + 0xc) + 2);
        }
    }
    else
    {
        const i32 over = s32(app, s);
        cpu.eax = 0;
        if (over < 0)
        {
            cpu.edx = s;
            const reg32 from = at(app, s + 0xc);
            for (i32 k = over; k < 0; ++k)
            {
                cpu.edx += 2;
                ++cpu.eax;
                putHalf(app, cpu.edx + 0x1c, half(app, from + 2 * k));
            }
        }
        putHalf(app, s + 0x1c, reg16(cpu.eax));
    }
    cpu.eax = 1;
    cpu.ecx = kept.ecx;
    cpu.esi = kept.esi;
    cpu.edi = kept.edi;
    cpu.ebp = kept.ebp;
    cpu.esp = kept.esp + 4;
}

/* 0x529140 (eax how many there are, edx where they are, ebx how many are
 * wanted, ecx the slot of where they go): the frames an XA loop kept, as
 * many as are wanted copied out and the rest moved to the front.  How many
 * were copied; the slot past them. */
void xaKeptCopy(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const i32 there = i32(cpu.eax);
    const reg32 from = cpu.edx, slot = cpu.ecx;
    cpu.edx = at(app, slot);
    i32 copied = i32(cpu.ebx);
    if (there < copied)
        copied = there;
    i32 i = 0;
    if (copied > 0)
    {
        cpu.ecx = from;
        for (; i < copied; ++i)
        {
            const reg16 w = half(app, cpu.ecx);
            cpu.ebx = (cpu.ebx & 0xffff0000) | w;
            cpu.ecx += 2;
            cpu.edx += 2;
            putHalf(app, cpu.edx - 2, w);
        }
    }
    if (i < there)
    {
        cpu.ecx = from;
        cpu.ebx = from + 2 * reg32(i);
        for (; i < there; ++i)
        {
            cpu.ecx += 2;
            putHalf(app, cpu.ecx - 2, half(app, cpu.ebx));
            cpu.ebx += 2;
        }
    }
    put(app, slot, cpu.edx);
    cpu.eax = reg32(copied);
    cpu.esp = kept.esp + 4;
}

/* 0x5291a8: XA looped (eax the state -- as xaOnceDecode's, +0x20 the length,
 * +0x1c the loop's start, +0x24 the frames kept and +0x26 them, +0x94 and
 * +0x96 the decoder's history at the loop -- edx frames wanted, ebx where):
 * the kept frames first, then whole blocks; the block across the end
 * decoded into the kept frames, and the loop's start (its block decoded on
 * the stack, the frames from the start kept) after it.  1. */
void xaLoopDecode(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 f = kept.frame(4, 0x44);
    cpu.esp = f;
    const reg32 s = cpu.eax;
    i32 wanted = i32(cpu.edx);
    cpu.edi = cpu.edx;
    cpu.esi = s;
    put(app, s + 0xc, cpu.ebx);
    if (wanted > 0)
    {
        put(app, f + 0x3c, s + 0xc);
        cpu.ebp = s + 0x26;
        do
        {
            if (half(app, s + 0x24) != 0)
            {
                cpu.ecx = at(app, f + 0x3c);
                cpu.ebx = reg32(wanted);
                cpu.eax = reg32(shalf(app, s + 0x24));
                cpu.edx = s + 0x26;
                if (!call(app, cpu, 0x529140))
                    return;
                cpu.ebx = ((cpu.ebx & 0xffff0000) | half(app, s + 0x24)) - cpu.eax;
                wanted -= i32(cpu.eax);
                putHalf(app, s + 0x24, reg16(cpu.ebx));
            }
            else if (s32(app, s + 0x18) + 0x1b < s32(app, s + 0x20))
            {
                cpu.edx = at(app, s + 0x10) + xaBlockBytes(cpu, at(app, s + 0x18));
                put(app, s, 0x1c);
                put(app, s + 8, cpu.edx);
                if (!call(app, cpu, kXaMono, {s}))
                    return;
                cpu.edx = at(app, s + 0x18) + 0x1c;
                wanted -= 0x1c;
                put(app, s + 0x18, cpu.edx);
            }
            else
            {
                const reg32 target = at(app, s + 0xc);
                put(app, f + 0x38, target);
                cpu.edx = at(app, s + 0x10) + xaBlockBytes(cpu, at(app, s + 0x18));
                put(app, s, 0x1c);
                put(app, s + 0xc, s + 0x26);
                put(app, s + 8, cpu.edx);
                if (!call(app, cpu, kXaMono, {s}))
                    return;
                put(app, s + 0x18, at(app, s + 0x18) + 0x1c);
                cpu.ebx = (cpu.ebx & 0xffff0000) | half(app, s + 0x20);
                cpu.eax = ((cpu.eax & 0xffff0000) | half(app, s + 0x18)) - cpu.ebx;
                cpu.edx = 0x1c - cpu.eax;
                putHalf(app, s + 0x24, reg16(cpu.edx));
                putHalf(app, s + 6, half(app, s + 0x94));
                cpu.eax = (cpu.eax & 0xffff0000) | half(app, s + 0x96);
                putHalf(app, s + 4, reg16(cpu.eax));
                cpu.ecx = cpu.edx + 1;
                putHalf(app, s + 0x24, reg16(cpu.ecx));
                cpu.eax = at(app, s + 0x1c);
                cpu.ecx = 0x1c;
                idiv(cpu, 0x1c);
                cpu.eax = reg32(mul(i32(cpu.eax), 0x1c));
                put(app, s + 0x18, cpu.eax);
                cpu.eax = at(app, s + 0x1c);
                idiv(cpu, 0x1c);
                if (cpu.edx != 0)
                {
                    put(app, s, cpu.ecx);
                    cpu.edx = at(app, s + 0x10) + xaBlockBytes(cpu, at(app, s + 0x18));
                    cpu.eax = f;
                    put(app, s + 8, cpu.edx);
                    put(app, s + 0xc, f);
                    if (!call(app, cpu, kXaMono, {s}))
                        return;
                    cpu.ebx = at(app, s + 0x18) + 0x1c;
                    cpu.edx = at(app, s + 0x1c);
                    const reg32 from = cpu.ebx - cpu.edx;
                    put(app, f + 0x40, from);
                    cpu.ecx = from;
                    cpu.eax = f + 2 * (0x1c - from);
                    put(app, s + 0x18, cpu.ebx);
                    cpu.edx = 0;
                    if (i32(from) > 0)
                        do
                        {
                            cpu.ecx = reg32(shalf(app, s + 0x24));
                            const reg16 w = half(app, cpu.eax);
                            putHalf(app, s + cpu.ecx * 2 + 0x26, w);
                            cpu.ebx = ((cpu.ebx & 0xffff0000) | half(app, s + 0x24)) + 1;
                            ++cpu.edx;
                            putHalf(app, s + 0x24, reg16(cpu.ebx));
                            cpu.ebx = at(app, f + 0x40);
                            cpu.eax += 2;
                        } while (i32(cpu.edx) < i32(cpu.ebx));
                }
                cpu.eax = at(app, f + 0x38);
                put(app, s + 0xc, cpu.eax);
            }
        } while (wanted > 0);
    }
    cpu.eax = reg32(wanted) * 2;
    put(app, s + 0xc, at(app, s + 0xc) + cpu.eax);
    while (wanted < 0)
    {
        cpu.eax = reg32(shalf(app, s + 0x24));
        cpu.edx = (at(app, s + 0xc) & 0xffff0000) | half(app, at(app, s + 0xc));
        putHalf(app, s + cpu.eax * 2 + 0x26, reg16(cpu.edx));
        put(app, s + 0xc, at(app, s + 0xc) + 2);
        cpu.ecx = ((cpu.ecx & 0xffff0000) | half(app, s + 0x24)) + 1;
        ++wanted;
        putHalf(app, s + 0x24, reg16(cpu.ecx));
    }
    cpu.eax = 1;
    cpu.ecx = kept.ecx;
    cpu.esi = kept.esi;
    cpu.edi = kept.edi;
    cpu.ebp = kept.ebp;
    cpu.esp = kept.esp + 4;
}

/* 0x529384: XA with an intro (eax the state -- xaLoopDecode's, +0x98 the
 * decoder's slot -- edx frames wanted, ebx where): the kept frames first,
 * then the intro's blocks up to the loop's start, what the last leaves over
 * kept; at the loop the slot handed to xaLoopDecode, its history saved for
 * it, and the rest of the frames asked of it.  1. */
void xaIntroDecode(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 f = kept.frame(4, 8);
    cpu.esp = f;
    const reg32 s = cpu.eax;
    i32 wanted = i32(cpu.edx);
    cpu.ecx = cpu.edx;
    cpu.esi = s;
    put(app, s + 0xc, cpu.ebx);
    const i32 held = shalf(app, s + 0x24);
    cpu.edx = reg32(held);
    if (held >= wanted)
    {
        cpu.ebx = 0;
        for (; i32(cpu.ebx) < wanted; ++cpu.ebx)
        {
            putHalf(app, at(app, s + 0xc), half(app, s + 0x26 + 2 * cpu.ebx));
            put(app, s + 0xc, at(app, s + 0xc) + 2);
        }
        cpu.edx = s + 2 * cpu.ebx;
        reg32 left = 0;
        for (; i32(cpu.ebx) < shalf(app, s + 0x24); ++cpu.ebx)
        {
            ++left;
            putHalf(app, s + 0x24 + 2 * left, half(app, cpu.edx + 0x26));
            cpu.edx += 2;
        }
        cpu.eax = 1;
        putHalf(app, s + 0x24, reg16(left));
        cpu.ecx = kept.ecx;
        cpu.esi = kept.esi;
        cpu.edi = kept.edi;
        cpu.ebp = kept.ebp;
        cpu.esp = kept.esp + 4;
        return;
    }
    for (cpu.ebx = 0; i32(cpu.ebx) < held; ++cpu.ebx)
    {
        putHalf(app, at(app, s + 0xc), half(app, s + 0x26 + 2 * cpu.ebx));
        put(app, s + 0xc, at(app, s + 0xc) + 2);
    }
    i32 rest = wanted - held;
    i32 n = s32(app, s + 0x1c) - s32(app, s + 0x18) - 0x1b;
    if (n > rest)
        n = rest;
    if (n < 0)
        n = 0;
    cpu.edi = reg32(n);
    cpu.ebp = reg32(rest);
    cpu.edx = at(app, s + 0x10) + xaBlockBytes(cpu, at(app, s + 0x18));
    put(app, s, reg32(n));
    put(app, s + 8, cpu.edx);
    if (!call(app, cpu, kXaMono, {s}))
        return;
    cpu.ecx = at(app, s + 0x18) + reg32(n);
    put(app, s + 0x18, cpu.ecx);
    cpu.ebx = cpu.ecx - at(app, s);
    put(app, s + 0x18, cpu.ebx);
    const i32 over = s32(app, s);
    cpu.ebx = 0;
    cpu.edx = 0;
    cpu.eax = reg32(over * 2);
    const reg32 from = at(app, s + 0xc);
    while (i32(cpu.eax) < 0)
    {
        cpu.ecx = (from & 0xffff0000) | half(app, from + cpu.eax);
        cpu.eax += 2;
        putHalf(app, s + cpu.edx + 0x26, reg16(cpu.ecx));
        ++cpu.ebx;
        cpu.ecx = reg32(over) + cpu.ebx;
        cpu.edx += 2;
    }
    rest -= n;
    cpu.ebp = at(app, s + 0xc) - cpu.edx;
    putHalf(app, s + 0x24, reg16(cpu.ebx));
    cpu.edx = at(app, s + 0x18);
    cpu.eax = at(app, s + 0x1c) - cpu.edx;
    put(app, s + 0xc, cpu.ebp);
    if (i32(cpu.eax) < 0x1c)
    {
        putHalf(app, s + 0x94, half(app, s + 6));
        putHalf(app, s + 0x96, half(app, s + 4));
        cpu.eax = at(app, s + 0x98);
        cpu.ecx = reg32(rest);
        put(app, cpu.eax, 0x5291a8);
        if (rest > 0)
        {
            cpu.edx = reg32(rest);
            cpu.eax = s;
            cpu.ebx = at(app, s + 0xc);
            if (!call(app, cpu, 0x5291a8))
                return;
        }
    }
    cpu.eax = 1;
    cpu.ecx = kept.ecx;
    cpu.esi = kept.esi;
    cpu.edi = kept.edi;
    cpu.ebp = kept.ebp;
    cpu.esp = kept.esp + 4;
}

/* 0x529590: XA streamed (eax the state -- +0x10 the chunk's data, +0x14 its
 * length, +0x18 the frame, +0x1c the frames kept and +0x1e them -- edx
 * frames wanted, ebx where): the kept frames, whole blocks of the chunk, the
 * block across its end; at its end the next chunk asked of the refill
 * ([0x5678b4]: eax and edx the data's and the length's slots), its first
 * eight bytes the decoder's history; none, and the rest is silence.  1; -1
 * with no chunk. */
void xaStreamDecode(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 f0 = kept.frame(3, 0x10);
    cpu.esp = f0;
    const reg32 s = cpu.eax;
    i32 wanted = i32(cpu.edx);
    cpu.edi = cpu.edx;
    cpu.edx = at(app, s + 0x10);
    cpu.esi = s;
    if (cpu.edx == 0)
    {
        cpu.eax = 0xffffffff;
        cpu.esi = kept.esi;
        cpu.edi = kept.edi;
        cpu.ebp = kept.ebp;
        cpu.esp = kept.esp + 4;
        return;
    }
    cpu.esp = f0 - 4;
    put(app, s + 0xc, cpu.ebx);
    if (wanted > 0)
    {
        cpu.ebp = s + 0xc;
        do
        {
            if (half(app, s + 0x1c) != 0)
            {
                cpu.edx = s + 0x1e;
                cpu.ecx = s + 0xc;
                cpu.eax = reg32(shalf(app, s + 0x1c));
                cpu.ebx = reg32(wanted);
                if (!call(app, cpu, 0x529140))
                    return;
                const reg32 copied = cpu.eax;
                cpu.ebx = ((cpu.ebx & 0xffff0000) | half(app, s + 0x1c)) - copied;
                wanted -= i32(copied);
                putHalf(app, s + 0x1c, reg16(cpu.ebx));
            }
            else if (s32(app, s + 0x18) + 0x1b < s32(app, s + 0x14))
            {
                cpu.ecx = at(app, s + 0x14);
                cpu.eax = cpu.ecx - at(app, s + 0x18);
                cpu.ebx = 0x1c;
                idiv(cpu, 0x1c);
                reg32 blocks = reg32(mul(i32(cpu.eax), 0x1c));
                if (wanted < i32(blocks))
                {
                    cpu.eax = reg32(wanted + 0x1b);
                    idiv(cpu, 0x1c);
                    blocks = reg32(mul(i32(cpu.eax), 0x1c));
                }
                put(app, s, blocks);
                cpu.eax = reg32(mul(s32(app, s + 0x18), 15));
                idiv(cpu, 0x1c);
                cpu.edx = at(app, s + 0x10) + cpu.eax;
                put(app, s + 8, cpu.edx);
                if (!call(app, cpu, kXaMono, {s}))
                    return;
                cpu.edx = at(app, s + 0x18) + blocks;
                cpu.eax = blocks;
                wanted -= i32(blocks);
                put(app, s + 0x18, cpu.edx);
            }
            else
            {
                if (at(app, s + 0x10) != 1 && s32(app, s + 0x14) > s32(app, s + 0x18))
                {
                    cpu.ebx = 0x1c;
                    cpu.eax = reg32(mul(s32(app, s + 0x18), 15));
                    idiv(cpu, 0x1c);
                    cpu.edx = at(app, s + 0x10) + cpu.eax;
                    put(app, s, 0x1c);
                    put(app, s + 8, cpu.edx);
                    if (!call(app, cpu, kXaMono, {s}))
                        return;
                    cpu.ebx = at(app, s + 0x18) + 0x1c;
                    cpu.edx = cpu.ebx - at(app, s + 0x14);
                    cpu.eax = 0x1c - cpu.edx;
                    cpu.edx += cpu.edx;
                    put(app, s + 0x18, cpu.ebx);
                    cpu.ecx = at(app, s + 0xc) - cpu.edx;
                    wanted -= i32(cpu.eax);
                    put(app, s + 0xc, cpu.ecx);
                }
                cpu.edx = s + 0x14;
                cpu.eax = s + 0x10;
                cpu.edi = reg32(wanted);
                if (!call(app, cpu, at(app, 0x5678b4)))
                    return;
                cpu.ebx = at(app, s + 0x10);
                if (cpu.ebx == 0)
                {
                    cpu.eax = at(app, s + 0xc);
                    cpu.ebx = reg32(wanted) * 2;
                    cpu.edx = 0;
                    if (!call(app, cpu, kFill))
                        return;
                    cpu.edx = at(app, s + 0xc) + reg32(wanted) * 2;
                    wanted = 0;
                    put(app, s + 0xc, cpu.edx);
                    break;
                }
                cpu.edx = (cpu.edx & 0xffff0000) | half(app, cpu.ebx);
                putHalf(app, s + 6, reg16(cpu.edx));
                putHalf(app, s + 4, half(app, cpu.ebx + 2));
                cpu.eax = at(app, s + 0x10) + 8;
                put(app, s + 0x18, 0);
                put(app, s + 0x10, cpu.eax);
            }
        } while (wanted > 0);
    }
    cpu.eax = reg32(wanted) * 2;
    put(app, s + 0xc, at(app, s + 0xc) + cpu.eax);
    while (wanted < 0)
    {
        cpu.eax = reg32(shalf(app, s + 0x1c));
        cpu.edx = (at(app, s + 0xc) & 0xffff0000) | half(app, at(app, s + 0xc));
        putHalf(app, s + cpu.eax * 2 + 0x1e, reg16(cpu.edx));
        cpu.ebx = at(app, s + 0xc) + 2;
        cpu.ecx = ((cpu.ecx & 0xffff0000) | half(app, s + 0x1c)) + 1;
        put(app, s + 0xc, cpu.ebx);
        ++wanted;
        putHalf(app, s + 0x1c, reg16(cpu.ecx));
    }
    cpu.eax = 1;
    cpu.ecx = kept.ecx;
    cpu.esi = kept.esi;
    cpu.edi = kept.edi;
    cpu.ebp = kept.ebp;
    cpu.esp = kept.esp + 4;
}

/* 0x529778 (stdcall, 4 words; edx the state, ecx the chunk's length):
 * XA streamed set up, its first chunk to come.  0x54, the state's size. */
void xaStreamSetup(App* app, CPU& cpu)
{
    const reg32 s = cpu.edx;
    put(app, s + 0x10, 1);
    put(app, s + 0x18, 0);
    putHalf(app, s + 0x1c, 0);
    putHalf(app, s + 6, 0);
    putHalf(app, s + 4, 0);
    put(app, s + 0x14, cpu.ecx);
    put(app, at(app, cpu.esp + 0xc), 0x529590);
    cpu.edx = at(app, cpu.esp + 0x10);
    cpu.eax = 0x54;
    put(app, cpu.edx, 0);
    cpu.esp += 4 + 0x10;
}

/* 0x5297c0: XA from a packet player (eax the state -- +0x10 the packet's
 * data, +0x14 its length, +0x18 the frame, +0x1c the player, +0x20 the
 * frames taken since the last release, +0x24 the frames kept and +0x26
 * them -- edx frames wanted, ebx where): the frames taken last time given
 * back (0x511998), the kept frames, the packet's whole blocks and the block
 * across its end; at its end the next packet (0x5118fc), its first eight
 * bytes the decoder's history; none, and the rest is silence -- what a block
 * left over kept.  The frames taken this time. */
void xaPacketDecode(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 f = kept.frame(4, 0xc);
    cpu.esp = f;
    const reg32 s = cpu.eax;
    cpu.esi = s;
    cpu.ebp = s;
    i32 wanted = i32(cpu.edx);
    cpu.edx = at(app, s + 0x20);
    put(app, s + 0xc, cpu.ebx);
    if (cpu.edx != 0)
    {
        cpu.eax = at(app, s + 0x1c);
        if (!call(app, cpu, 0x511998))
            return;
        put(app, cpu.esi + 0x20, 0);
    }
    cpu.edi = s + 0x14;
    while (wanted > 0)
    {
        if (half(app, s + 0x24) != 0)
        {
            cpu.ecx = s + 0xc;
            cpu.ebx = reg32(wanted);
            cpu.eax = reg32(shalf(app, s + 0x24));
            cpu.edx = s + 0x26;
            cpu.esi = reg32(wanted);
            if (!call(app, cpu, 0x529140))
                return;
            cpu.ecx = ((cpu.ecx & 0xffff0000) | half(app, s + 0x24)) - cpu.eax;
            cpu.edx = at(app, s + 0x20) + cpu.eax;
            cpu.esi -= cpu.eax;
            wanted = i32(cpu.esi);
            putHalf(app, s + 0x24, reg16(cpu.ecx));
            put(app, s + 0x20, cpu.edx);
            continue;
        }
        cpu.ebx = at(app, s + 0x14);
        if (s32(app, s + 0x18) + 0x1b < i32(cpu.ebx))
        {
            cpu.eax = cpu.ebx - at(app, s + 0x18);
            cpu.ecx = 0x1c;
            idiv(cpu, 0x1c);
            cpu.esi = reg32(mul(i32(cpu.eax), 0x1c));
            cpu.ebx = reg32(wanted);
            if (i32(cpu.esi) > wanted)
            {
                cpu.eax = cpu.ebx + 0x1b;
                idiv(cpu, 0x1c);
                cpu.esi = reg32(mul(i32(cpu.eax), 0x1c));
            }
            cpu.edx = at(app, s + 0x10) + xaBlockBytes(cpu, at(app, s + 0x18));
            put(app, s, cpu.esi);
            put(app, s + 8, cpu.edx);
            if (!call(app, cpu, kXaMono, {s}))
                return;
            cpu.edx = at(app, s + 0x18) + cpu.esi;
            cpu.ebx = at(app, s + 0x20) + cpu.esi;
            cpu.ecx = reg32(wanted) - cpu.esi;
            put(app, s + 0x18, cpu.edx);
            put(app, s + 0x20, cpu.ebx);
            wanted = i32(cpu.ecx);
            continue;
        }
        if (i32(cpu.ebx) > s32(app, s + 0x18))
        {
            cpu.edx = at(app, s + 0x10) + xaBlockBytes(cpu, at(app, s + 0x18));
            put(app, s, 0x1c);
            put(app, s + 8, cpu.edx);
            if (!call(app, cpu, kXaMono, {s}))
                return;
            cpu.edx = at(app, s + 0x18) + 0x1c;
            cpu.ecx = at(app, s + 0x14);
            cpu.esi = at(app, s + 0xc);
            put(app, s + 0x18, cpu.edx);
            cpu.eax = cpu.edx - cpu.ecx;
            cpu.edx = 0x1c - cpu.eax;
            cpu.eax += cpu.eax;
            cpu.ebx = reg32(wanted) - cpu.edx;
            cpu.esi -= cpu.eax;
            cpu.eax = at(app, s + 0x20) + cpu.edx;
            put(app, s + 0xc, cpu.esi);
            wanted = i32(cpu.ebx);
            put(app, s + 0x20, cpu.eax);
        }
        cpu.edx = s + 0x14;
        cpu.eax = at(app, s + 0x1c);
        if (!call(app, cpu, 0x5118fc))
            return;
        put(app, s + 0x10, cpu.eax);
        if (cpu.eax != 0)
        {
            cpu.edx = (cpu.edx & 0xffff0000) | half(app, cpu.eax);
            putHalf(app, s + 6, reg16(cpu.edx));
            putHalf(app, s + 4, half(app, cpu.eax + 2));
            cpu.eax = at(app, s + 0x10) + 8;
            put(app, s + 0x18, 0);
            put(app, s + 0x10, cpu.eax);
            continue;
        }
        cpu.ecx = reg32(wanted);
        if (wanted <= 0)
            continue;
        if (at(app, s + 0x20) != 0)
        {
            cpu.eax = at(app, s + 0xc);
            cpu.ebx = reg32(wanted) * 2;
            cpu.edx = 0;
            if (!call(app, cpu, kFill))
                return;
        }
        cpu.esi = at(app, s + 0xc) + reg32(wanted) * 2;
        wanted = 0;
        put(app, s + 0xc, cpu.esi);
    }
    cpu.edx = at(app, s + 0xc) + reg32(wanted) * 2;
    put(app, s + 0xc, cpu.edx);
    if (wanted < 0)
    {
        const reg32 over = reg32(-wanted);
        cpu.edi = s + 0x26 + reg32(shalf(app, s + 0x24)) * 2;
        cpu.esi = cpu.edx;
        repCopy(app, cpu, over * 2);
        cpu.ebx = ((cpu.ebx & 0xffff0000) | half(app, s + 0x24)) + over;
        putHalf(app, s + 0x24, reg16(cpu.ebx));
        put(app, s + 0x20, at(app, s + 0x20) - over);
    }
    cpu.eax = at(app, s + 0x20);
    leave(cpu, kept, kEcx | kEsi | kEdi);
}

/* 0x5299f4 (stdcall, 4 words; eax the sound, ecx the packet's length, edx
 * the state): XA from a packet player set up, its player by 0x52d160.
 * 0x5c, the state's size. */
void xaPacketSetup(App* app, CPU& cpu)
{
    if (!call(app, cpu, 0x52d160))
        return;
    const reg32 s = cpu.edx;
    put(app, s + 0x10, 0);
    put(app, s + 0x18, 0);
    putHalf(app, s + 0x24, 0);
    putHalf(app, s + 6, 0);
    putHalf(app, s + 4, 0);
    put(app, s + 0x20, 0);
    put(app, s + 0x1c, cpu.eax);
    put(app, s + 0x14, cpu.ecx);
    put(app, at(app, cpu.esp + 0xc), 0x5297c0);
    cpu.eax = at(app, cpu.esp + 0x10);
    put(app, cpu.eax, 0);
    cpu.eax = 0x5c;
    cpu.esp += 4 + 0x10;
}

namespace
{

constexpr reg32 kXaStereo = 0x52d250;  // mmx::xaStereo (cdecl: the state): [s] frames from [s+0xc] to [s+0x10]

/* The stereo XA decoders' block's place: frame * 30 / 28 (30 bytes a block
 * of 28 frames), cdq; idiv as the code has it. */
reg32 xaStereoBlockBytes(CPU& cpu, reg32 frame)
{
    cpu.eax = frame * 30;
    cpu.ecx = 0x1c;
    idiv(cpu, 0x1c);
    return cpu.eax;
}

}  // namespace

/* 0x529a50 (eax the state): a stereo XA sound's frames played so far. */
void xaStereoPlayed(App* app, CPU& cpu)
{
    cpu.eax = at(app, cpu.eax + 0x1c);
    cpu.esp += 4;
}

/* 0x529a54: stereo XA played once (eax the state -- +0x10 where, +0x14 the
 * data, +0x18 the length, +0x1c the frame, +0x20 the samples kept and +0x24
 * them -- edx frames wanted, ebx where): xaOnceDecode's, two samples a
 * frame by mmx::xaStereo; what is left over, the rest of a block.  1; -1 at
 * its end. */
void xaStereoOnceDecode(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 f = kept.frame(4, 4);
    cpu.esp = f;
    const reg32 s = cpu.eax;
    i32 wanted = i32(cpu.edx);
    cpu.edx = cpu.ebx;
    cpu.ecx = at(app, s + 0x1c);
    cpu.edi = at(app, s + 0x18);
    cpu.ebx = s;
    if (i32(cpu.ecx) >= i32(cpu.edi))
    {
        cpu.eax = 0xffffffff;
        cpu.ecx = kept.ecx;
        cpu.edi = kept.edi;
        cpu.esp = kept.esp + 4;
        return;
    }
    put(app, s + 0x10, cpu.edx);
    const i32 held = shalf(app, s + 0x20);
    if (wanted <= (held >> 1))
    {
        const i32 samples = wanted * 2;
        i32 i = 0;
        for (; i < samples; ++i)
        {
            putHalf(app, at(app, s + 0x10), half(app, s + 0x24 + 2 * i));
            put(app, s + 0x10, at(app, s + 0x10) + 2);
        }
        reg32 left = 0;
        for (; i < shalf(app, s + 0x20); ++i)
        {
            ++left;
            putHalf(app, s + 0x22 + 2 * left, half(app, s + 0x24 + 2 * i));
        }
        cpu.edx = reg32(i);
        putHalf(app, s + 0x20, reg16(left));
        cpu.eax = 1;
        cpu.ecx = kept.ecx;
        cpu.edi = kept.edi;
        cpu.esp = kept.esp + 4;
        return;
    }
    for (i32 i = 0; i < held; ++i)
    {
        putHalf(app, at(app, s + 0x10), half(app, s + 0x24 + 2 * i));
        put(app, s + 0x10, at(app, s + 0x10) + 2);
    }
    i32 rest = wanted - (held >> 1);
    i32 left = s32(app, s + 0x18) - s32(app, s + 0x1c);
    if (left < 0)
        left = 0;
    const i32 n = rest >= left ? left : rest;
    put(app, s, reg32(n));
    cpu.edx = at(app, s + 0x14) + xaStereoBlockBytes(cpu, at(app, s + 0x1c));
    put(app, s + 0xc, cpu.edx);
    cpu.esi = reg32(rest);
    cpu.ebp = reg32(left);
    if (!call(app, cpu, kXaStereo, {s}))
        return;
    cpu.ecx = at(app, s + 0x1c) + reg32(n) - at(app, s);
    put(app, s + 0x1c, cpu.ecx);
    if (left == n)
    {
        i32 silence = (rest - n - i32(cpu.ecx - at(app, s + 0x18))) * 2;
        cpu.edx = at(app, s + 0x18);
        for (; silence > 0; --silence)
        {
            cpu.edx = 0;
            putHalf(app, at(app, s + 0x10), 0);
            put(app, s + 0x10, at(app, s + 0x10) + 2);
        }
    }
    else
    {
        cpu.eax = reg32(rest);
        idiv(cpu, 0x1c);
        i32 over = -(0x1c - i32(cpu.edx));
        if (over == -0x1c)
            over = 0;
        over *= 2;
        cpu.edx = 0;
        if (over < 0)
        {
            const reg32 from = at(app, s + 0x10);
            for (i32 k = over; k < 0; ++k)
            {
                ++cpu.edx;
                putHalf(app, s + 0x22 + 2 * cpu.edx, half(app, from + 2 * k));
            }
        }
        putHalf(app, s + 0x20, reg16(cpu.edx));
    }
    cpu.eax = 1;
    cpu.ecx = kept.ecx;
    cpu.esi = kept.esi;
    cpu.edi = kept.edi;
    cpu.ebp = kept.ebp;
    cpu.esp = kept.esp + 4;
}

/* 0x529c2c (stdcall, 4 words; edx the state, ebx the data, ecx the length):
 * stereo XA played once set up.  0x90, the state's size. */
void xaStereoOnceSetup(App* app, CPU& cpu)
{
    const reg32 s = cpu.edx;
    put(app, s + 0x1c, 0);
    putHalf(app, s + 0x20, 0);
    putHalf(app, s + 6, 0);
    putHalf(app, s + 4, 0);
    putHalf(app, s + 0xa, 0);
    putHalf(app, s + 8, 0);
    put(app, s + 0x14, cpu.ebx);
    put(app, s + 0x18, cpu.ecx);
    put(app, at(app, cpu.esp + 0xc), 0x529a54);
    cpu.edx = at(app, cpu.esp + 0x10);
    cpu.eax = 0x90;
    put(app, cpu.edx, 0x529a50);
    cpu.esp += 4 + 0x10;
}

/* 0x529c80: xaKeptCopy's for stereo -- frames of two samples. */
void xaStereoKeptCopy(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const i32 there = i32(cpu.eax);
    const reg32 from = cpu.edx, slot = cpu.ecx;
    cpu.edx = at(app, slot);
    i32 copied = i32(cpu.ebx);
    if (there < copied)
        copied = there;
    i32 i = 0;
    if (copied > 0)
    {
        cpu.ecx = from;
        for (; i < copied; ++i)
        {
            cpu.edx += 2;
            putHalf(app, cpu.edx - 2, half(app, cpu.ecx));
            cpu.ecx += 4;
            cpu.edx += 2;
            const reg16 w = half(app, cpu.ecx - 2);
            cpu.ebx = (cpu.ebx & 0xffff0000) | w;
            putHalf(app, cpu.edx - 2, w);
        }
    }
    if (i < there)
    {
        cpu.ecx = from;
        cpu.ebx = from + 4 * reg32(i);
        for (; i < there; ++i)
        {
            putHalf(app, cpu.ecx, half(app, cpu.ebx));
            cpu.ebx += 4;
            cpu.ecx += 4;
            putHalf(app, cpu.ecx - 2, half(app, cpu.ebx - 2));
        }
    }
    put(app, slot, cpu.edx);
    cpu.eax = reg32(copied);
    cpu.esp = kept.esp + 4;
}

/* 0x529cfc: stereo XA looped (eax the state -- +0x10 where, +0x14 the data,
 * +0x1c the frame, +0x20 the loop's start, +0x24 the length, +0x28 the
 * frames kept and +0x2c them, +0x108.. the decoder's history at the loop --
 * edx frames wanted, ebx where): xaLoopDecode's, two samples a frame by
 * mmx::xaStereo.  1. */
void xaStereoLoopDecode(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 f = kept.frame(4, 0x7c);
    cpu.esp = f;
    const reg32 s = cpu.eax;
    i32 wanted = i32(cpu.edx);
    cpu.edi = cpu.edx;
    cpu.esi = s;
    put(app, s + 0x10, cpu.ebx);
    if (wanted > 0)
    {
        put(app, f + 0x74, s + 0x10);
        cpu.ebp = s + 0x2c;
        do
        {
            if (half(app, s + 0x28) != 0)
            {
                cpu.ecx = s + 0x10;
                cpu.ebx = reg32(wanted);
                cpu.eax = reg32(shalf(app, s + 0x28));
                cpu.edx = s + 0x2c;
                if (!call(app, cpu, 0x529c80))
                    return;
                cpu.ebx = ((cpu.ebx & 0xffff0000) | half(app, s + 0x28)) - cpu.eax;
                wanted -= i32(cpu.eax);
                putHalf(app, s + 0x28, reg16(cpu.ebx));
            }
            else if (s32(app, s + 0x1c) + 0x1b < s32(app, s + 0x24))
            {
                cpu.edx = at(app, s + 0x14) + xaStereoBlockBytes(cpu, at(app, s + 0x1c));
                put(app, s, 0x1c);
                put(app, s + 0xc, cpu.edx);
                if (!call(app, cpu, kXaStereo, {s}))
                    return;
                cpu.eax = at(app, s + 0x1c) + 0x1c;
                wanted -= 0x1c;
                put(app, s + 0x1c, cpu.eax);
            }
            else
            {
                const reg32 target = at(app, s + 0x10);
                put(app, f + 0x70, target);
                cpu.edx = at(app, s + 0x14) + xaStereoBlockBytes(cpu, at(app, s + 0x1c));
                put(app, s, 0x1c);
                put(app, s + 0x10, s + 0x2c);
                put(app, s + 0xc, cpu.edx);
                if (!call(app, cpu, kXaStereo, {s}))
                    return;
                put(app, s + 0x1c, at(app, s + 0x1c) + 0x1c);
                cpu.ebx = (cpu.ebx & 0xffff0000) | half(app, s + 0x24);
                cpu.eax = ((cpu.eax & 0xffff0000) | half(app, s + 0x1c)) - cpu.ebx;
                cpu.edx = 0x1c - cpu.eax;
                putHalf(app, s + 0x28, reg16(cpu.edx));
                putHalf(app, s + 6, half(app, s + 0x108));
                putHalf(app, s + 4, half(app, s + 0x10a));
                putHalf(app, s + 0xa, half(app, s + 0x10c));
                cpu.eax = (cpu.eax & 0xffff0000) | half(app, s + 0x10e);
                putHalf(app, s + 8, reg16(cpu.eax));
                cpu.ecx = cpu.edx + 1;
                putHalf(app, s + 0x28, reg16(cpu.ecx));
                cpu.eax = at(app, s + 0x20);
                cpu.ecx = 0x1c;
                idiv(cpu, 0x1c);
                cpu.eax = reg32(mul(i32(cpu.eax), 0x1c));
                put(app, s + 0x1c, cpu.eax);
                cpu.eax = at(app, s + 0x20);
                idiv(cpu, 0x1c);
                if (cpu.edx != 0)
                {
                    put(app, s, cpu.ecx);
                    cpu.edx = at(app, s + 0x14) + xaStereoBlockBytes(cpu, at(app, s + 0x1c));
                    cpu.eax = f;
                    put(app, s + 0xc, cpu.edx);
                    put(app, s + 0x10, f);
                    if (!call(app, cpu, kXaStereo, {s}))
                        return;
                    cpu.ebx = at(app, s + 0x1c) + 0x1c;
                    const reg32 from = cpu.ebx - at(app, s + 0x20);
                    put(app, f + 0x78, from);
                    cpu.eax = f + 4 * (0x1c - from);
                    put(app, s + 0x1c, cpu.ebx);
                    cpu.ecx = from;
                    cpu.edx = 0;
                    if (i32(from) > 0)
                        do
                        {
                            cpu.ecx = reg32(shalf(app, s + 0x28));
                            cpu.ebx = (cpu.ebx & 0xffff0000) | half(app, cpu.eax);
                            putHalf(app, s + cpu.ecx * 4 + 0x2c, reg16(cpu.ebx));
                            cpu.ecx = reg32(shalf(app, s + 0x28));
                            cpu.ebx = (cpu.ebx & 0xffff0000) | half(app, cpu.eax + 2);
                            putHalf(app, s + cpu.ecx * 4 + 0x2e, reg16(cpu.ebx));
                            cpu.eax += 4;
                            cpu.ebx = ((cpu.ebx & 0xffff0000) | half(app, s + 0x28)) + 1;
                            ++cpu.edx;
                            cpu.ecx = at(app, f + 0x78);
                            putHalf(app, s + 0x28, reg16(cpu.ebx));
                        } while (i32(cpu.edx) < i32(cpu.ecx));
                }
                cpu.eax = at(app, f + 0x70);
                put(app, s + 0x10, cpu.eax);
            }
        } while (wanted > 0);
    }
    cpu.eax = reg32(wanted) * 4;
    put(app, s + 0x10, at(app, s + 0x10) + cpu.eax);
    while (wanted < 0)
    {
        cpu.eax = reg32(shalf(app, s + 0x28)) << 2;
        cpu.edx = at(app, s + 0x10);
        cpu.ecx = s + cpu.eax;
        putHalf(app, cpu.ecx + 0x2c, half(app, cpu.edx));
        cpu.edx = reg32(shalf(app, s + 0x28));
        cpu.eax = (at(app, s + 0x10) & 0xffff0000) | half(app, at(app, s + 0x10) + 2);
        putHalf(app, s + cpu.edx * 4 + 0x2e, reg16(cpu.eax));
        cpu.edx = at(app, s + 0x10) + 4;
        cpu.ecx = ((cpu.ecx & 0xffff0000) | half(app, s + 0x28)) + 1;
        put(app, s + 0x10, cpu.edx);
        ++wanted;
        putHalf(app, s + 0x28, reg16(cpu.ecx));
    }
    cpu.eax = 1;
    cpu.ecx = kept.ecx;
    cpu.esi = kept.esi;
    cpu.edi = kept.edi;
    cpu.ebp = kept.ebp;
    cpu.esp = kept.esp + 4;
}

/* 0x529f24: stereo XA with an intro (eax the state -- xaStereoLoopDecode's,
 * +0x110 the decoder's slot -- edx frames wanted, ebx where): xaIntroDecode's,
 * two samples a frame.  1 (edx 1 too). */
void xaStereoIntroDecode(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 f = kept.frame(4, 0xc);
    cpu.esp = f;
    const reg32 s = cpu.eax;
    i32 wanted = i32(cpu.edx);
    cpu.ecx = cpu.edx;
    cpu.esi = s;
    put(app, s + 0x10, cpu.ebx);
    const i32 held = shalf(app, s + 0x28);
    const auto copyFrame = [&](reg32 i) {
        const reg32 to = at(app, s + 0x10);
        putHalf(app, to, half(app, s + 0x2c + 4 * i));
        putHalf(app, at(app, s + 0x10) + 2, half(app, s + 0x2e + 4 * i));
        put(app, s + 0x10, at(app, s + 0x10) + 4);
    };
    if (held >= wanted)
    {
        cpu.ebx = 0;
        for (; i32(cpu.ebx) < wanted; ++cpu.ebx)
            copyFrame(cpu.ebx);
        reg32 left = 0;
        cpu.edx = s + 4 * cpu.ebx;
        for (; i32(cpu.ebx) < shalf(app, s + 0x28); ++cpu.ebx)
        {
            putHalf(app, s + 0x2c + 4 * left, half(app, cpu.edx + 0x2c));
            putHalf(app, s + 0x2e + 4 * left, half(app, cpu.edx + 0x2e));
            ++left;
            cpu.edx += 4;
        }
        putHalf(app, s + 0x28, reg16(left));
        cpu.eax = 1;
        cpu.edx = 1;
        cpu.ecx = kept.ecx;
        cpu.esi = kept.esi;
        cpu.edi = kept.edi;
        cpu.ebp = kept.ebp;
        cpu.esp = kept.esp + 4;
        return;
    }
    for (cpu.ebx = 0; i32(cpu.ebx) < held; ++cpu.ebx)
        copyFrame(cpu.ebx);
    i32 rest = wanted - held;
    i32 n = s32(app, s + 0x20) - s32(app, s + 0x1c) - 0x1b;
    if (n > rest)
        n = rest;
    if (n < 0)
        n = 0;
    put(app, s, reg32(n));
    cpu.edx = at(app, s + 0x14) + xaStereoBlockBytes(cpu, at(app, s + 0x1c));
    put(app, s + 0xc, cpu.edx);
    if (!call(app, cpu, kXaStereo, {s}))
        return;
    cpu.ebp = at(app, s + 0x1c) + reg32(n);
    put(app, s + 0x1c, cpu.ebp);
    cpu.edx = cpu.ebp - at(app, s);
    put(app, s + 0x1c, cpu.edx);
    const i32 over = s32(app, s);
    cpu.ebx = 0;
    cpu.edx = 0;
    cpu.eax = reg32(over * 4);
    while (i32(cpu.eax) < 0)
    {
        const reg32 to = s + cpu.edx;
        putHalf(app, to + 0x2c, half(app, at(app, s + 0x10) + cpu.eax));
        putHalf(app, to + 0x2e, half(app, at(app, s + 0x10) + cpu.eax + 2));
        ++cpu.ebx;
        cpu.eax += 4;
        cpu.edx += 4;
    }
    rest -= n;
    cpu.ebp = at(app, s + 0x10) - cpu.edx;
    putHalf(app, s + 0x28, reg16(cpu.ebx));
    cpu.edx = reg32(rest);
    put(app, s + 0x10, cpu.ebp);
    cpu.eax = at(app, s + 0x20) - at(app, s + 0x1c);
    cpu.ecx = at(app, s + 0x1c);
    if (i32(cpu.eax) < 0x1c)
    {
        putHalf(app, s + 0x108, half(app, s + 6));
        putHalf(app, s + 0x10a, half(app, s + 4));
        putHalf(app, s + 0x10c, half(app, s + 0xa));
        putHalf(app, s + 0x10e, half(app, s + 8));
        cpu.eax = at(app, s + 0x110);
        put(app, cpu.eax, 0x529cfc);
        if (rest > 0)
        {
            cpu.eax = s;
            cpu.ebx = at(app, s + 0x10);
            if (!call(app, cpu, 0x529cfc))
                return;
        }
    }
    cpu.eax = 1;
    cpu.edx = 1;
    cpu.ecx = kept.ecx;
    cpu.esi = kept.esi;
    cpu.edi = kept.edi;
    cpu.ebp = kept.ebp;
    cpu.esp = kept.esp + 4;
}

/* 0x52a144 (stdcall, 4 words; edx the state, ebx the data, ecx its bytes;
 * the loop's start, the length, the decoder's slot, the second function's):
 * stereo XA with an intro set up.  0x114, the state's size. */
void xaStereoIntroSetup(App* app, CPU& cpu)
{
    const reg32 s = cpu.edx;
    put(app, s + 0x1c, 0);
    putHalf(app, s + 0x28, 0);
    putHalf(app, s + 6, 0);
    putHalf(app, s + 4, 0);
    putHalf(app, s + 0xa, 0);
    putHalf(app, s + 8, 0);
    put(app, s + 0x14, cpu.ebx);
    put(app, s + 0x18, cpu.ecx);
    put(app, s + 0x20, at(app, cpu.esp + 4));
    put(app, s + 0x24, at(app, cpu.esp + 8));
    cpu.ecx = at(app, cpu.esp + 0xc);
    put(app, s + 0x110, cpu.ecx);
    cpu.edx = at(app, cpu.esp + 0x10);
    put(app, cpu.ecx, 0x529f24);
    cpu.eax = 0x114;
    put(app, cpu.edx, 0);
    cpu.esp += 4 + 0x10;
}

/* 0x52a1a0: stereo XA streamed from memory (eax the state -- +0x10 where,
 * +0x14 the chunk's data, +0x18 its length, +0x1c the frame, +0x20 the
 * frames kept and +0x24 them -- edx frames wanted, ebx where):
 * xaStreamDecode's, two samples a frame, the history four words.  1; -1
 * with no chunk. */
void xaStereoStreamDecode(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 f0 = kept.frame(3, 0xc);
    cpu.esp = f0;
    const reg32 s = cpu.eax;
    i32 wanted = i32(cpu.edx);
    cpu.edi = cpu.edx;
    cpu.edx = at(app, s + 0x14);
    cpu.esi = s;
    if (cpu.edx == 0)
    {
        cpu.eax = 0xffffffff;
        cpu.esi = kept.esi;
        cpu.edi = kept.edi;
        cpu.ebp = kept.ebp;
        cpu.esp = kept.esp + 4;
        return;
    }
    const reg32 f = f0 - 4;
    cpu.esp = f;
    put(app, s + 0x10, cpu.ebx);
    if (wanted > 0)
    {
        cpu.ebp = s + 0x14;
        do
        {
            cpu.ebx = at(app, s + 0x20);
            if (cpu.ebx != 0)
            {
                cpu.ecx = s + 0x10;
                cpu.edx = s + 0x24;
                cpu.eax = cpu.ebx;
                cpu.ebx = reg32(wanted);
                if (!call(app, cpu, 0x529c80))
                    return;
                cpu.edx = at(app, s + 0x20) - cpu.eax;
                wanted -= i32(cpu.eax);
                put(app, s + 0x20, cpu.edx);
                continue;
            }
            if (s32(app, s + 0x1c) + 0x1b < s32(app, s + 0x18))
            {
                cpu.ebx = 0x1c;
                cpu.eax = at(app, s + 0x1c) * 30;
                idiv(cpu, 0x1c);
                cpu.edx = at(app, s + 0x14) + cpu.eax;
                put(app, s, 0x1c);
                put(app, s + 0xc, cpu.edx);
                if (!call(app, cpu, kXaStereo, {s}))
                    return;
                cpu.ebx = at(app, s + 0x1c) + 0x1c;
                wanted -= 0x1c;
                put(app, s + 0x1c, cpu.ebx);
                continue;
            }
            if (at(app, s + 0x14) != 1)
            {
                cpu.ebx = 0x1c;
                cpu.eax = at(app, s + 0x1c) * 30;
                idiv(cpu, 0x1c);
                cpu.edx = at(app, s + 0x14) + cpu.eax;
                put(app, s, 0x1c);
                put(app, s + 0xc, cpu.edx);
                if (!call(app, cpu, kXaStereo, {s}))
                    return;
                cpu.eax = at(app, s + 0x1c) + cpu.ebx;
                cpu.edx = at(app, s + 0x18);
                put(app, s + 0x1c, cpu.eax);
                cpu.eax -= cpu.edx;
                cpu.edx = cpu.ebx - cpu.eax;
                cpu.ecx = at(app, s + 0x10);
                cpu.eax <<= 2;
                cpu.ecx -= cpu.eax;
                wanted -= i32(cpu.edx);
                put(app, s + 0x10, cpu.ecx);
            }
            cpu.edx = s + 0x18;
            cpu.eax = s + 0x14;
            cpu.edi = reg32(wanted);
            if (!call(app, cpu, at(app, 0x5678b4)))
                return;
            cpu.ebx = at(app, s + 0x14);
            if (cpu.ebx == 0)
            {
                wanted *= 2;
                for (; wanted > 0; --wanted)
                {
                    putHalf(app, at(app, s + 0x10), 0);
                    put(app, s + 0x10, at(app, s + 0x10) + 2);
                }
                continue;
            }
            putHalf(app, s + 6, half(app, cpu.ebx));
            putHalf(app, s + 4, half(app, cpu.ebx + 2));
            cpu.edx = (cpu.edx & 0xffff0000) | half(app, cpu.ebx + 4);
            putHalf(app, s + 0xa, reg16(cpu.edx));
            cpu.eax = (cpu.eax & 0xffff0000) | half(app, cpu.ebx + 6);
            putHalf(app, s + 8, reg16(cpu.eax));
            cpu.eax = at(app, s + 0x14) + 8;
            put(app, s + 0x1c, 0);
            put(app, s + 0x14, cpu.eax);
        } while (wanted > 0);
    }
    cpu.eax = reg32(wanted) * 4;
    put(app, s + 0x10, at(app, s + 0x10) + cpu.eax);
    while (wanted < 0)
    {
        cpu.edx = at(app, s + 0x20);
        cpu.eax = (at(app, s + 0x10) & 0xffff0000) | half(app, at(app, s + 0x10));
        putHalf(app, s + cpu.edx * 4 + 0x24, reg16(cpu.eax));
        cpu.edx = at(app, s + 0x20);
        cpu.eax = (at(app, s + 0x10) & 0xffff0000) | half(app, at(app, s + 0x10) + 2);
        putHalf(app, s + cpu.edx * 4 + 0x26, reg16(cpu.eax));
        cpu.ecx = at(app, s + 0x10) + 4;
        cpu.ebx = at(app, s + 0x20) + 1;
        put(app, s + 0x10, cpu.ecx);
        ++wanted;
        put(app, s + 0x20, cpu.ebx);
    }
    cpu.eax = 1;
    cpu.ecx = kept.ecx;
    cpu.esi = kept.esi;
    cpu.edi = kept.edi;
    cpu.ebp = kept.ebp;
    cpu.esp = kept.esp + 4;
}

/* 0x52a3a0: stereo XA from a packet player (eax the state -- +0x10 where,
 * +0x14 the packet's data, +0x18 its length, +0x1c the frame, +0x20 the
 * frames kept and +0x2c them, +0x24 the player, +0x28 the frames taken since
 * the last release -- edx frames wanted, ebx where): xaPacketDecode's, two
 * samples a frame.  The frames taken this time. */
void xaStereoPacketDecode(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 f = kept.frame(4, 8);
    cpu.esp = f;
    const reg32 s = cpu.eax;
    cpu.esi = s;
    cpu.ebp = s;
    i32 wanted = i32(cpu.edx);
    cpu.edx = at(app, s + 0x28);
    put(app, s + 0x10, cpu.ebx);
    if (cpu.edx != 0)
    {
        cpu.eax = at(app, s + 0x24);
        if (!call(app, cpu, 0x511998))
            return;
        put(app, cpu.esi + 0x28, 0);
    }
    cpu.edi = s + 0x10;
    cpu.esi = s + 0x18;
    while (wanted > 0)
    {
        cpu.ebx = at(app, s + 0x20);
        if (cpu.ebx != 0)
        {
            cpu.edx = s + 0x2c;
            cpu.eax = cpu.ebx;
            cpu.ecx = s + 0x10;
            cpu.ebx = reg32(wanted);
            if (!call(app, cpu, 0x529c80))
                return;
            cpu.ebx = reg32(wanted) - cpu.eax;
            cpu.ecx = at(app, s + 0x20) - cpu.eax;
            cpu.edx = at(app, s + 0x28) + cpu.eax;
            put(app, s + 0x20, cpu.ecx);
            wanted = i32(cpu.ebx);
            put(app, s + 0x28, cpu.edx);
            continue;
        }
        if (s32(app, s + 0x1c) + 0x1b < s32(app, s + 0x18))
        {
            cpu.edx = at(app, s + 0x14) + xaStereoBlockBytes(cpu, at(app, s + 0x1c));
            put(app, s, 0x1c);
            put(app, s + 0xc, cpu.edx);
            if (!call(app, cpu, kXaStereo, {s}))
                return;
            cpu.ebx = at(app, s + 0x1c) + 0x1c;
            cpu.edx = at(app, s + 0x28) + 0x1c;
            cpu.eax = reg32(wanted) - 0x1c;
            put(app, s + 0x1c, cpu.ebx);
            put(app, s + 0x28, cpu.edx);
            wanted = i32(cpu.eax);
            continue;
        }
        if (at(app, s + 0x14) != 0)
        {
            cpu.edx = at(app, s + 0x14) + xaStereoBlockBytes(cpu, at(app, s + 0x1c));
            put(app, s, 0x1c);
            put(app, s + 0xc, cpu.edx);
            if (!call(app, cpu, kXaStereo, {s}))
                return;
            cpu.eax = at(app, s + 0x1c) + 0x1c;
            put(app, s + 0x1c, cpu.eax);
            cpu.edx = cpu.eax - at(app, s + 0x18);
            cpu.ebx = at(app, s + 0x10);
            cpu.eax = 0x1c - cpu.edx;
            cpu.ecx = reg32(wanted) - cpu.eax;
            cpu.ebx -= cpu.edx << 2;
            cpu.edx = at(app, s + 0x28) + cpu.eax;
            put(app, s + 0x10, cpu.ebx);
            wanted = i32(cpu.ecx);
            put(app, s + 0x28, cpu.edx);
        }
        cpu.edx = s + 0x18;
        cpu.eax = at(app, s + 0x24);
        if (!call(app, cpu, 0x5118fc))
            return;
        put(app, s + 0x14, cpu.eax);
        if (cpu.eax != 0)
        {
            cpu.edx = cpu.eax;
            putHalf(app, s + 6, half(app, cpu.edx));
            putHalf(app, s + 4, half(app, cpu.edx + 2));
            putHalf(app, s + 0xa, half(app, cpu.edx + 4));
            cpu.eax = (cpu.eax & 0xffff0000) | half(app, cpu.edx + 6);
            putHalf(app, s + 8, reg16(cpu.eax));
            cpu.eax = at(app, s + 0x14) + 8;
            put(app, s + 0x1c, 0);
            put(app, s + 0x14, cpu.eax);
            continue;
        }
        cpu.ebx = reg32(wanted);
        if (wanted <= 0)
            continue;
        if (at(app, s + 0x28) != 0)
        {
            cpu.ebx <<= 2;
            cpu.eax = at(app, s + 0x10);
            cpu.edx = 0;
            if (!call(app, cpu, kFill))
                return;
        }
        cpu.edi = at(app, s + 0x10) + (reg32(wanted) << 2);
        cpu.eax = 0;
        put(app, s + 0x10, cpu.edi);
        wanted = 0;
    }
    cpu.edx = at(app, s + 0x10) + (reg32(wanted) << 2);
    put(app, s + 0x10, cpu.edx);
    if (wanted < 0)
    {
        const reg32 over = reg32(-wanted);
        cpu.edi = s + 0x2c + (at(app, s + 0x20) << 2);
        cpu.esi = cpu.edx;
        repCopy(app, cpu, over * 4);
        put(app, s + 0x20, at(app, s + 0x20) + over);
        put(app, s + 0x28, at(app, s + 0x28) - over);
    }
    cpu.eax = at(app, s + 0x28);
    leave(cpu, kept, kEcx | kEsi | kEdi);
}

/* 0x52a610 (eax the state): a frame-coded sound's frames played so far. */
void framesPlayedCoded(App* app, CPU& cpu)
{
    cpu.eax = at(app, cpu.eax + 0xd4c);
    cpu.esp += 4;
}

/* 0x52a618 (eax the decoded samples as dwords, edx where, ebx how many):
 * each to 16 bits, clipped by its low 17 bits as the code tests them. */
void codedToWords(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 from = cpu.eax, count = cpu.ebx;
    cpu.eax = cpu.edx;
    if (i32(count) > 0)
    {
        cpu.edx = from;
        cpu.ebx = cpu.eax;
        for (reg32 i = 0; i32(i) < i32(count); ++i)
        {
            cpu.eax = at(app, cpu.edx) & 0x1ffff;
            if (cpu.eax > 0x7fff && cpu.eax < 0x18000)
                cpu.eax = cpu.eax >= 0x10000 ? 0x8000 : 0x7fff;
            cpu.ebx += 2;
            cpu.edx += 4;
            putHalf(app, cpu.ebx - 2, reg16(cpu.eax));
        }
    }
    cpu.ecx = kept.ecx;
    cpu.esp = kept.esp + 4;
}

/* 0x52a668: a frame-coded sound (eax the state -- +0x684 the decoded frame
 * of 0x1b0 samples as dwords, +0xd44 the length, +0xd48 the samples of the
 * frame left, +0xd4c the frames played -- edx frames wanted, ebx where):
 * what is left of the frame first, then frame after frame by 0x52df80;
 * past the end, silence.  1; -1 at its end. */
void codedDecode(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 f = kept.frame(4, 0xc);
    cpu.esp = f;
    const reg32 s = cpu.eax;
    i32 wanted = i32(cpu.edx);
    cpu.ecx = cpu.ebx;
    cpu.edi = s;
    const reg32 played = at(app, s + 0xd4c);
    cpu.edx = at(app, s + 0xd44);
    if (played >= cpu.edx)
    {
        cpu.eax = 0xffffffff;
        cpu.ecx = kept.ecx;
        cpu.edi = kept.edi;
        cpu.esp = kept.esp + 4;
        return;
    }
    cpu.ebx = played + reg32(wanted);
    cpu.edx = at(app, s + 0xd44);
    i32 over = i32(cpu.ebx - cpu.edx);
    put(app, s + 0xd4c, cpu.ebx);
    if (over > 0)
        wanted -= over;
    else
        over = 0;
    put(app, f, reg32(over));
    const reg32 frame = s + 0x684;
    put(app, f + 4, frame);
    const auto copy = [&](reg32 n) {
        cpu.eax = frame + ((0x1b0 - at(app, s + 0xd48)) << 2);
        cpu.edx = cpu.ecx;
        cpu.ebx = n;
        cpu.esi = n;
        cpu.ebp = reg32(wanted);
        if (!call(app, cpu, 0x52a618))
            return false;
        cpu.ecx += n * 2;
        cpu.eax = at(app, s + 0xd48) - n;
        wanted -= i32(n);
        put(app, s + 0xd48, cpu.eax);
        return true;
    };
    reg32 n = at(app, s + 0xd48);
    if (wanted < i32(n))
        n = reg32(wanted);
    if (!copy(n))
        return;
    if (wanted > 0)
    {
        put(app, f + 8, frame);
        do
        {
            cpu.edx = 1;
            cpu.eax = s;
            cpu.esi = 0x1b0;
            cpu.ebp = reg32(wanted);
            if (!call(app, cpu, 0x52df80))
                return;
            put(app, s + 0xd48, 0x1b0);
            n = wanted < 0x1b0 ? reg32(wanted) : 0x1b0;
            if (!copy(n))
                return;
        } while (wanted > 0);
    }
    cpu.eax = 0;
    for (cpu.edx = at(app, f); i32(cpu.edx) > 0; cpu.edx = at(app, f))
    {
        cpu.ecx += 2;
        cpu.ebx = cpu.edx - 1;
        putHalf(app, cpu.ecx - 2, 0);
        put(app, f, cpu.ebx);
    }
    cpu.eax = 1;
    cpu.ecx = kept.ecx;
    cpu.esi = kept.esi;
    cpu.edi = kept.edi;
    cpu.ebp = kept.ebp;
    cpu.esp = kept.esp + 4;
}

/* 0x52a790 (stdcall, 4 words; ebx the data, ecx the length, edx the state):
 * a frame-coded sound set up, its decoder by 0x52de94.  0xd50, the state's
 * size. */
void codedSetup(App* app, CPU& cpu)
{
    const reg32 esi = cpu.esi;
    cpu.esp -= 4;
    cpu.esi = cpu.edx;
    cpu.eax = cpu.ebx;
    if (!call(app, cpu, 0x52de94))
        return;
    put(app, cpu.esi + 0xd48, 0);
    put(app, cpu.esi + 0xd4c, 0);
    cpu.eax = at(app, cpu.esp + 0x10);
    put(app, cpu.esi + 0xd44, cpu.ecx);
    put(app, cpu.eax, 0x52a668);
    cpu.eax = at(app, cpu.esp + 0x14);
    put(app, cpu.eax, 0x52a610);
    cpu.eax = 0xd50;
    cpu.esi = esi;
    cpu.esp += 4 + 4 + 0x10;
}

/* 0x52a7e0: a frame-coded sound streamed (eax the state -- +0xd44 the
 * chunk, +0xd48 its samples, +0xd4c the sample in it, +0xd50 the samples of
 * the decoded frame left -- edx frames wanted, ebx where): frame after frame
 * by 0x52df80, the chunk's end asked of the refill ([0x5678b4]); a chunk
 * starting with 0 a raw block (its byte 1 at +4, its data at [s]), any other
 * its decoder's set-up (0x52de94); none, and the rest is silence.  1; -1
 * with no chunk. */
void codedStreamDecode(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 f = kept.frame(4, 0xc);
    cpu.esp = f;
    const reg32 s = cpu.eax;
    i32 wanted = i32(cpu.edx);
    cpu.edi = cpu.edx;
    cpu.edx = at(app, s + 0xd44);
    cpu.ecx = s;
    const auto out = [&](reg32 eax) {
        cpu.eax = eax;
        cpu.ecx = kept.ecx;
        cpu.esi = kept.esi;
        cpu.edi = kept.edi;
        cpu.ebp = kept.ebp;
        cpu.esp = kept.esp + 4;
    };
    if (cpu.edx == 0)
    {
        out(0xffffffff);
        return;
    }
    cpu.ebp = cpu.ebx;
    while (wanted > 0)
    {
        if (s32(app, s + 0xd4c) >= s32(app, s + 0xd48))
        {
            cpu.edx = s + 0xd48;
            cpu.eax = s + 0xd44;
            cpu.edi = reg32(wanted);
            if (!call(app, cpu, at(app, 0x5678b4)))
                return;
            cpu.ebx = at(app, s + 0xd44);
            if (cpu.eax != 0 || cpu.ebx == 0)
            {
                cpu.ebx = reg32(wanted) * 2;
                cpu.eax = cpu.ebp;
                cpu.edx = 0;
                if (!call(app, cpu, kFill))
                    return;
                put(app, s + 0xd4c, 0);
                put(app, s + 0xd48, 0);
                out(1);
                return;
            }
            cpu.edx = (cpu.edx & 0xffffff00) | byte(app, cpu.ebx);
            cpu.eax = cpu.ebx;
            if (byte(app, cpu.ebx) == 0)
            {
                cpu.eax = byte(app, cpu.ebx + 1);
                put(app, s + 4, cpu.eax);
                cpu.eax = at(app, s + 0xd44) + 2;
                put(app, s + 8, 8);
                put(app, s, cpu.eax);
            }
            else
            {
                cpu.eax = cpu.ebx + 1;
                cpu.edx = s;
                if (!call(app, cpu, 0x52de94))
                    return;
            }
            put(app, s + 0xd4c, 0);
        }
        if (s32(app, s + 0xd50) <= 0)
        {
            cpu.edx = 1;
            cpu.eax = s;
            cpu.edi = reg32(wanted);
            if (!call(app, cpu, 0x52df80))
                return;
            put(app, s + 0xd50, 0x1b0);
        }
        i32 n = s32(app, s + 0xd48) - s32(app, s + 0xd4c);
        if (wanted < n)
            n = wanted;
        cpu.edx = at(app, s + 0xd50);
        if (n > i32(cpu.edx))
            n = i32(cpu.edx);
        cpu.esi = reg32(n);
        cpu.eax = ((0x1b0 - at(app, s + 0xd50)) << 2) + s + 0x684;
        cpu.ebx = reg32(n);
        cpu.edx = cpu.ebp;
        cpu.edi = reg32(wanted);
        if (!call(app, cpu, 0x52a618))
            return;
        cpu.ebx = at(app, s + 0xd4c) + reg32(n);
        cpu.ebp += reg32(n) * 2;
        cpu.eax = at(app, s + 0xd50) - reg32(n);
        put(app, s + 0xd4c, cpu.ebx);
        wanted -= n;
        put(app, s + 0xd50, cpu.eax);
    }
    out(1);
}

/* 0x52a970 (stdcall, 4 words; edx the state): a frame-coded sound streamed
 * set up, its first chunk to come.  0xd54, the state's size. */
void codedStreamSetup(App* app, CPU& cpu)
{
    const reg32 s = cpu.edx;
    put(app, s + 0xd44, 1);
    put(app, s + 0xd48, 0);
    put(app, s + 0xd4c, 0);
    put(app, s + 0xd50, 0);
    put(app, at(app, cpu.esp + 0x10), 0);
    cpu.edx = at(app, cpu.esp + 0xc);
    cpu.eax = 0xd54;
    put(app, cpu.edx, 0x52a7e0);
    cpu.esp += 4 + 0x10;
}

/* 0x52a9c0: a frame-coded sound from a packet player (eax the state --
 * +0xd44 the packet, +0xd48 its samples, +0xd4c the player, +0xd50 the
 * frames taken since the last release, +0xd54 the sample in the packet and
 * +0xd56 the samples of the decoded frame left, as words -- edx frames
 * wanted, ebx where): codedStreamDecode's, the packets from 0x5118fc, those
 * taken given back (0x511998).  The frames taken this time. */
void codedPacketDecode(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 f = kept.frame(4, 8);
    cpu.esp = f;
    const reg32 s = cpu.eax;
    cpu.esi = s;
    i32 wanted = i32(cpu.edx);
    cpu.edi = cpu.edx;
    cpu.ebp = cpu.ebx;
    cpu.edx = at(app, s + 0xd50);
    cpu.ecx = s;
    if (cpu.edx != 0)
    {
        cpu.eax = at(app, s + 0xd4c);
        if (!call(app, cpu, 0x511998))
            return;
        put(app, cpu.esi + 0xd50, 0);
    }
    while (wanted > 0)
    {
        cpu.ebx = at(app, s + 0xd48);
        cpu.eax = half(app, s + 0xd54);
        if (i32(cpu.eax) >= i32(cpu.ebx))
        {
            cpu.edx = s + 0xd48;
            cpu.eax = at(app, s + 0xd4c);
            cpu.edi = reg32(wanted);
            if (!call(app, cpu, 0x5118fc))
                return;
            put(app, s + 0xd44, cpu.eax);
            if (cpu.eax == 0)
            {
                if (at(app, s + 0xd50) != 0)
                {
                    cpu.ebx = reg32(wanted) * 2;
                    cpu.eax = cpu.ebp;
                    cpu.edx = 0;
                    if (!call(app, cpu, kFill))
                        return;
                }
                putHalf(app, s + 0xd54, 0);
                put(app, s + 0xd48, 0);
                break;
            }
            if (byte(app, cpu.eax) != 0)
            {
                cpu.eax += 1;
                cpu.edx = s;
                if (!call(app, cpu, 0x52de94))
                    return;
            }
            else
            {
                cpu.eax = byte(app, cpu.eax + 1);
                put(app, s + 4, cpu.eax);
                cpu.eax = at(app, s + 0xd44) + 2;
                put(app, s + 8, 8);
                put(app, s, cpu.eax);
            }
            putHalf(app, s + 0xd54, 0);
        }
        if (shalf(app, s + 0xd56) <= 0)
        {
            cpu.edx = 1;
            cpu.eax = s;
            cpu.edi = reg32(wanted);
            if (!call(app, cpu, 0x52df80))
                return;
            putHalf(app, s + 0xd56, 0x1b0);
        }
        cpu.eax = at(app, s + 0xd48) - half(app, s + 0xd54);
        i32 n = i32(cpu.eax);
        if (wanted < n)
            n = wanted;
        if (shalf(app, s + 0xd56) < n)
            n = shalf(app, s + 0xd56);
        cpu.esi = reg32(n);
        cpu.eax = ((0x1b0 - reg32(shalf(app, s + 0xd56))) << 2) + s + 0x684;
        cpu.ebx = reg32(n);
        cpu.edx = cpu.ebp;
        cpu.edi = reg32(wanted);
        if (!call(app, cpu, 0x52a618))
            return;
        putHalf(app, s + 0xd54, reg16(half(app, s + 0xd54) + n));
        cpu.ebx = at(app, s + 0xd50) + reg32(n);
        cpu.ebp += reg32(n) * 2;
        cpu.eax = (((reg32(n) * 2) & 0xffff0000) | half(app, s + 0xd56)) - reg32(n);
        put(app, s + 0xd50, cpu.ebx);
        wanted -= n;
        putHalf(app, s + 0xd56, reg16(cpu.eax));
    }
    cpu.eax = at(app, s + 0xd50);
    cpu.ecx = kept.ecx;
    cpu.esi = kept.esi;
    cpu.edi = kept.edi;
    cpu.ebp = kept.ebp;
    cpu.esp = kept.esp + 4;
}

/* 0x52ab70 (stdcall, 4 words; eax the sound, edx the state): a frame-coded
 * sound from a packet player set up, its player by 0x52d160.  0xd58, the
 * state's size. */
void codedPacketSetup(App* app, CPU& cpu)
{
    if (!call(app, cpu, 0x52d160))
        return;
    const reg32 s = cpu.edx;
    put(app, s + 0xd44, 0);
    put(app, s + 0xd48, 0);
    putHalf(app, s + 0xd54, 0);
    putHalf(app, s + 0xd56, 0);
    put(app, s + 0xd4c, cpu.eax);
    put(app, s + 0xd50, 0);
    put(app, at(app, cpu.esp + 0x10), 0);
    cpu.eax = at(app, cpu.esp + 0xc);
    put(app, cpu.eax, 0x52a9c0);
    cpu.eax = 0xd58;
    cpu.esp += 4 + 0x10;
}

namespace
{

x86::Float f32(App* app, reg32 a) { return x86::Float(app->getMemory<float>(a)); }

}  // namespace

/* 0x52d370 (eax the bit reader -- [+0] the next byte, [+4] the bits, [+8]
 * how many -- edx how many): the next edx bits, the reader topped up with a
 * byte when fewer than 8 are left. */
void codedBits(App* app, CPU& cpu)
{
    const reg32 r = cpu.eax, n = cpu.edx;
    const reg32 value = at(app, n * 4 + 0x56b1d0) & at(app, r + 4);
    const reg32 left = at(app, r + 8) - n;
    put(app, r + 8, left);
    put(app, r + 4, at(app, r + 4) >> (n & 0x1f));
    if (i32(left) < 8)
    {
        cpu.edx = reg32(byte(app, at(app, r))) << (left & 0x1f);
        put(app, r, at(app, r) + 1);
        put(app, r + 8, left + 8);
        put(app, r + 4, at(app, r + 4) | cpu.edx);
    }
    cpu.eax = value;
    cpu.esp += 4;
}

/* 0x52d3cc (eax the bit reader, edx how many): edx bits passed over. */
void codedSkip(App* app, CPU& cpu)
{
    const reg32 r = cpu.eax, n = cpu.edx;
    put(app, r + 4, at(app, r + 4) >> (n & 0x1f));
    const reg32 left = at(app, r + 8) - n;
    put(app, r + 8, left);
    if (i32(left) < 8)
    {
        const reg32 bits = reg32(byte(app, at(app, r))) << (left & 0x1f);
        put(app, r + 4, at(app, r + 4) | bits);
        put(app, r + 8, left + 8);
        cpu.edx = at(app, r) + 1;
        put(app, r, cpu.edx);
    }
    cpu.esp += 4;
}

/* 0x52d428 (eax the bit reader, edx the kind, ebx where, ecx the step): a
 * subframe's pulses, every ecx-th of 0x6c floats.  Kind 0: two bits each --
 * 0, -2.0, 0 or 2.0.  Otherwise the codes of the tables at 0x56b2f4 (the next
 * state by the low byte) and 0x56b4f4 (the next table, the bits it took, the
 * value): past 3 the value; 2 or 3 a run of zeros (6 bits + 7); 0 or 1 a
 * count of 1 bits from 7, then its sign. */
void codedPulses(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 f = kept.frame(3, 0x10);
    cpu.esp = f;
    const reg32 r = cpu.eax, out = cpu.ebx, step = cpu.ecx;
    cpu.esi = r;
    cpu.ebp = out;
    cpu.edi = step;
    const auto skip = [&](reg32 n) {
        cpu.edx = n;
        cpu.eax = r;
        return call(app, cpu, 0x52d3cc);
    };
    const auto bits = [&](reg32 n) {
        cpu.edx = n;
        cpu.eax = r;
        return call(app, cpu, 0x52d370);
    };
    const auto out_ = [&] {
        cpu.esi = kept.esi;
        cpu.edi = kept.edi;
        cpu.ebp = kept.ebp;
        cpu.esp = kept.esp + 4;
    };
    if (cpu.edx == 0)
    {
        cpu.ecx = 0;
        cpu.ebx = 3;
        do
        {
            cpu.eax = at(app, r + 4) & 3;
            reg32 n = 1, value = 0;
            if (cpu.eax == 1)
                n = 2, value = 0xc0000000;
            else if (cpu.eax == 3)
                n = 2, value = 0x40000000;
            put(app, out + cpu.ecx * 4, value);
            if (!skip(n))
                return;
            cpu.ecx += step;
        } while (i32(cpu.ecx) < 0x6c);
        out_();
        return;
    }
    cpu.ecx = 0;
    put(app, f, 0);
    do
    {
        cpu.eax = at(app, r + 4) & 0xff;
        cpu.edx = at(app, f) << 8;
        cpu.ebx = byte(app, cpu.edx + cpu.eax + 0x56b2f4);
        const reg32 code = cpu.ebx * 0xc;
        put(app, f + 4, code);
        put(app, f, at(app, code + 0x56b4f4));
        if (!skip(at(app, code + 0x56b4f8)))
            return;
        if (i32(cpu.ebx) > 3)
        {
            cpu.edx = code;
            cpu.eax = at(app, code + 0x56b4fc);
            put(app, out + cpu.ecx * 4, cpu.eax);
            cpu.ecx += step;
        }
        else if (i32(cpu.ebx) > 1)
        {
            if (!bits(6))
                return;
            cpu.eax += 7;
            i32 run = i32(cpu.eax);
            cpu.eax = reg32(mul(run, i32(step))) + cpu.ecx;
            if (i32(cpu.eax) > 0x6c)
            {
                cpu.eax = 0x6c - cpu.ecx;
                idiv(cpu, step);
                run = i32(cpu.eax);
            }
            cpu.ebx = reg32(run);
            cpu.eax = 0;
            if (run > 0)
            {
                cpu.edx = reg32(run);
                do
                {
                    ++cpu.eax;
                    put(app, out + cpu.ecx * 4, 0);
                    cpu.ecx += step;
                } while (i32(cpu.eax) < run);
            }
        }
        else
        {
            cpu.ebx = 7;
            for (;;)
            {
                if (!bits(1))
                    return;
                if (cpu.eax != 1)
                    break;
                cpu.ebx += cpu.eax;
            }
            if (!bits(1))
                return;
            cpu.edx = out + cpu.ecx * 4;
            if (cpu.eax != 1)
                cpu.ebx = 0u - cpu.ebx;
            put(app, f + 0xc, cpu.ebx);
            app->getMemory<float>(cpu.edx) = float(i32(cpu.ebx));
            cpu.ecx += step;
        }
    } while (i32(cpu.ecx) < 0x6c);
    out_();
}

/* 0x52d5cc (eax the samples): the odd samples between the even ones -- each
 * from its neighbours 1, 3 and 5 away either side, by the weights at
 * 0x5520ec, 0x5520f4, 0x5520fc -- 0x36 of them. */
void codedInterpolate(App* app, CPU& cpu)
{
    auto& fpu = cpu.fpu;
    const x86::Float c1 = f64(app, 0x5520ec), c2 = f64(app, 0x5520f4), c3 = f64(app, 0x5520fc);
    const reg32 end = cpu.eax + 0x1b0;
    for (reg32 at = cpu.eax; at != end; at += 8)
    {
        x86::Float sum = fpu.mul(fpu.add(f32(app, at - 4), f32(app, at + 4)), c1);
        sum = fpu.add(sum, fpu.mul(fpu.add(f32(app, at - 0xc), f32(app, at + 0xc)), c2));
        sum = fpu.add(sum, fpu.mul(fpu.add(f32(app, at - 0x14), f32(app, at + 0x14)), c3));
        fstp32(app, at, sum);
    }
    cpu.eax = end;
    cpu.esp += 4;
}

/* 0x52d618 (eax the 12 reflection coefficients, edx where): the synthesis
 * filter's 12 coefficients from them, step by step through a lattice kept
 * in floats on the stack, as the x87 rounds them. */
void codedFilter(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 f = kept.frame(5, 0x6c);
    auto& fpu = cpu.fpu;
    const reg32 k = cpu.eax, out = cpu.edx;
    put(app, f + 0x64, out);
    // A[-1] at f+0x30 (1.0 first), A[0..10] at f+0x34 the coefficients; the
    // history at f.
    for (i32 i = 10; i >= 0; --i)
        app->getMemory<float>(f + 0x34 + 4 * reg32(i)) = app->getMemory<float>(k + 4 * reg32(i));
    put(app, f + 0x30, 0x3f800000);
    put(app, f + 0x60, k + 0x28);
    const auto A = [&](i32 i) -> reg32 { return f + 0x34 + 4 * reg32(i); };
    for (reg32 n = 0; n < 0xc; ++n)
    {
        x86::Float acc = fpu.mul(-f32(app, k + 0x2c), f32(app, f + 0x5c));
        fstp32(app, f + 0x68, acc);
        reg32 c = k + 0x28;
        for (i32 e = 10; e >= 0; --e, c -= 4)
        {
            acc = fpu.sub(acc, fpu.mul(f32(app, c), f32(app, A(e - 1))));
            fstp32(app, A(e), fpu.add(fpu.mul(f32(app, c), acc), f32(app, A(e - 1))));
        }
        fstp32(app, f + 0x68, acc);
        cpu.eax = at(app, f + 0x68);
        cpu.ecx = 0;
        put(app, f + 0x30, cpu.eax);
        put(app, f + 4 * n, cpu.eax);
        if (n > 0)
        {
            acc = f32(app, f + 0x68);
            cpu.edx = out;
            for (reg32 i = 0; i < n; ++i)
            {
                acc = fpu.sub(acc, fpu.mul(f32(app, cpu.edx), f32(app, f + 4 * (n - 1 - i))));
                cpu.edx += 4;
                ++cpu.ecx;
            }
            fstp32(app, f + 0x68, acc);
        }
        cpu.eax = at(app, f + 0x68);
        put(app, out + 4 * n, cpu.eax);
    }
    cpu.ecx = kept.ecx;
    cpu.esp = kept.esp + 4;
}

/* 0x52d6d8 (eax the state, edx the first sample, ebx how many blocks of 12,
 * ecx whether to round): the synthesis filter -- its 12 coefficients from
 * the reflection coefficients at +0x114 (0x52d618), each sample the
 * excitation there plus the 12 last outputs (a ring at +0x144) by them; the
 * sample stored plus 0 (or 1.5 * 2^23, which rounds it to a whole number).
 * Unrolled by 12 as the code is: of each 12, the 4th and the 11th add the
 * output as stored (a float), the others as the x87 holds it. */
void codedSynthesis(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 f = kept.frame(2, 0x34);
    cpu.esp = f;
    auto& fpu = cpu.fpu;
    const reg32 s = cpu.eax, first = cpu.edx, blocks = cpu.ebx;
    put(app, f + 0x30, cpu.ecx != 0 ? 0x4b400000 : 0);
    cpu.esi = s;
    cpu.edi = first;
    cpu.edx = f;
    cpu.eax = s + 0x114;
    if (!call(app, cpu, 0x52d618))
        return;
    cpu.eax = first * 4 + s + 0x684;
    cpu.edx = 0;
    const x86::Float g = f32(app, f + 0x30);
    for (; i32(cpu.edx) < i32(blocks); ++cpu.edx, cpu.eax += 0x30)
        for (reg32 j = 0; j < 12; ++j)
        {
            const reg32 x = cpu.eax + 4 * j;
            x86::Float sum = fpu.add(fpu.mul(f32(app, f), f32(app, s + 0x144 + 4 * ((12 - j) % 12))), f32(app, x));
            for (reg32 k = 1; k < 12; ++k)
                sum = fpu.add(sum, fpu.mul(f32(app, f + 4 * k), f32(app, s + 0x144 + 4 * ((k + 12 - j) % 12))));
            const reg32 ring = s + 0x144 + 4 * (11 - j);
            fstp32(app, ring, sum);
            if (j == 3 || j == 10)
                sum = f32(app, ring);
            fstp32(app, x, fpu.add(sum, g));
        }
    cpu.esi = kept.esi;
    cpu.edi = kept.edi;
    cpu.esp = kept.esp + 4;
}

/* 0x52de94 (eax the data, edx the state): a frame-coded sound's decoder set
 * up -- [0x9f6b24] (the mixer's emms) first; its bit reader on the data
 * after the first byte, its header (a flag, a shift, a scale and the
 * reflection coefficients' 64 floats scaled), its history cleared. */
void codedStart(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 f = kept.frame(2, 8);
    auto& fpu = cpu.fpu;
    const reg32 data = cpu.eax, s = cpu.edx;
    cpu.esi = data;
    cpu.ebx = s;
    cpu.esp = f - 4;
    if (!call(app, cpu, at(app, 0x9f6b24)))
        return;
    put(app, s + 8, 8);
    put(app, s + 4, byte(app, data));
    put(app, s, data + 1);
    const auto bits = [&](reg32 n) {
        cpu.eax = s;
        cpu.edx = n;
        return call(app, cpu, 0x52d370);
    };
    if (!bits(1))
        return;
    put(app, s + 0xc, cpu.eax);
    if (!bits(4))
        return;
    put(app, s + 0x10, 0x20 - cpu.eax);
    if (!bits(4))
        return;
    cpu.eax += 1;
    put(app, f, cpu.eax);
    put(app, f + 4, 0);
    fstp32(app, s + 0x14, fpu.mul(x86::Float(std::int64_t(cpu.eax)), f64(app, 0x552104)));
    if (!bits(6))
        return;
    put(app, f, cpu.eax);
    const x86::Float scale =
        fpu.add(fpu.mul(x86::Float(std::int64_t(cpu.eax)), f64(app, 0x55210c)), f64(app, 0x552114));
    cpu.edx = s + 0x100;
    for (reg32 a = s + 4; a != s + 0x100; a += 4)
        fstp32(app, a + 0x14, fpu.mul(f32(app, a + 0x10), scale));
    cpu.eax = s;
    cpu.edx = s + 0x30;
    for (reg32 a = s + 4; a != s + 0x34; a += 4)
    {
        put(app, a + 0x110, 0);
        put(app, a + 0x140, 0);
    }
    for (reg32 a = s + 4; a != s + 0x514; a += 4)
        put(app, a + 0x170, 0);
    cpu.eax = s + 0x510;
    cpu.ecx = kept.ecx;
    cpu.ebx = kept.ebx;
    cpu.esi = kept.esi;
    cpu.esp = kept.esp + 4;
}

/* 0x52df80 (eax the state, edx whether to round): one frame of 432
 * samples -- [0x9f6b24] first; the change of the 12 reflection coefficients
 * (6 bits each for 4, 5 for 8, by the tables at 0x56b1f4 and 0x56b234, a
 * quarter of it a step); 4 subframes of 108, each the past excitation at its
 * lag by one gain plus the pulses (0x52d428; or every other one, the rest
 * interpolated by 0x52d5cc and the gain halved) by the other; the excitation
 * kept, then the synthesis filter (0x52d6d8) over 12, 12, 12 and 396 samples,
 * the coefficients a step nearer before each. */
void codedFrame(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 f = kept.frame(5, 0x230);
    cpu.esp = f;
    auto& fpu = cpu.fpu;
    const reg32 s = cpu.eax;
    cpu.esi = s;
    put(app, f + 0x214, cpu.edx);
    if (!call(app, cpu, at(app, 0x9f6b24)))
        return;
    const auto bits = [&](reg32 n) {
        cpu.edx = n;
        cpu.eax = s;
        return call(app, cpu, 0x52d370);
    };
    const auto delta = [&](reg32 i, reg32 table) {
        fstp32(app, f + 0x1d8 + 4 * i,
               fpu.mul(fpu.sub(f32(app, cpu.eax * 4 + table), f32(app, s + 0x114 + 4 * i)), f64(app, 0x55211c)));
    };
    if (!bits(6))
        return;
    cpu.ecx = at(app, s + 0x10);
    cpu.edx = cpu.eax;
    cpu.ebp = cpu.eax < cpu.ecx ? 1 : 0;
    delta(0, 0x56b1f4);
    cpu.ebx = 6;
    for (cpu.ecx = 1; cpu.ecx < 4;)
    {
        cpu.edi = s + 4 * cpu.ecx;
        if (!bits(6))
            return;
        delta(cpu.ecx, 0x56b1f4);
        ++cpu.ecx;
    }
    cpu.ebx = 5;
    for (cpu.ecx = 4; cpu.ecx < 0xc;)
    {
        cpu.edi = s + 4 * cpu.ecx;
        if (!bits(5))
            return;
        delta(cpu.ecx, 0x56b234);
        ++cpu.ecx;
    }
    const reg32 kind = cpu.ebp;
    put(app, f + 0x220, 0xd8);
    for (reg32 sub = 0; sub != 0x6c0; sub += 0x1b0)
    {
        cpu.edi = sub;
        if (!bits(8))
            return;
        put(app, f + 0x22c, at(app, f + 0x220) - cpu.eax);
        if (!bits(4))
            return;
        put(app, f + 0x208, cpu.eax);
        put(app, f + 0x20c, 0);
        fstp32(app, f + 0x224, fpu.mul(x86::Float(std::int64_t(cpu.eax)), f64(app, 0x552124)));
        if (!bits(6))
            return;
        cpu.eax = at(app, s + cpu.eax * 4 + 0x14);
        cpu.ecx = at(app, s + 0xc);
        put(app, f + 0x228, cpu.eax);
        if (cpu.ecx == 0)
        {
            cpu.ecx = 1;
            cpu.ebx = f + 0x14;
            cpu.edx = kind;
            cpu.eax = s;
            if (!call(app, cpu, 0x52d428))
                return;
        }
        else
        {
            if (!bits(1))
                return;
            const reg32 phase = cpu.eax;
            cpu.ecx = phase;
            put(app, f + 0x218, phase);
            cpu.ebx = f + 0x14;
            if (!bits(1))
                return;
            const reg32 odd = phase << 2;
            put(app, f + 0x210, cpu.eax);
            put(app, f + 0x21c, odd);
            cpu.edx = kind;
            cpu.ebx = f + 0x14 + odd;
            cpu.ecx = 2;
            cpu.eax = s;
            if (!call(app, cpu, 0x52d428))
                return;
            if (at(app, f + 0x210) != 0)
            {
                cpu.ecx = 0;
                for (reg32 a = f + 0x18 - odd; a != f + 0x1c8 - odd; a += 8)
                    put(app, a, 0);
                cpu.eax = 0x1c8 - odd;
                cpu.edx = 0x1c8 - odd;
            }
            else
            {
                cpu.ecx = 0;
                for (reg32 a = f; a != f + 0x14; a += 4)
                    put(app, a, 0);
                cpu.ebx = 0;
                for (reg32 a = f + 0x1c4; a != f + 0x1d8; a += 4)
                    put(app, a, 0);
                cpu.edx = at(app, f + 0x218) << 2;
                cpu.eax = f + 0x18 - cpu.edx;
                if (!call(app, cpu, 0x52d5cc))
                    return;
                fstp32(app, f + 0x228, fpu.mul(f32(app, f + 0x228), f64(app, 0x55212c)));
            }
        }
        const reg32 lag = at(app, f + 0x22c) * 4 + s;
        const x86::Float g2 = f32(app, f + 0x228), g1 = f32(app, f + 0x224);
        for (reg32 i = 0; i != 0x1b0; i += 4)
            fstp32(app, s + sub + 4 + i + 0x680,
                   fpu.add(fpu.mul(g1, f32(app, lag + i + 0x174)), fpu.mul(g2, f32(app, f + i + 0x14))));
        cpu.eax = 0x1b0;
        cpu.ecx = s + sub + 0x1b0;
        cpu.edx = lag + 0x1b0;
        cpu.ebx = at(app, f + 0x220) + 0x6c;
        put(app, f + 0x220, cpu.ebx);
    }
    for (reg32 a = s + 4; a != s + 0x514; a += 4)
        put(app, a + 0x170, at(app, a + 0x830));
    const auto step = [&] {
        for (reg32 i = 0; i < 0xc; ++i)
            fstp32(app, s + 0x114 + 4 * i, fpu.add(f32(app, f + 0x1d8 + 4 * i), f32(app, s + 0x114 + 4 * i)));
    };
    const reg32 places[4][2] = {{0, 1}, {0xc, 1}, {0x18, 1}, {0x24, 0x21}};
    for (const auto& p : places)
    {
        step();
        cpu.ecx = at(app, f + 0x214);
        cpu.ebx = p[1];
        cpu.eax = s;
        cpu.edx = p[0];
        if (!call(app, cpu, 0x52d6d8))
            return;
    }
    cpu.ebx = kept.ebx;
    cpu.ecx = kept.ecx;
    cpu.esi = kept.esi;
    cpu.edi = kept.edi;
    cpu.ebp = kept.ebp;
    cpu.esp = kept.esp + 4;
}

namespace
{

/* The x87 as the conversions' code drives it, instruction by instruction:
 * its stack, so that what is left in its registers and its status word are
 * the code's. */
struct X87
{
    App* app;
    x86::FPU& f;
    void fld(x86::Float v) { f.push(v); }
    void fldm(reg32 a) { f.push(f32(app, a)); }
    void fldst(int i) { f.push(f.st(i)); }
    void fxch(int i) { std::swap(f.st(0), f.st(i)); }
    void fmulst(int i) { f.st(0) = f.mul(f.st(0), f.st(i)); }
    void faddm(reg32 a) { f.st(0) = f.add(f.st(0), f32(app, a)); }
    void faddp(int i)
    {
        f.st(i) = f.add(f.st(i), f.st(0));
        f.pop();
    }
    void fst(reg32 a) { app->getMemory<float>(a) = float(f.st(0)); }
    void fstp(reg32 a)
    {
        fst(a);
        f.pop();
    }
    void pop() { f.pop(); }
};

constexpr reg32 kXaFirst = 0x56ad50, kXaSecond = 0x56ad60, kXaNibbles = 0xa0baa0;

}  // namespace

/* 0x5008a0 (cdecl: count, 16-bit samples, where): each to a float, eight
 * at a time (read, then written) and the rest one by one.  Every register
 * kept (pushad). */
void convert16(App* app, CPU& cpu)
{
    const reg32 esp = cpu.esp;
    i32 count = s32(app, esp + 4);
    reg32 from = at(app, esp + 8), to = at(app, esp + 0xc);
    if (count > 7)
    {
        count -= 7;
        do
        {
            float v[8];
            for (int i = 0; i < 8; ++i)
                v[i] = float(i16(half(app, from + 2 * i)));
            for (int i = 0; i < 8; ++i)
                app->getMemory<float>(to + 4 * i) = v[i];
            from += 0x10;
            to += 0x20;
            count -= 8;
        } while (count > 0);
        count += 7;
    }
    for (; count > 0; --count, from += 2, to += 4)
        app->getMemory<float>(to) = float(i16(half(app, from)));
    cpu.esp = esp + 4;
}

/* 0x500910 (cdecl: frames, stereo floats, where): each frame's two sides
 * added and halved, rounded to a whole number by adding 1.5 * 2^23 (the
 * float written back over the left side), then clipped to 16 bits by its low
 * 20 bits as the code tests them. */
void convertToWords(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    auto& fpu = cpu.fpu;
    cpu.ecx = at(app, kept.esp + 8);
    cpu.ebx = (at(app, kept.esp + 4) << 3) + cpu.ecx;
    cpu.edx = at(app, kept.esp + 0xc);
    for (cpu.eax = cpu.ecx; cpu.eax < cpu.ebx;)
    {
        const x86::Float half_ = fpu.mul(fpu.add(f32(app, cpu.eax + 4), f32(app, cpu.eax)), f64(app, 0x54e304));
        fstp32(app, cpu.eax, fpu.add(half_, f64(app, 0x54e30c)));
        cpu.ecx = at(app, cpu.eax) & 0xfffff;
        cpu.eax += 8;
        reg16 w = reg16(cpu.ecx);
        if (cpu.ecx > 0x7fff && cpu.ecx < 0xf8000)
            w = cpu.ecx >= 0x80000 ? 0x8000 : 0x7fff;
        putHalf(app, cpu.edx, w);
        cpu.edx += 2;
    }
    cpu.ebx = kept.ebx;
    cpu.esp = kept.esp + 4;
}

/* 0x500990 (cdecl: the state -- [+0] frames, [+4..+0x10] the history,
 * [+0x14] the data, [+0x18] where): stereo XA by the x87, each block's two
 * filters and its nibbles' table at 0xa0baa0; the history kept at 0x567870
 * on the way.  Every register kept (pushad). */
void convertXaStereo(App* app, CPU& cpu)
{
    const reg32 esp = cpu.esp;
    X87 x{app, cpu.fpu};
    const reg32 s = at(app, esp + 4);
    reg32 from = at(app, s + 0x14), to = at(app, s + 0x18);
    for (reg32 i = 0; i < 4; ++i)
        put(app, 0x567870 + 4 * i, at(app, s + 4 + 4 * i));
    while (s32(app, s) > 0)
    {
        put(app, s, at(app, s) - 0x1c);
        const reg32 lo = byte(app, from) & 0xf, hi = byte(app, from) >> 4;
        x.fldm(lo * 4 + kXaSecond);
        x.fldm(lo * 4 + kXaFirst);
        x.fldm(hi * 4 + kXaSecond);
        x.fldm(hi * 4 + kXaFirst);
        const reg32 shiftHi = reg32(byte(app, from + 1) >> 4) << 6, shiftLo = reg32(byte(app, from + 1) & 0xf) << 6;
        from += 2;
        for (i32 n = 0x1c; n > 0; n -= 2)
        {
            for (int half_ = 0; half_ < 2; ++half_)
            {
                const reg32 a = half_ == 0 ? 0x567870 : 0x567874, b = half_ == 0 ? 0x567874 : 0x567870;
                const reg32 c = half_ == 0 ? 0x567878 : 0x56787c, d = half_ == 0 ? 0x56787c : 0x567878;
                x.fldm(a);
                x.fmulst(1);
                x.fldm(c);
                x.fmulst(4);
                x.fldm(b);
                x.fmulst(4);
                x.fldm(d);
                x.fmulst(7);
                x.fxch(1);
                x.faddp(3);
                const reg8 code = byte(app, from + reg32(half_));
                x.faddp(1);
                x.fxch(1);
                x.faddm(shiftHi + reg32(code >> 4) * 4 + kXaNibbles);
                x.fxch(1);
                x.faddm(shiftLo + reg32(code & 0xf) * 4 + kXaNibbles);
                x.fxch(1);
                x.fst(to + 8 * reg32(half_));
                x.fstp(b);
                x.fst(to + 8 * reg32(half_) + 4);
                x.fstp(d);
            }
            from += 2;
            to += 0x10;
        }
        for (int i = 0; i < 4; ++i)
            x.pop();
    }
    put(app, s + 0x18, to);
    for (reg32 i = 0; i < 4; ++i)
        put(app, s + 4 + 4 * i, at(app, 0x567870 + 4 * i));
    cpu.esp = esp + 4;
}

/* 0x500b10 (cdecl: count, 8-bit samples, where): each to a float by the
 * table at 0xa0c2a0, four at a time (read, then written) and the rest one by
 * one.  Every register kept (pushad). */
void convert8(App* app, CPU& cpu)
{
    const reg32 esp = cpu.esp;
    i32 count = s32(app, esp + 4);
    reg32 from = at(app, esp + 8), to = at(app, esp + 0xc);
    if (count > 3)
    {
        count -= 3;
        do
        {
            reg32 v[4];
            for (int i = 0; i < 4; ++i)
                v[i] = at(app, byte(app, from + reg32(i)) * 4 + 0xa0c2a0);
            for (int i = 0; i < 4; ++i)
                put(app, to + 4 * reg32(i), v[i]);
            from += 4;
            to += 0x10;
            count -= 4;
        } while (count > 0);
        count += 3;
    }
    for (; count > 0; --count, ++from, to += 4)
        put(app, to, at(app, byte(app, from) * 4 + 0xa0c2a0));
    cpu.esp = esp + 4;
}

/* 0x500b90 (cdecl: the state -- [+0] frames, [+4], [+8] the history,
 * [+0xc] the data, [+0x10] where): mono XA by the x87, as the code's stack
 * moves, its last fcompp's status word left.  Every register kept. */
void convertXaMono(App* app, CPU& cpu)
{
    const reg32 esp = cpu.esp;
    X87 x{app, cpu.fpu};
    const reg32 s = at(app, esp + 4);
    reg32 from = at(app, s + 0xc), to = at(app, s + 0x10);
    put(app, 0x567880, at(app, s + 4));
    put(app, 0x567884, at(app, s + 8));
    while (s32(app, s) > 0)
    {
        put(app, s, at(app, s) - 0x1c);
        const reg32 filter = byte(app, from) >> 4;
        x.fldm(filter * 4 + kXaSecond);
        x.fldm(filter * 4 + kXaFirst);
        const reg32 shift = reg32(byte(app, from) & 0xf) << 6;
        ++from;
        x.fldm(0x567884);
        x.fmulst(2);
        x.fldm(0x567880);
        x.fldm(0x567880);
        x.fldm(0x567884);
        from += 0xe;
        to += 0x70;
        for (i32 n = -14; n < 0; ++n)
        {
            const reg8 code = byte(app, reg32(n) + from);
            x.pop();
            x.fmulst(3);
            x.faddp(2);
            x.fmulst(3);
            x.fxch(1);
            x.faddm(shift + reg32(code >> 4) * 4 + kXaNibbles);
            x.fldst(0);
            x.fldst(0);
            x.fxch(2);
            x.fst(to + reg32(n) * 8);
            x.fmulst(4);
            x.fxch(1);
            x.fmulst(5);
            x.fxch(1);
            x.faddp(3);
            x.fxch(2);
            x.faddm(shift + reg32(code & 0xf) * 4 + kXaNibbles);
            x.fldst(0);
            x.fxch(1);
            x.fst(to + reg32(n) * 8 + 4);
            x.fxch(2);
        }
        x.fstp(0x567884);
        x.pop();
        x.fstp(0x567880);
        cpu.fpu.compare(cpu.fpu.st(0), cpu.fpu.st(1));
        x.pop();
        x.pop();
        x.pop();
    }
    put(app, s + 4, at(app, 0x567880));
    put(app, s + 8, at(app, 0x567884));
    put(app, s + 0x10, to);
    cpu.esp = esp + 4;
}

}  // namespace snd
}  // namespace nfs3hp
