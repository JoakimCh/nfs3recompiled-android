#include "nfs3hp.h"
#include <lib/thread.h>

namespace nfs3hp
{
// Port (tools/apply_native_vertices.py): defined in native_vertices.cpp.
bool aiVotes(win32::WinApplication* app, x86::CPU& cpu);

/* sub_40bca0: native, nfs3hp::pursuit::radioResume */

/* sub_40bd00: native, nfs3hp::pursuit::radioAbort */

/* align: skip 0x00 */
void Application::sub_40bd60(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0040bd60  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 0040bd61  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 0040bd63  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0040bd64  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 0x8b 0xdb */
void Application::sub_40bd70(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0040bd70  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 0040bd71  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 0040bd73  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0040bd74  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_40bd80: native, nfs3hp::pursuit::resetOnTrack */

/* sub_40bf50: native, nfs3hp::pursuit::copRestart */

/* sub_40bfe0: native, nfs3hp::pursuit::topSpeedFactor */

/* sub_40bff0: native, nfs3hp::pursuit::followChased */

/* sub_40c140: native, nfs3hp::pursuit::raceEndHookToo */

/* sub_40c150: native, nfs3hp::pursuit::raceStartHookToo */

/* sub_40c160: native, nfs3hp::pursuit::followCar */

/* sub_40c210: native, nfs3hp::pursuit::countdownDone */

/* sub_40c270: native, nfs3hp::pursuit::trafficTarget */

/* sub_40c2f0: native, nfs3hp::pursuit::trafficStep */

/* sub_40c4f0: native, nfs3hp::aiplan::leastTrafficPlayer */

/* sub_40c590: native, nfs3hp::aiplan::placeTrafficCar */

/* sub_40c630: native, nfs3hp::aiplan::reactToTraffic */

/* sub_40c780: native, nfs3hp::aiplan::slowForPolice */

/* sub_40c7f0: native, nfs3hp::aiplan::countStopped */

/* sub_40c830: native, nfs3hp::aiplan::nearPoliceCar */

/* sub_40c8a0: native, nfs3hp::aiplan::weighLaneVotes */

/* sub_40c8d0: native, nfs3hp::aiplan::voteRoadside */

/* sub_40c950: native, nfs3hp::aiplan::atRoadside */

/* sub_40c9f0: native, nfs3hp::aiplan::advanceCarAi */

/* sub_40cb20: native, nfs3hp::aiplan::clearSensedCars */

/* sub_40cb50: native, nfs3hp::aiplan::cacheTrafficSide */

/* sub_40cb70: native, nfs3hp::aiplan::resetTrafficCar */

/* sub_40cb90: native, nfs3hp::aiplan::clearTrafficRecord */

/* sub_40cd80: native, nfs3hp::aiplan::placeOnTrack */

/* sub_40ce70: native, nfs3hp::aiplan::brakeToStop */

/* sub_40cee0: native, nfs3hp::aiplan::voteCurrentLane */

/* sub_40cfc0: native, nfs3hp::aiplan::senseTraffic */

/* sub_40d1f0: native, nfs3hp::aiplan::planLaneChange */

/* sub_40d2e0: native, nfs3hp::aiplan::edgeLaneCost */

/* sub_40d3d0: native, nfs3hp::aiplan::scoreLanesByRoad */

/* sub_40d720: native, nfs3hp::aiplan::scoreLanesByObstacles */

/* sub_40d800: native, nfs3hp::aiplan::scoreLanesByCars */

/* sub_40d9f0: native, nfs3hp::aiplan::edgePenalty */

/* sub_40da30: native, nfs3hp::aiplan::sumLaneVotes */

/* sub_40daf0: native, nfs3hp::aiplan::steerToLane */

/* sub_40dd60: native, nfs3hp::aiplan::beginLanePlanning */

/* sub_40ddb0: native, nfs3hp::aiplan::chooseLane */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 */
void Application::sub_40de30(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (aiVotes(app, cpu.sync())) /* port: native (tools/apply_native_vertices.py) */
    {
        cpu.reload();
        return;
    }
    // 0040de30  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 0040de31  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 0040de32  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 0040de34  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 0040de36  e8f5fbffff             -call 0x40da30
    cpu.esp -= 4;
    nfs3hp::aiplan::sumLaneVotes(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0040de3b  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 0040de3d  e8aefcffff             -call 0x40daf0
    cpu.esp -= 4;
    nfs3hp::aiplan::steerToLane(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0040de42  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0040de43  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0040de44  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_40de50: native, nfs3hp::aiplan::startHorn */

/* sub_40deb0: native, nfs3hp::aiplan::stopHorn */

/* sub_40df10: native, nfs3hp::aiplan::stepTrafficLoading */

/* sub_40e000: native, nfs3hp::load::loadOpponentSpeeds */

/* sub_40e080: native, nfs3hp::aiplan::targetSpeedAt */

/* sub_40e0c0: native, nfs3hp::aiplan::roadKindAt */

/* sub_40e0f0: native, nfs3hp::aiplan::cacheRoadWidth */

/* sub_40e120: native, nfs3hp::aiplan::nodeGap */

/* sub_40e160: native, nfs3hp::aiplan::nodeOffset */

/* sub_40e1b0: native, nfs3hp::aiplan::nodesAheadBySpeed */

/* sub_40e200: native, nfs3hp::aiplan::nodeLaneBits */

/* sub_40e220: native, nfs3hp::aiplan::nodeHasLane */

/* sub_40e270: native, nfs3hp::aiplan::laneBit */

/* sub_40e2b0: native, nfs3hp::aiplan::roadSliceIndex */

/* sub_40e350: native, nfs3hp::aiplan::carSlices */

/* sub_40e3c0: native, nfs3hp::aiplan::fillTrackTuning */

/* sub_40e410: native, nfs3hp::aiplan::setupTrackTuning */

/* sub_40ec40: native, nfs3hp::aiplan::freeSpeedTable */

/* sub_40ec70: native, nfs3hp::aiplan::trafficSide */

/* sub_40eca0: native, nfs3hp::aiplan::roadIsWide */

/* align: skip 0x8b 0xc0 */
void Application::sub_40ece0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0040ece0  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 0040ece1  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 0040ece2  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 0040ece3  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 0040ece5  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 0040ece8  8b15acd46f00           -mov edx, dword ptr [0x6fd4ac]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(7328940) /* 0x6fd4ac */);
    // 0040ecee  83fa0b                 +cmp edx, 0xb
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(11 /*0xb*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0040ecf1  7d10                   -jge 0x40ed03
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x0040ed03;
    }
    // 0040ecf3  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 0040ecf5  c1e005                 +shl eax, 5
    {
        x86::reg8 tmp = 5 /*0x5*/ % 32;
        x86::reg32& op = cpu.eax;
        if (tmp)
        {
            cpu.flags.cf = 1 & (op >> (32 - tmp));
            cpu.set_szp((op <<= tmp));
            if (tmp == 1) cpu.flags.of = (cpu.flags.cf != (1 & (op >> (32 - 1))));
        }
    }
    // 0040ecf8  8b809cef5600           -mov eax, dword ptr [eax + 0x56ef9c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(5697436) /* 0x56ef9c */);
    // 0040ecfe  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 0040ed01  eb07                   -jmp 0x40ed0a
    goto L_0x0040ed0a;
L_0x0040ed03:
    // 0040ed03  c745fc0c93d641         -mov dword ptr [ebp - 4], 0x41d6930c
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = 1104581388 /*0x41d6930c*/;
L_0x0040ed0a:
    // 0040ed0a  d945fc                 -fld dword ptr [ebp - 4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */));
    // 0040ed0d  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 0040ed0f  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0040ed10  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0040ed11  58                     -pop eax
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    cpu.fpu.count += 1;
    cpu.fpu.st(0) = fpu1;
    }
    // 0040ed12  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_40ed40: native, nfs3hp::aiplan::trafficSpeedAt */

/* sub_40ee80: native, nfs3hp::aiplan::tuningSpeed */

/* sub_40eed0: native, nfs3hp::aiplan::tuningDistance */

/* sub_40ef10: native, nfs3hp::aiplan::tuningFirst */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x90 */
void Application::sub_40ef30(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0040ef30  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 0040ef31  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 0040ef32  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 0040ef33  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 0040ef35  8b9054010000           -mov edx, dword ptr [eax + 0x154]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(340) /* 0x154 */);
    // 0040ef3b  8b401c                 -mov eax, dword ptr [eax + 0x1c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(28) /* 0x1c */);
    // 0040ef3e  8b0d40d95d00           -mov ecx, dword ptr [0x5dd940]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(6150464) /* 0x5dd940 */);
    // 0040ef44  40                     -inc eax
    (cpu.eax)++;
    // 0040ef45  39c8                   +cmp eax, ecx
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
    // 0040ef47  7c02                   -jl 0x40ef4b
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x0040ef4b;
    }
    // 0040ef49  29c8                   -sub eax, ecx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.ecx));
L_0x0040ef4b:
    // 0040ef4b  e8900f0900             -call 0x49fee0
    cpu.esp -= 4;
    sub_49fee0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0040ef50  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 0040ef52  3d00020000             +cmp eax, 0x200
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(512 /*0x200*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0040ef57  7e05                   -jle 0x40ef5e
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x0040ef5e;
    }
    // 0040ef59  2d00040000             -sub eax, 0x400
    (cpu.eax) -= x86::reg32(x86::sreg32(1024 /*0x400*/));
L_0x0040ef5e:
    // 0040ef5e  3d00feffff             +cmp eax, 0xfffffe00
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(4294966784 /*0xfffffe00*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0040ef63  7d05                   -jge 0x40ef6a
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x0040ef6a;
    }
    // 0040ef65  0500040000             -add eax, 0x400
    (cpu.eax) += x86::reg32(x86::sreg32(1024 /*0x400*/));
L_0x0040ef6a:
    // 0040ef6a  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0040ef6b  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0040ef6c  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0040ef6d  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_40ef70: native, nfs3hp::aiplan::nodeDirectionDot */

/* sub_40f000: native, nfs3hp::aiplan::nodeWithinRange */

/* sub_40f050: native, nfs3hp::aiplan::carWithinReach */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 */
void Application::sub_40f0c0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0040f0c0  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 0040f0c1  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 0040f0c2  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 0040f0c4  8b1520f25600           -mov edx, dword ptr [0x56f220]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5698080) /* 0x56f220 */);
    // 0040f0ca  83fa0a                 +cmp edx, 0xa
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(10 /*0xa*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0040f0cd  7d0a                   -jge 0x40f0d9
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x0040f0d9;
    }
    // 0040f0cf  42                     +inc edx
    {
        x86::reg32& tmp = cpu.edx;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 0040f0d0  8b04955c255500         -mov eax, dword ptr [edx*4 + 0x55255c]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5580124) /* 0x55255c */ + cpu.edx * 4);
    // 0040f0d7  eb0a                   -jmp 0x40f0e3
    goto L_0x0040f0e3;
