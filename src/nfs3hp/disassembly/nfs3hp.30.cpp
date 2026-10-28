#include "nfs3hp.h"
#include <lib/thread.h>

namespace nfs3hp
{

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x8d 0x40 0x00 */
void Application::sub_4d03c0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004d03c0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004d03c1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004d03c2  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004d03c3  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004d03c4  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004d03c5  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004d03c7  83ec08                 -sub esp, 8
    (cpu.esp) -= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 004d03ca  89d1                   -mov ecx, edx
    cpu.ecx = cpu.edx;
    // 004d03cc  8d5dfc                 -lea ebx, [ebp - 4]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004d03cf  8d55f8                 -lea edx, [ebp - 8]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004d03d2  e8e9edffff             -call 0x4cf1c0
    cpu.esp -= 4;
    sub_4cf1c0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d03d7  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004d03d9  0f8573000000           -jne 0x4d0452
    if (!cpu.flags.zf)
    {
        goto L_0x004d0452;
    }
    // 004d03df  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004d03e2  3b4820                 +cmp ecx, dword ptr [eax + 0x20]
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.eax + x86::reg32(32) /* 0x20 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004d03e5  0f8267000000           -jb 0x4d0452
    if (cpu.flags.cf)
    {
        goto L_0x004d0452;
    }
    // 004d03eb  8b4024                 -mov eax, dword ptr [eax + 0x24]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(36) /* 0x24 */);
    // 004d03ee  83e808                 -sub eax, 8
    (cpu.eax) -= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 004d03f1  39c1                   +cmp ecx, eax
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.eax));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004d03f3  775d                   -ja 0x4d0452
    if (!cpu.flags.cf && !cpu.flags.zf)
    {
        goto L_0x004d0452;
    }
    // 004d03f5  8339fe                 +cmp dword ptr [ecx], -2
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.ecx);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(-2 /*-0x2*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004d03f8  7458                   -je 0x4d0452
    if (cpu.flags.zf)
    {
        goto L_0x004d0452;
    }
    // 004d03fa  c701feffffff           -mov dword ptr [ecx], 0xfffffffe
    app->getMemory<x86::reg32>(cpu.ecx) = 4294967294 /*0xfffffffe*/;
    // 004d0400  8b5104                 -mov edx, dword ptr [ecx + 4]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(4) /* 0x4 */);
    // 004d0403  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004d0406  e815eeffff             -call 0x4cf220
    cpu.esp -= 4;
    sub_4cf220(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d040b  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004d040e  8b7004                 -mov esi, dword ptr [eax + 4]
    cpu.esi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 004d0411  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004d0412  ff15b8445300           -call dword ptr [0x5344b8]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(5457080) /* 0x5344b8 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d0418  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004d041b  8b5828                 -mov ebx, dword ptr [eax + 0x28]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(40) /* 0x28 */);
    // 004d041e  83fb02                 +cmp ebx, 2
    {
        x86::reg32 tmp1 = cpu.ebx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(2 /*0x2*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004d0421  7507                   -jne 0x4d042a
    if (!cpu.flags.zf)
    {
        goto L_0x004d042a;
    }
    // 004d0423  c7402801000000         -mov dword ptr [eax + 0x28], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(40) /* 0x28 */) = 1 /*0x1*/;
L_0x004d042a:
    // 004d042a  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004d042d  8b7804                 -mov edi, dword ptr [eax + 4]
    cpu.edi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 004d0430  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004d0431  ff1588455300           -call dword ptr [0x534588]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(5457288) /* 0x534588 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d0437  83fb02                 +cmp ebx, 2
    {
        x86::reg32 tmp1 = cpu.ebx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(2 /*0x2*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004d043a  7516                   -jne 0x4d0452
    if (!cpu.flags.zf)
    {
        goto L_0x004d0452;
    }
    // 004d043c  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004d043f  83783800               +cmp dword ptr [eax + 0x38], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(56) /* 0x38 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004d0443  7405                   -je 0x4d044a
    if (cpu.flags.zf)
    {
        goto L_0x004d044a;
    }
    // 004d0445  8b5030                 -mov edx, dword ptr [eax + 0x30]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(48) /* 0x30 */);
    // 004d0448  eb03                   -jmp 0x4d044d
    goto L_0x004d044d;
L_0x004d044a:
    // 004d044a  8b502c                 -mov edx, dword ptr [eax + 0x2c]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(44) /* 0x2c */);
L_0x004d044d:
    // 004d044d  e8bef3ffff             -call 0x4cf810
    cpu.esp -= 4;
    sub_4cf810(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x004d0452:
    // 004d0452  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004d0454  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d0455  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d0456  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d0457  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d0458  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d0459  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 */
void Application::sub_4d0460(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004d0460  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004d0461  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004d0462  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004d0463  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004d0465  83ec08                 -sub esp, 8
    (cpu.esp) -= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 004d0468  8d5dfc                 -lea ebx, [ebp - 4]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004d046b  8d55f8                 -lea edx, [ebp - 8]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004d046e  e84dedffff             -call 0x4cf1c0
    cpu.esp -= 4;
    sub_4cf1c0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d0473  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004d0475  7404                   -je 0x4d047b
    if (cpu.flags.zf)
    {
        goto L_0x004d047b;
    }
    // 004d0477  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
    // 004d0479  eb06                   -jmp 0x4d0481
    goto L_0x004d0481;
L_0x004d047b:
    // 004d047b  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004d047e  8b4008                 -mov eax, dword ptr [eax + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
L_0x004d0481:
    // 004d0481  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004d0483  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d0484  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d0485  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d0486  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 */
void Application::sub_4d0490(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004d0490  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004d0491  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004d0492  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004d0493  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004d0495  83ec08                 -sub esp, 8
    (cpu.esp) -= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 004d0498  8d5dfc                 -lea ebx, [ebp - 4]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004d049b  8d55f8                 -lea edx, [ebp - 8]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004d049e  e81dedffff             -call 0x4cf1c0
    cpu.esp -= 4;
    sub_4cf1c0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d04a3  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004d04a5  7404                   -je 0x4d04ab
    if (cpu.flags.zf)
    {
        goto L_0x004d04ab;
    }
    // 004d04a7  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
    // 004d04a9  eb06                   -jmp 0x4d04b1
    goto L_0x004d04b1;
L_0x004d04ab:
    // 004d04ab  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004d04ae  8b4028                 -mov eax, dword ptr [eax + 0x28]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(40) /* 0x28 */);
L_0x004d04b1:
    // 004d04b1  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004d04b3  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d04b4  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d04b5  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d04b6  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 */
void Application::sub_4d04c0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004d04c0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004d04c1  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004d04c2  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004d04c3  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004d04c5  83ec08                 -sub esp, 8
    (cpu.esp) -= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 004d04c8  8d5dfc                 -lea ebx, [ebp - 4]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004d04cb  8d55f8                 -lea edx, [ebp - 8]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004d04ce  e8edecffff             -call 0x4cf1c0
    cpu.esp -= 4;
    sub_4cf1c0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d04d3  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004d04d5  7519                   -jne 0x4d04f0
    if (!cpu.flags.zf)
    {
        goto L_0x004d04f0;
    }
    // 004d04d7  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004d04da  83782800               +cmp dword ptr [eax + 0x28], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(40) /* 0x28 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004d04de  7510                   -jne 0x4d04f0
    if (!cpu.flags.zf)
    {
        goto L_0x004d04f0;
    }
    // 004d04e0  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004d04e3  83780800               +cmp dword ptr [eax + 8], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004d04e7  7507                   -jne 0x4d04f0
    if (!cpu.flags.zf)
    {
        goto L_0x004d04f0;
    }
    // 004d04e9  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 004d04ee  eb02                   -jmp 0x4d04f2
    goto L_0x004d04f2;
L_0x004d04f0:
    // 004d04f0  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
L_0x004d04f2:
    // 004d04f2  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004d04f4  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d04f5  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d04f6  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d04f7  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8b 0xd2 */
void Application::sub_4d0500(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004d0500  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004d0501  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004d0502  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004d0503  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004d0504  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004d0506  83ec08                 -sub esp, 8
    (cpu.esp) -= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 004d0509  8d5dfc                 -lea ebx, [ebp - 4]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004d050c  8d55f8                 -lea edx, [ebp - 8]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004d050f  e8acecffff             -call 0x4cf1c0
    cpu.esp -= 4;
    sub_4cf1c0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d0514  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004d0516  7404                   -je 0x4d051c
    if (cpu.flags.zf)
    {
        goto L_0x004d051c;
    }
    // 004d0518  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
    // 004d051a  eb0e                   -jmp 0x4d052a
    goto L_0x004d052a;
L_0x004d051c:
    // 004d051c  8b55f8                 -mov edx, dword ptr [ebp - 8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004d051f  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004d0522  8b4a20                 -mov ecx, dword ptr [edx + 0x20]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(32) /* 0x20 */);
    // 004d0525  8b4024                 -mov eax, dword ptr [eax + 0x24]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(36) /* 0x24 */);
    // 004d0528  29c8                   -sub eax, ecx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.ecx));
L_0x004d052a:
    // 004d052a  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004d052c  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d052d  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d052e  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d052f  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d0530  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x8d 0x40 0x00 */
void Application::sub_4d0540(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004d0540  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004d0541  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004d0542  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004d0543  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004d0545  83ec08                 -sub esp, 8
    (cpu.esp) -= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 004d0548  8d5dfc                 -lea ebx, [ebp - 4]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004d054b  8d55f8                 -lea edx, [ebp - 8]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004d054e  e86decffff             -call 0x4cf1c0
    cpu.esp -= 4;
    sub_4cf1c0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d0553  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004d0555  7404                   -je 0x4d055b
    if (cpu.flags.zf)
    {
        goto L_0x004d055b;
    }
    // 004d0557  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
    // 004d0559  eb06                   -jmp 0x4d0561
    goto L_0x004d0561;
L_0x004d055b:
    // 004d055b  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004d055e  8b403c                 -mov eax, dword ptr [eax + 0x3c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(60) /* 0x3c */);
L_0x004d0561:
    // 004d0561  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004d0563  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d0564  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d0565  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d0566  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 */
void Application::sub_4d0570(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004d0570  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004d0571  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004d0572  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004d0573  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004d0574  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004d0575  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004d0576  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004d0578  83ec08                 -sub esp, 8
    (cpu.esp) -= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 004d057b  8d5dfc                 -lea ebx, [ebp - 4]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004d057e  8d55f8                 -lea edx, [ebp - 8]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004d0581  e83aecffff             -call 0x4cf1c0
    cpu.esp -= 4;
    sub_4cf1c0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d0586  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004d0588  7407                   -je 0x4d0591
    if (cpu.flags.zf)
    {
        goto L_0x004d0591;
    }
    // 004d058a  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
    // 004d058c  e96f000000             -jmp 0x4d0600
    goto L_0x004d0600;
L_0x004d0591:
    // 004d0591  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004d0594  83780800               +cmp dword ptr [eax + 8], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004d0598  750b                   -jne 0x4d05a5
    if (!cpu.flags.zf)
    {
        goto L_0x004d05a5;
    }
    // 004d059a  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 004d059c  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004d059e  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d059f  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d05a0  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d05a1  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d05a2  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d05a3  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d05a4  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004d05a5:
    // 004d05a5  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004d05a8  8b4804                 -mov ecx, dword ptr [eax + 4]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 004d05ab  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004d05ac  ff15b8445300           -call dword ptr [0x5344b8]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(5457080) /* 0x5344b8 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d05b2  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004d05b5  8b780c                 -mov edi, dword ptr [eax + 0xc]
    cpu.edi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
    // 004d05b8  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004d05bb  8b704c                 -mov esi, dword ptr [eax + 0x4c]
    cpu.esi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(76) /* 0x4c */);
    // 004d05be  8b4040                 -mov eax, dword ptr [eax + 0x40]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(64) /* 0x40 */);
    // 004d05c1  8b5e0c                 -mov ebx, dword ptr [esi + 0xc]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 004d05c4  85db                   +test ebx, ebx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & cpu.ebx));
    // 004d05c6  7429                   -je 0x4d05f1
    if (cpu.flags.zf)
    {
        goto L_0x004d05f1;
    }
L_0x004d05c8:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004d05c8  8b5304                 -mov edx, dword ptr [ebx + 4]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(4) /* 0x4 */);
    // 004d05cb  89d9                   -mov ecx, ebx
    cpu.ecx = cpu.ebx;
    // 004d05cd  83fa01                 +cmp edx, 1
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
    // 004d05d0  741f                   -je 0x4d05f1
    if (cpu.flags.zf)
    {
        goto L_0x004d05f1;
    }
    // 004d05d2  8b8b24010000           -mov ecx, dword ptr [ebx + 0x124]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(292) /* 0x124 */);
    // 004d05d8  89fb                   -mov ebx, edi
    cpu.ebx = cpu.edi;
    // 004d05da  89ca                   -mov edx, ecx
    cpu.edx = cpu.ecx;
    // 004d05dc  e80fecffff             -call 0x4cf1f0
    cpu.esp -= 4;
    sub_4cf1f0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d05e1  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004d05e3  750c                   -jne 0x4d05f1
    if (!cpu.flags.zf)
    {
        goto L_0x004d05f1;
    }
    // 004d05e5  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004d05e7  8b760c                 -mov esi, dword ptr [esi + 0xc]
    cpu.esi = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 004d05ea  8b5e0c                 -mov ebx, dword ptr [esi + 0xc]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 004d05ed  85db                   +test ebx, ebx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & cpu.ebx));
    // 004d05ef  75d7                   -jne 0x4d05c8
    if (!cpu.flags.zf)
    {
        goto L_0x004d05c8;
    }
L_0x004d05f1:
    // 004d05f1  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004d05f4  8b4804                 -mov ecx, dword ptr [eax + 4]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 004d05f7  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004d05f8  ff1588455300           -call dword ptr [0x534588]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(5457288) /* 0x534588 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d05fe  8b06                   -mov eax, dword ptr [esi]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi);
L_0x004d0600:
    // 004d0600  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004d0602  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d0603  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d0604  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d0605  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d0606  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d0607  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d0608  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x90 */
void Application::sub_4d0610(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004d0610  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004d0611  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004d0612  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004d0613  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004d0615  83ec08                 -sub esp, 8
    (cpu.esp) -= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 004d0618  89d1                   -mov ecx, edx
    cpu.ecx = cpu.edx;
    // 004d061a  8d5dfc                 -lea ebx, [ebp - 4]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004d061d  8d55f8                 -lea edx, [ebp - 8]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004d0620  e89bebffff             -call 0x4cf1c0
    cpu.esp -= 4;
    sub_4cf1c0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d0625  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004d0627  7404                   -je 0x4d062d
    if (cpu.flags.zf)
    {
        goto L_0x004d062d;
    }
    // 004d0629  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
    // 004d062b  eb17                   -jmp 0x4d0644
    goto L_0x004d0644;
L_0x004d062d:
    // 004d062d  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004d0630  89ca                   -mov edx, ecx
    cpu.edx = cpu.ecx;
    // 004d0632  e809edffff             -call 0x4cf340
    cpu.esp -= 4;
    sub_4cf340(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d0637  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004d0639  7506                   -jne 0x4d0641
    if (!cpu.flags.zf)
    {
        goto L_0x004d0641;
    }
    // 004d063b  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004d063d  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d063e  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d063f  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d0640  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004d0641:
    // 004d0641  8b4004                 -mov eax, dword ptr [eax + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
L_0x004d0644:
    // 004d0644  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004d0646  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d0647  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d0648  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d0649  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_4d06f0: native, nfs3hp::port::text::drawCharacter */

/* sub_4d0a10: native, nfs3hp::render::pictureTexture */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x90 */
void Application::sub_4d0d50(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004d0d50  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004d0d51  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004d0d52  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004d0d53  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004d0d54  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004d0d55  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004d0d56  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004d0d58  81ec04020000           -sub esp, 0x204
    (cpu.esp) -= x86::reg32(x86::sreg32(516 /*0x204*/));
    // 004d0d5e  81ed82010000           -sub ebp, 0x182
    (cpu.ebp) -= x86::reg32(x86::sreg32(386 /*0x182*/));
    // 004d0d64  813dc8da7c0080020000   +cmp dword ptr [0x7cdac8], 0x280
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(8182472) /* 0x7cdac8 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(640 /*0x280*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004d0d6e  7c28                   -jl 0x4d0d98
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004d0d98;
    }
    // 004d0d70  68b4297a00             -push 0x7a29b4
    app->getMemory<x86::reg32>(cpu.esp-4) = 8006068 /*0x7a29b4*/;
    cpu.esp -= 4;
    // 004d0d75  68940b5400             -push 0x540b94
    app->getMemory<x86::reg32>(cpu.esp-4) = 5507988 /*0x540b94*/;
    cpu.esp -= 4;
    // 004d0d7a  8d857effffff           -lea eax, [ebp - 0x82]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-130) /* -0x82 */);
    // 004d0d80  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004d0d81  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 004d0d83  e808e90000             -call 0x4df690
    cpu.esp -= 4;
    nfs3hp::watcom::sprintf(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d0d88  83c40c                 -add esp, 0xc
    (cpu.esp) += x86::reg32(x86::sreg32(12 /*0xc*/));
    // 004d0d8b  30e4                   +xor ah, ah
    cpu.clear_co();
    cpu.set_szp((cpu.ah ^= x86::reg8(x86::sreg8(cpu.ah))));
    // 004d0d8d  890d88018400           -mov dword ptr [0x840188], ecx
    app->getMemory<x86::reg32>(x86::reg32(8651144) /* 0x840188 */) = cpu.ecx;
    // 004d0d93  88657e                 -mov byte ptr [ebp + 0x7e], ah
    app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(126) /* 0x7e */) = cpu.ah;
    // 004d0d96  eb3a                   -jmp 0x4d0dd2
    goto L_0x004d0dd2;
L_0x004d0d98:
    // 004d0d98  68b4297a00             -push 0x7a29b4
    app->getMemory<x86::reg32>(cpu.esp-4) = 8006068 /*0x7a29b4*/;
    cpu.esp -= 4;
    // 004d0d9d  68a40b5400             -push 0x540ba4
    app->getMemory<x86::reg32>(cpu.esp-4) = 5508004 /*0x540ba4*/;
    cpu.esp -= 4;
    // 004d0da2  8d857effffff           -lea eax, [ebp - 0x82]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-130) /* -0x82 */);
    // 004d0da8  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004d0da9  e8e2e80000             -call 0x4df690
    cpu.esp -= 4;
    nfs3hp::watcom::sprintf(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d0dae  83c40c                 -add esp, 0xc
    (cpu.esp) += x86::reg32(x86::sreg32(12 /*0xc*/));
    // 004d0db1  68b4297a00             -push 0x7a29b4
    app->getMemory<x86::reg32>(cpu.esp-4) = 8006068 /*0x7a29b4*/;
    cpu.esp -= 4;
    // 004d0db6  68b00b5400             -push 0x540bb0
    app->getMemory<x86::reg32>(cpu.esp-4) = 5508016 /*0x540bb0*/;
    cpu.esp -= 4;
    // 004d0dbb  8d457e                 -lea eax, [ebp + 0x7e]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(126) /* 0x7e */);
    // 004d0dbe  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004d0dbf  bb01000000             -mov ebx, 1
    cpu.ebx = 1 /*0x1*/;
    // 004d0dc4  e8c7e80000             -call 0x4df690
    cpu.esp -= 4;
    nfs3hp::watcom::sprintf(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d0dc9  83c40c                 -add esp, 0xc
    (cpu.esp) += x86::reg32(x86::sreg32(12 /*0xc*/));
    // 004d0dcc  891d88018400           -mov dword ptr [0x840188], ebx
    app->getMemory<x86::reg32>(x86::reg32(8651144) /* 0x840188 */) = cpu.ebx;
L_0x004d0dd2:
    // 004d0dd2  8d857effffff           -lea eax, [ebp - 0x82]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-130) /* -0x82 */);
    // 004d0dd8  e883000100             -call 0x4e0e60
    cpu.esp -= 4;
    nfs3hp::ea::fileExists(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d0ddd  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004d0ddf  0f8407020000           -je 0x4d0fec
    if (cpu.flags.zf)
    {
        goto L_0x004d0fec;
    }
    // 004d0de5  807d7e00               +cmp byte ptr [ebp + 0x7e], 0
    {
        x86::reg8 tmp1 = app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(126) /* 0x7e */);
        x86::reg8 tmp2 = x86::reg8(x86::sreg8(0 /*0x0*/));
        x86::reg8 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 7);
        cpu.flags.of ^= 1 & (result >> 7);
        cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
        cpu.set_szp(result);
    }
    // 004d0de9  7410                   -je 0x4d0dfb
    if (cpu.flags.zf)
    {
        goto L_0x004d0dfb;
    }
    // 004d0deb  8d457e                 -lea eax, [ebp + 0x7e]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(126) /* 0x7e */);
    // 004d0dee  e86d000100             -call 0x4e0e60
    cpu.esp -= 4;
    nfs3hp::ea::fileExists(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d0df3  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004d0df5  0f84f1010000           -je 0x4d0fec
    if (cpu.flags.zf)
    {
        goto L_0x004d0fec;
    }
L_0x004d0dfb:
    // 004d0dfb  ba10000000             -mov edx, 0x10
    cpu.edx = 16 /*0x10*/;
    // 004d0e00  8d857effffff           -lea eax, [ebp - 0x82]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-130) /* -0x82 */);
    // 004d0e06  bf0000803f             -mov edi, 0x3f800000
    cpu.edi = 1065353216 /*0x3f800000*/;
    // 004d0e0b  e8b0000100             -call 0x4e0ec0
    cpu.esp -= 4;
    nfs3hp::ea::loadFile(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d0e10  31f6                   -xor esi, esi
    cpu.esi ^= x86::reg32(x86::sreg32(cpu.esi));
    // 004d0e12  89857e010000           -mov dword ptr [ebp + 0x17e], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(382) /* 0x17e */) = cpu.eax;
    // 004d0e18  e803e70100             -call 0x4ef520
    cpu.esp -= 4;
    sub_4ef520(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d0e1d  31d2                   +xor edx, edx
    cpu.clear_co();
    cpu.set_szp((cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx))));
    // 004d0e1f  a118725600             -mov eax, dword ptr [0x567218]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5665304) /* 0x567218 */);
    // 004d0e24  893584018400           -mov dword ptr [0x840184], esi
    app->getMemory<x86::reg32>(x86::reg32(8651140) /* 0x840184 */) = cpu.esi;
    // 004d0e2a  893d8c018400           -mov dword ptr [0x84018c], edi
    app->getMemory<x86::reg32>(x86::reg32(8651148) /* 0x84018c */) = cpu.edi;
    // 004d0e30  a3a0f68300             -mov dword ptr [0x83f6a0], eax
    app->getMemory<x86::reg32>(x86::reg32(8648352) /* 0x83f6a0 */) = cpu.eax;
    // 004d0e35  eb46                   -jmp 0x4d0e7d
    goto L_0x004d0e7d;
L_0x004d0e37:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004d0e37  83fe20                 +cmp esi, 0x20
    {
        x86::reg32 tmp1 = cpu.esi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(32 /*0x20*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004d0e3a  7405                   -je 0x4d0e41
    if (cpu.flags.zf)
    {
        goto L_0x004d0e41;
    }
    // 004d0e3c  83fe2f                 +cmp esi, 0x2f
    {
        x86::reg32 tmp1 = cpu.esi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(47 /*0x2f*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004d0e3f  7507                   -jne 0x4d0e48
    if (!cpu.flags.zf)
    {
        goto L_0x004d0e48;
    }
L_0x004d0e41:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004d0e41  8a4708                 -mov al, byte ptr [edi + 8]
    cpu.al = app->getMemory<x86::reg8>(cpu.edi + x86::reg32(8) /* 0x8 */);
    // 004d0e44  fec8                   +dec al
    {
        x86::reg8& tmp = cpu.al;
        cpu.flags.of = 1 & (tmp >> 7);
        tmp--;
        cpu.flags.of &= ~(1 & (tmp >> 7));
        cpu.set_szp(tmp);
    }
    // 004d0e46  eb03                   -jmp 0x4d0e4b
    goto L_0x004d0e4b;
L_0x004d0e48:
    // 004d0e48  8a4308                 -mov al, byte ptr [ebx + 8]
    cpu.al = app->getMemory<x86::reg8>(cpu.ebx + x86::reg32(8) /* 0x8 */);
L_0x004d0e4b:
    // 004d0e4b  8882e0f48300           -mov byte ptr [edx + 0x83f4e0], al
    app->getMemory<x86::reg8>(cpu.edx + x86::reg32(8647904) /* 0x83f4e0 */) = cpu.al;
    // 004d0e51  eb0b                   -jmp 0x4d0e5e
    goto L_0x004d0e5e;
L_0x004d0e53:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004d0e53  8a4308                 -mov al, byte ptr [ebx + 8]
    cpu.al = app->getMemory<x86::reg8>(cpu.ebx + x86::reg32(8) /* 0x8 */);
    // 004d0e56  fec0                   -inc al
    (cpu.al)++;
    // 004d0e58  8882e0f48300           -mov byte ptr [edx + 0x83f4e0], al
    app->getMemory<x86::reg8>(cpu.edx + x86::reg32(8647904) /* 0x83f4e0 */) = cpu.al;
L_0x004d0e5e:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004d0e5e  8a4709                 -mov al, byte ptr [edi + 9]
    cpu.al = app->getMemory<x86::reg8>(cpu.edi + x86::reg32(9) /* 0x9 */);
    // 004d0e61  8882c0ff8300           -mov byte ptr [edx + 0x83ffc0], al
    app->getMemory<x86::reg8>(cpu.edx + x86::reg32(8650688) /* 0x83ffc0 */) = cpu.al;
    // 004d0e67  8a470a                 -mov al, byte ptr [edi + 0xa]
    cpu.al = app->getMemory<x86::reg8>(cpu.edi + x86::reg32(10) /* 0xa */);
    // 004d0e6a  888280fa8300           -mov byte ptr [edx + 0x83fa80], al
    app->getMemory<x86::reg8>(cpu.edx + x86::reg32(8649344) /* 0x83fa80 */) = cpu.al;
L_0x004d0e70:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004d0e70  42                     -inc edx
    (cpu.edx)++;
    // 004d0e71  81fae0000000           +cmp edx, 0xe0
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(224 /*0xe0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004d0e77  0f8d8d000000           -jge 0x4d0f0a
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004d0f0a;
    }
L_0x004d0e7d:
    // 004d0e7d  8d7220                 -lea esi, [edx + 0x20]
    cpu.esi = x86::reg32(cpu.edx + x86::reg32(32) /* 0x20 */);
    // 004d0e80  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004d0e82  e8e9eb0100             -call 0x4efa70
    cpu.esp -= 4;
    sub_4efa70(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d0e87  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 004d0e89  89c7                   -mov edi, eax
    cpu.edi = cpu.eax;
    // 004d0e8b  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004d0e8d  74e1                   -je 0x4d0e70
    if (cpu.flags.zf)
    {
        goto L_0x004d0e70;
    }
    // 004d0e8f  8a4002                 -mov al, byte ptr [eax + 2]
    cpu.al = app->getMemory<x86::reg8>(cpu.eax + x86::reg32(2) /* 0x2 */);
    // 004d0e92  888240fc8300           -mov byte ptr [edx + 0x83fc40], al
    app->getMemory<x86::reg8>(cpu.edx + x86::reg32(8649792) /* 0x83fc40 */) = cpu.al;
    // 004d0e98  8a4303                 -mov al, byte ptr [ebx + 3]
    cpu.al = app->getMemory<x86::reg8>(cpu.ebx + x86::reg32(3) /* 0x3 */);
    // 004d0e9b  b902000000             -mov ecx, 2
    cpu.ecx = 2 /*0x2*/;
    // 004d0ea0  888200fe8300           -mov byte ptr [edx + 0x83fe00], al
    app->getMemory<x86::reg8>(cpu.edx + x86::reg32(8650240) /* 0x83fe00 */) = cpu.al;
    // 004d0ea6  8d4304                 -lea eax, [ebx + 4]
    cpu.eax = x86::reg32(cpu.ebx + x86::reg32(4) /* 0x4 */);
    // 004d0ea9  8b4401fc               -mov eax, dword ptr [ecx + eax - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(-4) /* -0x4 */ + cpu.eax * 1);
    // 004d0ead  f7d9                   -neg ecx
    cpu.ecx = ~cpu.ecx + 1;
    // 004d0eaf  8d0ccd20000000         -lea ecx, [ecx*8 + 0x20]
    cpu.ecx = x86::reg32(x86::reg32(32) /* 0x20 */ + cpu.ecx * 8);
    // 004d0eb6  d3e8                   -shr eax, cl
    cpu.eax >>= cpu.cl % 32;
    // 004d0eb8  b902000000             -mov ecx, 2
    cpu.ecx = 2 /*0x2*/;
    // 004d0ebd  8882c0f88300           -mov byte ptr [edx + 0x83f8c0], al
    app->getMemory<x86::reg8>(cpu.edx + x86::reg32(8648896) /* 0x83f8c0 */) = cpu.al;
    // 004d0ec3  8d4306                 -lea eax, [ebx + 6]
    cpu.eax = x86::reg32(cpu.ebx + x86::reg32(6) /* 0x6 */);
    // 004d0ec6  8b4401fc               -mov eax, dword ptr [ecx + eax - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(-4) /* -0x4 */ + cpu.eax * 1);
    // 004d0eca  f7d9                   -neg ecx
    cpu.ecx = ~cpu.ecx + 1;
    // 004d0ecc  8d0ccd20000000         -lea ecx, [ecx*8 + 0x20]
    cpu.ecx = x86::reg32(x86::reg32(32) /* 0x20 */ + cpu.ecx * 8);
    // 004d0ed3  d3e8                   -shr eax, cl
    cpu.eax >>= cpu.cl % 32;
    // 004d0ed5  888200f78300           -mov byte ptr [edx + 0x83f700], al
    app->getMemory<x86::reg8>(cpu.edx + x86::reg32(8648448) /* 0x83f700 */) = cpu.al;
    // 004d0edb  833d8801840000         +cmp dword ptr [0x840188], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(8651144) /* 0x840188 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004d0ee2  0f846bffffff           -je 0x4d0e53
    if (cpu.flags.zf)
    {
        goto L_0x004d0e53;
    }
    // 004d0ee8  83fe50                 +cmp esi, 0x50
    {
        x86::reg32 tmp1 = cpu.esi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(80 /*0x50*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004d0eeb  0f8450ffffff           -je 0x4d0e41
    if (cpu.flags.zf)
    {
        goto L_0x004d0e41;
    }
    // 004d0ef1  83fe4d                 +cmp esi, 0x4d
    {
        x86::reg32 tmp1 = cpu.esi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(77 /*0x4d*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004d0ef4  0f853dffffff           -jne 0x4d0e37
    if (!cpu.flags.zf)
    {
        goto L_0x004d0e37;
    }
    // 004d0efa  8a4708                 -mov al, byte ptr [edi + 8]
    cpu.al = app->getMemory<x86::reg8>(cpu.edi + x86::reg32(8) /* 0x8 */);
    // 004d0efd  fec8                   +dec al
    {
        x86::reg8& tmp = cpu.al;
        cpu.flags.of = 1 & (tmp >> 7);
        tmp--;
        cpu.flags.of &= ~(1 & (tmp >> 7));
        cpu.set_szp(tmp);
    }
    // 004d0eff  8882e0f48300           -mov byte ptr [edx + 0x83f4e0], al
    app->getMemory<x86::reg8>(cpu.edx + x86::reg32(8647904) /* 0x83f4e0 */) = cpu.al;
    // 004d0f05  e954ffffff             -jmp 0x4d0e5e
    goto L_0x004d0e5e;
L_0x004d0f0a:
    // 004d0f0a  e801fbffff             -call 0x4d0a10
    cpu.esp -= 4;
    nfs3hp::render::pictureTexture(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d0f0f  8b857e010000           -mov eax, dword ptr [ebp + 0x17e]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(382) /* 0x17e */);
    // 004d0f15  e876090100             -call 0x4e1890
    cpu.esp -= 4;
    nfs3hp::ea::purgememadr(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d0f1a  807d7e00               +cmp byte ptr [ebp + 0x7e], 0
    {
        x86::reg8 tmp1 = app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(126) /* 0x7e */);
        x86::reg8 tmp2 = x86::reg8(x86::sreg8(0 /*0x0*/));
        x86::reg8 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 7);
        cpu.flags.of ^= 1 & (result >> 7);
        cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
        cpu.set_szp(result);
    }
    // 004d0f1e  0f84c8000000           -je 0x4d0fec
    if (cpu.flags.zf)
    {
        goto L_0x004d0fec;
    }
    // 004d0f24  ba01000000             -mov edx, 1
    cpu.edx = 1 /*0x1*/;
    // 004d0f29  8d457e                 -lea eax, [ebp + 0x7e]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(126) /* 0x7e */);
    // 004d0f2c  891584018400           -mov dword ptr [0x840184], edx
    app->getMemory<x86::reg32>(x86::reg32(8651140) /* 0x840184 */) = cpu.edx;
    // 004d0f32  ba10000000             -mov edx, 0x10
    cpu.edx = 16 /*0x10*/;
    // 004d0f37  e884ff0000             -call 0x4e0ec0
    cpu.esp -= 4;
    nfs3hp::ea::loadFile(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d0f3c  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 004d0f3e  e8dde50100             -call 0x4ef520
    cpu.esp -= 4;
    sub_4ef520(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d0f43  a118725600             -mov eax, dword ptr [0x567218]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5665304) /* 0x567218 */);
    // 004d0f48  31d2                   +xor edx, edx
    cpu.clear_co();
    cpu.set_szp((cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx))));
    // 004d0f4a  a3a4f68300             -mov dword ptr [0x83f6a4], eax
    app->getMemory<x86::reg32>(x86::reg32(8648356) /* 0x83f6a4 */) = cpu.eax;
    // 004d0f4f  eb0c                   -jmp 0x4d0f5d
    goto L_0x004d0f5d;
L_0x004d0f51:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004d0f51  81fae0000000           +cmp edx, 0xe0
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(224 /*0xe0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004d0f57  0f8d7b000000           -jge 0x4d0fd8
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004d0fd8;
    }
L_0x004d0f5d:
    // 004d0f5d  8d4220                 -lea eax, [edx + 0x20]
    cpu.eax = x86::reg32(cpu.edx + x86::reg32(32) /* 0x20 */);
    // 004d0f60  e80beb0100             -call 0x4efa70
    cpu.esp -= 4;
    sub_4efa70(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d0f65  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 004d0f67  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004d0f69  7467                   -je 0x4d0fd2
    if (cpu.flags.zf)
    {
        goto L_0x004d0fd2;
    }
    // 004d0f6b  8a4002                 -mov al, byte ptr [eax + 2]
    cpu.al = app->getMemory<x86::reg8>(cpu.eax + x86::reg32(2) /* 0x2 */);
    // 004d0f6e  888220fd8300           -mov byte ptr [edx + 0x83fd20], al
    app->getMemory<x86::reg8>(cpu.edx + x86::reg32(8650016) /* 0x83fd20 */) = cpu.al;
    // 004d0f74  8a4303                 -mov al, byte ptr [ebx + 3]
    cpu.al = app->getMemory<x86::reg8>(cpu.ebx + x86::reg32(3) /* 0x3 */);
    // 004d0f77  b902000000             -mov ecx, 2
    cpu.ecx = 2 /*0x2*/;
    // 004d0f7c  8882e0fe8300           -mov byte ptr [edx + 0x83fee0], al
    app->getMemory<x86::reg8>(cpu.edx + x86::reg32(8650464) /* 0x83fee0 */) = cpu.al;
    // 004d0f82  8d4304                 -lea eax, [ebx + 4]
    cpu.eax = x86::reg32(cpu.ebx + x86::reg32(4) /* 0x4 */);
    // 004d0f85  8b4401fc               -mov eax, dword ptr [ecx + eax - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(-4) /* -0x4 */ + cpu.eax * 1);
    // 004d0f89  f7d9                   -neg ecx
    cpu.ecx = ~cpu.ecx + 1;
    // 004d0f8b  8d0ccd20000000         -lea ecx, [ecx*8 + 0x20]
    cpu.ecx = x86::reg32(x86::reg32(32) /* 0x20 */ + cpu.ecx * 8);
    // 004d0f92  d3e8                   -shr eax, cl
    cpu.eax >>= cpu.cl % 32;
    // 004d0f94  b902000000             -mov ecx, 2
    cpu.ecx = 2 /*0x2*/;
    // 004d0f99  8882a0f98300           -mov byte ptr [edx + 0x83f9a0], al
    app->getMemory<x86::reg8>(cpu.edx + x86::reg32(8649120) /* 0x83f9a0 */) = cpu.al;
    // 004d0f9f  8d4306                 -lea eax, [ebx + 6]
    cpu.eax = x86::reg32(cpu.ebx + x86::reg32(6) /* 0x6 */);
    // 004d0fa2  8b4401fc               -mov eax, dword ptr [ecx + eax - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(-4) /* -0x4 */ + cpu.eax * 1);
    // 004d0fa6  f7d9                   -neg ecx
    cpu.ecx = ~cpu.ecx + 1;
    // 004d0fa8  8d0ccd20000000         -lea ecx, [ecx*8 + 0x20]
    cpu.ecx = x86::reg32(x86::reg32(32) /* 0x20 */ + cpu.ecx * 8);
    // 004d0faf  d3e8                   +shr eax, cl
    {
        x86::reg8 tmp = cpu.cl % 32;
        x86::reg32& op = cpu.eax;
        if (tmp)
        {
            cpu.flags.cf = 1 & (op >> (tmp - 1));
            if (tmp == 1) cpu.flags.of = (1 & (op >> (32 - 1)));
            cpu.set_szp((op >>= tmp));
        }
    }
    // 004d0fb1  8882e0f78300           -mov byte ptr [edx + 0x83f7e0], al
    app->getMemory<x86::reg8>(cpu.edx + x86::reg32(8648672) /* 0x83f7e0 */) = cpu.al;
    // 004d0fb7  8a4308                 -mov al, byte ptr [ebx + 8]
    cpu.al = app->getMemory<x86::reg8>(cpu.ebx + x86::reg32(8) /* 0x8 */);
    // 004d0fba  8882c0f58300           -mov byte ptr [edx + 0x83f5c0], al
    app->getMemory<x86::reg8>(cpu.edx + x86::reg32(8648128) /* 0x83f5c0 */) = cpu.al;
    // 004d0fc0  8a4309                 -mov al, byte ptr [ebx + 9]
    cpu.al = app->getMemory<x86::reg8>(cpu.ebx + x86::reg32(9) /* 0x9 */);
    // 004d0fc3  8882a0008400           -mov byte ptr [edx + 0x8400a0], al
    app->getMemory<x86::reg8>(cpu.edx + x86::reg32(8650912) /* 0x8400a0 */) = cpu.al;
    // 004d0fc9  8a430a                 -mov al, byte ptr [ebx + 0xa]
    cpu.al = app->getMemory<x86::reg8>(cpu.ebx + x86::reg32(10) /* 0xa */);
    // 004d0fcc  888260fb8300           -mov byte ptr [edx + 0x83fb60], al
    app->getMemory<x86::reg8>(cpu.edx + x86::reg32(8649568) /* 0x83fb60 */) = cpu.al;
L_0x004d0fd2:
    // 004d0fd2  42                     +inc edx
    {
        x86::reg32& tmp = cpu.edx;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 004d0fd3  e979ffffff             -jmp 0x4d0f51
    goto L_0x004d0f51;
L_0x004d0fd8:
    // 004d0fd8  e833faffff             -call 0x4d0a10
    cpu.esp -= 4;
    nfs3hp::render::pictureTexture(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d0fdd  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004d0fdf  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 004d0fe1  e8aa080100             -call 0x4e1890
    cpu.esp -= 4;
    nfs3hp::ea::purgememadr(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d0fe6  890d84018400           -mov dword ptr [0x840184], ecx
    app->getMemory<x86::reg32>(x86::reg32(8651140) /* 0x840184 */) = cpu.ecx;
L_0x004d0fec:
    // 004d0fec  8da582010000           -lea esp, [ebp + 0x182]
    cpu.esp = x86::reg32(cpu.ebp + x86::reg32(386) /* 0x182 */);
    // 004d0ff2  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d0ff3  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d0ff4  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d0ff5  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d0ff6  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d0ff7  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d0ff8  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_4d1000: native, nfs3hp::port::text::drawText */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8b 0xd2 */
void Application::sub_4d10e0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004d10e0  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004d10e1  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004d10e2  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004d10e4  83ec08                 -sub esp, 8
    (cpu.esp) -= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 004d10e7  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 004d10e9  8955f8                 -mov dword ptr [ebp - 8], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.edx;
    // 004d10ec  8955fc                 -mov dword ptr [ebp - 4], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.edx;
    // 004d10ef  e88c030000             -call 0x4d1480
    cpu.esp -= 4;
    nfs3hp::port::text::textWidthWithOverhang(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d10f4  db45fc                 -fild dword ptr [ebp - 4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 004d10f7  d9c9                   -fxch st(1)
    
    // 004d10f9  d8e9                   -fsubr st(1)
    x86::Float fpu2 = cpu.fpu.st(0);
    x86::Float fpu3 = cpu.fpu.sub(x86::Float(fpu1), fpu2);
    // 004d10fb  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004d10fd  ddd9                   -fstp st(1)
    x86::Float fpu4 = x86::Float(fpu3);
    cpu.fpu.st(0) = fpu4;
    }
    // 004d10ff  e852ec0000             -call 0x4dfd56
    cpu.esp -= 4;
    nfs3hp::watcom::CHP(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d1104  db5df8                 -fistp dword ptr [ebp - 8]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu5 = cpu.fpu.st(0);
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = x86::reg32(cpu.fpu.toInteger<x86::sreg32>(fpu5));
    // 004d1107  8b55f8                 -mov edx, dword ptr [ebp - 8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    cpu.fpu.count -= 1;
    }
    // 004d110a  e8f1feffff             -call 0x4d1000
    cpu.esp -= 4;
    nfs3hp::port::text::drawText(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d110f  ddd8                   -fstp st(0)
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu6 = cpu.fpu.st(0);
    x86::Float fpu7 = x86::Float(fpu6);
    // 004d1111  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004d1113  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d1114  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    cpu.fpu.count -= 1;
    }
    // 004d1115  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_4d1120: native, nfs3hp::graphics::drawTextBox */

/* sub_4d11f0: native, nfs3hp::port::fields::drawCursorText3d */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8b 0xd2 */
void Application::sub_4d1310(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004d1310  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004d1311  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004d1312  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004d1314  b8c0747f00             -mov eax, 0x7f74c0
    cpu.eax = 8352960 /*0x7f74c0*/;
    // 004d1319  8b15acf68300           -mov edx, dword ptr [0x83f6ac]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8648364) /* 0x83f6ac */);
    // 004d131f  e85ca9fcff             -call 0x49bc80
    cpu.esp -= 4;
    sub_49bc80(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d1324  b8d0b48100             -mov eax, 0x81b4d0
    cpu.eax = 8500432 /*0x81b4d0*/;
    // 004d1329  8b15d8f68300           -mov edx, dword ptr [0x83f6d8]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8648408) /* 0x83f6d8 */);
    // 004d132f  e84ca9fcff             -call 0x49bc80
    cpu.esp -= 4;
    sub_49bc80(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d1334  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d1335  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d1336  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_4d1340: native, nfs3hp::port::text::flushFonts */

/* sub_4d1390: native, nfs3hp::port::text::setTextScale */

/* sub_4d1400: native, nfs3hp::port::text::keepTextScale */

/* sub_4d1410: native, nfs3hp::port::text::restoreTextScale */

/* sub_4d1430: native, nfs3hp::port::text::measureText */

/* sub_4d1480: native, nfs3hp::port::text::textWidthWithOverhang */

/* align: skip 0x8b 0xc0 */
void Application::sub_4d14f0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004d14f0  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004d14f1  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004d14f2  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004d14f3  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004d14f5  83ec08                 -sub esp, 8
    (cpu.esp) -= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 004d14f8  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 004d14fa  88c1                   -mov cl, al
    cpu.cl = cpu.al;
    // 004d14fc  a184018400             -mov eax, dword ptr [0x840184]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(8651140) /* 0x840184 */);
    // 004d1501  c1e005                 -shl eax, 5
    cpu.eax <<= 5 /*0x5*/ % 32;
    // 004d1504  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004d1506  c1e003                 -shl eax, 3
    cpu.eax <<= 3 /*0x3*/ % 32;
    // 004d1509  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 004d150b  660fbe840160fa8300     -movsx ax, byte ptr [ecx + eax + 0x83fa60]
    cpu.ax = x86::reg16(static_cast<x86::sreg8>(app->getMemory<x86::reg8>(cpu.ecx + x86::reg32(8649312) /* 0x83fa60 */ + cpu.eax * 1)));
    // 004d1514  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 004d1517  df45fc                 -fild word ptr [ebp - 4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(x86::sreg16(app->getMemory<x86::reg16>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 004d151a  d80d8c018400           -fmul dword ptr [0x84018c]
    x86::Float fpu2 = cpu.fpu.mul(fpu1, x86::Float(app->getMemory<float>(x86::reg32(8651148) /* 0x84018c */)));
    cpu.fpu.count += 1;
    cpu.fpu.st(0) = fpu2;
    }
    // 004d1520  e831e80000             -call 0x4dfd56
    cpu.esp -= 4;
    nfs3hp::watcom::CHP(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d1525  db5df8                 -fistp dword ptr [ebp - 8]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu3 = cpu.fpu.st(0);
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = x86::reg32(cpu.fpu.toInteger<x86::sreg32>(fpu3));
    // 004d1528  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004d152b  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004d152d  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d152e  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d152f  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    cpu.fpu.count -= 1;
    }
    // 004d1530  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_4d1540: native, nfs3hp::port::text::characterWidth */

/* sub_4d1590: native, nfs3hp::port::text::characterOverhang */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x8d 0x40 0x00 */
void Application::sub_4d15e0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004d15e0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004d15e1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004d15e2  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004d15e3  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004d15e4  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004d15e5  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004d15e6  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004d15e8  83ec10                 -sub esp, 0x10
    (cpu.esp) -= x86::reg32(x86::sreg32(16 /*0x10*/));
    // 004d15eb  ba01000000             -mov edx, 1
    cpu.edx = 1 /*0x1*/;
    // 004d15f0  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 004d15f2  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 004d15f4  31f6                   -xor esi, esi
    cpu.esi ^= x86::reg32(x86::sreg32(cpu.esi));
    // 004d15f6  66a1d4f68300           -mov ax, word ptr [0x83f6d4]
    cpu.ax = app->getMemory<x86::reg16>(x86::reg32(8648404) /* 0x83f6d4 */);
    // 004d15fc  891584018400           -mov dword ptr [0x840184], edx
    app->getMemory<x86::reg32>(x86::reg32(8651140) /* 0x840184 */) = cpu.edx;
    // 004d1602  894df4                 -mov dword ptr [ebp - 0xc], ecx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.ecx;
    // 004d1605  8945f8                 -mov dword ptr [ebp - 8], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.eax;
    // 004d1608  b920000000             -mov ecx, 0x20
    cpu.ecx = 32 /*0x20*/;
    // 004d160d  db45f8                 -fild dword ptr [ebp - 8]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    // 004d1610  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 004d1612  d91d041c5600           -fstp dword ptr [0x561c04]
    app->getMemory<float>(x86::reg32(5643268) /* 0x561c04 */) = float(fpu1);
    // 004d1618  66a1d6f68300           -mov ax, word ptr [0x83f6d6]
    cpu.ax = app->getMemory<x86::reg16>(x86::reg32(8648406) /* 0x83f6d6 */);
    // 004d161e  d905041c5600           -fld dword ptr [0x561c04]
    x86::Float fpu2 = x86::Float(app->getMemory<float>(x86::reg32(5643268) /* 0x561c04 */));
    // 004d1624  8945f8                 -mov dword ptr [ebp - 8], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.eax;
    // 004d1627  d91de41b5600           -fstp dword ptr [0x561be4]
    app->getMemory<float>(x86::reg32(5643236) /* 0x561be4 */) = float(fpu2);
    // 004d162d  db45f8                 -fild dword ptr [ebp - 8]
    x86::Float fpu3 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    // 004d1630  d91d281c5600           -fstp dword ptr [0x561c28]
    app->getMemory<float>(x86::reg32(5643304) /* 0x561c28 */) = float(fpu3);
    // 004d1636  30e4                   +xor ah, ah
    cpu.clear_co();
    cpu.set_szp((cpu.ah ^= x86::reg8(x86::sreg8(cpu.ah))));
    // 004d1638  8b15281c5600           -mov edx, dword ptr [0x561c28]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5643304) /* 0x561c28 */);
    // 004d163e  8915081c5600           -mov dword ptr [0x561c08], edx
    app->getMemory<x86::reg32>(x86::reg32(5643272) /* 0x561c08 */) = cpu.edx;
    // 004d1644  8865fd                 -mov byte ptr [ebp - 3], ah
    app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-3) /* -0x3 */) = cpu.ah;
    }
    // 004d1647  eb08                   -jmp 0x4d1651
    goto L_0x004d1651;
L_0x004d1649:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004d1649  81f980000000           +cmp ecx, 0x80
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(128 /*0x80*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004d164f  7d46                   -jge 0x4d1697
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004d1697;
    }
L_0x004d1651:
    // 004d1651  8b55f4                 -mov edx, dword ptr [ebp - 0xc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 004d1654  8d45fc                 -lea eax, [ebp - 4]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004d1657  89f3                   -mov ebx, esi
    cpu.ebx = cpu.esi;
    // 004d1659  884dfc                 -mov byte ptr [ebp - 4], cl
    app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.cl;
    // 004d165c  e89ff9ffff             -call 0x4d1000
    cpu.esp -= 4;
    nfs3hp::port::text::drawText(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d1661  8b45f4                 -mov eax, dword ptr [ebp - 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 004d1664  8945f8                 -mov dword ptr [ebp - 8], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.eax;
    // 004d1667  db45f8                 -fild dword ptr [ebp - 8]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu4 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    // 004d166a  a1c8da7c00             -mov eax, dword ptr [0x7cdac8]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(8182472) /* 0x7cdac8 */);
    // 004d166f  d9c9                   -fxch st(1)
    
    // 004d1671  d8c1                   -fadd st(1)
    x86::Float fpu5 = cpu.fpu.st(0);
    x86::Float fpu6 = cpu.fpu.add(fpu5, x86::Float(fpu4));
    // 004d1673  83e814                 -sub eax, 0x14
    (cpu.eax) -= x86::reg32(x86::sreg32(20 /*0x14*/));
    // 004d1676  ddd9                   -fstp st(1)
    x86::Float fpu7 = x86::Float(fpu6);
    cpu.fpu.st(0) = fpu7;
    }
    // 004d1678  e8d9e60000             -call 0x4dfd56
    cpu.esp -= 4;
    nfs3hp::watcom::CHP(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d167d  db5df4                 -fistp dword ptr [ebp - 0xc]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu8 = cpu.fpu.st(0);
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = x86::reg32(cpu.fpu.toInteger<x86::sreg32>(fpu8));
    // 004d1680  3b45f4                 +cmp eax, dword ptr [ebp - 0xc]
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    cpu.fpu.count -= 1;
    }
    // 004d1683  7d0f                   -jge 0x4d1694
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004d1694;
    }
    // 004d1685  a1a4f68300             -mov eax, dword ptr [0x83f6a4]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(8648356) /* 0x83f6a4 */);
    // 004d168a  31ff                   -xor edi, edi
    cpu.edi ^= x86::reg32(x86::sreg32(cpu.edi));
    // 004d168c  83c006                 -add eax, 6
    (cpu.eax) += x86::reg32(x86::sreg32(6 /*0x6*/));
    // 004d168f  897df4                 -mov dword ptr [ebp - 0xc], edi
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.edi;
    // 004d1692  01c6                   +add esi, eax
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
L_0x004d1694:
    // 004d1694  41                     +inc ecx
    {
        x86::reg32& tmp = cpu.ecx;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 004d1695  ebb2                   -jmp 0x4d1649
    goto L_0x004d1649;
L_0x004d1697:
    // 004d1697  b9e0000000             -mov ecx, 0xe0
    cpu.ecx = 224 /*0xe0*/;
    // 004d169c  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
    // 004d169e  be05000000             -mov esi, 5
    cpu.esi = 5 /*0x5*/;
    // 004d16a3  8945f0                 -mov dword ptr [ebp - 0x10], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = cpu.eax;
    // 004d16a6  e97e000000             -jmp 0x4d1729
    goto L_0x004d1729;
L_0x004d16ab:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004d16ab  8b1d3c1b5600           -mov ebx, dword ptr [0x561b3c]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(5643068) /* 0x561b3c */);
    // 004d16b1  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 004d16b3  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004d16b4  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 004d16b6  8a9100fe8300           -mov dl, byte ptr [ecx + 0x83fe00]
    cpu.dl = app->getMemory<x86::reg8>(cpu.ecx + x86::reg32(8650240) /* 0x83fe00 */);
    // 004d16bc  6850ffffff             -push 0xffffff50
    app->getMemory<x86::reg32>(cpu.esp-4) = 4294967120 /*0xffffff50*/;
    cpu.esp -= 4;
    // 004d16c1  42                     -inc edx
    (cpu.edx)++;
    // 004d16c2  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
    // 004d16c4  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004d16c5  8a8140fc8300           -mov al, byte ptr [ecx + 0x83fc40]
    cpu.al = app->getMemory<x86::reg8>(cpu.ecx + x86::reg32(8649792) /* 0x83fc40 */);
    // 004d16cb  8a9900f78300           -mov bl, byte ptr [ecx + 0x83f700]
    cpu.bl = app->getMemory<x86::reg8>(cpu.ecx + x86::reg32(8648448) /* 0x83f700 */);
    // 004d16d1  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004d16d2  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 004d16d4  8b45f0                 -mov eax, dword ptr [ebp - 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 004d16d7  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004d16d8  8945f8                 -mov dword ptr [ebp - 8], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.eax;
    // 004d16db  8a91c0f88300           -mov dl, byte ptr [ecx + 0x83f8c0]
    cpu.dl = app->getMemory<x86::reg8>(cpu.ecx + x86::reg32(8648896) /* 0x83f8c0 */);
    // 004d16e1  db45f8                 -fild dword ptr [ebp - 8]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu9 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    // 004d16e4  d95df8                 -fstp dword ptr [ebp - 8]
    app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = float(fpu9);
    // 004d16e7  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004d16e9  ff75f8                 -push dword ptr [ebp - 8]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    cpu.esp -= 4;
    }
    // 004d16ec  e8ffefffff             -call 0x4d06f0
    cpu.esp -= 4;
    nfs3hp::port::text::drawCharacter(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d16f1  d845f8                 -fadd dword ptr [ebp - 8]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu10 = cpu.fpu.st(0);
    x86::Float fpu11 = cpu.fpu.add(fpu10, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    cpu.fpu.st(0) = fpu11;
    }
    // 004d16f4  e85de60000             -call 0x4dfd56
    cpu.esp -= 4;
    nfs3hp::watcom::CHP(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d16f9  db5df0                 -fistp dword ptr [ebp - 0x10]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu12 = cpu.fpu.st(0);
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = x86::reg32(cpu.fpu.toInteger<x86::sreg32>(fpu12));
    // 004d16fc  8b7df0                 -mov edi, dword ptr [ebp - 0x10]
    cpu.edi = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 004d16ff  a1c8da7c00             -mov eax, dword ptr [0x7cdac8]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(8182472) /* 0x7cdac8 */);
    // 004d1704  83c705                 -add edi, 5
    (cpu.edi) += x86::reg32(x86::sreg32(5 /*0x5*/));
    // 004d1707  83e814                 -sub eax, 0x14
    (cpu.eax) -= x86::reg32(x86::sreg32(20 /*0x14*/));
    // 004d170a  897df0                 -mov dword ptr [ebp - 0x10], edi
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = cpu.edi;
    // 004d170d  39f8                   +cmp eax, edi
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
    cpu.fpu.count -= 1;
    }
    // 004d170f  7d0f                   -jge 0x4d1720
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004d1720;
    }
    // 004d1711  a1a4f68300             -mov eax, dword ptr [0x83f6a4]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(8648356) /* 0x83f6a4 */);
    // 004d1716  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
    // 004d1718  83c006                 -add eax, 6
    (cpu.eax) += x86::reg32(x86::sreg32(6 /*0x6*/));
    // 004d171b  895df0                 -mov dword ptr [ebp - 0x10], ebx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = cpu.ebx;
    // 004d171e  01c6                   -add esi, eax
    (cpu.esi) += x86::reg32(x86::sreg32(cpu.eax));
L_0x004d1720:
    // 004d1720  41                     -inc ecx
    (cpu.ecx)++;
    // 004d1721  81f940010000           +cmp ecx, 0x140
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(320 /*0x140*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004d1727  7d15                   -jge 0x4d173e
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004d173e;
    }
L_0x004d1729:
    // 004d1729  8b15a4f68300           -mov edx, dword ptr [0x83f6a4]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8648356) /* 0x83f6a4 */);
    // 004d172f  a1ccda7c00             -mov eax, dword ptr [0x7cdacc]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(8182476) /* 0x7cdacc */);
    // 004d1734  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 004d1736  39c6                   +cmp esi, eax
    {
        x86::reg32 tmp1 = cpu.esi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.eax));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004d1738  0f8c6dffffff           -jl 0x4d16ab
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004d16ab;
    }
L_0x004d173e:
    // 004d173e  e8fdfbffff             -call 0x4d1340
    cpu.esp -= 4;
    nfs3hp::port::text::flushFonts(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d1743  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004d1745  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d1746  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d1747  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d1748  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d1749  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d174a  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d174b  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_4d1750: native, nfs3hp::port::text::loadLanguageText */

/* sub_4d17b0: native, nfs3hp::port::text::specialText */

/* sub_4d1850: native, nfs3hp::port::text::languageText */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 0x8b 0xdb */
void Application::sub_4d1880(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004d1880  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004d1881  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004d1882  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004d1883  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004d1885  8b15803a5600           -mov edx, dword ptr [0x563a80]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5651072) /* 0x563a80 */);
    // 004d188b  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 004d188d  7407                   -je 0x4d1896
    if (cpu.flags.zf)
    {
        goto L_0x004d1896;
    }
    // 004d188f  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004d1891  e8faff0000             -call 0x4e1890
    cpu.esp -= 4;
    nfs3hp::ea::purgememadr(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x004d1896:
    // 004d1896  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 004d1898  890d803a5600           -mov dword ptr [0x563a80], ecx
    app->getMemory<x86::reg32>(x86::reg32(5651072) /* 0x563a80 */) = cpu.ecx;
    // 004d189e  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d189f  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d18a0  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d18a1  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 */
void Application::sub_4d18b0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004d18b0  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004d18b1  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004d18b2  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004d18b4  ba10000000             -mov edx, 0x10
    cpu.edx = 16 /*0x10*/;
    // 004d18b9  83f802                 +cmp eax, 2
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
    // 004d18bc  721b                   -jb 0x4d18d9
    if (cpu.flags.cf)
    {
        goto L_0x004d18d9;
    }
    // 004d18be  760a                   -jbe 0x4d18ca
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x004d18ca;
    }
    // 004d18c0  83f806                 +cmp eax, 6
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(6 /*0x6*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004d18c3  740f                   -je 0x4d18d4
    if (cpu.flags.zf)
    {
        goto L_0x004d18d4;
    }
    // 004d18c5  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004d18c7  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d18c8  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d18c9  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004d18ca:
    // 004d18ca  ba08000000             -mov edx, 8
    cpu.edx = 8 /*0x8*/;
    // 004d18cf  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004d18d1  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d18d2  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d18d3  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004d18d4:
    // 004d18d4  ba20000000             -mov edx, 0x20
    cpu.edx = 32 /*0x20*/;
L_0x004d18d9:
    // 004d18d9  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004d18db  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d18dc  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d18dd  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_4d18e0: native, nfs3hp::port::shapes::scan4444 */

/* sub_4d1950: native, nfs3hp::port::shapes::scan8888 */

/* sub_4d19b0: native, nfs3hp::port::shapes::scanNibbles */

/* sub_4d1a00: native, nfs3hp::port::shapes::scanPaletted */

/* sub_4d1a90: native, nfs3hp::port::shapes::scan1555 */

/* sub_4d1ad0: native, nfs3hp::port::shapes::scan565 */

/* sub_4d1b20: native, nfs3hp::port::shapes::convert4444 */

/* sub_4d1c00: native, nfs3hp::port::shapes::convert8888 */

/* sub_4d1ce0: native, nfs3hp::port::shapes::convert8 */

/* sub_4d1db0: native, nfs3hp::port::shapes::convert565 */

/* sub_4d1e60: native, nfs3hp::port::shapes::convert1555 */

/* sub_4d1f70: native, nfs3hp::port::shapes::nibblesTo1555 */

/* sub_4d2050: native, nfs3hp::port::shapes::nibblesTo565 */

/* sub_4d2150: native, nfs3hp::port::shapes::nibblesTo4444 */

/* sub_4d21f0: native, nfs3hp::port::shapes::nibblesTo8888 */

/* sub_4d22b0: native, nfs3hp::port::shapes::paletteTo1555 */

/* sub_4d23f0: native, nfs3hp::port::shapes::paletteTo565 */

/* sub_4d2510: native, nfs3hp::port::shapes::paletteTo4444 */

/* sub_4d2690: native, nfs3hp::port::shapes::paletteTo8888 */

/* sub_4d27e0: native, nfs3hp::port::shapes::argb8888To4444 */

/* sub_4d2940: native, nfs3hp::port::shapes::argb8888To565 */

/* sub_4d2a80: native, nfs3hp::port::shapes::argb8888To1555 */

/* sub_4d2be0: native, nfs3hp::port::shapes::rgb565To1555 */

/* sub_4d2d20: native, nfs3hp::port::shapes::rgb565To4444 */

/* sub_4d2e60: native, nfs3hp::port::shapes::rgb565To8888 */

/* sub_4d2fb0: native, nfs3hp::port::shapes::argb1555To565 */

/* sub_4d30f0: native, nfs3hp::port::shapes::argb1555To4444 */

/* sub_4d3230: native, nfs3hp::port::shapes::argb1555To8888 */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x8b 0xc0 */
void Application::sub_4d3380(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004d3380  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004d3381  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004d3382  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004d3383  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004d3384  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004d3386  83ec10                 -sub esp, 0x10
    (cpu.esp) -= x86::reg32(x86::sreg32(16 /*0x10*/));
    // 004d3389  895dfc                 -mov dword ptr [ebp - 4], ebx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.ebx;
    // 004d338c  8b7002                 -mov esi, dword ptr [eax + 2]
    cpu.esi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(2) /* 0x2 */);
    // 004d338f  8b4804                 -mov ecx, dword ptr [eax + 4]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 004d3392  c1fe10                 -sar esi, 0x10
    cpu.esi = x86::reg32(x86::sreg32(cpu.esi) >> (16 /*0x10*/ % 32));
    // 004d3395  c1f910                 -sar ecx, 0x10
    cpu.ecx = x86::reg32(x86::sreg32(cpu.ecx) >> (16 /*0x10*/ % 32));
    // 004d3398  0faff1                 -imul esi, ecx
    cpu.esi = x86::reg32(x86::sreg64(x86::sreg32(cpu.esi)) * x86::sreg64(x86::sreg32(cpu.ecx)));
    // 004d339b  8d5810                 -lea ebx, [eax + 0x10]
    cpu.ebx = x86::reg32(cpu.eax + x86::reg32(16) /* 0x10 */);
    // 004d339e  8975f8                 -mov dword ptr [ebp - 8], esi
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.esi;
    // 004d33a1  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
L_0x004d33a3:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004d33a3  3b4df8                 +cmp ecx, dword ptr [ebp - 8]
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004d33a6  7d55                   -jge 0x4d33fd
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004d33fd;
    }
    // 004d33a8  0fb633                 -movzx esi, byte ptr [ebx]
    cpu.esi = x86::reg32(app->getMemory<x86::reg8>(cpu.ebx));
    // 004d33ab  8b7dfc                 -mov edi, dword ptr [ebp - 4]
    cpu.edi = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004d33ae  c1e602                 -shl esi, 2
    cpu.esi <<= 2 /*0x2*/ % 32;
    // 004d33b1  01fe                   -add esi, edi
    (cpu.esi) += x86::reg32(x86::sreg32(cpu.edi));
    // 004d33b3  8b36                   -mov esi, dword ptr [esi]
    cpu.esi = app->getMemory<x86::reg32>(cpu.esi);
    // 004d33b5  803bff                 +cmp byte ptr [ebx], 0xff
    {
        x86::reg8 tmp1 = app->getMemory<x86::reg8>(cpu.ebx);
        x86::reg8 tmp2 = x86::reg8(x86::sreg8(255 /*0xff*/));
        x86::reg8 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 7);
        cpu.flags.of ^= 1 & (result >> 7);
        cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
        cpu.set_szp(result);
    }
    // 004d33b8  7437                   -je 0x4d33f1
    if (cpu.flags.zf)
    {
        goto L_0x004d33f1;
    }
    // 004d33ba  89f7                   -mov edi, esi
    cpu.edi = cpu.esi;
    // 004d33bc  81e70000f000           -and edi, 0xf00000
    cpu.edi &= x86::reg32(x86::sreg32(15728640 /*0xf00000*/));
    // 004d33c2  c1ff0c                 -sar edi, 0xc
    cpu.edi = x86::reg32(x86::sreg32(cpu.edi) >> (12 /*0xc*/ % 32));
    // 004d33c5  6681cf0080             -or di, 0x8000
    cpu.di |= x86::reg16(x86::sreg16(32768 /*0x8000*/));
    // 004d33ca  897df0                 -mov dword ptr [ebp - 0x10], edi
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = cpu.edi;
    // 004d33cd  89f7                   -mov edi, esi
    cpu.edi = cpu.esi;
    // 004d33cf  81e700f00000           -and edi, 0xf000
    cpu.edi &= x86::reg32(x86::sreg32(61440 /*0xf000*/));
    // 004d33d5  c1ff08                 -sar edi, 8
    cpu.edi = x86::reg32(x86::sreg32(cpu.edi) >> (8 /*0x8*/ % 32));
    // 004d33d8  81e6f0000000           -and esi, 0xf0
    cpu.esi &= x86::reg32(x86::sreg32(240 /*0xf0*/));
    // 004d33de  897df4                 -mov dword ptr [ebp - 0xc], edi
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.edi;
    // 004d33e1  8b7df0                 -mov edi, dword ptr [ebp - 0x10]
    cpu.edi = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 004d33e4  c1fe04                 -sar esi, 4
    cpu.esi = x86::reg32(x86::sreg32(cpu.esi) >> (4 /*0x4*/ % 32));
    // 004d33e7  0b7df4                 -or edi, dword ptr [ebp - 0xc]
    cpu.edi |= x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */)));
    // 004d33ea  09fe                   +or esi, edi
    cpu.clear_co();
    cpu.set_szp((cpu.esi |= x86::reg32(x86::sreg32(cpu.edi))));
    // 004d33ec  668932                 -mov word ptr [edx], si
    app->getMemory<x86::reg16>(cpu.edx) = cpu.si;
    // 004d33ef  eb05                   -jmp 0x4d33f6
    goto L_0x004d33f6;
L_0x004d33f1:
    // 004d33f1  66c7020000             -mov word ptr [edx], 0
    app->getMemory<x86::reg16>(cpu.edx) = 0 /*0x0*/;
L_0x004d33f6:
    // 004d33f6  83c202                 +add edx, 2
    {
        x86::reg32& tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(2 /*0x2*/));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 004d33f9  41                     +inc ecx
    {
        x86::reg32& tmp = cpu.ecx;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 004d33fa  43                     +inc ebx
    {
        x86::reg32& tmp = cpu.ebx;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 004d33fb  eba6                   -jmp 0x4d33a3
    goto L_0x004d33a3;
L_0x004d33fd:
    // 004d33fd  c60000                 -mov byte ptr [eax], 0
    app->getMemory<x86::reg8>(cpu.eax) = 0 /*0x0*/;
    // 004d3400  80086d                 -or byte ptr [eax], 0x6d
    app->getMemory<x86::reg8>(cpu.eax) |= x86::reg8(x86::sreg8(109 /*0x6d*/));
    // 004d3403  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004d3405  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d3406  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d3407  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d3408  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d3409  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 */
void Application::sub_4d3410(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004d3410  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004d3411  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004d3412  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004d3413  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004d3414  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004d3415  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004d3416  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004d3418  83ec0c                 -sub esp, 0xc
    (cpu.esp) -= x86::reg32(x86::sreg32(12 /*0xc*/));
    // 004d341b  8b5004                 -mov edx, dword ptr [eax + 4]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 004d341e  8b4802                 -mov ecx, dword ptr [eax + 2]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(2) /* 0x2 */);
    // 004d3421  c1fa10                 -sar edx, 0x10
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (16 /*0x10*/ % 32));
    // 004d3424  c1f910                 -sar ecx, 0x10
    cpu.ecx = x86::reg32(x86::sreg32(cpu.ecx) >> (16 /*0x10*/ % 32));
    // 004d3427  0fafca                 -imul ecx, edx
    cpu.ecx = x86::reg32(x86::sreg64(x86::sreg32(cpu.ecx)) * x86::sreg64(x86::sreg32(cpu.edx)));
    // 004d342a  8d5010                 -lea edx, [eax + 0x10]
    cpu.edx = x86::reg32(cpu.eax + x86::reg32(16) /* 0x10 */);
    // 004d342d  8955f8                 -mov dword ptr [ebp - 8], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.edx;
    // 004d3430  8b10                   -mov edx, dword ptr [eax]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax);
    // 004d3432  81e2ff000000           -and edx, 0xff
    cpu.edx &= x86::reg32(x86::sreg32(255 /*0xff*/));
    // 004d3438  894dfc                 -mov dword ptr [ebp - 4], ecx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.ecx;
    // 004d343b  83fa7e                 +cmp edx, 0x7e
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(126 /*0x7e*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004d343e  755c                   -jne 0x4d349c
    if (!cpu.flags.zf)
    {
        goto L_0x004d349c;
    }
    // 004d3440  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
L_0x004d3442:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004d3442  3b55fc                 +cmp edx, dword ptr [ebp - 4]
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004d3445  7d4f                   -jge 0x4d3496
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004d3496;
    }
    // 004d3447  8b75f8                 -mov esi, dword ptr [ebp - 8]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004d344a  8d1c12                 -lea ebx, [edx + edx]
    cpu.ebx = x86::reg32(cpu.edx + cpu.edx * 1);
    // 004d344d  01f3                   -add ebx, esi
    (cpu.ebx) += x86::reg32(x86::sreg32(cpu.esi));
    // 004d344f  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 004d3451  668b0b                 -mov cx, word ptr [ebx]
    cpu.cx = app->getMemory<x86::reg16>(cpu.ebx);
    // 004d3454  f6c580                 +test ch, 0x80
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.ch & 128 /*0x80*/));
    // 004d3457  7435                   -je 0x4d348e
    if (cpu.flags.zf)
    {
        goto L_0x004d348e;
    }
    // 004d3459  8db100040000           -lea esi, [ecx + 0x400]
    cpu.esi = x86::reg32(cpu.ecx + x86::reg32(1024) /* 0x400 */);
    // 004d345f  c1fe03                 -sar esi, 3
    cpu.esi = x86::reg32(x86::sreg32(cpu.esi) >> (3 /*0x3*/ % 32));
    // 004d3462  81e6000f0000           -and esi, 0xf00
    cpu.esi &= x86::reg32(x86::sreg32(3840 /*0xf00*/));
    // 004d3468  6681ce0080             -or si, 0x8000
    cpu.si |= x86::reg16(x86::sreg16(32768 /*0x8000*/));
    // 004d346d  8975f4                 -mov dword ptr [ebp - 0xc], esi
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.esi;
    // 004d3470  8d7120                 -lea esi, [ecx + 0x20]
    cpu.esi = x86::reg32(cpu.ecx + x86::reg32(32) /* 0x20 */);
    // 004d3473  8b7df4                 -mov edi, dword ptr [ebp - 0xc]
    cpu.edi = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 004d3476  41                     -inc ecx
    (cpu.ecx)++;
    // 004d3477  c1fe02                 -sar esi, 2
    cpu.esi = x86::reg32(x86::sreg32(cpu.esi) >> (2 /*0x2*/ % 32));
    // 004d347a  d1f9                   -sar ecx, 1
    cpu.ecx = x86::reg32(x86::sreg32(cpu.ecx) >> (1 /*0x1*/ % 32));
    // 004d347c  81e6f0000000           -and esi, 0xf0
    cpu.esi &= x86::reg32(x86::sreg32(240 /*0xf0*/));
    // 004d3482  83e10f                 -and ecx, 0xf
    cpu.ecx &= x86::reg32(x86::sreg32(15 /*0xf*/));
    // 004d3485  09fe                   -or esi, edi
    cpu.esi |= x86::reg32(x86::sreg32(cpu.edi));
    // 004d3487  09f1                   +or ecx, esi
    cpu.clear_co();
    cpu.set_szp((cpu.ecx |= x86::reg32(x86::sreg32(cpu.esi))));
    // 004d3489  66890b                 -mov word ptr [ebx], cx
    app->getMemory<x86::reg16>(cpu.ebx) = cpu.cx;
    // 004d348c  eb05                   -jmp 0x4d3493
    goto L_0x004d3493;
L_0x004d348e:
    // 004d348e  66c7030000             -mov word ptr [ebx], 0
    app->getMemory<x86::reg16>(cpu.ebx) = 0 /*0x0*/;
L_0x004d3493:
    // 004d3493  42                     +inc edx
    {
        x86::reg32& tmp = cpu.edx;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 004d3494  ebac                   -jmp 0x4d3442
    goto L_0x004d3442;
L_0x004d3496:
    // 004d3496  c60000                 -mov byte ptr [eax], 0
    app->getMemory<x86::reg8>(cpu.eax) = 0 /*0x0*/;
    // 004d3499  80086d                 -or byte ptr [eax], 0x6d
    app->getMemory<x86::reg8>(cpu.eax) |= x86::reg8(x86::sreg8(109 /*0x6d*/));
L_0x004d349c:
    // 004d349c  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004d349e  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d349f  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d34a0  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d34a1  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d34a2  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d34a3  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d34a4  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 0x8b 0xdb */
void Application::sub_4d34b0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004d34b0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004d34b1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004d34b2  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004d34b3  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004d34b4  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004d34b5  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004d34b7  83ec20                 -sub esp, 0x20
    (cpu.esp) -= x86::reg32(x86::sreg32(32 /*0x20*/));
    // 004d34ba  8945f0                 -mov dword ptr [ebp - 0x10], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = cpu.eax;
    // 004d34bd  8955e0                 -mov dword ptr [ebp - 0x20], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-32) /* -0x20 */) = cpu.edx;
    // 004d34c0  8b4002                 -mov eax, dword ptr [eax + 2]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(2) /* 0x2 */);
    // 004d34c3  c1f810                 -sar eax, 0x10
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (16 /*0x10*/ % 32));
    // 004d34c6  8945f8                 -mov dword ptr [ebp - 8], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.eax;
    // 004d34c9  8b45f0                 -mov eax, dword ptr [ebp - 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 004d34cc  8b4004                 -mov eax, dword ptr [eax + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 004d34cf  c1f810                 -sar eax, 0x10
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (16 /*0x10*/ % 32));
    // 004d34d2  8945e4                 -mov dword ptr [ebp - 0x1c], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-28) /* -0x1c */) = cpu.eax;
    // 004d34d5  8b45f0                 -mov eax, dword ptr [ebp - 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 004d34d8  83c010                 -add eax, 0x10
    (cpu.eax) += x86::reg32(x86::sreg32(16 /*0x10*/));
    // 004d34db  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 004d34de  8b45f0                 -mov eax, dword ptr [ebp - 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 004d34e1  8b00                   -mov eax, dword ptr [eax]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax);
    // 004d34e3  25ff000000             -and eax, 0xff
    cpu.eax &= x86::reg32(x86::sreg32(255 /*0xff*/));
    // 004d34e8  8955e8                 -mov dword ptr [ebp - 0x18], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-24) /* -0x18 */) = cpu.edx;
    // 004d34eb  83f87e                 +cmp eax, 0x7e
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(126 /*0x7e*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004d34ee  0f85c5010000           -jne 0x4d36b9
    if (!cpu.flags.zf)
    {
        goto L_0x004d36b9;
    }
    // 004d34f4  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 004d34f6  8955ec                 -mov dword ptr [ebp - 0x14], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */) = cpu.edx;
L_0x004d34f9:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004d34f9  8b45ec                 -mov eax, dword ptr [ebp - 0x14]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */);
    // 004d34fc  8b4de4                 -mov ecx, dword ptr [ebp - 0x1c]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-28) /* -0x1c */);
    // 004d34ff  39c8                   +cmp eax, ecx
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
    // 004d3501  0f8d90010000           -jge 0x4d3697
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004d3697;
    }
    // 004d3507  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
    // 004d3509  895df4                 -mov dword ptr [ebp - 0xc], ebx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.ebx;
