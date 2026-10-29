#include "nfs3hp.h"
#include <lib/thread.h>

namespace nfs3hp
{
// Port (tools/apply_native_ai.py): defined in native_ai.cpp.
bool aiHeading(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_ai.py): defined in native_ai.cpp.
bool aiPull(win32::WinApplication* app, x86::CPU& cpu);

/* sub_405af0: native, nfs3hp::aidrive::nearHuman */

/* sub_405b50: native, nfs3hp::dead::stub_0x405b50 */

/* sub_405c20: native, nfs3hp::dead::stub_0x405c20 */

/* sub_405c80: native, nfs3hp::aidrive::humanNearSlice */

/* sub_405cd0: native, nfs3hp::aidrive::trafficUnwatched */

/* sub_405d40: native, nfs3hp::aidrive::trafficStart */

/* sub_405dc0: native, nfs3hp::aidrive::trafficStop */

/* sub_405e20: native, nfs3hp::aidrive::extraCarStep */

/* sub_405e50: native, nfs3hp::dead::stub_0x405e50 */

/* sub_405e60: native, nfs3hp::aidrive::setDrivingConstants */

/* sub_405fb0: native, nfs3hp::aidrive::drivingNothing */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 0x8b 0xdb */
void Application::sub_405fc0(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00405fc0  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00405fc1  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00405fc3  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00405fc4  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_405fd0: native, nfs3hp::aidrive::setReverse */

/* sub_4060d0: native, nfs3hp::aidrive::reverseCheck */

/* sub_406120: native, nfs3hp::aidrive::reverseWhenSlow */

/* sub_406160: native, nfs3hp::aidrive::reverseWhenTipped */

/* sub_4061b0: native, nfs3hp::aidrive::engineRevs */

/* sub_4063e0: native, nfs3hp::aidrive::brakeForce */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x8d 0x40 0x00 */
void Application::sub_4064f0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (aiPull(app, cpu.sync())) /* port: native (tools/apply_native_ai.py) */
    {
        cpu.reload();
        return;
    }
    // 004064f0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004064f1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004064f2  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004064f3  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004064f4  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004064f5  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004064f6  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004064f8  83ec24                 -sub esp, 0x24
    (cpu.esp) -= x86::reg32(x86::sreg32(36 /*0x24*/));
    // 004064fb  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004064fd  c6800905000000         -mov byte ptr [eax + 0x509], 0
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(1289) /* 0x509 */) = 0 /*0x0*/;
    // 00406504  f6800002000001         +test byte ptr [eax + 0x200], 1
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(cpu.eax + x86::reg32(512) /* 0x200 */) & 1 /*0x1*/));
    // 0040650b  7445                   -je 0x406552
    if (cpu.flags.zf)
    {
        goto L_0x00406552;
    }
    // 0040650d  8b8228050000           -mov eax, dword ptr [edx + 0x528]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(1320) /* 0x528 */);
    // 00406513  8b80cc010000           -mov eax, dword ptr [eax + 0x1cc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(460) /* 0x1cc */);
    // 00406519  8945f4                 -mov dword ptr [ebp - 0xc], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.eax;
    // 0040651c  d945f4                 +fld dword ptr [ebp - 0xc]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */));
    // 0040651f  d88abc070000           +fmul dword ptr [edx + 0x7bc]
    x86::Float fpu2 = cpu.fpu.mul(fpu1, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(1980) /* 0x7bc */)));
    // 00406525  d89ac0070000           +fcomp dword ptr [edx + 0x7c0]
    cpu.fpu.compare(fpu2, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(1984) /* 0x7c0 */)));
    // 0040652b  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 0040652d  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 0040652e  730a                   -jae 0x40653a
    if (!cpu.flags.cf)
    {
        goto L_0x0040653a;
    }
    // 00406530  31d2                   +xor edx, edx
    cpu.clear_co();
    cpu.set_szp((cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx))));
    // 00406532  8955f8                 -mov dword ptr [ebp - 8], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.edx;
    // 00406535  e97a010000             -jmp 0x4066b4
    goto L_0x004066b4;
