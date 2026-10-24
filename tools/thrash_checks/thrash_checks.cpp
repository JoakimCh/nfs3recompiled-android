/* src/nfs3hp/port_thrash.cpp, the THRASH driver as the port's own, against
 * the driver as it was -- native_thrash.cpp's voodoo2a over the port's Glide,
 * frozen in reference/ -- on the desktop, without the game.
 *
 * Two guest memories, each with voodoo2a's image as the DLL loads, the
 * game's vertices, texels and records, a heap and a stack; under each driver
 * the one ThrashRenderer, its game thread's half (the GL thread's work is
 * dropped, glthread below).  A session sets the driver up -- THRASH_about,
 * THRASH_init, a mode -- makes a run of random calls, the way the game makes
 * them, and ends in THRASH_restore.  Each call goes to both drivers, and then
 * they are compared:
 *
 *   - what the renderer handed the GL thread (ThrashRenderer::Watcher), its
 *     own state after the call (snapshot), and the Renderer under it -- the
 *     window opened, its mode, the frame buffer's locks, the presents -- the
 *     resources made and freed and the guest context let go and taken back,
 *     all in order;
 *   - the calls of the game's own functions the driver was handed (its
 *     lambdas) and of VirtualAlloc and VirtualFree, voodoo2a's heap's, in
 *     order, with their arguments;
 *   - eax where the export gives something back, esp, ebx, esi, edi and ebp;
 *   - the memory the game sees: voodoo2a's data but for what only the old
 *     driver kept (Glide's table, its drawing pointers, its colour table, the
 *     event, DirectDraw's object, its atexit list), the game's area, the heap,
 *     and the stack from the arguments up;
 *   - the triangles traced (NFS_NATIVE_CHECK's), with the port's own features
 *     -- the 4:3 fit, the emblem's narrowing, clearPicture -- switched alike
 *     in both now and then.
 *
 * The game's callbacks and VirtualAlloc may stop the game (cpu.terminate) at a
 * call a session picks; from there on neither driver may do anything.  What
 * the old driver crashed in on the port -- a state set with no window, Glide's
 * pointers cleared by THRASH_is under an open window, a mode set before
 * THRASH_init -- no session does, nor does any hand the driver a window
 * thread to set its mode on (the execute lambda), which the game never does.
 *
 * Built and run on Windows by windows/run.py. */
#include "port_thrash.h"
#include "native_thrash.h"
#include "thrash.h"
#include "reference/glide2x.h"
#include <lib/glthread.h>
#include <lib/library.h>
#include <lib/memmap.h>
#include <lib/renderer.h>
#include <lib/thrashrenderer.h>
#include <SDL3/SDL.h>
#include <algorithm>
#include <cmath>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <random>
#include <string>
#include <vector>
#include <sys/mman.h>

namespace x86
{
void assertLog(const char*, int, const char*) {}
}

/* What the drivers, the renderer and src/lib/cpu.cpp want of SDL. */
extern "C"
{
Uint64 SDLCALL SDL_GetPerformanceCounter(void) { return 0; }
Uint64 SDLCALL SDL_GetPerformanceFrequency(void) { return 1; }
const char* SDLCALL SDL_getenv(const char* name) { return std::getenv(name); }
int SDLCALL SDL_strcmp(const char* a, const char* b) { return std::strcmp(a, b); }
char* SDLCALL SDL_strstr(const char* a, const char* b) { return const_cast<char*>(std::strstr(a, b)); }
void SDLCALL SDL_Log(const char*, ...) {}
void SDLCALL SDL_LogInfo(int, const char*, ...) {}
void SDLCALL SDL_LogError(int, const char*, ...) {}
void SDLCALL SDL_LogWarn(int, const char*, ...) {}
void SDLCALL SDL_LogCritical(int, const char*, ...) {}
void SDLCALL SDL_LockSpinlock(SDL_SpinLock*) {}
void SDLCALL SDL_UnlockSpinlock(SDL_SpinLock*) {}
SDL_FunctionPointer SDLCALL SDL_GL_GetProcAddress(const char*) { return nullptr; }
}

/* The drivers' exports: the reference's and the new one's. */
#define THRASH_EXPORTS(X)                                                                                         \
    X(about) X(clearwindow) X(clip) X(drawline) X(drawlinemesh) X(drawlinestrip) X(drawpoint) X(drawpointmesh)    \
    X(drawpointstrip) X(drawquad) X(drawquadmesh) X(drawtri) X(drawtrifan) X(drawtrimesh) X(drawtristrip)         \
    X(flushwindow) X(idle) X(init) X(is) X(lockwindow) X(pageflip) X(readrect) X(restore) X(selectdisplay)        \
    X(setstate) X(settexture) X(setvideomode) X(sync) X(talloc) X(treset) X(tupdate) X(unlockwindow) X(window)    \
    X(writerect) X(modemessage)
#define DECLARE(name) void THRASH_##name(win32::WinApplication* app, x86::CPU& cpu);
namespace reference
{
THRASH_EXPORTS(DECLARE)
}
namespace nfs3hp
{
THRASH_EXPORTS(DECLARE)
}
#undef DECLARE

