#include "nfs3hp.h"
#include <lib/thread.h>

namespace nfs3hp
{

/* sub_52a144: native, nfs3hp::snd::xaStereoIntroSetup */

/* sub_52a1a0: native, nfs3hp::snd::xaStereoStreamDecode */

/* sub_52a354: native, nfs3hp::snd::xaStereoStreamSetup */

/* sub_52a3a0: native, nfs3hp::snd::xaStereoPacketDecode */

/* sub_52a5b4: native, nfs3hp::snd::xaStereoFileSetup */

/* sub_52a610: native, nfs3hp::snd::framesPlayedCoded */

/* sub_52a618: native, nfs3hp::snd::codedToWords */

/* sub_52a668: native, nfs3hp::snd::codedDecode */

/* sub_52a790: native, nfs3hp::snd::codedSetup */

/* sub_52a7e0: native, nfs3hp::snd::codedStreamDecode */

/* sub_52a970: native, nfs3hp::snd::codedStreamSetup */

/* sub_52a9c0: native, nfs3hp::snd::codedPacketDecode */

/* sub_52ab70: native, nfs3hp::snd::codedPacketSetup */

/* sub_52abd0: native, nfs3hp::snd::dead_0x52abd0 */

/* sub_52abd8: native, nfs3hp::snd::dead_0x52abd8 */

/* sub_52abf8: native, nfs3hp::snd::dead_0x52abf8 */

/* sub_52ad28: native, nfs3hp::snd::dead_0x52ad28 */

/* sub_52ad70: native, nfs3hp::snd::dead_0x52ad70 */

/* sub_52af30: native, nfs3hp::snd::dead_0x52af30 */

/* sub_52af80: native, nfs3hp::snd::dead_0x52af80 */

/* sub_52b160: native, nfs3hp::snd::dead_0x52b160 */

/* sub_52b1c0: native, nfs3hp::snd::panLaw */

/* sub_52b230: native, nfs3hp::snd::readBigEndian */

/* sub_52b290: native, nfs3hp::watcom::putch */

/* sub_52b300: native, nfs3hp::snd::dead_0x52b300 */

/* sub_52b4d0: native, nfs3hp::snd::dead_0x52b4d0 */

/* sub_52b500: native, nfs3hp::snd::setSendLevel */

/* align: skip  */
void Application::sub_52b523(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0052b523  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 0052b524  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 0052b526  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 0052b527  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 0052b528  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 0052b529  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 0052b52a  83ec08                 -sub esp, 8
    (cpu.esp) -= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 0052b52d  8a6518                 -mov ah, byte ptr [ebp + 0x18]
    cpu.ah = app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(24) /* 0x18 */);
    // 0052b530  80fc01                 +cmp ah, 1
    {
        x86::reg8 tmp1 = cpu.ah;
        x86::reg8 tmp2 = x86::reg8(x86::sreg8(1 /*0x1*/));
        x86::reg8 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 7);
        cpu.flags.of ^= 1 & (result >> 7);
        cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
        cpu.set_szp(result);
    }
    // 0052b533  772f                   -ja 0x52b564
    if (!cpu.flags.cf && !cpu.flags.zf)
    {
        goto L_0x0052b564;
    }
    // 0052b535  84e4                   +test ah, ah
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.ah & cpu.ah));
    // 0052b537  7524                   -jne 0x52b55d
    if (!cpu.flags.zf)
    {
        goto L_0x0052b55d;
    }
    // 0052b539  d9ee                   +fldz 
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = 0.0;
    // 0052b53b  dc5d10                 +fcomp qword ptr [ebp + 0x10]
    cpu.fpu.compare(fpu1, x86::Float(app->getMemory<double>(cpu.ebp + x86::reg32(16) /* 0x10 */)));
    // 0052b53e  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 0052b540  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 0052b541  730a                   -jae 0x52b54d
    if (!cpu.flags.cf)
    {
        goto L_0x0052b54d;
    }
    // 0052b543  31c9                   +xor ecx, ecx
    cpu.clear_co();
    cpu.set_szp((cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx))));
    // 0052b545  894de8                 -mov dword ptr [ebp - 0x18], ecx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-24) /* -0x18 */) = cpu.ecx;
    // 0052b548  894dec                 -mov dword ptr [ebp - 0x14], ecx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */) = cpu.ecx;
    // 0052b54b  eb4f                   -jmp 0x52b59c
    goto L_0x0052b59c;
L_0x0052b54d:
    // 0052b54d  7607                   -jbe 0x52b556
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x0052b556;
    }
    // 0052b54f  b847800000             -mov eax, 0x8047
    cpu.eax = 32839 /*0x8047*/;
    // 0052b554  eb38                   -jmp 0x52b58e
    goto L_0x0052b58e;
L_0x0052b556:
    // 0052b556  b847400000             -mov eax, 0x4047
    cpu.eax = 16455 /*0x4047*/;
    // 0052b55b  eb31                   -jmp 0x52b58e
    goto L_0x0052b58e;
L_0x0052b55d:
    // 0052b55d  b847200000             -mov eax, 0x2047
    cpu.eax = 8263 /*0x2047*/;
    // 0052b562  eb2a                   -jmp 0x52b58e
    goto L_0x0052b58e;
L_0x0052b564:
    // 0052b564  d9ee                   +fldz 
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu2 = 0.0;
    // 0052b566  dc5d10                 +fcomp qword ptr [ebp + 0x10]
    cpu.fpu.compare(fpu2, x86::Float(app->getMemory<double>(cpu.ebp + x86::reg32(16) /* 0x10 */)));
    // 0052b569  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 0052b56b  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 0052b56c  720a                   -jb 0x52b578
    if (cpu.flags.cf)
    {
        goto L_0x0052b578;
    }
    // 0052b56e  31d2                   +xor edx, edx
    cpu.clear_co();
    cpu.set_szp((cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx))));
    // 0052b570  8955e8                 -mov dword ptr [ebp - 0x18], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-24) /* -0x18 */) = cpu.edx;
    // 0052b573  8955ec                 -mov dword ptr [ebp - 0x14], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */) = cpu.edx;
    // 0052b576  eb24                   -jmp 0x52b59c
    goto L_0x0052b59c;
L_0x0052b578:
    // 0052b578  d9ee                   +fldz 
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu3 = 0.0;
    // 0052b57a  dc5d08                 +fcomp qword ptr [ebp + 8]
    cpu.fpu.compare(fpu3, x86::Float(app->getMemory<double>(cpu.ebp + x86::reg32(8) /* 0x8 */)));
    // 0052b57d  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 0052b57f  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 0052b580  7307                   -jae 0x52b589
    if (!cpu.flags.cf)
    {
        goto L_0x0052b589;
    }
    // 0052b582  b807810000             -mov eax, 0x8107
    cpu.eax = 33031 /*0x8107*/;
    // 0052b587  eb05                   -jmp 0x52b58e
    goto L_0x0052b58e;
L_0x0052b589:
    // 0052b589  b807110000             -mov eax, 0x1107
    cpu.eax = 4359 /*0x1107*/;
L_0x0052b58e:
    // 0052b58e  8d5d10                 -lea ebx, [ebp + 0x10]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(16) /* 0x10 */);
    // 0052b591  8d5508                 -lea edx, [ebp + 8]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(8) /* 0x8 */);
    // 0052b594  e8188effff             -call 0x5243b1
    cpu.esp -= 4;
    nfs3hp::watcom::reportError(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052b599  dd5de8                 -fstp qword ptr [ebp - 0x18]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu4 = cpu.fpu.st(0);
    app->getMemory<double>(cpu.ebp + x86::reg32(-24) /* -0x18 */) = double(fpu4);
    cpu.fpu.count -= 1;
    }
L_0x0052b59c:
    // 0052b59c  dd45e8                 -fld qword ptr [ebp - 0x18]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu5 = x86::Float(app->getMemory<double>(cpu.ebp + x86::reg32(-24) /* -0x18 */));
    // 0052b59f  8d65f0                 -lea esp, [ebp - 0x10]
    cpu.esp = x86::reg32(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 0052b5a2  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052b5a3  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052b5a4  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052b5a5  58                     -pop eax
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052b5a6  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    cpu.fpu.count += 1;
    cpu.fpu.st(0) = fpu5;
    }
    // 0052b5a7  c21400                 -ret 0x14
    cpu.esp += 4+20 /*0x14*/;
    return;
}

/* sub_52b5b0: native, nfs3hp::watcom::mbclen */

/* sub_52b5e0: native, nfs3hp::watcom::mbcicmp */

/* sub_52b640: native, nfs3hp::watcom::startHook */

/* align: skip  */
void Application::sub_52b641(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0052b641  a36cb15600             -mov dword ptr [0x56b16c], eax
    app->getMemory<x86::reg32>(x86::reg32(5681516) /* 0x56b16c */) = cpu.eax;
    // 0052b646  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_52b647: native, nfs3hp::watcom::printMathError */

/* sub_52b68f: native, nfs3hp::watcom::callMatherr */

/* align: skip 0x00 0x00 */
void Application::sub_52b6c0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0052b6c0  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 0052b6c1  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 0052b6c2  8b7c240c               -mov edi, dword ptr [esp + 0xc]
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(12) /* 0xc */);
    // 0052b6c6  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 0052b6c8  7c3b                   -jl 0x52b705
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x0052b705;
    }
L_0x0052b6ca:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 0052b6ca  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    // 0052b6cc  7c3b                   -jl 0x52b709
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x0052b709;
    }
L_0x0052b6ce:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 0052b6ce  8b7004                 -mov esi, dword ptr [eax + 4]
    cpu.esi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 0052b6d1  39f2                   +cmp edx, esi
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.esi));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0052b6d3  7e02                   -jle 0x52b6d7
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x0052b6d7;
    }
    // 0052b6d5  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
L_0x0052b6d7:
    // 0052b6d7  39f1                   +cmp ecx, esi
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
    // 0052b6d9  7e02                   -jle 0x52b6dd
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x0052b6dd;
    }
    // 0052b6db  89f1                   -mov ecx, esi
    cpu.ecx = cpu.esi;
L_0x0052b6dd:
    // 0052b6dd  85db                   +test ebx, ebx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & cpu.ebx));
    // 0052b6df  7c2c                   -jl 0x52b70d
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x0052b70d;
    }
L_0x0052b6e1:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 0052b6e1  85ff                   +test edi, edi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edi & cpu.edi));
    // 0052b6e3  7c2c                   -jl 0x52b711
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x0052b711;
    }
L_0x0052b6e5:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 0052b6e5  8b7008                 -mov esi, dword ptr [eax + 8]
    cpu.esi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 0052b6e8  39f3                   +cmp ebx, esi
    {
        x86::reg32 tmp1 = cpu.ebx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.esi));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0052b6ea  7e02                   -jle 0x52b6ee
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x0052b6ee;
    }
    // 0052b6ec  89f3                   -mov ebx, esi
    cpu.ebx = cpu.esi;
L_0x0052b6ee:
    // 0052b6ee  39f7                   +cmp edi, esi
    {
        x86::reg32 tmp1 = cpu.edi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.esi));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0052b6f0  7e02                   -jle 0x52b6f4
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x0052b6f4;
    }
    // 0052b6f2  89f7                   -mov edi, esi
    cpu.edi = cpu.esi;
L_0x0052b6f4:
    // 0052b6f4  894814                 -mov dword ptr [eax + 0x14], ecx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */) = cpu.ecx;
    // 0052b6f7  895810                 -mov dword ptr [eax + 0x10], ebx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(16) /* 0x10 */) = cpu.ebx;
    // 0052b6fa  897818                 -mov dword ptr [eax + 0x18], edi
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */) = cpu.edi;
    // 0052b6fd  89500c                 -mov dword ptr [eax + 0xc], edx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */) = cpu.edx;
    // 0052b700  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052b701  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052b702  c20400                 -ret 4
    cpu.esp += 4+4 /*0x4*/;
    return;
L_0x0052b705:
    // 0052b705  31d2                   +xor edx, edx
    cpu.clear_co();
    cpu.set_szp((cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx))));
    // 0052b707  ebc1                   -jmp 0x52b6ca
    goto L_0x0052b6ca;
L_0x0052b709:
    // 0052b709  31c9                   +xor ecx, ecx
    cpu.clear_co();
    cpu.set_szp((cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx))));
    // 0052b70b  ebc1                   -jmp 0x52b6ce
    goto L_0x0052b6ce;
L_0x0052b70d:
    // 0052b70d  31db                   +xor ebx, ebx
    cpu.clear_co();
    cpu.set_szp((cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx))));
    // 0052b70f  ebd0                   -jmp 0x52b6e1
    goto L_0x0052b6e1;
L_0x0052b711:
    // 0052b711  31ff                   +xor edi, edi
    cpu.clear_co();
    cpu.set_szp((cpu.edi ^= x86::reg32(x86::sreg32(cpu.edi))));
    // 0052b713  ebd0                   -jmp 0x52b6e5
    goto L_0x0052b6e5;
}

/* align: skip 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 */
void Application::sub_52b720(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0052b720  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 0052b721  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 0052b722  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 0052b723  83ec0c                 -sub esp, 0xc
    (cpu.esp) -= x86::reg32(x86::sreg32(12 /*0xc*/));
    // 0052b726  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 0052b728  89d7                   -mov edi, edx
    cpu.edi = cpu.edx;
    // 0052b72a  895c2408               -mov dword ptr [esp + 8], ebx
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(8) /* 0x8 */) = cpu.ebx;
    // 0052b72e  89cd                   -mov ebp, ecx
    cpu.ebp = cpu.ecx;
    // 0052b730  39d8                   +cmp eax, ebx
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
    // 0052b732  0f8f84000000           -jg 0x52b7bc
    if (!cpu.flags.zf && (cpu.flags.sf == cpu.flags.of))
    {
        goto L_0x0052b7bc;
    }
L_0x0052b738:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 0052b738  39fd                   +cmp ebp, edi
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
    // 0052b73a  7d06                   -jge 0x52b742
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x0052b742;
    }
    // 0052b73c  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 0052b73e  89ef                   -mov edi, ebp
    cpu.edi = cpu.ebp;
    // 0052b740  89c5                   -mov ebp, eax
    cpu.ebp = cpu.eax;
L_0x0052b742:
    // 0052b742  8b442408               -mov eax, dword ptr [esp + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(8) /* 0x8 */);
    // 0052b746  29f0                   -sub eax, esi
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.esi));
    // 0052b748  8b4c241c               -mov ecx, dword ptr [esp + 0x1c]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(28) /* 0x1c */);
    // 0052b74c  40                     -inc eax
    (cpu.eax)++;
    // 0052b74d  89fa                   -mov edx, edi
    cpu.edx = cpu.edi;
    // 0052b74f  890424                 -mov dword ptr [esp], eax
    app->getMemory<x86::reg32>(cpu.esp) = cpu.eax;
    // 0052b752  89e8                   -mov eax, ebp
    cpu.eax = cpu.ebp;
    // 0052b754  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 0052b755  29f8                   -sub eax, edi
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edi));
    // 0052b757  b901000000             -mov ecx, 1
    cpu.ecx = 1 /*0x1*/;
    // 0052b75c  48                     -dec eax
    (cpu.eax)--;
    // 0052b75d  8b5c2404               -mov ebx, dword ptr [esp + 4]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(4) /* 0x4 */);
    // 0052b761  89442408               -mov dword ptr [esp + 8], eax
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(8) /* 0x8 */) = cpu.eax;
    // 0052b765  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 0052b767  47                     -inc edi
    (cpu.edi)++;
    // 0052b768  e8d31dfdff             -call 0x4fd540
    cpu.esp -= 4;
    sub_4fd540(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052b76d  8b5c241c               -mov ebx, dword ptr [esp + 0x1c]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(28) /* 0x1c */);
    // 0052b771  8b4c2404               -mov ecx, dword ptr [esp + 4]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(4) /* 0x4 */);
    // 0052b775  8b442408               -mov eax, dword ptr [esp + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(8) /* 0x8 */);
    // 0052b779  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 0052b77a  89fa                   -mov edx, edi
    cpu.edx = cpu.edi;
    // 0052b77c  bb01000000             -mov ebx, 1
    cpu.ebx = 1 /*0x1*/;
    // 0052b781  e8ba1dfdff             -call 0x4fd540
    cpu.esp -= 4;
    sub_4fd540(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052b786  8b44241c               -mov eax, dword ptr [esp + 0x1c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(28) /* 0x1c */);
    // 0052b78a  8b4c2404               -mov ecx, dword ptr [esp + 4]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(4) /* 0x4 */);
    // 0052b78e  bb01000000             -mov ebx, 1
    cpu.ebx = 1 /*0x1*/;
    // 0052b793  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 0052b794  89fa                   -mov edx, edi
    cpu.edx = cpu.edi;
    // 0052b796  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 0052b798  e8a31dfdff             -call 0x4fd540
    cpu.esp -= 4;
    sub_4fd540(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052b79d  8b54241c               -mov edx, dword ptr [esp + 0x1c]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(28) /* 0x1c */);
    // 0052b7a1  b901000000             -mov ecx, 1
    cpu.ecx = 1 /*0x1*/;
    // 0052b7a6  8b1c24                 -mov ebx, dword ptr [esp]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    // 0052b7a9  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 0052b7aa  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 0052b7ac  89ea                   -mov edx, ebp
    cpu.edx = cpu.ebp;
    // 0052b7ae  e88d1dfdff             -call 0x4fd540
    cpu.esp -= 4;
    sub_4fd540(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052b7b3  83c40c                 +add esp, 0xc
    {
        x86::reg32& tmp1 = cpu.esp;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(12 /*0xc*/));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 0052b7b6  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052b7b7  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052b7b8  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052b7b9  c20400                 -ret 4
    cpu.esp += 4+4 /*0x4*/;
    return;
L_0x0052b7bc:
    // 0052b7bc  89de                   -mov esi, ebx
    cpu.esi = cpu.ebx;
    // 0052b7be  89442408               -mov dword ptr [esp + 8], eax
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(8) /* 0x8 */) = cpu.eax;
    // 0052b7c2  e971ffffff             -jmp 0x52b738
    goto L_0x0052b738;
}

