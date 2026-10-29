// game_checks.cpp's parts for EA's threads, events, timers and locks (native_ea_threads.cpp), included in each
// table with the macro naming the part.
#if defined(EA_WINDOWS)
// {from, to}, -- what the functions write, compared
// None of their own: the threads' globals (0x9ef5b0 to 0x9ef5bc), the locks'
// (0x564a60, 0x564a64), the game's lock (0x564480), DirectDraw's flags
// (0x9f3d0c, 0x567180) are on pages compared already, and the cases' records,
// matrices and pages are in the harness's (0x61d000 to 0x620000).  The jump
// table of setThreadPriority (0x4dfa10) generate.py puts in the game's data.
#elif defined(EA_EFFECTS)
// kSomething,  -- a stand-in's effect of this file's
kThreadsWait,          // WaitForMultipleObjectsEx: one of the handles' index, the time up, failed, abandoned
kThreadsCreated,       // CreateThread: a HANDLE and the thread's id, or 0
kThreadsPriority,      // GetThreadPriority: one of Windows' seven, another, or THREAD_PRIORITY_ERROR_RETURN
kThreadsDuplicate,     // DuplicateHandle: the handle where it is asked for, TRUE; or FALSE
kThreadsPages,         // 0x501110: the pages at 0x61d000 (the size rounded up to them now and then), or 0
kThreadsSineCosine,    // 0x4ea970: an angle's sine to [edx], its cosine to [ebx]
kThreadsNormal,        // 0x4e01c0: the vector at eax normalized into [edx]
kThreadsMemoryStatus,  // GlobalMemoryStatus: the MEMORYSTATUS past its length made up
kThreadsClock,         // timeGetTime: near the time the timer's next tick is due (0x79c178), mostly, else any
kThreadsMmResult,      // timeBeginPeriod, timeGetDevCaps: 0 (TIMERR_NOERROR) mostly, else 97
kThreadsMessageSent,   // the game's message to its message thread (0x4cc7c0): answered now and then (the driver's flag 0x9ef607 set), 0 or not
#elif defined(EA_EFFECT_CASES)
// case kSomething: ... break;
case kThreadsWait:
{
    // (how many, the handles, all, the time, alertable): which was set --
    // one of them mostly -- or WAIT_TIMEOUT, WAIT_FAILED, one abandoned.
    const x86::reg32 count = words[0];
    const x86::reg32 index = count - 1 < 64 ? (r >> 8) % count : (r >> 8) % 4;
    result = r % 8 < 5 ? index : r % 8 == 5 ? 0x102 : r % 8 == 6 ? 0xffffffff : 0x80 + index;
    break;
}
case kThreadsCreated:
    // (security, stack, start, its parameter, flags, &the id)
    result = r % 5 != 0 ? 0x7800 + (r >> 8) % 0x100 * 4 : 0;
    if (result != 0 && words[5] < kMemory - 4)
        word(words[5]) = random(id + 1);
    break;
case kThreadsPriority:
{
    static const x86::reg32 priorities[] = {0xfffffff1, 0xfffffffe, 0xffffffff, 0, 1, 2, 15,
                                            0x7fffffff, 3, 0xfffffffd, 14, 0xfffffff2};
    result = r % 13 < 12 ? priorities[r % 13] : r >> 8;
    break;
}
case kThreadsDuplicate:
    // (its process, the handle, the process it is for, &the new one, access, inherited, options)
    result = r % 5 != 0 ? 1 : 0;
    if (result != 0 && words[3] < kMemory - 4)
        word(words[3]) = 0x7c00 + (r >> 8) % 0x100 * 4;
    break;
case kThreadsPages:
    // eax the size's address: rounded up to the 4K pages now and then, as
    // the pages are got -- only the sizes the pages here hold.
    result = r % 6 == 0 ? 0 : 0x61d000;
    if ((r >> 4) % 2 != 0 && word(words[0]) <= 0x1000)
        word(words[0]) = (word(words[0]) + 0xfff) & ~0xfffu;
    break;
