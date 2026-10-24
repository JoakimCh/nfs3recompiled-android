#include "nfs3hp.h"
#include <lib/thread.h>

namespace nfs3hp
{
// Port (tools/apply_native_vertices.py): defined in native_vertices.cpp.
bool unitVector(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_vertices.py): defined in native_vertices.cpp.
bool vectorLengthOf(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_vertices.py): defined in native_vertices.cpp.
bool subtractVectors(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_vertices.py): defined in native_vertices.cpp.
bool addVectors(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_vertices.py): defined in native_vertices.cpp.
bool scaleVectors(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_vertices.py): defined in native_vertices.cpp.
bool dotPush(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_vertices.py): defined in native_vertices.cpp.
bool transformPoints(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_vertices.py): defined in native_vertices.cpp.
bool multiplyMatrices(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_vertices.py): defined in native_vertices.cpp.
bool dotProducts(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_vertices.py): defined in native_vertices.cpp.
bool rotateVectors(win32::WinApplication* app, x86::CPU& cpu);

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x54 0x22 0x00 */
void Application::sub_4df310(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004df310  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004df311  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004df312  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004df313  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004df314  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004df316  e865c70000             -call 0x4eba80
    cpu.esp -= 4;
    sub_4eba80(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004df31b  3b05c0a28c00           +cmp eax, dword ptr [0x8ca2c0]
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(9216704) /* 0x8ca2c0 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004df321  7518                   -jne 0x4df33b
    if (!cpu.flags.zf)
    {
        goto L_0x004df33b;
    }
    // 004df323  8b0dc8a28c00           -mov ecx, dword ptr [0x8ca2c8]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(9216712) /* 0x8ca2c8 */);
    // 004df329  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    // 004df32b  740e                   -je 0x4df33b
    if (cpu.flags.zf)
    {
        goto L_0x004df33b;
    }
    // 004df32d  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004df32e  8b11                   -mov edx, dword ptr [ecx]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ecx);
    // 004df330  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
    // 004df332  ff5208                 -call dword ptr [edx + 8]
    cpu.ip = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(8) /* 0x8 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004df335  891dc8a28c00           -mov dword ptr [0x8ca2c8], ebx
    app->getMemory<x86::reg32>(x86::reg32(9216712) /* 0x8ca2c8 */) = cpu.ebx;
L_0x004df33b:
    // 004df33b  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df33c  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df33d  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df33e  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df33f  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip  */
void Application::sub_4df340(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004df340  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004df341  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004df343  a1d4a28c00             -mov eax, dword ptr [0x8ca2d4]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(9216724) /* 0x8ca2d4 */);
    // 004df348  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df349  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x00 0x00 0x00 0x00 0x00 0x00 */
void Application::sub_4df350(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004df350  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004df351  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004df352  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004df353  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004df355  8b1550435600           -mov edx, dword ptr [0x564350]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5653328) /* 0x564350 */);
L_0x004df35b:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004df35b  8b0a                   -mov ecx, dword ptr [edx]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.edx);
    // 004df35d  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004df35f  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    // 004df361  7412                   -je 0x4df375
    if (cpu.flags.zf)
    {
        goto L_0x004df375;
    }
    // 004df363  83c20c                 -add edx, 0xc
    (cpu.edx) += x86::reg32(x86::sreg32(12 /*0xc*/));
    // 004df366  81fa6ff29e00           +cmp edx, 0x9ef26f
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(10416751 /*0x9ef26f*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004df36c  76ed                   -jbe 0x4df35b
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x004df35b;
    }
    // 004df36e  baf0a28c00             -mov edx, 0x8ca2f0
    cpu.edx = 9216752 /*0x8ca2f0*/;
    // 004df373  ebe6                   -jmp 0x4df35b
    goto L_0x004df35b;
L_0x004df375:
    // 004df375  891550435600           -mov dword ptr [0x564350], edx
    app->getMemory<x86::reg32>(x86::reg32(5653328) /* 0x564350 */) = cpu.edx;
    // 004df37b  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df37c  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df37d  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df37e  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x90 */
void Application::sub_4df380(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004df380  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004df381  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004df383  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 004df388  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df389  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 */
void Application::sub_4df390(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004df390  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004df391  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004df393  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df394  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 0x8b 0xdb */
void Application::sub_4df3a0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004df3a0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004df3a1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004df3a2  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004df3a3  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004df3a4  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004df3a5  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004df3a7  83ec0c                 -sub esp, 0xc
    (cpu.esp) -= x86::reg32(x86::sreg32(12 /*0xc*/));
    // 004df3aa  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 004df3ac  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
    // 004df3ae  895df4                 -mov dword ptr [ebp - 0xc], ebx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.ebx;
    // 004df3b1  895df8                 -mov dword ptr [ebp - 8], ebx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.ebx;
    // 004df3b4  833d4843560000         +cmp dword ptr [0x564348], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5653320) /* 0x564348 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004df3bb  7454                   -je 0x4df411
    if (cpu.flags.zf)
    {
        goto L_0x004df411;
    }
    // 004df3bd  a370f29e00             -mov dword ptr [0x9ef270], eax
    app->getMemory<x86::reg32>(x86::reg32(10416752) /* 0x9ef270 */) = cpu.eax;
    // 004df3c2  891574f29e00           -mov dword ptr [0x9ef274], edx
    app->getMemory<x86::reg32>(x86::reg32(10416756) /* 0x9ef274 */) = cpu.edx;
    // 004df3c8  e883ffffff             -call 0x4df350
    cpu.esp -= 4;
    sub_4df350(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004df3cd  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 004df3d0  a174f29e00             -mov eax, dword ptr [0x9ef274]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(10416756) /* 0x9ef274 */);
    // 004df3d5  8b55fc                 -mov edx, dword ptr [ebp - 4]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004df3d8  8950fc                 -mov dword ptr [eax - 4], edx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(-4) /* -0x4 */) = cpu.edx;
    // 004df3db  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 004df3dd  7432                   -je 0x4df411
    if (cpu.flags.zf)
    {
        goto L_0x004df411;
    }
    // 004df3df  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004df3e2  8b154c435600           -mov edx, dword ptr [0x56434c]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5653324) /* 0x56434c */);
    // 004df3e8  83e904                 -sub ecx, 4
    (cpu.ecx) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 004df3eb  42                     -inc edx
    (cpu.edx)++;
    // 004df3ec  8908                   -mov dword ptr [eax], ecx
    app->getMemory<x86::reg32>(cpu.eax) = cpu.ecx;
    // 004df3ee  89154c435600           -mov dword ptr [0x56434c], edx
    app->getMemory<x86::reg32>(x86::reg32(5653324) /* 0x56434c */) = cpu.edx;
    // 004df3f4  0f31                   -rdtsc 
    cpu.rdtsc();
    // 004df3f6  8995f4ffffff           -mov dword ptr [ebp - 0xc], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.edx;
    // 004df3fc  8985f8ffffff           -mov dword ptr [ebp - 8], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.eax;
    // 004df402  8b45f4                 -mov eax, dword ptr [ebp - 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 004df405  8b55fc                 -mov edx, dword ptr [ebp - 4]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004df408  894204                 -mov dword ptr [edx + 4], eax
    app->getMemory<x86::reg32>(cpu.edx + x86::reg32(4) /* 0x4 */) = cpu.eax;
    // 004df40b  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004df40e  894208                 -mov dword ptr [edx + 8], eax
    app->getMemory<x86::reg32>(cpu.edx + x86::reg32(8) /* 0x8 */) = cpu.eax;
L_0x004df411:
    // 004df411  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004df413  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df414  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df415  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df416  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df417  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df418  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x90 */
void Application::sub_4df420(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004df420  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004df421  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004df422  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004df423  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004df424  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004df425  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004df426  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004df428  83ec18                 -sub esp, 0x18
    (cpu.esp) -= x86::reg32(x86::sreg32(24 /*0x18*/));
    // 004df42b  83e804                 -sub eax, 4
    (cpu.eax) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 004df42e  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 004df430  8945f8                 -mov dword ptr [ebp - 8], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.eax;
    // 004df433  8955e8                 -mov dword ptr [ebp - 0x18], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-24) /* -0x18 */) = cpu.edx;
    // 004df436  8955ec                 -mov dword ptr [ebp - 0x14], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */) = cpu.edx;
    // 004df439  0f31                   -rdtsc 
    cpu.rdtsc();
    // 004df43b  8995e8ffffff           -mov dword ptr [ebp - 0x18], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-24) /* -0x18 */) = cpu.edx;
    // 004df441  8985ecffffff           -mov dword ptr [ebp - 0x14], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */) = cpu.eax;
    // 004df447  833d4843560000         +cmp dword ptr [0x564348], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5653320) /* 0x564348 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004df44e  0f84ce000000           -je 0x4df522
    if (cpu.flags.zf)
    {
        goto L_0x004df522;
    }
    // 004df454  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004df457  8b00                   -mov eax, dword ptr [eax]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax);
    // 004df459  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 004df45c  8b4004                 -mov eax, dword ptr [eax + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 004df45f  8945f0                 -mov dword ptr [ebp - 0x10], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = cpu.eax;
    // 004df462  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004df465  8b4008                 -mov eax, dword ptr [eax + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 004df468  8945f4                 -mov dword ptr [ebp - 0xc], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.eax;
    // 004df46b  8b85ecffffff           -mov eax, dword ptr [ebp - 0x14]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */);
    // 004df471  8b95e8ffffff           -mov edx, dword ptr [ebp - 0x18]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-24) /* -0x18 */);
    // 004df477  2b85f4ffffff           +sub eax, dword ptr [ebp - 0xc]
    {
        x86::reg32& tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 004df47d  1b95f0ffffff           -sbb edx, dword ptr [ebp - 0x10]
    (cpu.edx) -= x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */)) + cpu.flags.cf);
    // 004df483  8985f4ffffff           -mov dword ptr [ebp - 0xc], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.eax;
    // 004df489  8995f0ffffff           -mov dword ptr [ebp - 0x10], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = cpu.edx;
    // 004df48f  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004df492  8b08                   -mov ecx, dword ptr [eax]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax);
    // 004df494  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 004df496  8a01                   -mov al, byte ptr [ecx]
    cpu.al = app->getMemory<x86::reg8>(cpu.ecx);
    // 004df498  88c2                   -mov dl, al
    cpu.dl = cpu.al;
    // 004df49a  29d1                   -sub ecx, edx
    (cpu.ecx) -= x86::reg32(x86::sreg32(cpu.edx));
    // 004df49c  ba78f49e00             -mov edx, 0x9ef478
    cpu.edx = 10417272 /*0x9ef478*/;
L_0x004df4a1:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004df4a1  fec8                   -dec al
    (cpu.al)--;
    // 004df4a3  3cff                   +cmp al, 0xff
    {
        x86::reg8 tmp1 = cpu.al;
        x86::reg8 tmp2 = x86::reg8(x86::sreg8(255 /*0xff*/));
        x86::reg8 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 7);
        cpu.flags.of ^= 1 & (result >> 7);
        cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
        cpu.set_szp(result);
    }
    // 004df4a5  7409                   -je 0x4df4b0
    if (cpu.flags.zf)
    {
        goto L_0x004df4b0;
    }
    // 004df4a7  42                     +inc edx
    {
        x86::reg32& tmp = cpu.edx;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 004df4a8  8a21                   -mov ah, byte ptr [ecx]
    cpu.ah = app->getMemory<x86::reg8>(cpu.ecx);
    // 004df4aa  41                     +inc ecx
    {
        x86::reg32& tmp = cpu.ecx;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 004df4ab  8862ff                 -mov byte ptr [edx - 1], ah
    app->getMemory<x86::reg8>(cpu.edx + x86::reg32(-1) /* -0x1 */) = cpu.ah;
    // 004df4ae  ebf1                   -jmp 0x4df4a1
    goto L_0x004df4a1;
L_0x004df4b0:
    // 004df4b0  b878f39e00             -mov eax, 0x9ef378
    cpu.eax = 10417016 /*0x9ef378*/;
    // 004df4b5  c60200                 -mov byte ptr [edx], 0
    app->getMemory<x86::reg8>(cpu.edx) = 0 /*0x0*/;
    // 004df4b8  ba34985400             -mov edx, 0x549834
    cpu.edx = 5543988 /*0x549834*/;
    // 004df4bd  e826eb0000             -call 0x4edfe8
    cpu.esp -= 4;
    nfs3hp::watcom::fopen(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004df4c2  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004df4c4  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004df4c6  7444                   -je 0x4df50c
    if (cpu.flags.zf)
    {
        goto L_0x004df50c;
    }
    // 004df4c8  30db                   -xor bl, bl
    cpu.bl ^= x86::reg8(x86::sreg8(cpu.bl));
L_0x004df4ca:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004df4ca  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 004df4cc  8b354c435600           -mov esi, dword ptr [0x56434c]
    cpu.esi = app->getMemory<x86::reg32>(x86::reg32(5653324) /* 0x56434c */);
    // 004df4d2  88d8                   -mov al, bl
    cpu.al = cpu.bl;
    // 004df4d4  39f0                   +cmp eax, esi
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.esi));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004df4d6  7d12                   -jge 0x4df4ea
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004df4ea;
    }
    // 004df4d8  6838985400             -push 0x549838
    app->getMemory<x86::reg32>(cpu.esp-4) = 5543992 /*0x549838*/;
    cpu.esp -= 4;
    // 004df4dd  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004df4de  fec3                   -inc bl
    (cpu.bl)++;
    // 004df4e0  e89b560100             -call 0x4f4b80
    cpu.esp -= 4;
    nfs3hp::watcom::fprintf(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004df4e5  83c408                 +add esp, 8
    {
        x86::reg32& tmp1 = cpu.esp;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(8 /*0x8*/));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 004df4e8  ebe0                   -jmp 0x4df4ca
    goto L_0x004df4ca;
L_0x004df4ea:
    // 004df4ea  8b45f4                 -mov eax, dword ptr [ebp - 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 004df4ed  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004df4ee  8b45f0                 -mov eax, dword ptr [ebp - 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 004df4f1  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004df4f2  6878f49e00             -push 0x9ef478
    app->getMemory<x86::reg32>(cpu.esp-4) = 10417272 /*0x9ef478*/;
    cpu.esp -= 4;
    // 004df4f7  683c985400             -push 0x54983c
    app->getMemory<x86::reg32>(cpu.esp-4) = 5543996 /*0x54983c*/;
    cpu.esp -= 4;
    // 004df4fc  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004df4fd  e87e560100             -call 0x4f4b80
    cpu.esp -= 4;
    nfs3hp::watcom::fprintf(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004df502  83c414                 -add esp, 0x14
    (cpu.esp) += x86::reg32(x86::sreg32(20 /*0x14*/));
    // 004df505  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004df507  e8f4eb0000             -call 0x4ee100
    cpu.esp -= 4;
    nfs3hp::watcom::fclose(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x004df50c:
    // 004df50c  8b3d4c435600           -mov edi, dword ptr [0x56434c]
    cpu.edi = app->getMemory<x86::reg32>(x86::reg32(5653324) /* 0x56434c */);
    // 004df512  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004df515  4f                     -dec edi
    (cpu.edi)--;
    // 004df516  c70000000000           -mov dword ptr [eax], 0
    app->getMemory<x86::reg32>(cpu.eax) = 0 /*0x0*/;
    // 004df51c  893d4c435600           -mov dword ptr [0x56434c], edi
    app->getMemory<x86::reg32>(x86::reg32(5653324) /* 0x56434c */) = cpu.edi;
L_0x004df522:
    // 004df522  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004df524  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df525  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df526  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df527  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df528  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df529  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df52a  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x40 0x00 0x8b 0xc9 */
void Application::sub_4df530(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004df530  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004df531  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004df532  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004df533  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004df535  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
L_0x004df537:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004df537  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004df538  6848985400             -push 0x549848
    app->getMemory<x86::reg32>(cpu.esp-4) = 5544008 /*0x549848*/;
    cpu.esp -= 4;
    // 004df53d  6878f39e00             -push 0x9ef378
    app->getMemory<x86::reg32>(cpu.esp-4) = 10417016 /*0x9ef378*/;
    cpu.esp -= 4;
    // 004df542  e849010000             -call 0x4df690
    cpu.esp -= 4;
    nfs3hp::watcom::sprintf(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004df547  83c40c                 -add esp, 0xc
    (cpu.esp) += x86::reg32(x86::sreg32(12 /*0xc*/));
    // 004df54a  ba54985400             -mov edx, 0x549854
    cpu.edx = 5544020 /*0x549854*/;
    // 004df54f  b878f39e00             -mov eax, 0x9ef378
    cpu.eax = 10417016 /*0x9ef378*/;
    // 004df554  e88fea0000             -call 0x4edfe8
    cpu.esp -= 4;
    nfs3hp::watcom::fopen(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004df559  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004df55b  7403                   -je 0x4df560
    if (cpu.flags.zf)
    {
        goto L_0x004df560;
    }
    // 004df55d  41                     +inc ecx
    {
        x86::reg32& tmp = cpu.ecx;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 004df55e  ebd7                   -jmp 0x4df537
    goto L_0x004df537;
L_0x004df560:
    // 004df560  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df561  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df562  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df563  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 */
void Application::sub_4df570(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004df570  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004df571  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004df572  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004df573  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004df574  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004df575  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004df576  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004df578  83ec08                 -sub esp, 8
    (cpu.esp) -= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 004df57b  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 004df57d  8955f8                 -mov dword ptr [ebp - 8], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.edx;
    // 004df580  8955fc                 -mov dword ptr [ebp - 4], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.edx;
    // 004df583  833d4843560000         +cmp dword ptr [0x564348], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5653320) /* 0x564348 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004df58a  7429                   -je 0x4df5b5
    if (cpu.flags.zf)
    {
        goto L_0x004df5b5;
    }
    // 004df58c  e89fffffff             -call 0x4df530
    cpu.esp -= 4;
    sub_4df530(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004df591  ff054c435600           -inc dword ptr [0x56434c]
    (app->getMemory<x86::reg32>(x86::reg32(5653324) /* 0x56434c */))++;
    // 004df597  0f31                   -rdtsc 
    cpu.rdtsc();
    // 004df599  8995f8ffffff           -mov dword ptr [ebp - 8], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.edx;
    // 004df59f  8985fcffffff           -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 004df5a5  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004df5a8  a3a8f59e00             -mov dword ptr [0x9ef5a8], eax
    app->getMemory<x86::reg32>(x86::reg32(10417576) /* 0x9ef5a8 */) = cpu.eax;
    // 004df5ad  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004df5b0  a3acf59e00             -mov dword ptr [0x9ef5ac], eax
    app->getMemory<x86::reg32>(x86::reg32(10417580) /* 0x9ef5ac */) = cpu.eax;
L_0x004df5b5:
    // 004df5b5  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004df5b7  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df5b8  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df5b9  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df5ba  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df5bb  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df5bc  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df5bd  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8b 0xc0 */
void Application::sub_4df5c0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004df5c0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004df5c1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004df5c2  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004df5c3  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004df5c4  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004df5c5  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004df5c6  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004df5c8  83ec10                 -sub esp, 0x10
    (cpu.esp) -= x86::reg32(x86::sreg32(16 /*0x10*/));
    // 004df5cb  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 004df5cd  8955f0                 -mov dword ptr [ebp - 0x10], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = cpu.edx;
    // 004df5d0  8955f4                 -mov dword ptr [ebp - 0xc], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.edx;
    // 004df5d3  0f31                   -rdtsc 
    cpu.rdtsc();
    // 004df5d5  8995f0ffffff           -mov dword ptr [ebp - 0x10], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = cpu.edx;
    // 004df5db  8985f4ffffff           -mov dword ptr [ebp - 0xc], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.eax;
    // 004df5e1  833d4843560000         +cmp dword ptr [0x564348], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5653320) /* 0x564348 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004df5e8  746c                   -je 0x4df656
    if (cpu.flags.zf)
    {
        goto L_0x004df656;
    }
    // 004df5ea  a1a8f59e00             -mov eax, dword ptr [0x9ef5a8]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(10417576) /* 0x9ef5a8 */);
    // 004df5ef  8945f8                 -mov dword ptr [ebp - 8], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.eax;
    // 004df5f2  a1acf59e00             -mov eax, dword ptr [0x9ef5ac]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(10417580) /* 0x9ef5ac */);
    // 004df5f7  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 004df5fa  8b85f4ffffff           -mov eax, dword ptr [ebp - 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 004df600  8b95f0ffffff           -mov edx, dword ptr [ebp - 0x10]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 004df606  2b85fcffffff           +sub eax, dword ptr [ebp - 4]
    {
        x86::reg32& tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 004df60c  1b95f8ffffff           -sbb edx, dword ptr [ebp - 8]
    (cpu.edx) -= x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */)) + cpu.flags.cf);
    // 004df612  8985fcffffff           -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 004df618  8995f8ffffff           -mov dword ptr [ebp - 8], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.edx;
    // 004df61e  ba34985400             -mov edx, 0x549834
    cpu.edx = 5543988 /*0x549834*/;
    // 004df623  b878f39e00             -mov eax, 0x9ef378
    cpu.eax = 10417016 /*0x9ef378*/;
    // 004df628  e8bbe90000             -call 0x4edfe8
    cpu.esp -= 4;
    nfs3hp::watcom::fopen(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004df62d  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004df62f  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004df631  741d                   -je 0x4df650
    if (cpu.flags.zf)
    {
        goto L_0x004df650;
    }
    // 004df633  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004df636  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004df637  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004df63a  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004df63b  6858985400             -push 0x549858
    app->getMemory<x86::reg32>(cpu.esp-4) = 5544024 /*0x549858*/;
    cpu.esp -= 4;
    // 004df640  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004df641  e83a550100             -call 0x4f4b80
    cpu.esp -= 4;
    nfs3hp::watcom::fprintf(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004df646  83c410                 -add esp, 0x10
    (cpu.esp) += x86::reg32(x86::sreg32(16 /*0x10*/));
    // 004df649  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004df64b  e8b0ea0000             -call 0x4ee100
    cpu.esp -= 4;
    nfs3hp::watcom::fclose(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x004df650:
    // 004df650  ff0d4c435600           -dec dword ptr [0x56434c]
    (app->getMemory<x86::reg32>(x86::reg32(5653324) /* 0x56434c */))--;
L_0x004df656:
    // 004df656  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004df658  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df659  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df65a  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df65b  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df65c  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df65d  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df65e  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_4df660: native, nfs3hp::watcom::mem_putc */

/* sub_4df674: native, nfs3hp::watcom::vsprintf */

/* sub_4df690: native, nfs3hp::watcom::sprintf */

/* sub_4df6c0: native, nfs3hp::Message */

/* sub_4df6f0: native, nfs3hp::ea::waitForObjects */

/* sub_4df730: native, nfs3hp::ea::threadStart */

/* sub_4df740: native, nfs3hp::ea::threadsInit */

/* sub_4df7a0: native, nfs3hp::ea::createThread */

/* sub_4df870: native, nfs3hp::ea::removeThread */

/* sub_4df8e0: native, nfs3hp::ea::sleepMs */

/* sub_4df8f0: native, nfs3hp::ea::sleepTicks */

/* sub_4df930: native, nfs3hp::ea::isThread */

/* sub_4df980: native, nfs3hp::ea::threadPriority */

/* sub_4dfa30: native, nfs3hp::ea::setThreadPriority */

/* sub_4dfaf0: native, nfs3hp::ea::exitThread */

/* sub_4dfb00: native, nfs3hp::ea::createEvent */

/* sub_4dfb20: native, nfs3hp::ea::postEvent */

/* sub_4dfb30: native, nfs3hp::ea::signalEvent */

/* sub_4dfb40: native, nfs3hp::ea::pollEvent */

/* sub_4dfb70: native, nfs3hp::ea::waitEvent */

/* sub_4dfb90: native, nfs3hp::ea::waitEventTicks */

/* sub_4dfbf0: native, nfs3hp::ea::waitForAny */

/* sub_4dfc00: native, nfs3hp::ea::closeEvent */

/* sub_4dfc10: native, nfs3hp::ea::createManualEvent */

/* sub_4dfc30: native, nfs3hp::ea::setEvent */

/* sub_4dfc40: native, nfs3hp::ea::resetEvent */

/* sub_4dfc50: native, nfs3hp::ea::pulseEvent */

/* sub_4dfc60: native, nfs3hp::ea::waitManualEvent */

/* sub_4dfc80: native, nfs3hp::ea::setAndCloseEvent */

/* sub_4dfca0: native, nfs3hp::ea::lastErrorText */

/* sub_4dfce0: native, nfs3hp::ea::setLastError */

/* sub_4dfcf0: native, nfs3hp::ea::lastError */

/* sub_4dfd00: native, nfs3hp::ea::doNothing */

/* sub_4dfd04: native, nfs3hp::watcom::exit */

/* sub_4dfd30: native, nfs3hp::watcom::_exit */

/* sub_4dfd56: native, nfs3hp::watcom::CHP */

/* sub_4dfd80: native, nfs3hp::ea::xRotation */

/* sub_4dfde0: native, nfs3hp::ea::yRotation */

/* sub_4dfe40: native, nfs3hp::ea::zRotation */

/* sub_4dfea0: native, nfs3hp::ea::axisRotation */

/* align: skip 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 */
void Application::sub_4dffb0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (addVectors(app, cpu.sync())) /* port: native (tools/apply_native_vertices.py) */
    {
        cpu.reload();
        return;
    }
    // 004dffb0  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004dffb1  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004dffb2  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 004dffb4  89df                   -mov edi, ebx
    cpu.edi = cpu.ebx;
    // 004dffb6  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004dffb8  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 004dffba  7e34                   -jle 0x4dfff0
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004dfff0;
    }
L_0x004dffbc:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004dffbc  89cb                   -mov ebx, ecx
    cpu.ebx = cpu.ecx;
    // 004dffbe  89fa                   -mov edx, edi
    cpu.edx = cpu.edi;
    // 004dffc0  d900                   -fld dword ptr [eax]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.eax));
    // 004dffc2  d802                   -fadd dword ptr [edx]
    x86::Float fpu2 = cpu.fpu.add(fpu1, x86::Float(app->getMemory<float>(cpu.edx)));
    // 004dffc4  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu3 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 004dffc7  d84204                 -fadd dword ptr [edx + 4]
    x86::Float fpu4 = cpu.fpu.add(fpu3, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(4) /* 0x4 */)));
    // 004dffca  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu5 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 004dffcd  d84208                 -fadd dword ptr [edx + 8]
    x86::Float fpu6 = cpu.fpu.add(fpu5, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(8) /* 0x8 */)));
    // 004dffd0  d9ca                   -fxch st(2)
    
    // 004dffd2  8d400c                 -lea eax, [eax + 0xc]
    cpu.eax = x86::reg32(cpu.eax + x86::reg32(12) /* 0xc */);
    // 004dffd5  d91b                   -fstp dword ptr [ebx]
    app->getMemory<float>(cpu.ebx) = float(fpu2);
    // 004dffd7  d95b04                 -fstp dword ptr [ebx + 4]
    app->getMemory<float>(cpu.ebx + x86::reg32(4) /* 0x4 */) = float(fpu4);
    // 004dffda  d95b08                 -fstp dword ptr [ebx + 8]
    app->getMemory<float>(cpu.ebx + x86::reg32(8) /* 0x8 */) = float(fpu6);
    // 004dffdd  83c10c                 +add ecx, 0xc
    {
        x86::reg32& tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(12 /*0xc*/));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 004dffe0  4e                     +dec esi
    {
        x86::reg32& tmp = cpu.esi;
        cpu.flags.of = 1 & (tmp >> 31);
        tmp--;
        cpu.flags.of &= ~(1 & (tmp >> 31));
        cpu.set_szp(tmp);
    }
    }
    // 004dffe1  75d9                   -jne 0x4dffbc
    if (!cpu.flags.zf)
    {
        goto L_0x004dffbc;
    }
    // 004dffe3  8d8000000000           -lea eax, [eax]
    cpu.eax = x86::reg32(cpu.eax);
    // 004dffe9  8d9200000000           -lea edx, [edx]
    cpu.edx = x86::reg32(cpu.edx);
    // 004dffef  90                     -nop 
    ;
L_0x004dfff0:
    // 004dfff0  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dfff1  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dfff2  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x90 */
void Application::sub_4e0000(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (subtractVectors(app, cpu.sync())) /* port: native (tools/apply_native_vertices.py) */
    {
        cpu.reload();
        return;
    }
    // 004e0000  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004e0001  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004e0002  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 004e0004  89df                   -mov edi, ebx
    cpu.edi = cpu.ebx;
    // 004e0006  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004e0008  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 004e000a  7e34                   -jle 0x4e0040
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004e0040;
    }
L_0x004e000c:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004e000c  89cb                   -mov ebx, ecx
    cpu.ebx = cpu.ecx;
    // 004e000e  89fa                   -mov edx, edi
    cpu.edx = cpu.edi;
    // 004e0010  d900                   -fld dword ptr [eax]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.eax));
    // 004e0012  d822                   -fsub dword ptr [edx]
    x86::Float fpu2 = cpu.fpu.sub(fpu1, x86::Float(app->getMemory<float>(cpu.edx)));
    // 004e0014  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu3 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 004e0017  d86204                 -fsub dword ptr [edx + 4]
    x86::Float fpu4 = cpu.fpu.sub(fpu3, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(4) /* 0x4 */)));
    // 004e001a  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu5 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 004e001d  d86208                 -fsub dword ptr [edx + 8]
    x86::Float fpu6 = cpu.fpu.sub(fpu5, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(8) /* 0x8 */)));
    // 004e0020  d9ca                   -fxch st(2)
    
    // 004e0022  8d400c                 -lea eax, [eax + 0xc]
    cpu.eax = x86::reg32(cpu.eax + x86::reg32(12) /* 0xc */);
    // 004e0025  d91b                   -fstp dword ptr [ebx]
    app->getMemory<float>(cpu.ebx) = float(fpu2);
    // 004e0027  d95b04                 -fstp dword ptr [ebx + 4]
    app->getMemory<float>(cpu.ebx + x86::reg32(4) /* 0x4 */) = float(fpu4);
    // 004e002a  d95b08                 -fstp dword ptr [ebx + 8]
    app->getMemory<float>(cpu.ebx + x86::reg32(8) /* 0x8 */) = float(fpu6);
    // 004e002d  83c10c                 +add ecx, 0xc
    {
        x86::reg32& tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(12 /*0xc*/));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 004e0030  4e                     +dec esi
    {
        x86::reg32& tmp = cpu.esi;
        cpu.flags.of = 1 & (tmp >> 31);
        tmp--;
        cpu.flags.of &= ~(1 & (tmp >> 31));
        cpu.set_szp(tmp);
    }
    }
    // 004e0031  75d9                   -jne 0x4e000c
    if (!cpu.flags.zf)
    {
        goto L_0x004e000c;
    }
    // 004e0033  8d8000000000           -lea eax, [eax]
    cpu.eax = x86::reg32(cpu.eax);
    // 004e0039  8d9200000000           -lea edx, [edx]
    cpu.edx = x86::reg32(cpu.edx);
    // 004e003f  90                     -nop 
    ;