L_0x004d350c:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004d350c  8b45f4                 -mov eax, dword ptr [ebp - 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 004d350f  3b45f8                 +cmp eax, dword ptr [ebp - 8]
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004d3512  0f8d77010000           -jge 0x4d368f
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004d368f;
    }
    // 004d3518  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004d351b  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 004d351d  668b08                 -mov cx, word ptr [eax]
    cpu.cx = app->getMemory<x86::reg16>(cpu.eax);
    // 004d3520  f6c580                 +test ch, 0x80
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.ch & 128 /*0x80*/));
    // 004d3523  0f8445010000           -je 0x4d366e
    if (cpu.flags.zf)
    {
        goto L_0x004d366e;
    }
    // 004d3529  bf20000000             -mov edi, 0x20
    cpu.edi = 32 /*0x20*/;
    // 004d352e  8b45ec                 -mov eax, dword ptr [ebp - 0x14]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */);
    // 004d3531  89cb                   -mov ebx, ecx
    cpu.ebx = cpu.ecx;
    // 004d3533  89ce                   -mov esi, ecx
    cpu.esi = cpu.ecx;
    // 004d3535  89ca                   -mov edx, ecx
    cpu.edx = cpu.ecx;
    // 004d3537  83e31f                 -and ebx, 0x1f
    cpu.ebx &= x86::reg32(x86::sreg32(31 /*0x1f*/));
    // 004d353a  81e6e0030000           -and esi, 0x3e0
    cpu.esi &= x86::reg32(x86::sreg32(992 /*0x3e0*/));
    // 004d3540  81e2007c0000           -and edx, 0x7c00
    cpu.edx &= x86::reg32(x86::sreg32(31744 /*0x7c00*/));
    // 004d3546  c1e305                 -shl ebx, 5
    cpu.ebx <<= 5 /*0x5*/ % 32;
    // 004d3549  c1fa05                 -sar edx, 5
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (5 /*0x5*/ % 32));
    // 004d354c  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004d354e  7e3d                   -jle 0x4d358d
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004d358d;
    }
    // 004d3550  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004d3553  8b4dfc                 -mov ecx, dword ptr [ebp - 4]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004d3556  01c0                   -add eax, eax
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.eax));
    // 004d3558  29c1                   -sub ecx, eax
    (cpu.ecx) -= x86::reg32(x86::sreg32(cpu.eax));
    // 004d355a  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004d355c  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 004d355e  668b08                 -mov cx, word ptr [eax]
    cpu.cx = app->getMemory<x86::reg16>(cpu.eax);
    // 004d3561  f6c580                 +test ch, 0x80
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.ch & 128 /*0x80*/));
    // 004d3564  7427                   -je 0x4d358d
    if (cpu.flags.zf)
    {
        goto L_0x004d358d;
    }
    // 004d3566  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004d3568  83e01f                 -and eax, 0x1f
    cpu.eax &= x86::reg32(x86::sreg32(31 /*0x1f*/));
    // 004d356b  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 004d356e  01c3                   -add ebx, eax
    (cpu.ebx) += x86::reg32(x86::sreg32(cpu.eax));
    // 004d3570  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004d3572  25e0030000             -and eax, 0x3e0
    cpu.eax &= x86::reg32(x86::sreg32(992 /*0x3e0*/));
    // 004d3577  c1f803                 -sar eax, 3
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (3 /*0x3*/ % 32));
    // 004d357a  01c6                   -add esi, eax
    (cpu.esi) += x86::reg32(x86::sreg32(cpu.eax));
    // 004d357c  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004d357e  25007c0000             -and eax, 0x7c00
    cpu.eax &= x86::reg32(x86::sreg32(31744 /*0x7c00*/));
    // 004d3583  c1f808                 -sar eax, 8
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (8 /*0x8*/ % 32));
    // 004d3586  bf24000000             -mov edi, 0x24
    cpu.edi = 36 /*0x24*/;
    // 004d358b  01c2                   -add edx, eax
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.eax));
L_0x004d358d:
    // 004d358d  8b45e4                 -mov eax, dword ptr [ebp - 0x1c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-28) /* -0x1c */);
    // 004d3590  8b4dec                 -mov ecx, dword ptr [ebp - 0x14]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */);
    // 004d3593  48                     -dec eax
    (cpu.eax)--;
    // 004d3594  39c8                   +cmp eax, ecx
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
    // 004d3596  7e39                   -jle 0x4d35d1
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004d35d1;
    }
    // 004d3598  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004d359b  8b4dfc                 -mov ecx, dword ptr [ebp - 4]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004d359e  01c0                   -add eax, eax
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.eax));
    // 004d35a0  01c8                   -add eax, ecx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.ecx));
    // 004d35a2  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 004d35a4  668b08                 -mov cx, word ptr [eax]
    cpu.cx = app->getMemory<x86::reg16>(cpu.eax);
    // 004d35a7  f6c580                 +test ch, 0x80
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.ch & 128 /*0x80*/));
    // 004d35aa  7425                   -je 0x4d35d1
    if (cpu.flags.zf)
    {
        goto L_0x004d35d1;
    }
    // 004d35ac  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004d35ae  83e01f                 -and eax, 0x1f
    cpu.eax &= x86::reg32(x86::sreg32(31 /*0x1f*/));
    // 004d35b1  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 004d35b4  01c3                   -add ebx, eax
    (cpu.ebx) += x86::reg32(x86::sreg32(cpu.eax));
    // 004d35b6  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004d35b8  25e0030000             -and eax, 0x3e0
    cpu.eax &= x86::reg32(x86::sreg32(992 /*0x3e0*/));
    // 004d35bd  c1f803                 -sar eax, 3
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (3 /*0x3*/ % 32));
    // 004d35c0  01c6                   -add esi, eax
    (cpu.esi) += x86::reg32(x86::sreg32(cpu.eax));
    // 004d35c2  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004d35c4  25007c0000             -and eax, 0x7c00
    cpu.eax &= x86::reg32(x86::sreg32(31744 /*0x7c00*/));
    // 004d35c9  c1f808                 -sar eax, 8
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (8 /*0x8*/ % 32));
    // 004d35cc  83c704                 -add edi, 4
    (cpu.edi) += x86::reg32(x86::sreg32(4 /*0x4*/));
    // 004d35cf  01c2                   -add edx, eax
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.eax));
L_0x004d35d1:
    // 004d35d1  837df400               +cmp dword ptr [ebp - 0xc], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004d35d5  7e32                   -jle 0x4d3609
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004d3609;
    }
    // 004d35d7  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004d35da  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 004d35dc  668b48fe               -mov cx, word ptr [eax - 2]
    cpu.cx = app->getMemory<x86::reg16>(cpu.eax + x86::reg32(-2) /* -0x2 */);
    // 004d35e0  f6c580                 +test ch, 0x80
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.ch & 128 /*0x80*/));
    // 004d35e3  7424                   -je 0x4d3609
    if (cpu.flags.zf)
    {
        goto L_0x004d3609;
    }
    // 004d35e5  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004d35e7  83e01f                 -and eax, 0x1f
    cpu.eax &= x86::reg32(x86::sreg32(31 /*0x1f*/));
    // 004d35ea  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 004d35ed  01c3                   -add ebx, eax
    (cpu.ebx) += x86::reg32(x86::sreg32(cpu.eax));
    // 004d35ef  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004d35f1  83c704                 -add edi, 4
    (cpu.edi) += x86::reg32(x86::sreg32(4 /*0x4*/));
    // 004d35f4  25e0030000             -and eax, 0x3e0
    cpu.eax &= x86::reg32(x86::sreg32(992 /*0x3e0*/));
    // 004d35f9  81e1007c0000           -and ecx, 0x7c00
    cpu.ecx &= x86::reg32(x86::sreg32(31744 /*0x7c00*/));
    // 004d35ff  c1f908                 -sar ecx, 8
    cpu.ecx = x86::reg32(x86::sreg32(cpu.ecx) >> (8 /*0x8*/ % 32));
    // 004d3602  c1f803                 -sar eax, 3
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (3 /*0x3*/ % 32));
    // 004d3605  01ca                   -add edx, ecx
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.ecx));
    // 004d3607  01c6                   -add esi, eax
    (cpu.esi) += x86::reg32(x86::sreg32(cpu.eax));
