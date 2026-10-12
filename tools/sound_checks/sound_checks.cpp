/* src/nfs3hp/native_isnd.cpp against eacsnd's generated code, on the desktop,
 * without the game.
 *
 * eacsnd's generated code is made afresh from nfs3hp/eacsnd.dll by the port's
 * own generator, without the hooks of the tree's copy (generate.py), and built
 * with the port's headers.  Two guest memories hold the same state: eacsnd's segments as
 * they load, its globals and the stack made up afresh for every case.  The
 * generated export runs on one, the native on the other, and then come
 * compared: eax, esp, ebx, esi, edi and ebp; every byte of memory, the stack
 * below the esp they return with too -- the natives push what eacsnd pushes,
 * and pos3d's arithmetic lands nowhere else; and every call they made out --
 * the game's functions iSNDdirectsetfunctions keeps, a COM object's Release --
 * in order, with its stack and arguments.  Every so often all of both
 * memories are compared, for a write anywhere else.
 *
 * The functions called out are stand-ins (stub*).  Each case scripts what they
 * do, the same for both runs: the floats the position function hands back,
 * what Release returns, now and then one that writes into the record being
 * cleared, changes esi, leaves esp off or stops the game -- whatever the code
 * after a call reads again, it has to read again too.
 *
 * Most cases are eacsnd's state on the port -- no DirectSound, no 3D buffers.
 * In the others a native has to step aside and leave everything as it was.
 *
 * See run.sh. */
#include "eacsnd.h"
#include "isnd.h"
#include <lib/memmap.h>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <random>
#include <string>
#include <vector>
#include <sys/mman.h>

namespace isnd = nfs3hp::isnd;

namespace x86
{
void assertLog(const char* file, int line, const char* expr)
{
    std::printf("assert %s:%d %s\n", file, line, expr);
}
}

/* src/lib/cpu.cpp's rdtsc, which nothing here runs, is all it wants of SDL. */
extern "C" Uint64 SDL_GetPerformanceCounter(void) { return 0; }
extern "C" Uint64 SDL_GetPerformanceFrequency(void) { return 1; }

namespace nfs3hp
{
bool soundVersion(win32::WinApplication* app, x86::CPU& cpu);
bool soundSetFunctions(win32::WinApplication* app, x86::CPU& cpu);
bool soundRecordStart(win32::WinApplication* app, x86::CPU& cpu);
bool soundRecordPacket(win32::WinApplication* app, x86::CPU& cpu);
bool soundRecordStop(win32::WinApplication* app, x86::CPU& cpu);
bool soundVolume(win32::WinApplication* app, x86::CPU& cpu);
bool soundPosition(win32::WinApplication* app, x86::CPU& cpu);
bool soundRate(win32::WinApplication* app, x86::CPU& cpu);
bool soundCreateBuffer(win32::WinApplication* app, x86::CPU& cpu);
bool soundRemoveBuffer(win32::WinApplication* app, x86::CPU& cpu);
bool soundPlayBuffer(win32::WinApplication* app, x86::CPU& cpu);
bool soundStopBuffer(win32::WinApplication* app, x86::CPU& cpu);
}

