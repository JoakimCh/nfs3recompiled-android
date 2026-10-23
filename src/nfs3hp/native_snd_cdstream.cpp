#include "native_snd.h"

/* EA's CD stream (cmn\cdstream.c), native (native_snd.cpp says how): a ring
 * of chunks a reader thread fills from a file, block by block, as commands
 * queued to it ask -- open a file, go on to the next, seek, stop -- and the
 * SND streamer (native_snd_stream.cpp) takes chunks from, giving each back
 * when played.  native_snd_stream.cpp's comment lists the stream's fields.
 *
 * In the ring each chunk is an 8-byte header -- its id, its length with the
 * header -- and its data: -1 for an id wraps the ring to its start, -2 marks a
 * chunk given back, -3 one the reader dropped.  A command block (0x9c bytes)
 * is the file's name, +0x90 its argument, +0x94 the command, +0x98 the next. */
namespace nfs3hp
{
namespace snd
{

namespace
{

constexpr reg32 kStreams = 0x5645b8, kStreamWalk = 0x5645bc, kBlockCount = 0x5645a4;
constexpr reg32 kTimer = 0x79c1a4;
constexpr reg32 kCdFile = 0x54a3d0;
constexpr reg32 kSetEvent = 0x4dfb20, kWaitEvent = 0x4dfb70, kCreateEvent = 0x4dfb00, kCloseHandle = 0x4dfc00;
constexpr reg32 kCreateThread = 0x4df7a0, kRemoveThread = 0x4df870, kSleep = 0x4df8e0;
constexpr reg32 kNewLock = 0x4eb2e0, kFreeLock = 0x4eb360;
constexpr reg32 kAllocate = 0x4e1620, kFree = 0x4e1890, kFillZero = 0x4e070c, kTouch = 0x5011a0;
constexpr reg32 kStrncpy = 0x4e0e30, kMoveMemory = 0x4ea4f0, kTrace = 0x4e08f0;
constexpr reg32 kOpenBlock = 0x501270, kCloseBlock = 0x5013a0, kReadBlock = 0x5013b0, kSeekBlock = 0x501450;
constexpr reg32 kReader = 0x4e53c0;
constexpr reg32 kWrap = 0xffffffff, kGivenBack = 0xfffffffe, kDropped = 0xfffffffd;
constexpr reg32 kEndId = 0x5343456c;        // 'SCEl', big-endian

/* The stream's lock's calls, its address left in eax as the code pushes it
 * from there. */
bool lock(App* app, CPU& cpu, reg32 stream)
{
    cpu.eax = at(app, stream + 0xac);
    return call(app, cpu, at(app, kEnterCriticalSection), {cpu.eax});
}

bool unlock(App* app, CPU& cpu, reg32 stream)
{
    cpu.eax = at(app, stream + 0xac);
    return call(app, cpu, at(app, kLeaveCriticalSection), {cpu.eax});
}

/* The reader woken: the stream's event (at +0xa8, its thread's at +0x8c). */
bool wake(App* app, CPU& cpu, reg32 stream)
{
    return callWith(app, cpu, kSetEvent, stream + 0x8c, at(app, stream + 0xa8));
}

reg32 bigEndian(reg32 v) { return v >> 24 | (v >> 8 & 0xff00) | (v << 8 & 0xff0000) | v << 24; }

}  // namespace

/* 0x4e68a0: chunk edx of stream eax given back, the reader woken. */
void freeStreamChunk(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 stream = cpu.eax, chunk = cpu.edx;
    put(app, chunk, kGivenBack);
    if (!wake(app, cpu, stream))
        return;
    kept.ret(cpu, cpu.eax);
    cpu.edx = at(app, stream + 0xa8);
}

/* 0x4e68c0: the bytes stream eax holds read (none for no stream). */
void streamBytesRead(App* app, CPU& cpu)
{
    if (cpu.eax != 0)
        cpu.eax = at(app, cpu.eax + 0xb8);
    cpu.esp += 4;
}

/* 0x4e68e0: whether the reader has nothing to do: no stream, or idle (7)
 * with no command queued. */
void readerIdle(App* app, CPU& cpu)
{
    const reg32 s = at(app, kStreams);
    cpu.eax = s == 0 || (at(app, s + 0x20) == 7 && at(app, s + 0x78) == 0) ? 1 : 0;
    cpu.esp += 4;
}

/* 0x4e6950: whether stream eax's reader waits for room. */
void readerWaits(App* app, CPU& cpu)
{
    cpu.eax = at(app, cpu.eax + 0xb4);
    cpu.esp += 4;
}

/* 0x4e6660: the chunks given back at stream eax's freed end passed over --
 * the room they took counted out -- and a wrap followed to the ring's start. */
void passFreedChunks(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 s = cpu.eax;
    cpu.esp = kept.frame(3);
    if (!lock(app, cpu, s))
        return;
    if (at(app, s + 0x18) != at(app, s + 0x14))
        for (;;)
        {
            if (at(app, s + 0x18) == at(app, s + 0x10))
                break;
            const reg32 p = at(app, s + 0x18);
            if (at(app, p) == kGivenBack)
            {
                put(app, s + 0xbc, at(app, s + 0xbc) - (at(app, p + 4) - 8));
                put(app, s + 0x18, at(app, s + 0x18) + at(app, p + 4));
            }
            else if (at(app, p) == kWrap)
            {
                if (p == at(app, s + 0x14))
                    put(app, s + 0x14, at(app, s + 4));
                put(app, s + 0x18, at(app, s + 4));
            }
            else
                break;
            if (at(app, s + 0x18) == at(app, s + 0x14))
                break;
        }
    if (!unlock(app, cpu, s))
        return;
    kept.ret(cpu, cpu.eax);
}

/* 0x4e66e0: the room stream eax has to read into before the freed end, or
 * to the ring's end when that is behind or the ring empty. */
void roomAhead(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 s = cpu.eax;
    cpu.esp = kept.frame(1);
    if (!callWith(app, cpu, 0x4e6660, s))
        return;
    const reg32 freed = at(app, s + 0x18), write = at(app, s + 0xc);
    reg32 room = freed - write;
    if (freed < write || (freed == write && freed == at(app, s + 0x14)))
        room = at(app, s + 8) - write;
    kept.ret(cpu, room);
}

/* 0x4e6710: the room from where stream eax writes to the ring's end. */
void roomToEnd(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 s = cpu.eax;
    cpu.esp = kept.frame(1);
    if (!callWith(app, cpu, 0x4e6660, s))
        return;
    kept.ret(cpu, at(app, s + 8) - at(app, s + 0xc));
}

/* 0x4e6720: the room at the ring's start, when the freed end has wrapped. */
void roomAtStart(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 s = cpu.eax;
    cpu.esp = kept.frame(1);
    if (!callWith(app, cpu, 0x4e6660, s))
        return;
    kept.ret(cpu, at(app, s + 0x18) > at(app, s + 0xc) ? 0 : at(app, s + 0x18) - at(app, s + 4));
}

/* 0x4e6740 (getstreamchunk): the next chunk of stream eax to play, whole;
 * 0 for none yet (or while a command that empties the ring waits), -2 while
 * the reader is stopped, -1 for a chunk it dropped. */
void getStreamChunk(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 s = cpu.eax;
    cpu.esp = kept.frame(5);
    if (s == 0)
    {
        if (!fail(app, cpu, kept.frame(5), kCdFile, 0x54a844, 0x91b, {0x54a854}))
            return;
        kept.ret(cpu, 0);
        return;
    }
    if (at(app, s + 0x78) != 0)
    {
        const reg32 command = at(app, at(app, s + 0x78) + 0x94);
        if (command == 0xb || command == 0xd || command == 0x14 || command == 0x17)
        {
            kept.ret(cpu, 0);
            return;
        }
    }
    const reg32 state = at(app, s + 0x20);
    if (state == 2 || state == 1)
    {
        kept.ret(cpu, 0);
        return;
    }
    if (state == 0xe)
    {
        kept.ret(cpu, 0xfffffffe);
        return;
    }
    if (at(app, s + 0x10) == at(app, s + 0x14))
    {
        kept.ret(cpu, 0);
        return;
    }
    if (!lock(app, cpu, s))
        return;
    reg32 result = 0;
    bool take = true;
    if (at(app, at(app, s + 0x14)) == kWrap)
    {
        put(app, s + 0x14, at(app, s + 4));
        take = at(app, s + 0x10) != at(app, s + 0x14);
    }
    if (take)
    {
        const reg32 size = at(app, at(app, s + 0x14) + 4);
        const reg32 write = at(app, s + 0x10), read = at(app, s + 0x14);
        const i32 room = write >= read ? i32(write - read) : i32(at(app, s + 8) - read);
        if (room >= i32(size))
        {
            const reg32 p = read;
            put(app, s + 0xb8, at(app, s + 0xb8) - (size - 8));
            put(app, s + 0xbc, at(app, s + 0xbc) + (size - 8));
            put(app, s + 0x14, at(app, s + 0x14) + size);
            result = p;
            if (at(app, p) == kDropped)
            {
                if (p == at(app, s + 0x18))
                    put(app, s + 0x18, at(app, s + 0x14));
                else
                    put(app, p, kGivenBack);
                result = 0xffffffff;
                cpu.esi = result;
                if (!wake(app, cpu, at(app, kStreams)))
                    return;
            }
        }
    }
    if (!unlock(app, cpu, s))
        return;
    kept.ret(cpu, result);
}

/* 0x4e69e0: the stream's command blocks: edx of them at eax, chained. */
void chainCommandBlocks(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    reg32 b = cpu.eax;
    const reg32 s = at(app, kStreams);
    if (s == 0)
    {
        kept.ret(cpu, cpu.eax);
        return;
    }
    put(app, s + 0x74, b);
    for (i32 i = 0; i < i32(cpu.edx - 1); ++i)
    {
        put(app, b + 0x98, b + 0x9c);
        b += 0x9c;
    }
    put(app, b + 0x98, 0);
    kept.ret(cpu, b);
    cpu.edx = i32(kept.edx - 1) > 0 ? kept.edx - 1 : 0;
}

/* 0x4e6a20: command block eax back on the stream's free list. */
void freeCommandBlock(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 b = cpu.eax;
    cpu.esp = kept.frame(2);
    const reg32 s = at(app, kStreams);
    if (s == 0)
    {
        kept.ret(cpu, cpu.eax);
        return;
    }
    cpu.esp = kept.frame(3);
    if (!lock(app, cpu, s))
        return;
    put(app, b + 0x98, at(app, at(app, kStreams) + 0x74));
    put(app, at(app, kStreams) + 0x74, b);
    if (!unlock(app, cpu, at(app, kStreams)))
        return;
    kept.ret(cpu, cpu.eax);
}

/* 0x4e6a70: whether eax command blocks are free. */
void commandBlocksFree(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    reg32 n = cpu.eax;
    cpu.esp = kept.frame(3);
    if (at(app, kStreams) == 0)
    {
        kept.ret(cpu, 0);
        return;
    }
    if (!lock(app, cpu, at(app, kStreams)))
        return;
    reg32 b = at(app, at(app, kStreams) + 0x74);
    while (n != 0 && b != 0)
    {
        b = at(app, b + 0x98);
        --n;
    }
    if (!unlock(app, cpu, at(app, kStreams)))
        return;
    kept.ret(cpu, n == 0 ? 1 : 0);
}

/* 0x4e6b30 (getstreamblocka): a free command block; none (0) when there is
 * none and eax says not to mind, an error when it minds. */
void takeCommandBlock(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 mind = cpu.eax;
    cpu.esp = kept.frame(3);
    if (at(app, kStreams) == 0)
    {
        kept.ret(cpu, 0);
        return;
    }
    if (!lock(app, cpu, at(app, kStreams)))
        return;
    if (at(app, at(app, kStreams) + 0x74) == 0)
    {
        if (mind == 0)
        {
            if (!unlock(app, cpu, at(app, kStreams)))
                return;
            kept.ret(cpu, 0);
            return;
        }
        if (!fail(app, cpu, kept.frame(5), kCdFile, 0x54a880, 0xae6, {0x54a890}))
            return;
    }
    const reg32 s = at(app, kStreams);
    const reg32 b = at(app, s + 0x74);
    put(app, s + 0x74, at(app, b + 0x98));
    put(app, b + 0x98, 0);
    if (!unlock(app, cpu, s))
        return;
    kept.ret(cpu, b);
}

/* 0x4e4c60 (streamcommanda, stdcall 8): command ebx with argument ecx and
 * file edx queued to stream eax, the reader woken; [esp+4] says to break into
 * what it does, [esp+8] to mind no block being free.  1, 0 for no block. */
void streamCommand(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 s = cpu.eax, name = cpu.edx, command = cpu.ebx, argument = cpu.ecx;
    const reg32 urgent = at(app, kept.esp + 4), mind = at(app, kept.esp + 8);
    const reg32 f = kept.frame(3, 4);
    cpu.esp = f;
    put(app, f, command);
    if (at(app, kStreams) == 0)
    {
        if (mind != 0 && !fail(app, cpu, f, kCdFile, 0x54a6a0, 0x328, {0x54a6b0}))
            return;
        kept.ret(cpu, 0, 8);
        return;
    }
    if (!lock(app, cpu, s))
        return;
    reg32 b;
    if (!callWith(app, cpu, 0x4e6b30, mind))
        return;
    b = cpu.eax;
    if (b == 0)
    {
        if (!unlock(app, cpu, s))
            return;
        kept.ret(cpu, 0, 8);
        return;
    }
    if (!callWith(app, cpu, kStrncpy, b, name, 0x8f))
        return;
    putByte(app, b + 0x8e, 0);
    put(app, b + 0x90, argument);
    put(app, b + 0x94, at(app, f));
    if (at(app, s + 0x7c) != 0)
    {
        put(app, at(app, s + 0x7c) + 0x98, b);
        put(app, s + 0x7c, b);
    }
    else
    {
        put(app, s + 0x7c, b);
        put(app, s + 0x78, b);
    }
    if (urgent != 0 && at(app, s + 0x24) == 0)
        put(app, s + 0x24, 0xf);
    if (!unlock(app, cpu, s) || !wake(app, cpu, s))
        return;
    kept.ret(cpu, 1, 8);
}

/* 0x4e4d70 (purgestreamcommanda, stdcall 4): the commands queued to stream
 * eax dropped and command ebx (argument ecx, file edx) queued alone, the
 * reader woken -- and, for those that stop it (0xb, 0xd, 0x14), waited for.
 * [esp+4] to mind no block being free.  1. */
void purgeStreamCommand(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 s = cpu.eax, name = cpu.edx, command = cpu.ebx, argument = cpu.ecx;
    const reg32 mind = at(app, kept.esp + 4);
    const reg32 f = kept.frame(3, 4);
    cpu.esp = f;
    put(app, f, argument);
    if (at(app, kStreams) == 0)
    {
        if (mind != 0 && !fail(app, cpu, f, kCdFile, 0x54a6ec, 0x34e, {0x54a700}))
            return;
        kept.ret(cpu, 0, 4);
        return;
    }
    if (!lock(app, cpu, s))
        return;
    while (at(app, s + 0x78) != 0)
    {
        const reg32 b = at(app, s + 0x78);
        put(app, s + 0x78, at(app, b + 0x98));
        if (!callWith(app, cpu, 0x4e6a20, b))
            return;
    }
    if (!callWith(app, cpu, 0x4e6b30, mind))
        return;
    const reg32 b = cpu.eax;
    if (!callWith(app, cpu, kStrncpy, b, name, 0x8f))
        return;
    putByte(app, b + 0x8e, 0);
    put(app, b + 0x94, command);
    put(app, b + 0x90, at(app, f));
    put(app, s + 0x7c, b);
    put(app, s + 0x78, b);
    if (at(app, s + 0x1c) != 0 && at(app, s + 0x24) == 0)
        put(app, s + 0x24, 0xf);
    if (!unlock(app, cpu, s) || !wake(app, cpu, s))
        return;
    if ((command == 0xb || command == 0xd || command == 0x14) && !callWith(app, cpu, kWaitEvent, at(app, s + 0xa4)))
        return;
    kept.ret(cpu, 1, 4);
}

namespace
{

/* The wrappers' calls: purgeStreamCommand / streamCommand with their
 * arguments, ebx and ecx kept for the caller as their pushes keep them. */
void purgeWith(App* app, CPU& cpu, reg32 command, bool named, reg32 mind)
{
    const Kept kept(cpu);
    const reg32 s = cpu.eax, edx = cpu.edx;
    cpu.esp = kept.frame(2);
    cpu.ebx = command;
    cpu.ecx = named ? 0 : edx;
    cpu.edx = named ? edx : 0x54a744;
    if (!call(app, cpu, 0x4e4d70, {mind}))
        return;
    const reg32 left = cpu.edx;
    kept.ret(cpu, cpu.eax);
    cpu.edx = left;
    (void)s;
}

void commandWith(App* app, CPU& cpu, reg32 command, bool named, reg32 urgent, reg32 mind)
{
    const Kept kept(cpu);
    const reg32 edx = cpu.edx;
    cpu.esp = kept.frame(2);
    cpu.ebx = command;
    cpu.ecx = named ? 0 : edx;
    cpu.edx = named ? edx : 0x54a744;
    if (!call(app, cpu, 0x4e4c60, {urgent, mind}))
        return;
    const reg32 left = cpu.edx;
    kept.ret(cpu, cpu.eax);
    cpu.edx = left;
}

}  // namespace

/* 0x4e4ea0..0x4e50c0: the commands by name: open file edx (1), open it next
 * (0x11), go on with it (0xd), switch to it (0x12), queue it (0x13), restart
 * with it (0x14); seek to edx (2), read on from edx (0x10), stop at edx
 * (0xb) -- each minding no block or not. */
void streamOpen(App* app, CPU& cpu) { purgeWith(app, cpu, 1, true, 1); }
void streamOpenQuietly(App* app, CPU& cpu) { purgeWith(app, cpu, 1, true, 0); }
void streamOpenNext(App* app, CPU& cpu) { commandWith(app, cpu, 0x11, true, 0, 1); }
void streamOpenNextQuietly(App* app, CPU& cpu) { commandWith(app, cpu, 0x11, true, 0, 0); }
void streamContinue(App* app, CPU& cpu) { purgeWith(app, cpu, 0xd, true, 1); }
void streamContinueQuietly(App* app, CPU& cpu) { purgeWith(app, cpu, 0xd, true, 0); }
void streamSwitch(App* app, CPU& cpu) { purgeWith(app, cpu, 0x12, true, 1); }
void streamSwitchQuietly(App* app, CPU& cpu) { purgeWith(app, cpu, 0x12, true, 0); }
void streamQueueFile(App* app, CPU& cpu) { commandWith(app, cpu, 0x13, true, 0, 1); }
void streamQueueFileQuietly(App* app, CPU& cpu) { commandWith(app, cpu, 0x13, true, 0, 0); }
void streamRestart(App* app, CPU& cpu) { purgeWith(app, cpu, 0x14, true, 1); }
void streamRestartQuietly(App* app, CPU& cpu) { purgeWith(app, cpu, 0x14, true, 0); }
void streamSeek(App* app, CPU& cpu) { commandWith(app, cpu, 2, false, 1, 1); }
void streamSeekQuietly(App* app, CPU& cpu) { commandWith(app, cpu, 2, false, 1, 0); }
void streamReadOn(App* app, CPU& cpu) { commandWith(app, cpu, 0x10, false, 0, 1); }
void streamReadOnQuietly(App* app, CPU& cpu) { commandWith(app, cpu, 0x10, false, 0, 0); }
void streamStopAt(App* app, CPU& cpu) { purgeWith(app, cpu, 0xb, false, 1); }
void streamStopAtQuietly(App* app, CPU& cpu) { purgeWith(app, cpu, 0xb, false, 0); }

/* 0x4e4420 (initstreamstructa): stream eax set up -- its ring (+0x84 bytes at
 * +0x88), edx command blocks after it, blocks of ebx read at once -- and its
 * reader thread started; ecx says the stream is the first. */
void initStreamStruct(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 s = cpu.eax, blockSize = cpu.ebx, first = cpu.ecx;
    cpu.esp = kept.frame(3);
    if (first != 0 && at(app, kStreams) != 0 && !fail(app, cpu, kept.frame(3), kCdFile, 0x54a42c, 0x100, {0x54a440}))
        return;
    if (first != 0 && i32(blockSize) < 0x2000
        && !fail(app, cpu, kept.frame(3), kCdFile, 0x54a42c, 0x105, {0x54a47c}))
        return;
    put(app, kStreamWalk, s);
    put(app, kStreams, s);
    if (!callWith(app, cpu, 0x4e69e0, s + 0xc0, at(app, kBlockCount)))
        return;
    put(app, s + 0x3c, at(app, s + 0x84));
    put(app, s + 4, at(app, s + 0x88));
    put(app, s + 8, at(app, s + 0x88) + at(app, s + 0x84));
    put(app, s + 0x2c, first);
    put(app, s + 0x18, at(app, s + 4));
    put(app, s + 0x14, at(app, s + 0x18));
    put(app, s + 0xc, at(app, s + 0x14));
    put(app, s + 0x10, at(app, s + 0xc));
    put(app, s + 0x28, 0);
    put(app, s + 0x40, blockSize);
    put(app, s + 0x1c, 0);
    put(app, s + 0x70, 0);
    put(app, s + 0x78, 0);
    put(app, s + 0x7c, at(app, s + 0x78));
    put(app, s + 0x20, 7);
    put(app, s + 0x24, 0);
    put(app, s + 0x38, 0);
    put(app, s + 0x34, at(app, s + 0x38));
    put(app, s + 0xbc, 0);
    put(app, s + 0xb8, at(app, s + 0xbc));
    put(app, s + 0x30, 0);
    if (!call(app, cpu, kCreateEvent))
        return;
    put(app, s + 0xa4, cpu.eax);
    if (!call(app, cpu, kNewLock))
        return;
    put(app, s + 0xac, cpu.eax);
    if (!callWith(app, cpu, kCreateThread, kReader, 0, 1, 0xffffffff, {s + 0x8c}))
        return;
    if (cpu.eax == 0 && !fail(app, cpu, kept.frame(3), kCdFile, 0x54a42c, 0x12d, {0x54a4ac}))
        return;
    if (!callWith(app, cpu, kWaitEvent, at(app, s + 0xa4)))
        return;
    kept.ret(cpu, s);
}

void initStreamStructSecond(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(1);
    cpu.ecx = 0;
    if (!call(app, cpu, 0x4e4420))
        return;
    kept.ret(cpu, cpu.eax);
}

void initStreamStructFirst(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(1);
    cpu.ecx = 1;
    if (!call(app, cpu, 0x4e4420))
        return;
    kept.ret(cpu, cpu.eax);
}

/* 0x4e45f0 (initstreama): a stream of eax bytes (whole pages) allocated in
 * memory pool ebx -- its ring and the stream with its command blocks, their
 * pages touched -- and set up with blocks of edx; ecx says the first. */
void initStream(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 pool = cpu.ebx, first = cpu.ecx;
    const reg32 f = kept.frame(3, 4);
    cpu.esp = f;
    put(app, f, cpu.edx);
    reg32 size = cpu.eax;
    if (size & 0xfff)
        size = (size + 0x1000) & 0x7ffff000;
    put(app, kWhere, kCdFile);
    put(app, kWhere + 4, 0x54a4ec);
    put(app, kWhere + 8, 0x188);
    if (!callWith(app, cpu, kAllocate, 0x54a4f8, size, pool, size))
        return;
    const reg32 ring = cpu.eax;
    if (ring == 0 && first != 0 && !fail(app, cpu, f, kCdFile, 0x54a4ec, 0x18a, {0x54a504}))
        return;
    put(app, kWhere + 4, 0x54a4ec);
    put(app, kWhere, kCdFile);
    put(app, kWhere + 8, 0x18e);
    const reg32 structSize = ((at(app, kBlockCount) * 0x9c + 0xf) & 0xfff0) + 0xc0;
    if (!callWith(app, cpu, kAllocate, 0x54a520, structSize, pool, size))
        return;
    const reg32 s = cpu.eax;
    if (!callWith(app, cpu, kFillZero, s, structSize, pool, size))
        return;
    put(app, s + 0x88, ring);
    put(app, s + 0x84, size);
    if (!callWith(app, cpu, kTouch, ring, size, 0x1000, size))
        return;
    if (!callWith(app, cpu, kTouch, s, structSize, 0x1000, size))
        return;
    if (!callWith(app, cpu, 0x4e4420, s, structSize, at(app, f), first))
        return;
    kept.ret(cpu, cpu.eax);
}

void initStreamSecond(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(1);
    cpu.ecx = 0;
    if (!call(app, cpu, 0x4e45f0))
        return;
    kept.ret(cpu, cpu.eax);
}

void initStreamFirst(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(1);
    cpu.ecx = 1;
    if (!call(app, cpu, 0x4e45f0))
        return;
    kept.ret(cpu, cpu.eax);
}

/* 0x4e4a30 (delstreamstruct): the first stream's reader stopped (8) --
 * waited for while it works -- and its thread, events and lock gone. */
void deleteStreamStruct(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 s = cpu.eax;
    cpu.esp = kept.frame(5);
    if (at(app, kStreams) == 0 && !fail(app, cpu, kept.frame(6), kCdFile, 0x54a5a4, 0x25d, {0x54a5b4}))
        return;
    const reg32 first = at(app, kStreams);
    if (s != first)
    {
        kept.ret(cpu, cpu.eax);
        return;
    }
    put(app, first + 0x24, 8);
    const reg32 deadline = at(app, kTimer) + 0x2710;
    if (at(app, first + 0x28) == 1)
        do
        {
            safepoint(app, cpu);
            if (s32(app, kTimer) > i32(deadline)
                && !fail(app, cpu, kept.frame(5), kCdFile, 0x54a5a4, 0x273, {0x54a5f4}))
                return;
        } while (at(app, s + 0x28) == 1);
    put(app, s + 0x24, 8);
    if (!wake(app, cpu, at(app, kStreams)))
        return;
    if (!callWith(app, cpu, kWaitEvent, at(app, s + 0xa4)) || !callWith(app, cpu, kCloseHandle, at(app, s + 0xa4))
        || !callWith(app, cpu, kFreeLock, at(app, s + 0xac)))
        return;
    put(app, s + 0xac, 0);
    if (!callWith(app, cpu, kRemoveThread, s + 0x8c))
        return;
    put(app, kStreams, 0);
    kept.ret(cpu, cpu.eax);
}

/* 0x4e4b50 (delstream): stream eax freed -- the first with every stream
 * after it, another unlinked -- and the streams no more. */
void deleteStream(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    reg32 s = cpu.eax;
    cpu.esp = kept.frame(5);
    if (at(app, kStreams) == 0 && !fail(app, cpu, kept.frame(6), kCdFile, 0x54a638, 0x2bc, {0x54a644}))
        return;
    const reg32 first = at(app, kStreams);
    if (s == first)
    {
        if (!callWith(app, cpu, 0x4e4a30, first))
            return;
        reg32 next = first;
        do
        {
            next = at(app, next + 0x70);
            if (!callWith(app, cpu, kFree, at(app, s + 0x88)) || !callWith(app, cpu, kFree, s))
                return;
            s = next;
        } while (next != 0);
    }
    else
    {
        reg32 c = first;
        if (at(app, first + 0x70) != 0)
            while (s != at(app, c + 0x70))
            {
                c = at(app, c + 0x70);
                if (at(app, c + 0x70) == 0)
                    break;
            }
        if (s != at(app, c + 0x70) && !fail(app, cpu, kept.frame(5), kCdFile, 0x54a638, 0x2d9, {0x54a680}))
            return;
        put(app, c + 0x70, at(app, s + 0x70));
        if (!callWith(app, cpu, kFree, at(app, s + 0x88)) || !callWith(app, cpu, kFree, s))
            return;
    }
    put(app, kStreams, 0);
    put(app, kStreamWalk, 0);
    kept.ret(cpu, cpu.eax);
}

namespace
{

/* The reader thread's work, on the first stream ([0x5645b8]) and the
 * streams after it (each takes the chunks whose ids its mask and id match).
 * Each wait is for the event at +0xa8, the reader marked waiting (+0xb4) the
 * while; a command arriving (+0x24) breaks a wait off and sends the reader
 * back to take it.  The steps return false when the game stopped. */
struct Reader
{
    App* app;
    CPU& cpu;
    reg32 frame;  // the thread's local: the file's block size

