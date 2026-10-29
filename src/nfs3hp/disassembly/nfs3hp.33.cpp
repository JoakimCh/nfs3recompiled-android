#include "nfs3hp.h"
#include <lib/thread.h>

namespace nfs3hp
{

/* sub_4e10e0: native, nfs3hp::ea::unlinkFreeBlock */

/* sub_4e1100: native, nfs3hp::ea::clearMemClasses */

/* sub_4e1120: native, nfs3hp::ea::markMemBlock */

/* sub_4e11e0: native, nfs3hp::ea::memClassOverhead */

/* sub_4e11f0: native, nfs3hp::ea::memBlockOverhead */

/* sub_4e1230: native, nfs3hp::ea::creatememclass */

/* sub_4e14b0: native, nfs3hp::ea::releasememclass */

/* sub_4e1500: native, nfs3hp::ea::getfreememclass */

/* sub_4e1580: native, nfs3hp::ea::largestmem */

/* sub_4e15b0: native, nfs3hp::ea::largestmemclass */

/* sub_4e15d0: native, nfs3hp::ea::memBlockSize */

/* sub_4e15e0: native, nfs3hp::ea::memBlockName */

/* sub_4e1610: native, nfs3hp::ea::memBlockFlags */

/* sub_4e1620: native, nfs3hp::ea::reservememadr */

/* sub_4e1890: native, nfs3hp::ea::purgememadr */

/* sub_4e1990: native, nfs3hp::ea::purgememclass */

/* sub_4e19d0: native, nfs3hp::ea::reservememStdcall */

/* sub_4e19f0: native, nfs3hp::ea::purgememStdcall */

/* sub_4e1a00: native, nfs3hp::StopSoundBufferLambda */

/* sub_4e1a0c: native, nfs3hp::AcquireSoundBufferPositionLambda */

/* sub_4e1a24: native, nfs3hp::AcquireSoundDataLambda */

/* sub_4e1a34: native, nfs3hp::PrintSoundLambda */

/* sub_4e1a64: native, nfs3hp::TraceSoundLambda */

/* sub_4e1a88: native, nfs3hp::abortmessagewrapper */

/* sub_4e1adc: native, nfs3hp::TickSoundLambda */

/* sub_4e1ae4: native, nfs3hp::iSNDconvertsample */

/* sub_4e1d1c: native, nfs3hp::snd::leaveAudioLocks */

/* sub_4e1d48: native, nfs3hp::audiofocushandler */

/* sub_4e1dd4: native, nfs3hp::iSNDloaddll */

/* sub_4e217c: native, nfs3hp::snd::iSNDunloaddll */

/* sub_4e21b0: native, nfs3hp::SNDcaps */

/* sub_4e2224: native, nfs3hp::dead::stub_0x4e2224 */

/* sub_4e2228: native, nfs3hp::snd::SNDsetrate */

/* sub_4e2234: native, nfs3hp::SoundServeHandler */

/* sub_4e225c: native, nfs3hp::snd::iSNDmessageinit */

/* sub_4e2450: native, nfs3hp::snd::iSNDinit */

/* sub_4e253c: native, nfs3hp::snd::iSNDrestore */

/* sub_4e257c: native, nfs3hp::port::soundIdle */

/* sub_4e25c0: native, nfs3hp::port::iSNDstop */

/* sub_4e2630: native, nfs3hp::snd::SNDinit */

/* sub_4e26b4: native, nfs3hp::snd::SNDrestore */

/* sub_4e2754: native, nfs3hp::snd::iSNDverifymode */

/* sub_4e28a0: native, nfs3hp::watcom::unlink */

/* sub_4e28c0: native, nfs3hp::ea::initHandlesDefault */

/* sub_4e28d0: native, nfs3hp::ea::openHandle */

/* sub_4e2ab0: native, nfs3hp::ea::openHandleErrorsAs */

/* sub_4e2ae0: native, nfs3hp::ea::openHandleToWrite */

/* sub_4e2ba0: native, nfs3hp::ea::openMapHandle */

/* sub_4e2da0: native, nfs3hp::ea::closeHandle */

/* sub_4e2de0: native, nfs3hp::ea::readHandle */

/* sub_4e2e20: native, nfs3hp::ea::writeHandle */

/* sub_4e2e60: native, nfs3hp::ea::seekHandle */

/* sub_4e2eb0: native, nfs3hp::ea::isSlash */

/* sub_4e2ebe: native, nfs3hp::ea::notSlash */

/* sub_4e2ed0: native, nfs3hp::ea::volumeRoot */

/* sub_4e2fd0: native, nfs3hp::ea::fullPathName */

/* sub_4e3110: native, nfs3hp::ea::logicalDrives */

/* sub_4e3120: native, nfs3hp::ea::driveOfPath */

/* sub_4e3250: native, nfs3hp::ea::driveLetter */

/* sub_4e32e0: native, nfs3hp::ea::diskFreeBytes */

/* sub_4e3330: native, nfs3hp::ea::driveNumber */

/* sub_4e3340: native, nfs3hp::ea::setDirectory */

/* sub_4e33a0: native, nfs3hp::ea::getDirectory */

/* sub_4e3410: native, nfs3hp::ea::handlesReady */

/* sub_4e3430: native, nfs3hp::ea::initHandles */

/* sub_4e34c0: native, nfs3hp::ea::closeAllHandles */

/* sub_4e3570: native, nfs3hp::ea::takeHandleSlot */

/* sub_4e3600: native, nfs3hp::ea::deleteFile */

/* sub_4e3620: native, nfs3hp::ea::openFileHandle */

/* sub_4e3980: native, nfs3hp::ea::handleInfo */

/* sub_4e3ae0: native, nfs3hp::ea::readHandleBytes */

/* sub_4e3cc0: native, nfs3hp::ea::writeHandleBytes */

/* sub_4e3e60: native, nfs3hp::ea::seekHandleTo */

/* sub_4e3f30: native, nfs3hp::ea::handlePosition */

/* sub_4e3fe0: native, nfs3hp::ea::closeHandleSlot */

/* sub_4e40a0: native, nfs3hp::ea::lockHandleDrive */

/* sub_4e40f0: native, nfs3hp::ea::unlockHandleDrive */

/* sub_4e4140: native, nfs3hp::ea::openMemoryHandle */

/* sub_4e41f0: native, nfs3hp::ea::handleMemory */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x90 */
void Application::sub_4e4230(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004e4230  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004e4231  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004e4232  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004e4233  89d5                   -mov ebp, edx
    cpu.ebp = cpu.edx;
    // 004e4235  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 004e4237  8b15a0455600           -mov edx, dword ptr [0x5645a0]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5653920) /* 0x5645a0 */);
    // 004e423d  f7d3                   -not ebx
    cpu.ebx = ~cpu.ebx;
    // 004e423f  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 004e4241  7417                   -je 0x4e425a
    if (cpu.flags.zf)
    {
        goto L_0x004e425a;
    }
    // 004e4243  85db                   +test ebx, ebx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & cpu.ebx));
    // 004e4245  7c13                   -jl 0x4e425a
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004e425a;
    }
    // 004e4247  3b1d9c455600           +cmp ebx, dword ptr [0x56459c]
    {
        x86::reg32 tmp1 = cpu.ebx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(5653916) /* 0x56459c */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004e424d  7d0b                   -jge 0x4e425a
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004e425a;
    }
    // 004e424f  c1e305                 -shl ebx, 5
    cpu.ebx <<= 5 /*0x5*/ % 32;
    // 004e4252  8d341a                 -lea esi, [edx + ebx]
    cpu.esi = x86::reg32(cpu.edx + cpu.ebx * 1);
    // 004e4255  803e00                 +cmp byte ptr [esi], 0
    {
        x86::reg8 tmp1 = app->getMemory<x86::reg8>(cpu.esi);
        x86::reg8 tmp2 = x86::reg8(x86::sreg8(0 /*0x0*/));
        x86::reg8 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 7);
        cpu.flags.of ^= 1 & (result >> 7);
        cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
        cpu.set_szp(result);
    }
    // 004e4258  7506                   -jne 0x4e4260
    if (!cpu.flags.zf)
    {
        goto L_0x004e4260;
    }
