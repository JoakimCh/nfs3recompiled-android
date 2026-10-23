#include "nfs3hp.h"
#include <lib/thread.h>

namespace nfs3hp
{
// Port (tools/apply_native_frontend.py): defined in native_frontend_cars.cpp.
bool carMenuMusicBack(win32::WinApplication* app, x86::CPU& cpu);

/* sub_4103a0: native, nfs3hp::snd::musicAfterSetting */

/* sub_410460: native, nfs3hp::snd::musicMenuSix */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x8d 0x40 0x00 */
void Application::sub_4104b0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (carMenuMusicBack(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 004104b0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004104b1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004104b2  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004104b3  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004104b4  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004104b6  833d9425550000         +cmp dword ptr [0x552594], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5580180) /* 0x552594 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004104bd  742a                   -je 0x4104e9
    if (cpu.flags.zf)
    {
        goto L_0x004104e9;
    }
    // 004104bf  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 004104c1  8b1decbb6f00           -mov ebx, dword ptr [0x6fbbec]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(7322604) /* 0x6fbbec */);
    // 004104c7  890d94255500           -mov dword ptr [0x552594], ecx
    app->getMemory<x86::reg32>(x86::reg32(5580180) /* 0x552594 */) = cpu.ecx;
    // 004104cd  83fb06                 +cmp ebx, 6
    {
        x86::reg32 tmp1 = cpu.ebx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(6 /*0x6*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004104d0  7417                   -je 0x4104e9
    if (cpu.flags.zf)
    {
        goto L_0x004104e9;
    }
    // 004104d2  e8f9040000             -call 0x4109d0
    cpu.esp -= 4;
    nfs3hp::snd::musicStop(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004104d7  b816000000             -mov eax, 0x16
    cpu.eax = 22 /*0x16*/;
    // 004104dc  8b15e8bb6f00           -mov edx, dword ptr [0x6fbbe8]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(7322600) /* 0x6fbbe8 */);
    // 004104e2  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
    // 004104e4  e807000000             -call 0x4104f0
    cpu.esp -= 4;
    nfs3hp::snd::musicStart(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x004104e9:
    // 004104e9  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004104ea  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004104eb  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004104ec  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004104ed  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_4104f0: native, nfs3hp::snd::musicStart */

/* sub_4107c0: native, nfs3hp::snd::raceMusicStart */

/* sub_4109d0: native, nfs3hp::snd::musicStop */

/* align: skip 0x8d 0x44 0x20 0x00 */
void Application::sub_410a40(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00410a40  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00410a41  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00410a42  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00410a43  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00410a45  8b1554bb6f00           -mov edx, dword ptr [0x6fbb54]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(7322452) /* 0x6fbb54 */);
    // 00410a4b  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 00410a4d  7540                   -jne 0x410a8f
    if (!cpu.flags.zf)
    {
        goto L_0x00410a8f;
    }
    // 00410a4f  833da025550000         +cmp dword ptr [0x5525a0], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5580192) /* 0x5525a0 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00410a56  7437                   -je 0x410a8f
    if (cpu.flags.zf)
    {
        goto L_0x00410a8f;
    }
    // 00410a58  833d1029550000         +cmp dword ptr [0x552910], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5581072) /* 0x552910 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00410a5f  742e                   -je 0x410a8f
    if (cpu.flags.zf)
    {
        goto L_0x00410a8f;
    }
    // 00410a61  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00410a63  e8f8800d00             -call 0x4e8b60
    cpu.esp -= 4;
    nfs3hp::snd::SNDstreamvol(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00410a68  e8bb700d00             -call 0x4e7b28
    cpu.esp -= 4;
    nfs3hp::snd::SNDstreampurge(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00410a6d  e816690d00             -call 0x4e7388
    cpu.esp -= 4;
    nfs3hp::snd::SNDpathrestore(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00410a72  8b3d500a5700           -mov edi, dword ptr [0x570a50]
    cpu.edi = app->getMemory<x86::reg32>(x86::reg32(5704272) /* 0x570a50 */);
    // 00410a78  8915a0255500           -mov dword ptr [0x5525a0], edx
    app->getMemory<x86::reg32>(x86::reg32(5580192) /* 0x5525a0 */) = cpu.edx;
    // 00410a7e  85ff                   +test edi, edi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edi & cpu.edi));
    // 00410a80  740d                   -je 0x410a8f
    if (cpu.flags.zf)
    {
        goto L_0x00410a8f;
    }
    // 00410a82  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 00410a84  e8070e0d00             -call 0x4e1890
    cpu.esp -= 4;
    sub_4e1890(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00410a89  8915500a5700           -mov dword ptr [0x570a50], edx
    app->getMemory<x86::reg32>(x86::reg32(5704272) /* 0x570a50 */) = cpu.edx;
L_0x00410a8f:
    // 00410a8f  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00410a90  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00410a91  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00410a92  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_410aa0: native, nfs3hp::snd::musicStreamEnd */

/* sub_410ad0: native, nfs3hp::snd::banksFree */

/* sub_410b20: native, nfs3hp::snd::banksRemove */

/* sub_410b50: native, nfs3hp::snd::bankLoad */

/* align: skip 0x8d 0x40 0x00 0x8b 0xc9 */
void Application::sub_410c30(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00410c30  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00410c31  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00410c33  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00410c34  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_410c40: native, nfs3hp::snd::listenerMove */

/* sub_410cb0: native, nfs3hp::snd::sourceDistance */

/* sub_410d30: native, nfs3hp::snd::sourceAngle */

/* sub_410dc0: native, nfs3hp::snd::carAngle */

/* sub_410e30: native, nfs3hp::snd::trackSounds */

/* sub_411410: native, nfs3hp::snd::raceSoundTick */

/* sub_411620: native, nfs3hp::snd::sourceReset */

/* sub_411680: native, nfs3hp::snd::sourcesReset */

/* sub_411750: native, nfs3hp::snd::copChaseSet */

/* sub_4117a0: native, nfs3hp::snd::playerCarSound */

/* sub_411c50: native, nfs3hp::snd::copSiren */

/* sub_411ca0: native, nfs3hp::snd::copSirenStop */

/* sub_411cb0: native, nfs3hp::snd::copEngine */

/* sub_411da0: native, nfs3hp::snd::copEngineStop */

/* sub_411db0: native, nfs3hp::snd::copDistance */

/* sub_411e20: native, nfs3hp::snd::copsCloseness */

/* sub_411e60: native, nfs3hp::snd::copCarSound */

/* sub_4121b0: native, nfs3hp::snd::copRemove */

/* sub_412220: native, nfs3hp::snd::copSourcesPick */

/* sub_4124d0: native, nfs3hp::snd::placeAhead */

/* sub_412620: native, nfs3hp::snd::placeAcross */

/* sub_4127b0: native, nfs3hp::snd::carFlagTest */

/* sub_4127c0: native, nfs3hp::snd::carRadio */

/* sub_412880: native, nfs3hp::snd::playerCopRadio */

/* sub_4129a0: native, nfs3hp::snd::raceValue */

/* sub_4129b0: native, nfs3hp::snd::soundNothing */

/* sub_4129c0: native, nfs3hp::snd::raceSoundInit */

/* sub_412b50: native, nfs3hp::snd::raceSoundEnd */

/* sub_412be0: native, nfs3hp::snd::copLineFor */

/* sub_412d60: native, nfs3hp::snd::raceAnnouncer */

/* sub_4136e0: native, nfs3hp::snd::raceBankLoad */

/* sub_413750: native, nfs3hp::snd::voiceBankLoad */

/* sub_4138e0: native, nfs3hp::snd::carBankLoad */

/* sub_413bc0: native, nfs3hp::snd::raceBanksLoad */

/* sub_414800: native, nfs3hp::snd::slotsEmpty */

/* sub_414830: native, nfs3hp::snd::engineSoundsStart */

/* sub_414940: native, nfs3hp::snd::crashPitch */

/* sub_4149e0: native, nfs3hp::snd::crashEffect */

/* sub_414d70: native, nfs3hp::snd::scrapeEffect */

/* sub_414e10: native, nfs3hp::snd::farEffectAim */

/* sub_414ef0: native, nfs3hp::snd::farEffectPlay */

/* sub_414f60: native, nfs3hp::snd::farEffectTick */

/* sub_414f90: native, nfs3hp::snd::crowdEffect */

/* sub_415010: native, nfs3hp::snd::carEffectFifteen */

/* sub_415050: native, nfs3hp::snd::zoneSound */

/* sub_415210: native, nfs3hp::snd::scenerySounds */

/* sub_416d90: native, nfs3hp::snd::carKnock */

/* sub_416f60: native, nfs3hp::port::slotStop */

/* sub_416fc0: native, nfs3hp::port::slotEffect */

/* sub_417080: native, nfs3hp::port::slotPlay */

/* sub_417390: native, nfs3hp::snd::carEngine */

/* sub_4179d0: native, nfs3hp::snd::noiseBySpeed */

/* sub_417b80: native, nfs3hp::snd::noiseByDistance */

/* sub_417c00: native, nfs3hp::snd::playerNoise */

/* sub_417c70: native, nfs3hp::snd::playerNoiseStop */

/* sub_417ca0: native, nfs3hp::snd::sirenIsOn */

/* sub_417cb0: native, nfs3hp::snd::sirenFirstTone */

/* sub_417d00: native, nfs3hp::snd::sirenFirstDone */

/* align: skip 0x8d 0x44 0x20 0x00 */
void Application::sub_417d50(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00417d50  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00417d51  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00417d52  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00417d53  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00417d54  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00417d55  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00417d57  6a40                   -push 0x40
    app->getMemory<x86::reg32>(cpu.esp-4) = 64 /*0x40*/;
    cpu.esp -= 4;
    // 00417d59  b97f000000             -mov ecx, 0x7f
    cpu.ecx = 127 /*0x7f*/;
    // 00417d5e  a160115700             -mov eax, dword ptr [0x571160]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5706080) /* 0x571160 */);
    // 00417d63  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
    // 00417d65  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00417d67  e844050000             -call 0x4182b0
    cpu.esp -= 4;
    nfs3hp::port::playEffect(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00417d6c  31f6                   -xor esi, esi
    cpu.esi ^= x86::reg32(x86::sreg32(cpu.esi));
    // 00417d6e  a3c00e5700             -mov dword ptr [0x570ec0], eax
    app->getMemory<x86::reg32>(x86::reg32(5705408) /* 0x570ec0 */) = cpu.eax;
    // 00417d73  a1c00e5700             -mov eax, dword ptr [0x570ec0]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5705408) /* 0x570ec0 */);
    // 00417d78  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 00417d7a  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
    // 00417d7c  e8cf1a0d00             -call 0x4e9850
    cpu.esp -= 4;
    nfs3hp::snd::SNDpos3d(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00417d81  46                     -inc esi
    (cpu.esi)++;
L_0x00417d82:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00417d82  81feffff0000           +cmp esi, 0xffff
    {
        x86::reg32 tmp1 = cpu.esi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(65535 /*0xffff*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00417d88  7d11                   -jge 0x417d9b
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00417d9b;
    }
    // 00417d8a  a1c00e5700             -mov eax, dword ptr [0x570ec0]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5705408) /* 0x570ec0 */);
    // 00417d8f  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 00417d91  31db                   +xor ebx, ebx
    cpu.clear_co();
    cpu.set_szp((cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx))));
    // 00417d93  e8b81a0d00             -call 0x4e9850
    cpu.esp -= 4;
    nfs3hp::snd::SNDpos3d(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00417d98  46                     +inc esi
    {
        x86::reg32& tmp = cpu.esi;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 00417d99  ebe7                   -jmp 0x417d82
    goto L_0x00417d82;
L_0x00417d9b:
    // 00417d9b  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00417d9c  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00417d9d  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00417d9e  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00417d9f  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00417da0  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_417db0: native, nfs3hp::snd::sirenSecondTone */

/* sub_417e00: native, nfs3hp::snd::sirenSteadyTone */

/* sub_417e60: native, nfs3hp::snd::sirenSecondDone */

/* sub_417eb0: native, nfs3hp::snd::sirenStart */

/* sub_417f60: native, nfs3hp::snd::sirenStop */

/* sub_417fd0: native, nfs3hp::snd::sirenTick */

/* sub_4181d0: native, nfs3hp::port::playMenuEffect */

/* sub_418280: native, nfs3hp::port::playCarEffectFive */

/* sub_4182b0: native, nfs3hp::port::playEffect */

/* sub_4184f0: native, nfs3hp::port::playSpeechEffect */

/* sub_4185e0: native, nfs3hp::port::panFromSide */

/* sub_418610: native, nfs3hp::port::masterSilent */

/* sub_418620: native, nfs3hp::port::masterBack */

/* align: skip  */
void Application::sub_418670(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00418670  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00418671  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00418672  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00418674  b87f000000             -mov eax, 0x7f
    cpu.eax = 127 /*0x7f*/;
    // 00418679  e852ed0c00             -call 0x4e73d0
    cpu.esp -= 4;
    nfs3hp::snd::SNDmastervol(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0041867e  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00418680  e8db040d00             -call 0x4e8b60
    cpu.esp -= 4;
    nfs3hp::snd::SNDstreamvol(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00418685  b864000000             -mov eax, 0x64
    cpu.eax = 100 /*0x64*/;
    // 0041868a  8b15e8bb6f00           -mov edx, dword ptr [0x6fbbe8]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(7322600) /* 0x6fbbe8 */);
    // 00418690  e8dbed0c00             -call 0x4e7470
    cpu.esp -= 4;
    nfs3hp::snd::SNDstreamautovol(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00418695  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00418696  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00418697  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_4186a0: native, nfs3hp::port::silenceForMenus */

/* sub_4186f0: native, nfs3hp::port::silenceForRace */

/* sub_418740: native, nfs3hp::port::busInit */

/* sub_418770: native, nfs3hp::port::busUp */

/* sub_418790: native, nfs3hp::port::busDown */

/* sub_4187a0: native, nfs3hp::port::slotsStop */

/* sub_4187e0: native, nfs3hp::port::musicMuteToggle */

/* sub_418840: native, nfs3hp::decompiled::swapRaceVolumes */

/* sub_4188a0: native, nfs3hp::snd::copBeepTick */

/* sub_418930: native, nfs3hp::snd::copBeepStart */

/* sub_418990: native, nfs3hp::snd::chaseLevel */

/* sub_418c30: native, nfs3hp::snd::copEffect */

/* sub_418c60: native, nfs3hp::snd::musicEventResume */

/* align: skip 0x00 0x00 0x00 0x00 0x00 */
void Application::sub_418cc0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00418cc0  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00418cc1  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00418cc2  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00418cc3  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00418cc5  6a01                   -push 1
    app->getMemory<x86::reg32>(cpu.esp-4) = 1 /*0x1*/;
    cpu.esp -= 4;
    // 00418cc7  6a00                   -push 0
    app->getMemory<x86::reg32>(cpu.esp-4) = 0 /*0x0*/;
    cpu.esp -= 4;
    // 00418cc9  6a00                   -push 0
    app->getMemory<x86::reg32>(cpu.esp-4) = 0 /*0x0*/;
    cpu.esp -= 4;
    // 00418ccb  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00418ccc  68306c5300             -push 0x536c30
    app->getMemory<x86::reg32>(cpu.esp-4) = 5467184 /*0x536c30*/;
    cpu.esp -= 4;
    // 00418cd1  6a00                   -push 0
    app->getMemory<x86::reg32>(cpu.esp-4) = 0 /*0x0*/;
    cpu.esp -= 4;
    // 00418cd3  2eff154c455300         -call dword ptr cs:[0x53454c]
    cpu.ip = app->getMemory<x86::reg32>(cpu.ecs + x86::reg32(5457228) /* 0x53454c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00418cda  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00418cdb  2eff1580445300         -call dword ptr cs:[0x534480]
    cpu.ip = app->getMemory<x86::reg32>(cpu.ecs + x86::reg32(5457024) /* 0x534480 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00418ce2  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 00418ce7  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00418ce8  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00418ce9  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00418cea  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x40 0x00 0x8b 0xc9 */
void Application::sub_418cf0(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00418cf0  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00418cf1  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00418cf3  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00418cf4  c3                     -ret 
    cpu.esp += 4;
    return;
}

}
