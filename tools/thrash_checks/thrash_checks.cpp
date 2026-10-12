/* src/nfs3hp/native_thrash.cpp against voodoo2a's generated code, on the
 * desktop, without the game.
 *
 * voodoo2a's generated code is made afresh from nfs3hp/voodoo2a.dll by the
 * port's own generator, without the hooks of the tree's copy (generate.py), and
 * built with the port's headers.  Two guest memories hold the same state:
 * voodoo2a's image as it loads, its variables made up for every case, the
 * game's vertices, records and buffers, and the stack.  An export runs
 * generated on one and natively (THRASH_*, native_thrash.cpp) on the other,
 * and then they are compared: every call out in order -- Glide's functions,
 * Win32's through voodoo2a's imports, the game's callbacks, DirectDraw's
 * methods -- with what it was handed (a vertex as the ten fields voodoo2a
 * sets); eax where the export gives something back, esp, ebx, esi, edi and
 * ebp; and every byte of voodoo2a's image, the game's buffers, the heap and
 * the stack from the arguments up.  The stack below them is the exports' own
 * and nobody else's.  Every so often all of both memories are compared, for a
 * write anywhere else.
 *
 * Glide is called two ways: voodoo2a's code through its table of Glide's
 * functions, the natives straight (glide2x::drawTriangle, drawLine and
 * glide2x::direct) or through the same table.  Here both go to one stand-in
 * per function, which takes what the port's Glide would take of its arguments
 * -- a byte, a word, a float's bits -- and does what it would with eax: a
 * function the port has as void leaves it as it was.
 *
 * The stand-ins' results come from the case's seed and the call's place in
 * the case, the same for both runs as long as both make the same calls.
 * Win32's functions and the game's may stop the game (cpu.terminate) at a
 * call a case picks: from there on neither run may do anything.
 *
 * Every drawing export runs with voodoo2a's drawing pointed every way
 * THRASH_setstate points it -- Glide's own triangle and line, antialiased,
 * in two passes, both -- and now and then at the game's own functions.
 * "malloc/free" is voodoo2a's heap alone: a run of allocations and frees,
 * the heap growing by VirtualAlloc and giving miniheaps back.
 *
 * See run.sh. */
#include "voodoo2a.h"
#include "native_thrash.h"
#include "thrash.h"
#include <lib/gliderenderer.h>
#include <lib/memmap.h>
#include <lib/thrashrenderer.h>
#include <winapi/glide2x.h>
#include <SDL3/SDL.h>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <random>
#include <string>
#include <vector>
#include <sys/mman.h>

namespace x86
{
void assertLog(const char* file, int line, const char* expr)
{
    std::printf("assert %s:%d %s\n", file, line, expr);
}
}

/* What native_thrash.cpp and src/lib/cpu.cpp want of SDL. */
extern "C"
{
Uint64 SDL_GetPerformanceCounter(void) { return 0; }
Uint64 SDL_GetPerformanceFrequency(void) { return 1; }
const char* SDL_getenv(const char* name) { return std::getenv(name); }
int SDL_strcmp(const char* a, const char* b) { return std::strcmp(a, b); }
}

