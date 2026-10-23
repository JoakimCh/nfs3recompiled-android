#include "native_snd.h"

/* EA's SNDSTRM (cmn\sst.c, cmn\sstrstat.c) and the packet player under it
 * (cmn\spktplay.c), native (native_snd.cpp says how): what plays a movie's
 * sound.  The movie's reader hands its chunks -- headers, data, loops, ends --
 * to a stream as requests; the stream's system task parses them, a header
 * starting the packet player on a voice, each data chunk submitted to it as a
 * packet the mixer plays; the packets played and done with are given back
 * through the stream's callbacks.
 *
 * A stream (16 at 0x9f254c): +0 its requests (0x2c bytes each), +4 its
 * queue (the chunks' reader), +8 the packet player's voice handle, +0xc its
 * packet player, +0x10 the requests' serial, +0x14 the player's state (0
 * stopped, 1 playing, 2 a new header waiting), +0x15 the requests it takes,
 * +0x16 those it holds, +0x17 the one playing, +0x18 whether the queue is the
 * caller's, +0x1c the header playing, +0x20 the header parsed, +0x24 and +0x30
 * their play's settings (12 bytes), +0x3c the play's options.  A request: +0
 * its chunks, +4 its handle (the serial and the stream's index), +8 and +0xc
 * the submission's results, +0x10 its data rate, +0x14 the frames played, +0x18
 * its frames, +0x1c the frames submitted, +0x20 the packets submitted, +0x24
 * the loop, +0x28 the time it waits for (a word).
 *
 * A packet player (16 at 0xa0b044): +0 its voice's handle (-1 stopped), +4
 * the packets' serial, +8 the ring's packets, +0xa its head, +0xc the packet
 * playing (-1 none), +0xe the packets in it, +0x10 the frames submitted, +0x14
 * those the hardware holds, +0x18 its memory, +0x1c the packets' free
 * callback, +0x20 the frames' callback, +0x24 the header, +0x28 the ring: 12
 * bytes a packet -- its serial, frames and data. */