L_0x004d3609:
    // 004d3609  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004d360c  8b4df4                 -mov ecx, dword ptr [ebp - 0xc]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 004d360f  48                     -dec eax
    (cpu.eax)--;
    // 004d3610  39c8                   +cmp eax, ecx
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
    // 004d3612  7e32                   -jle 0x4d3646
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004d3646;
    }
    // 004d3614  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004d3617  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 004d3619  668b4802               -mov cx, word ptr [eax + 2]
    cpu.cx = app->getMemory<x86::reg16>(cpu.eax + x86::reg32(2) /* 0x2 */);
    // 004d361d  f6c580                 +test ch, 0x80
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.ch & 128 /*0x80*/));
    // 004d3620  7424                   -je 0x4d3646
    if (cpu.flags.zf)
    {
        goto L_0x004d3646;
    }
    // 004d3622  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004d3624  83e01f                 -and eax, 0x1f
    cpu.eax &= x86::reg32(x86::sreg32(31 /*0x1f*/));
    // 004d3627  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 004d362a  01c3                   -add ebx, eax
    (cpu.ebx) += x86::reg32(x86::sreg32(cpu.eax));
    // 004d362c  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004d362e  83c704                 -add edi, 4
    (cpu.edi) += x86::reg32(x86::sreg32(4 /*0x4*/));
    // 004d3631  25e0030000             -and eax, 0x3e0
    cpu.eax &= x86::reg32(x86::sreg32(992 /*0x3e0*/));
    // 004d3636  81e1007c0000           -and ecx, 0x7c00
    cpu.ecx &= x86::reg32(x86::sreg32(31744 /*0x7c00*/));
    // 004d363c  c1f908                 -sar ecx, 8
    cpu.ecx = x86::reg32(x86::sreg32(cpu.ecx) >> (8 /*0x8*/ % 32));
    // 004d363f  c1f803                 -sar eax, 3
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (3 /*0x3*/ % 32));
    // 004d3642  01ca                   -add edx, ecx
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.ecx));
    // 004d3644  01c6                   -add esi, eax
    (cpu.esi) += x86::reg32(x86::sreg32(cpu.eax));