namespace
{

using x86::reg32;
namespace driver = nfs3hp::port::driver;

constexpr reg32 kMemory = 0x1000000;

/* Where things are, in both memories. */
constexpr reg32 kImageBase = 0xa82200;                       // voodoo2a's RVA 0
constexpr reg32 kImage = 0xa83200, kImageEnd = 0xa97600;    // voodoo2a as it loads
constexpr reg32 kGame = 0x600000, kGameEnd = 0x6c0000;      // the game's vertices, records, pixels
constexpr reg32 kVertices = 0x600000;                       // 512 of the game's vertices
constexpr reg32 kVertexCount = 512;
constexpr reg32 kIndices = 0x610000;                        // 4096 vertex indices
constexpr reg32 kRecords = 0x620000;                        // 16 texture records of 0x20 bytes
constexpr reg32 kLambdaRecord = 0x621000;                   // THRASH_setstate 0x13's
constexpr reg32 kFogBytes = 0x622000;                       // THRASH_setstate 0x69's
constexpr reg32 kSlotMap = 0x623000;                        // VirtualAlloc's slots in use
constexpr reg32 kPixels = 0x630000, kPixelsEnd = 0x6a0000;  // texels, and what readrect and writerect take
constexpr reg32 kDirectDrawObject = 0x6b0000, kDirectDrawVtable = 0x6b0100;
constexpr reg32 kHeap = 0x100000, kHeapEnd = 0x500000;      // VirtualAlloc's 16 slots
constexpr reg32 kSlotSize = 0x40000;
constexpr reg32 kStackLow = 0xef0000, kStackHigh = 0xf00000;
constexpr reg32 kFrameBuffers = 0x800000;                   // what Renderer::lock hands out

/* What only the old driver kept of voodoo2a's data. */
const std::pair<reg32, reg32> kOldOnly[] = {
    {0xa91f14, 0xa91f18},  // the mode the window's thread opened
    {0xa91f40, 0xa91f44},  // the event the window's thread set
    {0xa91f48, 0xa91f4c},  // DirectDraw's object
    {0xa91f50, 0xa91f54},  // glide2x.dll
    {0xa92334, 0xa92338},  // the window's thread to open the mode
    {0xa93210, 0xa93610},  // a colour byte as Glide's float
    {0xa93610, 0xa93714},  // the line's pointer, Glide's functions, and the drawing's other pointers
    {0xa937bc, 0xa93844},  // atexit's list
};

/* The stand-ins' addresses: what dynamic_call finds nothing at. */
constexpr reg32 kGlideStub = 0xe00000;   // + 0x10 a Glide function the reference looked up
constexpr reg32 kImportStub = 0xe10000;  // + an import's offset in voodoo2a's table
constexpr reg32 kFindWindow = 0xe20000;  // the game's lambdas
constexpr reg32 kLockHook = 0xe20020;
constexpr reg32 kLog = 0xe20030;
constexpr reg32 kSetCooperativeLevel = 0xe20060, kRelease = 0xe20070;  // DirectDraw's object's
constexpr reg32 kGlideModule = 0x7700;   // what LoadLibraryA hands back

/* voodoo2a's imports, by their place in its table. */
struct Import
{
    reg32 slot;
    const char* name;
    reg32 arguments;
};

const Import kImports[] = {
    {0xa903ec, "LoadLibraryA", 1}, {0xa903d8, "GetProcAddress", 2}, {0xa90390, "FreeLibrary", 1},
    {0xa90368, "CreateEventA", 4}, {0xa90364, "CloseHandle", 1}, {0xa9035c, "SetForegroundWindow", 1},
    {0xa90358, "PostMessageA", 4}, {0xa90438, "WaitForSingleObject", 2}, {0xa90404, "SetEvent", 1},
    {0xa90448, "DirectDrawCreate", 3}, {0xa9042c, "VirtualAlloc", 4}, {0xa90430, "VirtualFree", 3},
};
constexpr reg32 kVirtualAlloc = 0xa9042c, kVirtualFree = 0xa90430;

typedef std::vector<reg32> Words;

std::uint64_t mix(std::uint64_t x)
{
    x += 0x9e3779b97f4a7c15ull;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ull;
    x = (x ^ (x >> 27)) * 0x94d049bb133111ebull;
    return x ^ (x >> 31);
}

reg32 bitsOf(float f)
{
    reg32 bits;
    std::memcpy(&bits, &f, sizeof bits);
    return bits;
}

/* The session's seed and the compared call the game stops at, if any. */
std::uint64_t g_seed = 0;
long g_stopAt = -1;
/* The Glide functions the reference looked up, by the stand-in's number. */
std::vector<std::string> g_glideNames;

}  // namespace

namespace win32
{

/* A guest memory of its own, and its own logs. */
class CheckApp : public WinApplication
{
public:
    explicit CheckApp(bool reference) : WinApplication("thrash_checks", 0, {}), reference(reference) {}
    bool reference;
    Words calls;                           // the compared calls out: id, then the arguments, each
    std::vector<Words> events;             // the renderer's and the Renderer's
    ThrashRenderer* renderer = nullptr;    // the one the driver made, while it lives
    reg32 resources = 0;
    bool reachedGlide = false;             // the new driver called a Glide function
    long callCount = 0;

    reg32& word(reg32 address) { return reinterpret_cast<reg32&>(*&getMemory<x86::reg8>(address)); }

    reg32 random(reg32 id) { return reg32(mix(g_seed ^ (std::uint64_t(callCount) << 32) ^ id)); }

    void event(Words e) { events.push_back(std::move(e)); }

    /* A compared call: true when the game stops in it. */
    bool compared(reg32 id, const Words& arguments, x86::CPU& cpu)
    {
        calls.push_back(id);
        calls.push_back(reg32(arguments.size()));
        calls.insert(calls.end(), arguments.begin(), arguments.end());
        if (callCount++ != g_stopAt)
            return false;
        cpu.terminate = true;
        return true;
    }