namespace
{

constexpr x86::reg32 kMemory = 0x1000000;

/* Where things are, in both memories. */
constexpr x86::reg32 kImage = 0xa83200, kImageEnd = 0xa97600;      // voodoo2a as it loads
constexpr x86::reg32 kCodeEnd = 0xa8fe00;
constexpr x86::reg32 kGame = 0x600000, kGameEnd = 0x680000;        // the game's vertices, records, buffers
constexpr x86::reg32 kVertices = 0x600000;                         // 512 of the game's vertices
constexpr x86::reg32 kVertexCount = 512;
constexpr x86::reg32 kIndices = 0x610000;                          // 4096 vertex indices
constexpr x86::reg32 kRecords = 0x620000;                          // 16 texture records of 0x20 bytes
constexpr x86::reg32 kLambdaRecord = 0x621000;                     // THRASH_setstate 0x13's
constexpr x86::reg32 kFogBytes = 0x622000;                         // THRASH_setstate 0x69's
constexpr x86::reg32 kPixels = 0x630000;
constexpr x86::reg32 kResult = 0x631000;                           // where the mode message's result goes
constexpr x86::reg32 kDirectDraw = 0x632000, kDirectDrawVtable = 0x632100;
constexpr x86::reg32 kSlotMap = 0x633000;                          // VirtualAlloc's slots in use
constexpr x86::reg32 kHeap = 0x100000, kHeapEnd = 0x500000;        // VirtualAlloc's 16 slots
constexpr x86::reg32 kSlotSize = 0x40000;
constexpr x86::reg32 kStackLow = 0xef0000, kStackHigh = 0xf00000;

/* The stand-ins' addresses: anything dynamic_call does not know. */
constexpr x86::reg32 kGlideStub = 0xe00000;     // + 0x10 a function of voodoo2a's Glide table
constexpr x86::reg32 kImportStub = 0xe10000;    // + an import's offset in voodoo2a's table
constexpr x86::reg32 kFindWindow = 0xe20000;    // the game's callbacks
constexpr x86::reg32 kExecute = 0xe20010;
constexpr x86::reg32 kLockHook = 0xe20020;
constexpr x86::reg32 kLog = 0xe20030;
constexpr x86::reg32 kGameTriangle = 0xe20040;  // a drawing pointer the game set
constexpr x86::reg32 kGameLine = 0xe20050;
constexpr x86::reg32 kSetCooperativeLevel = 0xe20060;
constexpr x86::reg32 kRelease = 0xe20070;
constexpr x86::reg32 kGlideModule = 0x7700;     // what LoadLibraryA hands back

constexpr x86::reg32 kGlideTable = 0xa93614;

/* voodoo2a's Glide table, in its order, and what the port's Glide takes of
 * each argument: w a dword, b its byte, h its word, s its word sign-extended,
 * p a pointer that is logged, o one that is not (into the caller's frame), v
 * a GrVertex (the ten fields voodoo2a sets), f the 64 bytes of a fog table. */
struct GlideFunction
{
    const char* name;
    const char* arguments;
    bool returns;
};

const GlideFunction kGlide[] = {
    {"_grGlideInit@0", "", false},
    {"_grSstQueryHardware@4", "p", true},
    {"_grSstQueryBoards@4", "p", true},
    {"_grGlideShutdown@0", "", false},
    {"_grSstSelect@4", "w", false},
    {"_grSstWinClose@0", "", false},
    {"_grSstWinOpen@28", "wwwwwww", true},
    {"_grTexCombineFunction@8", "ww", false},
    {"_grChromakeyValue@4", "w", false},
    {"_grAlphaTestReferenceValue@4", "b", false},
    {"_grTexDownloadTable@12", "wwp", false},
    {"_grRenderBuffer@4", "w", false},
    {"_grBufferClear@12", "wbh", false},
    {"_grBufferSwap@4", "w", false},
    {"_grSstStatus@0", "", true},
    {"_grSstVRetraceOn@0", "", true},
    {"_grSstIdle@0", "", false},
    {"_grSstIsBusy@0", "", false},
    {"_grClipWindow@16", "wwww", false},
    {"_grColorCombine@20", "wwwww", false},
    {"_grAlphaCombine@20", "wwwww", false},
    {"_grAlphaBlendFunction@16", "wwww", false},
    {"_grCullMode@4", "w", false},
    {"_grTexFilterMode@12", "www", false},
    {"_grDitherMode@4", "w", false},
    {"_grChromakeyMode@4", "w", false},
    {"_grAlphaTestFunction@4", "w", false},
    {"_grDepthBufferMode@4", "w", false},
    {"_grDepthBufferFunction@4", "w", false},
    {"_grDepthMask@4", "w", false},
    {"_grFogColorValue@4", "w", false},
    {"_grFogMode@4", "w", false},
    {"_grFogTable@4", "f", false},
    {"_grLfbLock@24", "wwwwwo", true},
    {"_grLfbUnlock@8", "ww", true},
    {"_grLfbWriteRegion@32", "wwwwwwwp", true},
    {"_grLfbReadRegion@28", "wwwwwwp", true},
    {"_grDrawTriangle@12", "vvv", false},
    {"_grDrawLine@8", "vv", false},
    {"_grDrawPoint@4", "v", false},
    {"_grGammaCorrectionValue@4", "w", false},
    {"_grDepthBiasLevel@4", "s", false},
    {"_grTexMipMapMode@12", "www", false},
    {"_grTexCombine@28", "wwwwwww", false},
    {"_grTexCalcMemRequired@16", "wwww", true},
    {"_grTexDownloadMipMap@16", "wwwp", false},
    {"_grTexMinAddress@4", "w", true},
    {"_grTexMaxAddress@4", "w", true},
    {"_grTexSource@16", "wwwp", false},
    {"_grTexClampMode@12", "www", false},
    {"_grGlideGetVersion@4", "o", false},
    {"_grAADrawTriangle@24", "vvvwww", false},
    {"_grAADrawLine@8", "vv", false},
    {"_grHints@8", "ww", false},
    {"_grTexLodBiasValue@8", "ww", false},
    {"_grSstScreenWidth@0", "", true},
    {"_grSstScreenHeight@0", "", true},
    {"_grBufferNumPending@0", "", true},
    {"_grSstControl@4", "w", true},
};
constexpr unsigned kGlideCount = sizeof kGlide / sizeof kGlide[0];

enum Glide : unsigned
{
    kQueryHardware = 1, kQueryBoards = 2, kWinOpen = 6, kStatus = 14, kRetraceOn = 15, kLfbLock = 33,
    kLfbUnlock = 34, kLfbWrite = 35, kLfbRead = 36, kDrawTriangle = 37, kDrawLine = 38, kCalcMemory = 44,
    kTexMin = 46, kTexMax = 47, kGetVersion = 50, kScreenWidth = 55, kScreenHeight = 56, kPending = 57,
    kControl = 58,
};

/* voodoo2a's imports that its code calls, by their place in its table. */
struct Import
{
    x86::reg32 slot;
    const char* name;
    x86::reg32 arguments;
};

const Import kImports[] = {
    {0xa903ec, "LoadLibraryA", 1}, {0xa903d8, "GetProcAddress", 2}, {0xa90390, "FreeLibrary", 1},
    {0xa90368, "CreateEventA", 4}, {0xa90364, "CloseHandle", 1}, {0xa9035c, "SetForegroundWindow", 1},
    {0xa90358, "PostMessageA", 4}, {0xa90438, "WaitForSingleObject", 2}, {0xa90404, "SetEvent", 1},
    {0xa90448, "DirectDrawCreate", 3}, {0xa9042c, "VirtualAlloc", 4}, {0xa90430, "VirtualFree", 3},
};

struct Call
{
    x86::reg32 id;
    std::vector<x86::reg32> words;
    bool operator==(const Call& o) const { return id == o.id && words == o.words; }
};

/* The case: its seed and the call the game stops at, if any. */
std::uint64_t g_seed = 0;
long g_stopAt = -1;
bool g_lookupFails = false;  // GetProcAddress may not find grGlideInit and the two queries
x86::reg32 g_texMin = 0, g_texMax = 0;

std::uint64_t mix(std::uint64_t x)
{
    x += 0x9e3779b97f4a7c15ull;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ull;
    x = (x ^ (x >> 27)) * 0x94d049bb133111ebull;
    return x ^ (x >> 31);
}

typedef void (*Generated)(win32::WinApplication*, x86::CPU&);

struct Method
{
    x86::reg32 address;
    Generated function;
};

const Method kMethods[] = {
#include "voodoo2a_methods.inc"
};

Generated generatedAt(x86::reg32 address)
{
    const Method* end = kMethods + sizeof kMethods / sizeof kMethods[0];
    const Method* found = std::lower_bound(kMethods, end, address,
                                           [](const Method& m, x86::reg32 a) { return m.address < a; });
    return found != end && found->address == address ? found->function : nullptr;
}

}

namespace win32
{

/* A guest memory of its own, and its own log of calls out. */
class CheckApp : public WinApplication
{
public:
    CheckApp(bool generated) : WinApplication("thrash_checks", 0, {}), generated(generated) {}
    bool generated;
    std::vector<Call> calls;
    bool reachedGenerated = false;  // the native side called into voodoo2a's code

    x86::reg32& word(x86::reg32 address) { return reinterpret_cast<x86::reg32&>(*&getMemory<x86::reg8>(address)); }

    x86::reg32 random(x86::reg32 id)
    {
        return x86::reg32(mix(g_seed ^ (std::uint64_t(calls.size()) << 32) ^ id));
    }

    /* The call just logged stops the game: true when it does. */
    bool stops(x86::CPU& cpu)
    {
        if (long(calls.size()) - 1 != g_stopAt)
            return false;
        cpu.terminate = true;
        return true;
    }

    void logVertex(std::vector<x86::reg32>& words, x86::reg32 at)
    {
        for (const x86::reg32 offset : {0x00u, 0x04u, 0x0cu, 0x10u, 0x14u, 0x18u, 0x1cu, 0x20u, 0x24u, 0x28u})
            words.push_back(word(at + offset));
    }