L_0x004e0040:
    // 004e0040  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e0041  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e0042  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x90 */
void Application::sub_4e0050(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (scaleVectors(app, cpu.sync())) /* port: native (tools/apply_native_vertices.py) */
    {
        cpu.reload();
        return;
    }
    // 004e0050  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004e0051  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 004e0053  8b44240c               -mov eax, dword ptr [esp + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(12) /* 0xc */);
    // 004e0057  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    // 004e0059  7e25                   -jle 0x4e0080
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004e0080;
    }
    // 004e005b  d9442408               -fld dword ptr [esp + 8]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.esp + x86::reg32(8) /* 0x8 */));
    cpu.fpu.count += 1;
    cpu.fpu.st(0) = fpu1;
    }
L_0x004e005f:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004e005f  d902                   -fld dword ptr [edx]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu2 = x86::Float(app->getMemory<float>(cpu.edx));
    // 004e0061  d8c9                   -fmul st(1)
    x86::Float fpu3 = cpu.fpu.st(0);
    x86::Float fpu4 = cpu.fpu.mul(fpu2, x86::Float(fpu3));
    // 004e0063  d918                   -fstp dword ptr [eax]
    app->getMemory<float>(cpu.eax) = float(fpu4);
    // 004e0065  d94204                 -fld dword ptr [edx + 4]
    x86::Float fpu5 = x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(4) /* 0x4 */));
    // 004e0068  d8c9                   -fmul st(1)
    x86::Float fpu6 = cpu.fpu.mul(fpu5, x86::Float(fpu3));
    // 004e006a  d95804                 -fstp dword ptr [eax + 4]
    app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */) = float(fpu6);
    // 004e006d  d94208                 -fld dword ptr [edx + 8]
    x86::Float fpu7 = x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(8) /* 0x8 */));
    // 004e0070  d8c9                   -fmul st(1)
    x86::Float fpu8 = cpu.fpu.mul(fpu7, x86::Float(fpu3));
    // 004e0072  83c00c                 -add eax, 0xc
    (cpu.eax) += x86::reg32(x86::sreg32(12 /*0xc*/));
    // 004e0075  83c20c                 +add edx, 0xc
    {
        x86::reg32& tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(12 /*0xc*/));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 004e0078  d958fc                 +fstp dword ptr [eax - 4]
    app->getMemory<float>(cpu.eax + x86::reg32(-4) /* -0x4 */) = float(fpu8);
    // 004e007b  49                     +dec ecx
    {
        x86::reg32& tmp = cpu.ecx;
        cpu.flags.of = 1 & (tmp >> 31);
        tmp--;
        cpu.flags.of &= ~(1 & (tmp >> 31));
        cpu.set_szp(tmp);
    }
    }
    // 004e007c  75e1                   -jne 0x4e005f
    if (!cpu.flags.zf)
    {
        goto L_0x004e005f;
    }
    // 004e007e  ddd8                   -fstp st(0)
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu9 = cpu.fpu.st(0);
    x86::Float fpu10 = x86::Float(fpu9);
    cpu.fpu.count -= 1;
    }
