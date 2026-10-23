#include "native_snd.h"

/* EA's SND library's start and end (cmn\sinit.c, win\sdriver.c) and the
 * sound thread under it, native (native_snd.cpp says how): SNDinit checks the
 * mode against eacsnd's, loads eacsnd and has the game's message thread start
 * the driver -- the mixer, eacsnd's own start, the sound thread that serves
 * the library 100 times a second, the audio focus handler -- and waits for it;
 * SNDrestore undoes it all.
 *
 * The driver's state at 0x9ef600: +0 eacsnd's module, +4 the sound thread
 * started, +5 the focus handler added, +6 the restore registered at exit, +7
 * the message done, +8 the mode, +0xc the driver's result, +0x10 the mode
 * asked for, +0x14 the rate, +0x16 the rate set; eacsnd's functions at
 * +0x1c (its check), +0x20 (its start), +0x24 (its end), +0x54 (its volume). */
namespace nfs3hp
{
namespace snd
{

namespace
{

constexpr reg32 kModule = 0x9ef600, kThreadStarted = 0x9ef604, kFocusAdded = 0x9ef605, kAtExit = 0x9ef606;
constexpr reg32 kMessageDone = 0x9ef607, kMode = 0x9ef608, kDriverResult = 0x9ef60c, kModeAsked = 0x9ef610;
constexpr reg32 kRate = 0x9ef614, kRateSet = 0x9ef616;
constexpr reg32 kDirectCheck = 0x9ef61c, kDirectStart = 0x9ef620, kDirectEnd = 0x9ef624, kDirectVolume = 0x9ef654;
constexpr reg32 kFreeLibrary = 0x5344dc;
constexpr reg32 kLeaveAll = 0x564420;       // what Error calls to leave the library's lock
constexpr reg32 kSoundRunning = 0x5643d8;
constexpr reg32 kDriverFile = 0x549b10;
constexpr reg32 kMessage = 0x8200;
constexpr reg32 kRegisterHandler = 0x4cc6d0, kSendMessage = 0x4cc7c0, kFocusHandler = 0x4cc860;
constexpr reg32 kSleep = 0x4df8e0, kCreateThread = 0x4df7a0, kCreateEvent = 0x4dfb00, kSetEvent = 0x4dfb20;
constexpr reg32 kWaitEvent = 0x4dfb70, kCloseHandle = 0x4dfc00;
// The sound thread's (the game's sound server).
constexpr reg32 kServer = 0x79c150, kServerThread = 0x79c154, kServerEvent = 0x79c168;

}  // namespace

/* 0x4e217c: eacsnd unloaded.  0. */
void iSNDunloaddll(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(3);
    const reg32 module = at(app, kModule);
    if (module != 0 && !call(app, cpu, at(app, kFreeLibrary), {module}))
        return;
    put(app, kModule, 0);
    kept.ret(cpu, 0);
}

/* 0x4e2228: the rate to ax.  0. */
void SNDsetrate(App* app, CPU& cpu)
{
    putHalf(app, kRateSet, reg16(cpu.eax));
    cpu.eax = 0;
    cpu.esp += 4;
}

/* 0x4e1d1c: the library's lock left as often as it was entered (Error's
 * way out of it). */
void leaveAudioLocks(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(2);
    while (sbyte(app, kEntered) > 0)
    {
        putByte(app, kEntered, reg8(byte(app, kEntered) - 1));
        cpu.edx = at(app, kLock);
        if (!call(app, cpu, at(app, kLeaveCriticalSection), {cpu.edx}))
            return;
    }
    kept.ret(cpu, cpu.eax);
}

/* 0x4e225c (iSNDmessageinit, stdcall 24): the driver's message, on the
 * game's message thread: [esp+0x14] 0 starts it for window [esp+8] -- eacsnd
 * checked for the mode, the rate taken from it, the mixer and eacsnd started,
 * the sound thread and the focus handler added -- another ends it.  The
 * result in 0x9ef60c, the message done.  0. */
void iSNDmessageinit(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(3);
    const reg32 window = at(app, kept.esp + 8);
    auto done = [&] {
        putByte(app, kMessageDone, 1);
        const reg32 ecx = cpu.ecx, edx = cpu.edx;
        kept.ret(cpu, 0, 0x18);
        cpu.ecx = ecx;
        cpu.edx = edx;
    };
    if (at(app, kept.esp + 0x14) != 0)
    {
        if (byte(app, kThreadStarted) != 0)
        {
            cpu.edx &= 0xffffff00;
            putByte(app, kThreadStarted, 0);
            if (!callWith(app, cpu, 0x48ec80, 0))
                return;
        }
        if (byte(app, kFocusAdded) != 0)
        {
            cpu.ebx &= 0xffffff00;
            if (!callWith(app, cpu, kFocusHandler, 0))
                return;
            putByte(app, kFocusAdded, reg8(cpu.ebx));
        }
        if (!call(app, cpu, at(app, kDirectEnd)))
            return;
        cpu.ecx = 0;
        put(app, kDriverResult, 0);
        return done();
    }
    if (window == 0)
    {
        cpu.ebx = kDriverFile;
        cpu.edi = 0x549f54;
        cpu.ebp = 0x2d9;
        if (!fail(app, cpu, kept.frame(4), kDriverFile, 0x549f54, 0x2d9, {0x549f64}))
            return;
        cpu.edi = kept.edi;
    }
    const reg32 mode = at(app, kModeAsked);
    cpu.ebx = mode;
    if (!call(app, cpu, at(app, kDirectCheck), {window}))
        return;
    if (i32(cpu.eax) <= 0)
    {
        put(app, kDriverResult, cpu.eax);
        return done();
    }
    const reg32 flags = mode >> 8;
    reg16 rate;
    if (flags & 8)
        rate = 0x5622;
    else if (flags & 4)
        rate = 0x3e80;
    else if (flags & 0x10)
        rate = 0x7d00;
    else if (flags & 0x20)
        rate = 0xac44;
    else if (flags & 2)
        rate = 0x2b11;
    else
    {
        cpu.eax = kDriverFile;
        cpu.edx = 0x549f54;
        cpu.ecx = 0x2f7;
        cpu.ebx = 0xfffffff8;
        if (!fail(app, cpu, kept.frame(3), kDriverFile, 0x549f54, 0x2f7, {0x549f98}))
            return;
        put(app, kDriverResult, 0xfffffff8);
        return done();
    }
    putHalf(app, kRate, rate);
    put(app, kMode, mode);
    if (byte(app, kAtExit) == 0)
    {
        cpu.ecx = (cpu.ecx & 0xffff00ff) | 0x100;
        if (!callWith(app, cpu, 0x4f2a78, 0x4e26b4))
            return;
        putByte(app, kAtExit, reg8(cpu.ecx >> 8));
    }
    if (!callWith(app, cpu, 0x4fff18, at(app, kMode), 0x4ffb64))
        return;
    if (at(app, kDirectVolume) != 0 && !callWith(app, cpu, at(app, kDirectVolume), at(app, 0xa0a25c)))
        return;
    if (!call(app, cpu, at(app, kDirectStart), {mode, window}))
        return;
    put(app, kDriverResult, cpu.eax);
    if (s32(app, kDriverResult) < 0)
        return done();
    if (byte(app, kThreadStarted) == 0)
    {
        if (!callWith(app, cpu, 0x48ec80, 0x4e2234))
            return;
        putByte(app, kThreadStarted, 1);
    }
    if (byte(app, kFocusAdded) == 0)
    {
        cpu.edx = (cpu.edx & 0xffff00ff) | 0x100;
        if (!callWith(app, cpu, kFocusHandler, 0x4e1d48))
            return;
        putByte(app, kFocusAdded, reg8(cpu.edx >> 8));
    }
    put(app, kDriverResult, 0);
    done();
}

/* 0x4e2450 (iSNDinit): the driver started for mode eax: eacsnd loaded, the
 * message sent to the game's message thread and waited for.  The driver's
 * result; -16 without the timer or the window. */
void iSNDinit(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(3);
    put(app, kModeAsked, cpu.eax);
    put(app, kLeaveAll, 0x4e1d1c);
    if (!call(app, cpu, 0x4e1dd4))
        return;
    if (at(app, kSoundRunning) == 0)
    {
        cpu.ebp = kDriverFile;
        cpu.eax = 0x549fbc;
        cpu.edx = 0x349;
        if (!fail(app, cpu, kept.frame(3), kDriverFile, 0x549fbc, 0x349, {0x549fc8}))
            return;
        const reg32 edx = cpu.edx;
        kept.ret(cpu, 0xfffffff0);
        cpu.edx = edx;
        return;
    }
    if (!call(app, cpu, 0x4eba70))
        return;
    if (cpu.eax == 0)
    {
        cpu.ebx = kDriverFile;
        cpu.esi = 0x549fbc;
        cpu.edi = 0x351;
        if (!fail(app, cpu, kept.frame(5), kDriverFile, 0x549fbc, 0x351, {0x54a004}))
            return;
        const reg32 edx = cpu.edx;
        kept.ret(cpu, 0xfffffff0);
        cpu.edx = edx;
        return;
    }
    if (!call(app, cpu, kRegisterHandler, {kMessage, 0x4e225c}))
        return;
    cpu.eax &= 0xffff00ff;
    putByte(app, kMessageDone, 0);
    if (!callWith(app, cpu, kSendMessage, kMessage, 0, 0, 0))
        return;
    // The message thread's answer waited for, as the code waits: a slice
    // given up a time.
    while (byte(app, kMessageDone) == 0)
    {
        safepoint(app, cpu);
        cpu.edx = 0;
        if (!callWith(app, cpu, kSleep, 0))
            return;
    }
    const reg32 edx = cpu.edx;
    kept.ret(cpu, at(app, kDriverResult));
    cpu.edx = edx;
}

/* 0x4e253c (iSNDrestore): the driver ended by the message thread (or, with
 * none, its sound thread and focus handler taken here) and eacsnd unloaded.
 * The driver's result. */
void iSNDrestore(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(3);
    cpu.eax &= 0xffff00ff;
    putByte(app, kMessageDone, 0);
    if (!callWith(app, cpu, kSendMessage, kMessage, 1, 0, 0))
        return;
    if (cpu.eax == 0)
    {
        if (byte(app, kThreadStarted) != 0)
        {
            cpu.edx &= 0xffff00ff;
            putByte(app, kThreadStarted, 0);
            if (!call(app, cpu, 0x48ec80))
                return;
        }
        if (byte(app, kFocusAdded) != 0)
        {
            cpu.ebx &= 0xffff00ff;
            if (!callWith(app, cpu, kFocusHandler, 0))
                return;
            putByte(app, kFocusAdded, reg8(cpu.ebx >> 8));
        }
        cpu.edx = 0;
        put(app, kDriverResult, 0);
    }
    else
        while (byte(app, kMessageDone) == 0)
        {
            safepoint(app, cpu);
            if (!callWith(app, cpu, kSleep, 0))
                return;
        }
    cpu.ecx = 0;
    if (!call(app, cpu, 0x4e217c))
        return;
    put(app, kLeaveAll, 0);
    kept.ret(cpu, at(app, kDriverResult));
}

/* 0x4e2754 (iSNDverifymode): mode eax (-1 any) against eacsnd's caps: its
 * format (8 before 2, 4, 1), its rate (8, 0x10, 4, 0x20, 2, 1, in the second
 * byte) and stereo (0x20000) as both have them.  0 with an error for no format
 * or no rate.  edx left as the rates both have. */
void iSNDverifymode(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 mode = cpu.eax;
    cpu.esp = kept.frame(4);
    if (!callWith(app, cpu, 0x4e21b0, kept.edx))
        return;
    const reg32 caps = cpu.eax;
    const reg32 both = (mode == 0xffffffff ? caps : mode) & caps;
    const reg32 formats = both & 0xff, rates = both & 0xff00;
    const reg32 stereo = mode == 0xffffffff ? 0 : both & 0xff0000;
    cpu.edx = rates;
    if (formats == 0)
    {
        if (!fail(app, cpu, kept.frame(5), 0x54a098, 0x54a0a4, 0xfc, {0x54a0b4}))
            return;
        const reg32 edx = cpu.edx;
        kept.ret(cpu, 0);
        cpu.edx = edx;
        return;
    }
    if (rates == 0)
    {
        cpu.edx = 0x54a098;
        if (!fail(app, cpu, kept.frame(4), 0x54a098, 0x54a0a4, 0x104, {0x54a100}))
            return;
        const reg32 edx = cpu.edx;
        kept.ret(cpu, 0);
        cpu.edx = edx;
        return;
    }
    reg32 result = formats & 8 ? 8 : formats & 2 ? 2 : formats & 4 ? 4 : 1;
    const reg32 r = rates >> 8;
    result |= (r & 8 ? 8 : r & 0x10 ? 0x10 : r & 4 ? 4 : r & 0x20 ? 0x20 : r & 2 ? 2 : 1) << 8;
    if (stereo & 0x20000)
        result |= 0x20000;
    kept.ret(cpu, result);
    cpu.edx = rates;
}

/* 0x4e2630 (SNDinit): the library started for mode eax: its voices (16 when
 * none were asked for), its tick, its lock, the master volume; the mode
 * verified, the driver started (undone when it failed).  0, or the
 * driver's error. */
void SNDinit(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 mode = cpu.eax;
    cpu.esp = kept.frame(3);
    if (byte(app, kInited) != 0)
    {
        kept.ret(cpu, 0);
        return;
    }
    if (byte(app, kVoicesUsed) == 0)
        putByte(app, kVoicesUsed, 0x10);
    if (at(app, 0xa09b08) == 0)
        put(app, 0xa09b08, 0x500c80);
    if (!call(app, cpu, 0x4eb2e0))
        return;
    put(app, kLock, cpu.eax);
    cpu.edi = 0;
    put(app, kTicks, 0);
    put(app, kTicks + 4, 0);
    putByte(app, kMasterVolume, 0x7f);
    if (!callWith(app, cpu, 0x4e2754, mode, kept.edx))
        return;
    cpu.edx = kept.edx;
    if (!call(app, cpu, 0x4e2450))
        return;
    const reg32 result = cpu.eax;
    cpu.ecx = result;
    if (i32(result) < 0)
    {
        if (!call(app, cpu, 0x4e253c))
            return;
        const reg32 edx = cpu.edx;
        kept.ret(cpu, result);
        cpu.edx = edx;
        return;
    }
    putByte(app, kInited, 1);
    const reg32 edx = cpu.edx;
    kept.ret(cpu, 0);
    cpu.edx = edx;
}

/* 0x4e26b4 (SNDrestore): the library ended: what registered a restore
 * restored (the game's, Pathfinder, the streamers, the effects), every sound
 * stopped, the effects' end told, the driver ended, the lock gone.  The
 * driver's result; -10 before SNDinit. */
void SNDrestore(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    if (byte(app, kInited) == 0)
    {
        kept.ret(cpu, 0xfffffff6);
        return;
    }
    for (const reg32 restore : {0xa09b34u, 0xa09b38u, 0xa09b2cu, 0xa09b30u, 0xa09b28u})
        if (at(app, restore) != 0 && !call(app, cpu, at(app, restore)))
            return;
    if (!call(app, cpu, 0x4e9010))
        return;
    if (at(app, 0xa09b24) != 0 && !callWith(app, cpu, at(app, 0xa09b24), 0xffffffff))
        return;
    const reg32 ebx = cpu.ebx, edx = cpu.edx;
    cpu.esp = kept.frame(2);
    if (!call(app, cpu, 0x4e253c))
        return;
    const reg32 result = cpu.eax;
    putByte(app, kInited, 0);
    if (!callWith(app, cpu, 0x4eb360, at(app, kLock)))
        return;
    kept.ret(cpu, result);
    cpu.ebx = ebx;
    cpu.edx = edx;
    cpu.ecx = cpu.ecx;
}

/* 0x48ec40: the sound thread: its event made, the server (0x79c150) run each
 * time the event is set, until there is none. */
void soundThread(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(2);
    if (!call(app, cpu, kCreateEvent))
        return;
    put(app, kServerEvent, cpu.eax);
    for (;;)
    {
        safepoint(app, cpu);
        cpu.edx = at(app, kServer);
        if (cpu.edx == 0)
            break;
        if (!call(app, cpu, cpu.edx) || !callWith(app, cpu, kWaitEvent, at(app, kServerEvent)))
            return;
    }
    if (!callWith(app, cpu, kCloseHandle, at(app, kServerEvent)))
        return;
    put(app, kServerEvent, cpu.edx);
    kept.ret(cpu, cpu.eax);
}

/* 0x48ec80: the sound thread's server to eax: a first one starts the thread
 * (waited for until its event is there), none ends it (its event set and the
 * thread waited for until it is gone). */
void setSoundServer(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(5);
    put(app, kServer, cpu.eax);
    if (cpu.eax != 0 && at(app, kServerEvent) == 0)
    {
        cpu.edx = 0;
        if (!callWith(app, cpu, kCreateThread, 0x48ec40, 0, 3, 0xffffffff, {kServerThread}))
            return;
        while (at(app, kServerEvent) == 0)
        {
            safepoint(app, cpu);
            if (!callWith(app, cpu, kSleep, 0))
                return;
        }
    }
    else if (at(app, kServer) == 0 && at(app, kServerEvent) != 0)
    {
        cpu.esi = at(app, kServerEvent);
        if (!callWith(app, cpu, kSetEvent, kServerThread, cpu.esi))
            return;
        while (at(app, kServerEvent) != 0)
        {
            safepoint(app, cpu);
            if (!callWith(app, cpu, kSleep, 0))
                return;
        }
    }
    kept.ret(cpu, cpu.eax);
}

}  // namespace snd
}  // namespace nfs3hp
