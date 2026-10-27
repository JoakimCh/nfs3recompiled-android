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

/* sub_432690: native, nfs3hp::collide::subdivisionDepth */

/* sub_432720: native, nfs3hp::render::subdivideQuad */

/* sub_433060: native, nfs3hp::render::quadSubdivided */

/* sub_4332b0: native, nfs3hp::render::quadRecords */

/* sub_433530: native, nfs3hp::collide::drawTexturedTriangles */

/* sub_433660: native, nfs3hp::collide::drawFlatTriangles */

/* sub_4336e0: native, nfs3hp::collide::drawTrianglesByZ */

/* sub_433840: native, nfs3hp::collide::drawQuadsByZ */

/* sub_4339d0: native, nfs3hp::collide::drawFlatTrianglesAgain */

/* sub_433a50: native, nfs3hp::vertices::triangleList */

/* sub_433bb0: native, nfs3hp::vertices::quadList */

/* sub_433d40: native, nfs3hp::graphics::drawColouredQuadRecord */

/* sub_433e30: native, nfs3hp::render::colouredTriangles */

/* sub_434120: native, nfs3hp::render::triangleRecords */

/* sub_434380: native, nfs3hp::vertices::submitPolygons */

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

/* sub_4347b0: native, nfs3hp::collide::drawColouredTriangles */

/* sub_4347d0: native, nfs3hp::graphics::drawLineRecord */

/* sub_434850: native, nfs3hp::collide::stateRecord */

/* sub_434870: native, nfs3hp::render::polygonDrawers */

/* sub_434950: native, nfs3hp::collide::drawRecords */

/* sub_434990: native, nfs3hp::collide::raceTextFrame */

/* sub_4349a0: native, nfs3hp::collide::setMirrored */

/* sub_4349d0: native, nfs3hp::collide::drawMirroredRecords */

/* sub_434a00: native, nfs3hp::graphics::endFrame */

/* sub_434a70: native, nfs3hp::collide::countFrame */

/* sub_434a80: native, nfs3hp::collide::raceViewDistance */

/* sub_434a90: native, nfs3hp::collide::raceFrameEnd */

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

/* sub_434ae0: native, nfs3hp::collide::raceFrameNothing */

/* sub_434af0: native, nfs3hp::collide::raceEndNothing */

/* sub_434b00: native, nfs3hp::collide::raceStartDrawing */

/* sub_434b10: native, nfs3hp::collide::raceStartNothing */

/* sub_434b20: native, nfs3hp::graphics::syncWindow */

/* sub_434b40: native, nfs3hp::graphics::flushAndFlip */

/* sub_434b60: native, nfs3hp::collide::drawPointer */

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

/* sub_436c40: native, nfs3hp::collide::openMessages */

/* sub_436cf0: native, nfs3hp::collide::closeMessages */

/* sub_436d40: native, nfs3hp::collide::clearAllMessages */

/* sub_436d60: native, nfs3hp::collide::clearMessages */

/* sub_436dc0: native, nfs3hp::collide::clearMessageLine */

/* sub_436e10: native, nfs3hp::collide::addMessageText */

/* sub_436e90: native, nfs3hp::collide::addMessageCharacter */

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
    nfs3hp::collide::messagesScrolled(app, cpu.sync());
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

/* sub_437080: native, nfs3hp::collide::copyMessageLines */

/* sub_4371a0: native, nfs3hp::collide::messagesScrolled */

/* sub_4371c0: native, nfs3hp::collide::messagesNothing */

/* sub_4371d0: native, nfs3hp::collide::seedHash */

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