    void outside(reg32 address, x86::CPU& cpu);
};

CheckApp* g_running = nullptr;  // whose run the watcher's events belong to

void CheckApp::outside(reg32 address, x86::CPU& cpu)
{
    static const bool trace = std::getenv("THRASH_CHECKS_TRACE") != nullptr;
    if (trace)
        std::printf("  %s: %08x\n", reference ? "reference" : "new", unsigned(address));
    const reg32 esp = cpu.esp;
    auto argument = [&](reg32 i) { return word(esp + 4 + 4 * i); };
    auto finish = [&](reg32 result, reg32 count) {
        cpu.eax = result;
        cpu.ecx = 0x33333333;
        cpu.edx = 0x44444444;
        cpu.esp = esp + 4 + 4 * count;
    };
    if (address >= kGlideStub && address < kGlideStub + 0x10 * reg32(g_glideNames.size()) && (address & 0xf) == 0)
    {
        if (!reference)
            reachedGlide = true;
        const std::string& name = g_glideNames[(address - kGlideStub) / 0x10];
        const Library::Symbol symbol = (*glide2x::s_glide2xRegistry)[name];
        if (!symbol.second)
        {
            std::printf("Glide's %s is not in the reference\n", name.c_str());
            std::exit(2);
        }
        if (trace)
            std::printf("    %s\n", name.c_str());
        symbol.second(this, cpu);
        if (trace)
            std::printf("    back\n");
        return;
    }
    for (const Import& import : kImports)
    {
        if (address != kImportStub + (import.slot & 0xfff))
            continue;
        Words words;
        for (reg32 i = 0; i < import.arguments; ++i)
            words.push_back(argument(i));
        reg32 result = 1;
        switch (import.slot)
        {
        case kVirtualAlloc:  // the lowest slot free
        {
            if (compared(import.slot, words, cpu))
                return;
            result = 0;
            if (random(import.slot) % 25 != 0 && words[1] <= kSlotSize)
                for (reg32 slot = 0; slot < (kHeapEnd - kHeap) / kSlotSize; ++slot)
                    if (!(word(kSlotMap) & (1u << slot)))
                    {
                        word(kSlotMap) |= 1u << slot;
                        result = kHeap + slot * kSlotSize;
                        break;
                    }
            break;
        }
        case kVirtualFree:
            if (compared(import.slot, words, cpu))
                return;
            result = 0;
            if (random(import.slot) % 25 != 0 && words[0] >= kHeap && words[0] < kHeapEnd)
            {
                word(kSlotMap) &= ~(1u << ((words[0] - kHeap) / kSlotSize));
                result = 1;
            }
            break;
        // The Win32 the old driver set the card up with, as the port's answered.
        case 0xa903ec:  // LoadLibraryA
            result = kGlideModule;
            break;
        case 0xa903d8:  // GetProcAddress: a stand-in of the reference's Glide
        {
            const std::string name = &getMemory<char>(words[1]);
            const auto at = std::find(g_glideNames.begin(), g_glideNames.end(), name);
            result = kGlideStub + 0x10 * reg32(at - g_glideNames.begin());
            if (at == g_glideNames.end())
                g_glideNames.push_back(name);
            break;
        }
        case 0xa90368:  // CreateEventA
            result = 0x5001;
            break;
        case 0xa90438:  // WaitForSingleObject
            result = 0;
            break;
        case 0xa90448:  // DirectDrawCreate
            word(words[1]) = kDirectDrawObject;
            result = 0;
            break;
        case 0xa90358:  // PostMessageA: no session hands the driver a window thread
            std::printf("the reference posted the window's thread a message\n");
            std::exit(2);
        default:
            break;
        }
        finish(result, import.arguments);
        return;
    }
    switch (address)
    {
    case kFindWindow:
        if (compared(address, {}, cpu))
            return;
        finish(random(address) % 8 != 0 ? 0x9000 + random(address) % 0x100 : 0, 0);
        return;
    case kLockHook:
        if (compared(address, {argument(0)}, cpu))
            return;
        finish(random(address), 1);
        return;
    case kSetCooperativeLevel:
        finish(0, 3);
        return;
    case kRelease:
        finish(0, 1);
        return;
    default:
        break;
    }
    std::printf("a call to %08x, no stand-in there (%s)\n", unsigned(address), reference ? "reference" : "new");
    std::exit(2);
}

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
    static_cast<CheckApp*>(this)->outside(address, cpu);
}

static reg32 kindOf(GenericResource* resource)
{
    return dynamic_cast<ThrashRenderer*>(resource) ? 'T' : dynamic_cast<Renderer*>(resource) ? 'R' : '?';
}

GenericResource* WinApplication::getResource(x86::reg32 resource)
{
    const auto it = m_resources.find(resource);
    return it == m_resources.end() ? nullptr : it->second;
}

x86::reg32 WinApplication::allocateResource(GenericResource* resource)
{
    CheckApp* app = static_cast<CheckApp*>(this);
    const reg32 index = ++app->resources + 0x20000;
    resource->setResourceIndex(index);
    m_resources[index] = resource;
    app->event({'A', kindOf(resource), index});
    if (ThrashRenderer* renderer = dynamic_cast<ThrashRenderer*>(resource))
        app->renderer = renderer;
    return index;
}

void WinApplication::freeResource(x86::reg32 resource)
{
    CheckApp* app = static_cast<CheckApp*>(this);
    const auto it = m_resources.find(resource);
    if (it == m_resources.end())
    {
        app->event({'F', '?', resource});
        return;
    }
    app->event({'F', kindOf(it->second), resource});
    if (it->second == app->renderer)
        app->renderer = nullptr;
    delete it->second;
    m_resources.erase(it);
}

void WinApplication::lockContext(const x86::CPU&) { static_cast<CheckApp*>(this)->event({'l'}); }
void WinApplication::unlockContext(const x86::CPU&) { static_cast<CheckApp*>(this)->event({'u'}); }

GenericResource::GenericResource() : m_resourceIndex(0) {}
GenericResource::~GenericResource() {}
x86::reg32 GenericResource::getResourceIndex() const { return m_resourceIndex; }
void GenericResource::setResourceIndex(x86::reg32 resourceIndex) { m_resourceIndex = resourceIndex; }

void MemMap::usedRanges(std::vector<std::pair<x86::reg32, x86::reg32>>& ranges)
{
    ranges.assign(1, {0, kMemory});
}

/* The Renderer as the drivers see it: the window's mode, the frame buffer's
 * locks and the presents, logged. */
Renderer::Renderer(WinApplication* application, Window* window)
{
    m_application = application;
    m_window = window;
    m_videoMemory = nullptr;
    m_currentBuffer = 0;
    m_width = m_height = m_depth = 0;
    m_lastWindowW = m_lastWindowH = -1;
    m_vpX = m_vpY = 0;
    m_vpW = 640;
    m_vpH = 480;
    m_keyboardShift = 0;
    static_cast<CheckApp*>(application)->event({'r', window != nullptr});
}

Renderer::~Renderer() { static_cast<CheckApp*>(m_application)->event({'~'}); }

void Renderer::setVideoMode(x86::reg32 w, x86::reg32 h, x86::reg32 bpp)
{
    m_currentBuffer = 0;
    m_width = w;
    m_height = h;
    m_depth = bpp;
    static_cast<CheckApp*>(m_application)->event({'M', w, h, bpp});
}

x86::reg32 Renderer::lock(x86::reg32 index)
{
    static_cast<CheckApp*>(m_application)->event({'K', index});
    return kFrameBuffers + (index & 3) * 0x100000;
}

void Renderer::unlock(x86::reg32 index) { static_cast<CheckApp*>(m_application)->event({'k', index}); }
void Renderer::ensureFramePacing() { static_cast<CheckApp*>(m_application)->event({'e'}); }
void Renderer::paceFrame() { static_cast<CheckApp*>(m_application)->event({'p'}); }
void Renderer::present() { static_cast<CheckApp*>(m_application)->event({'P'}); }

/* The GL thread, its work dropped: only the game thread's half of the
 * renderer is checked. */
namespace glthread
{
bool on() { return false; }
void post(Renderer*, std::function<void()>) {}
void finish() {}
void release() {}
unsigned long long presentPosted(int) { return 0; }
void presentDone() {}
}

}  // namespace win32

