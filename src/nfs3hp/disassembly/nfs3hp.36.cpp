#include "nfs3hp.h"
#include <lib/thread.h>

namespace nfs3hp
{

/* sub_4ed800: native, nfs3hp::dead::stub_0x4ed800 */

/* align: skip 0x8d 0x40 0x00 */
void Application::sub_4ed820(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004ed820  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004ed821  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004ed822  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004ed823  83ec6c                 -sub esp, 0x6c
    (cpu.esp) -= x86::reg32(x86::sreg32(108 /*0x6c*/));
    // 004ed826  8bac2480000000         -mov ebp, dword ptr [esp + 0x80]
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(128) /* 0x80 */);
    // 004ed82d  89d6                   -mov esi, edx
    cpu.esi = cpu.edx;
    // 004ed82f  89df                   -mov edi, ebx
    cpu.edi = cpu.ebx;
    // 004ed831  89cb                   -mov ebx, ecx
    cpu.ebx = cpu.ecx;
    // 004ed833  89e1                   -mov ecx, esp
    cpu.ecx = cpu.esp;
    // 004ed835  ba6c000000             -mov edx, 0x6c
    cpu.edx = 108 /*0x6c*/;
    // 004ed83a  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004ed83b  89542404               -mov dword ptr [esp + 4], edx
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(4) /* 0x4 */) = cpu.edx;
    // 004ed83f  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004ed840  8b10                   -mov edx, dword ptr [eax]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax);
    // 004ed842  ff5258                 -call dword ptr [edx + 0x58]
    cpu.ip = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(88) /* 0x58 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004ed845  66a9ffff               +test ax, 0xffff
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg16>(cpu.ax & 65535 /*0xffff*/));
    // 004ed849  0f8575000000           -jne 0x4ed8c4
    if (!cpu.flags.zf)
    {
        goto L_0x004ed8c4;
    }
    // 004ed84f  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 004ed851  7406                   -je 0x4ed859
    if (cpu.flags.zf)
    {
        goto L_0x004ed859;
    }
    // 004ed853  8b44240c               -mov eax, dword ptr [esp + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(12) /* 0xc */);
    // 004ed857  8906                   -mov dword ptr [esi], eax
    app->getMemory<x86::reg32>(cpu.esi) = cpu.eax;
L_0x004ed859:
    // 004ed859  85ff                   +test edi, edi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edi & cpu.edi));
    // 004ed85b  7406                   -je 0x4ed863
    if (cpu.flags.zf)
    {
        goto L_0x004ed863;
    }
    // 004ed85d  8b442408               -mov eax, dword ptr [esp + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(8) /* 0x8 */);
    // 004ed861  8907                   -mov dword ptr [edi], eax
    app->getMemory<x86::reg32>(cpu.edi) = cpu.eax;
L_0x004ed863:
    // 004ed863  8b74247c               -mov esi, dword ptr [esp + 0x7c]
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(124) /* 0x7c */);
    // 004ed867  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 004ed869  7406                   -je 0x4ed871
    if (cpu.flags.zf)
    {
        goto L_0x004ed871;
    }
    // 004ed86b  8b442410               -mov eax, dword ptr [esp + 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(16) /* 0x10 */);
    // 004ed86f  8906                   -mov dword ptr [esi], eax
    app->getMemory<x86::reg32>(cpu.esi) = cpu.eax;
L_0x004ed871:
    // 004ed871  85ed                   +test ebp, ebp
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebp & cpu.ebp));
    // 004ed873  7407                   -je 0x4ed87c
    if (cpu.flags.zf)
    {
        goto L_0x004ed87c;
    }
    // 004ed875  8b442424               -mov eax, dword ptr [esp + 0x24]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(36) /* 0x24 */);
    // 004ed879  894500                 -mov dword ptr [ebp], eax
    app->getMemory<x86::reg32>(cpu.ebp) = cpu.eax;
L_0x004ed87c:
    // 004ed87c  85db                   +test ebx, ebx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & cpu.ebx));
    // 004ed87e  740f                   -je 0x4ed88f
    if (cpu.flags.zf)
    {
        goto L_0x004ed88f;
    }
    // 004ed880  837c245410             +cmp dword ptr [esp + 0x54], 0x10
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(84) /* 0x54 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(16 /*0x10*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004ed885  7411                   -je 0x4ed898
    if (cpu.flags.zf)
    {
        goto L_0x004ed898;
    }
    // 004ed887  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 004ed889  8a442454               -mov al, byte ptr [esp + 0x54]
    cpu.al = app->getMemory<x86::reg8>(cpu.esp + x86::reg32(84) /* 0x54 */);
    // 004ed88d  8903                   -mov dword ptr [ebx], eax
    app->getMemory<x86::reg32>(cpu.ebx) = cpu.eax;
L_0x004ed88f:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004ed88f  83c46c                 -add esp, 0x6c
    (cpu.esp) += x86::reg32(x86::sreg32(108 /*0x6c*/));
    // 004ed892  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ed893  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ed894  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ed895  c20800                 -ret 8
    cpu.esp += 4+8 /*0x8*/;
    return;
L_0x004ed898:
    // 004ed898  8b442458               -mov eax, dword ptr [esp + 0x58]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(88) /* 0x58 */);
    // 004ed89c  e8dfdfffff             -call 0x4eb880
    cpu.esp -= 4;
    sub_4eb880(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004ed8a1  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 004ed8a3  8b44245c               -mov eax, dword ptr [esp + 0x5c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(92) /* 0x5c */);
    // 004ed8a7  e8d4dfffff             -call 0x4eb880
    cpu.esp -= 4;
    sub_4eb880(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004ed8ac  01c6                   -add esi, eax
    (cpu.esi) += x86::reg32(x86::sreg32(cpu.eax));
    // 004ed8ae  8b442460               -mov eax, dword ptr [esp + 0x60]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(96) /* 0x60 */);
    // 004ed8b2  e8c9dfffff             -call 0x4eb880
    cpu.esp -= 4;
    sub_4eb880(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004ed8b7  01c6                   -add esi, eax
    (cpu.esi) += x86::reg32(x86::sreg32(cpu.eax));
    // 004ed8b9  8933                   -mov dword ptr [ebx], esi
    app->getMemory<x86::reg32>(cpu.ebx) = cpu.esi;
    // 004ed8bb  83c46c                 -add esp, 0x6c
    (cpu.esp) += x86::reg32(x86::sreg32(108 /*0x6c*/));
    // 004ed8be  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ed8bf  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ed8c0  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ed8c1  c20800                 -ret 8
    cpu.esp += 4+8 /*0x8*/;
    return;
L_0x004ed8c4:
    // 004ed8c4  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 004ed8c6  7406                   -je 0x4ed8ce
    if (cpu.flags.zf)
    {
        goto L_0x004ed8ce;
    }
    // 004ed8c8  c70600000000           -mov dword ptr [esi], 0
    app->getMemory<x86::reg32>(cpu.esi) = 0 /*0x0*/;
L_0x004ed8ce:
    // 004ed8ce  85ff                   +test edi, edi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edi & cpu.edi));
    // 004ed8d0  7406                   -je 0x4ed8d8
    if (cpu.flags.zf)
    {
        goto L_0x004ed8d8;
    }
    // 004ed8d2  c70700000000           -mov dword ptr [edi], 0
    app->getMemory<x86::reg32>(cpu.edi) = 0 /*0x0*/;
L_0x004ed8d8:
    // 004ed8d8  85db                   +test ebx, ebx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & cpu.ebx));
    // 004ed8da  7406                   -je 0x4ed8e2
    if (cpu.flags.zf)
    {
        goto L_0x004ed8e2;
    }
    // 004ed8dc  c70300000000           -mov dword ptr [ebx], 0
    app->getMemory<x86::reg32>(cpu.ebx) = 0 /*0x0*/;
L_0x004ed8e2:
    // 004ed8e2  8b4c247c               -mov ecx, dword ptr [esp + 0x7c]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(124) /* 0x7c */);
    // 004ed8e6  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    // 004ed8e8  7406                   -je 0x4ed8f0
    if (cpu.flags.zf)
    {
        goto L_0x004ed8f0;
    }
    // 004ed8ea  c70100000000           -mov dword ptr [ecx], 0
    app->getMemory<x86::reg32>(cpu.ecx) = 0 /*0x0*/;
L_0x004ed8f0:
    // 004ed8f0  85ed                   +test ebp, ebp
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebp & cpu.ebp));
    // 004ed8f2  749b                   -je 0x4ed88f
    if (cpu.flags.zf)
    {
        goto L_0x004ed88f;
    }
    // 004ed8f4  c7450000000000         -mov dword ptr [ebp], 0
    app->getMemory<x86::reg32>(cpu.ebp) = 0 /*0x0*/;
    // 004ed8fb  83c46c                 -add esp, 0x6c
    (cpu.esp) += x86::reg32(x86::sreg32(108 /*0x6c*/));
    // 004ed8fe  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ed8ff  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ed900  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ed901  c20800                 -ret 8
    cpu.esp += 4+8 /*0x8*/;
    return;
}

/* sub_4ed910: native, nfs3hp::dead::stub_0x4ed910 */

/* sub_4ed950: native, nfs3hp::dead::stub_0x4ed950 */

/* sub_4ed990: native, nfs3hp::dead::stub_0x4ed990 */

/* sub_4eda10: native, nfs3hp::dead::stub_0x4eda10 */

/* sub_4edb80: native, nfs3hp::dead::stub_0x4edb80 */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 */
void Application::sub_4edbc0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004edbc0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004edbc1  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004edbc2  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004edbc3  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004edbc4  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004edbc6  83ec08                 -sub esp, 8
    (cpu.esp) -= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 004edbc9  8b7514                 -mov esi, dword ptr [ebp + 0x14]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(20) /* 0x14 */);
    // 004edbcc  ba01000000             -mov edx, 1
    cpu.edx = 1 /*0x1*/;
    // 004edbd1  8b4518                 -mov eax, dword ptr [ebp + 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(24) /* 0x18 */);
    // 004edbd4  8b4e54                 -mov ecx, dword ptr [esi + 0x54]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(84) /* 0x54 */);
    // 004edbd7  8955f8                 -mov dword ptr [ebp - 8], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.edx;
    // 004edbda  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 004edbdd  83f910                 +cmp ecx, 0x10
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(16 /*0x10*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004edbe0  0f84be000000           -je 0x4edca4
    if (cpu.flags.zf)
    {
        goto L_0x004edca4;
    }
    // 004edbe6  0fb67e54               -movzx edi, byte ptr [esi + 0x54]
    cpu.edi = x86::reg32(app->getMemory<x86::reg8>(cpu.esi + x86::reg32(84) /* 0x54 */));
L_0x004edbea:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004edbea  83ff10                 +cmp edi, 0x10
    {
        x86::reg32 tmp1 = cpu.edi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(16 /*0x10*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004edbed  0f83d4000000           -jae 0x4edcc7
    if (!cpu.flags.cf)
    {
        goto L_0x004edcc7;
    }
    // 004edbf3  83ff08                 +cmp edi, 8
    {
        x86::reg32 tmp1 = cpu.edi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(8 /*0x8*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004edbf6  0f8305010000           -jae 0x4edd01
    if (!cpu.flags.cf)
    {
        goto L_0x004edd01;
    }
L_0x004edbfc:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004edbfc  8b5dfc                 -mov ebx, dword ptr [ebp - 4]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004edbff  85db                   +test ebx, ebx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & cpu.ebx));
    // 004edc01  0f848f000000           -je 0x4edc96
    if (cpu.flags.zf)
    {
        goto L_0x004edc96;
    }
    // 004edc07  837b1000               +cmp dword ptr [ebx + 0x10], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(16) /* 0x10 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004edc0b  0f8431010000           -je 0x4edd42
    if (cpu.flags.zf)
    {
        goto L_0x004edd42;
    }
    // 004edc11  a1a0099f00             -mov eax, dword ptr [0x9f09a0]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(10422688) /* 0x9f09a0 */);
    // 004edc16  3b4308                 +cmp eax, dword ptr [ebx + 8]
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(8) /* 0x8 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004edc19  0f8d23010000           -jge 0x4edd42
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004edd42;
    }
    // 004edc1f  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004edc21  89f3                   -mov ebx, esi
    cpu.ebx = cpu.esi;
    // 004edc23  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 004edc25  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004edc28  e873dcffff             -call 0x4eb8a0
    cpu.esp -= 4;
    sub_4eb8a0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004edc2d  8b4650                 -mov eax, dword ptr [esi + 0x50]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(80) /* 0x50 */);
    // 004edc30  8a4e68                 -mov cl, byte ptr [esi + 0x68]
    cpu.cl = app->getMemory<x86::reg8>(cpu.esi + x86::reg32(104) /* 0x68 */);
    // 004edc33  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004edc34  f6c110                 +test cl, 0x10
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.cl & 16 /*0x10*/));
    // 004edc37  0f84e7000000           -je 0x4edd24
    if (cpu.flags.zf)
    {
        goto L_0x004edd24;
    }
    // 004edc3d  b846000000             -mov eax, 0x46
    cpu.eax = 70 /*0x46*/;
L_0x004edc42:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004edc42  8a6e6a                 -mov ch, byte ptr [esi + 0x6a]
    cpu.ch = app->getMemory<x86::reg8>(cpu.esi + x86::reg32(106) /* 0x6a */);
    // 004edc45  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004edc46  f6c520                 +test ch, 0x20
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.ch & 32 /*0x20*/));
    // 004edc49  0f84df000000           -je 0x4edd2e
    if (cpu.flags.zf)
    {
        goto L_0x004edd2e;
    }
    // 004edc4f  b858000000             -mov eax, 0x58
    cpu.eax = 88 /*0x58*/;
L_0x004edc54:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004edc54  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004edc55  8b4614                 -mov eax, dword ptr [esi + 0x14]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(20) /* 0x14 */);
    // 004edc58  40                     -inc eax
    (cpu.eax)++;
    // 004edc59  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004edc5a  8b5610                 -mov edx, dword ptr [esi + 0x10]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(16) /* 0x10 */);
    // 004edc5d  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004edc5e  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004edc5f  8b4e54                 -mov ecx, dword ptr [esi + 0x54]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(84) /* 0x54 */);
    // 004edc62  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004edc63  8b5e08                 -mov ebx, dword ptr [esi + 8]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(8) /* 0x8 */);
    // 004edc66  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004edc67  8b7e0c                 -mov edi, dword ptr [esi + 0xc]
    cpu.edi = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 004edc6a  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004edc6d  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004edc6e  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004edc70  0f84c2000000           -je 0x4edd38
    if (cpu.flags.zf)
    {
        goto L_0x004edd38;
    }
    // 004edc76  b820000000             -mov eax, 0x20
    cpu.eax = 32 /*0x20*/;
L_0x004edc7b:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004edc7b  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004edc7c  68b4c15400             -push 0x54c1b4
    app->getMemory<x86::reg32>(cpu.esp-4) = 5554612 /*0x54c1b4*/;
    cpu.esp -= 4;
    // 004edc81  6a08                   -push 8
    app->getMemory<x86::reg32>(cpu.esp-4) = 8 /*0x8*/;
    cpu.esp -= 4;
    // 004edc83  68d44e5600             -push 0x564ed4
    app->getMemory<x86::reg32>(cpu.esp-4) = 5656276 /*0x564ed4*/;
    cpu.esp -= 4;
    // 004edc88  e8c3330100             -call 0x501050
    cpu.esp -= 4;
    nfs3hp::ea::fileReport(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004edc8d  83c434                 -add esp, 0x34
    (cpu.esp) += x86::reg32(x86::sreg32(52 /*0x34*/));
L_0x004edc90:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004edc90  ff05a0099f00           -inc dword ptr [0x9f09a0]
    (app->getMemory<x86::reg32>(x86::reg32(10422688) /* 0x9f09a0 */))++;
L_0x004edc96:
    // 004edc96  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 004edc9b  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004edc9d  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004edc9e  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004edc9f  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004edca0  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004edca1  c20800                 -ret 8
    cpu.esp += 4+8 /*0x8*/;
    return;
L_0x004edca4:
    // 004edca4  8b4658                 -mov eax, dword ptr [esi + 0x58]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(88) /* 0x58 */);
    // 004edca7  e8d4dbffff             -call 0x4eb880
    cpu.esp -= 4;
    sub_4eb880(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004edcac  89c7                   -mov edi, eax
    cpu.edi = cpu.eax;
    // 004edcae  8b465c                 -mov eax, dword ptr [esi + 0x5c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(92) /* 0x5c */);
    // 004edcb1  e8cadbffff             -call 0x4eb880
    cpu.esp -= 4;
    sub_4eb880(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004edcb6  01c7                   -add edi, eax
    (cpu.edi) += x86::reg32(x86::sreg32(cpu.eax));
    // 004edcb8  8b4660                 -mov eax, dword ptr [esi + 0x60]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(96) /* 0x60 */);
    // 004edcbb  e8c0dbffff             -call 0x4eb880
    cpu.esp -= 4;
    sub_4eb880(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004edcc0  01c7                   +add edi, eax
    {
        x86::reg32& tmp1 = cpu.edi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.eax));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 004edcc2  e923ffffff             -jmp 0x4edbea
    goto L_0x004edbea;
L_0x004edcc7:
    // 004edcc7  770c                   -ja 0x4edcd5
    if (!cpu.flags.cf && !cpu.flags.zf)
    {
        goto L_0x004edcd5;
    }
    // 004edcc9  800da4099f0004         +or byte ptr [0x9f09a4], 4
    cpu.clear_co();
    cpu.set_szp((app->getMemory<x86::reg8>(x86::reg32(10422692) /* 0x9f09a4 */) |= x86::reg8(x86::sreg8(4 /*0x4*/))));
    // 004edcd0  e927ffffff             -jmp 0x4edbfc
    goto L_0x004edbfc;
L_0x004edcd5:
    // 004edcd5  83ff18                 +cmp edi, 0x18
    {
        x86::reg32 tmp1 = cpu.edi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(24 /*0x18*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004edcd8  0f821effffff           -jb 0x4edbfc
    if (cpu.flags.cf)
    {
        goto L_0x004edbfc;
    }
    // 004edcde  770c                   -ja 0x4edcec
    if (!cpu.flags.cf && !cpu.flags.zf)
    {
        goto L_0x004edcec;
    }
    // 004edce0  800da4099f0008         +or byte ptr [0x9f09a4], 8
    cpu.clear_co();
    cpu.set_szp((app->getMemory<x86::reg8>(x86::reg32(10422692) /* 0x9f09a4 */) |= x86::reg8(x86::sreg8(8 /*0x8*/))));
    // 004edce7  e910ffffff             -jmp 0x4edbfc
    goto L_0x004edbfc;
L_0x004edcec:
    // 004edcec  83ff20                 +cmp edi, 0x20
    {
        x86::reg32 tmp1 = cpu.edi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(32 /*0x20*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004edcef  0f8507ffffff           -jne 0x4edbfc
    if (!cpu.flags.zf)
    {
        goto L_0x004edbfc;
    }
    // 004edcf5  800da4099f0010         +or byte ptr [0x9f09a4], 0x10
    cpu.clear_co();
    cpu.set_szp((app->getMemory<x86::reg8>(x86::reg32(10422692) /* 0x9f09a4 */) |= x86::reg8(x86::sreg8(16 /*0x10*/))));
    // 004edcfc  e9fbfeffff             -jmp 0x4edbfc
    goto L_0x004edbfc;
L_0x004edd01:
    // 004edd01  770c                   -ja 0x4edd0f
    if (!cpu.flags.cf && !cpu.flags.zf)
    {
        goto L_0x004edd0f;
    }
    // 004edd03  800da4099f0001         +or byte ptr [0x9f09a4], 1
    cpu.clear_co();
    cpu.set_szp((app->getMemory<x86::reg8>(x86::reg32(10422692) /* 0x9f09a4 */) |= x86::reg8(x86::sreg8(1 /*0x1*/))));
    // 004edd0a  e9edfeffff             -jmp 0x4edbfc
    goto L_0x004edbfc;
L_0x004edd0f:
    // 004edd0f  83ff0f                 +cmp edi, 0xf
    {
        x86::reg32 tmp1 = cpu.edi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(15 /*0xf*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004edd12  0f85e4feffff           -jne 0x4edbfc
    if (!cpu.flags.zf)
    {
        goto L_0x004edbfc;
    }
    // 004edd18  800da4099f0002         +or byte ptr [0x9f09a4], 2
    cpu.clear_co();
    cpu.set_szp((app->getMemory<x86::reg8>(x86::reg32(10422692) /* 0x9f09a4 */) |= x86::reg8(x86::sreg8(2 /*0x2*/))));
    // 004edd1f  e9d8feffff             -jmp 0x4edbfc
    goto L_0x004edbfc;
L_0x004edd24:
    // 004edd24  b844000000             -mov eax, 0x44
    cpu.eax = 68 /*0x44*/;
    // 004edd29  e914ffffff             -jmp 0x4edc42
    goto L_0x004edc42;
L_0x004edd2e:
    // 004edd2e  b84e000000             -mov eax, 0x4e
    cpu.eax = 78 /*0x4e*/;
    // 004edd33  e91cffffff             -jmp 0x4edc54
    goto L_0x004edc54;
L_0x004edd38:
    // 004edd38  b821000000             -mov eax, 0x21
    cpu.eax = 33 /*0x21*/;
    // 004edd3d  e939ffffff             -jmp 0x4edc7b
    goto L_0x004edc7b;
L_0x004edd42:
    // 004edd42  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004edd45  83781000               +cmp dword ptr [eax + 0x10], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(16) /* 0x10 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004edd49  0f8441ffffff           -je 0x4edc90
    if (cpu.flags.zf)
    {
        goto L_0x004edc90;
    }
    // 004edd4f  8b55fc                 -mov edx, dword ptr [ebp - 4]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004edd52  a1a0099f00             -mov eax, dword ptr [0x9f09a0]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(10422688) /* 0x9f09a0 */);
    // 004edd57  3b4208                 +cmp eax, dword ptr [edx + 8]
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.edx + x86::reg32(8) /* 0x8 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004edd5a  0f8c30ffffff           -jl 0x4edc90
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004edc90;
    }
    // 004edd60  68ecc15400             -push 0x54c1ec
    app->getMemory<x86::reg32>(cpu.esp-4) = 5554668 /*0x54c1ec*/;
    cpu.esp -= 4;
    // 004edd65  6a01                   -push 1
    app->getMemory<x86::reg32>(cpu.esp-4) = 1 /*0x1*/;
    cpu.esp -= 4;
    // 004edd67  68d44e5600             -push 0x564ed4
    app->getMemory<x86::reg32>(cpu.esp-4) = 5656276 /*0x564ed4*/;
    cpu.esp -= 4;
    // 004edd6c  e8df320100             -call 0x501050
    cpu.esp -= 4;
    nfs3hp::ea::fileReport(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004edd71  83c40c                 -add esp, 0xc
    (cpu.esp) += x86::reg32(x86::sreg32(12 /*0xc*/));
    // 004edd74  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 004edd76  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004edd78  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004edd79  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004edd7a  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004edd7b  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004edd7c  c20800                 -ret 8
    cpu.esp += 4+8 /*0x8*/;
    return;
}

/* sub_4edd80: native, nfs3hp::watcom::open_flags */

/* sub_4edebc: native, nfs3hp::watcom::doopen */

/* sub_4edfa4: native, nfs3hp::watcom::fsopen */

/* sub_4edfe8: native, nfs3hp::watcom::fopen */

/* sub_4edff4: native, nfs3hp::dead::stub_0x4edff4 */

/* sub_4ee07c: native, nfs3hp::dead::stub_0x4ee07c */

/* sub_4ee100: native, nfs3hp::watcom::fclose */