/* align: skip 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 */
void Application::sub_52b7d0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0052b7d0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 0052b7d1  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 0052b7d2  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 0052b7d3  81ec04010000           -sub esp, 0x104
    (cpu.esp) -= x86::reg32(x86::sreg32(260 /*0x104*/));
    // 0052b7d9  813d9472560080b55000   +cmp dword ptr [0x567294], 0x50b580
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5665428) /* 0x567294 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(5289344 /*0x50b580*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0052b7e3  7444                   -je 0x52b829
    if (cpu.flags.zf)
    {
        goto L_0x0052b829;
    }
L_0x0052b7e5:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 0052b7e5  8d84241c010000         -lea eax, [esp + 0x11c]
    cpu.eax = x86::reg32(cpu.esp + x86::reg32(284) /* 0x11c */);
    // 0052b7ec  8d9c2400010000         -lea ebx, [esp + 0x100]
    cpu.ebx = x86::reg32(cpu.esp + x86::reg32(256) /* 0x100 */);
    // 0052b7f3  8b942418010000         -mov edx, dword ptr [esp + 0x118]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(280) /* 0x118 */);
    // 0052b7fa  89842400010000         -mov dword ptr [esp + 0x100], eax
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(256) /* 0x100 */) = cpu.eax;
    // 0052b801  89e0                   -mov eax, esp
    cpu.eax = cpu.esp;
    // 0052b803  e86c3efbff             -call 0x4df674
    cpu.esp -= 4;
    nfs3hp::watcom::vsprintf(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052b808  8b942414010000         -mov edx, dword ptr [esp + 0x114]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(276) /* 0x114 */);
    // 0052b80f  89e0                   -mov eax, esp
    cpu.eax = cpu.esp;
    // 0052b811  31ff                   -xor edi, edi
    cpu.edi ^= x86::reg32(x86::sreg32(cpu.edi));
    // 0052b813  e848000000             -call 0x52b860
    cpu.esp -= 4;
    sub_52b860(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052b818  89bc2400010000         -mov dword ptr [esp + 0x100], edi
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(256) /* 0x100 */) = cpu.edi;
    // 0052b81f  81c404010000           -add esp, 0x104
    (cpu.esp) += x86::reg32(x86::sreg32(260 /*0x104*/));
    // 0052b825  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052b826  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052b827  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052b828  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x0052b829:
    // 0052b829  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 0052b82a  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 0052b82b  b9f41f5500             -mov ecx, 0x551ff4
    cpu.ecx = 5578740 /*0x551ff4*/;
    // 0052b830  bb04205500             -mov ebx, 0x552004
    cpu.ebx = 5578756 /*0x552004*/;
    // 0052b835  be3c000000             -mov esi, 0x3c
    cpu.esi = 60 /*0x3c*/;
    // 0052b83a  6810205500             -push 0x552010
    app->getMemory<x86::reg32>(cpu.esp-4) = 5578768 /*0x552010*/;
    cpu.esp -= 4;
    // 0052b83f  890d90215500           -mov dword ptr [0x552190], ecx
    app->getMemory<x86::reg32>(x86::reg32(5579152) /* 0x552190 */) = cpu.ecx;
    // 0052b845  891d94215500           -mov dword ptr [0x552194], ebx
    app->getMemory<x86::reg32>(x86::reg32(5579156) /* 0x552194 */) = cpu.ebx;
    // 0052b84b  893598215500           -mov dword ptr [0x552198], esi
    app->getMemory<x86::reg32>(x86::reg32(5579160) /* 0x552198 */) = cpu.esi;
    // 0052b851  e8ba57edff             -call 0x401010
    cpu.esp -= 4;
    nfs3hp::Error(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052b856  83c404                 +add esp, 4
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
    // 0052b859  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052b85a  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052b85b  eb88                   -jmp 0x52b7e5
    goto L_0x0052b7e5;
}

/* align: skip 0x8d 0x40 0x00 */
void Application::sub_52b860(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0052b860  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 0052b861  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 0052b862  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 0052b863  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 0052b864  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 0052b866  89d3                   -mov ebx, edx
    cpu.ebx = cpu.edx;
    // 0052b868  e88346fcff             -call 0x4efef0
    cpu.esp -= 4;
    sub_4efef0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052b86d  8b1584435600           -mov edx, dword ptr [0x564384]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5653380) /* 0x564384 */);
    // 0052b873  29c2                   -sub edx, eax
    (cpu.edx) -= x86::reg32(x86::sreg32(cpu.eax));
    // 0052b875  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 0052b877  c1fa1f                 -sar edx, 0x1f
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (31 /*0x1f*/ % 32));
    // 0052b87a  2bc2                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 0052b87c  d1f8                   -sar eax, 1
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (1 /*0x1*/ % 32));
    // 0052b87e  8b3df8715600           -mov edi, dword ptr [0x5671f8]
    cpu.edi = app->getMemory<x86::reg32>(x86::reg32(5665272) /* 0x5671f8 */);
    // 0052b884  89da                   -mov edx, ebx
    cpu.edx = cpu.ebx;
    // 0052b886  8b35fc715600           -mov esi, dword ptr [0x5671fc]
    cpu.esi = app->getMemory<x86::reg32>(x86::reg32(5665276) /* 0x5671fc */);
    // 0052b88c  e8bf4ffcff             -call 0x4f0850
    cpu.esp -= 4;
    sub_4f0850(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052b891  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 0052b893  e8b842fcff             -call 0x4efb50
    cpu.esp -= 4;
    sub_4efb50(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052b898  893df8715600           -mov dword ptr [0x5671f8], edi
    app->getMemory<x86::reg32>(x86::reg32(5665272) /* 0x5671f8 */) = cpu.edi;
    // 0052b89e  8935fc715600           -mov dword ptr [0x5671fc], esi
    app->getMemory<x86::reg32>(x86::reg32(5665276) /* 0x5671fc */) = cpu.esi;
    // 0052b8a4  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052b8a5  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052b8a6  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052b8a7  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052b8a8  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x00 0x00 0x00 0x00 0x00 0x00 0x00 */
void Application::sub_52b8b0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0052b8b0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 0052b8b1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 0052b8b2  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 0052b8b3  8b5008                 -mov edx, dword ptr [eax + 8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 0052b8b6  8b4804                 -mov ecx, dword ptr [eax + 4]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 0052b8b9  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 0052b8ba  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
    // 0052b8bc  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 0052b8be  e8fdfdffff             -call 0x52b6c0
    cpu.esp -= 4;
    sub_52b6c0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052b8c3  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052b8c4  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052b8c5  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052b8c6  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 */
void Application::sub_52b8d0(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0052b8d0  b870b15600             -mov eax, 0x56b170
    cpu.eax = 5681520 /*0x56b170*/;
    // 0052b8d5  e946bdf6ff             -jmp 0x497620
    return sub_497620(app, cpu.handOver());
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 */
void Application::sub_52b8e0(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0052b8e0  e83bf4fbff             -call 0x4ead20
    cpu.esp -= 4;
    sub_4ead20(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052b8e5  e9362b0000             -jmp 0x52e420
    return sub_52e420(app, cpu.handOver());
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 */
void Application::sub_52b8f0(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0052b8f0  e99bf4fbff             -jmp 0x4ead90
    return sub_4ead90(app, cpu.handOver());
}

/* align: skip 0x8d 0x44 0x20 0x00 */
void Application::sub_52b910(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
  goto start;
dynamic_jump:
  switch(cpu.ip)
  {
start:
    // 0052b910  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 0052b911  83f804                 +cmp eax, 4
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
    // 0052b914  7707                   -ja 0x52b91d
    if (!cpu.flags.cf && !cpu.flags.zf)
    {
        goto L_0x0052b91d;
    }
    // 0052b916  ff2485f8b85200         -jmp dword ptr [eax*4 + 0x52b8f8]
    cpu.ip = app->getMemory<x86::reg32>(5421304 + cpu.eax * 4); goto dynamic_jump;
  case 0x0052b91d:
L_0x0052b91d:
    // 0052b91d  a1f84f5600             -mov eax, dword ptr [0x564ff8]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5656568) /* 0x564ff8 */);
    // 0052b922  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 0052b924  c1fa1f                 -sar edx, 0x1f
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (31 /*0x1f*/ % 32));
    // 0052b927  c1e203                 +shl edx, 3
    {
        x86::reg8 tmp = 3 /*0x3*/ % 32;
        x86::reg32& op = cpu.edx;
        if (tmp)
        {
            cpu.flags.cf = 1 & (op >> (32 - tmp));
            cpu.set_szp((op <<= tmp));
            if (tmp == 1) cpu.flags.of = (cpu.flags.cf != (1 & (op >> (32 - 1))));
        }
    }
    // 0052b92a  1bc2                   -sbb eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx) + cpu.flags.cf);
    // 0052b92c  c1f803                 -sar eax, 3
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (3 /*0x3*/ % 32));
    // 0052b92f  99                     -cdq 
    cpu.edx_eax = x86::reg64(static_cast<x86::sreg32>(cpu.eax));
    // 0052b930  31d0                   -xor eax, edx
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.edx));
    // 0052b932  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 0052b934  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052b935  c3                     -ret 
    cpu.esp += 4;
    return;
  case 0x0052b936:
    // 0052b936  a1fc4f5600             -mov eax, dword ptr [0x564ffc]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5656572) /* 0x564ffc */);
    // 0052b93b  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 0052b93d  c1fa1f                 -sar edx, 0x1f
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (31 /*0x1f*/ % 32));
    // 0052b940  c1e203                 +shl edx, 3
    {
        x86::reg8 tmp = 3 /*0x3*/ % 32;
        x86::reg32& op = cpu.edx;
        if (tmp)
        {
            cpu.flags.cf = 1 & (op >> (32 - tmp));
            cpu.set_szp((op <<= tmp));
            if (tmp == 1) cpu.flags.of = (cpu.flags.cf != (1 & (op >> (32 - 1))));
        }
    }
    // 0052b943  1bc2                   -sbb eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx) + cpu.flags.cf);
    // 0052b945  c1f803                 -sar eax, 3
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (3 /*0x3*/ % 32));
    // 0052b948  99                     -cdq 
    cpu.edx_eax = x86::reg64(static_cast<x86::sreg32>(cpu.eax));
    // 0052b949  31d0                   -xor eax, edx
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.edx));
    // 0052b94b  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 0052b94d  48                     -dec eax
    (cpu.eax)--;
    // 0052b94e  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052b94f  c3                     -ret 
    cpu.esp += 4;
    return;
  case 0x0052b950:
    // 0052b950  a1f84f5600             -mov eax, dword ptr [0x564ff8]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5656568) /* 0x564ff8 */);
    // 0052b955  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052b956  c3                     -ret 
    cpu.esp += 4;
    return;
  case 0x0052b957:
    // 0052b957  a1fc4f5600             -mov eax, dword ptr [0x564ffc]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5656572) /* 0x564ffc */);
    // 0052b95c  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052b95d  c3                     -ret 
    cpu.esp += 4;
    return;
  case 0x0052b95e:
    // 0052b95e  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 0052b963  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052b964  c3                     -ret 
    cpu.esp += 4;
    return;
  default:
    NFS2_ASSERT(false);
  }
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 0x8b 0xdb */
void Application::sub_52b970(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0052b970  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 0052b971  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 0052b972  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 0052b973  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 0052b974  81ec04010000           -sub esp, 0x104
    (cpu.esp) -= x86::reg32(x86::sreg32(260 /*0x104*/));
    // 0052b97a  8bb4241c010000         -mov esi, dword ptr [esp + 0x11c]
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(284) /* 0x11c */);
    // 0052b981  8b8c2418010000         -mov ecx, dword ptr [esp + 0x118]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(280) /* 0x118 */);
    // 0052b988  8d842424010000         -lea eax, [esp + 0x124]
    cpu.eax = x86::reg32(cpu.esp + x86::reg32(292) /* 0x124 */);
    // 0052b98f  8d9c2400010000         -lea ebx, [esp + 0x100]
    cpu.ebx = x86::reg32(cpu.esp + x86::reg32(256) /* 0x100 */);
    // 0052b996  8b942420010000         -mov edx, dword ptr [esp + 0x120]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(288) /* 0x120 */);
    // 0052b99d  c1e603                 -shl esi, 3
    cpu.esi <<= 3 /*0x3*/ % 32;
    // 0052b9a0  89842400010000         -mov dword ptr [esp + 0x100], eax
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(256) /* 0x100 */) = cpu.eax;
    // 0052b9a7  89e0                   -mov eax, esp
    cpu.eax = cpu.esp;
    // 0052b9a9  c1e103                 -shl ecx, 3
    cpu.ecx <<= 3 /*0x3*/ % 32;
    // 0052b9ac  e8c33cfbff             -call 0x4df674
    cpu.esp -= 4;
    nfs3hp::watcom::vsprintf(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052b9b1  89e0                   -mov eax, esp
    cpu.eax = cpu.esp;
    // 0052b9b3  89f3                   -mov ebx, esi
    cpu.ebx = cpu.esi;
    // 0052b9b5  89ca                   -mov edx, ecx
    cpu.edx = cpu.ecx;
    // 0052b9b7  e8242b0000             -call 0x52e4e0
    cpu.esp -= 4;
    sub_52e4e0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052b9bc  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 0052b9be  89942400010000         -mov dword ptr [esp + 0x100], edx
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(256) /* 0x100 */) = cpu.edx;
    // 0052b9c5  81c404010000           -add esp, 0x104
    (cpu.esp) += x86::reg32(x86::sreg32(260 /*0x104*/));
    // 0052b9cb  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052b9cc  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052b9cd  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052b9ce  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052b9cf  90                     -nop 
    ;
    // 0052b9d0  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip  */
void Application::sub_52b9d0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    goto L_entry_0x0052b9d0;
    // 0052b970  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 0052b971  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 0052b972  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 0052b973  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 0052b974  81ec04010000           -sub esp, 0x104
    (cpu.esp) -= x86::reg32(x86::sreg32(260 /*0x104*/));
    // 0052b97a  8bb4241c010000         -mov esi, dword ptr [esp + 0x11c]
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(284) /* 0x11c */);
    // 0052b981  8b8c2418010000         -mov ecx, dword ptr [esp + 0x118]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(280) /* 0x118 */);
    // 0052b988  8d842424010000         -lea eax, [esp + 0x124]
    cpu.eax = x86::reg32(cpu.esp + x86::reg32(292) /* 0x124 */);
    // 0052b98f  8d9c2400010000         -lea ebx, [esp + 0x100]
    cpu.ebx = x86::reg32(cpu.esp + x86::reg32(256) /* 0x100 */);
    // 0052b996  8b942420010000         -mov edx, dword ptr [esp + 0x120]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(288) /* 0x120 */);
    // 0052b99d  c1e603                 -shl esi, 3
    cpu.esi <<= 3 /*0x3*/ % 32;
    // 0052b9a0  89842400010000         -mov dword ptr [esp + 0x100], eax
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(256) /* 0x100 */) = cpu.eax;
    // 0052b9a7  89e0                   -mov eax, esp
    cpu.eax = cpu.esp;
    // 0052b9a9  c1e103                 -shl ecx, 3
    cpu.ecx <<= 3 /*0x3*/ % 32;
    // 0052b9ac  e8c33cfbff             -call 0x4df674
    cpu.esp -= 4;
    nfs3hp::watcom::vsprintf(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052b9b1  89e0                   -mov eax, esp
    cpu.eax = cpu.esp;
    // 0052b9b3  89f3                   -mov ebx, esi
    cpu.ebx = cpu.esi;
    // 0052b9b5  89ca                   -mov edx, ecx
    cpu.edx = cpu.ecx;
    // 0052b9b7  e8242b0000             -call 0x52e4e0
    cpu.esp -= 4;
    sub_52e4e0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052b9bc  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 0052b9be  89942400010000         -mov dword ptr [esp + 0x100], edx
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(256) /* 0x100 */) = cpu.edx;
    // 0052b9c5  81c404010000           -add esp, 0x104
    (cpu.esp) += x86::reg32(x86::sreg32(260 /*0x104*/));
    // 0052b9cb  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052b9cc  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052b9cd  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052b9ce  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052b9cf  90                     -nop 
    ;
L_entry_0x0052b9d0:
    // 0052b9d0  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x8d 0x40 0x00 */