L_0x004d3646:
    // 004d3646  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004d3648  c1fa1f                 -sar edx, 0x1f
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (31 /*0x1f*/ % 32));
    // 004d364b  f7ff                   -idiv edi
    {
        x86::sreg64 tmp = x86::sreg64(cpu.edx_eax);
        x86::sreg32 d = x86::sreg32(cpu.edi);
        cpu.edx_eax = x86::reg64(tmp / d);
        cpu.edx = x86::reg32(tmp % d);
    }
    // 004d364d  c1e00a                 -shl eax, 0xa
    cpu.eax <<= 10 /*0xa*/ % 32;
    // 004d3650  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 004d3652  80cc80                 -or ah, 0x80
    cpu.ah |= x86::reg8(x86::sreg8(128 /*0x80*/));
    // 004d3655  c1fa1f                 -sar edx, 0x1f
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (31 /*0x1f*/ % 32));
    // 004d3658  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 004d365a  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004d365c  f7ff                   -idiv edi
    {
        x86::sreg64 tmp = x86::sreg64(cpu.edx_eax);
        x86::sreg32 d = x86::sreg32(cpu.edi);
        cpu.edx_eax = x86::reg64(tmp / d);
        cpu.edx = x86::reg32(tmp % d);
    }
    // 004d365e  89da                   -mov edx, ebx
    cpu.edx = cpu.ebx;
    // 004d3660  c1e005                 -shl eax, 5
    cpu.eax <<= 5 /*0x5*/ % 32;
    // 004d3663  c1fa1f                 -sar edx, 0x1f
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (31 /*0x1f*/ % 32));
    // 004d3666  09c1                   -or ecx, eax
    cpu.ecx |= x86::reg32(x86::sreg32(cpu.eax));
    // 004d3668  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 004d366a  f7ff                   -idiv edi
    {
        x86::sreg64 tmp = x86::sreg64(cpu.edx_eax);
        x86::sreg32 d = x86::sreg32(cpu.edi);
        cpu.edx_eax = x86::reg64(tmp / d);
        cpu.edx = x86::reg32(tmp % d);
    }
    // 004d366c  09c1                   -or ecx, eax
    cpu.ecx |= x86::reg32(x86::sreg32(cpu.eax));
L_0x004d366e:
    // 004d366e  8b55f4                 -mov edx, dword ptr [ebp - 0xc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 004d3671  8b45e8                 -mov eax, dword ptr [ebp - 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-24) /* -0x18 */);
    // 004d3674  42                     -inc edx
    (cpu.edx)++;
    // 004d3675  8d5802                 -lea ebx, [eax + 2]
    cpu.ebx = x86::reg32(cpu.eax + x86::reg32(2) /* 0x2 */);
    // 004d3678  668908                 -mov word ptr [eax], cx
    app->getMemory<x86::reg16>(cpu.eax) = cpu.cx;
    // 004d367b  8b4dfc                 -mov ecx, dword ptr [ebp - 4]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004d367e  8955f4                 -mov dword ptr [ebp - 0xc], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.edx;
    // 004d3681  83c102                 +add ecx, 2
    {
        x86::reg32& tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(2 /*0x2*/));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 004d3684  895de8                 -mov dword ptr [ebp - 0x18], ebx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-24) /* -0x18 */) = cpu.ebx;
    // 004d3687  894dfc                 -mov dword ptr [ebp - 4], ecx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.ecx;
    // 004d368a  e97dfeffff             -jmp 0x4d350c
    goto L_0x004d350c;
L_0x004d368f:
    // 004d368f  ff45ec                 +inc dword ptr [ebp - 0x14]
    {
        auto tmp = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */);
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 004d3692  e962feffff             -jmp 0x4d34f9
    goto L_0x004d34f9;
L_0x004d3697:
    // 004d3697  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004d369a  0fafc1                 -imul eax, ecx
    cpu.eax = x86::reg32(x86::sreg64(x86::sreg32(cpu.eax)) * x86::sreg64(x86::sreg32(cpu.ecx)));
    // 004d369d  8b7df0                 -mov edi, dword ptr [ebp - 0x10]
    cpu.edi = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 004d36a0  8b75e0                 -mov esi, dword ptr [ebp - 0x20]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-32) /* -0x20 */);
    // 004d36a3  83c710                 -add edi, 0x10
    (cpu.edi) += x86::reg32(x86::sreg32(16 /*0x10*/));
    // 004d36a6  8d0c00                 -lea ecx, [eax + eax]
    cpu.ecx = x86::reg32(cpu.eax + cpu.eax * 1);
    // 004d36a9  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004d36aa  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004d36ac  c1e902                 -shr ecx, 2
    cpu.ecx >>= 2 /*0x2*/ % 32;
    // 004d36af  f2a5                   -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004d36b1  8ac8                   -mov cl, al
    cpu.cl = cpu.al;
    // 004d36b3  80e103                 +and cl, 3
    cpu.clear_co();
    cpu.set_szp((cpu.cl &= x86::reg8(x86::sreg8(3 /*0x3*/))));
    // 004d36b6  f2a4                   -repne movsb byte ptr es:[edi], byte ptr [esi]
    while (cpu.ecx)
    {
        app->getMemory<x86::reg8>(cpu.ees + cpu.edi) = app->getMemory<x86::reg8>(cpu.esi);
        if (cpu.flags.df)
        {
            cpu.edi -= 1;
            cpu.esi -= 1;
        }
        else
        {
            cpu.edi += 1;
            cpu.esi += 1;
        }
        --cpu.ecx;
        if (cpu.flags.zf)
            break;
    }
    // 004d36b8  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
L_0x004d36b9:
    // 004d36b9  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004d36bb  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d36bc  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d36bd  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d36be  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d36bf  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d36c0  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_4d37a0: native, nfs3hp::port::shapes::shapeToPixels */