    /* A Glide function, both ways: `words` already as the port's Glide takes
     * them; `out` where it writes, if it does.  Its result. */
    x86::reg32 glide(unsigned i, std::vector<x86::reg32> words, x86::reg32 out)
    {
        calls.push_back({kGlideTable + 4 * i, std::move(words)});
        const x86::reg32 r = random(i);
        switch (i)
        {
        case kQueryHardware:
            word(out + 4) = r % 3;
            word(out + 8) = 1 + (r >> 4) % 8;
            word(out + 0xc) = (r >> 8) % 4 == 0 ? 0 : (r >> 8) % 4 == 1 ? 0x100 : (r >> 8) % 4 == 2 ? 0x1000 : 2;
            word(out + 0x14) = (r >> 12) & 1;
            return (r >> 16) % 8 != 0;
        case kQueryBoards:
            word(out) = (r >> 4) % 4 == 0 ? 0 : (r >> 4) % 4 == 1 ? 0xffffffff : 1 + (r >> 6) % 2;
            return (r >> 16) % 6 != 0;
        case kWinOpen:
        case kLfbLock:
            if (i == kLfbLock)
            {
                word(out + 4) = 0x200000 + (r & 0xfff0);
                word(out + 8) = 0x800 + (r >> 16) % 4 * 0x200;
                word(out + 0xc) = 0;
                word(out + 0x10) = 0;
            }
            return (r >> 20) % 7 != 0;
        case kCalcMemory:
            return ((r % 0x60000) + 8) & ~7u;
        case kTexMin:
            return g_texMin;
        case kTexMax:
            return g_texMax;
        case kGetVersion:
        {
            static const char* const versions[] = {"Glide Version 2.43", "2.42", "2.41", "2.5", "2.53", "3.0",
                                                   "", "v2.4", "x", "Glide 2.42b"};
            if (r % 4 != 0)
                std::strcpy(&getMemory<char>(out), versions[(r >> 4) % 10]);
            return 0;
        }
        case kScreenWidth:
        case kScreenHeight:
            return 512 + (r % 4) * 128;
        case kPending:
        case kRetraceOn:
            return r % 10 < 3 ? 1 + (r >> 8) % 3 : 0;
        default:
            return r;
        }
    }

    /* A Glide function called from guest code, through voodoo2a's table. */
    void glideStub(unsigned i, x86::CPU& cpu)
    {
        const GlideFunction& f = kGlide[i];
        const x86::reg32 esp = cpu.esp;
        std::vector<x86::reg32> words;
        x86::reg32 out = 0;
        x86::reg32 at = esp + 4;
        for (const char* kind = f.arguments; *kind; ++kind, at += 4)
        {
            const x86::reg32 raw = word(at);
            switch (*kind)
            {
            case 'w': case 'p': words.push_back(raw); break;
            case 'b': words.push_back(raw & 0xff); break;
            case 'h': words.push_back(raw & 0xffff); break;
            case 's': words.push_back(x86::reg32(x86::sreg32(x86::sreg16(raw)))); break;
            case 'v': logVertex(words, raw); break;
            case 'f':
                for (x86::reg32 j = 0; j < 64; j += 4)
                    words.push_back(word(raw + j));
                break;
            case 'o': break;
            }
            if (*kind == 'o' || i == kQueryHardware || i == kQueryBoards)
                out = raw;
        }
        const x86::reg32 result = glide(i, std::move(words), out);
        if (f.returns)
            cpu.eax = result;
        cpu.ecx = 0x11111111;
        cpu.edx = 0x22222222;
        cpu.esp = esp + 4 + 4 * x86::reg32(std::strlen(f.arguments));
    }

    /* An import, a callback of the game's or a method of DirectDraw's. */
    void outside(x86::reg32 id, x86::reg32 count, x86::CPU& cpu)
    {
        const x86::reg32 esp = cpu.esp;
        std::vector<x86::reg32> words;
        for (x86::reg32 i = 0; i < count; ++i)
            words.push_back(word(esp + 4 + 4 * i));
        if (id == kGameTriangle || id == kGameLine)
        {
            words.clear();
            for (x86::reg32 i = 0; i < count; ++i)
                logVertex(words, word(esp + 4 + 4 * i));
        }
        calls.push_back({id, words});
        if (stops(cpu))
            return;
        const x86::reg32 r = random(id);
        x86::reg32 result = r;
        switch (id)
        {
        case 0xa903ec:  // LoadLibraryA
            result = r % 10 != 0 ? kGlideModule : 0;
            break;
        case 0xa903d8:  // GetProcAddress
        {
            const std::string name = &getMemory<char>(words[1]);
            result = 0;
            for (unsigned i = 0; i < kGlideCount; ++i)
                if (name == kGlide[i].name)
                    result = g_lookupFails && i <= kQueryBoards && r % 14 == 0 ? 0 : kGlideStub + 0x10 * i;
            break;
        }
        case 0xa90390: case 0xa90364: case 0xa9035c: case 0xa90358: case 0xa90404:
            result = 1;
            break;
        case 0xa90368:  // CreateEventA
            result = r % 10 != 0 ? 0x5000 + (r >> 8) % 0x100 : 0;
            break;
        case 0xa90438:  // WaitForSingleObject
            result = 0;
            break;
        case 0xa90448:  // DirectDrawCreate
            if (r % 5 != 0)
            {
                word(words[1]) = kDirectDraw;
                result = 0;
            }
            else
            {
                result = 0x80004005;
            }
            break;
        case 0xa9042c:  // VirtualAlloc: the lowest slot free
        {
            result = 0;
            if (r % 25 != 0 && words[1] <= kSlotSize)
                for (x86::reg32 slot = 0; slot < (kHeapEnd - kHeap) / kSlotSize; ++slot)
                    if (!(word(kSlotMap) & (1u << slot)))
                    {
                        word(kSlotMap) |= 1u << slot;
                        result = kHeap + slot * kSlotSize;
                        break;
                    }
            break;
        }
        case 0xa90430:  // VirtualFree
            result = 0;
            if (r % 25 != 0 && words[0] >= kHeap && words[0] < kHeapEnd)
            {
                word(kSlotMap) &= ~(1u << ((words[0] - kHeap) / kSlotSize));
                result = 1;
            }
            break;
        case kFindWindow:
            result = r % 8 != 0 ? 0x9000 + r % 0x100 : 0;
            break;
        case kSetCooperativeLevel:
            result = r % 5 != 0 ? 0 : 0x80004005;
            break;
        default:
            break;
        }
        cpu.eax = result;
        cpu.ecx = 0x33333333;
        cpu.edx = 0x44444444;
        cpu.esp = esp + 4 + 4 * count;
    }
};

CheckApp* g_running = nullptr;  // whose run the host's Glide calls belong to

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
    if (address >= kGlideStub && address < kGlideStub + 0x10 * kGlideCount && (address & 0xf) == 0)
    {
        app->glideStub((address - kGlideStub) / 0x10, cpu);
        return;
    }
    for (const Import& import : kImports)
        if (address == kImportStub + (import.slot & 0xfff))
        {
            app->outside(import.slot, import.arguments, cpu);
            return;
        }
    switch (address)
    {
    case kFindWindow: app->outside(address, 0, cpu); return;
    case kExecute: app->outside(address, 2, cpu); return;
    case kLockHook: app->outside(address, 1, cpu); return;
    case kGameTriangle: app->outside(address, 3, cpu); return;
    case kGameLine: app->outside(address, 2, cpu); return;
    case kSetCooperativeLevel: app->outside(address, 3, cpu); return;
    case kRelease: app->outside(address, 1, cpu); return;
    default: break;
    }
    if (const Generated generated = generatedAt(address))
    {
        if (!app->generated)
            app->reachedGenerated = true;
        generated(this, cpu);
        return;
    }
    std::printf("a call to %08x, no stand-in there (%s, %zu calls)\n", unsigned(address),
                app->generated ? "generated" : "native", app->calls.size());
    for (const Call& c : app->calls)
        std::printf("  %08x %zu\n", c.id, c.words.size());
    std::exit(2);
}