L_0x004e425a:
    // 004e425a  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 004e425c  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e425d  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e425e  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e425f  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004e4260:
    // 004e4260  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004e4261  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004e4262  0fb67601               -movzx esi, byte ptr [esi + 1]
    cpu.esi = x86::reg32(app->getMemory<x86::reg8>(cpu.esi + x86::reg32(1) /* 0x1 */));
    // 004e4266  8b3cb560f79e00         -mov edi, dword ptr [esi*4 + 0x9ef760]
    cpu.edi = app->getMemory<x86::reg32>(x86::reg32(10418016) /* 0x9ef760 */ + cpu.esi * 4);
    // 004e426d  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004e426e  ff15b8445300           -call dword ptr [0x5344b8]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(5457080) /* 0x5344b8 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e4274  6a00                   -push 0
    app->getMemory<x86::reg32>(cpu.esp-4) = 0 /*0x0*/;
    cpu.esp -= 4;
    // 004e4276  2eff15f4455300         -call dword ptr cs:[0x5345f4]
    cpu.ip = app->getMemory<x86::reg32>(cpu.ecs + x86::reg32(5457396) /* 0x5345f4 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e427d  a1a0455600             -mov eax, dword ptr [0x5645a0]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5653920) /* 0x5645a0 */);
    // 004e4282  01d8                   -add eax, ebx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.ebx));
    // 004e4284  83781400               +cmp dword ptr [eax + 0x14], 0
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
    // 004e4288  7543                   -jne 0x4e42cd
    if (!cpu.flags.zf)
    {
        goto L_0x004e42cd;
    }
    // 004e428a  8b4804                 -mov ecx, dword ptr [eax + 4]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 004e428d  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004e428e  2eff15d8455300         -call dword ptr cs:[0x5345d8]
    cpu.ip = app->getMemory<x86::reg32>(cpu.ecs + x86::reg32(5457368) /* 0x5345d8 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e4295  6a00                   -push 0
    app->getMemory<x86::reg32>(cpu.esp-4) = 0 /*0x0*/;
    cpu.esp -= 4;
    // 004e4297  6a00                   -push 0
    app->getMemory<x86::reg32>(cpu.esp-4) = 0 /*0x0*/;
    cpu.esp -= 4;
    // 004e4299  89c7                   -mov edi, eax
    cpu.edi = cpu.eax;
    // 004e429b  a1a0455600             -mov eax, dword ptr [0x5645a0]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5653920) /* 0x5645a0 */);
    // 004e42a0  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004e42a1  8b6c0304               -mov ebp, dword ptr [ebx + eax + 4]
    cpu.ebp = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(4) /* 0x4 */ + cpu.eax * 1);
    // 004e42a5  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004e42a6  2eff15f0455300         -call dword ptr cs:[0x5345f0]
    cpu.ip = app->getMemory<x86::reg32>(cpu.ecs + x86::reg32(5457392) /* 0x5345f0 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e42ad  8b2da0455600           -mov ebp, dword ptr [0x5645a0]
    cpu.ebp = app->getMemory<x86::reg32>(x86::reg32(5653920) /* 0x5645a0 */);
    // 004e42b3  89442b18               -mov dword ptr [ebx + ebp + 0x18], eax
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(24) /* 0x18 */ + cpu.ebp * 1) = cpu.eax;
L_0x004e42b7:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004e42b7  8b04b560f79e00         -mov eax, dword ptr [esi*4 + 0x9ef760]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(10418016) /* 0x9ef760 */ + cpu.esi * 4);
    // 004e42be  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004e42bf  ff1588455300           -call dword ptr [0x534588]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(5457288) /* 0x534588 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e42c5  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 004e42c7  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e42c8  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e42c9  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e42ca  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e42cb  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e42cc  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004e42cd:
    // 004e42cd  31ff                   +xor edi, edi
    cpu.clear_co();
    cpu.set_szp((cpu.edi ^= x86::reg32(x86::sreg32(cpu.edi))));
    // 004e42cf  ebe6                   -jmp 0x4e42b7
    goto L_0x004e42b7;
}