L_0x004e0080:
    // 004e0080  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e0081  c20800                 -ret 8
    cpu.esp += 4+8 /*0x8*/;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 */
void Application::sub_4e0090(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004e0090  83ec0c                 -sub esp, 0xc
    (cpu.esp) -= x86::reg32(x86::sreg32(12 /*0xc*/));
    // 004e0093  d902                   -fld dword ptr [edx]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.edx));
    // 004e0095  d820                   -fsub dword ptr [eax]
    x86::Float fpu2 = cpu.fpu.sub(fpu1, x86::Float(app->getMemory<float>(cpu.eax)));
    // 004e0097  d91c24                 -fstp dword ptr [esp]
    app->getMemory<float>(cpu.esp) = float(fpu2);
    // 004e009a  d94204                 -fld dword ptr [edx + 4]
    x86::Float fpu3 = x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(4) /* 0x4 */));
    // 004e009d  d86004                 -fsub dword ptr [eax + 4]
    x86::Float fpu4 = cpu.fpu.sub(fpu3, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */)));
    // 004e00a0  d95c2404               -fstp dword ptr [esp + 4]
    app->getMemory<float>(cpu.esp + x86::reg32(4) /* 0x4 */) = float(fpu4);
    // 004e00a4  d94208                 -fld dword ptr [edx + 8]
    x86::Float fpu5 = x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(8) /* 0x8 */));
    // 004e00a7  d86008                 -fsub dword ptr [eax + 8]
    x86::Float fpu6 = cpu.fpu.sub(fpu5, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */)));
    // 004e00aa  89e0                   -mov eax, esp
    cpu.eax = cpu.esp;
    // 004e00ac  d95c2408               -fstp dword ptr [esp + 8]
    app->getMemory<float>(cpu.esp + x86::reg32(8) /* 0x8 */) = float(fpu6);
    }
    // 004e00b0  e8eb050000             -call 0x4e06a0
    cpu.esp -= 4;
    sub_4e06a0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e00b5  83c40c                 -add esp, 0xc
    (cpu.esp) += x86::reg32(x86::sreg32(12 /*0xc*/));
    // 004e00b8  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x00 0x00 0x00 0x00 0x00 0x00 0x00 */
void Application::sub_4e00c0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004e00c0  d900                   -fld dword ptr [eax]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.eax));
    // 004e00c2  d80a                   -fmul dword ptr [edx]
    x86::Float fpu2 = cpu.fpu.mul(fpu1, x86::Float(app->getMemory<float>(cpu.edx)));
    // 004e00c4  d91b                   -fstp dword ptr [ebx]
    app->getMemory<float>(cpu.ebx) = float(fpu2);
    // 004e00c6  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu3 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 004e00c9  d80a                   -fmul dword ptr [edx]
    x86::Float fpu4 = cpu.fpu.mul(fpu3, x86::Float(app->getMemory<float>(cpu.edx)));
    // 004e00cb  d95b04                 -fstp dword ptr [ebx + 4]
    app->getMemory<float>(cpu.ebx + x86::reg32(4) /* 0x4 */) = float(fpu4);
    // 004e00ce  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu5 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 004e00d1  d80a                   -fmul dword ptr [edx]
    x86::Float fpu6 = cpu.fpu.mul(fpu5, x86::Float(app->getMemory<float>(cpu.edx)));
    // 004e00d3  d95b08                 -fstp dword ptr [ebx + 8]
    app->getMemory<float>(cpu.ebx + x86::reg32(8) /* 0x8 */) = float(fpu6);
    // 004e00d6  d9400c                 -fld dword ptr [eax + 0xc]
    x86::Float fpu7 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(12) /* 0xc */));
    // 004e00d9  d84a04                 -fmul dword ptr [edx + 4]
    x86::Float fpu8 = cpu.fpu.mul(fpu7, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(4) /* 0x4 */)));
    // 004e00dc  d95b0c                 -fstp dword ptr [ebx + 0xc]
    app->getMemory<float>(cpu.ebx + x86::reg32(12) /* 0xc */) = float(fpu8);
    // 004e00df  d94010                 -fld dword ptr [eax + 0x10]
    x86::Float fpu9 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(16) /* 0x10 */));
    // 004e00e2  d84a04                 -fmul dword ptr [edx + 4]
    x86::Float fpu10 = cpu.fpu.mul(fpu9, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(4) /* 0x4 */)));
    // 004e00e5  d95b10                 -fstp dword ptr [ebx + 0x10]
    app->getMemory<float>(cpu.ebx + x86::reg32(16) /* 0x10 */) = float(fpu10);
    // 004e00e8  d94014                 -fld dword ptr [eax + 0x14]
    x86::Float fpu11 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(20) /* 0x14 */));
    // 004e00eb  d84a04                 -fmul dword ptr [edx + 4]
    x86::Float fpu12 = cpu.fpu.mul(fpu11, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(4) /* 0x4 */)));
    // 004e00ee  d95b14                 -fstp dword ptr [ebx + 0x14]
    app->getMemory<float>(cpu.ebx + x86::reg32(20) /* 0x14 */) = float(fpu12);
    // 004e00f1  d94018                 -fld dword ptr [eax + 0x18]
    x86::Float fpu13 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(24) /* 0x18 */));
    // 004e00f4  d84a08                 -fmul dword ptr [edx + 8]
    x86::Float fpu14 = cpu.fpu.mul(fpu13, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(8) /* 0x8 */)));
    // 004e00f7  d95b18                 -fstp dword ptr [ebx + 0x18]
    app->getMemory<float>(cpu.ebx + x86::reg32(24) /* 0x18 */) = float(fpu14);
    // 004e00fa  d9401c                 -fld dword ptr [eax + 0x1c]
    x86::Float fpu15 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(28) /* 0x1c */));
    // 004e00fd  d84a08                 -fmul dword ptr [edx + 8]
    x86::Float fpu16 = cpu.fpu.mul(fpu15, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(8) /* 0x8 */)));
    // 004e0100  d95b1c                 -fstp dword ptr [ebx + 0x1c]
    app->getMemory<float>(cpu.ebx + x86::reg32(28) /* 0x1c */) = float(fpu16);
    // 004e0103  d94020                 -fld dword ptr [eax + 0x20]
    x86::Float fpu17 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(32) /* 0x20 */));
    // 004e0106  d84a08                 -fmul dword ptr [edx + 8]
    x86::Float fpu18 = cpu.fpu.mul(fpu17, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(8) /* 0x8 */)));
    // 004e0109  d95b20                 -fstp dword ptr [ebx + 0x20]
    app->getMemory<float>(cpu.ebx + x86::reg32(32) /* 0x20 */) = float(fpu18);
    }
    // 004e010c  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x40 0x00 */