/* sub_4ee144: native, nfs3hp::watcom::shutdown_stream */

/* sub_4ee15c: native, nfs3hp::watcom::hexDigit */

/* sub_4ee168: native, nfs3hp::watcom::MkTmpFile */

/* sub_4ee214: native, nfs3hp::watcom::doclose */

/* sub_4ee2e0: native, nfs3hp::watcom::remove */

/* sub_4ee2f0: native, nfs3hp::watcom::strrchr */

/* sub_4ee310: native, nfs3hp::watcom::strcmp */

/* sub_4ee3c0: native, nfs3hp::watcom::chmod */

/* sub_4ee400: native, nfs3hp::watcom::rmdir */

/* sub_4ee420: native, nfs3hp::watcom::ftell */

/* sub_4ee480: native, nfs3hp::watcom::med3 */

/* sub_4ee4d0: native, nfs3hp::watcom::byteswap */

/* sub_4ee4f8: native, nfs3hp::watcom::qsort */

/* sub_4eeae0: native, nfs3hp::load::savefileadr */

/* sub_4eebb0: native, nfs3hp::load::savefileadrQuietly */

/* sub_4eebd0: native, nfs3hp::watcom::fwrite */

/* sub_4eede0: native, nfs3hp::watcom::toupper */

/* sub_4eedf0: native, nfs3hp::watcom::strncat */

/* align: skip 0x00 */
void Application::sub_4eee30(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004eee30  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004eee31  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004eee32  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004eee33  83ec28                 -sub esp, 0x28
    (cpu.esp) -= x86::reg32(x86::sreg32(40 /*0x28*/));
    // 004eee36  89c7                   -mov edi, eax
    cpu.edi = cpu.eax;
    // 004eee38  89542420               -mov dword ptr [esp + 0x20], edx
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(32) /* 0x20 */) = cpu.edx;
    // 004eee3c  895c2424               -mov dword ptr [esp + 0x24], ebx
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(36) /* 0x24 */) = cpu.ebx;
    // 004eee40  85db                   +test ebx, ebx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & cpu.ebx));
    // 004eee42  0f8478000000           -je 0x4eeec0
    if (cpu.flags.zf)
    {
        goto L_0x004eeec0;
    }
L_0x004eee48:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004eee48  8b5c2424               -mov ebx, dword ptr [esp + 0x24]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(36) /* 0x24 */);
    // 004eee4c  85db                   +test ebx, ebx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & cpu.ebx));
    // 004eee4e  0f857a000000           -jne 0x4eeece
    if (!cpu.flags.zf)
    {
        goto L_0x004eeece;
    }
    // 004eee54  c744242408000000       -mov dword ptr [esp + 0x24], 8
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(36) /* 0x24 */) = 8 /*0x8*/;
L_0x004eee5c:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004eee5c  8b6c2424               -mov ebp, dword ptr [esp + 0x24]
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(36) /* 0x24 */);
L_0x004eee60:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004eee60  85ff                   +test edi, edi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edi & cpu.edi));
    // 004eee62  7c08                   -jl 0x4eee6c
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004eee6c;
    }
    // 004eee64  81ff00400000           +cmp edi, 0x4000
    {
        x86::reg32 tmp1 = cpu.edi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(16384 /*0x4000*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004eee6a  7e6e                   -jle 0x4eeeda
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004eeeda;
    }
L_0x004eee6c:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004eee6c  837c243800             +cmp dword ptr [esp + 0x38], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(56) /* 0x38 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004eee71  7442                   -je 0x4eeeb5
    if (cpu.flags.zf)
    {
        goto L_0x004eeeb5;
    }
    // 004eee73  6800200000             -push 0x2000
    app->getMemory<x86::reg32>(cpu.esp-4) = 8192 /*0x2000*/;
    cpu.esp -= 4;
    // 004eee78  6800400000             -push 0x4000
    app->getMemory<x86::reg32>(cpu.esp-4) = 16384 /*0x4000*/;
    cpu.esp -= 4;
    // 004eee7d  8b54242c               -mov edx, dword ptr [esp + 0x2c]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(44) /* 0x2c */);
    // 004eee81  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004eee82  8b4c242c               -mov ecx, dword ptr [esp + 0x2c]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(44) /* 0x2c */);
    // 004eee86  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004eee87  beb4c25400             -mov esi, 0x54c2b4
    cpu.esi = 5554868 /*0x54c2b4*/;
    // 004eee8c  bdc4c25400             -mov ebp, 0x54c2c4
    cpu.ebp = 5554884 /*0x54c2c4*/;
    // 004eee91  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004eee92  b854000000             -mov eax, 0x54
    cpu.eax = 84 /*0x54*/;
    // 004eee97  893590215500           -mov dword ptr [0x552190], esi
    app->getMemory<x86::reg32>(x86::reg32(5579152) /* 0x552190 */) = cpu.esi;
    // 004eee9d  68d8c25400             -push 0x54c2d8
    app->getMemory<x86::reg32>(cpu.esp-4) = 5554904 /*0x54c2d8*/;
    cpu.esp -= 4;
    // 004eeea2  892d94215500           -mov dword ptr [0x552194], ebp
    app->getMemory<x86::reg32>(x86::reg32(5579156) /* 0x552194 */) = cpu.ebp;
    // 004eeea8  a398215500             -mov dword ptr [0x552198], eax
    app->getMemory<x86::reg32>(x86::reg32(5579160) /* 0x552198 */) = cpu.eax;
    // 004eeead  e85e21f1ff             -call 0x401010
    cpu.esp -= 4;
    nfs3hp::Error(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004eeeb2  83c418                 -add esp, 0x18
    (cpu.esp) += x86::reg32(x86::sreg32(24 /*0x18*/));
L_0x004eeeb5:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004eeeb5  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 004eeeb7  83c428                 +add esp, 0x28
    {
        x86::reg32& tmp1 = cpu.esp;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(40 /*0x28*/));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 004eeeba  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004eeebb  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004eeebc  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004eeebd  c20400                 -ret 4
    cpu.esp += 4+4 /*0x4*/;
    return;
L_0x004eeec0:
    // 004eeec0  a18c435600             -mov eax, dword ptr [0x56438c]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5653388) /* 0x56438c */);
    // 004eeec5  89442424               -mov dword ptr [esp + 0x24], eax
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(36) /* 0x24 */) = cpu.eax;
    // 004eeec9  e97affffff             -jmp 0x4eee48
    goto L_0x004eee48;
L_0x004eeece:
    // 004eeece  83fb0f                 +cmp ebx, 0xf
    {
        x86::reg32 tmp1 = cpu.ebx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(15 /*0xf*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004eeed1  7589                   -jne 0x4eee5c
    if (!cpu.flags.zf)
    {
        goto L_0x004eee5c;
    }
    // 004eeed3  bd10000000             -mov ebp, 0x10
    cpu.ebp = 16 /*0x10*/;
    // 004eeed8  eb86                   -jmp 0x4eee60
    goto L_0x004eee60;
L_0x004eeeda:
    // 004eeeda  8b442420               -mov eax, dword ptr [esp + 0x20]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(32) /* 0x20 */);
    // 004eeede  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004eeee0  7c8a                   -jl 0x4eee6c
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004eee6c;
    }
    // 004eeee2  3d00200000             +cmp eax, 0x2000
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(8192 /*0x2000*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004eeee7  7f83                   -jg 0x4eee6c
    if (!cpu.flags.zf && (cpu.flags.sf == cpu.flags.of))
    {
        goto L_0x004eee6c;
    }
    // 004eeee9  8b442424               -mov eax, dword ptr [esp + 0x24]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(36) /* 0x24 */);
    // 004eeeed  e8dea90100             -call 0x5098d0
    cpu.esp -= 4;
    sub_5098d0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004eeef2  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004eeef4  754a                   -jne 0x4eef40
    if (!cpu.flags.zf)
    {
        goto L_0x004eef40;
    }
    // 004eeef6  837c243800             +cmp dword ptr [esp + 0x38], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(56) /* 0x38 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004eeefb  74b8                   -je 0x4eeeb5
    if (cpu.flags.zf)
    {
        goto L_0x004eeeb5;
    }
    // 004eeefd  8b542424               -mov edx, dword ptr [esp + 0x24]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(36) /* 0x24 */);
    // 004eef01  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004eef02  8b4c2424               -mov ecx, dword ptr [esp + 0x24]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(36) /* 0x24 */);
    // 004eef06  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004eef07  beb4c25400             -mov esi, 0x54c2b4
    cpu.esi = 5554868 /*0x54c2b4*/;
    // 004eef0c  bdc4c25400             -mov ebp, 0x54c2c4
    cpu.ebp = 5554884 /*0x54c2c4*/;
    // 004eef11  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004eef12  b85f000000             -mov eax, 0x5f
    cpu.eax = 95 /*0x5f*/;
    // 004eef17  893590215500           -mov dword ptr [0x552190], esi
    app->getMemory<x86::reg32>(x86::reg32(5579152) /* 0x552190 */) = cpu.esi;
    // 004eef1d  6828c35400             -push 0x54c328
    app->getMemory<x86::reg32>(cpu.esp-4) = 5554984 /*0x54c328*/;
    cpu.esp -= 4;
    // 004eef22  892d94215500           -mov dword ptr [0x552194], ebp
    app->getMemory<x86::reg32>(x86::reg32(5579156) /* 0x552194 */) = cpu.ebp;
    // 004eef28  a398215500             -mov dword ptr [0x552198], eax
    app->getMemory<x86::reg32>(x86::reg32(5579160) /* 0x552198 */) = cpu.eax;
    // 004eef2d  e8de20f1ff             -call 0x401010
    cpu.esp -= 4;
    nfs3hp::Error(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004eef32  83c410                 -add esp, 0x10
    (cpu.esp) += x86::reg32(x86::sreg32(16 /*0x10*/));
    // 004eef35  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 004eef37  83c428                 -add esp, 0x28
    (cpu.esp) += x86::reg32(x86::sreg32(40 /*0x28*/));
    // 004eef3a  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004eef3b  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004eef3c  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004eef3d  c20400                 -ret 4
    cpu.esp += 4+4 /*0x4*/;
    return;
L_0x004eef40:
    // 004eef40  89fa                   -mov edx, edi
    cpu.edx = cpu.edi;
    // 004eef42  0fafd5                 -imul edx, ebp
    cpu.edx = x86::reg32(x86::sreg64(x86::sreg32(cpu.edx)) * x86::sreg64(x86::sreg32(cpu.ebp)));
    // 004eef45  83c207                 -add edx, 7
    (cpu.edx) += x86::reg32(x86::sreg32(7 /*0x7*/));
    // 004eef48  80e2f8                 -and dl, 0xf8
    cpu.dl &= x86::reg8(x86::sreg8(248 /*0xf8*/));
    // 004eef4b  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004eef4d  c1fa1f                 -sar edx, 0x1f
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (31 /*0x1f*/ % 32));
    // 004eef50  f7fd                   -idiv ebp
    {
        x86::sreg64 tmp = x86::sreg64(cpu.edx_eax);
        x86::sreg32 d = x86::sreg32(cpu.ebp);
        cpu.edx_eax = x86::reg64(tmp / d);
        cpu.edx = x86::reg32(tmp % d);
    }
    // 004eef52  0fafc5                 -imul eax, ebp
    cpu.eax = x86::reg32(x86::sreg64(x86::sreg32(cpu.eax)) * x86::sreg64(x86::sreg32(cpu.ebp)));
    // 004eef55  c1f803                 -sar eax, 3
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (3 /*0x3*/ % 32));
    // 004eef58  8b5c2420               -mov ebx, dword ptr [esp + 0x20]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(32) /* 0x20 */);
    // 004eef5c  8944241c               -mov dword ptr [esp + 0x1c], eax
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(28) /* 0x1c */) = cpu.eax;
    // 004eef60  0fafc3                 -imul eax, ebx
    cpu.eax = x86::reg32(x86::sreg64(x86::sreg32(cpu.eax)) * x86::sreg64(x86::sreg32(cpu.ebx)));
    // 004eef63  8b742424               -mov esi, dword ptr [esp + 0x24]
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(36) /* 0x24 */);
    // 004eef67  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004eef68  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004eef69  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004eef6a  83c048                 -add eax, 0x48
    (cpu.eax) += x86::reg32(x86::sreg32(72 /*0x48*/));
    // 004eef6d  687cc35400             -push 0x54c37c
    app->getMemory<x86::reg32>(cpu.esp-4) = 5555068 /*0x54c37c*/;
    cpu.esp -= 4;
    // 004eef72  89442424               -mov dword ptr [esp + 0x24], eax
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(36) /* 0x24 */) = cpu.eax;
    // 004eef76  8d442410               -lea eax, [esp + 0x10]
    cpu.eax = x86::reg32(cpu.esp + x86::reg32(16) /* 0x10 */);
    // 004eef7a  be6a000000             -mov esi, 0x6a
    cpu.esi = 106 /*0x6a*/;
    // 004eef7f  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004eef80  bab4c25400             -mov edx, 0x54c2b4
    cpu.edx = 5554868 /*0x54c2b4*/;
    // 004eef85  bbc4c25400             -mov ebx, 0x54c2c4
    cpu.ebx = 5554884 /*0x54c2c4*/;
    // 004eef8a  e80107ffff             -call 0x4df690
    cpu.esp -= 4;
    nfs3hp::watcom::sprintf(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004eef8f  8d442414               -lea eax, [esp + 0x14]
    cpu.eax = x86::reg32(cpu.esp + x86::reg32(20) /* 0x14 */);
    // 004eef93  83c414                 -add esp, 0x14
    (cpu.esp) += x86::reg32(x86::sreg32(20 /*0x14*/));
    // 004eef96  891590215500           -mov dword ptr [0x552190], edx
    app->getMemory<x86::reg32>(x86::reg32(5579152) /* 0x552190 */) = cpu.edx;
    // 004eef9c  891d94215500           -mov dword ptr [0x552194], ebx
    app->getMemory<x86::reg32>(x86::reg32(5579156) /* 0x552194 */) = cpu.ebx;
    // 004eefa2  8b542414               -mov edx, dword ptr [esp + 0x14]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(20) /* 0x14 */);
    // 004eefa6  89cb                   -mov ebx, ecx
    cpu.ebx = cpu.ecx;
    // 004eefa8  893598215500           -mov dword ptr [0x552198], esi
    app->getMemory<x86::reg32>(x86::reg32(5579160) /* 0x552198 */) = cpu.esi;
    // 004eefae  e86d26ffff             -call 0x4e1620
    cpu.esp -= 4;
    nfs3hp::ea::reservememadr(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004eefb3  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 004eefb5  89442410               -mov dword ptr [esp + 0x10], eax
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(16) /* 0x10 */) = cpu.eax;
    // 004eefb9  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004eefbb  7567                   -jne 0x4ef024
    if (!cpu.flags.zf)
    {
        goto L_0x004ef024;
    }
    // 004eefbd  837c243800             +cmp dword ptr [esp + 0x38], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(56) /* 0x38 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004eefc2  0f84edfeffff           -je 0x4eeeb5
    if (cpu.flags.zf)
    {
        goto L_0x004eeeb5;
    }
    // 004eefc8  b9b4c25400             -mov ecx, 0x54c2b4
    cpu.ecx = 5554868 /*0x54c2b4*/;
    // 004eefcd  bbc4c25400             -mov ebx, 0x54c2c4
    cpu.ebx = 5554884 /*0x54c2c4*/;
    // 004eefd2  be70000000             -mov esi, 0x70
    cpu.esi = 112 /*0x70*/;
    // 004eefd7  8b2d00445600           -mov ebp, dword ptr [0x564400]
    cpu.ebp = app->getMemory<x86::reg32>(x86::reg32(5653504) /* 0x564400 */);
    // 004eefdd  890d90215500           -mov dword ptr [0x552190], ecx
    app->getMemory<x86::reg32>(x86::reg32(5579152) /* 0x552190 */) = cpu.ecx;
    // 004eefe3  891d94215500           -mov dword ptr [0x552194], ebx
    app->getMemory<x86::reg32>(x86::reg32(5579156) /* 0x552194 */) = cpu.ebx;
    // 004eefe9  45                     -inc ebp
    (cpu.ebp)++;
    // 004eefea  893598215500           -mov dword ptr [0x552198], esi
    app->getMemory<x86::reg32>(x86::reg32(5579160) /* 0x552198 */) = cpu.esi;
    // 004eeff0  892d00445600           -mov dword ptr [0x564400], ebp
    app->getMemory<x86::reg32>(x86::reg32(5653504) /* 0x564400 */) = cpu.ebp;
    // 004eeff6  e88525ffff             -call 0x4e1580
    cpu.esp -= 4;
    nfs3hp::ea::largestmem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004eeffb  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004eeffc  8b442418               -mov eax, dword ptr [esp + 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(24) /* 0x18 */);
    // 004ef000  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004ef001  8b54242c               -mov edx, dword ptr [esp + 0x2c]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(44) /* 0x2c */);
    // 004ef005  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004ef006  8b4c242c               -mov ecx, dword ptr [esp + 0x2c]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(44) /* 0x2c */);
    // 004ef00a  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004ef00b  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004ef00c  6888c35400             -push 0x54c388
    app->getMemory<x86::reg32>(cpu.esp-4) = 5555080 /*0x54c388*/;
    cpu.esp -= 4;
    // 004ef011  e8fa1ff1ff             -call 0x401010
    cpu.esp -= 4;
    nfs3hp::Error(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004ef016  83c418                 -add esp, 0x18
    (cpu.esp) += x86::reg32(x86::sreg32(24 /*0x18*/));
    // 004ef019  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 004ef01b  83c428                 -add esp, 0x28
    (cpu.esp) += x86::reg32(x86::sreg32(40 /*0x28*/));
    // 004ef01e  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef01f  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef020  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef021  c20400                 -ret 4
    cpu.esp += 4+4 /*0x4*/;
    return;
L_0x004ef024:
    // 004ef024  ba48000000             -mov edx, 0x48
    cpu.edx = 72 /*0x48*/;
    // 004ef029  e8de16ffff             -call 0x4e070c
    cpu.esp -= 4;
    nfs3hp::fillZero(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004ef02e  89742418               -mov dword ptr [esp + 0x18], esi
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(24) /* 0x18 */) = cpu.esi;
    // 004ef032  8b442424               -mov eax, dword ptr [esp + 0x24]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(36) /* 0x24 */);
    // 004ef036  8d5638                 -lea edx, [esi + 0x38]
    cpu.edx = x86::reg32(cpu.esi + x86::reg32(56) /* 0x38 */);
    // 004ef039  e892a80100             -call 0x5098d0
    cpu.esp -= 4;
    sub_5098d0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004ef03e  c60200                 -mov byte ptr [edx], 0
    app->getMemory<x86::reg8>(cpu.edx) = 0 /*0x0*/;
    // 004ef041  25ff000000             -and eax, 0xff
    cpu.eax &= x86::reg32(x86::sreg32(255 /*0xff*/));
    // 004ef046  8b0a                   -mov ecx, dword ptr [edx]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.edx);
    // 004ef048  66897a04               -mov word ptr [edx + 4], di
    app->getMemory<x86::reg16>(cpu.edx + x86::reg32(4) /* 0x4 */) = cpu.di;
    // 004ef04c  09c1                   -or ecx, eax
    cpu.ecx |= x86::reg32(x86::sreg32(cpu.eax));
    // 004ef04e  8b442420               -mov eax, dword ptr [esp + 0x20]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(32) /* 0x20 */);
    // 004ef052  890a                   -mov dword ptr [edx], ecx
    app->getMemory<x86::reg32>(cpu.edx) = cpu.ecx;
    // 004ef054  66894206               -mov word ptr [edx + 6], ax
    app->getMemory<x86::reg16>(cpu.edx + x86::reg32(6) /* 0x6 */) = cpu.ax;
    // 004ef058  c706444e4957           -mov dword ptr [esi], 0x57494e44
    app->getMemory<x86::reg32>(cpu.esi) = 1464421956 /*0x57494e44*/;
    // 004ef05e  897e04                 -mov dword ptr [esi + 4], edi
    app->getMemory<x86::reg32>(cpu.esi + x86::reg32(4) /* 0x4 */) = cpu.edi;
    // 004ef061  8b442420               -mov eax, dword ptr [esp + 0x20]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(32) /* 0x20 */);
    // 004ef065  897e14                 -mov dword ptr [esi + 0x14], edi
    app->getMemory<x86::reg32>(cpu.esi + x86::reg32(20) /* 0x14 */) = cpu.edi;
    // 004ef068  894608                 -mov dword ptr [esi + 8], eax
    app->getMemory<x86::reg32>(cpu.esi + x86::reg32(8) /* 0x8 */) = cpu.eax;
    // 004ef06b  894618                 -mov dword ptr [esi + 0x18], eax
    app->getMemory<x86::reg32>(cpu.esi + x86::reg32(24) /* 0x18 */) = cpu.eax;
    // 004ef06e  8a442424               -mov al, byte ptr [esp + 0x24]
    cpu.al = app->getMemory<x86::reg8>(cpu.esp + x86::reg32(36) /* 0x24 */);
    // 004ef072  88461c                 -mov byte ptr [esi + 0x1c], al
    app->getMemory<x86::reg8>(cpu.esi + x86::reg32(28) /* 0x1c */) = cpu.al;
    // 004ef075  8b02                   -mov eax, dword ptr [edx]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edx);
    // 004ef077  25ff000000             -and eax, 0xff
    cpu.eax &= x86::reg32(x86::sreg32(255 /*0xff*/));
    // 004ef07c  895620                 -mov dword ptr [esi + 0x20], edx
    app->getMemory<x86::reg32>(cpu.esi + x86::reg32(32) /* 0x20 */) = cpu.edx;
    // 004ef07f  8b1d80835600           -mov ebx, dword ptr [0x568380]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(5669760) /* 0x568380 */);
    // 004ef085  88461d                 -mov byte ptr [esi + 0x1d], al
    app->getMemory<x86::reg8>(cpu.esi + x86::reg32(29) /* 0x1d */) = cpu.al;
    // 004ef088  85db                   +test ebx, ebx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & cpu.ebx));
    // 004ef08a  7557                   -jne 0x4ef0e3
    if (!cpu.flags.zf)
    {
        goto L_0x004ef0e3;
    }
    // 004ef08c  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004ef08e  8b542438               -mov edx, dword ptr [esp + 0x38]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(56) /* 0x38 */);
    // 004ef092  e8f927ffff             -call 0x4e1890
    cpu.esp -= 4;
    nfs3hp::ea::purgememadr(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004ef097  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 004ef099  0f8416feffff           -je 0x4eeeb5
    if (cpu.flags.zf)
    {
        goto L_0x004eeeb5;
    }
    // 004ef09f  8b6c2424               -mov ebp, dword ptr [esp + 0x24]
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(36) /* 0x24 */);
    // 004ef0a3  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004ef0a4  8b442424               -mov eax, dword ptr [esp + 0x24]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(36) /* 0x24 */);
    // 004ef0a8  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004ef0a9  b9b4c25400             -mov ecx, 0x54c2b4
    cpu.ecx = 5554868 /*0x54c2b4*/;
    // 004ef0ae  bbc4c25400             -mov ebx, 0x54c2c4
    cpu.ebx = 5554884 /*0x54c2c4*/;
    // 004ef0b3  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004ef0b4  be8b000000             -mov esi, 0x8b
    cpu.esi = 139 /*0x8b*/;
    // 004ef0b9  890d90215500           -mov dword ptr [0x552190], ecx
    app->getMemory<x86::reg32>(x86::reg32(5579152) /* 0x552190 */) = cpu.ecx;
    // 004ef0bf  68d8c35400             -push 0x54c3d8
    app->getMemory<x86::reg32>(cpu.esp-4) = 5555160 /*0x54c3d8*/;
    cpu.esp -= 4;
    // 004ef0c4  891d94215500           -mov dword ptr [0x552194], ebx
    app->getMemory<x86::reg32>(x86::reg32(5579156) /* 0x552194 */) = cpu.ebx;
    // 004ef0ca  893598215500           -mov dword ptr [0x552198], esi
    app->getMemory<x86::reg32>(x86::reg32(5579160) /* 0x552198 */) = cpu.esi;
    // 004ef0d0  e83b1ff1ff             -call 0x401010
    cpu.esp -= 4;
    nfs3hp::Error(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004ef0d5  83c410                 -add esp, 0x10
    (cpu.esp) += x86::reg32(x86::sreg32(16 /*0x10*/));
    // 004ef0d8  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 004ef0da  83c428                 -add esp, 0x28
    (cpu.esp) += x86::reg32(x86::sreg32(40 /*0x28*/));
    // 004ef0dd  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef0de  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef0df  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef0e0  c20400                 -ret 4
    cpu.esp += 4+4 /*0x4*/;
    return;
L_0x004ef0e3:
    // 004ef0e3  8b44241c               -mov eax, dword ptr [esp + 0x1c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(28) /* 0x1c */);
    // 004ef0e7  8b4c2420               -mov ecx, dword ptr [esp + 0x20]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(32) /* 0x20 */);
    // 004ef0eb  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
    // 004ef0ed  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004ef0ef  894628                 -mov dword ptr [esi + 0x28], eax
    app->getMemory<x86::reg32>(cpu.esi + x86::reg32(40) /* 0x28 */) = cpu.eax;
    // 004ef0f2  b810000000             -mov eax, 0x10
    cpu.eax = 16 /*0x10*/;
    // 004ef0f7  e834a90100             -call 0x509a30
    cpu.esp -= 4;
    sub_509a30(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004ef0fc  bb03000000             -mov ebx, 3
    cpu.ebx = 3 /*0x3*/;
    // 004ef101  89f9                   -mov ecx, edi
    cpu.ecx = cpu.edi;
    // 004ef103  89ea                   -mov edx, ebp
    cpu.edx = cpu.ebp;
    // 004ef105  89462c                 -mov dword ptr [esi + 0x2c], eax
    app->getMemory<x86::reg32>(cpu.esi + x86::reg32(44) /* 0x2c */) = cpu.eax;
    // 004ef108  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 004ef10a  e821a90100             -call 0x509a30
    cpu.esp -= 4;
    sub_509a30(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004ef10f  8b6e2c                 -mov ebp, dword ptr [esi + 0x2c]
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(44) /* 0x2c */);
    // 004ef112  894630                 -mov dword ptr [esi + 0x30], eax
    app->getMemory<x86::reg32>(cpu.esi + x86::reg32(48) /* 0x30 */) = cpu.eax;
    // 004ef115  85ed                   +test ebp, ebp
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebp & cpu.ebp));
    // 004ef117  7558                   -jne 0x4ef171
    if (!cpu.flags.zf)
    {
        goto L_0x004ef171;
    }
L_0x004ef119:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004ef119  8b442410               -mov eax, dword ptr [esp + 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(16) /* 0x10 */);
    // 004ef11d  8b542438               -mov edx, dword ptr [esp + 0x38]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(56) /* 0x38 */);
    // 004ef121  e86a27ffff             -call 0x4e1890
    cpu.esp -= 4;
    nfs3hp::ea::purgememadr(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004ef126  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 004ef128  7434                   -je 0x4ef15e
    if (cpu.flags.zf)
    {
        goto L_0x004ef15e;
    }
    // 004ef12a  8b6c2420               -mov ebp, dword ptr [esp + 0x20]
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(32) /* 0x20 */);
    // 004ef12e  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004ef12f  b9b4c25400             -mov ecx, 0x54c2b4
    cpu.ecx = 5554868 /*0x54c2b4*/;
    // 004ef134  bbc4c25400             -mov ebx, 0x54c2c4
    cpu.ebx = 5554884 /*0x54c2c4*/;
    // 004ef139  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004ef13a  be99000000             -mov esi, 0x99
    cpu.esi = 153 /*0x99*/;
    // 004ef13f  890d90215500           -mov dword ptr [0x552190], ecx
    app->getMemory<x86::reg32>(x86::reg32(5579152) /* 0x552190 */) = cpu.ecx;
    // 004ef145  6844c45400             -push 0x54c444
    app->getMemory<x86::reg32>(cpu.esp-4) = 5555268 /*0x54c444*/;
    cpu.esp -= 4;
    // 004ef14a  891d94215500           -mov dword ptr [0x552194], ebx
    app->getMemory<x86::reg32>(x86::reg32(5579156) /* 0x552194 */) = cpu.ebx;
    // 004ef150  893598215500           -mov dword ptr [0x552198], esi
    app->getMemory<x86::reg32>(x86::reg32(5579160) /* 0x552198 */) = cpu.esi;
    // 004ef156  e8b51ef1ff             -call 0x401010
    cpu.esp -= 4;
    nfs3hp::Error(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004ef15b  83c40c                 -add esp, 0xc
    (cpu.esp) += x86::reg32(x86::sreg32(12 /*0xc*/));
L_0x004ef15e:
    // 004ef15e  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 004ef160  89442418               -mov dword ptr [esp + 0x18], eax
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(24) /* 0x18 */) = cpu.eax;
    // 004ef164  8b442418               -mov eax, dword ptr [esp + 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(24) /* 0x18 */);
    // 004ef168  83c428                 -add esp, 0x28
    (cpu.esp) += x86::reg32(x86::sreg32(40 /*0x28*/));
    // 004ef16b  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef16c  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef16d  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef16e  c20400                 -ret 4
    cpu.esp += 4+4 /*0x4*/;
    return;
L_0x004ef171:
    // 004ef171  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004ef173  74a4                   -je 0x4ef119
    if (cpu.flags.zf)
    {
        goto L_0x004ef119;
    }
    // 004ef175  8b442418               -mov eax, dword ptr [esp + 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(24) /* 0x18 */);
    // 004ef179  83c428                 -add esp, 0x28
    (cpu.esp) += x86::reg32(x86::sreg32(40 /*0x28*/));
    // 004ef17c  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef17d  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef17e  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef17f  c20400                 -ret 4
    cpu.esp += 4+4 /*0x4*/;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x8b 0xc0 */
void Application::sub_4ef190(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004ef190  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004ef191  8b350c445600           -mov esi, dword ptr [0x56440c]
    cpu.esi = app->getMemory<x86::reg32>(x86::reg32(5653516) /* 0x56440c */);
    // 004ef197  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004ef198  e893fcffff             -call 0x4eee30
    cpu.esp -= 4;
    sub_4eee30(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004ef19d  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef19e  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_4ef1a0: native, nfs3hp::dead::stub_0x4ef1a0 */

/* align: skip 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 */
void Application::sub_4ef1b0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004ef1b0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004ef1b1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004ef1b2  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004ef1b3  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004ef1b4  8b0d0c505600           -mov ecx, dword ptr [0x56500c]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(5656588) /* 0x56500c */);
    // 004ef1ba  8b1504505600           -mov edx, dword ptr [0x565004]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5656580) /* 0x565004 */);
    // 004ef1c0  8b1d00505600           -mov ebx, dword ptr [0x565000]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(5656576) /* 0x565000 */);
    // 004ef1c6  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004ef1c7  a108505600             -mov eax, dword ptr [0x565008]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5656584) /* 0x565008 */);
    // 004ef1cc  89de                   -mov esi, ebx
    cpu.esi = cpu.ebx;
    // 004ef1ce  29d8                   -sub eax, ebx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.ebx));
    // 004ef1d0  29d1                   -sub ecx, edx
    (cpu.ecx) -= x86::reg32(x86::sreg32(cpu.edx));
    // 004ef1d2  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 004ef1d4  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004ef1d6  e865e30000             -call 0x4fd540
    cpu.esp -= 4;
    sub_4fd540(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004ef1db  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef1dc  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef1dd  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef1de  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef1df  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip  */
void Application::sub_4ef1e0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004ef1e0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004ef1e1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004ef1e2  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004ef1e3  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 004ef1e5  89d6                   -mov esi, edx
    cpu.esi = cpu.edx;
    // 004ef1e7  8b4008                 -mov eax, dword ptr [eax + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 004ef1ea  8b0a                   -mov ecx, dword ptr [edx]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.edx);
    // 004ef1ec  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004ef1ee  741e                   -je 0x4ef20e
    if (cpu.flags.zf)
    {
        goto L_0x004ef20e;
    }
    // 004ef1f0  8d14c500000000         -lea edx, [eax*8]
    cpu.edx = x86::reg32(cpu.eax * 8);
    // 004ef1f7  01da                   -add edx, ebx
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.ebx));
L_0x004ef1f9:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004ef1f9  83ea08                 +sub edx, 8
    {
        x86::reg32& tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(8 /*0x8*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 004ef1fc  48                     +dec eax
    {
        x86::reg32& tmp = cpu.eax;
        cpu.flags.of = 1 & (tmp >> 31);
        tmp--;
        cpu.flags.of &= ~(1 & (tmp >> 31));
        cpu.set_szp(tmp);
    }
    // 004ef1fd  7405                   -je 0x4ef204
    if (cpu.flags.zf)
    {
        goto L_0x004ef204;
    }
    // 004ef1ff  3b4a10                 +cmp ecx, dword ptr [edx + 0x10]
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.edx + x86::reg32(16) /* 0x10 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004ef202  75f5                   -jne 0x4ef1f9
    if (!cpu.flags.zf)
    {
        goto L_0x004ef1f9;
    }
L_0x004ef204:
    // 004ef204  c1e003                 -shl eax, 3
    cpu.eax <<= 3 /*0x3*/ % 32;
    // 004ef207  01d8                   -add eax, ebx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.ebx));
    // 004ef209  3b4810                 +cmp ecx, dword ptr [eax + 0x10]
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.eax + x86::reg32(16) /* 0x10 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004ef20c  7458                   -je 0x4ef266
    if (cpu.flags.zf)
    {
        goto L_0x004ef266;
    }
L_0x004ef20e:
    // 004ef20e  833d0c44560000         +cmp dword ptr [0x56440c], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5653516) /* 0x56440c */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004ef215  7449                   -je 0x4ef260
    if (cpu.flags.zf)
    {
        goto L_0x004ef260;
    }
    // 004ef217  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 004ef219  e8e2a90100             -call 0x509c00
    cpu.esp -= 4;
    sub_509c00(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004ef21e  e8bd23ffff             -call 0x4e15e0
    cpu.esp -= 4;
    nfs3hp::ea::memBlockName(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004ef223  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004ef225  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004ef227  7505                   -jne 0x4ef22e
    if (!cpu.flags.zf)
    {
        goto L_0x004ef22e;
    }
    // 004ef229  ba7cc45400             -mov edx, 0x54c47c
    cpu.edx = 5555324 /*0x54c47c*/;
L_0x004ef22e:
    // 004ef22e  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004ef22f  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004ef230  b980c45400             -mov ecx, 0x54c480
    cpu.ecx = 5555328 /*0x54c480*/;
    // 004ef235  bb90c45400             -mov ebx, 0x54c490
    cpu.ebx = 5555344 /*0x54c490*/;
    // 004ef23a  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004ef23b  bf4f000000             -mov edi, 0x4f
    cpu.edi = 79 /*0x4f*/;
    // 004ef240  890d90215500           -mov dword ptr [0x552190], ecx
    app->getMemory<x86::reg32>(x86::reg32(5579152) /* 0x552190 */) = cpu.ecx;
    // 004ef246  689cc45400             -push 0x54c49c
    app->getMemory<x86::reg32>(cpu.esp-4) = 5555356 /*0x54c49c*/;
    cpu.esp -= 4;
    // 004ef24b  891d94215500           -mov dword ptr [0x552194], ebx
    app->getMemory<x86::reg32>(x86::reg32(5579156) /* 0x552194 */) = cpu.ebx;
    // 004ef251  893d98215500           -mov dword ptr [0x552198], edi
    app->getMemory<x86::reg32>(x86::reg32(5579160) /* 0x552198 */) = cpu.edi;
    // 004ef257  e8b41df1ff             -call 0x401010
    cpu.esp -= 4;
    nfs3hp::Error(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004ef25c  83c40c                 -add esp, 0xc
    (cpu.esp) += x86::reg32(x86::sreg32(12 /*0xc*/));
    // 004ef25f  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
L_0x004ef260:
    // 004ef260  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 004ef262  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef263  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef264  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef265  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004ef266:
    // 004ef266  8b4014                 -mov eax, dword ptr [eax + 0x14]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */);
    // 004ef269  01d8                   -add eax, ebx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.ebx));
    // 004ef26b  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef26c  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef26d  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef26e  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_4ef270: native, nfs3hp::ea::locateShape */

/* align: skip 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 */
void Application::sub_4ef2b0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004ef2b0  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004ef2b1  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004ef2b2  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004ef2b3  89c7                   -mov edi, eax
    cpu.edi = cpu.eax;
    // 004ef2b5  89d6                   -mov esi, edx
    cpu.esi = cpu.edx;
    // 004ef2b7  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 004ef2b9  85db                   +test ebx, ebx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & cpu.ebx));
    // 004ef2bb  7e41                   -jle 0x4ef2fe
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004ef2fe;
    }
L_0x004ef2bd:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004ef2bd  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004ef2bf  d1fa                   -sar edx, 1
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (1 /*0x1*/ % 32));
    // 004ef2c1  01fa                   -add edx, edi
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.edi));
    // 004ef2c3  a801                   +test al, 1
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.al & 1 /*0x1*/));
    // 004ef2c5  743b                   -je 0x4ef302
    if (cpu.flags.zf)
    {
        goto L_0x004ef302;
    }
    // 004ef2c7  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 004ef2c9  8a0a                   -mov cl, byte ptr [edx]
    cpu.cl = app->getMemory<x86::reg8>(cpu.edx);
    // 004ef2cb  c1f904                 -sar ecx, 4
    cpu.ecx = x86::reg32(x86::sreg32(cpu.ecx) >> (4 /*0x4*/ % 32));
L_0x004ef2ce:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004ef2ce  88ca                   -mov dl, cl
    cpu.dl = cpu.cl;
    // 004ef2d0  84c9                   +test cl, cl
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.cl & cpu.cl));
    // 004ef2d2  7425                   -je 0x4ef2f9
    if (cpu.flags.zf)
    {
        goto L_0x004ef2f9;
    }
    // 004ef2d4  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 004ef2d6  d1f9                   -sar ecx, 1
    cpu.ecx = x86::reg32(x86::sreg32(cpu.ecx) >> (1 /*0x1*/ % 32));
    // 004ef2d8  01f1                   -add ecx, esi
    (cpu.ecx) += x86::reg32(x86::sreg32(cpu.esi));
    // 004ef2da  a801                   +test al, 1
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.al & 1 /*0x1*/));
    // 004ef2dc  742f                   -je 0x4ef30d
    if (cpu.flags.zf)
    {
        goto L_0x004ef30d;
    }
    // 004ef2de  8a31                   -mov dh, byte ptr [ecx]
    cpu.dh = app->getMemory<x86::reg8>(cpu.ecx);
    // 004ef2e0  80e60f                 -and dh, 0xf
    cpu.dh &= x86::reg8(x86::sreg8(15 /*0xf*/));
    // 004ef2e3  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 004ef2e5  88f1                   -mov cl, dh
    cpu.cl = cpu.dh;
    // 004ef2e7  81e2ff000000           -and edx, 0xff
    cpu.edx &= x86::reg32(x86::sreg32(255 /*0xff*/));
    // 004ef2ed  c1e204                 -shl edx, 4
    cpu.edx <<= 4 /*0x4*/ % 32;