L_0x0040653a:
    // 0040653a  d982c0070000           +fld dword ptr [edx + 0x7c0]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu3 = x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(1984) /* 0x7c0 */));
    // 00406540  d85df4                 +fcomp dword ptr [ebp - 0xc]
    cpu.fpu.compare(fpu3, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */)));
    // 00406543  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00406545  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 00406546  760a                   -jbe 0x406552
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x00406552;
    }
    // 00406548  31c9                   +xor ecx, ecx
    cpu.clear_co();
    cpu.set_szp((cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx))));
    // 0040654a  894df8                 -mov dword ptr [ebp - 8], ecx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.ecx;
    // 0040654d  e962010000             -jmp 0x4066b4
    goto L_0x004066b4;
L_0x00406552:
    // 00406552  d982c4070000           -fld dword ptr [edx + 0x7c4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu4 = x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(1988) /* 0x7c4 */));
    // 00406558  dc0554625300           -fadd qword ptr [0x536254]
    x86::Float fpu5 = cpu.fpu.add(fpu4, x86::Float(app->getMemory<double>(x86::reg32(5464660) /* 0x536254 */)));
    // 0040655e  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 00406561  db1c24                 -fistp dword ptr [esp]
    app->getMemory<x86::reg32>(cpu.esp) = x86::reg32(cpu.fpu.toInteger<x86::sreg32>(fpu5));
    // 00406564  58                     -pop eax
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00406565  83f86f                 +cmp eax, 0x6f
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(111 /*0x6f*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    }
    // 00406568  7e05                   -jle 0x40656f
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x0040656f;
    }
    // 0040656a  b86f000000             -mov eax, 0x6f
    cpu.eax = 111 /*0x6f*/;
L_0x0040656f:
    // 0040656f  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00406571  7f02                   -jg 0x406575
    if (!cpu.flags.zf && (cpu.flags.sf == cpu.flags.of))
    {
        goto L_0x00406575;
    }
    // 00406573  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
L_0x00406575:
    // 00406575  8b9a28050000           -mov ebx, dword ptr [edx + 0x528]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(1320) /* 0x528 */);
    // 0040657b  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 0040657d  8b8483ec020000         -mov eax, dword ptr [ebx + eax*4 + 0x2ec]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(748) /* 0x2ec */ + cpu.eax * 4);
    // 00406584  8b1df0d46f00           -mov ebx, dword ptr [0x6fd4f0]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(7329008) /* 0x6fd4f0 */);
    // 0040658a  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 0040658d  85db                   +test ebx, ebx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & cpu.ebx));
    // 0040658f  7512                   -jne 0x4065a3
    if (!cpu.flags.zf)
    {
        goto L_0x004065a3;
    }
    // 00406591  837a0864               +cmp dword ptr [edx + 8], 0x64
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(8) /* 0x8 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(100 /*0x64*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00406595  7e0c                   -jle 0x4065a3
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004065a3;
    }
    // 00406597  d945fc                 -fld dword ptr [ebp - 4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu6 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */));
    // 0040659a  d80d5c625300           -fmul dword ptr [0x53625c]
    x86::Float fpu7 = cpu.fpu.mul(fpu6, x86::Float(app->getMemory<float>(x86::reg32(5464668) /* 0x53625c */)));
    // 004065a0  d95dfc                 -fstp dword ptr [ebp - 4]
    app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = float(fpu7);
    }
L_0x004065a3:
    // 004065a3  833dccd46f0000         +cmp dword ptr [0x6fd4cc], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(7328972) /* 0x6fd4cc */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004065aa  7411                   -je 0x4065bd
    if (cpu.flags.zf)
    {
        goto L_0x004065bd;
    }
    // 004065ac  83f92d                 +cmp ecx, 0x2d
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(45 /*0x2d*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004065af  7d0c                   -jge 0x4065bd
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004065bd;
    }
    // 004065b1  d945fc                 -fld dword ptr [ebp - 4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu8 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */));
    // 004065b4  d80d5c625300           -fmul dword ptr [0x53625c]
    x86::Float fpu9 = cpu.fpu.mul(fpu8, x86::Float(app->getMemory<float>(x86::reg32(5464668) /* 0x53625c */)));
    // 004065ba  d95dfc                 -fstp dword ptr [ebp - 4]
    app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = float(fpu9);
    }