void Application::sub_52b9e0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0052b9e0  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 0052b9e1  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 0052b9e3  89da                   -mov edx, ebx
    cpu.edx = cpu.ebx;
    // 0052b9e5  b8000000ff             -mov eax, 0xff000000
    cpu.eax = 4278190080 /*0xff000000*/;
    // 0052b9ea  e8713dfcff             -call 0x4ef760
    cpu.esp -= 4;
    sub_4ef760(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052b9ef  e8bc37fcff             -call 0x4ef1b0
    cpu.esp -= 4;
    sub_4ef1b0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052b9f4  89cb                   -mov ebx, ecx
    cpu.ebx = cpu.ecx;
    // 0052b9f6  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 0052b9f8  e8c34ffcff             -call 0x4f09c0
    cpu.esp -= 4;
    sub_4f09c0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052b9fd  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052b9fe  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x90 */
void Application::sub_52ba00(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0052ba00  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 0052ba01  e86a000000             -call 0x52ba70
    cpu.esp -= 4;
    sub_52ba70(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052ba06  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 0052ba08  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 0052ba0a  e861000000             -call 0x52ba70
    cpu.esp -= 4;
    sub_52ba70(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052ba0f  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 0052ba11  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 0052ba13  e8183efcff             -call 0x4ef830
    cpu.esp -= 4;
    sub_4ef830(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052ba18  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052ba19  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8b 0xd2 */
void Application::sub_52ba70(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
  goto start;
dynamic_jump:
  switch(cpu.ip)
  {
start:
    // 0052ba70  83f812                 +cmp eax, 0x12
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(18 /*0x12*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0052ba73  7707                   -ja 0x52ba7c
    if (!cpu.flags.cf && !cpu.flags.zf)
    {
        goto L_0x0052ba7c;
    }
    // 0052ba75  ff24851cba5200         -jmp dword ptr [eax*4 + 0x52ba1c]
    cpu.ip = app->getMemory<x86::reg32>(5421596 + cpu.eax * 4); goto dynamic_jump;
  case 0x0052ba7c:
L_0x0052ba7c:
    // 0052ba7c  b8aaaa00ff             -mov eax, 0xff00aaaa
    cpu.eax = 4278233770 /*0xff00aaaa*/;
    // 0052ba81  e9da3cfcff             -jmp 0x4ef760
    return sub_4ef760(app, cpu.handOver());
  case 0x0052ba86:
    // 0052ba86  b8000000ff             -mov eax, 0xff000000
    cpu.eax = 4278190080 /*0xff000000*/;
    // 0052ba8b  e9d03cfcff             -jmp 0x4ef760
    return sub_4ef760(app, cpu.handOver());
  case 0x0052ba90:
    // 0052ba90  b8ffffffff             -mov eax, 0xffffffff
    cpu.eax = 4294967295 /*0xffffffff*/;
    // 0052ba95  e9c63cfcff             -jmp 0x4ef760
    return sub_4ef760(app, cpu.handOver());
  case 0x0052ba9a:
    // 0052ba9a  b80000aaff             -mov eax, 0xffaa0000
    cpu.eax = 4289331200 /*0xffaa0000*/;
    // 0052ba9f  e9bc3cfcff             -jmp 0x4ef760
    return sub_4ef760(app, cpu.handOver());
  case 0x0052baa4:
    // 0052baa4  b850ffffff             -mov eax, 0xffffff50
    cpu.eax = 4294967120 /*0xffffff50*/;
    // 0052baa9  e9b23cfcff             -jmp 0x4ef760
    return sub_4ef760(app, cpu.handOver());
  case 0x0052baae:
    // 0052baae  b8aa0000ff             -mov eax, 0xff0000aa
    cpu.eax = 4278190250 /*0xff0000aa*/;
    // 0052bab3  e9a83cfcff             -jmp 0x4ef760
    return sub_4ef760(app, cpu.handOver());
  default:
    NFS2_ASSERT(false);
  }
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8b 0xd2 */
void Application::sub_52bac0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0052bac0  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 0052bac1  b8e0004f00             -mov eax, 0x4f00e0
    cpu.eax = 5177568 /*0x4f00e0*/;
    // 0052bac6  e82546fcff             -call 0x4f00f0
    cpu.esp -= 4;
    sub_4f00f0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x0052bacb:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 0052bacb  e85046fcff             -call 0x4f0120
    cpu.esp -= 4;
    sub_4f0120(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052bad0  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 0052bad2  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0052bad4  74f5                   -je 0x52bacb
    if (cpu.flags.zf)
    {
        goto L_0x0052bacb;
    }
    // 0052bad6  83f861                 +cmp eax, 0x61
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(97 /*0x61*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0052bad9  7c08                   -jl 0x52bae3
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x0052bae3;
    }
    // 0052badb  83f87a                 +cmp eax, 0x7a
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(122 /*0x7a*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0052bade  7f03                   -jg 0x52bae3
    if (!cpu.flags.zf && (cpu.flags.sf == cpu.flags.of))
    {
        goto L_0x0052bae3;
    }
    // 0052bae0  8d50e0                 -lea edx, [eax - 0x20]
    cpu.edx = x86::reg32(cpu.eax + x86::reg32(-32) /* -0x20 */);
L_0x0052bae3:
    // 0052bae3  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 0052bae5  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052bae6  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 */
void Application::sub_52baf0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0052baf0  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 0052baf1  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 0052baf3  8b442408               -mov eax, dword ptr [esp + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(8) /* 0x8 */);
    // 0052baf7  e874ffffff             -call 0x52ba70
    cpu.esp -= 4;
    sub_52ba70(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052bafc  c1e603                 -shl esi, 3
    cpu.esi <<= 3 /*0x3*/ % 32;
    // 0052baff  c1e203                 -shl edx, 3
    cpu.edx <<= 3 /*0x3*/ % 32;
    // 0052bb02  c1e303                 -shl ebx, 3
    cpu.ebx <<= 3 /*0x3*/ % 32;
    // 0052bb05  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 0052bb06  c1e103                 -shl ecx, 3
    cpu.ecx <<= 3 /*0x3*/ % 32;
    // 0052bb09  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 0052bb0b  e8301afdff             -call 0x4fd540
    cpu.esp -= 4;
    sub_4fd540(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052bb10  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052bb11  c20400                 -ret 4
    cpu.esp += 4+4 /*0x4*/;
    return;
}

/* align: skip 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 */
void Application::sub_52bb20(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0052bb20  b898b15600             -mov eax, 0x56b198
    cpu.eax = 5681560 /*0x56b198*/;
    // 0052bb25  e9f6baf6ff             -jmp 0x497620
    return sub_497620(app, cpu.handOver());
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8b 0xd2 */
void Application::sub_52bb50(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
  goto start;
dynamic_jump:
  switch(cpu.ip)
  {
start:
    // 0052bb50  83f804                 +cmp eax, 4
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
    // 0052bb53  7707                   -ja 0x52bb5c
    if (!cpu.flags.cf && !cpu.flags.zf)
    {
        goto L_0x0052bb5c;
    }
    // 0052bb55  ff248534bb5200         -jmp dword ptr [eax*4 + 0x52bb34]
    cpu.ip = app->getMemory<x86::reg32>(5421876 + cpu.eax * 4); goto dynamic_jump;
  case 0x0052bb5c:
L_0x0052bb5c:
    // 0052bb5c  b850000000             -mov eax, 0x50
    cpu.eax = 80 /*0x50*/;
    // 0052bb61  c3                     -ret 
    cpu.esp += 4;
    return;
  case 0x0052bb62:
    // 0052bb62  b818000000             -mov eax, 0x18
    cpu.eax = 24 /*0x18*/;
    // 0052bb67  c3                     -ret 
    cpu.esp += 4;
    return;
  case 0x0052bb68:
    // 0052bb68  a1f84f5600             -mov eax, dword ptr [0x564ff8]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5656568) /* 0x564ff8 */);
    // 0052bb6d  c3                     -ret 
    cpu.esp += 4;
    return;
  case 0x0052bb6e:
    // 0052bb6e  a1fc4f5600             -mov eax, dword ptr [0x564ffc]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5656572) /* 0x564ffc */);
    // 0052bb73  c3                     -ret 
    cpu.esp += 4;
    return;
  case 0x0052bb74:
    // 0052bb74  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 0052bb76  c3                     -ret 
    cpu.esp += 4;
    return;
  default:
    NFS2_ASSERT(false);
  }
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 */
void Application::sub_52bb80(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0052bb80  e91b51fbff             -jmp 0x4e0ca0
    return sub_4e0ca0(app, cpu.handOver());
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 0x8b 0xdb */
void Application::sub_52bb90(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0052bb90  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 0052bb91  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 0052bb93  e888f1fbff             -call 0x4ead20
    cpu.esp -= 4;
    sub_4ead20(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052bb98  e883280000             -call 0x52e420
    cpu.esp -= 4;
    sub_52e420(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052bb9d  8b5602                 -mov edx, dword ptr [esi + 2]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(2) /* 0x2 */);
    // 0052bba0  b802000000             -mov eax, 2
    cpu.eax = 2 /*0x2*/;
    // 0052bba5  c1fa10                 -sar edx, 0x10
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (16 /*0x10*/ % 32));
    // 0052bba8  e8a3ffffff             -call 0x52bb50
    cpu.esp -= 4;
    sub_52bb50(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052bbad  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 0052bbaf  8b5e04                 -mov ebx, dword ptr [esi + 4]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 0052bbb2  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 0052bbb4  b803000000             -mov eax, 3
    cpu.eax = 3 /*0x3*/;
    // 0052bbb9  c1fb10                 -sar ebx, 0x10
    cpu.ebx = x86::reg32(x86::sreg32(cpu.ebx) >> (16 /*0x10*/ % 32));
    // 0052bbbc  e88fffffff             -call 0x52bb50
    cpu.esp -= 4;
    sub_52bb50(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052bbc1  29d8                   -sub eax, ebx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.ebx));
    // 0052bbc3  d1fa                   -sar edx, 1
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (1 /*0x1*/ % 32));
    // 0052bbc5  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 0052bbc7  b8000000ff             -mov eax, 0xff000000
    cpu.eax = 4278190080 /*0xff000000*/;
    // 0052bbcc  d1fb                   -sar ebx, 1
    cpu.ebx = x86::reg32(x86::sreg32(cpu.ebx) >> (1 /*0x1*/ % 32));
    // 0052bbce  e88d3bfcff             -call 0x4ef760
    cpu.esp -= 4;
    sub_4ef760(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052bbd3  e8d835fcff             -call 0x4ef1b0
    cpu.esp -= 4;
    sub_4ef1b0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052bbd8  e8c350fbff             -call 0x4e0ca0
    cpu.esp -= 4;
    sub_4e0ca0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052bbdd  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 0052bbdf  e8dc4dfcff             -call 0x4f09c0
    cpu.esp -= 4;
    sub_4f09c0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052bbe4  e8a7f1fbff             -call 0x4ead90
    cpu.esp -= 4;
    sub_4ead90(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052bbe9  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052bbea  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x40 0x00 0x8b 0xc9 */
void Application::sub_52bbf0(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0052bbf0  e80b010000             -call 0x52bd00
    cpu.esp -= 4;
    sub_52bd00(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052bbf5  e95651fbff             -jmp 0x4e0d50
    return sub_4e0d50(app, cpu.handOver());
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 */
void Application::sub_52bc00(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0052bc00  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 0052bc01  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 0052bc02  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 0052bc03  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 0052bc04  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 0052bc05  81ec04010000           -sub esp, 0x104
    (cpu.esp) -= x86::reg32(x86::sreg32(260 /*0x104*/));
    // 0052bc0b  8b8c241c010000         -mov ecx, dword ptr [esp + 0x11c]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(284) /* 0x11c */);
    // 0052bc12  8bb42420010000         -mov esi, dword ptr [esp + 0x120]
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(288) /* 0x120 */);
    // 0052bc19  8b1594725600           -mov edx, dword ptr [0x567294]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5665428) /* 0x567294 */);
    // 0052bc1f  c1e103                 -shl ecx, 3
    cpu.ecx <<= 3 /*0x3*/ % 32;
    // 0052bc22  c1e603                 -shl esi, 3
    cpu.esi <<= 3 /*0x3*/ % 32;
    // 0052bc25  81fa80b55000           +cmp edx, 0x50b580
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(5289344 /*0x50b580*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0052bc2b  7452                   -je 0x52bc7f
    if (cpu.flags.zf)
    {
        goto L_0x0052bc7f;
    }
L_0x0052bc2d:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 0052bc2d  8d842428010000         -lea eax, [esp + 0x128]
    cpu.eax = x86::reg32(cpu.esp + x86::reg32(296) /* 0x128 */);
    // 0052bc34  8d9c2400010000         -lea ebx, [esp + 0x100]
    cpu.ebx = x86::reg32(cpu.esp + x86::reg32(256) /* 0x100 */);
    // 0052bc3b  8b942424010000         -mov edx, dword ptr [esp + 0x124]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(292) /* 0x124 */);
    // 0052bc42  89842400010000         -mov dword ptr [esp + 0x100], eax
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(256) /* 0x100 */) = cpu.eax;
    // 0052bc49  89e0                   -mov eax, esp
    cpu.eax = cpu.esp;
    // 0052bc4b  e8243afbff             -call 0x4df674
    cpu.esp -= 4;
    nfs3hp::watcom::vsprintf(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052bc50  e8cbf0fbff             -call 0x4ead20
    cpu.esp -= 4;
    sub_4ead20(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052bc55  e8c6270000             -call 0x52e420
    cpu.esp -= 4;
    sub_52e420(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052bc5a  89e0                   -mov eax, esp
    cpu.eax = cpu.esp;
    // 0052bc5c  89f3                   -mov ebx, esi
    cpu.ebx = cpu.esi;
    // 0052bc5e  89ca                   -mov edx, ecx
    cpu.edx = cpu.ecx;
    // 0052bc60  e87b280000             -call 0x52e4e0
    cpu.esp -= 4;
    sub_52e4e0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052bc65  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 0052bc67  89842400010000         -mov dword ptr [esp + 0x100], eax
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(256) /* 0x100 */) = cpu.eax;
    // 0052bc6e  e81df1fbff             -call 0x4ead90
    cpu.esp -= 4;
    sub_4ead90(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052bc73  81c404010000           -add esp, 0x104
    (cpu.esp) += x86::reg32(x86::sreg32(260 /*0x104*/));
    // 0052bc79  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052bc7a  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052bc7b  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052bc7c  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052bc7d  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052bc7e  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x0052bc7f:
    // 0052bc7f  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 0052bc80  bb50205500             -mov ebx, 0x552050
    cpu.ebx = 5578832 /*0x552050*/;
    // 0052bc85  bf60205500             -mov edi, 0x552060
    cpu.edi = 5578848 /*0x552060*/;
    // 0052bc8a  bd72000000             -mov ebp, 0x72
    cpu.ebp = 114 /*0x72*/;
    // 0052bc8f  6874205500             -push 0x552074
    app->getMemory<x86::reg32>(cpu.esp-4) = 5578868 /*0x552074*/;
    cpu.esp -= 4;
    // 0052bc94  891d90215500           -mov dword ptr [0x552190], ebx
    app->getMemory<x86::reg32>(x86::reg32(5579152) /* 0x552190 */) = cpu.ebx;
    // 0052bc9a  893d94215500           -mov dword ptr [0x552194], edi
    app->getMemory<x86::reg32>(x86::reg32(5579156) /* 0x552194 */) = cpu.edi;
    // 0052bca0  892d98215500           -mov dword ptr [0x552198], ebp
    app->getMemory<x86::reg32>(x86::reg32(5579160) /* 0x552198 */) = cpu.ebp;
    // 0052bca6  e86553edff             -call 0x401010
    cpu.esp -= 4;
    nfs3hp::Error(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052bcab  83c404                 +add esp, 4
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
    // 0052bcae  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052bcaf  e979ffffff             -jmp 0x52bc2d
    goto L_0x0052bc2d;
}

/* align: skip  */
void Application::sub_52bd00(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
  goto start;
dynamic_jump:
  switch(cpu.ip)
  {
start:
    // 0052bd00  83f812                 +cmp eax, 0x12
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(18 /*0x12*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0052bd03  7707                   -ja 0x52bd0c
    if (!cpu.flags.cf && !cpu.flags.zf)
    {
        goto L_0x0052bd0c;
    }
    // 0052bd05  ff2485b4bc5200         -jmp dword ptr [eax*4 + 0x52bcb4]
    cpu.ip = app->getMemory<x86::reg32>(5422260 + cpu.eax * 4); goto dynamic_jump;
  case 0x0052bd0c:
L_0x0052bd0c:
    // 0052bd0c  b807000000             -mov eax, 7
    cpu.eax = 7 /*0x7*/;
    // 0052bd11  c3                     -ret 
    cpu.esp += 4;
    return;
  case 0x0052bd12:
    // 0052bd12  b870000000             -mov eax, 0x70
    cpu.eax = 112 /*0x70*/;
    // 0052bd17  c3                     -ret 
    cpu.esp += 4;
    return;
  default:
    NFS2_ASSERT(false);
  }
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8b 0xd2 */
void Application::sub_52bd20(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0052bd20  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 0052bd21  b8e0004f00             -mov eax, 0x4f00e0
    cpu.eax = 5177568 /*0x4f00e0*/;
    // 0052bd26  e8c543fcff             -call 0x4f00f0
    cpu.esp -= 4;
    sub_4f00f0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x0052bd2b:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 0052bd2b  e8f043fcff             -call 0x4f0120
    cpu.esp -= 4;
    sub_4f0120(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052bd30  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 0052bd32  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0052bd34  74f5                   -je 0x52bd2b
    if (cpu.flags.zf)
    {
        goto L_0x0052bd2b;
    }
    // 0052bd36  83f861                 +cmp eax, 0x61
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(97 /*0x61*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0052bd39  7c08                   -jl 0x52bd43
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x0052bd43;
    }
    // 0052bd3b  83f87a                 +cmp eax, 0x7a
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(122 /*0x7a*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0052bd3e  7f03                   -jg 0x52bd43
    if (!cpu.flags.zf && (cpu.flags.sf == cpu.flags.of))
    {
        goto L_0x0052bd43;
    }
    // 0052bd40  8d50e0                 -lea edx, [eax - 0x20]
    cpu.edx = x86::reg32(cpu.eax + x86::reg32(-32) /* -0x20 */);
L_0x0052bd43:
    // 0052bd43  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 0052bd45  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052bd46  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 */
void Application::sub_52bd50(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0052bd50  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 0052bd51  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 0052bd52  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 0052bd53  83ec0c                 -sub esp, 0xc
    (cpu.esp) -= x86::reg32(x86::sreg32(12 /*0xc*/));
    // 0052bd56  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 0052bd58  891424                 -mov dword ptr [esp], edx
    app->getMemory<x86::reg32>(cpu.esp) = cpu.edx;
    // 0052bd5b  89df                   -mov edi, ebx
    cpu.edi = cpu.ebx;
    // 0052bd5d  89cd                   -mov ebp, ecx
    cpu.ebp = cpu.ecx;
    // 0052bd5f  8b44241c               -mov eax, dword ptr [esp + 0x1c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(28) /* 0x1c */);
    // 0052bd63  8b0c24                 -mov ecx, dword ptr [esp]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    // 0052bd66  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 0052bd68  01cd                   -add ebp, ecx
    (cpu.ebp) += x86::reg32(x86::sreg32(cpu.ecx));
    // 0052bd6a  e881feffff             -call 0x52bbf0
    cpu.esp -= 4;
    sub_52bbf0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052bd6f  39cd                   +cmp ebp, ecx
    {
        x86::reg32 tmp1 = cpu.ebp;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ecx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0052bd71  7e31                   -jle 0x52bda4
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x0052bda4;
    }
    // 0052bd73  89742408               -mov dword ptr [esp + 8], esi
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(8) /* 0x8 */) = cpu.esi;
    // 0052bd77  895c2404               -mov dword ptr [esp + 4], ebx
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(4) /* 0x4 */) = cpu.ebx;
L_0x0052bd7b:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 0052bd7b  85ff                   +test edi, edi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edi & cpu.edi));
    // 0052bd7d  7e20                   -jle 0x52bd9f
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x0052bd9f;
    }
    // 0052bd7f  8b5c2408               -mov ebx, dword ptr [esp + 8]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(8) /* 0x8 */);
    // 0052bd83  8b442404               -mov eax, dword ptr [esp + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(4) /* 0x4 */);
    // 0052bd87  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 0052bd89  01c3                   -add ebx, eax
    (cpu.ebx) += x86::reg32(x86::sreg32(cpu.eax));
L_0x0052bd8b:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 0052bd8b  68b4205500             -push 0x5520b4
    app->getMemory<x86::reg32>(cpu.esp-4) = 5578932 /*0x5520b4*/;
    cpu.esp -= 4;
    // 0052bd90  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 0052bd91  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 0052bd92  e8e94bfbff             -call 0x4e0980
    cpu.esp -= 4;
    sub_4e0980(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052bd97  42                     -inc edx
    (cpu.edx)++;
    // 0052bd98  83c40c                 -add esp, 0xc
    (cpu.esp) += x86::reg32(x86::sreg32(12 /*0xc*/));
    // 0052bd9b  39da                   +cmp edx, ebx
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ebx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0052bd9d  7cec                   -jl 0x52bd8b
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x0052bd8b;
    }
L_0x0052bd9f:
    // 0052bd9f  41                     -inc ecx
    (cpu.ecx)++;
    // 0052bda0  39e9                   +cmp ecx, ebp
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ebp));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0052bda2  7cd7                   -jl 0x52bd7b
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x0052bd7b;
    }
L_0x0052bda4:
    // 0052bda4  83c40c                 -add esp, 0xc
    (cpu.esp) += x86::reg32(x86::sreg32(12 /*0xc*/));
    // 0052bda7  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052bda8  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052bda9  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052bdaa  c20400                 -ret 4
    cpu.esp += 4+4 /*0x4*/;
    return;
}

/* align: skip 0x00 0x00 0x00 */
void Application::sub_52bdb0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0052bdb0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 0052bdb1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 0052bdb2  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 0052bdb3  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 0052bdb4  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 0052bdb5  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 0052bdb6  83ec10                 -sub esp, 0x10
    (cpu.esp) -= x86::reg32(x86::sreg32(16 /*0x10*/));
    // 0052bdb9  b8b8205500             -mov eax, 0x5520b8
    cpu.eax = 5578936 /*0x5520b8*/;
    // 0052bdbe  e80d2dfeff             -call 0x50ead0
    cpu.esp -= 4;
    nfs3hp::watcom::getenv(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052bdc3  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 0052bdc5  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0052bdc7  0f84f9000000           -je 0x52bec6
    if (cpu.flags.zf)
    {
        goto L_0x0052bec6;
    }
L_0x0052bdcd:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 0052bdcd  803900                 +cmp byte ptr [ecx], 0
    {
        x86::reg8 tmp1 = app->getMemory<x86::reg8>(cpu.ecx);
        x86::reg8 tmp2 = x86::reg8(x86::sreg8(0 /*0x0*/));
        x86::reg8 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 7);
        cpu.flags.of ^= 1 & (result >> 7);
        cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
        cpu.set_szp(result);
    }
    // 0052bdd0  0f84e6000000           -je 0x52bebc
    if (cpu.flags.zf)
    {
        goto L_0x0052bebc;
    }
    // 0052bdd6  b23a                   -mov dl, 0x3a
    cpu.dl = 58 /*0x3a*/;
    // 0052bdd8  89ce                   -mov esi, ecx
    cpu.esi = cpu.ecx;
L_0x0052bdda:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 0052bdda  8a06                   -mov al, byte ptr [esi]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi);
    // 0052bddc  3ac2                   +cmp al, dl
    {
        x86::reg8 tmp1 = cpu.al;
        x86::reg8 tmp2 = x86::reg8(x86::sreg8(cpu.dl));
        x86::reg8 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 7);
        cpu.flags.of ^= 1 & (result >> 7);
        cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
        cpu.set_szp(result);
    }
    // 0052bdde  7412                   -je 0x52bdf2
    if (cpu.flags.zf)
    {
        goto L_0x0052bdf2;
    }
    // 0052bde0  3c00                   +cmp al, 0
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
    // 0052bde2  740c                   -je 0x52bdf0
    if (cpu.flags.zf)
    {
        goto L_0x0052bdf0;
    }
    // 0052bde4  46                     -inc esi
    (cpu.esi)++;
    // 0052bde5  8a06                   -mov al, byte ptr [esi]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi);
    // 0052bde7  3ac2                   +cmp al, dl
    {
        x86::reg8 tmp1 = cpu.al;
        x86::reg8 tmp2 = x86::reg8(x86::sreg8(cpu.dl));
        x86::reg8 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 7);
        cpu.flags.of ^= 1 & (result >> 7);
        cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
        cpu.set_szp(result);
    }
    // 0052bde9  7407                   -je 0x52bdf2
    if (cpu.flags.zf)
    {
        goto L_0x0052bdf2;
    }
    // 0052bdeb  46                     -inc esi
    (cpu.esi)++;
    // 0052bdec  3c00                   +cmp al, 0
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
    // 0052bdee  75ea                   -jne 0x52bdda
    if (!cpu.flags.zf)
    {
        goto L_0x0052bdda;
    }
L_0x0052bdf0:
    // 0052bdf0  2bf6                   -sub esi, esi
    (cpu.esi) -= x86::reg32(x86::sreg32(cpu.esi));
L_0x0052bdf2:
    // 0052bdf2  89e0                   -mov eax, esp
    cpu.eax = cpu.esp;
    // 0052bdf4  89f5                   -mov ebp, esi
    cpu.ebp = cpu.esi;
    // 0052bdf6  29ce                   -sub esi, ecx
    (cpu.esi) -= x86::reg32(x86::sreg32(cpu.ecx));
    // 0052bdf8  89ca                   -mov edx, ecx
    cpu.edx = cpu.ecx;
    // 0052bdfa  89f3                   -mov ebx, esi
    cpu.ebx = cpu.esi;
    // 0052bdfc  e82f50fbff             -call 0x4e0e30
    cpu.esp -= 4;
    nfs3hp::watcom::strncpy(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052be01  bb10000000             -mov ebx, 0x10
    cpu.ebx = 16 /*0x10*/;
    // 0052be06  30d2                   -xor dl, dl
    cpu.dl ^= x86::reg8(x86::sreg8(cpu.dl));
    // 0052be08  89e0                   -mov eax, esp
    cpu.eax = cpu.esp;
    // 0052be0a  881434                 -mov byte ptr [esp + esi], dl
    app->getMemory<x86::reg8>(cpu.esp + cpu.esi * 1) = cpu.dl;
    // 0052be0d  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 0052be0f  e84c280000             -call 0x52e660
    cpu.esp -= 4;
    sub_52e660(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052be14  8d7501                 -lea esi, [ebp + 1]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(1) /* 0x1 */);
    // 0052be17  b23a                   -mov dl, 0x3a
    cpu.dl = 58 /*0x3a*/;
    // 0052be19  89c7                   -mov edi, eax
    cpu.edi = cpu.eax;
    // 0052be1b  89f1                   -mov ecx, esi
    cpu.ecx = cpu.esi;
L_0x0052be1d:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 0052be1d  8a06                   -mov al, byte ptr [esi]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi);
    // 0052be1f  3ac2                   +cmp al, dl
    {
        x86::reg8 tmp1 = cpu.al;
        x86::reg8 tmp2 = x86::reg8(x86::sreg8(cpu.dl));
        x86::reg8 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 7);
        cpu.flags.of ^= 1 & (result >> 7);
        cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
        cpu.set_szp(result);
    }
    // 0052be21  7412                   -je 0x52be35
    if (cpu.flags.zf)
    {
        goto L_0x0052be35;
    }
    // 0052be23  3c00                   +cmp al, 0
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
    // 0052be25  740c                   -je 0x52be33
    if (cpu.flags.zf)
    {
        goto L_0x0052be33;
    }
    // 0052be27  46                     -inc esi
    (cpu.esi)++;
    // 0052be28  8a06                   -mov al, byte ptr [esi]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi);
    // 0052be2a  3ac2                   +cmp al, dl
    {
        x86::reg8 tmp1 = cpu.al;
        x86::reg8 tmp2 = x86::reg8(x86::sreg8(cpu.dl));
        x86::reg8 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 7);
        cpu.flags.of ^= 1 & (result >> 7);
        cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
        cpu.set_szp(result);
    }
    // 0052be2c  7407                   -je 0x52be35
    if (cpu.flags.zf)
    {
        goto L_0x0052be35;
    }
    // 0052be2e  46                     -inc esi
    (cpu.esi)++;
    // 0052be2f  3c00                   +cmp al, 0
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
    // 0052be31  75ea                   -jne 0x52be1d
    if (!cpu.flags.zf)
    {
        goto L_0x0052be1d;
    }
L_0x0052be33:
    // 0052be33  2bf6                   -sub esi, esi
    (cpu.esi) -= x86::reg32(x86::sreg32(cpu.esi));
L_0x0052be35:
    // 0052be35  89e0                   -mov eax, esp
    cpu.eax = cpu.esp;
    // 0052be37  89f5                   -mov ebp, esi
    cpu.ebp = cpu.esi;
    // 0052be39  29ce                   -sub esi, ecx
    (cpu.esi) -= x86::reg32(x86::sreg32(cpu.ecx));
    // 0052be3b  89ca                   -mov edx, ecx
    cpu.edx = cpu.ecx;
    // 0052be3d  89f3                   -mov ebx, esi
    cpu.ebx = cpu.esi;
    // 0052be3f  e8ec4ffbff             -call 0x4e0e30
    cpu.esp -= 4;
    nfs3hp::watcom::strncpy(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052be44  bb10000000             -mov ebx, 0x10
    cpu.ebx = 16 /*0x10*/;
    // 0052be49  30f6                   -xor dh, dh
    cpu.dh ^= x86::reg8(x86::sreg8(cpu.dh));
    // 0052be4b  89e0                   -mov eax, esp
    cpu.eax = cpu.esp;
    // 0052be4d  883434                 -mov byte ptr [esp + esi], dh
    app->getMemory<x86::reg8>(cpu.esp + cpu.esi * 1) = cpu.dh;
    // 0052be50  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 0052be52  e809280000             -call 0x52e660
    cpu.esp -= 4;
    sub_52e660(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052be57  8d7501                 -lea esi, [ebp + 1]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(1) /* 0x1 */);
    // 0052be5a  b22a                   -mov dl, 0x2a
    cpu.dl = 42 /*0x2a*/;
    // 0052be5c  8944240c               -mov dword ptr [esp + 0xc], eax
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(12) /* 0xc */) = cpu.eax;
    // 0052be60  89f1                   -mov ecx, esi
    cpu.ecx = cpu.esi;
L_0x0052be62:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 0052be62  8a06                   -mov al, byte ptr [esi]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi);
    // 0052be64  3ac2                   +cmp al, dl
    {
        x86::reg8 tmp1 = cpu.al;
        x86::reg8 tmp2 = x86::reg8(x86::sreg8(cpu.dl));
        x86::reg8 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 7);
        cpu.flags.of ^= 1 & (result >> 7);
        cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
        cpu.set_szp(result);
    }
    // 0052be66  7412                   -je 0x52be7a
    if (cpu.flags.zf)
    {
        goto L_0x0052be7a;
    }
    // 0052be68  3c00                   +cmp al, 0
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
    // 0052be6a  740c                   -je 0x52be78
    if (cpu.flags.zf)
    {
        goto L_0x0052be78;
    }
    // 0052be6c  46                     -inc esi
    (cpu.esi)++;
    // 0052be6d  8a06                   -mov al, byte ptr [esi]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi);
    // 0052be6f  3ac2                   +cmp al, dl
    {
        x86::reg8 tmp1 = cpu.al;
        x86::reg8 tmp2 = x86::reg8(x86::sreg8(cpu.dl));
        x86::reg8 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 7);
        cpu.flags.of ^= 1 & (result >> 7);
        cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
        cpu.set_szp(result);
    }
    // 0052be71  7407                   -je 0x52be7a
    if (cpu.flags.zf)
    {
        goto L_0x0052be7a;
    }
    // 0052be73  46                     -inc esi
    (cpu.esi)++;
    // 0052be74  3c00                   +cmp al, 0
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
    // 0052be76  75ea                   -jne 0x52be62
    if (!cpu.flags.zf)
    {
        goto L_0x0052be62;
    }
L_0x0052be78:
    // 0052be78  2bf6                   -sub esi, esi
    (cpu.esi) -= x86::reg32(x86::sreg32(cpu.esi));
L_0x0052be7a:
    // 0052be7a  89e0                   -mov eax, esp
    cpu.eax = cpu.esp;
    // 0052be7c  89f5                   -mov ebp, esi
    cpu.ebp = cpu.esi;
    // 0052be7e  29ce                   -sub esi, ecx
    (cpu.esi) -= x86::reg32(x86::sreg32(cpu.ecx));
    // 0052be80  89ca                   -mov edx, ecx
    cpu.edx = cpu.ecx;
    // 0052be82  89f3                   -mov ebx, esi
    cpu.ebx = cpu.esi;
    // 0052be84  e8a74ffbff             -call 0x4e0e30
    cpu.esp -= 4;
    nfs3hp::watcom::strncpy(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052be89  89e0                   -mov eax, esp
    cpu.eax = cpu.esp;
    // 0052be8b  30db                   -xor bl, bl
    cpu.bl ^= x86::reg8(x86::sreg8(cpu.bl));
    // 0052be8d  31d2                   +xor edx, edx
    cpu.clear_co();
    cpu.set_szp((cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx))));
    // 0052be8f  881c34                 -mov byte ptr [esp + esi], bl
    app->getMemory<x86::reg8>(cpu.esp + cpu.esi * 1) = cpu.bl;
    // 0052be92  bb10000000             -mov ebx, 0x10
    cpu.ebx = 16 /*0x10*/;
    // 0052be97  e8c4270000             -call 0x52e660
    cpu.esp -= 4;
    sub_52e660(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052be9c  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 0052be9e  89fa                   -mov edx, edi
    cpu.edx = cpu.edi;
    // 0052bea0  8b44240c               -mov eax, dword ptr [esp + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(12) /* 0xc */);
    // 0052bea4  e8df24ffff             -call 0x51e388
    cpu.esp -= 4;
    sub_51e388(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052bea9  89ca                   -mov edx, ecx
    cpu.edx = cpu.ecx;
    // 0052beab  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 0052bead  8d7501                 -lea esi, [ebp + 1]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(1) /* 0x1 */);
    // 0052beb0  e8836fffff             -call 0x522e38
    cpu.esp -= 4;
    nfs3hp::watcom::SetIOMode(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052beb5  89f1                   -mov ecx, esi
    cpu.ecx = cpu.esi;
    // 0052beb7  e911ffffff             -jmp 0x52bdcd
    goto L_0x0052bdcd;
L_0x0052bebc:
    // 0052bebc  b8c4205500             -mov eax, 0x5520c4
    cpu.eax = 5578948 /*0x5520c4*/;
    // 0052bec1  e80a280000             -call 0x52e6d0
    cpu.esp -= 4;
    sub_52e6d0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x0052bec6:
    // 0052bec6  83c410                 -add esp, 0x10
    (cpu.esp) += x86::reg32(x86::sreg32(16 /*0x10*/));
    // 0052bec9  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052beca  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052becb  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052becc  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052becd  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052bece  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052becf  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip  */
void Application::sub_52bed0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0052bed0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 0052bed1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 0052bed2  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 0052bed3  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 0052bed4  8b1554b1a000           -mov edx, dword ptr [0xa0b154]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(10531156) /* 0xa0b154 */);
    // 0052beda  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 0052bedc  0f8480000000           -je 0x52bf62
    if (cpu.flags.zf)
    {
        goto L_0x0052bf62;
    }
    // 0052bee2  eb30                   -jmp 0x52bf14
    goto L_0x0052bf14;
L_0x0052bee4:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 0052bee4  833d50b1a00000         +cmp dword ptr [0xa0b150], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(10531152) /* 0xa0b150 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0052beeb  7424                   -je 0x52bf11
    if (cpu.flags.zf)
    {
        goto L_0x0052bf11;
    }
    // 0052beed  8b3554b1a000           -mov esi, dword ptr [0xa0b154]
    cpu.esi = app->getMemory<x86::reg32>(x86::reg32(10531156) /* 0xa0b154 */);
    // 0052bef3  89d1                   -mov ecx, edx
    cpu.ecx = cpu.edx;
    // 0052bef5  29f1                   -sub ecx, esi
    (cpu.ecx) -= x86::reg32(x86::sreg32(cpu.esi));
    // 0052bef7  8b1d50b1a000           -mov ebx, dword ptr [0xa0b150]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(10531152) /* 0xa0b150 */);
    // 0052befd  c1f902                 -sar ecx, 2
    cpu.ecx = x86::reg32(x86::sreg32(cpu.ecx) >> (2 /*0x2*/ % 32));
    // 0052bf00  803c1900               +cmp byte ptr [ecx + ebx], 0
    {
        x86::reg8 tmp1 = app->getMemory<x86::reg8>(cpu.ecx + cpu.ebx * 1);
        x86::reg8 tmp2 = x86::reg8(x86::sreg8(0 /*0x0*/));
        x86::reg8 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 7);
        cpu.flags.of ^= 1 & (result >> 7);
        cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
        cpu.set_szp(result);
    }
    // 0052bf04  7405                   -je 0x52bf0b
    if (cpu.flags.zf)
    {
        goto L_0x0052bf0b;
    }
    // 0052bf06  e8e5bafcff             -call 0x4f79f0
    cpu.esp -= 4;
    nfs3hp::watcom::nfree(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x0052bf0b:
    // 0052bf0b  c70200000000           -mov dword ptr [edx], 0
    app->getMemory<x86::reg32>(cpu.edx) = 0 /*0x0*/;
L_0x0052bf11:
    // 0052bf11  83c204                 -add edx, 4
    (cpu.edx) += x86::reg32(x86::sreg32(4 /*0x4*/));
L_0x0052bf14:
    // 0052bf14  8b02                   -mov eax, dword ptr [edx]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edx);
    // 0052bf16  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0052bf18  75ca                   -jne 0x52bee4
    if (!cpu.flags.zf)
    {
        goto L_0x0052bee4;
    }
    // 0052bf1a  833d50b1a00000         +cmp dword ptr [0xa0b150], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(10531152) /* 0xa0b150 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0052bf21  750c                   -jne 0x52bf2f
    if (!cpu.flags.zf)
    {
        goto L_0x0052bf2f;
    }
    // 0052bf23  b805000000             -mov eax, 5
    cpu.eax = 5 /*0x5*/;
    // 0052bf28  e8d3b9fcff             -call 0x4f7900
    cpu.esp -= 4;
    nfs3hp::watcom::nmalloc(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052bf2d  eb0f                   -jmp 0x52bf3e
    goto L_0x0052bf3e;
L_0x0052bf2f:
    // 0052bf2f  ba05000000             -mov edx, 5
    cpu.edx = 5 /*0x5*/;
    // 0052bf34  a154b1a000             -mov eax, dword ptr [0xa0b154]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(10531156) /* 0xa0b154 */);
    // 0052bf39  e882c6feff             -call 0x5185c0
    cpu.esp -= 4;
    nfs3hp::watcom::nrealloc(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x0052bf3e:
    // 0052bf3e  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0052bf40  750a                   -jne 0x52bf4c
    if (!cpu.flags.zf)
    {
        goto L_0x0052bf4c;
    }
    // 0052bf42  b8ffffffff             -mov eax, 0xffffffff
    cpu.eax = 4294967295 /*0xffffffff*/;
    // 0052bf47  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052bf48  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052bf49  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052bf4a  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052bf4b  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x0052bf4c:
    // 0052bf4c  a354b1a000             -mov dword ptr [0xa0b154], eax
    app->getMemory<x86::reg32>(x86::reg32(10531156) /* 0xa0b154 */) = cpu.eax;
    // 0052bf51  c70000000000           -mov dword ptr [eax], 0
    app->getMemory<x86::reg32>(cpu.eax) = 0 /*0x0*/;
    // 0052bf57  83c004                 -add eax, 4
    (cpu.eax) += x86::reg32(x86::sreg32(4 /*0x4*/));
    // 0052bf5a  a350b1a000             -mov dword ptr [0xa0b150], eax
    app->getMemory<x86::reg32>(x86::reg32(10531152) /* 0xa0b150 */) = cpu.eax;
    // 0052bf5f  c60000                 -mov byte ptr [eax], 0
    app->getMemory<x86::reg8>(cpu.eax) = 0 /*0x0*/;
L_0x0052bf62:
    // 0052bf62  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 0052bf64  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052bf65  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052bf66  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052bf67  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052bf68  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x00 0x00 0x00 0x00 0x00 0x00 0x00 */
void Application::sub_52bf70(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0052bf70  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 0052bf71  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 0052bf72  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 0052bf74  89d6                   -mov esi, edx
    cpu.esi = cpu.edx;
    // 0052bf76  85db                   +test ebx, ebx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & cpu.ebx));
    // 0052bf78  7505                   -jne 0x52bf7f
    if (!cpu.flags.zf)
    {
        goto L_0x0052bf7f;
    }
L_0x0052bf7a:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 0052bf7a  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 0052bf7c  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052bf7d  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052bf7e  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x0052bf7f:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 0052bf7f  668b01                 -mov ax, word ptr [ecx]
    cpu.ax = app->getMemory<x86::reg16>(cpu.ecx);
    // 0052bf82  668b16                 -mov dx, word ptr [esi]
    cpu.dx = app->getMemory<x86::reg16>(cpu.esi);
    // 0052bf85  f6c4ff                 +test ah, 0xff
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.ah & 255 /*0xff*/));
    // 0052bf88  7525                   -jne 0x52bfaf
    if (!cpu.flags.zf)
    {
        goto L_0x0052bfaf;
    }
    // 0052bf8a  f6c6ff                 +test dh, 0xff
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.dh & 255 /*0xff*/));
    // 0052bf8d  7520                   -jne 0x52bfaf
    if (!cpu.flags.zf)
    {
        goto L_0x0052bfaf;
    }
    // 0052bf8f  663d4100               +cmp ax, 0x41
    {
        x86::reg16 tmp1 = cpu.ax;
        x86::reg16 tmp2 = x86::reg16(x86::sreg16(65 /*0x41*/));
        x86::reg16 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 15);
        cpu.flags.of ^= 1 & (result >> 15);
        cpu.flags.of &= (1 & (tmp1 >> 15)) != (1 & (tmp2 >> 15));
        cpu.set_szp(result);
    }
    // 0052bf93  720b                   -jb 0x52bfa0
    if (cpu.flags.cf)
    {
        goto L_0x0052bfa0;
    }
    // 0052bf95  663d5a00               +cmp ax, 0x5a
    {
        x86::reg16 tmp1 = cpu.ax;
        x86::reg16 tmp2 = x86::reg16(x86::sreg16(90 /*0x5a*/));
        x86::reg16 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 15);
        cpu.flags.of ^= 1 & (result >> 15);
        cpu.flags.of &= (1 & (tmp1 >> 15)) != (1 & (tmp2 >> 15));
        cpu.set_szp(result);
    }
    // 0052bf99  7705                   -ja 0x52bfa0
    if (!cpu.flags.cf && !cpu.flags.zf)
    {
        goto L_0x0052bfa0;
    }
    // 0052bf9b  0520000000             -add eax, 0x20
    (cpu.eax) += x86::reg32(x86::sreg32(32 /*0x20*/));
L_0x0052bfa0:
    // 0052bfa0  6683fa41               +cmp dx, 0x41
    {
        x86::reg16 tmp1 = cpu.dx;
        x86::reg16 tmp2 = x86::reg16(x86::sreg16(65 /*0x41*/));
        x86::reg16 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 15);
        cpu.flags.of ^= 1 & (result >> 15);
        cpu.flags.of &= (1 & (tmp1 >> 15)) != (1 & (tmp2 >> 15));
        cpu.set_szp(result);
    }
    // 0052bfa4  7209                   -jb 0x52bfaf
    if (cpu.flags.cf)
    {
        goto L_0x0052bfaf;
    }
    // 0052bfa6  6683fa5a               +cmp dx, 0x5a
    {
        x86::reg16 tmp1 = cpu.dx;
        x86::reg16 tmp2 = x86::reg16(x86::sreg16(90 /*0x5a*/));
        x86::reg16 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 15);
        cpu.flags.of ^= 1 & (result >> 15);
        cpu.flags.of &= (1 & (tmp1 >> 15)) != (1 & (tmp2 >> 15));
        cpu.set_szp(result);
    }
    // 0052bfaa  7703                   -ja 0x52bfaf
    if (!cpu.flags.cf && !cpu.flags.zf)
    {
        goto L_0x0052bfaf;
    }
    // 0052bfac  83c220                 -add edx, 0x20
    (cpu.edx) += x86::reg32(x86::sreg32(32 /*0x20*/));
L_0x0052bfaf:
    // 0052bfaf  6639d0                 +cmp ax, dx
    {
        x86::reg16 tmp1 = cpu.ax;
        x86::reg16 tmp2 = x86::reg16(x86::sreg16(cpu.dx));
        x86::reg16 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 15);
        cpu.flags.of ^= 1 & (result >> 15);
        cpu.flags.of &= (1 & (tmp1 >> 15)) != (1 & (tmp2 >> 15));
        cpu.set_szp(result);
    }
    // 0052bfb2  740f                   -je 0x52bfc3
    if (cpu.flags.zf)
    {
        goto L_0x0052bfc3;
    }
    // 0052bfb4  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
    // 0052bfb6  25ffff0000             -and eax, 0xffff
    cpu.eax &= x86::reg32(x86::sreg32(65535 /*0xffff*/));
    // 0052bfbb  6689d3                 -mov bx, dx
    cpu.bx = cpu.dx;
    // 0052bfbe  29d8                   -sub eax, ebx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.ebx));
    // 0052bfc0  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052bfc1  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052bfc2  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x0052bfc3:
    // 0052bfc3  6685d2                 +test dx, dx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg16>(cpu.dx & cpu.dx));
    // 0052bfc6  7505                   -jne 0x52bfcd
    if (!cpu.flags.zf)
    {
        goto L_0x0052bfcd;
    }
    // 0052bfc8  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 0052bfca  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052bfcb  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052bfcc  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x0052bfcd:
    // 0052bfcd  83c102                 -add ecx, 2
    (cpu.ecx) += x86::reg32(x86::sreg32(2 /*0x2*/));
    // 0052bfd0  83c602                 +add esi, 2
    {
        x86::reg32& tmp1 = cpu.esi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(2 /*0x2*/));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 0052bfd3  4b                     +dec ebx
    {
        x86::reg32& tmp = cpu.ebx;
        cpu.flags.of = 1 & (tmp >> 31);
        tmp--;
        cpu.flags.of &= ~(1 & (tmp >> 31));
        cpu.set_szp(tmp);
    }
    // 0052bfd4  74a4                   -je 0x52bf7a
    if (cpu.flags.zf)
    {
        goto L_0x0052bf7a;
    }
    // 0052bfd6  eba7                   -jmp 0x52bf7f
    goto L_0x0052bf7f;
}

