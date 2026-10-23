/* specs_checks.cpp -- sub_4b22d0's decompiled native against its generated
 * transcription, in the manner of tools/loading_checks: the same memory and
 * registers for both, everything but the stack below the returned esp
 * compared.  The heap is a bump allocator with a failure knob so the ways out
 * when an allocation fails run too; sprintf and memset are the port's real
 * Watcom natives; the names, the numbers in parentheses and the format
 * strings come from the game's own images. */
#include <nfs3hp.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <map>
#include <random>
#include <string>
#include <vector>
#include <sys/mman.h>

#include "spec_images.h"
#include <lib/thread.h>

namespace x86
{
std::uint32_t g_lastIp = 0;
void assertLog(const char* file, int line, const char* expr)
{
    std::printf("assert %s:%d %s (ip=%08x)\n", file, line, expr, unsigned(g_lastIp));
}
}

namespace nfs3hp
{
bool nativesEnabled() { return true; }
bool nativeOriginalRunning() { return false; }
bool nativeChecking() { return false; }

bool specsFileLine(win32::WinApplication* app, x86::CPU& cpu);  // native_specs_file.cpp

constexpr x86::reg32 kMemory = 0x4000000;
constexpr x86::reg32 kStack = 0x3ff0000;
constexpr x86::reg32 kHeapNext = 0x27ffff0;
constexpr x86::reg32 kHeap = 0x2800000;
constexpr x86::reg32 kRecord = 0x580000;   // the record under test, 0x1000 bytes
constexpr x86::reg32 kOutSize = 0x57f000;  // the caller's dword for the length
constexpr x86::reg32 kNameTable = 0x55eddc;
constexpr x86::reg32 kDescTable = 0x4af3b2;
constexpr x86::reg32 kNewLine = 0x4b0698;

x86::reg8* g_memory = nullptr;
std::map<x86::reg32, win32::MethodPtr> g_methods;

inline void setWordStatic(x86::reg32 at, x86::reg32 value)
{
    std::memcpy(g_memory + at, &value, 4);
}

/* The allocation failure knob: the nth call and later return null (-1 never). */
int g_allocFailAfter = -1;
int g_allocCalls = 0;
}  // namespace nfs3hp