case kThreadsSineCosine:
case kThreadsNormal:
{
    // As the x87 has them: of an ordinary angle or axis, its sine and cosine
    // or the axis made a unit long; of a NaN, that NaN quieted, for every
    // part; of an infinity, or of an axis none long, the default NaN.  (One
    // NaN's bits only: with two, the host's double arithmetic picks either,
    // as its compiler orders the operands.)
    const x86::reg32 count = s.effect == kThreadsNormal ? 3 : 2;
    float in[3] = {};
    x86::reg32 special = 0;
    for (x86::reg32 i = 0; i < (count == 3 ? 3u : 1u); ++i)
    {
        const x86::reg32 bits = words[count == 3 ? 2 + i : 3];
        std::memcpy(&in[i], &bits, 4);
        if ((bits & 0x7f800000) == 0x7f800000 && special == 0)
            special = bits & 0x7fffff ? bits | 0x400000 : 0xffc00000;
    }
    float out[3];
    if (count == 2)
    {
        out[0] = std::sin(in[0]);
        out[1] = std::cos(in[0]);
    }
    else
    {
        const double length = std::sqrt(double(in[0]) * in[0] + double(in[1]) * in[1] + double(in[2]) * in[2]);
        if (length == 0 || !std::isfinite(length))
            special = special != 0 ? special : 0xffc00000;
        for (x86::reg32 i = 0; i < 3; ++i)
            out[i] = special != 0 ? 0 : float(in[i] / length);
    }
    for (x86::reg32 i = 0; i < count; ++i)
    {
        x86::reg32 bits = special;
        if (special == 0)
            std::memcpy(&bits, &out[i], 4);
        const x86::reg32 to = s.effect == kThreadsNormal ? words[1] + 4 * i : words[1 + i];
        if (to < kMemory - 4)
            word(to) = bits;
    }
    break;
}
case kThreadsClock:
    // Within a second and a half either side of the next tick's time, so that the timer's callback
    // takes each way (late by a millisecond or more, a little late, very late); now and then any time.
    result = r % 8 != 0 ? word(0x79c178) + (r >> 8) % 3001 - 1500 : random(id + 1);
    break;
case kThreadsMessageSent:
    // The message thread's answer: the driver's message done (0x9ef607) mostly, and the call's result 0
    // (no message thread) or not.
    if (r % 4 != 0)
        getMemory<x86::reg8>(0x9ef607) = 1;
    result = (r >> 4) % 4 == 0 ? 0 : r | 1;
    break;
case kThreadsMmResult:
    result = r % 6 != 0 ? 0 : 97;
    break;
case kThreadsMemoryStatus:
    for (x86::reg32 i = 1; i < 8 && words[0] < kMemory - 0x20; ++i)
        word(words[0] + 4 * i) = random(id + i);
    break;