void Application::sub_4e0110(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004e0110  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004e0111  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 004e0114  8b08                   -mov ecx, dword ptr [eax]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax);
    // 004e0116  890a                   -mov dword ptr [edx], ecx
    app->getMemory<x86::reg32>(cpu.edx) = cpu.ecx;
    // 004e0118  8b4810                 -mov ecx, dword ptr [eax + 0x10]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(16) /* 0x10 */);
    // 004e011b  894a10                 -mov dword ptr [edx + 0x10], ecx
    app->getMemory<x86::reg32>(cpu.edx + x86::reg32(16) /* 0x10 */) = cpu.ecx;
    // 004e011e  8b4820                 -mov ecx, dword ptr [eax + 0x20]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(32) /* 0x20 */);
    // 004e0121  894a20                 -mov dword ptr [edx + 0x20], ecx
    app->getMemory<x86::reg32>(cpu.edx + x86::reg32(32) /* 0x20 */) = cpu.ecx;
    // 004e0124  d9400c                 -fld dword ptr [eax + 0xc]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(12) /* 0xc */));
    // 004e0127  8b4804                 -mov ecx, dword ptr [eax + 4]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 004e012a  d95a04                 -fstp dword ptr [edx + 4]
    app->getMemory<float>(cpu.edx + x86::reg32(4) /* 0x4 */) = float(fpu1);
    // 004e012d  894a0c                 -mov dword ptr [edx + 0xc], ecx
    app->getMemory<x86::reg32>(cpu.edx + x86::reg32(12) /* 0xc */) = cpu.ecx;
    // 004e0130  890c24                 -mov dword ptr [esp], ecx
    app->getMemory<x86::reg32>(cpu.esp) = cpu.ecx;
    // 004e0133  d94018                 -fld dword ptr [eax + 0x18]
    x86::Float fpu2 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(24) /* 0x18 */));
    // 004e0136  8b4808                 -mov ecx, dword ptr [eax + 8]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 004e0139  d95a08                 -fstp dword ptr [edx + 8]
    app->getMemory<float>(cpu.edx + x86::reg32(8) /* 0x8 */) = float(fpu2);
    // 004e013c  894a18                 -mov dword ptr [edx + 0x18], ecx
    app->getMemory<x86::reg32>(cpu.edx + x86::reg32(24) /* 0x18 */) = cpu.ecx;
    // 004e013f  890c24                 -mov dword ptr [esp], ecx
    app->getMemory<x86::reg32>(cpu.esp) = cpu.ecx;
    // 004e0142  d9401c                 -fld dword ptr [eax + 0x1c]
    x86::Float fpu3 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(28) /* 0x1c */));
    // 004e0145  8b4814                 -mov ecx, dword ptr [eax + 0x14]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */);
    // 004e0148  d95a14                 -fstp dword ptr [edx + 0x14]
    app->getMemory<float>(cpu.edx + x86::reg32(20) /* 0x14 */) = float(fpu3);
    // 004e014b  890c24                 -mov dword ptr [esp], ecx
    app->getMemory<x86::reg32>(cpu.esp) = cpu.ecx;
    // 004e014e  894a1c                 -mov dword ptr [edx + 0x1c], ecx
    app->getMemory<x86::reg32>(cpu.edx + x86::reg32(28) /* 0x1c */) = cpu.ecx;
    // 004e0151  83c404                 -add esp, 4
    (cpu.esp) += x86::reg32(x86::sreg32(4 /*0x4*/));
    // 004e0154  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    }
    // 004e0155  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 */
void Application::sub_4e0160(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004e0160  d94004                 -fld dword ptr [eax + 4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 004e0163  d84a08                 -fmul dword ptr [edx + 8]
    x86::Float fpu2 = cpu.fpu.mul(fpu1, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(8) /* 0x8 */)));
    // 004e0166  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu3 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 004e0169  d80a                   -fmul dword ptr [edx]
    x86::Float fpu4 = cpu.fpu.mul(fpu3, x86::Float(app->getMemory<float>(cpu.edx)));
    // 004e016b  d900                   -fld dword ptr [eax]
    x86::Float fpu5 = x86::Float(app->getMemory<float>(cpu.eax));
    // 004e016d  d84a04                 -fmul dword ptr [edx + 4]
    x86::Float fpu6 = cpu.fpu.mul(fpu5, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(4) /* 0x4 */)));
    // 004e0170  d9ca                   -fxch st(2)
    
    // 004e0172  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu7 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 004e0175  d84a04                 -fmul dword ptr [edx + 4]
    x86::Float fpu8 = cpu.fpu.mul(fpu7, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(4) /* 0x4 */)));
    // 004e0178  d900                   -fld dword ptr [eax]
    x86::Float fpu9 = x86::Float(app->getMemory<float>(cpu.eax));
    // 004e017a  d84a08                 -fmul dword ptr [edx + 8]
    x86::Float fpu10 = cpu.fpu.mul(fpu9, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(8) /* 0x8 */)));
    // 004e017d  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu11 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 004e0180  d80a                   -fmul dword ptr [edx]
    x86::Float fpu12 = cpu.fpu.mul(fpu11, x86::Float(app->getMemory<float>(cpu.edx)));
    // 004e0182  d9ca                   -fxch st(2)
    
    // 004e0184  deeb                   -fsubp st(3)
    x86::Float fpu13 = cpu.fpu.sub(fpu2, fpu8);
    // 004e0186  deeb                   -fsubp st(3)
    x86::Float fpu14 = cpu.fpu.sub(fpu4, fpu10);
    // 004e0188  deeb                   -fsubp st(3)
    x86::Float fpu15 = cpu.fpu.sub(fpu6, fpu12);
    // 004e018a  8d400c                 -lea eax, [eax + 0xc]
    cpu.eax = x86::reg32(cpu.eax + x86::reg32(12) /* 0xc */);
    // 004e018d  d91b                   -fstp dword ptr [ebx]
    app->getMemory<float>(cpu.ebx) = float(fpu13);
    // 004e018f  d95b04                 -fstp dword ptr [ebx + 4]
    app->getMemory<float>(cpu.ebx + x86::reg32(4) /* 0x4 */) = float(fpu14);
    // 004e0192  d95b08                 -fstp dword ptr [ebx + 8]
    app->getMemory<float>(cpu.ebx + x86::reg32(8) /* 0x8 */) = float(fpu15);
    }
    // 004e0195  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x54 0x22 0x00 */
void Application::sub_4e01a0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004e01a0  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004e01a1  83ec0c                 -sub esp, 0xc
    (cpu.esp) -= x86::reg32(x86::sreg32(12 /*0xc*/));
    // 004e01a4  89d9                   -mov ecx, ebx
    cpu.ecx = cpu.ebx;
    // 004e01a6  89e3                   -mov ebx, esp
    cpu.ebx = cpu.esp;
    // 004e01a8  e8b3ffffff             -call 0x4e0160
    cpu.esp -= 4;
    sub_4e0160(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e01ad  89e0                   -mov eax, esp
    cpu.eax = cpu.esp;
    // 004e01af  89ca                   -mov edx, ecx
    cpu.edx = cpu.ecx;
    // 004e01b1  e80a000000             -call 0x4e01c0
    cpu.esp -= 4;
    sub_4e01c0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e01b6  83c40c                 -add esp, 0xc
    (cpu.esp) += x86::reg32(x86::sreg32(12 /*0xc*/));
    // 004e01b9  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e01ba  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x40 0x00 0x8b 0xc9 */
void Application::sub_4e01c0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (unitVector(app, cpu.sync())) /* port: native (tools/apply_native_vertices.py) */
    {
        cpu.reload();
        return;
    }
    // 004e01c0  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004e01c1  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 004e01c4  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 004e01c6  e8d5040000             -call 0x4e06a0
    cpu.esp -= 4;
    sub_4e06a0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e01cb  d9e8                   -fld1 
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = 1.0;
    // 004e01cd  d901                   -fld dword ptr [ecx]
    x86::Float fpu2 = x86::Float(app->getMemory<float>(cpu.ecx));
    // 004e01cf  d9c9                   -fxch st(1)
    
    // 004e01d1  def2                   -fdivrp st(2)
    x86::Float fpu3 = cpu.fpu.st(0);
    x86::Float fpu4 = cpu.fpu.div(fpu1, x86::Float(fpu3));
    // 004e01d3  d8c9                   -fmul st(1)
    x86::Float fpu5 = cpu.fpu.mul(fpu2, x86::Float(fpu4));
    // 004e01d5  d91a                   -fstp dword ptr [edx]
    app->getMemory<float>(cpu.edx) = float(fpu5);
    // 004e01d7  d94104                 -fld dword ptr [ecx + 4]
    x86::Float fpu6 = x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(4) /* 0x4 */));
    // 004e01da  d8c9                   -fmul st(1)
    x86::Float fpu7 = cpu.fpu.mul(fpu6, x86::Float(fpu4));
    // 004e01dc  d95a04                 -fstp dword ptr [edx + 4]
    app->getMemory<float>(cpu.edx + x86::reg32(4) /* 0x4 */) = float(fpu7);
    // 004e01df  d84908                 -fmul dword ptr [ecx + 8]
    x86::Float fpu8 = cpu.fpu.mul(fpu4, x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(8) /* 0x8 */)));
    // 004e01e2  d95a08                 -fstp dword ptr [edx + 8]
    app->getMemory<float>(cpu.edx + x86::reg32(8) /* 0x8 */) = float(fpu8);
    // 004e01e5  83c404                 -add esp, 4
    (cpu.esp) += x86::reg32(x86::sreg32(4 /*0x4*/));
    // 004e01e8  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    cpu.fpu.count -= 1;
    }
    // 004e01e9  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 */
void Application::sub_4e01f0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (dotPush(app, cpu.sync())) /* port: native (tools/apply_native_vertices.py) */
    {
        cpu.reload();
        return;
    }
    // 004e01f0  d900                   -fld dword ptr [eax]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.eax));
    // 004e01f2  d80a                   -fmul dword ptr [edx]
    x86::Float fpu2 = cpu.fpu.mul(fpu1, x86::Float(app->getMemory<float>(cpu.edx)));
    // 004e01f4  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu3 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 004e01f7  d84a04                 -fmul dword ptr [edx + 4]
    x86::Float fpu4 = cpu.fpu.mul(fpu3, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(4) /* 0x4 */)));
    // 004e01fa  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu5 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 004e01fd  d84a08                 -fmul dword ptr [edx + 8]
    x86::Float fpu6 = cpu.fpu.mul(fpu5, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(8) /* 0x8 */)));
    // 004e0200  d9ca                   -fxch st(2)
    
    // 004e0202  dec1                   -faddp st(1)
    x86::Float fpu7 = cpu.fpu.add(fpu4, fpu2);
    // 004e0204  dec1                   -faddp st(1)
    x86::Float fpu8 = cpu.fpu.add(fpu6, fpu7);
    cpu.fpu.count += 1;
    cpu.fpu.st(0) = fpu8;
    }
    // 004e0206  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 */
void Application::sub_4e0210(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (dotProducts(app, cpu.sync())) /* port: native (tools/apply_native_vertices.py) */
    {
        cpu.reload();
        return;
    }
    // 004e0210  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004e0211  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004e0212  89c7                   -mov edi, eax
    cpu.edi = cpu.eax;
    // 004e0214  89d6                   -mov esi, edx
    cpu.esi = cpu.edx;
    // 004e0216  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004e0218  7e26                   -jle 0x4e0240
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004e0240;
    }