namespace
{

constexpr x86::reg32 kMemory = 0x1000000;

/* Where things are, in both memories. */
constexpr x86::reg32 kAuto = 0xa32800, kAutoBytes = 29696;
constexpr x86::reg32 kImports = 0xa3a800, kImportsBytes = 1536;
constexpr x86::reg32 kData = 0xa3b800, kDataBytes = 6656;
constexpr x86::reg32 kExportTable = 0xa3e800, kExportTableBytes = 1024;
constexpr x86::reg32 kGlobals = 0xa3c09c, kGlobalsEnd = 0xa3cad0;   // eacsnd's globals, SYMBOLS.md
constexpr x86::reg32 kWindow = 0xa30000, kWindowEnd = 0xa60000;     // eacsnd, and every record an index reaches
constexpr x86::reg32 kScratch = 0x800000, kScratchEnd = 0x804000;   // what the caller's esi points at, COM objects
constexpr x86::reg32 kObjects = 0x802000;                           // 16 COM objects of 16 bytes
constexpr x86::reg32 kVtable = 0x803000;
constexpr x86::reg32 kStackLow = 0xef0000, kStackHigh = 0xf00000;

/* The stand-ins' addresses: anything dynamic_call does not know. */
constexpr x86::reg32 kStubPosition = 0x00e10000;
constexpr x86::reg32 kStubStop = 0x00e10010;
constexpr x86::reg32 kStubRelease = 0x00e10020;
constexpr x86::reg32 kStubOther = 0x00e10030;  // the five functions nothing here calls

struct Call
{
    x86::reg32 address;
    x86::reg32 esp;
    x86::reg32 arguments[3];
    bool operator==(const Call& o) const
    {
        return address == o.address && esp == o.esp && std::memcmp(arguments, o.arguments, sizeof arguments) == 0;
    }
};

/* What the stand-ins do in a case, the same for both runs. */
struct Script
{
    float position[3][3];       // per call: the floats handed back
    x86::reg32 result[4];       // per call: eax
    int scribble = -1;          // the call that writes into [esi + 8]
    x86::reg32 scribbleValue = 0;
    int moveEsi = -1;           // the call that leaves esi changed
    x86::reg32 newEsi = 0;
    int skewEsp = -1;           // the call that leaves esp 4 off
    int stop = -1;              // the call that stops the game
};

Script g_script;
double g_scale = 0;  // the position scale as eacsnd's data has it

}