L_0x004065bd:
    // 004065bd  83bae406000000         +cmp dword ptr [edx + 0x6e4], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(1764) /* 0x6e4 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004065c4  7e0c                   -jle 0x4065d2
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004065d2;
    }
    // 004065c6  d945fc                 -fld dword ptr [ebp - 4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu10 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */));
    // 004065c9  d80d60625300           -fmul dword ptr [0x536260]
    x86::Float fpu11 = cpu.fpu.mul(fpu10, x86::Float(app->getMemory<float>(x86::reg32(5464672) /* 0x536260 */)));
    // 004065cf  d95dfc                 -fstp dword ptr [ebp - 4]
    app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = float(fpu11);
    }
L_0x004065d2:
    // 004065d2  833d0cd56f0000         +cmp dword ptr [0x6fd50c], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(7329036) /* 0x6fd50c */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004065d9  0f845f000000           -je 0x40663e
    if (cpu.flags.zf)
    {
        goto L_0x0040663e;
    }
    // 004065df  8b35f4d46f00           -mov esi, dword ptr [0x6fd4f4]
    cpu.esi = app->getMemory<x86::reg32>(x86::reg32(7329012) /* 0x6fd4f4 */);
    // 004065e5  8b82f0010000           -mov eax, dword ptr [edx + 0x1f0]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(496) /* 0x1f0 */);
    // 004065eb  39f0                   +cmp eax, esi
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
    // 004065ed  744f                   -je 0x40663e
    if (cpu.flags.zf)
    {
        goto L_0x0040663e;
    }
    // 004065ef  66833dda227a0000       +cmp word ptr [0x7a22da], 0
    {
        x86::reg16 tmp1 = app->getMemory<x86::reg16>(x86::reg32(8004314) /* 0x7a22da */);
        x86::reg16 tmp2 = x86::reg16(x86::sreg16(0 /*0x0*/));
        x86::reg16 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 15);
        cpu.flags.of ^= 1 & (result >> 15);
        cpu.flags.of &= (1 & (tmp1 >> 15)) != (1 & (tmp2 >> 15));
        cpu.set_szp(result);
    }
    // 004065f7  7408                   -je 0x406601
    if (cpu.flags.zf)
    {
        goto L_0x00406601;
    }
    // 004065f9  3b0518d56f00           +cmp eax, dword ptr [0x6fd518]
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
    // 004065ff  7d3d                   -jge 0x40663e
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x0040663e;
    }
L_0x00406601:
    // 00406601  a1f4d46f00             -mov eax, dword ptr [0x6fd4f4]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(7329012) /* 0x6fd4f4 */);
    // 00406606  8b1c8548fa5e00         -mov ebx, dword ptr [eax*4 + 0x5efa48]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(6224456) /* 0x5efa48 */ + cpu.eax * 4);
    // 0040660d  8b421c                 -mov eax, dword ptr [edx + 0x1c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(28) /* 0x1c */);
    // 00406610  2b431c                 -sub eax, dword ptr [ebx + 0x1c]
    (cpu.eax) -= x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(28) /* 0x1c */)));
    // 00406613  83f8fd                 +cmp eax, -3
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(-3 /*-0x3*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00406616  7e05                   -jle 0x40661d
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x0040661d;
    }
    // 00406618  83f80f                 +cmp eax, 0xf
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(15 /*0xf*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0040661b  7c21                   -jl 0x40663e
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x0040663e;
    }
L_0x0040661d:
    // 0040661d  83f8f8                 +cmp eax, -8
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(-8 /*-0x8*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00406620  7e10                   -jle 0x406632
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00406632;
    }
    // 00406622  83f81e                 +cmp eax, 0x1e
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(30 /*0x1e*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00406625  7d0b                   -jge 0x406632
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00406632;
    }
    // 00406627  d945fc                 +fld dword ptr [ebp - 4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu12 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */));
    // 0040662a  d80d64625300           +fmul dword ptr [0x536264]
    x86::Float fpu13 = cpu.fpu.mul(fpu12, x86::Float(app->getMemory<float>(x86::reg32(5464676) /* 0x536264 */)));
    cpu.fpu.count += 1;
    cpu.fpu.st(0) = fpu13;
    }
    // 00406630  eb09                   -jmp 0x40663b
    goto L_0x0040663b;
