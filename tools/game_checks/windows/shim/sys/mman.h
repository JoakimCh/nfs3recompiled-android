/* What game_checks.cpp wants of POSIX's mmap, on Windows: anonymous memory. */
#pragma once
#include <cstddef>
#include <windows.h>
#undef min
#undef max
#define PROT_READ 1
#define PROT_WRITE 2
#define MAP_PRIVATE 2
#define MAP_ANONYMOUS 0x20
#define MAP_FAILED ((void*)-1)
inline void* mmap(void*, size_t length, int, int, int, long)
{
    void* p = VirtualAlloc(nullptr, length, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    return p ? p : MAP_FAILED;
}
inline int munmap(void* p, size_t) { return VirtualFree(p, 0, MEM_RELEASE) ? 0 : -1; }