namespace win32
{

/* A guest memory of its own, and its own log of calls out. */
class CheckApp : public WinApplication
{
public:
    CheckApp() : WinApplication("sound_checks", 0, {}) {}
    std::vector<Call> calls;
};

WinApplication::WinApplication(const char*, x86::reg32, const std::vector<Section>&)
{
    void* memory = mmap(nullptr, kMemory, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (memory == MAP_FAILED)
        std::abort();
    m_memory = static_cast<x86::reg8*>(memory);
}

WinApplication::~WinApplication() {}

int WinApplication::s_traceApi = 0;
bool WinApplication::readTraceApi() { return false; }
void WinApplication::traceCall(const Method&, x86::reg32) {}
void WinApplication::yieldContext(const x86::CPU&) {}

void WinApplication::dynamicCallElsewhere(x86::reg32 address, x86::CPU& cpu)
{
    CheckApp* app = static_cast<CheckApp*>(this);
    const x86::reg32 esp = cpu.esp;
    auto word = [&](x86::reg32 at) { return getMemory<x86::reg32>(at); };
    Call call{address, esp, {word(esp + 4), word(esp + 8), word(esp + 12)}};
    const int index = int(app->calls.size());
    app->calls.push_back(call);
    if (index == g_script.stop)
    {
        cpu.terminate = true;
        return;
    }
    x86::reg32 argumentBytes = 0;
    switch (address)
    {
    case kStubPosition:
        argumentBytes = 12;
        if (index < 3)
        {
            const x86::reg32 out = call.arguments[2];
            for (int i = 0; i < 3; ++i)
                getMemory<float>(out + 4 * i) = g_script.position[index][i];
        }
        break;
    case kStubStop:
    case kStubRelease:
        argumentBytes = 4;
        break;
    default:
        std::printf("a call to %08x, no stand-in there\n", unsigned(address));
        std::exit(2);
    }
    if (index == g_script.scribble)
        getMemory<x86::reg32>(cpu.esi + 8) = g_script.scribbleValue;
    if (index == g_script.moveEsi)
        cpu.esi = g_script.newEsi;
    cpu.eax = g_script.result[index & 3];
    cpu.ecx = 0x11111111 * x86::reg32(index + 1);
    cpu.edx = 0x22222222;
    cpu.esp = esp + 4 + argumentBytes + (index == g_script.skewEsp ? 4 : 0);
}

void MemMap::usedRanges(std::vector<std::pair<x86::reg32, x86::reg32>>& ranges)
{
    ranges.assign(1, {0, kMemory});
}

}

namespace
{

using Native = bool (*)(win32::WinApplication*, x86::CPU&);
using Generated = void (*)(win32::WinApplication*, x86::CPU&);

/* When a native is to step aside: eacsnd's ways with DirectSound made
 * (kDirectSoundMade) or 3D buffers asked for (kIs3d), which are not native. */
enum StepAside
{
    kNever,
    kWithDirectSound,       // kDirectSoundMade
    kWith3dAndDirectSound,  // kIs3d and kDirectSoundMade
    kWith3d,                // kIs3d
};

struct Export
{
    const char* name;
    Generated generated;
    Native native;
    StepAside stepAside;
};

const Export kExports[] = {
    {"iSNDdllversion", &eacsnd::sub_a32bc4, &nfs3hp::soundVersion, kNever},
    {"iSNDdirectsetfunctions", &eacsnd::sub_a32bd8, &nfs3hp::soundSetFunctions, kNever},
    {"iSNDdirectrecordstart", &eacsnd::sub_a338fc, &nfs3hp::soundRecordStart, kNever},
    {"iSNDdirectrecordpacket", &eacsnd::sub_a33904, &nfs3hp::soundRecordPacket, kNever},
    {"iSNDdirectrecordstop", &eacsnd::sub_a3390c, &nfs3hp::soundRecordStop, kNever},
    {"iSNDdirectvol", &eacsnd::sub_a33e18, &nfs3hp::soundVolume, kWithDirectSound},
    {"iSNDdirectpos3d", &eacsnd::sub_a33e68, &nfs3hp::soundPosition, kWithDirectSound},
    {"iSNDdirectrate", &eacsnd::sub_a33f0c, &nfs3hp::soundRate, kWithDirectSound},
    {"iSNDdirectcreate3dbuf", &eacsnd::sub_a33f4c, &nfs3hp::soundCreateBuffer, kWith3dAndDirectSound},
    {"iSNDdirectremovebuf", &eacsnd::sub_a33fc0, &nfs3hp::soundRemoveBuffer, kWith3dAndDirectSound},
    {"iSNDdirectplay3d", &eacsnd::sub_a34014, &nfs3hp::soundPlayBuffer, kWith3d},
    {"iSNDdirectstopbuf", &eacsnd::sub_a341b0, &nfs3hp::soundStopBuffer, kWithDirectSound},
};

std::mt19937 g_random(1998);

x86::reg32 random32()
{
    return x86::reg32(g_random());
}

bool chance(int percent)
{
    return int(g_random() % 100) < percent;
}

/* A float of every kind: ordinary, tiny, huge, denormal, zero, infinite, NaN. */
float anyFloat()
{
    switch (g_random() % 8)
    {
    case 0: { float f; x86::reg32 bits = random32(); std::memcpy(&f, &bits, 4); return f; }
    case 1: return 0.0f;
    case 2: return -0.0f;
    case 3: return std::ldexp(float(int(g_random() % 2001) - 1000), -140);
    case 4: return (g_random() & 1) ? INFINITY : -INFINITY;
    case 5: return std::ldexp(1.0f + float(g_random() % 1000) / 1000.0f, int(g_random() % 250) - 125);
    default: return float(int(g_random() % 20001) - 10000) * 0.37f;
    }
}

double anyDouble(double real)
{
    switch (g_random() % 6)
    {
    case 0: { double d; uint64_t bits = (uint64_t(random32()) << 32) | random32(); std::memcpy(&d, &bits, 8); return d; }
    case 1: return -real;
    case 2: return real * 1e30;
    default: return real;
    }
}

/* A buffer or slot index: mostly one of eacsnd's, now and then far beyond. */
x86::reg32 anyIndex(x86::reg32 count, x86::reg32 recordBytes)
{
    if (chance(85))
        return g_random() % count;
    const x86::reg32 most = (kWindowEnd - 0xa3d000) / recordBytes;
    return g_random() % most;
}

template <typename T>
T& mem(win32::WinApplication& app, x86::reg32 at)
{
    return reinterpret_cast<T&>(*&app.getMemory<x86::reg8>(at));
}

x86::reg8* bytes(win32::WinApplication& app, x86::reg32 at)
{
    return &app.getMemory<x86::reg8>(at);
}

struct Counts
{
    unsigned cases = 0, ran = 0, stepped = 0, stopped = 0, failed = 0;
};

const char* g_name = "";
unsigned g_case = 0;

bool report(Counts& counts, const char* what)
{
    if (++counts.failed <= 10)
        std::printf("  %s case %u: %s\n", g_name, g_case, what);
    return false;
}

/* The first byte of [from, to) where the two memories differ, or `to`. */
x86::reg32 firstDifference(win32::WinApplication& a, win32::WinApplication& b, x86::reg32 from, x86::reg32 to)
{
    if (to <= from || std::memcmp(bytes(a, from), bytes(b, from), to - from) == 0)
        return to;
    for (x86::reg32 at = from; at < to; ++at)
        if (*bytes(a, at) != *bytes(b, at))
            return at;
    return to;
}

void copyWindows(win32::WinApplication& to, win32::WinApplication& from)
{
    std::memcpy(bytes(to, kWindow), bytes(from, kWindow), kWindowEnd - kWindow);
    std::memcpy(bytes(to, kScratch), bytes(from, kScratch), kScratchEnd - kScratch);
    std::memcpy(bytes(to, kStackLow), bytes(from, kStackLow), kStackHigh - kStackLow);
}

/* One case of one export: the state made up on `g`, copied to `n`, then both
 * run and compared. */
bool runCase(const Export& e, win32::CheckApp& g, win32::CheckApp& n, Counts& counts)
{
    ++counts.cases;
    // eacsnd's globals afresh: random, but its flags and functions as a case wants them.
    for (x86::reg32 at = kGlobals; at < kGlobalsEnd; at += 4)
        mem<x86::reg32>(g, at) = random32();
    const bool portState = chance(80);
    mem<x86::reg8>(g, isnd::kDirectSoundMade) = portState || chance(30) ? 0 : x86::reg8(1 + g_random() % 255);
    mem<x86::reg8>(g, isnd::kIs3d) = portState || chance(40) ? 0 : x86::reg8(1 + g_random() % 255);
    for (x86::reg32 at = isnd::kFunctionMix; at <= isnd::kFunctionConvert; at += 4)
        mem<x86::reg32>(g, at) = kStubOther;
    mem<x86::reg32>(g, isnd::kFunctionStopBuffer) = kStubStop;
    mem<x86::reg32>(g, isnd::kFunctionBufferPosition) = kStubPosition;
    mem<double>(g, isnd::kPositionScale) = anyDouble(g_scale);

    // What the caller's esi may point at: records of COM objects, or none.
    const auto object = [&]() -> x86::reg32 {
        switch (g_random() % 3)
        {
        case 0: return 0;
        default: return kObjects + 16 * (g_random() % 16);
        }
    };
    for (x86::reg32 at = kScratch; at < kObjects; at += 4)
        mem<x86::reg32>(g, at) = object();
    for (x86::reg32 i = 0; i < 16; ++i)
    {
        mem<x86::reg32>(g, kObjects + 16 * i) = kVtable;
        mem<x86::reg32>(g, kObjects + 16 * i + 4) = random32();
    }
    mem<x86::reg32>(g, kVtable + 8) = kStubRelease;

    // The stack: random, the return address, the arguments.
    for (x86::reg32 at = kStackLow; at < kStackHigh; at += 4)
        mem<x86::reg32>(g, at) = random32();
    const x86::reg32 esp = kStackHigh - 0x400 - 4 * (g_random() % 64);
    x86::reg32 arguments[8];
    for (x86::reg32& a : arguments)
        a = random32();
    if (e.generated == &eacsnd::sub_a33e18 || e.generated == &eacsnd::sub_a33e68 || e.generated == &eacsnd::sub_a33f0c
        || e.generated == &eacsnd::sub_a341b0)
        arguments[0] = anyIndex(isnd::kBufferCount, isnd::kBufferBytes);
    if (e.generated == &eacsnd::sub_a33fc0)
        arguments[0] = anyIndex(isnd::kSlotCount, isnd::kSlotBytes);
    // pos3d reads its buffer after the call out; with esp left off, from the
    // next argument.
    if (e.generated == &eacsnd::sub_a33e68)
        for (x86::reg32 i = 1; i < 3; ++i)
            arguments[i] = anyIndex(isnd::kBufferCount, isnd::kBufferBytes);
    for (x86::reg32 i = 0; i < 8; ++i)
        mem<x86::reg32>(g, esp + 4 + 4 * i) = arguments[i];

    // The registers, esi now and then at a record of the scratch area.
    x86::CPU cpu{};
    cpu.eax = random32();
    cpu.ebx = random32();
    cpu.ecx = random32();
    cpu.edx = random32();
    cpu.esi = kScratch + 4 * (g_random() % 0x7f0);
    cpu.edi = random32();
    cpu.ebp = random32();
    cpu.esp = esp;
    if (e.generated == &eacsnd::sub_a34014)
    {
        mem<x86::reg32>(g, cpu.esi + isnd::kBufferActive) = object();
        mem<x86::reg32>(g, cpu.esi + isnd::kBufferMain) = chance(30) ? mem<x86::reg32>(g, cpu.esi) : object();
        mem<x86::reg32>(g, cpu.esi + isnd::kBuffer3d) = object();
    }

    // The stand-ins' script.
    g_script = Script{};
    for (auto& call : g_script.position)
        for (float& f : call)
            f = anyFloat();
    for (x86::reg32& r : g_script.result)
        r = random32();
    if (chance(10))
    {
        g_script.scribble = int(g_random() % 2);
        g_script.scribbleValue = chance(50) ? 0 : object();
    }
    if (chance(5))
    {
        g_script.moveEsi = int(g_random() % 2);
        g_script.newEsi = kScratch + 4 * (g_random() % 0x7f0);
    }
    if (chance(5))
        g_script.skewEsp = int(g_random() % 2);
    if (chance(5))
        g_script.stop = int(g_random() % 2);

    copyWindows(n, g);
    g.calls.clear();
    n.calls.clear();

    // The native first: it steps aside where eacsnd's way is not native, and
    // then it must not have touched anything.
    const bool made = mem<x86::reg8>(g, isnd::kDirectSoundMade) != 0;
    const bool is3d = mem<x86::reg8>(g, isnd::kIs3d) != 0;
    const bool toStep = (e.stepAside == kWithDirectSound && made)
                        || (e.stepAside == kWith3dAndDirectSound && is3d && made)
                        || (e.stepAside == kWith3d && is3d);
    x86::CPU nativeCpu = cpu;
    const bool ran = e.native(&n, nativeCpu);
    if (ran == toStep)
        return report(counts, toStep ? "ran where eacsnd's way is not native" : "stepped aside where it should run");
    if (!ran)
    {
        ++counts.stepped;
        if (nativeCpu.eax != cpu.eax || nativeCpu.ebx != cpu.ebx || nativeCpu.ecx != cpu.ecx
            || nativeCpu.edx != cpu.edx || nativeCpu.esi != cpu.esi || nativeCpu.edi != cpu.edi
            || nativeCpu.ebp != cpu.ebp || nativeCpu.esp != cpu.esp || nativeCpu.terminate)
            return report(counts, "stepped aside with the registers changed");
        if (!n.calls.empty())
            return report(counts, "stepped aside after calling out");
        for (const auto& w : {std::make_pair(kWindow, kWindowEnd), std::make_pair(kScratch, kScratchEnd),
                              std::make_pair(kStackLow, kStackHigh)})
            if (firstDifference(g, n, w.first, w.second) != w.second)
                return report(counts, "stepped aside with memory changed");
        return true;
    }
    ++counts.ran;
    x86::CPU generatedCpu = cpu;
    e.generated(&g, generatedCpu);

    char what[256];
    const bool stopped = generatedCpu.terminate;
    if (stopped)
        ++counts.stopped;
    if (nativeCpu.terminate != generatedCpu.terminate)
        return report(counts, "stopped in one run only");
    if (!(g.calls == n.calls))
    {
        std::snprintf(what, sizeof what, "calls out: %zu generated, %zu native", g.calls.size(), n.calls.size());
        for (size_t i = 0; i < g.calls.size() && i < n.calls.size(); ++i)
            if (!(g.calls[i] == n.calls[i]))
            {
                std::snprintf(what, sizeof what, "call %zu: %08x at esp %08x (%08x %08x %08x) generated, %08x at %08x (%08x %08x %08x) native",
                              i, g.calls[i].address, g.calls[i].esp, g.calls[i].arguments[0], g.calls[i].arguments[1],
                              g.calls[i].arguments[2], n.calls[i].address, n.calls[i].esp, n.calls[i].arguments[0],
                              n.calls[i].arguments[1], n.calls[i].arguments[2]);
                break;
            }
        return report(counts, what);
    }
    if (generatedCpu.esp != nativeCpu.esp)
    {
        std::snprintf(what, sizeof what, "esp %08x generated, %08x native", generatedCpu.esp, nativeCpu.esp);
        return report(counts, what);
    }
    if (!stopped)
    {
        const struct { const char* name; x86::reg32 g, n; } registers[] = {
            {"eax", generatedCpu.eax, nativeCpu.eax}, {"ebx", generatedCpu.ebx, nativeCpu.ebx},
            {"esi", generatedCpu.esi, nativeCpu.esi}, {"edi", generatedCpu.edi, nativeCpu.edi},
            {"ebp", generatedCpu.ebp, nativeCpu.ebp},
        };
        for (const auto& r : registers)
            if (r.g != r.n)
            {
                std::snprintf(what, sizeof what, "%s %08x generated, %08x native", r.name, r.g, r.n);
                return report(counts, what);
            }
    }
    for (const auto& w : {std::make_pair(kWindow, kWindowEnd), std::make_pair(kScratch, kScratchEnd),
                          std::make_pair(kStackLow, kStackHigh)})
    {
        const x86::reg32 at = firstDifference(g, n, w.first, w.second);
        if (at != w.second)
        {
            std::snprintf(what, sizeof what, "memory at %08x: %02x generated, %02x native", at, *bytes(g, at),
                          *bytes(n, at));
            return report(counts, what);
        }
    }
    return true;
}

}

int main(int argc, char** argv)
{
    const unsigned cases = argc > 1 ? unsigned(std::strtoul(argv[1], nullptr, 10)) : 20000;
    // mutations.py's: stop at the first case that fails, and check one export.
    const bool stopAtFirst = argc > 2 && std::strcmp(argv[2], "--first") == 0;
    const char* only = argc > 3 ? argv[3] : nullptr;
    win32::CheckApp g, n;
    for (win32::CheckApp* app : {&g, &n})
    {
        std::memcpy(bytes(*app, kAuto), eacsnd::s_AUTOSegment, kAutoBytes);
        std::memcpy(bytes(*app, kImports), eacsnd::s__idataSegment, kImportsBytes);
        std::memcpy(bytes(*app, kData), eacsnd::s_DGROUPSegment, kDataBytes);
        std::memcpy(bytes(*app, kExportTable), eacsnd::s__edataSegment, kExportTableBytes);
    }
    g_scale = mem<double>(g, isnd::kPositionScale);
    std::printf("the position scale as eacsnd has it: %.17g\n", g_scale);

    bool failed = false;
    for (const Export& e : kExports)
    {
        if (only && std::strcmp(only, e.name) != 0)
            continue;
        Counts counts;
        g_name = e.name;
        for (g_case = 0; g_case < cases; ++g_case)
        {
            if (!runCase(e, g, n, counts) && stopAtFirst)
                return 1;
            // Both memories alike again, the dead stack included, for the next case.
            copyWindows(n, g);
            if (g_case % 2000 == 1999 || g_case + 1 == cases)
            {
                const x86::reg32 at = firstDifference(g, n, 0, kMemory);
                if (at != kMemory)
                {
                    std::printf("  %s: memory at %08x written outside the windows\n", e.name, at);
                    ++counts.failed;
                    std::memcpy(bytes(n, 0), bytes(g, 0), kMemory);
                }
            }
        }
        std::printf("%-24s %7u cases: %7u run, %6u stepped aside, %5u stopped the game -- %u failed\n", e.name,
                    counts.cases, counts.ran, counts.stepped, counts.stopped, counts.failed);
        failed = failed || counts.failed != 0;
    }
    std::printf(failed ? "FAILED\n" : "all alike\n");
    return failed ? 1 : 0;
}