L_0x00406632:
    // 00406632  d945fc                 -fld dword ptr [ebp - 4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu14 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */));
    // 00406635  d80d68625300           -fmul dword ptr [0x536268]
    x86::Float fpu15 = cpu.fpu.mul(fpu14, x86::Float(app->getMemory<float>(x86::reg32(5464680) /* 0x536268 */)));
    cpu.fpu.count += 1;
    cpu.fpu.st(0) = fpu15;
    }
L_0x0040663b:
    // 0040663b  d95dfc                 -fstp dword ptr [ebp - 4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu16 = cpu.fpu.st(0);
    app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = float(fpu16);
    cpu.fpu.count -= 1;
    }
L_0x0040663e:
    // 0040663e  f6820002000010         +test byte ptr [edx + 0x200], 0x10
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(cpu.edx + x86::reg32(512) /* 0x200 */) & 16 /*0x10*/));
    // 00406645  7434                   -je 0x40667b
    if (cpu.flags.zf)
    {
        goto L_0x0040667b;
    }
    // 00406647  83f902                 +cmp ecx, 2
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(2 /*0x2*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0040664a  7d2f                   -jge 0x40667b
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x0040667b;
    }
    // 0040664c  d945fc                 +fld dword ptr [ebp - 4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu17 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */));
    // 0040664f  dd55dc                 +fst qword ptr [ebp - 0x24]
    app->getMemory<double>(cpu.ebp + x86::reg32(-36) /* -0x24 */) = double(fpu17);
    // 00406652  dc1d6c625300           +fcomp qword ptr [0x53626c]
    cpu.fpu.compare(fpu17, x86::Float(app->getMemory<double>(x86::reg32(5464684) /* 0x53626c */)));
    // 00406658  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 0040665a  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 0040665b  760c                   -jbe 0x406669
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x00406669;
    }
    // 0040665d  31ff                   +xor edi, edi
    cpu.clear_co();
    cpu.set_szp((cpu.edi ^= x86::reg32(x86::sreg32(cpu.edi))));
    // 0040665f  b800002840             -mov eax, 0x40280000
    cpu.eax = 1076363264 /*0x40280000*/;
    // 00406664  897dec                 -mov dword ptr [ebp - 0x14], edi
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */) = cpu.edi;
    // 00406667  eb09                   -jmp 0x406672
    goto L_0x00406672;
L_0x00406669:
    // 00406669  8b45dc                 -mov eax, dword ptr [ebp - 0x24]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-36) /* -0x24 */);
    // 0040666c  8945ec                 -mov dword ptr [ebp - 0x14], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */) = cpu.eax;
    // 0040666f  8b45e0                 -mov eax, dword ptr [ebp - 0x20]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-32) /* -0x20 */);
L_0x00406672:
    // 00406672  8945f0                 -mov dword ptr [ebp - 0x10], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = cpu.eax;
    // 00406675  dd45ec                 -fld qword ptr [ebp - 0x14]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu18 = x86::Float(app->getMemory<double>(cpu.ebp + x86::reg32(-20) /* -0x14 */));
    // 00406678  d95dfc                 -fstp dword ptr [ebp - 4]
    app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = float(fpu18);
    }
L_0x0040667b:
    // 0040667b  f6052eeb550020         +test byte ptr [0x55eb2e], 0x20
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(x86::reg32(5630766) /* 0x55eb2e */) & 32 /*0x20*/));
    // 00406682  742a                   -je 0x4066ae
    if (cpu.flags.zf)
    {
        goto L_0x004066ae;
    }
    // 00406684  f6820002000020         +test byte ptr [edx + 0x200], 0x20
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(cpu.edx + x86::reg32(512) /* 0x200 */) & 32 /*0x20*/));
    // 0040668b  7421                   -je 0x4066ae
    if (cpu.flags.zf)
    {
        goto L_0x004066ae;
    }
    // 0040668d  d982c4070000           +fld dword ptr [edx + 0x7c4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu19 = x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(1988) /* 0x7c4 */));
    // 00406693  dc1d74625300           +fcomp qword ptr [0x536274]
    cpu.fpu.compare(fpu19, x86::Float(app->getMemory<double>(x86::reg32(5464692) /* 0x536274 */)));
    // 00406699  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 0040669b  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 0040669c  7610                   -jbe 0x4066ae
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x004066ae;
    }
    // 0040669e  d945fc                 -fld dword ptr [ebp - 4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu20 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */));
    // 004066a1  d9c0                   -fld st(0)
    x86::Float fpu21 = x86::Float(fpu20);
    // 004066a3  dc0d7c625300           -fmul qword ptr [0x53627c]
    x86::Float fpu22 = cpu.fpu.mul(fpu21, x86::Float(app->getMemory<double>(x86::reg32(5464700) /* 0x53627c */)));
    // 004066a9  ddd9                   -fstp st(1)
    x86::Float fpu23 = x86::Float(fpu22);
    // 004066ab  d95dfc                 -fstp dword ptr [ebp - 4]
    app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = float(fpu23);
    }