#elif defined(EA_GAME_FUNCTIONS)
// {address, "name", convention, registers, words, clobbers, through, deref, effect},
// The file system's pages got (the files' native, eax the size's address, it
// logged); an angle's sine and cosine (eax the angle's address, it logged);
// a vector normalized (eax it, its three floats logged; edx where to).
{0x501110, "pages got", kWatcom, 1, 0, kEax, 0, 1, kThreadsPages},
{0x4ea970, "a sine and cosine", kWatcom, 3, 0, 0, 0, 1, kThreadsSineCosine},
{0x4e01c0, "a vector normalized", kWatcom, 2, 0, 0, 0, 3, kThreadsNormal},
#elif defined(EA_POINTERS)
// {slot, "name", convention, registers, words, clobbers, through, deref, effect},
// The handles WaitForMultipleObjectsEx is handed: the first logged; the
// MEMORYSTATUS GlobalMemoryStatus fills: its length logged.
{0x534630, "WaitForMultipleObjectsEx", kStdcall, 0, 5, kScratch, 5, 1, kThreadsWait},
{0x534504, "GetCurrentProcess", kStdcall, 0, 0, kScratch, -1, 0, kNothing},
{0x534510, "GetCurrentThread", kStdcall, 0, 0, kScratch, -1, 0, kNothing},
{0x5344b4, "DuplicateHandle", kStdcall, 0, 7, kScratch, -1, 0, kThreadsDuplicate},
{0x5344a4, "CreateThread", kStdcall, 0, 6, kScratch, -1, 0, kThreadsCreated},
{0x5345bc, "ResumeThread", kStdcall, 0, 1, kScratch, -1, 0, kNothing},
{0x534608, "TerminateThread", kStdcall, 0, 2, kScratch, -1, 0, kSucceed},
{0x534564, "GetThreadPriority", kStdcall, 0, 1, kScratch, -1, 0, kThreadsPriority},
{0x5345fc, "SetThreadPriority", kStdcall, 0, 2, kScratch, -1, 0, kSucceed},
{0x5344c4, "ExitThread", kStdcall, 0, 1, kScratch, -1, 0, kNothing},
{0x5345e8, "SetEvent", kStdcall, 0, 1, kScratch, -1, 0, kSucceed},
{0x5345b8, "ResetEvent", kStdcall, 0, 1, kScratch, -1, 0, kSucceed},
{0x5345a4, "PulseEvent", kStdcall, 0, 1, kScratch, -1, 0, kSucceed},
{0x5345f4, "SetLastError", kStdcall, 0, 1, kScratch, -1, 0, kNothing},
{0x534584, "InitializeCriticalSection", kStdcall, 0, 1, kScratch, -1, 0, kNothing},
{0x5344ac, "DeleteCriticalSection", kStdcall, 0, 1, kScratch, -1, 0, kNothing},
{0x534580, "GlobalMemoryStatus", kStdcall, 0, 1, kScratch, 4, 1, kThreadsMemoryStatus},
// The function a thread runs, which threadStart calls (by the stand-in's own address).
{0xfff0a0, "a thread's function", kWatcom, 0, 0, kEax, -1, 0, kNothing},
#elif defined(EA_PROMISES)
// {"ea::name", watcom, result, arguments, fpu, heap, liveOnly},
{"ea::waitForObjects", true, true, 0},
{"ea::threadStart", true, true, 0},
{"ea::threadsInit", true, true, 0},
{"ea::createThread", true, true, 0},
{"ea::removeThread", true, true, 0},
{"ea::sleepMs", true, true, 0},
{"ea::sleepTicks", true, true, 0},
{"ea::isThread", true, true, 0},
{"ea::threadPriority", true, true, 0},
{"ea::setThreadPriority", true, true, 0},
{"ea::exitThread", true, true, 0},
{"ea::createEvent", true, true, 0},
{"ea::postEvent", true, true, 0},
{"ea::signalEvent", true, true, 0},
{"ea::pollEvent", true, true, 0},
{"ea::waitEvent", true, true, 0},
{"ea::waitEventTicks", true, true, 0},
{"ea::waitForAny", true, true, 0},
{"ea::closeEvent", true, true, 0},
{"ea::createManualEvent", true, true, 0},
{"ea::setEvent", true, true, 0},
{"ea::resetEvent", true, true, 0},
{"ea::pulseEvent", true, true, 0},
{"ea::waitManualEvent", true, true, 0},
{"ea::setAndCloseEvent", true, true, 0},
{"ea::lastErrorText", true, true, 0},
{"ea::setLastError", true, true, 0},
{"ea::lastError", true, true, 0},
{"ea::doNothing", true, true, 0},
// The rotations' x87 stack is balanced: its depth compared, what they store.
{"ea::xRotation", true, true, 0},
{"ea::yRotation", true, true, 0},
{"ea::zRotation", true, true, 0},
{"ea::axisRotation", true, true, 0},
// Its result on the x87's stack: that compared too.
{"ea::randomFraction", true, true, 0, true, kNoHeap, true},
{"ea::growLocks", true, true, 0},
{"ea::makeLock", true, true, 0},
{"ea::enterLock", true, true, 0},
{"ea::leaveLock", true, true, 0},
{"ea::freeLock", true, true, 0},
{"ea::surfaceLocked", true, true, 0},
{"ea::physicalMemory", true, true, 0},
#elif defined(EA_ARGUMENTS)
/* Where the threads' cases keep their own: the pages a pool of locks is got
 * in; a thread's record; handles; a matrix, an axis; lock records; a
 * buffer for text.  And the function a thread runs (its stand-in's slot). */
constexpr x86::reg32 kThreadsPagesGot = 0x61d000, kThreadsRecord = 0x61e000, kThreadsHandles = 0x61e100;
constexpr x86::reg32 kThreadsMatrix = 0x61e200, kThreadsAxis = 0x61e300, kThreadsLocks = 0x61e400;
constexpr x86::reg32 kThreadsText = 0x61f000, kThreadsFunction = 0xfff0a0;

/* What the stand-in at `slot` gives back in eax as call `call` of the case
 * (from 0), handed `eax` -- as CheckApp::standIn makes it up for kNothing. */
