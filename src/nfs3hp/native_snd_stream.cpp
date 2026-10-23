#include "native_snd.h"

/* EA's streaming, native (native_snd.cpp says how): the system tasks the
 * game's loop and the streams run on, the coordination of the stream's top-up
 * with the game's file loads, the SND streamer that plays a stream (music, a
 * movie's sound) through a voice, and the CD stream under it, whose reader
 * thread reads the stream's file into a ring of chunks.
 *
 * The system tasks: 16 of 0x10 bytes at 0x9ef7e8 -- the function, its period
 * in ticks, the tick it runs next, whether it runs now.
 *
 * The streamer's state (sstream.c) at 0x564670..0x56480c: 0x56467c the CD
 * stream, 0x564680/0x564684 the queue of chunks to play, 0x564688 the chunk
 * playing, 0x564690 the voice's handle, 0x5646a0 the stream's patch,
 * 0x5646fd its state (0 off, 1 filling, 2 playing, 3 ending, 4 interrupted),
 * 0x5646ff the voice's chunk count, 0x56470d the playing chunk's state,
 * 0x56470e/0x56470f and 0x56471c the loops' ring, 0x56478c the file's name.
 *
 * A CD stream (cdstream.c), 0xc0 bytes and its command blocks of 0x9c:
 * +4/+8 the ring's start and end, +0xc where the reader writes, +0x10 its
 * chunk's start, +0x14 where the player reads, +0x18 what was freed, +0x1c
 * the file, +0x20 the reader's state, +0x24 a command waiting, +0x28 busy,
 * +0x3c the ring's size, +0x40 the block read at once, +0x70 the next stream,
 * +0x74 the free command blocks, +0x78/+0x7c the commands queued, +0x80 the
 * command being done, +0x8c the reader thread, +0xa4/+0xa8 its events, +0xac
 * its lock, +0xb4 whether the reader waits, +0xb8/+0xbc bytes read and
 * played. */