L_0x004066ae:
    // 004066ae  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004066b1  8945f8                 -mov dword ptr [ebp - 8], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.eax;
L_0x004066b4:
    // 004066b4  d945f8                 -fld dword ptr [ebp - 8]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu24 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */));
    // 004066b7  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004066b9  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004066ba  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004066bb  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004066bc  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004066bd  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004066be  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    cpu.fpu.count += 1;
    cpu.fpu.st(0) = fpu24;
    }
    // 004066bf  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_4066c0: native, nfs3hp::aidrive::speedAlongRoad */

/* sub_406880: native, nfs3hp::aidrive::laneError */

/* sub_4068a0: native, nfs3hp::aidrive::glideAlongRoad */

/* sub_406980: native, nfs3hp::aidrive::lookAheadSlice */

/* sub_406a80: native, nfs3hp::aidrive::sidewaysToRoad */

/* sub_406b00: native, nfs3hp::aidrive::towardTarget */

/* sub_406b60: native, nfs3hp::aidrive::towardTargetAhead */

/* sub_406c00: native, nfs3hp::aidrive::towardSlice */

/* sub_406c90: native, nfs3hp::aidrive::towardSliceSlowing */

/* sub_406d40: native, nfs3hp::aidrive::towardLane */

/* sub_406e50: native, nfs3hp::aidrive::wayToGo */

/* align: skip 0x90 */
void Application::sub_4070c0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (aiHeading(app, cpu.sync())) /* port: native (tools/apply_native_ai.py) */
    {
        cpu.reload();
        return;
    }
    // 004070c0  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004070c1  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004070c2  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004070c3  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004070c4  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004070c6  83ec30                 -sub esp, 0x30
    (cpu.esp) -= x86::reg32(x86::sreg32(48 /*0x30*/));
    // 004070c9  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 004070cb  8b8810020000           -mov ecx, dword ptr [eax + 0x210]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(528) /* 0x210 */);
    // 004070d1  891568ec5600           -mov dword ptr [0x56ec68], edx
    app->getMemory<x86::reg32>(x86::reg32(5696616) /* 0x56ec68 */) = cpu.edx;
    // 004070d7  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    // 004070d9  7e0e                   -jle 0x4070e9
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004070e9;
    }
    // 004070db  db8010020000           +fild dword ptr [eax + 0x210]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.eax + x86::reg32(528) /* 0x210 */)));
    // 004070e1  dc0dd4625300           +fmul qword ptr [0x5362d4]
    x86::Float fpu2 = cpu.fpu.mul(fpu1, x86::Float(app->getMemory<double>(x86::reg32(5464788) /* 0x5362d4 */)));
    cpu.fpu.count += 1;
    cpu.fpu.st(0) = fpu2;
    }
    // 004070e7  eb18                   -jmp 0x407101
    goto L_0x00407101;