/* sub_4d3f50: native, nfs3hp::render::squareTexture */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 0x8b 0xdb */
void Application::sub_4d4080(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004d4080  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004d4081  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004d4082  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004d4083  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004d4085  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 004d4088  89ce                   -mov esi, ecx
    cpu.esi = cpu.ecx;
    // 004d408a  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004d408c  7409                   -je 0x4d4097
    if (cpu.flags.zf)
    {
        goto L_0x004d4097;
    }
    // 004d408e  e84db10100             -call 0x4ef1e0
    cpu.esp -= 4;
    sub_4ef1e0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d4093  89c7                   -mov edi, eax
    cpu.edi = cpu.eax;
    // 004d4095  eb02                   -jmp 0x4d4099
    goto L_0x004d4099;
L_0x004d4097:
    // 004d4097  89d7                   -mov edi, edx
    cpu.edi = cpu.edx;
L_0x004d4099:
    // 004d4099  8b5510                 -mov edx, dword ptr [ebp + 0x10]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(16) /* 0x10 */);
    // 004d409c  89d9                   -mov ecx, ebx
    cpu.ecx = cpu.ebx;
    // 004d409e  668b4704               -mov ax, word ptr [edi + 4]
    cpu.ax = app->getMemory<x86::reg16>(cpu.edi + x86::reg32(4) /* 0x4 */);
    // 004d40a2  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004d40a3  668906                 -mov word ptr [esi], ax
    app->getMemory<x86::reg16>(cpu.esi) = cpu.ax;
    // 004d40a6  89f3                   -mov ebx, esi
    cpu.ebx = cpu.esi;
    // 004d40a8  668b4706               -mov ax, word ptr [edi + 6]
    cpu.ax = app->getMemory<x86::reg16>(cpu.edi + x86::reg32(6) /* 0x6 */);
    // 004d40ac  8d55fc                 -lea edx, [ebp - 4]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004d40af  66894602               -mov word ptr [esi + 2], ax
    app->getMemory<x86::reg16>(cpu.esi + x86::reg32(2) /* 0x2 */) = cpu.ax;
    // 004d40b3  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 004d40b5  c6462800               -mov byte ptr [esi + 0x28], 0
    app->getMemory<x86::reg8>(cpu.esi + x86::reg32(40) /* 0x28 */) = 0 /*0x0*/;
    // 004d40b9  e892feffff             -call 0x4d3f50
    cpu.esp -= 4;
    nfs3hp::render::squareTexture(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d40be  894604                 -mov dword ptr [esi + 4], eax
    app->getMemory<x86::reg32>(cpu.esi + x86::reg32(4) /* 0x4 */) = cpu.eax;
    // 004d40c1  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 004d40c3  e818e40100             -call 0x4f24e0
    cpu.esp -= 4;
    sub_4f24e0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d40c8  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004d40ca  741f                   -je 0x4d40eb
    if (cpu.flags.zf)
    {
        goto L_0x004d40eb;
    }
    // 004d40cc  ba3c945400             -mov edx, 0x54943c
    cpu.edx = 5542972 /*0x54943c*/;
    // 004d40d1  e84ac70000             -call 0x4e0820
    cpu.esp -= 4;
    nfs3hp::watcom::strstr(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d40d6  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004d40d8  7411                   -je 0x4d40eb
    if (cpu.flags.zf)
    {
        goto L_0x004d40eb;
    }
    // 004d40da  8a6628                 -mov ah, byte ptr [esi + 0x28]
    cpu.ah = app->getMemory<x86::reg8>(cpu.esi + x86::reg32(40) /* 0x28 */);
    // 004d40dd  80cc02                 -or ah, 2
    cpu.ah |= x86::reg8(x86::sreg8(2 /*0x2*/));
    // 004d40e0  b901000000             -mov ecx, 1
    cpu.ecx = 1 /*0x1*/;
    // 004d40e5  886628                 -mov byte ptr [esi + 0x28], ah
    app->getMemory<x86::reg8>(cpu.esi + x86::reg32(40) /* 0x28 */) = cpu.ah;
    // 004d40e8  894dfc                 -mov dword ptr [ebp - 4], ecx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.ecx;
L_0x004d40eb:
    // 004d40eb  837dfc00               +cmp dword ptr [ebp - 4], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004d40ef  740f                   -je 0x4d4100
    if (cpu.flags.zf)
    {
        goto L_0x004d4100;
    }
    // 004d40f1  8a5628                 -mov dl, byte ptr [esi + 0x28]
    cpu.dl = app->getMemory<x86::reg8>(cpu.esi + x86::reg32(40) /* 0x28 */);
    // 004d40f4  c64629ff               -mov byte ptr [esi + 0x29], 0xff
    app->getMemory<x86::reg8>(cpu.esi + x86::reg32(41) /* 0x29 */) = 255 /*0xff*/;
    // 004d40f8  80ca04                 +or dl, 4
    cpu.clear_co();
    cpu.set_szp((cpu.dl |= x86::reg8(x86::sreg8(4 /*0x4*/))));
    // 004d40fb  885628                 -mov byte ptr [esi + 0x28], dl
    app->getMemory<x86::reg8>(cpu.esi + x86::reg32(40) /* 0x28 */) = cpu.dl;
    // 004d40fe  eb0f                   -jmp 0x4d410f
    goto L_0x004d410f;
L_0x004d4100:
    // 004d4100  a08c3a5600             -mov al, byte ptr [0x563a8c]
    cpu.al = app->getMemory<x86::reg8>(x86::reg32(5651084) /* 0x563a8c */);
    // 004d4105  884629                 -mov byte ptr [esi + 0x29], al
    app->getMemory<x86::reg8>(cpu.esi + x86::reg32(41) /* 0x29 */) = cpu.al;
    // 004d4108  fec0                   -inc al
    (cpu.al)++;
    // 004d410a  a28c3a5600             -mov byte ptr [0x563a8c], al
    app->getMemory<x86::reg8>(x86::reg32(5651084) /* 0x563a8c */) = cpu.al;
L_0x004d410f:
    // 004d410f  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004d4111  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d4112  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d4113  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d4114  c20400                 -ret 4
    cpu.esp += 4+4 /*0x4*/;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 */
void Application::sub_4d4120(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004d4120  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004d4121  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004d4123  39d0                   +cmp eax, edx
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
    // 004d4125  7e02                   -jle 0x4d4129
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004d4129;
    }
    // 004d4127  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
L_0x004d4129:
    // 004d4129  3d00010000             +cmp eax, 0x100
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
    // 004d412e  7c07                   -jl 0x4d4137
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004d4137;
    }
    // 004d4130  b800010000             -mov eax, 0x100
    cpu.eax = 256 /*0x100*/;
    // 004d4135  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d4136  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004d4137:
    // 004d4137  3d80000000             +cmp eax, 0x80
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(128 /*0x80*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004d413c  7c07                   -jl 0x4d4145
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004d4145;
    }
    // 004d413e  b880000000             -mov eax, 0x80
    cpu.eax = 128 /*0x80*/;
    // 004d4143  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d4144  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004d4145:
    // 004d4145  83f840                 +cmp eax, 0x40
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(64 /*0x40*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004d4148  7c07                   -jl 0x4d4151
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004d4151;
    }
    // 004d414a  b840000000             -mov eax, 0x40
    cpu.eax = 64 /*0x40*/;
    // 004d414f  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d4150  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004d4151:
    // 004d4151  83f820                 +cmp eax, 0x20
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
    // 004d4154  7c07                   -jl 0x4d415d
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004d415d;
    }
    // 004d4156  b820000000             -mov eax, 0x20
    cpu.eax = 32 /*0x20*/;
    // 004d415b  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d415c  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004d415d:
    // 004d415d  83f810                 +cmp eax, 0x10
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(16 /*0x10*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004d4160  7c07                   -jl 0x4d4169
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004d4169;
    }
    // 004d4162  b810000000             -mov eax, 0x10
    cpu.eax = 16 /*0x10*/;
    // 004d4167  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d4168  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004d4169:
    // 004d4169  83f808                 +cmp eax, 8
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(8 /*0x8*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004d416c  7c07                   -jl 0x4d4175
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004d4175;
    }
    // 004d416e  b808000000             -mov eax, 8
    cpu.eax = 8 /*0x8*/;
    // 004d4173  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d4174  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004d4175:
    // 004d4175  83f804                 +cmp eax, 4
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
    // 004d4178  7c07                   -jl 0x4d4181
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004d4181;
    }
    // 004d417a  b804000000             -mov eax, 4
    cpu.eax = 4 /*0x4*/;
    // 004d417f  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d4180  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004d4181:
    // 004d4181  83f802                 +cmp eax, 2
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
    // 004d4184  7c07                   -jl 0x4d418d
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004d418d;
    }
    // 004d4186  b802000000             -mov eax, 2
    cpu.eax = 2 /*0x2*/;
    // 004d418b  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d418c  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004d418d:
    // 004d418d  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 004d4192  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d4193  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_4d41a0: native, nfs3hp::render::paletteTexture */

/* align: skip 0x8d 0x40 0x00 0x8b 0xc9 */
void Application::sub_4d43e0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004d43e0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004d43e1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004d43e2  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004d43e3  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004d43e4  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004d43e6  f6059c3a560001         +test byte ptr [0x563a9c], 1
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(x86::reg32(5651100) /* 0x563a9c */) & 1 /*0x1*/));
    // 004d43ed  7407                   -je 0x4d43f6
    if (cpu.flags.zf)
    {
        goto L_0x004d43f6;
    }
    // 004d43ef  b81f000000             -mov eax, 0x1f
    cpu.eax = 31 /*0x1f*/;
    // 004d43f4  eb02                   -jmp 0x4d43f8
    goto L_0x004d43f8;
L_0x004d43f6:
    // 004d43f6  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
L_0x004d43f8:
    // 004d43f8  8a1d9c3a5600           -mov bl, byte ptr [0x563a9c]
    cpu.bl = app->getMemory<x86::reg8>(x86::reg32(5651100) /* 0x563a9c */);
    // 004d43fe  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004d4400  f6c302                 +test bl, 2
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.bl & 2 /*0x2*/));
    // 004d4403  7407                   -je 0x4d440c
    if (cpu.flags.zf)
    {
        goto L_0x004d440c;
    }
    // 004d4405  b81f000000             -mov eax, 0x1f
    cpu.eax = 31 /*0x1f*/;
    // 004d440a  eb02                   -jmp 0x4d440e
    goto L_0x004d440e;
L_0x004d440c:
    // 004d440c  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
L_0x004d440e:
    // 004d440e  8a3d9c3a5600           -mov bh, byte ptr [0x563a9c]
    cpu.bh = app->getMemory<x86::reg8>(x86::reg32(5651100) /* 0x563a9c */);
    // 004d4414  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 004d4416  f6c704                 +test bh, 4
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.bh & 4 /*0x4*/));
    // 004d4419  7407                   -je 0x4d4422
    if (cpu.flags.zf)
    {
        goto L_0x004d4422;
    }
    // 004d441b  b81f000000             -mov eax, 0x1f
    cpu.eax = 31 /*0x1f*/;
    // 004d4420  eb02                   -jmp 0x4d4424
    goto L_0x004d4424;
L_0x004d4422:
    // 004d4422  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
L_0x004d4424:
    // 004d4424  c1e20a                 -shl edx, 0xa
    cpu.edx <<= 10 /*0xa*/ % 32;
    // 004d4427  c1e105                 -shl ecx, 5
    cpu.ecx <<= 5 /*0x5*/ % 32;
    // 004d442a  80ce80                 -or dh, 0x80
    cpu.dh |= x86::reg8(x86::sreg8(128 /*0x80*/));
    // 004d442d  09ca                   -or edx, ecx
    cpu.edx |= x86::reg32(x86::sreg32(cpu.ecx));
    // 004d442f  09d0                   -or eax, edx
    cpu.eax |= x86::reg32(x86::sreg32(cpu.edx));
    // 004d4431  ff059c3a5600           -inc dword ptr [0x563a9c]
    (app->getMemory<x86::reg32>(x86::reg32(5651100) /* 0x563a9c */))++;
    // 004d4437  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d4438  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d4439  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d443a  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d443b  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x44 0x20 0x00 */
void Application::sub_4d4440(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004d4440  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004d4441  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004d4442  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004d4443  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004d4445  83ec10                 -sub esp, 0x10
    (cpu.esp) -= x86::reg32(x86::sreg32(16 /*0x10*/));
    // 004d4448  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 004d444a  8955f8                 -mov dword ptr [ebp - 8], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.edx;
    // 004d444d  c1e003                 -shl eax, 3
    cpu.eax <<= 3 /*0x3*/ % 32;
    // 004d4450  01f0                   -add eax, esi
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.esi));
    // 004d4452  8b14859c207900         -mov edx, dword ptr [eax*4 + 0x79209c]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(7938204) /* 0x79209c */ + cpu.eax * 4);
    // 004d4459  0faf148594207900       -imul edx, dword ptr [eax*4 + 0x792094]
    cpu.edx = x86::reg32(x86::sreg64(x86::sreg32(cpu.edx)) * x86::sreg64(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(7938196) /* 0x792094 */ + cpu.eax * 4))));
    // 004d4461  03148598207900         -add edx, dword ptr [eax*4 + 0x792098]
    (cpu.edx) += x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(7938200) /* 0x792098 */ + cpu.eax * 4)));
    // 004d4468  8d0c12                 -lea ecx, [edx + edx]
    cpu.ecx = x86::reg32(cpu.edx + cpu.edx * 1);
    // 004d446b  01d9                   -add ecx, ebx
    (cpu.ecx) += x86::reg32(x86::sreg32(cpu.ebx));
    // 004d446d  8b5df8                 -mov ebx, dword ptr [ebp - 8]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004d4470  8b5b02                 -mov ebx, dword ptr [ebx + 2]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(2) /* 0x2 */);
    // 004d4473  c1fb10                 -sar ebx, 0x10
    cpu.ebx = x86::reg32(x86::sreg32(cpu.ebx) >> (16 /*0x10*/ % 32));
    // 004d4476  895df0                 -mov dword ptr [ebp - 0x10], ebx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = cpu.ebx;
    // 004d4479  8b7df0                 -mov edi, dword ptr [ebp - 0x10]
    cpu.edi = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 004d447c  8b1c85a4207900         -mov ebx, dword ptr [eax*4 + 0x7920a4]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(7938212) /* 0x7920a4 */ + cpu.eax * 4);
    // 004d4483  0fafdf                 -imul ebx, edi
    cpu.ebx = x86::reg32(x86::sreg64(x86::sreg32(cpu.ebx)) * x86::sreg64(x86::sreg32(cpu.edi)));
    // 004d4486  8b3c85a0207900         -mov edi, dword ptr [eax*4 + 0x7920a0]
    cpu.edi = app->getMemory<x86::reg32>(x86::reg32(7938208) /* 0x7920a0 */ + cpu.eax * 4);
    // 004d448d  8b55f8                 -mov edx, dword ptr [ebp - 8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004d4490  01fb                   -add ebx, edi
    (cpu.ebx) += x86::reg32(x86::sreg32(cpu.edi));
    // 004d4492  83c210                 -add edx, 0x10
    (cpu.edx) += x86::reg32(x86::sreg32(16 /*0x10*/));
    // 004d4495  01db                   -add ebx, ebx
    (cpu.ebx) += x86::reg32(x86::sreg32(cpu.ebx));
    // 004d4497  01da                   -add edx, ebx
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.ebx));
    // 004d4499  8b1c85b0207900         -mov ebx, dword ptr [eax*4 + 0x7920b0]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(7938224) /* 0x7920b0 */ + cpu.eax * 4);
    // 004d44a0  85db                   +test ebx, ebx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & cpu.ebx));
    // 004d44a2  746c                   -je 0x4d4510
    if (cpu.flags.zf)
    {
        goto L_0x004d4510;
    }
    // 004d44a4  31ff                   -xor edi, edi
    cpu.edi ^= x86::reg32(x86::sreg32(cpu.edi));
    // 004d44a6  897dfc                 -mov dword ptr [ebp - 4], edi
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.edi;
L_0x004d44a9:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004d44a9  8d04f500000000         -lea eax, [esi*8]
    cpu.eax = x86::reg32(cpu.esi * 8);
    // 004d44b0  01f0                   -add eax, esi
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.esi));
    // 004d44b2  8b5dfc                 -mov ebx, dword ptr [ebp - 4]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004d44b5  3b1c85ac207900         +cmp ebx, dword ptr [eax*4 + 0x7920ac]
    {
        x86::reg32 tmp1 = cpu.ebx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(7938220) /* 0x7920ac */ + cpu.eax * 4)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004d44bc  0f8db0000000           -jge 0x4d4572
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004d4572;
    }
    // 004d44c2  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
L_0x004d44c4:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004d44c4  8d04f500000000         -lea eax, [esi*8]
    cpu.eax = x86::reg32(cpu.esi * 8);
    // 004d44cb  01f0                   -add eax, esi
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.esi));
    // 004d44cd  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 004d44d0  3b98a8207900           +cmp ebx, dword ptr [eax + 0x7920a8]
    {
        x86::reg32 tmp1 = cpu.ebx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.eax + x86::reg32(7938216) /* 0x7920a8 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004d44d6  7d29                   -jge 0x4d4501
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004d4501;
    }
    // 004d44d8  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004d44db  8b4002                 -mov eax, dword ptr [eax + 2]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(2) /* 0x2 */);
    // 004d44de  c1f810                 -sar eax, 0x10
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (16 /*0x10*/ % 32));
    // 004d44e1  0fafc3                 -imul eax, ebx
    cpu.eax = x86::reg32(x86::sreg64(x86::sreg32(cpu.eax)) * x86::sreg64(x86::sreg32(cpu.ebx)));
    // 004d44e4  0345fc                 -add eax, dword ptr [ebp - 4]
    (cpu.eax) += x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 004d44e7  01c0                   +add eax, eax
    {
        x86::reg32& tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.eax));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 004d44e9  8d3c02                 -lea edi, [edx + eax]
    cpu.edi = x86::reg32(cpu.edx + cpu.eax * 1);
    // 004d44ec  8d041b                 -lea eax, [ebx + ebx]
    cpu.eax = x86::reg32(cpu.ebx + cpu.ebx * 1);
    // 004d44ef  897df0                 -mov dword ptr [ebp - 0x10], edi
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = cpu.edi;
    // 004d44f2  8d3c01                 -lea edi, [ecx + eax]
    cpu.edi = x86::reg32(cpu.ecx + cpu.eax * 1);
    // 004d44f5  8b45f0                 -mov eax, dword ptr [ebp - 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 004d44f8  43                     +inc ebx
    {
        x86::reg32& tmp = cpu.ebx;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 004d44f9  668b00                 -mov ax, word ptr [eax]
    cpu.ax = app->getMemory<x86::reg16>(cpu.eax);
    // 004d44fc  668907                 -mov word ptr [edi], ax
    app->getMemory<x86::reg16>(cpu.edi) = cpu.ax;
    // 004d44ff  ebc3                   -jmp 0x4d44c4
    goto L_0x004d44c4;
L_0x004d4501:
    // 004d4501  8b8094207900           -mov eax, dword ptr [eax + 0x792094]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(7938196) /* 0x792094 */);
    // 004d4507  01c0                   -add eax, eax
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.eax));
    // 004d4509  01c1                   +add ecx, eax
    {
        x86::reg32& tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.eax));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 004d450b  ff45fc                 +inc dword ptr [ebp - 4]
    {
        auto tmp = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 004d450e  eb99                   -jmp 0x4d44a9
    goto L_0x004d44a9;
L_0x004d4510:
    // 004d4510  895df4                 -mov dword ptr [ebp - 0xc], ebx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.ebx;
L_0x004d4513:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004d4513  8d04f500000000         -lea eax, [esi*8]
    cpu.eax = x86::reg32(cpu.esi * 8);
    // 004d451a  01f0                   -add eax, esi
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.esi));
    // 004d451c  8b5df4                 -mov ebx, dword ptr [ebp - 0xc]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 004d451f  3b1c85ac207900         +cmp ebx, dword ptr [eax*4 + 0x7920ac]
    {
        x86::reg32 tmp1 = cpu.ebx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(7938220) /* 0x7920ac */ + cpu.eax * 4)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004d4526  7d4a                   -jge 0x4d4572
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004d4572;
    }
    // 004d4528  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