L_0x004e021a:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004e021a  89da                   -mov edx, ebx
    cpu.edx = cpu.ebx;
    // 004e021c  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004e021e  83c104                 -add ecx, 4
    (cpu.ecx) += x86::reg32(x86::sreg32(4 /*0x4*/));
    // 004e0221  d900                   -fld dword ptr [eax]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.eax));
    // 004e0223  d80a                   -fmul dword ptr [edx]
    x86::Float fpu2 = cpu.fpu.mul(fpu1, x86::Float(app->getMemory<float>(cpu.edx)));
    // 004e0225  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu3 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 004e0228  d84a04                 -fmul dword ptr [edx + 4]
    x86::Float fpu4 = cpu.fpu.mul(fpu3, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(4) /* 0x4 */)));
    // 004e022b  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu5 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 004e022e  d84a08                 -fmul dword ptr [edx + 8]
    x86::Float fpu6 = cpu.fpu.mul(fpu5, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(8) /* 0x8 */)));
    // 004e0231  d9ca                   -fxch st(2)
    
    // 004e0233  dec1                   -faddp st(1)
    x86::Float fpu7 = cpu.fpu.add(fpu4, fpu2);
    // 004e0235  dec1                   -faddp st(1)
    x86::Float fpu8 = cpu.fpu.add(fpu6, fpu7);
    // 004e0237  d959fc                 -fstp dword ptr [ecx - 4]
    app->getMemory<float>(cpu.ecx + x86::reg32(-4) /* -0x4 */) = float(fpu8);
    // 004e023a  83c60c                 +add esi, 0xc
    {
        x86::reg32& tmp1 = cpu.esi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(12 /*0xc*/));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 004e023d  4f                     +dec edi
    {
        x86::reg32& tmp = cpu.edi;
        cpu.flags.of = 1 & (tmp >> 31);
        tmp--;
        cpu.flags.of &= ~(1 & (tmp >> 31));
        cpu.set_szp(tmp);
    }
    }
    // 004e023e  75da                   -jne 0x4e021a
    if (!cpu.flags.zf)
    {
        goto L_0x004e021a;
    }
L_0x004e0240:
    // 004e0240  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e0241  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e0242  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x90 */
void Application::sub_4e0250(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004e0250  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004e0251  83ec0c                 -sub esp, 0xc
    (cpu.esp) -= x86::reg32(x86::sreg32(12 /*0xc*/));
    // 004e0254  89e2                   -mov edx, esp
    cpu.edx = cpu.esp;
    // 004e0256  e865ffffff             -call 0x4e01c0
    cpu.esp -= 4;
    sub_4e01c0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e025b  8b542418               -mov edx, dword ptr [esp + 0x18]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(24) /* 0x18 */);
    // 004e025f  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004e0260  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 004e0265  8d542404               -lea edx, [esp + 4]
    cpu.edx = x86::reg32(cpu.esp + x86::reg32(4) /* 0x4 */);
    // 004e0269  ff742418               -push dword ptr [esp + 0x18]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(24) /* 0x18 */);
    cpu.esp -= 4;
    // 004e026d  e8defdffff             -call 0x4e0050
    cpu.esp -= 4;
    sub_4e0050(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e0272  83c40c                 -add esp, 0xc
    (cpu.esp) += x86::reg32(x86::sreg32(12 /*0xc*/));
    // 004e0275  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e0276  c20800                 -ret 8
    cpu.esp += 4+8 /*0x8*/;
    return;
}

/* align: skip 0x00 0x00 0x00 0x00 0x00 0x00 0x00 */
void Application::sub_4e0280(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (multiplyMatrices(app, cpu.sync())) /* port: native (tools/apply_native_vertices.py) */
    {
        cpu.reload();
        return;
    }
    // 004e0280  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004e0281  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004e0282  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004e0283  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004e0284  83ec2c                 -sub esp, 0x2c
    (cpu.esp) -= x86::reg32(x86::sreg32(44 /*0x2c*/));
    // 004e0287  89442424               -mov dword ptr [esp + 0x24], eax
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(36) /* 0x24 */) = cpu.eax;
    // 004e028b  89d5                   -mov ebp, edx
    cpu.ebp = cpu.edx;
    // 004e028d  895c2428               -mov dword ptr [esp + 0x28], ebx
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(40) /* 0x28 */) = cpu.ebx;
    // 004e0291  39d8                   +cmp eax, ebx
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ebx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004e0293  0f84fd000000           -je 0x4e0396
    if (cpu.flags.zf)
    {
        goto L_0x004e0396;
    }
L_0x004e0299:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004e0299  8b7c2428               -mov edi, dword ptr [esp + 0x28]
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(40) /* 0x28 */);
    // 004e029d  39fd                   +cmp ebp, edi
    {
        x86::reg32 tmp1 = cpu.ebp;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.edi));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004e029f  7513                   -jne 0x4e02b4
    if (!cpu.flags.zf)
    {
        goto L_0x004e02b4;
    }
    // 004e02a1  3b7c2424               +cmp edi, dword ptr [esp + 0x24]
    {
        x86::reg32 tmp1 = cpu.edi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.esp + x86::reg32(36) /* 0x24 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004e02a5  740b                   -je 0x4e02b2
    if (cpu.flags.zf)
    {
        goto L_0x004e02b2;
    }
    // 004e02a7  b909000000             -mov ecx, 9
    cpu.ecx = 9 /*0x9*/;
    // 004e02ac  89e7                   -mov edi, esp
    cpu.edi = cpu.esp;
    // 004e02ae  89ee                   -mov esi, ebp
    cpu.esi = cpu.ebp;
    // 004e02b0  f3a5                   -rep movsd dword ptr es:[edi], dword ptr [esi]
    while (cpu.ecx)
    {
        app->getMemory<x86::reg32>(cpu.ees + cpu.edi) = app->getMemory<x86::reg32>(cpu.esi);
        if (cpu.flags.df)
        {
            cpu.edi -= 4;
            cpu.esi -= 4;
        }
        else
        {
            cpu.edi += 4;
            cpu.esi += 4;
        }
        --cpu.ecx;
    }
L_0x004e02b2:
    // 004e02b2  89e2                   -mov edx, esp
    cpu.edx = cpu.esp;
L_0x004e02b4:
    // 004e02b4  d94004                 -fld dword ptr [eax + 4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 004e02b7  d84a0c                 -fmul dword ptr [edx + 0xc]
    x86::Float fpu2 = cpu.fpu.mul(fpu1, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(12) /* 0xc */)));
    // 004e02ba  d900                   -fld dword ptr [eax]
    x86::Float fpu3 = x86::Float(app->getMemory<float>(cpu.eax));
    // 004e02bc  d80a                   -fmul dword ptr [edx]
    x86::Float fpu4 = cpu.fpu.mul(fpu3, x86::Float(app->getMemory<float>(cpu.edx)));
    // 004e02be  dec1                   -faddp st(1)
    x86::Float fpu5 = cpu.fpu.add(fpu2, fpu4);
    // 004e02c0  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu6 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 004e02c3  d84a18                 -fmul dword ptr [edx + 0x18]
    x86::Float fpu7 = cpu.fpu.mul(fpu6, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(24) /* 0x18 */)));
    // 004e02c6  dec1                   -faddp st(1)
    x86::Float fpu8 = cpu.fpu.add(fpu5, fpu7);
    // 004e02c8  d91b                   -fstp dword ptr [ebx]
    app->getMemory<float>(cpu.ebx) = float(fpu8);
    // 004e02ca  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu9 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 004e02cd  d84a10                 -fmul dword ptr [edx + 0x10]
    x86::Float fpu10 = cpu.fpu.mul(fpu9, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(16) /* 0x10 */)));
    // 004e02d0  d900                   -fld dword ptr [eax]
    x86::Float fpu11 = x86::Float(app->getMemory<float>(cpu.eax));
    // 004e02d2  d84a04                 -fmul dword ptr [edx + 4]
    x86::Float fpu12 = cpu.fpu.mul(fpu11, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(4) /* 0x4 */)));
    // 004e02d5  dec1                   -faddp st(1)
    x86::Float fpu13 = cpu.fpu.add(fpu10, fpu12);
    // 004e02d7  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu14 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 004e02da  d84a1c                 -fmul dword ptr [edx + 0x1c]
    x86::Float fpu15 = cpu.fpu.mul(fpu14, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(28) /* 0x1c */)));
    // 004e02dd  dec1                   -faddp st(1)
    x86::Float fpu16 = cpu.fpu.add(fpu13, fpu15);
    // 004e02df  d95b04                 -fstp dword ptr [ebx + 4]
    app->getMemory<float>(cpu.ebx + x86::reg32(4) /* 0x4 */) = float(fpu16);
    // 004e02e2  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu17 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 004e02e5  d84a14                 -fmul dword ptr [edx + 0x14]
    x86::Float fpu18 = cpu.fpu.mul(fpu17, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(20) /* 0x14 */)));
    // 004e02e8  d900                   -fld dword ptr [eax]
    x86::Float fpu19 = x86::Float(app->getMemory<float>(cpu.eax));
    // 004e02ea  d84a08                 -fmul dword ptr [edx + 8]
    x86::Float fpu20 = cpu.fpu.mul(fpu19, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(8) /* 0x8 */)));
    // 004e02ed  dec1                   -faddp st(1)
    x86::Float fpu21 = cpu.fpu.add(fpu18, fpu20);
    // 004e02ef  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu22 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 004e02f2  d84a20                 -fmul dword ptr [edx + 0x20]
    x86::Float fpu23 = cpu.fpu.mul(fpu22, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(32) /* 0x20 */)));
    // 004e02f5  dec1                   -faddp st(1)
    x86::Float fpu24 = cpu.fpu.add(fpu21, fpu23);
    // 004e02f7  d95b08                 -fstp dword ptr [ebx + 8]
    app->getMemory<float>(cpu.ebx + x86::reg32(8) /* 0x8 */) = float(fpu24);
    // 004e02fa  d94010                 -fld dword ptr [eax + 0x10]
    x86::Float fpu25 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(16) /* 0x10 */));
    // 004e02fd  d84a0c                 -fmul dword ptr [edx + 0xc]
    x86::Float fpu26 = cpu.fpu.mul(fpu25, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(12) /* 0xc */)));
    // 004e0300  d9400c                 -fld dword ptr [eax + 0xc]
    x86::Float fpu27 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(12) /* 0xc */));
    // 004e0303  d80a                   -fmul dword ptr [edx]
    x86::Float fpu28 = cpu.fpu.mul(fpu27, x86::Float(app->getMemory<float>(cpu.edx)));
    // 004e0305  dec1                   -faddp st(1)
    x86::Float fpu29 = cpu.fpu.add(fpu26, fpu28);
    // 004e0307  d94014                 -fld dword ptr [eax + 0x14]
    x86::Float fpu30 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(20) /* 0x14 */));
    // 004e030a  d84a18                 -fmul dword ptr [edx + 0x18]
    x86::Float fpu31 = cpu.fpu.mul(fpu30, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(24) /* 0x18 */)));
    // 004e030d  dec1                   -faddp st(1)
    x86::Float fpu32 = cpu.fpu.add(fpu29, fpu31);
    // 004e030f  d95b0c                 -fstp dword ptr [ebx + 0xc]
    app->getMemory<float>(cpu.ebx + x86::reg32(12) /* 0xc */) = float(fpu32);
    // 004e0312  d9400c                 -fld dword ptr [eax + 0xc]
    x86::Float fpu33 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(12) /* 0xc */));
    // 004e0315  d84a04                 -fmul dword ptr [edx + 4]
    x86::Float fpu34 = cpu.fpu.mul(fpu33, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(4) /* 0x4 */)));
    // 004e0318  d94010                 -fld dword ptr [eax + 0x10]
    x86::Float fpu35 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(16) /* 0x10 */));
    // 004e031b  d84a10                 -fmul dword ptr [edx + 0x10]
    x86::Float fpu36 = cpu.fpu.mul(fpu35, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(16) /* 0x10 */)));
    // 004e031e  dec1                   -faddp st(1)
    x86::Float fpu37 = cpu.fpu.add(fpu34, fpu36);
    // 004e0320  d94014                 -fld dword ptr [eax + 0x14]
    x86::Float fpu38 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(20) /* 0x14 */));
    // 004e0323  d84a1c                 -fmul dword ptr [edx + 0x1c]
    x86::Float fpu39 = cpu.fpu.mul(fpu38, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(28) /* 0x1c */)));
    // 004e0326  dec1                   -faddp st(1)
    x86::Float fpu40 = cpu.fpu.add(fpu37, fpu39);
    // 004e0328  d95b10                 -fstp dword ptr [ebx + 0x10]
    app->getMemory<float>(cpu.ebx + x86::reg32(16) /* 0x10 */) = float(fpu40);
    // 004e032b  d9400c                 -fld dword ptr [eax + 0xc]
    x86::Float fpu41 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(12) /* 0xc */));
    // 004e032e  d84a08                 -fmul dword ptr [edx + 8]
    x86::Float fpu42 = cpu.fpu.mul(fpu41, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(8) /* 0x8 */)));
    // 004e0331  d94010                 -fld dword ptr [eax + 0x10]
    x86::Float fpu43 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(16) /* 0x10 */));
    // 004e0334  d84a14                 -fmul dword ptr [edx + 0x14]
    x86::Float fpu44 = cpu.fpu.mul(fpu43, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(20) /* 0x14 */)));
    // 004e0337  dec1                   -faddp st(1)
    x86::Float fpu45 = cpu.fpu.add(fpu42, fpu44);
    // 004e0339  d94014                 -fld dword ptr [eax + 0x14]
    x86::Float fpu46 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(20) /* 0x14 */));
    // 004e033c  d84a20                 -fmul dword ptr [edx + 0x20]
    x86::Float fpu47 = cpu.fpu.mul(fpu46, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(32) /* 0x20 */)));
    // 004e033f  dec1                   -faddp st(1)
    x86::Float fpu48 = cpu.fpu.add(fpu45, fpu47);
    // 004e0341  d95b14                 -fstp dword ptr [ebx + 0x14]
    app->getMemory<float>(cpu.ebx + x86::reg32(20) /* 0x14 */) = float(fpu48);
    // 004e0344  d9401c                 -fld dword ptr [eax + 0x1c]
    x86::Float fpu49 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(28) /* 0x1c */));
    // 004e0347  d84a0c                 -fmul dword ptr [edx + 0xc]
    x86::Float fpu50 = cpu.fpu.mul(fpu49, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(12) /* 0xc */)));
    // 004e034a  d94018                 -fld dword ptr [eax + 0x18]
    x86::Float fpu51 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(24) /* 0x18 */));
    // 004e034d  d80a                   -fmul dword ptr [edx]
    x86::Float fpu52 = cpu.fpu.mul(fpu51, x86::Float(app->getMemory<float>(cpu.edx)));
    // 004e034f  dec1                   -faddp st(1)
    x86::Float fpu53 = cpu.fpu.add(fpu50, fpu52);
    // 004e0351  d94020                 -fld dword ptr [eax + 0x20]
    x86::Float fpu54 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(32) /* 0x20 */));
    // 004e0354  d84a18                 -fmul dword ptr [edx + 0x18]
    x86::Float fpu55 = cpu.fpu.mul(fpu54, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(24) /* 0x18 */)));
    // 004e0357  dec1                   -faddp st(1)
    x86::Float fpu56 = cpu.fpu.add(fpu53, fpu55);
    // 004e0359  d95b18                 -fstp dword ptr [ebx + 0x18]
    app->getMemory<float>(cpu.ebx + x86::reg32(24) /* 0x18 */) = float(fpu56);
    // 004e035c  d94018                 -fld dword ptr [eax + 0x18]
    x86::Float fpu57 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(24) /* 0x18 */));
    // 004e035f  d84a04                 -fmul dword ptr [edx + 4]
    x86::Float fpu58 = cpu.fpu.mul(fpu57, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(4) /* 0x4 */)));
    // 004e0362  d9401c                 -fld dword ptr [eax + 0x1c]
    x86::Float fpu59 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(28) /* 0x1c */));
    // 004e0365  d84a10                 -fmul dword ptr [edx + 0x10]
    x86::Float fpu60 = cpu.fpu.mul(fpu59, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(16) /* 0x10 */)));
    // 004e0368  dec1                   -faddp st(1)
    x86::Float fpu61 = cpu.fpu.add(fpu58, fpu60);
    // 004e036a  d94020                 -fld dword ptr [eax + 0x20]
    x86::Float fpu62 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(32) /* 0x20 */));
    // 004e036d  d84a1c                 -fmul dword ptr [edx + 0x1c]
    x86::Float fpu63 = cpu.fpu.mul(fpu62, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(28) /* 0x1c */)));
    // 004e0370  dec1                   -faddp st(1)
    x86::Float fpu64 = cpu.fpu.add(fpu61, fpu63);
    // 004e0372  d95b1c                 -fstp dword ptr [ebx + 0x1c]
    app->getMemory<float>(cpu.ebx + x86::reg32(28) /* 0x1c */) = float(fpu64);
    // 004e0375  d94018                 -fld dword ptr [eax + 0x18]
    x86::Float fpu65 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(24) /* 0x18 */));
    // 004e0378  d84a08                 -fmul dword ptr [edx + 8]
    x86::Float fpu66 = cpu.fpu.mul(fpu65, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(8) /* 0x8 */)));
    // 004e037b  d9401c                 -fld dword ptr [eax + 0x1c]
    x86::Float fpu67 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(28) /* 0x1c */));
    // 004e037e  d84a14                 -fmul dword ptr [edx + 0x14]
    x86::Float fpu68 = cpu.fpu.mul(fpu67, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(20) /* 0x14 */)));
    // 004e0381  dec1                   -faddp st(1)
    x86::Float fpu69 = cpu.fpu.add(fpu66, fpu68);
    // 004e0383  d94020                 -fld dword ptr [eax + 0x20]
    x86::Float fpu70 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(32) /* 0x20 */));
    // 004e0386  d84a20                 -fmul dword ptr [edx + 0x20]
    x86::Float fpu71 = cpu.fpu.mul(fpu70, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(32) /* 0x20 */)));
    // 004e0389  dec1                   -faddp st(1)
    x86::Float fpu72 = cpu.fpu.add(fpu69, fpu71);
    // 004e038b  d95b20                 -fstp dword ptr [ebx + 0x20]
    app->getMemory<float>(cpu.ebx + x86::reg32(32) /* 0x20 */) = float(fpu72);
    // 004e038e  83c42c                 +add esp, 0x2c
    {
        x86::reg32& tmp1 = cpu.esp;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(44 /*0x2c*/));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 004e0391  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e0392  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e0393  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e0394  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    }
    // 004e0395  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004e0396:
    // 004e0396  b909000000             -mov ecx, 9
    cpu.ecx = 9 /*0x9*/;
    // 004e039b  89e7                   -mov edi, esp
    cpu.edi = cpu.esp;
    // 004e039d  8b742424               -mov esi, dword ptr [esp + 0x24]
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(36) /* 0x24 */);
    // 004e03a1  89e0                   -mov eax, esp
    cpu.eax = cpu.esp;
    // 004e03a3  f3a5                   -rep movsd dword ptr es:[edi], dword ptr [esi]
    while (cpu.ecx)
    {
        app->getMemory<x86::reg32>(cpu.ees + cpu.edi) = app->getMemory<x86::reg32>(cpu.esi);
        if (cpu.flags.df)
        {
            cpu.edi -= 4;
            cpu.esi -= 4;
        }
        else
        {
            cpu.edi += 4;
            cpu.esi += 4;
        }
        --cpu.ecx;
    }
    // 004e03a5  e9effeffff             -jmp 0x4e0299
    goto L_0x004e0299;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 */