L_0x004070e9:
    // 004070e9  8db100020000           -lea esi, [ecx + 0x200]
    cpu.esi = x86::reg32(cpu.ecx + x86::reg32(512) /* 0x200 */);
    // 004070ef  8975fc                 -mov dword ptr [ebp - 4], esi
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.esi;
    // 004070f2  db45fc                 +fild dword ptr [ebp - 4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu3 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 004070f5  dc0ddc625300           +fmul qword ptr [0x5362dc]
    x86::Float fpu4 = cpu.fpu.mul(fpu3, x86::Float(app->getMemory<double>(x86::reg32(5464796) /* 0x5362dc */)));
    // 004070fb  dc05e4625300           +fadd qword ptr [0x5362e4]
    x86::Float fpu5 = cpu.fpu.add(fpu4, x86::Float(app->getMemory<double>(x86::reg32(5464804) /* 0x5362e4 */)));
    cpu.fpu.count += 1;
    cpu.fpu.st(0) = fpu5;
    }
L_0x00407101:
    // 00407101  dd5df4                 +fstp qword ptr [ebp - 0xc]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu6 = cpu.fpu.st(0);
    app->getMemory<double>(cpu.ebp + x86::reg32(-12) /* -0xc */) = double(fpu6);
    // 00407104  dd45f4                 +fld qword ptr [ebp - 0xc]
    x86::Float fpu7 = x86::Float(app->getMemory<double>(cpu.ebp + x86::reg32(-12) /* -0xc */));
    // 00407107  8d75d0                 -lea esi, [ebp - 0x30]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(-48) /* -0x30 */);
    // 0040710a  d91d64ec5600           +fstp dword ptr [0x56ec64]
    app->getMemory<float>(x86::reg32(5696612) /* 0x56ec64 */) = float(fpu7);
    cpu.fpu.count -= 1;
    }
    // 00407110  e83bfdffff             -call 0x406e50
    cpu.esp -= 4;
    nfs3hp::aidrive::wayToGo(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00407115  d945d8                 +fld dword ptr [ebp - 0x28]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu8 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-40) /* -0x28 */));
    // 00407118  d945d0                 +fld dword ptr [ebp - 0x30]
    x86::Float fpu9 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-48) /* -0x30 */));
    cpu.fpu.count += 2;
    cpu.fpu.st(0) = fpu9;
    cpu.fpu.st(1) = fpu8;
    }
    // 0040711b  e8b9950d00             -call 0x4e06d9
    cpu.esp -= 4;
    nfs3hp::watcom::IF_DATAN2(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00407120  dc0dec625300           +fmul qword ptr [0x5362ec]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu10 = cpu.fpu.st(0);
    x86::Float fpu11 = cpu.fpu.mul(fpu10, x86::Float(app->getMemory<double>(x86::reg32(5464812) /* 0x5362ec */)));
    // 00407126  d9ee                   +fldz 
    x86::Float fpu12 = 0.0;
    // 00407128  d9c9                   +fxch st(1)
    
    // 0040712a  d9155cec5600           +fst dword ptr [0x56ec5c]
    app->getMemory<float>(x86::reg32(5696604) /* 0x56ec5c */) = float(fpu11);
    // 00407130  dd5dec                 +fstp qword ptr [ebp - 0x14]
    app->getMemory<double>(cpu.ebp + x86::reg32(-20) /* -0x14 */) = double(fpu11);
    // 00407133  dc5dec                 +fcomp qword ptr [ebp - 0x14]
    cpu.fpu.compare(fpu12, x86::Float(app->getMemory<double>(cpu.ebp + x86::reg32(-20) /* -0x14 */)));
    // 00407136  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00407138  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    cpu.fpu.count -= 1;
    }
    // 00407139  760b                   -jbe 0x407146
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x00407146;
    }
    // 0040713b  d9e8                   +fld1 
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu13 = 1.0;
    // 0040713d  dc45ec                 +fadd qword ptr [ebp - 0x14]
    x86::Float fpu14 = cpu.fpu.add(fpu13, x86::Float(app->getMemory<double>(cpu.ebp + x86::reg32(-20) /* -0x14 */)));
    // 00407140  d91d5cec5600           +fstp dword ptr [0x56ec5c]
    app->getMemory<float>(x86::reg32(5696604) /* 0x56ec5c */) = float(fpu14);
    }
