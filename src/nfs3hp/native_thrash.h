#ifndef NFS3HP_NATIVE_THRASH_H
#define NFS3HP_NATIVE_THRASH_H

#include <x86.h>

namespace win32
{
class WinApplication;
}

/* What the game's natives share around the THRASH driver (port_thrash.cpp). */
namespace nfs3hp
{

/* voodoo2a's malloc and free (native_watcom_heap.cpp): Watcom's near heap on
 * voodoo2a's variables, growing by VirtualAlloc through its imports -- what
 * the driver's texture and lock records come from.  After a call,
 * cpu.terminate says whether the game stopped in one. */
x86::reg32 thrashMalloc(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 amount);
void thrashFree(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 pointer);

/* From native_vertices.cpp, for the stand-ins of the other files:
 * NFS_NATIVE_CHECK, NFS_NATIVES, and whether one of its checks is running the
 * generated code, when every stand-in steps aside. */
bool nativeChecking();
bool nativesEnabled();
bool nativeOriginalRunning();

/* From native_vertices.cpp, for native_render.cpp: NFS_NATIVE_CHECK's
 * whole-memory check of `native` against the generated function at `address`,
 * once a second, the triangles it hands THRASH compared when `triangles`;
 * `state` (null at first) keeps the function's counts. */
void nativeCheckWhole(win32::WinApplication* app, x86::CPU& cpu, const char* name, x86::reg32 address,
                      void*& state, void (*native)(win32::WinApplication*, x86::CPU&), bool triangles);

}

#endif
