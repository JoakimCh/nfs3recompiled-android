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

/* sub_42f550: native, nfs3hp::collide::findContact */

/* sub_42f8c0: native, nfs3hp::collide::contactNormal */

/* sub_42fe10: native, nfs3hp::collide::pushCarsApart */

/* sub_42fee0: native, nfs3hp::collide::separateCars */

/* sub_430210: native, nfs3hp::collide::polygonEdgeNormal */

/* sub_430350: native, nfs3hp::collide::clearOfWall */

/* sub_4304b0: native, nfs3hp::collide::carAgainstWalls */

/* sub_430c80: native, nfs3hp::collide::collideCars */

/* sub_430cd0: native, nfs3hp::collide::clearCarList */

/* sub_430ce0: native, nfs3hp::collide::objectInReach */

/* sub_430da0: native, nfs3hp::collide::carAgainstObjects */

/* sub_4310c0: native, nfs3hp::collide::addCarToList */

/* sub_4311d0: native, nfs3hp::collide::carCollisions */

/* sub_431250: native, nfs3hp::collide::distanceSquared */

/* sub_431280: native, nfs3hp::collide::nearestPoint */

/* sub_431320: native, nfs3hp::collide::openCollFile */

/* sub_4313b0: native, nfs3hp::collide::closeCollFile */

/* sub_4313d0: native, nfs3hp::collide::collFileSize */

/* sub_4313e0: native, nfs3hp::collide::readCollFile */

/* sub_431410: native, nfs3hp::collide::collFileCount */

/* sub_431420: native, nfs3hp::collide::collChunk */

/* sub_431430: native, nfs3hp::collide::playerControls */

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

/* sub_4318c0: native, nfs3hp::collide::forgetRenderStates */

/* sub_431900: native, nfs3hp::graphics::setRenderState */

/* sub_431aa0: native, nfs3hp::collide::statesForText */

/* sub_431af0: native, nfs3hp::collide::statesForPictures */

/* sub_431b40: native, nfs3hp::collide::statesForHud */

/* sub_431bc0: native, nfs3hp::collide::statesForScreens */

/* sub_431c20: native, nfs3hp::collide::passLayerNothing */

/* sub_431c30: native, nfs3hp::collide::passSecondLayer */

/* sub_431c40: native, nfs3hp::collide::passFirstLayer */

/* sub_431c50: native, nfs3hp::collide::makeBlendTables */

/* sub_431d50: native, nfs3hp::collide::blendSpan */

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
