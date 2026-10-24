#include "nfs3hp.h"
#include <lib/thread.h>

namespace nfs3hp
{

/* sub_42c7f0: native, nfs3hp::raceload::setTimeStep */

/* sub_42c830: native, nfs3hp::raceload::addCarTasks */

/* sub_42c950: native, nfs3hp::raceload::openCarViv */

/* sub_42ca80: native, nfs3hp::raceload::closeCarViv */

/* sub_42cab0: native, nfs3hp::raceload::removeCarTasks */

/* sub_42cc20: native, nfs3hp::raceload::countLaps */

/* sub_42cd00: native, nfs3hp::raceload::carAxesSpeed */

/* sub_42cdd0: native, nfs3hp::raceload::carForwardSpeed */

/* sub_42ce10: native, nfs3hp::raceload::carRaceDistance */

/* sub_42ce70: native, nfs3hp::raceload::updateRaceCars */

/* sub_42cff0: native, nfs3hp::raceload::frameFraction */

/* sub_42d020: native, nfs3hp::raceload::placeHeadlights */

/* sub_42d160: native, nfs3hp::raceload::placeCarShadow */

/* sub_42d3e0: native, nfs3hp::raceload::sortRaceCars */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x8b 0xc0 */
void Application::sub_42d4f0(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0042d4f0  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 0042d4f1  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 0042d4f3  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042d4f4  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_42d500: native, nfs3hp::raceload::emptyHook */

/* sub_42d510: native, nfs3hp::ea::gameTrace */

/* sub_42d520: native, nfs3hp::raceload::emptyHook2 */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 0x8b 0xdb */
void Application::sub_42d530(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0042d530  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 0042d531  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 0042d533  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042d534  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 0x8b 0xdb */
void Application::sub_42d540(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0042d540  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 0042d541  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 0042d543  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042d544  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_42d620: native, nfs3hp::raceload::showMessage */

/* sub_42d710: native, nfs3hp::raceload::sendMessage */

/* sub_42d790: native, nfs3hp::raceload::openMessages */

/* sub_42d7f0: native, nfs3hp::raceload::closeMessages */

/* sub_42d800: native, nfs3hp::raceload::clearMessages */

/* sub_42d810: native, nfs3hp::raceload::sendTypedMessage */

/* sub_42d860: native, nfs3hp::raceload::newMessageLine */

/* sub_42d8a0: native, nfs3hp::raceload::freeMessageLine */

/* sub_42d8b0: native, nfs3hp::raceload::insertMessageLine */

/* sub_42d910: native, nfs3hp::raceload::freeMessageLines */

/* sub_42d940: native, nfs3hp::raceload::clearMessageLines */

/* sub_42d9b0: native, nfs3hp::raceload::showMessageLines */

/* sub_42da30: native, nfs3hp::raceload::appendMessageLine */

/* align: skip 0x8d 0x44 0x20 0x00 */
void Application::sub_42daa0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0042daa0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 0042daa1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 0042daa2  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 0042daa3  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 0042daa4  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 0042daa5  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 0042daa6  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 0042daa8  a1a0375500             -mov eax, dword ptr [0x5537a0]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5584800) /* 0x5537a0 */);
    // 0042daad  8b10                   -mov edx, dword ptr [eax]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax);
    // 0042daaf  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 0042dab0  ff15b8445300           -call dword ptr [0x5344b8]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(5457080) /* 0x5344b8 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042dab6  8b0da0375500           -mov ecx, dword ptr [0x5537a0]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(5584800) /* 0x5537a0 */);
    // 0042dabc  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
    // 0042dabe  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    // 0042dac0  7416                   -je 0x42dad8
    if (cpu.flags.zf)
    {
        goto L_0x0042dad8;
    }
    // 0042dac2  8b7104                 -mov esi, dword ptr [ecx + 4]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(4) /* 0x4 */);
    // 0042dac5  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 0042dac7  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 0042dac9  740d                   -je 0x42dad8
    if (cpu.flags.zf)
    {
        goto L_0x0042dad8;
    }
    // 0042dacb  8b4668                 -mov eax, dword ptr [esi + 0x68]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(104) /* 0x68 */);
L_0x0042dace:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 0042dace  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0042dad0  7406                   -je 0x42dad8
    if (cpu.flags.zf)
    {
        goto L_0x0042dad8;
    }
    // 0042dad2  43                     +inc ebx
    {
        x86::reg32& tmp = cpu.ebx;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 0042dad3  8b4068                 -mov eax, dword ptr [eax + 0x68]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(104) /* 0x68 */);
    // 0042dad6  ebf6                   -jmp 0x42dace
    goto L_0x0042dace;
L_0x0042dad8:
    // 0042dad8  a1a0375500             -mov eax, dword ptr [0x5537a0]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5584800) /* 0x5537a0 */);
    // 0042dadd  8b38                   -mov edi, dword ptr [eax]
    cpu.edi = app->getMemory<x86::reg32>(cpu.eax);
    // 0042dadf  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 0042dae0  ff1588455300           -call dword ptr [0x534588]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(5457288) /* 0x534588 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042dae6  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 0042dae8  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042dae9  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042daea  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042daeb  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042daec  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042daed  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042daee  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_42daf0: native, nfs3hp::raceload::closeMessageLines */

/* sub_42db70: native, nfs3hp::raceload::openMessageLines */

/* sub_42dc20: native, nfs3hp::raceload::raceControlsThread */

/* align: skip  */
void Application::sub_42dc3e(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0042dc3e  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042dc3f  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_42dc40: native, nfs3hp::raceload::wakeRaceControls */

/* sub_42dc60: native, nfs3hp::raceload::raceControlsTick */

/* sub_42dcb0: native, nfs3hp::raceload::startRaceControlsTick */

/* sub_42dd00: native, nfs3hp::raceload::stopRaceControlsTick */

/* sub_42dd60: native, nfs3hp::raceload::cornerInBox */

/* sub_42e010: native, nfs3hp::raceload::cornerInBoxBack */

/* sub_42e2c0: native, nfs3hp::raceload::cornerInBox2 */

/* sub_42e4f0: native, nfs3hp::raceload::cornerInBoxBack2 */

/* sub_42e720: native, nfs3hp::raceload::clampSpin */

/* sub_42e820: native, nfs3hp::raceload::applyImpulse */

/* sub_42e9c0: native, nfs3hp::raceload::bounceOffWall */

/* sub_42ee10: native, nfs3hp::raceload::hitWall */

/* sub_42efe0: native, nfs3hp::raceload::boxHitsWall */

/* sub_42f280: native, nfs3hp::raceload::carsCollide */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x90 */
void Application::sub_42f550(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0042f550  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 0042f551  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 0042f552  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 0042f553  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 0042f554  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 0042f555  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 0042f557  89c7                   -mov edi, eax
    cpu.edi = cpu.eax;
    // 0042f559  89d6                   -mov esi, edx
    cpu.esi = cpu.edx;
    // 0042f55b  6a00                   -push 0
    app->getMemory<x86::reg32>(cpu.esp-4) = 0 /*0x0*/;
    cpu.esp -= 4;
    // 0042f55d  bb01000000             -mov ebx, 1
    cpu.ebx = 1 /*0x1*/;
    // 0042f562  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 0042f564  e8f7e7ffff             -call 0x42dd60
    cpu.esp -= 4;
    nfs3hp::raceload::cornerInBox(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042f569  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0042f56b  740a                   -je 0x42f577
    if (cpu.flags.zf)
    {
        goto L_0x0042f577;
    }
    // 0042f56d  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 0042f572  e939030000             -jmp 0x42f8b0
    goto L_0x0042f8b0;
L_0x0042f577:
    // 0042f577  b901000000             -mov ecx, 1
    cpu.ecx = 1 /*0x1*/;
    // 0042f57c  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 0042f57d  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 0042f57f  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
    // 0042f581  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 0042f583  e8d8e7ffff             -call 0x42dd60
    cpu.esp -= 4;
    nfs3hp::raceload::cornerInBox(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042f588  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0042f58a  740b                   -je 0x42f597
    if (cpu.flags.zf)
    {
        goto L_0x0042f597;
    }
    // 0042f58c  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 0042f591  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f592  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f593  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f594  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f595  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f596  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x0042f597:
    // 0042f597  6a01                   -push 1
    app->getMemory<x86::reg32>(cpu.esp-4) = 1 /*0x1*/;
    cpu.esp -= 4;
    // 0042f599  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 0042f59b  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 0042f59d  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 0042f59f  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
    // 0042f5a1  e8bae7ffff             -call 0x42dd60
    cpu.esp -= 4;
    nfs3hp::raceload::cornerInBox(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042f5a6  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0042f5a8  740b                   -je 0x42f5b5
    if (cpu.flags.zf)
    {
        goto L_0x0042f5b5;
    }
    // 0042f5aa  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 0042f5af  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f5b0  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f5b1  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f5b2  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f5b3  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f5b4  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x0042f5b5:
    // 0042f5b5  bbffffffff             -mov ebx, 0xffffffff
    cpu.ebx = 4294967295 /*0xffffffff*/;
    // 0042f5ba  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 0042f5bb  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 0042f5bd  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 0042f5bf  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 0042f5c1  e89ae7ffff             -call 0x42dd60
    cpu.esp -= 4;
    nfs3hp::raceload::cornerInBox(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042f5c6  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0042f5c8  740b                   -je 0x42f5d5
    if (cpu.flags.zf)
    {
        goto L_0x0042f5d5;
    }
    // 0042f5ca  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 0042f5cf  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f5d0  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f5d1  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f5d2  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f5d3  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f5d4  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x0042f5d5:
    // 0042f5d5  b9ffffffff             -mov ecx, 0xffffffff
    cpu.ecx = 4294967295 /*0xffffffff*/;
    // 0042f5da  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 0042f5db  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 0042f5dd  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
    // 0042f5df  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 0042f5e1  e87ae7ffff             -call 0x42dd60
    cpu.esp -= 4;
    nfs3hp::raceload::cornerInBox(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042f5e6  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0042f5e8  740b                   -je 0x42f5f5
    if (cpu.flags.zf)
    {
        goto L_0x0042f5f5;
    }
    // 0042f5ea  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 0042f5ef  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f5f0  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f5f1  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f5f2  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f5f3  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f5f4  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x0042f5f5:
    // 0042f5f5  6aff                   -push -1
    app->getMemory<x86::reg32>(cpu.esp-4) = -1 /*-0x1*/;
    cpu.esp -= 4;
    // 0042f5f7  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 0042f5f9  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 0042f5fb  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 0042f5fd  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
    // 0042f5ff  e85ce7ffff             -call 0x42dd60
    cpu.esp -= 4;
    nfs3hp::raceload::cornerInBox(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042f604  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0042f606  740b                   -je 0x42f613
    if (cpu.flags.zf)
    {
        goto L_0x0042f613;
    }
    // 0042f608  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 0042f60d  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f60e  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f60f  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f610  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f611  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f612  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x0042f613:
    // 0042f613  bb01000000             -mov ebx, 1
    cpu.ebx = 1 /*0x1*/;
    // 0042f618  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 0042f619  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 0042f61b  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 0042f61d  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 0042f61f  e8ece9ffff             -call 0x42e010
    cpu.esp -= 4;
    nfs3hp::raceload::cornerInBoxBack(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042f624  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0042f626  740b                   -je 0x42f633
    if (cpu.flags.zf)
    {
        goto L_0x0042f633;
    }
    // 0042f628  b802000000             -mov eax, 2
    cpu.eax = 2 /*0x2*/;
    // 0042f62d  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f62e  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f62f  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f630  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f631  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f632  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x0042f633:
    // 0042f633  b901000000             -mov ecx, 1
    cpu.ecx = 1 /*0x1*/;
    // 0042f638  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 0042f639  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 0042f63b  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
    // 0042f63d  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 0042f63f  e8cce9ffff             -call 0x42e010
    cpu.esp -= 4;
    nfs3hp::raceload::cornerInBoxBack(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042f644  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0042f646  740b                   -je 0x42f653
    if (cpu.flags.zf)
    {
        goto L_0x0042f653;
    }
    // 0042f648  b802000000             -mov eax, 2
    cpu.eax = 2 /*0x2*/;
    // 0042f64d  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f64e  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f64f  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f650  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f651  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f652  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x0042f653:
    // 0042f653  6a01                   -push 1
    app->getMemory<x86::reg32>(cpu.esp-4) = 1 /*0x1*/;
    cpu.esp -= 4;
    // 0042f655  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 0042f657  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 0042f659  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 0042f65b  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
    // 0042f65d  e8aee9ffff             -call 0x42e010
    cpu.esp -= 4;
    nfs3hp::raceload::cornerInBoxBack(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042f662  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0042f664  740b                   -je 0x42f671
    if (cpu.flags.zf)
    {
        goto L_0x0042f671;
    }
    // 0042f666  b802000000             -mov eax, 2
    cpu.eax = 2 /*0x2*/;
    // 0042f66b  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f66c  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f66d  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f66e  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f66f  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f670  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x0042f671:
    // 0042f671  bbffffffff             -mov ebx, 0xffffffff
    cpu.ebx = 4294967295 /*0xffffffff*/;
    // 0042f676  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 0042f677  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 0042f679  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 0042f67b  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 0042f67d  e88ee9ffff             -call 0x42e010
    cpu.esp -= 4;
    nfs3hp::raceload::cornerInBoxBack(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042f682  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0042f684  740b                   -je 0x42f691
    if (cpu.flags.zf)
    {
        goto L_0x0042f691;
    }
    // 0042f686  b802000000             -mov eax, 2
    cpu.eax = 2 /*0x2*/;
    // 0042f68b  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f68c  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f68d  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f68e  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f68f  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f690  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x0042f691:
    // 0042f691  b9ffffffff             -mov ecx, 0xffffffff
    cpu.ecx = 4294967295 /*0xffffffff*/;
    // 0042f696  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 0042f697  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 0042f699  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
    // 0042f69b  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 0042f69d  e86ee9ffff             -call 0x42e010
    cpu.esp -= 4;
    nfs3hp::raceload::cornerInBoxBack(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042f6a2  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0042f6a4  740b                   -je 0x42f6b1
    if (cpu.flags.zf)
    {
        goto L_0x0042f6b1;
    }
    // 0042f6a6  b802000000             -mov eax, 2
    cpu.eax = 2 /*0x2*/;
    // 0042f6ab  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f6ac  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f6ad  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f6ae  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f6af  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f6b0  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x0042f6b1:
    // 0042f6b1  6aff                   -push -1
    app->getMemory<x86::reg32>(cpu.esp-4) = -1 /*-0x1*/;
    cpu.esp -= 4;
    // 0042f6b3  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 0042f6b5  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 0042f6b7  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 0042f6b9  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
    // 0042f6bb  e850e9ffff             -call 0x42e010
    cpu.esp -= 4;
    nfs3hp::raceload::cornerInBoxBack(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042f6c0  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0042f6c2  740b                   -je 0x42f6cf
    if (cpu.flags.zf)
    {
        goto L_0x0042f6cf;
    }
    // 0042f6c4  b802000000             -mov eax, 2
    cpu.eax = 2 /*0x2*/;
    // 0042f6c9  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f6ca  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f6cb  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f6cc  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f6cd  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f6ce  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x0042f6cf:
    // 0042f6cf  6a01                   -push 1
    app->getMemory<x86::reg32>(cpu.esp-4) = 1 /*0x1*/;
    cpu.esp -= 4;
    // 0042f6d1  b901000000             -mov ecx, 1
    cpu.ecx = 1 /*0x1*/;
    // 0042f6d6  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 0042f6d8  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 0042f6da  89cb                   -mov ebx, ecx
    cpu.ebx = cpu.ecx;
    // 0042f6dc  e8dfebffff             -call 0x42e2c0
    cpu.esp -= 4;
    nfs3hp::raceload::cornerInBox2(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042f6e1  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0042f6e3  740b                   -je 0x42f6f0
    if (cpu.flags.zf)
    {
        goto L_0x0042f6f0;
    }
    // 0042f6e5  b803000000             -mov eax, 3
    cpu.eax = 3 /*0x3*/;
    // 0042f6ea  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f6eb  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f6ec  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f6ed  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f6ee  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f6ef  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x0042f6f0:
    // 0042f6f0  6aff                   -push -1
    app->getMemory<x86::reg32>(cpu.esp-4) = -1 /*-0x1*/;
    cpu.esp -= 4;
    // 0042f6f2  b901000000             -mov ecx, 1
    cpu.ecx = 1 /*0x1*/;
    // 0042f6f7  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 0042f6f9  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 0042f6fb  89cb                   -mov ebx, ecx
    cpu.ebx = cpu.ecx;
    // 0042f6fd  e8beebffff             -call 0x42e2c0
    cpu.esp -= 4;
    nfs3hp::raceload::cornerInBox2(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042f702  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0042f704  740b                   -je 0x42f711
    if (cpu.flags.zf)
    {
        goto L_0x0042f711;
    }
    // 0042f706  b803000000             -mov eax, 3
    cpu.eax = 3 /*0x3*/;
    // 0042f70b  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f70c  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f70d  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f70e  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f70f  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f710  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x0042f711:
    // 0042f711  6a01                   -push 1
    app->getMemory<x86::reg32>(cpu.esp-4) = 1 /*0x1*/;
    cpu.esp -= 4;
    // 0042f713  b9ffffffff             -mov ecx, 0xffffffff
    cpu.ecx = 4294967295 /*0xffffffff*/;
    // 0042f718  bb01000000             -mov ebx, 1
    cpu.ebx = 1 /*0x1*/;
    // 0042f71d  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 0042f71f  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 0042f721  e89aebffff             -call 0x42e2c0
    cpu.esp -= 4;
    nfs3hp::raceload::cornerInBox2(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042f726  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0042f728  740b                   -je 0x42f735
    if (cpu.flags.zf)
    {
        goto L_0x0042f735;
    }
    // 0042f72a  b803000000             -mov eax, 3
    cpu.eax = 3 /*0x3*/;
    // 0042f72f  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f730  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f731  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f732  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f733  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f734  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x0042f735:
    // 0042f735  6aff                   -push -1
    app->getMemory<x86::reg32>(cpu.esp-4) = -1 /*-0x1*/;
    cpu.esp -= 4;
    // 0042f737  b9ffffffff             -mov ecx, 0xffffffff
    cpu.ecx = 4294967295 /*0xffffffff*/;
    // 0042f73c  bb01000000             -mov ebx, 1
    cpu.ebx = 1 /*0x1*/;
    // 0042f741  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 0042f743  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 0042f745  e876ebffff             -call 0x42e2c0
    cpu.esp -= 4;
    nfs3hp::raceload::cornerInBox2(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042f74a  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0042f74c  740b                   -je 0x42f759
    if (cpu.flags.zf)
    {
        goto L_0x0042f759;
    }
    // 0042f74e  b803000000             -mov eax, 3
    cpu.eax = 3 /*0x3*/;
    // 0042f753  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f754  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f755  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f756  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f757  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f758  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x0042f759:
    // 0042f759  6a01                   -push 1
    app->getMemory<x86::reg32>(cpu.esp-4) = 1 /*0x1*/;
    cpu.esp -= 4;
    // 0042f75b  b901000000             -mov ecx, 1
    cpu.ecx = 1 /*0x1*/;
    // 0042f760  bbffffffff             -mov ebx, 0xffffffff
    cpu.ebx = 4294967295 /*0xffffffff*/;
    // 0042f765  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 0042f767  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 0042f769  e852ebffff             -call 0x42e2c0
    cpu.esp -= 4;
    nfs3hp::raceload::cornerInBox2(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042f76e  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0042f770  740b                   -je 0x42f77d
    if (cpu.flags.zf)
    {
        goto L_0x0042f77d;
    }
    // 0042f772  b803000000             -mov eax, 3
    cpu.eax = 3 /*0x3*/;
    // 0042f777  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f778  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f779  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f77a  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f77b  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f77c  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x0042f77d:
    // 0042f77d  6aff                   -push -1
    app->getMemory<x86::reg32>(cpu.esp-4) = -1 /*-0x1*/;
    cpu.esp -= 4;
    // 0042f77f  b901000000             -mov ecx, 1
    cpu.ecx = 1 /*0x1*/;
    // 0042f784  bbffffffff             -mov ebx, 0xffffffff
    cpu.ebx = 4294967295 /*0xffffffff*/;
    // 0042f789  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 0042f78b  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 0042f78d  e82eebffff             -call 0x42e2c0
    cpu.esp -= 4;
    nfs3hp::raceload::cornerInBox2(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042f792  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0042f794  740b                   -je 0x42f7a1
    if (cpu.flags.zf)
    {
        goto L_0x0042f7a1;
    }
    // 0042f796  b803000000             -mov eax, 3
    cpu.eax = 3 /*0x3*/;
    // 0042f79b  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f79c  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f79d  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f79e  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f79f  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f7a0  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x0042f7a1:
    // 0042f7a1  6a01                   -push 1
    app->getMemory<x86::reg32>(cpu.esp-4) = 1 /*0x1*/;
    cpu.esp -= 4;
    // 0042f7a3  b9ffffffff             -mov ecx, 0xffffffff
    cpu.ecx = 4294967295 /*0xffffffff*/;
    // 0042f7a8  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 0042f7aa  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 0042f7ac  89cb                   -mov ebx, ecx
    cpu.ebx = cpu.ecx;
    // 0042f7ae  e80debffff             -call 0x42e2c0
    cpu.esp -= 4;
    nfs3hp::raceload::cornerInBox2(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042f7b3  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0042f7b5  740b                   -je 0x42f7c2
    if (cpu.flags.zf)
    {
        goto L_0x0042f7c2;
    }
    // 0042f7b7  b803000000             -mov eax, 3
    cpu.eax = 3 /*0x3*/;
    // 0042f7bc  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f7bd  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f7be  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f7bf  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f7c0  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f7c1  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x0042f7c2:
    // 0042f7c2  6aff                   -push -1
    app->getMemory<x86::reg32>(cpu.esp-4) = -1 /*-0x1*/;
    cpu.esp -= 4;
    // 0042f7c4  b9ffffffff             -mov ecx, 0xffffffff
    cpu.ecx = 4294967295 /*0xffffffff*/;
    // 0042f7c9  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 0042f7cb  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 0042f7cd  89cb                   -mov ebx, ecx
    cpu.ebx = cpu.ecx;
    // 0042f7cf  e8eceaffff             -call 0x42e2c0
    cpu.esp -= 4;
    nfs3hp::raceload::cornerInBox2(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042f7d4  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0042f7d6  740b                   -je 0x42f7e3
    if (cpu.flags.zf)
    {
        goto L_0x0042f7e3;
    }
    // 0042f7d8  b803000000             -mov eax, 3
    cpu.eax = 3 /*0x3*/;
    // 0042f7dd  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f7de  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f7df  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f7e0  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f7e1  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f7e2  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x0042f7e3:
    // 0042f7e3  6a01                   -push 1
    app->getMemory<x86::reg32>(cpu.esp-4) = 1 /*0x1*/;
    cpu.esp -= 4;
    // 0042f7e5  b901000000             -mov ecx, 1
    cpu.ecx = 1 /*0x1*/;
    // 0042f7ea  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 0042f7ec  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 0042f7ee  89cb                   -mov ebx, ecx
    cpu.ebx = cpu.ecx;
    // 0042f7f0  e8fbecffff             -call 0x42e4f0
    cpu.esp -= 4;
    nfs3hp::raceload::cornerInBoxBack2(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042f7f5  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0042f7f7  0f85ae000000           -jne 0x42f8ab
    if (!cpu.flags.zf)
    {
        goto L_0x0042f8ab;
    }
    // 0042f7fd  6aff                   -push -1
    app->getMemory<x86::reg32>(cpu.esp-4) = -1 /*-0x1*/;
    cpu.esp -= 4;
    // 0042f7ff  b901000000             -mov ecx, 1
    cpu.ecx = 1 /*0x1*/;
    // 0042f804  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 0042f806  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 0042f808  89cb                   -mov ebx, ecx
    cpu.ebx = cpu.ecx;
    // 0042f80a  e8e1ecffff             -call 0x42e4f0
    cpu.esp -= 4;
    nfs3hp::raceload::cornerInBoxBack2(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042f80f  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0042f811  0f8594000000           -jne 0x42f8ab
    if (!cpu.flags.zf)
    {
        goto L_0x0042f8ab;
    }
    // 0042f817  6a01                   -push 1
    app->getMemory<x86::reg32>(cpu.esp-4) = 1 /*0x1*/;
    cpu.esp -= 4;
    // 0042f819  b9ffffffff             -mov ecx, 0xffffffff
    cpu.ecx = 4294967295 /*0xffffffff*/;
    // 0042f81e  bb01000000             -mov ebx, 1
    cpu.ebx = 1 /*0x1*/;
    // 0042f823  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 0042f825  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 0042f827  e8c4ecffff             -call 0x42e4f0
    cpu.esp -= 4;
    nfs3hp::raceload::cornerInBoxBack2(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042f82c  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0042f82e  0f8577000000           -jne 0x42f8ab
    if (!cpu.flags.zf)
    {
        goto L_0x0042f8ab;
    }
    // 0042f834  6aff                   -push -1
    app->getMemory<x86::reg32>(cpu.esp-4) = -1 /*-0x1*/;
    cpu.esp -= 4;
    // 0042f836  b9ffffffff             -mov ecx, 0xffffffff
    cpu.ecx = 4294967295 /*0xffffffff*/;
    // 0042f83b  bb01000000             -mov ebx, 1
    cpu.ebx = 1 /*0x1*/;
    // 0042f840  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 0042f842  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 0042f844  e8a7ecffff             -call 0x42e4f0
    cpu.esp -= 4;
    nfs3hp::raceload::cornerInBoxBack2(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042f849  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0042f84b  755e                   -jne 0x42f8ab
    if (!cpu.flags.zf)
    {
        goto L_0x0042f8ab;
    }
    // 0042f84d  6a01                   -push 1
    app->getMemory<x86::reg32>(cpu.esp-4) = 1 /*0x1*/;
    cpu.esp -= 4;
    // 0042f84f  b901000000             -mov ecx, 1
    cpu.ecx = 1 /*0x1*/;
    // 0042f854  bbffffffff             -mov ebx, 0xffffffff
    cpu.ebx = 4294967295 /*0xffffffff*/;
    // 0042f859  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 0042f85b  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 0042f85d  e88eecffff             -call 0x42e4f0
    cpu.esp -= 4;
    nfs3hp::raceload::cornerInBoxBack2(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042f862  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0042f864  7545                   -jne 0x42f8ab
    if (!cpu.flags.zf)
    {
        goto L_0x0042f8ab;
    }
    // 0042f866  6aff                   -push -1
    app->getMemory<x86::reg32>(cpu.esp-4) = -1 /*-0x1*/;
    cpu.esp -= 4;
    // 0042f868  b901000000             -mov ecx, 1
    cpu.ecx = 1 /*0x1*/;
    // 0042f86d  bbffffffff             -mov ebx, 0xffffffff
    cpu.ebx = 4294967295 /*0xffffffff*/;
    // 0042f872  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 0042f874  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 0042f876  e875ecffff             -call 0x42e4f0
    cpu.esp -= 4;
    nfs3hp::raceload::cornerInBoxBack2(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042f87b  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0042f87d  752c                   -jne 0x42f8ab
    if (!cpu.flags.zf)
    {
        goto L_0x0042f8ab;
    }
    // 0042f87f  6a01                   -push 1
    app->getMemory<x86::reg32>(cpu.esp-4) = 1 /*0x1*/;
    cpu.esp -= 4;
    // 0042f881  b9ffffffff             -mov ecx, 0xffffffff
    cpu.ecx = 4294967295 /*0xffffffff*/;
    // 0042f886  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 0042f888  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 0042f88a  89cb                   -mov ebx, ecx
    cpu.ebx = cpu.ecx;
    // 0042f88c  e85fecffff             -call 0x42e4f0
    cpu.esp -= 4;
    nfs3hp::raceload::cornerInBoxBack2(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042f891  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0042f893  7516                   -jne 0x42f8ab
    if (!cpu.flags.zf)
    {
        goto L_0x0042f8ab;
    }
    // 0042f895  6aff                   -push -1
    app->getMemory<x86::reg32>(cpu.esp-4) = -1 /*-0x1*/;
    cpu.esp -= 4;
    // 0042f897  b9ffffffff             -mov ecx, 0xffffffff
    cpu.ecx = 4294967295 /*0xffffffff*/;
    // 0042f89c  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 0042f89e  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 0042f8a0  89cb                   -mov ebx, ecx
    cpu.ebx = cpu.ecx;
    // 0042f8a2  e849ecffff             -call 0x42e4f0
    cpu.esp -= 4;
    nfs3hp::raceload::cornerInBoxBack2(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042f8a7  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0042f8a9  7405                   -je 0x42f8b0
    if (cpu.flags.zf)
    {
        goto L_0x0042f8b0;
    }
L_0x0042f8ab:
    // 0042f8ab  b804000000             -mov eax, 4
    cpu.eax = 4 /*0x4*/;
L_0x0042f8b0:
    // 0042f8b0  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f8b1  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f8b2  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f8b3  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f8b4  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042f8b5  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x54 0x22 0x00 */
void Application::sub_42f8c0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0042f8c0  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 0042f8c1  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 0042f8c2  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 0042f8c3  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 0042f8c4  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 0042f8c6  83ec7c                 -sub esp, 0x7c
    (cpu.esp) -= x86::reg32(x86::sreg32(124 /*0x7c*/));
    // 0042f8c9  89d1                   -mov ecx, edx
    cpu.ecx = cpu.edx;
    // 0042f8cb  85db                   +test ebx, ebx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & cpu.ebx));
    // 0042f8cd  7404                   -je 0x42f8d3
    if (cpu.flags.zf)
    {
        goto L_0x0042f8d3;
    }
    // 0042f8cf  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 0042f8d1  eb02                   -jmp 0x42f8d5
    goto L_0x0042f8d5;
L_0x0042f8d3:
    // 0042f8d3  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
L_0x0042f8d5:
    // 0042f8d5  d981a4000000           +fld dword ptr [ecx + 0xa4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(164) /* 0xa4 */));
    // 0042f8db  d8a2a4000000           +fsub dword ptr [edx + 0xa4]
    x86::Float fpu2 = cpu.fpu.sub(fpu1, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(164) /* 0xa4 */)));
    // 0042f8e1  d9ee                   +fldz 
    x86::Float fpu3 = 0.0;
    // 0042f8e3  d9c9                   +fxch st(1)
    
    // 0042f8e5  d95ddc                 +fstp dword ptr [ebp - 0x24]
    app->getMemory<float>(cpu.ebp + x86::reg32(-36) /* -0x24 */) = float(fpu2);
    // 0042f8e8  d85ddc                 +fcomp dword ptr [ebp - 0x24]
    cpu.fpu.compare(fpu3, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-36) /* -0x24 */)));
    // 0042f8eb  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 0042f8ed  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 0042f8ee  7308                   -jae 0x42f8f8
    if (!cpu.flags.cf)
    {
        goto L_0x0042f8f8;
    }
    // 0042f8f0  8b45dc                 -mov eax, dword ptr [ebp - 0x24]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-36) /* -0x24 */);
    // 0042f8f3  8945d0                 -mov dword ptr [ebp - 0x30], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-48) /* -0x30 */) = cpu.eax;
    // 0042f8f6  eb08                   -jmp 0x42f900
    goto L_0x0042f900;
L_0x0042f8f8:
    // 0042f8f8  d945dc                 +fld dword ptr [ebp - 0x24]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu4 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-36) /* -0x24 */));
    // 0042f8fb  d9e0                   +fchs 
    x86::Float fpu5 = -fpu4;
    // 0042f8fd  d95dd0                 +fstp dword ptr [ebp - 0x30]
    app->getMemory<float>(cpu.ebp + x86::reg32(-48) /* -0x30 */) = float(fpu5);
    }
L_0x0042f900:
    // 0042f900  d9ee                   +fldz 
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu6 = 0.0;
    // 0042f902  d981a8000000           +fld dword ptr [ecx + 0xa8]
    x86::Float fpu7 = x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(168) /* 0xa8 */));
    // 0042f908  8b45d0                 -mov eax, dword ptr [ebp - 0x30]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-48) /* -0x30 */);
    // 0042f90b  d8a2a8000000           +fsub dword ptr [edx + 0xa8]
    x86::Float fpu8 = cpu.fpu.sub(fpu7, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(168) /* 0xa8 */)));
    // 0042f911  8945c4                 -mov dword ptr [ebp - 0x3c], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-60) /* -0x3c */) = cpu.eax;
    // 0042f914  d95dec                 +fstp dword ptr [ebp - 0x14]
    app->getMemory<float>(cpu.ebp + x86::reg32(-20) /* -0x14 */) = float(fpu8);
    // 0042f917  d85dec                 +fcomp dword ptr [ebp - 0x14]
    cpu.fpu.compare(fpu6, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-20) /* -0x14 */)));
    // 0042f91a  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 0042f91c  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 0042f91d  7308                   -jae 0x42f927
    if (!cpu.flags.cf)
    {
        goto L_0x0042f927;
    }
    // 0042f91f  8b45ec                 -mov eax, dword ptr [ebp - 0x14]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */);
    // 0042f922  8945b8                 -mov dword ptr [ebp - 0x48], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-72) /* -0x48 */) = cpu.eax;
    // 0042f925  eb08                   -jmp 0x42f92f
    goto L_0x0042f92f;
L_0x0042f927:
    // 0042f927  d945ec                 +fld dword ptr [ebp - 0x14]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu9 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-20) /* -0x14 */));
    // 0042f92a  d9e0                   +fchs 
    x86::Float fpu10 = -fpu9;
    // 0042f92c  d95db8                 +fstp dword ptr [ebp - 0x48]
    app->getMemory<float>(cpu.ebp + x86::reg32(-72) /* -0x48 */) = float(fpu10);
    }
L_0x0042f92f:
    // 0042f92f  d9ee                   +fldz 
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu11 = 0.0;
    // 0042f931  d981ac000000           +fld dword ptr [ecx + 0xac]
    x86::Float fpu12 = x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(172) /* 0xac */));
    // 0042f937  8b45b8                 -mov eax, dword ptr [ebp - 0x48]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-72) /* -0x48 */);
    // 0042f93a  d8a2ac000000           +fsub dword ptr [edx + 0xac]
    x86::Float fpu13 = cpu.fpu.sub(fpu12, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(172) /* 0xac */)));
    // 0042f940  8945c8                 -mov dword ptr [ebp - 0x38], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-56) /* -0x38 */) = cpu.eax;
    // 0042f943  d95de8                 +fstp dword ptr [ebp - 0x18]
    app->getMemory<float>(cpu.ebp + x86::reg32(-24) /* -0x18 */) = float(fpu13);
    // 0042f946  d85de8                 +fcomp dword ptr [ebp - 0x18]
    cpu.fpu.compare(fpu11, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-24) /* -0x18 */)));
    // 0042f949  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 0042f94b  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 0042f94c  7308                   -jae 0x42f956
    if (!cpu.flags.cf)
    {
        goto L_0x0042f956;
    }
    // 0042f94e  8b45e8                 -mov eax, dword ptr [ebp - 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-24) /* -0x18 */);
    // 0042f951  8945bc                 -mov dword ptr [ebp - 0x44], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-68) /* -0x44 */) = cpu.eax;
    // 0042f954  eb08                   -jmp 0x42f95e
    goto L_0x0042f95e;
L_0x0042f956:
    // 0042f956  d945e8                 +fld dword ptr [ebp - 0x18]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu14 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-24) /* -0x18 */));
    // 0042f959  d9e0                   +fchs 
    x86::Float fpu15 = -fpu14;
    // 0042f95b  d95dbc                 +fstp dword ptr [ebp - 0x44]
    app->getMemory<float>(cpu.ebp + x86::reg32(-68) /* -0x44 */) = float(fpu15);
    }
L_0x0042f95e:
    // 0042f95e  8b45bc                 -mov eax, dword ptr [ebp - 0x44]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-68) /* -0x44 */);
    // 0042f961  8945f8                 -mov dword ptr [ebp - 8], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.eax;
    // 0042f964  8b45c4                 -mov eax, dword ptr [ebp - 0x3c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-60) /* -0x3c */);
    // 0042f967  d945c8                 +fld dword ptr [ebp - 0x38]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu16 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-56) /* -0x38 */));
    // 0042f96a  8945f4                 -mov dword ptr [ebp - 0xc], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.eax;
    // 0042f96d  d85dc4                 +fcomp dword ptr [ebp - 0x3c]
    cpu.fpu.compare(fpu16, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-60) /* -0x3c */)));
    // 0042f970  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 0042f972  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 0042f973  7606                   -jbe 0x42f97b
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x0042f97b;
    }
    // 0042f975  8b45c8                 -mov eax, dword ptr [ebp - 0x38]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-56) /* -0x38 */);
    // 0042f978  8945f4                 -mov dword ptr [ebp - 0xc], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.eax;
L_0x0042f97b:
    // 0042f97b  d945f8                 +fld dword ptr [ebp - 8]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu17 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */));
    // 0042f97e  d85df4                 +fcomp dword ptr [ebp - 0xc]
    cpu.fpu.compare(fpu17, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */)));
    // 0042f981  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 0042f983  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 0042f984  7606                   -jbe 0x42f98c
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x0042f98c;
    }
    // 0042f986  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 0042f989  8945f4                 -mov dword ptr [ebp - 0xc], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.eax;
L_0x0042f98c:
    // 0042f98c  d945f4                 +fld dword ptr [ebp - 0xc]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu18 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */));
    // 0042f98f  dc1dfc735300           +fcomp qword ptr [0x5373fc]
    cpu.fpu.compare(fpu18, x86::Float(app->getMemory<double>(x86::reg32(5469180) /* 0x5373fc */)));
    // 0042f995  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 0042f997  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 0042f998  0f8645020000           -jbe 0x42fbe3
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x0042fbe3;
    }
    // 0042f99e  8d7d84                 -lea edi, [ebp - 0x7c]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(-124) /* -0x7c */);
    // 0042f9a1  8db1a4000000           -lea esi, [ecx + 0xa4]
    cpu.esi = x86::reg32(cpu.ecx + x86::reg32(164) /* 0xa4 */);
    // 0042f9a7  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 0042f9a8  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 0042f9a9  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 0042f9aa  8d7d9c                 -lea edi, [ebp - 0x64]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(-100) /* -0x64 */);
    // 0042f9ad  8db2c0000000           -lea esi, [edx + 0xc0]
    cpu.esi = x86::reg32(cpu.edx + x86::reg32(192) /* 0xc0 */);
    // 0042f9b3  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 0042f9b4  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 0042f9b5  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 0042f9b6  8d7da8                 -lea edi, [ebp - 0x58]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(-88) /* -0x58 */);
    // 0042f9b9  8db2cc000000           -lea esi, [edx + 0xcc]
    cpu.esi = x86::reg32(cpu.edx + x86::reg32(204) /* 0xcc */);
    // 0042f9bf  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 0042f9c0  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 0042f9c1  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 0042f9c2  8d7d90                 -lea edi, [ebp - 0x70]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(-112) /* -0x70 */);
    // 0042f9c5  8db2d8000000           -lea esi, [edx + 0xd8]
    cpu.esi = x86::reg32(cpu.edx + x86::reg32(216) /* 0xd8 */);
    // 0042f9cb  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 0042f9cc  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 0042f9cd  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 0042f9ce  85db                   +test ebx, ebx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & cpu.ebx));
    // 0042f9d0  741a                   -je 0x42f9ec
    if (cpu.flags.zf)
    {
        goto L_0x0042f9ec;
    }
    // 0042f9d2  d90504ff5e00           +fld dword ptr [0x5eff04]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu19 = x86::Float(app->getMemory<float>(x86::reg32(6225668) /* 0x5eff04 */));
    // 0042f9d8  d9ee                   +fldz 
    x86::Float fpu20 = 0.0;
    // 0042f9da  ded9                   +fcompp 
    cpu.fpu.compare(fpu20, fpu19);
    // 0042f9dc  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 0042f9de  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 0042f9df  7307                   -jae 0x42f9e8
    if (!cpu.flags.cf)
    {
        goto L_0x0042f9e8;
    }
    // 0042f9e1  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 0042f9e6  eb1c                   -jmp 0x42fa04
    goto L_0x0042fa04;
L_0x0042f9e8:
    // 0042f9e8  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
    // 0042f9ea  eb18                   -jmp 0x42fa04
    goto L_0x0042fa04;
L_0x0042f9ec:
    // 0042f9ec  d90504ff5e00           +fld dword ptr [0x5eff04]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu21 = x86::Float(app->getMemory<float>(x86::reg32(6225668) /* 0x5eff04 */));
    // 0042f9f2  d9ee                   +fldz 
    x86::Float fpu22 = 0.0;
    // 0042f9f4  ded9                   +fcompp 
    cpu.fpu.compare(fpu22, fpu21);
    // 0042f9f6  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 0042f9f8  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 0042f9f9  7607                   -jbe 0x42fa02
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x0042fa02;
    }
    // 0042f9fb  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 0042fa00  eb02                   -jmp 0x42fa04
    goto L_0x0042fa04;
L_0x0042fa02:
    // 0042fa02  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
L_0x0042fa04:
    // 0042fa04  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0042fa06  741b                   -je 0x42fa23
    if (cpu.flags.zf)
    {
        goto L_0x0042fa23;
    }
    // 0042fa08  8a55a3                 -mov dl, byte ptr [ebp - 0x5d]
    cpu.dl = app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-93) /* -0x5d */);
    // 0042fa0b  80f280                 -xor dl, 0x80
    cpu.dl ^= x86::reg8(x86::sreg8(128 /*0x80*/));
    // 0042fa0e  8a659f                 -mov ah, byte ptr [ebp - 0x61]
    cpu.ah = app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-97) /* -0x61 */);
    // 0042fa11  8855a3                 -mov byte ptr [ebp - 0x5d], dl
    app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-93) /* -0x5d */) = cpu.dl;
    // 0042fa14  8a75a7                 -mov dh, byte ptr [ebp - 0x59]
    cpu.dh = app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-89) /* -0x59 */);
    // 0042fa17  80f480                 -xor ah, 0x80
    cpu.ah ^= x86::reg8(x86::sreg8(128 /*0x80*/));
    // 0042fa1a  80f680                 -xor dh, 0x80
    cpu.dh ^= x86::reg8(x86::sreg8(128 /*0x80*/));
    // 0042fa1d  88659f                 -mov byte ptr [ebp - 0x61], ah
    app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-97) /* -0x61 */) = cpu.ah;
    // 0042fa20  8875a7                 -mov byte ptr [ebp - 0x59], dh
    app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-89) /* -0x59 */) = cpu.dh;
L_0x0042fa23:
    // 0042fa23  85db                   +test ebx, ebx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & cpu.ebx));
    // 0042fa25  741a                   -je 0x42fa41
    if (cpu.flags.zf)
    {
        goto L_0x0042fa41;
    }
    // 0042fa27  d905b4fe5e00           +fld dword ptr [0x5efeb4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu23 = x86::Float(app->getMemory<float>(x86::reg32(6225588) /* 0x5efeb4 */));
    // 0042fa2d  d9ee                   +fldz 
    x86::Float fpu24 = 0.0;
    // 0042fa2f  ded9                   +fcompp 
    cpu.fpu.compare(fpu24, fpu23);
    // 0042fa31  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 0042fa33  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 0042fa34  7307                   -jae 0x42fa3d
    if (!cpu.flags.cf)
    {
        goto L_0x0042fa3d;
    }
    // 0042fa36  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 0042fa3b  eb1c                   -jmp 0x42fa59
    goto L_0x0042fa59;
L_0x0042fa3d:
    // 0042fa3d  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
    // 0042fa3f  eb18                   -jmp 0x42fa59
    goto L_0x0042fa59;
L_0x0042fa41:
    // 0042fa41  d905b4fe5e00           +fld dword ptr [0x5efeb4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu25 = x86::Float(app->getMemory<float>(x86::reg32(6225588) /* 0x5efeb4 */));
    // 0042fa47  d9ee                   +fldz 
    x86::Float fpu26 = 0.0;
    // 0042fa49  ded9                   +fcompp 
    cpu.fpu.compare(fpu26, fpu25);
    // 0042fa4b  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 0042fa4d  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 0042fa4e  7607                   -jbe 0x42fa57
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x0042fa57;
    }
    // 0042fa50  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 0042fa55  eb02                   -jmp 0x42fa59
    goto L_0x0042fa59;
L_0x0042fa57:
    // 0042fa57  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
L_0x0042fa59:
    // 0042fa59  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0042fa5b  741a                   -je 0x42fa77
    if (cpu.flags.zf)
    {
        goto L_0x0042fa77;
    }
    // 0042fa5d  8a4dab                 -mov cl, byte ptr [ebp - 0x55]
    cpu.cl = app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-85) /* -0x55 */);
    // 0042fa60  80f180                 -xor cl, 0x80
    cpu.cl ^= x86::reg8(x86::sreg8(128 /*0x80*/));
    // 0042fa63  8a45b3                 -mov al, byte ptr [ebp - 0x4d]
    cpu.al = app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-77) /* -0x4d */);
    // 0042fa66  884dab                 -mov byte ptr [ebp - 0x55], cl
    app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-85) /* -0x55 */) = cpu.cl;
    // 0042fa69  8a6daf                 -mov ch, byte ptr [ebp - 0x51]
    cpu.ch = app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-81) /* -0x51 */);
    // 0042fa6c  3480                   -xor al, 0x80
    cpu.al ^= x86::reg8(x86::sreg8(128 /*0x80*/));
    // 0042fa6e  80f580                 -xor ch, 0x80
    cpu.ch ^= x86::reg8(x86::sreg8(128 /*0x80*/));
    // 0042fa71  8845b3                 -mov byte ptr [ebp - 0x4d], al
    app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-77) /* -0x4d */) = cpu.al;
    // 0042fa74  886daf                 -mov byte ptr [ebp - 0x51], ch
    app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-81) /* -0x51 */) = cpu.ch;
L_0x0042fa77:
    // 0042fa77  85db                   +test ebx, ebx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & cpu.ebx));
    // 0042fa79  741a                   -je 0x42fa95
    if (cpu.flags.zf)
    {
        goto L_0x0042fa95;
    }
    // 0042fa7b  d905b8fe5e00           +fld dword ptr [0x5efeb8]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu27 = x86::Float(app->getMemory<float>(x86::reg32(6225592) /* 0x5efeb8 */));
    // 0042fa81  d9ee                   +fldz 
    x86::Float fpu28 = 0.0;
    // 0042fa83  ded9                   +fcompp 
    cpu.fpu.compare(fpu28, fpu27);
    // 0042fa85  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 0042fa87  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 0042fa88  7307                   -jae 0x42fa91
    if (!cpu.flags.cf)
    {
        goto L_0x0042fa91;
    }
    // 0042fa8a  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 0042fa8f  eb1c                   -jmp 0x42faad
    goto L_0x0042faad;
L_0x0042fa91:
    // 0042fa91  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
    // 0042fa93  eb18                   -jmp 0x42faad
    goto L_0x0042faad;
L_0x0042fa95:
    // 0042fa95  d905b8fe5e00           +fld dword ptr [0x5efeb8]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu29 = x86::Float(app->getMemory<float>(x86::reg32(6225592) /* 0x5efeb8 */));
    // 0042fa9b  d9ee                   +fldz 
    x86::Float fpu30 = 0.0;
    // 0042fa9d  ded9                   +fcompp 
    cpu.fpu.compare(fpu30, fpu29);
    // 0042fa9f  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 0042faa1  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 0042faa2  7607                   -jbe 0x42faab
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x0042faab;
    }
    // 0042faa4  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 0042faa9  eb02                   -jmp 0x42faad
    goto L_0x0042faad;
L_0x0042faab:
    // 0042faab  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
L_0x0042faad:
    // 0042faad  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0042faaf  741b                   -je 0x42facc
    if (cpu.flags.zf)
    {
        goto L_0x0042facc;
    }
    // 0042fab1  8a5597                 -mov dl, byte ptr [ebp - 0x69]
    cpu.dl = app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-105) /* -0x69 */);
    // 0042fab4  80f280                 -xor dl, 0x80
    cpu.dl ^= x86::reg8(x86::sreg8(128 /*0x80*/));
    // 0042fab7  8a6593                 -mov ah, byte ptr [ebp - 0x6d]
    cpu.ah = app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-109) /* -0x6d */);
    // 0042faba  885597                 -mov byte ptr [ebp - 0x69], dl
    app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-105) /* -0x69 */) = cpu.dl;
    // 0042fabd  8a759b                 -mov dh, byte ptr [ebp - 0x65]
    cpu.dh = app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-101) /* -0x65 */);
    // 0042fac0  80f480                 -xor ah, 0x80
    cpu.ah ^= x86::reg8(x86::sreg8(128 /*0x80*/));
    // 0042fac3  80f680                 +xor dh, 0x80
    cpu.clear_co();
    cpu.set_szp((cpu.dh ^= x86::reg8(x86::sreg8(128 /*0x80*/))));
    // 0042fac6  886593                 -mov byte ptr [ebp - 0x6d], ah
    app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-109) /* -0x6d */) = cpu.ah;
    // 0042fac9  88759b                 -mov byte ptr [ebp - 0x65], dh
    app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-101) /* -0x65 */) = cpu.dh;
L_0x0042facc:
    // 0042facc  8d5584                 -lea edx, [ebp - 0x7c]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-124) /* -0x7c */);
    // 0042facf  8d459c                 -lea eax, [ebp - 0x64]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-100) /* -0x64 */);
    // 0042fad2  e819070b00             -call 0x4e01f0
    cpu.esp -= 4;
    sub_4e01f0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042fad7  d9ee                   +fldz 
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu31 = 0.0;
    // 0042fad9  ded9                   +fcompp 
    x86::Float fpu32 = cpu.fpu.st(0);
    cpu.fpu.compare(fpu31, fpu32);
    // 0042fadb  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 0042fadd  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    cpu.fpu.count -= 1;
    }
    // 0042fade  730d                   -jae 0x42faed
    if (!cpu.flags.cf)
    {
        goto L_0x0042faed;
    }
    // 0042fae0  8d5584                 -lea edx, [ebp - 0x7c]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-124) /* -0x7c */);
    // 0042fae3  8d459c                 -lea eax, [ebp - 0x64]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-100) /* -0x64 */);
    // 0042fae6  e805070b00             -call 0x4e01f0
    cpu.esp -= 4;
    sub_4e01f0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042faeb  eb0d                   -jmp 0x42fafa
    goto L_0x0042fafa;
L_0x0042faed:
    // 0042faed  8d5584                 -lea edx, [ebp - 0x7c]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-124) /* -0x7c */);
    // 0042faf0  8d459c                 -lea eax, [ebp - 0x64]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-100) /* -0x64 */);
    // 0042faf3  e8f8060b00             -call 0x4e01f0
    cpu.esp -= 4;
    sub_4e01f0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042faf8  d9e0                   +fchs 
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu33 = cpu.fpu.st(0);
    x86::Float fpu34 = -fpu33;
    cpu.fpu.st(0) = fpu34;
    }
L_0x0042fafa:
    // 0042fafa  d95dfc                 +fstp dword ptr [ebp - 4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu35 = cpu.fpu.st(0);
    app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = float(fpu35);
    // 0042fafd  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 0042fb00  8d5584                 -lea edx, [ebp - 0x7c]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-124) /* -0x7c */);
    // 0042fb03  8945d4                 -mov dword ptr [ebp - 0x2c], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-44) /* -0x2c */) = cpu.eax;
    // 0042fb06  8d45a8                 -lea eax, [ebp - 0x58]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-88) /* -0x58 */);
    cpu.fpu.count -= 1;
    }
    // 0042fb09  e8e2060b00             -call 0x4e01f0
    cpu.esp -= 4;
    sub_4e01f0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042fb0e  d9ee                   +fldz 
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu36 = 0.0;
    // 0042fb10  ded9                   +fcompp 
    x86::Float fpu37 = cpu.fpu.st(0);
    cpu.fpu.compare(fpu36, fpu37);
    // 0042fb12  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 0042fb14  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    cpu.fpu.count -= 1;
    }
    // 0042fb15  730d                   -jae 0x42fb24
    if (!cpu.flags.cf)
    {
        goto L_0x0042fb24;
    }
    // 0042fb17  8d5584                 -lea edx, [ebp - 0x7c]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-124) /* -0x7c */);
    // 0042fb1a  8d45a8                 -lea eax, [ebp - 0x58]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-88) /* -0x58 */);
    // 0042fb1d  e8ce060b00             -call 0x4e01f0
    cpu.esp -= 4;
    sub_4e01f0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042fb22  eb0d                   -jmp 0x42fb31
    goto L_0x0042fb31;
L_0x0042fb24:
    // 0042fb24  8d5584                 -lea edx, [ebp - 0x7c]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-124) /* -0x7c */);
    // 0042fb27  8d45a8                 -lea eax, [ebp - 0x58]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-88) /* -0x58 */);
    // 0042fb2a  e8c1060b00             -call 0x4e01f0
    cpu.esp -= 4;
    sub_4e01f0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042fb2f  d9e0                   +fchs 
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu38 = cpu.fpu.st(0);
    x86::Float fpu39 = -fpu38;
    cpu.fpu.st(0) = fpu39;
    }
L_0x0042fb31:
    // 0042fb31  d95dc0                 +fstp dword ptr [ebp - 0x40]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu40 = cpu.fpu.st(0);
    app->getMemory<float>(cpu.ebp + x86::reg32(-64) /* -0x40 */) = float(fpu40);
    // 0042fb34  8b45c0                 -mov eax, dword ptr [ebp - 0x40]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-64) /* -0x40 */);
    // 0042fb37  8d5584                 -lea edx, [ebp - 0x7c]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-124) /* -0x7c */);
    // 0042fb3a  8945cc                 -mov dword ptr [ebp - 0x34], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-52) /* -0x34 */) = cpu.eax;
    // 0042fb3d  8d4590                 -lea eax, [ebp - 0x70]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-112) /* -0x70 */);
    cpu.fpu.count -= 1;
    }
    // 0042fb40  e8ab060b00             -call 0x4e01f0
    cpu.esp -= 4;
    sub_4e01f0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042fb45  d9ee                   +fldz 
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu41 = 0.0;
    // 0042fb47  ded9                   +fcompp 
    x86::Float fpu42 = cpu.fpu.st(0);
    cpu.fpu.compare(fpu41, fpu42);
    // 0042fb49  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 0042fb4b  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    cpu.fpu.count -= 1;
    }
    // 0042fb4c  730d                   -jae 0x42fb5b
    if (!cpu.flags.cf)
    {
        goto L_0x0042fb5b;
    }
    // 0042fb4e  8d5584                 -lea edx, [ebp - 0x7c]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-124) /* -0x7c */);
    // 0042fb51  8d4590                 -lea eax, [ebp - 0x70]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-112) /* -0x70 */);
    // 0042fb54  e897060b00             -call 0x4e01f0
    cpu.esp -= 4;
    sub_4e01f0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042fb59  eb0d                   -jmp 0x42fb68
    goto L_0x0042fb68;
L_0x0042fb5b:
    // 0042fb5b  8d5584                 -lea edx, [ebp - 0x7c]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-124) /* -0x7c */);
    // 0042fb5e  8d4590                 -lea eax, [ebp - 0x70]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-112) /* -0x70 */);
    // 0042fb61  e88a060b00             -call 0x4e01f0
    cpu.esp -= 4;
    sub_4e01f0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042fb66  d9e0                   +fchs 
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu43 = cpu.fpu.st(0);
    x86::Float fpu44 = -fpu43;
    cpu.fpu.st(0) = fpu44;
    }
L_0x0042fb68:
    // 0042fb68  d95df0                 +fstp dword ptr [ebp - 0x10]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu45 = cpu.fpu.st(0);
    app->getMemory<float>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = float(fpu45);
    // 0042fb6b  8b45f0                 -mov eax, dword ptr [ebp - 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 0042fb6e  d945d4                 +fld dword ptr [ebp - 0x2c]
    x86::Float fpu46 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-44) /* -0x2c */));
    // 0042fb71  8945b4                 -mov dword ptr [ebp - 0x4c], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-76) /* -0x4c */) = cpu.eax;
    // 0042fb74  d85dcc                 +fcomp dword ptr [ebp - 0x34]
    cpu.fpu.compare(fpu46, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-52) /* -0x34 */)));
    // 0042fb77  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 0042fb79  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    cpu.fpu.count -= 1;
    }
    // 0042fb7a  7620                   -jbe 0x42fb9c
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x0042fb9c;
    }
    // 0042fb7c  d945d4                 +fld dword ptr [ebp - 0x2c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu47 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-44) /* -0x2c */));
    // 0042fb7f  d85df0                 +fcomp dword ptr [ebp - 0x10]
    cpu.fpu.compare(fpu47, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-16) /* -0x10 */)));
    // 0042fb82  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 0042fb84  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 0042fb85  7615                   -jbe 0x42fb9c
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x0042fb9c;
    }
    // 0042fb87  8b459c                 -mov eax, dword ptr [ebp - 0x64]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-100) /* -0x64 */);
    // 0042fb8a  a378fe5e00             -mov dword ptr [0x5efe78], eax
    app->getMemory<x86::reg32>(x86::reg32(6225528) /* 0x5efe78 */) = cpu.eax;
    // 0042fb8f  8b45a0                 -mov eax, dword ptr [ebp - 0x60]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-96) /* -0x60 */);
    // 0042fb92  a37cfe5e00             -mov dword ptr [0x5efe7c], eax
    app->getMemory<x86::reg32>(x86::reg32(6225532) /* 0x5efe7c */) = cpu.eax;
    // 0042fb97  8b45a4                 -mov eax, dword ptr [ebp - 0x5c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-92) /* -0x5c */);
    // 0042fb9a  eb3b                   -jmp 0x42fbd7
    goto L_0x0042fbd7;
L_0x0042fb9c:
    // 0042fb9c  d945cc                 +fld dword ptr [ebp - 0x34]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu48 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-52) /* -0x34 */));
    // 0042fb9f  d85db4                 +fcomp dword ptr [ebp - 0x4c]
    cpu.fpu.compare(fpu48, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-76) /* -0x4c */)));
    // 0042fba2  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 0042fba4  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 0042fba5  761d                   -jbe 0x42fbc4
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x0042fbc4;
    }
    // 0042fba7  8b45a8                 -mov eax, dword ptr [ebp - 0x58]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-88) /* -0x58 */);
    // 0042fbaa  a378fe5e00             -mov dword ptr [0x5efe78], eax
    app->getMemory<x86::reg32>(x86::reg32(6225528) /* 0x5efe78 */) = cpu.eax;
    // 0042fbaf  8b45ac                 -mov eax, dword ptr [ebp - 0x54]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-84) /* -0x54 */);
    // 0042fbb2  a37cfe5e00             -mov dword ptr [0x5efe7c], eax
    app->getMemory<x86::reg32>(x86::reg32(6225532) /* 0x5efe7c */) = cpu.eax;
    // 0042fbb7  8b45b0                 -mov eax, dword ptr [ebp - 0x50]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-80) /* -0x50 */);
    // 0042fbba  a380fe5e00             -mov dword ptr [0x5efe80], eax
    app->getMemory<x86::reg32>(x86::reg32(6225536) /* 0x5efe80 */) = cpu.eax;
    // 0042fbbf  e942020000             -jmp 0x42fe06
    goto L_0x0042fe06;
L_0x0042fbc4:
    // 0042fbc4  8b4590                 -mov eax, dword ptr [ebp - 0x70]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-112) /* -0x70 */);
    // 0042fbc7  a378fe5e00             -mov dword ptr [0x5efe78], eax
    app->getMemory<x86::reg32>(x86::reg32(6225528) /* 0x5efe78 */) = cpu.eax;
    // 0042fbcc  8b4594                 -mov eax, dword ptr [ebp - 0x6c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-108) /* -0x6c */);
    // 0042fbcf  a37cfe5e00             -mov dword ptr [0x5efe7c], eax
    app->getMemory<x86::reg32>(x86::reg32(6225532) /* 0x5efe7c */) = cpu.eax;
    // 0042fbd4  8b4598                 -mov eax, dword ptr [ebp - 0x68]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-104) /* -0x68 */);
L_0x0042fbd7:
    // 0042fbd7  a380fe5e00             -mov dword ptr [0x5efe80], eax
    app->getMemory<x86::reg32>(x86::reg32(6225536) /* 0x5efe80 */) = cpu.eax;
    // 0042fbdc  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 0042fbde  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042fbdf  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042fbe0  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042fbe1  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042fbe2  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x0042fbe3:
    // 0042fbe3  d90504ff5e00           +fld dword ptr [0x5eff04]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu49 = x86::Float(app->getMemory<float>(x86::reg32(6225668) /* 0x5eff04 */));
    // 0042fbe9  d9ee                   +fldz 
    x86::Float fpu50 = 0.0;
    // 0042fbeb  ded9                   +fcompp 
    cpu.fpu.compare(fpu50, fpu49);
    // 0042fbed  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 0042fbef  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 0042fbf0  760e                   -jbe 0x42fc00
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x0042fc00;
    }
    // 0042fbf2  d98214010000           +fld dword ptr [edx + 0x114]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu51 = x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(276) /* 0x114 */));
    // 0042fbf8  d80504ff5e00           +fadd dword ptr [0x5eff04]
    x86::Float fpu52 = cpu.fpu.add(fpu51, x86::Float(app->getMemory<float>(x86::reg32(6225668) /* 0x5eff04 */)));
    cpu.fpu.count += 1;
    cpu.fpu.st(0) = fpu52;
    }
    // 0042fbfe  eb0c                   -jmp 0x42fc0c
    goto L_0x0042fc0c;
L_0x0042fc00:
    // 0042fc00  d98214010000           +fld dword ptr [edx + 0x114]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu53 = x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(276) /* 0x114 */));
    // 0042fc06  d82504ff5e00           +fsub dword ptr [0x5eff04]
    x86::Float fpu54 = cpu.fpu.sub(fpu53, x86::Float(app->getMemory<float>(x86::reg32(6225668) /* 0x5eff04 */)));
    cpu.fpu.count += 1;
    cpu.fpu.st(0) = fpu54;
    }
L_0x0042fc0c:
    // 0042fc0c  d95de0                 +fstp dword ptr [ebp - 0x20]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu55 = cpu.fpu.st(0);
    app->getMemory<float>(cpu.ebp + x86::reg32(-32) /* -0x20 */) = float(fpu55);
    // 0042fc0f  d905b4fe5e00           +fld dword ptr [0x5efeb4]
    x86::Float fpu56 = x86::Float(app->getMemory<float>(x86::reg32(6225588) /* 0x5efeb4 */));
    // 0042fc15  d9ee                   +fldz 
    x86::Float fpu57 = 0.0;
    // 0042fc17  ded9                   +fcompp 
    cpu.fpu.compare(fpu57, fpu56);
    // 0042fc19  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 0042fc1b  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    cpu.fpu.count -= 1;
    }
    // 0042fc1c  760e                   -jbe 0x42fc2c
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x0042fc2c;
    }
    // 0042fc1e  d98218010000           +fld dword ptr [edx + 0x118]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu58 = x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(280) /* 0x118 */));
    // 0042fc24  d805b4fe5e00           +fadd dword ptr [0x5efeb4]
    x86::Float fpu59 = cpu.fpu.add(fpu58, x86::Float(app->getMemory<float>(x86::reg32(6225588) /* 0x5efeb4 */)));
    cpu.fpu.count += 1;
    cpu.fpu.st(0) = fpu59;
    }
    // 0042fc2a  eb0c                   -jmp 0x42fc38
    goto L_0x0042fc38;
L_0x0042fc2c:
    // 0042fc2c  d98218010000           +fld dword ptr [edx + 0x118]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu60 = x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(280) /* 0x118 */));
    // 0042fc32  d825b4fe5e00           +fsub dword ptr [0x5efeb4]
    x86::Float fpu61 = cpu.fpu.sub(fpu60, x86::Float(app->getMemory<float>(x86::reg32(6225588) /* 0x5efeb4 */)));
    cpu.fpu.count += 1;
    cpu.fpu.st(0) = fpu61;
    }
L_0x0042fc38:
    // 0042fc38  d95de4                 +fstp dword ptr [ebp - 0x1c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu62 = cpu.fpu.st(0);
    app->getMemory<float>(cpu.ebp + x86::reg32(-28) /* -0x1c */) = float(fpu62);
    // 0042fc3b  d905b8fe5e00           +fld dword ptr [0x5efeb8]
    x86::Float fpu63 = x86::Float(app->getMemory<float>(x86::reg32(6225592) /* 0x5efeb8 */));
    // 0042fc41  d9ee                   +fldz 
    x86::Float fpu64 = 0.0;
    // 0042fc43  ded9                   +fcompp 
    cpu.fpu.compare(fpu64, fpu63);
    // 0042fc45  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 0042fc47  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    cpu.fpu.count -= 1;
    }
    // 0042fc48  760e                   -jbe 0x42fc58
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x0042fc58;
    }
    // 0042fc4a  d9821c010000           +fld dword ptr [edx + 0x11c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu65 = x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(284) /* 0x11c */));
    // 0042fc50  d805b8fe5e00           +fadd dword ptr [0x5efeb8]
    x86::Float fpu66 = cpu.fpu.add(fpu65, x86::Float(app->getMemory<float>(x86::reg32(6225592) /* 0x5efeb8 */)));
    cpu.fpu.count += 1;
    cpu.fpu.st(0) = fpu66;
    }
    // 0042fc56  eb0c                   -jmp 0x42fc64
    goto L_0x0042fc64;
L_0x0042fc58:
    // 0042fc58  d9821c010000           +fld dword ptr [edx + 0x11c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu67 = x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(284) /* 0x11c */));
    // 0042fc5e  d825b8fe5e00           +fsub dword ptr [0x5efeb8]
    x86::Float fpu68 = cpu.fpu.sub(fpu67, x86::Float(app->getMemory<float>(x86::reg32(6225592) /* 0x5efeb8 */)));
    cpu.fpu.count += 1;
    cpu.fpu.st(0) = fpu68;
    }
L_0x0042fc64:
    // 0042fc64  d95dd8                 +fstp dword ptr [ebp - 0x28]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu69 = cpu.fpu.st(0);
    app->getMemory<float>(cpu.ebp + x86::reg32(-40) /* -0x28 */) = float(fpu69);
    // 0042fc67  d945e0                 +fld dword ptr [ebp - 0x20]
    x86::Float fpu70 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-32) /* -0x20 */));
    // 0042fc6a  d85de4                 +fcomp dword ptr [ebp - 0x1c]
    cpu.fpu.compare(fpu70, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-28) /* -0x1c */)));
    // 0042fc6d  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 0042fc6f  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    cpu.fpu.count -= 1;
    }
    // 0042fc70  0f838f000000           -jae 0x42fd05
    if (!cpu.flags.cf)
    {
        goto L_0x0042fd05;
    }
    // 0042fc76  d945e0                 +fld dword ptr [ebp - 0x20]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu71 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-32) /* -0x20 */));
    // 0042fc79  d85dd8                 +fcomp dword ptr [ebp - 0x28]
    cpu.fpu.compare(fpu71, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-40) /* -0x28 */)));
    // 0042fc7c  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 0042fc7e  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 0042fc7f  0f8380000000           -jae 0x42fd05
    if (!cpu.flags.cf)
    {
        goto L_0x0042fd05;
    }
    // 0042fc85  bf78fe5e00             -mov edi, 0x5efe78
    cpu.edi = 6225528 /*0x5efe78*/;
    // 0042fc8a  8db2c0000000           -lea esi, [edx + 0xc0]
    cpu.esi = x86::reg32(cpu.edx + x86::reg32(192) /* 0xc0 */);
    // 0042fc90  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 0042fc91  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 0042fc92  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 0042fc93  85db                   +test ebx, ebx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & cpu.ebx));
    // 0042fc95  741a                   -je 0x42fcb1
    if (cpu.flags.zf)
    {
        goto L_0x0042fcb1;
    }
    // 0042fc97  d90504ff5e00           +fld dword ptr [0x5eff04]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu72 = x86::Float(app->getMemory<float>(x86::reg32(6225668) /* 0x5eff04 */));
    // 0042fc9d  d9ee                   +fldz 
    x86::Float fpu73 = 0.0;
    // 0042fc9f  ded9                   +fcompp 
    cpu.fpu.compare(fpu73, fpu72);
    // 0042fca1  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 0042fca3  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 0042fca4  7307                   -jae 0x42fcad
    if (!cpu.flags.cf)
    {
        goto L_0x0042fcad;
    }
    // 0042fca6  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 0042fcab  eb1c                   -jmp 0x42fcc9
    goto L_0x0042fcc9;
L_0x0042fcad:
    // 0042fcad  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
    // 0042fcaf  eb18                   -jmp 0x42fcc9
    goto L_0x0042fcc9;
L_0x0042fcb1:
    // 0042fcb1  d90504ff5e00           +fld dword ptr [0x5eff04]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu74 = x86::Float(app->getMemory<float>(x86::reg32(6225668) /* 0x5eff04 */));
    // 0042fcb7  d9ee                   +fldz 
    x86::Float fpu75 = 0.0;
    // 0042fcb9  ded9                   +fcompp 
    cpu.fpu.compare(fpu75, fpu74);
    // 0042fcbb  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 0042fcbd  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 0042fcbe  7607                   -jbe 0x42fcc7
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x0042fcc7;
    }
    // 0042fcc0  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 0042fcc5  eb02                   -jmp 0x42fcc9
    goto L_0x0042fcc9;
L_0x0042fcc7:
    // 0042fcc7  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
L_0x0042fcc9:
    // 0042fcc9  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0042fccb  0f8435010000           -je 0x42fe06
    if (cpu.flags.zf)
    {
        goto L_0x0042fe06;
    }
    // 0042fcd1  8a1d7bfe5e00           -mov bl, byte ptr [0x5efe7b]
    cpu.bl = app->getMemory<x86::reg8>(x86::reg32(6225531) /* 0x5efe7b */);
    // 0042fcd7  80f380                 -xor bl, 0x80
    cpu.bl ^= x86::reg8(x86::sreg8(128 /*0x80*/));
    // 0042fcda  8a0d83fe5e00           -mov cl, byte ptr [0x5efe83]
    cpu.cl = app->getMemory<x86::reg8>(x86::reg32(6225539) /* 0x5efe83 */);
    // 0042fce0  881d7bfe5e00           -mov byte ptr [0x5efe7b], bl
    app->getMemory<x86::reg8>(x86::reg32(6225531) /* 0x5efe7b */) = cpu.bl;
    // 0042fce6  8a3d7ffe5e00           -mov bh, byte ptr [0x5efe7f]
    cpu.bh = app->getMemory<x86::reg8>(x86::reg32(6225535) /* 0x5efe7f */);
    // 0042fcec  80f180                 -xor cl, 0x80
    cpu.cl ^= x86::reg8(x86::sreg8(128 /*0x80*/));
    // 0042fcef  80f780                 +xor bh, 0x80
    cpu.clear_co();
    cpu.set_szp((cpu.bh ^= x86::reg8(x86::sreg8(128 /*0x80*/))));
    // 0042fcf2  880d83fe5e00           -mov byte ptr [0x5efe83], cl
    app->getMemory<x86::reg8>(x86::reg32(6225539) /* 0x5efe83 */) = cpu.cl;
    // 0042fcf8  883d7ffe5e00           -mov byte ptr [0x5efe7f], bh
    app->getMemory<x86::reg8>(x86::reg32(6225535) /* 0x5efe7f */) = cpu.bh;
    // 0042fcfe  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 0042fd00  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042fd01  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042fd02  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042fd03  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042fd04  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x0042fd05:
    // 0042fd05  d945e4                 +fld dword ptr [ebp - 0x1c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu76 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-28) /* -0x1c */));
    // 0042fd08  d85dd8                 +fcomp dword ptr [ebp - 0x28]
    cpu.fpu.compare(fpu76, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-40) /* -0x28 */)));
    // 0042fd0b  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 0042fd0d  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 0042fd0e  0f837d000000           -jae 0x42fd91
    if (!cpu.flags.cf)
    {
        goto L_0x0042fd91;
    }
    // 0042fd14  bf78fe5e00             -mov edi, 0x5efe78
    cpu.edi = 6225528 /*0x5efe78*/;
    // 0042fd19  8db2cc000000           -lea esi, [edx + 0xcc]
    cpu.esi = x86::reg32(cpu.edx + x86::reg32(204) /* 0xcc */);
    // 0042fd1f  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 0042fd20  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 0042fd21  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 0042fd22  85db                   +test ebx, ebx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & cpu.ebx));
    // 0042fd24  741a                   -je 0x42fd40
    if (cpu.flags.zf)
    {
        goto L_0x0042fd40;
    }
    // 0042fd26  d905b4fe5e00           +fld dword ptr [0x5efeb4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu77 = x86::Float(app->getMemory<float>(x86::reg32(6225588) /* 0x5efeb4 */));
    // 0042fd2c  d9ee                   +fldz 
    x86::Float fpu78 = 0.0;
    // 0042fd2e  ded9                   +fcompp 
    cpu.fpu.compare(fpu78, fpu77);
    // 0042fd30  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 0042fd32  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 0042fd33  7307                   -jae 0x42fd3c
    if (!cpu.flags.cf)
    {
        goto L_0x0042fd3c;
    }
    // 0042fd35  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 0042fd3a  eb1c                   -jmp 0x42fd58
    goto L_0x0042fd58;
L_0x0042fd3c:
    // 0042fd3c  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
    // 0042fd3e  eb18                   -jmp 0x42fd58
    goto L_0x0042fd58;
L_0x0042fd40:
    // 0042fd40  d905b4fe5e00           +fld dword ptr [0x5efeb4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu79 = x86::Float(app->getMemory<float>(x86::reg32(6225588) /* 0x5efeb4 */));
    // 0042fd46  d9ee                   +fldz 
    x86::Float fpu80 = 0.0;
    // 0042fd48  ded9                   +fcompp 
    cpu.fpu.compare(fpu80, fpu79);
    // 0042fd4a  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 0042fd4c  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 0042fd4d  7607                   -jbe 0x42fd56
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x0042fd56;
    }
    // 0042fd4f  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 0042fd54  eb02                   -jmp 0x42fd58
    goto L_0x0042fd58;
L_0x0042fd56:
    // 0042fd56  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
L_0x0042fd58:
    // 0042fd58  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0042fd5a  0f84a6000000           -je 0x42fe06
    if (cpu.flags.zf)
    {
        goto L_0x0042fe06;
    }
    // 0042fd60  a07ffe5e00             -mov al, byte ptr [0x5efe7f]
    cpu.al = app->getMemory<x86::reg8>(x86::reg32(6225535) /* 0x5efe7f */);
    // 0042fd65  3480                   -xor al, 0x80
    cpu.al ^= x86::reg8(x86::sreg8(128 /*0x80*/));
    // 0042fd67  8a2d7bfe5e00           -mov ch, byte ptr [0x5efe7b]
    cpu.ch = app->getMemory<x86::reg8>(x86::reg32(6225531) /* 0x5efe7b */);
    // 0042fd6d  a27ffe5e00             -mov byte ptr [0x5efe7f], al
    app->getMemory<x86::reg8>(x86::reg32(6225535) /* 0x5efe7f */) = cpu.al;
    // 0042fd72  8a2583fe5e00           -mov ah, byte ptr [0x5efe83]
    cpu.ah = app->getMemory<x86::reg8>(x86::reg32(6225539) /* 0x5efe83 */);
    // 0042fd78  80f580                 -xor ch, 0x80
    cpu.ch ^= x86::reg8(x86::sreg8(128 /*0x80*/));
    // 0042fd7b  80f480                 -xor ah, 0x80
    cpu.ah ^= x86::reg8(x86::sreg8(128 /*0x80*/));
    // 0042fd7e  882d7bfe5e00           -mov byte ptr [0x5efe7b], ch
    app->getMemory<x86::reg8>(x86::reg32(6225531) /* 0x5efe7b */) = cpu.ch;
    // 0042fd84  882583fe5e00           -mov byte ptr [0x5efe83], ah
    app->getMemory<x86::reg8>(x86::reg32(6225539) /* 0x5efe83 */) = cpu.ah;
    // 0042fd8a  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 0042fd8c  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042fd8d  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042fd8e  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042fd8f  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042fd90  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x0042fd91:
    // 0042fd91  bf78fe5e00             -mov edi, 0x5efe78
    cpu.edi = 6225528 /*0x5efe78*/;
    // 0042fd96  8db2d8000000           -lea esi, [edx + 0xd8]
    cpu.esi = x86::reg32(cpu.edx + x86::reg32(216) /* 0xd8 */);
    // 0042fd9c  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 0042fd9d  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 0042fd9e  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 0042fd9f  85db                   +test ebx, ebx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & cpu.ebx));
    // 0042fda1  741a                   -je 0x42fdbd
    if (cpu.flags.zf)
    {
        goto L_0x0042fdbd;
    }
    // 0042fda3  d905b8fe5e00           +fld dword ptr [0x5efeb8]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu81 = x86::Float(app->getMemory<float>(x86::reg32(6225592) /* 0x5efeb8 */));
    // 0042fda9  d9ee                   +fldz 
    x86::Float fpu82 = 0.0;
    // 0042fdab  ded9                   +fcompp 
    cpu.fpu.compare(fpu82, fpu81);
    // 0042fdad  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 0042fdaf  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 0042fdb0  7307                   -jae 0x42fdb9
    if (!cpu.flags.cf)
    {
        goto L_0x0042fdb9;
    }
    // 0042fdb2  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 0042fdb7  eb1c                   -jmp 0x42fdd5
    goto L_0x0042fdd5;
L_0x0042fdb9:
    // 0042fdb9  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
    // 0042fdbb  eb18                   -jmp 0x42fdd5
    goto L_0x0042fdd5;
L_0x0042fdbd:
    // 0042fdbd  d905b8fe5e00           +fld dword ptr [0x5efeb8]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu83 = x86::Float(app->getMemory<float>(x86::reg32(6225592) /* 0x5efeb8 */));
    // 0042fdc3  d9ee                   +fldz 
    x86::Float fpu84 = 0.0;
    // 0042fdc5  ded9                   +fcompp 
    cpu.fpu.compare(fpu84, fpu83);
    // 0042fdc7  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 0042fdc9  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 0042fdca  7607                   -jbe 0x42fdd3
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x0042fdd3;
    }
    // 0042fdcc  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 0042fdd1  eb02                   -jmp 0x42fdd5
    goto L_0x0042fdd5;
L_0x0042fdd3:
    // 0042fdd3  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
L_0x0042fdd5:
    // 0042fdd5  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0042fdd7  742d                   -je 0x42fe06
    if (cpu.flags.zf)
    {
        goto L_0x0042fe06;
    }
    // 0042fdd9  8a157bfe5e00           -mov dl, byte ptr [0x5efe7b]
    cpu.dl = app->getMemory<x86::reg8>(x86::reg32(6225531) /* 0x5efe7b */);
    // 0042fddf  80f280                 -xor dl, 0x80
    cpu.dl ^= x86::reg8(x86::sreg8(128 /*0x80*/));
    // 0042fde2  8a1d83fe5e00           -mov bl, byte ptr [0x5efe83]
    cpu.bl = app->getMemory<x86::reg8>(x86::reg32(6225539) /* 0x5efe83 */);
    // 0042fde8  88157bfe5e00           -mov byte ptr [0x5efe7b], dl
    app->getMemory<x86::reg8>(x86::reg32(6225531) /* 0x5efe7b */) = cpu.dl;
    // 0042fdee  8a357ffe5e00           -mov dh, byte ptr [0x5efe7f]
    cpu.dh = app->getMemory<x86::reg8>(x86::reg32(6225535) /* 0x5efe7f */);
    // 0042fdf4  80f380                 -xor bl, 0x80
    cpu.bl ^= x86::reg8(x86::sreg8(128 /*0x80*/));
    // 0042fdf7  80f680                 -xor dh, 0x80
    cpu.dh ^= x86::reg8(x86::sreg8(128 /*0x80*/));
    // 0042fdfa  881d83fe5e00           -mov byte ptr [0x5efe83], bl
    app->getMemory<x86::reg8>(x86::reg32(6225539) /* 0x5efe83 */) = cpu.bl;
    // 0042fe00  88357ffe5e00           -mov byte ptr [0x5efe7f], dh
    app->getMemory<x86::reg8>(x86::reg32(6225535) /* 0x5efe7f */) = cpu.dh;
L_0x0042fe06:
    // 0042fe06  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 0042fe08  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042fe09  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042fe0a  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042fe0b  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042fe0c  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x40 0x00 */
void Application::sub_42fe10(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0042fe10  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 0042fe11  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 0042fe12  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 0042fe13  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 0042fe14  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 0042fe16  83ec30                 -sub esp, 0x30
    (cpu.esp) -= x86::reg32(x86::sreg32(48 /*0x30*/));
    // 0042fe19  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 0042fe1b  89d6                   -mov esi, edx
    cpu.esi = cpu.edx;
    // 0042fe1d  8b4514                 -mov eax, dword ptr [ebp + 0x14]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(20) /* 0x14 */);
    // 0042fe20  8945dc                 -mov dword ptr [ebp - 0x24], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-36) /* -0x24 */) = cpu.eax;
    // 0042fe23  8b4518                 -mov eax, dword ptr [ebp + 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(24) /* 0x18 */);
    // 0042fe26  8945e0                 -mov dword ptr [ebp - 0x20], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-32) /* -0x20 */) = cpu.eax;
    // 0042fe29  8b451c                 -mov eax, dword ptr [ebp + 0x1c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(28) /* 0x1c */);
    // 0042fe2c  8945e4                 -mov dword ptr [ebp - 0x1c], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-28) /* -0x1c */) = cpu.eax;
    // 0042fe2f  8d45dc                 -lea eax, [ebp - 0x24]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-36) /* -0x24 */);
    // 0042fe32  e8b9740600             -call 0x4972f0
    cpu.esp -= 4;
    sub_4972f0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042fe37  d981b0000000           -fld dword ptr [ecx + 0xb0]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(176) /* 0xb0 */));
    // 0042fe3d  d882b0000000           -fadd dword ptr [edx + 0xb0]
    x86::Float fpu2 = cpu.fpu.add(fpu1, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(176) /* 0xb0 */)));
    // 0042fe43  d982b0000000           -fld dword ptr [edx + 0xb0]
    x86::Float fpu3 = x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(176) /* 0xb0 */));
    // 0042fe49  d9e8                   -fld1 
    x86::Float fpu4 = 1.0;
    // 0042fe4b  def2                   -fdivrp st(2)
    x86::Float fpu5 = cpu.fpu.div(fpu4, x86::Float(fpu2));
    // 0042fe4d  d8c9                   -fmul st(1)
    x86::Float fpu6 = cpu.fpu.mul(fpu3, x86::Float(fpu5));
    // 0042fe4f  d981b0000000           -fld dword ptr [ecx + 0xb0]
    x86::Float fpu7 = x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(176) /* 0xb0 */));
    // 0042fe55  deca                   -fmulp st(2)
    x86::Float fpu8 = cpu.fpu.mul(fpu5, fpu7);
    // 0042fe57  dd0504745300           -fld qword ptr [0x537404]
    x86::Float fpu9 = x86::Float(app->getMemory<double>(x86::reg32(5469188) /* 0x537404 */));
    // 0042fe5d  d9c9                   -fxch st(1)
    
    // 0042fe5f  d8c9                   -fmul st(1)
    x86::Float fpu10 = cpu.fpu.mul(fpu6, x86::Float(fpu9));
    // 0042fe61  8d45e8                 -lea eax, [ebp - 0x18]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-24) /* -0x18 */);
    // 0042fe64  d9ca                   -fxch st(2)
    
    // 0042fe66  dec9                   -fmulp st(1)
    x86::Float fpu11 = cpu.fpu.mul(fpu9, fpu8);
    // 0042fe68  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 0042fe69  d9ca                   -fxch st(2)
    
    // 0042fe6b  ddd8                   -fstp st(0)
    x86::Float fpu12 = cpu.fpu.st(0);
    x86::Float fpu13 = x86::Float(fpu12);
    // 0042fe6d  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 0042fe70  8d55dc                 -lea edx, [ebp - 0x24]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-36) /* -0x24 */);
    // 0042fe73  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 0042fe78  d9e0                   -fchs 
    x86::Float fpu14 = -fpu10;
    // 0042fe7a  d91c24                 -fstp dword ptr [esp]
    app->getMemory<float>(cpu.esp) = float(fpu14);
    // 0042fe7d  d95df4                 -fstp dword ptr [ebp - 0xc]
    app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */) = float(fpu11);
    cpu.fpu.count -= 1;
    }
    // 0042fe80  e8cb010b00             -call 0x4e0050
    cpu.esp -= 4;
    sub_4e0050(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042fe85  8d45d0                 -lea eax, [ebp - 0x30]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-48) /* -0x30 */);
    // 0042fe88  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 0042fe89  8d55dc                 -lea edx, [ebp - 0x24]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-36) /* -0x24 */);
    // 0042fe8c  ff75f4                 -push dword ptr [ebp - 0xc]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    cpu.esp -= 4;
    // 0042fe8f  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 0042fe94  8d5de8                 -lea ebx, [ebp - 0x18]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-24) /* -0x18 */);
    // 0042fe97  e8b4010b00             -call 0x4e0050
    cpu.esp -= 4;
    sub_4e0050(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042fe9c  8d9198000000           -lea edx, [ecx + 0x98]
    cpu.edx = x86::reg32(cpu.ecx + x86::reg32(152) /* 0x98 */);
    // 0042fea2  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 0042fea7  89d1                   -mov ecx, edx
    cpu.ecx = cpu.edx;
    // 0042fea9  e802010b00             -call 0x4dffb0
    cpu.esp -= 4;
    sub_4dffb0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042feae  8d5dd0                 -lea ebx, [ebp - 0x30]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-48) /* -0x30 */);
    // 0042feb1  8d9698000000           -lea edx, [esi + 0x98]
    cpu.edx = x86::reg32(cpu.esi + x86::reg32(152) /* 0x98 */);
    // 0042feb7  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 0042febc  89d1                   -mov ecx, edx
    cpu.ecx = cpu.edx;
    // 0042febe  e8ed000b00             -call 0x4dffb0
    cpu.esp -= 4;
    sub_4dffb0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042fec3  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 0042fec8  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 0042feca  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042fecb  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042fecc  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042fecd  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042fece  c20c00                 -ret 0xc
    cpu.esp += 4+12 /*0xc*/;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x8d 0x40 0x00 */
void Application::sub_42fee0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0042fee0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 0042fee1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 0042fee2  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 0042fee3  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 0042fee4  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 0042fee5  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 0042fee7  83ec1c                 -sub esp, 0x1c
    (cpu.esp) -= x86::reg32(x86::sreg32(28 /*0x1c*/));
    // 0042feea  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 0042feec  89d7                   -mov edi, edx
    cpu.edi = cpu.edx;
    // 0042feee  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 0042fef0  8d9ec0000000           -lea ebx, [esi + 0xc0]
    cpu.ebx = x86::reg32(cpu.esi + x86::reg32(192) /* 0xc0 */);
    // 0042fef6  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 0042fef8  05c0000000             -add eax, 0xc0
    (cpu.eax) += x86::reg32(x86::sreg32(192 /*0xc0*/));
    // 0042fefd  8955f4                 -mov dword ptr [ebp - 0xc], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.edx;
    // 0042ff00  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 0042ff03  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 0042ff05  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 0042ff07  e8e4020b00             -call 0x4e01f0
    cpu.esp -= 4;
    sub_4e01f0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042ff0c  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 0042ff0e  05cc000000             -add eax, 0xcc
    (cpu.eax) += x86::reg32(x86::sreg32(204 /*0xcc*/));
    // 0042ff13  d91dbcfe5e00           -fstp dword ptr [0x5efebc]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = cpu.fpu.st(0);
    app->getMemory<float>(x86::reg32(6225596) /* 0x5efebc */) = float(fpu1);
    // 0042ff19  8945f0                 -mov dword ptr [ebp - 0x10], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = cpu.eax;
    // 0042ff1c  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 0042ff1e  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 0042ff20  8d8fd8000000           -lea ecx, [edi + 0xd8]
    cpu.ecx = x86::reg32(cpu.edi + x86::reg32(216) /* 0xd8 */);
    cpu.fpu.count -= 1;
    }
    // 0042ff26  e8c5020b00             -call 0x4e01f0
    cpu.esp -= 4;
    sub_4e01f0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042ff2b  89ca                   -mov edx, ecx
    cpu.edx = cpu.ecx;
    // 0042ff2d  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 0042ff2f  d91dc0fe5e00           -fstp dword ptr [0x5efec0]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu2 = cpu.fpu.st(0);
    app->getMemory<float>(x86::reg32(6225600) /* 0x5efec0 */) = float(fpu2);
    cpu.fpu.count -= 1;
    }
    // 0042ff35  e8b6020b00             -call 0x4e01f0
    cpu.esp -= 4;
    sub_4e01f0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042ff3a  8d9ecc000000           -lea ebx, [esi + 0xcc]
    cpu.ebx = x86::reg32(cpu.esi + x86::reg32(204) /* 0xcc */);
    // 0042ff40  8b55fc                 -mov edx, dword ptr [ebp - 4]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 0042ff43  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 0042ff45  d91dc4fe5e00           -fstp dword ptr [0x5efec4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu3 = cpu.fpu.st(0);
    app->getMemory<float>(x86::reg32(6225604) /* 0x5efec4 */) = float(fpu3);
    cpu.fpu.count -= 1;
    }
    // 0042ff4b  e8a0020b00             -call 0x4e01f0
    cpu.esp -= 4;
    sub_4e01f0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042ff50  8b55f0                 -mov edx, dword ptr [ebp - 0x10]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 0042ff53  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 0042ff55  d91dc8fe5e00           -fstp dword ptr [0x5efec8]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu4 = cpu.fpu.st(0);
    app->getMemory<float>(x86::reg32(6225608) /* 0x5efec8 */) = float(fpu4);
    cpu.fpu.count -= 1;
    }
    // 0042ff5b  e890020b00             -call 0x4e01f0
    cpu.esp -= 4;
    sub_4e01f0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042ff60  89ca                   -mov edx, ecx
    cpu.edx = cpu.ecx;
    // 0042ff62  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 0042ff64  d91dccfe5e00           -fstp dword ptr [0x5efecc]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu5 = cpu.fpu.st(0);
    app->getMemory<float>(x86::reg32(6225612) /* 0x5efecc */) = float(fpu5);
    cpu.fpu.count -= 1;
    }
    // 0042ff6a  e881020b00             -call 0x4e01f0
    cpu.esp -= 4;
    sub_4e01f0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042ff6f  8d9ed8000000           -lea ebx, [esi + 0xd8]
    cpu.ebx = x86::reg32(cpu.esi + x86::reg32(216) /* 0xd8 */);
    // 0042ff75  8b55fc                 -mov edx, dword ptr [ebp - 4]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 0042ff78  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 0042ff7a  d91dd0fe5e00           -fstp dword ptr [0x5efed0]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu6 = cpu.fpu.st(0);
    app->getMemory<float>(x86::reg32(6225616) /* 0x5efed0 */) = float(fpu6);
    cpu.fpu.count -= 1;
    }
    // 0042ff80  e86b020b00             -call 0x4e01f0
    cpu.esp -= 4;
    sub_4e01f0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042ff85  8b55f0                 -mov edx, dword ptr [ebp - 0x10]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 0042ff88  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 0042ff8a  d91dd4fe5e00           -fstp dword ptr [0x5efed4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu7 = cpu.fpu.st(0);
    app->getMemory<float>(x86::reg32(6225620) /* 0x5efed4 */) = float(fpu7);
    cpu.fpu.count -= 1;
    }
    // 0042ff90  e85b020b00             -call 0x4e01f0
    cpu.esp -= 4;
    sub_4e01f0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042ff95  89ca                   -mov edx, ecx
    cpu.edx = cpu.ecx;
    // 0042ff97  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 0042ff99  d91dd8fe5e00           -fstp dword ptr [0x5efed8]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu8 = cpu.fpu.st(0);
    app->getMemory<float>(x86::reg32(6225624) /* 0x5efed8 */) = float(fpu8);
    cpu.fpu.count -= 1;
    }
    // 0042ff9f  e84c020b00             -call 0x4e01f0
    cpu.esp -= 4;
    sub_4e01f0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042ffa4  d91ddcfe5e00           -fstp dword ptr [0x5efedc]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu9 = cpu.fpu.st(0);
    app->getMemory<float>(x86::reg32(6225628) /* 0x5efedc */) = float(fpu9);
    // 0042ffaa  d905bcfe5e00           -fld dword ptr [0x5efebc]
    x86::Float fpu10 = x86::Float(app->getMemory<float>(x86::reg32(6225596) /* 0x5efebc */));
    // 0042ffb0  d88f14010000           -fmul dword ptr [edi + 0x114]
    x86::Float fpu11 = cpu.fpu.mul(fpu10, x86::Float(app->getMemory<float>(cpu.edi + x86::reg32(276) /* 0x114 */)));
    // 0042ffb6  d905c0fe5e00           -fld dword ptr [0x5efec0]
    x86::Float fpu12 = x86::Float(app->getMemory<float>(x86::reg32(6225600) /* 0x5efec0 */));
    // 0042ffbc  d88f18010000           -fmul dword ptr [edi + 0x118]
    x86::Float fpu13 = cpu.fpu.mul(fpu12, x86::Float(app->getMemory<float>(cpu.edi + x86::reg32(280) /* 0x118 */)));
    // 0042ffc2  d905c4fe5e00           -fld dword ptr [0x5efec4]
    x86::Float fpu14 = x86::Float(app->getMemory<float>(x86::reg32(6225604) /* 0x5efec4 */));
    // 0042ffc8  d88f1c010000           -fmul dword ptr [edi + 0x11c]
    x86::Float fpu15 = cpu.fpu.mul(fpu14, x86::Float(app->getMemory<float>(cpu.edi + x86::reg32(284) /* 0x11c */)));
    // 0042ffce  d905c8fe5e00           -fld dword ptr [0x5efec8]
    x86::Float fpu16 = x86::Float(app->getMemory<float>(x86::reg32(6225608) /* 0x5efec8 */));
    // 0042ffd4  d88f14010000           -fmul dword ptr [edi + 0x114]
    x86::Float fpu17 = cpu.fpu.mul(fpu16, x86::Float(app->getMemory<float>(cpu.edi + x86::reg32(276) /* 0x114 */)));
    // 0042ffda  d905ccfe5e00           -fld dword ptr [0x5efecc]
    x86::Float fpu18 = x86::Float(app->getMemory<float>(x86::reg32(6225612) /* 0x5efecc */));
    // 0042ffe0  d88f18010000           -fmul dword ptr [edi + 0x118]
    x86::Float fpu19 = cpu.fpu.mul(fpu18, x86::Float(app->getMemory<float>(cpu.edi + x86::reg32(280) /* 0x118 */)));
    // 0042ffe6  d905d0fe5e00           -fld dword ptr [0x5efed0]
    x86::Float fpu20 = x86::Float(app->getMemory<float>(x86::reg32(6225616) /* 0x5efed0 */));
    // 0042ffec  d88f1c010000           -fmul dword ptr [edi + 0x11c]
    x86::Float fpu21 = cpu.fpu.mul(fpu20, x86::Float(app->getMemory<float>(cpu.edi + x86::reg32(284) /* 0x11c */)));
    // 0042fff2  d905d4fe5e00           -fld dword ptr [0x5efed4]
    x86::Float fpu22 = x86::Float(app->getMemory<float>(x86::reg32(6225620) /* 0x5efed4 */));
    // 0042fff8  d88f14010000           -fmul dword ptr [edi + 0x114]
    x86::Float fpu23 = cpu.fpu.mul(fpu22, x86::Float(app->getMemory<float>(cpu.edi + x86::reg32(276) /* 0x114 */)));
    // 0042fffe  d9cd                   -fxch st(5)
    
    // 00430000  d91de4fe5e00           -fstp dword ptr [0x5efee4]
    app->getMemory<float>(x86::reg32(6225636) /* 0x5efee4 */) = float(fpu13);
    // 00430006  d905d8fe5e00           -fld dword ptr [0x5efed8]
    x86::Float fpu24 = x86::Float(app->getMemory<float>(x86::reg32(6225624) /* 0x5efed8 */));
    // 0043000c  d88f18010000           -fmul dword ptr [edi + 0x118]
    x86::Float fpu25 = cpu.fpu.mul(fpu24, x86::Float(app->getMemory<float>(cpu.edi + x86::reg32(280) /* 0x118 */)));
    // 00430012  d9cc                   -fxch st(4)
    
    // 00430014  d91de8fe5e00           -fstp dword ptr [0x5efee8]
    app->getMemory<float>(x86::reg32(6225640) /* 0x5efee8 */) = float(fpu15);
    // 0043001a  d905dcfe5e00           -fld dword ptr [0x5efedc]
    x86::Float fpu26 = x86::Float(app->getMemory<float>(x86::reg32(6225628) /* 0x5efedc */));
    // 00430020  d88f1c010000           -fmul dword ptr [edi + 0x11c]
    x86::Float fpu27 = cpu.fpu.mul(fpu26, x86::Float(app->getMemory<float>(cpu.edi + x86::reg32(284) /* 0x11c */)));
    // 00430026  d9cb                   -fxch st(3)
    
    // 00430028  d91decfe5e00           -fstp dword ptr [0x5efeec]
    app->getMemory<float>(x86::reg32(6225644) /* 0x5efeec */) = float(fpu17);
    // 0043002e  d905bcfe5e00           -fld dword ptr [0x5efebc]
    x86::Float fpu28 = x86::Float(app->getMemory<float>(x86::reg32(6225596) /* 0x5efebc */));
    // 00430034  d88e14010000           -fmul dword ptr [esi + 0x114]
    x86::Float fpu29 = cpu.fpu.mul(fpu28, x86::Float(app->getMemory<float>(cpu.esi + x86::reg32(276) /* 0x114 */)));
    // 0043003a  d9ca                   -fxch st(2)
    
    // 0043003c  d91df0fe5e00           -fstp dword ptr [0x5efef0]
    app->getMemory<float>(x86::reg32(6225648) /* 0x5efef0 */) = float(fpu19);
    // 00430042  d905c0fe5e00           -fld dword ptr [0x5efec0]
    x86::Float fpu30 = x86::Float(app->getMemory<float>(x86::reg32(6225600) /* 0x5efec0 */));
    // 00430048  d88e14010000           -fmul dword ptr [esi + 0x114]
    x86::Float fpu31 = cpu.fpu.mul(fpu30, x86::Float(app->getMemory<float>(cpu.esi + x86::reg32(276) /* 0x114 */)));
    // 0043004e  d9c9                   -fxch st(1)
    
    // 00430050  d91df4fe5e00           -fstp dword ptr [0x5efef4]
    app->getMemory<float>(x86::reg32(6225652) /* 0x5efef4 */) = float(fpu21);
    // 00430056  d905c4fe5e00           -fld dword ptr [0x5efec4]
    x86::Float fpu32 = x86::Float(app->getMemory<float>(x86::reg32(6225604) /* 0x5efec4 */));
    // 0043005c  d88e14010000           -fmul dword ptr [esi + 0x114]
    x86::Float fpu33 = cpu.fpu.mul(fpu32, x86::Float(app->getMemory<float>(cpu.esi + x86::reg32(276) /* 0x114 */)));
    // 00430062  d9cd                   -fxch st(5)
    
    // 00430064  d91df8fe5e00           -fstp dword ptr [0x5efef8]
    app->getMemory<float>(x86::reg32(6225656) /* 0x5efef8 */) = float(fpu23);
    // 0043006a  d905c8fe5e00           -fld dword ptr [0x5efec8]
    x86::Float fpu34 = x86::Float(app->getMemory<float>(x86::reg32(6225608) /* 0x5efec8 */));
    // 00430070  d88e18010000           -fmul dword ptr [esi + 0x118]
    x86::Float fpu35 = cpu.fpu.mul(fpu34, x86::Float(app->getMemory<float>(cpu.esi + x86::reg32(280) /* 0x118 */)));
    // 00430076  d9cc                   -fxch st(4)
    
    // 00430078  d91dfcfe5e00           -fstp dword ptr [0x5efefc]
    app->getMemory<float>(x86::reg32(6225660) /* 0x5efefc */) = float(fpu25);
    // 0043007e  d905ccfe5e00           -fld dword ptr [0x5efecc]
    x86::Float fpu36 = x86::Float(app->getMemory<float>(x86::reg32(6225612) /* 0x5efecc */));
    // 00430084  d88e18010000           -fmul dword ptr [esi + 0x118]
    x86::Float fpu37 = cpu.fpu.mul(fpu36, x86::Float(app->getMemory<float>(cpu.esi + x86::reg32(280) /* 0x118 */)));
    // 0043008a  d9cb                   -fxch st(3)
    
    // 0043008c  d91d00ff5e00           -fstp dword ptr [0x5eff00]
    app->getMemory<float>(x86::reg32(6225664) /* 0x5eff00 */) = float(fpu27);
    // 00430092  d905d0fe5e00           -fld dword ptr [0x5efed0]
    x86::Float fpu38 = x86::Float(app->getMemory<float>(x86::reg32(6225616) /* 0x5efed0 */));
    // 00430098  d88e18010000           -fmul dword ptr [esi + 0x118]
    x86::Float fpu39 = cpu.fpu.mul(fpu38, x86::Float(app->getMemory<float>(cpu.esi + x86::reg32(280) /* 0x118 */)));
    // 0043009e  d9ca                   -fxch st(2)
    
    // 004300a0  d91d90fe5e00           -fstp dword ptr [0x5efe90]
    app->getMemory<float>(x86::reg32(6225552) /* 0x5efe90 */) = float(fpu29);
    // 004300a6  d905d4fe5e00           -fld dword ptr [0x5efed4]
    x86::Float fpu40 = x86::Float(app->getMemory<float>(x86::reg32(6225620) /* 0x5efed4 */));
    // 004300ac  d88e1c010000           -fmul dword ptr [esi + 0x11c]
    x86::Float fpu41 = cpu.fpu.mul(fpu40, x86::Float(app->getMemory<float>(cpu.esi + x86::reg32(284) /* 0x11c */)));
    // 004300b2  d9c9                   -fxch st(1)
    
    // 004300b4  d91d94fe5e00           -fstp dword ptr [0x5efe94]
    app->getMemory<float>(x86::reg32(6225556) /* 0x5efe94 */) = float(fpu31);
    // 004300ba  d905d8fe5e00           -fld dword ptr [0x5efed8]
    x86::Float fpu42 = x86::Float(app->getMemory<float>(x86::reg32(6225624) /* 0x5efed8 */));
    // 004300c0  d88e1c010000           -fmul dword ptr [esi + 0x11c]
    x86::Float fpu43 = cpu.fpu.mul(fpu42, x86::Float(app->getMemory<float>(cpu.esi + x86::reg32(284) /* 0x11c */)));
    // 004300c6  31c9                   +xor ecx, ecx
    cpu.clear_co();
    cpu.set_szp((cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx))));
    // 004300c8  d9cd                   +fxch st(5)
    
    // 004300ca  d91d98fe5e00           +fstp dword ptr [0x5efe98]
    app->getMemory<float>(x86::reg32(6225560) /* 0x5efe98 */) = float(fpu33);
    // 004300d0  d905dcfe5e00           +fld dword ptr [0x5efedc]
    x86::Float fpu44 = x86::Float(app->getMemory<float>(x86::reg32(6225628) /* 0x5efedc */));
    // 004300d6  d88e1c010000           +fmul dword ptr [esi + 0x11c]
    x86::Float fpu45 = cpu.fpu.mul(fpu44, x86::Float(app->getMemory<float>(cpu.esi + x86::reg32(284) /* 0x11c */)));
    // 004300dc  894df8                 -mov dword ptr [ebp - 8], ecx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.ecx;
    // 004300df  d9cc                   +fxch st(4)
    
    // 004300e1  d91d9cfe5e00           +fstp dword ptr [0x5efe9c]
    app->getMemory<float>(x86::reg32(6225564) /* 0x5efe9c */) = float(fpu35);
    // 004300e7  d9ca                   +fxch st(2)
    
    // 004300e9  d91da0fe5e00           +fstp dword ptr [0x5efea0]
    app->getMemory<float>(x86::reg32(6225568) /* 0x5efea0 */) = float(fpu37);
    // 004300ef  d91da4fe5e00           +fstp dword ptr [0x5efea4]
    app->getMemory<float>(x86::reg32(6225572) /* 0x5efea4 */) = float(fpu39);
    // 004300f5  d91da8fe5e00           +fstp dword ptr [0x5efea8]
    app->getMemory<float>(x86::reg32(6225576) /* 0x5efea8 */) = float(fpu41);
    // 004300fb  d9c9                   +fxch st(1)
    
    // 004300fd  d91dacfe5e00           +fstp dword ptr [0x5efeac]
    app->getMemory<float>(x86::reg32(6225580) /* 0x5efeac */) = float(fpu43);
    // 00430103  d91db0fe5e00           +fstp dword ptr [0x5efeb0]
    app->getMemory<float>(x86::reg32(6225584) /* 0x5efeb0 */) = float(fpu45);
    // 00430109  d91de0fe5e00           +fstp dword ptr [0x5efee0]
    app->getMemory<float>(x86::reg32(6225632) /* 0x5efee0 */) = float(fpu11);
    cpu.fpu.count -= 1;
    }
    // 0043010f  eb49                   -jmp 0x43015a
    goto L_0x0043015a;
L_0x00430111:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00430111  83f803                 +cmp eax, 3
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(3 /*0x3*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00430114  7508                   -jne 0x43011e
    if (!cpu.flags.zf)
    {
        goto L_0x0043011e;
    }
    // 00430116  89fa                   -mov edx, edi
    cpu.edx = cpu.edi;
    // 00430118  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 0043011a  31db                   +xor ebx, ebx
    cpu.clear_co();
    cpu.set_szp((cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx))));
    // 0043011c  eb0e                   -jmp 0x43012c
    goto L_0x0043012c;
L_0x0043011e:
    // 0043011e  83f804                 +cmp eax, 4
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
    // 00430121  750e                   -jne 0x430131
    if (!cpu.flags.zf)
    {
        goto L_0x00430131;
    }
    // 00430123  bb01000000             -mov ebx, 1
    cpu.ebx = 1 /*0x1*/;
    // 00430128  89fa                   -mov edx, edi
    cpu.edx = cpu.edi;
    // 0043012a  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
L_0x0043012c:
    // 0043012c  e88ff7ffff             -call 0x42f8c0
    cpu.esp -= 4;
    sub_42f8c0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00430131:
    // 00430131  8b45ec                 -mov eax, dword ptr [ebp - 0x14]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */);
    // 00430134  8b55e8                 -mov edx, dword ptr [ebp - 0x18]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-24) /* -0x18 */);
    // 00430137  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00430138  8b4de4                 -mov ecx, dword ptr [ebp - 0x1c]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-28) /* -0x1c */);
    // 0043013b  8b5df8                 -mov ebx, dword ptr [ebp - 8]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 0043013e  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 0043013f  43                     -inc ebx
    (cpu.ebx)++;
    // 00430140  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 00430142  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00430143  89fa                   -mov edx, edi
    cpu.edx = cpu.edi;
    // 00430145  895df8                 -mov dword ptr [ebp - 8], ebx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.ebx;
    // 00430148  e8c3fcffff             -call 0x42fe10
    cpu.esp -= 4;
    sub_42fe10(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0043014d  8945f4                 -mov dword ptr [ebp - 0xc], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.eax;
    // 00430150  837df804               +cmp dword ptr [ebp - 8], 4
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(4 /*0x4*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00430154  0f8da2000000           -jge 0x4301fc
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004301fc;
    }
L_0x0043015a:
    // 0043015a  8d4de4                 -lea ecx, [ebp - 0x1c]
    cpu.ecx = x86::reg32(cpu.ebp + x86::reg32(-28) /* -0x1c */);
    // 0043015d  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 00430162  8d9e98000000           -lea ebx, [esi + 0x98]
    cpu.ebx = x86::reg32(cpu.esi + x86::reg32(152) /* 0x98 */);
    // 00430168  8d9798000000           -lea edx, [edi + 0x98]
    cpu.edx = x86::reg32(cpu.edi + x86::reg32(152) /* 0x98 */);
    // 0043016e  e88dfe0a00             -call 0x4e0000
    cpu.esp -= 4;
    sub_4e0000(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00430173  8d55e4                 -lea edx, [ebp - 0x1c]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-28) /* -0x1c */);
    // 00430176  8d86c0000000           -lea eax, [esi + 0xc0]
    cpu.eax = x86::reg32(cpu.esi + x86::reg32(192) /* 0xc0 */);
    // 0043017c  e86f000b00             -call 0x4e01f0
    cpu.esp -= 4;
    sub_4e01f0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00430181  8d55e4                 -lea edx, [ebp - 0x1c]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-28) /* -0x1c */);
    // 00430184  8d86cc000000           -lea eax, [esi + 0xcc]
    cpu.eax = x86::reg32(cpu.esi + x86::reg32(204) /* 0xcc */);
    // 0043018a  d91d60fe5e00           -fstp dword ptr [0x5efe60]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu46 = cpu.fpu.st(0);
    app->getMemory<float>(x86::reg32(6225504) /* 0x5efe60 */) = float(fpu46);
    cpu.fpu.count -= 1;
    }
    // 00430190  e85b000b00             -call 0x4e01f0
    cpu.esp -= 4;
    sub_4e01f0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00430195  8d55e4                 -lea edx, [ebp - 0x1c]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-28) /* -0x1c */);
    // 00430198  8d86d8000000           -lea eax, [esi + 0xd8]
    cpu.eax = x86::reg32(cpu.esi + x86::reg32(216) /* 0xd8 */);
    // 0043019e  d91d64fe5e00           -fstp dword ptr [0x5efe64]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu47 = cpu.fpu.st(0);
    app->getMemory<float>(x86::reg32(6225508) /* 0x5efe64 */) = float(fpu47);
    cpu.fpu.count -= 1;
    }
    // 004301a4  e847000b00             -call 0x4e01f0
    cpu.esp -= 4;
    sub_4e01f0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004301a9  8d55e4                 -lea edx, [ebp - 0x1c]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-28) /* -0x1c */);
    // 004301ac  8d87c0000000           -lea eax, [edi + 0xc0]
    cpu.eax = x86::reg32(cpu.edi + x86::reg32(192) /* 0xc0 */);
    // 004301b2  d91d68fe5e00           -fstp dword ptr [0x5efe68]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu48 = cpu.fpu.st(0);
    app->getMemory<float>(x86::reg32(6225512) /* 0x5efe68 */) = float(fpu48);
    cpu.fpu.count -= 1;
    }
    // 004301b8  e833000b00             -call 0x4e01f0
    cpu.esp -= 4;
    sub_4e01f0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004301bd  8d55e4                 -lea edx, [ebp - 0x1c]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-28) /* -0x1c */);
    // 004301c0  8d87cc000000           -lea eax, [edi + 0xcc]
    cpu.eax = x86::reg32(cpu.edi + x86::reg32(204) /* 0xcc */);
    // 004301c6  d91d6cfe5e00           -fstp dword ptr [0x5efe6c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu49 = cpu.fpu.st(0);
    app->getMemory<float>(x86::reg32(6225516) /* 0x5efe6c */) = float(fpu49);
    cpu.fpu.count -= 1;
    }
    // 004301cc  e81f000b00             -call 0x4e01f0
    cpu.esp -= 4;
    sub_4e01f0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004301d1  8d55e4                 -lea edx, [ebp - 0x1c]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-28) /* -0x1c */);
    // 004301d4  8d87d8000000           -lea eax, [edi + 0xd8]
    cpu.eax = x86::reg32(cpu.edi + x86::reg32(216) /* 0xd8 */);
    // 004301da  d91d70fe5e00           -fstp dword ptr [0x5efe70]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu50 = cpu.fpu.st(0);
    app->getMemory<float>(x86::reg32(6225520) /* 0x5efe70 */) = float(fpu50);
    cpu.fpu.count -= 1;
    }
    // 004301e0  e80b000b00             -call 0x4e01f0
    cpu.esp -= 4;
    sub_4e01f0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004301e5  89fa                   -mov edx, edi
    cpu.edx = cpu.edi;
    // 004301e7  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004301e9  d91d74fe5e00           -fstp dword ptr [0x5efe74]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu51 = cpu.fpu.st(0);
    app->getMemory<float>(x86::reg32(6225524) /* 0x5efe74 */) = float(fpu51);
    cpu.fpu.count -= 1;
    }
    // 004301ef  e85cf3ffff             -call 0x42f550
    cpu.esp -= 4;
    sub_42f550(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004301f4  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004301f6  0f8515ffffff           -jne 0x430111
    if (!cpu.flags.zf)
    {
        goto L_0x00430111;
    }
L_0x004301fc:
    // 004301fc  8b45f4                 -mov eax, dword ptr [ebp - 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 004301ff  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00430201  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00430202  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00430203  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00430204  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00430205  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00430206  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 */
void Application::sub_430210(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00430210  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00430211  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00430212  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00430213  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00430214  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00430216  83ec28                 -sub esp, 0x28
    (cpu.esp) -= x86::reg32(x86::sreg32(40 /*0x28*/));
    // 00430219  89d1                   -mov ecx, edx
    cpu.ecx = cpu.edx;
    // 0043021b  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 0043021d  8955d8                 -mov dword ptr [ebp - 0x28], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-40) /* -0x28 */) = cpu.edx;
    // 00430220  8955f4                 -mov dword ptr [ebp - 0xc], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.edx;
    // 00430223  8955e0                 -mov dword ptr [ebp - 0x20], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-32) /* -0x20 */) = cpu.edx;
    // 00430226  c745dc00000100         -mov dword ptr [ebp - 0x24], 0x10000
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-36) /* -0x24 */) = 65536 /*0x10000*/;
    // 0043022d  83f801                 +cmp eax, 1
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1 /*0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00430230  7513                   -jne 0x430245
    if (!cpu.flags.zf)
    {
        goto L_0x00430245;
    }
    // 00430232  8b7338                 -mov esi, dword ptr [ebx + 0x38]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(56) /* 0x38 */);
    // 00430235  8b4344                 -mov eax, dword ptr [ebx + 0x44]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(68) /* 0x44 */);
    // 00430238  29f0                   +sub eax, esi
    {
        x86::reg32& tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.esi));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 0043023a  8945f8                 -mov dword ptr [ebp - 8], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.eax;
    // 0043023d  8b433c                 -mov eax, dword ptr [ebx + 0x3c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(60) /* 0x3c */);
    // 00430240  8b7b30                 -mov edi, dword ptr [ebx + 0x30]
    cpu.edi = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(48) /* 0x30 */);
    // 00430243  eb4a                   -jmp 0x43028f
    goto L_0x0043028f;
L_0x00430245:
    // 00430245  83f802                 +cmp eax, 2
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
    // 00430248  7515                   -jne 0x43025f
    if (!cpu.flags.zf)
    {
        goto L_0x0043025f;
    }
    // 0043024a  8b5350                 -mov edx, dword ptr [ebx + 0x50]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(80) /* 0x50 */);
    // 0043024d  8b432c                 -mov eax, dword ptr [ebx + 0x2c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(44) /* 0x2c */);
    // 00430250  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 00430252  8945f8                 -mov dword ptr [ebp - 8], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.eax;
    // 00430255  8b4324                 -mov eax, dword ptr [ebx + 0x24]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(36) /* 0x24 */);
    // 00430258  8b7348                 -mov esi, dword ptr [ebx + 0x48]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(72) /* 0x48 */);
    // 0043025b  29f0                   +sub eax, esi
    {
        x86::reg32& tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.esi));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 0043025d  eb32                   -jmp 0x430291
    goto L_0x00430291;
L_0x0043025f:
    // 0043025f  83f804                 +cmp eax, 4
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
    // 00430262  7515                   -jne 0x430279
    if (!cpu.flags.zf)
    {
        goto L_0x00430279;
    }
    // 00430264  8b7b2c                 -mov edi, dword ptr [ebx + 0x2c]
    cpu.edi = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(44) /* 0x2c */);
    // 00430267  8b4338                 -mov eax, dword ptr [ebx + 0x38]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(56) /* 0x38 */);
    // 0043026a  29f8                   -sub eax, edi
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edi));
    // 0043026c  8945f8                 -mov dword ptr [ebp - 8], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.eax;
    // 0043026f  8b4330                 -mov eax, dword ptr [ebx + 0x30]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(48) /* 0x30 */);
    // 00430272  8b5324                 -mov edx, dword ptr [ebx + 0x24]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(36) /* 0x24 */);
    // 00430275  29d0                   +sub eax, edx
    {
        x86::reg32& tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.edx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 00430277  eb18                   -jmp 0x430291
    goto L_0x00430291;
L_0x00430279:
    // 00430279  83f808                 +cmp eax, 8
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
    // 0043027c  7516                   -jne 0x430294
    if (!cpu.flags.zf)
    {
        goto L_0x00430294;
    }
    // 0043027e  8b7344                 -mov esi, dword ptr [ebx + 0x44]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(68) /* 0x44 */);
    // 00430281  8b4350                 -mov eax, dword ptr [ebx + 0x50]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(80) /* 0x50 */);
    // 00430284  29f0                   -sub eax, esi
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.esi));
    // 00430286  8945f8                 -mov dword ptr [ebp - 8], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.eax;
    // 00430289  8b4348                 -mov eax, dword ptr [ebx + 0x48]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(72) /* 0x48 */);
    // 0043028c  8b7b3c                 -mov edi, dword ptr [ebx + 0x3c]
    cpu.edi = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(60) /* 0x3c */);
L_0x0043028f:
    // 0043028f  29f8                   -sub eax, edi
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edi));
L_0x00430291:
    // 00430291  8945f0                 -mov dword ptr [ebp - 0x10], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = cpu.eax;
L_0x00430294:
    // 00430294  8d45f0                 -lea eax, [ebp - 0x10]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 00430297  8b55e0                 -mov edx, dword ptr [ebp - 0x20]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-32) /* -0x20 */);
    // 0043029a  e8216e0600             -call 0x4970c0
    cpu.esp -= 4;
    sub_4970c0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0043029f  8b45f4                 -mov eax, dword ptr [ebp - 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 004302a2  f7ea                   -imul edx
    cpu.edx_eax = x86::reg64(x86::sreg64(static_cast<x86::sreg32>(cpu.eax)) * x86::sreg64(x86::sreg32(cpu.edx)));
    // 004302a4  c1e210                 -shl edx, 0x10
    cpu.edx <<= 16 /*0x10*/ % 32;
    // 004302a7  c1e810                 +shr eax, 0x10
    {
        x86::reg8 tmp = 16 /*0x10*/ % 32;
        x86::reg32& op = cpu.eax;
        if (tmp)
        {
            cpu.flags.cf = 1 & (op >> (tmp - 1));
            if (tmp == 1) cpu.flags.of = (1 & (op >> (32 - 1)));
            cpu.set_szp((op >>= tmp));
        }
    }
    // 004302aa  11d0                   -adc eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx) + cpu.flags.cf);
    // 004302ac  8b55dc                 -mov edx, dword ptr [ebp - 0x24]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-36) /* -0x24 */);
    // 004302af  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 004302b1  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004302b4  f7ea                   -imul edx
    cpu.edx_eax = x86::reg64(x86::sreg64(static_cast<x86::sreg32>(cpu.eax)) * x86::sreg64(x86::sreg32(cpu.edx)));
    // 004302b6  c1e210                 -shl edx, 0x10
    cpu.edx <<= 16 /*0x10*/ % 32;
    // 004302b9  c1e810                 +shr eax, 0x10
    {
        x86::reg8 tmp = 16 /*0x10*/ % 32;
        x86::reg32& op = cpu.eax;
        if (tmp)
        {
            cpu.flags.cf = 1 & (op >> (tmp - 1));
            if (tmp == 1) cpu.flags.of = (1 & (op >> (32 - 1)));
            cpu.set_szp((op >>= tmp));
        }
    }
    // 004302bc  11d0                   -adc eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx) + cpu.flags.cf);
    // 004302be  8b55d8                 -mov edx, dword ptr [ebp - 0x28]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-40) /* -0x28 */);
    // 004302c1  29c3                   -sub ebx, eax
    (cpu.ebx) -= x86::reg32(x86::sreg32(cpu.eax));
    // 004302c3  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004302c6  895de4                 -mov dword ptr [ebp - 0x1c], ebx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-28) /* -0x1c */) = cpu.ebx;
    // 004302c9  f7ea                   -imul edx
    cpu.edx_eax = x86::reg64(x86::sreg64(static_cast<x86::sreg32>(cpu.eax)) * x86::sreg64(x86::sreg32(cpu.edx)));
    // 004302cb  c1e210                 -shl edx, 0x10
    cpu.edx <<= 16 /*0x10*/ % 32;
    // 004302ce  c1e810                 +shr eax, 0x10
    {
        x86::reg8 tmp = 16 /*0x10*/ % 32;
        x86::reg32& op = cpu.eax;
        if (tmp)
        {
            cpu.flags.cf = 1 & (op >> (tmp - 1));
            if (tmp == 1) cpu.flags.of = (1 & (op >> (32 - 1)));
            cpu.set_szp((op >>= tmp));
        }
    }
    // 004302d1  11d0                   -adc eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx) + cpu.flags.cf);
    // 004302d3  8b55e0                 -mov edx, dword ptr [ebp - 0x20]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-32) /* -0x20 */);
    // 004302d6  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 004302d8  8b45f0                 -mov eax, dword ptr [ebp - 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 004302db  f7ea                   -imul edx
    cpu.edx_eax = x86::reg64(x86::sreg64(static_cast<x86::sreg32>(cpu.eax)) * x86::sreg64(x86::sreg32(cpu.edx)));
    // 004302dd  c1e210                 -shl edx, 0x10
    cpu.edx <<= 16 /*0x10*/ % 32;
    // 004302e0  c1e810                 +shr eax, 0x10
    {
        x86::reg8 tmp = 16 /*0x10*/ % 32;
        x86::reg32& op = cpu.eax;
        if (tmp)
        {
            cpu.flags.cf = 1 & (op >> (tmp - 1));
            if (tmp == 1) cpu.flags.of = (1 & (op >> (32 - 1)));
            cpu.set_szp((op >>= tmp));
        }
    }
    // 004302e3  11d0                   -adc eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx) + cpu.flags.cf);
    // 004302e5  8b55dc                 -mov edx, dword ptr [ebp - 0x24]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-36) /* -0x24 */);
    // 004302e8  29c3                   -sub ebx, eax
    (cpu.ebx) -= x86::reg32(x86::sreg32(cpu.eax));
    // 004302ea  8b45f0                 -mov eax, dword ptr [ebp - 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 004302ed  895de8                 -mov dword ptr [ebp - 0x18], ebx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-24) /* -0x18 */) = cpu.ebx;
    // 004302f0  f7ea                   -imul edx
    cpu.edx_eax = x86::reg64(x86::sreg64(static_cast<x86::sreg32>(cpu.eax)) * x86::sreg64(x86::sreg32(cpu.edx)));
    // 004302f2  c1e210                 -shl edx, 0x10
    cpu.edx <<= 16 /*0x10*/ % 32;
    // 004302f5  c1e810                 +shr eax, 0x10
    {
        x86::reg8 tmp = 16 /*0x10*/ % 32;
        x86::reg32& op = cpu.eax;
        if (tmp)
        {
            cpu.flags.cf = 1 & (op >> (tmp - 1));
            if (tmp == 1) cpu.flags.of = (1 & (op >> (32 - 1)));
            cpu.set_szp((op >>= tmp));
        }
    }
    // 004302f8  11d0                   -adc eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx) + cpu.flags.cf);
    // 004302fa  8b55d8                 -mov edx, dword ptr [ebp - 0x28]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-40) /* -0x28 */);
    // 004302fd  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 004302ff  8b45f4                 -mov eax, dword ptr [ebp - 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 00430302  f7ea                   -imul edx
    cpu.edx_eax = x86::reg64(x86::sreg64(static_cast<x86::sreg32>(cpu.eax)) * x86::sreg64(x86::sreg32(cpu.edx)));
    // 00430304  c1e210                 -shl edx, 0x10
    cpu.edx <<= 16 /*0x10*/ % 32;
    // 00430307  c1e810                 +shr eax, 0x10
    {
        x86::reg8 tmp = 16 /*0x10*/ % 32;
        x86::reg32& op = cpu.eax;
        if (tmp)
        {
            cpu.flags.cf = 1 & (op >> (tmp - 1));
            if (tmp == 1) cpu.flags.of = (1 & (op >> (32 - 1)));
            cpu.set_szp((op >>= tmp));
        }
    }
    // 0043030a  11d0                   -adc eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx) + cpu.flags.cf);
    // 0043030c  29c3                   -sub ebx, eax
    (cpu.ebx) -= x86::reg32(x86::sreg32(cpu.eax));
    // 0043030e  895dfc                 -mov dword ptr [ebp - 4], ebx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.ebx;
    // 00430311  8b45e4                 -mov eax, dword ptr [ebp - 0x1c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-28) /* -0x1c */);
    // 00430314  dd050c745300           -fld qword ptr [0x53740c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<double>(x86::reg32(5469196) /* 0x53740c */));
    // 0043031a  db45fc                 -fild dword ptr [ebp - 4]
    x86::Float fpu2 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 0043031d  d8c9                   -fmul st(1)
    x86::Float fpu3 = cpu.fpu.mul(fpu2, x86::Float(fpu1));
    // 0043031f  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 00430322  8b45e8                 -mov eax, dword ptr [ebp - 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-24) /* -0x18 */);
    // 00430325  db45fc                 -fild dword ptr [ebp - 4]
    x86::Float fpu4 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 00430328  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 0043032b  d8ca                   -fmul st(2)
    x86::Float fpu5 = cpu.fpu.mul(fpu4, x86::Float(fpu1));
    // 0043032d  db45fc                 -fild dword ptr [ebp - 4]
    x86::Float fpu6 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 00430330  decb                   -fmulp st(3)
    x86::Float fpu7 = cpu.fpu.mul(fpu1, fpu6);
    // 00430332  895dec                 -mov dword ptr [ebp - 0x14], ebx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */) = cpu.ebx;
    // 00430335  d9c9                   -fxch st(1)
    
    // 00430337  d95908                 -fstp dword ptr [ecx + 8]
    app->getMemory<float>(cpu.ecx + x86::reg32(8) /* 0x8 */) = float(fpu3);
    // 0043033a  d919                   -fstp dword ptr [ecx]
    app->getMemory<float>(cpu.ecx) = float(fpu5);
    // 0043033c  d95904                 -fstp dword ptr [ecx + 4]
    app->getMemory<float>(cpu.ecx + x86::reg32(4) /* 0x4 */) = float(fpu7);
    // 0043033f  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00430341  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00430342  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00430343  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00430344  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    }
    // 00430345  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x54 0x22 0x00 */
void Application::sub_430350(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00430350  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00430351  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00430352  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00430353  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00430354  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00430355  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00430357  83ec30                 -sub esp, 0x30
    (cpu.esp) -= x86::reg32(x86::sreg32(48 /*0x30*/));
    // 0043035a  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 0043035c  89d1                   -mov ecx, edx
    cpu.ecx = cpu.edx;
    // 0043035e  ba01000000             -mov edx, 1
    cpu.edx = 1 /*0x1*/;
    // 00430363  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00430365  e87604ffff             -call 0x4207e0
    cpu.esp -= 4;
    nfs3hp::trackdata::positionSurface(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0043036a  8b5118                 -mov edx, dword ptr [ecx + 0x18]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(24) /* 0x18 */);
    // 0043036d  83e03f                 -and eax, 0x3f
    cpu.eax &= x86::reg32(x86::sreg32(63 /*0x3f*/));
    // 00430370  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 00430372  7407                   -je 0x43037b
    if (cpu.flags.zf)
    {
        goto L_0x0043037b;
    }
    // 00430374  8d5154                 -lea edx, [ecx + 0x54]
    cpu.edx = x86::reg32(cpu.ecx + x86::reg32(84) /* 0x54 */);
    // 00430377  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 00430379  750a                   -jne 0x430385
    if (!cpu.flags.zf)
    {
        goto L_0x00430385;
    }
L_0x0043037b:
    // 0043037b  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 00430380  e91c010000             -jmp 0x4304a1
    goto L_0x004304a1;
L_0x00430385:
    // 00430385  8b716c                 -mov esi, dword ptr [ecx + 0x6c]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(108) /* 0x6c */);
    // 00430388  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 0043038a  740d                   -je 0x430399
    if (cpu.flags.zf)
    {
        goto L_0x00430399;
    }
    // 0043038c  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 00430391  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00430393  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00430394  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00430395  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00430396  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00430397  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00430398  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x00430399:
    // 00430399  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0043039b  7405                   -je 0x4303a2
    if (cpu.flags.zf)
    {
        goto L_0x004303a2;
    }
    // 0043039d  83f80e                 +cmp eax, 0xe
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(14 /*0xe*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004303a0  750d                   -jne 0x4303af
    if (!cpu.flags.zf)
    {
        goto L_0x004303af;
    }
L_0x004303a2:
    // 004303a2  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 004303a7  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004303a9  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004303aa  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004303ab  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004303ac  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004303ad  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004303ae  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004303af:
    // 004303af  8975f8                 -mov dword ptr [ebp - 8], esi
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.esi;
    // 004303b2  8b839c000000           -mov eax, dword ptr [ebx + 0x9c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(156) /* 0x9c */);
    // 004303b8  31d2                   +xor edx, edx
    cpu.clear_co();
    cpu.set_szp((cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx))));
    // 004303ba  8945f4                 -mov dword ptr [ebp - 0xc], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.eax;
    // 004303bd  e979000000             -jmp 0x43043b
    goto L_0x0043043b;
L_0x004303c2:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004303c2  8b7110                 -mov esi, dword ptr [ecx + 0x10]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(16) /* 0x10 */);
    // 004303c5  8d04f500000000         -lea eax, [esi*8]
    cpu.eax = x86::reg32(cpu.esi * 8);
    // 004303cc  01f0                   -add eax, esi
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.esi));
    // 004303ce  8b3548d95d00           -mov esi, dword ptr [0x5dd948]
    cpu.esi = app->getMemory<x86::reg32>(x86::reg32(6150472) /* 0x5dd948 */);
    // 004303d4  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 004303d7  01f0                   -add eax, esi
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.esi));
L_0x004303d9:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004303d9  8d7dd0                 -lea edi, [ebp - 0x30]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(-48) /* -0x30 */);
    // 004303dc  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 004303de  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004303df  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004303e0  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004303e1  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 004303e3  7511                   -jne 0x4303f6
    if (!cpu.flags.zf)
    {
        goto L_0x004303f6;
    }
    // 004303e5  8b45d4                 -mov eax, dword ptr [ebp - 0x2c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-44) /* -0x2c */);
    // 004303e8  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 004303eb  db45fc                 +fild dword ptr [ebp - 4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 004303ee  dc0d14745300           +fmul qword ptr [0x537414]
    x86::Float fpu2 = cpu.fpu.mul(fpu1, x86::Float(app->getMemory<double>(x86::reg32(5469204) /* 0x537414 */)));
    cpu.fpu.count += 1;
    cpu.fpu.st(0) = fpu2;
    }
    // 004303f4  eb3c                   -jmp 0x430432
    goto L_0x00430432;
L_0x004303f6:
    // 004303f6  8b45d4                 -mov eax, dword ptr [ebp - 0x2c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-44) /* -0x2c */);
    // 004303f9  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 004303fc  db45fc                 +fild dword ptr [ebp - 4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu3 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 004303ff  dc0d14745300           +fmul qword ptr [0x537414]
    x86::Float fpu4 = cpu.fpu.mul(fpu3, x86::Float(app->getMemory<double>(x86::reg32(5469204) /* 0x537414 */)));
    // 00430405  d945f8                 +fld dword ptr [ebp - 8]
    x86::Float fpu5 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */));
    // 00430408  dd55ec                 +fst qword ptr [ebp - 0x14]
    app->getMemory<double>(cpu.ebp + x86::reg32(-20) /* -0x14 */) = double(fpu5);
    // 0043040b  d9c9                   +fxch st(1)
    
    // 0043040d  dd5ddc                 +fstp qword ptr [ebp - 0x24]
    app->getMemory<double>(cpu.ebp + x86::reg32(-36) /* -0x24 */) = double(fpu4);
    // 00430410  dc5ddc                 +fcomp qword ptr [ebp - 0x24]
    cpu.fpu.compare(fpu5, x86::Float(app->getMemory<double>(cpu.ebp + x86::reg32(-36) /* -0x24 */)));
    // 00430413  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00430415  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 00430416  760b                   -jbe 0x430423
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x00430423;
    }
    // 00430418  8b45dc                 -mov eax, dword ptr [ebp - 0x24]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-36) /* -0x24 */);
    // 0043041b  8945e4                 -mov dword ptr [ebp - 0x1c], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-28) /* -0x1c */) = cpu.eax;
    // 0043041e  8b45e0                 -mov eax, dword ptr [ebp - 0x20]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-32) /* -0x20 */);
    // 00430421  eb09                   -jmp 0x43042c
    goto L_0x0043042c;
L_0x00430423:
    // 00430423  8b45ec                 -mov eax, dword ptr [ebp - 0x14]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */);
    // 00430426  8945e4                 -mov dword ptr [ebp - 0x1c], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-28) /* -0x1c */) = cpu.eax;
    // 00430429  8b45f0                 -mov eax, dword ptr [ebp - 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
L_0x0043042c:
    // 0043042c  8945e8                 -mov dword ptr [ebp - 0x18], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-24) /* -0x18 */) = cpu.eax;
    // 0043042f  dd45e4                 -fld qword ptr [ebp - 0x1c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu6 = x86::Float(app->getMemory<double>(cpu.ebp + x86::reg32(-28) /* -0x1c */));
    cpu.fpu.count += 1;
    cpu.fpu.st(0) = fpu6;
    }
L_0x00430432:
    // 00430432  d95df8                 -fstp dword ptr [ebp - 8]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu7 = cpu.fpu.st(0);
    app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = float(fpu7);
    // 00430435  42                     -inc edx
    (cpu.edx)++;
    // 00430436  83fa04                 +cmp edx, 4
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
    cpu.fpu.count -= 1;
    }
    // 00430439  7d1a                   -jge 0x430455
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00430455;
    }
L_0x0043043b:
    // 0043043b  8b4114                 -mov eax, dword ptr [ecx + 0x14]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(20) /* 0x14 */);
    // 0043043e  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00430440  7480                   -je 0x4303c2
    if (cpu.flags.zf)
    {
        goto L_0x004303c2;
    }
    // 00430442  8d049500000000         -lea eax, [edx*4]
    cpu.eax = x86::reg32(cpu.edx * 4);
    // 00430449  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 0043044b  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 0043044e  01c8                   -add eax, ecx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.ecx));
    // 00430450  83c024                 +add eax, 0x24
    {
        x86::reg32& tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(36 /*0x24*/));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 00430453  eb84                   -jmp 0x4303d9
    goto L_0x004303d9;
L_0x00430455:
    // 00430455  6683bb6401000000       +cmp word ptr [ebx + 0x164], 0
    {
        x86::reg16 tmp1 = app->getMemory<x86::reg16>(cpu.ebx + x86::reg32(356) /* 0x164 */);
        x86::reg16 tmp2 = x86::reg16(x86::sreg16(0 /*0x0*/));
        x86::reg16 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 15);
        cpu.flags.of ^= 1 & (result >> 15);
        cpu.flags.of &= (1 & (tmp1 >> 15)) != (1 & (tmp2 >> 15));
        cpu.set_szp(result);
    }
    // 0043045d  7420                   -je 0x43047f
    if (cpu.flags.zf)
    {
        goto L_0x0043047f;
    }
    // 0043045f  d945f8                 +fld dword ptr [ebp - 8]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu8 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */));
    // 00430462  dc051c745300           +fadd qword ptr [0x53741c]
    x86::Float fpu9 = cpu.fpu.add(fpu8, x86::Float(app->getMemory<double>(x86::reg32(5469212) /* 0x53741c */)));
    // 00430468  d945f4                 +fld dword ptr [ebp - 0xc]
    x86::Float fpu10 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */));
    // 0043046b  ded9                   +fcompp 
    cpu.fpu.compare(fpu10, fpu9);
    // 0043046d  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 0043046f  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 00430470  732d                   -jae 0x43049f
    if (!cpu.flags.cf)
    {
        goto L_0x0043049f;
    }
    // 00430472  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 00430477  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00430479  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043047a  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043047b  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043047c  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043047d  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043047e  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x0043047f:
    // 0043047f  d945f8                 +fld dword ptr [ebp - 8]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu11 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */));
    // 00430482  dc0524745300           +fadd qword ptr [0x537424]
    x86::Float fpu12 = cpu.fpu.add(fpu11, x86::Float(app->getMemory<double>(x86::reg32(5469220) /* 0x537424 */)));
    // 00430488  d945f4                 +fld dword ptr [ebp - 0xc]
    x86::Float fpu13 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */));
    // 0043048b  ded9                   +fcompp 
    cpu.fpu.compare(fpu13, fpu12);
    // 0043048d  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 0043048f  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 00430490  730d                   -jae 0x43049f
    if (!cpu.flags.cf)
    {
        goto L_0x0043049f;
    }
    // 00430492  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 00430497  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00430499  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043049a  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043049b  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043049c  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043049d  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043049e  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x0043049f:
    // 0043049f  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
L_0x004304a1:
    // 004304a1  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004304a3  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004304a4  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004304a5  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004304a6  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004304a7  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004304a8  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x90 */
void Application::sub_4304b0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004304b0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004304b1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004304b2  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004304b3  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004304b4  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004304b5  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004304b6  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004304b8  81ec3c020000           -sub esp, 0x23c
    (cpu.esp) -= x86::reg32(x86::sreg32(572 /*0x23c*/));
    // 004304be  81ed82000000           -sub ebp, 0x82
    (cpu.ebp) -= x86::reg32(x86::sreg32(130 /*0x82*/));
    // 004304c4  89457a                 -mov dword ptr [ebp + 0x7a], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(122) /* 0x7a */) = cpu.eax;
    // 004304c7  8d7d12                 -lea edi, [ebp + 0x12]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(18) /* 0x12 */);
    // 004304ca  be30dd4200             -mov esi, 0x42dd30
    cpu.esi = 4382000 /*0x42dd30*/;
    // 004304cf  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004304d0  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004304d1  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004304d2  8d7dee                 -lea edi, [ebp - 0x12]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(-18) /* -0x12 */);
    // 004304d5  be3cdd4200             -mov esi, 0x42dd3c
    cpu.esi = 4382012 /*0x42dd3c*/;
    // 004304da  b909000000             -mov ecx, 9
    cpu.ecx = 9 /*0x9*/;
    // 004304df  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 004304e1  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004304e2  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004304e3  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004304e4  89555e                 -mov dword ptr [ebp + 0x5e], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(94) /* 0x5e */) = cpu.edx;
    // 004304e7  8d7d96                 -lea edi, [ebp - 0x6a]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(-106) /* -0x6a */);
    // 004304ea  8db0c0000000           -lea esi, [eax + 0xc0]
    cpu.esi = x86::reg32(cpu.eax + x86::reg32(192) /* 0xc0 */);
    // 004304f0  f3a5                   -rep movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004304f2  89555a                 -mov dword ptr [ebp + 0x5a], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(90) /* 0x5a */) = cpu.edx;
    // 004304f5  d9052c745300           -fld dword ptr [0x53742c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(x86::reg32(5469228) /* 0x53742c */));
    // 004304fb  d980a4000000           -fld dword ptr [eax + 0xa4]
    x86::Float fpu2 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(164) /* 0xa4 */));
    // 00430501  d8c9                   -fmul st(1)
    x86::Float fpu3 = cpu.fpu.mul(fpu2, x86::Float(fpu1));
    // 00430503  d95dee                 -fstp dword ptr [ebp - 0x12]
    app->getMemory<float>(cpu.ebp + x86::reg32(-18) /* -0x12 */) = float(fpu3);
    // 00430506  d980a8000000           -fld dword ptr [eax + 0xa8]
    x86::Float fpu4 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(168) /* 0xa8 */));
    // 0043050c  d8c9                   -fmul st(1)
    x86::Float fpu5 = cpu.fpu.mul(fpu4, x86::Float(fpu1));
    // 0043050e  d95df2                 -fstp dword ptr [ebp - 0xe]
    app->getMemory<float>(cpu.ebp + x86::reg32(-14) /* -0xe */) = float(fpu5);
    // 00430511  d980ac000000           -fld dword ptr [eax + 0xac]
    x86::Float fpu6 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(172) /* 0xac */));
    // 00430517  8d455a                 -lea eax, [ebp + 0x5a]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(90) /* 0x5a */);
    // 0043051a  d8c9                   -fmul st(1)
    x86::Float fpu7 = cpu.fpu.mul(fpu6, x86::Float(fpu1));
    // 0043051c  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 0043051d  8b457a                 -mov eax, dword ptr [ebp + 0x7a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(122) /* 0x7a */);
    // 00430520  d95df6                 -fstp dword ptr [ebp - 0xa]
    app->getMemory<float>(cpu.ebp + x86::reg32(-10) /* -0xa */) = float(fpu7);
    // 00430523  d980ec000000           -fld dword ptr [eax + 0xec]
    x86::Float fpu8 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(236) /* 0xec */));
    // 00430529  d8c9                   -fmul st(1)
    x86::Float fpu9 = cpu.fpu.mul(fpu8, x86::Float(fpu1));
    // 0043052b  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 0043052e  d91c24                 -fstp dword ptr [esp]
    app->getMemory<float>(cpu.esp) = float(fpu9);
    // 00430531  d980e8000000           -fld dword ptr [eax + 0xe8]
    x86::Float fpu10 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(232) /* 0xe8 */));
    // 00430537  d8c9                   -fmul st(1)
    x86::Float fpu11 = cpu.fpu.mul(fpu10, x86::Float(fpu1));
    // 00430539  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 0043053c  d91c24                 -fstp dword ptr [esp]
    app->getMemory<float>(cpu.esp) = float(fpu11);
    // 0043053f  d888e4000000           -fmul dword ptr [eax + 0xe4]
    x86::Float fpu12 = cpu.fpu.mul(fpu1, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(228) /* 0xe4 */)));
    // 00430545  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 00430548  8d45ba                 -lea eax, [ebp - 0x46]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-70) /* -0x46 */);
    // 0043054b  d91c24                 -fstp dword ptr [esp]
    app->getMemory<float>(cpu.esp) = float(fpu12);
    }
    // 0043054e  e86d270700             -call 0x4a2cc0
    cpu.esp -= 4;
    sub_4a2cc0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00430553  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00430555  740e                   -je 0x430565
    if (cpu.flags.zf)
    {
        goto L_0x00430565;
    }
    // 00430557  8d5d96                 -lea ebx, [ebp - 0x6a]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-106) /* -0x6a */);
    // 0043055a  8d55ba                 -lea edx, [ebp - 0x46]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-70) /* -0x46 */);
    // 0043055d  8d4596                 -lea eax, [ebp - 0x6a]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-106) /* -0x6a */);
    // 00430560  e81bfd0a00             -call 0x4e0280
    cpu.esp -= 4;
    sub_4e0280(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00430565:
    // 00430565  8b457a                 -mov eax, dword ptr [ebp + 0x7a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(122) /* 0x7a */);
    // 00430568  6683b86401000000       +cmp word ptr [eax + 0x164], 0
    {
        x86::reg16 tmp1 = app->getMemory<x86::reg16>(cpu.eax + x86::reg32(356) /* 0x164 */);
        x86::reg16 tmp2 = x86::reg16(x86::sreg16(0 /*0x0*/));
        x86::reg16 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 15);
        cpu.flags.of ^= 1 & (result >> 15);
        cpu.flags.of &= (1 & (tmp1 >> 15)) != (1 & (tmp2 >> 15));
        cpu.set_szp(result);
    }
    // 00430570  0f859b000000           -jne 0x430611
    if (!cpu.flags.zf)
    {
        goto L_0x00430611;
    }
    // 00430576  d98014010000           -fld dword ptr [eax + 0x114]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu13 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(276) /* 0x114 */));
    // 0043057c  31f6                   +xor esi, esi
    cpu.clear_co();
    cpu.set_szp((cpu.esi ^= x86::reg32(x86::sreg32(cpu.esi))));
    // 0043057e  d9e0                   +fchs 
    x86::Float fpu14 = -fpu13;
    // 00430580  89b53affffff           -mov dword ptr [ebp - 0xc6], esi
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-198) /* -0xc6 */) = cpu.esi;
    // 00430586  d99d36ffffff           +fstp dword ptr [ebp - 0xca]
    app->getMemory<float>(cpu.ebp + x86::reg32(-202) /* -0xca */) = float(fpu14);
    // 0043058c  8b801c010000           -mov eax, dword ptr [eax + 0x11c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(284) /* 0x11c */);
    // 00430592  89853effffff           -mov dword ptr [ebp - 0xc2], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-194) /* -0xc2 */) = cpu.eax;
    // 00430598  8b457a                 -mov eax, dword ptr [ebp + 0x7a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(122) /* 0x7a */);
    // 0043059b  8b8014010000           -mov eax, dword ptr [eax + 0x114]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(276) /* 0x114 */);
    // 004305a1  898542ffffff           -mov dword ptr [ebp - 0xbe], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-190) /* -0xbe */) = cpu.eax;
    // 004305a7  8b457a                 -mov eax, dword ptr [ebp + 0x7a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(122) /* 0x7a */);
    // 004305aa  89b546ffffff           -mov dword ptr [ebp - 0xba], esi
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-186) /* -0xba */) = cpu.esi;
    // 004305b0  8b801c010000           -mov eax, dword ptr [eax + 0x11c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(284) /* 0x11c */);
    // 004305b6  89854affffff           -mov dword ptr [ebp - 0xb6], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-182) /* -0xb6 */) = cpu.eax;
    // 004305bc  8b457a                 -mov eax, dword ptr [ebp + 0x7a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(122) /* 0x7a */);
    // 004305bf  8b8014010000           -mov eax, dword ptr [eax + 0x114]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(276) /* 0x114 */);
    // 004305c5  bb04000000             -mov ebx, 4
    cpu.ebx = 4 /*0x4*/;
    // 004305ca  89854effffff           -mov dword ptr [ebp - 0xb2], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-178) /* -0xb2 */) = cpu.eax;
    // 004305d0  8b457a                 -mov eax, dword ptr [ebp + 0x7a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(122) /* 0x7a */);
    // 004305d3  89b552ffffff           -mov dword ptr [ebp - 0xae], esi
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-174) /* -0xae */) = cpu.esi;
    // 004305d9  895d6a                 -mov dword ptr [ebp + 0x6a], ebx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(106) /* 0x6a */) = cpu.ebx;
    // 004305dc  d9801c010000           +fld dword ptr [eax + 0x11c]
    x86::Float fpu15 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(284) /* 0x11c */));
    // 004305e2  d9e0                   +fchs 
    x86::Float fpu16 = -fpu15;
    // 004305e4  d99d56ffffff           +fstp dword ptr [ebp - 0xaa]
    app->getMemory<float>(cpu.ebp + x86::reg32(-170) /* -0xaa */) = float(fpu16);
    // 004305ea  d98014010000           +fld dword ptr [eax + 0x114]
    x86::Float fpu17 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(276) /* 0x114 */));
    // 004305f0  d9e0                   +fchs 
    x86::Float fpu18 = -fpu17;
    // 004305f2  89b55effffff           -mov dword ptr [ebp - 0xa2], esi
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-162) /* -0xa2 */) = cpu.esi;
    // 004305f8  d99d5affffff           +fstp dword ptr [ebp - 0xa6]
    app->getMemory<float>(cpu.ebp + x86::reg32(-166) /* -0xa6 */) = float(fpu18);
    // 004305fe  d9801c010000           +fld dword ptr [eax + 0x11c]
    x86::Float fpu19 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(284) /* 0x11c */));
    // 00430604  d9e0                   +fchs 
    x86::Float fpu20 = -fpu19;
    // 00430606  d99d62ffffff           +fstp dword ptr [ebp - 0x9e]
    app->getMemory<float>(cpu.ebp + x86::reg32(-158) /* -0x9e */) = float(fpu20);
    }
    // 0043060c  e955010000             -jmp 0x430766
    goto L_0x00430766;
L_0x00430611:
    // 00430611  d98014010000           -fld dword ptr [eax + 0x114]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu21 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(276) /* 0x114 */));
    // 00430617  d9e0                   -fchs 
    x86::Float fpu22 = -fpu21;
    // 00430619  d99d36ffffff           -fstp dword ptr [ebp - 0xca]
    app->getMemory<float>(cpu.ebp + x86::reg32(-202) /* -0xca */) = float(fpu22);
    // 0043061f  8b8018010000           -mov eax, dword ptr [eax + 0x118]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(280) /* 0x118 */);
    // 00430625  89853affffff           -mov dword ptr [ebp - 0xc6], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-198) /* -0xc6 */) = cpu.eax;
    // 0043062b  8b457a                 -mov eax, dword ptr [ebp + 0x7a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(122) /* 0x7a */);
    // 0043062e  8b801c010000           -mov eax, dword ptr [eax + 0x11c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(284) /* 0x11c */);
    // 00430634  89853effffff           -mov dword ptr [ebp - 0xc2], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-194) /* -0xc2 */) = cpu.eax;
    // 0043063a  8b457a                 -mov eax, dword ptr [ebp + 0x7a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(122) /* 0x7a */);
    // 0043063d  8b8014010000           -mov eax, dword ptr [eax + 0x114]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(276) /* 0x114 */);
    // 00430643  898542ffffff           -mov dword ptr [ebp - 0xbe], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-190) /* -0xbe */) = cpu.eax;
    // 00430649  8b457a                 -mov eax, dword ptr [ebp + 0x7a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(122) /* 0x7a */);
    // 0043064c  8b8018010000           -mov eax, dword ptr [eax + 0x118]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(280) /* 0x118 */);
    // 00430652  898546ffffff           -mov dword ptr [ebp - 0xba], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-186) /* -0xba */) = cpu.eax;
    // 00430658  8b457a                 -mov eax, dword ptr [ebp + 0x7a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(122) /* 0x7a */);
    // 0043065b  8b801c010000           -mov eax, dword ptr [eax + 0x11c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(284) /* 0x11c */);
    // 00430661  89854affffff           -mov dword ptr [ebp - 0xb6], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-182) /* -0xb6 */) = cpu.eax;
    // 00430667  8b457a                 -mov eax, dword ptr [ebp + 0x7a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(122) /* 0x7a */);
    // 0043066a  8b8014010000           -mov eax, dword ptr [eax + 0x114]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(276) /* 0x114 */);
    // 00430670  89854effffff           -mov dword ptr [ebp - 0xb2], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-178) /* -0xb2 */) = cpu.eax;
    // 00430676  8b457a                 -mov eax, dword ptr [ebp + 0x7a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(122) /* 0x7a */);
    // 00430679  8b8018010000           -mov eax, dword ptr [eax + 0x118]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(280) /* 0x118 */);
    // 0043067f  898552ffffff           -mov dword ptr [ebp - 0xae], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-174) /* -0xae */) = cpu.eax;
    // 00430685  8b457a                 -mov eax, dword ptr [ebp + 0x7a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(122) /* 0x7a */);
    // 00430688  d9801c010000           -fld dword ptr [eax + 0x11c]
    x86::Float fpu23 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(284) /* 0x11c */));
    // 0043068e  d9e0                   -fchs 
    x86::Float fpu24 = -fpu23;
    // 00430690  d99d56ffffff           -fstp dword ptr [ebp - 0xaa]
    app->getMemory<float>(cpu.ebp + x86::reg32(-170) /* -0xaa */) = float(fpu24);
    // 00430696  d98014010000           -fld dword ptr [eax + 0x114]
    x86::Float fpu25 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(276) /* 0x114 */));
    // 0043069c  d9e0                   -fchs 
    x86::Float fpu26 = -fpu25;
    // 0043069e  d99d5affffff           -fstp dword ptr [ebp - 0xa6]
    app->getMemory<float>(cpu.ebp + x86::reg32(-166) /* -0xa6 */) = float(fpu26);
    // 004306a4  8b8018010000           -mov eax, dword ptr [eax + 0x118]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(280) /* 0x118 */);
    // 004306aa  89855effffff           -mov dword ptr [ebp - 0xa2], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-162) /* -0xa2 */) = cpu.eax;
    // 004306b0  8b457a                 -mov eax, dword ptr [ebp + 0x7a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(122) /* 0x7a */);
    // 004306b3  d9801c010000           -fld dword ptr [eax + 0x11c]
    x86::Float fpu27 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(284) /* 0x11c */));
    // 004306b9  d9e0                   -fchs 
    x86::Float fpu28 = -fpu27;
    // 004306bb  d99d62ffffff           -fstp dword ptr [ebp - 0x9e]
    app->getMemory<float>(cpu.ebp + x86::reg32(-158) /* -0x9e */) = float(fpu28);
    // 004306c1  d98014010000           -fld dword ptr [eax + 0x114]
    x86::Float fpu29 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(276) /* 0x114 */));
    // 004306c7  d9e0                   -fchs 
    x86::Float fpu30 = -fpu29;
    // 004306c9  d99d66ffffff           -fstp dword ptr [ebp - 0x9a]
    app->getMemory<float>(cpu.ebp + x86::reg32(-154) /* -0x9a */) = float(fpu30);
    // 004306cf  d98018010000           -fld dword ptr [eax + 0x118]
    x86::Float fpu31 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(280) /* 0x118 */));
    // 004306d5  d9e0                   -fchs 
    x86::Float fpu32 = -fpu31;
    // 004306d7  d99d6affffff           -fstp dword ptr [ebp - 0x96]
    app->getMemory<float>(cpu.ebp + x86::reg32(-150) /* -0x96 */) = float(fpu32);
    // 004306dd  8b801c010000           -mov eax, dword ptr [eax + 0x11c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(284) /* 0x11c */);
    // 004306e3  89856effffff           -mov dword ptr [ebp - 0x92], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-146) /* -0x92 */) = cpu.eax;
    // 004306e9  8b457a                 -mov eax, dword ptr [ebp + 0x7a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(122) /* 0x7a */);
    // 004306ec  8b8014010000           -mov eax, dword ptr [eax + 0x114]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(276) /* 0x114 */);
    // 004306f2  898572ffffff           -mov dword ptr [ebp - 0x8e], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-142) /* -0x8e */) = cpu.eax;
    // 004306f8  8b457a                 -mov eax, dword ptr [ebp + 0x7a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(122) /* 0x7a */);
    // 004306fb  d98018010000           -fld dword ptr [eax + 0x118]
    x86::Float fpu33 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(280) /* 0x118 */));
    // 00430701  d9e0                   -fchs 
    x86::Float fpu34 = -fpu33;
    // 00430703  d99d76ffffff           -fstp dword ptr [ebp - 0x8a]
    app->getMemory<float>(cpu.ebp + x86::reg32(-138) /* -0x8a */) = float(fpu34);
    // 00430709  8b801c010000           -mov eax, dword ptr [eax + 0x11c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(284) /* 0x11c */);
    // 0043070f  89857affffff           -mov dword ptr [ebp - 0x86], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-134) /* -0x86 */) = cpu.eax;
    // 00430715  8b457a                 -mov eax, dword ptr [ebp + 0x7a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(122) /* 0x7a */);
    // 00430718  8b8014010000           -mov eax, dword ptr [eax + 0x114]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(276) /* 0x114 */);
    // 0043071e  b908000000             -mov ecx, 8
    cpu.ecx = 8 /*0x8*/;
    // 00430723  89857effffff           -mov dword ptr [ebp - 0x82], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-130) /* -0x82 */) = cpu.eax;
    // 00430729  8b457a                 -mov eax, dword ptr [ebp + 0x7a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(122) /* 0x7a */);
    // 0043072c  894d6a                 -mov dword ptr [ebp + 0x6a], ecx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(106) /* 0x6a */) = cpu.ecx;
    // 0043072f  d98018010000           -fld dword ptr [eax + 0x118]
    x86::Float fpu35 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(280) /* 0x118 */));
    // 00430735  d9e0                   -fchs 
    x86::Float fpu36 = -fpu35;
    // 00430737  d95d82                 -fstp dword ptr [ebp - 0x7e]
    app->getMemory<float>(cpu.ebp + x86::reg32(-126) /* -0x7e */) = float(fpu36);
    // 0043073a  d9801c010000           -fld dword ptr [eax + 0x11c]
    x86::Float fpu37 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(284) /* 0x11c */));
    // 00430740  d9e0                   -fchs 
    x86::Float fpu38 = -fpu37;
    // 00430742  d95d86                 -fstp dword ptr [ebp - 0x7a]
    app->getMemory<float>(cpu.ebp + x86::reg32(-122) /* -0x7a */) = float(fpu38);
    // 00430745  d98014010000           -fld dword ptr [eax + 0x114]
    x86::Float fpu39 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(276) /* 0x114 */));
    // 0043074b  d9e0                   -fchs 
    x86::Float fpu40 = -fpu39;
    // 0043074d  d95d8a                 -fstp dword ptr [ebp - 0x76]
    app->getMemory<float>(cpu.ebp + x86::reg32(-118) /* -0x76 */) = float(fpu40);
    // 00430750  d98018010000           -fld dword ptr [eax + 0x118]
    x86::Float fpu41 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(280) /* 0x118 */));
    // 00430756  d9e0                   -fchs 
    x86::Float fpu42 = -fpu41;
    // 00430758  d95d8e                 -fstp dword ptr [ebp - 0x72]
    app->getMemory<float>(cpu.ebp + x86::reg32(-114) /* -0x72 */) = float(fpu42);
    // 0043075b  d9801c010000           -fld dword ptr [eax + 0x11c]
    x86::Float fpu43 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(284) /* 0x11c */));
    // 00430761  d9e0                   -fchs 
    x86::Float fpu44 = -fpu43;
    // 00430763  d95d92                 -fstp dword ptr [ebp - 0x6e]
    app->getMemory<float>(cpu.ebp + x86::reg32(-110) /* -0x6e */) = float(fpu44);
    }
L_0x00430766:
    // 00430766  8d8536ffffff           -lea eax, [ebp - 0xca]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-202) /* -0xca */);
    // 0043076c  8b4d7a                 -mov ecx, dword ptr [ebp + 0x7a]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(122) /* 0x7a */);
    // 0043076f  8d5d96                 -lea ebx, [ebp - 0x6a]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-106) /* -0x6a */);
    // 00430772  8d9536ffffff           -lea edx, [ebp - 0xca]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-202) /* -0xca */);
    // 00430778  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00430779  81c198000000           -add ecx, 0x98
    (cpu.ecx) += x86::reg32(x86::sreg32(152 /*0x98*/));
    // 0043077f  8b456a                 -mov eax, dword ptr [ebp + 0x6a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(106) /* 0x6a */);
    // 00430782  e8a9fc0a00             -call 0x4e0430
    cpu.esp -= 4;
    sub_4e0430(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00430787  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
    // 00430789  895d72                 -mov dword ptr [ebp + 0x72], ebx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(114) /* 0x72 */) = cpu.ebx;
L_0x0043078c:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 0043078c  8b4572                 -mov eax, dword ptr [ebp + 0x72]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(114) /* 0x72 */);
    // 0043078f  3b456a                 +cmp eax, dword ptr [ebp + 0x6a]
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(106) /* 0x6a */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00430792  0f8dc8040000           -jge 0x430c60
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00430c60;
    }
    // 00430798  8b457a                 -mov eax, dword ptr [ebp + 0x7a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(122) /* 0x7a */);
    // 0043079b  8b5572                 -mov edx, dword ptr [ebp + 0x72]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(114) /* 0x72 */);
    // 0043079e  8d700c                 -lea esi, [eax + 0xc]
    cpu.esi = x86::reg32(cpu.eax + x86::reg32(12) /* 0xc */);
    // 004307a1  8d049500000000         -lea eax, [edx*4]
    cpu.eax = x86::reg32(cpu.edx * 4);
    // 004307a8  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 004307aa  b91e000000             -mov ecx, 0x1e
    cpu.ecx = 30 /*0x1e*/;
    // 004307af  8d148500000000         -lea edx, [eax*4]
    cpu.edx = x86::reg32(cpu.eax * 4);
    // 004307b6  8dbd46feffff           -lea edi, [ebp - 0x1ba]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(-442) /* -0x1ba */);
    // 004307bc  8d5dee                 -lea ebx, [ebp - 0x12]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-18) /* -0x12 */);
    // 004307bf  8b842a36ffffff         -mov eax, dword ptr [edx + ebp - 0xca]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(-202) /* -0xca */ + cpu.ebp * 1);
    // 004307c6  f3a5                   -rep movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004307c8  894542                 -mov dword ptr [ebp + 0x42], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(66) /* 0x42 */) = cpu.eax;
    // 004307cb  8b842a3affffff         -mov eax, dword ptr [edx + ebp - 0xc6]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(-198) /* -0xc6 */ + cpu.ebp * 1);
    // 004307d2  8d4d42                 -lea ecx, [ebp + 0x42]
    cpu.ecx = x86::reg32(cpu.ebp + x86::reg32(66) /* 0x42 */);
    // 004307d5  894546                 -mov dword ptr [ebp + 0x46], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(70) /* 0x46 */) = cpu.eax;
    // 004307d8  8b842a3effffff         -mov eax, dword ptr [edx + ebp - 0xc2]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(-194) /* -0xc2 */ + cpu.ebp * 1);
    // 004307df  8d5542                 -lea edx, [ebp + 0x42]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(66) /* 0x42 */);
    // 004307e2  89454a                 -mov dword ptr [ebp + 0x4a], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(74) /* 0x4a */) = cpu.eax;
    // 004307e5  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 004307ea  e8c1f70a00             -call 0x4dffb0
    cpu.esp -= 4;
    sub_4dffb0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004307ef  d94542                 -fld dword ptr [ebp + 0x42]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu45 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(66) /* 0x42 */));
    // 004307f2  dc0d34745300           -fmul qword ptr [0x537434]
    x86::Float fpu46 = cpu.fpu.mul(fpu45, x86::Float(app->getMemory<double>(x86::reg32(5469236) /* 0x537434 */)));
    // 004307f8  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 004307fb  db1c24                 -fistp dword ptr [esp]
    app->getMemory<x86::reg32>(cpu.esp) = x86::reg32(cpu.fpu.toInteger<x86::sreg32>(fpu46));
    // 004307fe  58                     -pop eax
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004307ff  d94546                 -fld dword ptr [ebp + 0x46]
    x86::Float fpu47 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(70) /* 0x46 */));
    // 00430802  dc0d34745300           -fmul qword ptr [0x537434]
    x86::Float fpu48 = cpu.fpu.mul(fpu47, x86::Float(app->getMemory<double>(x86::reg32(5469236) /* 0x537434 */)));
    // 00430808  89451e                 -mov dword ptr [ebp + 0x1e], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(30) /* 0x1e */) = cpu.eax;
    // 0043080b  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 0043080e  db1c24                 -fistp dword ptr [esp]
    app->getMemory<x86::reg32>(cpu.esp) = x86::reg32(cpu.fpu.toInteger<x86::sreg32>(fpu48));
    // 00430811  58                     -pop eax
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00430812  d9454a                 -fld dword ptr [ebp + 0x4a]
    x86::Float fpu49 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(74) /* 0x4a */));
    // 00430815  dc0d34745300           -fmul qword ptr [0x537434]
    x86::Float fpu50 = cpu.fpu.mul(fpu49, x86::Float(app->getMemory<double>(x86::reg32(5469236) /* 0x537434 */)));
    // 0043081b  31ff                   -xor edi, edi
    cpu.edi ^= x86::reg32(x86::sreg32(cpu.edi));
    // 0043081d  8d751e                 -lea esi, [ebp + 0x1e]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(30) /* 0x1e */);
    // 00430820  897d76                 -mov dword ptr [ebp + 0x76], edi
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(118) /* 0x76 */) = cpu.edi;
    // 00430823  8dbd4afeffff           -lea edi, [ebp - 0x1b6]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(-438) /* -0x1b6 */);
    // 00430829  bb01000000             -mov ebx, 1
    cpu.ebx = 1 /*0x1*/;
    // 0043082e  8d9546feffff           -lea edx, [ebp - 0x1ba]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-442) /* -0x1ba */);
    // 00430834  894522                 -mov dword ptr [ebp + 0x22], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(34) /* 0x22 */) = cpu.eax;
    // 00430837  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 0043083a  db1c24                 -fistp dword ptr [esp]
    app->getMemory<x86::reg32>(cpu.esp) = x86::reg32(cpu.fpu.toInteger<x86::sreg32>(fpu50));
    // 0043083d  58                     -pop eax
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043083e  894526                 -mov dword ptr [ebp + 0x26], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(38) /* 0x26 */) = cpu.eax;
    // 00430841  8d451e                 -lea eax, [ebp + 0x1e]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(30) /* 0x1e */);
    // 00430844  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00430845  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00430846  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    }
    // 00430847  e894eefeff             -call 0x41f6e0
    cpu.esp -= 4;
    nfs3hp::trackdata::updatePosition(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0043084c  8d9546feffff           -lea edx, [ebp - 0x1ba]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-442) /* -0x1ba */);
    // 00430852  8b457a                 -mov eax, dword ptr [ebp + 0x7a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(122) /* 0x7a */);
    // 00430855  e8f6faffff             -call 0x430350
    cpu.esp -= 4;
    sub_430350(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0043085a  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0043085c  0f844e010000           -je 0x4309b0
    if (cpu.flags.zf)
    {
        goto L_0x004309b0;
    }
    // 00430862  b91e000000             -mov ecx, 0x1e
    cpu.ecx = 30 /*0x1e*/;
    // 00430867  8dbdbefeffff           -lea edi, [ebp - 0x142]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(-322) /* -0x142 */);
    // 0043086d  8db546feffff           -lea esi, [ebp - 0x1ba]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(-442) /* -0x1ba */);
    // 00430873  8b557a                 -mov edx, dword ptr [ebp + 0x7a]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(122) /* 0x7a */);
    // 00430876  8d9d46feffff           -lea ebx, [ebp - 0x1ba]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-442) /* -0x1ba */);
    // 0043087c  8d451e                 -lea eax, [ebp + 0x1e]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(30) /* 0x1e */);
    // 0043087f  f3a5                   -rep movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00430881  83c20c                 -add edx, 0xc
    (cpu.edx) += x86::reg32(x86::sreg32(12 /*0xc*/));
    // 00430884  8d4d5e                 -lea ecx, [ebp + 0x5e]
    cpu.ecx = x86::reg32(cpu.ebp + x86::reg32(94) /* 0x5e */);
    // 00430887  8d7dde                 -lea edi, [ebp - 0x22]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(-34) /* -0x22 */);
    // 0043088a  be48dd4200             -mov esi, 0x42dd48
    cpu.esi = 4382024 /*0x42dd48*/;
    // 0043088f  e8ccf4feff             -call 0x41fd60
    cpu.esp -= 4;
    nfs3hp::trackdata::quadEdgeFlags(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00430894  894562                 -mov dword ptr [ebp + 0x62], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(98) /* 0x62 */) = cpu.eax;
    // 00430897  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00430899  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 0043089a  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 0043089b  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 0043089c  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 0043089d  89551a                 -mov dword ptr [ebp + 0x1a], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(26) /* 0x1a */) = cpu.edx;
    // 004308a0  895516                 -mov dword ptr [ebp + 0x16], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(22) /* 0x16 */) = cpu.edx;
    // 004308a3  895512                 -mov dword ptr [ebp + 0x12], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(18) /* 0x12 */) = cpu.edx;
    // 004308a6  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004308a8  0f8402010000           -je 0x4309b0
    if (cpu.flags.zf)
    {
        goto L_0x004309b0;
    }
    // 004308ae  89556e                 -mov dword ptr [ebp + 0x6e], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(110) /* 0x6e */) = cpu.edx;
    // 004308b1  31c9                   +xor ecx, ecx
    cpu.clear_co();
    cpu.set_szp((cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx))));
    // 004308b3  eb09                   -jmp 0x4308be
    goto L_0x004308be;
L_0x004308b5:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004308b5  83f904                 +cmp ecx, 4
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(4 /*0x4*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004308b8  0f8d92000000           -jge 0x430950
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00430950;
    }
L_0x004308be:
    // 004308be  8d048d00000000         -lea eax, [ecx*4]
    cpu.eax = x86::reg32(cpu.ecx * 4);
    // 004308c5  8b5562                 -mov edx, dword ptr [ebp + 0x62]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(98) /* 0x62 */);
    // 004308c8  8b7c28de               -mov edi, dword ptr [eax + ebp - 0x22]
    cpu.edi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(-34) /* -0x22 */ + cpu.ebp * 1);
    // 004308cc  85fa                   +test edx, edi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edi));
    // 004308ce  0f8476000000           -je 0x43094a
    if (cpu.flags.zf)
    {
        goto L_0x0043094a;
    }
    // 004308d4  8b557a                 -mov edx, dword ptr [ebp + 0x7a]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(122) /* 0x7a */);
    // 004308d7  8d9dbefeffff           -lea ebx, [ebp - 0x142]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-322) /* -0x142 */);
    // 004308dd  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 004308df  83c20c                 -add edx, 0xc
    (cpu.edx) += x86::reg32(x86::sreg32(12 /*0xc*/));
    // 004308e2  e889effeff             -call 0x41f870
    cpu.esp -= 4;
    nfs3hp::trackdata::findMatchingQuad(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004308e7  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004308e9  7412                   -je 0x4308fd
    if (cpu.flags.zf)
    {
        goto L_0x004308fd;
    }
    // 004308eb  8d95befeffff           -lea edx, [ebp - 0x142]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-322) /* -0x142 */);
    // 004308f1  8b457a                 -mov eax, dword ptr [ebp + 0x7a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(122) /* 0x7a */);
    // 004308f4  e857faffff             -call 0x430350
    cpu.esp -= 4;
    sub_430350(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004308f9  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004308fb  744d                   -je 0x43094a
    if (cpu.flags.zf)
    {
        goto L_0x0043094a;
    }
L_0x004308fd:
    // 004308fd  8b5d7a                 -mov ebx, dword ptr [ebp + 0x7a]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(122) /* 0x7a */);
    // 00430900  8d554e                 -lea edx, [ebp + 0x4e]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(78) /* 0x4e */);
    // 00430903  8b448dde               -mov eax, dword ptr [ebp + ecx*4 - 0x22]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-34) /* -0x22 */ + cpu.ecx * 4);
    // 00430907  83c30c                 -add ebx, 0xc
    (cpu.ebx) += x86::reg32(x86::sreg32(12 /*0xc*/));
    // 0043090a  e801f9ffff             -call 0x430210
    cpu.esp -= 4;
    sub_430210(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0043090f  d9e8                   -fld1 
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu51 = 1.0;
    // 00430911  d94512                 -fld dword ptr [ebp + 0x12]
    x86::Float fpu52 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(18) /* 0x12 */));
    // 00430914  d94516                 -fld dword ptr [ebp + 0x16]
    x86::Float fpu53 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(22) /* 0x16 */));
    // 00430917  d9451a                 -fld dword ptr [ebp + 0x1a]
    x86::Float fpu54 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(26) /* 0x1a */));
    // 0043091a  8b5576                 -mov edx, dword ptr [ebp + 0x76]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(118) /* 0x76 */);
    // 0043091d  8b448dde               -mov eax, dword ptr [ebp + ecx*4 - 0x22]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-34) /* -0x22 */ + cpu.ecx * 4);
    // 00430921  d9cb                   -fxch st(3)
    
    // 00430923  d8456e                 -fadd dword ptr [ebp + 0x6e]
    x86::Float fpu55 = cpu.fpu.add(fpu51, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(110) /* 0x6e */)));
    // 00430926  d9ca                   -fxch st(2)
    
    // 00430928  d8454e                 -fadd dword ptr [ebp + 0x4e]
    x86::Float fpu56 = cpu.fpu.add(fpu52, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(78) /* 0x4e */)));
    // 0043092b  d9c9                   -fxch st(1)
    
    // 0043092d  d84552                 -fadd dword ptr [ebp + 0x52]
    x86::Float fpu57 = cpu.fpu.add(fpu53, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(82) /* 0x52 */)));
    // 00430930  d9cb                   -fxch st(3)
    
    // 00430932  d84556                 -fadd dword ptr [ebp + 0x56]
    x86::Float fpu58 = cpu.fpu.add(fpu54, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(86) /* 0x56 */)));
    // 00430935  09c2                   +or edx, eax
    cpu.clear_co();
    cpu.set_szp((cpu.edx |= x86::reg32(x86::sreg32(cpu.eax))));
    // 00430937  d9ca                   +fxch st(2)
    
    // 00430939  d95d6e                 +fstp dword ptr [ebp + 0x6e]
    app->getMemory<float>(cpu.ebp + x86::reg32(110) /* 0x6e */) = float(fpu55);
    // 0043093c  d95d12                 +fstp dword ptr [ebp + 0x12]
    app->getMemory<float>(cpu.ebp + x86::reg32(18) /* 0x12 */) = float(fpu56);
    // 0043093f  d9c9                   +fxch st(1)
    
    // 00430941  d95d16                 +fstp dword ptr [ebp + 0x16]
    app->getMemory<float>(cpu.ebp + x86::reg32(22) /* 0x16 */) = float(fpu57);
    // 00430944  d95d1a                 +fstp dword ptr [ebp + 0x1a]
    app->getMemory<float>(cpu.ebp + x86::reg32(26) /* 0x1a */) = float(fpu58);
    // 00430947  895576                 -mov dword ptr [ebp + 0x76], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(118) /* 0x76 */) = cpu.edx;
    }
L_0x0043094a:
    // 0043094a  41                     +inc ecx
    {
        x86::reg32& tmp = cpu.ecx;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 0043094b  e965ffffff             -jmp 0x4308b5
    goto L_0x004308b5;
L_0x00430950:
    // 00430950  f7456effffff7f         +test dword ptr [ebp + 0x6e], 0x7fffffff
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(110) /* 0x6e */) & 2147483647 /*0x7fffffff*/));
    // 00430957  742a                   -je 0x430983
    if (cpu.flags.zf)
    {
        goto L_0x00430983;
    }
    // 00430959  d9e8                   -fld1 
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu59 = 1.0;
    // 0043095b  d94512                 -fld dword ptr [ebp + 0x12]
    x86::Float fpu60 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(18) /* 0x12 */));
    // 0043095e  d9c9                   -fxch st(1)
    
    // 00430960  d8756e                 -fdiv dword ptr [ebp + 0x6e]
    x86::Float fpu61 = cpu.fpu.div(fpu59, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(110) /* 0x6e */)));
    // 00430963  d9c9                   -fxch st(1)
    
    // 00430965  d8c9                   -fmul st(1)
    x86::Float fpu62 = cpu.fpu.mul(fpu60, x86::Float(fpu61));
    // 00430967  d94516                 -fld dword ptr [ebp + 0x16]
    x86::Float fpu63 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(22) /* 0x16 */));
    // 0043096a  d8ca                   -fmul st(2)
    x86::Float fpu64 = cpu.fpu.mul(fpu63, x86::Float(fpu61));
    // 0043096c  d9451a                 -fld dword ptr [ebp + 0x1a]
    x86::Float fpu65 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(26) /* 0x1a */));
    // 0043096f  decb                   -fmulp st(3)
    x86::Float fpu66 = cpu.fpu.mul(fpu61, fpu65);
    // 00430971  31db                   +xor ebx, ebx
    cpu.clear_co();
    cpu.set_szp((cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx))));
    // 00430973  d9c9                   +fxch st(1)
    
    // 00430975  d95d12                 +fstp dword ptr [ebp + 0x12]
    app->getMemory<float>(cpu.ebp + x86::reg32(18) /* 0x12 */) = float(fpu62);
    // 00430978  d95d16                 +fstp dword ptr [ebp + 0x16]
    app->getMemory<float>(cpu.ebp + x86::reg32(22) /* 0x16 */) = float(fpu64);
    // 0043097b  d95d1a                 +fstp dword ptr [ebp + 0x1a]
    app->getMemory<float>(cpu.ebp + x86::reg32(26) /* 0x1a */) = float(fpu66);
    // 0043097e  895d16                 -mov dword ptr [ebp + 0x16], ebx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(22) /* 0x16 */) = cpu.ebx;
    }
    // 00430981  eb2d                   -jmp 0x4309b0
    goto L_0x004309b0;
L_0x00430983:
    // 00430983  8b457a                 -mov eax, dword ptr [ebp + 0x7a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(122) /* 0x7a */);
    // 00430986  d98098000000           -fld dword ptr [eax + 0x98]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu67 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(152) /* 0x98 */));
    // 0043098c  d86542                 -fsub dword ptr [ebp + 0x42]
    x86::Float fpu68 = cpu.fpu.sub(fpu67, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(66) /* 0x42 */)));
    // 0043098f  d95d12                 -fstp dword ptr [ebp + 0x12]
    app->getMemory<float>(cpu.ebp + x86::reg32(18) /* 0x12 */) = float(fpu68);
    // 00430992  d9809c000000           -fld dword ptr [eax + 0x9c]
    x86::Float fpu69 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(156) /* 0x9c */));
    // 00430998  d86546                 -fsub dword ptr [ebp + 0x46]
    x86::Float fpu70 = cpu.fpu.sub(fpu69, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(70) /* 0x46 */)));
    // 0043099b  d95d16                 -fstp dword ptr [ebp + 0x16]
    app->getMemory<float>(cpu.ebp + x86::reg32(22) /* 0x16 */) = float(fpu70);
    // 0043099e  d980a0000000           -fld dword ptr [eax + 0xa0]
    x86::Float fpu71 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(160) /* 0xa0 */));
    // 004309a4  d8654a                 -fsub dword ptr [ebp + 0x4a]
    x86::Float fpu72 = cpu.fpu.sub(fpu71, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(74) /* 0x4a */)));
    // 004309a7  8b4562                 -mov eax, dword ptr [ebp + 0x62]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(98) /* 0x62 */);
    // 004309aa  d95d1a                 -fstp dword ptr [ebp + 0x1a]
    app->getMemory<float>(cpu.ebp + x86::reg32(26) /* 0x1a */) = float(fpu72);
    // 004309ad  894576                 -mov dword ptr [ebp + 0x76], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(118) /* 0x76 */) = cpu.eax;
    }
L_0x004309b0:
    // 004309b0  837d7600               +cmp dword ptr [ebp + 0x76], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(118) /* 0x76 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004309b4  0f84b3020000           -je 0x430c6d
    if (cpu.flags.zf)
    {
        goto L_0x00430c6d;
    }
    // 004309ba  8d4512                 -lea eax, [ebp + 0x12]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(18) /* 0x12 */);
    // 004309bd  e82e690600             -call 0x4972f0
    cpu.esp -= 4;
    sub_4972f0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004309c2  d9ee                   +fldz 
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu73 = 0.0;
    // 004309c4  ded9                   +fcompp 
    x86::Float fpu74 = cpu.fpu.st(0);
    cpu.fpu.compare(fpu73, fpu74);
    // 004309c6  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 004309c8  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    cpu.fpu.count -= 1;
    }
    // 004309c9  0f8491020000           -je 0x430c60
    if (cpu.flags.zf)
    {
        goto L_0x00430c60;
    }
    // 004309cf  8b5572                 -mov edx, dword ptr [ebp + 0x72]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(114) /* 0x72 */);
    // 004309d2  8d049500000000         -lea eax, [edx*4]
    cpu.eax = x86::reg32(cpu.edx * 4);
    // 004309d9  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 004309db  8d7dfa                 -lea edi, [ebp - 6]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(-6) /* -0x6 */);
    // 004309de  8db48536ffffff         -lea esi, [ebp + eax*4 - 0xca]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(-202) /* -0xca */ + cpu.eax * 4);
    // 004309e5  8a6576                 -mov ah, byte ptr [ebp + 0x76]
    cpu.ah = app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(118) /* 0x76 */);
    // 004309e8  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004309e9  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004309ea  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004309eb  f6c404                 +test ah, 4
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.ah & 4 /*0x4*/));
    // 004309ee  7449                   -je 0x430a39
    if (cpu.flags.zf)
    {
        goto L_0x00430a39;
    }
    // 004309f0  f6c401                 +test ah, 1
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.ah & 1 /*0x1*/));
    // 004309f3  741e                   -je 0x430a13
    if (cpu.flags.zf)
    {
        goto L_0x00430a13;
    }
    // 004309f5  8b457a                 -mov eax, dword ptr [ebp + 0x7a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(122) /* 0x7a */);
    // 004309f8  dd053c745300           +fld qword ptr [0x53743c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu75 = x86::Float(app->getMemory<double>(x86::reg32(5469244) /* 0x53743c */));
    // 004309fe  db403c                 +fild dword ptr [eax + 0x3c]
    x86::Float fpu76 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.eax + x86::reg32(60) /* 0x3c */)));
    // 00430a01  d8c9                   +fmul st(1)
    x86::Float fpu77 = cpu.fpu.mul(fpu76, x86::Float(fpu75));
    // 00430a03  d95dfa                 +fstp dword ptr [ebp - 6]
    app->getMemory<float>(cpu.ebp + x86::reg32(-6) /* -0x6 */) = float(fpu77);
    // 00430a06  db4040                 +fild dword ptr [eax + 0x40]
    x86::Float fpu78 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.eax + x86::reg32(64) /* 0x40 */)));
    // 00430a09  d8c9                   +fmul st(1)
    x86::Float fpu79 = cpu.fpu.mul(fpu78, x86::Float(fpu75));
    // 00430a0b  d95dfe                 +fstp dword ptr [ebp - 2]
    app->getMemory<float>(cpu.ebp + x86::reg32(-2) /* -0x2 */) = float(fpu79);
    // 00430a0e  db4044                 +fild dword ptr [eax + 0x44]
    x86::Float fpu80 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.eax + x86::reg32(68) /* 0x44 */)));
    cpu.fpu.count += 2;
    cpu.fpu.st(0) = fpu80;
    cpu.fpu.st(1) = fpu75;
    }
    // 00430a11  eb1c                   -jmp 0x430a2f
    goto L_0x00430a2f;
L_0x00430a13:
    // 00430a13  8b457a                 -mov eax, dword ptr [ebp + 0x7a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(122) /* 0x7a */);
    // 00430a16  dd053c745300           +fld qword ptr [0x53743c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu81 = x86::Float(app->getMemory<double>(x86::reg32(5469244) /* 0x53743c */));
    // 00430a1c  db4030                 +fild dword ptr [eax + 0x30]
    x86::Float fpu82 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.eax + x86::reg32(48) /* 0x30 */)));
    // 00430a1f  d8c9                   +fmul st(1)
    x86::Float fpu83 = cpu.fpu.mul(fpu82, x86::Float(fpu81));
    // 00430a21  d95dfa                 +fstp dword ptr [ebp - 6]
    app->getMemory<float>(cpu.ebp + x86::reg32(-6) /* -0x6 */) = float(fpu83);
    // 00430a24  db4034                 +fild dword ptr [eax + 0x34]
    x86::Float fpu84 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.eax + x86::reg32(52) /* 0x34 */)));
    // 00430a27  d8c9                   +fmul st(1)
    x86::Float fpu85 = cpu.fpu.mul(fpu84, x86::Float(fpu81));
    // 00430a29  d95dfe                 +fstp dword ptr [ebp - 2]
    app->getMemory<float>(cpu.ebp + x86::reg32(-2) /* -0x2 */) = float(fpu85);
    // 00430a2c  db4038                 +fild dword ptr [eax + 0x38]
    x86::Float fpu86 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.eax + x86::reg32(56) /* 0x38 */)));
    cpu.fpu.count += 2;
    cpu.fpu.st(0) = fpu86;
    cpu.fpu.st(1) = fpu81;
    }
L_0x00430a2f:
    // 00430a2f  dec9                   +fmulp st(1)
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu87 = cpu.fpu.st(1);
    x86::Float fpu88 = cpu.fpu.st(0);
    x86::Float fpu89 = cpu.fpu.mul(fpu87, fpu88);
    // 00430a31  d95d02                 +fstp dword ptr [ebp + 2]
    app->getMemory<float>(cpu.ebp + x86::reg32(2) /* 0x2 */) = float(fpu89);
    cpu.fpu.count -= 2;
    }
    // 00430a34  e98f000000             -jmp 0x430ac8
    goto L_0x00430ac8;
L_0x00430a39:
    // 00430a39  f6c408                 +test ah, 8
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.ah & 8 /*0x8*/));
    // 00430a3c  7446                   -je 0x430a84
    if (cpu.flags.zf)
    {
        goto L_0x00430a84;
    }
    // 00430a3e  f6c401                 +test ah, 1
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.ah & 1 /*0x1*/));
    // 00430a41  741e                   -je 0x430a61
    if (cpu.flags.zf)
    {
        goto L_0x00430a61;
    }
    // 00430a43  8b457a                 -mov eax, dword ptr [ebp + 0x7a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(122) /* 0x7a */);
    // 00430a46  dd053c745300           +fld qword ptr [0x53743c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu90 = x86::Float(app->getMemory<double>(x86::reg32(5469244) /* 0x53743c */));
    // 00430a4c  db4048                 +fild dword ptr [eax + 0x48]
    x86::Float fpu91 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.eax + x86::reg32(72) /* 0x48 */)));
    // 00430a4f  d8c9                   +fmul st(1)
    x86::Float fpu92 = cpu.fpu.mul(fpu91, x86::Float(fpu90));
    // 00430a51  d95dfa                 +fstp dword ptr [ebp - 6]
    app->getMemory<float>(cpu.ebp + x86::reg32(-6) /* -0x6 */) = float(fpu92);
    // 00430a54  db404c                 +fild dword ptr [eax + 0x4c]
    x86::Float fpu93 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.eax + x86::reg32(76) /* 0x4c */)));
    // 00430a57  d8c9                   +fmul st(1)
    x86::Float fpu94 = cpu.fpu.mul(fpu93, x86::Float(fpu90));
    // 00430a59  d95dfe                 +fstp dword ptr [ebp - 2]
    app->getMemory<float>(cpu.ebp + x86::reg32(-2) /* -0x2 */) = float(fpu94);
    // 00430a5c  db4050                 +fild dword ptr [eax + 0x50]
    x86::Float fpu95 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.eax + x86::reg32(80) /* 0x50 */)));
    cpu.fpu.count += 2;
    cpu.fpu.st(0) = fpu95;
    cpu.fpu.st(1) = fpu90;
    }
    // 00430a5f  eb1c                   -jmp 0x430a7d
    goto L_0x00430a7d;
L_0x00430a61:
    // 00430a61  8b457a                 -mov eax, dword ptr [ebp + 0x7a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(122) /* 0x7a */);
    // 00430a64  dd053c745300           +fld qword ptr [0x53743c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu96 = x86::Float(app->getMemory<double>(x86::reg32(5469244) /* 0x53743c */));
    // 00430a6a  db4054                 +fild dword ptr [eax + 0x54]
    x86::Float fpu97 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.eax + x86::reg32(84) /* 0x54 */)));
    // 00430a6d  d8c9                   +fmul st(1)
    x86::Float fpu98 = cpu.fpu.mul(fpu97, x86::Float(fpu96));
    // 00430a6f  d95dfa                 +fstp dword ptr [ebp - 6]
    app->getMemory<float>(cpu.ebp + x86::reg32(-6) /* -0x6 */) = float(fpu98);
    // 00430a72  db4058                 +fild dword ptr [eax + 0x58]
    x86::Float fpu99 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.eax + x86::reg32(88) /* 0x58 */)));
    // 00430a75  d8c9                   +fmul st(1)
    x86::Float fpu100 = cpu.fpu.mul(fpu99, x86::Float(fpu96));
    // 00430a77  d95dfe                 +fstp dword ptr [ebp - 2]
    app->getMemory<float>(cpu.ebp + x86::reg32(-2) /* -0x2 */) = float(fpu100);
    // 00430a7a  db405c                 +fild dword ptr [eax + 0x5c]
    x86::Float fpu101 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.eax + x86::reg32(92) /* 0x5c */)));
    cpu.fpu.count += 2;
    cpu.fpu.st(0) = fpu101;
    cpu.fpu.st(1) = fpu96;
    }
L_0x00430a7d:
    // 00430a7d  dec9                   +fmulp st(1)
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu102 = cpu.fpu.st(1);
    x86::Float fpu103 = cpu.fpu.st(0);
    x86::Float fpu104 = cpu.fpu.mul(fpu102, fpu103);
    // 00430a7f  d95d02                 +fstp dword ptr [ebp + 2]
    app->getMemory<float>(cpu.ebp + x86::reg32(2) /* 0x2 */) = float(fpu104);
    cpu.fpu.count -= 2;
    }
    // 00430a82  eb44                   -jmp 0x430ac8
    goto L_0x00430ac8;
L_0x00430a84:
    // 00430a84  f6c401                 +test ah, 1
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.ah & 1 /*0x1*/));
    // 00430a87  741e                   -je 0x430aa7
    if (cpu.flags.zf)
    {
        goto L_0x00430aa7;
    }
    // 00430a89  8b457a                 -mov eax, dword ptr [ebp + 0x7a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(122) /* 0x7a */);
    // 00430a8c  dd053c745300           +fld qword ptr [0x53743c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu105 = x86::Float(app->getMemory<double>(x86::reg32(5469244) /* 0x53743c */));
    // 00430a92  db403c                 +fild dword ptr [eax + 0x3c]
    x86::Float fpu106 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.eax + x86::reg32(60) /* 0x3c */)));
    // 00430a95  d8c9                   +fmul st(1)
    x86::Float fpu107 = cpu.fpu.mul(fpu106, x86::Float(fpu105));
    // 00430a97  d95dfa                 +fstp dword ptr [ebp - 6]
    app->getMemory<float>(cpu.ebp + x86::reg32(-6) /* -0x6 */) = float(fpu107);
    // 00430a9a  db4040                 +fild dword ptr [eax + 0x40]
    x86::Float fpu108 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.eax + x86::reg32(64) /* 0x40 */)));
    // 00430a9d  d8c9                   +fmul st(1)
    x86::Float fpu109 = cpu.fpu.mul(fpu108, x86::Float(fpu105));
    // 00430a9f  d95dfe                 +fstp dword ptr [ebp - 2]
    app->getMemory<float>(cpu.ebp + x86::reg32(-2) /* -0x2 */) = float(fpu109);
    // 00430aa2  db4044                 +fild dword ptr [eax + 0x44]
    x86::Float fpu110 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.eax + x86::reg32(68) /* 0x44 */)));
    cpu.fpu.count += 2;
    cpu.fpu.st(0) = fpu110;
    cpu.fpu.st(1) = fpu105;
    }
    // 00430aa5  eb1c                   -jmp 0x430ac3
    goto L_0x00430ac3;
L_0x00430aa7:
    // 00430aa7  8b457a                 -mov eax, dword ptr [ebp + 0x7a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(122) /* 0x7a */);
    // 00430aaa  dd053c745300           -fld qword ptr [0x53743c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu111 = x86::Float(app->getMemory<double>(x86::reg32(5469244) /* 0x53743c */));
    // 00430ab0  db4030                 -fild dword ptr [eax + 0x30]
    x86::Float fpu112 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.eax + x86::reg32(48) /* 0x30 */)));
    // 00430ab3  d8c9                   -fmul st(1)
    x86::Float fpu113 = cpu.fpu.mul(fpu112, x86::Float(fpu111));
    // 00430ab5  d95dfa                 -fstp dword ptr [ebp - 6]
    app->getMemory<float>(cpu.ebp + x86::reg32(-6) /* -0x6 */) = float(fpu113);
    // 00430ab8  db4034                 -fild dword ptr [eax + 0x34]
    x86::Float fpu114 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.eax + x86::reg32(52) /* 0x34 */)));
    // 00430abb  d8c9                   -fmul st(1)
    x86::Float fpu115 = cpu.fpu.mul(fpu114, x86::Float(fpu111));
    // 00430abd  d95dfe                 -fstp dword ptr [ebp - 2]
    app->getMemory<float>(cpu.ebp + x86::reg32(-2) /* -0x2 */) = float(fpu115);
    // 00430ac0  db4038                 -fild dword ptr [eax + 0x38]
    x86::Float fpu116 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.eax + x86::reg32(56) /* 0x38 */)));
    cpu.fpu.count += 2;
    cpu.fpu.st(0) = fpu116;
    cpu.fpu.st(1) = fpu111;
    }
L_0x00430ac3:
    // 00430ac3  dec9                   -fmulp st(1)
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu117 = cpu.fpu.st(1);
    x86::Float fpu118 = cpu.fpu.st(0);
    x86::Float fpu119 = cpu.fpu.mul(fpu117, fpu118);
    // 00430ac5  d95d02                 -fstp dword ptr [ebp + 2]
    app->getMemory<float>(cpu.ebp + x86::reg32(2) /* 0x2 */) = float(fpu119);
    cpu.fpu.count -= 2;
    }
L_0x00430ac8:
    // 00430ac8  8b4572                 -mov eax, dword ptr [ebp + 0x72]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(114) /* 0x72 */);
    // 00430acb  8d148500000000         -lea edx, [eax*4]
    cpu.edx = x86::reg32(cpu.eax * 4);
    // 00430ad2  8d4dfa                 -lea ecx, [ebp - 6]
    cpu.ecx = x86::reg32(cpu.ebp + x86::reg32(-6) /* -0x6 */);
    // 00430ad5  29c2                   -sub edx, eax
    (cpu.edx) -= x86::reg32(x86::sreg32(cpu.eax));
    // 00430ad7  8d8536ffffff           -lea eax, [ebp - 0xca]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-202) /* -0xca */);
    // 00430add  c1e202                 -shl edx, 2
    cpu.edx <<= 2 /*0x2*/ % 32;
    // 00430ae0  8d5d12                 -lea ebx, [ebp + 0x12]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(18) /* 0x12 */);
    // 00430ae3  01c2                   -add edx, eax
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.eax));
    // 00430ae5  8b457a                 -mov eax, dword ptr [ebp + 0x7a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(122) /* 0x7a */);
    // 00430ae8  e823e3ffff             -call 0x42ee10
    cpu.esp -= 4;
    nfs3hp::raceload::hitWall(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00430aed  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00430aef  0f8478010000           -je 0x430c6d
    if (cpu.flags.zf)
    {
        goto L_0x00430c6d;
    }
    // 00430af5  8b457a                 -mov eax, dword ptr [ebp + 0x7a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(122) /* 0x7a */);
    // 00430af8  8b501c                 -mov edx, dword ptr [eax + 0x1c]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(28) /* 0x1c */);
    // 00430afb  8d04d500000000         -lea eax, [edx*8]
    cpu.eax = x86::reg32(cpu.edx * 8);
    // 00430b02  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 00430b04  8b1548d95d00           -mov edx, dword ptr [0x5dd948]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(6150472) /* 0x5dd948 */);
    // 00430b0a  dd053c745300           -fld qword ptr [0x53743c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu120 = x86::Float(app->getMemory<double>(x86::reg32(5469244) /* 0x53743c */));
    // 00430b10  db0482                 -fild dword ptr [edx + eax*4]
    x86::Float fpu121 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.edx + cpu.eax * 4)));
    // 00430b13  d8c9                   -fmul st(1)
    x86::Float fpu122 = cpu.fpu.mul(fpu121, x86::Float(fpu120));
    // 00430b15  db448204               -fild dword ptr [edx + eax*4 + 4]
    x86::Float fpu123 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.edx + x86::reg32(4) /* 0x4 */ + cpu.eax * 4)));
    // 00430b19  d8ca                   -fmul st(2)
    x86::Float fpu124 = cpu.fpu.mul(fpu123, x86::Float(fpu120));
    // 00430b1b  db448208               -fild dword ptr [edx + eax*4 + 8]
    x86::Float fpu125 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.edx + x86::reg32(8) /* 0x8 */ + cpu.eax * 4)));
    // 00430b1f  8b457a                 -mov eax, dword ptr [ebp + 0x7a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(122) /* 0x7a */);
    // 00430b22  d8cb                   -fmul st(3)
    x86::Float fpu126 = cpu.fpu.mul(fpu125, x86::Float(fpu120));
    // 00430b24  d98098000000           -fld dword ptr [eax + 0x98]
    x86::Float fpu127 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(152) /* 0x98 */));
    // 00430b2a  d9cb                   -fxch st(3)
    
    // 00430b2c  d95d2a                 -fstp dword ptr [ebp + 0x2a]
    app->getMemory<float>(cpu.ebp + x86::reg32(42) /* 0x2a */) = float(fpu122);
    // 00430b2f  d9ca                   -fxch st(2)
    
    // 00430b31  d8652a                 -fsub dword ptr [ebp + 0x2a]
    x86::Float fpu128 = cpu.fpu.sub(fpu127, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(42) /* 0x2a */)));
    // 00430b34  d9c9                   -fxch st(1)
    
    // 00430b36  d95d2e                 -fstp dword ptr [ebp + 0x2e]
    app->getMemory<float>(cpu.ebp + x86::reg32(46) /* 0x2e */) = float(fpu124);
    // 00430b39  d95d36                 -fstp dword ptr [ebp + 0x36]
    app->getMemory<float>(cpu.ebp + x86::reg32(54) /* 0x36 */) = float(fpu128);
    // 00430b3c  d9809c000000           -fld dword ptr [eax + 0x9c]
    x86::Float fpu129 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(156) /* 0x9c */));
    // 00430b42  d8652e                 -fsub dword ptr [ebp + 0x2e]
    x86::Float fpu130 = cpu.fpu.sub(fpu129, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(46) /* 0x2e */)));
    // 00430b45  d9c9                   -fxch st(1)
    
    // 00430b47  d95d32                 -fstp dword ptr [ebp + 0x32]
    app->getMemory<float>(cpu.ebp + x86::reg32(50) /* 0x32 */) = float(fpu126);
    // 00430b4a  d95d3a                 -fstp dword ptr [ebp + 0x3a]
    app->getMemory<float>(cpu.ebp + x86::reg32(58) /* 0x3a */) = float(fpu130);
    // 00430b4d  d980a0000000           -fld dword ptr [eax + 0xa0]
    x86::Float fpu131 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(160) /* 0xa0 */));
    // 00430b53  d86532                 -fsub dword ptr [ebp + 0x32]
    x86::Float fpu132 = cpu.fpu.sub(fpu131, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(50) /* 0x32 */)));
    // 00430b56  d95d3e                 -fstp dword ptr [ebp + 0x3e]
    app->getMemory<float>(cpu.ebp + x86::reg32(62) /* 0x3e */) = float(fpu132);
    // 00430b59  8b481c                 -mov ecx, dword ptr [eax + 0x1c]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(28) /* 0x1c */);
    // 00430b5c  8d04cd00000000         -lea eax, [ecx*8]
    cpu.eax = x86::reg32(cpu.ecx * 8);
    // 00430b63  01c8                   -add eax, ecx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.ecx));
    // 00430b65  8b448215               -mov eax, dword ptr [edx + eax*4 + 0x15]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(21) /* 0x15 */ + cpu.eax * 4);
    // 00430b69  c1f818                 -sar eax, 0x18
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (24 /*0x18*/ % 32));
    // 00430b6c  c1e009                 -shl eax, 9
    cpu.eax <<= 9 /*0x9*/ % 32;
    // 00430b6f  89457e                 -mov dword ptr [ebp + 0x7e], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */) = cpu.eax;
    // 00430b72  db457e                 -fild dword ptr [ebp + 0x7e]
    x86::Float fpu133 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */)));
    // 00430b75  d8c9                   -fmul st(1)
    x86::Float fpu134 = cpu.fpu.mul(fpu133, x86::Float(fpu120));
    // 00430b77  8b457a                 -mov eax, dword ptr [ebp + 0x7a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(122) /* 0x7a */);
    // 00430b7a  d95d06                 -fstp dword ptr [ebp + 6]
    app->getMemory<float>(cpu.ebp + x86::reg32(6) /* 0x6 */) = float(fpu134);
    // 00430b7d  8b481c                 -mov ecx, dword ptr [eax + 0x1c]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(28) /* 0x1c */);
    // 00430b80  8d04cd00000000         -lea eax, [ecx*8]
    cpu.eax = x86::reg32(cpu.ecx * 8);
    // 00430b87  01c8                   -add eax, ecx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.ecx));
    // 00430b89  8b448216               -mov eax, dword ptr [edx + eax*4 + 0x16]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(22) /* 0x16 */ + cpu.eax * 4);
    // 00430b8d  c1f818                 -sar eax, 0x18
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (24 /*0x18*/ % 32));
    // 00430b90  c1e009                 -shl eax, 9
    cpu.eax <<= 9 /*0x9*/ % 32;
    // 00430b93  89457e                 -mov dword ptr [ebp + 0x7e], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */) = cpu.eax;
    // 00430b96  db457e                 -fild dword ptr [ebp + 0x7e]
    x86::Float fpu135 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */)));
    // 00430b99  d8c9                   -fmul st(1)
    x86::Float fpu136 = cpu.fpu.mul(fpu135, x86::Float(fpu120));
    // 00430b9b  8b457a                 -mov eax, dword ptr [ebp + 0x7a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(122) /* 0x7a */);
    // 00430b9e  d95d0a                 -fstp dword ptr [ebp + 0xa]
    app->getMemory<float>(cpu.ebp + x86::reg32(10) /* 0xa */) = float(fpu136);
    // 00430ba1  8b481c                 -mov ecx, dword ptr [eax + 0x1c]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(28) /* 0x1c */);
    // 00430ba4  8d04cd00000000         -lea eax, [ecx*8]
    cpu.eax = x86::reg32(cpu.ecx * 8);
    // 00430bab  01c8                   -add eax, ecx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.ecx));
    // 00430bad  8b448217               -mov eax, dword ptr [edx + eax*4 + 0x17]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(23) /* 0x17 */ + cpu.eax * 4);
    // 00430bb1  c1f818                 -sar eax, 0x18
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (24 /*0x18*/ % 32));
    // 00430bb4  c1e009                 +shl eax, 9
    {
        x86::reg8 tmp = 9 /*0x9*/ % 32;
        x86::reg32& op = cpu.eax;
        if (tmp)
        {
            cpu.flags.cf = 1 & (op >> (32 - tmp));
            cpu.set_szp((op <<= tmp));
            if (tmp == 1) cpu.flags.of = (cpu.flags.cf != (1 & (op >> (32 - 1))));
        }
    }
    // 00430bb7  89457e                 -mov dword ptr [ebp + 0x7e], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */) = cpu.eax;
    // 00430bba  db457e                 +fild dword ptr [ebp + 0x7e]
    x86::Float fpu137 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */)));
    // 00430bbd  dec9                   +fmulp st(1)
    x86::Float fpu138 = cpu.fpu.mul(fpu120, fpu137);
    // 00430bbf  8d5536                 -lea edx, [ebp + 0x36]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(54) /* 0x36 */);
    // 00430bc2  8d4506                 -lea eax, [ebp + 6]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(6) /* 0x6 */);
    // 00430bc5  d95d0e                 +fstp dword ptr [ebp + 0xe]
    app->getMemory<float>(cpu.ebp + x86::reg32(14) /* 0xe */) = float(fpu138);
    }
    // 00430bc8  e823f60a00             -call 0x4e01f0
    cpu.esp -= 4;
    sub_4e01f0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00430bcd  d9ee                   +fldz 
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu139 = 0.0;
    // 00430bcf  d9c9                   +fxch st(1)
    
    // 00430bd1  d95d66                 +fstp dword ptr [ebp + 0x66]
    x86::Float fpu140 = cpu.fpu.st(0);
    app->getMemory<float>(cpu.ebp + x86::reg32(102) /* 0x66 */) = float(fpu140);
    // 00430bd4  d85d66                 +fcomp dword ptr [ebp + 0x66]
    cpu.fpu.compare(fpu139, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(102) /* 0x66 */)));
    // 00430bd7  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00430bd9  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    cpu.fpu.count -= 1;
    }
    // 00430bda  7722                   -ja 0x430bfe
    if (!cpu.flags.cf && !cpu.flags.zf)
    {
        goto L_0x00430bfe;
    }
    // 00430bdc  8b457a                 -mov eax, dword ptr [ebp + 0x7a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(122) /* 0x7a */);
    // 00430bdf  8b501c                 -mov edx, dword ptr [eax + 0x1c]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(28) /* 0x1c */);
    // 00430be2  8d04d500000000         -lea eax, [edx*8]
    cpu.eax = x86::reg32(cpu.edx * 8);
    // 00430be9  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 00430beb  8b1548d95d00           -mov edx, dword ptr [0x5dd948]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(6150472) /* 0x5dd948 */);
    // 00430bf1  8a44820e               -mov al, byte ptr [edx + eax*4 + 0xe]
    cpu.al = app->getMemory<x86::reg8>(cpu.edx + x86::reg32(14) /* 0xe */ + cpu.eax * 4);
    // 00430bf5  240f                   -and al, 0xf
    cpu.al &= x86::reg8(x86::sreg8(15 /*0xf*/));
    // 00430bf7  25ff000000             +and eax, 0xff
    cpu.clear_co();
    cpu.set_szp((cpu.eax &= x86::reg32(x86::sreg32(255 /*0xff*/))));
    // 00430bfc  eb2d                   -jmp 0x430c2b
    goto L_0x00430c2b;
L_0x00430bfe:
    // 00430bfe  7626                   -jbe 0x430c26
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x00430c26;
    }
    // 00430c00  8b457a                 -mov eax, dword ptr [ebp + 0x7a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(122) /* 0x7a */);
    // 00430c03  8b501c                 -mov edx, dword ptr [eax + 0x1c]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(28) /* 0x1c */);
    // 00430c06  8d04d500000000         -lea eax, [edx*8]
    cpu.eax = x86::reg32(cpu.edx * 8);
    // 00430c0d  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 00430c0f  8b1548d95d00           -mov edx, dword ptr [0x5dd948]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(6150472) /* 0x5dd948 */);
    // 00430c15  8a44820e               -mov al, byte ptr [edx + eax*4 + 0xe]
    cpu.al = app->getMemory<x86::reg8>(cpu.edx + x86::reg32(14) /* 0xe */ + cpu.eax * 4);
    // 00430c19  25ff000000             -and eax, 0xff
    cpu.eax &= x86::reg32(x86::sreg32(255 /*0xff*/));
    // 00430c1e  c1f804                 -sar eax, 4
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (4 /*0x4*/ % 32));
    // 00430c21  83e00f                 +and eax, 0xf
    cpu.clear_co();
    cpu.set_szp((cpu.eax &= x86::reg32(x86::sreg32(15 /*0xf*/))));
    // 00430c24  eb05                   -jmp 0x430c2b
    goto L_0x00430c2b;
L_0x00430c26:
    // 00430c26  b804000000             -mov eax, 4
    cpu.eax = 4 /*0x4*/;
L_0x00430c2b:
    // 00430c2b  8b557a                 -mov edx, dword ptr [ebp + 0x7a]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(122) /* 0x7a */);
    // 00430c2e  0d00000400             -or eax, 0x40000
    cpu.eax |= x86::reg32(x86::sreg32(262144 /*0x40000*/));
    // 00430c33  8a8a00020000           -mov cl, byte ptr [edx + 0x200]
    cpu.cl = app->getMemory<x86::reg8>(cpu.edx + x86::reg32(512) /* 0x200 */);
    // 00430c39  898270010000           -mov dword ptr [edx + 0x170], eax
    app->getMemory<x86::reg32>(cpu.edx + x86::reg32(368) /* 0x170 */) = cpu.eax;
    // 00430c3f  f6c102                 +test cl, 2
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.cl & 2 /*0x2*/));
    // 00430c42  740b                   -je 0x430c4f
    if (cpu.flags.zf)
    {
        goto L_0x00430c4f;
    }
    // 00430c44  8d5512                 -lea edx, [ebp + 0x12]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(18) /* 0x12 */);
    // 00430c47  8b457a                 -mov eax, dword ptr [ebp + 0x7a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(122) /* 0x7a */);
    // 00430c4a  e81155fdff             -call 0x406160
    cpu.esp -= 4;
    sub_406160(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00430c4f:
    // 00430c4f  8b457a                 -mov eax, dword ptr [ebp + 0x7a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(122) /* 0x7a */);
    // 00430c52  f6800002000004         +test byte ptr [eax + 0x200], 4
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(cpu.eax + x86::reg32(512) /* 0x200 */) & 4 /*0x4*/));
    // 00430c59  7405                   -je 0x430c60
    if (cpu.flags.zf)
    {
        goto L_0x00430c60;
    }
    // 00430c5b  e894980700             -call 0x4aa4f4
    cpu.esp -= 4;
    sub_4aa4f4(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00430c60:
    // 00430c60  8da582000000           -lea esp, [ebp + 0x82]
    cpu.esp = x86::reg32(cpu.ebp + x86::reg32(130) /* 0x82 */);
    // 00430c66  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00430c67  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00430c68  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00430c69  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00430c6a  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00430c6b  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00430c6c  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x00430c6d:
    // 00430c6d  ff4572                 +inc dword ptr [ebp + 0x72]
    {
        auto tmp = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(114) /* 0x72 */);
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 00430c70  e917fbffff             -jmp 0x43078c
    goto L_0x0043078c;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 0x8b 0xdb */
void Application::sub_430c80(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00430c80  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00430c81  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00430c82  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00430c83  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00430c84  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00430c85  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00430c87  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00430c89  89d6                   -mov esi, edx
    cpu.esi = cpu.edx;
    // 00430c8b  bb20000000             -mov ebx, 0x20
    cpu.ebx = 32 /*0x20*/;
    // 00430c90  31ff                   -xor edi, edi
    cpu.edi ^= x86::reg32(x86::sreg32(cpu.edi));
L_0x00430c92:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00430c92  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 00430c94  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00430c96  e845f2ffff             -call 0x42fee0
    cpu.esp -= 4;
    sub_42fee0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00430c9b  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 00430c9d  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00430c9f  7405                   -je 0x430ca6
    if (cpu.flags.zf)
    {
        goto L_0x00430ca6;
    }
    // 00430ca1  bf01000000             -mov edi, 1
    cpu.edi = 1 /*0x1*/;
L_0x00430ca6:
    // 00430ca6  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 00430ca8  7406                   -je 0x430cb0
    if (cpu.flags.zf)
    {
        goto L_0x00430cb0;
    }
    // 00430caa  4b                     -dec ebx
    (cpu.ebx)--;
    // 00430cab  83fbff                 +cmp ebx, -1
    {
        x86::reg32 tmp1 = cpu.ebx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(-1 /*-0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00430cae  75e2                   -jne 0x430c92
    if (!cpu.flags.zf)
    {
        goto L_0x00430c92;
    }
L_0x00430cb0:
    // 00430cb0  85ff                   +test edi, edi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edi & cpu.edi));
    // 00430cb2  740e                   -je 0x430cc2
    if (cpu.flags.zf)
    {
        goto L_0x00430cc2;
    }
    // 00430cb4  bb84fe5e00             -mov ebx, 0x5efe84
    cpu.ebx = 6225540 /*0x5efe84*/;
    // 00430cb9  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 00430cbb  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00430cbd  e8bee5ffff             -call 0x42f280
    cpu.esp -= 4;
    nfs3hp::raceload::carsCollide(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00430cc2:
    // 00430cc2  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00430cc3  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00430cc4  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00430cc5  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00430cc6  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00430cc7  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8b 0xd2 */
void Application::sub_430cd0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00430cd0  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00430cd1  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00430cd2  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00430cd4  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00430cd6  8915bc375500           -mov dword ptr [0x5537bc], edx
    app->getMemory<x86::reg32>(x86::reg32(5584828) /* 0x5537bc */) = cpu.edx;
    // 00430cdc  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00430cdd  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00430cde  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x90 */
void Application::sub_430ce0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00430ce0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00430ce1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00430ce2  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00430ce3  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00430ce5  83ec10                 -sub esp, 0x10
    (cpu.esp) -= x86::reg32(x86::sreg32(16 /*0x10*/));
    // 00430ce8  8b5d14                 -mov ebx, dword ptr [ebp + 0x14]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(20) /* 0x14 */);
    // 00430ceb  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00430ced  d902                   -fld dword ptr [edx]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.edx));
    // 00430cef  d8a098000000           -fsub dword ptr [eax + 0x98]
    x86::Float fpu2 = cpu.fpu.sub(fpu1, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(152) /* 0x98 */)));
    // 00430cf5  05c0000000             +add eax, 0xc0
    {
        x86::reg32& tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(192 /*0xc0*/));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 00430cfa  d91b                   +fstp dword ptr [ebx]
    app->getMemory<float>(cpu.ebx) = float(fpu2);
    // 00430cfc  d94208                 +fld dword ptr [edx + 8]
    x86::Float fpu3 = x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(8) /* 0x8 */));
    // 00430cff  d860e0                 +fsub dword ptr [eax - 0x20]
    x86::Float fpu4 = cpu.fpu.sub(fpu3, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(-32) /* -0x20 */)));
    // 00430d02  89da                   -mov edx, ebx
    cpu.edx = cpu.ebx;
    // 00430d04  d95b08                 +fstp dword ptr [ebx + 8]
    app->getMemory<float>(cpu.ebx + x86::reg32(8) /* 0x8 */) = float(fpu4);
    // 00430d07  c7430400000000         -mov dword ptr [ebx + 4], 0
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(4) /* 0x4 */) = 0 /*0x0*/;
    }
    // 00430d0e  e8ddf40a00             -call 0x4e01f0
    cpu.esp -= 4;
    sub_4e01f0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00430d13  d9ee                   +fldz 
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu5 = 0.0;
    // 00430d15  d9c9                   +fxch st(1)
    
    // 00430d17  d95df8                 +fstp dword ptr [ebp - 8]
    x86::Float fpu6 = cpu.fpu.st(0);
    app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = float(fpu6);
    // 00430d1a  d85df8                 +fcomp dword ptr [ebp - 8]
    cpu.fpu.compare(fpu5, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    // 00430d1d  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00430d1f  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    cpu.fpu.count -= 1;
    }
    // 00430d20  7308                   -jae 0x430d2a
    if (!cpu.flags.cf)
    {
        goto L_0x00430d2a;
    }
    // 00430d22  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 00430d25  8945f0                 -mov dword ptr [ebp - 0x10], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = cpu.eax;
    // 00430d28  eb08                   -jmp 0x430d32
    goto L_0x00430d32;
L_0x00430d2a:
    // 00430d2a  d945f8                 +fld dword ptr [ebp - 8]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu7 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */));
    // 00430d2d  d9e0                   +fchs 
    x86::Float fpu8 = -fpu7;
    // 00430d2f  d95df0                 +fstp dword ptr [ebp - 0x10]
    app->getMemory<float>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = float(fpu8);
    }
L_0x00430d32:
    // 00430d32  d98114010000           +fld dword ptr [ecx + 0x114]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu9 = x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(276) /* 0x114 */));
    // 00430d38  d84510                 +fadd dword ptr [ebp + 0x10]
    x86::Float fpu10 = cpu.fpu.add(fpu9, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(16) /* 0x10 */)));
    // 00430d3b  d85df0                 +fcomp dword ptr [ebp - 0x10]
    cpu.fpu.compare(fpu10, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-16) /* -0x10 */)));
    // 00430d3e  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00430d40  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 00430d41  7304                   -jae 0x430d47
    if (!cpu.flags.cf)
    {
        goto L_0x00430d47;
    }
    // 00430d43  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
    // 00430d45  eb4c                   -jmp 0x430d93
    goto L_0x00430d93;
L_0x00430d47:
    // 00430d47  8d81d8000000           -lea eax, [ecx + 0xd8]
    cpu.eax = x86::reg32(cpu.ecx + x86::reg32(216) /* 0xd8 */);
    // 00430d4d  89da                   -mov edx, ebx
    cpu.edx = cpu.ebx;
    // 00430d4f  e89cf40a00             -call 0x4e01f0
    cpu.esp -= 4;
    sub_4e01f0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00430d54  d9ee                   +fldz 
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu11 = 0.0;
    // 00430d56  d9c9                   +fxch st(1)
    
    // 00430d58  d95dfc                 +fstp dword ptr [ebp - 4]
    x86::Float fpu12 = cpu.fpu.st(0);
    app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = float(fpu12);
    // 00430d5b  d85dfc                 +fcomp dword ptr [ebp - 4]
    cpu.fpu.compare(fpu11, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 00430d5e  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00430d60  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    cpu.fpu.count -= 1;
    }
    // 00430d61  7308                   -jae 0x430d6b
    if (!cpu.flags.cf)
    {
        goto L_0x00430d6b;
    }
    // 00430d63  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00430d66  8945f4                 -mov dword ptr [ebp - 0xc], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.eax;
    // 00430d69  eb08                   -jmp 0x430d73
    goto L_0x00430d73;
L_0x00430d6b:
    // 00430d6b  d945fc                 +fld dword ptr [ebp - 4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu13 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */));
    // 00430d6e  d9e0                   +fchs 
    x86::Float fpu14 = -fpu13;
    // 00430d70  d95df4                 +fstp dword ptr [ebp - 0xc]
    app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */) = float(fpu14);
    }
L_0x00430d73:
    // 00430d73  d9811c010000           +fld dword ptr [ecx + 0x11c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu15 = x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(284) /* 0x11c */));
    // 00430d79  d84510                 +fadd dword ptr [ebp + 0x10]
    x86::Float fpu16 = cpu.fpu.add(fpu15, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(16) /* 0x10 */)));
    // 00430d7c  d85df4                 +fcomp dword ptr [ebp - 0xc]
    cpu.fpu.compare(fpu16, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */)));
    // 00430d7f  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00430d81  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 00430d82  730a                   -jae 0x430d8e
    if (!cpu.flags.cf)
    {
        goto L_0x00430d8e;
    }
    // 00430d84  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00430d86  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00430d88  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00430d89  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00430d8a  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00430d8b  c20800                 -ret 8
    cpu.esp += 4+8 /*0x8*/;
    return;
L_0x00430d8e:
    // 00430d8e  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
L_0x00430d93:
    // 00430d93  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00430d95  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00430d96  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00430d97  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00430d98  c20800                 -ret 8
    cpu.esp += 4+8 /*0x8*/;
    return;
}

/* align: skip 0x8d 0x40 0x00 0x8b 0xc9 */
void Application::sub_430da0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00430da0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00430da1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00430da2  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00430da3  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00430da4  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00430da5  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00430da6  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00430da8  83ec6c                 -sub esp, 0x6c
    (cpu.esp) -= x86::reg32(x86::sreg32(108 /*0x6c*/));
    // 00430dab  8945f0                 -mov dword ptr [ebp - 0x10], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = cpu.eax;
    // 00430dae  83c00c                 -add eax, 0xc
    (cpu.eax) += x86::reg32(x86::sreg32(12 /*0xc*/));
    // 00430db1  e85af1feff             -call 0x41ff10
    cpu.esp -= 4;
    nfs3hp::trackdata::sectionItemCount(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00430db6  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 00430db8  31c2                   -xor edx, eax
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00430dba  8945f4                 -mov dword ptr [ebp - 0xc], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.eax;
    // 00430dbd  8955ec                 -mov dword ptr [ebp - 0x14], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */) = cpu.edx;
L_0x00430dc0:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00430dc0  8b45ec                 -mov eax, dword ptr [ebp - 0x14]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */);
    // 00430dc3  3b45f4                 +cmp eax, dword ptr [ebp - 0xc]
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
    // 00430dc6  0f8de5020000           -jge 0x4310b1
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004310b1;
    }
    // 00430dcc  8b45f0                 -mov eax, dword ptr [ebp - 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 00430dcf  8d4dfc                 -lea ecx, [ebp - 4]
    cpu.ecx = x86::reg32(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00430dd2  8d5db8                 -lea ebx, [ebp - 0x48]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-72) /* -0x48 */);
    // 00430dd5  8b55ec                 -mov edx, dword ptr [ebp - 0x14]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */);
    // 00430dd8  83c00c                 -add eax, 0xc
    (cpu.eax) += x86::reg32(x86::sreg32(12 /*0xc*/));
    // 00430ddb  e840f1feff             -call 0x41ff20
    cpu.esp -= 4;
    nfs3hp::trackdata::sectionItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00430de0  8b45fa                 -mov eax, dword ptr [ebp - 6]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-6) /* -0x6 */);
    // 00430de3  c1f810                 -sar eax, 0x10
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (16 /*0x10*/ % 32));
    // 00430de6  c1e008                 +shl eax, 8
    {
        x86::reg8 tmp = 8 /*0x8*/ % 32;
        x86::reg32& op = cpu.eax;
        if (tmp)
        {
            cpu.flags.cf = 1 & (op >> (32 - tmp));
            cpu.set_szp((op <<= tmp));
            if (tmp == 1) cpu.flags.of = (cpu.flags.cf != (1 & (op >> (32 - 1))));
        }
    }
    // 00430de9  8945f8                 -mov dword ptr [ebp - 8], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.eax;
    // 00430dec  8b45b8                 -mov eax, dword ptr [ebp - 0x48]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-72) /* -0x48 */);
    // 00430def  db45f8                 +fild dword ptr [ebp - 8]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    // 00430df2  8945f8                 -mov dword ptr [ebp - 8], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.eax;
    // 00430df5  dd0544745300           +fld qword ptr [0x537444]
    x86::Float fpu2 = x86::Float(app->getMemory<double>(x86::reg32(5469252) /* 0x537444 */));
    // 00430dfb  d9c9                   +fxch st(1)
    
    // 00430dfd  d8c9                   +fmul st(1)
    x86::Float fpu3 = cpu.fpu.mul(fpu1, x86::Float(fpu2));
    // 00430dff  db45f8                 +fild dword ptr [ebp - 8]
    x86::Float fpu4 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    // 00430e02  8b45bc                 -mov eax, dword ptr [ebp - 0x44]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-68) /* -0x44 */);
    // 00430e05  d8ca                   +fmul st(2)
    x86::Float fpu5 = cpu.fpu.mul(fpu4, x86::Float(fpu2));
    // 00430e07  8945f8                 -mov dword ptr [ebp - 8], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.eax;
    // 00430e0a  8b45c0                 -mov eax, dword ptr [ebp - 0x40]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-64) /* -0x40 */);
    // 00430e0d  db45f8                 +fild dword ptr [ebp - 8]
    x86::Float fpu6 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    // 00430e10  8945f8                 -mov dword ptr [ebp - 8], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.eax;
    // 00430e13  d8cb                   +fmul st(3)
    x86::Float fpu7 = cpu.fpu.mul(fpu6, x86::Float(fpu2));
    // 00430e15  db45f8                 +fild dword ptr [ebp - 8]
    x86::Float fpu8 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    // 00430e18  decc                   +fmulp st(4)
    x86::Float fpu9 = cpu.fpu.mul(fpu2, fpu8);
    // 00430e1a  d9ee                   +fldz 
    x86::Float fpu10 = 0.0;
    // 00430e1c  d9ca                   +fxch st(2)
    
    // 00430e1e  d955c4                 +fst dword ptr [ebp - 0x3c]
    app->getMemory<float>(cpu.ebp + x86::reg32(-60) /* -0x3c */) = float(fpu5);
    // 00430e21  d9c9                   +fxch st(1)
    
    // 00430e23  d95dc8                 +fstp dword ptr [ebp - 0x38]
    app->getMemory<float>(cpu.ebp + x86::reg32(-56) /* -0x38 */) = float(fpu7);
    // 00430e26  8b45f0                 -mov eax, dword ptr [ebp - 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 00430e29  d9cb                   +fxch st(3)
    
    // 00430e2b  d95dcc                 +fstp dword ptr [ebp - 0x34]
    app->getMemory<float>(cpu.ebp + x86::reg32(-52) /* -0x34 */) = float(fpu9);
    // 00430e2e  d9ca                   +fxch st(2)
    
    // 00430e30  d8a098000000           +fsub dword ptr [eax + 0x98]
    x86::Float fpu11 = cpu.fpu.sub(fpu5, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(152) /* 0x98 */)));
    // 00430e36  d9c9                   +fxch st(1)
    
    // 00430e38  d95de4                 +fstp dword ptr [ebp - 0x1c]
    app->getMemory<float>(cpu.ebp + x86::reg32(-28) /* -0x1c */) = float(fpu3);
    // 00430e3b  d95dd8                 +fstp dword ptr [ebp - 0x28]
    app->getMemory<float>(cpu.ebp + x86::reg32(-40) /* -0x28 */) = float(fpu11);
    // 00430e3e  d85dd8                 +fcomp dword ptr [ebp - 0x28]
    cpu.fpu.compare(fpu10, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-40) /* -0x28 */)));
    // 00430e41  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00430e43  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 00430e44  7308                   -jae 0x430e4e
    if (!cpu.flags.cf)
    {
        goto L_0x00430e4e;
    }
    // 00430e46  8b45d8                 -mov eax, dword ptr [ebp - 0x28]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-40) /* -0x28 */);
    // 00430e49  8945d0                 -mov dword ptr [ebp - 0x30], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-48) /* -0x30 */) = cpu.eax;
    // 00430e4c  eb08                   -jmp 0x430e56
    goto L_0x00430e56;
L_0x00430e4e:
    // 00430e4e  d945d8                 +fld dword ptr [ebp - 0x28]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu12 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-40) /* -0x28 */));
    // 00430e51  d9e0                   +fchs 
    x86::Float fpu13 = -fpu12;
    // 00430e53  d95dd0                 +fstp dword ptr [ebp - 0x30]
    app->getMemory<float>(cpu.ebp + x86::reg32(-48) /* -0x30 */) = float(fpu13);
    }
L_0x00430e56:
    // 00430e56  8b45d0                 -mov eax, dword ptr [ebp - 0x30]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-48) /* -0x30 */);
    // 00430e59  8945e0                 -mov dword ptr [ebp - 0x20], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-32) /* -0x20 */) = cpu.eax;
    // 00430e5c  8b45f0                 -mov eax, dword ptr [ebp - 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 00430e5f  d945cc                 +fld dword ptr [ebp - 0x34]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu14 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-52) /* -0x34 */));
    // 00430e62  d8a0a0000000           +fsub dword ptr [eax + 0xa0]
    x86::Float fpu15 = cpu.fpu.sub(fpu14, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(160) /* 0xa0 */)));
    // 00430e68  d9ee                   +fldz 
    x86::Float fpu16 = 0.0;
    // 00430e6a  d9c9                   +fxch st(1)
    
    // 00430e6c  d95ddc                 +fstp dword ptr [ebp - 0x24]
    app->getMemory<float>(cpu.ebp + x86::reg32(-36) /* -0x24 */) = float(fpu15);
    // 00430e6f  d85ddc                 +fcomp dword ptr [ebp - 0x24]
    cpu.fpu.compare(fpu16, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-36) /* -0x24 */)));
    // 00430e72  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00430e74  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 00430e75  7308                   -jae 0x430e7f
    if (!cpu.flags.cf)
    {
        goto L_0x00430e7f;
    }
    // 00430e77  8b45dc                 -mov eax, dword ptr [ebp - 0x24]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-36) /* -0x24 */);
    // 00430e7a  8945e8                 -mov dword ptr [ebp - 0x18], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-24) /* -0x18 */) = cpu.eax;
    // 00430e7d  eb08                   -jmp 0x430e87
    goto L_0x00430e87;
L_0x00430e7f:
    // 00430e7f  d945dc                 +fld dword ptr [ebp - 0x24]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu17 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-36) /* -0x24 */));
    // 00430e82  d9e0                   +fchs 
    x86::Float fpu18 = -fpu17;
    // 00430e84  d95de8                 +fstp dword ptr [ebp - 0x18]
    app->getMemory<float>(cpu.ebp + x86::reg32(-24) /* -0x18 */) = float(fpu18);
    }
L_0x00430e87:
    // 00430e87  d945e0                 +fld dword ptr [ebp - 0x20]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu19 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-32) /* -0x20 */));
    // 00430e8a  d85de8                 +fcomp dword ptr [ebp - 0x18]
    cpu.fpu.compare(fpu19, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-24) /* -0x18 */)));
    // 00430e8d  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00430e8f  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 00430e90  760e                   -jbe 0x430ea0
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x00430ea0;
    }
    // 00430e92  d945e8                 +fld dword ptr [ebp - 0x18]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu20 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-24) /* -0x18 */));
    // 00430e95  d80d4c745300           +fmul dword ptr [0x53744c]
    x86::Float fpu21 = cpu.fpu.mul(fpu20, x86::Float(app->getMemory<float>(x86::reg32(5469260) /* 0x53744c */)));
    // 00430e9b  d845e0                 +fadd dword ptr [ebp - 0x20]
    x86::Float fpu22 = cpu.fpu.add(fpu21, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-32) /* -0x20 */)));
    cpu.fpu.count += 1;
    cpu.fpu.st(0) = fpu22;
    }
    // 00430e9e  eb0c                   -jmp 0x430eac
    goto L_0x00430eac;
L_0x00430ea0:
    // 00430ea0  d945e0                 +fld dword ptr [ebp - 0x20]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu23 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-32) /* -0x20 */));
    // 00430ea3  d80d4c745300           +fmul dword ptr [0x53744c]
    x86::Float fpu24 = cpu.fpu.mul(fpu23, x86::Float(app->getMemory<float>(x86::reg32(5469260) /* 0x53744c */)));
    // 00430ea9  d845e8                 +fadd dword ptr [ebp - 0x18]
    x86::Float fpu25 = cpu.fpu.add(fpu24, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-24) /* -0x18 */)));
    cpu.fpu.count += 1;
    cpu.fpu.st(0) = fpu25;
    }
L_0x00430eac:
    // 00430eac  d95dd4                 +fstp dword ptr [ebp - 0x2c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu26 = cpu.fpu.st(0);
    app->getMemory<float>(cpu.ebp + x86::reg32(-44) /* -0x2c */) = float(fpu26);
    // 00430eaf  8b45f0                 -mov eax, dword ptr [ebp - 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 00430eb2  d945e4                 +fld dword ptr [ebp - 0x1c]
    x86::Float fpu27 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-28) /* -0x1c */));
    // 00430eb5  d88020010000           +fadd dword ptr [eax + 0x120]
    x86::Float fpu28 = cpu.fpu.add(fpu27, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(288) /* 0x120 */)));
    // 00430ebb  d85dd4                 +fcomp dword ptr [ebp - 0x2c]
    cpu.fpu.compare(fpu28, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-44) /* -0x2c */)));
    // 00430ebe  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00430ec0  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    cpu.fpu.count -= 1;
    }
    // 00430ec1  0f86e2010000           -jbe 0x4310a9
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x004310a9;
    }
    // 00430ec7  d945e4                 +fld dword ptr [ebp - 0x1c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu29 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-28) /* -0x1c */));
    // 00430eca  d80d50745300           +fmul dword ptr [0x537450]
    x86::Float fpu30 = cpu.fpu.mul(fpu29, x86::Float(app->getMemory<float>(x86::reg32(5469264) /* 0x537450 */)));
    // 00430ed0  8b45f0                 -mov eax, dword ptr [ebp - 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 00430ed3  d8985c010000           +fcomp dword ptr [eax + 0x15c]
    cpu.fpu.compare(fpu30, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(348) /* 0x15c */)));
    // 00430ed9  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00430edb  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 00430edc  0f86c7010000           -jbe 0x4310a9
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x004310a9;
    }
    // 00430ee2  8d45ac                 -lea eax, [ebp - 0x54]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-84) /* -0x54 */);
    // 00430ee5  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00430ee6  8d55c4                 -lea edx, [ebp - 0x3c]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-60) /* -0x3c */);
    // 00430ee9  8b45f0                 -mov eax, dword ptr [ebp - 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 00430eec  ff75e4                 -push dword ptr [ebp - 0x1c]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-28) /* -0x1c */);
    cpu.esp -= 4;
    // 00430eef  e8ecfdffff             -call 0x430ce0
    cpu.esp -= 4;
    sub_430ce0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00430ef4  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00430ef6  0f84ad010000           -je 0x4310a9
    if (cpu.flags.zf)
    {
        goto L_0x004310a9;
    }
    // 00430efc  8b55ec                 -mov edx, dword ptr [ebp - 0x14]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */);
    // 00430eff  8b45f0                 -mov eax, dword ptr [ebp - 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 00430f02  e849c4feff             -call 0x41d350
    cpu.esp -= 4;
    sub_41d350(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00430f07  d945b4                 -fld dword ptr [ebp - 0x4c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu31 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-76) /* -0x4c */));
    // 00430f0a  dc0d54745300           -fmul qword ptr [0x537454]
    x86::Float fpu32 = cpu.fpu.mul(fpu31, x86::Float(app->getMemory<double>(x86::reg32(5469268) /* 0x537454 */)));
    // 00430f10  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 00430f12  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 00430f15  db1c24                 -fistp dword ptr [esp]
    app->getMemory<x86::reg32>(cpu.esp) = x86::reg32(cpu.fpu.toInteger<x86::sreg32>(fpu32));
    // 00430f18  58                     -pop eax
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00430f19  d945ac                 -fld dword ptr [ebp - 0x54]
    x86::Float fpu33 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-84) /* -0x54 */));
    // 00430f1c  dc0d54745300           -fmul qword ptr [0x537454]
    x86::Float fpu34 = cpu.fpu.mul(fpu33, x86::Float(app->getMemory<double>(x86::reg32(5469268) /* 0x537454 */)));
    // 00430f22  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 00430f24  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00430f26  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 00430f29  db1c24                 -fistp dword ptr [esp]
    app->getMemory<x86::reg32>(cpu.esp) = x86::reg32(cpu.fpu.toInteger<x86::sreg32>(fpu34));
    // 00430f2c  58                     -pop eax
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00430f2d  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 00430f2f  8b45f0                 -mov eax, dword ptr [ebp - 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    }
    // 00430f32  e809050400             -call 0x471440
    cpu.esp -= 4;
    nfs3hp::controls::bumpJolt(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00430f37  83fe01                 +cmp esi, 1
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
    // 00430f3a  0f85c9000000           -jne 0x431009
    if (!cpu.flags.zf)
    {
        goto L_0x00431009;
    }
    // 00430f40  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
    // 00430f42  8b45f0                 -mov eax, dword ptr [ebp - 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 00430f45  895d98                 -mov dword ptr [ebp - 0x68], ebx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-104) /* -0x68 */) = cpu.ebx;
    // 00430f48  d98098000000           -fld dword ptr [eax + 0x98]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu35 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(152) /* 0x98 */));
    // 00430f4e  d865c4                 -fsub dword ptr [ebp - 0x3c]
    x86::Float fpu36 = cpu.fpu.sub(fpu35, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-60) /* -0x3c */)));
    // 00430f51  d95d94                 -fstp dword ptr [ebp - 0x6c]
    app->getMemory<float>(cpu.ebp + x86::reg32(-108) /* -0x6c */) = float(fpu36);
    // 00430f54  d980a0000000           -fld dword ptr [eax + 0xa0]
    x86::Float fpu37 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(160) /* 0xa0 */));
    // 00430f5a  d865cc                 -fsub dword ptr [ebp - 0x34]
    x86::Float fpu38 = cpu.fpu.sub(fpu37, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-52) /* -0x34 */)));
    // 00430f5d  8d4594                 -lea eax, [ebp - 0x6c]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-108) /* -0x6c */);
    // 00430f60  d95d9c                 -fstp dword ptr [ebp - 0x64]
    app->getMemory<float>(cpu.ebp + x86::reg32(-100) /* -0x64 */) = float(fpu38);
    }
    // 00430f63  e888630600             -call 0x4972f0
    cpu.esp -= 4;
    sub_4972f0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00430f68  8d45a0                 -lea eax, [ebp - 0x60]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-96) /* -0x60 */);
    // 00430f6b  8d5594                 -lea edx, [ebp - 0x6c]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-108) /* -0x6c */);
    // 00430f6e  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00430f6f  8d4da0                 -lea ecx, [ebp - 0x60]
    cpu.ecx = x86::reg32(cpu.ebp + x86::reg32(-96) /* -0x60 */);
    // 00430f72  8d5da0                 -lea ebx, [ebp - 0x60]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-96) /* -0x60 */);
    // 00430f75  ff75e4                 -push dword ptr [ebp - 0x1c]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-28) /* -0x1c */);
    cpu.esp -= 4;
    // 00430f78  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 00430f7a  ddd8                   -fstp st(0)
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu39 = cpu.fpu.st(0);
    x86::Float fpu40 = x86::Float(fpu39);
    cpu.fpu.count -= 1;
    }
    // 00430f7c  e8cff00a00             -call 0x4e0050
    cpu.esp -= 4;
    sub_4e0050(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00430f81  8d55c4                 -lea edx, [ebp - 0x3c]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-60) /* -0x3c */);
    // 00430f84  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 00430f86  e825f00a00             -call 0x4dffb0
    cpu.esp -= 4;
    sub_4dffb0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00430f8b  8d5da0                 -lea ebx, [ebp - 0x60]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-96) /* -0x60 */);
    // 00430f8e  8d5594                 -lea edx, [ebp - 0x6c]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-108) /* -0x6c */);
    // 00430f91  8b45f0                 -mov eax, dword ptr [ebp - 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 00430f94  6a00                   -push 0
    app->getMemory<x86::reg32>(cpu.esp-4) = 0 /*0x0*/;
    cpu.esp -= 4;
    // 00430f96  e845e0ffff             -call 0x42efe0
    cpu.esp -= 4;
    nfs3hp::raceload::boxHitsWall(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00430f9b  8b45f0                 -mov eax, dword ptr [ebp - 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 00430f9e  f78068010000ffffff7f   +test dword ptr [eax + 0x168], 0x7fffffff
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(app->getMemory<x86::reg32>(cpu.eax + x86::reg32(360) /* 0x168 */) & 2147483647 /*0x7fffffff*/));
    // 00430fa8  7442                   -je 0x430fec
    if (cpu.flags.zf)
    {
        goto L_0x00430fec;
    }
    // 00430faa  d98068010000           -fld dword ptr [eax + 0x168]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu41 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(360) /* 0x168 */));
    // 00430fb0  c780700100000a000600   -mov dword ptr [eax + 0x170], 0x6000a
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(368) /* 0x170 */) = 393226 /*0x6000a*/;
    // 00430fba  d80d5c745300           -fmul dword ptr [0x53745c]
    x86::Float fpu42 = cpu.fpu.mul(fpu41, x86::Float(app->getMemory<float>(x86::reg32(5469276) /* 0x53745c */)));
    // 00430fc0  d98098000000           -fld dword ptr [eax + 0x98]
    x86::Float fpu43 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(152) /* 0x98 */));
    // 00430fc6  d9809c000000           -fld dword ptr [eax + 0x9c]
    x86::Float fpu44 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(156) /* 0x9c */));
    // 00430fcc  d980a0000000           -fld dword ptr [eax + 0xa0]
    x86::Float fpu45 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(160) /* 0xa0 */));
    // 00430fd2  d9ca                   -fxch st(2)
    
    // 00430fd4  d99878010000           -fstp dword ptr [eax + 0x178]
    app->getMemory<float>(cpu.eax + x86::reg32(376) /* 0x178 */) = float(fpu43);
    // 00430fda  d9987c010000           -fstp dword ptr [eax + 0x17c]
    app->getMemory<float>(cpu.eax + x86::reg32(380) /* 0x17c */) = float(fpu44);
    // 00430fe0  d99880010000           -fstp dword ptr [eax + 0x180]
    app->getMemory<float>(cpu.eax + x86::reg32(384) /* 0x180 */) = float(fpu45);
    // 00430fe6  d99868010000           -fstp dword ptr [eax + 0x168]
    app->getMemory<float>(cpu.eax + x86::reg32(360) /* 0x168 */) = float(fpu42);
    }
L_0x00430fec:
    // 00430fec  8b45f0                 -mov eax, dword ptr [ebp - 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 00430fef  f6800002000002         +test byte ptr [eax + 0x200], 2
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(cpu.eax + x86::reg32(512) /* 0x200 */) & 2 /*0x2*/));
    // 00430ff6  0f84ad000000           -je 0x4310a9
    if (cpu.flags.zf)
    {
        goto L_0x004310a9;
    }
    // 00430ffc  e81f51fdff             -call 0x406120
    cpu.esp -= 4;
    sub_406120(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00431001  ff45ec                 +inc dword ptr [ebp - 0x14]
    {
        auto tmp = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */);
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 00431004  e9b7fdffff             -jmp 0x430dc0
    goto L_0x00430dc0;
L_0x00431009:
    // 00431009  83fe02                 +cmp esi, 2
    {
        x86::reg32 tmp1 = cpu.esi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(2 /*0x2*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0043100c  7550                   -jne 0x43105e
    if (!cpu.flags.zf)
    {
        goto L_0x0043105e;
    }
    // 0043100e  8b45f0                 -mov eax, dword ptr [ebp - 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 00431011  d980b8000000           +fld dword ptr [eax + 0xb8]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu46 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(184) /* 0xb8 */));
    // 00431017  dc1d64745300           +fcomp qword ptr [0x537464]
    cpu.fpu.compare(fpu46, x86::Float(app->getMemory<double>(x86::reg32(5469284) /* 0x537464 */)));
    // 0043101d  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 0043101f  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 00431020  0f8683000000           -jbe 0x4310a9
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x004310a9;
    }
    // 00431026  8b45f0                 -mov eax, dword ptr [ebp - 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 00431029  c780700100000b000600   -mov dword ptr [eax + 0x170], 0x6000b
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(368) /* 0x170 */) = 393227 /*0x6000b*/;
    // 00431033  c7806c01000000000000   -mov dword ptr [eax + 0x16c], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(364) /* 0x16c */) = 0 /*0x0*/;
    // 0043103d  8db878010000           -lea edi, [eax + 0x178]
    cpu.edi = x86::reg32(cpu.eax + x86::reg32(376) /* 0x178 */);
    // 00431043  8db098000000           -lea esi, [eax + 0x98]
    cpu.esi = x86::reg32(cpu.eax + x86::reg32(152) /* 0x98 */);
    // 00431049  c7806801000000007041   -mov dword ptr [eax + 0x168], 0x41700000
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(360) /* 0x168 */) = 1097859072 /*0x41700000*/;
    // 00431053  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00431054  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00431055  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00431056  ff45ec                 +inc dword ptr [ebp - 0x14]
    {
        auto tmp = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */);
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 00431059  e962fdffff             -jmp 0x430dc0
    goto L_0x00430dc0;
L_0x0043105e:
    // 0043105e  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 00431060  7d47                   -jge 0x4310a9
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004310a9;
    }
    // 00431062  8b45f0                 -mov eax, dword ptr [ebp - 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 00431065  c7806801000000007041   -mov dword ptr [eax + 0x168], 0x41700000
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(360) /* 0x168 */) = 1097859072 /*0x41700000*/;
    // 0043106f  c780700100000a000600   -mov dword ptr [eax + 0x170], 0x6000a
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(368) /* 0x170 */) = 393226 /*0x6000a*/;
    // 00431079  c7806c01000000000000   -mov dword ptr [eax + 0x16c], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(364) /* 0x16c */) = 0 /*0x0*/;
    // 00431083  d98098000000           +fld dword ptr [eax + 0x98]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu47 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(152) /* 0x98 */));
    // 00431089  d9809c000000           +fld dword ptr [eax + 0x9c]
    x86::Float fpu48 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(156) /* 0x9c */));
    // 0043108f  d980a0000000           +fld dword ptr [eax + 0xa0]
    x86::Float fpu49 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(160) /* 0xa0 */));
    // 00431095  d9ca                   +fxch st(2)
    
    // 00431097  d99878010000           +fstp dword ptr [eax + 0x178]
    app->getMemory<float>(cpu.eax + x86::reg32(376) /* 0x178 */) = float(fpu47);
    // 0043109d  d9987c010000           +fstp dword ptr [eax + 0x17c]
    app->getMemory<float>(cpu.eax + x86::reg32(380) /* 0x17c */) = float(fpu48);
    // 004310a3  d99880010000           +fstp dword ptr [eax + 0x180]
    app->getMemory<float>(cpu.eax + x86::reg32(384) /* 0x180 */) = float(fpu49);
    }
L_0x004310a9:
    // 004310a9  ff45ec                 +inc dword ptr [ebp - 0x14]
    {
        auto tmp = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */);
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 004310ac  e90ffdffff             -jmp 0x430dc0
    goto L_0x00430dc0;
L_0x004310b1:
    // 004310b1  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004310b3  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004310b4  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004310b5  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004310b6  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004310b7  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004310b8  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004310b9  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 */
void Application::sub_4310c0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004310c0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004310c1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004310c2  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004310c3  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004310c4  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004310c6  83ec1c                 -sub esp, 0x1c
    (cpu.esp) -= x86::reg32(x86::sreg32(28 /*0x1c*/));
    // 004310c9  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 004310cb  a1bc375500             -mov eax, dword ptr [0x5537bc]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5584828) /* 0x5537bc */);
    // 004310d0  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
    // 004310d2  890c8510fe5e00         -mov dword ptr [eax*4 + 0x5efe10], ecx
    app->getMemory<x86::reg32>(x86::reg32(6225424) /* 0x5efe10 */ + cpu.eax * 4) = cpu.ecx;
L_0x004310d9:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004310d9  8b15bc375500           -mov edx, dword ptr [0x5537bc]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5584828) /* 0x5537bc */);
    // 004310df  39d3                   +cmp ebx, edx
    {
        x86::reg32 tmp1 = cpu.ebx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.edx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004310e1  0f8dcd000000           -jge 0x4311b4
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004311b4;
    }
    // 004310e7  d9ee                   +fldz 
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = 0.0;
    // 004310e9  d98120010000           +fld dword ptr [ecx + 0x120]
    x86::Float fpu2 = x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(288) /* 0x120 */));
    // 004310ef  8b149d10fe5e00         -mov edx, dword ptr [ebx*4 + 0x5efe10]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(6225424) /* 0x5efe10 */ + cpu.ebx * 4);
    // 004310f6  d981a0000000           +fld dword ptr [ecx + 0xa0]
    x86::Float fpu3 = x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(160) /* 0xa0 */));
    // 004310fc  d9c9                   +fxch st(1)
    
    // 004310fe  d88220010000           +fadd dword ptr [edx + 0x120]
    x86::Float fpu4 = cpu.fpu.add(fpu2, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(288) /* 0x120 */)));
    // 00431104  d9c9                   +fxch st(1)
    
    // 00431106  d8a2a0000000           +fsub dword ptr [edx + 0xa0]
    x86::Float fpu5 = cpu.fpu.sub(fpu3, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(160) /* 0xa0 */)));
    // 0043110c  d9c9                   +fxch st(1)
    
    // 0043110e  d95df0                 +fstp dword ptr [ebp - 0x10]
    app->getMemory<float>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = float(fpu4);
    // 00431111  d95dfc                 +fstp dword ptr [ebp - 4]
    app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = float(fpu5);
    // 00431114  d85dfc                 +fcomp dword ptr [ebp - 4]
    cpu.fpu.compare(fpu1, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 00431117  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00431119  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 0043111a  7308                   -jae 0x431124
    if (!cpu.flags.cf)
    {
        goto L_0x00431124;
    }
    // 0043111c  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 0043111f  8945e8                 -mov dword ptr [ebp - 0x18], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-24) /* -0x18 */) = cpu.eax;
    // 00431122  eb08                   -jmp 0x43112c
    goto L_0x0043112c;
L_0x00431124:
    // 00431124  d945fc                 +fld dword ptr [ebp - 4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu6 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */));
    // 00431127  d9e0                   +fchs 
    x86::Float fpu7 = -fpu6;
    // 00431129  d95de8                 +fstp dword ptr [ebp - 0x18]
    app->getMemory<float>(cpu.ebp + x86::reg32(-24) /* -0x18 */) = float(fpu7);
    }
L_0x0043112c:
    // 0043112c  d945e8                 +fld dword ptr [ebp - 0x18]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu8 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-24) /* -0x18 */));
    // 0043112f  d85df0                 +fcomp dword ptr [ebp - 0x10]
    cpu.fpu.compare(fpu8, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-16) /* -0x10 */)));
    // 00431132  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00431134  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 00431135  0f8373000000           -jae 0x4311ae
    if (!cpu.flags.cf)
    {
        goto L_0x004311ae;
    }
    // 0043113b  d98198000000           +fld dword ptr [ecx + 0x98]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu9 = x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(152) /* 0x98 */));
    // 00431141  d8a298000000           +fsub dword ptr [edx + 0x98]
    x86::Float fpu10 = cpu.fpu.sub(fpu9, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(152) /* 0x98 */)));
    // 00431147  d9ee                   +fldz 
    x86::Float fpu11 = 0.0;
    // 00431149  d9c9                   +fxch st(1)
    
    // 0043114b  d95de4                 +fstp dword ptr [ebp - 0x1c]
    app->getMemory<float>(cpu.ebp + x86::reg32(-28) /* -0x1c */) = float(fpu10);
    // 0043114e  d85de4                 +fcomp dword ptr [ebp - 0x1c]
    cpu.fpu.compare(fpu11, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-28) /* -0x1c */)));
    // 00431151  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00431153  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 00431154  7308                   -jae 0x43115e
    if (!cpu.flags.cf)
    {
        goto L_0x0043115e;
    }
    // 00431156  8b45e4                 -mov eax, dword ptr [ebp - 0x1c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-28) /* -0x1c */);
    // 00431159  8945f4                 -mov dword ptr [ebp - 0xc], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.eax;
    // 0043115c  eb08                   -jmp 0x431166
    goto L_0x00431166;
L_0x0043115e:
    // 0043115e  d945e4                 +fld dword ptr [ebp - 0x1c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu12 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-28) /* -0x1c */));
    // 00431161  d9e0                   +fchs 
    x86::Float fpu13 = -fpu12;
    // 00431163  d95df4                 +fstp dword ptr [ebp - 0xc]
    app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */) = float(fpu13);
    }
L_0x00431166:
    // 00431166  d945f4                 +fld dword ptr [ebp - 0xc]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu14 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */));
    // 00431169  d85df0                 +fcomp dword ptr [ebp - 0x10]
    cpu.fpu.compare(fpu14, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-16) /* -0x10 */)));
    // 0043116c  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 0043116e  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 0043116f  733d                   -jae 0x4311ae
    if (!cpu.flags.cf)
    {
        goto L_0x004311ae;
    }
    // 00431171  d9819c000000           +fld dword ptr [ecx + 0x9c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu15 = x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(156) /* 0x9c */));
    // 00431177  d8a29c000000           +fsub dword ptr [edx + 0x9c]
    x86::Float fpu16 = cpu.fpu.sub(fpu15, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(156) /* 0x9c */)));
    // 0043117d  d9ee                   +fldz 
    x86::Float fpu17 = 0.0;
    // 0043117f  d9c9                   +fxch st(1)
    
    // 00431181  d95dec                 +fstp dword ptr [ebp - 0x14]
    app->getMemory<float>(cpu.ebp + x86::reg32(-20) /* -0x14 */) = float(fpu16);
    // 00431184  d85dec                 +fcomp dword ptr [ebp - 0x14]
    cpu.fpu.compare(fpu17, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-20) /* -0x14 */)));
    // 00431187  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00431189  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 0043118a  7308                   -jae 0x431194
    if (!cpu.flags.cf)
    {
        goto L_0x00431194;
    }
    // 0043118c  8b45ec                 -mov eax, dword ptr [ebp - 0x14]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */);
    // 0043118f  8945f8                 -mov dword ptr [ebp - 8], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.eax;
    // 00431192  eb08                   -jmp 0x43119c
    goto L_0x0043119c;
L_0x00431194:
    // 00431194  d945ec                 +fld dword ptr [ebp - 0x14]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu18 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-20) /* -0x14 */));
    // 00431197  d9e0                   +fchs 
    x86::Float fpu19 = -fpu18;
    // 00431199  d95df8                 +fstp dword ptr [ebp - 8]
    app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = float(fpu19);
    }
L_0x0043119c:
    // 0043119c  d945f8                 +fld dword ptr [ebp - 8]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu20 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */));
    // 0043119f  d85df0                 +fcomp dword ptr [ebp - 0x10]
    cpu.fpu.compare(fpu20, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-16) /* -0x10 */)));
    // 004311a2  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 004311a4  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 004311a5  7307                   -jae 0x4311ae
    if (!cpu.flags.cf)
    {
        goto L_0x004311ae;
    }
    // 004311a7  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004311a9  e8d2faffff             -call 0x430c80
    cpu.esp -= 4;
    sub_430c80(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x004311ae:
    // 004311ae  43                     +inc ebx
    {
        x86::reg32& tmp = cpu.ebx;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 004311af  e925ffffff             -jmp 0x4310d9
    goto L_0x004310d9;
L_0x004311b4:
    // 004311b4  8d4a01                 -lea ecx, [edx + 1]
    cpu.ecx = x86::reg32(cpu.edx + x86::reg32(1) /* 0x1 */);
    // 004311b7  890dbc375500           -mov dword ptr [0x5537bc], ecx
    app->getMemory<x86::reg32>(x86::reg32(5584828) /* 0x5537bc */) = cpu.ecx;
    // 004311bd  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004311bf  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004311c0  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004311c1  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004311c2  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004311c3  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 */
void Application::sub_4311d0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004311d0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004311d1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004311d2  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004311d3  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004311d4  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004311d5  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004311d7  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004311d9  8b9874010000           -mov ebx, dword ptr [eax + 0x174]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(372) /* 0x174 */);
    // 004311df  b901000000             -mov ecx, 1
    cpu.ecx = 1 /*0x1*/;
    // 004311e4  85db                   +test ebx, ebx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & cpu.ebx));
    // 004311e6  7e0a                   -jle 0x4311f2
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004311f2;
    }
    // 004311e8  89de                   -mov esi, ebx
    cpu.esi = cpu.ebx;
    // 004311ea  29ce                   -sub esi, ecx
    (cpu.esi) -= x86::reg32(x86::sreg32(cpu.ecx));
    // 004311ec  89b074010000           -mov dword ptr [eax + 0x174], esi
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(372) /* 0x174 */) = cpu.esi;
L_0x004311f2:
    // 004311f2  80ba8800000000         +cmp byte ptr [edx + 0x88], 0
    {
        x86::reg8 tmp1 = app->getMemory<x86::reg8>(cpu.edx + x86::reg32(136) /* 0x88 */);
        x86::reg8 tmp2 = x86::reg8(x86::sreg8(0 /*0x0*/));
        x86::reg8 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 7);
        cpu.flags.of ^= 1 & (result >> 7);
        cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
        cpu.set_szp(result);
    }
    // 004311f9  754c                   -jne 0x431247
    if (!cpu.flags.zf)
    {
        goto L_0x00431247;
    }
    // 004311fb  80ba8900000000         +cmp byte ptr [edx + 0x89], 0
    {
        x86::reg8 tmp1 = app->getMemory<x86::reg8>(cpu.edx + x86::reg32(137) /* 0x89 */);
        x86::reg8 tmp2 = x86::reg8(x86::sreg8(0 /*0x0*/));
        x86::reg8 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 7);
        cpu.flags.of ^= 1 & (result >> 7);
        cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
        cpu.set_szp(result);
    }
    // 00431202  7443                   -je 0x431247
    if (cpu.flags.zf)
    {
        goto L_0x00431247;
    }
    // 00431204  83ba7401000000         +cmp dword ptr [edx + 0x174], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(372) /* 0x174 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0043120b  7404                   -je 0x431211
    if (cpu.flags.zf)
    {
        goto L_0x00431211;
    }
    // 0043120d  31c9                   +xor ecx, ecx
    cpu.clear_co();
    cpu.set_szp((cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx))));
    // 0043120f  eb0b                   -jmp 0x43121c
    goto L_0x0043121c;
L_0x00431211:
    // 00431211  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    // 00431213  7407                   -je 0x43121c
    if (cpu.flags.zf)
    {
        goto L_0x0043121c;
    }
    // 00431215  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 00431217  e8a4feffff             -call 0x4310c0
    cpu.esp -= 4;
    sub_4310c0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x0043121c:
    // 0043121c  f6828801000040         +test byte ptr [edx + 0x188], 0x40
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(cpu.edx + x86::reg32(392) /* 0x188 */) & 64 /*0x40*/));
    // 00431223  740b                   -je 0x431230
    if (cpu.flags.zf)
    {
        goto L_0x00431230;
    }
    // 00431225  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    // 00431227  7407                   -je 0x431230
    if (cpu.flags.zf)
    {
        goto L_0x00431230;
    }
    // 00431229  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 0043122b  e870fbffff             -call 0x430da0
    cpu.esp -= 4;
    sub_430da0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00431230:
    // 00431230  f6828801000080         +test byte ptr [edx + 0x188], 0x80
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(cpu.edx + x86::reg32(392) /* 0x188 */) & 128 /*0x80*/));
    // 00431237  7407                   -je 0x431240
    if (cpu.flags.zf)
    {
        goto L_0x00431240;
    }
    // 00431239  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 0043123b  e870f2ffff             -call 0x4304b0
    cpu.esp -= 4;
    sub_4304b0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00431240:
    // 00431240  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 00431242  e8f9ee0600             -call 0x4a0140
    cpu.esp -= 4;
    sub_4a0140(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00431247:
    // 00431247  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00431248  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00431249  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043124a  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043124b  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043124c  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x00 0x00 0x00 */
void Application::sub_431250(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00431250  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00431251  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00431252  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00431254  29c8                   -sub eax, ecx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.ecx));
    // 00431256  0fafc0                 -imul eax, eax
    cpu.eax = x86::reg32(x86::sreg64(x86::sreg32(cpu.eax)) * x86::sreg64(x86::sreg32(cpu.eax)));
    // 00431259  2b550c                 -sub edx, dword ptr [ebp + 0xc]
    (cpu.edx) -= x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(12) /* 0xc */)));
    // 0043125c  0fafd2                 -imul edx, edx
    cpu.edx = x86::reg32(x86::sreg64(x86::sreg32(cpu.edx)) * x86::sreg64(x86::sreg32(cpu.edx)));
    // 0043125f  8b7510                 -mov esi, dword ptr [ebp + 0x10]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(16) /* 0x10 */);
    // 00431262  89d9                   -mov ecx, ebx
    cpu.ecx = cpu.ebx;
    // 00431264  29f1                   -sub ecx, esi
    (cpu.ecx) -= x86::reg32(x86::sreg32(cpu.esi));
    // 00431266  01c2                   -add edx, eax
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.eax));
    // 00431268  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 0043126a  0fafc1                 -imul eax, ecx
    cpu.eax = x86::reg32(x86::sreg64(x86::sreg32(cpu.eax)) * x86::sreg64(x86::sreg32(cpu.ecx)));
    // 0043126d  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 0043126f  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00431270  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00431271  c20800                 -ret 8
    cpu.esp += 4+8 /*0x8*/;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 */
void Application::sub_431280(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00431280  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00431281  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00431282  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00431283  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00431284  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00431286  83ec10                 -sub esp, 0x10
    (cpu.esp) -= x86::reg32(x86::sreg32(16 /*0x10*/));
    // 00431289  89c7                   -mov edi, eax
    cpu.edi = cpu.eax;
    // 0043128b  8955f8                 -mov dword ptr [ebp - 8], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.edx;
    // 0043128e  895df0                 -mov dword ptr [ebp - 0x10], ebx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = cpu.ebx;
    // 00431291  8b0dcc375500           -mov ecx, dword ptr [0x5537cc]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(5584844) /* 0x5537cc */);
    // 00431297  31d2                   +xor edx, edx
    cpu.clear_co();
    cpu.set_szp((cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx))));
    // 00431299  8b1dc8375500           -mov ebx, dword ptr [0x5537c8]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(5584840) /* 0x5537c8 */);
    // 0043129f  8955f4                 -mov dword ptr [ebp - 0xc], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.edx;
    // 004312a2  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004312a3  8b55f8                 -mov edx, dword ptr [ebp - 8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004312a6  8b0dc4375500           -mov ecx, dword ptr [0x5537c4]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(5584836) /* 0x5537c4 */);
    // 004312ac  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004312ad  8b5df0                 -mov ebx, dword ptr [ebp - 0x10]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 004312b0  be01000000             -mov esi, 1
    cpu.esi = 1 /*0x1*/;
    // 004312b5  e896ffffff             -call 0x431250
    cpu.esp -= 4;
    sub_431250(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004312ba  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 004312bd  eb08                   -jmp 0x4312c7
    goto L_0x004312c7;
L_0x004312bf:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004312bf  81fe67010000           +cmp esi, 0x167
    {
        x86::reg32 tmp1 = cpu.esi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(359 /*0x167*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004312c5  7d3d                   -jge 0x431304
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00431304;
    }
L_0x004312c7:
    // 004312c7  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004312c9  c1e004                 -shl eax, 4
    cpu.eax <<= 4 /*0x4*/ % 32;
    // 004312cc  8b90cc375500           -mov edx, dword ptr [eax + 0x5537cc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(5584844) /* 0x5537cc */);
    // 004312d2  8b5df0                 -mov ebx, dword ptr [ebp - 0x10]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 004312d5  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004312d6  8b88c8375500           -mov ecx, dword ptr [eax + 0x5537c8]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(5584840) /* 0x5537c8 */);
    // 004312dc  8b55f8                 -mov edx, dword ptr [ebp - 8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004312df  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004312e0  8b88c4375500           -mov ecx, dword ptr [eax + 0x5537c4]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(5584836) /* 0x5537c4 */);
    // 004312e6  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 004312e8  e863ffffff             -call 0x431250
    cpu.esp -= 4;
    sub_431250(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004312ed  3b45fc                 +cmp eax, dword ptr [ebp - 4]
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004312f0  7d0f                   -jge 0x431301
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00431301;
    }
    // 004312f2  8975f4                 -mov dword ptr [ebp - 0xc], esi
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.esi;
    // 004312f5  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 004312f8  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004312fa  7505                   -jne 0x431301
    if (!cpu.flags.zf)
    {
        goto L_0x00431301;
    }
    // 004312fc  be67010000             -mov esi, 0x167
    cpu.esi = 359 /*0x167*/;
L_0x00431301:
    // 00431301  46                     +inc esi
    {
        x86::reg32& tmp = cpu.esi;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 00431302  ebbb                   -jmp 0x4312bf
    goto L_0x004312bf;
L_0x00431304:
    // 00431304  8b45f4                 -mov eax, dword ptr [ebp - 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 00431307  c1e004                 -shl eax, 4
    cpu.eax <<= 4 /*0x4*/ % 32;
    // 0043130a  8b80d0375500           -mov eax, dword ptr [eax + 0x5537d0]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(5584848) /* 0x5537d0 */);
    // 00431310  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00431312  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00431313  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00431314  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00431315  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00431316  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 */
void Application::sub_431320(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00431320  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00431321  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00431322  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00431323  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00431324  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00431325  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00431327  83ec08                 -sub esp, 8
    (cpu.esp) -= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 0043132a  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 0043132c  8b1518ff5e00           -mov edx, dword ptr [0x5eff18]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(6225688) /* 0x5eff18 */);
    // 00431332  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 00431334  7407                   -je 0x43133d
    if (cpu.flags.zf)
    {
        goto L_0x0043133d;
    }
    // 00431336  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 00431338  e873000000             -call 0x4313b0
    cpu.esp -= 4;
    sub_4313b0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x0043133d:
    // 0043133d  8d4dfc                 -lea ecx, [ebp - 4]
    cpu.ecx = x86::reg32(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00431340  8d5df8                 -lea ebx, [ebp - 8]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 00431343  ba18ff5e00             -mov edx, 0x5eff18
    cpu.edx = 6225688 /*0x5eff18*/;
    // 00431348  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 0043134a  e881150b00             -call 0x4e28d0
    cpu.esp -= 4;
    nfs3hp::ea::openHandle(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0043134f  bb10000000             -mov ebx, 0x10
    cpu.ebx = 16 /*0x10*/;
    // 00431354  ba08ff5e00             -mov edx, 0x5eff08
    cpu.edx = 6225672 /*0x5eff08*/;
    // 00431359  a118ff5e00             -mov eax, dword ptr [0x5eff18]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(6225688) /* 0x5eff18 */);
    // 0043135e  e87d1a0b00             -call 0x4e2de0
    cpu.esp -= 4;
    nfs3hp::ea::readHandle(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00431363  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00431365  7428                   -je 0x43138f
    if (cpu.flags.zf)
    {
        goto L_0x0043138f;
    }
    // 00431367  bb04000000             -mov ebx, 4
    cpu.ebx = 4 /*0x4*/;
    // 0043136c  ba6c745300             -mov edx, 0x53746c
    cpu.edx = 5469292 /*0x53746c*/;
    // 00431371  b808ff5e00             -mov eax, 0x5eff08
    cpu.eax = 6225672 /*0x5eff08*/;
    // 00431376  e815a00b00             -call 0x4eb390
    cpu.esp -= 4;
    nfs3hp::watcom::strncmp(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0043137b  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0043137d  7510                   -jne 0x43138f
    if (!cpu.flags.zf)
    {
        goto L_0x0043138f;
    }
    // 0043137f  833d0cff5e000b         +cmp dword ptr [0x5eff0c], 0xb
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(6225676) /* 0x5eff0c */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(11 /*0xb*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00431386  7507                   -jne 0x43138f
    if (!cpu.flags.zf)
    {
        goto L_0x0043138f;
    }
    // 00431388  a118ff5e00             -mov eax, dword ptr [0x5eff18]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(6225688) /* 0x5eff18 */);
    // 0043138d  eb14                   -jmp 0x4313a3
    goto L_0x004313a3;
L_0x0043138f:
    // 0043138f  a118ff5e00             -mov eax, dword ptr [0x5eff18]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(6225688) /* 0x5eff18 */);
    // 00431394  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
    // 00431396  e8051a0b00             -call 0x4e2da0
    cpu.esp -= 4;
    nfs3hp::ea::closeHandle(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0043139b  891d18ff5e00           -mov dword ptr [0x5eff18], ebx
    app->getMemory<x86::reg32>(x86::reg32(6225688) /* 0x5eff18 */) = cpu.ebx;
    // 004313a1  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
L_0x004313a3:
    // 004313a3  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004313a5  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004313a6  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004313a7  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004313a8  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004313a9  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004313aa  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x40 0x00 0x8b 0xc9 */
void Application::sub_4313b0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004313b0  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004313b1  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004313b2  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004313b4  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 004313b6  e8e5190b00             -call 0x4e2da0
    cpu.esp -= 4;
    nfs3hp::ea::closeHandle(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004313bb  891518ff5e00           -mov dword ptr [0x5eff18], edx
    app->getMemory<x86::reg32>(x86::reg32(6225688) /* 0x5eff18 */) = cpu.edx;
    // 004313c1  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004313c2  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004313c3  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 */
void Application::sub_4313d0(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004313d0  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004313d1  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004313d3  a110ff5e00             -mov eax, dword ptr [0x5eff10]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(6225680) /* 0x5eff10 */);
    // 004313d8  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004313d9  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 */
void Application::sub_4313e0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004313e0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004313e1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004313e2  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004313e3  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004313e4  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004313e6  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 004313e8  89d6                   -mov esi, edx
    cpu.esi = cpu.edx;
    // 004313ea  ba10000000             -mov edx, 0x10
    cpu.edx = 16 /*0x10*/;
    // 004313ef  e86c1a0b00             -call 0x4e2e60
    cpu.esp -= 4;
    nfs3hp::ea::seekHandle(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004313f4  8b1d10ff5e00           -mov ebx, dword ptr [0x5eff10]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(6225680) /* 0x5eff10 */);
    // 004313fa  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 004313fc  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004313fe  83eb10                 -sub ebx, 0x10
    (cpu.ebx) -= x86::reg32(x86::sreg32(16 /*0x10*/));
    // 00431401  e8da190b00             -call 0x4e2de0
    cpu.esp -= 4;
    nfs3hp::ea::readHandle(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00431406  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 0043140b  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043140c  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043140d  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043140e  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043140f  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip  */
void Application::sub_431410(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00431410  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00431411  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00431413  a114ff5e00             -mov eax, dword ptr [0x5eff14]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(6225684) /* 0x5eff14 */);
    // 00431418  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00431419  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 */
void Application::sub_431420(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00431420  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00431421  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00431423  030490                 -add eax, dword ptr [eax + edx*4]
    (cpu.eax) += x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.eax + cpu.edx * 4)));
    // 00431426  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00431427  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 */
void Application::sub_431430(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00431430  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00431431  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00431432  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00431433  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00431434  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00431436  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00431438  833d98fd5e0000         +cmp dword ptr [0x5efd98], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(6225304) /* 0x5efd98 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0043143f  7f12                   -jg 0x431453
    if (!cpu.flags.zf && (cpu.flags.sf == cpu.flags.of))
    {
        goto L_0x00431453;
    }
    // 00431441  833d88fd5e0000         +cmp dword ptr [0x5efd88], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(6225288) /* 0x5efd88 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00431448  7f09                   -jg 0x431453
    if (!cpu.flags.zf && (cpu.flags.sf == cpu.flags.of))
    {
        goto L_0x00431453;
    }
    // 0043144a  833d94d46f0000         +cmp dword ptr [0x6fd494], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(7328916) /* 0x6fd494 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00431451  7407                   -je 0x43145a
    if (cpu.flags.zf)
    {
        goto L_0x0043145a;
    }
L_0x00431453:
    // 00431453  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00431455  e8e642fdff             -call 0x405740
    cpu.esp -= 4;
    sub_405740(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x0043145a:
    // 0043145a  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 0043145c  ff91fc050000           -call dword ptr [ecx + 0x5fc]
    cpu.ip = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(1532) /* 0x5fc */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00431462  a0a9c47900             -mov al, byte ptr [0x79c4a9]
    cpu.al = app->getMemory<x86::reg8>(x86::reg32(7980201) /* 0x79c4a9 */);
    // 00431467  888104050000           -mov byte ptr [ecx + 0x504], al
    app->getMemory<x86::reg8>(cpu.ecx + x86::reg32(1284) /* 0x504 */) = cpu.al;
    // 0043146d  a0aac47900             -mov al, byte ptr [0x79c4aa]
    cpu.al = app->getMemory<x86::reg8>(x86::reg32(7980202) /* 0x79c4aa */);
    // 00431472  888105050000           -mov byte ptr [ecx + 0x505], al
    app->getMemory<x86::reg8>(cpu.ecx + x86::reg32(1285) /* 0x505 */) = cpu.al;
    // 00431478  a1a5c47900             -mov eax, dword ptr [0x79c4a5]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(7980197) /* 0x79c4a5 */);
    // 0043147d  c1f818                 -sar eax, 0x18
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (24 /*0x18*/ % 32));
    // 00431480  8b91f0010000           -mov edx, dword ptr [ecx + 0x1f0]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(496) /* 0x1f0 */);
    // 00431486  898118050000           -mov dword ptr [ecx + 0x518], eax
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(1304) /* 0x518 */) = cpu.eax;
    // 0043148c  8d049500000000         -lea eax, [edx*4]
    cpu.eax = x86::reg32(cpu.edx * 4);
    // 00431493  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 00431495  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 00431498  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 0043149a  83bcc248d56f0001       +cmp dword ptr [edx + eax*8 + 0x6fd548], 1
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(7329096) /* 0x6fd548 */ + cpu.eax * 8);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1 /*0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004314a2  750f                   -jne 0x4314b3
    if (!cpu.flags.zf)
    {
        goto L_0x004314b3;
    }
    // 004314a4  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
    // 004314a6  8a810b050000           -mov al, byte ptr [ecx + 0x50b]
    cpu.al = app->getMemory<x86::reg8>(cpu.ecx + x86::reg32(1291) /* 0x50b */);
    // 004314ac  e85fe20500             -call 0x48f710
    cpu.esp -= 4;
    nfs3hp::controls::stepMenuChoiceOfThree(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004314b1  eb16                   -jmp 0x4314c9
    goto L_0x004314c9;
L_0x004314b3:
    // 004314b3  8b8128050000           -mov eax, dword ptr [ecx + 0x528]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(1320) /* 0x528 */);
    // 004314b9  8b5008                 -mov edx, dword ptr [eax + 8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 004314bc  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 004314be  8a810b050000           -mov al, byte ptr [ecx + 0x50b]
    cpu.al = app->getMemory<x86::reg8>(cpu.ecx + x86::reg32(1291) /* 0x50b */);
    // 004314c4  e817e20500             -call 0x48f6e0
    cpu.esp -= 4;
    nfs3hp::controls::stepMenuChoice(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x004314c9:
    // 004314c9  888106050000           -mov byte ptr [ecx + 0x506], al
    app->getMemory<x86::reg8>(cpu.ecx + x86::reg32(1286) /* 0x506 */) = cpu.al;
    // 004314cf  f605abc4790004         +test byte ptr [0x79c4ab], 4
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(x86::reg32(7980203) /* 0x79c4ab */) & 4 /*0x4*/));
    // 004314d6  7407                   -je 0x4314df
    if (cpu.flags.zf)
    {
        goto L_0x004314df;
    }
    // 004314d8  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 004314dd  eb02                   -jmp 0x4314e1
    goto L_0x004314e1;
L_0x004314df:
    // 004314df  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
L_0x004314e1:
    // 004314e1  8a15abc47900           -mov dl, byte ptr [0x79c4ab]
    cpu.dl = app->getMemory<x86::reg8>(x86::reg32(7980203) /* 0x79c4ab */);
    // 004314e7  88810d050000           -mov byte ptr [ecx + 0x50d], al
    app->getMemory<x86::reg8>(cpu.ecx + x86::reg32(1293) /* 0x50d */) = cpu.al;
    // 004314ed  f6c208                 +test dl, 8
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.dl & 8 /*0x8*/));
    // 004314f0  7407                   -je 0x4314f9
    if (cpu.flags.zf)
    {
        goto L_0x004314f9;
    }
    // 004314f2  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 004314f7  eb02                   -jmp 0x4314fb
    goto L_0x004314fb;
L_0x004314f9:
    // 004314f9  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
L_0x004314fb:
    // 004314fb  8a35abc47900           -mov dh, byte ptr [0x79c4ab]
    cpu.dh = app->getMemory<x86::reg8>(x86::reg32(7980203) /* 0x79c4ab */);
    // 00431501  88810e050000           -mov byte ptr [ecx + 0x50e], al
    app->getMemory<x86::reg8>(cpu.ecx + x86::reg32(1294) /* 0x50e */) = cpu.al;
    // 00431507  f6c680                 +test dh, 0x80
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.dh & 128 /*0x80*/));
    // 0043150a  7407                   -je 0x431513
    if (cpu.flags.zf)
    {
        goto L_0x00431513;
    }
    // 0043150c  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 00431511  eb02                   -jmp 0x431515
    goto L_0x00431515;
L_0x00431513:
    // 00431513  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
L_0x00431515:
    // 00431515  8a1dabc47900           -mov bl, byte ptr [0x79c4ab]
    cpu.bl = app->getMemory<x86::reg8>(x86::reg32(7980203) /* 0x79c4ab */);
    // 0043151b  888112050000           -mov byte ptr [ecx + 0x512], al
    app->getMemory<x86::reg8>(cpu.ecx + x86::reg32(1298) /* 0x512 */) = cpu.al;
    // 00431521  f6c340                 +test bl, 0x40
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.bl & 64 /*0x40*/));
    // 00431524  741f                   -je 0x431545
    if (cpu.flags.zf)
    {
        goto L_0x00431545;
    }
    // 00431526  8b8160060000           -mov eax, dword ptr [ecx + 0x660]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(1632) /* 0x660 */);
    // 0043152c  40                     -inc eax
    (cpu.eax)++;
    // 0043152d  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 0043152f  bb03000000             -mov ebx, 3
    cpu.ebx = 3 /*0x3*/;
    // 00431534  c1fa1f                 -sar edx, 0x1f
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (31 /*0x1f*/ % 32));
    // 00431537  898160060000           -mov dword ptr [ecx + 0x660], eax
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(1632) /* 0x660 */) = cpu.eax;
    // 0043153d  f7fb                   -idiv ebx
    {
        x86::sreg64 tmp = x86::sreg64(cpu.edx_eax);
        x86::sreg32 d = x86::sreg32(cpu.ebx);
        cpu.edx_eax = x86::reg64(tmp / d);
        cpu.edx = x86::reg32(tmp % d);
    }
    // 0043153f  899160060000           -mov dword ptr [ecx + 0x660], edx
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(1632) /* 0x660 */) = cpu.edx;
L_0x00431545:
    // 00431545  f605abc4790002         +test byte ptr [0x79c4ab], 2
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(x86::reg32(7980203) /* 0x79c4ab */) & 2 /*0x2*/));
    // 0043154c  7421                   -je 0x43156f
    if (cpu.flags.zf)
    {
        goto L_0x0043156f;
    }
    // 0043154e  f6810002000020         +test byte ptr [ecx + 0x200], 0x20
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(cpu.ecx + x86::reg32(512) /* 0x200 */) & 32 /*0x20*/));
    // 00431555  7411                   -je 0x431568
    if (cpu.flags.zf)
    {
        goto L_0x00431568;
    }
    // 00431557  ba01000000             -mov edx, 1
    cpu.edx = 1 /*0x1*/;
    // 0043155c  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 0043155e  e8bd3cfdff             -call 0x405220
    cpu.esp -= 4;
    sub_405220(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00431563  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00431564  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00431565  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00431566  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00431567  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x00431568:
    // 00431568  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 0043156a  e8917bffff             -call 0x429100
    cpu.esp -= 4;
    nfs3hp::racestart::resetCar(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x0043156f:
    // 0043156f  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00431570  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00431571  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00431572  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00431573  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_431580: native, nfs3hp::controls::clearJoysticks */

/* sub_4315a0: native, nfs3hp::controls::readJoysticks */

/* sub_431690: native, nfs3hp::controls::pollJoystick */

/* sub_4316c0: native, nfs3hp::controls::buttonHeld */

/* sub_4316f0: native, nfs3hp::controls::hatPointing */

/* sub_431740: native, nfs3hp::controls::axisAmount */

/* sub_4317d0: native, nfs3hp::controls::keyHeld */

/* sub_431800: native, nfs3hp::controls::controlHeld */

/* sub_431880: native, nfs3hp::controls::controlHeldNo */

/* sub_431885: native, nfs3hp::controls::controlHeldYes */

/* sub_43188d: native, nfs3hp::controls::controlHeldByKind */

/* sub_4318b0: native, nfs3hp::controls::noControl */

/* align: skip 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 */
void Application::sub_4318c0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004318c0  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004318c1  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004318c2  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004318c4  baffffffff             -mov edx, 0xffffffff
    cpu.edx = 4294967295 /*0xffffffff*/;
    // 004318c9  8915584e5500           -mov dword ptr [0x554e58], edx
    app->getMemory<x86::reg32>(x86::reg32(5590616) /* 0x554e58 */) = cpu.edx;
    // 004318cf  89155c4e5500           -mov dword ptr [0x554e5c], edx
    app->getMemory<x86::reg32>(x86::reg32(5590620) /* 0x554e5c */) = cpu.edx;
    // 004318d5  8915604e5500           -mov dword ptr [0x554e60], edx
    app->getMemory<x86::reg32>(x86::reg32(5590624) /* 0x554e60 */) = cpu.edx;
    // 004318db  8915644e5500           -mov dword ptr [0x554e64], edx
    app->getMemory<x86::reg32>(x86::reg32(5590628) /* 0x554e64 */) = cpu.edx;
    // 004318e1  8915684e5500           -mov dword ptr [0x554e68], edx
    app->getMemory<x86::reg32>(x86::reg32(5590632) /* 0x554e68 */) = cpu.edx;
    // 004318e7  89156c4e5500           -mov dword ptr [0x554e6c], edx
    app->getMemory<x86::reg32>(x86::reg32(5590636) /* 0x554e6c */) = cpu.edx;
    // 004318ed  8915544e5500           -mov dword ptr [0x554e54], edx
    app->getMemory<x86::reg32>(x86::reg32(5590612) /* 0x554e54 */) = cpu.edx;
    // 004318f3  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004318f4  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004318f5  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_431900: native, nfs3hp::graphics::setRenderState */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x90 */
void Application::sub_431aa0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00431aa0  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00431aa1  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00431aa2  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00431aa4  e817feffff             -call 0x4318c0
    cpu.esp -= 4;
    sub_4318c0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00431aa9  b80d000000             -mov eax, 0xd
    cpu.eax = 13 /*0xd*/;
    // 00431aae  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00431ab0  e84bfeffff             -call 0x431900
    cpu.esp -= 4;
    nfs3hp::graphics::setRenderState(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00431ab5  b815000000             -mov eax, 0x15
    cpu.eax = 21 /*0x15*/;
    // 00431aba  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00431abc  e83ffeffff             -call 0x431900
    cpu.esp -= 4;
    nfs3hp::graphics::setRenderState(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00431ac1  b868000000             -mov eax, 0x68
    cpu.eax = 104 /*0x68*/;
    // 00431ac6  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00431ac8  e833feffff             -call 0x431900
    cpu.esp -= 4;
    nfs3hp::graphics::setRenderState(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00431acd  b802000000             -mov eax, 2
    cpu.eax = 2 /*0x2*/;
    // 00431ad2  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00431ad4  e827feffff             -call 0x431900
    cpu.esp -= 4;
    nfs3hp::graphics::setRenderState(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00431ad9  b804000000             -mov eax, 4
    cpu.eax = 4 /*0x4*/;
    // 00431ade  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00431ae0  e81bfeffff             -call 0x431900
    cpu.esp -= 4;
    nfs3hp::graphics::setRenderState(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00431ae5  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00431ae6  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00431ae7  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8b 0xd2 */
void Application::sub_431af0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00431af0  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00431af1  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00431af2  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00431af4  e8c7fdffff             -call 0x4318c0
    cpu.esp -= 4;
    sub_4318c0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00431af9  b804000000             -mov eax, 4
    cpu.eax = 4 /*0x4*/;
    // 00431afe  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00431b00  e8fbfdffff             -call 0x431900
    cpu.esp -= 4;
    nfs3hp::graphics::setRenderState(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00431b05  b80d000000             -mov eax, 0xd
    cpu.eax = 13 /*0xd*/;
    // 00431b0a  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00431b0c  e8effdffff             -call 0x431900
    cpu.esp -= 4;
    nfs3hp::graphics::setRenderState(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00431b11  b815000000             -mov eax, 0x15
    cpu.eax = 21 /*0x15*/;
    // 00431b16  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00431b18  e8e3fdffff             -call 0x431900
    cpu.esp -= 4;
    nfs3hp::graphics::setRenderState(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00431b1d  b868000000             -mov eax, 0x68
    cpu.eax = 104 /*0x68*/;
    // 00431b22  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00431b24  e8d7fdffff             -call 0x431900
    cpu.esp -= 4;
    nfs3hp::graphics::setRenderState(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00431b29  b802000000             -mov eax, 2
    cpu.eax = 2 /*0x2*/;
    // 00431b2e  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00431b30  e8cbfdffff             -call 0x431900
    cpu.esp -= 4;
    nfs3hp::graphics::setRenderState(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00431b35  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00431b36  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00431b37  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8b 0xd2 */
void Application::sub_431b40(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00431b40  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00431b41  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00431b42  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00431b44  8b1534bc6f00           -mov edx, dword ptr [0x6fbc34]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(7322676) /* 0x6fbc34 */);
    // 00431b4a  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 00431b4c  740c                   -je 0x431b5a
    if (cpu.flags.zf)
    {
        goto L_0x00431b5a;
    }
    // 00431b4e  a1683a7a00             -mov eax, dword ptr [0x7a3a68]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(8010344) /* 0x7a3a68 */);
    // 00431b53  a3603a7a00             -mov dword ptr [0x7a3a60], eax
    app->getMemory<x86::reg32>(x86::reg32(8010336) /* 0x7a3a60 */) = cpu.eax;
    // 00431b58  eb06                   -jmp 0x431b60
    goto L_0x00431b60;
L_0x00431b5a:
    // 00431b5a  8915603a7a00           -mov dword ptr [0x7a3a60], edx
    app->getMemory<x86::reg32>(x86::reg32(8010336) /* 0x7a3a60 */) = cpu.edx;
L_0x00431b60:
    // 00431b60  e8fb5e0900             -call 0x4c7a60
    cpu.esp -= 4;
    nfs3hp::decompiled::setDepthOffsets(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00431b65  e856fdffff             -call 0x4318c0
    cpu.esp -= 4;
    sub_4318c0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00431b6a  b804000000             -mov eax, 4
    cpu.eax = 4 /*0x4*/;
    // 00431b6f  8b15603a7a00           -mov edx, dword ptr [0x7a3a60]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8010336) /* 0x7a3a60 */);
    // 00431b75  e886fdffff             -call 0x431900
    cpu.esp -= 4;
    nfs3hp::graphics::setRenderState(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00431b7a  ba01000000             -mov edx, 1
    cpu.edx = 1 /*0x1*/;
    // 00431b7f  b80d000000             -mov eax, 0xd
    cpu.eax = 13 /*0xd*/;
    // 00431b84  e877fdffff             -call 0x431900
    cpu.esp -= 4;
    nfs3hp::graphics::setRenderState(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00431b89  b815000000             -mov eax, 0x15
    cpu.eax = 21 /*0x15*/;
    // 00431b8e  8b15643a7a00           -mov edx, dword ptr [0x7a3a64]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8010340) /* 0x7a3a64 */);
    // 00431b94  e867fdffff             -call 0x431900
    cpu.esp -= 4;
    nfs3hp::graphics::setRenderState(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00431b99  b868000000             -mov eax, 0x68
    cpu.eax = 104 /*0x68*/;
    // 00431b9e  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00431ba0  e85bfdffff             -call 0x431900
    cpu.esp -= 4;
    nfs3hp::graphics::setRenderState(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00431ba5  b802000000             -mov eax, 2
    cpu.eax = 2 /*0x2*/;
    // 00431baa  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00431bac  e84ffdffff             -call 0x431900
    cpu.esp -= 4;
    nfs3hp::graphics::setRenderState(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00431bb1  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00431bb2  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00431bb3  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 */
void Application::sub_431bc0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00431bc0  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00431bc1  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00431bc2  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00431bc4  e8f7fcffff             -call 0x4318c0
    cpu.esp -= 4;
    sub_4318c0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00431bc9  b80d000000             -mov eax, 0xd
    cpu.eax = 13 /*0xd*/;
    // 00431bce  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00431bd0  e82bfdffff             -call 0x431900
    cpu.esp -= 4;
    nfs3hp::graphics::setRenderState(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00431bd5  b815000000             -mov eax, 0x15
    cpu.eax = 21 /*0x15*/;
    // 00431bda  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00431bdc  e81ffdffff             -call 0x431900
    cpu.esp -= 4;
    nfs3hp::graphics::setRenderState(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00431be1  b868000000             -mov eax, 0x68
    cpu.eax = 104 /*0x68*/;
    // 00431be6  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00431be8  e813fdffff             -call 0x431900
    cpu.esp -= 4;
    nfs3hp::graphics::setRenderState(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00431bed  ba01000000             -mov edx, 1
    cpu.edx = 1 /*0x1*/;
    // 00431bf2  b802000000             -mov eax, 2
    cpu.eax = 2 /*0x2*/;
    // 00431bf7  e804fdffff             -call 0x431900
    cpu.esp -= 4;
    nfs3hp::graphics::setRenderState(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00431bfc  b804000000             -mov eax, 4
    cpu.eax = 4 /*0x4*/;
    // 00431c01  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00431c03  e8f8fcffff             -call 0x431900
    cpu.esp -= 4;
    nfs3hp::graphics::setRenderState(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00431c08  ba01000000             -mov edx, 1
    cpu.edx = 1 /*0x1*/;
    // 00431c0d  b8c2020000             -mov eax, 0x2c2
    cpu.eax = 706 /*0x2c2*/;
    // 00431c12  e8e9fcffff             -call 0x431900
    cpu.esp -= 4;
    nfs3hp::graphics::setRenderState(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00431c17  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00431c18  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00431c19  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 */
void Application::sub_431c20(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00431c20  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00431c21  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00431c23  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00431c24  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 0x8b 0xdb */
void Application::sub_431c30(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00431c30  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00431c31  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00431c33  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00431c34  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 0x8b 0xdb */
void Application::sub_431c40(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00431c40  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00431c41  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00431c43  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00431c44  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 0x8b 0xdb */
void Application::sub_431c50(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00431c50  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00431c51  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00431c52  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00431c53  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00431c54  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00431c55  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00431c56  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00431c58  31ff                   -xor edi, edi
    cpu.edi ^= x86::reg32(x86::sreg32(cpu.edi));
    // 00431c5a  31f6                   -xor esi, esi
    cpu.esi ^= x86::reg32(x86::sreg32(cpu.esi));
    // 00431c5c  31db                   +xor ebx, ebx
    cpu.clear_co();
    cpu.set_szp((cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx))));
    // 00431c5e  eb05                   -jmp 0x431c65
    goto L_0x00431c65;
L_0x00431c60:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00431c60  83fb20                 +cmp ebx, 0x20
    {
        x86::reg32 tmp1 = cpu.ebx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(32 /*0x20*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00431c63  7d2c                   -jge 0x431c91
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00431c91;
    }
L_0x00431c65:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00431c65  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 00431c67  0fafc3                 -imul eax, ebx
    cpu.eax = x86::reg32(x86::sreg64(x86::sreg32(cpu.eax)) * x86::sreg64(x86::sreg32(cpu.ebx)));
    // 00431c6a  8d501e                 -lea edx, [eax + 0x1e]
    cpu.edx = x86::reg32(cpu.eax + x86::reg32(30) /* 0x1e */);
    // 00431c6d  b91f000000             -mov ecx, 0x1f
    cpu.ecx = 31 /*0x1f*/;
    // 00431c72  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 00431c74  c1fa1f                 -sar edx, 0x1f
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (31 /*0x1f*/ % 32));
    // 00431c77  f7f9                   -idiv ecx
    {
        x86::sreg64 tmp = x86::sreg64(cpu.edx_eax);
        x86::sreg32 d = x86::sreg32(cpu.ecx);
        cpu.edx_eax = x86::reg64(tmp / d);
        cpu.edx = x86::reg32(tmp % d);
    }
    // 00431c79  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00431c7b  83f81f                 +cmp eax, 0x1f
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(31 /*0x1f*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00431c7e  7e05                   -jle 0x431c85
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00431c85;
    }
    // 00431c80  b91f000000             -mov ecx, 0x1f
    cpu.ecx = 31 /*0x1f*/;
L_0x00431c85:
    // 00431c85  47                     +inc edi
    {
        x86::reg32& tmp = cpu.edi;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 00431c86  43                     +inc ebx
    {
        x86::reg32& tmp = cpu.ebx;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 00431c87  66890c7d96175f00       -mov word ptr [edi*2 + 0x5f1796], cx
    app->getMemory<x86::reg16>(x86::reg32(6231958) /* 0x5f1796 */ + cpu.edi * 2) = cpu.cx;
    // 00431c8f  ebcf                   -jmp 0x431c60
    goto L_0x00431c60;
L_0x00431c91:
    // 00431c91  46                     -inc esi
    (cpu.esi)++;
    // 00431c92  83fe20                 +cmp esi, 0x20
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
    // 00431c95  7d04                   -jge 0x431c9b
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00431c9b;
    }
    // 00431c97  31db                   +xor ebx, ebx
    cpu.clear_co();
    cpu.set_szp((cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx))));
    // 00431c99  ebca                   -jmp 0x431c65
    goto L_0x00431c65;
L_0x00431c9b:
    // 00431c9b  31ff                   -xor edi, edi
    cpu.edi ^= x86::reg32(x86::sreg32(cpu.edi));
    // 00431c9d  31f6                   -xor esi, esi
    cpu.esi ^= x86::reg32(x86::sreg32(cpu.esi));
    // 00431c9f  31db                   +xor ebx, ebx
    cpu.clear_co();
    cpu.set_szp((cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx))));
    // 00431ca1  eb05                   -jmp 0x431ca8
    goto L_0x00431ca8;
L_0x00431ca3:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00431ca3  83fb40                 +cmp ebx, 0x40
    {
        x86::reg32 tmp1 = cpu.ebx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(64 /*0x40*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00431ca6  7d2c                   -jge 0x431cd4
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00431cd4;
    }
L_0x00431ca8:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00431ca8  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 00431caa  0fafc3                 -imul eax, ebx
    cpu.eax = x86::reg32(x86::sreg64(x86::sreg32(cpu.eax)) * x86::sreg64(x86::sreg32(cpu.ebx)));
    // 00431cad  8d501e                 -lea edx, [eax + 0x1e]
    cpu.edx = x86::reg32(cpu.eax + x86::reg32(30) /* 0x1e */);
    // 00431cb0  b91f000000             -mov ecx, 0x1f
    cpu.ecx = 31 /*0x1f*/;
    // 00431cb5  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 00431cb7  c1fa1f                 -sar edx, 0x1f
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (31 /*0x1f*/ % 32));
    // 00431cba  f7f9                   -idiv ecx
    {
        x86::sreg64 tmp = x86::sreg64(cpu.edx_eax);
        x86::sreg32 d = x86::sreg32(cpu.ecx);
        cpu.edx_eax = x86::reg64(tmp / d);
        cpu.edx = x86::reg32(tmp % d);
    }
    // 00431cbc  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00431cbe  83f83f                 +cmp eax, 0x3f
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(63 /*0x3f*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00431cc1  7e05                   -jle 0x431cc8
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00431cc8;
    }
    // 00431cc3  b93f000000             -mov ecx, 0x3f
    cpu.ecx = 63 /*0x3f*/;
L_0x00431cc8:
    // 00431cc8  47                     +inc edi
    {
        x86::reg32& tmp = cpu.edi;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 00431cc9  43                     +inc ebx
    {
        x86::reg32& tmp = cpu.ebx;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 00431cca  66890c7d96075f00       -mov word ptr [edi*2 + 0x5f0796], cx
    app->getMemory<x86::reg16>(x86::reg32(6227862) /* 0x5f0796 */ + cpu.edi * 2) = cpu.cx;
    // 00431cd2  ebcf                   -jmp 0x431ca3
    goto L_0x00431ca3;
L_0x00431cd4:
    // 00431cd4  46                     -inc esi
    (cpu.esi)++;
    // 00431cd5  83fe20                 +cmp esi, 0x20
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
    // 00431cd8  7d04                   -jge 0x431cde
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00431cde;
    }
    // 00431cda  31db                   +xor ebx, ebx
    cpu.clear_co();
    cpu.set_szp((cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx))));
    // 00431cdc  ebca                   -jmp 0x431ca8
    goto L_0x00431ca8;
L_0x00431cde:
    // 00431cde  833d8c4356000f         +cmp dword ptr [0x56438c], 0xf
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5653388) /* 0x56438c */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(15 /*0xf*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00431ce5  7523                   -jne 0x431d0a
    if (!cpu.flags.zf)
    {
        goto L_0x00431d0a;
    }
    // 00431ce7  b91f000000             -mov ecx, 0x1f
    cpu.ecx = 31 /*0x1f*/;
    // 00431cec  bfe0030000             -mov edi, 0x3e0
    cpu.edi = 992 /*0x3e0*/;
    // 00431cf1  bb007c0000             -mov ebx, 0x7c00
    cpu.ebx = 31744 /*0x7c00*/;
    // 00431cf6  ba0a000000             -mov edx, 0xa
    cpu.edx = 10 /*0xa*/;
    // 00431cfb  31f6                   +xor esi, esi
    cpu.clear_co();
    cpu.set_szp((cpu.esi ^= x86::reg32(x86::sreg32(cpu.esi))));
    // 00431cfd  890d704e5500           -mov dword ptr [0x554e70], ecx
    app->getMemory<x86::reg32>(x86::reg32(5590640) /* 0x554e70 */) = cpu.ecx;
    // 00431d03  b905000000             -mov ecx, 5
    cpu.ecx = 5 /*0x5*/;
    // 00431d08  eb21                   -jmp 0x431d2b
    goto L_0x00431d2b;
L_0x00431d0a:
    // 00431d0a  bb1f000000             -mov ebx, 0x1f
    cpu.ebx = 31 /*0x1f*/;
    // 00431d0f  bfe0070000             -mov edi, 0x7e0
    cpu.edi = 2016 /*0x7e0*/;
    // 00431d14  b905000000             -mov ecx, 5
    cpu.ecx = 5 /*0x5*/;
    // 00431d19  ba0b000000             -mov edx, 0xb
    cpu.edx = 11 /*0xb*/;
    // 00431d1e  31f6                   -xor esi, esi
    cpu.esi ^= x86::reg32(x86::sreg32(cpu.esi));
    // 00431d20  891d704e5500           -mov dword ptr [0x554e70], ebx
    app->getMemory<x86::reg32>(x86::reg32(5590640) /* 0x554e70 */) = cpu.ebx;
    // 00431d26  bb00f80000             -mov ebx, 0xf800
    cpu.ebx = 63488 /*0xf800*/;
L_0x00431d2b:
    // 00431d2b  893d744e5500           -mov dword ptr [0x554e74], edi
    app->getMemory<x86::reg32>(x86::reg32(5590644) /* 0x554e74 */) = cpu.edi;
    // 00431d31  89357c4e5500           -mov dword ptr [0x554e7c], esi
    app->getMemory<x86::reg32>(x86::reg32(5590652) /* 0x554e7c */) = cpu.esi;
    // 00431d37  891d784e5500           -mov dword ptr [0x554e78], ebx
    app->getMemory<x86::reg32>(x86::reg32(5590648) /* 0x554e78 */) = cpu.ebx;
    // 00431d3d  890d804e5500           -mov dword ptr [0x554e80], ecx
    app->getMemory<x86::reg32>(x86::reg32(5590656) /* 0x554e80 */) = cpu.ecx;
    // 00431d43  8915844e5500           -mov dword ptr [0x554e84], edx
    app->getMemory<x86::reg32>(x86::reg32(5590660) /* 0x554e84 */) = cpu.edx;
    // 00431d49  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00431d4a  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00431d4b  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00431d4c  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00431d4d  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00431d4e  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00431d4f  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip  */
void Application::sub_431d50(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00431d50  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00431d51  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00431d52  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00431d53  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00431d54  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00431d55  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00431d56  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00431d58  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
L_0x00431d5b:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00431d5b  8b4810                 -mov ecx, dword ptr [eax + 0x10]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(16) /* 0x10 */);
    // 00431d5e  3b480c                 +cmp ecx, dword ptr [eax + 0xc]
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
    // 00431d61  0f8201010000           -jb 0x431e68
    if (cpu.flags.cf)
    {
        goto L_0x00431e68;
    }
    // 00431d67  8b5808                 -mov ebx, dword ptr [eax + 8]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 00431d6a  8b5018                 -mov edx, dword ptr [eax + 0x18]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */);
    // 00431d6d  8b7014                 -mov esi, dword ptr [eax + 0x14]
    cpu.esi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */);
    // 00431d70  21da                   -and edx, ebx
    cpu.edx &= x86::reg32(x86::sreg32(cpu.ebx));
    // 00431d72  01f2                   -add edx, esi
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.esi));
    // 00431d74  c1ea0f                 -shr edx, 0xf
    cpu.edx >>= 15 /*0xf*/ % 32;
    // 00431d77  8d1c9500000000         -lea ebx, [edx*4]
    cpu.ebx = x86::reg32(cpu.edx * 4);
    // 00431d7e  8b10                   -mov edx, dword ptr [eax]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax);
    // 00431d80  8b141a                 -mov edx, dword ptr [edx + ebx]
    cpu.edx = app->getMemory<x86::reg32>(cpu.edx + cpu.ebx * 1);
    // 00431d83  8b581c                 -mov ebx, dword ptr [eax + 0x1c]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(28) /* 0x1c */);
    // 00431d86  8d0c1e                 -lea ecx, [esi + ebx]
    cpu.ecx = x86::reg32(cpu.esi + cpu.ebx * 1);
    // 00431d89  8b5820                 -mov ebx, dword ptr [eax + 0x20]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(32) /* 0x20 */);
    // 00431d8c  8b7018                 -mov esi, dword ptr [eax + 0x18]
    cpu.esi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */);
    // 00431d8f  8b780c                 -mov edi, dword ptr [eax + 0xc]
    cpu.edi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
    // 00431d92  01de                   -add esi, ebx
    (cpu.esi) += x86::reg32(x86::sreg32(cpu.ebx));
    // 00431d94  668b3f                 -mov di, word ptr [edi]
    cpu.di = app->getMemory<x86::reg16>(cpu.edi);
    // 00431d97  897018                 -mov dword ptr [eax + 0x18], esi
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */) = cpu.esi;
    // 00431d9a  8b35704e5500           -mov esi, dword ptr [0x554e70]
    cpu.esi = app->getMemory<x86::reg32>(x86::reg32(5590640) /* 0x554e70 */);
    // 00431da0  8b1d981f5f00           -mov ebx, dword ptr [0x5f1f98]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(6234008) /* 0x5f1f98 */);
    // 00431da6  21d6                   -and esi, edx
    cpu.esi &= x86::reg32(x86::sreg32(cpu.edx));
    // 00431da8  894814                 -mov dword ptr [eax + 0x14], ecx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */) = cpu.ecx;
    // 00431dab  668b3473               -mov si, word ptr [ebx + esi*2]
    cpu.si = app->getMemory<x86::reg16>(cpu.ebx + cpu.esi * 2);
    // 00431daf  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
    // 00431db1  8b0d704e5500           -mov ecx, dword ptr [0x554e70]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(5590640) /* 0x554e70 */);
    // 00431db7  6689fb                 -mov bx, di
    cpu.bx = cpu.di;
    // 00431dba  81e6ffff0000           -and esi, 0xffff
    cpu.esi &= x86::reg32(x86::sreg32(65535 /*0xffff*/));
    // 00431dc0  21cb                   -and ebx, ecx
    cpu.ebx &= x86::reg32(x86::sreg32(cpu.ecx));
    // 00431dc2  01de                   -add esi, ebx
    (cpu.esi) += x86::reg32(x86::sreg32(cpu.ebx));
    // 00431dc4  39ce                   +cmp esi, ecx
    {
        x86::reg32 tmp1 = cpu.esi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ecx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00431dc6  7e02                   -jle 0x431dca
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00431dca;
    }
    // 00431dc8  89ce                   -mov esi, ecx
    cpu.esi = cpu.ecx;
L_0x00431dca:
    // 00431dca  8b1d744e5500           -mov ebx, dword ptr [0x554e74]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(5590644) /* 0x554e74 */);
    // 00431dd0  8a0d804e5500           -mov cl, byte ptr [0x554e80]
    cpu.cl = app->getMemory<x86::reg8>(x86::reg32(5590656) /* 0x554e80 */);
    // 00431dd6  21d3                   -and ebx, edx
    cpu.ebx &= x86::reg32(x86::sreg32(cpu.edx));
    // 00431dd8  d3fb                   -sar ebx, cl
    cpu.ebx = x86::reg32(x86::sreg32(cpu.ebx) >> (cpu.cl % 32));
    // 00431dda  01db                   -add ebx, ebx
    (cpu.ebx) += x86::reg32(x86::sreg32(cpu.ebx));
    // 00431ddc  895dfc                 -mov dword ptr [ebp - 4], ebx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.ebx;
    // 00431ddf  8b4dfc                 -mov ecx, dword ptr [ebp - 4]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00431de2  8b1da41f5f00           -mov ebx, dword ptr [0x5f1fa4]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(6234020) /* 0x5f1fa4 */);
    // 00431de8  01cb                   -add ebx, ecx
    (cpu.ebx) += x86::reg32(x86::sreg32(cpu.ecx));
    // 00431dea  668b1b                 -mov bx, word ptr [ebx]
    cpu.bx = app->getMemory<x86::reg16>(cpu.ebx);
    // 00431ded  8a0d804e5500           -mov cl, byte ptr [0x554e80]
    cpu.cl = app->getMemory<x86::reg8>(x86::reg32(5590656) /* 0x554e80 */);
    // 00431df3  81e3ffff0000           -and ebx, 0xffff
    cpu.ebx &= x86::reg32(x86::sreg32(65535 /*0xffff*/));
    // 00431df9  d3e3                   -shl ebx, cl
    cpu.ebx <<= cpu.cl % 32;
    // 00431dfb  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 00431dfd  6689f9                 -mov cx, di
    cpu.cx = cpu.di;
    // 00431e00  230d744e5500           -and ecx, dword ptr [0x554e74]
    cpu.ecx &= x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(5590644) /* 0x554e74 */)));
    // 00431e06  01cb                   -add ebx, ecx
    (cpu.ebx) += x86::reg32(x86::sreg32(cpu.ecx));
    // 00431e08  8b0d744e5500           -mov ecx, dword ptr [0x554e74]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(5590644) /* 0x554e74 */);
    // 00431e0e  39cb                   +cmp ebx, ecx
    {
        x86::reg32 tmp1 = cpu.ebx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ecx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00431e10  7e02                   -jle 0x431e14
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00431e14;
    }
    // 00431e12  89cb                   -mov ebx, ecx
    cpu.ebx = cpu.ecx;
L_0x00431e14:
    // 00431e14  2315784e5500           -and edx, dword ptr [0x554e78]
    cpu.edx &= x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(5590648) /* 0x554e78 */)));
    // 00431e1a  8a0d844e5500           -mov cl, byte ptr [0x554e84]
    cpu.cl = app->getMemory<x86::reg8>(x86::reg32(5590660) /* 0x554e84 */);
    // 00431e20  d3fa                   -sar edx, cl
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (cpu.cl % 32));
    // 00431e22  8b0d9c1f5f00           -mov ecx, dword ptr [0x5f1f9c]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(6234012) /* 0x5f1f9c */);
    // 00431e28  01d2                   -add edx, edx
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.edx));
    // 00431e2a  01ca                   -add edx, ecx
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.ecx));
    // 00431e2c  668b12                 -mov dx, word ptr [edx]
    cpu.dx = app->getMemory<x86::reg16>(cpu.edx);
    // 00431e2f  8a0d844e5500           -mov cl, byte ptr [0x554e84]
    cpu.cl = app->getMemory<x86::reg8>(x86::reg32(5590660) /* 0x554e84 */);
    // 00431e35  81e2ffff0000           -and edx, 0xffff
    cpu.edx &= x86::reg32(x86::sreg32(65535 /*0xffff*/));
    // 00431e3b  d3e2                   -shl edx, cl
    cpu.edx <<= cpu.cl % 32;
    // 00431e3d  8b0d784e5500           -mov ecx, dword ptr [0x554e78]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(5590648) /* 0x554e78 */);
    // 00431e43  81e7ffff0000           -and edi, 0xffff
    cpu.edi &= x86::reg32(x86::sreg32(65535 /*0xffff*/));
    // 00431e49  21cf                   -and edi, ecx
    cpu.edi &= x86::reg32(x86::sreg32(cpu.ecx));
    // 00431e4b  01fa                   -add edx, edi
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.edi));
    // 00431e4d  39ca                   +cmp edx, ecx
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
    // 00431e4f  7e02                   -jle 0x431e53
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00431e53;
    }
    // 00431e51  89ca                   -mov edx, ecx
    cpu.edx = cpu.ecx;
L_0x00431e53:
    // 00431e53  09f3                   -or ebx, esi
    cpu.ebx |= x86::reg32(x86::sreg32(cpu.esi));
    // 00431e55  09d3                   +or ebx, edx
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(cpu.edx))));
    // 00431e57  8b500c                 -mov edx, dword ptr [eax + 0xc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
    // 00431e5a  8d4a02                 -lea ecx, [edx + 2]
    cpu.ecx = x86::reg32(cpu.edx + x86::reg32(2) /* 0x2 */);
    // 00431e5d  89480c                 -mov dword ptr [eax + 0xc], ecx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */) = cpu.ecx;
    // 00431e60  66891a                 -mov word ptr [edx], bx
    app->getMemory<x86::reg16>(cpu.edx) = cpu.bx;
    // 00431e63  e9f3feffff             -jmp 0x431d5b
    goto L_0x00431d5b;
L_0x00431e68:
    // 00431e68  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00431e6a  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00431e6b  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00431e6c  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00431e6d  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00431e6e  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00431e6f  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00431e70  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x8d 0x40 0x00 */
void Application::sub_431e80(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00431e80  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00431e81  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00431e82  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00431e83  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00431e84  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00431e85  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00431e86  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
L_0x00431e88:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00431e88  8b4810                 -mov ecx, dword ptr [eax + 0x10]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(16) /* 0x10 */);
    // 00431e8b  3b480c                 +cmp ecx, dword ptr [eax + 0xc]
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
    // 00431e8e  0f82fc000000           -jb 0x431f90
    if (cpu.flags.cf)
    {
        goto L_0x00431f90;
    }
    // 00431e94  8b5808                 -mov ebx, dword ptr [eax + 8]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 00431e97  8b5018                 -mov edx, dword ptr [eax + 0x18]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */);
    // 00431e9a  8b7014                 -mov esi, dword ptr [eax + 0x14]
    cpu.esi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */);
    // 00431e9d  21da                   -and edx, ebx
    cpu.edx &= x86::reg32(x86::sreg32(cpu.ebx));
    // 00431e9f  01f2                   -add edx, esi
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.esi));
    // 00431ea1  8b18                   -mov ebx, dword ptr [eax]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.eax);
    // 00431ea3  c1ea0f                 -shr edx, 0xf
    cpu.edx >>= 15 /*0xf*/ % 32;
    // 00431ea6  8b780c                 -mov edi, dword ptr [eax + 0xc]
    cpu.edi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
    // 00431ea9  0fbf1453               -movsx edx, word ptr [ebx + edx*2]
    cpu.edx = x86::reg32(static_cast<x86::sreg16>(app->getMemory<x86::reg16>(cpu.ebx + cpu.edx * 2)));
    // 00431ead  8b581c                 -mov ebx, dword ptr [eax + 0x1c]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(28) /* 0x1c */);
    // 00431eb0  668b3f                 -mov di, word ptr [edi]
    cpu.di = app->getMemory<x86::reg16>(cpu.edi);
    // 00431eb3  8d0c1e                 -lea ecx, [esi + ebx]
    cpu.ecx = x86::reg32(cpu.esi + cpu.ebx * 1);
    // 00431eb6  8b5820                 -mov ebx, dword ptr [eax + 0x20]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(32) /* 0x20 */);
    // 00431eb9  8b7018                 -mov esi, dword ptr [eax + 0x18]
    cpu.esi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */);
    // 00431ebc  894814                 -mov dword ptr [eax + 0x14], ecx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */) = cpu.ecx;
    // 00431ebf  01de                   -add esi, ebx
    (cpu.esi) += x86::reg32(x86::sreg32(cpu.ebx));
    // 00431ec1  897018                 -mov dword ptr [eax + 0x18], esi
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */) = cpu.esi;
    // 00431ec4  f6c680                 +test dh, 0x80
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.dh & 128 /*0x80*/));
    // 00431ec7  0f84ba000000           -je 0x431f87
    if (cpu.flags.zf)
    {
        goto L_0x00431f87;
    }
    // 00431ecd  8b35704e5500           -mov esi, dword ptr [0x554e70]
    cpu.esi = app->getMemory<x86::reg32>(x86::reg32(5590640) /* 0x554e70 */);
    // 00431ed3  8b1d981f5f00           -mov ebx, dword ptr [0x5f1f98]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(6234008) /* 0x5f1f98 */);
    // 00431ed9  21d6                   -and esi, edx
    cpu.esi &= x86::reg32(x86::sreg32(cpu.edx));
    // 00431edb  668b3473               -mov si, word ptr [ebx + esi*2]
    cpu.si = app->getMemory<x86::reg16>(cpu.ebx + cpu.esi * 2);
    // 00431edf  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
    // 00431ee1  8b0d704e5500           -mov ecx, dword ptr [0x554e70]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(5590640) /* 0x554e70 */);
    // 00431ee7  6689fb                 -mov bx, di
    cpu.bx = cpu.di;
    // 00431eea  81e6ffff0000           -and esi, 0xffff
    cpu.esi &= x86::reg32(x86::sreg32(65535 /*0xffff*/));
    // 00431ef0  21cb                   -and ebx, ecx
    cpu.ebx &= x86::reg32(x86::sreg32(cpu.ecx));
    // 00431ef2  01de                   -add esi, ebx
    (cpu.esi) += x86::reg32(x86::sreg32(cpu.ebx));
    // 00431ef4  39ce                   +cmp esi, ecx
    {
        x86::reg32 tmp1 = cpu.esi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ecx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00431ef6  7e02                   -jle 0x431efa
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00431efa;
    }
    // 00431ef8  89ce                   -mov esi, ecx
    cpu.esi = cpu.ecx;
L_0x00431efa:
    // 00431efa  8b1d744e5500           -mov ebx, dword ptr [0x554e74]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(5590644) /* 0x554e74 */);
    // 00431f00  8a0d804e5500           -mov cl, byte ptr [0x554e80]
    cpu.cl = app->getMemory<x86::reg8>(x86::reg32(5590656) /* 0x554e80 */);
    // 00431f06  21d3                   -and ebx, edx
    cpu.ebx &= x86::reg32(x86::sreg32(cpu.edx));
    // 00431f08  d3fb                   -sar ebx, cl
    cpu.ebx = x86::reg32(x86::sreg32(cpu.ebx) >> (cpu.cl % 32));
    // 00431f0a  8b0da41f5f00           -mov ecx, dword ptr [0x5f1fa4]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(6234020) /* 0x5f1fa4 */);
    // 00431f10  01db                   -add ebx, ebx
    (cpu.ebx) += x86::reg32(x86::sreg32(cpu.ebx));
    // 00431f12  01cb                   -add ebx, ecx
    (cpu.ebx) += x86::reg32(x86::sreg32(cpu.ecx));
    // 00431f14  668b1b                 -mov bx, word ptr [ebx]
    cpu.bx = app->getMemory<x86::reg16>(cpu.ebx);
    // 00431f17  8a0d804e5500           -mov cl, byte ptr [0x554e80]
    cpu.cl = app->getMemory<x86::reg8>(x86::reg32(5590656) /* 0x554e80 */);
    // 00431f1d  81e3ffff0000           -and ebx, 0xffff
    cpu.ebx &= x86::reg32(x86::sreg32(65535 /*0xffff*/));
    // 00431f23  d3e3                   -shl ebx, cl
    cpu.ebx <<= cpu.cl % 32;
    // 00431f25  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 00431f27  6689f9                 -mov cx, di
    cpu.cx = cpu.di;
    // 00431f2a  230d744e5500           -and ecx, dword ptr [0x554e74]
    cpu.ecx &= x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(5590644) /* 0x554e74 */)));
    // 00431f30  01cb                   -add ebx, ecx
    (cpu.ebx) += x86::reg32(x86::sreg32(cpu.ecx));
    // 00431f32  8b0d744e5500           -mov ecx, dword ptr [0x554e74]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(5590644) /* 0x554e74 */);
    // 00431f38  39cb                   +cmp ebx, ecx
    {
        x86::reg32 tmp1 = cpu.ebx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ecx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00431f3a  7e02                   -jle 0x431f3e
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00431f3e;
    }
    // 00431f3c  89cb                   -mov ebx, ecx
    cpu.ebx = cpu.ecx;
L_0x00431f3e:
    // 00431f3e  2315784e5500           -and edx, dword ptr [0x554e78]
    cpu.edx &= x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(5590648) /* 0x554e78 */)));
    // 00431f44  8a0d844e5500           -mov cl, byte ptr [0x554e84]
    cpu.cl = app->getMemory<x86::reg8>(x86::reg32(5590660) /* 0x554e84 */);
    // 00431f4a  d3fa                   -sar edx, cl
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (cpu.cl % 32));
    // 00431f4c  8b0d9c1f5f00           -mov ecx, dword ptr [0x5f1f9c]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(6234012) /* 0x5f1f9c */);
    // 00431f52  01d2                   -add edx, edx
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.edx));
    // 00431f54  01ca                   -add edx, ecx
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.ecx));
    // 00431f56  668b12                 -mov dx, word ptr [edx]
    cpu.dx = app->getMemory<x86::reg16>(cpu.edx);
    // 00431f59  8a0d844e5500           -mov cl, byte ptr [0x554e84]
    cpu.cl = app->getMemory<x86::reg8>(x86::reg32(5590660) /* 0x554e84 */);
    // 00431f5f  81e2ffff0000           -and edx, 0xffff
    cpu.edx &= x86::reg32(x86::sreg32(65535 /*0xffff*/));
    // 00431f65  d3e2                   -shl edx, cl
    cpu.edx <<= cpu.cl % 32;
    // 00431f67  8b0d784e5500           -mov ecx, dword ptr [0x554e78]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(5590648) /* 0x554e78 */);
    // 00431f6d  81e7ffff0000           -and edi, 0xffff
    cpu.edi &= x86::reg32(x86::sreg32(65535 /*0xffff*/));
    // 00431f73  21cf                   -and edi, ecx
    cpu.edi &= x86::reg32(x86::sreg32(cpu.ecx));
    // 00431f75  01fa                   -add edx, edi
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.edi));
    // 00431f77  39ca                   +cmp edx, ecx
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
    // 00431f79  7e02                   -jle 0x431f7d
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00431f7d;
    }
    // 00431f7b  89ca                   -mov edx, ecx
    cpu.edx = cpu.ecx;
L_0x00431f7d:
    // 00431f7d  09f3                   -or ebx, esi
    cpu.ebx |= x86::reg32(x86::sreg32(cpu.esi));
    // 00431f7f  09da                   -or edx, ebx
    cpu.edx |= x86::reg32(x86::sreg32(cpu.ebx));
    // 00431f81  8b580c                 -mov ebx, dword ptr [eax + 0xc]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
    // 00431f84  668913                 -mov word ptr [ebx], dx
    app->getMemory<x86::reg16>(cpu.ebx) = cpu.dx;
L_0x00431f87:
    // 00431f87  83400c02               +add dword ptr [eax + 0xc], 2
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
    // 00431f8b  e9f8feffff             -jmp 0x431e88
    goto L_0x00431e88;
L_0x00431f90:
    // 00431f90  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00431f91  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00431f92  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00431f93  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00431f94  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00431f95  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00431f96  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 */
void Application::sub_431fa0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00431fa0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00431fa1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00431fa2  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00431fa3  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00431fa4  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00431fa5  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00431fa6  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
L_0x00431fa8:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00431fa8  8b4810                 -mov ecx, dword ptr [eax + 0x10]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(16) /* 0x10 */);
    // 00431fab  3b480c                 +cmp ecx, dword ptr [eax + 0xc]
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
    // 00431fae  0f82ad000000           -jb 0x432061
    if (cpu.flags.cf)
    {
        goto L_0x00432061;
    }
    // 00431fb4  8b5808                 -mov ebx, dword ptr [eax + 8]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 00431fb7  8b5018                 -mov edx, dword ptr [eax + 0x18]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */);
    // 00431fba  8b7014                 -mov esi, dword ptr [eax + 0x14]
    cpu.esi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */);
    // 00431fbd  21da                   -and edx, ebx
    cpu.edx &= x86::reg32(x86::sreg32(cpu.ebx));
    // 00431fbf  01f2                   -add edx, esi
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.esi));
    // 00431fc1  8b08                   -mov ecx, dword ptr [eax]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax);
    // 00431fc3  c1ea0f                 -shr edx, 0xf
    cpu.edx >>= 15 /*0xf*/ % 32;
    // 00431fc6  0fbf1c51               -movsx ebx, word ptr [ecx + edx*2]
    cpu.ebx = x86::reg32(static_cast<x86::sreg16>(app->getMemory<x86::reg16>(cpu.ecx + cpu.edx * 2)));
    // 00431fca  8b501c                 -mov edx, dword ptr [eax + 0x1c]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(28) /* 0x1c */);
    // 00431fcd  8b4818                 -mov ecx, dword ptr [eax + 0x18]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */);
    // 00431fd0  8d3c16                 -lea edi, [esi + edx]
    cpu.edi = x86::reg32(cpu.esi + cpu.edx * 1);
    // 00431fd3  8b5020                 -mov edx, dword ptr [eax + 0x20]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(32) /* 0x20 */);
    // 00431fd6  897814                 -mov dword ptr [eax + 0x14], edi
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */) = cpu.edi;
    // 00431fd9  01d1                   -add ecx, edx
    (cpu.ecx) += x86::reg32(x86::sreg32(cpu.edx));
    // 00431fdb  894818                 -mov dword ptr [eax + 0x18], ecx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */) = cpu.ecx;
    // 00431fde  f6c780                 +test bh, 0x80
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.bh & 128 /*0x80*/));
    // 00431fe1  7475                   -je 0x432058
    if (cpu.flags.zf)
    {
        goto L_0x00432058;
    }
    // 00431fe3  8b35704e5500           -mov esi, dword ptr [0x554e70]
    cpu.esi = app->getMemory<x86::reg32>(x86::reg32(5590640) /* 0x554e70 */);
    // 00431fe9  8b15981f5f00           -mov edx, dword ptr [0x5f1f98]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(6234008) /* 0x5f1f98 */);
    // 00431fef  21de                   -and esi, ebx
    cpu.esi &= x86::reg32(x86::sreg32(cpu.ebx));
    // 00431ff1  668b3472               -mov si, word ptr [edx + esi*2]
    cpu.si = app->getMemory<x86::reg16>(cpu.edx + cpu.esi * 2);
    // 00431ff5  8b15744e5500           -mov edx, dword ptr [0x554e74]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5590644) /* 0x554e74 */);
    // 00431ffb  8a0d804e5500           -mov cl, byte ptr [0x554e80]
    cpu.cl = app->getMemory<x86::reg8>(x86::reg32(5590656) /* 0x554e80 */);
    // 00432001  21da                   -and edx, ebx
    cpu.edx &= x86::reg32(x86::sreg32(cpu.ebx));
    // 00432003  d3fa                   -sar edx, cl
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (cpu.cl % 32));
    // 00432005  8d0c12                 -lea ecx, [edx + edx]
    cpu.ecx = x86::reg32(cpu.edx + cpu.edx * 1);
    // 00432008  8b15a41f5f00           -mov edx, dword ptr [0x5f1fa4]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(6234020) /* 0x5f1fa4 */);
    // 0043200e  81e6ffff0000           -and esi, 0xffff
    cpu.esi &= x86::reg32(x86::sreg32(65535 /*0xffff*/));
    // 00432014  668b1411               -mov dx, word ptr [ecx + edx]
    cpu.dx = app->getMemory<x86::reg16>(cpu.ecx + cpu.edx * 1);
    // 00432018  8a0d804e5500           -mov cl, byte ptr [0x554e80]
    cpu.cl = app->getMemory<x86::reg8>(x86::reg32(5590656) /* 0x554e80 */);
    // 0043201e  81e2ffff0000           -and edx, 0xffff
    cpu.edx &= x86::reg32(x86::sreg32(65535 /*0xffff*/));
    // 00432024  8b3d784e5500           -mov edi, dword ptr [0x554e78]
    cpu.edi = app->getMemory<x86::reg32>(x86::reg32(5590648) /* 0x554e78 */);
    // 0043202a  d3e2                   -shl edx, cl
    cpu.edx <<= cpu.cl % 32;
    // 0043202c  21fb                   -and ebx, edi
    cpu.ebx &= x86::reg32(x86::sreg32(cpu.edi));
    // 0043202e  8a0d844e5500           -mov cl, byte ptr [0x554e84]
    cpu.cl = app->getMemory<x86::reg8>(x86::reg32(5590660) /* 0x554e84 */);
    // 00432034  d3fb                   -sar ebx, cl
    cpu.ebx = x86::reg32(x86::sreg32(cpu.ebx) >> (cpu.cl % 32));
    // 00432036  8b0d9c1f5f00           -mov ecx, dword ptr [0x5f1f9c]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(6234012) /* 0x5f1f9c */);
    // 0043203c  668b1c59               -mov bx, word ptr [ecx + ebx*2]
    cpu.bx = app->getMemory<x86::reg16>(cpu.ecx + cpu.ebx * 2);
    // 00432040  8a0d844e5500           -mov cl, byte ptr [0x554e84]
    cpu.cl = app->getMemory<x86::reg8>(x86::reg32(5590660) /* 0x554e84 */);
    // 00432046  81e3ffff0000           -and ebx, 0xffff
    cpu.ebx &= x86::reg32(x86::sreg32(65535 /*0xffff*/));
    // 0043204c  09f2                   -or edx, esi
    cpu.edx |= x86::reg32(x86::sreg32(cpu.esi));
    // 0043204e  d3e3                   -shl ebx, cl
    cpu.ebx <<= cpu.cl % 32;
    // 00432050  09d3                   -or ebx, edx
    cpu.ebx |= x86::reg32(x86::sreg32(cpu.edx));
    // 00432052  8b500c                 -mov edx, dword ptr [eax + 0xc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
    // 00432055  66891a                 -mov word ptr [edx], bx
    app->getMemory<x86::reg16>(cpu.edx) = cpu.bx;
L_0x00432058:
    // 00432058  83400c02               +add dword ptr [eax + 0xc], 2
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
    // 0043205c  e947ffffff             -jmp 0x431fa8
    goto L_0x00431fa8;
L_0x00432061:
    // 00432061  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00432062  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00432063  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00432064  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00432065  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00432066  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00432067  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8b 0xd2 */
void Application::sub_432070(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00432070  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00432071  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00432072  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00432073  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00432074  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00432075  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00432076  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
L_0x00432078:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00432078  8b4810                 -mov ecx, dword ptr [eax + 0x10]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(16) /* 0x10 */);
    // 0043207b  3b480c                 +cmp ecx, dword ptr [eax + 0xc]
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
    // 0043207e  0f82f6000000           -jb 0x43217a
    if (cpu.flags.cf)
    {
        goto L_0x0043217a;
    }
    // 00432084  8b5808                 -mov ebx, dword ptr [eax + 8]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 00432087  8b5018                 -mov edx, dword ptr [eax + 0x18]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */);
    // 0043208a  8b7014                 -mov esi, dword ptr [eax + 0x14]
    cpu.esi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */);
    // 0043208d  21da                   -and edx, ebx
    cpu.edx &= x86::reg32(x86::sreg32(cpu.ebx));
    // 0043208f  01f2                   -add edx, esi
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.esi));
    // 00432091  c1ea0f                 -shr edx, 0xf
    cpu.edx >>= 15 /*0xf*/ % 32;
    // 00432094  8d1c12                 -lea ebx, [edx + edx]
    cpu.ebx = x86::reg32(cpu.edx + cpu.edx * 1);
    // 00432097  8b10                   -mov edx, dword ptr [eax]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax);
    // 00432099  0fbf141a               -movsx edx, word ptr [edx + ebx]
    cpu.edx = x86::reg32(static_cast<x86::sreg16>(app->getMemory<x86::reg16>(cpu.edx + cpu.ebx * 1)));
    // 0043209d  8b581c                 -mov ebx, dword ptr [eax + 0x1c]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(28) /* 0x1c */);
    // 004320a0  8d0c1e                 -lea ecx, [esi + ebx]
    cpu.ecx = x86::reg32(cpu.esi + cpu.ebx * 1);
    // 004320a3  8b5820                 -mov ebx, dword ptr [eax + 0x20]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(32) /* 0x20 */);
    // 004320a6  8b7018                 -mov esi, dword ptr [eax + 0x18]
    cpu.esi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */);
    // 004320a9  8b780c                 -mov edi, dword ptr [eax + 0xc]
    cpu.edi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
    // 004320ac  01de                   -add esi, ebx
    (cpu.esi) += x86::reg32(x86::sreg32(cpu.ebx));
    // 004320ae  668b3f                 -mov di, word ptr [edi]
    cpu.di = app->getMemory<x86::reg16>(cpu.edi);
    // 004320b1  897018                 -mov dword ptr [eax + 0x18], esi
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */) = cpu.esi;
    // 004320b4  8b35704e5500           -mov esi, dword ptr [0x554e70]
    cpu.esi = app->getMemory<x86::reg32>(x86::reg32(5590640) /* 0x554e70 */);
    // 004320ba  8b1d981f5f00           -mov ebx, dword ptr [0x5f1f98]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(6234008) /* 0x5f1f98 */);
    // 004320c0  21d6                   -and esi, edx
    cpu.esi &= x86::reg32(x86::sreg32(cpu.edx));
    // 004320c2  894814                 -mov dword ptr [eax + 0x14], ecx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */) = cpu.ecx;
    // 004320c5  668b3473               -mov si, word ptr [ebx + esi*2]
    cpu.si = app->getMemory<x86::reg16>(cpu.ebx + cpu.esi * 2);
    // 004320c9  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
    // 004320cb  8b0d704e5500           -mov ecx, dword ptr [0x554e70]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(5590640) /* 0x554e70 */);
    // 004320d1  6689fb                 -mov bx, di
    cpu.bx = cpu.di;
    // 004320d4  81e6ffff0000           -and esi, 0xffff
    cpu.esi &= x86::reg32(x86::sreg32(65535 /*0xffff*/));
    // 004320da  21cb                   -and ebx, ecx
    cpu.ebx &= x86::reg32(x86::sreg32(cpu.ecx));
    // 004320dc  01de                   -add esi, ebx
    (cpu.esi) += x86::reg32(x86::sreg32(cpu.ebx));
    // 004320de  39ce                   +cmp esi, ecx
    {
        x86::reg32 tmp1 = cpu.esi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ecx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004320e0  7e02                   -jle 0x4320e4
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004320e4;
    }
    // 004320e2  89ce                   -mov esi, ecx
    cpu.esi = cpu.ecx;
L_0x004320e4:
    // 004320e4  8b1d744e5500           -mov ebx, dword ptr [0x554e74]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(5590644) /* 0x554e74 */);
    // 004320ea  8a0d804e5500           -mov cl, byte ptr [0x554e80]
    cpu.cl = app->getMemory<x86::reg8>(x86::reg32(5590656) /* 0x554e80 */);
    // 004320f0  21d3                   -and ebx, edx
    cpu.ebx &= x86::reg32(x86::sreg32(cpu.edx));
    // 004320f2  d3fb                   -sar ebx, cl
    cpu.ebx = x86::reg32(x86::sreg32(cpu.ebx) >> (cpu.cl % 32));
    // 004320f4  8b0da41f5f00           -mov ecx, dword ptr [0x5f1fa4]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(6234020) /* 0x5f1fa4 */);
    // 004320fa  01db                   -add ebx, ebx
    (cpu.ebx) += x86::reg32(x86::sreg32(cpu.ebx));
    // 004320fc  01cb                   -add ebx, ecx
    (cpu.ebx) += x86::reg32(x86::sreg32(cpu.ecx));
    // 004320fe  668b1b                 -mov bx, word ptr [ebx]
    cpu.bx = app->getMemory<x86::reg16>(cpu.ebx);
    // 00432101  8a0d804e5500           -mov cl, byte ptr [0x554e80]
    cpu.cl = app->getMemory<x86::reg8>(x86::reg32(5590656) /* 0x554e80 */);
    // 00432107  81e3ffff0000           -and ebx, 0xffff
    cpu.ebx &= x86::reg32(x86::sreg32(65535 /*0xffff*/));
    // 0043210d  d3e3                   -shl ebx, cl
    cpu.ebx <<= cpu.cl % 32;
    // 0043210f  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 00432111  6689f9                 -mov cx, di
    cpu.cx = cpu.di;
    // 00432114  230d744e5500           -and ecx, dword ptr [0x554e74]
    cpu.ecx &= x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(5590644) /* 0x554e74 */)));
    // 0043211a  01cb                   -add ebx, ecx
    (cpu.ebx) += x86::reg32(x86::sreg32(cpu.ecx));
    // 0043211c  8b0d744e5500           -mov ecx, dword ptr [0x554e74]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(5590644) /* 0x554e74 */);
    // 00432122  39cb                   +cmp ebx, ecx
    {
        x86::reg32 tmp1 = cpu.ebx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ecx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00432124  7e02                   -jle 0x432128
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00432128;
    }
    // 00432126  89cb                   -mov ebx, ecx
    cpu.ebx = cpu.ecx;
L_0x00432128:
    // 00432128  2315784e5500           -and edx, dword ptr [0x554e78]
    cpu.edx &= x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(5590648) /* 0x554e78 */)));
    // 0043212e  8a0d844e5500           -mov cl, byte ptr [0x554e84]
    cpu.cl = app->getMemory<x86::reg8>(x86::reg32(5590660) /* 0x554e84 */);
    // 00432134  d3fa                   -sar edx, cl
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (cpu.cl % 32));
    // 00432136  8b0d9c1f5f00           -mov ecx, dword ptr [0x5f1f9c]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(6234012) /* 0x5f1f9c */);
    // 0043213c  01d2                   -add edx, edx
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.edx));
    // 0043213e  01ca                   -add edx, ecx
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.ecx));
    // 00432140  668b12                 -mov dx, word ptr [edx]
    cpu.dx = app->getMemory<x86::reg16>(cpu.edx);
    // 00432143  8a0d844e5500           -mov cl, byte ptr [0x554e84]
    cpu.cl = app->getMemory<x86::reg8>(x86::reg32(5590660) /* 0x554e84 */);
    // 00432149  81e2ffff0000           -and edx, 0xffff
    cpu.edx &= x86::reg32(x86::sreg32(65535 /*0xffff*/));
    // 0043214f  d3e2                   -shl edx, cl
    cpu.edx <<= cpu.cl % 32;
    // 00432151  8b0d784e5500           -mov ecx, dword ptr [0x554e78]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(5590648) /* 0x554e78 */);
    // 00432157  81e7ffff0000           -and edi, 0xffff
    cpu.edi &= x86::reg32(x86::sreg32(65535 /*0xffff*/));
    // 0043215d  21cf                   -and edi, ecx
    cpu.edi &= x86::reg32(x86::sreg32(cpu.ecx));
    // 0043215f  01fa                   -add edx, edi
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.edi));
    // 00432161  39ca                   +cmp edx, ecx
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
    // 00432163  7e02                   -jle 0x432167
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00432167;
    }
    // 00432165  89ca                   -mov edx, ecx
    cpu.edx = cpu.ecx;
L_0x00432167:
    // 00432167  09f3                   -or ebx, esi
    cpu.ebx |= x86::reg32(x86::sreg32(cpu.esi));
    // 00432169  09da                   -or edx, ebx
    cpu.edx |= x86::reg32(x86::sreg32(cpu.ebx));
    // 0043216b  8b580c                 -mov ebx, dword ptr [eax + 0xc]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
    // 0043216e  668913                 -mov word ptr [ebx], dx
    app->getMemory<x86::reg16>(cpu.ebx) = cpu.dx;
    // 00432171  83400c02               +add dword ptr [eax + 0xc], 2
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
    // 00432175  e9fefeffff             -jmp 0x432078
    goto L_0x00432078;
L_0x0043217a:
    // 0043217a  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043217b  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043217c  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043217d  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043217e  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043217f  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00432180  c3                     -ret 
    cpu.esp += 4;
    return;
}

}