L_0x004ef2f0:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004ef2f0  09ca                   -or edx, ecx
    cpu.edx |= x86::reg32(x86::sreg32(cpu.ecx));
    // 004ef2f2  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 004ef2f4  d1f9                   -sar ecx, 1
    cpu.ecx = x86::reg32(x86::sreg32(cpu.ecx) >> (1 /*0x1*/ % 32));
    // 004ef2f6  881431                 -mov byte ptr [ecx + esi], dl
    app->getMemory<x86::reg8>(cpu.ecx + cpu.esi * 1) = cpu.dl;
L_0x004ef2f9:
    // 004ef2f9  40                     -inc eax
    (cpu.eax)++;
    // 004ef2fa  39d8                   +cmp eax, ebx
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
    // 004ef2fc  7cbf                   -jl 0x4ef2bd
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004ef2bd;
    }
L_0x004ef2fe:
    // 004ef2fe  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef2ff  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef300  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef301  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004ef302:
    // 004ef302  8a12                   -mov dl, byte ptr [edx]
    cpu.dl = app->getMemory<x86::reg8>(cpu.edx);
    // 004ef304  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 004ef306  80e20f                 +and dl, 0xf
    cpu.clear_co();
    cpu.set_szp((cpu.dl &= x86::reg8(x86::sreg8(15 /*0xf*/))));
    // 004ef309  88d1                   -mov cl, dl
    cpu.cl = cpu.dl;
    // 004ef30b  ebc1                   -jmp 0x4ef2ce
    goto L_0x004ef2ce;
L_0x004ef30d:
    // 004ef30d  8a31                   -mov dh, byte ptr [ecx]
    cpu.dh = app->getMemory<x86::reg8>(cpu.ecx);
    // 004ef30f  80e6f0                 -and dh, 0xf0
    cpu.dh &= x86::reg8(x86::sreg8(240 /*0xf0*/));
    // 004ef312  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 004ef314  88f1                   -mov cl, dh
    cpu.cl = cpu.dh;
    // 004ef316  81e2ff000000           +and edx, 0xff
    cpu.clear_co();
    cpu.set_szp((cpu.edx &= x86::reg32(x86::sreg32(255 /*0xff*/))));
    // 004ef31c  ebd2                   -jmp 0x4ef2f0
    goto L_0x004ef2f0;
}