    reg32 s() const { return at(app, kStreams); }
    reg32 w() const { return at(app, kStreamWalk); }
    reg32 field(reg32 off) const { return at(app, s() + off); }
    void set(reg32 off, reg32 v) { put(app, s() + off, v); }
    bool command() const { return field(0x24) != 0; }

    bool lock() { return snd::lock(app, cpu, s()); }
    bool unlock() { return snd::unlock(app, cpu, s()); }
    bool wait() { return callWith(app, cpu, kWaitEvent, field(0xa8)); }

    bool ask(reg32 target, reg32 stream, reg32& result)
    {
        if (!callWith(app, cpu, target, stream))
            return false;
        result = cpu.eax;
        return true;
    }

    bool move(reg32 from, reg32 to, reg32 bytes) { return callWith(app, cpu, kMoveMemory, from, to, bytes); }

    /* Waited while `busy` says so and no command comes.  1 to go on, 2 for a
     * command, 0 the game stopped. */
    template <typename Busy>
    int waitWhile(Busy busy)
    {
        for (;;)
        {
            if (command())
                break;
            bool b;
            if (!busy(b))
                return 0;
            if (!b)
                break;
            set(0xb4, 1);
            if (!wait())
                return 0;
        }
        set(0xb4, 0);
        return command() ? 2 : 1;
    }