namespace nfs3hp
{
namespace snd
{

namespace
{

// The system tasks.
constexpr reg32 kTasks = 0x9ef7e8, kTaskCount = 0x10;
constexpr reg32 kTaskDepth = 0x564670;      // the tasks' nesting
constexpr reg32 kTaskTick = 0x564674;       // the tick the tasks last ran at
constexpr reg32 kTaskTiming = 0x56466c, kTaskTime = 0x564668;
constexpr reg32 kRdtscOk = 0x5643bc;
constexpr reg32 kClock = 0x79c1a0;          // the tasks' clock
constexpr reg32 kTimer = 0x79c1a4;          // the game's timer, 60 a second
constexpr reg32 kSoundRunning = 0x5643d8;   // the sound thread runs
// The streamer's.
constexpr reg32 kCdStream = 0x56467c;
constexpr reg32 kQueueHead = 0x564680, kQueueTail = 0x564684, kPlaying = 0x564688;
constexpr reg32 kStreamHandle = 0x564690;
constexpr reg32 kChunksPlayed = 0x564694, kChunksQueued = 0x564698, kBytesQueued = 0x56469c;
constexpr reg32 kStreamPatch = 0x5646a0;
constexpr reg32 kPatchSet = 0x5646fc, kStreamState = 0x5646fd, kNoEnd = 0x5646fe, kVoiceChunks = 0x5646ff;
constexpr reg32 kFirstHeader = 0x564700, kStreamVoice = 0x564701;
constexpr reg32 kStreamVolume = 0x564702, kStreamPan = 0x564703, kStreamBend = 0x564704, kStreamEffect = 0x564705;
constexpr reg32 kStartTries = 0x564706, kServiceAdded = 0x564708;
constexpr reg32 kFilesQueued = 0x564709, kFilesStarted = 0x56470a, kSkipHeaders = 0x56470b, kFormatKnown = 0x56470c;
constexpr reg32 kChunkState = 0x56470d, kLoopNow = 0x56470e, kLoopLast = 0x56470f;
constexpr reg32 kHeadersSeen = 0x564710, kHeadersWanted = 0x564714, kBytesWanted = 0x564718;
constexpr reg32 kLoops = 0x56471c;
constexpr reg32 kTopupWanted = 0x56476c, kTopupBy = 0x564770;
constexpr reg32 kOldFormat = 0x564774, kNewFormat = 0x564780;
constexpr reg32 kStreamName = 0x56478c, kStreamNameEnd = 0x56480b;
constexpr reg32 kEndsSeen = 0x564678;
constexpr reg32 kTopupHook = 0x56480c;      // Pathfinder's, when it streams
constexpr reg32 kNextChunk = 0x5678b4;      // what the mixer calls for the next chunk
constexpr reg32 kStreamerRestore = 0xa09b30;
constexpr reg32 kStreamService = 0x4e85a8;
// The top-up's coordination (iocoord.c).
constexpr reg32 kTopupFunction = 0x9f6a50;
constexpr reg32 kTopupEvent = 0x567864, kToppedUp = 0x56785c;
constexpr reg32 kLoadLock = 0x564480;
// The CD stream's.
constexpr reg32 kStreams = 0x5645b8, kStreamWalk = 0x5645bc, kBlockCount = 0x5645a4;
constexpr reg32 kMainThread = 0x4df930, kCreateEvent = 0x4dfb00, kSetEvent = 0x4dfb20, kWaitEvent = 0x4dfb70;
constexpr reg32 kCloseHandle = 0x4dfc00, kSleep = 0x4df8e0, kCreateThread = 0x4df7a0, kRemoveThread = 0x4df870;
constexpr reg32 kNewLock = 0x4eb2e0, kFreeLock = 0x4eb360;
constexpr reg32 kAllocate = 0x4e1620, kFree = 0x4e1890, kFillZero = 0x4e070c, kTouch = 0x5011a0;
constexpr reg32 kStrncpy = 0x4e0e30, kStrncmp = 0x4eb390, kMoveMemory = 0x4ea4f0;
constexpr reg32 kTrace = 0x4e08f0;
constexpr reg32 kOpenBlock = 0x501270, kCloseBlock = 0x5013a0, kReadBlock = 0x5013b0, kSeekBlock = 0x501450;

constexpr reg32 kStreamFile = 0x54ac34, kCdFile = 0x54a3d0, kTaskFile = 0x54abf8;

/* The lock's calls, its address left in eax as the code pushes it from there. */
bool lock(App* app, CPU& cpu, reg32 section)
{
    cpu.eax = section;
    return call(app, cpu, at(app, kEnterCriticalSection), {section});
}

bool unlock(App* app, CPU& cpu, reg32 section)
{
    cpu.eax = section;
    return call(app, cpu, at(app, kLeaveCriticalSection), {section});
}

bool enter(App* app, CPU& cpu) { return call(app, cpu, 0x500e20); }
bool leave(App* app, CPU& cpu) { return call(app, cpu, 0x500e7c); }

/* A function of the game's with eax, its result back in `result`. */
bool ask(App* app, CPU& cpu, reg32 target, reg32 eax, reg32& result)
{
    if (!callWith(app, cpu, target, eax))
        return false;
    result = cpu.eax;
    return true;
}

/* freeChunk's call: chunk edx of stream eax given back to the reader. */
bool freeChunk(App* app, CPU& cpu, reg32 stream, reg32 chunk)
{
    return callWith(app, cpu, 0x4e68a0, stream, chunk);
}

}  // namespace

/* 0x4e7520 (addsystemtask): function eax run every edx ticks, the first in
 * ebx; in the first free slot past as many as the tasks are nested.  The tick
 * it runs first. */
void addSystemTask(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 function = cpu.eax, period = cpu.edx;
    reg32 skip = at(app, kTaskDepth);
    cpu.esp = kept.frame(4, 4);
    put(app, cpu.esp, cpu.ebx);
    put(app, kTaskDepth, skip + 1);
    reg32 slot = 0xffffffff;
    for (reg32 i = 0; i < kTaskCount; ++i)
    {
        const reg32 f = at(app, kTasks + 16 * i);
        if (f == function)
            slot = i;
        else if (f == 0 && slot == 0xffffffff)
        {
            if (skip == 0)
                slot = i;
            else
                --skip;
        }
    }
    if (slot == 0xffffffff)
    {
        if (!fail(app, cpu, cpu.esp, kTaskFile, 0x54ac08, 0x60, {0x54ac18}))
            return;
        put(app, kTaskDepth, at(app, kTaskDepth) - 1);
        kept.ret(cpu, cpu.eax);
        cpu.edx = skip + 1;
        return;
    }
    const reg32 t = kTasks + 16 * slot;
    put(app, t, function);
    put(app, t + 4, period);
    const reg32 first = at(app, kClock) + kept.ebx;
    put(app, t + 0xc, 0);
    put(app, t + 8, first);
    put(app, kTaskDepth, at(app, kTaskDepth) - 1);
    kept.ret(cpu, first);
    cpu.edx = at(app, kTaskDepth) + 1;
}

/* 0x4e75e0: function eax no longer a task.  Its slot's offset, 0x100 for none. */
void removeSystemTask(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 function = cpu.eax;
    reg32 offset = 0, index = 0;
    while (function != at(app, kTasks + offset))
    {
        offset += 0x10;
        ++index;
        if (offset >= 0x100)
            break;
    }
    if (index < kTaskCount && at(app, kTasks + index * 16) == function)
        put(app, kTasks + index * 16, 0);
    kept.ret(cpu, offset);
}

/* 0x4e7630: the tasks due by the clock run, once a tick: each with eax and
 * the ticks it was late in edx, not while it runs already.  What they gave
 * back, or-ed. */
void runSystemTasks(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 argument = cpu.eax;
    cpu.esp = kept.frame(6);
    reg32 result = 0, started = kept.ebp;
    if (at(app, kTaskTiming) != 0)
    {
        cpu.eax = argument;
        if (at(app, kRdtscOk) != 0)
            cpu.rdtsc();
        started = cpu.eax;
    }
    // The code's safepoint before the tick's test (0x4e7648), on every call.
    safepoint(app, cpu);
    // eax as the loop leaves it: the clock, 0 after a task ran.
    reg32 left = at(app, kClock);
    if (at(app, kTaskTick) != at(app, kClock))
    {
        put(app, kTaskTick, at(app, kClock));
        for (reg32 offset = 0; offset < 0x100; offset += 0x10)
        {
            // The loop's safepoint, as the code's: the frame wait polls the
            // clock through here, and the timer's thread advances it only
            // with the guest's context handed over.
            safepoint(app, cpu);
            const reg32 t = kTasks + offset;
            const reg32 function = at(app, t);
            if (function == 0)
                continue;
            left = at(app, kClock);
            if (s32(app, kClock) < s32(app, t + 8) || at(app, t + 0xc) != 0)
                continue;
            left = 0;
            put(app, t + 0xc, 1);
            cpu.ebx = function;
            cpu.ecx = offset;
            cpu.esi = result;
            cpu.edi = argument;
            cpu.ebp = started;
            if (!callWith(app, cpu, function, argument, at(app, kClock) - at(app, t + 8)))
                return;
            result |= cpu.eax;
            put(app, t + 8, at(app, kClock) + at(app, t + 4));
            put(app, t + 0xc, 0);
        }
    }
    if (at(app, kTaskTiming) != 0)
    {
        cpu.eax = left;
        if (at(app, kRdtscOk) != 0)
            cpu.rdtsc();
        put(app, kTaskTime, at(app, kTaskTime) + (cpu.eax - started));
    }
    kept.ret(cpu, result);
}

/* 0x4e7720: the tasks run until eax ticks of the timer have passed or one
 * gave something back -- what it gave.  A busy wait the timer's thread ends. */
void waitSystemTasks(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(2);
    const reg32 until = cpu.eax + at(app, kTimer);
    reg32 result = 0;
    while (s32(app, kTimer) < i32(until) && result == 0)
    {
        safepoint(app, cpu);
        giveWay(app, cpu);
        if (!callWith(app, cpu, 0x4e7630, 0))
            return;
        result = cpu.eax;
    }
    kept.ret(cpu, result);
}

/* 0x4ff660: the stream's top-up function, eax (0 none). */
void setTopupFunction(App* app, CPU& cpu)
{
    put(app, kTopupFunction, cpu.eax);
    cpu.esp += 4;
}

/* 0x4ff670: the stream topped up with eax before a load -- under the load's
 * lock but on the main thread -- or, with no top-up, the wait ended at once. */
void topUpStream(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 argument = cpu.eax;
    cpu.esp = kept.frame(5);
    if (!callWith(app, cpu, kMainThread, 0))
        return;
    const bool other = cpu.eax == 0;
    if (at(app, kTopupEvent) == 0)
    {
        if (!call(app, cpu, kCreateEvent))
            return;
        put(app, kTopupEvent, cpu.eax);
    }
    if (at(app, kTopupFunction) != 0)
    {
        // The load's lock taken with the lock pushed from edi.
        if (other)
        {
            cpu.esp = kept.frame(6);
            if (!call(app, cpu, at(app, kEnterCriticalSection), {at(app, kLoadLock)}))
                return;
            cpu.esp = kept.frame(5);
        }
        put(app, kToppedUp, 0);
        cpu.ebp = 0;
        if (!callWith(app, cpu, at(app, kTopupFunction), argument, cpu.edx, argument, cpu.ecx))
            return;
        if (other && !unlock(app, cpu, at(app, kLoadLock)))
            return;
        kept.ret(cpu, cpu.eax);
        return;
    }
    put(app, kToppedUp, 1);
    if (!callWith(app, cpu, kSetEvent, 0, at(app, kTopupEvent)))
        return;
    kept.ret(cpu, cpu.eax);
}

/* 0x4ff700: waittopupstream's wait on the main thread -- entered by a jump
 * with edx and ebp pushed: an error while a surface is locked, then the tasks
 * run a ms apart until the top-up is done (or there is no event); edx and ebp
 * popped and back. */
void waitTopupMain(App* app, CPU& cpu)
{
    const reg32 esp = cpu.esp;
    if (!call(app, cpu, kSurfaceLocked))
        return;
    // The error with esi, ecx and ebx pushed (and popped after it).
    if (cpu.eax != 0)
    {
        put(app, esp - 4, cpu.esi);
        put(app, esp - 8, cpu.ecx);
        put(app, esp - 12, cpu.ebx);
        if (!fail(app, cpu, esp - 12, 0x54e0c4, 0x54e0d4, 0x5e, {0x54e0e4}))
            return;
    }
    cpu.edx = 0;
    for (;;)
    {
        safepoint(app, cpu);
        if (at(app, kTopupEvent) == 0)
            break;
        cpu.ebp = at(app, kToppedUp);
        if (cpu.ebp != 0)
            break;
        if (!callWith(app, cpu, kSleep, 1) || !callWith(app, cpu, 0x4e7630, cpu.ebp))
            return;
    }
    cpu.ebp = at(app, esp);
    cpu.edx = at(app, esp + 4);
    cpu.esp = esp + 12;
}

/* 0x4ff80f: waittopupstream's way out, by a jump: ebp and edx popped. */
void waitTopupDone(App* app, CPU& cpu)
{
    cpu.ebp = at(app, cpu.esp);
    cpu.edx = at(app, cpu.esp + 4);
    cpu.esp += 12;
}

/* 0x4ff76e: waittopupstream's wait on another thread: the event (edx)
 * waited for; edx and ebp popped and back. */
void waitTopupEvent(App* app, CPU& cpu)
{
    const reg32 esp = cpu.esp;
    if (!callWith(app, cpu, kWaitEvent, cpu.edx))
        return;
    cpu.ebp = at(app, esp);
    cpu.edx = at(app, esp + 4);
    cpu.esp = esp + 12;
}

/* 0x4ff7f0 (waittopupstream): the top-up waited for -- on the main thread
 * by the tasks, on another by its event (none, no wait). */
void waitTopupStream(App* app, CPU& cpu)
{
    put(app, cpu.esp - 4, cpu.edx);
    put(app, cpu.esp - 8, cpu.ebp);
    cpu.esp -= 8;
    if (!callWith(app, cpu, kMainThread, 0))
        return;
    // The waits are the code's jumps: on with the stack as it is.
    if (cpu.eax != 0)
    {
        app->dynamic_call(0x4ff700, cpu);
        return;
    }
    cpu.edx = at(app, kTopupEvent);
    if (cpu.edx != 0)
    {
        app->dynamic_call(0x4ff76e, cpu);
        return;
    }
    cpu.ebp = at(app, cpu.esp);
    cpu.edx = at(app, cpu.esp + 4);
    cpu.esp += 12;
}

/* 0x4ff7c0: before a load, the stream topped up (when it plays and the sound
 * runs) and that waited for, as waittopupstream after it. */
void topUpBeforeLoad(App* app, CPU& cpu)
{
    if (at(app, kTopupFunction) == 0 || at(app, kSoundRunning) == 0)
    {
        cpu.esp += 4;
        return;
    }
    if (!call(app, cpu, 0x4ff670))
        return;
    waitTopupStream(app, cpu);
}

/* 0x4ff7e0: the ret of topUpBeforeLoad's. */
void topupReturn(App*, CPU& cpu)
{
    cpu.esp += 4;
}

/* 0x4ff780: the top-up done, its waiters let go. */
void topupDone(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(2);
    if (at(app, kTopupEvent) != 0)
    {
        put(app, kToppedUp, 1);
        if (!callWith(app, cpu, kSetEvent, 0, at(app, kTopupEvent)))
            return;
    }
    kept.ret(cpu, cpu.eax);
}

/* 0x4ff7b0: whether the top-up is done. */
void toppedUp(App* app, CPU& cpu)
{
    cpu.eax = at(app, kToppedUp);
    cpu.esp += 4;
}

/* 0x4ff820, 0x4ff830: the load's block size and its flags. */
void loadBlockSize(App*, CPU& cpu)
{
    cpu.eax = 0x3e8;
    cpu.esp += 4;
}

void loadFlags(App*, CPU& cpu)
{
    cpu.eax = 0;
    cpu.esp += 4;
}

/* 0x5017b4: the chunks the platform holds of a stream's: none here. */
void platformChunks(App*, CPU& cpu)
{
    cpu.eax = 0;
    cpu.esp += 4;
}

/* 0x5016c0 (iSNDclearchunk): edx frames of silence at eax in voice ebx's
 * format: XA's 8-byte header and 15 bytes a 28 frames, or PCM's zeros. */
void iSNDclearchunk(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 buffer = cpu.eax, p = platform(cpu.ebx);
    i32 frames = i32(cpu.edx);
    const reg32 compression = byte(app, p + 4);
    reg32 eax = (buffer & 0xffff00ff) | compression << 8;
    if (compression == 7)
    {
        const i32 blocks = quotient(frames + 0x1b, 0x1c);
        for (reg32 i = 0; i < 8; i += 2)
            putHalf(app, buffer + i, 0);
        i32 bytes = blocks * 15;
        if (byte(app, p + 3) == 2)
            bytes += bytes;
        eax = 0;
        for (i32 i = 0; i < bytes; ++i)
            putByte(app, buffer + 8 + reg32(i), 0), eax = reg32(i + 1);
        kept.ret(cpu, eax);
        cpu.edx = reg32(bytes);
        cpu.ebx = 0x1c | byte(app, p + 3) << 8;
        return;
    }
    if (compression == 9)
    {
        kept.ret(cpu, eax);
        return;
    }
    if (compression == 0)
    {
        if (byte(app, p + 3) == 2)
            frames += frames;
        const reg32 bits = byte(app, p + 2);
        eax = (buffer & 0xffff00ff) | bits << 8;
        if (bits == 0x10)
        {
            eax = 0;
            for (i32 i = 0; i < frames; ++i)
                putHalf(app, buffer + 2 * reg32(i), 0), eax = reg32(i + 1);
        }
        else if (bits == 8 && frames > 0)
        {
            for (i32 i = 0; i < frames; ++i)
                putByte(app, buffer + reg32(i), 0);
            eax = buffer + reg32(frames);
        }
        kept.ret(cpu, eax);
        cpu.edx = reg32(frames);
        return;
    }
    // Error with eax as the code has it, edx and ebx left as the error's file
    // and line.
    cpu.eax = eax;
    cpu.ecx = 0x54e5f8;
    cpu.edx = 0x54e5e8;
    cpu.ebx = 0x4a;
    if (!fail(app, cpu, kept.frame(2), 0x54e5e8, 0x54e5f8, 0x4a, {0x54e608}))
        return;
    const reg32 edx = cpu.edx, ebx = cpu.ebx;
    kept.ret(cpu, cpu.eax);
    cpu.edx = edx;
    cpu.ebx = ebx;
}

/* 0x4e7470 (SNDstreamautovol): the stream's voice to volume edx over eax
 * ticks. */
void SNDstreamautovol(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 ticks = cpu.eax, volume = cpu.edx;
    cpu.esp = kept.frame(2);
    if (byte(app, kInited) == 0)
    {
        kept.ret(cpu, 0xfffffff2);
        return;
    }
    if (i32(volume) > 0x7f || i32(volume) < 0)
    {
        if (!fail(app, cpu, kept.frame(3), 0x54ab74, 0x54ab84, 0x7c, {0x54ab98, volume}))
            return;
        kept.ret(cpu, 0xfffffff8);
        return;
    }
    putByte(app, kStreamVolume, reg8(volume));
    if (!callWith(app, cpu, 0x4e9420, at(app, kStreamHandle), ticks, volume, at(app, kStreamHandle)))
        return;
    kept.ret(cpu, 0);
}

/* 0x4e74f0: the stream's volume: its voice's, or what it was set to. */
void SNDstreamgetvol(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    if (byte(app, kInited) == 0)
    {
        kept.ret(cpu, 0xfffffff2);
        return;
    }
    cpu.esp = kept.frame(1);
    reg32 volume;
    if (!ask(app, cpu, 0x501670, at(app, kStreamHandle), volume))
        return;
    kept.ret(cpu, i32(volume) < 0 ? reg32(sbyte(app, kStreamVolume)) : volume);
}

/* 0x4e8944: the streamer reset: nothing queued, no voice, the mixer's refill
 * its, and its service among the tasks. */
void resetStreamer(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(3);
    put(app, kNextChunk, 0x4e8328);
    put(app, kStreamerRestore, 0x4e784c);
    for (const reg32 a : {kHeadersSeen, kChunksPlayed, kChunksQueued, kBytesQueued, kQueueHead, kQueueTail})
        put(app, a, 0);
    put(app, kStreamHandle, 0xffffffff);
    putByte(app, kStreamState, 0);
    putByte(app, kLoopNow, 0);
    putByte(app, kLoopLast, 0);
    put(app, kLoops + 4 * reg32(sbyte(app, kLoopLast)), 0xffffffff);
    putByte(app, kNoEnd, 1);
    putByte(app, kChunkState, 0);
    if (byte(app, kServiceAdded) == 0)
    {
        if (!callWith(app, cpu, 0x4e7520, kStreamService, 0, 1, 0xffffffff))
            return;
        putByte(app, kServiceAdded, 1);
    }
    kept.ret(cpu, 0);
}

/* 0x4e7750 (SNDstreamsetup): the streamer set up on CD stream eax, the
 * play's options at edx. */
void SNDstreamsetup(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 stream = cpu.eax, options = cpu.edx;
    cpu.esp = kept.frame(3);
    if (byte(app, kInited) == 0)
    {
        kept.ret(cpu, 0xfffffff2);
        return;
    }
    if (at(app, kStreamerRestore) != 0)
    {
        if (!fail(app, cpu, kept.frame(3), kStreamFile, 0x54ac44, 0xb1, {0x54ac54}))
            return;
        kept.ret(cpu, 0xfffffff0);
        return;
    }
    reg32 result;
    if (!enter(app, cpu) || !ask(app, cpu, 0x5017b4, cpu.eax, result))
        return;
    if (i32(result) < 0)
    {
        if (!leave(app, cpu))
            return;
        kept.ret(cpu, result);
        return;
    }
    cpu.esp = kept.frame(4);
    putByte(app, kStreamName, 0);
    putByte(app, kFirstHeader, 1);
    put(app, 0x56468c, 0);
    putByte(app, kStreamVolume, byte(app, options + 8));
    putByte(app, kStreamPan, byte(app, options + 7));
    putByte(app, kStreamBend, byte(app, options + 9));
    putByte(app, kStreamEffect, byte(app, options + 0xa));
    put(app, kCdStream, stream);
    putByte(app, kPatchSet, 0);
    putByte(app, kFilesQueued, 0);
    putByte(app, kFilesStarted, 0);
    put(app, kHeadersWanted, 0xf);
    putByte(app, kSkipHeaders, 0xff);
    putByte(app, kFormatKnown, 0);
    if (!call(app, cpu, 0x4e8944) || !leave(app, cpu))
        return;
    kept.ret(cpu, result);
}

/* 0x4e784c (SNDstreamrestore): the streamer done with: its stream purged,
 * its service gone. */
void SNDstreamrestore(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(1);
    if (!callWith(app, cpu, 0x4ff660, 0))
        return;
    if (byte(app, kInited) == 0 || at(app, kStreamerRestore) == 0)
    {
        kept.ret(cpu, 0xfffffff2);
        return;
    }
    if (!call(app, cpu, 0x4e7b28))
        return;
    if (byte(app, kServiceAdded) != 0)
    {
        if (!callWith(app, cpu, 0x4e75e0, kStreamService))
            return;
        putByte(app, kServiceAdded, 0);
    }
    cpu.esp = kept.frame(2);
    put(app, kStreamerRestore, 0);
    if (!call(app, cpu, 0x5017b4))
        return;
    kept.ret(cpu, 0);
}

/* 0x4e78a0 (SNDstreamqueue): file eax queued to play, from offset edx: the
 * first starts the stream; another is read on as the stream needs it, but
 * for at most 19 files at once.  0, -13 for no room, -14 before the setup. */
void SNDstreamqueue(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 name = cpu.eax, offset = cpu.edx;
    cpu.esp = kept.frame(3);
    if (byte(app, kInited) == 0)
    {
        kept.ret(cpu, 0xfffffff2);
        return;
    }
    if (at(app, kStreamerRestore) == 0)
    {
        if (!fail(app, cpu, kept.frame(3), kStreamFile, 0x54aca4, 0x1c5, {0x54acb4}))
            return;
        kept.ret(cpu, 0xfffffff2);
        return;
    }
    if (byte(app, kStreamState) == 0)
    {
        if (offset != 0)
        {
            if (!callWith(app, cpu, 0x4e4fe0, at(app, kCdStream), name)
                || !callWith(app, cpu, 0x4e5060, at(app, kCdStream), offset))
                return;
        }
        else if (!callWith(app, cpu, 0x4e4f20, at(app, kCdStream), name))
            return;
        if (!enter(app, cpu) || !call(app, cpu, 0x4e8944))
            return;
        putByte(app, kStreamState, 1);
        if (!leave(app, cpu))
            return;
    }
    else
    {
        if (!enter(app, cpu))
            return;
        const bool full = sbyte(app, kFilesQueued) + sbyte(app, kFilesStarted) >= 0x13;
        if (!leave(app, cpu))
            return;
        if (full)
        {
            kept.ret(cpu, 0xfffffff3);
            return;
        }
        reg32 room;
        if (!ask(app, cpu, 0x4e6a70, offset == 0 ? 1 : 2, room))
            return;
        if (room == 0)
        {
            kept.ret(cpu, 0xfffffff3);
            return;
        }
        if (offset == 0)
        {
            if (!callWith(app, cpu, 0x4e4ee0, at(app, kCdStream), name))
                return;
        }
        else
        {
            if (!callWith(app, cpu, kStrncmp, kStreamName, name, 0x80))
                return;
            if (cpu.eax != 0 && !callWith(app, cpu, 0x4e4fa0, at(app, kCdStream), name))
                return;
            if (!callWith(app, cpu, 0x4e5060, at(app, kCdStream), offset))
                return;
        }
    }
    putByte(app, kFilesQueued, reg8(byte(app, kFilesQueued) + 1));
    if (!callWith(app, cpu, kStrncpy, kStreamName, name, 0x80))
        return;
    putByte(app, kStreamNameEnd, 0);
    kept.ret(cpu, 0);
}

/* 0x4e7a14 (SNDstreaminterrupt): the stream cut to file eax at offset edx:
 * what the reader holds past the voice's chunks dropped.  0; -18 while
 * already interrupted, -16 when not playing. */
void SNDstreaminterrupt(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 name = cpu.eax, offset = cpu.edx;
    cpu.esp = kept.frame(3);
    if (byte(app, kInited) == 0)
    {
        kept.ret(cpu, 0xfffffff2);
        return;
    }
    if (at(app, kStreamerRestore) == 0)
    {
        if (!fail(app, cpu, kept.frame(3), kStreamFile, 0x54ace0, 0x21b, {0x54acf4}))
            return;
        kept.ret(cpu, 0xfffffff2);
        return;
    }
    if (byte(app, kStreamState) == 4)
    {
        kept.ret(cpu, 0xffffffee);
        return;
    }
    if (byte(app, kStreamState) != 2)
    {
        kept.ret(cpu, 0xfffffff0);
        return;
    }
    if (!callWith(app, cpu, 0x4e4f60, at(app, kCdStream), name)
        || !callWith(app, cpu, 0x4e5060, at(app, kCdStream), offset) || !enter(app, cpu))
        return;
    reg32 c = at(app, kQueueHead);
    for (reg32 i = 0; i32(i) < i32(byte(app, kVoiceChunks) * 3) && c != at(app, kQueueTail); ++i)
        c = at(app, c);
    put(app, kQueueTail, c);
    c = at(app, c);
    while (c != 0)
    {
        const reg32 chunk = c;
        c = at(app, c);
        if (!freeChunk(app, cpu, at(app, kCdStream), chunk))
            return;
        put(app, kChunksQueued, at(app, kChunksQueued) - 1);
    }
    if (!leave(app, cpu))
        return;
    putByte(app, kStreamState, 4);
    if (!callWith(app, cpu, kStrncpy, kStreamName, name, 0x80))
        return;
    putByte(app, kStreamNameEnd, 0);
    kept.ret(cpu, 0);
}

/* 0x4e7b28 (SNDstreampurge): the stream stopped -- its voice, waited for --
 * and everything it held dropped. */
void SNDstreampurge(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(3);
    if (byte(app, kInited) == 0)
    {
        kept.ret(cpu, 0xfffffff2);
        return;
    }
    if (at(app, kStreamerRestore) == 0)
    {
        if (!fail(app, cpu, kept.frame(5), kStreamFile, 0x54ad24, 0x2b3, {0x54ad34}))
            return;
        kept.ret(cpu, 0xfffffff2);
        return;
    }
    if (!callWith(app, cpu, 0x4e9670, at(app, kStreamHandle)))
        return;
    const reg32 deadline = at(app, kTicks) + 0xc8;
    for (;;)
    {
        reg32 stopped;
        if (!ask(app, cpu, 0x4e8fd0, at(app, kStreamHandle), stopped))
            return;
        if (stopped != 0)
            break;
        safepoint(app, cpu);
        if (deadline < at(app, kTicks)
            && !fail(app, cpu, kept.frame(3), kStreamFile, 0x54ad24, 0x2c6, {0x54ad60}))
            return;
        if (!callWith(app, cpu, 0x4e7630, 0))
            return;
    }
    if (!enter(app, cpu) || !call(app, cpu, 0x4e7ff8))
        return;
    putByte(app, kSkipHeaders, 0xff);
    for (const reg32 a : {kFormatKnown, kFilesQueued, kFilesStarted, kStreamState, kStreamName, kPatchSet})
        putByte(app, a, 0);
    if (!callWith(app, cpu, 0x4ff660, 0))
        return;
    if (byte(app, kServiceAdded) != 0)
    {
        if (!callWith(app, cpu, 0x4e75e0, kStreamService))
            return;
        putByte(app, kServiceAdded, 0);
    }
    if (!leave(app, cpu))
        return;
    kept.ret(cpu, 0);
}

/* 0x4e7c58 (SNDstreamchunksleft): the chunks queued to play. */
void SNDstreamchunksleft(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(1);
    reg32 result = 0xfffffff2;
    if (byte(app, kInited) == 0)
    {
        kept.ret(cpu, result);
        return;
    }
    if (at(app, kStreamerRestore) == 0)
    {
        if (!fail(app, cpu, kept.frame(4), kStreamFile, 0x54ada4, 0x34b, {0x54adb8}))
            return;
        kept.ret(cpu, result);
        return;
    }
    if (!enter(app, cpu))
        return;
    if (byte(app, kStreamState) != 0)
    {
        reg32 held;
        if (!ask(app, cpu, 0x5017b4, byte(app, kVoiceChunks), held))
            return;
        result = at(app, kChunksQueued) + held;
        if (byte(app, kChunkState) == 2)
            --result;
    }
    if (!leave(app, cpu))
        return;
    kept.ret(cpu, result);
}

/* 0x4e7ce0 (SNDstreambuftime): the stream's buffered time in ms: its chunks
 * left times 1000 over the voice's chunks a second. */
void SNDstreambuftime(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(2);
    if (byte(app, kInited) == 0)
    {
        kept.ret(cpu, 0xfffffff2);
        return;
    }
    if (at(app, kStreamerRestore) == 0)
    {
        if (!fail(app, cpu, kept.frame(2), kStreamFile, 0x54adec, 0x3c2, {0x54ae00}))
            return;
        kept.ret(cpu, 0xfffffff2);
        return;
    }
    cpu.esp = kept.frame(3);
    if (!enter(app, cpu))
        return;
    reg32 result = 0xfffffff2;
    if (byte(app, kStreamState) != 0 && byte(app, kStreamState) != 1)
    {
        cpu.esp = kept.frame(4);
        if (byte(app, kVoiceChunks) == 0
            && !fail(app, cpu, kept.frame(6), kStreamFile, 0x54adec, 0x3d3, {0x54ae30}))
            return;
        reg32 left;
        if (!ask(app, cpu, 0x4e7c58, cpu.eax, left))
            return;
        result = reg32(quotient(mul(i32(left), 1000), i32(byte(app, kVoiceChunks))));
    }
    if (!leave(app, cpu))
        return;
    kept.ret(cpu, result);
}

/* 0x4e7dd0: the top-up wanted no more: done (its waiters let go), and
 * Pathfinder's hook told with eax. */
void streamToppedUp(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 how = cpu.eax;
    cpu.esp = kept.frame(1);
    put(app, kTopupWanted, 0);
    if (!callWith(app, cpu, 0x4ff780, how, 0))
        return;
    if (at(app, kTopupHook) != 0 && !callWith(app, cpu, at(app, kTopupHook), 0, 0))
        return;
    kept.ret(cpu, cpu.eax);
}

/* 0x4e7df4 (iSNDstreamchecktopup): whether the top-up asked for is done --
 * the stream holds the time asked, its reader waits, or it has nothing more
 * to read -- or timed out. */
void iSNDstreamchecktopup(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(1);
    if (at(app, kTopupWanted) == 0)
    {
        kept.ret(cpu, cpu.eax);
        return;
    }
    if (!call(app, cpu, 0x4e7ce0))
        return;
    reg32 how = 0xffffffff;
    if (i32(cpu.eax) >= s32(app, kTopupWanted))
        how = 1;
    else
    {
        reg32 waiting;
        if (!ask(app, cpu, 0x4e6950, at(app, kCdStream), waiting))
            return;
        if (waiting != 0)
        {
            reg32 held;
            if (!ask(app, cpu, 0x5017b4, byte(app, kVoiceChunks), held))
                return;
            if (i32(held) > 1)
            {
                kept.ret(cpu, held);
                return;
            }
            how = 0;
        }
        else
        {
            if (!call(app, cpu, 0x4e68e0))
                return;
            if (cpu.eax != 0 && at(app, kTopupHook) == 0)
                how = 1;
        }
    }
    if (how != 0xffffffff && !callWith(app, cpu, 0x4e7dd0, how))
        return;
    // The timer read into eax, what the function gives back unless timed out.
    const reg32 timer = at(app, kTimer);
    if (i32(timer) > s32(app, kTopupBy))
    {
        cpu.eax = 0x412;
        if (!fail(app, cpu, kept.frame(2), kStreamFile, 0x54ae8c, 0x412, {0x54aea4})
            || !callWith(app, cpu, 0x4e7dd0, 0))
            return;
        kept.ret(cpu, cpu.eax);
        return;
    }
    kept.ret(cpu, timer);
}

/* 0x4e7e98 (iSNDstreamsetbuftime): a top-up to eax ms asked for (Pathfinder's
 * hook adding its own), within as many seconds as the sound thread runs. */
void iSNDstreamsetbuftime(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    reg32 wanted = cpu.eax;
    cpu.esp = kept.frame(3);
    if (byte(app, kInited) == 0)
    {
        kept.ret(cpu, cpu.eax);
        return;
    }
    if (i32(wanted) <= 0)
    {
        if (!fail(app, cpu, kept.frame(5), kStreamFile, 0x54aedc, 0x426, {0x54aef4}))
            return;
        kept.ret(cpu, cpu.eax);
        return;
    }
    if (at(app, kTopupHook) != 0)
    {
        if (!callWith(app, cpu, at(app, kTopupHook), wanted, wanted))
            return;
        wanted += cpu.eax;
    }
    put(app, kTopupBy, at(app, kTimer) + at(app, kSoundRunning) * 60);
    put(app, kTopupWanted, wanted);
    if (!call(app, cpu, kSurfaceLocked))
        return;
    if (cpu.eax == 0 && !call(app, cpu, 0x4e7df4))
        return;
    kept.ret(cpu, cpu.eax);
}

/* 0x4e7ff8: the chunks queued and playing given back to the reader. */
void dropQueuedChunks(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(2);
    if (!enter(app, cpu))
        return;
    if (at(app, kQueueHead) != 0)
    {
        while (at(app, kQueueHead) != at(app, kQueueTail))
        {
            const reg32 chunk = at(app, kQueueHead);
            put(app, kQueueHead, at(app, chunk));
            if (!freeChunk(app, cpu, at(app, kCdStream), chunk))
                return;
        }
        if (!freeChunk(app, cpu, at(app, kCdStream), at(app, kQueueHead)))
            return;
        if (at(app, kPlaying) != 0 && !freeChunk(app, cpu, at(app, kCdStream), at(app, kPlaying)))
            return;
    }
    put(app, kQueueHead, 0);
    put(app, kQueueTail, 0);
    put(app, kPlaying, 0);
    if (!leave(app, cpu))
        return;
    kept.ret(cpu, cpu.eax);
}

/* 0x4e8078: a data chunk ('SCDl', eax) queued to play.  3. */
void queueDataChunk(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 chunk = cpu.eax;
    put(app, kChunksQueued, at(app, kChunksQueued) + 1);
    put(app, kBytesQueued, at(app, kBytesQueued) + at(app, chunk + 4));
    if (at(app, chunk) != 0xffffffff)
        put(app, chunk, 0);
    if (at(app, kQueueHead) == 0)
    {
        put(app, kQueueHead, chunk);
        put(app, kQueueTail, chunk);
    }
    else
    {
        put(app, at(app, kQueueTail), chunk);
        put(app, kQueueTail, chunk);
    }
    kept.ret(cpu, 3);
}

/* 0x4e80cc (iSNDparseheader): a header chunk ('SCHl', eax): its patch copied
 * to the stream's and resolved -- a later file's started again when its
 * format differs.  1. */
void iSNDparseheader(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 chunk = cpu.eax;
    const reg32 f = kept.frame(6, 0x10);
    cpu.esp = f;
    if (sbyte(app, kSkipHeaders) > 0)
        putByte(app, kSkipHeaders, reg8(byte(app, kSkipHeaders) - 1));
    const reg32 size = at(app, chunk + 4) - 8;
    put(app, f + 0xc, chunk + 8);
    if ((i32(size) <= 0 || i32(size) > 0x5c)
        && !fail(app, cpu, f, kStreamFile, 0x54af34, 0x4aa, {0x54af44, 0x5c, size}))
        return;
    if (byte(app, kFirstHeader) != 0)
    {
        putByte(app, kFilesStarted, reg8(byte(app, kFilesStarted) + 1));
        putByte(app, kFilesQueued, reg8(byte(app, kFilesQueued) - 1));
        for (reg32 i = 0; i < 12; i += 4)
            put(app, kOldFormat + i, at(app, kNewFormat + i));
        if (!callWith(app, cpu, 0x502330, at(app, f + 0xc), kNewFormat))
            return;
        if (byte(app, kFormatKnown) != 0)
        {
            bool differs = false;
            for (reg32 i = 0; i < 8 && !differs; ++i)
                differs = byte(app, kNewFormat + i) != byte(app, kOldFormat + i);
            if (differs)
            {
                if (byte(app, kStreamState) != 2 && byte(app, kStreamState) != 3)
                {
                    if (!call(app, cpu, 0x4e89f8))
                        return;
                    if (i32(cpu.eax) < 0 && !fail(app, cpu, f, kStreamFile, 0x54af34, 0x4c7, {0x54afbc}))
                        return;
                }
                putByte(app, kStreamState, 3);
            }
        }
        putByte(app, kFormatKnown, 1);
    }
    for (reg32 i = 0; i < size; ++i)
        putByte(app, kStreamPatch + i, byte(app, at(app, f + 0xc) + i));
    put(app, f, 0xffffffff);
    if (!callWith(app, cpu, 0x5021ac, kStreamPatch, 0, f, 0xffffffff))
        return;
    putByte(app, kPatchSet, 1);
    if (!freeChunk(app, cpu, at(app, kCdStream), chunk))
        return;
    kept.ret(cpu, 1);
}

/* 0x4e8258: a loop chunk ('SCCl', eax): its count into the loops' ring.  2. */
void queueLoopChunk(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 chunk = cpu.eax;
    cpu.esp = kept.frame(2);
    if (byte(app, kLoopNow) != byte(app, kLoopLast) || s32(app, kLoops + 4 * reg32(sbyte(app, kLoopNow))) > 0)
        putByte(app, kLoopLast, reg8(byte(app, kLoopLast) + 1));
    if (sbyte(app, kLoopLast) >= 0x14)
        putByte(app, kLoopLast, 0);
    put(app, kLoops + 4 * reg32(sbyte(app, kLoopLast)), at(app, chunk + 8));
    if (!freeChunk(app, cpu, at(app, kCdStream), chunk))
        return;
    kept.ret(cpu, 2);
}

/* 0x4e82c4: a seek chunk ('SCLl', eax): the reader sent back to its offset.  4. */
void streamSeekChunk(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 chunk = cpu.eax;
    cpu.esp = kept.frame(2);
    if (!callWith(app, cpu, 0x4e5020, at(app, kCdStream), at(app, chunk + 8)))
        return;
    if (!freeChunk(app, cpu, at(app, kCdStream), chunk))
        return;
    kept.ret(cpu, 4);
}

/* 0x4e82ec: an end chunk ('SCEl', eax): counted, the queue's last marked the
 * end unless the stream goes on.  5. */
void streamEndChunk(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 chunk = cpu.eax;
    cpu.esp = kept.frame(2);
    put(app, kEndsSeen, at(app, kEndsSeen) + 1);
    if (byte(app, kNoEnd) == 0)
        put(app, at(app, kQueueTail), 0xffffffff);
    if (!freeChunk(app, cpu, at(app, kCdStream), chunk))
        return;
    kept.ret(cpu, 5);
}

/* 0x4e8320: the ends seen. */
void streamEndsSeen(App* app, CPU& cpu)
{
    cpu.eax = at(app, kEndsSeen);
    cpu.esp += 4;
}

/* 0x4e7f30: a chunk the reader read (eax) handed on by its id: data, a
 * header, a loop, a seek, an end; another given back.  -15 for it, -14 before
 * SNDinit. */
void parseStreamChunk(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 chunk = cpu.eax;
    cpu.esp = kept.frame(2);
    if (byte(app, kInited) == 0)
    {
        kept.ret(cpu, 0xfffffff2);
        return;
    }
    cpu.esp = kept.frame(3);
    if (!enter(app, cpu))
        return;
    reg32 result = 0xfffffff1;
    const reg32 id = at(app, chunk);
    const struct { reg32 id, handler; } handlers[] = {
        {0x6c444353, 0x4e8078}, {0x6c484353, 0x4e80cc}, {0x6c434353, 0x4e8258}, {0x6c4c4353, 0x4e82c4},
        {0x6c454353, 0x4e82ec}};
    bool handled = false;
    for (const auto& h : handlers)
        if (id == h.id)
        {
            if (!ask(app, cpu, h.handler, chunk, result))
                return;
            handled = true;
        }
    if (!handled && !freeChunk(app, cpu, at(app, kCdStream), chunk))
        return;
    if (!leave(app, cpu))
        return;
    kept.ret(cpu, result);
}

/* 0x4e8328: the mixer's refill: the next chunk to play into [eax] and its
 * frames into [edx] -- the one playing given back first, the loops counted
 * down; a chunk's first pass silenced.  1 once the chunk plays, 0 before; at
 * the stream's end none. */
void nextStreamChunk(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 data = cpu.eax, frames = cpu.edx;
    cpu.esp = kept.frame(5);
    reg32 result = 0;
    // The chunk taken off the queue: the one playing given back, the counts
    // moved on, the loops' ring stepped when this loop ran out.
    auto take = [&](reg32 chunk) {
        put(app, kQueueHead, at(app, chunk));
        const reg32 bytes = at(app, chunk + 4);
        if (at(app, kPlaying) != 0 && !freeChunk(app, cpu, at(app, kCdStream), at(app, kPlaying)))
            return false;
        put(app, kPlaying, chunk);
        put(app, kChunksQueued, at(app, kChunksQueued) - 1);
        put(app, kBytesQueued, at(app, kBytesQueued) - bytes);
        put(app, kChunksPlayed, at(app, kChunksPlayed) + 1);
        const reg32 loop = kLoops + 4 * reg32(sbyte(app, kLoopNow));
        put(app, loop, at(app, loop) - 1);
        if (s32(app, kLoops + 4 * reg32(sbyte(app, kLoopNow))) <= 0)
        {
            putByte(app, kFilesStarted, reg8(byte(app, kFilesStarted) - 1));
            if (byte(app, kLoopNow) != byte(app, kLoopLast))
            {
                putByte(app, kLoopNow, reg8(byte(app, kLoopNow) + 1));
                if (sbyte(app, kLoopNow) >= 0x14)
                    putByte(app, kLoopNow, 0);
            }
        }
        return true;
    };
    const reg32 state = byte(app, kChunkState);
    if ((state == 2 || state == 1) && at(app, kQueueHead) != at(app, kQueueTail))
    {
        if (!take(at(app, kQueueHead)))
            return;
        putByte(app, kChunkState, 0);
    }
    if (at(app, kQueueHead) != at(app, kQueueTail))
    {
        const reg32 chunk = at(app, kQueueHead);
        put(app, data, chunk + 0xc);
        put(app, frames, at(app, chunk + 8));
        if (!take(chunk))
            return;
        kept.ret(cpu, result);
        return;
    }
    if (at(app, at(app, kQueueHead)) == 0xffffffff)
    {
        if (!freeChunk(app, cpu, at(app, kCdStream), at(app, kQueueHead)))
            return;
        put(app, data, 0);
        put(app, frames, 0);
        kept.ret(cpu, result);
        return;
    }
    put(app, data, at(app, kQueueHead) + 0xc);
    put(app, frames, at(app, at(app, kQueueHead) + 8));
    if (byte(app, kChunkState) == 1)
    {
        if (!callWith(app, cpu, 0x5016c0, at(app, data), at(app, frames), reg32(sbyte(app, kStreamVoice))))
            return;
        putByte(app, kChunkState, 2);
    }
    if (byte(app, kChunkState) == 0)
        putByte(app, kChunkState, 1);
    if (byte(app, kChunkState) == 2)
        result = 1;
    kept.ret(cpu, result);
}

/* 0x4e89f8 (iSNDstreamstart): the stream's voice started on its patch, with
 * the stream's volume, pan, bend and effect level: its handle, its voice, its
 * chunks; the top-up the loads wait for set.  The handle; -1 while the last
 * still plays. */
void iSNDstreamstart(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 f = kept.frame(1, 0x10);
    cpu.esp = f;
    reg32 stopped;
    if (!ask(app, cpu, 0x4e8fd0, at(app, kStreamHandle), stopped))
        return;
    if (stopped == 0)
    {
        kept.ret(cpu, 0xffffffff);
        return;
    }
    cpu.esp = f - 0xc;
    if (byte(app, kPatchSet) == 0 && !fail(app, cpu, f - 0x10, kStreamFile, 0x54b040, 0x714, {0x54b050}))
        return;
    if (!callWith(app, cpu, 0x4e9b20, f))
        return;
    putByte(app, f + 8, byte(app, kStreamVolume));
    putByte(app, f + 7, byte(app, kStreamPan));
    putByte(app, f + 9, byte(app, kStreamBend));
    putByte(app, f + 0xa, byte(app, kStreamEffect));
    if (!callWith(app, cpu, 0x501de8, kStreamPatch, f))
        return;
    put(app, kStreamHandle, cpu.eax);
    if (s32(app, kStreamHandle) < 0)
    {
        putHalf(app, kStartTries, reg16(half(app, kStartTries) + 1));
        if (half(app, kStartTries) > 0x2710
            && !fail(app, cpu, f - 0xc, kStreamFile, 0x54b040, 0x737, {0x54b074}))
            return;
        kept.ret(cpu, at(app, kStreamHandle));
        return;
    }
    reg32 index;
    if (!ask(app, cpu, 0x4ffc9c, at(app, kStreamHandle), index))
        return;
    putByte(app, kStreamVoice, reg8(index));
    putByte(app, kVoiceChunks, byte(app, voice(reg32(sbyte(app, kStreamVoice))) + 0xb));
    putByte(app, kStreamState, 2);
    putByte(app, kPatchSet, 0);
    putHalf(app, kStartTries, 0);
    if (!callWith(app, cpu, 0x4ff660, 0x4e7e98))
        return;
    kept.ret(cpu, at(app, kStreamHandle));
}

/* 0x4e8b60 (SNDstreamvol): the stream's volume to eax. */
void SNDstreamvol(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 volume = cpu.eax;
    cpu.esp = kept.frame(2);
    if (byte(app, kInited) == 0)
    {
        kept.ret(cpu, 0xfffffff2);
        return;
    }
    if (i32(volume) > 0x7f || i32(volume) < 0)
    {
        if (!fail(app, cpu, kept.frame(3), 0x54b0c0, 0x54b0cc, 0x74, {0x54b0dc, volume}))
            return;
        kept.ret(cpu, 0xfffffff8);
        return;
    }
    putByte(app, kStreamVolume, reg8(volume));
    if (!callWith(app, cpu, 0x4e95fc, at(app, kStreamHandle), volume))
        return;
    kept.ret(cpu, 0);
}

namespace
{

/* What iSNDstreamservice does with each chunk the reader has: parsed, until
 * none (0, or past -10: an error), or `stop` says so.  False when the game
 * stopped; `chunk` the last. */
bool readChunks(App* app, CPU& cpu, reg32& chunk, reg32& parsed, bool& error)
{
    error = false;
    if (!ask(app, cpu, 0x4e6740, at(app, kCdStream), chunk))
        return false;
    cpu.edx = chunk;
    parsed = 0xffffffff;
    if (i32(chunk) > 0 || i32(chunk) <= -10)
    {
        if (!ask(app, cpu, 0x4e7f30, chunk, parsed))
            return false;
        error = i32(parsed) < 0;
    }
    return true;
}

}  // namespace

/* 0x4e85a8 (iSNDstreamservice): the streamer's system task, by its state:
 * filling (the chunks parsed until the headers wanted are in, then the
 * voice started), playing (chunks parsed, the top-up checked), ending (the
 * voice stopped when the chunks run out), interrupted (the queue dropped and
 * the new file's chunks parsed). */
void iSNDstreamservice(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    if (!call(app, cpu, kSurfaceLocked))
        return;
    if (cpu.eax != 0)
    {
        kept.ret(cpu, 0);
        return;
    }
    cpu.esp = kept.frame(3);
    if (!enter(app, cpu))
        return;
    // Done: the lock left, edx as the last chunk or call left it (the code
    // keeps no edx of its caller's).
    auto done = [&] {
        if (!leave(app, cpu))
            return;
        const reg32 edx = cpu.edx;
        kept.ret(cpu, 0);
        cpu.edx = edx;
    };
    // The reader held back by the headers to skip until enough is read:
    // false when the service waits for it.
    auto readerReady = [&](bool& ready) {
        ready = true;
        if (byte(app, kSkipHeaders) != 0)
            return true;
        if (at(app, kBytesWanted) == 0xffffffff)
        {
            ready = false;
            return true;
        }
        reg32 bytes;
        if (!ask(app, cpu, 0x4e68c0, at(app, kCdStream), bytes))
            return false;
        if (i32(bytes) < s32(app, kBytesWanted))
        {
            reg32 waiting;
            if (!ask(app, cpu, 0x4e6950, at(app, kCdStream), waiting))
                return false;
            if (waiting == 0)
            {
                ready = false;
                return true;
            }
        }
        putByte(app, kSkipHeaders, 0xff);
        return true;
    };
    const reg32 state = byte(app, kStreamState);
    if (state == 1)
    {
        for (;;)
        {
            safepoint(app, cpu);
            if (byte(app, kFirstHeader) == 0 && s32(app, kHeadersSeen) >= s32(app, kHeadersWanted))
                return done();
            bool ready;
            if (!readerReady(ready))
                return;
            if (!ready)
                return done();
            reg32 chunk, parsed;
            bool error;
            if (!readChunks(app, cpu, chunk, parsed, error))
                return;
            if (i32(chunk) <= 0 && i32(chunk) > -10 && chunk != 0)
            {
                if (at(app, kHeadersSeen) == 0 || byte(app, kFirstHeader) == 0)
                    return done();
                if (!call(app, cpu, 0x4e89f8))
                    return;
                return done();
            }
            if (chunk != 0)
            {
                if (error)
                {
                    if (!fail(app, cpu, kept.frame(3), kStreamFile, 0x54b000, 0x61c, {0x54b014}))
                        return;
                }
                else if (parsed == 3)
                    put(app, kHeadersSeen, at(app, kHeadersSeen) + 1);
                else if (parsed == 1 && byte(app, kStreamState) != 1)
                    return done();
            }
            if (i32(chunk) > 0 || i32(chunk) <= -10)
                continue;
            if (byte(app, kFirstHeader) == 0)
                return done();
            bool start = s32(app, kHeadersSeen) >= s32(app, kHeadersWanted);
            if (!start && at(app, kHeadersSeen) != 0)
            {
                reg32 waiting;
                if (!ask(app, cpu, 0x4e6950, at(app, kCdStream), waiting))
                    return;
                start = waiting != 0;
            }
            if (!start)
            {
                if (at(app, kHeadersSeen) == 0)
                    return done();
                if (!call(app, cpu, 0x4e68e0))
                    return;
                if (cpu.eax == 0)
                    return done();
            }
            if (!call(app, cpu, 0x4e89f8))
                return;
            return done();
        }
    }
    if (state == 2)
    {
        for (;;)
        {
            safepoint(app, cpu);
            bool ready;
            if (!readerReady(ready))
                return;
            if (!ready)
                return done();
            reg32 chunk, parsed;
            bool error;
            if (!readChunks(app, cpu, chunk, parsed, error))
                return;
            if (parsed == 1 || !(i32(chunk) > 0 || i32(chunk) <= -10))
                break;
        }
        if (!call(app, cpu, 0x4e7df4))
            return;
        return done();
    }
    if (state == 3)
    {
        if (!call(app, cpu, 0x4e7c58))
            return;
        if (i32(cpu.eax) > 0)
            return done();
        reg32 stopped;
        if (!callWith(app, cpu, 0x4e9670, at(app, kStreamHandle))
            || !ask(app, cpu, 0x4e8fd0, at(app, kStreamHandle), stopped))
            return;
        if (stopped == 0)
            return done();
        putByte(app, kFilesStarted, reg8(byte(app, kFilesStarted) - 1));
        if (!call(app, cpu, 0x4e7ff8))
            return;
        cpu.edx = (cpu.edx & 0xffffff00) | 1;
        if (!call(app, cpu, 0x4e8944))
            return;
        putByte(app, kStreamState, 1);
        return done();
    }
    if (state == 4)
    {
        reg32 bytes;
        if (!call(app, cpu, 0x4e7df4) || !ask(app, cpu, 0x4e68c0, at(app, kCdStream), bytes))
            return;
        if (i32(bytes) <= 0x1388)
            return done();
        if (at(app, kQueueHead) != 0)
        {
            while (at(app, kQueueHead) != at(app, kQueueTail))
            {
                const reg32 chunk = at(app, kQueueHead);
                put(app, kQueueHead, at(app, chunk));
                if (chunk != at(app, kPlaying) && !freeChunk(app, cpu, at(app, kCdStream), chunk))
                    return;
            }
            if (!freeChunk(app, cpu, at(app, kCdStream), at(app, kQueueHead)))
                return;
        }
        put(app, kQueueHead, 0);
        put(app, kQueueTail, 0);
        putByte(app, kFilesQueued, 1);
        putByte(app, kFilesStarted, 0);
        for (const reg32 a : {kHeadersSeen, kChunksPlayed, kChunksQueued, kBytesQueued})
            put(app, a, 0);
        putByte(app, kLoopNow, 0);
        putByte(app, kLoopLast, 0);
        put(app, kLoops + 4 * reg32(sbyte(app, kLoopLast)), 0xffffffff);
        putByte(app, kChunkState, 0);
        for (;;)
        {
            safepoint(app, cpu);
            reg32 chunk;
            if (!ask(app, cpu, 0x4e6740, at(app, kCdStream), chunk))
                return;
            cpu.edx = chunk;
            if (i32(chunk) > 0 || i32(chunk) <= -10)
            {
                if (!callWith(app, cpu, 0x4e7f30, chunk))
                    return;
                continue;
            }
            break;
        }
        putByte(app, kStreamState, 2);
        return done();
    }
    done();
}

}  // namespace snd
}  // namespace nfs3hp