void MemMap::usedRanges(std::vector<std::pair<x86::reg32, x86::reg32>>& ranges)
{
    ranges.assign(1, {0, kMemory});
}

void ThrashRenderer::finishTriangle(ThrashVertex*)
{
    std::abort();  // thrashRenderer() is null here
}

void ThrashRenderer::renderPending()
{
    std::abort();
}

namespace glide2x
{

namespace
{

std::vector<x86::reg32> vertexWords(const GrVertex* v)
{
    const float fields[] = {v->x, v->y, v->r, v->g, v->b, v->ooz, v->a, v->oow, v->tmuvtx[0].sow, v->tmuvtx[0].tow};
    std::vector<x86::reg32> words;
    for (const float f : fields)
    {
        x86::reg32 bits;
        std::memcpy(&bits, &f, sizeof bits);
        words.push_back(bits);
    }
    return words;
}

x86::reg32 bitsOf(float f)
{
    x86::reg32 bits;
    std::memcpy(&bits, &f, sizeof bits);
    return bits;
}

x86::reg32 call(unsigned i, std::vector<x86::reg32> words, x86::reg32 out = 0)
{
    return g_running->glide(i, std::move(words), out);
}

}

void drawTriangle(const GrVertex* a, const GrVertex* b, const GrVertex* c)
{
    std::vector<x86::reg32> words = vertexWords(a);
    for (const GrVertex* v : {b, c})
    {
        const std::vector<x86::reg32> more = vertexWords(v);
        words.insert(words.end(), more.begin(), more.end());
    }
    call(kDrawTriangle, words);
}

void drawLine(const GrVertex* a, const GrVertex* b)
{
    std::vector<x86::reg32> words = vertexWords(a);
    const std::vector<x86::reg32> more = vertexWords(b);
    words.insert(words.end(), more.begin(), more.end());
    call(kDrawLine, words);
}

bool fullColourTextures() { return false; }

namespace direct
{
void chromakeyValue(WinApplication*, x86::CPU&, x86::reg32 color) { call(8, {color}); }
void colorCombine(WinApplication*, x86::CPU&, x86::reg32 function, x86::reg32 factor, x86::reg32 local,
                  x86::reg32 other, x86::reg32 invert)
{
    call(19, {function, factor, local, other, invert});
}
void alphaCombine(WinApplication*, x86::CPU&, x86::reg32 function, x86::reg32 factor, x86::reg32 local,
                  x86::reg32 other, x86::reg32 invert)
{
    call(20, {function, factor, local, other, invert});
}
void alphaBlendFunction(WinApplication*, x86::CPU&, x86::reg32 a, x86::reg32 b, x86::reg32 c, x86::reg32 d)
{
    call(21, {a, b, c, d});
}
void cullMode(WinApplication*, x86::CPU&, x86::reg32 mode) { call(22, {mode}); }
void texFilterMode(WinApplication*, x86::CPU&, x86::reg32 tmu, x86::reg32 a, x86::reg32 b) { call(23, {tmu, a, b}); }
void ditherMode(WinApplication*, x86::CPU&, x86::reg32 mode) { call(24, {mode}); }
void chromakeyMode(WinApplication*, x86::CPU&, x86::reg32 mode) { call(25, {mode}); }
void alphaTestFunction(WinApplication*, x86::CPU&, x86::reg32 function) { call(26, {function}); }
void depthBufferMode(WinApplication*, x86::CPU&, x86::reg32 mode) { call(27, {mode}); }
void depthBufferFunction(WinApplication*, x86::CPU&, x86::reg32 function) { call(28, {function}); }
void depthMask(WinApplication*, x86::CPU&, x86::reg32 mask) { call(29, {mask}); }
void fogColorValue(WinApplication*, x86::CPU&, x86::reg32 colour) { call(30, {colour}); }
void fogMode(WinApplication*, x86::CPU&, x86::reg32 mode) { call(31, {mode}); }
void fogTable(WinApplication*, x86::CPU&, const x86::reg8* table)
{
    std::vector<x86::reg32> words(16);
    std::memcpy(words.data(), table, 64);
    call(32, words);
}
void gammaCorrectionValue(WinApplication*, x86::CPU&, float gamma) { call(40, {bitsOf(gamma)}); }
void depthBiasLevel(WinApplication*, x86::CPU&, x86::sreg16 bias) { call(41, {x86::reg32(x86::sreg32(bias))}); }
void texMipMapMode(WinApplication*, x86::CPU&, x86::reg32 tmu, x86::reg32 mode, x86::reg32 blend)
{
    call(42, {tmu, mode, blend});
}
void texCombine(WinApplication*, x86::CPU&, x86::reg32 tmu, x86::reg32 a, x86::reg32 b, x86::reg32 c, x86::reg32 d,
                x86::reg32 e, x86::reg32 f)
{
    call(43, {tmu, a, b, c, d, e, f});
}
void texClampMode(WinApplication*, x86::CPU&, x86::reg32 tmu, x86::reg32 s, x86::reg32 t) { call(49, {tmu, s, t}); }
void texLodBiasValue(WinApplication*, x86::CPU&, x86::reg32 tmu, float bias) { call(54, {tmu, bitsOf(bias)}); }
x86::reg32 texCalcMemRequired(WinApplication*, x86::CPU&, x86::reg32 a, x86::reg32 b, x86::reg32 c, x86::reg32 d)
{
    return call(44, {a, b, c, d});
}
x86::reg32 texMinAddress(WinApplication*, x86::CPU&, x86::reg32 tmu) { return call(46, {tmu}); }
x86::reg32 texMaxAddress(WinApplication*, x86::CPU&, x86::reg32 tmu) { return call(47, {tmu}); }
void texSource(WinApplication*, x86::CPU&, x86::reg32 tmu, x86::reg32 start, x86::reg32 evenOdd, x86::reg32 info)
{
    call(48, {tmu, start, evenOdd, info});
}
void texDownloadMipMap(WinApplication*, x86::CPU&, x86::reg32 tmu, x86::reg32 start, x86::reg32 evenOdd,
                       x86::reg32 info)
{
    call(45, {tmu, start, evenOdd, info});
}
void texDownloadTable(WinApplication*, x86::CPU&, x86::reg32 tmu, x86::reg32 type, x86::reg32 data)
{
    call(10, {tmu, type, data});
}
void renderBuffer(WinApplication*, x86::CPU&, x86::reg32 buffer) { call(11, {buffer}); }
void bufferClear(WinApplication*, x86::CPU&, x86::reg32 colour, x86::reg8 alpha, x86::reg16 depth)
{
    call(12, {colour, alpha, depth});
}
void bufferSwap(WinApplication*, x86::CPU&, x86::reg32 interval) { call(13, {interval}); }
x86::sreg32 bufferNumPending(WinApplication*, x86::CPU&) { return x86::sreg32(call(kPending, {})); }
x86::reg32 sstStatus(WinApplication*, x86::CPU&) { return call(kStatus, {}); }
x86::reg32 sstVRetraceOn(WinApplication*, x86::CPU&) { return call(kRetraceOn, {}); }
void sstIdle(WinApplication*, x86::CPU&) { call(16, {}); }
void sstIsBusy(WinApplication*, x86::CPU&) { call(17, {}); }
void clipWindow(WinApplication*, x86::CPU&, x86::reg32 a, x86::reg32 b, x86::reg32 c, x86::reg32 d)
{
    call(18, {a, b, c, d});
}
x86::reg32 lfbLock(WinApplication*, x86::CPU&, x86::reg32 type, x86::reg32 buffer, x86::reg32 writeMode,
                   x86::reg32 origin, x86::reg32 pipeline, x86::reg32 info)
{
    return call(kLfbLock, {type, buffer, writeMode, origin, pipeline}, info);
}
x86::reg32 lfbUnlock(WinApplication*, x86::CPU&, x86::reg32 type, x86::reg32 buffer)
{
    return call(kLfbUnlock, {type, buffer});
}
x86::reg32 lfbReadRegion(WinApplication*, x86::CPU&, x86::reg32 buffer, x86::reg32 x, x86::reg32 y, x86::reg32 width,
                         x86::reg32 height, x86::reg32 stride, x86::reg32 data)
{
    return call(kLfbRead, {buffer, x, y, width, height, stride, data});
}
void resetTextures() {}
ThrashRenderer* thrashRenderer() { return nullptr; }
x86::reg32 sstControl(WinApplication*, x86::CPU&, x86::reg32 code) { return call(kControl, {code}); }
}

}

}