/* sub_4e42e0: native, nfs3hp::dead::stub_0x4e42e0 */

/* align: skip 0x90 */
void Application::sub_4e4320(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004e4320  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004e4321  8b15a0455600           -mov edx, dword ptr [0x5645a0]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5653920) /* 0x5645a0 */);
    // 004e4327  f7d0                   -not eax
    cpu.eax = ~cpu.eax;
    // 004e4329  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 004e432b  741d                   -je 0x4e434a
    if (cpu.flags.zf)
    {
        goto L_0x004e434a;
    }
    // 004e432d  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004e432f  7c19                   -jl 0x4e434a
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004e434a;
    }
    // 004e4331  3b059c455600           +cmp eax, dword ptr [0x56459c]
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(5653916) /* 0x56459c */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004e4337  7d11                   -jge 0x4e434a
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004e434a;
    }
    // 004e4339  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004e433b  a1a0455600             -mov eax, dword ptr [0x5645a0]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5653920) /* 0x5645a0 */);
    // 004e4340  c1e205                 -shl edx, 5
    cpu.edx <<= 5 /*0x5*/ % 32;
    // 004e4343  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 004e4345  803800                 +cmp byte ptr [eax], 0
    {
        x86::reg8 tmp1 = app->getMemory<x86::reg8>(cpu.eax);
        x86::reg8 tmp2 = x86::reg8(x86::sreg8(0 /*0x0*/));
        x86::reg8 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 7);
        cpu.flags.of ^= 1 & (result >> 7);
        cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
        cpu.set_szp(result);
    }
    // 004e4348  7504                   -jne 0x4e434e
    if (!cpu.flags.zf)
    {
        goto L_0x004e434e;
    }
L_0x004e434a:
    // 004e434a  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 004e434c  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e434d  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004e434e:
    // 004e434e  8a4001                 -mov al, byte ptr [eax + 1]
    cpu.al = app->getMemory<x86::reg8>(cpu.eax + x86::reg32(1) /* 0x1 */);
    // 004e4351  25ff000000             -and eax, 0xff
    cpu.eax &= x86::reg32(x86::sreg32(255 /*0xff*/));
    // 004e4356  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e4357  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 */
