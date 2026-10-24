#include "nfs3hp.h"
#include <lib/thread.h>

namespace nfs3hp
{

/* sub_41e3c0: native, nfs3hp::trackdata::nearestNodeCoarse */

/* sub_41e420: native, nfs3hp::trackdata::followNode */

/* sub_41e470: native, nfs3hp::trackdata::nearestNode */

/* sub_41e6a0: native, nfs3hp::trackdata::quadVertices */

/* sub_41e720: native, nfs3hp::trackdata::quadStepForward */

/* sub_41e770: native, nfs3hp::trackdata::quadStepBack */

/* sub_41e7c0: native, nfs3hp::trackdata::quadToFixed */

/* sub_41e8d0: native, nfs3hp::trackdata::quadSet */

/* sub_41e8f0: native, nfs3hp::trackdata::nodeSection */

/* sub_41e940: native, nfs3hp::trackdata::resetPosition */

/* sub_41e990: native, nfs3hp::trackdata::findQuad */

/* sub_41f090: native, nfs3hp::trackdata::findQuadNearby */

/* sub_41f330: native, nfs3hp::trackdata::findQuadByLinks */

/* sub_41f500: native, nfs3hp::trackdata::findQuadFallback */

/* sub_41f650: native, nfs3hp::trackdata::locateOnRoad */

/* sub_41f6e0: native, nfs3hp::trackdata::updatePosition */

/* sub_41f870: native, nfs3hp::trackdata::findMatchingQuad */

/* sub_41fd60: native, nfs3hp::trackdata::quadEdgeFlags */

/* sub_41ff10: native, nfs3hp::trackdata::sectionItemCount */

/* sub_41ff20: native, nfs3hp::trackdata::sectionItem */

/* sub_41ffa0: native, nfs3hp::trackdata::setLaneOffsets */

/* align: skip  */
void Application::sub_41ffb0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0041ffb0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 0041ffb1  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 0041ffb2  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 0041ffb4  bb01000000             -mov ebx, 1
    cpu.ebx = 1 /*0x1*/;
    // 0041ffb9  e812000000             -call 0x41ffd0
    cpu.esp -= 4;
    nfs3hp::trackdata::lanePosition(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0041ffbe  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0041ffbf  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0041ffc0  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_41ffd0: native, nfs3hp::trackdata::lanePosition */

/* sub_420230: native, nfs3hp::trackdata::positionFrame */

/* sub_4205a0: native, nfs3hp::trackdata::snapToTrack */

/* sub_420650: native, nfs3hp::trackdata::placeOnTrack */

/* sub_4206f0: native, nfs3hp::trackdata::positionColour */

/* sub_4207e0: native, nfs3hp::trackdata::positionSurface */

/* sub_420840: native, nfs3hp::trackdata::surfaceUnder */

/* sub_420bf0: native, nfs3hp::trackdata::inTunnel */

/* sub_420d60: native, nfs3hp::trackdata::carFacingWay */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x8b 0xc0 */
void Application::sub_420ff0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00420ff0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00420ff1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00420ff2  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00420ff3  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00420ff4  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00420ff5  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00420ff6  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00420ff8  83ec1c                 -sub esp, 0x1c
    (cpu.esp) -= x86::reg32(x86::sreg32(28 /*0x1c*/));
    // 00420ffb  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00420ffd  d94008                 -fld dword ptr [eax + 8]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 00421000  dc0df46d5300           -fmul qword ptr [0x536df4]
    x86::Float fpu2 = cpu.fpu.mul(fpu1, x86::Float(app->getMemory<double>(x86::reg32(5467636) /* 0x536df4 */)));
    // 00421006  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 00421009  db1c24                 -fistp dword ptr [esp]
    app->getMemory<x86::reg32>(cpu.esp) = x86::reg32(cpu.fpu.toInteger<x86::sreg32>(fpu2));
    // 0042100c  58                     -pop eax
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042100d  d9410c                 -fld dword ptr [ecx + 0xc]
    x86::Float fpu3 = x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(12) /* 0xc */));
    // 00421010  dc0df46d5300           -fmul qword ptr [0x536df4]
    x86::Float fpu4 = cpu.fpu.mul(fpu3, x86::Float(app->getMemory<double>(x86::reg32(5467636) /* 0x536df4 */)));
    // 00421016  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 00421018  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 0042101b  db1c24                 -fistp dword ptr [esp]
    app->getMemory<x86::reg32>(cpu.esp) = x86::reg32(cpu.fpu.toInteger<x86::sreg32>(fpu4));
    // 0042101e  58                     -pop eax
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042101f  d94110                 -fld dword ptr [ecx + 0x10]
    x86::Float fpu5 = x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(16) /* 0x10 */));
    // 00421022  dc0df46d5300           -fmul qword ptr [0x536df4]
    x86::Float fpu6 = cpu.fpu.mul(fpu5, x86::Float(app->getMemory<double>(x86::reg32(5467636) /* 0x536df4 */)));
    // 00421028  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 0042102a  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 0042102d  db1c24                 -fistp dword ptr [esp]
    app->getMemory<x86::reg32>(cpu.esp) = x86::reg32(cpu.fpu.toInteger<x86::sreg32>(fpu6));
    // 00421030  58                     -pop eax
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00421031  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 00421034  8b4104                 -mov eax, dword ptr [ecx + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(4) /* 0x4 */);
    // 00421037  8b048548fa5e00         -mov eax, dword ptr [eax*4 + 0x5efa48]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(6224456) /* 0x5efa48 */ + cpu.eax * 4);
    // 0042103e  8b581c                 -mov ebx, dword ptr [eax + 0x1c]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(28) /* 0x1c */);
    // 00421041  8d04dd00000000         -lea eax, [ebx*8]
    cpu.eax = x86::reg32(cpu.ebx * 8);
    // 00421048  01d8                   -add eax, ebx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.ebx));
    // 0042104a  8b3d48d95d00           -mov edi, dword ptr [0x5dd948]
    cpu.edi = app->getMemory<x86::reg32>(x86::reg32(6150472) /* 0x5dd948 */);
    // 00421050  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 00421053  01f8                   -add eax, edi
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edi));
    // 00421055  8b38                   -mov edi, dword ptr [eax]
    cpu.edi = app->getMemory<x86::reg32>(cpu.eax);
    // 00421057  29fe                   -sub esi, edi
    (cpu.esi) -= x86::reg32(x86::sreg32(cpu.edi));
    // 00421059  8975e4                 -mov dword ptr [ebp - 0x1c], esi
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-28) /* -0x1c */) = cpu.esi;
    // 0042105c  2b5004                 -sub edx, dword ptr [eax + 4]
    (cpu.edx) -= x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */)));
    // 0042105f  8b7808                 -mov edi, dword ptr [eax + 8]
    cpu.edi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 00421062  8955e8                 -mov dword ptr [ebp - 0x18], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-24) /* -0x18 */) = cpu.edx;
    // 00421065  8b55fc                 -mov edx, dword ptr [ebp - 4]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00421068  29fa                   -sub edx, edi
    (cpu.edx) -= x86::reg32(x86::sreg32(cpu.edi));
    // 0042106a  8955ec                 -mov dword ptr [ebp - 0x14], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */) = cpu.edx;
    // 0042106d  8b5015                 -mov edx, dword ptr [eax + 0x15]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(21) /* 0x15 */);
    // 00421070  c1fa18                 -sar edx, 0x18
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (24 /*0x18*/ % 32));
    // 00421073  c1e209                 -shl edx, 9
    cpu.edx <<= 9 /*0x9*/ % 32;
    // 00421076  8955f0                 -mov dword ptr [ebp - 0x10], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = cpu.edx;
    // 00421079  8b5016                 -mov edx, dword ptr [eax + 0x16]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(22) /* 0x16 */);
    // 0042107c  c1fa18                 -sar edx, 0x18
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (24 /*0x18*/ % 32));
    // 0042107f  8b4017                 -mov eax, dword ptr [eax + 0x17]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(23) /* 0x17 */);
    // 00421082  c1e209                 -shl edx, 9
    cpu.edx <<= 9 /*0x9*/ % 32;
    // 00421085  c1f818                 -sar eax, 0x18
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (24 /*0x18*/ % 32));
    // 00421088  8955f4                 -mov dword ptr [ebp - 0xc], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.edx;
    // 0042108b  c1e009                 -shl eax, 9
    cpu.eax <<= 9 /*0x9*/ % 32;
    // 0042108e  8b55e4                 -mov edx, dword ptr [ebp - 0x1c]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-28) /* -0x1c */);
    // 00421091  8945f8                 -mov dword ptr [ebp - 8], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.eax;
    // 00421094  8b45f0                 -mov eax, dword ptr [ebp - 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 00421097  f7ea                   -imul edx
    cpu.edx_eax = x86::reg64(x86::sreg64(static_cast<x86::sreg32>(cpu.eax)) * x86::sreg64(x86::sreg32(cpu.edx)));
    // 00421099  c1e210                 -shl edx, 0x10
    cpu.edx <<= 16 /*0x10*/ % 32;
    // 0042109c  c1e810                 +shr eax, 0x10
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
    // 0042109f  11d0                   -adc eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx) + cpu.flags.cf);
    // 004210a1  8b55e8                 -mov edx, dword ptr [ebp - 0x18]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-24) /* -0x18 */);
    // 004210a4  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 004210a6  8b45f4                 -mov eax, dword ptr [ebp - 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 004210a9  f7ea                   -imul edx
    cpu.edx_eax = x86::reg64(x86::sreg64(static_cast<x86::sreg32>(cpu.eax)) * x86::sreg64(x86::sreg32(cpu.edx)));
    // 004210ab  c1e210                 -shl edx, 0x10
    cpu.edx <<= 16 /*0x10*/ % 32;
    // 004210ae  c1e810                 +shr eax, 0x10
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
    // 004210b1  11d0                   -adc eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx) + cpu.flags.cf);
    // 004210b3  8b55ec                 -mov edx, dword ptr [ebp - 0x14]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */);
    // 004210b6  01c6                   -add esi, eax
    (cpu.esi) += x86::reg32(x86::sreg32(cpu.eax));
    // 004210b8  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004210bb  f7ea                   -imul edx
    cpu.edx_eax = x86::reg64(x86::sreg64(static_cast<x86::sreg32>(cpu.eax)) * x86::sreg64(x86::sreg32(cpu.edx)));
    // 004210bd  c1e210                 -shl edx, 0x10
    cpu.edx <<= 16 /*0x10*/ % 32;
    // 004210c0  c1e810                 +shr eax, 0x10
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
    // 004210c3  11d0                   -adc eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx) + cpu.flags.cf);
    // 004210c5  01c6                   -add esi, eax
    (cpu.esi) += x86::reg32(x86::sreg32(cpu.eax));
    // 004210c7  8b4104                 -mov eax, dword ptr [ecx + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(4) /* 0x4 */);
    // 004210ca  8b048548fa5e00         -mov eax, dword ptr [eax*4 + 0x5efa48]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(6224456) /* 0x5efa48 */ + cpu.eax * 4);
    // 004210d1  83b89809000000         +cmp dword ptr [eax + 0x998], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(2456) /* 0x998 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    }
    // 004210d8  7507                   -jne 0x4210e1
    if (!cpu.flags.zf)
    {
        goto L_0x004210e1;
    }
    // 004210da  b8f8ffffff             -mov eax, 0xfffffff8
    cpu.eax = 4294967288 /*0xfffffff8*/;
    // 004210df  eb1b                   -jmp 0x4210fc
    goto L_0x004210fc;
L_0x004210e1:
    // 004210e1  b808000000             -mov eax, 8
    cpu.eax = 8 /*0x8*/;
    // 004210e6  eb04                   -jmp 0x4210ec
    goto L_0x004210ec;
    // 004210e8  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004210ea  7c10                   -jl 0x4210fc
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004210fc;
    }
L_0x004210ec:
    // 004210ec  8b0d40d95d00           -mov ecx, dword ptr [0x5dd940]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(6150464) /* 0x5dd940 */);
    // 004210f2  01d8                   -add eax, ebx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.ebx));
    // 004210f4  39c8                   +cmp eax, ecx
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
    // 004210f6  7c10                   -jl 0x421108
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x00421108;
    }
    // 004210f8  29c8                   +sub eax, ecx
    {
        x86::reg32& tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ecx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 004210fa  eb0c                   -jmp 0x421108
    goto L_0x00421108;
L_0x004210fc:
    // 004210fc  01d8                   -add eax, ebx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.ebx));
    // 004210fe  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00421100  7d06                   -jge 0x421108
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00421108;
    }
    // 00421102  030540d95d00           -add eax, dword ptr [0x5dd940]
    (cpu.eax) += x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(6150464) /* 0x5dd940 */)));
L_0x00421108:
    // 00421108  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 0042110a  c1e003                 -shl eax, 3
    cpu.eax <<= 3 /*0x3*/ % 32;
    // 0042110d  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 0042110f  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 00421112  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 00421114  7e46                   -jle 0x42115c
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x0042115c;
    }
    // 00421116  8b1548d95d00           -mov edx, dword ptr [0x5dd948]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(6150472) /* 0x5dd948 */);
    // 0042111c  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 0042111e  8a500e                 -mov dl, byte ptr [eax + 0xe]
    cpu.dl = app->getMemory<x86::reg8>(cpu.eax + x86::reg32(14) /* 0xe */);
    // 00421121  f6c20f                 +test dl, 0xf
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.dl & 15 /*0xf*/));
    // 00421124  7419                   -je 0x42113f
    if (cpu.flags.zf)
    {
        goto L_0x0042113f;
    }
    // 00421126  88d0                   -mov al, dl
    cpu.al = cpu.dl;
    // 00421128  240f                   -and al, 0xf
    cpu.al &= x86::reg8(x86::sreg8(15 /*0xf*/));
    // 0042112a  3c02                   +cmp al, 2
    {
        x86::reg8 tmp1 = cpu.al;
        x86::reg8 tmp2 = x86::reg8(x86::sreg8(2 /*0x2*/));
        x86::reg8 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 7);
        cpu.flags.of ^= 1 & (result >> 7);
        cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
        cpu.set_szp(result);
    }
    // 0042112c  750a                   -jne 0x421138
    if (!cpu.flags.zf)
    {
        goto L_0x00421138;
    }
    // 0042112e  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 00421133  e97d000000             -jmp 0x4211b5
    goto L_0x004211b5;
L_0x00421138:
    // 00421138  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
    // 0042113a  e976000000             -jmp 0x4211b5
    goto L_0x004211b5;
L_0x0042113f:
    // 0042113f  88d0                   -mov al, dl
    cpu.al = cpu.dl;
    // 00421141  25ff000000             -and eax, 0xff
    cpu.eax &= x86::reg32(x86::sreg32(255 /*0xff*/));
    // 00421146  c1f804                 -sar eax, 4
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (4 /*0x4*/ % 32));
    // 00421149  83e00f                 -and eax, 0xf
    cpu.eax &= x86::reg32(x86::sreg32(15 /*0xf*/));
    // 0042114c  83f802                 +cmp eax, 2
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
    // 0042114f  7507                   -jne 0x421158
    if (!cpu.flags.zf)
    {
        goto L_0x00421158;
    }
    // 00421151  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 00421156  eb5d                   -jmp 0x4211b5
    goto L_0x004211b5;
L_0x00421158:
    // 00421158  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
    // 0042115a  eb59                   -jmp 0x4211b5
    goto L_0x004211b5;
L_0x0042115c:
    // 0042115c  8b1548d95d00           -mov edx, dword ptr [0x5dd948]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(6150472) /* 0x5dd948 */);
    // 00421162  01c2                   -add edx, eax
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.eax));
    // 00421164  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00421166  8a420e                 -mov al, byte ptr [edx + 0xe]
    cpu.al = app->getMemory<x86::reg8>(cpu.edx + x86::reg32(14) /* 0xe */);
    // 00421169  c1f804                 -sar eax, 4
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (4 /*0x4*/ % 32));
    // 0042116c  a80f                   +test al, 0xf
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.al & 15 /*0xf*/));
    // 0042116e  7421                   -je 0x421191
    if (cpu.flags.zf)
    {
        goto L_0x00421191;
    }
    // 00421170  83e00f                 -and eax, 0xf
    cpu.eax &= x86::reg32(x86::sreg32(15 /*0xf*/));
    // 00421173  83f802                 +cmp eax, 2
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
    // 00421176  750e                   -jne 0x421186
    if (!cpu.flags.zf)
    {
        goto L_0x00421186;
    }
    // 00421178  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 0042117d  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 0042117f  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00421180  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00421181  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00421182  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00421183  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00421184  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00421185  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x00421186:
    // 00421186  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00421188  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 0042118a  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042118b  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042118c  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042118d  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042118e  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042118f  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00421190  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x00421191:
    // 00421191  8a420e                 -mov al, byte ptr [edx + 0xe]
    cpu.al = app->getMemory<x86::reg8>(cpu.edx + x86::reg32(14) /* 0xe */);
    // 00421194  240f                   -and al, 0xf
    cpu.al &= x86::reg8(x86::sreg8(15 /*0xf*/));
    // 00421196  3c02                   +cmp al, 2
    {
        x86::reg8 tmp1 = cpu.al;
        x86::reg8 tmp2 = x86::reg8(x86::sreg8(2 /*0x2*/));
        x86::reg8 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 7);
        cpu.flags.of ^= 1 & (result >> 7);
        cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
        cpu.set_szp(result);
    }
    // 00421198  750e                   -jne 0x4211a8
    if (!cpu.flags.zf)
    {
        goto L_0x004211a8;
    }
    // 0042119a  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 0042119f  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004211a1  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004211a2  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004211a3  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004211a4  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004211a5  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004211a6  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004211a7  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004211a8:
    // 004211a8  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 004211aa  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004211ac  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004211ad  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004211ae  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004211af  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004211b0  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004211b1  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004211b2  c3                     -ret 
    cpu.esp += 4;
    return;
    // 004211b3  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
L_0x004211b5:
    // 004211b5  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004211b7  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004211b8  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004211b9  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004211ba  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004211bb  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004211bc  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004211bd  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_4211c0: native, nfs3hp::trackdata::carSectionKind */

/* align: skip 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 */
/* data blob: 0000040000000a00000014000000280000003c00000050000000700000008c00000000000000803f000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000008d80000000008d9200000000 */
void Application::sub_421360(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00421360  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00421361  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00421363  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00421364  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 0x8b 0xdb */
void Application::sub_421370(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00421370  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00421371  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00421373  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00421374  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 0x8b 0xdb */
void Application::sub_421380(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00421380  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00421381  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00421382  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00421383  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00421384  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00421386  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00421388  8d5008                 -lea edx, [eax + 8]
    cpu.edx = x86::reg32(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 0042138b  8b18                   -mov ebx, dword ptr [eax]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.eax);
    // 0042138d  8b4004                 -mov eax, dword ptr [eax + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 00421390  e84b150000             -call 0x4228e0
    cpu.esp -= 4;
    sub_4228e0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00421395  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00421397  e844aa0b00             -call 0x4dbde0
    cpu.esp -= 4;
    sub_4dbde0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042139c  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042139d  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042139e  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042139f  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004213a0  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x8d 0x40 0x00 */
void Application::sub_4213b0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004213b0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004213b1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004213b2  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004213b3  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004213b4  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004213b6  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004213b8  e823aa0b00             -call 0x4dbde0
    cpu.esp -= 4;
    sub_4dbde0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004213bd  8b4204                 -mov eax, dword ptr [edx + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(4) /* 0x4 */);
    // 004213c0  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 004213c3  8b88b0105e00           -mov ecx, dword ptr [eax + 0x5e10b0]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164656) /* 0x5e10b0 */);
    // 004213c9  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    // 004213cb  7463                   -je 0x421430
    if (cpu.flags.zf)
    {
        goto L_0x00421430;
    }
    // 004213cd  8b01                   -mov eax, dword ptr [ecx]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx);
    // 004213cf  83f808                 +cmp eax, 8
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
    // 004213d2  755c                   -jne 0x421430
    if (!cpu.flags.zf)
    {
        goto L_0x00421430;
    }
    // 004213d4  d90520105e00           -fld dword ptr [0x5e1020]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(x86::reg32(6164512) /* 0x5e1020 */));
    // 004213da  d90538105e00           -fld dword ptr [0x5e1038]
    x86::Float fpu2 = x86::Float(app->getMemory<float>(x86::reg32(6164536) /* 0x5e1038 */));
    // 004213e0  d9052c105e00           -fld dword ptr [0x5e102c]
    x86::Float fpu3 = x86::Float(app->getMemory<float>(x86::reg32(6164524) /* 0x5e102c */));
    // 004213e6  d90530105e00           -fld dword ptr [0x5e1030]
    x86::Float fpu4 = x86::Float(app->getMemory<float>(x86::reg32(6164528) /* 0x5e1030 */));
    // 004213ec  a1a0105e00             -mov eax, dword ptr [0x5e10a0]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(6164640) /* 0x5e10a0 */);
    // 004213f1  d9cb                   -fxch st(3)
    
    // 004213f3  d91d9c005600           -fstp dword ptr [0x56009c]
    app->getMemory<float>(x86::reg32(5636252) /* 0x56009c */) = float(fpu1);
    // 004213f9  a33c445600             -mov dword ptr [0x56443c], eax
    app->getMemory<x86::reg32>(x86::reg32(5653564) /* 0x56443c */) = cpu.eax;
    // 004213fe  a134105e00             -mov eax, dword ptr [0x5e1034]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(6164532) /* 0x5e1034 */);
    // 00421403  d9c9                   -fxch st(1)
    
    // 00421405  d91da0005600           -fstp dword ptr [0x5600a0]
    app->getMemory<float>(x86::reg32(5636256) /* 0x5600a0 */) = float(fpu2);
    // 0042140b  a340445600             -mov dword ptr [0x564440], eax
    app->getMemory<x86::reg32>(x86::reg32(5653568) /* 0x564440 */) = cpu.eax;
    // 00421410  a124105e00             -mov eax, dword ptr [0x5e1024]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(6164516) /* 0x5e1024 */);
    // 00421415  d91da4005600           -fstp dword ptr [0x5600a4]
    app->getMemory<float>(x86::reg32(5636260) /* 0x5600a4 */) = float(fpu3);
    // 0042141b  a334445600             -mov dword ptr [0x564434], eax
    app->getMemory<x86::reg32>(x86::reg32(5653556) /* 0x564434 */) = cpu.eax;
    // 00421420  a128105e00             -mov eax, dword ptr [0x5e1028]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(6164520) /* 0x5e1028 */);
    // 00421425  d91da8005600           -fstp dword ptr [0x5600a8]
    app->getMemory<float>(x86::reg32(5636264) /* 0x5600a8 */) = float(fpu4);
    // 0042142b  a338445600             -mov dword ptr [0x564438], eax
    app->getMemory<x86::reg32>(x86::reg32(5653560) /* 0x564438 */) = cpu.eax;
    }
L_0x00421430:
    // 00421430  8b4204                 -mov eax, dword ptr [edx + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(4) /* 0x4 */);
    // 00421433  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
    // 00421435  891c85f42f5500         -mov dword ptr [eax*4 + 0x552ff4], ebx
    app->getMemory<x86::reg32>(x86::reg32(5582836) /* 0x552ff4 */ + cpu.eax * 4) = cpu.ebx;
    // 0042143c  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042143d  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042143e  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042143f  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00421440  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x8d 0x40 0x00 */
void Application::sub_421450(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00421450  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00421451  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00421453  a3c42e5500             -mov dword ptr [0x552ec4], eax
    app->getMemory<x86::reg32>(x86::reg32(5582532) /* 0x552ec4 */) = cpu.eax;
    // 00421458  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 0042145a  7607                   -jbe 0x421463
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x00421463;
    }
    // 0042145c  83fa02                 +cmp edx, 2
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(2 /*0x2*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0042145f  7409                   -je 0x42146a
    if (cpu.flags.zf)
    {
        goto L_0x0042146a;
    }
    // 00421461  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00421462  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x00421463:
    // 00421463  e818ffffff             -call 0x421380
    cpu.esp -= 4;
    sub_421380(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00421468  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00421469  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x0042146a:
    // 0042146a  e841ffffff             -call 0x4213b0
    cpu.esp -= 4;
    sub_4213b0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042146f  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00421470  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x8d 0x40 0x00 */
void Application::sub_421480(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00421480  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00421481  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00421483  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00421484  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 0x8b 0xdb */
void Application::sub_421490(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00421490  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00421491  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00421492  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00421493  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00421494  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00421495  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00421496  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00421498  83ec20                 -sub esp, 0x20
    (cpu.esp) -= x86::reg32(x86::sreg32(32 /*0x20*/));
    // 0042149b  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 0042149d  b908000000             -mov ecx, 8
    cpu.ecx = 8 /*0x8*/;
    // 004214a2  8d7de0                 -lea edi, [ebp - 0x20]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(-32) /* -0x20 */);
    // 004214a5  beb0124200             -mov esi, 0x4212b0
    cpu.esi = 4330160 /*0x4212b0*/;
    // 004214aa  8b0485b0105e00         -mov eax, dword ptr [eax*4 + 0x5e10b0]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(6164656) /* 0x5e10b0 */ + cpu.eax * 4);
    // 004214b1  f3a5                   -rep movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004214b3  8b4804                 -mov ecx, dword ptr [eax + 4]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 004214b6  d981c0070000           -fld dword ptr [ecx + 0x7c0]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(1984) /* 0x7c0 */));
    // 004214bc  dc0d046e5300           -fmul qword ptr [0x536e04]
    x86::Float fpu2 = cpu.fpu.mul(fpu1, x86::Float(app->getMemory<double>(x86::reg32(5467652) /* 0x536e04 */)));
    // 004214c2  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 004214c5  db1c24                 -fistp dword ptr [esp]
    app->getMemory<x86::reg32>(cpu.esp) = x86::reg32(cpu.fpu.toInteger<x86::sreg32>(fpu2));
    // 004214c8  58                     -pop eax
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004214c9  8b35b0d36f00           -mov esi, dword ptr [0x6fd3b0]
    cpu.esi = app->getMemory<x86::reg32>(x86::reg32(7328688) /* 0x6fd3b0 */);
    // 004214cf  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 004214d1  83fe01                 +cmp esi, 1
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
    }
    // 004214d4  7504                   -jne 0x4214da
    if (!cpu.flags.zf)
    {
        goto L_0x004214da;
    }
    // 004214d6  21f2                   +and edx, esi
    cpu.clear_co();
    cpu.set_szp((cpu.edx &= x86::reg32(x86::sreg32(cpu.esi))));
    // 004214d8  eb02                   -jmp 0x4214dc
    goto L_0x004214dc;
L_0x004214da:
    // 004214da  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
L_0x004214dc:
    // 004214dc  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
L_0x004214de:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004214de  3b5c85e4               +cmp ebx, dword ptr [ebp + eax*4 - 0x1c]
    {
        x86::reg32 tmp1 = cpu.ebx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-28) /* -0x1c */ + cpu.eax * 4)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004214e2  7e03                   -jle 0x4214e7
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004214e7;
    }
    // 004214e4  40                     +inc eax
    {
        x86::reg32& tmp = cpu.eax;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 004214e5  ebf7                   -jmp 0x4214de
    goto L_0x004214de;
L_0x004214e7:
    // 004214e7  8b7485e0               -mov esi, dword ptr [ebp + eax*4 - 0x20]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-32) /* -0x20 */ + cpu.eax * 4);
    // 004214eb  89049514305500         -mov dword ptr [edx*4 + 0x553014], eax
    app->getMemory<x86::reg32>(x86::reg32(5582868) /* 0x553014 */ + cpu.edx * 4) = cpu.eax;
    // 004214f2  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 004214f4  29f0                   -sub eax, esi
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.esi));
    // 004214f6  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004214f8  7d12                   -jge 0x42150c
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x0042150c;
    }
    // 004214fa  8b411c                 -mov eax, dword ptr [ecx + 0x1c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(28) /* 0x1c */);
    // 004214fd  83e803                 -sub eax, 3
    (cpu.eax) -= x86::reg32(x86::sreg32(3 /*0x3*/));
    // 00421500  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00421502  7d50                   -jge 0x421554
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00421554;
    }
    // 00421504  030540d95d00           +add eax, dword ptr [0x5dd940]
    {
        x86::reg32& tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(6150464) /* 0x5dd940 */)));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 0042150a  eb48                   -jmp 0x421554
    goto L_0x00421554;
L_0x0042150c:
    // 0042150c  3d00000300             +cmp eax, 0x30000
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(196608 /*0x30000*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00421511  7d14                   -jge 0x421527
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00421527;
    }
    // 00421513  8b411c                 -mov eax, dword ptr [ecx + 0x1c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(28) /* 0x1c */);
    // 00421516  8b0d40d95d00           -mov ecx, dword ptr [0x5dd940]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(6150464) /* 0x5dd940 */);
    // 0042151c  83c003                 -add eax, 3
    (cpu.eax) += x86::reg32(x86::sreg32(3 /*0x3*/));
    // 0042151f  39c8                   +cmp eax, ecx
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
    // 00421521  7c31                   -jl 0x421554
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x00421554;
    }
    // 00421523  29c8                   +sub eax, ecx
    {
        x86::reg32& tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ecx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 00421525  eb2d                   -jmp 0x421554
    goto L_0x00421554;
L_0x00421527:
    // 00421527  3d00001400             +cmp eax, 0x140000
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1310720 /*0x140000*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0042152c  7d14                   -jge 0x421542
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00421542;
    }
    // 0042152e  8b411c                 -mov eax, dword ptr [ecx + 0x1c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(28) /* 0x1c */);
    // 00421531  8b3540d95d00           -mov esi, dword ptr [0x5dd940]
    cpu.esi = app->getMemory<x86::reg32>(x86::reg32(6150464) /* 0x5dd940 */);
    // 00421537  83c005                 -add eax, 5
    (cpu.eax) += x86::reg32(x86::sreg32(5 /*0x5*/));
    // 0042153a  39f0                   +cmp eax, esi
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
    // 0042153c  7c16                   -jl 0x421554
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x00421554;
    }
    // 0042153e  29f0                   +sub eax, esi
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
    // 00421540  eb12                   -jmp 0x421554
    goto L_0x00421554;
L_0x00421542:
    // 00421542  8b411c                 -mov eax, dword ptr [ecx + 0x1c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(28) /* 0x1c */);
    // 00421545  8b0d40d95d00           -mov ecx, dword ptr [0x5dd940]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(6150464) /* 0x5dd940 */);
    // 0042154b  83c007                 -add eax, 7
    (cpu.eax) += x86::reg32(x86::sreg32(7 /*0x7*/));
    // 0042154e  39c8                   +cmp eax, ecx
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
    // 00421550  7c02                   -jl 0x421554
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x00421554;
    }
    // 00421552  29c8                   -sub eax, ecx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.ecx));
L_0x00421554:
    // 00421554  8904950c305500         -mov dword ptr [edx*4 + 0x55300c], eax
    app->getMemory<x86::reg32>(x86::reg32(5582860) /* 0x55300c */ + cpu.edx * 4) = cpu.eax;
    // 0042155b  31f6                   -xor esi, esi
    cpu.esi ^= x86::reg32(x86::sreg32(cpu.esi));
    // 0042155d  89349504305500         -mov dword ptr [edx*4 + 0x553004], esi
    app->getMemory<x86::reg32>(x86::reg32(5582852) /* 0x553004 */ + cpu.edx * 4) = cpu.esi;
    // 00421564  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00421566  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00421567  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00421568  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00421569  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042156a  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042156b  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042156c  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x40 0x00 */
void Application::sub_421570(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00421570  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00421571  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00421572  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00421574  d900                   -fld dword ptr [eax]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.eax));
    // 00421576  d9e0                   -fchs 
    x86::Float fpu2 = -fpu1;
    // 00421578  d91a                   -fstp dword ptr [edx]
    app->getMemory<float>(cpu.edx) = float(fpu2);
    // 0042157a  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu3 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 0042157d  d9e0                   -fchs 
    x86::Float fpu4 = -fpu3;
    // 0042157f  d95a04                 -fstp dword ptr [edx + 4]
    app->getMemory<float>(cpu.edx + x86::reg32(4) /* 0x4 */) = float(fpu4);
    // 00421582  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu5 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 00421585  d9e0                   -fchs 
    x86::Float fpu6 = -fpu5;
    // 00421587  d95a08                 -fstp dword ptr [edx + 8]
    app->getMemory<float>(cpu.edx + x86::reg32(8) /* 0x8 */) = float(fpu6);
    // 0042158a  8b480c                 -mov ecx, dword ptr [eax + 0xc]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
    // 0042158d  894a0c                 -mov dword ptr [edx + 0xc], ecx
    app->getMemory<x86::reg32>(cpu.edx + x86::reg32(12) /* 0xc */) = cpu.ecx;
    // 00421590  8b4810                 -mov ecx, dword ptr [eax + 0x10]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(16) /* 0x10 */);
    // 00421593  894a10                 -mov dword ptr [edx + 0x10], ecx
    app->getMemory<x86::reg32>(cpu.edx + x86::reg32(16) /* 0x10 */) = cpu.ecx;
    // 00421596  8b4814                 -mov ecx, dword ptr [eax + 0x14]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */);
    // 00421599  894a14                 -mov dword ptr [edx + 0x14], ecx
    app->getMemory<x86::reg32>(cpu.edx + x86::reg32(20) /* 0x14 */) = cpu.ecx;
    // 0042159c  d94018                 -fld dword ptr [eax + 0x18]
    x86::Float fpu7 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(24) /* 0x18 */));
    // 0042159f  d9e0                   -fchs 
    x86::Float fpu8 = -fpu7;
    // 004215a1  d95a18                 -fstp dword ptr [edx + 0x18]
    app->getMemory<float>(cpu.edx + x86::reg32(24) /* 0x18 */) = float(fpu8);
    // 004215a4  d9401c                 -fld dword ptr [eax + 0x1c]
    x86::Float fpu9 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(28) /* 0x1c */));
    // 004215a7  d9e0                   -fchs 
    x86::Float fpu10 = -fpu9;
    // 004215a9  d95a1c                 -fstp dword ptr [edx + 0x1c]
    app->getMemory<float>(cpu.edx + x86::reg32(28) /* 0x1c */) = float(fpu10);
    // 004215ac  d94020                 -fld dword ptr [eax + 0x20]
    x86::Float fpu11 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(32) /* 0x20 */));
    // 004215af  d9e0                   -fchs 
    x86::Float fpu12 = -fpu11;
    // 004215b1  d95a20                 -fstp dword ptr [edx + 0x20]
    app->getMemory<float>(cpu.edx + x86::reg32(32) /* 0x20 */) = float(fpu12);
    // 004215b4  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004215b5  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    }
    // 004215b6  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 */
void Application::sub_4215c0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004215c0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004215c1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004215c2  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004215c3  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004215c4  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004215c5  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004215c7  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 004215ca  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 004215cc  8b0db0d36f00           -mov ecx, dword ptr [0x6fd3b0]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(7328688) /* 0x6fd3b0 */);
    // 004215d2  83f901                 +cmp ecx, 1
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1 /*0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004215d5  7504                   -jne 0x4215db
    if (!cpu.flags.zf)
    {
        goto L_0x004215db;
    }
    // 004215d7  21cb                   +and ebx, ecx
    cpu.clear_co();
    cpu.set_szp((cpu.ebx &= x86::reg32(x86::sreg32(cpu.ecx))));
    // 004215d9  eb02                   -jmp 0x4215dd
    goto L_0x004215dd;
L_0x004215db:
    // 004215db  31c3                   -xor ebx, eax
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.eax));
L_0x004215dd:
    // 004215dd  8b3598fd5e00           -mov esi, dword ptr [0x5efd98]
    cpu.esi = app->getMemory<x86::reg32>(x86::reg32(6225304) /* 0x5efd98 */);
    // 004215e3  a1a4fd5e00             -mov eax, dword ptr [0x5efda4]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(6225316) /* 0x5efda4 */);
    // 004215e8  01f0                   -add eax, esi
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.esi));
    // 004215ea  39c2                   +cmp edx, eax
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.eax));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004215ec  0f8d32010000           -jge 0x421724
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00421724;
    }
    // 004215f2  8d049d00000000         -lea eax, [ebx*4]
    cpu.eax = x86::reg32(cpu.ebx * 4);
    // 004215f9  8bb8b8105e00           -mov edi, dword ptr [eax + 0x5e10b8]
    cpu.edi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164664) /* 0x5e10b8 */);
    // 004215ff  85ff                   +test edi, edi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edi & cpu.edi));
    // 00421601  740a                   -je 0x42160d
    if (cpu.flags.zf)
    {
        goto L_0x0042160d;
    }
    // 00421603  7404                   -je 0x421609
    if (cpu.flags.zf)
    {
        goto L_0x00421609;
    }
    // 00421605  8b07                   -mov eax, dword ptr [edi]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edi);
    // 00421607  eb14                   -jmp 0x42161d
    goto L_0x0042161d;
L_0x00421609:
    // 00421609  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
    // 0042160b  eb10                   -jmp 0x42161d
    goto L_0x0042161d;
L_0x0042160d:
    // 0042160d  8bb0b0105e00           -mov esi, dword ptr [eax + 0x5e10b0]
    cpu.esi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164656) /* 0x5e10b0 */);
    // 00421613  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 00421615  7404                   -je 0x42161b
    if (cpu.flags.zf)
    {
        goto L_0x0042161b;
    }
    // 00421617  8b06                   -mov eax, dword ptr [esi]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi);
    // 00421619  eb02                   -jmp 0x42161d
    goto L_0x0042161d;
L_0x0042161b:
    // 0042161b  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
L_0x0042161d:
    // 0042161d  83f811                 +cmp eax, 0x11
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(17 /*0x11*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00421620  7523                   -jne 0x421645
    if (!cpu.flags.zf)
    {
        goto L_0x00421645;
    }
    // 00421622  8b0c9d502f5500         -mov ecx, dword ptr [ebx*4 + 0x552f50]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(5582672) /* 0x552f50 */ + cpu.ebx * 4);
    // 00421629  8bb918010000           -mov edi, dword ptr [ecx + 0x118]
    cpu.edi = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(280) /* 0x118 */);
    // 0042162f  83ffff                 +cmp edi, -1
    {
        x86::reg32 tmp1 = cpu.edi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(-1 /*-0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00421632  7411                   -je 0x421645
    if (cpu.flags.zf)
    {
        goto L_0x00421645;
    }
    // 00421634  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 00421636  e825defeff             -call 0x40f460
    cpu.esp -= 4;
    sub_40f460(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042163b  c78118010000ffffffff   -mov dword ptr [ecx + 0x118], 0xffffffff
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(280) /* 0x118 */) = 4294967295 /*0xffffffff*/;
L_0x00421645:
    // 00421645  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 00421647  e8c44c0000             -call 0x426310
    cpu.esp -= 4;
    sub_426310(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042164c  8d049d00000000         -lea eax, [ebx*4]
    cpu.eax = x86::reg32(cpu.ebx * 4);
    // 00421653  8b88b8105e00           -mov ecx, dword ptr [eax + 0x5e10b8]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164664) /* 0x5e10b8 */);
    // 00421659  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    // 0042165b  7404                   -je 0x421661
    if (cpu.flags.zf)
    {
        goto L_0x00421661;
    }
    // 0042165d  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 0042165f  eb06                   -jmp 0x421667
    goto L_0x00421667;
L_0x00421661:
    // 00421661  8b80b0105e00           -mov eax, dword ptr [eax + 0x5e10b0]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164656) /* 0x5e10b0 */);
L_0x00421667:
    // 00421667  8b4008                 -mov eax, dword ptr [eax + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 0042166a  3b0495c8fa5e00         +cmp eax, dword ptr [edx*4 + 0x5efac8]
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(6224584) /* 0x5efac8 */ + cpu.edx * 4)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00421671  740b                   -je 0x42167e
    if (cpu.flags.zf)
    {
        goto L_0x0042167e;
    }
    // 00421673  c7049df42f550001000000 -mov dword ptr [ebx*4 + 0x552ff4], 1
    app->getMemory<x86::reg32>(x86::reg32(5582836) /* 0x552ff4 */ + cpu.ebx * 4) = 1 /*0x1*/;
L_0x0042167e:
    // 0042167e  8d049d00000000         -lea eax, [ebx*4]
    cpu.eax = x86::reg32(cpu.ebx * 4);
    // 00421685  8b88b8105e00           -mov ecx, dword ptr [eax + 0x5e10b8]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164664) /* 0x5e10b8 */);
    // 0042168b  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    // 0042168d  7404                   -je 0x421693
    if (cpu.flags.zf)
    {
        goto L_0x00421693;
    }
    // 0042168f  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00421691  eb06                   -jmp 0x421699
    goto L_0x00421699;
L_0x00421693:
    // 00421693  8b80b0105e00           -mov eax, dword ptr [eax + 0x5e10b0]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164656) /* 0x5e10b0 */);
L_0x00421699:
    // 00421699  8b4004                 -mov eax, dword ptr [eax + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 0042169c  3b0495c8fa5e00         +cmp eax, dword ptr [edx*4 + 0x5efac8]
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(6224584) /* 0x5efac8 */ + cpu.edx * 4)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004216a3  740b                   -je 0x4216b0
    if (cpu.flags.zf)
    {
        goto L_0x004216b0;
    }
    // 004216a5  c7049df42f550001000000 -mov dword ptr [ebx*4 + 0x552ff4], 1
    app->getMemory<x86::reg32>(x86::reg32(5582836) /* 0x552ff4 */ + cpu.ebx * 4) = 1 /*0x1*/;
L_0x004216b0:
    // 004216b0  c745fc01000000         -mov dword ptr [ebp - 4], 1
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = 1 /*0x1*/;
    // 004216b7  eb06                   -jmp 0x4216bf
    goto L_0x004216bf;
L_0x004216b9:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004216b9  837dfc19               +cmp dword ptr [ebp - 4], 0x19
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(25 /*0x19*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004216bd  7d59                   -jge 0x421718
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00421718;
    }
L_0x004216bf:
    // 004216bf  8b4dfc                 -mov ecx, dword ptr [ebp - 4]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004216c2  8d049d00000000         -lea eax, [ebx*4]
    cpu.eax = x86::reg32(cpu.ebx * 4);
    // 004216c9  8b84c8c82e5500         -mov eax, dword ptr [eax + ecx*8 + 0x552ec8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(5582536) /* 0x552ec8 */ + cpu.ecx * 8);
    // 004216d0  8b3495c8fa5e00         -mov esi, dword ptr [edx*4 + 0x5efac8]
    cpu.esi = app->getMemory<x86::reg32>(x86::reg32(6224584) /* 0x5efac8 */ + cpu.edx * 4);
    // 004216d7  897004                 -mov dword ptr [eax + 4], esi
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */) = cpu.esi;
    // 004216da  897008                 -mov dword ptr [eax + 8], esi
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */) = cpu.esi;
    // 004216dd  89f1                   -mov ecx, esi
    cpu.ecx = cpu.esi;
    // 004216df  8d782c                 -lea edi, [eax + 0x2c]
    cpu.edi = x86::reg32(cpu.eax + x86::reg32(44) /* 0x2c */);
    // 004216e2  d98198000000           +fld dword ptr [ecx + 0x98]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(152) /* 0x98 */));
    // 004216e8  8b7004                 -mov esi, dword ptr [eax + 4]
    cpu.esi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 004216eb  8b4804                 -mov ecx, dword ptr [eax + 4]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 004216ee  d95814                 +fstp dword ptr [eax + 0x14]
    app->getMemory<float>(cpu.eax + x86::reg32(20) /* 0x14 */) = float(fpu1);
    // 004216f1  d9819c000000           +fld dword ptr [ecx + 0x9c]
    x86::Float fpu2 = x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(156) /* 0x9c */));
    // 004216f7  8b4804                 -mov ecx, dword ptr [eax + 4]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 004216fa  d95818                 +fstp dword ptr [eax + 0x18]
    app->getMemory<float>(cpu.eax + x86::reg32(24) /* 0x18 */) = float(fpu2);
    // 004216fd  d981a0000000           +fld dword ptr [ecx + 0xa0]
    x86::Float fpu3 = x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(160) /* 0xa0 */));
    // 00421703  b909000000             -mov ecx, 9
    cpu.ecx = 9 /*0x9*/;
    // 00421708  d9581c                 +fstp dword ptr [eax + 0x1c]
    app->getMemory<float>(cpu.eax + x86::reg32(28) /* 0x1c */) = float(fpu3);
    // 0042170b  8db6c0000000           -lea esi, [esi + 0xc0]
    cpu.esi = x86::reg32(cpu.esi + x86::reg32(192) /* 0xc0 */);
    // 00421711  f3a5                   -rep movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00421713  ff45fc                 +inc dword ptr [ebp - 4]
    {
        auto tmp = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    }
    // 00421716  eba1                   -jmp 0x4216b9
    goto L_0x004216b9;
L_0x00421718:
    // 00421718  ba03000000             -mov edx, 3
    cpu.edx = 3 /*0x3*/;
    // 0042171d  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 0042171f  e88c210000             -call 0x4238b0
    cpu.esp -= 4;
    sub_4238b0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00421724:
    // 00421724  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00421726  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00421727  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00421728  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00421729  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042172a  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042172b  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x44 0x20 0x00 */
void Application::sub_421730(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00421730  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00421731  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00421732  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00421733  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00421734  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00421736  83ec74                 -sub esp, 0x74
    (cpu.esp) -= x86::reg32(x86::sreg32(116 /*0x74*/));
    // 00421739  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 0042173b  8b9104010000           -mov edx, dword ptr [ecx + 0x104]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(260) /* 0x104 */);
    // 00421741  8b4004                 -mov eax, dword ptr [eax + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 00421744  83fa01                 +cmp edx, 1
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
    // 00421747  751a                   -jne 0x421763
    if (!cpu.flags.zf)
    {
        goto L_0x00421763;
    }
    // 00421749  d98020090000           +fld dword ptr [eax + 0x920]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(2336) /* 0x920 */));
    // 0042174f  8b9024090000           -mov edx, dword ptr [eax + 0x924]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(2340) /* 0x924 */);
    // 00421755  d80d0c6e5300           +fmul dword ptr [0x536e0c]
    x86::Float fpu2 = cpu.fpu.mul(fpu1, x86::Float(app->getMemory<float>(x86::reg32(5467660) /* 0x536e0c */)));
    // 0042175b  8955fc                 -mov dword ptr [ebp - 4], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.edx;
    // 0042175e  d95df8                 +fstp dword ptr [ebp - 8]
    app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = float(fpu2);
    }
    // 00421761  eb18                   -jmp 0x42177b
    goto L_0x0042177b;
L_0x00421763:
    // 00421763  d98024090000           -fld dword ptr [eax + 0x924]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu3 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(2340) /* 0x924 */));
    // 00421769  8b9020090000           -mov edx, dword ptr [eax + 0x920]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(2336) /* 0x920 */);
    // 0042176f  d80d106e5300           -fmul dword ptr [0x536e10]
    x86::Float fpu4 = cpu.fpu.mul(fpu3, x86::Float(app->getMemory<float>(x86::reg32(5467664) /* 0x536e10 */)));
    // 00421775  8955f8                 -mov dword ptr [ebp - 8], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.edx;
    // 00421778  d95dfc                 -fstp dword ptr [ebp - 4]
    app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = float(fpu4);
    }
L_0x0042177b:
    // 0042177b  81b8a405000000007042   +cmp dword ptr [eax + 0x5a4], 0x42700000
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(1444) /* 0x5a4 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1114636288 /*0x42700000*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00421785  7e0c                   -jle 0x421793
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00421793;
    }
    // 00421787  d945fc                 -fld dword ptr [ebp - 4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu5 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */));
    // 0042178a  d80d106e5300           -fmul dword ptr [0x536e10]
    x86::Float fpu6 = cpu.fpu.mul(fpu5, x86::Float(app->getMemory<float>(x86::reg32(5467664) /* 0x536e10 */)));
    // 00421790  d95dfc                 -fstp dword ptr [ebp - 4]
    app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = float(fpu6);
    }
L_0x00421793:
    // 00421793  8d458c                 -lea eax, [ebp - 0x74]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-116) /* -0x74 */);
    // 00421796  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00421797  ff75fc                 -push dword ptr [ebp - 4]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    cpu.esp -= 4;
    // 0042179a  b898445600             -mov eax, 0x564498
    cpu.eax = 5653656 /*0x564498*/;
    // 0042179f  8d5dd4                 -lea ebx, [ebp - 0x2c]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-44) /* -0x2c */);
    // 004217a2  e879900c00             -call 0x4ea820
    cpu.esp -= 4;
    sub_4ea820(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004217a7  8d45b0                 -lea eax, [ebp - 0x50]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-80) /* -0x50 */);
    // 004217aa  d945f8                 -fld dword ptr [ebp - 8]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu7 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */));
    // 004217ad  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004217ae  d84150                 -fadd dword ptr [ecx + 0x50]
    x86::Float fpu8 = cpu.fpu.add(fpu7, x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(80) /* 0x50 */)));
    // 004217b1  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 004217b4  b898445600             -mov eax, 0x564498
    cpu.eax = 5653656 /*0x564498*/;
    // 004217b9  d91c24                 -fstp dword ptr [esp]
    app->getMemory<float>(cpu.esp) = float(fpu8);
    // 004217bc  8d55b0                 -lea edx, [ebp - 0x50]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-80) /* -0x50 */);
    }
    // 004217bf  e8bc8e0c00             -call 0x4ea680
    cpu.esp -= 4;
    sub_4ea680(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004217c4  8d458c                 -lea eax, [ebp - 0x74]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-116) /* -0x74 */);
    // 004217c7  e8b4ea0b00             -call 0x4e0280
    cpu.esp -= 4;
    sub_4e0280(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004217cc  8d512c                 -lea edx, [ecx + 0x2c]
    cpu.edx = x86::reg32(cpu.ecx + x86::reg32(44) /* 0x2c */);
    // 004217cf  8d45d4                 -lea eax, [ebp - 0x2c]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-44) /* -0x2c */);
    // 004217d2  89d3                   -mov ebx, edx
    cpu.ebx = cpu.edx;
    // 004217d4  e8a7ea0b00             -call 0x4e0280
    cpu.esp -= 4;
    sub_4e0280(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004217d9  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004217db  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004217dc  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004217dd  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004217de  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004217df  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip  */
void Application::sub_4217e0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004217e0  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004217e1  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004217e2  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004217e3  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004217e4  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004217e5  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004217e7  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004217e9  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 004217ec  8b88b8105e00           -mov ecx, dword ptr [eax + 0x5e10b8]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164664) /* 0x5e10b8 */);
    // 004217f2  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    // 004217f4  740c                   -je 0x421802
    if (cpu.flags.zf)
    {
        goto L_0x00421802;
    }
    // 004217f6  7404                   -je 0x4217fc
    if (cpu.flags.zf)
    {
        goto L_0x004217fc;
    }
    // 004217f8  8b01                   -mov eax, dword ptr [ecx]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx);
    // 004217fa  eb02                   -jmp 0x4217fe
    goto L_0x004217fe;
L_0x004217fc:
    // 004217fc  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
L_0x004217fe:
    // 004217fe  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00421800  eb0c                   -jmp 0x42180e
    goto L_0x0042180e;
L_0x00421802:
    // 00421802  8bb0b0105e00           -mov esi, dword ptr [eax + 0x5e10b0]
    cpu.esi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164656) /* 0x5e10b0 */);
    // 00421808  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 0042180a  7402                   -je 0x42180e
    if (cpu.flags.zf)
    {
        goto L_0x0042180e;
    }
    // 0042180c  8b0e                   -mov ecx, dword ptr [esi]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esi);
L_0x0042180e:
    // 0042180e  8d049500000000         -lea eax, [edx*4]
    cpu.eax = x86::reg32(cpu.edx * 4);
    // 00421815  83f913                 +cmp ecx, 0x13
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(19 /*0x13*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00421818  752a                   -jne 0x421844
    if (!cpu.flags.zf)
    {
        goto L_0x00421844;
    }
    // 0042181a  8bb8b8105e00           -mov edi, dword ptr [eax + 0x5e10b8]
    cpu.edi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164664) /* 0x5e10b8 */);
    // 00421820  85ff                   +test edi, edi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edi & cpu.edi));
    // 00421822  7404                   -je 0x421828
    if (cpu.flags.zf)
    {
        goto L_0x00421828;
    }
    // 00421824  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 00421826  eb06                   -jmp 0x42182e
    goto L_0x0042182e;
L_0x00421828:
    // 00421828  8b80b0105e00           -mov eax, dword ptr [eax + 0x5e10b0]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164656) /* 0x5e10b0 */);
L_0x0042182e:
    // 0042182e  8b801c010000           -mov eax, dword ptr [eax + 0x11c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(284) /* 0x11c */);
    // 00421834  8d0cc500000000         -lea ecx, [eax*8]
    cpu.ecx = x86::reg32(cpu.eax * 8);
    // 0042183b  8b8491c82e5500         -mov eax, dword ptr [ecx + edx*4 + 0x552ec8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(5582536) /* 0x552ec8 */ + cpu.edx * 4);
    // 00421842  eb14                   -jmp 0x421858
    goto L_0x00421858;
L_0x00421844:
    // 00421844  8b90b8105e00           -mov edx, dword ptr [eax + 0x5e10b8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164664) /* 0x5e10b8 */);
    // 0042184a  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 0042184c  7404                   -je 0x421852
    if (cpu.flags.zf)
    {
        goto L_0x00421852;
    }
    // 0042184e  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 00421850  eb06                   -jmp 0x421858
    goto L_0x00421858;
L_0x00421852:
    // 00421852  8b80b0105e00           -mov eax, dword ptr [eax + 0x5e10b0]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164656) /* 0x5e10b0 */);
L_0x00421858:
    // 00421858  8b88ec000000           -mov ecx, dword ptr [eax + 0xec]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(236) /* 0xec */);
    // 0042185e  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    // 00421860  7c04                   -jl 0x421866
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x00421866;
    }
    // 00421862  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00421864  eb06                   -jmp 0x42186c
    goto L_0x0042186c;
L_0x00421866:
    // 00421866  8b8084000000           -mov eax, dword ptr [eax + 0x84]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(132) /* 0x84 */);
L_0x0042186c:
    // 0042186c  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042186d  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042186e  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042186f  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00421870  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00421871  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x8b 0xc0 */
void Application::sub_421880(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00421880  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00421881  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00421882  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00421883  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00421884  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00421885  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00421887  83ec0c                 -sub esp, 0xc
    (cpu.esp) -= x86::reg32(x86::sreg32(12 /*0xc*/));
    // 0042188a  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 0042188c  d902                   -fld dword ptr [edx]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.edx));
    // 0042188e  dc0d146e5300           -fmul qword ptr [0x536e14]
    x86::Float fpu2 = cpu.fpu.mul(fpu1, x86::Float(app->getMemory<double>(x86::reg32(5467668) /* 0x536e14 */)));
    // 00421894  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 00421897  db1c24                 -fistp dword ptr [esp]
    app->getMemory<x86::reg32>(cpu.esp) = x86::reg32(cpu.fpu.toInteger<x86::sreg32>(fpu2));
    // 0042189a  58                     -pop eax
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042189b  8945f4                 -mov dword ptr [ebp - 0xc], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.eax;
    // 0042189e  d94204                 -fld dword ptr [edx + 4]
    x86::Float fpu3 = x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(4) /* 0x4 */));
    // 004218a1  dc0d146e5300           -fmul qword ptr [0x536e14]
    x86::Float fpu4 = cpu.fpu.mul(fpu3, x86::Float(app->getMemory<double>(x86::reg32(5467668) /* 0x536e14 */)));
    // 004218a7  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 004218aa  db1c24                 -fistp dword ptr [esp]
    app->getMemory<x86::reg32>(cpu.esp) = x86::reg32(cpu.fpu.toInteger<x86::sreg32>(fpu4));
    // 004218ad  58                     -pop eax
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004218ae  8945f8                 -mov dword ptr [ebp - 8], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.eax;
    // 004218b1  d94208                 -fld dword ptr [edx + 8]
    x86::Float fpu5 = x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(8) /* 0x8 */));
    // 004218b4  dc0d146e5300           -fmul qword ptr [0x536e14]
    x86::Float fpu6 = cpu.fpu.mul(fpu5, x86::Float(app->getMemory<double>(x86::reg32(5467668) /* 0x536e14 */)));
    // 004218ba  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 004218bd  db1c24                 -fistp dword ptr [esp]
    app->getMemory<x86::reg32>(cpu.esp) = x86::reg32(cpu.fpu.toInteger<x86::sreg32>(fpu6));
    // 004218c0  58                     -pop eax
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004218c1  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 004218c4  8b4304                 -mov eax, dword ptr [ebx + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(4) /* 0x4 */);
    // 004218c7  b91e000000             -mov ecx, 0x1e
    cpu.ecx = 30 /*0x1e*/;
    // 004218cc  8d7b74                 -lea edi, [ebx + 0x74]
    cpu.edi = x86::reg32(cpu.ebx + x86::reg32(116) /* 0x74 */);
    // 004218cf  8d700c                 -lea esi, [eax + 0xc]
    cpu.esi = x86::reg32(cpu.eax + x86::reg32(12) /* 0xc */);
    // 004218d2  f3a5                   -rep movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004218d4  8d4b74                 -lea ecx, [ebx + 0x74]
    cpu.ecx = x86::reg32(cpu.ebx + x86::reg32(116) /* 0x74 */);
    // 004218d7  8d45f4                 -lea eax, [ebp - 0xc]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 004218da  89ca                   -mov edx, ecx
    cpu.edx = cpu.ecx;
    // 004218dc  bb01000000             -mov ebx, 1
    cpu.ebx = 1 /*0x1*/;
    }
    // 004218e1  e83acbffff             -call 0x41e420
    cpu.esp -= 4;
    nfs3hp::trackdata::followNode(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004218e6  8d45f4                 -lea eax, [ebp - 0xc]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 004218e9  89ca                   -mov edx, ecx
    cpu.edx = cpu.ecx;
    // 004218eb  e8f0ddffff             -call 0x41f6e0
    cpu.esp -= 4;
    nfs3hp::trackdata::updatePosition(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004218f0  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004218f2  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004218f3  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004218f4  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004218f5  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004218f6  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004218f7  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8b 0xd2 */
void Application::sub_421900(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00421900  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00421901  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00421902  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00421903  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00421904  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00421905  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00421906  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00421908  81ec88000000           -sub esp, 0x88
    (cpu.esp) -= x86::reg32(x86::sreg32(136 /*0x88*/));
    // 0042190e  81ed82000000           -sub ebp, 0x82
    (cpu.ebp) -= x86::reg32(x86::sreg32(130 /*0x82*/));
    // 00421914  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 00421916  31f6                   -xor esi, esi
    cpu.esi ^= x86::reg32(x86::sreg32(cpu.esi));
L_0x00421918:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00421918  3b359cfd5e00           +cmp esi, dword ptr [0x5efd9c]
    {
        x86::reg32 tmp1 = cpu.esi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(6225308) /* 0x5efd9c */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0042191e  0f8d5e020000           -jge 0x421b82
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00421b82;
    }
    // 00421924  8b0cb5c8fa5e00         -mov ecx, dword ptr [esi*4 + 0x5efac8]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(6224584) /* 0x5efac8 */ + cpu.esi * 4);
    // 0042192b  8aa189000000           -mov ah, byte ptr [ecx + 0x89]
    cpu.ah = app->getMemory<x86::reg8>(cpu.ecx + x86::reg32(137) /* 0x89 */);
    // 00421931  84e4                   +test ah, ah
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.ah & cpu.ah));
    // 00421933  0f8443020000           -je 0x421b7c
    if (cpu.flags.zf)
    {
        goto L_0x00421b7c;
    }
    // 00421939  80b98800000000         +cmp byte ptr [ecx + 0x88], 0
    {
        x86::reg8 tmp1 = app->getMemory<x86::reg8>(cpu.ecx + x86::reg32(136) /* 0x88 */);
        x86::reg8 tmp2 = x86::reg8(x86::sreg8(0 /*0x0*/));
        x86::reg8 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 7);
        cpu.flags.of ^= 1 & (result >> 7);
        cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
        cpu.set_szp(result);
    }
    // 00421940  0f8536020000           -jne 0x421b7c
    if (!cpu.flags.zf)
    {
        goto L_0x00421b7c;
    }
    // 00421946  d98120010000           +fld dword ptr [ecx + 0x120]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(288) /* 0x120 */));
    // 0042194c  8d8198000000           -lea eax, [ecx + 0x98]
    cpu.eax = x86::reg32(cpu.ecx + x86::reg32(152) /* 0x98 */);
    // 00421952  dc051c6e5300           +fadd qword ptr [0x536e1c]
    x86::Float fpu2 = cpu.fpu.add(fpu1, x86::Float(app->getMemory<double>(x86::reg32(5467676) /* 0x536e1c */)));
    // 00421958  89da                   -mov edx, ebx
    cpu.edx = cpu.ebx;
    // 0042195a  dd5d5a                 +fstp qword ptr [ebp + 0x5a]
    app->getMemory<double>(cpu.ebp + x86::reg32(90) /* 0x5a */) = double(fpu2);
    }
    // 0042195d  e84e4c0700             -call 0x4965b0
    cpu.esp -= 4;
    sub_4965b0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00421962  dc5d5a                 +fcomp qword ptr [ebp + 0x5a]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu3 = cpu.fpu.st(0);
    cpu.fpu.compare(fpu3, x86::Float(app->getMemory<double>(cpu.ebp + x86::reg32(90) /* 0x5a */)));
    // 00421965  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00421967  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    cpu.fpu.count -= 1;
    }
    // 00421968  0f870e020000           -ja 0x421b7c
    if (!cpu.flags.cf && !cpu.flags.zf)
    {
        goto L_0x00421b7c;
    }
    // 0042196e  d903                   +fld dword ptr [ebx]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu4 = x86::Float(app->getMemory<float>(cpu.ebx));
    // 00421970  d8a198000000           +fsub dword ptr [ecx + 0x98]
    x86::Float fpu5 = cpu.fpu.sub(fpu4, x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(152) /* 0x98 */)));
    // 00421976  d95d2a                 +fstp dword ptr [ebp + 0x2a]
    app->getMemory<float>(cpu.ebp + x86::reg32(42) /* 0x2a */) = float(fpu5);
    // 00421979  d94304                 +fld dword ptr [ebx + 4]
    x86::Float fpu6 = x86::Float(app->getMemory<float>(cpu.ebx + x86::reg32(4) /* 0x4 */));
    // 0042197c  d8a19c000000           +fsub dword ptr [ecx + 0x9c]
    x86::Float fpu7 = cpu.fpu.sub(fpu6, x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(156) /* 0x9c */)));
    // 00421982  8d452a                 -lea eax, [ebp + 0x2a]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(42) /* 0x2a */);
    // 00421985  d95d2e                 +fstp dword ptr [ebp + 0x2e]
    app->getMemory<float>(cpu.ebp + x86::reg32(46) /* 0x2e */) = float(fpu7);
    // 00421988  d94308                 +fld dword ptr [ebx + 8]
    x86::Float fpu8 = x86::Float(app->getMemory<float>(cpu.ebx + x86::reg32(8) /* 0x8 */));
    // 0042198b  d8a1a0000000           +fsub dword ptr [ecx + 0xa0]
    x86::Float fpu9 = cpu.fpu.sub(fpu8, x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(160) /* 0xa0 */)));
    // 00421991  8d91c0000000           -lea edx, [ecx + 0xc0]
    cpu.edx = x86::reg32(cpu.ecx + x86::reg32(192) /* 0xc0 */);
    // 00421997  d95d32                 +fstp dword ptr [ebp + 0x32]
    app->getMemory<float>(cpu.ebp + x86::reg32(50) /* 0x32 */) = float(fpu9);
    }
    // 0042199a  e851e80b00             -call 0x4e01f0
    cpu.esp -= 4;
    sub_4e01f0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042199f  8d452a                 -lea eax, [ebp + 0x2a]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(42) /* 0x2a */);
    // 004219a2  8d91cc000000           -lea edx, [ecx + 0xcc]
    cpu.edx = x86::reg32(cpu.ecx + x86::reg32(204) /* 0xcc */);
    // 004219a8  d95d42                 +fstp dword ptr [ebp + 0x42]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu10 = cpu.fpu.st(0);
    app->getMemory<float>(cpu.ebp + x86::reg32(66) /* 0x42 */) = float(fpu10);
    cpu.fpu.count -= 1;
    }
    // 004219ab  e840e80b00             -call 0x4e01f0
    cpu.esp -= 4;
    sub_4e01f0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004219b0  8d452a                 -lea eax, [ebp + 0x2a]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(42) /* 0x2a */);
    // 004219b3  8d91d8000000           -lea edx, [ecx + 0xd8]
    cpu.edx = x86::reg32(cpu.ecx + x86::reg32(216) /* 0xd8 */);
    // 004219b9  d95d46                 +fstp dword ptr [ebp + 0x46]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu11 = cpu.fpu.st(0);
    app->getMemory<float>(cpu.ebp + x86::reg32(70) /* 0x46 */) = float(fpu11);
    cpu.fpu.count -= 1;
    }
    // 004219bc  e82fe80b00             -call 0x4e01f0
    cpu.esp -= 4;
    sub_4e01f0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004219c1  d9ee                   +fldz 
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu12 = 0.0;
    // 004219c3  d9c9                   +fxch st(1)
    
    // 004219c5  d95d4a                 +fstp dword ptr [ebp + 0x4a]
    x86::Float fpu13 = cpu.fpu.st(0);
    app->getMemory<float>(cpu.ebp + x86::reg32(74) /* 0x4a */) = float(fpu13);
    // 004219c8  d98114010000           +fld dword ptr [ecx + 0x114]
    x86::Float fpu14 = x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(276) /* 0x114 */));
    // 004219ce  d98118010000           +fld dword ptr [ecx + 0x118]
    x86::Float fpu15 = x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(280) /* 0x118 */));
    // 004219d4  d9811c010000           +fld dword ptr [ecx + 0x11c]
    x86::Float fpu16 = x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(284) /* 0x11c */));
    // 004219da  d9ca                   +fxch st(2)
    
    // 004219dc  d905246e5300           +fld dword ptr [0x536e24]
    x86::Float fpu17 = x86::Float(app->getMemory<float>(x86::reg32(5467684) /* 0x536e24 */));
    // 004219e2  d9c9                   +fxch st(1)
    
    // 004219e4  d8c1                   +fadd st(1)
    x86::Float fpu18 = cpu.fpu.add(fpu14, x86::Float(fpu17));
    // 004219e6  d9ca                   +fxch st(2)
    
    // 004219e8  d8c1                   +fadd st(1)
    x86::Float fpu19 = cpu.fpu.add(fpu15, x86::Float(fpu17));
    // 004219ea  d9cb                   +fxch st(3)
    
    // 004219ec  dec1                   +faddp st(1)
    x86::Float fpu20 = cpu.fpu.add(fpu17, fpu16);
    // 004219ee  d9c9                   +fxch st(1)
    
    // 004219f0  d95d1e                 +fstp dword ptr [ebp + 0x1e]
    app->getMemory<float>(cpu.ebp + x86::reg32(30) /* 0x1e */) = float(fpu18);
    // 004219f3  d9c9                   +fxch st(1)
    
    // 004219f5  d95d22                 +fstp dword ptr [ebp + 0x22]
    app->getMemory<float>(cpu.ebp + x86::reg32(34) /* 0x22 */) = float(fpu19);
    // 004219f8  d95d26                 +fstp dword ptr [ebp + 0x26]
    app->getMemory<float>(cpu.ebp + x86::reg32(38) /* 0x26 */) = float(fpu20);
    // 004219fb  d85d42                 +fcomp dword ptr [ebp + 0x42]
    cpu.fpu.compare(fpu12, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(66) /* 0x42 */)));
    // 004219fe  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00421a00  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    cpu.fpu.count -= 1;
    }
    // 00421a01  760a                   -jbe 0x421a0d
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x00421a0d;
    }
    // 00421a03  d94542                 +fld dword ptr [ebp + 0x42]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu21 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(66) /* 0x42 */));
    // 00421a06  d9e0                   +fchs 
    x86::Float fpu22 = -fpu21;
    // 00421a08  d95d6e                 +fstp dword ptr [ebp + 0x6e]
    app->getMemory<float>(cpu.ebp + x86::reg32(110) /* 0x6e */) = float(fpu22);
    }
    // 00421a0b  eb06                   -jmp 0x421a13
    goto L_0x00421a13;
L_0x00421a0d:
    // 00421a0d  8b4542                 -mov eax, dword ptr [ebp + 0x42]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(66) /* 0x42 */);
    // 00421a10  89456e                 -mov dword ptr [ebp + 0x6e], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(110) /* 0x6e */) = cpu.eax;
L_0x00421a13:
    // 00421a13  8b456e                 -mov eax, dword ptr [ebp + 0x6e]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(110) /* 0x6e */);
    // 00421a16  d9ee                   +fldz 
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu23 = 0.0;
    // 00421a18  89454e                 -mov dword ptr [ebp + 0x4e], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(78) /* 0x4e */) = cpu.eax;
    // 00421a1b  d85d46                 +fcomp dword ptr [ebp + 0x46]
    cpu.fpu.compare(fpu23, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(70) /* 0x46 */)));
    // 00421a1e  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00421a20  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 00421a21  760a                   -jbe 0x421a2d
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x00421a2d;
    }
    // 00421a23  d94546                 +fld dword ptr [ebp + 0x46]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu24 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(70) /* 0x46 */));
    // 00421a26  d9e0                   +fchs 
    x86::Float fpu25 = -fpu24;
    // 00421a28  d95d72                 +fstp dword ptr [ebp + 0x72]
    app->getMemory<float>(cpu.ebp + x86::reg32(114) /* 0x72 */) = float(fpu25);
    }
    // 00421a2b  eb06                   -jmp 0x421a33
    goto L_0x00421a33;
L_0x00421a2d:
    // 00421a2d  8b4546                 -mov eax, dword ptr [ebp + 0x46]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(70) /* 0x46 */);
    // 00421a30  894572                 -mov dword ptr [ebp + 0x72], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(114) /* 0x72 */) = cpu.eax;
L_0x00421a33:
    // 00421a33  8b4572                 -mov eax, dword ptr [ebp + 0x72]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(114) /* 0x72 */);
    // 00421a36  d9ee                   +fldz 
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu26 = 0.0;
    // 00421a38  894552                 -mov dword ptr [ebp + 0x52], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(82) /* 0x52 */) = cpu.eax;
    // 00421a3b  d85d4a                 +fcomp dword ptr [ebp + 0x4a]
    cpu.fpu.compare(fpu26, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(74) /* 0x4a */)));
    // 00421a3e  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00421a40  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 00421a41  760a                   -jbe 0x421a4d
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x00421a4d;
    }
    // 00421a43  d9454a                 +fld dword ptr [ebp + 0x4a]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu27 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(74) /* 0x4a */));
    // 00421a46  d9e0                   +fchs 
    x86::Float fpu28 = -fpu27;
    // 00421a48  d95d7e                 +fstp dword ptr [ebp + 0x7e]
    app->getMemory<float>(cpu.ebp + x86::reg32(126) /* 0x7e */) = float(fpu28);
    }
    // 00421a4b  eb06                   -jmp 0x421a53
    goto L_0x00421a53;
L_0x00421a4d:
    // 00421a4d  8b454a                 -mov eax, dword ptr [ebp + 0x4a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(74) /* 0x4a */);
    // 00421a50  89457e                 -mov dword ptr [ebp + 0x7e], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */) = cpu.eax;
L_0x00421a53:
    // 00421a53  8b457e                 -mov eax, dword ptr [ebp + 0x7e]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */);
    // 00421a56  d9454e                 +fld dword ptr [ebp + 0x4e]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu29 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(78) /* 0x4e */));
    // 00421a59  894556                 -mov dword ptr [ebp + 0x56], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(86) /* 0x56 */) = cpu.eax;
    // 00421a5c  d85d1e                 +fcomp dword ptr [ebp + 0x1e]
    cpu.fpu.compare(fpu29, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(30) /* 0x1e */)));
    // 00421a5f  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00421a61  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 00421a62  0f8314010000           -jae 0x421b7c
    if (!cpu.flags.cf)
    {
        goto L_0x00421b7c;
    }
    // 00421a68  d94552                 +fld dword ptr [ebp + 0x52]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu30 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(82) /* 0x52 */));
    // 00421a6b  d85d22                 +fcomp dword ptr [ebp + 0x22]
    cpu.fpu.compare(fpu30, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(34) /* 0x22 */)));
    // 00421a6e  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00421a70  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 00421a71  0f8305010000           -jae 0x421b7c
    if (!cpu.flags.cf)
    {
        goto L_0x00421b7c;
    }
    // 00421a77  d9457e                 +fld dword ptr [ebp + 0x7e]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu31 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(126) /* 0x7e */));
    // 00421a7a  d85d26                 +fcomp dword ptr [ebp + 0x26]
    cpu.fpu.compare(fpu31, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(38) /* 0x26 */)));
    // 00421a7d  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00421a7f  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 00421a80  0f83f6000000           -jae 0x421b7c
    if (!cpu.flags.cf)
    {
        goto L_0x00421b7c;
    }
    // 00421a86  d9ee                   +fldz 
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu32 = 0.0;
    // 00421a88  d85d46                 +fcomp dword ptr [ebp + 0x46]
    cpu.fpu.compare(fpu32, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(70) /* 0x46 */)));
    // 00421a8b  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00421a8d  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 00421a8e  730f                   -jae 0x421a9f
    if (!cpu.flags.cf)
    {
        goto L_0x00421a9f;
    }
    // 00421a90  31ff                   +xor edi, edi
    cpu.clear_co();
    cpu.set_szp((cpu.edi ^= x86::reg32(x86::sreg32(cpu.edi))));
    // 00421a92  b80000f03f             -mov eax, 0x3ff00000
    cpu.eax = 1072693248 /*0x3ff00000*/;
    // 00421a97  897d62                 -mov dword ptr [ebp + 0x62], edi
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(98) /* 0x62 */) = cpu.edi;
    // 00421a9a  894566                 -mov dword ptr [ebp + 0x66], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(102) /* 0x66 */) = cpu.eax;
    // 00421a9d  eb0d                   -jmp 0x421aac
    goto L_0x00421aac;
L_0x00421a9f:
    // 00421a9f  31d2                   +xor edx, edx
    cpu.clear_co();
    cpu.set_szp((cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx))));
    // 00421aa1  bf0000f0bf             -mov edi, 0xbff00000
    cpu.edi = 3220176896 /*0xbff00000*/;
    // 00421aa6  895562                 -mov dword ptr [ebp + 0x62], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(98) /* 0x62 */) = cpu.edx;
    // 00421aa9  897d66                 -mov dword ptr [ebp + 0x66], edi
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(102) /* 0x66 */) = cpu.edi;
L_0x00421aac:
    // 00421aac  d9454a                 +fld dword ptr [ebp + 0x4a]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu33 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(74) /* 0x4a */));
    // 00421aaf  d8c8                   +fmul st(0)
    x86::Float fpu34 = cpu.fpu.mul(fpu33, x86::Float(fpu33));
    // 00421ab1  d94526                 +fld dword ptr [ebp + 0x26]
    x86::Float fpu35 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(38) /* 0x26 */));
    // 00421ab4  d8c8                   +fmul st(0)
    x86::Float fpu36 = cpu.fpu.mul(fpu35, x86::Float(fpu35));
    // 00421ab6  def9                   +fdivp st(1)
    x86::Float fpu37 = cpu.fpu.div(fpu34, fpu36);
    // 00421ab8  d94542                 +fld dword ptr [ebp + 0x42]
    x86::Float fpu38 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(66) /* 0x42 */));
    // 00421abb  d8c8                   +fmul st(0)
    x86::Float fpu39 = cpu.fpu.mul(fpu38, x86::Float(fpu38));
    // 00421abd  d9451e                 +fld dword ptr [ebp + 0x1e]
    x86::Float fpu40 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(30) /* 0x1e */));
    // 00421ac0  d8c8                   +fmul st(0)
    x86::Float fpu41 = cpu.fpu.mul(fpu40, x86::Float(fpu40));
    // 00421ac2  def9                   +fdivp st(1)
    x86::Float fpu42 = cpu.fpu.div(fpu39, fpu41);
    // 00421ac4  dd4562                 +fld qword ptr [ebp + 0x62]
    x86::Float fpu43 = x86::Float(app->getMemory<double>(cpu.ebp + x86::reg32(98) /* 0x62 */));
    // 00421ac7  d9c9                   +fxch st(1)
    
    // 00421ac9  dec2                   +faddp st(2)
    x86::Float fpu44 = cpu.fpu.add(fpu37, fpu42);
    // 00421acb  d9ee                   +fldz 
    x86::Float fpu45 = 0.0;
    // 00421acd  d9e8                   +fld1 
    x86::Float fpu46 = 1.0;
    // 00421acf  dee3                   +fsubrp st(3)
    x86::Float fpu47 = cpu.fpu.sub(fpu46, x86::Float(fpu44));
    // 00421ad1  d9c9                   +fxch st(1)
    
    // 00421ad3  d95d6a                 +fstp dword ptr [ebp + 0x6a]
    app->getMemory<float>(cpu.ebp + x86::reg32(106) /* 0x6a */) = float(fpu43);
    // 00421ad6  d9c9                   +fxch st(1)
    
    // 00421ad8  d95d76                 +fstp dword ptr [ebp + 0x76]
    app->getMemory<float>(cpu.ebp + x86::reg32(118) /* 0x76 */) = float(fpu47);
    // 00421adb  d85d76                 +fcomp dword ptr [ebp + 0x76]
    cpu.fpu.compare(fpu45, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(118) /* 0x76 */)));
    // 00421ade  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00421ae0  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 00421ae1  0f8795000000           -ja 0x421b7c
    if (!cpu.flags.cf && !cpu.flags.zf)
    {
        goto L_0x00421b7c;
    }
    // 00421ae7  d94522                 -fld dword ptr [ebp + 0x22]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu48 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(34) /* 0x22 */));
    // 00421aea  dcc8                   -fmul st(0), st(0)
    x86::Float fpu49 = cpu.fpu.mul(fpu48, fpu48);
    // 00421aec  d84d76                 -fmul dword ptr [ebp + 0x76]
    x86::Float fpu50 = cpu.fpu.mul(fpu49, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(118) /* 0x76 */)));
    // 00421aef  83ec04                 +sub esp, 4
    {
        x86::reg32& tmp1 = cpu.esp;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(4 /*0x4*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 00421af2  d91c24                 +fstp dword ptr [esp]
    app->getMemory<float>(cpu.esp) = float(fpu50);
    }
    // 00421af5  e8268e0c00             -call 0x4ea920
    cpu.esp -= 4;
    sub_4ea920(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00421afa  d94552                 +fld dword ptr [ebp + 0x52]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu51 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(82) /* 0x52 */));
    // 00421afd  d9c9                   +fxch st(1)
    
    // 00421aff  d95d7a                 +fstp dword ptr [ebp + 0x7a]
    x86::Float fpu52 = cpu.fpu.st(0);
    app->getMemory<float>(cpu.ebp + x86::reg32(122) /* 0x7a */) = float(fpu52);
    // 00421b02  d85d7a                 +fcomp dword ptr [ebp + 0x7a]
    cpu.fpu.compare(fpu51, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(122) /* 0x7a */)));
    // 00421b05  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00421b07  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    cpu.fpu.count -= 1;
    }
    // 00421b08  7372                   -jae 0x421b7c
    if (!cpu.flags.cf)
    {
        goto L_0x00421b7c;
    }
    // 00421b0a  d9457a                 +fld dword ptr [ebp + 0x7a]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu53 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(122) /* 0x7a */));
    // 00421b0d  8b4542                 -mov eax, dword ptr [ebp + 0x42]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(66) /* 0x42 */);
    // 00421b10  d84d6a                 +fmul dword ptr [ebp + 0x6a]
    x86::Float fpu54 = cpu.fpu.mul(fpu53, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(106) /* 0x6a */)));
    // 00421b13  894536                 -mov dword ptr [ebp + 0x36], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(54) /* 0x36 */) = cpu.eax;
    // 00421b16  8b454a                 -mov eax, dword ptr [ebp + 0x4a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(74) /* 0x4a */);
    // 00421b19  8d55fa                 -lea edx, [ebp - 6]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-6) /* -0x6 */);
    // 00421b1c  89453e                 -mov dword ptr [ebp + 0x3e], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(62) /* 0x3e */) = cpu.eax;
    // 00421b1f  8d81c0000000           -lea eax, [ecx + 0xc0]
    cpu.eax = x86::reg32(cpu.ecx + x86::reg32(192) /* 0xc0 */);
    // 00421b25  d95d3a                 +fstp dword ptr [ebp + 0x3a]
    app->getMemory<float>(cpu.ebp + x86::reg32(58) /* 0x3a */) = float(fpu54);
    }
    // 00421b28  e8e3e50b00             -call 0x4e0110
    cpu.esp -= 4;
    sub_4e0110(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00421b2d  8d55fa                 -lea edx, [ebp - 6]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-6) /* -0x6 */);
    // 00421b30  8d4536                 -lea eax, [ebp + 0x36]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(54) /* 0x36 */);
    // 00421b33  e8b8e60b00             -call 0x4e01f0
    cpu.esp -= 4;
    sub_4e01f0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00421b38  8d5506                 -lea edx, [ebp + 6]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(6) /* 0x6 */);
    // 00421b3b  8d4536                 -lea eax, [ebp + 0x36]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(54) /* 0x36 */);
    // 00421b3e  d95d42                 +fstp dword ptr [ebp + 0x42]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu55 = cpu.fpu.st(0);
    app->getMemory<float>(cpu.ebp + x86::reg32(66) /* 0x42 */) = float(fpu55);
    cpu.fpu.count -= 1;
    }
    // 00421b41  e8aae60b00             -call 0x4e01f0
    cpu.esp -= 4;
    sub_4e01f0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00421b46  8d5512                 -lea edx, [ebp + 0x12]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(18) /* 0x12 */);
    // 00421b49  8d4536                 -lea eax, [ebp + 0x36]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(54) /* 0x36 */);
    // 00421b4c  d95d46                 +fstp dword ptr [ebp + 0x46]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu56 = cpu.fpu.st(0);
    app->getMemory<float>(cpu.ebp + x86::reg32(70) /* 0x46 */) = float(fpu56);
    cpu.fpu.count -= 1;
    }
    // 00421b4f  e89ce60b00             -call 0x4e01f0
    cpu.esp -= 4;
    sub_4e01f0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00421b54  d98198000000           +fld dword ptr [ecx + 0x98]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu57 = x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(152) /* 0x98 */));
    // 00421b5a  d84542                 +fadd dword ptr [ebp + 0x42]
    x86::Float fpu58 = cpu.fpu.add(fpu57, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(66) /* 0x42 */)));
    // 00421b5d  d91b                   +fstp dword ptr [ebx]
    app->getMemory<float>(cpu.ebx) = float(fpu58);
    // 00421b5f  d9819c000000           +fld dword ptr [ecx + 0x9c]
    x86::Float fpu59 = x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(156) /* 0x9c */));
    // 00421b65  d84546                 +fadd dword ptr [ebp + 0x46]
    x86::Float fpu60 = cpu.fpu.add(fpu59, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(70) /* 0x46 */)));
    // 00421b68  d9c9                   +fxch st(1)
    
    // 00421b6a  d95d4a                 +fstp dword ptr [ebp + 0x4a]
    x86::Float fpu61 = cpu.fpu.st(0);
    app->getMemory<float>(cpu.ebp + x86::reg32(74) /* 0x4a */) = float(fpu61);
    // 00421b6d  d95b04                 +fstp dword ptr [ebx + 4]
    app->getMemory<float>(cpu.ebx + x86::reg32(4) /* 0x4 */) = float(fpu60);
    // 00421b70  d981a0000000           +fld dword ptr [ecx + 0xa0]
    x86::Float fpu62 = x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(160) /* 0xa0 */));
    // 00421b76  d8454a                 +fadd dword ptr [ebp + 0x4a]
    x86::Float fpu63 = cpu.fpu.add(fpu62, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(74) /* 0x4a */)));
    // 00421b79  d95b08                 +fstp dword ptr [ebx + 8]
    app->getMemory<float>(cpu.ebx + x86::reg32(8) /* 0x8 */) = float(fpu63);
    cpu.fpu.count -= 1;
    }
L_0x00421b7c:
    // 00421b7c  46                     +inc esi
    {
        x86::reg32& tmp = cpu.esi;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 00421b7d  e996fdffff             -jmp 0x421918
    goto L_0x00421918;
L_0x00421b82:
    // 00421b82  8da582000000           -lea esp, [ebp + 0x82]
    cpu.esp = x86::reg32(cpu.ebp + x86::reg32(130) /* 0x82 */);
    // 00421b88  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00421b89  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00421b8a  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00421b8b  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00421b8c  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00421b8d  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00421b8e  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x90 */
void Application::sub_421b90(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00421b90  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00421b91  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00421b92  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00421b93  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00421b94  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00421b95  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00421b97  83ec60                 -sub esp, 0x60
    (cpu.esp) -= x86::reg32(x86::sreg32(96 /*0x60*/));
    // 00421b9a  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00421b9c  89d3                   -mov ebx, edx
    cpu.ebx = cpu.edx;
    // 00421b9e  83c074                 -add eax, 0x74
    (cpu.eax) += x86::reg32(x86::sreg32(116 /*0x74*/));
    // 00421ba1  ba01000000             -mov edx, 1
    cpu.edx = 1 /*0x1*/;
    // 00421ba6  8b7010                 -mov esi, dword ptr [eax + 0x10]
    cpu.esi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(16) /* 0x10 */);
    // 00421ba9  e832ecffff             -call 0x4207e0
    cpu.esp -= 4;
    nfs3hp::trackdata::positionSurface(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00421bae  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00421baf  8b7b08                 -mov edi, dword ptr [ebx + 8]
    cpu.edi = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(8) /* 0x8 */);
    // 00421bb2  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00421bb3  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 00421bb5  8b4304                 -mov eax, dword ptr [ebx + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(4) /* 0x4 */);
    // 00421bb8  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00421bb9  8b3b                   -mov edi, dword ptr [ebx]
    cpu.edi = app->getMemory<x86::reg32>(cpu.ebx);
    // 00421bbb  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00421bbc  83e23f                 -and edx, 0x3f
    cpu.edx &= x86::reg32(x86::sreg32(63 /*0x3f*/));
    // 00421bbf  e82cf0ffff             -call 0x420bf0
    cpu.esp -= 4;
    nfs3hp::trackdata::inTunnel(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00421bc4  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00421bc6  7416                   -je 0x421bde
    if (cpu.flags.zf)
    {
        goto L_0x00421bde;
    }
    // 00421bc8  8b3d542e5500           -mov edi, dword ptr [0x552e54]
    cpu.edi = app->getMemory<x86::reg32>(x86::reg32(5582420) /* 0x552e54 */);
    // 00421bce  8d04b500000000         -lea eax, [esi*4]
    cpu.eax = x86::reg32(cpu.esi * 4);
    // 00421bd5  01f8                   +add eax, edi
    {
        x86::reg32& tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.edi));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 00421bd7  8b00                   -mov eax, dword ptr [eax]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax);
    // 00421bd9  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 00421bdc  eb07                   -jmp 0x421be5
    goto L_0x00421be5;
L_0x00421bde:
    // 00421bde  c745fc0000c841         -mov dword ptr [ebp - 4], 0x41c80000
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = 1103626240 /*0x41c80000*/;
L_0x00421be5:
    // 00421be5  83b98800000000         +cmp dword ptr [ecx + 0x88], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(136) /* 0x88 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00421bec  0f8484000000           -je 0x421c76
    if (cpu.flags.zf)
    {
        goto L_0x00421c76;
    }
    // 00421bf2  83b98c00000000         +cmp dword ptr [ecx + 0x8c], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(140) /* 0x8c */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00421bf9  0f8477000000           -je 0x421c76
    if (cpu.flags.zf)
    {
        goto L_0x00421c76;
    }
    // 00421bff  83b9e000000000         +cmp dword ptr [ecx + 0xe0], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(224) /* 0xe0 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00421c06  0f856a000000           -jne 0x421c76
    if (!cpu.flags.zf)
    {
        goto L_0x00421c76;
    }
    // 00421c0c  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 00421c0e  7466                   -je 0x421c76
    if (cpu.flags.zf)
    {
        goto L_0x00421c76;
    }
    // 00421c10  83fa0e                 +cmp edx, 0xe
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(14 /*0xe*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00421c13  7461                   -je 0x421c76
    if (cpu.flags.zf)
    {
        goto L_0x00421c76;
    }
    // 00421c15  8d7da0                 -lea edi, [ebp - 0x60]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(-96) /* -0x60 */);
    // 00421c18  8bb1c8000000           -mov esi, dword ptr [ecx + 0xc8]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(200) /* 0xc8 */);
    // 00421c1e  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00421c1f  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00421c20  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00421c21  8d7dac                 -lea edi, [ebp - 0x54]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(-84) /* -0x54 */);
    // 00421c24  8bb1cc000000           -mov esi, dword ptr [ecx + 0xcc]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(204) /* 0xcc */);
    // 00421c2a  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00421c2b  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00421c2c  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00421c2d  8d7db8                 -lea edi, [ebp - 0x48]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(-72) /* -0x48 */);
    // 00421c30  8bb1d0000000           -mov esi, dword ptr [ecx + 0xd0]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(208) /* 0xd0 */);
    // 00421c36  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00421c37  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00421c38  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00421c39  8d7dc4                 -lea edi, [ebp - 0x3c]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(-60) /* -0x3c */);
    // 00421c3c  8bb1d4000000           -mov esi, dword ptr [ecx + 0xd4]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(212) /* 0xd4 */);
    // 00421c42  8d55d0                 -lea edx, [ebp - 0x30]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-48) /* -0x30 */);
    // 00421c45  8d45a0                 -lea eax, [ebp - 0x60]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-96) /* -0x60 */);
    // 00421c48  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00421c49  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00421c4a  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00421c4b  e8004e0700             -call 0x496a50
    cpu.esp -= 4;
    sub_496a50(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00421c50  8b4308                 -mov eax, dword ptr [ebx + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(8) /* 0x8 */);
    // 00421c53  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00421c54  8b5304                 -mov edx, dword ptr [ebx + 4]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(4) /* 0x4 */);
    // 00421c57  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00421c58  8b33                   -mov esi, dword ptr [ebx]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ebx);
    // 00421c5a  8b81c8000000           -mov eax, dword ptr [ecx + 0xc8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(200) /* 0xc8 */);
    // 00421c60  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00421c61  8b7808                 -mov edi, dword ptr [eax + 8]
    cpu.edi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 00421c64  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00421c65  8b5004                 -mov edx, dword ptr [eax + 4]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 00421c68  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00421c69  8b08                   -mov ecx, dword ptr [eax]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax);
    // 00421c6b  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00421c6c  8d45d0                 -lea eax, [ebp - 0x30]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-48) /* -0x30 */);
    // 00421c6f  e82c4c0700             -call 0x4968a0
    cpu.esp -= 4;
    sub_4968a0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00421c74  eb19                   -jmp 0x421c8f
    goto L_0x00421c8f;
L_0x00421c76:
    // 00421c76  8d04f500000000         -lea eax, [esi*8]
    cpu.eax = x86::reg32(cpu.esi * 8);
    // 00421c7d  8b1548d95d00           -mov edx, dword ptr [0x5dd948]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(6150472) /* 0x5dd948 */);
    // 00421c83  01f0                   +add eax, esi
    {
        x86::reg32& tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.esi));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 00421c85  db448204               +fild dword ptr [edx + eax*4 + 4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.edx + x86::reg32(4) /* 0x4 */ + cpu.eax * 4)));
    // 00421c89  dc0d346e5300           +fmul qword ptr [0x536e34]
    x86::Float fpu2 = cpu.fpu.mul(fpu1, x86::Float(app->getMemory<double>(x86::reg32(5467700) /* 0x536e34 */)));
    cpu.fpu.count += 1;
    cpu.fpu.st(0) = fpu2;
    }
L_0x00421c8f:
    // 00421c8f  d845fc                 +fadd dword ptr [ebp - 4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu3 = cpu.fpu.st(0);
    x86::Float fpu4 = cpu.fpu.add(fpu3, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 00421c92  dc052c6e5300           +fadd qword ptr [0x536e2c]
    x86::Float fpu5 = cpu.fpu.add(fpu4, x86::Float(app->getMemory<double>(x86::reg32(5467692) /* 0x536e2c */)));
    // 00421c98  d95df8                 +fstp dword ptr [ebp - 8]
    app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = float(fpu5);
    // 00421c9b  d94304                 +fld dword ptr [ebx + 4]
    x86::Float fpu6 = x86::Float(app->getMemory<float>(cpu.ebx + x86::reg32(4) /* 0x4 */));
    // 00421c9e  d85df8                 +fcomp dword ptr [ebp - 8]
    cpu.fpu.compare(fpu6, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    // 00421ca1  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00421ca3  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    cpu.fpu.count -= 1;
    }
    // 00421ca4  7305                   -jae 0x421cab
    if (!cpu.flags.cf)
    {
        goto L_0x00421cab;
    }
    // 00421ca6  8b4304                 -mov eax, dword ptr [ebx + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(4) /* 0x4 */);
    // 00421ca9  eb03                   -jmp 0x421cae
    goto L_0x00421cae;
L_0x00421cab:
    // 00421cab  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
L_0x00421cae:
    // 00421cae  8945f4                 -mov dword ptr [ebp - 0xc], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.eax;
    // 00421cb1  8b45f4                 -mov eax, dword ptr [ebp - 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 00421cb4  894304                 -mov dword ptr [ebx + 4], eax
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(4) /* 0x4 */) = cpu.eax;
    // 00421cb7  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00421cb9  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00421cba  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00421cbb  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00421cbc  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00421cbd  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00421cbe  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x90 */
void Application::sub_421cc0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00421cc0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00421cc1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00421cc2  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00421cc3  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00421cc4  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00421cc5  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00421cc7  81ecbc000000           -sub esp, 0xbc
    (cpu.esp) -= x86::reg32(x86::sreg32(188 /*0xbc*/));
    // 00421ccd  83ed7e                 -sub ebp, 0x7e
    (cpu.ebp) -= x86::reg32(x86::sreg32(126 /*0x7e*/));
    // 00421cd0  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 00421cd2  895576                 -mov dword ptr [ebp + 0x76], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(118) /* 0x76 */) = cpu.edx;
    // 00421cd5  8d7d5e                 -lea edi, [ebp + 0x5e]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(94) /* 0x5e */);
    // 00421cd8  8db596000000           -lea esi, [ebp + 0x96]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(150) /* 0x96 */);
    // 00421cde  ba01000000             -mov edx, 1
    cpu.edx = 1 /*0x1*/;
    // 00421ce3  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00421ce4  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00421ce5  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00421ce6  83c074                 -add eax, 0x74
    (cpu.eax) += x86::reg32(x86::sreg32(116 /*0x74*/));
    // 00421ce9  8d7d46                 -lea edi, [ebp + 0x46]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(70) /* 0x46 */);
    // 00421cec  8b7576                 -mov esi, dword ptr [ebp + 0x76]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(118) /* 0x76 */);
    // 00421cef  e8eceaffff             -call 0x4207e0
    cpu.esp -= 4;
    nfs3hp::trackdata::positionSurface(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00421cf4  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00421cf5  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00421cf6  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00421cf7  8d7d6a                 -lea edi, [ebp + 0x6a]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(106) /* 0x6a */);
    // 00421cfa  8d7546                 -lea esi, [ebp + 0x46]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(70) /* 0x46 */);
    // 00421cfd  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00421cfe  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00421cff  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00421d00  b91e000000             -mov ecx, 0x1e
    cpu.ecx = 30 /*0x1e*/;
    // 00421d05  8d7dc2                 -lea edi, [ebp - 0x3e]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(-62) /* -0x3e */);
    // 00421d08  8d7374                 -lea esi, [ebx + 0x74]
    cpu.esi = x86::reg32(cpu.ebx + x86::reg32(116) /* 0x74 */);
    // 00421d0b  f3a5                   -rep movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00421d0d  83e03f                 -and eax, 0x3f
    cpu.eax &= x86::reg32(x86::sreg32(63 /*0x3f*/));
    // 00421d10  8b93e0000000           -mov edx, dword ptr [ebx + 0xe0]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(224) /* 0xe0 */);
    // 00421d16  89457a                 -mov dword ptr [ebp + 0x7a], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(122) /* 0x7a */) = cpu.eax;
    // 00421d19  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 00421d1b  7436                   -je 0x421d53
    if (cpu.flags.zf)
    {
        goto L_0x00421d53;
    }
    // 00421d1d  8b4304                 -mov eax, dword ptr [ebx + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(4) /* 0x4 */);
    // 00421d20  8b482c                 -mov ecx, dword ptr [eax + 0x2c]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(44) /* 0x2c */);
    // 00421d23  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    // 00421d25  744e                   -je 0x421d75
    if (cpu.flags.zf)
    {
        goto L_0x00421d75;
    }
    // 00421d27  83fa01                 +cmp edx, 1
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
    // 00421d2a  750b                   -jne 0x421d37
    if (!cpu.flags.zf)
    {
        goto L_0x00421d37;
    }
    // 00421d2c  6683790400             +cmp word ptr [ecx + 4], 0
    {
        x86::reg16 tmp1 = app->getMemory<x86::reg16>(cpu.ecx + x86::reg32(4) /* 0x4 */);
        x86::reg16 tmp2 = x86::reg16(x86::sreg16(0 /*0x0*/));
        x86::reg16 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 15);
        cpu.flags.of ^= 1 & (result >> 15);
        cpu.flags.of &= (1 & (tmp1 >> 15)) != (1 & (tmp2 >> 15));
        cpu.set_szp(result);
    }
    // 00421d31  0f8d32010000           -jge 0x421e69
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00421e69;
    }
L_0x00421d37:
    // 00421d37  83bbe000000002         +cmp dword ptr [ebx + 0xe0], 2
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(224) /* 0xe0 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(2 /*0x2*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00421d3e  7535                   -jne 0x421d75
    if (!cpu.flags.zf)
    {
        goto L_0x00421d75;
    }
    // 00421d40  8b4304                 -mov eax, dword ptr [ebx + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(4) /* 0x4 */);
    // 00421d43  8b402c                 -mov eax, dword ptr [eax + 0x2c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(44) /* 0x2c */);
    // 00421d46  6683780600             +cmp word ptr [eax + 6], 0
    {
        x86::reg16 tmp1 = app->getMemory<x86::reg16>(cpu.eax + x86::reg32(6) /* 0x6 */);
        x86::reg16 tmp2 = x86::reg16(x86::sreg16(0 /*0x0*/));
        x86::reg16 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 15);
        cpu.flags.of ^= 1 & (result >> 15);
        cpu.flags.of &= (1 & (tmp1 >> 15)) != (1 & (tmp2 >> 15));
        cpu.set_szp(result);
    }
    // 00421d4b  0f8d18010000           -jge 0x421e69
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00421e69;
    }
    // 00421d51  eb22                   -jmp 0x421d75
    goto L_0x00421d75;
L_0x00421d53:
    // 00421d53  83bb8800000000         +cmp dword ptr [ebx + 0x88], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(136) /* 0x88 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00421d5a  7419                   -je 0x421d75
    if (cpu.flags.zf)
    {
        goto L_0x00421d75;
    }
    // 00421d5c  83bb8c00000000         +cmp dword ptr [ebx + 0x8c], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(140) /* 0x8c */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00421d63  7410                   -je 0x421d75
    if (cpu.flags.zf)
    {
        goto L_0x00421d75;
    }
    // 00421d65  8b4d7a                 -mov ecx, dword ptr [ebp + 0x7a]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(122) /* 0x7a */);
    // 00421d68  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    // 00421d6a  7409                   -je 0x421d75
    if (cpu.flags.zf)
    {
        goto L_0x00421d75;
    }
    // 00421d6c  83f90e                 +cmp ecx, 0xe
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(14 /*0xe*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00421d6f  0f85f4000000           -jne 0x421e69
    if (!cpu.flags.zf)
    {
        goto L_0x00421e69;
    }
L_0x00421d75:
    // 00421d75  b90a000000             -mov ecx, 0xa
    cpu.ecx = 10 /*0xa*/;
L_0x00421d7a:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00421d7a  d9454a                 -fld dword ptr [ebp + 0x4a]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(74) /* 0x4a */));
    // 00421d7d  d94546                 -fld dword ptr [ebp + 0x46]
    x86::Float fpu2 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(70) /* 0x46 */));
    // 00421d80  d8455e                 -fadd dword ptr [ebp + 0x5e]
    x86::Float fpu3 = cpu.fpu.add(fpu2, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(94) /* 0x5e */)));
    // 00421d83  d9c9                   -fxch st(1)
    
    // 00421d85  d84562                 -fadd dword ptr [ebp + 0x62]
    x86::Float fpu4 = cpu.fpu.add(fpu1, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(98) /* 0x62 */)));
    // 00421d88  d9c9                   -fxch st(1)
    
    // 00421d8a  dd053c6e5300           -fld qword ptr [0x536e3c]
    x86::Float fpu5 = x86::Float(app->getMemory<double>(x86::reg32(5467708) /* 0x536e3c */));
    // 00421d90  d9c9                   -fxch st(1)
    
    // 00421d92  d8c9                   -fmul st(1)
    x86::Float fpu6 = cpu.fpu.mul(fpu3, x86::Float(fpu5));
    // 00421d94  d9ca                   -fxch st(2)
    
    // 00421d96  d8c9                   -fmul st(1)
    x86::Float fpu7 = cpu.fpu.mul(fpu4, x86::Float(fpu5));
    // 00421d98  d9454e                 -fld dword ptr [ebp + 0x4e]
    x86::Float fpu8 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(78) /* 0x4e */));
    // 00421d9b  8d7d3a                 -lea edi, [ebp + 0x3a]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(58) /* 0x3a */);
    // 00421d9e  d84566                 -fadd dword ptr [ebp + 0x66]
    x86::Float fpu9 = cpu.fpu.add(fpu8, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(102) /* 0x66 */)));
    // 00421da1  8d756a                 -lea esi, [ebp + 0x6a]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(106) /* 0x6a */);
    // 00421da4  deca                   -fmulp st(2)
    x86::Float fpu10 = cpu.fpu.mul(fpu5, fpu9);
    // 00421da6  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00421da7  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00421da8  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00421da9  d9ca                   -fxch st(2)
    
    // 00421dab  d9556a                 -fst dword ptr [ebp + 0x6a]
    app->getMemory<float>(cpu.ebp + x86::reg32(106) /* 0x6a */) = float(fpu6);
    // 00421dae  dc0d446e5300           -fmul qword ptr [0x536e44]
    x86::Float fpu11 = cpu.fpu.mul(fpu6, x86::Float(app->getMemory<double>(x86::reg32(5467716) /* 0x536e44 */)));
    // 00421db4  d9ca                   -fxch st(2)
    
    // 00421db6  d95d6e                 -fstp dword ptr [ebp + 0x6e]
    app->getMemory<float>(cpu.ebp + x86::reg32(110) /* 0x6e */) = float(fpu7);
    // 00421db9  d95d72                 -fstp dword ptr [ebp + 0x72]
    app->getMemory<float>(cpu.ebp + x86::reg32(114) /* 0x72 */) = float(fpu10);
    // 00421dbc  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 00421dbf  db1c24                 -fistp dword ptr [esp]
    app->getMemory<x86::reg32>(cpu.esp) = x86::reg32(cpu.fpu.toInteger<x86::sreg32>(fpu11));
    // 00421dc2  58                     -pop eax
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00421dc3  d9456e                 -fld dword ptr [ebp + 0x6e]
    x86::Float fpu12 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(110) /* 0x6e */));
    // 00421dc6  dc0d446e5300           -fmul qword ptr [0x536e44]
    x86::Float fpu13 = cpu.fpu.mul(fpu12, x86::Float(app->getMemory<double>(x86::reg32(5467716) /* 0x536e44 */)));
    // 00421dcc  894552                 -mov dword ptr [ebp + 0x52], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(82) /* 0x52 */) = cpu.eax;
    // 00421dcf  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 00421dd2  db1c24                 -fistp dword ptr [esp]
    app->getMemory<x86::reg32>(cpu.esp) = x86::reg32(cpu.fpu.toInteger<x86::sreg32>(fpu13));
    // 00421dd5  58                     -pop eax
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00421dd6  d94572                 -fld dword ptr [ebp + 0x72]
    x86::Float fpu14 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(114) /* 0x72 */));
    // 00421dd9  dc0d446e5300           -fmul qword ptr [0x536e44]
    x86::Float fpu15 = cpu.fpu.mul(fpu14, x86::Float(app->getMemory<double>(x86::reg32(5467716) /* 0x536e44 */)));
    // 00421ddf  8d55c2                 -lea edx, [ebp - 0x3e]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-62) /* -0x3e */);
    // 00421de2  894556                 -mov dword ptr [ebp + 0x56], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(86) /* 0x56 */) = cpu.eax;
    // 00421de5  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 00421de8  db1c24                 -fistp dword ptr [esp]
    app->getMemory<x86::reg32>(cpu.esp) = x86::reg32(cpu.fpu.toInteger<x86::sreg32>(fpu15));
    // 00421deb  58                     -pop eax
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00421dec  89455a                 -mov dword ptr [ebp + 0x5a], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(90) /* 0x5a */) = cpu.eax;
    // 00421def  8d4552                 -lea eax, [ebp + 0x52]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(82) /* 0x52 */);
    }
    // 00421df2  e899cbffff             -call 0x41e990
    cpu.esp -= 4;
    nfs3hp::trackdata::findQuad(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00421df7  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 00421df9  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00421dfb  7413                   -je 0x421e10
    if (cpu.flags.zf)
    {
        goto L_0x00421e10;
    }
    // 00421dfd  ba01000000             -mov edx, 1
    cpu.edx = 1 /*0x1*/;
    // 00421e02  8d45c2                 -lea eax, [ebp - 0x3e]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-62) /* -0x3e */);
    // 00421e05  e8d6e9ffff             -call 0x4207e0
    cpu.esp -= 4;
    nfs3hp::trackdata::positionSurface(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00421e0a  83e03f                 -and eax, 0x3f
    cpu.eax &= x86::reg32(x86::sreg32(63 /*0x3f*/));
    // 00421e0d  89457a                 -mov dword ptr [ebp + 0x7a], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(122) /* 0x7a */) = cpu.eax;
L_0x00421e10:
    // 00421e10  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 00421e12  7418                   -je 0x421e2c
    if (cpu.flags.zf)
    {
        goto L_0x00421e2c;
    }
    // 00421e14  8b7d7a                 -mov edi, dword ptr [ebp + 0x7a]
    cpu.edi = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(122) /* 0x7a */);
    // 00421e17  85ff                   +test edi, edi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edi & cpu.edi));
    // 00421e19  7411                   -je 0x421e2c
    if (cpu.flags.zf)
    {
        goto L_0x00421e2c;
    }
    // 00421e1b  83ff0e                 +cmp edi, 0xe
    {
        x86::reg32 tmp1 = cpu.edi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(14 /*0xe*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00421e1e  740c                   -je 0x421e2c
    if (cpu.flags.zf)
    {
        goto L_0x00421e2c;
    }
    // 00421e20  837dd600               +cmp dword ptr [ebp - 0x2a], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-42) /* -0x2a */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00421e24  7406                   -je 0x421e2c
    if (cpu.flags.zf)
    {
        goto L_0x00421e2c;
    }
    // 00421e26  837dda00               +cmp dword ptr [ebp - 0x26], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-38) /* -0x26 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00421e2a  7508                   -jne 0x421e34
    if (!cpu.flags.zf)
    {
        goto L_0x00421e34;
    }
L_0x00421e2c:
    // 00421e2c  8d7d46                 -lea edi, [ebp + 0x46]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(70) /* 0x46 */);
    // 00421e2f  8d756a                 -lea esi, [ebp + 0x6a]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(106) /* 0x6a */);
    // 00421e32  eb18                   -jmp 0x421e4c
    goto L_0x00421e4c;
L_0x00421e34:
    // 00421e34  8d7d5e                 -lea edi, [ebp + 0x5e]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(94) /* 0x5e */);
    // 00421e37  8d756a                 -lea esi, [ebp + 0x6a]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(106) /* 0x6a */);
    // 00421e3a  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00421e3b  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00421e3c  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00421e3d  8d7d46                 -lea edi, [ebp + 0x46]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(70) /* 0x46 */);
    // 00421e40  8d753a                 -lea esi, [ebp + 0x3a]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(58) /* 0x3a */);
    // 00421e43  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00421e44  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00421e45  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00421e46  8d7d6a                 -lea edi, [ebp + 0x6a]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(106) /* 0x6a */);
    // 00421e49  8d753a                 -lea esi, [ebp + 0x3a]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(58) /* 0x3a */);
L_0x00421e4c:
    // 00421e4c  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00421e4d  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00421e4e  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00421e4f  49                     +dec ecx
    {
        x86::reg32& tmp = cpu.ecx;
        cpu.flags.of = 1 & (tmp >> 31);
        tmp--;
        cpu.flags.of &= ~(1 & (tmp >> 31));
        cpu.set_szp(tmp);
    }
    // 00421e50  0f8524ffffff           -jne 0x421d7a
    if (!cpu.flags.zf)
    {
        goto L_0x00421d7a;
    }
    // 00421e56  8b7d76                 -mov edi, dword ptr [ebp + 0x76]
    cpu.edi = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(118) /* 0x76 */);
    // 00421e59  8d755e                 -lea esi, [ebp + 0x5e]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(94) /* 0x5e */);
    // 00421e5c  8b5576                 -mov edx, dword ptr [ebp + 0x76]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(118) /* 0x76 */);
    // 00421e5f  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 00421e61  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00421e62  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00421e63  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00421e64  e817faffff             -call 0x421880
    cpu.esp -= 4;
    sub_421880(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00421e69:
    // 00421e69  8d657e                 -lea esp, [ebp + 0x7e]
    cpu.esp = x86::reg32(cpu.ebp + x86::reg32(126) /* 0x7e */);
    // 00421e6c  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00421e6d  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00421e6e  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00421e6f  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00421e70  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00421e71  c20c00                 -ret 0xc
    cpu.esp += 4+12 /*0xc*/;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 */
void Application::sub_421e80(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00421e80  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00421e81  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00421e82  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00421e83  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00421e84  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00421e85  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00421e87  83ec28                 -sub esp, 0x28
    (cpu.esp) -= x86::reg32(x86::sreg32(40 /*0x28*/));
    // 00421e8a  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 00421e8c  89d1                   -mov ecx, edx
    cpu.ecx = cpu.edx;
    // 00421e8e  8b9084000000           -mov edx, dword ptr [eax + 0x84]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(132) /* 0x84 */);
    // 00421e94  8d04d500000000         -lea eax, [edx*8]
    cpu.eax = x86::reg32(cpu.edx * 8);
    // 00421e9b  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 00421e9d  8b1548d95d00           -mov edx, dword ptr [0x5dd948]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(6150472) /* 0x5dd948 */);
    // 00421ea3  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 00421ea6  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 00421ea8  8b5015                 -mov edx, dword ptr [eax + 0x15]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(21) /* 0x15 */);
    // 00421eab  c1fa18                 -sar edx, 0x18
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (24 /*0x18*/ % 32));
    // 00421eae  c1e209                 -shl edx, 9
    cpu.edx <<= 9 /*0x9*/ % 32;
    // 00421eb1  8955fc                 -mov dword ptr [ebp - 4], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.edx;
    // 00421eb4  dd054c6e5300           -fld qword ptr [0x536e4c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<double>(x86::reg32(5467724) /* 0x536e4c */));
    // 00421eba  db45fc                 -fild dword ptr [ebp - 4]
    x86::Float fpu2 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 00421ebd  d8c9                   -fmul st(1)
    x86::Float fpu3 = cpu.fpu.mul(fpu2, x86::Float(fpu1));
    // 00421ebf  8b5016                 -mov edx, dword ptr [eax + 0x16]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(22) /* 0x16 */);
    // 00421ec2  dd05546e5300           -fld qword ptr [0x536e54]
    x86::Float fpu4 = x86::Float(app->getMemory<double>(x86::reg32(5467732) /* 0x536e54 */));
    // 00421ec8  d9c9                   -fxch st(1)
    
    // 00421eca  d8c9                   -fmul st(1)
    x86::Float fpu5 = cpu.fpu.mul(fpu3, x86::Float(fpu4));
    // 00421ecc  c1fa18                 -sar edx, 0x18
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (24 /*0x18*/ % 32));
    // 00421ecf  8b4017                 -mov eax, dword ptr [eax + 0x17]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(23) /* 0x17 */);
    // 00421ed2  c1e209                 -shl edx, 9
    cpu.edx <<= 9 /*0x9*/ % 32;
    // 00421ed5  c1f818                 -sar eax, 0x18
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (24 /*0x18*/ % 32));
    // 00421ed8  8955fc                 -mov dword ptr [ebp - 4], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.edx;
    // 00421edb  c1e009                 -shl eax, 9
    cpu.eax <<= 9 /*0x9*/ % 32;
    // 00421ede  db45fc                 -fild dword ptr [ebp - 4]
    x86::Float fpu6 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 00421ee1  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 00421ee4  d8cb                   -fmul st(3)
    x86::Float fpu7 = cpu.fpu.mul(fpu6, x86::Float(fpu1));
    // 00421ee6  db45fc                 -fild dword ptr [ebp - 4]
    x86::Float fpu8 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 00421ee9  decc                   -fmulp st(4)
    x86::Float fpu9 = cpu.fpu.mul(fpu1, fpu8);
    // 00421eeb  d8ca                   -fmul st(2)
    x86::Float fpu10 = cpu.fpu.mul(fpu7, x86::Float(fpu4));
    // 00421eed  d9cb                   -fxch st(3)
    
    // 00421eef  deca                   -fmulp st(2)
    x86::Float fpu11 = cpu.fpu.mul(fpu4, fpu9);
    // 00421ef1  d901                   -fld dword ptr [ecx]
    x86::Float fpu12 = x86::Float(app->getMemory<float>(cpu.ecx));
    // 00421ef3  d94104                 -fld dword ptr [ecx + 4]
    x86::Float fpu13 = x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(4) /* 0x4 */));
    // 00421ef6  d94108                 -fld dword ptr [ecx + 8]
    x86::Float fpu14 = x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(8) /* 0x8 */));
    // 00421ef9  d901                   -fld dword ptr [ecx]
    x86::Float fpu15 = x86::Float(app->getMemory<float>(cpu.ecx));
    // 00421efb  d9cc                   -fxch st(4)
    
    // 00421efd  d95de4                 -fstp dword ptr [ebp - 0x1c]
    app->getMemory<float>(cpu.ebp + x86::reg32(-28) /* -0x1c */) = float(fpu5);
    // 00421f00  8d55f0                 -lea edx, [ebp - 0x10]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 00421f03  d9ca                   -fxch st(2)
    
    // 00421f05  d865e4                 -fsub dword ptr [ebp - 0x1c]
    x86::Float fpu16 = cpu.fpu.sub(fpu12, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-28) /* -0x1c */)));
    // 00421f08  d9cb                   -fxch st(3)
    
    // 00421f0a  d845e4                 -fadd dword ptr [ebp - 0x1c]
    x86::Float fpu17 = cpu.fpu.add(fpu15, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-28) /* -0x1c */)));
    // 00421f0d  d9cb                   -fxch st(3)
    
    // 00421f0f  d95dd8                 -fstp dword ptr [ebp - 0x28]
    app->getMemory<float>(cpu.ebp + x86::reg32(-40) /* -0x28 */) = float(fpu16);
    // 00421f12  d9ca                   -fxch st(2)
    
    // 00421f14  d95df0                 -fstp dword ptr [ebp - 0x10]
    app->getMemory<float>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = float(fpu17);
    // 00421f17  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 00421f19  d94104                 -fld dword ptr [ecx + 4]
    x86::Float fpu18 = x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(4) /* 0x4 */));
    // 00421f1c  d9cc                   -fxch st(4)
    
    // 00421f1e  d95de8                 -fstp dword ptr [ebp - 0x18]
    app->getMemory<float>(cpu.ebp + x86::reg32(-24) /* -0x18 */) = float(fpu10);
    // 00421f21  d9ca                   -fxch st(2)
    
    // 00421f23  d95dec                 -fstp dword ptr [ebp - 0x14]
    app->getMemory<float>(cpu.ebp + x86::reg32(-20) /* -0x14 */) = float(fpu11);
    // 00421f26  d865e8                 -fsub dword ptr [ebp - 0x18]
    x86::Float fpu19 = cpu.fpu.sub(fpu13, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-24) /* -0x18 */)));
    // 00421f29  d9ca                   -fxch st(2)
    
    // 00421f2b  d845e8                 -fadd dword ptr [ebp - 0x18]
    x86::Float fpu20 = cpu.fpu.add(fpu18, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-24) /* -0x18 */)));
    // 00421f2e  d9ca                   -fxch st(2)
    
    // 00421f30  d95ddc                 -fstp dword ptr [ebp - 0x24]
    app->getMemory<float>(cpu.ebp + x86::reg32(-36) /* -0x24 */) = float(fpu19);
    // 00421f33  d9c9                   -fxch st(1)
    
    // 00421f35  d95df4                 -fstp dword ptr [ebp - 0xc]
    app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */) = float(fpu20);
    // 00421f38  d865ec                 -fsub dword ptr [ebp - 0x14]
    x86::Float fpu21 = cpu.fpu.sub(fpu14, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-20) /* -0x14 */)));
    // 00421f3b  d94108                 -fld dword ptr [ecx + 8]
    x86::Float fpu22 = x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(8) /* 0x8 */));
    // 00421f3e  d845ec                 -fadd dword ptr [ebp - 0x14]
    x86::Float fpu23 = cpu.fpu.add(fpu22, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-20) /* -0x14 */)));
    // 00421f41  d9c9                   -fxch st(1)
    
    // 00421f43  d95de0                 -fstp dword ptr [ebp - 0x20]
    app->getMemory<float>(cpu.ebp + x86::reg32(-32) /* -0x20 */) = float(fpu21);
    // 00421f46  d95df8                 -fstp dword ptr [ebp - 8]
    app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = float(fpu23);
    }
    // 00421f49  e832f9ffff             -call 0x421880
    cpu.esp -= 4;
    sub_421880(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00421f4e  8b55e0                 -mov edx, dword ptr [ebp - 0x20]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-32) /* -0x20 */);
    // 00421f51  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00421f52  8b75dc                 -mov esi, dword ptr [ebp - 0x24]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-36) /* -0x24 */);
    // 00421f55  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00421f56  8b7dd8                 -mov edi, dword ptr [ebp - 0x28]
    cpu.edi = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-40) /* -0x28 */);
    // 00421f59  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00421f5a  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 00421f5c  8d55f0                 -lea edx, [ebp - 0x10]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 00421f5f  e85cfdffff             -call 0x421cc0
    cpu.esp -= 4;
    sub_421cc0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00421f64  d945f0                 -fld dword ptr [ebp - 0x10]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu24 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-16) /* -0x10 */));
    // 00421f67  d865e4                 -fsub dword ptr [ebp - 0x1c]
    x86::Float fpu25 = cpu.fpu.sub(fpu24, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-28) /* -0x1c */)));
    // 00421f6a  d919                   -fstp dword ptr [ecx]
    app->getMemory<float>(cpu.ecx) = float(fpu25);
    // 00421f6c  d945f4                 -fld dword ptr [ebp - 0xc]
    x86::Float fpu26 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */));
    // 00421f6f  d865e8                 -fsub dword ptr [ebp - 0x18]
    x86::Float fpu27 = cpu.fpu.sub(fpu26, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-24) /* -0x18 */)));
    // 00421f72  89ca                   -mov edx, ecx
    cpu.edx = cpu.ecx;
    // 00421f74  d95904                 -fstp dword ptr [ecx + 4]
    app->getMemory<float>(cpu.ecx + x86::reg32(4) /* 0x4 */) = float(fpu27);
    // 00421f77  d945f8                 -fld dword ptr [ebp - 8]
    x86::Float fpu28 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */));
    // 00421f7a  d865ec                 -fsub dword ptr [ebp - 0x14]
    x86::Float fpu29 = cpu.fpu.sub(fpu28, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-20) /* -0x14 */)));
    // 00421f7d  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 00421f7f  d95908                 -fstp dword ptr [ecx + 8]
    app->getMemory<float>(cpu.ecx + x86::reg32(8) /* 0x8 */) = float(fpu29);
    }
    // 00421f82  e8f9f8ffff             -call 0x421880
    cpu.esp -= 4;
    sub_421880(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00421f87  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00421f89  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00421f8a  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00421f8b  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00421f8c  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00421f8d  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00421f8e  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x90 */
void Application::sub_421f90(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00421f90  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00421f91  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00421f92  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00421f93  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00421f94  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00421f95  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00421f97  83ec28                 -sub esp, 0x28
    (cpu.esp) -= x86::reg32(x86::sreg32(40 /*0x28*/));
    // 00421f9a  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 00421f9c  89d1                   -mov ecx, edx
    cpu.ecx = cpu.edx;
    // 00421f9e  8b9084000000           -mov edx, dword ptr [eax + 0x84]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(132) /* 0x84 */);
    // 00421fa4  8d04d500000000         -lea eax, [edx*8]
    cpu.eax = x86::reg32(cpu.edx * 8);
    // 00421fab  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 00421fad  8b1548d95d00           -mov edx, dword ptr [0x5dd948]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(6150472) /* 0x5dd948 */);
    // 00421fb3  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 00421fb6  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 00421fb8  8b5015                 -mov edx, dword ptr [eax + 0x15]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(21) /* 0x15 */);
    // 00421fbb  c1fa18                 -sar edx, 0x18
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (24 /*0x18*/ % 32));
    // 00421fbe  c1e209                 -shl edx, 9
    cpu.edx <<= 9 /*0x9*/ % 32;
    // 00421fc1  8955fc                 -mov dword ptr [ebp - 4], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.edx;
    // 00421fc4  dd055c6e5300           -fld qword ptr [0x536e5c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<double>(x86::reg32(5467740) /* 0x536e5c */));
    // 00421fca  db45fc                 -fild dword ptr [ebp - 4]
    x86::Float fpu2 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 00421fcd  d8c9                   -fmul st(1)
    x86::Float fpu3 = cpu.fpu.mul(fpu2, x86::Float(fpu1));
    // 00421fcf  8b5016                 -mov edx, dword ptr [eax + 0x16]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(22) /* 0x16 */);
    // 00421fd2  dd05646e5300           -fld qword ptr [0x536e64]
    x86::Float fpu4 = x86::Float(app->getMemory<double>(x86::reg32(5467748) /* 0x536e64 */));
    // 00421fd8  d9c9                   -fxch st(1)
    
    // 00421fda  d8c9                   -fmul st(1)
    x86::Float fpu5 = cpu.fpu.mul(fpu3, x86::Float(fpu4));
    // 00421fdc  c1fa18                 -sar edx, 0x18
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (24 /*0x18*/ % 32));
    // 00421fdf  8b4017                 -mov eax, dword ptr [eax + 0x17]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(23) /* 0x17 */);
    // 00421fe2  c1e209                 -shl edx, 9
    cpu.edx <<= 9 /*0x9*/ % 32;
    // 00421fe5  c1f818                 -sar eax, 0x18
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (24 /*0x18*/ % 32));
    // 00421fe8  8955fc                 -mov dword ptr [ebp - 4], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.edx;
    // 00421feb  c1e009                 -shl eax, 9
    cpu.eax <<= 9 /*0x9*/ % 32;
    // 00421fee  db45fc                 -fild dword ptr [ebp - 4]
    x86::Float fpu6 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 00421ff1  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 00421ff4  d8cb                   -fmul st(3)
    x86::Float fpu7 = cpu.fpu.mul(fpu6, x86::Float(fpu1));
    // 00421ff6  db45fc                 -fild dword ptr [ebp - 4]
    x86::Float fpu8 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 00421ff9  decc                   -fmulp st(4)
    x86::Float fpu9 = cpu.fpu.mul(fpu1, fpu8);
    // 00421ffb  d8ca                   -fmul st(2)
    x86::Float fpu10 = cpu.fpu.mul(fpu7, x86::Float(fpu4));
    // 00421ffd  d9cb                   -fxch st(3)
    
    // 00421fff  deca                   -fmulp st(2)
    x86::Float fpu11 = cpu.fpu.mul(fpu4, fpu9);
    // 00422001  d901                   -fld dword ptr [ecx]
    x86::Float fpu12 = x86::Float(app->getMemory<float>(cpu.ecx));
    // 00422003  d94104                 -fld dword ptr [ecx + 4]
    x86::Float fpu13 = x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(4) /* 0x4 */));
    // 00422006  d94108                 -fld dword ptr [ecx + 8]
    x86::Float fpu14 = x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(8) /* 0x8 */));
    // 00422009  d901                   -fld dword ptr [ecx]
    x86::Float fpu15 = x86::Float(app->getMemory<float>(cpu.ecx));
    // 0042200b  d9cc                   -fxch st(4)
    
    // 0042200d  d95de4                 -fstp dword ptr [ebp - 0x1c]
    app->getMemory<float>(cpu.ebp + x86::reg32(-28) /* -0x1c */) = float(fpu5);
    // 00422010  8d55f0                 -lea edx, [ebp - 0x10]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 00422013  d9ca                   -fxch st(2)
    
    // 00422015  d845e4                 -fadd dword ptr [ebp - 0x1c]
    x86::Float fpu16 = cpu.fpu.add(fpu12, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-28) /* -0x1c */)));
    // 00422018  d9cb                   -fxch st(3)
    
    // 0042201a  d865e4                 -fsub dword ptr [ebp - 0x1c]
    x86::Float fpu17 = cpu.fpu.sub(fpu15, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-28) /* -0x1c */)));
    // 0042201d  d9cb                   -fxch st(3)
    
    // 0042201f  d95dd8                 -fstp dword ptr [ebp - 0x28]
    app->getMemory<float>(cpu.ebp + x86::reg32(-40) /* -0x28 */) = float(fpu16);
    // 00422022  d9ca                   -fxch st(2)
    
    // 00422024  d95df0                 -fstp dword ptr [ebp - 0x10]
    app->getMemory<float>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = float(fpu17);
    // 00422027  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 00422029  d94104                 -fld dword ptr [ecx + 4]
    x86::Float fpu18 = x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(4) /* 0x4 */));
    // 0042202c  d9cc                   -fxch st(4)
    
    // 0042202e  d95de8                 -fstp dword ptr [ebp - 0x18]
    app->getMemory<float>(cpu.ebp + x86::reg32(-24) /* -0x18 */) = float(fpu10);
    // 00422031  d9ca                   -fxch st(2)
    
    // 00422033  d95dec                 -fstp dword ptr [ebp - 0x14]
    app->getMemory<float>(cpu.ebp + x86::reg32(-20) /* -0x14 */) = float(fpu11);
    // 00422036  d845e8                 -fadd dword ptr [ebp - 0x18]
    x86::Float fpu19 = cpu.fpu.add(fpu13, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-24) /* -0x18 */)));
    // 00422039  d9ca                   -fxch st(2)
    
    // 0042203b  d865e8                 -fsub dword ptr [ebp - 0x18]
    x86::Float fpu20 = cpu.fpu.sub(fpu18, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-24) /* -0x18 */)));
    // 0042203e  d9ca                   -fxch st(2)
    
    // 00422040  d95ddc                 -fstp dword ptr [ebp - 0x24]
    app->getMemory<float>(cpu.ebp + x86::reg32(-36) /* -0x24 */) = float(fpu19);
    // 00422043  d9c9                   -fxch st(1)
    
    // 00422045  d95df4                 -fstp dword ptr [ebp - 0xc]
    app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */) = float(fpu20);
    // 00422048  d845ec                 -fadd dword ptr [ebp - 0x14]
    x86::Float fpu21 = cpu.fpu.add(fpu14, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-20) /* -0x14 */)));
    // 0042204b  d94108                 -fld dword ptr [ecx + 8]
    x86::Float fpu22 = x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(8) /* 0x8 */));
    // 0042204e  d865ec                 -fsub dword ptr [ebp - 0x14]
    x86::Float fpu23 = cpu.fpu.sub(fpu22, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-20) /* -0x14 */)));
    // 00422051  d9c9                   -fxch st(1)
    
    // 00422053  d95de0                 -fstp dword ptr [ebp - 0x20]
    app->getMemory<float>(cpu.ebp + x86::reg32(-32) /* -0x20 */) = float(fpu21);
    // 00422056  d95df8                 -fstp dword ptr [ebp - 8]
    app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = float(fpu23);
    }
    // 00422059  e822f8ffff             -call 0x421880
    cpu.esp -= 4;
    sub_421880(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042205e  8b55e0                 -mov edx, dword ptr [ebp - 0x20]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-32) /* -0x20 */);
    // 00422061  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00422062  8b75dc                 -mov esi, dword ptr [ebp - 0x24]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-36) /* -0x24 */);
    // 00422065  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00422066  8b7dd8                 -mov edi, dword ptr [ebp - 0x28]
    cpu.edi = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-40) /* -0x28 */);
    // 00422069  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 0042206a  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 0042206c  8d55f0                 -lea edx, [ebp - 0x10]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 0042206f  e84cfcffff             -call 0x421cc0
    cpu.esp -= 4;
    sub_421cc0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00422074  d945f0                 -fld dword ptr [ebp - 0x10]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu24 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-16) /* -0x10 */));
    // 00422077  d845e4                 -fadd dword ptr [ebp - 0x1c]
    x86::Float fpu25 = cpu.fpu.add(fpu24, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-28) /* -0x1c */)));
    // 0042207a  d919                   -fstp dword ptr [ecx]
    app->getMemory<float>(cpu.ecx) = float(fpu25);
    // 0042207c  d945f4                 -fld dword ptr [ebp - 0xc]
    x86::Float fpu26 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */));
    // 0042207f  d845e8                 -fadd dword ptr [ebp - 0x18]
    x86::Float fpu27 = cpu.fpu.add(fpu26, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-24) /* -0x18 */)));
    // 00422082  89ca                   -mov edx, ecx
    cpu.edx = cpu.ecx;
    // 00422084  d95904                 -fstp dword ptr [ecx + 4]
    app->getMemory<float>(cpu.ecx + x86::reg32(4) /* 0x4 */) = float(fpu27);
    // 00422087  d945f8                 -fld dword ptr [ebp - 8]
    x86::Float fpu28 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */));
    // 0042208a  d845ec                 -fadd dword ptr [ebp - 0x14]
    x86::Float fpu29 = cpu.fpu.add(fpu28, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-20) /* -0x14 */)));
    // 0042208d  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 0042208f  d95908                 -fstp dword ptr [ecx + 8]
    app->getMemory<float>(cpu.ecx + x86::reg32(8) /* 0x8 */) = float(fpu29);
    }
    // 00422092  e8e9f7ffff             -call 0x421880
    cpu.esp -= 4;
    sub_421880(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00422097  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00422099  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042209a  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042209b  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042209c  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042209d  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042209e  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x90 */
void Application::sub_4220a0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004220a0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004220a1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004220a2  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004220a3  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004220a4  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004220a5  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004220a7  83ec6c                 -sub esp, 0x6c
    (cpu.esp) -= x86::reg32(x86::sreg32(108 /*0x6c*/));
    // 004220aa  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 004220ac  89d1                   -mov ecx, edx
    cpu.ecx = cpu.edx;
    // 004220ae  83c074                 -add eax, 0x74
    (cpu.eax) += x86::reg32(x86::sreg32(116 /*0x74*/));
    // 004220b1  ba01000000             -mov edx, 1
    cpu.edx = 1 /*0x1*/;
    // 004220b6  8b7010                 -mov esi, dword ptr [eax + 0x10]
    cpu.esi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(16) /* 0x10 */);
    // 004220b9  e822e7ffff             -call 0x4207e0
    cpu.esp -= 4;
    nfs3hp::trackdata::positionSurface(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004220be  8b9388000000           -mov edx, dword ptr [ebx + 0x88]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(136) /* 0x88 */);
    // 004220c4  83e03f                 -and eax, 0x3f
    cpu.eax &= x86::reg32(x86::sreg32(63 /*0x3f*/));
    // 004220c7  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 004220c9  0f846e000000           -je 0x42213d
    if (cpu.flags.zf)
    {
        goto L_0x0042213d;
    }
    // 004220cf  83bb8c00000000         +cmp dword ptr [ebx + 0x8c], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(140) /* 0x8c */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004220d6  7465                   -je 0x42213d
    if (cpu.flags.zf)
    {
        goto L_0x0042213d;
    }
    // 004220d8  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004220da  7461                   -je 0x42213d
    if (cpu.flags.zf)
    {
        goto L_0x0042213d;
    }
    // 004220dc  83f80e                 +cmp eax, 0xe
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
    // 004220df  745c                   -je 0x42213d
    if (cpu.flags.zf)
    {
        goto L_0x0042213d;
    }
    // 004220e1  8d7d94                 -lea edi, [ebp - 0x6c]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(-108) /* -0x6c */);
    // 004220e4  8bb3c8000000           -mov esi, dword ptr [ebx + 0xc8]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(200) /* 0xc8 */);
    // 004220ea  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004220eb  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004220ec  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004220ed  8d7da0                 -lea edi, [ebp - 0x60]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(-96) /* -0x60 */);
    // 004220f0  8bb3cc000000           -mov esi, dword ptr [ebx + 0xcc]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(204) /* 0xcc */);
    // 004220f6  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004220f7  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004220f8  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004220f9  8d7dac                 -lea edi, [ebp - 0x54]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(-84) /* -0x54 */);
    // 004220fc  8bb3d0000000           -mov esi, dword ptr [ebx + 0xd0]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(208) /* 0xd0 */);
    // 00422102  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00422103  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00422104  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00422105  8d7db8                 -lea edi, [ebp - 0x48]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(-72) /* -0x48 */);
    // 00422108  8bb3d4000000           -mov esi, dword ptr [ebx + 0xd4]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(212) /* 0xd4 */);
    // 0042210e  8d55c4                 -lea edx, [ebp - 0x3c]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-60) /* -0x3c */);
    // 00422111  8d4594                 -lea eax, [ebp - 0x6c]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-108) /* -0x6c */);
    // 00422114  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00422115  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00422116  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00422117  e834490700             -call 0x496a50
    cpu.esp -= 4;
    sub_496a50(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042211c  8b4108                 -mov eax, dword ptr [ecx + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(8) /* 0x8 */);
    // 0042211f  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00422120  8b5104                 -mov edx, dword ptr [ecx + 4]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(4) /* 0x4 */);
    // 00422123  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00422124  8b31                   -mov esi, dword ptr [ecx]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ecx);
    // 00422126  8b83c8000000           -mov eax, dword ptr [ebx + 0xc8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(200) /* 0xc8 */);
    // 0042212c  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 0042212d  8b7808                 -mov edi, dword ptr [eax + 8]
    cpu.edi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 00422130  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00422131  8b5004                 -mov edx, dword ptr [eax + 4]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 00422134  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00422135  8b18                   -mov ebx, dword ptr [eax]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.eax);
    // 00422137  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00422138  e912010000             -jmp 0x42224f
    goto L_0x0042224f;
L_0x0042213d:
    // 0042213d  8d04f500000000         -lea eax, [esi*8]
    cpu.eax = x86::reg32(cpu.esi * 8);
    // 00422144  01f0                   -add eax, esi
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.esi));
    // 00422146  8b1548d95d00           -mov edx, dword ptr [0x5dd948]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(6150472) /* 0x5dd948 */);
    // 0042214c  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 0042214f  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 00422151  8b5015                 -mov edx, dword ptr [eax + 0x15]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(21) /* 0x15 */);
    // 00422154  c1fa18                 -sar edx, 0x18
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (24 /*0x18*/ % 32));
    // 00422157  c1e209                 -shl edx, 9
    cpu.edx <<= 9 /*0x9*/ % 32;
    // 0042215a  8955fc                 -mov dword ptr [ebp - 4], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.edx;
    // 0042215d  dd05746e5300           -fld qword ptr [0x536e74]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<double>(x86::reg32(5467764) /* 0x536e74 */));
    // 00422163  db45fc                 -fild dword ptr [ebp - 4]
    x86::Float fpu2 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 00422166  d8c9                   -fmul st(1)
    x86::Float fpu3 = cpu.fpu.mul(fpu2, x86::Float(fpu1));
    // 00422168  db00                   -fild dword ptr [eax]
    x86::Float fpu4 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.eax)));
    // 0042216a  db4004                 -fild dword ptr [eax + 4]
    x86::Float fpu5 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */)));
    // 0042216d  db4008                 -fild dword ptr [eax + 8]
    x86::Float fpu6 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */)));
    // 00422170  d9cb                   -fxch st(3)
    
    // 00422172  d95dc4                 -fstp dword ptr [ebp - 0x3c]
    app->getMemory<float>(cpu.ebp + x86::reg32(-60) /* -0x3c */) = float(fpu3);
    // 00422175  8b5016                 -mov edx, dword ptr [eax + 0x16]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(22) /* 0x16 */);
    // 00422178  c1fa18                 -sar edx, 0x18
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (24 /*0x18*/ % 32));
    // 0042217b  c1e209                 -shl edx, 9
    cpu.edx <<= 9 /*0x9*/ % 32;
    // 0042217e  8955fc                 -mov dword ptr [ebp - 4], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.edx;
    // 00422181  db45fc                 -fild dword ptr [ebp - 4]
    x86::Float fpu7 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 00422184  d8cc                   -fmul st(4)
    x86::Float fpu8 = cpu.fpu.mul(fpu7, x86::Float(fpu1));
    // 00422186  d95dc8                 -fstp dword ptr [ebp - 0x38]
    app->getMemory<float>(cpu.ebp + x86::reg32(-56) /* -0x38 */) = float(fpu8);
    // 00422189  8b5017                 -mov edx, dword ptr [eax + 0x17]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(23) /* 0x17 */);
    // 0042218c  c1fa18                 -sar edx, 0x18
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (24 /*0x18*/ % 32));
    // 0042218f  c1e209                 -shl edx, 9
    cpu.edx <<= 9 /*0x9*/ % 32;
    // 00422192  8955fc                 -mov dword ptr [ebp - 4], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.edx;
    // 00422195  db45fc                 -fild dword ptr [ebp - 4]
    x86::Float fpu9 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 00422198  d8cc                   -fmul st(4)
    x86::Float fpu10 = cpu.fpu.mul(fpu9, x86::Float(fpu1));
    // 0042219a  d9ca                   -fxch st(2)
    
    // 0042219c  d8cc                   -fmul st(4)
    x86::Float fpu11 = cpu.fpu.mul(fpu4, x86::Float(fpu1));
    // 0042219e  d9ca                   -fxch st(2)
    
    // 004221a0  d95dcc                 -fstp dword ptr [ebp - 0x34]
    app->getMemory<float>(cpu.ebp + x86::reg32(-52) /* -0x34 */) = float(fpu10);
    // 004221a3  8b500d                 -mov edx, dword ptr [eax + 0xd]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(13) /* 0xd */);
    // 004221a6  c1fa18                 -sar edx, 0x18
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (24 /*0x18*/ % 32));
    // 004221a9  c1e209                 -shl edx, 9
    cpu.edx <<= 9 /*0x9*/ % 32;
    // 004221ac  8955fc                 -mov dword ptr [ebp - 4], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.edx;
    // 004221af  db45fc                 -fild dword ptr [ebp - 4]
    x86::Float fpu12 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 004221b2  d8cc                   -fmul st(4)
    x86::Float fpu13 = cpu.fpu.mul(fpu12, x86::Float(fpu1));
    // 004221b4  d9c9                   -fxch st(1)
    
    // 004221b6  d8cc                   -fmul st(4)
    x86::Float fpu14 = cpu.fpu.mul(fpu5, x86::Float(fpu1));
    // 004221b8  d9c9                   -fxch st(1)
    
    // 004221ba  d95dd0                 -fstp dword ptr [ebp - 0x30]
    app->getMemory<float>(cpu.ebp + x86::reg32(-48) /* -0x30 */) = float(fpu13);
    // 004221bd  8b500e                 -mov edx, dword ptr [eax + 0xe]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(14) /* 0xe */);
    // 004221c0  c1fa18                 -sar edx, 0x18
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (24 /*0x18*/ % 32));
    // 004221c3  c1e209                 -shl edx, 9
    cpu.edx <<= 9 /*0x9*/ % 32;
    // 004221c6  8955fc                 -mov dword ptr [ebp - 4], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.edx;
    // 004221c9  db45fc                 -fild dword ptr [ebp - 4]
    x86::Float fpu15 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 004221cc  d8cc                   -fmul st(4)
    x86::Float fpu16 = cpu.fpu.mul(fpu15, x86::Float(fpu1));
    // 004221ce  d9cb                   -fxch st(3)
    
    // 004221d0  d8cc                   -fmul st(4)
    x86::Float fpu17 = cpu.fpu.mul(fpu6, x86::Float(fpu1));
    // 004221d2  d9cb                   -fxch st(3)
    
    // 004221d4  d95dd4                 -fstp dword ptr [ebp - 0x2c]
    app->getMemory<float>(cpu.ebp + x86::reg32(-44) /* -0x2c */) = float(fpu16);
    // 004221d7  8b500f                 -mov edx, dword ptr [eax + 0xf]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(15) /* 0xf */);
    // 004221da  c1fa18                 -sar edx, 0x18
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (24 /*0x18*/ % 32));
    // 004221dd  c1e209                 -shl edx, 9
    cpu.edx <<= 9 /*0x9*/ % 32;
    // 004221e0  8955fc                 -mov dword ptr [ebp - 4], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.edx;
    // 004221e3  db45fc                 -fild dword ptr [ebp - 4]
    x86::Float fpu18 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 004221e6  decc                   -fmulp st(4)
    x86::Float fpu19 = cpu.fpu.mul(fpu1, fpu18);
    // 004221e8  d9c9                   -fxch st(1)
    
    // 004221ea  d95de8                 -fstp dword ptr [ebp - 0x18]
    app->getMemory<float>(cpu.ebp + x86::reg32(-24) /* -0x18 */) = float(fpu11);
    // 004221ed  d95dec                 -fstp dword ptr [ebp - 0x14]
    app->getMemory<float>(cpu.ebp + x86::reg32(-20) /* -0x14 */) = float(fpu14);
    // 004221f0  d95df0                 -fstp dword ptr [ebp - 0x10]
    app->getMemory<float>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = float(fpu17);
    // 004221f3  d95dd8                 -fstp dword ptr [ebp - 0x28]
    app->getMemory<float>(cpu.ebp + x86::reg32(-40) /* -0x28 */) = float(fpu19);
    // 004221f6  8b5011                 -mov edx, dword ptr [eax + 0x11]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(17) /* 0x11 */);
    // 004221f9  c1fa18                 -sar edx, 0x18
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (24 /*0x18*/ % 32));
    // 004221fc  c1e209                 -shl edx, 9
    cpu.edx <<= 9 /*0x9*/ % 32;
    // 004221ff  8955fc                 -mov dword ptr [ebp - 4], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.edx;
    // 00422202  dd05746e5300           -fld qword ptr [0x536e74]
    x86::Float fpu20 = x86::Float(app->getMemory<double>(x86::reg32(5467764) /* 0x536e74 */));
    // 00422208  db45fc                 -fild dword ptr [ebp - 4]
    x86::Float fpu21 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 0042220b  d8c9                   -fmul st(1)
    x86::Float fpu22 = cpu.fpu.mul(fpu21, x86::Float(fpu20));
    // 0042220d  d95ddc                 -fstp dword ptr [ebp - 0x24]
    app->getMemory<float>(cpu.ebp + x86::reg32(-36) /* -0x24 */) = float(fpu22);
    // 00422210  8b5012                 -mov edx, dword ptr [eax + 0x12]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(18) /* 0x12 */);
    // 00422213  c1fa18                 -sar edx, 0x18
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (24 /*0x18*/ % 32));
    // 00422216  c1e209                 -shl edx, 9
    cpu.edx <<= 9 /*0x9*/ % 32;
    // 00422219  8955fc                 -mov dword ptr [ebp - 4], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.edx;
    // 0042221c  db45fc                 -fild dword ptr [ebp - 4]
    x86::Float fpu23 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 0042221f  d8c9                   -fmul st(1)
    x86::Float fpu24 = cpu.fpu.mul(fpu23, x86::Float(fpu20));
    // 00422221  d95de0                 -fstp dword ptr [ebp - 0x20]
    app->getMemory<float>(cpu.ebp + x86::reg32(-32) /* -0x20 */) = float(fpu24);
    // 00422224  8b4013                 -mov eax, dword ptr [eax + 0x13]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(19) /* 0x13 */);
    // 00422227  c1f818                 -sar eax, 0x18
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (24 /*0x18*/ % 32));
    // 0042222a  c1e009                 +shl eax, 9
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
    // 0042222d  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 00422230  db45fc                 +fild dword ptr [ebp - 4]
    x86::Float fpu25 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 00422233  dec9                   +fmulp st(1)
    x86::Float fpu26 = cpu.fpu.mul(fpu20, fpu25);
    // 00422235  d95de4                 +fstp dword ptr [ebp - 0x1c]
    app->getMemory<float>(cpu.ebp + x86::reg32(-28) /* -0x1c */) = float(fpu26);
    // 00422238  8b7108                 -mov esi, dword ptr [ecx + 8]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(8) /* 0x8 */);
    // 0042223b  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 0042223c  8b7904                 -mov edi, dword ptr [ecx + 4]
    cpu.edi = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(4) /* 0x4 */);
    // 0042223f  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00422240  8b01                   -mov eax, dword ptr [ecx]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx);
    // 00422242  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00422243  8b55f0                 -mov edx, dword ptr [ebp - 0x10]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 00422246  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00422247  8b5dec                 -mov ebx, dword ptr [ebp - 0x14]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */);
    // 0042224a  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 0042224b  8b75e8                 -mov esi, dword ptr [ebp - 0x18]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-24) /* -0x18 */);
    // 0042224e  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    }
L_0x0042224f:
    // 0042224f  8d45c4                 -lea eax, [ebp - 0x3c]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-60) /* -0x3c */);
    // 00422252  e849460700             -call 0x4968a0
    cpu.esp -= 4;
    sub_4968a0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00422257  dc056c6e5300           +fadd qword ptr [0x536e6c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu27 = cpu.fpu.st(0);
    x86::Float fpu28 = cpu.fpu.add(fpu27, x86::Float(app->getMemory<double>(x86::reg32(5467756) /* 0x536e6c */)));
    // 0042225d  d95df8                 +fstp dword ptr [ebp - 8]
    app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = float(fpu28);
    // 00422260  d94104                 +fld dword ptr [ecx + 4]
    x86::Float fpu29 = x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(4) /* 0x4 */));
    // 00422263  d85df8                 +fcomp dword ptr [ebp - 8]
    cpu.fpu.compare(fpu29, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    // 00422266  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00422268  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    cpu.fpu.count -= 1;
    }
    // 00422269  7605                   -jbe 0x422270
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x00422270;
    }
    // 0042226b  8b4104                 -mov eax, dword ptr [ecx + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(4) /* 0x4 */);
    // 0042226e  eb03                   -jmp 0x422273
    goto L_0x00422273;
L_0x00422270:
    // 00422270  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
L_0x00422273:
    // 00422273  8945f4                 -mov dword ptr [ebp - 0xc], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.eax;
    // 00422276  8b45f4                 -mov eax, dword ptr [ebp - 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 00422279  894104                 -mov dword ptr [ecx + 4], eax
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(4) /* 0x4 */) = cpu.eax;
    // 0042227c  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 0042227e  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042227f  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00422280  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00422281  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00422282  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00422283  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 */
void Application::sub_422290(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00422290  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00422291  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00422292  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00422293  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00422294  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00422295  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00422297  83ec40                 -sub esp, 0x40
    (cpu.esp) -= x86::reg32(x86::sreg32(64 /*0x40*/));
    // 0042229a  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 0042229d  8955f0                 -mov dword ptr [ebp - 0x10], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = cpu.edx;
    // 004222a0  83c02c                 -add eax, 0x2c
    (cpu.eax) += x86::reg32(x86::sreg32(44 /*0x2c*/));
    // 004222a3  8945ec                 -mov dword ptr [ebp - 0x14], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */) = cpu.eax;
    // 004222a6  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004222a9  83c038                 -add eax, 0x38
    (cpu.eax) += x86::reg32(x86::sreg32(56 /*0x38*/));
    // 004222ac  8945e8                 -mov dword ptr [ebp - 0x18], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-24) /* -0x18 */) = cpu.eax;
    // 004222af  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004222b2  8d7dc0                 -lea edi, [ebp - 0x40]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(-64) /* -0x40 */);
    // 004222b5  83c044                 +add eax, 0x44
    {
        x86::reg32& tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(68 /*0x44*/));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 004222b8  bed0124200             -mov esi, 0x4212d0
    cpu.esi = 4330192 /*0x4212d0*/;
    // 004222bd  8945f8                 -mov dword ptr [ebp - 8], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.eax;
    // 004222c0  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004222c3  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004222c4  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004222c5  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004222c6  8b4008                 -mov eax, dword ptr [eax + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 004222c9  8b8098000000           -mov eax, dword ptr [eax + 0x98]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(152) /* 0x98 */);
    // 004222cf  8945d8                 -mov dword ptr [ebp - 0x28], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-40) /* -0x28 */) = cpu.eax;
    // 004222d2  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004222d5  8b4008                 -mov eax, dword ptr [eax + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 004222d8  8b809c000000           -mov eax, dword ptr [eax + 0x9c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(156) /* 0x9c */);
    // 004222de  8945dc                 -mov dword ptr [ebp - 0x24], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-36) /* -0x24 */) = cpu.eax;
    // 004222e1  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004222e4  8b4008                 -mov eax, dword ptr [eax + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 004222e7  8d4dcc                 -lea ecx, [ebp - 0x34]
    cpu.ecx = x86::reg32(cpu.ebp + x86::reg32(-52) /* -0x34 */);
    // 004222ea  89d3                   -mov ebx, edx
    cpu.ebx = cpu.edx;
    // 004222ec  8b80a0000000           -mov eax, dword ptr [eax + 0xa0]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(160) /* 0xa0 */);
    // 004222f2  8d55d8                 -lea edx, [ebp - 0x28]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-40) /* -0x28 */);
    // 004222f5  8945e0                 -mov dword ptr [ebp - 0x20], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-32) /* -0x20 */) = cpu.eax;
    // 004222f8  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 004222fd  e8fedc0b00             -call 0x4e0000
    cpu.esp -= 4;
    sub_4e0000(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00422302  8b4df8                 -mov ecx, dword ptr [ebp - 8]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 00422305  8b5df0                 -mov ebx, dword ptr [ebp - 0x10]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 00422308  8d55d8                 -lea edx, [ebp - 0x28]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-40) /* -0x28 */);
    // 0042230b  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 00422310  e8ebdc0b00             -call 0x4e0000
    cpu.esp -= 4;
    sub_4e0000(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00422315  8b55f8                 -mov edx, dword ptr [ebp - 8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 00422318  8d4de4                 -lea ecx, [ebp - 0x1c]
    cpu.ecx = x86::reg32(cpu.ebp + x86::reg32(-28) /* -0x1c */);
    // 0042231b  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 0042231d  8b5df8                 -mov ebx, dword ptr [ebp - 8]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 00422320  e89bde0b00             -call 0x4e01c0
    cpu.esp -= 4;
    sub_4e01c0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00422325  8d55c0                 -lea edx, [ebp - 0x40]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-64) /* -0x40 */);
    // 00422328  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 0042232d  e8dede0b00             -call 0x4e0210
    cpu.esp -= 4;
    sub_4e0210(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00422332  d9ee                   +fldz 
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = 0.0;
    // 00422334  d85de4                 +fcomp dword ptr [ebp - 0x1c]
    cpu.fpu.compare(fpu1, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-28) /* -0x1c */)));
    // 00422337  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00422339  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 0042233a  760a                   -jbe 0x422346
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x00422346;
    }
    // 0042233c  d945e4                 +fld dword ptr [ebp - 0x1c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu2 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-28) /* -0x1c */));
    // 0042233f  d9e0                   +fchs 
    x86::Float fpu3 = -fpu2;
    // 00422341  d95df4                 +fstp dword ptr [ebp - 0xc]
    app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */) = float(fpu3);
    }
    // 00422344  eb06                   -jmp 0x42234c
    goto L_0x0042234c;
L_0x00422346:
    // 00422346  8b45e4                 -mov eax, dword ptr [ebp - 0x1c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-28) /* -0x1c */);
    // 00422349  8945f4                 -mov dword ptr [ebp - 0xc], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.eax;
L_0x0042234c:
    // 0042234c  d945f4                 +fld dword ptr [ebp - 0xc]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu4 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */));
    // 0042234f  dc1d7c6e5300           +fcomp qword ptr [0x536e7c]
    cpu.fpu.compare(fpu4, x86::Float(app->getMemory<double>(x86::reg32(5467772) /* 0x536e7c */)));
    // 00422355  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00422357  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 00422358  7609                   -jbe 0x422363
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x00422363;
    }
    // 0042235a  8d7dc0                 -lea edi, [ebp - 0x40]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(-64) /* -0x40 */);
    // 0042235d  8b75e8                 -mov esi, dword ptr [ebp - 0x18]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-24) /* -0x18 */);
    // 00422360  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00422361  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00422362  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
L_0x00422363:
    // 00422363  8b5dec                 -mov ebx, dword ptr [ebp - 0x14]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */);
    // 00422366  8b55f8                 -mov edx, dword ptr [ebp - 8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 00422369  8d45c0                 -lea eax, [ebp - 0x40]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-64) /* -0x40 */);
    // 0042236c  e82fde0b00             -call 0x4e01a0
    cpu.esp -= 4;
    sub_4e01a0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00422371  8b5de8                 -mov ebx, dword ptr [ebp - 0x18]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-24) /* -0x18 */);
    // 00422374  8b55ec                 -mov edx, dword ptr [ebp - 0x14]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */);
    // 00422377  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 0042237a  e8e1dd0b00             -call 0x4e0160
    cpu.esp -= 4;
    sub_4e0160(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042237f  8b55fc                 -mov edx, dword ptr [ebp - 4]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00422382  83c22c                 -add edx, 0x2c
    (cpu.edx) += x86::reg32(x86::sreg32(44 /*0x2c*/));
    // 00422385  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00422388  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00422389  ff7050                 -push dword ptr [eax + 0x50]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(80) /* 0x50 */);
    cpu.esp -= 4;
    // 0042238c  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 0042238e  e8ed820c00             -call 0x4ea680
    cpu.esp -= 4;
    sub_4ea680(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00422393  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00422396  8b08                   -mov ecx, dword ptr [eax]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax);
    // 00422398  83f90a                 +cmp ecx, 0xa
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(10 /*0xa*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0042239b  7518                   -jne 0x4223b5
    if (!cpu.flags.zf)
    {
        goto L_0x004223b5;
    }
    // 0042239d  8b400c                 -mov eax, dword ptr [eax + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
    // 004223a0  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004223a1  8b0485182f5500         -mov eax, dword ptr [eax*4 + 0x552f18]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5582616) /* 0x552f18 */ + cpu.eax * 4);
    // 004223a8  ffb01c010000           -push dword ptr [eax + 0x11c]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(284) /* 0x11c */);
    cpu.esp -= 4;
    // 004223ae  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004223b0  e8fb860c00             -call 0x4eaab0
    cpu.esp -= 4;
    sub_4eaab0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x004223b5:
    // 004223b5  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004223b7  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004223b8  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004223b9  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004223ba  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004223bb  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004223bc  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x40 0x00 */
void Application::sub_4223c0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004223c0  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004223c1  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004223c2  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004223c3  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004223c5  81ecb0000000           -sub esp, 0xb0
    (cpu.esp) -= x86::reg32(x86::sreg32(176 /*0xb0*/));
    // 004223cb  81ed82000000           -sub ebp, 0x82
    (cpu.ebp) -= x86::reg32(x86::sreg32(130 /*0x82*/));
    // 004223d1  89457a                 -mov dword ptr [ebp + 0x7a], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(122) /* 0x7a */) = cpu.eax;
    // 004223d4  895576                 -mov dword ptr [ebp + 0x76], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(118) /* 0x76 */) = cpu.edx;
    // 004223d7  8b149d602f5500         -mov edx, dword ptr [ebx*4 + 0x552f60]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5582688) /* 0x552f60 */ + cpu.ebx * 4);
    // 004223de  8bb218010000           -mov esi, dword ptr [edx + 0x118]
    cpu.esi = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(280) /* 0x118 */);
    // 004223e4  895572                 -mov dword ptr [ebp + 0x72], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(114) /* 0x72 */) = cpu.edx;
    // 004223e7  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 004223e9  0f8419010000           -je 0x422508
    if (cpu.flags.zf)
    {
        goto L_0x00422508;
    }
    // 004223ef  83ba1c01000000         +cmp dword ptr [edx + 0x11c], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(284) /* 0x11c */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004223f6  0f840c010000           -je 0x422508
    if (cpu.flags.zf)
    {
        goto L_0x00422508;
    }
    // 004223fc  d98210010000           -fld dword ptr [edx + 0x110]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(272) /* 0x110 */));
    // 00422402  d805846e5300           -fadd dword ptr [0x536e84]
    x86::Float fpu2 = cpu.fpu.add(fpu1, x86::Float(app->getMemory<float>(x86::reg32(5467780) /* 0x536e84 */)));
    // 00422408  d80d886e5300           -fmul dword ptr [0x536e88]
    x86::Float fpu3 = cpu.fpu.mul(fpu2, x86::Float(app->getMemory<float>(x86::reg32(5467784) /* 0x536e88 */)));
    // 0042240e  d9e8                   -fld1 
    x86::Float fpu4 = 1.0;
    // 00422410  d9ea                   -fldl2e 
    x86::Float fpu5 = 1.4426950408889634;
    // 00422412  d8ca                   -fmul st(2)
    x86::Float fpu6 = cpu.fpu.mul(fpu5, x86::Float(fpu3));
    // 00422414  ddd2                   -fst st(2)
    x86::Float fpu7 = x86::Float(fpu6);
    // 00422416  d9f8                   -fprem 
    x86::Float fpu8 = cpu.fpu.rem(fpu6, fpu4);
    // 00422418  d9f0                   -f2xm1 
    x86::Float fpu9 = cpu.fpu.f2xm1(fpu8);
    // 0042241a  dec1                   -faddp st(1)
    x86::Float fpu10 = cpu.fpu.add(fpu4, fpu9);
    // 0042241c  d9fd                   -fscale 
    x86::Float fpu11 = cpu.fpu.scale(fpu10, fpu7);
    // 0042241e  ddd9                   -fstp st(1)
    x86::Float fpu12 = x86::Float(fpu11);
    // 00422420  d9e8                   -fld1 
    x86::Float fpu13 = 1.0;
    // 00422422  dec1                   -faddp st(1)
    x86::Float fpu14 = cpu.fpu.add(fpu12, fpu13);
    // 00422424  d9e8                   -fld1 
    x86::Float fpu15 = 1.0;
    // 00422426  def1                   -fdivrp st(1)
    x86::Float fpu16 = cpu.fpu.div(fpu15, x86::Float(fpu14));
    // 00422428  d9e8                   -fld1 
    x86::Float fpu17 = 1.0;
    // 0042242a  8d7d3a                 -lea edi, [ebp + 0x3a]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(58) /* 0x3a */);
    // 0042242d  8db220010000           -lea esi, [edx + 0x120]
    cpu.esi = x86::reg32(cpu.edx + x86::reg32(288) /* 0x120 */);
    // 00422433  d9c9                   -fxch st(1)
    
    // 00422435  d95d7e                 -fstp dword ptr [ebp + 0x7e]
    app->getMemory<float>(cpu.ebp + x86::reg32(126) /* 0x7e */) = float(fpu16);
    // 00422438  d8657e                 -fsub dword ptr [ebp + 0x7e]
    x86::Float fpu18 = cpu.fpu.sub(fpu17, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(126) /* 0x7e */)));
    // 0042243b  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 0042243c  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 0042243d  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 0042243e  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 0042243f  d95d6e                 -fstp dword ptr [ebp + 0x6e]
    app->getMemory<float>(cpu.ebp + x86::reg32(110) /* 0x6e */) = float(fpu18);
    // 00422442  83f901                 +cmp ecx, 1
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1 /*0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    }
    // 00422445  7521                   -jne 0x422468
    if (!cpu.flags.zf)
    {
        goto L_0x00422468;
    }
    // 00422447  8d55f6                 -lea edx, [ebp - 0xa]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-10) /* -0xa */);
    // 0042244a  8d453a                 -lea eax, [ebp + 0x3a]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(58) /* 0x3a */);
    // 0042244d  e83e510900             -call 0x4b7590
    cpu.esp -= 4;
    sub_4b7590(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00422452  8d55d2                 -lea edx, [ebp - 0x2e]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-46) /* -0x2e */);
    // 00422455  8d45f6                 -lea eax, [ebp - 0xa]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-10) /* -0xa */);
    // 00422458  e813f1ffff             -call 0x421570
    cpu.esp -= 4;
    sub_421570(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042245d  8d553a                 -lea edx, [ebp + 0x3a]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(58) /* 0x3a */);
    // 00422460  8d45d2                 -lea eax, [ebp - 0x2e]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-46) /* -0x2e */);
    // 00422463  e8584f0900             -call 0x4b73c0
    cpu.esp -= 4;
    sub_4b73c0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00422468:
    // 00422468  8d552a                 -lea edx, [ebp + 0x2a]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(42) /* 0x2a */);
    // 0042246b  8b457a                 -mov eax, dword ptr [ebp + 0x7a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(122) /* 0x7a */);
    // 0042246e  e84d4f0900             -call 0x4b73c0
    cpu.esp -= 4;
    sub_4b73c0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00422473  8d552a                 -lea edx, [ebp + 0x2a]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(42) /* 0x2a */);
    // 00422476  8d453a                 -lea eax, [ebp + 0x3a]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(58) /* 0x3a */);
    // 00422479  e8824e0900             -call 0x4b7300
    cpu.esp -= 4;
    sub_4b7300(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042247e  8d451a                 -lea eax, [ebp + 0x1a]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(26) /* 0x1a */);
    // 00422481  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00422482  8d552a                 -lea edx, [ebp + 0x2a]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(42) /* 0x2a */);
    // 00422485  8d453a                 -lea eax, [ebp + 0x3a]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(58) /* 0x3a */);
    // 00422488  ff757e                 -push dword ptr [ebp + 0x7e]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */);
    cpu.esp -= 4;
    // 0042248b  e8504d0900             -call 0x4b71e0
    cpu.esp -= 4;
    sub_4b71e0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00422490  8b557a                 -mov edx, dword ptr [ebp + 0x7a]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(122) /* 0x7a */);
    // 00422493  8d451a                 -lea eax, [ebp + 0x1a]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(26) /* 0x1a */);
    // 00422496  e8f5500900             -call 0x4b7590
    cpu.esp -= 4;
    sub_4b7590(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042249b  8b4572                 -mov eax, dword ptr [ebp + 0x72]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(114) /* 0x72 */);
    // 0042249e  8b801c010000           -mov eax, dword ptr [eax + 0x11c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(284) /* 0x11c */);
    // 004224a4  c1e302                 -shl ebx, 2
    cpu.ebx <<= 2 /*0x2*/ % 32;
    // 004224a7  8b5572                 -mov edx, dword ptr [ebp + 0x72]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(114) /* 0x72 */);
    // 004224aa  8b9cc3c82e5500         -mov ebx, dword ptr [ebx + eax*8 + 0x552ec8]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(5582536) /* 0x552ec8 */ + cpu.eax * 8);
    // 004224b1  8d4d62                 -lea ecx, [ebp + 0x62]
    cpu.ecx = x86::reg32(cpu.ebp + x86::reg32(98) /* 0x62 */);
    // 004224b4  81c230010000           -add edx, 0x130
    (cpu.edx) += x86::reg32(x86::sreg32(304 /*0x130*/));
    // 004224ba  8b5b04                 -mov ebx, dword ptr [ebx + 4]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(4) /* 0x4 */);
    // 004224bd  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 004224c2  81c398000000           -add ebx, 0x98
    (cpu.ebx) += x86::reg32(x86::sreg32(152 /*0x98*/));
    // 004224c8  e8e3da0b00             -call 0x4dffb0
    cpu.esp -= 4;
    sub_4dffb0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004224cd  8d454a                 -lea eax, [ebp + 0x4a]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(74) /* 0x4a */);
    // 004224d0  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004224d1  8d5562                 -lea edx, [ebp + 0x62]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(98) /* 0x62 */);
    // 004224d4  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 004224d9  ff756e                 -push dword ptr [ebp + 0x6e]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(110) /* 0x6e */);
    cpu.esp -= 4;
    // 004224dc  e86fdb0b00             -call 0x4e0050
    cpu.esp -= 4;
    sub_4e0050(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004224e1  8d4556                 -lea eax, [ebp + 0x56]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(86) /* 0x56 */);
    // 004224e4  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004224e5  8b4d76                 -mov ecx, dword ptr [ebp + 0x76]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(118) /* 0x76 */);
    // 004224e8  8b5576                 -mov edx, dword ptr [ebp + 0x76]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(118) /* 0x76 */);
    // 004224eb  ff757e                 -push dword ptr [ebp + 0x7e]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */);
    cpu.esp -= 4;
    // 004224ee  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 004224f3  8d5d56                 -lea ebx, [ebp + 0x56]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(86) /* 0x56 */);
    // 004224f6  e855db0b00             -call 0x4e0050
    cpu.esp -= 4;
    sub_4e0050(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004224fb  8d554a                 -lea edx, [ebp + 0x4a]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(74) /* 0x4a */);
    // 004224fe  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 00422503  e8a8da0b00             -call 0x4dffb0
    cpu.esp -= 4;
    sub_4dffb0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00422508:
    // 00422508  8da582000000           -lea esp, [ebp + 0x82]
    cpu.esp = x86::reg32(cpu.ebp + x86::reg32(130) /* 0x82 */);
    // 0042250e  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042250f  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00422510  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00422511  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x8b 0xc0 */
void Application::sub_422520(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00422520  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00422521  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00422522  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00422523  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00422525  83ec08                 -sub esp, 8
    (cpu.esp) -= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 00422528  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 0042252b  8955f8                 -mov dword ptr [ebp - 8], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.edx;
    // 0042252e  83b80401000000         +cmp dword ptr [eax + 0x104], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(260) /* 0x104 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00422535  7405                   -je 0x42253c
    if (cpu.flags.zf)
    {
        goto L_0x0042253c;
    }
    // 00422537  e8f4f1ffff             -call 0x421730
    cpu.esp -= 4;
    sub_421730(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x0042253c:
    // 0042253c  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 0042253f  89df                   -mov edi, ebx
    cpu.edi = cpu.ebx;
    // 00422541  8d7014                 -lea esi, [eax + 0x14]
    cpu.esi = x86::reg32(cpu.eax + x86::reg32(20) /* 0x14 */);
    // 00422544  89da                   -mov edx, ebx
    cpu.edx = cpu.ebx;
    // 00422546  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00422547  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00422548  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00422549  e832f3ffff             -call 0x421880
    cpu.esp -= 4;
    sub_421880(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042254e  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00422551  83b8f400000000         +cmp dword ptr [eax + 0xf4], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(244) /* 0xf4 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00422558  744a                   -je 0x4225a4
    if (cpu.flags.zf)
    {
        goto L_0x004225a4;
    }
    // 0042255a  89da                   -mov edx, ebx
    cpu.edx = cpu.ebx;
    // 0042255c  e81ff9ffff             -call 0x421e80
    cpu.esp -= 4;
    sub_421e80(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00422561  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00422564  89da                   -mov edx, ebx
    cpu.edx = cpu.ebx;
    // 00422566  e825faffff             -call 0x421f90
    cpu.esp -= 4;
    sub_421f90(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042256b  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 0042256e  8b4004                 -mov eax, dword ptr [eax + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 00422571  8bb8a0000000           -mov edi, dword ptr [eax + 0xa0]
    cpu.edi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(160) /* 0xa0 */);
    // 00422577  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00422578  8b909c000000           -mov edx, dword ptr [eax + 0x9c]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(156) /* 0x9c */);
    // 0042257e  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 0042257f  8bb098000000           -mov esi, dword ptr [eax + 0x98]
    cpu.esi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(152) /* 0x98 */);
    // 00422585  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00422586  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00422589  89da                   -mov edx, ebx
    cpu.edx = cpu.ebx;
    // 0042258b  e830f7ffff             -call 0x421cc0
    cpu.esp -= 4;
    sub_421cc0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00422590  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00422593  89da                   -mov edx, ebx
    cpu.edx = cpu.ebx;
    // 00422595  e8f6f5ffff             -call 0x421b90
    cpu.esp -= 4;
    sub_421b90(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042259a  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 0042259d  89da                   -mov edx, ebx
    cpu.edx = cpu.ebx;
    // 0042259f  e8fcfaffff             -call 0x4220a0
    cpu.esp -= 4;
    sub_4220a0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x004225a4:
    // 004225a4  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004225a7  83b8f800000000         +cmp dword ptr [eax + 0xf8], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(248) /* 0xf8 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004225ae  7407                   -je 0x4225b7
    if (cpu.flags.zf)
    {
        goto L_0x004225b7;
    }
    // 004225b0  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 004225b2  e849f3ffff             -call 0x421900
    cpu.esp -= 4;
    sub_421900(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x004225b7:
    // 004225b7  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004225ba  83b80801000000         +cmp dword ptr [eax + 0x108], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(264) /* 0x108 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004225c1  7407                   -je 0x4225ca
    if (cpu.flags.zf)
    {
        goto L_0x004225ca;
    }
    // 004225c3  89da                   -mov edx, ebx
    cpu.edx = cpu.ebx;
    // 004225c5  e8c6fcffff             -call 0x422290
    cpu.esp -= 4;
    sub_422290(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x004225ca:
    // 004225ca  83f901                 +cmp ecx, 1
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1 /*0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004225cd  7515                   -jne 0x4225e4
    if (!cpu.flags.zf)
    {
        goto L_0x004225e4;
    }
    // 004225cf  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004225d2  8b4004                 -mov eax, dword ptr [eax + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 004225d5  8b55f8                 -mov edx, dword ptr [ebp - 8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004225d8  05c0000000             +add eax, 0xc0
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
    // 004225dd  e88eefffff             -call 0x421570
    cpu.esp -= 4;
    sub_421570(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004225e2  eb10                   -jmp 0x4225f4
    goto L_0x004225f4;
L_0x004225e4:
    // 004225e4  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004225e7  b909000000             -mov ecx, 9
    cpu.ecx = 9 /*0x9*/;
    // 004225ec  8b7df8                 -mov edi, dword ptr [ebp - 8]
    cpu.edi = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004225ef  8d702c                 -lea esi, [eax + 0x2c]
    cpu.esi = x86::reg32(cpu.eax + x86::reg32(44) /* 0x2c */);
    // 004225f2  f3a5                   -rep movsd dword ptr es:[edi], dword ptr [esi]
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
L_0x004225f4:
    // 004225f4  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004225f7  89da                   -mov edx, ebx
    cpu.edx = cpu.ebx;
    // 004225f9  e882f2ffff             -call 0x421880
    cpu.esp -= 4;
    sub_421880(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004225fe  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00422600  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00422601  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00422602  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00422603  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 */
void Application::sub_422610(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00422610  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00422611  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00422612  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00422613  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00422614  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00422615  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00422617  83ec60                 -sub esp, 0x60
    (cpu.esp) -= x86::reg32(x86::sreg32(96 /*0x60*/));
    // 0042261a  89c7                   -mov edi, eax
    cpu.edi = cpu.eax;
    // 0042261c  89d6                   -mov esi, edx
    cpu.esi = cpu.edx;
    // 0042261e  8d049500000000         -lea eax, [edx*4]
    cpu.eax = x86::reg32(cpu.edx * 4);
    // 00422625  8b90602f5500           -mov edx, dword ptr [eax + 0x552f60]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(5582688) /* 0x552f60 */);
    // 0042262b  8955f8                 -mov dword ptr [ebp - 8], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.edx;
    // 0042262e  8b90b0105e00           -mov edx, dword ptr [eax + 0x5e10b0]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164656) /* 0x5e10b0 */);
    // 00422634  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 00422636  7404                   -je 0x42263c
    if (cpu.flags.zf)
    {
        goto L_0x0042263c;
    }
    // 00422638  8b02                   -mov eax, dword ptr [edx]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edx);
    // 0042263a  eb02                   -jmp 0x42263e
    goto L_0x0042263e;
L_0x0042263c:
    // 0042263c  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
L_0x0042263e:
    // 0042263e  8b0db0d36f00           -mov ecx, dword ptr [0x6fd3b0]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(7328688) /* 0x6fd3b0 */);
    // 00422644  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 00422647  83f901                 +cmp ecx, 1
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1 /*0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0042264a  7504                   -jne 0x422650
    if (!cpu.flags.zf)
    {
        goto L_0x00422650;
    }
    // 0042264c  89f3                   -mov ebx, esi
    cpu.ebx = cpu.esi;
    // 0042264e  eb06                   -jmp 0x422656
    goto L_0x00422656;
L_0x00422650:
    // 00422650  8b1df4d46f00           -mov ebx, dword ptr [0x6fd4f4]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(7329012) /* 0x6fd4f4 */);
L_0x00422656:
    // 00422656  8b55fc                 -mov edx, dword ptr [ebp - 4]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00422659  8d04b500000000         -lea eax, [esi*4]
    cpu.eax = x86::reg32(cpu.esi * 4);
    // 00422660  8b94d0c82e5500         -mov edx, dword ptr [eax + edx*8 + 0x552ec8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(5582536) /* 0x552ec8 */ + cpu.edx * 8);
    // 00422667  807c3a5800             +cmp byte ptr [edx + edi + 0x58], 0
    {
        x86::reg8 tmp1 = app->getMemory<x86::reg8>(cpu.edx + x86::reg32(88) /* 0x58 */ + cpu.edi * 1);
        x86::reg8 tmp2 = x86::reg8(x86::sreg8(0 /*0x0*/));
        x86::reg8 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 7);
        cpu.flags.of ^= 1 & (result >> 7);
        cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
        cpu.set_szp(result);
    }
    // 0042266c  750e                   -jne 0x42267c
    if (!cpu.flags.zf)
    {
        goto L_0x0042267c;
    }
    // 0042266e  89fa                   -mov edx, edi
    cpu.edx = cpu.edi;
    // 00422670  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 00422672  e839120000             -call 0x4238b0
    cpu.esp -= 4;
    sub_4238b0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00422677  e956010000             -jmp 0x4227d2
    goto L_0x004227d2;
L_0x0042267c:
    // 0042267c  8b94f8c82e5500         -mov edx, dword ptr [eax + edi*8 + 0x552ec8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(5582536) /* 0x552ec8 */ + cpu.edi * 8);
    // 00422683  8b80b0105e00           -mov eax, dword ptr [eax + 0x5e10b0]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164656) /* 0x5e10b0 */);
    // 00422689  8b4804                 -mov ecx, dword ptr [eax + 4]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 0042268c  3b4a04                 +cmp ecx, dword ptr [edx + 4]
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.edx + x86::reg32(4) /* 0x4 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0042268f  7411                   -je 0x4226a2
    if (cpu.flags.zf)
    {
        goto L_0x004226a2;
    }
    // 00422691  89fa                   -mov edx, edi
    cpu.edx = cpu.edi;
    // 00422693  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 00422695  e816120000             -call 0x4238b0
    cpu.esp -= 4;
    sub_4238b0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042269a  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 0042269c  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042269d  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042269e  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042269f  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004226a0  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004226a1  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004226a2:
    // 004226a2  8b4808                 -mov ecx, dword ptr [eax + 8]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 004226a5  3b4a08                 +cmp ecx, dword ptr [edx + 8]
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.edx + x86::reg32(8) /* 0x8 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004226a8  7411                   -je 0x4226bb
    if (cpu.flags.zf)
    {
        goto L_0x004226bb;
    }
    // 004226aa  89fa                   -mov edx, edi
    cpu.edx = cpu.edi;
    // 004226ac  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004226ae  e8fd110000             -call 0x4238b0
    cpu.esp -= 4;
    sub_4238b0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004226b3  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004226b5  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004226b6  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004226b7  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004226b8  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004226b9  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004226ba  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004226bb:
    // 004226bb  3b0c9dc8fa5e00         +cmp ecx, dword ptr [ebx*4 + 0x5efac8]
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(6224584) /* 0x5efac8 */ + cpu.ebx * 4)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004226c2  7411                   -je 0x4226d5
    if (cpu.flags.zf)
    {
        goto L_0x004226d5;
    }
    // 004226c4  89fa                   -mov edx, edi
    cpu.edx = cpu.edi;
    // 004226c6  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004226c8  e8e3110000             -call 0x4238b0
    cpu.esp -= 4;
    sub_4238b0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004226cd  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004226cf  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004226d0  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004226d1  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004226d2  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004226d3  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004226d4  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004226d5:
    // 004226d5  8b4dfc                 -mov ecx, dword ptr [ebp - 4]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004226d8  83f913                 +cmp ecx, 0x13
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(19 /*0x13*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004226db  7511                   -jne 0x4226ee
    if (!cpu.flags.zf)
    {
        goto L_0x004226ee;
    }
    // 004226dd  89fa                   -mov edx, edi
    cpu.edx = cpu.edi;
    // 004226df  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004226e1  e8ca110000             -call 0x4238b0
    cpu.esp -= 4;
    sub_4238b0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004226e6  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004226e8  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004226e9  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004226ea  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004226eb  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004226ec  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004226ed  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004226ee:
    // 004226ee  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004226f1  89b81c010000           -mov dword ptr [eax + 0x11c], edi
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(284) /* 0x11c */) = cpu.edi;
    // 004226f7  83f910                 +cmp ecx, 0x10
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
    // 004226fa  740e                   -je 0x42270a
    if (cpu.flags.zf)
    {
        goto L_0x0042270a;
    }
    // 004226fc  83f918                 +cmp ecx, 0x18
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(24 /*0x18*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004226ff  7409                   -je 0x42270a
    if (cpu.flags.zf)
    {
        goto L_0x0042270a;
    }
    // 00422701  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 00422703  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00422705  e8463d0000             -call 0x426450
    cpu.esp -= 4;
    sub_426450(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x0042270a:
    // 0042270a  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 0042270d  8d5dd4                 -lea ebx, [ebp - 0x2c]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-44) /* -0x2c */);
    // 00422710  8d14b500000000         -lea edx, [esi*4]
    cpu.edx = x86::reg32(cpu.esi * 4);
    // 00422717  c1e003                 -shl eax, 3
    cpu.eax <<= 3 /*0x3*/ % 32;
    // 0042271a  8955ec                 -mov dword ptr [ebp - 0x14], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */) = cpu.edx;
    // 0042271d  01c2                   -add edx, eax
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.eax));
    // 0042271f  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 00422721  8955f0                 -mov dword ptr [ebp - 0x10], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = cpu.edx;
    // 00422724  8b82c82e5500           -mov eax, dword ptr [edx + 0x552ec8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(5582536) /* 0x552ec8 */);
    // 0042272a  8d55a0                 -lea edx, [ebp - 0x60]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-96) /* -0x60 */);
    // 0042272d  e8eefdffff             -call 0x422520
    cpu.esp -= 4;
    sub_422520(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00422732  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 00422735  0520010000             -add eax, 0x120
    (cpu.eax) += x86::reg32(x86::sreg32(288 /*0x120*/));
    // 0042273a  8945f4                 -mov dword ptr [ebp - 0xc], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.eax;
    // 0042273d  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 0042273f  8d45a0                 -lea eax, [ebp - 0x60]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-96) /* -0x60 */);
    // 00422742  e8794c0900             -call 0x4b73c0
    cpu.esp -= 4;
    sub_4b73c0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00422747  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 00422749  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 0042274b  e8003d0000             -call 0x426450
    cpu.esp -= 4;
    sub_426450(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00422750  8b55ec                 -mov edx, dword ptr [ebp - 0x14]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */);
    // 00422753  8d04fd00000000         -lea eax, [edi*8]
    cpu.eax = x86::reg32(cpu.edi * 8);
    // 0042275a  8d5de0                 -lea ebx, [ebp - 0x20]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-32) /* -0x20 */);
    // 0042275d  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 0042275f  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 00422761  8d55a0                 -lea edx, [ebp - 0x60]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-96) /* -0x60 */);
    // 00422764  8b80c82e5500           -mov eax, dword ptr [eax + 0x552ec8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(5582536) /* 0x552ec8 */);
    // 0042276a  e8b1fdffff             -call 0x422520
    cpu.esp -= 4;
    sub_422520(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042276f  8b45f0                 -mov eax, dword ptr [ebp - 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 00422772  8b80c82e5500           -mov eax, dword ptr [eax + 0x552ec8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(5582536) /* 0x552ec8 */);
    // 00422778  8b4df8                 -mov ecx, dword ptr [ebp - 8]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 0042277b  8b4004                 -mov eax, dword ptr [eax + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 0042277e  8d55d4                 -lea edx, [ebp - 0x2c]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-44) /* -0x2c */);
    // 00422781  8d9898000000           -lea ebx, [eax + 0x98]
    cpu.ebx = x86::reg32(cpu.eax + x86::reg32(152) /* 0x98 */);
    // 00422787  81c130010000           -add ecx, 0x130
    (cpu.ecx) += x86::reg32(x86::sreg32(304 /*0x130*/));
    // 0042278d  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 00422792  e869d80b00             -call 0x4e0000
    cpu.esp -= 4;
    sub_4e0000(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00422797  8d55c4                 -lea edx, [ebp - 0x3c]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-60) /* -0x3c */);
    // 0042279a  8d45a0                 -lea eax, [ebp - 0x60]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-96) /* -0x60 */);
    // 0042279d  e81e4c0900             -call 0x4b73c0
    cpu.esp -= 4;
    sub_4b73c0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004227a2  8b55f4                 -mov edx, dword ptr [ebp - 0xc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 004227a5  8d45c4                 -lea eax, [ebp - 0x3c]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-60) /* -0x3c */);
    // 004227a8  e8534b0900             -call 0x4b7300
    cpu.esp -= 4;
    sub_4b7300(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004227ad  ba13000000             -mov edx, 0x13
    cpu.edx = 19 /*0x13*/;
    // 004227b2  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004227b4  e8f7100000             -call 0x4238b0
    cpu.esp -= 4;
    sub_4238b0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004227b9  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004227bc  8b55f8                 -mov edx, dword ptr [ebp - 8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004227bf  c7801001000000000000   -mov dword ptr [eax + 0x110], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(272) /* 0x110 */) = 0 /*0x0*/;
    // 004227c9  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004227cc  898218010000           -mov dword ptr [edx + 0x118], eax
    app->getMemory<x86::reg32>(cpu.edx + x86::reg32(280) /* 0x118 */) = cpu.eax;
L_0x004227d2:
    // 004227d2  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004227d4  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004227d5  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004227d6  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004227d7  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004227d8  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004227d9  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 */
void Application::sub_4227e0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004227e0  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004227e1  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004227e2  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004227e3  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004227e4  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004227e6  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 004227e9  833800                 +cmp dword ptr [eax], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004227ec  7545                   -jne 0x422833
    if (!cpu.flags.zf)
    {
        goto L_0x00422833;
    }
    // 004227ee  8b5004                 -mov edx, dword ptr [eax + 4]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 004227f1  c1e202                 -shl edx, 2
    cpu.edx <<= 2 /*0x2*/ % 32;
    // 004227f4  8b8ab8105e00           -mov ecx, dword ptr [edx + 0x5e10b8]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(6164664) /* 0x5e10b8 */);
    // 004227fa  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    // 004227fc  7404                   -je 0x422802
    if (cpu.flags.zf)
    {
        goto L_0x00422802;
    }
    // 004227fe  89ca                   -mov edx, ecx
    cpu.edx = cpu.ecx;
    // 00422800  eb06                   -jmp 0x422808
    goto L_0x00422808;
L_0x00422802:
    // 00422802  8b92b0105e00           -mov edx, dword ptr [edx + 0x5e10b0]
    cpu.edx = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(6164656) /* 0x5e10b0 */);
L_0x00422808:
    // 00422808  f74254ffffff7f         +test dword ptr [edx + 0x54], 0x7fffffff
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(app->getMemory<x86::reg32>(cpu.edx + x86::reg32(84) /* 0x54 */) & 2147483647 /*0x7fffffff*/));
    // 0042280f  7422                   -je 0x422833
    if (cpu.flags.zf)
    {
        goto L_0x00422833;
    }
    // 00422811  8b4004                 -mov eax, dword ptr [eax + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 00422814  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 00422817  8bb0b8105e00           -mov esi, dword ptr [eax + 0x5e10b8]
    cpu.esi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164664) /* 0x5e10b8 */);
    // 0042281d  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 0042281f  7404                   -je 0x422825
    if (cpu.flags.zf)
    {
        goto L_0x00422825;
    }
    // 00422821  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 00422823  eb06                   -jmp 0x42282b
    goto L_0x0042282b;
L_0x00422825:
    // 00422825  8b80b0105e00           -mov eax, dword ptr [eax + 0x5e10b0]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164656) /* 0x5e10b0 */);
L_0x0042282b:
    // 0042282b  8b4054                 -mov eax, dword ptr [eax + 0x54]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(84) /* 0x54 */);
    // 0042282e  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 00422831  eb07                   -jmp 0x42283a
    goto L_0x0042283a;
L_0x00422833:
    // 00422833  c745fc0000803f         -mov dword ptr [ebp - 4], 0x3f800000
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = 1065353216 /*0x3f800000*/;
L_0x0042283a:
    // 0042283a  d945fc                 -fld dword ptr [ebp - 4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */));
    // 0042283d  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 0042283f  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00422840  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00422841  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00422842  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    cpu.fpu.count += 1;
    cpu.fpu.st(0) = fpu1;
    }
    // 00422843  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 */
void Application::sub_422850(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00422850  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00422851  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00422852  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00422853  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00422854  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00422855  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00422857  83ec0c                 -sub esp, 0xc
    (cpu.esp) -= x86::reg32(x86::sreg32(12 /*0xc*/));
    // 0042285a  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 0042285c  8d703c                 -lea esi, [eax + 0x3c]
    cpu.esi = x86::reg32(cpu.eax + x86::reg32(60) /* 0x3c */);
    // 0042285f  83c00c                 -add eax, 0xc
    (cpu.eax) += x86::reg32(x86::sreg32(12 /*0xc*/));
    // 00422862  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 00422864  8d5930                 -lea ebx, [ecx + 0x30]
    cpu.ebx = x86::reg32(cpu.ecx + x86::reg32(48) /* 0x30 */);
    // 00422867  e8a4d80b00             -call 0x4e0110
    cpu.esp -= 4;
    sub_4e0110(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042286c  d901                   -fld dword ptr [ecx]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.ecx));
    // 0042286e  8d45f4                 -lea eax, [ebp - 0xc]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 00422871  d9e0                   -fchs 
    x86::Float fpu2 = -fpu1;
    // 00422873  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 00422875  d95df4                 -fstp dword ptr [ebp - 0xc]
    app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */) = float(fpu2);
    // 00422878  d94104                 -fld dword ptr [ecx + 4]
    x86::Float fpu3 = x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(4) /* 0x4 */));
    // 0042287b  d9e0                   -fchs 
    x86::Float fpu4 = -fpu3;
    // 0042287d  d95df8                 -fstp dword ptr [ebp - 8]
    app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = float(fpu4);
    // 00422880  d94108                 -fld dword ptr [ecx + 8]
    x86::Float fpu5 = x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(8) /* 0x8 */));
    // 00422883  d9e0                   -fchs 
    x86::Float fpu6 = -fpu5;
    // 00422885  d95dfc                 -fstp dword ptr [ebp - 4]
    app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = float(fpu6);
    // 00422888  d900                   -fld dword ptr [eax]
    x86::Float fpu7 = x86::Float(app->getMemory<float>(cpu.eax));
    // 0042288a  d80a                   -fmul dword ptr [edx]
    x86::Float fpu8 = cpu.fpu.mul(fpu7, x86::Float(app->getMemory<float>(cpu.edx)));
    // 0042288c  d900                   -fld dword ptr [eax]
    x86::Float fpu9 = x86::Float(app->getMemory<float>(cpu.eax));
    // 0042288e  d84a04                 -fmul dword ptr [edx + 4]
    x86::Float fpu10 = cpu.fpu.mul(fpu9, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(4) /* 0x4 */)));
    // 00422891  d900                   -fld dword ptr [eax]
    x86::Float fpu11 = x86::Float(app->getMemory<float>(cpu.eax));
    // 00422893  d84a08                 -fmul dword ptr [edx + 8]
    x86::Float fpu12 = cpu.fpu.mul(fpu11, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(8) /* 0x8 */)));
    // 00422896  d9ca                   -fxch st(2)
    
    // 00422898  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu13 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 0042289b  d84a0c                 -fmul dword ptr [edx + 0xc]
    x86::Float fpu14 = cpu.fpu.mul(fpu13, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(12) /* 0xc */)));
    // 0042289e  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu15 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 004228a1  d84a10                 -fmul dword ptr [edx + 0x10]
    x86::Float fpu16 = cpu.fpu.mul(fpu15, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(16) /* 0x10 */)));
    // 004228a4  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu17 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 004228a7  d84a14                 -fmul dword ptr [edx + 0x14]
    x86::Float fpu18 = cpu.fpu.mul(fpu17, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(20) /* 0x14 */)));
    // 004228aa  d9ca                   -fxch st(2)
    
    // 004228ac  dec3                   -faddp st(3)
    x86::Float fpu19 = cpu.fpu.add(fpu8, fpu14);
    // 004228ae  dec3                   -faddp st(3)
    x86::Float fpu20 = cpu.fpu.add(fpu10, fpu16);
    // 004228b0  dec3                   -faddp st(3)
    x86::Float fpu21 = cpu.fpu.add(fpu12, fpu18);
    // 004228b2  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu22 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 004228b5  d84a18                 -fmul dword ptr [edx + 0x18]
    x86::Float fpu23 = cpu.fpu.mul(fpu22, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(24) /* 0x18 */)));
    // 004228b8  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu24 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 004228bb  d84a1c                 -fmul dword ptr [edx + 0x1c]
    x86::Float fpu25 = cpu.fpu.mul(fpu24, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(28) /* 0x1c */)));
    // 004228be  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu26 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 004228c1  d84a20                 -fmul dword ptr [edx + 0x20]
    x86::Float fpu27 = cpu.fpu.mul(fpu26, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(32) /* 0x20 */)));
    // 004228c4  d9ca                   -fxch st(2)
    
    // 004228c6  dec3                   -faddp st(3)
    x86::Float fpu28 = cpu.fpu.add(fpu19, fpu23);
    // 004228c8  dec3                   -faddp st(3)
    x86::Float fpu29 = cpu.fpu.add(fpu20, fpu25);
    // 004228ca  dec3                   -faddp st(3)
    x86::Float fpu30 = cpu.fpu.add(fpu21, fpu27);
    // 004228cc  8d400c                 -lea eax, [eax + 0xc]
    cpu.eax = x86::reg32(cpu.eax + x86::reg32(12) /* 0xc */);
    // 004228cf  d91b                   -fstp dword ptr [ebx]
    app->getMemory<float>(cpu.ebx) = float(fpu28);
    // 004228d1  d95b04                 -fstp dword ptr [ebx + 4]
    app->getMemory<float>(cpu.ebx + x86::reg32(4) /* 0x4 */) = float(fpu29);
    // 004228d4  d95b08                 -fstp dword ptr [ebx + 8]
    app->getMemory<float>(cpu.ebx + x86::reg32(8) /* 0x8 */) = float(fpu30);
    // 004228d7  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004228d9  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004228da  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004228db  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004228dc  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004228dd  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    }
    // 004228de  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x90 */
void Application::sub_4228e0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004228e0  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004228e1  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004228e2  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004228e3  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004228e4  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004228e6  83ec0c                 -sub esp, 0xc
    (cpu.esp) -= x86::reg32(x86::sreg32(12 /*0xc*/));
    // 004228e9  89c7                   -mov edi, eax
    cpu.edi = cpu.eax;
    // 004228eb  89d6                   -mov esi, edx
    cpu.esi = cpu.edx;
    // 004228ed  895dfc                 -mov dword ptr [ebp - 4], ebx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.ebx;
    // 004228f0  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 004228f2  8b0db0d36f00           -mov ecx, dword ptr [0x6fd3b0]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(7328688) /* 0x6fd3b0 */);
    // 004228f8  8955f8                 -mov dword ptr [ebp - 8], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.edx;
    // 004228fb  83f901                 +cmp ecx, 1
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1 /*0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004228fe  7504                   -jne 0x422904
    if (!cpu.flags.zf)
    {
        goto L_0x00422904;
    }
    // 00422900  21cf                   +and edi, ecx
    cpu.clear_co();
    cpu.set_szp((cpu.edi &= x86::reg32(x86::sreg32(cpu.ecx))));
    // 00422902  eb02                   -jmp 0x422906
    goto L_0x00422906;
L_0x00422904:
    // 00422904  31c7                   -xor edi, eax
    cpu.edi ^= x86::reg32(x86::sreg32(cpu.eax));
L_0x00422906:
    // 00422906  8d04bd00000000         -lea eax, [edi*4]
    cpu.eax = x86::reg32(cpu.edi * 4);
    // 0042290d  8b98b0105e00           -mov ebx, dword ptr [eax + 0x5e10b0]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164656) /* 0x5e10b0 */);
    // 00422913  85db                   +test ebx, ebx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & cpu.ebx));
    // 00422915  742c                   -je 0x422943
    if (cpu.flags.zf)
    {
        goto L_0x00422943;
    }
    // 00422917  89d9                   -mov ecx, ebx
    cpu.ecx = cpu.ebx;
    // 00422919  8b13                   -mov edx, dword ptr [ebx]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebx);
    // 0042291b  83fa13                 +cmp edx, 0x13
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(19 /*0x13*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0042291e  7523                   -jne 0x422943
    if (!cpu.flags.zf)
    {
        goto L_0x00422943;
    }
    // 00422920  c745f801000000         -mov dword ptr [ebp - 8], 1
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = 1 /*0x1*/;
    // 00422927  8b90602f5500           -mov edx, dword ptr [eax + 0x552f60]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(5582688) /* 0x552f60 */);
    // 0042292d  8b921c010000           -mov edx, dword ptr [edx + 0x11c]
    cpu.edx = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(284) /* 0x11c */);
    // 00422933  8b94d0c82e5500         -mov edx, dword ptr [eax + edx*8 + 0x552ec8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(5582536) /* 0x552ec8 */ + cpu.edx * 8);
    // 0042293a  895df4                 -mov dword ptr [ebp - 0xc], ebx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.ebx;
    // 0042293d  8990b0105e00           -mov dword ptr [eax + 0x5e10b0], edx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164656) /* 0x5e10b0 */) = cpu.edx;
L_0x00422943:
    // 00422943  8b4dfc                 -mov ecx, dword ptr [ebp - 4]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00422946  8d04bd00000000         -lea eax, [edi*4]
    cpu.eax = x86::reg32(cpu.edi * 4);
    // 0042294d  89f3                   -mov ebx, esi
    cpu.ebx = cpu.esi;
    // 0042294f  8d560c                 -lea edx, [esi + 0xc]
    cpu.edx = x86::reg32(cpu.esi + x86::reg32(12) /* 0xc */);
    // 00422952  83b8b8105e0000         +cmp dword ptr [eax + 0x5e10b8], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164664) /* 0x5e10b8 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00422959  7408                   -je 0x422963
    if (cpu.flags.zf)
    {
        goto L_0x00422963;
    }
    // 0042295b  8b80b8105e00           -mov eax, dword ptr [eax + 0x5e10b8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164664) /* 0x5e10b8 */);
    // 00422961  eb06                   -jmp 0x422969
    goto L_0x00422969;
L_0x00422963:
    // 00422963  8b80b0105e00           -mov eax, dword ptr [eax + 0x5e10b0]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164656) /* 0x5e10b0 */);
L_0x00422969:
    // 00422969  e8b2fbffff             -call 0x422520
    cpu.esp -= 4;
    sub_422520(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042296e  837df800               +cmp dword ptr [ebp - 8], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00422972  7419                   -je 0x42298d
    if (cpu.flags.zf)
    {
        goto L_0x0042298d;
    }
    // 00422974  8b4dfc                 -mov ecx, dword ptr [ebp - 4]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00422977  8d460c                 -lea eax, [esi + 0xc]
    cpu.eax = x86::reg32(cpu.esi + x86::reg32(12) /* 0xc */);
    // 0042297a  89fb                   -mov ebx, edi
    cpu.ebx = cpu.edi;
    // 0042297c  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 0042297e  e83dfaffff             -call 0x4223c0
    cpu.esp -= 4;
    sub_4223c0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00422983  8b55f4                 -mov edx, dword ptr [ebp - 0xc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 00422986  8914bdb0105e00         -mov dword ptr [edi*4 + 0x5e10b0], edx
    app->getMemory<x86::reg32>(x86::reg32(6164656) /* 0x5e10b0 */ + cpu.edi * 4) = cpu.edx;
L_0x0042298d:
    // 0042298d  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 0042298f  8b5dfc                 -mov ebx, dword ptr [ebp - 4]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00422992  e8b9feffff             -call 0x422850
    cpu.esp -= 4;
    sub_422850(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00422997  85db                   +test ebx, ebx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & cpu.ebx));
    // 00422999  7519                   -jne 0x4229b4
    if (!cpu.flags.zf)
    {
        goto L_0x004229b4;
    }
    // 0042299b  8d04bd00000000         -lea eax, [edi*4]
    cpu.eax = x86::reg32(cpu.edi * 4);
    // 004229a2  29f8                   -sub eax, edi
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edi));
    // 004229a4  c1e005                 -shl eax, 5
    cpu.eax <<= 5 /*0x5*/ % 32;
    // 004229a7  b918000000             -mov ecx, 0x18
    cpu.ecx = 24 /*0x18*/;
    // 004229ac  8db850d95d00           -lea edi, [eax + 0x5dd950]
    cpu.edi = x86::reg32(cpu.eax + x86::reg32(6150480) /* 0x5dd950 */);
    // 004229b2  f3a5                   -rep movsd dword ptr es:[edi], dword ptr [esi]
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
L_0x004229b4:
    // 004229b4  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004229b6  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004229b7  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004229b8  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004229b9  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004229ba  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x40 0x00 0x8b 0xc9 */
void Application::sub_4229c0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004229c0  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004229c1  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004229c2  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004229c3  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004229c4  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004229c6  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 004229c9  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 004229cc  8b0db0d36f00           -mov ecx, dword ptr [0x6fd3b0]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(7328688) /* 0x6fd3b0 */);
    // 004229d2  83f901                 +cmp ecx, 1
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1 /*0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004229d5  7509                   -jne 0x4229e0
    if (!cpu.flags.zf)
    {
        goto L_0x004229e0;
    }
    // 004229d7  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 004229d9  21cb                   +and ebx, ecx
    cpu.clear_co();
    cpu.set_szp((cpu.ebx &= x86::reg32(x86::sreg32(cpu.ecx))));
    // 004229db  895dfc                 -mov dword ptr [ebp - 4], ebx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.ebx;
    // 004229de  eb05                   -jmp 0x4229e5
    goto L_0x004229e5;
L_0x004229e0:
    // 004229e0  31f6                   -xor esi, esi
    cpu.esi ^= x86::reg32(x86::sreg32(cpu.esi));
    // 004229e2  8975fc                 -mov dword ptr [ebp - 4], esi
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.esi;
L_0x004229e5:
    // 004229e5  8b5dfc                 -mov ebx, dword ptr [ebp - 4]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004229e8  8d049d00000000         -lea eax, [ebx*4]
    cpu.eax = x86::reg32(cpu.ebx * 4);
    // 004229ef  29d8                   -sub eax, ebx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.ebx));
    // 004229f1  b918000000             -mov ecx, 0x18
    cpu.ecx = 24 /*0x18*/;
    // 004229f6  c1e005                 -shl eax, 5
    cpu.eax <<= 5 /*0x5*/ % 32;
    // 004229f9  89d7                   -mov edi, edx
    cpu.edi = cpu.edx;
    // 004229fb  8db050d95d00           -lea esi, [eax + 0x5dd950]
    cpu.esi = x86::reg32(cpu.eax + x86::reg32(6150480) /* 0x5dd950 */);
    // 00422a01  8d049d00000000         -lea eax, [ebx*4]
    cpu.eax = x86::reg32(cpu.ebx * 4);
    // 00422a08  f3a5                   -rep movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00422a0a  8bb8b8105e00           -mov edi, dword ptr [eax + 0x5e10b8]
    cpu.edi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164664) /* 0x5e10b8 */);
    // 00422a10  85ff                   +test edi, edi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edi & cpu.edi));
    // 00422a12  740a                   -je 0x422a1e
    if (cpu.flags.zf)
    {
        goto L_0x00422a1e;
    }
    // 00422a14  7404                   -je 0x422a1a
    if (cpu.flags.zf)
    {
        goto L_0x00422a1a;
    }
    // 00422a16  8b1f                   -mov ebx, dword ptr [edi]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.edi);
    // 00422a18  eb10                   -jmp 0x422a2a
    goto L_0x00422a2a;
L_0x00422a1a:
    // 00422a1a  31db                   +xor ebx, ebx
    cpu.clear_co();
    cpu.set_szp((cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx))));
    // 00422a1c  eb0c                   -jmp 0x422a2a
    goto L_0x00422a2a;
L_0x00422a1e:
    // 00422a1e  8b98b0105e00           -mov ebx, dword ptr [eax + 0x5e10b0]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164656) /* 0x5e10b0 */);
    // 00422a24  85db                   +test ebx, ebx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & cpu.ebx));
    // 00422a26  7402                   -je 0x422a2a
    if (cpu.flags.zf)
    {
        goto L_0x00422a2a;
    }
    // 00422a28  8b1b                   -mov ebx, dword ptr [ebx]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.ebx);
L_0x00422a2a:
    // 00422a2a  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00422a2d  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 00422a30  83fb13                 +cmp ebx, 0x13
    {
        x86::reg32 tmp1 = cpu.ebx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(19 /*0x13*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00422a33  7515                   -jne 0x422a4a
    if (!cpu.flags.zf)
    {
        goto L_0x00422a4a;
    }
    // 00422a35  8b98602f5500           -mov ebx, dword ptr [eax + 0x552f60]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(5582688) /* 0x552f60 */);
    // 00422a3b  8b9b1c010000           -mov ebx, dword ptr [ebx + 0x11c]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(284) /* 0x11c */);
    // 00422a41  8b84d8c82e5500         -mov eax, dword ptr [eax + ebx*8 + 0x552ec8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(5582536) /* 0x552ec8 */ + cpu.ebx * 8);
    // 00422a48  eb21                   -jmp 0x422a6b
    goto L_0x00422a6b;
L_0x00422a4a:
    // 00422a4a  8bb0b8105e00           -mov esi, dword ptr [eax + 0x5e10b8]
    cpu.esi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164664) /* 0x5e10b8 */);
    // 00422a50  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 00422a52  7411                   -je 0x422a65
    if (cpu.flags.zf)
    {
        goto L_0x00422a65;
    }
    // 00422a54  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 00422a56  89d7                   -mov edi, edx
    cpu.edi = cpu.edx;
    // 00422a58  8d7014                 -lea esi, [eax + 0x14]
    cpu.esi = x86::reg32(cpu.eax + x86::reg32(20) /* 0x14 */);
    // 00422a5b  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00422a5c  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00422a5d  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00422a5e  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00422a60  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00422a61  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00422a62  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00422a63  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00422a64  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x00422a65:
    // 00422a65  8b80b0105e00           -mov eax, dword ptr [eax + 0x5e10b0]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164656) /* 0x5e10b0 */);
L_0x00422a6b:
    // 00422a6b  89d7                   -mov edi, edx
    cpu.edi = cpu.edx;
    // 00422a6d  8d7014                 -lea esi, [eax + 0x14]
    cpu.esi = x86::reg32(cpu.eax + x86::reg32(20) /* 0x14 */);
    // 00422a70  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00422a71  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00422a72  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00422a73  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00422a75  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00422a76  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00422a77  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00422a78  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00422a79  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 */
void Application::sub_422aa0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
  goto start;
dynamic_jump:
  switch(cpu.ip)
  {
start:
    // 00422aa0  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00422aa1  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00422aa2  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00422aa3  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00422aa4  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00422aa6  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 00422aa8  e8f3000000             -call 0x422ba0
    cpu.esp -= 4;
    sub_422ba0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00422aad  8b0db0d36f00           -mov ecx, dword ptr [0x6fd3b0]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(7328688) /* 0x6fd3b0 */);
    // 00422ab3  83f901                 +cmp ecx, 1
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1 /*0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00422ab6  7504                   -jne 0x422abc
    if (!cpu.flags.zf)
    {
        goto L_0x00422abc;
    }
    // 00422ab8  21ca                   +and edx, ecx
    cpu.clear_co();
    cpu.set_szp((cpu.edx &= x86::reg32(x86::sreg32(cpu.ecx))));
    // 00422aba  eb02                   -jmp 0x422abe
    goto L_0x00422abe;
L_0x00422abc:
    // 00422abc  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
L_0x00422abe:
    // 00422abe  813d84367d0040010000   +cmp dword ptr [0x7d3684], 0x140
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(8205956) /* 0x7d3684 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(320 /*0x140*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00422ac8  0f8c90000000           -jl 0x422b5e
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x00422b5e;
    }
    // 00422ace  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00422ad0  0f8488000000           -je 0x422b5e
    if (cpu.flags.zf)
    {
        goto L_0x00422b5e;
    }
    // 00422ad6  f6800002000002         +test byte ptr [eax + 0x200], 2
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(cpu.eax + x86::reg32(512) /* 0x200 */) & 2 /*0x2*/));
    // 00422add  0f857b000000           -jne 0x422b5e
    if (!cpu.flags.zf)
    {
        goto L_0x00422b5e;
    }
    // 00422ae3  66f705583a7a008001     +test word ptr [0x7a3a58], 0x180
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg16>(app->getMemory<x86::reg16>(x86::reg32(8010328) /* 0x7a3a58 */) & 384 /*0x180*/));
    // 00422aec  0f856c000000           -jne 0x422b5e
    if (!cpu.flags.zf)
    {
        goto L_0x00422b5e;
    }
    // 00422af2  833d6492550000         +cmp dword ptr [0x559264], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5608036) /* 0x559264 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00422af9  740a                   -je 0x422b05
    if (cpu.flags.zf)
    {
        goto L_0x00422b05;
    }
  [[fallthrough]];
  case 0x00422afb:
    // 00422afb  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 00422b00  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00422b01  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00422b02  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00422b03  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00422b04  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x00422b05:
    // 00422b05  833da0d36f0002         +cmp dword ptr [0x6fd3a0], 2
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(7328672) /* 0x6fd3a0 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(2 /*0x2*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00422b0c  7450                   -je 0x422b5e
    if (cpu.flags.zf)
    {
        goto L_0x00422b5e;
    }
    // 00422b0e  8d0c9500000000         -lea ecx, [edx*4]
    cpu.ecx = x86::reg32(cpu.edx * 4);
    // 00422b15  8b81a0c47900           -mov eax, dword ptr [ecx + 0x79c4a0]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(7980192) /* 0x79c4a0 */);
    // 00422b1b  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00422b1d  753f                   -jne 0x422b5e
    if (!cpu.flags.zf)
    {
        goto L_0x00422b5e;
    }
    // 00422b1f  833d30fe550000         +cmp dword ptr [0x55fe30], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5635632) /* 0x55fe30 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00422b26  7405                   -je 0x422b2d
    if (cpu.flags.zf)
    {
        goto L_0x00422b2d;
    }
    // 00422b28  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00422b29  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00422b2a  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00422b2b  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00422b2c  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x00422b2d:
    // 00422b2d  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 00422b2f  e8cc0f0000             -call 0x423b00
    cpu.esp -= 4;
    sub_423b00(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00422b34  8bb1b0105e00           -mov esi, dword ptr [ecx + 0x5e10b0]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(6164656) /* 0x5e10b0 */);
    // 00422b3a  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 00422b3c  7413                   -je 0x422b51
    if (cpu.flags.zf)
    {
        goto L_0x00422b51;
    }
    // 00422b3e  8b16                   -mov edx, dword ptr [esi]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi);
    // 00422b40  83fa13                 +cmp edx, 0x13
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(19 /*0x13*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00422b43  750c                   -jne 0x422b51
    if (!cpu.flags.zf)
    {
        goto L_0x00422b51;
    }
    // 00422b45  8b81602f5500           -mov eax, dword ptr [ecx + 0x552f60]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(5582688) /* 0x552f60 */);
    // 00422b4b  8b801c010000           -mov eax, dword ptr [eax + 0x11c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(284) /* 0x11c */);
L_0x00422b51:
    // 00422b51  48                     -dec eax
    (cpu.eax)--;
    // 00422b52  83f805                 +cmp eax, 5
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(5 /*0x5*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00422b55  7707                   -ja 0x422b5e
    if (!cpu.flags.cf && !cpu.flags.zf)
    {
        goto L_0x00422b5e;
    }
    // 00422b57  ff24857c2a4200         -jmp dword ptr [eax*4 + 0x422a7c]
    cpu.ip = app->getMemory<x86::reg32>(4336252 + cpu.eax * 4); goto dynamic_jump;
L_0x00422b5e:
    // 00422b5e  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00422b60  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00422b61  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00422b62  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00422b63  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00422b64  c3                     -ret 
    cpu.esp += 4;
    return;
  default:
    NFS2_ASSERT(false);
  }
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 0x8b 0xdb */
void Application::sub_422b70(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00422b70  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00422b71  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00422b72  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00422b74  8b15b0d36f00           -mov edx, dword ptr [0x6fd3b0]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(7328688) /* 0x6fd3b0 */);
    // 00422b7a  83fa01                 +cmp edx, 1
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
    // 00422b7d  7504                   -jne 0x422b83
    if (!cpu.flags.zf)
    {
        goto L_0x00422b83;
    }
    // 00422b7f  21d0                   +and eax, edx
    cpu.clear_co();
    cpu.set_szp((cpu.eax &= x86::reg32(x86::sreg32(cpu.edx))));
    // 00422b81  eb02                   -jmp 0x422b85
    goto L_0x00422b85;
L_0x00422b83:
    // 00422b83  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
L_0x00422b85:
    // 00422b85  8b0485b0105e00         -mov eax, dword ptr [eax*4 + 0x5e10b0]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(6164656) /* 0x5e10b0 */ + cpu.eax * 4);
    // 00422b8c  8b8014010000           -mov eax, dword ptr [eax + 0x114]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(276) /* 0x114 */);
    // 00422b92  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00422b93  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00422b94  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 0x8b 0xdb */
void Application::sub_422ba0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00422ba0  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00422ba1  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00422ba2  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00422ba4  8b15b0d36f00           -mov edx, dword ptr [0x6fd3b0]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(7328688) /* 0x6fd3b0 */);
    // 00422baa  83fa01                 +cmp edx, 1
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
    // 00422bad  7504                   -jne 0x422bb3
    if (!cpu.flags.zf)
    {
        goto L_0x00422bb3;
    }
    // 00422baf  21d0                   +and eax, edx
    cpu.clear_co();
    cpu.set_szp((cpu.eax &= x86::reg32(x86::sreg32(cpu.edx))));
    // 00422bb1  eb02                   -jmp 0x422bb5
    goto L_0x00422bb5;
L_0x00422bb3:
    // 00422bb3  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
L_0x00422bb5:
    // 00422bb5  8b0485b0105e00         -mov eax, dword ptr [eax*4 + 0x5e10b0]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(6164656) /* 0x5e10b0 */ + cpu.eax * 4);
    // 00422bbc  8b4004                 -mov eax, dword ptr [eax + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 00422bbf  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00422bc0  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00422bc1  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x8b 0xc0 */
void Application::sub_422bd0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00422bd0  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00422bd1  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00422bd2  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00422bd4  8b15b0d36f00           -mov edx, dword ptr [0x6fd3b0]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(7328688) /* 0x6fd3b0 */);
    // 00422bda  83fa01                 +cmp edx, 1
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
    // 00422bdd  7504                   -jne 0x422be3
    if (!cpu.flags.zf)
    {
        goto L_0x00422be3;
    }
    // 00422bdf  21d0                   +and eax, edx
    cpu.clear_co();
    cpu.set_szp((cpu.eax &= x86::reg32(x86::sreg32(cpu.edx))));
    // 00422be1  eb02                   -jmp 0x422be5
    goto L_0x00422be5;
L_0x00422be3:
    // 00422be3  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
L_0x00422be5:
    // 00422be5  8b0485b0105e00         -mov eax, dword ptr [eax*4 + 0x5e10b0]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(6164656) /* 0x5e10b0 */ + cpu.eax * 4);
    // 00422bec  8b4008                 -mov eax, dword ptr [eax + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 00422bef  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00422bf0  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00422bf1  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x8b 0xc0 */
void Application::sub_422c00(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00422c00  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00422c01  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00422c02  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00422c03  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00422c05  8b0db0d36f00           -mov ecx, dword ptr [0x6fd3b0]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(7328688) /* 0x6fd3b0 */);
    // 00422c0b  83f901                 +cmp ecx, 1
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1 /*0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00422c0e  7504                   -jne 0x422c14
    if (!cpu.flags.zf)
    {
        goto L_0x00422c14;
    }
    // 00422c10  21c8                   +and eax, ecx
    cpu.clear_co();
    cpu.set_szp((cpu.eax &= x86::reg32(x86::sreg32(cpu.ecx))));
    // 00422c12  eb02                   -jmp 0x422c16
    goto L_0x00422c16;
L_0x00422c14:
    // 00422c14  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
L_0x00422c16:
    // 00422c16  8d0c8500000000         -lea ecx, [eax*4]
    cpu.ecx = x86::reg32(cpu.eax * 4);
    // 00422c1d  8b99b0105e00           -mov ebx, dword ptr [ecx + 0x5e10b0]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(6164656) /* 0x5e10b0 */);
    // 00422c23  3b5304                 +cmp edx, dword ptr [ebx + 4]
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(4) /* 0x4 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00422c26  740a                   -je 0x422c32
    if (cpu.flags.zf)
    {
        goto L_0x00422c32;
    }
    // 00422c28  c781f42f550001000000   -mov dword ptr [ecx + 0x552ff4], 1
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(5582836) /* 0x552ff4 */) = 1 /*0x1*/;
L_0x00422c32:
    // 00422c32  8b0485b0105e00         -mov eax, dword ptr [eax*4 + 0x5e10b0]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(6164656) /* 0x5e10b0 */ + cpu.eax * 4);
    // 00422c39  895004                 -mov dword ptr [eax + 4], edx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */) = cpu.edx;
    // 00422c3c  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00422c3d  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00422c3e  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00422c3f  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip  */
void Application::sub_422c40(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00422c40  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00422c41  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00422c42  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00422c43  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00422c45  8b0db0d36f00           -mov ecx, dword ptr [0x6fd3b0]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(7328688) /* 0x6fd3b0 */);
    // 00422c4b  83f901                 +cmp ecx, 1
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1 /*0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00422c4e  7504                   -jne 0x422c54
    if (!cpu.flags.zf)
    {
        goto L_0x00422c54;
    }
    // 00422c50  21c8                   +and eax, ecx
    cpu.clear_co();
    cpu.set_szp((cpu.eax &= x86::reg32(x86::sreg32(cpu.ecx))));
    // 00422c52  eb02                   -jmp 0x422c56
    goto L_0x00422c56;
L_0x00422c54:
    // 00422c54  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
L_0x00422c56:
    // 00422c56  8d0c8500000000         -lea ecx, [eax*4]
    cpu.ecx = x86::reg32(cpu.eax * 4);
    // 00422c5d  8b99b0105e00           -mov ebx, dword ptr [ecx + 0x5e10b0]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(6164656) /* 0x5e10b0 */);
    // 00422c63  3b5308                 +cmp edx, dword ptr [ebx + 8]
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(8) /* 0x8 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00422c66  740a                   -je 0x422c72
    if (cpu.flags.zf)
    {
        goto L_0x00422c72;
    }
    // 00422c68  c781f42f550001000000   -mov dword ptr [ecx + 0x552ff4], 1
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(5582836) /* 0x552ff4 */) = 1 /*0x1*/;
L_0x00422c72:
    // 00422c72  8b0485b0105e00         -mov eax, dword ptr [eax*4 + 0x5e10b0]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(6164656) /* 0x5e10b0 */ + cpu.eax * 4);
    // 00422c79  895008                 -mov dword ptr [eax + 8], edx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */) = cpu.edx;
    // 00422c7c  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00422c7d  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00422c7e  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00422c7f  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip  */
void Application::sub_422c80(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00422c80  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00422c81  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00422c83  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00422c84  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8b 0xd2 */
void Application::sub_422cf0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
  goto start;
dynamic_jump:
  switch(cpu.ip)
  {
start:
    // 00422cf0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00422cf1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00422cf2  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00422cf3  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00422cf4  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00422cf5  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00422cf6  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00422cf8  83ec7c                 -sub esp, 0x7c
    (cpu.esp) -= x86::reg32(x86::sreg32(124 /*0x7c*/));
    // 00422cfb  8b15b0d36f00           -mov edx, dword ptr [0x6fd3b0]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(7328688) /* 0x6fd3b0 */);
    // 00422d01  83fa01                 +cmp edx, 1
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
    // 00422d04  7504                   -jne 0x422d0a
    if (!cpu.flags.zf)
    {
        goto L_0x00422d0a;
    }
    // 00422d06  89d1                   -mov ecx, edx
    cpu.ecx = cpu.edx;
    // 00422d08  eb02                   -jmp 0x422d0c
    goto L_0x00422d0c;
L_0x00422d0a:
    // 00422d0a  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
L_0x00422d0c:
    // 00422d0c  8d7d84                 -lea edi, [ebp - 0x7c]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(-124) /* -0x7c */);
    // 00422d0f  bedc124200             -mov esi, 0x4212dc
    cpu.esi = 4330204 /*0x4212dc*/;
    // 00422d14  894dfc                 -mov dword ptr [ebp - 4], ecx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.ecx;
    // 00422d17  b91e000000             -mov ecx, 0x1e
    cpu.ecx = 30 /*0x1e*/;
    // 00422d1c  f3a5                   -rep movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00422d1e  b909000000             -mov ecx, 9
    cpu.ecx = 9 /*0x9*/;
    // 00422d23  bf5cd95d00             -mov edi, 0x5dd95c
    cpu.edi = 6150492 /*0x5dd95c*/;
    // 00422d28  be98445600             -mov esi, 0x564498
    cpu.esi = 5653656 /*0x564498*/;
    // 00422d2d  f3a5                   -rep movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00422d2f  bf50d95d00             -mov edi, 0x5dd950
    cpu.edi = 6150480 /*0x5dd950*/;
    // 00422d34  be8c445600             -mov esi, 0x56448c
    cpu.esi = 5653644 /*0x56448c*/;
    // 00422d39  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00422d3a  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00422d3b  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00422d3c  b909000000             -mov ecx, 9
    cpu.ecx = 9 /*0x9*/;
    // 00422d41  bfbcd95d00             -mov edi, 0x5dd9bc
    cpu.edi = 6150588 /*0x5dd9bc*/;
    // 00422d46  be98445600             -mov esi, 0x564498
    cpu.esi = 5653656 /*0x564498*/;
    // 00422d4b  f3a5                   -rep movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00422d4d  bfb0d95d00             -mov edi, 0x5dd9b0
    cpu.edi = 6150576 /*0x5dd9b0*/;
    // 00422d52  be8c445600             -mov esi, 0x56448c
    cpu.esi = 5653644 /*0x56448c*/;
    // 00422d57  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
    // 00422d59  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00422d5a  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00422d5b  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00422d5c  e8ff0c0000             -call 0x423a60
    cpu.esp -= 4;
    sub_423a60(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00422d61:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00422d61  3b5dfc                 +cmp ebx, dword ptr [ebp - 4]
    {
        x86::reg32 tmp1 = cpu.ebx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00422d64  0f8f010b0000           -jg 0x42386b
    if (!cpu.flags.zf && (cpu.flags.sf == cpu.flags.of))
    {
        goto L_0x0042386b;
    }
    // 00422d6a  be01000000             -mov esi, 1
    cpu.esi = 1 /*0x1*/;
    // 00422d6f  ba10000000             -mov edx, 0x10
    cpu.edx = 16 /*0x10*/;
    // 00422d74  31ff                   -xor edi, edi
    cpu.edi ^= x86::reg32(x86::sreg32(cpu.edi));
    // 00422d76  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 00422d78  893cdd10105e00         -mov dword ptr [ebx*8 + 0x5e1010], edi
    app->getMemory<x86::reg32>(x86::reg32(6164496) /* 0x5e1010 */ + cpu.ebx * 8) = cpu.edi;
    // 00422d7f  89349df42f5500         -mov dword ptr [ebx*4 + 0x552ff4], esi
    app->getMemory<x86::reg32>(x86::reg32(5582836) /* 0x552ff4 */ + cpu.ebx * 4) = cpu.esi;
    // 00422d86  893cdd14105e00         -mov dword ptr [ebx*8 + 0x5e1014], edi
    app->getMemory<x86::reg32>(x86::reg32(6164500) /* 0x5e1014 */ + cpu.ebx * 8) = cpu.edi;
    // 00422d8d  e81e0b0000             -call 0x4238b0
    cpu.esp -= 4;
    sub_4238b0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00422d92  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 00422d94  31d2                   +xor edx, edx
    cpu.clear_co();
    cpu.set_szp((cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx))));
    // 00422d96  e8c50b0000             -call 0x423960
    cpu.esp -= 4;
    sub_423960(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00422d9b  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 00422d9d  e9a30a0000             -jmp 0x423845
    goto L_0x00423845;
L_0x00422da2:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00422da2  8b0df4d46f00           -mov ecx, dword ptr [0x6fd4f4]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(7329012) /* 0x6fd4f4 */);
L_0x00422da8:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00422da8  8b348d48fa5e00         -mov esi, dword ptr [ecx*4 + 0x5efa48]
    cpu.esi = app->getMemory<x86::reg32>(x86::reg32(6224456) /* 0x5efa48 */ + cpu.ecx * 4);
    // 00422daf  897004                 -mov dword ptr [eax + 4], esi
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */) = cpu.esi;
    // 00422db2  897008                 -mov dword ptr [eax + 8], esi
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */) = cpu.esi;
    // 00422db5  f6860002000020         +test byte ptr [esi + 0x200], 0x20
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(cpu.esi + x86::reg32(512) /* 0x200 */) & 32 /*0x20*/));
    // 00422dbc  740e                   -je 0x422dcc
    if (cpu.flags.zf)
    {
        goto L_0x00422dcc;
    }
    // 00422dbe  8b349de02e5500         -mov esi, dword ptr [ebx*4 + 0x552ee0]
    cpu.esi = app->getMemory<x86::reg32>(x86::reg32(5582560) /* 0x552ee0 */ + cpu.ebx * 4);
    // 00422dc5  89349db0105e00         -mov dword ptr [ebx*4 + 0x5e10b0], esi
    app->getMemory<x86::reg32>(x86::reg32(6164656) /* 0x5e10b0 */ + cpu.ebx * 4) = cpu.esi;
L_0x00422dcc:
    // 00422dcc  c7401000000000         -mov dword ptr [eax + 0x10], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(16) /* 0x10 */) = 0 /*0x0*/;
    // 00422dd3  b91e000000             -mov ecx, 0x1e
    cpu.ecx = 30 /*0x1e*/;
    // 00422dd8  8910                   -mov dword ptr [eax], edx
    app->getMemory<x86::reg32>(cpu.eax) = cpu.edx;
    // 00422dda  8d7584                 -lea esi, [ebp - 0x7c]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(-124) /* -0x7c */);
    // 00422ddd  8d7874                 -lea edi, [eax + 0x74]
    cpu.edi = x86::reg32(cpu.eax + x86::reg32(116) /* 0x74 */);
    // 00422de0  89580c                 -mov dword ptr [eax + 0xc], ebx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */) = cpu.ebx;
    // 00422de3  f3a5                   -rep movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00422de5  c780ec000000ffffffff   -mov dword ptr [eax + 0xec], 0xffffffff
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(236) /* 0xec */) = 4294967295 /*0xffffffff*/;
    // 00422def  8b7004                 -mov esi, dword ptr [eax + 4]
    cpu.esi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 00422df2  b909000000             -mov ecx, 9
    cpu.ecx = 9 /*0x9*/;
    // 00422df7  8d782c                 -lea edi, [eax + 0x2c]
    cpu.edi = x86::reg32(cpu.eax + x86::reg32(44) /* 0x2c */);
    // 00422dfa  8db6c0000000           -lea esi, [esi + 0xc0]
    cpu.esi = x86::reg32(cpu.esi + x86::reg32(192) /* 0xc0 */);
    // 00422e00  f3a5                   -rep movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00422e02  8b4804                 -mov ecx, dword ptr [eax + 4]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 00422e05  c7405000000000         -mov dword ptr [eax + 0x50], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(80) /* 0x50 */) = 0 /*0x0*/;
    // 00422e0c  d98198000000           -fld dword ptr [ecx + 0x98]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(152) /* 0x98 */));
    // 00422e12  8b4804                 -mov ecx, dword ptr [eax + 4]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 00422e15  d95814                 -fstp dword ptr [eax + 0x14]
    app->getMemory<float>(cpu.eax + x86::reg32(20) /* 0x14 */) = float(fpu1);
    // 00422e18  d9819c000000           -fld dword ptr [ecx + 0x9c]
    x86::Float fpu2 = x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(156) /* 0x9c */));
    // 00422e1e  8b4804                 -mov ecx, dword ptr [eax + 4]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 00422e21  d95818                 -fstp dword ptr [eax + 0x18]
    app->getMemory<float>(cpu.eax + x86::reg32(24) /* 0x18 */) = float(fpu2);
    // 00422e24  d981a0000000           -fld dword ptr [ecx + 0xa0]
    x86::Float fpu3 = x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(160) /* 0xa0 */));
    // 00422e2a  c7402000000000         -mov dword ptr [eax + 0x20], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(32) /* 0x20 */) = 0 /*0x0*/;
    // 00422e31  c7402400000000         -mov dword ptr [eax + 0x24], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(36) /* 0x24 */) = 0 /*0x0*/;
    // 00422e38  c74028000040c0         -mov dword ptr [eax + 0x28], 0xc0400000
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(40) /* 0x28 */) = 3225419776 /*0xc0400000*/;
    // 00422e3f  d9581c                 -fstp dword ptr [eax + 0x1c]
    app->getMemory<float>(cpu.eax + x86::reg32(28) /* 0x1c */) = float(fpu3);
    // 00422e42  c7405400000000         -mov dword ptr [eax + 0x54], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(84) /* 0x54 */) = 0 /*0x0*/;
    // 00422e49  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 00422e4b  8d3408                 -lea esi, [eax + ecx]
    cpu.esi = x86::reg32(cpu.eax + cpu.ecx * 1);
    // 00422e4e  41                     -inc ecx
    (cpu.ecx)++;
    // 00422e4f  c6465800               -mov byte ptr [esi + 0x58], 0
    app->getMemory<x86::reg8>(cpu.esi + x86::reg32(88) /* 0x58 */) = 0 /*0x0*/;
    }
L_0x00422e53:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00422e53  83f919                 +cmp ecx, 0x19
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(25 /*0x19*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00422e56  7d0a                   -jge 0x422e62
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00422e62;
    }
    // 00422e58  8d3408                 -lea esi, [eax + ecx]
    cpu.esi = x86::reg32(cpu.eax + cpu.ecx * 1);
    // 00422e5b  41                     +inc ecx
    {
        x86::reg32& tmp = cpu.ecx;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 00422e5c  c6465800               -mov byte ptr [esi + 0x58], 0
    app->getMemory<x86::reg8>(cpu.esi + x86::reg32(88) /* 0x58 */) = 0 /*0x0*/;
    // 00422e60  ebf1                   -jmp 0x422e53
    goto L_0x00422e53;
L_0x00422e62:
    // 00422e62  c780f400000000000000   -mov dword ptr [eax + 0xf4], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(244) /* 0xf4 */) = 0 /*0x0*/;
    // 00422e6c  c780f800000000000000   -mov dword ptr [eax + 0xf8], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(248) /* 0xf8 */) = 0 /*0x0*/;
    // 00422e76  c780fc00000000000000   -mov dword ptr [eax + 0xfc], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(252) /* 0xfc */) = 0 /*0x0*/;
    // 00422e80  c7800401000000000000   -mov dword ptr [eax + 0x104], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(260) /* 0x104 */) = 0 /*0x0*/;
    // 00422e8a  c7800801000000000000   -mov dword ptr [eax + 0x108], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(264) /* 0x108 */) = 0 /*0x0*/;
    // 00422e94  c7800c01000000000000   -mov dword ptr [eax + 0x10c], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(268) /* 0x10c */) = 0 /*0x0*/;
    // 00422e9e  8d4aff                 -lea ecx, [edx - 1]
    cpu.ecx = x86::reg32(cpu.edx + x86::reg32(-1) /* -0x1 */);
    // 00422ea1  c780f000000000000000   -mov dword ptr [eax + 0xf0], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(240) /* 0xf0 */) = 0 /*0x0*/;
    // 00422eab  83f917                 +cmp ecx, 0x17
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(23 /*0x17*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00422eae  0f878b090000           -ja 0x42383f
    if (!cpu.flags.cf && !cpu.flags.zf)
    {
        goto L_0x0042383f;
    }
    // 00422eb4  ff248d882c4200         -jmp dword ptr [ecx*4 + 0x422c88]
    cpu.ip = app->getMemory<x86::reg32>(4336776 + cpu.ecx * 4); goto dynamic_jump;
  case 0x00422ebb:
    // 00422ebb  c7801001000000000000   -mov dword ptr [eax + 0x110], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(272) /* 0x110 */) = 0 /*0x0*/;
    // 00422ec5  c780140100009a99193f   -mov dword ptr [eax + 0x114], 0x3f19999a
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(276) /* 0x114 */) = 1058642330 /*0x3f19999a*/;
    // 00422ecf  c78018010000000080bf   -mov dword ptr [eax + 0x118], 0xbf800000
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(280) /* 0x118 */) = 3212836864 /*0xbf800000*/;
    // 00422ed9  c7405000000000         -mov dword ptr [eax + 0x50], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(80) /* 0x50 */) = 0 /*0x0*/;
    // 00422ee0  c7800401000001000000   -mov dword ptr [eax + 0x104], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(260) /* 0x104 */) = 1 /*0x1*/;
    // 00422eea  c7800801000000000000   -mov dword ptr [eax + 0x108], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(264) /* 0x108 */) = 0 /*0x0*/;
    // 00422ef4  c780f400000000000000   -mov dword ptr [eax + 0xf4], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(244) /* 0xf4 */) = 0 /*0x0*/;
    // 00422efe  c780f000000000000000   -mov dword ptr [eax + 0xf0], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(240) /* 0xf0 */) = 0 /*0x0*/;
    // 00422f08  c6406901               -mov byte ptr [eax + 0x69], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(105) /* 0x69 */) = 1 /*0x1*/;
    // 00422f0c  e92e090000             -jmp 0x42383f
    goto L_0x0042383f;
  case 0x00422f11:
    // 00422f11  c7801001000000000000   -mov dword ptr [eax + 0x110], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(272) /* 0x110 */) = 0 /*0x0*/;
    // 00422f1b  c780140100009a99193f   -mov dword ptr [eax + 0x114], 0x3f19999a
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(276) /* 0x114 */) = 1058642330 /*0x3f19999a*/;
    // 00422f25  c780180100000000803f   -mov dword ptr [eax + 0x118], 0x3f800000
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(280) /* 0x118 */) = 1065353216 /*0x3f800000*/;
    // 00422f2f  c740508fc2f53c         -mov dword ptr [eax + 0x50], 0x3cf5c28f
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(80) /* 0x50 */) = 1022739087 /*0x3cf5c28f*/;
    // 00422f36  c7800401000002000000   -mov dword ptr [eax + 0x104], 2
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(260) /* 0x104 */) = 2 /*0x2*/;
    // 00422f40  c7800801000000000000   -mov dword ptr [eax + 0x108], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(264) /* 0x108 */) = 0 /*0x0*/;
    // 00422f4a  c780f400000000000000   -mov dword ptr [eax + 0xf4], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(244) /* 0xf4 */) = 0 /*0x0*/;
    // 00422f54  c780f000000000000000   -mov dword ptr [eax + 0xf0], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(240) /* 0xf0 */) = 0 /*0x0*/;
    // 00422f5e  c6406901               -mov byte ptr [eax + 0x69], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(105) /* 0x69 */) = 1 /*0x1*/;
    // 00422f62  e9d8080000             -jmp 0x42383f
    goto L_0x0042383f;
  case 0x00422f67:
    // 00422f67  c7801001000000000000   -mov dword ptr [eax + 0x110], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(272) /* 0x110 */) = 0 /*0x0*/;
    // 00422f71  c780140100000000803f   -mov dword ptr [eax + 0x114], 0x3f800000
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(276) /* 0x114 */) = 1065353216 /*0x3f800000*/;
    // 00422f7b  c78018010000000080c0   -mov dword ptr [eax + 0x118], 0xc0800000
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(280) /* 0x118 */) = 3229614080 /*0xc0800000*/;
    // 00422f85  c7801c0100000000803e   -mov dword ptr [eax + 0x11c], 0x3e800000
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(284) /* 0x11c */) = 1048576000 /*0x3e800000*/;
    // 00422f8f  c78020010000cdcc4c3e   -mov dword ptr [eax + 0x120], 0x3e4ccccd
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(288) /* 0x120 */) = 1045220557 /*0x3e4ccccd*/;
    // 00422f99  c740508fc2f53c         -mov dword ptr [eax + 0x50], 0x3cf5c28f
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(80) /* 0x50 */) = 1022739087 /*0x3cf5c28f*/;
    // 00422fa0  c7800401000000000000   -mov dword ptr [eax + 0x104], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(260) /* 0x104 */) = 0 /*0x0*/;
    // 00422faa  c7800801000001000000   -mov dword ptr [eax + 0x108], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(264) /* 0x108 */) = 1 /*0x1*/;
    // 00422fb4  c780f400000001000000   -mov dword ptr [eax + 0xf4], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(244) /* 0xf4 */) = 1 /*0x1*/;
    // 00422fbe  c780f000000001000000   -mov dword ptr [eax + 0xf0], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(240) /* 0xf0 */) = 1 /*0x1*/;
    // 00422fc8  c780f800000001000000   -mov dword ptr [eax + 0xf8], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(248) /* 0xf8 */) = 1 /*0x1*/;
    // 00422fd2  c6405b01               -mov byte ptr [eax + 0x5b], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(91) /* 0x5b */) = 1 /*0x1*/;
    // 00422fd6  c6405d01               -mov byte ptr [eax + 0x5d], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(93) /* 0x5d */) = 1 /*0x1*/;
    // 00422fda  c6405e01               -mov byte ptr [eax + 0x5e], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(94) /* 0x5e */) = 1 /*0x1*/;
    // 00422fde  c6406901               -mov byte ptr [eax + 0x69], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(105) /* 0x69 */) = 1 /*0x1*/;
    // 00422fe2  c6406d01               -mov byte ptr [eax + 0x6d], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(109) /* 0x6d */) = 1 /*0x1*/;
    // 00422fe6  c6407001               -mov byte ptr [eax + 0x70], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(112) /* 0x70 */) = 1 /*0x1*/;
    // 00422fea  e950080000             -jmp 0x42383f
    goto L_0x0042383f;
  case 0x00422fef:
    // 00422fef  c7801001000000000000   -mov dword ptr [eax + 0x110], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(272) /* 0x110 */) = 0 /*0x0*/;
    // 00422ff9  c780140100000000803f   -mov dword ptr [eax + 0x114], 0x3f800000
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(276) /* 0x114 */) = 1065353216 /*0x3f800000*/;
    // 00423003  c78018010000000050c0   -mov dword ptr [eax + 0x118], 0xc0500000
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(280) /* 0x118 */) = 3226468352 /*0xc0500000*/;
    // 0042300d  c7801c01000000000040   -mov dword ptr [eax + 0x11c], 0x40000000
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(284) /* 0x11c */) = 1073741824 /*0x40000000*/;
    // 00423017  c7802001000000000000   -mov dword ptr [eax + 0x120], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(288) /* 0x120 */) = 0 /*0x0*/;
    // 00423021  c740508fc2f53c         -mov dword ptr [eax + 0x50], 0x3cf5c28f
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(80) /* 0x50 */) = 1022739087 /*0x3cf5c28f*/;
    // 00423028  c7800401000000000000   -mov dword ptr [eax + 0x104], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(260) /* 0x104 */) = 0 /*0x0*/;
    // 00423032  c7800801000001000000   -mov dword ptr [eax + 0x108], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(264) /* 0x108 */) = 1 /*0x1*/;
    // 0042303c  c780f400000001000000   -mov dword ptr [eax + 0xf4], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(244) /* 0xf4 */) = 1 /*0x1*/;
    // 00423046  c780f000000001000000   -mov dword ptr [eax + 0xf0], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(240) /* 0xf0 */) = 1 /*0x1*/;
    // 00423050  c780f800000001000000   -mov dword ptr [eax + 0xf8], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(248) /* 0xf8 */) = 1 /*0x1*/;
    // 0042305a  c6405b01               -mov byte ptr [eax + 0x5b], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(91) /* 0x5b */) = 1 /*0x1*/;
    // 0042305e  c6405d01               -mov byte ptr [eax + 0x5d], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(93) /* 0x5d */) = 1 /*0x1*/;
    // 00423062  c6405c01               -mov byte ptr [eax + 0x5c], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(92) /* 0x5c */) = 1 /*0x1*/;
    // 00423066  c6406901               -mov byte ptr [eax + 0x69], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(105) /* 0x69 */) = 1 /*0x1*/;
    // 0042306a  c6406d01               -mov byte ptr [eax + 0x6d], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(109) /* 0x6d */) = 1 /*0x1*/;
    // 0042306e  c6407001               -mov byte ptr [eax + 0x70], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(112) /* 0x70 */) = 1 /*0x1*/;
    // 00423072  e9c8070000             -jmp 0x42383f
    goto L_0x0042383f;
  case 0x00423077:
    // 00423077  c7801001000000000000   -mov dword ptr [eax + 0x110], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(272) /* 0x110 */) = 0 /*0x0*/;
    // 00423081  c780140100003333d33f   -mov dword ptr [eax + 0x114], 0x3fd33333
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(276) /* 0x114 */) = 1070805811 /*0x3fd33333*/;
    // 0042308b  c780180100000000b0c0   -mov dword ptr [eax + 0x118], 0xc0b00000
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(280) /* 0x118 */) = 3232759808 /*0xc0b00000*/;
    // 00423095  c7801c0100000000803e   -mov dword ptr [eax + 0x11c], 0x3e800000
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(284) /* 0x11c */) = 1048576000 /*0x3e800000*/;
    // 0042309f  c78020010000cdcc4c3e   -mov dword ptr [eax + 0x120], 0x3e4ccccd
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(288) /* 0x120 */) = 1045220557 /*0x3e4ccccd*/;
    // 004230a9  c740500ad7233d         -mov dword ptr [eax + 0x50], 0x3d23d70a
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(80) /* 0x50 */) = 1025758986 /*0x3d23d70a*/;
    // 004230b0  c7800401000000000000   -mov dword ptr [eax + 0x104], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(260) /* 0x104 */) = 0 /*0x0*/;
    // 004230ba  c7800801000001000000   -mov dword ptr [eax + 0x108], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(264) /* 0x108 */) = 1 /*0x1*/;
    // 004230c4  c780f400000001000000   -mov dword ptr [eax + 0xf4], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(244) /* 0xf4 */) = 1 /*0x1*/;
    // 004230ce  c780f000000001000000   -mov dword ptr [eax + 0xf0], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(240) /* 0xf0 */) = 1 /*0x1*/;
    // 004230d8  c780f800000001000000   -mov dword ptr [eax + 0xf8], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(248) /* 0xf8 */) = 1 /*0x1*/;
    // 004230e2  c6406301               -mov byte ptr [eax + 0x63], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(99) /* 0x63 */) = 1 /*0x1*/;
    // 004230e6  c6405d01               -mov byte ptr [eax + 0x5d], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(93) /* 0x5d */) = 1 /*0x1*/;
    // 004230ea  c6405e01               -mov byte ptr [eax + 0x5e], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(94) /* 0x5e */) = 1 /*0x1*/;
    // 004230ee  c6405c01               -mov byte ptr [eax + 0x5c], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(92) /* 0x5c */) = 1 /*0x1*/;
    // 004230f2  c6406901               -mov byte ptr [eax + 0x69], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(105) /* 0x69 */) = 1 /*0x1*/;
    // 004230f6  c6406d01               -mov byte ptr [eax + 0x6d], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(109) /* 0x6d */) = 1 /*0x1*/;
    // 004230fa  c6407001               -mov byte ptr [eax + 0x70], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(112) /* 0x70 */) = 1 /*0x1*/;
    // 004230fe  c6406401               -mov byte ptr [eax + 0x64], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(100) /* 0x64 */) = 1 /*0x1*/;
    // 00423102  c6406501               -mov byte ptr [eax + 0x65], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(101) /* 0x65 */) = 1 /*0x1*/;
    // 00423106  c6405f01               -mov byte ptr [eax + 0x5f], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(95) /* 0x5f */) = 1 /*0x1*/;
    // 0042310a  e930070000             -jmp 0x42383f
    goto L_0x0042383f;
  case 0x0042310f:
    // 0042310f  c7801001000000000000   -mov dword ptr [eax + 0x110], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(272) /* 0x110 */) = 0 /*0x0*/;
    // 00423119  c780140100003333d33f   -mov dword ptr [eax + 0x114], 0x3fd33333
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(276) /* 0x114 */) = 1070805811 /*0x3fd33333*/;
    // 00423123  c78018010000000098c0   -mov dword ptr [eax + 0x118], 0xc0980000
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(280) /* 0x118 */) = 3231186944 /*0xc0980000*/;
    // 0042312d  c7801c01000000000040   -mov dword ptr [eax + 0x11c], 0x40000000
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(284) /* 0x11c */) = 1073741824 /*0x40000000*/;
    // 00423137  c7802001000000000000   -mov dword ptr [eax + 0x120], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(288) /* 0x120 */) = 0 /*0x0*/;
    // 00423141  c740500ad7233d         -mov dword ptr [eax + 0x50], 0x3d23d70a
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(80) /* 0x50 */) = 1025758986 /*0x3d23d70a*/;
    // 00423148  c7800401000000000000   -mov dword ptr [eax + 0x104], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(260) /* 0x104 */) = 0 /*0x0*/;
    // 00423152  c7800801000001000000   -mov dword ptr [eax + 0x108], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(264) /* 0x108 */) = 1 /*0x1*/;
    // 0042315c  c780f400000001000000   -mov dword ptr [eax + 0xf4], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(244) /* 0xf4 */) = 1 /*0x1*/;
    // 00423166  c780f000000001000000   -mov dword ptr [eax + 0xf0], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(240) /* 0xf0 */) = 1 /*0x1*/;
    // 00423170  c780f800000001000000   -mov dword ptr [eax + 0xf8], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(248) /* 0xf8 */) = 1 /*0x1*/;
    // 0042317a  c6405c01               -mov byte ptr [eax + 0x5c], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(92) /* 0x5c */) = 1 /*0x1*/;
    // 0042317e  c6405b01               -mov byte ptr [eax + 0x5b], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(91) /* 0x5b */) = 1 /*0x1*/;
    // 00423182  c6405e01               -mov byte ptr [eax + 0x5e], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(94) /* 0x5e */) = 1 /*0x1*/;
    // 00423186  c6406901               -mov byte ptr [eax + 0x69], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(105) /* 0x69 */) = 1 /*0x1*/;
    // 0042318a  c6406d01               -mov byte ptr [eax + 0x6d], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(109) /* 0x6d */) = 1 /*0x1*/;
    // 0042318e  c6407001               -mov byte ptr [eax + 0x70], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(112) /* 0x70 */) = 1 /*0x1*/;
    // 00423192  e9a8060000             -jmp 0x42383f
    goto L_0x0042383f;
  case 0x00423197:
    // 00423197  c780100100000000c040   -mov dword ptr [eax + 0x110], 0x40c00000
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(272) /* 0x110 */) = 1086324736 /*0x40c00000*/;
    // 004231a1  c7801401000000000040   -mov dword ptr [eax + 0x114], 0x40000000
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(276) /* 0x114 */) = 1073741824 /*0x40000000*/;
    // 004231ab  c780180100000000c040   -mov dword ptr [eax + 0x118], 0x40c00000
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(280) /* 0x118 */) = 1086324736 /*0x40c00000*/;
    // 004231b5  c7801c0100006f12833a   -mov dword ptr [eax + 0x11c], 0x3a83126f
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(284) /* 0x11c */) = 981668463 /*0x3a83126f*/;
    // 004231bf  c78020010000ffffffff   -mov dword ptr [eax + 0x120], 0xffffffff
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(288) /* 0x120 */) = 4294967295 /*0xffffffff*/;
    // 004231c9  c7802401000000000000   -mov dword ptr [eax + 0x124], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(292) /* 0x124 */) = 0 /*0x0*/;
    // 004231d3  c7802801000000000000   -mov dword ptr [eax + 0x128], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(296) /* 0x128 */) = 0 /*0x0*/;
    // 004231dd  c7405000000000         -mov dword ptr [eax + 0x50], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(80) /* 0x50 */) = 0 /*0x0*/;
    // 004231e4  c7800401000000000000   -mov dword ptr [eax + 0x104], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(260) /* 0x104 */) = 0 /*0x0*/;
    // 004231ee  c7800801000001000000   -mov dword ptr [eax + 0x108], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(264) /* 0x108 */) = 1 /*0x1*/;
    // 004231f8  c780f400000001000000   -mov dword ptr [eax + 0xf4], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(244) /* 0xf4 */) = 1 /*0x1*/;
    // 00423202  c780f000000001000000   -mov dword ptr [eax + 0xf0], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(240) /* 0xf0 */) = 1 /*0x1*/;
    // 0042320c  c780f800000001000000   -mov dword ptr [eax + 0xf8], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(248) /* 0xf8 */) = 1 /*0x1*/;
    // 00423216  c6406401               -mov byte ptr [eax + 0x64], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(100) /* 0x64 */) = 1 /*0x1*/;
    // 0042321a  c6406501               -mov byte ptr [eax + 0x65], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(101) /* 0x65 */) = 1 /*0x1*/;
    // 0042321e  c6406301               -mov byte ptr [eax + 0x63], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(99) /* 0x63 */) = 1 /*0x1*/;
    // 00423222  c6406901               -mov byte ptr [eax + 0x69], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(105) /* 0x69 */) = 1 /*0x1*/;
    // 00423226  e914060000             -jmp 0x42383f
    goto L_0x0042383f;
  case 0x0042322b:
    // 0042322b  c7801001000000000000   -mov dword ptr [eax + 0x110], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(272) /* 0x110 */) = 0 /*0x0*/;
    // 00423235  c7801401000000004040   -mov dword ptr [eax + 0x114], 0x40400000
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(276) /* 0x114 */) = 1077936128 /*0x40400000*/;
    // 0042323f  c78018010000000020c1   -mov dword ptr [eax + 0x118], 0xc1200000
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(280) /* 0x118 */) = 3240099840 /*0xc1200000*/;
    // 00423249  c740500000283a         -mov dword ptr [eax + 0x50], 0x3a280000
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(80) /* 0x50 */) = 975699968 /*0x3a280000*/;
    // 00423250  c7800401000000000000   -mov dword ptr [eax + 0x104], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(260) /* 0x104 */) = 0 /*0x0*/;
    // 0042325a  c7800801000001000000   -mov dword ptr [eax + 0x108], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(264) /* 0x108 */) = 1 /*0x1*/;
    // 00423264  c780f400000001000000   -mov dword ptr [eax + 0xf4], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(244) /* 0xf4 */) = 1 /*0x1*/;
    // 0042326e  c780f800000001000000   -mov dword ptr [eax + 0xf8], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(248) /* 0xf8 */) = 1 /*0x1*/;
    // 00423278  c780f000000001000000   -mov dword ptr [eax + 0xf0], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(240) /* 0xf0 */) = 1 /*0x1*/;
    // 00423282  e9b8050000             -jmp 0x42383f
    goto L_0x0042383f;
  case 0x00423287:
    // 00423287  c7801001000000009040   -mov dword ptr [eax + 0x110], 0x40900000
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(272) /* 0x110 */) = 1083179008 /*0x40900000*/;
    // 00423291  c780140100000000c03f   -mov dword ptr [eax + 0x114], 0x3fc00000
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(276) /* 0x114 */) = 1069547520 /*0x3fc00000*/;
    // 0042329b  c7801801000000009040   -mov dword ptr [eax + 0x118], 0x40900000
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(280) /* 0x118 */) = 1083179008 /*0x40900000*/;
    // 004232a5  c7801c01000000000000   -mov dword ptr [eax + 0x11c], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(284) /* 0x11c */) = 0 /*0x0*/;
    // 004232af  c7802001000000000000   -mov dword ptr [eax + 0x120], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(288) /* 0x120 */) = 0 /*0x0*/;
    // 004232b9  c7802401000000000000   -mov dword ptr [eax + 0x124], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(292) /* 0x124 */) = 0 /*0x0*/;
    // 004232c3  c7405000000000         -mov dword ptr [eax + 0x50], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(80) /* 0x50 */) = 0 /*0x0*/;
    // 004232ca  c7800401000000000000   -mov dword ptr [eax + 0x104], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(260) /* 0x104 */) = 0 /*0x0*/;
    // 004232d4  c7800801000001000000   -mov dword ptr [eax + 0x108], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(264) /* 0x108 */) = 1 /*0x1*/;
    // 004232de  c780f400000001000000   -mov dword ptr [eax + 0xf4], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(244) /* 0xf4 */) = 1 /*0x1*/;
    // 004232e8  c780f800000001000000   -mov dword ptr [eax + 0xf8], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(248) /* 0xf8 */) = 1 /*0x1*/;
    // 004232f2  c780f000000001000000   -mov dword ptr [eax + 0xf0], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(240) /* 0xf0 */) = 1 /*0x1*/;
    // 004232fc  e93e050000             -jmp 0x42383f
    goto L_0x0042383f;
  case 0x00423301:
    // 00423301  c780100100000000c040   -mov dword ptr [eax + 0x110], 0x40c00000
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(272) /* 0x110 */) = 1086324736 /*0x40c00000*/;
    // 0042330b  c7801401000000000040   -mov dword ptr [eax + 0x114], 0x40000000
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(276) /* 0x114 */) = 1073741824 /*0x40000000*/;
    // 00423315  c780180100000000c040   -mov dword ptr [eax + 0x118], 0x40c00000
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(280) /* 0x118 */) = 1086324736 /*0x40c00000*/;
    // 0042331f  c7801c01000000000000   -mov dword ptr [eax + 0x11c], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(284) /* 0x11c */) = 0 /*0x0*/;
    // 00423329  c7802001000000000000   -mov dword ptr [eax + 0x120], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(288) /* 0x120 */) = 0 /*0x0*/;
    // 00423333  c740508fc2f53c         -mov dword ptr [eax + 0x50], 0x3cf5c28f
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(80) /* 0x50 */) = 1022739087 /*0x3cf5c28f*/;
    // 0042333a  c7800401000000000000   -mov dword ptr [eax + 0x104], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(260) /* 0x104 */) = 0 /*0x0*/;
    // 00423344  c7800801000001000000   -mov dword ptr [eax + 0x108], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(264) /* 0x108 */) = 1 /*0x1*/;
    // 0042334e  c780f400000001000000   -mov dword ptr [eax + 0xf4], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(244) /* 0xf4 */) = 1 /*0x1*/;
    // 00423358  c780f800000001000000   -mov dword ptr [eax + 0xf8], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(248) /* 0xf8 */) = 1 /*0x1*/;
    // 00423362  c780f000000001000000   -mov dword ptr [eax + 0xf0], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(240) /* 0xf0 */) = 1 /*0x1*/;
    // 0042336c  c6405b01               -mov byte ptr [eax + 0x5b], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(91) /* 0x5b */) = 1 /*0x1*/;
    // 00423370  c6405c01               -mov byte ptr [eax + 0x5c], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(92) /* 0x5c */) = 1 /*0x1*/;
    // 00423374  c6405d01               -mov byte ptr [eax + 0x5d], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(93) /* 0x5d */) = 1 /*0x1*/;
    // 00423378  c6405e01               -mov byte ptr [eax + 0x5e], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(94) /* 0x5e */) = 1 /*0x1*/;
    // 0042337c  e9be040000             -jmp 0x42383f
    goto L_0x0042383f;
  case 0x00423381:
    // 00423381  c780100100000000c040   -mov dword ptr [eax + 0x110], 0x40c00000
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(272) /* 0x110 */) = 1086324736 /*0x40c00000*/;
    // 0042338b  c7802c01000001000000   -mov dword ptr [eax + 0x12c], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(300) /* 0x12c */) = 1 /*0x1*/;
    // 00423395  c7802401000000000000   -mov dword ptr [eax + 0x124], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(292) /* 0x124 */) = 0 /*0x0*/;
    // 0042339f  c78028010000cdcc4c3e   -mov dword ptr [eax + 0x128], 0x3e4ccccd
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(296) /* 0x128 */) = 1045220557 /*0x3e4ccccd*/;
    // 004233a9  c7803001000001000000   -mov dword ptr [eax + 0x130], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(304) /* 0x130 */) = 1 /*0x1*/;
    // 004233b3  c7405000000000         -mov dword ptr [eax + 0x50], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(80) /* 0x50 */) = 0 /*0x0*/;
    // 004233ba  c7800401000000000000   -mov dword ptr [eax + 0x104], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(260) /* 0x104 */) = 0 /*0x0*/;
    // 004233c4  c7800801000000000000   -mov dword ptr [eax + 0x108], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(264) /* 0x108 */) = 0 /*0x0*/;
    // 004233ce  c780f400000000000000   -mov dword ptr [eax + 0xf4], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(244) /* 0xf4 */) = 0 /*0x0*/;
    // 004233d8  c780f000000000000000   -mov dword ptr [eax + 0xf0], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(240) /* 0xf0 */) = 0 /*0x0*/;
    // 004233e2  c780f800000001000000   -mov dword ptr [eax + 0xf8], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(248) /* 0xf8 */) = 1 /*0x1*/;
    // 004233ec  e94e040000             -jmp 0x42383f
    goto L_0x0042383f;
  case 0x004233f1:
    // 004233f1  c7801001000001000000   -mov dword ptr [eax + 0x110], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(272) /* 0x110 */) = 1 /*0x1*/;
    // 004233fb  c7405000000000         -mov dword ptr [eax + 0x50], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(80) /* 0x50 */) = 0 /*0x0*/;
    // 00423402  c7800401000000000000   -mov dword ptr [eax + 0x104], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(260) /* 0x104 */) = 0 /*0x0*/;
    // 0042340c  c7800801000000000000   -mov dword ptr [eax + 0x108], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(264) /* 0x108 */) = 0 /*0x0*/;
    // 00423416  c780f400000000000000   -mov dword ptr [eax + 0xf4], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(244) /* 0xf4 */) = 0 /*0x0*/;
    // 00423420  c780f000000000000000   -mov dword ptr [eax + 0xf0], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(240) /* 0xf0 */) = 0 /*0x0*/;
    // 0042342a  c780f800000001000000   -mov dword ptr [eax + 0xf8], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(248) /* 0xf8 */) = 1 /*0x1*/;
    // 00423434  e906040000             -jmp 0x42383f
    goto L_0x0042383f;
  case 0x00423439:
    // 00423439  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 0042343b  c7801001000000000000   -mov dword ptr [eax + 0x110], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(272) /* 0x110 */) = 0 /*0x0*/;
    // 00423445  f6052eeb550020         +test byte ptr [0x55eb2e], 0x20
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(x86::reg32(5630766) /* 0x55eb2e */) & 32 /*0x20*/));
    // 0042344c  740c                   -je 0x42345a
    if (cpu.flags.zf)
    {
        goto L_0x0042345a;
    }
    // 0042344e  c7801401000004000000   -mov dword ptr [eax + 0x114], 4
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(276) /* 0x114 */) = 4 /*0x4*/;
    // 00423458  eb43                   -jmp 0x42349d
    goto L_0x0042349d;
L_0x0042345a:
    // 0042345a  833db8d36f0000         +cmp dword ptr [0x6fd3b8], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(7328696) /* 0x6fd3b8 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00423461  751b                   -jne 0x42347e
    if (!cpu.flags.zf)
    {
        goto L_0x0042347e;
    }
    // 00423463  833db0d36f0004         +cmp dword ptr [0x6fd3b0], 4
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(7328688) /* 0x6fd3b0 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(4 /*0x4*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0042346a  7412                   -je 0x42347e
    if (cpu.flags.zf)
    {
        goto L_0x0042347e;
    }
    // 0042346c  8b35c0d46f00           -mov esi, dword ptr [0x6fd4c0]
    cpu.esi = app->getMemory<x86::reg32>(x86::reg32(7328960) /* 0x6fd4c0 */);
    // 00423472  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 00423474  7508                   -jne 0x42347e
    if (!cpu.flags.zf)
    {
        goto L_0x0042347e;
    }
    // 00423476  89b014010000           -mov dword ptr [eax + 0x114], esi
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(276) /* 0x114 */) = cpu.esi;
    // 0042347c  eb1f                   -jmp 0x42349d
    goto L_0x0042349d;
L_0x0042347e:
    // 0042347e  833dc0d46f0000         +cmp dword ptr [0x6fd4c0], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(7328960) /* 0x6fd4c0 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00423485  740c                   -je 0x423493
    if (cpu.flags.zf)
    {
        goto L_0x00423493;
    }
    // 00423487  c7811401000005000000   -mov dword ptr [ecx + 0x114], 5
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(276) /* 0x114 */) = 5 /*0x5*/;
    // 00423491  eb0a                   -jmp 0x42349d
    goto L_0x0042349d;
L_0x00423493:
    // 00423493  c7811401000004000000   -mov dword ptr [ecx + 0x114], 4
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(276) /* 0x114 */) = 4 /*0x4*/;
L_0x0042349d:
    // 0042349d  c7811c01000000000000   -mov dword ptr [ecx + 0x11c], 0
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(284) /* 0x11c */) = 0 /*0x0*/;
    // 004234a7  c78118010000ffffffff   -mov dword ptr [ecx + 0x118], 0xffffffff
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(280) /* 0x118 */) = 4294967295 /*0xffffffff*/;
    // 004234b1  c7405000000000         -mov dword ptr [eax + 0x50], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(80) /* 0x50 */) = 0 /*0x0*/;
    // 004234b8  c7800401000000000000   -mov dword ptr [eax + 0x104], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(260) /* 0x104 */) = 0 /*0x0*/;
    // 004234c2  c7800801000000000000   -mov dword ptr [eax + 0x108], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(264) /* 0x108 */) = 0 /*0x0*/;
    // 004234cc  c780f400000000000000   -mov dword ptr [eax + 0xf4], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(244) /* 0xf4 */) = 0 /*0x0*/;
    // 004234d6  c780f000000000000000   -mov dword ptr [eax + 0xf0], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(240) /* 0xf0 */) = 0 /*0x0*/;
    // 004234e0  c6405d01               -mov byte ptr [eax + 0x5d], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(93) /* 0x5d */) = 1 /*0x1*/;
    // 004234e4  c6405e01               -mov byte ptr [eax + 0x5e], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(94) /* 0x5e */) = 1 /*0x1*/;
    // 004234e8  c6405b01               -mov byte ptr [eax + 0x5b], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(91) /* 0x5b */) = 1 /*0x1*/;
    // 004234ec  c6405c01               -mov byte ptr [eax + 0x5c], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(92) /* 0x5c */) = 1 /*0x1*/;
    // 004234f0  e94a030000             -jmp 0x42383f
    goto L_0x0042383f;
  case 0x004234f5:
    // 004234f5  c7801001000000000000   -mov dword ptr [eax + 0x110], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(272) /* 0x110 */) = 0 /*0x0*/;
    // 004234ff  c7801401000000000000   -mov dword ptr [eax + 0x114], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(276) /* 0x114 */) = 0 /*0x0*/;
    // 00423509  c78018010000ffffffff   -mov dword ptr [eax + 0x118], 0xffffffff
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(280) /* 0x118 */) = 4294967295 /*0xffffffff*/;
    // 00423513  c7801c01000000000000   -mov dword ptr [eax + 0x11c], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(284) /* 0x11c */) = 0 /*0x0*/;
    // 0042351d  c7405000000000         -mov dword ptr [eax + 0x50], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(80) /* 0x50 */) = 0 /*0x0*/;
    // 00423524  c7800401000000000000   -mov dword ptr [eax + 0x104], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(260) /* 0x104 */) = 0 /*0x0*/;
    // 0042352e  c7800801000000000000   -mov dword ptr [eax + 0x108], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(264) /* 0x108 */) = 0 /*0x0*/;
    // 00423538  c780f400000001000000   -mov dword ptr [eax + 0xf4], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(244) /* 0xf4 */) = 1 /*0x1*/;
    // 00423542  c780f800000001000000   -mov dword ptr [eax + 0xf8], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(248) /* 0xf8 */) = 1 /*0x1*/;
    // 0042354c  c780f000000001000000   -mov dword ptr [eax + 0xf0], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(240) /* 0xf0 */) = 1 /*0x1*/;
    // 00423556  e9e4020000             -jmp 0x42383f
    goto L_0x0042383f;
  case 0x0042355b:
    // 0042355b  c7801001000000000000   -mov dword ptr [eax + 0x110], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(272) /* 0x110 */) = 0 /*0x0*/;
    // 00423565  c780140100000ad7233c   -mov dword ptr [eax + 0x114], 0x3c23d70a
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(276) /* 0x114 */) = 1008981770 /*0x3c23d70a*/;
    // 0042356f  c7801801000000000000   -mov dword ptr [eax + 0x118], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(280) /* 0x118 */) = 0 /*0x0*/;
    // 00423579  c7801c01000000000000   -mov dword ptr [eax + 0x11c], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(284) /* 0x11c */) = 0 /*0x0*/;
    // 00423583  c7405000000000         -mov dword ptr [eax + 0x50], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(80) /* 0x50 */) = 0 /*0x0*/;
    // 0042358a  c7800401000000000000   -mov dword ptr [eax + 0x104], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(260) /* 0x104 */) = 0 /*0x0*/;
    // 00423594  c7800801000000000000   -mov dword ptr [eax + 0x108], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(264) /* 0x108 */) = 0 /*0x0*/;
    // 0042359e  c780f400000000000000   -mov dword ptr [eax + 0xf4], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(244) /* 0xf4 */) = 0 /*0x0*/;
    // 004235a8  c780f000000000000000   -mov dword ptr [eax + 0xf0], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(240) /* 0xf0 */) = 0 /*0x0*/;
    // 004235b2  c780f800000001000000   -mov dword ptr [eax + 0xf8], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(248) /* 0xf8 */) = 1 /*0x1*/;
    // 004235bc  e97e020000             -jmp 0x42383f
    goto L_0x0042383f;
  case 0x004235c1:
    // 004235c1  c7801001000000000040   -mov dword ptr [eax + 0x110], 0x40000000
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(272) /* 0x110 */) = 1073741824 /*0x40000000*/;
    // 004235cb  c780140100000681d53e   -mov dword ptr [eax + 0x114], 0x3ed58106
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(276) /* 0x114 */) = 1054179590 /*0x3ed58106*/;
    // 004235d5  c780180100009a9919c0   -mov dword ptr [eax + 0x118], 0xc019999a
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(280) /* 0x118 */) = 3222903194 /*0xc019999a*/;
    // 004235df  c7801c01000096430b3e   -mov dword ptr [eax + 0x11c], 0x3e0b4396
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(284) /* 0x11c */) = 1040925590 /*0x3e0b4396*/;
    // 004235e9  c740500ad7233c         -mov dword ptr [eax + 0x50], 0x3c23d70a
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(80) /* 0x50 */) = 1008981770 /*0x3c23d70a*/;
    // 004235f0  c7800401000001000000   -mov dword ptr [eax + 0x104], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(260) /* 0x104 */) = 1 /*0x1*/;
    // 004235fa  c7800801000001000000   -mov dword ptr [eax + 0x108], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(264) /* 0x108 */) = 1 /*0x1*/;
    // 00423604  c780f400000000000000   -mov dword ptr [eax + 0xf4], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(244) /* 0xf4 */) = 0 /*0x0*/;
    // 0042360e  c780f000000001000000   -mov dword ptr [eax + 0xf0], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(240) /* 0xf0 */) = 1 /*0x1*/;
    // 00423618  e922020000             -jmp 0x42383f
    goto L_0x0042383f;
  case 0x0042361d:
    // 0042361d  c7801001000000000000   -mov dword ptr [eax + 0x110], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(272) /* 0x110 */) = 0 /*0x0*/;
    // 00423627  c7801401000000000040   -mov dword ptr [eax + 0x114], 0x40000000
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(276) /* 0x114 */) = 1073741824 /*0x40000000*/;
    // 00423631  c780180100009a99193f   -mov dword ptr [eax + 0x118], 0x3f19999a
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(280) /* 0x118 */) = 1058642330 /*0x3f19999a*/;
    // 0042363b  c7801c01000000000000   -mov dword ptr [eax + 0x11c], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(284) /* 0x11c */) = 0 /*0x0*/;
    // 00423645  c740507b142e3e         -mov dword ptr [eax + 0x50], 0x3e2e147b
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(80) /* 0x50 */) = 1043207291 /*0x3e2e147b*/;
    // 0042364c  c7800401000000000000   -mov dword ptr [eax + 0x104], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(260) /* 0x104 */) = 0 /*0x0*/;
    // 00423656  c7800801000001000000   -mov dword ptr [eax + 0x108], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(264) /* 0x108 */) = 1 /*0x1*/;
    // 00423660  c780f400000001000000   -mov dword ptr [eax + 0xf4], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(244) /* 0xf4 */) = 1 /*0x1*/;
    // 0042366a  c780f000000001000000   -mov dword ptr [eax + 0xf0], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(240) /* 0xf0 */) = 1 /*0x1*/;
    // 00423674  c6406401               -mov byte ptr [eax + 0x64], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(100) /* 0x64 */) = 1 /*0x1*/;
    // 00423678  c6406501               -mov byte ptr [eax + 0x65], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(101) /* 0x65 */) = 1 /*0x1*/;
    // 0042367c  c6405b01               -mov byte ptr [eax + 0x5b], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(91) /* 0x5b */) = 1 /*0x1*/;
    // 00423680  c6405f01               -mov byte ptr [eax + 0x5f], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(95) /* 0x5f */) = 1 /*0x1*/;
    // 00423684  c6406901               -mov byte ptr [eax + 0x69], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(105) /* 0x69 */) = 1 /*0x1*/;
    // 00423688  e9b2010000             -jmp 0x42383f
    goto L_0x0042383f;
  case 0x0042368d:
    // 0042368d  c78010010000000020c0   -mov dword ptr [eax + 0x110], 0xc0200000
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(272) /* 0x110 */) = 3223322624 /*0xc0200000*/;
    // 00423697  c78014010000d578a93f   -mov dword ptr [eax + 0x114], 0x3fa978d5
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(276) /* 0x114 */) = 1068071125 /*0x3fa978d5*/;
    // 004236a1  c78018010000000020c0   -mov dword ptr [eax + 0x118], 0xc0200000
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(280) /* 0x118 */) = 3223322624 /*0xc0200000*/;
    // 004236ab  c7801c01000000000000   -mov dword ptr [eax + 0x11c], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(284) /* 0x11c */) = 0 /*0x0*/;
    // 004236b5  c74050f4fd543c         -mov dword ptr [eax + 0x50], 0x3c54fdf4
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(80) /* 0x50 */) = 1012202996 /*0x3c54fdf4*/;
    // 004236bc  c7800401000000000000   -mov dword ptr [eax + 0x104], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(260) /* 0x104 */) = 0 /*0x0*/;
    // 004236c6  c7800801000001000000   -mov dword ptr [eax + 0x108], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(264) /* 0x108 */) = 1 /*0x1*/;
    // 004236d0  c780f400000001000000   -mov dword ptr [eax + 0xf4], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(244) /* 0xf4 */) = 1 /*0x1*/;
    // 004236da  c780f000000001000000   -mov dword ptr [eax + 0xf0], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(240) /* 0xf0 */) = 1 /*0x1*/;
    // 004236e4  c6406301               -mov byte ptr [eax + 0x63], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(99) /* 0x63 */) = 1 /*0x1*/;
    // 004236e8  c6406501               -mov byte ptr [eax + 0x65], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(101) /* 0x65 */) = 1 /*0x1*/;
    // 004236ec  c6405f01               -mov byte ptr [eax + 0x5f], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(95) /* 0x5f */) = 1 /*0x1*/;
    // 004236f0  c6406901               -mov byte ptr [eax + 0x69], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(105) /* 0x69 */) = 1 /*0x1*/;
    // 004236f4  e946010000             -jmp 0x42383f
    goto L_0x0042383f;
  case 0x004236f9:
    // 004236f9  c78010010000000020c0   -mov dword ptr [eax + 0x110], 0xc0200000
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(272) /* 0x110 */) = 3223322624 /*0xc0200000*/;
    // 00423703  c78014010000d578a93f   -mov dword ptr [eax + 0x114], 0x3fa978d5
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(276) /* 0x114 */) = 1068071125 /*0x3fa978d5*/;
    // 0042370d  c7801801000000002040   -mov dword ptr [eax + 0x118], 0x40200000
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(280) /* 0x118 */) = 1075838976 /*0x40200000*/;
    // 00423717  c7801c01000000000000   -mov dword ptr [eax + 0x11c], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(284) /* 0x11c */) = 0 /*0x0*/;
    // 00423721  c74050f4fd543c         -mov dword ptr [eax + 0x50], 0x3c54fdf4
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(80) /* 0x50 */) = 1012202996 /*0x3c54fdf4*/;
    // 00423728  c7800401000000000000   -mov dword ptr [eax + 0x104], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(260) /* 0x104 */) = 0 /*0x0*/;
    // 00423732  c7800801000001000000   -mov dword ptr [eax + 0x108], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(264) /* 0x108 */) = 1 /*0x1*/;
    // 0042373c  c780f400000001000000   -mov dword ptr [eax + 0xf4], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(244) /* 0xf4 */) = 1 /*0x1*/;
    // 00423746  c780f000000001000000   -mov dword ptr [eax + 0xf0], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(240) /* 0xf0 */) = 1 /*0x1*/;
    // 00423750  c6406301               -mov byte ptr [eax + 0x63], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(99) /* 0x63 */) = 1 /*0x1*/;
    // 00423754  c6406401               -mov byte ptr [eax + 0x64], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(100) /* 0x64 */) = 1 /*0x1*/;
    // 00423758  c6405f01               -mov byte ptr [eax + 0x5f], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(95) /* 0x5f */) = 1 /*0x1*/;
    // 0042375c  c6406901               -mov byte ptr [eax + 0x69], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(105) /* 0x69 */) = 1 /*0x1*/;
    // 00423760  e9da000000             -jmp 0x42383f
    goto L_0x0042383f;
  case 0x00423765:
    // 00423765  c7800401000000000000   -mov dword ptr [eax + 0x104], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(260) /* 0x104 */) = 0 /*0x0*/;
    // 0042376f  c7800801000001000000   -mov dword ptr [eax + 0x108], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(264) /* 0x108 */) = 1 /*0x1*/;
    // 00423779  c780f400000000000000   -mov dword ptr [eax + 0xf4], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(244) /* 0xf4 */) = 0 /*0x0*/;
    // 00423783  c780f000000001000000   -mov dword ptr [eax + 0xf0], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(240) /* 0xf0 */) = 1 /*0x1*/;
    // 0042378d  c780f800000001000000   -mov dword ptr [eax + 0xf8], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(248) /* 0xf8 */) = 1 /*0x1*/;
    // 00423797  c7405000000000         -mov dword ptr [eax + 0x50], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(80) /* 0x50 */) = 0 /*0x0*/;
    // 0042379e  e99c000000             -jmp 0x42383f
    goto L_0x0042383f;
  case 0x004237a3:
    // 004237a3  c780100100000000c03f   -mov dword ptr [eax + 0x110], 0x3fc00000
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(272) /* 0x110 */) = 1069547520 /*0x3fc00000*/;
    // 004237ad  c780140100000ad7a33b   -mov dword ptr [eax + 0x114], 0x3ba3d70a
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(276) /* 0x114 */) = 1000593162 /*0x3ba3d70a*/;
    // 004237b7  c7801801000001000000   -mov dword ptr [eax + 0x118], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(280) /* 0x118 */) = 1 /*0x1*/;
    // 004237c1  c7801c01000001000000   -mov dword ptr [eax + 0x11c], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(284) /* 0x11c */) = 1 /*0x1*/;
    // 004237cb  c7405000000000         -mov dword ptr [eax + 0x50], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(80) /* 0x50 */) = 0 /*0x0*/;
    // 004237d2  c7800401000000000000   -mov dword ptr [eax + 0x104], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(260) /* 0x104 */) = 0 /*0x0*/;
    // 004237dc  c7800801000001000000   -mov dword ptr [eax + 0x108], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(264) /* 0x108 */) = 1 /*0x1*/;
    // 004237e6  c780f400000000000000   -mov dword ptr [eax + 0xf4], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(244) /* 0xf4 */) = 0 /*0x0*/;
    // 004237f0  c780f000000000000000   -mov dword ptr [eax + 0xf0], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(240) /* 0xf0 */) = 0 /*0x0*/;
    // 004237fa  c780f800000001000000   -mov dword ptr [eax + 0xf8], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(248) /* 0xf8 */) = 1 /*0x1*/;
    // 00423804  eb39                   -jmp 0x42383f
    goto L_0x0042383f;
  case 0x00423806:
    // 00423806  c7800401000000000000   -mov dword ptr [eax + 0x104], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(260) /* 0x104 */) = 0 /*0x0*/;
    // 00423810  c7800801000001000000   -mov dword ptr [eax + 0x108], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(264) /* 0x108 */) = 1 /*0x1*/;
    // 0042381a  c780f400000001000000   -mov dword ptr [eax + 0xf4], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(244) /* 0xf4 */) = 1 /*0x1*/;
    // 00423824  c780f800000001000000   -mov dword ptr [eax + 0xf8], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(248) /* 0xf8 */) = 1 /*0x1*/;
    // 0042382e  c780f000000001000000   -mov dword ptr [eax + 0xf0], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(240) /* 0xf0 */) = 1 /*0x1*/;
    // 00423838  c740500000283a         -mov dword ptr [eax + 0x50], 0x3a280000
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(80) /* 0x50 */) = 975699968 /*0x3a280000*/;
  [[fallthrough]];
  case 0x0042383f:
L_0x0042383f:
    // 0042383f  42                     -inc edx
    (cpu.edx)++;
    // 00423840  83fa19                 +cmp edx, 0x19
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(25 /*0x19*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00423843  7d20                   -jge 0x423865
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00423865;
    }
L_0x00423845:
    // 00423845  8d0c9d00000000         -lea ecx, [ebx*4]
    cpu.ecx = x86::reg32(cpu.ebx * 4);
    // 0042384c  8b84d1c82e5500         -mov eax, dword ptr [ecx + edx*8 + 0x552ec8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(5582536) /* 0x552ec8 */ + cpu.edx * 8);
    // 00423853  8b4dfc                 -mov ecx, dword ptr [ebp - 4]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00423856  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    // 00423858  0f8444f5ffff           -je 0x422da2
    if (cpu.flags.zf)
    {
        goto L_0x00422da2;
    }
    // 0042385e  89d9                   -mov ecx, ebx
    cpu.ecx = cpu.ebx;
    // 00423860  e943f5ffff             -jmp 0x422da8
    goto L_0x00422da8;
L_0x00423865:
    // 00423865  43                     +inc ebx
    {
        x86::reg32& tmp = cpu.ebx;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 00423866  e9f6f4ffff             -jmp 0x422d61
    goto L_0x00422d61;
L_0x0042386b:
    // 0042386b  ba1e000000             -mov edx, 0x1e
    cpu.edx = 30 /*0x1e*/;
    // 00423870  b803000000             -mov eax, 3
    cpu.eax = 3 /*0x3*/;
    // 00423875  e826c7ffff             -call 0x41ffa0
    cpu.esp -= 4;
    nfs3hp::trackdata::setLaneOffsets(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042387a  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 0042387c  a304305500             -mov dword ptr [0x553004], eax
    app->getMemory<x86::reg32>(x86::reg32(5582852) /* 0x553004 */) = cpu.eax;
    // 00423881  a308305500             -mov dword ptr [0x553008], eax
    app->getMemory<x86::reg32>(x86::reg32(5582856) /* 0x553008 */) = cpu.eax;
    // 00423886  a30c305500             -mov dword ptr [0x55300c], eax
    app->getMemory<x86::reg32>(x86::reg32(5582860) /* 0x55300c */) = cpu.eax;
    // 0042388b  a310305500             -mov dword ptr [0x553010], eax
    app->getMemory<x86::reg32>(x86::reg32(5582864) /* 0x553010 */) = cpu.eax;
    // 00423890  a314305500             -mov dword ptr [0x553014], eax
    app->getMemory<x86::reg32>(x86::reg32(5582868) /* 0x553014 */) = cpu.eax;
    // 00423895  a318305500             -mov dword ptr [0x553018], eax
    app->getMemory<x86::reg32>(x86::reg32(5582872) /* 0x553018 */) = cpu.eax;
    // 0042389a  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 0042389c  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042389d  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042389e  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042389f  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004238a0  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004238a1  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004238a2  c3                     -ret 
    cpu.esp += 4;
    return;
  default:
    NFS2_ASSERT(false);
  }
}

/* align: skip 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 */
void Application::sub_4238b0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004238b0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004238b1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004238b2  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004238b3  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004238b4  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004238b5  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004238b7  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 004238b9  89d1                   -mov ecx, edx
    cpu.ecx = cpu.edx;
    // 004238bb  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 004238be  8b90b8105e00           -mov edx, dword ptr [eax + 0x5e10b8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164664) /* 0x5e10b8 */);
    // 004238c4  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 004238c6  740a                   -je 0x4238d2
    if (cpu.flags.zf)
    {
        goto L_0x004238d2;
    }
    // 004238c8  7404                   -je 0x4238ce
    if (cpu.flags.zf)
    {
        goto L_0x004238ce;
    }
    // 004238ca  8b02                   -mov eax, dword ptr [edx]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edx);
    // 004238cc  eb14                   -jmp 0x4238e2
    goto L_0x004238e2;
L_0x004238ce:
    // 004238ce  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
    // 004238d0  eb10                   -jmp 0x4238e2
    goto L_0x004238e2;
L_0x004238d2:
    // 004238d2  8bb8b0105e00           -mov edi, dword ptr [eax + 0x5e10b0]
    cpu.edi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164656) /* 0x5e10b0 */);
    // 004238d8  85ff                   +test edi, edi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edi & cpu.edi));
    // 004238da  7404                   -je 0x4238e0
    if (cpu.flags.zf)
    {
        goto L_0x004238e0;
    }
    // 004238dc  8b07                   -mov eax, dword ptr [edi]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edi);
    // 004238de  eb02                   -jmp 0x4238e2
    goto L_0x004238e2;
L_0x004238e0:
    // 004238e0  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
L_0x004238e2:
    // 004238e2  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004238e4  83f913                 +cmp ecx, 0x13
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(19 /*0x13*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004238e7  7414                   -je 0x4238fd
    if (cpu.flags.zf)
    {
        goto L_0x004238fd;
    }
    // 004238e9  83f813                 +cmp eax, 0x13
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(19 /*0x13*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004238ec  740f                   -je 0x4238fd
    if (cpu.flags.zf)
    {
        goto L_0x004238fd;
    }
    // 004238ee  39c8                   +cmp eax, ecx
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
    // 004238f0  740b                   -je 0x4238fd
    if (cpu.flags.zf)
    {
        goto L_0x004238fd;
    }
    // 004238f2  c7049df42f550001000000 -mov dword ptr [ebx*4 + 0x552ff4], 1
    app->getMemory<x86::reg32>(x86::reg32(5582836) /* 0x552ff4 */ + cpu.ebx * 4) = 1 /*0x1*/;
L_0x004238fd:
    // 004238fd  83f904                 +cmp ecx, 4
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
    // 00423900  740f                   -je 0x423911
    if (cpu.flags.zf)
    {
        goto L_0x00423911;
    }
    // 00423902  83f903                 +cmp ecx, 3
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(3 /*0x3*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00423905  740a                   -je 0x423911
    if (cpu.flags.zf)
    {
        goto L_0x00423911;
    }
    // 00423907  83f906                 +cmp ecx, 6
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(6 /*0x6*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0042390a  7405                   -je 0x423911
    if (cpu.flags.zf)
    {
        goto L_0x00423911;
    }
    // 0042390c  83f905                 +cmp ecx, 5
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(5 /*0x5*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0042390f  752e                   -jne 0x42393f
    if (!cpu.flags.zf)
    {
        goto L_0x0042393f;
    }
L_0x00423911:
    // 00423911  83fa13                 +cmp edx, 0x13
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(19 /*0x13*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00423914  750b                   -jne 0x423921
    if (!cpu.flags.zf)
    {
        goto L_0x00423921;
    }
    // 00423916  89da                   -mov edx, ebx
    cpu.edx = cpu.ebx;
    // 00423918  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 0042391a  e8312b0000             -call 0x426450
    cpu.esp -= 4;
    sub_426450(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042391f  eb1e                   -jmp 0x42393f
    goto L_0x0042393f;
L_0x00423921:
    // 00423921  ba01000000             -mov edx, 1
    cpu.edx = 1 /*0x1*/;
    // 00423926  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00423928  8914dd10105e00         -mov dword ptr [ebx*8 + 0x5e1010], edx
    app->getMemory<x86::reg32>(x86::reg32(6164496) /* 0x5e1010 */ + cpu.ebx * 8) = cpu.edx;
    // 0042392f  89da                   -mov edx, ebx
    cpu.edx = cpu.ebx;
    // 00423931  31f6                   -xor esi, esi
    cpu.esi ^= x86::reg32(x86::sreg32(cpu.esi));
    // 00423933  e8182b0000             -call 0x426450
    cpu.esp -= 4;
    sub_426450(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00423938  8934dd10105e00         -mov dword ptr [ebx*8 + 0x5e1010], esi
    app->getMemory<x86::reg32>(x86::reg32(6164496) /* 0x5e1010 */ + cpu.ebx * 8) = cpu.esi;
L_0x0042393f:
    // 0042393f  8d049d00000000         -lea eax, [ebx*4]
    cpu.eax = x86::reg32(cpu.ebx * 4);
    // 00423946  8b94c8c82e5500         -mov edx, dword ptr [eax + ecx*8 + 0x552ec8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(5582536) /* 0x552ec8 */ + cpu.ecx * 8);
    // 0042394d  8990b0105e00           -mov dword ptr [eax + 0x5e10b0], edx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164656) /* 0x5e10b0 */) = cpu.edx;
    // 00423953  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00423954  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00423955  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00423956  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00423957  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00423958  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x90 */
void Application::sub_423960(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00423960  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00423961  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00423962  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00423963  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00423964  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00423965  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00423967  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 00423969  89d1                   -mov ecx, edx
    cpu.ecx = cpu.edx;
    // 0042396b  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 0042396e  8b90b8105e00           -mov edx, dword ptr [eax + 0x5e10b8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164664) /* 0x5e10b8 */);
    // 00423974  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 00423976  740a                   -je 0x423982
    if (cpu.flags.zf)
    {
        goto L_0x00423982;
    }
    // 00423978  7404                   -je 0x42397e
    if (cpu.flags.zf)
    {
        goto L_0x0042397e;
    }
    // 0042397a  8b02                   -mov eax, dword ptr [edx]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edx);
    // 0042397c  eb14                   -jmp 0x423992
    goto L_0x00423992;
L_0x0042397e:
    // 0042397e  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
    // 00423980  eb10                   -jmp 0x423992
    goto L_0x00423992;
L_0x00423982:
    // 00423982  8bb8b0105e00           -mov edi, dword ptr [eax + 0x5e10b0]
    cpu.edi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164656) /* 0x5e10b0 */);
    // 00423988  85ff                   +test edi, edi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edi & cpu.edi));
    // 0042398a  7404                   -je 0x423990
    if (cpu.flags.zf)
    {
        goto L_0x00423990;
    }
    // 0042398c  8b07                   -mov eax, dword ptr [edi]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edi);
    // 0042398e  eb02                   -jmp 0x423992
    goto L_0x00423992;
L_0x00423990:
    // 00423990  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
L_0x00423992:
    // 00423992  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 00423994  8d049d00000000         -lea eax, [ebx*4]
    cpu.eax = x86::reg32(cpu.ebx * 4);
    // 0042399b  8bb0b8105e00           -mov esi, dword ptr [eax + 0x5e10b8]
    cpu.esi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164664) /* 0x5e10b8 */);
    // 004239a1  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 004239a3  7404                   -je 0x4239a9
    if (cpu.flags.zf)
    {
        goto L_0x004239a9;
    }
    // 004239a5  8b06                   -mov eax, dword ptr [esi]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi);
    // 004239a7  eb02                   -jmp 0x4239ab
    goto L_0x004239ab;
L_0x004239a9:
    // 004239a9  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
L_0x004239ab:
    // 004239ab  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    // 004239ad  7504                   -jne 0x4239b3
    if (!cpu.flags.zf)
    {
        goto L_0x004239b3;
    }
    // 004239af  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004239b1  7419                   -je 0x4239cc
    if (cpu.flags.zf)
    {
        goto L_0x004239cc;
    }
L_0x004239b3:
    // 004239b3  83f913                 +cmp ecx, 0x13
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(19 /*0x13*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004239b6  7414                   -je 0x4239cc
    if (cpu.flags.zf)
    {
        goto L_0x004239cc;
    }
    // 004239b8  83fa13                 +cmp edx, 0x13
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(19 /*0x13*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004239bb  740f                   -je 0x4239cc
    if (cpu.flags.zf)
    {
        goto L_0x004239cc;
    }
    // 004239bd  39ca                   +cmp edx, ecx
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
    // 004239bf  740b                   -je 0x4239cc
    if (cpu.flags.zf)
    {
        goto L_0x004239cc;
    }
    // 004239c1  c7049df42f550001000000 -mov dword ptr [ebx*4 + 0x552ff4], 1
    app->getMemory<x86::reg32>(x86::reg32(5582836) /* 0x552ff4 */ + cpu.ebx * 4) = 1 /*0x1*/;
L_0x004239cc:
    // 004239cc  83f904                 +cmp ecx, 4
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
    // 004239cf  740f                   -je 0x4239e0
    if (cpu.flags.zf)
    {
        goto L_0x004239e0;
    }
    // 004239d1  83f903                 +cmp ecx, 3
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(3 /*0x3*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004239d4  740a                   -je 0x4239e0
    if (cpu.flags.zf)
    {
        goto L_0x004239e0;
    }
    // 004239d6  83f906                 +cmp ecx, 6
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(6 /*0x6*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004239d9  7405                   -je 0x4239e0
    if (cpu.flags.zf)
    {
        goto L_0x004239e0;
    }
    // 004239db  83f905                 +cmp ecx, 5
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(5 /*0x5*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004239de  751e                   -jne 0x4239fe
    if (!cpu.flags.zf)
    {
        goto L_0x004239fe;
    }
L_0x004239e0:
    // 004239e0  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 004239e5  89da                   -mov edx, ebx
    cpu.edx = cpu.ebx;
    // 004239e7  8904dd10105e00         -mov dword ptr [ebx*8 + 0x5e1010], eax
    app->getMemory<x86::reg32>(x86::reg32(6164496) /* 0x5e1010 */ + cpu.ebx * 8) = cpu.eax;
    // 004239ee  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004239f0  e85b2a0000             -call 0x426450
    cpu.esp -= 4;
    sub_426450(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004239f5  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 004239f7  8914dd10105e00         -mov dword ptr [ebx*8 + 0x5e1010], edx
    app->getMemory<x86::reg32>(x86::reg32(6164496) /* 0x5e1010 */ + cpu.ebx * 8) = cpu.edx;
L_0x004239fe:
    // 004239fe  8d049d00000000         -lea eax, [ebx*4]
    cpu.eax = x86::reg32(cpu.ebx * 4);
    // 00423a05  8b94c8c82e5500         -mov edx, dword ptr [eax + ecx*8 + 0x552ec8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(5582536) /* 0x552ec8 */ + cpu.ecx * 8);
    // 00423a0c  8990b8105e00           -mov dword ptr [eax + 0x5e10b8], edx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164664) /* 0x5e10b8 */) = cpu.edx;
    // 00423a12  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00423a13  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00423a14  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00423a15  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00423a16  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00423a17  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8b 0xd2 */
void Application::sub_423a20(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00423a20  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00423a21  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00423a22  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00423a23  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00423a25  8b15c0105e00           -mov edx, dword ptr [0x5e10c0]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(6164672) /* 0x5e10c0 */);
    // 00423a2b  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00423a2d  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00423a2f  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    // 00423a31  7402                   -je 0x423a35
    if (cpu.flags.zf)
    {
        goto L_0x00423a35;
    }
    // 00423a33  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
L_0x00423a35:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00423a35  83fa04                 +cmp edx, 4
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
    // 00423a38  7d0d                   -jge 0x423a47
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00423a47;
    }
    // 00423a3a  833c95c0bb6f0000       +cmp dword ptr [edx*4 + 0x6fbbc0], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(7322560) /* 0x6fbbc0 */ + cpu.edx * 4);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00423a42  7503                   -jne 0x423a47
    if (!cpu.flags.zf)
    {
        goto L_0x00423a47;
    }
    // 00423a44  42                     +inc edx
    {
        x86::reg32& tmp = cpu.edx;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 00423a45  ebee                   -jmp 0x423a35
    goto L_0x00423a35;
L_0x00423a47:
    // 00423a47  83fa04                 +cmp edx, 4
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
    // 00423a4a  7d08                   -jge 0x423a54
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00423a54;
    }
    // 00423a4c  42                     -inc edx
    (cpu.edx)++;
    // 00423a4d  8b0495bcbb6f00         -mov eax, dword ptr [edx*4 + 0x6fbbbc]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(7322556) /* 0x6fbbbc */ + cpu.edx * 4);
L_0x00423a54:
    // 00423a54  8915c0105e00           -mov dword ptr [0x5e10c0], edx
    app->getMemory<x86::reg32>(x86::reg32(6164672) /* 0x5e10c0 */) = cpu.edx;
    // 00423a5a  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00423a5b  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00423a5c  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00423a5d  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8b 0xc0 */
void Application::sub_423a60(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00423a60  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00423a61  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00423a62  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00423a64  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 00423a69  e8b2ffffff             -call 0x423a20
    cpu.esp -= 4;
    sub_423a20(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00423a6e  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 00423a70  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00423a72  7505                   -jne 0x423a79
    if (!cpu.flags.zf)
    {
        goto L_0x00423a79;
    }
    // 00423a74  ba02000000             -mov edx, 2
    cpu.edx = 2 /*0x2*/;
L_0x00423a79:
    // 00423a79  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00423a7b  40                     -inc eax
    (cpu.eax)++;
    // 00423a7c  89148538105e00         -mov dword ptr [eax*4 + 0x5e1038], edx
    app->getMemory<x86::reg32>(x86::reg32(6164536) /* 0x5e1038 */ + cpu.eax * 4) = cpu.edx;
L_0x00423a83:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00423a83  83f819                 +cmp eax, 0x19
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(25 /*0x19*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00423a86  7d0a                   -jge 0x423a92
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00423a92;
    }
    // 00423a88  40                     +inc eax
    {
        x86::reg32& tmp = cpu.eax;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 00423a89  89148538105e00         -mov dword ptr [eax*4 + 0x5e1038], edx
    app->getMemory<x86::reg32>(x86::reg32(6164536) /* 0x5e1038 */ + cpu.eax * 4) = cpu.edx;
    // 00423a90  ebf1                   -jmp 0x423a83
    goto L_0x00423a83;
L_0x00423a92:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00423a92  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00423a94  e887ffffff             -call 0x423a20
    cpu.esp -= 4;
    sub_423a20(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00423a99  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00423a9b  740b                   -je 0x423aa8
    if (cpu.flags.zf)
    {
        goto L_0x00423aa8;
    }
    // 00423a9d  8904953c105e00         -mov dword ptr [edx*4 + 0x5e103c], eax
    app->getMemory<x86::reg32>(x86::reg32(6164540) /* 0x5e103c */ + cpu.edx * 4) = cpu.eax;
    // 00423aa4  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 00423aa6  ebea                   -jmp 0x423a92
    goto L_0x00423a92;
L_0x00423aa8:
    // 00423aa8  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00423aa9  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00423aaa  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x40 0x00 0x8b 0xc9 */
void Application::sub_423ab0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00423ab0  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00423ab1  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00423ab2  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00423ab3  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00423ab5  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00423ab7  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00423ab9  31d2                   +xor edx, edx
    cpu.clear_co();
    cpu.set_szp((cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx))));
    // 00423abb  eb05                   -jmp 0x423ac2
    goto L_0x00423ac2;
L_0x00423abd:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00423abd  83f819                 +cmp eax, 0x19
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(25 /*0x19*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00423ac0  7d11                   -jge 0x423ad3
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00423ad3;
    }
L_0x00423ac2:
    // 00423ac2  3b0c853c105e00         +cmp ecx, dword ptr [eax*4 + 0x5e103c]
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(6164540) /* 0x5e103c */ + cpu.eax * 4)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00423ac9  7505                   -jne 0x423ad0
    if (!cpu.flags.zf)
    {
        goto L_0x00423ad0;
    }
    // 00423acb  ba01000000             -mov edx, 1
    cpu.edx = 1 /*0x1*/;
L_0x00423ad0:
    // 00423ad0  40                     +inc eax
    {
        x86::reg32& tmp = cpu.eax;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 00423ad1  ebea                   -jmp 0x423abd
    goto L_0x00423abd;
L_0x00423ad3:
    // 00423ad3  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 00423ad5  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00423ad6  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00423ad7  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00423ad8  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x90 */
void Application::sub_423ae0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00423ae0  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00423ae1  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00423ae2  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00423ae4  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00423ae6  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 00423ae8  e8c3ffffff             -call 0x423ab0
    cpu.esp -= 4;
    sub_423ab0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00423aed  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00423aef  7407                   -je 0x423af8
    if (cpu.flags.zf)
    {
        goto L_0x00423af8;
    }
    // 00423af1  89148db8bb6f00         -mov dword ptr [ecx*4 + 0x6fbbb8], edx
    app->getMemory<x86::reg32>(x86::reg32(7322552) /* 0x6fbbb8 */ + cpu.ecx * 4) = cpu.edx;
L_0x00423af8:
    // 00423af8  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00423af9  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00423afa  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x40 0x00 0x8b 0xc9 */
void Application::sub_423b00(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00423b00  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00423b01  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00423b02  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00423b03  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00423b04  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00423b06  8b15b0d36f00           -mov edx, dword ptr [0x6fd3b0]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(7328688) /* 0x6fd3b0 */);
    // 00423b0c  83fa01                 +cmp edx, 1
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
    // 00423b0f  7504                   -jne 0x423b15
    if (!cpu.flags.zf)
    {
        goto L_0x00423b15;
    }
    // 00423b11  21d0                   +and eax, edx
    cpu.clear_co();
    cpu.set_szp((cpu.eax &= x86::reg32(x86::sreg32(cpu.edx))));
    // 00423b13  eb02                   -jmp 0x423b17
    goto L_0x00423b17;
L_0x00423b15:
    // 00423b15  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
L_0x00423b17:
    // 00423b17  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 00423b1a  8b88b8105e00           -mov ecx, dword ptr [eax + 0x5e10b8]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164664) /* 0x5e10b8 */);
    // 00423b20  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    // 00423b22  7410                   -je 0x423b34
    if (cpu.flags.zf)
    {
        goto L_0x00423b34;
    }
    // 00423b24  7407                   -je 0x423b2d
    if (cpu.flags.zf)
    {
        goto L_0x00423b2d;
    }
    // 00423b26  8b01                   -mov eax, dword ptr [ecx]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx);
    // 00423b28  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00423b29  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00423b2a  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00423b2b  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00423b2c  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x00423b2d:
    // 00423b2d  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00423b2f  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00423b30  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00423b31  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00423b32  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00423b33  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x00423b34:
    // 00423b34  8bb0b0105e00           -mov esi, dword ptr [eax + 0x5e10b0]
    cpu.esi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164656) /* 0x5e10b0 */);
    // 00423b3a  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 00423b3c  7407                   -je 0x423b45
    if (cpu.flags.zf)
    {
        goto L_0x00423b45;
    }
    // 00423b3e  8b06                   -mov eax, dword ptr [esi]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi);
    // 00423b40  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00423b41  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00423b42  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00423b43  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00423b44  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x00423b45:
    // 00423b45  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00423b47  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00423b48  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00423b49  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00423b4a  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00423b4b  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x44 0x20 0x00 */
void Application::sub_423b50(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00423b50  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00423b51  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00423b52  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00423b53  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00423b55  8b0db0d36f00           -mov ecx, dword ptr [0x6fd3b0]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(7328688) /* 0x6fd3b0 */);
    // 00423b5b  83f901                 +cmp ecx, 1
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1 /*0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00423b5e  7504                   -jne 0x423b64
    if (!cpu.flags.zf)
    {
        goto L_0x00423b64;
    }
    // 00423b60  21c8                   +and eax, ecx
    cpu.clear_co();
    cpu.set_szp((cpu.eax &= x86::reg32(x86::sreg32(cpu.ecx))));
    // 00423b62  eb02                   -jmp 0x423b66
    goto L_0x00423b66;
L_0x00423b64:
    // 00423b64  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
L_0x00423b66:
    // 00423b66  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
    // 00423b68  891dec005600           -mov dword ptr [0x5600ec], ebx
    app->getMemory<x86::reg32>(x86::reg32(5636332) /* 0x5600ec */) = cpu.ebx;
    // 00423b6e  e83dfdffff             -call 0x4238b0
    cpu.esp -= 4;
    sub_4238b0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00423b73  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00423b74  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00423b75  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00423b76  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 */
void Application::sub_423b80(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00423b80  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00423b81  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00423b82  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00423b83  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00423b84  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00423b85  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00423b86  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00423b88  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00423b8a  833db0d36f0001         +cmp dword ptr [0x6fd3b0], 1
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(7328688) /* 0x6fd3b0 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1 /*0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00423b91  7405                   -je 0x423b98
    if (cpu.flags.zf)
    {
        goto L_0x00423b98;
    }
    // 00423b93  a1f4d46f00             -mov eax, dword ptr [0x6fd4f4]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(7329012) /* 0x6fd4f4 */);
L_0x00423b98:
    // 00423b98  8b35b0d36f00           -mov esi, dword ptr [0x6fd3b0]
    cpu.esi = app->getMemory<x86::reg32>(x86::reg32(7328688) /* 0x6fd3b0 */);
    // 00423b9e  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 00423ba0  83fe01                 +cmp esi, 1
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
    // 00423ba3  7504                   -jne 0x423ba9
    if (!cpu.flags.zf)
    {
        goto L_0x00423ba9;
    }
    // 00423ba5  21f1                   +and ecx, esi
    cpu.clear_co();
    cpu.set_szp((cpu.ecx &= x86::reg32(x86::sreg32(cpu.esi))));
    // 00423ba7  eb02                   -jmp 0x423bab
    goto L_0x00423bab;
L_0x00423ba9:
    // 00423ba9  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
L_0x00423bab:
    // 00423bab  8d048d00000000         -lea eax, [ecx*4]
    cpu.eax = x86::reg32(cpu.ecx * 4);
    // 00423bb2  8bb8b0105e00           -mov edi, dword ptr [eax + 0x5e10b0]
    cpu.edi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164656) /* 0x5e10b0 */);
    // 00423bb8  85ff                   +test edi, edi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edi & cpu.edi));
    // 00423bba  740b                   -je 0x423bc7
    if (cpu.flags.zf)
    {
        goto L_0x00423bc7;
    }
    // 00423bbc  8b07                   -mov eax, dword ptr [edi]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edi);
    // 00423bbe  83f810                 +cmp eax, 0x10
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
    // 00423bc1  0f8477010000           -je 0x423d3e
    if (cpu.flags.zf)
    {
        goto L_0x00423d3e;
    }
L_0x00423bc7:
    // 00423bc7  8b048db0105e00         -mov eax, dword ptr [ecx*4 + 0x5e10b0]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(6164656) /* 0x5e10b0 */ + cpu.ecx * 4);
    // 00423bce  8b349dc8fa5e00         -mov esi, dword ptr [ebx*4 + 0x5efac8]
    cpu.esi = app->getMemory<x86::reg32>(x86::reg32(6224584) /* 0x5efac8 */ + cpu.ebx * 4);
    // 00423bd5  3b7008                 +cmp esi, dword ptr [eax + 8]
    {
        x86::reg32 tmp1 = cpu.esi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00423bd8  0f8560010000           -jne 0x423d3e
    if (!cpu.flags.zf)
    {
        goto L_0x00423d3e;
    }
    // 00423bde  833db0d36f0001         +cmp dword ptr [0x6fd3b0], 1
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(7328688) /* 0x6fd3b0 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1 /*0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00423be5  7e19                   -jle 0x423c00
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00423c00;
    }
    // 00423be7  8b00                   -mov eax, dword ptr [eax]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax);
    // 00423be9  83f811                 +cmp eax, 0x11
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(17 /*0x11*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00423bec  7512                   -jne 0x423c00
    if (!cpu.flags.zf)
    {
        goto L_0x00423c00;
    }
    // 00423bee  8b1554105e00           -mov edx, dword ptr [0x5e1054]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(6164564) /* 0x5e1054 */);
    // 00423bf4  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00423bf6  e855ffffff             -call 0x423b50
    cpu.esp -= 4;
    sub_423b50(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00423bfb  e9a9000000             -jmp 0x423ca9
    goto L_0x00423ca9;
L_0x00423c00:
    // 00423c00  833db0d36f0001         +cmp dword ptr [0x6fd3b0], 1
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(7328688) /* 0x6fd3b0 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1 /*0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00423c07  7542                   -jne 0x423c4b
    if (!cpu.flags.zf)
    {
        goto L_0x00423c4b;
    }
    // 00423c09  8d048d00000000         -lea eax, [ecx*4]
    cpu.eax = x86::reg32(cpu.ecx * 4);
    // 00423c10  8b9048fa5e00           -mov edx, dword ptr [eax + 0x5efa48]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6224456) /* 0x5efa48 */);
    // 00423c16  f6820002000001         +test byte ptr [edx + 0x200], 1
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(cpu.edx + x86::reg32(512) /* 0x200 */) & 1 /*0x1*/));
    // 00423c1d  742c                   -je 0x423c4b
    if (cpu.flags.zf)
    {
        goto L_0x00423c4b;
    }
    // 00423c1f  83bac402000003         +cmp dword ptr [edx + 0x2c4], 3
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(708) /* 0x2c4 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(3 /*0x3*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00423c26  7523                   -jne 0x423c4b
    if (!cpu.flags.zf)
    {
        goto L_0x00423c4b;
    }
    // 00423c28  8bb0b0105e00           -mov esi, dword ptr [eax + 0x5e10b0]
    cpu.esi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164656) /* 0x5e10b0 */);
    // 00423c2e  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 00423c30  7404                   -je 0x423c36
    if (cpu.flags.zf)
    {
        goto L_0x00423c36;
    }
    // 00423c32  8b06                   -mov eax, dword ptr [esi]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi);
    // 00423c34  eb02                   -jmp 0x423c38
    goto L_0x00423c38;
L_0x00423c36:
    // 00423c36  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
L_0x00423c38:
    // 00423c38  8b1485902f5500         -mov edx, dword ptr [eax*4 + 0x552f90]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5582736) /* 0x552f90 */ + cpu.eax * 4);
    // 00423c3f  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00423c41  e80affffff             -call 0x423b50
    cpu.esp -= 4;
    sub_423b50(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00423c46  e95e000000             -jmp 0x423ca9
    goto L_0x00423ca9;
L_0x00423c4b:
    // 00423c4b  8d048d00000000         -lea eax, [ecx*4]
    cpu.eax = x86::reg32(cpu.ecx * 4);
    // 00423c52  8bb8b0105e00           -mov edi, dword ptr [eax + 0x5e10b0]
    cpu.edi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164656) /* 0x5e10b0 */);
    // 00423c58  85ff                   +test edi, edi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edi & cpu.edi));
    // 00423c5a  7407                   -je 0x423c63
    if (cpu.flags.zf)
    {
        goto L_0x00423c63;
    }
    // 00423c5c  8b07                   -mov eax, dword ptr [edi]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edi);
    // 00423c5e  83f813                 +cmp eax, 0x13
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(19 /*0x13*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00423c61  7446                   -je 0x423ca9
    if (cpu.flags.zf)
    {
        goto L_0x00423ca9;
    }
L_0x00423c63:
    // 00423c63  8d048d00000000         -lea eax, [ecx*4]
    cpu.eax = x86::reg32(cpu.ecx * 4);
    // 00423c6a  8b90b0105e00           -mov edx, dword ptr [eax + 0x5e10b0]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164656) /* 0x5e10b0 */);
    // 00423c70  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 00423c72  7404                   -je 0x423c78
    if (cpu.flags.zf)
    {
        goto L_0x00423c78;
    }
    // 00423c74  8b02                   -mov eax, dword ptr [edx]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edx);
    // 00423c76  eb02                   -jmp 0x423c7a
    goto L_0x00423c7a;
L_0x00423c78:
    // 00423c78  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
L_0x00423c7a:
    // 00423c7a  8b1c853c105e00         -mov ebx, dword ptr [eax*4 + 0x5e103c]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(6164540) /* 0x5e103c */ + cpu.eax * 4);
    // 00423c81  89ca                   -mov edx, ecx
    cpu.edx = cpu.ecx;
    // 00423c83  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 00423c85  e886e9ffff             -call 0x422610
    cpu.esp -= 4;
    sub_422610(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00423c8a  8d048d00000000         -lea eax, [ecx*4]
    cpu.eax = x86::reg32(cpu.ecx * 4);
    // 00423c91  8bb0b0105e00           -mov esi, dword ptr [eax + 0x5e10b0]
    cpu.esi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164656) /* 0x5e10b0 */);
    // 00423c97  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 00423c99  740e                   -je 0x423ca9
    if (cpu.flags.zf)
    {
        goto L_0x00423ca9;
    }
    // 00423c9b  8b06                   -mov eax, dword ptr [esi]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi);
    // 00423c9d  83f813                 +cmp eax, 0x13
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(19 /*0x13*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00423ca0  7507                   -jne 0x423ca9
    if (!cpu.flags.zf)
    {
        goto L_0x00423ca9;
    }
    // 00423ca2  89da                   -mov edx, ebx
    cpu.edx = cpu.ebx;
    // 00423ca4  e98e000000             -jmp 0x423d37
    goto L_0x00423d37;
L_0x00423ca9:
    // 00423ca9  8d048d00000000         -lea eax, [ecx*4]
    cpu.eax = x86::reg32(cpu.ecx * 4);
    // 00423cb0  8bb8b0105e00           -mov edi, dword ptr [eax + 0x5e10b0]
    cpu.edi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164656) /* 0x5e10b0 */);
    // 00423cb6  85ff                   +test edi, edi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edi & cpu.edi));
    // 00423cb8  7416                   -je 0x423cd0
    if (cpu.flags.zf)
    {
        goto L_0x00423cd0;
    }
    // 00423cba  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 00423cbc  8b17                   -mov edx, dword ptr [edi]
    cpu.edx = app->getMemory<x86::reg32>(cpu.edi);
    // 00423cbe  83fa13                 +cmp edx, 0x13
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(19 /*0x13*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00423cc1  750d                   -jne 0x423cd0
    if (!cpu.flags.zf)
    {
        goto L_0x00423cd0;
    }
    // 00423cc3  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00423cc5  8b971c010000           -mov edx, dword ptr [edi + 0x11c]
    cpu.edx = app->getMemory<x86::reg32>(cpu.edi + x86::reg32(284) /* 0x11c */);
    // 00423ccb  e880feffff             -call 0x423b50
    cpu.esp -= 4;
    sub_423b50(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00423cd0:
    // 00423cd0  8d048d00000000         -lea eax, [ecx*4]
    cpu.eax = x86::reg32(cpu.ecx * 4);
    // 00423cd7  8b90b0105e00           -mov edx, dword ptr [eax + 0x5e10b0]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164656) /* 0x5e10b0 */);
    // 00423cdd  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 00423cdf  7414                   -je 0x423cf5
    if (cpu.flags.zf)
    {
        goto L_0x00423cf5;
    }
    // 00423ce1  8b02                   -mov eax, dword ptr [edx]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edx);
    // 00423ce3  83f806                 +cmp eax, 6
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
    // 00423ce6  7e0d                   -jle 0x423cf5
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00423cf5;
    }
    // 00423ce8  8b1554105e00           -mov edx, dword ptr [0x5e1054]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(6164564) /* 0x5e1054 */);
    // 00423cee  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00423cf0  e8bbfbffff             -call 0x4238b0
    cpu.esp -= 4;
    sub_4238b0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00423cf5:
    // 00423cf5  8d048d00000000         -lea eax, [ecx*4]
    cpu.eax = x86::reg32(cpu.ecx * 4);
    // 00423cfc  8b98b0105e00           -mov ebx, dword ptr [eax + 0x5e10b0]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164656) /* 0x5e10b0 */);
    // 00423d02  85db                   +test ebx, ebx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & cpu.ebx));
    // 00423d04  740e                   -je 0x423d14
    if (cpu.flags.zf)
    {
        goto L_0x00423d14;
    }
    // 00423d06  8b03                   -mov eax, dword ptr [ebx]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx);
    // 00423d08  83f809                 +cmp eax, 9
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
    // 00423d0b  7507                   -jne 0x423d14
    if (!cpu.flags.zf)
    {
        goto L_0x00423d14;
    }
    // 00423d0d  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00423d0f  e87cd7ffff             -call 0x421490
    cpu.esp -= 4;
    sub_421490(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00423d14:
    // 00423d14  8d048d00000000         -lea eax, [ecx*4]
    cpu.eax = x86::reg32(cpu.ecx * 4);
    // 00423d1b  8bb0b0105e00           -mov esi, dword ptr [eax + 0x5e10b0]
    cpu.esi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164656) /* 0x5e10b0 */);
    // 00423d21  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 00423d23  7410                   -je 0x423d35
    if (cpu.flags.zf)
    {
        goto L_0x00423d35;
    }
    // 00423d25  8b16                   -mov edx, dword ptr [esi]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi);
    // 00423d27  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00423d29  e8b2fdffff             -call 0x423ae0
    cpu.esp -= 4;
    sub_423ae0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00423d2e  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00423d2f  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00423d30  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00423d31  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00423d32  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00423d33  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00423d34  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x00423d35:
    // 00423d35  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
L_0x00423d37:
    // 00423d37  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00423d39  e8a2fdffff             -call 0x423ae0
    cpu.esp -= 4;
    sub_423ae0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00423d3e:
    // 00423d3e  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00423d3f  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00423d40  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00423d41  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00423d42  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00423d43  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00423d44  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 */
/* data blob: 00008040000020410000a04100002042000070420000a0420000e04200000c434000000020000000100000000800000006000000040000000300000002000000 */
void Application::sub_423d90(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00423d90  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00423d91  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00423d92  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00423d93  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00423d94  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00423d95  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00423d96  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00423d98  83ec60                 -sub esp, 0x60
    (cpu.esp) -= x86::reg32(x86::sreg32(96 /*0x60*/));
    // 00423d9b  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00423d9d  ba1e000000             -mov edx, 0x1e
    cpu.edx = 30 /*0x1e*/;
    // 00423da2  beffffffff             -mov esi, 0xffffffff
    cpu.esi = 4294967295 /*0xffffffff*/;
    // 00423da7  8b1db0d36f00           -mov ebx, dword ptr [0x6fd3b0]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(7328688) /* 0x6fd3b0 */);
    // 00423dad  8955f4                 -mov dword ptr [ebp - 0xc], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.edx;
    // 00423db0  83fb01                 +cmp ebx, 1
    {
        x86::reg32 tmp1 = cpu.ebx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1 /*0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00423db3  7504                   -jne 0x423db9
    if (!cpu.flags.zf)
    {
        goto L_0x00423db9;
    }
    // 00423db5  21d9                   +and ecx, ebx
    cpu.clear_co();
    cpu.set_szp((cpu.ecx &= x86::reg32(x86::sreg32(cpu.ebx))));
    // 00423db7  eb02                   -jmp 0x423dbb
    goto L_0x00423dbb;
L_0x00423db9:
    // 00423db9  31c1                   -xor ecx, eax
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.eax));
L_0x00423dbb:
    // 00423dbb  8b048d582f5500         -mov eax, dword ptr [ecx*4 + 0x552f58]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5582680) /* 0x552f58 */ + cpu.ecx * 4);
    // 00423dc2  8b4004                 -mov eax, dword ptr [eax + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 00423dc5  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
    // 00423dc7  8b781c                 -mov edi, dword ptr [eax + 0x1c]
    cpu.edi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(28) /* 0x1c */);
L_0x00423dca:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00423dca  3b1d4c2e5500           +cmp ebx, dword ptr [0x552e4c]
    {
        x86::reg32 tmp1 = cpu.ebx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(5582412) /* 0x552e4c */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00423dd0  0f8dbf000000           -jge 0x423e95
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00423e95;
    }
    // 00423dd6  895dfc                 -mov dword ptr [ebp - 4], ebx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.ebx;
    // 00423dd9  8d049d00000000         -lea eax, [ebx*4]
    cpu.eax = x86::reg32(cpu.ebx * 4);
    // 00423de0  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 00423de3  8b55fc                 -mov edx, dword ptr [ebp - 4]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00423de6  c1e003                 -shl eax, 3
    cpu.eax <<= 3 /*0x3*/ % 32;
    // 00423de9  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 00423deb  8b15502e5500           -mov edx, dword ptr [0x552e50]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5582416) /* 0x552e50 */);
    // 00423df1  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 00423df3  89fa                   -mov edx, edi
    cpu.edx = cpu.edi;
    // 00423df5  2b5018                 -sub edx, dword ptr [eax + 0x18]
    (cpu.edx) -= x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */)));
    // 00423df8  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 00423dfa  7e05                   -jle 0x423e01
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00423e01;
    }
    // 00423dfc  8955f0                 -mov dword ptr [ebp - 0x10], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = cpu.edx;
    // 00423dff  eb0a                   -jmp 0x423e0b
    goto L_0x00423e0b;
L_0x00423e01:
    // 00423e01  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 00423e03  8955f0                 -mov dword ptr [ebp - 0x10], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = cpu.edx;
    // 00423e06  f7d8                   -neg eax
    cpu.eax = ~cpu.eax + 1;
    // 00423e08  8945f0                 -mov dword ptr [ebp - 0x10], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = cpu.eax;
L_0x00423e0b:
    // 00423e0b  a140d95d00             -mov eax, dword ptr [0x5dd940]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(6150464) /* 0x5dd940 */);
    // 00423e10  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 00423e12  c1fa1f                 -sar edx, 0x1f
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (31 /*0x1f*/ % 32));
    // 00423e15  2bc2                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 00423e17  d1f8                   -sar eax, 1
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (1 /*0x1*/ % 32));
    // 00423e19  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 00423e1c  8d049d00000000         -lea eax, [ebx*4]
    cpu.eax = x86::reg32(cpu.ebx * 4);
    // 00423e23  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 00423e25  c1e003                 -shl eax, 3
    cpu.eax <<= 3 /*0x3*/ % 32;
    // 00423e28  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 00423e2a  8b55fc                 -mov edx, dword ptr [ebp - 4]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00423e2d  8945f8                 -mov dword ptr [ebp - 8], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.eax;
    // 00423e30  3b55f0                 +cmp edx, dword ptr [ebp - 0x10]
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00423e33  7d27                   -jge 0x423e5c
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00423e5c;
    }
    // 00423e35  8b55f8                 -mov edx, dword ptr [ebp - 8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 00423e38  a1502e5500             -mov eax, dword ptr [0x552e50]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5582416) /* 0x552e50 */);
    // 00423e3d  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 00423e3f  89fa                   -mov edx, edi
    cpu.edx = cpu.edi;
    // 00423e41  2b5018                 -sub edx, dword ptr [eax + 0x18]
    (cpu.edx) -= x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */)));
    // 00423e44  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 00423e46  7e04                   -jle 0x423e4c
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00423e4c;
    }
    // 00423e48  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 00423e4a  eb04                   -jmp 0x423e50
    goto L_0x00423e50;
L_0x00423e4c:
    // 00423e4c  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 00423e4e  f7d8                   -neg eax
    cpu.eax = ~cpu.eax + 1;
L_0x00423e50:
    // 00423e50  8b1540d95d00           -mov edx, dword ptr [0x5dd940]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(6150464) /* 0x5dd940 */);
    // 00423e56  29c2                   +sub edx, eax
    {
        x86::reg32& tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.eax));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 00423e58  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 00423e5a  eb29                   -jmp 0x423e85
    goto L_0x00423e85;
L_0x00423e5c:
    // 00423e5c  8b55f8                 -mov edx, dword ptr [ebp - 8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 00423e5f  a1502e5500             -mov eax, dword ptr [0x552e50]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5582416) /* 0x552e50 */);
    // 00423e64  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 00423e66  89fa                   -mov edx, edi
    cpu.edx = cpu.edi;
    // 00423e68  2b5018                 -sub edx, dword ptr [eax + 0x18]
    (cpu.edx) -= x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */)));
    // 00423e6b  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 00423e6d  7e12                   -jle 0x423e81
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00423e81;
    }
    // 00423e6f  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 00423e71  3b45f4                 +cmp eax, dword ptr [ebp - 0xc]
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
    // 00423e74  7d19                   -jge 0x423e8f
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00423e8f;
    }
    // 00423e76  89de                   -mov esi, ebx
    cpu.esi = cpu.ebx;
    // 00423e78  8945f4                 -mov dword ptr [ebp - 0xc], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.eax;
    // 00423e7b  43                     +inc ebx
    {
        x86::reg32& tmp = cpu.ebx;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 00423e7c  e949ffffff             -jmp 0x423dca
    goto L_0x00423dca;
L_0x00423e81:
    // 00423e81  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 00423e83  f7d8                   -neg eax
    cpu.eax = ~cpu.eax + 1;
L_0x00423e85:
    // 00423e85  3b45f4                 +cmp eax, dword ptr [ebp - 0xc]
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
    // 00423e88  7d05                   -jge 0x423e8f
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00423e8f;
    }
    // 00423e8a  89de                   -mov esi, ebx
    cpu.esi = cpu.ebx;
    // 00423e8c  8945f4                 -mov dword ptr [ebp - 0xc], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.eax;
L_0x00423e8f:
    // 00423e8f  43                     +inc ebx
    {
        x86::reg32& tmp = cpu.ebx;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 00423e90  e935ffffff             -jmp 0x423dca
    goto L_0x00423dca;
L_0x00423e95:
    // 00423e95  83feff                 +cmp esi, -1
    {
        x86::reg32 tmp1 = cpu.esi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(-1 /*-0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00423e98  0f8401010000           -je 0x423f9f
    if (cpu.flags.zf)
    {
        goto L_0x00423f9f;
    }
    // 00423e9e  8d3cb500000000         -lea edi, [esi*4]
    cpu.edi = x86::reg32(cpu.esi * 4);
    // 00423ea5  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 00423ea7  c1e703                 -shl edi, 3
    cpu.edi <<= 3 /*0x3*/ % 32;
    // 00423eaa  29c7                   -sub edi, eax
    (cpu.edi) -= x86::reg32(x86::sreg32(cpu.eax));
    // 00423eac  a1502e5500             -mov eax, dword ptr [0x552e50]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5582416) /* 0x552e50 */);
    // 00423eb1  db0407                 -fild dword ptr [edi + eax]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.edi + cpu.eax * 1)));
    // 00423eb4  dc0d8c6e5300           -fmul qword ptr [0x536e8c]
    x86::Float fpu2 = cpu.fpu.mul(fpu1, x86::Float(app->getMemory<double>(x86::reg32(5467788) /* 0x536e8c */)));
    // 00423eba  d95dd4                 -fstp dword ptr [ebp - 0x2c]
    app->getMemory<float>(cpu.ebp + x86::reg32(-44) /* -0x2c */) = float(fpu2);
    // 00423ebd  db440704               -fild dword ptr [edi + eax + 4]
    x86::Float fpu3 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.edi + x86::reg32(4) /* 0x4 */ + cpu.eax * 1)));
    // 00423ec1  dc0d8c6e5300           -fmul qword ptr [0x536e8c]
    x86::Float fpu4 = cpu.fpu.mul(fpu3, x86::Float(app->getMemory<double>(x86::reg32(5467788) /* 0x536e8c */)));
    // 00423ec7  d95dd8                 -fstp dword ptr [ebp - 0x28]
    app->getMemory<float>(cpu.ebp + x86::reg32(-40) /* -0x28 */) = float(fpu4);
    // 00423eca  db440708               -fild dword ptr [edi + eax + 8]
    x86::Float fpu5 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.edi + x86::reg32(8) /* 0x8 */ + cpu.eax * 1)));
    // 00423ece  dc0d8c6e5300           -fmul qword ptr [0x536e8c]
    x86::Float fpu6 = cpu.fpu.mul(fpu5, x86::Float(app->getMemory<double>(x86::reg32(5467788) /* 0x536e8c */)));
    // 00423ed4  8b048d582f5500         -mov eax, dword ptr [ecx*4 + 0x552f58]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5582680) /* 0x552f58 */ + cpu.ecx * 4);
    // 00423edb  d95ddc                 -fstp dword ptr [ebp - 0x24]
    app->getMemory<float>(cpu.ebp + x86::reg32(-36) /* -0x24 */) = float(fpu6);
    // 00423ede  8b4004                 -mov eax, dword ptr [eax + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 00423ee1  8d55d4                 -lea edx, [ebp - 0x2c]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-44) /* -0x2c */);
    // 00423ee4  8d9898000000           -lea ebx, [eax + 0x98]
    cpu.ebx = x86::reg32(cpu.eax + x86::reg32(152) /* 0x98 */);
    // 00423eea  8d4de0                 -lea ecx, [ebp - 0x20]
    cpu.ecx = x86::reg32(cpu.ebp + x86::reg32(-32) /* -0x20 */);
    // 00423eed  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    }
    // 00423ef2  e809c10b00             -call 0x4e0000
    cpu.esp -= 4;
    sub_4e0000(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00423ef7  8d55e0                 -lea edx, [ebp - 0x20]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-32) /* -0x20 */);
    // 00423efa  8d45e0                 -lea eax, [ebp - 0x20]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-32) /* -0x20 */);
    // 00423efd  e8bec20b00             -call 0x4e01c0
    cpu.esp -= 4;
    sub_4e01c0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00423f02  a1502e5500             -mov eax, dword ptr [0x552e50]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5582416) /* 0x552e50 */);
    // 00423f07  8b54070a               -mov edx, dword ptr [edi + eax + 0xa]
    cpu.edx = app->getMemory<x86::reg32>(cpu.edi + x86::reg32(10) /* 0xa */ + cpu.eax * 1);
    // 00423f0b  c1fa10                 -sar edx, 0x10
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (16 /*0x10*/ % 32));
    // 00423f0e  c1e202                 -shl edx, 2
    cpu.edx <<= 2 /*0x2*/ % 32;
    // 00423f11  8955fc                 -mov dword ptr [ebp - 4], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.edx;
    // 00423f14  db45fc                 -fild dword ptr [ebp - 4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu7 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 00423f17  dc0d8c6e5300           -fmul qword ptr [0x536e8c]
    x86::Float fpu8 = cpu.fpu.mul(fpu7, x86::Float(app->getMemory<double>(x86::reg32(5467788) /* 0x536e8c */)));
    // 00423f1d  d95dc4                 -fstp dword ptr [ebp - 0x3c]
    app->getMemory<float>(cpu.ebp + x86::reg32(-60) /* -0x3c */) = float(fpu8);
    // 00423f20  8b54070c               -mov edx, dword ptr [edi + eax + 0xc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.edi + x86::reg32(12) /* 0xc */ + cpu.eax * 1);
    // 00423f24  c1fa10                 -sar edx, 0x10
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (16 /*0x10*/ % 32));
    // 00423f27  c1e202                 -shl edx, 2
    cpu.edx <<= 2 /*0x2*/ % 32;
    // 00423f2a  8955fc                 -mov dword ptr [ebp - 4], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.edx;
    // 00423f2d  db45fc                 -fild dword ptr [ebp - 4]
    x86::Float fpu9 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 00423f30  dc0d8c6e5300           -fmul qword ptr [0x536e8c]
    x86::Float fpu10 = cpu.fpu.mul(fpu9, x86::Float(app->getMemory<double>(x86::reg32(5467788) /* 0x536e8c */)));
    // 00423f36  d95dc8                 -fstp dword ptr [ebp - 0x38]
    app->getMemory<float>(cpu.ebp + x86::reg32(-56) /* -0x38 */) = float(fpu10);
    // 00423f39  8b54070e               -mov edx, dword ptr [edi + eax + 0xe]
    cpu.edx = app->getMemory<x86::reg32>(cpu.edi + x86::reg32(14) /* 0xe */ + cpu.eax * 1);
    // 00423f3d  c1fa10                 -sar edx, 0x10
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (16 /*0x10*/ % 32));
    // 00423f40  c1e202                 -shl edx, 2
    cpu.edx <<= 2 /*0x2*/ % 32;
    // 00423f43  8955fc                 -mov dword ptr [ebp - 4], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.edx;
    // 00423f46  db45fc                 -fild dword ptr [ebp - 4]
    x86::Float fpu11 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 00423f49  dc0d8c6e5300           -fmul qword ptr [0x536e8c]
    x86::Float fpu12 = cpu.fpu.mul(fpu11, x86::Float(app->getMemory<double>(x86::reg32(5467788) /* 0x536e8c */)));
    // 00423f4f  d95dcc                 -fstp dword ptr [ebp - 0x34]
    app->getMemory<float>(cpu.ebp + x86::reg32(-52) /* -0x34 */) = float(fpu12);
    // 00423f52  8b440710               -mov eax, dword ptr [edi + eax + 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edi + x86::reg32(16) /* 0x10 */ + cpu.eax * 1);
    // 00423f56  c1f810                 -sar eax, 0x10
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (16 /*0x10*/ % 32));
    // 00423f59  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 00423f5c  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 00423f5f  db45fc                 -fild dword ptr [ebp - 4]
    x86::Float fpu13 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 00423f62  dc0d8c6e5300           -fmul qword ptr [0x536e8c]
    x86::Float fpu14 = cpu.fpu.mul(fpu13, x86::Float(app->getMemory<double>(x86::reg32(5467788) /* 0x536e8c */)));
    // 00423f68  d95dd0                 -fstp dword ptr [ebp - 0x30]
    app->getMemory<float>(cpu.ebp + x86::reg32(-48) /* -0x30 */) = float(fpu14);
    // 00423f6b  8d55a0                 -lea edx, [ebp - 0x60]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-96) /* -0x60 */);
    // 00423f6e  8d45c4                 -lea eax, [ebp - 0x3c]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-60) /* -0x3c */);
    // 00423f71  8d4dec                 -lea ecx, [ebp - 0x14]
    cpu.ecx = x86::reg32(cpu.ebp + x86::reg32(-20) /* -0x14 */);
    // 00423f74  8d5de0                 -lea ebx, [ebp - 0x20]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-32) /* -0x20 */);
    }
    // 00423f77  e814360900             -call 0x4b7590
    cpu.esp -= 4;
    sub_4b7590(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00423f7c  8d45a0                 -lea eax, [ebp - 0x60]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-96) /* -0x60 */);
    // 00423f7f  8d55b8                 -lea edx, [ebp - 0x48]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-72) /* -0x48 */);
    // 00423f82  e8393a0900             -call 0x4b79c0
    cpu.esp -= 4;
    sub_4b79c0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00423f87  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 00423f8c  e87fc20b00             -call 0x4e0210
    cpu.esp -= 4;
    sub_4e0210(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00423f91  817deccdcccc3e         +cmp dword ptr [ebp - 0x14], 0x3ecccccd
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1053609165 /*0x3ecccccd*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00423f98  7e05                   -jle 0x423f9f
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00423f9f;
    }
    // 00423f9a  beffffffff             -mov esi, 0xffffffff
    cpu.esi = 4294967295 /*0xffffffff*/;
L_0x00423f9f:
    // 00423f9f  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 00423fa1  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00423fa3  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00423fa4  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00423fa5  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00423fa6  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00423fa7  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00423fa8  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00423fa9  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 */
void Application::sub_423fb0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00423fb0  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00423fb1  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00423fb3  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 00423fb6  83780400               +cmp dword ptr [eax + 4], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00423fba  740e                   -je 0x423fca
    if (cpu.flags.zf)
    {
        goto L_0x00423fca;
    }
    // 00423fbc  d94508                 +fld dword ptr [ebp + 8]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(8) /* 0x8 */));
    // 00423fbf  d80d946e5300           +fmul dword ptr [0x536e94]
    x86::Float fpu2 = cpu.fpu.mul(fpu1, x86::Float(app->getMemory<float>(x86::reg32(5467796) /* 0x536e94 */)));
    // 00423fc5  d95dfc                 +fstp dword ptr [ebp - 4]
    app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = float(fpu2);
    }
    // 00423fc8  eb06                   -jmp 0x423fd0
    goto L_0x00423fd0;
L_0x00423fca:
    // 00423fca  8b4508                 -mov eax, dword ptr [ebp + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(8) /* 0x8 */);
    // 00423fcd  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
L_0x00423fd0:
    // 00423fd0  d945fc                 -fld dword ptr [ebp - 4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu3 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */));
    // 00423fd3  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00423fd5  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    cpu.fpu.count += 1;
    cpu.fpu.st(0) = fpu3;
    }
    // 00423fd6  c20400                 -ret 4
    cpu.esp += 4+4 /*0x4*/;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x90 */
void Application::sub_423fe0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00423fe0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00423fe1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00423fe2  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00423fe3  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00423fe4  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00423fe6  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 00423fe8  4a                     -dec edx
    (cpu.edx)--;
    // 00423fe9  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 00423feb  21c2                   -and edx, eax
    cpu.edx &= x86::reg32(x86::sreg32(cpu.eax));
    // 00423fed  29d3                   -sub ebx, edx
    (cpu.ebx) -= x86::reg32(x86::sreg32(cpu.edx));
L_0x00423fef:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00423fef  6685c0                 +test ax, ax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg16>(cpu.ax & cpu.ax));
    // 00423ff2  742a                   -je 0x42401e
    if (cpu.flags.zf)
    {
        goto L_0x0042401e;
    }
    // 00423ff4  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 00423ff6  6689c1                 -mov cx, ax
    cpu.cx = cpu.ax;
    // 00423ff9  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00423ffb  6689d0                 -mov ax, dx
    cpu.ax = cpu.dx;
    // 00423ffe  29c1                   -sub ecx, eax
    (cpu.ecx) -= x86::reg32(x86::sreg32(cpu.eax));
    // 00424000  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00424002  6689d8                 -mov ax, bx
    cpu.ax = cpu.bx;
    // 00424005  39c1                   +cmp ecx, eax
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
    // 00424007  740a                   -je 0x424013
    if (cpu.flags.zf)
    {
        goto L_0x00424013;
    }
    // 00424009  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 0042400e  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042400f  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00424010  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00424011  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00424012  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x00424013:
    // 00424013  89d1                   -mov ecx, edx
    cpu.ecx = cpu.edx;
    // 00424015  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 00424017  49                     -dec ecx
    (cpu.ecx)--;
    // 00424018  01db                   -add ebx, ebx
    (cpu.ebx) += x86::reg32(x86::sreg32(cpu.ebx));
    // 0042401a  21ca                   +and edx, ecx
    cpu.clear_co();
    cpu.set_szp((cpu.edx &= x86::reg32(x86::sreg32(cpu.ecx))));
    // 0042401c  ebd1                   -jmp 0x423fef
    goto L_0x00423fef;
L_0x0042401e:
    // 0042401e  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00424020  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00424021  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00424022  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00424023  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00424024  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 0x8b 0xdb */
void Application::sub_424030(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00424030  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00424031  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00424032  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00424033  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00424034  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00424036  83ec0c                 -sub esp, 0xc
    (cpu.esp) -= x86::reg32(x86::sreg32(12 /*0xc*/));
    // 00424039  8b5518                 -mov edx, dword ptr [ebp + 0x18]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(24) /* 0x18 */);
    // 0042403c  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 0042403e  f74514ffffff7f         +test dword ptr [ebp + 0x14], 0x7fffffff
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(20) /* 0x14 */) & 2147483647 /*0x7fffffff*/));
    // 00424045  746d                   -je 0x4240b4
    if (cpu.flags.zf)
    {
        goto L_0x004240b4;
    }
    // 00424047  8bb1e8040000           -mov esi, dword ptr [ecx + 0x4e8]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(1256) /* 0x4e8 */);
    // 0042404d  81fe00004040           +cmp esi, 0x40400000
    {
        x86::reg32 tmp1 = cpu.esi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1077936128 /*0x40400000*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00424053  7e09                   -jle 0x42405e
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x0042405e;
    }
    // 00424055  c745fc00004040         -mov dword ptr [ebp - 4], 0x40400000
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = 1077936128 /*0x40400000*/;
    // 0042405c  eb03                   -jmp 0x424061
    goto L_0x00424061;
L_0x0042405e:
    // 0042405e  8975fc                 -mov dword ptr [ebp - 4], esi
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.esi;
L_0x00424061:
    // 00424061  d945fc                 +fld dword ptr [ebp - 4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */));
    // 00424064  dc1d9c6e5300           +fcomp qword ptr [0x536e9c]
    cpu.fpu.compare(fpu1, x86::Float(app->getMemory<double>(x86::reg32(5467804) /* 0x536e9c */)));
    // 0042406a  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 0042406c  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 0042406d  7608                   -jbe 0x424077
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x00424077;
    }
    // 0042406f  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00424072  8945f8                 -mov dword ptr [ebp - 8], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.eax;
    // 00424075  eb07                   -jmp 0x42407e
    goto L_0x0042407e;
L_0x00424077:
    // 00424077  c745f8000040c0         -mov dword ptr [ebp - 8], 0xc0400000
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = 3225419776 /*0xc0400000*/;
L_0x0042407e:
    // 0042407e  d945f8                 -fld dword ptr [ebp - 8]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu2 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */));
    // 00424081  d805a46e5300           -fadd dword ptr [0x536ea4]
    x86::Float fpu3 = cpu.fpu.add(fpu2, x86::Float(app->getMemory<float>(x86::reg32(5467812) /* 0x536ea4 */)));
    // 00424087  d80da86e5300           -fmul dword ptr [0x536ea8]
    x86::Float fpu4 = cpu.fpu.mul(fpu3, x86::Float(app->getMemory<float>(x86::reg32(5467816) /* 0x536ea8 */)));
    // 0042408d  d9e8                   -fld1 
    x86::Float fpu5 = 1.0;
    // 0042408f  dee1                   -fsubrp st(1)
    x86::Float fpu6 = cpu.fpu.sub(fpu5, x86::Float(fpu4));
    // 00424091  d84d14                 -fmul dword ptr [ebp + 0x14]
    x86::Float fpu7 = cpu.fpu.mul(fpu6, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(20) /* 0x14 */)));
    // 00424094  d902                   -fld dword ptr [edx]
    x86::Float fpu8 = x86::Float(app->getMemory<float>(cpu.edx));
    // 00424096  d9e8                   -fld1 
    x86::Float fpu9 = 1.0;
    // 00424098  dee2                   -fsubrp st(2)
    x86::Float fpu10 = cpu.fpu.sub(fpu9, x86::Float(fpu7));
    // 0042409a  d8c9                   -fmul st(1)
    x86::Float fpu11 = cpu.fpu.mul(fpu8, x86::Float(fpu10));
    // 0042409c  d9c1                   -fld st(1)
    x86::Float fpu12 = x86::Float(fpu10);
    // 0042409e  d8ca                   -fmul st(2)
    x86::Float fpu13 = cpu.fpu.mul(fpu12, x86::Float(fpu10));
    // 004240a0  d94208                 -fld dword ptr [edx + 8]
    x86::Float fpu14 = x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(8) /* 0x8 */));
    // 004240a3  decb                   -fmulp st(3)
    x86::Float fpu15 = cpu.fpu.mul(fpu10, fpu14);
    // 004240a5  d84a04                 -fmul dword ptr [edx + 4]
    x86::Float fpu16 = cpu.fpu.mul(fpu13, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(4) /* 0x4 */)));
    // 004240a8  d9c9                   -fxch st(1)
    
    // 004240aa  d91a                   -fstp dword ptr [edx]
    app->getMemory<float>(cpu.edx) = float(fpu11);
    // 004240ac  d9c9                   -fxch st(1)
    
    // 004240ae  d95a08                 -fstp dword ptr [edx + 8]
    app->getMemory<float>(cpu.edx + x86::reg32(8) /* 0x8 */) = float(fpu15);
    // 004240b1  d95a04                 -fstp dword ptr [edx + 4]
    app->getMemory<float>(cpu.edx + x86::reg32(4) /* 0x4 */) = float(fpu16);
    }
L_0x004240b4:
    // 004240b4  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004240b6  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004240b7  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004240b8  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004240b9  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004240ba  c20800                 -ret 8
    cpu.esp += 4+8 /*0x8*/;
    return;
}

/* align: skip 0x8d 0x40 0x00 */
void Application::sub_4240c0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004240c0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004240c1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004240c2  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004240c3  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004240c4  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004240c5  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004240c6  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004240c8  83ec28                 -sub esp, 0x28
    (cpu.esp) -= x86::reg32(x86::sreg32(40 /*0x28*/));
    // 004240cb  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 004240ce  8d7de4                 -lea edi, [ebp - 0x1c]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(-28) /* -0x1c */);
    // 004240d1  8db010010000           -lea esi, [eax + 0x110]
    cpu.esi = x86::reg32(cpu.eax + x86::reg32(272) /* 0x110 */);
    // 004240d7  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004240d8  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004240d9  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004240da  8b4004                 -mov eax, dword ptr [eax + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 004240dd  8b8098000000           -mov eax, dword ptr [eax + 0x98]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(152) /* 0x98 */);
    // 004240e3  8945f0                 -mov dword ptr [ebp - 0x10], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = cpu.eax;
    // 004240e6  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004240e9  8b4004                 -mov eax, dword ptr [eax + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 004240ec  8b809c000000           -mov eax, dword ptr [eax + 0x9c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(156) /* 0x9c */);
    // 004240f2  8945f4                 -mov dword ptr [ebp - 0xc], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.eax;
    // 004240f5  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004240f8  8b4004                 -mov eax, dword ptr [eax + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 004240fb  8b80a0000000           -mov eax, dword ptr [eax + 0xa0]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(160) /* 0xa0 */);
    // 00424101  8b15fc227900           -mov edx, dword ptr [0x7922fc]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(7938812) /* 0x7922fc */);
    // 00424107  8945f8                 -mov dword ptr [ebp - 8], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.eax;
    // 0042410a  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 0042410c  7521                   -jne 0x42412f
    if (!cpu.flags.zf)
    {
        goto L_0x0042412f;
    }
    // 0042410e  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00424111  c740500ad7a33c         -mov dword ptr [eax + 0x50], 0x3ca3d70a
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(80) /* 0x50 */) = 1017370378 /*0x3ca3d70a*/;
    // 00424118  8955e4                 -mov dword ptr [ebp - 0x1c], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-28) /* -0x1c */) = cpu.edx;
    // 0042411b  8b4004                 -mov eax, dword ptr [eax + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 0042411e  d9801c010000           +fld dword ptr [eax + 0x11c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(284) /* 0x11c */));
    // 00424124  dc0dac6e5300           +fmul qword ptr [0x536eac]
    x86::Float fpu2 = cpu.fpu.mul(fpu1, x86::Float(app->getMemory<double>(x86::reg32(5467820) /* 0x536eac */)));
    // 0042412a  d95dec                 +fstp dword ptr [ebp - 0x14]
    app->getMemory<float>(cpu.ebp + x86::reg32(-20) /* -0x14 */) = float(fpu2);
    }
    // 0042412d  eb3c                   -jmp 0x42416b
    goto L_0x0042416b;
L_0x0042412f:
    // 0042412f  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00424132  c7405000000000         -mov dword ptr [eax + 0x50], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(80) /* 0x50 */) = 0 /*0x0*/;
    // 00424139  8b4004                 -mov eax, dword ptr [eax + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 0042413c  8b80a8090000           -mov eax, dword ptr [eax + 0x9a8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(2472) /* 0x9a8 */);
    // 00424142  83f801                 +cmp eax, 1
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
    // 00424145  7209                   -jb 0x424150
    if (cpu.flags.cf)
    {
        goto L_0x00424150;
    }
    // 00424147  7614                   -jbe 0x42415d
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x0042415d;
    }
    // 00424149  83f802                 +cmp eax, 2
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
    // 0042414c  7418                   -je 0x424166
    if (cpu.flags.zf)
    {
        goto L_0x00424166;
    }
    // 0042414e  eb1b                   -jmp 0x42416b
    goto L_0x0042416b;
L_0x00424150:
    // 00424150  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00424152  7517                   -jne 0x42416b
    if (!cpu.flags.zf)
    {
        goto L_0x0042416b;
    }
    // 00424154  c745e4cdccccbe         -mov dword ptr [ebp - 0x1c], 0xbecccccd
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-28) /* -0x1c */) = 3201092813 /*0xbecccccd*/;
    // 0042415b  eb0e                   -jmp 0x42416b
    goto L_0x0042416b;
L_0x0042415d:
    // 0042415d  c745e4cdcccc3e         -mov dword ptr [ebp - 0x1c], 0x3ecccccd
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-28) /* -0x1c */) = 1053609165 /*0x3ecccccd*/;
    // 00424164  eb05                   -jmp 0x42416b
    goto L_0x0042416b;
L_0x00424166:
    // 00424166  31ff                   -xor edi, edi
    cpu.edi ^= x86::reg32(x86::sreg32(cpu.edi));
    // 00424168  897de4                 -mov dword ptr [ebp - 0x1c], edi
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-28) /* -0x1c */) = cpu.edi;
L_0x0042416b:
    // 0042416b  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 0042416e  8b4008                 -mov eax, dword ptr [eax + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 00424171  d945e8                 -fld dword ptr [ebp - 0x18]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu3 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-24) /* -0x18 */));
    // 00424174  d8880c010000           -fmul dword ptr [eax + 0x10c]
    x86::Float fpu4 = cpu.fpu.mul(fpu3, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(268) /* 0x10c */)));
    // 0042417a  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 0042417d  d95de8                 -fstp dword ptr [ebp - 0x18]
    app->getMemory<float>(cpu.ebp + x86::reg32(-24) /* -0x18 */) = float(fpu4);
    // 00424180  8b400c                 -mov eax, dword ptr [eax + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
    // 00424183  833c85a0c4790000       +cmp dword ptr [eax*4 + 0x79c4a0], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(7980192) /* 0x79c4a0 */ + cpu.eax * 4);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    }
    // 0042418b  7404                   -je 0x424191
    if (cpu.flags.zf)
    {
        goto L_0x00424191;
    }
    // 0042418d  8075ef80               -xor byte ptr [ebp - 0x11], 0x80
    app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-17) /* -0x11 */) ^= x86::reg8(x86::sreg8(128 /*0x80*/));
L_0x00424191:
    // 00424191  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00424194  8b4004                 -mov eax, dword ptr [eax + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 00424197  8d5dd8                 -lea ebx, [ebp - 0x28]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-40) /* -0x28 */);
    // 0042419a  8d90c0000000           -lea edx, [eax + 0xc0]
    cpu.edx = x86::reg32(cpu.eax + x86::reg32(192) /* 0xc0 */);
    // 004241a0  8b4dfc                 -mov ecx, dword ptr [ebp - 4]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004241a3  8d45e4                 -lea eax, [ebp - 0x1c]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-28) /* -0x1c */);
    // 004241a6  83c114                 -add ecx, 0x14
    (cpu.ecx) += x86::reg32(x86::sreg32(20 /*0x14*/));
    // 004241a9  d900                   -fld dword ptr [eax]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu5 = x86::Float(app->getMemory<float>(cpu.eax));
    // 004241ab  d80a                   -fmul dword ptr [edx]
    x86::Float fpu6 = cpu.fpu.mul(fpu5, x86::Float(app->getMemory<float>(cpu.edx)));
    // 004241ad  d900                   -fld dword ptr [eax]
    x86::Float fpu7 = x86::Float(app->getMemory<float>(cpu.eax));
    // 004241af  d84a04                 -fmul dword ptr [edx + 4]
    x86::Float fpu8 = cpu.fpu.mul(fpu7, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(4) /* 0x4 */)));
    // 004241b2  d900                   -fld dword ptr [eax]
    x86::Float fpu9 = x86::Float(app->getMemory<float>(cpu.eax));
    // 004241b4  d84a08                 -fmul dword ptr [edx + 8]
    x86::Float fpu10 = cpu.fpu.mul(fpu9, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(8) /* 0x8 */)));
    // 004241b7  d9ca                   -fxch st(2)
    
    // 004241b9  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu11 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 004241bc  d84a0c                 -fmul dword ptr [edx + 0xc]
    x86::Float fpu12 = cpu.fpu.mul(fpu11, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(12) /* 0xc */)));
    // 004241bf  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu13 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 004241c2  d84a10                 -fmul dword ptr [edx + 0x10]
    x86::Float fpu14 = cpu.fpu.mul(fpu13, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(16) /* 0x10 */)));
    // 004241c5  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu15 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 004241c8  d84a14                 -fmul dword ptr [edx + 0x14]
    x86::Float fpu16 = cpu.fpu.mul(fpu15, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(20) /* 0x14 */)));
    // 004241cb  d9ca                   -fxch st(2)
    
    // 004241cd  dec3                   -faddp st(3)
    x86::Float fpu17 = cpu.fpu.add(fpu6, fpu12);
    // 004241cf  dec3                   -faddp st(3)
    x86::Float fpu18 = cpu.fpu.add(fpu8, fpu14);
    // 004241d1  dec3                   -faddp st(3)
    x86::Float fpu19 = cpu.fpu.add(fpu10, fpu16);
    // 004241d3  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu20 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 004241d6  d84a18                 -fmul dword ptr [edx + 0x18]
    x86::Float fpu21 = cpu.fpu.mul(fpu20, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(24) /* 0x18 */)));
    // 004241d9  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu22 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 004241dc  d84a1c                 -fmul dword ptr [edx + 0x1c]
    x86::Float fpu23 = cpu.fpu.mul(fpu22, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(28) /* 0x1c */)));
    // 004241df  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu24 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 004241e2  d84a20                 -fmul dword ptr [edx + 0x20]
    x86::Float fpu25 = cpu.fpu.mul(fpu24, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(32) /* 0x20 */)));
    // 004241e5  d9ca                   -fxch st(2)
    
    // 004241e7  dec3                   -faddp st(3)
    x86::Float fpu26 = cpu.fpu.add(fpu17, fpu21);
    // 004241e9  dec3                   -faddp st(3)
    x86::Float fpu27 = cpu.fpu.add(fpu18, fpu23);
    // 004241eb  dec3                   -faddp st(3)
    x86::Float fpu28 = cpu.fpu.add(fpu19, fpu25);
    // 004241ed  8d400c                 -lea eax, [eax + 0xc]
    cpu.eax = x86::reg32(cpu.eax + x86::reg32(12) /* 0xc */);
    // 004241f0  d91b                   -fstp dword ptr [ebx]
    app->getMemory<float>(cpu.ebx) = float(fpu26);
    // 004241f2  d95b04                 -fstp dword ptr [ebx + 4]
    app->getMemory<float>(cpu.ebx + x86::reg32(4) /* 0x4 */) = float(fpu27);
    // 004241f5  d95b08                 -fstp dword ptr [ebx + 8]
    app->getMemory<float>(cpu.ebx + x86::reg32(8) /* 0x8 */) = float(fpu28);
    // 004241f8  8d5dd8                 -lea ebx, [ebp - 0x28]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-40) /* -0x28 */);
    // 004241fb  8d55f0                 -lea edx, [ebp - 0x10]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 004241fe  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    }
    // 00424203  e8a8bd0b00             -call 0x4dffb0
    cpu.esp -= 4;
    sub_4dffb0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00424208  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 0042420b  8b400c                 -mov eax, dword ptr [eax + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
    // 0042420e  833c85a0c4790000       +cmp dword ptr [eax*4 + 0x79c4a0], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(7980192) /* 0x79c4a0 */ + cpu.eax * 4);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00424216  7418                   -je 0x424230
    if (cpu.flags.zf)
    {
        goto L_0x00424230;
    }
    // 00424218  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 0042421b  8b55fc                 -mov edx, dword ptr [ebp - 4]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 0042421e  8b4004                 -mov eax, dword ptr [eax + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 00424221  83c22c                 -add edx, 0x2c
    (cpu.edx) += x86::reg32(x86::sreg32(44 /*0x2c*/));
    // 00424224  05c0000000             +add eax, 0xc0
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
    // 00424229  e842d3ffff             -call 0x421570
    cpu.esp -= 4;
    sub_421570(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042422e  eb19                   -jmp 0x424249
    goto L_0x00424249;
L_0x00424230:
    // 00424230  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00424233  8b7dfc                 -mov edi, dword ptr [ebp - 4]
    cpu.edi = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00424236  8b4004                 -mov eax, dword ptr [eax + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 00424239  b909000000             -mov ecx, 9
    cpu.ecx = 9 /*0x9*/;
    // 0042423e  8d7f2c                 -lea edi, [edi + 0x2c]
    cpu.edi = x86::reg32(cpu.edi + x86::reg32(44) /* 0x2c */);
    // 00424241  8db0c0000000           -lea esi, [eax + 0xc0]
    cpu.esi = x86::reg32(cpu.eax + x86::reg32(192) /* 0xc0 */);
    // 00424247  f3a5                   -rep movsd dword ptr es:[edi], dword ptr [esi]
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
L_0x00424249:
    // 00424249  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 0042424b  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042424c  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042424d  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042424e  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042424f  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00424250  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00424251  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x8b 0xc0 */
void Application::sub_424260(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00424260  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00424261  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00424262  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00424263  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00424264  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00424265  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00424266  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00424268  83ec28                 -sub esp, 0x28
    (cpu.esp) -= x86::reg32(x86::sreg32(40 /*0x28*/));
    // 0042426b  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 0042426e  8d7dd8                 -lea edi, [ebp - 0x28]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(-40) /* -0x28 */);
    // 00424271  8db010010000           -lea esi, [eax + 0x110]
    cpu.esi = x86::reg32(cpu.eax + x86::reg32(272) /* 0x110 */);
    // 00424277  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00424278  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00424279  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 0042427a  8b4004                 -mov eax, dword ptr [eax + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 0042427d  8b8098000000           -mov eax, dword ptr [eax + 0x98]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(152) /* 0x98 */);
    // 00424283  8945f0                 -mov dword ptr [ebp - 0x10], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = cpu.eax;
    // 00424286  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00424289  8b4004                 -mov eax, dword ptr [eax + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 0042428c  8b809c000000           -mov eax, dword ptr [eax + 0x9c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(156) /* 0x9c */);
    // 00424292  8945f4                 -mov dword ptr [ebp - 0xc], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.eax;
    // 00424295  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00424298  8b4004                 -mov eax, dword ptr [eax + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 0042429b  8b80a0000000           -mov eax, dword ptr [eax + 0xa0]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(160) /* 0xa0 */);
    // 004242a1  8945f8                 -mov dword ptr [ebp - 8], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.eax;
    // 004242a4  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004242a7  8b4008                 -mov eax, dword ptr [eax + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 004242aa  d945dc                 -fld dword ptr [ebp - 0x24]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-36) /* -0x24 */));
    // 004242ad  d8880c010000           -fmul dword ptr [eax + 0x10c]
    x86::Float fpu2 = cpu.fpu.mul(fpu1, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(268) /* 0x10c */)));
    // 004242b3  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004242b6  d95ddc                 -fstp dword ptr [ebp - 0x24]
    app->getMemory<float>(cpu.ebp + x86::reg32(-36) /* -0x24 */) = float(fpu2);
    // 004242b9  8b4004                 -mov eax, dword ptr [eax + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 004242bc  d9801c010000           -fld dword ptr [eax + 0x11c]
    x86::Float fpu3 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(284) /* 0x11c */));
    // 004242c2  dc0db46e5300           -fmul qword ptr [0x536eb4]
    x86::Float fpu4 = cpu.fpu.mul(fpu3, x86::Float(app->getMemory<double>(x86::reg32(5467828) /* 0x536eb4 */)));
    // 004242c8  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004242cb  d95de0                 -fstp dword ptr [ebp - 0x20]
    app->getMemory<float>(cpu.ebp + x86::reg32(-32) /* -0x20 */) = float(fpu4);
    // 004242ce  8b400c                 -mov eax, dword ptr [eax + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
    // 004242d1  833c85a0c4790000       +cmp dword ptr [eax*4 + 0x79c4a0], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(7980192) /* 0x79c4a0 */ + cpu.eax * 4);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    }
    // 004242d9  7404                   -je 0x4242df
    if (cpu.flags.zf)
    {
        goto L_0x004242df;
    }
    // 004242db  8075e380               -xor byte ptr [ebp - 0x1d], 0x80
    app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-29) /* -0x1d */) ^= x86::reg8(x86::sreg8(128 /*0x80*/));
L_0x004242df:
    // 004242df  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004242e2  8b4004                 -mov eax, dword ptr [eax + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 004242e5  8d5de4                 -lea ebx, [ebp - 0x1c]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-28) /* -0x1c */);
    // 004242e8  8d90c0000000           -lea edx, [eax + 0xc0]
    cpu.edx = x86::reg32(cpu.eax + x86::reg32(192) /* 0xc0 */);
    // 004242ee  8b4dfc                 -mov ecx, dword ptr [ebp - 4]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004242f1  8d45d8                 -lea eax, [ebp - 0x28]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-40) /* -0x28 */);
    // 004242f4  83c114                 -add ecx, 0x14
    (cpu.ecx) += x86::reg32(x86::sreg32(20 /*0x14*/));
    // 004242f7  d900                   -fld dword ptr [eax]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu5 = x86::Float(app->getMemory<float>(cpu.eax));
    // 004242f9  d80a                   -fmul dword ptr [edx]
    x86::Float fpu6 = cpu.fpu.mul(fpu5, x86::Float(app->getMemory<float>(cpu.edx)));
    // 004242fb  d900                   -fld dword ptr [eax]
    x86::Float fpu7 = x86::Float(app->getMemory<float>(cpu.eax));
    // 004242fd  d84a04                 -fmul dword ptr [edx + 4]
    x86::Float fpu8 = cpu.fpu.mul(fpu7, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(4) /* 0x4 */)));
    // 00424300  d900                   -fld dword ptr [eax]
    x86::Float fpu9 = x86::Float(app->getMemory<float>(cpu.eax));
    // 00424302  d84a08                 -fmul dword ptr [edx + 8]
    x86::Float fpu10 = cpu.fpu.mul(fpu9, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(8) /* 0x8 */)));
    // 00424305  d9ca                   -fxch st(2)
    
    // 00424307  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu11 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 0042430a  d84a0c                 -fmul dword ptr [edx + 0xc]
    x86::Float fpu12 = cpu.fpu.mul(fpu11, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(12) /* 0xc */)));
    // 0042430d  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu13 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 00424310  d84a10                 -fmul dword ptr [edx + 0x10]
    x86::Float fpu14 = cpu.fpu.mul(fpu13, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(16) /* 0x10 */)));
    // 00424313  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu15 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 00424316  d84a14                 -fmul dword ptr [edx + 0x14]
    x86::Float fpu16 = cpu.fpu.mul(fpu15, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(20) /* 0x14 */)));
    // 00424319  d9ca                   -fxch st(2)
    
    // 0042431b  dec3                   -faddp st(3)
    x86::Float fpu17 = cpu.fpu.add(fpu6, fpu12);
    // 0042431d  dec3                   -faddp st(3)
    x86::Float fpu18 = cpu.fpu.add(fpu8, fpu14);
    // 0042431f  dec3                   -faddp st(3)
    x86::Float fpu19 = cpu.fpu.add(fpu10, fpu16);
    // 00424321  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu20 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 00424324  d84a18                 -fmul dword ptr [edx + 0x18]
    x86::Float fpu21 = cpu.fpu.mul(fpu20, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(24) /* 0x18 */)));
    // 00424327  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu22 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 0042432a  d84a1c                 -fmul dword ptr [edx + 0x1c]
    x86::Float fpu23 = cpu.fpu.mul(fpu22, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(28) /* 0x1c */)));
    // 0042432d  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu24 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 00424330  d84a20                 -fmul dword ptr [edx + 0x20]
    x86::Float fpu25 = cpu.fpu.mul(fpu24, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(32) /* 0x20 */)));
    // 00424333  d9ca                   -fxch st(2)
    
    // 00424335  dec3                   -faddp st(3)
    x86::Float fpu26 = cpu.fpu.add(fpu17, fpu21);
    // 00424337  dec3                   -faddp st(3)
    x86::Float fpu27 = cpu.fpu.add(fpu18, fpu23);
    // 00424339  dec3                   -faddp st(3)
    x86::Float fpu28 = cpu.fpu.add(fpu19, fpu25);
    // 0042433b  8d400c                 -lea eax, [eax + 0xc]
    cpu.eax = x86::reg32(cpu.eax + x86::reg32(12) /* 0xc */);
    // 0042433e  d91b                   -fstp dword ptr [ebx]
    app->getMemory<float>(cpu.ebx) = float(fpu26);
    // 00424340  d95b04                 -fstp dword ptr [ebx + 4]
    app->getMemory<float>(cpu.ebx + x86::reg32(4) /* 0x4 */) = float(fpu27);
    // 00424343  d95b08                 -fstp dword ptr [ebx + 8]
    app->getMemory<float>(cpu.ebx + x86::reg32(8) /* 0x8 */) = float(fpu28);
    // 00424346  8d5de4                 -lea ebx, [ebp - 0x1c]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-28) /* -0x1c */);
    // 00424349  8d55f0                 -lea edx, [ebp - 0x10]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 0042434c  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    }
    // 00424351  e85abc0b00             -call 0x4dffb0
    cpu.esp -= 4;
    sub_4dffb0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00424356  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00424359  8b400c                 -mov eax, dword ptr [eax + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
    // 0042435c  833c85a0c4790000       +cmp dword ptr [eax*4 + 0x79c4a0], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(7980192) /* 0x79c4a0 */ + cpu.eax * 4);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00424364  7418                   -je 0x42437e
    if (cpu.flags.zf)
    {
        goto L_0x0042437e;
    }
    // 00424366  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00424369  8b55fc                 -mov edx, dword ptr [ebp - 4]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 0042436c  8b4004                 -mov eax, dword ptr [eax + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 0042436f  83c22c                 -add edx, 0x2c
    (cpu.edx) += x86::reg32(x86::sreg32(44 /*0x2c*/));
    // 00424372  05c0000000             +add eax, 0xc0
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
    // 00424377  e8f4d1ffff             -call 0x421570
    cpu.esp -= 4;
    sub_421570(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042437c  eb19                   -jmp 0x424397
    goto L_0x00424397;
L_0x0042437e:
    // 0042437e  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00424381  8b7dfc                 -mov edi, dword ptr [ebp - 4]
    cpu.edi = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00424384  8b4004                 -mov eax, dword ptr [eax + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 00424387  b909000000             -mov ecx, 9
    cpu.ecx = 9 /*0x9*/;
    // 0042438c  8d7f2c                 -lea edi, [edi + 0x2c]
    cpu.edi = x86::reg32(cpu.edi + x86::reg32(44) /* 0x2c */);
    // 0042438f  8db0c0000000           -lea esi, [eax + 0xc0]
    cpu.esi = x86::reg32(cpu.eax + x86::reg32(192) /* 0xc0 */);
    // 00424395  f3a5                   -rep movsd dword ptr es:[edi], dword ptr [esi]
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
L_0x00424397:
    // 00424397  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00424399  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042439a  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042439b  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042439c  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042439d  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042439e  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042439f  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip  */
void Application::sub_4243a0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004243a0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004243a1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004243a2  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004243a3  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004243a4  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004243a5  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004243a6  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004243a8  83ec5c                 -sub esp, 0x5c
    (cpu.esp) -= x86::reg32(x86::sreg32(92 /*0x5c*/));
    // 004243ab  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 004243ae  8d7da4                 -lea edi, [ebp - 0x5c]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(-92) /* -0x5c */);
    // 004243b1  8db010010000           -lea esi, [eax + 0x110]
    cpu.esi = x86::reg32(cpu.eax + x86::reg32(272) /* 0x110 */);
    // 004243b7  8b1da8367d00           -mov ebx, dword ptr [0x7d36a8]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(8205992) /* 0x7d36a8 */);
    // 004243bd  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004243be  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004243bf  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004243c0  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 004243c2  8b5004                 -mov edx, dword ptr [eax + 4]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 004243c5  85db                   +test ebx, ebx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & cpu.ebx));
    // 004243c7  740d                   -je 0x4243d6
    if (cpu.flags.zf)
    {
        goto L_0x004243d6;
    }
    // 004243c9  833d60d97c0000         +cmp dword ptr [0x7cd960], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(8182112) /* 0x7cd960 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004243d0  0f84b1020000           -je 0x424687
    if (cpu.flags.zf)
    {
        goto L_0x00424687;
    }
L_0x004243d6:
    // 004243d6  833dec00560000         +cmp dword ptr [0x5600ec], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5636332) /* 0x5600ec */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004243dd  0f85a4020000           -jne 0x424687
    if (!cpu.flags.zf)
    {
        goto L_0x00424687;
    }
    // 004243e3  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004243e6  8b4004                 -mov eax, dword ptr [eax + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 004243e9  81b80c010000f4fd343f   +cmp dword ptr [eax + 0x10c], 0x3f34fdf4
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(268) /* 0x10c */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1060437492 /*0x3f34fdf4*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004243f3  7d36                   -jge 0x42442b
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x0042442b;
    }
    // 004243f5  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004243f8  83b80c01000000         +cmp dword ptr [eax + 0x10c], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(268) /* 0x10c */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004243ff  751b                   -jne 0x42441c
    if (!cpu.flags.zf)
    {
        goto L_0x0042441c;
    }
    // 00424401  83ba9809000000         +cmp dword ptr [edx + 0x998], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(2456) /* 0x998 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00424408  7e07                   -jle 0x424411
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00424411;
    }
    // 0042440a  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 0042440f  eb02                   -jmp 0x424413
    goto L_0x00424413;
L_0x00424411:
    // 00424411  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
L_0x00424413:
    // 00424413  8b4dfc                 -mov ecx, dword ptr [ebp - 4]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00424416  8981fc000000           -mov dword ptr [ecx + 0xfc], eax
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(252) /* 0xfc */) = cpu.eax;
L_0x0042441c:
    // 0042441c  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 0042441f  c7800c01000003000000   -mov dword ptr [eax + 0x10c], 3
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(268) /* 0x10c */) = 3 /*0x3*/;
    // 00424429  eb0c                   -jmp 0x424437
    goto L_0x00424437;
L_0x0042442b:
    // 0042442b  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 0042442e  83b80c01000000         +cmp dword ptr [eax + 0x10c], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(268) /* 0x10c */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00424435  7417                   -je 0x42444e
    if (cpu.flags.zf)
    {
        goto L_0x0042444e;
    }
L_0x00424437:
    // 00424437  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 0042443a  8bb80c010000           -mov edi, dword ptr [eax + 0x10c]
    cpu.edi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(268) /* 0x10c */);
    // 00424440  31f6                   +xor esi, esi
    cpu.clear_co();
    cpu.set_szp((cpu.esi ^= x86::reg32(x86::sreg32(cpu.esi))));
    // 00424442  4f                     +dec edi
    {
        x86::reg32& tmp = cpu.edi;
        cpu.flags.of = 1 & (tmp >> 31);
        tmp--;
        cpu.flags.of &= ~(1 & (tmp >> 31));
        cpu.set_szp(tmp);
    }
    // 00424443  8975f8                 -mov dword ptr [ebp - 8], esi
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.esi;
    // 00424446  89b80c010000           -mov dword ptr [eax + 0x10c], edi
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(268) /* 0x10c */) = cpu.edi;
    // 0042444c  eb30                   -jmp 0x42447e
    goto L_0x0042447e;
L_0x0042444e:
    // 0042444e  ffb11c010000           -push dword ptr [ecx + 0x11c]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(284) /* 0x11c */);
    cpu.esp -= 4;
    // 00424454  e857fbffff             -call 0x423fb0
    cpu.esp -= 4;
    sub_423fb0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00424459  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 0042445c  8b400c                 -mov eax, dword ptr [eax + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
    // 0042445f  8b1c85a0c47900         -mov ebx, dword ptr [eax*4 + 0x79c4a0]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(7980192) /* 0x79c4a0 */ + cpu.eax * 4);
    // 00424466  d95df8                 -fstp dword ptr [ebp - 8]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = cpu.fpu.st(0);
    app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = float(fpu1);
    // 00424469  85db                   +test ebx, ebx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & cpu.ebx));
    cpu.fpu.count -= 1;
    }
    // 0042446b  7511                   -jne 0x42447e
    if (!cpu.flags.zf)
    {
        goto L_0x0042447e;
    }
    // 0042446d  8d45a4                 -lea eax, [ebp - 0x5c]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-92) /* -0x5c */);
    // 00424470  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00424471  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 00424473  ffb120010000           -push dword ptr [ecx + 0x120]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(288) /* 0x120 */);
    cpu.esp -= 4;
    // 00424479  e8b2fbffff             -call 0x424030
    cpu.esp -= 4;
    sub_424030(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x0042447e:
    // 0042447e  8b8228050000           -mov eax, dword ptr [edx + 0x528]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(1320) /* 0x528 */);
    // 00424484  db80c0020000           +fild dword ptr [eax + 0x2c0]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu2 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.eax + x86::reg32(704) /* 0x2c0 */)));
    // 0042448a  dc0dbc6e5300           +fmul qword ptr [0x536ebc]
    x86::Float fpu3 = cpu.fpu.mul(fpu2, x86::Float(app->getMemory<double>(x86::reg32(5467836) /* 0x536ebc */)));
    // 00424490  dd55e0                 +fst qword ptr [ebp - 0x20]
    app->getMemory<double>(cpu.ebp + x86::reg32(-32) /* -0x20 */) = double(fpu3);
    // 00424493  dc1dc46e5300           +fcomp qword ptr [0x536ec4]
    cpu.fpu.compare(fpu3, x86::Float(app->getMemory<double>(x86::reg32(5467844) /* 0x536ec4 */)));
    // 00424499  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 0042449b  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 0042449c  730e                   -jae 0x4244ac
    if (!cpu.flags.cf)
    {
        goto L_0x004244ac;
    }
    // 0042449e  8b45e0                 -mov eax, dword ptr [ebp - 0x20]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-32) /* -0x20 */);
    // 004244a1  8945f0                 -mov dword ptr [ebp - 0x10], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = cpu.eax;
    // 004244a4  8b45e4                 -mov eax, dword ptr [ebp - 0x1c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-28) /* -0x1c */);
    // 004244a7  8945f4                 -mov dword ptr [ebp - 0xc], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.eax;
    // 004244aa  eb0d                   -jmp 0x4244b9
    goto L_0x004244b9;
L_0x004244ac:
    // 004244ac  31f6                   -xor esi, esi
    cpu.esi ^= x86::reg32(x86::sreg32(cpu.esi));
    // 004244ae  bf0000223f             -mov edi, 0x3f220000
    cpu.edi = 1059192832 /*0x3f220000*/;
    // 004244b3  8975f0                 -mov dword ptr [ebp - 0x10], esi
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = cpu.esi;
    // 004244b6  897df4                 -mov dword ptr [ebp - 0xc], edi
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.edi;
L_0x004244b9:
    // 004244b9  d945a8                 -fld dword ptr [ebp - 0x58]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu4 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-88) /* -0x58 */));
    // 004244bc  d9c0                   -fld st(0)
    x86::Float fpu5 = x86::Float(fpu4);
    // 004244be  dc45f0                 -fadd qword ptr [ebp - 0x10]
    x86::Float fpu6 = cpu.fpu.add(fpu5, x86::Float(app->getMemory<double>(cpu.ebp + x86::reg32(-16) /* -0x10 */)));
    // 004244c1  ddd9                   -fstp st(1)
    x86::Float fpu7 = x86::Float(fpu6);
    // 004244c3  d95da8                 -fstp dword ptr [ebp - 0x58]
    app->getMemory<float>(cpu.ebp + x86::reg32(-88) /* -0x58 */) = float(fpu7);
    // 004244c6  d905cc6e5300           -fld dword ptr [0x536ecc]
    x86::Float fpu8 = x86::Float(app->getMemory<float>(x86::reg32(5467852) /* 0x536ecc */));
    // 004244cc  d98218010000           -fld dword ptr [edx + 0x118]
    x86::Float fpu9 = x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(280) /* 0x118 */));
    // 004244d2  d8c9                   -fmul st(1)
    x86::Float fpu10 = cpu.fpu.mul(fpu9, x86::Float(fpu8));
    // 004244d4  d845a8                 -fadd dword ptr [ebp - 0x58]
    x86::Float fpu11 = cpu.fpu.add(fpu10, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-88) /* -0x58 */)));
    // 004244d7  d95da8                 -fstp dword ptr [ebp - 0x58]
    app->getMemory<float>(cpu.ebp + x86::reg32(-88) /* -0x58 */) = float(fpu11);
    // 004244da  d88a1c010000           -fmul dword ptr [edx + 0x11c]
    x86::Float fpu12 = cpu.fpu.mul(fpu8, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(284) /* 0x11c */)));
    // 004244e0  d86dac                 -fsubr dword ptr [ebp - 0x54]
    x86::Float fpu13 = cpu.fpu.sub(x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-84) /* -0x54 */)), fpu12);
    // 004244e3  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004244e6  d95dac                 -fstp dword ptr [ebp - 0x54]
    app->getMemory<float>(cpu.ebp + x86::reg32(-84) /* -0x54 */) = float(fpu13);
    // 004244e9  8b400c                 -mov eax, dword ptr [eax + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
    // 004244ec  833c85a0c4790000       +cmp dword ptr [eax*4 + 0x79c4a0], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(7980192) /* 0x79c4a0 */ + cpu.eax * 4);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    }
    // 004244f4  0f848d000000           -je 0x424587
    if (cpu.flags.zf)
    {
        goto L_0x00424587;
    }
    // 004244fa  8075af80               -xor byte ptr [ebp - 0x51], 0x80
    app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-81) /* -0x51 */) ^= x86::reg8(x86::sreg8(128 /*0x80*/));
    // 004244fe  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00424501  8b4004                 -mov eax, dword ptr [eax + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 00424504  8d90c0000000           -lea edx, [eax + 0xc0]
    cpu.edx = x86::reg32(cpu.eax + x86::reg32(192) /* 0xc0 */);
    // 0042450a  8d5dc8                 -lea ebx, [ebp - 0x38]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-56) /* -0x38 */);
    // 0042450d  8d45a4                 -lea eax, [ebp - 0x5c]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-92) /* -0x5c */);
    // 00424510  d900                   -fld dword ptr [eax]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu14 = x86::Float(app->getMemory<float>(cpu.eax));
    // 00424512  d80a                   -fmul dword ptr [edx]
    x86::Float fpu15 = cpu.fpu.mul(fpu14, x86::Float(app->getMemory<float>(cpu.edx)));
    // 00424514  d900                   -fld dword ptr [eax]
    x86::Float fpu16 = x86::Float(app->getMemory<float>(cpu.eax));
    // 00424516  d84a04                 -fmul dword ptr [edx + 4]
    x86::Float fpu17 = cpu.fpu.mul(fpu16, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(4) /* 0x4 */)));
    // 00424519  d900                   -fld dword ptr [eax]
    x86::Float fpu18 = x86::Float(app->getMemory<float>(cpu.eax));
    // 0042451b  d84a08                 -fmul dword ptr [edx + 8]
    x86::Float fpu19 = cpu.fpu.mul(fpu18, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(8) /* 0x8 */)));
    // 0042451e  d9ca                   -fxch st(2)
    
    // 00424520  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu20 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 00424523  d84a0c                 -fmul dword ptr [edx + 0xc]
    x86::Float fpu21 = cpu.fpu.mul(fpu20, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(12) /* 0xc */)));
    // 00424526  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu22 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 00424529  d84a10                 -fmul dword ptr [edx + 0x10]
    x86::Float fpu23 = cpu.fpu.mul(fpu22, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(16) /* 0x10 */)));
    // 0042452c  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu24 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 0042452f  d84a14                 -fmul dword ptr [edx + 0x14]
    x86::Float fpu25 = cpu.fpu.mul(fpu24, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(20) /* 0x14 */)));
    // 00424532  d9ca                   -fxch st(2)
    
    // 00424534  dec3                   -faddp st(3)
    x86::Float fpu26 = cpu.fpu.add(fpu15, fpu21);
    // 00424536  dec3                   -faddp st(3)
    x86::Float fpu27 = cpu.fpu.add(fpu17, fpu23);
    // 00424538  dec3                   -faddp st(3)
    x86::Float fpu28 = cpu.fpu.add(fpu19, fpu25);
    // 0042453a  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu29 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 0042453d  d84a18                 -fmul dword ptr [edx + 0x18]
    x86::Float fpu30 = cpu.fpu.mul(fpu29, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(24) /* 0x18 */)));
    // 00424540  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu31 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 00424543  d84a1c                 -fmul dword ptr [edx + 0x1c]
    x86::Float fpu32 = cpu.fpu.mul(fpu31, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(28) /* 0x1c */)));
    // 00424546  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu33 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 00424549  d84a20                 -fmul dword ptr [edx + 0x20]
    x86::Float fpu34 = cpu.fpu.mul(fpu33, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(32) /* 0x20 */)));
    // 0042454c  d9ca                   -fxch st(2)
    
    // 0042454e  dec3                   -faddp st(3)
    x86::Float fpu35 = cpu.fpu.add(fpu26, fpu30);
    // 00424550  dec3                   -faddp st(3)
    x86::Float fpu36 = cpu.fpu.add(fpu27, fpu32);
    // 00424552  dec3                   -faddp st(3)
    x86::Float fpu37 = cpu.fpu.add(fpu28, fpu34);
    // 00424554  8d400c                 -lea eax, [eax + 0xc]
    cpu.eax = x86::reg32(cpu.eax + x86::reg32(12) /* 0xc */);
    // 00424557  d91b                   -fstp dword ptr [ebx]
    app->getMemory<float>(cpu.ebx) = float(fpu35);
    // 00424559  d95b04                 -fstp dword ptr [ebx + 4]
    app->getMemory<float>(cpu.ebx + x86::reg32(4) /* 0x4 */) = float(fpu36);
    // 0042455c  d95b08                 -fstp dword ptr [ebx + 8]
    app->getMemory<float>(cpu.ebx + x86::reg32(8) /* 0x8 */) = float(fpu37);
    // 0042455f  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00424562  8b4dfc                 -mov ecx, dword ptr [ebp - 4]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00424565  8b4004                 -mov eax, dword ptr [eax + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 00424568  83c114                 -add ecx, 0x14
    (cpu.ecx) += x86::reg32(x86::sreg32(20 /*0x14*/));
    // 0042456b  8d9098000000           -lea edx, [eax + 0x98]
    cpu.edx = x86::reg32(cpu.eax + x86::reg32(152) /* 0x98 */);
    // 00424571  8d5dc8                 -lea ebx, [ebp - 0x38]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-56) /* -0x38 */);
    // 00424574  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    }
    // 00424579  e832ba0b00             -call 0x4dffb0
    cpu.esp -= 4;
    sub_4dffb0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042457e  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00424580  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00424581  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00424582  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00424583  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00424584  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00424585  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00424586  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x00424587:
    // 00424587  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 0042458a  8b4004                 -mov eax, dword ptr [eax + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 0042458d  8d90c0000000           -lea edx, [eax + 0xc0]
    cpu.edx = x86::reg32(cpu.eax + x86::reg32(192) /* 0xc0 */);
    // 00424593  8d5dc8                 -lea ebx, [ebp - 0x38]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-56) /* -0x38 */);
    // 00424596  8d45a4                 -lea eax, [ebp - 0x5c]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-92) /* -0x5c */);
    // 00424599  d900                   -fld dword ptr [eax]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu38 = x86::Float(app->getMemory<float>(cpu.eax));
    // 0042459b  d80a                   -fmul dword ptr [edx]
    x86::Float fpu39 = cpu.fpu.mul(fpu38, x86::Float(app->getMemory<float>(cpu.edx)));
    // 0042459d  d900                   -fld dword ptr [eax]
    x86::Float fpu40 = x86::Float(app->getMemory<float>(cpu.eax));
    // 0042459f  d84a04                 -fmul dword ptr [edx + 4]
    x86::Float fpu41 = cpu.fpu.mul(fpu40, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(4) /* 0x4 */)));
    // 004245a2  d900                   -fld dword ptr [eax]
    x86::Float fpu42 = x86::Float(app->getMemory<float>(cpu.eax));
    // 004245a4  d84a08                 -fmul dword ptr [edx + 8]
    x86::Float fpu43 = cpu.fpu.mul(fpu42, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(8) /* 0x8 */)));
    // 004245a7  d9ca                   -fxch st(2)
    
    // 004245a9  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu44 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 004245ac  d84a0c                 -fmul dword ptr [edx + 0xc]
    x86::Float fpu45 = cpu.fpu.mul(fpu44, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(12) /* 0xc */)));
    // 004245af  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu46 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 004245b2  d84a10                 -fmul dword ptr [edx + 0x10]
    x86::Float fpu47 = cpu.fpu.mul(fpu46, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(16) /* 0x10 */)));
    // 004245b5  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu48 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 004245b8  d84a14                 -fmul dword ptr [edx + 0x14]
    x86::Float fpu49 = cpu.fpu.mul(fpu48, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(20) /* 0x14 */)));
    // 004245bb  d9ca                   -fxch st(2)
    
    // 004245bd  dec3                   -faddp st(3)
    x86::Float fpu50 = cpu.fpu.add(fpu39, fpu45);
    // 004245bf  dec3                   -faddp st(3)
    x86::Float fpu51 = cpu.fpu.add(fpu41, fpu47);
    // 004245c1  dec3                   -faddp st(3)
    x86::Float fpu52 = cpu.fpu.add(fpu43, fpu49);
    // 004245c3  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu53 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 004245c6  d84a18                 -fmul dword ptr [edx + 0x18]
    x86::Float fpu54 = cpu.fpu.mul(fpu53, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(24) /* 0x18 */)));
    // 004245c9  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu55 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 004245cc  d84a1c                 -fmul dword ptr [edx + 0x1c]
    x86::Float fpu56 = cpu.fpu.mul(fpu55, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(28) /* 0x1c */)));
    // 004245cf  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu57 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 004245d2  d84a20                 -fmul dword ptr [edx + 0x20]
    x86::Float fpu58 = cpu.fpu.mul(fpu57, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(32) /* 0x20 */)));
    // 004245d5  d9ca                   -fxch st(2)
    
    // 004245d7  dec3                   -faddp st(3)
    x86::Float fpu59 = cpu.fpu.add(fpu50, fpu54);
    // 004245d9  dec3                   -faddp st(3)
    x86::Float fpu60 = cpu.fpu.add(fpu51, fpu56);
    // 004245db  dec3                   -faddp st(3)
    x86::Float fpu61 = cpu.fpu.add(fpu52, fpu58);
    // 004245dd  8d400c                 -lea eax, [eax + 0xc]
    cpu.eax = x86::reg32(cpu.eax + x86::reg32(12) /* 0xc */);
    // 004245e0  d91b                   -fstp dword ptr [ebx]
    app->getMemory<float>(cpu.ebx) = float(fpu59);
    // 004245e2  d95b04                 -fstp dword ptr [ebx + 4]
    app->getMemory<float>(cpu.ebx + x86::reg32(4) /* 0x4 */) = float(fpu60);
    // 004245e5  d95b08                 -fstp dword ptr [ebx + 8]
    app->getMemory<float>(cpu.ebx + x86::reg32(8) /* 0x8 */) = float(fpu61);
    // 004245e8  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004245eb  83b80c01000001         +cmp dword ptr [eax + 0x10c], 1
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(268) /* 0x10c */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1 /*0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    }
    // 004245f2  7515                   -jne 0x424609
    if (!cpu.flags.zf)
    {
        goto L_0x00424609;
    }
    // 004245f4  8d7dbc                 -lea edi, [ebp - 0x44]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(-68) /* -0x44 */);
    // 004245f7  8d75c8                 -lea esi, [ebp - 0x38]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(-56) /* -0x38 */);
    // 004245fa  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004245fb  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004245fc  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004245fd  c7800c01000000000000   -mov dword ptr [eax + 0x10c], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(268) /* 0x10c */) = 0 /*0x0*/;
    // 00424607  eb21                   -jmp 0x42462a
    goto L_0x0042462a;
L_0x00424609:
    // 00424609  8b400c                 -mov eax, dword ptr [eax + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
    // 0042460c  833cc510105e0000       +cmp dword ptr [eax*8 + 0x5e1010], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(6164496) /* 0x5e1010 */ + cpu.eax * 8);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00424614  7408                   -je 0x42461e
    if (cpu.flags.zf)
    {
        goto L_0x0042461e;
    }
    // 00424616  8d7dbc                 -lea edi, [ebp - 0x44]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(-68) /* -0x44 */);
    // 00424619  8d75c8                 -lea esi, [ebp - 0x38]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(-56) /* -0x38 */);
    // 0042461c  eb09                   -jmp 0x424627
    goto L_0x00424627;
L_0x0042461e:
    // 0042461e  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00424621  8d7dbc                 -lea edi, [ebp - 0x44]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(-68) /* -0x44 */);
    // 00424624  8d7020                 -lea esi, [eax + 0x20]
    cpu.esi = x86::reg32(cpu.eax + x86::reg32(32) /* 0x20 */);
L_0x00424627:
    // 00424627  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00424628  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00424629  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
L_0x0042462a:
    // 0042462a  8d4dd4                 -lea ecx, [ebp - 0x2c]
    cpu.ecx = x86::reg32(cpu.ebp + x86::reg32(-44) /* -0x2c */);
    // 0042462d  8d5dbc                 -lea ebx, [ebp - 0x44]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-68) /* -0x44 */);
    // 00424630  8d55c8                 -lea edx, [ebp - 0x38]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-56) /* -0x38 */);
    // 00424633  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 00424638  8b75fc                 -mov esi, dword ptr [ebp - 4]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 0042463b  e8c0b90b00             -call 0x4e0000
    cpu.esp -= 4;
    sub_4e0000(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00424640  8d45b0                 -lea eax, [ebp - 0x50]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-80) /* -0x50 */);
    // 00424643  8d55d4                 -lea edx, [ebp - 0x2c]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-44) /* -0x2c */);
    // 00424646  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00424647  8d5db0                 -lea ebx, [ebp - 0x50]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-80) /* -0x50 */);
    // 0042464a  83c620                 -add esi, 0x20
    (cpu.esi) += x86::reg32(x86::sreg32(32 /*0x20*/));
    // 0042464d  ff75f8                 -push dword ptr [ebp - 8]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    cpu.esp -= 4;
    // 00424650  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 00424655  89f1                   -mov ecx, esi
    cpu.ecx = cpu.esi;
    // 00424657  e8f4b90b00             -call 0x4e0050
    cpu.esp -= 4;
    sub_4e0050(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042465c  8d55bc                 -lea edx, [ebp - 0x44]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-68) /* -0x44 */);
    // 0042465f  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 00424664  e847b90b00             -call 0x4dffb0
    cpu.esp -= 4;
    sub_4dffb0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00424669  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 0042466c  8b4dfc                 -mov ecx, dword ptr [ebp - 4]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 0042466f  8b4004                 -mov eax, dword ptr [eax + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 00424672  89f3                   -mov ebx, esi
    cpu.ebx = cpu.esi;
    // 00424674  8d9098000000           -lea edx, [eax + 0x98]
    cpu.edx = x86::reg32(cpu.eax + x86::reg32(152) /* 0x98 */);
    // 0042467a  83c114                 -add ecx, 0x14
    (cpu.ecx) += x86::reg32(x86::sreg32(20 /*0x14*/));
    // 0042467d  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 00424682  e829b90b00             -call 0x4dffb0
    cpu.esp -= 4;
    sub_4dffb0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00424687:
    // 00424687  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00424689  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042468a  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042468b  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042468c  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042468d  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042468e  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042468f  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip  */
void Application::sub_424690(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00424690  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00424691  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00424692  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00424693  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00424694  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00424696  83ec18                 -sub esp, 0x18
    (cpu.esp) -= x86::reg32(x86::sreg32(24 /*0x18*/));
    // 00424699  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 0042469b  8b4004                 -mov eax, dword ptr [eax + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 0042469e  f6800002000020         +test byte ptr [eax + 0x200], 0x20
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(cpu.eax + x86::reg32(512) /* 0x200 */) & 32 /*0x20*/));
    // 004246a5  7406                   -je 0x4246ad
    if (cpu.flags.zf)
    {
        goto L_0x004246ad;
    }
    // 004246a7  8b80a4090000           -mov eax, dword ptr [eax + 0x9a4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(2468) /* 0x9a4 */);
L_0x004246ad:
    // 004246ad  8b9098000000           -mov edx, dword ptr [eax + 0x98]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(152) /* 0x98 */);
    // 004246b3  8955e8                 -mov dword ptr [ebp - 0x18], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-24) /* -0x18 */) = cpu.edx;
    // 004246b6  8b909c000000           -mov edx, dword ptr [eax + 0x9c]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(156) /* 0x9c */);
    // 004246bc  8955ec                 -mov dword ptr [ebp - 0x14], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */) = cpu.edx;
    // 004246bf  8b90a0000000           -mov edx, dword ptr [eax + 0xa0]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(160) /* 0xa0 */);
    // 004246c5  8955f0                 -mov dword ptr [ebp - 0x10], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = cpu.edx;
    // 004246c8  894108                 -mov dword ptr [ecx + 8], eax
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(8) /* 0x8 */) = cpu.eax;
    // 004246cb  8b15a8367d00           -mov edx, dword ptr [0x7d36a8]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205992) /* 0x7d36a8 */);
    // 004246d1  894104                 -mov dword ptr [ecx + 4], eax
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(4) /* 0x4 */) = cpu.eax;
    // 004246d4  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 004246d6  7409                   -je 0x4246e1
    if (cpu.flags.zf)
    {
        goto L_0x004246e1;
    }
    // 004246d8  833d60d97c0000         +cmp dword ptr [0x7cd960], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(8182112) /* 0x7cd960 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004246df  7453                   -je 0x424734
    if (cpu.flags.zf)
    {
        goto L_0x00424734;
    }
L_0x004246e1:
    // 004246e1  833dec00560000         +cmp dword ptr [0x5600ec], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5636332) /* 0x5600ec */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004246e8  754a                   -jne 0x424734
    if (!cpu.flags.zf)
    {
        goto L_0x00424734;
    }
    // 004246ea  db0584367d00           -fild dword ptr [0x7d3684]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(8205956) /* 0x7d3684 */)));
    // 004246f0  d80dd06e5300           -fmul dword ptr [0x536ed0]
    x86::Float fpu2 = cpu.fpu.mul(fpu1, x86::Float(app->getMemory<float>(x86::reg32(5467856) /* 0x536ed0 */)));
    // 004246f6  8d5dfc                 -lea ebx, [ebp - 4]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004246f9  8d55f4                 -lea edx, [ebp - 0xc]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 004246fc  8d45f8                 -lea eax, [ebp - 8]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004246ff  d95df8                 -fstp dword ptr [ebp - 8]
    app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = float(fpu2);
    }
    // 00424702  e869620c00             -call 0x4ea970
    cpu.esp -= 4;
    sub_4ea970(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00424707  d945fc                 -fld dword ptr [ebp - 4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu3 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */));
    // 0042470a  d80dd46e5300           -fmul dword ptr [0x536ed4]
    x86::Float fpu4 = cpu.fpu.mul(fpu3, x86::Float(app->getMemory<float>(x86::reg32(5467860) /* 0x536ed4 */)));
    // 00424710  d845e8                 -fadd dword ptr [ebp - 0x18]
    x86::Float fpu5 = cpu.fpu.add(fpu4, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-24) /* -0x18 */)));
    // 00424713  d95914                 -fstp dword ptr [ecx + 0x14]
    app->getMemory<float>(cpu.ecx + x86::reg32(20) /* 0x14 */) = float(fpu5);
    // 00424716  d945f4                 -fld dword ptr [ebp - 0xc]
    x86::Float fpu6 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */));
    // 00424719  d80dd86e5300           -fmul dword ptr [0x536ed8]
    x86::Float fpu7 = cpu.fpu.mul(fpu6, x86::Float(app->getMemory<float>(x86::reg32(5467864) /* 0x536ed8 */)));
    // 0042471f  d845ec                 -fadd dword ptr [ebp - 0x14]
    x86::Float fpu8 = cpu.fpu.add(fpu7, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-20) /* -0x14 */)));
    // 00424722  d95918                 -fstp dword ptr [ecx + 0x18]
    app->getMemory<float>(cpu.ecx + x86::reg32(24) /* 0x18 */) = float(fpu8);
    // 00424725  d945f4                 -fld dword ptr [ebp - 0xc]
    x86::Float fpu9 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */));
    // 00424728  d80ddc6e5300           -fmul dword ptr [0x536edc]
    x86::Float fpu10 = cpu.fpu.mul(fpu9, x86::Float(app->getMemory<float>(x86::reg32(5467868) /* 0x536edc */)));
    // 0042472e  d845f0                 -fadd dword ptr [ebp - 0x10]
    x86::Float fpu11 = cpu.fpu.add(fpu10, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-16) /* -0x10 */)));
    // 00424731  d9591c                 -fstp dword ptr [ecx + 0x1c]
    app->getMemory<float>(cpu.ecx + x86::reg32(28) /* 0x1c */) = float(fpu11);
    }
L_0x00424734:
    // 00424734  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00424736  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00424737  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00424738  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00424739  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042473a  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x40 0x00 0x8b 0xc9 */
void Application::sub_424740(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00424740  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00424741  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00424742  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00424743  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00424744  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00424745  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00424746  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00424748  83ec78                 -sub esp, 0x78
    (cpu.esp) -= x86::reg32(x86::sreg32(120 /*0x78*/));
    // 0042474b  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 0042474e  8d7da0                 -lea edi, [ebp - 0x60]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(-96) /* -0x60 */);
    // 00424751  8db010010000           -lea esi, [eax + 0x110]
    cpu.esi = x86::reg32(cpu.eax + x86::reg32(272) /* 0x110 */);
    // 00424757  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00424758  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00424759  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 0042475a  8b5004                 -mov edx, dword ptr [eax + 4]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 0042475d  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 0042475f  8b8298000000           -mov eax, dword ptr [edx + 0x98]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(152) /* 0x98 */);
    // 00424765  8945c4                 -mov dword ptr [ebp - 0x3c], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-60) /* -0x3c */) = cpu.eax;
    // 00424768  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 0042476a  8b4004                 -mov eax, dword ptr [eax + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 0042476d  8b809c000000           -mov eax, dword ptr [eax + 0x9c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(156) /* 0x9c */);
    // 00424773  8945c8                 -mov dword ptr [ebp - 0x38], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-56) /* -0x38 */) = cpu.eax;
    // 00424776  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00424778  8b4004                 -mov eax, dword ptr [eax + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 0042477b  8b80a0000000           -mov eax, dword ptr [eax + 0xa0]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(160) /* 0xa0 */);
    // 00424781  8b1da8367d00           -mov ebx, dword ptr [0x7d36a8]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(8205992) /* 0x7d36a8 */);
    // 00424787  8945cc                 -mov dword ptr [ebp - 0x34], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-52) /* -0x34 */) = cpu.eax;
    // 0042478a  85db                   +test ebx, ebx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & cpu.ebx));
    // 0042478c  740d                   -je 0x42479b
    if (cpu.flags.zf)
    {
        goto L_0x0042479b;
    }
    // 0042478e  833d60d97c0000         +cmp dword ptr [0x7cd960], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(8182112) /* 0x7cd960 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00424795  0f84a1030000           -je 0x424b3c
    if (cpu.flags.zf)
    {
        goto L_0x00424b3c;
    }
L_0x0042479b:
    // 0042479b  8b3dec005600           -mov edi, dword ptr [0x5600ec]
    cpu.edi = app->getMemory<x86::reg32>(x86::reg32(5636332) /* 0x5600ec */);
    // 004247a1  85ff                   +test edi, edi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edi & cpu.edi));
    // 004247a3  0f8593030000           -jne 0x424b3c
    if (!cpu.flags.zf)
    {
        goto L_0x00424b3c;
    }
    // 004247a9  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004247ac  8b400c                 -mov eax, dword ptr [eax + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
    // 004247af  833cc514105e0020       +cmp dword ptr [eax*8 + 0x5e1014], 0x20
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(6164500) /* 0x5e1014 */ + cpu.eax * 8);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(32 /*0x20*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004247b7  7e13                   -jle 0x4247cc
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004247cc;
    }
    // 004247b9  b8000050c0             -mov eax, 0xc0500000
    cpu.eax = 3226468352 /*0xc0500000*/;
    // 004247be  897da0                 -mov dword ptr [ebp - 0x60], edi
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-96) /* -0x60 */) = cpu.edi;
    // 004247c1  bf0000803f             -mov edi, 0x3f800000
    cpu.edi = 1065353216 /*0x3f800000*/;
    // 004247c6  8945a8                 -mov dword ptr [ebp - 0x58], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-88) /* -0x58 */) = cpu.eax;
    // 004247c9  897da4                 -mov dword ptr [ebp - 0x5c], edi
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-92) /* -0x5c */) = cpu.edi;
L_0x004247cc:
    // 004247cc  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004247cf  8b4004                 -mov eax, dword ptr [eax + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 004247d2  81b80c010000f4fd343f   +cmp dword ptr [eax + 0x10c], 0x3f34fdf4
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(268) /* 0x10c */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1060437492 /*0x3f34fdf4*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004247dc  7d36                   -jge 0x424814
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00424814;
    }
    // 004247de  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004247e1  83b80c01000000         +cmp dword ptr [eax + 0x10c], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(268) /* 0x10c */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004247e8  751b                   -jne 0x424805
    if (!cpu.flags.zf)
    {
        goto L_0x00424805;
    }
    // 004247ea  83ba9809000000         +cmp dword ptr [edx + 0x998], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(2456) /* 0x998 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004247f1  7e07                   -jle 0x4247fa
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004247fa;
    }
    // 004247f3  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 004247f8  eb02                   -jmp 0x4247fc
    goto L_0x004247fc;
L_0x004247fa:
    // 004247fa  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
L_0x004247fc:
    // 004247fc  8b4dfc                 -mov ecx, dword ptr [ebp - 4]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004247ff  8981fc000000           -mov dword ptr [ecx + 0xfc], eax
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(252) /* 0xfc */) = cpu.eax;
L_0x00424805:
    // 00424805  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00424808  c7800c01000003000000   -mov dword ptr [eax + 0x10c], 3
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(268) /* 0x10c */) = 3 /*0x3*/;
    // 00424812  eb0c                   -jmp 0x424820
    goto L_0x00424820;
L_0x00424814:
    // 00424814  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00424817  83b80c01000000         +cmp dword ptr [eax + 0x10c], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(268) /* 0x10c */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0042481e  7417                   -je 0x424837
    if (cpu.flags.zf)
    {
        goto L_0x00424837;
    }
L_0x00424820:
    // 00424820  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00424823  8bb80c010000           -mov edi, dword ptr [eax + 0x10c]
    cpu.edi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(268) /* 0x10c */);
    // 00424829  31f6                   +xor esi, esi
    cpu.clear_co();
    cpu.set_szp((cpu.esi ^= x86::reg32(x86::sreg32(cpu.esi))));
    // 0042482b  4f                     +dec edi
    {
        x86::reg32& tmp = cpu.edi;
        cpu.flags.of = 1 & (tmp >> 31);
        tmp--;
        cpu.flags.of &= ~(1 & (tmp >> 31));
        cpu.set_szp(tmp);
    }
    // 0042482c  8975e4                 -mov dword ptr [ebp - 0x1c], esi
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-28) /* -0x1c */) = cpu.esi;
    // 0042482f  89b80c010000           -mov dword ptr [eax + 0x10c], edi
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(268) /* 0x10c */) = cpu.edi;
    // 00424835  eb30                   -jmp 0x424867
    goto L_0x00424867;
L_0x00424837:
    // 00424837  ffb11c010000           -push dword ptr [ecx + 0x11c]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(284) /* 0x11c */);
    cpu.esp -= 4;
    // 0042483d  e86ef7ffff             -call 0x423fb0
    cpu.esp -= 4;
    sub_423fb0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00424842  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00424845  8b400c                 -mov eax, dword ptr [eax + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
    // 00424848  8b1c85a0c47900         -mov ebx, dword ptr [eax*4 + 0x79c4a0]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(7980192) /* 0x79c4a0 */ + cpu.eax * 4);
    // 0042484f  d95de4                 -fstp dword ptr [ebp - 0x1c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = cpu.fpu.st(0);
    app->getMemory<float>(cpu.ebp + x86::reg32(-28) /* -0x1c */) = float(fpu1);
    // 00424852  85db                   +test ebx, ebx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & cpu.ebx));
    cpu.fpu.count -= 1;
    }
    // 00424854  7511                   -jne 0x424867
    if (!cpu.flags.zf)
    {
        goto L_0x00424867;
    }
    // 00424856  8d45a0                 -lea eax, [ebp - 0x60]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-96) /* -0x60 */);
    // 00424859  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 0042485a  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 0042485c  ffb120010000           -push dword ptr [ecx + 0x120]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(288) /* 0x120 */);
    cpu.esp -= 4;
    // 00424862  e8c9f7ffff             -call 0x424030
    cpu.esp -= 4;
    sub_424030(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00424867:
    // 00424867  d905e06e5300           +fld dword ptr [0x536ee0]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu2 = x86::Float(app->getMemory<float>(x86::reg32(5467872) /* 0x536ee0 */));
    // 0042486d  d98218010000           +fld dword ptr [edx + 0x118]
    x86::Float fpu3 = x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(280) /* 0x118 */));
    // 00424873  d8c9                   +fmul st(1)
    x86::Float fpu4 = cpu.fpu.mul(fpu3, x86::Float(fpu2));
    // 00424875  d845a4                 +fadd dword ptr [ebp - 0x5c]
    x86::Float fpu5 = cpu.fpu.add(fpu4, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-92) /* -0x5c */)));
    // 00424878  d95da4                 +fstp dword ptr [ebp - 0x5c]
    app->getMemory<float>(cpu.ebp + x86::reg32(-92) /* -0x5c */) = float(fpu5);
    // 0042487b  d88a1c010000           +fmul dword ptr [edx + 0x11c]
    x86::Float fpu6 = cpu.fpu.mul(fpu2, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(284) /* 0x11c */)));
    // 00424881  d86da8                 +fsubr dword ptr [ebp - 0x58]
    x86::Float fpu7 = cpu.fpu.sub(x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-88) /* -0x58 */)), fpu6);
    // 00424884  d9ee                   +fldz 
    x86::Float fpu8 = 0.0;
    // 00424886  d9c9                   +fxch st(1)
    
    // 00424888  d95da8                 +fstp dword ptr [ebp - 0x58]
    app->getMemory<float>(cpu.ebp + x86::reg32(-88) /* -0x58 */) = float(fpu7);
    // 0042488b  d89aec040000           +fcomp dword ptr [edx + 0x4ec]
    cpu.fpu.compare(fpu8, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(1260) /* 0x4ec */)));
    // 00424891  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00424893  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 00424894  760d                   -jbe 0x4248a3
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x004248a3;
    }
    // 00424896  d982ec040000           +fld dword ptr [edx + 0x4ec]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu9 = x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(1260) /* 0x4ec */));
    // 0042489c  d9e0                   +fchs 
    x86::Float fpu10 = -fpu9;
    // 0042489e  d95dec                 +fstp dword ptr [ebp - 0x14]
    app->getMemory<float>(cpu.ebp + x86::reg32(-20) /* -0x14 */) = float(fpu10);
    }
    // 004248a1  eb09                   -jmp 0x4248ac
    goto L_0x004248ac;
L_0x004248a3:
    // 004248a3  8b82ec040000           -mov eax, dword ptr [edx + 0x4ec]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(1260) /* 0x4ec */);
    // 004248a9  8945ec                 -mov dword ptr [ebp - 0x14], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */) = cpu.eax;
L_0x004248ac:
    // 004248ac  d9ee                   +fldz 
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu11 = 0.0;
    // 004248ae  d89af4040000           +fcomp dword ptr [edx + 0x4f4]
    cpu.fpu.compare(fpu11, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(1268) /* 0x4f4 */)));
    // 004248b4  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 004248b6  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 004248b7  760d                   -jbe 0x4248c6
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x004248c6;
    }
    // 004248b9  d982f4040000           +fld dword ptr [edx + 0x4f4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu12 = x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(1268) /* 0x4f4 */));
    // 004248bf  d9e0                   +fchs 
    x86::Float fpu13 = -fpu12;
    // 004248c1  d95df0                 +fstp dword ptr [ebp - 0x10]
    app->getMemory<float>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = float(fpu13);
    }
    // 004248c4  eb09                   -jmp 0x4248cf
    goto L_0x004248cf;
L_0x004248c6:
    // 004248c6  8b82f4040000           -mov eax, dword ptr [edx + 0x4f4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(1268) /* 0x4f4 */);
    // 004248cc  8945f0                 -mov dword ptr [ebp - 0x10], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = cpu.eax;
L_0x004248cf:
    // 004248cf  d945ec                 +fld dword ptr [ebp - 0x14]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu14 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-20) /* -0x14 */));
    // 004248d2  d85df0                 +fcomp dword ptr [ebp - 0x10]
    cpu.fpu.compare(fpu14, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-16) /* -0x10 */)));
    // 004248d5  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 004248d7  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 004248d8  765c                   -jbe 0x424936
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x00424936;
    }
    // 004248da  d9ee                   +fldz 
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu15 = 0.0;
    // 004248dc  d89af4040000           +fcomp dword ptr [edx + 0x4f4]
    cpu.fpu.compare(fpu15, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(1268) /* 0x4f4 */)));
    // 004248e2  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 004248e4  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 004248e5  760d                   -jbe 0x4248f4
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x004248f4;
    }
    // 004248e7  d982f4040000           +fld dword ptr [edx + 0x4f4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu16 = x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(1268) /* 0x4f4 */));
    // 004248ed  d9e0                   +fchs 
    x86::Float fpu17 = -fpu16;
    // 004248ef  d95de0                 +fstp dword ptr [ebp - 0x20]
    app->getMemory<float>(cpu.ebp + x86::reg32(-32) /* -0x20 */) = float(fpu17);
    }
    // 004248f2  eb09                   -jmp 0x4248fd
    goto L_0x004248fd;
L_0x004248f4:
    // 004248f4  8b82f4040000           -mov eax, dword ptr [edx + 0x4f4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(1268) /* 0x4f4 */);
    // 004248fa  8945e0                 -mov dword ptr [ebp - 0x20], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-32) /* -0x20 */) = cpu.eax;
L_0x004248fd:
    // 004248fd  d945e0                 +fld dword ptr [ebp - 0x20]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu18 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-32) /* -0x20 */));
    // 00424900  d80de46e5300           +fmul dword ptr [0x536ee4]
    x86::Float fpu19 = cpu.fpu.mul(fpu18, x86::Float(app->getMemory<float>(x86::reg32(5467876) /* 0x536ee4 */)));
    // 00424906  d9ee                   +fldz 
    x86::Float fpu20 = 0.0;
    // 00424908  d9c9                   +fxch st(1)
    
    // 0042490a  d95dd0                 +fstp dword ptr [ebp - 0x30]
    app->getMemory<float>(cpu.ebp + x86::reg32(-48) /* -0x30 */) = float(fpu19);
    // 0042490d  d89aec040000           +fcomp dword ptr [edx + 0x4ec]
    cpu.fpu.compare(fpu20, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(1260) /* 0x4ec */)));
    // 00424913  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00424915  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 00424916  760d                   -jbe 0x424925
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x00424925;
    }
    // 00424918  d982ec040000           +fld dword ptr [edx + 0x4ec]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu21 = x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(1260) /* 0x4ec */));
    // 0042491e  d9e0                   +fchs 
    x86::Float fpu22 = -fpu21;
    // 00424920  d95dd8                 +fstp dword ptr [ebp - 0x28]
    app->getMemory<float>(cpu.ebp + x86::reg32(-40) /* -0x28 */) = float(fpu22);
    }
    // 00424923  eb09                   -jmp 0x42492e
    goto L_0x0042492e;
L_0x00424925:
    // 00424925  8b82ec040000           -mov eax, dword ptr [edx + 0x4ec]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(1260) /* 0x4ec */);
    // 0042492b  8945d8                 -mov dword ptr [ebp - 0x28], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-40) /* -0x28 */) = cpu.eax;
L_0x0042492e:
    // 0042492e  d945d8                 +fld dword ptr [ebp - 0x28]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu23 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-40) /* -0x28 */));
    // 00424931  d845d0                 +fadd dword ptr [ebp - 0x30]
    x86::Float fpu24 = cpu.fpu.add(fpu23, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-48) /* -0x30 */)));
    cpu.fpu.count += 1;
    cpu.fpu.st(0) = fpu24;
    }
    // 00424934  eb5a                   -jmp 0x424990
    goto L_0x00424990;
L_0x00424936:
    // 00424936  d9ee                   +fldz 
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu25 = 0.0;
    // 00424938  d89aec040000           +fcomp dword ptr [edx + 0x4ec]
    cpu.fpu.compare(fpu25, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(1260) /* 0x4ec */)));
    // 0042493e  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00424940  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 00424941  760d                   -jbe 0x424950
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x00424950;
    }
    // 00424943  d982ec040000           +fld dword ptr [edx + 0x4ec]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu26 = x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(1260) /* 0x4ec */));
    // 00424949  d9e0                   +fchs 
    x86::Float fpu27 = -fpu26;
    // 0042494b  d95de8                 +fstp dword ptr [ebp - 0x18]
    app->getMemory<float>(cpu.ebp + x86::reg32(-24) /* -0x18 */) = float(fpu27);
    }
    // 0042494e  eb09                   -jmp 0x424959
    goto L_0x00424959;
L_0x00424950:
    // 00424950  8b82ec040000           -mov eax, dword ptr [edx + 0x4ec]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(1260) /* 0x4ec */);
    // 00424956  8945e8                 -mov dword ptr [ebp - 0x18], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-24) /* -0x18 */) = cpu.eax;
L_0x00424959:
    // 00424959  d945e8                 +fld dword ptr [ebp - 0x18]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu28 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-24) /* -0x18 */));
    // 0042495c  d80de46e5300           +fmul dword ptr [0x536ee4]
    x86::Float fpu29 = cpu.fpu.mul(fpu28, x86::Float(app->getMemory<float>(x86::reg32(5467876) /* 0x536ee4 */)));
    // 00424962  d9ee                   +fldz 
    x86::Float fpu30 = 0.0;
    // 00424964  d9c9                   +fxch st(1)
    
    // 00424966  d95dd4                 +fstp dword ptr [ebp - 0x2c]
    app->getMemory<float>(cpu.ebp + x86::reg32(-44) /* -0x2c */) = float(fpu29);
    // 00424969  d89af4040000           +fcomp dword ptr [edx + 0x4f4]
    cpu.fpu.compare(fpu30, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(1268) /* 0x4f4 */)));
    // 0042496f  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00424971  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 00424972  760d                   -jbe 0x424981
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x00424981;
    }
    // 00424974  d982f4040000           +fld dword ptr [edx + 0x4f4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu31 = x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(1268) /* 0x4f4 */));
    // 0042497a  d9e0                   +fchs 
    x86::Float fpu32 = -fpu31;
    // 0042497c  d95ddc                 +fstp dword ptr [ebp - 0x24]
    app->getMemory<float>(cpu.ebp + x86::reg32(-36) /* -0x24 */) = float(fpu32);
    }
    // 0042497f  eb09                   -jmp 0x42498a
    goto L_0x0042498a;
L_0x00424981:
    // 00424981  8b82f4040000           -mov eax, dword ptr [edx + 0x4f4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(1268) /* 0x4f4 */);
    // 00424987  8945dc                 -mov dword ptr [ebp - 0x24], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-36) /* -0x24 */) = cpu.eax;
L_0x0042498a:
    // 0042498a  d945dc                 +fld dword ptr [ebp - 0x24]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu33 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-36) /* -0x24 */));
    // 0042498d  d845d4                 +fadd dword ptr [ebp - 0x2c]
    x86::Float fpu34 = cpu.fpu.add(fpu33, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-44) /* -0x2c */)));
    cpu.fpu.count += 1;
    cpu.fpu.st(0) = fpu34;
    }
L_0x00424990:
    // 00424990  d95df4                 +fstp dword ptr [ebp - 0xc]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu35 = cpu.fpu.st(0);
    app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */) = float(fpu35);
    // 00424993  d945f4                 +fld dword ptr [ebp - 0xc]
    x86::Float fpu36 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */));
    // 00424996  d80de86e5300           +fmul dword ptr [0x536ee8]
    x86::Float fpu37 = cpu.fpu.mul(fpu36, x86::Float(app->getMemory<float>(x86::reg32(5467880) /* 0x536ee8 */)));
    // 0042499c  d955f8                 +fst dword ptr [ebp - 8]
    app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = float(fpu37);
    // 0042499f  d81dec6e5300           +fcomp dword ptr [0x536eec]
    cpu.fpu.compare(fpu37, x86::Float(app->getMemory<float>(x86::reg32(5467884) /* 0x536eec */)));
    // 004249a5  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 004249a7  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    cpu.fpu.count -= 1;
    }
    // 004249a8  7607                   -jbe 0x4249b1
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x004249b1;
    }
    // 004249aa  c745f80000c040         -mov dword ptr [ebp - 8], 0x40c00000
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = 1086324736 /*0x40c00000*/;
L_0x004249b1:
    // 004249b1  d945a8                 -fld dword ptr [ebp - 0x58]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu38 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-88) /* -0x58 */));
    // 004249b4  d865f8                 -fsub dword ptr [ebp - 8]
    x86::Float fpu39 = cpu.fpu.sub(fpu38, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    // 004249b7  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004249ba  d95da8                 -fstp dword ptr [ebp - 0x58]
    app->getMemory<float>(cpu.ebp + x86::reg32(-88) /* -0x58 */) = float(fpu39);
    // 004249bd  8b400c                 -mov eax, dword ptr [eax + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
    // 004249c0  833c85a0c4790000       +cmp dword ptr [eax*4 + 0x79c4a0], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(7980192) /* 0x79c4a0 */ + cpu.eax * 4);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    }
    // 004249c8  747b                   -je 0x424a45
    if (cpu.flags.zf)
    {
        goto L_0x00424a45;
    }
    // 004249ca  8075ab80               -xor byte ptr [ebp - 0x55], 0x80
    app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-85) /* -0x55 */) ^= x86::reg8(x86::sreg8(128 /*0x80*/));
    // 004249ce  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004249d1  8b4004                 -mov eax, dword ptr [eax + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 004249d4  8d5db8                 -lea ebx, [ebp - 0x48]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-72) /* -0x48 */);
    // 004249d7  8d90c0000000           -lea edx, [eax + 0xc0]
    cpu.edx = x86::reg32(cpu.eax + x86::reg32(192) /* 0xc0 */);
    // 004249dd  8b4dfc                 -mov ecx, dword ptr [ebp - 4]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004249e0  8d45a0                 -lea eax, [ebp - 0x60]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-96) /* -0x60 */);
    // 004249e3  83c114                 +add ecx, 0x14
    {
        x86::reg32& tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(20 /*0x14*/));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 004249e6  d900                   +fld dword ptr [eax]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu40 = x86::Float(app->getMemory<float>(cpu.eax));
    // 004249e8  d80a                   +fmul dword ptr [edx]
    x86::Float fpu41 = cpu.fpu.mul(fpu40, x86::Float(app->getMemory<float>(cpu.edx)));
    // 004249ea  d900                   +fld dword ptr [eax]
    x86::Float fpu42 = x86::Float(app->getMemory<float>(cpu.eax));
    // 004249ec  d84a04                 +fmul dword ptr [edx + 4]
    x86::Float fpu43 = cpu.fpu.mul(fpu42, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(4) /* 0x4 */)));
    // 004249ef  d900                   +fld dword ptr [eax]
    x86::Float fpu44 = x86::Float(app->getMemory<float>(cpu.eax));
    // 004249f1  d84a08                 +fmul dword ptr [edx + 8]
    x86::Float fpu45 = cpu.fpu.mul(fpu44, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(8) /* 0x8 */)));
    // 004249f4  d9ca                   +fxch st(2)
    
    // 004249f6  d94004                 +fld dword ptr [eax + 4]
    x86::Float fpu46 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 004249f9  d84a0c                 +fmul dword ptr [edx + 0xc]
    x86::Float fpu47 = cpu.fpu.mul(fpu46, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(12) /* 0xc */)));
    // 004249fc  d94004                 +fld dword ptr [eax + 4]
    x86::Float fpu48 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 004249ff  d84a10                 +fmul dword ptr [edx + 0x10]
    x86::Float fpu49 = cpu.fpu.mul(fpu48, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(16) /* 0x10 */)));
    // 00424a02  d94004                 +fld dword ptr [eax + 4]
    x86::Float fpu50 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 00424a05  d84a14                 +fmul dword ptr [edx + 0x14]
    x86::Float fpu51 = cpu.fpu.mul(fpu50, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(20) /* 0x14 */)));
    // 00424a08  d9ca                   +fxch st(2)
    
    // 00424a0a  dec3                   +faddp st(3)
    x86::Float fpu52 = cpu.fpu.add(fpu41, fpu47);
    // 00424a0c  dec3                   +faddp st(3)
    x86::Float fpu53 = cpu.fpu.add(fpu43, fpu49);
    // 00424a0e  dec3                   +faddp st(3)
    x86::Float fpu54 = cpu.fpu.add(fpu45, fpu51);
    // 00424a10  d94008                 +fld dword ptr [eax + 8]
    x86::Float fpu55 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 00424a13  d84a18                 +fmul dword ptr [edx + 0x18]
    x86::Float fpu56 = cpu.fpu.mul(fpu55, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(24) /* 0x18 */)));
    // 00424a16  d94008                 +fld dword ptr [eax + 8]
    x86::Float fpu57 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 00424a19  d84a1c                 +fmul dword ptr [edx + 0x1c]
    x86::Float fpu58 = cpu.fpu.mul(fpu57, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(28) /* 0x1c */)));
    // 00424a1c  d94008                 +fld dword ptr [eax + 8]
    x86::Float fpu59 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 00424a1f  d84a20                 +fmul dword ptr [edx + 0x20]
    x86::Float fpu60 = cpu.fpu.mul(fpu59, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(32) /* 0x20 */)));
    // 00424a22  d9ca                   +fxch st(2)
    
    // 00424a24  dec3                   +faddp st(3)
    x86::Float fpu61 = cpu.fpu.add(fpu52, fpu56);
    // 00424a26  dec3                   +faddp st(3)
    x86::Float fpu62 = cpu.fpu.add(fpu53, fpu58);
    // 00424a28  dec3                   +faddp st(3)
    x86::Float fpu63 = cpu.fpu.add(fpu54, fpu60);
    // 00424a2a  8d400c                 -lea eax, [eax + 0xc]
    cpu.eax = x86::reg32(cpu.eax + x86::reg32(12) /* 0xc */);
    // 00424a2d  d91b                   +fstp dword ptr [ebx]
    app->getMemory<float>(cpu.ebx) = float(fpu61);
    // 00424a2f  d95b04                 +fstp dword ptr [ebx + 4]
    app->getMemory<float>(cpu.ebx + x86::reg32(4) /* 0x4 */) = float(fpu62);
    // 00424a32  d95b08                 +fstp dword ptr [ebx + 8]
    app->getMemory<float>(cpu.ebx + x86::reg32(8) /* 0x8 */) = float(fpu63);
    // 00424a35  8d5db8                 -lea ebx, [ebp - 0x48]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-72) /* -0x48 */);
    // 00424a38  8d55c4                 -lea edx, [ebp - 0x3c]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-60) /* -0x3c */);
    // 00424a3b  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    }
    // 00424a40  e9f2000000             -jmp 0x424b37
    goto L_0x00424b37;
L_0x00424a45:
    // 00424a45  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00424a48  8b4004                 -mov eax, dword ptr [eax + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 00424a4b  8d90c0000000           -lea edx, [eax + 0xc0]
    cpu.edx = x86::reg32(cpu.eax + x86::reg32(192) /* 0xc0 */);
    // 00424a51  8d5db8                 -lea ebx, [ebp - 0x48]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-72) /* -0x48 */);
    // 00424a54  8d45a0                 -lea eax, [ebp - 0x60]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-96) /* -0x60 */);
    // 00424a57  d900                   -fld dword ptr [eax]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu64 = x86::Float(app->getMemory<float>(cpu.eax));
    // 00424a59  d80a                   -fmul dword ptr [edx]
    x86::Float fpu65 = cpu.fpu.mul(fpu64, x86::Float(app->getMemory<float>(cpu.edx)));
    // 00424a5b  d900                   -fld dword ptr [eax]
    x86::Float fpu66 = x86::Float(app->getMemory<float>(cpu.eax));
    // 00424a5d  d84a04                 -fmul dword ptr [edx + 4]
    x86::Float fpu67 = cpu.fpu.mul(fpu66, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(4) /* 0x4 */)));
    // 00424a60  d900                   -fld dword ptr [eax]
    x86::Float fpu68 = x86::Float(app->getMemory<float>(cpu.eax));
    // 00424a62  d84a08                 -fmul dword ptr [edx + 8]
    x86::Float fpu69 = cpu.fpu.mul(fpu68, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(8) /* 0x8 */)));
    // 00424a65  d9ca                   -fxch st(2)
    
    // 00424a67  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu70 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 00424a6a  d84a0c                 -fmul dword ptr [edx + 0xc]
    x86::Float fpu71 = cpu.fpu.mul(fpu70, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(12) /* 0xc */)));
    // 00424a6d  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu72 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 00424a70  d84a10                 -fmul dword ptr [edx + 0x10]
    x86::Float fpu73 = cpu.fpu.mul(fpu72, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(16) /* 0x10 */)));
    // 00424a73  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu74 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 00424a76  d84a14                 -fmul dword ptr [edx + 0x14]
    x86::Float fpu75 = cpu.fpu.mul(fpu74, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(20) /* 0x14 */)));
    // 00424a79  d9ca                   -fxch st(2)
    
    // 00424a7b  dec3                   -faddp st(3)
    x86::Float fpu76 = cpu.fpu.add(fpu65, fpu71);
    // 00424a7d  dec3                   -faddp st(3)
    x86::Float fpu77 = cpu.fpu.add(fpu67, fpu73);
    // 00424a7f  dec3                   -faddp st(3)
    x86::Float fpu78 = cpu.fpu.add(fpu69, fpu75);
    // 00424a81  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu79 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 00424a84  d84a18                 -fmul dword ptr [edx + 0x18]
    x86::Float fpu80 = cpu.fpu.mul(fpu79, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(24) /* 0x18 */)));
    // 00424a87  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu81 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 00424a8a  d84a1c                 -fmul dword ptr [edx + 0x1c]
    x86::Float fpu82 = cpu.fpu.mul(fpu81, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(28) /* 0x1c */)));
    // 00424a8d  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu83 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 00424a90  d84a20                 -fmul dword ptr [edx + 0x20]
    x86::Float fpu84 = cpu.fpu.mul(fpu83, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(32) /* 0x20 */)));
    // 00424a93  d9ca                   -fxch st(2)
    
    // 00424a95  dec3                   -faddp st(3)
    x86::Float fpu85 = cpu.fpu.add(fpu76, fpu80);
    // 00424a97  dec3                   -faddp st(3)
    x86::Float fpu86 = cpu.fpu.add(fpu77, fpu82);
    // 00424a99  dec3                   -faddp st(3)
    x86::Float fpu87 = cpu.fpu.add(fpu78, fpu84);
    // 00424a9b  8d400c                 -lea eax, [eax + 0xc]
    cpu.eax = x86::reg32(cpu.eax + x86::reg32(12) /* 0xc */);
    // 00424a9e  d91b                   -fstp dword ptr [ebx]
    app->getMemory<float>(cpu.ebx) = float(fpu85);
    // 00424aa0  d95b04                 -fstp dword ptr [ebx + 4]
    app->getMemory<float>(cpu.ebx + x86::reg32(4) /* 0x4 */) = float(fpu86);
    // 00424aa3  d95b08                 -fstp dword ptr [ebx + 8]
    app->getMemory<float>(cpu.ebx + x86::reg32(8) /* 0x8 */) = float(fpu87);
    // 00424aa6  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00424aa9  83b80c01000001         +cmp dword ptr [eax + 0x10c], 1
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(268) /* 0x10c */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1 /*0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    }
    // 00424ab0  7515                   -jne 0x424ac7
    if (!cpu.flags.zf)
    {
        goto L_0x00424ac7;
    }
    // 00424ab2  8d7dac                 -lea edi, [ebp - 0x54]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(-84) /* -0x54 */);
    // 00424ab5  8d75b8                 -lea esi, [ebp - 0x48]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(-72) /* -0x48 */);
    // 00424ab8  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00424ab9  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00424aba  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00424abb  c7800c01000000000000   -mov dword ptr [eax + 0x10c], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(268) /* 0x10c */) = 0 /*0x0*/;
    // 00424ac5  eb21                   -jmp 0x424ae8
    goto L_0x00424ae8;
L_0x00424ac7:
    // 00424ac7  8b400c                 -mov eax, dword ptr [eax + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
    // 00424aca  833cc510105e0000       +cmp dword ptr [eax*8 + 0x5e1010], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(6164496) /* 0x5e1010 */ + cpu.eax * 8);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00424ad2  7408                   -je 0x424adc
    if (cpu.flags.zf)
    {
        goto L_0x00424adc;
    }
    // 00424ad4  8d7dac                 -lea edi, [ebp - 0x54]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(-84) /* -0x54 */);
    // 00424ad7  8d75b8                 -lea esi, [ebp - 0x48]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(-72) /* -0x48 */);
    // 00424ada  eb09                   -jmp 0x424ae5
    goto L_0x00424ae5;
L_0x00424adc:
    // 00424adc  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00424adf  8d7dac                 -lea edi, [ebp - 0x54]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(-84) /* -0x54 */);
    // 00424ae2  8d7020                 -lea esi, [eax + 0x20]
    cpu.esi = x86::reg32(cpu.eax + x86::reg32(32) /* 0x20 */);
L_0x00424ae5:
    // 00424ae5  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00424ae6  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00424ae7  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
L_0x00424ae8:
    // 00424ae8  8d4d94                 -lea ecx, [ebp - 0x6c]
    cpu.ecx = x86::reg32(cpu.ebp + x86::reg32(-108) /* -0x6c */);
    // 00424aeb  8d5dac                 -lea ebx, [ebp - 0x54]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-84) /* -0x54 */);
    // 00424aee  8d55b8                 -lea edx, [ebp - 0x48]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-72) /* -0x48 */);
    // 00424af1  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 00424af6  8b75fc                 -mov esi, dword ptr [ebp - 4]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00424af9  e802b50b00             -call 0x4e0000
    cpu.esp -= 4;
    sub_4e0000(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00424afe  8d4588                 -lea eax, [ebp - 0x78]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-120) /* -0x78 */);
    // 00424b01  8d5594                 -lea edx, [ebp - 0x6c]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-108) /* -0x6c */);
    // 00424b04  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00424b05  8d5d88                 -lea ebx, [ebp - 0x78]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-120) /* -0x78 */);
    // 00424b08  83c620                 -add esi, 0x20
    (cpu.esi) += x86::reg32(x86::sreg32(32 /*0x20*/));
    // 00424b0b  ff75e4                 -push dword ptr [ebp - 0x1c]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-28) /* -0x1c */);
    cpu.esp -= 4;
    // 00424b0e  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 00424b13  89f1                   -mov ecx, esi
    cpu.ecx = cpu.esi;
    // 00424b15  e836b50b00             -call 0x4e0050
    cpu.esp -= 4;
    sub_4e0050(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00424b1a  8d55ac                 -lea edx, [ebp - 0x54]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-84) /* -0x54 */);
    // 00424b1d  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 00424b22  e889b40b00             -call 0x4dffb0
    cpu.esp -= 4;
    sub_4dffb0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00424b27  8b4dfc                 -mov ecx, dword ptr [ebp - 4]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00424b2a  8d55c4                 -lea edx, [ebp - 0x3c]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-60) /* -0x3c */);
    // 00424b2d  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 00424b32  89f3                   -mov ebx, esi
    cpu.ebx = cpu.esi;
    // 00424b34  83c114                 -add ecx, 0x14
    (cpu.ecx) += x86::reg32(x86::sreg32(20 /*0x14*/));
L_0x00424b37:
    // 00424b37  e874b40b00             -call 0x4dffb0
    cpu.esp -= 4;
    sub_4dffb0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00424b3c:
    // 00424b3c  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00424b3e  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00424b3f  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00424b40  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00424b41  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00424b42  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00424b43  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00424b44  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 0x8b 0xdb */
void Application::sub_424b50(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00424b50  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00424b51  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00424b52  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00424b53  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00424b54  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00424b55  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00424b56  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00424b58  83ec2c                 -sub esp, 0x2c
    (cpu.esp) -= x86::reg32(x86::sreg32(44 /*0x2c*/));
    // 00424b5b  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 00424b5d  8b5004                 -mov edx, dword ptr [eax + 4]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 00424b60  89c7                   -mov edi, eax
    cpu.edi = cpu.eax;
    // 00424b62  8b8298000000           -mov eax, dword ptr [edx + 0x98]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(152) /* 0x98 */);
    // 00424b68  8945d4                 -mov dword ptr [ebp - 0x2c], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-44) /* -0x2c */) = cpu.eax;
    // 00424b6b  8b4604                 -mov eax, dword ptr [esi + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 00424b6e  8b809c000000           -mov eax, dword ptr [eax + 0x9c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(156) /* 0x9c */);
    // 00424b74  8945d8                 -mov dword ptr [ebp - 0x28], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-40) /* -0x28 */) = cpu.eax;
    // 00424b77  8b4604                 -mov eax, dword ptr [esi + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 00424b7a  8b80a0000000           -mov eax, dword ptr [eax + 0xa0]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(160) /* 0xa0 */);
    // 00424b80  8b0da8367d00           -mov ecx, dword ptr [0x7d36a8]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205992) /* 0x7d36a8 */);
    // 00424b86  8945dc                 -mov dword ptr [ebp - 0x24], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-36) /* -0x24 */) = cpu.eax;
    // 00424b89  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    // 00424b8b  740d                   -je 0x424b9a
    if (cpu.flags.zf)
    {
        goto L_0x00424b9a;
    }
    // 00424b8d  833d60d97c0000         +cmp dword ptr [0x7cd960], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(8182112) /* 0x7cd960 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00424b94  0f8433010000           -je 0x424ccd
    if (cpu.flags.zf)
    {
        goto L_0x00424ccd;
    }
L_0x00424b9a:
    // 00424b9a  833dec00560000         +cmp dword ptr [0x5600ec], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5636332) /* 0x5600ec */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00424ba1  0f8526010000           -jne 0x424ccd
    if (!cpu.flags.zf)
    {
        goto L_0x00424ccd;
    }
    // 00424ba7  8b4604                 -mov eax, dword ptr [esi + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 00424baa  81b80c010000f4fd343f   +cmp dword ptr [eax + 0x10c], 0x3f34fdf4
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(268) /* 0x10c */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1060437492 /*0x3f34fdf4*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00424bb4  7d3e                   -jge 0x424bf4
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00424bf4;
    }
    // 00424bb6  83be0c01000000         +cmp dword ptr [esi + 0x10c], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(268) /* 0x10c */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00424bbd  752b                   -jne 0x424bea
    if (!cpu.flags.zf)
    {
        goto L_0x00424bea;
    }
    // 00424bbf  83ba9809000000         +cmp dword ptr [edx + 0x998], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(2456) /* 0x998 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00424bc6  7e07                   -jle 0x424bcf
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00424bcf;
    }
    // 00424bc8  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 00424bcd  eb02                   -jmp 0x424bd1
    goto L_0x00424bd1;
L_0x00424bcf:
    // 00424bcf  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
L_0x00424bd1:
    // 00424bd1  8d55d4                 -lea edx, [ebp - 0x2c]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-44) /* -0x2c */);
    // 00424bd4  8d4e20                 -lea ecx, [esi + 0x20]
    cpu.ecx = x86::reg32(cpu.esi + x86::reg32(32) /* 0x20 */);
    // 00424bd7  8986fc000000           -mov dword ptr [esi + 0xfc], eax
    app->getMemory<x86::reg32>(cpu.esi + x86::reg32(252) /* 0xfc */) = cpu.eax;
    // 00424bdd  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 00424be2  8d5e14                 -lea ebx, [esi + 0x14]
    cpu.ebx = x86::reg32(cpu.esi + x86::reg32(20) /* 0x14 */);
    // 00424be5  e816b40b00             -call 0x4e0000
    cpu.esp -= 4;
    sub_4e0000(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00424bea:
    // 00424bea  c7860c01000040000000   -mov dword ptr [esi + 0x10c], 0x40
    app->getMemory<x86::reg32>(cpu.esi + x86::reg32(268) /* 0x10c */) = 64 /*0x40*/;
L_0x00424bf4:
    // 00424bf4  8b8724010000           -mov eax, dword ptr [edi + 0x124]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edi + x86::reg32(292) /* 0x124 */);
    // 00424bfa  8d5001                 -lea edx, [eax + 1]
    cpu.edx = x86::reg32(cpu.eax + x86::reg32(1) /* 0x1 */);
    // 00424bfd  899724010000           -mov dword ptr [edi + 0x124], edx
    app->getMemory<x86::reg32>(cpu.edi + x86::reg32(292) /* 0x124 */) = cpu.edx;
    // 00424c03  3b8720010000           +cmp eax, dword ptr [edi + 0x120]
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.edi + x86::reg32(288) /* 0x120 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00424c09  7e1c                   -jle 0x424c27
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00424c27;
    }
    // 00424c0b  d9871c010000           -fld dword ptr [edi + 0x11c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.edi + x86::reg32(284) /* 0x11c */));
    // 00424c11  d88728010000           -fadd dword ptr [edi + 0x128]
    x86::Float fpu2 = cpu.fpu.add(fpu1, x86::Float(app->getMemory<float>(cpu.edi + x86::reg32(296) /* 0x128 */)));
    // 00424c17  c7872401000000000000   -mov dword ptr [edi + 0x124], 0
    app->getMemory<x86::reg32>(cpu.edi + x86::reg32(292) /* 0x124 */) = 0 /*0x0*/;
    // 00424c21  d99f28010000           -fstp dword ptr [edi + 0x128]
    app->getMemory<float>(cpu.edi + x86::reg32(296) /* 0x128 */) = float(fpu2);
    }
L_0x00424c27:
    // 00424c27  8d5dfc                 -lea ebx, [ebp - 4]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00424c2a  8d55f8                 -lea edx, [ebp - 8]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 00424c2d  8d8728010000           -lea eax, [edi + 0x128]
    cpu.eax = x86::reg32(cpu.edi + x86::reg32(296) /* 0x128 */);
    // 00424c33  e8385d0c00             -call 0x4ea970
    cpu.esp -= 4;
    sub_4ea970(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00424c38  d98710010000           -fld dword ptr [edi + 0x110]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu3 = x86::Float(app->getMemory<float>(cpu.edi + x86::reg32(272) /* 0x110 */));
    // 00424c3e  d84dfc                 -fmul dword ptr [ebp - 4]
    x86::Float fpu4 = cpu.fpu.mul(fpu3, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 00424c41  d95dec                 -fstp dword ptr [ebp - 0x14]
    app->getMemory<float>(cpu.ebp + x86::reg32(-20) /* -0x14 */) = float(fpu4);
    // 00424c44  d98718010000           -fld dword ptr [edi + 0x118]
    x86::Float fpu5 = x86::Float(app->getMemory<float>(cpu.edi + x86::reg32(280) /* 0x118 */));
    // 00424c4a  d84df8                 -fmul dword ptr [ebp - 8]
    x86::Float fpu6 = cpu.fpu.mul(fpu5, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    // 00424c4d  d95df4                 -fstp dword ptr [ebp - 0xc]
    app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */) = float(fpu6);
    // 00424c50  d98714010000           -fld dword ptr [edi + 0x114]
    x86::Float fpu7 = x86::Float(app->getMemory<float>(cpu.edi + x86::reg32(276) /* 0x114 */));
    // 00424c56  d845f8                 -fadd dword ptr [ebp - 8]
    x86::Float fpu8 = cpu.fpu.add(fpu7, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    // 00424c59  d95df0                 -fstp dword ptr [ebp - 0x10]
    app->getMemory<float>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = float(fpu8);
    // 00424c5c  8b4604                 -mov eax, dword ptr [esi + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 00424c5f  8d90c0000000           -lea edx, [eax + 0xc0]
    cpu.edx = x86::reg32(cpu.eax + x86::reg32(192) /* 0xc0 */);
    // 00424c65  8d5de0                 -lea ebx, [ebp - 0x20]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-32) /* -0x20 */);
    // 00424c68  8d45ec                 -lea eax, [ebp - 0x14]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-20) /* -0x14 */);
    // 00424c6b  8d4e14                 -lea ecx, [esi + 0x14]
    cpu.ecx = x86::reg32(cpu.esi + x86::reg32(20) /* 0x14 */);
    // 00424c6e  d900                   -fld dword ptr [eax]
    x86::Float fpu9 = x86::Float(app->getMemory<float>(cpu.eax));
    // 00424c70  d80a                   -fmul dword ptr [edx]
    x86::Float fpu10 = cpu.fpu.mul(fpu9, x86::Float(app->getMemory<float>(cpu.edx)));
    // 00424c72  d900                   -fld dword ptr [eax]
    x86::Float fpu11 = x86::Float(app->getMemory<float>(cpu.eax));
    // 00424c74  d84a04                 -fmul dword ptr [edx + 4]
    x86::Float fpu12 = cpu.fpu.mul(fpu11, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(4) /* 0x4 */)));
    // 00424c77  d900                   -fld dword ptr [eax]
    x86::Float fpu13 = x86::Float(app->getMemory<float>(cpu.eax));
    // 00424c79  d84a08                 -fmul dword ptr [edx + 8]
    x86::Float fpu14 = cpu.fpu.mul(fpu13, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(8) /* 0x8 */)));
    // 00424c7c  d9ca                   -fxch st(2)
    
    // 00424c7e  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu15 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 00424c81  d84a0c                 -fmul dword ptr [edx + 0xc]
    x86::Float fpu16 = cpu.fpu.mul(fpu15, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(12) /* 0xc */)));
    // 00424c84  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu17 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 00424c87  d84a10                 -fmul dword ptr [edx + 0x10]
    x86::Float fpu18 = cpu.fpu.mul(fpu17, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(16) /* 0x10 */)));
    // 00424c8a  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu19 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 00424c8d  d84a14                 -fmul dword ptr [edx + 0x14]
    x86::Float fpu20 = cpu.fpu.mul(fpu19, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(20) /* 0x14 */)));
    // 00424c90  d9ca                   -fxch st(2)
    
    // 00424c92  dec3                   -faddp st(3)
    x86::Float fpu21 = cpu.fpu.add(fpu10, fpu16);
    // 00424c94  dec3                   -faddp st(3)
    x86::Float fpu22 = cpu.fpu.add(fpu12, fpu18);
    // 00424c96  dec3                   -faddp st(3)
    x86::Float fpu23 = cpu.fpu.add(fpu14, fpu20);
    // 00424c98  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu24 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 00424c9b  d84a18                 -fmul dword ptr [edx + 0x18]
    x86::Float fpu25 = cpu.fpu.mul(fpu24, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(24) /* 0x18 */)));
    // 00424c9e  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu26 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 00424ca1  d84a1c                 -fmul dword ptr [edx + 0x1c]
    x86::Float fpu27 = cpu.fpu.mul(fpu26, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(28) /* 0x1c */)));
    // 00424ca4  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu28 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 00424ca7  d84a20                 -fmul dword ptr [edx + 0x20]
    x86::Float fpu29 = cpu.fpu.mul(fpu28, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(32) /* 0x20 */)));
    // 00424caa  d9ca                   -fxch st(2)
    
    // 00424cac  dec3                   -faddp st(3)
    x86::Float fpu30 = cpu.fpu.add(fpu21, fpu25);
    // 00424cae  dec3                   -faddp st(3)
    x86::Float fpu31 = cpu.fpu.add(fpu22, fpu27);
    // 00424cb0  dec3                   -faddp st(3)
    x86::Float fpu32 = cpu.fpu.add(fpu23, fpu29);
    // 00424cb2  8d400c                 -lea eax, [eax + 0xc]
    cpu.eax = x86::reg32(cpu.eax + x86::reg32(12) /* 0xc */);
    // 00424cb5  d91b                   -fstp dword ptr [ebx]
    app->getMemory<float>(cpu.ebx) = float(fpu30);
    // 00424cb7  d95b04                 -fstp dword ptr [ebx + 4]
    app->getMemory<float>(cpu.ebx + x86::reg32(4) /* 0x4 */) = float(fpu31);
    // 00424cba  d95b08                 -fstp dword ptr [ebx + 8]
    app->getMemory<float>(cpu.ebx + x86::reg32(8) /* 0x8 */) = float(fpu32);
    // 00424cbd  8d5de0                 -lea ebx, [ebp - 0x20]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-32) /* -0x20 */);
    // 00424cc0  8d55d4                 -lea edx, [ebp - 0x2c]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-44) /* -0x2c */);
    // 00424cc3  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    }
    // 00424cc8  e8e3b20b00             -call 0x4dffb0
    cpu.esp -= 4;
    sub_4dffb0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00424ccd:
    // 00424ccd  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00424ccf  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00424cd0  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00424cd1  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00424cd2  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00424cd3  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00424cd4  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00424cd5  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x54 0x22 0x00 */
void Application::sub_424ce0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00424ce0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00424ce1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00424ce2  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00424ce3  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00424ce4  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00424ce5  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00424ce6  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00424ce8  83ec20                 -sub esp, 0x20
    (cpu.esp) -= x86::reg32(x86::sreg32(32 /*0x20*/));
    // 00424ceb  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 00424ced  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00424cef  a1a4c17900             -mov eax, dword ptr [0x79c1a4]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(7979428) /* 0x79c1a4 */);
    // 00424cf4  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 00424cf6  2b9624010000           -sub edx, dword ptr [esi + 0x124]
    (cpu.edx) -= x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.esi + x86::reg32(292) /* 0x124 */)));
    // 00424cfc  83fa02                 +cmp edx, 2
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(2 /*0x2*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00424cff  0f8c16010000           -jl 0x424e1b
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x00424e1b;
    }
    // 00424d05  8b3d1c305500           -mov edi, dword ptr [0x55301c]
    cpu.edi = app->getMemory<x86::reg32>(x86::reg32(5582876) /* 0x55301c */);
    // 00424d0b  898624010000           -mov dword ptr [esi + 0x124], eax
    app->getMemory<x86::reg32>(cpu.esi + x86::reg32(292) /* 0x124 */) = cpu.eax;
    // 00424d11  85ff                   +test edi, edi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edi & cpu.edi));
    // 00424d13  7409                   -je 0x424d1e
    if (cpu.flags.zf)
    {
        goto L_0x00424d1e;
    }
    // 00424d15  833d2030550000         +cmp dword ptr [0x553020], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5582880) /* 0x553020 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00424d1c  7451                   -je 0x424d6f
    if (cpu.flags.zf)
    {
        goto L_0x00424d6f;
    }
L_0x00424d1e:
    // 00424d1e  8b151c305500           -mov edx, dword ptr [0x55301c]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5582876) /* 0x55301c */);
    // 00424d24  c7811c01000000000000   -mov dword ptr [ecx + 0x11c], 0
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(284) /* 0x11c */) = 0 /*0x0*/;
    // 00424d2e  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 00424d30  7525                   -jne 0x424d57
    if (!cpu.flags.zf)
    {
        goto L_0x00424d57;
    }
    // 00424d32  833d20305500ff         +cmp dword ptr [0x553020], -1
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5582880) /* 0x553020 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(-1 /*-0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00424d39  750e                   -jne 0x424d49
    if (!cpu.flags.zf)
    {
        goto L_0x00424d49;
    }
    // 00424d3b  d98120010000           +fld dword ptr [ecx + 0x120]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(288) /* 0x120 */));
    // 00424d41  d805f06e5300           +fadd dword ptr [0x536ef0]
    x86::Float fpu2 = cpu.fpu.add(fpu1, x86::Float(app->getMemory<float>(x86::reg32(5467888) /* 0x536ef0 */)));
    cpu.fpu.count += 1;
    cpu.fpu.st(0) = fpu2;
    }
    // 00424d47  eb20                   -jmp 0x424d69
    goto L_0x00424d69;
L_0x00424d49:
    // 00424d49  d98120010000           +fld dword ptr [ecx + 0x120]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu3 = x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(288) /* 0x120 */));
    // 00424d4f  d805f46e5300           +fadd dword ptr [0x536ef4]
    x86::Float fpu4 = cpu.fpu.add(fpu3, x86::Float(app->getMemory<float>(x86::reg32(5467892) /* 0x536ef4 */)));
    cpu.fpu.count += 1;
    cpu.fpu.st(0) = fpu4;
    }
    // 00424d55  eb12                   -jmp 0x424d69
    goto L_0x00424d69;
L_0x00424d57:
    // 00424d57  db0520305500           -fild dword ptr [0x553020]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu5 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(5582880) /* 0x553020 */)));
    // 00424d5d  d80df86e5300           -fmul dword ptr [0x536ef8]
    x86::Float fpu6 = cpu.fpu.mul(fpu5, x86::Float(app->getMemory<float>(x86::reg32(5467896) /* 0x536ef8 */)));
    // 00424d63  d88120010000           -fadd dword ptr [ecx + 0x120]
    x86::Float fpu7 = cpu.fpu.add(fpu6, x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(288) /* 0x120 */)));
    cpu.fpu.count += 1;
    cpu.fpu.st(0) = fpu7;
    }
L_0x00424d69:
    // 00424d69  d99920010000           -fstp dword ptr [ecx + 0x120]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu8 = cpu.fpu.st(0);
    app->getMemory<float>(cpu.ecx + x86::reg32(288) /* 0x120 */) = float(fpu8);
    cpu.fpu.count -= 1;
    }
L_0x00424d6f:
    // 00424d6f  8d5dfc                 -lea ebx, [ebp - 4]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00424d72  8d55f8                 -lea edx, [ebp - 8]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 00424d75  8d8120010000           -lea eax, [ecx + 0x120]
    cpu.eax = x86::reg32(cpu.ecx + x86::reg32(288) /* 0x120 */);
    // 00424d7b  e8f05b0c00             -call 0x4ea970
    cpu.esp -= 4;
    sub_4ea970(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00424d80  d98110010000           -fld dword ptr [ecx + 0x110]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu9 = x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(272) /* 0x110 */));
    // 00424d86  d84dfc                 -fmul dword ptr [ebp - 4]
    x86::Float fpu10 = cpu.fpu.mul(fpu9, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 00424d89  d95de0                 -fstp dword ptr [ebp - 0x20]
    app->getMemory<float>(cpu.ebp + x86::reg32(-32) /* -0x20 */) = float(fpu10);
    // 00424d8c  d98118010000           -fld dword ptr [ecx + 0x118]
    x86::Float fpu11 = x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(280) /* 0x118 */));
    // 00424d92  d84df8                 -fmul dword ptr [ebp - 8]
    x86::Float fpu12 = cpu.fpu.mul(fpu11, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    // 00424d95  d95de8                 -fstp dword ptr [ebp - 0x18]
    app->getMemory<float>(cpu.ebp + x86::reg32(-24) /* -0x18 */) = float(fpu12);
    // 00424d98  d98114010000           -fld dword ptr [ecx + 0x114]
    x86::Float fpu13 = x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(276) /* 0x114 */));
    // 00424d9e  d845f8                 -fadd dword ptr [ebp - 8]
    x86::Float fpu14 = cpu.fpu.add(fpu13, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    // 00424da1  d95de4                 -fstp dword ptr [ebp - 0x1c]
    app->getMemory<float>(cpu.ebp + x86::reg32(-28) /* -0x1c */) = float(fpu14);
    // 00424da4  8b4604                 -mov eax, dword ptr [esi + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 00424da7  8d90c0000000           -lea edx, [eax + 0xc0]
    cpu.edx = x86::reg32(cpu.eax + x86::reg32(192) /* 0xc0 */);
    // 00424dad  8d5dec                 -lea ebx, [ebp - 0x14]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-20) /* -0x14 */);
    // 00424db0  8d45e0                 -lea eax, [ebp - 0x20]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-32) /* -0x20 */);
    // 00424db3  d900                   -fld dword ptr [eax]
    x86::Float fpu15 = x86::Float(app->getMemory<float>(cpu.eax));
    // 00424db5  d80a                   -fmul dword ptr [edx]
    x86::Float fpu16 = cpu.fpu.mul(fpu15, x86::Float(app->getMemory<float>(cpu.edx)));
    // 00424db7  d900                   -fld dword ptr [eax]
    x86::Float fpu17 = x86::Float(app->getMemory<float>(cpu.eax));
    // 00424db9  d84a04                 -fmul dword ptr [edx + 4]
    x86::Float fpu18 = cpu.fpu.mul(fpu17, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(4) /* 0x4 */)));
    // 00424dbc  d900                   -fld dword ptr [eax]
    x86::Float fpu19 = x86::Float(app->getMemory<float>(cpu.eax));
    // 00424dbe  d84a08                 -fmul dword ptr [edx + 8]
    x86::Float fpu20 = cpu.fpu.mul(fpu19, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(8) /* 0x8 */)));
    // 00424dc1  d9ca                   -fxch st(2)
    
    // 00424dc3  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu21 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 00424dc6  d84a0c                 -fmul dword ptr [edx + 0xc]
    x86::Float fpu22 = cpu.fpu.mul(fpu21, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(12) /* 0xc */)));
    // 00424dc9  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu23 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 00424dcc  d84a10                 -fmul dword ptr [edx + 0x10]
    x86::Float fpu24 = cpu.fpu.mul(fpu23, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(16) /* 0x10 */)));
    // 00424dcf  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu25 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 00424dd2  d84a14                 -fmul dword ptr [edx + 0x14]
    x86::Float fpu26 = cpu.fpu.mul(fpu25, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(20) /* 0x14 */)));
    // 00424dd5  d9ca                   -fxch st(2)
    
    // 00424dd7  dec3                   -faddp st(3)
    x86::Float fpu27 = cpu.fpu.add(fpu16, fpu22);
    // 00424dd9  dec3                   -faddp st(3)
    x86::Float fpu28 = cpu.fpu.add(fpu18, fpu24);
    // 00424ddb  dec3                   -faddp st(3)
    x86::Float fpu29 = cpu.fpu.add(fpu20, fpu26);
    // 00424ddd  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu30 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 00424de0  d84a18                 -fmul dword ptr [edx + 0x18]
    x86::Float fpu31 = cpu.fpu.mul(fpu30, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(24) /* 0x18 */)));
    // 00424de3  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu32 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 00424de6  d84a1c                 -fmul dword ptr [edx + 0x1c]
    x86::Float fpu33 = cpu.fpu.mul(fpu32, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(28) /* 0x1c */)));
    // 00424de9  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu34 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 00424dec  d84a20                 -fmul dword ptr [edx + 0x20]
    x86::Float fpu35 = cpu.fpu.mul(fpu34, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(32) /* 0x20 */)));
    // 00424def  d9ca                   -fxch st(2)
    
    // 00424df1  dec3                   -faddp st(3)
    x86::Float fpu36 = cpu.fpu.add(fpu27, fpu31);
    // 00424df3  dec3                   -faddp st(3)
    x86::Float fpu37 = cpu.fpu.add(fpu28, fpu33);
    // 00424df5  dec3                   -faddp st(3)
    x86::Float fpu38 = cpu.fpu.add(fpu29, fpu35);
    // 00424df7  8d400c                 -lea eax, [eax + 0xc]
    cpu.eax = x86::reg32(cpu.eax + x86::reg32(12) /* 0xc */);
    // 00424dfa  d91b                   -fstp dword ptr [ebx]
    app->getMemory<float>(cpu.ebx) = float(fpu36);
    // 00424dfc  d95b04                 -fstp dword ptr [ebx + 4]
    app->getMemory<float>(cpu.ebx + x86::reg32(4) /* 0x4 */) = float(fpu37);
    // 00424dff  d95b08                 -fstp dword ptr [ebx + 8]
    app->getMemory<float>(cpu.ebx + x86::reg32(8) /* 0x8 */) = float(fpu38);
    // 00424e02  8b4604                 -mov eax, dword ptr [esi + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 00424e05  8d4e14                 -lea ecx, [esi + 0x14]
    cpu.ecx = x86::reg32(cpu.esi + x86::reg32(20) /* 0x14 */);
    // 00424e08  8d9098000000           -lea edx, [eax + 0x98]
    cpu.edx = x86::reg32(cpu.eax + x86::reg32(152) /* 0x98 */);
    // 00424e0e  8d5dec                 -lea ebx, [ebp - 0x14]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-20) /* -0x14 */);
    // 00424e11  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    }
    // 00424e16  e895b10b00             -call 0x4dffb0
    cpu.esp -= 4;
    sub_4dffb0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00424e1b:
    // 00424e1b  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00424e1d  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00424e1e  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00424e1f  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00424e20  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00424e21  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00424e22  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00424e23  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 */
void Application::sub_424e30(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00424e30  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00424e31  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00424e32  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00424e33  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00424e34  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00424e35  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00424e36  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00424e38  83ec24                 -sub esp, 0x24
    (cpu.esp) -= x86::reg32(x86::sreg32(36 /*0x24*/));
    // 00424e3b  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 00424e3d  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00424e3f  8b4004                 -mov eax, dword ptr [eax + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 00424e42  db8024050000           -fild dword ptr [eax + 0x524]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.eax + x86::reg32(1316) /* 0x524 */)));
    // 00424e48  d80dfc6e5300           -fmul dword ptr [0x536efc]
    x86::Float fpu2 = cpu.fpu.mul(fpu1, x86::Float(app->getMemory<float>(x86::reg32(5467900) /* 0x536efc */)));
    // 00424e4e  d805006f5300           -fadd dword ptr [0x536f00]
    x86::Float fpu3 = cpu.fpu.add(fpu2, x86::Float(app->getMemory<float>(x86::reg32(5467904) /* 0x536f00 */)));
    // 00424e54  d99e20010000           -fstp dword ptr [esi + 0x120]
    app->getMemory<float>(cpu.esi + x86::reg32(288) /* 0x120 */) = float(fpu3);
    // 00424e5a  f6401c01               +test byte ptr [eax + 0x1c], 1
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(cpu.eax + x86::reg32(28) /* 0x1c */) & 1 /*0x1*/));
    }
    // 00424e5e  7409                   -je 0x424e69
    if (cpu.flags.zf)
    {
        goto L_0x00424e69;
    }
    // 00424e60  c745fc0000803f         -mov dword ptr [ebp - 4], 0x3f800000
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = 1065353216 /*0x3f800000*/;
    // 00424e67  eb07                   -jmp 0x424e70
    goto L_0x00424e70;
L_0x00424e69:
    // 00424e69  c745fc000080bf         -mov dword ptr [ebp - 4], 0xbf800000
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = 3212836864 /*0xbf800000*/;
L_0x00424e70:
    // 00424e70  8d5df8                 -lea ebx, [ebp - 8]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 00424e73  8d55f4                 -lea edx, [ebp - 0xc]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 00424e76  8d8120010000           -lea eax, [ecx + 0x120]
    cpu.eax = x86::reg32(cpu.ecx + x86::reg32(288) /* 0x120 */);
    // 00424e7c  e8ef5a0c00             -call 0x4ea970
    cpu.esp -= 4;
    sub_4ea970(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00424e81  d945f8                 -fld dword ptr [ebp - 8]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu4 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */));
    // 00424e84  d84dfc                 -fmul dword ptr [ebp - 4]
    x86::Float fpu5 = cpu.fpu.mul(fpu4, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 00424e87  d88910010000           -fmul dword ptr [ecx + 0x110]
    x86::Float fpu6 = cpu.fpu.mul(fpu5, x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(272) /* 0x110 */)));
    // 00424e8d  d95ddc                 -fstp dword ptr [ebp - 0x24]
    app->getMemory<float>(cpu.ebp + x86::reg32(-36) /* -0x24 */) = float(fpu6);
    // 00424e90  d98118010000           -fld dword ptr [ecx + 0x118]
    x86::Float fpu7 = x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(280) /* 0x118 */));
    // 00424e96  d84df4                 -fmul dword ptr [ebp - 0xc]
    x86::Float fpu8 = cpu.fpu.mul(fpu7, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */)));
    // 00424e99  d95de4                 -fstp dword ptr [ebp - 0x1c]
    app->getMemory<float>(cpu.ebp + x86::reg32(-28) /* -0x1c */) = float(fpu8);
    // 00424e9c  8b8114010000           -mov eax, dword ptr [ecx + 0x114]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(276) /* 0x114 */);
    // 00424ea2  8945e0                 -mov dword ptr [ebp - 0x20], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-32) /* -0x20 */) = cpu.eax;
    // 00424ea5  8b4604                 -mov eax, dword ptr [esi + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 00424ea8  8d90c0000000           -lea edx, [eax + 0xc0]
    cpu.edx = x86::reg32(cpu.eax + x86::reg32(192) /* 0xc0 */);
    // 00424eae  8d5de8                 -lea ebx, [ebp - 0x18]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-24) /* -0x18 */);
    // 00424eb1  8d45dc                 -lea eax, [ebp - 0x24]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-36) /* -0x24 */);
    // 00424eb4  d900                   -fld dword ptr [eax]
    x86::Float fpu9 = x86::Float(app->getMemory<float>(cpu.eax));
    // 00424eb6  d80a                   -fmul dword ptr [edx]
    x86::Float fpu10 = cpu.fpu.mul(fpu9, x86::Float(app->getMemory<float>(cpu.edx)));
    // 00424eb8  d900                   -fld dword ptr [eax]
    x86::Float fpu11 = x86::Float(app->getMemory<float>(cpu.eax));
    // 00424eba  d84a04                 -fmul dword ptr [edx + 4]
    x86::Float fpu12 = cpu.fpu.mul(fpu11, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(4) /* 0x4 */)));
    // 00424ebd  d900                   -fld dword ptr [eax]
    x86::Float fpu13 = x86::Float(app->getMemory<float>(cpu.eax));
    // 00424ebf  d84a08                 -fmul dword ptr [edx + 8]
    x86::Float fpu14 = cpu.fpu.mul(fpu13, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(8) /* 0x8 */)));
    // 00424ec2  d9ca                   -fxch st(2)
    
    // 00424ec4  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu15 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 00424ec7  d84a0c                 -fmul dword ptr [edx + 0xc]
    x86::Float fpu16 = cpu.fpu.mul(fpu15, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(12) /* 0xc */)));
    // 00424eca  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu17 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 00424ecd  d84a10                 -fmul dword ptr [edx + 0x10]
    x86::Float fpu18 = cpu.fpu.mul(fpu17, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(16) /* 0x10 */)));
    // 00424ed0  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu19 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 00424ed3  d84a14                 -fmul dword ptr [edx + 0x14]
    x86::Float fpu20 = cpu.fpu.mul(fpu19, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(20) /* 0x14 */)));
    // 00424ed6  d9ca                   -fxch st(2)
    
    // 00424ed8  dec3                   -faddp st(3)
    x86::Float fpu21 = cpu.fpu.add(fpu10, fpu16);
    // 00424eda  dec3                   -faddp st(3)
    x86::Float fpu22 = cpu.fpu.add(fpu12, fpu18);
    // 00424edc  dec3                   -faddp st(3)
    x86::Float fpu23 = cpu.fpu.add(fpu14, fpu20);
    // 00424ede  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu24 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 00424ee1  d84a18                 -fmul dword ptr [edx + 0x18]
    x86::Float fpu25 = cpu.fpu.mul(fpu24, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(24) /* 0x18 */)));
    // 00424ee4  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu26 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 00424ee7  d84a1c                 -fmul dword ptr [edx + 0x1c]
    x86::Float fpu27 = cpu.fpu.mul(fpu26, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(28) /* 0x1c */)));
    // 00424eea  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu28 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 00424eed  d84a20                 -fmul dword ptr [edx + 0x20]
    x86::Float fpu29 = cpu.fpu.mul(fpu28, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(32) /* 0x20 */)));
    // 00424ef0  d9ca                   -fxch st(2)
    
    // 00424ef2  dec3                   -faddp st(3)
    x86::Float fpu30 = cpu.fpu.add(fpu21, fpu25);
    // 00424ef4  dec3                   -faddp st(3)
    x86::Float fpu31 = cpu.fpu.add(fpu22, fpu27);
    // 00424ef6  dec3                   -faddp st(3)
    x86::Float fpu32 = cpu.fpu.add(fpu23, fpu29);
    // 00424ef8  8d400c                 -lea eax, [eax + 0xc]
    cpu.eax = x86::reg32(cpu.eax + x86::reg32(12) /* 0xc */);
    // 00424efb  d91b                   -fstp dword ptr [ebx]
    app->getMemory<float>(cpu.ebx) = float(fpu30);
    // 00424efd  d95b04                 -fstp dword ptr [ebx + 4]
    app->getMemory<float>(cpu.ebx + x86::reg32(4) /* 0x4 */) = float(fpu31);
    // 00424f00  d95b08                 -fstp dword ptr [ebx + 8]
    app->getMemory<float>(cpu.ebx + x86::reg32(8) /* 0x8 */) = float(fpu32);
    // 00424f03  8b4604                 -mov eax, dword ptr [esi + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 00424f06  8d4e14                 -lea ecx, [esi + 0x14]
    cpu.ecx = x86::reg32(cpu.esi + x86::reg32(20) /* 0x14 */);
    // 00424f09  8d9098000000           -lea edx, [eax + 0x98]
    cpu.edx = x86::reg32(cpu.eax + x86::reg32(152) /* 0x98 */);
    // 00424f0f  8d5de8                 -lea ebx, [ebp - 0x18]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-24) /* -0x18 */);
    // 00424f12  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    }
    // 00424f17  e894b00b00             -call 0x4dffb0
    cpu.esp -= 4;
    sub_4dffb0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00424f1c  8d7e20                 -lea edi, [esi + 0x20]
    cpu.edi = x86::reg32(cpu.esi + x86::reg32(32) /* 0x20 */);
    // 00424f1f  8d75e8                 -lea esi, [ebp - 0x18]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(-24) /* -0x18 */);
    // 00424f22  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00424f23  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00424f24  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00424f25  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00424f27  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00424f28  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00424f29  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00424f2a  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00424f2b  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00424f2c  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00424f2d  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8b 0xc0 */
void Application::sub_424f30(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00424f30  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00424f31  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00424f32  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00424f33  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00424f34  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00424f35  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00424f36  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00424f38  83ec24                 -sub esp, 0x24
    (cpu.esp) -= x86::reg32(x86::sreg32(36 /*0x24*/));
    // 00424f3b  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00424f3d  8d55dc                 -lea edx, [ebp - 0x24]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-36) /* -0x24 */);
    // 00424f40  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 00424f42  83c02c                 -add eax, 0x2c
    (cpu.eax) += x86::reg32(x86::sreg32(44 /*0x2c*/));
    // 00424f45  e876240900             -call 0x4b73c0
    cpu.esp -= 4;
    sub_4b73c0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00424f4a  83b92401000000         +cmp dword ptr [ecx + 0x124], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(292) /* 0x124 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00424f51  7457                   -je 0x424faa
    if (cpu.flags.zf)
    {
        goto L_0x00424faa;
    }
    // 00424f53  8b8128010000           -mov eax, dword ptr [ecx + 0x128]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(296) /* 0x128 */);
    // 00424f59  8b1d58da7c00           -mov ebx, dword ptr [0x7cda58]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(8182360) /* 0x7cda58 */);
    // 00424f5f  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 00424f62  83fb02                 +cmp ebx, 2
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
    // 00424f65  7514                   -jne 0x424f7b
    if (!cpu.flags.zf)
    {
        goto L_0x00424f7b;
    }
    // 00424f67  3b1d4cd97c00           +cmp ebx, dword ptr [0x7cd94c]
    {
        x86::reg32 tmp1 = cpu.ebx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(8182092) /* 0x7cd94c */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00424f6d  7e0c                   -jle 0x424f7b
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00424f7b;
    }
    // 00424f6f  c7812401000000000000   -mov dword ptr [ecx + 0x124], 0
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(292) /* 0x124 */) = 0 /*0x0*/;
    // 00424f79  eb46                   -jmp 0x424fc1
    goto L_0x00424fc1;
L_0x00424f7b:
    // 00424f7b  8d45ec                 -lea eax, [ebp - 0x14]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-20) /* -0x14 */);
    // 00424f7e  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00424f7f  8d55dc                 -lea edx, [ebp - 0x24]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-36) /* -0x24 */);
    // 00424f82  8d8614010000           -lea eax, [esi + 0x114]
    cpu.eax = x86::reg32(cpu.esi + x86::reg32(276) /* 0x114 */);
    // 00424f88  ff75fc                 -push dword ptr [ebp - 4]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    cpu.esp -= 4;
    // 00424f8b  e850220900             -call 0x4b71e0
    cpu.esp -= 4;
    sub_4b71e0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00424f90  8dbe14010000           -lea edi, [esi + 0x114]
    cpu.edi = x86::reg32(cpu.esi + x86::reg32(276) /* 0x114 */);
    // 00424f96  8d75ec                 -lea esi, [ebp - 0x14]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(-20) /* -0x14 */);
    // 00424f99  8d45ec                 -lea eax, [ebp - 0x14]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-20) /* -0x14 */);
    // 00424f9c  8d512c                 -lea edx, [ecx + 0x2c]
    cpu.edx = x86::reg32(cpu.ecx + x86::reg32(44) /* 0x2c */);
    // 00424f9f  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00424fa0  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00424fa1  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00424fa2  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00424fa3  e8e8250900             -call 0x4b7590
    cpu.esp -= 4;
    sub_4b7590(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00424fa8  eb17                   -jmp 0x424fc1
    goto L_0x00424fc1;
L_0x00424faa:
    // 00424faa  8d75dc                 -lea esi, [ebp - 0x24]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(-36) /* -0x24 */);
    // 00424fad  8db914010000           -lea edi, [ecx + 0x114]
    cpu.edi = x86::reg32(cpu.ecx + x86::reg32(276) /* 0x114 */);
    // 00424fb3  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00424fb4  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00424fb5  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00424fb6  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00424fb7  c7812401000001000000   -mov dword ptr [ecx + 0x124], 1
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(292) /* 0x124 */) = 1 /*0x1*/;
L_0x00424fc1:
    // 00424fc1  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00424fc3  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00424fc4  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00424fc5  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00424fc6  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00424fc7  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00424fc8  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00424fc9  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 */
void Application::sub_424fd0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00424fd0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00424fd1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00424fd2  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00424fd3  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00424fd4  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00424fd5  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00424fd7  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 00424fda  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 00424fdc  89d1                   -mov ecx, edx
    cpu.ecx = cpu.edx;
    // 00424fde  89d6                   -mov esi, edx
    cpu.esi = cpu.edx;
    // 00424fe0  8d7b14                 -lea edi, [ebx + 0x14]
    cpu.edi = x86::reg32(cpu.ebx + x86::reg32(20) /* 0x14 */);
    // 00424fe3  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00424fe4  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00424fe5  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00424fe6  8b4008                 -mov eax, dword ptr [eax + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 00424fe9  0598000000             +add eax, 0x98
    {
        x86::reg32& tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(152 /*0x98*/));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 00424fee  e8bd150700             -call 0x4965b0
    cpu.esp -= 4;
    sub_4965b0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00424ff3  d9ee                   +fldz 
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = 0.0;
    // 00424ff5  ded9                   +fcompp 
    x86::Float fpu2 = cpu.fpu.st(0);
    cpu.fpu.compare(fpu1, fpu2);
    // 00424ff7  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00424ff9  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    cpu.fpu.count -= 1;
    }
    // 00424ffa  7613                   -jbe 0x42500f
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x0042500f;
    }
    // 00424ffc  8b4308                 -mov eax, dword ptr [ebx + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(8) /* 0x8 */);
    // 00424fff  89ca                   -mov edx, ecx
    cpu.edx = cpu.ecx;
    // 00425001  0598000000             +add eax, 0x98
    {
        x86::reg32& tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(152 /*0x98*/));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 00425006  e8a5150700             -call 0x4965b0
    cpu.esp -= 4;
    sub_4965b0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042500b  d9e0                   +fchs 
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu3 = cpu.fpu.st(0);
    x86::Float fpu4 = -fpu3;
    cpu.fpu.st(0) = fpu4;
    }
    // 0042500d  eb0f                   -jmp 0x42501e
    goto L_0x0042501e;
L_0x0042500f:
    // 0042500f  8b4308                 -mov eax, dword ptr [ebx + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(8) /* 0x8 */);
    // 00425012  89ca                   -mov edx, ecx
    cpu.edx = cpu.ecx;
    // 00425014  0598000000             +add eax, 0x98
    {
        x86::reg32& tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(152 /*0x98*/));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 00425019  e892150700             -call 0x4965b0
    cpu.esp -= 4;
    sub_4965b0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x0042501e:
    // 0042501e  d95dfc                 +fstp dword ptr [ebp - 4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu5 = cpu.fpu.st(0);
    app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = float(fpu5);
    // 00425021  d945fc                 +fld dword ptr [ebp - 4]
    x86::Float fpu6 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */));
    // 00425024  d85d18                 +fcomp dword ptr [ebp + 0x18]
    cpu.fpu.compare(fpu6, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(24) /* 0x18 */)));
    // 00425027  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00425029  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    cpu.fpu.count -= 1;
    }
    // 0042502a  7614                   -jbe 0x425040
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x00425040;
    }
    // 0042502c  f74518ffffff7f         +test dword ptr [ebp + 0x18], 0x7fffffff
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(24) /* 0x18 */) & 2147483647 /*0x7fffffff*/));
    // 00425033  740b                   -je 0x425040
    if (cpu.flags.zf)
    {
        goto L_0x00425040;
    }
    // 00425035  d945fc                 +fld dword ptr [ebp - 4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu7 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */));
    // 00425038  d87518                 +fdiv dword ptr [ebp + 0x18]
    x86::Float fpu8 = cpu.fpu.div(fpu7, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(24) /* 0x18 */)));
    // 0042503b  d95b54                 +fstp dword ptr [ebx + 0x54]
    app->getMemory<float>(cpu.ebx + x86::reg32(84) /* 0x54 */) = float(fpu8);
    }
    // 0042503e  eb07                   -jmp 0x425047
    goto L_0x00425047;
L_0x00425040:
    // 00425040  c7435400000000         -mov dword ptr [ebx + 0x54], 0
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(84) /* 0x54 */) = 0 /*0x0*/;
L_0x00425047:
    // 00425047  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00425049  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042504a  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042504b  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042504c  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042504d  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042504e  c20400                 -ret 4
    cpu.esp += 4+4 /*0x4*/;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x8d 0x40 0x00 */
void Application::sub_425060(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00425060  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00425061  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00425062  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00425063  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00425064  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00425065  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00425066  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00425068  83ec1c                 -sub esp, 0x1c
    (cpu.esp) -= x86::reg32(x86::sreg32(28 /*0x1c*/));
    // 0042506b  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 0042506d  8b15a8367d00           -mov edx, dword ptr [0x7d36a8]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205992) /* 0x7d36a8 */);
    // 00425073  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 00425075  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 00425077  740d                   -je 0x425086
    if (cpu.flags.zf)
    {
        goto L_0x00425086;
    }
    // 00425079  833d60d97c0000         +cmp dword ptr [0x7cd960], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(8182112) /* 0x7cd960 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00425080  0f8460010000           -je 0x4251e6
    if (cpu.flags.zf)
    {
        goto L_0x004251e6;
    }
L_0x00425086:
    // 00425086  833dec00560000         +cmp dword ptr [0x5600ec], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5636332) /* 0x5600ec */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0042508d  0f8553010000           -jne 0x4251e6
    if (!cpu.flags.zf)
    {
        goto L_0x004251e6;
    }
    // 00425093  8b4104                 -mov eax, dword ptr [ecx + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(4) /* 0x4 */);
    // 00425096  8d780c                 -lea edi, [eax + 0xc]
    cpu.edi = x86::reg32(cpu.eax + x86::reg32(12) /* 0xc */);
    // 00425099  8b410c                 -mov eax, dword ptr [ecx + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(12) /* 0xc */);
    // 0042509c  e8cf8b0900             -call 0x4bdc70
    cpu.esp -= 4;
    sub_4bdc70(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004250a1  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004250a3  746a                   -je 0x42510f
    if (cpu.flags.zf)
    {
        goto L_0x0042510f;
    }
    // 004250a5  8b9184000000           -mov edx, dword ptr [ecx + 0x84]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(132) /* 0x84 */);
    // 004250ab  8d04d500000000         -lea eax, [edx*8]
    cpu.eax = x86::reg32(cpu.edx * 8);
    // 004250b2  01c2                   -add edx, eax
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.eax));
    // 004250b4  a148d95d00             -mov eax, dword ptr [0x5dd948]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(6150472) /* 0x5dd948 */);
    // 004250b9  c1e202                 -shl edx, 2
    cpu.edx <<= 2 /*0x2*/ % 32;
    // 004250bc  668b44020c             -mov ax, word ptr [edx + eax + 0xc]
    cpu.ax = app->getMemory<x86::reg16>(cpu.edx + x86::reg32(12) /* 0xc */ + cpu.eax * 1);
    // 004250c1  25ffff0000             -and eax, 0xffff
    cpu.eax &= x86::reg32(x86::sreg32(65535 /*0xffff*/));
    // 004250c6  e815efffff             -call 0x423fe0
    cpu.esp -= 4;
    sub_423fe0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004250cb  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004250cd  7525                   -jne 0x4250f4
    if (!cpu.flags.zf)
    {
        goto L_0x004250f4;
    }
    // 004250cf  8b5710                 -mov edx, dword ptr [edi + 0x10]
    cpu.edx = app->getMemory<x86::reg32>(cpu.edi + x86::reg32(16) /* 0x10 */);
    // 004250d2  8d04d500000000         -lea eax, [edx*8]
    cpu.eax = x86::reg32(cpu.edx * 8);
    // 004250d9  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 004250db  8b1548d95d00           -mov edx, dword ptr [0x5dd948]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(6150472) /* 0x5dd948 */);
    // 004250e1  668b44820c             -mov ax, word ptr [edx + eax*4 + 0xc]
    cpu.ax = app->getMemory<x86::reg16>(cpu.edx + x86::reg32(12) /* 0xc */ + cpu.eax * 4);
    // 004250e6  25ffff0000             -and eax, 0xffff
    cpu.eax &= x86::reg32(x86::sreg32(65535 /*0xffff*/));
    // 004250eb  e8f0eeffff             -call 0x423fe0
    cpu.esp -= 4;
    sub_423fe0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004250f0  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004250f2  741b                   -je 0x42510f
    if (cpu.flags.zf)
    {
        goto L_0x0042510f;
    }
L_0x004250f4:
    // 004250f4  8b4104                 -mov eax, dword ptr [ecx + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(4) /* 0x4 */);
    // 004250f7  83b83806000007         +cmp dword ptr [eax + 0x638], 7
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(1592) /* 0x638 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(7 /*0x7*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004250fe  7c07                   -jl 0x425107
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x00425107;
    }
    // 00425100  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 00425105  eb02                   -jmp 0x425109
    goto L_0x00425109;
L_0x00425107:
    // 00425107  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
L_0x00425109:
    // 00425109  898630010000           -mov dword ptr [esi + 0x130], eax
    app->getMemory<x86::reg32>(cpu.esi + x86::reg32(304) /* 0x130 */) = cpu.eax;
L_0x0042510f:
    // 0042510f  8d55e4                 -lea edx, [ebp - 0x1c]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-28) /* -0x1c */);
    // 00425112  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 00425114  8b9e30010000           -mov ebx, dword ptr [esi + 0x130]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(304) /* 0x130 */);
    // 0042511a  e8b1aeffff             -call 0x41ffd0
    cpu.esp -= 4;
    nfs3hp::trackdata::lanePosition(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042511f  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 00425121  8b45e4                 -mov eax, dword ptr [ebp - 0x1c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-28) /* -0x1c */);
    // 00425124  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 00425127  db45fc                 +fild dword ptr [ebp - 4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 0042512a  8b45e8                 -mov eax, dword ptr [ebp - 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-24) /* -0x18 */);
    // 0042512d  dd05046f5300           +fld qword ptr [0x536f04]
    x86::Float fpu2 = x86::Float(app->getMemory<double>(x86::reg32(5467908) /* 0x536f04 */));
    // 00425133  d9c9                   +fxch st(1)
    
    // 00425135  d8c9                   +fmul st(1)
    x86::Float fpu3 = cpu.fpu.mul(fpu1, x86::Float(fpu2));
    // 00425137  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 0042513a  8b45ec                 -mov eax, dword ptr [ebp - 0x14]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */);
    // 0042513d  db45fc                 +fild dword ptr [ebp - 4]
    x86::Float fpu4 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 00425140  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 00425143  d8ca                   +fmul st(2)
    x86::Float fpu5 = cpu.fpu.mul(fpu4, x86::Float(fpu2));
    // 00425145  db45fc                 +fild dword ptr [ebp - 4]
    x86::Float fpu6 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 00425148  decb                   +fmulp st(3)
    x86::Float fpu7 = cpu.fpu.mul(fpu2, fpu6);
    // 0042514a  d9c9                   +fxch st(1)
    
    // 0042514c  d95df0                 +fstp dword ptr [ebp - 0x10]
    app->getMemory<float>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = float(fpu3);
    // 0042514f  d95df4                 +fstp dword ptr [ebp - 0xc]
    app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */) = float(fpu5);
    // 00425152  d95df8                 +fstp dword ptr [ebp - 8]
    app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = float(fpu7);
    // 00425155  d94114                 +fld dword ptr [ecx + 0x14]
    x86::Float fpu8 = x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(20) /* 0x14 */));
    // 00425158  d85df0                 +fcomp dword ptr [ebp - 0x10]
    cpu.fpu.compare(fpu8, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-16) /* -0x10 */)));
    // 0042515b  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 0042515d  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 0042515e  7516                   -jne 0x425176
    if (!cpu.flags.zf)
    {
        goto L_0x00425176;
    }
    // 00425160  d94118                 +fld dword ptr [ecx + 0x18]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu9 = x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(24) /* 0x18 */));
    // 00425163  d85df4                 +fcomp dword ptr [ebp - 0xc]
    cpu.fpu.compare(fpu9, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */)));
    // 00425166  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00425168  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 00425169  750b                   -jne 0x425176
    if (!cpu.flags.zf)
    {
        goto L_0x00425176;
    }
    // 0042516b  d9411c                 +fld dword ptr [ecx + 0x1c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu10 = x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(28) /* 0x1c */));
    // 0042516e  d85df8                 +fcomp dword ptr [ebp - 8]
    cpu.fpu.compare(fpu10, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    // 00425171  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00425173  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 00425174  7449                   -je 0x4251bf
    if (cpu.flags.zf)
    {
        goto L_0x004251bf;
    }
L_0x00425176:
    // 00425176  8b3d24305500           -mov edi, dword ptr [0x553024]
    cpu.edi = app->getMemory<x86::reg32>(x86::reg32(5582884) /* 0x553024 */);
    // 0042517c  47                     -inc edi
    (cpu.edi)++;
    // 0042517d  c7862401000000000000   -mov dword ptr [esi + 0x124], 0
    app->getMemory<x86::reg32>(cpu.esi + x86::reg32(292) /* 0x124 */) = 0 /*0x0*/;
    // 00425187  893d24305500           -mov dword ptr [0x553024], edi
    app->getMemory<x86::reg32>(x86::reg32(5582884) /* 0x553024 */) = cpu.edi;
    // 0042518d  83ff03                 +cmp edi, 3
    {
        x86::reg32 tmp1 = cpu.edi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(3 /*0x3*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00425190  7c1b                   -jl 0x4251ad
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004251ad;
    }
    // 00425192  31d2                   +xor edx, edx
    cpu.clear_co();
    cpu.set_szp((cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx))));
    // 00425194  c7862c01000000000000   -mov dword ptr [esi + 0x12c], 0
    app->getMemory<x86::reg32>(cpu.esi + x86::reg32(300) /* 0x12c */) = 0 /*0x0*/;
    // 0042519e  891524305500           -mov dword ptr [0x553024], edx
    app->getMemory<x86::reg32>(x86::reg32(5582884) /* 0x553024 */) = cpu.edx;
    // 004251a4  c7415400000000         -mov dword ptr [ecx + 0x54], 0
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(84) /* 0x54 */) = 0 /*0x0*/;
    // 004251ab  eb0a                   -jmp 0x4251b7
    goto L_0x004251b7;
L_0x004251ad:
    // 004251ad  c7862c01000001000000   -mov dword ptr [esi + 0x12c], 1
    app->getMemory<x86::reg32>(cpu.esi + x86::reg32(300) /* 0x12c */) = 1 /*0x1*/;
L_0x004251b7:
    // 004251b7  8b410c                 -mov eax, dword ptr [ecx + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(12) /* 0xc */);
    // 004251ba  e8118a0900             -call 0x4bdbd0
    cpu.esp -= 4;
    sub_4bdbd0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x004251bf:
    // 004251bf  8d55f0                 -lea edx, [ebp - 0x10]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 004251c2  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004251c4  ffb610010000           -push dword ptr [esi + 0x110]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(272) /* 0x110 */);
    cpu.esp -= 4;
    // 004251ca  e801feffff             -call 0x424fd0
    cpu.esp -= 4;
    sub_424fd0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004251cf  8d5114                 -lea edx, [ecx + 0x14]
    cpu.edx = x86::reg32(cpu.ecx + x86::reg32(20) /* 0x14 */);
    // 004251d2  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004251d4  8999ec000000           -mov dword ptr [ecx + 0xec], ebx
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(236) /* 0xec */) = cpu.ebx;
    // 004251da  e8b1d0ffff             -call 0x422290
    cpu.esp -= 4;
    sub_422290(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004251df  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004251e1  e84afdffff             -call 0x424f30
    cpu.esp -= 4;
    sub_424f30(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x004251e6:
    // 004251e6  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004251e8  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004251e9  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004251ea  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004251eb  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004251ec  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004251ed  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004251ee  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x90 */
void Application::sub_4251f0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004251f0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004251f1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004251f2  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004251f3  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004251f4  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004251f5  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004251f6  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004251f8  83ec30                 -sub esp, 0x30
    (cpu.esp) -= x86::reg32(x86::sreg32(48 /*0x30*/));
    // 004251fb  8945f4                 -mov dword ptr [ebp - 0xc], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.eax;
    // 004251fe  8b400c                 -mov eax, dword ptr [eax + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
    // 00425201  e88aebffff             -call 0x423d90
    cpu.esp -= 4;
    sub_423d90(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00425206  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 00425208  83f8ff                 +cmp eax, -1
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
    // 0042520b  7525                   -jne 0x425232
    if (!cpu.flags.zf)
    {
        goto L_0x00425232;
    }
    // 0042520d  8b45f4                 -mov eax, dword ptr [ebp - 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 00425210  ba08000000             -mov edx, 8
    cpu.edx = 8 /*0x8*/;
    // 00425215  8b400c                 -mov eax, dword ptr [eax + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
    // 00425218  e893e6ffff             -call 0x4238b0
    cpu.esp -= 4;
    sub_4238b0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042521d  8b45f4                 -mov eax, dword ptr [ebp - 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 00425220  8b500c                 -mov edx, dword ptr [eax + 0xc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
    // 00425223  b808000000             -mov eax, 8
    cpu.eax = 8 /*0x8*/;
    // 00425228  e823120000             -call 0x426450
    cpu.esp -= 4;
    sub_426450(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042522d  e986010000             -jmp 0x4253b8
    goto L_0x004253b8;
L_0x00425232:
    // 00425232  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 00425235  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 00425237  c1e003                 -shl eax, 3
    cpu.eax <<= 3 /*0x3*/ % 32;
    // 0042523a  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 0042523c  8b15502e5500           -mov edx, dword ptr [0x552e50]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5582416) /* 0x552e50 */);
    // 00425242  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 00425244  8b4df4                 -mov ecx, dword ptr [ebp - 0xc]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 00425247  8b5018                 -mov edx, dword ptr [eax + 0x18]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */);
    // 0042524a  8991ec000000           -mov dword ptr [ecx + 0xec], edx
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(236) /* 0xec */) = cpu.edx;
    // 00425250  dd050c6f5300           -fld qword ptr [0x536f0c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<double>(x86::reg32(5467916) /* 0x536f0c */));
    // 00425256  db00                   -fild dword ptr [eax]
    x86::Float fpu2 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.eax)));
    // 00425258  d8c9                   -fmul st(1)
    x86::Float fpu3 = cpu.fpu.mul(fpu2, x86::Float(fpu1));
    // 0042525a  d95914                 -fstp dword ptr [ecx + 0x14]
    app->getMemory<float>(cpu.ecx + x86::reg32(20) /* 0x14 */) = float(fpu3);
    // 0042525d  db4004                 -fild dword ptr [eax + 4]
    x86::Float fpu4 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */)));
    // 00425260  d8c9                   -fmul st(1)
    x86::Float fpu5 = cpu.fpu.mul(fpu4, x86::Float(fpu1));
    // 00425262  d95918                 -fstp dword ptr [ecx + 0x18]
    app->getMemory<float>(cpu.ecx + x86::reg32(24) /* 0x18 */) = float(fpu5);
    // 00425265  db4008                 -fild dword ptr [eax + 8]
    x86::Float fpu6 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */)));
    // 00425268  dec9                   -fmulp st(1)
    x86::Float fpu7 = cpu.fpu.mul(fpu1, fpu6);
    // 0042526a  d9591c                 -fstp dword ptr [ecx + 0x1c]
    app->getMemory<float>(cpu.ecx + x86::reg32(28) /* 0x1c */) = float(fpu7);
    // 0042526d  8a5016                 -mov dl, byte ptr [eax + 0x16]
    cpu.dl = app->getMemory<x86::reg8>(cpu.eax + x86::reg32(22) /* 0x16 */);
    // 00425270  f6c201                 +test dl, 1
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.dl & 1 /*0x1*/));
    }
    // 00425273  742d                   -je 0x4252a2
    if (cpu.flags.zf)
    {
        goto L_0x004252a2;
    }
    // 00425275  be98445600             -mov esi, 0x564498
    cpu.esi = 5653656 /*0x564498*/;
    // 0042527a  8b4104                 -mov eax, dword ptr [ecx + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(4) /* 0x4 */);
    // 0042527d  89ca                   -mov edx, ecx
    cpu.edx = cpu.ecx;
    // 0042527f  894108                 -mov dword ptr [ecx + 8], eax
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(8) /* 0x8 */) = cpu.eax;
    // 00425282  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 00425284  c7810801000001000000   -mov dword ptr [ecx + 0x108], 1
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(264) /* 0x108 */) = 1 /*0x1*/;
    // 0042528e  b909000000             -mov ecx, 9
    cpu.ecx = 9 /*0x9*/;
    // 00425293  8d782c                 -lea edi, [eax + 0x2c]
    cpu.edi = x86::reg32(cpu.eax + x86::reg32(44) /* 0x2c */);
    // 00425296  83c214                 +add edx, 0x14
    {
        x86::reg32& tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(20 /*0x14*/));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 00425299  f3a5                   -rep movsd dword ptr es:[edi], dword ptr [esi]
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
    // 0042529b  e8f0cfffff             -call 0x422290
    cpu.esp -= 4;
    sub_422290(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004252a0  eb74                   -jmp 0x425316
    goto L_0x00425316;
L_0x004252a2:
    // 004252a2  c7810801000000000000   -mov dword ptr [ecx + 0x108], 0
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(264) /* 0x108 */) = 0 /*0x0*/;
    // 004252ac  8b500a                 -mov edx, dword ptr [eax + 0xa]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(10) /* 0xa */);
    // 004252af  c1fa10                 -sar edx, 0x10
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (16 /*0x10*/ % 32));
    // 004252b2  c1e202                 -shl edx, 2
    cpu.edx <<= 2 /*0x2*/ % 32;
    // 004252b5  8955f8                 -mov dword ptr [ebp - 8], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.edx;
    // 004252b8  dd050c6f5300           -fld qword ptr [0x536f0c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu8 = x86::Float(app->getMemory<double>(x86::reg32(5467916) /* 0x536f0c */));
    // 004252be  db45f8                 -fild dword ptr [ebp - 8]
    x86::Float fpu9 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    // 004252c1  d8c9                   -fmul st(1)
    x86::Float fpu10 = cpu.fpu.mul(fpu9, x86::Float(fpu8));
    // 004252c3  d95dd0                 -fstp dword ptr [ebp - 0x30]
    app->getMemory<float>(cpu.ebp + x86::reg32(-48) /* -0x30 */) = float(fpu10);
    // 004252c6  8b500c                 -mov edx, dword ptr [eax + 0xc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
    // 004252c9  c1fa10                 -sar edx, 0x10
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (16 /*0x10*/ % 32));
    // 004252cc  c1e202                 -shl edx, 2
    cpu.edx <<= 2 /*0x2*/ % 32;
    // 004252cf  8955f8                 -mov dword ptr [ebp - 8], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.edx;
    // 004252d2  db45f8                 -fild dword ptr [ebp - 8]
    x86::Float fpu11 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    // 004252d5  d8c9                   -fmul st(1)
    x86::Float fpu12 = cpu.fpu.mul(fpu11, x86::Float(fpu8));
    // 004252d7  d95dd4                 -fstp dword ptr [ebp - 0x2c]
    app->getMemory<float>(cpu.ebp + x86::reg32(-44) /* -0x2c */) = float(fpu12);
    // 004252da  8b500e                 -mov edx, dword ptr [eax + 0xe]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(14) /* 0xe */);
    // 004252dd  c1fa10                 -sar edx, 0x10
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (16 /*0x10*/ % 32));
    // 004252e0  c1e202                 -shl edx, 2
    cpu.edx <<= 2 /*0x2*/ % 32;
    // 004252e3  8955f8                 -mov dword ptr [ebp - 8], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.edx;
    // 004252e6  db45f8                 -fild dword ptr [ebp - 8]
    x86::Float fpu13 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    // 004252e9  d8c9                   -fmul st(1)
    x86::Float fpu14 = cpu.fpu.mul(fpu13, x86::Float(fpu8));
    // 004252eb  d95dd8                 -fstp dword ptr [ebp - 0x28]
    app->getMemory<float>(cpu.ebp + x86::reg32(-40) /* -0x28 */) = float(fpu14);
    // 004252ee  8b4010                 -mov eax, dword ptr [eax + 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(16) /* 0x10 */);
    // 004252f1  c1f810                 -sar eax, 0x10
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (16 /*0x10*/ % 32));
    // 004252f4  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 004252f7  8945f8                 -mov dword ptr [ebp - 8], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.eax;
    // 004252fa  83c12c                 -add ecx, 0x2c
    (cpu.ecx) += x86::reg32(x86::sreg32(44 /*0x2c*/));
    // 004252fd  db45f8                 -fild dword ptr [ebp - 8]
    x86::Float fpu15 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    // 00425300  dec9                   -fmulp st(1)
    x86::Float fpu16 = cpu.fpu.mul(fpu8, fpu15);
    // 00425302  89ca                   -mov edx, ecx
    cpu.edx = cpu.ecx;
    // 00425304  8d45d0                 -lea eax, [ebp - 0x30]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-48) /* -0x30 */);
    // 00425307  d95ddc                 -fstp dword ptr [ebp - 0x24]
    app->getMemory<float>(cpu.ebp + x86::reg32(-36) /* -0x24 */) = float(fpu16);
    }
    // 0042530a  e881220900             -call 0x4b7590
    cpu.esp -= 4;
    sub_4b7590(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042530f  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00425311  e8aa260900             -call 0x4b79c0
    cpu.esp -= 4;
    sub_4b79c0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00425316:
    // 00425316  8d049d00000000         -lea eax, [ebx*4]
    cpu.eax = x86::reg32(cpu.ebx * 4);
    // 0042531d  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 0042531f  c1e003                 -shl eax, 3
    cpu.eax <<= 3 /*0x3*/ % 32;
    // 00425322  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 00425324  8b15502e5500           -mov edx, dword ptr [0x552e50]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5582416) /* 0x552e50 */);
    // 0042532a  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 0042532c  f6401602               +test byte ptr [eax + 0x16], 2
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(cpu.eax + x86::reg32(22) /* 0x16 */) & 2 /*0x2*/));
    // 00425330  741c                   -je 0x42534e
    if (cpu.flags.zf)
    {
        goto L_0x0042534e;
    }
    // 00425332  8b55f4                 -mov edx, dword ptr [ebp - 0xc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 00425335  8b45f4                 -mov eax, dword ptr [ebp - 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 00425338  83c214                 -add edx, 0x14
    (cpu.edx) += x86::reg32(x86::sreg32(20 /*0x14*/));
    // 0042533b  680000c040             -push 0x40c00000
    app->getMemory<x86::reg32>(cpu.esp-4) = 1086324736 /*0x40c00000*/;
    cpu.esp -= 4;
    // 00425340  e88bfcffff             -call 0x424fd0
    cpu.esp -= 4;
    sub_424fd0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00425345  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00425347  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00425348  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00425349  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042534a  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042534b  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042534c  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042534d  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x0042534e:
    // 0042534e  8b5012                 -mov edx, dword ptr [eax + 0x12]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(18) /* 0x12 */);
    // 00425351  c1fa10                 -sar edx, 0x10
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (16 /*0x10*/ % 32));
    // 00425354  c1e209                 -shl edx, 9
    cpu.edx <<= 9 /*0x9*/ % 32;
    // 00425357  b968010000             -mov ecx, 0x168
    cpu.ecx = 360 /*0x168*/;
    // 0042535c  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 0042535e  c1fa1f                 -sar edx, 0x1f
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (31 /*0x1f*/ % 32));
    // 00425361  f7f9                   +idiv ecx
    {
        x86::sreg64 tmp = x86::sreg64(cpu.edx_eax);
        x86::sreg32 d = x86::sreg32(cpu.ecx);
        cpu.edx_eax = x86::reg64(tmp / d);
        cpu.edx = x86::reg32(tmp % d);
    }
    // 00425363  8d5de4                 -lea ebx, [ebp - 0x1c]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-28) /* -0x1c */);
    // 00425366  8d55e0                 -lea edx, [ebp - 0x20]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-32) /* -0x20 */);
    // 00425369  e8f2580c00             -call 0x4eac60
    cpu.esp -= 4;
    sub_4eac60(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042536e  8b45e4                 -mov eax, dword ptr [ebp - 0x1c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-28) /* -0x1c */);
    // 00425371  8945f8                 -mov dword ptr [ebp - 8], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.eax;
    // 00425374  8b45e0                 -mov eax, dword ptr [ebp - 0x20]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-32) /* -0x20 */);
    // 00425377  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 0042537a  db45f8                 +fild dword ptr [ebp - 8]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu17 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    // 0042537d  db45fc                 +fild dword ptr [ebp - 4]
    x86::Float fpu18 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 00425380  def9                   +fdivp st(1)
    x86::Float fpu19 = cpu.fpu.div(fpu17, fpu18);
    // 00425382  d955f0                 +fst dword ptr [ebp - 0x10]
    app->getMemory<float>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = float(fpu19);
    // 00425385  d81d146f5300           +fcomp dword ptr [0x536f14]
    cpu.fpu.compare(fpu19, x86::Float(app->getMemory<float>(x86::reg32(5467924) /* 0x536f14 */)));
    // 0042538b  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 0042538d  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 0042538e  7309                   -jae 0x425399
    if (!cpu.flags.cf)
    {
        goto L_0x00425399;
    }
    // 00425390  c745ec3333333f         -mov dword ptr [ebp - 0x14], 0x3f333333
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */) = 1060320051 /*0x3f333333*/;
    // 00425397  eb16                   -jmp 0x4253af
    goto L_0x004253af;
L_0x00425399:
    // 00425399  d945f0                 -fld dword ptr [ebp - 0x10]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu20 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-16) /* -0x10 */));
    // 0042539c  d9c0                   -fld st(0)
    x86::Float fpu21 = x86::Float(fpu20);
    // 0042539e  ded9                   -fcompp 
    cpu.fpu.compare(fpu21, fpu20);
    // 004253a0  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 004253a2  9e                     -sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    // 004253a3  8b45f0                 -mov eax, dword ptr [ebp - 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 004253a6  8945e8                 -mov dword ptr [ebp - 0x18], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-24) /* -0x18 */) = cpu.eax;
    // 004253a9  8b45e8                 -mov eax, dword ptr [ebp - 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-24) /* -0x18 */);
    // 004253ac  8945ec                 -mov dword ptr [ebp - 0x14], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */) = cpu.eax;
    }
L_0x004253af:
    // 004253af  8b55f4                 -mov edx, dword ptr [ebp - 0xc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 004253b2  8b45ec                 -mov eax, dword ptr [ebp - 0x14]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */);
    // 004253b5  894254                 -mov dword ptr [edx + 0x54], eax
    app->getMemory<x86::reg32>(cpu.edx + x86::reg32(84) /* 0x54 */) = cpu.eax;
L_0x004253b8:
    // 004253b8  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004253ba  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004253bb  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004253bc  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004253bd  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004253be  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004253bf  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004253c0  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x8d 0x40 0x00 */
void Application::sub_4253d0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004253d0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004253d1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004253d2  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004253d3  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004253d4  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004253d5  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004253d6  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004253d8  81ec84000000           -sub esp, 0x84
    (cpu.esp) -= x86::reg32(x86::sreg32(132 /*0x84*/));
    // 004253de  81ed82000000           -sub ebp, 0x82
    (cpu.ebp) -= x86::reg32(x86::sreg32(130 /*0x82*/));
    // 004253e4  89457e                 -mov dword ptr [ebp + 0x7e], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */) = cpu.eax;
    // 004253e7  8b9010010000           -mov edx, dword ptr [eax + 0x110]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(272) /* 0x110 */);
    // 004253ed  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 004253ef  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 004253f1  7553                   -jne 0x425446
    if (!cpu.flags.zf)
    {
        goto L_0x00425446;
    }
    // 004253f3  8b8014010000           -mov eax, dword ptr [eax + 0x114]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(276) /* 0x114 */);
    // 004253f9  89ca                   -mov edx, ecx
    cpu.edx = cpu.ecx;
    // 004253fb  e8b09ffeff             -call 0x40f3b0
    cpu.esp -= 4;
    sub_40f3b0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00425400  898218010000           -mov dword ptr [edx + 0x118], eax
    app->getMemory<x86::reg32>(cpu.edx + x86::reg32(280) /* 0x118 */) = cpu.eax;
    // 00425406  83f8ff                 +cmp eax, -1
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
    // 00425409  7531                   -jne 0x42543c
    if (!cpu.flags.zf)
    {
        goto L_0x0042543c;
    }
    // 0042540b  8b420c                 -mov eax, dword ptr [edx + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(12) /* 0xc */);
    // 0042540e  8b0485b8bb6f00         -mov eax, dword ptr [eax*4 + 0x6fbbb8]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(7322552) /* 0x6fbbb8 */ + cpu.eax * 4);
    // 00425415  e896e6ffff             -call 0x423ab0
    cpu.esp -= 4;
    sub_423ab0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042541a  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0042541c  740c                   -je 0x42542a
    if (cpu.flags.zf)
    {
        goto L_0x0042542a;
    }
    // 0042541e  8b520c                 -mov edx, dword ptr [edx + 0xc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(12) /* 0xc */);
    // 00425421  8b0495b8bb6f00         -mov eax, dword ptr [edx*4 + 0x6fbbb8]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(7322552) /* 0x6fbbb8 */ + cpu.edx * 4);
    // 00425428  eb08                   -jmp 0x425432
    goto L_0x00425432;
L_0x0042542a:
    // 0042542a  a154105e00             -mov eax, dword ptr [0x5e1054]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(6164564) /* 0x5e1054 */);
    // 0042542f  8b520c                 -mov edx, dword ptr [edx + 0xc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(12) /* 0xc */);
L_0x00425432:
    // 00425432  e8d9d1ffff             -call 0x422610
    cpu.esp -= 4;
    sub_422610(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00425437  e9f6010000             -jmp 0x425632
    goto L_0x00425632;
L_0x0042543c:
    // 0042543c  c7821001000001000000   -mov dword ptr [edx + 0x110], 1
    app->getMemory<x86::reg32>(cpu.edx + x86::reg32(272) /* 0x110 */) = 1 /*0x1*/;
L_0x00425446:
    // 00425446  83b918010000ff         +cmp dword ptr [ecx + 0x118], -1
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(280) /* 0x118 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(-1 /*-0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0042544d  7511                   -jne 0x425460
    if (!cpu.flags.zf)
    {
        goto L_0x00425460;
    }
    // 0042544f  8b8114010000           -mov eax, dword ptr [ecx + 0x114]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(276) /* 0x114 */);
    // 00425455  e8569ffeff             -call 0x40f3b0
    cpu.esp -= 4;
    sub_40f3b0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042545a  898118010000           -mov dword ptr [ecx + 0x118], eax
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(280) /* 0x118 */) = cpu.eax;
L_0x00425460:
    // 00425460  8bb118010000           -mov esi, dword ptr [ecx + 0x118]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(280) /* 0x118 */);
    // 00425466  83feff                 +cmp esi, -1
    {
        x86::reg32 tmp1 = cpu.esi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(-1 /*-0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00425469  750d                   -jne 0x425478
    if (!cpu.flags.zf)
    {
        goto L_0x00425478;
    }
    // 0042546b  8da582000000           -lea esp, [ebp + 0x82]
    cpu.esp = x86::reg32(cpu.ebp + x86::reg32(130) /* 0x82 */);
    // 00425471  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00425472  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00425473  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00425474  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00425475  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00425476  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00425477  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x00425478:
    // 00425478  8d5d22                 -lea ebx, [ebp + 0x22]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(34) /* 0x22 */);
    // 0042547b  8d5552                 -lea edx, [ebp + 0x52]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(82) /* 0x52 */);
    // 0042547e  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 00425480  e8bba4feff             -call 0x40f940
    cpu.esp -= 4;
    sub_40f940(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00425485  8b8118010000           -mov eax, dword ptr [ecx + 0x118]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(280) /* 0x118 */);
    // 0042548b  e830a6feff             -call 0x40fac0
    cpu.esp -= 4;
    sub_40fac0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00425490  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00425492  7557                   -jne 0x4254eb
    if (!cpu.flags.zf)
    {
        goto L_0x004254eb;
    }
    // 00425494  8b8118010000           -mov eax, dword ptr [ecx + 0x118]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(280) /* 0x118 */);
    // 0042549a  e8c19ffeff             -call 0x40f460
    cpu.esp -= 4;
    sub_40f460(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042549f  8b457e                 -mov eax, dword ptr [ebp + 0x7e]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */);
    // 004254a2  c78118010000ffffffff   -mov dword ptr [ecx + 0x118], 0xffffffff
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(280) /* 0x118 */) = 4294967295 /*0xffffffff*/;
    // 004254ac  8b400c                 -mov eax, dword ptr [eax + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
    // 004254af  8b0485b8bb6f00         -mov eax, dword ptr [eax*4 + 0x6fbbb8]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(7322552) /* 0x6fbbb8 */ + cpu.eax * 4);
    // 004254b6  e8f5e5ffff             -call 0x423ab0
    cpu.esp -= 4;
    sub_423ab0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004254bb  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004254bd  740f                   -je 0x4254ce
    if (cpu.flags.zf)
    {
        goto L_0x004254ce;
    }
    // 004254bf  8b457e                 -mov eax, dword ptr [ebp + 0x7e]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */);
    // 004254c2  8b500c                 -mov edx, dword ptr [eax + 0xc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
    // 004254c5  8b0495b8bb6f00         -mov eax, dword ptr [edx*4 + 0x6fbbb8]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(7322552) /* 0x6fbbb8 */ + cpu.edx * 4);
    // 004254cc  eb0b                   -jmp 0x4254d9
    goto L_0x004254d9;
L_0x004254ce:
    // 004254ce  8b457e                 -mov eax, dword ptr [ebp + 0x7e]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */);
    // 004254d1  8b500c                 -mov edx, dword ptr [eax + 0xc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
    // 004254d4  a154105e00             -mov eax, dword ptr [0x5e1054]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(6164564) /* 0x5e1054 */);
L_0x004254d9:
    // 004254d9  e832d1ffff             -call 0x422610
    cpu.esp -= 4;
    sub_422610(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004254de  8da582000000           -lea esp, [ebp + 0x82]
    cpu.esp = x86::reg32(cpu.ebp + x86::reg32(130) /* 0x82 */);
    // 004254e4  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004254e5  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004254e6  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004254e7  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004254e8  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004254e9  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004254ea  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004254eb:
    // 004254eb  8bb914010000           -mov edi, dword ptr [ecx + 0x114]
    cpu.edi = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(276) /* 0x114 */);
    // 004254f1  83ff05                 +cmp edi, 5
    {
        x86::reg32 tmp1 = cpu.edi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(5 /*0x5*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004254f4  7409                   -je 0x4254ff
    if (cpu.flags.zf)
    {
        goto L_0x004254ff;
    }
    // 004254f6  83ff04                 +cmp edi, 4
    {
        x86::reg32 tmp1 = cpu.edi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(4 /*0x4*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004254f9  0f85c1000000           -jne 0x4255c0
    if (!cpu.flags.zf)
    {
        goto L_0x004255c0;
    }
L_0x004254ff:
    // 004254ff  8b457e                 -mov eax, dword ptr [ebp + 0x7e]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */);
    // 00425502  8b4004                 -mov eax, dword ptr [eax + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 00425505  8d9024010000           -lea edx, [eax + 0x124]
    cpu.edx = x86::reg32(cpu.eax + x86::reg32(292) /* 0x124 */);
    // 0042550b  8d5dfe                 -lea ebx, [ebp - 2]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-2) /* -0x2 */);
    // 0042550e  8d4522                 -lea eax, [ebp + 0x22]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(34) /* 0x22 */);
    // 00425511  e86aad0b00             -call 0x4e0280
    cpu.esp -= 4;
    sub_4e0280(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00425516  8b457e                 -mov eax, dword ptr [ebp + 0x7e]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */);
    // 00425519  8b4004                 -mov eax, dword ptr [eax + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 0042551c  8d7d6a                 -lea edi, [ebp + 0x6a]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(106) /* 0x6a */);
    // 0042551f  8d9024010000           -lea edx, [eax + 0x124]
    cpu.edx = x86::reg32(cpu.eax + x86::reg32(292) /* 0x124 */);
    // 00425525  8d5d46                 -lea ebx, [ebp + 0x46]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(70) /* 0x46 */);
    // 00425528  8d4552                 -lea eax, [ebp + 0x52]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(82) /* 0x52 */);
    // 0042552b  8d7546                 -lea esi, [ebp + 0x46]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(70) /* 0x46 */);
    // 0042552e  d900                   +fld dword ptr [eax]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.eax));
    // 00425530  d80a                   +fmul dword ptr [edx]
    x86::Float fpu2 = cpu.fpu.mul(fpu1, x86::Float(app->getMemory<float>(cpu.edx)));
    // 00425532  d900                   +fld dword ptr [eax]
    x86::Float fpu3 = x86::Float(app->getMemory<float>(cpu.eax));
    // 00425534  d84a04                 +fmul dword ptr [edx + 4]
    x86::Float fpu4 = cpu.fpu.mul(fpu3, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(4) /* 0x4 */)));
    // 00425537  d900                   +fld dword ptr [eax]
    x86::Float fpu5 = x86::Float(app->getMemory<float>(cpu.eax));
    // 00425539  d84a08                 +fmul dword ptr [edx + 8]
    x86::Float fpu6 = cpu.fpu.mul(fpu5, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(8) /* 0x8 */)));
    // 0042553c  d9ca                   +fxch st(2)
    
    // 0042553e  d94004                 +fld dword ptr [eax + 4]
    x86::Float fpu7 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 00425541  d84a0c                 +fmul dword ptr [edx + 0xc]
    x86::Float fpu8 = cpu.fpu.mul(fpu7, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(12) /* 0xc */)));
    // 00425544  d94004                 +fld dword ptr [eax + 4]
    x86::Float fpu9 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 00425547  d84a10                 +fmul dword ptr [edx + 0x10]
    x86::Float fpu10 = cpu.fpu.mul(fpu9, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(16) /* 0x10 */)));
    // 0042554a  d94004                 +fld dword ptr [eax + 4]
    x86::Float fpu11 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 0042554d  d84a14                 +fmul dword ptr [edx + 0x14]
    x86::Float fpu12 = cpu.fpu.mul(fpu11, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(20) /* 0x14 */)));
    // 00425550  d9ca                   +fxch st(2)
    
    // 00425552  dec3                   +faddp st(3)
    x86::Float fpu13 = cpu.fpu.add(fpu2, fpu8);
    // 00425554  dec3                   +faddp st(3)
    x86::Float fpu14 = cpu.fpu.add(fpu4, fpu10);
    // 00425556  dec3                   +faddp st(3)
    x86::Float fpu15 = cpu.fpu.add(fpu6, fpu12);
    // 00425558  d94008                 +fld dword ptr [eax + 8]
    x86::Float fpu16 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 0042555b  d84a18                 +fmul dword ptr [edx + 0x18]
    x86::Float fpu17 = cpu.fpu.mul(fpu16, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(24) /* 0x18 */)));
    // 0042555e  d94008                 +fld dword ptr [eax + 8]
    x86::Float fpu18 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 00425561  d84a1c                 +fmul dword ptr [edx + 0x1c]
    x86::Float fpu19 = cpu.fpu.mul(fpu18, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(28) /* 0x1c */)));
    // 00425564  d94008                 +fld dword ptr [eax + 8]
    x86::Float fpu20 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 00425567  d84a20                 +fmul dword ptr [edx + 0x20]
    x86::Float fpu21 = cpu.fpu.mul(fpu20, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(32) /* 0x20 */)));
    // 0042556a  d9ca                   +fxch st(2)
    
    // 0042556c  dec3                   +faddp st(3)
    x86::Float fpu22 = cpu.fpu.add(fpu13, fpu17);
    // 0042556e  dec3                   +faddp st(3)
    x86::Float fpu23 = cpu.fpu.add(fpu14, fpu19);
    // 00425570  dec3                   +faddp st(3)
    x86::Float fpu24 = cpu.fpu.add(fpu15, fpu21);
    // 00425572  8d400c                 -lea eax, [eax + 0xc]
    cpu.eax = x86::reg32(cpu.eax + x86::reg32(12) /* 0xc */);
    // 00425575  d91b                   +fstp dword ptr [ebx]
    app->getMemory<float>(cpu.ebx) = float(fpu22);
    // 00425577  d95b04                 +fstp dword ptr [ebx + 4]
    app->getMemory<float>(cpu.ebx + x86::reg32(4) /* 0x4 */) = float(fpu23);
    // 0042557a  d95b08                 +fstp dword ptr [ebx + 8]
    app->getMemory<float>(cpu.ebx + x86::reg32(8) /* 0x8 */) = float(fpu24);
    // 0042557d  8d456a                 -lea eax, [ebp + 0x6a]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(106) /* 0x6a */);
    // 00425580  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00425581  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00425582  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00425583  e8681d0700             -call 0x4972f0
    cpu.esp -= 4;
    sub_4972f0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00425588  8b457e                 -mov eax, dword ptr [ebp + 0x7e]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */);
    // 0042558b  8b4004                 -mov eax, dword ptr [eax + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 0042558e  d9e8                   +fld1 
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu25 = 1.0;
    // 00425590  d88020010000           +fadd dword ptr [eax + 0x120]
    x86::Float fpu26 = cpu.fpu.add(fpu25, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(288) /* 0x120 */)));
    // 00425596  d95d7a                 +fstp dword ptr [ebp + 0x7a]
    app->getMemory<float>(cpu.ebp + x86::reg32(122) /* 0x7a */) = float(fpu26);
    // 00425599  d85d7a                 +fcomp dword ptr [ebp + 0x7a]
    x86::Float fpu27 = cpu.fpu.st(0);
    cpu.fpu.compare(fpu27, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(122) /* 0x7a */)));
    // 0042559c  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 0042559e  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    cpu.fpu.count -= 1;
    }
    // 0042559f  7335                   -jae 0x4255d6
    if (!cpu.flags.cf)
    {
        goto L_0x004255d6;
    }
    // 004255a1  8d456a                 -lea eax, [ebp + 0x6a]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(106) /* 0x6a */);
    // 004255a4  8d556a                 -lea edx, [ebp + 0x6a]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(106) /* 0x6a */);
    // 004255a7  8d7d46                 -lea edi, [ebp + 0x46]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(70) /* 0x46 */);
    // 004255aa  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004255ab  8d756a                 -lea esi, [ebp + 0x6a]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(106) /* 0x6a */);
    // 004255ae  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 004255b3  ff757a                 -push dword ptr [ebp + 0x7a]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(122) /* 0x7a */);
    cpu.esp -= 4;
    // 004255b6  e895aa0b00             -call 0x4e0050
    cpu.esp -= 4;
    sub_4e0050(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004255bb  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004255bc  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004255bd  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004255be  eb16                   -jmp 0x4255d6
    goto L_0x004255d6;
L_0x004255c0:
    // 004255c0  b909000000             -mov ecx, 9
    cpu.ecx = 9 /*0x9*/;
    // 004255c5  8d7dfe                 -lea edi, [ebp - 2]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(-2) /* -0x2 */);
    // 004255c8  8d7522                 -lea esi, [ebp + 0x22]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(34) /* 0x22 */);
    // 004255cb  f3a5                   -rep movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004255cd  8d7d46                 -lea edi, [ebp + 0x46]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(70) /* 0x46 */);
    // 004255d0  8d7552                 -lea esi, [ebp + 0x52]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(82) /* 0x52 */);
    // 004255d3  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004255d4  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004255d5  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
L_0x004255d6:
    // 004255d6  8b457e                 -mov eax, dword ptr [ebp + 0x7e]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */);
    // 004255d9  8b4004                 -mov eax, dword ptr [eax + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 004255dc  8b8098000000           -mov eax, dword ptr [eax + 0x98]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(152) /* 0x98 */);
    // 004255e2  89455e                 -mov dword ptr [ebp + 0x5e], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(94) /* 0x5e */) = cpu.eax;
    // 004255e5  8b457e                 -mov eax, dword ptr [ebp + 0x7e]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */);
    // 004255e8  8b4004                 -mov eax, dword ptr [eax + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 004255eb  8b809c000000           -mov eax, dword ptr [eax + 0x9c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(156) /* 0x9c */);
    // 004255f1  894562                 -mov dword ptr [ebp + 0x62], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(98) /* 0x62 */) = cpu.eax;
    // 004255f4  8b457e                 -mov eax, dword ptr [ebp + 0x7e]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */);
    // 004255f7  8b4d7e                 -mov ecx, dword ptr [ebp + 0x7e]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */);
    // 004255fa  8b4004                 -mov eax, dword ptr [eax + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 004255fd  8d5d46                 -lea ebx, [ebp + 0x46]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(70) /* 0x46 */);
    // 00425600  8d555e                 -lea edx, [ebp + 0x5e]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(94) /* 0x5e */);
    // 00425603  8b80a0000000           -mov eax, dword ptr [eax + 0xa0]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(160) /* 0xa0 */);
    // 00425609  83c114                 -add ecx, 0x14
    (cpu.ecx) += x86::reg32(x86::sreg32(20 /*0x14*/));
    // 0042560c  894566                 -mov dword ptr [ebp + 0x66], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(102) /* 0x66 */) = cpu.eax;
    // 0042560f  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 00425614  e897a90b00             -call 0x4dffb0
    cpu.esp -= 4;
    sub_4dffb0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00425619  8b457e                 -mov eax, dword ptr [ebp + 0x7e]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */);
    // 0042561c  8d7546                 -lea esi, [ebp + 0x46]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(70) /* 0x46 */);
    // 0042561f  8d7820                 -lea edi, [eax + 0x20]
    cpu.edi = x86::reg32(cpu.eax + x86::reg32(32) /* 0x20 */);
    // 00425622  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00425623  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00425624  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00425625  b909000000             -mov ecx, 9
    cpu.ecx = 9 /*0x9*/;
    // 0042562a  8d75fe                 -lea esi, [ebp - 2]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(-2) /* -0x2 */);
    // 0042562d  8d782c                 -lea edi, [eax + 0x2c]
    cpu.edi = x86::reg32(cpu.eax + x86::reg32(44) /* 0x2c */);
    // 00425630  f3a5                   -rep movsd dword ptr es:[edi], dword ptr [esi]
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
L_0x00425632:
    // 00425632  8da582000000           -lea esp, [ebp + 0x82]
    cpu.esp = x86::reg32(cpu.ebp + x86::reg32(130) /* 0x82 */);
    // 00425638  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00425639  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042563a  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042563b  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042563c  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042563d  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042563e  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x90 */
void Application::sub_425640(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00425640  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00425641  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00425642  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00425643  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00425644  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00425645  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00425646  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00425648  81ec94000000           -sub esp, 0x94
    (cpu.esp) -= x86::reg32(x86::sreg32(148 /*0x94*/));
    // 0042564e  81ed82000000           -sub ebp, 0x82
    (cpu.ebp) -= x86::reg32(x86::sreg32(130 /*0x82*/));
    // 00425654  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 00425656  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00425658  8b9018010000           -mov edx, dword ptr [eax + 0x118]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(280) /* 0x118 */);
    // 0042565e  c740549a99993f         -mov dword ptr [eax + 0x54], 0x3f99999a
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(84) /* 0x54 */) = 1067030938 /*0x3f99999a*/;
    // 00425665  83faff                 +cmp edx, -1
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
    // 00425668  0f85d7000000           -jne 0x425745
    if (!cpu.flags.zf)
    {
        goto L_0x00425745;
    }
    // 0042566e  8d45ee                 -lea eax, [ebp - 0x12]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-18) /* -0x12 */);
    // 00425671  8d4d66                 -lea ecx, [ebp + 0x66]
    cpu.ecx = x86::reg32(cpu.ebp + x86::reg32(102) /* 0x66 */);
    // 00425674  bb01000000             -mov ebx, 1
    cpu.ebx = 1 /*0x1*/;
    // 00425679  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 0042567a  ba02000000             -mov edx, 2
    cpu.edx = 2 /*0x2*/;
    // 0042567f  8b8614010000           -mov eax, dword ptr [esi + 0x114]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(276) /* 0x114 */);
    // 00425685  e846a2feff             -call 0x40f8d0
    cpu.esp -= 4;
    sub_40f8d0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042568a  8b4566                 -mov eax, dword ptr [ebp + 0x66]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(102) /* 0x66 */);
    // 0042568d  89457e                 -mov dword ptr [ebp + 0x7e], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */) = cpu.eax;
    // 00425690  db457e                 +fild dword ptr [ebp + 0x7e]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */)));
    // 00425693  8b456a                 -mov eax, dword ptr [ebp + 0x6a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(106) /* 0x6a */);
    // 00425696  dc0d1c6f5300           +fmul qword ptr [0x536f1c]
    x86::Float fpu2 = cpu.fpu.mul(fpu1, x86::Float(app->getMemory<double>(x86::reg32(5467932) /* 0x536f1c */)));
    // 0042569c  89457e                 -mov dword ptr [ebp + 0x7e], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */) = cpu.eax;
    // 0042569f  8b456e                 -mov eax, dword ptr [ebp + 0x6e]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(110) /* 0x6e */);
    // 004256a2  db457e                 +fild dword ptr [ebp + 0x7e]
    x86::Float fpu3 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */)));
    // 004256a5  89457e                 -mov dword ptr [ebp + 0x7e], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */) = cpu.eax;
    // 004256a8  dc0d1c6f5300           +fmul qword ptr [0x536f1c]
    x86::Float fpu4 = cpu.fpu.mul(fpu3, x86::Float(app->getMemory<double>(x86::reg32(5467932) /* 0x536f1c */)));
    // 004256ae  db457e                 +fild dword ptr [ebp + 0x7e]
    x86::Float fpu5 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */)));
    // 004256b1  8b45ee                 -mov eax, dword ptr [ebp - 0x12]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-18) /* -0x12 */);
    // 004256b4  dc0d1c6f5300           +fmul qword ptr [0x536f1c]
    x86::Float fpu6 = cpu.fpu.mul(fpu5, x86::Float(app->getMemory<double>(x86::reg32(5467932) /* 0x536f1c */)));
    // 004256ba  89457e                 -mov dword ptr [ebp + 0x7e], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */) = cpu.eax;
    // 004256bd  8b45f2                 -mov eax, dword ptr [ebp - 0xe]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-14) /* -0xe */);
    // 004256c0  db457e                 +fild dword ptr [ebp + 0x7e]
    x86::Float fpu7 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */)));
    // 004256c3  89457e                 -mov dword ptr [ebp + 0x7e], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */) = cpu.eax;
    // 004256c6  dc0d1c6f5300           +fmul qword ptr [0x536f1c]
    x86::Float fpu8 = cpu.fpu.mul(fpu7, x86::Float(app->getMemory<double>(x86::reg32(5467932) /* 0x536f1c */)));
    // 004256cc  db457e                 +fild dword ptr [ebp + 0x7e]
    x86::Float fpu9 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */)));
    // 004256cf  8b45f6                 -mov eax, dword ptr [ebp - 0xa]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-10) /* -0xa */);
    // 004256d2  dc0d1c6f5300           +fmul qword ptr [0x536f1c]
    x86::Float fpu10 = cpu.fpu.mul(fpu9, x86::Float(app->getMemory<double>(x86::reg32(5467932) /* 0x536f1c */)));
    // 004256d8  89457e                 -mov dword ptr [ebp + 0x7e], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */) = cpu.eax;
    // 004256db  8b45fa                 -mov eax, dword ptr [ebp - 6]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-6) /* -0x6 */);
    // 004256de  db457e                 +fild dword ptr [ebp + 0x7e]
    x86::Float fpu11 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */)));
    // 004256e1  89457e                 -mov dword ptr [ebp + 0x7e], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */) = cpu.eax;
    // 004256e4  dc0d1c6f5300           +fmul qword ptr [0x536f1c]
    x86::Float fpu12 = cpu.fpu.mul(fpu11, x86::Float(app->getMemory<double>(x86::reg32(5467932) /* 0x536f1c */)));
    // 004256ea  db457e                 +fild dword ptr [ebp + 0x7e]
    x86::Float fpu13 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */)));
    // 004256ed  8b45fe                 -mov eax, dword ptr [ebp - 2]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-2) /* -0x2 */);
    // 004256f0  dc0d1c6f5300           +fmul qword ptr [0x536f1c]
    x86::Float fpu14 = cpu.fpu.mul(fpu13, x86::Float(app->getMemory<double>(x86::reg32(5467932) /* 0x536f1c */)));
    // 004256f6  89457e                 -mov dword ptr [ebp + 0x7e], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */) = cpu.eax;
    // 004256f9  d9ce                   +fxch st(6)
    
    // 004256fb  d95d72                 +fstp dword ptr [ebp + 0x72]
    app->getMemory<float>(cpu.ebp + x86::reg32(114) /* 0x72 */) = float(fpu2);
    // 004256fe  db457e                 +fild dword ptr [ebp + 0x7e]
    x86::Float fpu15 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */)));
    // 00425701  8b4502                 -mov eax, dword ptr [ebp + 2]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(2) /* 0x2 */);
    // 00425704  dc0d1c6f5300           +fmul qword ptr [0x536f1c]
    x86::Float fpu16 = cpu.fpu.mul(fpu15, x86::Float(app->getMemory<double>(x86::reg32(5467932) /* 0x536f1c */)));
    // 0042570a  89457e                 -mov dword ptr [ebp + 0x7e], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */) = cpu.eax;
    // 0042570d  d9cd                   +fxch st(5)
    
    // 0042570f  d95d76                 +fstp dword ptr [ebp + 0x76]
    app->getMemory<float>(cpu.ebp + x86::reg32(118) /* 0x76 */) = float(fpu4);
    // 00425712  db457e                 +fild dword ptr [ebp + 0x7e]
    x86::Float fpu17 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */)));
    // 00425715  8b4506                 -mov eax, dword ptr [ebp + 6]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(6) /* 0x6 */);
    // 00425718  dc0d1c6f5300           +fmul qword ptr [0x536f1c]
    x86::Float fpu18 = cpu.fpu.mul(fpu17, x86::Float(app->getMemory<double>(x86::reg32(5467932) /* 0x536f1c */)));
    // 0042571e  89457e                 -mov dword ptr [ebp + 0x7e], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */) = cpu.eax;
    // 00425721  d9cc                   +fxch st(4)
    
    // 00425723  d95d7a                 +fstp dword ptr [ebp + 0x7a]
    app->getMemory<float>(cpu.ebp + x86::reg32(122) /* 0x7a */) = float(fpu6);
    // 00425726  db457e                 +fild dword ptr [ebp + 0x7e]
    x86::Float fpu19 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */)));
    // 00425729  8b450a                 -mov eax, dword ptr [ebp + 0xa]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(10) /* 0xa */);
    // 0042572c  dc0d1c6f5300           +fmul qword ptr [0x536f1c]
    x86::Float fpu20 = cpu.fpu.mul(fpu19, x86::Float(app->getMemory<double>(x86::reg32(5467932) /* 0x536f1c */)));
    // 00425732  89457e                 -mov dword ptr [ebp + 0x7e], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */) = cpu.eax;
    // 00425735  d9cb                   +fxch st(3)
    
    // 00425737  d95d12                 +fstp dword ptr [ebp + 0x12]
    app->getMemory<float>(cpu.ebp + x86::reg32(18) /* 0x12 */) = float(fpu8);
    // 0042573a  db457e                 +fild dword ptr [ebp + 0x7e]
    x86::Float fpu21 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */)));
    // 0042573d  8b450e                 -mov eax, dword ptr [ebp + 0xe]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(14) /* 0xe */);
    cpu.fpu.count += 7;
    cpu.fpu.st(0) = fpu21;
    cpu.fpu.st(1) = fpu12;
    cpu.fpu.st(2) = fpu10;
    cpu.fpu.st(3) = fpu20;
    cpu.fpu.st(4) = fpu18;
    cpu.fpu.st(5) = fpu16;
    cpu.fpu.st(6) = fpu14;
    }
    // 00425740  e9df010000             -jmp 0x425924
    goto L_0x00425924;
L_0x00425745:
    // 00425745  8d5d12                 -lea ebx, [ebp + 0x12]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(18) /* 0x12 */);
    // 00425748  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 0042574a  8d5572                 -lea edx, [ebp + 0x72]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(114) /* 0x72 */);
    // 0042574d  e8eea1feff             -call 0x40f940
    cpu.esp -= 4;
    sub_40f940(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00425752  8b8618010000           -mov eax, dword ptr [esi + 0x118]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(280) /* 0x118 */);
    // 00425758  e863a3feff             -call 0x40fac0
    cpu.esp -= 4;
    sub_40fac0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042575d  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0042575f  0f85f3010000           -jne 0x425958
    if (!cpu.flags.zf)
    {
        goto L_0x00425958;
    }
    // 00425765  8b8618010000           -mov eax, dword ptr [esi + 0x118]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(280) /* 0x118 */);
    // 0042576b  e8f09cfeff             -call 0x40f460
    cpu.esp -= 4;
    sub_40f460(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00425770  c78618010000ffffffff   -mov dword ptr [esi + 0x118], 0xffffffff
    app->getMemory<x86::reg32>(cpu.esi + x86::reg32(280) /* 0x118 */) = 4294967295 /*0xffffffff*/;
    // 0042577a  833db0d36f0001         +cmp dword ptr [0x6fd3b0], 1
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(7328688) /* 0x6fd3b0 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1 /*0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00425781  0f8ecb000000           -jle 0x425852
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00425852;
    }
    // 00425787  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
L_0x00425789:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00425789  3b0518d56f00           +cmp eax, dword ptr [0x6fd518]
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(7329048) /* 0x6fd518 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0042578f  0f8de9010000           -jge 0x42597e
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x0042597e;
    }
    // 00425795  8b3485c8fa5e00         -mov esi, dword ptr [eax*4 + 0x5efac8]
    cpu.esi = app->getMemory<x86::reg32>(x86::reg32(6224584) /* 0x5efac8 */ + cpu.eax * 4);
    // 0042579c  83bec402000000         +cmp dword ptr [esi + 0x2c4], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(708) /* 0x2c4 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004257a3  0f85a3000000           -jne 0x42584c
    if (!cpu.flags.zf)
    {
        goto L_0x0042584c;
    }
    // 004257a9  8a9600020000           -mov dl, byte ptr [esi + 0x200]
    cpu.dl = app->getMemory<x86::reg8>(cpu.esi + x86::reg32(512) /* 0x200 */);
    // 004257af  f6c280                 +test dl, 0x80
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.dl & 128 /*0x80*/));
    // 004257b2  0f8594000000           -jne 0x42584c
    if (!cpu.flags.zf)
    {
        goto L_0x0042584c;
    }
    // 004257b8  f6c201                 +test dl, 1
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.dl & 1 /*0x1*/));
    // 004257bb  0f848b000000           -je 0x42584c
    if (cpu.flags.zf)
    {
        goto L_0x0042584c;
    }
    // 004257c1  a3f8d46f00             -mov dword ptr [0x6fd4f8], eax
    app->getMemory<x86::reg32>(x86::reg32(7329016) /* 0x6fd4f8 */) = cpu.eax;
    // 004257c6  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004257c8  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 004257ca  e8f1bdffff             -call 0x4215c0
    cpu.esp -= 4;
    sub_4215c0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004257cf  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 004257d1  e86afe0500             -call 0x485640
    cpu.esp -= 4;
    sub_485640(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004257d6  833d94367d0000         +cmp dword ptr [0x7d3694], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(8205972) /* 0x7d3694 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004257dd  751e                   -jne 0x4257fd
    if (!cpu.flags.zf)
    {
        goto L_0x004257fd;
    }
    // 004257df  bba4010000             -mov ebx, 0x1a4
    cpu.ebx = 420 /*0x1a4*/;
    // 004257e4  ba28c66f00             -mov edx, 0x6fc628
    cpu.edx = 7325224 /*0x6fc628*/;
    // 004257e9  b850bc6f00             -mov eax, 0x6fbc50
    cpu.eax = 7322704 /*0x6fbc50*/;
    // 004257ee  e8fd4c0c00             -call 0x4ea4f0
    cpu.esp -= 4;
    nfs3hp::ea::memmove(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004257f3  c70594367d0001000000   -mov dword ptr [0x7d3694], 1
    app->getMemory<x86::reg32>(x86::reg32(8205972) /* 0x7d3694 */) = 1 /*0x1*/;
L_0x004257fd:
    // 004257fd  be0000803f             -mov esi, 0x3f800000
    cpu.esi = 1065353216 /*0x3f800000*/;
    // 00425802  b802000000             -mov eax, 2
    cpu.eax = 2 /*0x2*/;
    // 00425807  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 00425809  ba11000000             -mov edx, 0x11
    cpu.edx = 17 /*0x11*/;
    // 0042580e  890d88bd6f00           -mov dword ptr [0x6fbd88], ecx
    app->getMemory<x86::reg32>(x86::reg32(7323016) /* 0x6fbd88 */) = cpu.ecx;
    // 00425814  890d84bd6f00           -mov dword ptr [0x6fbd84], ecx
    app->getMemory<x86::reg32>(x86::reg32(7323012) /* 0x6fbd84 */) = cpu.ecx;
    // 0042581a  893590bd6f00           -mov dword ptr [0x6fbd90], esi
    app->getMemory<x86::reg32>(x86::reg32(7323024) /* 0x6fbd90 */) = cpu.esi;
    // 00425820  89358cbd6f00           -mov dword ptr [0x6fbd8c], esi
    app->getMemory<x86::reg32>(x86::reg32(7323020) /* 0x6fbd8c */) = cpu.esi;
    // 00425826  a370bc6f00             -mov dword ptr [0x6fbc70], eax
    app->getMemory<x86::reg32>(x86::reg32(7322736) /* 0x6fbc70 */) = cpu.eax;
    // 0042582b  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 0042582d  893560bc6f00           -mov dword ptr [0x6fbc60], esi
    app->getMemory<x86::reg32>(x86::reg32(7322720) /* 0x6fbc60 */) = cpu.esi;
    // 00425833  e888fb0500             -call 0x4853c0
    cpu.esp -= 4;
    sub_4853c0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00425838  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
    // 0042583a  e881ec0500             -call 0x4844c0
    cpu.esp -= 4;
    sub_4844c0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042583f  8da582000000           -lea esp, [ebp + 0x82]
    cpu.esp = x86::reg32(cpu.ebp + x86::reg32(130) /* 0x82 */);
    // 00425845  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00425846  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00425847  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00425848  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00425849  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042584a  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042584b  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x0042584c:
    // 0042584c  40                     +inc eax
    {
        x86::reg32& tmp = cpu.eax;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 0042584d  e937ffffff             -jmp 0x425789
    goto L_0x00425789;
L_0x00425852:
    // 00425852  8d4536                 -lea eax, [ebp + 0x36]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(54) /* 0x36 */);
    // 00425855  bb01000000             -mov ebx, 1
    cpu.ebx = 1 /*0x1*/;
    // 0042585a  ba02000000             -mov edx, 2
    cpu.edx = 2 /*0x2*/;
    // 0042585f  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00425860  8b8114010000           -mov eax, dword ptr [ecx + 0x114]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(276) /* 0x114 */);
    // 00425866  8d4d5a                 -lea ecx, [ebp + 0x5a]
    cpu.ecx = x86::reg32(cpu.ebp + x86::reg32(90) /* 0x5a */);
    // 00425869  e862a0feff             -call 0x40f8d0
    cpu.esp -= 4;
    sub_40f8d0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042586e  8b455a                 -mov eax, dword ptr [ebp + 0x5a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(90) /* 0x5a */);
    // 00425871  89457e                 -mov dword ptr [ebp + 0x7e], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */) = cpu.eax;
    // 00425874  db457e                 -fild dword ptr [ebp + 0x7e]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu22 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */)));
    // 00425877  8b455e                 -mov eax, dword ptr [ebp + 0x5e]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(94) /* 0x5e */);
    // 0042587a  dc0d1c6f5300           -fmul qword ptr [0x536f1c]
    x86::Float fpu23 = cpu.fpu.mul(fpu22, x86::Float(app->getMemory<double>(x86::reg32(5467932) /* 0x536f1c */)));
    // 00425880  89457e                 -mov dword ptr [ebp + 0x7e], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */) = cpu.eax;
    // 00425883  8b4562                 -mov eax, dword ptr [ebp + 0x62]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(98) /* 0x62 */);
    // 00425886  db457e                 -fild dword ptr [ebp + 0x7e]
    x86::Float fpu24 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */)));
    // 00425889  89457e                 -mov dword ptr [ebp + 0x7e], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */) = cpu.eax;
    // 0042588c  dc0d1c6f5300           -fmul qword ptr [0x536f1c]
    x86::Float fpu25 = cpu.fpu.mul(fpu24, x86::Float(app->getMemory<double>(x86::reg32(5467932) /* 0x536f1c */)));
    // 00425892  db457e                 -fild dword ptr [ebp + 0x7e]
    x86::Float fpu26 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */)));
    // 00425895  8b4536                 -mov eax, dword ptr [ebp + 0x36]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(54) /* 0x36 */);
    // 00425898  dc0d1c6f5300           -fmul qword ptr [0x536f1c]
    x86::Float fpu27 = cpu.fpu.mul(fpu26, x86::Float(app->getMemory<double>(x86::reg32(5467932) /* 0x536f1c */)));
    // 0042589e  89457e                 -mov dword ptr [ebp + 0x7e], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */) = cpu.eax;
    // 004258a1  8b453a                 -mov eax, dword ptr [ebp + 0x3a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(58) /* 0x3a */);
    // 004258a4  db457e                 -fild dword ptr [ebp + 0x7e]
    x86::Float fpu28 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */)));
    // 004258a7  89457e                 -mov dword ptr [ebp + 0x7e], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */) = cpu.eax;
    // 004258aa  dc0d1c6f5300           -fmul qword ptr [0x536f1c]
    x86::Float fpu29 = cpu.fpu.mul(fpu28, x86::Float(app->getMemory<double>(x86::reg32(5467932) /* 0x536f1c */)));
    // 004258b0  db457e                 -fild dword ptr [ebp + 0x7e]
    x86::Float fpu30 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */)));
    // 004258b3  8b453e                 -mov eax, dword ptr [ebp + 0x3e]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(62) /* 0x3e */);
    // 004258b6  dc0d1c6f5300           -fmul qword ptr [0x536f1c]
    x86::Float fpu31 = cpu.fpu.mul(fpu30, x86::Float(app->getMemory<double>(x86::reg32(5467932) /* 0x536f1c */)));
    // 004258bc  89457e                 -mov dword ptr [ebp + 0x7e], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */) = cpu.eax;
    // 004258bf  8b4542                 -mov eax, dword ptr [ebp + 0x42]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(66) /* 0x42 */);
    // 004258c2  db457e                 -fild dword ptr [ebp + 0x7e]
    x86::Float fpu32 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */)));
    // 004258c5  89457e                 -mov dword ptr [ebp + 0x7e], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */) = cpu.eax;
    // 004258c8  dc0d1c6f5300           -fmul qword ptr [0x536f1c]
    x86::Float fpu33 = cpu.fpu.mul(fpu32, x86::Float(app->getMemory<double>(x86::reg32(5467932) /* 0x536f1c */)));
    // 004258ce  db457e                 -fild dword ptr [ebp + 0x7e]
    x86::Float fpu34 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */)));
    // 004258d1  8b4546                 -mov eax, dword ptr [ebp + 0x46]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(70) /* 0x46 */);
    // 004258d4  dc0d1c6f5300           -fmul qword ptr [0x536f1c]
    x86::Float fpu35 = cpu.fpu.mul(fpu34, x86::Float(app->getMemory<double>(x86::reg32(5467932) /* 0x536f1c */)));
    // 004258da  89457e                 -mov dword ptr [ebp + 0x7e], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */) = cpu.eax;
    // 004258dd  d9ce                   -fxch st(6)
    
    // 004258df  d95d72                 -fstp dword ptr [ebp + 0x72]
    app->getMemory<float>(cpu.ebp + x86::reg32(114) /* 0x72 */) = float(fpu23);
    // 004258e2  db457e                 -fild dword ptr [ebp + 0x7e]
    x86::Float fpu36 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */)));
    // 004258e5  8b454a                 -mov eax, dword ptr [ebp + 0x4a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(74) /* 0x4a */);
    // 004258e8  dc0d1c6f5300           -fmul qword ptr [0x536f1c]
    x86::Float fpu37 = cpu.fpu.mul(fpu36, x86::Float(app->getMemory<double>(x86::reg32(5467932) /* 0x536f1c */)));
    // 004258ee  89457e                 -mov dword ptr [ebp + 0x7e], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */) = cpu.eax;
    // 004258f1  d9cd                   -fxch st(5)
    
    // 004258f3  d95d76                 -fstp dword ptr [ebp + 0x76]
    app->getMemory<float>(cpu.ebp + x86::reg32(118) /* 0x76 */) = float(fpu25);
    // 004258f6  db457e                 -fild dword ptr [ebp + 0x7e]
    x86::Float fpu38 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */)));
    // 004258f9  8b454e                 -mov eax, dword ptr [ebp + 0x4e]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(78) /* 0x4e */);
    // 004258fc  dc0d1c6f5300           -fmul qword ptr [0x536f1c]
    x86::Float fpu39 = cpu.fpu.mul(fpu38, x86::Float(app->getMemory<double>(x86::reg32(5467932) /* 0x536f1c */)));
    // 00425902  89457e                 -mov dword ptr [ebp + 0x7e], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */) = cpu.eax;
    // 00425905  d9cc                   -fxch st(4)
    
    // 00425907  d95d7a                 -fstp dword ptr [ebp + 0x7a]
    app->getMemory<float>(cpu.ebp + x86::reg32(122) /* 0x7a */) = float(fpu27);
    // 0042590a  db457e                 -fild dword ptr [ebp + 0x7e]
    x86::Float fpu40 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */)));
    // 0042590d  8b4552                 -mov eax, dword ptr [ebp + 0x52]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(82) /* 0x52 */);
    // 00425910  dc0d1c6f5300           -fmul qword ptr [0x536f1c]
    x86::Float fpu41 = cpu.fpu.mul(fpu40, x86::Float(app->getMemory<double>(x86::reg32(5467932) /* 0x536f1c */)));
    // 00425916  89457e                 -mov dword ptr [ebp + 0x7e], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */) = cpu.eax;
    // 00425919  d9cb                   -fxch st(3)
    
    // 0042591b  d95d12                 -fstp dword ptr [ebp + 0x12]
    app->getMemory<float>(cpu.ebp + x86::reg32(18) /* 0x12 */) = float(fpu29);
    // 0042591e  db457e                 -fild dword ptr [ebp + 0x7e]
    x86::Float fpu42 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */)));
    // 00425921  8b4556                 -mov eax, dword ptr [ebp + 0x56]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(86) /* 0x56 */);
    cpu.fpu.count += 7;
    cpu.fpu.st(0) = fpu42;
    cpu.fpu.st(1) = fpu33;
    cpu.fpu.st(2) = fpu31;
    cpu.fpu.st(3) = fpu41;
    cpu.fpu.st(4) = fpu39;
    cpu.fpu.st(5) = fpu37;
    cpu.fpu.st(6) = fpu35;
    }
L_0x00425924:
    // 00425924  dc0d1c6f5300           -fmul qword ptr [0x536f1c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu43 = cpu.fpu.st(0);
    x86::Float fpu44 = cpu.fpu.mul(fpu43, x86::Float(app->getMemory<double>(x86::reg32(5467932) /* 0x536f1c */)));
    // 0042592a  89457e                 -mov dword ptr [ebp + 0x7e], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */) = cpu.eax;
    // 0042592d  d9ca                   -fxch st(2)
    
    // 0042592f  d95d16                 -fstp dword ptr [ebp + 0x16]
    x86::Float fpu45 = cpu.fpu.st(2);
    app->getMemory<float>(cpu.ebp + x86::reg32(22) /* 0x16 */) = float(fpu45);
    // 00425932  db457e                 -fild dword ptr [ebp + 0x7e]
    x86::Float fpu46 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */)));
    // 00425935  dc0d1c6f5300           -fmul qword ptr [0x536f1c]
    x86::Float fpu47 = cpu.fpu.mul(fpu46, x86::Float(app->getMemory<double>(x86::reg32(5467932) /* 0x536f1c */)));
    // 0042593b  d9c9                   -fxch st(1)
    
    // 0042593d  d95d1a                 -fstp dword ptr [ebp + 0x1a]
    x86::Float fpu48 = cpu.fpu.st(1);
    app->getMemory<float>(cpu.ebp + x86::reg32(26) /* 0x1a */) = float(fpu48);
    // 00425940  d9cd                   -fxch st(5)
    
    // 00425942  d95d1e                 -fstp dword ptr [ebp + 0x1e]
    x86::Float fpu49 = cpu.fpu.st(6);
    app->getMemory<float>(cpu.ebp + x86::reg32(30) /* 0x1e */) = float(fpu49);
    // 00425945  d9cb                   -fxch st(3)
    
    // 00425947  d95d22                 -fstp dword ptr [ebp + 0x22]
    x86::Float fpu50 = cpu.fpu.st(5);
    app->getMemory<float>(cpu.ebp + x86::reg32(34) /* 0x22 */) = float(fpu50);
    // 0042594a  d9c9                   -fxch st(1)
    
    // 0042594c  d95d26                 -fstp dword ptr [ebp + 0x26]
    x86::Float fpu51 = cpu.fpu.st(4);
    app->getMemory<float>(cpu.ebp + x86::reg32(38) /* 0x26 */) = float(fpu51);
    // 0042594f  d95d2a                 -fstp dword ptr [ebp + 0x2a]
    x86::Float fpu52 = cpu.fpu.st(3);
    app->getMemory<float>(cpu.ebp + x86::reg32(42) /* 0x2a */) = float(fpu52);
    // 00425952  d95d2e                 -fstp dword ptr [ebp + 0x2e]
    app->getMemory<float>(cpu.ebp + x86::reg32(46) /* 0x2e */) = float(fpu44);
    // 00425955  d95d32                 -fstp dword ptr [ebp + 0x32]
    app->getMemory<float>(cpu.ebp + x86::reg32(50) /* 0x32 */) = float(fpu47);
    cpu.fpu.count -= 7;
    }
L_0x00425958:
    // 00425958  8b4604                 -mov eax, dword ptr [esi + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 0042595b  8d5d72                 -lea ebx, [ebp + 0x72]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(114) /* 0x72 */);
    // 0042595e  8d9098000000           -lea edx, [eax + 0x98]
    cpu.edx = x86::reg32(cpu.eax + x86::reg32(152) /* 0x98 */);
    // 00425964  8d4e14                 -lea ecx, [esi + 0x14]
    cpu.ecx = x86::reg32(cpu.esi + x86::reg32(20) /* 0x14 */);
    // 00425967  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 0042596c  e83fa60b00             -call 0x4dffb0
    cpu.esp -= 4;
    sub_4dffb0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00425971  b909000000             -mov ecx, 9
    cpu.ecx = 9 /*0x9*/;
    // 00425976  8d7e2c                 -lea edi, [esi + 0x2c]
    cpu.edi = x86::reg32(cpu.esi + x86::reg32(44) /* 0x2c */);
    // 00425979  8d7512                 -lea esi, [ebp + 0x12]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(18) /* 0x12 */);
    // 0042597c  f3a5                   -rep movsd dword ptr es:[edi], dword ptr [esi]
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
L_0x0042597e:
    // 0042597e  8da582000000           -lea esp, [ebp + 0x82]
    cpu.esp = x86::reg32(cpu.ebp + x86::reg32(130) /* 0x82 */);
    // 00425984  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00425985  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00425986  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00425987  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00425988  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00425989  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042598a  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x40 0x00 0x8b 0xc9 */
void Application::sub_425990(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00425990  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00425991  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00425992  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00425993  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00425994  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00425995  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00425996  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00425998  83ec18                 -sub esp, 0x18
    (cpu.esp) -= x86::reg32(x86::sreg32(24 /*0x18*/));
    // 0042599b  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 0042599d  8b5004                 -mov edx, dword ptr [eax + 4]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 004259a0  89c7                   -mov edi, eax
    cpu.edi = cpu.eax;
    // 004259a2  8b8298000000           -mov eax, dword ptr [edx + 0x98]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(152) /* 0x98 */);
    // 004259a8  8945f4                 -mov dword ptr [ebp - 0xc], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.eax;
    // 004259ab  8b4604                 -mov eax, dword ptr [esi + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 004259ae  8b809c000000           -mov eax, dword ptr [eax + 0x9c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(156) /* 0x9c */);
    // 004259b4  8945f8                 -mov dword ptr [ebp - 8], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.eax;
    // 004259b7  8b4604                 -mov eax, dword ptr [esi + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 004259ba  8b80a0000000           -mov eax, dword ptr [eax + 0xa0]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(160) /* 0xa0 */);
    // 004259c0  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 004259c3  8b4604                 -mov eax, dword ptr [esi + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 004259c6  81b80c010000f4fd343f   +cmp dword ptr [eax + 0x10c], 0x3f34fdf4
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(268) /* 0x10c */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1060437492 /*0x3f34fdf4*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004259d0  7d3e                   -jge 0x425a10
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00425a10;
    }
    // 004259d2  83be0c01000000         +cmp dword ptr [esi + 0x10c], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(268) /* 0x10c */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004259d9  752b                   -jne 0x425a06
    if (!cpu.flags.zf)
    {
        goto L_0x00425a06;
    }
    // 004259db  83ba9809000000         +cmp dword ptr [edx + 0x998], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(2456) /* 0x998 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004259e2  7e07                   -jle 0x4259eb
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004259eb;
    }
    // 004259e4  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 004259e9  eb02                   -jmp 0x4259ed
    goto L_0x004259ed;
L_0x004259eb:
    // 004259eb  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
L_0x004259ed:
    // 004259ed  8d5df4                 -lea ebx, [ebp - 0xc]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 004259f0  8d4e20                 -lea ecx, [esi + 0x20]
    cpu.ecx = x86::reg32(cpu.esi + x86::reg32(32) /* 0x20 */);
    // 004259f3  8986fc000000           -mov dword ptr [esi + 0xfc], eax
    app->getMemory<x86::reg32>(cpu.esi + x86::reg32(252) /* 0xfc */) = cpu.eax;
    // 004259f9  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 004259fe  8d5614                 -lea edx, [esi + 0x14]
    cpu.edx = x86::reg32(cpu.esi + x86::reg32(20) /* 0x14 */);
    // 00425a01  e8faa50b00             -call 0x4e0000
    cpu.esp -= 4;
    sub_4e0000(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00425a06:
    // 00425a06  c7860c01000040000000   -mov dword ptr [esi + 0x10c], 0x40
    app->getMemory<x86::reg32>(cpu.esi + x86::reg32(268) /* 0x10c */) = 64 /*0x40*/;
L_0x00425a10:
    // 00425a10  8b460c                 -mov eax, dword ptr [esi + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 00425a13  833c85a0c4790000       +cmp dword ptr [eax*4 + 0x79c4a0], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(7980192) /* 0x79c4a0 */ + cpu.eax * 4);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00425a1b  740f                   -je 0x425a2c
    if (cpu.flags.zf)
    {
        goto L_0x00425a2c;
    }
    // 00425a1d  8aa71b010000           -mov ah, byte ptr [edi + 0x11b]
    cpu.ah = app->getMemory<x86::reg8>(cpu.edi + x86::reg32(283) /* 0x11b */);
    // 00425a23  80f480                 -xor ah, 0x80
    cpu.ah ^= x86::reg8(x86::sreg8(128 /*0x80*/));
    // 00425a26  88a71b010000           -mov byte ptr [edi + 0x11b], ah
    app->getMemory<x86::reg8>(cpu.edi + x86::reg32(283) /* 0x11b */) = cpu.ah;
L_0x00425a2c:
    // 00425a2c  8b4604                 -mov eax, dword ptr [esi + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 00425a2f  8d90c0000000           -lea edx, [eax + 0xc0]
    cpu.edx = x86::reg32(cpu.eax + x86::reg32(192) /* 0xc0 */);
    // 00425a35  8d5de8                 -lea ebx, [ebp - 0x18]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-24) /* -0x18 */);
    // 00425a38  8d8710010000           -lea eax, [edi + 0x110]
    cpu.eax = x86::reg32(cpu.edi + x86::reg32(272) /* 0x110 */);
    // 00425a3e  8d4e14                 -lea ecx, [esi + 0x14]
    cpu.ecx = x86::reg32(cpu.esi + x86::reg32(20) /* 0x14 */);
    // 00425a41  d900                   -fld dword ptr [eax]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.eax));
    // 00425a43  d80a                   -fmul dword ptr [edx]
    x86::Float fpu2 = cpu.fpu.mul(fpu1, x86::Float(app->getMemory<float>(cpu.edx)));
    // 00425a45  d900                   -fld dword ptr [eax]
    x86::Float fpu3 = x86::Float(app->getMemory<float>(cpu.eax));
    // 00425a47  d84a04                 -fmul dword ptr [edx + 4]
    x86::Float fpu4 = cpu.fpu.mul(fpu3, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(4) /* 0x4 */)));
    // 00425a4a  d900                   -fld dword ptr [eax]
    x86::Float fpu5 = x86::Float(app->getMemory<float>(cpu.eax));
    // 00425a4c  d84a08                 -fmul dword ptr [edx + 8]
    x86::Float fpu6 = cpu.fpu.mul(fpu5, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(8) /* 0x8 */)));
    // 00425a4f  d9ca                   -fxch st(2)
    
    // 00425a51  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu7 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 00425a54  d84a0c                 -fmul dword ptr [edx + 0xc]
    x86::Float fpu8 = cpu.fpu.mul(fpu7, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(12) /* 0xc */)));
    // 00425a57  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu9 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 00425a5a  d84a10                 -fmul dword ptr [edx + 0x10]
    x86::Float fpu10 = cpu.fpu.mul(fpu9, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(16) /* 0x10 */)));
    // 00425a5d  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu11 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 00425a60  d84a14                 -fmul dword ptr [edx + 0x14]
    x86::Float fpu12 = cpu.fpu.mul(fpu11, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(20) /* 0x14 */)));
    // 00425a63  d9ca                   -fxch st(2)
    
    // 00425a65  dec3                   -faddp st(3)
    x86::Float fpu13 = cpu.fpu.add(fpu2, fpu8);
    // 00425a67  dec3                   -faddp st(3)
    x86::Float fpu14 = cpu.fpu.add(fpu4, fpu10);
    // 00425a69  dec3                   -faddp st(3)
    x86::Float fpu15 = cpu.fpu.add(fpu6, fpu12);
    // 00425a6b  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu16 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 00425a6e  d84a18                 -fmul dword ptr [edx + 0x18]
    x86::Float fpu17 = cpu.fpu.mul(fpu16, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(24) /* 0x18 */)));
    // 00425a71  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu18 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 00425a74  d84a1c                 -fmul dword ptr [edx + 0x1c]
    x86::Float fpu19 = cpu.fpu.mul(fpu18, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(28) /* 0x1c */)));
    // 00425a77  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu20 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 00425a7a  d84a20                 -fmul dword ptr [edx + 0x20]
    x86::Float fpu21 = cpu.fpu.mul(fpu20, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(32) /* 0x20 */)));
    // 00425a7d  d9ca                   -fxch st(2)
    
    // 00425a7f  dec3                   -faddp st(3)
    x86::Float fpu22 = cpu.fpu.add(fpu13, fpu17);
    // 00425a81  dec3                   -faddp st(3)
    x86::Float fpu23 = cpu.fpu.add(fpu14, fpu19);
    // 00425a83  dec3                   -faddp st(3)
    x86::Float fpu24 = cpu.fpu.add(fpu15, fpu21);
    // 00425a85  8d400c                 -lea eax, [eax + 0xc]
    cpu.eax = x86::reg32(cpu.eax + x86::reg32(12) /* 0xc */);
    // 00425a88  d91b                   -fstp dword ptr [ebx]
    app->getMemory<float>(cpu.ebx) = float(fpu22);
    // 00425a8a  d95b04                 -fstp dword ptr [ebx + 4]
    app->getMemory<float>(cpu.ebx + x86::reg32(4) /* 0x4 */) = float(fpu23);
    // 00425a8d  d95b08                 -fstp dword ptr [ebx + 8]
    app->getMemory<float>(cpu.ebx + x86::reg32(8) /* 0x8 */) = float(fpu24);
    // 00425a90  8d5de8                 -lea ebx, [ebp - 0x18]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-24) /* -0x18 */);
    // 00425a93  8d55f4                 -lea edx, [ebp - 0xc]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 00425a96  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    }
    // 00425a9b  e810a50b00             -call 0x4dffb0
    cpu.esp -= 4;
    sub_4dffb0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00425aa0  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00425aa2  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00425aa3  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00425aa4  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00425aa5  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00425aa6  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00425aa7  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00425aa8  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x90 */
void Application::sub_425ab0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00425ab0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00425ab1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00425ab2  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00425ab3  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00425ab4  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00425ab6  83ec0c                 -sub esp, 0xc
    (cpu.esp) -= x86::reg32(x86::sreg32(12 /*0xc*/));
    // 00425ab9  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00425abb  8b4004                 -mov eax, dword ptr [eax + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 00425abe  8d90c0000000           -lea edx, [eax + 0xc0]
    cpu.edx = x86::reg32(cpu.eax + x86::reg32(192) /* 0xc0 */);
    // 00425ac4  8d5df4                 -lea ebx, [ebp - 0xc]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 00425ac7  8d8110010000           -lea eax, [ecx + 0x110]
    cpu.eax = x86::reg32(cpu.ecx + x86::reg32(272) /* 0x110 */);
    // 00425acd  d900                   -fld dword ptr [eax]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.eax));
    // 00425acf  d80a                   -fmul dword ptr [edx]
    x86::Float fpu2 = cpu.fpu.mul(fpu1, x86::Float(app->getMemory<float>(cpu.edx)));
    // 00425ad1  d900                   -fld dword ptr [eax]
    x86::Float fpu3 = x86::Float(app->getMemory<float>(cpu.eax));
    // 00425ad3  d84a04                 -fmul dword ptr [edx + 4]
    x86::Float fpu4 = cpu.fpu.mul(fpu3, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(4) /* 0x4 */)));
    // 00425ad6  d900                   -fld dword ptr [eax]
    x86::Float fpu5 = x86::Float(app->getMemory<float>(cpu.eax));
    // 00425ad8  d84a08                 -fmul dword ptr [edx + 8]
    x86::Float fpu6 = cpu.fpu.mul(fpu5, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(8) /* 0x8 */)));
    // 00425adb  d9ca                   -fxch st(2)
    
    // 00425add  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu7 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 00425ae0  d84a0c                 -fmul dword ptr [edx + 0xc]
    x86::Float fpu8 = cpu.fpu.mul(fpu7, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(12) /* 0xc */)));
    // 00425ae3  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu9 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 00425ae6  d84a10                 -fmul dword ptr [edx + 0x10]
    x86::Float fpu10 = cpu.fpu.mul(fpu9, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(16) /* 0x10 */)));
    // 00425ae9  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu11 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 00425aec  d84a14                 -fmul dword ptr [edx + 0x14]
    x86::Float fpu12 = cpu.fpu.mul(fpu11, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(20) /* 0x14 */)));
    // 00425aef  d9ca                   -fxch st(2)
    
    // 00425af1  dec3                   -faddp st(3)
    x86::Float fpu13 = cpu.fpu.add(fpu2, fpu8);
    // 00425af3  dec3                   -faddp st(3)
    x86::Float fpu14 = cpu.fpu.add(fpu4, fpu10);
    // 00425af5  dec3                   -faddp st(3)
    x86::Float fpu15 = cpu.fpu.add(fpu6, fpu12);
    // 00425af7  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu16 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 00425afa  d84a18                 -fmul dword ptr [edx + 0x18]
    x86::Float fpu17 = cpu.fpu.mul(fpu16, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(24) /* 0x18 */)));
    // 00425afd  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu18 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 00425b00  d84a1c                 -fmul dword ptr [edx + 0x1c]
    x86::Float fpu19 = cpu.fpu.mul(fpu18, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(28) /* 0x1c */)));
    // 00425b03  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu20 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 00425b06  d84a20                 -fmul dword ptr [edx + 0x20]
    x86::Float fpu21 = cpu.fpu.mul(fpu20, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(32) /* 0x20 */)));
    // 00425b09  d9ca                   -fxch st(2)
    
    // 00425b0b  dec3                   -faddp st(3)
    x86::Float fpu22 = cpu.fpu.add(fpu13, fpu17);
    // 00425b0d  dec3                   -faddp st(3)
    x86::Float fpu23 = cpu.fpu.add(fpu14, fpu19);
    // 00425b0f  dec3                   -faddp st(3)
    x86::Float fpu24 = cpu.fpu.add(fpu15, fpu21);
    // 00425b11  8d400c                 -lea eax, [eax + 0xc]
    cpu.eax = x86::reg32(cpu.eax + x86::reg32(12) /* 0xc */);
    // 00425b14  d91b                   -fstp dword ptr [ebx]
    app->getMemory<float>(cpu.ebx) = float(fpu22);
    // 00425b16  d95b04                 -fstp dword ptr [ebx + 4]
    app->getMemory<float>(cpu.ebx + x86::reg32(4) /* 0x4 */) = float(fpu23);
    // 00425b19  d95b08                 -fstp dword ptr [ebx + 8]
    app->getMemory<float>(cpu.ebx + x86::reg32(8) /* 0x8 */) = float(fpu24);
    // 00425b1c  8d5df4                 -lea ebx, [ebp - 0xc]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 00425b1f  8b5104                 -mov edx, dword ptr [ecx + 4]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(4) /* 0x4 */);
    // 00425b22  8d4114                 -lea eax, [ecx + 0x14]
    cpu.eax = x86::reg32(cpu.ecx + x86::reg32(20) /* 0x14 */);
    // 00425b25  81c298000000           -add edx, 0x98
    (cpu.edx) += x86::reg32(x86::sreg32(152 /*0x98*/));
    // 00425b2b  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00425b2d  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    }
    // 00425b32  e879a40b00             -call 0x4dffb0
    cpu.esp -= 4;
    sub_4dffb0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00425b37  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00425b39  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00425b3a  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00425b3b  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00425b3c  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00425b3d  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8b 0xc0 */
void Application::sub_425b40(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00425b40  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00425b41  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00425b42  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00425b43  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00425b44  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00425b45  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00425b47  81ec04010000           -sub esp, 0x104
    (cpu.esp) -= x86::reg32(x86::sreg32(260 /*0x104*/));
    // 00425b4d  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 00425b4f  89d1                   -mov ecx, edx
    cpu.ecx = cpu.edx;
    // 00425b51  89d6                   -mov esi, edx
    cpu.esi = cpu.edx;
    // 00425b53  8d7b14                 -lea edi, [ebx + 0x14]
    cpu.edi = x86::reg32(cpu.ebx + x86::reg32(20) /* 0x14 */);
    // 00425b56  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00425b57  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00425b58  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00425b59  8b4008                 -mov eax, dword ptr [eax + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 00425b5c  0598000000             +add eax, 0x98
    {
        x86::reg32& tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(152 /*0x98*/));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 00425b61  e84a0a0700             -call 0x4965b0
    cpu.esp -= 4;
    sub_4965b0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00425b66  d9ee                   +fldz 
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = 0.0;
    // 00425b68  ded9                   +fcompp 
    x86::Float fpu2 = cpu.fpu.st(0);
    cpu.fpu.compare(fpu1, fpu2);
    // 00425b6a  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00425b6c  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    cpu.fpu.count -= 1;
    }
    // 00425b6d  7613                   -jbe 0x425b82
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x00425b82;
    }
    // 00425b6f  8b4308                 -mov eax, dword ptr [ebx + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(8) /* 0x8 */);
    // 00425b72  89ca                   -mov edx, ecx
    cpu.edx = cpu.ecx;
    // 00425b74  0598000000             +add eax, 0x98
    {
        x86::reg32& tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(152 /*0x98*/));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 00425b79  e8320a0700             -call 0x4965b0
    cpu.esp -= 4;
    sub_4965b0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00425b7e  d9e0                   +fchs 
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu3 = cpu.fpu.st(0);
    x86::Float fpu4 = -fpu3;
    cpu.fpu.st(0) = fpu4;
    }
    // 00425b80  eb0f                   -jmp 0x425b91
    goto L_0x00425b91;
L_0x00425b82:
    // 00425b82  8b4308                 -mov eax, dword ptr [ebx + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(8) /* 0x8 */);
    // 00425b85  89ca                   -mov edx, ecx
    cpu.edx = cpu.ecx;
    // 00425b87  0598000000             -add eax, 0x98
    (cpu.eax) += x86::reg32(x86::sreg32(152 /*0x98*/));
    // 00425b8c  e81f0a0700             -call 0x4965b0
    cpu.esp -= 4;
    sub_4965b0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00425b91:
    // 00425b91  d95dfc                 -fstp dword ptr [ebp - 4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu5 = cpu.fpu.st(0);
    app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = float(fpu5);
    // 00425b94  d945fc                 -fld dword ptr [ebp - 4]
    x86::Float fpu6 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */));
    // 00425b97  8b1528305500           -mov edx, dword ptr [0x553028]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5582888) /* 0x553028 */);
    // 00425b9d  d84d1c                 -fmul dword ptr [ebp + 0x1c]
    x86::Float fpu7 = cpu.fpu.mul(fpu6, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(28) /* 0x1c */)));
    // 00425ba0  42                     -inc edx
    (cpu.edx)++;
    // 00425ba1  d84518                 -fadd dword ptr [ebp + 0x18]
    x86::Float fpu8 = cpu.fpu.add(fpu7, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(24) /* 0x18 */)));
    // 00425ba4  891528305500           -mov dword ptr [0x553028], edx
    app->getMemory<x86::reg32>(x86::reg32(5582888) /* 0x553028 */) = cpu.edx;
    // 00425baa  d95b54                 -fstp dword ptr [ebx + 0x54]
    app->getMemory<float>(cpu.ebx + x86::reg32(84) /* 0x54 */) = float(fpu8);
    // 00425bad  83fa05                 +cmp edx, 5
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(5 /*0x5*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    cpu.fpu.count -= 1;
    }
    // 00425bb0  752e                   -jne 0x425be0
    if (!cpu.flags.zf)
    {
        goto L_0x00425be0;
    }
    // 00425bb2  83ec08                 -sub esp, 8
    (cpu.esp) -= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 00425bb5  d94354                 -fld dword ptr [ebx + 0x54]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu9 = x86::Float(app->getMemory<float>(cpu.ebx + x86::reg32(84) /* 0x54 */));
    // 00425bb8  dd1c24                 -fstp qword ptr [esp]
    app->getMemory<double>(cpu.esp) = double(fpu9);
    // 00425bbb  83ec08                 -sub esp, 8
    (cpu.esp) -= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 00425bbe  d945fc                 -fld dword ptr [ebp - 4]
    x86::Float fpu10 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */));
    // 00425bc1  dd1c24                 -fstp qword ptr [esp]
    app->getMemory<double>(cpu.esp) = double(fpu10);
    // 00425bc4  68246f5300             -push 0x536f24
    app->getMemory<x86::reg32>(cpu.esp-4) = 5467940 /*0x536f24*/;
    cpu.esp -= 4;
    // 00425bc9  8d85fcfeffff           -lea eax, [ebp - 0x104]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-260) /* -0x104 */);
    // 00425bcf  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00425bd0  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
    }
    // 00425bd2  e8b99a0b00             -call 0x4df690
    cpu.esp -= 4;
    nfs3hp::watcom::sprintf(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00425bd7  83c418                 -add esp, 0x18
    (cpu.esp) += x86::reg32(x86::sreg32(24 /*0x18*/));
    // 00425bda  891d28305500           -mov dword ptr [0x553028], ebx
    app->getMemory<x86::reg32>(x86::reg32(5582888) /* 0x553028 */) = cpu.ebx;
L_0x00425be0:
    // 00425be0  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00425be2  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00425be3  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00425be4  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00425be5  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00425be6  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00425be7  c20800                 -ret 8
    cpu.esp += 4+8 /*0x8*/;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 */
void Application::sub_425bf0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00425bf0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00425bf1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00425bf2  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00425bf3  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00425bf4  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00425bf5  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00425bf6  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00425bf8  83ec1c                 -sub esp, 0x1c
    (cpu.esp) -= x86::reg32(x86::sreg32(28 /*0x1c*/));
    // 00425bfb  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00425bfd  8b15a8367d00           -mov edx, dword ptr [0x7d36a8]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205992) /* 0x7d36a8 */);
    // 00425c03  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 00425c05  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 00425c07  740d                   -je 0x425c16
    if (cpu.flags.zf)
    {
        goto L_0x00425c16;
    }
    // 00425c09  833d60d97c0000         +cmp dword ptr [0x7cd960], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(8182112) /* 0x7cd960 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00425c10  0f842f010000           -je 0x425d45
    if (cpu.flags.zf)
    {
        goto L_0x00425d45;
    }
L_0x00425c16:
    // 00425c16  833dec00560000         +cmp dword ptr [0x5600ec], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5636332) /* 0x5600ec */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00425c1d  0f8522010000           -jne 0x425d45
    if (!cpu.flags.zf)
    {
        goto L_0x00425d45;
    }
    // 00425c23  8b4104                 -mov eax, dword ptr [ecx + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(4) /* 0x4 */);
    // 00425c26  8d780c                 -lea edi, [eax + 0xc]
    cpu.edi = x86::reg32(cpu.eax + x86::reg32(12) /* 0xc */);
    // 00425c29  8b410c                 -mov eax, dword ptr [ecx + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(12) /* 0xc */);
    // 00425c2c  e83f800900             -call 0x4bdc70
    cpu.esp -= 4;
    sub_4bdc70(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00425c31  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00425c33  746c                   -je 0x425ca1
    if (cpu.flags.zf)
    {
        goto L_0x00425ca1;
    }
    // 00425c35  8b9184000000           -mov edx, dword ptr [ecx + 0x84]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(132) /* 0x84 */);
    // 00425c3b  8d04d500000000         -lea eax, [edx*8]
    cpu.eax = x86::reg32(cpu.edx * 8);
    // 00425c42  01c2                   -add edx, eax
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.eax));
    // 00425c44  a148d95d00             -mov eax, dword ptr [0x5dd948]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(6150472) /* 0x5dd948 */);
    // 00425c49  c1e202                 -shl edx, 2
    cpu.edx <<= 2 /*0x2*/ % 32;
    // 00425c4c  668b44020c             -mov ax, word ptr [edx + eax + 0xc]
    cpu.ax = app->getMemory<x86::reg16>(cpu.edx + x86::reg32(12) /* 0xc */ + cpu.eax * 1);
    // 00425c51  25ffff0000             -and eax, 0xffff
    cpu.eax &= x86::reg32(x86::sreg32(65535 /*0xffff*/));
    // 00425c56  e885e3ffff             -call 0x423fe0
    cpu.esp -= 4;
    sub_423fe0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00425c5b  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00425c5d  7527                   -jne 0x425c86
    if (!cpu.flags.zf)
    {
        goto L_0x00425c86;
    }
    // 00425c5f  8b5710                 -mov edx, dword ptr [edi + 0x10]
    cpu.edx = app->getMemory<x86::reg32>(cpu.edi + x86::reg32(16) /* 0x10 */);
    // 00425c62  8d04d500000000         -lea eax, [edx*8]
    cpu.eax = x86::reg32(cpu.edx * 8);
    // 00425c69  01c2                   -add edx, eax
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.eax));
    // 00425c6b  a148d95d00             -mov eax, dword ptr [0x5dd948]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(6150472) /* 0x5dd948 */);
    // 00425c70  c1e202                 -shl edx, 2
    cpu.edx <<= 2 /*0x2*/ % 32;
    // 00425c73  668b44020c             -mov ax, word ptr [edx + eax + 0xc]
    cpu.ax = app->getMemory<x86::reg16>(cpu.edx + x86::reg32(12) /* 0xc */ + cpu.eax * 1);
    // 00425c78  25ffff0000             -and eax, 0xffff
    cpu.eax &= x86::reg32(x86::sreg32(65535 /*0xffff*/));
    // 00425c7d  e85ee3ffff             -call 0x423fe0
    cpu.esp -= 4;
    sub_423fe0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00425c82  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00425c84  741b                   -je 0x425ca1
    if (cpu.flags.zf)
    {
        goto L_0x00425ca1;
    }
L_0x00425c86:
    // 00425c86  8b4104                 -mov eax, dword ptr [ecx + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(4) /* 0x4 */);
    // 00425c89  83b83806000007         +cmp dword ptr [eax + 0x638], 7
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(1592) /* 0x638 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(7 /*0x7*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00425c90  7c07                   -jl 0x425c99
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x00425c99;
    }
    // 00425c92  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 00425c97  eb02                   -jmp 0x425c9b
    goto L_0x00425c9b;
L_0x00425c99:
    // 00425c99  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
L_0x00425c9b:
    // 00425c9b  89861c010000           -mov dword ptr [esi + 0x11c], eax
    app->getMemory<x86::reg32>(cpu.esi + x86::reg32(284) /* 0x11c */) = cpu.eax;
L_0x00425ca1:
    // 00425ca1  8d55e4                 -lea edx, [ebp - 0x1c]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-28) /* -0x1c */);
    // 00425ca4  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 00425ca6  8b9e1c010000           -mov ebx, dword ptr [esi + 0x11c]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(284) /* 0x11c */);
    // 00425cac  e81fa3ffff             -call 0x41ffd0
    cpu.esp -= 4;
    nfs3hp::trackdata::lanePosition(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00425cb1  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 00425cb3  8b45e4                 -mov eax, dword ptr [ebp - 0x1c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-28) /* -0x1c */);
    // 00425cb6  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 00425cb9  db45fc                 +fild dword ptr [ebp - 4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 00425cbc  8b45e8                 -mov eax, dword ptr [ebp - 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-24) /* -0x18 */);
    // 00425cbf  dd052c6f5300           +fld qword ptr [0x536f2c]
    x86::Float fpu2 = x86::Float(app->getMemory<double>(x86::reg32(5467948) /* 0x536f2c */));
    // 00425cc5  d9c9                   +fxch st(1)
    
    // 00425cc7  d8c9                   +fmul st(1)
    x86::Float fpu3 = cpu.fpu.mul(fpu1, x86::Float(fpu2));
    // 00425cc9  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 00425ccc  8b45ec                 -mov eax, dword ptr [ebp - 0x14]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */);
    // 00425ccf  db45fc                 +fild dword ptr [ebp - 4]
    x86::Float fpu4 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 00425cd2  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 00425cd5  d8ca                   +fmul st(2)
    x86::Float fpu5 = cpu.fpu.mul(fpu4, x86::Float(fpu2));
    // 00425cd7  db45fc                 +fild dword ptr [ebp - 4]
    x86::Float fpu6 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 00425cda  decb                   +fmulp st(3)
    x86::Float fpu7 = cpu.fpu.mul(fpu2, fpu6);
    // 00425cdc  d9c9                   +fxch st(1)
    
    // 00425cde  d95df0                 +fstp dword ptr [ebp - 0x10]
    app->getMemory<float>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = float(fpu3);
    // 00425ce1  d805346f5300           +fadd dword ptr [0x536f34]
    x86::Float fpu8 = cpu.fpu.add(fpu5, x86::Float(app->getMemory<float>(x86::reg32(5467956) /* 0x536f34 */)));
    // 00425ce7  d9c9                   +fxch st(1)
    
    // 00425ce9  d95df8                 +fstp dword ptr [ebp - 8]
    app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = float(fpu7);
    // 00425cec  d95df4                 +fstp dword ptr [ebp - 0xc]
    app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */) = float(fpu8);
    // 00425cef  d94114                 +fld dword ptr [ecx + 0x14]
    x86::Float fpu9 = x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(20) /* 0x14 */));
    // 00425cf2  d85df0                 +fcomp dword ptr [ebp - 0x10]
    cpu.fpu.compare(fpu9, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-16) /* -0x10 */)));
    // 00425cf5  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00425cf7  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 00425cf8  7516                   -jne 0x425d10
    if (!cpu.flags.zf)
    {
        goto L_0x00425d10;
    }
    // 00425cfa  d94118                 +fld dword ptr [ecx + 0x18]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu10 = x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(24) /* 0x18 */));
    // 00425cfd  d85df4                 +fcomp dword ptr [ebp - 0xc]
    cpu.fpu.compare(fpu10, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */)));
    // 00425d00  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00425d02  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 00425d03  750b                   -jne 0x425d10
    if (!cpu.flags.zf)
    {
        goto L_0x00425d10;
    }
    // 00425d05  d9411c                 +fld dword ptr [ecx + 0x1c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu11 = x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(28) /* 0x1c */));
    // 00425d08  d85df8                 +fcomp dword ptr [ebp - 8]
    cpu.fpu.compare(fpu11, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    // 00425d0b  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00425d0d  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 00425d0e  7408                   -je 0x425d18
    if (cpu.flags.zf)
    {
        goto L_0x00425d18;
    }
L_0x00425d10:
    // 00425d10  8b410c                 -mov eax, dword ptr [ecx + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(12) /* 0xc */);
    // 00425d13  e8b87e0900             -call 0x4bdbd0
    cpu.esp -= 4;
    sub_4bdbd0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00425d18:
    // 00425d18  ffb614010000           -push dword ptr [esi + 0x114]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(276) /* 0x114 */);
    cpu.esp -= 4;
    // 00425d1e  8d55f0                 -lea edx, [ebp - 0x10]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 00425d21  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00425d23  ffb610010000           -push dword ptr [esi + 0x110]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(272) /* 0x110 */);
    cpu.esp -= 4;
    // 00425d29  e812feffff             -call 0x425b40
    cpu.esp -= 4;
    sub_425b40(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00425d2e  8d5114                 -lea edx, [ecx + 0x14]
    cpu.edx = x86::reg32(cpu.ecx + x86::reg32(20) /* 0x14 */);
    // 00425d31  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00425d33  8999ec000000           -mov dword ptr [ecx + 0xec], ebx
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(236) /* 0xec */) = cpu.ebx;
    // 00425d39  e852c5ffff             -call 0x422290
    cpu.esp -= 4;
    sub_422290(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00425d3e  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00425d40  e8ebf1ffff             -call 0x424f30
    cpu.esp -= 4;
    sub_424f30(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00425d45:
    // 00425d45  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00425d47  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00425d48  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00425d49  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00425d4a  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00425d4b  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00425d4c  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00425d4d  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8b 0xc0 */
void Application::sub_425d50(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00425d50  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00425d51  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00425d52  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00425d53  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00425d54  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00425d55  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00425d56  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00425d58  81ecb0000000           -sub esp, 0xb0
    (cpu.esp) -= x86::reg32(x86::sreg32(176 /*0xb0*/));
    // 00425d5e  81ed82000000           -sub ebp, 0x82
    (cpu.ebp) -= x86::reg32(x86::sreg32(130 /*0x82*/));
    // 00425d64  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 00425d66  b908000000             -mov ecx, 8
    cpu.ecx = 8 /*0x8*/;
    // 00425d6b  8d7dd2                 -lea edi, [ebp - 0x2e]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(-46) /* -0x2e */);
    // 00425d6e  be503d4200             -mov esi, 0x423d50
    cpu.esi = 4341072 /*0x423d50*/;
    // 00425d73  f3a5                   -rep movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00425d75  b908000000             -mov ecx, 8
    cpu.ecx = 8 /*0x8*/;
    // 00425d7a  8d7df2                 -lea edi, [ebp - 0xe]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(-14) /* -0xe */);
    // 00425d7d  be703d4200             -mov esi, 0x423d70
    cpu.esi = 4341104 /*0x423d70*/;
    // 00425d82  f3a5                   -rep movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00425d84  8b15a8367d00           -mov edx, dword ptr [0x7d36a8]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205992) /* 0x7d36a8 */);
    // 00425d8a  8b4804                 -mov ecx, dword ptr [eax + 4]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 00425d8d  31f6                   -xor esi, esi
    cpu.esi ^= x86::reg32(x86::sreg32(cpu.esi));
    // 00425d8f  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 00425d91  740d                   -je 0x425da0
    if (cpu.flags.zf)
    {
        goto L_0x00425da0;
    }
    // 00425d93  833d60d97c0000         +cmp dword ptr [0x7cd960], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(8182112) /* 0x7cd960 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00425d9a  0f84d9040000           -je 0x426279
    if (cpu.flags.zf)
    {
        goto L_0x00426279;
    }
L_0x00425da0:
    // 00425da0  833dec00560000         +cmp dword ptr [0x5600ec], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5636332) /* 0x5600ec */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00425da7  0f85cc040000           -jne 0x426279
    if (!cpu.flags.zf)
    {
        goto L_0x00426279;
    }
    // 00425dad  833d80367d0000         +cmp dword ptr [0x7d3680], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(8205952) /* 0x7d3680 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00425db4  740a                   -je 0x425dc0
    if (cpu.flags.zf)
    {
        goto L_0x00425dc0;
    }
    // 00425db6  8b430c                 -mov eax, dword ptr [ebx + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(12) /* 0xc */);
    // 00425db9  ff048504305500         -inc dword ptr [eax*4 + 0x553004]
    (app->getMemory<x86::reg32>(x86::reg32(5582852) /* 0x553004 */ + cpu.eax * 4))++;
L_0x00425dc0:
    // 00425dc0  8b430c                 -mov eax, dword ptr [ebx + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(12) /* 0xc */);
    // 00425dc3  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 00425dc6  8bb804305500           -mov edi, dword ptr [eax + 0x553004]
    cpu.edi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(5582852) /* 0x553004 */);
    // 00425dcc  8b9014305500           -mov edx, dword ptr [eax + 0x553014]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(5582868) /* 0x553014 */);
    // 00425dd2  3b7c95f2               +cmp edi, dword ptr [ebp + edx*4 - 0xe]
    {
        x86::reg32 tmp1 = cpu.edi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-14) /* -0xe */ + cpu.edx * 4)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00425dd6  0f859b010000           -jne 0x425f77
    if (!cpu.flags.zf)
    {
        goto L_0x00425f77;
    }
    // 00425ddc  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00425dde  899004305500           -mov dword ptr [eax + 0x553004], edx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(5582852) /* 0x553004 */) = cpu.edx;
    // 00425de4  8b430c                 -mov eax, dword ptr [ebx + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(12) /* 0xc */);
    // 00425de7  8b04850c305500         -mov eax, dword ptr [eax*4 + 0x55300c]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5582860) /* 0x55300c */ + cpu.eax * 4);
    // 00425dee  8b3d40d95d00           -mov edi, dword ptr [0x5dd940]
    cpu.edi = app->getMemory<x86::reg32>(x86::reg32(6150464) /* 0x5dd940 */);
    // 00425df4  40                     -inc eax
    (cpu.eax)++;
    // 00425df5  39f8                   +cmp eax, edi
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
    // 00425df7  7c02                   -jl 0x425dfb
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x00425dfb;
    }
    // 00425df9  29f8                   -sub eax, edi
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edi));
L_0x00425dfb:
    // 00425dfb  8b530c                 -mov edx, dword ptr [ebx + 0xc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(12) /* 0xc */);
    // 00425dfe  8904950c305500         -mov dword ptr [edx*4 + 0x55300c], eax
    app->getMemory<x86::reg32>(x86::reg32(5582860) /* 0x55300c */ + cpu.edx * 4) = cpu.eax;
    // 00425e05  8b81c0070000           -mov eax, dword ptr [ecx + 0x7c0]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(1984) /* 0x7c0 */);
    // 00425e0b  89455a                 -mov dword ptr [ebp + 0x5a], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(90) /* 0x5a */) = cpu.eax;
    // 00425e0e  8b430c                 -mov eax, dword ptr [ebx + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(12) /* 0xc */);
    // 00425e11  8b511c                 -mov edx, dword ptr [ecx + 0x1c]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(28) /* 0x1c */);
    // 00425e14  8b3c850c305500         -mov edi, dword ptr [eax*4 + 0x55300c]
    cpu.edi = app->getMemory<x86::reg32>(x86::reg32(5582860) /* 0x55300c */ + cpu.eax * 4);
    // 00425e1b  8b048514305500         -mov eax, dword ptr [eax*4 + 0x553014]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5582868) /* 0x553014 */ + cpu.eax * 4);
    // 00425e22  d9455a                 -fld dword ptr [ebp + 0x5a]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(90) /* 0x5a */));
    // 00425e25  d86485d2               -fsub dword ptr [ebp + eax*4 - 0x2e]
    x86::Float fpu2 = cpu.fpu.sub(fpu1, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-46) /* -0x2e */ + cpu.eax * 4)));
    // 00425e29  29fa                   -sub edx, edi
    (cpu.edx) -= x86::reg32(x86::sreg32(cpu.edi));
    // 00425e2b  d95d72                 -fstp dword ptr [ebp + 0x72]
    app->getMemory<float>(cpu.ebp + x86::reg32(114) /* 0x72 */) = float(fpu2);
    // 00425e2e  83fa07                 +cmp edx, 7
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(7 /*0x7*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    }
    // 00425e31  7f1d                   -jg 0x425e50
    if (!cpu.flags.zf && (cpu.flags.sf == cpu.flags.of))
    {
        goto L_0x00425e50;
    }
    // 00425e33  83fa04                 +cmp edx, 4
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
    // 00425e36  7e1f                   -jle 0x425e57
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00425e57;
    }
    // 00425e38  d94572                 +fld dword ptr [ebp + 0x72]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu3 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(114) /* 0x72 */));
    // 00425e3b  d81d386f5300           +fcomp dword ptr [0x536f38]
    cpu.fpu.compare(fpu3, x86::Float(app->getMemory<float>(x86::reg32(5467960) /* 0x536f38 */)));
    // 00425e41  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00425e43  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 00425e44  7311                   -jae 0x425e57
    if (!cpu.flags.cf)
    {
        goto L_0x00425e57;
    }
    // 00425e46  d9ee                   +fldz 
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu4 = 0.0;
    // 00425e48  d85d72                 +fcomp dword ptr [ebp + 0x72]
    cpu.fpu.compare(fpu4, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(114) /* 0x72 */)));
    // 00425e4b  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00425e4d  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 00425e4e  7307                   -jae 0x425e57
    if (!cpu.flags.cf)
    {
        goto L_0x00425e57;
    }
L_0x00425e50:
    // 00425e50  be01000000             -mov esi, 1
    cpu.esi = 1 /*0x1*/;
    // 00425e55  eb27                   -jmp 0x425e7e
    goto L_0x00425e7e;
L_0x00425e57:
    // 00425e57  83fafa                 +cmp edx, -6
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(-6 /*-0x6*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00425e5a  7c1d                   -jl 0x425e79
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x00425e79;
    }
    // 00425e5c  83fafc                 +cmp edx, -4
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(-4 /*-0x4*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00425e5f  7d1d                   -jge 0x425e7e
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00425e7e;
    }
    // 00425e61  d94572                 +fld dword ptr [ebp + 0x72]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu5 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(114) /* 0x72 */));
    // 00425e64  dc1d3c6f5300           +fcomp qword ptr [0x536f3c]
    cpu.fpu.compare(fpu5, x86::Float(app->getMemory<double>(x86::reg32(5467964) /* 0x536f3c */)));
    // 00425e6a  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00425e6c  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 00425e6d  760f                   -jbe 0x425e7e
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x00425e7e;
    }
    // 00425e6f  d9ee                   +fldz 
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu6 = 0.0;
    // 00425e71  d85d72                 +fcomp dword ptr [ebp + 0x72]
    cpu.fpu.compare(fpu6, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(114) /* 0x72 */)));
    // 00425e74  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00425e76  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 00425e77  7605                   -jbe 0x425e7e
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x00425e7e;
    }
L_0x00425e79:
    // 00425e79  be02000000             -mov esi, 2
    cpu.esi = 2 /*0x2*/;
L_0x00425e7e:
    // 00425e7e  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 00425e80  0f84f1000000           -je 0x425f77
    if (cpu.flags.zf)
    {
        goto L_0x00425f77;
    }
    // 00425e86  31d2                   +xor edx, edx
    cpu.clear_co();
    cpu.set_szp((cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx))));
L_0x00425e88:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00425e88  d9455a                 +fld dword ptr [ebp + 0x5a]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu7 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(90) /* 0x5a */));
    // 00425e8b  d85c95d2               +fcomp dword ptr [ebp + edx*4 - 0x2e]
    cpu.fpu.compare(fpu7, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-46) /* -0x2e */ + cpu.edx * 4)));
    // 00425e8f  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00425e91  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 00425e92  7603                   -jbe 0x425e97
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x00425e97;
    }
    // 00425e94  42                     +inc edx
    {
        x86::reg32& tmp = cpu.edx;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 00425e95  ebf1                   -jmp 0x425e88
    goto L_0x00425e88;
L_0x00425e97:
    // 00425e97  8b430c                 -mov eax, dword ptr [ebx + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(12) /* 0xc */);
    // 00425e9a  89148514305500         -mov dword ptr [eax*4 + 0x553014], edx
    app->getMemory<x86::reg32>(x86::reg32(5582868) /* 0x553014 */ + cpu.eax * 4) = cpu.edx;
    // 00425ea1  8b430c                 -mov eax, dword ptr [ebx + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(12) /* 0xc */);
    // 00425ea4  8b048514305500         -mov eax, dword ptr [eax*4 + 0x553014]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5582868) /* 0x553014 */ + cpu.eax * 4);
    // 00425eab  d9455a                 -fld dword ptr [ebp + 0x5a]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu8 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(90) /* 0x5a */));
    // 00425eae  d86485d2               -fsub dword ptr [ebp + eax*4 - 0x2e]
    x86::Float fpu9 = cpu.fpu.sub(fpu8, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-46) /* -0x2e */ + cpu.eax * 4)));
    // 00425eb2  8b430c                 -mov eax, dword ptr [ebx + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(12) /* 0xc */);
    // 00425eb5  d95d62                 -fstp dword ptr [ebp + 0x62]
    app->getMemory<float>(cpu.ebp + x86::reg32(98) /* 0x62 */) = float(fpu9);
    }
    // 00425eb8  e8b37d0900             -call 0x4bdc70
    cpu.esp -= 4;
    sub_4bdc70(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00425ebd  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00425ebf  0f84b2000000           -je 0x425f77
    if (cpu.flags.zf)
    {
        goto L_0x00425f77;
    }
    // 00425ec5  83fe01                 +cmp esi, 1
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
    // 00425ec8  0f8562000000           -jne 0x425f30
    if (!cpu.flags.zf)
    {
        goto L_0x00425f30;
    }
    // 00425ece  d94562                 +fld dword ptr [ebp + 0x62]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu10 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(98) /* 0x62 */));
    // 00425ed1  d81d446f5300           +fcomp dword ptr [0x536f44]
    cpu.fpu.compare(fpu10, x86::Float(app->getMemory<float>(x86::reg32(5467972) /* 0x536f44 */)));
    // 00425ed7  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00425ed9  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 00425eda  7314                   -jae 0x425ef0
    if (!cpu.flags.cf)
    {
        goto L_0x00425ef0;
    }
    // 00425edc  8b411c                 -mov eax, dword ptr [ecx + 0x1c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(28) /* 0x1c */);
    // 00425edf  8b1540d95d00           -mov edx, dword ptr [0x5dd940]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(6150464) /* 0x5dd940 */);
    // 00425ee5  83c003                 -add eax, 3
    (cpu.eax) += x86::reg32(x86::sreg32(3 /*0x3*/));
    // 00425ee8  39d0                   +cmp eax, edx
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
    // 00425eea  7c38                   -jl 0x425f24
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x00425f24;
    }
    // 00425eec  29d0                   +sub eax, edx
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
    // 00425eee  eb34                   -jmp 0x425f24
    goto L_0x00425f24;
L_0x00425ef0:
    // 00425ef0  d94562                 +fld dword ptr [ebp + 0x62]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu11 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(98) /* 0x62 */));
    // 00425ef3  d81d486f5300           +fcomp dword ptr [0x536f48]
    cpu.fpu.compare(fpu11, x86::Float(app->getMemory<float>(x86::reg32(5467976) /* 0x536f48 */)));
    // 00425ef9  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00425efb  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 00425efc  7314                   -jae 0x425f12
    if (!cpu.flags.cf)
    {
        goto L_0x00425f12;
    }
    // 00425efe  8b411c                 -mov eax, dword ptr [ecx + 0x1c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(28) /* 0x1c */);
    // 00425f01  8b1540d95d00           -mov edx, dword ptr [0x5dd940]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(6150464) /* 0x5dd940 */);
    // 00425f07  83c005                 -add eax, 5
    (cpu.eax) += x86::reg32(x86::sreg32(5 /*0x5*/));
    // 00425f0a  39d0                   +cmp eax, edx
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
    // 00425f0c  7c16                   -jl 0x425f24
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x00425f24;
    }
    // 00425f0e  29d0                   +sub eax, edx
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
    // 00425f10  eb12                   -jmp 0x425f24
    goto L_0x00425f24;
L_0x00425f12:
    // 00425f12  8b411c                 -mov eax, dword ptr [ecx + 0x1c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(28) /* 0x1c */);
    // 00425f15  8b1540d95d00           -mov edx, dword ptr [0x5dd940]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(6150464) /* 0x5dd940 */);
    // 00425f1b  83c007                 -add eax, 7
    (cpu.eax) += x86::reg32(x86::sreg32(7 /*0x7*/));
    // 00425f1e  39d0                   +cmp eax, edx
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
    // 00425f20  7c02                   -jl 0x425f24
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x00425f24;
    }
    // 00425f22  29d0                   +sub eax, edx
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
L_0x00425f24:
    // 00425f24  8b530c                 -mov edx, dword ptr [ebx + 0xc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(12) /* 0xc */);
    // 00425f27  8904950c305500         -mov dword ptr [edx*4 + 0x55300c], eax
    app->getMemory<x86::reg32>(x86::reg32(5582860) /* 0x55300c */ + cpu.edx * 4) = cpu.eax;
    // 00425f2e  eb3a                   -jmp 0x425f6a
    goto L_0x00425f6a;
L_0x00425f30:
    // 00425f30  d94562                 +fld dword ptr [ebp + 0x62]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu12 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(98) /* 0x62 */));
    // 00425f33  dc1d4c6f5300           +fcomp qword ptr [0x536f4c]
    cpu.fpu.compare(fpu12, x86::Float(app->getMemory<double>(x86::reg32(5467980) /* 0x536f4c */)));
    // 00425f39  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00425f3b  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 00425f3c  7612                   -jbe 0x425f50
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x00425f50;
    }
    // 00425f3e  8b411c                 -mov eax, dword ptr [ecx + 0x1c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(28) /* 0x1c */);
    // 00425f41  83e803                 -sub eax, 3
    (cpu.eax) -= x86::reg32(x86::sreg32(3 /*0x3*/));
    // 00425f44  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00425f46  7d18                   -jge 0x425f60
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00425f60;
    }
    // 00425f48  030540d95d00           +add eax, dword ptr [0x5dd940]
    {
        x86::reg32& tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(6150464) /* 0x5dd940 */)));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 00425f4e  eb10                   -jmp 0x425f60
    goto L_0x00425f60;
L_0x00425f50:
    // 00425f50  8b411c                 -mov eax, dword ptr [ecx + 0x1c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(28) /* 0x1c */);
    // 00425f53  83e805                 -sub eax, 5
    (cpu.eax) -= x86::reg32(x86::sreg32(5 /*0x5*/));
    // 00425f56  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00425f58  7d06                   -jge 0x425f60
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00425f60;
    }
    // 00425f5a  030540d95d00           -add eax, dword ptr [0x5dd940]
    (cpu.eax) += x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(6150464) /* 0x5dd940 */)));
L_0x00425f60:
    // 00425f60  8b530c                 -mov edx, dword ptr [ebx + 0xc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(12) /* 0xc */);
    // 00425f63  8904950c305500         -mov dword ptr [edx*4 + 0x55300c], eax
    app->getMemory<x86::reg32>(x86::reg32(5582860) /* 0x55300c */ + cpu.edx * 4) = cpu.eax;
L_0x00425f6a:
    // 00425f6a  ba09000000             -mov edx, 9
    cpu.edx = 9 /*0x9*/;
    // 00425f6f  8b430c                 -mov eax, dword ptr [ebx + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(12) /* 0xc */);
    // 00425f72  e8497d0900             -call 0x4bdcc0
    cpu.esp -= 4;
    sub_4bdcc0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00425f77:
    // 00425f77  8b430c                 -mov eax, dword ptr [ebx + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(12) /* 0xc */);
    // 00425f7a  e8f17c0900             -call 0x4bdc70
    cpu.esp -= 4;
    sub_4bdc70(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00425f7f  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00425f81  745e                   -je 0x425fe1
    if (cpu.flags.zf)
    {
        goto L_0x00425fe1;
    }
    // 00425f83  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 00425f85  754d                   -jne 0x425fd4
    if (!cpu.flags.zf)
    {
        goto L_0x00425fd4;
    }
    // 00425f87  8b9384000000           -mov edx, dword ptr [ebx + 0x84]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(132) /* 0x84 */);
    // 00425f8d  8d04d500000000         -lea eax, [edx*8]
    cpu.eax = x86::reg32(cpu.edx * 8);
    // 00425f94  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 00425f96  8b1548d95d00           -mov edx, dword ptr [0x5dd948]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(6150472) /* 0x5dd948 */);
    // 00425f9c  668b44820c             -mov ax, word ptr [edx + eax*4 + 0xc]
    cpu.ax = app->getMemory<x86::reg16>(cpu.edx + x86::reg32(12) /* 0xc */ + cpu.eax * 4);
    // 00425fa1  25ffff0000             -and eax, 0xffff
    cpu.eax &= x86::reg32(x86::sreg32(65535 /*0xffff*/));
    // 00425fa6  e835e0ffff             -call 0x423fe0
    cpu.esp -= 4;
    sub_423fe0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00425fab  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00425fad  7525                   -jne 0x425fd4
    if (!cpu.flags.zf)
    {
        goto L_0x00425fd4;
    }
    // 00425faf  8b511c                 -mov edx, dword ptr [ecx + 0x1c]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(28) /* 0x1c */);
    // 00425fb2  8d04d500000000         -lea eax, [edx*8]
    cpu.eax = x86::reg32(cpu.edx * 8);
    // 00425fb9  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 00425fbb  8b1548d95d00           -mov edx, dword ptr [0x5dd948]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(6150472) /* 0x5dd948 */);
    // 00425fc1  668b44820c             -mov ax, word ptr [edx + eax*4 + 0xc]
    cpu.ax = app->getMemory<x86::reg16>(cpu.edx + x86::reg32(12) /* 0xc */ + cpu.eax * 4);
    // 00425fc6  25ffff0000             -and eax, 0xffff
    cpu.eax &= x86::reg32(x86::sreg32(65535 /*0xffff*/));
    // 00425fcb  e810e0ffff             -call 0x423fe0
    cpu.esp -= 4;
    sub_423fe0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00425fd0  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00425fd2  740d                   -je 0x425fe1
    if (cpu.flags.zf)
    {
        goto L_0x00425fe1;
    }
L_0x00425fd4:
    // 00425fd4  8b430c                 -mov eax, dword ptr [ebx + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(12) /* 0xc */);
    // 00425fd7  e8f47b0900             -call 0x4bdbd0
    cpu.esp -= 4;
    sub_4bdbd0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00425fdc  e998020000             -jmp 0x426279
    goto L_0x00426279;
L_0x00425fe1:
    // 00425fe1  8b430c                 -mov eax, dword ptr [ebx + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(12) /* 0xc */);
    // 00425fe4  8b04850c305500         -mov eax, dword ptr [eax*4 + 0x55300c]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5582860) /* 0x55300c */ + cpu.eax * 4);
    // 00425feb  8b1540d95d00           -mov edx, dword ptr [0x5dd940]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(6150464) /* 0x5dd940 */);
    // 00425ff1  40                     -inc eax
    (cpu.eax)++;
    // 00425ff2  39d0                   +cmp eax, edx
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
    // 00425ff4  7c02                   -jl 0x425ff8
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x00425ff8;
    }
    // 00425ff6  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
L_0x00425ff8:
    // 00425ff8  8b530c                 -mov edx, dword ptr [ebx + 0xc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(12) /* 0xc */);
    // 00425ffb  c1e202                 -shl edx, 2
    cpu.edx <<= 2 /*0x2*/ % 32;
    // 00425ffe  8b8a0c305500           -mov ecx, dword ptr [edx + 0x55300c]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(5582860) /* 0x55300c */);
    // 00426004  895526                 -mov dword ptr [ebp + 0x26], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(38) /* 0x26 */) = cpu.edx;
    // 00426007  8d14cd00000000         -lea edx, [ecx*8]
    cpu.edx = x86::reg32(cpu.ecx * 8);
    // 0042600e  01ca                   -add edx, ecx
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.ecx));
    // 00426010  8b3548d95d00           -mov esi, dword ptr [0x5dd948]
    cpu.esi = app->getMemory<x86::reg32>(x86::reg32(6150472) /* 0x5dd948 */);
    // 00426016  c1e202                 -shl edx, 2
    cpu.edx <<= 2 /*0x2*/ % 32;
    // 00426019  8d0c32                 -lea ecx, [edx + esi]
    cpu.ecx = x86::reg32(cpu.edx + cpu.esi * 1);
    // 0042601c  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 0042601e  c1e003                 -shl eax, 3
    cpu.eax <<= 3 /*0x3*/ % 32;
    // 00426021  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 00426023  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 00426026  01f0                   -add eax, esi
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.esi));
    // 00426028  89451e                 -mov dword ptr [ebp + 0x1e], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(30) /* 0x1e */) = cpu.eax;
    // 0042602b  8b10                   -mov edx, dword ptr [eax]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax);
    // 0042602d  8b4526                 -mov eax, dword ptr [ebp + 0x26]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(38) /* 0x26 */);
    // 00426030  8b8014305500           -mov eax, dword ptr [eax + 0x553014]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(5582868) /* 0x553014 */);
    // 00426036  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 00426039  8b39                   -mov edi, dword ptr [ecx]
    cpu.edi = app->getMemory<x86::reg32>(cpu.ecx);
    // 0042603b  894522                 -mov dword ptr [ebp + 0x22], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(34) /* 0x22 */) = cpu.eax;
    // 0042603e  29fa                   -sub edx, edi
    (cpu.edx) -= x86::reg32(x86::sreg32(cpu.edi));
    // 00426040  8b7d22                 -mov edi, dword ptr [ebp + 0x22]
    cpu.edi = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(34) /* 0x22 */);
    // 00426043  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 00426045  c1fa1f                 -sar edx, 0x1f
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (31 /*0x1f*/ % 32));
    // 00426048  f77c2ff2               -idiv dword ptr [edi + ebp - 0xe]
    {
        x86::sreg64 tmp = x86::sreg64(cpu.edx_eax);
        x86::sreg32 d = x86::sreg32(app->getMemory<x86::reg32>(cpu.edi + x86::reg32(-14) /* -0xe */ + cpu.ebp * 1));
        cpu.edx_eax = x86::reg64(tmp / d);
        cpu.edx = x86::reg32(tmp % d);
    }
    // 0042604c  89457e                 -mov dword ptr [ebp + 0x7e], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */) = cpu.eax;
    // 0042604f  8b451e                 -mov eax, dword ptr [ebp + 0x1e]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(30) /* 0x1e */);
    // 00426052  8b5004                 -mov edx, dword ptr [eax + 4]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 00426055  8b4104                 -mov eax, dword ptr [ecx + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(4) /* 0x4 */);
    // 00426058  29c2                   -sub edx, eax
    (cpu.edx) -= x86::reg32(x86::sreg32(cpu.eax));
    // 0042605a  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 0042605c  c1fa1f                 -sar edx, 0x1f
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (31 /*0x1f*/ % 32));
    // 0042605f  f77c2ff2               -idiv dword ptr [edi + ebp - 0xe]
    {
        x86::sreg64 tmp = x86::sreg64(cpu.edx_eax);
        x86::sreg32 d = x86::sreg32(app->getMemory<x86::reg32>(cpu.edi + x86::reg32(-14) /* -0xe */ + cpu.ebp * 1));
        cpu.edx_eax = x86::reg64(tmp / d);
        cpu.edx = x86::reg32(tmp % d);
    }
    // 00426063  89457a                 -mov dword ptr [ebp + 0x7a], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(122) /* 0x7a */) = cpu.eax;
    // 00426066  8b451e                 -mov eax, dword ptr [ebp + 0x1e]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(30) /* 0x1e */);
    // 00426069  8b7908                 -mov edi, dword ptr [ecx + 8]
    cpu.edi = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(8) /* 0x8 */);
    // 0042606c  8b5008                 -mov edx, dword ptr [eax + 8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 0042606f  29fa                   -sub edx, edi
    (cpu.edx) -= x86::reg32(x86::sreg32(cpu.edi));
    // 00426071  8b7d22                 -mov edi, dword ptr [ebp + 0x22]
    cpu.edi = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(34) /* 0x22 */);
    // 00426074  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 00426076  c1fa1f                 -sar edx, 0x1f
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (31 /*0x1f*/ % 32));
    // 00426079  f77c2ff2               -idiv dword ptr [edi + ebp - 0xe]
    {
        x86::sreg64 tmp = x86::sreg64(cpu.edx_eax);
        x86::sreg32 d = x86::sreg32(app->getMemory<x86::reg32>(cpu.edi + x86::reg32(-14) /* -0xe */ + cpu.ebp * 1));
        cpu.edx_eax = x86::reg64(tmp / d);
        cpu.edx = x86::reg32(tmp % d);
    }
    // 0042607d  dd05546f5300           -fld qword ptr [0x536f54]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu13 = x86::Float(app->getMemory<double>(x86::reg32(5467988) /* 0x536f54 */));
    // 00426083  db01                   -fild dword ptr [ecx]
    x86::Float fpu14 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ecx)));
    // 00426085  d8c9                   -fmul st(1)
    x86::Float fpu15 = cpu.fpu.mul(fpu14, x86::Float(fpu13));
    // 00426087  db457e                 -fild dword ptr [ebp + 0x7e]
    x86::Float fpu16 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */)));
    // 0042608a  d8ca                   -fmul st(2)
    x86::Float fpu17 = cpu.fpu.mul(fpu16, x86::Float(fpu13));
    // 0042608c  89457e                 -mov dword ptr [ebp + 0x7e], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */) = cpu.eax;
    // 0042608f  8b4526                 -mov eax, dword ptr [ebp + 0x26]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(38) /* 0x26 */);
    // 00426092  d95d12                 -fstp dword ptr [ebp + 0x12]
    app->getMemory<float>(cpu.ebp + x86::reg32(18) /* 0x12 */) = float(fpu17);
    // 00426095  db8004305500           -fild dword ptr [eax + 0x553004]
    x86::Float fpu18 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.eax + x86::reg32(5582852) /* 0x553004 */)));
    // 0042609b  d84d12                 -fmul dword ptr [ebp + 0x12]
    x86::Float fpu19 = cpu.fpu.mul(fpu18, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(18) /* 0x12 */)));
    // 0042609e  dec1                   -faddp st(1)
    x86::Float fpu20 = cpu.fpu.add(fpu15, fpu19);
    // 004260a0  8b4b0c                 -mov ecx, dword ptr [ebx + 0xc]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(12) /* 0xc */);
    // 004260a3  d95b14                 -fstp dword ptr [ebx + 0x14]
    app->getMemory<float>(cpu.ebx + x86::reg32(20) /* 0x14 */) = float(fpu20);
    // 004260a6  8b148d0c305500         -mov edx, dword ptr [ecx*4 + 0x55300c]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5582860) /* 0x55300c */ + cpu.ecx * 4);
    // 004260ad  8d04d500000000         -lea eax, [edx*8]
    cpu.eax = x86::reg32(cpu.edx * 8);
    // 004260b4  db457a                 -fild dword ptr [ebp + 0x7a]
    x86::Float fpu21 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(122) /* 0x7a */)));
    // 004260b7  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 004260b9  d8c9                   -fmul st(1)
    x86::Float fpu22 = cpu.fpu.mul(fpu21, x86::Float(fpu13));
    // 004260bb  db448604               -fild dword ptr [esi + eax*4 + 4]
    x86::Float fpu23 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.esi + x86::reg32(4) /* 0x4 */ + cpu.eax * 4)));
    // 004260bf  d8ca                   -fmul st(2)
    x86::Float fpu24 = cpu.fpu.mul(fpu23, x86::Float(fpu13));
    // 004260c1  d9c9                   -fxch st(1)
    
    // 004260c3  d95d16                 -fstp dword ptr [ebp + 0x16]
    app->getMemory<float>(cpu.ebp + x86::reg32(22) /* 0x16 */) = float(fpu22);
    // 004260c6  db048d04305500         -fild dword ptr [ecx*4 + 0x553004]
    x86::Float fpu25 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(5582852) /* 0x553004 */ + cpu.ecx * 4)));
    // 004260cd  d84d16                 -fmul dword ptr [ebp + 0x16]
    x86::Float fpu26 = cpu.fpu.mul(fpu25, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(22) /* 0x16 */)));
    // 004260d0  dec1                   -faddp st(1)
    x86::Float fpu27 = cpu.fpu.add(fpu24, fpu26);
    // 004260d2  8b530c                 -mov edx, dword ptr [ebx + 0xc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(12) /* 0xc */);
    // 004260d5  d95b18                 -fstp dword ptr [ebx + 0x18]
    app->getMemory<float>(cpu.ebx + x86::reg32(24) /* 0x18 */) = float(fpu27);
    // 004260d8  8b0c950c305500         -mov ecx, dword ptr [edx*4 + 0x55300c]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(5582860) /* 0x55300c */ + cpu.edx * 4);
    // 004260df  8d04cd00000000         -lea eax, [ecx*8]
    cpu.eax = x86::reg32(cpu.ecx * 8);
    // 004260e6  db457e                 -fild dword ptr [ebp + 0x7e]
    x86::Float fpu28 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */)));
    // 004260e9  01c8                   +add eax, ecx
    {
        x86::reg32& tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ecx));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 004260eb  d8c9                   +fmul st(1)
    x86::Float fpu29 = cpu.fpu.mul(fpu28, x86::Float(fpu13));
    // 004260ed  db448608               +fild dword ptr [esi + eax*4 + 8]
    x86::Float fpu30 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.esi + x86::reg32(8) /* 0x8 */ + cpu.eax * 4)));
    // 004260f1  deca                   +fmulp st(2)
    x86::Float fpu31 = cpu.fpu.mul(fpu13, fpu30);
    // 004260f3  d95d1a                 +fstp dword ptr [ebp + 0x1a]
    app->getMemory<float>(cpu.ebp + x86::reg32(26) /* 0x1a */) = float(fpu29);
    // 004260f6  db049504305500         +fild dword ptr [edx*4 + 0x553004]
    x86::Float fpu32 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(5582852) /* 0x553004 */ + cpu.edx * 4)));
    // 004260fd  d84d1a                 +fmul dword ptr [ebp + 0x1a]
    x86::Float fpu33 = cpu.fpu.mul(fpu32, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(26) /* 0x1a */)));
    // 00426100  dec1                   +faddp st(1)
    x86::Float fpu34 = cpu.fpu.add(fpu31, fpu33);
    // 00426102  d95b1c                 +fstp dword ptr [ebx + 0x1c]
    app->getMemory<float>(cpu.ebx + x86::reg32(28) /* 0x1c */) = float(fpu34);
    // 00426105  8b4304                 -mov eax, dword ptr [ebx + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(4) /* 0x4 */);
    // 00426108  d98098000000           +fld dword ptr [eax + 0x98]
    x86::Float fpu35 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(152) /* 0x98 */));
    // 0042610e  d86314                 +fsub dword ptr [ebx + 0x14]
    x86::Float fpu36 = cpu.fpu.sub(fpu35, x86::Float(app->getMemory<float>(cpu.ebx + x86::reg32(20) /* 0x14 */)));
    // 00426111  d9ee                   +fldz 
    x86::Float fpu37 = 0.0;
    // 00426113  d9c9                   +fxch st(1)
    
    // 00426115  d95d5e                 +fstp dword ptr [ebp + 0x5e]
    app->getMemory<float>(cpu.ebp + x86::reg32(94) /* 0x5e */) = float(fpu36);
    // 00426118  d85d5e                 +fcomp dword ptr [ebp + 0x5e]
    cpu.fpu.compare(fpu37, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(94) /* 0x5e */)));
    // 0042611b  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 0042611d  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 0042611e  760a                   -jbe 0x42612a
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x0042612a;
    }
    // 00426120  d9455e                 +fld dword ptr [ebp + 0x5e]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu38 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(94) /* 0x5e */));
    // 00426123  d9e0                   +fchs 
    x86::Float fpu39 = -fpu38;
    // 00426125  d95d42                 +fstp dword ptr [ebp + 0x42]
    app->getMemory<float>(cpu.ebp + x86::reg32(66) /* 0x42 */) = float(fpu39);
    }
    // 00426128  eb06                   -jmp 0x426130
    goto L_0x00426130;
L_0x0042612a:
    // 0042612a  8b455e                 -mov eax, dword ptr [ebp + 0x5e]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(94) /* 0x5e */);
    // 0042612d  894542                 -mov dword ptr [ebp + 0x42], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(66) /* 0x42 */) = cpu.eax;
L_0x00426130:
    // 00426130  8b4304                 -mov eax, dword ptr [ebx + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(4) /* 0x4 */);
    // 00426133  d980a0000000           +fld dword ptr [eax + 0xa0]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu40 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(160) /* 0xa0 */));
    // 00426139  d8631c                 +fsub dword ptr [ebx + 0x1c]
    x86::Float fpu41 = cpu.fpu.sub(fpu40, x86::Float(app->getMemory<float>(cpu.ebx + x86::reg32(28) /* 0x1c */)));
    // 0042613c  d9ee                   +fldz 
    x86::Float fpu42 = 0.0;
    // 0042613e  d9c9                   +fxch st(1)
    
    // 00426140  d95d56                 +fstp dword ptr [ebp + 0x56]
    app->getMemory<float>(cpu.ebp + x86::reg32(86) /* 0x56 */) = float(fpu41);
    // 00426143  d85d56                 +fcomp dword ptr [ebp + 0x56]
    cpu.fpu.compare(fpu42, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(86) /* 0x56 */)));
    // 00426146  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00426148  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 00426149  760a                   -jbe 0x426155
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x00426155;
    }
    // 0042614b  d94556                 +fld dword ptr [ebp + 0x56]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu43 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(86) /* 0x56 */));
    // 0042614e  d9e0                   +fchs 
    x86::Float fpu44 = -fpu43;
    // 00426150  d95d32                 +fstp dword ptr [ebp + 0x32]
    app->getMemory<float>(cpu.ebp + x86::reg32(50) /* 0x32 */) = float(fpu44);
    }
    // 00426153  eb06                   -jmp 0x42615b
    goto L_0x0042615b;
L_0x00426155:
    // 00426155  8b4556                 -mov eax, dword ptr [ebp + 0x56]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(86) /* 0x56 */);
    // 00426158  894532                 -mov dword ptr [ebp + 0x32], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(50) /* 0x32 */) = cpu.eax;
L_0x0042615b:
    // 0042615b  d94542                 +fld dword ptr [ebp + 0x42]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu45 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(66) /* 0x42 */));
    // 0042615e  d85d32                 +fcomp dword ptr [ebp + 0x32]
    cpu.fpu.compare(fpu45, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(50) /* 0x32 */)));
    // 00426161  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00426163  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 00426164  766c                   -jbe 0x4261d2
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x004261d2;
    }
    // 00426166  8b4304                 -mov eax, dword ptr [ebx + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(4) /* 0x4 */);
    // 00426169  d980a0000000           +fld dword ptr [eax + 0xa0]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu46 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(160) /* 0xa0 */));
    // 0042616f  d8631c                 +fsub dword ptr [ebx + 0x1c]
    x86::Float fpu47 = cpu.fpu.sub(fpu46, x86::Float(app->getMemory<float>(cpu.ebx + x86::reg32(28) /* 0x1c */)));
    // 00426172  d9ee                   +fldz 
    x86::Float fpu48 = 0.0;
    // 00426174  d9c9                   +fxch st(1)
    
    // 00426176  d95d66                 +fstp dword ptr [ebp + 0x66]
    app->getMemory<float>(cpu.ebp + x86::reg32(102) /* 0x66 */) = float(fpu47);
    // 00426179  d85d66                 +fcomp dword ptr [ebp + 0x66]
    cpu.fpu.compare(fpu48, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(102) /* 0x66 */)));
    // 0042617c  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 0042617e  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 0042617f  760a                   -jbe 0x42618b
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x0042618b;
    }
    // 00426181  d94566                 +fld dword ptr [ebp + 0x66]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu49 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(102) /* 0x66 */));
    // 00426184  d9e0                   +fchs 
    x86::Float fpu50 = -fpu49;
    // 00426186  d95d4a                 +fstp dword ptr [ebp + 0x4a]
    app->getMemory<float>(cpu.ebp + x86::reg32(74) /* 0x4a */) = float(fpu50);
    }
    // 00426189  eb06                   -jmp 0x426191
    goto L_0x00426191;
L_0x0042618b:
    // 0042618b  8b4566                 -mov eax, dword ptr [ebp + 0x66]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(102) /* 0x66 */);
    // 0042618e  89454a                 -mov dword ptr [ebp + 0x4a], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(74) /* 0x4a */) = cpu.eax;
L_0x00426191:
    // 00426191  d9454a                 +fld dword ptr [ebp + 0x4a]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu51 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(74) /* 0x4a */));
    // 00426194  d80d5c6f5300           +fmul dword ptr [0x536f5c]
    x86::Float fpu52 = cpu.fpu.mul(fpu51, x86::Float(app->getMemory<float>(x86::reg32(5467996) /* 0x536f5c */)));
    // 0042619a  8b4304                 -mov eax, dword ptr [ebx + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(4) /* 0x4 */);
    // 0042619d  d9ee                   +fldz 
    x86::Float fpu53 = 0.0;
    // 0042619f  d98098000000           +fld dword ptr [eax + 0x98]
    x86::Float fpu54 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(152) /* 0x98 */));
    // 004261a5  d86314                 +fsub dword ptr [ebx + 0x14]
    x86::Float fpu55 = cpu.fpu.sub(fpu54, x86::Float(app->getMemory<float>(cpu.ebx + x86::reg32(20) /* 0x14 */)));
    // 004261a8  d9ca                   +fxch st(2)
    
    // 004261aa  d95d2a                 +fstp dword ptr [ebp + 0x2a]
    app->getMemory<float>(cpu.ebp + x86::reg32(42) /* 0x2a */) = float(fpu52);
    // 004261ad  d9c9                   +fxch st(1)
    
    // 004261af  d95d6a                 +fstp dword ptr [ebp + 0x6a]
    app->getMemory<float>(cpu.ebp + x86::reg32(106) /* 0x6a */) = float(fpu55);
    // 004261b2  d85d6a                 +fcomp dword ptr [ebp + 0x6a]
    cpu.fpu.compare(fpu53, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(106) /* 0x6a */)));
    // 004261b5  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 004261b7  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 004261b8  760a                   -jbe 0x4261c4
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x004261c4;
    }
    // 004261ba  d9456a                 +fld dword ptr [ebp + 0x6a]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu56 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(106) /* 0x6a */));
    // 004261bd  d9e0                   +fchs 
    x86::Float fpu57 = -fpu56;
    // 004261bf  d95d3a                 +fstp dword ptr [ebp + 0x3a]
    app->getMemory<float>(cpu.ebp + x86::reg32(58) /* 0x3a */) = float(fpu57);
    }
    // 004261c2  eb06                   -jmp 0x4261ca
    goto L_0x004261ca;
L_0x004261c4:
    // 004261c4  8b456a                 -mov eax, dword ptr [ebp + 0x6a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(106) /* 0x6a */);
    // 004261c7  89453a                 -mov dword ptr [ebp + 0x3a], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(58) /* 0x3a */) = cpu.eax;
L_0x004261ca:
    // 004261ca  d9453a                 +fld dword ptr [ebp + 0x3a]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu58 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(58) /* 0x3a */));
    // 004261cd  d8452a                 +fadd dword ptr [ebp + 0x2a]
    x86::Float fpu59 = cpu.fpu.add(fpu58, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(42) /* 0x2a */)));
    cpu.fpu.count += 1;
    cpu.fpu.st(0) = fpu59;
    }
    // 004261d0  eb6a                   -jmp 0x42623c
    goto L_0x0042623c;
L_0x004261d2:
    // 004261d2  8b4304                 -mov eax, dword ptr [ebx + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(4) /* 0x4 */);
    // 004261d5  d98098000000           +fld dword ptr [eax + 0x98]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu60 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(152) /* 0x98 */));
    // 004261db  d86314                 +fsub dword ptr [ebx + 0x14]
    x86::Float fpu61 = cpu.fpu.sub(fpu60, x86::Float(app->getMemory<float>(cpu.ebx + x86::reg32(20) /* 0x14 */)));
    // 004261de  d9ee                   +fldz 
    x86::Float fpu62 = 0.0;
    // 004261e0  d9c9                   +fxch st(1)
    
    // 004261e2  d95d6e                 +fstp dword ptr [ebp + 0x6e]
    app->getMemory<float>(cpu.ebp + x86::reg32(110) /* 0x6e */) = float(fpu61);
    // 004261e5  d85d6e                 +fcomp dword ptr [ebp + 0x6e]
    cpu.fpu.compare(fpu62, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(110) /* 0x6e */)));
    // 004261e8  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 004261ea  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 004261eb  760a                   -jbe 0x4261f7
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x004261f7;
    }
    // 004261ed  d9456e                 +fld dword ptr [ebp + 0x6e]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu63 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(110) /* 0x6e */));
    // 004261f0  d9e0                   +fchs 
    x86::Float fpu64 = -fpu63;
    // 004261f2  d95d36                 +fstp dword ptr [ebp + 0x36]
    app->getMemory<float>(cpu.ebp + x86::reg32(54) /* 0x36 */) = float(fpu64);
    }
    // 004261f5  eb06                   -jmp 0x4261fd
    goto L_0x004261fd;
L_0x004261f7:
    // 004261f7  8b456e                 -mov eax, dword ptr [ebp + 0x6e]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(110) /* 0x6e */);
    // 004261fa  894536                 -mov dword ptr [ebp + 0x36], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(54) /* 0x36 */) = cpu.eax;
L_0x004261fd:
    // 004261fd  d94536                 +fld dword ptr [ebp + 0x36]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu65 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(54) /* 0x36 */));
    // 00426200  d80d5c6f5300           +fmul dword ptr [0x536f5c]
    x86::Float fpu66 = cpu.fpu.mul(fpu65, x86::Float(app->getMemory<float>(x86::reg32(5467996) /* 0x536f5c */)));
    // 00426206  8b4304                 -mov eax, dword ptr [ebx + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(4) /* 0x4 */);
    // 00426209  d9ee                   +fldz 
    x86::Float fpu67 = 0.0;
    // 0042620b  d980a0000000           +fld dword ptr [eax + 0xa0]
    x86::Float fpu68 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(160) /* 0xa0 */));
    // 00426211  d8631c                 +fsub dword ptr [ebx + 0x1c]
    x86::Float fpu69 = cpu.fpu.sub(fpu68, x86::Float(app->getMemory<float>(cpu.ebx + x86::reg32(28) /* 0x1c */)));
    // 00426214  d9ca                   +fxch st(2)
    
    // 00426216  d95d2e                 +fstp dword ptr [ebp + 0x2e]
    app->getMemory<float>(cpu.ebp + x86::reg32(46) /* 0x2e */) = float(fpu66);
    // 00426219  d9c9                   +fxch st(1)
    
    // 0042621b  d95d52                 +fstp dword ptr [ebp + 0x52]
    app->getMemory<float>(cpu.ebp + x86::reg32(82) /* 0x52 */) = float(fpu69);
    // 0042621e  d85d52                 +fcomp dword ptr [ebp + 0x52]
    cpu.fpu.compare(fpu67, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(82) /* 0x52 */)));
    // 00426221  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00426223  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 00426224  760a                   -jbe 0x426230
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x00426230;
    }
    // 00426226  d94552                 +fld dword ptr [ebp + 0x52]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu70 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(82) /* 0x52 */));
    // 00426229  d9e0                   +fchs 
    x86::Float fpu71 = -fpu70;
    // 0042622b  d95d46                 +fstp dword ptr [ebp + 0x46]
    app->getMemory<float>(cpu.ebp + x86::reg32(70) /* 0x46 */) = float(fpu71);
    }
    // 0042622e  eb06                   -jmp 0x426236
    goto L_0x00426236;
L_0x00426230:
    // 00426230  8b4552                 -mov eax, dword ptr [ebp + 0x52]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(82) /* 0x52 */);
    // 00426233  894546                 -mov dword ptr [ebp + 0x46], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(70) /* 0x46 */) = cpu.eax;
L_0x00426236:
    // 00426236  d94546                 +fld dword ptr [ebp + 0x46]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu72 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(70) /* 0x46 */));
    // 00426239  d8452e                 +fadd dword ptr [ebp + 0x2e]
    x86::Float fpu73 = cpu.fpu.add(fpu72, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(46) /* 0x2e */)));
    cpu.fpu.count += 1;
    cpu.fpu.st(0) = fpu73;
    }
L_0x0042623c:
    // 0042623c  d95d4e                 +fstp dword ptr [ebp + 0x4e]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu74 = cpu.fpu.st(0);
    app->getMemory<float>(cpu.ebp + x86::reg32(78) /* 0x4e */) = float(fpu74);
    // 0042623f  d9454e                 +fld dword ptr [ebp + 0x4e]
    x86::Float fpu75 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(78) /* 0x4e */));
    // 00426242  d80d5c6f5300           +fmul dword ptr [0x536f5c]
    x86::Float fpu76 = cpu.fpu.mul(fpu75, x86::Float(app->getMemory<float>(x86::reg32(5467996) /* 0x536f5c */)));
    // 00426248  d905606f5300           +fld dword ptr [0x536f60]
    x86::Float fpu77 = x86::Float(app->getMemory<float>(x86::reg32(5468000) /* 0x536f60 */));
    // 0042624e  d9c9                   +fxch st(1)
    
    // 00426250  d95d76                 +fstp dword ptr [ebp + 0x76]
    app->getMemory<float>(cpu.ebp + x86::reg32(118) /* 0x76 */) = float(fpu76);
    // 00426253  d85d76                 +fcomp dword ptr [ebp + 0x76]
    cpu.fpu.compare(fpu77, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(118) /* 0x76 */)));
    // 00426256  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00426258  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    cpu.fpu.count -= 1;
    }
    // 00426259  7309                   -jae 0x426264
    if (!cpu.flags.cf)
    {
        goto L_0x00426264;
    }
    // 0042625b  c7453e00006040         -mov dword ptr [ebp + 0x3e], 0x40600000
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(62) /* 0x3e */) = 1080033280 /*0x40600000*/;
    // 00426262  eb06                   -jmp 0x42626a
    goto L_0x0042626a;
L_0x00426264:
    // 00426264  8b4576                 -mov eax, dword ptr [ebp + 0x76]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(118) /* 0x76 */);
    // 00426267  89453e                 -mov dword ptr [ebp + 0x3e], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(62) /* 0x3e */) = cpu.eax;
L_0x0042626a:
    // 0042626a  d905386f5300           -fld dword ptr [0x536f38]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu78 = x86::Float(app->getMemory<float>(x86::reg32(5467960) /* 0x536f38 */));
    // 00426270  d8653e                 -fsub dword ptr [ebp + 0x3e]
    x86::Float fpu79 = cpu.fpu.sub(fpu78, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(62) /* 0x3e */)));
    // 00426273  d84318                 -fadd dword ptr [ebx + 0x18]
    x86::Float fpu80 = cpu.fpu.add(fpu79, x86::Float(app->getMemory<float>(cpu.ebx + x86::reg32(24) /* 0x18 */)));
    // 00426276  d95b18                 -fstp dword ptr [ebx + 0x18]
    app->getMemory<float>(cpu.ebx + x86::reg32(24) /* 0x18 */) = float(fpu80);
    }
L_0x00426279:
    // 00426279  8da582000000           -lea esp, [ebp + 0x82]
    cpu.esp = x86::reg32(cpu.ebp + x86::reg32(130) /* 0x82 */);
    // 0042627f  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426280  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426281  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426282  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426283  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426284  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426285  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x54 0x22 0x00 */
void Application::sub_426290(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00426290  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00426291  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00426293  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426294  c3                     -ret 
    cpu.esp += 4;
    return;
}

}