/* align: skip 0x8b 0xc0 */
void Application::sub_4ef320(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004ef320  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
L_0x004ef321:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004ef321  8a08                   -mov cl, byte ptr [eax]
    cpu.cl = app->getMemory<x86::reg8>(cpu.eax);
    // 004ef323  40                     -inc eax
    (cpu.eax)++;
    // 004ef324  80f9ff                 +cmp cl, 0xff
    {
        x86::reg8 tmp1 = cpu.cl;
        x86::reg8 tmp2 = x86::reg8(x86::sreg8(255 /*0xff*/));
        x86::reg8 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 7);
        cpu.flags.of ^= 1 & (result >> 7);
        cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
        cpu.set_szp(result);
    }
    // 004ef327  7506                   -jne 0x4ef32f
    if (!cpu.flags.zf)
    {
        goto L_0x004ef32f;
    }
    // 004ef329  42                     +inc edx
    {
        x86::reg32& tmp = cpu.edx;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 004ef32a  4b                     +dec ebx
    {
        x86::reg32& tmp = cpu.ebx;
        cpu.flags.of = 1 & (tmp >> 31);
        tmp--;
        cpu.flags.of &= ~(1 & (tmp >> 31));
        cpu.set_szp(tmp);
    }
    // 004ef32b  75f4                   -jne 0x4ef321
    if (!cpu.flags.zf)
    {
        goto L_0x004ef321;
    }
    // 004ef32d  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef32e  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004ef32f:
    // 004ef32f  880a                   -mov byte ptr [edx], cl
    app->getMemory<x86::reg8>(cpu.edx) = cpu.cl;
    // 004ef331  42                     +inc edx
    {
        x86::reg32& tmp = cpu.edx;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 004ef332  4b                     +dec ebx
    {
        x86::reg32& tmp = cpu.ebx;
        cpu.flags.of = 1 & (tmp >> 31);
        tmp--;
        cpu.flags.of &= ~(1 & (tmp >> 31));
        cpu.set_szp(tmp);
    }
    // 004ef333  75ec                   -jne 0x4ef321
    if (!cpu.flags.zf)
    {
        goto L_0x004ef321;
    }
    // 004ef335  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef336  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 */
void Application::sub_4ef340(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004ef340  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
L_0x004ef341:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004ef341  668b08                 -mov cx, word ptr [eax]
    cpu.cx = app->getMemory<x86::reg16>(cpu.eax);
    // 004ef344  6685c9                 +test cx, cx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg16>(cpu.cx & cpu.cx));
    // 004ef347  750b                   -jne 0x4ef354
    if (!cpu.flags.zf)
    {
        goto L_0x004ef354;
    }
    // 004ef349  83c202                 -add edx, 2
    (cpu.edx) += x86::reg32(x86::sreg32(2 /*0x2*/));
    // 004ef34c  83c002                 +add eax, 2
    {
        x86::reg32& tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(2 /*0x2*/));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 004ef34f  4b                     +dec ebx
    {
        x86::reg32& tmp = cpu.ebx;
        cpu.flags.of = 1 & (tmp >> 31);
        tmp--;
        cpu.flags.of &= ~(1 & (tmp >> 31));
        cpu.set_szp(tmp);
    }
    // 004ef350  75ef                   -jne 0x4ef341
    if (!cpu.flags.zf)
    {
        goto L_0x004ef341;
    }
    // 004ef352  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef353  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004ef354:
    // 004ef354  66890a                 -mov word ptr [edx], cx
    app->getMemory<x86::reg16>(cpu.edx) = cpu.cx;
    // 004ef357  83c202                 -add edx, 2
    (cpu.edx) += x86::reg32(x86::sreg32(2 /*0x2*/));
    // 004ef35a  83c002                 +add eax, 2
    {
        x86::reg32& tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(2 /*0x2*/));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 004ef35d  4b                     +dec ebx
    {
        x86::reg32& tmp = cpu.ebx;
        cpu.flags.of = 1 & (tmp >> 31);
        tmp--;
        cpu.flags.of &= ~(1 & (tmp >> 31));
        cpu.set_szp(tmp);
    }
    // 004ef35e  75e1                   -jne 0x4ef341
    if (!cpu.flags.zf)
    {
        goto L_0x004ef341;
    }
    // 004ef360  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef361  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x8b 0xc0 */
void Application::sub_4ef370(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004ef370  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004ef371  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004ef372  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004ef373  bf03000000             -mov edi, 3
    cpu.edi = 3 /*0x3*/;
    // 004ef378  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
L_0x004ef37a:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004ef37a  89f9                   -mov ecx, edi
    cpu.ecx = cpu.edi;
    // 004ef37c  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004ef37e  8b4401fc               -mov eax, dword ptr [ecx + eax - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(-4) /* -0x4 */ + cpu.eax * 1);
    // 004ef382  f7d9                   -neg ecx
    cpu.ecx = ~cpu.ecx + 1;
    // 004ef384  8d0ccd20000000         -lea ecx, [ecx*8 + 0x20]
    cpu.ecx = x86::reg32(x86::reg32(32) /* 0x20 */ + cpu.ecx * 8);
    // 004ef38b  d3e8                   -shr eax, cl
    cpu.eax >>= cpu.cl % 32;
    // 004ef38d  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004ef38f  750d                   -jne 0x4ef39e
    if (!cpu.flags.zf)
    {
        goto L_0x004ef39e;
    }
    // 004ef391  83c203                 -add edx, 3
    (cpu.edx) += x86::reg32(x86::sreg32(3 /*0x3*/));
    // 004ef394  83c603                 +add esi, 3
    {
        x86::reg32& tmp1 = cpu.esi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(3 /*0x3*/));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 004ef397  4b                     +dec ebx
    {
        x86::reg32& tmp = cpu.ebx;
        cpu.flags.of = 1 & (tmp >> 31);
        tmp--;
        cpu.flags.of &= ~(1 & (tmp >> 31));
        cpu.set_szp(tmp);
    }
    // 004ef398  75e0                   -jne 0x4ef37a
    if (!cpu.flags.zf)
    {
        goto L_0x004ef37a;
    }
    // 004ef39a  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef39b  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef39c  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef39d  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004ef39e:
    // 004ef39e  8a06                   -mov al, byte ptr [esi]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi);
    // 004ef3a0  8802                   -mov byte ptr [edx], al
    app->getMemory<x86::reg8>(cpu.edx) = cpu.al;
    // 004ef3a2  8a4601                 -mov al, byte ptr [esi + 1]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi + x86::reg32(1) /* 0x1 */);
    // 004ef3a5  884201                 -mov byte ptr [edx + 1], al
    app->getMemory<x86::reg8>(cpu.edx + x86::reg32(1) /* 0x1 */) = cpu.al;
    // 004ef3a8  8a4602                 -mov al, byte ptr [esi + 2]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi + x86::reg32(2) /* 0x2 */);
    // 004ef3ab  884202                 -mov byte ptr [edx + 2], al
    app->getMemory<x86::reg8>(cpu.edx + x86::reg32(2) /* 0x2 */) = cpu.al;
    // 004ef3ae  83c203                 -add edx, 3
    (cpu.edx) += x86::reg32(x86::sreg32(3 /*0x3*/));
    // 004ef3b1  83c603                 +add esi, 3
    {
        x86::reg32& tmp1 = cpu.esi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(3 /*0x3*/));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 004ef3b4  4b                     +dec ebx
    {
        x86::reg32& tmp = cpu.ebx;
        cpu.flags.of = 1 & (tmp >> 31);
        tmp--;
        cpu.flags.of &= ~(1 & (tmp >> 31));
        cpu.set_szp(tmp);
    }
    // 004ef3b5  75c3                   -jne 0x4ef37a
    if (!cpu.flags.zf)
    {
        goto L_0x004ef37a;
    }
    // 004ef3b7  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef3b8  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef3b9  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef3ba  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x40 0x00 0x8b 0xc9 */
void Application::sub_4ef3c0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004ef3c0  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004ef3c1  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
L_0x004ef3c2:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004ef3c2  8b08                   -mov ecx, dword ptr [eax]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax);
    // 004ef3c4  89ce                   -mov esi, ecx
    cpu.esi = cpu.ecx;
    // 004ef3c6  c1ee18                 -shr esi, 0x18
    cpu.esi >>= 24 /*0x18*/ % 32;
    // 004ef3c9  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 004ef3cb  750c                   -jne 0x4ef3d9
    if (!cpu.flags.zf)
    {
        goto L_0x004ef3d9;
    }
    // 004ef3cd  83c204                 -add edx, 4
    (cpu.edx) += x86::reg32(x86::sreg32(4 /*0x4*/));
    // 004ef3d0  83c004                 +add eax, 4
    {
        x86::reg32& tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(4 /*0x4*/));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 004ef3d3  4b                     +dec ebx
    {
        x86::reg32& tmp = cpu.ebx;
        cpu.flags.of = 1 & (tmp >> 31);
        tmp--;
        cpu.flags.of &= ~(1 & (tmp >> 31));
        cpu.set_szp(tmp);
    }
    // 004ef3d4  75ec                   -jne 0x4ef3c2
    if (!cpu.flags.zf)
    {
        goto L_0x004ef3c2;
    }
    // 004ef3d6  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef3d7  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef3d8  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004ef3d9:
    // 004ef3d9  890a                   -mov dword ptr [edx], ecx
    app->getMemory<x86::reg32>(cpu.edx) = cpu.ecx;
    // 004ef3db  83c204                 -add edx, 4
    (cpu.edx) += x86::reg32(x86::sreg32(4 /*0x4*/));
    // 004ef3de  83c004                 +add eax, 4
    {
        x86::reg32& tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(4 /*0x4*/));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 004ef3e1  4b                     +dec ebx
    {
        x86::reg32& tmp = cpu.ebx;
        cpu.flags.of = 1 & (tmp >> 31);
        tmp--;
        cpu.flags.of &= ~(1 & (tmp >> 31));
        cpu.set_szp(tmp);
    }
    // 004ef3e2  75de                   -jne 0x4ef3c2
    if (!cpu.flags.zf)
    {
        goto L_0x004ef3c2;
    }
    // 004ef3e4  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef3e5  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef3e6  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 */
void Application::sub_4ef3f0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004ef3f0  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004ef3f1  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004ef3f2  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004ef3f3  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004ef3f4  81ec04040000           -sub esp, 0x404
    (cpu.esp) -= x86::reg32(x86::sreg32(1028 /*0x404*/));
    // 004ef3fa  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 004ef3fc  89d7                   -mov edi, edx
    cpu.edi = cpu.edx;
    // 004ef3fe  8b00                   -mov eax, dword ptr [eax]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax);
    // 004ef400  83e07f                 -and eax, 0x7f
    cpu.eax &= x86::reg32(x86::sreg32(127 /*0x7f*/));
    // 004ef403  8a80546d5600           -mov al, byte ptr [eax + 0x566d54]
    cpu.al = app->getMemory<x86::reg8>(cpu.eax + x86::reg32(5664084) /* 0x566d54 */);
    // 004ef409  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004ef40b  83f804                 +cmp eax, 4
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(4 /*0x4*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004ef40e  0f8580000000           -jne 0x4ef494
    if (!cpu.flags.zf)
    {
        goto L_0x004ef494;
    }
    // 004ef414  31ed                   -xor ebp, ebp
    cpu.ebp ^= x86::reg32(x86::sreg32(cpu.ebp));
L_0x004ef416:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004ef416  8b0cad14a8a000         -mov ecx, dword ptr [ebp*4 + 0xa0a814]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(10528788) /* 0xa0a814 */ + cpu.ebp * 4);
    // 004ef41d  898c2400040000         -mov dword ptr [esp + 0x400], ecx
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(1024) /* 0x400 */) = cpu.ecx;
    // 004ef424  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 004ef426  890db4505600           -mov dword ptr [0x5650b4], ecx
    app->getMemory<x86::reg32>(x86::reg32(5656756) /* 0x5650b4 */) = cpu.ecx;
    // 004ef42c  890cad14a8a000         -mov dword ptr [ebp*4 + 0xa0a814], ecx
    app->getMemory<x86::reg32>(x86::reg32(10528788) /* 0xa0a814 */ + cpu.ebp * 4) = cpu.ecx;
    // 004ef433  83fa08                 +cmp edx, 8
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(8 /*0x8*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004ef436  752d                   -jne 0x4ef465
    if (!cpu.flags.zf)
    {
        goto L_0x004ef465;
    }
    // 004ef438  803d1050560010         +cmp byte ptr [0x565010], 0x10
    {
        x86::reg8 tmp1 = app->getMemory<x86::reg8>(x86::reg32(5656592) /* 0x565010 */);
        x86::reg8 tmp2 = x86::reg8(x86::sreg8(16 /*0x10*/));
        x86::reg8 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 7);
        cpu.flags.of ^= 1 & (result >> 7);
        cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
        cpu.set_szp(result);
    }
    // 004ef43f  7524                   -jne 0x4ef465
    if (!cpu.flags.zf)
    {
        goto L_0x004ef465;
    }
    // 004ef441  89e2                   -mov edx, esp
    cpu.edx = cpu.esp;
    // 004ef443  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004ef445  b97b000000             -mov ecx, 0x7b
    cpu.ecx = 123 /*0x7b*/;
    // 004ef44a  e8e1b30100             -call 0x50a830
    cpu.esp -= 4;
    sub_50a830(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004ef44f  bac0af5000             -mov edx, 0x50afc0
    cpu.edx = 5287872 /*0x50afc0*/;
    // 004ef454  a3b0099f00             -mov dword ptr [0x9f09b0], eax
    app->getMemory<x86::reg32>(x86::reg32(10422704) /* 0x9f09b0 */) = cpu.eax;
    // 004ef459  890dbc505600           -mov dword ptr [0x5650bc], ecx
    app->getMemory<x86::reg32>(x86::reg32(5656764) /* 0x5650bc */) = cpu.ecx;
    // 004ef45f  8915b4505600           -mov dword ptr [0x5650b4], edx
    app->getMemory<x86::reg32>(x86::reg32(5656756) /* 0x5650b4 */) = cpu.edx;
L_0x004ef465:
    // 004ef465  b99c505600             -mov ecx, 0x56509c
    cpu.ecx = 5656732 /*0x56509c*/;
    // 004ef46a  89fa                   -mov edx, edi
    cpu.edx = cpu.edi;
    // 004ef46c  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004ef46e  e83dbc0100             -call 0x50b0b0
    cpu.esp -= 4;
    sub_50b0b0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004ef473  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
    // 004ef475  8b842400040000         -mov eax, dword ptr [esp + 0x400]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(1024) /* 0x400 */);
    // 004ef47c  891dbc505600           -mov dword ptr [0x5650bc], ebx
    app->getMemory<x86::reg32>(x86::reg32(5656764) /* 0x5650bc */) = cpu.ebx;
    // 004ef482  8904ad14a8a000         -mov dword ptr [ebp*4 + 0xa0a814], eax
    app->getMemory<x86::reg32>(x86::reg32(10528788) /* 0xa0a814 */ + cpu.ebp * 4) = cpu.eax;
    // 004ef489  81c404040000           +add esp, 0x404
    {
        x86::reg32& tmp1 = cpu.esp;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1028 /*0x404*/));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 004ef48f  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef490  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef491  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef492  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef493  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004ef494:
    // 004ef494  bdff000000             -mov ebp, 0xff
    cpu.ebp = 255 /*0xff*/;
    // 004ef499  e978ffffff             -jmp 0x4ef416
    goto L_0x004ef416;
}

/* sub_4ef4a0: native, nfs3hp::dead::stub_0x4ef4a0 */

/* align: skip 0x8d 0x44 0x20 0x00 */
void Application::sub_4ef4c0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004ef4c0  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004ef4c1  8b4808                 -mov ecx, dword ptr [eax + 8]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 004ef4c4  c1f910                 -sar ecx, 0x10
    cpu.ecx = x86::reg32(x86::sreg32(cpu.ecx) >> (16 /*0x10*/ % 32));
    // 004ef4c7  29cb                   -sub ebx, ecx
    (cpu.ebx) -= x86::reg32(x86::sreg32(cpu.ecx));
    // 004ef4c9  8b4806                 -mov ecx, dword ptr [eax + 6]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6) /* 0x6 */);
    // 004ef4cc  c1f910                 -sar ecx, 0x10
    cpu.ecx = x86::reg32(x86::sreg32(cpu.ecx) >> (16 /*0x10*/ % 32));
    // 004ef4cf  29ca                   -sub edx, ecx
    (cpu.edx) -= x86::reg32(x86::sreg32(cpu.ecx));
    // 004ef4d1  e81affffff             -call 0x4ef3f0
    cpu.esp -= 4;
    sub_4ef3f0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004ef4d6  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef4d7  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_4ef4e0: native, nfs3hp::dead::stub_0x4ef4e0 */

/* sub_4ef500: native, nfs3hp::dead::stub_0x4ef500 */

/* align: skip 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 */
void Application::sub_4ef520(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004ef520  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004ef521  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004ef522  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004ef523  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004ef524  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004ef525  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004ef527  b904000000             -mov ecx, 4
    cpu.ecx = 4 /*0x4*/;
    // 004ef52c  8b00                   -mov eax, dword ptr [eax]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax);
    // 004ef52e  0fc8                   -bswap eax
    {
        x86::reg32& tmp = cpu.eax;
        tmp = ( tmp               << 16) ^  (tmp >> 16);
        tmp = ((tmp & 0x00ff00ff) <<  8) ^ ((tmp >>  8) & 0x00ff00ff);
    }
    // 004ef530  f7d9                   -neg ecx
    cpu.ecx = ~cpu.ecx + 1;
    // 004ef532  8d0ccd20000000         -lea ecx, [ecx*8 + 0x20]
    cpu.ecx = x86::reg32(x86::reg32(32) /* 0x20 */ + cpu.ecx * 8);
    // 004ef539  d3e8                   -shr eax, cl
    cpu.eax >>= cpu.cl % 32;
    // 004ef53b  30c0                   -xor al, al
    cpu.al ^= x86::reg8(x86::sreg8(cpu.al));
    // 004ef53d  3d00544e46             +cmp eax, 0x464e5400
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1179538432 /*0x464e5400*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004ef542  7431                   -je 0x4ef575
    if (cpu.flags.zf)
    {
        goto L_0x004ef575;
    }
    // 004ef544  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004ef545  b9ccc45400             -mov ecx, 0x54c4cc
    cpu.ecx = 5555404 /*0x54c4cc*/;
    // 004ef54a  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004ef54b  bbdcc45400             -mov ebx, 0x54c4dc
    cpu.ebx = 5555420 /*0x54c4dc*/;
    // 004ef550  be54000000             -mov esi, 0x54
    cpu.esi = 84 /*0x54*/;
    // 004ef555  68e4c45400             -push 0x54c4e4
    app->getMemory<x86::reg32>(cpu.esp-4) = 5555428 /*0x54c4e4*/;
    cpu.esp -= 4;
    // 004ef55a  890d90215500           -mov dword ptr [0x552190], ecx
    app->getMemory<x86::reg32>(x86::reg32(5579152) /* 0x552190 */) = cpu.ecx;
    // 004ef560  891d94215500           -mov dword ptr [0x552194], ebx
    app->getMemory<x86::reg32>(x86::reg32(5579156) /* 0x552194 */) = cpu.ebx;
    // 004ef566  893598215500           -mov dword ptr [0x552198], esi
    app->getMemory<x86::reg32>(x86::reg32(5579160) /* 0x552198 */) = cpu.esi;
    // 004ef56c  e89f1af1ff             -call 0x401010
    cpu.esp -= 4;
    nfs3hp::Error(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004ef571  83c408                 -add esp, 8
    (cpu.esp) += x86::reg32(x86::sreg32(8 /*0x8*/));
    // 004ef574  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
L_0x004ef575:
    // 004ef575  8b420d                 -mov eax, dword ptr [edx + 0xd]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(13) /* 0xd */);
    // 004ef578  c1f818                 -sar eax, 0x18
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (24 /*0x18*/ % 32));
    // 004ef57b  a300725600             -mov dword ptr [0x567200], eax
    app->getMemory<x86::reg32>(x86::reg32(5665280) /* 0x567200 */) = cpu.eax;
    // 004ef580  8b420e                 -mov eax, dword ptr [edx + 0xe]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(14) /* 0xe */);
    // 004ef583  c1f818                 -sar eax, 0x18
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (24 /*0x18*/ % 32));
    // 004ef586  a304725600             -mov dword ptr [0x567204], eax
    app->getMemory<x86::reg32>(x86::reg32(5665284) /* 0x567204 */) = cpu.eax;
    // 004ef58b  8b420f                 -mov eax, dword ptr [edx + 0xf]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(15) /* 0xf */);
    // 004ef58e  c1f818                 -sar eax, 0x18
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (24 /*0x18*/ % 32));
    // 004ef591  bf64000000             -mov edi, 0x64
    cpu.edi = 100 /*0x64*/;
    // 004ef596  a310725600             -mov dword ptr [0x567210], eax
    app->getMemory<x86::reg32>(x86::reg32(5665296) /* 0x567210 */) = cpu.eax;
    // 004ef59b  8b4210                 -mov eax, dword ptr [edx + 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(16) /* 0x10 */);
    // 004ef59e  bd01000000             -mov ebp, 1
    cpu.ebp = 1 /*0x1*/;
    // 004ef5a3  c1f818                 -sar eax, 0x18
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (24 /*0x18*/ % 32));
    // 004ef5a6  891574725600           -mov dword ptr [0x567274], edx
    app->getMemory<x86::reg32>(x86::reg32(5665396) /* 0x567274 */) = cpu.edx;
    // 004ef5ac  a314725600             -mov dword ptr [0x567214], eax
    app->getMemory<x86::reg32>(x86::reg32(5665300) /* 0x567214 */) = cpu.eax;
    // 004ef5b1  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 004ef5b3  a110725600             -mov eax, dword ptr [0x567210]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5665296) /* 0x567210 */);
    // 004ef5b8  8b4a1c                 -mov ecx, dword ptr [edx + 0x1c]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(28) /* 0x1c */);
    // 004ef5bb  01c3                   -add ebx, eax
    (cpu.ebx) += x86::reg32(x86::sreg32(cpu.eax));
    // 004ef5bd  893d70725600           -mov dword ptr [0x567270], edi
    app->getMemory<x86::reg32>(x86::reg32(5665392) /* 0x567270 */) = cpu.edi;
    // 004ef5c3  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 004ef5c5  892d0c725600           -mov dword ptr [0x56720c], ebp
    app->getMemory<x86::reg32>(x86::reg32(5665292) /* 0x56720c */) = cpu.ebp;
    // 004ef5cb  31d8                   -xor eax, ebx
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.ebx));
    // 004ef5cd  01d1                   -add ecx, edx
    (cpu.ecx) += x86::reg32(x86::sreg32(cpu.edx));
    // 004ef5cf  668b420a               -mov ax, word ptr [edx + 0xa]
    cpu.ax = app->getMemory<x86::reg16>(cpu.edx + x86::reg32(10) /* 0xa */);
    // 004ef5d3  890d7c725600           -mov dword ptr [0x56727c], ecx
    app->getMemory<x86::reg32>(x86::reg32(5665404) /* 0x56727c */) = cpu.ecx;
    // 004ef5d9  a368725600             -mov dword ptr [0x567268], eax
    app->getMemory<x86::reg32>(x86::reg32(5665384) /* 0x567268 */) = cpu.eax;
    // 004ef5de  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 004ef5e0  891d18725600           -mov dword ptr [0x567218], ebx
    app->getMemory<x86::reg32>(x86::reg32(5665304) /* 0x567218 */) = cpu.ebx;
    // 004ef5e6  a3a4725600             -mov dword ptr [0x5672a4], eax
    app->getMemory<x86::reg32>(x86::reg32(5665444) /* 0x5672a4 */) = cpu.eax;
    // 004ef5eb  a3a0725600             -mov dword ptr [0x5672a0], eax
    app->getMemory<x86::reg32>(x86::reg32(5665440) /* 0x5672a0 */) = cpu.eax;
    // 004ef5f0  8b4214                 -mov eax, dword ptr [edx + 0x14]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(20) /* 0x14 */);
    // 004ef5f3  891d1c725600           -mov dword ptr [0x56721c], ebx
    app->getMemory<x86::reg32>(x86::reg32(5665308) /* 0x56721c */) = cpu.ebx;
    // 004ef5f9  8d1c02                 -lea ebx, [edx + eax]
    cpu.ebx = x86::reg32(cpu.edx + cpu.eax * 1);
    // 004ef5fc  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004ef5fe  891d78725600           -mov dword ptr [0x567278], ebx
    app->getMemory<x86::reg32>(x86::reg32(5665400) /* 0x567278 */) = cpu.ebx;
    // 004ef604  8b00                   -mov eax, dword ptr [eax]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax);
    // 004ef606  83e07f                 -and eax, 0x7f
    cpu.eax &= x86::reg32(x86::sreg32(127 /*0x7f*/));
    // 004ef609  8a80546d5600           -mov al, byte ptr [eax + 0x566d54]
    cpu.al = app->getMemory<x86::reg8>(cpu.eax + x86::reg32(5664084) /* 0x566d54 */);
    // 004ef60f  a308725600             -mov dword ptr [0x567208], eax
    app->getMemory<x86::reg32>(x86::reg32(5665288) /* 0x567208 */) = cpu.eax;
    // 004ef614  8b5902                 -mov ebx, dword ptr [ecx + 2]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(2) /* 0x2 */);
    // 004ef617  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004ef619  c1fb10                 -sar ebx, 0x10
    cpu.ebx = x86::reg32(x86::sreg32(cpu.ebx) >> (16 /*0x10*/ % 32));
    // 004ef61c  8b00                   -mov eax, dword ptr [eax]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax);
    // 004ef61e  83e07f                 -and eax, 0x7f
    cpu.eax &= x86::reg32(x86::sreg32(127 /*0x7f*/));
    // 004ef621  8a80546d5600           -mov al, byte ptr [eax + 0x566d54]
    cpu.al = app->getMemory<x86::reg8>(cpu.eax + x86::reg32(5664084) /* 0x566d54 */);
    // 004ef627  0fafc3                 -imul eax, ebx
    cpu.eax = x86::reg32(x86::sreg64(x86::sreg32(cpu.eax)) * x86::sreg64(x86::sreg32(cpu.ebx)));
    // 004ef62a  83c007                 -add eax, 7
    (cpu.eax) += x86::reg32(x86::sreg32(7 /*0x7*/));
    // 004ef62d  24f8                   -and al, 0xf8
    cpu.al &= x86::reg8(x86::sreg8(248 /*0xf8*/));
    // 004ef62f  c1f803                 -sar eax, 3
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (3 /*0x3*/ % 32));
    // 004ef632  a36c725600             -mov dword ptr [0x56726c], eax
    app->getMemory<x86::reg32>(x86::reg32(5665388) /* 0x56726c */) = cpu.eax;
    // 004ef637  8b420c                 -mov eax, dword ptr [edx + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(12) /* 0xc */);
    // 004ef63a  c1f810                 -sar eax, 0x10
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (16 /*0x10*/ % 32));
    // 004ef63d  83e003                 -and eax, 3
    cpu.eax &= x86::reg32(x86::sreg32(3 /*0x3*/));
    // 004ef640  83f802                 +cmp eax, 2
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(2 /*0x2*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004ef643  740c                   -je 0x4ef651
    if (cpu.flags.zf)
    {
        goto L_0x004ef651;
    }
    // 004ef645  813d68725600ff000000   +cmp dword ptr [0x567268], 0xff
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5665384) /* 0x567268 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(255 /*0xff*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004ef64f  7e3e                   -jle 0x4ef68f
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004ef68f;
    }
L_0x004ef651:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004ef651  c7059472560080b55000   -mov dword ptr [0x567294], 0x50b580
    app->getMemory<x86::reg32>(x86::reg32(5665428) /* 0x567294 */) = 5289344 /*0x50b580*/;
L_0x004ef65b:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004ef65b  ba40000000             -mov edx, 0x40
    cpu.edx = 64 /*0x40*/;
    // 004ef660  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 004ef662  b828725600             -mov eax, 0x567228
    cpu.eax = 5665320 /*0x567228*/;
    // 004ef667  890d20725600           -mov dword ptr [0x567220], ecx
    app->getMemory<x86::reg32>(x86::reg32(5665312) /* 0x567220 */) = cpu.ecx;
    // 004ef66d  890d24725600           -mov dword ptr [0x567224], ecx
    app->getMemory<x86::reg32>(x86::reg32(5665316) /* 0x567224 */) = cpu.ecx;
    // 004ef673  890da8725600           -mov dword ptr [0x5672a8], ecx
    app->getMemory<x86::reg32>(x86::reg32(5665448) /* 0x5672a8 */) = cpu.ecx;
    // 004ef679  e88e10ffff             -call 0x4e070c
    cpu.esp -= 4;
    nfs3hp::fillZero(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004ef67e  e84dca0100             -call 0x50c0d0
    cpu.esp -= 4;
    sub_50c0d0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004ef683  890d98725600           -mov dword ptr [0x567298], ecx
    app->getMemory<x86::reg32>(x86::reg32(5665432) /* 0x567298 */) = cpu.ecx;
    // 004ef689  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef68a  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef68b  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef68c  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef68d  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef68e  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004ef68f:
    // 004ef68f  b902000000             -mov ecx, 2
    cpu.ecx = 2 /*0x2*/;
    // 004ef694  8d4220                 -lea eax, [edx + 0x20]
    cpu.eax = x86::reg32(cpu.edx + x86::reg32(32) /* 0x20 */);
    // 004ef697  8b4401fc               -mov eax, dword ptr [ecx + eax - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(-4) /* -0x4 */ + cpu.eax * 1);
    // 004ef69b  f7d9                   -neg ecx
    cpu.ecx = ~cpu.ecx + 1;
    // 004ef69d  8d0ccd20000000         -lea ecx, [ecx*8 + 0x20]
    cpu.ecx = x86::reg32(x86::reg32(32) /* 0x20 */ + cpu.ecx * 8);
    // 004ef6a4  d3e8                   -shr eax, cl
    cpu.eax >>= cpu.cl % 32;
    // 004ef6a6  3dff000000             +cmp eax, 0xff
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(255 /*0xff*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004ef6ab  77a4                   -ja 0x4ef651
    if (!cpu.flags.cf && !cpu.flags.zf)
    {
        goto L_0x004ef651;
    }
    // 004ef6ad  c7059472560040b55000   -mov dword ptr [0x567294], 0x50b540
    app->getMemory<x86::reg32>(x86::reg32(5665428) /* 0x567294 */) = 5289280 /*0x50b540*/;
    // 004ef6b7  eba2                   -jmp 0x4ef65b
    goto L_0x004ef65b;
}