void Application::sub_4e4360(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004e4360  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004e4361  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004e4362  83ec0c                 -sub esp, 0xc
    (cpu.esp) -= x86::reg32(x86::sreg32(12 /*0xc*/));
    // 004e4365  8d4c2408               -lea ecx, [esp + 8]
    cpu.ecx = x86::reg32(cpu.esp + x86::reg32(8) /* 0x8 */);
    // 004e4369  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004e436a  8d5c2408               -lea ebx, [esp + 8]
    cpu.ebx = x86::reg32(cpu.esp + x86::reg32(8) /* 0x8 */);
    // 004e436e  8d542404               -lea edx, [esp + 4]
    cpu.edx = x86::reg32(cpu.esp + x86::reg32(4) /* 0x4 */);
    // 004e4372  e839e7ffff             -call 0x4e2ab0
    cpu.esp -= 4;
    nfs3hp::ea::openHandleErrorsAs(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e4377  8b1424                 -mov edx, dword ptr [esp]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    // 004e437a  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 004e437c  750a                   -jne 0x4e4388
    if (!cpu.flags.zf)
    {
        goto L_0x004e4388;
    }
    // 004e437e  8b442408               -mov eax, dword ptr [esp + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(8) /* 0x8 */);
    // 004e4382  83c40c                 -add esp, 0xc
    (cpu.esp) += x86::reg32(x86::sreg32(12 /*0xc*/));
    // 004e4385  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e4386  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e4387  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004e4388:
    // 004e4388  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004e438a  e811eaffff             -call 0x4e2da0
    cpu.esp -= 4;
    nfs3hp::ea::closeHandle(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e438f  8b442408               -mov eax, dword ptr [esp + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(8) /* 0x8 */);
    // 004e4393  83c40c                 -add esp, 0xc
    (cpu.esp) += x86::reg32(x86::sreg32(12 /*0xc*/));
    // 004e4396  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e4397  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e4398  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x90 */
void Application::sub_4e43a0(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004e43a0  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004e43a1  ba01000000             -mov edx, 1
    cpu.edx = 1 /*0x1*/;
    // 004e43a6  e8b5ffffff             -call 0x4e4360
    cpu.esp -= 4;
    sub_4e4360(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e43ab  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e43ac  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_4e43b0: native, nfs3hp::dead::stub_0x4e43b0 */

/* sub_4e43c0: native, nfs3hp::dead::stub_0x4e43c0 */

/* sub_4e43d0: native, nfs3hp::dead::stub_0x4e43d0 */

/* sub_4e4420: native, nfs3hp::snd::initStreamStruct */

/* sub_4e45d0: native, nfs3hp::snd::initStreamStructSecond */

/* sub_4e45e0: native, nfs3hp::snd::initStreamStructFirst */

/* sub_4e45f0: native, nfs3hp::snd::initStream */

/* sub_4e4780: native, nfs3hp::snd::initStreamSecond */

/* sub_4e4790: native, nfs3hp::snd::initStreamFirst */

/* align: skip 0x8d 0x40 0x00 */
void Application::sub_4e47a0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004e47a0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004e47a1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004e47a2  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004e47a3  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004e47a4  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004e47a5  83ec20                 -sub esp, 0x20
    (cpu.esp) -= x86::reg32(x86::sreg32(32 /*0x20*/));
    // 004e47a8  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 004e47aa  89d7                   -mov edi, edx
    cpu.edi = cpu.edx;
    // 004e47ac  e85f9b0000             -call 0x4ee310
    cpu.esp -= 4;
    nfs3hp::watcom::strcmp(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e47b1  8d4c2408               -lea ecx, [esp + 8]
    cpu.ecx = x86::reg32(cpu.esp + x86::reg32(8) /* 0x8 */);
    // 004e47b5  89c5                   -mov ebp, eax
    cpu.ebp = cpu.eax;
    // 004e47b7  8944241c               -mov dword ptr [esp + 0x1c], eax
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(28) /* 0x1c */) = cpu.eax;
    // 004e47bb  8d442418               -lea eax, [esp + 0x18]
    cpu.eax = x86::reg32(cpu.esp + x86::reg32(24) /* 0x18 */);
    // 004e47bf  8d5c2410               -lea ebx, [esp + 0x10]
    cpu.ebx = x86::reg32(cpu.esp + x86::reg32(16) /* 0x10 */);
    // 004e47c3  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004e47c4  8d542404               -lea edx, [esp + 4]
    cpu.edx = x86::reg32(cpu.esp + x86::reg32(4) /* 0x4 */);
    // 004e47c8  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004e47ca  e8a1ca0100             -call 0x501270
    cpu.esp -= 4;
    nfs3hp::ea::openBlockHandle(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e47cf  85ed                   +test ebp, ebp
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebp & cpu.ebp));
    // 004e47d1  0f85bd000000           -jne 0x4e4894
    if (!cpu.flags.zf)
    {
        goto L_0x004e4894;
    }
    // 004e47d7  8b0424                 -mov eax, dword ptr [esp]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp);
    // 004e47da  89442404               -mov dword ptr [esp + 4], eax
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(4) /* 0x4 */) = cpu.eax;
    // 004e47de  8b442410               -mov eax, dword ptr [esp + 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(16) /* 0x10 */);
    // 004e47e2  89442414               -mov dword ptr [esp + 0x14], eax
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(20) /* 0x14 */) = cpu.eax;
    // 004e47e6  8b442408               -mov eax, dword ptr [esp + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(8) /* 0x8 */);
    // 004e47ea  8944240c               -mov dword ptr [esp + 0xc], eax
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(12) /* 0xc */) = cpu.eax;
L_0x004e47ee:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004e47ee  8b442408               -mov eax, dword ptr [esp + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(8) /* 0x8 */);
    // 004e47f2  2d00200000             -sub eax, 0x2000
    (cpu.eax) -= x86::reg32(x86::sreg32(8192 /*0x2000*/));
    // 004e47f7  662500e0               -and ax, 0xe000
    cpu.ax &= x86::reg16(x86::sreg16(57344 /*0xe000*/));
    // 004e47fb  89442408               -mov dword ptr [esp + 8], eax
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(8) /* 0x8 */) = cpu.eax;
    // 004e47ff  3d00000400             +cmp eax, 0x40000
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(262144 /*0x40000*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004e4804  0f8ea7000000           -jle 0x4e48b1
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004e48b1;
    }
    // 004e480a  c744240800000400       -mov dword ptr [esp + 8], 0x40000
    app->getMemory<x86::reg32>(cpu.esp + x86::reg32(8) /* 0x8 */) = 262144 /*0x40000*/;