L_0x00407146:
    // 00407146  d90564ec5600           +fld dword ptr [0x56ec64]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu15 = x86::Float(app->getMemory<float>(x86::reg32(5696612) /* 0x56ec64 */));
    // 0040714c  d8255cec5600           +fsub dword ptr [0x56ec5c]
    x86::Float fpu16 = cpu.fpu.sub(fpu15, x86::Float(app->getMemory<float>(x86::reg32(5696604) /* 0x56ec5c */)));
    // 00407152  d91560ec5600           +fst dword ptr [0x56ec60]
    app->getMemory<float>(x86::reg32(5696608) /* 0x56ec60 */) = float(fpu16);
    // 00407158  dd55dc                 +fst qword ptr [ebp - 0x24]
    app->getMemory<double>(cpu.ebp + x86::reg32(-36) /* -0x24 */) = double(fpu16);
    // 0040715b  dc1df4625300           +fcomp qword ptr [0x5362f4]
    cpu.fpu.compare(fpu16, x86::Float(app->getMemory<double>(x86::reg32(5464820) /* 0x5362f4 */)));
    // 00407161  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00407163  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 00407164  730b                   -jae 0x407171
    if (!cpu.flags.cf)
    {
        goto L_0x00407171;
    }
    // 00407166  d9e8                   +fld1 
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu17 = 1.0;
    // 00407168  dc45dc                 +fadd qword ptr [ebp - 0x24]
    x86::Float fpu18 = cpu.fpu.add(fpu17, x86::Float(app->getMemory<double>(cpu.ebp + x86::reg32(-36) /* -0x24 */)));
    // 0040716b  d91d60ec5600           +fstp dword ptr [0x56ec60]
    app->getMemory<float>(x86::reg32(5696608) /* 0x56ec60 */) = float(fpu18);
    }
L_0x00407171:
    // 00407171  d90560ec5600           +fld dword ptr [0x56ec60]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu19 = x86::Float(app->getMemory<float>(x86::reg32(5696608) /* 0x56ec60 */));
    // 00407177  dd55e4                 +fst qword ptr [ebp - 0x1c]
    app->getMemory<double>(cpu.ebp + x86::reg32(-28) /* -0x1c */) = double(fpu19);
    // 0040717a  dc1de4625300           +fcomp qword ptr [0x5362e4]
    cpu.fpu.compare(fpu19, x86::Float(app->getMemory<double>(x86::reg32(5464804) /* 0x5362e4 */)));
    // 00407180  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00407182  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 00407183  760f                   -jbe 0x407194
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x00407194;
    }
    // 00407185  dd45e4                 -fld qword ptr [ebp - 0x1c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu20 = x86::Float(app->getMemory<double>(cpu.ebp + x86::reg32(-28) /* -0x1c */));
    // 00407188  dc05fc625300           -fadd qword ptr [0x5362fc]
    x86::Float fpu21 = cpu.fpu.add(fpu20, x86::Float(app->getMemory<double>(x86::reg32(5464828) /* 0x5362fc */)));
    // 0040718e  d91d60ec5600           -fstp dword ptr [0x56ec60]
    app->getMemory<float>(x86::reg32(5696608) /* 0x56ec60 */) = float(fpu21);
    }
L_0x00407194:
    // 00407194  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00407196  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00407197  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00407198  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00407199  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0040719a  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_4071a0: native, nfs3hp::aidrive::integrate */

/* sub_407380: native, nfs3hp::aidrive::coastAfterFinish */

/* sub_4076b0: native, nfs3hp::aidrive::steerOnRoad */

/* sub_407c30: native, nfs3hp::aidrive::steerReversing */

/* sub_407fa0: native, nfs3hp::aidrive::steerOffRoad */

/* sub_408520: native, nfs3hp::aidrive::rideWithTarget */

/* sub_408600: native, nfs3hp::aidrive::aiPhysics */

/* sub_408870: native, nfs3hp::aidrive::easeLane */

/* sub_4088f0: native, nfs3hp::aidrive::aiStep */

/* sub_408ad0: native, nfs3hp::pursuit::raceStartHook */

/* sub_408ae0: native, nfs3hp::pursuit::raceEndHook */

/* sub_408af0: native, nfs3hp::dead::stub_0x408af0 */

/* sub_408b30: native, nfs3hp::pursuit::roadsideTarget */

/* sub_408bd0: native, nfs3hp::pursuit::countLaneTime */

/* sub_408c50: native, nfs3hp::pursuit::pulledOverTarget */

/* sub_408dc0: native, nfs3hp::pursuit::classSpeedFactor */