namespace win32
{

WinApplication::WinApplication(const char*, x86::reg32, const std::vector<Section>&)
{
    void* memory = mmap(nullptr, nfs3hp::kMemory, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (memory == MAP_FAILED)
        std::abort();
    m_memory = static_cast<x86::reg8*>(memory);
    nfs3hp::g_memory = m_memory;
    /* the game's own data: the names, the ids, the format strings, "\r\n". */
    std::memcpy(m_memory + g_dgroup_at, g_dgroup, g_dgroup_len);
    {   /* the whole code segment, jump tables and constants included */
        FILE* image = std::fopen(SPEC_AUTO_BIN, "rb");
        if (!image || std::fread(m_memory + 0x401000, 1, g_auto_len, image) != g_auto_len)
            std::abort();
        std::fclose(image);
    }
    /* the runtime's init (0x4ff570) aims the float format slots at
     * __EFG_printf and __EFG_scanf; the file image still holds the error
     * stub there. */
    nfs3hp::setWordStatic(0x56ac64, 0x51f140);
    nfs3hp::setWordStatic(0x56ac68, 0x51f254);
}

WinApplication::~WinApplication() {}

int WinApplication::s_traceApi = 0;
bool WinApplication::readTraceApi() { return false; }
void WinApplication::traceCall(const Method&, x86::reg32) {}
void WinApplication::yieldContext(const x86::CPU&) {}

void WinApplication::dynamicCallElsewhere(x86::reg32 address, x86::CPU& cpu)
{
    auto method = nfs3hp::g_methods.find(address);
    if (method == nfs3hp::g_methods.end())
    {
        std::printf("no method at %08x\n", unsigned(address));
        std::abort();
    }
    method->second(this, cpu);
}

void MemMap::usedRanges(std::vector<std::pair<x86::reg32, x86::reg32>>& ranges)
{
    ranges.assign(1, {0, nfs3hp::kMemory});
}

/* the conio path's context locks and sleep, never run here. */
void WinApplication::lockContext(const x86::CPU&) {}
void WinApplication::unlockContext(const x86::CPU&) {}
void win32::Thread::sleep(x86::reg32) {}

}

namespace nfs3hp
{

inline x86::reg32 word(x86::reg32 at)
{
    x86::reg32 value;
    std::memcpy(&value, g_memory + at, 4);
    return value;
}

inline void setWord(x86::reg32 at, x86::reg32 value)
{
    std::memcpy(g_memory + at, &value, 4);
}

/* The heap as a bump allocator, the loading_checks way; the failure knob
 * makes the nth and later allocations null. */
void Application::sub_4e1620(WinApplication*, x86::CPU& cpu)
{
    const x86::reg32 at = word(kHeapNext);
    ++g_allocCalls;
    if (g_allocFailAfter >= 0 && g_allocCalls > g_allocFailAfter)
    {
        cpu.eax = 0;
        cpu.flags.zf = 1;
        cpu.flags.sf = 0;
        cpu.flags.cf = 0;
        cpu.flags.of = 0;
        cpu.esp += 4;
        return;
    }
    setWord(kHeapNext, at + ((cpu.edx + 15) & ~15u));
    cpu.eax = at;
    cpu.flags.zf = 0;
    cpu.flags.sf = 1;
    cpu.esp += 4;
}

void Application::sub_4e1890(WinApplication*, x86::CPU& cpu)
{
    /* the real free pushes and pops ebx, ecx, edx, esi, edi and ebp; its eax
     * is what neither caller reads back. */
    cpu.eax = 0;
    cpu.esp += 4;
}

/* The real Watcom natives behind the registry addresses the native calls. */
static void call_sprintf(win32::WinApplication* app, x86::CPU& cpu) { watcom::sprintf(app, cpu); }
static void call_memset(win32::WinApplication* app, x86::CPU& cpu) { watcom::memset(app, cpu); }
static void call_mem_putc(win32::WinApplication* app, x86::CPU& cpu) { watcom::mem_putc(app, cpu); }
static void call_vsprintf(win32::WinApplication* app, x86::CPU& cpu) { watcom::vsprintf(app, cpu); }

Application::Application(const char* appName)
    : WinApplication(appName, 0x400000, {})
{
    g_methods = {
        {0x4b0790, &Application::sub_4b0790}, {0x4b07c0, &Application::sub_4b07c0},
        {0x4b0880, &Application::sub_4b0880}, {0x4b08d0, &Application::sub_4b08d0},
        {0x4b22d0, &Application::sub_4b22d0},
        {0x4e1620, &Application::sub_4e1620}, {0x4e1890, &Application::sub_4e1890},
        {0x4df690, &call_sprintf}, {0x4e0640, &call_memset},
        {0x4df660, &call_mem_putc}, {0x4df674, &call_vsprintf},
        {0x51f140, &Application::sub_51f140}, {0x51f254, &Application::sub_51f254},
    };
}

}  // namespace nfs3hp

namespace
{

std::mt19937 g_random(1998);

x86::reg32 random(x86::reg32 below)
{
    return below ? x86::reg32(g_random() % below) : 0;
}

x86::CPU entryState(x86::reg32 serial, bool withRecord = true)
{
    x86::CPU cpu;
    std::memset(&cpu, 0, sizeof cpu);
    cpu.init(0, 0);
    cpu.eax = withRecord ? nfs3hp::kRecord : 0;
    cpu.edx = nfs3hp::kOutSize;
    cpu.ebx = serial;
    cpu.ecx = g_random();
    cpu.esi = g_random();
    cpu.edi = g_random();
    cpu.ebp = g_random();
    cpu.esp = nfs3hp::kStack;
    cpu.flags.lo = x86::reg8((g_random() & 0xd5) | 0x02);
    cpu.flags.of = g_random() & 1;
    cpu.flags.df = 0;
    return cpu;
}

typedef bool (*Native)(win32::WinApplication*, x86::CPU&);

struct Totals
{
    unsigned cases = 0;
    unsigned failures = 0;
};

std::map<std::string, Totals> g_totals;

bool compare(nfs3hp::Application& app, const char* name, Native nativeFn, x86::CPU entry)
{
    Totals& totals = g_totals[name];
    ++totals.cases;
    static std::vector<x86::reg8> before, original;
    before.assign(nfs3hp::g_memory, nfs3hp::g_memory + nfs3hp::kMemory);

    x86::CPU generated = entry;
    x86::g_lastIp = generated.ip;
    app.dynamic_call(0x4b22d0, generated);
    x86::g_lastIp = generated.ip;
    original.assign(nfs3hp::g_memory, nfs3hp::g_memory + nfs3hp::kMemory);

    std::memcpy(nfs3hp::g_memory, before.data(), nfs3hp::kMemory);
    nfs3hp::g_allocCalls = 0;
    x86::CPU mine = entry;
    const bool took = nativeFn(&app, mine);
    if (!took)
    {
        std::printf("%s: the native stepped aside\n", name);
        ++totals.failures;
        return false;
    }

    char what[300] = "";
    const x86::reg32 stackEnd = generated.esp;
    const x86::reg32 stackStart = generated.esp - 0x10000;
    unsigned differing = 0;
    for (x86::reg32 chunk = 0; chunk < nfs3hp::kMemory; chunk += 0x10000)
    {
        if (std::memcmp(nfs3hp::g_memory + chunk, &original[chunk], 0x10000) == 0)
            continue;
        for (x86::reg32 i = chunk; i < chunk + 0x10000; ++i)
        {
            if (nfs3hp::g_memory[i] == original[i] || (i >= stackStart && i < stackEnd))
                continue;
            if (differing++ == 0)
                std::snprintf(what, sizeof what, "memory at %08x: %02x native, %02x generated", unsigned(i),
                              unsigned(nfs3hp::g_memory[i]), unsigned(original[i]));
        }
    }
    if (differing > 1)
    {
        const std::size_t length = std::strlen(what);
        std::snprintf(what + length, sizeof what - length, " (%u bytes)", differing);
    }
    if (!what[0]
        && (mine.eax != generated.eax || mine.ebx != generated.ebx || mine.ecx != generated.ecx
            || mine.edx != generated.edx || mine.esi != generated.esi || mine.edi != generated.edi
            || mine.ebp != generated.ebp || mine.esp != generated.esp))
        std::snprintf(what, sizeof what,
                      "registers native/generated: eax %08x/%08x ebx %08x/%08x ecx %08x/%08x edx %08x/%08x "
                      "esi %08x/%08x edi %08x/%08x ebp %08x/%08x esp %08x/%08x",
                      unsigned(mine.eax), unsigned(generated.eax), unsigned(mine.ebx), unsigned(generated.ebx),
                      unsigned(mine.ecx), unsigned(generated.ecx), unsigned(mine.edx), unsigned(generated.edx),
                      unsigned(mine.esi), unsigned(generated.esi), unsigned(mine.edi), unsigned(generated.edi),
                      unsigned(mine.ebp), unsigned(generated.ebp), unsigned(mine.esp), unsigned(generated.esp));
    if (!what[0] && mine.flags.lo != generated.flags.lo)
        std::snprintf(what, sizeof what, "flags lo native %02x generated %02x", unsigned(mine.flags.lo),
                      unsigned(generated.flags.lo));
    if (!what[0] && (mine.flags.hi != generated.flags.hi || mine.flags.of != generated.flags.of))
        std::snprintf(what, sizeof what, "flags hi/of differ");
    if (!what[0] && std::memcmp(&mine.fpu, &generated.fpu, sizeof(x86::FPU)) != 0)
        std::snprintf(what, sizeof what, "the fpu state differs");
    if (!what[0])
        return true;
    std::printf("%s: %s\n", name, what);
    ++totals.failures;
    return false;
}

int runs = 0;

void oneCaseNull(nfs3hp::Application& app)
{
    nfs3hp::setWord(nfs3hp::kOutSize, g_random());
    nfs3hp::g_allocCalls = 0;
    nfs3hp::g_allocFailAfter = -1;
    compare(app, "null pointer", nfs3hp::specsFileLine, entryState(g_random(), false));
}

void oneCase(nfs3hp::Application& app, const char* name, int failAfter, bool withRecord)
{
    /* the record's fields, and the caller's dword, as the caller might have
     * them; the serial in ebx. */
    for (x86::reg32 i = 0; i < 0x1000; i += 4)
    {
        x86::reg32 v = g_random();
        if (!withRecord)
            v = 0;
        nfs3hp::setWord(nfs3hp::kRecord + i, v);
    }
    nfs3hp::setWord(nfs3hp::kOutSize, g_random());
    nfs3hp::g_allocCalls = 0;
    nfs3hp::g_allocFailAfter = failAfter;
    const char* dot = std::strrchr(name, ';');
    std::string label = std::string(dot ? dot + 1 : name);
    compare(app, name, nfs3hp::specsFileLine, entryState(g_random()));
}

}  // namespace

int main()
{
    nfs3hp::Application app("nfs3hp");

    /* the record null, the record whole, an allocation failing at the first
     * field, in the middle, at the last, and at the join. */
    oneCaseNull(app);
    oneCase(app, "zeroed record", -1, false);
    for (int i = 0; i < 32; ++i)
        oneCase(app, "whole record", -1, true);
    /* what the first whole record's text looks like, for the eye */
    {
        nfs3hp::setWord(nfs3hp::kHeapNext, nfs3hp::kHeap);
        nfs3hp::g_allocCalls = 0;
        nfs3hp::g_allocFailAfter = -1;
        x86::CPU cpu = entryState(0x1234abcd);
        nfs3hp::specsFileLine(&app, cpu);
        std::printf("---- the text, first 400 bytes ----\n%.400s\n----\n",
                    (const char*)(nfs3hp::g_memory + cpu.eax));
    }
    oneCase(app, "first alloc fails", 1, true);
    oneCase(app, "alloc fails at field 2", 2, true);
    oneCase(app, "alloc fails mid-table", 41, true);
    oneCase(app, "alloc fails at field 80", 80, true);
    oneCase(app, "join alloc fails", 81, true);
    oneCase(app, "alloc fails past the join", 82, true);
    oneCase(app, "zeroed record again", -1, false);
    oneCaseNull(app);

    unsigned cases = 0, failures = 0;
    for (const auto& [name, totals] : g_totals)
    {
        cases += totals.cases;
        failures += totals.failures;
    }
    std::printf("specs checks: %u cases, %u failures\n", cases, failures);
    return failures ? 1 : 0;
}
