#include "nfs3hp.h"
#include <lib/thread.h>

namespace nfs3hp
{
// Port (tools/apply_native_frontend.py): defined in native_frontend_cars.cpp.
bool carMenuMusicBack(win32::WinApplication* app, x86::CPU& cpu);

/* sub_4103a0: native, nfs3hp::port::musicAfterSetting */

/* sub_410460: native, nfs3hp::port::musicMenuSix */

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
    nfs3hp::port::musicStop(app, cpu.sync());
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
    nfs3hp::port::musicStart(app, cpu.sync());
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

/* sub_4104f0: native, nfs3hp::port::musicStart */

/* sub_4107c0: native, nfs3hp::port::raceMusicStart */

/* sub_4109d0: native, nfs3hp::port::musicStop */

/* sub_410a40: native, nfs3hp::dead::stub_0x410a40 */

/* sub_410aa0: native, nfs3hp::port::musicStreamEnd */

/* sub_410ad0: native, nfs3hp::port::banksFree */

/* sub_410b20: native, nfs3hp::port::banksRemove */

/* sub_410b50: native, nfs3hp::port::bankLoad */

/* sub_410c30: native, nfs3hp::dead::stub_0x410c30 */

/* sub_410c40: native, nfs3hp::port::listenerMove */

/* sub_410cb0: native, nfs3hp::port::sourceDistance */

/* sub_410d30: native, nfs3hp::port::sourceAngle */

/* sub_410dc0: native, nfs3hp::port::carAngle */

/* sub_410e30: native, nfs3hp::port::trackSounds */

/* sub_411410: native, nfs3hp::port::raceSoundTick */

/* sub_411620: native, nfs3hp::port::sourceReset */

/* sub_411680: native, nfs3hp::port::sourcesReset */

/* sub_411750: native, nfs3hp::port::copChaseSet */

/* sub_4117a0: native, nfs3hp::port::playerCarSound */

/* sub_411c50: native, nfs3hp::port::copSiren */

/* sub_411ca0: native, nfs3hp::port::copSirenStop */

/* sub_411cb0: native, nfs3hp::port::copEngine */

/* sub_411da0: native, nfs3hp::port::copEngineStop */

/* sub_411db0: native, nfs3hp::port::copDistance */

/* sub_411e20: native, nfs3hp::port::copsCloseness */

/* sub_411e60: native, nfs3hp::port::copCarSound */

/* sub_4121b0: native, nfs3hp::port::copRemove */

/* sub_412220: native, nfs3hp::port::copSourcesPick */

/* sub_4124d0: native, nfs3hp::port::placeAhead */

/* sub_412620: native, nfs3hp::port::placeAcross */

/* sub_4127b0: native, nfs3hp::port::carFlagTest */

/* sub_4127c0: native, nfs3hp::port::carRadio */

/* sub_412880: native, nfs3hp::port::playerCopRadio */

/* sub_4129a0: native, nfs3hp::port::raceValue */

/* sub_4129b0: native, nfs3hp::port::soundNothing */

/* sub_4129c0: native, nfs3hp::port::raceSoundInit */

/* sub_412b50: native, nfs3hp::port::raceSoundEnd */

/* sub_412be0: native, nfs3hp::port::copLineFor */

/* sub_412d60: native, nfs3hp::port::raceAnnouncer */

/* sub_4136e0: native, nfs3hp::port::raceBankLoad */

/* sub_413750: native, nfs3hp::port::voiceBankLoad */

/* sub_4138e0: native, nfs3hp::port::carBankLoad */

/* sub_413bc0: native, nfs3hp::port::raceBanksLoad */

/* sub_414800: native, nfs3hp::port::slotsEmpty */

/* sub_414830: native, nfs3hp::port::engineSoundsStart */

/* sub_414940: native, nfs3hp::port::crashPitch */

/* sub_4149e0: native, nfs3hp::port::crashEffect */

/* sub_414d70: native, nfs3hp::port::scrapeEffect */

/* sub_414e10: native, nfs3hp::port::farEffectAim */

/* sub_414ef0: native, nfs3hp::port::farEffectPlay */

/* sub_414f60: native, nfs3hp::port::farEffectTick */

/* sub_414f90: native, nfs3hp::port::crowdEffect */

/* sub_415010: native, nfs3hp::port::carEffectFifteen */

/* sub_415050: native, nfs3hp::port::zoneSound */

/* sub_415210: native, nfs3hp::port::scenerySounds */

/* sub_416d90: native, nfs3hp::port::carKnock */

/* sub_416f60: native, nfs3hp::port::slotStop */

/* sub_416fc0: native, nfs3hp::port::slotEffect */

/* sub_417080: native, nfs3hp::port::slotPlay */

/* sub_417390: native, nfs3hp::port::carEngine */

/* sub_4179d0: native, nfs3hp::port::noiseBySpeed */

/* sub_417b80: native, nfs3hp::port::noiseByDistance */

/* sub_417c00: native, nfs3hp::port::playerNoise */

/* sub_417c70: native, nfs3hp::port::playerNoiseStop */

/* sub_417ca0: native, nfs3hp::port::sirenIsOn */

/* sub_417cb0: native, nfs3hp::port::sirenFirstTone */

/* sub_417d00: native, nfs3hp::port::sirenFirstDone */

/* sub_417d50: native, nfs3hp::dead::stub_0x417d50 */

/* sub_417db0: native, nfs3hp::port::sirenSecondTone */

/* sub_417e00: native, nfs3hp::port::sirenSteadyTone */

/* sub_417e60: native, nfs3hp::port::sirenSecondDone */

/* sub_417eb0: native, nfs3hp::port::sirenStart */

/* sub_417f60: native, nfs3hp::port::sirenStop */

/* sub_417fd0: native, nfs3hp::port::sirenTick */

/* sub_4181d0: native, nfs3hp::port::playMenuEffect */

/* sub_418280: native, nfs3hp::port::playCarEffectFive */

/* sub_4182b0: native, nfs3hp::port::playEffect */

/* sub_4184f0: native, nfs3hp::port::playSpeechEffect */

/* sub_4185e0: native, nfs3hp::port::panFromSide */

/* sub_418610: native, nfs3hp::port::masterSilent */

/* sub_418620: native, nfs3hp::port::masterBack */

/* sub_418670: native, nfs3hp::dead::stub_0x418670 */

/* sub_4186a0: native, nfs3hp::port::silenceForMenus */

/* sub_4186f0: native, nfs3hp::port::silenceForRace */

/* sub_418740: native, nfs3hp::port::busInit */

/* sub_418770: native, nfs3hp::port::busUp */

/* sub_418790: native, nfs3hp::port::busDown */

/* sub_4187a0: native, nfs3hp::port::slotsStop */

/* sub_4187e0: native, nfs3hp::port::musicMuteToggle */

/* sub_418840: native, nfs3hp::decompiled::swapRaceVolumes */

/* sub_4188a0: native, nfs3hp::port::copBeepTick */

/* sub_418930: native, nfs3hp::port::copBeepStart */

/* sub_418990: native, nfs3hp::port::chaseLevel */

/* sub_418c30: native, nfs3hp::port::copEffect */

/* sub_418c60: native, nfs3hp::port::musicEventResume */

/* sub_418cc0: native, nfs3hp::track::shellOpen */

/* sub_418cf0: native, nfs3hp::dead::stub_0x418cf0 */

}