/* align: skip 0x00 0x00 0x00 0x00 0x00 0x00 0x00 */
void Application::sub_4ef6c0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004ef6c0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004ef6c1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004ef6c2  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004ef6c3  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004ef6c4  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004ef6c5  83ec10                 -sub esp, 0x10
    (cpu.esp) -= x86::reg32(x86::sreg32(16 /*0x10*/));
    // 004ef6c8  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004ef6ca  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 004ef6cc  c1e910                 -shr ecx, 0x10
    cpu.ecx >>= 16 /*0x10*/ % 32;
    // 004ef6cf  81e1ff000000           -and ecx, 0xff
    cpu.ecx &= x86::reg32(x86::sreg32(255 /*0xff*/));
    // 004ef6d5  bb9f860100             -mov ebx, 0x1869f
    cpu.ebx = 99999 /*0x1869f*/;
    // 004ef6da  894c2404               -mov dword ptr [esp + 4], ecx
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(4) /* 0x4 */) = cpu.ecx;
    // 004ef6de  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 004ef6e0  ba14a8a000             -mov edx, 0xa0a814
    cpu.edx = 10528788 /*0xa0a814*/;
    // 004ef6e5  c1e908                 -shr ecx, 8
    cpu.ecx >>= 8 /*0x8*/ % 32;
    // 004ef6e8  25ff000000             -and eax, 0xff
    cpu.eax &= x86::reg32(x86::sreg32(255 /*0xff*/));
    // 004ef6ed  81e1ff000000           -and ecx, 0xff
    cpu.ecx &= x86::reg32(x86::sreg32(255 /*0xff*/));
    // 004ef6f3  890424                 -mov dword ptr [esp], eax
    app->getMemory<x86::reg32>(cpu.esp) = cpu.eax;
    // 004ef6f6  894c2408               -mov dword ptr [esp + 8], ecx
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(8) /* 0x8 */) = cpu.ecx;
    // 004ef6fa  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 004ef6fc  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 004ef6fe  894c240c               -mov dword ptr [esp + 0xc], ecx
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(12) /* 0xc */) = cpu.ecx;
L_0x004ef702:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004ef702  83c204                 -add edx, 4
    (cpu.edx) += x86::reg32(x86::sreg32(4 /*0x4*/));
    // 004ef705  0fb67afd               -movzx edi, byte ptr [edx - 3]
    cpu.edi = x86::reg32(app->getMemory<x86::reg8>(cpu.edx + x86::reg32(-3) /* -0x3 */));
    // 004ef709  0fb66afc               -movzx ebp, byte ptr [edx - 4]
    cpu.ebp = x86::reg32(app->getMemory<x86::reg8>(cpu.edx + x86::reg32(-4) /* -0x4 */));
    // 004ef70d  8a88c4505600           -mov cl, byte ptr [eax + 0x5650c4]
    cpu.cl = app->getMemory<x86::reg8>(cpu.eax + x86::reg32(5656772) /* 0x5650c4 */);
    // 004ef713  0fb672fe               -movzx esi, byte ptr [edx - 2]
    cpu.esi = x86::reg32(app->getMemory<x86::reg8>(cpu.edx + x86::reg32(-2) /* -0x2 */));
    // 004ef717  84c9                   +test cl, cl
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.cl & cpu.cl));
    // 004ef719  742b                   -je 0x4ef746
    if (cpu.flags.zf)
    {
        goto L_0x004ef746;
    }
    // 004ef71b  8b4c2408               -mov ecx, dword ptr [esp + 8]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(8) /* 0x8 */);
    // 004ef71f  29f9                   -sub ecx, edi
    (cpu.ecx) -= x86::reg32(x86::sreg32(cpu.edi));
    // 004ef721  89cf                   -mov edi, ecx
    cpu.edi = cpu.ecx;
    // 004ef723  0faff9                 -imul edi, ecx
    cpu.edi = x86::reg32(x86::sreg64(x86::sreg32(cpu.edi)) * x86::sreg64(x86::sreg32(cpu.ecx)));
    // 004ef726  8b4c2404               -mov ecx, dword ptr [esp + 4]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(4) /* 0x4 */);
    // 004ef72a  29f1                   -sub ecx, esi
    (cpu.ecx) -= x86::reg32(x86::sreg32(cpu.esi));
    // 004ef72c  0fafc9                 -imul ecx, ecx
    cpu.ecx = x86::reg32(x86::sreg64(x86::sreg32(cpu.ecx)) * x86::sreg64(x86::sreg32(cpu.ecx)));
    // 004ef72f  8d340f                 -lea esi, [edi + ecx]
    cpu.esi = x86::reg32(cpu.edi + cpu.ecx * 1);
    // 004ef732  8b0c24                 -mov ecx, dword ptr [esp]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    // 004ef735  29e9                   -sub ecx, ebp
    (cpu.ecx) -= x86::reg32(x86::sreg32(cpu.ebp));
    // 004ef737  0fafc9                 -imul ecx, ecx
    cpu.ecx = x86::reg32(x86::sreg64(x86::sreg32(cpu.ecx)) * x86::sreg64(x86::sreg32(cpu.ecx)));
    // 004ef73a  01f1                   -add ecx, esi
    (cpu.ecx) += x86::reg32(x86::sreg32(cpu.esi));
    // 004ef73c  39d9                   +cmp ecx, ebx
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ebx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004ef73e  7d06                   -jge 0x4ef746
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004ef746;
    }
    // 004ef740  8944240c               -mov dword ptr [esp + 0xc], eax
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(12) /* 0xc */) = cpu.eax;
    // 004ef744  89cb                   -mov ebx, ecx
    cpu.ebx = cpu.ecx;
L_0x004ef746:
    // 004ef746  40                     -inc eax
    (cpu.eax)++;
    // 004ef747  3d00010000             +cmp eax, 0x100
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(256 /*0x100*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004ef74c  7cb4                   -jl 0x4ef702
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004ef702;
    }
    // 004ef74e  8b44240c               -mov eax, dword ptr [esp + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(12) /* 0xc */);
    // 004ef752  83c410                 -add esp, 0x10
    (cpu.esp) += x86::reg32(x86::sreg32(16 /*0x10*/));
    // 004ef755  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef756  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef757  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef758  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef759  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef75a  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x40 0x00 0x8b 0xc9 */
void Application::sub_4ef760(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004ef760  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004ef761  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004ef762  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 004ef764  8a2510505600           -mov ah, byte ptr [0x565010]
    cpu.ah = app->getMemory<x86::reg8>(x86::reg32(5656592) /* 0x565010 */);
    // 004ef76a  80fc08                 +cmp ah, 8
    {
        x86::reg8 tmp1 = cpu.ah;
        x86::reg8 tmp2 = x86::reg8(x86::sreg8(8 /*0x8*/));
        x86::reg8 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 7);
        cpu.flags.of ^= 1 & (result >> 7);
        cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
        cpu.set_szp(result);
    }
    // 004ef76d  761c                   -jbe 0x4ef78b
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x004ef78b;
    }
    // 004ef76f  80fc0f                 +cmp ah, 0xf
    {
        x86::reg8 tmp1 = cpu.ah;
        x86::reg8 tmp2 = x86::reg8(x86::sreg8(15 /*0xf*/));
        x86::reg8 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 7);
        cpu.flags.of ^= 1 & (result >> 7);
        cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
        cpu.set_szp(result);
    }
    // 004ef772  745e                   -je 0x4ef7d2
    if (cpu.flags.zf)
    {
        goto L_0x004ef7d2;
    }
    // 004ef774  80fc10                 +cmp ah, 0x10
    {
        x86::reg8 tmp1 = cpu.ah;
        x86::reg8 tmp2 = x86::reg8(x86::sreg8(16 /*0x10*/));
        x86::reg8 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 7);
        cpu.flags.of ^= 1 & (result >> 7);
        cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
        cpu.set_szp(result);
    }
    // 004ef777  0f8483000000           -je 0x4ef800
    if (cpu.flags.zf)
    {
        goto L_0x004ef800;
    }
    // 004ef77d  80fc18                 +cmp ah, 0x18
    {
        x86::reg8 tmp1 = cpu.ah;
        x86::reg8 tmp2 = x86::reg8(x86::sreg8(24 /*0x18*/));
        x86::reg8 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 7);
        cpu.flags.of ^= 1 & (result >> 7);
        cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
        cpu.set_szp(result);
    }
    // 004ef780  0f829f000000           -jb 0x4ef825
    if (cpu.flags.cf)
    {
        goto L_0x004ef825;
    }
    // 004ef786  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 004ef788  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef789  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef78a  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004ef78b:
    // 004ef78b  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004ef78c  8b0dc0505600           -mov ecx, dword ptr [0x5650c0]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(5656768) /* 0x5650c0 */);
    // 004ef792  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    // 004ef794  7427                   -je 0x4ef7bd
    if (cpu.flags.zf)
    {
        goto L_0x004ef7bd;
    }
    // 004ef796  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 004ef798  81e30000f800           -and ebx, 0xf80000
    cpu.ebx &= x86::reg32(x86::sreg32(16252928 /*0xf80000*/));
    // 004ef79e  c1eb09                 -shr ebx, 9
    cpu.ebx >>= 9 /*0x9*/ % 32;
    // 004ef7a1  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004ef7a3  c1e803                 -shr eax, 3
    cpu.eax >>= 3 /*0x3*/ % 32;
    // 004ef7a6  81e200f80000           -and edx, 0xf800
    cpu.edx &= x86::reg32(x86::sreg32(63488 /*0xf800*/));
    // 004ef7ac  c1ea06                 -shr edx, 6
    cpu.edx >>= 6 /*0x6*/ % 32;
    // 004ef7af  83e01f                 -and eax, 0x1f
    cpu.eax &= x86::reg32(x86::sreg32(31 /*0x1f*/));
    // 004ef7b2  01d8                   -add eax, ebx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.ebx));
    // 004ef7b4  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 004ef7b6  31db                   +xor ebx, ebx
    cpu.clear_co();
    cpu.set_szp((cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx))));
    // 004ef7b8  8a1c01                 -mov bl, byte ptr [ecx + eax]
    cpu.bl = app->getMemory<x86::reg8>(cpu.ecx + cpu.eax * 1);
    // 004ef7bb  eb0f                   -jmp 0x4ef7cc
    goto L_0x004ef7cc;
L_0x004ef7bd:
    // 004ef7bd  89da                   -mov edx, ebx
    cpu.edx = cpu.ebx;
    // 004ef7bf  8d0514a8a000           -lea eax, [0xa0a814]
    cpu.eax = x86::reg32(x86::reg32(10528788) /* 0xa0a814 */);
    // 004ef7c5  e8f6feffff             -call 0x4ef6c0
    cpu.esp -= 4;
    sub_4ef6c0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004ef7ca  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
L_0x004ef7cc:
    // 004ef7cc  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef7cd  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 004ef7cf  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef7d0  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef7d1  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004ef7d2:
    // 004ef7d2  09db                   +or ebx, ebx
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(cpu.ebx))));
    // 004ef7d4  7425                   -je 0x4ef7fb
    if (cpu.flags.zf)
    {
        goto L_0x004ef7fb;
    }
    // 004ef7d6  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 004ef7d8  81e30000f800           -and ebx, 0xf80000
    cpu.ebx &= x86::reg32(x86::sreg32(16252928 /*0xf80000*/));
    // 004ef7de  c1eb09                 -shr ebx, 9
    cpu.ebx >>= 9 /*0x9*/ % 32;
    // 004ef7e1  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004ef7e3  c1e803                 -shr eax, 3
    cpu.eax >>= 3 /*0x3*/ % 32;
    // 004ef7e6  81e200f80000           -and edx, 0xf800
    cpu.edx &= x86::reg32(x86::sreg32(63488 /*0xf800*/));
    // 004ef7ec  c1ea06                 -shr edx, 6
    cpu.edx >>= 6 /*0x6*/ % 32;
    // 004ef7ef  83e01f                 -and eax, 0x1f
    cpu.eax &= x86::reg32(x86::sreg32(31 /*0x1f*/));
    // 004ef7f2  01c3                   -add ebx, eax
    (cpu.ebx) += x86::reg32(x86::sreg32(cpu.eax));
    // 004ef7f4  8d9c1300800000         -lea ebx, [ebx + edx + 0x8000]
    cpu.ebx = x86::reg32(cpu.ebx + x86::reg32(32768) /* 0x8000 */ + cpu.edx * 1);
L_0x004ef7fb:
    // 004ef7fb  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 004ef7fd  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef7fe  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef7ff  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004ef800:
    // 004ef800  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 004ef802  81e30000f800           -and ebx, 0xf80000
    cpu.ebx &= x86::reg32(x86::sreg32(16252928 /*0xf80000*/));
    // 004ef808  c1eb08                 -shr ebx, 8
    cpu.ebx >>= 8 /*0x8*/ % 32;
    // 004ef80b  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004ef80d  c1e803                 -shr eax, 3
    cpu.eax >>= 3 /*0x3*/ % 32;
    // 004ef810  81e200fc0000           -and edx, 0xfc00
    cpu.edx &= x86::reg32(x86::sreg32(64512 /*0xfc00*/));
    // 004ef816  c1ea05                 -shr edx, 5
    cpu.edx >>= 5 /*0x5*/ % 32;
    // 004ef819  83e01f                 -and eax, 0x1f
    cpu.eax &= x86::reg32(x86::sreg32(31 /*0x1f*/));
    // 004ef81c  01c3                   -add ebx, eax
    (cpu.ebx) += x86::reg32(x86::sreg32(cpu.eax));
    // 004ef81e  01d3                   -add ebx, edx
    (cpu.ebx) += x86::reg32(x86::sreg32(cpu.edx));
    // 004ef820  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 004ef822  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef823  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef824  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004ef825:
    // 004ef825  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
    // 004ef827  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 004ef829  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef82a  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef82b  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x00 0x00 0x00 0x00 */
void Application::sub_4ef830(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004ef830  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004ef831  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004ef832  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004ef833  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004ef834  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004ef835  83ec34                 -sub esp, 0x34
    (cpu.esp) -= x86::reg32(x86::sreg32(52 /*0x34*/));
    // 004ef838  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 004ef83a  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
    // 004ef83c  8a2510505600           -mov ah, byte ptr [0x565010]
    cpu.ah = app->getMemory<x86::reg8>(x86::reg32(5656592) /* 0x565010 */);
    // 004ef842  891da4725600           -mov dword ptr [0x5672a4], ebx
    app->getMemory<x86::reg32>(x86::reg32(5665444) /* 0x5672a4 */) = cpu.ebx;
    // 004ef848  80fc08                 +cmp ah, 8
    {
        x86::reg8 tmp1 = cpu.ah;
        x86::reg8 tmp2 = x86::reg8(x86::sreg8(8 /*0x8*/));
        x86::reg8 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 7);
        cpu.flags.of ^= 1 & (result >> 7);
        cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
        cpu.set_szp(result);
    }
    // 004ef84b  7540                   -jne 0x4ef88d
    if (!cpu.flags.zf)
    {
        goto L_0x004ef88d;
    }
    // 004ef84d  81f900010000           +cmp ecx, 0x100
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(256 /*0x100*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004ef853  7238                   -jb 0x4ef88d
    if (cpu.flags.cf)
    {
        goto L_0x004ef88d;
    }
    // 004ef855  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004ef856  be34c55400             -mov esi, 0x54c534
    cpu.esi = 5555508 /*0x54c534*/;
    // 004ef85b  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 004ef85d  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004ef85e  a010505600             -mov al, byte ptr [0x565010]
    cpu.al = app->getMemory<x86::reg8>(x86::reg32(5656592) /* 0x565010 */);
    // 004ef863  bf44c55400             -mov edi, 0x54c544
    cpu.edi = 5555524 /*0x54c544*/;
    // 004ef868  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004ef869  bd3c000000             -mov ebp, 0x3c
    cpu.ebp = 60 /*0x3c*/;
    // 004ef86e  893590215500           -mov dword ptr [0x552190], esi
    app->getMemory<x86::reg32>(x86::reg32(5579152) /* 0x552190 */) = cpu.esi;
    // 004ef874  6850c55400             -push 0x54c550
    app->getMemory<x86::reg32>(cpu.esp-4) = 5555536 /*0x54c550*/;
    cpu.esp -= 4;
    // 004ef879  893d94215500           -mov dword ptr [0x552194], edi
    app->getMemory<x86::reg32>(x86::reg32(5579156) /* 0x552194 */) = cpu.edi;
    // 004ef87f  892d98215500           -mov dword ptr [0x552198], ebp
    app->getMemory<x86::reg32>(x86::reg32(5579160) /* 0x552198 */) = cpu.ebp;
    // 004ef885  e88617f1ff             -call 0x401010
    cpu.esp -= 4;
    nfs3hp::Error(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004ef88a  83c410                 -add esp, 0x10
    (cpu.esp) += x86::reg32(x86::sreg32(16 /*0x10*/));
L_0x004ef88d:
    // 004ef88d  3b0d20725600           +cmp ecx, dword ptr [0x567220]
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(5665312) /* 0x567220 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004ef893  750c                   -jne 0x4ef8a1
    if (!cpu.flags.zf)
    {
        goto L_0x004ef8a1;
    }
    // 004ef895  3b1524725600           +cmp edx, dword ptr [0x567224]
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(5665316) /* 0x567224 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004ef89b  0f8458010000           -je 0x4ef9f9
    if (cpu.flags.zf)
    {
        goto L_0x004ef9f9;
    }
L_0x004ef8a1:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004ef8a1  890d20725600           -mov dword ptr [0x567220], ecx
    app->getMemory<x86::reg32>(x86::reg32(5665312) /* 0x567220 */) = cpu.ecx;
    // 004ef8a7  891524725600           -mov dword ptr [0x567224], edx
    app->getMemory<x86::reg32>(x86::reg32(5665316) /* 0x567224 */) = cpu.edx;
    // 004ef8ad  31ff                   -xor edi, edi
    cpu.edi ^= x86::reg32(x86::sreg32(cpu.edi));
    // 004ef8af  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004ef8b1  893da8725600           -mov dword ptr [0x5672a8], edi
    app->getMemory<x86::reg32>(x86::reg32(5665448) /* 0x5672a8 */) = cpu.edi;
    // 004ef8b7  e8e4ca0100             -call 0x50c3a0
    cpu.esp -= 4;
    sub_50c3a0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004ef8bc  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 004ef8be  c1e910                 -shr ecx, 0x10
    cpu.ecx >>= 16 /*0x10*/ % 32;
    // 004ef8c1  81e1ff000000           -and ecx, 0xff
    cpu.ecx &= x86::reg32(x86::sreg32(255 /*0xff*/));
    // 004ef8c7  894c2418               -mov dword ptr [esp + 0x18], ecx
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(24) /* 0x18 */) = cpu.ecx;
    // 004ef8cb  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 004ef8cd  25ff000000             -and eax, 0xff
    cpu.eax &= x86::reg32(x86::sreg32(255 /*0xff*/));
    // 004ef8d2  8944241c               -mov dword ptr [esp + 0x1c], eax
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(28) /* 0x1c */) = cpu.eax;
    // 004ef8d6  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004ef8d8  e8c3ca0100             -call 0x50c3a0
    cpu.esp -= 4;
    sub_50c3a0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004ef8dd  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004ef8df  c1ea10                 -shr edx, 0x10
    cpu.edx >>= 16 /*0x10*/ % 32;
    // 004ef8e2  81e2ff000000           -and edx, 0xff
    cpu.edx &= x86::reg32(x86::sreg32(255 /*0xff*/));
    // 004ef8e8  89542420               -mov dword ptr [esp + 0x20], edx
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(32) /* 0x20 */) = cpu.edx;
    // 004ef8ec  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004ef8ee  25ff000000             -and eax, 0xff
    cpu.eax &= x86::reg32(x86::sreg32(255 /*0xff*/));
    // 004ef8f3  c1ea08                 -shr edx, 8
    cpu.edx >>= 8 /*0x8*/ % 32;
    // 004ef8f6  89442424               -mov dword ptr [esp + 0x24], eax
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(36) /* 0x24 */) = cpu.eax;
    // 004ef8fa  8b442420               -mov eax, dword ptr [esp + 0x20]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(32) /* 0x20 */);
    // 004ef8fe  81e2ff000000           -and edx, 0xff
    cpu.edx &= x86::reg32(x86::sreg32(255 /*0xff*/));
    // 004ef904  8d1c8500000000         -lea ebx, [eax*4]
    cpu.ebx = x86::reg32(cpu.eax * 4);
    // 004ef90b  89542428               -mov dword ptr [esp + 0x28], edx
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(40) /* 0x28 */) = cpu.edx;
    // 004ef90f  01c3                   -add ebx, eax
    (cpu.ebx) += x86::reg32(x86::sreg32(cpu.eax));
    // 004ef911  8d349500000000         -lea esi, [edx*4]
    cpu.esi = x86::reg32(cpu.edx * 4);
    // 004ef918  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 004ef91a  c1e302                 -shl ebx, 2
    cpu.ebx <<= 2 /*0x2*/ % 32;
    // 004ef91d  01d6                   -add esi, edx
    (cpu.esi) += x86::reg32(x86::sreg32(cpu.edx));
    // 004ef91f  29c3                   -sub ebx, eax
    (cpu.ebx) -= x86::reg32(x86::sreg32(cpu.eax));
    // 004ef921  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004ef923  c1e602                 -shl esi, 2
    cpu.esi <<= 2 /*0x2*/ % 32;
    // 004ef926  29c6                   -sub esi, eax
    (cpu.esi) -= x86::reg32(x86::sreg32(cpu.eax));
    // 004ef928  8b442424               -mov eax, dword ptr [esp + 0x24]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(36) /* 0x24 */);
    // 004ef92c  89442410               -mov dword ptr [esp + 0x10], eax
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(16) /* 0x10 */) = cpu.eax;
    // 004ef930  31ed                   -xor ebp, ebp
    cpu.ebp ^= x86::reg32(x86::sreg32(cpu.ebp));
    // 004ef932  8b542410               -mov edx, dword ptr [esp + 0x10]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(16) /* 0x10 */);
    // 004ef936  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 004ef939  897c242c               -mov dword ptr [esp + 0x2c], edi
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(44) /* 0x2c */) = cpu.edi;
    // 004ef93d  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 004ef93f  c1e908                 -shr ecx, 8
    cpu.ecx >>= 8 /*0x8*/ % 32;
    // 004ef942  89442410               -mov dword ptr [esp + 0x10], eax
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(16) /* 0x10 */) = cpu.eax;
    // 004ef946  81e1ff000000           -and ecx, 0xff
    cpu.ecx &= x86::reg32(x86::sreg32(255 /*0xff*/));
    // 004ef94c  8b542410               -mov edx, dword ptr [esp + 0x10]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(16) /* 0x10 */);
    // 004ef950  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 004ef953  894c2414               -mov dword ptr [esp + 0x14], ecx
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(20) /* 0x14 */) = cpu.ecx;
    // 004ef957  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 004ef959  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 004ef95b  89442430               -mov dword ptr [esp + 0x30], eax
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(48) /* 0x30 */) = cpu.eax;
    // 004ef95f  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
