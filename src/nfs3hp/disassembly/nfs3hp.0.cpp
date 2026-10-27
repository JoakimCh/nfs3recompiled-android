#include "nfs3hp.h"
#include <lib/thread.h>

namespace nfs3hp
{

/* align: skip  */
void Application::sub_401000(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
L_0x00401000:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00401000  cc                     -int3 
    NFS2_ASSERT(false);
    // 00401001  ebfd                   -jmp 0x401000
    goto L_0x00401000;
}

/* sub_401010: native, nfs3hp::Error */

/* sub_401220: native, nfs3hp::airace::nothingAtStart */

/* sub_401230: native, nfs3hp::airace::nothingAtLoad */

/* sub_401240: native, nfs3hp::airace::releaseEdge */

/* sub_4012c0: native, nfs3hp::airace::setUpCops */

/* sub_401320: native, nfs3hp::airace::radioOn */

/* sub_401330: native, nfs3hp::airace::radioLevelDown */

/* sub_401350: native, nfs3hp::airace::radioLevelUp */

/* sub_401370: native, nfs3hp::airace::copTopSpeed */

/* sub_4013b0: native, nfs3hp::airace::nearestCopGap */

/* sub_401430: native, nfs3hp::airace::setWantedSpeed */

/* sub_4014b0: native, nfs3hp::airace::noteSpeeding */

/* sub_401500: native, nfs3hp::airace::pulledOver */

/* sub_401520: native, nfs3hp::airace::copRadioCall */

/* sub_401580: native, nfs3hp::airace::ticketRadio */

/* sub_4015b0: native, nfs3hp::airace::stopIfCopNear */

/* sub_401650: native, nfs3hp::airace::stopForCop */

/* sub_401780: native, nfs3hp::airace::sizeUpTarget */

/* sub_4018b0: native, nfs3hp::airace::joinPursuit */

/* sub_401a20: native, nfs3hp::airace::leaveCopList */

/* sub_401a80: native, nfs3hp::airace::giveUpPursuit */

/* sub_401b50: native, nfs3hp::airace::pullOverSpot */

/* sub_401c20: native, nfs3hp::airace::planPullOver */

/* sub_401e20: native, nfs3hp::airace::endPullOver */

/* sub_401e40: native, nfs3hp::airace::copStopsBy */

/* sub_401fb0: native, nfs3hp::airace::stopOver */

/* sub_401ff0: native, nfs3hp::airace::giveTicket */

/* sub_402110: native, nfs3hp::airace::targetStopping */

/* sub_402420: native, nfs3hp::airace::chaseSpeed */

/* sub_4025c0: native, nfs3hp::airace::pursueTarget */

/* sub_402750: native, nfs3hp::airace::votePursuitLane */

/* sub_4028e0: native, nfs3hp::airace::sideTowardNode */

/* sub_402910: native, nfs3hp::airace::keepSideOfTarget */

/* sub_4029c0: native, nfs3hp::airace::placeCopAtStart */

/* sub_402a00: native, nfs3hp::airace::placeCop */

/* sub_402c70: native, nfs3hp::airace::alwaysOne */

/* sub_402c80: native, nfs3hp::airace::carReversing */

/* sub_402cb0: native, nfs3hp::airace::copHitByCar */

/* sub_402d90: native, nfs3hp::airace::voteRoadLane */

/* sub_402e10: native, nfs3hp::airace::spotSpeeder */

/* sub_402f70: native, nfs3hp::airace::laneOffRoad */

/* sub_402fd0: native, nfs3hp::airace::atOrderNode */

/* sub_403000: native, nfs3hp::airace::sideOfOrder */

/* sub_403030: native, nfs3hp::airace::takeOrder */

/* sub_403180: native, nfs3hp::airace::parkCop */

/* sub_403270: native, nfs3hp::airace::drivePatrol */

/* sub_4032e0: native, nfs3hp::airace::copDriver */

/* sub_403830: native, nfs3hp::airace::giveOrder */

/* sub_403870: native, nfs3hp::airace::spreadCops */

/* sub_403910: native, nfs3hp::airace::radioStopped */

/* sub_403950: native, nfs3hp::airace::radioStop */

/* sub_403970: native, nfs3hp::airace::initPursuits */

/* sub_4039c0: native, nfs3hp::airace::callRoadblock */

/* sub_403b20: native, nfs3hp::airace::callTwoCars */

/* sub_403d30: native, nfs3hp::airace::roadblockSiren */

/* sub_403df0: native, nfs3hp::airace::watchRoadblock */

/* sub_403ed0: native, nfs3hp::airace::watchSecondCar */

/* sub_403f80: native, nfs3hp::airace::copsWanted */

/* sub_404070: native, nfs3hp::airace::radioJoined */

/* sub_4040b0: native, nfs3hp::airace::radioGiveUp */

/* sub_4040e0: native, nfs3hp::airace::releaseCops */

/* sub_4042b0: native, nfs3hp::airace::dropCop */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x8b 0xc0 */
void Application::sub_404310(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00404310  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00404311  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00404312  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00404313  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00404314  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00404316  6a00                   -push 0
    app->getMemory<x86::reg32>(cpu.esp-4) = 0 /*0x0*/;
    cpu.esp -= 4;
    // 00404318  6a00                   -push 0
    app->getMemory<x86::reg32>(cpu.esp-4) = 0 /*0x0*/;
    cpu.esp -= 4;
    // 0040431a  bb02000000             -mov ebx, 2
    cpu.ebx = 2 /*0x2*/;
    // 0040431f  6a00                   -push 0
    app->getMemory<x86::reg32>(cpu.esp-4) = 0 /*0x0*/;
    cpu.esp -= 4;
    // 00404321  8b9030070000           -mov edx, dword ptr [eax + 0x730]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(1840) /* 0x730 */);
    // 00404327  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 00404329  e802f5ffff             -call 0x403830
    cpu.esp -= 4;
    nfs3hp::airace::giveOrder(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0040432e  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0040432f  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00404330  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00404331  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00404332  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_404340: native, nfs3hp::airace::sendCopAhead */

/* sub_4043a0: native, nfs3hp::airace::callBackup */

/* sub_404560: native, nfs3hp::airace::orderTaken */

/* sub_404580: native, nfs3hp::airace::nothingForCop */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 0x8b 0xdb */
void Application::sub_404590(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00404590  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00404591  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00404593  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00404594  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 0x8b 0xdb */
void Application::sub_4045a0(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004045a0  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004045a1  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004045a3  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004045a4  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 0x8b 0xdb */
void Application::sub_4045b0(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004045b0  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004045b1  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004045b3  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004045b4  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 0x8b 0xdb */
void Application::sub_4045c0(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004045c0  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004045c1  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004045c3  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004045c4  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 0x8b 0xdb */
void Application::sub_4045d0(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004045d0  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004045d1  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004045d3  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004045d4  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 0x8b 0xdb */
void Application::sub_4045e0(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004045e0  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004045e1  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004045e3  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004045e4  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 0x8b 0xdb */
void Application::sub_4045f0(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004045f0  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004045f1  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004045f3  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004045f4  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 0x8b 0xdb */
void Application::sub_404600(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00404600  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00404601  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00404603  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00404604  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_404610: native, nfs3hp::airace::classRule */

/* sub_404650: native, nfs3hp::airace::nothingAtEnd */

/* sub_404660: native, nfs3hp::airace::nothingAtEndToo */

/* sub_404690: native, nfs3hp::airace::setRammingRules */

/* sub_4047f0: native, nfs3hp::airace::classValue */

/* sub_404810: native, nfs3hp::airace::classValueToo */

/* sub_404840: native, nfs3hp::airace::rivalTick */

/* sub_404a00: native, nfs3hp::airace::carContact */

/* sub_404b90: native, nfs3hp::airace::slowForClass */

/* sub_404c40: native, nfs3hp::airace::nothingAtStartToo */

/* sub_404c50: native, nfs3hp::airace::catchUpSpeed */

/* sub_404c80: native, nfs3hp::airace::findLeader */

/* sub_404d30: native, nfs3hp::aidrive::copStartPlace */

/* sub_404e40: native, nfs3hp::aidrive::callRoadblock */

/* sub_404f80: native, nfs3hp::aidrive::sirenSwitch */

/* sub_404ff0: native, nfs3hp::aidrive::watchRacers */

/* sub_405220: native, nfs3hp::aidrive::jumpBehindLeader */

/* sub_4052e0: native, nfs3hp::aidrive::clockRacers */

/* sub_4053b0: native, nfs3hp::aidrive::startPursuit */

/* sub_405430: native, nfs3hp::aidrive::bustCheck */

/* sub_405630: native, nfs3hp::aidrive::pursuitStep */

/* sub_4056e0: native, nfs3hp::aidrive::dropPursuit */

/* sub_405740: native, nfs3hp::aidrive::copDriver */

/* sub_405a20: native, nfs3hp::aidrive::nearCar */

}
