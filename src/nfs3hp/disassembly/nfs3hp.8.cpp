#include "nfs3hp.h"
#include <lib/thread.h>

namespace nfs3hp
{
// Port (tools/apply_native_frontend.py): defined in native_frontend_options.cpp.
bool audioMenuMusicMoved(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_options.cpp.
bool feedSpeedListKey(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_options.cpp.
bool feedPositionListKey(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_options.cpp.
bool feedTimeListKey(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_options.cpp.
bool feedSpeedButtonKey(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_options.cpp.
bool feedPositionButtonKey(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_options.cpp.
bool feedTimeButtonKey(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_options.cpp.
bool feedSeparate(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_options.cpp.
bool feedOnExit(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_options.cpp.
bool feedOnEnter(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_render.py): defined in native_render.cpp.
bool polygonDrawers(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_render.py): defined in native_render.cpp.
bool colouredTriangles(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_render.py): defined in native_render.cpp.
bool subdivideQuad(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_render.py): defined in native_render.cpp.
bool quadSubdivided(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_render.py): defined in native_render.cpp.
bool quadRecords(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_render.py): defined in native_render.cpp.
bool triangleRecords(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_vertices.py): defined in native_vertices.cpp.
bool quadList(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_vertices.py): defined in native_vertices.cpp.
bool triangleList(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_vertices.py): defined in native_vertices.cpp.
bool submitPolygons(win32::WinApplication* app, x86::CPU& cpu);

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x8d 0x40 0x00 */
void Application::sub_432190(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00432190  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00432191  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00432192  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00432193  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00432194  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00432195  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00432196  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
L_0x00432198:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00432198  8b4810                 -mov ecx, dword ptr [eax + 0x10]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(16) /* 0x10 */);
    // 0043219b  3b480c                 +cmp ecx, dword ptr [eax + 0xc]
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0043219e  0f82ab000000           -jb 0x43224f
    if (cpu.flags.cf)
    {
        goto L_0x0043224f;
    }
    // 004321a4  8b5808                 -mov ebx, dword ptr [eax + 8]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 004321a7  8b5018                 -mov edx, dword ptr [eax + 0x18]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */);
    // 004321aa  8b7014                 -mov esi, dword ptr [eax + 0x14]
    cpu.esi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */);
    // 004321ad  21da                   -and edx, ebx
    cpu.edx &= x86::reg32(x86::sreg32(cpu.ebx));
    // 004321af  01f2                   -add edx, esi
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.esi));
    // 004321b1  c1ea0f                 -shr edx, 0xf
    cpu.edx >>= 15 /*0xf*/ % 32;
    // 004321b4  8d0c12                 -lea ecx, [edx + edx]
    cpu.ecx = x86::reg32(cpu.edx + cpu.edx * 1);
    // 004321b7  8b581c                 -mov ebx, dword ptr [eax + 0x1c]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(28) /* 0x1c */);
    // 004321ba  8b10                   -mov edx, dword ptr [eax]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax);
    // 004321bc  8d3c1e                 -lea edi, [esi + ebx]
    cpu.edi = x86::reg32(cpu.esi + cpu.ebx * 1);
    // 004321bf  8b5818                 -mov ebx, dword ptr [eax + 0x18]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */);
    // 004321c2  0fbf1411               -movsx edx, word ptr [ecx + edx]
    cpu.edx = x86::reg32(static_cast<x86::sreg16>(app->getMemory<x86::reg16>(cpu.ecx + cpu.edx * 1)));
    // 004321c6  8b4820                 -mov ecx, dword ptr [eax + 0x20]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(32) /* 0x20 */);
    // 004321c9  8b35704e5500           -mov esi, dword ptr [0x554e70]
    cpu.esi = app->getMemory<x86::reg32>(x86::reg32(5590640) /* 0x554e70 */);
    // 004321cf  01cb                   -add ebx, ecx
    (cpu.ebx) += x86::reg32(x86::sreg32(cpu.ecx));
    // 004321d1  21d6                   -and esi, edx
    cpu.esi &= x86::reg32(x86::sreg32(cpu.edx));
    // 004321d3  895818                 -mov dword ptr [eax + 0x18], ebx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */) = cpu.ebx;
    // 004321d6  8b1d981f5f00           -mov ebx, dword ptr [0x5f1f98]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(6234008) /* 0x5f1f98 */);
    // 004321dc  897814                 -mov dword ptr [eax + 0x14], edi
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */) = cpu.edi;
    // 004321df  668b3473               -mov si, word ptr [ebx + esi*2]
    cpu.si = app->getMemory<x86::reg16>(cpu.ebx + cpu.esi * 2);
    // 004321e3  8b1d744e5500           -mov ebx, dword ptr [0x554e74]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(5590644) /* 0x554e74 */);
    // 004321e9  8a0d804e5500           -mov cl, byte ptr [0x554e80]
    cpu.cl = app->getMemory<x86::reg8>(x86::reg32(5590656) /* 0x554e80 */);
    // 004321ef  21d3                   -and ebx, edx
    cpu.ebx &= x86::reg32(x86::sreg32(cpu.edx));
    // 004321f1  d3fb                   -sar ebx, cl
    cpu.ebx = x86::reg32(x86::sreg32(cpu.ebx) >> (cpu.cl % 32));
    // 004321f3  8b0da41f5f00           -mov ecx, dword ptr [0x5f1fa4]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(6234020) /* 0x5f1fa4 */);
    // 004321f9  81e6ffff0000           -and esi, 0xffff
    cpu.esi &= x86::reg32(x86::sreg32(65535 /*0xffff*/));
    // 004321ff  668b1c59               -mov bx, word ptr [ecx + ebx*2]
    cpu.bx = app->getMemory<x86::reg16>(cpu.ecx + cpu.ebx * 2);
    // 00432203  8a0d804e5500           -mov cl, byte ptr [0x554e80]
    cpu.cl = app->getMemory<x86::reg8>(x86::reg32(5590656) /* 0x554e80 */);
    // 00432209  81e3ffff0000           -and ebx, 0xffff
    cpu.ebx &= x86::reg32(x86::sreg32(65535 /*0xffff*/));
    // 0043220f  8b3d784e5500           -mov edi, dword ptr [0x554e78]
    cpu.edi = app->getMemory<x86::reg32>(x86::reg32(5590648) /* 0x554e78 */);
    // 00432215  d3e3                   -shl ebx, cl
    cpu.ebx <<= cpu.cl % 32;
    // 00432217  21fa                   -and edx, edi
    cpu.edx &= x86::reg32(x86::sreg32(cpu.edi));
    // 00432219  8a0d844e5500           -mov cl, byte ptr [0x554e84]
    cpu.cl = app->getMemory<x86::reg8>(x86::reg32(5590660) /* 0x554e84 */);
    // 0043221f  d3fa                   -sar edx, cl
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (cpu.cl % 32));
    // 00432221  8d0c12                 -lea ecx, [edx + edx]
    cpu.ecx = x86::reg32(cpu.edx + cpu.edx * 1);
    // 00432224  8b159c1f5f00           -mov edx, dword ptr [0x5f1f9c]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(6234012) /* 0x5f1f9c */);
    // 0043222a  668b1411               -mov dx, word ptr [ecx + edx]
    cpu.dx = app->getMemory<x86::reg16>(cpu.ecx + cpu.edx * 1);
    // 0043222e  8a0d844e5500           -mov cl, byte ptr [0x554e84]
    cpu.cl = app->getMemory<x86::reg8>(x86::reg32(5590660) /* 0x554e84 */);
    // 00432234  81e2ffff0000           -and edx, 0xffff
    cpu.edx &= x86::reg32(x86::sreg32(65535 /*0xffff*/));
    // 0043223a  09f3                   -or ebx, esi
    cpu.ebx |= x86::reg32(x86::sreg32(cpu.esi));
    // 0043223c  d3e2                   -shl edx, cl
    cpu.edx <<= cpu.cl % 32;
    // 0043223e  8b480c                 -mov ecx, dword ptr [eax + 0xc]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
    // 00432241  09da                   -or edx, ebx
    cpu.edx |= x86::reg32(x86::sreg32(cpu.ebx));
    // 00432243  668911                 -mov word ptr [ecx], dx
    app->getMemory<x86::reg16>(cpu.ecx) = cpu.dx;
    // 00432246  83400c02               +add dword ptr [eax + 0xc], 2
    {
        auto tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(2 /*0x2*/));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 0043224a  e949ffffff             -jmp 0x432198
    goto L_0x00432198;
L_0x0043224f:
    // 0043224f  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00432250  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00432251  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00432252  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00432253  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00432254  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00432255  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x54 0x22 0x00 */
void Application::sub_432260(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00432260  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00432261  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00432262  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00432263  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00432264  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00432265  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00432266  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
L_0x00432268:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00432268  8b4810                 -mov ecx, dword ptr [eax + 0x10]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(16) /* 0x10 */);
    // 0043226b  8b500c                 -mov edx, dword ptr [eax + 0xc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
    // 0043226e  39ca                   +cmp edx, ecx
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ecx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00432270  0f87a3000000           -ja 0x432319
    if (!cpu.flags.cf && !cpu.flags.zf)
    {
        goto L_0x00432319;
    }
    // 00432276  668b12                 -mov dx, word ptr [edx]
    cpu.dx = app->getMemory<x86::reg16>(cpu.edx);
    // 00432279  8b481c                 -mov ecx, dword ptr [eax + 0x1c]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(28) /* 0x1c */);
    // 0043227c  8b5814                 -mov ebx, dword ptr [eax + 0x14]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */);
    // 0043227f  8b7018                 -mov esi, dword ptr [eax + 0x18]
    cpu.esi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */);
    // 00432282  01cb                   -add ebx, ecx
    (cpu.ebx) += x86::reg32(x86::sreg32(cpu.ecx));
    // 00432284  8b4820                 -mov ecx, dword ptr [eax + 0x20]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(32) /* 0x20 */);
    // 00432287  895814                 -mov dword ptr [eax + 0x14], ebx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */) = cpu.ebx;
    // 0043228a  01ce                   -add esi, ecx
    (cpu.esi) += x86::reg32(x86::sreg32(cpu.ecx));
    // 0043228c  897018                 -mov dword ptr [eax + 0x18], esi
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */) = cpu.esi;
    // 0043228f  8b35704e5500           -mov esi, dword ptr [0x554e70]
    cpu.esi = app->getMemory<x86::reg32>(x86::reg32(5590640) /* 0x554e70 */);
    // 00432295  81e2ffff0000           -and edx, 0xffff
    cpu.edx &= x86::reg32(x86::sreg32(65535 /*0xffff*/));
    // 0043229b  8b1d981f5f00           -mov ebx, dword ptr [0x5f1f98]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(6234008) /* 0x5f1f98 */);
    // 004322a1  21d6                   -and esi, edx
    cpu.esi &= x86::reg32(x86::sreg32(cpu.edx));
    // 004322a3  668b3473               -mov si, word ptr [ebx + esi*2]
    cpu.si = app->getMemory<x86::reg16>(cpu.ebx + cpu.esi * 2);
    // 004322a7  8b1d744e5500           -mov ebx, dword ptr [0x554e74]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(5590644) /* 0x554e74 */);
    // 004322ad  8a0d804e5500           -mov cl, byte ptr [0x554e80]
    cpu.cl = app->getMemory<x86::reg8>(x86::reg32(5590656) /* 0x554e80 */);
    // 004322b3  21d3                   -and ebx, edx
    cpu.ebx &= x86::reg32(x86::sreg32(cpu.edx));
    // 004322b5  d3fb                   -sar ebx, cl
    cpu.ebx = x86::reg32(x86::sreg32(cpu.ebx) >> (cpu.cl % 32));
    // 004322b7  8b0da41f5f00           -mov ecx, dword ptr [0x5f1fa4]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(6234020) /* 0x5f1fa4 */);
    // 004322bd  81e6ffff0000           -and esi, 0xffff
    cpu.esi &= x86::reg32(x86::sreg32(65535 /*0xffff*/));
    // 004322c3  668b1c59               -mov bx, word ptr [ecx + ebx*2]
    cpu.bx = app->getMemory<x86::reg16>(cpu.ecx + cpu.ebx * 2);
    // 004322c7  8a0d804e5500           -mov cl, byte ptr [0x554e80]
    cpu.cl = app->getMemory<x86::reg8>(x86::reg32(5590656) /* 0x554e80 */);
    // 004322cd  81e3ffff0000           -and ebx, 0xffff
    cpu.ebx &= x86::reg32(x86::sreg32(65535 /*0xffff*/));
    // 004322d3  8b3d784e5500           -mov edi, dword ptr [0x554e78]
    cpu.edi = app->getMemory<x86::reg32>(x86::reg32(5590648) /* 0x554e78 */);
    // 004322d9  d3e3                   -shl ebx, cl
    cpu.ebx <<= cpu.cl % 32;
    // 004322db  21fa                   -and edx, edi
    cpu.edx &= x86::reg32(x86::sreg32(cpu.edi));
    // 004322dd  8a0d844e5500           -mov cl, byte ptr [0x554e84]
    cpu.cl = app->getMemory<x86::reg8>(x86::reg32(5590660) /* 0x554e84 */);
    // 004322e3  d3fa                   -sar edx, cl
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (cpu.cl % 32));
    // 004322e5  8b0d9c1f5f00           -mov ecx, dword ptr [0x5f1f9c]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(6234012) /* 0x5f1f9c */);
    // 004322eb  668b1451               -mov dx, word ptr [ecx + edx*2]
    cpu.dx = app->getMemory<x86::reg16>(cpu.ecx + cpu.edx * 2);
    // 004322ef  8a0d844e5500           -mov cl, byte ptr [0x554e84]
    cpu.cl = app->getMemory<x86::reg8>(x86::reg32(5590660) /* 0x554e84 */);
    // 004322f5  81e2ffff0000           -and edx, 0xffff
    cpu.edx &= x86::reg32(x86::sreg32(65535 /*0xffff*/));
    // 004322fb  09f3                   -or ebx, esi
    cpu.ebx |= x86::reg32(x86::sreg32(cpu.esi));
    // 004322fd  d3e2                   -shl edx, cl
    cpu.edx <<= cpu.cl % 32;
    // 004322ff  09da                   -or edx, ebx
    cpu.edx |= x86::reg32(x86::sreg32(cpu.ebx));
    // 00432301  668b1da01f5f00         -mov bx, word ptr [0x5f1fa0]
    cpu.bx = app->getMemory<x86::reg16>(x86::reg32(6234016) /* 0x5f1fa0 */);
    // 00432308  8b480c                 -mov ecx, dword ptr [eax + 0xc]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
    // 0043230b  01da                   -add edx, ebx
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.ebx));
    // 0043230d  668911                 -mov word ptr [ecx], dx
    app->getMemory<x86::reg16>(cpu.ecx) = cpu.dx;
    // 00432310  83400c02               +add dword ptr [eax + 0xc], 2
    {
        auto tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(2 /*0x2*/));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 00432314  e94fffffff             -jmp 0x432268
    goto L_0x00432268;
L_0x00432319:
    // 00432319  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043231a  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043231b  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043231c  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043231d  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043231e  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043231f  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip  */
void Application::sub_432320(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00432320  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00432321  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00432322  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00432323  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00432324  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00432325  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
L_0x00432327:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00432327  8b5010                 -mov edx, dword ptr [eax + 0x10]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(16) /* 0x10 */);
    // 0043232a  8b480c                 -mov ecx, dword ptr [eax + 0xc]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
    // 0043232d  39d1                   +cmp ecx, edx
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.edx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0043232f  7737                   -ja 0x432368
    if (!cpu.flags.cf && !cpu.flags.zf)
    {
        goto L_0x00432368;
    }
    // 00432331  668b11                 -mov dx, word ptr [ecx]
    cpu.dx = app->getMemory<x86::reg16>(cpu.ecx);
    // 00432334  8b5814                 -mov ebx, dword ptr [eax + 0x14]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */);
    // 00432337  8b481c                 -mov ecx, dword ptr [eax + 0x1c]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(28) /* 0x1c */);
    // 0043233a  8b7018                 -mov esi, dword ptr [eax + 0x18]
    cpu.esi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */);
    // 0043233d  01cb                   -add ebx, ecx
    (cpu.ebx) += x86::reg32(x86::sreg32(cpu.ecx));
    // 0043233f  8b4820                 -mov ecx, dword ptr [eax + 0x20]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(32) /* 0x20 */);
    // 00432342  895814                 -mov dword ptr [eax + 0x14], ebx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */) = cpu.ebx;
    // 00432345  01ce                   -add esi, ecx
    (cpu.esi) += x86::reg32(x86::sreg32(cpu.ecx));
    // 00432347  8a0d8c4e5500           -mov cl, byte ptr [0x554e8c]
    cpu.cl = app->getMemory<x86::reg8>(x86::reg32(5590668) /* 0x554e8c */);
    // 0043234d  668b1d884e5500         -mov bx, word ptr [0x554e88]
    cpu.bx = app->getMemory<x86::reg16>(x86::reg32(5590664) /* 0x554e88 */);
    // 00432354  66d3ea                 -shr dx, cl
    cpu.dx >>= cpu.cl % 32;
    // 00432357  8b480c                 -mov ecx, dword ptr [eax + 0xc]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
    // 0043235a  897018                 -mov dword ptr [eax + 0x18], esi
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */) = cpu.esi;
    // 0043235d  21da                   -and edx, ebx
    cpu.edx &= x86::reg32(x86::sreg32(cpu.ebx));
    // 0043235f  668911                 -mov word ptr [ecx], dx
    app->getMemory<x86::reg16>(cpu.ecx) = cpu.dx;
    // 00432362  83400c02               +add dword ptr [eax + 0xc], 2
    {
        auto tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(2 /*0x2*/));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 00432366  ebbf                   -jmp 0x432327
    goto L_0x00432327;
L_0x00432368:
    // 00432368  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00432369  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043236a  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043236b  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043236c  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043236d  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_432370: native, nfs3hp::graphics::clearSoftwareBlend */

/* sub_432390: native, nfs3hp::graphics::setSoftwareBlendColour */

/* sub_432440: native, nfs3hp::graphics::dead_0x432440 */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x54 0x22 0x00 */
void Application::sub_432690(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00432690  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00432691  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00432693  83ec18                 +sub esp, 0x18
    {
        x86::reg32& tmp1 = cpu.esp;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(24 /*0x18*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 00432696  8b4008                 -mov eax, dword ptr [eax + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 00432699  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 0043269c  8b4208                 -mov eax, dword ptr [edx + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(8) /* 0x8 */);
    // 0043269f  8945f4                 -mov dword ptr [ebp - 0xc], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.eax;
    // 004326a2  8b4308                 -mov eax, dword ptr [ebx + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(8) /* 0x8 */);
    // 004326a5  8945f8                 -mov dword ptr [ebp - 8], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.eax;
    // 004326a8  8b4108                 -mov eax, dword ptr [ecx + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(8) /* 0x8 */);
    // 004326ab  d945f4                 +fld dword ptr [ebp - 0xc]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */));
    // 004326ae  8945f0                 -mov dword ptr [ebp - 0x10], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = cpu.eax;
    // 004326b1  d85dfc                 +fcomp dword ptr [ebp - 4]
    cpu.fpu.compare(fpu1, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 004326b4  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 004326b6  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 004326b7  7306                   -jae 0x4326bf
    if (!cpu.flags.cf)
    {
        goto L_0x004326bf;
    }
    // 004326b9  8b45f4                 -mov eax, dword ptr [ebp - 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 004326bc  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
L_0x004326bf:
    // 004326bf  d945f8                 +fld dword ptr [ebp - 8]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu2 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */));
    // 004326c2  d85dfc                 +fcomp dword ptr [ebp - 4]
    cpu.fpu.compare(fpu2, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 004326c5  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 004326c7  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 004326c8  7306                   -jae 0x4326d0
    if (!cpu.flags.cf)
    {
        goto L_0x004326d0;
    }
    // 004326ca  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004326cd  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
L_0x004326d0:
    // 004326d0  d945f0                 +fld dword ptr [ebp - 0x10]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu3 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-16) /* -0x10 */));
    // 004326d3  d85dfc                 +fcomp dword ptr [ebp - 4]
    cpu.fpu.compare(fpu3, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 004326d6  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 004326d8  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 004326d9  7306                   -jae 0x4326e1
    if (!cpu.flags.cf)
    {
        goto L_0x004326e1;
    }
    // 004326db  8b45f0                 -mov eax, dword ptr [ebp - 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 004326de  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
L_0x004326e1:
    // 004326e1  d945fc                 +fld dword ptr [ebp - 4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu4 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */));
    // 004326e4  dd55e8                 +fst qword ptr [ebp - 0x18]
    app->getMemory<double>(cpu.ebp + x86::reg32(-24) /* -0x18 */) = double(fpu4);
    // 004326e7  dc1d74745300           +fcomp qword ptr [0x537474]
    cpu.fpu.compare(fpu4, x86::Float(app->getMemory<double>(x86::reg32(5469300) /* 0x537474 */)));
    // 004326ed  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 004326ef  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 004326f0  7606                   -jbe 0x4326f8
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x004326f8;
    }
    // 004326f2  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
    // 004326f4  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004326f6  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004326f7  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004326f8:
    // 004326f8  dd45e8                 +fld qword ptr [ebp - 0x18]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu5 = x86::Float(app->getMemory<double>(cpu.ebp + x86::reg32(-24) /* -0x18 */));
    // 004326fb  dc1d7c745300           +fcomp qword ptr [0x53747c]
    cpu.fpu.compare(fpu5, x86::Float(app->getMemory<double>(x86::reg32(5469308) /* 0x53747c */)));
    // 00432701  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00432703  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 00432704  7609                   -jbe 0x43270f
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x0043270f;
    }
    // 00432706  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 0043270b  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 0043270d  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043270e  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x0043270f:
    // 0043270f  b802000000             -mov eax, 2
    cpu.eax = 2 /*0x2*/;
    // 00432714  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00432716  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00432717  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8b 0xd2 */
void Application::sub_432720(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (subdivideQuad(app, cpu.sync())) /* port: native (tools/apply_native_render.py) */
    {
        cpu.reload();
        return;
    }
    // 00432720  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00432721  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00432722  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00432723  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00432725  81ec00010000           -sub esp, 0x100
    (cpu.esp) -= x86::reg32(x86::sreg32(256 /*0x100*/));
    // 0043272b  83ed6e                 -sub ebp, 0x6e
    (cpu.ebp) -= x86::reg32(x86::sreg32(110 /*0x6e*/));
    // 0043272e  89455e                 -mov dword ptr [ebp + 0x5e], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(94) /* 0x5e */) = cpu.eax;
    // 00432731  89556a                 -mov dword ptr [ebp + 0x6a], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(106) /* 0x6a */) = cpu.edx;
    // 00432734  895d62                 -mov dword ptr [ebp + 0x62], ebx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(98) /* 0x62 */) = cpu.ebx;
    // 00432737  894d66                 -mov dword ptr [ebp + 0x66], ecx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(102) /* 0x66 */) = cpu.ecx;
    // 0043273a  8b8d8e000000           -mov ecx, dword ptr [ebp + 0x8e]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(142) /* 0x8e */);
    // 00432740  8b9d8a000000           -mov ebx, dword ptr [ebp + 0x8a]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(138) /* 0x8a */);
    // 00432746  8b9586000000           -mov edx, dword ptr [ebp + 0x86]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(134) /* 0x86 */);
    // 0043274c  8b8582000000           -mov eax, dword ptr [ebp + 0x82]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(130) /* 0x82 */);
    // 00432752  e839ffffff             -call 0x432690
    cpu.esp -= 4;
    sub_432690(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00432757  3b455e                 +cmp eax, dword ptr [ebp + 0x5e]
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(94) /* 0x5e */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0043275a  0f8ef2070000           -jle 0x432f52
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00432f52;
    }
    // 00432760  8b456a                 -mov eax, dword ptr [ebp + 0x6a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(106) /* 0x6a */);
    // 00432763  d900                   -fld dword ptr [eax]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.eax));
    // 00432765  8b4562                 -mov eax, dword ptr [ebp + 0x62]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(98) /* 0x62 */);
    // 00432768  d800                   -fadd dword ptr [eax]
    x86::Float fpu2 = cpu.fpu.add(fpu1, x86::Float(app->getMemory<float>(cpu.eax)));
    // 0043276a  dd0584745300           -fld qword ptr [0x537484]
    x86::Float fpu3 = x86::Float(app->getMemory<double>(x86::reg32(5469316) /* 0x537484 */));
    // 00432770  d9c9                   -fxch st(1)
    
    // 00432772  d8c9                   -fmul st(1)
    x86::Float fpu4 = cpu.fpu.mul(fpu2, x86::Float(fpu3));
    // 00432774  8b456a                 -mov eax, dword ptr [ebp + 0x6a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(106) /* 0x6a */);
    // 00432777  d95d0e                 -fstp dword ptr [ebp + 0xe]
    app->getMemory<float>(cpu.ebp + x86::reg32(14) /* 0xe */) = float(fpu4);
    // 0043277a  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu5 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 0043277d  8b4562                 -mov eax, dword ptr [ebp + 0x62]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(98) /* 0x62 */);
    // 00432780  d84004                 -fadd dword ptr [eax + 4]
    x86::Float fpu6 = cpu.fpu.add(fpu5, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */)));
    // 00432783  d8c9                   -fmul st(1)
    x86::Float fpu7 = cpu.fpu.mul(fpu6, x86::Float(fpu3));
    // 00432785  8b456a                 -mov eax, dword ptr [ebp + 0x6a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(106) /* 0x6a */);
    // 00432788  d95d12                 -fstp dword ptr [ebp + 0x12]
    app->getMemory<float>(cpu.ebp + x86::reg32(18) /* 0x12 */) = float(fpu7);
    // 0043278b  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu8 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 0043278e  8b4562                 -mov eax, dword ptr [ebp + 0x62]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(98) /* 0x62 */);
    // 00432791  d84008                 -fadd dword ptr [eax + 8]
    x86::Float fpu9 = cpu.fpu.add(fpu8, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */)));
    // 00432794  d8c9                   -fmul st(1)
    x86::Float fpu10 = cpu.fpu.mul(fpu9, x86::Float(fpu3));
    // 00432796  8b8582000000           -mov eax, dword ptr [ebp + 0x82]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(130) /* 0x82 */);
    // 0043279c  d95d16                 -fstp dword ptr [ebp + 0x16]
    app->getMemory<float>(cpu.ebp + x86::reg32(22) /* 0x16 */) = float(fpu10);
    // 0043279f  d94018                 -fld dword ptr [eax + 0x18]
    x86::Float fpu11 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(24) /* 0x18 */));
    // 004327a2  8b8586000000           -mov eax, dword ptr [ebp + 0x86]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(134) /* 0x86 */);
    // 004327a8  d84018                 -fadd dword ptr [eax + 0x18]
    x86::Float fpu12 = cpu.fpu.add(fpu11, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(24) /* 0x18 */)));
    // 004327ab  d8c9                   -fmul st(1)
    x86::Float fpu13 = cpu.fpu.mul(fpu12, x86::Float(fpu3));
    // 004327ad  8b8582000000           -mov eax, dword ptr [ebp + 0x82]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(130) /* 0x82 */);
    // 004327b3  d95d86                 -fstp dword ptr [ebp - 0x7a]
    app->getMemory<float>(cpu.ebp + x86::reg32(-122) /* -0x7a */) = float(fpu13);
    // 004327b6  d9401c                 -fld dword ptr [eax + 0x1c]
    x86::Float fpu14 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(28) /* 0x1c */));
    // 004327b9  8b8586000000           -mov eax, dword ptr [ebp + 0x86]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(134) /* 0x86 */);
    // 004327bf  d8401c                 -fadd dword ptr [eax + 0x1c]
    x86::Float fpu15 = cpu.fpu.add(fpu14, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(28) /* 0x1c */)));
    // 004327c2  dec9                   -fmulp st(1)
    x86::Float fpu16 = cpu.fpu.mul(fpu3, fpu15);
    // 004327c4  8b9582000000           -mov edx, dword ptr [ebp + 0x82]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(130) /* 0x82 */);
    // 004327ca  d95d8a                 -fstp dword ptr [ebp - 0x76]
    app->getMemory<float>(cpu.ebp + x86::reg32(-118) /* -0x76 */) = float(fpu16);
    // 004327cd  8b5210                 -mov edx, dword ptr [edx + 0x10]
    cpu.edx = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(16) /* 0x10 */);
    // 004327d0  8b4010                 -mov eax, dword ptr [eax + 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(16) /* 0x10 */);
    // 004327d3  d1ea                   -shr edx, 1
    cpu.edx >>= 1 /*0x1*/ % 32;
    // 004327d5  d1e8                   -shr eax, 1
    cpu.eax >>= 1 /*0x1*/ % 32;
    // 004327d7  81e27f7f7f7f           -and edx, 0x7f7f7f7f
    cpu.edx &= x86::reg32(x86::sreg32(2139062143 /*0x7f7f7f7f*/));
    // 004327dd  257f7f7f7f             -and eax, 0x7f7f7f7f
    cpu.eax &= x86::reg32(x86::sreg32(2139062143 /*0x7f7f7f7f*/));
    // 004327e2  01c2                   -add edx, eax
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.eax));
    // 004327e4  8b4d16                 -mov ecx, dword ptr [ebp + 0x16]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(22) /* 0x16 */);
    // 004327e7  89957effffff           -mov dword ptr [ebp - 0x82], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-130) /* -0x82 */) = cpu.edx;
    // 004327ed  f7c1ffffff7f           +test ecx, 0x7fffffff
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & 2147483647 /*0x7fffffff*/));
    }
    // 004327f3  7507                   -jne 0x4327fc
    if (!cpu.flags.zf)
    {
        goto L_0x004327fc;
    }
    // 004327f5  c7451680008037         -mov dword ptr [ebp + 0x16], 0x37800080
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(22) /* 0x16 */) = 931135616 /*0x37800080*/;
L_0x004327fc:
    // 004327fc  d9e8                   -fld1 
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu17 = 1.0;
    // 004327fe  d87516                 -fdiv dword ptr [ebp + 0x16]
    x86::Float fpu18 = cpu.fpu.div(fpu17, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(22) /* 0x16 */)));
    // 00432801  8d4d4a                 -lea ecx, [ebp + 0x4a]
    cpu.ecx = x86::reg32(cpu.ebp + x86::reg32(74) /* 0x4a */);
    // 00432804  8d9d6effffff           -lea ebx, [ebp - 0x92]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-146) /* -0x92 */);
    // 0043280a  8d450e                 -lea eax, [ebp + 0xe]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(14) /* 0xe */);
    // 0043280d  8d7d82                 -lea edi, [ebp - 0x7e]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(-126) /* -0x7e */);
    // 00432810  8db56effffff           -lea esi, [ebp - 0x92]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(-146) /* -0x92 */);
    // 00432816  d95d4a                 -fstp dword ptr [ebp + 0x4a]
    app->getMemory<float>(cpu.ebp + x86::reg32(74) /* 0x4a */) = float(fpu18);
    // 00432819  d9059c005600           -fld dword ptr [0x56009c]
    x86::Float fpu19 = x86::Float(app->getMemory<float>(x86::reg32(5636252) /* 0x56009c */));
    // 0043281f  d809                   -fmul dword ptr [ecx]
    x86::Float fpu20 = cpu.fpu.mul(fpu19, x86::Float(app->getMemory<float>(cpu.ecx)));
    // 00432821  d905a0005600           -fld dword ptr [0x5600a0]
    x86::Float fpu21 = x86::Float(app->getMemory<float>(x86::reg32(5636256) /* 0x5600a0 */));
    // 00432827  d809                   -fmul dword ptr [ecx]
    x86::Float fpu22 = cpu.fpu.mul(fpu21, x86::Float(app->getMemory<float>(cpu.ecx)));
    // 00432829  8b11                   -mov edx, dword ptr [ecx]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ecx);
    // 0043282b  d84804                 -fmul dword ptr [eax + 4]
    x86::Float fpu23 = cpu.fpu.mul(fpu22, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */)));
    // 0043282e  d9c9                   -fxch st(1)
    
    // 00432830  89530c                 -mov dword ptr [ebx + 0xc], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(12) /* 0xc */) = cpu.edx;
    // 00432833  d808                   -fmul dword ptr [eax]
    x86::Float fpu24 = cpu.fpu.mul(fpu20, x86::Float(app->getMemory<float>(cpu.eax)));
    // 00432835  8b5008                 -mov edx, dword ptr [eax + 8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 00432838  d905a4005600           -fld dword ptr [0x5600a4]
    x86::Float fpu25 = x86::Float(app->getMemory<float>(x86::reg32(5636260) /* 0x5600a4 */));
    // 0043283e  dec1                   -faddp st(1)
    x86::Float fpu26 = cpu.fpu.add(fpu24, fpu25);
    // 00432840  d905a8005600           -fld dword ptr [0x5600a8]
    x86::Float fpu27 = x86::Float(app->getMemory<float>(x86::reg32(5636264) /* 0x5600a8 */));
    // 00432846  dec2                   -faddp st(2)
    x86::Float fpu28 = cpu.fpu.add(fpu23, fpu27);
    // 00432848  d91b                   -fstp dword ptr [ebx]
    app->getMemory<float>(cpu.ebx) = float(fpu26);
    // 0043284a  895308                 -mov dword ptr [ebx + 8], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(8) /* 0x8 */) = cpu.edx;
    // 0043284d  d95b04                 -fstp dword ptr [ebx + 4]
    app->getMemory<float>(cpu.ebx + x86::reg32(4) /* 0x4 */) = float(fpu28);
    // 00432850  8b460c                 -mov eax, dword ptr [esi + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 00432853  8b0df8347d00           -mov ecx, dword ptr [0x7d34f8]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205560) /* 0x7d34f8 */);
    // 00432859  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    }
    // 0043285e  7558                   -jne 0x4328b8
    if (!cpu.flags.zf)
    {
        goto L_0x004328b8;
    }
    // 00432860  39c8                   +cmp eax, ecx
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ecx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00432862  7d54                   -jge 0x4328b8
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004328b8;
    }
    // 00432864  8b4604                 -mov eax, dword ptr [esi + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 00432867  bb00000000             -mov ebx, 0
    cpu.ebx = 0 /*0x0*/;
    // 0043286c  8b0d04357d00           -mov ecx, dword ptr [0x7d3504]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205572) /* 0x7d3504 */);
    // 00432872  8b1500357d00           -mov edx, dword ptr [0x7d3500]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205568) /* 0x7d3500 */);
    // 00432878  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 0043287d  750d                   -jne 0x43288c
    if (!cpu.flags.zf)
    {
        goto L_0x0043288c;
    }
    // 0043287f  39c8                   +cmp eax, ecx
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ecx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00432881  7c09                   -jl 0x43288c
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x0043288c;
    }
    // 00432883  39d0                   +cmp eax, edx
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.edx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00432885  7e09                   -jle 0x432890
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00432890;
    }
    // 00432887  83cb04                 +or ebx, 4
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(4 /*0x4*/))));
    // 0043288a  eb04                   -jmp 0x432890
    goto L_0x00432890;
L_0x0043288c:
    // 0043288c  83cb08                 -or ebx, 8
    cpu.ebx |= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 0043288f  90                     -nop 
    ;
L_0x00432890:
    // 00432890  8b06                   -mov eax, dword ptr [esi]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi);
    // 00432892  90                     -nop 
    ;
    // 00432893  8b0dfc347d00           -mov ecx, dword ptr [0x7d34fc]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205564) /* 0x7d34fc */);
    // 00432899  8b150c357d00           -mov edx, dword ptr [0x7d350c]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205580) /* 0x7d350c */);
    // 0043289f  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004328a4  750d                   -jne 0x4328b3
    if (!cpu.flags.zf)
    {
        goto L_0x004328b3;
    }
    // 004328a6  39c8                   +cmp eax, ecx
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ecx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004328a8  7c09                   -jl 0x4328b3
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004328b3;
    }
    // 004328aa  39d0                   +cmp eax, edx
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.edx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004328ac  7e0f                   -jle 0x4328bd
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004328bd;
    }
    // 004328ae  83cb02                 +or ebx, 2
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(2 /*0x2*/))));
    // 004328b1  eb0a                   -jmp 0x4328bd
    goto L_0x004328bd;
L_0x004328b3:
    // 004328b3  83cb01                 +or ebx, 1
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(1 /*0x1*/))));
    // 004328b6  eb05                   -jmp 0x4328bd
    goto L_0x004328bd;
L_0x004328b8:
    // 004328b8  bb10000000             -mov ebx, 0x10
    cpu.ebx = 16 /*0x10*/;
L_0x004328bd:
    // 004328bd  881f                   -mov byte ptr [edi], bl
    app->getMemory<x86::reg8>(cpu.edi) = cpu.bl;
    // 004328bf  8b456a                 -mov eax, dword ptr [ebp + 0x6a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(106) /* 0x6a */);
    // 004328c2  d900                   -fld dword ptr [eax]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu29 = x86::Float(app->getMemory<float>(cpu.eax));
    // 004328c4  8b457e                 -mov eax, dword ptr [ebp + 0x7e]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */);
    // 004328c7  d800                   -fadd dword ptr [eax]
    x86::Float fpu30 = cpu.fpu.add(fpu29, x86::Float(app->getMemory<float>(cpu.eax)));
    // 004328c9  dd0584745300           -fld qword ptr [0x537484]
    x86::Float fpu31 = x86::Float(app->getMemory<double>(x86::reg32(5469316) /* 0x537484 */));
    // 004328cf  d9c9                   -fxch st(1)
    
    // 004328d1  d8c9                   -fmul st(1)
    x86::Float fpu32 = cpu.fpu.mul(fpu30, x86::Float(fpu31));
    // 004328d3  8b456a                 -mov eax, dword ptr [ebp + 0x6a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(106) /* 0x6a */);
    // 004328d6  d95d1a                 -fstp dword ptr [ebp + 0x1a]
    app->getMemory<float>(cpu.ebp + x86::reg32(26) /* 0x1a */) = float(fpu32);
    // 004328d9  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu33 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 004328dc  8b457e                 -mov eax, dword ptr [ebp + 0x7e]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */);
    // 004328df  d84004                 -fadd dword ptr [eax + 4]
    x86::Float fpu34 = cpu.fpu.add(fpu33, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */)));
    // 004328e2  d8c9                   -fmul st(1)
    x86::Float fpu35 = cpu.fpu.mul(fpu34, x86::Float(fpu31));
    // 004328e4  8b456a                 -mov eax, dword ptr [ebp + 0x6a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(106) /* 0x6a */);
    // 004328e7  d95d1e                 -fstp dword ptr [ebp + 0x1e]
    app->getMemory<float>(cpu.ebp + x86::reg32(30) /* 0x1e */) = float(fpu35);
    // 004328ea  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu36 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 004328ed  8b457e                 -mov eax, dword ptr [ebp + 0x7e]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */);
    // 004328f0  d84008                 -fadd dword ptr [eax + 8]
    x86::Float fpu37 = cpu.fpu.add(fpu36, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */)));
    // 004328f3  d8c9                   -fmul st(1)
    x86::Float fpu38 = cpu.fpu.mul(fpu37, x86::Float(fpu31));
    // 004328f5  8b8582000000           -mov eax, dword ptr [ebp + 0x82]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(130) /* 0x82 */);
    // 004328fb  d95d22                 -fstp dword ptr [ebp + 0x22]
    app->getMemory<float>(cpu.ebp + x86::reg32(34) /* 0x22 */) = float(fpu38);
    // 004328fe  d94018                 -fld dword ptr [eax + 0x18]
    x86::Float fpu39 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(24) /* 0x18 */));
    // 00432901  8b858e000000           -mov eax, dword ptr [ebp + 0x8e]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(142) /* 0x8e */);
    // 00432907  d84018                 -fadd dword ptr [eax + 0x18]
    x86::Float fpu40 = cpu.fpu.add(fpu39, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(24) /* 0x18 */)));
    // 0043290a  d8c9                   -fmul st(1)
    x86::Float fpu41 = cpu.fpu.mul(fpu40, x86::Float(fpu31));
    // 0043290c  8b8582000000           -mov eax, dword ptr [ebp + 0x82]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(130) /* 0x82 */);
    // 00432912  d95da6                 -fstp dword ptr [ebp - 0x5a]
    app->getMemory<float>(cpu.ebp + x86::reg32(-90) /* -0x5a */) = float(fpu41);
    // 00432915  d9401c                 -fld dword ptr [eax + 0x1c]
    x86::Float fpu42 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(28) /* 0x1c */));
    // 00432918  8b858e000000           -mov eax, dword ptr [ebp + 0x8e]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(142) /* 0x8e */);
    // 0043291e  d8401c                 -fadd dword ptr [eax + 0x1c]
    x86::Float fpu43 = cpu.fpu.add(fpu42, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(28) /* 0x1c */)));
    // 00432921  dec9                   -fmulp st(1)
    x86::Float fpu44 = cpu.fpu.mul(fpu31, fpu43);
    // 00432923  8b9582000000           -mov edx, dword ptr [ebp + 0x82]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(130) /* 0x82 */);
    // 00432929  d95daa                 -fstp dword ptr [ebp - 0x56]
    app->getMemory<float>(cpu.ebp + x86::reg32(-86) /* -0x56 */) = float(fpu44);
    // 0043292c  8b5210                 -mov edx, dword ptr [edx + 0x10]
    cpu.edx = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(16) /* 0x10 */);
    // 0043292f  8b4010                 -mov eax, dword ptr [eax + 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(16) /* 0x10 */);
    // 00432932  d1ea                   -shr edx, 1
    cpu.edx >>= 1 /*0x1*/ % 32;
    // 00432934  d1e8                   -shr eax, 1
    cpu.eax >>= 1 /*0x1*/ % 32;
    // 00432936  81e27f7f7f7f           -and edx, 0x7f7f7f7f
    cpu.edx &= x86::reg32(x86::sreg32(2139062143 /*0x7f7f7f7f*/));
    // 0043293c  257f7f7f7f             -and eax, 0x7f7f7f7f
    cpu.eax &= x86::reg32(x86::sreg32(2139062143 /*0x7f7f7f7f*/));
    // 00432941  01c2                   -add edx, eax
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.eax));
    // 00432943  8b7522                 -mov esi, dword ptr [ebp + 0x22]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(34) /* 0x22 */);
    // 00432946  89559e                 -mov dword ptr [ebp - 0x62], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-98) /* -0x62 */) = cpu.edx;
    // 00432949  f7c6ffffff7f           +test esi, 0x7fffffff
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & 2147483647 /*0x7fffffff*/));
    }
    // 0043294f  7507                   -jne 0x432958
    if (!cpu.flags.zf)
    {
        goto L_0x00432958;
    }
    // 00432951  c7452280008037         -mov dword ptr [ebp + 0x22], 0x37800080
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(34) /* 0x22 */) = 931135616 /*0x37800080*/;
L_0x00432958:
    // 00432958  d9e8                   -fld1 
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu45 = 1.0;
    // 0043295a  d87522                 -fdiv dword ptr [ebp + 0x22]
    x86::Float fpu46 = cpu.fpu.div(fpu45, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(34) /* 0x22 */)));
    // 0043295d  8d4d4e                 -lea ecx, [ebp + 0x4e]
    cpu.ecx = x86::reg32(cpu.ebp + x86::reg32(78) /* 0x4e */);
    // 00432960  8d5d8e                 -lea ebx, [ebp - 0x72]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-114) /* -0x72 */);
    // 00432963  8d451a                 -lea eax, [ebp + 0x1a]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(26) /* 0x1a */);
    // 00432966  8d7da2                 -lea edi, [ebp - 0x5e]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(-94) /* -0x5e */);
    // 00432969  8d758e                 -lea esi, [ebp - 0x72]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(-114) /* -0x72 */);
    // 0043296c  d95d4e                 -fstp dword ptr [ebp + 0x4e]
    app->getMemory<float>(cpu.ebp + x86::reg32(78) /* 0x4e */) = float(fpu46);
    // 0043296f  d9059c005600           -fld dword ptr [0x56009c]
    x86::Float fpu47 = x86::Float(app->getMemory<float>(x86::reg32(5636252) /* 0x56009c */));
    // 00432975  d809                   -fmul dword ptr [ecx]
    x86::Float fpu48 = cpu.fpu.mul(fpu47, x86::Float(app->getMemory<float>(cpu.ecx)));
    // 00432977  d905a0005600           -fld dword ptr [0x5600a0]
    x86::Float fpu49 = x86::Float(app->getMemory<float>(x86::reg32(5636256) /* 0x5600a0 */));
    // 0043297d  d809                   -fmul dword ptr [ecx]
    x86::Float fpu50 = cpu.fpu.mul(fpu49, x86::Float(app->getMemory<float>(cpu.ecx)));
    // 0043297f  8b11                   -mov edx, dword ptr [ecx]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ecx);
    // 00432981  d84804                 -fmul dword ptr [eax + 4]
    x86::Float fpu51 = cpu.fpu.mul(fpu50, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */)));
    // 00432984  d9c9                   -fxch st(1)
    
    // 00432986  89530c                 -mov dword ptr [ebx + 0xc], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(12) /* 0xc */) = cpu.edx;
    // 00432989  d808                   -fmul dword ptr [eax]
    x86::Float fpu52 = cpu.fpu.mul(fpu48, x86::Float(app->getMemory<float>(cpu.eax)));
    // 0043298b  8b5008                 -mov edx, dword ptr [eax + 8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 0043298e  d905a4005600           -fld dword ptr [0x5600a4]
    x86::Float fpu53 = x86::Float(app->getMemory<float>(x86::reg32(5636260) /* 0x5600a4 */));
    // 00432994  dec1                   -faddp st(1)
    x86::Float fpu54 = cpu.fpu.add(fpu52, fpu53);
    // 00432996  d905a8005600           -fld dword ptr [0x5600a8]
    x86::Float fpu55 = x86::Float(app->getMemory<float>(x86::reg32(5636264) /* 0x5600a8 */));
    // 0043299c  dec2                   -faddp st(2)
    x86::Float fpu56 = cpu.fpu.add(fpu51, fpu55);
    // 0043299e  d91b                   -fstp dword ptr [ebx]
    app->getMemory<float>(cpu.ebx) = float(fpu54);
    // 004329a0  895308                 -mov dword ptr [ebx + 8], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(8) /* 0x8 */) = cpu.edx;
    // 004329a3  d95b04                 -fstp dword ptr [ebx + 4]
    app->getMemory<float>(cpu.ebx + x86::reg32(4) /* 0x4 */) = float(fpu56);
    // 004329a6  8b460c                 -mov eax, dword ptr [esi + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 004329a9  8b0df8347d00           -mov ecx, dword ptr [0x7d34f8]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205560) /* 0x7d34f8 */);
    // 004329af  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    }
    // 004329b4  7558                   -jne 0x432a0e
    if (!cpu.flags.zf)
    {
        goto L_0x00432a0e;
    }
    // 004329b6  39c8                   +cmp eax, ecx
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ecx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004329b8  7d54                   -jge 0x432a0e
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00432a0e;
    }
    // 004329ba  8b4604                 -mov eax, dword ptr [esi + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 004329bd  bb00000000             -mov ebx, 0
    cpu.ebx = 0 /*0x0*/;
    // 004329c2  8b0d04357d00           -mov ecx, dword ptr [0x7d3504]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205572) /* 0x7d3504 */);
    // 004329c8  8b1500357d00           -mov edx, dword ptr [0x7d3500]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205568) /* 0x7d3500 */);
    // 004329ce  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004329d3  750d                   -jne 0x4329e2
    if (!cpu.flags.zf)
    {
        goto L_0x004329e2;
    }
    // 004329d5  39c8                   +cmp eax, ecx
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ecx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004329d7  7c09                   -jl 0x4329e2
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004329e2;
    }
    // 004329d9  39d0                   +cmp eax, edx
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.edx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004329db  7e09                   -jle 0x4329e6
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004329e6;
    }
    // 004329dd  83cb04                 +or ebx, 4
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(4 /*0x4*/))));
    // 004329e0  eb04                   -jmp 0x4329e6
    goto L_0x004329e6;
L_0x004329e2:
    // 004329e2  83cb08                 -or ebx, 8
    cpu.ebx |= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 004329e5  90                     -nop 
    ;
L_0x004329e6:
    // 004329e6  8b06                   -mov eax, dword ptr [esi]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi);
    // 004329e8  90                     -nop 
    ;
    // 004329e9  8b0dfc347d00           -mov ecx, dword ptr [0x7d34fc]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205564) /* 0x7d34fc */);
    // 004329ef  8b150c357d00           -mov edx, dword ptr [0x7d350c]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205580) /* 0x7d350c */);
    // 004329f5  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004329fa  750d                   -jne 0x432a09
    if (!cpu.flags.zf)
    {
        goto L_0x00432a09;
    }
    // 004329fc  39c8                   +cmp eax, ecx
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ecx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004329fe  7c09                   -jl 0x432a09
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x00432a09;
    }
    // 00432a00  39d0                   +cmp eax, edx
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.edx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00432a02  7e0f                   -jle 0x432a13
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00432a13;
    }
    // 00432a04  83cb02                 +or ebx, 2
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(2 /*0x2*/))));
    // 00432a07  eb0a                   -jmp 0x432a13
    goto L_0x00432a13;
L_0x00432a09:
    // 00432a09  83cb01                 +or ebx, 1
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(1 /*0x1*/))));
    // 00432a0c  eb05                   -jmp 0x432a13
    goto L_0x00432a13;
L_0x00432a0e:
    // 00432a0e  bb10000000             -mov ebx, 0x10
    cpu.ebx = 16 /*0x10*/;
L_0x00432a13:
    // 00432a13  881f                   -mov byte ptr [edi], bl
    app->getMemory<x86::reg8>(cpu.edi) = cpu.bl;
    // 00432a15  8b4562                 -mov eax, dword ptr [ebp + 0x62]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(98) /* 0x62 */);
    // 00432a18  d900                   -fld dword ptr [eax]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu57 = x86::Float(app->getMemory<float>(cpu.eax));
    // 00432a1a  8b4566                 -mov eax, dword ptr [ebp + 0x66]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(102) /* 0x66 */);
    // 00432a1d  d800                   -fadd dword ptr [eax]
    x86::Float fpu58 = cpu.fpu.add(fpu57, x86::Float(app->getMemory<float>(cpu.eax)));
    // 00432a1f  dd0584745300           -fld qword ptr [0x537484]
    x86::Float fpu59 = x86::Float(app->getMemory<double>(x86::reg32(5469316) /* 0x537484 */));
    // 00432a25  d9c9                   -fxch st(1)
    
    // 00432a27  d8c9                   -fmul st(1)
    x86::Float fpu60 = cpu.fpu.mul(fpu58, x86::Float(fpu59));
    // 00432a29  8b4562                 -mov eax, dword ptr [ebp + 0x62]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(98) /* 0x62 */);
    // 00432a2c  d95d26                 -fstp dword ptr [ebp + 0x26]
    app->getMemory<float>(cpu.ebp + x86::reg32(38) /* 0x26 */) = float(fpu60);
    // 00432a2f  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu61 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 00432a32  8b4566                 -mov eax, dword ptr [ebp + 0x66]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(102) /* 0x66 */);
    // 00432a35  d84004                 -fadd dword ptr [eax + 4]
    x86::Float fpu62 = cpu.fpu.add(fpu61, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */)));
    // 00432a38  d8c9                   -fmul st(1)
    x86::Float fpu63 = cpu.fpu.mul(fpu62, x86::Float(fpu59));
    // 00432a3a  8b4562                 -mov eax, dword ptr [ebp + 0x62]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(98) /* 0x62 */);
    // 00432a3d  d95d2a                 -fstp dword ptr [ebp + 0x2a]
    app->getMemory<float>(cpu.ebp + x86::reg32(42) /* 0x2a */) = float(fpu63);
    // 00432a40  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu64 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 00432a43  8b4566                 -mov eax, dword ptr [ebp + 0x66]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(102) /* 0x66 */);
    // 00432a46  d84008                 -fadd dword ptr [eax + 8]
    x86::Float fpu65 = cpu.fpu.add(fpu64, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */)));
    // 00432a49  d8c9                   -fmul st(1)
    x86::Float fpu66 = cpu.fpu.mul(fpu65, x86::Float(fpu59));
    // 00432a4b  8b8586000000           -mov eax, dword ptr [ebp + 0x86]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(134) /* 0x86 */);
    // 00432a51  d95d2e                 -fstp dword ptr [ebp + 0x2e]
    app->getMemory<float>(cpu.ebp + x86::reg32(46) /* 0x2e */) = float(fpu66);
    // 00432a54  d94018                 -fld dword ptr [eax + 0x18]
    x86::Float fpu67 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(24) /* 0x18 */));
    // 00432a57  8b858a000000           -mov eax, dword ptr [ebp + 0x8a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(138) /* 0x8a */);
    // 00432a5d  d84018                 -fadd dword ptr [eax + 0x18]
    x86::Float fpu68 = cpu.fpu.add(fpu67, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(24) /* 0x18 */)));
    // 00432a60  d8c9                   -fmul st(1)
    x86::Float fpu69 = cpu.fpu.mul(fpu68, x86::Float(fpu59));
    // 00432a62  8b8586000000           -mov eax, dword ptr [ebp + 0x86]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(134) /* 0x86 */);
    // 00432a68  d95dc6                 -fstp dword ptr [ebp - 0x3a]
    app->getMemory<float>(cpu.ebp + x86::reg32(-58) /* -0x3a */) = float(fpu69);
    // 00432a6b  d9401c                 -fld dword ptr [eax + 0x1c]
    x86::Float fpu70 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(28) /* 0x1c */));
    // 00432a6e  8b858a000000           -mov eax, dword ptr [ebp + 0x8a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(138) /* 0x8a */);
    // 00432a74  d8401c                 -fadd dword ptr [eax + 0x1c]
    x86::Float fpu71 = cpu.fpu.add(fpu70, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(28) /* 0x1c */)));
    // 00432a77  dec9                   -fmulp st(1)
    x86::Float fpu72 = cpu.fpu.mul(fpu59, fpu71);
    // 00432a79  8b9586000000           -mov edx, dword ptr [ebp + 0x86]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(134) /* 0x86 */);
    // 00432a7f  d95dca                 -fstp dword ptr [ebp - 0x36]
    app->getMemory<float>(cpu.ebp + x86::reg32(-54) /* -0x36 */) = float(fpu72);
    // 00432a82  8b5210                 -mov edx, dword ptr [edx + 0x10]
    cpu.edx = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(16) /* 0x10 */);
    // 00432a85  8b4010                 -mov eax, dword ptr [eax + 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(16) /* 0x10 */);
    // 00432a88  d1ea                   -shr edx, 1
    cpu.edx >>= 1 /*0x1*/ % 32;
    // 00432a8a  d1e8                   -shr eax, 1
    cpu.eax >>= 1 /*0x1*/ % 32;
    // 00432a8c  81e27f7f7f7f           -and edx, 0x7f7f7f7f
    cpu.edx &= x86::reg32(x86::sreg32(2139062143 /*0x7f7f7f7f*/));
    // 00432a92  257f7f7f7f             -and eax, 0x7f7f7f7f
    cpu.eax &= x86::reg32(x86::sreg32(2139062143 /*0x7f7f7f7f*/));
    // 00432a97  01c2                   -add edx, eax
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.eax));
    // 00432a99  8b452e                 -mov eax, dword ptr [ebp + 0x2e]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(46) /* 0x2e */);
    // 00432a9c  8955be                 -mov dword ptr [ebp - 0x42], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-66) /* -0x42 */) = cpu.edx;
    // 00432a9f  a9ffffff7f             +test eax, 0x7fffffff
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483647 /*0x7fffffff*/));
    }
    // 00432aa4  7507                   -jne 0x432aad
    if (!cpu.flags.zf)
    {
        goto L_0x00432aad;
    }
    // 00432aa6  c7452e80008037         -mov dword ptr [ebp + 0x2e], 0x37800080
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(46) /* 0x2e */) = 931135616 /*0x37800080*/;
L_0x00432aad:
    // 00432aad  d9e8                   -fld1 
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu73 = 1.0;
    // 00432aaf  d8752e                 -fdiv dword ptr [ebp + 0x2e]
    x86::Float fpu74 = cpu.fpu.div(fpu73, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(46) /* 0x2e */)));
    // 00432ab2  8d4d52                 -lea ecx, [ebp + 0x52]
    cpu.ecx = x86::reg32(cpu.ebp + x86::reg32(82) /* 0x52 */);
    // 00432ab5  8d5dae                 -lea ebx, [ebp - 0x52]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-82) /* -0x52 */);
    // 00432ab8  8d4526                 -lea eax, [ebp + 0x26]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(38) /* 0x26 */);
    // 00432abb  8d7dc2                 -lea edi, [ebp - 0x3e]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(-62) /* -0x3e */);
    // 00432abe  8d75ae                 -lea esi, [ebp - 0x52]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(-82) /* -0x52 */);
    // 00432ac1  d95d52                 -fstp dword ptr [ebp + 0x52]
    app->getMemory<float>(cpu.ebp + x86::reg32(82) /* 0x52 */) = float(fpu74);
    // 00432ac4  d9059c005600           -fld dword ptr [0x56009c]
    x86::Float fpu75 = x86::Float(app->getMemory<float>(x86::reg32(5636252) /* 0x56009c */));
    // 00432aca  d809                   -fmul dword ptr [ecx]
    x86::Float fpu76 = cpu.fpu.mul(fpu75, x86::Float(app->getMemory<float>(cpu.ecx)));
    // 00432acc  d905a0005600           -fld dword ptr [0x5600a0]
    x86::Float fpu77 = x86::Float(app->getMemory<float>(x86::reg32(5636256) /* 0x5600a0 */));
    // 00432ad2  d809                   -fmul dword ptr [ecx]
    x86::Float fpu78 = cpu.fpu.mul(fpu77, x86::Float(app->getMemory<float>(cpu.ecx)));
    // 00432ad4  8b11                   -mov edx, dword ptr [ecx]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ecx);
    // 00432ad6  d84804                 -fmul dword ptr [eax + 4]
    x86::Float fpu79 = cpu.fpu.mul(fpu78, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */)));
    // 00432ad9  d9c9                   -fxch st(1)
    
    // 00432adb  89530c                 -mov dword ptr [ebx + 0xc], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(12) /* 0xc */) = cpu.edx;
    // 00432ade  d808                   -fmul dword ptr [eax]
    x86::Float fpu80 = cpu.fpu.mul(fpu76, x86::Float(app->getMemory<float>(cpu.eax)));
    // 00432ae0  8b5008                 -mov edx, dword ptr [eax + 8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 00432ae3  d905a4005600           -fld dword ptr [0x5600a4]
    x86::Float fpu81 = x86::Float(app->getMemory<float>(x86::reg32(5636260) /* 0x5600a4 */));
    // 00432ae9  dec1                   -faddp st(1)
    x86::Float fpu82 = cpu.fpu.add(fpu80, fpu81);
    // 00432aeb  d905a8005600           -fld dword ptr [0x5600a8]
    x86::Float fpu83 = x86::Float(app->getMemory<float>(x86::reg32(5636264) /* 0x5600a8 */));
    // 00432af1  dec2                   -faddp st(2)
    x86::Float fpu84 = cpu.fpu.add(fpu79, fpu83);
    // 00432af3  d91b                   -fstp dword ptr [ebx]
    app->getMemory<float>(cpu.ebx) = float(fpu82);
    // 00432af5  895308                 -mov dword ptr [ebx + 8], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(8) /* 0x8 */) = cpu.edx;
    // 00432af8  d95b04                 -fstp dword ptr [ebx + 4]
    app->getMemory<float>(cpu.ebx + x86::reg32(4) /* 0x4 */) = float(fpu84);
    // 00432afb  8b460c                 -mov eax, dword ptr [esi + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 00432afe  8b0df8347d00           -mov ecx, dword ptr [0x7d34f8]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205560) /* 0x7d34f8 */);
    // 00432b04  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    }
    // 00432b09  7558                   -jne 0x432b63
    if (!cpu.flags.zf)
    {
        goto L_0x00432b63;
    }
    // 00432b0b  39c8                   +cmp eax, ecx
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ecx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00432b0d  7d54                   -jge 0x432b63
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00432b63;
    }
    // 00432b0f  8b4604                 -mov eax, dword ptr [esi + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 00432b12  bb00000000             -mov ebx, 0
    cpu.ebx = 0 /*0x0*/;
    // 00432b17  8b0d04357d00           -mov ecx, dword ptr [0x7d3504]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205572) /* 0x7d3504 */);
    // 00432b1d  8b1500357d00           -mov edx, dword ptr [0x7d3500]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205568) /* 0x7d3500 */);
    // 00432b23  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 00432b28  750d                   -jne 0x432b37
    if (!cpu.flags.zf)
    {
        goto L_0x00432b37;
    }
    // 00432b2a  39c8                   +cmp eax, ecx
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ecx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00432b2c  7c09                   -jl 0x432b37
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x00432b37;
    }
    // 00432b2e  39d0                   +cmp eax, edx
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.edx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00432b30  7e09                   -jle 0x432b3b
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00432b3b;
    }
    // 00432b32  83cb04                 +or ebx, 4
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(4 /*0x4*/))));
    // 00432b35  eb04                   -jmp 0x432b3b
    goto L_0x00432b3b;
L_0x00432b37:
    // 00432b37  83cb08                 -or ebx, 8
    cpu.ebx |= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 00432b3a  90                     -nop 
    ;
L_0x00432b3b:
    // 00432b3b  8b06                   -mov eax, dword ptr [esi]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi);
    // 00432b3d  90                     -nop 
    ;
    // 00432b3e  8b0dfc347d00           -mov ecx, dword ptr [0x7d34fc]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205564) /* 0x7d34fc */);
    // 00432b44  8b150c357d00           -mov edx, dword ptr [0x7d350c]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205580) /* 0x7d350c */);
    // 00432b4a  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 00432b4f  750d                   -jne 0x432b5e
    if (!cpu.flags.zf)
    {
        goto L_0x00432b5e;
    }
    // 00432b51  39c8                   +cmp eax, ecx
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ecx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00432b53  7c09                   -jl 0x432b5e
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x00432b5e;
    }
    // 00432b55  39d0                   +cmp eax, edx
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.edx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00432b57  7e0f                   -jle 0x432b68
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00432b68;
    }
    // 00432b59  83cb02                 +or ebx, 2
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(2 /*0x2*/))));
    // 00432b5c  eb0a                   -jmp 0x432b68
    goto L_0x00432b68;
L_0x00432b5e:
    // 00432b5e  83cb01                 +or ebx, 1
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(1 /*0x1*/))));
    // 00432b61  eb05                   -jmp 0x432b68
    goto L_0x00432b68;
L_0x00432b63:
    // 00432b63  bb10000000             -mov ebx, 0x10
    cpu.ebx = 16 /*0x10*/;
L_0x00432b68:
    // 00432b68  881f                   -mov byte ptr [edi], bl
    app->getMemory<x86::reg8>(cpu.edi) = cpu.bl;
    // 00432b6a  8b457e                 -mov eax, dword ptr [ebp + 0x7e]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */);
    // 00432b6d  d900                   -fld dword ptr [eax]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu85 = x86::Float(app->getMemory<float>(cpu.eax));
    // 00432b6f  8b4566                 -mov eax, dword ptr [ebp + 0x66]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(102) /* 0x66 */);
    // 00432b72  d800                   -fadd dword ptr [eax]
    x86::Float fpu86 = cpu.fpu.add(fpu85, x86::Float(app->getMemory<float>(cpu.eax)));
    // 00432b74  dd0584745300           -fld qword ptr [0x537484]
    x86::Float fpu87 = x86::Float(app->getMemory<double>(x86::reg32(5469316) /* 0x537484 */));
    // 00432b7a  d9c9                   -fxch st(1)
    
    // 00432b7c  d8c9                   -fmul st(1)
    x86::Float fpu88 = cpu.fpu.mul(fpu86, x86::Float(fpu87));
    // 00432b7e  8b457e                 -mov eax, dword ptr [ebp + 0x7e]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */);
    // 00432b81  d95d32                 -fstp dword ptr [ebp + 0x32]
    app->getMemory<float>(cpu.ebp + x86::reg32(50) /* 0x32 */) = float(fpu88);
    // 00432b84  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu89 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 00432b87  8b4566                 -mov eax, dword ptr [ebp + 0x66]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(102) /* 0x66 */);
    // 00432b8a  d84004                 -fadd dword ptr [eax + 4]
    x86::Float fpu90 = cpu.fpu.add(fpu89, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */)));
    // 00432b8d  d8c9                   -fmul st(1)
    x86::Float fpu91 = cpu.fpu.mul(fpu90, x86::Float(fpu87));
    // 00432b8f  8b457e                 -mov eax, dword ptr [ebp + 0x7e]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */);
    // 00432b92  d95d36                 -fstp dword ptr [ebp + 0x36]
    app->getMemory<float>(cpu.ebp + x86::reg32(54) /* 0x36 */) = float(fpu91);
    // 00432b95  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu92 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 00432b98  8b4566                 -mov eax, dword ptr [ebp + 0x66]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(102) /* 0x66 */);
    // 00432b9b  d84008                 -fadd dword ptr [eax + 8]
    x86::Float fpu93 = cpu.fpu.add(fpu92, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */)));
    // 00432b9e  d8c9                   -fmul st(1)
    x86::Float fpu94 = cpu.fpu.mul(fpu93, x86::Float(fpu87));
    // 00432ba0  8b858e000000           -mov eax, dword ptr [ebp + 0x8e]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(142) /* 0x8e */);
    // 00432ba6  d95d3a                 -fstp dword ptr [ebp + 0x3a]
    app->getMemory<float>(cpu.ebp + x86::reg32(58) /* 0x3a */) = float(fpu94);
    // 00432ba9  d94018                 -fld dword ptr [eax + 0x18]
    x86::Float fpu95 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(24) /* 0x18 */));
    // 00432bac  8b858a000000           -mov eax, dword ptr [ebp + 0x8a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(138) /* 0x8a */);
    // 00432bb2  d84018                 -fadd dword ptr [eax + 0x18]
    x86::Float fpu96 = cpu.fpu.add(fpu95, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(24) /* 0x18 */)));
    // 00432bb5  d8c9                   -fmul st(1)
    x86::Float fpu97 = cpu.fpu.mul(fpu96, x86::Float(fpu87));
    // 00432bb7  8b858e000000           -mov eax, dword ptr [ebp + 0x8e]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(142) /* 0x8e */);
    // 00432bbd  d95de6                 -fstp dword ptr [ebp - 0x1a]
    app->getMemory<float>(cpu.ebp + x86::reg32(-26) /* -0x1a */) = float(fpu97);
    // 00432bc0  d9401c                 -fld dword ptr [eax + 0x1c]
    x86::Float fpu98 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(28) /* 0x1c */));
    // 00432bc3  8b858a000000           -mov eax, dword ptr [ebp + 0x8a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(138) /* 0x8a */);
    // 00432bc9  d8401c                 -fadd dword ptr [eax + 0x1c]
    x86::Float fpu99 = cpu.fpu.add(fpu98, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(28) /* 0x1c */)));
    // 00432bcc  dec9                   -fmulp st(1)
    x86::Float fpu100 = cpu.fpu.mul(fpu87, fpu99);
    // 00432bce  8b958e000000           -mov edx, dword ptr [ebp + 0x8e]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(142) /* 0x8e */);
    // 00432bd4  d95dea                 -fstp dword ptr [ebp - 0x16]
    app->getMemory<float>(cpu.ebp + x86::reg32(-22) /* -0x16 */) = float(fpu100);
    // 00432bd7  8b5210                 -mov edx, dword ptr [edx + 0x10]
    cpu.edx = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(16) /* 0x10 */);
    // 00432bda  8b4010                 -mov eax, dword ptr [eax + 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(16) /* 0x10 */);
    // 00432bdd  d1ea                   -shr edx, 1
    cpu.edx >>= 1 /*0x1*/ % 32;
    // 00432bdf  d1e8                   -shr eax, 1
    cpu.eax >>= 1 /*0x1*/ % 32;
    // 00432be1  81e27f7f7f7f           -and edx, 0x7f7f7f7f
    cpu.edx &= x86::reg32(x86::sreg32(2139062143 /*0x7f7f7f7f*/));
    // 00432be7  257f7f7f7f             -and eax, 0x7f7f7f7f
    cpu.eax &= x86::reg32(x86::sreg32(2139062143 /*0x7f7f7f7f*/));
    // 00432bec  01c2                   -add edx, eax
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.eax));
    // 00432bee  8b4d3a                 -mov ecx, dword ptr [ebp + 0x3a]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(58) /* 0x3a */);
    // 00432bf1  8955de                 -mov dword ptr [ebp - 0x22], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-34) /* -0x22 */) = cpu.edx;
    // 00432bf4  f7c1ffffff7f           +test ecx, 0x7fffffff
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & 2147483647 /*0x7fffffff*/));
    }
    // 00432bfa  7507                   -jne 0x432c03
    if (!cpu.flags.zf)
    {
        goto L_0x00432c03;
    }
    // 00432bfc  c7453a80008037         -mov dword ptr [ebp + 0x3a], 0x37800080
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(58) /* 0x3a */) = 931135616 /*0x37800080*/;
L_0x00432c03:
    // 00432c03  d9e8                   -fld1 
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu101 = 1.0;
    // 00432c05  d8753a                 -fdiv dword ptr [ebp + 0x3a]
    x86::Float fpu102 = cpu.fpu.div(fpu101, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(58) /* 0x3a */)));
    // 00432c08  8d4d56                 -lea ecx, [ebp + 0x56]
    cpu.ecx = x86::reg32(cpu.ebp + x86::reg32(86) /* 0x56 */);
    // 00432c0b  8d5dce                 -lea ebx, [ebp - 0x32]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-50) /* -0x32 */);
    // 00432c0e  8d4532                 -lea eax, [ebp + 0x32]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(50) /* 0x32 */);
    // 00432c11  8d7de2                 -lea edi, [ebp - 0x1e]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(-30) /* -0x1e */);
    // 00432c14  8d75ce                 -lea esi, [ebp - 0x32]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(-50) /* -0x32 */);
    // 00432c17  d95d56                 -fstp dword ptr [ebp + 0x56]
    app->getMemory<float>(cpu.ebp + x86::reg32(86) /* 0x56 */) = float(fpu102);
    // 00432c1a  d9059c005600           -fld dword ptr [0x56009c]
    x86::Float fpu103 = x86::Float(app->getMemory<float>(x86::reg32(5636252) /* 0x56009c */));
    // 00432c20  d809                   -fmul dword ptr [ecx]
    x86::Float fpu104 = cpu.fpu.mul(fpu103, x86::Float(app->getMemory<float>(cpu.ecx)));
    // 00432c22  d905a0005600           -fld dword ptr [0x5600a0]
    x86::Float fpu105 = x86::Float(app->getMemory<float>(x86::reg32(5636256) /* 0x5600a0 */));
    // 00432c28  d809                   -fmul dword ptr [ecx]
    x86::Float fpu106 = cpu.fpu.mul(fpu105, x86::Float(app->getMemory<float>(cpu.ecx)));
    // 00432c2a  8b11                   -mov edx, dword ptr [ecx]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ecx);
    // 00432c2c  d84804                 -fmul dword ptr [eax + 4]
    x86::Float fpu107 = cpu.fpu.mul(fpu106, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */)));
    // 00432c2f  d9c9                   -fxch st(1)
    
    // 00432c31  89530c                 -mov dword ptr [ebx + 0xc], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(12) /* 0xc */) = cpu.edx;
    // 00432c34  d808                   -fmul dword ptr [eax]
    x86::Float fpu108 = cpu.fpu.mul(fpu104, x86::Float(app->getMemory<float>(cpu.eax)));
    // 00432c36  8b5008                 -mov edx, dword ptr [eax + 8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 00432c39  d905a4005600           -fld dword ptr [0x5600a4]
    x86::Float fpu109 = x86::Float(app->getMemory<float>(x86::reg32(5636260) /* 0x5600a4 */));
    // 00432c3f  dec1                   -faddp st(1)
    x86::Float fpu110 = cpu.fpu.add(fpu108, fpu109);
    // 00432c41  d905a8005600           -fld dword ptr [0x5600a8]
    x86::Float fpu111 = x86::Float(app->getMemory<float>(x86::reg32(5636264) /* 0x5600a8 */));
    // 00432c47  dec2                   -faddp st(2)
    x86::Float fpu112 = cpu.fpu.add(fpu107, fpu111);
    // 00432c49  d91b                   -fstp dword ptr [ebx]
    app->getMemory<float>(cpu.ebx) = float(fpu110);
    // 00432c4b  895308                 -mov dword ptr [ebx + 8], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(8) /* 0x8 */) = cpu.edx;
    // 00432c4e  d95b04                 -fstp dword ptr [ebx + 4]
    app->getMemory<float>(cpu.ebx + x86::reg32(4) /* 0x4 */) = float(fpu112);
    // 00432c51  8b460c                 -mov eax, dword ptr [esi + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 00432c54  8b0df8347d00           -mov ecx, dword ptr [0x7d34f8]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205560) /* 0x7d34f8 */);
    // 00432c5a  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    }
    // 00432c5f  7558                   -jne 0x432cb9
    if (!cpu.flags.zf)
    {
        goto L_0x00432cb9;
    }
    // 00432c61  39c8                   +cmp eax, ecx
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ecx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00432c63  7d54                   -jge 0x432cb9
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00432cb9;
    }
    // 00432c65  8b4604                 -mov eax, dword ptr [esi + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 00432c68  bb00000000             -mov ebx, 0
    cpu.ebx = 0 /*0x0*/;
    // 00432c6d  8b0d04357d00           -mov ecx, dword ptr [0x7d3504]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205572) /* 0x7d3504 */);
    // 00432c73  8b1500357d00           -mov edx, dword ptr [0x7d3500]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205568) /* 0x7d3500 */);
    // 00432c79  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 00432c7e  750d                   -jne 0x432c8d
    if (!cpu.flags.zf)
    {
        goto L_0x00432c8d;
    }
    // 00432c80  39c8                   +cmp eax, ecx
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ecx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00432c82  7c09                   -jl 0x432c8d
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x00432c8d;
    }
    // 00432c84  39d0                   +cmp eax, edx
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.edx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00432c86  7e09                   -jle 0x432c91
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00432c91;
    }
    // 00432c88  83cb04                 +or ebx, 4
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(4 /*0x4*/))));
    // 00432c8b  eb04                   -jmp 0x432c91
    goto L_0x00432c91;
L_0x00432c8d:
    // 00432c8d  83cb08                 -or ebx, 8
    cpu.ebx |= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 00432c90  90                     -nop 
    ;
L_0x00432c91:
    // 00432c91  8b06                   -mov eax, dword ptr [esi]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi);
    // 00432c93  90                     -nop 
    ;
    // 00432c94  8b0dfc347d00           -mov ecx, dword ptr [0x7d34fc]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205564) /* 0x7d34fc */);
    // 00432c9a  8b150c357d00           -mov edx, dword ptr [0x7d350c]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205580) /* 0x7d350c */);
    // 00432ca0  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 00432ca5  750d                   -jne 0x432cb4
    if (!cpu.flags.zf)
    {
        goto L_0x00432cb4;
    }
    // 00432ca7  39c8                   +cmp eax, ecx
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ecx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00432ca9  7c09                   -jl 0x432cb4
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x00432cb4;
    }
    // 00432cab  39d0                   +cmp eax, edx
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.edx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00432cad  7e0f                   -jle 0x432cbe
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00432cbe;
    }
    // 00432caf  83cb02                 +or ebx, 2
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(2 /*0x2*/))));
    // 00432cb2  eb0a                   -jmp 0x432cbe
    goto L_0x00432cbe;
L_0x00432cb4:
    // 00432cb4  83cb01                 +or ebx, 1
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(1 /*0x1*/))));
    // 00432cb7  eb05                   -jmp 0x432cbe
    goto L_0x00432cbe;
L_0x00432cb9:
    // 00432cb9  bb10000000             -mov ebx, 0x10
    cpu.ebx = 16 /*0x10*/;
L_0x00432cbe:
    // 00432cbe  881f                   -mov byte ptr [edi], bl
    app->getMemory<x86::reg8>(cpu.edi) = cpu.bl;
    // 00432cc0  8b456a                 -mov eax, dword ptr [ebp + 0x6a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(106) /* 0x6a */);
    // 00432cc3  d900                   -fld dword ptr [eax]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu113 = x86::Float(app->getMemory<float>(cpu.eax));
    // 00432cc5  8b4566                 -mov eax, dword ptr [ebp + 0x66]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(102) /* 0x66 */);
    // 00432cc8  d800                   -fadd dword ptr [eax]
    x86::Float fpu114 = cpu.fpu.add(fpu113, x86::Float(app->getMemory<float>(cpu.eax)));
    // 00432cca  dd0584745300           -fld qword ptr [0x537484]
    x86::Float fpu115 = x86::Float(app->getMemory<double>(x86::reg32(5469316) /* 0x537484 */));
    // 00432cd0  d9c9                   -fxch st(1)
    
    // 00432cd2  d8c9                   -fmul st(1)
    x86::Float fpu116 = cpu.fpu.mul(fpu114, x86::Float(fpu115));
    // 00432cd4  8b456a                 -mov eax, dword ptr [ebp + 0x6a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(106) /* 0x6a */);
    // 00432cd7  d95d3e                 -fstp dword ptr [ebp + 0x3e]
    app->getMemory<float>(cpu.ebp + x86::reg32(62) /* 0x3e */) = float(fpu116);
    // 00432cda  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu117 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 00432cdd  8b4566                 -mov eax, dword ptr [ebp + 0x66]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(102) /* 0x66 */);
    // 00432ce0  d84004                 -fadd dword ptr [eax + 4]
    x86::Float fpu118 = cpu.fpu.add(fpu117, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */)));
    // 00432ce3  d8c9                   -fmul st(1)
    x86::Float fpu119 = cpu.fpu.mul(fpu118, x86::Float(fpu115));
    // 00432ce5  8b456a                 -mov eax, dword ptr [ebp + 0x6a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(106) /* 0x6a */);
    // 00432ce8  d95d42                 -fstp dword ptr [ebp + 0x42]
    app->getMemory<float>(cpu.ebp + x86::reg32(66) /* 0x42 */) = float(fpu119);
    // 00432ceb  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu120 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 00432cee  8b4566                 -mov eax, dword ptr [ebp + 0x66]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(102) /* 0x66 */);
    // 00432cf1  d84008                 -fadd dword ptr [eax + 8]
    x86::Float fpu121 = cpu.fpu.add(fpu120, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */)));
    // 00432cf4  d8c9                   -fmul st(1)
    x86::Float fpu122 = cpu.fpu.mul(fpu121, x86::Float(fpu115));
    // 00432cf6  8b8582000000           -mov eax, dword ptr [ebp + 0x82]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(130) /* 0x82 */);
    // 00432cfc  d95d46                 -fstp dword ptr [ebp + 0x46]
    app->getMemory<float>(cpu.ebp + x86::reg32(70) /* 0x46 */) = float(fpu122);
    // 00432cff  d94018                 -fld dword ptr [eax + 0x18]
    x86::Float fpu123 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(24) /* 0x18 */));
    // 00432d02  8b858a000000           -mov eax, dword ptr [ebp + 0x8a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(138) /* 0x8a */);
    // 00432d08  d84018                 -fadd dword ptr [eax + 0x18]
    x86::Float fpu124 = cpu.fpu.add(fpu123, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(24) /* 0x18 */)));
    // 00432d0b  d8c9                   -fmul st(1)
    x86::Float fpu125 = cpu.fpu.mul(fpu124, x86::Float(fpu115));
    // 00432d0d  8b8582000000           -mov eax, dword ptr [ebp + 0x82]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(130) /* 0x82 */);
    // 00432d13  d95d06                 -fstp dword ptr [ebp + 6]
    app->getMemory<float>(cpu.ebp + x86::reg32(6) /* 0x6 */) = float(fpu125);
    // 00432d16  d9401c                 -fld dword ptr [eax + 0x1c]
    x86::Float fpu126 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(28) /* 0x1c */));
    // 00432d19  8b858a000000           -mov eax, dword ptr [ebp + 0x8a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(138) /* 0x8a */);
    // 00432d1f  d8401c                 -fadd dword ptr [eax + 0x1c]
    x86::Float fpu127 = cpu.fpu.add(fpu126, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(28) /* 0x1c */)));
    // 00432d22  dec9                   -fmulp st(1)
    x86::Float fpu128 = cpu.fpu.mul(fpu115, fpu127);
    // 00432d24  8b958a000000           -mov edx, dword ptr [ebp + 0x8a]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(138) /* 0x8a */);
    // 00432d2a  8b8582000000           -mov eax, dword ptr [ebp + 0x82]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(130) /* 0x82 */);
    // 00432d30  d95d0a                 -fstp dword ptr [ebp + 0xa]
    app->getMemory<float>(cpu.ebp + x86::reg32(10) /* 0xa */) = float(fpu128);
    // 00432d33  8b4010                 -mov eax, dword ptr [eax + 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(16) /* 0x10 */);
    // 00432d36  8b5210                 -mov edx, dword ptr [edx + 0x10]
    cpu.edx = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(16) /* 0x10 */);
    // 00432d39  d1e8                   -shr eax, 1
    cpu.eax >>= 1 /*0x1*/ % 32;
    // 00432d3b  d1ea                   -shr edx, 1
    cpu.edx >>= 1 /*0x1*/ % 32;
    // 00432d3d  257f7f7f7f             -and eax, 0x7f7f7f7f
    cpu.eax &= x86::reg32(x86::sreg32(2139062143 /*0x7f7f7f7f*/));
    // 00432d42  81e27f7f7f7f           -and edx, 0x7f7f7f7f
    cpu.edx &= x86::reg32(x86::sreg32(2139062143 /*0x7f7f7f7f*/));
    // 00432d48  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 00432d4a  8b7546                 -mov esi, dword ptr [ebp + 0x46]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(70) /* 0x46 */);
    // 00432d4d  8945fe                 -mov dword ptr [ebp - 2], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-2) /* -0x2 */) = cpu.eax;
    // 00432d50  f7c6ffffff7f           +test esi, 0x7fffffff
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & 2147483647 /*0x7fffffff*/));
    }
    // 00432d56  7507                   -jne 0x432d5f
    if (!cpu.flags.zf)
    {
        goto L_0x00432d5f;
    }
    // 00432d58  c7454680008037         -mov dword ptr [ebp + 0x46], 0x37800080
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(70) /* 0x46 */) = 931135616 /*0x37800080*/;
L_0x00432d5f:
    // 00432d5f  d9e8                   -fld1 
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu129 = 1.0;
    // 00432d61  d87546                 -fdiv dword ptr [ebp + 0x46]
    x86::Float fpu130 = cpu.fpu.div(fpu129, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(70) /* 0x46 */)));
    // 00432d64  8d4d5a                 -lea ecx, [ebp + 0x5a]
    cpu.ecx = x86::reg32(cpu.ebp + x86::reg32(90) /* 0x5a */);
    // 00432d67  8d5dee                 -lea ebx, [ebp - 0x12]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-18) /* -0x12 */);
    // 00432d6a  8d453e                 -lea eax, [ebp + 0x3e]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(62) /* 0x3e */);
    // 00432d6d  8d7d02                 -lea edi, [ebp + 2]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(2) /* 0x2 */);
    // 00432d70  8d75ee                 -lea esi, [ebp - 0x12]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(-18) /* -0x12 */);
    // 00432d73  d95d5a                 -fstp dword ptr [ebp + 0x5a]
    app->getMemory<float>(cpu.ebp + x86::reg32(90) /* 0x5a */) = float(fpu130);
    // 00432d76  d9059c005600           -fld dword ptr [0x56009c]
    x86::Float fpu131 = x86::Float(app->getMemory<float>(x86::reg32(5636252) /* 0x56009c */));
    // 00432d7c  d809                   -fmul dword ptr [ecx]
    x86::Float fpu132 = cpu.fpu.mul(fpu131, x86::Float(app->getMemory<float>(cpu.ecx)));
    // 00432d7e  d905a0005600           -fld dword ptr [0x5600a0]
    x86::Float fpu133 = x86::Float(app->getMemory<float>(x86::reg32(5636256) /* 0x5600a0 */));
    // 00432d84  d809                   -fmul dword ptr [ecx]
    x86::Float fpu134 = cpu.fpu.mul(fpu133, x86::Float(app->getMemory<float>(cpu.ecx)));
    // 00432d86  8b11                   -mov edx, dword ptr [ecx]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ecx);
    // 00432d88  d84804                 -fmul dword ptr [eax + 4]
    x86::Float fpu135 = cpu.fpu.mul(fpu134, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */)));
    // 00432d8b  d9c9                   -fxch st(1)
    
    // 00432d8d  89530c                 -mov dword ptr [ebx + 0xc], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(12) /* 0xc */) = cpu.edx;
    // 00432d90  d808                   -fmul dword ptr [eax]
    x86::Float fpu136 = cpu.fpu.mul(fpu132, x86::Float(app->getMemory<float>(cpu.eax)));
    // 00432d92  8b5008                 -mov edx, dword ptr [eax + 8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 00432d95  d905a4005600           -fld dword ptr [0x5600a4]
    x86::Float fpu137 = x86::Float(app->getMemory<float>(x86::reg32(5636260) /* 0x5600a4 */));
    // 00432d9b  dec1                   -faddp st(1)
    x86::Float fpu138 = cpu.fpu.add(fpu136, fpu137);
    // 00432d9d  d905a8005600           -fld dword ptr [0x5600a8]
    x86::Float fpu139 = x86::Float(app->getMemory<float>(x86::reg32(5636264) /* 0x5600a8 */));
    // 00432da3  dec2                   -faddp st(2)
    x86::Float fpu140 = cpu.fpu.add(fpu135, fpu139);
    // 00432da5  d91b                   -fstp dword ptr [ebx]
    app->getMemory<float>(cpu.ebx) = float(fpu138);
    // 00432da7  895308                 -mov dword ptr [ebx + 8], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(8) /* 0x8 */) = cpu.edx;
    // 00432daa  d95b04                 -fstp dword ptr [ebx + 4]
    app->getMemory<float>(cpu.ebx + x86::reg32(4) /* 0x4 */) = float(fpu140);
    // 00432dad  8b460c                 -mov eax, dword ptr [esi + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 00432db0  8b0df8347d00           -mov ecx, dword ptr [0x7d34f8]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205560) /* 0x7d34f8 */);
    // 00432db6  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    }
    // 00432dbb  7558                   -jne 0x432e15
    if (!cpu.flags.zf)
    {
        goto L_0x00432e15;
    }
    // 00432dbd  39c8                   +cmp eax, ecx
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ecx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00432dbf  7d54                   -jge 0x432e15
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00432e15;
    }
    // 00432dc1  8b4604                 -mov eax, dword ptr [esi + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 00432dc4  bb00000000             -mov ebx, 0
    cpu.ebx = 0 /*0x0*/;
    // 00432dc9  8b0d04357d00           -mov ecx, dword ptr [0x7d3504]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205572) /* 0x7d3504 */);
    // 00432dcf  8b1500357d00           -mov edx, dword ptr [0x7d3500]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205568) /* 0x7d3500 */);
    // 00432dd5  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 00432dda  750d                   -jne 0x432de9
    if (!cpu.flags.zf)
    {
        goto L_0x00432de9;
    }
    // 00432ddc  39c8                   +cmp eax, ecx
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ecx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00432dde  7c09                   -jl 0x432de9
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x00432de9;
    }
    // 00432de0  39d0                   +cmp eax, edx
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.edx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00432de2  7e09                   -jle 0x432ded
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00432ded;
    }
    // 00432de4  83cb04                 +or ebx, 4
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(4 /*0x4*/))));
    // 00432de7  eb04                   -jmp 0x432ded
    goto L_0x00432ded;
L_0x00432de9:
    // 00432de9  83cb08                 -or ebx, 8
    cpu.ebx |= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 00432dec  90                     -nop 
    ;
L_0x00432ded:
    // 00432ded  8b06                   -mov eax, dword ptr [esi]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi);
    // 00432def  90                     -nop 
    ;
    // 00432df0  8b0dfc347d00           -mov ecx, dword ptr [0x7d34fc]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205564) /* 0x7d34fc */);
    // 00432df6  8b150c357d00           -mov edx, dword ptr [0x7d350c]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205580) /* 0x7d350c */);
    // 00432dfc  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 00432e01  750d                   -jne 0x432e10
    if (!cpu.flags.zf)
    {
        goto L_0x00432e10;
    }
    // 00432e03  39c8                   +cmp eax, ecx
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ecx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00432e05  7c09                   -jl 0x432e10
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x00432e10;
    }
    // 00432e07  39d0                   +cmp eax, edx
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.edx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00432e09  7e0f                   -jle 0x432e1a
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00432e1a;
    }
    // 00432e0b  83cb02                 +or ebx, 2
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(2 /*0x2*/))));
    // 00432e0e  eb0a                   -jmp 0x432e1a
    goto L_0x00432e1a;
L_0x00432e10:
    // 00432e10  83cb01                 +or ebx, 1
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(1 /*0x1*/))));
    // 00432e13  eb05                   -jmp 0x432e1a
    goto L_0x00432e1a;
L_0x00432e15:
    // 00432e15  bb10000000             -mov ebx, 0x10
    cpu.ebx = 16 /*0x10*/;
L_0x00432e1a:
    // 00432e1a  881f                   -mov byte ptr [edi], bl
    app->getMemory<x86::reg8>(cpu.edi) = cpu.bl;
    // 00432e1c  8b8582000000           -mov eax, dword ptr [ebp + 0x82]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(130) /* 0x82 */);
    // 00432e22  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00432e24  8a5014                 -mov dl, byte ptr [eax + 0x14]
    cpu.dl = app->getMemory<x86::reg8>(cpu.eax + x86::reg32(20) /* 0x14 */);
    // 00432e27  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00432e29  8a4582                 -mov al, byte ptr [ebp - 0x7e]
    cpu.al = app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-126) /* -0x7e */);
    // 00432e2c  21c2                   -and edx, eax
    cpu.edx &= x86::reg32(x86::sreg32(cpu.eax));
    // 00432e2e  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00432e30  8b4d5e                 -mov ecx, dword ptr [ebp + 0x5e]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(94) /* 0x5e */);
    // 00432e33  8a4502                 -mov al, byte ptr [ebp + 2]
    cpu.al = app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(2) /* 0x2 */);
    // 00432e36  41                     -inc ecx
    (cpu.ecx)++;
    // 00432e37  21c2                   -and edx, eax
    cpu.edx &= x86::reg32(x86::sreg32(cpu.eax));
    // 00432e39  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00432e3b  894d5e                 -mov dword ptr [ebp + 0x5e], ecx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(94) /* 0x5e */) = cpu.ecx;
    // 00432e3e  8a45a2                 -mov al, byte ptr [ebp - 0x5e]
    cpu.al = app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-94) /* -0x5e */);
    // 00432e41  85c2                   +test edx, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.eax));
    // 00432e43  752b                   -jne 0x432e70
    if (!cpu.flags.zf)
    {
        goto L_0x00432e70;
    }
    // 00432e45  8d458e                 -lea eax, [ebp - 0x72]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-114) /* -0x72 */);
    // 00432e48  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00432e49  8d45ee                 -lea eax, [ebp - 0x12]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-18) /* -0x12 */);
    // 00432e4c  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00432e4d  8d856effffff           -lea eax, [ebp - 0x92]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-146) /* -0x92 */);
    // 00432e53  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00432e54  8b9d82000000           -mov ebx, dword ptr [ebp + 0x82]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(130) /* 0x82 */);
    // 00432e5a  8d4d3e                 -lea ecx, [ebp + 0x3e]
    cpu.ecx = x86::reg32(cpu.ebp + x86::reg32(62) /* 0x3e */);
    // 00432e5d  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00432e5e  8d451a                 -lea eax, [ebp + 0x1a]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(26) /* 0x1a */);
    // 00432e61  8b556a                 -mov edx, dword ptr [ebp + 0x6a]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(106) /* 0x6a */);
    // 00432e64  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00432e65  8d5d0e                 -lea ebx, [ebp + 0xe]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(14) /* 0xe */);
    // 00432e68  8b455e                 -mov eax, dword ptr [ebp + 0x5e]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(94) /* 0x5e */);
    // 00432e6b  e8b0f8ffff             -call 0x432720
    cpu.esp -= 4;
    sub_432720(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00432e70:
    // 00432e70  8b8586000000           -mov eax, dword ptr [ebp + 0x86]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(134) /* 0x86 */);
    // 00432e76  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00432e78  8a5014                 -mov dl, byte ptr [eax + 0x14]
    cpu.dl = app->getMemory<x86::reg8>(cpu.eax + x86::reg32(20) /* 0x14 */);
    // 00432e7b  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00432e7d  8a4582                 -mov al, byte ptr [ebp - 0x7e]
    cpu.al = app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-126) /* -0x7e */);
    // 00432e80  21c2                   -and edx, eax
    cpu.edx &= x86::reg32(x86::sreg32(cpu.eax));
    // 00432e82  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00432e84  8a45c2                 -mov al, byte ptr [ebp - 0x3e]
    cpu.al = app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-62) /* -0x3e */);
    // 00432e87  21d0                   -and eax, edx
    cpu.eax &= x86::reg32(x86::sreg32(cpu.edx));
    // 00432e89  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00432e8b  8a5502                 -mov dl, byte ptr [ebp + 2]
    cpu.dl = app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(2) /* 0x2 */);
    // 00432e8e  85d0                   +test eax, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.edx));
    // 00432e90  752b                   -jne 0x432ebd
    if (!cpu.flags.zf)
    {
        goto L_0x00432ebd;
    }
    // 00432e92  8d45ee                 -lea eax, [ebp - 0x12]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-18) /* -0x12 */);
    // 00432e95  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00432e96  8d45ae                 -lea eax, [ebp - 0x52]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-82) /* -0x52 */);
    // 00432e99  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00432e9a  8bb586000000           -mov esi, dword ptr [ebp + 0x86]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(134) /* 0x86 */);
    // 00432ea0  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00432ea1  8d856effffff           -lea eax, [ebp - 0x92]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-146) /* -0x92 */);
    // 00432ea7  8d4d26                 -lea ecx, [ebp + 0x26]
    cpu.ecx = x86::reg32(cpu.ebp + x86::reg32(38) /* 0x26 */);
    // 00432eaa  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00432eab  8d453e                 -lea eax, [ebp + 0x3e]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(62) /* 0x3e */);
    // 00432eae  8b5d62                 -mov ebx, dword ptr [ebp + 0x62]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(98) /* 0x62 */);
    // 00432eb1  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00432eb2  8d550e                 -lea edx, [ebp + 0xe]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(14) /* 0xe */);
    // 00432eb5  8b455e                 -mov eax, dword ptr [ebp + 0x5e]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(94) /* 0x5e */);
    // 00432eb8  e863f8ffff             -call 0x432720
    cpu.esp -= 4;
    sub_432720(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00432ebd:
    // 00432ebd  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00432ebf  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00432ec1  8a4502                 -mov al, byte ptr [ebp + 2]
    cpu.al = app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(2) /* 0x2 */);
    // 00432ec4  8a55a2                 -mov dl, byte ptr [ebp - 0x5e]
    cpu.dl = app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-94) /* -0x5e */);
    // 00432ec7  21c2                   -and edx, eax
    cpu.edx &= x86::reg32(x86::sreg32(cpu.eax));
    // 00432ec9  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00432ecb  8a45e2                 -mov al, byte ptr [ebp - 0x1e]
    cpu.al = app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-30) /* -0x1e */);
    // 00432ece  8b8d8e000000           -mov ecx, dword ptr [ebp + 0x8e]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(142) /* 0x8e */);
    // 00432ed4  21c2                   -and edx, eax
    cpu.edx &= x86::reg32(x86::sreg32(cpu.eax));
    // 00432ed6  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00432ed8  8a4114                 -mov al, byte ptr [ecx + 0x14]
    cpu.al = app->getMemory<x86::reg8>(cpu.ecx + x86::reg32(20) /* 0x14 */);
    // 00432edb  85c2                   +test edx, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.eax));
    // 00432edd  7522                   -jne 0x432f01
    if (!cpu.flags.zf)
    {
        goto L_0x00432f01;
    }
    // 00432edf  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00432ee0  8d45ce                 -lea eax, [ebp - 0x32]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-50) /* -0x32 */);
    // 00432ee3  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00432ee4  8d45ee                 -lea eax, [ebp - 0x12]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-18) /* -0x12 */);
    // 00432ee7  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00432ee8  8d458e                 -lea eax, [ebp - 0x72]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-114) /* -0x72 */);
    // 00432eeb  8d5d3e                 -lea ebx, [ebp + 0x3e]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(62) /* 0x3e */);
    // 00432eee  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00432eef  8b457e                 -mov eax, dword ptr [ebp + 0x7e]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */);
    // 00432ef2  8d551a                 -lea edx, [ebp + 0x1a]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(26) /* 0x1a */);
    // 00432ef5  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00432ef6  8d4d32                 -lea ecx, [ebp + 0x32]
    cpu.ecx = x86::reg32(cpu.ebp + x86::reg32(50) /* 0x32 */);
    // 00432ef9  8b455e                 -mov eax, dword ptr [ebp + 0x5e]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(94) /* 0x5e */);
    // 00432efc  e81ff8ffff             -call 0x432720
    cpu.esp -= 4;
    sub_432720(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00432f01:
    // 00432f01  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00432f03  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00432f05  8a45c2                 -mov al, byte ptr [ebp - 0x3e]
    cpu.al = app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-62) /* -0x3e */);
    // 00432f08  8a5502                 -mov dl, byte ptr [ebp + 2]
    cpu.dl = app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(2) /* 0x2 */);
    // 00432f0b  8b8d8a000000           -mov ecx, dword ptr [ebp + 0x8a]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(138) /* 0x8a */);
    // 00432f11  21c2                   -and edx, eax
    cpu.edx &= x86::reg32(x86::sreg32(cpu.eax));
    // 00432f13  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00432f15  8a4114                 -mov al, byte ptr [ecx + 0x14]
    cpu.al = app->getMemory<x86::reg8>(cpu.ecx + x86::reg32(20) /* 0x14 */);
    // 00432f18  21c2                   -and edx, eax
    cpu.edx &= x86::reg32(x86::sreg32(cpu.eax));
    // 00432f1a  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00432f1c  8a45e2                 -mov al, byte ptr [ebp - 0x1e]
    cpu.al = app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-30) /* -0x1e */);
    // 00432f1f  85c2                   +test edx, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.eax));
    // 00432f21  0f852c010000           -jne 0x433053
    if (!cpu.flags.zf)
    {
        goto L_0x00433053;
    }
    // 00432f27  8d45ce                 -lea eax, [ebp - 0x32]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-50) /* -0x32 */);
    // 00432f2a  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00432f2b  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00432f2c  8d45ae                 -lea eax, [ebp - 0x52]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-82) /* -0x52 */);
    // 00432f2f  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00432f30  8d45ee                 -lea eax, [ebp - 0x12]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-18) /* -0x12 */);
    // 00432f33  8d5d26                 -lea ebx, [ebp + 0x26]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(38) /* 0x26 */);
    // 00432f36  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00432f37  8d4532                 -lea eax, [ebp + 0x32]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(50) /* 0x32 */);
    // 00432f3a  8d553e                 -lea edx, [ebp + 0x3e]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(62) /* 0x3e */);
    // 00432f3d  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00432f3e  8b4d66                 -mov ecx, dword ptr [ebp + 0x66]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(102) /* 0x66 */);
    // 00432f41  8b455e                 -mov eax, dword ptr [ebp + 0x5e]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(94) /* 0x5e */);
    // 00432f44  e8d7f7ffff             -call 0x432720
    cpu.esp -= 4;
    sub_432720(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00432f49  8d656e                 -lea esp, [ebp + 0x6e]
    cpu.esp = x86::reg32(cpu.ebp + x86::reg32(110) /* 0x6e */);
    // 00432f4c  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00432f4d  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00432f4e  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00432f4f  c21400                 -ret 0x14
    cpu.esp += 4+20 /*0x14*/;
    return;
L_0x00432f52:
    // 00432f52  8b8586000000           -mov eax, dword ptr [ebp + 0x86]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(134) /* 0x86 */);
    // 00432f58  8b9582000000           -mov edx, dword ptr [ebp + 0x82]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(130) /* 0x82 */);
    // 00432f5e  8b4014                 -mov eax, dword ptr [eax + 0x14]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */);
    // 00432f61  8b5214                 -mov edx, dword ptr [edx + 0x14]
    cpu.edx = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(20) /* 0x14 */);
    // 00432f64  83e010                 -and eax, 0x10
    cpu.eax &= x86::reg32(x86::sreg32(16 /*0x10*/));
    // 00432f67  83e210                 -and edx, 0x10
    cpu.edx &= x86::reg32(x86::sreg32(16 /*0x10*/));
    // 00432f6a  09c2                   -or edx, eax
    cpu.edx |= x86::reg32(x86::sreg32(cpu.eax));
    // 00432f6c  8b858a000000           -mov eax, dword ptr [ebp + 0x8a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(138) /* 0x8a */);
    // 00432f72  8b4014                 -mov eax, dword ptr [eax + 0x14]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */);
    // 00432f75  83e010                 -and eax, 0x10
    cpu.eax &= x86::reg32(x86::sreg32(16 /*0x10*/));
    // 00432f78  09c2                   -or edx, eax
    cpu.edx |= x86::reg32(x86::sreg32(cpu.eax));
    // 00432f7a  8b858e000000           -mov eax, dword ptr [ebp + 0x8e]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(142) /* 0x8e */);
    // 00432f80  8b4014                 -mov eax, dword ptr [eax + 0x14]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */);
    // 00432f83  83e010                 -and eax, 0x10
    cpu.eax &= x86::reg32(x86::sreg32(16 /*0x10*/));
    // 00432f86  09d0                   +or eax, edx
    cpu.clear_co();
    cpu.set_szp((cpu.eax |= x86::reg32(x86::sreg32(cpu.edx))));
    // 00432f88  0f85a8000000           -jne 0x433036
    if (!cpu.flags.zf)
    {
        goto L_0x00433036;
    }
    // 00432f8e  8b9586000000           -mov edx, dword ptr [ebp + 0x86]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(134) /* 0x86 */);
    // 00432f94  8b8582000000           -mov eax, dword ptr [ebp + 0x82]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(130) /* 0x82 */);
    // 00432f9a  8b5214                 -mov edx, dword ptr [edx + 0x14]
    cpu.edx = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(20) /* 0x14 */);
    // 00432f9d  8b4014                 -mov eax, dword ptr [eax + 0x14]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */);
    // 00432fa0  83e201                 -and edx, 1
    cpu.edx &= x86::reg32(x86::sreg32(1 /*0x1*/));
    // 00432fa3  83e001                 -and eax, 1
    cpu.eax &= x86::reg32(x86::sreg32(1 /*0x1*/));
    // 00432fa6  09c2                   -or edx, eax
    cpu.edx |= x86::reg32(x86::sreg32(cpu.eax));
    // 00432fa8  8b858a000000           -mov eax, dword ptr [ebp + 0x8a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(138) /* 0x8a */);
    // 00432fae  8b4014                 -mov eax, dword ptr [eax + 0x14]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */);
    // 00432fb1  83e001                 -and eax, 1
    cpu.eax &= x86::reg32(x86::sreg32(1 /*0x1*/));
    // 00432fb4  09d0                   -or eax, edx
    cpu.eax |= x86::reg32(x86::sreg32(cpu.edx));
    // 00432fb6  8b958e000000           -mov edx, dword ptr [ebp + 0x8e]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(142) /* 0x8e */);
    // 00432fbc  8b5214                 -mov edx, dword ptr [edx + 0x14]
    cpu.edx = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(20) /* 0x14 */);
    // 00432fbf  83e201                 -and edx, 1
    cpu.edx &= x86::reg32(x86::sreg32(1 /*0x1*/));
    // 00432fc2  09d0                   +or eax, edx
    cpu.clear_co();
    cpu.set_szp((cpu.eax |= x86::reg32(x86::sreg32(cpu.edx))));
    // 00432fc4  752b                   -jne 0x432ff1
    if (!cpu.flags.zf)
    {
        goto L_0x00432ff1;
    }
    // 00432fc6  8b8d8e000000           -mov ecx, dword ptr [ebp + 0x8e]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(142) /* 0x8e */);
    // 00432fcc  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00432fcd  8b9d8a000000           -mov ebx, dword ptr [ebp + 0x8a]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(138) /* 0x8a */);
    // 00432fd3  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00432fd4  8bb586000000           -mov esi, dword ptr [ebp + 0x86]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(134) /* 0x86 */);
    // 00432fda  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00432fdb  8bbd82000000           -mov edi, dword ptr [ebp + 0x82]
    cpu.edi = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(130) /* 0x82 */);
    // 00432fe1  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00432fe2  ff154cf99e00           -call dword ptr [0x9ef94c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418508) /* 0x9ef94c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00432fe8  8d656e                 -lea esp, [ebp + 0x6e]
    cpu.esp = x86::reg32(cpu.ebp + x86::reg32(110) /* 0x6e */);
    // 00432feb  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00432fec  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00432fed  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00432fee  c21400                 -ret 0x14
    cpu.esp += 4+20 /*0x14*/;
    return;
L_0x00432ff1:
    // 00432ff1  6a01                   -push 1
    app->getMemory<x86::reg32>(cpu.esp-4) = 1 /*0x1*/;
    cpu.esp -= 4;
    // 00432ff3  68c2020000             -push 0x2c2
    app->getMemory<x86::reg32>(cpu.esp-4) = 706 /*0x2c2*/;
    cpu.esp -= 4;
    // 00432ff8  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00432ffe  8b858e000000           -mov eax, dword ptr [ebp + 0x8e]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(142) /* 0x8e */);
    // 00433004  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00433005  8b958a000000           -mov edx, dword ptr [ebp + 0x8a]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(138) /* 0x8a */);
    // 0043300b  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 0043300c  8b8d86000000           -mov ecx, dword ptr [ebp + 0x86]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(134) /* 0x86 */);
    // 00433012  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00433013  8b9d82000000           -mov ebx, dword ptr [ebp + 0x82]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(130) /* 0x82 */);
    // 00433019  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 0043301a  ff154cf99e00           -call dword ptr [0x9ef94c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418508) /* 0x9ef94c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00433020  6a00                   -push 0
    app->getMemory<x86::reg32>(cpu.esp-4) = 0 /*0x0*/;
    cpu.esp -= 4;
    // 00433022  68c2020000             -push 0x2c2
    app->getMemory<x86::reg32>(cpu.esp-4) = 706 /*0x2c2*/;
    cpu.esp -= 4;
    // 00433027  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0043302d  8d656e                 -lea esp, [ebp + 0x6e]
    cpu.esp = x86::reg32(cpu.ebp + x86::reg32(110) /* 0x6e */);
    // 00433030  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00433031  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00433032  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00433033  c21400                 -ret 0x14
    cpu.esp += 4+20 /*0x14*/;
    return;
L_0x00433036:
    // 00433036  8b8d8e000000           -mov ecx, dword ptr [ebp + 0x8e]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(142) /* 0x8e */);
    // 0043303c  8b9d8a000000           -mov ebx, dword ptr [ebp + 0x8a]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(138) /* 0x8a */);
    // 00433042  8b9586000000           -mov edx, dword ptr [ebp + 0x86]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(134) /* 0x86 */);
    // 00433048  8b8582000000           -mov eax, dword ptr [ebp + 0x82]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(130) /* 0x82 */);
    // 0043304e  e88de90800             -call 0x4c19e0
    cpu.esp -= 4;
    sub_4c19e0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00433053:
    // 00433053  8d656e                 -lea esp, [ebp + 0x6e]
    cpu.esp = x86::reg32(cpu.ebp + x86::reg32(110) /* 0x6e */);
    // 00433056  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00433057  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00433058  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00433059  c21400                 -ret 0x14
    cpu.esp += 4+20 /*0x14*/;
    return;
}

/* align: skip 0x8d 0x44 0x20 0x00 */
void Application::sub_433060(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (quadSubdivided(app, cpu.sync())) /* port: native (tools/apply_native_render.py) */
    {
        cpu.reload();
        return;
    }
    // 00433060  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00433061  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00433062  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00433063  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00433065  83ec48                 -sub esp, 0x48
    (cpu.esp) -= x86::reg32(x86::sreg32(72 /*0x48*/));
    // 00433068  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 0043306b  89d6                   -mov esi, edx
    cpu.esi = cpu.edx;
    // 0043306d  895df8                 -mov dword ptr [ebp - 8], ebx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.ebx;
    // 00433070  89cf                   -mov edi, ecx
    cpu.edi = cpu.ecx;
    // 00433072  8b55fc                 -mov edx, dword ptr [ebp - 4]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00433075  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00433077  8a4214                 -mov al, byte ptr [edx + 0x14]
    cpu.al = app->getMemory<x86::reg8>(cpu.edx + x86::reg32(20) /* 0x14 */);
    // 0043307a  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 0043307c  8a5614                 -mov dl, byte ptr [esi + 0x14]
    cpu.dl = app->getMemory<x86::reg8>(cpu.esi + x86::reg32(20) /* 0x14 */);
    // 0043307f  21c2                   -and edx, eax
    cpu.edx &= x86::reg32(x86::sreg32(cpu.eax));
    // 00433081  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00433083  8a4314                 -mov al, byte ptr [ebx + 0x14]
    cpu.al = app->getMemory<x86::reg8>(cpu.ebx + x86::reg32(20) /* 0x14 */);
    // 00433086  21c2                   -and edx, eax
    cpu.edx &= x86::reg32(x86::sreg32(cpu.eax));
    // 00433088  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 0043308a  8a4114                 -mov al, byte ptr [ecx + 0x14]
    cpu.al = app->getMemory<x86::reg8>(cpu.ecx + x86::reg32(20) /* 0x14 */);
    // 0043308d  85c2                   +test edx, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.eax));
    // 0043308f  0f8515020000           -jne 0x4332aa
    if (!cpu.flags.zf)
    {
        goto L_0x004332aa;
    }
    // 00433095  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00433098  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 0043309a  e8f1f5ffff             -call 0x432690
    cpu.esp -= 4;
    sub_432690(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0043309f  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004330a1  0f85a5000000           -jne 0x43314c
    if (!cpu.flags.zf)
    {
        goto L_0x0043314c;
    }
    // 004330a7  8b55fc                 -mov edx, dword ptr [ebp - 4]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004330aa  8b4614                 -mov eax, dword ptr [esi + 0x14]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(20) /* 0x14 */);
    // 004330ad  8b5214                 -mov edx, dword ptr [edx + 0x14]
    cpu.edx = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(20) /* 0x14 */);
    // 004330b0  83e010                 -and eax, 0x10
    cpu.eax &= x86::reg32(x86::sreg32(16 /*0x10*/));
    // 004330b3  83e210                 -and edx, 0x10
    cpu.edx &= x86::reg32(x86::sreg32(16 /*0x10*/));
    // 004330b6  09d0                   -or eax, edx
    cpu.eax |= x86::reg32(x86::sreg32(cpu.edx));
    // 004330b8  8b55f8                 -mov edx, dword ptr [ebp - 8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004330bb  8b5214                 -mov edx, dword ptr [edx + 0x14]
    cpu.edx = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(20) /* 0x14 */);
    // 004330be  83e210                 -and edx, 0x10
    cpu.edx &= x86::reg32(x86::sreg32(16 /*0x10*/));
    // 004330c1  09d0                   -or eax, edx
    cpu.eax |= x86::reg32(x86::sreg32(cpu.edx));
    // 004330c3  8b5714                 -mov edx, dword ptr [edi + 0x14]
    cpu.edx = app->getMemory<x86::reg32>(cpu.edi + x86::reg32(20) /* 0x14 */);
    // 004330c6  83e210                 -and edx, 0x10
    cpu.edx &= x86::reg32(x86::sreg32(16 /*0x10*/));
    // 004330c9  09d0                   +or eax, edx
    cpu.clear_co();
    cpu.set_szp((cpu.eax |= x86::reg32(x86::sreg32(cpu.edx))));
    // 004330cb  756a                   -jne 0x433137
    if (!cpu.flags.zf)
    {
        goto L_0x00433137;
    }
    // 004330cd  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004330d0  8b5614                 -mov edx, dword ptr [esi + 0x14]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(20) /* 0x14 */);
    // 004330d3  8b4014                 -mov eax, dword ptr [eax + 0x14]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */);
    // 004330d6  83e201                 -and edx, 1
    cpu.edx &= x86::reg32(x86::sreg32(1 /*0x1*/));
    // 004330d9  83e001                 -and eax, 1
    cpu.eax &= x86::reg32(x86::sreg32(1 /*0x1*/));
    // 004330dc  09c2                   -or edx, eax
    cpu.edx |= x86::reg32(x86::sreg32(cpu.eax));
    // 004330de  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004330e1  8b4014                 -mov eax, dword ptr [eax + 0x14]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */);
    // 004330e4  83e001                 -and eax, 1
    cpu.eax &= x86::reg32(x86::sreg32(1 /*0x1*/));
    // 004330e7  09d0                   -or eax, edx
    cpu.eax |= x86::reg32(x86::sreg32(cpu.edx));
    // 004330e9  8b5714                 -mov edx, dword ptr [edi + 0x14]
    cpu.edx = app->getMemory<x86::reg32>(cpu.edi + x86::reg32(20) /* 0x14 */);
    // 004330ec  83e201                 -and edx, 1
    cpu.edx &= x86::reg32(x86::sreg32(1 /*0x1*/));
    // 004330ef  09d0                   +or eax, edx
    cpu.clear_co();
    cpu.set_szp((cpu.eax |= x86::reg32(x86::sreg32(cpu.edx))));
    // 004330f1  7515                   -jne 0x433108
    if (!cpu.flags.zf)
    {
        goto L_0x00433108;
    }
    // 004330f3  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004330f4  8b55f8                 -mov edx, dword ptr [ebp - 8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004330f7  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004330f8  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004330f9  8b4dfc                 -mov ecx, dword ptr [ebp - 4]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004330fc  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004330fd  ff154cf99e00           -call dword ptr [0x9ef94c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418508) /* 0x9ef94c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00433103  e9a2010000             -jmp 0x4332aa
    goto L_0x004332aa;
L_0x00433108:
    // 00433108  6a01                   -push 1
    app->getMemory<x86::reg32>(cpu.esp-4) = 1 /*0x1*/;
    cpu.esp -= 4;
    // 0043310a  68c2020000             -push 0x2c2
    app->getMemory<x86::reg32>(cpu.esp-4) = 706 /*0x2c2*/;
    cpu.esp -= 4;
    // 0043310f  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00433115  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00433116  8b5df8                 -mov ebx, dword ptr [ebp - 8]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 00433119  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 0043311a  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 0043311b  8b75fc                 -mov esi, dword ptr [ebp - 4]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 0043311e  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 0043311f  ff154cf99e00           -call dword ptr [0x9ef94c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418508) /* 0x9ef94c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00433125  6a00                   -push 0
    app->getMemory<x86::reg32>(cpu.esp-4) = 0 /*0x0*/;
    cpu.esp -= 4;
    // 00433127  68c2020000             -push 0x2c2
    app->getMemory<x86::reg32>(cpu.esp-4) = 706 /*0x2c2*/;
    cpu.esp -= 4;
    // 0043312c  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00433132  e973010000             -jmp 0x4332aa
    goto L_0x004332aa;
L_0x00433137:
    // 00433137  8b5df8                 -mov ebx, dword ptr [ebp - 8]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 0043313a  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 0043313d  89f9                   -mov ecx, edi
    cpu.ecx = cpu.edi;
    // 0043313f  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 00433141  e89ae80800             -call 0x4c19e0
    cpu.esp -= 4;
    sub_4c19e0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00433146  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00433148  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00433149  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043314a  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043314b  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x0043314c:
    // 0043314c  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 0043314f  8b400c                 -mov eax, dword ptr [eax + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
    // 00433152  8945f0                 -mov dword ptr [ebp - 0x10], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = cpu.eax;
    // 00433155  a9ffffff7f             +test eax, 0x7fffffff
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483647 /*0x7fffffff*/));
    // 0043315a  7507                   -jne 0x433163
    if (!cpu.flags.zf)
    {
        goto L_0x00433163;
    }
    // 0043315c  c745f080008037         -mov dword ptr [ebp - 0x10], 0x37800080
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = 931135616 /*0x37800080*/;
L_0x00433163:
    // 00433163  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00433166  d900                   -fld dword ptr [eax]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.eax));
    // 00433168  d825a4005600           -fsub dword ptr [0x5600a4]
    x86::Float fpu2 = cpu.fpu.sub(fpu1, x86::Float(app->getMemory<float>(x86::reg32(5636260) /* 0x5600a4 */)));
    // 0043316e  d945f0                 -fld dword ptr [ebp - 0x10]
    x86::Float fpu3 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-16) /* -0x10 */));
    // 00433171  d9c0                   -fld st(0)
    x86::Float fpu4 = x86::Float(fpu3);
    // 00433173  d80d9c005600           -fmul dword ptr [0x56009c]
    x86::Float fpu5 = cpu.fpu.mul(fpu4, x86::Float(app->getMemory<float>(x86::reg32(5636252) /* 0x56009c */)));
    // 00433179  defa                   -fdivp st(2)
    x86::Float fpu6 = cpu.fpu.div(fpu2, fpu5);
    // 0043317b  d9e8                   -fld1 
    x86::Float fpu7 = 1.0;
    // 0043317d  d8f1                   -fdiv st(1)
    x86::Float fpu8 = cpu.fpu.div(fpu7, x86::Float(fpu3));
    // 0043317f  d9ca                   -fxch st(2)
    
    // 00433181  d95db8                 -fstp dword ptr [ebp - 0x48]
    app->getMemory<float>(cpu.ebp + x86::reg32(-72) /* -0x48 */) = float(fpu6);
    // 00433184  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu9 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 00433187  d825a8005600           -fsub dword ptr [0x5600a8]
    x86::Float fpu10 = cpu.fpu.sub(fpu9, x86::Float(app->getMemory<float>(x86::reg32(5636264) /* 0x5600a8 */)));
    // 0043318d  d9c9                   -fxch st(1)
    
    // 0043318f  d80da0005600           -fmul dword ptr [0x5600a0]
    x86::Float fpu11 = cpu.fpu.mul(fpu3, x86::Float(app->getMemory<float>(x86::reg32(5636256) /* 0x5600a0 */)));
    // 00433195  def9                   -fdivp st(1)
    x86::Float fpu12 = cpu.fpu.div(fpu10, fpu11);
    // 00433197  d9c9                   -fxch st(1)
    
    // 00433199  d95dc0                 -fstp dword ptr [ebp - 0x40]
    app->getMemory<float>(cpu.ebp + x86::reg32(-64) /* -0x40 */) = float(fpu8);
    // 0043319c  d95dbc                 -fstp dword ptr [ebp - 0x44]
    app->getMemory<float>(cpu.ebp + x86::reg32(-68) /* -0x44 */) = float(fpu12);
    // 0043319f  8b460c                 -mov eax, dword ptr [esi + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 004331a2  8945f4                 -mov dword ptr [ebp - 0xc], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.eax;
    // 004331a5  a9ffffff7f             +test eax, 0x7fffffff
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483647 /*0x7fffffff*/));
    }
    // 004331aa  7507                   -jne 0x4331b3
    if (!cpu.flags.zf)
    {
        goto L_0x004331b3;
    }
    // 004331ac  c745f480008037         -mov dword ptr [ebp - 0xc], 0x37800080
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = 931135616 /*0x37800080*/;
L_0x004331b3:
    // 004331b3  d906                   -fld dword ptr [esi]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu13 = x86::Float(app->getMemory<float>(cpu.esi));
    // 004331b5  d825a4005600           -fsub dword ptr [0x5600a4]
    x86::Float fpu14 = cpu.fpu.sub(fpu13, x86::Float(app->getMemory<float>(x86::reg32(5636260) /* 0x5600a4 */)));
    // 004331bb  d945f4                 -fld dword ptr [ebp - 0xc]
    x86::Float fpu15 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */));
    // 004331be  d9c0                   -fld st(0)
    x86::Float fpu16 = x86::Float(fpu15);
    // 004331c0  d80d9c005600           -fmul dword ptr [0x56009c]
    x86::Float fpu17 = cpu.fpu.mul(fpu16, x86::Float(app->getMemory<float>(x86::reg32(5636252) /* 0x56009c */)));
    // 004331c6  defa                   -fdivp st(2)
    x86::Float fpu18 = cpu.fpu.div(fpu14, fpu17);
    // 004331c8  d9e8                   -fld1 
    x86::Float fpu19 = 1.0;
    // 004331ca  d8f1                   -fdiv st(1)
    x86::Float fpu20 = cpu.fpu.div(fpu19, x86::Float(fpu15));
    // 004331cc  d9ca                   -fxch st(2)
    
    // 004331ce  d95dc4                 -fstp dword ptr [ebp - 0x3c]
    app->getMemory<float>(cpu.ebp + x86::reg32(-60) /* -0x3c */) = float(fpu18);
    // 004331d1  d94604                 -fld dword ptr [esi + 4]
    x86::Float fpu21 = x86::Float(app->getMemory<float>(cpu.esi + x86::reg32(4) /* 0x4 */));
    // 004331d4  d825a8005600           -fsub dword ptr [0x5600a8]
    x86::Float fpu22 = cpu.fpu.sub(fpu21, x86::Float(app->getMemory<float>(x86::reg32(5636264) /* 0x5600a8 */)));
    // 004331da  d9c9                   -fxch st(1)
    
    // 004331dc  d80da0005600           -fmul dword ptr [0x5600a0]
    x86::Float fpu23 = cpu.fpu.mul(fpu15, x86::Float(app->getMemory<float>(x86::reg32(5636256) /* 0x5600a0 */)));
    // 004331e2  def9                   -fdivp st(1)
    x86::Float fpu24 = cpu.fpu.div(fpu22, fpu23);
    // 004331e4  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004331e7  d9c9                   -fxch st(1)
    
    // 004331e9  d95dcc                 -fstp dword ptr [ebp - 0x34]
    app->getMemory<float>(cpu.ebp + x86::reg32(-52) /* -0x34 */) = float(fpu20);
    // 004331ec  d95dc8                 -fstp dword ptr [ebp - 0x38]
    app->getMemory<float>(cpu.ebp + x86::reg32(-56) /* -0x38 */) = float(fpu24);
    // 004331ef  8b400c                 -mov eax, dword ptr [eax + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
    // 004331f2  8945ec                 -mov dword ptr [ebp - 0x14], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */) = cpu.eax;
    // 004331f5  a9ffffff7f             +test eax, 0x7fffffff
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483647 /*0x7fffffff*/));
    }
    // 004331fa  7507                   -jne 0x433203
    if (!cpu.flags.zf)
    {
        goto L_0x00433203;
    }
    // 004331fc  c745ec80008037         -mov dword ptr [ebp - 0x14], 0x37800080
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */) = 931135616 /*0x37800080*/;
L_0x00433203:
    // 00433203  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 00433206  d900                   -fld dword ptr [eax]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu25 = x86::Float(app->getMemory<float>(cpu.eax));
    // 00433208  d825a4005600           -fsub dword ptr [0x5600a4]
    x86::Float fpu26 = cpu.fpu.sub(fpu25, x86::Float(app->getMemory<float>(x86::reg32(5636260) /* 0x5600a4 */)));
    // 0043320e  d945ec                 -fld dword ptr [ebp - 0x14]
    x86::Float fpu27 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-20) /* -0x14 */));
    // 00433211  d9c0                   -fld st(0)
    x86::Float fpu28 = x86::Float(fpu27);
    // 00433213  d80d9c005600           -fmul dword ptr [0x56009c]
    x86::Float fpu29 = cpu.fpu.mul(fpu28, x86::Float(app->getMemory<float>(x86::reg32(5636252) /* 0x56009c */)));
    // 00433219  defa                   -fdivp st(2)
    x86::Float fpu30 = cpu.fpu.div(fpu26, fpu29);
    // 0043321b  d9e8                   -fld1 
    x86::Float fpu31 = 1.0;
    // 0043321d  d8f1                   -fdiv st(1)
    x86::Float fpu32 = cpu.fpu.div(fpu31, x86::Float(fpu27));
    // 0043321f  d9ca                   -fxch st(2)
    
    // 00433221  d95dd0                 -fstp dword ptr [ebp - 0x30]
    app->getMemory<float>(cpu.ebp + x86::reg32(-48) /* -0x30 */) = float(fpu30);
    // 00433224  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu33 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 00433227  d825a8005600           -fsub dword ptr [0x5600a8]
    x86::Float fpu34 = cpu.fpu.sub(fpu33, x86::Float(app->getMemory<float>(x86::reg32(5636264) /* 0x5600a8 */)));
    // 0043322d  d9c9                   -fxch st(1)
    
    // 0043322f  d80da0005600           -fmul dword ptr [0x5600a0]
    x86::Float fpu35 = cpu.fpu.mul(fpu27, x86::Float(app->getMemory<float>(x86::reg32(5636256) /* 0x5600a0 */)));
    // 00433235  def9                   -fdivp st(1)
    x86::Float fpu36 = cpu.fpu.div(fpu34, fpu35);
    // 00433237  d9c9                   -fxch st(1)
    
    // 00433239  d95dd8                 -fstp dword ptr [ebp - 0x28]
    app->getMemory<float>(cpu.ebp + x86::reg32(-40) /* -0x28 */) = float(fpu32);
    // 0043323c  d95dd4                 -fstp dword ptr [ebp - 0x2c]
    app->getMemory<float>(cpu.ebp + x86::reg32(-44) /* -0x2c */) = float(fpu36);
    // 0043323f  8b470c                 -mov eax, dword ptr [edi + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edi + x86::reg32(12) /* 0xc */);
    // 00433242  8945e8                 -mov dword ptr [ebp - 0x18], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-24) /* -0x18 */) = cpu.eax;
    // 00433245  a9ffffff7f             +test eax, 0x7fffffff
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483647 /*0x7fffffff*/));
    }
    // 0043324a  7507                   -jne 0x433253
    if (!cpu.flags.zf)
    {
        goto L_0x00433253;
    }
    // 0043324c  c745e880008037         -mov dword ptr [ebp - 0x18], 0x37800080
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-24) /* -0x18 */) = 931135616 /*0x37800080*/;
L_0x00433253:
    // 00433253  d907                   -fld dword ptr [edi]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu37 = x86::Float(app->getMemory<float>(cpu.edi));
    // 00433255  d825a4005600           -fsub dword ptr [0x5600a4]
    x86::Float fpu38 = cpu.fpu.sub(fpu37, x86::Float(app->getMemory<float>(x86::reg32(5636260) /* 0x5600a4 */)));
    // 0043325b  d945e8                 -fld dword ptr [ebp - 0x18]
    x86::Float fpu39 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-24) /* -0x18 */));
    // 0043325e  d9c0                   -fld st(0)
    x86::Float fpu40 = x86::Float(fpu39);
    // 00433260  d80d9c005600           -fmul dword ptr [0x56009c]
    x86::Float fpu41 = cpu.fpu.mul(fpu40, x86::Float(app->getMemory<float>(x86::reg32(5636252) /* 0x56009c */)));
    // 00433266  defa                   -fdivp st(2)
    x86::Float fpu42 = cpu.fpu.div(fpu38, fpu41);
    // 00433268  d9e8                   -fld1 
    x86::Float fpu43 = 1.0;
    // 0043326a  d8f1                   -fdiv st(1)
    x86::Float fpu44 = cpu.fpu.div(fpu43, x86::Float(fpu39));
    // 0043326c  d9ca                   -fxch st(2)
    
    // 0043326e  d95ddc                 -fstp dword ptr [ebp - 0x24]
    app->getMemory<float>(cpu.ebp + x86::reg32(-36) /* -0x24 */) = float(fpu42);
    // 00433271  d94704                 -fld dword ptr [edi + 4]
    x86::Float fpu45 = x86::Float(app->getMemory<float>(cpu.edi + x86::reg32(4) /* 0x4 */));
    // 00433274  d825a8005600           -fsub dword ptr [0x5600a8]
    x86::Float fpu46 = cpu.fpu.sub(fpu45, x86::Float(app->getMemory<float>(x86::reg32(5636264) /* 0x5600a8 */)));
    // 0043327a  d9c9                   -fxch st(1)
    
    // 0043327c  d80da0005600           -fmul dword ptr [0x5600a0]
    x86::Float fpu47 = cpu.fpu.mul(fpu39, x86::Float(app->getMemory<float>(x86::reg32(5636256) /* 0x5600a0 */)));
    // 00433282  def9                   -fdivp st(1)
    x86::Float fpu48 = cpu.fpu.div(fpu46, fpu47);
    // 00433284  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00433285  8b55f8                 -mov edx, dword ptr [ebp - 8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 00433288  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00433289  8b4dfc                 -mov ecx, dword ptr [ebp - 4]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 0043328c  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 0043328d  8d45dc                 -lea eax, [ebp - 0x24]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-36) /* -0x24 */);
    // 00433290  8d5dc4                 -lea ebx, [ebp - 0x3c]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-60) /* -0x3c */);
    // 00433293  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00433294  8d55b8                 -lea edx, [ebp - 0x48]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-72) /* -0x48 */);
    // 00433297  8d4dd0                 -lea ecx, [ebp - 0x30]
    cpu.ecx = x86::reg32(cpu.ebp + x86::reg32(-48) /* -0x30 */);
    // 0043329a  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 0043329b  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 0043329d  d9c9                   -fxch st(1)
    
    // 0043329f  d95de4                 -fstp dword ptr [ebp - 0x1c]
    app->getMemory<float>(cpu.ebp + x86::reg32(-28) /* -0x1c */) = float(fpu44);
    // 004332a2  d95de0                 -fstp dword ptr [ebp - 0x20]
    app->getMemory<float>(cpu.ebp + x86::reg32(-32) /* -0x20 */) = float(fpu48);
    }
    // 004332a5  e876f4ffff             -call 0x432720
    cpu.esp -= 4;
    sub_432720(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x004332aa:
    // 004332aa  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004332ac  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004332ad  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004332ae  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004332af  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip  */
void Application::sub_4332b0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (quadRecords(app, cpu.sync())) /* port: native (tools/apply_native_render.py) */
    {
        cpu.reload();
        return;
    }
    // 004332b0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004332b1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004332b2  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004332b3  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004332b4  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004332b5  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004332b6  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004332b8  83ec0c                 -sub esp, 0xc
    (cpu.esp) -= x86::reg32(x86::sreg32(12 /*0xc*/));
    // 004332bb  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
L_0x004332bd:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004332bd  8b460c                 -mov eax, dword ptr [esi + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 004332c0  8945f8                 -mov dword ptr [ebp - 8], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.eax;
    // 004332c3  8b4614                 -mov eax, dword ptr [esi + 0x14]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(20) /* 0x14 */);
    // 004332c6  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 004332c9  8b4604                 -mov eax, dword ptr [esi + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 004332cc  c1f810                 -sar eax, 0x10
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (16 /*0x10*/ % 32));
    // 004332cf  8b7e08                 -mov edi, dword ptr [esi + 8]
    cpu.edi = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(8) /* 0x8 */);
    // 004332d2  8945f4                 -mov dword ptr [ebp - 0xc], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.eax;
    // 004332d5  8b5e10                 -mov ebx, dword ptr [esi + 0x10]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(16) /* 0x10 */);
    // 004332d8  8a65f4                 -mov ah, byte ptr [ebp - 0xc]
    cpu.ah = app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 004332db  f6c401                 +test ah, 1
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.ah & 1 /*0x1*/));
    // 004332de  741f                   -je 0x4332ff
    if (cpu.flags.zf)
    {
        goto L_0x004332ff;
    }
    // 004332e0  833d584e550001         +cmp dword ptr [0x554e58], 1
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5590616) /* 0x554e58 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1 /*0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004332e7  7430                   -je 0x433319
    if (cpu.flags.zf)
    {
        goto L_0x00433319;
    }
    // 004332e9  b901000000             -mov ecx, 1
    cpu.ecx = 1 /*0x1*/;
    // 004332ee  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004332ef  6a68                   -push 0x68
    app->getMemory<x86::reg32>(cpu.esp-4) = 104 /*0x68*/;
    cpu.esp -= 4;
    // 004332f1  890d584e5500           -mov dword ptr [0x554e58], ecx
    app->getMemory<x86::reg32>(x86::reg32(5590616) /* 0x554e58 */) = cpu.ecx;
    // 004332f7  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004332fd  eb1a                   -jmp 0x433319
    goto L_0x00433319;
L_0x004332ff:
    // 004332ff  833d584e550000         +cmp dword ptr [0x554e58], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5590616) /* 0x554e58 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00433306  7411                   -je 0x433319
    if (cpu.flags.zf)
    {
        goto L_0x00433319;
    }
    // 00433308  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 0043330a  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 0043330b  6a68                   -push 0x68
    app->getMemory<x86::reg32>(cpu.esp-4) = 104 /*0x68*/;
    cpu.esp -= 4;
    // 0043330d  8915584e5500           -mov dword ptr [0x554e58], edx
    app->getMemory<x86::reg32>(x86::reg32(5590616) /* 0x554e58 */) = cpu.edx;
    // 00433313  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00433319:
    // 00433319  8b4e18                 -mov ecx, dword ptr [esi + 0x18]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(24) /* 0x18 */);
    // 0043331c  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    // 0043331e  0f847a000000           -je 0x43339e
    if (cpu.flags.zf)
    {
        goto L_0x0043339e;
    }
    // 00433324  f645f402               +test byte ptr [ebp - 0xc], 2
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-12) /* -0xc */) & 2 /*0x2*/));
    // 00433328  7553                   -jne 0x43337d
    if (!cpu.flags.zf)
    {
        goto L_0x0043337d;
    }
    // 0043332a  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 0043332c  8b5008                 -mov edx, dword ptr [eax + 8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 0043332f  895718                 -mov dword ptr [edi + 0x18], edx
    app->getMemory<x86::reg32>(cpu.edi + x86::reg32(24) /* 0x18 */) = cpu.edx;
    // 00433332  8b4618                 -mov eax, dword ptr [esi + 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(24) /* 0x18 */);
    // 00433335  8b500c                 -mov edx, dword ptr [eax + 0xc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
    // 00433338  89571c                 -mov dword ptr [edi + 0x1c], edx
    app->getMemory<x86::reg32>(cpu.edi + x86::reg32(28) /* 0x1c */) = cpu.edx;
    // 0043333b  8b4618                 -mov eax, dword ptr [esi + 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(24) /* 0x18 */);
    // 0043333e  d94010                 -fld dword ptr [eax + 0x10]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(16) /* 0x10 */));
    // 00433341  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 00433344  d95818                 -fstp dword ptr [eax + 0x18]
    app->getMemory<float>(cpu.eax + x86::reg32(24) /* 0x18 */) = float(fpu1);
    // 00433347  8b4618                 -mov eax, dword ptr [esi + 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(24) /* 0x18 */);
    // 0043334a  d94014                 -fld dword ptr [eax + 0x14]
    x86::Float fpu2 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(20) /* 0x14 */));
    // 0043334d  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 00433350  d9581c                 -fstp dword ptr [eax + 0x1c]
    app->getMemory<float>(cpu.eax + x86::reg32(28) /* 0x1c */) = float(fpu2);
    // 00433353  8b4618                 -mov eax, dword ptr [esi + 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(24) /* 0x18 */);
    // 00433356  8b5018                 -mov edx, dword ptr [eax + 0x18]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */);
    // 00433359  895318                 -mov dword ptr [ebx + 0x18], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(24) /* 0x18 */) = cpu.edx;
    // 0043335c  8b4618                 -mov eax, dword ptr [esi + 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(24) /* 0x18 */);
    // 0043335f  8b501c                 -mov edx, dword ptr [eax + 0x1c]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(28) /* 0x1c */);
    // 00433362  89531c                 -mov dword ptr [ebx + 0x1c], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(28) /* 0x1c */) = cpu.edx;
    // 00433365  8b4618                 -mov eax, dword ptr [esi + 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(24) /* 0x18 */);
    // 00433368  d94020                 -fld dword ptr [eax + 0x20]
    x86::Float fpu3 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(32) /* 0x20 */));
    // 0043336b  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 0043336e  d95818                 -fstp dword ptr [eax + 0x18]
    app->getMemory<float>(cpu.eax + x86::reg32(24) /* 0x18 */) = float(fpu3);
    // 00433371  8b4618                 -mov eax, dword ptr [esi + 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(24) /* 0x18 */);
    // 00433374  d94024                 -fld dword ptr [eax + 0x24]
    x86::Float fpu4 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(36) /* 0x24 */));
    // 00433377  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 0043337a  d9581c                 -fstp dword ptr [eax + 0x1c]
    app->getMemory<float>(cpu.eax + x86::reg32(28) /* 0x1c */) = float(fpu4);
    }
L_0x0043337d:
    // 0043337d  8b4618                 -mov eax, dword ptr [esi + 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(24) /* 0x18 */);
    // 00433380  8b15544e5500           -mov edx, dword ptr [0x554e54]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5590612) /* 0x554e54 */);
    // 00433386  8b4804                 -mov ecx, dword ptr [eax + 4]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 00433389  39ca                   +cmp edx, ecx
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ecx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0043338b  742a                   -je 0x4333b7
    if (cpu.flags.zf)
    {
        goto L_0x004333b7;
    }
    // 0043338d  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 0043338e  6a01                   -push 1
    app->getMemory<x86::reg32>(cpu.esp-4) = 1 /*0x1*/;
    cpu.esp -= 4;
    // 00433390  890d544e5500           -mov dword ptr [0x554e54], ecx
    app->getMemory<x86::reg32>(x86::reg32(5590612) /* 0x554e54 */) = cpu.ecx;
    // 00433396  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0043339c  eb19                   -jmp 0x4333b7
    goto L_0x004333b7;
L_0x0043339e:
    // 0043339e  833d544e550000         +cmp dword ptr [0x554e54], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5590612) /* 0x554e54 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004333a5  7410                   -je 0x4333b7
    if (cpu.flags.zf)
    {
        goto L_0x004333b7;
    }
    // 004333a7  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 004333a9  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004333aa  6a01                   -push 1
    app->getMemory<x86::reg32>(cpu.esp-4) = 1 /*0x1*/;
    cpu.esp -= 4;
    // 004333ac  a3544e5500             -mov dword ptr [0x554e54], eax
    app->getMemory<x86::reg32>(x86::reg32(5590612) /* 0x554e54 */) = cpu.eax;
    // 004333b1  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x004333b7:
    // 004333b7  8b5618                 -mov edx, dword ptr [esi + 0x18]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(24) /* 0x18 */);
    // 004333ba  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 004333bc  740e                   -je 0x4333cc
    if (cpu.flags.zf)
    {
        goto L_0x004333cc;
    }
    // 004333be  f6422808               +test byte ptr [edx + 0x28], 8
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(cpu.edx + x86::reg32(40) /* 0x28 */) & 8 /*0x8*/));
    // 004333c2  7408                   -je 0x4333cc
    if (cpu.flags.zf)
    {
        goto L_0x004333cc;
    }
    // 004333c4  8b4710                 -mov eax, dword ptr [edi + 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edi + x86::reg32(16) /* 0x10 */);
    // 004333c7  e8c4efffff             -call 0x432390
    cpu.esp -= 4;
    nfs3hp::graphics::setSoftwareBlendColour(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x004333cc:
    // 004333cc  f645f408               +test byte ptr [ebp - 0xc], 8
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-12) /* -0xc */) & 8 /*0x8*/));
    // 004333d0  7412                   -je 0x4333e4
    if (cpu.flags.zf)
    {
        goto L_0x004333e4;
    }
    // 004333d2  8b4dfc                 -mov ecx, dword ptr [ebp - 4]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004333d5  8b55f8                 -mov edx, dword ptr [ebp - 8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004333d8  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 004333da  e881fcffff             -call 0x433060
    cpu.esp -= 4;
    sub_433060(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004333df  e90c010000             -jmp 0x4334f0
    goto L_0x004334f0;
L_0x004333e4:
    // 004333e4  8b4e18                 -mov ecx, dword ptr [esi + 0x18]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(24) /* 0x18 */);
    // 004333e7  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    // 004333e9  0f84f4000000           -je 0x4334e3
    if (cpu.flags.zf)
    {
        goto L_0x004334e3;
    }
    // 004333ef  f6412810               +test byte ptr [ecx + 0x28], 0x10
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(cpu.ecx + x86::reg32(40) /* 0x28 */) & 16 /*0x10*/));
    // 004333f3  0f84ea000000           -je 0x4334e3
    if (cpu.flags.zf)
    {
        goto L_0x004334e3;
    }
    // 004333f9  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004333fc  8b5714                 -mov edx, dword ptr [edi + 0x14]
    cpu.edx = app->getMemory<x86::reg32>(cpu.edi + x86::reg32(20) /* 0x14 */);
    // 004333ff  8b4014                 -mov eax, dword ptr [eax + 0x14]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */);
    // 00433402  83e210                 -and edx, 0x10
    cpu.edx &= x86::reg32(x86::sreg32(16 /*0x10*/));
    // 00433405  83e010                 -and eax, 0x10
    cpu.eax &= x86::reg32(x86::sreg32(16 /*0x10*/));
    // 00433408  09d0                   -or eax, edx
    cpu.eax |= x86::reg32(x86::sreg32(cpu.edx));
    // 0043340a  8b5314                 -mov edx, dword ptr [ebx + 0x14]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(20) /* 0x14 */);
    // 0043340d  83e210                 -and edx, 0x10
    cpu.edx &= x86::reg32(x86::sreg32(16 /*0x10*/));
    // 00433410  09c2                   -or edx, eax
    cpu.edx |= x86::reg32(x86::sreg32(cpu.eax));
    // 00433412  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00433415  8b4014                 -mov eax, dword ptr [eax + 0x14]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */);
    // 00433418  83e010                 -and eax, 0x10
    cpu.eax &= x86::reg32(x86::sreg32(16 /*0x10*/));
    // 0043341b  09d0                   +or eax, edx
    cpu.clear_co();
    cpu.set_szp((cpu.eax |= x86::reg32(x86::sreg32(cpu.edx))));
    // 0043341d  0f8595000000           -jne 0x4334b8
    if (!cpu.flags.zf)
    {
        goto L_0x004334b8;
    }
    // 00433423  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 00433426  8b5714                 -mov edx, dword ptr [edi + 0x14]
    cpu.edx = app->getMemory<x86::reg32>(cpu.edi + x86::reg32(20) /* 0x14 */);
    // 00433429  8b4014                 -mov eax, dword ptr [eax + 0x14]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */);
    // 0043342c  83e201                 -and edx, 1
    cpu.edx &= x86::reg32(x86::sreg32(1 /*0x1*/));
    // 0043342f  83e001                 -and eax, 1
    cpu.eax &= x86::reg32(x86::sreg32(1 /*0x1*/));
    // 00433432  09c2                   -or edx, eax
    cpu.edx |= x86::reg32(x86::sreg32(cpu.eax));
    // 00433434  8b4314                 -mov eax, dword ptr [ebx + 0x14]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(20) /* 0x14 */);
    // 00433437  83e001                 -and eax, 1
    cpu.eax &= x86::reg32(x86::sreg32(1 /*0x1*/));
    // 0043343a  09d0                   -or eax, edx
    cpu.eax |= x86::reg32(x86::sreg32(cpu.edx));
    // 0043343c  8b55fc                 -mov edx, dword ptr [ebp - 4]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 0043343f  8b5214                 -mov edx, dword ptr [edx + 0x14]
    cpu.edx = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(20) /* 0x14 */);
    // 00433442  83e201                 -and edx, 1
    cpu.edx &= x86::reg32(x86::sreg32(1 /*0x1*/));
    // 00433445  09d0                   +or eax, edx
    cpu.clear_co();
    cpu.set_szp((cpu.eax |= x86::reg32(x86::sreg32(cpu.edx))));
    // 00433447  7523                   -jne 0x43346c
    if (!cpu.flags.zf)
    {
        goto L_0x0043346c;
    }
    // 00433449  8b4dfc                 -mov ecx, dword ptr [ebp - 4]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 0043344c  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 0043344d  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 0043344e  8b5df8                 -mov ebx, dword ptr [ebp - 8]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 00433451  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00433452  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00433453  ff154cf99e00           -call dword ptr [0x9ef94c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418508) /* 0x9ef94c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00433459  8b36                   -mov esi, dword ptr [esi]
    cpu.esi = app->getMemory<x86::reg32>(cpu.esi);
    // 0043345b  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 0043345d  0f84b4000000           -je 0x433517
    if (cpu.flags.zf)
    {
        goto L_0x00433517;
    }
    // 00433463  668b4604               -mov ax, word ptr [esi + 4]
    cpu.ax = app->getMemory<x86::reg16>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 00433467  e9a2000000             -jmp 0x43350e
    goto L_0x0043350e;
L_0x0043346c:
    // 0043346c  6a01                   -push 1
    app->getMemory<x86::reg32>(cpu.esp-4) = 1 /*0x1*/;
    cpu.esp -= 4;
    // 0043346e  68c2020000             -push 0x2c2
    app->getMemory<x86::reg32>(cpu.esp-4) = 706 /*0x2c2*/;
    cpu.esp -= 4;
    // 00433473  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00433479  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 0043347c  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 0043347d  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 0043347e  8b55f8                 -mov edx, dword ptr [ebp - 8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 00433481  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00433482  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00433483  ff154cf99e00           -call dword ptr [0x9ef94c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418508) /* 0x9ef94c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00433489  6a00                   -push 0
    app->getMemory<x86::reg32>(cpu.esp-4) = 0 /*0x0*/;
    cpu.esp -= 4;
    // 0043348b  68c2020000             -push 0x2c2
    app->getMemory<x86::reg32>(cpu.esp-4) = 706 /*0x2c2*/;
    cpu.esp -= 4;
    // 00433490  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00433496  8b36                   -mov esi, dword ptr [esi]
    cpu.esi = app->getMemory<x86::reg32>(cpu.esi);
    // 00433498  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 0043349a  0f8477000000           -je 0x433517
    if (cpu.flags.zf)
    {
        goto L_0x00433517;
    }
    // 004334a0  668b4604               -mov ax, word ptr [esi + 4]
    cpu.ax = app->getMemory<x86::reg16>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 004334a4  6685c0                 +test ax, ax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg16>(cpu.ax & cpu.ax));
    // 004334a7  0f8410feffff           -je 0x4332bd
    if (cpu.flags.zf)
    {
        goto L_0x004332bd;
    }
    // 004334ad  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004334af  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004334b1  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004334b2  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004334b3  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004334b4  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004334b5  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004334b6  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004334b7  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004334b8:
    // 004334b8  8b4dfc                 -mov ecx, dword ptr [ebp - 4]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004334bb  8b55f8                 -mov edx, dword ptr [ebp - 8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004334be  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 004334c0  e81be50800             -call 0x4c19e0
    cpu.esp -= 4;
    sub_4c19e0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004334c5  8b36                   -mov esi, dword ptr [esi]
    cpu.esi = app->getMemory<x86::reg32>(cpu.esi);
    // 004334c7  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 004334c9  744c                   -je 0x433517
    if (cpu.flags.zf)
    {
        goto L_0x00433517;
    }
    // 004334cb  668b4604               -mov ax, word ptr [esi + 4]
    cpu.ax = app->getMemory<x86::reg16>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 004334cf  6685c0                 +test ax, ax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg16>(cpu.ax & cpu.ax));
    // 004334d2  0f84e5fdffff           -je 0x4332bd
    if (cpu.flags.zf)
    {
        goto L_0x004332bd;
    }
    // 004334d8  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004334da  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004334dc  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004334dd  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004334de  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004334df  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004334e0  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004334e1  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004334e2  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004334e3:
    // 004334e3  8b4dfc                 -mov ecx, dword ptr [ebp - 4]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004334e6  8b55f8                 -mov edx, dword ptr [ebp - 8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004334e9  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 004334eb  e810e40800             -call 0x4c1900
    cpu.esp -= 4;
    sub_4c1900(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x004334f0:
    // 004334f0  8b36                   -mov esi, dword ptr [esi]
    cpu.esi = app->getMemory<x86::reg32>(cpu.esi);
    // 004334f2  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 004334f4  7421                   -je 0x433517
    if (cpu.flags.zf)
    {
        goto L_0x00433517;
    }
    // 004334f6  668b4604               -mov ax, word ptr [esi + 4]
    cpu.ax = app->getMemory<x86::reg16>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 004334fa  6685c0                 +test ax, ax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg16>(cpu.ax & cpu.ax));
    // 004334fd  0f84bafdffff           -je 0x4332bd
    if (cpu.flags.zf)
    {
        goto L_0x004332bd;
    }
    // 00433503  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 00433505  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00433507  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00433508  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00433509  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043350a  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043350b  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043350c  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043350d  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x0043350e:
    // 0043350e  6685c0                 +test ax, ax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg16>(cpu.ax & cpu.ax));
    // 00433511  0f84a6fdffff           -je 0x4332bd
    if (cpu.flags.zf)
    {
        goto L_0x004332bd;
    }
L_0x00433517:
    // 00433517  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 00433519  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 0043351b  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043351c  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043351d  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043351e  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043351f  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00433520  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00433521  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x8b 0xc0 */
void Application::sub_433530(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00433530  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00433531  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00433532  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00433533  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00433534  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00433535  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00433536  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00433538  83ec08                 -sub esp, 8
    (cpu.esp) -= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 0043353b  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
L_0x0043353d:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 0043353d  8b460c                 -mov eax, dword ptr [esi + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 00433540  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 00433543  8b4604                 -mov eax, dword ptr [esi + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 00433546  c1f810                 -sar eax, 0x10
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (16 /*0x10*/ % 32));
    // 00433549  8b7e08                 -mov edi, dword ptr [esi + 8]
    cpu.edi = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(8) /* 0x8 */);
    // 0043354c  8945f8                 -mov dword ptr [ebp - 8], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.eax;
    // 0043354f  8b5e10                 -mov ebx, dword ptr [esi + 0x10]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(16) /* 0x10 */);
    // 00433552  8a65f8                 -mov ah, byte ptr [ebp - 8]
    cpu.ah = app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 00433555  f6c401                 +test ah, 1
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.ah & 1 /*0x1*/));
    // 00433558  741f                   -je 0x433579
    if (cpu.flags.zf)
    {
        goto L_0x00433579;
    }
    // 0043355a  833d584e550001         +cmp dword ptr [0x554e58], 1
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5590616) /* 0x554e58 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1 /*0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00433561  7430                   -je 0x433593
    if (cpu.flags.zf)
    {
        goto L_0x00433593;
    }
    // 00433563  b901000000             -mov ecx, 1
    cpu.ecx = 1 /*0x1*/;
    // 00433568  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00433569  6a68                   -push 0x68
    app->getMemory<x86::reg32>(cpu.esp-4) = 104 /*0x68*/;
    cpu.esp -= 4;
    // 0043356b  890d584e5500           -mov dword ptr [0x554e58], ecx
    app->getMemory<x86::reg32>(x86::reg32(5590616) /* 0x554e58 */) = cpu.ecx;
    // 00433571  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00433577  eb1a                   -jmp 0x433593
    goto L_0x00433593;
L_0x00433579:
    // 00433579  833d584e550000         +cmp dword ptr [0x554e58], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5590616) /* 0x554e58 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00433580  7411                   -je 0x433593
    if (cpu.flags.zf)
    {
        goto L_0x00433593;
    }
    // 00433582  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00433584  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00433585  6a68                   -push 0x68
    app->getMemory<x86::reg32>(cpu.esp-4) = 104 /*0x68*/;
    cpu.esp -= 4;
    // 00433587  8915584e5500           -mov dword ptr [0x554e58], edx
    app->getMemory<x86::reg32>(x86::reg32(5590616) /* 0x554e58 */) = cpu.edx;
    // 0043358d  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00433593:
    // 00433593  8b4e18                 -mov ecx, dword ptr [esi + 0x18]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(24) /* 0x18 */);
    // 00433596  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    // 00433598  7462                   -je 0x4335fc
    if (cpu.flags.zf)
    {
        goto L_0x004335fc;
    }
    // 0043359a  f645f802               +test byte ptr [ebp - 8], 2
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-8) /* -0x8 */) & 2 /*0x2*/));
    // 0043359e  753b                   -jne 0x4335db
    if (!cpu.flags.zf)
    {
        goto L_0x004335db;
    }
    // 004335a0  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004335a2  8b5008                 -mov edx, dword ptr [eax + 8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 004335a5  895718                 -mov dword ptr [edi + 0x18], edx
    app->getMemory<x86::reg32>(cpu.edi + x86::reg32(24) /* 0x18 */) = cpu.edx;
    // 004335a8  8b4618                 -mov eax, dword ptr [esi + 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(24) /* 0x18 */);
    // 004335ab  8b500c                 -mov edx, dword ptr [eax + 0xc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
    // 004335ae  89571c                 -mov dword ptr [edi + 0x1c], edx
    app->getMemory<x86::reg32>(cpu.edi + x86::reg32(28) /* 0x1c */) = cpu.edx;
    // 004335b1  8b4618                 -mov eax, dword ptr [esi + 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(24) /* 0x18 */);
    // 004335b4  d94010                 -fld dword ptr [eax + 0x10]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(16) /* 0x10 */));
    // 004335b7  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004335ba  d95818                 -fstp dword ptr [eax + 0x18]
    app->getMemory<float>(cpu.eax + x86::reg32(24) /* 0x18 */) = float(fpu1);
    // 004335bd  8b4618                 -mov eax, dword ptr [esi + 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(24) /* 0x18 */);
    // 004335c0  d94014                 -fld dword ptr [eax + 0x14]
    x86::Float fpu2 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(20) /* 0x14 */));
    // 004335c3  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004335c6  d9581c                 -fstp dword ptr [eax + 0x1c]
    app->getMemory<float>(cpu.eax + x86::reg32(28) /* 0x1c */) = float(fpu2);
    // 004335c9  8b4618                 -mov eax, dword ptr [esi + 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(24) /* 0x18 */);
    // 004335cc  8b5018                 -mov edx, dword ptr [eax + 0x18]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */);
    // 004335cf  895318                 -mov dword ptr [ebx + 0x18], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(24) /* 0x18 */) = cpu.edx;
    // 004335d2  8b4618                 -mov eax, dword ptr [esi + 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(24) /* 0x18 */);
    // 004335d5  8b501c                 -mov edx, dword ptr [eax + 0x1c]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(28) /* 0x1c */);
    // 004335d8  89531c                 -mov dword ptr [ebx + 0x1c], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(28) /* 0x1c */) = cpu.edx;
    }
L_0x004335db:
    // 004335db  8b4618                 -mov eax, dword ptr [esi + 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(24) /* 0x18 */);
    // 004335de  8b15544e5500           -mov edx, dword ptr [0x554e54]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5590612) /* 0x554e54 */);
    // 004335e4  8b4804                 -mov ecx, dword ptr [eax + 4]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 004335e7  39ca                   +cmp edx, ecx
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ecx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004335e9  742a                   -je 0x433615
    if (cpu.flags.zf)
    {
        goto L_0x00433615;
    }
    // 004335eb  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004335ec  6a01                   -push 1
    app->getMemory<x86::reg32>(cpu.esp-4) = 1 /*0x1*/;
    cpu.esp -= 4;
    // 004335ee  890d544e5500           -mov dword ptr [0x554e54], ecx
    app->getMemory<x86::reg32>(x86::reg32(5590612) /* 0x554e54 */) = cpu.ecx;
    // 004335f4  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004335fa  eb19                   -jmp 0x433615
    goto L_0x00433615;
L_0x004335fc:
    // 004335fc  833d544e550000         +cmp dword ptr [0x554e54], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5590612) /* 0x554e54 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00433603  7410                   -je 0x433615
    if (cpu.flags.zf)
    {
        goto L_0x00433615;
    }
    // 00433605  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00433607  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00433608  6a01                   -push 1
    app->getMemory<x86::reg32>(cpu.esp-4) = 1 /*0x1*/;
    cpu.esp -= 4;
    // 0043360a  a3544e5500             -mov dword ptr [0x554e54], eax
    app->getMemory<x86::reg32>(x86::reg32(5590612) /* 0x554e54 */) = cpu.eax;
    // 0043360f  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00433615:
    // 00433615  8b5618                 -mov edx, dword ptr [esi + 0x18]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(24) /* 0x18 */);
    // 00433618  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 0043361a  740e                   -je 0x43362a
    if (cpu.flags.zf)
    {
        goto L_0x0043362a;
    }
    // 0043361c  f6422808               +test byte ptr [edx + 0x28], 8
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(cpu.edx + x86::reg32(40) /* 0x28 */) & 8 /*0x8*/));
    // 00433620  7408                   -je 0x43362a
    if (cpu.flags.zf)
    {
        goto L_0x0043362a;
    }
    // 00433622  8b4710                 -mov eax, dword ptr [edi + 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edi + x86::reg32(16) /* 0x10 */);
    // 00433625  e866edffff             -call 0x432390
    cpu.esp -= 4;
    nfs3hp::graphics::setSoftwareBlendColour(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x0043362a:
    // 0043362a  8b55fc                 -mov edx, dword ptr [ebp - 4]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 0043362d  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 0043362f  e87cdb0800             -call 0x4c11b0
    cpu.esp -= 4;
    sub_4c11b0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00433634  8b36                   -mov esi, dword ptr [esi]
    cpu.esi = app->getMemory<x86::reg32>(cpu.esi);
    // 00433636  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 00433638  740e                   -je 0x433648
    if (cpu.flags.zf)
    {
        goto L_0x00433648;
    }
    // 0043363a  668b4604               -mov ax, word ptr [esi + 4]
    cpu.ax = app->getMemory<x86::reg16>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 0043363e  663d0100               +cmp ax, 1
    {
        x86::reg16 tmp1 = cpu.ax;
        x86::reg16 tmp2 = x86::reg16(x86::sreg16(1 /*0x1*/));
        x86::reg16 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 15);
        cpu.flags.of ^= 1 & (result >> 15);
        cpu.flags.of &= (1 & (tmp1 >> 15)) != (1 & (tmp2 >> 15));
        cpu.set_szp(result);
    }
    // 00433642  0f84f5feffff           -je 0x43353d
    if (cpu.flags.zf)
    {
        goto L_0x0043353d;
    }
L_0x00433648:
    // 00433648  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 0043364a  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 0043364c  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043364d  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043364e  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043364f  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00433650  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00433651  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00433652  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x90 */
void Application::sub_433660(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00433660  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00433661  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00433662  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00433663  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00433664  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00433665  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00433666  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00433668  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 0043366a  8b15544e5500           -mov edx, dword ptr [0x554e54]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5590612) /* 0x554e54 */);
    // 00433670  8b780c                 -mov edi, dword ptr [eax + 0xc]
    cpu.edi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
    // 00433673  8b7008                 -mov esi, dword ptr [eax + 8]
    cpu.esi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 00433676  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 00433678  7411                   -je 0x43368b
    if (cpu.flags.zf)
    {
        goto L_0x0043368b;
    }
    // 0043367a  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 0043367c  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 0043367d  6a01                   -push 1
    app->getMemory<x86::reg32>(cpu.esp-4) = 1 /*0x1*/;
    cpu.esp -= 4;
    // 0043367f  890d544e5500           -mov dword ptr [0x554e54], ecx
    app->getMemory<x86::reg32>(x86::reg32(5590612) /* 0x554e54 */) = cpu.ecx;
    // 00433685  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x0043368b:
    // 0043368b  f6430601               +test byte ptr [ebx + 6], 1
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(cpu.ebx + x86::reg32(6) /* 0x6 */) & 1 /*0x1*/));
    // 0043368f  741f                   -je 0x4336b0
    if (cpu.flags.zf)
    {
        goto L_0x004336b0;
    }
    // 00433691  833d584e550001         +cmp dword ptr [0x554e58], 1
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5590616) /* 0x554e58 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1 /*0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00433698  742f                   -je 0x4336c9
    if (cpu.flags.zf)
    {
        goto L_0x004336c9;
    }
    // 0043369a  ba01000000             -mov edx, 1
    cpu.edx = 1 /*0x1*/;
    // 0043369f  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004336a0  6a68                   -push 0x68
    app->getMemory<x86::reg32>(cpu.esp-4) = 104 /*0x68*/;
    cpu.esp -= 4;
    // 004336a2  8915584e5500           -mov dword ptr [0x554e58], edx
    app->getMemory<x86::reg32>(x86::reg32(5590616) /* 0x554e58 */) = cpu.edx;
    // 004336a8  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004336ae  eb19                   -jmp 0x4336c9
    goto L_0x004336c9;
L_0x004336b0:
    // 004336b0  833d584e550000         +cmp dword ptr [0x554e58], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5590616) /* 0x554e58 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004336b7  7410                   -je 0x4336c9
    if (cpu.flags.zf)
    {
        goto L_0x004336c9;
    }
    // 004336b9  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 004336bb  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004336bc  6a68                   -push 0x68
    app->getMemory<x86::reg32>(cpu.esp-4) = 104 /*0x68*/;
    cpu.esp -= 4;
    // 004336be  a3584e5500             -mov dword ptr [0x554e58], eax
    app->getMemory<x86::reg32>(x86::reg32(5590616) /* 0x554e58 */) = cpu.eax;
    // 004336c3  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x004336c9:
    // 004336c9  89fa                   -mov edx, edi
    cpu.edx = cpu.edi;
    // 004336cb  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004336cd  e84ed40800             -call 0x4c0b20
    cpu.esp -= 4;
    sub_4c0b20(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004336d2  8b03                   -mov eax, dword ptr [ebx]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx);
    // 004336d4  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004336d5  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004336d6  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004336d7  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004336d8  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004336d9  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004336da  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x40 0x00 0x8b 0xc9 */
void Application::sub_4336e0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004336e0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004336e1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004336e2  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004336e3  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004336e4  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004336e5  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004336e6  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004336e8  83ec08                 -sub esp, 8
    (cpu.esp) -= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 004336eb  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
L_0x004336ed:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004336ed  8b4608                 -mov eax, dword ptr [esi + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(8) /* 0x8 */);
    // 004336f0  8945f8                 -mov dword ptr [ebp - 8], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.eax;
    // 004336f3  8b4604                 -mov eax, dword ptr [esi + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 004336f6  c1f810                 -sar eax, 0x10
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (16 /*0x10*/ % 32));
    // 004336f9  8b7e0c                 -mov edi, dword ptr [esi + 0xc]
    cpu.edi = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 004336fc  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 004336ff  8b5e10                 -mov ebx, dword ptr [esi + 0x10]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(16) /* 0x10 */);
    // 00433702  8a65fc                 -mov ah, byte ptr [ebp - 4]
    cpu.ah = app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00433705  f6c401                 +test ah, 1
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.ah & 1 /*0x1*/));
    // 00433708  741f                   -je 0x433729
    if (cpu.flags.zf)
    {
        goto L_0x00433729;
    }
    // 0043370a  833d584e550001         +cmp dword ptr [0x554e58], 1
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5590616) /* 0x554e58 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1 /*0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00433711  7430                   -je 0x433743
    if (cpu.flags.zf)
    {
        goto L_0x00433743;
    }
    // 00433713  b901000000             -mov ecx, 1
    cpu.ecx = 1 /*0x1*/;
    // 00433718  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00433719  6a68                   -push 0x68
    app->getMemory<x86::reg32>(cpu.esp-4) = 104 /*0x68*/;
    cpu.esp -= 4;
    // 0043371b  890d584e5500           -mov dword ptr [0x554e58], ecx
    app->getMemory<x86::reg32>(x86::reg32(5590616) /* 0x554e58 */) = cpu.ecx;
    // 00433721  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00433727  eb1a                   -jmp 0x433743
    goto L_0x00433743;
L_0x00433729:
    // 00433729  833d584e550000         +cmp dword ptr [0x554e58], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5590616) /* 0x554e58 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00433730  7411                   -je 0x433743
    if (cpu.flags.zf)
    {
        goto L_0x00433743;
    }
    // 00433732  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00433734  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00433735  6a68                   -push 0x68
    app->getMemory<x86::reg32>(cpu.esp-4) = 104 /*0x68*/;
    cpu.esp -= 4;
    // 00433737  8915584e5500           -mov dword ptr [0x554e58], edx
    app->getMemory<x86::reg32>(x86::reg32(5590616) /* 0x554e58 */) = cpu.edx;
    // 0043373d  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00433743:
    // 00433743  8b4e18                 -mov ecx, dword ptr [esi + 0x18]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(24) /* 0x18 */);
    // 00433746  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    // 00433748  7462                   -je 0x4337ac
    if (cpu.flags.zf)
    {
        goto L_0x004337ac;
    }
    // 0043374a  f645fc02               +test byte ptr [ebp - 4], 2
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-4) /* -0x4 */) & 2 /*0x2*/));
    // 0043374e  753b                   -jne 0x43378b
    if (!cpu.flags.zf)
    {
        goto L_0x0043378b;
    }
    // 00433750  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00433752  d94008                 -fld dword ptr [eax + 8]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 00433755  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 00433758  d95818                 -fstp dword ptr [eax + 0x18]
    app->getMemory<float>(cpu.eax + x86::reg32(24) /* 0x18 */) = float(fpu1);
    // 0043375b  8b4618                 -mov eax, dword ptr [esi + 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(24) /* 0x18 */);
    // 0043375e  d9400c                 -fld dword ptr [eax + 0xc]
    x86::Float fpu2 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(12) /* 0xc */));
    // 00433761  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 00433764  d9581c                 -fstp dword ptr [eax + 0x1c]
    app->getMemory<float>(cpu.eax + x86::reg32(28) /* 0x1c */) = float(fpu2);
    // 00433767  8b4618                 -mov eax, dword ptr [esi + 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(24) /* 0x18 */);
    // 0043376a  8b5010                 -mov edx, dword ptr [eax + 0x10]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(16) /* 0x10 */);
    // 0043376d  895718                 -mov dword ptr [edi + 0x18], edx
    app->getMemory<x86::reg32>(cpu.edi + x86::reg32(24) /* 0x18 */) = cpu.edx;
    // 00433770  8b4618                 -mov eax, dword ptr [esi + 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(24) /* 0x18 */);
    // 00433773  8b5014                 -mov edx, dword ptr [eax + 0x14]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */);
    // 00433776  89571c                 -mov dword ptr [edi + 0x1c], edx
    app->getMemory<x86::reg32>(cpu.edi + x86::reg32(28) /* 0x1c */) = cpu.edx;
    // 00433779  8b4618                 -mov eax, dword ptr [esi + 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(24) /* 0x18 */);
    // 0043377c  8b5018                 -mov edx, dword ptr [eax + 0x18]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */);
    // 0043377f  895318                 -mov dword ptr [ebx + 0x18], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(24) /* 0x18 */) = cpu.edx;
    // 00433782  8b4618                 -mov eax, dword ptr [esi + 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(24) /* 0x18 */);
    // 00433785  8b501c                 -mov edx, dword ptr [eax + 0x1c]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(28) /* 0x1c */);
    // 00433788  89531c                 -mov dword ptr [ebx + 0x1c], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(28) /* 0x1c */) = cpu.edx;
    }
L_0x0043378b:
    // 0043378b  8b4618                 -mov eax, dword ptr [esi + 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(24) /* 0x18 */);
    // 0043378e  8b15544e5500           -mov edx, dword ptr [0x554e54]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5590612) /* 0x554e54 */);
    // 00433794  8b4804                 -mov ecx, dword ptr [eax + 4]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 00433797  39ca                   +cmp edx, ecx
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ecx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00433799  742a                   -je 0x4337c5
    if (cpu.flags.zf)
    {
        goto L_0x004337c5;
    }
    // 0043379b  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 0043379c  6a01                   -push 1
    app->getMemory<x86::reg32>(cpu.esp-4) = 1 /*0x1*/;
    cpu.esp -= 4;
    // 0043379e  890d544e5500           -mov dword ptr [0x554e54], ecx
    app->getMemory<x86::reg32>(x86::reg32(5590612) /* 0x554e54 */) = cpu.ecx;
    // 004337a4  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004337aa  eb19                   -jmp 0x4337c5
    goto L_0x004337c5;
L_0x004337ac:
    // 004337ac  833d544e550000         +cmp dword ptr [0x554e54], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5590612) /* 0x554e54 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004337b3  7410                   -je 0x4337c5
    if (cpu.flags.zf)
    {
        goto L_0x004337c5;
    }
    // 004337b5  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 004337b7  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004337b8  6a01                   -push 1
    app->getMemory<x86::reg32>(cpu.esp-4) = 1 /*0x1*/;
    cpu.esp -= 4;
    // 004337ba  a3544e5500             -mov dword ptr [0x554e54], eax
    app->getMemory<x86::reg32>(x86::reg32(5590612) /* 0x554e54 */) = cpu.eax;
    // 004337bf  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x004337c5:
    // 004337c5  f645fc04               +test byte ptr [ebp - 4], 4
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-4) /* -0x4 */) & 4 /*0x4*/));
    // 004337c9  741c                   -je 0x4337e7
    if (cpu.flags.zf)
    {
        goto L_0x004337e7;
    }
    // 004337cb  833d5c4e550000         +cmp dword ptr [0x554e5c], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5590620) /* 0x554e5c */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004337d2  7430                   -je 0x433804
    if (cpu.flags.zf)
    {
        goto L_0x00433804;
    }
    // 004337d4  31c9                   +xor ecx, ecx
    cpu.clear_co();
    cpu.set_szp((cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx))));
    // 004337d6  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004337d7  6a15                   -push 0x15
    app->getMemory<x86::reg32>(cpu.esp-4) = 21 /*0x15*/;
    cpu.esp -= 4;
    // 004337d9  890d5c4e5500           -mov dword ptr [0x554e5c], ecx
    app->getMemory<x86::reg32>(x86::reg32(5590620) /* 0x554e5c */) = cpu.ecx;
    // 004337df  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004337e5  eb1d                   -jmp 0x433804
    goto L_0x00433804;
L_0x004337e7:
    // 004337e7  8b15643a7a00           -mov edx, dword ptr [0x7a3a64]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8010340) /* 0x7a3a64 */);
    // 004337ed  3b155c4e5500           +cmp edx, dword ptr [0x554e5c]
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(5590620) /* 0x554e5c */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004337f3  740f                   -je 0x433804
    if (cpu.flags.zf)
    {
        goto L_0x00433804;
    }
    // 004337f5  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004337f6  6a15                   -push 0x15
    app->getMemory<x86::reg32>(cpu.esp-4) = 21 /*0x15*/;
    cpu.esp -= 4;
    // 004337f8  89155c4e5500           -mov dword ptr [0x554e5c], edx
    app->getMemory<x86::reg32>(x86::reg32(5590620) /* 0x554e5c */) = cpu.edx;
    // 004337fe  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00433804:
    // 00433804  f645fc10               +test byte ptr [ebp - 4], 0x10
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-4) /* -0x4 */) & 16 /*0x10*/));
    // 00433808  740c                   -je 0x433816
    if (cpu.flags.zf)
    {
        goto L_0x00433816;
    }
    // 0043380a  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 0043380d  89fa                   -mov edx, edi
    cpu.edx = cpu.edi;
    // 0043380f  e88ce20800             -call 0x4c1aa0
    cpu.esp -= 4;
    sub_4c1aa0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00433814  eb0a                   -jmp 0x433820
    goto L_0x00433820;
L_0x00433816:
    // 00433816  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 00433819  89fa                   -mov edx, edi
    cpu.edx = cpu.edi;
    // 0043381b  e890d90800             -call 0x4c11b0
    cpu.esp -= 4;
    sub_4c11b0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00433820:
    // 00433820  8b36                   -mov esi, dword ptr [esi]
    cpu.esi = app->getMemory<x86::reg32>(cpu.esi);
    // 00433822  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 00433824  740e                   -je 0x433834
    if (cpu.flags.zf)
    {
        goto L_0x00433834;
    }
    // 00433826  668b4604               -mov ax, word ptr [esi + 4]
    cpu.ax = app->getMemory<x86::reg16>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 0043382a  663d0100               +cmp ax, 1
    {
        x86::reg16 tmp1 = cpu.ax;
        x86::reg16 tmp2 = x86::reg16(x86::sreg16(1 /*0x1*/));
        x86::reg16 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 15);
        cpu.flags.of ^= 1 & (result >> 15);
        cpu.flags.of &= (1 & (tmp1 >> 15)) != (1 & (tmp2 >> 15));
        cpu.set_szp(result);
    }
    // 0043382e  0f84b9feffff           -je 0x4336ed
    if (cpu.flags.zf)
    {
        goto L_0x004336ed;
    }
L_0x00433834:
    // 00433834  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 00433836  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00433838  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00433839  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043383a  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043383b  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043383c  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043383d  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043383e  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x90 */
void Application::sub_433840(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00433840  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00433841  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00433842  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00433843  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00433844  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00433845  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00433846  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00433848  83ec0c                 -sub esp, 0xc
    (cpu.esp) -= x86::reg32(x86::sreg32(12 /*0xc*/));
    // 0043384b  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
L_0x0043384d:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 0043384d  8b4608                 -mov eax, dword ptr [esi + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(8) /* 0x8 */);
    // 00433850  8945f8                 -mov dword ptr [ebp - 8], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.eax;
    // 00433853  8b4610                 -mov eax, dword ptr [esi + 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(16) /* 0x10 */);
    // 00433856  8945f4                 -mov dword ptr [ebp - 0xc], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.eax;
    // 00433859  8b4604                 -mov eax, dword ptr [esi + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 0043385c  c1f810                 -sar eax, 0x10
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (16 /*0x10*/ % 32));
    // 0043385f  8b7e0c                 -mov edi, dword ptr [esi + 0xc]
    cpu.edi = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 00433862  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 00433865  8b5e14                 -mov ebx, dword ptr [esi + 0x14]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(20) /* 0x14 */);
    // 00433868  8a65fc                 -mov ah, byte ptr [ebp - 4]
    cpu.ah = app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 0043386b  f6c401                 +test ah, 1
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.ah & 1 /*0x1*/));
    // 0043386e  741f                   -je 0x43388f
    if (cpu.flags.zf)
    {
        goto L_0x0043388f;
    }
    // 00433870  833d584e550001         +cmp dword ptr [0x554e58], 1
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5590616) /* 0x554e58 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1 /*0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00433877  7430                   -je 0x4338a9
    if (cpu.flags.zf)
    {
        goto L_0x004338a9;
    }
    // 00433879  b901000000             -mov ecx, 1
    cpu.ecx = 1 /*0x1*/;
    // 0043387e  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 0043387f  6a68                   -push 0x68
    app->getMemory<x86::reg32>(cpu.esp-4) = 104 /*0x68*/;
    cpu.esp -= 4;
    // 00433881  890d584e5500           -mov dword ptr [0x554e58], ecx
    app->getMemory<x86::reg32>(x86::reg32(5590616) /* 0x554e58 */) = cpu.ecx;
    // 00433887  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0043388d  eb1a                   -jmp 0x4338a9
    goto L_0x004338a9;
L_0x0043388f:
    // 0043388f  833d584e550000         +cmp dword ptr [0x554e58], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5590616) /* 0x554e58 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00433896  7411                   -je 0x4338a9
    if (cpu.flags.zf)
    {
        goto L_0x004338a9;
    }
    // 00433898  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 0043389a  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 0043389b  6a68                   -push 0x68
    app->getMemory<x86::reg32>(cpu.esp-4) = 104 /*0x68*/;
    cpu.esp -= 4;
    // 0043389d  8915584e5500           -mov dword ptr [0x554e58], edx
    app->getMemory<x86::reg32>(x86::reg32(5590616) /* 0x554e58 */) = cpu.edx;
    // 004338a3  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x004338a9:
    // 004338a9  8b4e18                 -mov ecx, dword ptr [esi + 0x18]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(24) /* 0x18 */);
    // 004338ac  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    // 004338ae  0f847a000000           -je 0x43392e
    if (cpu.flags.zf)
    {
        goto L_0x0043392e;
    }
    // 004338b4  f645fc02               +test byte ptr [ebp - 4], 2
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-4) /* -0x4 */) & 2 /*0x2*/));
    // 004338b8  7553                   -jne 0x43390d
    if (!cpu.flags.zf)
    {
        goto L_0x0043390d;
    }
    // 004338ba  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004338bc  d94008                 -fld dword ptr [eax + 8]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 004338bf  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004338c2  d95818                 -fstp dword ptr [eax + 0x18]
    app->getMemory<float>(cpu.eax + x86::reg32(24) /* 0x18 */) = float(fpu1);
    // 004338c5  8b4618                 -mov eax, dword ptr [esi + 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(24) /* 0x18 */);
    // 004338c8  d9400c                 -fld dword ptr [eax + 0xc]
    x86::Float fpu2 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(12) /* 0xc */));
    // 004338cb  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004338ce  d9581c                 -fstp dword ptr [eax + 0x1c]
    app->getMemory<float>(cpu.eax + x86::reg32(28) /* 0x1c */) = float(fpu2);
    // 004338d1  8b4618                 -mov eax, dword ptr [esi + 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(24) /* 0x18 */);
    // 004338d4  8b5010                 -mov edx, dword ptr [eax + 0x10]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(16) /* 0x10 */);
    // 004338d7  895718                 -mov dword ptr [edi + 0x18], edx
    app->getMemory<x86::reg32>(cpu.edi + x86::reg32(24) /* 0x18 */) = cpu.edx;
    // 004338da  8b4618                 -mov eax, dword ptr [esi + 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(24) /* 0x18 */);
    // 004338dd  8b5014                 -mov edx, dword ptr [eax + 0x14]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */);
    // 004338e0  89571c                 -mov dword ptr [edi + 0x1c], edx
    app->getMemory<x86::reg32>(cpu.edi + x86::reg32(28) /* 0x1c */) = cpu.edx;
    // 004338e3  8b4618                 -mov eax, dword ptr [esi + 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(24) /* 0x18 */);
    // 004338e6  d94018                 -fld dword ptr [eax + 0x18]
    x86::Float fpu3 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(24) /* 0x18 */));
    // 004338e9  8b45f4                 -mov eax, dword ptr [ebp - 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 004338ec  d95818                 -fstp dword ptr [eax + 0x18]
    app->getMemory<float>(cpu.eax + x86::reg32(24) /* 0x18 */) = float(fpu3);
    // 004338ef  8b4618                 -mov eax, dword ptr [esi + 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(24) /* 0x18 */);
    // 004338f2  d9401c                 -fld dword ptr [eax + 0x1c]
    x86::Float fpu4 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(28) /* 0x1c */));
    // 004338f5  8b45f4                 -mov eax, dword ptr [ebp - 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 004338f8  d9581c                 -fstp dword ptr [eax + 0x1c]
    app->getMemory<float>(cpu.eax + x86::reg32(28) /* 0x1c */) = float(fpu4);
    // 004338fb  8b4618                 -mov eax, dword ptr [esi + 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(24) /* 0x18 */);
    // 004338fe  8b5020                 -mov edx, dword ptr [eax + 0x20]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(32) /* 0x20 */);
    // 00433901  895318                 -mov dword ptr [ebx + 0x18], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(24) /* 0x18 */) = cpu.edx;
    // 00433904  8b4618                 -mov eax, dword ptr [esi + 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(24) /* 0x18 */);
    // 00433907  8b5024                 -mov edx, dword ptr [eax + 0x24]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(36) /* 0x24 */);
    // 0043390a  89531c                 -mov dword ptr [ebx + 0x1c], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(28) /* 0x1c */) = cpu.edx;
    }
L_0x0043390d:
    // 0043390d  8b4618                 -mov eax, dword ptr [esi + 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(24) /* 0x18 */);
    // 00433910  8b15544e5500           -mov edx, dword ptr [0x554e54]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5590612) /* 0x554e54 */);
    // 00433916  8b4804                 -mov ecx, dword ptr [eax + 4]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 00433919  39ca                   +cmp edx, ecx
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ecx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0043391b  742a                   -je 0x433947
    if (cpu.flags.zf)
    {
        goto L_0x00433947;
    }
    // 0043391d  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 0043391e  6a01                   -push 1
    app->getMemory<x86::reg32>(cpu.esp-4) = 1 /*0x1*/;
    cpu.esp -= 4;
    // 00433920  890d544e5500           -mov dword ptr [0x554e54], ecx
    app->getMemory<x86::reg32>(x86::reg32(5590612) /* 0x554e54 */) = cpu.ecx;
    // 00433926  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0043392c  eb19                   -jmp 0x433947
    goto L_0x00433947;
L_0x0043392e:
    // 0043392e  833d544e550000         +cmp dword ptr [0x554e54], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5590612) /* 0x554e54 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00433935  7410                   -je 0x433947
    if (cpu.flags.zf)
    {
        goto L_0x00433947;
    }
    // 00433937  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00433939  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 0043393a  6a01                   -push 1
    app->getMemory<x86::reg32>(cpu.esp-4) = 1 /*0x1*/;
    cpu.esp -= 4;
    // 0043393c  a3544e5500             -mov dword ptr [0x554e54], eax
    app->getMemory<x86::reg32>(x86::reg32(5590612) /* 0x554e54 */) = cpu.eax;
    // 00433941  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00433947:
    // 00433947  f645fc04               +test byte ptr [ebp - 4], 4
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-4) /* -0x4 */) & 4 /*0x4*/));
    // 0043394b  741c                   -je 0x433969
    if (cpu.flags.zf)
    {
        goto L_0x00433969;
    }
    // 0043394d  833d5c4e550000         +cmp dword ptr [0x554e5c], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5590620) /* 0x554e5c */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00433954  7430                   -je 0x433986
    if (cpu.flags.zf)
    {
        goto L_0x00433986;
    }
    // 00433956  31c9                   +xor ecx, ecx
    cpu.clear_co();
    cpu.set_szp((cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx))));
    // 00433958  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00433959  6a15                   -push 0x15
    app->getMemory<x86::reg32>(cpu.esp-4) = 21 /*0x15*/;
    cpu.esp -= 4;
    // 0043395b  890d5c4e5500           -mov dword ptr [0x554e5c], ecx
    app->getMemory<x86::reg32>(x86::reg32(5590620) /* 0x554e5c */) = cpu.ecx;
    // 00433961  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00433967  eb1d                   -jmp 0x433986
    goto L_0x00433986;
L_0x00433969:
    // 00433969  8b15643a7a00           -mov edx, dword ptr [0x7a3a64]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8010340) /* 0x7a3a64 */);
    // 0043396f  3b155c4e5500           +cmp edx, dword ptr [0x554e5c]
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(5590620) /* 0x554e5c */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00433975  740f                   -je 0x433986
    if (cpu.flags.zf)
    {
        goto L_0x00433986;
    }
    // 00433977  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00433978  6a15                   -push 0x15
    app->getMemory<x86::reg32>(cpu.esp-4) = 21 /*0x15*/;
    cpu.esp -= 4;
    // 0043397a  89155c4e5500           -mov dword ptr [0x554e5c], edx
    app->getMemory<x86::reg32>(x86::reg32(5590620) /* 0x554e5c */) = cpu.edx;
    // 00433980  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00433986:
    // 00433986  f645fc10               +test byte ptr [ebp - 4], 0x10
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-4) /* -0x4 */) & 16 /*0x10*/));
    // 0043398a  7411                   -je 0x43399d
    if (cpu.flags.zf)
    {
        goto L_0x0043399d;
    }
    // 0043398c  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 0043398f  89d9                   -mov ecx, ebx
    cpu.ecx = cpu.ebx;
    // 00433991  89fa                   -mov edx, edi
    cpu.edx = cpu.edi;
    // 00433993  8b5df4                 -mov ebx, dword ptr [ebp - 0xc]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 00433996  e845e70800             -call 0x4c20e0
    cpu.esp -= 4;
    sub_4c20e0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0043399b  eb0f                   -jmp 0x4339ac
    goto L_0x004339ac;
L_0x0043399d:
    // 0043399d  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004339a0  89d9                   -mov ecx, ebx
    cpu.ecx = cpu.ebx;
    // 004339a2  89fa                   -mov edx, edi
    cpu.edx = cpu.edi;
    // 004339a4  8b5df4                 -mov ebx, dword ptr [ebp - 0xc]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 004339a7  e834d90800             -call 0x4c12e0
    cpu.esp -= 4;
    sub_4c12e0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x004339ac:
    // 004339ac  8b36                   -mov esi, dword ptr [esi]
    cpu.esi = app->getMemory<x86::reg32>(cpu.esi);
    // 004339ae  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 004339b0  740d                   -je 0x4339bf
    if (cpu.flags.zf)
    {
        goto L_0x004339bf;
    }
    // 004339b2  668b4604               -mov ax, word ptr [esi + 4]
    cpu.ax = app->getMemory<x86::reg16>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 004339b6  6685c0                 +test ax, ax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg16>(cpu.ax & cpu.ax));
    // 004339b9  0f848efeffff           -je 0x43384d
    if (cpu.flags.zf)
    {
        goto L_0x0043384d;
    }
L_0x004339bf:
    // 004339bf  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004339c1  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004339c3  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004339c4  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004339c5  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004339c6  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004339c7  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004339c8  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004339c9  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 */
void Application::sub_4339d0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004339d0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004339d1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004339d2  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004339d3  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004339d4  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004339d5  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004339d6  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004339d8  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 004339da  8b15544e5500           -mov edx, dword ptr [0x554e54]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5590612) /* 0x554e54 */);
    // 004339e0  8b780c                 -mov edi, dword ptr [eax + 0xc]
    cpu.edi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
    // 004339e3  8b7008                 -mov esi, dword ptr [eax + 8]
    cpu.esi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 004339e6  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 004339e8  7411                   -je 0x4339fb
    if (cpu.flags.zf)
    {
        goto L_0x004339fb;
    }
    // 004339ea  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 004339ec  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004339ed  6a01                   -push 1
    app->getMemory<x86::reg32>(cpu.esp-4) = 1 /*0x1*/;
    cpu.esp -= 4;
    // 004339ef  890d544e5500           -mov dword ptr [0x554e54], ecx
    app->getMemory<x86::reg32>(x86::reg32(5590612) /* 0x554e54 */) = cpu.ecx;
    // 004339f5  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x004339fb:
    // 004339fb  f6430601               +test byte ptr [ebx + 6], 1
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(cpu.ebx + x86::reg32(6) /* 0x6 */) & 1 /*0x1*/));
    // 004339ff  741f                   -je 0x433a20
    if (cpu.flags.zf)
    {
        goto L_0x00433a20;
    }
    // 00433a01  833d584e550001         +cmp dword ptr [0x554e58], 1
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5590616) /* 0x554e58 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1 /*0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00433a08  742f                   -je 0x433a39
    if (cpu.flags.zf)
    {
        goto L_0x00433a39;
    }
    // 00433a0a  ba01000000             -mov edx, 1
    cpu.edx = 1 /*0x1*/;
    // 00433a0f  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00433a10  6a68                   -push 0x68
    app->getMemory<x86::reg32>(cpu.esp-4) = 104 /*0x68*/;
    cpu.esp -= 4;
    // 00433a12  8915584e5500           -mov dword ptr [0x554e58], edx
    app->getMemory<x86::reg32>(x86::reg32(5590616) /* 0x554e58 */) = cpu.edx;
    // 00433a18  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00433a1e  eb19                   -jmp 0x433a39
    goto L_0x00433a39;
L_0x00433a20:
    // 00433a20  833d584e550000         +cmp dword ptr [0x554e58], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5590616) /* 0x554e58 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00433a27  7410                   -je 0x433a39
    if (cpu.flags.zf)
    {
        goto L_0x00433a39;
    }
    // 00433a29  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00433a2b  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00433a2c  6a68                   -push 0x68
    app->getMemory<x86::reg32>(cpu.esp-4) = 104 /*0x68*/;
    cpu.esp -= 4;
    // 00433a2e  a3584e5500             -mov dword ptr [0x554e58], eax
    app->getMemory<x86::reg32>(x86::reg32(5590616) /* 0x554e58 */) = cpu.eax;
    // 00433a33  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00433a39:
    // 00433a39  89fa                   -mov edx, edi
    cpu.edx = cpu.edi;
    // 00433a3b  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 00433a3d  e8ded00800             -call 0x4c0b20
    cpu.esp -= 4;
    sub_4c0b20(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00433a42  8b03                   -mov eax, dword ptr [ebx]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx);
    // 00433a44  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00433a45  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00433a46  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00433a47  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00433a48  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00433a49  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00433a4a  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x40 0x00 0x8b 0xc9 */
void Application::sub_433a50(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (triangleList(app, cpu.sync())) /* port: native (tools/apply_native_vertices.py) */
    {
        cpu.reload();
        return;
    }
    // 00433a50  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00433a51  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00433a52  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00433a53  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00433a54  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00433a55  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00433a56  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00433a58  83ec08                 -sub esp, 8
    (cpu.esp) -= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 00433a5b  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
L_0x00433a5d:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00433a5d  8b4608                 -mov eax, dword ptr [esi + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(8) /* 0x8 */);
    // 00433a60  8945f8                 -mov dword ptr [ebp - 8], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.eax;
    // 00433a63  8b4604                 -mov eax, dword ptr [esi + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 00433a66  c1f810                 -sar eax, 0x10
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (16 /*0x10*/ % 32));
    // 00433a69  8b7e0c                 -mov edi, dword ptr [esi + 0xc]
    cpu.edi = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 00433a6c  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 00433a6f  8b5e10                 -mov ebx, dword ptr [esi + 0x10]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(16) /* 0x10 */);
    // 00433a72  8a65fc                 -mov ah, byte ptr [ebp - 4]
    cpu.ah = app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00433a75  f6c401                 +test ah, 1
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.ah & 1 /*0x1*/));
    // 00433a78  741f                   -je 0x433a99
    if (cpu.flags.zf)
    {
        goto L_0x00433a99;
    }
    // 00433a7a  833d584e550001         +cmp dword ptr [0x554e58], 1
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5590616) /* 0x554e58 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1 /*0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00433a81  7430                   -je 0x433ab3
    if (cpu.flags.zf)
    {
        goto L_0x00433ab3;
    }
    // 00433a83  b901000000             -mov ecx, 1
    cpu.ecx = 1 /*0x1*/;
    // 00433a88  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00433a89  6a68                   -push 0x68
    app->getMemory<x86::reg32>(cpu.esp-4) = 104 /*0x68*/;
    cpu.esp -= 4;
    // 00433a8b  890d584e5500           -mov dword ptr [0x554e58], ecx
    app->getMemory<x86::reg32>(x86::reg32(5590616) /* 0x554e58 */) = cpu.ecx;
    // 00433a91  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00433a97  eb1a                   -jmp 0x433ab3
    goto L_0x00433ab3;
L_0x00433a99:
    // 00433a99  833d584e550000         +cmp dword ptr [0x554e58], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5590616) /* 0x554e58 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00433aa0  7411                   -je 0x433ab3
    if (cpu.flags.zf)
    {
        goto L_0x00433ab3;
    }
    // 00433aa2  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00433aa4  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00433aa5  6a68                   -push 0x68
    app->getMemory<x86::reg32>(cpu.esp-4) = 104 /*0x68*/;
    cpu.esp -= 4;
    // 00433aa7  8915584e5500           -mov dword ptr [0x554e58], edx
    app->getMemory<x86::reg32>(x86::reg32(5590616) /* 0x554e58 */) = cpu.edx;
    // 00433aad  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00433ab3:
    // 00433ab3  8b4e18                 -mov ecx, dword ptr [esi + 0x18]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(24) /* 0x18 */);
    // 00433ab6  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    // 00433ab8  7462                   -je 0x433b1c
    if (cpu.flags.zf)
    {
        goto L_0x00433b1c;
    }
    // 00433aba  f645fc02               +test byte ptr [ebp - 4], 2
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-4) /* -0x4 */) & 2 /*0x2*/));
    // 00433abe  753b                   -jne 0x433afb
    if (!cpu.flags.zf)
    {
        goto L_0x00433afb;
    }
    // 00433ac0  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00433ac2  d94008                 -fld dword ptr [eax + 8]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 00433ac5  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 00433ac8  d95818                 -fstp dword ptr [eax + 0x18]
    app->getMemory<float>(cpu.eax + x86::reg32(24) /* 0x18 */) = float(fpu1);
    // 00433acb  8b4618                 -mov eax, dword ptr [esi + 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(24) /* 0x18 */);
    // 00433ace  d9400c                 -fld dword ptr [eax + 0xc]
    x86::Float fpu2 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(12) /* 0xc */));
    // 00433ad1  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 00433ad4  d9581c                 -fstp dword ptr [eax + 0x1c]
    app->getMemory<float>(cpu.eax + x86::reg32(28) /* 0x1c */) = float(fpu2);
    // 00433ad7  8b4618                 -mov eax, dword ptr [esi + 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(24) /* 0x18 */);
    // 00433ada  8b5010                 -mov edx, dword ptr [eax + 0x10]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(16) /* 0x10 */);
    // 00433add  895718                 -mov dword ptr [edi + 0x18], edx
    app->getMemory<x86::reg32>(cpu.edi + x86::reg32(24) /* 0x18 */) = cpu.edx;
    // 00433ae0  8b4618                 -mov eax, dword ptr [esi + 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(24) /* 0x18 */);
    // 00433ae3  8b5014                 -mov edx, dword ptr [eax + 0x14]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */);
    // 00433ae6  89571c                 -mov dword ptr [edi + 0x1c], edx
    app->getMemory<x86::reg32>(cpu.edi + x86::reg32(28) /* 0x1c */) = cpu.edx;
    // 00433ae9  8b4618                 -mov eax, dword ptr [esi + 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(24) /* 0x18 */);
    // 00433aec  8b5018                 -mov edx, dword ptr [eax + 0x18]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */);
    // 00433aef  895318                 -mov dword ptr [ebx + 0x18], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(24) /* 0x18 */) = cpu.edx;
    // 00433af2  8b4618                 -mov eax, dword ptr [esi + 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(24) /* 0x18 */);
    // 00433af5  8b501c                 -mov edx, dword ptr [eax + 0x1c]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(28) /* 0x1c */);
    // 00433af8  89531c                 -mov dword ptr [ebx + 0x1c], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(28) /* 0x1c */) = cpu.edx;
    }
L_0x00433afb:
    // 00433afb  8b4618                 -mov eax, dword ptr [esi + 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(24) /* 0x18 */);
    // 00433afe  8b15544e5500           -mov edx, dword ptr [0x554e54]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5590612) /* 0x554e54 */);
    // 00433b04  8b4804                 -mov ecx, dword ptr [eax + 4]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 00433b07  39ca                   +cmp edx, ecx
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ecx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00433b09  742a                   -je 0x433b35
    if (cpu.flags.zf)
    {
        goto L_0x00433b35;
    }
    // 00433b0b  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00433b0c  6a01                   -push 1
    app->getMemory<x86::reg32>(cpu.esp-4) = 1 /*0x1*/;
    cpu.esp -= 4;
    // 00433b0e  890d544e5500           -mov dword ptr [0x554e54], ecx
    app->getMemory<x86::reg32>(x86::reg32(5590612) /* 0x554e54 */) = cpu.ecx;
    // 00433b14  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00433b1a  eb19                   -jmp 0x433b35
    goto L_0x00433b35;
L_0x00433b1c:
    // 00433b1c  833d544e550000         +cmp dword ptr [0x554e54], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5590612) /* 0x554e54 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00433b23  7410                   -je 0x433b35
    if (cpu.flags.zf)
    {
        goto L_0x00433b35;
    }
    // 00433b25  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00433b27  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00433b28  6a01                   -push 1
    app->getMemory<x86::reg32>(cpu.esp-4) = 1 /*0x1*/;
    cpu.esp -= 4;
    // 00433b2a  a3544e5500             -mov dword ptr [0x554e54], eax
    app->getMemory<x86::reg32>(x86::reg32(5590612) /* 0x554e54 */) = cpu.eax;
    // 00433b2f  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00433b35:
    // 00433b35  f645fc04               +test byte ptr [ebp - 4], 4
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-4) /* -0x4 */) & 4 /*0x4*/));
    // 00433b39  741c                   -je 0x433b57
    if (cpu.flags.zf)
    {
        goto L_0x00433b57;
    }
    // 00433b3b  833d5c4e550000         +cmp dword ptr [0x554e5c], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5590620) /* 0x554e5c */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00433b42  7430                   -je 0x433b74
    if (cpu.flags.zf)
    {
        goto L_0x00433b74;
    }
    // 00433b44  31c9                   +xor ecx, ecx
    cpu.clear_co();
    cpu.set_szp((cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx))));
    // 00433b46  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00433b47  6a15                   -push 0x15
    app->getMemory<x86::reg32>(cpu.esp-4) = 21 /*0x15*/;
    cpu.esp -= 4;
    // 00433b49  890d5c4e5500           -mov dword ptr [0x554e5c], ecx
    app->getMemory<x86::reg32>(x86::reg32(5590620) /* 0x554e5c */) = cpu.ecx;
    // 00433b4f  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00433b55  eb1d                   -jmp 0x433b74
    goto L_0x00433b74;
L_0x00433b57:
    // 00433b57  8b15643a7a00           -mov edx, dword ptr [0x7a3a64]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8010340) /* 0x7a3a64 */);
    // 00433b5d  3b155c4e5500           +cmp edx, dword ptr [0x554e5c]
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(5590620) /* 0x554e5c */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00433b63  740f                   -je 0x433b74
    if (cpu.flags.zf)
    {
        goto L_0x00433b74;
    }
    // 00433b65  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00433b66  6a15                   -push 0x15
    app->getMemory<x86::reg32>(cpu.esp-4) = 21 /*0x15*/;
    cpu.esp -= 4;
    // 00433b68  89155c4e5500           -mov dword ptr [0x554e5c], edx
    app->getMemory<x86::reg32>(x86::reg32(5590620) /* 0x554e5c */) = cpu.edx;
    // 00433b6e  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00433b74:
    // 00433b74  f645fc10               +test byte ptr [ebp - 4], 0x10
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-4) /* -0x4 */) & 16 /*0x10*/));
    // 00433b78  740c                   -je 0x433b86
    if (cpu.flags.zf)
    {
        goto L_0x00433b86;
    }
    // 00433b7a  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 00433b7d  89fa                   -mov edx, edi
    cpu.edx = cpu.edi;
    // 00433b7f  e81cdf0800             -call 0x4c1aa0
    cpu.esp -= 4;
    sub_4c1aa0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00433b84  eb0a                   -jmp 0x433b90
    goto L_0x00433b90;
L_0x00433b86:
    // 00433b86  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 00433b89  89fa                   -mov edx, edi
    cpu.edx = cpu.edi;
    // 00433b8b  e820d60800             -call 0x4c11b0
    cpu.esp -= 4;
    sub_4c11b0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00433b90:
    // 00433b90  8b36                   -mov esi, dword ptr [esi]
    cpu.esi = app->getMemory<x86::reg32>(cpu.esi);
    // 00433b92  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 00433b94  740e                   -je 0x433ba4
    if (cpu.flags.zf)
    {
        goto L_0x00433ba4;
    }
    // 00433b96  668b4604               -mov ax, word ptr [esi + 4]
    cpu.ax = app->getMemory<x86::reg16>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 00433b9a  663d0100               +cmp ax, 1
    {
        x86::reg16 tmp1 = cpu.ax;
        x86::reg16 tmp2 = x86::reg16(x86::sreg16(1 /*0x1*/));
        x86::reg16 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 15);
        cpu.flags.of ^= 1 & (result >> 15);
        cpu.flags.of &= (1 & (tmp1 >> 15)) != (1 & (tmp2 >> 15));
        cpu.set_szp(result);
    }
    // 00433b9e  0f84b9feffff           -je 0x433a5d
    if (cpu.flags.zf)
    {
        goto L_0x00433a5d;
    }
L_0x00433ba4:
    // 00433ba4  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 00433ba6  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00433ba8  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00433ba9  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00433baa  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00433bab  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00433bac  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00433bad  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00433bae  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x90 */
void Application::sub_433bb0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (quadList(app, cpu.sync())) /* port: native (tools/apply_native_vertices.py) */
    {
        cpu.reload();
        return;
    }
    // 00433bb0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00433bb1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00433bb2  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00433bb3  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00433bb4  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00433bb5  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00433bb6  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00433bb8  83ec0c                 -sub esp, 0xc
    (cpu.esp) -= x86::reg32(x86::sreg32(12 /*0xc*/));
    // 00433bbb  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
L_0x00433bbd:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00433bbd  8b4608                 -mov eax, dword ptr [esi + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(8) /* 0x8 */);
    // 00433bc0  8945f8                 -mov dword ptr [ebp - 8], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.eax;
    // 00433bc3  8b4610                 -mov eax, dword ptr [esi + 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(16) /* 0x10 */);
    // 00433bc6  8945f4                 -mov dword ptr [ebp - 0xc], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.eax;
    // 00433bc9  8b4604                 -mov eax, dword ptr [esi + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 00433bcc  c1f810                 -sar eax, 0x10
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (16 /*0x10*/ % 32));
    // 00433bcf  8b7e0c                 -mov edi, dword ptr [esi + 0xc]
    cpu.edi = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 00433bd2  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 00433bd5  8b5e14                 -mov ebx, dword ptr [esi + 0x14]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(20) /* 0x14 */);
    // 00433bd8  8a65fc                 -mov ah, byte ptr [ebp - 4]
    cpu.ah = app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00433bdb  f6c401                 +test ah, 1
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.ah & 1 /*0x1*/));
    // 00433bde  741f                   -je 0x433bff
    if (cpu.flags.zf)
    {
        goto L_0x00433bff;
    }
    // 00433be0  833d584e550001         +cmp dword ptr [0x554e58], 1
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5590616) /* 0x554e58 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1 /*0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00433be7  7430                   -je 0x433c19
    if (cpu.flags.zf)
    {
        goto L_0x00433c19;
    }
    // 00433be9  b901000000             -mov ecx, 1
    cpu.ecx = 1 /*0x1*/;
    // 00433bee  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00433bef  6a68                   -push 0x68
    app->getMemory<x86::reg32>(cpu.esp-4) = 104 /*0x68*/;
    cpu.esp -= 4;
    // 00433bf1  890d584e5500           -mov dword ptr [0x554e58], ecx
    app->getMemory<x86::reg32>(x86::reg32(5590616) /* 0x554e58 */) = cpu.ecx;
    // 00433bf7  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00433bfd  eb1a                   -jmp 0x433c19
    goto L_0x00433c19;
L_0x00433bff:
    // 00433bff  833d584e550000         +cmp dword ptr [0x554e58], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5590616) /* 0x554e58 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00433c06  7411                   -je 0x433c19
    if (cpu.flags.zf)
    {
        goto L_0x00433c19;
    }
    // 00433c08  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00433c0a  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00433c0b  6a68                   -push 0x68
    app->getMemory<x86::reg32>(cpu.esp-4) = 104 /*0x68*/;
    cpu.esp -= 4;
    // 00433c0d  8915584e5500           -mov dword ptr [0x554e58], edx
    app->getMemory<x86::reg32>(x86::reg32(5590616) /* 0x554e58 */) = cpu.edx;
    // 00433c13  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00433c19:
    // 00433c19  8b4e18                 -mov ecx, dword ptr [esi + 0x18]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(24) /* 0x18 */);
    // 00433c1c  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    // 00433c1e  0f847a000000           -je 0x433c9e
    if (cpu.flags.zf)
    {
        goto L_0x00433c9e;
    }
    // 00433c24  f645fc02               +test byte ptr [ebp - 4], 2
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-4) /* -0x4 */) & 2 /*0x2*/));
    // 00433c28  7553                   -jne 0x433c7d
    if (!cpu.flags.zf)
    {
        goto L_0x00433c7d;
    }
    // 00433c2a  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00433c2c  d94008                 -fld dword ptr [eax + 8]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 00433c2f  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 00433c32  d95818                 -fstp dword ptr [eax + 0x18]
    app->getMemory<float>(cpu.eax + x86::reg32(24) /* 0x18 */) = float(fpu1);
    // 00433c35  8b4618                 -mov eax, dword ptr [esi + 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(24) /* 0x18 */);
    // 00433c38  d9400c                 -fld dword ptr [eax + 0xc]
    x86::Float fpu2 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(12) /* 0xc */));
    // 00433c3b  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 00433c3e  d9581c                 -fstp dword ptr [eax + 0x1c]
    app->getMemory<float>(cpu.eax + x86::reg32(28) /* 0x1c */) = float(fpu2);
    // 00433c41  8b4618                 -mov eax, dword ptr [esi + 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(24) /* 0x18 */);
    // 00433c44  8b5010                 -mov edx, dword ptr [eax + 0x10]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(16) /* 0x10 */);
    // 00433c47  895718                 -mov dword ptr [edi + 0x18], edx
    app->getMemory<x86::reg32>(cpu.edi + x86::reg32(24) /* 0x18 */) = cpu.edx;
    // 00433c4a  8b4618                 -mov eax, dword ptr [esi + 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(24) /* 0x18 */);
    // 00433c4d  8b5014                 -mov edx, dword ptr [eax + 0x14]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */);
    // 00433c50  89571c                 -mov dword ptr [edi + 0x1c], edx
    app->getMemory<x86::reg32>(cpu.edi + x86::reg32(28) /* 0x1c */) = cpu.edx;
    // 00433c53  8b4618                 -mov eax, dword ptr [esi + 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(24) /* 0x18 */);
    // 00433c56  d94018                 -fld dword ptr [eax + 0x18]
    x86::Float fpu3 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(24) /* 0x18 */));
    // 00433c59  8b45f4                 -mov eax, dword ptr [ebp - 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 00433c5c  d95818                 -fstp dword ptr [eax + 0x18]
    app->getMemory<float>(cpu.eax + x86::reg32(24) /* 0x18 */) = float(fpu3);
    // 00433c5f  8b4618                 -mov eax, dword ptr [esi + 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(24) /* 0x18 */);
    // 00433c62  d9401c                 -fld dword ptr [eax + 0x1c]
    x86::Float fpu4 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(28) /* 0x1c */));
    // 00433c65  8b45f4                 -mov eax, dword ptr [ebp - 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 00433c68  d9581c                 -fstp dword ptr [eax + 0x1c]
    app->getMemory<float>(cpu.eax + x86::reg32(28) /* 0x1c */) = float(fpu4);
    // 00433c6b  8b4618                 -mov eax, dword ptr [esi + 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(24) /* 0x18 */);
    // 00433c6e  8b5020                 -mov edx, dword ptr [eax + 0x20]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(32) /* 0x20 */);
    // 00433c71  895318                 -mov dword ptr [ebx + 0x18], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(24) /* 0x18 */) = cpu.edx;
    // 00433c74  8b4618                 -mov eax, dword ptr [esi + 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(24) /* 0x18 */);
    // 00433c77  8b5024                 -mov edx, dword ptr [eax + 0x24]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(36) /* 0x24 */);
    // 00433c7a  89531c                 -mov dword ptr [ebx + 0x1c], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(28) /* 0x1c */) = cpu.edx;
    }
L_0x00433c7d:
    // 00433c7d  8b4618                 -mov eax, dword ptr [esi + 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(24) /* 0x18 */);
    // 00433c80  8b15544e5500           -mov edx, dword ptr [0x554e54]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5590612) /* 0x554e54 */);
    // 00433c86  8b4804                 -mov ecx, dword ptr [eax + 4]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 00433c89  39ca                   +cmp edx, ecx
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ecx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00433c8b  742a                   -je 0x433cb7
    if (cpu.flags.zf)
    {
        goto L_0x00433cb7;
    }
    // 00433c8d  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00433c8e  6a01                   -push 1
    app->getMemory<x86::reg32>(cpu.esp-4) = 1 /*0x1*/;
    cpu.esp -= 4;
    // 00433c90  890d544e5500           -mov dword ptr [0x554e54], ecx
    app->getMemory<x86::reg32>(x86::reg32(5590612) /* 0x554e54 */) = cpu.ecx;
    // 00433c96  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00433c9c  eb19                   -jmp 0x433cb7
    goto L_0x00433cb7;
L_0x00433c9e:
    // 00433c9e  833d544e550000         +cmp dword ptr [0x554e54], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5590612) /* 0x554e54 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00433ca5  7410                   -je 0x433cb7
    if (cpu.flags.zf)
    {
        goto L_0x00433cb7;
    }
    // 00433ca7  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00433ca9  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00433caa  6a01                   -push 1
    app->getMemory<x86::reg32>(cpu.esp-4) = 1 /*0x1*/;
    cpu.esp -= 4;
    // 00433cac  a3544e5500             -mov dword ptr [0x554e54], eax
    app->getMemory<x86::reg32>(x86::reg32(5590612) /* 0x554e54 */) = cpu.eax;
    // 00433cb1  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00433cb7:
    // 00433cb7  f645fc04               +test byte ptr [ebp - 4], 4
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-4) /* -0x4 */) & 4 /*0x4*/));
    // 00433cbb  741c                   -je 0x433cd9
    if (cpu.flags.zf)
    {
        goto L_0x00433cd9;
    }
    // 00433cbd  833d5c4e550000         +cmp dword ptr [0x554e5c], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5590620) /* 0x554e5c */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00433cc4  7430                   -je 0x433cf6
    if (cpu.flags.zf)
    {
        goto L_0x00433cf6;
    }
    // 00433cc6  31c9                   +xor ecx, ecx
    cpu.clear_co();
    cpu.set_szp((cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx))));
    // 00433cc8  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00433cc9  6a15                   -push 0x15
    app->getMemory<x86::reg32>(cpu.esp-4) = 21 /*0x15*/;
    cpu.esp -= 4;
    // 00433ccb  890d5c4e5500           -mov dword ptr [0x554e5c], ecx
    app->getMemory<x86::reg32>(x86::reg32(5590620) /* 0x554e5c */) = cpu.ecx;
    // 00433cd1  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00433cd7  eb1d                   -jmp 0x433cf6
    goto L_0x00433cf6;
L_0x00433cd9:
    // 00433cd9  8b15643a7a00           -mov edx, dword ptr [0x7a3a64]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8010340) /* 0x7a3a64 */);
    // 00433cdf  3b155c4e5500           +cmp edx, dword ptr [0x554e5c]
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(5590620) /* 0x554e5c */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00433ce5  740f                   -je 0x433cf6
    if (cpu.flags.zf)
    {
        goto L_0x00433cf6;
    }
    // 00433ce7  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00433ce8  6a15                   -push 0x15
    app->getMemory<x86::reg32>(cpu.esp-4) = 21 /*0x15*/;
    cpu.esp -= 4;
    // 00433cea  89155c4e5500           -mov dword ptr [0x554e5c], edx
    app->getMemory<x86::reg32>(x86::reg32(5590620) /* 0x554e5c */) = cpu.edx;
    // 00433cf0  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00433cf6:
    // 00433cf6  f645fc10               +test byte ptr [ebp - 4], 0x10
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-4) /* -0x4 */) & 16 /*0x10*/));
    // 00433cfa  7411                   -je 0x433d0d
    if (cpu.flags.zf)
    {
        goto L_0x00433d0d;
    }
    // 00433cfc  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 00433cff  89d9                   -mov ecx, ebx
    cpu.ecx = cpu.ebx;
    // 00433d01  89fa                   -mov edx, edi
    cpu.edx = cpu.edi;
    // 00433d03  8b5df4                 -mov ebx, dword ptr [ebp - 0xc]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 00433d06  e8d5e30800             -call 0x4c20e0
    cpu.esp -= 4;
    sub_4c20e0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00433d0b  eb0f                   -jmp 0x433d1c
    goto L_0x00433d1c;
L_0x00433d0d:
    // 00433d0d  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 00433d10  89d9                   -mov ecx, ebx
    cpu.ecx = cpu.ebx;
    // 00433d12  89fa                   -mov edx, edi
    cpu.edx = cpu.edi;
    // 00433d14  8b5df4                 -mov ebx, dword ptr [ebp - 0xc]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 00433d17  e8c4d50800             -call 0x4c12e0
    cpu.esp -= 4;
    sub_4c12e0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00433d1c:
    // 00433d1c  8b36                   -mov esi, dword ptr [esi]
    cpu.esi = app->getMemory<x86::reg32>(cpu.esi);
    // 00433d1e  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 00433d20  740d                   -je 0x433d2f
    if (cpu.flags.zf)
    {
        goto L_0x00433d2f;
    }
    // 00433d22  668b4604               -mov ax, word ptr [esi + 4]
    cpu.ax = app->getMemory<x86::reg16>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 00433d26  6685c0                 +test ax, ax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg16>(cpu.ax & cpu.ax));
    // 00433d29  0f848efeffff           -je 0x433bbd
    if (cpu.flags.zf)
    {
        goto L_0x00433bbd;
    }
L_0x00433d2f:
    // 00433d2f  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 00433d31  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00433d33  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00433d34  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00433d35  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00433d36  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00433d37  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00433d38  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00433d39  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_433d40: native, nfs3hp::graphics::drawColouredQuadRecord */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x54 0x22 0x00 */
void Application::sub_433e30(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (colouredTriangles(app, cpu.sync())) /* port: native (tools/apply_native_render.py) */
    {
        cpu.reload();
        return;
    }
    // 00433e30  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00433e31  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00433e32  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00433e33  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00433e34  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00433e35  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00433e36  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00433e38  83ec0c                 -sub esp, 0xc
    (cpu.esp) -= x86::reg32(x86::sreg32(12 /*0xc*/));
    // 00433e3b  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
L_0x00433e3d:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00433e3d  f6460780               +test byte ptr [esi + 7], 0x80
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(cpu.esi + x86::reg32(7) /* 0x7 */) & 128 /*0x80*/));
    // 00433e41  0f84c8010000           -je 0x43400f
    if (cpu.flags.zf)
    {
        goto L_0x0043400f;
    }
    // 00433e47  833d584e550000         +cmp dword ptr [0x554e58], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5590616) /* 0x554e58 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00433e4e  7411                   -je 0x433e61
    if (cpu.flags.zf)
    {
        goto L_0x00433e61;
    }
    // 00433e50  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 00433e52  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00433e53  6a68                   -push 0x68
    app->getMemory<x86::reg32>(cpu.esp-4) = 104 /*0x68*/;
    cpu.esp -= 4;
    // 00433e55  890d584e5500           -mov dword ptr [0x554e58], ecx
    app->getMemory<x86::reg32>(x86::reg32(5590616) /* 0x554e58 */) = cpu.ecx;
    // 00433e5b  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00433e61:
    // 00433e61  8b5608                 -mov edx, dword ptr [esi + 8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(8) /* 0x8 */);
    // 00433e64  8b4640                 -mov eax, dword ptr [esi + 0x40]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(64) /* 0x40 */);
    // 00433e67  894210                 -mov dword ptr [edx + 0x10], eax
    app->getMemory<x86::reg32>(cpu.edx + x86::reg32(16) /* 0x10 */) = cpu.eax;
    // 00433e6a  8b560c                 -mov edx, dword ptr [esi + 0xc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 00433e6d  8b4644                 -mov eax, dword ptr [esi + 0x44]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(68) /* 0x44 */);
    // 00433e70  894210                 -mov dword ptr [edx + 0x10], eax
    app->getMemory<x86::reg32>(cpu.edx + x86::reg32(16) /* 0x10 */) = cpu.eax;
    // 00433e73  8b5610                 -mov edx, dword ptr [esi + 0x10]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(16) /* 0x10 */);
    // 00433e76  8b4648                 -mov eax, dword ptr [esi + 0x48]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(72) /* 0x48 */);
    // 00433e79  894210                 -mov dword ptr [edx + 0x10], eax
    app->getMemory<x86::reg32>(cpu.edx + x86::reg32(16) /* 0x10 */) = cpu.eax;
    // 00433e7c  8b5e18                 -mov ebx, dword ptr [esi + 0x18]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(24) /* 0x18 */);
    // 00433e7f  85db                   +test ebx, ebx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & cpu.ebx));
    // 00433e81  7453                   -je 0x433ed6
    if (cpu.flags.zf)
    {
        goto L_0x00433ed6;
    }
    // 00433e83  8b4608                 -mov eax, dword ptr [esi + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(8) /* 0x8 */);
    // 00433e86  8b5620                 -mov edx, dword ptr [esi + 0x20]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(32) /* 0x20 */);
    // 00433e89  895018                 -mov dword ptr [eax + 0x18], edx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */) = cpu.edx;
    // 00433e8c  8b4608                 -mov eax, dword ptr [esi + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(8) /* 0x8 */);
    // 00433e8f  8b5624                 -mov edx, dword ptr [esi + 0x24]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(36) /* 0x24 */);
    // 00433e92  89501c                 -mov dword ptr [eax + 0x1c], edx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(28) /* 0x1c */) = cpu.edx;
    // 00433e95  8b460c                 -mov eax, dword ptr [esi + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 00433e98  8b5628                 -mov edx, dword ptr [esi + 0x28]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(40) /* 0x28 */);
    // 00433e9b  895018                 -mov dword ptr [eax + 0x18], edx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */) = cpu.edx;
    // 00433e9e  8b460c                 -mov eax, dword ptr [esi + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 00433ea1  8b562c                 -mov edx, dword ptr [esi + 0x2c]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(44) /* 0x2c */);
    // 00433ea4  89501c                 -mov dword ptr [eax + 0x1c], edx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(28) /* 0x1c */) = cpu.edx;
    // 00433ea7  8b4610                 -mov eax, dword ptr [esi + 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(16) /* 0x10 */);
    // 00433eaa  8b5630                 -mov edx, dword ptr [esi + 0x30]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(48) /* 0x30 */);
    // 00433ead  895018                 -mov dword ptr [eax + 0x18], edx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */) = cpu.edx;
    // 00433eb0  8b4610                 -mov eax, dword ptr [esi + 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(16) /* 0x10 */);
    // 00433eb3  8b5634                 -mov edx, dword ptr [esi + 0x34]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(52) /* 0x34 */);
    // 00433eb6  89501c                 -mov dword ptr [eax + 0x1c], edx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(28) /* 0x1c */) = cpu.edx;
    // 00433eb9  a1544e5500             -mov eax, dword ptr [0x554e54]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5590612) /* 0x554e54 */);
    // 00433ebe  8b7e18                 -mov edi, dword ptr [esi + 0x18]
    cpu.edi = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(24) /* 0x18 */);
    // 00433ec1  39f8                   +cmp eax, edi
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.edi));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00433ec3  7429                   -je 0x433eee
    if (cpu.flags.zf)
    {
        goto L_0x00433eee;
    }
    // 00433ec5  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00433ec6  6a01                   -push 1
    app->getMemory<x86::reg32>(cpu.esp-4) = 1 /*0x1*/;
    cpu.esp -= 4;
    // 00433ec8  893d544e5500           -mov dword ptr [0x554e54], edi
    app->getMemory<x86::reg32>(x86::reg32(5590612) /* 0x554e54 */) = cpu.edi;
    // 00433ece  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00433ed4  eb18                   -jmp 0x433eee
    goto L_0x00433eee;
L_0x00433ed6:
    // 00433ed6  833d544e550000         +cmp dword ptr [0x554e54], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5590612) /* 0x554e54 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00433edd  740f                   -je 0x433eee
    if (cpu.flags.zf)
    {
        goto L_0x00433eee;
    }
    // 00433edf  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00433ee0  6a01                   -push 1
    app->getMemory<x86::reg32>(cpu.esp-4) = 1 /*0x1*/;
    cpu.esp -= 4;
    // 00433ee2  891d544e5500           -mov dword ptr [0x554e54], ebx
    app->getMemory<x86::reg32>(x86::reg32(5590612) /* 0x554e54 */) = cpu.ebx;
    // 00433ee8  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00433eee:
    // 00433eee  8b4608                 -mov eax, dword ptr [esi + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(8) /* 0x8 */);
    // 00433ef1  83781400               +cmp dword ptr [eax + 0x14], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00433ef5  0f8506010000           -jne 0x434001
    if (!cpu.flags.zf)
    {
        goto L_0x00434001;
    }
    // 00433efb  8b460c                 -mov eax, dword ptr [esi + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 00433efe  83781400               +cmp dword ptr [eax + 0x14], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00433f02  0f85f9000000           -jne 0x434001
    if (!cpu.flags.zf)
    {
        goto L_0x00434001;
    }
    // 00433f08  8b4610                 -mov eax, dword ptr [esi + 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(16) /* 0x10 */);
    // 00433f0b  83781400               +cmp dword ptr [eax + 0x14], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00433f0f  0f85ec000000           -jne 0x434001
    if (!cpu.flags.zf)
    {
        goto L_0x00434001;
    }
    // 00433f15  8b4608                 -mov eax, dword ptr [esi + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(8) /* 0x8 */);
    // 00433f18  f6400f80               +test byte ptr [eax + 0xf], 0x80
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(cpu.eax + x86::reg32(15) /* 0xf */) & 128 /*0x80*/));
    // 00433f1c  7509                   -jne 0x433f27
    if (!cpu.flags.zf)
    {
        goto L_0x00433f27;
    }
    // 00433f1e  81780c0000803f         +cmp dword ptr [eax + 0xc], 0x3f800000
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1065353216 /*0x3f800000*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00433f25  7e07                   -jle 0x433f2e
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00433f2e;
    }
L_0x00433f27:
    // 00433f27  31db                   +xor ebx, ebx
    cpu.clear_co();
    cpu.set_szp((cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx))));
    // 00433f29  895df4                 -mov dword ptr [ebp - 0xc], ebx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.ebx;
    // 00433f2c  eb08                   -jmp 0x433f36
    goto L_0x00433f36;
L_0x00433f2e:
    // 00433f2e  d9e8                   -fld1 
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = 1.0;
    // 00433f30  d8600c                 -fsub dword ptr [eax + 0xc]
    x86::Float fpu2 = cpu.fpu.sub(fpu1, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(12) /* 0xc */)));
    // 00433f33  d95df4                 -fstp dword ptr [ebp - 0xc]
    app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */) = float(fpu2);
    }
L_0x00433f36:
    // 00433f36  8b4608                 -mov eax, dword ptr [esi + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(8) /* 0x8 */);
    // 00433f39  8b55f4                 -mov edx, dword ptr [ebp - 0xc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 00433f3c  895008                 -mov dword ptr [eax + 8], edx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */) = cpu.edx;
    // 00433f3f  8b4608                 -mov eax, dword ptr [esi + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(8) /* 0x8 */);
    // 00433f42  d90594005600           -fld dword ptr [0x560094]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu3 = x86::Float(app->getMemory<float>(x86::reg32(5636244) /* 0x560094 */));
    // 00433f48  d84808                 -fmul dword ptr [eax + 8]
    x86::Float fpu4 = cpu.fpu.mul(fpu3, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */)));
    // 00433f4b  d95808                 -fstp dword ptr [eax + 8]
    app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */) = float(fpu4);
    // 00433f4e  8b4608                 -mov eax, dword ptr [esi + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(8) /* 0x8 */);
    // 00433f51  d90598005600           -fld dword ptr [0x560098]
    x86::Float fpu5 = x86::Float(app->getMemory<float>(x86::reg32(5636248) /* 0x560098 */));
    // 00433f57  d84008                 -fadd dword ptr [eax + 8]
    x86::Float fpu6 = cpu.fpu.add(fpu5, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */)));
    // 00433f5a  d95808                 -fstp dword ptr [eax + 8]
    app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */) = float(fpu6);
    // 00433f5d  8b460c                 -mov eax, dword ptr [esi + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 00433f60  f6400f80               +test byte ptr [eax + 0xf], 0x80
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(cpu.eax + x86::reg32(15) /* 0xf */) & 128 /*0x80*/));
    }
    // 00433f64  7509                   -jne 0x433f6f
    if (!cpu.flags.zf)
    {
        goto L_0x00433f6f;
    }
    // 00433f66  81780c0000803f         +cmp dword ptr [eax + 0xc], 0x3f800000
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1065353216 /*0x3f800000*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00433f6d  7e07                   -jle 0x433f76
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00433f76;
    }
L_0x00433f6f:
    // 00433f6f  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
    // 00433f71  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 00433f74  eb08                   -jmp 0x433f7e
    goto L_0x00433f7e;
L_0x00433f76:
    // 00433f76  d9e8                   -fld1 
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu7 = 1.0;
    // 00433f78  d8600c                 -fsub dword ptr [eax + 0xc]
    x86::Float fpu8 = cpu.fpu.sub(fpu7, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(12) /* 0xc */)));
    // 00433f7b  d95dfc                 -fstp dword ptr [ebp - 4]
    app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = float(fpu8);
    }
L_0x00433f7e:
    // 00433f7e  8b460c                 -mov eax, dword ptr [esi + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 00433f81  8b55fc                 -mov edx, dword ptr [ebp - 4]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00433f84  895008                 -mov dword ptr [eax + 8], edx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */) = cpu.edx;
    // 00433f87  8b460c                 -mov eax, dword ptr [esi + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 00433f8a  d90594005600           -fld dword ptr [0x560094]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu9 = x86::Float(app->getMemory<float>(x86::reg32(5636244) /* 0x560094 */));
    // 00433f90  d84808                 -fmul dword ptr [eax + 8]
    x86::Float fpu10 = cpu.fpu.mul(fpu9, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */)));
    // 00433f93  d95808                 -fstp dword ptr [eax + 8]
    app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */) = float(fpu10);
    // 00433f96  8b460c                 -mov eax, dword ptr [esi + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 00433f99  d90598005600           -fld dword ptr [0x560098]
    x86::Float fpu11 = x86::Float(app->getMemory<float>(x86::reg32(5636248) /* 0x560098 */));
    // 00433f9f  d84008                 -fadd dword ptr [eax + 8]
    x86::Float fpu12 = cpu.fpu.add(fpu11, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */)));
    // 00433fa2  d95808                 -fstp dword ptr [eax + 8]
    app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */) = float(fpu12);
    // 00433fa5  8b4610                 -mov eax, dword ptr [esi + 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(16) /* 0x10 */);
    // 00433fa8  f6400f80               +test byte ptr [eax + 0xf], 0x80
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(cpu.eax + x86::reg32(15) /* 0xf */) & 128 /*0x80*/));
    }
    // 00433fac  7509                   -jne 0x433fb7
    if (!cpu.flags.zf)
    {
        goto L_0x00433fb7;
    }
    // 00433fae  81780c0000803f         +cmp dword ptr [eax + 0xc], 0x3f800000
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1065353216 /*0x3f800000*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00433fb5  7e07                   -jle 0x433fbe
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00433fbe;
    }
L_0x00433fb7:
    // 00433fb7  31c9                   +xor ecx, ecx
    cpu.clear_co();
    cpu.set_szp((cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx))));
    // 00433fb9  894df8                 -mov dword ptr [ebp - 8], ecx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.ecx;
    // 00433fbc  eb08                   -jmp 0x433fc6
    goto L_0x00433fc6;
L_0x00433fbe:
    // 00433fbe  d9e8                   +fld1 
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu13 = 1.0;
    // 00433fc0  d8600c                 +fsub dword ptr [eax + 0xc]
    x86::Float fpu14 = cpu.fpu.sub(fpu13, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(12) /* 0xc */)));
    // 00433fc3  d95df8                 +fstp dword ptr [ebp - 8]
    app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = float(fpu14);
    }
L_0x00433fc6:
    // 00433fc6  8b4610                 -mov eax, dword ptr [esi + 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(16) /* 0x10 */);
    // 00433fc9  8b55f8                 -mov edx, dword ptr [ebp - 8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 00433fcc  895008                 -mov dword ptr [eax + 8], edx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */) = cpu.edx;
    // 00433fcf  8b4610                 -mov eax, dword ptr [esi + 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(16) /* 0x10 */);
    // 00433fd2  d90594005600           +fld dword ptr [0x560094]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu15 = x86::Float(app->getMemory<float>(x86::reg32(5636244) /* 0x560094 */));
    // 00433fd8  d84808                 +fmul dword ptr [eax + 8]
    x86::Float fpu16 = cpu.fpu.mul(fpu15, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */)));
    // 00433fdb  d95808                 +fstp dword ptr [eax + 8]
    app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */) = float(fpu16);
    // 00433fde  8b4610                 -mov eax, dword ptr [esi + 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(16) /* 0x10 */);
    // 00433fe1  d90598005600           +fld dword ptr [0x560098]
    x86::Float fpu17 = x86::Float(app->getMemory<float>(x86::reg32(5636248) /* 0x560098 */));
    // 00433fe7  d84008                 +fadd dword ptr [eax + 8]
    x86::Float fpu18 = cpu.fpu.add(fpu17, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */)));
    // 00433fea  d95808                 +fstp dword ptr [eax + 8]
    app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */) = float(fpu18);
    // 00433fed  8b5e10                 -mov ebx, dword ptr [esi + 0x10]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(16) /* 0x10 */);
    // 00433ff0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00433ff1  8b7e0c                 -mov edi, dword ptr [esi + 0xc]
    cpu.edi = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 00433ff4  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00433ff5  8b4608                 -mov eax, dword ptr [esi + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(8) /* 0x8 */);
    // 00433ff8  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    }
    // 00433ff9  ff1574f99e00           -call dword ptr [0x9ef974]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418548) /* 0x9ef974 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00433fff  eb0e                   -jmp 0x43400f
    goto L_0x0043400f;
L_0x00434001:
    // 00434001  8b5e10                 -mov ebx, dword ptr [esi + 0x10]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(16) /* 0x10 */);
    // 00434004  8b560c                 -mov edx, dword ptr [esi + 0xc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 00434007  8b4608                 -mov eax, dword ptr [esi + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(8) /* 0x8 */);
    // 0043400a  e8a1d10800             -call 0x4c11b0
    cpu.esp -= 4;
    sub_4c11b0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x0043400f:
    // 0043400f  f6460740               +test byte ptr [esi + 7], 0x40
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(cpu.esi + x86::reg32(7) /* 0x7 */) & 64 /*0x40*/));
    // 00434013  0f84e7000000           -je 0x434100
    if (cpu.flags.zf)
    {
        goto L_0x00434100;
    }
    // 00434019  833d584e550001         +cmp dword ptr [0x554e58], 1
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5590616) /* 0x554e58 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1 /*0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00434020  7414                   -je 0x434036
    if (cpu.flags.zf)
    {
        goto L_0x00434036;
    }
    // 00434022  b901000000             -mov ecx, 1
    cpu.ecx = 1 /*0x1*/;
    // 00434027  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00434028  6a68                   -push 0x68
    app->getMemory<x86::reg32>(cpu.esp-4) = 104 /*0x68*/;
    cpu.esp -= 4;
    // 0043402a  890d584e5500           -mov dword ptr [0x554e58], ecx
    app->getMemory<x86::reg32>(x86::reg32(5590616) /* 0x554e58 */) = cpu.ecx;
    // 00434030  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00434036:
    // 00434036  8b4608                 -mov eax, dword ptr [esi + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(8) /* 0x8 */);
    // 00434039  8b5674                 -mov edx, dword ptr [esi + 0x74]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(116) /* 0x74 */);
    // 0043403c  895010                 -mov dword ptr [eax + 0x10], edx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(16) /* 0x10 */) = cpu.edx;
    // 0043403f  8b560c                 -mov edx, dword ptr [esi + 0xc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 00434042  8b4678                 -mov eax, dword ptr [esi + 0x78]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(120) /* 0x78 */);
    // 00434045  894210                 -mov dword ptr [edx + 0x10], eax
    app->getMemory<x86::reg32>(cpu.edx + x86::reg32(16) /* 0x10 */) = cpu.eax;
    // 00434048  8b5610                 -mov edx, dword ptr [esi + 0x10]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(16) /* 0x10 */);
    // 0043404b  8b467c                 -mov eax, dword ptr [esi + 0x7c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(124) /* 0x7c */);
    // 0043404e  894210                 -mov dword ptr [edx + 0x10], eax
    app->getMemory<x86::reg32>(cpu.edx + x86::reg32(16) /* 0x10 */) = cpu.eax;
    // 00434051  8b5e50                 -mov ebx, dword ptr [esi + 0x50]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(80) /* 0x50 */);
    // 00434054  85db                   +test ebx, ebx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & cpu.ebx));
    // 00434056  7453                   -je 0x4340ab
    if (cpu.flags.zf)
    {
        goto L_0x004340ab;
    }
    // 00434058  8b4608                 -mov eax, dword ptr [esi + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(8) /* 0x8 */);
    // 0043405b  8b5654                 -mov edx, dword ptr [esi + 0x54]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(84) /* 0x54 */);
    // 0043405e  895018                 -mov dword ptr [eax + 0x18], edx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */) = cpu.edx;
    // 00434061  8b4608                 -mov eax, dword ptr [esi + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(8) /* 0x8 */);
    // 00434064  8b5658                 -mov edx, dword ptr [esi + 0x58]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(88) /* 0x58 */);
    // 00434067  89501c                 -mov dword ptr [eax + 0x1c], edx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(28) /* 0x1c */) = cpu.edx;
    // 0043406a  8b460c                 -mov eax, dword ptr [esi + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 0043406d  8b565c                 -mov edx, dword ptr [esi + 0x5c]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(92) /* 0x5c */);
    // 00434070  895018                 -mov dword ptr [eax + 0x18], edx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */) = cpu.edx;
    // 00434073  8b460c                 -mov eax, dword ptr [esi + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 00434076  8b5660                 -mov edx, dword ptr [esi + 0x60]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(96) /* 0x60 */);
    // 00434079  89501c                 -mov dword ptr [eax + 0x1c], edx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(28) /* 0x1c */) = cpu.edx;
    // 0043407c  8b4610                 -mov eax, dword ptr [esi + 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(16) /* 0x10 */);
    // 0043407f  8b5664                 -mov edx, dword ptr [esi + 0x64]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(100) /* 0x64 */);
    // 00434082  895018                 -mov dword ptr [eax + 0x18], edx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */) = cpu.edx;
    // 00434085  8b4610                 -mov eax, dword ptr [esi + 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(16) /* 0x10 */);
    // 00434088  8b5668                 -mov edx, dword ptr [esi + 0x68]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(104) /* 0x68 */);
    // 0043408b  89501c                 -mov dword ptr [eax + 0x1c], edx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(28) /* 0x1c */) = cpu.edx;
    // 0043408e  a1544e5500             -mov eax, dword ptr [0x554e54]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5590612) /* 0x554e54 */);
    // 00434093  8b7e50                 -mov edi, dword ptr [esi + 0x50]
    cpu.edi = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(80) /* 0x50 */);
    // 00434096  39f8                   +cmp eax, edi
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.edi));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00434098  7429                   -je 0x4340c3
    if (cpu.flags.zf)
    {
        goto L_0x004340c3;
    }
    // 0043409a  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 0043409b  6a01                   -push 1
    app->getMemory<x86::reg32>(cpu.esp-4) = 1 /*0x1*/;
    cpu.esp -= 4;
    // 0043409d  893d544e5500           -mov dword ptr [0x554e54], edi
    app->getMemory<x86::reg32>(x86::reg32(5590612) /* 0x554e54 */) = cpu.edi;
    // 004340a3  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004340a9  eb18                   -jmp 0x4340c3
    goto L_0x004340c3;
L_0x004340ab:
    // 004340ab  833d544e550000         +cmp dword ptr [0x554e54], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5590612) /* 0x554e54 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004340b2  740f                   -je 0x4340c3
    if (cpu.flags.zf)
    {
        goto L_0x004340c3;
    }
    // 004340b4  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004340b5  6a01                   -push 1
    app->getMemory<x86::reg32>(cpu.esp-4) = 1 /*0x1*/;
    cpu.esp -= 4;
    // 004340b7  891d544e5500           -mov dword ptr [0x554e54], ebx
    app->getMemory<x86::reg32>(x86::reg32(5590612) /* 0x554e54 */) = cpu.ebx;
    // 004340bd  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x004340c3:
    // 004340c3  8b4608                 -mov eax, dword ptr [esi + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(8) /* 0x8 */);
    // 004340c6  80781400               +cmp byte ptr [eax + 0x14], 0
    {
        x86::reg8 tmp1 = app->getMemory<x86::reg8>(cpu.eax + x86::reg32(20) /* 0x14 */);
        x86::reg8 tmp2 = x86::reg8(x86::sreg8(0 /*0x0*/));
        x86::reg8 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 7);
        cpu.flags.of ^= 1 & (result >> 7);
        cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
        cpu.set_szp(result);
    }
    // 004340ca  7526                   -jne 0x4340f2
    if (!cpu.flags.zf)
    {
        goto L_0x004340f2;
    }
    // 004340cc  8b460c                 -mov eax, dword ptr [esi + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 004340cf  80781400               +cmp byte ptr [eax + 0x14], 0
    {
        x86::reg8 tmp1 = app->getMemory<x86::reg8>(cpu.eax + x86::reg32(20) /* 0x14 */);
        x86::reg8 tmp2 = x86::reg8(x86::sreg8(0 /*0x0*/));
        x86::reg8 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 7);
        cpu.flags.of ^= 1 & (result >> 7);
        cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
        cpu.set_szp(result);
    }
    // 004340d3  751d                   -jne 0x4340f2
    if (!cpu.flags.zf)
    {
        goto L_0x004340f2;
    }
    // 004340d5  8b4610                 -mov eax, dword ptr [esi + 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(16) /* 0x10 */);
    // 004340d8  80781400               +cmp byte ptr [eax + 0x14], 0
    {
        x86::reg8 tmp1 = app->getMemory<x86::reg8>(cpu.eax + x86::reg32(20) /* 0x14 */);
        x86::reg8 tmp2 = x86::reg8(x86::sreg8(0 /*0x0*/));
        x86::reg8 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 7);
        cpu.flags.of ^= 1 & (result >> 7);
        cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
        cpu.set_szp(result);
    }
    // 004340dc  7514                   -jne 0x4340f2
    if (!cpu.flags.zf)
    {
        goto L_0x004340f2;
    }
    // 004340de  8b5e10                 -mov ebx, dword ptr [esi + 0x10]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(16) /* 0x10 */);
    // 004340e1  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004340e2  8b7e0c                 -mov edi, dword ptr [esi + 0xc]
    cpu.edi = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 004340e5  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004340e6  8b4608                 -mov eax, dword ptr [esi + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(8) /* 0x8 */);
    // 004340e9  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004340ea  ff1574f99e00           -call dword ptr [0x9ef974]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418548) /* 0x9ef974 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004340f0  eb0e                   -jmp 0x434100
    goto L_0x00434100;
L_0x004340f2:
    // 004340f2  8b5e10                 -mov ebx, dword ptr [esi + 0x10]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(16) /* 0x10 */);
    // 004340f5  8b560c                 -mov edx, dword ptr [esi + 0xc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 004340f8  8b4608                 -mov eax, dword ptr [esi + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(8) /* 0x8 */);
    // 004340fb  e8b0d00800             -call 0x4c11b0
    cpu.esp -= 4;
    sub_4c11b0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00434100:
    // 00434100  8b36                   -mov esi, dword ptr [esi]
    cpu.esi = app->getMemory<x86::reg32>(cpu.esi);
    // 00434102  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 00434104  740e                   -je 0x434114
    if (cpu.flags.zf)
    {
        goto L_0x00434114;
    }
    // 00434106  668b4604               -mov ax, word ptr [esi + 4]
    cpu.ax = app->getMemory<x86::reg16>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 0043410a  663d0300               +cmp ax, 3
    {
        x86::reg16 tmp1 = cpu.ax;
        x86::reg16 tmp2 = x86::reg16(x86::sreg16(3 /*0x3*/));
        x86::reg16 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 15);
        cpu.flags.of ^= 1 & (result >> 15);
        cpu.flags.of &= (1 & (tmp1 >> 15)) != (1 & (tmp2 >> 15));
        cpu.set_szp(result);
    }
    // 0043410e  0f8429fdffff           -je 0x433e3d
    if (cpu.flags.zf)
    {
        goto L_0x00433e3d;
    }
L_0x00434114:
    // 00434114  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 00434116  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00434118  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00434119  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043411a  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043411b  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043411c  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043411d  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043411e  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x90 */
void Application::sub_434120(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (triangleRecords(app, cpu.sync())) /* port: native (tools/apply_native_render.py) */
    {
        cpu.reload();
        return;
    }
    // 00434120  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00434121  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00434122  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00434123  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00434124  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00434125  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00434126  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00434128  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 0043412b  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
L_0x0043412d:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 0043412d  8b7308                 -mov esi, dword ptr [ebx + 8]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(8) /* 0x8 */);
    // 00434130  8b530c                 -mov edx, dword ptr [ebx + 0xc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(12) /* 0xc */);
    // 00434133  8a4e14                 -mov cl, byte ptr [esi + 0x14]
    cpu.cl = app->getMemory<x86::reg8>(cpu.esi + x86::reg32(20) /* 0x14 */);
    // 00434136  224a14                 -and cl, byte ptr [edx + 0x14]
    cpu.cl &= x86::reg8(x86::sreg8(app->getMemory<x86::reg8>(cpu.edx + x86::reg32(20) /* 0x14 */)));
    // 00434139  8b4310                 -mov eax, dword ptr [ebx + 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(16) /* 0x10 */);
    // 0043413c  8a6814                 -mov ch, byte ptr [eax + 0x14]
    cpu.ch = app->getMemory<x86::reg8>(cpu.eax + x86::reg32(20) /* 0x14 */);
    // 0043413f  20e9                   +and cl, ch
    cpu.clear_co();
    cpu.set_szp((cpu.cl &= x86::reg8(x86::sreg8(cpu.ch))));
    // 00434141  0f850b020000           -jne 0x434352
    if (!cpu.flags.zf)
    {
        goto L_0x00434352;
    }
    // 00434147  8a4e14                 -mov cl, byte ptr [esi + 0x14]
    cpu.cl = app->getMemory<x86::reg8>(cpu.esi + x86::reg32(20) /* 0x14 */);
    // 0043414a  8a5214                 -mov dl, byte ptr [edx + 0x14]
    cpu.dl = app->getMemory<x86::reg8>(cpu.edx + x86::reg32(20) /* 0x14 */);
    // 0043414d  80e110                 -and cl, 0x10
    cpu.cl &= x86::reg8(x86::sreg8(16 /*0x10*/));
    // 00434150  80e210                 -and dl, 0x10
    cpu.dl &= x86::reg8(x86::sreg8(16 /*0x10*/));
    // 00434153  88e8                   -mov al, ch
    cpu.al = cpu.ch;
    // 00434155  08ca                   -or dl, cl
    cpu.dl |= x86::reg8(x86::sreg8(cpu.cl));
    // 00434157  2410                   -and al, 0x10
    cpu.al &= x86::reg8(x86::sreg8(16 /*0x10*/));
    // 00434159  08d0                   +or al, dl
    cpu.clear_co();
    cpu.set_szp((cpu.al |= x86::reg8(x86::sreg8(cpu.dl))));
    // 0043415b  0f85e6010000           -jne 0x434347
    if (!cpu.flags.zf)
    {
        goto L_0x00434347;
    }
    // 00434161  833d584e550000         +cmp dword ptr [0x554e58], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5590616) /* 0x554e58 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00434168  7411                   -je 0x43417b
    if (cpu.flags.zf)
    {
        goto L_0x0043417b;
    }
    // 0043416a  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 0043416c  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 0043416d  6a68                   -push 0x68
    app->getMemory<x86::reg32>(cpu.esp-4) = 104 /*0x68*/;
    cpu.esp -= 4;
    // 0043416f  890d584e5500           -mov dword ptr [0x554e58], ecx
    app->getMemory<x86::reg32>(x86::reg32(5590616) /* 0x554e58 */) = cpu.ecx;
    // 00434175  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x0043417b:
    // 0043417b  8b7318                 -mov esi, dword ptr [ebx + 0x18]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(24) /* 0x18 */);
    // 0043417e  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 00434180  7453                   -je 0x4341d5
    if (cpu.flags.zf)
    {
        goto L_0x004341d5;
    }
    // 00434182  8b4308                 -mov eax, dword ptr [ebx + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(8) /* 0x8 */);
    // 00434185  8b5320                 -mov edx, dword ptr [ebx + 0x20]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(32) /* 0x20 */);
    // 00434188  895018                 -mov dword ptr [eax + 0x18], edx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */) = cpu.edx;
    // 0043418b  8b4308                 -mov eax, dword ptr [ebx + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(8) /* 0x8 */);
    // 0043418e  8b5324                 -mov edx, dword ptr [ebx + 0x24]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(36) /* 0x24 */);
    // 00434191  89501c                 -mov dword ptr [eax + 0x1c], edx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(28) /* 0x1c */) = cpu.edx;
    // 00434194  8b430c                 -mov eax, dword ptr [ebx + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(12) /* 0xc */);
    // 00434197  8b5328                 -mov edx, dword ptr [ebx + 0x28]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(40) /* 0x28 */);
    // 0043419a  895018                 -mov dword ptr [eax + 0x18], edx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */) = cpu.edx;
    // 0043419d  8b430c                 -mov eax, dword ptr [ebx + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(12) /* 0xc */);
    // 004341a0  8b532c                 -mov edx, dword ptr [ebx + 0x2c]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(44) /* 0x2c */);
    // 004341a3  89501c                 -mov dword ptr [eax + 0x1c], edx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(28) /* 0x1c */) = cpu.edx;
    // 004341a6  8b4310                 -mov eax, dword ptr [ebx + 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(16) /* 0x10 */);
    // 004341a9  8b5330                 -mov edx, dword ptr [ebx + 0x30]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(48) /* 0x30 */);
    // 004341ac  895018                 -mov dword ptr [eax + 0x18], edx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */) = cpu.edx;
    // 004341af  8b4310                 -mov eax, dword ptr [ebx + 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(16) /* 0x10 */);
    // 004341b2  8b5334                 -mov edx, dword ptr [ebx + 0x34]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(52) /* 0x34 */);
    // 004341b5  89501c                 -mov dword ptr [eax + 0x1c], edx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(28) /* 0x1c */) = cpu.edx;
    // 004341b8  a1544e5500             -mov eax, dword ptr [0x554e54]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5590612) /* 0x554e54 */);
    // 004341bd  8b7b18                 -mov edi, dword ptr [ebx + 0x18]
    cpu.edi = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(24) /* 0x18 */);
    // 004341c0  39f8                   +cmp eax, edi
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.edi));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004341c2  7429                   -je 0x4341ed
    if (cpu.flags.zf)
    {
        goto L_0x004341ed;
    }
    // 004341c4  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004341c5  6a01                   -push 1
    app->getMemory<x86::reg32>(cpu.esp-4) = 1 /*0x1*/;
    cpu.esp -= 4;
    // 004341c7  893d544e5500           -mov dword ptr [0x554e54], edi
    app->getMemory<x86::reg32>(x86::reg32(5590612) /* 0x554e54 */) = cpu.edi;
    // 004341cd  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004341d3  eb18                   -jmp 0x4341ed
    goto L_0x004341ed;
L_0x004341d5:
    // 004341d5  833d544e550000         +cmp dword ptr [0x554e54], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5590612) /* 0x554e54 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004341dc  740f                   -je 0x4341ed
    if (cpu.flags.zf)
    {
        goto L_0x004341ed;
    }
    // 004341de  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004341df  6a01                   -push 1
    app->getMemory<x86::reg32>(cpu.esp-4) = 1 /*0x1*/;
    cpu.esp -= 4;
    // 004341e1  8935544e5500           -mov dword ptr [0x554e54], esi
    app->getMemory<x86::reg32>(x86::reg32(5590612) /* 0x554e54 */) = cpu.esi;
    // 004341e7  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x004341ed:
    // 004341ed  8b5308                 -mov edx, dword ptr [ebx + 8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(8) /* 0x8 */);
    // 004341f0  8b730c                 -mov esi, dword ptr [ebx + 0xc]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(12) /* 0xc */);
    // 004341f3  8b4214                 -mov eax, dword ptr [edx + 0x14]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(20) /* 0x14 */);
    // 004341f6  8b4e14                 -mov ecx, dword ptr [esi + 0x14]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(20) /* 0x14 */);
    // 004341f9  83e001                 -and eax, 1
    cpu.eax &= x86::reg32(x86::sreg32(1 /*0x1*/));
    // 004341fc  83e101                 -and ecx, 1
    cpu.ecx &= x86::reg32(x86::sreg32(1 /*0x1*/));
    // 004341ff  09c1                   -or ecx, eax
    cpu.ecx |= x86::reg32(x86::sreg32(cpu.eax));
    // 00434201  8b4310                 -mov eax, dword ptr [ebx + 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(16) /* 0x10 */);
    // 00434204  8b7814                 -mov edi, dword ptr [eax + 0x14]
    cpu.edi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */);
    // 00434207  83e701                 -and edi, 1
    cpu.edi &= x86::reg32(x86::sreg32(1 /*0x1*/));
    // 0043420a  09f9                   +or ecx, edi
    cpu.clear_co();
    cpu.set_szp((cpu.ecx |= x86::reg32(x86::sreg32(cpu.edi))));
    // 0043420c  750b                   -jne 0x434219
    if (!cpu.flags.zf)
    {
        goto L_0x00434219;
    }
    // 0043420e  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 0043420f  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00434210  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00434211  ff1574f99e00           -call dword ptr [0x9ef974]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418548) /* 0x9ef974 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00434217  eb2c                   -jmp 0x434245
    goto L_0x00434245;
L_0x00434219:
    // 00434219  6a01                   -push 1
    app->getMemory<x86::reg32>(cpu.esp-4) = 1 /*0x1*/;
    cpu.esp -= 4;
    // 0043421b  68c2020000             -push 0x2c2
    app->getMemory<x86::reg32>(cpu.esp-4) = 706 /*0x2c2*/;
    cpu.esp -= 4;
    // 00434220  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00434226  8b4310                 -mov eax, dword ptr [ebx + 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(16) /* 0x10 */);
    // 00434229  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 0043422a  8b530c                 -mov edx, dword ptr [ebx + 0xc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(12) /* 0xc */);
    // 0043422d  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 0043422e  8b4b08                 -mov ecx, dword ptr [ebx + 8]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(8) /* 0x8 */);
    // 00434231  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00434232  ff1574f99e00           -call dword ptr [0x9ef974]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418548) /* 0x9ef974 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00434238  6a00                   -push 0
    app->getMemory<x86::reg32>(cpu.esp-4) = 0 /*0x0*/;
    cpu.esp -= 4;
    // 0043423a  68c2020000             -push 0x2c2
    app->getMemory<x86::reg32>(cpu.esp-4) = 706 /*0x2c2*/;
    cpu.esp -= 4;
    // 0043423f  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00434245:
    // 00434245  f6430740               +test byte ptr [ebx + 7], 0x40
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(cpu.ebx + x86::reg32(7) /* 0x7 */) & 64 /*0x40*/));
    // 00434249  0f8403010000           -je 0x434352
    if (cpu.flags.zf)
    {
        goto L_0x00434352;
    }
    // 0043424f  833d584e550001         +cmp dword ptr [0x554e58], 1
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5590616) /* 0x554e58 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1 /*0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00434256  7414                   -je 0x43426c
    if (cpu.flags.zf)
    {
        goto L_0x0043426c;
    }
    // 00434258  bf01000000             -mov edi, 1
    cpu.edi = 1 /*0x1*/;
    // 0043425d  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 0043425e  6a68                   -push 0x68
    app->getMemory<x86::reg32>(cpu.esp-4) = 104 /*0x68*/;
    cpu.esp -= 4;
    // 00434260  893d584e5500           -mov dword ptr [0x554e58], edi
    app->getMemory<x86::reg32>(x86::reg32(5590616) /* 0x554e58 */) = cpu.edi;
    // 00434266  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x0043426c:
    // 0043426c  8b4350                 -mov eax, dword ptr [ebx + 0x50]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(80) /* 0x50 */);
    // 0043426f  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00434271  7453                   -je 0x4342c6
    if (cpu.flags.zf)
    {
        goto L_0x004342c6;
    }
    // 00434273  8b4308                 -mov eax, dword ptr [ebx + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(8) /* 0x8 */);
    // 00434276  8b5354                 -mov edx, dword ptr [ebx + 0x54]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(84) /* 0x54 */);
    // 00434279  895018                 -mov dword ptr [eax + 0x18], edx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */) = cpu.edx;
    // 0043427c  8b4308                 -mov eax, dword ptr [ebx + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(8) /* 0x8 */);
    // 0043427f  8b5358                 -mov edx, dword ptr [ebx + 0x58]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(88) /* 0x58 */);
    // 00434282  89501c                 -mov dword ptr [eax + 0x1c], edx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(28) /* 0x1c */) = cpu.edx;
    // 00434285  8b430c                 -mov eax, dword ptr [ebx + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(12) /* 0xc */);
    // 00434288  8b535c                 -mov edx, dword ptr [ebx + 0x5c]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(92) /* 0x5c */);
    // 0043428b  895018                 -mov dword ptr [eax + 0x18], edx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */) = cpu.edx;
    // 0043428e  8b430c                 -mov eax, dword ptr [ebx + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(12) /* 0xc */);
    // 00434291  8b5360                 -mov edx, dword ptr [ebx + 0x60]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(96) /* 0x60 */);
    // 00434294  89501c                 -mov dword ptr [eax + 0x1c], edx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(28) /* 0x1c */) = cpu.edx;
    // 00434297  8b4310                 -mov eax, dword ptr [ebx + 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(16) /* 0x10 */);
    // 0043429a  8b5364                 -mov edx, dword ptr [ebx + 0x64]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(100) /* 0x64 */);
    // 0043429d  895018                 -mov dword ptr [eax + 0x18], edx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */) = cpu.edx;
    // 004342a0  8b4310                 -mov eax, dword ptr [ebx + 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(16) /* 0x10 */);
    // 004342a3  8b5368                 -mov edx, dword ptr [ebx + 0x68]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(104) /* 0x68 */);
    // 004342a6  89501c                 -mov dword ptr [eax + 0x1c], edx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(28) /* 0x1c */) = cpu.edx;
    // 004342a9  a1544e5500             -mov eax, dword ptr [0x554e54]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5590612) /* 0x554e54 */);
    // 004342ae  8b5350                 -mov edx, dword ptr [ebx + 0x50]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(80) /* 0x50 */);
    // 004342b1  39d0                   +cmp eax, edx
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.edx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004342b3  7428                   -je 0x4342dd
    if (cpu.flags.zf)
    {
        goto L_0x004342dd;
    }
    // 004342b5  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004342b6  6a01                   -push 1
    app->getMemory<x86::reg32>(cpu.esp-4) = 1 /*0x1*/;
    cpu.esp -= 4;
    // 004342b8  8915544e5500           -mov dword ptr [0x554e54], edx
    app->getMemory<x86::reg32>(x86::reg32(5590612) /* 0x554e54 */) = cpu.edx;
    // 004342be  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004342c4  eb17                   -jmp 0x4342dd
    goto L_0x004342dd;
L_0x004342c6:
    // 004342c6  833d544e550000         +cmp dword ptr [0x554e54], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5590612) /* 0x554e54 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004342cd  740e                   -je 0x4342dd
    if (cpu.flags.zf)
    {
        goto L_0x004342dd;
    }
    // 004342cf  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004342d0  6a01                   -push 1
    app->getMemory<x86::reg32>(cpu.esp-4) = 1 /*0x1*/;
    cpu.esp -= 4;
    // 004342d2  a3544e5500             -mov dword ptr [0x554e54], eax
    app->getMemory<x86::reg32>(x86::reg32(5590612) /* 0x554e54 */) = cpu.eax;
    // 004342d7  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x004342dd:
    // 004342dd  8b4308                 -mov eax, dword ptr [ebx + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(8) /* 0x8 */);
    // 004342e0  8b730c                 -mov esi, dword ptr [ebx + 0xc]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(12) /* 0xc */);
    // 004342e3  8b4814                 -mov ecx, dword ptr [eax + 0x14]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */);
    // 004342e6  8b5614                 -mov edx, dword ptr [esi + 0x14]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(20) /* 0x14 */);
    // 004342e9  83e101                 -and ecx, 1
    cpu.ecx &= x86::reg32(x86::sreg32(1 /*0x1*/));
    // 004342ec  83e201                 -and edx, 1
    cpu.edx &= x86::reg32(x86::sreg32(1 /*0x1*/));
    // 004342ef  09d1                   -or ecx, edx
    cpu.ecx |= x86::reg32(x86::sreg32(cpu.edx));
    // 004342f1  8b5310                 -mov edx, dword ptr [ebx + 0x10]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(16) /* 0x10 */);
    // 004342f4  894dfc                 -mov dword ptr [ebp - 4], ecx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.ecx;
    // 004342f7  8b4a14                 -mov ecx, dword ptr [edx + 0x14]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(20) /* 0x14 */);
    // 004342fa  8b7dfc                 -mov edi, dword ptr [ebp - 4]
    cpu.edi = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004342fd  83e101                 -and ecx, 1
    cpu.ecx &= x86::reg32(x86::sreg32(1 /*0x1*/));
    // 00434300  09f9                   +or ecx, edi
    cpu.clear_co();
    cpu.set_szp((cpu.ecx |= x86::reg32(x86::sreg32(cpu.edi))));
    // 00434302  750b                   -jne 0x43430f
    if (!cpu.flags.zf)
    {
        goto L_0x0043430f;
    }
    // 00434304  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00434305  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00434306  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00434307  ff1574f99e00           -call dword ptr [0x9ef974]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418548) /* 0x9ef974 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0043430d  eb43                   -jmp 0x434352
    goto L_0x00434352;
L_0x0043430f:
    // 0043430f  6a01                   -push 1
    app->getMemory<x86::reg32>(cpu.esp-4) = 1 /*0x1*/;
    cpu.esp -= 4;
    // 00434311  68c2020000             -push 0x2c2
    app->getMemory<x86::reg32>(cpu.esp-4) = 706 /*0x2c2*/;
    cpu.esp -= 4;
    // 00434316  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0043431c  8b4310                 -mov eax, dword ptr [ebx + 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(16) /* 0x10 */);
    // 0043431f  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00434320  8b530c                 -mov edx, dword ptr [ebx + 0xc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(12) /* 0xc */);
    // 00434323  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00434324  8b4b08                 -mov ecx, dword ptr [ebx + 8]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(8) /* 0x8 */);
    // 00434327  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00434328  ff1574f99e00           -call dword ptr [0x9ef974]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418548) /* 0x9ef974 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0043432e  6a00                   -push 0
    app->getMemory<x86::reg32>(cpu.esp-4) = 0 /*0x0*/;
    cpu.esp -= 4;
    // 00434330  68c2020000             -push 0x2c2
    app->getMemory<x86::reg32>(cpu.esp-4) = 706 /*0x2c2*/;
    cpu.esp -= 4;
    // 00434335  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0043433b  8b1b                   -mov ebx, dword ptr [ebx]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.ebx);
    // 0043433d  85db                   +test ebx, ebx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & cpu.ebx));
    // 0043433f  7425                   -je 0x434366
    if (cpu.flags.zf)
    {
        goto L_0x00434366;
    }
    // 00434341  668b4304               -mov ax, word ptr [ebx + 4]
    cpu.ax = app->getMemory<x86::reg16>(cpu.ebx + x86::reg32(4) /* 0x4 */);
    // 00434345  eb15                   -jmp 0x43435c
    goto L_0x0043435c;
L_0x00434347:
    // 00434347  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00434349  88c2                   -mov dl, al
    cpu.dl = cpu.al;
    // 0043434b  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 0043434d  e87ef70800             -call 0x4c3ad0
    cpu.esp -= 4;
    sub_4c3ad0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00434352:
    // 00434352  8b1b                   -mov ebx, dword ptr [ebx]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.ebx);
    // 00434354  85db                   +test ebx, ebx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & cpu.ebx));
    // 00434356  740e                   -je 0x434366
    if (cpu.flags.zf)
    {
        goto L_0x00434366;
    }
    // 00434358  668b4304               -mov ax, word ptr [ebx + 4]
    cpu.ax = app->getMemory<x86::reg16>(cpu.ebx + x86::reg32(4) /* 0x4 */);
L_0x0043435c:
    // 0043435c  663d0300               +cmp ax, 3
    {
        x86::reg16 tmp1 = cpu.ax;
        x86::reg16 tmp2 = x86::reg16(x86::sreg16(3 /*0x3*/));
        x86::reg16 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 15);
        cpu.flags.of ^= 1 & (result >> 15);
        cpu.flags.of &= (1 & (tmp1 >> 15)) != (1 & (tmp2 >> 15));
        cpu.set_szp(result);
    }
    // 00434360  0f84c7fdffff           -je 0x43412d
    if (cpu.flags.zf)
    {
        goto L_0x0043412d;
    }
L_0x00434366:
    // 00434366  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 00434368  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 0043436a  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043436b  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043436c  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043436d  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043436e  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043436f  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00434370  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x8d 0x40 0x00 */
void Application::sub_434380(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (submitPolygons(app, cpu.sync())) /* port: native (tools/apply_native_vertices.py) */
    {
        cpu.reload();
        return;
    }
    // 00434380  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00434381  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00434382  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00434383  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00434384  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00434385  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00434386  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00434388  83ec18                 -sub esp, 0x18
    (cpu.esp) -= x86::reg32(x86::sreg32(24 /*0x18*/));
    // 0043438b  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 0043438d  89c7                   -mov edi, eax
    cpu.edi = cpu.eax;
L_0x0043438f:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 0043438f  f6460780               +test byte ptr [esi + 7], 0x80
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(cpu.esi + x86::reg32(7) /* 0x7 */) & 128 /*0x80*/));
    // 00434393  0f8486020000           -je 0x43461f
    if (cpu.flags.zf)
    {
        goto L_0x0043461f;
    }
    // 00434399  833d584e550000         +cmp dword ptr [0x554e58], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5590616) /* 0x554e58 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004343a0  7411                   -je 0x4343b3
    if (cpu.flags.zf)
    {
        goto L_0x004343b3;
    }
    // 004343a2  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 004343a4  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004343a5  6a68                   -push 0x68
    app->getMemory<x86::reg32>(cpu.esp-4) = 104 /*0x68*/;
    cpu.esp -= 4;
    // 004343a7  890d584e5500           -mov dword ptr [0x554e58], ecx
    app->getMemory<x86::reg32>(x86::reg32(5590616) /* 0x554e58 */) = cpu.ecx;
    // 004343ad  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x004343b3:
    // 004343b3  8b5608                 -mov edx, dword ptr [esi + 8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(8) /* 0x8 */);
    // 004343b6  8b4640                 -mov eax, dword ptr [esi + 0x40]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(64) /* 0x40 */);
    // 004343b9  894210                 -mov dword ptr [edx + 0x10], eax
    app->getMemory<x86::reg32>(cpu.edx + x86::reg32(16) /* 0x10 */) = cpu.eax;
    // 004343bc  8b560c                 -mov edx, dword ptr [esi + 0xc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 004343bf  8b4644                 -mov eax, dword ptr [esi + 0x44]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(68) /* 0x44 */);
    // 004343c2  894210                 -mov dword ptr [edx + 0x10], eax
    app->getMemory<x86::reg32>(cpu.edx + x86::reg32(16) /* 0x10 */) = cpu.eax;
    // 004343c5  8b5610                 -mov edx, dword ptr [esi + 0x10]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(16) /* 0x10 */);
    // 004343c8  8b4648                 -mov eax, dword ptr [esi + 0x48]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(72) /* 0x48 */);
    // 004343cb  894210                 -mov dword ptr [edx + 0x10], eax
    app->getMemory<x86::reg32>(cpu.edx + x86::reg32(16) /* 0x10 */) = cpu.eax;
    // 004343ce  837e1800               +cmp dword ptr [esi + 0x18], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(24) /* 0x18 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004343d2  7453                   -je 0x434427
    if (cpu.flags.zf)
    {
        goto L_0x00434427;
    }
    // 004343d4  8b4608                 -mov eax, dword ptr [esi + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(8) /* 0x8 */);
    // 004343d7  8b5620                 -mov edx, dword ptr [esi + 0x20]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(32) /* 0x20 */);
    // 004343da  895018                 -mov dword ptr [eax + 0x18], edx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */) = cpu.edx;
    // 004343dd  8b4608                 -mov eax, dword ptr [esi + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(8) /* 0x8 */);
    // 004343e0  8b5624                 -mov edx, dword ptr [esi + 0x24]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(36) /* 0x24 */);
    // 004343e3  89501c                 -mov dword ptr [eax + 0x1c], edx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(28) /* 0x1c */) = cpu.edx;
    // 004343e6  8b460c                 -mov eax, dword ptr [esi + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 004343e9  8b5628                 -mov edx, dword ptr [esi + 0x28]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(40) /* 0x28 */);
    // 004343ec  895018                 -mov dword ptr [eax + 0x18], edx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */) = cpu.edx;
    // 004343ef  8b460c                 -mov eax, dword ptr [esi + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 004343f2  8b562c                 -mov edx, dword ptr [esi + 0x2c]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(44) /* 0x2c */);
    // 004343f5  89501c                 -mov dword ptr [eax + 0x1c], edx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(28) /* 0x1c */) = cpu.edx;
    // 004343f8  8b4610                 -mov eax, dword ptr [esi + 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(16) /* 0x10 */);
    // 004343fb  8b5630                 -mov edx, dword ptr [esi + 0x30]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(48) /* 0x30 */);
    // 004343fe  895018                 -mov dword ptr [eax + 0x18], edx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */) = cpu.edx;
    // 00434401  8b4610                 -mov eax, dword ptr [esi + 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(16) /* 0x10 */);
    // 00434404  8b5634                 -mov edx, dword ptr [esi + 0x34]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(52) /* 0x34 */);
    // 00434407  89501c                 -mov dword ptr [eax + 0x1c], edx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(28) /* 0x1c */) = cpu.edx;
    // 0043440a  a1544e5500             -mov eax, dword ptr [0x554e54]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5590612) /* 0x554e54 */);
    // 0043440f  8b5618                 -mov edx, dword ptr [esi + 0x18]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(24) /* 0x18 */);
    // 00434412  39d0                   +cmp eax, edx
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.edx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00434414  742a                   -je 0x434440
    if (cpu.flags.zf)
    {
        goto L_0x00434440;
    }
    // 00434416  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00434417  6a01                   -push 1
    app->getMemory<x86::reg32>(cpu.esp-4) = 1 /*0x1*/;
    cpu.esp -= 4;
    // 00434419  8915544e5500           -mov dword ptr [0x554e54], edx
    app->getMemory<x86::reg32>(x86::reg32(5590612) /* 0x554e54 */) = cpu.edx;
    // 0043441f  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00434425  eb19                   -jmp 0x434440
    goto L_0x00434440;
L_0x00434427:
    // 00434427  833d544e550000         +cmp dword ptr [0x554e54], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5590612) /* 0x554e54 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0043442e  7410                   -je 0x434440
    if (cpu.flags.zf)
    {
        goto L_0x00434440;
    }
    // 00434430  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00434432  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00434433  6a01                   -push 1
    app->getMemory<x86::reg32>(cpu.esp-4) = 1 /*0x1*/;
    cpu.esp -= 4;
    // 00434435  a3544e5500             -mov dword ptr [0x554e54], eax
    app->getMemory<x86::reg32>(x86::reg32(5590612) /* 0x554e54 */) = cpu.eax;
    // 0043443a  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00434440:
    // 00434440  8b4608                 -mov eax, dword ptr [esi + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(8) /* 0x8 */);
    // 00434443  83781400               +cmp dword ptr [eax + 0x14], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00434447  0f85c4010000           -jne 0x434611
    if (!cpu.flags.zf)
    {
        goto L_0x00434611;
    }
    // 0043444d  8b460c                 -mov eax, dword ptr [esi + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 00434450  83781400               +cmp dword ptr [eax + 0x14], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00434454  0f85b7010000           -jne 0x434611
    if (!cpu.flags.zf)
    {
        goto L_0x00434611;
    }
    // 0043445a  8b4610                 -mov eax, dword ptr [esi + 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(16) /* 0x10 */);
    // 0043445d  83781400               +cmp dword ptr [eax + 0x14], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00434461  0f85aa010000           -jne 0x434611
    if (!cpu.flags.zf)
    {
        goto L_0x00434611;
    }
    // 00434467  8b4608                 -mov eax, dword ptr [esi + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(8) /* 0x8 */);
    // 0043446a  f6400f80               +test byte ptr [eax + 0xf], 0x80
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(cpu.eax + x86::reg32(15) /* 0xf */) & 128 /*0x80*/));
    // 0043446e  7509                   -jne 0x434479
    if (!cpu.flags.zf)
    {
        goto L_0x00434479;
    }
    // 00434470  81780c0000803f         +cmp dword ptr [eax + 0xc], 0x3f800000
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1065353216 /*0x3f800000*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00434477  7e07                   -jle 0x434480
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00434480;
    }
L_0x00434479:
    // 00434479  31c9                   +xor ecx, ecx
    cpu.clear_co();
    cpu.set_szp((cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx))));
    // 0043447b  894dec                 -mov dword ptr [ebp - 0x14], ecx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */) = cpu.ecx;
    // 0043447e  eb08                   -jmp 0x434488
    goto L_0x00434488;
L_0x00434480:
    // 00434480  d9e8                   -fld1 
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = 1.0;
    // 00434482  d8600c                 -fsub dword ptr [eax + 0xc]
    x86::Float fpu2 = cpu.fpu.sub(fpu1, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(12) /* 0xc */)));
    // 00434485  d95dec                 -fstp dword ptr [ebp - 0x14]
    app->getMemory<float>(cpu.ebp + x86::reg32(-20) /* -0x14 */) = float(fpu2);
    }
L_0x00434488:
    // 00434488  8b4608                 -mov eax, dword ptr [esi + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(8) /* 0x8 */);
    // 0043448b  8b55ec                 -mov edx, dword ptr [ebp - 0x14]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */);
    // 0043448e  895008                 -mov dword ptr [eax + 8], edx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */) = cpu.edx;
    // 00434491  8b4608                 -mov eax, dword ptr [esi + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(8) /* 0x8 */);
    // 00434494  d90594005600           -fld dword ptr [0x560094]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu3 = x86::Float(app->getMemory<float>(x86::reg32(5636244) /* 0x560094 */));
    // 0043449a  d84808                 -fmul dword ptr [eax + 8]
    x86::Float fpu4 = cpu.fpu.mul(fpu3, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */)));
    // 0043449d  d95808                 -fstp dword ptr [eax + 8]
    app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */) = float(fpu4);
    // 004344a0  8b4608                 -mov eax, dword ptr [esi + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(8) /* 0x8 */);
    // 004344a3  d90598005600           -fld dword ptr [0x560098]
    x86::Float fpu5 = x86::Float(app->getMemory<float>(x86::reg32(5636248) /* 0x560098 */));
    // 004344a9  d84008                 -fadd dword ptr [eax + 8]
    x86::Float fpu6 = cpu.fpu.add(fpu5, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */)));
    // 004344ac  d95808                 -fstp dword ptr [eax + 8]
    app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */) = float(fpu6);
    // 004344af  8b460c                 -mov eax, dword ptr [esi + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 004344b2  f6400f80               +test byte ptr [eax + 0xf], 0x80
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(cpu.eax + x86::reg32(15) /* 0xf */) & 128 /*0x80*/));
    }
    // 004344b6  7509                   -jne 0x4344c1
    if (!cpu.flags.zf)
    {
        goto L_0x004344c1;
    }
    // 004344b8  81780c0000803f         +cmp dword ptr [eax + 0xc], 0x3f800000
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1065353216 /*0x3f800000*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004344bf  7e07                   -jle 0x4344c8
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004344c8;
    }
L_0x004344c1:
    // 004344c1  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
    // 004344c3  8945f8                 -mov dword ptr [ebp - 8], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.eax;
    // 004344c6  eb08                   -jmp 0x4344d0
    goto L_0x004344d0;
L_0x004344c8:
    // 004344c8  d9e8                   -fld1 
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu7 = 1.0;
    // 004344ca  d8600c                 -fsub dword ptr [eax + 0xc]
    x86::Float fpu8 = cpu.fpu.sub(fpu7, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(12) /* 0xc */)));
    // 004344cd  d95df8                 -fstp dword ptr [ebp - 8]
    app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = float(fpu8);
    }
L_0x004344d0:
    // 004344d0  8b460c                 -mov eax, dword ptr [esi + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 004344d3  8b55f8                 -mov edx, dword ptr [ebp - 8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004344d6  895008                 -mov dword ptr [eax + 8], edx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */) = cpu.edx;
    // 004344d9  8b460c                 -mov eax, dword ptr [esi + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 004344dc  d90594005600           -fld dword ptr [0x560094]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu9 = x86::Float(app->getMemory<float>(x86::reg32(5636244) /* 0x560094 */));
    // 004344e2  d84808                 -fmul dword ptr [eax + 8]
    x86::Float fpu10 = cpu.fpu.mul(fpu9, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */)));
    // 004344e5  d95808                 -fstp dword ptr [eax + 8]
    app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */) = float(fpu10);
    // 004344e8  8b460c                 -mov eax, dword ptr [esi + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 004344eb  d90598005600           -fld dword ptr [0x560098]
    x86::Float fpu11 = x86::Float(app->getMemory<float>(x86::reg32(5636248) /* 0x560098 */));
    // 004344f1  d84008                 -fadd dword ptr [eax + 8]
    x86::Float fpu12 = cpu.fpu.add(fpu11, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */)));
    // 004344f4  d95808                 -fstp dword ptr [eax + 8]
    app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */) = float(fpu12);
    // 004344f7  8b4610                 -mov eax, dword ptr [esi + 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(16) /* 0x10 */);
    // 004344fa  f6400f80               +test byte ptr [eax + 0xf], 0x80
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(cpu.eax + x86::reg32(15) /* 0xf */) & 128 /*0x80*/));
    }
    // 004344fe  7509                   -jne 0x434509
    if (!cpu.flags.zf)
    {
        goto L_0x00434509;
    }
    // 00434500  81780c0000803f         +cmp dword ptr [eax + 0xc], 0x3f800000
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1065353216 /*0x3f800000*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00434507  7e07                   -jle 0x434510
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00434510;
    }
L_0x00434509:
    // 00434509  31c9                   +xor ecx, ecx
    cpu.clear_co();
    cpu.set_szp((cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx))));
    // 0043450b  894df4                 -mov dword ptr [ebp - 0xc], ecx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.ecx;
    // 0043450e  eb08                   -jmp 0x434518
    goto L_0x00434518;
L_0x00434510:
    // 00434510  d9e8                   -fld1 
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu13 = 1.0;
    // 00434512  d8600c                 -fsub dword ptr [eax + 0xc]
    x86::Float fpu14 = cpu.fpu.sub(fpu13, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(12) /* 0xc */)));
    // 00434515  d95df4                 -fstp dword ptr [ebp - 0xc]
    app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */) = float(fpu14);
    }
L_0x00434518:
    // 00434518  8b4610                 -mov eax, dword ptr [esi + 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(16) /* 0x10 */);
    // 0043451b  8b55f4                 -mov edx, dword ptr [ebp - 0xc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 0043451e  895008                 -mov dword ptr [eax + 8], edx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */) = cpu.edx;
    // 00434521  8b4610                 -mov eax, dword ptr [esi + 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(16) /* 0x10 */);
    // 00434524  d90594005600           -fld dword ptr [0x560094]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu15 = x86::Float(app->getMemory<float>(x86::reg32(5636244) /* 0x560094 */));
    // 0043452a  d84808                 -fmul dword ptr [eax + 8]
    x86::Float fpu16 = cpu.fpu.mul(fpu15, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */)));
    // 0043452d  d95808                 -fstp dword ptr [eax + 8]
    app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */) = float(fpu16);
    // 00434530  8b4610                 -mov eax, dword ptr [esi + 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(16) /* 0x10 */);
    // 00434533  d90598005600           -fld dword ptr [0x560098]
    x86::Float fpu17 = x86::Float(app->getMemory<float>(x86::reg32(5636248) /* 0x560098 */));
    // 00434539  d84008                 -fadd dword ptr [eax + 8]
    x86::Float fpu18 = cpu.fpu.add(fpu17, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */)));
    // 0043453c  d95808                 -fstp dword ptr [eax + 8]
    app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */) = float(fpu18);
    // 0043453f  8b5e10                 -mov ebx, dword ptr [esi + 0x10]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(16) /* 0x10 */);
    // 00434542  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00434543  8b460c                 -mov eax, dword ptr [esi + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 00434546  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00434547  8b5608                 -mov edx, dword ptr [esi + 8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(8) /* 0x8 */);
    // 0043454a  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    }
    // 0043454b  ff1574f99e00           -call dword ptr [0x9ef974]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418548) /* 0x9ef974 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00434551  8b36                   -mov esi, dword ptr [esi]
    cpu.esi = app->getMemory<x86::reg32>(cpu.esi);
    // 00434553  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 00434555  740e                   -je 0x434565
    if (cpu.flags.zf)
    {
        goto L_0x00434565;
    }
    // 00434557  668b4604               -mov ax, word ptr [esi + 4]
    cpu.ax = app->getMemory<x86::reg16>(cpu.esi + x86::reg32(4) /* 0x4 */);
L_0x0043455b:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 0043455b  663d0300               +cmp ax, 3
    {
        x86::reg16 tmp1 = cpu.ax;
        x86::reg16 tmp2 = x86::reg16(x86::sreg16(3 /*0x3*/));
        x86::reg16 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 15);
        cpu.flags.of ^= 1 & (result >> 15);
        cpu.flags.of &= (1 & (tmp1 >> 15)) != (1 & (tmp2 >> 15));
        cpu.set_szp(result);
    }
    // 0043455f  0f842afeffff           -je 0x43438f
    if (cpu.flags.zf)
    {
        goto L_0x0043438f;
    }
L_0x00434565:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00434565  89fe                   -mov esi, edi
    cpu.esi = cpu.edi;
L_0x00434567:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00434567  8a7e07                 -mov bh, byte ptr [esi + 7]
    cpu.bh = app->getMemory<x86::reg8>(cpu.esi + x86::reg32(7) /* 0x7 */);
    // 0043456a  f6c740                 +test bh, 0x40
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.bh & 64 /*0x40*/));
    // 0043456d  0f841a020000           -je 0x43478d
    if (cpu.flags.zf)
    {
        goto L_0x0043478d;
    }
    // 00434573  88f9                   -mov cl, bh
    cpu.cl = cpu.bh;
    // 00434575  80e1bf                 -and cl, 0xbf
    cpu.cl &= x86::reg8(x86::sreg8(191 /*0xbf*/));
    // 00434578  884e07                 -mov byte ptr [esi + 7], cl
    app->getMemory<x86::reg8>(cpu.esi + x86::reg32(7) /* 0x7 */) = cpu.cl;
    // 0043457b  833d584e550001         +cmp dword ptr [0x554e58], 1
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5590616) /* 0x554e58 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1 /*0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00434582  7414                   -je 0x434598
    if (cpu.flags.zf)
    {
        goto L_0x00434598;
    }
    // 00434584  bb01000000             -mov ebx, 1
    cpu.ebx = 1 /*0x1*/;
    // 00434589  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 0043458a  6a68                   -push 0x68
    app->getMemory<x86::reg32>(cpu.esp-4) = 104 /*0x68*/;
    cpu.esp -= 4;
    // 0043458c  891d584e5500           -mov dword ptr [0x554e58], ebx
    app->getMemory<x86::reg32>(x86::reg32(5590616) /* 0x554e58 */) = cpu.ebx;
    // 00434592  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00434598:
    // 00434598  8b5608                 -mov edx, dword ptr [esi + 8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(8) /* 0x8 */);
    // 0043459b  8b4674                 -mov eax, dword ptr [esi + 0x74]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(116) /* 0x74 */);
    // 0043459e  894210                 -mov dword ptr [edx + 0x10], eax
    app->getMemory<x86::reg32>(cpu.edx + x86::reg32(16) /* 0x10 */) = cpu.eax;
    // 004345a1  8b560c                 -mov edx, dword ptr [esi + 0xc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 004345a4  8b4678                 -mov eax, dword ptr [esi + 0x78]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(120) /* 0x78 */);
    // 004345a7  894210                 -mov dword ptr [edx + 0x10], eax
    app->getMemory<x86::reg32>(cpu.edx + x86::reg32(16) /* 0x10 */) = cpu.eax;
    // 004345aa  8b5610                 -mov edx, dword ptr [esi + 0x10]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(16) /* 0x10 */);
    // 004345ad  8b467c                 -mov eax, dword ptr [esi + 0x7c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(124) /* 0x7c */);
    // 004345b0  894210                 -mov dword ptr [edx + 0x10], eax
    app->getMemory<x86::reg32>(cpu.edx + x86::reg32(16) /* 0x10 */) = cpu.eax;
    // 004345b3  8b7e50                 -mov edi, dword ptr [esi + 0x50]
    cpu.edi = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(80) /* 0x50 */);
    // 004345b6  85ff                   +test edi, edi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edi & cpu.edi));
    // 004345b8  0f8479000000           -je 0x434637
    if (cpu.flags.zf)
    {
        goto L_0x00434637;
    }
    // 004345be  8b4608                 -mov eax, dword ptr [esi + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(8) /* 0x8 */);
    // 004345c1  8b5654                 -mov edx, dword ptr [esi + 0x54]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(84) /* 0x54 */);
    // 004345c4  895018                 -mov dword ptr [eax + 0x18], edx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */) = cpu.edx;
    // 004345c7  8b4608                 -mov eax, dword ptr [esi + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(8) /* 0x8 */);
    // 004345ca  8b5658                 -mov edx, dword ptr [esi + 0x58]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(88) /* 0x58 */);
    // 004345cd  89501c                 -mov dword ptr [eax + 0x1c], edx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(28) /* 0x1c */) = cpu.edx;
    // 004345d0  8b460c                 -mov eax, dword ptr [esi + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 004345d3  8b565c                 -mov edx, dword ptr [esi + 0x5c]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(92) /* 0x5c */);
    // 004345d6  895018                 -mov dword ptr [eax + 0x18], edx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */) = cpu.edx;
    // 004345d9  8b460c                 -mov eax, dword ptr [esi + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 004345dc  8b5660                 -mov edx, dword ptr [esi + 0x60]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(96) /* 0x60 */);
    // 004345df  89501c                 -mov dword ptr [eax + 0x1c], edx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(28) /* 0x1c */) = cpu.edx;
    // 004345e2  8b4610                 -mov eax, dword ptr [esi + 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(16) /* 0x10 */);
    // 004345e5  8b5664                 -mov edx, dword ptr [esi + 0x64]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(100) /* 0x64 */);
    // 004345e8  895018                 -mov dword ptr [eax + 0x18], edx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */) = cpu.edx;
    // 004345eb  8b4610                 -mov eax, dword ptr [esi + 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(16) /* 0x10 */);
    // 004345ee  8b5668                 -mov edx, dword ptr [esi + 0x68]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(104) /* 0x68 */);
    // 004345f1  89501c                 -mov dword ptr [eax + 0x1c], edx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(28) /* 0x1c */) = cpu.edx;
    // 004345f4  a1544e5500             -mov eax, dword ptr [0x554e54]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5590612) /* 0x554e54 */);
    // 004345f9  8b5650                 -mov edx, dword ptr [esi + 0x50]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(80) /* 0x50 */);
    // 004345fc  39d0                   +cmp eax, edx
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.edx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004345fe  744f                   -je 0x43464f
    if (cpu.flags.zf)
    {
        goto L_0x0043464f;
    }
    // 00434600  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00434601  6a01                   -push 1
    app->getMemory<x86::reg32>(cpu.esp-4) = 1 /*0x1*/;
    cpu.esp -= 4;
    // 00434603  8915544e5500           -mov dword ptr [0x554e54], edx
    app->getMemory<x86::reg32>(x86::reg32(5590612) /* 0x554e54 */) = cpu.edx;
    // 00434609  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0043460f  eb3e                   -jmp 0x43464f
    goto L_0x0043464f;
L_0x00434611:
    // 00434611  8b5e10                 -mov ebx, dword ptr [esi + 0x10]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(16) /* 0x10 */);
    // 00434614  8b560c                 -mov edx, dword ptr [esi + 0xc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 00434617  8b4608                 -mov eax, dword ptr [esi + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(8) /* 0x8 */);
    // 0043461a  e891cb0800             -call 0x4c11b0
    cpu.esp -= 4;
    sub_4c11b0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x0043461f:
    // 0043461f  8b36                   -mov esi, dword ptr [esi]
    cpu.esi = app->getMemory<x86::reg32>(cpu.esi);
    // 00434621  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 00434623  0f843cffffff           -je 0x434565
    if (cpu.flags.zf)
    {
        goto L_0x00434565;
    }
    // 00434629  668b4604               -mov ax, word ptr [esi + 4]
    cpu.ax = app->getMemory<x86::reg16>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 0043462d  e929ffffff             -jmp 0x43455b
    goto L_0x0043455b;
    // 00434632  e92effffff             -jmp 0x434565
    goto L_0x00434565;
L_0x00434637:
    // 00434637  833d544e550000         +cmp dword ptr [0x554e54], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5590612) /* 0x554e54 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0043463e  740f                   -je 0x43464f
    if (cpu.flags.zf)
    {
        goto L_0x0043464f;
    }
    // 00434640  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00434641  6a01                   -push 1
    app->getMemory<x86::reg32>(cpu.esp-4) = 1 /*0x1*/;
    cpu.esp -= 4;
    // 00434643  893d544e5500           -mov dword ptr [0x554e54], edi
    app->getMemory<x86::reg32>(x86::reg32(5590612) /* 0x554e54 */) = cpu.edi;
    // 00434649  ff156cf99e00           -call dword ptr [0x9ef96c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418540) /* 0x9ef96c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x0043464f:
    // 0043464f  8b4608                 -mov eax, dword ptr [esi + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(8) /* 0x8 */);
    // 00434652  83781400               +cmp dword ptr [eax + 0x14], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00434656  0f8523010000           -jne 0x43477f
    if (!cpu.flags.zf)
    {
        goto L_0x0043477f;
    }
    // 0043465c  8b460c                 -mov eax, dword ptr [esi + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 0043465f  83781400               +cmp dword ptr [eax + 0x14], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00434663  0f8516010000           -jne 0x43477f
    if (!cpu.flags.zf)
    {
        goto L_0x0043477f;
    }
    // 00434669  8b4610                 -mov eax, dword ptr [esi + 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(16) /* 0x10 */);
    // 0043466c  83781400               +cmp dword ptr [eax + 0x14], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00434670  0f8509010000           -jne 0x43477f
    if (!cpu.flags.zf)
    {
        goto L_0x0043477f;
    }
    // 00434676  8b4608                 -mov eax, dword ptr [esi + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(8) /* 0x8 */);
    // 00434679  f6400f80               +test byte ptr [eax + 0xf], 0x80
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(cpu.eax + x86::reg32(15) /* 0xf */) & 128 /*0x80*/));
    // 0043467d  7509                   -jne 0x434688
    if (!cpu.flags.zf)
    {
        goto L_0x00434688;
    }
    // 0043467f  81780c0000803f         +cmp dword ptr [eax + 0xc], 0x3f800000
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1065353216 /*0x3f800000*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00434686  7e07                   -jle 0x43468f
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x0043468f;
    }
L_0x00434688:
    // 00434688  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
    // 0043468a  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 0043468d  eb08                   -jmp 0x434697
    goto L_0x00434697;
L_0x0043468f:
    // 0043468f  d9e8                   -fld1 
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu19 = 1.0;
    // 00434691  d8600c                 -fsub dword ptr [eax + 0xc]
    x86::Float fpu20 = cpu.fpu.sub(fpu19, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(12) /* 0xc */)));
    // 00434694  d95dfc                 -fstp dword ptr [ebp - 4]
    app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = float(fpu20);
    }
L_0x00434697:
    // 00434697  8b4608                 -mov eax, dword ptr [esi + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(8) /* 0x8 */);
    // 0043469a  8b55fc                 -mov edx, dword ptr [ebp - 4]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 0043469d  895008                 -mov dword ptr [eax + 8], edx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */) = cpu.edx;
    // 004346a0  8b4608                 -mov eax, dword ptr [esi + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(8) /* 0x8 */);
    // 004346a3  d90594005600           -fld dword ptr [0x560094]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu21 = x86::Float(app->getMemory<float>(x86::reg32(5636244) /* 0x560094 */));
    // 004346a9  d84808                 -fmul dword ptr [eax + 8]
    x86::Float fpu22 = cpu.fpu.mul(fpu21, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */)));
    // 004346ac  d95808                 -fstp dword ptr [eax + 8]
    app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */) = float(fpu22);
    // 004346af  8b4608                 -mov eax, dword ptr [esi + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(8) /* 0x8 */);
    // 004346b2  d90598005600           -fld dword ptr [0x560098]
    x86::Float fpu23 = x86::Float(app->getMemory<float>(x86::reg32(5636248) /* 0x560098 */));
    // 004346b8  d84008                 -fadd dword ptr [eax + 8]
    x86::Float fpu24 = cpu.fpu.add(fpu23, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */)));
    // 004346bb  d95808                 -fstp dword ptr [eax + 8]
    app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */) = float(fpu24);
    // 004346be  8b460c                 -mov eax, dword ptr [esi + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 004346c1  f6400f80               +test byte ptr [eax + 0xf], 0x80
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(cpu.eax + x86::reg32(15) /* 0xf */) & 128 /*0x80*/));
    }
    // 004346c5  7509                   -jne 0x4346d0
    if (!cpu.flags.zf)
    {
        goto L_0x004346d0;
    }
    // 004346c7  81780c0000803f         +cmp dword ptr [eax + 0xc], 0x3f800000
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1065353216 /*0x3f800000*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004346ce  7e07                   -jle 0x4346d7
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004346d7;
    }
L_0x004346d0:
    // 004346d0  31c9                   +xor ecx, ecx
    cpu.clear_co();
    cpu.set_szp((cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx))));
    // 004346d2  894df0                 -mov dword ptr [ebp - 0x10], ecx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = cpu.ecx;
    // 004346d5  eb08                   -jmp 0x4346df
    goto L_0x004346df;
L_0x004346d7:
    // 004346d7  d9e8                   -fld1 
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu25 = 1.0;
    // 004346d9  d8600c                 -fsub dword ptr [eax + 0xc]
    x86::Float fpu26 = cpu.fpu.sub(fpu25, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(12) /* 0xc */)));
    // 004346dc  d95df0                 -fstp dword ptr [ebp - 0x10]
    app->getMemory<float>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = float(fpu26);
    }
L_0x004346df:
    // 004346df  8b460c                 -mov eax, dword ptr [esi + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 004346e2  8b55f0                 -mov edx, dword ptr [ebp - 0x10]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 004346e5  895008                 -mov dword ptr [eax + 8], edx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */) = cpu.edx;
    // 004346e8  8b460c                 -mov eax, dword ptr [esi + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 004346eb  d90594005600           -fld dword ptr [0x560094]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu27 = x86::Float(app->getMemory<float>(x86::reg32(5636244) /* 0x560094 */));
    // 004346f1  d84808                 -fmul dword ptr [eax + 8]
    x86::Float fpu28 = cpu.fpu.mul(fpu27, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */)));
    // 004346f4  d95808                 -fstp dword ptr [eax + 8]
    app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */) = float(fpu28);
    // 004346f7  8b460c                 -mov eax, dword ptr [esi + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 004346fa  d90598005600           -fld dword ptr [0x560098]
    x86::Float fpu29 = x86::Float(app->getMemory<float>(x86::reg32(5636248) /* 0x560098 */));
    // 00434700  d84008                 -fadd dword ptr [eax + 8]
    x86::Float fpu30 = cpu.fpu.add(fpu29, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */)));
    // 00434703  d95808                 -fstp dword ptr [eax + 8]
    app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */) = float(fpu30);
    // 00434706  8b4610                 -mov eax, dword ptr [esi + 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(16) /* 0x10 */);
    // 00434709  f6400f80               +test byte ptr [eax + 0xf], 0x80
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(cpu.eax + x86::reg32(15) /* 0xf */) & 128 /*0x80*/));
    }
    // 0043470d  7509                   -jne 0x434718
    if (!cpu.flags.zf)
    {
        goto L_0x00434718;
    }
    // 0043470f  81780c0000803f         +cmp dword ptr [eax + 0xc], 0x3f800000
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1065353216 /*0x3f800000*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00434716  7e07                   -jle 0x43471f
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x0043471f;
    }
L_0x00434718:
    // 00434718  31ff                   +xor edi, edi
    cpu.clear_co();
    cpu.set_szp((cpu.edi ^= x86::reg32(x86::sreg32(cpu.edi))));
    // 0043471a  897de8                 -mov dword ptr [ebp - 0x18], edi
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-24) /* -0x18 */) = cpu.edi;
    // 0043471d  eb08                   -jmp 0x434727
    goto L_0x00434727;
L_0x0043471f:
    // 0043471f  d9e8                   -fld1 
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu31 = 1.0;
    // 00434721  d8600c                 -fsub dword ptr [eax + 0xc]
    x86::Float fpu32 = cpu.fpu.sub(fpu31, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(12) /* 0xc */)));
    // 00434724  d95de8                 -fstp dword ptr [ebp - 0x18]
    app->getMemory<float>(cpu.ebp + x86::reg32(-24) /* -0x18 */) = float(fpu32);
    }
L_0x00434727:
    // 00434727  8b4610                 -mov eax, dword ptr [esi + 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(16) /* 0x10 */);
    // 0043472a  8b55e8                 -mov edx, dword ptr [ebp - 0x18]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-24) /* -0x18 */);
    // 0043472d  895008                 -mov dword ptr [eax + 8], edx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */) = cpu.edx;
    // 00434730  8b4610                 -mov eax, dword ptr [esi + 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(16) /* 0x10 */);
    // 00434733  d90594005600           -fld dword ptr [0x560094]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu33 = x86::Float(app->getMemory<float>(x86::reg32(5636244) /* 0x560094 */));
    // 00434739  d84808                 -fmul dword ptr [eax + 8]
    x86::Float fpu34 = cpu.fpu.mul(fpu33, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */)));
    // 0043473c  d95808                 -fstp dword ptr [eax + 8]
    app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */) = float(fpu34);
    // 0043473f  8b4610                 -mov eax, dword ptr [esi + 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(16) /* 0x10 */);
    // 00434742  d90598005600           -fld dword ptr [0x560098]
    x86::Float fpu35 = x86::Float(app->getMemory<float>(x86::reg32(5636248) /* 0x560098 */));
    // 00434748  d84008                 -fadd dword ptr [eax + 8]
    x86::Float fpu36 = cpu.fpu.add(fpu35, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */)));
    // 0043474b  d95808                 -fstp dword ptr [eax + 8]
    app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */) = float(fpu36);
    // 0043474e  8b4610                 -mov eax, dword ptr [esi + 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(16) /* 0x10 */);
    // 00434751  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00434752  8b560c                 -mov edx, dword ptr [esi + 0xc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 00434755  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00434756  8b4e08                 -mov ecx, dword ptr [esi + 8]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(8) /* 0x8 */);
    // 00434759  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    }
    // 0043475a  ff1574f99e00           -call dword ptr [0x9ef974]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(10418548) /* 0x9ef974 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00434760  8b36                   -mov esi, dword ptr [esi]
    cpu.esi = app->getMemory<x86::reg32>(cpu.esi);
    // 00434762  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 00434764  740e                   -je 0x434774
    if (cpu.flags.zf)
    {
        goto L_0x00434774;
    }
    // 00434766  668b4604               -mov ax, word ptr [esi + 4]
    cpu.ax = app->getMemory<x86::reg16>(cpu.esi + x86::reg32(4) /* 0x4 */);
L_0x0043476a:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 0043476a  663d0300               +cmp ax, 3
    {
        x86::reg16 tmp1 = cpu.ax;
        x86::reg16 tmp2 = x86::reg16(x86::sreg16(3 /*0x3*/));
        x86::reg16 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 15);
        cpu.flags.of ^= 1 & (result >> 15);
        cpu.flags.of &= (1 & (tmp1 >> 15)) != (1 & (tmp2 >> 15));
        cpu.set_szp(result);
    }
    // 0043476e  0f84f3fdffff           -je 0x434567
    if (cpu.flags.zf)
    {
        goto L_0x00434567;
    }
L_0x00434774:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00434774  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 00434776  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00434778  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00434779  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043477a  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043477b  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043477c  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043477d  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043477e  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x0043477f:
    // 0043477f  8b5e10                 -mov ebx, dword ptr [esi + 0x10]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(16) /* 0x10 */);
    // 00434782  8b560c                 -mov edx, dword ptr [esi + 0xc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 00434785  8b4608                 -mov eax, dword ptr [esi + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(8) /* 0x8 */);
    // 00434788  e823ca0800             -call 0x4c11b0
    cpu.esp -= 4;
    sub_4c11b0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x0043478d:
    // 0043478d  8b36                   -mov esi, dword ptr [esi]
    cpu.esi = app->getMemory<x86::reg32>(cpu.esi);
    // 0043478f  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 00434791  74e1                   -je 0x434774
    if (cpu.flags.zf)
    {
        goto L_0x00434774;
    }
    // 00434793  668b4604               -mov ax, word ptr [esi + 4]
    cpu.ax = app->getMemory<x86::reg16>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 00434797  ebd1                   -jmp 0x43476a
    goto L_0x0043476a;
}

/* align: skip  */
void Application::sub_434799(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00434799  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 0043479b  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 0043479d  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043479e  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043479f  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004347a0  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004347a1  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004347a2  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004347a3  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 */
void Application::sub_4347b0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004347b0  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004347b1  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004347b3  833d603a7a0000         +cmp dword ptr [0x7a3a60], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(8010336) /* 0x7a3a60 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004347ba  7407                   -je 0x4347c3
    if (cpu.flags.zf)
    {
        goto L_0x004347c3;
    }
    // 004347bc  e8bffbffff             -call 0x434380
    cpu.esp -= 4;
    sub_434380(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004347c1  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004347c2  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004347c3:
    // 004347c3  e868f6ffff             -call 0x433e30
    cpu.esp -= 4;
    sub_433e30(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004347c8  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004347c9  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_4347d0: native, nfs3hp::graphics::drawLineRecord */

/* align: skip 0x8d 0x40 0x00 0x8b 0xc9 */
void Application::sub_434850(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00434850  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00434851  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00434852  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00434853  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00434855  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00434857  8b500c                 -mov edx, dword ptr [eax + 0xc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
    // 0043485a  8b4008                 -mov eax, dword ptr [eax + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 0043485d  e89ed0ffff             -call 0x431900
    cpu.esp -= 4;
    nfs3hp::graphics::setRenderState(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00434862  8b01                   -mov eax, dword ptr [ecx]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx);
    // 00434864  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00434865  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00434866  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00434867  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8b 0xd2 */
void Application::sub_434870(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (polygonDrawers(app, cpu.sync())) /* port: native (tools/apply_native_render.py) */
    {
        cpu.reload();
        return;
    }
    // 00434870  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00434871  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00434872  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00434873  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00434874  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00434875  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00434876  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00434878  ba403d4300             -mov edx, 0x433d40
    cpu.edx = 4406592 /*0x433d40*/;
    // 0043487d  8a25583a7a00           -mov ah, byte ptr [0x7a3a58]
    cpu.ah = app->getMemory<x86::reg8>(x86::reg32(8010328) /* 0x7a3a58 */);
    // 00434883  891588075f00           -mov dword ptr [0x5f0788], edx
    app->getMemory<x86::reg32>(x86::reg32(6227848) /* 0x5f0788 */) = cpu.edx;
    // 00434889  f6c440                 +test ah, 0x40
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.ah & 64 /*0x40*/));
    // 0043488c  7438                   -je 0x4348c6
    if (cpu.flags.zf)
    {
        goto L_0x004348c6;
    }
    // 0043488e  bbe0364300             -mov ebx, 0x4336e0
    cpu.ebx = 4404960 /*0x4336e0*/;
    // 00434893  bed0394300             -mov esi, 0x4339d0
    cpu.esi = 4405712 /*0x4339d0*/;
    // 00434898  bf50484300             -mov edi, 0x434850
    cpu.edi = 4409424 /*0x434850*/;
    // 0043489d  b8b0474300             -mov eax, 0x4347b0
    cpu.eax = 4409264 /*0x4347b0*/;
    // 004348a2  b940384300             -mov ecx, 0x433840
    cpu.ecx = 4405312 /*0x433840*/;
    // 004348a7  891d84075f00           -mov dword ptr [0x5f0784], ebx
    app->getMemory<x86::reg32>(x86::reg32(6227844) /* 0x5f0784 */) = cpu.ebx;
    // 004348ad  893590075f00           -mov dword ptr [0x5f0790], esi
    app->getMemory<x86::reg32>(x86::reg32(6227856) /* 0x5f0790 */) = cpu.esi;
    // 004348b3  893d94075f00           -mov dword ptr [0x5f0794], edi
    app->getMemory<x86::reg32>(x86::reg32(6227860) /* 0x5f0794 */) = cpu.edi;
    // 004348b9  a38c075f00             -mov dword ptr [0x5f078c], eax
    app->getMemory<x86::reg32>(x86::reg32(6227852) /* 0x5f078c */) = cpu.eax;
    // 004348be  890d80075f00           -mov dword ptr [0x5f0780], ecx
    app->getMemory<x86::reg32>(x86::reg32(6227840) /* 0x5f0780 */) = cpu.ecx;
    // 004348c4  eb79                   -jmp 0x43493f
    goto L_0x0043493f;
L_0x004348c6:
    // 004348c6  f6c406                 +test ah, 6
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.ah & 6 /*0x6*/));
    // 004348c9  743e                   -je 0x434909
    if (cpu.flags.zf)
    {
        goto L_0x00434909;
    }
    // 004348cb  b930354300             -mov ecx, 0x433530
    cpu.ecx = 4404528 /*0x433530*/;
    // 004348d0  bb60364300             -mov ebx, 0x433660
    cpu.ebx = 4404832 /*0x433660*/;
    // 004348d5  be50484300             -mov esi, 0x434850
    cpu.esi = 4409424 /*0x434850*/;
    // 004348da  bf20414300             -mov edi, 0x434120
    cpu.edi = 4407584 /*0x434120*/;
    // 004348df  bab0324300             -mov edx, 0x4332b0
    cpu.edx = 4403888 /*0x4332b0*/;
    // 004348e4  890d84075f00           -mov dword ptr [0x5f0784], ecx
    app->getMemory<x86::reg32>(x86::reg32(6227844) /* 0x5f0784 */) = cpu.ecx;
    // 004348ea  891d90075f00           -mov dword ptr [0x5f0790], ebx
    app->getMemory<x86::reg32>(x86::reg32(6227856) /* 0x5f0790 */) = cpu.ebx;
    // 004348f0  893594075f00           -mov dword ptr [0x5f0794], esi
    app->getMemory<x86::reg32>(x86::reg32(6227860) /* 0x5f0794 */) = cpu.esi;
    // 004348f6  893d8c075f00           -mov dword ptr [0x5f078c], edi
    app->getMemory<x86::reg32>(x86::reg32(6227852) /* 0x5f078c */) = cpu.edi;
    // 004348fc  891580075f00           -mov dword ptr [0x5f0780], edx
    app->getMemory<x86::reg32>(x86::reg32(6227840) /* 0x5f0780 */) = cpu.edx;
    // 00434902  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00434903  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00434904  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00434905  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00434906  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00434907  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00434908  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x00434909:
    // 00434909  ba503a4300             -mov edx, 0x433a50
    cpu.edx = 4405840 /*0x433a50*/;
    // 0043490e  b9d0474300             -mov ecx, 0x4347d0
    cpu.ecx = 4409296 /*0x4347d0*/;
    // 00434913  bb50484300             -mov ebx, 0x434850
    cpu.ebx = 4409424 /*0x434850*/;
    // 00434918  beb0474300             -mov esi, 0x4347b0
    cpu.esi = 4409264 /*0x4347b0*/;
    // 0043491d  b8b03b4300             -mov eax, 0x433bb0
    cpu.eax = 4406192 /*0x433bb0*/;
    // 00434922  891584075f00           -mov dword ptr [0x5f0784], edx
    app->getMemory<x86::reg32>(x86::reg32(6227844) /* 0x5f0784 */) = cpu.edx;
    // 00434928  890d90075f00           -mov dword ptr [0x5f0790], ecx
    app->getMemory<x86::reg32>(x86::reg32(6227856) /* 0x5f0790 */) = cpu.ecx;
    // 0043492e  891d94075f00           -mov dword ptr [0x5f0794], ebx
    app->getMemory<x86::reg32>(x86::reg32(6227860) /* 0x5f0794 */) = cpu.ebx;
    // 00434934  89358c075f00           -mov dword ptr [0x5f078c], esi
    app->getMemory<x86::reg32>(x86::reg32(6227852) /* 0x5f078c */) = cpu.esi;
    // 0043493a  a380075f00             -mov dword ptr [0x5f0780], eax
    app->getMemory<x86::reg32>(x86::reg32(6227840) /* 0x5f0780 */) = cpu.eax;
L_0x0043493f:
    // 0043493f  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00434940  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00434941  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00434942  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00434943  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00434944  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00434945  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x54 0x22 0x00 */
void Application::sub_434950(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00434950  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00434951  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00434952  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00434953  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00434955  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00434957  ba01000000             -mov edx, 1
    cpu.edx = 1 /*0x1*/;
    // 0043495c  b80d000000             -mov eax, 0xd
    cpu.eax = 13 /*0xd*/;
    // 00434961  e89acfffff             -call 0x431900
    cpu.esp -= 4;
    nfs3hp::graphics::setRenderState(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00434966:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00434966  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    // 00434968  7419                   -je 0x434983
    if (cpu.flags.zf)
    {
        goto L_0x00434983;
    }
    // 0043496a  8b4102                 -mov eax, dword ptr [ecx + 2]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(2) /* 0x2 */);
    // 0043496d  c1f810                 +sar eax, 0x10
    {
        x86::reg8 tmp = 16 /*0x10*/ % 32;
        x86::reg32& op = cpu.eax;
        if (tmp)
        {
            cpu.flags.cf = 1 & (x86::sreg32(op) >> (tmp - 1));
            if (tmp == 1) cpu.flags.of = 0;
            cpu.set_szp((op = x86::reg32(x86::sreg32(op) >> tmp)));
        }
    }
    // 00434970  8d148500000000         -lea edx, [eax*4]
    cpu.edx = x86::reg32(cpu.eax * 4);
    // 00434977  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00434979  ff9280075f00           -call dword ptr [edx + 0x5f0780]
    cpu.ip = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(6227840) /* 0x5f0780 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0043497f  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00434981  ebe3                   -jmp 0x434966
    goto L_0x00434966;
L_0x00434983:
    // 00434983  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00434984  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00434985  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00434986  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 */
void Application::sub_434990(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00434990  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00434991  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00434993  b8c0da7c00             -mov eax, 0x7cdac0
    cpu.eax = 8182464 /*0x7cdac0*/;
    // 00434998  e8d3a30800             -call 0x4bed70
    cpu.esp -= 4;
    sub_4bed70(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0043499d  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043499e  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x90 */
void Application::sub_4349a0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004349a0  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004349a1  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004349a2  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004349a4  8b10                   -mov edx, dword ptr [eax]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax);
    // 004349a6  83fa01                 +cmp edx, 1
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1 /*0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004349a9  7504                   -jne 0x4349af
    if (!cpu.flags.zf)
    {
        goto L_0x004349af;
    }
    // 004349ab  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004349ad  eb02                   -jmp 0x4349b1
    goto L_0x004349b1;
L_0x004349af:
    // 004349af  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
L_0x004349b1:
    // 004349b1  8b15c4d46f00           -mov edx, dword ptr [0x6fd4c4]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(7328964) /* 0x6fd4c4 */);
    // 004349b7  31d0                   -xor eax, edx
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.edx));
    // 004349b9  a34c4e5500             -mov dword ptr [0x554e4c], eax
    app->getMemory<x86::reg32>(x86::reg32(5590604) /* 0x554e4c */) = cpu.eax;
    // 004349be  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004349bf  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004349c0  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x8d 0x40 0x00 */
void Application::sub_4349d0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004349d0  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004349d1  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004349d2  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004349d4  8b10                   -mov edx, dword ptr [eax]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax);
    // 004349d6  83fa01                 +cmp edx, 1
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1 /*0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004349d9  7504                   -jne 0x4349df
    if (!cpu.flags.zf)
    {
        goto L_0x004349df;
    }
    // 004349db  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004349dd  eb02                   -jmp 0x4349e1
    goto L_0x004349e1;
L_0x004349df:
    // 004349df  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
L_0x004349e1:
    // 004349e1  8b15c4d46f00           -mov edx, dword ptr [0x6fd4c4]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(7328964) /* 0x6fd4c4 */);
    // 004349e7  31d0                   -xor eax, edx
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.edx));
    // 004349e9  a34c4e5500             -mov dword ptr [0x554e4c], eax
    app->getMemory<x86::reg32>(x86::reg32(5590604) /* 0x554e4c */) = cpu.eax;
    // 004349ee  8b450c                 -mov eax, dword ptr [ebp + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(12) /* 0xc */);
    // 004349f1  e85affffff             -call 0x434950
    cpu.esp -= 4;
    sub_434950(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004349f6  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004349f7  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004349f8  c20800                 -ret 8
    cpu.esp += 4+8 /*0x8*/;
    return;
}

/* sub_434a00: native, nfs3hp::graphics::endFrame */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x90 */
void Application::sub_434a70(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00434a70  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00434a71  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00434a73  ff05a81f5f00           -inc dword ptr [0x5f1fa8]
    (app->getMemory<x86::reg32>(x86::reg32(6234024) /* 0x5f1fa8 */))++;
    // 00434a79  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00434a7a  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x40 0x00 0x8b 0xc9 */
void Application::sub_434a80(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00434a80  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00434a81  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00434a83  a128bc6f00             -mov eax, dword ptr [0x6fbc28]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(7322664) /* 0x6fbc28 */);
    // 00434a88  e8838bfeff             -call 0x41d610
    cpu.esp -= 4;
    sub_41d610(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00434a8d  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00434a8e  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x90 */
void Application::sub_434a90(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00434a90  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00434a91  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00434a92  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00434a94  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00434a96  a0faf96f00             -mov al, byte ptr [0x6ff9fa]
    cpu.al = app->getMemory<x86::reg8>(x86::reg32(7338490) /* 0x6ff9fa */);
    // 00434a9b  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 00434a9d  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00434a9f  c1e210                 -shl edx, 0x10
    cpu.edx <<= 16 /*0x10*/ % 32;
    // 00434aa2  a0f9f96f00             -mov al, byte ptr [0x6ff9f9]
    cpu.al = app->getMemory<x86::reg8>(x86::reg32(7338489) /* 0x6ff9f9 */);
    // 00434aa7  81ca000000ff           -or edx, 0xff000000
    cpu.edx |= x86::reg32(x86::sreg32(4278190080 /*0xff000000*/));
    // 00434aad  c1e008                 -shl eax, 8
    cpu.eax <<= 8 /*0x8*/ % 32;
    // 00434ab0  09c2                   -or edx, eax
    cpu.edx |= x86::reg32(x86::sreg32(cpu.eax));
    // 00434ab2  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00434ab4  a0f8f96f00             -mov al, byte ptr [0x6ff9f8]
    cpu.al = app->getMemory<x86::reg8>(x86::reg32(7338488) /* 0x6ff9f8 */);
    // 00434ab9  09c2                   -or edx, eax
    cpu.edx |= x86::reg32(x86::sreg32(cpu.eax));
    // 00434abb  b803000000             -mov eax, 3
    cpu.eax = 3 /*0x3*/;
    // 00434ac0  e83bceffff             -call 0x431900
    cpu.esp -= 4;
    nfs3hp::graphics::setRenderState(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00434ac5  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00434ac6  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00434ac7  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8b 0xd2 */
void Application::sub_434ad0(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00434ad0  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00434ad1  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00434ad3  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00434ad4  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 0x8b 0xdb */
void Application::sub_434ae0(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00434ae0  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00434ae1  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00434ae3  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00434ae4  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 0x8b 0xdb */
void Application::sub_434af0(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00434af0  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00434af1  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00434af3  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00434af4  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 0x8b 0xdb */
void Application::sub_434b00(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00434b00  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00434b01  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00434b03  e8b8680b00             -call 0x4eb3c0
    cpu.esp -= 4;
    nfs3hp::graphics::makeReciprocals(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00434b08  e863fdffff             -call 0x434870
    cpu.esp -= 4;
    sub_434870(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00434b0d  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00434b0e  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x90 */
void Application::sub_434b10(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00434b10  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00434b11  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00434b13  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00434b14  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_434b20: native, nfs3hp::graphics::syncWindow */

/* sub_434b40: native, nfs3hp::graphics::flushAndFlip */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 0x8b 0xdb */
void Application::sub_434b60(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00434b60  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00434b61  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00434b62  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00434b63  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00434b64  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00434b65  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00434b66  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00434b68  81ec9c000000           -sub esp, 0x9c
    (cpu.esp) -= x86::reg32(x86::sreg32(156 /*0x9c*/));
    // 00434b6e  81ed82000000           -sub ebp, 0x82
    (cpu.ebp) -= x86::reg32(x86::sreg32(130 /*0x82*/));
    // 00434b74  8d4d7a                 -lea ecx, [ebp + 0x7a]
    cpu.ecx = x86::reg32(cpu.ebp + x86::reg32(122) /* 0x7a */);
    // 00434b77  8d5d76                 -lea ebx, [ebp + 0x76]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(118) /* 0x76 */);
    // 00434b7a  8d5572                 -lea edx, [ebp + 0x72]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(114) /* 0x72 */);
    // 00434b7d  8d456e                 -lea eax, [ebp + 0x6e]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(110) /* 0x6e */);
    // 00434b80  e88b070000             -call 0x435310
    cpu.esp -= 4;
    nfs3hp::controls::readMouse(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00434b85  8d556a                 -lea edx, [ebp + 0x6a]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(106) /* 0x6a */);
    // 00434b88  8d4566                 -lea eax, [ebp + 0x66]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(102) /* 0x66 */);
    // 00434b8b  e8805f0a00             -call 0x4dab10
    cpu.esp -= 4;
    sub_4dab10(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00434b90  8b4572                 -mov eax, dword ptr [ebp + 0x72]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(114) /* 0x72 */);
    // 00434b93  2b4566                 -sub eax, dword ptr [ebp + 0x66]
    (cpu.eax) -= x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(102) /* 0x66 */)));
    // 00434b96  8b4d6a                 -mov ecx, dword ptr [ebp + 0x6a]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(106) /* 0x6a */);
    // 00434b99  89457e                 -mov dword ptr [ebp + 0x7e], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */) = cpu.eax;
    // 00434b9c  ba00ff7f3f             -mov edx, 0x3f7fff00
    cpu.edx = 1065352960 /*0x3f7fff00*/;
    // 00434ba1  db457e                 -fild dword ptr [ebp + 0x7e]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */)));
    // 00434ba4  d95d46                 -fstp dword ptr [ebp + 0x46]
    app->getMemory<float>(cpu.ebp + x86::reg32(70) /* 0x46 */) = float(fpu1);
    // 00434ba7  895552                 -mov dword ptr [ebp + 0x52], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(82) /* 0x52 */) = cpu.edx;
    // 00434baa  895532                 -mov dword ptr [ebp + 0x32], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(50) /* 0x32 */) = cpu.edx;
    // 00434bad  895512                 -mov dword ptr [ebp + 0x12], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(18) /* 0x12 */) = cpu.edx;
    // 00434bb0  8b4546                 -mov eax, dword ptr [ebp + 0x46]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(70) /* 0x46 */);
    // 00434bb3  8955f2                 -mov dword ptr [ebp - 0xe], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-14) /* -0xe */) = cpu.edx;
    // 00434bb6  894526                 -mov dword ptr [ebp + 0x26], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(38) /* 0x26 */) = cpu.eax;
    // 00434bb9  894506                 -mov dword ptr [ebp + 6], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(6) /* 0x6 */) = cpu.eax;
    // 00434bbc  8945e6                 -mov dword ptr [ebp - 0x1a], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-26) /* -0x1a */) = cpu.eax;
    // 00434bbf  8b4576                 -mov eax, dword ptr [ebp + 0x76]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(118) /* 0x76 */);
    // 00434bc2  d94546                 -fld dword ptr [ebp + 0x46]
    x86::Float fpu2 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(70) /* 0x46 */));
    // 00434bc5  29c8                   -sub eax, ecx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.ecx));
    // 00434bc7  d9058c745300           -fld dword ptr [0x53748c]
    x86::Float fpu3 = x86::Float(app->getMemory<float>(x86::reg32(5469324) /* 0x53748c */));
    // 00434bcd  d9c9                   -fxch st(1)
    
    // 00434bcf  d8c1                   -fadd st(1)
    x86::Float fpu4 = cpu.fpu.add(fpu2, x86::Float(fpu3));
    // 00434bd1  89457e                 -mov dword ptr [ebp + 0x7e], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */) = cpu.eax;
    // 00434bd4  d95d06                 -fstp dword ptr [ebp + 6]
    app->getMemory<float>(cpu.ebp + x86::reg32(6) /* 0x6 */) = float(fpu4);
    // 00434bd7  db457e                 -fild dword ptr [ebp + 0x7e]
    x86::Float fpu5 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */)));
    // 00434bda  d95d4a                 -fstp dword ptr [ebp + 0x4a]
    app->getMemory<float>(cpu.ebp + x86::reg32(74) /* 0x4a */) = float(fpu5);
    // 00434bdd  8b454a                 -mov eax, dword ptr [ebp + 0x4a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(74) /* 0x4a */);
    // 00434be0  d9454a                 -fld dword ptr [ebp + 0x4a]
    x86::Float fpu6 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(74) /* 0x4a */));
    // 00434be3  89452a                 -mov dword ptr [ebp + 0x2a], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(42) /* 0x2a */) = cpu.eax;
    // 00434be6  89450a                 -mov dword ptr [ebp + 0xa], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(10) /* 0xa */) = cpu.eax;
    // 00434be9  8945ea                 -mov dword ptr [ebp - 0x16], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-22) /* -0x16 */) = cpu.eax;
    // 00434bec  dec1                   -faddp st(1)
    x86::Float fpu7 = cpu.fpu.add(fpu3, fpu6);
    // 00434bee  8b4506                 -mov eax, dword ptr [ebp + 6]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(6) /* 0x6 */);
    // 00434bf1  d95d2a                 -fstp dword ptr [ebp + 0x2a]
    app->getMemory<float>(cpu.ebp + x86::reg32(42) /* 0x2a */) = float(fpu7);
    // 00434bf4  894526                 -mov dword ptr [ebp + 0x26], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(38) /* 0x26 */) = cpu.eax;
    // 00434bf7  8b452a                 -mov eax, dword ptr [ebp + 0x2a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(42) /* 0x2a */);
    // 00434bfa  8b153c3d5600           -mov edx, dword ptr [0x563d3c]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5651772) /* 0x563d3c */);
    // 00434c00  89454a                 -mov dword ptr [ebp + 0x4a], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(74) /* 0x4a */) = cpu.eax;
    // 00434c03  8d049500000000         -lea eax, [edx*4]
    cpu.eax = x86::reg32(cpu.edx * 4);
    // 00434c0a  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 00434c0c  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 00434c0f  bfffffffff             -mov edi, 0xffffffff
    cpu.edi = 4294967295 /*0xffffffff*/;
    // 00434c14  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 00434c16  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
    // 00434c18  8d148500000000         -lea edx, [eax*4]
    cpu.edx = x86::reg32(cpu.eax * 4);
    // 00434c1f  8d75e6                 -lea esi, [ebp - 0x1a]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(-26) /* -0x1a */);
    // 00434c22  895d4e                 -mov dword ptr [ebp + 0x4e], ebx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(78) /* 0x4e */) = cpu.ebx;
    // 00434c25  8b82e0418b00           -mov eax, dword ptr [edx + 0x8b41e0]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(9126368) /* 0x8b41e0 */);
    // 00434c2b  895d2e                 -mov dword ptr [ebp + 0x2e], ebx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(46) /* 0x2e */) = cpu.ebx;
    // 00434c2e  8945fe                 -mov dword ptr [ebp - 2], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-2) /* -0x2 */) = cpu.eax;
    // 00434c31  8b82e4418b00           -mov eax, dword ptr [edx + 0x8b41e4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(9126372) /* 0x8b41e4 */);
    // 00434c37  895d0e                 -mov dword ptr [ebp + 0xe], ebx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(14) /* 0xe */) = cpu.ebx;
    // 00434c3a  894502                 -mov dword ptr [ebp + 2], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(2) /* 0x2 */) = cpu.eax;
    // 00434c3d  8b82e8418b00           -mov eax, dword ptr [edx + 0x8b41e8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(9126376) /* 0x8b41e8 */);
    // 00434c43  895dee                 -mov dword ptr [ebp - 0x12], ebx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-18) /* -0x12 */) = cpu.ebx;
    // 00434c46  89451e                 -mov dword ptr [ebp + 0x1e], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(30) /* 0x1e */) = cpu.eax;
    // 00434c49  8b82ec418b00           -mov eax, dword ptr [edx + 0x8b41ec]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(9126380) /* 0x8b41ec */);
    // 00434c4f  897d56                 -mov dword ptr [ebp + 0x56], edi
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(86) /* 0x56 */) = cpu.edi;
    // 00434c52  894522                 -mov dword ptr [ebp + 0x22], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(34) /* 0x22 */) = cpu.eax;
    // 00434c55  8b82f0418b00           -mov eax, dword ptr [edx + 0x8b41f0]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(9126384) /* 0x8b41f0 */);
    // 00434c5b  897d36                 -mov dword ptr [ebp + 0x36], edi
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(54) /* 0x36 */) = cpu.edi;
    // 00434c5e  89453e                 -mov dword ptr [ebp + 0x3e], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(62) /* 0x3e */) = cpu.eax;
    // 00434c61  8b82f4418b00           -mov eax, dword ptr [edx + 0x8b41f4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(9126388) /* 0x8b41f4 */);
    // 00434c67  897d16                 -mov dword ptr [ebp + 0x16], edi
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(22) /* 0x16 */) = cpu.edi;
    // 00434c6a  894542                 -mov dword ptr [ebp + 0x42], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(66) /* 0x42 */) = cpu.eax;
    // 00434c6d  8b82f8418b00           -mov eax, dword ptr [edx + 0x8b41f8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(9126392) /* 0x8b41f8 */);
    // 00434c73  897df6                 -mov dword ptr [ebp - 0xa], edi
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-10) /* -0xa */) = cpu.edi;
    // 00434c76  89455e                 -mov dword ptr [ebp + 0x5e], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(94) /* 0x5e */) = cpu.eax;
    // 00434c79  8b82fc418b00           -mov eax, dword ptr [edx + 0x8b41fc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(9126396) /* 0x8b41fc */);
    // 00434c7f  8d7dfa                 -lea edi, [ebp - 6]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(-6) /* -0x6 */);
    // 00434c82  894562                 -mov dword ptr [ebp + 0x62], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(98) /* 0x62 */) = cpu.eax;
    // 00434c85  8b460c                 -mov eax, dword ptr [esi + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 00434c88  8b0df8347d00           -mov ecx, dword ptr [0x7d34f8]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205560) /* 0x7d34f8 */);
    // 00434c8e  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    }
    // 00434c93  7558                   -jne 0x434ced
    if (!cpu.flags.zf)
    {
        goto L_0x00434ced;
    }
    // 00434c95  39c8                   +cmp eax, ecx
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ecx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00434c97  7d54                   -jge 0x434ced
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00434ced;
    }
    // 00434c99  8b4604                 -mov eax, dword ptr [esi + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 00434c9c  bb00000000             -mov ebx, 0
    cpu.ebx = 0 /*0x0*/;
    // 00434ca1  8b0d04357d00           -mov ecx, dword ptr [0x7d3504]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205572) /* 0x7d3504 */);
    // 00434ca7  8b1500357d00           -mov edx, dword ptr [0x7d3500]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205568) /* 0x7d3500 */);
    // 00434cad  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 00434cb2  750d                   -jne 0x434cc1
    if (!cpu.flags.zf)
    {
        goto L_0x00434cc1;
    }
    // 00434cb4  39c8                   +cmp eax, ecx
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ecx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00434cb6  7c09                   -jl 0x434cc1
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x00434cc1;
    }
    // 00434cb8  39d0                   +cmp eax, edx
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.edx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00434cba  7e09                   -jle 0x434cc5
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00434cc5;
    }
    // 00434cbc  83cb04                 +or ebx, 4
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(4 /*0x4*/))));
    // 00434cbf  eb04                   -jmp 0x434cc5
    goto L_0x00434cc5;
L_0x00434cc1:
    // 00434cc1  83cb08                 -or ebx, 8
    cpu.ebx |= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 00434cc4  90                     -nop 
    ;
L_0x00434cc5:
    // 00434cc5  8b06                   -mov eax, dword ptr [esi]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi);
    // 00434cc7  90                     -nop 
    ;
    // 00434cc8  8b0dfc347d00           -mov ecx, dword ptr [0x7d34fc]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205564) /* 0x7d34fc */);
    // 00434cce  8b150c357d00           -mov edx, dword ptr [0x7d350c]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205580) /* 0x7d350c */);
    // 00434cd4  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 00434cd9  750d                   -jne 0x434ce8
    if (!cpu.flags.zf)
    {
        goto L_0x00434ce8;
    }
    // 00434cdb  39c8                   +cmp eax, ecx
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ecx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00434cdd  7c09                   -jl 0x434ce8
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x00434ce8;
    }
    // 00434cdf  39d0                   +cmp eax, edx
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.edx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00434ce1  7e0f                   -jle 0x434cf2
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00434cf2;
    }
    // 00434ce3  83cb02                 +or ebx, 2
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(2 /*0x2*/))));
    // 00434ce6  eb0a                   -jmp 0x434cf2
    goto L_0x00434cf2;
L_0x00434ce8:
    // 00434ce8  83cb01                 +or ebx, 1
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(1 /*0x1*/))));
    // 00434ceb  eb05                   -jmp 0x434cf2
    goto L_0x00434cf2;
L_0x00434ced:
    // 00434ced  bb10000000             -mov ebx, 0x10
    cpu.ebx = 16 /*0x10*/;
L_0x00434cf2:
    // 00434cf2  881f                   -mov byte ptr [edi], bl
    app->getMemory<x86::reg8>(cpu.edi) = cpu.bl;
    // 00434cf4  8d7d1a                 -lea edi, [ebp + 0x1a]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(26) /* 0x1a */);
    // 00434cf7  8d7506                 -lea esi, [ebp + 6]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(6) /* 0x6 */);
    // 00434cfa  8b460c                 -mov eax, dword ptr [esi + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 00434cfd  8b0df8347d00           -mov ecx, dword ptr [0x7d34f8]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205560) /* 0x7d34f8 */);
    // 00434d03  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 00434d08  7558                   -jne 0x434d62
    if (!cpu.flags.zf)
    {
        goto L_0x00434d62;
    }
    // 00434d0a  39c8                   +cmp eax, ecx
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ecx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00434d0c  7d54                   -jge 0x434d62
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00434d62;
    }
    // 00434d0e  8b4604                 -mov eax, dword ptr [esi + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 00434d11  bb00000000             -mov ebx, 0
    cpu.ebx = 0 /*0x0*/;
    // 00434d16  8b0d04357d00           -mov ecx, dword ptr [0x7d3504]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205572) /* 0x7d3504 */);
    // 00434d1c  8b1500357d00           -mov edx, dword ptr [0x7d3500]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205568) /* 0x7d3500 */);
    // 00434d22  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 00434d27  750d                   -jne 0x434d36
    if (!cpu.flags.zf)
    {
        goto L_0x00434d36;
    }
    // 00434d29  39c8                   +cmp eax, ecx
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ecx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00434d2b  7c09                   -jl 0x434d36
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x00434d36;
    }
    // 00434d2d  39d0                   +cmp eax, edx
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.edx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00434d2f  7e09                   -jle 0x434d3a
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00434d3a;
    }
    // 00434d31  83cb04                 +or ebx, 4
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(4 /*0x4*/))));
    // 00434d34  eb04                   -jmp 0x434d3a
    goto L_0x00434d3a;
L_0x00434d36:
    // 00434d36  83cb08                 -or ebx, 8
    cpu.ebx |= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 00434d39  90                     -nop 
    ;
L_0x00434d3a:
    // 00434d3a  8b06                   -mov eax, dword ptr [esi]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi);
    // 00434d3c  90                     -nop 
    ;
    // 00434d3d  8b0dfc347d00           -mov ecx, dword ptr [0x7d34fc]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205564) /* 0x7d34fc */);
    // 00434d43  8b150c357d00           -mov edx, dword ptr [0x7d350c]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205580) /* 0x7d350c */);
    // 00434d49  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 00434d4e  750d                   -jne 0x434d5d
    if (!cpu.flags.zf)
    {
        goto L_0x00434d5d;
    }
    // 00434d50  39c8                   +cmp eax, ecx
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ecx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00434d52  7c09                   -jl 0x434d5d
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x00434d5d;
    }
    // 00434d54  39d0                   +cmp eax, edx
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.edx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00434d56  7e0f                   -jle 0x434d67
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00434d67;
    }
    // 00434d58  83cb02                 +or ebx, 2
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(2 /*0x2*/))));
    // 00434d5b  eb0a                   -jmp 0x434d67
    goto L_0x00434d67;
L_0x00434d5d:
    // 00434d5d  83cb01                 +or ebx, 1
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(1 /*0x1*/))));
    // 00434d60  eb05                   -jmp 0x434d67
    goto L_0x00434d67;
L_0x00434d62:
    // 00434d62  bb10000000             -mov ebx, 0x10
    cpu.ebx = 16 /*0x10*/;
L_0x00434d67:
    // 00434d67  881f                   -mov byte ptr [edi], bl
    app->getMemory<x86::reg8>(cpu.edi) = cpu.bl;
    // 00434d69  8d7d3a                 -lea edi, [ebp + 0x3a]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(58) /* 0x3a */);
    // 00434d6c  8d7526                 -lea esi, [ebp + 0x26]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(38) /* 0x26 */);
    // 00434d6f  8b460c                 -mov eax, dword ptr [esi + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 00434d72  8b0df8347d00           -mov ecx, dword ptr [0x7d34f8]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205560) /* 0x7d34f8 */);
    // 00434d78  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 00434d7d  7558                   -jne 0x434dd7
    if (!cpu.flags.zf)
    {
        goto L_0x00434dd7;
    }
    // 00434d7f  39c8                   +cmp eax, ecx
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ecx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00434d81  7d54                   -jge 0x434dd7
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00434dd7;
    }
    // 00434d83  8b4604                 -mov eax, dword ptr [esi + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 00434d86  bb00000000             -mov ebx, 0
    cpu.ebx = 0 /*0x0*/;
    // 00434d8b  8b0d04357d00           -mov ecx, dword ptr [0x7d3504]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205572) /* 0x7d3504 */);
    // 00434d91  8b1500357d00           -mov edx, dword ptr [0x7d3500]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205568) /* 0x7d3500 */);
    // 00434d97  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 00434d9c  750d                   -jne 0x434dab
    if (!cpu.flags.zf)
    {
        goto L_0x00434dab;
    }
    // 00434d9e  39c8                   +cmp eax, ecx
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ecx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00434da0  7c09                   -jl 0x434dab
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x00434dab;
    }
    // 00434da2  39d0                   +cmp eax, edx
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.edx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00434da4  7e09                   -jle 0x434daf
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00434daf;
    }
    // 00434da6  83cb04                 +or ebx, 4
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(4 /*0x4*/))));
    // 00434da9  eb04                   -jmp 0x434daf
    goto L_0x00434daf;
L_0x00434dab:
    // 00434dab  83cb08                 -or ebx, 8
    cpu.ebx |= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 00434dae  90                     -nop 
    ;
L_0x00434daf:
    // 00434daf  8b06                   -mov eax, dword ptr [esi]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi);
    // 00434db1  90                     -nop 
    ;
    // 00434db2  8b0dfc347d00           -mov ecx, dword ptr [0x7d34fc]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205564) /* 0x7d34fc */);
    // 00434db8  8b150c357d00           -mov edx, dword ptr [0x7d350c]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205580) /* 0x7d350c */);
    // 00434dbe  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 00434dc3  750d                   -jne 0x434dd2
    if (!cpu.flags.zf)
    {
        goto L_0x00434dd2;
    }
    // 00434dc5  39c8                   +cmp eax, ecx
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ecx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00434dc7  7c09                   -jl 0x434dd2
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x00434dd2;
    }
    // 00434dc9  39d0                   +cmp eax, edx
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.edx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00434dcb  7e0f                   -jle 0x434ddc
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00434ddc;
    }
    // 00434dcd  83cb02                 +or ebx, 2
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(2 /*0x2*/))));
    // 00434dd0  eb0a                   -jmp 0x434ddc
    goto L_0x00434ddc;
L_0x00434dd2:
    // 00434dd2  83cb01                 +or ebx, 1
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(1 /*0x1*/))));
    // 00434dd5  eb05                   -jmp 0x434ddc
    goto L_0x00434ddc;
L_0x00434dd7:
    // 00434dd7  bb10000000             -mov ebx, 0x10
    cpu.ebx = 16 /*0x10*/;
L_0x00434ddc:
    // 00434ddc  881f                   -mov byte ptr [edi], bl
    app->getMemory<x86::reg8>(cpu.edi) = cpu.bl;
    // 00434dde  8d7d5a                 -lea edi, [ebp + 0x5a]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(90) /* 0x5a */);
    // 00434de1  8d7546                 -lea esi, [ebp + 0x46]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(70) /* 0x46 */);
    // 00434de4  8b460c                 -mov eax, dword ptr [esi + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 00434de7  8b0df8347d00           -mov ecx, dword ptr [0x7d34f8]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205560) /* 0x7d34f8 */);
    // 00434ded  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 00434df2  7558                   -jne 0x434e4c
    if (!cpu.flags.zf)
    {
        goto L_0x00434e4c;
    }
    // 00434df4  39c8                   +cmp eax, ecx
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ecx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00434df6  7d54                   -jge 0x434e4c
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00434e4c;
    }
    // 00434df8  8b4604                 -mov eax, dword ptr [esi + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 00434dfb  bb00000000             -mov ebx, 0
    cpu.ebx = 0 /*0x0*/;
    // 00434e00  8b0d04357d00           -mov ecx, dword ptr [0x7d3504]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205572) /* 0x7d3504 */);
    // 00434e06  8b1500357d00           -mov edx, dword ptr [0x7d3500]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205568) /* 0x7d3500 */);
    // 00434e0c  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 00434e11  750d                   -jne 0x434e20
    if (!cpu.flags.zf)
    {
        goto L_0x00434e20;
    }
    // 00434e13  39c8                   +cmp eax, ecx
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ecx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00434e15  7c09                   -jl 0x434e20
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x00434e20;
    }
    // 00434e17  39d0                   +cmp eax, edx
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.edx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00434e19  7e09                   -jle 0x434e24
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00434e24;
    }
    // 00434e1b  83cb04                 +or ebx, 4
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(4 /*0x4*/))));
    // 00434e1e  eb04                   -jmp 0x434e24
    goto L_0x00434e24;
L_0x00434e20:
    // 00434e20  83cb08                 -or ebx, 8
    cpu.ebx |= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 00434e23  90                     -nop 
    ;
L_0x00434e24:
    // 00434e24  8b06                   -mov eax, dword ptr [esi]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi);
    // 00434e26  90                     -nop 
    ;
    // 00434e27  8b0dfc347d00           -mov ecx, dword ptr [0x7d34fc]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205564) /* 0x7d34fc */);
    // 00434e2d  8b150c357d00           -mov edx, dword ptr [0x7d350c]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205580) /* 0x7d350c */);
    // 00434e33  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 00434e38  750d                   -jne 0x434e47
    if (!cpu.flags.zf)
    {
        goto L_0x00434e47;
    }
    // 00434e3a  39c8                   +cmp eax, ecx
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ecx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00434e3c  7c09                   -jl 0x434e47
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x00434e47;
    }
    // 00434e3e  39d0                   +cmp eax, edx
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.edx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00434e40  7e0f                   -jle 0x434e51
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00434e51;
    }
    // 00434e42  83cb02                 +or ebx, 2
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(2 /*0x2*/))));
    // 00434e45  eb0a                   -jmp 0x434e51
    goto L_0x00434e51;
L_0x00434e47:
    // 00434e47  83cb01                 +or ebx, 1
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(1 /*0x1*/))));
    // 00434e4a  eb05                   -jmp 0x434e51
    goto L_0x00434e51;
L_0x00434e4c:
    // 00434e4c  bb10000000             -mov ebx, 0x10
    cpu.ebx = 16 /*0x10*/;
L_0x00434e51:
    // 00434e51  881f                   -mov byte ptr [edi], bl
    app->getMemory<x86::reg8>(cpu.edi) = cpu.bl;
    // 00434e53  8b153c3d5600           -mov edx, dword ptr [0x563d3c]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5651772) /* 0x563d3c */);
    // 00434e59  8d049500000000         -lea eax, [edx*4]
    cpu.eax = x86::reg32(cpu.edx * 4);
    // 00434e60  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 00434e62  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 00434e65  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 00434e67  8d4d46                 -lea ecx, [ebp + 0x46]
    cpu.ecx = x86::reg32(cpu.ebp + x86::reg32(70) /* 0x46 */);
    // 00434e6a  8b1485dc418b00         -mov edx, dword ptr [eax*4 + 0x8b41dc]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(9126364) /* 0x8b41dc */ + cpu.eax * 4);
    // 00434e71  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 00434e76  8d5d26                 -lea ebx, [ebp + 0x26]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(38) /* 0x26 */);
    // 00434e79  e882caffff             -call 0x431900
    cpu.esp -= 4;
    nfs3hp::graphics::setRenderState(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00434e7e  8d5506                 -lea edx, [ebp + 6]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(6) /* 0x6 */);
    // 00434e81  8d45e6                 -lea eax, [ebp - 0x1a]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-26) /* -0x1a */);
    // 00434e84  e857c40800             -call 0x4c12e0
    cpu.esp -= 4;
    sub_4c12e0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00434e89  8da582000000           -lea esp, [ebp + 0x82]
    cpu.esp = x86::reg32(cpu.ebp + x86::reg32(130) /* 0x82 */);
    // 00434e8f  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00434e90  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00434e91  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00434e92  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00434e93  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00434e94  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00434e95  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_434f20: native, nfs3hp::controls::startDirectInput */

/* sub_434fd0: native, nfs3hp::controls::stopDirectInput */

/* sub_4350a0: native, nfs3hp::controls::openMouse */

/* sub_435230: native, nfs3hp::frontend::placePointer */

/* sub_4352d0: native, nfs3hp::controls::setPointerBounds */

/* sub_435310: native, nfs3hp::controls::readMouse */

/* sub_435600: native, nfs3hp::controls::findJoysticks */

/* sub_435690: native, nfs3hp::controls::describeJoystick */

/* sub_4358f0: native, nfs3hp::controls::readJoystick */

/* sub_435ae0: native, nfs3hp::controls::readAxisZone */

/* sub_435b40: native, nfs3hp::controls::setAxisZone */

/* sub_435b60: native, nfs3hp::controls::resetForceFeedback */

/* sub_435bc0: native, nfs3hp::controls::setAutocenter */

/* sub_435c60: native, nfs3hp::controls::pauseEffects */

/* sub_435cc0: native, nfs3hp::controls::continueEffects */

/* sub_435d20: native, nfs3hp::controls::actuatorsOn */

/* sub_435d90: native, nfs3hp::controls::actuatorsOff */

/* sub_435df0: native, nfs3hp::controls::setGain */

/* sub_435f10: native, nfs3hp::controls::createEffect */

/* sub_4361e0: native, nfs3hp::controls::startEffect */

/* sub_436230: native, nfs3hp::controls::stopEffect */

/* sub_436270: native, nfs3hp::controls::stopEffects */

/* sub_4362f0: native, nfs3hp::controls::downloadEffect */

/* sub_436310: native, nfs3hp::controls::unloadEffect */

/* sub_436330: native, nfs3hp::controls::updateEffect */

/* sub_436610: native, nfs3hp::controls::setCooperativeLevel */

/* sub_4366e0: native, nfs3hp::controls::acquireDevice */

/* sub_436800: native, nfs3hp::controls::unacquireDevice */

/* sub_4368c0: native, nfs3hp::controls::acquireResult */

/* sub_4368f0: native, nfs3hp::controls::effectPlaying */

/* sub_436930: native, nfs3hp::controls::hideCursor */

/* sub_436980: native, nfs3hp::controls::joystickFound */

/* sub_436b10: native, nfs3hp::controls::axisProperty */

/* align: skip 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 */
void Application::sub_436c40(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00436c40  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00436c41  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00436c42  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00436c43  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00436c44  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00436c45  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00436c46  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00436c48  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00436c4a  8b7808                 -mov edi, dword ptr [eax + 8]
    cpu.edi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 00436c4d  8b500c                 -mov edx, dword ptr [eax + 0xc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
    // 00436c50  8b7004                 -mov esi, dword ptr [eax + 4]
    cpu.esi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 00436c53  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 00436c55  740b                   -je 0x436c62
    if (cpu.flags.zf)
    {
        goto L_0x00436c62;
    }
    // 00436c57  83fe01                 +cmp esi, 1
    {
        x86::reg32 tmp1 = cpu.esi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1 /*0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00436c5a  7e04                   -jle 0x436c60
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00436c60;
    }
    // 00436c5c  01d6                   +add esi, edx
    {
        x86::reg32& tmp1 = cpu.esi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.edx));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 00436c5e  eb02                   -jmp 0x436c62
    goto L_0x00436c62;
L_0x00436c60:
    // 00436c60  01d7                   -add edi, edx
    (cpu.edi) += x86::reg32(x86::sreg32(cpu.edx));
L_0x00436c62:
    // 00436c62  bb10000000             -mov ebx, 0x10
    cpu.ebx = 16 /*0x10*/;
    // 00436c67  bac8240000             -mov edx, 0x24c8
    cpu.edx = 9416 /*0x24c8*/;
    // 00436c6c  b890745300             -mov eax, 0x537490
    cpu.eax = 5469328 /*0x537490*/;
    // 00436c71  e8aaa90a00             -call 0x4e1620
    cpu.esp -= 4;
    nfs3hp::ea::reservememadr(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00436c76  bac8240000             -mov edx, 0x24c8
    cpu.edx = 9416 /*0x24c8*/;
    // 00436c7b  a3044f5500             -mov dword ptr [0x554f04], eax
    app->getMemory<x86::reg32>(x86::reg32(5590788) /* 0x554f04 */) = cpu.eax;
    // 00436c80  e8879a0a00             -call 0x4e070c
    cpu.esp -= 4;
    nfs3hp::fillZero(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00436c85  a1044f5500             -mov eax, dword ptr [0x554f04]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5590788) /* 0x554f04 */);
    // 00436c8a  8d5008                 -lea edx, [eax + 8]
    cpu.edx = x86::reg32(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 00436c8d  bb20000000             -mov ebx, 0x20
    cpu.ebx = 32 /*0x20*/;
    // 00436c92  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00436c94  e857380b00             -call 0x4ea4f0
    cpu.esp -= 4;
    nfs3hp::ea::memmove(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00436c99  a1044f5500             -mov eax, dword ptr [0x554f04]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5590788) /* 0x554f04 */);
    // 00436c9e  bb10000000             -mov ebx, 0x10
    cpu.ebx = 16 /*0x10*/;
    // 00436ca3  897004                 -mov dword ptr [eax + 4], esi
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */) = cpu.esi;
    // 00436ca6  baf8030000             -mov edx, 0x3f8
    cpu.edx = 1016 /*0x3f8*/;
    // 00436cab  8938                   -mov dword ptr [eax], edi
    app->getMemory<x86::reg32>(cpu.eax) = cpu.edi;
    // 00436cad  b890745300             -mov eax, 0x537490
    cpu.eax = 5469328 /*0x537490*/;
    // 00436cb2  e869a90a00             -call 0x4e1620
    cpu.esp -= 4;
    nfs3hp::ea::reservememadr(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00436cb7  baf8030000             -mov edx, 0x3f8
    cpu.edx = 1016 /*0x3f8*/;
    // 00436cbc  a3084f5500             -mov dword ptr [0x554f08], eax
    app->getMemory<x86::reg32>(x86::reg32(5590792) /* 0x554f08 */) = cpu.eax;
    // 00436cc1  e8469a0a00             -call 0x4e070c
    cpu.esp -= 4;
    nfs3hp::fillZero(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00436cc6  a1084f5500             -mov eax, dword ptr [0x554f08]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5590792) /* 0x554f08 */);
    // 00436ccb  8b5104                 -mov edx, dword ptr [ecx + 4]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(4) /* 0x4 */);
    // 00436cce  8910                   -mov dword ptr [eax], edx
    app->getMemory<x86::reg32>(cpu.eax) = cpu.edx;
    // 00436cd0  c7050c4f550001000000   -mov dword ptr [0x554f0c], 1
    app->getMemory<x86::reg32>(x86::reg32(5590796) /* 0x554f0c */) = 1 /*0x1*/;
    // 00436cda  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00436cdb  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00436cdc  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00436cdd  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00436cde  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00436cdf  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00436ce0  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x8d 0x40 0x00 */
void Application::sub_436cf0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00436cf0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00436cf1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00436cf2  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00436cf3  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00436cf4  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00436cf5  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00436cf7  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00436cf9  8b0d044f5500           -mov ecx, dword ptr [0x554f04]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(5590788) /* 0x554f04 */);
    // 00436cff  89150c4f5500           -mov dword ptr [0x554f0c], edx
    app->getMemory<x86::reg32>(x86::reg32(5590796) /* 0x554f0c */) = cpu.edx;
    // 00436d05  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    // 00436d07  7407                   -je 0x436d10
    if (cpu.flags.zf)
    {
        goto L_0x00436d10;
    }
    // 00436d09  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00436d0b  e880ab0a00             -call 0x4e1890
    cpu.esp -= 4;
    nfs3hp::ea::purgememadr(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00436d10:
    // 00436d10  8b1d084f5500           -mov ebx, dword ptr [0x554f08]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(5590792) /* 0x554f08 */);
    // 00436d16  85db                   +test ebx, ebx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & cpu.ebx));
    // 00436d18  7407                   -je 0x436d21
    if (cpu.flags.zf)
    {
        goto L_0x00436d21;
    }
    // 00436d1a  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 00436d1c  e86fab0a00             -call 0x4e1890
    cpu.esp -= 4;
    nfs3hp::ea::purgememadr(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00436d21:
    // 00436d21  31f6                   -xor esi, esi
    cpu.esi ^= x86::reg32(x86::sreg32(cpu.esi));
    // 00436d23  8935044f5500           -mov dword ptr [0x554f04], esi
    app->getMemory<x86::reg32>(x86::reg32(5590788) /* 0x554f04 */) = cpu.esi;
    // 00436d29  8935084f5500           -mov dword ptr [0x554f08], esi
    app->getMemory<x86::reg32>(x86::reg32(5590792) /* 0x554f08 */) = cpu.esi;
    // 00436d2f  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00436d30  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00436d31  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00436d32  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00436d33  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00436d34  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 0x8b 0xdb */
void Application::sub_436d40(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00436d40  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00436d41  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00436d42  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00436d44  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
L_0x00436d46:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00436d46  a1044f5500             -mov eax, dword ptr [0x554f04]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5590788) /* 0x554f04 */);
    // 00436d4b  3b5008                 +cmp edx, dword ptr [eax + 8]
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00436d4e  7d0a                   -jge 0x436d5a
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00436d5a;
    }
    // 00436d50  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 00436d52  e809000000             -call 0x436d60
    cpu.esp -= 4;
    sub_436d60(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00436d57  42                     +inc edx
    {
        x86::reg32& tmp = cpu.edx;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 00436d58  ebec                   -jmp 0x436d46
    goto L_0x00436d46;
L_0x00436d5a:
    // 00436d5a  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00436d5b  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00436d5c  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x40 0x00 */
void Application::sub_436d60(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00436d60  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00436d61  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00436d62  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00436d63  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00436d64  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00436d65  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00436d67  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 00436d69  8b350c4f5500           -mov esi, dword ptr [0x554f0c]
    cpu.esi = app->getMemory<x86::reg32>(x86::reg32(5590796) /* 0x554f0c */);
    // 00436d6f  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 00436d71  7444                   -je 0x436db7
    if (cpu.flags.zf)
    {
        goto L_0x00436db7;
    }
    // 00436d73  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00436d75  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 00436d77  89150c4f5500           -mov dword ptr [0x554f0c], edx
    app->getMemory<x86::reg32>(x86::reg32(5590796) /* 0x554f0c */) = cpu.edx;
L_0x00436d7d:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00436d7d  a1044f5500             -mov eax, dword ptr [0x554f04]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5590788) /* 0x554f04 */);
    // 00436d82  3b4804                 +cmp ecx, dword ptr [eax + 4]
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00436d85  7d0c                   -jge 0x436d93
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00436d93;
    }
    // 00436d87  89ca                   -mov edx, ecx
    cpu.edx = cpu.ecx;
    // 00436d89  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 00436d8b  e830000000             -call 0x436dc0
    cpu.esp -= 4;
    sub_436dc0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00436d90  41                     +inc ecx
    {
        x86::reg32& tmp = cpu.ecx;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 00436d91  ebea                   -jmp 0x436d7d
    goto L_0x00436d7d;
L_0x00436d93:
    // 00436d93  69db94040000           -imul ebx, ebx, 0x494
    cpu.ebx = x86::reg32(x86::sreg64(x86::sreg32(cpu.ebx)) * x86::sreg64(x86::sreg32(1172 /*0x494*/)));
    // 00436d99  c744032800000000       -mov dword ptr [ebx + eax + 0x28], 0
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(40) /* 0x28 */ + cpu.eax * 1) = 0 /*0x0*/;
    // 00436da1  c744032c00000000       -mov dword ptr [ebx + eax + 0x2c], 0
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(44) /* 0x2c */ + cpu.eax * 1) = 0 /*0x0*/;
    // 00436da9  89350c4f5500           -mov dword ptr [0x554f0c], esi
    app->getMemory<x86::reg32>(x86::reg32(5590796) /* 0x554f0c */) = cpu.esi;
    // 00436daf  c744033000000000       -mov dword ptr [ebx + eax + 0x30], 0
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(48) /* 0x30 */ + cpu.eax * 1) = 0 /*0x0*/;
L_0x00436db7:
    // 00436db7  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00436db8  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00436db9  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00436dba  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00436dbb  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00436dbc  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x40 0x00 */
void Application::sub_436dc0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00436dc0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00436dc1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00436dc2  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00436dc3  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00436dc5  69d894040000           -imul ebx, eax, 0x494
    cpu.ebx = x86::reg32(x86::sreg64(x86::sreg32(cpu.eax)) * x86::sreg64(x86::sreg32(1172 /*0x494*/)));
    // 00436dcb  8b0d044f5500           -mov ecx, dword ptr [0x554f04]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(5590788) /* 0x554f04 */);
    // 00436dd1  8d4128                 -lea eax, [ecx + 0x28]
    cpu.eax = x86::reg32(cpu.ecx + x86::reg32(40) /* 0x28 */);
    // 00436dd4  01c3                   -add ebx, eax
    (cpu.ebx) += x86::reg32(x86::sreg32(cpu.eax));
    // 00436dd6  8d04d500000000         -lea eax, [edx*8]
    cpu.eax = x86::reg32(cpu.edx * 8);
    // 00436ddd  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 00436ddf  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 00436de2  01c2                   -add edx, eax
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.eax));
    // 00436de4  c1e202                 -shl edx, 2
    cpu.edx <<= 2 /*0x2*/ % 32;
    // 00436de7  8d430c                 -lea eax, [ebx + 0xc]
    cpu.eax = x86::reg32(cpu.ebx + x86::reg32(12) /* 0xc */);
    // 00436dea  c7040200000000         -mov dword ptr [edx + eax], 0
    app->getMemory<x86::reg32>(cpu.edx + cpu.eax * 1) = 0 /*0x0*/;
    // 00436df1  c744020400000000       -mov dword ptr [edx + eax + 4], 0
    app->getMemory<x86::reg32>(cpu.edx + x86::reg32(4) /* 0x4 */ + cpu.eax * 1) = 0 /*0x0*/;
    // 00436df9  c744020800000000       -mov dword ptr [edx + eax + 8], 0
    app->getMemory<x86::reg32>(cpu.edx + x86::reg32(8) /* 0x8 */ + cpu.eax * 1) = 0 /*0x0*/;
    // 00436e01  c644020c00             -mov byte ptr [edx + eax + 0xc], 0
    app->getMemory<x86::reg8>(cpu.edx + x86::reg32(12) /* 0xc */ + cpu.eax * 1) = 0 /*0x0*/;
    // 00436e06  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00436e07  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00436e08  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00436e09  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 */
void Application::sub_436e10(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00436e10  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00436e11  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00436e12  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00436e13  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00436e14  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00436e16  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 00436e18  89d3                   -mov ebx, edx
    cpu.ebx = cpu.edx;
    // 00436e1a  8b150c4f5500           -mov edx, dword ptr [0x554f0c]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5590796) /* 0x554f0c */);
    // 00436e20  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 00436e22  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 00436e24  7507                   -jne 0x436e2d
    if (!cpu.flags.zf)
    {
        goto L_0x00436e2d;
    }
    // 00436e26  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00436e28  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00436e29  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00436e2a  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00436e2b  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00436e2c  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x00436e2d:
    // 00436e2d  ff05d83f5f00           -inc dword ptr [0x5f3fd8]
    (app->getMemory<x86::reg32>(x86::reg32(6242264) /* 0x5f3fd8 */))++;
L_0x00436e33:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00436e33  803b00                 +cmp byte ptr [ebx], 0
    {
        x86::reg8 tmp1 = app->getMemory<x86::reg8>(cpu.ebx);
        x86::reg8 tmp2 = x86::reg8(x86::sreg8(0 /*0x0*/));
        x86::reg8 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 7);
        cpu.flags.of ^= 1 & (result >> 7);
        cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
        cpu.set_szp(result);
    }
    // 00436e36  7421                   -je 0x436e59
    if (cpu.flags.zf)
    {
        goto L_0x00436e59;
    }
    // 00436e38  a1044f5500             -mov eax, dword ptr [0x554f04]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5590788) /* 0x554f04 */);
    // 00436e3d  3b08                   +cmp ecx, dword ptr [eax]
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.eax)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00436e3f  7d18                   -jge 0x436e59
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00436e59;
    }
    // 00436e41  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00436e43  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 00436e45  8a13                   -mov dl, byte ptr [ebx]
    cpu.dl = app->getMemory<x86::reg8>(cpu.ebx);
    // 00436e47  e844000000             -call 0x436e90
    cpu.esp -= 4;
    sub_436e90(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00436e4c  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00436e4e  7505                   -jne 0x436e55
    if (!cpu.flags.zf)
    {
        goto L_0x00436e55;
    }
    // 00436e50  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00436e51  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00436e52  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00436e53  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00436e54  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x00436e55:
    // 00436e55  41                     +inc ecx
    {
        x86::reg32& tmp = cpu.ecx;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 00436e56  43                     +inc ebx
    {
        x86::reg32& tmp = cpu.ebx;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 00436e57  ebda                   -jmp 0x436e33
    goto L_0x00436e33;
L_0x00436e59:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00436e59  a1044f5500             -mov eax, dword ptr [0x554f04]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5590788) /* 0x554f04 */);
    // 00436e5e  3b08                   +cmp ecx, dword ptr [eax]
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.eax)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00436e60  7d15                   -jge 0x436e77
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00436e77;
    }
    // 00436e62  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 00436e64  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00436e66  e825000000             -call 0x436e90
    cpu.esp -= 4;
    sub_436e90(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00436e6b  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00436e6d  7505                   -jne 0x436e74
    if (!cpu.flags.zf)
    {
        goto L_0x00436e74;
    }
    // 00436e6f  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00436e70  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00436e71  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00436e72  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00436e73  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x00436e74:
    // 00436e74  41                     +inc ecx
    {
        x86::reg32& tmp = cpu.ecx;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 00436e75  ebe2                   -jmp 0x436e59
    goto L_0x00436e59;
L_0x00436e77:
    // 00436e77  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 00436e7c  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00436e7d  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00436e7e  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00436e7f  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00436e80  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x8d 0x40 0x00 */
void Application::sub_436e90(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00436e90  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00436e91  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00436e92  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00436e93  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00436e94  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00436e95  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00436e97  83ec08                 -sub esp, 8
    (cpu.esp) -= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 00436e9a  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 00436e9c  8855fc                 -mov byte ptr [ebp - 4], dl
    app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.dl;
    // 00436e9f  833d0c4f550000         +cmp dword ptr [0x554f0c], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5590796) /* 0x554f0c */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00436ea6  7507                   -jne 0x436eaf
    if (!cpu.flags.zf)
    {
        goto L_0x00436eaf;
    }
    // 00436ea8  31c9                   +xor ecx, ecx
    cpu.clear_co();
    cpu.set_szp((cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx))));
    // 00436eaa  e9f9000000             -jmp 0x436fa8
    goto L_0x00436fa8;
L_0x00436eaf:
    // 00436eaf  69c094040000           -imul eax, eax, 0x494
    cpu.eax = x86::reg32(x86::sreg64(x86::sreg32(cpu.eax)) * x86::sreg64(x86::sreg32(1172 /*0x494*/)));
    // 00436eb5  8b3d044f5500           -mov edi, dword ptr [0x554f04]
    cpu.edi = app->getMemory<x86::reg32>(x86::reg32(5590788) /* 0x554f04 */);
    // 00436ebb  8945f8                 -mov dword ptr [ebp - 8], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.eax;
    // 00436ebe  8d3438                 -lea esi, [eax + edi]
    cpu.esi = x86::reg32(cpu.eax + cpu.edi * 1);
    // 00436ec1  8b5630                 -mov edx, dword ptr [esi + 0x30]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(48) /* 0x30 */);
    // 00436ec4  8d04d500000000         -lea eax, [edx*8]
    cpu.eax = x86::reg32(cpu.edx * 8);
    // 00436ecb  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 00436ecd  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 00436ed0  8b4df8                 -mov ecx, dword ptr [ebp - 8]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 00436ed3  01c2                   -add edx, eax
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.eax));
    // 00436ed5  8d4728                 -lea eax, [edi + 0x28]
    cpu.eax = x86::reg32(cpu.edi + x86::reg32(40) /* 0x28 */);
    // 00436ed8  01c8                   -add eax, ecx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.ecx));
    // 00436eda  c1e202                 -shl edx, 2
    cpu.edx <<= 2 /*0x2*/ % 32;
    // 00436edd  83c00c                 -add eax, 0xc
    (cpu.eax) += x86::reg32(x86::sreg32(12 /*0xc*/));
    // 00436ee0  8d0c10                 -lea ecx, [eax + edx]
    cpu.ecx = x86::reg32(cpu.eax + cpu.edx * 1);
    // 00436ee3  8b4108                 -mov eax, dword ptr [ecx + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(8) /* 0x8 */);
    // 00436ee6  8d5001                 -lea edx, [eax + 1]
    cpu.edx = x86::reg32(cpu.eax + x86::reg32(1) /* 0x1 */);
    // 00436ee9  895108                 -mov dword ptr [ecx + 8], edx
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(8) /* 0x8 */) = cpu.edx;
    // 00436eec  8a55fc                 -mov dl, byte ptr [ebp - 4]
    cpu.dl = app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00436eef  8854010c               -mov byte ptr [ecx + eax + 0xc], dl
    app->getMemory<x86::reg8>(cpu.ecx + x86::reg32(12) /* 0xc */ + cpu.eax * 1) = cpu.dl;
    // 00436ef3  837f0c01               +cmp dword ptr [edi + 0xc], 1
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.edi + x86::reg32(12) /* 0xc */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1 /*0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00436ef7  7537                   -jne 0x436f30
    if (!cpu.flags.zf)
    {
        goto L_0x00436f30;
    }
    // 00436ef9  8b17                   -mov edx, dword ptr [edi]
    cpu.edx = app->getMemory<x86::reg32>(cpu.edi);
    // 00436efb  3b5108                 +cmp edx, dword ptr [ecx + 8]
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(8) /* 0x8 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00436efe  7d07                   -jge 0x436f07
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00436f07;
    }
    // 00436f00  c7410800000000         -mov dword ptr [ecx + 8], 0
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(8) /* 0x8 */) = 0 /*0x0*/;
L_0x00436f07:
    // 00436f07  8b5904                 -mov ebx, dword ptr [ecx + 4]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(4) /* 0x4 */);
    // 00436f0a  3b5908                 +cmp ebx, dword ptr [ecx + 8]
    {
        x86::reg32 tmp1 = cpu.ebx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(8) /* 0x8 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00436f0d  751a                   -jne 0x436f29
    if (!cpu.flags.zf)
    {
        goto L_0x00436f29;
    }
    // 00436f0f  8d7301                 -lea esi, [ebx + 1]
    cpu.esi = x86::reg32(cpu.ebx + x86::reg32(1) /* 0x1 */);
    // 00436f12  a1044f5500             -mov eax, dword ptr [0x554f04]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5590788) /* 0x554f04 */);
    // 00436f17  897104                 -mov dword ptr [ecx + 4], esi
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(4) /* 0x4 */) = cpu.esi;
    // 00436f1a  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 00436f1c  8b18                   -mov ebx, dword ptr [eax]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.eax);
    // 00436f1e  c1fa1f                 -sar edx, 0x1f
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (31 /*0x1f*/ % 32));
    // 00436f21  43                     -inc ebx
    (cpu.ebx)++;
    // 00436f22  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 00436f24  f7fb                   +idiv ebx
    {
        x86::sreg64 tmp = x86::sreg64(cpu.edx_eax);
        x86::sreg32 d = x86::sreg32(cpu.ebx);
        cpu.edx_eax = x86::reg64(tmp / d);
        cpu.edx = x86::reg32(tmp % d);
    }
    // 00436f26  895104                 -mov dword ptr [ecx + 4], edx
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(4) /* 0x4 */) = cpu.edx;
L_0x00436f29:
    // 00436f29  8b4104                 -mov eax, dword ptr [ecx + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(4) /* 0x4 */);
    // 00436f2c  8901                   -mov dword ptr [ecx], eax
    app->getMemory<x86::reg32>(cpu.ecx) = cpu.eax;
    // 00436f2e  eb6b                   -jmp 0x436f9b
    goto L_0x00436f9b;
L_0x00436f30:
    // 00436f30  8b17                   -mov edx, dword ptr [edi]
    cpu.edx = app->getMemory<x86::reg32>(cpu.edi);
    // 00436f32  3b5108                 +cmp edx, dword ptr [ecx + 8]
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(8) /* 0x8 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00436f35  753f                   -jne 0x436f76
    if (!cpu.flags.zf)
    {
        goto L_0x00436f76;
    }
    // 00436f37  8b4630                 -mov eax, dword ptr [esi + 0x30]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(48) /* 0x30 */);
    // 00436f3a  40                     -inc eax
    (cpu.eax)++;
    // 00436f3b  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 00436f3d  894630                 -mov dword ptr [esi + 0x30], eax
    app->getMemory<x86::reg32>(cpu.esi + x86::reg32(48) /* 0x30 */) = cpu.eax;
    // 00436f40  c1fa1f                 -sar edx, 0x1f
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (31 /*0x1f*/ % 32));
    // 00436f43  f77f04                 -idiv dword ptr [edi + 4]
    {
        x86::sreg64 tmp = x86::sreg64(cpu.edx_eax);
        x86::sreg32 d = x86::sreg32(app->getMemory<x86::reg32>(cpu.edi + x86::reg32(4) /* 0x4 */));
        cpu.edx_eax = x86::reg64(tmp / d);
        cpu.edx = x86::reg32(tmp % d);
    }
    // 00436f46  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 00436f48  895630                 -mov dword ptr [esi + 0x30], edx
    app->getMemory<x86::reg32>(cpu.esi + x86::reg32(48) /* 0x30 */) = cpu.edx;
    // 00436f4b  e870feffff             -call 0x436dc0
    cpu.esp -= 4;
    sub_436dc0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00436f50  8b75f8                 -mov esi, dword ptr [ebp - 8]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 00436f53  8b3d044f5500           -mov edi, dword ptr [0x554f04]
    cpu.edi = app->getMemory<x86::reg32>(x86::reg32(5590788) /* 0x554f04 */);
    // 00436f59  01fe                   -add esi, edi
    (cpu.esi) += x86::reg32(x86::sreg32(cpu.edi));
    // 00436f5b  8b4630                 -mov eax, dword ptr [esi + 0x30]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(48) /* 0x30 */);
    // 00436f5e  8b562c                 -mov edx, dword ptr [esi + 0x2c]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(44) /* 0x2c */);
    // 00436f61  39d0                   +cmp eax, edx
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.edx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00436f63  7511                   -jne 0x436f76
    if (!cpu.flags.zf)
    {
        goto L_0x00436f76;
    }
    // 00436f65  8d4201                 -lea eax, [edx + 1]
    cpu.eax = x86::reg32(cpu.edx + x86::reg32(1) /* 0x1 */);
    // 00436f68  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 00436f6a  89462c                 -mov dword ptr [esi + 0x2c], eax
    app->getMemory<x86::reg32>(cpu.esi + x86::reg32(44) /* 0x2c */) = cpu.eax;
    // 00436f6d  c1fa1f                 -sar edx, 0x1f
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (31 /*0x1f*/ % 32));
    // 00436f70  f77f04                 -idiv dword ptr [edi + 4]
    {
        x86::sreg64 tmp = x86::sreg64(cpu.edx_eax);
        x86::sreg32 d = x86::sreg32(app->getMemory<x86::reg32>(cpu.edi + x86::reg32(4) /* 0x4 */));
        cpu.edx_eax = x86::reg64(tmp / d);
        cpu.edx = x86::reg32(tmp % d);
    }
    // 00436f73  89562c                 -mov dword ptr [esi + 0x2c], edx
    app->getMemory<x86::reg32>(cpu.esi + x86::reg32(44) /* 0x2c */) = cpu.edx;
L_0x00436f76:
    // 00436f76  a1044f5500             -mov eax, dword ptr [0x554f04]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5590788) /* 0x554f04 */);
    // 00436f7b  83782000               +cmp dword ptr [eax + 0x20], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(32) /* 0x20 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00436f7f  7407                   -je 0x436f88
    if (cpu.flags.zf)
    {
        goto L_0x00436f88;
    }
    // 00436f81  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 00436f83  e818020000             -call 0x4371a0
    cpu.esp -= 4;
    sub_4371a0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00436f88:
    // 00436f88  69d394040000           -imul edx, ebx, 0x494
    cpu.edx = x86::reg32(x86::sreg64(x86::sreg32(cpu.ebx)) * x86::sreg64(x86::sreg32(1172 /*0x494*/)));
    // 00436f8e  a1044f5500             -mov eax, dword ptr [0x554f04]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5590788) /* 0x554f04 */);
    // 00436f93  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 00436f95  8b502c                 -mov edx, dword ptr [eax + 0x2c]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(44) /* 0x2c */);
    // 00436f98  895028                 -mov dword ptr [eax + 0x28], edx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(40) /* 0x28 */) = cpu.edx;
L_0x00436f9b:
    // 00436f9b  8b4108                 -mov eax, dword ptr [ecx + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(8) /* 0x8 */);
    // 00436f9e  c644010c00             -mov byte ptr [ecx + eax + 0xc], 0
    app->getMemory<x86::reg8>(cpu.ecx + x86::reg32(12) /* 0xc */ + cpu.eax * 1) = 0 /*0x0*/;
    // 00436fa3  b901000000             -mov ecx, 1
    cpu.ecx = 1 /*0x1*/;
L_0x00436fa8:
    // 00436fa8  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00436faa  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00436fac  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00436fad  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00436fae  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00436faf  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00436fb0  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00436fb1  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x8b 0xc0 */
void Application::sub_436fc0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00436fc0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00436fc1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00436fc2  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00436fc3  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00436fc4  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00436fc5  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00436fc7  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 00436fc9  833d0c4f550000         +cmp dword ptr [0x554f0c], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5590796) /* 0x554f0c */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00436fd0  7507                   -jne 0x436fd9
    if (!cpu.flags.zf)
    {
        goto L_0x00436fd9;
    }
    // 00436fd2  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
    // 00436fd4  e99b000000             -jmp 0x437074
    goto L_0x00437074;
L_0x00436fd9:
    // 00436fd9  69cb94040000           -imul ecx, ebx, 0x494
    cpu.ecx = x86::reg32(x86::sreg64(x86::sreg32(cpu.ebx)) * x86::sreg64(x86::sreg32(1172 /*0x494*/)));
    // 00436fdf  a1044f5500             -mov eax, dword ptr [0x554f04]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5590788) /* 0x554f04 */);
    // 00436fe4  83c028                 -add eax, 0x28
    (cpu.eax) += x86::reg32(x86::sreg32(40 /*0x28*/));
    // 00436fe7  01c1                   -add ecx, eax
    (cpu.ecx) += x86::reg32(x86::sreg32(cpu.eax));
    // 00436fe9  8b5108                 -mov edx, dword ptr [ecx + 8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(8) /* 0x8 */);
L_0x00436fec:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00436fec  3b5104                 +cmp edx, dword ptr [ecx + 4]
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(4) /* 0x4 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00436fef  7428                   -je 0x437019
    if (cpu.flags.zf)
    {
        goto L_0x00437019;
    }
    // 00436ff1  8d04d500000000         -lea eax, [edx*8]
    cpu.eax = x86::reg32(cpu.edx * 8);
    // 00436ff8  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 00436ffa  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 00436ffd  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 00436fff  8b748114               -mov esi, dword ptr [ecx + eax*4 + 0x14]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(20) /* 0x14 */ + cpu.eax * 4);
    // 00437003  3b748110               +cmp esi, dword ptr [ecx + eax*4 + 0x10]
    {
        x86::reg32 tmp1 = cpu.esi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(16) /* 0x10 */ + cpu.eax * 4)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00437007  7510                   -jne 0x437019
    if (!cpu.flags.zf)
    {
        goto L_0x00437019;
    }
    // 00437009  4a                     -dec edx
    (cpu.edx)--;
    // 0043700a  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 0043700c  7dde                   -jge 0x436fec
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00436fec;
    }
    // 0043700e  a1044f5500             -mov eax, dword ptr [0x554f04]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5590788) /* 0x554f04 */);
    // 00437013  8b5004                 -mov edx, dword ptr [eax + 4]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 00437016  4a                     +dec edx
    {
        x86::reg32& tmp = cpu.edx;
        cpu.flags.of = 1 & (tmp >> 31);
        tmp--;
        cpu.flags.of &= ~(1 & (tmp >> 31));
        cpu.set_szp(tmp);
    }
    // 00437017  ebd3                   -jmp 0x436fec
    goto L_0x00436fec;
L_0x00437019:
    // 00437019  8d04d500000000         -lea eax, [edx*8]
    cpu.eax = x86::reg32(cpu.edx * 8);
    // 00437020  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 00437022  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 00437025  8d3402                 -lea esi, [edx + eax]
    cpu.esi = x86::reg32(cpu.edx + cpu.eax * 1);
    // 00437028  c1e602                 -shl esi, 2
    cpu.esi <<= 2 /*0x2*/ % 32;
    // 0043702b  8d410c                 -lea eax, [ecx + 0xc]
    cpu.eax = x86::reg32(cpu.ecx + x86::reg32(12) /* 0xc */);
    // 0043702e  01f0                   -add eax, esi
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.esi));
    // 00437030  8b7008                 -mov esi, dword ptr [eax + 8]
    cpu.esi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 00437033  3b7004                 +cmp esi, dword ptr [eax + 4]
    {
        x86::reg32 tmp1 = cpu.esi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00437036  7508                   -jne 0x437040
    if (!cpu.flags.zf)
    {
        goto L_0x00437040;
    }
    // 00437038  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 0043703a  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043703b  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043703c  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043703d  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043703e  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043703f  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x00437040:
    // 00437040  4e                     -dec esi
    (cpu.esi)--;
    // 00437041  897008                 -mov dword ptr [eax + 8], esi
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */) = cpu.esi;
    // 00437044  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 00437046  7d0b                   -jge 0x437053
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00437053;
    }
    // 00437048  8b35044f5500           -mov esi, dword ptr [0x554f04]
    cpu.esi = app->getMemory<x86::reg32>(x86::reg32(5590788) /* 0x554f04 */);
    // 0043704e  8b36                   -mov esi, dword ptr [esi]
    cpu.esi = app->getMemory<x86::reg32>(cpu.esi);
    // 00437050  897008                 -mov dword ptr [eax + 8], esi
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */) = cpu.esi;
L_0x00437053:
    // 00437053  895108                 -mov dword ptr [ecx + 8], edx
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(8) /* 0x8 */) = cpu.edx;
    // 00437056  034008                 -add eax, dword ptr [eax + 8]
    (cpu.eax) += x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */)));
    // 00437059  c6400c00               -mov byte ptr [eax + 0xc], 0
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(12) /* 0xc */) = 0 /*0x0*/;
    // 0043705d  a1044f5500             -mov eax, dword ptr [0x554f04]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5590788) /* 0x554f04 */);
    // 00437062  83782000               +cmp dword ptr [eax + 0x20], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(32) /* 0x20 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00437066  7407                   -je 0x43706f
    if (cpu.flags.zf)
    {
        goto L_0x0043706f;
    }
    // 00437068  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 0043706a  e831010000             -call 0x4371a0
    cpu.esp -= 4;
    sub_4371a0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x0043706f:
    // 0043706f  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
L_0x00437074:
    // 00437074  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00437075  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00437076  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00437077  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00437078  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00437079  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 */
void Application::sub_437080(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00437080  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00437081  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00437082  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00437083  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00437084  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00437085  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00437086  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00437088  83ec08                 -sub esp, 8
    (cpu.esp) -= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 0043708b  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 0043708d  69d394040000           -imul edx, ebx, 0x494
    cpu.edx = x86::reg32(x86::sreg64(x86::sreg32(cpu.ebx)) * x86::sreg64(x86::sreg32(1172 /*0x494*/)));
    // 00437093  a1084f5500             -mov eax, dword ptr [0x554f08]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5590792) /* 0x554f08 */);
    // 00437098  8b08                   -mov ecx, dword ptr [eax]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax);
    // 0043709a  83f901                 +cmp ecx, 1
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1 /*0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0043709d  7576                   -jne 0x437115
    if (!cpu.flags.zf)
    {
        goto L_0x00437115;
    }
    // 0043709f  a1044f5500             -mov eax, dword ptr [0x554f04]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5590788) /* 0x554f04 */);
    // 004370a4  8b7010                 -mov esi, dword ptr [eax + 0x10]
    cpu.esi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(16) /* 0x10 */);
    // 004370a7  8b540234               -mov edx, dword ptr [edx + eax + 0x34]
    cpu.edx = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(52) /* 0x34 */ + cpu.eax * 1);
    // 004370ab  01ce                   -add esi, ecx
    (cpu.esi) += x86::reg32(x86::sreg32(cpu.ecx));
    // 004370ad  8d3c32                 -lea edi, [edx + esi]
    cpu.edi = x86::reg32(cpu.edx + cpu.esi * 1);
    // 004370b0  89f1                   -mov ecx, esi
    cpu.ecx = cpu.esi;
    // 004370b2  39fe                   +cmp esi, edi
    {
        x86::reg32 tmp1 = cpu.esi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.edi));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004370b4  7d07                   -jge 0x4370bd
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004370bd;
    }
    // 004370b6  8b00                   -mov eax, dword ptr [eax]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax);
    // 004370b8  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 004370ba  8d4801                 -lea ecx, [eax + 1]
    cpu.ecx = x86::reg32(cpu.eax + x86::reg32(1) /* 0x1 */);
L_0x004370bd:
    // 004370bd  69fb94040000           -imul edi, ebx, 0x494
    cpu.edi = x86::reg32(x86::sreg64(x86::sreg32(cpu.ebx)) * x86::sreg64(x86::sreg32(1172 /*0x494*/)));
    // 004370c3  a1084f5500             -mov eax, dword ptr [0x554f08]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5590792) /* 0x554f08 */);
    // 004370c8  83c004                 -add eax, 4
    (cpu.eax) += x86::reg32(x86::sreg32(4 /*0x4*/));
    // 004370cb  8945f8                 -mov dword ptr [ebp - 8], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.eax;
    // 004370ce  a1044f5500             -mov eax, dword ptr [0x554f04]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5590788) /* 0x554f04 */);
    // 004370d3  83c028                 -add eax, 0x28
    (cpu.eax) += x86::reg32(x86::sreg32(40 /*0x28*/));
    // 004370d6  01f8                   -add eax, edi
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edi));
    // 004370d8  83c018                 -add eax, 0x18
    (cpu.eax) += x86::reg32(x86::sreg32(24 /*0x18*/));
    // 004370db  89cb                   -mov ebx, ecx
    cpu.ebx = cpu.ecx;
    // 004370dd  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 004370df  8b55f8                 -mov edx, dword ptr [ebp - 8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004370e2  e809340b00             -call 0x4ea4f0
    cpu.esp -= 4;
    nfs3hp::ea::memmove(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004370e7  39f1                   +cmp ecx, esi
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.esi));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004370e9  0f8da0000000           -jge 0x43718f
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x0043718f;
    }
    // 004370ef  a1084f5500             -mov eax, dword ptr [0x554f08]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5590792) /* 0x554f08 */);
    // 004370f4  83c004                 -add eax, 4
    (cpu.eax) += x86::reg32(x86::sreg32(4 /*0x4*/));
    // 004370f7  8d1408                 -lea edx, [eax + ecx]
    cpu.edx = x86::reg32(cpu.eax + cpu.ecx * 1);
    // 004370fa  a1044f5500             -mov eax, dword ptr [0x554f04]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5590788) /* 0x554f04 */);
    // 004370ff  83c028                 -add eax, 0x28
    (cpu.eax) += x86::reg32(x86::sreg32(40 /*0x28*/));
    // 00437102  89f3                   -mov ebx, esi
    cpu.ebx = cpu.esi;
    // 00437104  01f8                   -add eax, edi
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edi));
    // 00437106  29cb                   -sub ebx, ecx
    (cpu.ebx) -= x86::reg32(x86::sreg32(cpu.ecx));
    // 00437108  83c018                 +add eax, 0x18
    {
        x86::reg32& tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(24 /*0x18*/));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 0043710b  e8e0330b00             -call 0x4ea4f0
    cpu.esp -= 4;
    nfs3hp::ea::memmove(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00437110  e97a000000             -jmp 0x43718f
    goto L_0x0043718f;
L_0x00437115:
    // 00437115  a1044f5500             -mov eax, dword ptr [0x554f04]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5590788) /* 0x554f04 */);
    // 0043711a  8b440228               -mov eax, dword ptr [edx + eax + 0x28]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(40) /* 0x28 */ + cpu.eax * 1);
    // 0043711e  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 00437120  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
L_0x00437123:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00437123  8b3d084f5500           -mov edi, dword ptr [0x554f08]
    cpu.edi = app->getMemory<x86::reg32>(x86::reg32(5590792) /* 0x554f08 */);
    // 00437129  3b0f                   +cmp ecx, dword ptr [edi]
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.edi)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0043712b  7d62                   -jge 0x43718f
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x0043718f;
    }
    // 0043712d  8b55fc                 -mov edx, dword ptr [ebp - 4]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00437130  01ca                   -add edx, ecx
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.ecx));
    // 00437132  8b35044f5500           -mov esi, dword ptr [0x554f04]
    cpu.esi = app->getMemory<x86::reg32>(x86::reg32(5590788) /* 0x554f04 */);
    // 00437138  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 0043713a  c1fa1f                 -sar edx, 0x1f
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (31 /*0x1f*/ % 32));
    // 0043713d  f77e04                 -idiv dword ptr [esi + 4]
    {
        x86::sreg64 tmp = x86::sreg64(cpu.edx_eax);
        x86::sreg32 d = x86::sreg32(app->getMemory<x86::reg32>(cpu.esi + x86::reg32(4) /* 0x4 */));
        cpu.edx_eax = x86::reg64(tmp / d);
        cpu.edx = x86::reg32(tmp % d);
    }
    // 00437140  8d04d500000000         -lea eax, [edx*8]
    cpu.eax = x86::reg32(cpu.edx * 8);
    // 00437147  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 00437149  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 0043714c  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 0043714e  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 00437151  8945f8                 -mov dword ptr [ebp - 8], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.eax;
    // 00437154  69c394040000           -imul eax, ebx, 0x494
    cpu.eax = x86::reg32(x86::sreg64(x86::sreg32(cpu.ebx)) * x86::sreg64(x86::sreg32(1172 /*0x494*/)));
    // 0043715a  83c628                 -add esi, 0x28
    (cpu.esi) += x86::reg32(x86::sreg32(40 /*0x28*/));
    // 0043715d  01f0                   -add eax, esi
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.esi));
    // 0043715f  8b55f8                 -mov edx, dword ptr [ebp - 8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 00437162  83c00c                 -add eax, 0xc
    (cpu.eax) += x86::reg32(x86::sreg32(12 /*0xc*/));
    // 00437165  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 00437167  8d700c                 -lea esi, [eax + 0xc]
    cpu.esi = x86::reg32(cpu.eax + x86::reg32(12) /* 0xc */);
    // 0043716a  6bc165                 -imul eax, ecx, 0x65
    cpu.eax = x86::reg32(x86::sreg64(x86::sreg32(cpu.ecx)) * x86::sreg64(x86::sreg32(101 /*0x65*/)));
    // 0043716d  83c704                 -add edi, 4
    (cpu.edi) += x86::reg32(x86::sreg32(4 /*0x4*/));
    // 00437170  01c7                   -add edi, eax
    (cpu.edi) += x86::reg32(x86::sreg32(cpu.eax));
    // 00437172  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
L_0x00437173:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00437173  8a06                   -mov al, byte ptr [esi]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi);
    // 00437175  8807                   -mov byte ptr [edi], al
    app->getMemory<x86::reg8>(cpu.edi) = cpu.al;
    // 00437177  3c00                   +cmp al, 0
    {
        x86::reg8 tmp1 = cpu.al;
        x86::reg8 tmp2 = x86::reg8(x86::sreg8(0 /*0x0*/));
        x86::reg8 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 7);
        cpu.flags.of ^= 1 & (result >> 7);
        cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
        cpu.set_szp(result);
    }
    // 00437179  7410                   -je 0x43718b
    if (cpu.flags.zf)
    {
        goto L_0x0043718b;
    }
    // 0043717b  8a4601                 -mov al, byte ptr [esi + 1]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi + x86::reg32(1) /* 0x1 */);
    // 0043717e  83c602                 -add esi, 2
    (cpu.esi) += x86::reg32(x86::sreg32(2 /*0x2*/));
    // 00437181  884701                 -mov byte ptr [edi + 1], al
    app->getMemory<x86::reg8>(cpu.edi + x86::reg32(1) /* 0x1 */) = cpu.al;
    // 00437184  83c702                 -add edi, 2
    (cpu.edi) += x86::reg32(x86::sreg32(2 /*0x2*/));
    // 00437187  3c00                   +cmp al, 0
    {
        x86::reg8 tmp1 = cpu.al;
        x86::reg8 tmp2 = x86::reg8(x86::sreg8(0 /*0x0*/));
        x86::reg8 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 7);
        cpu.flags.of ^= 1 & (result >> 7);
        cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
        cpu.set_szp(result);
    }
    // 00437189  75e8                   -jne 0x437173
    if (!cpu.flags.zf)
    {
        goto L_0x00437173;
    }
L_0x0043718b:
    // 0043718b  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043718c  41                     +inc ecx
    {
        x86::reg32& tmp = cpu.ecx;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 0043718d  eb94                   -jmp 0x437123
    goto L_0x00437123;
L_0x0043718f:
    // 0043718f  a1084f5500             -mov eax, dword ptr [0x554f08]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5590792) /* 0x554f08 */);
    // 00437194  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00437196  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00437197  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00437198  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00437199  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043719a  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043719b  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043719c  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x40 0x00 */
void Application::sub_4371a0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004371a0  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004371a1  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004371a3  a1044f5500             -mov eax, dword ptr [0x554f04]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5590788) /* 0x554f04 */);
    // 004371a8  83782000               +cmp dword ptr [eax + 0x20], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(32) /* 0x20 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004371ac  7404                   -je 0x4371b2
    if (cpu.flags.zf)
    {
        goto L_0x004371b2;
    }
    // 004371ae  83780c01               -cmp dword ptr [eax + 0xc], 1
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1 /*0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
L_0x004371b2:
    // 004371b2  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004371b3  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 */
void Application::sub_4371c0(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004371c0  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004371c1  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004371c3  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004371c4  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 0x8b 0xdb */
void Application::sub_4371d0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004371d0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004371d1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004371d2  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004371d3  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004371d4  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004371d6  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004371d8  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 004371db  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 004371dd  f6c201                 +test dl, 1
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.dl & 1 /*0x1*/));
    // 004371e0  7501                   -jne 0x4371e3
    if (!cpu.flags.zf)
    {
        goto L_0x004371e3;
    }
    // 004371e2  42                     -inc edx
    (cpu.edx)++;
L_0x004371e3:
    // 004371e3  89d3                   -mov ebx, edx
    cpu.ebx = cpu.edx;
    // 004371e5  a801                   +test al, 1
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.al & 1 /*0x1*/));
    // 004371e7  7501                   -jne 0x4371ea
    if (!cpu.flags.zf)
    {
        goto L_0x004371ea;
    }
    // 004371e9  40                     -inc eax
    (cpu.eax)++;
L_0x004371ea:
    // 004371ea  89da                   -mov edx, ebx
    cpu.edx = cpu.ebx;
    // 004371ec  0fafd0                 -imul edx, eax
    cpu.edx = x86::reg32(x86::sreg64(x86::sreg32(cpu.edx)) * x86::sreg64(x86::sreg32(cpu.eax)));
    // 004371ef  81e2ffff0000           -and edx, 0xffff
    cpu.edx &= x86::reg32(x86::sreg32(65535 /*0xffff*/));
    // 004371f5  0fafd3                 -imul edx, ebx
    cpu.edx = x86::reg32(x86::sreg64(x86::sreg32(cpu.edx)) * x86::sreg64(x86::sreg32(cpu.ebx)));
    // 004371f8  81e2ffff0000           -and edx, 0xffff
    cpu.edx &= x86::reg32(x86::sreg32(65535 /*0xffff*/));
    // 004371fe  0fafd3                 -imul edx, ebx
    cpu.edx = x86::reg32(x86::sreg64(x86::sreg32(cpu.edx)) * x86::sreg64(x86::sreg32(cpu.ebx)));
    // 00437201  81e2ffff0000           -and edx, 0xffff
    cpu.edx &= x86::reg32(x86::sreg32(65535 /*0xffff*/));
    // 00437207  0fafd3                 -imul edx, ebx
    cpu.edx = x86::reg32(x86::sreg64(x86::sreg32(cpu.edx)) * x86::sreg64(x86::sreg32(cpu.ebx)));
    // 0043720a  81e2ffff0000           -and edx, 0xffff
    cpu.edx &= x86::reg32(x86::sreg32(65535 /*0xffff*/));
    // 00437210  0fafd3                 -imul edx, ebx
    cpu.edx = x86::reg32(x86::sreg64(x86::sreg32(cpu.edx)) * x86::sreg64(x86::sreg32(cpu.ebx)));
    // 00437213  81e2ffff0000           -and edx, 0xffff
    cpu.edx &= x86::reg32(x86::sreg32(65535 /*0xffff*/));
    // 00437219  0fafd3                 -imul edx, ebx
    cpu.edx = x86::reg32(x86::sreg64(x86::sreg32(cpu.edx)) * x86::sreg64(x86::sreg32(cpu.ebx)));
    // 0043721c  81e2ffff0000           -and edx, 0xffff
    cpu.edx &= x86::reg32(x86::sreg32(65535 /*0xffff*/));
    // 00437222  0fafd3                 -imul edx, ebx
    cpu.edx = x86::reg32(x86::sreg64(x86::sreg32(cpu.edx)) * x86::sreg64(x86::sreg32(cpu.ebx)));
    // 00437225  81e2ffff0000           -and edx, 0xffff
    cpu.edx &= x86::reg32(x86::sreg32(65535 /*0xffff*/));
    // 0043722b  0fafd3                 -imul edx, ebx
    cpu.edx = x86::reg32(x86::sreg64(x86::sreg32(cpu.edx)) * x86::sreg64(x86::sreg32(cpu.ebx)));
    // 0043722e  89d1                   -mov ecx, edx
    cpu.ecx = cpu.edx;
    // 00437230  81e1ffff0000           -and ecx, 0xffff
    cpu.ecx &= x86::reg32(x86::sreg32(65535 /*0xffff*/));
    // 00437236  8915144f5500           -mov dword ptr [0x554f14], edx
    app->getMemory<x86::reg32>(x86::reg32(5590804) /* 0x554f14 */) = cpu.edx;
    // 0043723c  890d104f5500           -mov dword ptr [0x554f10], ecx
    app->getMemory<x86::reg32>(x86::reg32(5590800) /* 0x554f10 */) = cpu.ecx;
    // 00437242  891d184f5500           -mov dword ptr [0x554f18], ebx
    app->getMemory<x86::reg32>(x86::reg32(5590808) /* 0x554f18 */) = cpu.ebx;
    // 00437248  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00437249  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043724a  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043724b  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043724c  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x00 0x00 0x00 */
void Application::sub_437250(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (feedSeparate(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 00437250  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00437251  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00437252  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00437253  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00437254  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
L_0x00437256:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00437256  8b1508bc6f00           -mov edx, dword ptr [0x6fbc08]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(7322632) /* 0x6fbc08 */);
    // 0043725c  a104bc6f00             -mov eax, dword ptr [0x6fbc04]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(7322628) /* 0x6fbc04 */);
    // 00437261  39d0                   +cmp eax, edx
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.edx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00437263  7408                   -je 0x43726d
    if (cpu.flags.zf)
    {
        goto L_0x0043726d;
    }
    // 00437265  3b050cbc6f00           +cmp eax, dword ptr [0x6fbc0c]
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(7322636) /* 0x6fbc0c */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0043726b  751c                   -jne 0x437289
    if (!cpu.flags.zf)
    {
        goto L_0x00437289;
    }
L_0x0043726d:
    // 0043726d  8b1d04bc6f00           -mov ebx, dword ptr [0x6fbc04]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(7322628) /* 0x6fbc04 */);
    // 00437273  43                     -inc ebx
    (cpu.ebx)++;
    // 00437274  891d04bc6f00           -mov dword ptr [0x6fbc04], ebx
    app->getMemory<x86::reg32>(x86::reg32(7322628) /* 0x6fbc04 */) = cpu.ebx;
    // 0043727a  83fb09                 +cmp ebx, 9
    {
        x86::reg32 tmp1 = cpu.ebx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(9 /*0x9*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0043727d  7ed7                   -jle 0x437256
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00437256;
    }
    // 0043727f  31ff                   +xor edi, edi
    cpu.clear_co();
    cpu.set_szp((cpu.edi ^= x86::reg32(x86::sreg32(cpu.edi))));
    // 00437281  893d04bc6f00           -mov dword ptr [0x6fbc04], edi
    app->getMemory<x86::reg32>(x86::reg32(7322628) /* 0x6fbc04 */) = cpu.edi;
    // 00437287  ebcd                   -jmp 0x437256
    goto L_0x00437256;
L_0x00437289:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00437289  8b1504bc6f00           -mov edx, dword ptr [0x6fbc04]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(7322628) /* 0x6fbc04 */);
    // 0043728f  a108bc6f00             -mov eax, dword ptr [0x6fbc08]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(7322632) /* 0x6fbc08 */);
    // 00437294  39d0                   +cmp eax, edx
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.edx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00437296  7408                   -je 0x4372a0
    if (cpu.flags.zf)
    {
        goto L_0x004372a0;
    }
    // 00437298  3b050cbc6f00           +cmp eax, dword ptr [0x6fbc0c]
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(7322636) /* 0x6fbc0c */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0043729e  751c                   -jne 0x4372bc
    if (!cpu.flags.zf)
    {
        goto L_0x004372bc;
    }
L_0x004372a0:
    // 004372a0  8b1d08bc6f00           -mov ebx, dword ptr [0x6fbc08]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(7322632) /* 0x6fbc08 */);
    // 004372a6  43                     -inc ebx
    (cpu.ebx)++;
    // 004372a7  891d08bc6f00           -mov dword ptr [0x6fbc08], ebx
    app->getMemory<x86::reg32>(x86::reg32(7322632) /* 0x6fbc08 */) = cpu.ebx;
    // 004372ad  83fb09                 +cmp ebx, 9
    {
        x86::reg32 tmp1 = cpu.ebx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(9 /*0x9*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004372b0  7ed7                   -jle 0x437289
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00437289;
    }
    // 004372b2  31ff                   +xor edi, edi
    cpu.clear_co();
    cpu.set_szp((cpu.edi ^= x86::reg32(x86::sreg32(cpu.edi))));
    // 004372b4  893d08bc6f00           -mov dword ptr [0x6fbc08], edi
    app->getMemory<x86::reg32>(x86::reg32(7322632) /* 0x6fbc08 */) = cpu.edi;
    // 004372ba  ebcd                   -jmp 0x437289
    goto L_0x00437289;
L_0x004372bc:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004372bc  8b1504bc6f00           -mov edx, dword ptr [0x6fbc04]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(7322628) /* 0x6fbc04 */);
    // 004372c2  a10cbc6f00             -mov eax, dword ptr [0x6fbc0c]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(7322636) /* 0x6fbc0c */);
    // 004372c7  39d0                   +cmp eax, edx
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.edx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004372c9  7408                   -je 0x4372d3
    if (cpu.flags.zf)
    {
        goto L_0x004372d3;
    }
    // 004372cb  3b0508bc6f00           +cmp eax, dword ptr [0x6fbc08]
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(7322632) /* 0x6fbc08 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004372d1  751c                   -jne 0x4372ef
    if (!cpu.flags.zf)
    {
        goto L_0x004372ef;
    }
L_0x004372d3:
    // 004372d3  8b1d0cbc6f00           -mov ebx, dword ptr [0x6fbc0c]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(7322636) /* 0x6fbc0c */);
    // 004372d9  43                     -inc ebx
    (cpu.ebx)++;
    // 004372da  891d0cbc6f00           -mov dword ptr [0x6fbc0c], ebx
    app->getMemory<x86::reg32>(x86::reg32(7322636) /* 0x6fbc0c */) = cpu.ebx;
    // 004372e0  83fb09                 +cmp ebx, 9
    {
        x86::reg32 tmp1 = cpu.ebx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(9 /*0x9*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004372e3  7ed7                   -jle 0x4372bc
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004372bc;
    }
    // 004372e5  31ff                   +xor edi, edi
    cpu.clear_co();
    cpu.set_szp((cpu.edi ^= x86::reg32(x86::sreg32(cpu.edi))));
    // 004372e7  893d0cbc6f00           -mov dword ptr [0x6fbc0c], edi
    app->getMemory<x86::reg32>(x86::reg32(7322636) /* 0x6fbc0c */) = cpu.edi;
    // 004372ed  ebcd                   -jmp 0x4372bc
    goto L_0x004372bc;
L_0x004372ef:
    // 004372ef  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004372f0  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004372f1  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004372f2  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004372f3  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 */
void Application::sub_437300(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (feedTimeButtonKey(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 00437300  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00437301  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00437302  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00437303  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00437304  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00437306  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00437308  89d6                   -mov esi, edx
    cpu.esi = cpu.edx;
    // 0043730a  89df                   -mov edi, ebx
    cpu.edi = cpu.ebx;
    // 0043730c  6683fb0d               +cmp bx, 0xd
    {
        x86::reg16 tmp1 = cpu.bx;
        x86::reg16 tmp2 = x86::reg16(x86::sreg16(13 /*0xd*/));
        x86::reg16 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 15);
        cpu.flags.of ^= 1 & (result >> 15);
        cpu.flags.of &= (1 & (tmp1 >> 15)) != (1 & (tmp2 >> 15));
        cpu.set_szp(result);
    }
    // 00437310  7527                   -jne 0x437339
    if (!cpu.flags.zf)
    {
        goto L_0x00437339;
    }
L_0x00437312:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00437312  0fbfdf                 -movsx ebx, di
    cpu.ebx = x86::reg32(static_cast<x86::sreg16>(cpu.di));
    // 00437315  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 00437317  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00437319  e8529f0200             -call 0x461270
    cpu.esp -= 4;
    nfs3hp::frontend::buttonKey(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0043731e  8b1d04bc6f00           -mov ebx, dword ptr [0x6fbc04]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(7322628) /* 0x6fbc04 */);
    // 00437324  3b1d08bc6f00           +cmp ebx, dword ptr [0x6fbc08]
    {
        x86::reg32 tmp1 = cpu.ebx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(7322632) /* 0x6fbc08 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0043732a  74e6                   -je 0x437312
    if (cpu.flags.zf)
    {
        goto L_0x00437312;
    }
    // 0043732c  3b1d0cbc6f00           +cmp ebx, dword ptr [0x6fbc0c]
    {
        x86::reg32 tmp1 = cpu.ebx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(7322636) /* 0x6fbc0c */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00437332  74de                   -je 0x437312
    if (cpu.flags.zf)
    {
        goto L_0x00437312;
    }
    // 00437334  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00437335  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00437336  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00437337  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00437338  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x00437339:
    // 00437339  0fbfdb                 -movsx ebx, bx
    cpu.ebx = x86::reg32(static_cast<x86::sreg16>(cpu.bx));
    // 0043733c  e82f9f0200             -call 0x461270
    cpu.esp -= 4;
    nfs3hp::frontend::buttonKey(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00437341  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00437342  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00437343  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00437344  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00437345  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x54 0x22 0x00 */
void Application::sub_437350(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (feedTimeListKey(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 00437350  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00437351  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00437352  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00437354  0fbfdb                 -movsx ebx, bx
    cpu.ebx = x86::reg32(static_cast<x86::sreg16>(cpu.bx));
    // 00437357  8b0d04bc6f00           -mov ecx, dword ptr [0x6fbc04]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(7322628) /* 0x6fbc04 */);
    // 0043735d  e83eb10200             -call 0x4624a0
    cpu.esp -= 4;
    sub_4624a0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00437362  8b1504bc6f00           -mov edx, dword ptr [0x6fbc04]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(7322628) /* 0x6fbc04 */);
    // 00437368  39d1                   +cmp ecx, edx
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.edx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0043736a  7416                   -je 0x437382
    if (cpu.flags.zf)
    {
        goto L_0x00437382;
    }
    // 0043736c  3b1508bc6f00           +cmp edx, dword ptr [0x6fbc08]
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(7322632) /* 0x6fbc08 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00437372  7408                   -je 0x43737c
    if (cpu.flags.zf)
    {
        goto L_0x0043737c;
    }
    // 00437374  3b150cbc6f00           +cmp edx, dword ptr [0x6fbc0c]
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(7322636) /* 0x6fbc0c */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0043737a  7506                   -jne 0x437382
    if (!cpu.flags.zf)
    {
        goto L_0x00437382;
    }
L_0x0043737c:
    // 0043737c  890d04bc6f00           -mov dword ptr [0x6fbc04], ecx
    app->getMemory<x86::reg32>(x86::reg32(7322628) /* 0x6fbc04 */) = cpu.ecx;
L_0x00437382:
    // 00437382  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00437383  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00437384  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 0x8b 0xdb */
void Application::sub_437390(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (feedPositionButtonKey(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 00437390  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00437391  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00437392  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00437393  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00437394  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00437396  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00437398  89d6                   -mov esi, edx
    cpu.esi = cpu.edx;
    // 0043739a  89df                   -mov edi, ebx
    cpu.edi = cpu.ebx;
    // 0043739c  6683fb0d               +cmp bx, 0xd
    {
        x86::reg16 tmp1 = cpu.bx;
        x86::reg16 tmp2 = x86::reg16(x86::sreg16(13 /*0xd*/));
        x86::reg16 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 15);
        cpu.flags.of ^= 1 & (result >> 15);
        cpu.flags.of &= (1 & (tmp1 >> 15)) != (1 & (tmp2 >> 15));
        cpu.set_szp(result);
    }
    // 004373a0  7527                   -jne 0x4373c9
    if (!cpu.flags.zf)
    {
        goto L_0x004373c9;
    }
L_0x004373a2:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004373a2  0fbfdf                 -movsx ebx, di
    cpu.ebx = x86::reg32(static_cast<x86::sreg16>(cpu.di));
    // 004373a5  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 004373a7  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004373a9  e8c29e0200             -call 0x461270
    cpu.esp -= 4;
    nfs3hp::frontend::buttonKey(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004373ae  8b1d08bc6f00           -mov ebx, dword ptr [0x6fbc08]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(7322632) /* 0x6fbc08 */);
    // 004373b4  3b1d04bc6f00           +cmp ebx, dword ptr [0x6fbc04]
    {
        x86::reg32 tmp1 = cpu.ebx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(7322628) /* 0x6fbc04 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004373ba  74e6                   -je 0x4373a2
    if (cpu.flags.zf)
    {
        goto L_0x004373a2;
    }
    // 004373bc  3b1d0cbc6f00           +cmp ebx, dword ptr [0x6fbc0c]
    {
        x86::reg32 tmp1 = cpu.ebx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(7322636) /* 0x6fbc0c */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004373c2  74de                   -je 0x4373a2
    if (cpu.flags.zf)
    {
        goto L_0x004373a2;
    }
    // 004373c4  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004373c5  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004373c6  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004373c7  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004373c8  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004373c9:
    // 004373c9  0fbfdb                 -movsx ebx, bx
    cpu.ebx = x86::reg32(static_cast<x86::sreg16>(cpu.bx));
    // 004373cc  e89f9e0200             -call 0x461270
    cpu.esp -= 4;
    nfs3hp::frontend::buttonKey(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004373d1  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004373d2  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004373d3  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004373d4  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004373d5  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x54 0x22 0x00 */
void Application::sub_4373e0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (feedPositionListKey(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 004373e0  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004373e1  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004373e2  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004373e4  0fbfdb                 -movsx ebx, bx
    cpu.ebx = x86::reg32(static_cast<x86::sreg16>(cpu.bx));
    // 004373e7  8b0d08bc6f00           -mov ecx, dword ptr [0x6fbc08]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(7322632) /* 0x6fbc08 */);
    // 004373ed  e8aeb00200             -call 0x4624a0
    cpu.esp -= 4;
    sub_4624a0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004373f2  8b1508bc6f00           -mov edx, dword ptr [0x6fbc08]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(7322632) /* 0x6fbc08 */);
    // 004373f8  39d1                   +cmp ecx, edx
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.edx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004373fa  7416                   -je 0x437412
    if (cpu.flags.zf)
    {
        goto L_0x00437412;
    }
    // 004373fc  3b1504bc6f00           +cmp edx, dword ptr [0x6fbc04]
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(7322628) /* 0x6fbc04 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00437402  7408                   -je 0x43740c
    if (cpu.flags.zf)
    {
        goto L_0x0043740c;
    }
    // 00437404  3b150cbc6f00           +cmp edx, dword ptr [0x6fbc0c]
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(7322636) /* 0x6fbc0c */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0043740a  7506                   -jne 0x437412
    if (!cpu.flags.zf)
    {
        goto L_0x00437412;
    }
L_0x0043740c:
    // 0043740c  890d08bc6f00           -mov dword ptr [0x6fbc08], ecx
    app->getMemory<x86::reg32>(x86::reg32(7322632) /* 0x6fbc08 */) = cpu.ecx;
L_0x00437412:
    // 00437412  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00437413  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00437414  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 0x8b 0xdb */
void Application::sub_437420(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (feedSpeedButtonKey(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 00437420  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00437421  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00437422  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00437423  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00437424  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00437426  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00437428  89d6                   -mov esi, edx
    cpu.esi = cpu.edx;
    // 0043742a  89df                   -mov edi, ebx
    cpu.edi = cpu.ebx;
    // 0043742c  6683fb0d               +cmp bx, 0xd
    {
        x86::reg16 tmp1 = cpu.bx;
        x86::reg16 tmp2 = x86::reg16(x86::sreg16(13 /*0xd*/));
        x86::reg16 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 15);
        cpu.flags.of ^= 1 & (result >> 15);
        cpu.flags.of &= (1 & (tmp1 >> 15)) != (1 & (tmp2 >> 15));
        cpu.set_szp(result);
    }
    // 00437430  7527                   -jne 0x437459
    if (!cpu.flags.zf)
    {
        goto L_0x00437459;
    }
L_0x00437432:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00437432  0fbfdf                 -movsx ebx, di
    cpu.ebx = x86::reg32(static_cast<x86::sreg16>(cpu.di));
    // 00437435  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 00437437  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00437439  e8329e0200             -call 0x461270
    cpu.esp -= 4;
    nfs3hp::frontend::buttonKey(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0043743e  8b1d0cbc6f00           -mov ebx, dword ptr [0x6fbc0c]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(7322636) /* 0x6fbc0c */);
    // 00437444  3b1d04bc6f00           +cmp ebx, dword ptr [0x6fbc04]
    {
        x86::reg32 tmp1 = cpu.ebx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(7322628) /* 0x6fbc04 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0043744a  74e6                   -je 0x437432
    if (cpu.flags.zf)
    {
        goto L_0x00437432;
    }
    // 0043744c  3b1d08bc6f00           +cmp ebx, dword ptr [0x6fbc08]
    {
        x86::reg32 tmp1 = cpu.ebx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(7322632) /* 0x6fbc08 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00437452  74de                   -je 0x437432
    if (cpu.flags.zf)
    {
        goto L_0x00437432;
    }
    // 00437454  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00437455  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00437456  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00437457  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00437458  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x00437459:
    // 00437459  0fbfdb                 -movsx ebx, bx
    cpu.ebx = x86::reg32(static_cast<x86::sreg16>(cpu.bx));
    // 0043745c  e80f9e0200             -call 0x461270
    cpu.esp -= 4;
    nfs3hp::frontend::buttonKey(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00437461  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00437462  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00437463  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00437464  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00437465  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x54 0x22 0x00 */
void Application::sub_437470(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (feedSpeedListKey(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 00437470  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00437471  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00437472  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00437474  0fbfdb                 -movsx ebx, bx
    cpu.ebx = x86::reg32(static_cast<x86::sreg16>(cpu.bx));
    // 00437477  8b0d0cbc6f00           -mov ecx, dword ptr [0x6fbc0c]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(7322636) /* 0x6fbc0c */);
    // 0043747d  e81eb00200             -call 0x4624a0
    cpu.esp -= 4;
    sub_4624a0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00437482  8b150cbc6f00           -mov edx, dword ptr [0x6fbc0c]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(7322636) /* 0x6fbc0c */);
    // 00437488  39d1                   +cmp ecx, edx
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.edx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0043748a  7416                   -je 0x4374a2
    if (cpu.flags.zf)
    {
        goto L_0x004374a2;
    }
    // 0043748c  3b1504bc6f00           +cmp edx, dword ptr [0x6fbc04]
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(7322628) /* 0x6fbc04 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00437492  7408                   -je 0x43749c
    if (cpu.flags.zf)
    {
        goto L_0x0043749c;
    }
    // 00437494  3b1508bc6f00           +cmp edx, dword ptr [0x6fbc08]
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(7322632) /* 0x6fbc08 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0043749a  7506                   -jne 0x4374a2
    if (!cpu.flags.zf)
    {
        goto L_0x004374a2;
    }
L_0x0043749c:
    // 0043749c  890d0cbc6f00           -mov dword ptr [0x6fbc0c], ecx
    app->getMemory<x86::reg32>(x86::reg32(7322636) /* 0x6fbc0c */) = cpu.ecx;
L_0x004374a2:
    // 004374a2  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004374a3  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004374a4  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 0x8b 0xdb */
void Application::sub_4374b0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (feedOnEnter(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 004374b0  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004374b1  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004374b2  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004374b3  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004374b5  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 004374b7  a104bc6f00             -mov eax, dword ptr [0x6fbc04]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(7322628) /* 0x6fbc04 */);
    // 004374bc  a314395f00             -mov dword ptr [0x5f3914], eax
    app->getMemory<x86::reg32>(x86::reg32(6240532) /* 0x5f3914 */) = cpu.eax;
    // 004374c1  a10cbc6f00             -mov eax, dword ptr [0x6fbc0c]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(7322636) /* 0x6fbc0c */);
    // 004374c6  a318395f00             -mov dword ptr [0x5f3918], eax
    app->getMemory<x86::reg32>(x86::reg32(6240536) /* 0x5f3918 */) = cpu.eax;
    // 004374cb  a108bc6f00             -mov eax, dword ptr [0x6fbc08]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(7322632) /* 0x6fbc08 */);
    // 004374d0  ba94745300             -mov edx, 0x537494
    cpu.edx = 5469332 /*0x537494*/;
    // 004374d5  a310395f00             -mov dword ptr [0x5f3910], eax
    app->getMemory<x86::reg32>(x86::reg32(6240528) /* 0x5f3910 */) = cpu.eax;
    // 004374da  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004374dc  e85fb50000             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004374e1  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004374e3  740d                   -je 0x4374f2
    if (cpu.flags.zf)
    {
        goto L_0x004374f2;
    }
    // 004374e5  833db0d36f0001         +cmp dword ptr [0x6fd3b0], 1
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(7328688) /* 0x6fd3b0 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1 /*0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004374ec  7e04                   -jle 0x4374f2
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004374f2;
    }
    // 004374ee  80480401               -or byte ptr [eax + 4], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(4) /* 0x4 */) |= x86::reg8(x86::sreg8(1 /*0x1*/));
L_0x004374f2:
    // 004374f2  ba9c745300             -mov edx, 0x53749c
    cpu.edx = 5469340 /*0x53749c*/;
    // 004374f7  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004374f9  e842b50000             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004374fe  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00437500  7407                   -je 0x437509
    if (cpu.flags.zf)
    {
        goto L_0x00437509;
    }
    // 00437502  c7403000734300         -mov dword ptr [eax + 0x30], 0x437300
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(48) /* 0x30 */) = 4420352 /*0x437300*/;
L_0x00437509:
    // 00437509  baac745300             -mov edx, 0x5374ac
    cpu.edx = 5469356 /*0x5374ac*/;
    // 0043750e  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00437510  e82bb50000             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00437515  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00437517  7407                   -je 0x437520
    if (cpu.flags.zf)
    {
        goto L_0x00437520;
    }
    // 00437519  c7403050734300         -mov dword ptr [eax + 0x30], 0x437350
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(48) /* 0x30 */) = 4420432 /*0x437350*/;
L_0x00437520:
    // 00437520  babc745300             -mov edx, 0x5374bc
    cpu.edx = 5469372 /*0x5374bc*/;
    // 00437525  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00437527  e814b50000             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0043752c  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0043752e  7407                   -je 0x437537
    if (cpu.flags.zf)
    {
        goto L_0x00437537;
    }
    // 00437530  c7403090734300         -mov dword ptr [eax + 0x30], 0x437390
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(48) /* 0x30 */) = 4420496 /*0x437390*/;
L_0x00437537:
    // 00437537  bacc745300             -mov edx, 0x5374cc
    cpu.edx = 5469388 /*0x5374cc*/;
    // 0043753c  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 0043753e  e8fdb40000             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00437543  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00437545  7407                   -je 0x43754e
    if (cpu.flags.zf)
    {
        goto L_0x0043754e;
    }
    // 00437547  c74030e0734300         -mov dword ptr [eax + 0x30], 0x4373e0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(48) /* 0x30 */) = 4420576 /*0x4373e0*/;
L_0x0043754e:
    // 0043754e  badc745300             -mov edx, 0x5374dc
    cpu.edx = 5469404 /*0x5374dc*/;
    // 00437553  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00437555  e8e6b40000             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0043755a  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0043755c  7407                   -je 0x437565
    if (cpu.flags.zf)
    {
        goto L_0x00437565;
    }
    // 0043755e  c7403020744300         -mov dword ptr [eax + 0x30], 0x437420
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(48) /* 0x30 */) = 4420640 /*0x437420*/;
L_0x00437565:
    // 00437565  bae8745300             -mov edx, 0x5374e8
    cpu.edx = 5469416 /*0x5374e8*/;
    // 0043756a  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 0043756c  e8cfb40000             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00437571  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00437573  7407                   -je 0x43757c
    if (cpu.flags.zf)
    {
        goto L_0x0043757c;
    }
    // 00437575  c7403070744300         -mov dword ptr [eax + 0x30], 0x437470
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(48) /* 0x30 */) = 4420720 /*0x437470*/;
L_0x0043757c:
    // 0043757c  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 0043757e  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043757f  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00437580  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00437581  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x8b 0xc0 */
void Application::sub_437590(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (feedOnExit(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 00437590  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00437591  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00437592  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00437594  8b5018                 -mov edx, dword ptr [eax + 0x18]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */);
    // 00437597  8b4016                 -mov eax, dword ptr [eax + 0x16]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(22) /* 0x16 */);
    // 0043759a  c1fa10                 -sar edx, 0x10
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (16 /*0x10*/ % 32));
    // 0043759d  c1f810                 -sar eax, 0x10
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (16 /*0x10*/ % 32));
    // 004375a0  01c2                   -add edx, eax
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.eax));
    // 004375a2  8d049500000000         -lea eax, [edx*4]
    cpu.eax = x86::reg32(cpu.edx * 4);
    // 004375a9  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 004375ab  c1e004                 -shl eax, 4
    cpu.eax <<= 4 /*0x4*/ % 32;
    // 004375ae  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 004375b0  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 004375b3  05e04e6000             -add eax, 0x604ee0
    (cpu.eax) += x86::reg32(x86::sreg32(6311648 /*0x604ee0*/));
    // 004375b8  833805                 +cmp dword ptr [eax], 5
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(5 /*0x5*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004375bb  7534                   -jne 0x4375f1
    if (!cpu.flags.zf)
    {
        goto L_0x004375f1;
    }
    // 004375bd  baf4745300             -mov edx, 0x5374f4
    cpu.edx = 5469428 /*0x5374f4*/;
    // 004375c2  8b4010                 -mov eax, dword ptr [eax + 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(16) /* 0x10 */);
    // 004375c5  e8f6b30000             -call 0x4429c0
    cpu.esp -= 4;
    sub_4429c0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004375ca  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004375cc  7423                   -je 0x4375f1
    if (cpu.flags.zf)
    {
        goto L_0x004375f1;
    }
    // 004375ce  a114395f00             -mov eax, dword ptr [0x5f3914]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(6240532) /* 0x5f3914 */);
    // 004375d3  a304bc6f00             -mov dword ptr [0x6fbc04], eax
    app->getMemory<x86::reg32>(x86::reg32(7322628) /* 0x6fbc04 */) = cpu.eax;
    // 004375d8  a118395f00             -mov eax, dword ptr [0x5f3918]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(6240536) /* 0x5f3918 */);
    // 004375dd  a30cbc6f00             -mov dword ptr [0x6fbc0c], eax
    app->getMemory<x86::reg32>(x86::reg32(7322636) /* 0x6fbc0c */) = cpu.eax;
    // 004375e2  a110395f00             -mov eax, dword ptr [0x5f3910]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(6240528) /* 0x5f3910 */);
    // 004375e7  a308bc6f00             -mov dword ptr [0x6fbc08], eax
    app->getMemory<x86::reg32>(x86::reg32(7322632) /* 0x6fbc08 */) = cpu.eax;
    // 004375ec  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 004375ee  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004375ef  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004375f0  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004375f1:
    // 004375f1  e85afcffff             -call 0x437250
    cpu.esp -= 4;
    sub_437250(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004375f6  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 004375f8  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004375f9  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004375fa  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_437600: native, nfs3hp::frontend::funkeysOnEnter */

/* sub_4377c0: native, nfs3hp::frontend::funkeysOnExit */

/* sub_4377d0: native, nfs3hp::frontend::hardkeysOnEnter */

/* align: skip 0x00 0x00 */
void Application::sub_437990(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (audioMenuMusicMoved(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 00437990  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00437991  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00437992  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00437994  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00437996  e815500300             -call 0x46c9b0
    cpu.esp -= 4;
    nfs3hp::frontend::sliderValue(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0043799b  dc0d78755300           -fmul qword ptr [0x537578]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = cpu.fpu.st(0);
    x86::Float fpu2 = cpu.fpu.mul(fpu1, x86::Float(app->getMemory<double>(x86::reg32(5469560) /* 0x537578 */)));
    cpu.fpu.st(0) = fpu2;
    }
    // 004379a1  e8b0830a00             -call 0x4dfd56
    cpu.esp -= 4;
    nfs3hp::watcom::CHP(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004379a6  db1de8bb6f00           -fistp dword ptr [0x6fbbe8]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu3 = cpu.fpu.st(0);
    app->getMemory<x86::reg32>(x86::reg32(7322600) /* 0x6fbbe8 */) = x86::reg32(cpu.fpu.toInteger<x86::sreg32>(fpu3));
    // 004379ac  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004379ad  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    cpu.fpu.count -= 1;
    }
    // 004379ae  c3                     -ret 
    cpu.esp += 4;
    return;
}

}
