#ifndef NFS3HP_NATIVE_THRASH_H
#define NFS3HP_NATIVE_THRASH_H

#include <x86.h>

namespace win32
{
class WinApplication;
struct GrVertex;
}

namespace nfs3hp
{

/* One of the game's vertices as voodoo2a's THRASH functions hand it to Glide. */
void thrashVertex(win32::WinApplication* app, x86::reg32 in, float zScale, float wScale, win32::GrVertex& out);

/* voodoo2a's exports, native (native_thrash.cpp), and the function its
 * THRASH_setvideomode hands the game's window thread (sub_a84360). */
void THRASH_about(win32::WinApplication* app, x86::CPU& cpu);
void THRASH_clearwindow(win32::WinApplication* app, x86::CPU& cpu);
void THRASH_clip(win32::WinApplication* app, x86::CPU& cpu);
void THRASH_drawline(win32::WinApplication* app, x86::CPU& cpu);
void THRASH_drawlinemesh(win32::WinApplication* app, x86::CPU& cpu);
void THRASH_drawlinestrip(win32::WinApplication* app, x86::CPU& cpu);
void THRASH_drawpoint(win32::WinApplication* app, x86::CPU& cpu);
void THRASH_drawpointmesh(win32::WinApplication* app, x86::CPU& cpu);
void THRASH_drawpointstrip(win32::WinApplication* app, x86::CPU& cpu);
void THRASH_drawquad(win32::WinApplication* app, x86::CPU& cpu);
void THRASH_drawquadmesh(win32::WinApplication* app, x86::CPU& cpu);
void THRASH_drawtri(win32::WinApplication* app, x86::CPU& cpu);
void THRASH_drawtrifan(win32::WinApplication* app, x86::CPU& cpu);
void THRASH_drawtrimesh(win32::WinApplication* app, x86::CPU& cpu);
void THRASH_drawtristrip(win32::WinApplication* app, x86::CPU& cpu);
void THRASH_flushwindow(win32::WinApplication* app, x86::CPU& cpu);
void THRASH_idle(win32::WinApplication* app, x86::CPU& cpu);
void THRASH_init(win32::WinApplication* app, x86::CPU& cpu);
void THRASH_is(win32::WinApplication* app, x86::CPU& cpu);
void THRASH_lockwindow(win32::WinApplication* app, x86::CPU& cpu);
void THRASH_pageflip(win32::WinApplication* app, x86::CPU& cpu);
void THRASH_readrect(win32::WinApplication* app, x86::CPU& cpu);
void THRASH_restore(win32::WinApplication* app, x86::CPU& cpu);
void THRASH_selectdisplay(win32::WinApplication* app, x86::CPU& cpu);
void THRASH_setstate(win32::WinApplication* app, x86::CPU& cpu);
void THRASH_settexture(win32::WinApplication* app, x86::CPU& cpu);
void THRASH_setvideomode(win32::WinApplication* app, x86::CPU& cpu);
void THRASH_sync(win32::WinApplication* app, x86::CPU& cpu);
void THRASH_talloc(win32::WinApplication* app, x86::CPU& cpu);
void THRASH_treset(win32::WinApplication* app, x86::CPU& cpu);
void THRASH_tupdate(win32::WinApplication* app, x86::CPU& cpu);
void THRASH_unlockwindow(win32::WinApplication* app, x86::CPU& cpu);
void THRASH_window(win32::WinApplication* app, x86::CPU& cpu);
void THRASH_writerect(win32::WinApplication* app, x86::CPU& cpu);
void THRASH_modemessage(win32::WinApplication* app, x86::CPU& cpu);

/* voodoo2a's malloc and free (native_watcom_heap.cpp): Watcom's near heap on
 * voodoo2a's variables, growing by VirtualAlloc through its imports.  After a
 * call, cpu.terminate says whether the game stopped in one. */
x86::reg32 thrashMalloc(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 amount);
void thrashFree(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 pointer);

/* Whether the game draws through ThrashRenderer, the native driver's own
 * renderer (NFS_THRASH_GL, on by default), rather than the Voodoo2 emulated
 * over an atlas. */
bool thrashRendererWanted();

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