L_0x004ef961:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004ef961  8d042b                 -lea eax, [ebx + ebp]
    cpu.eax = x86::reg32(cpu.ebx + cpu.ebp * 1);
    // 004ef964  c1e804                 -shr eax, 4
    cpu.eax >>= 4 /*0x4*/ % 32;
    // 004ef967  890424                 -mov dword ptr [esp], eax
    app->getMemory<x86::reg32>(cpu.esp) = cpu.eax;
    // 004ef96a  8d043e                 -lea eax, [esi + edi]
    cpu.eax = x86::reg32(cpu.esi + cpu.edi * 1);
    // 004ef96d  c1e804                 -shr eax, 4
    cpu.eax >>= 4 /*0x4*/ % 32;
    // 004ef970  89442404               -mov dword ptr [esp + 4], eax
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(4) /* 0x4 */) = cpu.eax;
    // 004ef974  8b442430               -mov eax, dword ptr [esp + 0x30]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(48) /* 0x30 */);
    // 004ef978  01c8                   -add eax, ecx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.ecx));
    // 004ef97a  c1e804                 -shr eax, 4
    cpu.eax >>= 4 /*0x4*/ % 32;
    // 004ef97d  89442408               -mov dword ptr [esp + 8], eax
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(8) /* 0x8 */) = cpu.eax;
    // 004ef981  036c2418               -add ebp, dword ptr [esp + 0x18]
    (cpu.ebp) += x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.esp + x86::reg32(24) /* 0x18 */)));
    // 004ef985  037c2414               -add edi, dword ptr [esp + 0x14]
    (cpu.edi) += x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.esp + x86::reg32(20) /* 0x14 */)));
    // 004ef989  034c241c               -add ecx, dword ptr [esp + 0x1c]
    (cpu.ecx) += x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.esp + x86::reg32(28) /* 0x1c */)));
    // 004ef98d  2b5c2420               -sub ebx, dword ptr [esp + 0x20]
    (cpu.ebx) -= x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.esp + x86::reg32(32) /* 0x20 */)));
    // 004ef991  2b742428               -sub esi, dword ptr [esp + 0x28]
    (cpu.esi) -= x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.esp + x86::reg32(40) /* 0x28 */)));
    // 004ef995  8b442424               -mov eax, dword ptr [esp + 0x24]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(36) /* 0x24 */);
    // 004ef999  29442430               -sub dword ptr [esp + 0x30], eax
    (app->getMemory<x86::reg32>(cpu.esp + x86::reg32(48) /* 0x30 */)) -= x86::reg32(x86::sreg32(cpu.eax));
    // 004ef99d  8b0424                 -mov eax, dword ptr [esp]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp);
    // 004ef9a0  c1e010                 -shl eax, 0x10
    cpu.eax <<= 16 /*0x10*/ % 32;
    // 004ef9a3  8944240c               -mov dword ptr [esp + 0xc], eax
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(12) /* 0xc */) = cpu.eax;
    // 004ef9a7  8b44242c               -mov eax, dword ptr [esp + 0x2c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(44) /* 0x2c */);
    // 004ef9ab  0b44240c               -or eax, dword ptr [esp + 0xc]
    cpu.eax |= x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.esp + x86::reg32(12) /* 0xc */)));
    // 004ef9af  8944240c               -mov dword ptr [esp + 0xc], eax
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(12) /* 0xc */) = cpu.eax;
    // 004ef9b3  8b442404               -mov eax, dword ptr [esp + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(4) /* 0x4 */);
    // 004ef9b7  c1e008                 -shl eax, 8
    cpu.eax <<= 8 /*0x8*/ % 32;
    // 004ef9ba  89442410               -mov dword ptr [esp + 0x10], eax
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(16) /* 0x10 */) = cpu.eax;
    // 004ef9be  8b44240c               -mov eax, dword ptr [esp + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(12) /* 0xc */);
    // 004ef9c2  0b442410               -or eax, dword ptr [esp + 0x10]
    cpu.eax |= x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.esp + x86::reg32(16) /* 0x10 */)));
    // 004ef9c6  0b442408               -or eax, dword ptr [esp + 8]
    cpu.eax |= x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.esp + x86::reg32(8) /* 0x8 */)));
    // 004ef9ca  e891fdffff             -call 0x4ef760
    cpu.esp -= 4;
    sub_4ef760(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004ef9cf  898228725600           -mov dword ptr [edx + 0x567228], eax
    app->getMemory<x86::reg32>(cpu.edx + x86::reg32(5665320) /* 0x567228 */) = cpu.eax;
    // 004ef9d5  8a44242f               -mov al, byte ptr [esp + 0x2f]
    cpu.al = app->getMemory<x86::reg8>(cpu.esp + x86::reg32(47) /* 0x2f */);
    // 004ef9d9  0410                   -add al, 0x10
    (cpu.al) += x86::reg8(x86::sreg8(16 /*0x10*/));
    // 004ef9db  83c204                 -add edx, 4
    (cpu.edx) += x86::reg32(x86::sreg32(4 /*0x4*/));
    // 004ef9de  8844242f               -mov byte ptr [esp + 0x2f], al
    app->getMemory<x86::reg8>(cpu.esp + x86::reg32(47) /* 0x2f */) = cpu.al;
    // 004ef9e2  83fa40                 +cmp edx, 0x40
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(64 /*0x40*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004ef9e5  0f8576ffffff           -jne 0x4ef961
    if (!cpu.flags.zf)
    {
        goto L_0x004ef961;
    }
    // 004ef9eb  e890c70100             -call 0x50c180
    cpu.esp -= 4;
    sub_50c180(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004ef9f0  83c434                 -add esp, 0x34
    (cpu.esp) += x86::reg32(x86::sreg32(52 /*0x34*/));
    // 004ef9f3  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef9f4  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef9f5  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef9f6  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef9f7  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ef9f8  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004ef9f9:
    // 004ef9f9  833da872560000         +cmp dword ptr [0x5672a8], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5665448) /* 0x5672a8 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004efa00  0f849bfeffff           -je 0x4ef8a1
    if (cpu.flags.zf)
    {
        goto L_0x004ef8a1;
    }
    // 004efa06  83c434                 -add esp, 0x34
    (cpu.esp) += x86::reg32(x86::sreg32(52 /*0x34*/));
    // 004efa09  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004efa0a  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004efa0b  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004efa0c  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004efa0d  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004efa0e  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x00 */
void Application::sub_4efa10(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004efa10  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004efa11  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004efa12  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004efa13  89c5                   -mov ebp, eax
    cpu.ebp = cpu.eax;
    // 004efa15  89d7                   -mov edi, edx
    cpu.edi = cpu.edx;
    // 004efa17  89ce                   -mov esi, ecx
    cpu.esi = cpu.ecx;
    // 004efa19  89da                   -mov edx, ebx
    cpu.edx = cpu.ebx;
    // 004efa1b  85db                   +test ebx, ebx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & cpu.ebx));
    // 004efa1d  7436                   -je 0x4efa55
    if (cpu.flags.zf)
    {
        goto L_0x004efa55;
    }
L_0x004efa1f:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004efa1f  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004efa21  d1f8                   -sar eax, 1
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (1 /*0x1*/ % 32));
    // 004efa23  0fafc6                 -imul eax, esi
    cpu.eax = x86::reg32(x86::sreg64(x86::sreg32(cpu.eax)) * x86::sreg64(x86::sreg32(cpu.esi)));
    // 004efa26  8d1c07                 -lea ebx, [edi + eax]
    cpu.ebx = x86::reg32(cpu.edi + cpu.eax * 1);
    // 004efa29  b902000000             -mov ecx, 2
    cpu.ecx = 2 /*0x2*/;
    // 004efa2e  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 004efa30  8b4401fc               -mov eax, dword ptr [ecx + eax - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(-4) /* -0x4 */ + cpu.eax * 1);
    // 004efa34  f7d9                   -neg ecx
    cpu.ecx = ~cpu.ecx + 1;
    // 004efa36  8d0ccd20000000         -lea ecx, [ecx*8 + 0x20]
    cpu.ecx = x86::reg32(x86::reg32(32) /* 0x20 */ + cpu.ecx * 8);
    // 004efa3d  d3e8                   -shr eax, cl
    cpu.eax >>= cpu.cl % 32;
    // 004efa3f  89e9                   -mov ecx, ebp
    cpu.ecx = cpu.ebp;
    // 004efa41  29c1                   +sub ecx, eax
    {
        x86::reg32& tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.eax));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 004efa43  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004efa45  7414                   -je 0x4efa5b
    if (cpu.flags.zf)
    {
        goto L_0x004efa5b;
    }
    // 004efa47  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    // 004efa49  7e04                   -jle 0x4efa4f
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004efa4f;
    }
    // 004efa4b  4a                     -dec edx
    (cpu.edx)--;
    // 004efa4c  8d3c33                 -lea edi, [ebx + esi]
    cpu.edi = x86::reg32(cpu.ebx + cpu.esi * 1);
L_0x004efa4f:
    // 004efa4f  d1fa                   -sar edx, 1
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (1 /*0x1*/ % 32));
    // 004efa51  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 004efa53  75ca                   -jne 0x4efa1f
    if (!cpu.flags.zf)
    {
        goto L_0x004efa1f;
    }
L_0x004efa55:
    // 004efa55  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 004efa57  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004efa58  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004efa59  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004efa5a  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004efa5b:
    // 004efa5b  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 004efa5d  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004efa5e  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004efa5f  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004efa60  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x8d 0x40 0x00 */
void Application::sub_4efa70(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004efa70  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004efa71  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004efa72  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004efa73  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004efa74  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004efa75  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004efa76  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 004efa78  8b1570725600           -mov edx, dword ptr [0x567270]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5665392) /* 0x567270 */);
    // 004efa7e  8b3d78725600           -mov edi, dword ptr [0x567278]
    cpu.edi = app->getMemory<x86::reg32>(x86::reg32(5665400) /* 0x567278 */);
    // 004efa84  83fa64                 +cmp edx, 0x64
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(100 /*0x64*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004efa87  7d2e                   -jge 0x4efab7
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004efab7;
    }
    // 004efa89  b9acc55400             -mov ecx, 0x54c5ac
    cpu.ecx = 5555628 /*0x54c5ac*/;
    // 004efa8e  bbbcc55400             -mov ebx, 0x54c5bc
    cpu.ebx = 5555644 /*0x54c5bc*/;
    // 004efa93  bd64000000             -mov ebp, 0x64
    cpu.ebp = 100 /*0x64*/;
    // 004efa98  68ccc55400             -push 0x54c5cc
    app->getMemory<x86::reg32>(cpu.esp-4) = 5555660 /*0x54c5cc*/;
    cpu.esp -= 4;
    // 004efa9d  890d90215500           -mov dword ptr [0x552190], ecx
    app->getMemory<x86::reg32>(x86::reg32(5579152) /* 0x552190 */) = cpu.ecx;
    // 004efaa3  891d94215500           -mov dword ptr [0x552194], ebx
    app->getMemory<x86::reg32>(x86::reg32(5579156) /* 0x552194 */) = cpu.ebx;
    // 004efaa9  892d98215500           -mov dword ptr [0x552198], ebp
    app->getMemory<x86::reg32>(x86::reg32(5579160) /* 0x552198 */) = cpu.ebp;
    // 004efaaf  e85c15f1ff             -call 0x401010
    cpu.esp -= 4;
    nfs3hp::Error(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004efab4  83c404                 -add esp, 4
    (cpu.esp) += x86::reg32(x86::sreg32(4 /*0x4*/));
L_0x004efab7:
    // 004efab7  8d56e0                 -lea edx, [esi - 0x20]
    cpu.edx = x86::reg32(cpu.esi + x86::reg32(-32) /* -0x20 */);
    // 004efaba  8d049500000000         -lea eax, [edx*4]
    cpu.eax = x86::reg32(cpu.edx * 4);
    // 004efac1  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 004efac3  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 004efac6  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 004efac8  8d1407                 -lea edx, [edi + eax]
    cpu.edx = x86::reg32(cpu.edi + cpu.eax * 1);
    // 004efacb  b902000000             -mov ecx, 2
    cpu.ecx = 2 /*0x2*/;
    // 004efad0  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004efad2  8b4401fc               -mov eax, dword ptr [ecx + eax - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(-4) /* -0x4 */ + cpu.eax * 1);
    // 004efad6  f7d9                   -neg ecx
    cpu.ecx = ~cpu.ecx + 1;
    // 004efad8  8d0ccd20000000         -lea ecx, [ecx*8 + 0x20]
    cpu.ecx = x86::reg32(x86::reg32(32) /* 0x20 */ + cpu.ecx * 8);
    // 004efadf  d3e8                   -shr eax, cl
    cpu.eax >>= cpu.cl % 32;
    // 004efae1  39f0                   +cmp eax, esi
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
    // 004efae3  7509                   -jne 0x4efaee
    if (!cpu.flags.zf)
    {
        goto L_0x004efaee;
    }
    // 004efae5  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004efae7  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004efae8  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004efae9  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004efaea  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004efaeb  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004efaec  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004efaed  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004efaee:
    // 004efaee  b90b000000             -mov ecx, 0xb
    cpu.ecx = 11 /*0xb*/;
    // 004efaf3  8b1d68725600           -mov ebx, dword ptr [0x567268]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(5665384) /* 0x567268 */);
    // 004efaf9  89fa                   -mov edx, edi
    cpu.edx = cpu.edi;
    // 004efafb  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004efafd  e80effffff             -call 0x4efa10
    cpu.esp -= 4;
    sub_4efa10(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004efb02  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004efb03  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004efb04  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004efb05  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004efb06  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004efb07  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004efb08  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x90 */
void Application::sub_4efb10(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004efb10  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004efb11  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004efb12  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004efb13  8b0d9c725600           -mov ecx, dword ptr [0x56729c]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(5665436) /* 0x56729c */);
    // 004efb19  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 004efb1b  89d3                   -mov ebx, edx
    cpu.ebx = cpu.edx;
    // 004efb1d  a1a0725600             -mov eax, dword ptr [0x5672a0]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5665440) /* 0x5672a0 */);
    // 004efb22  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 004efb24  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    // 004efb26  7e13                   -jle 0x4efb3b
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004efb3b;
    }
L_0x004efb28:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004efb28  663b7002               +cmp si, word ptr [eax + 2]
    {
        x86::reg16 tmp1 = cpu.si;
        x86::reg16 tmp2 = x86::reg16(x86::sreg16(app->getMemory<x86::reg16>(cpu.eax + x86::reg32(2) /* 0x2 */)));
        x86::reg16 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 15);
        cpu.flags.of ^= 1 & (result >> 15);
        cpu.flags.of &= (1 & (tmp1 >> 15)) != (1 & (tmp2 >> 15));
        cpu.set_szp(result);
    }
    // 004efb2c  7505                   -jne 0x4efb33
    if (!cpu.flags.zf)
    {
        goto L_0x004efb33;
    }
    // 004efb2e  663b18                 +cmp bx, word ptr [eax]
    {
        x86::reg16 tmp1 = cpu.bx;
        x86::reg16 tmp2 = x86::reg16(x86::sreg16(app->getMemory<x86::reg16>(cpu.eax)));
        x86::reg16 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 15);
        cpu.flags.of ^= 1 & (result >> 15);
        cpu.flags.of &= (1 & (tmp1 >> 15)) != (1 & (tmp2 >> 15));
        cpu.set_szp(result);
    }
    // 004efb31  740e                   -je 0x4efb41
    if (cpu.flags.zf)
    {
        goto L_0x004efb41;
    }
L_0x004efb33:
    // 004efb33  42                     -inc edx
    (cpu.edx)++;
    // 004efb34  83c008                 -add eax, 8
    (cpu.eax) += x86::reg32(x86::sreg32(8 /*0x8*/));
    // 004efb37  39ca                   +cmp edx, ecx
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
    // 004efb39  7ced                   -jl 0x4efb28
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004efb28;
    }
L_0x004efb3b:
    // 004efb3b  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 004efb3d  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004efb3e  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004efb3f  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004efb40  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004efb41:
    // 004efb41  8b4001                 -mov eax, dword ptr [eax + 1]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(1) /* 0x1 */);
    // 004efb44  c1f818                 -sar eax, 0x18
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (24 /*0x18*/ % 32));
    // 004efb47  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004efb48  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004efb49  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004efb4a  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x40 0x00 0x8b 0xc9 */
void Application::sub_4efb50(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004efb50  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004efb51  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004efb52  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004efb53  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004efb54  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004efb55  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004efb56  83ec44                 -sub esp, 0x44
    (cpu.esp) -= x86::reg32(x86::sreg32(68 /*0x44*/));
    // 004efb59  89442420               -mov dword ptr [esp + 0x20], eax
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(32) /* 0x20 */) = cpu.eax;
    // 004efb5d  bfffffffff             -mov edi, 0xffffffff
    cpu.edi = 4294967295 /*0xffffffff*/;
    // 004efb62  8b35f8715600           -mov esi, dword ptr [0x5671f8]
    cpu.esi = app->getMemory<x86::reg32>(x86::reg32(5665272) /* 0x5671f8 */);
    // 004efb68  8b1500725600           -mov edx, dword ptr [0x567200]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5665280) /* 0x567200 */);
    // 004efb6e  8b2dfc715600           -mov ebp, dword ptr [0x5671fc]
    cpu.ebp = app->getMemory<x86::reg32>(x86::reg32(5665276) /* 0x5671fc */);
    // 004efb74  8b0d04725600           -mov ecx, dword ptr [0x567204]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(5665284) /* 0x567204 */);
    // 004efb7a  890424                 -mov dword ptr [esp], eax
    app->getMemory<x86::reg32>(cpu.esp) = cpu.eax;
    // 004efb7d  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
    // 004efb7f  a188725600             -mov eax, dword ptr [0x567288]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5665416) /* 0x567288 */);
    // 004efb84  895c241c               -mov dword ptr [esp + 0x1c], ebx
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(28) /* 0x1c */) = cpu.ebx;
    // 004efb88  897c2440               -mov dword ptr [esp + 0x40], edi
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(64) /* 0x40 */) = cpu.edi;
    // 004efb8c  89442414               -mov dword ptr [esp + 0x14], eax
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(20) /* 0x14 */) = cpu.eax;
    // 004efb90  a194725600             -mov eax, dword ptr [0x567294]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5665428) /* 0x567294 */);
    // 004efb95  895c243c               -mov dword ptr [esp + 0x3c], ebx
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(60) /* 0x3c */) = cpu.ebx;
    // 004efb99  8944240c               -mov dword ptr [esp + 0xc], eax
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(12) /* 0xc */) = cpu.eax;
    // 004efb9d  a198725600             -mov eax, dword ptr [0x567298]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5665432) /* 0x567298 */);
    // 004efba2  01d6                   -add esi, edx
    (cpu.esi) += x86::reg32(x86::sreg32(cpu.edx));
    // 004efba4  89442438               -mov dword ptr [esp + 0x38], eax
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(56) /* 0x38 */) = cpu.eax;
    // 004efba8  a1a0725600             -mov eax, dword ptr [0x5672a0]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5665440) /* 0x5672a0 */);
    // 004efbad  01cd                   -add ebp, ecx
    (cpu.ebp) += x86::reg32(x86::sreg32(cpu.ecx));
    // 004efbaf  89442418               -mov dword ptr [esp + 0x18], eax
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(24) /* 0x18 */) = cpu.eax;
    // 004efbb3  a1f8715600             -mov eax, dword ptr [0x5671f8]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5665272) /* 0x5671f8 */);
    // 004efbb8  8b542420               -mov edx, dword ptr [esp + 0x20]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(32) /* 0x20 */);
    // 004efbbc  89442410               -mov dword ptr [esp + 0x10], eax
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(16) /* 0x10 */) = cpu.eax;
    // 004efbc0  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 004efbc2  0f8419010000           -je 0x4efce1
    if (cpu.flags.zf)
    {
        goto L_0x004efce1;
    }