x86::reg32 threadsStandInResult(x86::reg32 slot, unsigned call, x86::reg32 eax)
{
    const x86::reg32 id = standInFor(slot);
    const auto random = [&](x86::reg32 i) { return x86::reg32(mix(g_seed ^ (std::uint64_t(call + 1) << 32) ^ i)); };
    return random(id ^ 0xabcd) % 4 != 0 ? random(id) : eax;
}

/* A handle: an event's, a thread's -- or none, or any. */
x86::reg32 aThreadsHandle()
{
    return chance(80) ? 0x7400 + below(0x100) * 4 : chance(50) ? 0 : random32();
}

/* A thread as the functions are handed one: the main thread (0), this one
 * (-1), or the record at 0x61e000. */
x86::reg32 aThreadsThread()
{
    return chance(20) ? 0 : chance(25) ? 0xffffffff : kThreadsRecord;
}

/* EA's priority: -3 to 3 mostly, just past them, or any. */
x86::reg32 aThreadsPriority()
{
    return chance(85) ? below(7) - 3 : chance(50) ? (chance(50) ? 4 : 0xfffffffc) : random32();
}

/* A float's bits: an angle mostly, 0 of either sign, any (but no infinity
 * nor NaN where `ordinary`). */
x86::reg32 aThreadsFloat(bool ordinary = false)
{
    if (chance(10))
        return chance(50) ? 0 : 0x80000000;
    if (chance(15) && !ordinary)
        return anyFloatBits(random32() | std::uint64_t(random32()) << 32);
    const float f = float(x86::sreg32(below(20001)) - 10000) / 1000.0f;
    x86::reg32 bits;
    std::memcpy(&bits, &f, 4);
    return bits;
}

/* The threads' world: set up or not, the main thread's id and handle; the
 * game's ticks a second; the error code; DirectDraw's flags; the free locks
 * -- a chain of records, or none -- and how many a pool grows by; the
 * harness's records, handles and buffers made up. */
void makeThreadsWorld(CheckApp& g)
{
    for (x86::reg32 at = kThreadsPagesGot; at < 0x620000; at += 4)
        g.word(at) = random32();
    g.word(0x9ef5b8) = chance(75) ? 1 : chance(80) ? 0 : random32();
    g.word(0x9ef5b4) = random32();
    g.word(0x9ef5b0) = aThreadsHandle();
    g.word(0x564480) = random32();
    static const x86::reg32 rates[] = {60, 100, 1000, 30, 1, 0xffffffff};
    g.word(0x5643d8) = chance(40) ? 0 : chance(80) ? rates[below(6)] : random32();
    g.word(0x9ef5bc) = random32();
    g.word(0x9f3d0c) = chance(85) ? 0 : random32();
    g.word(0x567180) = chance(85) ? 0 : random32();
    // How many locks a pool grows by: 32 as the game starts, a few, none,
    // up to as many as the pages hold -- or as many as wrap round to a few.
    g.word(0x564a60) = chance(30) ? 0x20 : chance(80) ? below(0x81) : 0x8000000 * (1 + below(31)) + below(4);
    // The free locks: none, or a chain of a few records.
    const x86::reg32 free = chance(40) ? 0 : 1 + below(8);
    for (x86::reg32 i = 0; i < 8; ++i)
    {
        const x86::reg32 record = kThreadsLocks + 0x20 * i;
        g.word(record + 0x18) = i + 1 < free ? record + 0x20 : chance(80) ? 0 : random32();
        g.word(record + 0x1c) = chance(80) ? 0x46524545 : random32();
    }
    g.word(0x564a64) = free != 0 ? kThreadsLocks : 0;
    // The thread's record: a handle, a stack size, a priority, 0, an id.
    g.word(kThreadsRecord) = aThreadsHandle();
    g.word(kThreadsRecord + 8) = aThreadsPriority();
    g.word(kThreadsRecord + 0xc) = 0;
    for (x86::reg32 i = 0; i < 16; ++i)
        g.word(kThreadsHandles + 4 * i) = aThreadsHandle();
    for (x86::reg32 i = 0; i < 3; ++i)
        g.word(kThreadsAxis + 4 * i) = aThreadsFloat();
}