    /* Until the room to the ring's end (stream `stream`) is all its room. */
    int waitTillEndRoomFree(reg32 stream)
    {
        return waitWhile([&](bool& busy) {
            reg32 a, b;
            if (!ask(0x4e6710, stream, a) || !ask(0x4e66e0, stream, b))
                return false;
            busy = a != b;
            return true;
        });
    }

    /* Until more than `bytes` are free ahead (roomAhead), of stream `stream`. */
    int waitTillAhead(reg32 stream, reg32 bytes, bool signedCompare = true)
    {
        return waitWhile([&](bool& busy) {
            reg32 a;
            if (!ask(0x4e66e0, stream, a))
                return false;
            busy = signedCompare ? i32(a) <= i32(bytes) : a <= bytes;
            return true;
        });
    }

    /* Until more than `bytes` are free at the ring's start (roomAtStart). */
    int waitTillStart(reg32 stream, reg32 bytes, bool signedCompare = true)
    {
        return waitWhile([&](bool& busy) {
            reg32 a;
            if (!ask(0x4e6720, stream, a))
                return false;
            busy = signedCompare ? i32(a) <= i32(bytes) : a <= bytes;
            return true;
        });
    }

    /* The blocks read into `to`, tried again (a ms between) until read. */
    bool readBlocks(reg32 to)
    {
        for (;;)
        {
            if (!callWith(app, cpu, kReadBlock, field(0x1c), to, field(0xa0)))
                return false;
            if (cpu.eax != 0)
                return true;
            if (!callWith(app, cpu, kSleep, 1))
                return false;
        }
    }