L_0x0040f0d9:
    // 0040f0d9  ba01000000             -mov edx, 1
    cpu.edx = 1 /*0x1*/;
    // 0040f0de  a160255500             -mov eax, dword ptr [0x552560]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5580128) /* 0x552560 */);
L_0x0040f0e3:
    // 0040f0e3  3b0540d95d00           +cmp eax, dword ptr [0x5dd940]
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(6150464) /* 0x5dd940 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0040f0e9  7c05                   -jl 0x40f0f0
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x0040f0f0;
    }
    // 0040f0eb  a160255500             -mov eax, dword ptr [0x552560]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5580128) /* 0x552560 */);
L_0x0040f0f0:
    // 0040f0f0  891520f25600           -mov dword ptr [0x56f220], edx
    app->getMemory<x86::reg32>(x86::reg32(5698080) /* 0x56f220 */) = cpu.edx;
    // 0040f0f6  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0040f0f7  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0040f0f8  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_40f100: native, nfs3hp::aiplan::alwaysOne */

/* sub_40f110: native, nfs3hp::aiplan::carBoxedIn */

/* sub_40f230: native, nfs3hp::load::clearTrackCameras */

/* sub_40f280: native, nfs3hp::load::loadTrackCameras */

/* sub_40f330: native, nfs3hp::aiplan::freeAnimationPaths */