L_0x004d452a:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004d452a  8d04f500000000         -lea eax, [esi*8]
    cpu.eax = x86::reg32(cpu.esi * 8);
    // 004d4531  01f0                   -add eax, esi
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.esi));
    // 004d4533  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 004d4536  3b98a8207900           +cmp ebx, dword ptr [eax + 0x7920a8]
    {
        x86::reg32 tmp1 = cpu.ebx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.eax + x86::reg32(7938216) /* 0x7920a8 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004d453c  7d18                   -jge 0x4d4556
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004d4556;
    }
    // 004d453e  8d041b                 -lea eax, [ebx + ebx]
    cpu.eax = x86::reg32(cpu.ebx + cpu.ebx * 1);
    // 004d4541  8d3c02                 -lea edi, [edx + eax]
    cpu.edi = x86::reg32(cpu.edx + cpu.eax * 1);
    // 004d4544  897df0                 -mov dword ptr [ebp - 0x10], edi
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = cpu.edi;
    // 004d4547  8d3c01                 -lea edi, [ecx + eax]
    cpu.edi = x86::reg32(cpu.ecx + cpu.eax * 1);
    // 004d454a  8b45f0                 -mov eax, dword ptr [ebp - 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 004d454d  43                     +inc ebx
    {
        x86::reg32& tmp = cpu.ebx;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 004d454e  668b00                 -mov ax, word ptr [eax]
    cpu.ax = app->getMemory<x86::reg16>(cpu.eax);
    // 004d4551  668907                 -mov word ptr [edi], ax
    app->getMemory<x86::reg16>(cpu.edi) = cpu.ax;
    // 004d4554  ebd4                   -jmp 0x4d452a
    goto L_0x004d452a;
L_0x004d4556:
    // 004d4556  8b8094207900           -mov eax, dword ptr [eax + 0x792094]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(7938196) /* 0x792094 */);
    // 004d455c  01c0                   -add eax, eax
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.eax));
    // 004d455e  01c1                   -add ecx, eax
    (cpu.ecx) += x86::reg32(x86::sreg32(cpu.eax));
    // 004d4560  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004d4563  8b4002                 -mov eax, dword ptr [eax + 2]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(2) /* 0x2 */);
    // 004d4566  c1f810                 -sar eax, 0x10
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (16 /*0x10*/ % 32));
    // 004d4569  01c0                   -add eax, eax
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.eax));
    // 004d456b  01c2                   +add edx, eax
    {
        x86::reg32& tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.eax));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 004d456d  ff45f4                 +inc dword ptr [ebp - 0xc]
    {
        auto tmp = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 004d4570  eba1                   -jmp 0x4d4513
    goto L_0x004d4513;
L_0x004d4572:
    // 004d4572  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004d4574  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d4575  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d4576  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d4577  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_4d4580: native, nfs3hp::render::pieceTexture */

/* sub_4d4ae0: native, nfs3hp::render::cabinTextures */

/* align: skip  */
void Application::sub_4d5030(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004d5030  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004d5031  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004d5032  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004d5033  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004d5034  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004d5036  b90b000000             -mov ecx, 0xb
    cpu.ecx = 11 /*0xb*/;
    // 004d503b  89df                   -mov edi, ebx
    cpu.edi = cpu.ebx;
    // 004d503d  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 004d503f  f3a5                   -rep movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004d5041  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d5042  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d5043  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d5044  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d5045  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x44 0x20 0x00 */
void Application::sub_4d5060(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
  goto start;
dynamic_jump:
  switch(cpu.ip)
  {
start:
    // 004d5060  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004d5061  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004d5062  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004d5063  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004d5064  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004d5066  b90b000000             -mov ecx, 0xb
    cpu.ecx = 11 /*0xb*/;
    // 004d506b  89df                   -mov edi, ebx
    cpu.edi = cpu.ebx;
    // 004d506d  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 004d506f  f3a5                   -rep movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004d5071  83fa04                 +cmp edx, 4
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(4 /*0x4*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004d5074  0f878d010000           -ja 0x4d5207
    if (!cpu.flags.cf && !cpu.flags.zf)
    {
        goto L_0x004d5207;
    }
    // 004d507a  ff249548504d00         -jmp dword ptr [edx*4 + 0x4d5048]
    cpu.ip = app->getMemory<x86::reg32>(5066824 + cpu.edx * 4); goto dynamic_jump;
  case 0x004d5081:
    // 004d5081  8b5010                 -mov edx, dword ptr [eax + 0x10]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(16) /* 0x10 */);
    // 004d5084  895308                 -mov dword ptr [ebx + 8], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(8) /* 0x8 */) = cpu.edx;
    // 004d5087  8b5014                 -mov edx, dword ptr [eax + 0x14]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */);
    // 004d508a  89530c                 -mov dword ptr [ebx + 0xc], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(12) /* 0xc */) = cpu.edx;
    // 004d508d  8b5008                 -mov edx, dword ptr [eax + 8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 004d5090  895310                 -mov dword ptr [ebx + 0x10], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(16) /* 0x10 */) = cpu.edx;
    // 004d5093  8b500c                 -mov edx, dword ptr [eax + 0xc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
    // 004d5096  895314                 -mov dword ptr [ebx + 0x14], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(20) /* 0x14 */) = cpu.edx;
    // 004d5099  8b5020                 -mov edx, dword ptr [eax + 0x20]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(32) /* 0x20 */);
    // 004d509c  895318                 -mov dword ptr [ebx + 0x18], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(24) /* 0x18 */) = cpu.edx;
    // 004d509f  8b5024                 -mov edx, dword ptr [eax + 0x24]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(36) /* 0x24 */);
    // 004d50a2  89531c                 -mov dword ptr [ebx + 0x1c], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(28) /* 0x1c */) = cpu.edx;
    // 004d50a5  8b5018                 -mov edx, dword ptr [eax + 0x18]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */);
    // 004d50a8  895320                 -mov dword ptr [ebx + 0x20], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(32) /* 0x20 */) = cpu.edx;
    // 004d50ab  d9401c                 -fld dword ptr [eax + 0x1c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(28) /* 0x1c */));
    // 004d50ae  8a6328                 -mov ah, byte ptr [ebx + 0x28]
    cpu.ah = app->getMemory<x86::reg8>(cpu.ebx + x86::reg32(40) /* 0x28 */);
    // 004d50b1  80f401                 -xor ah, 1
    cpu.ah ^= x86::reg8(x86::sreg8(1 /*0x1*/));
    // 004d50b4  d95b24                 -fstp dword ptr [ebx + 0x24]
    app->getMemory<float>(cpu.ebx + x86::reg32(36) /* 0x24 */) = float(fpu1);
    // 004d50b7  886328                 -mov byte ptr [ebx + 0x28], ah
    app->getMemory<x86::reg8>(cpu.ebx + x86::reg32(40) /* 0x28 */) = cpu.ah;
    // 004d50ba  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d50bb  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d50bc  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d50bd  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    }
    // 004d50be  c3                     -ret 
    cpu.esp += 4;
    return;
  case 0x004d50bf:
    // 004d50bf  d94020                 -fld dword ptr [eax + 0x20]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu2 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(32) /* 0x20 */));
    // 004d50c2  8a5328                 -mov dl, byte ptr [ebx + 0x28]
    cpu.dl = app->getMemory<x86::reg8>(cpu.ebx + x86::reg32(40) /* 0x28 */);
    // 004d50c5  d95b08                 -fstp dword ptr [ebx + 8]
    app->getMemory<float>(cpu.ebx + x86::reg32(8) /* 0x8 */) = float(fpu2);
    // 004d50c8  d94024                 -fld dword ptr [eax + 0x24]
    x86::Float fpu3 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(36) /* 0x24 */));
    // 004d50cb  80f201                 -xor dl, 1
    cpu.dl ^= x86::reg8(x86::sreg8(1 /*0x1*/));
    // 004d50ce  d95b0c                 -fstp dword ptr [ebx + 0xc]
    app->getMemory<float>(cpu.ebx + x86::reg32(12) /* 0xc */) = float(fpu3);
    // 004d50d1  8b4818                 -mov ecx, dword ptr [eax + 0x18]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */);
    // 004d50d4  894b10                 -mov dword ptr [ebx + 0x10], ecx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(16) /* 0x10 */) = cpu.ecx;
    // 004d50d7  8b481c                 -mov ecx, dword ptr [eax + 0x1c]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(28) /* 0x1c */);
    // 004d50da  894b14                 -mov dword ptr [ebx + 0x14], ecx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(20) /* 0x14 */) = cpu.ecx;
    // 004d50dd  8b4810                 -mov ecx, dword ptr [eax + 0x10]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(16) /* 0x10 */);
    // 004d50e0  894b18                 -mov dword ptr [ebx + 0x18], ecx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(24) /* 0x18 */) = cpu.ecx;
    // 004d50e3  8b4814                 -mov ecx, dword ptr [eax + 0x14]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */);
    // 004d50e6  894b1c                 -mov dword ptr [ebx + 0x1c], ecx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(28) /* 0x1c */) = cpu.ecx;
    // 004d50e9  8b4808                 -mov ecx, dword ptr [eax + 8]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 004d50ec  894b20                 -mov dword ptr [ebx + 0x20], ecx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(32) /* 0x20 */) = cpu.ecx;
    // 004d50ef  8b480c                 -mov ecx, dword ptr [eax + 0xc]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
    // 004d50f2  894b24                 -mov dword ptr [ebx + 0x24], ecx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(36) /* 0x24 */) = cpu.ecx;
    // 004d50f5  885328                 -mov byte ptr [ebx + 0x28], dl
    app->getMemory<x86::reg8>(cpu.ebx + x86::reg32(40) /* 0x28 */) = cpu.dl;
    // 004d50f8  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d50f9  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d50fa  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d50fb  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    }
    // 004d50fc  c3                     -ret 
    cpu.esp += 4;
    return;
  case 0x004d50fd:
    // 004d50fd  f6402801               +test byte ptr [eax + 0x28], 1
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(cpu.eax + x86::reg32(40) /* 0x28 */) & 1 /*0x1*/));
    // 004d5101  742f                   -je 0x4d5132
    if (cpu.flags.zf)
    {
        goto L_0x004d5132;
    }
    // 004d5103  8b5020                 -mov edx, dword ptr [eax + 0x20]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(32) /* 0x20 */);
    // 004d5106  895308                 -mov dword ptr [ebx + 8], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(8) /* 0x8 */) = cpu.edx;
    // 004d5109  8b5024                 -mov edx, dword ptr [eax + 0x24]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(36) /* 0x24 */);
    // 004d510c  89530c                 -mov dword ptr [ebx + 0xc], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(12) /* 0xc */) = cpu.edx;
    // 004d510f  8b5008                 -mov edx, dword ptr [eax + 8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 004d5112  895310                 -mov dword ptr [ebx + 0x10], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(16) /* 0x10 */) = cpu.edx;
    // 004d5115  8b500c                 -mov edx, dword ptr [eax + 0xc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
    // 004d5118  895314                 -mov dword ptr [ebx + 0x14], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(20) /* 0x14 */) = cpu.edx;
    // 004d511b  8b5010                 -mov edx, dword ptr [eax + 0x10]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(16) /* 0x10 */);
    // 004d511e  895318                 -mov dword ptr [ebx + 0x18], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(24) /* 0x18 */) = cpu.edx;
    // 004d5121  8b5014                 -mov edx, dword ptr [eax + 0x14]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */);
    // 004d5124  89531c                 -mov dword ptr [ebx + 0x1c], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(28) /* 0x1c */) = cpu.edx;
    // 004d5127  8b5018                 -mov edx, dword ptr [eax + 0x18]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */);
    // 004d512a  895320                 -mov dword ptr [ebx + 0x20], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(32) /* 0x20 */) = cpu.edx;
    // 004d512d  8b501c                 -mov edx, dword ptr [eax + 0x1c]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(28) /* 0x1c */);
    // 004d5130  eb2d                   -jmp 0x4d515f
    goto L_0x004d515f;
L_0x004d5132:
    // 004d5132  8b5010                 -mov edx, dword ptr [eax + 0x10]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(16) /* 0x10 */);
    // 004d5135  895308                 -mov dword ptr [ebx + 8], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(8) /* 0x8 */) = cpu.edx;
    // 004d5138  8b5014                 -mov edx, dword ptr [eax + 0x14]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */);
    // 004d513b  89530c                 -mov dword ptr [ebx + 0xc], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(12) /* 0xc */) = cpu.edx;
    // 004d513e  8b5018                 -mov edx, dword ptr [eax + 0x18]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */);
    // 004d5141  895310                 -mov dword ptr [ebx + 0x10], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(16) /* 0x10 */) = cpu.edx;
    // 004d5144  8b501c                 -mov edx, dword ptr [eax + 0x1c]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(28) /* 0x1c */);
    // 004d5147  895314                 -mov dword ptr [ebx + 0x14], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(20) /* 0x14 */) = cpu.edx;
    // 004d514a  8b5020                 -mov edx, dword ptr [eax + 0x20]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(32) /* 0x20 */);
    // 004d514d  895318                 -mov dword ptr [ebx + 0x18], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(24) /* 0x18 */) = cpu.edx;
    // 004d5150  8b5024                 -mov edx, dword ptr [eax + 0x24]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(36) /* 0x24 */);
    // 004d5153  89531c                 -mov dword ptr [ebx + 0x1c], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(28) /* 0x1c */) = cpu.edx;
    // 004d5156  8b5008                 -mov edx, dword ptr [eax + 8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 004d5159  895320                 -mov dword ptr [ebx + 0x20], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(32) /* 0x20 */) = cpu.edx;
    // 004d515c  8b500c                 -mov edx, dword ptr [eax + 0xc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
L_0x004d515f:
    // 004d515f  895324                 -mov dword ptr [ebx + 0x24], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(36) /* 0x24 */) = cpu.edx;
    // 004d5162  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d5163  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d5164  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d5165  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d5166  c3                     -ret 
    cpu.esp += 4;
    return;
  case 0x004d5167:
    // 004d5167  8b5018                 -mov edx, dword ptr [eax + 0x18]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */);
    // 004d516a  895308                 -mov dword ptr [ebx + 8], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(8) /* 0x8 */) = cpu.edx;
    // 004d516d  8b501c                 -mov edx, dword ptr [eax + 0x1c]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(28) /* 0x1c */);
    // 004d5170  89530c                 -mov dword ptr [ebx + 0xc], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(12) /* 0xc */) = cpu.edx;
    // 004d5173  8b5020                 -mov edx, dword ptr [eax + 0x20]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(32) /* 0x20 */);
    // 004d5176  895310                 -mov dword ptr [ebx + 0x10], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(16) /* 0x10 */) = cpu.edx;
    // 004d5179  8b5024                 -mov edx, dword ptr [eax + 0x24]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(36) /* 0x24 */);
    // 004d517c  895314                 -mov dword ptr [ebx + 0x14], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(20) /* 0x14 */) = cpu.edx;
    // 004d517f  8b5008                 -mov edx, dword ptr [eax + 8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 004d5182  895318                 -mov dword ptr [ebx + 0x18], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(24) /* 0x18 */) = cpu.edx;
    // 004d5185  8b500c                 -mov edx, dword ptr [eax + 0xc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
    // 004d5188  89531c                 -mov dword ptr [ebx + 0x1c], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(28) /* 0x1c */) = cpu.edx;
    // 004d518b  8b5010                 -mov edx, dword ptr [eax + 0x10]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(16) /* 0x10 */);
    // 004d518e  895320                 -mov dword ptr [ebx + 0x20], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(32) /* 0x20 */) = cpu.edx;
    // 004d5191  8b5014                 -mov edx, dword ptr [eax + 0x14]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */);
    // 004d5194  895324                 -mov dword ptr [ebx + 0x24], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(36) /* 0x24 */) = cpu.edx;
    // 004d5197  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d5198  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d5199  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d519a  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d519b  c3                     -ret 
    cpu.esp += 4;
    return;
  case 0x004d519c:
    // 004d519c  f6402801               +test byte ptr [eax + 0x28], 1
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(cpu.eax + x86::reg32(40) /* 0x28 */) & 1 /*0x1*/));
    // 004d51a0  7435                   -je 0x4d51d7
    if (cpu.flags.zf)
    {
        goto L_0x004d51d7;
    }
    // 004d51a2  8b5010                 -mov edx, dword ptr [eax + 0x10]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(16) /* 0x10 */);
    // 004d51a5  895308                 -mov dword ptr [ebx + 8], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(8) /* 0x8 */) = cpu.edx;
    // 004d51a8  8b5014                 -mov edx, dword ptr [eax + 0x14]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */);
    // 004d51ab  89530c                 -mov dword ptr [ebx + 0xc], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(12) /* 0xc */) = cpu.edx;
    // 004d51ae  8b5018                 -mov edx, dword ptr [eax + 0x18]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */);
    // 004d51b1  895310                 -mov dword ptr [ebx + 0x10], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(16) /* 0x10 */) = cpu.edx;
    // 004d51b4  8b501c                 -mov edx, dword ptr [eax + 0x1c]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(28) /* 0x1c */);
    // 004d51b7  895314                 -mov dword ptr [ebx + 0x14], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(20) /* 0x14 */) = cpu.edx;
    // 004d51ba  8b5020                 -mov edx, dword ptr [eax + 0x20]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(32) /* 0x20 */);
    // 004d51bd  895318                 -mov dword ptr [ebx + 0x18], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(24) /* 0x18 */) = cpu.edx;
    // 004d51c0  8b5024                 -mov edx, dword ptr [eax + 0x24]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(36) /* 0x24 */);
    // 004d51c3  89531c                 -mov dword ptr [ebx + 0x1c], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(28) /* 0x1c */) = cpu.edx;
    // 004d51c6  8b5008                 -mov edx, dword ptr [eax + 8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 004d51c9  895320                 -mov dword ptr [ebx + 0x20], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(32) /* 0x20 */) = cpu.edx;
    // 004d51cc  8b500c                 -mov edx, dword ptr [eax + 0xc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
    // 004d51cf  895324                 -mov dword ptr [ebx + 0x24], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(36) /* 0x24 */) = cpu.edx;
    // 004d51d2  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d51d3  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d51d4  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d51d5  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d51d6  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004d51d7:
    // 004d51d7  8b5020                 -mov edx, dword ptr [eax + 0x20]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(32) /* 0x20 */);
    // 004d51da  895308                 -mov dword ptr [ebx + 8], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(8) /* 0x8 */) = cpu.edx;
    // 004d51dd  8b5024                 -mov edx, dword ptr [eax + 0x24]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(36) /* 0x24 */);
    // 004d51e0  89530c                 -mov dword ptr [ebx + 0xc], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(12) /* 0xc */) = cpu.edx;
    // 004d51e3  8b5008                 -mov edx, dword ptr [eax + 8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 004d51e6  895310                 -mov dword ptr [ebx + 0x10], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(16) /* 0x10 */) = cpu.edx;
    // 004d51e9  8b500c                 -mov edx, dword ptr [eax + 0xc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
    // 004d51ec  895314                 -mov dword ptr [ebx + 0x14], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(20) /* 0x14 */) = cpu.edx;
    // 004d51ef  8b5010                 -mov edx, dword ptr [eax + 0x10]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(16) /* 0x10 */);
    // 004d51f2  895318                 -mov dword ptr [ebx + 0x18], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(24) /* 0x18 */) = cpu.edx;
    // 004d51f5  8b5014                 -mov edx, dword ptr [eax + 0x14]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */);
    // 004d51f8  89531c                 -mov dword ptr [ebx + 0x1c], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(28) /* 0x1c */) = cpu.edx;
    // 004d51fb  8b5018                 -mov edx, dword ptr [eax + 0x18]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */);
    // 004d51fe  895320                 -mov dword ptr [ebx + 0x20], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(32) /* 0x20 */) = cpu.edx;
    // 004d5201  8b501c                 -mov edx, dword ptr [eax + 0x1c]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(28) /* 0x1c */);
    // 004d5204  895324                 -mov dword ptr [ebx + 0x24], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(36) /* 0x24 */) = cpu.edx;
L_0x004d5207:
    // 004d5207  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d5208  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d5209  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d520a  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d520b  c3                     -ret 
    cpu.esp += 4;
    return;
  default:
    NFS2_ASSERT(false);
  }
}

/* align: skip  */
void Application::sub_4d5220(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
  goto start;
dynamic_jump:
  switch(cpu.ip)
  {
start:
    // 004d5220  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004d5221  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004d5222  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004d5223  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004d5224  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004d5226  b90b000000             -mov ecx, 0xb
    cpu.ecx = 11 /*0xb*/;
    // 004d522b  89df                   -mov edi, ebx
    cpu.edi = cpu.ebx;
    // 004d522d  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 004d522f  f3a5                   -rep movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004d5231  83fa04                 +cmp edx, 4
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(4 /*0x4*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004d5234  0f871d010000           -ja 0x4d5357
    if (!cpu.flags.cf && !cpu.flags.zf)
    {
        goto L_0x004d5357;
    }
    // 004d523a  ff24950c524d00         -jmp dword ptr [edx*4 + 0x4d520c]
    cpu.ip = app->getMemory<x86::reg32>(5067276 + cpu.edx * 4); goto dynamic_jump;
  case 0x004d5241:
    // 004d5241  8b5010                 -mov edx, dword ptr [eax + 0x10]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(16) /* 0x10 */);
    // 004d5244  895308                 -mov dword ptr [ebx + 8], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(8) /* 0x8 */) = cpu.edx;
    // 004d5247  8b5014                 -mov edx, dword ptr [eax + 0x14]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */);
    // 004d524a  89530c                 -mov dword ptr [ebx + 0xc], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(12) /* 0xc */) = cpu.edx;
    // 004d524d  8b5008                 -mov edx, dword ptr [eax + 8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 004d5250  895310                 -mov dword ptr [ebx + 0x10], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(16) /* 0x10 */) = cpu.edx;
    // 004d5253  8b500c                 -mov edx, dword ptr [eax + 0xc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
    // 004d5256  895314                 -mov dword ptr [ebx + 0x14], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(20) /* 0x14 */) = cpu.edx;
    // 004d5259  8b5020                 -mov edx, dword ptr [eax + 0x20]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(32) /* 0x20 */);
    // 004d525c  895318                 -mov dword ptr [ebx + 0x18], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(24) /* 0x18 */) = cpu.edx;
    // 004d525f  8b5024                 -mov edx, dword ptr [eax + 0x24]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(36) /* 0x24 */);
    // 004d5262  89531c                 -mov dword ptr [ebx + 0x1c], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(28) /* 0x1c */) = cpu.edx;
    // 004d5265  8b5018                 -mov edx, dword ptr [eax + 0x18]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */);
    // 004d5268  895320                 -mov dword ptr [ebx + 0x20], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(32) /* 0x20 */) = cpu.edx;
    // 004d526b  d9401c                 -fld dword ptr [eax + 0x1c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(28) /* 0x1c */));
    // 004d526e  8a6328                 -mov ah, byte ptr [ebx + 0x28]
    cpu.ah = app->getMemory<x86::reg8>(cpu.ebx + x86::reg32(40) /* 0x28 */);
    // 004d5271  80f401                 -xor ah, 1
    cpu.ah ^= x86::reg8(x86::sreg8(1 /*0x1*/));
    // 004d5274  d95b24                 -fstp dword ptr [ebx + 0x24]
    app->getMemory<float>(cpu.ebx + x86::reg32(36) /* 0x24 */) = float(fpu1);
    // 004d5277  886328                 -mov byte ptr [ebx + 0x28], ah
    app->getMemory<x86::reg8>(cpu.ebx + x86::reg32(40) /* 0x28 */) = cpu.ah;
    // 004d527a  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d527b  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d527c  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d527d  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    }
    // 004d527e  c3                     -ret 
    cpu.esp += 4;
    return;
  case 0x004d527f:
    // 004d527f  d94020                 -fld dword ptr [eax + 0x20]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu2 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(32) /* 0x20 */));
    // 004d5282  8a5328                 -mov dl, byte ptr [ebx + 0x28]
    cpu.dl = app->getMemory<x86::reg8>(cpu.ebx + x86::reg32(40) /* 0x28 */);
    // 004d5285  d95b08                 -fstp dword ptr [ebx + 8]
    app->getMemory<float>(cpu.ebx + x86::reg32(8) /* 0x8 */) = float(fpu2);
    // 004d5288  d94024                 -fld dword ptr [eax + 0x24]
    x86::Float fpu3 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(36) /* 0x24 */));
    // 004d528b  80f201                 -xor dl, 1
    cpu.dl ^= x86::reg8(x86::sreg8(1 /*0x1*/));
    // 004d528e  d95b0c                 -fstp dword ptr [ebx + 0xc]
    app->getMemory<float>(cpu.ebx + x86::reg32(12) /* 0xc */) = float(fpu3);
    // 004d5291  8b4818                 -mov ecx, dword ptr [eax + 0x18]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */);
    // 004d5294  894b10                 -mov dword ptr [ebx + 0x10], ecx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(16) /* 0x10 */) = cpu.ecx;
    // 004d5297  8b481c                 -mov ecx, dword ptr [eax + 0x1c]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(28) /* 0x1c */);
    // 004d529a  894b14                 -mov dword ptr [ebx + 0x14], ecx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(20) /* 0x14 */) = cpu.ecx;
    // 004d529d  8b4810                 -mov ecx, dword ptr [eax + 0x10]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(16) /* 0x10 */);
    // 004d52a0  894b18                 -mov dword ptr [ebx + 0x18], ecx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(24) /* 0x18 */) = cpu.ecx;
    // 004d52a3  8b4814                 -mov ecx, dword ptr [eax + 0x14]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */);
    // 004d52a6  894b1c                 -mov dword ptr [ebx + 0x1c], ecx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(28) /* 0x1c */) = cpu.ecx;
    // 004d52a9  8b4808                 -mov ecx, dword ptr [eax + 8]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 004d52ac  894b20                 -mov dword ptr [ebx + 0x20], ecx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(32) /* 0x20 */) = cpu.ecx;
    // 004d52af  8b480c                 -mov ecx, dword ptr [eax + 0xc]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
    // 004d52b2  894b24                 -mov dword ptr [ebx + 0x24], ecx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(36) /* 0x24 */) = cpu.ecx;
    // 004d52b5  885328                 -mov byte ptr [ebx + 0x28], dl
    app->getMemory<x86::reg8>(cpu.ebx + x86::reg32(40) /* 0x28 */) = cpu.dl;
    // 004d52b8  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d52b9  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d52ba  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d52bb  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    }
    // 004d52bc  c3                     -ret 
    cpu.esp += 4;
    return;
  case 0x004d52bd:
    // 004d52bd  8b5020                 -mov edx, dword ptr [eax + 0x20]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(32) /* 0x20 */);
    // 004d52c0  895308                 -mov dword ptr [ebx + 8], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(8) /* 0x8 */) = cpu.edx;
    // 004d52c3  8b5024                 -mov edx, dword ptr [eax + 0x24]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(36) /* 0x24 */);
    // 004d52c6  89530c                 -mov dword ptr [ebx + 0xc], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(12) /* 0xc */) = cpu.edx;
    // 004d52c9  8b5008                 -mov edx, dword ptr [eax + 8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 004d52cc  895310                 -mov dword ptr [ebx + 0x10], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(16) /* 0x10 */) = cpu.edx;
    // 004d52cf  8b500c                 -mov edx, dword ptr [eax + 0xc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
    // 004d52d2  895314                 -mov dword ptr [ebx + 0x14], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(20) /* 0x14 */) = cpu.edx;
    // 004d52d5  8b5010                 -mov edx, dword ptr [eax + 0x10]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(16) /* 0x10 */);
    // 004d52d8  895318                 -mov dword ptr [ebx + 0x18], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(24) /* 0x18 */) = cpu.edx;
    // 004d52db  8b5014                 -mov edx, dword ptr [eax + 0x14]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */);
    // 004d52de  89531c                 -mov dword ptr [ebx + 0x1c], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(28) /* 0x1c */) = cpu.edx;
    // 004d52e1  8b5018                 -mov edx, dword ptr [eax + 0x18]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */);
    // 004d52e4  895320                 -mov dword ptr [ebx + 0x20], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(32) /* 0x20 */) = cpu.edx;
    // 004d52e7  8b501c                 -mov edx, dword ptr [eax + 0x1c]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(28) /* 0x1c */);
    // 004d52ea  895324                 -mov dword ptr [ebx + 0x24], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(36) /* 0x24 */) = cpu.edx;
    // 004d52ed  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d52ee  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d52ef  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d52f0  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d52f1  c3                     -ret 
    cpu.esp += 4;
    return;
  case 0x004d52f2:
    // 004d52f2  8b5018                 -mov edx, dword ptr [eax + 0x18]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */);
    // 004d52f5  895308                 -mov dword ptr [ebx + 8], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(8) /* 0x8 */) = cpu.edx;
    // 004d52f8  8b501c                 -mov edx, dword ptr [eax + 0x1c]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(28) /* 0x1c */);
    // 004d52fb  89530c                 -mov dword ptr [ebx + 0xc], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(12) /* 0xc */) = cpu.edx;
    // 004d52fe  8b5020                 -mov edx, dword ptr [eax + 0x20]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(32) /* 0x20 */);
    // 004d5301  895310                 -mov dword ptr [ebx + 0x10], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(16) /* 0x10 */) = cpu.edx;
    // 004d5304  8b5024                 -mov edx, dword ptr [eax + 0x24]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(36) /* 0x24 */);
    // 004d5307  895314                 -mov dword ptr [ebx + 0x14], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(20) /* 0x14 */) = cpu.edx;
    // 004d530a  8b5008                 -mov edx, dword ptr [eax + 8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 004d530d  895318                 -mov dword ptr [ebx + 0x18], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(24) /* 0x18 */) = cpu.edx;
    // 004d5310  8b500c                 -mov edx, dword ptr [eax + 0xc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
    // 004d5313  89531c                 -mov dword ptr [ebx + 0x1c], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(28) /* 0x1c */) = cpu.edx;
    // 004d5316  8b5010                 -mov edx, dword ptr [eax + 0x10]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(16) /* 0x10 */);
    // 004d5319  895320                 -mov dword ptr [ebx + 0x20], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(32) /* 0x20 */) = cpu.edx;
    // 004d531c  8b5014                 -mov edx, dword ptr [eax + 0x14]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */);
    // 004d531f  895324                 -mov dword ptr [ebx + 0x24], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(36) /* 0x24 */) = cpu.edx;
    // 004d5322  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d5323  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d5324  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d5325  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d5326  c3                     -ret 
    cpu.esp += 4;
    return;
  case 0x004d5327:
    // 004d5327  8b5010                 -mov edx, dword ptr [eax + 0x10]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(16) /* 0x10 */);
    // 004d532a  895308                 -mov dword ptr [ebx + 8], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(8) /* 0x8 */) = cpu.edx;
    // 004d532d  8b5014                 -mov edx, dword ptr [eax + 0x14]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */);
    // 004d5330  89530c                 -mov dword ptr [ebx + 0xc], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(12) /* 0xc */) = cpu.edx;
    // 004d5333  8b5018                 -mov edx, dword ptr [eax + 0x18]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */);
    // 004d5336  895310                 -mov dword ptr [ebx + 0x10], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(16) /* 0x10 */) = cpu.edx;
    // 004d5339  8b501c                 -mov edx, dword ptr [eax + 0x1c]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(28) /* 0x1c */);
    // 004d533c  895314                 -mov dword ptr [ebx + 0x14], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(20) /* 0x14 */) = cpu.edx;
    // 004d533f  8b5020                 -mov edx, dword ptr [eax + 0x20]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(32) /* 0x20 */);
    // 004d5342  895318                 -mov dword ptr [ebx + 0x18], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(24) /* 0x18 */) = cpu.edx;
    // 004d5345  8b5024                 -mov edx, dword ptr [eax + 0x24]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(36) /* 0x24 */);
    // 004d5348  89531c                 -mov dword ptr [ebx + 0x1c], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(28) /* 0x1c */) = cpu.edx;
    // 004d534b  8b5008                 -mov edx, dword ptr [eax + 8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 004d534e  895320                 -mov dword ptr [ebx + 0x20], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(32) /* 0x20 */) = cpu.edx;
    // 004d5351  8b500c                 -mov edx, dword ptr [eax + 0xc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
    // 004d5354  895324                 -mov dword ptr [ebx + 0x24], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(36) /* 0x24 */) = cpu.edx;