/* Libraries, for the reference's Glide registry. */
namespace win32
{
static reg32 s_symbolIndex = 0x400500;
x86::reg32 Library::getSymbolIndex() { return s_symbolIndex++; }
Library::Library(const char* name) : m_next(nullptr), m_name(name) {}
Library::~Library() {}
}

namespace
{

using win32::CheckApp;
using win32::g_running;

/* What the renderer hands the GL thread, logged; a draw's vertices given up
 * here, as the dropped GL work would have given them back. */
struct Watch : win32::ThrashRenderer::Watcher
{
    void drawn(const win32::ThrashDraw& d) override
    {
        Words e = {'D', d.vertexCount, d.width, d.height, bitsOf(d.alphaTestRef), d.chromaKeyColor,
                   bitsOf(d.fogColor[0]), bitsOf(d.fogColor[1]), bitsOf(d.fogColor[2])};
        for (reg32 i = 0; i < d.vertexCount; ++i)
        {
            reg32 words[sizeof(win32::ThrashVertex) / 4];
            std::memcpy(words, &d.vertices[i], sizeof words);
            e.insert(e.end(), words, words + sizeof words / 4);
        }
        e.push_back(reg32(d.batches.size()));
        for (const auto& b : d.batches)
            for (const reg32 w : {b.end, b.texture, b.levels, reg32(b.format), reg32(b.wrapS), reg32(b.wrapT),
                                  reg32(b.zTest), reg32(b.zTestAlways), reg32(b.zBuffer), reg32(b.alphaBlend),
                                  reg32(b.cull), reg32(b.chromaKey), b.cullMode, b.clipMinX, b.clipMinY,
                                  b.clipMaxX, b.clipMaxY, bitsOf(b.gamma), reg32(b.fogTable)})
                e.push_back(w);
        e.push_back(reg32(d.fogTables.size()));
        for (const auto& table : d.fogTables)
            for (const float f : table)
                e.push_back(bitsOf(f));
        g_running->event(std::move(e));
        delete[] d.vertices;
    }
    void uploaded(reg32 index, reg32 size, reg32 levels, win32::TextureFormat format, bool fresh,
                  const std::vector<x86::reg8>& texels) override
    {
        Words e = {'U', index, size, levels, reg32(format), reg32(fresh), reg32(texels.size())};
        for (std::size_t i = 0; i < texels.size(); i += 4)
        {
            reg32 w = 0;
            std::memcpy(&w, texels.data() + i, std::min<std::size_t>(4, texels.size() - i));
            e.push_back(w);
        }
        g_running->event(std::move(e));
    }
    void cleared(reg32 color, reg32 minX, reg32 minY, reg32 maxX, reg32 maxY) override
    {
        g_running->event({'C', color, minX, minY, maxX, maxY});
    }
    void swapped() override { g_running->event({'S'}); }
    void rendered(reg32 buffer) override { g_running->event({'B', buffer}); }
    void released(const std::vector<reg32>& indices) override
    {
        Words e = {'X', reg32(indices.size())};
        e.insert(e.end(), indices.begin(), indices.end());
        g_running->event(std::move(e));
    }
} g_watch;

void observeSwap(win32::WinApplication* app)
{
    static_cast<CheckApp*>(app)->event({'O'});
}

std::mt19937 g_random(1998);

reg32 random32() { return reg32(g_random()); }
reg32 below(reg32 n) { return reg32(g_random() % n); }
bool chance(int percent) { return int(g_random() % 100) < percent; }

/* A float of every kind: ordinary, tiny, huge, denormal, zero, infinite, NaN. */
float anyFloat()
{
    switch (g_random() % 8)
    {
    case 0: { float f; reg32 bits = random32(); std::memcpy(&f, &bits, 4); return f; }
    case 1: return 0.0f;
    case 2: return -0.0f;
    case 3: return std::ldexp(float(int(g_random() % 2001) - 1000), -140);
    case 4: return (g_random() & 1) ? INFINITY : -INFINITY;
    case 5: return std::ldexp(1.0f + float(g_random() % 1000) / 1000.0f, int(g_random() % 250) - 125);
    default: return float(int(g_random() % 20001) - 10000) * 0.37f;
    }
}

/* A float as the game's vertices have them: on the screen, a depth, a 1/w. */
float screenFloat(float most)
{
    return chance(10) ? anyFloat() : float(g_random() % 100000) / 100000.0f * most;
}

x86::reg8* bytes(win32::WinApplication& app, reg32 at) { return &app.getMemory<x86::reg8>(at); }

/* voodoo2a's image as it loads, from the DLL. */
std::vector<x86::reg8> g_image;

bool loadImage(const char* path)
{
    std::FILE* f = std::fopen(path, "rb");
    if (!f)
        return false;
    std::vector<x86::reg8> dll;
    x86::reg8 buffer[65536];
    for (std::size_t n; (n = std::fread(buffer, 1, sizeof buffer, f)) > 0;)
        dll.insert(dll.end(), buffer, buffer + n);
    std::fclose(f);
    auto u16 = [&](std::size_t at) { return reg32(dll[at] | dll[at + 1] << 8); };
    auto u32 = [&](std::size_t at) { return reg32(dll[at] | dll[at + 1] << 8 | dll[at + 2] << 16 | reg32(dll[at + 3]) << 24); };
    const std::size_t pe = u32(0x3c);
    const reg32 sections = u16(pe + 6), optional = u16(pe + 20);
    g_image.assign(kImageEnd - kImage, 0);
    for (reg32 i = 0; i < sections; ++i)
    {
        const std::size_t s = pe + 24 + optional + 40 * i;
        const reg32 va = u32(s + 12), raw = u32(s + 16), offset = u32(s + 20);
        if (offset == 0)
            continue;  // .bss: a size, and nothing in the file
        for (reg32 j = 0; j < raw; ++j)
        {
            const reg32 at = kImageBase + va + j;
            if (at >= kImage && at < kImageEnd && offset + j < dll.size())
                g_image[at - kImage] = dll[offset + j];
        }
    }
    return true;
}

struct Counts
{
    unsigned sessions = 0, calls = 0, stopped = 0, failed = 0;
    std::map<std::string, unsigned> byExport;
};

unsigned g_session = 0;
const char* g_export = "";

bool report(Counts& counts, const std::string& what)
{
    if (++counts.failed <= 20)
        std::printf("  session %u, %s: %s\n", g_session, g_export, what.c_str());
    return false;
}

/* The first byte of [from, to) where the two memories differ, or `to`. */
reg32 firstDifference(CheckApp& a, CheckApp& b, reg32 from, reg32 to)
{
    if (to <= from || std::memcmp(bytes(a, from), bytes(b, from), to - from) == 0)
        return to;
    for (reg32 at = from; at < to; ++at)
        if (*bytes(a, at) != *bytes(b, at))
            return at;
    return to;
}

bool oldOnly(reg32 at)
{
    for (const auto& range : kOldOnly)
        if (at >= range.first && at < range.second)
            return true;
    return false;
}

/* The first byte the game sees where the two differ, or 0. */
reg32 seenDifference(CheckApp& r, CheckApp& n, reg32 esp)
{
    const std::pair<reg32, reg32> windows[] = {{kImage, kImageEnd}, {kGame, kGameEnd}, {kHeap, kHeapEnd}, {esp, kStackHigh}};
    for (const auto& w : windows)
        for (reg32 from = w.first; from < w.second;)
        {
            const reg32 at = firstDifference(r, n, from, w.second);
            if (at == w.second)
                break;
            if (!oldOnly(at))
                return at;
            from = at + 1;
        }
    return 0;
}

std::string describe(const Words& a, const Words& b, const char* what)
{
    std::size_t i = 0;
    while (i < a.size() && i < b.size() && a[i] == b[i])
        ++i;
    char text[300];
    std::snprintf(text, sizeof text, "%s: %zu words reference, %zu new, first difference at %zu (%08x reference, %08x new)",
                  what, a.size(), b.size(), i, i < a.size() ? unsigned(a[i]) : 0u, i < b.size() ? unsigned(b[i]) : 0u);
    return text;
}

std::string describeEvents(const std::vector<Words>& a, const std::vector<Words>& b)
{
    std::size_t i = 0;
    while (i < a.size() && i < b.size() && a[i] == b[i])
        ++i;
    char text[400];
    if (i < a.size() && i < b.size())
        return describe(a[i], b[i], ("renderer event " + std::to_string(i) + " '" + char(a[i][0]) + "'/'"
                                     + char(b[i][0]) + "'").c_str());
    std::snprintf(text, sizeof text, "renderer events: %zu reference, %zu new (the next '%c')", a.size(), b.size(),
                  i < a.size() ? char(a[i][0]) : i < b.size() ? char(b[i][0]) : '-');
    return text;
}

/* ---- A session ---- */

struct Driver
{
    void (*reference)(win32::WinApplication*, x86::CPU&);
    void (*mine)(win32::WinApplication*, x86::CPU&);
    reg32 argumentBytes;
    bool result;
};

#define EXPORT(name, bytes, result) {#name, {&reference::THRASH_##name, &nfs3hp::THRASH_##name, bytes, result}}
const std::map<std::string, Driver> kDrivers = {
    EXPORT(about, 0, true), EXPORT(clearwindow, 0, true), EXPORT(clip, 0x10, true), EXPORT(drawline, 8, false),
    EXPORT(drawlinemesh, 0xc, false), EXPORT(drawlinestrip, 8, false), EXPORT(drawpoint, 4, false),
    EXPORT(drawpointmesh, 0xc, false), EXPORT(drawpointstrip, 8, false), EXPORT(drawquad, 0x10, false),
    EXPORT(drawquadmesh, 0xc, false), EXPORT(drawtri, 0xc, false), EXPORT(drawtrifan, 8, false),
    EXPORT(drawtrimesh, 0xc, false), EXPORT(drawtristrip, 8, false), EXPORT(flushwindow, 0, false),
    EXPORT(idle, 0, false), EXPORT(init, 0, true), EXPORT(is, 0, true), EXPORT(lockwindow, 0, true),
    EXPORT(pageflip, 0, false), EXPORT(readrect, 0x14, true), EXPORT(restore, 0, true),
    EXPORT(selectdisplay, 4, true), EXPORT(setstate, 8, true), EXPORT(settexture, 4, true),
    EXPORT(setvideomode, 0xc, true), EXPORT(sync, 4, true), EXPORT(talloc, 0x14, true), EXPORT(treset, 0, true),
    EXPORT(tupdate, 0xc, true), EXPORT(unlockwindow, 4, true), EXPORT(window, 4, true),
    EXPORT(writerect, 0x14, true), EXPORT(modemessage, 0x18, true),
};
#undef EXPORT

/* What the session knows of the driver: the old one crashes on what it must
 * not be handed. */
struct Session
{
    bool setUp = false, window = false;
    std::vector<reg32> textures;   // THRASH_talloc's records
    std::vector<reg32> locks;      // THRASH_lockwindow's
    std::vector<driver::GrVertex> traceReference, traceMine;
    bool tracing = false;
};

reg32 vertex(reg32 count = 1)
{
    return kVertices + 0x20 * below(kVertexCount - count + 1);
}

int32_t anyCount(reg32 most)
{
    return chance(3) ? -int32_t(below(3)) : int32_t(below(most + 1));
}

/* The arguments of a call, as the game would push them. */
void makeArguments(const std::string& name, Session& s, reg32 (&a)[8])
{
    for (reg32& word : a)
        word = random32();
    if (name == "drawtri")
    {
        a[0] = vertex(); a[1] = vertex(); a[2] = vertex();
    }
    else if (name == "drawquad")
    {
        a[0] = vertex(); a[1] = vertex(); a[2] = vertex(); a[3] = vertex();
    }
    else if (name == "drawline")
    {
        a[0] = vertex(); a[1] = vertex();
    }
    else if (name == "drawpoint")
    {
        a[0] = vertex();
    }
    else if (name == "drawtrimesh" || name == "drawquadmesh" || name == "drawlinemesh" || name == "drawpointmesh")
    {
        a[0] = reg32(anyCount(60));
        a[1] = kVertices;
        a[2] = kIndices + 4 * below(1000);
    }
    else if (name == "drawtrifan" || name == "drawtristrip" || name == "drawlinestrip" || name == "drawpointstrip")
    {
        const int32_t count = anyCount(60);
        a[0] = reg32(count);
        a[1] = vertex(reg32(std::max(count, 0)) + 2);
    }
    else if (name == "setstate")
    {
        static const reg32 states[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf, 0x12, 0x13, 0x15,
                                       0x18, 0x19, 0x1a, 0x1c, 0x1f, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c,
                                       0x2bf, 0x2c2, 0xc9, 0xce};
        a[0] = chance(97) ? states[below(sizeof states / sizeof states[0])] : below(0x80);
        if (a[0] == 0x1b)
            a[0] = 0x1a;  // no execute lambda: no window thread
        a[1] = chance(70) ? below(5) : random32();
        if (a[0] == 1)
            a[1] = chance(30) || s.textures.empty() ? 0 : s.textures[below(reg32(s.textures.size()))];
        if (a[0] == 0x13)
            a[1] = chance(30) ? 0 : kLambdaRecord;
        if (a[0] == 0x1a || a[0] == 0x1c)
            a[1] = chance(50) ? 0 : a[0] == 0x1a ? kLog : kLockHook;
        if (a[0] == 0x69)
            a[1] = chance(30) ? 0 : kFogBytes;
        if (a[0] == 0xe && chance(50))
            a[1] = 1 + below(5000);
        if ((a[0] == 8 || a[0] == 0x65) && chance(70))
            a[1] = bitsOf(anyFloat());
        if (a[0] == 0xb && chance(40))
            a[1] = 3;
    }
    else if (name == "talloc")
    {
        a[0] = chance(95) ? 1u << below(9) : 1 + below(256);
        a[1] = chance(95) ? 1u << below(9) : 1 + below(256);
        a[2] = chance(95) ? below(10) : below(0x20);
        a[4] = below(10);
    }
    else if (name == "tupdate" || name == "settexture")
    {
        a[0] = s.textures.empty() ? 0 : s.textures[below(reg32(s.textures.size()))];
        if (name == "settexture" && chance(30))
            a[0] = 0;
        a[1] = chance(20) ? 0 : kPixels + 4 * below(0x400);
        a[2] = chance(50) ? 0 : kPixels + below(0x1000);
    }
    else if (name == "window")
    {
        a[0] = below(4);
    }
    else if (name == "sync")
    {
        a[0] = below(5);
    }
    else if (name == "unlockwindow")
    {
        a[0] = s.locks.empty() || chance(20) ? 0 : s.locks[below(reg32(s.locks.size()))];
    }
    else if (name == "readrect" || name == "writerect")
    {
        a[0] = below(640); a[1] = below(480); a[2] = below(640); a[3] = below(480);
        a[4] = kPixels;
    }
    else if (name == "selectdisplay")
    {
        a[0] = below(4) - 1;
    }
    else if (name == "setvideomode")
    {
        a[0] = below(17); a[1] = chance(10) ? 0 : 1 + below(3); a[2] = below(3);
    }
    else if (name == "modemessage")
    {
        a[3] = below(17);
        a[4] = below(4) | below(3) << 8;
        a[5] = kGame + 0x10;
    }
}

/* The calls a session may make now. */
std::string pickCall(const Session& s)
{
    static const char* const anytime[] = {"sync", "flushwindow", "idle", "modemessage", "talloc", "treset"};
    static const char* const drawing[] = {
        "drawtri", "drawquad", "drawquadmesh", "drawtrimesh", "drawtrifan", "drawtristrip", "drawline",
        "drawlinemesh", "drawlinestrip", "drawpoint", "drawpointmesh", "drawpointstrip",
    };
    static const char* const windowed[] = {
        "setstate", "setstate", "setstate", "setstate", "talloc", "tupdate", "tupdate", "settexture", "settexture",
        "window", "clearwindow", "pageflip", "clip", "lockwindow", "unlockwindow", "readrect", "writerect", "about",
        "selectdisplay", "init",
    };
    if (!s.setUp)
    {
        static const char* const setup[] = {"about", "is", "init", "init", "restore"};
        return chance(70) ? setup[below(5)] : anytime[below(6)];
    }
    if (!s.window)
    {
        static const char* const ready[] = {"about", "init", "selectdisplay", "setvideomode", "setvideomode", "is"};
        return chance(80) ? ready[below(6)] : anytime[below(6)];
    }
    if (chance(1))
        return "restore";
    if (chance(1))
        return "setvideomode";
    if (chance(45))
        return drawing[below(12)];
    if (chance(85))
    {
        // THRASH_tupdate takes a record the game has, which THRASH_talloc made.
        const std::string picked = windowed[below(sizeof windowed / sizeof windowed[0])];
        return picked == "tupdate" && s.textures.empty() ? "talloc" : picked;
    }
    return anytime[below(6)];
}

/* One call to both drivers, and the two compared.  False when they differ or
 * the game stopped. */
bool runCall(const std::string& name, Session& s, CheckApp& r, CheckApp& n, Counts& counts)
{
    const Driver& d = kDrivers.at(name);
    g_export = name.c_str();
    static const bool trace = std::getenv("THRASH_CHECKS_TRACE") != nullptr;
    if (trace)
        std::printf("session %u call %u: %s\n", g_session, counts.calls, name.c_str());
    ++counts.calls;
    ++counts.byExport[name];

    // Now and then the port's own features, alike in both.
    if (chance(3))
    {
        const bool on = chance(50);
        win32::glide2x::fitFourThree(on);
        driver::fitFourThree(on);
    }
    if (chance(3))
    {
        const bool on = chance(50);
        win32::glide2x::squeezeToLeft(on);
        driver::squeezeToLeft(on);
    }
    if (chance(2))
    {
        s.tracing = !s.tracing;
        win32::glide2x::traceTriangles(s.tracing ? &s.traceReference : nullptr);
        driver::traceTriangles(s.tracing ? &s.traceMine : nullptr);
    }

    // The stack: the same in both, the arguments where the game pushes them.
    const reg32 esp = kStackHigh - 0x800 - 4 * below(64);
    for (reg32 at = kStackLow; at < kStackHigh; at += 4)
        r.word(at) = random32();
    reg32 arguments[8];
    makeArguments(name, s, arguments);
    for (reg32 i = 0; i < 8; ++i)
        r.word(esp + 4 + 4 * i) = arguments[i];
    r.word(esp) = 0xdead0000;
    if (name == "is" && chance(70))
    {
        // What THRASH_is takes for Glide's version: what its frame holds.
        static const char* const versions[] = {"Glide Version 2.43", "2.42", "2.41", "2.5", "2.53", "3.0", "",
                                               "v2.4", "x", "Glide 2.42b", "2.4", "2.50"};
        std::strcpy(&r.getMemory<char>(esp - 0x54), versions[below(sizeof versions / sizeof versions[0])]);
    }
    std::memcpy(bytes(n, kStackLow), bytes(r, kStackLow), kStackHigh - kStackLow);

    x86::CPU cpu{};
    cpu.eax = random32();
    cpu.ebx = random32();
    cpu.ecx = random32();
    cpu.edx = random32();
    cpu.esi = random32();
    cpu.edi = random32();
    cpu.ebp = random32();
    cpu.esp = esp;
    x86::CPU referenceCpu = cpu, mineCpu = cpu;

    r.calls.clear();
    n.calls.clear();
    r.events.clear();
    n.events.clear();
    s.traceReference.clear();
    s.traceMine.clear();
    const long callCount = r.callCount;
    n.callCount = callCount;
    const bool clearing = s.window && chance(2);

    g_running = &r;
    if (clearing)
        win32::glide2x::clearPicture(&r, referenceCpu);
    d.reference(&r, referenceCpu);
    if (trace)
        std::printf("  the reference's done\n");
    g_running = &n;
    if (clearing)
        driver::clearPicture(&n, mineCpu);
    d.mine(&n, mineCpu);
    g_running = nullptr;

    char what[300];
    if (n.reachedGlide)
        return report(counts, "the new driver called a Glide function");
    const bool stopped = referenceCpu.terminate;
    if (referenceCpu.terminate != mineCpu.terminate)
        return report(counts, "stopped in one only");
    if (r.calls != n.calls)
        return report(counts, describe(r.calls, n.calls, "calls out"));
    if (r.events != n.events)
        return report(counts, describeEvents(r.events, n.events));
    if (s.traceReference.size() != s.traceMine.size()
        || std::memcmp(s.traceReference.data(), s.traceMine.data(), s.traceReference.size() * sizeof(driver::GrVertex)) != 0)
    {
        std::snprintf(what, sizeof what, "traced triangles: %zu vertices reference, %zu new", s.traceReference.size(),
                      s.traceMine.size());
        return report(counts, what);
    }
    if ((r.renderer == nullptr) != (n.renderer == nullptr))
        return report(counts, "a renderer in one only");
    if (r.renderer)
    {
        Words a, b;
        r.renderer->snapshot(a);
        n.renderer->snapshot(b);
        if (a != b)
            return report(counts, describe(a, b, "the renderer's state"));
    }
    if (!stopped)
    {
        const struct { const char* name; reg32 r, n; bool compared; } registers[] = {
            {"eax", referenceCpu.eax, mineCpu.eax, d.result}, {"esp", referenceCpu.esp, mineCpu.esp, true},
            {"ebx", referenceCpu.ebx, mineCpu.ebx, true}, {"esi", referenceCpu.esi, mineCpu.esi, true},
            {"edi", referenceCpu.edi, mineCpu.edi, true}, {"ebp", referenceCpu.ebp, mineCpu.ebp, true},
        };
        for (const auto& reg : registers)
            if (reg.compared && reg.r != reg.n)
            {
                std::snprintf(what, sizeof what, "%s %08x reference, %08x new", reg.name, reg.r, reg.n);
                return report(counts, what);
            }
        if (referenceCpu.esp != esp + 4 + d.argumentBytes)
        {
            std::snprintf(what, sizeof what, "esp %08x, not past the arguments", referenceCpu.esp);
            return report(counts, what);
        }
    }
    if (const reg32 at = seenDifference(r, n, esp))
    {
        std::snprintf(what, sizeof what, "memory at %08x: %02x reference, %02x new", at, *bytes(r, at), *bytes(n, at));
        return report(counts, what);
    }
    {
        x86::reg32 rt = 0, rf = 0, rx = 0, nt = 0, nf = 0, nx = 0;
        const bool ra = win32::glide2x::atlasFreeSpace(rt, rf, rx), na = driver::atlasFreeSpace(nt, nf, nx);
        int a[6], b[6];
        const bool rr = win32::glide2x::screenRect(a[0], a[1], a[2], a[3], a[4], a[5]);
        const bool nr = driver::screenRect(b[0], b[1], b[2], b[3], b[4], b[5]);
        if (ra != na || rt != nt || rf != nf || rx != nx || rr != nr || (rr && std::memcmp(a, b, sizeof a) != 0))
            return report(counts, "atlasFreeSpace or screenRect");
    }
    if (stopped)
    {
        ++counts.stopped;
        return false;
    }

    // What the session learns of the driver.
    if (name == "init" && referenceCpu.eax != 0)
        s.setUp = true;
    if (name == "restore")
        s.setUp = s.window = false;
    if (name == "setvideomode")
        s.window = (r.getMemory<x86::reg8>(0xa91ef4) & 2) != 0;
    if (name == "talloc" && referenceCpu.eax != 0)
        s.textures.push_back(referenceCpu.eax);
    if (name == "treset" || name == "setvideomode")
        s.textures.clear();
    if (name == "lockwindow" && referenceCpu.eax != 0)
        s.locks.push_back(referenceCpu.eax);
    if (name == "unlockwindow")
        s.locks.erase(std::remove(s.locks.begin(), s.locks.end(), arguments[0]), s.locks.end());
    return true;
}

/* Both memories as a session starts: voodoo2a as it loads, the game's area
 * made up, the heap empty. */
void startSession(CheckApp& r, CheckApp& n)
{
    std::memset(bytes(r, kGame), 0, kGameEnd - kGame);
    std::memset(bytes(r, kHeap), 0, kHeapEnd - kHeap);
    std::memcpy(bytes(r, kImage), g_image.data(), g_image.size());
    for (reg32 slot = 0xa90350; slot < 0xa9044c; slot += 4)
        r.word(slot) = 0xe1ff00;  // nothing there
    for (const Import& import : kImports)
        r.word(import.slot) = kImportStub + (import.slot & 0xfff);
    if (chance(50))
    {
        // The game layer's widescreen modes (nfs3hp_main.cpp), and Dynamic Fullscreen.
        static const struct { reg32 entry, width, height, resolution; } kWide[] = {
            {12, 1280, 720, driver::kResolution1280x720}, {14, 1600, 900, driver::kResolution1600x900},
            {15, 1920, 1080, driver::kResolution1920x1080}, {16, 1000, 450, driver::kResolutionDynamic},
        };
        for (const auto& wide : kWide)
        {
            const reg32 mode = 0xa92018 + wide.entry * 40;
            r.word(mode) = wide.width;
            r.word(mode + 4) = wide.height;
            r.word(mode + 16) = 1;
            r.word(0xa922e8 + wide.entry * 4) = wide.resolution;
        }
        const reg32 width = 800 + below(800), height = 360 + below(720);
        win32::glide2x::setDynamicResolution(width, height);
        driver::setDynamicResolution(width, height);
    }
    if (chance(10))
        r.word(0xa922e8 + below(17) * 4) = below(0x90);  // a resolution Glide does not know, now and then
    for (reg32 i = 0; i < kVertexCount; ++i)
    {
        const reg32 v = kVertices + i * 0x20;
        const bool wild = chance(15);
        r.word(v) = bitsOf(wild ? anyFloat() : screenFloat(640));
        r.word(v + 4) = bitsOf(wild ? anyFloat() : screenFloat(480));
        r.word(v + 8) = bitsOf(wild ? anyFloat() : screenFloat(1));
        r.word(v + 0xc) = bitsOf(wild ? anyFloat() : screenFloat(1));
        r.word(v + 0x10) = random32();
        r.word(v + 0x14) = random32();
        r.word(v + 0x18) = bitsOf(wild ? anyFloat() : screenFloat(4096));
        r.word(v + 0x1c) = bitsOf(wild ? anyFloat() : screenFloat(4096));
    }
    for (reg32 i = 0; i < 4096; ++i)
        r.word(kIndices + 4 * i) = below(kVertexCount);
    r.word(kLambdaRecord + 4) = chance(50) ? kFindWindow : 0;
    r.word(kLambdaRecord + 8) = 0;  // no window thread
    r.word(kLambdaRecord + 0x14) = chance(50) ? kLockHook : 0;
    r.word(kLambdaRecord + 0x18) = kLog;
    for (reg32 j = 0; j < 64; j += 4)
        r.word(kFogBytes + j) = random32();
    for (reg32 at = kPixels; at < kPixelsEnd; at += 4)
        r.word(at) = random32();
    r.word(kDirectDrawObject) = kDirectDrawVtable;
    r.word(kDirectDrawVtable + 8) = kRelease;
    r.word(kDirectDrawVtable + 0x50) = kSetCooperativeLevel;
    // The heap may not grow, now and then, or by other steps.
    r.word(0xa92830) = chance(97) ? 1 : 0;
    r.word(0xa9273c) = chance(97) ? 0 : 0xfffffffe;
    r.word(0xa92834) = chance(90) ? 0x10000 : chance(50) ? 0x1000 : 0x20001;
    std::memcpy(bytes(n, 0), bytes(r, 0), kMemory);
}

}  // namespace