/* sub_40f370: native, nfs3hp::aiplan::findFreeAnimation */

/* sub_40f3b0: native, nfs3hp::aiplan::startAnimation */

/* sub_40f430: native, nfs3hp::aiplan::setAnimationMode */

/* sub_40f460: native, nfs3hp::aiplan::stopAnimation */

/* sub_40f4b0: native, nfs3hp::aiplan::animationPose */

/* sub_40f6d0: native, nfs3hp::aiplan::animationPlace */

/* sub_40f800: native, nfs3hp::aiplan::animationProgress */

/* sub_40f880: native, nfs3hp::aiplan::animationLastPose */

/* sub_40f8d0: native, nfs3hp::aiplan::pathEndPose */

/* sub_40f940: native, nfs3hp::aiplan::animationStep */

/* align: skip 0x8d 0x40 0x00 */
void Application::sub_40fa10(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0040fa10  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 0040fa11  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 0040fa12  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 0040fa13  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 0040fa14  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 0040fa16  83ec08                 -sub esp, 8
    (cpu.esp) -= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 0040fa19  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 0040fa1b  e8a0000000             -call 0x40fac0
    cpu.esp -= 4;
    nfs3hp::aiplan::animationPlaying(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0040fa20  83f801                 +cmp eax, 1
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
    // 0040fa23  7407                   -je 0x40fa2c
    if (cpu.flags.zf)
    {
        goto L_0x0040fa2c;
    }
    // 0040fa25  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
    // 0040fa27  e986000000             -jmp 0x40fab2
    goto L_0x0040fab2;
L_0x0040fa2c:
    // 0040fa2c  89ca                   -mov edx, ecx
    cpu.edx = cpu.ecx;
    // 0040fa2e  c1e202                 -shl edx, 2
    cpu.edx <<= 2 /*0x2*/ % 32;
    // 0040fa31  29ca                   -sub edx, ecx
    (cpu.edx) -= x86::reg32(x86::sreg32(cpu.ecx));
    // 0040fa33  c1e203                 -shl edx, 3
    cpu.edx <<= 3 /*0x3*/ % 32;
    // 0040fa36  8b8234f25600           -mov eax, dword ptr [edx + 0x56f234]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(5698100) /* 0x56f234 */);
    // 0040fa3c  8d7008                 -lea esi, [eax + 8]
    cpu.esi = x86::reg32(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 0040fa3f  668b4004               -mov ax, word ptr [eax + 4]
    cpu.ax = app->getMemory<x86::reg16>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 0040fa43  25ffff0000             -and eax, 0xffff
    cpu.eax &= x86::reg32(x86::sreg32(65535 /*0xffff*/));
    // 0040fa48  8d48ff                 -lea ecx, [eax - 1]
    cpu.ecx = x86::reg32(cpu.eax + x86::reg32(-1) /* -0x1 */);
    // 0040fa4b  8b823cf25600           -mov eax, dword ptr [edx + 0x56f23c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(5698108) /* 0x56f23c */);
    // 0040fa51  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 0040fa53  c1fa1f                 -sar edx, 0x1f
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (31 /*0x1f*/ % 32));
    // 0040fa56  f7f9                   -idiv ecx
    {
        x86::sreg64 tmp = x86::sreg64(cpu.edx_eax);
        x86::sreg32 d = x86::sreg32(cpu.ecx);
        cpu.edx_eax = x86::reg64(tmp / d);
        cpu.edx = x86::reg32(tmp % d);
    }
    // 0040fa58  8d049500000000         -lea eax, [edx*4]
    cpu.eax = x86::reg32(cpu.edx * 4);
    // 0040fa5f  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 0040fa61  8d7df8                 -lea edi, [ebp - 8]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 0040fa64  8d74860c               -lea esi, [esi + eax*4 + 0xc]
    cpu.esi = x86::reg32(cpu.esi + x86::reg32(12) /* 0xc */ + cpu.eax * 4);
    // 0040fa68  89da                   -mov edx, ebx
    cpu.edx = cpu.ebx;
    // 0040fa6a  8d45f8                 -lea eax, [ebp - 8]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 0040fa6d  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 0040fa6e  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 0040fa6f  e82c720a00             -call 0x4b6ca0
    cpu.esp -= 4;
    sub_4b6ca0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0040fa74  8b5318                 -mov edx, dword ptr [ebx + 0x18]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(24) /* 0x18 */);
    // 0040fa77  8b430c                 -mov eax, dword ptr [ebx + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(12) /* 0xc */);
    // 0040fa7a  89530c                 -mov dword ptr [ebx + 0xc], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(12) /* 0xc */) = cpu.edx;
    // 0040fa7d  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 0040fa7f  894318                 -mov dword ptr [ebx + 0x18], eax
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(24) /* 0x18 */) = cpu.eax;
    // 0040fa82  f7da                   -neg edx
    cpu.edx = ~cpu.edx + 1;
    // 0040fa84  895318                 -mov dword ptr [ebx + 0x18], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(24) /* 0x18 */) = cpu.edx;
    // 0040fa87  8b4310                 -mov eax, dword ptr [ebx + 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(16) /* 0x10 */);
    // 0040fa8a  8b531c                 -mov edx, dword ptr [ebx + 0x1c]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(28) /* 0x1c */);
    // 0040fa8d  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 0040fa8f  895310                 -mov dword ptr [ebx + 0x10], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(16) /* 0x10 */) = cpu.edx;
    // 0040fa92  f7d9                   -neg ecx
    cpu.ecx = ~cpu.ecx + 1;
    // 0040fa94  89431c                 -mov dword ptr [ebx + 0x1c], eax
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(28) /* 0x1c */) = cpu.eax;
    // 0040fa97  894b1c                 -mov dword ptr [ebx + 0x1c], ecx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(28) /* 0x1c */) = cpu.ecx;
    // 0040fa9a  8b5320                 -mov edx, dword ptr [ebx + 0x20]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(32) /* 0x20 */);
    // 0040fa9d  8b4314                 -mov eax, dword ptr [ebx + 0x14]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(20) /* 0x14 */);
    // 0040faa0  895314                 -mov dword ptr [ebx + 0x14], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(20) /* 0x14 */) = cpu.edx;
    // 0040faa3  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 0040faa5  894320                 -mov dword ptr [ebx + 0x20], eax
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(32) /* 0x20 */) = cpu.eax;
    // 0040faa8  f7de                   -neg esi
    cpu.esi = ~cpu.esi + 1;
    // 0040faaa  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 0040faaf  897320                 -mov dword ptr [ebx + 0x20], esi
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(32) /* 0x20 */) = cpu.esi;
L_0x0040fab2:
    // 0040fab2  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 0040fab4  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0040fab5  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0040fab6  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0040fab7  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0040fab8  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_40fac0: native, nfs3hp::aiplan::animationPlaying */