L_0x004d5357:
    // 004d5357  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d5358  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d5359  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d535a  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d535b  c3                     -ret 
    cpu.esp += 4;
    return;
  default:
    NFS2_ASSERT(false);
  }
}

/* align: skip 0x8d 0x44 0x20 0x00 */
void Application::sub_4d5360(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004d5360  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004d5361  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004d5363  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d5364  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 0x8b 0xdb */
void Application::sub_4d5370(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004d5370  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004d5371  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004d5372  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004d5373  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004d5374  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004d5375  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004d5376  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004d5378  81ec08010000           -sub esp, 0x108
    (cpu.esp) -= x86::reg32(x86::sreg32(264 /*0x108*/));
    // 004d537e  6834297a00             -push 0x7a2934
    app->getMemory<x86::reg32>(cpu.esp-4) = 8005940 /*0x7a2934*/;
    cpu.esp -= 4;
    // 004d5383  6858945400             -push 0x549458
    app->getMemory<x86::reg32>(cpu.esp-4) = 5543000 /*0x549458*/;
    cpu.esp -= 4;
    // 004d5388  8d85f8feffff           -lea eax, [ebp - 0x108]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-264) /* -0x108 */);
    // 004d538e  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004d538f  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 004d5391  e8faa20000             -call 0x4df690
    cpu.esp -= 4;
    nfs3hp::watcom::sprintf(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d5396  83c40c                 -add esp, 0xc
    (cpu.esp) += x86::reg32(x86::sreg32(12 /*0xc*/));
    // 004d5399  8d85f8feffff           -lea eax, [ebp - 0x108]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-264) /* -0x108 */);
    // 004d539f  31ff                   +xor edi, edi
    cpu.clear_co();
    cpu.set_szp((cpu.edi ^= x86::reg32(x86::sreg32(cpu.edi))));
    // 004d53a1  e81abb0000             -call 0x4e0ec0
    cpu.esp -= 4;
    nfs3hp::ea::loadFile(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d53a6  6800001042             -push 0x42100000
    app->getMemory<x86::reg32>(cpu.esp-4) = 1108344832 /*0x42100000*/;
    cpu.esp -= 4;
    // 004d53ab  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 004d53ad  e87efefbff             -call 0x495230
    cpu.esp -= 4;
    nfs3hp::graphics::drawLoadingProgress(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d53b2  eb05                   -jmp 0x4d53b9
    goto L_0x004d53b9;
L_0x004d53b4:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004d53b4  83ff09                 +cmp edi, 9
    {
        x86::reg32 tmp1 = cpu.edi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(9 /*0x9*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004d53b7  7f70                   -jg 0x4d5429
    if (!cpu.flags.zf && (cpu.flags.sf == cpu.flags.of))
    {
        goto L_0x004d5429;
    }
L_0x004d53b9:
    // 004d53b9  e812e0fcff             -call 0x4a33d0
    cpu.esp -= 4;
    sub_4a33d0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d53be  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004d53bf  6864945400             -push 0x549464
    app->getMemory<x86::reg32>(cpu.esp-4) = 5543012 /*0x549464*/;
    cpu.esp -= 4;
    // 004d53c4  8d85f8feffff           -lea eax, [ebp - 0x108]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-264) /* -0x108 */);
    // 004d53ca  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004d53cb  e8c0a20000             -call 0x4df690
    cpu.esp -= 4;
    nfs3hp::watcom::sprintf(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d53d0  8d04bd00000000         -lea eax, [edi*4]
    cpu.eax = x86::reg32(cpu.edi * 4);
    // 004d53d7  29f8                   -sub eax, edi
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edi));
    // 004d53d9  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 004d53dc  29f8                   -sub eax, edi
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edi));
    // 004d53de  bb20000000             -mov ebx, 0x20
    cpu.ebx = 32 /*0x20*/;
    // 004d53e3  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 004d53e6  83c40c                 -add esp, 0xc
    (cpu.esp) += x86::reg32(x86::sreg32(12 /*0xc*/));
    // 004d53e9  8945f8                 -mov dword ptr [ebp - 8], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.eax;
    // 004d53ec  b820448b00             -mov eax, 0x8b4420
    cpu.eax = 9126944 /*0x8b4420*/;
    // 004d53f1  8b55f8                 -mov edx, dword ptr [ebp - 8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004d53f4  6a00                   -push 0
    app->getMemory<x86::reg32>(cpu.esp-4) = 0 /*0x0*/;
    cpu.esp -= 4;
    // 004d53f6  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 004d53f8  8d95f8feffff           -lea edx, [ebp - 0x108]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-264) /* -0x108 */);
    // 004d53fe  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 004d5401  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 004d5403  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004d5405  e876ecffff             -call 0x4d4080
    cpu.esp -= 4;
    sub_4d4080(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d540a  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004d540d  8a9048448b00           -mov dl, byte ptr [eax + 0x8b4448]
    cpu.dl = app->getMemory<x86::reg8>(cpu.eax + x86::reg32(9126984) /* 0x8b4448 */);
    // 004d5413  80ca04                 +or dl, 4
    cpu.clear_co();
    cpu.set_szp((cpu.dl |= x86::reg8(x86::sreg8(4 /*0x4*/))));
    // 004d5416  47                     +inc edi
    {
        x86::reg32& tmp = cpu.edi;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 004d5417  889048448b00           -mov byte ptr [eax + 0x8b4448], dl
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(9126984) /* 0x8b4448 */) = cpu.dl;
    // 004d541d  8b55fc                 -mov edx, dword ptr [ebp - 4]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004d5420  8914bd9c418b00         -mov dword ptr [edi*4 + 0x8b419c], edx
    app->getMemory<x86::reg32>(x86::reg32(9126300) /* 0x8b419c */ + cpu.edi * 4) = cpu.edx;
    // 004d5427  eb8b                   -jmp 0x4d53b4
    goto L_0x004d53b4;
L_0x004d5429:
    // 004d5429  6a00                   -push 0
    app->getMemory<x86::reg32>(cpu.esp-4) = 0 /*0x0*/;
    cpu.esp -= 4;
    // 004d542b  b9d8458b00             -mov ecx, 0x8b45d8
    cpu.ecx = 9127384 /*0x8b45d8*/;
    // 004d5430  bb20000000             -mov ebx, 0x20
    cpu.ebx = 32 /*0x20*/;
    // 004d5435  ba6c945400             -mov edx, 0x54946c
    cpu.edx = 5543020 /*0x54946c*/;
    // 004d543a  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004d543c  e83fecffff             -call 0x4d4080
    cpu.esp -= 4;
    sub_4d4080(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d5441  b9d8458b00             -mov ecx, 0x8b45d8
    cpu.ecx = 9127384 /*0x8b45d8*/;
    // 004d5446  6a00                   -push 0
    app->getMemory<x86::reg32>(cpu.esp-4) = 0 /*0x0*/;
    cpu.esp -= 4;
    // 004d5448  bb20000000             -mov ebx, 0x20
    cpu.ebx = 32 /*0x20*/;
    // 004d544d  ba74945400             -mov edx, 0x549474
    cpu.edx = 5543028 /*0x549474*/;
    // 004d5452  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004d5454  890d98488b00           -mov dword ptr [0x8b4898], ecx
    app->getMemory<x86::reg32>(x86::reg32(9128088) /* 0x8b4898 */) = cpu.ecx;
    // 004d545a  b904468b00             -mov ecx, 0x8b4604
    cpu.ecx = 9127428 /*0x8b4604*/;
    // 004d545f  e81cecffff             -call 0x4d4080
    cpu.esp -= 4;
    sub_4d4080(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d5464  bb04468b00             -mov ebx, 0x8b4604
    cpu.ebx = 9127428 /*0x8b4604*/;
    // 004d5469  6a00                   -push 0
    app->getMemory<x86::reg32>(cpu.esp-4) = 0 /*0x0*/;
    cpu.esp -= 4;
    // 004d546b  b930468b00             -mov ecx, 0x8b4630
    cpu.ecx = 9127472 /*0x8b4630*/;
    // 004d5470  ba7c945400             -mov edx, 0x54947c
    cpu.edx = 5543036 /*0x54947c*/;
    // 004d5475  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004d5477  891dc8418b00           -mov dword ptr [0x8b41c8], ebx
    app->getMemory<x86::reg32>(x86::reg32(9126344) /* 0x8b41c8 */) = cpu.ebx;
    // 004d547d  bb20000000             -mov ebx, 0x20
    cpu.ebx = 32 /*0x20*/;
    // 004d5482  bf30468b00             -mov edi, 0x8b4630
    cpu.edi = 9127472 /*0x8b4630*/;
    // 004d5487  e8f4ebffff             -call 0x4d4080
    cpu.esp -= 4;
    sub_4d4080(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d548c  6a00                   -push 0
    app->getMemory<x86::reg32>(cpu.esp-4) = 0 /*0x0*/;
    cpu.esp -= 4;
    // 004d548e  b95c468b00             -mov ecx, 0x8b465c
    cpu.ecx = 9127516 /*0x8b465c*/;
    // 004d5493  bb20000000             -mov ebx, 0x20
    cpu.ebx = 32 /*0x20*/;
    // 004d5498  ba84945400             -mov edx, 0x549484
    cpu.edx = 5543044 /*0x549484*/;
    // 004d549d  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004d549f  893dcc418b00           -mov dword ptr [0x8b41cc], edi
    app->getMemory<x86::reg32>(x86::reg32(9126348) /* 0x8b41cc */) = cpu.edi;
    // 004d54a5  e8d6ebffff             -call 0x4d4080
    cpu.esp -= 4;
    sub_4d4080(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d54aa  b85c468b00             -mov eax, 0x8b465c
    cpu.eax = 9127516 /*0x8b465c*/;
    // 004d54af  6a00                   -push 0
    app->getMemory<x86::reg32>(cpu.esp-4) = 0 /*0x0*/;
    cpu.esp -= 4;
    // 004d54b1  b988468b00             -mov ecx, 0x8b4688
    cpu.ecx = 9127560 /*0x8b4688*/;
    // 004d54b6  bb20000000             -mov ebx, 0x20
    cpu.ebx = 32 /*0x20*/;
    // 004d54bb  ba8c945400             -mov edx, 0x54948c
    cpu.edx = 5543052 /*0x54948c*/;
    // 004d54c0  a3d0418b00             -mov dword ptr [0x8b41d0], eax
    app->getMemory<x86::reg32>(x86::reg32(9126352) /* 0x8b41d0 */) = cpu.eax;
    // 004d54c5  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004d54c7  e8b4ebffff             -call 0x4d4080
    cpu.esp -= 4;
    sub_4d4080(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d54cc  6800001442             -push 0x42140000
    app->getMemory<x86::reg32>(cpu.esp-4) = 1108606976 /*0x42140000*/;
    cpu.esp -= 4;
    // 004d54d1  ba88468b00             -mov edx, 0x8b4688
    cpu.edx = 9127560 /*0x8b4688*/;
    // 004d54d6  b91c906700             -mov ecx, 0x67901c
    cpu.ecx = 6787100 /*0x67901c*/;
    // 004d54db  bb20000000             -mov ebx, 0x20
    cpu.ebx = 32 /*0x20*/;
    // 004d54e0  8915d4418b00           -mov dword ptr [0x8b41d4], edx
    app->getMemory<x86::reg32>(x86::reg32(9126356) /* 0x8b41d4 */) = cpu.edx;
    // 004d54e6  e845fdfbff             -call 0x495230
    cpu.esp -= 4;
    nfs3hp::graphics::drawLoadingProgress(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d54eb  e8e0defcff             -call 0x4a33d0
    cpu.esp -= 4;
    sub_4a33d0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d54f0  6a00                   -push 0
    app->getMemory<x86::reg32>(cpu.esp-4) = 0 /*0x0*/;
    cpu.esp -= 4;
    // 004d54f2  ba94945400             -mov edx, 0x549494
    cpu.edx = 5543060 /*0x549494*/;
    // 004d54f7  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004d54f9  e882ebffff             -call 0x4d4080
    cpu.esp -= 4;
    sub_4d4080(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d54fe  e8cddefcff             -call 0x4a33d0
    cpu.esp -= 4;
    sub_4a33d0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d5503  6a07                   -push 7
    app->getMemory<x86::reg32>(cpu.esp-4) = 7 /*0x7*/;
    cpu.esp -= 4;
    // 004d5505  b9bc478b00             -mov ecx, 0x8b47bc
    cpu.ecx = 9127868 /*0x8b47bc*/;
    // 004d550a  bb40000000             -mov ebx, 0x40
    cpu.ebx = 64 /*0x40*/;
    // 004d550f  ba9c945400             -mov edx, 0x54949c
    cpu.edx = 5543068 /*0x54949c*/;
    // 004d5514  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004d5516  e865ebffff             -call 0x4d4080
    cpu.esp -= 4;
    sub_4d4080(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d551b  6a07                   -push 7
    app->getMemory<x86::reg32>(cpu.esp-4) = 7 /*0x7*/;
    cpu.esp -= 4;
    // 004d551d  b9e8478b00             -mov ecx, 0x8b47e8
    cpu.ecx = 9127912 /*0x8b47e8*/;
    // 004d5522  bb20000000             -mov ebx, 0x20
    cpu.ebx = 32 /*0x20*/;
    // 004d5527  baa4945400             -mov edx, 0x5494a4
    cpu.edx = 5543076 /*0x5494a4*/;
    // 004d552c  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004d552e  e84debffff             -call 0x4d4080
    cpu.esp -= 4;
    sub_4d4080(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d5533  b80d000000             -mov eax, 0xd
    cpu.eax = 13 /*0xd*/;
    // 004d5538  b914488b00             -mov ecx, 0x8b4814
    cpu.ecx = 9127956 /*0x8b4814*/;
    // 004d553d  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 004d553f  bb80000000             -mov ebx, 0x80
    cpu.ebx = 128 /*0x80*/;
    // 004d5544  e8b7c3f5ff             -call 0x431900
    cpu.esp -= 4;
    nfs3hp::graphics::setRenderState(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d5549  6a07                   -push 7
    app->getMemory<x86::reg32>(cpu.esp-4) = 7 /*0x7*/;
    cpu.esp -= 4;
    // 004d554b  baac945400             -mov edx, 0x5494ac
    cpu.edx = 5543084 /*0x5494ac*/;
    // 004d5550  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004d5552  e829ebffff             -call 0x4d4080
    cpu.esp -= 4;
    sub_4d4080(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d5557  ba01000000             -mov edx, 1
    cpu.edx = 1 /*0x1*/;
    // 004d555c  b80d000000             -mov eax, 0xd
    cpu.eax = 13 /*0xd*/;
    // 004d5561  b940488b00             -mov ecx, 0x8b4840
    cpu.ecx = 9128000 /*0x8b4840*/;
    // 004d5566  bb20000000             -mov ebx, 0x20
    cpu.ebx = 32 /*0x20*/;
    // 004d556b  e890c3f5ff             -call 0x431900
    cpu.esp -= 4;
    nfs3hp::graphics::setRenderState(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d5570  6a07                   -push 7
    app->getMemory<x86::reg32>(cpu.esp-4) = 7 /*0x7*/;
    cpu.esp -= 4;
    // 004d5572  bab4945400             -mov edx, 0x5494b4
    cpu.edx = 5543092 /*0x5494b4*/;
    // 004d5577  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004d5579  e802ebffff             -call 0x4d4080
    cpu.esp -= 4;
    sub_4d4080(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d557e  6a07                   -push 7
    app->getMemory<x86::reg32>(cpu.esp-4) = 7 /*0x7*/;
    cpu.esp -= 4;
    // 004d5580  b96c488b00             -mov ecx, 0x8b486c
    cpu.ecx = 9128044 /*0x8b486c*/;
    // 004d5585  bb40000000             -mov ebx, 0x40
    cpu.ebx = 64 /*0x40*/;
    // 004d558a  babc945400             -mov edx, 0x5494bc
    cpu.edx = 5543100 /*0x5494bc*/;
    // 004d558f  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004d5591  e8eaeaffff             -call 0x4d4080
    cpu.esp -= 4;
    sub_4d4080(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d5596  f605583a7a0002         +test byte ptr [0x7a3a58], 2
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(x86::reg32(8010328) /* 0x7a3a58 */) & 2 /*0x2*/));
    // 004d559d  7418                   -je 0x4d55b7
    if (cpu.flags.zf)
    {
        goto L_0x004d55b7;
    }
    // 004d559f  bac4945400             -mov edx, 0x5494c4
    cpu.edx = 5543108 /*0x5494c4*/;
    // 004d55a4  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004d55a6  e8359c0100             -call 0x4ef1e0
    cpu.esp -= 4;
    sub_4ef1e0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d55ab  bad0da7d00             -mov edx, 0x7ddad0
    cpu.edx = 8248016 /*0x7ddad0*/;
    // 004d55b0  e8ebebffff             -call 0x4d41a0
    cpu.esp -= 4;
    nfs3hp::render::paletteTexture(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d55b5  eb18                   -jmp 0x4d55cf
    goto L_0x004d55cf;
L_0x004d55b7:
    // 004d55b7  6a00                   -push 0
    app->getMemory<x86::reg32>(cpu.esp-4) = 0 /*0x0*/;
    cpu.esp -= 4;
    // 004d55b9  b9d0da7d00             -mov ecx, 0x7ddad0
    cpu.ecx = 8248016 /*0x7ddad0*/;
    // 004d55be  bb20000000             -mov ebx, 0x20
    cpu.ebx = 32 /*0x20*/;
    // 004d55c3  bacc945400             -mov edx, 0x5494cc
    cpu.edx = 5543116 /*0x5494cc*/;
    // 004d55c8  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004d55ca  e8b1eaffff             -call 0x4d4080
    cpu.esp -= 4;
    sub_4d4080(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x004d55cf:
    // 004d55cf  6800001842             -push 0x42180000
    app->getMemory<x86::reg32>(cpu.esp-4) = 1108869120 /*0x42180000*/;
    cpu.esp -= 4;
    // 004d55d4  e857fcfbff             -call 0x495230
    cpu.esp -= 4;
    nfs3hp::graphics::drawLoadingProgress(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d55d9  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004d55db  b9d8418b00             -mov ecx, 0x8b41d8
    cpu.ecx = 9126360 /*0x8b41d8*/;
    // 004d55e0  e8ab5fffff             -call 0x4cb590
    cpu.esp -= 4;
    sub_4cb590(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d55e5  6800001c42             -push 0x421c0000
    app->getMemory<x86::reg32>(cpu.esp-4) = 1109131264 /*0x421c0000*/;
    cpu.esp -= 4;
    // 004d55ea  bb20000000             -mov ebx, 0x20
    cpu.ebx = 32 /*0x20*/;
    // 004d55ef  e83cfcfbff             -call 0x495230
    cpu.esp -= 4;
    nfs3hp::graphics::drawLoadingProgress(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d55f4  6a00                   -push 0
    app->getMemory<x86::reg32>(cpu.esp-4) = 0 /*0x0*/;
    cpu.esp -= 4;
    // 004d55f6  bad4945400             -mov edx, 0x5494d4
    cpu.edx = 5543124 /*0x5494d4*/;
    // 004d55fb  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004d55fd  e87eeaffff             -call 0x4d4080
    cpu.esp -= 4;
    sub_4d4080(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d5602  6a00                   -push 0
    app->getMemory<x86::reg32>(cpu.esp-4) = 0 /*0x0*/;
    cpu.esp -= 4;
    // 004d5604  b938438b00             -mov ecx, 0x8b4338
    cpu.ecx = 9126712 /*0x8b4338*/;
    // 004d5609  bb20000000             -mov ebx, 0x20
    cpu.ebx = 32 /*0x20*/;
    // 004d560e  badc945400             -mov edx, 0x5494dc
    cpu.edx = 5543132 /*0x5494dc*/;
    // 004d5613  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004d5615  e866eaffff             -call 0x4d4080
    cpu.esp -= 4;
    sub_4d4080(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d561a  6a00                   -push 0
    app->getMemory<x86::reg32>(cpu.esp-4) = 0 /*0x0*/;
    cpu.esp -= 4;
    // 004d561c  b964438b00             -mov ecx, 0x8b4364
    cpu.ecx = 9126756 /*0x8b4364*/;
    // 004d5621  bb20000000             -mov ebx, 0x20
    cpu.ebx = 32 /*0x20*/;
    // 004d5626  bae4945400             -mov edx, 0x5494e4
    cpu.edx = 5543140 /*0x5494e4*/;
    // 004d562b  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004d562d  e84eeaffff             -call 0x4d4080
    cpu.esp -= 4;
    sub_4d4080(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d5632  6a00                   -push 0
    app->getMemory<x86::reg32>(cpu.esp-4) = 0 /*0x0*/;
    cpu.esp -= 4;
    // 004d5634  b990438b00             -mov ecx, 0x8b4390
    cpu.ecx = 9126800 /*0x8b4390*/;
    // 004d5639  bb20000000             -mov ebx, 0x20
    cpu.ebx = 32 /*0x20*/;
    // 004d563e  baec945400             -mov edx, 0x5494ec
    cpu.edx = 5543148 /*0x5494ec*/;
    // 004d5643  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004d5645  e836eaffff             -call 0x4d4080
    cpu.esp -= 4;
    sub_4d4080(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d564a  6a00                   -push 0
    app->getMemory<x86::reg32>(cpu.esp-4) = 0 /*0x0*/;
    cpu.esp -= 4;
    // 004d564c  b9bc438b00             -mov ecx, 0x8b43bc
    cpu.ecx = 9126844 /*0x8b43bc*/;
    // 004d5651  bb20000000             -mov ebx, 0x20
    cpu.ebx = 32 /*0x20*/;
    // 004d5656  baf4945400             -mov edx, 0x5494f4
    cpu.edx = 5543156 /*0x5494f4*/;
    // 004d565b  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004d565d  e81eeaffff             -call 0x4d4080
    cpu.esp -= 4;
    sub_4d4080(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d5662  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 004d5664  7407                   -je 0x4d566d
    if (cpu.flags.zf)
    {
        goto L_0x004d566d;
    }
    // 004d5666  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004d5668  e823c20000             -call 0x4e1890
    cpu.esp -= 4;
    nfs3hp::ea::purgememadr(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x004d566d:
    // 004d566d  8a1de4478b00           -mov bl, byte ptr [0x8b47e4]
    cpu.bl = app->getMemory<x86::reg8>(x86::reg32(9127908) /* 0x8b47e4 */);
    // 004d5673  80cb08                 -or bl, 8
    cpu.bl |= x86::reg8(x86::sreg8(8 /*0x8*/));
    // 004d5676  8a0d94488b00           -mov cl, byte ptr [0x8b4894]
    cpu.cl = app->getMemory<x86::reg8>(x86::reg32(9128084) /* 0x8b4894 */);
    // 004d567c  881de4478b00           -mov byte ptr [0x8b47e4], bl
    app->getMemory<x86::reg8>(x86::reg32(9127908) /* 0x8b47e4 */) = cpu.bl;
    // 004d5682  8a3d68488b00           -mov bh, byte ptr [0x8b4868]
    cpu.bh = app->getMemory<x86::reg8>(x86::reg32(9128040) /* 0x8b4868 */);
    // 004d5688  80c908                 -or cl, 8
    cpu.cl |= x86::reg8(x86::sreg8(8 /*0x8*/));
    // 004d568b  80cf08                 -or bh, 8
    cpu.bh |= x86::reg8(x86::sreg8(8 /*0x8*/));
    // 004d568e  880d94488b00           -mov byte ptr [0x8b4894], cl
    app->getMemory<x86::reg8>(x86::reg32(9128084) /* 0x8b4894 */) = cpu.cl;
    // 004d5694  883d68488b00           -mov byte ptr [0x8b4868], bh
    app->getMemory<x86::reg8>(x86::reg32(9128040) /* 0x8b4868 */) = cpu.bh;
    // 004d569a  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004d569c  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d569d  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d569e  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d569f  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d56a0  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d56a1  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d56a2  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x90 */
void Application::sub_4d56b0(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004d56b0  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004d56b1  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004d56b3  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d56b4  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 0x8b 0xdb */
void Application::sub_4d56c0(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004d56c0  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004d56c1  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004d56c3  b8ffffffff             -mov eax, 0xffffffff
    cpu.eax = 4294967295 /*0xffffffff*/;
    // 004d56c8  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d56c9  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 */
void Application::sub_4d56d0(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004d56d0  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004d56d1  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004d56d3  b8ffffffff             -mov eax, 0xffffffff
    cpu.eax = 4294967295 /*0xffffffff*/;
    // 004d56d8  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d56d9  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 */
void Application::sub_4d56e0(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004d56e0  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004d56e1  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004d56e3  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d56e4  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 0x8b 0xdb */
void Application::sub_4d56f0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004d56f0  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004d56f1  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004d56f3  30e4                   -xor ah, ah
    cpu.ah ^= x86::reg8(x86::sreg8(cpu.ah));
    // 004d56f5  88258c3a5600           -mov byte ptr [0x563a8c], ah
    app->getMemory<x86::reg8>(x86::reg32(5651084) /* 0x563a8c */) = cpu.ah;
    // 004d56fb  e8d0dcfcff             -call 0x4a33d0
    cpu.esp -= 4;
    sub_4a33d0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d5700  e86bfcffff             -call 0x4d5370
    cpu.esp -= 4;
    sub_4d5370(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d5705  e8c6dcfcff             -call 0x4a33d0
    cpu.esp -= 4;
    sub_4a33d0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d570a  833d8ce8550000         -cmp dword ptr [0x55e88c], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5630092) /* 0x55e88c */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004d5711  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d5712  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x90 */
void Application::sub_4d5720(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004d5720  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004d5721  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004d5723  e868f3f5ff             -call 0x434a90
    cpu.esp -= 4;
    nfs3hp::collide::raceFrameEnd(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d5728  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d5729  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 */
void Application::sub_4d5730(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004d5730  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004d5731  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004d5733  e878ffffff             -call 0x4d56b0
    cpu.esp -= 4;
    sub_4d56b0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d5738  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d5739  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_4d5840: native, nfs3hp::port::draw2d::quadOutcodes */

/* align: skip 0x8b 0xc0 */
void Application::sub_4d5a80(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004d5a80  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004d5a81  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004d5a82  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004d5a83  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004d5a84  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004d5a86  83ec10                 -sub esp, 0x10
    (cpu.esp) -= x86::reg32(x86::sreg32(16 /*0x10*/));
    // 004d5a89  8945f0                 -mov dword ptr [ebp - 0x10], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = cpu.eax;
    // 004d5a8c  8955f8                 -mov dword ptr [ebp - 8], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.edx;
    // 004d5a8f  895dfc                 -mov dword ptr [ebp - 4], ebx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.ebx;
    // 004d5a92  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 004d5a94  8955f4                 -mov dword ptr [ebp - 0xc], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.edx;
L_0x004d5a97:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004d5a97  8b45f4                 -mov eax, dword ptr [ebp - 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 004d5a9a  3b45f0                 +cmp eax, dword ptr [ebp - 0x10]
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004d5a9d  0f8d94010000           -jge 0x4d5c37
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004d5c37;
    }
    // 004d5aa3  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004d5aa6  8b30                   -mov esi, dword ptr [eax]
    cpu.esi = app->getMemory<x86::reg32>(cpu.eax);
    // 004d5aa8  8b5df8                 -mov ebx, dword ptr [ebp - 8]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004d5aab  c1e605                 -shl esi, 5
    cpu.esi <<= 5 /*0x5*/ % 32;
    // 004d5aae  01de                   -add esi, ebx
    (cpu.esi) += x86::reg32(x86::sreg32(cpu.ebx));
    // 004d5ab0  8d7e14                 -lea edi, [esi + 0x14]
    cpu.edi = x86::reg32(cpu.esi + x86::reg32(20) /* 0x14 */);
    // 004d5ab3  8b460c                 -mov eax, dword ptr [esi + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 004d5ab6  8b0df8347d00           -mov ecx, dword ptr [0x7d34f8]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205560) /* 0x7d34f8 */);
    // 004d5abc  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004d5ac1  7558                   -jne 0x4d5b1b
    if (!cpu.flags.zf)
    {
        goto L_0x004d5b1b;
    }
    // 004d5ac3  39c8                   +cmp eax, ecx
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
    // 004d5ac5  7d54                   -jge 0x4d5b1b
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004d5b1b;
    }
    // 004d5ac7  8b4604                 -mov eax, dword ptr [esi + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 004d5aca  bb00000000             -mov ebx, 0
    cpu.ebx = 0 /*0x0*/;
    // 004d5acf  8b0d04357d00           -mov ecx, dword ptr [0x7d3504]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205572) /* 0x7d3504 */);
    // 004d5ad5  8b1500357d00           -mov edx, dword ptr [0x7d3500]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205568) /* 0x7d3500 */);
    // 004d5adb  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004d5ae0  750d                   -jne 0x4d5aef
    if (!cpu.flags.zf)
    {
        goto L_0x004d5aef;
    }
    // 004d5ae2  39c8                   +cmp eax, ecx
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
    // 004d5ae4  7c09                   -jl 0x4d5aef
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004d5aef;
    }
    // 004d5ae6  39d0                   +cmp eax, edx
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
    // 004d5ae8  7e09                   -jle 0x4d5af3
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004d5af3;
    }
    // 004d5aea  83cb04                 +or ebx, 4
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(4 /*0x4*/))));
    // 004d5aed  eb04                   -jmp 0x4d5af3
    goto L_0x004d5af3;
L_0x004d5aef:
    // 004d5aef  83cb08                 -or ebx, 8
    cpu.ebx |= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 004d5af2  90                     -nop 
    ;
L_0x004d5af3:
    // 004d5af3  8b06                   -mov eax, dword ptr [esi]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi);
    // 004d5af5  90                     -nop 
    ;
    // 004d5af6  8b0dfc347d00           -mov ecx, dword ptr [0x7d34fc]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205564) /* 0x7d34fc */);
    // 004d5afc  8b150c357d00           -mov edx, dword ptr [0x7d350c]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205580) /* 0x7d350c */);
    // 004d5b02  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004d5b07  750d                   -jne 0x4d5b16
    if (!cpu.flags.zf)
    {
        goto L_0x004d5b16;
    }
    // 004d5b09  39c8                   +cmp eax, ecx
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
    // 004d5b0b  7c09                   -jl 0x4d5b16
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004d5b16;
    }
    // 004d5b0d  39d0                   +cmp eax, edx
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
    // 004d5b0f  7e0f                   -jle 0x4d5b20
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004d5b20;
    }
    // 004d5b11  83cb02                 +or ebx, 2
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(2 /*0x2*/))));
    // 004d5b14  eb0a                   -jmp 0x4d5b20
    goto L_0x004d5b20;
L_0x004d5b16:
    // 004d5b16  83cb01                 +or ebx, 1
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(1 /*0x1*/))));
    // 004d5b19  eb05                   -jmp 0x4d5b20
    goto L_0x004d5b20;
L_0x004d5b1b:
    // 004d5b1b  bb10000000             -mov ebx, 0x10
    cpu.ebx = 16 /*0x10*/;
L_0x004d5b20:
    // 004d5b20  881f                   -mov byte ptr [edi], bl
    app->getMemory<x86::reg8>(cpu.edi) = cpu.bl;
    // 004d5b22  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004d5b25  8b7004                 -mov esi, dword ptr [eax + 4]
    cpu.esi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 004d5b28  8b7df8                 -mov edi, dword ptr [ebp - 8]
    cpu.edi = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004d5b2b  c1e605                 -shl esi, 5
    cpu.esi <<= 5 /*0x5*/ % 32;
    // 004d5b2e  01fe                   -add esi, edi
    (cpu.esi) += x86::reg32(x86::sreg32(cpu.edi));
    // 004d5b30  8d7e14                 -lea edi, [esi + 0x14]
    cpu.edi = x86::reg32(cpu.esi + x86::reg32(20) /* 0x14 */);
    // 004d5b33  8b460c                 -mov eax, dword ptr [esi + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 004d5b36  8b0df8347d00           -mov ecx, dword ptr [0x7d34f8]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205560) /* 0x7d34f8 */);
    // 004d5b3c  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004d5b41  7558                   -jne 0x4d5b9b
    if (!cpu.flags.zf)
    {
        goto L_0x004d5b9b;
    }
    // 004d5b43  39c8                   +cmp eax, ecx
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
    // 004d5b45  7d54                   -jge 0x4d5b9b
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004d5b9b;
    }
    // 004d5b47  8b4604                 -mov eax, dword ptr [esi + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 004d5b4a  bb00000000             -mov ebx, 0
    cpu.ebx = 0 /*0x0*/;
    // 004d5b4f  8b0d04357d00           -mov ecx, dword ptr [0x7d3504]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205572) /* 0x7d3504 */);
    // 004d5b55  8b1500357d00           -mov edx, dword ptr [0x7d3500]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205568) /* 0x7d3500 */);
    // 004d5b5b  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004d5b60  750d                   -jne 0x4d5b6f
    if (!cpu.flags.zf)
    {
        goto L_0x004d5b6f;
    }
    // 004d5b62  39c8                   +cmp eax, ecx
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
    // 004d5b64  7c09                   -jl 0x4d5b6f
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004d5b6f;
    }
    // 004d5b66  39d0                   +cmp eax, edx
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
    // 004d5b68  7e09                   -jle 0x4d5b73
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004d5b73;
    }
    // 004d5b6a  83cb04                 +or ebx, 4
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(4 /*0x4*/))));
    // 004d5b6d  eb04                   -jmp 0x4d5b73
    goto L_0x004d5b73;
L_0x004d5b6f:
    // 004d5b6f  83cb08                 -or ebx, 8
    cpu.ebx |= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 004d5b72  90                     -nop 
    ;
L_0x004d5b73:
    // 004d5b73  8b06                   -mov eax, dword ptr [esi]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi);
    // 004d5b75  90                     -nop 
    ;
    // 004d5b76  8b0dfc347d00           -mov ecx, dword ptr [0x7d34fc]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205564) /* 0x7d34fc */);
    // 004d5b7c  8b150c357d00           -mov edx, dword ptr [0x7d350c]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205580) /* 0x7d350c */);
    // 004d5b82  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004d5b87  750d                   -jne 0x4d5b96
    if (!cpu.flags.zf)
    {
        goto L_0x004d5b96;
    }
    // 004d5b89  39c8                   +cmp eax, ecx
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
    // 004d5b8b  7c09                   -jl 0x4d5b96
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004d5b96;
    }
    // 004d5b8d  39d0                   +cmp eax, edx
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
    // 004d5b8f  7e0f                   -jle 0x4d5ba0
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004d5ba0;
    }
    // 004d5b91  83cb02                 +or ebx, 2
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(2 /*0x2*/))));
    // 004d5b94  eb0a                   -jmp 0x4d5ba0
    goto L_0x004d5ba0;
L_0x004d5b96:
    // 004d5b96  83cb01                 +or ebx, 1
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(1 /*0x1*/))));
    // 004d5b99  eb05                   -jmp 0x4d5ba0
    goto L_0x004d5ba0;
L_0x004d5b9b:
    // 004d5b9b  bb10000000             -mov ebx, 0x10
    cpu.ebx = 16 /*0x10*/;
L_0x004d5ba0:
    // 004d5ba0  881f                   -mov byte ptr [edi], bl
    app->getMemory<x86::reg8>(cpu.edi) = cpu.bl;
    // 004d5ba2  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004d5ba5  8b7008                 -mov esi, dword ptr [eax + 8]
    cpu.esi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 004d5ba8  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004d5bab  c1e605                 -shl esi, 5
    cpu.esi <<= 5 /*0x5*/ % 32;
    // 004d5bae  01c6                   -add esi, eax
    (cpu.esi) += x86::reg32(x86::sreg32(cpu.eax));
    // 004d5bb0  8d7e14                 -lea edi, [esi + 0x14]
    cpu.edi = x86::reg32(cpu.esi + x86::reg32(20) /* 0x14 */);
    // 004d5bb3  8b460c                 -mov eax, dword ptr [esi + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 004d5bb6  8b0df8347d00           -mov ecx, dword ptr [0x7d34f8]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205560) /* 0x7d34f8 */);
    // 004d5bbc  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004d5bc1  7558                   -jne 0x4d5c1b
    if (!cpu.flags.zf)
    {
        goto L_0x004d5c1b;
    }
    // 004d5bc3  39c8                   +cmp eax, ecx
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
    // 004d5bc5  7d54                   -jge 0x4d5c1b
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004d5c1b;
    }
    // 004d5bc7  8b4604                 -mov eax, dword ptr [esi + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 004d5bca  bb00000000             -mov ebx, 0
    cpu.ebx = 0 /*0x0*/;
    // 004d5bcf  8b0d04357d00           -mov ecx, dword ptr [0x7d3504]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205572) /* 0x7d3504 */);
    // 004d5bd5  8b1500357d00           -mov edx, dword ptr [0x7d3500]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205568) /* 0x7d3500 */);
    // 004d5bdb  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004d5be0  750d                   -jne 0x4d5bef
    if (!cpu.flags.zf)
    {
        goto L_0x004d5bef;
    }
    // 004d5be2  39c8                   +cmp eax, ecx
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
    // 004d5be4  7c09                   -jl 0x4d5bef
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004d5bef;
    }
    // 004d5be6  39d0                   +cmp eax, edx
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
    // 004d5be8  7e09                   -jle 0x4d5bf3
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004d5bf3;
    }
    // 004d5bea  83cb04                 +or ebx, 4
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(4 /*0x4*/))));
    // 004d5bed  eb04                   -jmp 0x4d5bf3
    goto L_0x004d5bf3;
L_0x004d5bef:
    // 004d5bef  83cb08                 -or ebx, 8
    cpu.ebx |= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 004d5bf2  90                     -nop 
    ;
L_0x004d5bf3:
    // 004d5bf3  8b06                   -mov eax, dword ptr [esi]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi);
    // 004d5bf5  90                     -nop 
    ;
    // 004d5bf6  8b0dfc347d00           -mov ecx, dword ptr [0x7d34fc]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205564) /* 0x7d34fc */);
    // 004d5bfc  8b150c357d00           -mov edx, dword ptr [0x7d350c]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205580) /* 0x7d350c */);
    // 004d5c02  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004d5c07  750d                   -jne 0x4d5c16
    if (!cpu.flags.zf)
    {
        goto L_0x004d5c16;
    }
    // 004d5c09  39c8                   +cmp eax, ecx
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
    // 004d5c0b  7c09                   -jl 0x4d5c16
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004d5c16;
    }
    // 004d5c0d  39d0                   +cmp eax, edx
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
    // 004d5c0f  7e0f                   -jle 0x4d5c20
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004d5c20;
    }
    // 004d5c11  83cb02                 +or ebx, 2
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(2 /*0x2*/))));
    // 004d5c14  eb0a                   -jmp 0x4d5c20
    goto L_0x004d5c20;