/* align: skip 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 */
void Application::sub_52bfe0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0052bfe0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 0052bfe1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 0052bfe2  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 0052bfe3  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 0052bfe4  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 0052bfe5  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 0052bfe6  83ec10                 -sub esp, 0x10
    (cpu.esp) -= x86::reg32(x86::sreg32(16 /*0x10*/));
    // 0052bfe9  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 0052bfeb  ba02000000             -mov edx, 2
    cpu.edx = 2 /*0x2*/;
    // 0052bff0  89542404               -mov dword ptr [esp + 4], edx
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(4) /* 0x4 */) = cpu.edx;
    // 0052bff4  891424                 -mov dword ptr [esp], edx
    app->getMemory<x86::reg32>(cpu.esp) = cpu.edx;
    // 0052bff7  ba3d000000             -mov edx, 0x3d
    cpu.edx = 61 /*0x3d*/;
    // 0052bffc  e83f2b0000             -call 0x52eb40
    cpu.esp -= 4;
    sub_52eb40(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052c001  89c7                   -mov edi, eax
    cpu.edi = cpu.eax;
    // 0052c003  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0052c005  750a                   -jne 0x52c011
    if (!cpu.flags.zf)
    {
        goto L_0x0052c011;
    }
    // 0052c007  b8ffffffff             -mov eax, 0xffffffff
    cpu.eax = 4294967295 /*0xffffffff*/;
    // 0052c00c  e95a010000             -jmp 0x52c16b
    goto L_0x0052c16b;
L_0x0052c011:
    // 0052c011  39c8                   +cmp eax, ecx
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
    // 0052c013  750f                   -jne 0x52c024
    if (!cpu.flags.zf)
    {
        goto L_0x0052c024;
    }
    // 0052c015  b8ffffffff             -mov eax, 0xffffffff
    cpu.eax = 4294967295 /*0xffffffff*/;
    // 0052c01a  83c410                 -add esp, 0x10
    (cpu.esp) += x86::reg32(x86::sreg32(16 /*0x10*/));
    // 0052c01d  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c01e  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c01f  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c020  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c021  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c022  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c023  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x0052c024:
    // 0052c024  29c8                   -sub eax, ecx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.ecx));
    // 0052c026  d1f8                   -sar eax, 1
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (1 /*0x1*/ % 32));
    // 0052c028  8d2c4500000000         -lea ebp, [eax*2]
    cpu.ebp = x86::reg32(cpu.eax * 2);
    // 0052c02f  8d4502                 -lea eax, [ebp + 2]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(2) /* 0x2 */);
    // 0052c032  e8c9b8fcff             -call 0x4f7900
    cpu.esp -= 4;
    nfs3hp::watcom::nmalloc(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052c037  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 0052c039  89442408               -mov dword ptr [esp + 8], eax
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(8) /* 0x8 */) = cpu.eax;
    // 0052c03d  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0052c03f  750f                   -jne 0x52c050
    if (!cpu.flags.zf)
    {
        goto L_0x0052c050;
    }
    // 0052c041  b8ffffffff             -mov eax, 0xffffffff
    cpu.eax = 4294967295 /*0xffffffff*/;
    // 0052c046  83c410                 -add esp, 0x10
    (cpu.esp) += x86::reg32(x86::sreg32(16 /*0x10*/));
    // 0052c049  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c04a  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c04b  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c04c  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c04d  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c04e  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c04f  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x0052c050:
    // 0052c050  89eb                   -mov ebx, ebp
    cpu.ebx = cpu.ebp;
    // 0052c052  89ca                   -mov edx, ecx
    cpu.edx = cpu.ecx;
    // 0052c054  e8c792ffff             -call 0x525320
    cpu.esp -= 4;
    nfs3hp::watcom::memcpy(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052c059  8d5702                 -lea edx, [edi + 2]
    cpu.edx = x86::reg32(cpu.edi + x86::reg32(2) /* 0x2 */);
    // 0052c05c  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 0052c05e  66c7042e0000           -mov word ptr [esi + ebp], 0
    app->getMemory<x86::reg16>(cpu.esi + cpu.ebp * 1) = 0 /*0x0*/;
    // 0052c064  e89792ffff             -call 0x525300
    cpu.esp -= 4;
    nfs3hp::watcom::wcslen(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052c069  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0052c06b  7442                   -je 0x52c0af
    if (cpu.flags.zf)
    {
        goto L_0x0052c0af;
    }
    // 0052c06d  01c0                   -add eax, eax
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.eax));
    // 0052c06f  8944240c               -mov dword ptr [esp + 0xc], eax
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(12) /* 0xc */) = cpu.eax;
    // 0052c073  83c002                 -add eax, 2
    (cpu.eax) += x86::reg32(x86::sreg32(2 /*0x2*/));
    // 0052c076  e885b8fcff             -call 0x4f7900
    cpu.esp -= 4;
    nfs3hp::watcom::nmalloc(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052c07b  89c7                   -mov edi, eax
    cpu.edi = cpu.eax;
    // 0052c07d  89c5                   -mov ebp, eax
    cpu.ebp = cpu.eax;
    // 0052c07f  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0052c081  7516                   -jne 0x52c099
    if (!cpu.flags.zf)
    {
        goto L_0x0052c099;
    }
    // 0052c083  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 0052c085  e866b9fcff             -call 0x4f79f0
    cpu.esp -= 4;
    nfs3hp::watcom::nfree(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052c08a  b8ffffffff             -mov eax, 0xffffffff
    cpu.eax = 4294967295 /*0xffffffff*/;
    // 0052c08f  83c410                 -add esp, 0x10
    (cpu.esp) += x86::reg32(x86::sreg32(16 /*0x10*/));
    // 0052c092  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c093  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c094  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c095  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c096  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c097  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c098  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x0052c099:
    // 0052c099  8b74240c               -mov esi, dword ptr [esp + 0xc]
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(12) /* 0xc */);
    // 0052c09d  8b5c240c               -mov ebx, dword ptr [esp + 0xc]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(12) /* 0xc */);
    // 0052c0a1  01f7                   +add edi, esi
    {
        x86::reg32& tmp1 = cpu.edi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.esi));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 0052c0a3  e87892ffff             -call 0x525320
    cpu.esp -= 4;
    nfs3hp::watcom::memcpy(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052c0a8  66c7070000             -mov word ptr [edi], 0
    app->getMemory<x86::reg16>(cpu.edi) = 0 /*0x0*/;
    // 0052c0ad  eb02                   -jmp 0x52c0b1
    goto L_0x0052c0b1;
L_0x0052c0af:
    // 0052c0af  31ed                   -xor ebp, ebp
    cpu.ebp ^= x86::reg32(x86::sreg32(cpu.ebp));
L_0x0052c0b1:
    // 0052c0b1  8b442408               -mov eax, dword ptr [esp + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(8) /* 0x8 */);
    // 0052c0b5  89ea                   -mov edx, ebp
    cpu.edx = cpu.ebp;
    // 0052c0b7  e8e490ffff             -call 0x5251a0
    cpu.esp -= 4;
    sub_5251a0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052c0bc  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 0052c0be  8b442408               -mov eax, dword ptr [esp + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(8) /* 0x8 */);
    // 0052c0c2  e829b9fcff             -call 0x4f79f0
    cpu.esp -= 4;
    nfs3hp::watcom::nfree(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052c0c7  89e8                   -mov eax, ebp
    cpu.eax = cpu.ebp;
    // 0052c0c9  e822b9fcff             -call 0x4f79f0
    cpu.esp -= 4;
    nfs3hp::watcom::nfree(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052c0ce  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 0052c0d0  750f                   -jne 0x52c0e1
    if (!cpu.flags.zf)
    {
        goto L_0x0052c0e1;
    }
    // 0052c0d2  b8ffffffff             -mov eax, 0xffffffff
    cpu.eax = 4294967295 /*0xffffffff*/;
    // 0052c0d7  83c410                 -add esp, 0x10
    (cpu.esp) += x86::reg32(x86::sreg32(16 /*0x10*/));
    // 0052c0da  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c0db  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c0dc  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c0dd  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c0de  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c0df  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c0e0  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x0052c0e1:
    // 0052c0e1  833d58b1a00000         +cmp dword ptr [0xa0b158], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(10531160) /* 0xa0b158 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0052c0e8  7505                   -jne 0x52c0ef
    if (!cpu.flags.zf)
    {
        goto L_0x0052c0ef;
    }
    // 0052c0ea  e8b191ffff             -call 0x5252a0
    cpu.esp -= 4;
    nfs3hp::watcom::create_wide_environment(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x0052c0ef:
    // 0052c0ef  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 0052c0f1  e882000000             -call 0x52c178
    cpu.esp -= 4;
    nfs3hp::watcom::wputenv(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052c0f6  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0052c0f8  740f                   -je 0x52c109
    if (cpu.flags.zf)
    {
        goto L_0x0052c109;
    }
    // 0052c0fa  b8ffffffff             -mov eax, 0xffffffff
    cpu.eax = 4294967295 /*0xffffffff*/;
    // 0052c0ff  83c410                 -add esp, 0x10
    (cpu.esp) += x86::reg32(x86::sreg32(16 /*0x10*/));
    // 0052c102  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c103  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c104  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c105  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c106  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c107  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c108  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x0052c109:
    // 0052c109  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 0052c10b  e8f091ffff             -call 0x525300
    cpu.esp -= 4;
    nfs3hp::watcom::wcslen(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052c110  8d5801                 -lea ebx, [eax + 1]
    cpu.ebx = x86::reg32(cpu.eax + x86::reg32(1) /* 0x1 */);
    // 0052c113  8b442404               -mov eax, dword ptr [esp + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(4) /* 0x4 */);
    // 0052c117  0fafc3                 -imul eax, ebx
    cpu.eax = x86::reg32(x86::sreg64(x86::sreg32(cpu.eax)) * x86::sreg64(x86::sreg32(cpu.ebx)));
    // 0052c11a  e8e1b7fcff             -call 0x4f7900
    cpu.esp -= 4;
    nfs3hp::watcom::nmalloc(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052c11f  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 0052c121  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0052c123  7519                   -jne 0x52c13e
    if (!cpu.flags.zf)
    {
        goto L_0x0052c13e;
    }
    // 0052c125  b805000000             -mov eax, 5
    cpu.eax = 5 /*0x5*/;
    // 0052c12a  e85d4efdff             -call 0x500f8c
    cpu.esp -= 4;
    nfs3hp::watcom::set_errno_dos(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052c12f  b8ffffffff             -mov eax, 0xffffffff
    cpu.eax = 4294967295 /*0xffffffff*/;
    // 0052c134  83c410                 -add esp, 0x10
    (cpu.esp) += x86::reg32(x86::sreg32(16 /*0x10*/));
    // 0052c137  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c138  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c139  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c13a  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c13b  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c13c  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c13d  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x0052c13e:
    // 0052c13e  0faf1c24               -imul ebx, dword ptr [esp]
    cpu.ebx = x86::reg32(x86::sreg64(x86::sreg32(cpu.ebx)) * x86::sreg64(x86::sreg32(app->getMemory<x86::reg32>(cpu.esp))));
    // 0052c142  89ca                   -mov edx, ecx
    cpu.edx = cpu.ecx;
    // 0052c144  e8a781ffff             -call 0x5242f0
    cpu.esp -= 4;
    nfs3hp::watcom::wcstombs(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052c149  83f8ff                 +cmp eax, -1
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
    // 0052c14c  7516                   -jne 0x52c164
    if (!cpu.flags.zf)
    {
        goto L_0x0052c164;
    }
    // 0052c14e  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 0052c150  e89bb8fcff             -call 0x4f79f0
    cpu.esp -= 4;
    nfs3hp::watcom::nfree(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052c155  b8ffffffff             -mov eax, 0xffffffff
    cpu.eax = 4294967295 /*0xffffffff*/;
    // 0052c15a  83c410                 -add esp, 0x10
    (cpu.esp) += x86::reg32(x86::sreg32(16 /*0x10*/));
    // 0052c15d  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c15e  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c15f  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c160  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c161  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c162  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c163  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x0052c164:
    // 0052c164  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 0052c166  e821270000             -call 0x52e88c
    cpu.esp -= 4;
    sub_52e88c(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x0052c16b:
    // 0052c16b  83c410                 -add esp, 0x10
    (cpu.esp) += x86::reg32(x86::sreg32(16 /*0x10*/));
    // 0052c16e  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c16f  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c170  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c171  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c172  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c173  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c174  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_52c178: native, nfs3hp::watcom::wputenv */

/* sub_52c300: native, nfs3hp::watcom::wputenvFind */

/* align: skip 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 */
void Application::sub_52c410(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0052c410  8b402c                 -mov eax, dword ptr [eax + 0x2c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(44) /* 0x2c */);
    // 0052c413  8b400c                 -mov eax, dword ptr [eax + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
    // 0052c416  83e002                 -and eax, 2
    cpu.eax &= x86::reg32(x86::sreg32(2 /*0x2*/));
    // 0052c419  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 */
void Application::sub_52c420(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0052c420  8b402c                 -mov eax, dword ptr [eax + 0x2c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(44) /* 0x2c */);
    // 0052c423  8b400c                 -mov eax, dword ptr [eax + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
    // 0052c426  83e004                 -and eax, 4
    cpu.eax &= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 0052c429  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 */
void Application::sub_52c430(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0052c430  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 0052c431  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 0052c432  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 0052c433  83ec1c                 -sub esp, 0x1c
    (cpu.esp) -= x86::reg32(x86::sreg32(28 /*0x1c*/));
    // 0052c436  89d6                   -mov esi, edx
    cpu.esi = cpu.edx;
    // 0052c438  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 0052c43a  c1ea10                 -shr edx, 0x10
    cpu.edx >>= 16 /*0x10*/ % 32;
    // 0052c43d  81e2ff000000           -and edx, 0xff
    cpu.edx &= x86::reg32(x86::sreg32(255 /*0xff*/));
    // 0052c443  89c7                   -mov edi, eax
    cpu.edi = cpu.eax;
    // 0052c445  89542418               -mov dword ptr [esp + 0x18], edx
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(24) /* 0x18 */) = cpu.edx;
    // 0052c449  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 0052c44b  25ff000000             -and eax, 0xff
    cpu.eax &= x86::reg32(x86::sreg32(255 /*0xff*/));
    // 0052c450  8944240c               -mov dword ptr [esp + 0xc], eax
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(12) /* 0xc */) = cpu.eax;
    // 0052c454  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 0052c456  c1ea08                 -shr edx, 8
    cpu.edx >>= 8 /*0x8*/ % 32;
    // 0052c459  c1e810                 -shr eax, 0x10
    cpu.eax >>= 16 /*0x10*/ % 32;
    // 0052c45c  81e2ff000000           -and edx, 0xff
    cpu.edx &= x86::reg32(x86::sreg32(255 /*0xff*/));
    // 0052c462  25ff000000             -and eax, 0xff
    cpu.eax &= x86::reg32(x86::sreg32(255 /*0xff*/));
    // 0052c467  89542408               -mov dword ptr [esp + 8], edx
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(8) /* 0x8 */) = cpu.edx;
    // 0052c46b  89442410               -mov dword ptr [esp + 0x10], eax
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(16) /* 0x10 */) = cpu.eax;
    // 0052c46f  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 0052c471  89da                   -mov edx, ebx
    cpu.edx = cpu.ebx;
    // 0052c473  c1e808                 -shr eax, 8
    cpu.eax >>= 8 /*0x8*/ % 32;
    // 0052c476  c1ea18                 -shr edx, 0x18
    cpu.edx >>= 24 /*0x18*/ % 32;
    // 0052c479  25ff000000             -and eax, 0xff
    cpu.eax &= x86::reg32(x86::sreg32(255 /*0xff*/));
    // 0052c47e  81e2ff000000           -and edx, 0xff
    cpu.edx &= x86::reg32(x86::sreg32(255 /*0xff*/));
    // 0052c484  89442414               -mov dword ptr [esp + 0x14], eax
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(20) /* 0x14 */) = cpu.eax;
    // 0052c488  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 0052c48a  0fafc1                 -imul eax, ecx
    cpu.eax = x86::reg32(x86::sreg64(x86::sreg32(cpu.eax)) * x86::sreg64(x86::sreg32(cpu.ecx)));
    // 0052c48d  c1ef18                 -shr edi, 0x18
    cpu.edi >>= 24 /*0x18*/ % 32;
    // 0052c490  81e3ff000000           -and ebx, 0xff
    cpu.ebx &= x86::reg32(x86::sreg32(255 /*0xff*/));
    // 0052c496  81e7ff000000           -and edi, 0xff
    cpu.edi &= x86::reg32(x86::sreg32(255 /*0xff*/));
    // 0052c49c  895c2404               -mov dword ptr [esp + 4], ebx
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(4) /* 0x4 */) = cpu.ebx;
    // 0052c4a0  8d1c0e                 -lea ebx, [esi + ecx]
    cpu.ebx = x86::reg32(cpu.esi + cpu.ecx * 1);
    // 0052c4a3  89fa                   -mov edx, edi
    cpu.edx = cpu.edi;
    // 0052c4a5  0fafd6                 -imul edx, esi
    cpu.edx = x86::reg32(x86::sreg64(x86::sreg32(cpu.edx)) * x86::sreg64(x86::sreg32(cpu.esi)));
    // 0052c4a8  01c2                   -add edx, eax
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.eax));
    // 0052c4aa  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 0052c4ac  c1fa1f                 -sar edx, 0x1f
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (31 /*0x1f*/ % 32));
    // 0052c4af  f7fb                   -idiv ebx
    {
        x86::sreg64 tmp = x86::sreg64(cpu.edx_eax);
        x86::sreg32 d = x86::sreg32(cpu.ebx);
        cpu.edx_eax = x86::reg64(tmp / d);
        cpu.edx = x86::reg32(tmp % d);
    }
    // 0052c4b1  3dff000000             +cmp eax, 0xff
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
    // 0052c4b6  0f8e93000000           -jle 0x52c54f
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x0052c54f;
    }
    // 0052c4bc  b8ff000000             -mov eax, 0xff
    cpu.eax = 255 /*0xff*/;
L_0x0052c4c1:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 0052c4c1  8b542418               -mov edx, dword ptr [esp + 0x18]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(24) /* 0x18 */);
    // 0052c4c5  0fafd6                 -imul edx, esi
    cpu.edx = x86::reg32(x86::sreg64(x86::sreg32(cpu.edx)) * x86::sreg64(x86::sreg32(cpu.esi)));
    // 0052c4c8  89c7                   -mov edi, eax
    cpu.edi = cpu.eax;
    // 0052c4ca  8b442410               -mov eax, dword ptr [esp + 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(16) /* 0x10 */);
    // 0052c4ce  0fafc1                 -imul eax, ecx
    cpu.eax = x86::reg32(x86::sreg64(x86::sreg32(cpu.eax)) * x86::sreg64(x86::sreg32(cpu.ecx)));
    // 0052c4d1  01c2                   -add edx, eax
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.eax));
    // 0052c4d3  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 0052c4d5  c1fa1f                 -sar edx, 0x1f
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (31 /*0x1f*/ % 32));
    // 0052c4d8  f7fb                   -idiv ebx
    {
        x86::sreg64 tmp = x86::sreg64(cpu.edx_eax);
        x86::sreg32 d = x86::sreg32(cpu.ebx);
        cpu.edx_eax = x86::reg64(tmp / d);
        cpu.edx = x86::reg32(tmp % d);
    }
    // 0052c4da  3dff000000             +cmp eax, 0xff
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
    // 0052c4df  0f8e79000000           -jle 0x52c55e
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x0052c55e;
    }
    // 0052c4e5  b8ff000000             -mov eax, 0xff
    cpu.eax = 255 /*0xff*/;