namespace
{

using win32::CheckApp;

enum Kind
{
    kDraw, kState, kTextures, kFrame, kSetup, kHeapOps,
};

struct Export
{
    const char* name;
    x86::reg32 address;  // voodoo2a's function
    void (*native)(win32::WinApplication*, x86::CPU&);
    x86::reg32 argumentBytes;
    bool result;          // eax is one
    Kind kind;
};

const Export kExports[] = {
    {"THRASH_drawtri", 0xa85770, &nfs3hp::THRASH_drawtri, 0xc, false, kDraw},
    {"THRASH_drawquad", 0xa85300, &nfs3hp::THRASH_drawquad, 0x10, false, kDraw},
    {"THRASH_drawquadmesh", 0xa85520, &nfs3hp::THRASH_drawquadmesh, 0xc, false, kDraw},
    {"THRASH_drawtrimesh", 0xa85900, &nfs3hp::THRASH_drawtrimesh, 0xc, false, kDraw},
    {"THRASH_drawtrifan", 0xa86000, &nfs3hp::THRASH_drawtrifan, 8, false, kDraw},
    {"THRASH_drawtristrip", 0xa85ac0, &nfs3hp::THRASH_drawtristrip, 8, false, kDraw},
    {"THRASH_drawline", 0xa86240, &nfs3hp::THRASH_drawline, 8, false, kDraw},
    {"THRASH_drawlinemesh", 0xa86350, &nfs3hp::THRASH_drawlinemesh, 0xc, false, kDraw},
    {"THRASH_drawlinestrip", 0xa86490, &nfs3hp::THRASH_drawlinestrip, 8, false, kDraw},
    {"THRASH_drawpoint", 0xa86650, &nfs3hp::THRASH_drawpoint, 4, false, kDraw},
    {"THRASH_drawpointmesh", 0xa866e0, &nfs3hp::THRASH_drawpointmesh, 0xc, false, kDraw},
    {"THRASH_drawpointstrip", 0xa86790, &nfs3hp::THRASH_drawpointstrip, 8, false, kDraw},
    {"THRASH_setstate", 0xa84990, &nfs3hp::THRASH_setstate, 8, true, kState},
    {"THRASH_talloc", 0xa844b0, &nfs3hp::THRASH_talloc, 0x14, true, kTextures},
    {"THRASH_tupdate", 0xa84630, &nfs3hp::THRASH_tupdate, 0xc, true, kTextures},
    {"THRASH_treset", 0xa84690, &nfs3hp::THRASH_treset, 0, true, kTextures},
    {"THRASH_settexture", 0xa846d0, &nfs3hp::THRASH_settexture, 4, true, kTextures},
    {"THRASH_window", 0xa84780, &nfs3hp::THRASH_window, 4, true, kFrame},
    {"THRASH_clearwindow", 0xa847b0, &nfs3hp::THRASH_clearwindow, 0, true, kFrame},
    {"THRASH_flushwindow", 0xa847d0, &nfs3hp::THRASH_flushwindow, 0, true, kFrame},
    {"THRASH_pageflip", 0xa847e0, &nfs3hp::THRASH_pageflip, 0, false, kFrame},
    {"THRASH_idle", 0xa84810, &nfs3hp::THRASH_idle, 0, true, kFrame},
    {"THRASH_sync", 0xa84830, &nfs3hp::THRASH_sync, 4, true, kFrame},
    {"THRASH_clip", 0xa848b0, &nfs3hp::THRASH_clip, 0x10, true, kFrame},
    {"THRASH_lockwindow", 0xa850f0, &nfs3hp::THRASH_lockwindow, 0, true, kFrame},
    {"THRASH_unlockwindow", 0xa851d0, &nfs3hp::THRASH_unlockwindow, 4, true, kFrame},
    {"THRASH_readrect", 0xa85220, &nfs3hp::THRASH_readrect, 0x14, true, kFrame},
    {"THRASH_writerect", 0xa85290, &nfs3hp::THRASH_writerect, 0x14, true, kFrame},
    {"THRASH_about", 0xa83c60, &nfs3hp::THRASH_about, 0, true, kSetup},
    {"THRASH_init", 0xa83f50, &nfs3hp::THRASH_init, 0, true, kSetup},
    {"THRASH_is", 0xa83df0, &nfs3hp::THRASH_is, 0, true, kSetup},
    {"THRASH_selectdisplay", 0xa83f10, &nfs3hp::THRASH_selectdisplay, 4, true, kSetup},
    {"THRASH_setvideomode", 0xa843d0, &nfs3hp::THRASH_setvideomode, 0xc, true, kSetup},
    {"THRASH_restore", 0xa84100, &nfs3hp::THRASH_restore, 0, true, kSetup},
    {"THRASH_modemessage", 0xa84360, &nfs3hp::THRASH_modemessage, 0x18, true, kSetup},
    {"malloc/free", 0, nullptr, 0, true, kHeapOps},
};

std::mt19937 g_random(1998);

x86::reg32 random32()
{
    return x86::reg32(g_random());
}

x86::reg32 below(x86::reg32 n)
{
    return x86::reg32(g_random() % n);
}

bool chance(int percent)
{
    return int(g_random() % 100) < percent;
}

x86::reg32 bitsOf(float f)
{
    x86::reg32 bits;
    std::memcpy(&bits, &f, sizeof bits);
    return bits;
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

x86::reg8* bytes(win32::WinApplication& app, x86::reg32 at)
{
    return &app.getMemory<x86::reg8>(at);
}

struct Counts
{
    unsigned cases = 0, stopped = 0, failed = 0;
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

const std::pair<x86::reg32, x86::reg32> kWindows[] = {
    {kImage, kImageEnd}, {kGame, kGameEnd}, {kHeap, kHeapEnd}, {kStackLow, kStackHigh},
};

void copyWindows(win32::WinApplication& to, win32::WinApplication& from)
{
    for (const auto& w : kWindows)
        std::memcpy(bytes(to, w.first), bytes(from, w.first), w.second - w.first);
}

/* What the game's code keeps of voodoo2a's records, from what the generated
 * runs gave it: the lock records THRASH_lockwindow made. */
std::vector<x86::reg32> g_locks;
std::vector<x86::reg32> g_allocations;  // malloc/free's own

/* drawPointers, as THRASH_setstate 9 and 0xb leave them. */
void pointDrawing(CheckApp& g)
{
    const bool twoPass = chance(40), antialiased = chance(40);
    x86::reg32 triangle = kGlideStub + 0x10 * kDrawTriangle, line = kGlideStub + 0x10 * kDrawLine, quad = triangle;
    if (antialiased)
    {
        quad = 0xa83a60;
        triangle = 0xa83a40;
        line = kGlideStub + 0x10 * 52;  // grAADrawLine
    }
    x86::reg32 lineDraw = line;
    g.word(0xa93710) = twoPass ? 0xa83930 : triangle;
    g.word(0xa9370c) = twoPass ? 0xa839b0 : quad;
    if (twoPass)
        lineDraw = 0xa83a30;
    g.word(0xa93610) = lineDraw;
    g.word(0xa93708) = triangle;
    g.word(0xa93704) = line;
    g.word(0xa93700) = quad;
    // Now and then a pointer the game set itself.
    for (const x86::reg32 slot : {0xa93710u, 0xa9370cu, 0xa93708u, 0xa93700u})
        if (chance(3))
            g.word(slot) = kGameTriangle;
    if (chance(3))
        g.word(0xa93610) = kGameLine;
    g.word(0xa91f20) = antialiased ? 1 : 0;
    g.word(0xa91f24) = twoPass ? 1 : 0;
}

/* voodoo2a's variables made up afresh, every one a case can reach, in ways
 * that keep its pointers pointing where they may. */
void makeState(CheckApp& g, const Export& e)
{
    // Glide's table as voodoo2a's loading leaves it; its imports at the stand-ins.
    for (unsigned i = 0; i < kGlideCount; ++i)
        g.word(kGlideTable + 4 * i) = kGlideStub + 0x10 * i;
    for (x86::reg32 slot = 0xa90350; slot < 0xa9044c; slot += 4)
        g.word(slot) = 0xe1ff00;  // nothing there
    for (const Import& import : kImports)
        g.word(import.slot) = kImportStub + (import.slot & 0xfff);
    g.word(0xa93ea4) = 0;  // the environment, never set up on the port
    g.word(0xa9235c) = bitsOf(anyFloat());
    g.word(0xa92358) = bitsOf(anyFloat());
    if (chance(20))
        for (x86::reg32 i = 0; i < 256; ++i)
            g.word(0xa93210 + 4 * i) = chance(80) ? bitsOf(float(i)) : bitsOf(anyFloat());
    pointDrawing(g);
    g.word(0xa92354) = below(3);
    g.word(0xa91f2c) = below(2);
    g.word(0xa91f04) = below(3);
    g.word(0xa91efc) = random32();
    g.word(0xa91f00) = random32();
    g.word(0xa91f0c) = below(4);
    g.word(0xa91f18) = 512 + below(4) * 128;
    g.word(0xa91f1c) = 384 + below(4) * 96;
    g.word(0xa91f30) = chance(50) ? kFindWindow : 0;
    g.word(0xa91f3c) = chance(50) ? kExecute : 0;
    g.word(0xa91f38) = chance(50) ? kLockHook : 0;
    g.word(0xa91f34) = chance(50) ? kLog : 0;
    g.word(0xa91f08) = chance(80) ? 0x9000 + below(0x100) : 0;
    g.word(0xa91f40) = chance(80) ? 0x5000 + below(0x100) : 0;
    g.word(0xa91f44) = below(2);
    g.word(0xa91f48) = chance(30) ? kDirectDraw : 0;
    g.word(0xa91ef8) = below(2);
    g.word(0xa91f10) = below(2);
    g.word(0xa92334) = below(2);
    g.word(0xa91f14) = random32();
    g.word(0xa91f50) = chance(50) ? kGlideModule : 0;
    g.word(0xa91ef4) = chance(70) ? below(4) : random32();
    g.word(0xa91f54) = chance(50) ? 0 : 0x33444658;
    g.word(0xa93714) = chance(10) ? 0xffffffff : below(3);
    g.word(0xa93718) = below(3);
    g.word(0xa9371c) = 1 + below(8);
    g.word(0xa93720) = chance(50) ? 0 : chance(50) ? 0x100 : 0x1000;
    g.word(0xa93728) = below(2);
    g.word(0xa93840) = below(0x24);
    static const x86::reg32 widths[] = {512, 640, 800, 960, 1024, 1280};
    for (x86::reg32 mode = 0; mode < 17; ++mode)
    {
        const x86::reg32 entry = 0xa92018 + mode * 0x28;
        g.word(entry) = widths[below(6)];
        g.word(entry + 4) = g.word(entry) * 3 / 4;
        g.word(entry + 8) = chance(80) ? 16 : 32;
        g.word(entry + 0x10) = below(3);
        g.word(0xa922e8 + mode * 4) = below(16);
    }
    g_texMin = chance(50) ? 0 : 0x200000 * below(3);
    g_texMax = g_texMin + 0x200000 * (1 + below(2)) - 8 * below(4);
    if (e.kind == kTextures || chance(5))
        g.word(0xa937a8) = g_texMin + below(g_texMax - g_texMin + 0x100);
    // The heap may not grow, now and then, or by other steps.
    g.word(0xa92830) = chance(97) ? 1 : 0;
    g.word(0xa9273c) = chance(97) ? 0 : 0xfffffffe;
    g.word(0xa92834) = chance(90) ? 0x10000 : chance(50) ? 0x1000 : 0x20001;
}

void makeGame(CheckApp& g)
{
    for (x86::reg32 i = 0; i < kVertexCount; ++i)
    {
        const x86::reg32 v = kVertices + i * 0x20;
        for (const x86::reg32 offset : {0u, 4u, 8u, 0xcu, 0x18u, 0x1cu})
            g.word(v + offset) = bitsOf(anyFloat());
        g.word(v + 0x10) = random32();
        g.word(v + 0x14) = random32();
    }
    for (x86::reg32 i = 0; i < 4096; ++i)
        g.word(kIndices + 4 * i) = below(kVertexCount);
    for (x86::reg32 i = 0; i < 16; ++i)
        for (x86::reg32 j = 0; j < 0x20; j += 4)
            g.word(kRecords + 0x20 * i + j) = j == 0x1c ? 0 : random32();
    g.word(kLambdaRecord + 4) = kFindWindow;
    g.word(kLambdaRecord + 8) = kExecute;
    g.word(kLambdaRecord + 0x14) = kLockHook;
    g.word(kLambdaRecord + 0x18) = kLog;
    for (x86::reg32 j = 0; j < 64; j += 4)
        g.word(kFogBytes + j) = random32();
    g.word(kDirectDraw) = kDirectDrawVtable;
    g.word(kDirectDrawVtable + 8) = kRelease;
    g.word(kDirectDrawVtable + 0x50) = kSetCooperativeLevel;
    g.word(kResult) = random32();
}

/* A vertex pointer, or the first of `count` in a row. */
x86::reg32 vertex(x86::reg32 count = 1)
{
    return kVertices + 0x20 * below(kVertexCount - count + 1);
}

x86::sreg32 anyCount(x86::reg32 most)
{
    return chance(5) ? -x86::sreg32(below(3)) : x86::sreg32(below(most + 1));
}

/* The arguments of a case, as the game would push them. */
void makeArguments(CheckApp& g, const Export& e, x86::reg32 (&a)[8])
{
    for (x86::reg32& word : a)
        word = random32();
    const std::string name = e.name;
    if (name == "THRASH_drawtri")
    {
        a[0] = vertex(); a[1] = vertex(); a[2] = vertex();
    }
    else if (name == "THRASH_drawquad")
    {
        a[0] = vertex(); a[1] = vertex(); a[2] = vertex(); a[3] = vertex();
    }
    else if (name == "THRASH_drawline")
    {
        a[0] = vertex(); a[1] = vertex();
    }
    else if (name == "THRASH_drawpoint")
    {
        a[0] = vertex();
    }
    else if (name == "THRASH_drawtrimesh" || name == "THRASH_drawquadmesh" || name == "THRASH_drawlinemesh"
             || name == "THRASH_drawpointmesh")
    {
        a[0] = x86::reg32(anyCount(60));
        a[1] = kVertices;
        a[2] = kIndices + 4 * below(1000);
    }
    else if (name == "THRASH_drawtrifan" || name == "THRASH_drawtristrip" || name == "THRASH_drawlinestrip"
             || name == "THRASH_drawpointstrip")
    {
        const x86::sreg32 count = anyCount(60);
        a[0] = x86::reg32(count);
        a[1] = vertex(x86::reg32(std::max(count, 0)) + 2);
    }
    else if (name == "THRASH_setstate")
    {
        static const x86::reg32 states[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf, 0x12, 0x13,
                                            0x15, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a,
                                            0x6b, 0x6c};
        a[0] = chance(95) ? states[below(sizeof states / sizeof states[0])] : below(0x80);
        a[1] = chance(70) ? below(5) : random32();
        if (a[0] == 1)
            a[1] = chance(30) ? 0 : kRecords + 0x20 * below(16);
        if (a[0] == 0x13)
            a[1] = chance(30) ? 0 : kLambdaRecord;
        if (a[0] == 0x69)
            a[1] = chance(30) ? 0 : kFogBytes;
        if (a[0] == 0xe && chance(50))
            a[1] = 1 + below(5000);
        if ((a[0] == 8 || a[0] == 0x65) && chance(70))
            a[1] = bitsOf(anyFloat());
    }
    else if (name == "THRASH_talloc")
    {
        a[0] = chance(90) ? 1u << below(9) : below(300);
        a[1] = chance(90) ? 1u << below(9) : below(300);
        a[2] = chance(95) ? below(10) : below(0x100);
        a[4] = below(10);
    }
    else if (name == "THRASH_tupdate" || name == "THRASH_settexture")
    {
        a[0] = kRecords + 0x20 * below(16);
        if (name == "THRASH_settexture" && chance(30))
            a[0] = 0;
        a[1] = chance(30) ? 0 : kPixels + below(0x1000);
        a[2] = chance(50) ? 0 : kPixels + below(0x1000);
    }
    else if (name == "THRASH_window")
    {
        a[0] = below(4);
    }
    else if (name == "THRASH_sync")
    {
        a[0] = below(5);
    }
    else if (name == "THRASH_unlockwindow")
    {
        a[0] = g_locks.empty() || chance(20) ? 0 : g_locks[below(x86::reg32(g_locks.size()))];
    }
    else if (name == "THRASH_readrect" || name == "THRASH_writerect")
    {
        a[0] = below(640); a[1] = below(480); a[2] = below(640); a[3] = below(480);
        a[4] = kPixels;
    }
    else if (name == "THRASH_selectdisplay")
    {
        a[0] = below(4) - 1;
    }
    else if (name == "THRASH_setvideomode")
    {
        a[0] = below(17); a[1] = below(4); a[2] = below(3);
    }
    else if (name == "THRASH_modemessage")
    {
        a[3] = below(17);
        a[4] = below(4) | below(3) << 8;
        a[5] = kResult;
    }
}

/* One case of one export: the state made up on `g`, copied to `n`, then both
 * run and compared. */
bool runCase(const Export& e, CheckApp& g, CheckApp& n, Counts& counts)
{
    ++counts.cases;
    g_seed = mix(random32() | std::uint64_t(random32()) << 32);
    makeState(g, e);
    if (chance(30) || g_case == 0)
        makeGame(g);

    for (x86::reg32 at = kStackLow; at < kStackHigh; at += 4)
        g.word(at) = random32();
    const x86::reg32 esp = kStackHigh - 0x800 - 4 * below(64);
    x86::reg32 arguments[8];
    makeArguments(g, e, arguments);
    for (x86::reg32 i = 0; i < 8; ++i)
        g.word(esp + 4 + 4 * i) = arguments[i];
    g.word(esp) = 0xdead0000;  // the return address

    x86::CPU cpu{};
    cpu.eax = random32();
    cpu.ebx = random32();
    cpu.ecx = random32();
    cpu.edx = random32();
    cpu.esi = random32();
    cpu.edi = random32();
    cpu.ebp = random32();
    cpu.esp = esp;

    g_stopAt = chance(10) ? long(below(12)) : -1;
    // THRASH_about and THRASH_is look before they call; THRASH_init calls.
    g_lookupFails = e.address == 0xa83c60 || e.address == 0xa83df0;

    copyWindows(n, g);
    g.calls.clear();
    n.calls.clear();
    n.reachedGenerated = false;

    x86::CPU nativeCpu = cpu, generatedCpu = cpu;
    x86::reg32 nativeResult = 0, generatedResult = 0;
    if (e.kind == kHeapOps)
    {
        // A malloc or a free, Watcom's register convention: eax in and out.
        const bool allocate = g_allocations.empty() || chance(55);
        x86::reg32 argument;
        if (allocate)
        {
            switch (below(8))
            {
            case 0: argument = below(0x20); break;
            case 1: argument = below(0x30000); break;
            case 2: argument = chance(50) ? 0 : 0xffffffd4 + below(3); break;
            default: argument = 1 + below(0x400); break;
            }
        }
        else
        {
            const x86::reg32 i = below(x86::reg32(g_allocations.size()));
            argument = chance(90) ? g_allocations[i] : chance(50) ? 0 : kGame + 4 * below(100);
            if (argument == g_allocations[i])
                g_allocations.erase(g_allocations.begin() + i);
        }
        win32::g_running = &n;
        nativeResult = allocate ? nfs3hp::thrashMalloc(&n, nativeCpu, argument)
                                : (nfs3hp::thrashFree(&n, nativeCpu, argument), 0);
        win32::g_running = &g;
        generatedCpu.eax = argument;
        generatedCpu.esp -= 4;  // the call
        if (allocate)
            voodoo2a::sub_a86cb0(&g, generatedCpu);
        else
            voodoo2a::sub_a86da0(&g, generatedCpu);
        generatedResult = allocate ? generatedCpu.eax : 0;
        if (allocate && generatedResult != 0 && !generatedCpu.terminate)
            g_allocations.push_back(generatedResult);
        nativeCpu.eax = allocate ? nativeResult : generatedCpu.eax;
    }
    else
    {
        win32::g_running = &n;
        e.native(&n, nativeCpu);
        win32::g_running = &g;
        generatedAt(e.address)(&g, generatedCpu);
        if (e.address == 0xa850f0 && !generatedCpu.terminate && generatedCpu.eax != 0)
            g_locks.push_back(generatedCpu.eax);
        if (e.address == 0xa851d0)
            g_locks.erase(std::remove(g_locks.begin(), g_locks.end(), arguments[0]), g_locks.end());
    }

    char what[400];
    if (n.reachedGenerated)
        return report(counts, "the native called into voodoo2a's generated code");
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
                const Call& a = g.calls[i];
                const Call& b = n.calls[i];
                int at = 0;
                at += std::snprintf(what + at, sizeof what - at, "call %zu: %08x (", i, a.id);
                for (size_t j = 0; j < a.words.size() && j < 8; ++j)
                    at += std::snprintf(what + at, sizeof what - at, " %08x", a.words[j]);
                at += std::snprintf(what + at, sizeof what - at, ") generated, %08x (", b.id);
                for (size_t j = 0; j < b.words.size() && j < 8; ++j)
                    at += std::snprintf(what + at, sizeof what - at, " %08x", b.words[j]);
                std::snprintf(what + at, sizeof what - at, ") native");
                break;
            }
        return report(counts, what);
    }
    if (!stopped)
    {
        const struct { const char* name; x86::reg32 g, n; bool compared; } registers[] = {
            {"eax", generatedCpu.eax, nativeCpu.eax, e.result}, {"esp", generatedCpu.esp, nativeCpu.esp, true},
            {"ebx", generatedCpu.ebx, nativeCpu.ebx, true}, {"esi", generatedCpu.esi, nativeCpu.esi, true},
            {"edi", generatedCpu.edi, nativeCpu.edi, true}, {"ebp", generatedCpu.ebp, nativeCpu.ebp, true},
        };
        for (const auto& r : registers)
            if (r.compared && r.g != r.n)
            {
                std::snprintf(what, sizeof what, "%s %08x generated, %08x native", r.name, r.g, r.n);
                return report(counts, what);
            }
        if (generatedCpu.fpu.count != nativeCpu.fpu.count)
            return report(counts, "the FPU's stack left otherwise");
    }
    for (const auto& w : kWindows)
    {
        const x86::reg32 from = w.first == kStackLow ? esp : w.first;
        const x86::reg32 at = firstDifference(g, n, from, w.second);
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
    CheckApp g(true), n(false);
    for (CheckApp* app : {&g, &n})
    {
        std::memcpy(bytes(*app, 0xa83200), voodoo2a::s_AUTOSegment, 52224);
        std::memcpy(bytes(*app, 0xa90200), voodoo2a::s__idataSegment, 2048);
        std::memcpy(bytes(*app, 0xa91200), voodoo2a::s_DGROUPSegment, 7680);
        std::memcpy(bytes(*app, 0xa95200), voodoo2a::s__edataSegment, 1536);
        std::memcpy(bytes(*app, 0xa97200), voodoo2a::s__rsrcSegment, 1024);
    }
    // The names voodoo2a looks Glide's functions up by, in its table's order.
    for (unsigned i = 0, at = 0xa91210; i < kGlideCount; ++i)
    {
        const std::string name = &g.getMemory<char>(at);
        if (name != kGlide[i].name)
        {
            std::printf("voodoo2a's Glide name %u is %s, not %s\n", i, name.c_str(), kGlide[i].name);
            return 2;
        }
        at = (at + x86::reg32(name.size()) + 4) & ~3u;
    }
    for (const auto& m : kMethods)
        if (m.address < kImage || m.address >= kCodeEnd)
            return 2;

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
        std::printf("%-24s %7u cases, %5u stopped the game -- %u failed\n", e.name, counts.cases, counts.stopped,
                    counts.failed);
        failed = failed || counts.failed != 0;
    }
    std::printf(failed ? "FAILED\n" : "all alike\n");
    return failed ? 1 : 0;
}