L_0x004e4812:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004e4812  b9d0a35400             -mov ecx, 0x54a3d0
    cpu.ecx = 5546960 /*0x54a3d0*/;
    // 004e4817  bb2ca55400             -mov ebx, 0x54a52c
    cpu.ebx = 5547308 /*0x54a52c*/;
    // 004e481c  bef8010000             -mov esi, 0x1f8
    cpu.esi = 504 /*0x1f8*/;
    // 004e4821  ba00200000             -mov edx, 0x2000
    cpu.edx = 8192 /*0x2000*/;
    // 004e4826  b89ca55400             -mov eax, 0x54a59c
    cpu.eax = 5547420 /*0x54a59c*/;
    // 004e482b  890d90215500           -mov dword ptr [0x552190], ecx
    app->getMemory<x86::reg32>(x86::reg32(5579152) /* 0x552190 */) = cpu.ecx;
    // 004e4831  891d94215500           -mov dword ptr [0x552194], ebx
    app->getMemory<x86::reg32>(x86::reg32(5579156) /* 0x552194 */) = cpu.ebx;
    // 004e4837  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
    // 004e4839  893598215500           -mov dword ptr [0x552198], esi
    app->getMemory<x86::reg32>(x86::reg32(5579160) /* 0x552198 */) = cpu.esi;
    // 004e483f  e8dccdffff             -call 0x4e1620
    cpu.esp -= 4;
    nfs3hp::ea::reservememadr(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e4844  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 004e4846  b800200000             -mov eax, 0x2000
    cpu.eax = 8192 /*0x2000*/;
    // 004e484b  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004e484d  8b7c2418               -mov edi, dword ptr [esp + 0x18]
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(24) /* 0x18 */);
    // 004e4851  c1fa1f                 -sar edx, 0x1f
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (31 /*0x1f*/ % 32));
    // 004e4854  f7ff                   -idiv edi
    {
        x86::sreg64 tmp = x86::sreg64(cpu.edx_eax);
        x86::sreg32 d = x86::sreg32(cpu.edi);
        cpu.edx_eax = x86::reg64(tmp / d);
        cpu.edx = x86::reg32(tmp % d);
    }
    // 004e4856  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
L_0x004e4858:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004e4858  8b0424                 -mov eax, dword ptr [esp]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp);
    // 004e485b  89f3                   -mov ebx, esi
    cpu.ebx = cpu.esi;
    // 004e485d  89ca                   -mov edx, ecx
    cpu.edx = cpu.ecx;
    // 004e485f  e84ccb0100             -call 0x5013b0
    cpu.esp -= 4;
    nfs3hp::ea::readBlockHandle(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e4864  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004e4866  74f0                   -je 0x4e4858
    if (cpu.flags.zf)
    {
        goto L_0x004e4858;
    }
    // 004e4868  e8e3bd0000             -call 0x4f0650
    cpu.esp -= 4;
    sub_4f0650(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e486d  8b7c2408               -mov edi, dword ptr [esp + 8]
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(8) /* 0x8 */);
    // 004e4871  85ff                   +test edi, edi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edi & cpu.edi));
    // 004e4873  0f8e8b000000           -jle 0x4e4904
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004e4904;
    }
    // 004e4879  31ed                   -xor ebp, ebp
    cpu.ebp ^= x86::reg32(x86::sreg32(cpu.ebp));