L_0x004d5c16:
    // 004d5c16  83cb01                 +or ebx, 1
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(1 /*0x1*/))));
    // 004d5c19  eb05                   -jmp 0x4d5c20
    goto L_0x004d5c20;
L_0x004d5c1b:
    // 004d5c1b  bb10000000             -mov ebx, 0x10
    cpu.ebx = 16 /*0x10*/;
L_0x004d5c20:
    // 004d5c20  881f                   -mov byte ptr [edi], bl
    app->getMemory<x86::reg8>(cpu.edi) = cpu.bl;
    // 004d5c22  8b55f4                 -mov edx, dword ptr [ebp - 0xc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 004d5c25  8b4dfc                 -mov ecx, dword ptr [ebp - 4]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004d5c28  42                     -inc edx
    (cpu.edx)++;
    // 004d5c29  83c10c                 +add ecx, 0xc
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
    // 004d5c2c  8955f4                 -mov dword ptr [ebp - 0xc], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.edx;
    // 004d5c2f  894dfc                 -mov dword ptr [ebp - 4], ecx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.ecx;
    // 004d5c32  e960feffff             -jmp 0x4d5a97
    goto L_0x004d5a97;
L_0x004d5c37:
    // 004d5c37  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004d5c39  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d5c3a  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d5c3b  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d5c3c  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d5c3d  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_4d5c40: native, nfs3hp::port::shapes::resetTextures */

/* sub_4d5c90: native, nfs3hp::graphics::clearWithDepth */

/* sub_4d5cc0: native, nfs3hp::graphics::beginDrawing */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x90 */
void Application::sub_4d5d10(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004d5d10  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004d5d11  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004d5d12  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004d5d14  833d303b560000         +cmp dword ptr [0x563b30], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5651248) /* 0x563b30 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004d5d1b  7408                   -je 0x4d5d25
    if (cpu.flags.zf)
    {
        goto L_0x004d5d25;
    }
    // 004d5d1d  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 004d5d1f  890d303b5600           -mov dword ptr [0x563b30], ecx
    app->getMemory<x86::reg32>(x86::reg32(5651248) /* 0x563b30 */) = cpu.ecx;
L_0x004d5d25:
    // 004d5d25  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d5d26  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d5d27  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_4d5d30: native, nfs3hp::graphics::clearBothBuffers */

/* sub_4d5d70: native, nfs3hp::graphics::clearBothBuffersAndReset */

/* sub_4d5db0: native, nfs3hp::port::shapes::shapeByName */

/* sub_4d5e40: native, nfs3hp::port::fields::sliderShape */

/* sub_4d5ed0: native, nfs3hp::graphics::shapeIntoTexture */

/* sub_4d5f40: native, nfs3hp::graphics::makeArtTexture */

/* sub_4d6070: native, nfs3hp::port::shapes::shapeTexture */

/* sub_4d6110: native, nfs3hp::port::shapes::cutTile */

/* sub_4d6190: native, nfs3hp::port::shapes::shape565To1555 */

/* sub_4d6210: native, nfs3hp::port::shapes::tileRoom */

/* sub_4d6390: native, nfs3hp::port::shapes::artShapeTextures */

}