L_0x0052c4ea:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 0052c4ea  8b542414               -mov edx, dword ptr [esp + 0x14]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(20) /* 0x14 */);
    // 0052c4ee  0fafd1                 -imul edx, ecx
    cpu.edx = x86::reg32(x86::sreg64(x86::sreg32(cpu.edx)) * x86::sreg64(x86::sreg32(cpu.ecx)));
    // 0052c4f1  890424                 -mov dword ptr [esp], eax
    app->getMemory<x86::reg32>(cpu.esp) = cpu.eax;
    // 0052c4f4  8b442408               -mov eax, dword ptr [esp + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(8) /* 0x8 */);
    // 0052c4f8  0fafc6                 -imul eax, esi
    cpu.eax = x86::reg32(x86::sreg64(x86::sreg32(cpu.eax)) * x86::sreg64(x86::sreg32(cpu.esi)));
    // 0052c4fb  01c2                   -add edx, eax
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.eax));
    // 0052c4fd  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 0052c4ff  c1fa1f                 -sar edx, 0x1f
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (31 /*0x1f*/ % 32));
    // 0052c502  f7fb                   -idiv ebx
    {
        x86::sreg64 tmp = x86::sreg64(cpu.edx_eax);
        x86::sreg32 d = x86::sreg32(cpu.ebx);
        cpu.edx_eax = x86::reg64(tmp / d);
        cpu.edx = x86::reg32(tmp % d);
    }
    // 0052c504  3dff000000             +cmp eax, 0xff
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
    // 0052c509  7e5b                   -jle 0x52c566
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x0052c566;
    }
    // 0052c50b  b8ff000000             -mov eax, 0xff
    cpu.eax = 255 /*0xff*/;