void Application::sub_4e03b0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (rotateVectors(app, cpu.sync())) /* port: native (tools/apply_native_vertices.py) */
    {
        cpu.reload();
        return;
    }
    // 004e03b0  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004e03b1  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004e03b2  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 004e03b4  89df                   -mov edi, ebx
    cpu.edi = cpu.ebx;
    // 004e03b6  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004e03b8  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 004e03ba  7e64                   -jle 0x4e0420
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004e0420;
    }
L_0x004e03bc:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004e03bc  89cb                   -mov ebx, ecx
    cpu.ebx = cpu.ecx;
    // 004e03be  89fa                   -mov edx, edi
    cpu.edx = cpu.edi;
    // 004e03c0  d900                   -fld dword ptr [eax]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.eax));
    // 004e03c2  d80a                   -fmul dword ptr [edx]
    x86::Float fpu2 = cpu.fpu.mul(fpu1, x86::Float(app->getMemory<float>(cpu.edx)));
    // 004e03c4  d900                   -fld dword ptr [eax]
    x86::Float fpu3 = x86::Float(app->getMemory<float>(cpu.eax));
    // 004e03c6  d84a04                 -fmul dword ptr [edx + 4]
    x86::Float fpu4 = cpu.fpu.mul(fpu3, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(4) /* 0x4 */)));
    // 004e03c9  d900                   -fld dword ptr [eax]
    x86::Float fpu5 = x86::Float(app->getMemory<float>(cpu.eax));
    // 004e03cb  d84a08                 -fmul dword ptr [edx + 8]
    x86::Float fpu6 = cpu.fpu.mul(fpu5, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(8) /* 0x8 */)));
    // 004e03ce  d9ca                   -fxch st(2)
    
    // 004e03d0  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu7 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 004e03d3  d84a0c                 -fmul dword ptr [edx + 0xc]
    x86::Float fpu8 = cpu.fpu.mul(fpu7, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(12) /* 0xc */)));
    // 004e03d6  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu9 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 004e03d9  d84a10                 -fmul dword ptr [edx + 0x10]
    x86::Float fpu10 = cpu.fpu.mul(fpu9, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(16) /* 0x10 */)));
    // 004e03dc  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu11 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 004e03df  d84a14                 -fmul dword ptr [edx + 0x14]
    x86::Float fpu12 = cpu.fpu.mul(fpu11, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(20) /* 0x14 */)));
    // 004e03e2  d9ca                   -fxch st(2)
    
    // 004e03e4  dec3                   -faddp st(3)
    x86::Float fpu13 = cpu.fpu.add(fpu2, fpu8);
    // 004e03e6  dec3                   -faddp st(3)
    x86::Float fpu14 = cpu.fpu.add(fpu4, fpu10);
    // 004e03e8  dec3                   -faddp st(3)
    x86::Float fpu15 = cpu.fpu.add(fpu6, fpu12);
    // 004e03ea  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu16 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 004e03ed  d84a18                 -fmul dword ptr [edx + 0x18]
    x86::Float fpu17 = cpu.fpu.mul(fpu16, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(24) /* 0x18 */)));
    // 004e03f0  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu18 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 004e03f3  d84a1c                 -fmul dword ptr [edx + 0x1c]
    x86::Float fpu19 = cpu.fpu.mul(fpu18, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(28) /* 0x1c */)));
    // 004e03f6  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu20 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 004e03f9  d84a20                 -fmul dword ptr [edx + 0x20]
    x86::Float fpu21 = cpu.fpu.mul(fpu20, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(32) /* 0x20 */)));
    // 004e03fc  d9ca                   -fxch st(2)
    
    // 004e03fe  dec3                   -faddp st(3)
    x86::Float fpu22 = cpu.fpu.add(fpu13, fpu17);
    // 004e0400  dec3                   -faddp st(3)
    x86::Float fpu23 = cpu.fpu.add(fpu14, fpu19);
    // 004e0402  dec3                   -faddp st(3)
    x86::Float fpu24 = cpu.fpu.add(fpu15, fpu21);
    // 004e0404  8d400c                 -lea eax, [eax + 0xc]
    cpu.eax = x86::reg32(cpu.eax + x86::reg32(12) /* 0xc */);
    // 004e0407  d91b                   -fstp dword ptr [ebx]
    app->getMemory<float>(cpu.ebx) = float(fpu22);
    // 004e0409  d95b04                 -fstp dword ptr [ebx + 4]
    app->getMemory<float>(cpu.ebx + x86::reg32(4) /* 0x4 */) = float(fpu23);
    // 004e040c  d95b08                 -fstp dword ptr [ebx + 8]
    app->getMemory<float>(cpu.ebx + x86::reg32(8) /* 0x8 */) = float(fpu24);
    // 004e040f  83c10c                 +add ecx, 0xc
    {
        x86::reg32& tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(12 /*0xc*/));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 004e0412  4e                     +dec esi
    {
        x86::reg32& tmp = cpu.esi;
        cpu.flags.of = 1 & (tmp >> 31);
        tmp--;
        cpu.flags.of &= ~(1 & (tmp >> 31));
        cpu.set_szp(tmp);
    }
    }
    // 004e0413  75a7                   -jne 0x4e03bc
    if (!cpu.flags.zf)
    {
        goto L_0x004e03bc;
    }
    // 004e0415  8d8000000000           -lea eax, [eax]
    cpu.eax = x86::reg32(cpu.eax);
    // 004e041b  8d5200                 -lea edx, [edx]
    cpu.edx = x86::reg32(cpu.edx);
    // 004e041e  8bdb                   -mov ebx, ebx
    cpu.ebx = cpu.ebx;
L_0x004e0420:
    // 004e0420  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e0421  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e0422  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x90 */
void Application::sub_4e0430(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (transformPoints(app, cpu.sync())) /* port: native (tools/apply_native_vertices.py) */
    {
        cpu.reload();
        return;
    }
    // 004e0430  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004e0431  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004e0432  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004e0433  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 004e0436  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 004e0438  89d7                   -mov edi, edx
    cpu.edi = cpu.edx;
    // 004e043a  89dd                   -mov ebp, ebx
    cpu.ebp = cpu.ebx;
    // 004e043c  890c24                 -mov dword ptr [esp], ecx
    app->getMemory<x86::reg32>(cpu.esp) = cpu.ecx;
    // 004e043f  8b4c2414               -mov ecx, dword ptr [esp + 0x14]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(20) /* 0x14 */);
    // 004e0443  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004e0445  0f8e85000000           -jle 0x4e04d0
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004e04d0;
    }