L_0x004efbc8:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004efbc8  833d8c72560000         +cmp dword ptr [0x56728c], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5665420) /* 0x56728c */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004efbcf  7406                   -je 0x4efbd7
    if (cpu.flags.zf)
    {
        goto L_0x004efbd7;
    }
    // 004efbd1  ff158c725600           -call dword ptr [0x56728c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(5665420) /* 0x56728c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x004efbd7:
    // 004efbd7  b820000000             -mov eax, 0x20
    cpu.eax = 32 /*0x20*/;
    // 004efbdc  e88ffeffff             -call 0x4efa70
    cpu.esp -= 4;
    sub_4efa70(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004efbe1  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004efbe3  0f852b010000           -jne 0x4efd14
    if (!cpu.flags.zf)
    {
        goto L_0x004efd14;
    }
L_0x004efbe9:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004efbe9  8b44243c               -mov eax, dword ptr [esp + 0x3c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(60) /* 0x3c */);
    // 004efbed  8b542440               -mov edx, dword ptr [esp + 0x40]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(64) /* 0x40 */);
    // 004efbf1  89442434               -mov dword ptr [esp + 0x34], eax
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(52) /* 0x34 */) = cpu.eax;
    // 004efbf5  89e0                   -mov eax, esp
    cpu.eax = cpu.esp;
    // 004efbf7  42                     -inc edx
    (cpu.edx)++;
    // 004efbf8  ff54240c               -call dword ptr [esp + 0xc]
    cpu.ip = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(12) /* 0xc */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004efbfc  89542440               -mov dword ptr [esp + 0x40], edx
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(64) /* 0x40 */) = cpu.edx;
    // 004efc00  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 004efc02  8944243c               -mov dword ptr [esp + 0x3c], eax
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(60) /* 0x3c */) = cpu.eax;
    // 004efc06  83f820                 +cmp eax, 0x20
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(32 /*0x20*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004efc09  0f8e73010000           -jle 0x4efd82
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004efd82;
    }
    // 004efc0f  e85cfeffff             -call 0x4efa70
    cpu.esp -= 4;
    sub_4efa70(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004efc14  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004efc16  89c7                   -mov edi, eax
    cpu.edi = cpu.eax;
    // 004efc18  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004efc1a  0f841c010000           -je 0x4efd3c
    if (cpu.flags.zf)
    {
        goto L_0x004efd3c;
    }
    // 004efc20  b902000000             -mov ecx, 2
    cpu.ecx = 2 /*0x2*/;
    // 004efc25  83c004                 -add eax, 4
    (cpu.eax) += x86::reg32(x86::sreg32(4 /*0x4*/));
    // 004efc28  8b4401fc               -mov eax, dword ptr [ecx + eax - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(-4) /* -0x4 */ + cpu.eax * 1);
    // 004efc2c  f7d9                   -neg ecx
    cpu.ecx = ~cpu.ecx + 1;
    // 004efc2e  8d0ccd20000000         -lea ecx, [ecx*8 + 0x20]
    cpu.ecx = x86::reg32(x86::reg32(32) /* 0x20 */ + cpu.ecx * 8);
    // 004efc35  d3e8                   -shr eax, cl
    cpu.eax >>= cpu.cl % 32;
    // 004efc37  b902000000             -mov ecx, 2
    cpu.ecx = 2 /*0x2*/;
    // 004efc3c  89442424               -mov dword ptr [esp + 0x24], eax
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(36) /* 0x24 */) = cpu.eax;
    // 004efc40  8d4206                 -lea eax, [edx + 6]
    cpu.eax = x86::reg32(cpu.edx + x86::reg32(6) /* 0x6 */);
    // 004efc43  8b4401fc               -mov eax, dword ptr [ecx + eax - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(-4) /* -0x4 */ + cpu.eax * 1);
    // 004efc47  f7d9                   -neg ecx
    cpu.ecx = ~cpu.ecx + 1;
    // 004efc49  8d0ccd20000000         -lea ecx, [ecx*8 + 0x20]
    cpu.ecx = x86::reg32(x86::reg32(32) /* 0x20 */ + cpu.ecx * 8);
    // 004efc50  d3e8                   -shr eax, cl
    cpu.eax >>= cpu.cl % 32;
    // 004efc52  8944242c               -mov dword ptr [esp + 0x2c], eax
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(44) /* 0x2c */) = cpu.eax;
    // 004efc56  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 004efc58  8b4c2418               -mov ecx, dword ptr [esp + 0x18]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(24) /* 0x18 */);
    // 004efc5c  89442404               -mov dword ptr [esp + 4], eax
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(4) /* 0x4 */) = cpu.eax;
    // 004efc60  89442408               -mov dword ptr [esp + 8], eax
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(8) /* 0x8 */) = cpu.eax;
    // 004efc64  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    // 004efc66  740d                   -je 0x4efc75
    if (cpu.flags.zf)
    {
        goto L_0x004efc75;
    }
    // 004efc68  8b542434               -mov edx, dword ptr [esp + 0x34]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(52) /* 0x34 */);
    // 004efc6c  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 004efc6e  e89dfeffff             -call 0x4efb10
    cpu.esp -= 4;
    sub_4efb10(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004efc73  01c6                   -add esi, eax
    (cpu.esi) += x86::reg32(x86::sreg32(cpu.eax));
L_0x004efc75:
    // 004efc75  8b4706                 -mov eax, dword ptr [edi + 6]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edi + x86::reg32(6) /* 0x6 */);
    // 004efc78  c1f818                 -sar eax, 0x18
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (24 /*0x18*/ % 32));
    // 004efc7b  8d1406                 -lea edx, [esi + eax]
    cpu.edx = x86::reg32(cpu.esi + cpu.eax * 1);
    // 004efc7e  8b4707                 -mov eax, dword ptr [edi + 7]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edi + x86::reg32(7) /* 0x7 */);
    // 004efc81  c1f818                 -sar eax, 0x18
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (24 /*0x18*/ % 32));
    // 004efc84  89542428               -mov dword ptr [esp + 0x28], edx
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(40) /* 0x28 */) = cpu.edx;
    // 004efc88  8d1428                 -lea edx, [eax + ebp]
    cpu.edx = x86::reg32(cpu.eax + cpu.ebp * 1);
    // 004efc8b  8b5c2438               -mov ebx, dword ptr [esp + 0x38]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(56) /* 0x38 */);
    // 004efc8f  89542430               -mov dword ptr [esp + 0x30], edx
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(48) /* 0x30 */) = cpu.edx;
    // 004efc93  85db                   +test ebx, ebx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & cpu.ebx));
    // 004efc95  0f8588000000           -jne 0x4efd23
    if (!cpu.flags.zf)
    {
        goto L_0x004efd23;
    }
L_0x004efc9b:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004efc9b  a16c725600             -mov eax, dword ptr [0x56726c]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5665388) /* 0x56726c */);
    // 004efca0  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004efca1  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 004efca3  8a4703                 -mov al, byte ptr [edi + 3]
    cpu.al = app->getMemory<x86::reg8>(cpu.edi + x86::reg32(3) /* 0x3 */);
    // 004efca6  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004efca7  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 004efca9  8a4702                 -mov al, byte ptr [edi + 2]
    cpu.al = app->getMemory<x86::reg8>(cpu.edi + x86::reg32(2) /* 0x2 */);
    // 004efcac  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004efcad  8b542438               -mov edx, dword ptr [esp + 0x38]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(56) /* 0x38 */);
    // 004efcb1  8b4c2414               -mov ecx, dword ptr [esp + 0x14]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(20) /* 0x14 */);
    // 004efcb5  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004efcb6  8b542440               -mov edx, dword ptr [esp + 0x40]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(64) /* 0x40 */);
    // 004efcba  8b442438               -mov eax, dword ptr [esp + 0x38]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(56) /* 0x38 */);
    // 004efcbe  01ca                   -add edx, ecx
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.ecx));
    // 004efcc0  8b4c2414               -mov ecx, dword ptr [esp + 0x14]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(20) /* 0x14 */);
    // 004efcc4  8b1d7c725600           -mov ebx, dword ptr [0x56727c]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(5665404) /* 0x56727c */);
    // 004efcca  01c8                   -add eax, ecx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.ecx));
    // 004efccc  8b4c2434               -mov ecx, dword ptr [esp + 0x34]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(52) /* 0x34 */);
    // 004efcd0  ff542424               -call dword ptr [esp + 0x24]
    cpu.ip = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(36) /* 0x24 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004efcd4  8b4705                 -mov eax, dword ptr [edi + 5]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edi + x86::reg32(5) /* 0x5 */);
    // 004efcd7  c1f818                 -sar eax, 0x18
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (24 /*0x18*/ % 32));
    // 004efcda  01c6                   +add esi, eax
    {
        x86::reg32& tmp1 = cpu.esi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.eax));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 004efcdc  e908ffffff             -jmp 0x4efbe9
    goto L_0x004efbe9;
L_0x004efce1:
    // 004efce1  b9acc55400             -mov ecx, 0x54c5ac
    cpu.ecx = 5555628 /*0x54c5ac*/;
    // 004efce6  bb00c65400             -mov ebx, 0x54c600
    cpu.ebx = 5555712 /*0x54c600*/;
    // 004efceb  bf9e000000             -mov edi, 0x9e
    cpu.edi = 158 /*0x9e*/;
    // 004efcf0  6808c65400             -push 0x54c608
    app->getMemory<x86::reg32>(cpu.esp-4) = 5555720 /*0x54c608*/;
    cpu.esp -= 4;
    // 004efcf5  890d90215500           -mov dword ptr [0x552190], ecx
    app->getMemory<x86::reg32>(x86::reg32(5579152) /* 0x552190 */) = cpu.ecx;
    // 004efcfb  891d94215500           -mov dword ptr [0x552194], ebx
    app->getMemory<x86::reg32>(x86::reg32(5579156) /* 0x552194 */) = cpu.ebx;
    // 004efd01  893d98215500           -mov dword ptr [0x552198], edi
    app->getMemory<x86::reg32>(x86::reg32(5579160) /* 0x552198 */) = cpu.edi;
    // 004efd07  e80413f1ff             -call 0x401010
    cpu.esp -= 4;
    nfs3hp::Error(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004efd0c  83c404                 +add esp, 4
    {
        x86::reg32& tmp1 = cpu.esp;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(4 /*0x4*/));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 004efd0f  e9b4feffff             -jmp 0x4efbc8
    goto L_0x004efbc8;
L_0x004efd14:
    // 004efd14  8b4005                 -mov eax, dword ptr [eax + 5]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(5) /* 0x5 */);
    // 004efd17  c1f818                 +sar eax, 0x18
    {
        x86::reg8 tmp = 24 /*0x18*/ % 32;
        x86::reg32& op = cpu.eax;
        if (tmp)
        {
            cpu.flags.cf = 1 & (x86::sreg32(op) >> (tmp - 1));
            if (tmp == 1) cpu.flags.of = 0;
            cpu.set_szp((op = x86::reg32(x86::sreg32(op) >> tmp)));
        }
    }
    // 004efd1a  8944241c               -mov dword ptr [esp + 0x1c], eax
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(28) /* 0x1c */) = cpu.eax;
    // 004efd1e  e9c6feffff             -jmp 0x4efbe9
    goto L_0x004efbe9;
L_0x004efd23:
    // 004efd23  8b4c2440               -mov ecx, dword ptr [esp + 0x40]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(64) /* 0x40 */);
    // 004efd27  8b5c2420               -mov ebx, dword ptr [esp + 0x20]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(32) /* 0x20 */);
    // 004efd2b  8d542408               -lea edx, [esp + 8]
    cpu.edx = x86::reg32(cpu.esp + x86::reg32(8) /* 0x8 */);
    // 004efd2f  8d442404               -lea eax, [esp + 4]
    cpu.eax = x86::reg32(cpu.esp + x86::reg32(4) /* 0x4 */);
    // 004efd33  ff542438               -call dword ptr [esp + 0x38]
    cpu.ip = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(56) /* 0x38 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004efd37  e95fffffff             -jmp 0x4efc9b
    goto L_0x004efc9b;
L_0x004efd3c:
    // 004efd3c  833dcc51560000         +cmp dword ptr [0x5651cc], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5657036) /* 0x5651cc */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004efd43  0f84a0feffff           -je 0x4efbe9
    if (cpu.flags.zf)
    {
        goto L_0x004efbe9;
    }
    // 004efd49  a118725600             -mov eax, dword ptr [0x567218]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5665304) /* 0x567218 */);
    // 004efd4e  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004efd50  c1fa1f                 -sar edx, 0x1f
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (31 /*0x1f*/ % 32));
    // 004efd53  2bc2                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 004efd55  d1f8                   -sar eax, 1
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (1 /*0x1*/ % 32));
    // 004efd57  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004efd59  c1fa1f                 -sar edx, 0x1f
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (31 /*0x1f*/ % 32));
    // 004efd5c  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 004efd5e  2bc2                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 004efd60  d1f8                   -sar eax, 1
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (1 /*0x1*/ % 32));
    // 004efd62  89c7                   -mov edi, eax
    cpu.edi = cpu.eax;
    // 004efd64  b80000aaff             -mov eax, 0xffaa0000
    cpu.eax = 4289331200 /*0xffaa0000*/;
    // 004efd69  89ea                   -mov edx, ebp
    cpu.edx = cpu.ebp;
    // 004efd6b  e8f0f9ffff             -call 0x4ef760
    cpu.esp -= 4;
    sub_4ef760(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004efd70  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004efd71  8d5ffe                 -lea ebx, [edi - 2]
    cpu.ebx = x86::reg32(cpu.edi + x86::reg32(-2) /* -0x2 */);
    // 004efd74  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004efd76  e8c5d70000             -call 0x4fd540
    cpu.esp -= 4;
    sub_4fd540(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004efd7b  01fe                   +add esi, edi
    {
        x86::reg32& tmp1 = cpu.esi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.edi));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 004efd7d  e967feffff             -jmp 0x4efbe9
    goto L_0x004efbe9;
L_0x004efd82:
    // 004efd82  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004efd84  7531                   -jne 0x4efdb7
    if (!cpu.flags.zf)
    {
        goto L_0x004efdb7;
    }
    // 004efd86  833d9072560000         +cmp dword ptr [0x567290], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5665424) /* 0x567290 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004efd8d  0f858e000000           -jne 0x4efe21
    if (!cpu.flags.zf)
    {
        goto L_0x004efe21;
    }
L_0x004efd93:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004efd93  a100725600             -mov eax, dword ptr [0x567200]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5665280) /* 0x567200 */);
    // 004efd98  29c6                   -sub esi, eax
    (cpu.esi) -= x86::reg32(x86::sreg32(cpu.eax));
    // 004efd9a  a104725600             -mov eax, dword ptr [0x567204]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5665284) /* 0x567204 */);
    // 004efd9f  29c5                   -sub ebp, eax
    (cpu.ebp) -= x86::reg32(x86::sreg32(cpu.eax));
    // 004efda1  8935f8715600           -mov dword ptr [0x5671f8], esi
    app->getMemory<x86::reg32>(x86::reg32(5665272) /* 0x5671f8 */) = cpu.esi;
    // 004efda7  892dfc715600           -mov dword ptr [0x5671fc], ebp
    app->getMemory<x86::reg32>(x86::reg32(5665276) /* 0x5671fc */) = cpu.ebp;
    // 004efdad  83c444                 -add esp, 0x44
    (cpu.esp) += x86::reg32(x86::sreg32(68 /*0x44*/));
    // 004efdb0  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004efdb1  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004efdb2  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004efdb3  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004efdb4  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004efdb5  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004efdb6  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004efdb7:
    // 004efdb7  83f80a                 +cmp eax, 0xa
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(10 /*0xa*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004efdba  7517                   -jne 0x4efdd3
    if (!cpu.flags.zf)
    {
        goto L_0x004efdd3;
    }
    // 004efdbc  8b1510725600           -mov edx, dword ptr [0x567210]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5665296) /* 0x567210 */);
    // 004efdc2  031514725600           -add edx, dword ptr [0x567214]
    (cpu.edx) += x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(5665300) /* 0x567214 */)));
    // 004efdc8  8b742410               -mov esi, dword ptr [esp + 0x10]
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(16) /* 0x10 */);
    // 004efdcc  01d5                   +add ebp, edx
    {
        x86::reg32& tmp1 = cpu.ebp;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.edx));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 004efdce  e916feffff             -jmp 0x4efbe9
    goto L_0x004efbe9;
L_0x004efdd3:
    // 004efdd3  833dc851560000         +cmp dword ptr [0x5651c8], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5657032) /* 0x5651c8 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004efdda  7509                   -jne 0x4efde5
    if (!cpu.flags.zf)
    {
        goto L_0x004efde5;
    }
L_0x004efddc:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004efddc  0374241c               +add esi, dword ptr [esp + 0x1c]
    {
        x86::reg32& tmp1 = cpu.esi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.esp + x86::reg32(28) /* 0x1c */)));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 004efde0  e904feffff             -jmp 0x4efbe9
    goto L_0x004efbe9;
L_0x004efde5:
    // 004efde5  83f809                 +cmp eax, 9
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(9 /*0x9*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004efde8  75f2                   -jne 0x4efddc
    if (!cpu.flags.zf)
    {
        goto L_0x004efddc;
    }
    // 004efdea  8b3dc4515600           -mov edi, dword ptr [0x5651c4]
    cpu.edi = app->getMemory<x86::reg32>(x86::reg32(5657028) /* 0x5651c4 */);
    // 004efdf0  85ff                   +test edi, edi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edi & cpu.edi));
    // 004efdf2  0f8ef1fdffff           -jle 0x4efbe9
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004efbe9;
    }
    // 004efdf8  8d0cbd00000000         -lea ecx, [edi*4]
    cpu.ecx = x86::reg32(cpu.edi * 4);
    // 004efdff  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
L_0x004efe01:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004efe01  a1c8515600             -mov eax, dword ptr [0x5651c8]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5657032) /* 0x5651c8 */);
    // 004efe06  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 004efe08  8b18                   -mov ebx, dword ptr [eax]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.eax);
    // 004efe0a  39de                   +cmp esi, ebx
    {
        x86::reg32 tmp1 = cpu.esi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ebx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004efe0c  7d07                   -jge 0x4efe15
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004efe15;
    }
    // 004efe0e  89de                   -mov esi, ebx
    cpu.esi = cpu.ebx;
    // 004efe10  e9d4fdffff             -jmp 0x4efbe9
    goto L_0x004efbe9;
L_0x004efe15:
    // 004efe15  83c204                 -add edx, 4
    (cpu.edx) += x86::reg32(x86::sreg32(4 /*0x4*/));
    // 004efe18  39ca                   +cmp edx, ecx
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
    // 004efe1a  7ce5                   -jl 0x4efe01
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004efe01;
    }
    // 004efe1c  e9c8fdffff             -jmp 0x4efbe9
    goto L_0x004efbe9;
L_0x004efe21:
    // 004efe21  ff1590725600           -call dword ptr [0x567290]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(5665424) /* 0x567290 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004efe27  e967ffffff             -jmp 0x4efd93
    goto L_0x004efd93;
}