/* sub_40faf0: native, nfs3hp::Is3DSoundAvailable */

/* sub_40fb10: native, nfs3hp::aiplan::startSound */

/* sub_40fcf0: native, nfs3hp::aiplan::restartSound */

/* sub_40feb0: native, nfs3hp::snd::soundExit */

/* sub_40fed0: native, nfs3hp::snd::deleteMusicCopy */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8b 0xd2 */
void Application::sub_40ff20(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0040ff20  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 0040ff21  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 0040ff22  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 0040ff23  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 0040ff24  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 0040ff25  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 0040ff27  81ec8c000000           -sub esp, 0x8c
    (cpu.esp) -= x86::reg32(x86::sreg32(140 /*0x8c*/));
    // 0040ff2d  81ed82000000           -sub ebp, 0x82
    (cpu.ebp) -= x86::reg32(x86::sreg32(130 /*0x82*/));
    // 0040ff33  6834277a00             -push 0x7a2734
    app->getMemory<x86::reg32>(cpu.esp-4) = 8005428 /*0x7a2734*/;
    cpu.esp -= 4;
    // 0040ff38  6880685300             -push 0x536880
    app->getMemory<x86::reg32>(cpu.esp-4) = 5466240 /*0x536880*/;
    cpu.esp -= 4;
    // 0040ff3d  8d45f6                 -lea eax, [ebp - 0xa]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-10) /* -0xa */);
    // 0040ff40  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 0040ff41  e84af70c00             -call 0x4df690
    cpu.esp -= 4;
    nfs3hp::watcom::sprintf(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0040ff46  83c40c                 -add esp, 0xc
    (cpu.esp) += x86::reg32(x86::sreg32(12 /*0xc*/));
    // 0040ff49  8d45f6                 -lea eax, [ebp - 0xa]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-10) /* -0xa */);
    // 0040ff4c  be0000f000             -mov esi, 0xf00000
    cpu.esi = 15728640 /*0xf00000*/;
    // 0040ff51  e80a0f0d00             -call 0x4e0e60
    cpu.esp -= 4;
    nfs3hp::ea::fileExists(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0040ff56  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0040ff58  7415                   -je 0x40ff6f
    if (cpu.flags.zf)
    {
        goto L_0x0040ff6f;
    }
    // 0040ff5a  6a20                   -push 0x20
    app->getMemory<x86::reg32>(cpu.esp-4) = 32 /*0x20*/;
    cpu.esp -= 4;
    // 0040ff5c  8d45f6                 -lea eax, [ebp - 0xa]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-10) /* -0xa */);
    // 0040ff5f  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 0040ff60  2eff15ec455300         -call dword ptr cs:[0x5345ec]
    cpu.ip = app->getMemory<x86::reg32>(cpu.ecs + x86::reg32(5457388) /* 0x5345ec */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0040ff67  8d45f6                 -lea eax, [ebp - 0xa]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-10) /* -0xa */);
    // 0040ff6a  e831290d00             -call 0x4e28a0
    cpu.esp -= 4;
    nfs3hp::watcom::unlink(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x0040ff6f:
    // 0040ff6f  8d4d7a                 -lea ecx, [ebp + 0x7a]
    cpu.ecx = x86::reg32(cpu.ebp + x86::reg32(122) /* 0x7a */);
    // 0040ff72  8d5d7e                 -lea ebx, [ebp + 0x7e]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(126) /* 0x7e */);
    // 0040ff75  8d5576                 -lea edx, [ebp + 0x76]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(118) /* 0x76 */);
    // 0040ff78  8d45f6                 -lea eax, [ebp - 0xa]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-10) /* -0xa */);
    // 0040ff7b  e8602b0d00             -call 0x4e2ae0
    cpu.esp -= 4;
    nfs3hp::ea::openHandleToWrite(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0040ff80  8b4576                 -mov eax, dword ptr [ebp + 0x76]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(118) /* 0x76 */);
    // 0040ff83  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 0040ff85  e8a6420d00             -call 0x4e4230
    cpu.esp -= 4;
    sub_4e4230(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0040ff8a  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 0040ff8c  8b4576                 -mov eax, dword ptr [ebp + 0x76]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(118) /* 0x76 */);
    // 0040ff8f  e80c2e0d00             -call 0x4e2da0
    cpu.esp -= 4;
    nfs3hp::ea::closeHandle(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0040ff94  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 0040ff96  8da582000000           -lea esp, [ebp + 0x82]
    cpu.esp = x86::reg32(cpu.ebp + x86::reg32(130) /* 0x82 */);
    // 0040ff9c  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0040ff9d  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0040ff9e  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0040ff9f  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0040ffa0  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0040ffa1  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_40ffd0: native, nfs3hp::snd::raceTuneOf */

/* sub_410030: native, nfs3hp::snd::raceMusicPrepare */

/* sub_410330: native, nfs3hp::snd::musicStreamMake */

/* sub_410370: native, nfs3hp::snd::musicStreamMakeOf */

}
