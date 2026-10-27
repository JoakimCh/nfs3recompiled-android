// Guest memories of 4 GB reserved, committed where touched (a vectored
// exception handler), for the render harness.
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>

namespace
{
struct Region
{
    unsigned char* base;
    std::vector<unsigned> transient;  // pages committed on touch
};
Region g_regions[2];
int g_count = 0;
const unsigned long long kSize = 0x100000000ull + 0x10000;
}
void (*g_runaway)(const char*) = nullptr;
namespace
{

LONG CALLBACK handler(EXCEPTION_POINTERS* e)
{
    if (e->ExceptionRecord->ExceptionCode == EXCEPTION_ACCESS_VIOLATION)
    {
        unsigned char* at = reinterpret_cast<unsigned char*>(e->ExceptionRecord->ExceptionInformation[1]);
        for (int i = 0; i < g_count; ++i)
        {
            Region& r = g_regions[i];
            if (at >= r.base && at < r.base + kSize)
            {
                unsigned char* page = r.base + ((at - r.base) & ~0xfffull);
                if (!VirtualAlloc(page, 0x1000, MEM_COMMIT, PAGE_READWRITE))
                    return EXCEPTION_CONTINUE_SEARCH;
                r.transient.push_back(unsigned((page - r.base) >> 12));
                if (r.transient.size() > 60000 && g_runaway)
                    g_runaway("touched too many pages");
                return EXCEPTION_CONTINUE_EXECUTION;
            }
        }
        std::printf("access violation outside the guests at %p\n", at);
        if (g_runaway)
            g_runaway("host access violation");
        std::fflush(stdout);
        ExitProcess(5);
    }
    if (e->ExceptionRecord->ExceptionCode == EXCEPTION_INT_DIVIDE_BY_ZERO
        || e->ExceptionRecord->ExceptionCode == EXCEPTION_INT_OVERFLOW)
    {
        if (g_runaway)
            g_runaway("integer division fault");
        std::fflush(stdout);
        ExitProcess(6);
    }
    if (e->ExceptionRecord->ExceptionCode == EXCEPTION_STACK_OVERFLOW)
    {
        if (g_runaway)
            g_runaway("host stack overflow");
        std::fflush(stdout);
        ExitProcess(7);
    }
    return EXCEPTION_CONTINUE_SEARCH;
}
}

unsigned char* guestReserve()
{
    if (g_count == 0)
        AddVectoredExceptionHandler(1, handler);
    void* p = VirtualAlloc(nullptr, kSize, MEM_RESERVE, PAGE_READWRITE);
    if (!p)
        std::abort();
    g_regions[g_count].base = static_cast<unsigned char*>(p);
    return g_regions[g_count++].base;
}

void guestCommit(unsigned char* base, unsigned from, unsigned to)
{
    if (!VirtualAlloc(base + from, to - from, MEM_COMMIT, PAGE_READWRITE))
        std::abort();
}

static Region& regionOf(unsigned char* base)
{
    for (int i = 0; i < g_count; ++i)
        if (g_regions[i].base == base)
            return g_regions[i];
    std::abort();
}

// The pages committed on touch in either memory since the last drop.
std::vector<unsigned> guestTransient(unsigned char* a, unsigned char* b)
{
    std::vector<unsigned> pages = regionOf(a).transient;
    const std::vector<unsigned>& more = regionOf(b).transient;
    pages.insert(pages.end(), more.begin(), more.end());
    std::sort(pages.begin(), pages.end());
    pages.erase(std::unique(pages.begin(), pages.end()), pages.end());
    return pages;
}

void guestDrop(unsigned char* base)
{
    Region& r = regionOf(base);
    for (unsigned page : r.transient)
        VirtualFree(base + (unsigned long long)page * 0x1000, 0x1000, MEM_DECOMMIT);
    r.transient.clear();
}
