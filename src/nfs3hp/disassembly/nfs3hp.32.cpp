#include "nfs3hp.h"
#include <lib/thread.h>

namespace nfs3hp
{

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

/* sub_4dffb0: native, nfs3hp::vertices::addVectors */

/* sub_4e0000: native, nfs3hp::vertices::subtractVectors */

/* sub_4e0050: native, nfs3hp::vertices::scaleVectors */

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
    nfs3hp::vertices::vectorLengthOf(app, cpu.sync());
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
    nfs3hp::vertices::unitVector(app, cpu.sync());
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

/* sub_4e01c0: native, nfs3hp::vertices::unitVector */

/* sub_4e01f0: native, nfs3hp::vertices::dotPush */

/* sub_4e0210: native, nfs3hp::vertices::dotProducts */

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
    nfs3hp::vertices::unitVector(app, cpu.sync());
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
    nfs3hp::vertices::scaleVectors(app, cpu.sync());
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

/* sub_4e0280: native, nfs3hp::vertices::multiplyMatrices */

/* sub_4e03b0: native, nfs3hp::vertices::rotateVectors */

/* sub_4e0430: native, nfs3hp::vertices::transformPoints */

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
    nfs3hp::vertices::unitVector(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e066f  89e2                   -mov edx, esp
    cpu.edx = cpu.esp;
    // 004e0671  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004e0673  e848fbffff             -call 0x4e01c0
    cpu.esp -= 4;
    nfs3hp::vertices::unitVector(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e0678  89e2                   -mov edx, esp
    cpu.edx = cpu.esp;
    // 004e067a  8d44240c               -lea eax, [esp + 0xc]
    cpu.eax = x86::reg32(cpu.esp + x86::reg32(12) /* 0xc */);
    // 004e067e  e86dfbffff             -call 0x4e01f0
    cpu.esp -= 4;
    nfs3hp::vertices::dotPush(app, cpu.sync());
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

/* sub_4e06a0: native, nfs3hp::vertices::vectorLengthOf */

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