L_0x004e044b:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004e044b  89cb                   -mov ebx, ecx
    cpu.ebx = cpu.ecx;
    // 004e044d  89ea                   -mov edx, ebp
    cpu.edx = cpu.ebp;
    // 004e044f  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 004e0451  d900                   +fld dword ptr [eax]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.eax));
    // 004e0453  d80a                   +fmul dword ptr [edx]
    x86::Float fpu2 = cpu.fpu.mul(fpu1, x86::Float(app->getMemory<float>(cpu.edx)));
    // 004e0455  d900                   +fld dword ptr [eax]
    x86::Float fpu3 = x86::Float(app->getMemory<float>(cpu.eax));
    // 004e0457  d84a04                 +fmul dword ptr [edx + 4]
    x86::Float fpu4 = cpu.fpu.mul(fpu3, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(4) /* 0x4 */)));
    // 004e045a  d900                   +fld dword ptr [eax]
    x86::Float fpu5 = x86::Float(app->getMemory<float>(cpu.eax));
    // 004e045c  d84a08                 +fmul dword ptr [edx + 8]
    x86::Float fpu6 = cpu.fpu.mul(fpu5, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(8) /* 0x8 */)));
    // 004e045f  d9ca                   +fxch st(2)
    
    // 004e0461  d94004                 +fld dword ptr [eax + 4]
    x86::Float fpu7 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 004e0464  d84a0c                 +fmul dword ptr [edx + 0xc]
    x86::Float fpu8 = cpu.fpu.mul(fpu7, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(12) /* 0xc */)));
    // 004e0467  d94004                 +fld dword ptr [eax + 4]
    x86::Float fpu9 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 004e046a  d84a10                 +fmul dword ptr [edx + 0x10]
    x86::Float fpu10 = cpu.fpu.mul(fpu9, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(16) /* 0x10 */)));
    // 004e046d  d94004                 +fld dword ptr [eax + 4]
    x86::Float fpu11 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 004e0470  d84a14                 +fmul dword ptr [edx + 0x14]
    x86::Float fpu12 = cpu.fpu.mul(fpu11, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(20) /* 0x14 */)));
    // 004e0473  d9ca                   +fxch st(2)
    
    // 004e0475  dec3                   +faddp st(3)
    x86::Float fpu13 = cpu.fpu.add(fpu2, fpu8);
    // 004e0477  dec3                   +faddp st(3)
    x86::Float fpu14 = cpu.fpu.add(fpu4, fpu10);
    // 004e0479  dec3                   +faddp st(3)
    x86::Float fpu15 = cpu.fpu.add(fpu6, fpu12);
    // 004e047b  d94008                 +fld dword ptr [eax + 8]
    x86::Float fpu16 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 004e047e  d84a18                 +fmul dword ptr [edx + 0x18]
    x86::Float fpu17 = cpu.fpu.mul(fpu16, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(24) /* 0x18 */)));
    // 004e0481  d94008                 +fld dword ptr [eax + 8]
    x86::Float fpu18 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 004e0484  d84a1c                 +fmul dword ptr [edx + 0x1c]
    x86::Float fpu19 = cpu.fpu.mul(fpu18, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(28) /* 0x1c */)));
    // 004e0487  d94008                 +fld dword ptr [eax + 8]
    x86::Float fpu20 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 004e048a  d84a20                 +fmul dword ptr [edx + 0x20]
    x86::Float fpu21 = cpu.fpu.mul(fpu20, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(32) /* 0x20 */)));
    // 004e048d  d9ca                   +fxch st(2)
    
    // 004e048f  dec3                   +faddp st(3)
    x86::Float fpu22 = cpu.fpu.add(fpu13, fpu17);
    // 004e0491  dec3                   +faddp st(3)
    x86::Float fpu23 = cpu.fpu.add(fpu14, fpu19);
    // 004e0493  dec3                   +faddp st(3)
    x86::Float fpu24 = cpu.fpu.add(fpu15, fpu21);
    // 004e0495  8d400c                 -lea eax, [eax + 0xc]
    cpu.eax = x86::reg32(cpu.eax + x86::reg32(12) /* 0xc */);
    // 004e0498  d91b                   +fstp dword ptr [ebx]
    app->getMemory<float>(cpu.ebx) = float(fpu22);
    // 004e049a  d95b04                 +fstp dword ptr [ebx + 4]
    app->getMemory<float>(cpu.ebx + x86::reg32(4) /* 0x4 */) = float(fpu23);
    // 004e049d  d95b08                 +fstp dword ptr [ebx + 8]
    app->getMemory<float>(cpu.ebx + x86::reg32(8) /* 0x8 */) = float(fpu24);
    // 004e04a0  8b1424                 -mov edx, dword ptr [esp]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    // 004e04a3  89c7                   -mov edi, eax
    cpu.edi = cpu.eax;
    // 004e04a5  89cb                   -mov ebx, ecx
    cpu.ebx = cpu.ecx;
    // 004e04a7  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004e04a9  d900                   +fld dword ptr [eax]
    x86::Float fpu25 = x86::Float(app->getMemory<float>(cpu.eax));
    // 004e04ab  d802                   +fadd dword ptr [edx]
    x86::Float fpu26 = cpu.fpu.add(fpu25, x86::Float(app->getMemory<float>(cpu.edx)));
    // 004e04ad  d94004                 +fld dword ptr [eax + 4]
    x86::Float fpu27 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 004e04b0  d84204                 +fadd dword ptr [edx + 4]
    x86::Float fpu28 = cpu.fpu.add(fpu27, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(4) /* 0x4 */)));
    // 004e04b3  d94008                 +fld dword ptr [eax + 8]
    x86::Float fpu29 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 004e04b6  d84208                 +fadd dword ptr [edx + 8]
    x86::Float fpu30 = cpu.fpu.add(fpu29, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(8) /* 0x8 */)));
    // 004e04b9  d9ca                   +fxch st(2)
    
    // 004e04bb  8d400c                 -lea eax, [eax + 0xc]
    cpu.eax = x86::reg32(cpu.eax + x86::reg32(12) /* 0xc */);
    // 004e04be  d91b                   +fstp dword ptr [ebx]
    app->getMemory<float>(cpu.ebx) = float(fpu26);
    // 004e04c0  d95b04                 +fstp dword ptr [ebx + 4]
    app->getMemory<float>(cpu.ebx + x86::reg32(4) /* 0x4 */) = float(fpu28);
    // 004e04c3  d95b08                 +fstp dword ptr [ebx + 8]
    app->getMemory<float>(cpu.ebx + x86::reg32(8) /* 0x8 */) = float(fpu30);
    // 004e04c6  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 004e04c8  4e                     +dec esi
    {
        x86::reg32& tmp = cpu.esi;
        cpu.flags.of = 1 & (tmp >> 31);
        tmp--;
        cpu.flags.of &= ~(1 & (tmp >> 31));
        cpu.set_szp(tmp);
    }
    }
    // 004e04c9  7580                   -jne 0x4e044b
    if (!cpu.flags.zf)
    {
        goto L_0x004e044b;
    }
    // 004e04cb  8d4000                 -lea eax, [eax]
    cpu.eax = x86::reg32(cpu.eax);
    // 004e04ce  8bc9                   -mov ecx, ecx
    cpu.ecx = cpu.ecx;
L_0x004e04d0:
    // 004e04d0  83c404                 -add esp, 4
    (cpu.esp) += x86::reg32(x86::sreg32(4 /*0x4*/));
    // 004e04d3  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e04d4  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e04d5  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e04d6  c20400                 -ret 4
    cpu.esp += 4+4 /*0x4*/;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x90 */
void Application::sub_4e04e0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004e04e0  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004e04e1  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004e04e2  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004e04e3  83ec08                 -sub esp, 8
    (cpu.esp) -= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 004e04e6  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 004e04e8  89d7                   -mov edi, edx
    cpu.edi = cpu.edx;
    // 004e04ea  891c24                 -mov dword ptr [esp], ebx
    app->getMemory<x86::reg32>(cpu.esp) = cpu.ebx;
    // 004e04ed  89cd                   -mov ebp, ecx
    cpu.ebp = cpu.ecx;
    // 004e04ef  8b4c2418               -mov ecx, dword ptr [esp + 0x18]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(24) /* 0x18 */);
    // 004e04f3  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004e04f5  0f8ea5000000           -jle 0x4e05a0
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004e05a0;
    }
    // 004e04fb  8b54241c               -mov edx, dword ptr [esp + 0x1c]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(28) /* 0x1c */);
    // 004e04ff  8d049500000000         -lea eax, [edx*4]
    cpu.eax = x86::reg32(cpu.edx * 4);
    // 004e0506  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 004e0508  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 004e050b  89442404               -mov dword ptr [esp + 4], eax
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(4) /* 0x4 */) = cpu.eax;
L_0x004e050f:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004e050f  8b1424                 -mov edx, dword ptr [esp]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    // 004e0512  89cb                   -mov ebx, ecx
    cpu.ebx = cpu.ecx;
    // 004e0514  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 004e0516  d900                   -fld dword ptr [eax]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.eax));
    // 004e0518  d80a                   -fmul dword ptr [edx]
    x86::Float fpu2 = cpu.fpu.mul(fpu1, x86::Float(app->getMemory<float>(cpu.edx)));
    // 004e051a  d900                   -fld dword ptr [eax]
    x86::Float fpu3 = x86::Float(app->getMemory<float>(cpu.eax));
    // 004e051c  d84a04                 -fmul dword ptr [edx + 4]
    x86::Float fpu4 = cpu.fpu.mul(fpu3, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(4) /* 0x4 */)));
    // 004e051f  d900                   -fld dword ptr [eax]
    x86::Float fpu5 = x86::Float(app->getMemory<float>(cpu.eax));
    // 004e0521  d84a08                 -fmul dword ptr [edx + 8]
    x86::Float fpu6 = cpu.fpu.mul(fpu5, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(8) /* 0x8 */)));
    // 004e0524  d9ca                   -fxch st(2)
    
    // 004e0526  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu7 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 004e0529  d84a0c                 -fmul dword ptr [edx + 0xc]
    x86::Float fpu8 = cpu.fpu.mul(fpu7, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(12) /* 0xc */)));
    // 004e052c  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu9 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 004e052f  d84a10                 -fmul dword ptr [edx + 0x10]
    x86::Float fpu10 = cpu.fpu.mul(fpu9, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(16) /* 0x10 */)));
    // 004e0532  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu11 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 004e0535  d84a14                 -fmul dword ptr [edx + 0x14]
    x86::Float fpu12 = cpu.fpu.mul(fpu11, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(20) /* 0x14 */)));
    // 004e0538  d9ca                   -fxch st(2)
    
    // 004e053a  dec3                   -faddp st(3)
    x86::Float fpu13 = cpu.fpu.add(fpu2, fpu8);
    // 004e053c  dec3                   -faddp st(3)
    x86::Float fpu14 = cpu.fpu.add(fpu4, fpu10);
    // 004e053e  dec3                   -faddp st(3)
    x86::Float fpu15 = cpu.fpu.add(fpu6, fpu12);
    // 004e0540  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu16 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 004e0543  d84a18                 -fmul dword ptr [edx + 0x18]
    x86::Float fpu17 = cpu.fpu.mul(fpu16, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(24) /* 0x18 */)));
    // 004e0546  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu18 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 004e0549  d84a1c                 -fmul dword ptr [edx + 0x1c]
    x86::Float fpu19 = cpu.fpu.mul(fpu18, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(28) /* 0x1c */)));
    // 004e054c  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu20 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 004e054f  d84a20                 -fmul dword ptr [edx + 0x20]
    x86::Float fpu21 = cpu.fpu.mul(fpu20, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(32) /* 0x20 */)));
    // 004e0552  d9ca                   -fxch st(2)
    
    // 004e0554  dec3                   -faddp st(3)
    x86::Float fpu22 = cpu.fpu.add(fpu13, fpu17);
    // 004e0556  dec3                   -faddp st(3)
    x86::Float fpu23 = cpu.fpu.add(fpu14, fpu19);
    // 004e0558  dec3                   -faddp st(3)
    x86::Float fpu24 = cpu.fpu.add(fpu15, fpu21);
    // 004e055a  8d400c                 -lea eax, [eax + 0xc]
    cpu.eax = x86::reg32(cpu.eax + x86::reg32(12) /* 0xc */);
    // 004e055d  d91b                   -fstp dword ptr [ebx]
    app->getMemory<float>(cpu.ebx) = float(fpu22);
    // 004e055f  d95b04                 -fstp dword ptr [ebx + 4]
    app->getMemory<float>(cpu.ebx + x86::reg32(4) /* 0x4 */) = float(fpu23);
    // 004e0562  d95b08                 -fstp dword ptr [ebx + 8]
    app->getMemory<float>(cpu.ebx + x86::reg32(8) /* 0x8 */) = float(fpu24);
    // 004e0565  89c7                   -mov edi, eax
    cpu.edi = cpu.eax;
    // 004e0567  89cb                   -mov ebx, ecx
    cpu.ebx = cpu.ecx;
    // 004e0569  89ea                   -mov edx, ebp
    cpu.edx = cpu.ebp;
    // 004e056b  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004e056d  d900                   -fld dword ptr [eax]
    x86::Float fpu25 = x86::Float(app->getMemory<float>(cpu.eax));
    // 004e056f  d802                   -fadd dword ptr [edx]
    x86::Float fpu26 = cpu.fpu.add(fpu25, x86::Float(app->getMemory<float>(cpu.edx)));
    // 004e0571  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu27 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 004e0574  d84204                 -fadd dword ptr [edx + 4]
    x86::Float fpu28 = cpu.fpu.add(fpu27, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(4) /* 0x4 */)));
    // 004e0577  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu29 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 004e057a  d84208                 -fadd dword ptr [edx + 8]
    x86::Float fpu30 = cpu.fpu.add(fpu29, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(8) /* 0x8 */)));
    // 004e057d  d9ca                   -fxch st(2)
    
    // 004e057f  8d400c                 -lea eax, [eax + 0xc]
    cpu.eax = x86::reg32(cpu.eax + x86::reg32(12) /* 0xc */);
    // 004e0582  d91b                   -fstp dword ptr [ebx]
    app->getMemory<float>(cpu.ebx) = float(fpu26);
    // 004e0584  d95b04                 -fstp dword ptr [ebx + 4]
    app->getMemory<float>(cpu.ebx + x86::reg32(4) /* 0x4 */) = float(fpu28);
    // 004e0587  d95b08                 -fstp dword ptr [ebx + 8]
    app->getMemory<float>(cpu.ebx + x86::reg32(8) /* 0x8 */) = float(fpu30);
    // 004e058a  034c2404               +add ecx, dword ptr [esp + 4]
    {
        x86::reg32& tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.esp + x86::reg32(4) /* 0x4 */)));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 004e058e  4e                     +dec esi
    {
        x86::reg32& tmp = cpu.esi;
        cpu.flags.of = 1 & (tmp >> 31);
        tmp--;
        cpu.flags.of &= ~(1 & (tmp >> 31));
        cpu.set_szp(tmp);
    }
    }
    // 004e058f  0f857affffff           -jne 0x4e050f
    if (!cpu.flags.zf)
    {
        goto L_0x004e050f;
    }
    // 004e0595  8d8000000000           -lea eax, [eax]
    cpu.eax = x86::reg32(cpu.eax);
    // 004e059b  8d5200                 -lea edx, [edx]
    cpu.edx = x86::reg32(cpu.edx);
    // 004e059e  8bdb                   -mov ebx, ebx
    cpu.ebx = cpu.ebx;