L_0x0052c510:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 0052c510  0faf4c2404             -imul ecx, dword ptr [esp + 4]
    cpu.ecx = x86::reg32(x86::sreg64(x86::sreg32(cpu.ecx)) * x86::sreg64(x86::sreg32(app->getMemory<x86::reg32>(cpu.esp + x86::reg32(4) /* 0x4 */))));
    // 0052c515  8b54240c               -mov edx, dword ptr [esp + 0xc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(12) /* 0xc */);
    // 0052c519  0fafd6                 -imul edx, esi
    cpu.edx = x86::reg32(x86::sreg64(x86::sreg32(cpu.edx)) * x86::sreg64(x86::sreg32(cpu.esi)));
    // 0052c51c  01ca                   -add edx, ecx
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.ecx));
    // 0052c51e  89c5                   -mov ebp, eax
    cpu.ebp = cpu.eax;
    // 0052c520  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 0052c522  c1fa1f                 -sar edx, 0x1f
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (31 /*0x1f*/ % 32));
    // 0052c525  f7fb                   -idiv ebx
    {
        x86::sreg64 tmp = x86::sreg64(cpu.edx_eax);
        x86::sreg32 d = x86::sreg32(cpu.ebx);
        cpu.edx_eax = x86::reg64(tmp / d);
        cpu.edx = x86::reg32(tmp % d);
    }
    // 0052c527  3dff000000             +cmp eax, 0xff
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
    // 0052c52c  7f40                   -jg 0x52c56e
    if (!cpu.flags.zf && (cpu.flags.sf == cpu.flags.of))
    {
        goto L_0x0052c56e;
    }
    // 0052c52e  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0052c530  7c43                   -jl 0x52c575
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x0052c575;
    }
L_0x0052c532:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 0052c532  8b0c24                 -mov ecx, dword ptr [esp]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    // 0052c535  89fa                   -mov edx, edi
    cpu.edx = cpu.edi;
    // 0052c537  c1e110                 -shl ecx, 0x10
    cpu.ecx <<= 16 /*0x10*/ % 32;
    // 0052c53a  c1e218                 -shl edx, 0x18
    cpu.edx <<= 24 /*0x18*/ % 32;
    // 0052c53d  09d1                   -or ecx, edx
    cpu.ecx |= x86::reg32(x86::sreg32(cpu.edx));
    // 0052c53f  89ea                   -mov edx, ebp
    cpu.edx = cpu.ebp;
    // 0052c541  c1e208                 -shl edx, 8
    cpu.edx <<= 8 /*0x8*/ % 32;
    // 0052c544  09ca                   -or edx, ecx
    cpu.edx |= x86::reg32(x86::sreg32(cpu.ecx));
    // 0052c546  09d0                   -or eax, edx
    cpu.eax |= x86::reg32(x86::sreg32(cpu.edx));
    // 0052c548  83c41c                 -add esp, 0x1c
    (cpu.esp) += x86::reg32(x86::sreg32(28 /*0x1c*/));
    // 0052c54b  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c54c  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c54d  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c54e  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x0052c54f:
    // 0052c54f  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0052c551  0f8d6affffff           -jge 0x52c4c1
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x0052c4c1;
    }
    // 0052c557  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
    // 0052c559  e963ffffff             -jmp 0x52c4c1
    goto L_0x0052c4c1;
