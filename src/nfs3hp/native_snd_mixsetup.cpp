#include "native_snd.h"

/* EA's SND mixer's set-up, native (native_snd.cpp says how): what gives a
 * mixer channel the functions native_mixer.cpp mixes it with.  iSNDmixstart
 * (native_snd_play.cpp) calls, through the tables the mixer's start fills, a
 * decoder's set-up for the sound's format and way of playing, its volume's
 * and its resampler's; setMixStep calls the resampler's step setter, which
 * picks the resampler by the step.
 *
 * The port's CPU has MMX ([0x5643b4] set): the tables hold the MMX set.  Of
 * it, these are the set-ups of the decoders native_mixer.cpp knows -- PCM
 * looped, once and streamed, XA once, XA with an intro, XA stereo streamed
 * from memory and from a file.  The others (8-bit PCM, the rest of the XA
 * variants, the plain set) are dead code (native_snd_dead.inc).
 *
 * A decoder's set-up (stdcall, 4 words): eax the voice, edx the channel's
 * decoder state, ebx and ecx the sound's data and length (or its stream),
 * [esp+4] and [esp+8] more of the same, [esp+0xc] where the decoder goes,
 * [esp+0x10] the channel's second function.  The state's size back. */
namespace nfs3hp
{
namespace snd
{

namespace
{

/* sub_52c9a0: PCM played once: its data edx, length ebx, frame bytes ecx (as
 * a shift's count, halved).  0x10. */
void pcmOnce(App* app, CPU& cpu, reg32 state, reg32 data, reg32 length, reg32 bytes, reg32 decoder, reg32 second)
{
    put(app, state + 4, 0);
    put(app, state, data);
    put(app, state + 8, length);
    put(app, state + 0xc, reg32(i32(bytes) >> 1));
    put(app, decoder, 0x52c8f4);
    put(app, second, 0x52c8f0);
}

/* sub_52ca48: PCM looped: as once, its loop's start ecx. */
void pcmLooped(App* app, reg32 state, reg32 data, reg32 length, reg32 loop, reg32 bytes, reg32 decoder)
{
    put(app, state + 4, 0);
    put(app, state, data);
    put(app, state + 8, length);
    put(app, state + 0xc, loop);
    put(app, state + 0x10, reg32(i32(bytes) >> 1));
    put(app, decoder, 0x52c9d0);
}

/* sub_52cb74: PCM streamed, its chunks from the stream's refill. */
void pcmStreamed(App* app, reg32 state, reg32 bytes, reg32 decoder)
{
    put(app, state, 1);
    put(app, state + 4, 0);
    put(app, state + 8, 0);
    put(app, state + 0xc, reg32(i32(bytes) >> 1));
    put(app, decoder, 0x52ca80);
}

/* sub_5274b0 and its kin: PCM once, `bytes` a frame. */
void onceEntry(App* app, CPU& cpu, reg32 bytes)
{
    const Kept kept(cpu);
    const reg32 decoder = at(app, kept.esp + 0xc), second = at(app, kept.esp + 0x10);
    pcmOnce(app, cpu, kept.edx, kept.ebx, kept.ecx, bytes, decoder, second);
    kept.ret(cpu, 0x10, 0x10);
    cpu.ecx = reg32(i32(bytes) >> 1);
    cpu.edx = kept.ebx;
    cpu.ebx = kept.ecx;
}

/* sub_5274d0 and its kin: PCM looped, `bytes` a frame; the second function
 * none. */
void loopedEntry(App* app, CPU& cpu, reg32 bytes)
{
    const Kept kept(cpu);
    const reg32 loop = at(app, kept.esp + 8), start = at(app, kept.esp + 4);
    const reg32 decoder = at(app, kept.esp + 0xc);
    put(app, at(app, kept.esp + 0x10), 0);
    pcmLooped(app, kept.edx, kept.ebx, start, loop, bytes, decoder);
    kept.ret(cpu, 0x14, 0x10);
    cpu.ecx = loop;
    cpu.edx = reg32(i32(bytes) >> 1);
    cpu.ebx = start;
}

/* sub_527500 and its kin: PCM streamed, `bytes` a frame; the second function
 * none. */
void streamedEntry(App* app, CPU& cpu, reg32 bytes)
{
    const Kept kept(cpu);
    const reg32 decoder = at(app, kept.esp + 0xc);
    put(app, at(app, kept.esp + 0x10), 0);
    pcmStreamed(app, kept.edx, bytes, decoder);
    kept.ret(cpu, 0x10, 0x10);
    cpu.edx = reg32(i32(bytes) >> 1);
    cpu.ebx = decoder;
}

}  // namespace

/* The decoder set-ups' tables' entries, MMX set: 16-bit PCM mono (1),
 * stereo (2) for 0x9f6a6c.., and for 0x9f6a8c.. stereo (2) and four bytes a
 * frame (4). */
void pcmOnceMono(App* app, CPU& cpu) { onceEntry(app, cpu, 1); }
void pcmOnceStereo(App* app, CPU& cpu) { onceEntry(app, cpu, 2); }
void pcmOnceStereo2(App* app, CPU& cpu) { onceEntry(app, cpu, 2); }
void pcmOnceQuad(App* app, CPU& cpu) { onceEntry(app, cpu, 4); }
void pcmLoopedMono(App* app, CPU& cpu) { loopedEntry(app, cpu, 1); }
void pcmLoopedStereo(App* app, CPU& cpu) { loopedEntry(app, cpu, 2); }
void pcmLoopedStereo2(App* app, CPU& cpu) { loopedEntry(app, cpu, 2); }
void pcmLoopedQuad(App* app, CPU& cpu) { loopedEntry(app, cpu, 4); }
void pcmStreamedMono(App* app, CPU& cpu) { streamedEntry(app, cpu, 1); }
void pcmStreamedStereo(App* app, CPU& cpu) { streamedEntry(app, cpu, 2); }
void pcmStreamedStereo2(App* app, CPU& cpu) { streamedEntry(app, cpu, 2); }
void pcmStreamedQuad(App* app, CPU& cpu) { streamedEntry(app, cpu, 4); }

/* 0x52c9a0, 0x52ca48, 0x52cb74: the PCM set-ups themselves, as the entries
 * call them (registers and 2 words, 2 words, registers). */
void pcmOnceSetup(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    pcmOnce(app, cpu, cpu.eax, cpu.edx, cpu.ebx, cpu.ecx, at(app, kept.esp + 4), at(app, kept.esp + 8));
    kept.ret(cpu, 0x10, 8);
    cpu.ecx = reg32(i32(kept.ecx) >> 1);
}

void pcmLoopedSetup(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 bytes = at(app, kept.esp + 4);
    pcmLooped(app, cpu.eax, cpu.edx, cpu.ebx, cpu.ecx, bytes, at(app, kept.esp + 8));
    kept.ret(cpu, 0x14, 8);
    cpu.edx = reg32(i32(bytes) >> 1);
}

void pcmStreamedSetup(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    pcmStreamed(app, cpu.eax, cpu.edx, cpu.ebx);
    kept.ret(cpu, 0x10);
    cpu.edx = reg32(i32(kept.edx) >> 1);
}

/* 0x529104: XA played once: its data ebx, length ecx.  0x54. */
void xaOnceSetup(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 s = cpu.edx;
    put(app, s + 0x18, 0);
    putHalf(app, s + 0x1c, 0);
    putHalf(app, s + 6, 0);
    putHalf(app, s + 4, 0);
    put(app, s + 0x10, cpu.ebx);
    put(app, s + 0x14, cpu.ecx);
    put(app, at(app, kept.esp + 0xc), 0x528f74);
    put(app, at(app, kept.esp + 0x10), 0x528f70);
    kept.ret(cpu, 0x54, 0x10);
    cpu.edx = at(app, kept.esp + 0x10);
}

/* 0x529534: XA with an intro, then its loop ([esp+4], [esp+8]); the decoder's
 * place kept in the state.  0x9c. */
void xaIntroSetup(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 s = cpu.edx;
    put(app, s + 0x18, 0);
    putHalf(app, s + 0x24, 0);
    putHalf(app, s + 6, 0);
    putHalf(app, s + 4, 0);
    put(app, s + 0x10, cpu.ebx);
    put(app, s + 0x14, cpu.ecx);
    put(app, s + 0x1c, at(app, kept.esp + 4));
    put(app, s + 0x20, at(app, kept.esp + 8));
    const reg32 decoder = at(app, kept.esp + 0xc), second = at(app, kept.esp + 0x10);
    put(app, s + 0x98, decoder);
    put(app, decoder, 0x529384);
    put(app, second, 0);
    kept.ret(cpu, 0x9c, 0x10);
    cpu.ecx = decoder;
    cpu.edx = second;
}

/* 0x52a354: stereo XA streamed from memory, its stream ecx.  0x90. */
void xaStereoStreamSetup(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 s = cpu.edx;
    put(app, s + 0x14, 1);
    put(app, s + 0x1c, 0);
    put(app, s + 0x20, 0);
    putHalf(app, s + 6, 0);
    putHalf(app, s + 4, 0);
    putHalf(app, s + 0xa, 0);
    putHalf(app, s + 8, 0);
    put(app, s + 0x18, cpu.ecx);
    put(app, at(app, kept.esp + 0xc), 0x52a1a0);
    put(app, at(app, kept.esp + 0x10), 0);
    kept.ret(cpu, 0x90, 0x10);
    cpu.edx = at(app, kept.esp + 0x10);
}

/* 0x52d160: the packet player whose voice is voice eax (its index), -1 for
 * none. */
void packetPlayerOf(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 v = cpu.eax;
    cpu.esp = kept.frame(3);
    reg32 result = 0xffffffff;
    for (reg32 i = 0; i < 0x10; ++i)
    {
        const reg32 p = at(app, 0xa0b044 + 4 * i);
        if (p == 0)
            continue;
        cpu.ebx = v;
        cpu.ecx = i;
        cpu.edx = 4 * i;
        if (!callWith(app, cpu, 0x4ffc9c, at(app, p)))
            return;
        if (cpu.eax == v)
        {
            result = i;
            break;
        }
    }
    kept.ret(cpu, result);
}

/* 0x52a5b4: stereo XA streamed from a file through a packet player -- voice
 * eax's -- its stream ecx.  0x98. */
void xaStereoFileSetup(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    if (!call(app, cpu, 0x52d160))
        return;
    const reg32 s = kept.edx, player = cpu.eax;
    put(app, s + 0x14, 0);
    put(app, s + 0x1c, 0);
    put(app, s + 0x20, 0);
    putHalf(app, s + 6, 0);
    putHalf(app, s + 4, 0);
    putHalf(app, s + 0xa, 0);
    putHalf(app, s + 8, 0);
    put(app, s + 0x28, 0);
    put(app, s + 0x24, player);
    put(app, s + 0x18, kept.ecx);
    put(app, at(app, kept.esp + 0xc), 0x52a3a0);
    put(app, at(app, kept.esp + 0x10), 0);
    kept.ret(cpu, 0x98, 0x10);
}

/* 0x51f750, 0x51f850 (cdecl: state, the add's slot, the volume's slot): a
 * mono and a stereo source's volume functions, MMX. */
void volumeMonoSetup(App* app, CPU& cpu)
{
    const reg32 state = at(app, cpu.esp + 4), add = at(app, cpu.esp + 8), volume = at(app, cpu.esp + 0xc);
    put(app, state + 0x10, add);
    put(app, add, 0x51f7ad);
    put(app, state + 0x14, volume);
    put(app, volume, 0x51f774);
    cpu.esp += 4;
}

void volumeStereoSetup(App* app, CPU& cpu)
{
    const reg32 state = at(app, cpu.esp + 4), add = at(app, cpu.esp + 8), volume = at(app, cpu.esp + 0xc);
    put(app, state + 8, add);
    put(app, add, 0x51f897);
    put(app, state + 0xc, volume);
    put(app, volume, 0x51f874);
    cpu.esp += 4;
}

/* 0x5203a0, 0x5207e4 (cdecl: state, the step setter's slot, the frames
 * needed's, the resampler's): a mono and a stereo resampler, MMX, their step
 * setter given.  0. */
void resampleMonoSetup(App* app, CPU& cpu)
{
    const reg32 s = at(app, cpu.esp + 4);
    put(app, s, 0);
    put(app, s + 4, 0);
    putByte(app, s + 0x10, 0);
    putHalf(app, s + 0xe, 0);
    putByte(app, s + 0x11, 0);
    putByte(app, s + 0x12, 1);
    put(app, s + 0x14, at(app, cpu.esp + 8));
    put(app, s + 0x18, at(app, cpu.esp + 0xc));
    put(app, s + 0x1c, at(app, cpu.esp + 0x10));
    put(app, at(app, s + 0x14), 0x5202fc);
    cpu.edx = at(app, cpu.esp + 0x10);
    cpu.eax = 0;
    cpu.esp += 4;
}

void resampleStereoSetup(App* app, CPU& cpu)
{
    const reg32 s = at(app, cpu.esp + 4);
    put(app, s, 0);
    put(app, s + 4, 0);
    putByte(app, s + 0x14, 0);
    putByte(app, s + 0x15, 0);
    putByte(app, s + 0x16, 0);
    put(app, s + 0x18, at(app, cpu.esp + 8));
    put(app, s + 0x1c, at(app, cpu.esp + 0xc));
    put(app, s + 0x20, at(app, cpu.esp + 0x10));
    put(app, at(app, s + 0x18), 0x520740);
    cpu.edx = at(app, cpu.esp + 0x10);
    cpu.eax = 0;
    cpu.esp += 4;
}

namespace
{

/* The step setters: the step (16.16) kept, the history dropped when it
 * crosses 1 (or, from past 1, comes back to it or under); the resampler and
 * its frames-needed by the step against 1 -- under, at, over. */
void setStep(App* app, CPU& cpu, reg32 flags, reg32 slots, const reg32 (&under)[2], const reg32 (&at1)[2],
             const reg32 (&over)[2])
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(2);
    const reg32 s = at(app, kept.esp + 4), step = at(app, kept.esp + 8);
    const reg32 old = at(app, s + 8);
    const bool keep = (old < 0x10000 && step < 0x10000) || step == old || (old > 0x10000 && step > 0x10000);
    if (!keep)
    {
        putByte(app, s + flags, 0);
        putByte(app, s + flags + 1, 0);
        putByte(app, s + flags + 2, 0);
        put(app, s + 4, 0);
        put(app, s, 0);
    }
    put(app, s + 8, step);
    const reg32(&pick)[2] = step < 0x10000 ? under : step == 0x10000 ? at1 : over;
    put(app, at(app, s + slots), pick[0]);
    put(app, at(app, s + slots + 4), pick[1]);
    kept.ret(cpu, 0);
    cpu.ecx = s;
    cpu.edx = at(app, s + slots);
}

}  // namespace

/* 0x5202fc (cdecl: state, step): the mono resampler by its step. */
void resampleMonoStep(App* app, CPU& cpu)
{
    setStep(app, cpu, 0x10, 0x18, {0x5200c0, 0x5201e4}, {0x5200b8, 0x5201d8}, {0x520070, 0x5200ec});
}

/* 0x520740 (cdecl: state, step): the stereo resampler by its step. */
void resampleStereoStep(App* app, CPU& cpu)
{
    setStep(app, cpu, 0x14, 0x1c, {0x520440, 0x5205bc}, {0x520438, 0x5205b0}, {0x5203f0, 0x52046c});
}

namespace
{

struct Set
{
    reg32 at, value;
};

void store(App* app, std::initializer_list<Set> sets)
{
    for (const Set& s : sets)
        put(app, s.at, s.value);
}

}  // namespace

/* 0x521d80, 0x521e60: the PCM decoders' set-ups' tables, by MMX. */
void pcmTablesFirst(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    if (at(app, 0x5643b4) != 0)
        store(app, {{0x9f6a6c, 0x5274b0}, {0x9f6a70, 0x5274d0}, {0x9f6a74, 0x527500}, {0x9f6a78, 0x527520},
                    {0x9f6a7c, 0x527540}, {0x9f6a80, 0x527560}, {0x9f6a84, 0x527590}, {0x9f6a88, 0x5275b0}});
    else
    {
        cpu.esp = kept.frame(6);
        if (!call(app, cpu, 0x522100))
            return;
        store(app, {{0x9f6a6c, 0x5275d0}, {0x9f6a70, 0x5275f0}, {0x9f6a74, 0x527620}, {0x9f6a78, 0x527640},
                    {0x9f6a7c, 0x527660}, {0x9f6a80, 0x527680}, {0x9f6a84, 0x5276b0}, {0x9f6a88, 0x5276d0}});
    }
    kept.ret(cpu, 0);
}

void pcmTablesSecond(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    if (at(app, 0x5643b4) != 0)
        store(app, {{0x9f6a8c, 0x5276f0}, {0x9f6a90, 0x527710}, {0x9f6a94, 0x527740}, {0x9f6a98, 0x527760},
                    {0x9f6a9c, 0x527780}, {0x9f6aa0, 0x5277a0}, {0x9f6aa4, 0x5277d0}, {0x9f6aa8, 0x5277f0}});
    else
        store(app, {{0x9f6a8c, 0x527810}, {0x9f6a90, 0x527840}, {0x9f6a94, 0x527870}, {0x9f6a98, 0x527890},
                    {0x9f6a9c, 0x5278b0}, {0x9f6aa0, 0x5278e0}, {0x9f6aa4, 0x527910}, {0x9f6aa8, 0x527930}});
    kept.ret(cpu, 0);
}

/* 0x521f30: the XA float table: for each of 13 shifts, the 16 nibbles
 * (signed, at the top of a word) shifted down, as floats, at 0xa0baa0. */
void xaFloatTable(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 f = kept.frame(4, 4);
    for (reg32 shift = 0; shift < 0xd; ++shift)
        for (reg32 k = 0; k < 0x10; ++k)
        {
            const i32 v = (i32(k << 28) >> 16) >> shift;
            put(app, f, reg32(v));
            cpu.fpu.push(x86::Float(v));
            app->getMemory<float>(0xa0baa0 + shift * 0x40 + 4 * k) = float(cpu.fpu.st(0));
            cpu.fpu.pop();
        }
    kept.ret(cpu, 0x340);
    cpu.ecx = (kept.ecx & 0xffffff00) | 0xc;
    cpu.edx = 0;
}

/* 0x521f7c: the XA integer table: the same, times 256, at 0xa0bea0. */
void xaIntTable(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    for (reg32 shift = 0; shift < 0xd; ++shift)
        for (reg32 k = 0; k < 0x10; ++k)
            put(app, 0xa0bea0 + shift * 0x40 + 4 * k, reg32(((i32(k << 28) >> 16) >> shift) << 8));
    kept.ret(cpu, 0x340);
    cpu.ecx = (kept.ecx & 0xffffff00) | 0xc;
    cpu.edx = 0;
}

/* 0x521fc0: the XA decoders' set-ups' table, its tables first. */
void xaTables(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(6);
    if (!call(app, cpu, 0x521f30))
        return;
    if (at(app, 0x5643b4) != 0)
    {
        if (!call(app, cpu, 0x521f7c))
            return;
        store(app, {{0x9f6aac, 0x529104}, {0x9f6ab0, 0x529534}, {0x9f6ab4, 0x529778}, {0x9f6ab8, 0x5299f4},
                    {0x9f6abc, 0x529c2c}, {0x9f6ac0, 0x52a144}, {0x9f6ac4, 0x52a354}, {0x9f6ac8, 0x52a5b4}});
    }
    else
        store(app, {{0x9f6aac, 0x527ae8}, {0x9f6ab0, 0x527f20}, {0x9f6ab4, 0x52813c}, {0x9f6ab8, 0x5283a4},
                    {0x9f6abc, 0x5285b8}, {0x9f6ac0, 0x528a98}, {0x9f6ac4, 0x528cac}, {0x9f6ac8, 0x528f0c}});
    kept.ret(cpu, 0);
}

/* 0x5220a0: the last of the decoders' set-ups' tables. */
void lastTables(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    if (at(app, 0x5643b4) != 0)
        store(app, {{0x9f6acc, 0x52a790}, {0x9f6ad4, 0x52a970}, {0x9f6ad8, 0x52ab70}});
    else
        store(app, {{0x9f6acc, 0x52ad28}, {0x9f6ad4, 0x52af30}, {0x9f6ad8, 0x52b160}});
    kept.ret(cpu, 0);
}

/* 0x5230b8: the reverb's start: its send cleared, its tail run out (500). */
void reverbStart(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(2);
    cpu.edx = 0x1f4;
    put(app, 0xa0d2a0, 0x1f4);
    if (!call(app, cpu, at(app, 0x9f6a5c), {0xa0caa0, 0x200}))
        return;
    kept.ret(cpu, cpu.eax);
}

}  // namespace snd
}  // namespace nfs3hp
