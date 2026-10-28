#include "nfs3hp.h"
#include <lib/thread.h>

namespace nfs3hp
{
// Port (tools/apply_native_frontend.py): defined in native_frontend_options.cpp.
bool audioSpeechMoved(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_options.cpp.
bool audioEngineMoved(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_options.cpp.
bool audioEffectsMoved(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_options.cpp.
bool audioRaceMusicMoved(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_options.cpp.
bool audioVolumeDraw(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_options.cpp.
bool audioOnFrame(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_options.cpp.
bool audioOnExit(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_options.cpp.
bool audioOnEnter(win32::WinApplication* app, x86::CPU& cpu);

/* align: skip 0x90 */
void Application::sub_4379b0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (audioRaceMusicMoved(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 004379b0  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004379b1  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004379b2  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004379b4  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 004379b6  e8f54f0300             -call 0x46c9b0
    cpu.esp -= 4;
    nfs3hp::frontend::sliderValue(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004379bb  dc0d80755300           -fmul qword ptr [0x537580]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = cpu.fpu.st(0);
    x86::Float fpu2 = cpu.fpu.mul(fpu1, x86::Float(app->getMemory<double>(x86::reg32(5469568) /* 0x537580 */)));
    cpu.fpu.st(0) = fpu2;
    }
    // 004379c1  e890830a00             -call 0x4dfd56
    cpu.esp -= 4;
    nfs3hp::watcom::CHP(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004379c6  db1df0bb6f00           -fistp dword ptr [0x6fbbf0]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu3 = cpu.fpu.st(0);
    app->getMemory<x86::reg32>(x86::reg32(7322608) /* 0x6fbbf0 */) = x86::reg32(cpu.fpu.toInteger<x86::sreg32>(fpu3));
    // 004379cc  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004379cd  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    cpu.fpu.count -= 1;
    }
    // 004379ce  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x90 */
void Application::sub_4379d0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (audioEffectsMoved(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 004379d0  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004379d1  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004379d2  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004379d4  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 004379d7  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 004379d9  e8d24f0300             -call 0x46c9b0
    cpu.esp -= 4;
    nfs3hp::frontend::sliderValue(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004379de  8b1534925500           -mov edx, dword ptr [0x559234]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5607988) /* 0x559234 */);
    // 004379e4  d95dfc                 -fstp dword ptr [ebp - 4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = cpu.fpu.st(0);
    app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = float(fpu1);
    // 004379e7  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    cpu.fpu.count -= 1;
    }
    // 004379e9  7519                   -jne 0x437a04
    if (!cpu.flags.zf)
    {
        goto L_0x00437a04;
    }
    // 004379eb  d945fc                 -fld dword ptr [ebp - 4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu2 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */));
    // 004379ee  dc0d88755300           -fmul qword ptr [0x537588]
    x86::Float fpu3 = cpu.fpu.mul(fpu2, x86::Float(app->getMemory<double>(x86::reg32(5469576) /* 0x537588 */)));
    cpu.fpu.count += 1;
    cpu.fpu.st(0) = fpu3;
    }
    // 004379f4  e85d830a00             -call 0x4dfd56
    cpu.esp -= 4;
    nfs3hp::watcom::CHP(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004379f9  db1df4bb6f00           -fistp dword ptr [0x6fbbf4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu4 = cpu.fpu.st(0);
    app->getMemory<x86::reg32>(x86::reg32(7322612) /* 0x6fbbf4 */) = x86::reg32(cpu.fpu.toInteger<x86::sreg32>(fpu4));
    // 004379ff  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00437a01  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00437a02  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    cpu.fpu.count -= 1;
    }
    // 00437a03  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x00437a04:
    // 00437a04  d945fc                 -fld dword ptr [ebp - 4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu5 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */));
    // 00437a07  dc0d88755300           -fmul qword ptr [0x537588]
    x86::Float fpu6 = cpu.fpu.mul(fpu5, x86::Float(app->getMemory<double>(x86::reg32(5469576) /* 0x537588 */)));
    cpu.fpu.count += 1;
    cpu.fpu.st(0) = fpu6;
    }
    // 00437a0d  e844830a00             -call 0x4dfd56
    cpu.esp -= 4;
    nfs3hp::watcom::CHP(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00437a12  db1d20295500           -fistp dword ptr [0x552920]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu7 = cpu.fpu.st(0);
    app->getMemory<x86::reg32>(x86::reg32(5581088) /* 0x552920 */) = x86::reg32(cpu.fpu.toInteger<x86::sreg32>(fpu7));
    // 00437a18  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00437a1a  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00437a1b  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    cpu.fpu.count -= 1;
    }
    // 00437a1c  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x40 0x00 */
void Application::sub_437a20(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (audioEngineMoved(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 00437a20  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00437a21  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00437a22  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00437a24  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 00437a27  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00437a29  e8824f0300             -call 0x46c9b0
    cpu.esp -= 4;
    nfs3hp::frontend::sliderValue(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00437a2e  8b1534925500           -mov edx, dword ptr [0x559234]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5607988) /* 0x559234 */);
    // 00437a34  d95dfc                 -fstp dword ptr [ebp - 4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = cpu.fpu.st(0);
    app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = float(fpu1);
    // 00437a37  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    cpu.fpu.count -= 1;
    }
    // 00437a39  7519                   -jne 0x437a54
    if (!cpu.flags.zf)
    {
        goto L_0x00437a54;
    }
    // 00437a3b  d945fc                 -fld dword ptr [ebp - 4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu2 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */));
    // 00437a3e  dc0d90755300           -fmul qword ptr [0x537590]
    x86::Float fpu3 = cpu.fpu.mul(fpu2, x86::Float(app->getMemory<double>(x86::reg32(5469584) /* 0x537590 */)));
    cpu.fpu.count += 1;
    cpu.fpu.st(0) = fpu3;
    }
    // 00437a44  e80d830a00             -call 0x4dfd56
    cpu.esp -= 4;
    nfs3hp::watcom::CHP(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00437a49  db1df8bb6f00           -fistp dword ptr [0x6fbbf8]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu4 = cpu.fpu.st(0);
    app->getMemory<x86::reg32>(x86::reg32(7322616) /* 0x6fbbf8 */) = x86::reg32(cpu.fpu.toInteger<x86::sreg32>(fpu4));
    // 00437a4f  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00437a51  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00437a52  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    cpu.fpu.count -= 1;
    }
    // 00437a53  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x00437a54:
    // 00437a54  d945fc                 -fld dword ptr [ebp - 4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu5 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */));
    // 00437a57  dc0d90755300           -fmul qword ptr [0x537590]
    x86::Float fpu6 = cpu.fpu.mul(fpu5, x86::Float(app->getMemory<double>(x86::reg32(5469584) /* 0x537590 */)));
    cpu.fpu.count += 1;
    cpu.fpu.st(0) = fpu6;
    }
    // 00437a5d  e8f4820a00             -call 0x4dfd56
    cpu.esp -= 4;
    nfs3hp::watcom::CHP(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00437a62  db1d24295500           -fistp dword ptr [0x552924]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu7 = cpu.fpu.st(0);
    app->getMemory<x86::reg32>(x86::reg32(5581092) /* 0x552924 */) = x86::reg32(cpu.fpu.toInteger<x86::sreg32>(fpu7));
    // 00437a68  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00437a6a  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00437a6b  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    cpu.fpu.count -= 1;
    }
    // 00437a6c  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x40 0x00 */
void Application::sub_437a70(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (audioSpeechMoved(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 00437a70  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00437a71  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00437a72  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00437a74  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00437a76  e8354f0300             -call 0x46c9b0
    cpu.esp -= 4;
    nfs3hp::frontend::sliderValue(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00437a7b  dc0d98755300           -fmul qword ptr [0x537598]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = cpu.fpu.st(0);
    x86::Float fpu2 = cpu.fpu.mul(fpu1, x86::Float(app->getMemory<double>(x86::reg32(5469592) /* 0x537598 */)));
    cpu.fpu.st(0) = fpu2;
    }
    // 00437a81  e8d0820a00             -call 0x4dfd56
    cpu.esp -= 4;
    nfs3hp::watcom::CHP(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00437a86  db1dfcbb6f00           -fistp dword ptr [0x6fbbfc]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu3 = cpu.fpu.st(0);
    app->getMemory<x86::reg32>(x86::reg32(7322620) /* 0x6fbbfc */) = x86::reg32(cpu.fpu.toInteger<x86::sreg32>(fpu3));
    // 00437a8c  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00437a8d  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    cpu.fpu.count -= 1;
    }
    // 00437a8e  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x90 */
void Application::sub_437a90(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (audioVolumeDraw(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 00437a90  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00437a91  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00437a92  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00437a93  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00437a94  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00437a95  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00437a97  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 00437a99  89d7                   -mov edi, edx
    cpu.edi = cpu.edx;
    // 00437a9b  ba0f000000             -mov edx, 0xf
    cpu.edx = 15 /*0xf*/;
    // 00437aa0  e8bb2b0100             -call 0x44a660
    cpu.esp -= 4;
    nfs3hp::frontend::menuShownNow(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00437aa5  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00437aa7  0f8446030000           -je 0x437df3
    if (cpu.flags.zf)
    {
        goto L_0x00437df3;
    }
    // 00437aad  85ff                   +test edi, edi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edi & cpu.edi));
    // 00437aaf  0f8479020000           -je 0x437d2e
    if (cpu.flags.zf)
    {
        goto L_0x00437d2e;
    }
    // 00437ab5  3b353c4f5500           +cmp esi, dword ptr [0x554f3c]
    {
        x86::reg32 tmp1 = cpu.esi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(5590844) /* 0x554f3c */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00437abb  7559                   -jne 0x437b16
    if (!cpu.flags.zf)
    {
        goto L_0x00437b16;
    }
    // 00437abd  8b0d244f5500           -mov ecx, dword ptr [0x554f24]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(5590820) /* 0x554f24 */);
    // 00437ac3  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    // 00437ac5  752d                   -jne 0x437af4
    if (!cpu.flags.zf)
    {
        goto L_0x00437af4;
    }
    // 00437ac7  833d3492550000         +cmp dword ptr [0x559234], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5607988) /* 0x559234 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00437ace  751a                   -jne 0x437aea
    if (!cpu.flags.zf)
    {
        goto L_0x00437aea;
    }
    // 00437ad0  bbffffffff             -mov ebx, 0xffffffff
    cpu.ebx = 4294967295 /*0xffffffff*/;
    // 00437ad5  ba05000000             -mov edx, 5
    cpu.edx = 5 /*0x5*/;
    // 00437ada  a1384f5500             -mov eax, dword ptr [0x554f38]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5590840) /* 0x554f38 */);
    // 00437adf  e83c190b00             -call 0x4e9420
    cpu.esp -= 4;
    nfs3hp::port::SNDautovol(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00437ae4  890d384f5500           -mov dword ptr [0x554f38], ecx
    app->getMemory<x86::reg32>(x86::reg32(5590840) /* 0x554f38 */) = cpu.ecx;
L_0x00437aea:
    // 00437aea  c705244f550001000000   -mov dword ptr [0x554f24], 1
    app->getMemory<x86::reg32>(x86::reg32(5590820) /* 0x554f24 */) = 1 /*0x1*/;
L_0x00437af4:
    // 00437af4  833d3492550000         +cmp dword ptr [0x559234], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5607988) /* 0x559234 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00437afb  0f8583020000           -jne 0x437d84
    if (!cpu.flags.zf)
    {
        goto L_0x00437d84;
    }
    // 00437b01  b80a000000             -mov eax, 0xa
    cpu.eax = 10 /*0xa*/;
    // 00437b06  8b15e8bb6f00           -mov edx, dword ptr [0x6fbbe8]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(7322600) /* 0x6fbbe8 */);
    // 00437b0c  e85ff90a00             -call 0x4e7470
    cpu.esp -= 4;
    nfs3hp::snd::SNDstreamautovol(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00437b11  e96e020000             -jmp 0x437d84
    goto L_0x00437d84;
L_0x00437b16:
    // 00437b16  3b35404f5500           +cmp esi, dword ptr [0x554f40]
    {
        x86::reg32 tmp1 = cpu.esi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(5590848) /* 0x554f40 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00437b1c  755a                   -jne 0x437b78
    if (!cpu.flags.zf)
    {
        goto L_0x00437b78;
    }
    // 00437b1e  833d204f550000         +cmp dword ptr [0x554f20], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5590816) /* 0x554f20 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00437b25  752f                   -jne 0x437b56
    if (!cpu.flags.zf)
    {
        goto L_0x00437b56;
    }
    // 00437b27  833d3492550000         +cmp dword ptr [0x559234], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5607988) /* 0x559234 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00437b2e  751c                   -jne 0x437b4c
    if (!cpu.flags.zf)
    {
        goto L_0x00437b4c;
    }
    // 00437b30  bbffffffff             -mov ebx, 0xffffffff
    cpu.ebx = 4294967295 /*0xffffffff*/;
    // 00437b35  ba05000000             -mov edx, 5
    cpu.edx = 5 /*0x5*/;
    // 00437b3a  a1384f5500             -mov eax, dword ptr [0x554f38]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5590840) /* 0x554f38 */);
    // 00437b3f  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 00437b41  e8da180b00             -call 0x4e9420
    cpu.esp -= 4;
    nfs3hp::port::SNDautovol(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00437b46  890d384f5500           -mov dword ptr [0x554f38], ecx
    app->getMemory<x86::reg32>(x86::reg32(5590840) /* 0x554f38 */) = cpu.ecx;
L_0x00437b4c:
    // 00437b4c  c705204f550001000000   -mov dword ptr [0x554f20], 1
    app->getMemory<x86::reg32>(x86::reg32(5590816) /* 0x554f20 */) = 1 /*0x1*/;
L_0x00437b56:
    // 00437b56  833d3492550000         +cmp dword ptr [0x559234], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5607988) /* 0x559234 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00437b5d  0f8521020000           -jne 0x437d84
    if (!cpu.flags.zf)
    {
        goto L_0x00437d84;
    }
    // 00437b63  b80a000000             -mov eax, 0xa
    cpu.eax = 10 /*0xa*/;
    // 00437b68  8b15f0bb6f00           -mov edx, dword ptr [0x6fbbf0]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(7322608) /* 0x6fbbf0 */);
    // 00437b6e  e8fdf80a00             -call 0x4e7470
    cpu.esp -= 4;
    nfs3hp::snd::SNDstreamautovol(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00437b73  e90c020000             -jmp 0x437d84
    goto L_0x00437d84;
L_0x00437b78:
    // 00437b78  3b35444f5500           +cmp esi, dword ptr [0x554f44]
    {
        x86::reg32 tmp1 = cpu.esi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(5590852) /* 0x554f44 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00437b7e  0f8587000000           -jne 0x437c0b
    if (!cpu.flags.zf)
    {
        goto L_0x00437c0b;
    }
    // 00437b84  833d284f550000         +cmp dword ptr [0x554f28], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5590824) /* 0x554f28 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00437b8b  7554                   -jne 0x437be1
    if (!cpu.flags.zf)
    {
        goto L_0x00437be1;
    }
    // 00437b8d  833d3492550000         +cmp dword ptr [0x559234], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5607988) /* 0x559234 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00437b94  7510                   -jne 0x437ba6
    if (!cpu.flags.zf)
    {
        goto L_0x00437ba6;
    }
    // 00437b96  b80a000000             -mov eax, 0xa
    cpu.eax = 10 /*0xa*/;
    // 00437b9b  8b15f0bb6f00           -mov edx, dword ptr [0x6fbbf0]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(7322608) /* 0x6fbbf0 */);
    // 00437ba1  e8caf80a00             -call 0x4e7470
    cpu.esp -= 4;
    nfs3hp::snd::SNDstreamautovol(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00437ba6:
    // 00437ba6  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 00437bab  8b1534925500           -mov edx, dword ptr [0x559234]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5607988) /* 0x559234 */);
    // 00437bb1  a3284f5500             -mov dword ptr [0x554f28], eax
    app->getMemory<x86::reg32>(x86::reg32(5590824) /* 0x554f28 */) = cpu.eax;
    // 00437bb6  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 00437bb8  7527                   -jne 0x437be1
    if (!cpu.flags.zf)
    {
        goto L_0x00437be1;
    }
    // 00437bba  833d384f550000         +cmp dword ptr [0x554f38], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5590840) /* 0x554f38 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00437bc1  751e                   -jne 0x437be1
    if (!cpu.flags.zf)
    {
        goto L_0x00437be1;
    }
    // 00437bc3  6a40                   -push 0x40
    app->getMemory<x86::reg32>(cpu.esp-4) = 64 /*0x40*/;
    cpu.esp -= 4;
    // 00437bc5  ba07000000             -mov edx, 7
    cpu.edx = 7 /*0x7*/;
    // 00437bca  8b0df4bb6f00           -mov ecx, dword ptr [0x6fbbf4]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(7322612) /* 0x6fbbf4 */);
    // 00437bd0  a124115700             -mov eax, dword ptr [0x571124]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5706020) /* 0x571124 */);
    // 00437bd5  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
    // 00437bd7  e8d406feff             -call 0x4182b0
    cpu.esp -= 4;
    nfs3hp::port::playEffect(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00437bdc  a3384f5500             -mov dword ptr [0x554f38], eax
    app->getMemory<x86::reg32>(x86::reg32(5590840) /* 0x554f38 */) = cpu.eax;
L_0x00437be1:
    // 00437be1  833d3492550000         +cmp dword ptr [0x559234], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5607988) /* 0x559234 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00437be8  0f8596010000           -jne 0x437d84
    if (!cpu.flags.zf)
    {
        goto L_0x00437d84;
    }
    // 00437bee  a1384f5500             -mov eax, dword ptr [0x554f38]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5590840) /* 0x554f38 */);
    // 00437bf3  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00437bf5  0f8489010000           -je 0x437d84
    if (cpu.flags.zf)
    {
        goto L_0x00437d84;
    }
    // 00437bfb  8b15f4bb6f00           -mov edx, dword ptr [0x6fbbf4]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(7322612) /* 0x6fbbf4 */);
    // 00437c01  e8f6190b00             -call 0x4e95fc
    cpu.esp -= 4;
    nfs3hp::port::SNDvol(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00437c06  e979010000             -jmp 0x437d84
    goto L_0x00437d84;
L_0x00437c0b:
    // 00437c0b  3b35484f5500           +cmp esi, dword ptr [0x554f48]
    {
        x86::reg32 tmp1 = cpu.esi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(5590856) /* 0x554f48 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00437c11  0f8587000000           -jne 0x437c9e
    if (!cpu.flags.zf)
    {
        goto L_0x00437c9e;
    }
    // 00437c17  833d2c4f550000         +cmp dword ptr [0x554f2c], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5590828) /* 0x554f2c */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00437c1e  7554                   -jne 0x437c74
    if (!cpu.flags.zf)
    {
        goto L_0x00437c74;
    }
    // 00437c20  833d3492550000         +cmp dword ptr [0x559234], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5607988) /* 0x559234 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00437c27  7510                   -jne 0x437c39
    if (!cpu.flags.zf)
    {
        goto L_0x00437c39;
    }
    // 00437c29  b80a000000             -mov eax, 0xa
    cpu.eax = 10 /*0xa*/;
    // 00437c2e  8b15f0bb6f00           -mov edx, dword ptr [0x6fbbf0]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(7322608) /* 0x6fbbf0 */);
    // 00437c34  e837f80a00             -call 0x4e7470
    cpu.esp -= 4;
    nfs3hp::snd::SNDstreamautovol(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00437c39:
    // 00437c39  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 00437c3e  8b1534925500           -mov edx, dword ptr [0x559234]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5607988) /* 0x559234 */);
    // 00437c44  a32c4f5500             -mov dword ptr [0x554f2c], eax
    app->getMemory<x86::reg32>(x86::reg32(5590828) /* 0x554f2c */) = cpu.eax;
    // 00437c49  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 00437c4b  7527                   -jne 0x437c74
    if (!cpu.flags.zf)
    {
        goto L_0x00437c74;
    }
    // 00437c4d  833d384f550000         +cmp dword ptr [0x554f38], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5590840) /* 0x554f38 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00437c54  751e                   -jne 0x437c74
    if (!cpu.flags.zf)
    {
        goto L_0x00437c74;
    }
    // 00437c56  6a40                   -push 0x40
    app->getMemory<x86::reg32>(cpu.esp-4) = 64 /*0x40*/;
    cpu.esp -= 4;
    // 00437c58  ba07000000             -mov edx, 7
    cpu.edx = 7 /*0x7*/;
    // 00437c5d  8b0df8bb6f00           -mov ecx, dword ptr [0x6fbbf8]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(7322616) /* 0x6fbbf8 */);
    // 00437c63  a124115700             -mov eax, dword ptr [0x571124]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5706020) /* 0x571124 */);
    // 00437c68  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
    // 00437c6a  e84106feff             -call 0x4182b0
    cpu.esp -= 4;
    nfs3hp::port::playEffect(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00437c6f  a3384f5500             -mov dword ptr [0x554f38], eax
    app->getMemory<x86::reg32>(x86::reg32(5590840) /* 0x554f38 */) = cpu.eax;
L_0x00437c74:
    // 00437c74  833d3492550000         +cmp dword ptr [0x559234], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5607988) /* 0x559234 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00437c7b  0f8503010000           -jne 0x437d84
    if (!cpu.flags.zf)
    {
        goto L_0x00437d84;
    }
    // 00437c81  a1384f5500             -mov eax, dword ptr [0x554f38]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5590840) /* 0x554f38 */);
    // 00437c86  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00437c88  0f84f6000000           -je 0x437d84
    if (cpu.flags.zf)
    {
        goto L_0x00437d84;
    }
    // 00437c8e  8b15f8bb6f00           -mov edx, dword ptr [0x6fbbf8]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(7322616) /* 0x6fbbf8 */);
    // 00437c94  e863190b00             -call 0x4e95fc
    cpu.esp -= 4;
    nfs3hp::port::SNDvol(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00437c99  e9e6000000             -jmp 0x437d84
    goto L_0x00437d84;
L_0x00437c9e:
    // 00437c9e  3b354c4f5500           +cmp esi, dword ptr [0x554f4c]
    {
        x86::reg32 tmp1 = cpu.esi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(5590860) /* 0x554f4c */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00437ca4  0f85da000000           -jne 0x437d84
    if (!cpu.flags.zf)
    {
        goto L_0x00437d84;
    }
    // 00437caa  833d304f550000         +cmp dword ptr [0x554f30], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5590832) /* 0x554f30 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00437cb1  7554                   -jne 0x437d07
    if (!cpu.flags.zf)
    {
        goto L_0x00437d07;
    }
    // 00437cb3  833d3492550000         +cmp dword ptr [0x559234], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5607988) /* 0x559234 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00437cba  7510                   -jne 0x437ccc
    if (!cpu.flags.zf)
    {
        goto L_0x00437ccc;
    }
    // 00437cbc  b80a000000             -mov eax, 0xa
    cpu.eax = 10 /*0xa*/;
    // 00437cc1  8b15f0bb6f00           -mov edx, dword ptr [0x6fbbf0]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(7322608) /* 0x6fbbf0 */);
    // 00437cc7  e8a4f70a00             -call 0x4e7470
    cpu.esp -= 4;
    nfs3hp::snd::SNDstreamautovol(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00437ccc:
    // 00437ccc  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 00437cd1  8b1534925500           -mov edx, dword ptr [0x559234]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5607988) /* 0x559234 */);
    // 00437cd7  a3304f5500             -mov dword ptr [0x554f30], eax
    app->getMemory<x86::reg32>(x86::reg32(5590832) /* 0x554f30 */) = cpu.eax;
    // 00437cdc  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 00437cde  7527                   -jne 0x437d07
    if (!cpu.flags.zf)
    {
        goto L_0x00437d07;
    }
    // 00437ce0  833d384f550000         +cmp dword ptr [0x554f38], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5590840) /* 0x554f38 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00437ce7  751e                   -jne 0x437d07
    if (!cpu.flags.zf)
    {
        goto L_0x00437d07;
    }
    // 00437ce9  6a40                   -push 0x40
    app->getMemory<x86::reg32>(cpu.esp-4) = 64 /*0x40*/;
    cpu.esp -= 4;
    // 00437ceb  ba07000000             -mov edx, 7
    cpu.edx = 7 /*0x7*/;
    // 00437cf0  8b0dfcbb6f00           -mov ecx, dword ptr [0x6fbbfc]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(7322620) /* 0x6fbbfc */);
    // 00437cf6  a124115700             -mov eax, dword ptr [0x571124]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5706020) /* 0x571124 */);
    // 00437cfb  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
    // 00437cfd  e8ae05feff             -call 0x4182b0
    cpu.esp -= 4;
    nfs3hp::port::playEffect(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00437d02  a3384f5500             -mov dword ptr [0x554f38], eax
    app->getMemory<x86::reg32>(x86::reg32(5590840) /* 0x554f38 */) = cpu.eax;
L_0x00437d07:
    // 00437d07  833d3492550000         +cmp dword ptr [0x559234], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5607988) /* 0x559234 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00437d0e  0f8570000000           -jne 0x437d84
    if (!cpu.flags.zf)
    {
        goto L_0x00437d84;
    }
    // 00437d14  a1384f5500             -mov eax, dword ptr [0x554f38]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5590840) /* 0x554f38 */);
    // 00437d19  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00437d1b  0f8463000000           -je 0x437d84
    if (cpu.flags.zf)
    {
        goto L_0x00437d84;
    }
    // 00437d21  8b15fcbb6f00           -mov edx, dword ptr [0x6fbbfc]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(7322620) /* 0x6fbbfc */);
    // 00437d27  e8d0180b00             -call 0x4e95fc
    cpu.esp -= 4;
    nfs3hp::port::SNDvol(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00437d2c  eb56                   -jmp 0x437d84
    goto L_0x00437d84;
L_0x00437d2e:
    // 00437d2e  3b353c4f5500           +cmp esi, dword ptr [0x554f3c]
    {
        x86::reg32 tmp1 = cpu.esi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(5590844) /* 0x554f3c */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00437d34  750a                   -jne 0x437d40
    if (!cpu.flags.zf)
    {
        goto L_0x00437d40;
    }
    // 00437d36  31c9                   +xor ecx, ecx
    cpu.clear_co();
    cpu.set_szp((cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx))));
    // 00437d38  890d244f5500           -mov dword ptr [0x554f24], ecx
    app->getMemory<x86::reg32>(x86::reg32(5590820) /* 0x554f24 */) = cpu.ecx;
    // 00437d3e  eb44                   -jmp 0x437d84
    goto L_0x00437d84;
L_0x00437d40:
    // 00437d40  3b35404f5500           +cmp esi, dword ptr [0x554f40]
    {
        x86::reg32 tmp1 = cpu.esi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(5590848) /* 0x554f40 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00437d46  7509                   -jne 0x437d51
    if (!cpu.flags.zf)
    {
        goto L_0x00437d51;
    }
    // 00437d48  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
    // 00437d4a  a3204f5500             -mov dword ptr [0x554f20], eax
    app->getMemory<x86::reg32>(x86::reg32(5590816) /* 0x554f20 */) = cpu.eax;
    // 00437d4f  eb33                   -jmp 0x437d84
    goto L_0x00437d84;
L_0x00437d51:
    // 00437d51  3b35444f5500           +cmp esi, dword ptr [0x554f44]
    {
        x86::reg32 tmp1 = cpu.esi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(5590852) /* 0x554f44 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00437d57  750a                   -jne 0x437d63
    if (!cpu.flags.zf)
    {
        goto L_0x00437d63;
    }
    // 00437d59  31c9                   +xor ecx, ecx
    cpu.clear_co();
    cpu.set_szp((cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx))));
    // 00437d5b  890d284f5500           -mov dword ptr [0x554f28], ecx
    app->getMemory<x86::reg32>(x86::reg32(5590824) /* 0x554f28 */) = cpu.ecx;
    // 00437d61  eb21                   -jmp 0x437d84
    goto L_0x00437d84;
L_0x00437d63:
    // 00437d63  3b35484f5500           +cmp esi, dword ptr [0x554f48]
    {
        x86::reg32 tmp1 = cpu.esi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(5590856) /* 0x554f48 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00437d69  7509                   -jne 0x437d74
    if (!cpu.flags.zf)
    {
        goto L_0x00437d74;
    }
    // 00437d6b  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
    // 00437d6d  a32c4f5500             -mov dword ptr [0x554f2c], eax
    app->getMemory<x86::reg32>(x86::reg32(5590828) /* 0x554f2c */) = cpu.eax;
    // 00437d72  eb10                   -jmp 0x437d84
    goto L_0x00437d84;
L_0x00437d74:
    // 00437d74  3b354c4f5500           +cmp esi, dword ptr [0x554f4c]
    {
        x86::reg32 tmp1 = cpu.esi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(5590860) /* 0x554f4c */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00437d7a  7508                   -jne 0x437d84
    if (!cpu.flags.zf)
    {
        goto L_0x00437d84;
    }
    // 00437d7c  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 00437d7e  890d304f5500           -mov dword ptr [0x554f30], ecx
    app->getMemory<x86::reg32>(x86::reg32(5590832) /* 0x554f30 */) = cpu.ecx;
L_0x00437d84:
    // 00437d84  833d244f550000         +cmp dword ptr [0x554f24], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5590820) /* 0x554f24 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00437d8b  0f8559000000           -jne 0x437dea
    if (!cpu.flags.zf)
    {
        goto L_0x00437dea;
    }
    // 00437d91  833d204f550000         +cmp dword ptr [0x554f20], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5590816) /* 0x554f20 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00437d98  7550                   -jne 0x437dea
    if (!cpu.flags.zf)
    {
        goto L_0x00437dea;
    }
    // 00437d9a  833d284f550000         +cmp dword ptr [0x554f28], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5590824) /* 0x554f28 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00437da1  7547                   -jne 0x437dea
    if (!cpu.flags.zf)
    {
        goto L_0x00437dea;
    }
    // 00437da3  833d2c4f550000         +cmp dword ptr [0x554f2c], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5590828) /* 0x554f2c */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00437daa  753e                   -jne 0x437dea
    if (!cpu.flags.zf)
    {
        goto L_0x00437dea;
    }
    // 00437dac  833d304f550000         +cmp dword ptr [0x554f30], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5590832) /* 0x554f30 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00437db3  7535                   -jne 0x437dea
    if (!cpu.flags.zf)
    {
        goto L_0x00437dea;
    }
    // 00437db5  833d3492550000         +cmp dword ptr [0x559234], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5607988) /* 0x559234 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00437dbc  752c                   -jne 0x437dea
    if (!cpu.flags.zf)
    {
        goto L_0x00437dea;
    }
    // 00437dbe  b80a000000             -mov eax, 0xa
    cpu.eax = 10 /*0xa*/;
    // 00437dc3  8b15e8bb6f00           -mov edx, dword ptr [0x6fbbe8]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(7322600) /* 0x6fbbe8 */);
    // 00437dc9  bbffffffff             -mov ebx, 0xffffffff
    cpu.ebx = 4294967295 /*0xffffffff*/;
    // 00437dce  e89df60a00             -call 0x4e7470
    cpu.esp -= 4;
    nfs3hp::snd::SNDstreamautovol(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00437dd3  ba05000000             -mov edx, 5
    cpu.edx = 5 /*0x5*/;
    // 00437dd8  a1384f5500             -mov eax, dword ptr [0x554f38]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5590840) /* 0x554f38 */);
    // 00437ddd  e83e160b00             -call 0x4e9420
    cpu.esp -= 4;
    nfs3hp::port::SNDautovol(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00437de2  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00437de4  8915384f5500           -mov dword ptr [0x554f38], edx
    app->getMemory<x86::reg32>(x86::reg32(5590840) /* 0x554f38 */) = cpu.edx;
L_0x00437dea:
    // 00437dea  89fa                   -mov edx, edi
    cpu.edx = cpu.edi;
    // 00437dec  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 00437dee  e8ed4c0300             -call 0x46cae0
    cpu.esp -= 4;
    nfs3hp::port::fields::sliderDraw(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00437df3:
    // 00437df3  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00437df4  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00437df5  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00437df6  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00437df7  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00437df8  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x90 */
void Application::sub_437e00(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (audioOnEnter(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 00437e00  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00437e01  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00437e02  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00437e03  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00437e04  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00437e05  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00437e07  83ec10                 -sub esp, 0x10
    (cpu.esp) -= x86::reg32(x86::sreg32(16 /*0x10*/));
    // 00437e0a  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00437e0c  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00437e0e  0f844f020000           -je 0x438063
    if (cpu.flags.zf)
    {
        goto L_0x00438063;
    }
    // 00437e14  833d3492550000         +cmp dword ptr [0x559234], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5607988) /* 0x559234 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00437e1b  740a                   -je 0x437e27
    if (cpu.flags.zf)
    {
        goto L_0x00437e27;
    }
    // 00437e1d  689a99193f             -push 0x3f19999a
    app->getMemory<x86::reg32>(cpu.esp-4) = 1058642330 /*0x3f19999a*/;
    cpu.esp -= 4;
    // 00437e22  e809970100             -call 0x451530
    cpu.esp -= 4;
    nfs3hp::port::text::dimBackground(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00437e27:
    // 00437e27  e8c47cfdff             -call 0x40faf0
    cpu.esp -= 4;
    nfs3hp::Is3DSoundAvailable(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00437e2c  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00437e2e  7509                   -jne 0x437e39
    if (!cpu.flags.zf)
    {
        goto L_0x00437e39;
    }
    // 00437e30  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00437e32  6689156a635500         -mov word ptr [0x55636a], dx
    app->getMemory<x86::reg16>(x86::reg32(5596010) /* 0x55636a */) = cpu.dx;
L_0x00437e39:
    // 00437e39  833d3492550000         +cmp dword ptr [0x559234], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5607988) /* 0x559234 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00437e40  751d                   -jne 0x437e5f
    if (!cpu.flags.zf)
    {
        goto L_0x00437e5f;
    }
    // 00437e42  baa0755300             -mov edx, 0x5375a0
    cpu.edx = 5469600 /*0x5375a0*/;
    // 00437e47  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00437e49  e8f2ab0000             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00437e4e  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00437e50  740d                   -je 0x437e5f
    if (cpu.flags.zf)
    {
        goto L_0x00437e5f;
    }
    // 00437e52  833db0d36f0001         +cmp dword ptr [0x6fd3b0], 1
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
    // 00437e59  7e04                   -jle 0x437e5f
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00437e5f;
    }
    // 00437e5b  80480401               -or byte ptr [eax + 4], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(4) /* 0x4 */) |= x86::reg8(x86::sreg8(1 /*0x1*/));
L_0x00437e5f:
    // 00437e5f  baa8755300             -mov edx, 0x5375a8
    cpu.edx = 5469608 /*0x5375a8*/;
    // 00437e64  a100bc6f00             -mov eax, dword ptr [0x6fbc00]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(7322624) /* 0x6fbc00 */);
    // 00437e69  31ff                   -xor edi, edi
    cpu.edi ^= x86::reg32(x86::sreg32(cpu.edi));
    // 00437e6b  a370395f00             -mov dword ptr [0x5f3970], eax
    app->getMemory<x86::reg32>(x86::reg32(6240624) /* 0x5f3970 */) = cpu.eax;
    // 00437e70  893d204f5500           -mov dword ptr [0x554f20], edi
    app->getMemory<x86::reg32>(x86::reg32(5590816) /* 0x554f20 */) = cpu.edi;
    // 00437e76  893d244f5500           -mov dword ptr [0x554f24], edi
    app->getMemory<x86::reg32>(x86::reg32(5590820) /* 0x554f24 */) = cpu.edi;
    // 00437e7c  893d284f5500           -mov dword ptr [0x554f28], edi
    app->getMemory<x86::reg32>(x86::reg32(5590824) /* 0x554f28 */) = cpu.edi;
    // 00437e82  a1e4bb6f00             -mov eax, dword ptr [0x6fbbe4]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(7322596) /* 0x6fbbe4 */);
    // 00437e87  893d2c4f5500           -mov dword ptr [0x554f2c], edi
    app->getMemory<x86::reg32>(x86::reg32(5590828) /* 0x554f2c */) = cpu.edi;
    // 00437e8d  a368395f00             -mov dword ptr [0x5f3968], eax
    app->getMemory<x86::reg32>(x86::reg32(6240616) /* 0x5f3968 */) = cpu.eax;
    // 00437e92  a1ecbb6f00             -mov eax, dword ptr [0x6fbbec]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(7322604) /* 0x6fbbec */);
    // 00437e97  893d304f5500           -mov dword ptr [0x554f30], edi
    app->getMemory<x86::reg32>(x86::reg32(5590832) /* 0x554f30 */) = cpu.edi;
    // 00437e9d  a364395f00             -mov dword ptr [0x5f3964], eax
    app->getMemory<x86::reg32>(x86::reg32(6240612) /* 0x5f3964 */) = cpu.eax;
    // 00437ea2  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00437ea4  893d384f5500           -mov dword ptr [0x554f38], edi
    app->getMemory<x86::reg32>(x86::reg32(5590840) /* 0x554f38 */) = cpu.edi;
    // 00437eaa  e891ab0000             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00437eaf  a33c4f5500             -mov dword ptr [0x554f3c], eax
    app->getMemory<x86::reg32>(x86::reg32(5590844) /* 0x554f3c */) = cpu.eax;
    // 00437eb4  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00437eb6  742e                   -je 0x437ee6
    if (cpu.flags.zf)
    {
        goto L_0x00437ee6;
    }
    // 00437eb8  db05e8bb6f00           -fild dword ptr [0x6fbbe8]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(7322600) /* 0x6fbbe8 */)));
    // 00437ebe  dc0d00765300           -fmul qword ptr [0x537600]
    x86::Float fpu2 = cpu.fpu.mul(fpu1, x86::Float(app->getMemory<double>(x86::reg32(5469696) /* 0x537600 */)));
    // 00437ec4  ba90794300             -mov edx, 0x437990
    cpu.edx = 4422032 /*0x437990*/;
    // 00437ec9  c7402c907a4300         -mov dword ptr [eax + 0x2c], 0x437a90
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(44) /* 0x2c */) = 4422288 /*0x437a90*/;
    // 00437ed0  d95df4                 -fstp dword ptr [ebp - 0xc]
    app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */) = float(fpu2);
    }
    // 00437ed3  e8e84b0300             -call 0x46cac0
    cpu.esp -= 4;
    nfs3hp::frontend::sliderSetOnMove(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00437ed8  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00437ed9  a13c4f5500             -mov eax, dword ptr [0x554f3c]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5590844) /* 0x554f3c */);
    // 00437ede  ff75f4                 -push dword ptr [ebp - 0xc]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    cpu.esp -= 4;
    // 00437ee1  e86a4a0300             -call 0x46c950
    cpu.esp -= 4;
    nfs3hp::port::fields::sliderSetValue(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00437ee6:
    // 00437ee6  bab8755300             -mov edx, 0x5375b8
    cpu.edx = 5469624 /*0x5375b8*/;
    // 00437eeb  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00437eed  e84eab0000             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00437ef2  a3404f5500             -mov dword ptr [0x554f40], eax
    app->getMemory<x86::reg32>(x86::reg32(5590848) /* 0x554f40 */) = cpu.eax;
    // 00437ef7  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00437ef9  742f                   -je 0x437f2a
    if (cpu.flags.zf)
    {
        goto L_0x00437f2a;
    }
    // 00437efb  db05f0bb6f00           -fild dword ptr [0x6fbbf0]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu3 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(7322608) /* 0x6fbbf0 */)));
    // 00437f01  dc0d00765300           -fmul qword ptr [0x537600]
    x86::Float fpu4 = cpu.fpu.mul(fpu3, x86::Float(app->getMemory<double>(x86::reg32(5469696) /* 0x537600 */)));
    // 00437f07  bab0794300             -mov edx, 0x4379b0
    cpu.edx = 4422064 /*0x4379b0*/;
    // 00437f0c  c7402c907a4300         -mov dword ptr [eax + 0x2c], 0x437a90
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(44) /* 0x2c */) = 4422288 /*0x437a90*/;
    // 00437f13  d95df0                 -fstp dword ptr [ebp - 0x10]
    app->getMemory<float>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = float(fpu4);
    }
    // 00437f16  e8a54b0300             -call 0x46cac0
    cpu.esp -= 4;
    nfs3hp::frontend::sliderSetOnMove(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00437f1b  6a00                   -push 0
    app->getMemory<x86::reg32>(cpu.esp-4) = 0 /*0x0*/;
    cpu.esp -= 4;
    // 00437f1d  a1404f5500             -mov eax, dword ptr [0x554f40]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5590848) /* 0x554f40 */);
    // 00437f22  ff75f0                 -push dword ptr [ebp - 0x10]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    cpu.esp -= 4;
    // 00437f25  e8264a0300             -call 0x46c950
    cpu.esp -= 4;
    nfs3hp::port::fields::sliderSetValue(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00437f2a:
    // 00437f2a  bac8755300             -mov edx, 0x5375c8
    cpu.edx = 5469640 /*0x5375c8*/;
    // 00437f2f  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00437f31  e80aab0000             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00437f36  a3444f5500             -mov dword ptr [0x554f44], eax
    app->getMemory<x86::reg32>(x86::reg32(5590852) /* 0x554f44 */) = cpu.eax;
    // 00437f3b  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00437f3d  7445                   -je 0x437f84
    if (cpu.flags.zf)
    {
        goto L_0x00437f84;
    }
    // 00437f3f  c7402c907a4300         -mov dword ptr [eax + 0x2c], 0x437a90
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(44) /* 0x2c */) = 4422288 /*0x437a90*/;
    // 00437f46  833d3492550000         +cmp dword ptr [0x559234], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5607988) /* 0x559234 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00437f4d  7508                   -jne 0x437f57
    if (!cpu.flags.zf)
    {
        goto L_0x00437f57;
    }
    // 00437f4f  db05f4bb6f00           +fild dword ptr [0x6fbbf4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu5 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(7322612) /* 0x6fbbf4 */)));
    cpu.fpu.count += 1;
    cpu.fpu.st(0) = fpu5;
    }
    // 00437f55  eb06                   -jmp 0x437f5d
    goto L_0x00437f5d;
L_0x00437f57:
    // 00437f57  db0520295500           -fild dword ptr [0x552920]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu6 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(5581088) /* 0x552920 */)));
    cpu.fpu.count += 1;
    cpu.fpu.st(0) = fpu6;
    }
L_0x00437f5d:
    // 00437f5d  dc0d00765300           -fmul qword ptr [0x537600]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu7 = cpu.fpu.st(0);
    x86::Float fpu8 = cpu.fpu.mul(fpu7, x86::Float(app->getMemory<double>(x86::reg32(5469696) /* 0x537600 */)));
    // 00437f63  d95df8                 -fstp dword ptr [ebp - 8]
    app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = float(fpu8);
    // 00437f66  bad0794300             -mov edx, 0x4379d0
    cpu.edx = 4422096 /*0x4379d0*/;
    // 00437f6b  a1444f5500             -mov eax, dword ptr [0x554f44]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5590852) /* 0x554f44 */);
    cpu.fpu.count -= 1;
    }
    // 00437f70  e84b4b0300             -call 0x46cac0
    cpu.esp -= 4;
    nfs3hp::frontend::sliderSetOnMove(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00437f75  6a00                   -push 0
    app->getMemory<x86::reg32>(cpu.esp-4) = 0 /*0x0*/;
    cpu.esp -= 4;
    // 00437f77  a1444f5500             -mov eax, dword ptr [0x554f44]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5590852) /* 0x554f44 */);
    // 00437f7c  ff75f8                 -push dword ptr [ebp - 8]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    cpu.esp -= 4;
    // 00437f7f  e8cc490300             -call 0x46c950
    cpu.esp -= 4;
    nfs3hp::port::fields::sliderSetValue(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00437f84:
    // 00437f84  bad8755300             -mov edx, 0x5375d8
    cpu.edx = 5469656 /*0x5375d8*/;
    // 00437f89  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00437f8b  e8b0aa0000             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00437f90  a3484f5500             -mov dword ptr [0x554f48], eax
    app->getMemory<x86::reg32>(x86::reg32(5590856) /* 0x554f48 */) = cpu.eax;
    // 00437f95  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00437f97  7446                   -je 0x437fdf
    if (cpu.flags.zf)
    {
        goto L_0x00437fdf;
    }
    // 00437f99  8b1534925500           -mov edx, dword ptr [0x559234]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5607988) /* 0x559234 */);
    // 00437f9f  c7402c907a4300         -mov dword ptr [eax + 0x2c], 0x437a90
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(44) /* 0x2c */) = 4422288 /*0x437a90*/;
    // 00437fa6  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 00437fa8  7508                   -jne 0x437fb2
    if (!cpu.flags.zf)
    {
        goto L_0x00437fb2;
    }
    // 00437faa  db05f8bb6f00           +fild dword ptr [0x6fbbf8]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu9 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(7322616) /* 0x6fbbf8 */)));
    cpu.fpu.count += 1;
    cpu.fpu.st(0) = fpu9;
    }
    // 00437fb0  eb06                   -jmp 0x437fb8
    goto L_0x00437fb8;
L_0x00437fb2:
    // 00437fb2  db0524295500           -fild dword ptr [0x552924]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu10 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(5581092) /* 0x552924 */)));
    cpu.fpu.count += 1;
    cpu.fpu.st(0) = fpu10;
    }
L_0x00437fb8:
    // 00437fb8  dc0d00765300           -fmul qword ptr [0x537600]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu11 = cpu.fpu.st(0);
    x86::Float fpu12 = cpu.fpu.mul(fpu11, x86::Float(app->getMemory<double>(x86::reg32(5469696) /* 0x537600 */)));
    // 00437fbe  d95dfc                 -fstp dword ptr [ebp - 4]
    app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = float(fpu12);
    // 00437fc1  ba207a4300             -mov edx, 0x437a20
    cpu.edx = 4422176 /*0x437a20*/;
    // 00437fc6  a1484f5500             -mov eax, dword ptr [0x554f48]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5590856) /* 0x554f48 */);
    cpu.fpu.count -= 1;
    }
    // 00437fcb  e8f04a0300             -call 0x46cac0
    cpu.esp -= 4;
    nfs3hp::frontend::sliderSetOnMove(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00437fd0  6a00                   -push 0
    app->getMemory<x86::reg32>(cpu.esp-4) = 0 /*0x0*/;
    cpu.esp -= 4;
    // 00437fd2  a1484f5500             -mov eax, dword ptr [0x554f48]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5590856) /* 0x554f48 */);
    // 00437fd7  ff75fc                 -push dword ptr [ebp - 4]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    cpu.esp -= 4;
    // 00437fda  e871490300             -call 0x46c950
    cpu.esp -= 4;
    nfs3hp::port::fields::sliderSetValue(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00437fdf:
    // 00437fdf  baec755300             -mov edx, 0x5375ec
    cpu.edx = 5469676 /*0x5375ec*/;
    // 00437fe4  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00437fe6  e855aa0000             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00437feb  a34c4f5500             -mov dword ptr [0x554f4c], eax
    app->getMemory<x86::reg32>(x86::reg32(5590860) /* 0x554f4c */) = cpu.eax;
    // 00437ff0  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00437ff2  742f                   -je 0x438023
    if (cpu.flags.zf)
    {
        goto L_0x00438023;
    }
    // 00437ff4  db05fcbb6f00           -fild dword ptr [0x6fbbfc]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu13 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(7322620) /* 0x6fbbfc */)));
    // 00437ffa  dc0d00765300           -fmul qword ptr [0x537600]
    x86::Float fpu14 = cpu.fpu.mul(fpu13, x86::Float(app->getMemory<double>(x86::reg32(5469696) /* 0x537600 */)));
    // 00438000  ba707a4300             -mov edx, 0x437a70
    cpu.edx = 4422256 /*0x437a70*/;
    // 00438005  c7402c907a4300         -mov dword ptr [eax + 0x2c], 0x437a90
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(44) /* 0x2c */) = 4422288 /*0x437a90*/;
    // 0043800c  d95df0                 -fstp dword ptr [ebp - 0x10]
    app->getMemory<float>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = float(fpu14);
    }
    // 0043800f  e8ac4a0300             -call 0x46cac0
    cpu.esp -= 4;
    nfs3hp::frontend::sliderSetOnMove(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00438014  6a00                   -push 0
    app->getMemory<x86::reg32>(cpu.esp-4) = 0 /*0x0*/;
    cpu.esp -= 4;
    // 00438016  a14c4f5500             -mov eax, dword ptr [0x554f4c]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5590860) /* 0x554f4c */);
    // 0043801b  ff75f0                 -push dword ptr [ebp - 0x10]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    cpu.esp -= 4;
    // 0043801e  e82d490300             -call 0x46c950
    cpu.esp -= 4;
    nfs3hp::port::fields::sliderSetValue(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00438023:
    // 00438023  833d3492550000         +cmp dword ptr [0x559234], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5607988) /* 0x559234 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0043802a  7510                   -jne 0x43803c
    if (!cpu.flags.zf)
    {
        goto L_0x0043803c;
    }
    // 0043802c  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 00438031  8b15e8bb6f00           -mov edx, dword ptr [0x6fbbe8]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(7322600) /* 0x6fbbe8 */);
    // 00438037  e834f40a00             -call 0x4e7470
    cpu.esp -= 4;
    nfs3hp::snd::SNDstreamautovol(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x0043803c:
    // 0043803c  b910000000             -mov ecx, 0x10
    cpu.ecx = 16 /*0x10*/;
    // 00438041  a124295500             -mov eax, dword ptr [0x552924]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5581092) /* 0x552924 */);
    // 00438046  bf20395f00             -mov edi, 0x5f3920
    cpu.edi = 6240544 /*0x5f3920*/;
    // 0043804b  bed0bb6f00             -mov esi, 0x6fbbd0
    cpu.esi = 7322576 /*0x6fbbd0*/;
    // 00438050  a36c395f00             -mov dword ptr [0x5f396c], eax
    app->getMemory<x86::reg32>(x86::reg32(6240620) /* 0x5f396c */) = cpu.eax;
    // 00438055  a120295500             -mov eax, dword ptr [0x552920]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5581088) /* 0x552920 */);
    // 0043805a  f3a5                   -rep movsd dword ptr es:[edi], dword ptr [esi]
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
    // 0043805c  a360395f00             -mov dword ptr [0x5f3960], eax
    app->getMemory<x86::reg32>(x86::reg32(6240608) /* 0x5f3960 */) = cpu.eax;
    // 00438061  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
L_0x00438063:
    // 00438063  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00438065  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00438066  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00438067  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00438068  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00438069  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043806a  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x40 0x00 0x8b 0xc9 */
void Application::sub_438070(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (audioOnExit(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 00438070  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00438071  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00438072  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00438073  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00438074  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00438075  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00438076  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00438078  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 0043807a  833d3492550000         +cmp dword ptr [0x559234], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5607988) /* 0x559234 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00438081  7510                   -jne 0x438093
    if (!cpu.flags.zf)
    {
        goto L_0x00438093;
    }
    // 00438083  b80a000000             -mov eax, 0xa
    cpu.eax = 10 /*0xa*/;
    // 00438088  8b15e8bb6f00           -mov edx, dword ptr [0x6fbbe8]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(7322600) /* 0x6fbbe8 */);
    // 0043808e  e8ddf30a00             -call 0x4e7470
    cpu.esp -= 4;
    nfs3hp::snd::SNDstreamautovol(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00438093:
    // 00438093  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
    // 00438095  891d404f5500           -mov dword ptr [0x554f40], ebx
    app->getMemory<x86::reg32>(x86::reg32(5590848) /* 0x554f40 */) = cpu.ebx;
    // 0043809b  891d444f5500           -mov dword ptr [0x554f44], ebx
    app->getMemory<x86::reg32>(x86::reg32(5590852) /* 0x554f44 */) = cpu.ebx;
    // 004380a1  891d484f5500           -mov dword ptr [0x554f48], ebx
    app->getMemory<x86::reg32>(x86::reg32(5590856) /* 0x554f48 */) = cpu.ebx;
    // 004380a7  891d4c4f5500           -mov dword ptr [0x554f4c], ebx
    app->getMemory<x86::reg32>(x86::reg32(5590860) /* 0x554f4c */) = cpu.ebx;
    // 004380ad  891d204f5500           -mov dword ptr [0x554f20], ebx
    app->getMemory<x86::reg32>(x86::reg32(5590816) /* 0x554f20 */) = cpu.ebx;
    // 004380b3  891d244f5500           -mov dword ptr [0x554f24], ebx
    app->getMemory<x86::reg32>(x86::reg32(5590820) /* 0x554f24 */) = cpu.ebx;
    // 004380b9  891d284f5500           -mov dword ptr [0x554f28], ebx
    app->getMemory<x86::reg32>(x86::reg32(5590824) /* 0x554f28 */) = cpu.ebx;
    // 004380bf  891d2c4f5500           -mov dword ptr [0x554f2c], ebx
    app->getMemory<x86::reg32>(x86::reg32(5590828) /* 0x554f2c */) = cpu.ebx;
    // 004380c5  891d304f5500           -mov dword ptr [0x554f30], ebx
    app->getMemory<x86::reg32>(x86::reg32(5590832) /* 0x554f30 */) = cpu.ebx;
    // 004380cb  891d3c4f5500           -mov dword ptr [0x554f3c], ebx
    app->getMemory<x86::reg32>(x86::reg32(5590844) /* 0x554f3c */) = cpu.ebx;
    // 004380d1  833d3492550000         +cmp dword ptr [0x559234], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5607988) /* 0x559234 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004380d8  745c                   -je 0x438136
    if (cpu.flags.zf)
    {
        goto L_0x00438136;
    }
    // 004380da  803d0929550000         +cmp byte ptr [0x552909], 0
    {
        x86::reg8 tmp1 = app->getMemory<x86::reg8>(x86::reg32(5581065) /* 0x552909 */);
        x86::reg8 tmp2 = x86::reg8(x86::sreg8(0 /*0x0*/));
        x86::reg8 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 7);
        cpu.flags.of ^= 1 & (result >> 7);
        cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
        cpu.set_szp(result);
    }
    // 004380e1  7414                   -je 0x4380f7
    if (cpu.flags.zf)
    {
        goto L_0x004380f7;
    }
    // 004380e3  a120295500             -mov eax, dword ptr [0x552920]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5581088) /* 0x552920 */);
    // 004380e8  a3f4bb6f00             -mov dword ptr [0x6fbbf4], eax
    app->getMemory<x86::reg32>(x86::reg32(7322612) /* 0x6fbbf4 */) = cpu.eax;
    // 004380ed  a124295500             -mov eax, dword ptr [0x552924]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5581092) /* 0x552924 */);
    // 004380f2  a3f8bb6f00             -mov dword ptr [0x6fbbf8], eax
    app->getMemory<x86::reg32>(x86::reg32(7322616) /* 0x6fbbf8 */) = cpu.eax;
L_0x004380f7:
    // 004380f7  803d90e8550000         +cmp byte ptr [0x55e890], 0
    {
        x86::reg8 tmp1 = app->getMemory<x86::reg8>(x86::reg32(5630096) /* 0x55e890 */);
        x86::reg8 tmp2 = x86::reg8(x86::sreg8(0 /*0x0*/));
        x86::reg8 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 7);
        cpu.flags.of ^= 1 & (result >> 7);
        cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
        cpu.set_szp(result);
    }
    // 004380fe  7536                   -jne 0x438136
    if (!cpu.flags.zf)
    {
        goto L_0x00438136;
    }
    // 00438100  8b35f0bb6f00           -mov esi, dword ptr [0x6fbbf0]
    cpu.esi = app->getMemory<x86::reg32>(x86::reg32(7322608) /* 0x6fbbf0 */);
    // 00438106  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 00438108  742c                   -je 0x438136
    if (cpu.flags.zf)
    {
        goto L_0x00438136;
    }
    // 0043810a  833de4bb6f0002         +cmp dword ptr [0x6fbbe4], 2
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(7322596) /* 0x6fbbe4 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(2 /*0x2*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00438111  7e0e                   -jle 0x438121
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00438121;
    }
    // 00438113  bb01000000             -mov ebx, 1
    cpu.ebx = 1 /*0x1*/;
    // 00438118  a1acd46f00             -mov eax, dword ptr [0x6fd4ac]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(7328940) /* 0x6fd4ac */);
    // 0043811d  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 0043811f  eb09                   -jmp 0x43812a
    goto L_0x0043812a;
L_0x00438121:
    // 00438121  a1acd46f00             -mov eax, dword ptr [0x6fd4ac]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(7328940) /* 0x6fd4ac */);
    // 00438126  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 00438128  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
L_0x0043812a:
    // 0043812a  e89186fdff             -call 0x4107c0
    cpu.esp -= 4;
    nfs3hp::snd::raceMusicStart(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0043812f  c60590e8550001         -mov byte ptr [0x55e890], 1
    app->getMemory<x86::reg8>(x86::reg32(5630096) /* 0x55e890 */) = 1 /*0x1*/;
L_0x00438136:
    // 00438136  8b5118                 -mov edx, dword ptr [ecx + 0x18]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(24) /* 0x18 */);
    // 00438139  8b4916                 -mov ecx, dword ptr [ecx + 0x16]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(22) /* 0x16 */);
    // 0043813c  c1fa10                 -sar edx, 0x10
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (16 /*0x10*/ % 32));
    // 0043813f  c1f910                 -sar ecx, 0x10
    cpu.ecx = x86::reg32(x86::sreg32(cpu.ecx) >> (16 /*0x10*/ % 32));
    // 00438142  01d1                   -add ecx, edx
    (cpu.ecx) += x86::reg32(x86::sreg32(cpu.edx));
    // 00438144  8d048d00000000         -lea eax, [ecx*4]
    cpu.eax = x86::reg32(cpu.ecx * 4);
    // 0043814b  29c8                   -sub eax, ecx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.ecx));
    // 0043814d  c1e004                 -shl eax, 4
    cpu.eax <<= 4 /*0x4*/ % 32;
    // 00438150  29c8                   -sub eax, ecx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.ecx));
    // 00438152  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 00438155  05e04e6000             -add eax, 0x604ee0
    (cpu.eax) += x86::reg32(x86::sreg32(6311648 /*0x604ee0*/));
    // 0043815a  833805                 +cmp dword ptr [eax], 5
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(5 /*0x5*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0043815d  0f85a5000000           -jne 0x438208
    if (!cpu.flags.zf)
    {
        goto L_0x00438208;
    }
    // 00438163  ba08765300             -mov edx, 0x537608
    cpu.edx = 5469704 /*0x537608*/;
    // 00438168  8b4010                 -mov eax, dword ptr [eax + 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(16) /* 0x10 */);
    // 0043816b  e850a80000             -call 0x4429c0
    cpu.esp -= 4;
    sub_4429c0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00438170  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00438172  0f8490000000           -je 0x438208
    if (cpu.flags.zf)
    {
        goto L_0x00438208;
    }
    // 00438178  b910000000             -mov ecx, 0x10
    cpu.ecx = 16 /*0x10*/;
    // 0043817d  a160395f00             -mov eax, dword ptr [0x5f3960]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(6240608) /* 0x5f3960 */);
    // 00438182  bfd0bb6f00             -mov edi, 0x6fbbd0
    cpu.edi = 7322576 /*0x6fbbd0*/;
    // 00438187  be20395f00             -mov esi, 0x5f3920
    cpu.esi = 6240544 /*0x5f3920*/;
    // 0043818c  8a1d09295500           -mov bl, byte ptr [0x552909]
    cpu.bl = app->getMemory<x86::reg8>(x86::reg32(5581065) /* 0x552909 */);
    // 00438192  a320295500             -mov dword ptr [0x552920], eax
    app->getMemory<x86::reg32>(x86::reg32(5581088) /* 0x552920 */) = cpu.eax;
    // 00438197  a16c395f00             -mov eax, dword ptr [0x5f396c]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(6240620) /* 0x5f396c */);
    // 0043819c  f3a5                   -rep movsd dword ptr es:[edi], dword ptr [esi]
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
    // 0043819e  a324295500             -mov dword ptr [0x552924], eax
    app->getMemory<x86::reg32>(x86::reg32(5581092) /* 0x552924 */) = cpu.eax;
    // 004381a3  84db                   +test bl, bl
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.bl & cpu.bl));
    // 004381a5  7414                   -je 0x4381bb
    if (cpu.flags.zf)
    {
        goto L_0x004381bb;
    }
    // 004381a7  a120295500             -mov eax, dword ptr [0x552920]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5581088) /* 0x552920 */);
    // 004381ac  a3f4bb6f00             -mov dword ptr [0x6fbbf4], eax
    app->getMemory<x86::reg32>(x86::reg32(7322612) /* 0x6fbbf4 */) = cpu.eax;
    // 004381b1  a124295500             -mov eax, dword ptr [0x552924]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5581092) /* 0x552924 */);
    // 004381b6  a3f8bb6f00             -mov dword ptr [0x6fbbf8], eax
    app->getMemory<x86::reg32>(x86::reg32(7322616) /* 0x6fbbf8 */) = cpu.eax;
L_0x004381bb:
    // 004381bb  8b0d34925500           -mov ecx, dword ptr [0x559234]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(5607988) /* 0x559234 */);
    // 004381c1  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    // 004381c3  751e                   -jne 0x4381e3
    if (!cpu.flags.zf)
    {
        goto L_0x004381e3;
    }
    // 004381c5  833d344f550000         +cmp dword ptr [0x554f34], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5590836) /* 0x554f34 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004381cc  7415                   -je 0x4381e3
    if (cpu.flags.zf)
    {
        goto L_0x004381e3;
    }
    // 004381ce  ba01000000             -mov edx, 1
    cpu.edx = 1 /*0x1*/;
    // 004381d3  a1ecbb6f00             -mov eax, dword ptr [0x6fbbec]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(7322604) /* 0x6fbbec */);
    // 004381d8  890d344f5500           -mov dword ptr [0x554f34], ecx
    app->getMemory<x86::reg32>(x86::reg32(5590836) /* 0x554f34 */) = cpu.ecx;
    // 004381de  e8bd81fdff             -call 0x4103a0
    cpu.esp -= 4;
    nfs3hp::snd::musicAfterSetting(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x004381e3:
    // 004381e3  bbffffffff             -mov ebx, 0xffffffff
    cpu.ebx = 4294967295 /*0xffffffff*/;
    // 004381e8  ba05000000             -mov edx, 5
    cpu.edx = 5 /*0x5*/;
    // 004381ed  a1384f5500             -mov eax, dword ptr [0x554f38]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5590840) /* 0x554f38 */);
    // 004381f2  31ff                   -xor edi, edi
    cpu.edi ^= x86::reg32(x86::sreg32(cpu.edi));
    // 004381f4  e827120b00             -call 0x4e9420
    cpu.esp -= 4;
    nfs3hp::port::SNDautovol(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004381f9  893d384f5500           -mov dword ptr [0x554f38], edi
    app->getMemory<x86::reg32>(x86::reg32(5590840) /* 0x554f38 */) = cpu.edi;
    // 004381ff  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00438201  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00438202  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00438203  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00438204  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00438205  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00438206  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00438207  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x00438208:
    // 00438208  bbffffffff             -mov ebx, 0xffffffff
    cpu.ebx = 4294967295 /*0xffffffff*/;
    // 0043820d  ba05000000             -mov edx, 5
    cpu.edx = 5 /*0x5*/;
    // 00438212  a1384f5500             -mov eax, dword ptr [0x554f38]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5590840) /* 0x554f38 */);
    // 00438217  e804120b00             -call 0x4e9420
    cpu.esp -= 4;
    nfs3hp::port::SNDautovol(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0043821c  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 0043821e  8b1534925500           -mov edx, dword ptr [0x559234]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5607988) /* 0x559234 */);
    // 00438224  a3384f5500             -mov dword ptr [0x554f38], eax
    app->getMemory<x86::reg32>(x86::reg32(5590840) /* 0x554f38 */) = cpu.eax;
    // 00438229  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 0043822b  7526                   -jne 0x438253
    if (!cpu.flags.zf)
    {
        goto L_0x00438253;
    }
    // 0043822d  833d344f550000         +cmp dword ptr [0x554f34], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5590836) /* 0x554f34 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00438234  7509                   -jne 0x43823f
    if (!cpu.flags.zf)
    {
        goto L_0x0043823f;
    }
    // 00438236  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00438238  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00438239  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043823a  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043823b  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043823c  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043823d  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043823e  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x0043823f:
    // 0043823f  ba01000000             -mov edx, 1
    cpu.edx = 1 /*0x1*/;
    // 00438244  a3344f5500             -mov dword ptr [0x554f34], eax
    app->getMemory<x86::reg32>(x86::reg32(5590836) /* 0x554f34 */) = cpu.eax;
    // 00438249  a1ecbb6f00             -mov eax, dword ptr [0x6fbbec]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(7322604) /* 0x6fbbec */);
    // 0043824e  e84d81fdff             -call 0x4103a0
    cpu.esp -= 4;
    nfs3hp::snd::musicAfterSetting(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00438253:
    // 00438253  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00438255  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00438256  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00438257  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00438258  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00438259  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043825a  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043825b  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x44 0x20 0x00 */
void Application::sub_438260(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (audioOnFrame(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 00438260  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00438261  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00438262  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00438263  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00438264  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00438265  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00438266  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00438268  a170395f00             -mov eax, dword ptr [0x5f3970]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(6240624) /* 0x5f3970 */);
    // 0043826d  8b1500bc6f00           -mov edx, dword ptr [0x6fbc00]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(7322624) /* 0x6fbc00 */);
    // 00438273  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 00438275  39d0                   +cmp eax, edx
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
    // 00438277  7473                   -je 0x4382ec
    if (cpu.flags.zf)
    {
        goto L_0x004382ec;
    }
    // 00438279  b8e6010000             -mov eax, 0x1e6
    cpu.eax = 486 /*0x1e6*/;
    // 0043827e  891570395f00           -mov dword ptr [0x5f3970], edx
    app->getMemory<x86::reg32>(x86::reg32(6240624) /* 0x5f3970 */) = cpu.edx;
    // 00438284  e857c90000             -call 0x444be0
    cpu.esp -= 4;
    nfs3hp::frontend::dialogMessageById(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00438289  e872dc0000             -call 0x445f00
    cpu.esp -= 4;
    nfs3hp::frontend::dialogFadedIn(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0043828e  e88d0e0a00             -call 0x4d9120
    cpu.esp -= 4;
    nfs3hp::graphics::takeWindowAndClear(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00438293  e8182c0100             -call 0x44aeb0
    cpu.esp -= 4;
    sub_44aeb0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00438298  e853220100             -call 0x44a4f0
    cpu.esp -= 4;
    sub_44a4f0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0043829d  e80eb60000             -call 0x4438b0
    cpu.esp -= 4;
    sub_4438b0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004382a2  84c0                   +test al, al
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.al & cpu.al));
    // 004382a4  7405                   -je 0x4382ab
    if (cpu.flags.zf)
    {
        goto L_0x004382ab;
    }
    // 004382a6  e8a5dc0000             -call 0x445f50
    cpu.esp -= 4;
    sub_445f50(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x004382ab:
    // 004382ab  e8900e0a00             -call 0x4d9140
    cpu.esp -= 4;
    nfs3hp::graphics::flipAndWaitFrames(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004382b0  e81b87fdff             -call 0x4109d0
    cpu.esp -= 4;
    nfs3hp::snd::musicStop(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004382b5  e8e687fdff             -call 0x410aa0
    cpu.esp -= 4;
    nfs3hp::snd::musicStreamEnd(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004382ba  e86188fdff             -call 0x410b20
    cpu.esp -= 4;
    nfs3hp::snd::banksRemove(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004382bf  e8ec7bfdff             -call 0x40feb0
    cpu.esp -= 4;
    nfs3hp::snd::soundExit(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004382c4  a100bc6f00             -mov eax, dword ptr [0x6fbc00]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(7322624) /* 0x6fbc00 */);
    // 004382c9  ba01000000             -mov edx, 1
    cpu.edx = 1 /*0x1*/;
    // 004382ce  e81d7afdff             -call 0x40fcf0
    cpu.esp -= 4;
    nfs3hp::aiplan::restartSound(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004382d3  e808b4fdff             -call 0x4136e0
    cpu.esp -= 4;
    nfs3hp::snd::raceBankLoad(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004382d8  e85380fdff             -call 0x410330
    cpu.esp -= 4;
    nfs3hp::snd::musicStreamMake(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004382dd  a1ecbb6f00             -mov eax, dword ptr [0x6fbbec]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(7322604) /* 0x6fbbec */);
    // 004382e2  e8b980fdff             -call 0x4103a0
    cpu.esp -= 4;
    nfs3hp::snd::musicAfterSetting(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004382e7  e824dc0000             -call 0x445f10
    cpu.esp -= 4;
    sub_445f10(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x004382ec:
    // 004382ec  8b1de4bb6f00           -mov ebx, dword ptr [0x6fbbe4]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(7322596) /* 0x6fbbe4 */);
    // 004382f2  3b1d68395f00           +cmp ebx, dword ptr [0x5f3968]
    {
        x86::reg32 tmp1 = cpu.ebx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(6240616) /* 0x5f3968 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004382f8  741a                   -je 0x438314
    if (cpu.flags.zf)
    {
        goto L_0x00438314;
    }
    // 004382fa  be01000000             -mov esi, 1
    cpu.esi = 1 /*0x1*/;
    // 004382ff  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 00438301  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00438303  891d68395f00           -mov dword ptr [0x5f3968], ebx
    app->getMemory<x86::reg32>(x86::reg32(6240616) /* 0x5f3968 */) = cpu.ebx;
    // 00438309  e89280fdff             -call 0x4103a0
    cpu.esp -= 4;
    nfs3hp::snd::musicAfterSetting(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0043830e  8935344f5500           -mov dword ptr [0x554f34], esi
    app->getMemory<x86::reg32>(x86::reg32(5590836) /* 0x554f34 */) = cpu.esi;
L_0x00438314:
    // 00438314  8b3decbb6f00           -mov edi, dword ptr [0x6fbbec]
    cpu.edi = app->getMemory<x86::reg32>(x86::reg32(7322604) /* 0x6fbbec */);
    // 0043831a  3b3d64395f00           +cmp edi, dword ptr [0x5f3964]
    {
        x86::reg32 tmp1 = cpu.edi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(6240612) /* 0x5f3964 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00438320  7412                   -je 0x438334
    if (cpu.flags.zf)
    {
        goto L_0x00438334;
    }
    // 00438322  ba01000000             -mov edx, 1
    cpu.edx = 1 /*0x1*/;
    // 00438327  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 00438329  893d64395f00           -mov dword ptr [0x5f3964], edi
    app->getMemory<x86::reg32>(x86::reg32(6240612) /* 0x5f3964 */) = cpu.edi;
    // 0043832f  e86c80fdff             -call 0x4103a0
    cpu.esp -= 4;
    nfs3hp::snd::musicAfterSetting(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00438334:
    // 00438334  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00438336  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00438337  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00438338  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00438339  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043833a  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043833b  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043833c  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_438340: native, nfs3hp::load::endWithSlash */

/* sub_438350: native, nfs3hp::load::folderWritable */

/* sub_4383f0: native, nfs3hp::load::firstFreeHexFolder */

/* align: skip  */
void Application::sub_4384a0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004384a0  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004384a1  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004384a2  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004384a3  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004384a4  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004384a6  81ec2c010000           -sub esp, 0x12c
    (cpu.esp) -= x86::reg32(x86::sreg32(300 /*0x12c*/));
    // 004384ac  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004384ae  beb4287a00             -mov esi, 0x7a28b4
    cpu.esi = 8005812 /*0x7a28b4*/;
    // 004384b3  8dbdd4feffff           -lea edi, [ebp - 0x12c]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(-300) /* -0x12c */);
    // 004384b9  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
L_0x004384ba:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004384ba  8a06                   -mov al, byte ptr [esi]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi);
    // 004384bc  8807                   -mov byte ptr [edi], al
    app->getMemory<x86::reg8>(cpu.edi) = cpu.al;
    // 004384be  3c00                   +cmp al, 0
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
    // 004384c0  7410                   -je 0x4384d2
    if (cpu.flags.zf)
    {
        goto L_0x004384d2;
    }
    // 004384c2  8a4601                 -mov al, byte ptr [esi + 1]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi + x86::reg32(1) /* 0x1 */);
    // 004384c5  83c602                 -add esi, 2
    (cpu.esi) += x86::reg32(x86::sreg32(2 /*0x2*/));
    // 004384c8  884701                 -mov byte ptr [edi + 1], al
    app->getMemory<x86::reg8>(cpu.edi + x86::reg32(1) /* 0x1 */) = cpu.al;
    // 004384cb  83c702                 -add edi, 2
    (cpu.edi) += x86::reg32(x86::sreg32(2 /*0x2*/));
    // 004384ce  3c00                   +cmp al, 0
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
    // 004384d0  75e8                   -jne 0x4384ba
    if (!cpu.flags.zf)
    {
        goto L_0x004384ba;
    }
L_0x004384d2:
    // 004384d2  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004384d3  8d85d4feffff           -lea eax, [ebp - 0x12c]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-300) /* -0x12c */);
    // 004384d9  e862feffff             -call 0x438340
    cpu.esp -= 4;
    nfs3hp::load::endWithSlash(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004384de  8d85d4feffff           -lea eax, [ebp - 0x12c]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-300) /* -0x12c */);
    // 004384e4  e807ffffff             -call 0x4383f0
    cpu.esp -= 4;
    nfs3hp::load::firstFreeHexFolder(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004384e9  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004384eb  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004384ec  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004384ed  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004384ee  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004384ef  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_4384f0: native, nfs3hp::load::firstFreePlayerFolder */

/* sub_4385a0: native, nfs3hp::load::freePlayerCarFolder */

/* align: skip  */
void Application::sub_4385f0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004385f0  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004385f1  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004385f2  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004385f3  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004385f4  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004385f6  81ec2c010000           -sub esp, 0x12c
    (cpu.esp) -= x86::reg32(x86::sreg32(300 /*0x12c*/));
    // 004385fc  81edaa010000           -sub ebp, 0x1aa
    (cpu.ebp) -= x86::reg32(x86::sreg32(426 /*0x1aa*/));
    // 00438602  8d7d7e                 -lea edi, [ebp + 0x7e]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(126) /* 0x7e */);
    // 00438605  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 00438607  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
L_0x00438608:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00438608  8a06                   -mov al, byte ptr [esi]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi);
    // 0043860a  8807                   -mov byte ptr [edi], al
    app->getMemory<x86::reg8>(cpu.edi) = cpu.al;
    // 0043860c  3c00                   +cmp al, 0
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
    // 0043860e  7410                   -je 0x438620
    if (cpu.flags.zf)
    {
        goto L_0x00438620;
    }
    // 00438610  8a4601                 -mov al, byte ptr [esi + 1]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi + x86::reg32(1) /* 0x1 */);
    // 00438613  83c602                 -add esi, 2
    (cpu.esi) += x86::reg32(x86::sreg32(2 /*0x2*/));
    // 00438616  884701                 -mov byte ptr [edi + 1], al
    app->getMemory<x86::reg8>(cpu.edi + x86::reg32(1) /* 0x1 */) = cpu.al;
    // 00438619  83c702                 -add edi, 2
    (cpu.edi) += x86::reg32(x86::sreg32(2 /*0x2*/));
    // 0043861c  3c00                   +cmp al, 0
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
    // 0043861e  75e8                   -jne 0x438608
    if (!cpu.flags.zf)
    {
        goto L_0x00438608;
    }
L_0x00438620:
    // 00438620  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00438621  8d457e                 -lea eax, [ebp + 0x7e]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(126) /* 0x7e */);
    // 00438624  be78765300             -mov esi, 0x537678
    cpu.esi = 5469816 /*0x537678*/;
    // 00438629  8d7d7e                 -lea edi, [ebp + 0x7e]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(126) /* 0x7e */);
    // 0043862c  e80ffdffff             -call 0x438340
    cpu.esp -= 4;
    nfs3hp::load::endWithSlash(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00438631  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00438632  2bc9                   +sub ecx, ecx
    {
        x86::reg32& tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ecx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 00438634  49                     +dec ecx
    {
        x86::reg32& tmp = cpu.ecx;
        cpu.flags.of = 1 & (tmp >> 31);
        tmp--;
        cpu.flags.of &= ~(1 & (tmp >> 31));
        cpu.set_szp(tmp);
    }
    // 00438635  b000                   -mov al, 0
    cpu.al = 0 /*0x0*/;
    // 00438637  f2ae                   -repne scasb al, byte ptr es:[edi]
    while (cpu.ecx)
    {
        {
            x86::reg8 tmp1 = cpu.al;
            x86::reg8 tmp2 = x86::reg8(x86::sreg8(app->getMemory<x86::reg8>(cpu.ees + cpu.edi)));
            x86::reg8 result = tmp1 - tmp2;
            cpu.flags.cf = tmp1 < tmp2;
            cpu.flags.of = 1 & (tmp1 >> 7);
            cpu.flags.of ^= 1 & (result >> 7);
            cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
            cpu.set_szp(result);
        }
        if (cpu.flags.df)
        {
            cpu.edi -= 1;
        }
        else
        {
            cpu.edi += 1;
        }
        --cpu.ecx;
        if (cpu.flags.zf)
            break;
    }
    // 00438639  4f                     -dec edi
    (cpu.edi)--;
L_0x0043863a:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 0043863a  8a06                   -mov al, byte ptr [esi]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi);
    // 0043863c  8807                   -mov byte ptr [edi], al
    app->getMemory<x86::reg8>(cpu.edi) = cpu.al;
    // 0043863e  3c00                   +cmp al, 0
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
    // 00438640  7410                   -je 0x438652
    if (cpu.flags.zf)
    {
        goto L_0x00438652;
    }
    // 00438642  8a4601                 -mov al, byte ptr [esi + 1]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi + x86::reg32(1) /* 0x1 */);
    // 00438645  83c602                 -add esi, 2
    (cpu.esi) += x86::reg32(x86::sreg32(2 /*0x2*/));
    // 00438648  884701                 -mov byte ptr [edi + 1], al
    app->getMemory<x86::reg8>(cpu.edi + x86::reg32(1) /* 0x1 */) = cpu.al;
    // 0043864b  83c702                 -add edi, 2
    (cpu.edi) += x86::reg32(x86::sreg32(2 /*0x2*/));
    // 0043864e  3c00                   +cmp al, 0
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
    // 00438650  75e8                   -jne 0x43863a
    if (!cpu.flags.zf)
    {
        goto L_0x0043863a;
    }
L_0x00438652:
    // 00438652  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00438653  8d7d7e                 -lea edi, [ebp + 0x7e]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(126) /* 0x7e */);
    // 00438656  8b3495544f5500         -mov esi, dword ptr [edx*4 + 0x554f54]
    cpu.esi = app->getMemory<x86::reg32>(x86::reg32(5590868) /* 0x554f54 */ + cpu.edx * 4);
    // 0043865d  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 0043865e  2bc9                   +sub ecx, ecx
    {
        x86::reg32& tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ecx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 00438660  49                     +dec ecx
    {
        x86::reg32& tmp = cpu.ecx;
        cpu.flags.of = 1 & (tmp >> 31);
        tmp--;
        cpu.flags.of &= ~(1 & (tmp >> 31));
        cpu.set_szp(tmp);
    }
    // 00438661  b000                   -mov al, 0
    cpu.al = 0 /*0x0*/;
    // 00438663  f2ae                   -repne scasb al, byte ptr es:[edi]
    while (cpu.ecx)
    {
        {
            x86::reg8 tmp1 = cpu.al;
            x86::reg8 tmp2 = x86::reg8(x86::sreg8(app->getMemory<x86::reg8>(cpu.ees + cpu.edi)));
            x86::reg8 result = tmp1 - tmp2;
            cpu.flags.cf = tmp1 < tmp2;
            cpu.flags.of = 1 & (tmp1 >> 7);
            cpu.flags.of ^= 1 & (result >> 7);
            cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
            cpu.set_szp(result);
        }
        if (cpu.flags.df)
        {
            cpu.edi -= 1;
        }
        else
        {
            cpu.edi += 1;
        }
        --cpu.ecx;
        if (cpu.flags.zf)
            break;
    }
    // 00438665  4f                     -dec edi
    (cpu.edi)--;
L_0x00438666:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00438666  8a06                   -mov al, byte ptr [esi]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi);
    // 00438668  8807                   -mov byte ptr [edi], al
    app->getMemory<x86::reg8>(cpu.edi) = cpu.al;
    // 0043866a  3c00                   +cmp al, 0
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
    // 0043866c  7410                   -je 0x43867e
    if (cpu.flags.zf)
    {
        goto L_0x0043867e;
    }
    // 0043866e  8a4601                 -mov al, byte ptr [esi + 1]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi + x86::reg32(1) /* 0x1 */);
    // 00438671  83c602                 -add esi, 2
    (cpu.esi) += x86::reg32(x86::sreg32(2 /*0x2*/));
    // 00438674  884701                 -mov byte ptr [edi + 1], al
    app->getMemory<x86::reg8>(cpu.edi + x86::reg32(1) /* 0x1 */) = cpu.al;
    // 00438677  83c702                 -add edi, 2
    (cpu.edi) += x86::reg32(x86::sreg32(2 /*0x2*/));
    // 0043867a  3c00                   +cmp al, 0
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
    // 0043867c  75e8                   -jne 0x438666
    if (!cpu.flags.zf)
    {
        goto L_0x00438666;
    }
L_0x0043867e:
    // 0043867e  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043867f  ba80765300             -mov edx, 0x537680
    cpu.edx = 5469824 /*0x537680*/;
    // 00438684  8d457e                 -lea eax, [ebp + 0x7e]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(126) /* 0x7e */);
    // 00438687  e85c590b00             -call 0x4edfe8
    cpu.esp -= 4;
    nfs3hp::watcom::fopen(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0043868c  8da5aa010000           -lea esp, [ebp + 0x1aa]
    cpu.esp = x86::reg32(cpu.ebp + x86::reg32(426) /* 0x1aa */);
    // 00438692  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00438693  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00438694  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00438695  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00438696  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 */
void Application::sub_4386a0(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004386a0  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004386a1  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004386a3  e8585a0b00             -call 0x4ee100
    cpu.esp -= 4;
    nfs3hp::watcom::fclose(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004386a8  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004386a9  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_4386b0: native, nfs3hp::load::firstSubfolder */

/* sub_4387e0: native, nfs3hp::load::nextSubfolder */

/* sub_438870: native, nfs3hp::load::firstFile */

/* sub_438970: native, nfs3hp::load::nextFile */

/* sub_4389d0: native, nfs3hp::load::removeFolder */

/* sub_438a80: native, nfs3hp::load::firstCar */

/* sub_438aa0: native, nfs3hp::load::nextCar */

/* sub_438ad0: native, nfs3hp::load::makeCarId */

/* sub_438af0: native, nfs3hp::load::firstCarGlobal */

/* sub_438b10: native, nfs3hp::load::nextCarGlobal */

/* align: skip 0x8b 0xc0 */
void Application::sub_438b40(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00438b40  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00438b41  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00438b42  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00438b43  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00438b45  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00438b47  e8a4ffffff             -call 0x438af0
    cpu.esp -= 4;
    nfs3hp::load::firstCarGlobal(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00438b4c  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
L_0x00438b4e:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00438b4e  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00438b50  740c                   -je 0x438b5e
    if (cpu.flags.zf)
    {
        goto L_0x00438b5e;
    }
    // 00438b52  39ca                   +cmp edx, ecx
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
    // 00438b54  7408                   -je 0x438b5e
    if (cpu.flags.zf)
    {
        goto L_0x00438b5e;
    }
    // 00438b56  e8b5ffffff             -call 0x438b10
    cpu.esp -= 4;
    nfs3hp::load::nextCarGlobal(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00438b5b  42                     +inc edx
    {
        x86::reg32& tmp = cpu.edx;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 00438b5c  ebf0                   -jmp 0x438b4e
    goto L_0x00438b4e;
L_0x00438b5e:
    // 00438b5e  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00438b5f  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00438b60  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00438b61  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x8b 0xc0 */
void Application::sub_438b70(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00438b70  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00438b71  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00438b72  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00438b74  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 00438b76  e875ffffff             -call 0x438af0
    cpu.esp -= 4;
    nfs3hp::load::firstCarGlobal(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00438b7b:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00438b7b  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00438b7d  740b                   -je 0x438b8a
    if (cpu.flags.zf)
    {
        goto L_0x00438b8a;
    }
    // 00438b7f  3b10                   +cmp edx, dword ptr [eax]
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.eax)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00438b81  7407                   -je 0x438b8a
    if (cpu.flags.zf)
    {
        goto L_0x00438b8a;
    }
    // 00438b83  e888ffffff             -call 0x438b10
    cpu.esp -= 4;
    nfs3hp::load::nextCarGlobal(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00438b88  ebf1                   -jmp 0x438b7b
    goto L_0x00438b7b;
L_0x00438b8a:
    // 00438b8a  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00438b8b  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00438b8c  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_438b90: native, nfs3hp::load::appendCar */

/* sub_438bd0: native, nfs3hp::load::carCount */

/* sub_438be0: native, nfs3hp::load::countCars */

/* sub_438c10: native, nfs3hp::load::unlinkCar */

/* sub_438c50: native, nfs3hp::load::insertCarByName */

/* sub_438cc0: native, nfs3hp::load::joinCarLists */

/* sub_438d20: native, nfs3hp::load::carListOf */

/* sub_438d60: native, nfs3hp::load::takePoliceCars */

/* sub_438dc0: native, nfs3hp::load::takeClasslessCars */

/* sub_438e30: native, nfs3hp::load::takeOrdinaryCars */

/* sub_438eb0: native, nfs3hp::load::sortCars */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8b 0xd2 */
void Application::sub_438f60(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
  goto start;
dynamic_jump:
  switch(cpu.ip)
  {
start:
    // 00438f60  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00438f61  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00438f62  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00438f64  e8e70a0000             -call 0x439a50
    cpu.esp -= 4;
    nfs3hp::load::carRecord(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00438f69  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00438f6b  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00438f6d  7443                   -je 0x438fb2
    if (cpu.flags.zf)
    {
        goto L_0x00438fb2;
    }
    // 00438f6f  83fa03                 +cmp edx, 3
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(3 /*0x3*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00438f72  773c                   -ja 0x438fb0
    if (!cpu.flags.cf && !cpu.flags.zf)
    {
        goto L_0x00438fb0;
    }
    // 00438f74  ff2495488f4300         -jmp dword ptr [edx*4 + 0x438f48]
    cpu.ip = app->getMemory<x86::reg32>(4427592 + cpu.edx * 4); goto dynamic_jump;
  case 0x00438f7b:
    // 00438f7b  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00438f7d  8a818f030000           -mov al, byte ptr [ecx + 0x38f]
    cpu.al = app->getMemory<x86::reg8>(cpu.ecx + x86::reg32(911) /* 0x38f */);
    // 00438f83  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00438f84  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00438f85  c3                     -ret 
    cpu.esp += 4;
    return;
  case 0x00438f86:
    // 00438f86  8a8090030000           -mov al, byte ptr [eax + 0x390]
    cpu.al = app->getMemory<x86::reg8>(cpu.eax + x86::reg32(912) /* 0x390 */);
    // 00438f8c  25ff000000             -and eax, 0xff
    cpu.eax &= x86::reg32(x86::sreg32(255 /*0xff*/));
    // 00438f91  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00438f92  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00438f93  c3                     -ret 
    cpu.esp += 4;
    return;
  case 0x00438f94:
    // 00438f94  8a8091030000           -mov al, byte ptr [eax + 0x391]
    cpu.al = app->getMemory<x86::reg8>(cpu.eax + x86::reg32(913) /* 0x391 */);
    // 00438f9a  25ff000000             -and eax, 0xff
    cpu.eax &= x86::reg32(x86::sreg32(255 /*0xff*/));
    // 00438f9f  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00438fa0  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00438fa1  c3                     -ret 
    cpu.esp += 4;
    return;
  case 0x00438fa2:
    // 00438fa2  8a8092030000           -mov al, byte ptr [eax + 0x392]
    cpu.al = app->getMemory<x86::reg8>(cpu.eax + x86::reg32(914) /* 0x392 */);
    // 00438fa8  25ff000000             -and eax, 0xff
    cpu.eax &= x86::reg32(x86::sreg32(255 /*0xff*/));
    // 00438fad  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00438fae  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00438faf  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x00438fb0:
    // 00438fb0  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
L_0x00438fb2:
    // 00438fb2  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00438fb3  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00438fb4  c3                     -ret 
    cpu.esp += 4;
    return;
  default:
    NFS2_ASSERT(false);
  }
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 0x8b 0xdb */
void Application::sub_438fc0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00438fc0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00438fc1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00438fc2  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00438fc3  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00438fc4  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00438fc5  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00438fc7  83ec0c                 -sub esp, 0xc
    (cpu.esp) -= x86::reg32(x86::sreg32(12 /*0xc*/));
    // 00438fca  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00438fcc  8955f8                 -mov dword ptr [ebp - 8], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.edx;
    // 00438fcf  8d45f4                 -lea eax, [ebp - 0xc]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 00438fd2  e8a9faffff             -call 0x438a80
    cpu.esp -= 4;
    nfs3hp::load::firstCar(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00438fd7  31f6                   -xor esi, esi
    cpu.esi ^= x86::reg32(x86::sreg32(cpu.esi));
L_0x00438fd9:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00438fd9  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00438fdb  0f8454000000           -je 0x439035
    if (cpu.flags.zf)
    {
        goto L_0x00439035;
    }
    // 00438fe1  051c030000             -add eax, 0x31c
    (cpu.eax) += x86::reg32(x86::sreg32(796 /*0x31c*/));
    // 00438fe6  e8a5090000             -call 0x439990
    cpu.esp -= 4;
    nfs3hp::load::findCarById(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00438feb  e840070000             -call 0x439730
    cpu.esp -= 4;
    nfs3hp::load::carClass(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00438ff0  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00438ff2  83f801                 +cmp eax, 1
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
    // 00438ff5  7209                   -jb 0x439000
    if (cpu.flags.cf)
    {
        goto L_0x00439000;
    }
    // 00438ff7  7617                   -jbe 0x439010
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x00439010;
    }
    // 00438ff9  83f802                 +cmp eax, 2
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
    // 00438ffc  741e                   -je 0x43901c
    if (cpu.flags.zf)
    {
        goto L_0x0043901c;
    }
    // 00438ffe  eb26                   -jmp 0x439026
    goto L_0x00439026;
L_0x00439000:
    // 00439000  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00439002  7522                   -jne 0x439026
    if (!cpu.flags.zf)
    {
        goto L_0x00439026;
    }
    // 00439004  f6c101                 +test cl, 1
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.cl & 1 /*0x1*/));
    // 00439007  741d                   -je 0x439026
    if (cpu.flags.zf)
    {
        goto L_0x00439026;
    }
    // 00439009  ba01000000             -mov edx, 1
    cpu.edx = 1 /*0x1*/;
    // 0043900e  eb16                   -jmp 0x439026
    goto L_0x00439026;
L_0x00439010:
    // 00439010  f6c102                 +test cl, 2
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.cl & 2 /*0x2*/));
    // 00439013  7411                   -je 0x439026
    if (cpu.flags.zf)
    {
        goto L_0x00439026;
    }
    // 00439015  ba01000000             -mov edx, 1
    cpu.edx = 1 /*0x1*/;
    // 0043901a  eb0a                   -jmp 0x439026
    goto L_0x00439026;
L_0x0043901c:
    // 0043901c  f6c104                 +test cl, 4
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.cl & 4 /*0x4*/));
    // 0043901f  7405                   -je 0x439026
    if (cpu.flags.zf)
    {
        goto L_0x00439026;
    }
    // 00439021  ba01000000             -mov edx, 1
    cpu.edx = 1 /*0x1*/;
L_0x00439026:
    // 00439026  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 00439028  7401                   -je 0x43902b
    if (cpu.flags.zf)
    {
        goto L_0x0043902b;
    }
    // 0043902a  46                     +inc esi
    {
        x86::reg32& tmp = cpu.esi;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
L_0x0043902b:
    // 0043902b  8d45f4                 -lea eax, [ebp - 0xc]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 0043902e  e86dfaffff             -call 0x438aa0
    cpu.esp -= 4;
    nfs3hp::load::nextCar(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00439033  eba4                   -jmp 0x438fd9
    goto L_0x00438fd9;
L_0x00439035:
    // 00439035  8d04f500000000         -lea eax, [esi*8]
    cpu.eax = x86::reg32(cpu.esi * 8);
    // 0043903c  8d7808                 -lea edi, [eax + 8]
    cpu.edi = x86::reg32(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 0043903f  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
    // 00439041  b890765300             -mov eax, 0x537690
    cpu.eax = 5469840 /*0x537690*/;
    // 00439046  89fa                   -mov edx, edi
    cpu.edx = cpu.edi;
    // 00439048  e8d3850a00             -call 0x4e1620
    cpu.esp -= 4;
    nfs3hp::ea::reservememadr(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0043904d  89fb                   -mov ebx, edi
    cpu.ebx = cpu.edi;
    // 0043904f  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00439051  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 00439054  e8e7750a00             -call 0x4e0640
    cpu.esp -= 4;
    nfs3hp::watcom::memset(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00439059  8d45f4                 -lea eax, [ebp - 0xc]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 0043905c  e81ffaffff             -call 0x438a80
    cpu.esp -= 4;
    nfs3hp::load::firstCar(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00439061  31ff                   -xor edi, edi
    cpu.edi ^= x86::reg32(x86::sreg32(cpu.edi));
L_0x00439063:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00439063  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 00439065  85db                   +test ebx, ebx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & cpu.ebx));
    // 00439067  0f846a000000           -je 0x4390d7
    if (cpu.flags.zf)
    {
        goto L_0x004390d7;
    }
    // 0043906d  8d831c030000           -lea eax, [ebx + 0x31c]
    cpu.eax = x86::reg32(cpu.ebx + x86::reg32(796) /* 0x31c */);
    // 00439073  e818090000             -call 0x439990
    cpu.esp -= 4;
    nfs3hp::load::findCarById(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00439078  e8b3060000             -call 0x439730
    cpu.esp -= 4;
    nfs3hp::load::carClass(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0043907d  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 0043907f  83f801                 +cmp eax, 1
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
    // 00439082  7209                   -jb 0x43908d
    if (cpu.flags.cf)
    {
        goto L_0x0043908d;
    }
    // 00439084  7617                   -jbe 0x43909d
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x0043909d;
    }
    // 00439086  83f802                 +cmp eax, 2
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
    // 00439089  741e                   -je 0x4390a9
    if (cpu.flags.zf)
    {
        goto L_0x004390a9;
    }
    // 0043908b  eb26                   -jmp 0x4390b3
    goto L_0x004390b3;
L_0x0043908d:
    // 0043908d  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0043908f  7522                   -jne 0x4390b3
    if (!cpu.flags.zf)
    {
        goto L_0x004390b3;
    }
    // 00439091  f6c101                 +test cl, 1
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.cl & 1 /*0x1*/));
    // 00439094  741d                   -je 0x4390b3
    if (cpu.flags.zf)
    {
        goto L_0x004390b3;
    }
    // 00439096  ba01000000             -mov edx, 1
    cpu.edx = 1 /*0x1*/;
    // 0043909b  eb16                   -jmp 0x4390b3
    goto L_0x004390b3;
L_0x0043909d:
    // 0043909d  f6c102                 +test cl, 2
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.cl & 2 /*0x2*/));
    // 004390a0  7411                   -je 0x4390b3
    if (cpu.flags.zf)
    {
        goto L_0x004390b3;
    }
    // 004390a2  ba01000000             -mov edx, 1
    cpu.edx = 1 /*0x1*/;
    // 004390a7  eb0a                   -jmp 0x4390b3
    goto L_0x004390b3;
L_0x004390a9:
    // 004390a9  f6c104                 +test cl, 4
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.cl & 4 /*0x4*/));
    // 004390ac  7405                   -je 0x4390b3
    if (cpu.flags.zf)
    {
        goto L_0x004390b3;
    }
    // 004390ae  ba01000000             -mov edx, 1
    cpu.edx = 1 /*0x1*/;
L_0x004390b3:
    // 004390b3  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 004390b5  7416                   -je 0x4390cd
    if (cpu.flags.zf)
    {
        goto L_0x004390cd;
    }
    // 004390b7  8b55fc                 -mov edx, dword ptr [ebp - 4]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004390ba  8d04fd00000000         -lea eax, [edi*8]
    cpu.eax = x86::reg32(cpu.edi * 8);
    // 004390c1  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 004390c3  83c310                 +add ebx, 0x10
    {
        x86::reg32& tmp1 = cpu.ebx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(16 /*0x10*/));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 004390c6  c6400400               -mov byte ptr [eax + 4], 0
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(4) /* 0x4 */) = 0 /*0x0*/;
    // 004390ca  47                     +inc edi
    {
        x86::reg32& tmp = cpu.edi;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 004390cb  8918                   -mov dword ptr [eax], ebx
    app->getMemory<x86::reg32>(cpu.eax) = cpu.ebx;
L_0x004390cd:
    // 004390cd  8d45f4                 -lea eax, [ebp - 0xc]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 004390d0  e8cbf9ffff             -call 0x438aa0
    cpu.esp -= 4;
    nfs3hp::load::nextCar(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004390d5  eb8c                   -jmp 0x439063
    goto L_0x00439063;
L_0x004390d7:
    // 004390d7  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004390da  8930                   -mov dword ptr [eax], esi
    app->getMemory<x86::reg32>(cpu.eax) = cpu.esi;
    // 004390dc  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004390df  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004390e1  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004390e2  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004390e3  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004390e4  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004390e5  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004390e6  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 */
void Application::sub_4390f0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004390f0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004390f1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004390f2  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004390f3  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004390f4  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004390f5  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004390f7  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 004390fa  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 004390fc  e84f090000             -call 0x439a50
    cpu.esp -= 4;
    nfs3hp::load::carRecord(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00439101  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00439103  0f84b1000000           -je 0x4391ba
    if (cpu.flags.zf)
    {
        goto L_0x004391ba;
    }
    // 00439109  f6808003000008         +test byte ptr [eax + 0x380], 8
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(cpu.eax + x86::reg32(896) /* 0x380 */) & 8 /*0x8*/));
    // 00439110  0f85a2000000           -jne 0x4391b8
    if (!cpu.flags.zf)
    {
        goto L_0x004391b8;
    }
    // 00439116  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00439118  e8f3040000             -call 0x439610
    cpu.esp -= 4;
    nfs3hp::load::carHasNumericId(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0043911d  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 0043911f  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00439121  e85a050000             -call 0x439680
    cpu.esp -= 4;
    nfs3hp::load::carIsBonus(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00439126  89c7                   -mov edi, eax
    cpu.edi = cpu.eax;
    // 00439128  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 0043912a  e8b1040000             -call 0x4395e0
    cpu.esp -= 4;
    sub_4395e0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0043912f  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 00439131  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 00439134  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00439136  e8f5050000             -call 0x439730
    cpu.esp -= 4;
    nfs3hp::load::carClass(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0043913b  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 0043913d  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 00439142  f6c202                 +test dl, 2
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.dl & 2 /*0x2*/));
    // 00439145  7406                   -je 0x43914d
    if (cpu.flags.zf)
    {
        goto L_0x0043914d;
    }
    // 00439147  85db                   +test ebx, ebx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & cpu.ebx));
    // 00439149  7502                   -jne 0x43914d
    if (!cpu.flags.zf)
    {
        goto L_0x0043914d;
    }
    // 0043914b  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
L_0x0043914d:
    // 0043914d  f6c204                 +test dl, 4
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.dl & 4 /*0x4*/));
    // 00439150  7408                   -je 0x43915a
    if (cpu.flags.zf)
    {
        goto L_0x0043915a;
    }
    // 00439152  837dfc00               +cmp dword ptr [ebp - 4], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00439156  7402                   -je 0x43915a
    if (cpu.flags.zf)
    {
        goto L_0x0043915a;
    }
    // 00439158  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
L_0x0043915a:
    // 0043915a  f6c202                 +test dl, 2
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.dl & 2 /*0x2*/));
    // 0043915d  7406                   -je 0x439165
    if (cpu.flags.zf)
    {
        goto L_0x00439165;
    }
    // 0043915f  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 00439161  7502                   -jne 0x439165
    if (!cpu.flags.zf)
    {
        goto L_0x00439165;
    }
    // 00439163  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
L_0x00439165:
    // 00439165  f6c204                 +test dl, 4
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.dl & 4 /*0x4*/));
    // 00439168  7406                   -je 0x439170
    if (cpu.flags.zf)
    {
        goto L_0x00439170;
    }
    // 0043916a  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 0043916c  7402                   -je 0x439170
    if (cpu.flags.zf)
    {
        goto L_0x00439170;
    }
    // 0043916e  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
L_0x00439170:
    // 00439170  f6c220                 +test dl, 0x20
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.dl & 32 /*0x20*/));
    // 00439173  7406                   -je 0x43917b
    if (cpu.flags.zf)
    {
        goto L_0x0043917b;
    }
    // 00439175  85ff                   +test edi, edi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edi & cpu.edi));
    // 00439177  7502                   -jne 0x43917b
    if (!cpu.flags.zf)
    {
        goto L_0x0043917b;
    }
    // 00439179  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
L_0x0043917b:
    // 0043917b  f6c240                 +test dl, 0x40
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.dl & 64 /*0x40*/));
    // 0043917e  7406                   -je 0x439186
    if (cpu.flags.zf)
    {
        goto L_0x00439186;
    }
    // 00439180  85ff                   +test edi, edi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edi & cpu.edi));
    // 00439182  7402                   -je 0x439186
    if (cpu.flags.zf)
    {
        goto L_0x00439186;
    }
    // 00439184  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
L_0x00439186:
    // 00439186  f7c200000080           +test edx, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & 2147483648 /*0x80000000*/));
    // 0043918c  752c                   -jne 0x4391ba
    if (!cpu.flags.zf)
    {
        goto L_0x004391ba;
    }
    // 0043918e  f7c200000010           +test edx, 0x10000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & 268435456 /*0x10000000*/));
    // 00439194  7406                   -je 0x43919c
    if (cpu.flags.zf)
    {
        goto L_0x0043919c;
    }
    // 00439196  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    // 00439198  7402                   -je 0x43919c
    if (cpu.flags.zf)
    {
        goto L_0x0043919c;
    }
    // 0043919a  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
L_0x0043919c:
    // 0043919c  f7c200000020           +test edx, 0x20000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & 536870912 /*0x20000000*/));
    // 004391a2  7407                   -je 0x4391ab
    if (cpu.flags.zf)
    {
        goto L_0x004391ab;
    }
    // 004391a4  83f901                 +cmp ecx, 1
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
    // 004391a7  7402                   -je 0x4391ab
    if (cpu.flags.zf)
    {
        goto L_0x004391ab;
    }
    // 004391a9  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
L_0x004391ab:
    // 004391ab  f7c200000040           +test edx, 0x40000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & 1073741824 /*0x40000000*/));
    // 004391b1  7407                   -je 0x4391ba
    if (cpu.flags.zf)
    {
        goto L_0x004391ba;
    }
    // 004391b3  83f902                 +cmp ecx, 2
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
    // 004391b6  7402                   -je 0x4391ba
    if (cpu.flags.zf)
    {
        goto L_0x004391ba;
    }
L_0x004391b8:
    // 004391b8  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
L_0x004391ba:
    // 004391ba  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004391bc  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004391bd  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004391be  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004391bf  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004391c0  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004391c1  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x8b 0xc0 */
void Application::sub_4391d0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004391d0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004391d1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004391d2  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004391d3  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004391d4  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004391d5  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004391d7  83ec08                 -sub esp, 8
    (cpu.esp) -= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 004391da  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 004391dd  89d7                   -mov edi, edx
    cpu.edi = cpu.edx;
    // 004391df  e8ecf9ffff             -call 0x438bd0
    cpu.esp -= 4;
    nfs3hp::load::carCount(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004391e4  8945f8                 -mov dword ptr [ebp - 8], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.eax;
    // 004391e7  c1e003                 -shl eax, 3
    cpu.eax <<= 3 /*0x3*/ % 32;
    // 004391ea  8d5008                 -lea edx, [eax + 8]
    cpu.edx = x86::reg32(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 004391ed  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
    // 004391ef  b890765300             -mov eax, 0x537690
    cpu.eax = 5469840 /*0x537690*/;
    // 004391f4  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 004391f6  e825840a00             -call 0x4e1620
    cpu.esp -= 4;
    nfs3hp::ea::reservememadr(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004391fb  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 004391fd  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
L_0x004391ff:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004391ff  3b4df8                 +cmp ecx, dword ptr [ebp - 8]
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00439202  7d34                   -jge 0x439238
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00439238;
    }
    // 00439204  f645fc01               +test byte ptr [ebp - 4], 1
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-4) /* -0x4 */) & 1 /*0x1*/));
    // 00439208  750e                   -jne 0x439218
    if (!cpu.flags.zf)
    {
        goto L_0x00439218;
    }
    // 0043920a  8b55fc                 -mov edx, dword ptr [ebp - 4]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 0043920d  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 0043920f  e8dcfeffff             -call 0x4390f0
    cpu.esp -= 4;
    sub_4390f0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00439214  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00439216  741d                   -je 0x439235
    if (cpu.flags.zf)
    {
        goto L_0x00439235;
    }
L_0x00439218:
    // 00439218  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 0043921a  e831080000             -call 0x439a50
    cpu.esp -= 4;
    nfs3hp::load::carRecord(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0043921f  f6808003000008         +test byte ptr [eax + 0x380], 8
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(cpu.eax + x86::reg32(896) /* 0x380 */) & 8 /*0x8*/));
    // 00439226  750d                   -jne 0x439235
    if (!cpu.flags.zf)
    {
        goto L_0x00439235;
    }
    // 00439228  43                     -inc ebx
    (cpu.ebx)++;
    // 00439229  83c010                 +add eax, 0x10
    {
        x86::reg32& tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(16 /*0x10*/));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 0043922c  c644defc00             -mov byte ptr [esi + ebx*8 - 4], 0
    app->getMemory<x86::reg8>(cpu.esi + x86::reg32(-4) /* -0x4 */ + cpu.ebx * 8) = 0 /*0x0*/;
    // 00439231  8944def8               -mov dword ptr [esi + ebx*8 - 8], eax
    app->getMemory<x86::reg32>(cpu.esi + x86::reg32(-8) /* -0x8 */ + cpu.ebx * 8) = cpu.eax;
L_0x00439235:
    // 00439235  41                     +inc ecx
    {
        x86::reg32& tmp = cpu.ecx;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 00439236  ebc7                   -jmp 0x4391ff
    goto L_0x004391ff;
L_0x00439238:
    // 00439238  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 0043923a  891f                   -mov dword ptr [edi], ebx
    app->getMemory<x86::reg32>(cpu.edi) = cpu.ebx;
    // 0043923c  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 0043923e  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043923f  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00439240  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00439241  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00439242  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00439243  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_439250: native, nfs3hp::load::carName */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 */
void Application::sub_439290(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00439290  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00439291  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00439293  e8b8070000             -call 0x439a50
    cpu.esp -= 4;
    nfs3hp::load::carRecord(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00439298  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0043929a  7405                   -je 0x4392a1
    if (cpu.flags.zf)
    {
        goto L_0x004392a1;
    }
    // 0043929c  0515030000             -add eax, 0x315
    (cpu.eax) += x86::reg32(x86::sreg32(789 /*0x315*/));
L_0x004392a1:
    // 004392a1  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004392a2  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_4392b0: native, nfs3hp::load::carFolder */

/* sub_439300: native, nfs3hp::load::carFilePrefix */

/* sub_439360: native, nfs3hp::port::obj3d::carVivPath */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x8b 0xc0 */
void Application::sub_439450(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00439450  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00439451  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00439452  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00439453  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00439454  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00439455  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00439457  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 00439459  e8f2050000             -call 0x439a50
    cpu.esp -= 4;
    nfs3hp::load::carRecord(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0043945e  beb4287a00             -mov esi, 0x7a28b4
    cpu.esi = 8005812 /*0x7a28b4*/;
    // 00439463  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00439465  89d7                   -mov edi, edx
    cpu.edi = cpu.edx;
    // 00439467  c60200                 -mov byte ptr [edx], 0
    app->getMemory<x86::reg8>(cpu.edx) = 0 /*0x0*/;
    // 0043946a  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
L_0x0043946b:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 0043946b  8a06                   -mov al, byte ptr [esi]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi);
    // 0043946d  8807                   -mov byte ptr [edi], al
    app->getMemory<x86::reg8>(cpu.edi) = cpu.al;
    // 0043946f  3c00                   +cmp al, 0
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
    // 00439471  7410                   -je 0x439483
    if (cpu.flags.zf)
    {
        goto L_0x00439483;
    }
    // 00439473  8a4601                 -mov al, byte ptr [esi + 1]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi + x86::reg32(1) /* 0x1 */);
    // 00439476  83c602                 -add esi, 2
    (cpu.esi) += x86::reg32(x86::sreg32(2 /*0x2*/));
    // 00439479  884701                 -mov byte ptr [edi + 1], al
    app->getMemory<x86::reg8>(cpu.edi + x86::reg32(1) /* 0x1 */) = cpu.al;
    // 0043947c  83c702                 -add edi, 2
    (cpu.edi) += x86::reg32(x86::sreg32(2 /*0x2*/));
    // 0043947f  3c00                   +cmp al, 0
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
    // 00439481  75e8                   -jne 0x43946b
    if (!cpu.flags.zf)
    {
        goto L_0x0043946b;
    }
L_0x00439483:
    // 00439483  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00439484  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 00439486  8db110010000           -lea esi, [ecx + 0x110]
    cpu.esi = x86::reg32(cpu.ecx + x86::reg32(272) /* 0x110 */);
    // 0043948c  e8afeeffff             -call 0x438340
    cpu.esp -= 4;
    nfs3hp::load::endWithSlash(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00439491  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00439492  2bc9                   +sub ecx, ecx
    {
        x86::reg32& tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ecx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 00439494  49                     +dec ecx
    {
        x86::reg32& tmp = cpu.ecx;
        cpu.flags.of = 1 & (tmp >> 31);
        tmp--;
        cpu.flags.of &= ~(1 & (tmp >> 31));
        cpu.set_szp(tmp);
    }
    // 00439495  b000                   -mov al, 0
    cpu.al = 0 /*0x0*/;
    // 00439497  f2ae                   -repne scasb al, byte ptr es:[edi]
    while (cpu.ecx)
    {
        {
            x86::reg8 tmp1 = cpu.al;
            x86::reg8 tmp2 = x86::reg8(x86::sreg8(app->getMemory<x86::reg8>(cpu.ees + cpu.edi)));
            x86::reg8 result = tmp1 - tmp2;
            cpu.flags.cf = tmp1 < tmp2;
            cpu.flags.of = 1 & (tmp1 >> 7);
            cpu.flags.of ^= 1 & (result >> 7);
            cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
            cpu.set_szp(result);
        }
        if (cpu.flags.df)
        {
            cpu.edi -= 1;
        }
        else
        {
            cpu.edi += 1;
        }
        --cpu.ecx;
        if (cpu.flags.zf)
            break;
    }
    // 00439499  4f                     -dec edi
    (cpu.edi)--;
L_0x0043949a:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 0043949a  8a06                   -mov al, byte ptr [esi]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi);
    // 0043949c  8807                   -mov byte ptr [edi], al
    app->getMemory<x86::reg8>(cpu.edi) = cpu.al;
    // 0043949e  3c00                   +cmp al, 0
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
    // 004394a0  7410                   -je 0x4394b2
    if (cpu.flags.zf)
    {
        goto L_0x004394b2;
    }
    // 004394a2  8a4601                 -mov al, byte ptr [esi + 1]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi + x86::reg32(1) /* 0x1 */);
    // 004394a5  83c602                 -add esi, 2
    (cpu.esi) += x86::reg32(x86::sreg32(2 /*0x2*/));
    // 004394a8  884701                 -mov byte ptr [edi + 1], al
    app->getMemory<x86::reg8>(cpu.edi + x86::reg32(1) /* 0x1 */) = cpu.al;
    // 004394ab  83c702                 -add edi, 2
    (cpu.edi) += x86::reg32(x86::sreg32(2 /*0x2*/));
    // 004394ae  3c00                   +cmp al, 0
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
    // 004394b0  75e8                   -jne 0x43949a
    if (!cpu.flags.zf)
    {
        goto L_0x0043949a;
    }
L_0x004394b2:
    // 004394b2  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004394b3  be98765300             -mov esi, 0x537698
    cpu.esi = 5469848 /*0x537698*/;
    // 004394b8  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004394b9  2bc9                   +sub ecx, ecx
    {
        x86::reg32& tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ecx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 004394bb  49                     +dec ecx
    {
        x86::reg32& tmp = cpu.ecx;
        cpu.flags.of = 1 & (tmp >> 31);
        tmp--;
        cpu.flags.of &= ~(1 & (tmp >> 31));
        cpu.set_szp(tmp);
    }
    // 004394bc  b000                   -mov al, 0
    cpu.al = 0 /*0x0*/;
    // 004394be  f2ae                   -repne scasb al, byte ptr es:[edi]
    while (cpu.ecx)
    {
        {
            x86::reg8 tmp1 = cpu.al;
            x86::reg8 tmp2 = x86::reg8(x86::sreg8(app->getMemory<x86::reg8>(cpu.ees + cpu.edi)));
            x86::reg8 result = tmp1 - tmp2;
            cpu.flags.cf = tmp1 < tmp2;
            cpu.flags.of = 1 & (tmp1 >> 7);
            cpu.flags.of ^= 1 & (result >> 7);
            cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
            cpu.set_szp(result);
        }
        if (cpu.flags.df)
        {
            cpu.edi -= 1;
        }
        else
        {
            cpu.edi += 1;
        }
        --cpu.ecx;
        if (cpu.flags.zf)
            break;
    }
    // 004394c0  4f                     -dec edi
    (cpu.edi)--;
L_0x004394c1:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004394c1  8a06                   -mov al, byte ptr [esi]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi);
    // 004394c3  8807                   -mov byte ptr [edi], al
    app->getMemory<x86::reg8>(cpu.edi) = cpu.al;
    // 004394c5  3c00                   +cmp al, 0
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
    // 004394c7  7410                   -je 0x4394d9
    if (cpu.flags.zf)
    {
        goto L_0x004394d9;
    }
    // 004394c9  8a4601                 -mov al, byte ptr [esi + 1]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi + x86::reg32(1) /* 0x1 */);
    // 004394cc  83c602                 -add esi, 2
    (cpu.esi) += x86::reg32(x86::sreg32(2 /*0x2*/));
    // 004394cf  884701                 -mov byte ptr [edi + 1], al
    app->getMemory<x86::reg8>(cpu.edi + x86::reg32(1) /* 0x1 */) = cpu.al;
    // 004394d2  83c702                 -add edi, 2
    (cpu.edi) += x86::reg32(x86::sreg32(2 /*0x2*/));
    // 004394d5  3c00                   +cmp al, 0
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
    // 004394d7  75e8                   -jne 0x4394c1
    if (!cpu.flags.zf)
    {
        goto L_0x004394c1;
    }
L_0x004394d9:
    // 004394d9  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004394da  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 004394dc  e81ffeffff             -call 0x439300
    cpu.esp -= 4;
    nfs3hp::load::carFilePrefix(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004394e1  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 004394e3  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004394e4  2bc9                   +sub ecx, ecx
    {
        x86::reg32& tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ecx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 004394e6  49                     +dec ecx
    {
        x86::reg32& tmp = cpu.ecx;
        cpu.flags.of = 1 & (tmp >> 31);
        tmp--;
        cpu.flags.of &= ~(1 & (tmp >> 31));
        cpu.set_szp(tmp);
    }
    // 004394e7  b000                   -mov al, 0
    cpu.al = 0 /*0x0*/;
    // 004394e9  f2ae                   -repne scasb al, byte ptr es:[edi]
    while (cpu.ecx)
    {
        {
            x86::reg8 tmp1 = cpu.al;
            x86::reg8 tmp2 = x86::reg8(x86::sreg8(app->getMemory<x86::reg8>(cpu.ees + cpu.edi)));
            x86::reg8 result = tmp1 - tmp2;
            cpu.flags.cf = tmp1 < tmp2;
            cpu.flags.of = 1 & (tmp1 >> 7);
            cpu.flags.of ^= 1 & (result >> 7);
            cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
            cpu.set_szp(result);
        }
        if (cpu.flags.df)
        {
            cpu.edi -= 1;
        }
        else
        {
            cpu.edi += 1;
        }
        --cpu.ecx;
        if (cpu.flags.zf)
            break;
    }
    // 004394eb  4f                     -dec edi
    (cpu.edi)--;
L_0x004394ec:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004394ec  8a06                   -mov al, byte ptr [esi]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi);
    // 004394ee  8807                   -mov byte ptr [edi], al
    app->getMemory<x86::reg8>(cpu.edi) = cpu.al;
    // 004394f0  3c00                   +cmp al, 0
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
    // 004394f2  7410                   -je 0x439504
    if (cpu.flags.zf)
    {
        goto L_0x00439504;
    }
    // 004394f4  8a4601                 -mov al, byte ptr [esi + 1]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi + x86::reg32(1) /* 0x1 */);
    // 004394f7  83c602                 -add esi, 2
    (cpu.esi) += x86::reg32(x86::sreg32(2 /*0x2*/));
    // 004394fa  884701                 -mov byte ptr [edi + 1], al
    app->getMemory<x86::reg8>(cpu.edi + x86::reg32(1) /* 0x1 */) = cpu.al;
    // 004394fd  83c702                 -add edi, 2
    (cpu.edi) += x86::reg32(x86::sreg32(2 /*0x2*/));
    // 00439500  3c00                   +cmp al, 0
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
    // 00439502  75e8                   -jne 0x4394ec
    if (!cpu.flags.zf)
    {
        goto L_0x004394ec;
    }
L_0x00439504:
    // 00439504  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00439505  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00439506  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00439507  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00439508  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00439509  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043950a  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x40 0x00 0x8b 0xc9 */
void Application::sub_439510(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00439510  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00439511  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00439513  e838050000             -call 0x439a50
    cpu.esp -= 4;
    nfs3hp::load::carRecord(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00439518  0594030000             -add eax, 0x394
    (cpu.eax) += x86::reg32(x86::sreg32(916 /*0x394*/));
    // 0043951d  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043951e  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_439520: native, nfs3hp::load::carId */

/* align: skip 0x90 */
void Application::sub_439530(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00439530  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00439531  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00439532  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00439534  e857040000             -call 0x439990
    cpu.esp -= 4;
    nfs3hp::load::findCarById(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00439539  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 0043953b  e830000000             -call 0x439570
    cpu.esp -= 4;
    nfs3hp::load::carFlag40(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00439540  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00439542  7405                   -je 0x439549
    if (cpu.flags.zf)
    {
        goto L_0x00439549;
    }
    // 00439544  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00439546  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00439547  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00439548  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x00439549:
    // 00439549  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 0043954b  e830010000             -call 0x439680
    cpu.esp -= 4;
    nfs3hp::load::carIsBonus(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00439550  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00439552  7405                   -je 0x439559
    if (cpu.flags.zf)
    {
        goto L_0x00439559;
    }
    // 00439554  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00439556  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00439557  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00439558  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x00439559:
    // 00439559  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 0043955e  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043955f  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00439560  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_439570: native, nfs3hp::load::carFlag40 */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x90 */
void Application::sub_439590(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00439590  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00439591  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00439593  e8f8030000             -call 0x439990
    cpu.esp -= 4;
    nfs3hp::load::findCarById(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00439598  e8d3ffffff             -call 0x439570
    cpu.esp -= 4;
    nfs3hp::load::carFlag40(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0043959d  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043959e  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x90 */
void Application::sub_4395a0(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004395a0  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004395a1  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004395a3  e8a8040000             -call 0x439a50
    cpu.esp -= 4;
    nfs3hp::load::carRecord(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004395a8  8b8080030000           -mov eax, dword ptr [eax + 0x380]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(896) /* 0x380 */);
    // 004395ae  83e008                 -and eax, 8
    cpu.eax &= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 004395b1  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004395b2  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_4395c0: native, nfs3hp::load::carFlag4 */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x90 */
void Application::sub_4395e0(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004395e0  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004395e1  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004395e3  e868040000             -call 0x439a50
    cpu.esp -= 4;
    nfs3hp::load::carRecord(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004395e8  8b8080030000           -mov eax, dword ptr [eax + 0x380]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(896) /* 0x380 */);
    // 004395ee  83e002                 -and eax, 2
    cpu.eax &= x86::reg32(x86::sreg32(2 /*0x2*/));
    // 004395f1  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004395f2  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x90 */
void Application::sub_439600(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00439600  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00439601  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00439603  e888030000             -call 0x439990
    cpu.esp -= 4;
    nfs3hp::load::findCarById(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00439608  e8d3ffffff             -call 0x4395e0
    cpu.esp -= 4;
    sub_4395e0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0043960d  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043960e  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_439610: native, nfs3hp::load::carHasNumericId */

/* sub_439620: native, nfs3hp::load::idIsNumeric */

/* sub_439660: native, nfs3hp::load::numericId */

/* sub_439680: native, nfs3hp::load::carIsBonus */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x90 */
void Application::sub_4396a0(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004396a0  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004396a1  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004396a3  e8e8020000             -call 0x439990
    cpu.esp -= 4;
    nfs3hp::load::findCarById(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004396a8  e8d3ffffff             -call 0x439680
    cpu.esp -= 4;
    nfs3hp::load::carIsBonus(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004396ad  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004396ae  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_4396b0: native, nfs3hp::load::carIsPolice */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x90 */
void Application::sub_4396d0(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004396d0  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004396d1  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004396d3  e8b8020000             -call 0x439990
    cpu.esp -= 4;
    nfs3hp::load::findCarById(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004396d8  e8d3ffffff             -call 0x4396b0
    cpu.esp -= 4;
    nfs3hp::load::carIsPolice(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004396dd  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004396de  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_4396e0: native, nfs3hp::load::carIsFerrariOrMercedes */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x90 */
void Application::sub_439700(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00439700  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00439701  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00439703  e888020000             -call 0x439990
    cpu.esp -= 4;
    nfs3hp::load::findCarById(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00439708  e8d3ffffff             -call 0x4396e0
    cpu.esp -= 4;
    nfs3hp::load::carIsFerrariOrMercedes(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0043970d  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043970e  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x90 */
void Application::sub_439710(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00439710  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00439711  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00439713  e838030000             -call 0x439a50
    cpu.esp -= 4;
    nfs3hp::load::carRecord(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00439718  8a80a0030000           -mov al, byte ptr [eax + 0x3a0]
    cpu.al = app->getMemory<x86::reg8>(cpu.eax + x86::reg32(928) /* 0x3a0 */);
    // 0043971e  25ff000000             -and eax, 0xff
    cpu.eax &= x86::reg32(x86::sreg32(255 /*0xff*/));
    // 00439723  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00439724  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_439730: native, nfs3hp::load::carClass */

/* align: skip  */
void Application::sub_439740(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00439740  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00439741  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00439743  e808030000             -call 0x439a50
    cpu.esp -= 4;
    nfs3hp::load::carRecord(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00439748  8b8084030000           -mov eax, dword ptr [eax + 0x384]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(900) /* 0x384 */);
    // 0043974e  83e00f                 -and eax, 0xf
    cpu.eax &= x86::reg32(x86::sreg32(15 /*0xf*/));
    // 00439751  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00439752  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_439760: native, nfs3hp::port::fields::carColourCount */

/* sub_439780: native, nfs3hp::port::fields::carCustomColour */

/* sub_439790: native, nfs3hp::port::fields::carColour */

/* sub_4397c0: native, nfs3hp::port::fields::carColourName */

/* sub_4397d0: native, nfs3hp::port::fields::setCarColour */

/* sub_439810: native, nfs3hp::port::fields::carColourRgb */

/* sub_4398c0: native, nfs3hp::port::fields::setCarCustomColour */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x8b 0xc0 */
void Application::sub_439930(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00439930  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00439931  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00439933  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00439935  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00439936  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 */
void Application::sub_439940(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00439940  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00439941  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00439943  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00439945  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00439946  c20c00                 -ret 0xc
    cpu.esp += 4+12 /*0xc*/;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x90 */
void Application::sub_439950(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00439950  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00439951  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00439953  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00439955  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00439956  c20800                 -ret 8
    cpu.esp += 4+8 /*0x8*/;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x90 */
void Application::sub_439960(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00439960  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00439961  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00439963  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00439965  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00439966  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 */
void Application::sub_439970(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00439970  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00439971  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00439973  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00439975  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00439976  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 */
void Application::sub_439980(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00439980  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00439981  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00439983  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00439985  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00439986  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_439990: native, nfs3hp::load::findCarById */

/* sub_4399f0: native, nfs3hp::load::clearCarCache */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 */
void Application::sub_439a10(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00439a10  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00439a11  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00439a12  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00439a14  8b1485844f5500         -mov edx, dword ptr [eax*4 + 0x554f84]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5590916) /* 0x554f84 */ + cpu.eax * 4);
    // 00439a1b  b8c0d26f00             -mov eax, 0x6fd2c0
    cpu.eax = 7328448 /*0x6fd2c0*/;
    // 00439a20  e8abf0ffff             -call 0x438ad0
    cpu.esp -= 4;
    nfs3hp::load::makeCarId(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00439a25  b8c0d26f00             -mov eax, 0x6fd2c0
    cpu.eax = 7328448 /*0x6fd2c0*/;
    // 00439a2a  e861ffffff             -call 0x439990
    cpu.esp -= 4;
    nfs3hp::load::findCarById(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00439a2f  a3bcd26f00             -mov dword ptr [0x6fd2bc], eax
    app->getMemory<x86::reg32>(x86::reg32(7328444) /* 0x6fd2bc */) = cpu.eax;
    // 00439a34  e8f7fcffff             -call 0x439730
    cpu.esp -= 4;
    nfs3hp::load::carClass(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00439a39  a3d0d26f00             -mov dword ptr [0x6fd2d0], eax
    app->getMemory<x86::reg32>(x86::reg32(7328464) /* 0x6fd2d0 */) = cpu.eax;
    // 00439a3e  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00439a3f  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00439a40  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_439a50: native, nfs3hp::load::carRecord */

/* sub_439ab0: native, nfs3hp::port::fields::carText */

/* sub_439af0: native, nfs3hp::load::fecText */

/* sub_439b20: native, nfs3hp::load::findCarByName */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 */
void Application::sub_439b70(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00439b70  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00439b71  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00439b72  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
L_0x00439b74:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00439b74  8b15704f5500           -mov edx, dword ptr [0x554f70]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5590896) /* 0x554f70 */);
    // 00439b7a  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 00439b7c  7427                   -je 0x439ba5
    if (cpu.flags.zf)
    {
        goto L_0x00439ba5;
    }
    // 00439b7e  8b02                   -mov eax, dword ptr [edx]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edx);
    // 00439b80  a3704f5500             -mov dword ptr [0x554f70], eax
    app->getMemory<x86::reg32>(x86::reg32(5590896) /* 0x554f70 */) = cpu.eax;
    // 00439b85  f6828003000008         +test byte ptr [edx + 0x380], 8
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(cpu.edx + x86::reg32(896) /* 0x380 */) & 8 /*0x8*/));
    // 00439b8c  7407                   -je 0x439b95
    if (cpu.flags.zf)
    {
        goto L_0x00439b95;
    }
    // 00439b8e  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 00439b90  e80b170000             -call 0x43b2a0
    cpu.esp -= 4;
    sub_43b2a0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00439b95:
    // 00439b95  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 00439b97  e814000000             -call 0x439bb0
    cpu.esp -= 4;
    sub_439bb0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00439b9c  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 00439b9e  e8ed7c0a00             -call 0x4e1890
    cpu.esp -= 4;
    nfs3hp::ea::purgememadr(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00439ba3  ebcf                   -jmp 0x439b74
    goto L_0x00439b74;
L_0x00439ba5:
    // 00439ba5  8915704f5500           -mov dword ptr [0x554f70], edx
    app->getMemory<x86::reg32>(x86::reg32(5590896) /* 0x554f70 */) = cpu.edx;
    // 00439bab  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00439bad  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00439bae  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00439baf  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip  */
void Application::sub_439bb0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00439bb0  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00439bb1  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00439bb3  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00439bb5  7507                   -jne 0x439bbe
    if (!cpu.flags.zf)
    {
        goto L_0x00439bbe;
    }
    // 00439bb7  b8ffffffff             -mov eax, 0xffffffff
    cpu.eax = 4294967295 /*0xffffffff*/;
    // 00439bbc  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00439bbd  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x00439bbe:
    // 00439bbe  83c004                 -add eax, 4
    (cpu.eax) += x86::reg32(x86::sreg32(4 /*0x4*/));
    // 00439bc1  e82a000000             -call 0x439bf0
    cpu.esp -= 4;
    sub_439bf0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00439bc6  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00439bc8  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00439bc9  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_439bd0: native, nfs3hp::load::attachFecTexts */

/* align: skip 0x8b 0xc0 */
void Application::sub_439bf0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00439bf0  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00439bf1  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00439bf2  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00439bf4  8b5004                 -mov edx, dword ptr [eax + 4]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 00439bf7  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 00439bf9  7407                   -je 0x439c02
    if (cpu.flags.zf)
    {
        goto L_0x00439c02;
    }
    // 00439bfb  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 00439bfd  e88e7c0a00             -call 0x4e1890
    cpu.esp -= 4;
    nfs3hp::ea::purgememadr(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00439c02:
    // 00439c02  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00439c04  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00439c05  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00439c06  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_439c10: native, nfs3hp::load::bonusCarLocked */

/* align: skip 0x90 */
void Application::sub_439cc0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00439cc0  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00439cc1  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00439cc3  e888fdffff             -call 0x439a50
    cpu.esp -= 4;
    nfs3hp::load::carRecord(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00439cc8  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00439cca  7405                   -je 0x439cd1
    if (cpu.flags.zf)
    {
        goto L_0x00439cd1;
    }
    // 00439ccc  e83fffffff             -call 0x439c10
    cpu.esp -= 4;
    nfs3hp::load::bonusCarLocked(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00439cd1:
    // 00439cd1  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00439cd2  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x90 */
void Application::sub_439ce0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00439ce0  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00439ce1  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00439ce2  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00439ce4  83ec10                 -sub esp, 0x10
    (cpu.esp) -= x86::reg32(x86::sreg32(16 /*0x10*/));
    // 00439ce7  ba25000000             -mov edx, 0x25
    cpu.edx = 37 /*0x25*/;
    // 00439cec  8d45f0                 -lea eax, [ebp - 0x10]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 00439cef  e8dcedffff             -call 0x438ad0
    cpu.esp -= 4;
    nfs3hp::load::makeCarId(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00439cf4  8d45f0                 -lea eax, [ebp - 0x10]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 00439cf7  e894fcffff             -call 0x439990
    cpu.esp -= 4;
    nfs3hp::load::findCarById(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00439cfc  83f8ff                 +cmp eax, -1
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
    // 00439cff  7507                   -jne 0x439d08
    if (!cpu.flags.zf)
    {
        goto L_0x00439d08;
    }
    // 00439d01  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00439d03  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00439d05  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00439d06  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00439d07  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x00439d08:
    // 00439d08  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 00439d0d  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00439d0f  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00439d10  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00439d11  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_439d20: native, nfs3hp::load::checkDuplicateCars */

/* sub_439d90: native, nfs3hp::load::loadCarList */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x8b 0xc0 */
void Application::sub_43a4d0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0043a4d0  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 0043a4d1  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 0043a4d3  8b12                   -mov edx, dword ptr [edx]
    cpu.edx = app->getMemory<x86::reg32>(cpu.edx);
    // 0043a4d5  8b00                   -mov eax, dword ptr [eax]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax);
    // 0043a4d7  83c210                 -add edx, 0x10
    (cpu.edx) += x86::reg32(x86::sreg32(16 /*0x10*/));
    // 0043a4da  83c010                 -add eax, 0x10
    (cpu.eax) += x86::reg32(x86::sreg32(16 /*0x10*/));
    // 0043a4dd  e82e3e0b00             -call 0x4ee310
    cpu.esp -= 4;
    nfs3hp::watcom::strcmp(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0043a4e2  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0043a4e3  c3                     -ret 
    cpu.esp += 4;
    return;
}

}