L_0x004e487b:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004e487b  8b0424                 -mov eax, dword ptr [esp]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp);
    // 004e487e  89f3                   -mov ebx, esi
    cpu.ebx = cpu.esi;
    // 004e4880  89ca                   -mov edx, ecx
    cpu.edx = cpu.ecx;
    // 004e4882  e829cb0100             -call 0x5013b0
    cpu.esp -= 4;
    nfs3hp::ea::readBlockHandle(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e4887  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004e4889  756b                   -jne 0x4e48f6
    if (!cpu.flags.zf)
    {
        goto L_0x004e48f6;
    }
    // 004e488b  89e8                   -mov eax, ebp
    cpu.eax = cpu.ebp;
    // 004e488d  e89e2d0000             -call 0x4e7630
    cpu.esp -= 4;
    nfs3hp::snd::runSystemTasks(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e4892  ebe7                   -jmp 0x4e487b
    goto L_0x004e487b;
L_0x004e4894:
    // 004e4894  8d442418               -lea eax, [esp + 0x18]
    cpu.eax = x86::reg32(cpu.esp + x86::reg32(24) /* 0x18 */);
    // 004e4898  8d4c240c               -lea ecx, [esp + 0xc]
    cpu.ecx = x86::reg32(cpu.esp + x86::reg32(12) /* 0xc */);
    // 004e489c  8d5c2414               -lea ebx, [esp + 0x14]
    cpu.ebx = x86::reg32(cpu.esp + x86::reg32(20) /* 0x14 */);
    // 004e48a0  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004e48a1  8d542408               -lea edx, [esp + 8]
    cpu.edx = x86::reg32(cpu.esp + x86::reg32(8) /* 0x8 */);
    // 004e48a5  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 004e48a7  e8c4c90100             -call 0x501270
    cpu.esp -= 4;
    nfs3hp::ea::openBlockHandle(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e48ac  e93dffffff             -jmp 0x4e47ee
    goto L_0x004e47ee;
L_0x004e48b1:
    // 004e48b1  3d204e0000             +cmp eax, 0x4e20
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(20000 /*0x4e20*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004e48b6  0f8d56ffffff           -jge 0x4e4812
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004e4812;
    }
    // 004e48bc  68204e0000             -push 0x4e20
    app->getMemory<x86::reg32>(cpu.esp-4) = 20000 /*0x4e20*/;
    cpu.esp -= 4;
    // 004e48c1  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004e48c2  bbd0a35400             -mov ebx, 0x54a3d0
    cpu.ebx = 5546960 /*0x54a3d0*/;
    // 004e48c7  bf2ca55400             -mov edi, 0x54a52c
    cpu.edi = 5547308 /*0x54a52c*/;
    // 004e48cc  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004e48cd  bdf7010000             -mov ebp, 0x1f7
    cpu.ebp = 503 /*0x1f7*/;
    // 004e48d2  891d90215500           -mov dword ptr [0x552190], ebx
    app->getMemory<x86::reg32>(x86::reg32(5579152) /* 0x552190 */) = cpu.ebx;
    // 004e48d8  683ca55400             -push 0x54a53c
    app->getMemory<x86::reg32>(cpu.esp-4) = 5547324 /*0x54a53c*/;
    cpu.esp -= 4;
    // 004e48dd  893d94215500           -mov dword ptr [0x552194], edi
    app->getMemory<x86::reg32>(x86::reg32(5579156) /* 0x552194 */) = cpu.edi;
    // 004e48e3  892d98215500           -mov dword ptr [0x552198], ebp
    app->getMemory<x86::reg32>(x86::reg32(5579160) /* 0x552198 */) = cpu.ebp;
    // 004e48e9  e822c7f1ff             -call 0x401010
    cpu.esp -= 4;
    nfs3hp::Error(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e48ee  83c410                 +add esp, 0x10
    {
        x86::reg32& tmp1 = cpu.esp;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(16 /*0x10*/));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 004e48f1  e91cffffff             -jmp 0x4e4812
    goto L_0x004e4812;
L_0x004e48f6:
    // 004e48f6  81ef00200000           -sub edi, 0x2000
    (cpu.edi) -= x86::reg32(x86::sreg32(8192 /*0x2000*/));
    // 004e48fc  85ff                   +test edi, edi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edi & cpu.edi));
    // 004e48fe  0f8f77ffffff           -jg 0x4e487b
    if (!cpu.flags.zf && (cpu.flags.sf == cpu.flags.of))
    {
        goto L_0x004e487b;
    }
L_0x004e4904:
    // 004e4904  e847bd0000             -call 0x4f0650
    cpu.esp -= 4;
    sub_4f0650(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e4909  89c7                   -mov edi, eax
    cpu.edi = cpu.eax;
    // 004e490b  31ed                   -xor ebp, ebp
    cpu.ebp ^= x86::reg32(x86::sreg32(cpu.ebp));
L_0x004e490d:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004e490d  8b442404               -mov eax, dword ptr [esp + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(4) /* 0x4 */);
    // 004e4911  89f3                   -mov ebx, esi
    cpu.ebx = cpu.esi;
    // 004e4913  89ca                   -mov edx, ecx
    cpu.edx = cpu.ecx;
    // 004e4915  e896ca0100             -call 0x5013b0
    cpu.esp -= 4;
    nfs3hp::ea::readBlockHandle(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e491a  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004e491c  7509                   -jne 0x4e4927
    if (!cpu.flags.zf)
    {
        goto L_0x004e4927;
    }
    // 004e491e  89e8                   -mov eax, ebp
    cpu.eax = cpu.ebp;
    // 004e4920  e80b2d0000             -call 0x4e7630
    cpu.esp -= 4;
    nfs3hp::snd::runSystemTasks(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e4925  ebe6                   -jmp 0x4e490d
    goto L_0x004e490d;
L_0x004e4927:
    // 004e4927  e824bd0000             -call 0x4f0650
    cpu.esp -= 4;
    sub_4f0650(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e492c  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 004e492e  8b0424                 -mov eax, dword ptr [esp]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp);
    // 004e4931  e86aca0100             -call 0x5013a0
    cpu.esp -= 4;
    nfs3hp::ea::closeBlockHandle(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e4936  837c241c00             +cmp dword ptr [esp + 0x1c], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(28) /* 0x1c */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004e493b  7409                   -je 0x4e4946
    if (cpu.flags.zf)
    {
        goto L_0x004e4946;
    }
    // 004e493d  8b442404               -mov eax, dword ptr [esp + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(4) /* 0x4 */);
    // 004e4941  e85aca0100             -call 0x5013a0
    cpu.esp -= 4;
    nfs3hp::ea::closeBlockHandle(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x004e4946:
    // 004e4946  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004e4948  e843cfffff             -call 0x4e1890
    cpu.esp -= 4;
    nfs3hp::ea::purgememadr(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e494d  8d04bd00000000         -lea eax, [edi*4]
    cpu.eax = x86::reg32(cpu.edi * 4);
    // 004e4954  8d1407                 -lea edx, [edi + eax]
    cpu.edx = x86::reg32(cpu.edi + cpu.eax * 1);
    // 004e4957  01d2                   -add edx, edx
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.edx));
    // 004e4959  c1e210                 -shl edx, 0x10
    cpu.edx <<= 16 /*0x10*/ % 32;
    // 004e495c  8b4c2408               -mov ecx, dword ptr [esp + 8]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(8) /* 0x8 */);
    // 004e4960  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004e4962  c1fa1f                 -sar edx, 0x1f
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (31 /*0x1f*/ % 32));
    // 004e4965  f7f9                   -idiv ecx
    {
        x86::sreg64 tmp = x86::sreg64(cpu.edx_eax);
        x86::sreg32 d = x86::sreg32(cpu.ecx);
        cpu.edx_eax = x86::reg64(tmp / d);
        cpu.edx = x86::reg32(tmp % d);
    }
    // 004e4967  a3e0f79e00             -mov dword ptr [0x9ef7e0], eax
    app->getMemory<x86::reg32>(x86::reg32(10418144) /* 0x9ef7e0 */) = cpu.eax;
    // 004e496c  83f801                 +cmp eax, 1
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
    // 004e496f  7d0a                   -jge 0x4e497b
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004e497b;
    }
    // 004e4971  c705e0f79e0001000000   -mov dword ptr [0x9ef7e0], 1
    app->getMemory<x86::reg32>(x86::reg32(10418144) /* 0x9ef7e0 */) = 1 /*0x1*/;
L_0x004e497b:
    // 004e497b  b80000e803             -mov eax, 0x3e80000
    cpu.eax = 65536000 /*0x3e80000*/;
    // 004e4980  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004e4982  8b0de0f79e00           -mov ecx, dword ptr [0x9ef7e0]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(10418144) /* 0x9ef7e0 */);
    // 004e4988  c1fa1f                 -sar edx, 0x1f
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (31 /*0x1f*/ % 32));
    // 004e498b  f7f9                   -idiv ecx
    {
        x86::sreg64 tmp = x86::sreg64(cpu.edx_eax);
        x86::sreg32 d = x86::sreg32(cpu.ecx);
        cpu.edx_eax = x86::reg64(tmp / d);
        cpu.edx = x86::reg32(tmp % d);
    }
    // 004e498d  a3e4f79e00             -mov dword ptr [0x9ef7e4], eax
    app->getMemory<x86::reg32>(x86::reg32(10418148) /* 0x9ef7e4 */) = cpu.eax;
    // 004e4992  8b442408               -mov eax, dword ptr [esp + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(8) /* 0x8 */);
    // 004e4996  8b4c2408               -mov ecx, dword ptr [esp + 8]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(8) /* 0x8 */);
    // 004e499a  c1f802                 -sar eax, 2
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (2 /*0x2*/ % 32));
    // 004e499d  01c1                   -add ecx, eax
    (cpu.ecx) += x86::reg32(x86::sreg32(cpu.eax));
    // 004e499f  8d04bd00000000         -lea eax, [edi*4]
    cpu.eax = x86::reg32(cpu.edi * 4);
    // 004e49a6  8d1407                 -lea edx, [edi + eax]
    cpu.edx = x86::reg32(cpu.edi + cpu.eax * 1);
    // 004e49a9  01d2                   -add edx, edx
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.edx));
    // 004e49ab  c1e210                 -shl edx, 0x10
    cpu.edx <<= 16 /*0x10*/ % 32;
    // 004e49ae  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004e49b0  c1fa1f                 -sar edx, 0x1f
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (31 /*0x1f*/ % 32));
    // 004e49b3  f7f9                   -idiv ecx
    {
        x86::sreg64 tmp = x86::sreg64(cpu.edx_eax);
        x86::sreg32 d = x86::sreg32(cpu.ecx);
        cpu.edx_eax = x86::reg64(tmp / d);
        cpu.edx = x86::reg32(tmp % d);
    }
    // 004e49b5  a3a8455600             -mov dword ptr [0x5645a8], eax
    app->getMemory<x86::reg32>(x86::reg32(5653928) /* 0x5645a8 */) = cpu.eax;
    // 004e49ba  3dda000000             +cmp eax, 0xda
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(218 /*0xda*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004e49bf  7f25                   -jg 0x4e49e6
    if (!cpu.flags.zf && (cpu.flags.sf == cpu.flags.of))
    {
        goto L_0x004e49e6;
    }
    // 004e49c1  3da3000000             +cmp eax, 0xa3
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(163 /*0xa3*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004e49c6  7c2a                   -jl 0x4e49f2
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004e49f2;
    }
L_0x004e49c8:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004e49c8  8d049d00000000         -lea eax, [ebx*4]
    cpu.eax = x86::reg32(cpu.ebx * 4);
    // 004e49cf  01d8                   -add eax, ebx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.ebx));
    // 004e49d1  01c0                   -add eax, eax
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.eax));
    // 004e49d3  a3ac455600             -mov dword ptr [0x5645ac], eax
    app->getMemory<x86::reg32>(x86::reg32(5653932) /* 0x5645ac */) = cpu.eax;
    // 004e49d8  a1e4f79e00             -mov eax, dword ptr [0x9ef7e4]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(10418148) /* 0x9ef7e4 */);
    // 004e49dd  83c420                 +add esp, 0x20
    {
        x86::reg32& tmp1 = cpu.esp;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(32 /*0x20*/));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 004e49e0  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e49e1  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e49e2  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e49e3  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e49e4  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e49e5  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004e49e6:
    // 004e49e6  c705a8455600da000000   -mov dword ptr [0x5645a8], 0xda
    app->getMemory<x86::reg32>(x86::reg32(5653928) /* 0x5645a8 */) = 218 /*0xda*/;
    // 004e49f0  ebd6                   -jmp 0x4e49c8
    goto L_0x004e49c8;
L_0x004e49f2:
    // 004e49f2  b901000000             -mov ecx, 1
    cpu.ecx = 1 /*0x1*/;
    // 004e49f7  890da8455600           -mov dword ptr [0x5645a8], ecx
    app->getMemory<x86::reg32>(x86::reg32(5653928) /* 0x5645a8 */) = cpu.ecx;
    // 004e49fd  890d98715600           -mov dword ptr [0x567198], ecx
    app->getMemory<x86::reg32>(x86::reg32(5665176) /* 0x567198 */) = cpu.ecx;
    // 004e4a03  ebc3                   -jmp 0x4e49c8
    goto L_0x004e49c8;
}

/* sub_4e4a10: native, nfs3hp::dead::stub_0x4e4a10 */

/* sub_4e4a30: native, nfs3hp::snd::deleteStreamStruct */

/* sub_4e4b50: native, nfs3hp::snd::deleteStream */

/* sub_4e4c60: native, nfs3hp::snd::streamCommand */

/* sub_4e4d70: native, nfs3hp::snd::purgeStreamCommand */

/* sub_4e4ea0: native, nfs3hp::snd::streamOpen */

}