#include <dbghelp.h>

/* A crash's stack, named, for whoever finds the checks dying. */
static LONG WINAPI crashed(EXCEPTION_POINTERS* e)
{
    HANDLE process = GetCurrentProcess();
    SymInitialize(process, nullptr, TRUE);
    CONTEXT context = *e->ContextRecord;
    STACKFRAME64 frame = {};
    frame.AddrPC.Offset = context.Rip;
    frame.AddrPC.Mode = AddrModeFlat;
    frame.AddrStack.Offset = context.Rsp;
    frame.AddrStack.Mode = AddrModeFlat;
    frame.AddrFrame.Offset = context.Rbp;
    frame.AddrFrame.Mode = AddrModeFlat;
    std::printf("crashed: %08lx at %p\n", e->ExceptionRecord->ExceptionCode, e->ExceptionRecord->ExceptionAddress);
    for (int i = 0; i < 24 && StackWalk64(IMAGE_FILE_MACHINE_AMD64, process, GetCurrentThread(), &frame, &context,
                                          nullptr, SymFunctionTableAccess64, SymGetModuleBase64, nullptr); ++i)
    {
        char buffer[sizeof(SYMBOL_INFO) + 256] = {};
        SYMBOL_INFO* symbol = reinterpret_cast<SYMBOL_INFO*>(buffer);
        symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
        symbol->MaxNameLen = 255;
        DWORD64 displacement = 0;
        IMAGEHLP_LINE64 line = {};
        line.SizeOfStruct = sizeof line;
        DWORD lineDisplacement = 0;
        const bool named = SymFromAddr(process, frame.AddrPC.Offset, &displacement, symbol);
        const bool lined = SymGetLineFromAddr64(process, frame.AddrPC.Offset, &lineDisplacement, &line);
        std::printf("  %s:%lu %s\n", lined ? line.FileName : "?", lined ? line.LineNumber : 0ul,
                    named ? symbol->Name : "?");
    }
    std::exit(3);
}