namespace nfs3hp
{
namespace snd
{

namespace
{

constexpr reg32 kStreams = 0x9f254c;        // the 16 streams
constexpr reg32 kPlayerStream = 0x9f258c;   // bytes: each packet player's stream
constexpr reg32 kPlayers = 0xa0b044;        // the 16 packet players
constexpr reg32 kRequestSize = 0x2c;
constexpr reg32 kSstFile = 0x54ccb4, kPktFile = 0x54fdc0;
constexpr reg32 kEnter = 0x500e20, kLeave = 0x500e7c;
constexpr reg32 kFindStream = 0x4f3aa4, kStreamCount = 0x4f3fd0, kRemoveRequest = 0x4f3ab8;
constexpr reg32 kStreamTask = 0x4f3ebc, kStreamRestore = 0x4f3a90;
constexpr reg32 kStreamerRestore = 0xa09b30;   // the restore SNDrestore calls
constexpr reg32 kFreeChunk = 0x4d03c0, kNextChunk = 0x4d0300;
constexpr reg32 kMul64 = 0x503670, kDiv64 = 0x503760;
constexpr reg32 kIdData = 0x6c444353, kIdHeader = 0x6c484353, kIdEnd = 0x6c454353, kIdLoop = 0x6c434353;

reg32 player(App* app, reg32 index) { return at(app, kPlayers + 4 * index); }

/* The request a stream plays. */
reg32 playingRequest(App* app, reg32 s)
{
    return at(app, s) + reg32(sbyte(app, s + 0x17)) * kRequestSize;
}

bool ask(App* app, CPU& cpu, reg32 target, reg32 eax, reg32& result)
{
    if (!callWith(app, cpu, target, eax))
        return false;
    result = cpu.eax;
    return true;
}

}  // namespace

/* 0x503670 (__U8M): eax times edx, unsigned, into the 8 bytes at esi; eax
 * the place.  esi left at the frame's copy, as its movsd leaves it. */
void mul64(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 to = cpu.esi;
    const std::uint64_t product = std::uint64_t(cpu.eax) * cpu.edx;
    put(app, to, reg32(product));
    put(app, to + 4, reg32(product >> 32));
    const reg32 frame = kept.frame(4, 0xc);
    put(app, frame, reg32(product));
    put(app, frame + 4, reg32(product >> 32));
    put(app, frame + 8, cpu.edx & 0xffff);
    kept.ret(cpu, to);
    cpu.esi = frame + 8;
}

/* 0x503760 (__U8D, stdcall 12): the 64 bits [esp+8]:[esp+4] over [esp+0xc]
 * as its shifts divide them -- 32 bits of quotient, the high part's overflow
 * lost. */
void div64(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    reg32 low = at(app, kept.esp + 4), high = at(app, kept.esp + 8);
    const reg32 divisor = at(app, kept.esp + 0xc);
    reg32 quotient = 0;
    for (int i = 0; i < 32; ++i)
    {
        high = high + high + (low >> 31);
        low += low;
        quotient += quotient;
        if (high >= divisor)
        {
            ++quotient;
            high -= divisor;
        }
    }
    kept.ret(cpu, quotient, 0xc);
}

/* 0x523d90 (iSNDplatformpacketsize): no memory of the platform's. */
void platformPacketSize(App*, CPU& cpu)
{
    cpu.eax = 0;
    cpu.esp += 4;
}

/* 0x4f3aa4: stream eax (0..15), 0 for none. */
void findStream(App* app, CPU& cpu)
{
    cpu.eax = i32(cpu.eax) >= 0 && i32(cpu.eax) < 0x10 ? at(app, kStreams + 4 * cpu.eax) : 0;
    cpu.esp += 4;
}

/* 0x4f3ab5: iSNDstreamsystemtask's way out while a surface is locked:
 * 0. */
void streamTaskSkipped(App*, CPU& cpu)
{
    cpu.eax = 0;
    cpu.esp += 4;
}

/* 0x4f3b31: framesPlayed's way out, by a jump: ecx and ebx popped. */
void framesPlayedDone(App* app, CPU& cpu)
{
    cpu.ecx = at(app, cpu.esp);
    cpu.ebx = at(app, cpu.esp + 4);
    cpu.esp += 12;
}

/* 0x4f3fd0: the streams there are. */
void streamCount(App* app, CPU& cpu)
{
    reg32 n = 0;
    for (reg32 i = 0; i < 0x10; ++i)
        if (at(app, kStreams + 4 * i) != 0)
            ++n;
    cpu.eax = n;
    cpu.esp += 4;
}

/* 0x510a10: the request of handle eax, 0 for none. */
void findRequest(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 handle = cpu.eax;
    cpu.esp = kept.frame(4);
    reg32 result = 0;
    if (i32(handle) >= 0)
    {
        reg32 s;
        if (!ask(app, cpu, kFindStream, handle & 0xff, s))
            return;
        if (s != 0)
            for (i32 i = 0; i < sbyte(app, s + 0x16); ++i)
            {
                const reg32 r = at(app, s) + reg32(i) * kRequestSize;
                if (at(app, r + 4) == handle)
                {
                    result = r;
                    break;
                }
            }
    }
    kept.ret(cpu, result);
}

/* 0x4f2f50 (SNDSTRM_requeststatus): request eax's state into the 4 words at
 * edx -- 3 gone, 2 playing, 1 waiting, 0 not started -- with the ms it has
 * played and has left and those buffered.  0; -10 before SNDinit, -8 for no
 * stream. */
void SNDSTRM_requeststatus(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 handle = cpu.eax, out = cpu.edx;
    const reg32 f = kept.frame(3, 0x10);
    cpu.esp = f;
    for (reg32 i = 0; i < 0x10; i += 4)
        put(app, out + i, 0);
    if (byte(app, kInited) == 0)
    {
        kept.ret(cpu, 0xfffffff6);
        return;
    }
    if (i32(handle) < 0)
    {
        kept.ret(cpu, 0xfffffff8);
        return;
    }
    reg32 s;
    if (!ask(app, cpu, kFindStream, handle & 0xff, s))
        return;
    if (s == 0)
    {
        kept.ret(cpu, 0xfffffff8);
        cpu.edx = 0;
        return;
    }
    cpu.edx = s;
    cpu.esp = f - 4;
    if (!call(app, cpu, kEnter))
        return;
    reg32 r;
    if (!ask(app, cpu, 0x510a10, handle, r))
        return;
    // The ret: edx as the code leaves it.
    auto done = [&](reg32 eax) {
        if (!call(app, cpu, kLeave))
            return;
        const reg32 edx = cpu.edx;
        kept.ret(cpu, eax);
        cpu.edx = edx;
    };
    if (r == 0)
    {
        put(app, out, 3);
        return done(0);
    }
    if (s32(app, r + 8) < 0)
    {
        put(app, out, 0);
        return done(0);
    }
    reg32 rate;
    if (r == at(app, s))
    {
        put(app, out, 2);
        rate = half(app, s + 0x1c);
    }
    else
    {
        put(app, out, 1);
        rate = half(app, s + 0x20);
    }
    // ms = frames * 1000 / rate, in 64 bits: the played, then the left.
    cpu.esp = f - 0xc;
    put(app, f - 8, cpu.esi);
    put(app, f - 0xc, rate);
    cpu.esi = f + 8;
    if (!callWith(app, cpu, kMul64, at(app, r + 0x14), 1000))
        return;
    // The divisor is the word pushed for it: the 64 bits pushed below it.
    if (!call(app, cpu, kDiv64, {at(app, f + 8), at(app, f + 0xc)}))
        return;
    put(app, out + 4, cpu.eax);
    cpu.esp = f - 0xc;
    put(app, f - 0xc, rate);
    cpu.esi = f;
    if (!callWith(app, cpu, kMul64, at(app, r + 0x18) - at(app, r + 0x14), 1000))
        return;
    if (!call(app, cpu, kDiv64, {at(app, f), at(app, f + 4)}))
        return;
    put(app, out + 8, cpu.eax);
    cpu.esp = f - 8;
    if (at(app, r + 0x1c) > 0x3d0900
        && !fail(app, cpu, f - 8, 0x54cc50, 0x54cc60, 0x9b, {0x54cc78}))
        return;
    const reg32 buffered = at(app, r + 0x1c) * 1000;
    put(app, out + 0xc, buffered / rate);
    cpu.edx = buffered % rate;
    cpu.esi = at(app, f - 8);
    cpu.esp = f - 4;
    done(0);
}

/* 0x4f3a10: the memory a stream of eax requests with a packet player of edx
 * packets takes.  edx left as the requests' part. */
void streamMemory(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 requests = cpu.eax * kRequestSize + 0x4c;
    cpu.esp = kept.frame(1);
    if (!callWith(app, cpu, 0x511210, kept.edx))
        return;
    kept.ret(cpu, cpu.eax + requests);
    cpu.edx = requests;
}

/* 0x511210: the memory a packet player of eax packets takes. */
void playerMemory(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 size = cpu.eax * 0xc + 0x34;
    cpu.esp = kept.frame(1);
    if (!call(app, cpu, 0x523d90))
        return;
    kept.ret(cpu, cpu.eax + size);
}

/* 0x4f3a60 (SNDSTRM_create...): iSNDstreamcreate with the queue eax given
 * (its arguments edx, ebx, ecx, [esp+4]; the memory's size [esp+8]).  stdcall 8. */
void SNDSTRM_createqueued(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 queue = cpu.eax;
    cpu.esp = kept.frame(1);
    cpu.eax = kept.edx;
    cpu.edx = kept.ebx;
    cpu.ebx = kept.ecx;
    cpu.ecx = at(app, kept.esp + 4);
    if (!call(app, cpu, 0x4f3fec, {at(app, kept.esp + 8), queue, 1}))
        return;
    const reg32 ebx = cpu.ebx, ecx = cpu.ecx, edx = cpu.edx;
    kept.ret(cpu, cpu.eax, 8);
    cpu.ebx = ebx;
    cpu.ecx = ecx;
    cpu.edx = edx;
}

/* 0x4f3a80 (SNDSTRM_request...): a request of chunks ebx given whole. */
void SNDSTRM_requestdata(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(1);
    cpu.ecx = cpu.ebx;
    cpu.ebx = 0;
    if (!call(app, cpu, 0x4f4258, {2}))
        return;
    const reg32 ebx = cpu.ebx, edx = cpu.edx;
    kept.ret(cpu, cpu.eax);
    cpu.ebx = ebx;
    cpu.edx = edx;
}

/* 0x4f3a90: every stream destroyed (the streams' restore). */
void SNDSTRM_restore(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(1);
    for (reg32 i = 0; i < 0x10; ++i)
    {
        cpu.edx = i + 1;
        if (!callWith(app, cpu, 0x4f43c0, i))
            return;
    }
    kept.ret(cpu, 0);
}

/* 0x4f3ab8: request eax taken out of its stream, the rest moved up. */
void removeRequest(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 handle = cpu.eax;
    const reg32 s = at(app, kStreams + 4 * (handle & 0xff));
    reg32 kept_ = 0, to = 0, from = 0;
    for (i32 i = 0; i < sbyte(app, s + 0x16); ++i, from += kRequestSize)
    {
        const reg32 r = at(app, s) + from;
        if (at(app, r + 4) == handle)
            continue;
        if (sbyte(app, s + 0x17) == i)
            putByte(app, s + 0x17, reg8(kept_));
        const reg32 d = at(app, s) + to;
        for (reg32 k = 0; k < kRequestSize; k += 4)
            put(app, d + k, at(app, r + k));
        ++kept_;
        to += kRequestSize;
    }
    putByte(app, s + 0x16, reg8(byte(app, s + 0x16) - 1));
    if (sbyte(app, s + 0x17) > sbyte(app, s + 0x16))
        putByte(app, s + 0x17, reg8(byte(app, s + 0x17) - 1));
    kept.ret(cpu, s);
}

/* 0x4f3b44: the packet player's free callback: the chunk of the packet's
 * data at eax given back to its stream's queue. */
void packetFreed(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 chunk = cpu.eax - 0xc;
    cpu.esp = kept.frame(1);
    const reg32 s = at(app, kStreams + 4 * (at(app, chunk) & 0xff));
    if (!callWith(app, cpu, kFreeChunk, at(app, s + 4), chunk))
        return;
    kept.ret(cpu, cpu.eax);
}

/* 0x4f3b60: the packet player's frames callback: edx frames of player eax
 * played, counted off its stream's requests -- each played through taken out. */
void framesPlayed(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(2);
    const reg32 s = at(app, kStreams + 4 * reg32(sbyte(app, kPlayerStream + cpu.eax)));
    reg32 frames = cpu.edx, over = 0;
    for (;;)
    {
        const reg32 r = at(app, s);
        cpu.eax = r;
        if (frames > at(app, r + 0x1c))
        {
            over = frames - at(app, r + 0x1c);
            frames -= over;
        }
        put(app, r + 0x14, at(app, r + 0x14) + frames);
        put(app, r + 0x1c, at(app, r + 0x1c) - frames);
        cpu.edx = at(app, r + 0x14);
        if (at(app, r + 0x14) >= at(app, r + 0x18))
        {
            cpu.ebx = s;
            cpu.ecx = over;
            if (!callWith(app, cpu, kRemoveRequest, at(app, r + 4)))
                return;
        }
        if (over == 0)
            break;
        frames = over;
        cpu.edx = over;
        over = 0;
    }
    const reg32 eax = cpu.eax, edx = cpu.edx;
    kept.ret(cpu, eax);
    cpu.edx = edx;
}

/* 0x4f3ba4 (iSNDstreamparseheader): stream eax's header chunk edx: its patch
 * made the request's header and data rate; a first header starts the packet
 * player, another of a different format waits for it to stop (2).  0. */
void iSNDstreamparseheader(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 s = cpu.eax, chunk = cpu.edx;
    const reg32 f = kept.frame(5, 0xc);
    cpu.esp = f;
    const reg32 r = playingRequest(app, s);
    put(app, f, r);
    put(app, f + 8, s + 0x30);
    if (!callWith(app, cpu, 0x5119d8, chunk + 8, s + 0x20, s + 0x30, f + 4))
        return;
    put(app, r + 0x18, at(app, f + 4));
    if (!callWith(app, cpu, kFreeChunk, at(app, s + 4), chunk))
        return;
    cpu.edx = r;
    if (!callWith(app, cpu, 0x511bf0, s + 0x20))
        return;
    put(app, r + 0x10, cpu.eax);
    bool same = true;
    for (reg32 i = 0; i < 4 && same; ++i)
        same = byte(app, s + 0x1c + i) == byte(app, s + 0x20 + i);
    for (reg32 i = 0; i < 12 && same; ++i)
        same = byte(app, s + 0x24 + i) == byte(app, s + 0x30 + i);
    if (!same)
    {
        if (half(app, s + 0x1c) != 0)
        {
            putByte(app, s + 0x14, 2);
            const reg32 edx = cpu.edx;
            kept.ret(cpu, 0);
            cpu.edx = edx;
            return;
        }
        put(app, s + 0x1c, at(app, s + 0x20));
        for (reg32 i = 0; i < 12; i += 4)
            put(app, s + 0x24 + i, at(app, s + 0x30 + i));
    }
    if (byte(app, s + 0x14) != 1)
    {
        if (!callWith(app, cpu, 0x5112d0, at(app, s + 0xc), s + 0x1c, s + 0x24, s + 0x3c))
            return;
        put(app, s + 8, cpu.eax);
        if (s32(app, s + 8) < 0)
        {
            cpu.ecx = kSstFile;
            cpu.ebx = 0x54ccc0;
            cpu.esi = 0x115;
            if (!fail(app, cpu, f, kSstFile, 0x54ccc0, 0x115, {0x54ccd8}))
                return;
        }
        putByte(app, s + 0x14, 1);
    }
    const reg32 edx = cpu.edx;
    kept.ret(cpu, 0);
    cpu.edx = edx;
}

/* 0x4f3cc8: stream eax's loop chunk edx: its count the request's loop.  1. */
void iSNDstreamparseloop(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 s = cpu.eax, chunk = cpu.edx;
    cpu.esp = kept.frame(2);
    cpu.ecx = s;
    cpu.ebx = chunk + 8;
    if (!callWith(app, cpu, kFreeChunk, at(app, s + 4), chunk))
        return;
    const reg32 r = playingRequest(app, s);
    put(app, r + 0x24, at(app, chunk + 8));
    kept.ret(cpu, 1);
    cpu.edx = r;
}

/* 0x4f3d00 (iSNDstreamparsedata): stream eax's data chunk edx submitted to
 * its packet player as a packet -- the chunk marked with the request's
 * handle, its frames counted.  1. */
void iSNDstreamparsedata(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 s = cpu.eax, chunk = cpu.edx;
    const reg32 f = kept.frame(3, 0x10);
    cpu.esp = f;
    cpu.ebx = s;
    put(app, f + 4, at(app, chunk + 8));
    put(app, f + 0xc, chunk + 0xc);
    const reg32 r = playingRequest(app, s);
    cpu.ecx = r;
    put(app, chunk, at(app, r + 4));
    put(app, r + 0x1c, at(app, r + 0x1c) + at(app, f + 4));
    put(app, r + 0x20, at(app, r + 0x20) + 1);
    if (!callWith(app, cpu, 0x5114d4, at(app, s + 0xc), f))
        return;
    put(app, r + 0xc, cpu.eax);
    if (s32(app, r + 0xc) < 0)
    {
        cpu.eax = 0x54cd14;
        cpu.edx = 0x158;
        if (!fail(app, cpu, f, kSstFile, 0x54cd14, 0x158, {0x54cd28, at(app, r + 0xc)}))
            return;
    }
    if (s32(app, r + 8) < 0)
        put(app, r + 8, at(app, r + 0xc));
    const reg32 edx = cpu.edx;
    kept.ret(cpu, 1);
    cpu.edx = edx;
}

/* 0x4f3dac: stream eax's end chunk edx: the next request plays.  1. */
void iSNDstreamparseend(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 s = cpu.eax;
    cpu.esp = kept.frame(1);
    cpu.ecx = s;
    if (!callWith(app, cpu, kFreeChunk, at(app, s + 4), cpu.edx))
        return;
    putByte(app, s + 0x17, reg8(byte(app, s + 0x17) + 1));
    const reg32 edx = cpu.edx;
    kept.ret(cpu, 1);
    cpu.edx = edx;
}

/* 0x4f3dc4: stream eax's chunk edx handed on by its id; another given back.
 * What the handler gave (1 for another). */
void iSNDstreamparsechunk(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 s = cpu.eax, chunk = cpu.edx;
    cpu.esp = kept.frame(2);
    const reg32 id = at(app, chunk);
    cpu.ebx = id;
    cpu.ecx = 1;
    reg32 target = 0;
    if (id == kIdData)
        target = 0x4f3d00;
    else if (id == kIdHeader)
        target = 0x4f3ba4;
    else if (id == kIdEnd)
        target = 0x4f3dac;
    else if (id == kIdLoop)
        target = 0x4f3cc8;
    if (target != 0)
    {
        if (!callWith(app, cpu, target, s, chunk))
            return;
    }
    else
    {
        if (!callWith(app, cpu, kFreeChunk, at(app, s + 4), chunk))
            return;
        cpu.eax = 1;
    }
    const reg32 edx = cpu.edx;
    kept.ret(cpu, cpu.eax);
    cpu.edx = edx;
}

/* 0x4f3e1c: whether stream eax waits before it parses on: for the time its
 * request waits for, while the queue holds less -- unless the queue is done
 * (2).  1 to wait. */
void streamWaits(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 s = cpu.eax;
    cpu.esp = kept.frame(3);
    const reg32 r = playingRequest(app, s);
    reg32 result = 0;
    if (at(app, r + 0x10) != 0 && shalf(app, r + 0x28) != 0)
    {
        if (shalf(app, r + 0x28) < 0)
            result = 1;
        else
        {
            cpu.ebx = s;
            cpu.ecx = r;
            reg32 bytes;
            if (!ask(app, cpu, 0x4d0460, at(app, s + 4), bytes))
                return;
            if (bytes > 0x3d0900)
                bytes = 0x3d0900;
            const reg32 time = bytes * 1000 / at(app, r + 0x10);
            if (time >= reg32(shalf(app, r + 0x28)))
                putHalf(app, r + 0x28, 0);
            else
            {
                if (!callWith(app, cpu, 0x4d0490, at(app, s + 4)))
                    return;
                if ((cpu.eax & 0xff) != 2)
                    result = 1;
                else
                    putHalf(app, r + 0x28, 0);
            }
        }
    }
    kept.ret(cpu, result);
}

/* 0x4f3ebc (iSNDstreamsystemtask): each stream with requests served: a new
 * header's player started once the old one has played out, then (unless it
 * waits) its queue's chunks parsed -- 10 at most, or as many as the player
 * has room for.  0; nothing while a surface is locked. */
void iSNDstreamsystemtask(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    if (!call(app, cpu, kSurfaceLocked))
        return;
    if (cpu.eax != 0)
    {
        kept.ret(cpu, 0);
        return;
    }
    cpu.esp = kept.frame(4);
    for (reg32 i = 0; i < 0x10; ++i)
    {
        safepoint(app, cpu);
        const reg32 s = at(app, kStreams + 4 * i);
        cpu.edi = 4 * i;
        cpu.esi = s;
        if (s == 0 || byte(app, s + 0x16) == 0)
            continue;
        if (byte(app, s + 0x14) == 2)
        {
            reg32 left;
            if (!ask(app, cpu, 0x511680, at(app, s + 0xc), left))
                return;
            if (i32(left) > 0)
                continue;
            put(app, s + 0x1c, at(app, s + 0x20));
            if (!callWith(app, cpu, 0x51181c, at(app, s + 0xc), s + 0x1c, s + 0x24, s + 0x3c)
                || !callWith(app, cpu, 0x5112d0, at(app, s + 0xc)))
                return;
            put(app, s + 8, cpu.eax);
            if (s32(app, s + 8) < 0)
            {
                cpu.ecx = kSstFile;
                cpu.ebx = 0x54cd5c;
                cpu.eax = 0x235;
                if (!fail(app, cpu, kept.frame(4), kSstFile, 0x54cd5c, 0x235, {0x54cd74}))
                    return;
            }
            putByte(app, s + 0x14, 1);
        }
        reg32 waits;
        if (!ask(app, cpu, 0x4f3e1c, s, waits))
            return;
        if (waits != 0)
            continue;
        if (byte(app, s + 0x14) == 1)
        {
            if (!ask(app, cpu, 0x5115b8, at(app, s + 0xc), cpu.ecx))
                return;
            if (cpu.ecx == 0)
                continue;
        }
        else
            cpu.ecx = 10;
        if (!call(app, cpu, kEnter))
            return;
        // edx cleared once: the loop goes back past it.
        cpu.edx = 0;
        for (;;)
        {
            safepoint(app, cpu);
            cpu.ecx -= 1;
            reg32 chunk;
            if (!ask(app, cpu, kNextChunk, at(app, s + 4), chunk))
                return;
            if (chunk != 0)
            {
                cpu.edx = chunk;
                reg32 handled;
                if (!ask(app, cpu, 0x4f3dc4, s, handled))
                    return;
                cpu.edx = handled;
            }
            if (cpu.edx == 0 || i32(cpu.ecx) <= 0)
                break;
        }
        if (!call(app, cpu, kLeave))
            return;
    }
    const reg32 edx = cpu.edx;
    kept.ret(cpu, 0);
    cpu.edx = edx;
}

/* 0x4f3fec (iSNDstreamcreate, stdcall 12): a stream of edx requests (1..127)
 * in memory ecx of [esp+4] bytes, its packet player of ebx packets, the play's
 * options at eax; its queue [esp+8] when [esp+0xc] says it is given, else one
 * made in the memory left.  The first stream adds the streams' task.  Its
 * index; -10 before SNDinit, -9 with 16 streams. */
void iSNDstreamcreate(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 f = kept.frame(3, 0x10);
    cpu.esp = f;
    const reg32 options = cpu.eax, requests = cpu.edx, packets = cpu.ebx, memory = cpu.ecx;
    reg32 size = at(app, kept.esp + 4);
    const reg32 queue = at(app, kept.esp + 8), given = at(app, kept.esp + 0xc);
    put(app, f + 4, options);
    put(app, f + 0xc, requests);
    if (byte(app, kInited) == 0)
    {
        kept.ret(cpu, 0xfffffff6, 0xc);
        return;
    }
    if (i32(requests) <= 0 || i32(requests) >= 0x80)
    {
        cpu.ecx = requests;
        cpu.eax = 0x54cdac;
        cpu.edx = 0x280;
        if (!fail(app, cpu, f, kSstFile, 0x54cdac, 0x280, {0x54cdc0, requests}))
            return;
    }
    if (memory == 0)
    {
        cpu.eax = 0x54cdac;
        cpu.edx = 0x285;
        if (!fail(app, cpu, f, kSstFile, 0x54cdac, 0x285, {0x54ce10}))
            return;
    }
    reg32 slot = 0;
    cpu.ecx = at(app, kStreams);
    if (cpu.ecx != 0)
        for (;;)
        {
            ++slot;
            if (slot >= 0x10)
            {
                cpu.eax = 0x40;
                cpu.edx = slot;
                kept.ret(cpu, 0xfffffff7, 0xc);
                cpu.edx = slot;
                return;
            }
            if (at(app, kStreams + 4 * slot) == 0)
                break;
        }
    put(app, f + 8, slot);
    const reg32 s = memory;
    const reg32 requestBytes = requests * kRequestSize;
    size -= 0x4c;
    reg32 free = memory + 0x4c;
    put(app, s, free);
    free += requestBytes;
    size -= requestBytes;
    cpu.edx = requests;
    reg32 playerBytes;
    if (!ask(app, cpu, 0x511210, packets, playerBytes))
        return;
    put(app, f, free);
    free += playerBytes;
    size -= playerBytes;
    cpu.ecx = 0x4f3b60;
    if (!ask(app, cpu, 0x511210, packets, playerBytes))
        return;
    cpu.ebx = 0x4f3b44;
    if (!callWith(app, cpu, 0x511228, at(app, f), playerBytes))
        return;
    put(app, s + 0xc, cpu.eax);
    if (s32(app, s + 0xc) < 0)
    {
        const reg32 ebx = cpu.ebx, ecx = cpu.ecx, edx = cpu.edx;
        kept.ret(cpu, at(app, s + 0xc), 0xc);
        cpu.ebx = ebx;
        cpu.ecx = ecx;
        cpu.edx = edx;
        return;
    }
    cpu.edx = (cpu.edx & 0xffffff00) | (slot & 0xff);
    putByte(app, kPlayerStream + at(app, s + 0xc), reg8(slot));
    if (given != 0)
    {
        if (i32(size) < 0)
        {
            cpu.edx = kSstFile;
            cpu.ecx = 0x54cdac;
            cpu.ebx = 0x2b5;
            if (!fail(app, cpu, f, kSstFile, 0x54cdac, 0x2b5, {0x54ce34}))
                return;
        }
        put(app, s + 4, queue);
        putByte(app, s + 0x18, 1);
    }
    else
    {
        if (i32(size) < 0x6000)
        {
            cpu.ecx = kSstFile;
            cpu.ebx = 0x54cdac;
            cpu.eax = 0x2c2;
            if (!fail(app, cpu, f, kSstFile, 0x54cdac, 0x2c2, {0x54ce34}))
                return;
        }
        cpu.ebx = 1;
        cpu.esp = f - 4;
        if (!callWith(app, cpu, 0x4cfa80, requests + 1, 1, 1, free, {size}))
            return;
        cpu.esp = f;
        put(app, s + 4, cpu.eax);
        putByte(app, s + 0x18, 0);
        if (!call(app, cpu, 0x4d0500))
            return;
        const reg32 third = reg32(quotient(i32(cpu.eax), 3));
        cpu.ebx = at(app, s + 4);
        if (!callWith(app, cpu, 0x511ca0, at(app, s + 4), third))
            return;
    }
    put(app, s + 0x10, 0);
    put(app, s + 8, 0xffffffff);
    putByte(app, s + 0x15, reg8(requests));
    for (reg32 i = 0; i < 0x10; i += 4)
        put(app, s + 0x3c + i, at(app, options + i));
    reg32 count;
    if (!ask(app, cpu, 0x4f3fd0, 0, count))
        return;
    if (count == 0)
    {
        cpu.ebx = 1;
        cpu.esi = kStreamRestore;
        if (!callWith(app, cpu, 0x4e7520, kStreamTask, 0))
            return;
        put(app, kStreamerRestore, kStreamRestore);
    }
    put(app, kStreams + 4 * slot, s);
    if (!callWith(app, cpu, 0x4f4440, slot))
        return;
    const reg32 ebx = cpu.ebx, ecx = cpu.ecx, edx = cpu.edx;
    kept.ret(cpu, slot, 0xc);
    cpu.ebx = ebx;
    cpu.ecx = ecx;
    cpu.edx = edx;
}

/* 0x4f4258 (iSNDstreamrequest, stdcall 4): a request on stream eax for time
 * edx: of ebx bytes at ecx -- [esp+4] 0 read from the queue, 1 read from it
 * whole, 2 the chunks given.  Its handle; -10 before SNDinit, -8 for no
 * stream, -13 when it is full, -1 for no chunks. */
void iSNDstreamrequest(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 f = kept.frame(3, 8);
    cpu.esp = f;
    const reg32 index = cpu.eax, time = cpu.edx, bytes = cpu.ebx, data = cpu.ecx;
    const reg32 how = at(app, kept.esp + 4);
    put(app, f + 4, index);
    put(app, f, time);
    cpu.ebx = data;
    cpu.ecx = how;
    auto ret = [&](reg32 eax) {
        const reg32 ebx = cpu.ebx, ecx = cpu.ecx, edx = cpu.edx;
        kept.ret(cpu, eax, 4);
        cpu.ebx = ebx;
        cpu.ecx = ecx;
        cpu.edx = edx;
    };
    if (byte(app, kInited) == 0)
        return ret(0xfffffff6);
    reg32 s;
    if (!ask(app, cpu, kFindStream, index, s))
        return;
    cpu.edx = s;
    if (s == 0)
        return ret(0xfffffff8);
    if (!call(app, cpu, kEnter))
        return;
    if (sbyte(app, s + 0x16) >= sbyte(app, s + 0x15))
    {
        if (!call(app, cpu, kLeave))
            return;
        return ret(0xfffffff3);
    }
    const reg32 r = at(app, s) + reg32(sbyte(app, s + 0x16)) * kRequestSize;
    if (how == 0 || how == 1)
    {
        cpu.ecx = kIdEnd;
        if (how == 1)
            cpu.ebx = 0;
        if (!callWith(app, cpu, how == 0 ? 0x4cfef0 : 0x4cffb0, at(app, s + 4), bytes))
            return;
        put(app, r, cpu.eax);
    }
    else
        put(app, r, data);
    if (at(app, r) == 0)
    {
        if (!call(app, cpu, kLeave))
            return;
        return ret(0xffffffff);
    }
    put(app, s + 0x10, at(app, s + 0x10) + 0x100);
    if (s32(app, s + 0x10) < 0)
        put(app, s + 0x10, 0);
    put(app, r + 4, at(app, s + 0x10) | index);
    putHalf(app, r + 0x28, reg16(time));
    putByte(app, s + 0x16, reg8(byte(app, s + 0x16) + 1));
    put(app, r + 0x10, 0);
    put(app, r + 8, 0xffffffff);
    put(app, r + 0xc, 0xffffffff);
    for (const reg32 at_ : {0x14u, 0x1cu, 0x20u, 0x24u})
        put(app, r + at_, 0);
    if (!call(app, cpu, kLeave))
        return;
    ret(at(app, r + 4));
}

/* 0x4f43c0 (SNDSTRM_destroy): stream eax purged and gone -- its packet player,
 * its queue when made here; the last takes the streams' task.  0; -10 before
 * SNDinit, -8 for no stream. */
void SNDSTRM_destroy(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 index = cpu.eax;
    cpu.esp = kept.frame(2);
    if (byte(app, kInited) == 0)
    {
        kept.ret(cpu, 0xfffffff6);
        return;
    }
    reg32 s;
    if (!ask(app, cpu, kFindStream, index, s))
        return;
    if (s == 0)
    {
        kept.ret(cpu, 0xfffffff8);
        return;
    }
    cpu.esp = kept.frame(3);
    cpu.ecx = s;
    cpu.edx = index;
    reg32 count;
    if (!callWith(app, cpu, 0x4f4440, index) || !ask(app, cpu, 0x4f3fd0, 0, count))
        return;
    if (count == 1)
    {
        cpu.esp = kept.frame(4);
        cpu.ebx = 0;
        if (!callWith(app, cpu, 0x4e75e0, kStreamTask))
            return;
        put(app, kStreamerRestore, 0);
        cpu.ebx = kept.ebx;
        cpu.esp = kept.frame(3);
    }
    if (!callWith(app, cpu, 0x5118d0, at(app, s + 0xc)))
        return;
    if (byte(app, s + 0x18) == 0 && !callWith(app, cpu, 0x4cfd30, at(app, s + 4)))
        return;
    put(app, kStreams + 4 * index, 0);
    kept.ret(cpu, 0);
}

/* 0x4f4440 (SNDSTRM_purge): stream eax's player stopped, its queue emptied
 * when made here, its requests and headers cleared.  0; -10 before SNDinit,
 * -8 for no stream. */
void SNDSTRM_purge(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(1);
    if (byte(app, kInited) == 0)
    {
        kept.ret(cpu, 0xfffffff6);
        return;
    }
    reg32 s;
    if (!ask(app, cpu, kFindStream, cpu.eax, s))
        return;
    if (s == 0)
    {
        kept.ret(cpu, 0xfffffff8);
        return;
    }
    cpu.ecx = s;
    if (s32(app, s + 8) >= 0 && !callWith(app, cpu, 0x51181c, at(app, s + 0xc)))
        return;
    put(app, s + 8, 0xffffffff);
    if (byte(app, s + 0x18) == 0 && !callWith(app, cpu, 0x4d0220, at(app, s + 4)))
        return;
    cpu.esp = kept.frame(3);
    putByte(app, s + 0x16, 0);
    putByte(app, s + 0x17, 0);
    putByte(app, s + 0x14, 0);
    for (const auto& part : {std::pair<reg32, reg32>{0x1c, 4}, {0x20, 4}, {0x24, 0xc}, {0x30, 0xc}})
        if (!callWith(app, cpu, 0x4e0640, s + part.first, 0, part.second))
            return;
    kept.ret(cpu, 0);
}

/* 0x511228 (SNDPKTPLAY_create): a packet player in memory eax of edx bytes,
 * its free callback ebx, its frames callback ecx.  Its index; -10 before
 * SNDinit, -9 with 16, -6 for the platform's memory. */
void SNDPKTPLAY_create(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 f = kept.frame(3, 8);
    cpu.esp = f;
    const reg32 memory = cpu.eax, size = cpu.edx, freed = cpu.ebx, frames = cpu.ecx;
    put(app, f + 4, freed);
    auto ret = [&](reg32 eax) {
        const reg32 ebx = cpu.ebx, ecx = cpu.ecx, edx = cpu.edx;
        kept.ret(cpu, eax);
        cpu.ebx = ebx;
        cpu.ecx = ecx;
        cpu.edx = edx;
    };
    if (byte(app, kInited) == 0)
        return ret(0xfffffff6);
    cpu.edx = at(app, kPlayers);
    cpu.ebx = 0;
    cpu.ecx = 0;
    if (cpu.edx != 0)
        for (;;)
        {
            cpu.ecx += 4;
            cpu.ebx += 1;
            if (cpu.ecx >= 0x40)
                return ret(0xfffffff7);
            if (at(app, kPlayers + cpu.ecx) == 0)
                break;
        }
    cpu.edx = memory;
    if (!callWith(app, cpu, 0x523d90, cpu.ebx))
        return;
    if (i32(cpu.eax) < 0)
        return ret(0xfffffffa);
    if (!call(app, cpu, 0x523d90))
        return;
    put(app, f, memory);
    const reg32 p = memory + cpu.eax;
    cpu.edx = 0;
    if (!call(app, cpu, 0x523d90))
        return;
    const reg32 left = size - cpu.eax;
    put(app, kPlayers + cpu.ecx, p);
    cpu.ecx = 0xc;
    putHalf(app, p + 8, reg16((left - 0x34) / 0xc));
    cpu.edx = (left - 0x34) % 0xc;
    put(app, p + 0x20, frames);
    put(app, p + 0x18, at(app, f));
    put(app, p + 0x1c, at(app, f + 4));
    put(app, p, 0xffffffff);
    ret(cpu.ebx);
}

/* 0x5112d0 (SNDPKTPLAY_start): packet player eax started on a voice -- its
 * header at edx, the patch's settings at ebx, the play's options at ecx: the
 * voice set up as the patch has it and the platform's packet play started.
 * The voice's handle; -10 before SNDinit, -9 for no voice, the platform's
 * error. */
void SNDPKTPLAY_start(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 f = kept.frame(3, 0x10);
    cpu.esp = f;
    const reg32 index = cpu.eax, header = cpu.edx, settings = cpu.ebx, options = cpu.ecx;
    put(app, f + 8, index);
    put(app, f + 4, header);
    put(app, f + 0xc, options);
    auto ret = [&](reg32 eax) {
        const reg32 ebx = cpu.ebx, ecx = cpu.ecx, edx = cpu.edx;
        kept.ret(cpu, eax);
        cpu.ebx = ebx;
        cpu.ecx = ecx;
        cpu.edx = edx;
    };
    if (byte(app, kInited) == 0)
        return ret(0xfffffff6);
    if (!callWith(app, cpu, 0x523f90, options, 1))
        return;
    cpu.ecx = f;
    const reg32 p = player(app, index);
    if (!call(app, cpu, kEnter))
        return;
    cpu.ebx = reg32(sbyte(app, settings + 6));
    reg32 v;
    if (!ask(app, cpu, 0x4ff86c, at(app, settings), v))
        return;
    if (i32(v) < 0)
    {
        if (!call(app, cpu, kLeave))
            return;
        return ret(0xfffffff7);
    }
    put(app, p, at(app, f));
    putHalf(app, p + 0xa, 0);
    putHalf(app, p + 0xe, 0);
    put(app, p + 0x10, 0);
    put(app, p + 4, 0);
    put(app, p + 0x14, 0);
    putHalf(app, p + 0xc, 0xffff);
    put(app, p + 0x24, at(app, header));
    const reg32 c = voice(v);
    putByte(app, c + 0xa, 0xff);
    putByte(app, c + 0xf, byte(app, options + 7));
    putHalf(app, c + 0x10, half(app, settings + 4));
    put(app, c + 0x18, 0);
    put(app, c + 0x24, 0);
    put(app, c + 0x2c, 0x7fffffff);
    put(app, c + 0x28, 0x7f0000);
    put(app, c + 0x20, reg32(sbyte(app, options + 8)) << 16);
    putByte(app, c + 0x30, byte(app, settings + 7));
    putByte(app, c + 0x32, byte(app, settings + 8));
    putByte(app, c + 0x34, 1);
    putByte(app, c + 0x35, 0);
    putByte(app, c + 0x36, 0);
    putByte(app, c + 0x37, 1);
    putByte(app, c + 0x33, byte(app, options + 9));
    putByte(app, c + 0x38, byte(app, settings + 9));
    putByte(app, c + 0x39, byte(app, options + 0xa));
    putHalf(app, c + 0x42, reg16(sbyte(app, settings + 0xa) * 100));
    putByte(app, c + 0x3b, 0);
    putByte(app, c + 0x3a, 0);
    for (reg32 at_ = 0x48; at_ <= 0x5c; at_ += 4)
        put(app, c + at_, 0);
    putByte(app, c + 0x45, byte(app, options + 7));
    cpu.ecx = c;
    cpu.edx = v;
    if (!callWith(app, cpu, 0x502cb0, v) || !callWith(app, cpu, 0x5014a0, v, header))
        return;
    const reg32 level = reg32(quotient(mul(sbyte(app, c + 0x39), mul(sbyte(app, c + 0x38), s32(app, kBusLevels))), 0x3f01));
    const reg32 pushed = cpu.edx;
    if (!callWith(app, cpu, 0x523d94, index, v, reg32(sbyte(app, c + 0xf)), reg32(sbyte(app, c + 0x31)),
                  {reg32(shalf(app, c + 0x12)), level, reg32(sbyte(app, settings + 0xb)), pushed}))
        return;
    const reg32 result = cpu.eax;
    cpu.edx = result;
    if (i32(result) < 0)
    {
        if (!callWith(app, cpu, 0x4ffb64, v) || !call(app, cpu, kLeave))
            return;
        return ret(cpu.edx);
    }
    if (!call(app, cpu, kLeave))
        return;
    ret(at(app, p));
}

/* 0x5114d4 (SNDPKTPLAY_submit): packet edx (its frames +4, its data +0xc)
 * into player eax's ring.  Its serial; -10 before SNDinit, -13 when full. */
void SNDPKTPLAY_submit(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 packet = cpu.edx;
    cpu.esp = kept.frame(3);
    if (byte(app, kInited) == 0)
    {
        kept.ret(cpu, 0xfffffff6);
        return;
    }
    const reg32 p = player(app, cpu.eax);
    cpu.ecx = packet;
    cpu.edx = p;
    if (s32(app, p) < 0)
    {
        cpu.esi = kPktFile;
        cpu.edi = 0x54fdd0;
        cpu.ebp = 0xc1;
        if (!fail(app, cpu, kept.frame(5), kPktFile, 0x54fdd0, 0xc1, {0x54fde4}))
            return;
        cpu.esi = kept.esi;
        cpu.edi = kept.edi;
    }
    if (!call(app, cpu, kEnter))
        return;
    if (shalf(app, p + 0xe) >= shalf(app, p + 8) - 1)
    {
        if (!call(app, cpu, kLeave))
            return;
        const reg32 edx = cpu.edx;
        kept.ret(cpu, 0xfffffff3);
        cpu.edx = edx;
        return;
    }
    i32 slot = shalf(app, p + 0xa) + shalf(app, p + 0xe);
    if (slot >= shalf(app, p + 8))
        slot -= shalf(app, p + 8);
    const reg32 e = p + 0x28 + reg32(slot) * 0xc;
    put(app, e + 4, at(app, packet + 4));
    put(app, e + 8, at(app, packet + 0xc));
    put(app, e, at(app, p + 4));
    putHalf(app, p + 0xe, reg16(half(app, p + 0xe) + 1));
    put(app, p + 0x10, at(app, p + 0x10) + at(app, packet + 4));
    const reg32 serial = at(app, p + 4);
    put(app, p + 4, serial + 1);
    if (!call(app, cpu, kLeave))
        return;
    const reg32 edx = cpu.edx;
    kept.ret(cpu, serial);
    cpu.edx = edx;
}

namespace
{

/* The packet players' error for a player not started: Error with esi, edi
 * and ebx pushed (and popped after), at `esp`. */
bool notStarted(App* app, CPU& cpu, reg32 esp, reg32 function, reg32 line, reg32 text)
{
    return fail(app, cpu, esp, kPktFile, function, line, {text});
}

}  // namespace

/* 0x5115b8 (SNDPKTPLAY_submitspace): the packets player eax has room for;
 * -10 before SNDinit. */
void SNDPKTPLAY_submitspace(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    if (byte(app, kInited) == 0)
    {
        kept.ret(cpu, 0xfffffff6);
        return;
    }
    const reg32 p = player(app, cpu.eax);
    if (s32(app, p) < 0 && !notStarted(app, cpu, kept.frame(5), 0x54fe20, 0xf3, 0x54fe38))
        return;
    kept.ret(cpu, reg32(shalf(app, p + 8) - shalf(app, p + 0xe) - 1));
}

/* 0x51162c: the frames player eax has outstanding, submitted and in the
 * hardware. */
void framesOutstanding(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 p = player(app, cpu.eax);
    if (s32(app, p) < 0 && !notStarted(app, cpu, kept.frame(4), 0x54fe78, 0x104, 0x54fe9c))
        return;
    kept.ret(cpu, at(app, p + 0x10) + at(app, p + 0x14));
}

/* 0x511680 (SNDPKTPLAY_framesoutstanding): as 0x51162c, in the lock; -10
 * before SNDinit. */
void SNDPKTPLAY_framesoutstanding(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 index = cpu.eax;
    cpu.esp = kept.frame(1);
    if (byte(app, kInited) == 0)
    {
        kept.ret(cpu, 0xfffffff6);
        return;
    }
    cpu.edx = index;
    reg32 frames;
    if (!call(app, cpu, kEnter) || !ask(app, cpu, 0x51162c, index, frames))
        return;
    cpu.edx = frames;
    if (!call(app, cpu, kLeave))
        return;
    kept.ret(cpu, frames);
}

/* 0x511718 (SNDPKTPLAY_purge): player eax's packets of serials edx..ebx
 * taken out of its ring (their free callback called), the rest kept in
 * order.  0; -10 before SNDinit. */
void SNDPKTPLAY_purge(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 f = kept.frame(2, 0x10);
    cpu.esp = f;
    const reg32 index = cpu.eax;
    put(app, f, cpu.edx);
    put(app, f + 4, cpu.ebx);
    if (byte(app, kInited) == 0)
    {
        const reg32 ebx = cpu.ebx, edx = cpu.edx;
        kept.ret(cpu, 0xfffffff6);
        cpu.ebx = ebx;
        cpu.edx = edx;
        return;
    }
    cpu.esp = f - 8;
    const reg32 p = player(app, index);
    cpu.edx = p;
    if (s32(app, p) < 0)
    {
        cpu.ebx = kPktFile;
        cpu.esi = 0x54ff5c;
        cpu.edi = 0x13d;
        if (!fail(app, cpu, f - 8, kPktFile, 0x54ff5c, 0x13d, {0x54ff70}))
            return;
    }
    if (!call(app, cpu, kEnter))
        return;
    i32 to = shalf(app, p + 0xa), from = shalf(app, p + 0xa);
    const i32 count = shalf(app, p + 0xe);
    put(app, f + 0xc, reg32(count));
    for (i32 n = 0; n < count; ++n)
    {
        put(app, f + 8, p + 0x28);
        const reg32 e = p + 0x28 + reg32(from) * 0xc;
        const i32 serial = s32(app, e);
        if (serial < s32(app, f) || serial > s32(app, f + 4))
        {
            const reg32 d = p + 0x28 + reg32(to) * 0xc;
            ++to;
            for (reg32 k = 0; k < 0xc; k += 4)
                put(app, d + k, at(app, e + k));
            if (to >= shalf(app, p + 8))
                to = 0;
        }
        else
        {
            putHalf(app, p + 0xe, reg16(half(app, p + 0xe) - 1));
            put(app, p + 0x10, at(app, p + 0x10) - at(app, e + 4));
            if (at(app, p + 0x1c) != 0)
            {
                cpu.ebx = reg32(to);
                cpu.ecx = reg32(from);
                cpu.esi = e;
                cpu.edi = at(app, f);
                if (!callWith(app, cpu, at(app, p + 0x1c), at(app, e + 8)))
                    return;
            }
        }
        if (++from >= shalf(app, p + 8))
            from = 0;
    }
    cpu.ebx = reg32(to);
    if (!call(app, cpu, kLeave))
        return;
    cpu.ebx = reg32(to);
    cpu.edx = p;
    kept.ret(cpu, 0);
    cpu.ebx = reg32(to);
    cpu.edx = p;
}

/* 0x51181c (SNDPKTPLAY_stop): player eax's voice stopped, its packets
 * purged, the one playing given back too.  0; -10 before SNDinit. */
void SNDPKTPLAY_stop(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 index = cpu.eax;
    cpu.esp = kept.frame(2);
    if (byte(app, kInited) == 0)
    {
        kept.ret(cpu, 0xfffffff6);
        return;
    }
    cpu.esp = kept.frame(5);
    const reg32 p = player(app, index);
    cpu.ecx = p;
    if (s32(app, p) < 0)
    {
        cpu.ebx = kPktFile;
        cpu.edi = 0x54ffac;
        cpu.ebp = 0x178;
        if (!fail(app, cpu, kept.frame(6), kPktFile, 0x54ffac, 0x178, {0x54ffbc}))
            return;
        cpu.edi = kept.edi;
    }
    if (!call(app, cpu, kEnter) || !callWith(app, cpu, 0x4e9670, at(app, p)))
        return;
    cpu.ebx = 0x7fffffff;
    if (!callWith(app, cpu, 0x511718, index, 0))
        return;
    if (at(app, p + 0x1c) != 0 && shalf(app, p + 0xc) >= 0)
    {
        cpu.esi = reg32(shalf(app, p + 0xc)) * 0xc;
        if (!callWith(app, cpu, at(app, p + 0x1c), at(app, p + 0x28 + cpu.esi + 8)))
            return;
    }
    put(app, p, 0xffffffff);
    if (!call(app, cpu, kLeave))
        return;
    kept.ret(cpu, 0);
}

/* 0x5118d0 (SNDPKTPLAY_destroy): player eax no more.  0; -10 before
 * SNDinit. */
void SNDPKTPLAY_destroy(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 index = cpu.eax;
    cpu.esp = kept.frame(1);
    if (byte(app, kInited) == 0)
    {
        kept.ret(cpu, 0xfffffff6);
        return;
    }
    cpu.esp = kept.frame(2);
    if (!callWith(app, cpu, 0x523d90, index))
        return;
    put(app, kPlayers + 4 * index, 0);
    kept.ret(cpu, 0);
}

/* 0x5118fc: the mixer's next packet of player eax: the one playing given
 * back, the next taken -- its frames into [edx], its data the result (0 for
 * none). */
void nextPacket(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 out = cpu.edx;
    cpu.esp = kept.frame(2);
    const reg32 p = player(app, cpu.eax);
    cpu.ecx = out;
    cpu.edx = p;
    if (shalf(app, p + 0xc) >= 0)
    {
        const reg32 e = p + 0x28 + reg32(shalf(app, p + 0xc)) * 0xc;
        cpu.ebx = p + 0x28;
        putHalf(app, p + 0xc, 0xffff);
        if (at(app, p + 0x1c) != 0)
        {
            if (!callWith(app, cpu, at(app, p + 0x1c), at(app, e + 8)))
                return;
            cpu.edx = p;
        }
    }
    if (half(app, p + 0xe) == 0)
    {
        kept.ret(cpu, 0);
        cpu.edx = p;
        return;
    }
    putHalf(app, p + 0xc, half(app, p + 0xa));
    const reg32 e = p + 0x28 + reg32(shalf(app, p + 0xa)) * 0xc;
    put(app, out, at(app, e + 4));
    putHalf(app, p + 0xe, reg16(half(app, p + 0xe) - 1));
    putHalf(app, p + 0xa, reg16(half(app, p + 0xa) + 1));
    put(app, p + 0x14, at(app, p + 0x14) + at(app, e + 4));
    put(app, p + 0x10, at(app, p + 0x10) - at(app, e + 4));
    if (shalf(app, p + 0xa) >= shalf(app, p + 8))
        putHalf(app, p + 0xa, 0);
    kept.ret(cpu, at(app, e + 8));
    cpu.edx = p;
}

/* 0x511998: edx frames of player eax played by the hardware, its frames
 * callback told. */
void packetFramesPlayed(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(1);
    const reg32 c = player(app, cpu.eax);
    put(app, c + 0x14, at(app, c + 0x14) - cpu.edx);
    if (at(app, c + 0x20) != 0)
    {
        cpu.ecx = c;
        if (!call(app, cpu, at(app, c + 0x20)))
            return;
    }
    // edx as the callback leaves it.
    const reg32 edx = cpu.edx;
    kept.ret(cpu, cpu.eax);
    cpu.edx = edx;
}

/* 0x5119b0: a patch's settings at eax as they are by default.  0. */
void patchDefaults(App* app, CPU& cpu)
{
    const reg32 s = cpu.eax;
    put(app, s, 0xffffffff);
    putByte(app, s + 6, 0);
    putHalf(app, s + 4, 0);
    putByte(app, s + 7, 0x7f);
    putByte(app, s + 8, 0x40);
    putByte(app, s + 9, 0);
    putByte(app, s + 0xa, 0);
    putByte(app, s + 0xb, 0);
    cpu.eax = 0;
    cpu.esp += 4;
}

/* 0x5119d8 (iSNDpatchtohdr): patch eax made the header at edx -- its rate,
 * channels and representation -- with its settings at ebx and its frames
 * into [ecx].  0. */
void iSNDpatchtohdr(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 f = kept.frame(3, 0x1c);
    cpu.esp = f;
    const reg32 patch = cpu.eax, header = cpu.edx, settings = cpu.ebx, frames = cpu.ecx;
    put(app, f + 0x10, patch);
    put(app, f + 0x14, frames);
    if (!callWith(app, cpu, 0x5119b0, settings))
        return;
    put(app, f + 0x18, 0x10);
    reg32 compression = 0;
    put(app, f, patch + ((byte(app, patch + 3) & 2) ? 8 : 4));
    const reg8 cleared = byte(app, header + 2) & 0xfc;
    putHalf(app, header, 0x5622);
    putByte(app, header + 2, cleared | 1);
    put(app, frames, 0);
    for (;;)
    {
        if (!callWith(app, cpu, 0x5229d0, f, f + 4, f + 8, f + 0xc))
            return;
        if (cpu.eax == 0)
            break;
        const reg32 tag = at(app, f + 4), number = at(app, f + 8);
        cpu.ebx = tag;
        switch (tag)
        {
        case 0x81:
            put(app, f + 0x18, number);
            break;
        case 0x83:
            compression = number;
            break;
        case 0x91:
            putByte(app, settings + 0xb, reg8(number));
            break;
        case 0x82:
            putByte(app, header + 2, byte(app, header + 2) & 0xfc);
            putHalf(app, header + 2, reg16(half(app, header + 2) | (number & 3)));
            break;
        case 0x84:
            putHalf(app, header, reg16(number));
            break;
        case 0x85:
            put(app, frames, number);
            break;
        case 0x13:
            putByte(app, settings + 9, reg8(number));
            break;
        case 0xa:
            putByte(app, settings + 0xa, reg8(number));
            break;
        case 5:
            put(app, settings, number);
            break;
        case 6:
            putByte(app, settings + 6, reg8(number));
            break;
        default:
            break;
        }
    }
    // The representation: its bits on top of the channels' 2.
    auto represent = [&](reg8 bits) {
        putHalf(app, header + 2, half(app, header + 2) & 3);
        putByte(app, header + 2, byte(app, header + 2) | bits);
    };
    if (compression != 0)
    {
        if (compression == 5)
            represent(0x18);
        else if (compression == 7)
            represent(0xc);
        else if (compression == 9)
            represent(0x10);
        else
        {
            cpu.eax = 0x54fff4;
            cpu.edx = 0x550004;
            cpu.ecx = 0x64;
            if (!fail(app, cpu, f, 0x54fff4, 0x550004, 0x64, {0x550014}))
                return;
        }
    }
    else
    {
        cpu.ecx = at(app, f + 0x18);
        if (cpu.ecx == 0x10)
            represent(0);
        else if (cpu.ecx == 8)
            represent(8);
        else if (!fail(app, cpu, f, 0x54fff4, 0x550004, 0x77, {0x550040}))
            return;
    }
    const reg32 ebx = cpu.ebx, ecx = cpu.ecx, edx = cpu.edx;
    kept.ret(cpu, 0);
    cpu.ebx = ebx;
    cpu.ecx = ecx;
    cpu.edx = edx;
}

/* 0x511bf0 (iSNDplatformcalcdatarate): header eax's bytes a second, times
 * 256: its rate times channels times its representation's bytes a frame. */
void iSNDplatformcalcdatarate(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 header = cpu.eax;
    cpu.esp = kept.frame(3);
    const reg32 frames = reg32(half(app, header)) * (byte(app, header + 2) & 3);
    const reg32 representation = half(app, header + 2) & 0xfffc;
    reg32 bytes = kept.edx;
    if (representation == 0xc)
        bytes = 0x88;
    else if (representation == 0x10)
        bytes = 0x33;
    else if (representation == 8)
        bytes = 0x100;
    else if (representation == 0)
        bytes = 0x200;
    else if (!fail(app, cpu, kept.frame(5), 0x55006c, 0x55007c, 0x1c, {0x550098, reg32(half(app, header + 2) >> 2) & 0xffff}))
        return;
    kept.ret(cpu, reg32(mul(i32(frames), i32(bytes)) >> 8));
}

/* 0x511ca0: the stream eax's queue's chunks to ask for at once: edx.  0;
 * -10 before SNDinit, -8 for no stream. */
void streamChunksAtOnce(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    if (byte(app, kInited) == 0)
    {
        kept.ret(cpu, 0xfffffff6);
        return;
    }
    reg32 s;
    if (!ask(app, cpu, kFindStream, cpu.eax, s))
        return;
    if (s == 0)
    {
        kept.ret(cpu, 0xfffffff8);
        return;
    }
    if (!callWith(app, cpu, 0x4cfdd0, at(app, s + 4)))
        return;
    const reg32 ebx = cpu.ebx, ecx = cpu.ecx, edx = cpu.edx;
    kept.ret(cpu, 0);
    cpu.ebx = ebx;
    cpu.ecx = ecx;
    cpu.edx = edx;
}

}  // namespace snd
}  // namespace nfs3hp