    /* The file of the command taken opened -- its block size the local --
     * or, not found, traced and the reader idle.  `opened` false for that. */
    bool open(bool& opened, reg32 line)
    {
        if (field(0x1c) != 0 && !callWith(app, cpu, kCloseBlock, field(0x1c)))
            return false;
        if (!callWith(app, cpu, kOpenBlock, field(0x80), s() + 0x1c, s() + 0x50, s() + 0x58, {frame}))
            return false;
        opened = cpu.eax != 0;
        if (!opened)
        {
            if (!snd::call(app, cpu, kTrace, {0x54a764, field(0x80)}) || !callWith(app, cpu, 0x4e6a20, field(0x80)))
                return false;
            set(0x1c, 0);
            set(0x20, 7);
            return true;
        }
        if (!callWith(app, cpu, 0x4e6a20, field(0x80)) || !lock())
            return false;
        const reg32 block = at(app, frame);
        if (i32(block) > s32(app, s() + 0x40))
        {
            set(0xa0, 1);
            if (i32(block) > s32(app, s() + 0x3c)
                && !fail(app, cpu, frame, kCdFile, 0x54a788, line, {0x54a79c, block, field(0x3c)}))
                return false;
            if (i32(block + block) > s32(app, s() + 0x3c) && !snd::call(app, cpu, kTrace, {0x54a7d0}))
                return false;
            set(0x40, block);
        }
        else
        {
            set(0xa0, reg32(quotient(s32(app, s() + 0x40), i32(block))));
            set(0x40, block * field(0xa0));
        }
        set(0x60, field(0x50));
        set(0x54, field(0x50) + field(0x58));
        return true;
    }
};

}  // namespace

/* 0x4e53c0 (streamreaderthread): the reader of the CD streams, on a thread
 * of its own: the commands taken -- open a file, go on, seek, stop -- and the
 * file read block by block into the rings, each chunk to the stream whose
 * mask takes its id, the reader waiting while a ring is full. */
void streamReaderThread(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 frame = kept.frame(6, 4);
    cpu.esp = frame;
    Reader r{app, cpu, frame};
    if (!call(app, cpu, kCreateEvent))
        return;
    r.set(0xa8, cpu.eax);
    if (!callWith(app, cpu, kSetEvent, 0, r.field(0xa4)))
        return;
    bool ending = false;  // esi: the chunk read is the end's
    for (;;)
    {
        safepoint(app, cpu);
        if (!r.lock())
            return;
        if (r.field(0x24) == 8)
            r.set(0x20, 8);
        else if (r.field(0x24) == 0xf)
            r.set(0x20, 7);
        r.set(0x24, 0);
        if (!r.unlock())
            return;
        const reg32 state = r.field(0x20);
        if (state == 1 || state == 0x11 || state == 0x12 || state == 0x13)
        {
            bool opened;
            if (!r.open(opened, 0x577))
                return;
            if (!opened)
                continue;
            if (r.field(0x20) == 1 || r.field(0x20) == 0x12)
            {
                r.set(0x10, r.field(0x14));
                r.set(0xb8, 0);
            }
            r.set(0xc, r.field(0x10));
            r.set(0x20, r.field(0x20) == 0x13 || r.field(0x20) == 0x12 ? 7 : 0x10);
            if (!r.unlock())
                return;
            continue;
        }
        if (state == 7)
        {
            if (!callWith(app, cpu, 0x4e6660, r.s()))
                return;
            if (r.field(0x78) == 0)
            {
                if (!r.wait())
                    return;
                continue;
            }
            if (!r.lock())
                return;
            const reg32 c = r.field(0x78);
            r.set(0x78, at(app, c + 0x98));
            r.set(0x80, c);
            if (r.field(0x78) == 0)
                r.set(0x7c, 0);
            r.set(0x20, at(app, c + 0x94));
            r.set(0x60, r.field(0x50) + at(app, c + 0x90));
            const reg32 k = at(app, c + 0x94);
            if (!(k == 0xd || k == 0x14 || k == 1 || k == 0x11 || k == 0x12 || k == 0x13)
                && !callWith(app, cpu, 0x4e6a20, c))
                return;
            if (!r.unlock())
                return;
            continue;
        }
        if (state == 8)
        {
            if (r.field(0x1c) != 0 && !callWith(app, cpu, kCloseBlock, r.field(0x1c)))
                return;
            r.set(0x1c, 0);
            if (!callWith(app, cpu, kCloseHandle, r.field(0xa8)) || !callWith(app, cpu, kSetEvent, 0, r.field(0xa4)))
                return;
            kept.ret(cpu, cpu.eax);
            return;
        }
        bool reading = state == 2 || state == 0x10;
        if (state == 0xd || state == 0x14 || state == 0xb)
        {
            if (state != 0xb)
            {
                bool opened;
                if (!r.open(opened, 0x5a5))
                    return;
                if (!opened)
                    continue;
                if (!r.unlock())
                    return;
            }
            put(app, kStreamWalk, r.s());
            if (!r.lock())
                return;
            while (r.w() != 0)
            {
                const reg32 w = r.w();
                put(app, w + 0x18, at(app, w + 4));
                put(app, w + 0x14, at(app, w + 0x18));
                put(app, w + 0xc, at(app, w + 0x14));
                put(app, w + 0x10, at(app, w + 0xc));
                put(app, w + 0xbc, 0);
                put(app, w + 0xb8, at(app, w + 0xbc));
                put(app, kStreamWalk, at(app, w + 0x70));
            }
            if (!r.unlock())
                return;
            if (r.field(0x20) == 0x14)
            {
                r.set(0x20, 7);
                if (!callWith(app, cpu, kSetEvent, 0, r.field(0xa4)))
                    return;
                continue;
            }
            r.set(0x20, 2);
            if (!callWith(app, cpu, kSetEvent, 0, r.field(0xa4)))
                return;
            reading = true;
        }
        int go = 1;
        if (reading)
        {
            // A read started: from the chunk's start at the offset asked,
            // the part of the first block before it skipped.
            if (!r.lock())
                return;
            if (r.field(0x20) == 2)
            {
                r.set(0x10, r.field(0x14));
                r.set(0xc, r.field(0x10));
                r.set(0xb8, 0);
            }
            else
                r.set(0xc, r.field(0x10));
            r.set(0x5c, r.field(0x60));
            if (!r.unlock())
                return;
            if (!callWith(app, cpu, kSeekBlock, r.field(0x1c), r.field(0x5c)))
                return;
            const reg32 at0 = cpu.eax;
            if (!r.lock())
                return;
            r.set(0xb0, r.field(0x5c) - at0);
            r.set(0x4c, r.field(0x40) - r.field(0xb0));
            if (!r.unlock())
                return;
            reg32 room;
            if (!r.ask(0x4e6710, r.s(), room))
                return;
            if (i32(room) <= s32(app, r.s() + 0x40))
            {
                if ((go = r.waitTillEndRoomFree(r.s())) != 1)
                {
                    if (go == 0)
                        return;
                    continue;
                }
                if ((go = r.waitTillStart(r.s(), at(app, frame))) != 1)
                {
                    if (go == 0)
                        return;
                    continue;
                }
                if (!r.lock())
                    return;
                put(app, r.field(0x10), kWrap);
                r.set(0x10, r.field(4));
                r.set(0xc, r.field(0x10));
                if (!r.unlock())
                    return;
            }
            if ((go = r.waitTillAhead(r.s(), r.field(0x40))) != 1)
            {
                if (go == 0)
                    return;
                continue;
            }
            if (!r.readBlocks(r.field(0xc)) || !r.lock())
                return;
            r.set(0x5c, r.field(0x5c) + r.field(0x4c));
            if (r.field(0xb0) != 0 && !r.move(r.field(0x10) + r.field(0xb0), r.field(0x10), r.field(0x4c)))
                return;
            r.set(0xc, r.field(0xc) + r.field(0x4c));
            r.set(0x20, 3);
            if (!r.unlock())
                return;
        }
        else if (state != 3)
            continue;
        // State 3: a chunk's header in, its whole read and handed to its
        // stream's ring.
        if (r.field(0x4c) < 8)
        {
            reg32 room;
            if (!r.ask(0x4e6710, r.s(), room))
                return;
            if (i32(room) <= s32(app, r.s() + 0x40))
            {
                if ((go = r.waitTillEndRoomFree(r.s())) != 1 || (go = r.waitTillStart(r.w(), r.field(0x4c))) != 1)
                {
                    if (go == 0)
                        return;
                    continue;
                }
                if (!r.lock() || !r.move(r.field(0x10), r.field(4), r.field(0x4c)))
                    return;
                put(app, r.field(0x10), kWrap);
                r.set(0x10, r.field(4));
                r.set(0xc, r.field(0x10));
                r.set(0xc, r.field(0xc) + r.field(0x4c));
                if (!r.unlock())
                    return;
            }
            if ((go = r.waitTillAhead(r.s(), r.field(0x40))) != 1)
            {
                if (go == 0)
                    return;
                continue;
            }
            if (!r.readBlocks(r.field(0xc)) || !r.lock())
                return;
            r.set(0xc, r.field(0xc) + r.field(0x40));
            r.set(0x5c, r.field(0x5c) + r.field(0x40));
            r.set(0x4c, r.field(0x4c) + r.field(0x40));
            if (!r.unlock())
                return;
        }
        if (bigEndian(at(app, r.field(0x10))) == kEndId && r.field(0x78) != 0)
        {
            r.set(0x20, 7);
            continue;
        }
        if (!r.lock())
            return;
        r.set(0x48, at(app, r.field(0x10) + 4));
        r.set(0x44, r.field(0x48) - r.field(0x4c));
        put(app, kStreamWalk, r.field(0x70));
        while (r.w() != 0)
        {
            const reg32 id = bigEndian(at(app, r.field(0x10)));
            if ((id & at(app, r.w() + 0x6c)) == at(app, r.w() + 0x68))
                break;
            put(app, kStreamWalk, at(app, r.w() + 0x70));
        }
        if (r.w() == 0)
            put(app, kStreamWalk, r.s());
        if (!r.unlock())
            return;
        const reg32 length = r.field(0x48);
        if (length < 8 || i32(at(app, r.w() + 0x3c)) / 2 < i32(length))
        {
            if (r.field(0x2c) == 0)
            {
                // A chunk that cannot be: every stream's ring given an empty
                // chunk of the stream's id, and the reader idle.
                if (!r.lock())
                    return;
                put(app, kStreamWalk, r.s());
                while (r.w() != 0)
                {
                    const reg32 w = r.w();
                    put(app, at(app, w + 0x10), at(app, w + 0x68));
                    put(app, at(app, w + 0x10) + 4, 8);
                    put(app, w + 0x10, at(app, w + 0x10) + 8);
                    put(app, w + 0xc, at(app, w + 0x10));
                    put(app, kStreamWalk, at(app, w + 0x70));
                }
                if (!r.unlock())
                    return;
                r.set(0x20, 7);
                continue;
            }
            if (!fail(app, cpu, frame, kCdFile, 0x54a788, 0x638,
                      {0x54a800, r.field(0x48), at(app, r.w() + 0x3c), r.field(0x5c)}))
                return;
        }
        // The chunk to its stream.
        if (r.s() == r.w())
        {
            ending = bigEndian(at(app, r.field(0x10))) == kEndId;
        }
        else
        {
            ending = false;
            const reg32 w = r.w();
            reg32 room;
            if (!r.ask(0x4e6710, w, room))
                return;
            if (room <= r.field(0x48) + r.field(0x40) + 8)
            {
                if ((go = r.waitTillEndRoomFree(w)) != 1 || (go = r.waitTillAhead(w, 8, false)) != 1
                    || (go = r.waitTillStart(w, r.field(0x48) + r.field(0x40) + 8, false)) != 1)
                {
                    if (go == 0)
                        return;
                    continue;
                }
                if (!r.lock())
                    return;
                put(app, at(app, w + 0x10), kWrap);
                put(app, w + 0x10, at(app, w + 4));
                put(app, w + 0xc, at(app, w + 0x10));
                if (!r.unlock())
                    return;
            }
            if (s32(app, r.s() + 0x44) >= 0)
            {
                if ((go = r.waitTillAhead(w, r.field(0x4c))) != 1)
                {
                    if (go == 0)
                        return;
                    continue;
                }
                if (!r.lock() || !r.move(r.field(0x10), at(app, w + 0x10), r.field(0x4c)))
                    return;
                put(app, w + 0xc, at(app, w + 0x10) + r.field(0x4c));
                r.set(0xc, r.field(0x10));
                r.set(0x4c, 0);
            }
            else
            {
                if ((go = r.waitTillAhead(w, r.field(0x48))) != 1)
                {
                    if (go == 0)
                        return;
                    continue;
                }
                if (!r.lock() || !r.move(r.field(0x10), at(app, w + 0x10), r.field(0x48)))
                    return;
                put(app, w + 0xc, at(app, w + 0x10) + r.field(0x48));
                r.set(0x4c, 0u - r.field(0x44));
                if (!r.move(r.field(0x48) + r.field(0x10), r.field(0x10), r.field(0x4c)))
                    return;
                r.set(0xc, r.field(0xc) - r.field(0x48));
            }
            if (!r.unlock())
                return;
        }
        // What is left of the chunk read on into its stream's ring: room made
        // at the ring's start first when the end has too little.
        if (s32(app, r.s() + 0x44) > 0)
        {
            const reg32 w = r.w();
            reg32 room;
            if (!r.ask(0x4e6710, w, room))
                return;
            if (room <= r.field(0x44) + r.field(0x40) + 8)
            {
                if ((go = r.waitTillEndRoomFree(w)) != 1 || (go = r.waitTillStart(w, r.field(0x4c))) != 1)
                {
                    if (go == 0)
                        return;
                    continue;
                }
                if (!r.lock() || !r.move(at(app, w + 0x10), at(app, w + 4), r.field(0x4c)))
                    return;
                put(app, at(app, w + 0x10), kWrap);
                put(app, w + 0xc, at(app, w + 4) + r.field(0x4c));
                put(app, w + 0x10, at(app, w + 4));
                if (!r.unlock())
                    return;
            }
        }
        while (s32(app, r.s() + 0x44) > 0)
        {
            const reg32 w = r.w();
            if ((go = r.waitTillAhead(w, r.field(0x40))) != 1)
                break;
            if (!r.readBlocks(at(app, w + 0xc)) || !r.lock())
                return;
            r.set(0x5c, r.field(0x5c) + r.field(0x40));
            put(app, w + 0xc, at(app, w + 0xc) + r.field(0x40));
            r.set(0x44, r.field(0x44) - r.field(0x40));
            if (!r.unlock())
                return;
        }
        if (go == 0)
            return;
        if (r.command())
            continue;
        // The chunk done: its stream's write end past it.
        if (!r.lock())
            return;
        const reg32 w = r.w();
        put(app, w + 0x10, at(app, w + 0x10) + r.field(0x48));
        put(app, w + 0xb8, at(app, w + 0xb8) + (r.field(0x48) - 8));
        if (ending)
        {
            r.set(0x20, 7);
            if (!r.unlock())
                return;
            continue;
        }
        if (!r.unlock())
            return;
        if (w == r.s())
        {
            if (!r.lock())
                return;
            r.set(0x4c, at(app, w + 0xc) - at(app, w + 0x10));
            if (!r.unlock())
                return;
        }
        else if (r.field(0x4c) == 0)
        {
            const reg32 over = at(app, w + 0xc) - at(app, w + 0x10);
            reg32 room;
            if (!r.ask(0x4e6710, r.s(), room))
                return;
            if (i32(room) <= i32(over))
            {
                if ((go = r.waitTillEndRoomFree(r.s())) != 1 || (go = r.waitTillStart(r.s(), over)) != 1)
                {
                    if (go == 0)
                        return;
                    continue;
                }
                if (!r.lock())
                    return;
                put(app, r.field(0x10), kWrap);
                r.set(0x10, r.field(4));
                r.set(0xc, r.field(0x10));
                if (!r.unlock())
                    return;
            }
            if ((go = r.waitTillAhead(r.s(), at(app, r.w() + 0xc) - at(app, r.w() + 0x10))) != 1)
            {
                if (go == 0)
                    return;
                continue;
            }
            if (!r.lock())
                return;
            const reg32 ww = r.w();
            const reg32 bytes = at(app, ww + 0xc) - at(app, ww + 0x10);
            r.set(0x4c, bytes);
            if (!r.move(at(app, ww + 0x10), r.field(0x10), r.field(0x4c)))
                return;
            put(app, ww + 0xc, at(app, ww + 0x10));
            r.set(0xc, r.field(0x10) + r.field(0x4c));
            if (!r.unlock())
                return;
        }
        // On: the next chunk while the file has more and no command waits;
        // at the file's end every ring given a dropped-chunk mark.
        if (s32(app, r.s() + 0x5c) - s32(app, r.s() + 0x4c) < s32(app, r.s() + 0x54))
            continue;
        if (r.field(0x78) != 0)
        {
            r.set(0x20, 7);
            continue;
        }
        put(app, kStreamWalk, r.s());
        bool interrupted = false;
        while (r.w() != 0)
        {
            const reg32 ww = r.w();
            int g = r.waitWhile([&](bool& busy) {
                reg32 a;
                if (!r.ask(0x4e66e0, ww, a))
                    return false;
                busy = a + at(app, ww + 0x4c) <= 8;
                return true;
            });
            if (g == 0)
                return;
            if (g == 2)
            {
                interrupted = true;
                break;
            }
            put(app, kStreamWalk, at(app, ww + 0x70));
        }
        (void)interrupted;
        if (!r.lock())
            return;
        put(app, kStreamWalk, r.s());
        while (r.w() != 0)
        {
            const reg32 ww = r.w();
            put(app, at(app, ww + 0x10), kDropped);
            put(app, at(app, ww + 0x10) + 4, 8);
            put(app, ww + 0x10, at(app, ww + 0x10) + 8);
            put(app, ww + 0xc, at(app, ww + 0x10));
            put(app, kStreamWalk, at(app, ww + 0x70));
        }
        if (!r.unlock())
            return;
        r.set(0x20, 7);
    }
}

}  // namespace snd
}  // namespace nfs3hp