bool makeEaThreadsArguments(CheckApp& g, const std::string& name, x86::CPU& cpu, x86::reg32* stack)
{
    static const char* const names[] = {
        "waitForObjects", "threadStart", "threadsInit", "createThread", "removeThread", "sleepMs",
        "sleepTicks", "isThread", "threadPriority", "setThreadPriority", "exitThread", "createEvent",
        "postEvent", "signalEvent", "pollEvent", "waitEvent", "waitEventTicks", "waitForAny", "closeEvent",
        "createManualEvent", "setEvent", "resetEvent", "pulseEvent", "waitManualEvent", "setAndCloseEvent",
        "lastErrorText", "setLastError", "lastError", "doNothing", "xRotation", "yRotation", "zRotation",
        "axisRotation", "randomFraction", "growLocks", "makeLock", "enterLock", "leaveLock", "freeLock",
        "surfaceLocked", "physicalMemory"};
    if (std::find_if(std::begin(names), std::end(names), [&](const char* n) { return name == n; })
        == std::end(names))
        return false;
    makeThreadsWorld(g);
    // How many handles: one to 8 mostly, none, up to 16, or any.
    const auto aCount = [] { return chance(80) ? 1 + below(8) : chance(50) ? below(17) : random32(); };
    // A time: none, for ever, some ms or ticks, or any.
    const auto aTime = [] { return chance(25) ? 0 : chance(25) ? 0xffffffff : chance(70) ? below(2000) : random32(); };
    if (name == "waitForObjects" || name == "waitForAny")
    {
        cpu.eax = aCount();
        cpu.edx = kThreadsHandles;
        cpu.ebx = aTime();
    }
    else if (name == "threadStart")
        stack[0] = chance(90) ? standInFor(kThreadsFunction) : 0;
    else if (name == "createThread")
    {
        cpu.eax = chance(80) ? standInFor(kThreadsFunction) : random32();
        cpu.edx = chance(70) ? 0x1000 * below(0x41) : random32();
        cpu.ebx = aThreadsPriority();
        stack[0] = kThreadsRecord + 4 * below(4);
    }
    else if (name == "removeThread")
        cpu.eax = chance(15) ? 0 : chance(20) ? 0xffffffff : kThreadsRecord;
    else if (name == "sleepMs" || name == "sleepTicks" || name == "setLastError")
        cpu.eax = aTime();
    else if (name == "isThread")
    {
        cpu.eax = aThreadsThread();
        // The id GetCurrentThreadId gives (its case's first call) the main
        // thread's or the record's, often.
        const x86::reg32 current = threadsStandInResult(0x53450c, 0, cpu.eax);
        if (chance(60))
            g.word(0x9ef5b4) = current;
        g.word(kThreadsRecord + 0x10) = chance(60) ? current : random32();
    }
    else if (name == "threadPriority" || name == "setThreadPriority")
    {
        cpu.eax = aThreadsThread();
        cpu.edx = aThreadsPriority();
    }
    else if (name == "postEvent")
    {
        cpu.eax = random32();
        cpu.edx = aThreadsHandle();
    }
    else if (name == "signalEvent" || name == "pollEvent" || name == "waitEvent" || name == "closeEvent"
             || name == "setEvent" || name == "resetEvent" || name == "pulseEvent" || name == "waitManualEvent"
             || name == "setAndCloseEvent")
        cpu.eax = aThreadsHandle();
    else if (name == "waitEventTicks")
    {
        cpu.eax = aThreadsHandle();
        cpu.edx = aTime();
    }
    else if (name == "lastErrorText")
        cpu.eax = chance(30) ? 0 : kThreadsText;
    else if (name == "xRotation" || name == "yRotation" || name == "zRotation")
    {
        cpu.eax = kThreadsMatrix + 4 * below(4);
        stack[0] = aThreadsFloat();
    }
    else if (name == "axisRotation")
    {
        // An infinity or a NaN in the angle or in the axis, not both: two
        // NaNs' bits would come out of the double arithmetic either way.
        cpu.eax = kThreadsAxis;
        stack[0] = aThreadsFloat();
        const bool special = (stack[0] & 0x7f800000) == 0x7f800000;
        for (x86::reg32 i = 0; i < 3; ++i)
            g.word(kThreadsAxis + 4 * i) = aThreadsFloat(special);
        stack[1] = kThreadsMatrix + 4 * below(4);
    }
    else if (name == "enterLock" || name == "leaveLock")
        cpu.eax = kThreadsLocks + 0x20 * below(8);
    else if (name == "freeLock")
        cpu.eax = chance(15) ? 0 : kThreadsLocks + 0x20 * below(8);
    return true;
}
#endif