/* sub_408f00: native, nfs3hp::pursuit::unitFactor */

/* sub_408f10: native, nfs3hp::pursuit::radarFactor */

/* sub_409090: native, nfs3hp::pursuit::unitFactorToo */

/* sub_4090a0: native, nfs3hp::pursuit::leaderFactor */

/* sub_409290: native, nfs3hp::pursuit::nodeTargetSpeed */

/* sub_4092f0: native, nfs3hp::pursuit::markChased */

/* sub_409330: native, nfs3hp::pursuit::targetSpeed */

/* sub_4094b0: native, nfs3hp::pursuit::targetSpeedOnly */

/* sub_4094ba: native, nfs3hp::dead::stub_0x4094ba */

/* sub_4094d0: native, nfs3hp::pursuit::matchChasedSpeed */

/* sub_4095d0: native, nfs3hp::pursuit::scoreCloseCops */

/* sub_409660: native, nfs3hp::pursuit::growLaneTimes */

/* sub_4096b0: native, nfs3hp::pursuit::scoreLane */

/* sub_4097c0: native, nfs3hp::pursuit::scoreChases */

/* sub_409840: native, nfs3hp::pursuit::radioChaseCount */

/* sub_409920: native, nfs3hp::pursuit::scoreSpeeds */

/* sub_409a80: native, nfs3hp::pursuit::alwaysOne */

/* sub_409a90: native, nfs3hp::pursuit::takeOverCars */

/* sub_409b40: native, nfs3hp::pursuit::startReset */

/* sub_409b70: native, nfs3hp::pursuit::checkProgress */

/* sub_409c00: native, nfs3hp::pursuit::copStep */

/* sub_40a010: native, nfs3hp::pursuit::loadRacerBanks */

/* sub_40a330: native, nfs3hp::pursuit::countRadioFrames */

/* sub_40a380: native, nfs3hp::pursuit::radioNoise */

/* sub_40a410: native, nfs3hp::pursuit::sayPhrase */

/* sub_40a580: native, nfs3hp::pursuit::sayCarPhrase */

/* sub_40a6d0: native, nfs3hp::pursuit::namePhrase */

/* sub_40a6f0: native, nfs3hp::pursuit::namePhrases */

/* sub_40a910: native, nfs3hp::pursuit::radioFree */

/* sub_40a940: native, nfs3hp::pursuit::radioNothing */

/* sub_40a950: native, nfs3hp::pursuit::quietVoice */

/* sub_40a970: native, nfs3hp::pursuit::sayVoicePhrase */

/* sub_40aa20: native, nfs3hp::pursuit::sayCallSign */

/* sub_40aa70: native, nfs3hp::pursuit::sayPhraseOnly */

/* sub_40aa90: native, nfs3hp::pursuit::sayUnit */

/* sub_40ab20: native, nfs3hp::pursuit::sayDescription */

/* sub_40aea0: native, nfs3hp::pursuit::radioNothingToo */

/* sub_40aeb0: native, nfs3hp::pursuit::sayLocation */

/* sub_40b190: native, nfs3hp::pursuit::saySpeed */

/* sub_40b220: native, nfs3hp::pursuit::radioSpotted */

/* sub_40b330: native, nfs3hp::pursuit::radioPursuit */

/* sub_40b480: native, nfs3hp::pursuit::radioLost */

/* sub_40b530: native, nfs3hp::pursuit::radioBackup */

/* sub_40b670: native, nfs3hp::pursuit::radioPatrol */

/* sub_40b720: native, nfs3hp::pursuit::radioRoadblock */

/* sub_40b7f0: native, nfs3hp::pursuit::radioNothingThree */

/* sub_40b7f9: native, nfs3hp::dead::stub_0x40b7f9 */

/* sub_40b860: native, nfs3hp::pursuit::radioTicket */

/* sub_40b910: native, nfs3hp::pursuit::radioArrest */

/* sub_40b9c0: native, nfs3hp::pursuit::radioStopped */

/* sub_40bac0: native, nfs3hp::pursuit::radioAmbulance */

/* sub_40bba0: native, nfs3hp::pursuit::radioSpikes */

/* sub_40bc30: native, nfs3hp::pursuit::radioHelp */

}