L_0x004e05a0:
    // 004e05a0  83c408                 -add esp, 8
    (cpu.esp) += x86::reg32(x86::sreg32(8 /*0x8*/));
    // 004e05a3  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e05a4  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e05a5  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e05a6  c20800                 -ret 8
    cpu.esp += 4+8 /*0x8*/;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x90 */
void Application::sub_4e05b0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004e05b0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004e05b1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004e05b2  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004e05b3  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 004e05b5  89d1                   -mov ecx, edx
    cpu.ecx = cpu.edx;
    // 004e05b7  bb0c000000             -mov ebx, 0xc
    cpu.ebx = 12 /*0xc*/;
    // 004e05bc  e82f9f0000             -call 0x4ea4f0
    cpu.esp -= 4;
    nfs3hp::ea::memmove(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e05c1  bb0c000000             -mov ebx, 0xc
    cpu.ebx = 12 /*0xc*/;
    // 004e05c6  8d5110                 -lea edx, [ecx + 0x10]
    cpu.edx = x86::reg32(cpu.ecx + x86::reg32(16) /* 0x10 */);
    // 004e05c9  8d460c                 -lea eax, [esi + 0xc]
    cpu.eax = x86::reg32(cpu.esi + x86::reg32(12) /* 0xc */);
    // 004e05cc  e81f9f0000             -call 0x4ea4f0
    cpu.esp -= 4;
    nfs3hp::ea::memmove(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e05d1  bb0c000000             -mov ebx, 0xc
    cpu.ebx = 12 /*0xc*/;
    // 004e05d6  8d5120                 -lea edx, [ecx + 0x20]
    cpu.edx = x86::reg32(cpu.ecx + x86::reg32(32) /* 0x20 */);
    // 004e05d9  8d4618                 -lea eax, [esi + 0x18]
    cpu.eax = x86::reg32(cpu.esi + x86::reg32(24) /* 0x18 */);
    // 004e05dc  e80f9f0000             -call 0x4ea4f0
    cpu.esp -= 4;
    nfs3hp::ea::memmove(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e05e1  c7413800000000         -mov dword ptr [ecx + 0x38], 0
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(56) /* 0x38 */) = 0 /*0x0*/;
    // 004e05e8  c7413c0000803f         -mov dword ptr [ecx + 0x3c], 0x3f800000
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(60) /* 0x3c */) = 1065353216 /*0x3f800000*/;
    // 004e05ef  8b4138                 -mov eax, dword ptr [ecx + 0x38]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(56) /* 0x38 */);
    // 004e05f2  894134                 -mov dword ptr [ecx + 0x34], eax
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(52) /* 0x34 */) = cpu.eax;
    // 004e05f5  8b4134                 -mov eax, dword ptr [ecx + 0x34]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(52) /* 0x34 */);
    // 004e05f8  894130                 -mov dword ptr [ecx + 0x30], eax
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(48) /* 0x30 */) = cpu.eax;
    // 004e05fb  8b4130                 -mov eax, dword ptr [ecx + 0x30]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(48) /* 0x30 */);
    // 004e05fe  89412c                 -mov dword ptr [ecx + 0x2c], eax
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(44) /* 0x2c */) = cpu.eax;
    // 004e0601  8b412c                 -mov eax, dword ptr [ecx + 0x2c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(44) /* 0x2c */);
    // 004e0604  89411c                 -mov dword ptr [ecx + 0x1c], eax
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(28) /* 0x1c */) = cpu.eax;
    // 004e0607  8b411c                 -mov eax, dword ptr [ecx + 0x1c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(28) /* 0x1c */);
    // 004e060a  89410c                 -mov dword ptr [ecx + 0xc], eax
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(12) /* 0xc */) = cpu.eax;
    // 004e060d  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e060e  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e060f  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e0610  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x8d 0x40 0x00 */
void Application::sub_4e0620(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004e0620  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004e0621  89d1                   -mov ecx, edx
    cpu.ecx = cpu.edx;
    // 004e0623  89da                   -mov edx, ebx
    cpu.edx = cpu.ebx;
    // 004e0625  e886ffffff             -call 0x4e05b0
    cpu.esp -= 4;
    sub_4e05b0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e062a  8d5330                 -lea edx, [ebx + 0x30]
    cpu.edx = x86::reg32(cpu.ebx + x86::reg32(48) /* 0x30 */);
    // 004e062d  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004e062f  bb0c000000             -mov ebx, 0xc
    cpu.ebx = 12 /*0xc*/;
    // 004e0634  e8b79e0000             -call 0x4ea4f0
    cpu.esp -= 4;
    nfs3hp::ea::memmove(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e0639  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e063a  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_4e0640: native, nfs3hp::watcom::memset */

/* align: skip  */
void Application::sub_4e0658(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004e0658  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip  */
void Application::sub_4e0659(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004e0659  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x00 0x00 0x00 0x00 0x00 0x00 */
void Application::sub_4e0660(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004e0660  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004e0661  83ec18                 -sub esp, 0x18
    (cpu.esp) -= x86::reg32(x86::sreg32(24 /*0x18*/));
    // 004e0664  89d1                   -mov ecx, edx
    cpu.ecx = cpu.edx;
    // 004e0666  8d54240c               -lea edx, [esp + 0xc]
    cpu.edx = x86::reg32(cpu.esp + x86::reg32(12) /* 0xc */);
    // 004e066a  e851fbffff             -call 0x4e01c0
    cpu.esp -= 4;
    sub_4e01c0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e066f  89e2                   -mov edx, esp
    cpu.edx = cpu.esp;
    // 004e0671  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004e0673  e848fbffff             -call 0x4e01c0
    cpu.esp -= 4;
    sub_4e01c0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e0678  89e2                   -mov edx, esp
    cpu.edx = cpu.esp;
    // 004e067a  8d44240c               -lea eax, [esp + 0xc]
    cpu.eax = x86::reg32(cpu.esp + x86::reg32(12) /* 0xc */);
    // 004e067e  e86dfbffff             -call 0x4e01f0
    cpu.esp -= 4;
    sub_4e01f0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e0683  e8fa8d0100             -call 0x4f9482
    cpu.esp -= 4;
    nfs3hp::watcom::IF_DACOS(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e0688  dc0d20995400           -fmul qword ptr [0x549920]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = cpu.fpu.st(0);
    x86::Float fpu2 = cpu.fpu.mul(fpu1, x86::Float(app->getMemory<double>(x86::reg32(5544224) /* 0x549920 */)));
    // 004e068e  83c418                 -add esp, 0x18
    (cpu.esp) += x86::reg32(x86::sreg32(24 /*0x18*/));
    // 004e0691  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    cpu.fpu.st(0) = fpu2;
    }
    // 004e0692  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x90 */
void Application::sub_4e06a0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (vectorLengthOf(app, cpu.sync())) /* port: native (tools/apply_native_vertices.py) */
    {
        cpu.reload();
        return;
    }
    // 004e06a0  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 004e06a3  d900                   -fld dword ptr [eax]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.eax));
    // 004e06a5  d8c8                   -fmul st(0)
    x86::Float fpu2 = cpu.fpu.mul(fpu1, x86::Float(fpu1));
    // 004e06a7  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu3 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 004e06aa  d8c8                   -fmul st(0)
    x86::Float fpu4 = cpu.fpu.mul(fpu3, x86::Float(fpu3));
    // 004e06ac  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu5 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 004e06af  d9c9                   -fxch st(1)
    
    // 004e06b1  d8c2                   -fadd st(2)
    x86::Float fpu6 = cpu.fpu.add(fpu4, x86::Float(fpu2));
    // 004e06b3  d9c9                   -fxch st(1)
    
    // 004e06b5  d84808                 -fmul dword ptr [eax + 8]
    x86::Float fpu7 = cpu.fpu.mul(fpu5, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */)));
    // 004e06b8  d9c9                   -fxch st(1)
    
    // 004e06ba  ddda                   -fstp st(2)
    x86::Float fpu8 = x86::Float(fpu6);
    // 004e06bc  dec1                   -faddp st(1)
    x86::Float fpu9 = cpu.fpu.add(fpu8, fpu7);
    // 004e06be  d9fa                   -fsqrt 
    x86::Float fpu10 = cpu.fpu.sqrt(fpu9);
    // 004e06c0  83c404                 -add esp, 4
    (cpu.esp) += x86::reg32(x86::sreg32(4 /*0x4*/));
    cpu.fpu.count += 1;
    cpu.fpu.st(0) = fpu10;
    }
    // 004e06c3  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip  */
void Application::sub_4e06c4(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004e06c4  d9e8                   -fld1 
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = 1.0;
    // 004e06c6  f6055878560001         +test byte ptr [0x567858], 1
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(x86::reg32(5666904) /* 0x567858 */) & 1 /*0x1*/));
    cpu.fpu.count += 1;
    cpu.fpu.st(0) = fpu1;
    }
    // 004e06cd  7504                   -jne 0x4e06d3
    if (!cpu.flags.zf)
    {
        goto L_0x004e06d3;
    }
    // 004e06cf  d9f3                   +fpatan 
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu2 = cpu.fpu.st(0);
    x86::Float fpu3 = cpu.fpu.st(1);
    x86::Float fpu4 = cpu.fpu.atan(fpu2, fpu3);
    cpu.fpu.count -= 1;
    cpu.fpu.st(0) = fpu4;
    }
    // 004e06d1  eb05                   -jmp 0x4e06d8
    goto L_0x004e06d8;
L_0x004e06d3:
    // 004e06d3  e84cef0100             -call 0x4ff624
    cpu.esp -= 4;
    nfs3hp::watcom::fpatan_wrap(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x004e06d8:
    // 004e06d8  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_4e06d9: native, nfs3hp::watcom::IF_DATAN2 */

/* align: skip  */
void Application::sub_4e06ee(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004e06ee  dd442404               -fld qword ptr [esp + 4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<double>(cpu.esp + x86::reg32(4) /* 0x4 */));
    cpu.fpu.count += 1;
    cpu.fpu.st(0) = fpu1;
    }
    // 004e06f2  e8cdffffff             -call 0x4e06c4
    cpu.esp -= 4;
    sub_4e06c4(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e06f7  c20800                 -ret 8
    cpu.esp += 4+8 /*0x8*/;
    return;
}

/* align: skip  */
void Application::sub_4e06fa(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004e06fa  dd44240c               -fld qword ptr [esp + 0xc]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<double>(cpu.esp + x86::reg32(12) /* 0xc */));
    // 004e06fe  dd442404               -fld qword ptr [esp + 4]
    x86::Float fpu2 = x86::Float(app->getMemory<double>(cpu.esp + x86::reg32(4) /* 0x4 */));
    cpu.fpu.count += 2;
    cpu.fpu.st(0) = fpu2;
    cpu.fpu.st(1) = fpu1;
    }
    // 004e0702  e8d2ffffff             -call 0x4e06d9
    cpu.esp -= 4;
    nfs3hp::watcom::IF_DATAN2(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e0707  c21000                 -ret 0x10
    cpu.esp += 4+16 /*0x10*/;
    return;
}

/* sub_4e070c: native, nfs3hp::fillZero */

/* sub_4e0716: native, nfs3hp::fillByte */

/* sub_4e0721: native, nfs3hp::fillWord */

/* sub_4e0820: native, nfs3hp::watcom::strstr */

/* sub_4e08f0: native, nfs3hp::ea::monoPrintf */

/* sub_4e0980: native, nfs3hp::ea::monoPrintfAt */

/* sub_4e0a60: native, nfs3hp::ea::monoWrite */

/* sub_4e0c10: native, nfs3hp::ea::monoScroll */

/* sub_4e0ca0: native, nfs3hp::ea::monoClear */

/* sub_4e0d00: native, nfs3hp::ea::monoSetTop */

/* sub_4e0d50: native, nfs3hp::ea::monoSetAttribute */

/* sub_4e0d60: native, nfs3hp::ea::monoSetTab */

/* sub_4e0d70: native, nfs3hp::ea::monoPage */

/* sub_4e0d80: native, nfs3hp::ea::monoNoCursor */

/* sub_4e0d88: native, nfs3hp::port::eaRandom */

/* sub_4e0dee: native, nfs3hp::ea::seedRandom */

/* sub_4e0e30: native, nfs3hp::watcom::strncpy */

/* sub_4e0e60: native, nfs3hp::ea::fileExists */

/* sub_4e0ec0: native, nfs3hp::ea::loadFile */

/* sub_4e0fe0: native, nfs3hp::ea::loadFileQuietly */

/* sub_4e1000: native, nfs3hp::ea::findFreeBlock */

/* sub_4e1030: native, nfs3hp::ea::findLargestFreeBlock */

/* sub_4e1080: native, nfs3hp::ea::linkFreeBlock */

}