L_0x0052c55e:
    // 0052c55e  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0052c560  7d88                   -jge 0x52c4ea
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x0052c4ea;
    }
    // 0052c562  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
    // 0052c564  eb84                   -jmp 0x52c4ea
    goto L_0x0052c4ea;
L_0x0052c566:
    // 0052c566  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0052c568  7da6                   -jge 0x52c510
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x0052c510;
    }
    // 0052c56a  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
    // 0052c56c  eba2                   -jmp 0x52c510
    goto L_0x0052c510;
L_0x0052c56e:
    // 0052c56e  b8ff000000             -mov eax, 0xff
    cpu.eax = 255 /*0xff*/;
    // 0052c573  ebbd                   -jmp 0x52c532
    goto L_0x0052c532;
L_0x0052c575:
    // 0052c575  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
    // 0052c577  ebb9                   -jmp 0x52c532
    goto L_0x0052c532;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x90 */
void Application::sub_52c580(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0052c580  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 0052c581  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 0052c582  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 0052c583  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 0052c584  83ec08                 -sub esp, 8
    (cpu.esp) -= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 0052c587  89542404               -mov dword ptr [esp + 4], edx
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(4) /* 0x4 */) = cpu.edx;
    // 0052c58b  f7c3000000ff           +test ebx, 0xff000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & 4278190080 /*0xff000000*/));
    // 0052c591  7431                   -je 0x52c5c4
    if (cpu.flags.zf)
    {
        goto L_0x0052c5c4;
    }
L_0x0052c593:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 0052c593  bf0f000000             -mov edi, 0xf
    cpu.edi = 15 /*0xf*/;
    // 0052c598  89c5                   -mov ebp, eax
    cpu.ebp = cpu.eax;
    // 0052c59a  891c24                 -mov dword ptr [esp], ebx
    app->getMemory<x86::reg32>(cpu.esp) = cpu.ebx;
    // 0052c59d  31f6                   -xor esi, esi
    cpu.esi ^= x86::reg32(x86::sreg32(cpu.esi));
L_0x0052c59f:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 0052c59f  8b1c24                 -mov ebx, dword ptr [esp]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    // 0052c5a2  8b442404               -mov eax, dword ptr [esp + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(4) /* 0x4 */);
    // 0052c5a6  89f9                   -mov ecx, edi
    cpu.ecx = cpu.edi;
    // 0052c5a8  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 0052c5aa  e881feffff             -call 0x52c430
    cpu.esp -= 4;
    sub_52c430(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052c5af  83c504                 -add ebp, 4
    (cpu.ebp) += x86::reg32(x86::sreg32(4 /*0x4*/));
    // 0052c5b2  4f                     -dec edi
    (cpu.edi)--;
    // 0052c5b3  46                     -inc esi
    (cpu.esi)++;
    // 0052c5b4  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 0052c5b7  83fe10                 +cmp esi, 0x10
    {
        x86::reg32 tmp1 = cpu.esi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(16 /*0x10*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0052c5ba  7ce3                   -jl 0x52c59f
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x0052c59f;
    }
    // 0052c5bc  83c408                 -add esp, 8
    (cpu.esp) += x86::reg32(x86::sreg32(8 /*0x8*/));
    // 0052c5bf  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c5c0  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c5c1  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c5c2  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c5c3  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x0052c5c4:
    // 0052c5c4  89d3                   -mov ebx, edx
    cpu.ebx = cpu.edx;
    // 0052c5c6  81e3ffffff00           +and ebx, 0xffffff
    cpu.clear_co();
    cpu.set_szp((cpu.ebx &= x86::reg32(x86::sreg32(16777215 /*0xffffff*/))));
    // 0052c5cc  ebc5                   -jmp 0x52c593
    goto L_0x0052c593;
}

/* align: skip 0x8b 0xc0 */
void Application::sub_52c5d0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0052c5d0  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 0052c5d1  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 0052c5d2  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 0052c5d3  83ec08                 -sub esp, 8
    (cpu.esp) -= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 0052c5d6  89c7                   -mov edi, eax
    cpu.edi = cpu.eax;
    // 0052c5d8  89d6                   -mov esi, edx
    cpu.esi = cpu.edx;
    // 0052c5da  89cd                   -mov ebp, ecx
    cpu.ebp = cpu.ecx;
    // 0052c5dc  f7c3000000ff           +test ebx, 0xff000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & 4278190080 /*0xff000000*/));
    // 0052c5e2  0f8524010000           -jne 0x52c70c
    if (!cpu.flags.zf)
    {
        goto L_0x0052c70c;
    }
    // 0052c5e8  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 0052c5ea  89542404               -mov dword ptr [esp + 4], edx
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(4) /* 0x4 */) = cpu.edx;
    // 0052c5ee  891424                 -mov dword ptr [esp], edx
    app->getMemory<x86::reg32>(cpu.esp) = cpu.edx;