int main(int argc, char** argv)
{
    SetUnhandledExceptionFilter(crashed);
    std::setvbuf(stdout, nullptr, _IONBF, 0);
    const unsigned sessions = argc > 1 ? unsigned(std::strtoul(argv[1], nullptr, 10)) : 2000;
    const char* dll = argc > 2 ? argv[2] : "nfs3hp/voodoo2a.dll";
    if (!loadImage(dll))
    {
        std::printf("no %s\n", dll);
        return 2;
    }
    CheckApp r(true), n(false);
    win32::ThrashRenderer::watch(&g_watch);
    win32::glide2x::setSwapObserver(observeSwap);
    driver::setSwapObserver(observeSwap);
    Counts counts;
    for (g_session = 0; g_session < sessions; ++g_session)
    {
        ++counts.sessions;
        g_seed = mix(random32() | std::uint64_t(random32()) << 32);
        g_stopAt = chance(20) ? long(below(6)) : -1;
        r.callCount = n.callCount = 0;
        startSession(r, n);
        Session s;
        bool going = true;
        const unsigned length = 10 + below(300);
        for (unsigned i = 0; i < length && going; ++i)
            going = runCall(pickCall(s), s, r, n, counts);
        // The game going on, or not: either way the driver let go, unstopped.
        g_stopAt = -1;
        if (!going)
            std::memcpy(bytes(n, 0), bytes(r, 0), kMemory);
        runCall("restore", s, r, n, counts);
        win32::glide2x::traceTriangles(nullptr);
        driver::traceTriangles(nullptr);
    }
    std::printf("%u sessions, %u calls, %u stopped the game -- %u failed\n", counts.sessions, counts.calls,
                counts.stopped, counts.failed);
    for (const auto& e : counts.byExport)
        std::printf("  %-16s %7u\n", e.first.c_str(), e.second);
    std::printf(counts.failed ? "FAILED\n" : "all alike\n");
    return counts.failed ? 1 : 0;
}