/* align: skip 0x8d 0x44 0x20 0x00 */
void Application::sub_4efe30(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004efe30  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004efe31  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 004efe33  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004efe35  89da                   -mov edx, ebx
    cpu.edx = cpu.ebx;
    // 004efe37  e8140a0000             -call 0x4f0850
    cpu.esp -= 4;
    sub_4f0850(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004efe3c  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004efe3e  e80dfdffff             -call 0x4efb50
    cpu.esp -= 4;
    sub_4efb50(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004efe43  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004efe44  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 */
void Application::sub_4efe50(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004efe50  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004efe51  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004efe52  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004efe53  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004efe54  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004efe55  83ec0c                 -sub esp, 0xc
    (cpu.esp) -= x86::reg32(x86::sreg32(12 /*0xc*/));
    // 004efe58  890424                 -mov dword ptr [esp], eax
    app->getMemory<x86::reg32>(cpu.esp) = cpu.eax;
    // 004efe5b  89542404               -mov dword ptr [esp + 4], edx
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(4) /* 0x4 */) = cpu.edx;
    // 004efe5f  8b1424                 -mov edx, dword ptr [esp]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    // 004efe62  a1a0725600             -mov eax, dword ptr [0x5672a0]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5665440) /* 0x5672a0 */);
    // 004efe67  31ff                   -xor edi, edi
    cpu.edi ^= x86::reg32(x86::sreg32(cpu.edi));
    // 004efe69  31f6                   -xor esi, esi
    cpu.esi ^= x86::reg32(x86::sreg32(cpu.esi));
    // 004efe6b  31ed                   -xor ebp, ebp
    cpu.ebp ^= x86::reg32(x86::sreg32(cpu.ebp));
    // 004efe6d  89442408               -mov dword ptr [esp + 8], eax
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(8) /* 0x8 */) = cpu.eax;
    // 004efe71  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 004efe73  7411                   -je 0x4efe86
    if (cpu.flags.zf)
    {
        goto L_0x004efe86;
    }
L_0x004efe75:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004efe75  3b742404               +cmp esi, dword ptr [esp + 4]
    {
        x86::reg32 tmp1 = cpu.esi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.esp + x86::reg32(4) /* 0x4 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004efe79  7c3a                   -jl 0x4efeb5
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004efeb5;
    }
L_0x004efe7b:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004efe7b  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 004efe7d  83c40c                 -add esp, 0xc
    (cpu.esp) += x86::reg32(x86::sreg32(12 /*0xc*/));
    // 004efe80  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004efe81  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004efe82  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004efe83  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004efe84  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004efe85  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004efe86:
    // 004efe86  b924c65400             -mov ecx, 0x54c624
    cpu.ecx = 5555748 /*0x54c624*/;
    // 004efe8b  bb34c65400             -mov ebx, 0x54c634
    cpu.ebx = 5555764 /*0x54c634*/;
    // 004efe90  b847000000             -mov eax, 0x47
    cpu.eax = 71 /*0x47*/;
    // 004efe95  6840c65400             -push 0x54c640
    app->getMemory<x86::reg32>(cpu.esp-4) = 5555776 /*0x54c640*/;
    cpu.esp -= 4;
    // 004efe9a  890d90215500           -mov dword ptr [0x552190], ecx
    app->getMemory<x86::reg32>(x86::reg32(5579152) /* 0x552190 */) = cpu.ecx;
    // 004efea0  891d94215500           -mov dword ptr [0x552194], ebx
    app->getMemory<x86::reg32>(x86::reg32(5579156) /* 0x552194 */) = cpu.ebx;
    // 004efea6  a398215500             -mov dword ptr [0x552198], eax
    app->getMemory<x86::reg32>(x86::reg32(5579160) /* 0x552198 */) = cpu.eax;
    // 004efeab  e86011f1ff             -call 0x401010
    cpu.esp -= 4;
    nfs3hp::Error(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004efeb0  83c404                 +add esp, 4
    {
        x86::reg32& tmp1 = cpu.esp;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(4 /*0x4*/));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 004efeb3  ebc0                   -jmp 0x4efe75
    goto L_0x004efe75;
L_0x004efeb5:
    // 004efeb5  89e0                   -mov eax, esp
    cpu.eax = cpu.esp;
    // 004efeb7  89ea                   -mov edx, ebp
    cpu.edx = cpu.ebp;
    // 004efeb9  ff1594725600           -call dword ptr [0x567294]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(5665428) /* 0x567294 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004efebf  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 004efec1  89c5                   -mov ebp, eax
    cpu.ebp = cpu.eax;
    // 004efec3  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004efec5  74b4                   -je 0x4efe7b
    if (cpu.flags.zf)
    {
        goto L_0x004efe7b;
    }
    // 004efec7  e8a4fbffff             -call 0x4efa70
    cpu.esp -= 4;
    sub_4efa70(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004efecc  46                     -inc esi
    (cpu.esi)++;
    // 004efecd  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004efecf  74a4                   -je 0x4efe75
    if (cpu.flags.zf)
    {
        goto L_0x004efe75;
    }
    // 004efed1  8b5805                 -mov ebx, dword ptr [eax + 5]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(5) /* 0x5 */);
    // 004efed4  8b442408               -mov eax, dword ptr [esp + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(8) /* 0x8 */);
    // 004efed8  c1fb18                 -sar ebx, 0x18
    cpu.ebx = x86::reg32(x86::sreg32(cpu.ebx) >> (24 /*0x18*/ % 32));
    // 004efedb  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004efedd  7504                   -jne 0x4efee3
    if (!cpu.flags.zf)
    {
        goto L_0x004efee3;
    }
    // 004efedf  01df                   +add edi, ebx
    {
        x86::reg32& tmp1 = cpu.edi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ebx));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 004efee1  eb92                   -jmp 0x4efe75
    goto L_0x004efe75;
L_0x004efee3:
    // 004efee3  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004efee5  e826fcffff             -call 0x4efb10
    cpu.esp -= 4;
    sub_4efb10(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004efeea  01c3                   -add ebx, eax
    (cpu.ebx) += x86::reg32(x86::sreg32(cpu.eax));
    // 004efeec  01df                   +add edi, ebx
    {
        x86::reg32& tmp1 = cpu.edi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ebx));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 004efeee  eb85                   -jmp 0x4efe75
    goto L_0x004efe75;
}

/* align: skip  */
void Application::sub_4efef0(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004efef0  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004efef1  ba00010000             -mov edx, 0x100
    cpu.edx = 256 /*0x100*/;
    // 004efef6  e855ffffff             -call 0x4efe50
    cpu.esp -= 4;
    sub_4efe50(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004efefb  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004efefc  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x00 0x00 0x00 */
void Application::sub_4eff00(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004eff00  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004eff01  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004eff02  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004eff03  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004eff04  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 004eff06  8b5034                 -mov edx, dword ptr [eax + 0x34]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(52) /* 0x34 */);
    // 004eff09  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 004eff0b  752f                   -jne 0x4eff3c
    if (!cpu.flags.zf)
    {
        goto L_0x004eff3c;
    }
L_0x004eff0d:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004eff0d  8b592c                 -mov ebx, dword ptr [ecx + 0x2c]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(44) /* 0x2c */);
    // 004eff10  85db                   +test ebx, ebx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & cpu.ebx));
    // 004eff12  7407                   -je 0x4eff1b
    if (cpu.flags.zf)
    {
        goto L_0x004eff1b;
    }
    // 004eff14  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 004eff16  e8f59b0100             -call 0x509b10
    cpu.esp -= 4;
    sub_509b10(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x004eff1b:
    // 004eff1b  8b7130                 -mov esi, dword ptr [ecx + 0x30]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(48) /* 0x30 */);
    // 004eff1e  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 004eff20  7526                   -jne 0x4eff48
    if (!cpu.flags.zf)
    {
        goto L_0x004eff48;
    }
L_0x004eff22:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004eff22  c6411d00               -mov byte ptr [ecx + 0x1d], 0
    app->getMemory<x86::reg8>(cpu.ecx + x86::reg32(29) /* 0x1d */) = 0 /*0x0*/;
    // 004eff26  c6411c00               -mov byte ptr [ecx + 0x1c], 0
    app->getMemory<x86::reg8>(cpu.ecx + x86::reg32(28) /* 0x1c */) = 0 /*0x0*/;
    // 004eff2a  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004eff2c  c7016b4e4957           -mov dword ptr [ecx], 0x57494e6b
    app->getMemory<x86::reg32>(cpu.ecx) = 1464421995 /*0x57494e6b*/;
    // 004eff32  e85919ffff             -call 0x4e1890
    cpu.esp -= 4;
    nfs3hp::ea::purgememadr(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004eff37  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004eff38  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004eff39  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004eff3a  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004eff3b  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004eff3c:
    // 004eff3c  b8d0389f00             -mov eax, 0x9f38d0
    cpu.eax = 10434768 /*0x9f38d0*/;
    // 004eff41  e8ead7ffff             -call 0x4ed730
    cpu.esp -= 4;
    sub_4ed730(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004eff46  ebc5                   -jmp 0x4eff0d
    goto L_0x004eff0d;
L_0x004eff48:
    // 004eff48  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004eff4a  e8c19b0100             -call 0x509b10
    cpu.esp -= 4;
    sub_509b10(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004eff4f  ebd1                   -jmp 0x4eff22
    goto L_0x004eff22;
}

/* sub_4eff60: native, nfs3hp::watcom::strtok */

/* sub_4f0010: native, nfs3hp::ea::keyCharacter */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 */
void Application::sub_4f00d0(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004f00d0  e89bc8fdff             -call 0x4cc970
    cpu.esp -= 4;
    nfs3hp::frontend::nextKey(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004f00d5  25ffff0000             -and eax, 0xffff
    cpu.eax &= x86::reg32(x86::sreg32(65535 /*0xffff*/));
    // 004f00da  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x40 0x00 0x8b 0xc9 */
void Application::sub_4f00e0(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004f00e0  e88bc8fdff             -call 0x4cc970
    cpu.esp -= 4;
    nfs3hp::frontend::nextKey(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004f00e5  25ffff0000             +and eax, 0xffff
    cpu.clear_co();
    cpu.set_szp((cpu.eax &= x86::reg32(x86::sreg32(65535 /*0xffff*/))));
    // 004f00ea  e995c40100             -jmp 0x50c584
    return sub_50c584(app, cpu.handOver());
}

/* align: skip 0x90 */
void Application::sub_4f00f0(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004f00f0  a3d0515600             -mov dword ptr [0x5651d0], eax
    app->getMemory<x86::reg32>(x86::reg32(5657040) /* 0x5651d0 */) = cpu.eax;
    // 004f00f5  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_4f0100: native, nfs3hp::ea::keyFromHook */

/* sub_4f0120: native, nfs3hp::ea::inkey */

/* sub_4f0160: native, nfs3hp::dead::stub_0x4f0160 */

/* sub_4f01c0: native, nfs3hp::dead::stub_0x4f01c0 */

/* align: skip  */
void Application::sub_4f01f0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004f01f0  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004f01f1  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004f01f2  833d9012560000         +cmp dword ptr [0x561290], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5640848) /* 0x561290 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004f01f9  741d                   -je 0x4f0218
    if (cpu.flags.zf)
    {
        goto L_0x004f0218;
    }
L_0x004f01fb:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004f01fb  b901000000             -mov ecx, 1
    cpu.ecx = 1 /*0x1*/;
    // 004f0200  ba80000000             -mov edx, 0x80
    cpu.edx = 128 /*0x80*/;
    // 004f0205  b818485600             -mov eax, 0x564818
    cpu.eax = 5654552 /*0x564818*/;
    // 004f020a  890d88747f00           -mov dword ptr [0x7f7488], ecx
    app->getMemory<x86::reg32>(x86::reg32(8352904) /* 0x7f7488 */) = cpu.ecx;
    // 004f0210  e8f704ffff             -call 0x4e070c
    cpu.esp -= 4;
    nfs3hp::fillZero(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004f0215  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004f0216  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004f0217  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004f0218:
    // 004f0218  e8c3b0ffff             -call 0x4eb2e0
    cpu.esp -= 4;
    nfs3hp::ea::makeLock(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004f021d  a390125600             -mov dword ptr [0x561290], eax
    app->getMemory<x86::reg32>(x86::reg32(5640848) /* 0x561290 */) = cpu.eax;
    // 004f0222  ebd7                   -jmp 0x4f01fb
    goto L_0x004f01fb;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 */
void Application::sub_4f0230(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004f0230  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004f0231  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 004f0233  891588747f00           -mov dword ptr [0x7f7488], edx
    app->getMemory<x86::reg32>(x86::reg32(8352904) /* 0x7f7488 */) = cpu.edx;
    // 004f0239  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004f023a  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_4f0240: native, nfs3hp::ea::flushKeys */

/* sub_4f0250: native, nfs3hp::dead::stub_0x4f0250 */

/* sub_4f0260: native, nfs3hp::watcom::chdir */

/* align: skip 0x00 0x00 0x00 0x00 0x00 */
void Application::sub_4f0280(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004f0280  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004f0281  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004f0282  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004f0283  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004f0284  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004f0285  81ec40010000           -sub esp, 0x140
    (cpu.esp) -= x86::reg32(x86::sreg32(320 /*0x140*/));
    // 004f028b  8b15d4515600           -mov edx, dword ptr [0x5651d4]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5657044) /* 0x5651d4 */);
    // 004f0291  31f6                   -xor esi, esi
    cpu.esi ^= x86::reg32(x86::sreg32(cpu.esi));
    // 004f0293  83faff                 +cmp edx, -1
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(-1 /*-0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004f0296  7409                   -je 0x4f02a1
    if (cpu.flags.zf)
    {
        goto L_0x004f02a1;
    }
    // 004f0298  bfc90a9f00             -mov edi, 0x9f0ac9
    cpu.edi = 10422985 /*0x9f0ac9*/;
L_0x004f029d:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004f029d  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 004f029f  740e                   -je 0x4f02af
    if (cpu.flags.zf)
    {
        goto L_0x004f02af;
    }
L_0x004f02a1:
    // 004f02a1  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004f02a3  81c440010000           -add esp, 0x140
    (cpu.esp) += x86::reg32(x86::sreg32(320 /*0x140*/));
    // 004f02a9  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004f02aa  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004f02ab  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004f02ac  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004f02ad  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004f02ae  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004f02af:
    // 004f02af  89e0                   -mov eax, esp
    cpu.eax = cpu.esp;
    // 004f02b1  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004f02b2  8b0dd4515600           -mov ecx, dword ptr [0x5651d4]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(5657044) /* 0x5651d4 */);
    // 004f02b8  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004f02b9  2eff15d0445300         -call dword ptr cs:[0x5344d0]
    cpu.ip = app->getMemory<x86::reg32>(cpu.ecs + x86::reg32(5457104) /* 0x5344d0 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004f02c0  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004f02c2  743f                   -je 0x4f0303
    if (cpu.flags.zf)
    {
        goto L_0x004f0303;
    }
    // 004f02c4  8b1dc0099f00           -mov ebx, dword ptr [0x9f09c0]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(10422720) /* 0x9f09c0 */);
    // 004f02ca  30e4                   -xor ah, ah
    cpu.ah ^= x86::reg8(x86::sreg8(cpu.ah));
    // 004f02cc  bac4099f00             -mov edx, 0x9f09c4
    cpu.edx = 10422724 /*0x9f09c4*/;
    // 004f02d1  88a3c90a9f00           -mov byte ptr [ebx + 0x9f0ac9], ah
    app->getMemory<x86::reg8>(cpu.ebx + x86::reg32(10422985) /* 0x9f0ac9 */) = cpu.ah;
    // 004f02d7  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 004f02d9  e8520bffff             -call 0x4e0e30
    cpu.esp -= 4;
    nfs3hp::watcom::strncpy(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004f02de  bb04010000             -mov ebx, 0x104
    cpu.ebx = 260 /*0x104*/;
    // 004f02e3  8d54242c               -lea edx, [esp + 0x2c]
    cpu.edx = x86::reg32(cpu.esp + x86::reg32(44) /* 0x2c */);
    // 004f02e7  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 004f02e9  e802ebffff             -call 0x4eedf0
    cpu.esp -= 4;
    nfs3hp::watcom::strncat(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004f02ee  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004f02ef  2eff1520455300         -call dword ptr cs:[0x534520]
    cpu.ip = app->getMemory<x86::reg32>(cpu.ecs + x86::reg32(5457184) /* 0x534520 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004f02f6  83f8ff                 +cmp eax, -1
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(-1 /*-0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004f02f9  74a2                   -je 0x4f029d
    if (cpu.flags.zf)
    {
        goto L_0x004f029d;
    }
    // 004f02fb  a810                   +test al, 0x10
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.al & 16 /*0x10*/));
    // 004f02fd  759e                   -jne 0x4f029d
    if (!cpu.flags.zf)
    {
        goto L_0x004f029d;
    }
    // 004f02ff  89fe                   -mov esi, edi
    cpu.esi = cpu.edi;
    // 004f0301  eb9a                   -jmp 0x4f029d
    goto L_0x004f029d;
L_0x004f0303:
    // 004f0303  8b1dd4515600           -mov ebx, dword ptr [0x5651d4]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(5657044) /* 0x5651d4 */);
    // 004f0309  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004f030a  beffffffff             -mov esi, 0xffffffff
    cpu.esi = 4294967295 /*0xffffffff*/;
    // 004f030f  2eff15c8445300         -call dword ptr cs:[0x5344c8]
    cpu.ip = app->getMemory<x86::reg32>(cpu.ecs + x86::reg32(5457096) /* 0x5344c8 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004f0316  8935d4515600           -mov dword ptr [0x5651d4], esi
    app->getMemory<x86::reg32>(x86::reg32(5657044) /* 0x5651d4 */) = cpu.esi;
    // 004f031c  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 004f031e  81c440010000           -add esp, 0x140
    (cpu.esp) += x86::reg32(x86::sreg32(320 /*0x140*/));
    // 004f0324  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004f0325  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004f0326  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004f0327  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004f0328  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004f0329  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 */
void Application::sub_4f0330(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004f0330  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004f0331  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004f0332  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004f0333  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004f0334  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004f0335  81ec40010000           -sub esp, 0x140
    (cpu.esp) -= x86::reg32(x86::sreg32(320 /*0x140*/));
    // 004f033b  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 004f033d  8b15d4515600           -mov edx, dword ptr [0x5651d4]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5657044) /* 0x5651d4 */);
    // 004f0343  83faff                 +cmp edx, -1
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(-1 /*-0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004f0346  0f856b000000           -jne 0x4f03b7
    if (!cpu.flags.zf)
    {
        goto L_0x004f03b7;
    }
L_0x004f034c:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004f034c  bb04010000             -mov ebx, 0x104
    cpu.ebx = 260 /*0x104*/;
    // 004f0351  b8c4099f00             -mov eax, 0x9f09c4
    cpu.eax = 10422724 /*0x9f09c4*/;
    // 004f0356  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 004f0358  bfc4099f00             -mov edi, 0x9f09c4
    cpu.edi = 10422724 /*0x9f09c4*/;
    // 004f035d  e8ce0affff             -call 0x4e0e30
    cpu.esp -= 4;
    nfs3hp::watcom::strncpy(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004f0362  29c9                   -sub ecx, ecx
    (cpu.ecx) -= x86::reg32(x86::sreg32(cpu.ecx));
    // 004f0364  49                     -dec ecx
    (cpu.ecx)--;
    // 004f0365  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
    // 004f0367  f2ae                   -repne scasb al, byte ptr es:[edi]
    while (cpu.ecx)
    {
        {
            x86::reg8 tmp1 = cpu.al;
            x86::reg8 tmp2 = x86::reg8(x86::sreg8(app->getMemory<x86::reg8>(cpu.ees + cpu.edi)));
            x86::reg8 result = tmp1 - tmp2;
            cpu.flags.cf = tmp1 < tmp2;
            cpu.flags.of = 1 & (tmp1 >> 7);
            cpu.flags.of ^= 1 & (result >> 7);
            cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
            cpu.set_szp(result);
        }
        if (cpu.flags.df)
        {
            cpu.edi -= 1;
        }
        else
        {
            cpu.edi += 1;
        }
        --cpu.ecx;
        if (cpu.flags.zf)
            break;
    }
    // 004f0369  f7d1                   -not ecx
    cpu.ecx = ~cpu.ecx;
    // 004f036b  49                     -dec ecx
    (cpu.ecx)--;
    // 004f036c  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004f036e  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    // 004f0370  7e15                   -jle 0x4f0387
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004f0387;
    }
L_0x004f0372:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004f0372  8a90c4099f00           -mov dl, byte ptr [eax + 0x9f09c4]
    cpu.dl = app->getMemory<x86::reg8>(cpu.eax + x86::reg32(10422724) /* 0x9f09c4 */);
    // 004f0378  80fa5c                 +cmp dl, 0x5c
    {
        x86::reg8 tmp1 = cpu.dl;
        x86::reg8 tmp2 = x86::reg8(x86::sreg8(92 /*0x5c*/));
        x86::reg8 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 7);
        cpu.flags.of ^= 1 & (result >> 7);
        cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
        cpu.set_szp(result);
    }
    // 004f037b  740a                   -je 0x4f0387
    if (cpu.flags.zf)
    {
        goto L_0x004f0387;
    }
    // 004f037d  80fa3a                 +cmp dl, 0x3a
    {
        x86::reg8 tmp1 = cpu.dl;
        x86::reg8 tmp2 = x86::reg8(x86::sreg8(58 /*0x3a*/));
        x86::reg8 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 7);
        cpu.flags.of ^= 1 & (result >> 7);
        cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
        cpu.set_szp(result);
    }
    // 004f0380  7405                   -je 0x4f0387
    if (cpu.flags.zf)
    {
        goto L_0x004f0387;
    }
    // 004f0382  48                     -dec eax
    (cpu.eax)--;
    // 004f0383  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004f0385  7feb                   -jg 0x4f0372
    if (!cpu.flags.zf && (cpu.flags.sf == cpu.flags.of))
    {
        goto L_0x004f0372;
    }
L_0x004f0387:
    // 004f0387  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004f0389  7536                   -jne 0x4f03c1
    if (!cpu.flags.zf)
    {
        goto L_0x004f03c1;
    }
L_0x004f038b:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004f038b  a3c0099f00             -mov dword ptr [0x9f09c0], eax
    app->getMemory<x86::reg32>(x86::reg32(10422720) /* 0x9f09c0 */) = cpu.eax;
    // 004f0390  89e0                   -mov eax, esp
    cpu.eax = cpu.esp;
    // 004f0392  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004f0393  68c4099f00             -push 0x9f09c4
    app->getMemory<x86::reg32>(cpu.esp-4) = 10422724 /*0x9f09c4*/;
    cpu.esp -= 4;
    // 004f0398  2eff15cc445300         -call dword ptr cs:[0x5344cc]
    cpu.ip = app->getMemory<x86::reg32>(cpu.ecs + x86::reg32(5457100) /* 0x5344cc */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004f039f  a3d4515600             -mov dword ptr [0x5651d4], eax
    app->getMemory<x86::reg32>(x86::reg32(5657044) /* 0x5651d4 */) = cpu.eax;
    // 004f03a4  83f8ff                 +cmp eax, -1
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(-1 /*-0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004f03a7  751b                   -jne 0x4f03c4
    if (!cpu.flags.zf)
    {
        goto L_0x004f03c4;
    }
    // 004f03a9  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 004f03ab  81c440010000           +add esp, 0x140
    {
        x86::reg32& tmp1 = cpu.esp;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(320 /*0x140*/));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 004f03b1  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004f03b2  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004f03b3  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004f03b4  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004f03b5  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004f03b6  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004f03b7:
    // 004f03b7  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004f03b8  2eff15c8445300         -call dword ptr cs:[0x5344c8]
    cpu.ip = app->getMemory<x86::reg32>(cpu.ecs + x86::reg32(5457096) /* 0x5344c8 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004f03bf  eb8b                   -jmp 0x4f034c
    goto L_0x004f034c;
L_0x004f03c1:
    // 004f03c1  40                     +inc eax
    {
        x86::reg32& tmp = cpu.eax;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 004f03c2  ebc7                   -jmp 0x4f038b
    goto L_0x004f038b;
L_0x004f03c4:
    // 004f03c4  bac4099f00             -mov edx, 0x9f09c4
    cpu.edx = 10422724 /*0x9f09c4*/;
    // 004f03c9  8b1dc0099f00           -mov ebx, dword ptr [0x9f09c0]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(10422720) /* 0x9f09c0 */);
    // 004f03cf  30c9                   -xor cl, cl
    cpu.cl ^= x86::reg8(x86::sreg8(cpu.cl));
    // 004f03d1  b8c90a9f00             -mov eax, 0x9f0ac9
    cpu.eax = 10422985 /*0x9f0ac9*/;
    // 004f03d6  888bc90a9f00           -mov byte ptr [ebx + 0x9f0ac9], cl
    app->getMemory<x86::reg8>(cpu.ebx + x86::reg32(10422985) /* 0x9f0ac9 */) = cpu.cl;
    // 004f03dc  e84f0affff             -call 0x4e0e30
    cpu.esp -= 4;
    nfs3hp::watcom::strncpy(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004f03e1  bb04010000             -mov ebx, 0x104
    cpu.ebx = 260 /*0x104*/;
    // 004f03e6  8d54242c               -lea edx, [esp + 0x2c]
    cpu.edx = x86::reg32(cpu.esp + x86::reg32(44) /* 0x2c */);
    // 004f03ea  b8c90a9f00             -mov eax, 0x9f0ac9
    cpu.eax = 10422985 /*0x9f0ac9*/;
    // 004f03ef  e8fce9ffff             -call 0x4eedf0
    cpu.esp -= 4;
    nfs3hp::watcom::strncat(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004f03f4  68c90a9f00             -push 0x9f0ac9
    app->getMemory<x86::reg32>(cpu.esp-4) = 10422985 /*0x9f0ac9*/;
    cpu.esp -= 4;
    // 004f03f9  2eff1520455300         -call dword ptr cs:[0x534520]
    cpu.ip = app->getMemory<x86::reg32>(cpu.ecs + x86::reg32(5457184) /* 0x534520 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004f0400  83f8ff                 +cmp eax, -1
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(-1 /*-0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004f0403  7415                   -je 0x4f041a
    if (cpu.flags.zf)
    {
        goto L_0x004f041a;
    }
    // 004f0405  a810                   +test al, 0x10
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.al & 16 /*0x10*/));
    // 004f0407  7511                   -jne 0x4f041a
    if (!cpu.flags.zf)
    {
        goto L_0x004f041a;
    }
    // 004f0409  b8c90a9f00             -mov eax, 0x9f0ac9
    cpu.eax = 10422985 /*0x9f0ac9*/;
    // 004f040e  81c440010000           -add esp, 0x140
    (cpu.esp) += x86::reg32(x86::sreg32(320 /*0x140*/));
    // 004f0414  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004f0415  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004f0416  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004f0417  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004f0418  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004f0419  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004f041a:
    // 004f041a  e861feffff             -call 0x4f0280
    cpu.esp -= 4;
    sub_4f0280(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004f041f  81c440010000           -add esp, 0x140
    (cpu.esp) += x86::reg32(x86::sreg32(320 /*0x140*/));
    // 004f0425  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004f0426  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004f0427  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004f0428  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004f0429  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004f042a  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_4f0430: native, nfs3hp::watcom::atoi */

/* sub_4f0490: native, nfs3hp::watcom::atol */

/* sub_4f04f0: native, nfs3hp::watcom::cget_string */

/* sub_4f051c: native, nfs3hp::watcom::uncget_string */

/* sub_4f0520: native, nfs3hp::watcom::vsscanf */

/* sub_4f0548: native, nfs3hp::watcom::sscanf */

/* sub_4f0570: native, nfs3hp::watcom::fgets */

/* sub_4f05f0: native, nfs3hp::watcom::access */

/* align: skip 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 */
void Application::sub_4f0630(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004f0630  a1a4c17900             -mov eax, dword ptr [0x79c1a4]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(7979428) /* 0x79c1a4 */);
    // 004f0635  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_4f0640: native, nfs3hp::dead::stub_0x4f0640 */

/* align: skip 0x8d 0x44 0x20 0x00 */
void Application::sub_4f0650(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004f0650  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004f0651  8b15dc515600           -mov edx, dword ptr [0x5651dc]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5657052) /* 0x5651dc */);
    // 004f0657  e8d4ffffff             -call 0x4f0630
    cpu.esp -= 4;
    sub_4f0630(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004f065c  a3dc515600             -mov dword ptr [0x5651dc], eax
    app->getMemory<x86::reg32>(x86::reg32(5657052) /* 0x5651dc */) = cpu.eax;
    // 004f0661  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 004f0663  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004f0664  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_4f0670: native, nfs3hp::dead::stub_0x4f0670 */

/* sub_4f0690: native, nfs3hp::dead::stub_0x4f0690 */

/* sub_4f06a1: native, nfs3hp::dead::stub_0x4f06a1 */

/* sub_4f06c0: native, nfs3hp::dead::stub_0x4f06c0 */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8b 0xd2 */
void Application::sub_4f06e0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004f06e0  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004f06e1  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004f06e3  e848ffffff             -call 0x4f0630
    cpu.esp -= 4;
    sub_4f0630(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004f06e8  01c2                   -add edx, eax
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.eax));
    // 004f06ea  e841ffffff             -call 0x4f0630
    cpu.esp -= 4;
    sub_4f0630(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004f06ef  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 004f06f1  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004f06f3  7c02                   -jl 0x4f06f7
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004f06f7;
    }
    // 004f06f5  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004f06f6  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004f06f7:
    app->unlockContext(cpu);
    win32::Thread::sleep(0);
    app->lockContext(cpu);
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004f06f7  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 004f06f9  e8326fffff             -call 0x4e7630
    cpu.esp -= 4;
    nfs3hp::port::runSystemTasks(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004f06fe  e82dffffff             -call 0x4f0630
    cpu.esp -= 4;
    sub_4f0630(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004f0703  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 004f0705  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004f0707  7cee                   -jl 0x4f06f7
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004f06f7;
    }
    // 004f0709  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004f070a  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_4f0710: native, nfs3hp::watcom::sleep */

/* sub_4f0730: native, nfs3hp::watcom::getcwd */

/* sub_4f07d0: native, nfs3hp::watcom::getdiskfree */

/* align: skip 0x00 0x00 */
void Application::sub_4f0840(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004f0840  a118725600             -mov eax, dword ptr [0x567218]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5665304) /* 0x567218 */);
    // 004f0845  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x54 0x22 0x00 */
void Application::sub_4f0850(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004f0850  8915fc715600           -mov dword ptr [0x5671fc], edx
    app->getMemory<x86::reg32>(x86::reg32(5665276) /* 0x5671fc */) = cpu.edx;
    // 004f0856  a3f8715600             -mov dword ptr [0x5671f8], eax
    app->getMemory<x86::reg32>(x86::reg32(5665272) /* 0x5671f8 */) = cpu.eax;
    // 004f085b  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x44 0x20 0x00 */
void Application::sub_4f0860(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004f0860  a30c725600             -mov dword ptr [0x56720c], eax
    app->getMemory<x86::reg32>(x86::reg32(5665292) /* 0x56720c */) = cpu.eax;
    // 004f0865  e966b80100             -jmp 0x50c0d0
    return sub_50c0d0(app, cpu.handOver());
}

/* sub_4f0870: native, nfs3hp::dead::stub_0x4f0870 */

}