L_0x0052c5f1:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 0052c5f1  8b442404               -mov eax, dword ptr [esp + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(4) /* 0x4 */);
    // 0052c5f5  b901000000             -mov ecx, 1
    cpu.ecx = 1 /*0x1*/;
    // 0052c5fa  8b1c24                 -mov ebx, dword ptr [esp]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    // 0052c5fd  ba03000000             -mov edx, 3
    cpu.edx = 3 /*0x3*/;
    // 0052c602  8907                   -mov dword ptr [edi], eax
    app->getMemory<x86::reg32>(cpu.edi) = cpu.eax;
    // 0052c604  89e8                   -mov eax, ebp
    cpu.eax = cpu.ebp;
    // 0052c606  896f04                 -mov dword ptr [edi + 4], ebp
    app->getMemory<x86::reg32>(cpu.edi + x86::reg32(4) /* 0x4 */) = cpu.ebp;
    // 0052c609  e822feffff             -call 0x52c430
    cpu.esp -= 4;
    sub_52c430(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052c60e  b902000000             -mov ecx, 2
    cpu.ecx = 2 /*0x2*/;
    // 0052c613  8b1c24                 -mov ebx, dword ptr [esp]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    // 0052c616  894708                 -mov dword ptr [edi + 8], eax
    app->getMemory<x86::reg32>(cpu.edi + x86::reg32(8) /* 0x8 */) = cpu.eax;
    // 0052c619  89ca                   -mov edx, ecx
    cpu.edx = cpu.ecx;
    // 0052c61b  89e8                   -mov eax, ebp
    cpu.eax = cpu.ebp;
    // 0052c61d  e80efeffff             -call 0x52c430
    cpu.esp -= 4;
    sub_52c430(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052c622  b903000000             -mov ecx, 3
    cpu.ecx = 3 /*0x3*/;
    // 0052c627  8b1c24                 -mov ebx, dword ptr [esp]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    // 0052c62a  ba01000000             -mov edx, 1
    cpu.edx = 1 /*0x1*/;
    // 0052c62f  89470c                 -mov dword ptr [edi + 0xc], eax
    app->getMemory<x86::reg32>(cpu.edi + x86::reg32(12) /* 0xc */) = cpu.eax;
    // 0052c632  89e8                   -mov eax, ebp
    cpu.eax = cpu.ebp;
    // 0052c634  e8f7fdffff             -call 0x52c430
    cpu.esp -= 4;
    sub_52c430(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052c639  b901000000             -mov ecx, 1
    cpu.ecx = 1 /*0x1*/;
    // 0052c63e  ba04000000             -mov edx, 4
    cpu.edx = 4 /*0x4*/;
    // 0052c643  89f3                   -mov ebx, esi
    cpu.ebx = cpu.esi;
    // 0052c645  894710                 -mov dword ptr [edi + 0x10], eax
    app->getMemory<x86::reg32>(cpu.edi + x86::reg32(16) /* 0x10 */) = cpu.eax;
    // 0052c648  8b442404               -mov eax, dword ptr [esp + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(4) /* 0x4 */);
    // 0052c64c  e8dffdffff             -call 0x52c430
    cpu.esp -= 4;
    sub_52c430(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052c651  b902000000             -mov ecx, 2
    cpu.ecx = 2 /*0x2*/;
    // 0052c656  ba03000000             -mov edx, 3
    cpu.edx = 3 /*0x3*/;
    // 0052c65b  89f3                   -mov ebx, esi
    cpu.ebx = cpu.esi;
    // 0052c65d  894714                 -mov dword ptr [edi + 0x14], eax
    app->getMemory<x86::reg32>(cpu.edi + x86::reg32(20) /* 0x14 */) = cpu.eax;
    // 0052c660  8b442404               -mov eax, dword ptr [esp + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(4) /* 0x4 */);
    // 0052c664  e8c7fdffff             -call 0x52c430
    cpu.esp -= 4;
    sub_52c430(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052c669  b903000000             -mov ecx, 3
    cpu.ecx = 3 /*0x3*/;
    // 0052c66e  ba02000000             -mov edx, 2
    cpu.edx = 2 /*0x2*/;
    // 0052c673  89f3                   -mov ebx, esi
    cpu.ebx = cpu.esi;
    // 0052c675  894718                 -mov dword ptr [edi + 0x18], eax
    app->getMemory<x86::reg32>(cpu.edi + x86::reg32(24) /* 0x18 */) = cpu.eax;
    // 0052c678  8b442404               -mov eax, dword ptr [esp + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(4) /* 0x4 */);
    // 0052c67c  e8affdffff             -call 0x52c430
    cpu.esp -= 4;
    sub_52c430(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052c681  89471c                 -mov dword ptr [edi + 0x1c], eax
    app->getMemory<x86::reg32>(cpu.edi + x86::reg32(28) /* 0x1c */) = cpu.eax;
    // 0052c684  b904000000             -mov ecx, 4
    cpu.ecx = 4 /*0x4*/;
    // 0052c689  ba01000000             -mov edx, 1
    cpu.edx = 1 /*0x1*/;
    // 0052c68e  8b442404               -mov eax, dword ptr [esp + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(4) /* 0x4 */);
    // 0052c692  89f3                   -mov ebx, esi
    cpu.ebx = cpu.esi;
    // 0052c694  e897fdffff             -call 0x52c430
    cpu.esp -= 4;
    sub_52c430(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052c699  b901000000             -mov ecx, 1
    cpu.ecx = 1 /*0x1*/;
    // 0052c69e  ba04000000             -mov edx, 4
    cpu.edx = 4 /*0x4*/;
    // 0052c6a3  89eb                   -mov ebx, ebp
    cpu.ebx = cpu.ebp;
    // 0052c6a5  894720                 -mov dword ptr [edi + 0x20], eax
    app->getMemory<x86::reg32>(cpu.edi + x86::reg32(32) /* 0x20 */) = cpu.eax;
    // 0052c6a8  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 0052c6aa  897724                 -mov dword ptr [edi + 0x24], esi
    app->getMemory<x86::reg32>(cpu.edi + x86::reg32(36) /* 0x24 */) = cpu.esi;
    // 0052c6ad  e87efdffff             -call 0x52c430
    cpu.esp -= 4;
    sub_52c430(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052c6b2  b902000000             -mov ecx, 2
    cpu.ecx = 2 /*0x2*/;
    // 0052c6b7  ba03000000             -mov edx, 3
    cpu.edx = 3 /*0x3*/;
    // 0052c6bc  89eb                   -mov ebx, ebp
    cpu.ebx = cpu.ebp;
    // 0052c6be  894728                 -mov dword ptr [edi + 0x28], eax
    app->getMemory<x86::reg32>(cpu.edi + x86::reg32(40) /* 0x28 */) = cpu.eax;
    // 0052c6c1  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 0052c6c3  e868fdffff             -call 0x52c430
    cpu.esp -= 4;
    sub_52c430(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052c6c8  b903000000             -mov ecx, 3
    cpu.ecx = 3 /*0x3*/;
    // 0052c6cd  ba02000000             -mov edx, 2
    cpu.edx = 2 /*0x2*/;
    // 0052c6d2  89eb                   -mov ebx, ebp
    cpu.ebx = cpu.ebp;
    // 0052c6d4  89472c                 -mov dword ptr [edi + 0x2c], eax
    app->getMemory<x86::reg32>(cpu.edi + x86::reg32(44) /* 0x2c */) = cpu.eax;
    // 0052c6d7  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 0052c6d9  e852fdffff             -call 0x52c430
    cpu.esp -= 4;
    sub_52c430(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052c6de  b904000000             -mov ecx, 4
    cpu.ecx = 4 /*0x4*/;
    // 0052c6e3  ba01000000             -mov edx, 1
    cpu.edx = 1 /*0x1*/;
    // 0052c6e8  89eb                   -mov ebx, ebp
    cpu.ebx = cpu.ebp;
    // 0052c6ea  894730                 -mov dword ptr [edi + 0x30], eax
    app->getMemory<x86::reg32>(cpu.edi + x86::reg32(48) /* 0x30 */) = cpu.eax;
    // 0052c6ed  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 0052c6ef  e83cfdffff             -call 0x52c430
    cpu.esp -= 4;
    sub_52c430(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052c6f4  c7473800000000         -mov dword ptr [edi + 0x38], 0
    app->getMemory<x86::reg32>(cpu.edi + x86::reg32(56) /* 0x38 */) = 0 /*0x0*/;
    // 0052c6fb  c7473c00000000         -mov dword ptr [edi + 0x3c], 0
    app->getMemory<x86::reg32>(cpu.edi + x86::reg32(60) /* 0x3c */) = 0 /*0x0*/;
    // 0052c702  894734                 -mov dword ptr [edi + 0x34], eax
    app->getMemory<x86::reg32>(cpu.edi + x86::reg32(52) /* 0x34 */) = cpu.eax;
    // 0052c705  83c408                 +add esp, 8
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
    // 0052c708  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c709  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c70a  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c70b  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x0052c70c:
    // 0052c70c  895c2404               -mov dword ptr [esp + 4], ebx
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(4) /* 0x4 */) = cpu.ebx;
    // 0052c710  891c24                 -mov dword ptr [esp], ebx
    app->getMemory<x86::reg32>(cpu.esp) = cpu.ebx;
    // 0052c713  e9d9feffff             -jmp 0x52c5f1
    goto L_0x0052c5f1;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8b 0xd2 */
void Application::sub_52c720(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0052c720  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 0052c721  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 0052c722  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 0052c723  83ec14                 -sub esp, 0x14
    (cpu.esp) -= x86::reg32(x86::sreg32(20 /*0x14*/));
    // 0052c726  890424                 -mov dword ptr [esp], eax
    app->getMemory<x86::reg32>(cpu.esp) = cpu.eax;
    // 0052c729  89542404               -mov dword ptr [esp + 4], edx
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(4) /* 0x4 */) = cpu.edx;
    // 0052c72d  89cf                   -mov edi, ecx
    cpu.edi = cpu.ecx;
    // 0052c72f  f7c3000000ff           +test ebx, 0xff000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & 4278190080 /*0xff000000*/));
    // 0052c735  746e                   -je 0x52c7a5
    if (cpu.flags.zf)
    {
        goto L_0x0052c7a5;
    }
L_0x0052c737:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 0052c737  8b0424                 -mov eax, dword ptr [esp]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp);
    // 0052c73a  bd08000000             -mov ebp, 8
    cpu.ebp = 8 /*0x8*/;
    // 0052c73f  895c2408               -mov dword ptr [esp + 8], ebx
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(8) /* 0x8 */) = cpu.ebx;
    // 0052c743  31f6                   -xor esi, esi
    cpu.esi ^= x86::reg32(x86::sreg32(cpu.esi));
    // 0052c745  8944240c               -mov dword ptr [esp + 0xc], eax
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(12) /* 0xc */) = cpu.eax;
L_0x0052c749:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 0052c749  8b442408               -mov eax, dword ptr [esp + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(8) /* 0x8 */);
    // 0052c74d  89f1                   -mov ecx, esi
    cpu.ecx = cpu.esi;
    // 0052c74f  89fb                   -mov ebx, edi
    cpu.ebx = cpu.edi;
    // 0052c751  89ea                   -mov edx, ebp
    cpu.edx = cpu.ebp;
    // 0052c753  e8d8fcffff             -call 0x52c430
    cpu.esp -= 4;
    sub_52c430(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052c758  8b5c240c               -mov ebx, dword ptr [esp + 0xc]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(12) /* 0xc */);
    // 0052c75c  4d                     -dec ebp
    (cpu.ebp)--;
    // 0052c75d  46                     -inc esi
    (cpu.esi)++;
    // 0052c75e  8d5304                 -lea edx, [ebx + 4]
    cpu.edx = x86::reg32(cpu.ebx + x86::reg32(4) /* 0x4 */);
    // 0052c761  8903                   -mov dword ptr [ebx], eax
    app->getMemory<x86::reg32>(cpu.ebx) = cpu.eax;
    // 0052c763  8954240c               -mov dword ptr [esp + 0xc], edx
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(12) /* 0xc */) = cpu.edx;
    // 0052c767  83fe07                 +cmp esi, 7
    {
        x86::reg32 tmp1 = cpu.esi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(7 /*0x7*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0052c76a  7edd                   -jle 0x52c749
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x0052c749;
    }
    // 0052c76c  8b0424                 -mov eax, dword ptr [esp]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp);
    // 0052c76f  bd07000000             -mov ebp, 7
    cpu.ebp = 7 /*0x7*/;
    // 0052c774  31f6                   -xor esi, esi
    cpu.esi ^= x86::reg32(x86::sreg32(cpu.esi));
    // 0052c776  89442410               -mov dword ptr [esp + 0x10], eax
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(16) /* 0x10 */) = cpu.eax;
L_0x0052c77a:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 0052c77a  8b5c2404               -mov ebx, dword ptr [esp + 4]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(4) /* 0x4 */);
    // 0052c77e  89f1                   -mov ecx, esi
    cpu.ecx = cpu.esi;
    // 0052c780  89ea                   -mov edx, ebp
    cpu.edx = cpu.ebp;
    // 0052c782  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 0052c784  e8a7fcffff             -call 0x52c430
    cpu.esp -= 4;
    sub_52c430(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052c789  8b5c2410               -mov ebx, dword ptr [esp + 0x10]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(16) /* 0x10 */);
    // 0052c78d  4d                     -dec ebp
    (cpu.ebp)--;
    // 0052c78e  46                     -inc esi
    (cpu.esi)++;
    // 0052c78f  8d4b04                 -lea ecx, [ebx + 4]
    cpu.ecx = x86::reg32(cpu.ebx + x86::reg32(4) /* 0x4 */);
    // 0052c792  894320                 -mov dword ptr [ebx + 0x20], eax
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(32) /* 0x20 */) = cpu.eax;
    // 0052c795  894c2410               -mov dword ptr [esp + 0x10], ecx
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(16) /* 0x10 */) = cpu.ecx;
    // 0052c799  83fe07                 +cmp esi, 7
    {
        x86::reg32 tmp1 = cpu.esi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(7 /*0x7*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0052c79c  7edc                   -jle 0x52c77a
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x0052c77a;
    }
    // 0052c79e  83c414                 -add esp, 0x14
    (cpu.esp) += x86::reg32(x86::sreg32(20 /*0x14*/));
    // 0052c7a1  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c7a2  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c7a3  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c7a4  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x0052c7a5:
    // 0052c7a5  89cb                   -mov ebx, ecx
    cpu.ebx = cpu.ecx;
    // 0052c7a7  81e3ffffff00           +and ebx, 0xffffff
    cpu.clear_co();
    cpu.set_szp((cpu.ebx &= x86::reg32(x86::sreg32(16777215 /*0xffffff*/))));
    // 0052c7ad  eb88                   -jmp 0x52c737
    goto L_0x0052c737;
}

/* align: skip 0x90 */
void Application::sub_52c7b0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0052c7b0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 0052c7b1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 0052c7b2  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 0052c7b3  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 0052c7b4  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 0052c7b6  e855fcffff             -call 0x52c410
    cpu.esp -= 4;
    sub_52c410(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052c7bb  8d727c                 -lea esi, [edx + 0x7c]
    cpu.esi = x86::reg32(cpu.edx + x86::reg32(124) /* 0x7c */);
    // 0052c7be  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0052c7c0  7520                   -jne 0x52c7e2
    if (!cpu.flags.zf)
    {
        goto L_0x0052c7e2;
    }
    // 0052c7c2  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 0052c7c4  e857fcffff             -call 0x52c420
    cpu.esp -= 4;
    sub_52c420(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052c7c9  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0052c7cb  742a                   -je 0x52c7f7
    if (cpu.flags.zf)
    {
        goto L_0x0052c7f7;
    }
    // 0052c7cd  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 0052c7cf  8b4a78                 -mov ecx, dword ptr [edx + 0x78]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(120) /* 0x78 */);
    // 0052c7d2  8b5a70                 -mov ebx, dword ptr [edx + 0x70]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(112) /* 0x70 */);
    // 0052c7d5  8b526c                 -mov edx, dword ptr [edx + 0x6c]
    cpu.edx = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(108) /* 0x6c */);
    // 0052c7d8  e843ffffff             -call 0x52c720
    cpu.esp -= 4;
    sub_52c720(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052c7dd  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c7de  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c7df  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c7e0  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c7e1  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x0052c7e2:
    // 0052c7e2  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 0052c7e4  8b4a74                 -mov ecx, dword ptr [edx + 0x74]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(116) /* 0x74 */);
    // 0052c7e7  8b5a70                 -mov ebx, dword ptr [edx + 0x70]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(112) /* 0x70 */);
    // 0052c7ea  8b526c                 -mov edx, dword ptr [edx + 0x6c]
    cpu.edx = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(108) /* 0x6c */);
    // 0052c7ed  e8defdffff             -call 0x52c5d0
    cpu.esp -= 4;
    sub_52c5d0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052c7f2  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c7f3  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c7f4  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c7f5  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c7f6  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x0052c7f7:
    // 0052c7f7  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 0052c7f9  8b5a70                 -mov ebx, dword ptr [edx + 0x70]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(112) /* 0x70 */);
    // 0052c7fc  8b526c                 -mov edx, dword ptr [edx + 0x6c]
    cpu.edx = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(108) /* 0x6c */);
    // 0052c7ff  e87cfdffff             -call 0x52c580
    cpu.esp -= 4;
    sub_52c580(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052c804  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c805  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c806  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c807  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c808  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x00 0x00 0x00 0x00 0x00 0x00 0x00 */
void Application::sub_52c810(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0052c810  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 0052c812  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x90 */
void Application::sub_52c814(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0052c814  ff15c0b15600           -call dword ptr [0x56b1c0]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(5681600) /* 0x56b1c0 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052c81a  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x90 */
void Application::sub_52c81c(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0052c81c  ff15c4b15600           -call dword ptr [0x56b1c4]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(5681604) /* 0x56b1c4 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052c822  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x90 */
void Application::sub_52c824(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0052c824  ff15c8b15600           -call dword ptr [0x56b1c8]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(5681608) /* 0x56b1c8 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052c82a  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x90 */
void Application::sub_52c82c(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0052c82c  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 0052c82d  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 0052c82e  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0052c830  7410                   -je 0x52c842
    if (cpu.flags.zf)
    {
        goto L_0x0052c842;
    }
    // 0052c832  8b08                   -mov ecx, dword ptr [eax]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax);
    // 0052c834  8b35c0b15600           -mov esi, dword ptr [0x56b1c0]
    cpu.esi = app->getMemory<x86::reg32>(x86::reg32(5681600) /* 0x56b1c0 */);
    // 0052c83a  890dc0b15600           -mov dword ptr [0x56b1c0], ecx
    app->getMemory<x86::reg32>(x86::reg32(5681600) /* 0x56b1c0 */) = cpu.ecx;
    // 0052c840  8930                   -mov dword ptr [eax], esi
    app->getMemory<x86::reg32>(cpu.eax) = cpu.esi;
L_0x0052c842:
    // 0052c842  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 0052c844  740f                   -je 0x52c855
    if (cpu.flags.zf)
    {
        goto L_0x0052c855;
    }
    // 0052c846  8b02                   -mov eax, dword ptr [edx]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edx);
    // 0052c848  8b0dc4b15600           -mov ecx, dword ptr [0x56b1c4]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(5681604) /* 0x56b1c4 */);
    // 0052c84e  a3c4b15600             -mov dword ptr [0x56b1c4], eax
    app->getMemory<x86::reg32>(x86::reg32(5681604) /* 0x56b1c4 */) = cpu.eax;
    // 0052c853  890a                   -mov dword ptr [edx], ecx
    app->getMemory<x86::reg32>(cpu.edx) = cpu.ecx;
L_0x0052c855:
    // 0052c855  85db                   +test ebx, ebx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & cpu.ebx));
    // 0052c857  740f                   -je 0x52c868
    if (cpu.flags.zf)
    {
        goto L_0x0052c868;
    }
    // 0052c859  8b03                   -mov eax, dword ptr [ebx]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx);
    // 0052c85b  8b15c8b15600           -mov edx, dword ptr [0x56b1c8]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5681608) /* 0x56b1c8 */);
    // 0052c861  a3c8b15600             -mov dword ptr [0x56b1c8], eax
    app->getMemory<x86::reg32>(x86::reg32(5681608) /* 0x56b1c8 */) = cpu.eax;
    // 0052c866  8913                   -mov dword ptr [ebx], edx
    app->getMemory<x86::reg32>(cpu.ebx) = cpu.edx;
L_0x0052c868:
    // 0052c868  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c869  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c86a  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x00 0x00 0x00 0x00 0x00 */
void Application::sub_52c870(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0052c870  ff15ccb15600           -call dword ptr [0x56b1cc]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(5681612) /* 0x56b1cc */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052c876  8bc0                   -mov eax, eax
    cpu.eax = cpu.eax;
    // 0052c878  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 0052c879  baff000000             -mov edx, 0xff
    cpu.edx = 255 /*0xff*/;
    // 0052c87e  b8d4205500             -mov eax, 0x5520d4
    cpu.eax = 5578964 /*0x5520d4*/;
    // 0052c883  e88454feff             -call 0x511d0c
    cpu.esp -= 4;
    nfs3hp::watcom::fatal_runtime_error(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052c888  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c889  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip  */
void Application::sub_52c878(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    goto L_entry_0x0052c878;
    // 0052c870  ff15ccb15600           -call dword ptr [0x56b1cc]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(5681612) /* 0x56b1cc */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052c876  8bc0                   -mov eax, eax
    cpu.eax = cpu.eax;
L_entry_0x0052c878:
    // 0052c878  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 0052c879  baff000000             -mov edx, 0xff
    cpu.edx = 255 /*0xff*/;
    // 0052c87e  b8d4205500             -mov eax, 0x5520d4
    cpu.eax = 5578964 /*0x5520d4*/;
    // 0052c883  e88454feff             -call 0x511d0c
    cpu.esp -= 4;
    nfs3hp::watcom::fatal_runtime_error(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052c888  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0052c889  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip  */
void Application::sub_52c88a(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0052c88a  29d2                   -sub edx, edx
    (cpu.edx) -= x86::reg32(x86::sreg32(cpu.edx));
    // 0052c88c  29c0                   -sub eax, eax
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.eax));
    // 0052c88e  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip  */
void Application::sub_52c88f(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0052c88f  b883000000             -mov eax, 0x83
    cpu.eax = 131 /*0x83*/;
    // 0052c894  e887240000             -call 0x52ed20
    cpu.esp -= 4;
    sub_52ed20(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052c899  eb1d                   -jmp 0x52c8b8
    goto L_0x0052c8b8;
    // 0052c89b  b883000000             -mov eax, 0x83
    cpu.eax = 131 /*0x83*/;
    // 0052c8a0  e87b240000             -call 0x52ed20
    cpu.esp -= 4;
    sub_52ed20(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052c8a5  eb11                   -jmp 0x52c8b8
    goto L_0x0052c8b8;
    // 0052c8a7  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 0052c8a8  e8f75ffdff             -call 0x5028a4
    cpu.esp -= 4;
    nfs3hp::watcom::set_ERANGE(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052c8ad  b884000000             -mov eax, 0x84
    cpu.eax = 132 /*0x84*/;
    // 0052c8b2  e869240000             -call 0x52ed20
    cpu.esp -= 4;
    sub_52ed20(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052c8b7  58                     -pop eax
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
L_0x0052c8b8:
    // 0052c8b8  2500000080             -and eax, 0x80000000
    cpu.eax &= x86::reg32(x86::sreg32(2147483648 /*0x80000000*/));
    // 0052c8bd  0d0000f07f             -or eax, 0x7ff00000
    cpu.eax |= x86::reg32(x86::sreg32(2146435072 /*0x7ff00000*/));
    // 0052c8c2  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 0052c8c4  29c0                   -sub eax, eax
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.eax));
    // 0052c8c6  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip  */
void Application::sub_52c8a7(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    goto L_entry_0x0052c8a7;
    // 0052c88f  b883000000             -mov eax, 0x83
    cpu.eax = 131 /*0x83*/;
    // 0052c894  e887240000             -call 0x52ed20
    cpu.esp -= 4;
    sub_52ed20(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052c899  eb1d                   -jmp 0x52c8b8
    goto L_0x0052c8b8;
    // 0052c89b  b883000000             -mov eax, 0x83
    cpu.eax = 131 /*0x83*/;
    // 0052c8a0  e87b240000             -call 0x52ed20
    cpu.esp -= 4;
    sub_52ed20(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052c8a5  eb11                   -jmp 0x52c8b8
    goto L_0x0052c8b8;
L_entry_0x0052c8a7:
    // 0052c8a7  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 0052c8a8  e8f75ffdff             -call 0x5028a4
    cpu.esp -= 4;
    nfs3hp::watcom::set_ERANGE(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052c8ad  b884000000             -mov eax, 0x84
    cpu.eax = 132 /*0x84*/;
    // 0052c8b2  e869240000             -call 0x52ed20
    cpu.esp -= 4;
    sub_52ed20(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052c8b7  58                     -pop eax
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
L_0x0052c8b8:
    // 0052c8b8  2500000080             -and eax, 0x80000000
    cpu.eax &= x86::reg32(x86::sreg32(2147483648 /*0x80000000*/));
    // 0052c8bd  0d0000f07f             -or eax, 0x7ff00000
    cpu.eax |= x86::reg32(x86::sreg32(2146435072 /*0x7ff00000*/));
    // 0052c8c2  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 0052c8c4  29c0                   -sub eax, eax
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.eax));
    // 0052c8c6  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip  */
void Application::sub_52c89b(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    goto L_entry_0x0052c89b;
    // 0052c88f  b883000000             -mov eax, 0x83
    cpu.eax = 131 /*0x83*/;
    // 0052c894  e887240000             -call 0x52ed20
    cpu.esp -= 4;
    sub_52ed20(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052c899  eb1d                   -jmp 0x52c8b8
    goto L_0x0052c8b8;
L_entry_0x0052c89b:
    // 0052c89b  b883000000             -mov eax, 0x83
    cpu.eax = 131 /*0x83*/;
    // 0052c8a0  e87b240000             -call 0x52ed20
    cpu.esp -= 4;
    sub_52ed20(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052c8a5  eb11                   -jmp 0x52c8b8
    goto L_0x0052c8b8;
    // 0052c8a7  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 0052c8a8  e8f75ffdff             -call 0x5028a4
    cpu.esp -= 4;
    nfs3hp::watcom::set_ERANGE(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052c8ad  b884000000             -mov eax, 0x84
    cpu.eax = 132 /*0x84*/;
    // 0052c8b2  e869240000             -call 0x52ed20
    cpu.esp -= 4;
    sub_52ed20(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052c8b7  58                     -pop eax
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
L_0x0052c8b8:
    // 0052c8b8  2500000080             -and eax, 0x80000000
    cpu.eax &= x86::reg32(x86::sreg32(2147483648 /*0x80000000*/));
    // 0052c8bd  0d0000f07f             -or eax, 0x7ff00000
    cpu.eax |= x86::reg32(x86::sreg32(2146435072 /*0x7ff00000*/));
    // 0052c8c2  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 0052c8c4  29c0                   -sub eax, eax
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.eax));
    // 0052c8c6  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip  */
void Application::sub_52c8c7(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0052c8c7  b883000000             -mov eax, 0x83
    cpu.eax = 131 /*0x83*/;
    // 0052c8cc  e84f240000             -call 0x52ed20
    cpu.esp -= 4;
    sub_52ed20(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052c8d1  eb11                   -jmp 0x52c8e4
    goto L_0x0052c8e4;
    // 0052c8d3  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 0052c8d4  e8cb5ffdff             -call 0x5028a4
    cpu.esp -= 4;
    nfs3hp::watcom::set_ERANGE(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052c8d9  b884000000             -mov eax, 0x84
    cpu.eax = 132 /*0x84*/;
    // 0052c8de  e83d240000             -call 0x52ed20
    cpu.esp -= 4;
    sub_52ed20(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0052c8e3  58                     -pop eax
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
L_0x0052c8e4:
    // 0052c8e4  2500000080             -and eax, 0x80000000
    cpu.eax &= x86::reg32(x86::sreg32(2147483648 /*0x80000000*/));
    // 0052c8e9  0d0000807f             -or eax, 0x7f800000
    cpu.eax |= x86::reg32(x86::sreg32(2139095040 /*0x7f800000*/));
    // 0052c8ee  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_52c8f0: native, nfs3hp::snd::pcmPlayed */

/* sub_52c8f4: native, nfs3hp::snd::pcmOnceDecode */

/* sub_52c9a0: native, nfs3hp::snd::pcmOnceSetup */

/* sub_52c9d0: native, nfs3hp::snd::pcmLoopedDecode */

/* sub_52ca48: native, nfs3hp::snd::pcmLoopedSetup */

/* sub_52ca80: native, nfs3hp::snd::pcmStreamedDecode */

/* sub_52cb74: native, nfs3hp::snd::pcmStreamedSetup */

/* sub_52cba0: native, nfs3hp::snd::pcmFileDecode */

/* sub_52ccb8: native, nfs3hp::snd::pcmFileSetup */

/* sub_52ccf0: native, nfs3hp::snd::dead_0x52ccf0 */

/* sub_52ccf4: native, nfs3hp::snd::dead_0x52ccf4 */

/* sub_52cdd4: native, nfs3hp::snd::dead_0x52cdd4 */

/* sub_52ce20: native, nfs3hp::snd::dead_0x52ce20 */

/* sub_52ceb0: native, nfs3hp::snd::dead_0x52ceb0 */

/* sub_52cef0: native, nfs3hp::snd::dead_0x52cef0 */

/* sub_52cfd8: native, nfs3hp::snd::dead_0x52cfd8 */

}
