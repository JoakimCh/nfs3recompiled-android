#include "nfs3hp.h"
#include <lib/thread.h>

namespace nfs3hp
{
// Port (tools/apply_native_frontend.py): defined in native_frontend_cars.cpp.
bool tuningOnExit(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_cars.cpp.
bool tuningOnEnter(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_cars.cpp.
bool tuningPrepare(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_cars.cpp.
bool tuningFitButtons(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_cars.cpp.
bool tuningBindDoneCancel(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_cars.cpp.
bool tuningDefaultsKey(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_cars.cpp.
bool tuningCarListKey(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_cars.cpp.
bool tuningCancelKey(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_cars.cpp.
bool tuningDoneKey(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_cars.cpp.
bool tuningDefaultsAnswered(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_cars.cpp.
bool tuningLoadAdvanced(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_cars.cpp.
bool tuningBindSliders(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_cars.cpp.
bool tuningSlidersMoved(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_cars.cpp.
bool tuningRememberSliders(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_cars.cpp.
bool tuningSetSliders(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_cars.cpp.
bool tuningTiresMoved(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_cars.cpp.
bool tuningAeroMoved(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_cars.cpp.
bool tuningSuspensionMoved(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_cars.cpp.
bool tuningGearsMoved(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_cars.cpp.
bool tuningSteeringMoved(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_cars.cpp.
bool tuningBrakesMoved(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_cars.cpp.
bool tuningEngineMoved(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_cars.cpp.
bool tuningSave(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_cars.cpp.
bool tuningLoad(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_cars.cpp.
bool opponentOnFrame(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_cars.cpp.
bool opponentOnExit(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_cars.cpp.
bool opponentOnEnter(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_cars.cpp.
bool opponentFitArt(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_cars.cpp.
bool opponentFitCar(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_cars.cpp.
bool car2ColourClicked(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_cars.cpp.
bool car1ColourClicked(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_cars.cpp.
bool car2EditClicked(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_cars.cpp.
bool car1EditClicked(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_cars.cpp.
bool car2OnExit(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_cars.cpp.
bool car1OnExit(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_cars.cpp.
bool car2OnFrame(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_cars.cpp.
bool car1OnFrame(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_cars.cpp.
bool car2OnEnter(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_cars.cpp.
bool car1OnEnter(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_cars.cpp.
bool trackRecord(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_cars.cpp.
bool carRecord(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_cars.cpp.
bool trackSaveFrame(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_cars.cpp.
bool carSaveFrame(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_text_entry.py): defined in nfs3hp_main.cpp.
void textEntry(bool taking);

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 0x8b 0xdb */
void Application::sub_4262a0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004262a0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004262a1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004262a2  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004262a3  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004262a4  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004262a6  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 004262a8  83b81801000000         +cmp dword ptr [eax + 0x118], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(280) /* 0x118 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004262af  744f                   -je 0x426300
    if (cpu.flags.zf)
    {
        goto L_0x00426300;
    }
    // 004262b1  8b981c010000           -mov ebx, dword ptr [eax + 0x11c]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(284) /* 0x11c */);
    // 004262b7  85db                   +test ebx, ebx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & cpu.ebx));
    // 004262b9  7445                   -je 0x426300
    if (cpu.flags.zf)
    {
        goto L_0x00426300;
    }
    // 004262bb  81b8100100000000803f   +cmp dword ptr [eax + 0x110], 0x3f800000
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(272) /* 0x110 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1065353216 /*0x3f800000*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004262c5  7e1d                   -jle 0x4262e4
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004262e4;
    }
    // 004262c7  89da                   -mov edx, ebx
    cpu.edx = cpu.ebx;
    // 004262c9  8b400c                 -mov eax, dword ptr [eax + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
    // 004262cc  e8dfd5ffff             -call 0x4238b0
    cpu.esp -= 4;
    nfs3hp::carstate::setCameraMode(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004262d1  8b510c                 -mov edx, dword ptr [ecx + 0xc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(12) /* 0xc */);
    // 004262d4  8b811c010000           -mov eax, dword ptr [ecx + 0x11c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(284) /* 0x11c */);
    // 004262da  e871010000             -call 0x426450
    cpu.esp -= 4;
    sub_426450(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004262df  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004262e0  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004262e1  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004262e2  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004262e3  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004262e4:
    // 004262e4  8b500c                 -mov edx, dword ptr [eax + 0xc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
    // 004262e7  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 004262e9  e862010000             -call 0x426450
    cpu.esp -= 4;
    sub_426450(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004262ee  d98114010000           -fld dword ptr [ecx + 0x114]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(276) /* 0x114 */));
    // 004262f4  d88110010000           -fadd dword ptr [ecx + 0x110]
    x86::Float fpu2 = cpu.fpu.add(fpu1, x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(272) /* 0x110 */)));
    // 004262fa  d99910010000           -fstp dword ptr [ecx + 0x110]
    app->getMemory<float>(cpu.ecx + x86::reg32(272) /* 0x110 */) = float(fpu2);
    }
L_0x00426300:
    // 00426300  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426301  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426302  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426303  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426304  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 0x8b 0xdb */
void Application::sub_426310(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00426310  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00426311  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00426312  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00426313  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00426314  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00426315  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00426317  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 00426319  8d0c8500000000         -lea ecx, [eax*4]
    cpu.ecx = x86::reg32(cpu.eax * 4);
    // 00426320  8b91b0105e00           -mov edx, dword ptr [ecx + 0x5e10b0]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(6164656) /* 0x5e10b0 */);
    // 00426326  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 00426328  7431                   -je 0x42635b
    if (cpu.flags.zf)
    {
        goto L_0x0042635b;
    }
    // 0042632a  8b02                   -mov eax, dword ptr [edx]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edx);
    // 0042632c  83f813                 +cmp eax, 0x13
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
    // 0042632f  752a                   -jne 0x42635b
    if (!cpu.flags.zf)
    {
        goto L_0x0042635b;
    }
    // 00426331  8b81602f5500           -mov eax, dword ptr [ecx + 0x552f60]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(5582688) /* 0x552f60 */);
    // 00426337  8b901c010000           -mov edx, dword ptr [eax + 0x11c]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(284) /* 0x11c */);
    // 0042633d  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 0042633f  e86cd5ffff             -call 0x4238b0
    cpu.esp -= 4;
    nfs3hp::carstate::setCameraMode(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426344  8bb1b0105e00           -mov esi, dword ptr [ecx + 0x5e10b0]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(6164656) /* 0x5e10b0 */);
    // 0042634a  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 0042634c  7404                   -je 0x426352
    if (cpu.flags.zf)
    {
        goto L_0x00426352;
    }
    // 0042634e  8b06                   -mov eax, dword ptr [esi]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi);
    // 00426350  eb02                   -jmp 0x426354
    goto L_0x00426354;
L_0x00426352:
    // 00426352  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
L_0x00426354:
    // 00426354  89da                   -mov edx, ebx
    cpu.edx = cpu.ebx;
    // 00426356  e8f5000000             -call 0x426450
    cpu.esp -= 4;
    sub_426450(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x0042635b:
    // 0042635b  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042635c  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042635d  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042635e  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042635f  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426360  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x8d 0x40 0x00 */
void Application::sub_426370(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00426370  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00426371  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00426372  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00426373  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00426374  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00426376  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00426378  8b7004                 -mov esi, dword ptr [eax + 4]
    cpu.esi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 0042637b  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 0042637d  7452                   -je 0x4263d1
    if (cpu.flags.zf)
    {
        goto L_0x004263d1;
    }
    // 0042637f  8b7e1c                 -mov edi, dword ptr [esi + 0x1c]
    cpu.edi = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(28) /* 0x1c */);
    // 00426382  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00426383  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 00426385  8bb6a0000000           -mov esi, dword ptr [esi + 0xa0]
    cpu.esi = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(160) /* 0xa0 */);
    // 0042638b  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 0042638c  8bb89c000000           -mov edi, dword ptr [eax + 0x9c]
    cpu.edi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(156) /* 0x9c */);
    // 00426392  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00426393  8bb098000000           -mov esi, dword ptr [eax + 0x98]
    cpu.esi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(152) /* 0x98 */);
    // 00426399  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 0042639a  e851a8ffff             -call 0x420bf0
    cpu.esp -= 4;
    nfs3hp::trackdata::inTunnel(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042639f  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004263a1  7425                   -je 0x4263c8
    if (cpu.flags.zf)
    {
        goto L_0x004263c8;
    }
    // 004263a3  8bb984000000           -mov edi, dword ptr [ecx + 0x84]
    cpu.edi = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(132) /* 0x84 */);
    // 004263a9  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004263aa  8b411c                 -mov eax, dword ptr [ecx + 0x1c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(28) /* 0x1c */);
    // 004263ad  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004263ae  8b7118                 -mov esi, dword ptr [ecx + 0x18]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(24) /* 0x18 */);
    // 004263b1  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004263b2  8b7914                 -mov edi, dword ptr [ecx + 0x14]
    cpu.edi = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(20) /* 0x14 */);
    // 004263b5  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004263b6  e835a8ffff             -call 0x420bf0
    cpu.esp -= 4;
    nfs3hp::trackdata::inTunnel(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004263bb  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004263bd  7409                   -je 0x4263c8
    if (cpu.flags.zf)
    {
        goto L_0x004263c8;
    }
    // 004263bf  ff04d514105e00         +inc dword ptr [edx*8 + 0x5e1014]
    {
        auto tmp = app->getMemory<x86::reg32>(x86::reg32(6164500) /* 0x5e1014 */ + cpu.edx * 8);
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 004263c6  eb09                   -jmp 0x4263d1
    goto L_0x004263d1;
L_0x004263c8:
    // 004263c8  31f6                   -xor esi, esi
    cpu.esi ^= x86::reg32(x86::sreg32(cpu.esi));
    // 004263ca  8934d514105e00         -mov dword ptr [edx*8 + 0x5e1014], esi
    app->getMemory<x86::reg32>(x86::reg32(6164500) /* 0x5e1014 */ + cpu.edx * 8) = cpu.esi;
L_0x004263d1:
    // 004263d1  83fb08                 +cmp ebx, 8
    {
        x86::reg32 tmp1 = cpu.ebx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(8 /*0x8*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004263d4  7414                   -je 0x4263ea
    if (cpu.flags.zf)
    {
        goto L_0x004263ea;
    }
    // 004263d6  8b410c                 -mov eax, dword ptr [ecx + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(12) /* 0xc */);
    // 004263d9  8b0485082f5500         -mov eax, dword ptr [eax*4 + 0x552f08]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5582600) /* 0x552f08 */ + cpu.eax * 4);
    // 004263e0  c7802401000000000000   -mov dword ptr [eax + 0x124], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(292) /* 0x124 */) = 0 /*0x0*/;
L_0x004263ea:
    // 004263ea  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004263eb  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004263ec  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004263ed  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004263ee  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x90 */
void Application::sub_426450(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
  goto start;
dynamic_jump:
  switch(cpu.ip)
  {
start:
    // 00426450  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00426451  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00426452  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00426453  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00426454  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00426456  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 00426458  8d049500000000         -lea eax, [edx*4]
    cpu.eax = x86::reg32(cpu.edx * 4);
    // 0042645f  8b8cf0c82e5500         -mov ecx, dword ptr [eax + esi*8 + 0x552ec8]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(5582536) /* 0x552ec8 */ + cpu.esi * 8);
    // 00426466  89f3                   -mov ebx, esi
    cpu.ebx = cpu.esi;
    // 00426468  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 0042646a  e801ffffff             -call 0x426370
    cpu.esp -= 4;
    sub_426370(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042646f  8d56ff                 -lea edx, [esi - 1]
    cpu.edx = x86::reg32(cpu.esi + x86::reg32(-1) /* -0x1 */);
    // 00426472  83fa17                 +cmp edx, 0x17
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(23 /*0x17*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00426475  0f87da000000           -ja 0x426555
    if (!cpu.flags.cf && !cpu.flags.zf)
    {
        goto L_0x00426555;
    }
    // 0042647b  ff2495f0634200         -jmp dword ptr [edx*4 + 0x4263f0]
    cpu.ip = app->getMemory<x86::reg32>(4350960 + cpu.edx * 4); goto dynamic_jump;
  case 0x00426482:
    // 00426482  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00426484  e837dcffff             -call 0x4240c0
    cpu.esp -= 4;
    nfs3hp::carstate::chaseOffset(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426489  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042648a  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042648b  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042648c  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042648d  c3                     -ret 
    cpu.esp += 4;
    return;
  case 0x0042648e:
    // 0042648e  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00426490  e8cbddffff             -call 0x424260
    cpu.esp -= 4;
    nfs3hp::carstate::chaseOffsetLevel(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426495  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426496  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426497  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426498  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426499  c3                     -ret 
    cpu.esp += 4;
    return;
  case 0x0042649a:
    // 0042649a  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 0042649c  e89fe2ffff             -call 0x424740
    cpu.esp -= 4;
    sub_424740(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004264a1  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004264a2  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004264a3  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004264a4  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004264a5  c3                     -ret 
    cpu.esp += 4;
    return;
  case 0x004264a6:
    // 004264a6  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004264a8  e8f3deffff             -call 0x4243a0
    cpu.esp -= 4;
    sub_4243a0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004264ad  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004264ae  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004264af  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004264b0  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004264b1  c3                     -ret 
    cpu.esp += 4;
    return;
  case 0x004264b2:
    // 004264b2  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004264b4  e897e6ffff             -call 0x424b50
    cpu.esp -= 4;
    sub_424b50(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004264b9  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004264ba  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004264bb  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004264bc  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004264bd  c3                     -ret 
    cpu.esp += 4;
    return;
  case 0x004264be:
    // 004264be  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004264c0  e89bebffff             -call 0x425060
    cpu.esp -= 4;
    sub_425060(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004264c5  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004264c6  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004264c7  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004264c8  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004264c9  c3                     -ret 
    cpu.esp += 4;
    return;
  case 0x004264ca:
    // 004264ca  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004264cc  e87ff8ffff             -call 0x425d50
    cpu.esp -= 4;
    sub_425d50(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004264d1  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004264d2  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004264d3  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004264d4  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004264d5  c3                     -ret 
    cpu.esp += 4;
    return;
  case 0x004264d6:
    // 004264d6  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004264d8  e8b3f4ffff             -call 0x425990
    cpu.esp -= 4;
    sub_425990(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004264dd  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004264de  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004264df  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004264e0  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004264e1  c3                     -ret 
    cpu.esp += 4;
    return;
  case 0x004264e2:
    // 004264e2  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004264e4  e8c7f5ffff             -call 0x425ab0
    cpu.esp -= 4;
    sub_425ab0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004264e9  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004264ea  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004264eb  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004264ec  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004264ed  c3                     -ret 
    cpu.esp += 4;
    return;
  case 0x004264ee:
    // 004264ee  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004264f0  e8fbf6ffff             -call 0x425bf0
    cpu.esp -= 4;
    sub_425bf0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004264f5  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004264f6  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004264f7  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004264f8  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004264f9  c3                     -ret 
    cpu.esp += 4;
    return;
  case 0x004264fa:
    // 004264fa  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004264fc  e8cfeeffff             -call 0x4253d0
    cpu.esp -= 4;
    sub_4253d0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426501  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426502  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426503  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426504  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426505  c3                     -ret 
    cpu.esp += 4;
    return;
  case 0x00426506:
    // 00426506  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00426508  e833f1ffff             -call 0x425640
    cpu.esp -= 4;
    sub_425640(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042650d  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042650e  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042650f  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426510  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426511  c3                     -ret 
    cpu.esp += 4;
    return;
  case 0x00426512:
    // 00426512  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00426514  e8d7ecffff             -call 0x4251f0
    cpu.esp -= 4;
    sub_4251f0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426519  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042651a  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042651b  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042651c  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042651d  c3                     -ret 
    cpu.esp += 4;
    return;
  case 0x0042651e:
    // 0042651e  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00426520  e87bfdffff             -call 0x4262a0
    cpu.esp -= 4;
    sub_4262a0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426525  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426526  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426527  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426528  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426529  c3                     -ret 
    cpu.esp += 4;
    return;
  case 0x0042652a:
    // 0042652a  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 0042652c  e85ffdffff             -call 0x426290
    cpu.esp -= 4;
    sub_426290(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426531  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426532  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426533  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426534  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426535  c3                     -ret 
    cpu.esp += 4;
    return;
  case 0x00426536:
    // 00426536  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00426538  e853e1ffff             -call 0x424690
    cpu.esp -= 4;
    sub_424690(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042653d  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042653e  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042653f  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426540  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426541  c3                     -ret 
    cpu.esp += 4;
    return;
  case 0x00426542:
    // 00426542  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00426544  e897e7ffff             -call 0x424ce0
    cpu.esp -= 4;
    sub_424ce0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426549  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042654a  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042654b  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042654c  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042654d  c3                     -ret 
    cpu.esp += 4;
    return;
  case 0x0042654e:
    // 0042654e  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00426550  e8dbe8ffff             -call 0x424e30
    cpu.esp -= 4;
    sub_424e30(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
  [[fallthrough]];
  case 0x00426555:
L_0x00426555:
    // 00426555  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426556  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426557  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426558  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426559  c3                     -ret 
    cpu.esp += 4;
    return;
  default:
    NFS2_ASSERT(false);
  }
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 */
void Application::sub_426560(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00426560  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00426561  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00426562  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00426563  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00426564  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00426565  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00426566  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00426568  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 0042656a  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 0042656d  8b90b8105e00           -mov edx, dword ptr [eax + 0x5e10b8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164664) /* 0x5e10b8 */);
    // 00426573  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 00426575  7404                   -je 0x42657b
    if (cpu.flags.zf)
    {
        goto L_0x0042657b;
    }
    // 00426577  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 00426579  eb06                   -jmp 0x426581
    goto L_0x00426581;
L_0x0042657b:
    // 0042657b  8b80b0105e00           -mov eax, dword ptr [eax + 0x5e10b0]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164656) /* 0x5e10b0 */);
L_0x00426581:
    // 00426581  8d148d00000000         -lea edx, [ecx*4]
    cpu.edx = x86::reg32(cpu.ecx * 4);
    // 00426588  8b4004                 -mov eax, dword ptr [eax + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 0042658b  8bb2b8105e00           -mov esi, dword ptr [edx + 0x5e10b8]
    cpu.esi = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(6164664) /* 0x5e10b8 */);
    // 00426591  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
    // 00426593  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 00426595  7404                   -je 0x42659b
    if (cpu.flags.zf)
    {
        goto L_0x0042659b;
    }
    // 00426597  8b16                   -mov edx, dword ptr [esi]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi);
    // 00426599  eb02                   -jmp 0x42659d
    goto L_0x0042659d;
L_0x0042659b:
    // 0042659b  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
L_0x0042659d:
    // 0042659d  8b3da0367d00           -mov edi, dword ptr [0x7d36a0]
    cpu.edi = app->getMemory<x86::reg32>(x86::reg32(8205984) /* 0x7d36a0 */);
    // 004265a3  89d6                   -mov esi, edx
    cpu.esi = cpu.edx;
    // 004265a5  85ff                   +test edi, edi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edi & cpu.edi));
    // 004265a7  7415                   -je 0x4265be
    if (cpu.flags.zf)
    {
        goto L_0x004265be;
    }
    // 004265a9  833d6492550000         +cmp dword ptr [0x559264], 0
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
    // 004265b0  750c                   -jne 0x4265be
    if (!cpu.flags.zf)
    {
        goto L_0x004265be;
    }
    // 004265b2  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004265b4  bb17000000             -mov ebx, 0x17
    cpu.ebx = 23 /*0x17*/;
    // 004265b9  e976000000             -jmp 0x426634
    goto L_0x00426634;
L_0x004265be:
    // 004265be  83b8a409000000         +cmp dword ptr [eax + 0x9a4], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(2468) /* 0x9a4 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004265c5  742f                   -je 0x4265f6
    if (cpu.flags.zf)
    {
        goto L_0x004265f6;
    }
    // 004265c7  8d048d00000000         -lea eax, [ecx*4]
    cpu.eax = x86::reg32(cpu.ecx * 4);
    // 004265ce  8b90b8105e00           -mov edx, dword ptr [eax + 0x5e10b8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164664) /* 0x5e10b8 */);
    // 004265d4  bb15000000             -mov ebx, 0x15
    cpu.ebx = 21 /*0x15*/;
    // 004265d9  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 004265db  7404                   -je 0x4265e1
    if (cpu.flags.zf)
    {
        goto L_0x004265e1;
    }
    // 004265dd  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004265df  eb06                   -jmp 0x4265e7
    goto L_0x004265e7;
L_0x004265e1:
    // 004265e1  8b80b0105e00           -mov eax, dword ptr [eax + 0x5e10b0]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164656) /* 0x5e10b0 */);
L_0x004265e7:
    // 004265e7  8b148d702f5500         -mov edx, dword ptr [ecx*4 + 0x552f70]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5582704) /* 0x552f70 */ + cpu.ecx * 4);
    // 004265ee  8b4004                 -mov eax, dword ptr [eax + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 004265f1  894204                 -mov dword ptr [edx + 4], eax
    app->getMemory<x86::reg32>(cpu.edx + x86::reg32(4) /* 0x4 */) = cpu.eax;
    // 004265f4  eb43                   -jmp 0x426639
    goto L_0x00426639;
L_0x004265f6:
    // 004265f6  83b89c09000000         +cmp dword ptr [eax + 0x99c], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(2460) /* 0x99c */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004265fd  7407                   -je 0x426606
    if (cpu.flags.zf)
    {
        goto L_0x00426606;
    }
    // 004265ff  bb07000000             -mov ebx, 7
    cpu.ebx = 7 /*0x7*/;
    // 00426604  eb33                   -jmp 0x426639
    goto L_0x00426639;
L_0x00426606:
    // 00426606  83b88401000000         +cmp dword ptr [eax + 0x184], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(388) /* 0x184 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0042660d  7e07                   -jle 0x426616
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00426616;
    }
    // 0042660f  bb14000000             -mov ebx, 0x14
    cpu.ebx = 20 /*0x14*/;
    // 00426614  eb23                   -jmp 0x426639
    goto L_0x00426639;
L_0x00426616:
    // 00426616  83b82405000000         +cmp dword ptr [eax + 0x524], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(1316) /* 0x524 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0042661d  741a                   -je 0x426639
    if (cpu.flags.zf)
    {
        goto L_0x00426639;
    }
    // 0042661f  8b15f8d46f00           -mov edx, dword ptr [0x6fd4f8]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(7329016) /* 0x6fd4f8 */);
    // 00426625  3b15f4d46f00           +cmp edx, dword ptr [0x6fd4f4]
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(7329012) /* 0x6fd4f4 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0042662b  750c                   -jne 0x426639
    if (!cpu.flags.zf)
    {
        goto L_0x00426639;
    }
    // 0042662d  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 0042662f  bb18000000             -mov ebx, 0x18
    cpu.ebx = 24 /*0x18*/;
L_0x00426634:
    // 00426634  e8d7fcffff             -call 0x426310
    cpu.esp -= 4;
    sub_426310(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00426639:
    // 00426639  89da                   -mov edx, ebx
    cpu.edx = cpu.ebx;
    // 0042663b  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 0042663d  e81ed3ffff             -call 0x423960
    cpu.esp -= 4;
    nfs3hp::carstate::setOverrideMode(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426642  83fe18                 +cmp esi, 0x18
    {
        x86::reg32 tmp1 = cpu.esi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(24 /*0x18*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00426645  752c                   -jne 0x426673
    if (!cpu.flags.zf)
    {
        goto L_0x00426673;
    }
    // 00426647  85db                   +test ebx, ebx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & cpu.ebx));
    // 00426649  7528                   -jne 0x426673
    if (!cpu.flags.zf)
    {
        goto L_0x00426673;
    }
    // 0042664b  8d048d00000000         -lea eax, [ecx*4]
    cpu.eax = x86::reg32(cpu.ecx * 4);
    // 00426652  8b98b0105e00           -mov ebx, dword ptr [eax + 0x5e10b0]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164656) /* 0x5e10b0 */);
    // 00426658  85db                   +test ebx, ebx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & cpu.ebx));
    // 0042665a  7402                   -je 0x42665e
    if (cpu.flags.zf)
    {
        goto L_0x0042665e;
    }
    // 0042665c  8b1b                   -mov ebx, dword ptr [ebx]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.ebx);
L_0x0042665e:
    // 0042665e  ba18000000             -mov edx, 0x18
    cpu.edx = 24 /*0x18*/;
    // 00426663  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00426665  e846d2ffff             -call 0x4238b0
    cpu.esp -= 4;
    nfs3hp::carstate::setCameraMode(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042666a  89ca                   -mov edx, ecx
    cpu.edx = cpu.ecx;
    // 0042666c  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 0042666e  e89dbfffff             -call 0x422610
    cpu.esp -= 4;
    nfs3hp::carstate::switchCamera(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00426673:
    // 00426673  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426674  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426675  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426676  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426677  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426678  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426679  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 */
void Application::sub_426680(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00426680  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00426681  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00426682  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00426683  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00426684  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00426685  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00426686  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00426688  8b15b0d36f00           -mov edx, dword ptr [0x6fd3b0]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(7328688) /* 0x6fd3b0 */);
    // 0042668e  83fa01                 +cmp edx, 1
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
    // 00426691  7402                   -je 0x426695
    if (cpu.flags.zf)
    {
        goto L_0x00426695;
    }
    // 00426693  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
L_0x00426695:
    // 00426695  89d7                   -mov edi, edx
    cpu.edi = cpu.edx;
    // 00426697  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
L_0x00426699:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00426699  39f9                   +cmp ecx, edi
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.edi));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0042669b  0f8ff1000000           -jg 0x426792
    if (!cpu.flags.zf && (cpu.flags.sf == cpu.flags.of))
    {
        goto L_0x00426792;
    }
    // 004266a1  8b048db0105e00         -mov eax, dword ptr [ecx*4 + 0x5e10b0]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(6164656) /* 0x5e10b0 */ + cpu.ecx * 4);
    // 004266a8  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 004266aa  8b7004                 -mov esi, dword ptr [eax + 4]
    cpu.esi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 004266ad  8b18                   -mov ebx, dword ptr [eax]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.eax);
    // 004266af  83fb10                 +cmp ebx, 0x10
    {
        x86::reg32 tmp1 = cpu.ebx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(16 /*0x10*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004266b2  7405                   -je 0x4266b9
    if (cpu.flags.zf)
    {
        goto L_0x004266b9;
    }
    // 004266b4  83fb11                 +cmp ebx, 0x11
    {
        x86::reg32 tmp1 = cpu.ebx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(17 /*0x11*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004266b7  7506                   -jne 0x4266bf
    if (!cpu.flags.zf)
    {
        goto L_0x004266bf;
    }
L_0x004266b9:
    // 004266b9  8b901c010000           -mov edx, dword ptr [eax + 0x11c]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(284) /* 0x11c */);
L_0x004266bf:
    // 004266bf  f6860002000001         +test byte ptr [esi + 0x200], 1
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(cpu.esi + x86::reg32(512) /* 0x200 */) & 1 /*0x1*/));
    // 004266c6  0f847e000000           -je 0x42674a
    if (cpu.flags.zf)
    {
        goto L_0x0042674a;
    }
    // 004266cc  83bec402000003         +cmp dword ptr [esi + 0x2c4], 3
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(708) /* 0x2c4 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(3 /*0x3*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004266d3  0f8571000000           -jne 0x42674a
    if (!cpu.flags.zf)
    {
        goto L_0x0042674a;
    }
    // 004266d9  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 004266db  756d                   -jne 0x42674a
    if (!cpu.flags.zf)
    {
        goto L_0x0042674a;
    }
    // 004266dd  b811000000             -mov eax, 0x11
    cpu.eax = 17 /*0x11*/;
    // 004266e2  89ca                   -mov edx, ecx
    cpu.edx = cpu.ecx;
    // 004266e4  e827bfffff             -call 0x422610
    cpu.esp -= 4;
    nfs3hp::carstate::switchCamera(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004266e9  8b148db0105e00         -mov edx, dword ptr [ecx*4 + 0x5e10b0]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(6164656) /* 0x5e10b0 */ + cpu.ecx * 4);
    // 004266f0  c7821c01000001000000   -mov dword ptr [edx + 0x11c], 1
    app->getMemory<x86::reg32>(cpu.edx + x86::reg32(284) /* 0x11c */) = 1 /*0x1*/;
    // 004266fa  8bb218010000           -mov esi, dword ptr [edx + 0x118]
    cpu.esi = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(280) /* 0x118 */);
    // 00426700  83feff                 +cmp esi, -1
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
    // 00426703  7411                   -je 0x426716
    if (cpu.flags.zf)
    {
        goto L_0x00426716;
    }
    // 00426705  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 00426707  e8548dfeff             -call 0x40f460
    cpu.esp -= 4;
    nfs3hp::aiplan::stopAnimation(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042670c  c78218010000ffffffff   -mov dword ptr [edx + 0x118], 0xffffffff
    app->getMemory<x86::reg32>(cpu.edx + x86::reg32(280) /* 0x118 */) = 4294967295 /*0xffffffff*/;
L_0x00426716:
    // 00426716  833dc0d46f0000         +cmp dword ptr [0x6fd4c0], 0
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
    // 0042671d  7411                   -je 0x426730
    if (cpu.flags.zf)
    {
        goto L_0x00426730;
    }
    // 0042671f  b806000000             -mov eax, 6
    cpu.eax = 6 /*0x6*/;
    // 00426724  c7821401000006000000   -mov dword ptr [edx + 0x114], 6
    app->getMemory<x86::reg32>(cpu.edx + x86::reg32(276) /* 0x114 */) = 6 /*0x6*/;
    // 0042672e  eb0f                   -jmp 0x42673f
    goto L_0x0042673f;
L_0x00426730:
    // 00426730  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 00426735  c7821401000001000000   -mov dword ptr [edx + 0x114], 1
    app->getMemory<x86::reg32>(cpu.edx + x86::reg32(276) /* 0x114 */) = 1 /*0x1*/;
L_0x0042673f:
    // 0042673f  e86c8cfeff             -call 0x40f3b0
    cpu.esp -= 4;
    nfs3hp::aiplan::startAnimation(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426744  898218010000           -mov dword ptr [edx + 0x118], eax
    app->getMemory<x86::reg32>(cpu.edx + x86::reg32(280) /* 0x118 */) = cpu.eax;
L_0x0042674a:
    // 0042674a  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 0042674c  e80ffeffff             -call 0x426560
    cpu.esp -= 4;
    sub_426560(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426751  89ca                   -mov edx, ecx
    cpu.edx = cpu.ecx;
    // 00426753  8d048d00000000         -lea eax, [ecx*4]
    cpu.eax = x86::reg32(cpu.ecx * 4);
    // 0042675a  8b98b8105e00           -mov ebx, dword ptr [eax + 0x5e10b8]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164664) /* 0x5e10b8 */);
    // 00426760  85db                   +test ebx, ebx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & cpu.ebx));
    // 00426762  740a                   -je 0x42676e
    if (cpu.flags.zf)
    {
        goto L_0x0042676e;
    }
    // 00426764  7404                   -je 0x42676a
    if (cpu.flags.zf)
    {
        goto L_0x0042676a;
    }
    // 00426766  8b03                   -mov eax, dword ptr [ebx]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx);
    // 00426768  eb1d                   -jmp 0x426787
    goto L_0x00426787;
L_0x0042676a:
    // 0042676a  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
    // 0042676c  eb19                   -jmp 0x426787
    goto L_0x00426787;
L_0x0042676e:
    // 0042676e  8b98b0105e00           -mov ebx, dword ptr [eax + 0x5e10b0]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164656) /* 0x5e10b0 */);
    // 00426774  85db                   +test ebx, ebx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & cpu.ebx));
    // 00426776  740d                   -je 0x426785
    if (cpu.flags.zf)
    {
        goto L_0x00426785;
    }
    // 00426778  8b03                   -mov eax, dword ptr [ebx]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx);
    // 0042677a  e8d1fcffff             -call 0x426450
    cpu.esp -= 4;
    sub_426450(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042677f  41                     +inc ecx
    {
        x86::reg32& tmp = cpu.ecx;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 00426780  e914ffffff             -jmp 0x426699
    goto L_0x00426699;
L_0x00426785:
    // 00426785  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
L_0x00426787:
    // 00426787  e8c4fcffff             -call 0x426450
    cpu.esp -= 4;
    sub_426450(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042678c  41                     +inc ecx
    {
        x86::reg32& tmp = cpu.ecx;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 0042678d  e907ffffff             -jmp 0x426699
    goto L_0x00426699;
L_0x00426792:
    // 00426792  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426793  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426794  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426795  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426796  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426797  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426798  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x00 0x00 0x00 0x00 0x00 0x00 0x00 */
void Application::sub_4267a0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (carSaveFrame(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 004267a0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004267a1  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004267a2  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004267a4  81ec2c010000           -sub esp, 0x12c
    (cpu.esp) -= x86::reg32(x86::sreg32(300 /*0x12c*/));
    // 004267aa  03153c305500           -add edx, dword ptr [0x55303c]
    (cpu.edx) += x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(5582908) /* 0x55303c */)));
    // 004267b0  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004267b1  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004267b2  68646f5300             -push 0x536f64
    app->getMemory<x86::reg32>(cpu.esp-4) = 5468004 /*0x536f64*/;
    cpu.esp -= 4;
    // 004267b7  8d85d4feffff           -lea eax, [ebp - 0x12c]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-300) /* -0x12c */);
    // 004267bd  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004267be  e8cd8e0b00             -call 0x4df690
    cpu.esp -= 4;
    nfs3hp::watcom::sprintf(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004267c3  8b1d3c305500           -mov ebx, dword ptr [0x55303c]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(5582908) /* 0x55303c */);
    // 004267c9  43                     -inc ebx
    (cpu.ebx)++;
    // 004267ca  83c410                 -add esp, 0x10
    (cpu.esp) += x86::reg32(x86::sreg32(16 /*0x10*/));
    // 004267cd  891d3c305500           -mov dword ptr [0x55303c], ebx
    app->getMemory<x86::reg32>(x86::reg32(5582908) /* 0x55303c */) = cpu.ebx;
    // 004267d3  e848450c00             -call 0x4ead20
    cpu.esp -= 4;
    sub_4ead20(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004267d8  8d85d4feffff           -lea eax, [ebp - 0x12c]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-300) /* -0x12c */);
    // 004267de  e87d490c00             -call 0x4eb160
    cpu.esp -= 4;
    sub_4eb160(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004267e3  e8a8450c00             -call 0x4ead90
    cpu.esp -= 4;
    sub_4ead90(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004267e8  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004267ea  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004267eb  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004267ec  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x40 0x00 */
void Application::sub_4267f0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (trackSaveFrame(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 004267f0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004267f1  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004267f2  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004267f4  81ec2c010000           -sub esp, 0x12c
    (cpu.esp) -= x86::reg32(x86::sreg32(300 /*0x12c*/));
    // 004267fa  03153c305500           -add edx, dword ptr [0x55303c]
    (cpu.edx) += x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(5582908) /* 0x55303c */)));
    // 00426800  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00426801  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00426802  68786f5300             -push 0x536f78
    app->getMemory<x86::reg32>(cpu.esp-4) = 5468024 /*0x536f78*/;
    cpu.esp -= 4;
    // 00426807  8d85d4feffff           -lea eax, [ebp - 0x12c]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-300) /* -0x12c */);
    // 0042680d  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 0042680e  e87d8e0b00             -call 0x4df690
    cpu.esp -= 4;
    nfs3hp::watcom::sprintf(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426813  8b1d3c305500           -mov ebx, dword ptr [0x55303c]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(5582908) /* 0x55303c */);
    // 00426819  43                     -inc ebx
    (cpu.ebx)++;
    // 0042681a  83c410                 -add esp, 0x10
    (cpu.esp) += x86::reg32(x86::sreg32(16 /*0x10*/));
    // 0042681d  891d3c305500           -mov dword ptr [0x55303c], ebx
    app->getMemory<x86::reg32>(x86::reg32(5582908) /* 0x55303c */) = cpu.ebx;
    // 00426823  e8f8440c00             -call 0x4ead20
    cpu.esp -= 4;
    sub_4ead20(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426828  8d85d4feffff           -lea eax, [ebp - 0x12c]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-300) /* -0x12c */);
    // 0042682e  e82d490c00             -call 0x4eb160
    cpu.esp -= 4;
    sub_4eb160(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426833  e858450c00             -call 0x4ead90
    cpu.esp -= 4;
    sub_4ead90(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426838  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 0042683a  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042683b  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042683c  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 */
void Application::sub_426870(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (carRecord(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
  goto start;
dynamic_jump:
  switch(cpu.ip)
  {
start:
    // 00426870  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00426871  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00426872  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00426873  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00426874  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00426875  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00426876  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00426878  81ec34010000           -sub esp, 0x134
    (cpu.esp) -= x86::reg32(x86::sreg32(308 /*0x134*/));
    // 0042687e  f6052feb550040         +test byte ptr [0x55eb2f], 0x40
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(x86::reg32(5630767) /* 0x55eb2f */) & 64 /*0x40*/));
    // 00426885  0f8469020000           -je 0x426af4
    if (cpu.flags.zf)
    {
        goto L_0x00426af4;
    }
    // 0042688b  a138305500             -mov eax, dword ptr [0x553038]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5582904) /* 0x553038 */);
    // 00426890  83f808                 +cmp eax, 8
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
    // 00426893  0f875b020000           -ja 0x426af4
    if (!cpu.flags.cf && !cpu.flags.zf)
    {
        goto L_0x00426af4;
    }
    // 00426899  ff248540684200         -jmp dword ptr [eax*4 + 0x426840]
    cpu.ip = app->getMemory<x86::reg32>(4352064 + cpu.eax * 4); goto dynamic_jump;
  case 0x004268a0:
    // 004268a0  803d5048560000         +cmp byte ptr [0x564850], 0
    {
        x86::reg8 tmp1 = app->getMemory<x86::reg8>(x86::reg32(5654608) /* 0x564850 */);
        x86::reg8 tmp2 = x86::reg8(x86::sreg8(0 /*0x0*/));
        x86::reg8 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 7);
        cpu.flags.of ^= 1 & (result >> 7);
        cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
        cpu.set_szp(result);
    }
    // 004268a7  0f8447020000           -je 0x426af4
    if (cpu.flags.zf)
    {
        goto L_0x00426af4;
    }
    // 004268ad  803d3148560000         +cmp byte ptr [0x564831], 0
    {
        x86::reg8 tmp1 = app->getMemory<x86::reg8>(x86::reg32(5654577) /* 0x564831 */);
        x86::reg8 tmp2 = x86::reg8(x86::sreg8(0 /*0x0*/));
        x86::reg8 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 7);
        cpu.flags.of ^= 1 & (result >> 7);
        cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
        cpu.set_szp(result);
    }
    // 004268b4  0f843a020000           -je 0x426af4
    if (cpu.flags.zf)
    {
        goto L_0x00426af4;
    }
    // 004268ba  ba01000000             -mov edx, 1
    cpu.edx = 1 /*0x1*/;
    // 004268bf  a1bcd26f00             -mov eax, dword ptr [0x6fd2bc]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(7328444) /* 0x6fd2bc */);
    // 004268c4  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 004268c6  891538305500           -mov dword ptr [0x553038], edx
    app->getMemory<x86::reg32>(x86::reg32(5582904) /* 0x553038 */) = cpu.edx;
    // 004268cc  890d2c305500           -mov dword ptr [0x55302c], ecx
    app->getMemory<x86::reg32>(x86::reg32(5582892) /* 0x55302c */) = cpu.ecx;
    // 004268d2  891530305500           -mov dword ptr [0x553030], edx
    app->getMemory<x86::reg32>(x86::reg32(5582896) /* 0x553030 */) = cpu.edx;
    // 004268d8  890dd0105e00           -mov dword ptr [0x5e10d0], ecx
    app->getMemory<x86::reg32>(x86::reg32(6164688) /* 0x5e10d0 */) = cpu.ecx;
    // 004268de  890d3c305500           -mov dword ptr [0x55303c], ecx
    app->getMemory<x86::reg32>(x86::reg32(5582908) /* 0x55303c */) = cpu.ecx;
    // 004268e4  890d34305500           -mov dword ptr [0x553034], ecx
    app->getMemory<x86::reg32>(x86::reg32(5582900) /* 0x553034 */) = cpu.ecx;
    // 004268ea  e8312c0100             -call 0x439520
    cpu.esp -= 4;
    nfs3hp::load::carId(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004268ef  e86c2d0100             -call 0x439660
    cpu.esp -= 4;
    nfs3hp::load::numericId(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004268f4  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004268f5  688c6f5300             -push 0x536f8c
    app->getMemory<x86::reg32>(cpu.esp-4) = 5468044 /*0x536f8c*/;
    cpu.esp -= 4;
    // 004268fa  8d85ccfeffff           -lea eax, [ebp - 0x134]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-308) /* -0x134 */);
    // 00426900  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00426901  e88a8d0b00             -call 0x4df690
    cpu.esp -= 4;
    nfs3hp::watcom::sprintf(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426906  83c40c                 -add esp, 0xc
    (cpu.esp) += x86::reg32(x86::sreg32(12 /*0xc*/));
    // 00426909  8d85ccfeffff           -lea eax, [ebp - 0x134]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-308) /* -0x134 */);
    // 0042690f  e8bc480c00             -call 0x4eb1d0
    cpu.esp -= 4;
    nfs3hp::watcom::mkdir(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426914  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00426916  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426917  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426918  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426919  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042691a  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042691b  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042691c  c3                     -ret 
    cpu.esp += 4;
    return;
  case 0x0042691d:
    // 0042691d  c7053830550002000000   -mov dword ptr [0x553038], 2
    app->getMemory<x86::reg32>(x86::reg32(5582904) /* 0x553038 */) = 2 /*0x2*/;
    // 00426927  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00426929  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042692a  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042692b  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042692c  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042692d  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042692e  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042692f  c3                     -ret 
    cpu.esp += 4;
    return;
  case 0x00426930:
    // 00426930  b901000000             -mov ecx, 1
    cpu.ecx = 1 /*0x1*/;
    // 00426935  ba64000000             -mov edx, 0x64
    cpu.edx = 100 /*0x64*/;
    // 0042693a  a1bcd26f00             -mov eax, dword ptr [0x6fd2bc]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(7328444) /* 0x6fd2bc */);
    // 0042693f  890d38305500           -mov dword ptr [0x553038], ecx
    app->getMemory<x86::reg32>(x86::reg32(5582904) /* 0x553038 */) = cpu.ecx;
    // 00426945  e8d62b0100             -call 0x439520
    cpu.esp -= 4;
    nfs3hp::load::carId(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042694a  e8112d0100             -call 0x439660
    cpu.esp -= 4;
    nfs3hp::load::numericId(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042694f  e84cfeffff             -call 0x4267a0
    cpu.esp -= 4;
    sub_4267a0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426954  d9052c305500           -fld dword ptr [0x55302c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(x86::reg32(5582892) /* 0x55302c */));
    // 0042695a  8b1dd0105e00           -mov ebx, dword ptr [0x5e10d0]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(6164688) /* 0x5e10d0 */);
    // 00426960  d9c0                   -fld st(0)
    x86::Float fpu2 = x86::Float(fpu1);
    // 00426962  01cb                   -add ebx, ecx
    (cpu.ebx) += x86::reg32(x86::sreg32(cpu.ecx));
    // 00426964  dc05946f5300           -fadd qword ptr [0x536f94]
    x86::Float fpu3 = cpu.fpu.add(fpu2, x86::Float(app->getMemory<double>(x86::reg32(5468052) /* 0x536f94 */)));
    // 0042696a  891dd0105e00           -mov dword ptr [0x5e10d0], ebx
    app->getMemory<x86::reg32>(x86::reg32(6164688) /* 0x5e10d0 */) = cpu.ebx;
    // 00426970  ddd9                   -fstp st(1)
    x86::Float fpu4 = x86::Float(fpu3);
    // 00426972  d91d2c305500           -fstp dword ptr [0x55302c]
    app->getMemory<float>(x86::reg32(5582892) /* 0x55302c */) = float(fpu4);
    // 00426978  83fb1f                 +cmp ebx, 0x1f
    {
        x86::reg32 tmp1 = cpu.ebx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(31 /*0x1f*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    }
    // 0042697b  0f8e73010000           -jle 0x426af4
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00426af4;
    }
    // 00426981  c7053830550003000000   -mov dword ptr [0x553038], 3
    app->getMemory<x86::reg32>(x86::reg32(5582904) /* 0x553038 */) = 3 /*0x3*/;
    // 0042698b  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 0042698d  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042698e  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042698f  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426990  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426991  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426992  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426993  c3                     -ret 
    cpu.esp += 4;
    return;
  case 0x00426994:
    // 00426994  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00426996  be04000000             -mov esi, 4
    cpu.esi = 4 /*0x4*/;
    // 0042699b  a330305500             -mov dword ptr [0x553030], eax
    app->getMemory<x86::reg32>(x86::reg32(5582896) /* 0x553030 */) = cpu.eax;
    // 004269a0  a3d0105e00             -mov dword ptr [0x5e10d0], eax
    app->getMemory<x86::reg32>(x86::reg32(6164688) /* 0x5e10d0 */) = cpu.eax;
    // 004269a5  a33c305500             -mov dword ptr [0x55303c], eax
    app->getMemory<x86::reg32>(x86::reg32(5582908) /* 0x55303c */) = cpu.eax;
    // 004269aa  893538305500           -mov dword ptr [0x553038], esi
    app->getMemory<x86::reg32>(x86::reg32(5582904) /* 0x553038 */) = cpu.esi;
    // 004269b0  a32c305500             -mov dword ptr [0x55302c], eax
    app->getMemory<x86::reg32>(x86::reg32(5582892) /* 0x55302c */) = cpu.eax;
    // 004269b5  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004269b7  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004269b8  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004269b9  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004269ba  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004269bb  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004269bc  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004269bd  c3                     -ret 
    cpu.esp += 4;
    return;
  case 0x004269be:
    // 004269be  c7053830550005000000   -mov dword ptr [0x553038], 5
    app->getMemory<x86::reg32>(x86::reg32(5582904) /* 0x553038 */) = 5 /*0x5*/;
    // 004269c8  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004269ca  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004269cb  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004269cc  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004269cd  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004269ce  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004269cf  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004269d0  c3                     -ret 
    cpu.esp += 4;
    return;
  case 0x004269d1:
    // 004269d1  c7053830550004000000   -mov dword ptr [0x553038], 4
    app->getMemory<x86::reg32>(x86::reg32(5582904) /* 0x553038 */) = 4 /*0x4*/;
    // 004269db  a1bcd26f00             -mov eax, dword ptr [0x6fd2bc]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(7328444) /* 0x6fd2bc */);
    // 004269e0  bac8000000             -mov edx, 0xc8
    cpu.edx = 200 /*0xc8*/;
    // 004269e5  e8362b0100             -call 0x439520
    cpu.esp -= 4;
    nfs3hp::load::carId(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004269ea  e8712c0100             -call 0x439660
    cpu.esp -= 4;
    nfs3hp::load::numericId(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004269ef  e8acfdffff             -call 0x4267a0
    cpu.esp -= 4;
    sub_4267a0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004269f4  d9052c305500           -fld dword ptr [0x55302c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu5 = x86::Float(app->getMemory<float>(x86::reg32(5582892) /* 0x55302c */));
    // 004269fa  8b15d0105e00           -mov edx, dword ptr [0x5e10d0]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(6164688) /* 0x5e10d0 */);
    // 00426a00  d9c0                   -fld st(0)
    x86::Float fpu6 = x86::Float(fpu5);
    // 00426a02  42                     -inc edx
    (cpu.edx)++;
    // 00426a03  dc05946f5300           -fadd qword ptr [0x536f94]
    x86::Float fpu7 = cpu.fpu.add(fpu6, x86::Float(app->getMemory<double>(x86::reg32(5468052) /* 0x536f94 */)));
    // 00426a09  8915d0105e00           -mov dword ptr [0x5e10d0], edx
    app->getMemory<x86::reg32>(x86::reg32(6164688) /* 0x5e10d0 */) = cpu.edx;
    // 00426a0f  ddd9                   -fstp st(1)
    x86::Float fpu8 = x86::Float(fpu7);
    // 00426a11  d91d2c305500           -fstp dword ptr [0x55302c]
    app->getMemory<float>(x86::reg32(5582892) /* 0x55302c */) = float(fpu8);
    // 00426a17  83fa1f                 +cmp edx, 0x1f
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(31 /*0x1f*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    }
    // 00426a1a  0f8ed4000000           -jle 0x426af4
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00426af4;
    }
    // 00426a20  be01000000             -mov esi, 1
    cpu.esi = 1 /*0x1*/;
    // 00426a25  bb06000000             -mov ebx, 6
    cpu.ebx = 6 /*0x6*/;
    // 00426a2a  31ff                   -xor edi, edi
    cpu.edi ^= x86::reg32(x86::sreg32(cpu.edi));
    // 00426a2c  893530305500           -mov dword ptr [0x553030], esi
    app->getMemory<x86::reg32>(x86::reg32(5582896) /* 0x553030 */) = cpu.esi;
    // 00426a32  893d2c305500           -mov dword ptr [0x55302c], edi
    app->getMemory<x86::reg32>(x86::reg32(5582892) /* 0x55302c */) = cpu.edi;
    // 00426a38  891d38305500           -mov dword ptr [0x553038], ebx
    app->getMemory<x86::reg32>(x86::reg32(5582904) /* 0x553038 */) = cpu.ebx;
    // 00426a3e  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00426a40  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426a41  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426a42  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426a43  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426a44  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426a45  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426a46  c3                     -ret 
    cpu.esp += 4;
    return;
  case 0x00426a47:
    // 00426a47  b901000000             -mov ecx, 1
    cpu.ecx = 1 /*0x1*/;
    // 00426a4c  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00426a4e  bf07000000             -mov edi, 7
    cpu.edi = 7 /*0x7*/;
    // 00426a53  a330305500             -mov dword ptr [0x553030], eax
    app->getMemory<x86::reg32>(x86::reg32(5582896) /* 0x553030 */) = cpu.eax;
    // 00426a58  890d34305500           -mov dword ptr [0x553034], ecx
    app->getMemory<x86::reg32>(x86::reg32(5582900) /* 0x553034 */) = cpu.ecx;
    // 00426a5e  a3d0105e00             -mov dword ptr [0x5e10d0], eax
    app->getMemory<x86::reg32>(x86::reg32(6164688) /* 0x5e10d0 */) = cpu.eax;
    // 00426a63  a33c305500             -mov dword ptr [0x55303c], eax
    app->getMemory<x86::reg32>(x86::reg32(5582908) /* 0x55303c */) = cpu.eax;
    // 00426a68  893d38305500           -mov dword ptr [0x553038], edi
    app->getMemory<x86::reg32>(x86::reg32(5582904) /* 0x553038 */) = cpu.edi;
    // 00426a6e  a32c305500             -mov dword ptr [0x55302c], eax
    app->getMemory<x86::reg32>(x86::reg32(5582892) /* 0x55302c */) = cpu.eax;
    // 00426a73  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00426a75  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426a76  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426a77  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426a78  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426a79  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426a7a  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426a7b  c3                     -ret 
    cpu.esp += 4;
    return;
  case 0x00426a7c:
    // 00426a7c  c7053830550008000000   -mov dword ptr [0x553038], 8
    app->getMemory<x86::reg32>(x86::reg32(5582904) /* 0x553038 */) = 8 /*0x8*/;
    // 00426a86  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00426a88  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426a89  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426a8a  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426a8b  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426a8c  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426a8d  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426a8e  c3                     -ret 
    cpu.esp += 4;
    return;
  case 0x00426a8f:
    // 00426a8f  ba07000000             -mov edx, 7
    cpu.edx = 7 /*0x7*/;
    // 00426a94  a1bcd26f00             -mov eax, dword ptr [0x6fd2bc]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(7328444) /* 0x6fd2bc */);
    // 00426a99  891538305500           -mov dword ptr [0x553038], edx
    app->getMemory<x86::reg32>(x86::reg32(5582904) /* 0x553038 */) = cpu.edx;
    // 00426a9f  e87c2a0100             -call 0x439520
    cpu.esp -= 4;
    nfs3hp::load::carId(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426aa4  ba2c010000             -mov edx, 0x12c
    cpu.edx = 300 /*0x12c*/;
    // 00426aa9  e8b22b0100             -call 0x439660
    cpu.esp -= 4;
    nfs3hp::load::numericId(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426aae  e8edfcffff             -call 0x4267a0
    cpu.esp -= 4;
    sub_4267a0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426ab3  d9052c305500           -fld dword ptr [0x55302c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu9 = x86::Float(app->getMemory<float>(x86::reg32(5582892) /* 0x55302c */));
    // 00426ab9  8b0dd0105e00           -mov ecx, dword ptr [0x5e10d0]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(6164688) /* 0x5e10d0 */);
    // 00426abf  d9c0                   -fld st(0)
    x86::Float fpu10 = x86::Float(fpu9);
    // 00426ac1  41                     -inc ecx
    (cpu.ecx)++;
    // 00426ac2  dc05946f5300           -fadd qword ptr [0x536f94]
    x86::Float fpu11 = cpu.fpu.add(fpu10, x86::Float(app->getMemory<double>(x86::reg32(5468052) /* 0x536f94 */)));
    // 00426ac8  890dd0105e00           -mov dword ptr [0x5e10d0], ecx
    app->getMemory<x86::reg32>(x86::reg32(6164688) /* 0x5e10d0 */) = cpu.ecx;
    // 00426ace  ddd9                   -fstp st(1)
    x86::Float fpu12 = x86::Float(fpu11);
    // 00426ad0  d91d2c305500           -fstp dword ptr [0x55302c]
    app->getMemory<float>(x86::reg32(5582892) /* 0x55302c */) = float(fpu12);
    // 00426ad6  83f91f                 +cmp ecx, 0x1f
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(31 /*0x1f*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    }
    // 00426ad9  7e19                   -jle 0x426af4
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00426af4;
    }
    // 00426adb  bf01000000             -mov edi, 1
    cpu.edi = 1 /*0x1*/;
    // 00426ae0  31f6                   -xor esi, esi
    cpu.esi ^= x86::reg32(x86::sreg32(cpu.esi));
    // 00426ae2  893d30305500           -mov dword ptr [0x553030], edi
    app->getMemory<x86::reg32>(x86::reg32(5582896) /* 0x553030 */) = cpu.edi;
    // 00426ae8  89352c305500           -mov dword ptr [0x55302c], esi
    app->getMemory<x86::reg32>(x86::reg32(5582892) /* 0x55302c */) = cpu.esi;
    // 00426aee  893538305500           -mov dword ptr [0x553038], esi
    app->getMemory<x86::reg32>(x86::reg32(5582904) /* 0x553038 */) = cpu.esi;
L_0x00426af4:
    // 00426af4  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00426af6  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426af7  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426af8  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426af9  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426afa  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426afb  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426afc  c3                     -ret 
    cpu.esp += 4;
    return;
  default:
    NFS2_ASSERT(false);
  }
}

/* align: skip 0x8d 0x40 0x00 */
void Application::sub_426b00(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (trackRecord(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 00426b00  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00426b01  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00426b02  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00426b03  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00426b04  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00426b06  81ec34010000           -sub esp, 0x134
    (cpu.esp) -= x86::reg32(x86::sreg32(308 /*0x134*/));
    // 00426b0c  f6052feb550040         +test byte ptr [0x55eb2f], 0x40
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(x86::reg32(5630767) /* 0x55eb2f */) & 64 /*0x40*/));
    // 00426b13  0f84f3000000           -je 0x426c0c
    if (cpu.flags.zf)
    {
        goto L_0x00426c0c;
    }
    // 00426b19  a138305500             -mov eax, dword ptr [0x553038]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5582904) /* 0x553038 */);
    // 00426b1e  83f801                 +cmp eax, 1
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
    // 00426b21  7214                   -jb 0x426b37
    if (cpu.flags.cf)
    {
        goto L_0x00426b37;
    }
    // 00426b23  0f8688000000           -jbe 0x426bb1
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x00426bb1;
    }
    // 00426b29  83f802                 +cmp eax, 2
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
    // 00426b2c  0f8490000000           -je 0x426bc2
    if (cpu.flags.zf)
    {
        goto L_0x00426bc2;
    }
    // 00426b32  e9d5000000             -jmp 0x426c0c
    goto L_0x00426c0c;
L_0x00426b37:
    // 00426b37  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00426b39  7407                   -je 0x426b42
    if (cpu.flags.zf)
    {
        goto L_0x00426b42;
    }
    // 00426b3b  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00426b3d  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426b3e  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426b3f  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426b40  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426b41  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x00426b42:
    // 00426b42  803d5048560000         +cmp byte ptr [0x564850], 0
    {
        x86::reg8 tmp1 = app->getMemory<x86::reg8>(x86::reg32(5654608) /* 0x564850 */);
        x86::reg8 tmp2 = x86::reg8(x86::sreg8(0 /*0x0*/));
        x86::reg8 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 7);
        cpu.flags.of ^= 1 & (result >> 7);
        cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
        cpu.set_szp(result);
    }
    // 00426b49  0f84bd000000           -je 0x426c0c
    if (cpu.flags.zf)
    {
        goto L_0x00426c0c;
    }
    // 00426b4f  803d3148560000         +cmp byte ptr [0x564831], 0
    {
        x86::reg8 tmp1 = app->getMemory<x86::reg8>(x86::reg32(5654577) /* 0x564831 */);
        x86::reg8 tmp2 = x86::reg8(x86::sreg8(0 /*0x0*/));
        x86::reg8 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 7);
        cpu.flags.of ^= 1 & (result >> 7);
        cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
        cpu.set_szp(result);
    }
    // 00426b56  7507                   -jne 0x426b5f
    if (!cpu.flags.zf)
    {
        goto L_0x00426b5f;
    }
    // 00426b58  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00426b5a  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426b5b  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426b5c  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426b5d  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426b5e  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x00426b5f:
    // 00426b5f  ba01000000             -mov edx, 1
    cpu.edx = 1 /*0x1*/;
    // 00426b64  891538305500           -mov dword ptr [0x553038], edx
    app->getMemory<x86::reg32>(x86::reg32(5582904) /* 0x553038 */) = cpu.edx;
    // 00426b6a  891530305500           -mov dword ptr [0x553030], edx
    app->getMemory<x86::reg32>(x86::reg32(5582896) /* 0x553030 */) = cpu.edx;
    // 00426b70  8b15acd46f00           -mov edx, dword ptr [0x6fd4ac]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(7328940) /* 0x6fd4ac */);
    // 00426b76  a32c305500             -mov dword ptr [0x55302c], eax
    app->getMemory<x86::reg32>(x86::reg32(5582892) /* 0x55302c */) = cpu.eax;
    // 00426b7b  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00426b7c  a3d0105e00             -mov dword ptr [0x5e10d0], eax
    app->getMemory<x86::reg32>(x86::reg32(6164688) /* 0x5e10d0 */) = cpu.eax;
    // 00426b81  a33c305500             -mov dword ptr [0x55303c], eax
    app->getMemory<x86::reg32>(x86::reg32(5582908) /* 0x55303c */) = cpu.eax;
    // 00426b86  689c6f5300             -push 0x536f9c
    app->getMemory<x86::reg32>(cpu.esp-4) = 5468060 /*0x536f9c*/;
    cpu.esp -= 4;
    // 00426b8b  a334305500             -mov dword ptr [0x553034], eax
    app->getMemory<x86::reg32>(x86::reg32(5582900) /* 0x553034 */) = cpu.eax;
    // 00426b90  8d85ccfeffff           -lea eax, [ebp - 0x134]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-308) /* -0x134 */);
    // 00426b96  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00426b97  e8f48a0b00             -call 0x4df690
    cpu.esp -= 4;
    nfs3hp::watcom::sprintf(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426b9c  83c40c                 -add esp, 0xc
    (cpu.esp) += x86::reg32(x86::sreg32(12 /*0xc*/));
    // 00426b9f  8d85ccfeffff           -lea eax, [ebp - 0x134]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-308) /* -0x134 */);
    // 00426ba5  e826460c00             -call 0x4eb1d0
    cpu.esp -= 4;
    nfs3hp::watcom::mkdir(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426baa  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00426bac  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426bad  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426bae  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426baf  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426bb0  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x00426bb1:
    // 00426bb1  c7053830550002000000   -mov dword ptr [0x553038], 2
    app->getMemory<x86::reg32>(x86::reg32(5582904) /* 0x553038 */) = 2 /*0x2*/;
    // 00426bbb  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00426bbd  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426bbe  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426bbf  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426bc0  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426bc1  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x00426bc2:
    // 00426bc2  bb01000000             -mov ebx, 1
    cpu.ebx = 1 /*0x1*/;
    // 00426bc7  ba64000000             -mov edx, 0x64
    cpu.edx = 100 /*0x64*/;
    // 00426bcc  a1acd46f00             -mov eax, dword ptr [0x6fd4ac]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(7328940) /* 0x6fd4ac */);
    // 00426bd1  891d38305500           -mov dword ptr [0x553038], ebx
    app->getMemory<x86::reg32>(x86::reg32(5582904) /* 0x553038 */) = cpu.ebx;
    // 00426bd7  e814fcffff             -call 0x4267f0
    cpu.esp -= 4;
    sub_4267f0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426bdc  d9052c305500           -fld dword ptr [0x55302c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(x86::reg32(5582892) /* 0x55302c */));
    // 00426be2  8b35d0105e00           -mov esi, dword ptr [0x5e10d0]
    cpu.esi = app->getMemory<x86::reg32>(x86::reg32(6164688) /* 0x5e10d0 */);
    // 00426be8  d9c0                   -fld st(0)
    x86::Float fpu2 = x86::Float(fpu1);
    // 00426bea  01de                   -add esi, ebx
    (cpu.esi) += x86::reg32(x86::sreg32(cpu.ebx));
    // 00426bec  dc05ac6f5300           -fadd qword ptr [0x536fac]
    x86::Float fpu3 = cpu.fpu.add(fpu2, x86::Float(app->getMemory<double>(x86::reg32(5468076) /* 0x536fac */)));
    // 00426bf2  8935d0105e00           -mov dword ptr [0x5e10d0], esi
    app->getMemory<x86::reg32>(x86::reg32(6164688) /* 0x5e10d0 */) = cpu.esi;
    // 00426bf8  ddd9                   -fstp st(1)
    x86::Float fpu4 = x86::Float(fpu3);
    // 00426bfa  d91d2c305500           -fstp dword ptr [0x55302c]
    app->getMemory<float>(x86::reg32(5582892) /* 0x55302c */) = float(fpu4);
    // 00426c00  83fe1f                 +cmp esi, 0x1f
    {
        x86::reg32 tmp1 = cpu.esi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(31 /*0x1f*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    }
    // 00426c03  7e07                   -jle 0x426c0c
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00426c0c;
    }
    // 00426c05  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00426c07  a338305500             -mov dword ptr [0x553038], eax
    app->getMemory<x86::reg32>(x86::reg32(5582904) /* 0x553038 */) = cpu.eax;
L_0x00426c0c:
    // 00426c0c  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00426c0e  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426c0f  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426c10  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426c11  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426c12  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 */
void Application::sub_426c20(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (car1EditClicked(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 00426c20  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00426c21  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00426c22  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00426c24  ba01000000             -mov edx, 1
    cpu.edx = 1 /*0x1*/;
    // 00426c29  b805000000             -mov eax, 5
    cpu.eax = 5 /*0x5*/;
    // 00426c2e  891548305500           -mov dword ptr [0x553048], edx
    app->getMemory<x86::reg32>(x86::reg32(5582920) /* 0x553048 */) = cpu.edx;
    // 00426c34  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426c35  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426c36  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 */
void Application::sub_426c40(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (car2EditClicked(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 00426c40  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00426c41  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00426c42  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00426c44  ba02000000             -mov edx, 2
    cpu.edx = 2 /*0x2*/;
    // 00426c49  b805000000             -mov eax, 5
    cpu.eax = 5 /*0x5*/;
    // 00426c4e  891548305500           -mov dword ptr [0x553048], edx
    app->getMemory<x86::reg32>(x86::reg32(5582920) /* 0x553048 */) = cpu.edx;
    // 00426c54  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426c55  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426c56  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 */
void Application::sub_426c60(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (car1ColourClicked(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 00426c60  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00426c61  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00426c62  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00426c63  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00426c64  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00426c66  a1bcd26f00             -mov eax, dword ptr [0x6fd2bc]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(7328444) /* 0x6fd2bc */);
    // 00426c6b  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00426c6d  e81e2b0100             -call 0x439790
    cpu.esp -= 4;
    sub_439790(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426c72  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 00426c74  a1bcd26f00             -mov eax, dword ptr [0x6fd2bc]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(7328444) /* 0x6fd2bc */);
    // 00426c79  e8e22a0100             -call 0x439760
    cpu.esp -= 4;
    sub_439760(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426c7e  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00426c80  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 00426c82  7c4c                   -jl 0x426cd0
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x00426cd0;
    }
    // 00426c84  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00426c86  7e48                   -jle 0x426cd0
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00426cd0;
    }
    // 00426c88  42                     -inc edx
    (cpu.edx)++;
    // 00426c89  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 00426c8b  c1fa1f                 -sar edx, 0x1f
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (31 /*0x1f*/ % 32));
    // 00426c8e  f7f9                   -idiv ecx
    {
        x86::sreg64 tmp = x86::sreg64(cpu.edx_eax);
        x86::sreg32 d = x86::sreg32(cpu.ecx);
        cpu.edx_eax = x86::reg64(tmp / d);
        cpu.edx = x86::reg32(tmp % d);
    }
    // 00426c90  a1bcd26f00             -mov eax, dword ptr [0x6fd2bc]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(7328444) /* 0x6fd2bc */);
    // 00426c95  89d3                   -mov ebx, edx
    cpu.ebx = cpu.edx;
    // 00426c97  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00426c99  e8322b0100             -call 0x4397d0
    cpu.esp -= 4;
    sub_4397d0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426c9e  bab46f5300             -mov edx, 0x536fb4
    cpu.edx = 5468084 /*0x536fb4*/;
    // 00426ca3  e808420200             -call 0x44aeb0
    cpu.esp -= 4;
    sub_44aeb0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426ca8  e893bd0100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426cad  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00426caf  7407                   -je 0x426cb8
    if (cpu.flags.zf)
    {
        goto L_0x00426cb8;
    }
    // 00426cb1  c680b300000001         -mov byte ptr [eax + 0xb3], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(179) /* 0xb3 */) = 1 /*0x1*/;
L_0x00426cb8:
    // 00426cb8  bac86f5300             -mov edx, 0x536fc8
    cpu.edx = 5468104 /*0x536fc8*/;
    // 00426cbd  e8ee410200             -call 0x44aeb0
    cpu.esp -= 4;
    sub_44aeb0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426cc2  e879bd0100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426cc7  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00426cc9  7405                   -je 0x426cd0
    if (cpu.flags.zf)
    {
        goto L_0x00426cd0;
    }
    // 00426ccb  e850fd0200             -call 0x456a20
    cpu.esp -= 4;
    sub_456a20(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00426cd0:
    // 00426cd0  b802000000             -mov eax, 2
    cpu.eax = 2 /*0x2*/;
    // 00426cd5  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426cd6  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426cd7  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426cd8  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426cd9  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 */
void Application::sub_426ce0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (car2ColourClicked(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 00426ce0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00426ce1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00426ce2  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00426ce3  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00426ce4  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00426ce6  ba01000000             -mov edx, 1
    cpu.edx = 1 /*0x1*/;
    // 00426ceb  a128d36f00             -mov eax, dword ptr [0x6fd328]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(7328552) /* 0x6fd328 */);
    // 00426cf0  e89b2a0100             -call 0x439790
    cpu.esp -= 4;
    sub_439790(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426cf5  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 00426cf7  a128d36f00             -mov eax, dword ptr [0x6fd328]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(7328552) /* 0x6fd328 */);
    // 00426cfc  e85f2a0100             -call 0x439760
    cpu.esp -= 4;
    sub_439760(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426d01  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00426d03  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 00426d05  7c4f                   -jl 0x426d56
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x00426d56;
    }
    // 00426d07  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00426d09  7e4b                   -jle 0x426d56
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00426d56;
    }
    // 00426d0b  42                     -inc edx
    (cpu.edx)++;
    // 00426d0c  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 00426d0e  c1fa1f                 -sar edx, 0x1f
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (31 /*0x1f*/ % 32));
    // 00426d11  f7f9                   -idiv ecx
    {
        x86::sreg64 tmp = x86::sreg64(cpu.edx_eax);
        x86::sreg32 d = x86::sreg32(cpu.ecx);
        cpu.edx_eax = x86::reg64(tmp / d);
        cpu.edx = x86::reg32(tmp % d);
    }
    // 00426d13  a128d36f00             -mov eax, dword ptr [0x6fd328]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(7328552) /* 0x6fd328 */);
    // 00426d18  89d3                   -mov ebx, edx
    cpu.ebx = cpu.edx;
    // 00426d1a  ba01000000             -mov edx, 1
    cpu.edx = 1 /*0x1*/;
    // 00426d1f  e8ac2a0100             -call 0x4397d0
    cpu.esp -= 4;
    sub_4397d0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426d24  badc6f5300             -mov edx, 0x536fdc
    cpu.edx = 5468124 /*0x536fdc*/;
    // 00426d29  e882410200             -call 0x44aeb0
    cpu.esp -= 4;
    sub_44aeb0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426d2e  e80dbd0100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426d33  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00426d35  7407                   -je 0x426d3e
    if (cpu.flags.zf)
    {
        goto L_0x00426d3e;
    }
    // 00426d37  c680b300000001         -mov byte ptr [eax + 0xb3], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(179) /* 0xb3 */) = 1 /*0x1*/;
L_0x00426d3e:
    // 00426d3e  baf06f5300             -mov edx, 0x536ff0
    cpu.edx = 5468144 /*0x536ff0*/;
    // 00426d43  e868410200             -call 0x44aeb0
    cpu.esp -= 4;
    sub_44aeb0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426d48  e8f3bc0100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426d4d  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00426d4f  7405                   -je 0x426d56
    if (cpu.flags.zf)
    {
        goto L_0x00426d56;
    }
    // 00426d51  e8cafc0200             -call 0x456a20
    cpu.esp -= 4;
    sub_456a20(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00426d56:
    // 00426d56  b802000000             -mov eax, 2
    cpu.eax = 2 /*0x2*/;
    // 00426d5b  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426d5c  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426d5d  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426d5e  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426d5f  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip  */
void Application::sub_426d60(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (car1OnEnter(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 00426d60  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00426d61  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00426d62  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00426d63  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00426d64  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00426d66  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00426d68  e84397feff             -call 0x4104b0
    cpu.esp -= 4;
    sub_4104b0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426d6d  ba04705300             -mov edx, 0x537004
    cpu.edx = 5468164 /*0x537004*/;
    // 00426d72  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00426d74  e8c7bc0100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426d79  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 00426d7b  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00426d7d  7426                   -je 0x426da5
    if (cpu.flags.zf)
    {
        goto L_0x00426da5;
    }
    // 00426d7f  833db0d36f0001         +cmp dword ptr [0x6fd3b0], 1
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
    // 00426d86  7f10                   -jg 0x426d98
    if (!cpu.flags.zf && (cpu.flags.sf == cpu.flags.of))
    {
        goto L_0x00426d98;
    }
    // 00426d88  8b35b8d36f00           -mov esi, dword ptr [0x6fd3b8]
    cpu.esi = app->getMemory<x86::reg32>(x86::reg32(7328696) /* 0x6fd3b8 */);
    // 00426d8e  83fe01                 +cmp esi, 1
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
    // 00426d91  7405                   -je 0x426d98
    if (cpu.flags.zf)
    {
        goto L_0x00426d98;
    }
    // 00426d93  83fe02                 +cmp esi, 2
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
    // 00426d96  7506                   -jne 0x426d9e
    if (!cpu.flags.zf)
    {
        goto L_0x00426d9e;
    }
L_0x00426d98:
    // 00426d98  804a0401               +or byte ptr [edx + 4], 1
    cpu.clear_co();
    cpu.set_szp((app->getMemory<x86::reg8>(cpu.edx + x86::reg32(4) /* 0x4 */) |= x86::reg8(x86::sreg8(1 /*0x1*/))));
    // 00426d9c  eb07                   -jmp 0x426da5
    goto L_0x00426da5;
L_0x00426d9e:
    // 00426d9e  c74064206c4200         -mov dword ptr [eax + 0x64], 0x426c20
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(100) /* 0x64 */) = 4353056 /*0x426c20*/;
L_0x00426da5:
    // 00426da5  ba10705300             -mov edx, 0x537010
    cpu.edx = 5468176 /*0x537010*/;
    // 00426daa  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00426dac  e88fbc0100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426db1  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 00426db3  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00426db5  741d                   -je 0x426dd4
    if (cpu.flags.zf)
    {
        goto L_0x00426dd4;
    }
    // 00426db7  833db0d36f0001         +cmp dword ptr [0x6fd3b0], 1
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
    // 00426dbe  7507                   -jne 0x426dc7
    if (!cpu.flags.zf)
    {
        goto L_0x00426dc7;
    }
    // 00426dc0  b8aa010000             -mov eax, 0x1aa
    cpu.eax = 426 /*0x1aa*/;
    // 00426dc5  eb05                   -jmp 0x426dcc
    goto L_0x00426dcc;
L_0x00426dc7:
    // 00426dc7  b802010000             -mov eax, 0x102
    cpu.eax = 258 /*0x102*/;
L_0x00426dcc:
    // 00426dcc  e87faa0a00             -call 0x4d1850
    cpu.esp -= 4;
    nfs3hp::frontend::languageText(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426dd1  89423c                 -mov dword ptr [edx + 0x3c], eax
    app->getMemory<x86::reg32>(cpu.edx + x86::reg32(60) /* 0x3c */) = cpu.eax;
L_0x00426dd4:
    // 00426dd4  ba20705300             -mov edx, 0x537020
    cpu.edx = 5468192 /*0x537020*/;
    // 00426dd9  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00426ddb  e860bc0100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426de0  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00426de2  7407                   -je 0x426deb
    if (cpu.flags.zf)
    {
        goto L_0x00426deb;
    }
    // 00426de4  c74064606c4200         -mov dword ptr [eax + 0x64], 0x426c60
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(100) /* 0x64 */) = 4353120 /*0x426c60*/;
L_0x00426deb:
    // 00426deb  ba38705300             -mov edx, 0x537038
    cpu.edx = 5468216 /*0x537038*/;
    // 00426df0  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00426df2  e849bc0100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426df7  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00426df9  7407                   -je 0x426e02
    if (cpu.flags.zf)
    {
        goto L_0x00426e02;
    }
    // 00426dfb  c74064602e4500         -mov dword ptr [eax + 0x64], 0x452e60
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(5) /* 0x5 */) |= x86::reg8(16 /*0x10*/); /* port: Download Car hidden, as hidethis is (tools/apply_hide_download.py) */
L_0x00426e02:
    // 00426e02  ba48705300             -mov edx, 0x537048
    cpu.edx = 5468232 /*0x537048*/;
    // 00426e07  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00426e09  e832bc0100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426e0e  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00426e10  7404                   -je 0x426e16
    if (cpu.flags.zf)
    {
        goto L_0x00426e16;
    }
    // 00426e12  80480510               -or byte ptr [eax + 5], 0x10
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(5) /* 0x5 */) |= x86::reg8(x86::sreg8(16 /*0x10*/));
L_0x00426e16:
    // 00426e16  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00426e18  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426e19  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426e1a  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426e1b  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426e1c  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x40 0x00 */
void Application::sub_426e20(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (car1OnFrame(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 00426e20  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00426e21  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00426e22  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00426e23  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00426e24  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00426e26  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00426e28  e843faffff             -call 0x426870
    cpu.esp -= 4;
    sub_426870(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426e2d  ba54705300             -mov edx, 0x537054
    cpu.edx = 5468244 /*0x537054*/;
    // 00426e32  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00426e34  e807bc0100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426e39  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 00426e3b  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00426e3d  7418                   -je 0x426e57
    if (cpu.flags.zf)
    {
        goto L_0x00426e57;
    }
    // 00426e3f  a1bcd26f00             -mov eax, dword ptr [0x6fd2bc]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(7328444) /* 0x6fd2bc */);
    // 00426e44  e877c20200             -call 0x4530c0
    cpu.esp -= 4;
    sub_4530c0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426e49  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00426e4b  7406                   -je 0x426e53
    if (cpu.flags.zf)
    {
        goto L_0x00426e53;
    }
    // 00426e4d  806204fe               +and byte ptr [edx + 4], 0xfe
    cpu.clear_co();
    cpu.set_szp((app->getMemory<x86::reg8>(cpu.edx + x86::reg32(4) /* 0x4 */) &= x86::reg8(x86::sreg8(254 /*0xfe*/))));
    // 00426e51  eb04                   -jmp 0x426e57
    goto L_0x00426e57;
L_0x00426e53:
    // 00426e53  804a0401               -or byte ptr [edx + 4], 1
    app->getMemory<x86::reg8>(cpu.edx + x86::reg32(4) /* 0x4 */) |= x86::reg8(x86::sreg8(1 /*0x1*/));
L_0x00426e57:
    // 00426e57  bac86f5300             -mov edx, 0x536fc8
    cpu.edx = 5468104 /*0x536fc8*/;
    // 00426e5c  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00426e5e  e8ddbb0100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426e63  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 00426e65  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 00426e67  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00426e69  742b                   -je 0x426e96
    if (cpu.flags.zf)
    {
        goto L_0x00426e96;
    }
    // 00426e6b  a1bcd26f00             -mov eax, dword ptr [0x6fd2bc]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(7328444) /* 0x6fd2bc */);
    // 00426e70  e83b280100             -call 0x4396b0
    cpu.esp -= 4;
    nfs3hp::load::carIsPolice(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426e75  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00426e77  750f                   -jne 0x426e88
    if (!cpu.flags.zf)
    {
        goto L_0x00426e88;
    }
    // 00426e79  a1bcd26f00             -mov eax, dword ptr [0x6fd2bc]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(7328444) /* 0x6fd2bc */);
    // 00426e7e  e8dd280100             -call 0x439760
    cpu.esp -= 4;
    sub_439760(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426e83  83f801                 +cmp eax, 1
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
    // 00426e86  7508                   -jne 0x426e90
    if (!cpu.flags.zf)
    {
        goto L_0x00426e90;
    }
L_0x00426e88:
    // 00426e88  66814b040110           +or word ptr [ebx + 4], 0x1001
    cpu.clear_co();
    cpu.set_szp((app->getMemory<x86::reg16>(cpu.ebx + x86::reg32(4) /* 0x4 */) |= x86::reg16(x86::sreg16(4097 /*0x1001*/))));
    // 00426e8e  eb06                   -jmp 0x426e96
    goto L_0x00426e96;
L_0x00426e90:
    // 00426e90  66816204feef           -and word ptr [edx + 4], 0xeffe
    app->getMemory<x86::reg16>(cpu.edx + x86::reg32(4) /* 0x4 */) &= x86::reg16(x86::sreg16(61438 /*0xeffe*/));
L_0x00426e96:
    // 00426e96  ba20705300             -mov edx, 0x537020
    cpu.edx = 5468192 /*0x537020*/;
    // 00426e9b  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00426e9d  e89ebb0100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426ea2  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 00426ea4  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00426ea6  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00426ea8  7427                   -je 0x426ed1
    if (cpu.flags.zf)
    {
        goto L_0x00426ed1;
    }
    // 00426eaa  a1bcd26f00             -mov eax, dword ptr [0x6fd2bc]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(7328444) /* 0x6fd2bc */);
    // 00426eaf  e8fc270100             -call 0x4396b0
    cpu.esp -= 4;
    nfs3hp::load::carIsPolice(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426eb4  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00426eb6  750f                   -jne 0x426ec7
    if (!cpu.flags.zf)
    {
        goto L_0x00426ec7;
    }
    // 00426eb8  a1bcd26f00             -mov eax, dword ptr [0x6fd2bc]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(7328444) /* 0x6fd2bc */);
    // 00426ebd  e89e280100             -call 0x439760
    cpu.esp -= 4;
    sub_439760(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426ec2  83f801                 +cmp eax, 1
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
    // 00426ec5  7506                   -jne 0x426ecd
    if (!cpu.flags.zf)
    {
        goto L_0x00426ecd;
    }
L_0x00426ec7:
    // 00426ec7  80490401               +or byte ptr [ecx + 4], 1
    cpu.clear_co();
    cpu.set_szp((app->getMemory<x86::reg8>(cpu.ecx + x86::reg32(4) /* 0x4 */) |= x86::reg8(x86::sreg8(1 /*0x1*/))));
    // 00426ecb  eb04                   -jmp 0x426ed1
    goto L_0x00426ed1;
L_0x00426ecd:
    // 00426ecd  806204fe               -and byte ptr [edx + 4], 0xfe
    app->getMemory<x86::reg8>(cpu.edx + x86::reg32(4) /* 0x4 */) &= x86::reg8(x86::sreg8(254 /*0xfe*/));
L_0x00426ed1:
    // 00426ed1  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00426ed3  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426ed4  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426ed5  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426ed6  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426ed7  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8b 0xd2 */
void Application::sub_426ee0(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (car1OnExit(app, cpu)) /* port: native (tools/apply_native_frontend.py) */
    {
        return;
    }
    // 00426ee0  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00426ee1  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00426ee3  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00426ee5  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426ee6  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 */
void Application::sub_426ef0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (car2OnEnter(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 00426ef0  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00426ef1  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00426ef2  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00426ef3  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00426ef4  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00426ef6  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00426ef8  e8b395feff             -call 0x4104b0
    cpu.esp -= 4;
    sub_4104b0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426efd  ba60705300             -mov edx, 0x537060
    cpu.edx = 5468256 /*0x537060*/;
    // 00426f02  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00426f04  e837bb0100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426f09  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 00426f0b  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00426f0d  7426                   -je 0x426f35
    if (cpu.flags.zf)
    {
        goto L_0x00426f35;
    }
    // 00426f0f  833db0d36f0001         +cmp dword ptr [0x6fd3b0], 1
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
    // 00426f16  7f10                   -jg 0x426f28
    if (!cpu.flags.zf && (cpu.flags.sf == cpu.flags.of))
    {
        goto L_0x00426f28;
    }
    // 00426f18  8b35b8d36f00           -mov esi, dword ptr [0x6fd3b8]
    cpu.esi = app->getMemory<x86::reg32>(x86::reg32(7328696) /* 0x6fd3b8 */);
    // 00426f1e  83fe01                 +cmp esi, 1
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
    // 00426f21  7405                   -je 0x426f28
    if (cpu.flags.zf)
    {
        goto L_0x00426f28;
    }
    // 00426f23  83fe02                 +cmp esi, 2
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
    // 00426f26  7506                   -jne 0x426f2e
    if (!cpu.flags.zf)
    {
        goto L_0x00426f2e;
    }
L_0x00426f28:
    // 00426f28  804a0401               +or byte ptr [edx + 4], 1
    cpu.clear_co();
    cpu.set_szp((app->getMemory<x86::reg8>(cpu.edx + x86::reg32(4) /* 0x4 */) |= x86::reg8(x86::sreg8(1 /*0x1*/))));
    // 00426f2c  eb07                   -jmp 0x426f35
    goto L_0x00426f35;
L_0x00426f2e:
    // 00426f2e  c74064406c4200         -mov dword ptr [eax + 0x64], 0x426c40
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(100) /* 0x64 */) = 4353088 /*0x426c40*/;
L_0x00426f35:
    // 00426f35  ba20705300             -mov edx, 0x537020
    cpu.edx = 5468192 /*0x537020*/;
    // 00426f3a  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00426f3c  e8ffba0100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426f41  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00426f43  7407                   -je 0x426f4c
    if (cpu.flags.zf)
    {
        goto L_0x00426f4c;
    }
    // 00426f45  c74064e06c4200         -mov dword ptr [eax + 0x64], 0x426ce0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(100) /* 0x64 */) = 4353248 /*0x426ce0*/;
L_0x00426f4c:
    // 00426f4c  ba54705300             -mov edx, 0x537054
    cpu.edx = 5468244 /*0x537054*/;
    // 00426f51  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00426f53  e8e8ba0100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426f58  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00426f5a  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00426f5c  7418                   -je 0x426f76
    if (cpu.flags.zf)
    {
        goto L_0x00426f76;
    }
    // 00426f5e  a128d36f00             -mov eax, dword ptr [0x6fd328]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(7328552) /* 0x6fd328 */);
    // 00426f63  e858c10200             -call 0x4530c0
    cpu.esp -= 4;
    sub_4530c0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426f68  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00426f6a  7406                   -je 0x426f72
    if (cpu.flags.zf)
    {
        goto L_0x00426f72;
    }
    // 00426f6c  806104fe               +and byte ptr [ecx + 4], 0xfe
    cpu.clear_co();
    cpu.set_szp((app->getMemory<x86::reg8>(cpu.ecx + x86::reg32(4) /* 0x4 */) &= x86::reg8(x86::sreg8(254 /*0xfe*/))));
    // 00426f70  eb04                   -jmp 0x426f76
    goto L_0x00426f76;
L_0x00426f72:
    // 00426f72  80490401               -or byte ptr [ecx + 4], 1
    app->getMemory<x86::reg8>(cpu.ecx + x86::reg32(4) /* 0x4 */) |= x86::reg8(x86::sreg8(1 /*0x1*/));
L_0x00426f76:
    // 00426f76  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00426f78  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426f79  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426f7a  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426f7b  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00426f7c  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x40 0x00 */
void Application::sub_426f80(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (car2OnFrame(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 00426f80  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00426f81  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00426f82  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00426f83  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00426f84  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00426f86  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00426f88  e8e3f8ffff             -call 0x426870
    cpu.esp -= 4;
    sub_426870(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426f8d  ba54705300             -mov edx, 0x537054
    cpu.edx = 5468244 /*0x537054*/;
    // 00426f92  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00426f94  e8a7ba0100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426f99  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 00426f9b  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00426f9d  7418                   -je 0x426fb7
    if (cpu.flags.zf)
    {
        goto L_0x00426fb7;
    }
    // 00426f9f  a128d36f00             -mov eax, dword ptr [0x6fd328]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(7328552) /* 0x6fd328 */);
    // 00426fa4  e817c10200             -call 0x4530c0
    cpu.esp -= 4;
    sub_4530c0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426fa9  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00426fab  7406                   -je 0x426fb3
    if (cpu.flags.zf)
    {
        goto L_0x00426fb3;
    }
    // 00426fad  806204fe               +and byte ptr [edx + 4], 0xfe
    cpu.clear_co();
    cpu.set_szp((app->getMemory<x86::reg8>(cpu.edx + x86::reg32(4) /* 0x4 */) &= x86::reg8(x86::sreg8(254 /*0xfe*/))));
    // 00426fb1  eb04                   -jmp 0x426fb7
    goto L_0x00426fb7;
L_0x00426fb3:
    // 00426fb3  804a0401               -or byte ptr [edx + 4], 1
    app->getMemory<x86::reg8>(cpu.edx + x86::reg32(4) /* 0x4 */) |= x86::reg8(x86::sreg8(1 /*0x1*/));
L_0x00426fb7:
    // 00426fb7  baf06f5300             -mov edx, 0x536ff0
    cpu.edx = 5468144 /*0x536ff0*/;
    // 00426fbc  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00426fbe  e87dba0100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426fc3  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 00426fc5  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 00426fc7  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00426fc9  742b                   -je 0x426ff6
    if (cpu.flags.zf)
    {
        goto L_0x00426ff6;
    }
    // 00426fcb  a128d36f00             -mov eax, dword ptr [0x6fd328]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(7328552) /* 0x6fd328 */);
    // 00426fd0  e8db260100             -call 0x4396b0
    cpu.esp -= 4;
    nfs3hp::load::carIsPolice(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426fd5  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00426fd7  750f                   -jne 0x426fe8
    if (!cpu.flags.zf)
    {
        goto L_0x00426fe8;
    }
    // 00426fd9  a128d36f00             -mov eax, dword ptr [0x6fd328]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(7328552) /* 0x6fd328 */);
    // 00426fde  e87d270100             -call 0x439760
    cpu.esp -= 4;
    sub_439760(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00426fe3  83f801                 +cmp eax, 1
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
    // 00426fe6  7508                   -jne 0x426ff0
    if (!cpu.flags.zf)
    {
        goto L_0x00426ff0;
    }
L_0x00426fe8:
    // 00426fe8  66814b040110           +or word ptr [ebx + 4], 0x1001
    cpu.clear_co();
    cpu.set_szp((app->getMemory<x86::reg16>(cpu.ebx + x86::reg32(4) /* 0x4 */) |= x86::reg16(x86::sreg16(4097 /*0x1001*/))));
    // 00426fee  eb06                   -jmp 0x426ff6
    goto L_0x00426ff6;
L_0x00426ff0:
    // 00426ff0  66816204feef           -and word ptr [edx + 4], 0xeffe
    app->getMemory<x86::reg16>(cpu.edx + x86::reg32(4) /* 0x4 */) &= x86::reg16(x86::sreg16(61438 /*0xeffe*/));
L_0x00426ff6:
    // 00426ff6  ba20705300             -mov edx, 0x537020
    cpu.edx = 5468192 /*0x537020*/;
    // 00426ffb  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00426ffd  e83eba0100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427002  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 00427004  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00427006  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00427008  7427                   -je 0x427031
    if (cpu.flags.zf)
    {
        goto L_0x00427031;
    }
    // 0042700a  a128d36f00             -mov eax, dword ptr [0x6fd328]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(7328552) /* 0x6fd328 */);
    // 0042700f  e89c260100             -call 0x4396b0
    cpu.esp -= 4;
    nfs3hp::load::carIsPolice(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427014  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00427016  750f                   -jne 0x427027
    if (!cpu.flags.zf)
    {
        goto L_0x00427027;
    }
    // 00427018  a128d36f00             -mov eax, dword ptr [0x6fd328]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(7328552) /* 0x6fd328 */);
    // 0042701d  e83e270100             -call 0x439760
    cpu.esp -= 4;
    sub_439760(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427022  83f801                 +cmp eax, 1
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
    // 00427025  7506                   -jne 0x42702d
    if (!cpu.flags.zf)
    {
        goto L_0x0042702d;
    }
L_0x00427027:
    // 00427027  80490401               +or byte ptr [ecx + 4], 1
    cpu.clear_co();
    cpu.set_szp((app->getMemory<x86::reg8>(cpu.ecx + x86::reg32(4) /* 0x4 */) |= x86::reg8(x86::sreg8(1 /*0x1*/))));
    // 0042702b  eb04                   -jmp 0x427031
    goto L_0x00427031;
L_0x0042702d:
    // 0042702d  806204fe               -and byte ptr [edx + 4], 0xfe
    app->getMemory<x86::reg8>(cpu.edx + x86::reg32(4) /* 0x4 */) &= x86::reg8(x86::sreg8(254 /*0xfe*/));
L_0x00427031:
    // 00427031  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00427033  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00427034  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00427035  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00427036  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00427037  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8b 0xd2 */
void Application::sub_427040(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (car2OnExit(app, cpu)) /* port: native (tools/apply_native_frontend.py) */
    {
        return;
    }
    // 00427040  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00427041  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00427043  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00427045  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00427046  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 */
void Application::sub_427050(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (opponentFitCar(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 00427050  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00427051  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00427052  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00427053  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00427054  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00427056  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00427058  ba54705300             -mov edx, 0x537054
    cpu.edx = 5468244 /*0x537054*/;
    // 0042705d  e8deb90100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427062  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 00427064  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00427066  7427                   -je 0x42708f
    if (cpu.flags.zf)
    {
        goto L_0x0042708f;
    }
    // 00427068  8b1dd4d46f00           -mov ebx, dword ptr [0x6fd4d4]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(7328980) /* 0x6fd4d4 */);
    // 0042706e  83fb03                 +cmp ebx, 3
    {
        x86::reg32 tmp1 = cpu.ebx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(3 /*0x3*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00427071  7e18                   -jle 0x42708b
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x0042708b;
    }
    // 00427073  8d43fc                 -lea eax, [ebx - 4]
    cpu.eax = x86::reg32(cpu.ebx + x86::reg32(-4) /* -0x4 */);
    // 00427076  e845c00200             -call 0x4530c0
    cpu.esp -= 4;
    sub_4530c0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042707b  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0042707d  7406                   -je 0x427085
    if (cpu.flags.zf)
    {
        goto L_0x00427085;
    }
    // 0042707f  806204fe               +and byte ptr [edx + 4], 0xfe
    cpu.clear_co();
    cpu.set_szp((app->getMemory<x86::reg8>(cpu.edx + x86::reg32(4) /* 0x4 */) &= x86::reg8(x86::sreg8(254 /*0xfe*/))));
    // 00427083  eb0a                   -jmp 0x42708f
    goto L_0x0042708f;
L_0x00427085:
    // 00427085  804a0401               +or byte ptr [edx + 4], 1
    cpu.clear_co();
    cpu.set_szp((app->getMemory<x86::reg8>(cpu.edx + x86::reg32(4) /* 0x4 */) |= x86::reg8(x86::sreg8(1 /*0x1*/))));
    // 00427089  eb04                   -jmp 0x42708f
    goto L_0x0042708f;
L_0x0042708b:
    // 0042708b  80480401               -or byte ptr [eax + 4], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(4) /* 0x4 */) |= x86::reg8(x86::sreg8(1 /*0x1*/));
L_0x0042708f:
    // 0042708f  ba6c705300             -mov edx, 0x53706c
    cpu.edx = 5468268 /*0x53706c*/;
    // 00427094  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00427096  e8a5b90100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042709b  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0042709d  7416                   -je 0x4270b5
    if (cpu.flags.zf)
    {
        goto L_0x004270b5;
    }
    // 0042709f  833dd4d46f0003         +cmp dword ptr [0x6fd4d4], 3
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(7328980) /* 0x6fd4d4 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(3 /*0x3*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004270a6  7e09                   -jle 0x4270b1
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004270b1;
    }
    // 004270a8  806004fe               -and byte ptr [eax + 4], 0xfe
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(4) /* 0x4 */) &= x86::reg8(x86::sreg8(254 /*0xfe*/));
    // 004270ac  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004270ad  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004270ae  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004270af  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004270b0  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004270b1:
    // 004270b1  80480401               -or byte ptr [eax + 4], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(4) /* 0x4 */) |= x86::reg8(x86::sreg8(1 /*0x1*/));
L_0x004270b5:
    // 004270b5  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004270b6  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004270b7  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004270b8  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004270b9  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 */
void Application::sub_4270c0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (opponentFitArt(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 004270c0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004270c1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004270c2  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004270c3  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004270c4  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004270c5  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004270c7  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 004270c9  ba74705300             -mov edx, 0x537074
    cpu.edx = 5468276 /*0x537074*/;
    // 004270ce  e86db90100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004270d3  ba7c705300             -mov edx, 0x53707c
    cpu.edx = 5468284 /*0x53707c*/;
    // 004270d8  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 004270da  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 004270dc  e85fb90100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004270e1  8b1dd4d46f00           -mov ebx, dword ptr [0x6fd4d4]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(7328980) /* 0x6fd4d4 */);
    // 004270e7  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004270e9  83fb03                 +cmp ebx, 3
    {
        x86::reg32 tmp1 = cpu.ebx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(3 /*0x3*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004270ec  7f04                   -jg 0x4270f2
    if (!cpu.flags.zf && (cpu.flags.sf == cpu.flags.of))
    {
        goto L_0x004270f2;
    }
    // 004270ee  85db                   +test ebx, ebx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & cpu.ebx));
    // 004270f0  7534                   -jne 0x427126
    if (!cpu.flags.zf)
    {
        goto L_0x00427126;
    }
L_0x004270f2:
    // 004270f2  66c741080000           -mov word ptr [ecx + 8], 0
    app->getMemory<x86::reg16>(cpu.ecx + x86::reg32(8) /* 0x8 */) = 0 /*0x0*/;
    // 004270f8  66c7410a0c00           -mov word ptr [ecx + 0xa], 0xc
    app->getMemory<x86::reg16>(cpu.ecx + x86::reg32(10) /* 0xa */) = 12 /*0xc*/;
    // 004270fe  c7414084705300         -mov dword ptr [ecx + 0x40], 0x537084
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(64) /* 0x40 */) = 5468292 /*0x537084*/;
    // 00427105  66c741060000           -mov word ptr [ecx + 6], 0
    app->getMemory<x86::reg16>(cpu.ecx + x86::reg32(6) /* 0x6 */) = 0 /*0x0*/;
    // 0042710b  66c742068900           -mov word ptr [edx + 6], 0x89
    app->getMemory<x86::reg16>(cpu.edx + x86::reg32(6) /* 0x6 */) = 137 /*0x89*/;
    // 00427111  66c742084a00           -mov word ptr [edx + 8], 0x4a
    app->getMemory<x86::reg16>(cpu.edx + x86::reg32(8) /* 0x8 */) = 74 /*0x4a*/;
    // 00427117  66c7420a0900           -mov word ptr [edx + 0xa], 9
    app->getMemory<x86::reg16>(cpu.edx + x86::reg32(10) /* 0xa */) = 9 /*0x9*/;
    // 0042711d  c7424084705300         -mov dword ptr [edx + 0x40], 0x537084
    app->getMemory<x86::reg32>(cpu.edx + x86::reg32(64) /* 0x40 */) = 5468292 /*0x537084*/;
    // 00427124  eb56                   -jmp 0x42717c
    goto L_0x0042717c;
L_0x00427126:
    // 00427126  a0d4d46f00             -mov al, byte ptr [0x6fd4d4]
    cpu.al = app->getMemory<x86::reg8>(x86::reg32(7328980) /* 0x6fd4d4 */);
    // 0042712b  bb90705300             -mov ebx, 0x537090
    cpu.ebx = 5468304 /*0x537090*/;
    // 00427130  0430                   -add al, 0x30
    (cpu.al) += x86::reg8(x86::sreg8(48 /*0x30*/));
    // 00427132  8b3dd4d46f00           -mov edi, dword ptr [0x6fd4d4]
    cpu.edi = app->getMemory<x86::reg32>(x86::reg32(7328980) /* 0x6fd4d4 */);
    // 00427138  a293705300             -mov byte ptr [0x537093], al
    app->getMemory<x86::reg8>(x86::reg32(5468307) /* 0x537093 */) = cpu.al;
    // 0042713d  83ff03                 +cmp edi, 3
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
    // 00427140  7510                   -jne 0x427152
    if (!cpu.flags.zf)
    {
        goto L_0x00427152;
    }
    // 00427142  e8992b0100             -call 0x439ce0
    cpu.esp -= 4;
    sub_439ce0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427147  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00427149  7407                   -je 0x427152
    if (cpu.flags.zf)
    {
        goto L_0x00427152;
    }
    // 0042714b  c6059370530034         -mov byte ptr [0x537093], 0x34
    app->getMemory<x86::reg8>(x86::reg32(5468307) /* 0x537093 */) = 52 /*0x34*/;
L_0x00427152:
    // 00427152  66c741080000           -mov word ptr [ecx + 8], 0
    app->getMemory<x86::reg16>(cpu.ecx + x86::reg32(8) /* 0x8 */) = 0 /*0x0*/;
    // 00427158  66c7410a0900           -mov word ptr [ecx + 0xa], 9
    app->getMemory<x86::reg16>(cpu.ecx + x86::reg32(10) /* 0xa */) = 9 /*0x9*/;
    // 0042715e  66c741068900           -mov word ptr [ecx + 6], 0x89
    app->getMemory<x86::reg16>(cpu.ecx + x86::reg32(6) /* 0x6 */) = 137 /*0x89*/;
    // 00427164  895940                 -mov dword ptr [ecx + 0x40], ebx
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(64) /* 0x40 */) = cpu.ebx;
    // 00427167  66c742060000           -mov word ptr [edx + 6], 0
    app->getMemory<x86::reg16>(cpu.edx + x86::reg32(6) /* 0x6 */) = 0 /*0x0*/;
    // 0042716d  66c742080000           -mov word ptr [edx + 8], 0
    app->getMemory<x86::reg16>(cpu.edx + x86::reg32(8) /* 0x8 */) = 0 /*0x0*/;
    // 00427173  66c7420a0c00           -mov word ptr [edx + 0xa], 0xc
    app->getMemory<x86::reg16>(cpu.edx + x86::reg32(10) /* 0xa */) = 12 /*0xc*/;
    // 00427179  895a40                 -mov dword ptr [edx + 0x40], ebx
    app->getMemory<x86::reg32>(cpu.edx + x86::reg32(64) /* 0x40 */) = cpu.ebx;
L_0x0042717c:
    // 0042717c  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042717d  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042717e  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042717f  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00427180  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00427181  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x8b 0xc0 */
void Application::sub_427190(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (opponentOnFrame(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 00427190  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00427191  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00427192  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00427193  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00427194  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00427195  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00427197  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00427199  e81293feff             -call 0x4104b0
    cpu.esp -= 4;
    sub_4104b0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042719e  ba9c705300             -mov edx, 0x53709c
    cpu.edx = 5468316 /*0x53709c*/;
    // 004271a3  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004271a5  e896b80100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004271aa  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
    // 004271ac  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004271ae  7428                   -je 0x4271d8
    if (cpu.flags.zf)
    {
        goto L_0x004271d8;
    }
    // 004271b0  8b15b8d36f00           -mov edx, dword ptr [0x6fd3b8]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(7328696) /* 0x6fd3b8 */);
    // 004271b6  83fa03                 +cmp edx, 3
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
    // 004271b9  741d                   -je 0x4271d8
    if (cpu.flags.zf)
    {
        goto L_0x004271d8;
    }
    // 004271bb  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 004271bd  7406                   -je 0x4271c5
    if (cpu.flags.zf)
    {
        goto L_0x004271c5;
    }
    // 004271bf  80480401               +or byte ptr [eax + 4], 1
    cpu.clear_co();
    cpu.set_szp((app->getMemory<x86::reg8>(cpu.eax + x86::reg32(4) /* 0x4 */) |= x86::reg8(x86::sreg8(1 /*0x1*/))));
    // 004271c3  eb13                   -jmp 0x4271d8
    goto L_0x004271d8;
L_0x004271c5:
    // 004271c5  833dd0d46f0002         +cmp dword ptr [0x6fd4d0], 2
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(7328976) /* 0x6fd4d0 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(2 /*0x2*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004271cc  7506                   -jne 0x4271d4
    if (!cpu.flags.zf)
    {
        goto L_0x004271d4;
    }
    // 004271ce  80480401               +or byte ptr [eax + 4], 1
    cpu.clear_co();
    cpu.set_szp((app->getMemory<x86::reg8>(cpu.eax + x86::reg32(4) /* 0x4 */) |= x86::reg8(x86::sreg8(1 /*0x1*/))));
    // 004271d2  eb04                   -jmp 0x4271d8
    goto L_0x004271d8;
L_0x004271d4:
    // 004271d4  806004fe               -and byte ptr [eax + 4], 0xfe
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(4) /* 0x4 */) &= x86::reg8(x86::sreg8(254 /*0xfe*/));
L_0x004271d8:
    // 004271d8  baac705300             -mov edx, 0x5370ac
    cpu.edx = 5468332 /*0x5370ac*/;
    // 004271dd  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004271df  e85cb80100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004271e4  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004271e6  742e                   -je 0x427216
    if (cpu.flags.zf)
    {
        goto L_0x00427216;
    }
    // 004271e8  8b15b8d36f00           -mov edx, dword ptr [0x6fd3b8]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(7328696) /* 0x6fd3b8 */);
    // 004271ee  83fa03                 +cmp edx, 3
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
    // 004271f1  7423                   -je 0x427216
    if (cpu.flags.zf)
    {
        goto L_0x00427216;
    }
    // 004271f3  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 004271f5  7408                   -je 0x4271ff
    if (cpu.flags.zf)
    {
        goto L_0x004271ff;
    }
    // 004271f7  668148040110           +or word ptr [eax + 4], 0x1001
    cpu.clear_co();
    cpu.set_szp((app->getMemory<x86::reg16>(cpu.eax + x86::reg32(4) /* 0x4 */) |= x86::reg16(x86::sreg16(4097 /*0x1001*/))));
    // 004271fd  eb17                   -jmp 0x427216
    goto L_0x00427216;
L_0x004271ff:
    // 004271ff  833dd0d46f0002         +cmp dword ptr [0x6fd4d0], 2
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(7328976) /* 0x6fd4d0 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(2 /*0x2*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00427206  7508                   -jne 0x427210
    if (!cpu.flags.zf)
    {
        goto L_0x00427210;
    }
    // 00427208  668148040110           +or word ptr [eax + 4], 0x1001
    cpu.clear_co();
    cpu.set_szp((app->getMemory<x86::reg16>(cpu.eax + x86::reg32(4) /* 0x4 */) |= x86::reg16(x86::sreg16(4097 /*0x1001*/))));
    // 0042720e  eb06                   -jmp 0x427216
    goto L_0x00427216;
L_0x00427210:
    // 00427210  66816004feef           -and word ptr [eax + 4], 0xeffe
    app->getMemory<x86::reg16>(cpu.eax + x86::reg32(4) /* 0x4 */) &= x86::reg16(x86::sreg16(61438 /*0xeffe*/));
L_0x00427216:
    // 00427216  babc705300             -mov edx, 0x5370bc
    cpu.edx = 5468348 /*0x5370bc*/;
    // 0042721b  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 0042721d  e81eb80100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427222  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00427224  7413                   -je 0x427239
    if (cpu.flags.zf)
    {
        goto L_0x00427239;
    }
    // 00427226  833db8d36f0003         +cmp dword ptr [0x6fd3b8], 3
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(7328696) /* 0x6fd3b8 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(3 /*0x3*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0042722d  7506                   -jne 0x427235
    if (!cpu.flags.zf)
    {
        goto L_0x00427235;
    }
    // 0042722f  80480401               +or byte ptr [eax + 4], 1
    cpu.clear_co();
    cpu.set_szp((app->getMemory<x86::reg8>(cpu.eax + x86::reg32(4) /* 0x4 */) |= x86::reg8(x86::sreg8(1 /*0x1*/))));
    // 00427233  eb04                   -jmp 0x427239
    goto L_0x00427239;
L_0x00427235:
    // 00427235  806004fe               -and byte ptr [eax + 4], 0xfe
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(4) /* 0x4 */) &= x86::reg8(x86::sreg8(254 /*0xfe*/));
L_0x00427239:
    // 00427239  bac4705300             -mov edx, 0x5370c4
    cpu.edx = 5468356 /*0x5370c4*/;
    // 0042723e  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00427240  e8fbb70100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427245  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00427247  7417                   -je 0x427260
    if (cpu.flags.zf)
    {
        goto L_0x00427260;
    }
    // 00427249  833db8d36f0003         +cmp dword ptr [0x6fd3b8], 3
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(7328696) /* 0x6fd3b8 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(3 /*0x3*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00427250  7508                   -jne 0x42725a
    if (!cpu.flags.zf)
    {
        goto L_0x0042725a;
    }
    // 00427252  668148040110           +or word ptr [eax + 4], 0x1001
    cpu.clear_co();
    cpu.set_szp((app->getMemory<x86::reg16>(cpu.eax + x86::reg32(4) /* 0x4 */) |= x86::reg16(x86::sreg16(4097 /*0x1001*/))));
    // 00427258  eb06                   -jmp 0x427260
    goto L_0x00427260;
L_0x0042725a:
    // 0042725a  66816004feef           -and word ptr [eax + 4], 0xeffe
    app->getMemory<x86::reg16>(cpu.eax + x86::reg32(4) /* 0x4 */) &= x86::reg16(x86::sreg16(61438 /*0xeffe*/));
L_0x00427260:
    // 00427260  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00427262  e8e9fdffff             -call 0x427050
    cpu.esp -= 4;
    sub_427050(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427267  8b3dd4d46f00           -mov edi, dword ptr [0x6fd4d4]
    cpu.edi = app->getMemory<x86::reg32>(x86::reg32(7328980) /* 0x6fd4d4 */);
    // 0042726d  83ff03                 +cmp edi, 3
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
    // 00427270  7f04                   -jg 0x427276
    if (!cpu.flags.zf && (cpu.flags.sf == cpu.flags.of))
    {
        goto L_0x00427276;
    }
    // 00427272  85ff                   +test edi, edi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edi & cpu.edi));
    // 00427274  7504                   -jne 0x42727a
    if (!cpu.flags.zf)
    {
        goto L_0x0042727a;
    }
L_0x00427276:
    // 00427276  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
    // 00427278  eb02                   -jmp 0x42727c
    goto L_0x0042727c;
L_0x0042727a:
    // 0042727a  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
L_0x0042727c:
    // 0042727c  3b0540305500           +cmp eax, dword ptr [0x553040]
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(5582912) /* 0x553040 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00427282  7405                   -je 0x427289
    if (cpu.flags.zf)
    {
        goto L_0x00427289;
    }
    // 00427284  bb09000000             -mov ebx, 9
    cpu.ebx = 9 /*0x9*/;
L_0x00427289:
    // 00427289  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 0042728b  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042728c  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042728d  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042728e  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042728f  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00427290  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x8d 0x40 0x00 */
void Application::sub_4272a0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (opponentOnEnter(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 004272a0  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004272a1  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004272a2  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004272a3  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004272a4  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004272a6  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004272a8  e813feffff             -call 0x4270c0
    cpu.esp -= 4;
    sub_4270c0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004272ad  8b0dd4d46f00           -mov ecx, dword ptr [0x6fd4d4]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(7328980) /* 0x6fd4d4 */);
    // 004272b3  83f903                 +cmp ecx, 3
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
    // 004272b6  7f04                   -jg 0x4272bc
    if (!cpu.flags.zf && (cpu.flags.sf == cpu.flags.of))
    {
        goto L_0x004272bc;
    }
    // 004272b8  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    // 004272ba  750a                   -jne 0x4272c6
    if (!cpu.flags.zf)
    {
        goto L_0x004272c6;
    }
L_0x004272bc:
    // 004272bc  31f6                   +xor esi, esi
    cpu.clear_co();
    cpu.set_szp((cpu.esi ^= x86::reg32(x86::sreg32(cpu.esi))));
    // 004272be  893540305500           -mov dword ptr [0x553040], esi
    app->getMemory<x86::reg32>(x86::reg32(5582912) /* 0x553040 */) = cpu.esi;
    // 004272c4  eb06                   -jmp 0x4272cc
    goto L_0x004272cc;
L_0x004272c6:
    // 004272c6  890d40305500           -mov dword ptr [0x553040], ecx
    app->getMemory<x86::reg32>(x86::reg32(5582912) /* 0x553040 */) = cpu.ecx;
L_0x004272cc:
    // 004272cc  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004272ce  e87dfdffff             -call 0x427050
    cpu.esp -= 4;
    sub_427050(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004272d3  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 004272d5  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004272d6  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004272d7  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004272d8  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004272d9  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 */
void Application::sub_4272e0(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (opponentOnExit(app, cpu)) /* port: native (tools/apply_native_frontend.py) */
    {
        return;
    }
    // 004272e0  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004272e1  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004272e3  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 004272e5  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004272e6  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 */
void Application::sub_4272f0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (tuningLoad(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 004272f0  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004272f1  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004272f2  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004272f3  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004272f4  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004272f5  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004272f7  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 004272f9  e852270100             -call 0x439a50
    cpu.esp -= 4;
    nfs3hp::load::carRecord(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004272fe  31f6                   -xor esi, esi
    cpu.esi ^= x86::reg32(x86::sreg32(cpu.esi));
    // 00427300  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00427302  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00427304  7409                   -je 0x42730f
    if (cpu.flags.zf)
    {
        goto L_0x0042730f;
    }
    // 00427306  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00427308  e813220100             -call 0x439520
    cpu.esp -= 4;
    nfs3hp::load::carId(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042730d  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
L_0x0042730f:
    // 0042730f  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 00427311  7426                   -je 0x427339
    if (cpu.flags.zf)
    {
        goto L_0x00427339;
    }
    // 00427313  8b0d4c305500           -mov ecx, dword ptr [0x55304c]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(5582924) /* 0x55304c */);
    // 00427319  81f9bcd26f00           +cmp ecx, 0x6fd2bc
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(7328444 /*0x6fd2bc*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0042731f  7504                   -jne 0x427325
    if (!cpu.flags.zf)
    {
        goto L_0x00427325;
    }
    // 00427321  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
    // 00427323  eb0d                   -jmp 0x427332
    goto L_0x00427332;
L_0x00427325:
    // 00427325  81f928d36f00           +cmp ecx, 0x6fd328
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(7328552 /*0x6fd328*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0042732b  750c                   -jne 0x427339
    if (!cpu.flags.zf)
    {
        goto L_0x00427339;
    }
    // 0042732d  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
L_0x00427332:
    // 00427332  e819520b00             -call 0x4dc550
    cpu.esp -= 4;
    sub_4dc550(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427337  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
L_0x00427339:
    // 00427339  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 0042733b  7407                   -je 0x427344
    if (cpu.flags.zf)
    {
        goto L_0x00427344;
    }
    // 0042733d  b91c000000             -mov ecx, 0x1c
    cpu.ecx = 28 /*0x1c*/;
    // 00427342  eb0a                   -jmp 0x42734e
    goto L_0x0042734e;
L_0x00427344:
    // 00427344  b91c000000             -mov ecx, 0x1c
    cpu.ecx = 28 /*0x1c*/;
    // 00427349  be24d05500             -mov esi, 0x55d024
    cpu.esi = 5623844 /*0x55d024*/;
L_0x0042734e:
    // 0042734e  bfe0105e00             -mov edi, 0x5e10e0
    cpu.edi = 6164704 /*0x5e10e0*/;
    // 00427353  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00427354  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00427356  c1e902                 -shr ecx, 2
    cpu.ecx >>= 2 /*0x2*/ % 32;
    // 00427359  f2a5                   -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 0042735b  8ac8                   -mov cl, al
    cpu.cl = cpu.al;
    // 0042735d  80e103                 +and cl, 3
    cpu.clear_co();
    cpu.set_szp((cpu.cl &= x86::reg8(x86::sreg8(3 /*0x3*/))));
    // 00427360  f2a4                   -repne movsb byte ptr es:[edi], byte ptr [esi]
    while (cpu.ecx)
    {
        app->getMemory<x86::reg8>(cpu.ees + cpu.edi) = app->getMemory<x86::reg8>(cpu.esi);
        if (cpu.flags.df)
        {
            cpu.edi -= 1;
            cpu.esi -= 1;
        }
        else
        {
            cpu.edi += 1;
            cpu.esi += 1;
        }
        --cpu.ecx;
        if (cpu.flags.zf)
            break;
    }
    // 00427362  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00427363  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00427364  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00427365  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00427366  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00427367  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00427368  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x90 */
void Application::sub_427370(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (tuningSave(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 00427370  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00427371  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00427372  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00427373  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00427374  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00427375  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00427377  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00427379  e8d2260100             -call 0x439a50
    cpu.esp -= 4;
    nfs3hp::load::carRecord(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042737e  31ff                   -xor edi, edi
    cpu.edi ^= x86::reg32(x86::sreg32(cpu.edi));
    // 00427380  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00427382  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00427384  7409                   -je 0x42738f
    if (cpu.flags.zf)
    {
        goto L_0x0042738f;
    }
    // 00427386  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00427388  e893210100             -call 0x439520
    cpu.esp -= 4;
    nfs3hp::load::carId(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042738d  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
L_0x0042738f:
    // 0042738f  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 00427391  7426                   -je 0x4273b9
    if (cpu.flags.zf)
    {
        goto L_0x004273b9;
    }
    // 00427393  8b0d4c305500           -mov ecx, dword ptr [0x55304c]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(5582924) /* 0x55304c */);
    // 00427399  81f9bcd26f00           +cmp ecx, 0x6fd2bc
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(7328444 /*0x6fd2bc*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0042739f  7504                   -jne 0x4273a5
    if (!cpu.flags.zf)
    {
        goto L_0x004273a5;
    }
    // 004273a1  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
    // 004273a3  eb0d                   -jmp 0x4273b2
    goto L_0x004273b2;
L_0x004273a5:
    // 004273a5  81f928d36f00           +cmp ecx, 0x6fd328
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(7328552 /*0x6fd328*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004273ab  750c                   -jne 0x4273b9
    if (!cpu.flags.zf)
    {
        goto L_0x004273b9;
    }
    // 004273ad  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
L_0x004273b2:
    // 004273b2  e899510b00             -call 0x4dc550
    cpu.esp -= 4;
    sub_4dc550(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004273b7  89c7                   -mov edi, eax
    cpu.edi = cpu.eax;
L_0x004273b9:
    // 004273b9  85ff                   +test edi, edi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edi & cpu.edi));
    // 004273bb  741a                   -je 0x4273d7
    if (cpu.flags.zf)
    {
        goto L_0x004273d7;
    }
    // 004273bd  b91c000000             -mov ecx, 0x1c
    cpu.ecx = 28 /*0x1c*/;
    // 004273c2  bee0105e00             -mov esi, 0x5e10e0
    cpu.esi = 6164704 /*0x5e10e0*/;
    // 004273c7  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004273c8  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004273ca  c1e902                 -shr ecx, 2
    cpu.ecx >>= 2 /*0x2*/ % 32;
    // 004273cd  f2a5                   -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004273cf  8ac8                   -mov cl, al
    cpu.cl = cpu.al;
    // 004273d1  80e103                 +and cl, 3
    cpu.clear_co();
    cpu.set_szp((cpu.cl &= x86::reg8(x86::sreg8(3 /*0x3*/))));
    // 004273d4  f2a4                   -repne movsb byte ptr es:[edi], byte ptr [esi]
    while (cpu.ecx)
    {
        app->getMemory<x86::reg8>(cpu.ees + cpu.edi) = app->getMemory<x86::reg8>(cpu.esi);
        if (cpu.flags.df)
        {
            cpu.edi -= 1;
            cpu.esi -= 1;
        }
        else
        {
            cpu.edi += 1;
            cpu.esi += 1;
        }
        --cpu.ecx;
        if (cpu.flags.zf)
            break;
    }
    // 004273d6  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
L_0x004273d7:
    // 004273d7  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004273d8  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004273d9  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004273da  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004273db  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004273dc  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x40 0x00 */
void Application::sub_4273e0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (tuningEngineMoved(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 004273e0  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004273e1  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004273e2  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004273e4  83ec1c                 -sub esp, 0x1c
    (cpu.esp) -= x86::reg32(x86::sreg32(28 /*0x1c*/));
    // 004273e7  8b155cd05500           -mov edx, dword ptr [0x55d05c]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5623900) /* 0x55d05c */);
    // 004273ed  8955fc                 -mov dword ptr [ebp - 4], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.edx;
    // 004273f0  8b1540d05500           -mov edx, dword ptr [0x55d040]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5623872) /* 0x55d040 */);
    // 004273f6  8955f4                 -mov dword ptr [ebp - 0xc], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.edx;
    // 004273f9  d945f4                 -fld dword ptr [ebp - 0xc]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */));
    // 004273fc  d865fc                 -fsub dword ptr [ebp - 4]
    x86::Float fpu2 = cpu.fpu.sub(fpu1, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 004273ff  31d2                   +xor edx, edx
    cpu.clear_co();
    cpu.set_szp((cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx))));
    // 00427401  d95de4                 +fstp dword ptr [ebp - 0x1c]
    app->getMemory<float>(cpu.ebp + x86::reg32(-28) /* -0x1c */) = float(fpu2);
    }
    // 00427404  e8a7550400             -call 0x46c9b0
    cpu.esp -= 4;
    nfs3hp::frontend::sliderValue(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427409  d84de4                 +fmul dword ptr [ebp - 0x1c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu3 = cpu.fpu.st(0);
    x86::Float fpu4 = cpu.fpu.mul(fpu3, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-28) /* -0x1c */)));
    // 0042740c  d845fc                 +fadd dword ptr [ebp - 4]
    x86::Float fpu5 = cpu.fpu.add(fpu4, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 0042740f  d945fc                 +fld dword ptr [ebp - 4]
    x86::Float fpu6 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */));
    // 00427412  d9c9                   +fxch st(1)
    
    // 00427414  d95df8                 +fstp dword ptr [ebp - 8]
    app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = float(fpu5);
    // 00427417  d85df8                 +fcomp dword ptr [ebp - 8]
    cpu.fpu.compare(fpu6, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    // 0042741a  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 0042741c  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    cpu.fpu.count -= 1;
    }
    // 0042741d  7605                   -jbe 0x427424
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x00427424;
    }
    // 0042741f  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00427422  eb03                   -jmp 0x427427
    goto L_0x00427427;
L_0x00427424:
    // 00427424  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
L_0x00427427:
    // 00427427  8945ec                 -mov dword ptr [ebp - 0x14], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */) = cpu.eax;
    // 0042742a  d945ec                 +fld dword ptr [ebp - 0x14]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu7 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-20) /* -0x14 */));
    // 0042742d  d85df4                 +fcomp dword ptr [ebp - 0xc]
    cpu.fpu.compare(fpu7, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */)));
    // 00427430  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00427432  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 00427433  7605                   -jbe 0x42743a
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x0042743a;
    }
    // 00427435  8b45f4                 -mov eax, dword ptr [ebp - 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 00427438  eb19                   -jmp 0x427453
    goto L_0x00427453;
L_0x0042743a:
    // 0042743a  d945fc                 +fld dword ptr [ebp - 4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu8 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */));
    // 0042743d  d85df8                 +fcomp dword ptr [ebp - 8]
    cpu.fpu.compare(fpu8, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    // 00427440  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00427442  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 00427443  7605                   -jbe 0x42744a
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x0042744a;
    }
    // 00427445  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00427448  eb03                   -jmp 0x42744d
    goto L_0x0042744d;
L_0x0042744a:
    // 0042744a  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
L_0x0042744d:
    // 0042744d  8945e8                 -mov dword ptr [ebp - 0x18], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-24) /* -0x18 */) = cpu.eax;
    // 00427450  8b45e8                 -mov eax, dword ptr [ebp - 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-24) /* -0x18 */);
L_0x00427453:
    // 00427453  8945f0                 -mov dword ptr [ebp - 0x10], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = cpu.eax;
    // 00427456  8b45f0                 -mov eax, dword ptr [ebp - 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 00427459  a3e0105e00             -mov dword ptr [0x5e10e0], eax
    app->getMemory<x86::reg32>(x86::reg32(6164704) /* 0x5e10e0 */) = cpu.eax;
    // 0042745e  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00427460  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00427461  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00427462  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x90 */
void Application::sub_427470(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (tuningBrakesMoved(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 00427470  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00427471  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00427472  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00427474  83ec1c                 -sub esp, 0x1c
    (cpu.esp) -= x86::reg32(x86::sreg32(28 /*0x1c*/));
    // 00427477  8b1560d05500           -mov edx, dword ptr [0x55d060]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5623904) /* 0x55d060 */);
    // 0042747d  8955fc                 -mov dword ptr [ebp - 4], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.edx;
    // 00427480  8b1544d05500           -mov edx, dword ptr [0x55d044]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5623876) /* 0x55d044 */);
    // 00427486  8955f4                 -mov dword ptr [ebp - 0xc], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.edx;
    // 00427489  d945f4                 -fld dword ptr [ebp - 0xc]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */));
    // 0042748c  d865fc                 -fsub dword ptr [ebp - 4]
    x86::Float fpu2 = cpu.fpu.sub(fpu1, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 0042748f  31d2                   +xor edx, edx
    cpu.clear_co();
    cpu.set_szp((cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx))));
    // 00427491  d95de4                 +fstp dword ptr [ebp - 0x1c]
    app->getMemory<float>(cpu.ebp + x86::reg32(-28) /* -0x1c */) = float(fpu2);
    }
    // 00427494  e817550400             -call 0x46c9b0
    cpu.esp -= 4;
    nfs3hp::frontend::sliderValue(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427499  d84de4                 +fmul dword ptr [ebp - 0x1c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu3 = cpu.fpu.st(0);
    x86::Float fpu4 = cpu.fpu.mul(fpu3, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-28) /* -0x1c */)));
    // 0042749c  d845fc                 +fadd dword ptr [ebp - 4]
    x86::Float fpu5 = cpu.fpu.add(fpu4, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 0042749f  d945fc                 +fld dword ptr [ebp - 4]
    x86::Float fpu6 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */));
    // 004274a2  d9c9                   +fxch st(1)
    
    // 004274a4  d95df8                 +fstp dword ptr [ebp - 8]
    app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = float(fpu5);
    // 004274a7  d85df8                 +fcomp dword ptr [ebp - 8]
    cpu.fpu.compare(fpu6, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    // 004274aa  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 004274ac  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    cpu.fpu.count -= 1;
    }
    // 004274ad  7605                   -jbe 0x4274b4
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x004274b4;
    }
    // 004274af  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004274b2  eb03                   -jmp 0x4274b7
    goto L_0x004274b7;
L_0x004274b4:
    // 004274b4  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
L_0x004274b7:
    // 004274b7  8945ec                 -mov dword ptr [ebp - 0x14], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */) = cpu.eax;
    // 004274ba  d945ec                 +fld dword ptr [ebp - 0x14]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu7 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-20) /* -0x14 */));
    // 004274bd  d85df4                 +fcomp dword ptr [ebp - 0xc]
    cpu.fpu.compare(fpu7, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */)));
    // 004274c0  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 004274c2  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 004274c3  7605                   -jbe 0x4274ca
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x004274ca;
    }
    // 004274c5  8b45f4                 -mov eax, dword ptr [ebp - 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 004274c8  eb19                   -jmp 0x4274e3
    goto L_0x004274e3;
L_0x004274ca:
    // 004274ca  d945fc                 +fld dword ptr [ebp - 4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu8 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */));
    // 004274cd  d85df8                 +fcomp dword ptr [ebp - 8]
    cpu.fpu.compare(fpu8, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    // 004274d0  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 004274d2  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 004274d3  7605                   -jbe 0x4274da
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x004274da;
    }
    // 004274d5  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004274d8  eb03                   -jmp 0x4274dd
    goto L_0x004274dd;
L_0x004274da:
    // 004274da  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
L_0x004274dd:
    // 004274dd  8945e8                 -mov dword ptr [ebp - 0x18], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-24) /* -0x18 */) = cpu.eax;
    // 004274e0  8b45e8                 -mov eax, dword ptr [ebp - 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-24) /* -0x18 */);
L_0x004274e3:
    // 004274e3  8945f0                 -mov dword ptr [ebp - 0x10], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = cpu.eax;
    // 004274e6  8b45f0                 -mov eax, dword ptr [ebp - 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 004274e9  a3e4105e00             -mov dword ptr [0x5e10e4], eax
    app->getMemory<x86::reg32>(x86::reg32(6164708) /* 0x5e10e4 */) = cpu.eax;
    // 004274ee  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004274f0  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004274f1  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004274f2  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x90 */
void Application::sub_427500(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (tuningSteeringMoved(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 00427500  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00427501  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00427502  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00427504  83ec1c                 -sub esp, 0x1c
    (cpu.esp) -= x86::reg32(x86::sreg32(28 /*0x1c*/));
    // 00427507  8b1564d05500           -mov edx, dword ptr [0x55d064]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5623908) /* 0x55d064 */);
    // 0042750d  8955fc                 -mov dword ptr [ebp - 4], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.edx;
    // 00427510  8b1548d05500           -mov edx, dword ptr [0x55d048]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5623880) /* 0x55d048 */);
    // 00427516  8955f4                 -mov dword ptr [ebp - 0xc], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.edx;
    // 00427519  d945f4                 -fld dword ptr [ebp - 0xc]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */));
    // 0042751c  d865fc                 -fsub dword ptr [ebp - 4]
    x86::Float fpu2 = cpu.fpu.sub(fpu1, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 0042751f  31d2                   +xor edx, edx
    cpu.clear_co();
    cpu.set_szp((cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx))));
    // 00427521  d95de4                 +fstp dword ptr [ebp - 0x1c]
    app->getMemory<float>(cpu.ebp + x86::reg32(-28) /* -0x1c */) = float(fpu2);
    }
    // 00427524  e887540400             -call 0x46c9b0
    cpu.esp -= 4;
    nfs3hp::frontend::sliderValue(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427529  d84de4                 +fmul dword ptr [ebp - 0x1c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu3 = cpu.fpu.st(0);
    x86::Float fpu4 = cpu.fpu.mul(fpu3, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-28) /* -0x1c */)));
    // 0042752c  d845fc                 +fadd dword ptr [ebp - 4]
    x86::Float fpu5 = cpu.fpu.add(fpu4, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 0042752f  d945fc                 +fld dword ptr [ebp - 4]
    x86::Float fpu6 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */));
    // 00427532  d9c9                   +fxch st(1)
    
    // 00427534  d95df8                 +fstp dword ptr [ebp - 8]
    app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = float(fpu5);
    // 00427537  d85df8                 +fcomp dword ptr [ebp - 8]
    cpu.fpu.compare(fpu6, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    // 0042753a  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 0042753c  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    cpu.fpu.count -= 1;
    }
    // 0042753d  7605                   -jbe 0x427544
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x00427544;
    }
    // 0042753f  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00427542  eb03                   -jmp 0x427547
    goto L_0x00427547;
L_0x00427544:
    // 00427544  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
L_0x00427547:
    // 00427547  8945ec                 -mov dword ptr [ebp - 0x14], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */) = cpu.eax;
    // 0042754a  d945ec                 +fld dword ptr [ebp - 0x14]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu7 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-20) /* -0x14 */));
    // 0042754d  d85df4                 +fcomp dword ptr [ebp - 0xc]
    cpu.fpu.compare(fpu7, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */)));
    // 00427550  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00427552  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 00427553  7605                   -jbe 0x42755a
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x0042755a;
    }
    // 00427555  8b45f4                 -mov eax, dword ptr [ebp - 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 00427558  eb19                   -jmp 0x427573
    goto L_0x00427573;
L_0x0042755a:
    // 0042755a  d945fc                 +fld dword ptr [ebp - 4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu8 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */));
    // 0042755d  d85df8                 +fcomp dword ptr [ebp - 8]
    cpu.fpu.compare(fpu8, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    // 00427560  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00427562  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 00427563  7605                   -jbe 0x42756a
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x0042756a;
    }
    // 00427565  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00427568  eb03                   -jmp 0x42756d
    goto L_0x0042756d;
L_0x0042756a:
    // 0042756a  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
L_0x0042756d:
    // 0042756d  8945e8                 -mov dword ptr [ebp - 0x18], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-24) /* -0x18 */) = cpu.eax;
    // 00427570  8b45e8                 -mov eax, dword ptr [ebp - 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-24) /* -0x18 */);
L_0x00427573:
    // 00427573  8945f0                 -mov dword ptr [ebp - 0x10], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = cpu.eax;
    // 00427576  8b45f0                 -mov eax, dword ptr [ebp - 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 00427579  a3e8105e00             -mov dword ptr [0x5e10e8], eax
    app->getMemory<x86::reg32>(x86::reg32(6164712) /* 0x5e10e8 */) = cpu.eax;
    // 0042757e  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00427580  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00427581  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00427582  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x90 */
void Application::sub_427590(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (tuningGearsMoved(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 00427590  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00427591  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00427592  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00427594  83ec1c                 -sub esp, 0x1c
    (cpu.esp) -= x86::reg32(x86::sreg32(28 /*0x1c*/));
    // 00427597  8b1568d05500           -mov edx, dword ptr [0x55d068]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5623912) /* 0x55d068 */);
    // 0042759d  8955fc                 -mov dword ptr [ebp - 4], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.edx;
    // 004275a0  8b154cd05500           -mov edx, dword ptr [0x55d04c]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5623884) /* 0x55d04c */);
    // 004275a6  8955f4                 -mov dword ptr [ebp - 0xc], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.edx;
    // 004275a9  d945f4                 -fld dword ptr [ebp - 0xc]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */));
    // 004275ac  d865fc                 -fsub dword ptr [ebp - 4]
    x86::Float fpu2 = cpu.fpu.sub(fpu1, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 004275af  31d2                   +xor edx, edx
    cpu.clear_co();
    cpu.set_szp((cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx))));
    // 004275b1  d95de4                 +fstp dword ptr [ebp - 0x1c]
    app->getMemory<float>(cpu.ebp + x86::reg32(-28) /* -0x1c */) = float(fpu2);
    }
    // 004275b4  e8f7530400             -call 0x46c9b0
    cpu.esp -= 4;
    nfs3hp::frontend::sliderValue(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004275b9  d84de4                 +fmul dword ptr [ebp - 0x1c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu3 = cpu.fpu.st(0);
    x86::Float fpu4 = cpu.fpu.mul(fpu3, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-28) /* -0x1c */)));
    // 004275bc  d845fc                 +fadd dword ptr [ebp - 4]
    x86::Float fpu5 = cpu.fpu.add(fpu4, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 004275bf  d945fc                 +fld dword ptr [ebp - 4]
    x86::Float fpu6 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */));
    // 004275c2  d9c9                   +fxch st(1)
    
    // 004275c4  d95df8                 +fstp dword ptr [ebp - 8]
    app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = float(fpu5);
    // 004275c7  d85df8                 +fcomp dword ptr [ebp - 8]
    cpu.fpu.compare(fpu6, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    // 004275ca  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 004275cc  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    cpu.fpu.count -= 1;
    }
    // 004275cd  7605                   -jbe 0x4275d4
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x004275d4;
    }
    // 004275cf  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004275d2  eb03                   -jmp 0x4275d7
    goto L_0x004275d7;
L_0x004275d4:
    // 004275d4  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
L_0x004275d7:
    // 004275d7  8945ec                 -mov dword ptr [ebp - 0x14], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */) = cpu.eax;
    // 004275da  d945ec                 +fld dword ptr [ebp - 0x14]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu7 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-20) /* -0x14 */));
    // 004275dd  d85df4                 +fcomp dword ptr [ebp - 0xc]
    cpu.fpu.compare(fpu7, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */)));
    // 004275e0  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 004275e2  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 004275e3  7605                   -jbe 0x4275ea
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x004275ea;
    }
    // 004275e5  8b45f4                 -mov eax, dword ptr [ebp - 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 004275e8  eb19                   -jmp 0x427603
    goto L_0x00427603;
L_0x004275ea:
    // 004275ea  d945fc                 +fld dword ptr [ebp - 4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu8 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */));
    // 004275ed  d85df8                 +fcomp dword ptr [ebp - 8]
    cpu.fpu.compare(fpu8, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    // 004275f0  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 004275f2  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 004275f3  7605                   -jbe 0x4275fa
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x004275fa;
    }
    // 004275f5  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004275f8  eb03                   -jmp 0x4275fd
    goto L_0x004275fd;
L_0x004275fa:
    // 004275fa  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
L_0x004275fd:
    // 004275fd  8945e8                 -mov dword ptr [ebp - 0x18], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-24) /* -0x18 */) = cpu.eax;
    // 00427600  8b45e8                 -mov eax, dword ptr [ebp - 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-24) /* -0x18 */);
L_0x00427603:
    // 00427603  8945f0                 -mov dword ptr [ebp - 0x10], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = cpu.eax;
    // 00427606  8b45f0                 -mov eax, dword ptr [ebp - 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 00427609  a3ec105e00             -mov dword ptr [0x5e10ec], eax
    app->getMemory<x86::reg32>(x86::reg32(6164716) /* 0x5e10ec */) = cpu.eax;
    // 0042760e  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00427610  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00427611  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00427612  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x90 */
void Application::sub_427620(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (tuningSuspensionMoved(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 00427620  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00427621  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00427622  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00427624  83ec1c                 -sub esp, 0x1c
    (cpu.esp) -= x86::reg32(x86::sreg32(28 /*0x1c*/));
    // 00427627  8b156cd05500           -mov edx, dword ptr [0x55d06c]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5623916) /* 0x55d06c */);
    // 0042762d  8955fc                 -mov dword ptr [ebp - 4], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.edx;
    // 00427630  8b1550d05500           -mov edx, dword ptr [0x55d050]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5623888) /* 0x55d050 */);
    // 00427636  8955f4                 -mov dword ptr [ebp - 0xc], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.edx;
    // 00427639  d945f4                 -fld dword ptr [ebp - 0xc]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */));
    // 0042763c  d865fc                 -fsub dword ptr [ebp - 4]
    x86::Float fpu2 = cpu.fpu.sub(fpu1, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 0042763f  31d2                   +xor edx, edx
    cpu.clear_co();
    cpu.set_szp((cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx))));
    // 00427641  d95de4                 +fstp dword ptr [ebp - 0x1c]
    app->getMemory<float>(cpu.ebp + x86::reg32(-28) /* -0x1c */) = float(fpu2);
    }
    // 00427644  e867530400             -call 0x46c9b0
    cpu.esp -= 4;
    nfs3hp::frontend::sliderValue(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427649  d84de4                 +fmul dword ptr [ebp - 0x1c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu3 = cpu.fpu.st(0);
    x86::Float fpu4 = cpu.fpu.mul(fpu3, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-28) /* -0x1c */)));
    // 0042764c  d845fc                 +fadd dword ptr [ebp - 4]
    x86::Float fpu5 = cpu.fpu.add(fpu4, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 0042764f  d945fc                 +fld dword ptr [ebp - 4]
    x86::Float fpu6 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */));
    // 00427652  d9c9                   +fxch st(1)
    
    // 00427654  d95df8                 +fstp dword ptr [ebp - 8]
    app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = float(fpu5);
    // 00427657  d85df8                 +fcomp dword ptr [ebp - 8]
    cpu.fpu.compare(fpu6, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    // 0042765a  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 0042765c  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    cpu.fpu.count -= 1;
    }
    // 0042765d  7605                   -jbe 0x427664
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x00427664;
    }
    // 0042765f  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00427662  eb03                   -jmp 0x427667
    goto L_0x00427667;
L_0x00427664:
    // 00427664  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
L_0x00427667:
    // 00427667  8945ec                 -mov dword ptr [ebp - 0x14], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */) = cpu.eax;
    // 0042766a  d945ec                 +fld dword ptr [ebp - 0x14]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu7 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-20) /* -0x14 */));
    // 0042766d  d85df4                 +fcomp dword ptr [ebp - 0xc]
    cpu.fpu.compare(fpu7, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */)));
    // 00427670  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00427672  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 00427673  7605                   -jbe 0x42767a
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x0042767a;
    }
    // 00427675  8b45f4                 -mov eax, dword ptr [ebp - 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 00427678  eb19                   -jmp 0x427693
    goto L_0x00427693;
L_0x0042767a:
    // 0042767a  d945fc                 +fld dword ptr [ebp - 4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu8 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */));
    // 0042767d  d85df8                 +fcomp dword ptr [ebp - 8]
    cpu.fpu.compare(fpu8, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    // 00427680  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00427682  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 00427683  7605                   -jbe 0x42768a
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x0042768a;
    }
    // 00427685  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00427688  eb03                   -jmp 0x42768d
    goto L_0x0042768d;
L_0x0042768a:
    // 0042768a  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
L_0x0042768d:
    // 0042768d  8945e8                 -mov dword ptr [ebp - 0x18], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-24) /* -0x18 */) = cpu.eax;
    // 00427690  8b45e8                 -mov eax, dword ptr [ebp - 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-24) /* -0x18 */);
L_0x00427693:
    // 00427693  8945f0                 -mov dword ptr [ebp - 0x10], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = cpu.eax;
    // 00427696  8b45f0                 -mov eax, dword ptr [ebp - 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 00427699  a3f0105e00             -mov dword ptr [0x5e10f0], eax
    app->getMemory<x86::reg32>(x86::reg32(6164720) /* 0x5e10f0 */) = cpu.eax;
    // 0042769e  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004276a0  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004276a1  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004276a2  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x90 */
void Application::sub_4276b0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (tuningAeroMoved(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 004276b0  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004276b1  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004276b2  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004276b4  83ec1c                 -sub esp, 0x1c
    (cpu.esp) -= x86::reg32(x86::sreg32(28 /*0x1c*/));
    // 004276b7  8b1570d05500           -mov edx, dword ptr [0x55d070]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5623920) /* 0x55d070 */);
    // 004276bd  8955fc                 -mov dword ptr [ebp - 4], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.edx;
    // 004276c0  8b1554d05500           -mov edx, dword ptr [0x55d054]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5623892) /* 0x55d054 */);
    // 004276c6  8955f4                 -mov dword ptr [ebp - 0xc], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.edx;
    // 004276c9  d945f4                 -fld dword ptr [ebp - 0xc]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */));
    // 004276cc  d865fc                 -fsub dword ptr [ebp - 4]
    x86::Float fpu2 = cpu.fpu.sub(fpu1, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 004276cf  31d2                   +xor edx, edx
    cpu.clear_co();
    cpu.set_szp((cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx))));
    // 004276d1  d95de4                 +fstp dword ptr [ebp - 0x1c]
    app->getMemory<float>(cpu.ebp + x86::reg32(-28) /* -0x1c */) = float(fpu2);
    }
    // 004276d4  e8d7520400             -call 0x46c9b0
    cpu.esp -= 4;
    nfs3hp::frontend::sliderValue(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004276d9  d84de4                 +fmul dword ptr [ebp - 0x1c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu3 = cpu.fpu.st(0);
    x86::Float fpu4 = cpu.fpu.mul(fpu3, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-28) /* -0x1c */)));
    // 004276dc  d845fc                 +fadd dword ptr [ebp - 4]
    x86::Float fpu5 = cpu.fpu.add(fpu4, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 004276df  d945fc                 +fld dword ptr [ebp - 4]
    x86::Float fpu6 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */));
    // 004276e2  d9c9                   +fxch st(1)
    
    // 004276e4  d95df8                 +fstp dword ptr [ebp - 8]
    app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = float(fpu5);
    // 004276e7  d85df8                 +fcomp dword ptr [ebp - 8]
    cpu.fpu.compare(fpu6, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    // 004276ea  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 004276ec  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    cpu.fpu.count -= 1;
    }
    // 004276ed  7605                   -jbe 0x4276f4
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x004276f4;
    }
    // 004276ef  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004276f2  eb03                   -jmp 0x4276f7
    goto L_0x004276f7;
L_0x004276f4:
    // 004276f4  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
L_0x004276f7:
    // 004276f7  8945ec                 -mov dword ptr [ebp - 0x14], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */) = cpu.eax;
    // 004276fa  d945ec                 +fld dword ptr [ebp - 0x14]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu7 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-20) /* -0x14 */));
    // 004276fd  d85df4                 +fcomp dword ptr [ebp - 0xc]
    cpu.fpu.compare(fpu7, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */)));
    // 00427700  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00427702  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 00427703  7605                   -jbe 0x42770a
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x0042770a;
    }
    // 00427705  8b45f4                 -mov eax, dword ptr [ebp - 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 00427708  eb19                   -jmp 0x427723
    goto L_0x00427723;
L_0x0042770a:
    // 0042770a  d945fc                 +fld dword ptr [ebp - 4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu8 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */));
    // 0042770d  d85df8                 +fcomp dword ptr [ebp - 8]
    cpu.fpu.compare(fpu8, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    // 00427710  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00427712  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 00427713  7605                   -jbe 0x42771a
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x0042771a;
    }
    // 00427715  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00427718  eb03                   -jmp 0x42771d
    goto L_0x0042771d;
L_0x0042771a:
    // 0042771a  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
L_0x0042771d:
    // 0042771d  8945e8                 -mov dword ptr [ebp - 0x18], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-24) /* -0x18 */) = cpu.eax;
    // 00427720  8b45e8                 -mov eax, dword ptr [ebp - 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-24) /* -0x18 */);
L_0x00427723:
    // 00427723  8945f0                 -mov dword ptr [ebp - 0x10], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = cpu.eax;
    // 00427726  8b45f0                 -mov eax, dword ptr [ebp - 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 00427729  a3f4105e00             -mov dword ptr [0x5e10f4], eax
    app->getMemory<x86::reg32>(x86::reg32(6164724) /* 0x5e10f4 */) = cpu.eax;
    // 0042772e  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00427730  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00427731  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00427732  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x90 */
void Application::sub_427740(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (tuningTiresMoved(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 00427740  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00427741  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00427742  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00427744  83ec1c                 -sub esp, 0x1c
    (cpu.esp) -= x86::reg32(x86::sreg32(28 /*0x1c*/));
    // 00427747  8b1574d05500           -mov edx, dword ptr [0x55d074]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5623924) /* 0x55d074 */);
    // 0042774d  8955fc                 -mov dword ptr [ebp - 4], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.edx;
    // 00427750  8b1558d05500           -mov edx, dword ptr [0x55d058]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5623896) /* 0x55d058 */);
    // 00427756  8955f4                 -mov dword ptr [ebp - 0xc], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.edx;
    // 00427759  d945f4                 -fld dword ptr [ebp - 0xc]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */));
    // 0042775c  d865fc                 -fsub dword ptr [ebp - 4]
    x86::Float fpu2 = cpu.fpu.sub(fpu1, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 0042775f  31d2                   +xor edx, edx
    cpu.clear_co();
    cpu.set_szp((cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx))));
    // 00427761  d95de4                 +fstp dword ptr [ebp - 0x1c]
    app->getMemory<float>(cpu.ebp + x86::reg32(-28) /* -0x1c */) = float(fpu2);
    }
    // 00427764  e847520400             -call 0x46c9b0
    cpu.esp -= 4;
    nfs3hp::frontend::sliderValue(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427769  d84de4                 +fmul dword ptr [ebp - 0x1c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu3 = cpu.fpu.st(0);
    x86::Float fpu4 = cpu.fpu.mul(fpu3, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-28) /* -0x1c */)));
    // 0042776c  d845fc                 +fadd dword ptr [ebp - 4]
    x86::Float fpu5 = cpu.fpu.add(fpu4, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 0042776f  d945fc                 +fld dword ptr [ebp - 4]
    x86::Float fpu6 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */));
    // 00427772  d9c9                   +fxch st(1)
    
    // 00427774  d95df8                 +fstp dword ptr [ebp - 8]
    app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = float(fpu5);
    // 00427777  d85df8                 +fcomp dword ptr [ebp - 8]
    cpu.fpu.compare(fpu6, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    // 0042777a  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 0042777c  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    cpu.fpu.count -= 1;
    }
    // 0042777d  7605                   -jbe 0x427784
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x00427784;
    }
    // 0042777f  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00427782  eb03                   -jmp 0x427787
    goto L_0x00427787;
L_0x00427784:
    // 00427784  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
L_0x00427787:
    // 00427787  8945ec                 -mov dword ptr [ebp - 0x14], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */) = cpu.eax;
    // 0042778a  d945ec                 +fld dword ptr [ebp - 0x14]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu7 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-20) /* -0x14 */));
    // 0042778d  d85df4                 +fcomp dword ptr [ebp - 0xc]
    cpu.fpu.compare(fpu7, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */)));
    // 00427790  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00427792  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 00427793  7605                   -jbe 0x42779a
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x0042779a;
    }
    // 00427795  8b45f4                 -mov eax, dword ptr [ebp - 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 00427798  eb19                   -jmp 0x4277b3
    goto L_0x004277b3;
L_0x0042779a:
    // 0042779a  d945fc                 +fld dword ptr [ebp - 4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu8 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */));
    // 0042779d  d85df8                 +fcomp dword ptr [ebp - 8]
    cpu.fpu.compare(fpu8, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    // 004277a0  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 004277a2  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 004277a3  7605                   -jbe 0x4277aa
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x004277aa;
    }
    // 004277a5  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004277a8  eb03                   -jmp 0x4277ad
    goto L_0x004277ad;
L_0x004277aa:
    // 004277aa  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
L_0x004277ad:
    // 004277ad  8945e8                 -mov dword ptr [ebp - 0x18], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-24) /* -0x18 */) = cpu.eax;
    // 004277b0  8b45e8                 -mov eax, dword ptr [ebp - 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-24) /* -0x18 */);
L_0x004277b3:
    // 004277b3  8945f0                 -mov dword ptr [ebp - 0x10], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = cpu.eax;
    // 004277b6  8b45f0                 -mov eax, dword ptr [ebp - 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 004277b9  a3f8105e00             -mov dword ptr [0x5e10f8], eax
    app->getMemory<x86::reg32>(x86::reg32(6164728) /* 0x5e10f8 */) = cpu.eax;
    // 004277be  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004277c0  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004277c1  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004277c2  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x90 */
void Application::sub_4277d0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (tuningSetSliders(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 004277d0  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004277d1  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004277d2  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004277d3  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004277d5  83ec0c                 -sub esp, 0xc
    (cpu.esp) -= x86::reg32(x86::sreg32(12 /*0xc*/));
    // 004277d8  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 004277da  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004277dc  0f84be010000           -je 0x4279a0
    if (cpu.flags.zf)
    {
        goto L_0x004279a0;
    }
    // 004277e2  bad4705300             -mov edx, 0x5370d4
    cpu.edx = 5468372 /*0x5370d4*/;
    // 004277e7  e854b20100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004277ec  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004277ee  7430                   -je 0x427820
    if (cpu.flags.zf)
    {
        goto L_0x00427820;
    }
    // 004277f0  8b155cd05500           -mov edx, dword ptr [0x55d05c]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5623900) /* 0x55d05c */);
    // 004277f6  d905e0105e00           -fld dword ptr [0x5e10e0]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(x86::reg32(6164704) /* 0x5e10e0 */));
    // 004277fc  8955f8                 -mov dword ptr [ebp - 8], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.edx;
    // 004277ff  8b1540d05500           -mov edx, dword ptr [0x55d040]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5623872) /* 0x55d040 */);
    // 00427805  d865f8                 -fsub dword ptr [ebp - 8]
    x86::Float fpu2 = cpu.fpu.sub(fpu1, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    // 00427808  8955fc                 -mov dword ptr [ebp - 4], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.edx;
    // 0042780b  d945fc                 -fld dword ptr [ebp - 4]
    x86::Float fpu3 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */));
    // 0042780e  d865f8                 -fsub dword ptr [ebp - 8]
    x86::Float fpu4 = cpu.fpu.sub(fpu3, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    // 00427811  def9                   -fdivp st(1)
    x86::Float fpu5 = cpu.fpu.div(fpu2, fpu4);
    // 00427813  6a00                   -push 0
    app->getMemory<x86::reg32>(cpu.esp-4) = 0 /*0x0*/;
    cpu.esp -= 4;
    // 00427815  d95df4                 -fstp dword ptr [ebp - 0xc]
    app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */) = float(fpu5);
    // 00427818  ff75f4                 -push dword ptr [ebp - 0xc]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    cpu.esp -= 4;
    }
    // 0042781b  e830510400             -call 0x46c950
    cpu.esp -= 4;
    nfs3hp::frontend::sliderSetValue(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00427820:
    // 00427820  bae4705300             -mov edx, 0x5370e4
    cpu.edx = 5468388 /*0x5370e4*/;
    // 00427825  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00427827  e814b20100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042782c  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0042782e  7430                   -je 0x427860
    if (cpu.flags.zf)
    {
        goto L_0x00427860;
    }
    // 00427830  8b1560d05500           -mov edx, dword ptr [0x55d060]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5623904) /* 0x55d060 */);
    // 00427836  d905e4105e00           -fld dword ptr [0x5e10e4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu6 = x86::Float(app->getMemory<float>(x86::reg32(6164708) /* 0x5e10e4 */));
    // 0042783c  8955f8                 -mov dword ptr [ebp - 8], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.edx;
    // 0042783f  8b1544d05500           -mov edx, dword ptr [0x55d044]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5623876) /* 0x55d044 */);
    // 00427845  d865f8                 -fsub dword ptr [ebp - 8]
    x86::Float fpu7 = cpu.fpu.sub(fpu6, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    // 00427848  8955fc                 -mov dword ptr [ebp - 4], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.edx;
    // 0042784b  d945fc                 -fld dword ptr [ebp - 4]
    x86::Float fpu8 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */));
    // 0042784e  d865f8                 -fsub dword ptr [ebp - 8]
    x86::Float fpu9 = cpu.fpu.sub(fpu8, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    // 00427851  def9                   -fdivp st(1)
    x86::Float fpu10 = cpu.fpu.div(fpu7, fpu9);
    // 00427853  6a00                   -push 0
    app->getMemory<x86::reg32>(cpu.esp-4) = 0 /*0x0*/;
    cpu.esp -= 4;
    // 00427855  d95df4                 -fstp dword ptr [ebp - 0xc]
    app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */) = float(fpu10);
    // 00427858  ff75f4                 -push dword ptr [ebp - 0xc]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    cpu.esp -= 4;
    }
    // 0042785b  e8f0500400             -call 0x46c950
    cpu.esp -= 4;
    nfs3hp::frontend::sliderSetValue(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00427860:
    // 00427860  baf0705300             -mov edx, 0x5370f0
    cpu.edx = 5468400 /*0x5370f0*/;
    // 00427865  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00427867  e8d4b10100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042786c  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0042786e  7430                   -je 0x4278a0
    if (cpu.flags.zf)
    {
        goto L_0x004278a0;
    }
    // 00427870  8b1564d05500           -mov edx, dword ptr [0x55d064]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5623908) /* 0x55d064 */);
    // 00427876  d905e8105e00           -fld dword ptr [0x5e10e8]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu11 = x86::Float(app->getMemory<float>(x86::reg32(6164712) /* 0x5e10e8 */));
    // 0042787c  8955f8                 -mov dword ptr [ebp - 8], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.edx;
    // 0042787f  8b1548d05500           -mov edx, dword ptr [0x55d048]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5623880) /* 0x55d048 */);
    // 00427885  d865f8                 -fsub dword ptr [ebp - 8]
    x86::Float fpu12 = cpu.fpu.sub(fpu11, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    // 00427888  8955fc                 -mov dword ptr [ebp - 4], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.edx;
    // 0042788b  d945fc                 -fld dword ptr [ebp - 4]
    x86::Float fpu13 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */));
    // 0042788e  d865f8                 -fsub dword ptr [ebp - 8]
    x86::Float fpu14 = cpu.fpu.sub(fpu13, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    // 00427891  def9                   -fdivp st(1)
    x86::Float fpu15 = cpu.fpu.div(fpu12, fpu14);
    // 00427893  6a00                   -push 0
    app->getMemory<x86::reg32>(cpu.esp-4) = 0 /*0x0*/;
    cpu.esp -= 4;
    // 00427895  d95df4                 -fstp dword ptr [ebp - 0xc]
    app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */) = float(fpu15);
    // 00427898  ff75f4                 -push dword ptr [ebp - 0xc]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    cpu.esp -= 4;
    }
    // 0042789b  e8b0500400             -call 0x46c950
    cpu.esp -= 4;
    nfs3hp::frontend::sliderSetValue(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x004278a0:
    // 004278a0  ba00715300             -mov edx, 0x537100
    cpu.edx = 5468416 /*0x537100*/;
    // 004278a5  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004278a7  e894b10100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004278ac  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004278ae  7430                   -je 0x4278e0
    if (cpu.flags.zf)
    {
        goto L_0x004278e0;
    }
    // 004278b0  8b1568d05500           -mov edx, dword ptr [0x55d068]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5623912) /* 0x55d068 */);
    // 004278b6  d905ec105e00           -fld dword ptr [0x5e10ec]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu16 = x86::Float(app->getMemory<float>(x86::reg32(6164716) /* 0x5e10ec */));
    // 004278bc  8955f8                 -mov dword ptr [ebp - 8], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.edx;
    // 004278bf  8b154cd05500           -mov edx, dword ptr [0x55d04c]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5623884) /* 0x55d04c */);
    // 004278c5  d865f8                 -fsub dword ptr [ebp - 8]
    x86::Float fpu17 = cpu.fpu.sub(fpu16, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    // 004278c8  8955fc                 -mov dword ptr [ebp - 4], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.edx;
    // 004278cb  d945fc                 -fld dword ptr [ebp - 4]
    x86::Float fpu18 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */));
    // 004278ce  d865f8                 -fsub dword ptr [ebp - 8]
    x86::Float fpu19 = cpu.fpu.sub(fpu18, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    // 004278d1  def9                   -fdivp st(1)
    x86::Float fpu20 = cpu.fpu.div(fpu17, fpu19);
    // 004278d3  6a00                   -push 0
    app->getMemory<x86::reg32>(cpu.esp-4) = 0 /*0x0*/;
    cpu.esp -= 4;
    // 004278d5  d95df4                 -fstp dword ptr [ebp - 0xc]
    app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */) = float(fpu20);
    // 004278d8  ff75f4                 -push dword ptr [ebp - 0xc]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    cpu.esp -= 4;
    }
    // 004278db  e870500400             -call 0x46c950
    cpu.esp -= 4;
    nfs3hp::frontend::sliderSetValue(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x004278e0:
    // 004278e0  ba0c715300             -mov edx, 0x53710c
    cpu.edx = 5468428 /*0x53710c*/;
    // 004278e5  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004278e7  e854b10100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004278ec  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004278ee  7430                   -je 0x427920
    if (cpu.flags.zf)
    {
        goto L_0x00427920;
    }
    // 004278f0  8b156cd05500           -mov edx, dword ptr [0x55d06c]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5623916) /* 0x55d06c */);
    // 004278f6  d905f0105e00           -fld dword ptr [0x5e10f0]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu21 = x86::Float(app->getMemory<float>(x86::reg32(6164720) /* 0x5e10f0 */));
    // 004278fc  8955f8                 -mov dword ptr [ebp - 8], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.edx;
    // 004278ff  8b1550d05500           -mov edx, dword ptr [0x55d050]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5623888) /* 0x55d050 */);
    // 00427905  d865f8                 -fsub dword ptr [ebp - 8]
    x86::Float fpu22 = cpu.fpu.sub(fpu21, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    // 00427908  8955fc                 -mov dword ptr [ebp - 4], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.edx;
    // 0042790b  d945fc                 -fld dword ptr [ebp - 4]
    x86::Float fpu23 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */));
    // 0042790e  d865f8                 -fsub dword ptr [ebp - 8]
    x86::Float fpu24 = cpu.fpu.sub(fpu23, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    // 00427911  def9                   -fdivp st(1)
    x86::Float fpu25 = cpu.fpu.div(fpu22, fpu24);
    // 00427913  6a00                   -push 0
    app->getMemory<x86::reg32>(cpu.esp-4) = 0 /*0x0*/;
    cpu.esp -= 4;
    // 00427915  d95df4                 -fstp dword ptr [ebp - 0xc]
    app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */) = float(fpu25);
    // 00427918  ff75f4                 -push dword ptr [ebp - 0xc]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    cpu.esp -= 4;
    }
    // 0042791b  e830500400             -call 0x46c950
    cpu.esp -= 4;
    nfs3hp::frontend::sliderSetValue(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00427920:
    // 00427920  ba1c715300             -mov edx, 0x53711c
    cpu.edx = 5468444 /*0x53711c*/;
    // 00427925  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00427927  e814b10100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042792c  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0042792e  7430                   -je 0x427960
    if (cpu.flags.zf)
    {
        goto L_0x00427960;
    }
    // 00427930  8b1570d05500           -mov edx, dword ptr [0x55d070]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5623920) /* 0x55d070 */);
    // 00427936  d905f4105e00           -fld dword ptr [0x5e10f4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu26 = x86::Float(app->getMemory<float>(x86::reg32(6164724) /* 0x5e10f4 */));
    // 0042793c  8955f8                 -mov dword ptr [ebp - 8], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.edx;
    // 0042793f  8b1554d05500           -mov edx, dword ptr [0x55d054]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5623892) /* 0x55d054 */);
    // 00427945  d865f8                 -fsub dword ptr [ebp - 8]
    x86::Float fpu27 = cpu.fpu.sub(fpu26, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    // 00427948  8955fc                 -mov dword ptr [ebp - 4], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.edx;
    // 0042794b  d945fc                 -fld dword ptr [ebp - 4]
    x86::Float fpu28 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */));
    // 0042794e  d865f8                 -fsub dword ptr [ebp - 8]
    x86::Float fpu29 = cpu.fpu.sub(fpu28, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    // 00427951  def9                   -fdivp st(1)
    x86::Float fpu30 = cpu.fpu.div(fpu27, fpu29);
    // 00427953  6a00                   -push 0
    app->getMemory<x86::reg32>(cpu.esp-4) = 0 /*0x0*/;
    cpu.esp -= 4;
    // 00427955  d95df4                 -fstp dword ptr [ebp - 0xc]
    app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */) = float(fpu30);
    // 00427958  ff75f4                 -push dword ptr [ebp - 0xc]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    cpu.esp -= 4;
    }
    // 0042795b  e8f04f0400             -call 0x46c950
    cpu.esp -= 4;
    nfs3hp::frontend::sliderSetValue(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00427960:
    // 00427960  ba28715300             -mov edx, 0x537128
    cpu.edx = 5468456 /*0x537128*/;
    // 00427965  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00427967  e8d4b00100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042796c  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0042796e  7430                   -je 0x4279a0
    if (cpu.flags.zf)
    {
        goto L_0x004279a0;
    }
    // 00427970  8b1574d05500           -mov edx, dword ptr [0x55d074]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5623924) /* 0x55d074 */);
    // 00427976  d905f8105e00           -fld dword ptr [0x5e10f8]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu31 = x86::Float(app->getMemory<float>(x86::reg32(6164728) /* 0x5e10f8 */));
    // 0042797c  8955f8                 -mov dword ptr [ebp - 8], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.edx;
    // 0042797f  8b1558d05500           -mov edx, dword ptr [0x55d058]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5623896) /* 0x55d058 */);
    // 00427985  d865f8                 -fsub dword ptr [ebp - 8]
    x86::Float fpu32 = cpu.fpu.sub(fpu31, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    // 00427988  8955fc                 -mov dword ptr [ebp - 4], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.edx;
    // 0042798b  d945fc                 -fld dword ptr [ebp - 4]
    x86::Float fpu33 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */));
    // 0042798e  d865f8                 -fsub dword ptr [ebp - 8]
    x86::Float fpu34 = cpu.fpu.sub(fpu33, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    // 00427991  def9                   -fdivp st(1)
    x86::Float fpu35 = cpu.fpu.div(fpu32, fpu34);
    // 00427993  6a00                   -push 0
    app->getMemory<x86::reg32>(cpu.esp-4) = 0 /*0x0*/;
    cpu.esp -= 4;
    // 00427995  d95df4                 -fstp dword ptr [ebp - 0xc]
    app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */) = float(fpu35);
    // 00427998  ff75f4                 -push dword ptr [ebp - 0xc]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    cpu.esp -= 4;
    }
    // 0042799b  e8b04f0400             -call 0x46c950
    cpu.esp -= 4;
    nfs3hp::frontend::sliderSetValue(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x004279a0:
    // 004279a0  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004279a2  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004279a3  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004279a4  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004279a5  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x54 0x22 0x00 */
void Application::sub_4279b0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (tuningRememberSliders(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 004279b0  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004279b1  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004279b2  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004279b3  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004279b5  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 004279b7  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004279b9  0f84f5000000           -je 0x427ab4
    if (cpu.flags.zf)
    {
        goto L_0x00427ab4;
    }
    // 004279bf  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 004279c1  8915fc105e00           -mov dword ptr [0x5e10fc], edx
    app->getMemory<x86::reg32>(x86::reg32(6164732) /* 0x5e10fc */) = cpu.edx;
    // 004279c7  891500115e00           -mov dword ptr [0x5e1100], edx
    app->getMemory<x86::reg32>(x86::reg32(6164736) /* 0x5e1100 */) = cpu.edx;
    // 004279cd  891504115e00           -mov dword ptr [0x5e1104], edx
    app->getMemory<x86::reg32>(x86::reg32(6164740) /* 0x5e1104 */) = cpu.edx;
    // 004279d3  891508115e00           -mov dword ptr [0x5e1108], edx
    app->getMemory<x86::reg32>(x86::reg32(6164744) /* 0x5e1108 */) = cpu.edx;
    // 004279d9  89150c115e00           -mov dword ptr [0x5e110c], edx
    app->getMemory<x86::reg32>(x86::reg32(6164748) /* 0x5e110c */) = cpu.edx;
    // 004279df  891510115e00           -mov dword ptr [0x5e1110], edx
    app->getMemory<x86::reg32>(x86::reg32(6164752) /* 0x5e1110 */) = cpu.edx;
    // 004279e5  891514115e00           -mov dword ptr [0x5e1114], edx
    app->getMemory<x86::reg32>(x86::reg32(6164756) /* 0x5e1114 */) = cpu.edx;
    // 004279eb  bad4705300             -mov edx, 0x5370d4
    cpu.edx = 5468372 /*0x5370d4*/;
    // 004279f0  e84bb00100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004279f5  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004279f7  740d                   -je 0x427a06
    if (cpu.flags.zf)
    {
        goto L_0x00427a06;
    }
    // 004279f9  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 004279fb  e8b04f0400             -call 0x46c9b0
    cpu.esp -= 4;
    nfs3hp::frontend::sliderValue(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427a00  d91dfc105e00           -fstp dword ptr [0x5e10fc]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = cpu.fpu.st(0);
    app->getMemory<float>(x86::reg32(6164732) /* 0x5e10fc */) = float(fpu1);
    cpu.fpu.count -= 1;
    }
L_0x00427a06:
    // 00427a06  bae4705300             -mov edx, 0x5370e4
    cpu.edx = 5468388 /*0x5370e4*/;
    // 00427a0b  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00427a0d  e82eb00100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427a12  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00427a14  740d                   -je 0x427a23
    if (cpu.flags.zf)
    {
        goto L_0x00427a23;
    }
    // 00427a16  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00427a18  e8934f0400             -call 0x46c9b0
    cpu.esp -= 4;
    nfs3hp::frontend::sliderValue(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427a1d  d91d00115e00           -fstp dword ptr [0x5e1100]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu2 = cpu.fpu.st(0);
    app->getMemory<float>(x86::reg32(6164736) /* 0x5e1100 */) = float(fpu2);
    cpu.fpu.count -= 1;
    }
L_0x00427a23:
    // 00427a23  baf0705300             -mov edx, 0x5370f0
    cpu.edx = 5468400 /*0x5370f0*/;
    // 00427a28  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00427a2a  e811b00100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427a2f  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00427a31  740d                   -je 0x427a40
    if (cpu.flags.zf)
    {
        goto L_0x00427a40;
    }
    // 00427a33  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00427a35  e8764f0400             -call 0x46c9b0
    cpu.esp -= 4;
    nfs3hp::frontend::sliderValue(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427a3a  d91d04115e00           -fstp dword ptr [0x5e1104]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu3 = cpu.fpu.st(0);
    app->getMemory<float>(x86::reg32(6164740) /* 0x5e1104 */) = float(fpu3);
    cpu.fpu.count -= 1;
    }
L_0x00427a40:
    // 00427a40  ba00715300             -mov edx, 0x537100
    cpu.edx = 5468416 /*0x537100*/;
    // 00427a45  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00427a47  e8f4af0100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427a4c  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00427a4e  740d                   -je 0x427a5d
    if (cpu.flags.zf)
    {
        goto L_0x00427a5d;
    }
    // 00427a50  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00427a52  e8594f0400             -call 0x46c9b0
    cpu.esp -= 4;
    nfs3hp::frontend::sliderValue(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427a57  d91d08115e00           -fstp dword ptr [0x5e1108]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu4 = cpu.fpu.st(0);
    app->getMemory<float>(x86::reg32(6164744) /* 0x5e1108 */) = float(fpu4);
    cpu.fpu.count -= 1;
    }
L_0x00427a5d:
    // 00427a5d  ba0c715300             -mov edx, 0x53710c
    cpu.edx = 5468428 /*0x53710c*/;
    // 00427a62  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00427a64  e8d7af0100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427a69  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00427a6b  740d                   -je 0x427a7a
    if (cpu.flags.zf)
    {
        goto L_0x00427a7a;
    }
    // 00427a6d  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00427a6f  e83c4f0400             -call 0x46c9b0
    cpu.esp -= 4;
    nfs3hp::frontend::sliderValue(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427a74  d91d0c115e00           -fstp dword ptr [0x5e110c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu5 = cpu.fpu.st(0);
    app->getMemory<float>(x86::reg32(6164748) /* 0x5e110c */) = float(fpu5);
    cpu.fpu.count -= 1;
    }
L_0x00427a7a:
    // 00427a7a  ba1c715300             -mov edx, 0x53711c
    cpu.edx = 5468444 /*0x53711c*/;
    // 00427a7f  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00427a81  e8baaf0100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427a86  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00427a88  740d                   -je 0x427a97
    if (cpu.flags.zf)
    {
        goto L_0x00427a97;
    }
    // 00427a8a  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00427a8c  e81f4f0400             -call 0x46c9b0
    cpu.esp -= 4;
    nfs3hp::frontend::sliderValue(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427a91  d91d10115e00           -fstp dword ptr [0x5e1110]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu6 = cpu.fpu.st(0);
    app->getMemory<float>(x86::reg32(6164752) /* 0x5e1110 */) = float(fpu6);
    cpu.fpu.count -= 1;
    }
L_0x00427a97:
    // 00427a97  ba28715300             -mov edx, 0x537128
    cpu.edx = 5468456 /*0x537128*/;
    // 00427a9c  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00427a9e  e89daf0100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427aa3  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00427aa5  740d                   -je 0x427ab4
    if (cpu.flags.zf)
    {
        goto L_0x00427ab4;
    }
    // 00427aa7  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00427aa9  e8024f0400             -call 0x46c9b0
    cpu.esp -= 4;
    nfs3hp::frontend::sliderValue(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427aae  d91d14115e00           -fstp dword ptr [0x5e1114]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu7 = cpu.fpu.st(0);
    app->getMemory<float>(x86::reg32(6164756) /* 0x5e1114 */) = float(fpu7);
    cpu.fpu.count -= 1;
    }
L_0x00427ab4:
    // 00427ab4  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00427ab5  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00427ab6  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00427ab7  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8b 0xd2 */
void Application::sub_427ac0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (tuningSlidersMoved(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 00427ac0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00427ac1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00427ac2  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00427ac3  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00427ac4  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00427ac6  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00427ac8  b301                   -mov bl, 1
    cpu.bl = 1 /*0x1*/;
    // 00427aca  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00427acc  0f843c010000           -je 0x427c0e
    if (cpu.flags.zf)
    {
        goto L_0x00427c0e;
    }
    // 00427ad2  bad4705300             -mov edx, 0x5370d4
    cpu.edx = 5468372 /*0x5370d4*/;
    // 00427ad7  e864af0100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427adc  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00427ade  741a                   -je 0x427afa
    if (cpu.flags.zf)
    {
        goto L_0x00427afa;
    }
    // 00427ae0  31d2                   +xor edx, edx
    cpu.clear_co();
    cpu.set_szp((cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx))));
    // 00427ae2  e8c94e0400             -call 0x46c9b0
    cpu.esp -= 4;
    nfs3hp::frontend::sliderValue(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427ae7  d81dfc105e00           +fcomp dword ptr [0x5e10fc]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = cpu.fpu.st(0);
    cpu.fpu.compare(fpu1, x86::Float(app->getMemory<float>(x86::reg32(6164732) /* 0x5e10fc */)));
    // 00427aed  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00427aef  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    cpu.fpu.count -= 1;
    }
    // 00427af0  7404                   -je 0x427af6
    if (cpu.flags.zf)
    {
        goto L_0x00427af6;
    }
    // 00427af2  88d8                   -mov al, bl
    cpu.al = cpu.bl;
    // 00427af4  eb02                   -jmp 0x427af8
    goto L_0x00427af8;
L_0x00427af6:
    // 00427af6  30c0                   -xor al, al
    cpu.al ^= x86::reg8(x86::sreg8(cpu.al));
L_0x00427af8:
    // 00427af8  88c3                   -mov bl, al
    cpu.bl = cpu.al;
L_0x00427afa:
    // 00427afa  84db                   +test bl, bl
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.bl & cpu.bl));
    // 00427afc  752a                   -jne 0x427b28
    if (!cpu.flags.zf)
    {
        goto L_0x00427b28;
    }
    // 00427afe  bae4705300             -mov edx, 0x5370e4
    cpu.edx = 5468388 /*0x5370e4*/;
    // 00427b03  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00427b05  e836af0100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427b0a  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00427b0c  741a                   -je 0x427b28
    if (cpu.flags.zf)
    {
        goto L_0x00427b28;
    }
    // 00427b0e  31d2                   +xor edx, edx
    cpu.clear_co();
    cpu.set_szp((cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx))));
    // 00427b10  e89b4e0400             -call 0x46c9b0
    cpu.esp -= 4;
    nfs3hp::frontend::sliderValue(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427b15  d81d00115e00           +fcomp dword ptr [0x5e1100]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu2 = cpu.fpu.st(0);
    cpu.fpu.compare(fpu2, x86::Float(app->getMemory<float>(x86::reg32(6164736) /* 0x5e1100 */)));
    // 00427b1b  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00427b1d  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    cpu.fpu.count -= 1;
    }
    // 00427b1e  7404                   -je 0x427b24
    if (cpu.flags.zf)
    {
        goto L_0x00427b24;
    }
    // 00427b20  b001                   -mov al, 1
    cpu.al = 1 /*0x1*/;
    // 00427b22  eb02                   -jmp 0x427b26
    goto L_0x00427b26;
L_0x00427b24:
    // 00427b24  30c0                   -xor al, al
    cpu.al ^= x86::reg8(x86::sreg8(cpu.al));
L_0x00427b26:
    // 00427b26  88c3                   -mov bl, al
    cpu.bl = cpu.al;
L_0x00427b28:
    // 00427b28  84db                   +test bl, bl
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.bl & cpu.bl));
    // 00427b2a  752a                   -jne 0x427b56
    if (!cpu.flags.zf)
    {
        goto L_0x00427b56;
    }
    // 00427b2c  baf0705300             -mov edx, 0x5370f0
    cpu.edx = 5468400 /*0x5370f0*/;
    // 00427b31  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00427b33  e808af0100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427b38  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00427b3a  741a                   -je 0x427b56
    if (cpu.flags.zf)
    {
        goto L_0x00427b56;
    }
    // 00427b3c  31d2                   +xor edx, edx
    cpu.clear_co();
    cpu.set_szp((cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx))));
    // 00427b3e  e86d4e0400             -call 0x46c9b0
    cpu.esp -= 4;
    nfs3hp::frontend::sliderValue(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427b43  d81d04115e00           +fcomp dword ptr [0x5e1104]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu3 = cpu.fpu.st(0);
    cpu.fpu.compare(fpu3, x86::Float(app->getMemory<float>(x86::reg32(6164740) /* 0x5e1104 */)));
    // 00427b49  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00427b4b  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    cpu.fpu.count -= 1;
    }
    // 00427b4c  7404                   -je 0x427b52
    if (cpu.flags.zf)
    {
        goto L_0x00427b52;
    }
    // 00427b4e  b001                   -mov al, 1
    cpu.al = 1 /*0x1*/;
    // 00427b50  eb02                   -jmp 0x427b54
    goto L_0x00427b54;
L_0x00427b52:
    // 00427b52  30c0                   -xor al, al
    cpu.al ^= x86::reg8(x86::sreg8(cpu.al));
L_0x00427b54:
    // 00427b54  88c3                   -mov bl, al
    cpu.bl = cpu.al;
L_0x00427b56:
    // 00427b56  84db                   +test bl, bl
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.bl & cpu.bl));
    // 00427b58  752a                   -jne 0x427b84
    if (!cpu.flags.zf)
    {
        goto L_0x00427b84;
    }
    // 00427b5a  ba00715300             -mov edx, 0x537100
    cpu.edx = 5468416 /*0x537100*/;
    // 00427b5f  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00427b61  e8daae0100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427b66  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00427b68  741a                   -je 0x427b84
    if (cpu.flags.zf)
    {
        goto L_0x00427b84;
    }
    // 00427b6a  31d2                   +xor edx, edx
    cpu.clear_co();
    cpu.set_szp((cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx))));
    // 00427b6c  e83f4e0400             -call 0x46c9b0
    cpu.esp -= 4;
    nfs3hp::frontend::sliderValue(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427b71  d81d08115e00           +fcomp dword ptr [0x5e1108]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu4 = cpu.fpu.st(0);
    cpu.fpu.compare(fpu4, x86::Float(app->getMemory<float>(x86::reg32(6164744) /* 0x5e1108 */)));
    // 00427b77  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00427b79  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    cpu.fpu.count -= 1;
    }
    // 00427b7a  7404                   -je 0x427b80
    if (cpu.flags.zf)
    {
        goto L_0x00427b80;
    }
    // 00427b7c  b001                   -mov al, 1
    cpu.al = 1 /*0x1*/;
    // 00427b7e  eb02                   -jmp 0x427b82
    goto L_0x00427b82;
L_0x00427b80:
    // 00427b80  30c0                   -xor al, al
    cpu.al ^= x86::reg8(x86::sreg8(cpu.al));
L_0x00427b82:
    // 00427b82  88c3                   -mov bl, al
    cpu.bl = cpu.al;
L_0x00427b84:
    // 00427b84  84db                   +test bl, bl
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.bl & cpu.bl));
    // 00427b86  752a                   -jne 0x427bb2
    if (!cpu.flags.zf)
    {
        goto L_0x00427bb2;
    }
    // 00427b88  ba0c715300             -mov edx, 0x53710c
    cpu.edx = 5468428 /*0x53710c*/;
    // 00427b8d  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00427b8f  e8acae0100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427b94  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00427b96  741a                   -je 0x427bb2
    if (cpu.flags.zf)
    {
        goto L_0x00427bb2;
    }
    // 00427b98  31d2                   +xor edx, edx
    cpu.clear_co();
    cpu.set_szp((cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx))));
    // 00427b9a  e8114e0400             -call 0x46c9b0
    cpu.esp -= 4;
    nfs3hp::frontend::sliderValue(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427b9f  d81d0c115e00           +fcomp dword ptr [0x5e110c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu5 = cpu.fpu.st(0);
    cpu.fpu.compare(fpu5, x86::Float(app->getMemory<float>(x86::reg32(6164748) /* 0x5e110c */)));
    // 00427ba5  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00427ba7  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    cpu.fpu.count -= 1;
    }
    // 00427ba8  7404                   -je 0x427bae
    if (cpu.flags.zf)
    {
        goto L_0x00427bae;
    }
    // 00427baa  b001                   -mov al, 1
    cpu.al = 1 /*0x1*/;
    // 00427bac  eb02                   -jmp 0x427bb0
    goto L_0x00427bb0;
L_0x00427bae:
    // 00427bae  30c0                   -xor al, al
    cpu.al ^= x86::reg8(x86::sreg8(cpu.al));
L_0x00427bb0:
    // 00427bb0  88c3                   -mov bl, al
    cpu.bl = cpu.al;
L_0x00427bb2:
    // 00427bb2  84db                   +test bl, bl
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.bl & cpu.bl));
    // 00427bb4  752a                   -jne 0x427be0
    if (!cpu.flags.zf)
    {
        goto L_0x00427be0;
    }
    // 00427bb6  ba1c715300             -mov edx, 0x53711c
    cpu.edx = 5468444 /*0x53711c*/;
    // 00427bbb  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00427bbd  e87eae0100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427bc2  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00427bc4  741a                   -je 0x427be0
    if (cpu.flags.zf)
    {
        goto L_0x00427be0;
    }
    // 00427bc6  31d2                   +xor edx, edx
    cpu.clear_co();
    cpu.set_szp((cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx))));
    // 00427bc8  e8e34d0400             -call 0x46c9b0
    cpu.esp -= 4;
    nfs3hp::frontend::sliderValue(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427bcd  d81d10115e00           +fcomp dword ptr [0x5e1110]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu6 = cpu.fpu.st(0);
    cpu.fpu.compare(fpu6, x86::Float(app->getMemory<float>(x86::reg32(6164752) /* 0x5e1110 */)));
    // 00427bd3  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00427bd5  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    cpu.fpu.count -= 1;
    }
    // 00427bd6  7404                   -je 0x427bdc
    if (cpu.flags.zf)
    {
        goto L_0x00427bdc;
    }
    // 00427bd8  b001                   -mov al, 1
    cpu.al = 1 /*0x1*/;
    // 00427bda  eb02                   -jmp 0x427bde
    goto L_0x00427bde;
L_0x00427bdc:
    // 00427bdc  30c0                   -xor al, al
    cpu.al ^= x86::reg8(x86::sreg8(cpu.al));
L_0x00427bde:
    // 00427bde  88c3                   -mov bl, al
    cpu.bl = cpu.al;
L_0x00427be0:
    // 00427be0  84db                   +test bl, bl
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.bl & cpu.bl));
    // 00427be2  752a                   -jne 0x427c0e
    if (!cpu.flags.zf)
    {
        goto L_0x00427c0e;
    }
    // 00427be4  ba28715300             -mov edx, 0x537128
    cpu.edx = 5468456 /*0x537128*/;
    // 00427be9  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00427beb  e850ae0100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427bf0  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00427bf2  741a                   -je 0x427c0e
    if (cpu.flags.zf)
    {
        goto L_0x00427c0e;
    }
    // 00427bf4  31d2                   +xor edx, edx
    cpu.clear_co();
    cpu.set_szp((cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx))));
    // 00427bf6  e8b54d0400             -call 0x46c9b0
    cpu.esp -= 4;
    nfs3hp::frontend::sliderValue(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427bfb  d81d14115e00           +fcomp dword ptr [0x5e1114]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu7 = cpu.fpu.st(0);
    cpu.fpu.compare(fpu7, x86::Float(app->getMemory<float>(x86::reg32(6164756) /* 0x5e1114 */)));
    // 00427c01  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00427c03  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    cpu.fpu.count -= 1;
    }
    // 00427c04  7404                   -je 0x427c0a
    if (cpu.flags.zf)
    {
        goto L_0x00427c0a;
    }
    // 00427c06  b001                   -mov al, 1
    cpu.al = 1 /*0x1*/;
    // 00427c08  eb02                   -jmp 0x427c0c
    goto L_0x00427c0c;
L_0x00427c0a:
    // 00427c0a  30c0                   -xor al, al
    cpu.al ^= x86::reg8(x86::sreg8(cpu.al));
L_0x00427c0c:
    // 00427c0c  88c3                   -mov bl, al
    cpu.bl = cpu.al;
L_0x00427c0e:
    // 00427c0e  88d8                   -mov al, bl
    cpu.al = cpu.bl;
    // 00427c10  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00427c11  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00427c12  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00427c13  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00427c14  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 0x8b 0xdb */
void Application::sub_427c20(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (tuningBindSliders(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 00427c20  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00427c21  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00427c22  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00427c23  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00427c24  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00427c26  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00427c28  bad4705300             -mov edx, 0x5370d4
    cpu.edx = 5468372 /*0x5370d4*/;
    // 00427c2d  e80eae0100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427c32  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
    // 00427c34  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00427c36  740a                   -je 0x427c42
    if (cpu.flags.zf)
    {
        goto L_0x00427c42;
    }
    // 00427c38  bae0734200             -mov edx, 0x4273e0
    cpu.edx = 4355040 /*0x4273e0*/;
    // 00427c3d  e87e4e0400             -call 0x46cac0
    cpu.esp -= 4;
    nfs3hp::frontend::sliderSetOnMove(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00427c42:
    // 00427c42  bae4705300             -mov edx, 0x5370e4
    cpu.edx = 5468388 /*0x5370e4*/;
    // 00427c47  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00427c49  e8f2ad0100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427c4e  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00427c50  740a                   -je 0x427c5c
    if (cpu.flags.zf)
    {
        goto L_0x00427c5c;
    }
    // 00427c52  ba70744200             -mov edx, 0x427470
    cpu.edx = 4355184 /*0x427470*/;
    // 00427c57  e8644e0400             -call 0x46cac0
    cpu.esp -= 4;
    nfs3hp::frontend::sliderSetOnMove(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00427c5c:
    // 00427c5c  baf0705300             -mov edx, 0x5370f0
    cpu.edx = 5468400 /*0x5370f0*/;
    // 00427c61  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00427c63  e8d8ad0100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427c68  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00427c6a  740a                   -je 0x427c76
    if (cpu.flags.zf)
    {
        goto L_0x00427c76;
    }
    // 00427c6c  ba00754200             -mov edx, 0x427500
    cpu.edx = 4355328 /*0x427500*/;
    // 00427c71  e84a4e0400             -call 0x46cac0
    cpu.esp -= 4;
    nfs3hp::frontend::sliderSetOnMove(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00427c76:
    // 00427c76  ba00715300             -mov edx, 0x537100
    cpu.edx = 5468416 /*0x537100*/;
    // 00427c7b  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00427c7d  e8bead0100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427c82  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00427c84  740a                   -je 0x427c90
    if (cpu.flags.zf)
    {
        goto L_0x00427c90;
    }
    // 00427c86  ba90754200             -mov edx, 0x427590
    cpu.edx = 4355472 /*0x427590*/;
    // 00427c8b  e8304e0400             -call 0x46cac0
    cpu.esp -= 4;
    nfs3hp::frontend::sliderSetOnMove(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00427c90:
    // 00427c90  ba0c715300             -mov edx, 0x53710c
    cpu.edx = 5468428 /*0x53710c*/;
    // 00427c95  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00427c97  e8a4ad0100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427c9c  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00427c9e  740a                   -je 0x427caa
    if (cpu.flags.zf)
    {
        goto L_0x00427caa;
    }
    // 00427ca0  ba20764200             -mov edx, 0x427620
    cpu.edx = 4355616 /*0x427620*/;
    // 00427ca5  e8164e0400             -call 0x46cac0
    cpu.esp -= 4;
    nfs3hp::frontend::sliderSetOnMove(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00427caa:
    // 00427caa  ba1c715300             -mov edx, 0x53711c
    cpu.edx = 5468444 /*0x53711c*/;
    // 00427caf  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00427cb1  e88aad0100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427cb6  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00427cb8  740a                   -je 0x427cc4
    if (cpu.flags.zf)
    {
        goto L_0x00427cc4;
    }
    // 00427cba  bab0764200             -mov edx, 0x4276b0
    cpu.edx = 4355760 /*0x4276b0*/;
    // 00427cbf  e8fc4d0400             -call 0x46cac0
    cpu.esp -= 4;
    nfs3hp::frontend::sliderSetOnMove(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00427cc4:
    // 00427cc4  ba28715300             -mov edx, 0x537128
    cpu.edx = 5468456 /*0x537128*/;
    // 00427cc9  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00427ccb  e870ad0100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427cd0  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00427cd2  740a                   -je 0x427cde
    if (cpu.flags.zf)
    {
        goto L_0x00427cde;
    }
    // 00427cd4  ba40774200             -mov edx, 0x427740
    cpu.edx = 4355904 /*0x427740*/;
    // 00427cd9  e8e24d0400             -call 0x46cac0
    cpu.esp -= 4;
    nfs3hp::frontend::sliderSetOnMove(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00427cde:
    // 00427cde  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00427ce0  e8ebfaffff             -call 0x4277d0
    cpu.esp -= 4;
    sub_4277d0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427ce5  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00427ce7  e8c4fcffff             -call 0x4279b0
    cpu.esp -= 4;
    sub_4279b0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427cec  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 00427cee  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00427cef  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00427cf0  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00427cf1  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00427cf2  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x90 */
void Application::sub_427d00(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (tuningLoadAdvanced(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 00427d00  53                     -push ebx
    textEntry(false); /* port: the name is taken */
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00427d01  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00427d02  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00427d03  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00427d05  8b154c305500           -mov edx, dword ptr [0x55304c]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5582924) /* 0x55304c */);
    // 00427d0b  81fabcd26f00           +cmp edx, 0x6fd2bc
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(7328444 /*0x6fd2bc*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00427d11  7509                   -jne 0x427d1c
    if (!cpu.flags.zf)
    {
        goto L_0x00427d1c;
    }
    // 00427d13  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
    // 00427d15  e8364d0b00             -call 0x4dca50
    cpu.esp -= 4;
    nfs3hp::load::savePlayerSpecs(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427d1a  eb16                   -jmp 0x427d32
    goto L_0x00427d32;
L_0x00427d1c:
    // 00427d1c  81fa28d36f00           +cmp edx, 0x6fd328
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(7328552 /*0x6fd328*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00427d22  750c                   -jne 0x427d30
    if (!cpu.flags.zf)
    {
        goto L_0x00427d30;
    }
    // 00427d24  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 00427d29  e8224d0b00             -call 0x4dca50
    cpu.esp -= 4;
    nfs3hp::load::savePlayerSpecs(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427d2e  eb02                   -jmp 0x427d32
    goto L_0x00427d32;
L_0x00427d30:
    // 00427d30  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
L_0x00427d32:
    // 00427d32  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00427d34  7432                   -je 0x427d68
    if (cpu.flags.zf)
    {
        goto L_0x00427d68;
    }
    // 00427d36  8b1d4c305500           -mov ebx, dword ptr [0x55304c]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(5582924) /* 0x55304c */);
    // 00427d3c  81fbbcd26f00           +cmp ebx, 0x6fd2bc
    {
        x86::reg32 tmp1 = cpu.ebx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(7328444 /*0x6fd2bc*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00427d42  7507                   -jne 0x427d4b
    if (!cpu.flags.zf)
    {
        goto L_0x00427d4b;
    }
    // 00427d44  ba00928b00             -mov edx, 0x8b9200
    cpu.edx = 9146880 /*0x8b9200*/;
    // 00427d49  eb0d                   -jmp 0x427d58
    goto L_0x00427d58;
L_0x00427d4b:
    // 00427d4b  81fb28d36f00           +cmp ebx, 0x6fd328
    {
        x86::reg32 tmp1 = cpu.ebx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(7328552 /*0x6fd328*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00427d51  750f                   -jne 0x427d62
    if (!cpu.flags.zf)
    {
        goto L_0x00427d62;
    }
    // 00427d53  baa0888b00             -mov edx, 0x8b88a0
    cpu.edx = 9144480 /*0x8b88a0*/;
L_0x00427d58:
    // 00427d58  b8609b8b00             -mov eax, 0x8b9b60
    cpu.eax = 9149280 /*0x8b9b60*/;
    // 00427d5d  e8fe4d0b00             -call 0x4dcb60
    cpu.esp -= 4;
    sub_4dcb60(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00427d62:
    // 00427d62  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00427d64  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00427d65  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00427d66  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00427d67  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x00427d68:
    // 00427d68  b80e000000             -mov eax, 0xe
    cpu.eax = 14 /*0xe*/;
    // 00427d6d  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00427d6e  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00427d6f  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00427d70  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x8d 0x40 0x00 */
void Application::sub_427d80(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (tuningDefaultsAnswered(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 00427d80  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00427d81  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00427d82  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00427d84  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00427d86  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00427d88  83f901                 +cmp ecx, 1
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
    // 00427d8b  0f8579000000           -jne 0x427e0a
    if (!cpu.flags.zf)
    {
        goto L_0x00427e0a;
    }
    // 00427d91  e82ac90100             -call 0x4446c0
    cpu.esp -= 4;
    nfs3hp::frontend::dialogFocusedButton(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427d96  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00427d98  7564                   -jne 0x427dfe
    if (!cpu.flags.zf)
    {
        goto L_0x00427dfe;
    }
    // 00427d9a  d90524d05500           -fld dword ptr [0x55d024]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(x86::reg32(5623844) /* 0x55d024 */));
    // 00427da0  d90528d05500           -fld dword ptr [0x55d028]
    x86::Float fpu2 = x86::Float(app->getMemory<float>(x86::reg32(5623848) /* 0x55d028 */));
    // 00427da6  d9052cd05500           -fld dword ptr [0x55d02c]
    x86::Float fpu3 = x86::Float(app->getMemory<float>(x86::reg32(5623852) /* 0x55d02c */));
    // 00427dac  d90530d05500           -fld dword ptr [0x55d030]
    x86::Float fpu4 = x86::Float(app->getMemory<float>(x86::reg32(5623856) /* 0x55d030 */));
    // 00427db2  d90534d05500           -fld dword ptr [0x55d034]
    x86::Float fpu5 = x86::Float(app->getMemory<float>(x86::reg32(5623860) /* 0x55d034 */));
    // 00427db8  d90538d05500           -fld dword ptr [0x55d038]
    x86::Float fpu6 = x86::Float(app->getMemory<float>(x86::reg32(5623864) /* 0x55d038 */));
    // 00427dbe  d9053cd05500           -fld dword ptr [0x55d03c]
    x86::Float fpu7 = x86::Float(app->getMemory<float>(x86::reg32(5623868) /* 0x55d03c */));
    // 00427dc4  a150305500             -mov eax, dword ptr [0x553050]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5582928) /* 0x553050 */);
    // 00427dc9  d9ce                   -fxch st(6)
    
    // 00427dcb  d91de0105e00           -fstp dword ptr [0x5e10e0]
    app->getMemory<float>(x86::reg32(6164704) /* 0x5e10e0 */) = float(fpu1);
    // 00427dd1  d9cc                   -fxch st(4)
    
    // 00427dd3  d91de4105e00           -fstp dword ptr [0x5e10e4]
    app->getMemory<float>(x86::reg32(6164708) /* 0x5e10e4 */) = float(fpu2);
    // 00427dd9  d9ca                   -fxch st(2)
    
    // 00427ddb  d91de8105e00           -fstp dword ptr [0x5e10e8]
    app->getMemory<float>(x86::reg32(6164712) /* 0x5e10e8 */) = float(fpu3);
    // 00427de1  d91dec105e00           -fstp dword ptr [0x5e10ec]
    app->getMemory<float>(x86::reg32(6164716) /* 0x5e10ec */) = float(fpu4);
    // 00427de7  d91df0105e00           -fstp dword ptr [0x5e10f0]
    app->getMemory<float>(x86::reg32(6164720) /* 0x5e10f0 */) = float(fpu5);
    // 00427ded  d91df4105e00           -fstp dword ptr [0x5e10f4]
    app->getMemory<float>(x86::reg32(6164724) /* 0x5e10f4 */) = float(fpu6);
    // 00427df3  d91df8105e00           -fstp dword ptr [0x5e10f8]
    app->getMemory<float>(x86::reg32(6164728) /* 0x5e10f8 */) = float(fpu7);
    }
    // 00427df9  e8d2f9ffff             -call 0x4277d0
    cpu.esp -= 4;
    sub_4277d0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00427dfe:
    // 00427dfe  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 00427e00  7403                   -je 0x427e05
    if (cpu.flags.zf)
    {
        goto L_0x00427e05;
    }
    // 00427e02  c60201                 -mov byte ptr [edx], 1
    app->getMemory<x86::reg8>(cpu.edx) = 1 /*0x1*/;
L_0x00427e05:
    // 00427e05  b802000000             -mov eax, 2
    cpu.eax = 2 /*0x2*/;
L_0x00427e0a:
    // 00427e0a  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00427e0b  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00427e0c  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x40 0x00 */
void Application::sub_427e10(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (tuningDoneKey(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 00427e10  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00427e11  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00427e12  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00427e13  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00427e15  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 00427e17  89d1                   -mov ecx, edx
    cpu.ecx = cpu.edx;
    // 00427e19  6683fb0d               +cmp bx, 0xd
    {
        x86::reg16 tmp1 = cpu.bx;
        x86::reg16 tmp2 = x86::reg16(x86::sreg16(13 /*0xd*/));
        x86::reg16 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 15);
        cpu.flags.of ^= 1 & (result >> 15);
        cpu.flags.of &= (1 & (tmp1 >> 15)) != (1 & (tmp2 >> 15));
        cpu.set_szp(result);
    }
    // 00427e1d  0f856a000000           -jne 0x427e8d
    if (!cpu.flags.zf)
    {
        goto L_0x00427e8d;
    }
    // 00427e23  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 00427e25  e896fcffff             -call 0x427ac0
    cpu.esp -= 4;
    sub_427ac0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427e2a  84c0                   +test al, al
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.al & cpu.al));
    // 00427e2c  740c                   -je 0x427e3a
    if (cpu.flags.zf)
    {
        goto L_0x00427e3a;
    }
    // 00427e2e  a14c305500             -mov eax, dword ptr [0x55304c]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5582924) /* 0x55304c */);
    // 00427e33  8b00                   -mov eax, dword ptr [eax]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax);
    // 00427e35  e836f5ffff             -call 0x427370
    cpu.esp -= 4;
    sub_427370(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00427e3a:
    // 00427e3a  8b154c305500           -mov edx, dword ptr [0x55304c]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5582924) /* 0x55304c */);
    // 00427e40  81fabcd26f00           +cmp edx, 0x6fd2bc
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(7328444 /*0x6fd2bc*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00427e46  7511                   -jne 0x427e59
    if (!cpu.flags.zf)
    {
        goto L_0x00427e59;
    }
    // 00427e48  ba609b8b00             -mov edx, 0x8b9b60
    cpu.edx = 9149280 /*0x8b9b60*/;
    // 00427e4d  b800928b00             -mov eax, 0x8b9200
    cpu.eax = 9146880 /*0x8b9200*/;
    // 00427e52  e8994c0b00             -call 0x4dcaf0
    cpu.esp -= 4;
    sub_4dcaf0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427e57  eb1b                   -jmp 0x427e74
    goto L_0x00427e74;
L_0x00427e59:
    // 00427e59  81fa28d36f00           +cmp edx, 0x6fd328
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(7328552 /*0x6fd328*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00427e5f  7511                   -jne 0x427e72
    if (!cpu.flags.zf)
    {
        goto L_0x00427e72;
    }
    // 00427e61  ba609b8b00             -mov edx, 0x8b9b60
    cpu.edx = 9149280 /*0x8b9b60*/;
    // 00427e66  b8a0888b00             -mov eax, 0x8b88a0
    cpu.eax = 9144480 /*0x8b88a0*/;
    // 00427e6b  e8804c0b00             -call 0x4dcaf0
    cpu.esp -= 4;
    sub_4dcaf0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427e70  eb02                   -jmp 0x427e74
    goto L_0x00427e74;
L_0x00427e72:
    // 00427e72  30c0                   -xor al, al
    cpu.al ^= x86::reg8(x86::sreg8(cpu.al));
L_0x00427e74:
    // 00427e74  84c0                   +test al, al
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.al & cpu.al));
    // 00427e76  7405                   -je 0x427e7d
    if (cpu.flags.zf)
    {
        goto L_0x00427e7d;
    }
    // 00427e78  e883feffff             -call 0x427d00
    cpu.esp -= 4;
    sub_427d00(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00427e7d:
    // 00427e7d  0fbfdb                 -movsx ebx, bx
    cpu.ebx = x86::reg32(static_cast<x86::sreg16>(cpu.bx));
    // 00427e80  89ca                   -mov edx, ecx
    cpu.edx = cpu.ecx;
    // 00427e82  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 00427e84  e8e7930300             -call 0x461270
    cpu.esp -= 4;
    nfs3hp::frontend::buttonKey(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427e89  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00427e8a  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00427e8b  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00427e8c  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x00427e8d:
    // 00427e8d  0fbfdb                 -movsx ebx, bx
    cpu.ebx = x86::reg32(static_cast<x86::sreg16>(cpu.bx));
    // 00427e90  e8db930300             -call 0x461270
    cpu.esp -= 4;
    nfs3hp::frontend::buttonKey(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427e95  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00427e96  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00427e97  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00427e98  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x90 */
void Application::sub_427ea0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (tuningCancelKey(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 00427ea0  51                     -push ecx
    textEntry(false); /* port: the name is let go */
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00427ea1  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00427ea2  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00427ea3  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00427ea5  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 00427ea7  89d1                   -mov ecx, edx
    cpu.ecx = cpu.edx;
    // 00427ea9  6683fb0d               +cmp bx, 0xd
    {
        x86::reg16 tmp1 = cpu.bx;
        x86::reg16 tmp2 = x86::reg16(x86::sreg16(13 /*0xd*/));
        x86::reg16 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 15);
        cpu.flags.of ^= 1 & (result >> 15);
        cpu.flags.of &= (1 & (tmp1 >> 15)) != (1 & (tmp2 >> 15));
        cpu.set_szp(result);
    }
    // 00427ead  0f8573000000           -jne 0x427f26
    if (!cpu.flags.zf)
    {
        goto L_0x00427f26;
    }
    // 00427eb3  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 00427eb5  e806fcffff             -call 0x427ac0
    cpu.esp -= 4;
    sub_427ac0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427eba  84c0                   +test al, al
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.al & cpu.al));
    // 00427ebc  740c                   -je 0x427eca
    if (cpu.flags.zf)
    {
        goto L_0x00427eca;
    }
    // 00427ebe  a14c305500             -mov eax, dword ptr [0x55304c]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5582924) /* 0x55304c */);
    // 00427ec3  8b00                   -mov eax, dword ptr [eax]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax);
    // 00427ec5  e8a6f4ffff             -call 0x427370
    cpu.esp -= 4;
    sub_427370(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00427eca:
    // 00427eca  8b154c305500           -mov edx, dword ptr [0x55304c]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5582924) /* 0x55304c */);
    // 00427ed0  81fabcd26f00           +cmp edx, 0x6fd2bc
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(7328444 /*0x6fd2bc*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00427ed6  7524                   -jne 0x427efc
    if (!cpu.flags.zf)
    {
        goto L_0x00427efc;
    }
    // 00427ed8  ba609b8b00             -mov edx, 0x8b9b60
    cpu.edx = 9149280 /*0x8b9b60*/;
    // 00427edd  b800928b00             -mov eax, 0x8b9200
    cpu.eax = 9146880 /*0x8b9200*/;
    // 00427ee2  e8094c0b00             -call 0x4dcaf0
    cpu.esp -= 4;
    sub_4dcaf0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427ee7  84c0                   +test al, al
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.al & cpu.al));
    // 00427ee9  743b                   -je 0x427f26
    if (cpu.flags.zf)
    {
        goto L_0x00427f26;
    }
    // 00427eeb  ba609b8b00             -mov edx, 0x8b9b60
    cpu.edx = 9149280 /*0x8b9b60*/;
    // 00427ef0  b800928b00             -mov eax, 0x8b9200
    cpu.eax = 9146880 /*0x8b9200*/;
    // 00427ef5  e8664c0b00             -call 0x4dcb60
    cpu.esp -= 4;
    sub_4dcb60(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427efa  eb2a                   -jmp 0x427f26
    goto L_0x00427f26;
L_0x00427efc:
    // 00427efc  81fa28d36f00           +cmp edx, 0x6fd328
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(7328552 /*0x6fd328*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00427f02  7522                   -jne 0x427f26
    if (!cpu.flags.zf)
    {
        goto L_0x00427f26;
    }
    // 00427f04  ba609b8b00             -mov edx, 0x8b9b60
    cpu.edx = 9149280 /*0x8b9b60*/;
    // 00427f09  b8a0888b00             -mov eax, 0x8b88a0
    cpu.eax = 9144480 /*0x8b88a0*/;
    // 00427f0e  e8dd4b0b00             -call 0x4dcaf0
    cpu.esp -= 4;
    sub_4dcaf0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427f13  84c0                   +test al, al
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.al & cpu.al));
    // 00427f15  740f                   -je 0x427f26
    if (cpu.flags.zf)
    {
        goto L_0x00427f26;
    }
    // 00427f17  ba609b8b00             -mov edx, 0x8b9b60
    cpu.edx = 9149280 /*0x8b9b60*/;
    // 00427f1c  b8a0888b00             -mov eax, 0x8b88a0
    cpu.eax = 9144480 /*0x8b88a0*/;
    // 00427f21  e83a4c0b00             -call 0x4dcb60
    cpu.esp -= 4;
    sub_4dcb60(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00427f26:
    // 00427f26  0fbfdb                 -movsx ebx, bx
    cpu.ebx = x86::reg32(static_cast<x86::sreg16>(cpu.bx));
    // 00427f29  89ca                   -mov edx, ecx
    cpu.edx = cpu.ecx;
    // 00427f2b  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 00427f2d  e83e930300             -call 0x461270
    cpu.esp -= 4;
    nfs3hp::frontend::buttonKey(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427f32  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00427f33  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00427f34  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00427f35  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x54 0x22 0x00 */
void Application::sub_427f40(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (tuningCarListKey(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 00427f40  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00427f41  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00427f42  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00427f43  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00427f44  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00427f46  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 00427f48  89d1                   -mov ecx, edx
    cpu.ecx = cpu.edx;
    // 00427f4a  ba1d000000             -mov edx, 0x1d
    cpu.edx = 29 /*0x1d*/;
    // 00427f4f  e80c270200             -call 0x44a660
    cpu.esp -= 4;
    nfs3hp::frontend::menuShownNow(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427f54  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00427f56  7445                   -je 0x427f9d
    if (cpu.flags.zf)
    {
        goto L_0x00427f9d;
    }
    // 00427f58  a14c305500             -mov eax, dword ptr [0x55304c]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5582924) /* 0x55304c */);
    // 00427f5d  0fbfdb                 -movsx ebx, bx
    cpu.ebx = x86::reg32(static_cast<x86::sreg16>(cpu.bx));
    // 00427f60  89ca                   -mov edx, ecx
    cpu.edx = cpu.ecx;
    // 00427f62  8b38                   -mov edi, dword ptr [eax]
    cpu.edi = app->getMemory<x86::reg32>(cpu.eax);
    // 00427f64  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 00427f66  e885c00300             -call 0x463ff0
    cpu.esp -= 4;
    nfs3hp::frontend::listKey(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427f6b  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 00427f6d  a14c305500             -mov eax, dword ptr [0x55304c]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5582924) /* 0x55304c */);
    // 00427f72  3b38                   +cmp edi, dword ptr [eax]
    {
        x86::reg32 tmp1 = cpu.edi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.eax)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00427f74  7425                   -je 0x427f9b
    if (cpu.flags.zf)
    {
        goto L_0x00427f9b;
    }
    // 00427f76  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00427f78  e843fbffff             -call 0x427ac0
    cpu.esp -= 4;
    sub_427ac0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427f7d  84c0                   +test al, al
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.al & cpu.al));
    // 00427f7f  7407                   -je 0x427f88
    if (cpu.flags.zf)
    {
        goto L_0x00427f88;
    }
    // 00427f81  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 00427f83  e8e8f3ffff             -call 0x427370
    cpu.esp -= 4;
    sub_427370(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00427f88:
    // 00427f88  a14c305500             -mov eax, dword ptr [0x55304c]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5582924) /* 0x55304c */);
    // 00427f8d  8b00                   -mov eax, dword ptr [eax]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax);
    // 00427f8f  e85cf3ffff             -call 0x4272f0
    cpu.esp -= 4;
    sub_4272f0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427f94  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00427f96  e885fcffff             -call 0x427c20
    cpu.esp -= 4;
    sub_427c20(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00427f9b:
    // 00427f9b  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
L_0x00427f9d:
    // 00427f9d  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00427f9e  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00427f9f  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00427fa0  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00427fa1  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x8b 0xc0 */
void Application::sub_427fb0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (tuningDefaultsKey(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 00427fb0  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00427fb1  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00427fb2  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00427fb4  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00427fb6  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00427fb8  6683fb0d               +cmp bx, 0xd
    {
        x86::reg16 tmp1 = cpu.bx;
        x86::reg16 tmp2 = x86::reg16(x86::sreg16(13 /*0xd*/));
        x86::reg16 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 15);
        cpu.flags.of ^= 1 & (result >> 15);
        cpu.flags.of &= (1 & (tmp1 >> 15)) != (1 & (tmp2 >> 15));
        cpu.set_szp(result);
    }
    // 00427fbc  755e                   -jne 0x42801c
    if (!cpu.flags.zf)
    {
        goto L_0x0042801c;
    }
    // 00427fbe  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    // 00427fc0  745a                   -je 0x42801c
    if (cpu.flags.zf)
    {
        goto L_0x0042801c;
    }
    // 00427fc2  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 00427fc4  7456                   -je 0x42801c
    if (cpu.flags.zf)
    {
        goto L_0x0042801c;
    }
    // 00427fc6  b8e9010000             -mov eax, 0x1e9
    cpu.eax = 489 /*0x1e9*/;
    // 00427fcb  e880980a00             -call 0x4d1850
    cpu.esp -= 4;
    nfs3hp::frontend::languageText(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427fd0  a354305500             -mov dword ptr [0x553054], eax
    app->getMemory<x86::reg32>(x86::reg32(5582932) /* 0x553054 */) = cpu.eax;
    // 00427fd5  b8c4000000             -mov eax, 0xc4
    cpu.eax = 196 /*0xc4*/;
    // 00427fda  e871980a00             -call 0x4d1850
    cpu.esp -= 4;
    nfs3hp::frontend::languageText(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427fdf  a358305500             -mov dword ptr [0x553058], eax
    app->getMemory<x86::reg32>(x86::reg32(5582936) /* 0x553058 */) = cpu.eax;
    // 00427fe4  b8c5000000             -mov eax, 0xc5
    cpu.eax = 197 /*0xc5*/;
    // 00427fe9  e862980a00             -call 0x4d1850
    cpu.esp -= 4;
    nfs3hp::frontend::languageText(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00427fee  68807d4200             -push 0x427d80
    app->getMemory<x86::reg32>(cpu.esp-4) = 4357504 /*0x427d80*/;
    cpu.esp -= 4;
    // 00427ff3  6a00                   -push 0
    app->getMemory<x86::reg32>(cpu.esp-4) = 0 /*0x0*/;
    cpu.esp -= 4;
    // 00427ff5  b958305500             -mov ecx, 0x553058
    cpu.ecx = 5582936 /*0x553058*/;
    // 00427ffa  6a01                   -push 1
    app->getMemory<x86::reg32>(cpu.esp-4) = 1 /*0x1*/;
    cpu.esp -= 4;
    // 00427ffc  bb02000000             -mov ebx, 2
    cpu.ebx = 2 /*0x2*/;
    // 00428001  ba54305500             -mov edx, 0x553054
    cpu.edx = 5582932 /*0x553054*/;
    // 00428006  6a00                   -push 0
    app->getMemory<x86::reg32>(cpu.esp-4) = 0 /*0x0*/;
    cpu.esp -= 4;
    // 00428008  a35c305500             -mov dword ptr [0x55305c], eax
    app->getMemory<x86::reg32>(x86::reg32(5582940) /* 0x55305c */) = cpu.eax;
    // 0042800d  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 00428012  e8b9c60100             -call 0x4446d0
    cpu.esp -= 4;
    nfs3hp::frontend::dialogOpenQuestion(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00428017  b802000000             -mov eax, 2
    cpu.eax = 2 /*0x2*/;
L_0x0042801c:
    // 0042801c  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042801d  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042801e  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x90 */
void Application::sub_428020(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (tuningBindDoneCancel(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 00428020  53                     -push ebx
    textEntry(true); /* port: the game is waiting for a name */
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00428021  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00428022  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00428023  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00428025  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00428027  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00428029  742e                   -je 0x428059
    if (cpu.flags.zf)
    {
        goto L_0x00428059;
    }
    // 0042802b  ba34715300             -mov edx, 0x537134
    cpu.edx = 5468468 /*0x537134*/;
    // 00428030  e80baa0100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00428035  ba40715300             -mov edx, 0x537140
    cpu.edx = 5468480 /*0x537140*/;
    // 0042803a  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 0042803c  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 0042803e  e8fda90100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00428043  85db                   +test ebx, ebx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & cpu.ebx));
    // 00428045  7412                   -je 0x428059
    if (cpu.flags.zf)
    {
        goto L_0x00428059;
    }
    // 00428047  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00428049  740e                   -je 0x428059
    if (cpu.flags.zf)
    {
        goto L_0x00428059;
    }
    // 0042804b  c74330107e4200         -mov dword ptr [ebx + 0x30], 0x427e10
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(48) /* 0x30 */) = 4357648 /*0x427e10*/;
    // 00428052  c74030a07e4200         -mov dword ptr [eax + 0x30], 0x427ea0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(48) /* 0x30 */) = 4357792 /*0x427ea0*/;
L_0x00428059:
    // 00428059  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042805a  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042805b  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042805c  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x40 0x00 */
void Application::sub_428060(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (tuningFitButtons(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 00428060  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00428061  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00428062  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00428063  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00428064  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00428065  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00428067  83ec08                 -sub esp, 8
    (cpu.esp) -= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 0042806a  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 0042806c  89d3                   -mov ebx, edx
    cpu.ebx = cpu.edx;
    // 0042806e  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00428070  0f8431010000           -je 0x4281a7
    if (cpu.flags.zf)
    {
        goto L_0x004281a7;
    }
    // 00428076  e8a5ffffff             -call 0x428020
    cpu.esp -= 4;
    sub_428020(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042807b  ba4c715300             -mov edx, 0x53714c
    cpu.edx = 5468492 /*0x53714c*/;
    // 00428080  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00428082  e8b9a90100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00428087  ba54715300             -mov edx, 0x537154
    cpu.edx = 5468500 /*0x537154*/;
    // 0042808c  8945f8                 -mov dword ptr [ebp - 8], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.eax;
    // 0042808f  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 00428092  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00428094  e8a7a90100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00428099  ba60715300             -mov edx, 0x537160
    cpu.edx = 5468512 /*0x537160*/;
    // 0042809e  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 004280a0  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004280a2  e899a90100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004280a7  ba6c715300             -mov edx, 0x53716c
    cpu.edx = 5468524 /*0x53716c*/;
    // 004280ac  89c7                   -mov edi, eax
    cpu.edi = cpu.eax;
    // 004280ae  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004280b0  e88ba90100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004280b5  837df800               +cmp dword ptr [ebp - 8], 0
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
    // 004280b9  0f8477000000           -je 0x428136
    if (cpu.flags.zf)
    {
        goto L_0x00428136;
    }
    // 004280bf  89f1                   -mov ecx, esi
    cpu.ecx = cpu.esi;
    // 004280c1  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    // 004280c3  0f846d000000           -je 0x428136
    if (cpu.flags.zf)
    {
        goto L_0x00428136;
    }
    // 004280c9  85ff                   +test edi, edi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edi & cpu.edi));
    // 004280cb  0f8465000000           -je 0x428136
    if (cpu.flags.zf)
    {
        goto L_0x00428136;
    }
    // 004280d1  8b55f8                 -mov edx, dword ptr [ebp - 8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004280d4  c74230107e4200         -mov dword ptr [edx + 0x30], 0x427e10
    app->getMemory<x86::reg32>(cpu.edx + x86::reg32(48) /* 0x30 */) = 4357648 /*0x427e10*/;
    // 004280db  89fa                   -mov edx, edi
    cpu.edx = cpu.edi;
    // 004280dd  c74130107e4200         -mov dword ptr [ecx + 0x30], 0x427e10
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(48) /* 0x30 */) = 4357648 /*0x427e10*/;
    // 004280e4  c74230107e4200         -mov dword ptr [edx + 0x30], 0x427e10
    app->getMemory<x86::reg32>(cpu.edx + x86::reg32(48) /* 0x30 */) = 4357648 /*0x427e10*/;
    // 004280eb  83fb02                 +cmp ebx, 2
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
    // 004280ee  7209                   -jb 0x4280f9
    if (cpu.flags.cf)
    {
        goto L_0x004280f9;
    }
    // 004280f0  760c                   -jbe 0x4280fe
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x004280fe;
    }
    // 004280f2  83fb03                 +cmp ebx, 3
    {
        x86::reg32 tmp1 = cpu.ebx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(3 /*0x3*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004280f5  7418                   -je 0x42810f
    if (cpu.flags.zf)
    {
        goto L_0x0042810f;
    }
    // 004280f7  eb16                   -jmp 0x42810f
    goto L_0x0042810f;
L_0x004280f9:
    // 004280f9  83fb01                 +cmp ebx, 1
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
    // 004280fc  7511                   -jne 0x42810f
    if (!cpu.flags.zf)
    {
        goto L_0x0042810f;
    }
L_0x004280fe:
    // 004280fe  8b55fc                 -mov edx, dword ptr [ebp - 4]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00428101  806205ef               -and byte ptr [edx + 5], 0xef
    app->getMemory<x86::reg8>(cpu.edx + x86::reg32(5) /* 0x5 */) &= x86::reg8(x86::sreg8(239 /*0xef*/));
    // 00428105  806605ef               -and byte ptr [esi + 5], 0xef
    app->getMemory<x86::reg8>(cpu.esi + x86::reg32(5) /* 0x5 */) &= x86::reg8(x86::sreg8(239 /*0xef*/));
    // 00428109  806705ef               +and byte ptr [edi + 5], 0xef
    cpu.clear_co();
    cpu.set_szp((app->getMemory<x86::reg8>(cpu.edi + x86::reg32(5) /* 0x5 */) &= x86::reg8(x86::sreg8(239 /*0xef*/))));
    // 0042810d  eb0f                   -jmp 0x42811e
    goto L_0x0042811e;
L_0x0042810f:
    // 0042810f  8b55fc                 -mov edx, dword ptr [ebp - 4]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00428112  804a0510               -or byte ptr [edx + 5], 0x10
    app->getMemory<x86::reg8>(cpu.edx + x86::reg32(5) /* 0x5 */) |= x86::reg8(x86::sreg8(16 /*0x10*/));
    // 00428116  804e0510               -or byte ptr [esi + 5], 0x10
    app->getMemory<x86::reg8>(cpu.esi + x86::reg32(5) /* 0x5 */) |= x86::reg8(x86::sreg8(16 /*0x10*/));
    // 0042811a  804f0510               -or byte ptr [edi + 5], 0x10
    app->getMemory<x86::reg8>(cpu.edi + x86::reg32(5) /* 0x5 */) |= x86::reg8(x86::sreg8(16 /*0x10*/));
L_0x0042811e:
    // 0042811e  833d3492550000         +cmp dword ptr [0x559234], 0
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
    // 00428125  740f                   -je 0x428136
    if (cpu.flags.zf)
    {
        goto L_0x00428136;
    }
    // 00428127  8b55fc                 -mov edx, dword ptr [ebp - 4]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 0042812a  804a0510               -or byte ptr [edx + 5], 0x10
    app->getMemory<x86::reg8>(cpu.edx + x86::reg32(5) /* 0x5 */) |= x86::reg8(x86::sreg8(16 /*0x10*/));
    // 0042812e  804e0510               -or byte ptr [esi + 5], 0x10
    app->getMemory<x86::reg8>(cpu.esi + x86::reg32(5) /* 0x5 */) |= x86::reg8(x86::sreg8(16 /*0x10*/));
    // 00428132  804f0510               -or byte ptr [edi + 5], 0x10
    app->getMemory<x86::reg8>(cpu.edi + x86::reg32(5) /* 0x5 */) |= x86::reg8(x86::sreg8(16 /*0x10*/));
L_0x00428136:
    // 00428136  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00428138  0f8469000000           -je 0x4281a7
    if (cpu.flags.zf)
    {
        goto L_0x004281a7;
    }
    // 0042813e  83fb02                 +cmp ebx, 2
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
    // 00428141  7209                   -jb 0x42814c
    if (cpu.flags.cf)
    {
        goto L_0x0042814c;
    }
    // 00428143  7625                   -jbe 0x42816a
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x0042816a;
    }
    // 00428145  83fb03                 +cmp ebx, 3
    {
        x86::reg32 tmp1 = cpu.ebx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(3 /*0x3*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00428148  7439                   -je 0x428183
    if (cpu.flags.zf)
    {
        goto L_0x00428183;
    }
    // 0042814a  eb4e                   -jmp 0x42819a
    goto L_0x0042819a;
L_0x0042814c:
    // 0042814c  83fb01                 +cmp ebx, 1
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
    // 0042814f  7549                   -jne 0x42819a
    if (!cpu.flags.zf)
    {
        goto L_0x0042819a;
    }
    // 00428151  c74030407f4200         -mov dword ptr [eax + 0x30], 0x427f40
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(48) /* 0x30 */) = 4357952 /*0x427f40*/;
    // 00428158  8a7005                 -mov dh, byte ptr [eax + 5]
    cpu.dh = app->getMemory<x86::reg8>(cpu.eax + x86::reg32(5) /* 0x5 */);
    // 0042815b  c7406460305500         -mov dword ptr [eax + 0x64], 0x553060
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(100) /* 0x64 */) = 5582944 /*0x553060*/;
    // 00428162  80e6ef                 +and dh, 0xef
    cpu.clear_co();
    cpu.set_szp((cpu.dh &= x86::reg8(x86::sreg8(239 /*0xef*/))));
    // 00428165  887005                 -mov byte ptr [eax + 5], dh
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(5) /* 0x5 */) = cpu.dh;
    // 00428168  eb30                   -jmp 0x42819a
    goto L_0x0042819a;
L_0x0042816a:
    // 0042816a  c74030407f4200         -mov dword ptr [eax + 0x30], 0x427f40
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(48) /* 0x30 */) = 4357952 /*0x427f40*/;
    // 00428171  8a5805                 -mov bl, byte ptr [eax + 5]
    cpu.bl = app->getMemory<x86::reg8>(cpu.eax + x86::reg32(5) /* 0x5 */);
    // 00428174  c7406465305500         -mov dword ptr [eax + 0x64], 0x553065
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(100) /* 0x64 */) = 5582949 /*0x553065*/;
    // 0042817b  80e3ef                 +and bl, 0xef
    cpu.clear_co();
    cpu.set_szp((cpu.bl &= x86::reg8(x86::sreg8(239 /*0xef*/))));
    // 0042817e  885805                 -mov byte ptr [eax + 5], bl
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(5) /* 0x5 */) = cpu.bl;
    // 00428181  eb17                   -jmp 0x42819a
    goto L_0x0042819a;
L_0x00428183:
    // 00428183  c74030407f4200         -mov dword ptr [eax + 0x30], 0x427f40
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(48) /* 0x30 */) = 4357952 /*0x427f40*/;
    // 0042818a  8a7805                 -mov bh, byte ptr [eax + 5]
    cpu.bh = app->getMemory<x86::reg8>(cpu.eax + x86::reg32(5) /* 0x5 */);
    // 0042818d  c7406460305500         -mov dword ptr [eax + 0x64], 0x553060
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(100) /* 0x64 */) = 5582944 /*0x553060*/;
    // 00428194  80cf10                 -or bh, 0x10
    cpu.bh |= x86::reg8(x86::sreg8(16 /*0x10*/));
    // 00428197  887805                 -mov byte ptr [eax + 5], bh
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(5) /* 0x5 */) = cpu.bh;
L_0x0042819a:
    // 0042819a  833d3492550000         +cmp dword ptr [0x559234], 0
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
    // 004281a1  7404                   -je 0x4281a7
    if (cpu.flags.zf)
    {
        goto L_0x004281a7;
    }
    // 004281a3  80480510               -or byte ptr [eax + 5], 0x10
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(5) /* 0x5 */) |= x86::reg8(x86::sreg8(16 /*0x10*/));
L_0x004281a7:
    // 004281a7  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004281a9  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004281aa  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004281ab  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004281ac  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004281ad  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004281ae  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 */
void Application::sub_4281e0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (tuningPrepare(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
  goto start;
dynamic_jump:
  switch(cpu.ip)
  {
start:
    // 004281e0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004281e1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004281e2  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004281e3  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004281e4  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004281e5  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004281e6  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004281e8  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 004281ea  a350305500             -mov dword ptr [0x553050], eax
    app->getMemory<x86::reg32>(x86::reg32(5582928) /* 0x553050 */) = cpu.eax;
    // 004281ef  a148305500             -mov eax, dword ptr [0x553048]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5582920) /* 0x553048 */);
    // 004281f4  83f804                 +cmp eax, 4
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
    // 004281f7  0f8791000000           -ja 0x42828e
    if (!cpu.flags.cf && !cpu.flags.zf)
    {
        goto L_0x0042828e;
    }
    // 004281fd  ff2485b0814200         -jmp dword ptr [eax*4 + 0x4281b0]
    cpu.ip = app->getMemory<x86::reg32>(4358576 + cpu.eax * 4); goto dynamic_jump;
  case 0x00428204:
    // 00428204  babcd26f00             -mov edx, 0x6fd2bc
    cpu.edx = 7328444 /*0x6fd2bc*/;
    // 00428209  b8609b8b00             -mov eax, 0x8b9b60
    cpu.eax = 9149280 /*0x8b9b60*/;
    // 0042820e  be01000000             -mov esi, 1
    cpu.esi = 1 /*0x1*/;
    // 00428213  89154c305500           -mov dword ptr [0x55304c], edx
    app->getMemory<x86::reg32>(x86::reg32(5582924) /* 0x55304c */) = cpu.edx;
    // 00428219  ba00928b00             -mov edx, 0x8b9200
    cpu.edx = 9146880 /*0x8b9200*/;
    // 0042821e  31c9                   +xor ecx, ecx
    cpu.clear_co();
    cpu.set_szp((cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx))));
    // 00428220  e83b490b00             -call 0x4dcb60
    cpu.esp -= 4;
    sub_4dcb60(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00428225  893544305500           -mov dword ptr [0x553044], esi
    app->getMemory<x86::reg32>(x86::reg32(5582916) /* 0x553044 */) = cpu.esi;
    // 0042822b  e9d0000000             -jmp 0x428300
    goto L_0x00428300;
  case 0x00428230:
    // 00428230  bf28d36f00             -mov edi, 0x6fd328
    cpu.edi = 7328552 /*0x6fd328*/;
    // 00428235  baa0888b00             -mov edx, 0x8b88a0
    cpu.edx = 9144480 /*0x8b88a0*/;
    // 0042823a  b8609b8b00             -mov eax, 0x8b9b60
    cpu.eax = 9149280 /*0x8b9b60*/;
    // 0042823f  893d4c305500           -mov dword ptr [0x55304c], edi
    app->getMemory<x86::reg32>(x86::reg32(5582924) /* 0x55304c */) = cpu.edi;
    // 00428245  e816490b00             -call 0x4dcb60
    cpu.esp -= 4;
    sub_4dcb60(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042824a  b802000000             -mov eax, 2
    cpu.eax = 2 /*0x2*/;
    // 0042824f  31c9                   +xor ecx, ecx
    cpu.clear_co();
    cpu.set_szp((cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx))));
    // 00428251  a344305500             -mov dword ptr [0x553044], eax
    app->getMemory<x86::reg32>(x86::reg32(5582916) /* 0x553044 */) = cpu.eax;
    // 00428256  e9a5000000             -jmp 0x428300
    goto L_0x00428300;
  case 0x0042825b:
    // 0042825b  babcd26f00             -mov edx, 0x6fd2bc
    cpu.edx = 7328444 /*0x6fd2bc*/;
    // 00428260  b8609b8b00             -mov eax, 0x8b9b60
    cpu.eax = 9149280 /*0x8b9b60*/;
    // 00428265  be03000000             -mov esi, 3
    cpu.esi = 3 /*0x3*/;
    // 0042826a  89154c305500           -mov dword ptr [0x55304c], edx
    app->getMemory<x86::reg32>(x86::reg32(5582924) /* 0x55304c */) = cpu.edx;
    // 00428270  ba00928b00             -mov edx, 0x8b9200
    cpu.edx = 9146880 /*0x8b9200*/;
    // 00428275  31c9                   +xor ecx, ecx
    cpu.clear_co();
    cpu.set_szp((cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx))));
    // 00428277  e8e4480b00             -call 0x4dcb60
    cpu.esp -= 4;
    sub_4dcb60(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042827c  893544305500           -mov dword ptr [0x553044], esi
    app->getMemory<x86::reg32>(x86::reg32(5582916) /* 0x553044 */) = cpu.esi;
    // 00428282  e979000000             -jmp 0x428300
    goto L_0x00428300;
  case 0x00428287:
    // 00428287  31c9                   +xor ecx, ecx
    cpu.clear_co();
    cpu.set_szp((cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx))));
    // 00428289  e972000000             -jmp 0x428300
    goto L_0x00428300;
  case 0x0042828e:
L_0x0042828e:
    // 0042828e  a144305500             -mov eax, dword ptr [0x553044]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5582916) /* 0x553044 */);
    // 00428293  83f802                 +cmp eax, 2
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
    // 00428296  7209                   -jb 0x4282a1
    if (cpu.flags.cf)
    {
        goto L_0x004282a1;
    }
    // 00428298  760e                   -jbe 0x4282a8
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x004282a8;
    }
    // 0042829a  83f803                 +cmp eax, 3
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
    // 0042829d  7431                   -je 0x4282d0
    if (cpu.flags.zf)
    {
        goto L_0x004282d0;
    }
    // 0042829f  eb56                   -jmp 0x4282f7
    goto L_0x004282f7;
L_0x004282a1:
    // 004282a1  83f801                 +cmp eax, 1
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
    // 004282a4  742a                   -je 0x4282d0
    if (cpu.flags.zf)
    {
        goto L_0x004282d0;
    }
    // 004282a6  eb4f                   -jmp 0x4282f7
    goto L_0x004282f7;
L_0x004282a8:
    // 004282a8  bf28d36f00             -mov edi, 0x6fd328
    cpu.edi = 7328552 /*0x6fd328*/;
    // 004282ad  baa0888b00             -mov edx, 0x8b88a0
    cpu.edx = 9144480 /*0x8b88a0*/;
    // 004282b2  b8609b8b00             -mov eax, 0x8b9b60
    cpu.eax = 9149280 /*0x8b9b60*/;
    // 004282b7  893d4c305500           -mov dword ptr [0x55304c], edi
    app->getMemory<x86::reg32>(x86::reg32(5582924) /* 0x55304c */) = cpu.edi;
    // 004282bd  e89e480b00             -call 0x4dcb60
    cpu.esp -= 4;
    sub_4dcb60(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004282c2  a144305500             -mov eax, dword ptr [0x553044]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5582916) /* 0x553044 */);
    // 004282c7  31c9                   +xor ecx, ecx
    cpu.clear_co();
    cpu.set_szp((cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx))));
    // 004282c9  a348305500             -mov dword ptr [0x553048], eax
    app->getMemory<x86::reg32>(x86::reg32(5582920) /* 0x553048 */) = cpu.eax;
    // 004282ce  eb2c                   -jmp 0x4282fc
    goto L_0x004282fc;
L_0x004282d0:
    // 004282d0  b8bcd26f00             -mov eax, 0x6fd2bc
    cpu.eax = 7328444 /*0x6fd2bc*/;
    // 004282d5  ba00928b00             -mov edx, 0x8b9200
    cpu.edx = 9146880 /*0x8b9200*/;
    // 004282da  a34c305500             -mov dword ptr [0x55304c], eax
    app->getMemory<x86::reg32>(x86::reg32(5582924) /* 0x55304c */) = cpu.eax;
    // 004282df  b8609b8b00             -mov eax, 0x8b9b60
    cpu.eax = 9149280 /*0x8b9b60*/;
    // 004282e4  e877480b00             -call 0x4dcb60
    cpu.esp -= 4;
    sub_4dcb60(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004282e9  a144305500             -mov eax, dword ptr [0x553044]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5582916) /* 0x553044 */);
    // 004282ee  31c9                   +xor ecx, ecx
    cpu.clear_co();
    cpu.set_szp((cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx))));
    // 004282f0  a348305500             -mov dword ptr [0x553048], eax
    app->getMemory<x86::reg32>(x86::reg32(5582920) /* 0x553048 */) = cpu.eax;
    // 004282f5  eb05                   -jmp 0x4282fc
    goto L_0x004282fc;
L_0x004282f7:
    // 004282f7  b901000000             -mov ecx, 1
    cpu.ecx = 1 /*0x1*/;
L_0x004282fc:
    // 004282fc  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    // 004282fe  7552                   -jne 0x428352
    if (!cpu.flags.zf)
    {
        goto L_0x00428352;
    }
L_0x00428300:
    // 00428300  a14c305500             -mov eax, dword ptr [0x55304c]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5582924) /* 0x55304c */);
    // 00428305  8b00                   -mov eax, dword ptr [eax]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax);
    // 00428307  e8e4efffff             -call 0x4272f0
    cpu.esp -= 4;
    sub_4272f0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042830c  833d3492550000         +cmp dword ptr [0x559234], 0
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
    // 00428313  740a                   -je 0x42831f
    if (cpu.flags.zf)
    {
        goto L_0x0042831f;
    }
    // 00428315  689a99193f             -push 0x3f19999a
    app->getMemory<x86::reg32>(cpu.esp-4) = 1058642330 /*0x3f19999a*/;
    cpu.esp -= 4;
    // 0042831a  e811920200             -call 0x451530
    cpu.esp -= 4;
    nfs3hp::frontend::dimBackground(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x0042831f:
    // 0042831f  a148305500             -mov eax, dword ptr [0x553048]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5582920) /* 0x553048 */);
    // 00428324  8d50ff                 -lea edx, [eax - 1]
    cpu.edx = x86::reg32(cpu.eax + x86::reg32(-1) /* -0x1 */);
    // 00428327  83fa03                 +cmp edx, 3
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
    // 0042832a  7721                   -ja 0x42834d
    if (!cpu.flags.cf && !cpu.flags.zf)
    {
        goto L_0x0042834d;
    }
    // 0042832c  ff2495c4814200         -jmp dword ptr [edx*4 + 0x4281c4]
    cpu.ip = app->getMemory<x86::reg32>(4358596 + cpu.edx * 4); goto dynamic_jump;
  case 0x00428333:
    // 00428333  8b1548305500           -mov edx, dword ptr [0x553048]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5582920) /* 0x553048 */);
    // 00428339  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 0042833b  e820fdffff             -call 0x428060
    cpu.esp -= 4;
    sub_428060(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00428340  eb10                   -jmp 0x428352
    goto L_0x00428352;
  case 0x00428342:
    // 00428342  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 00428344  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 00428346  e815fdffff             -call 0x428060
    cpu.esp -= 4;
    sub_428060(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042834b  eb05                   -jmp 0x428352
    goto L_0x00428352;
L_0x0042834d:
    // 0042834d  b901000000             -mov ecx, 1
    cpu.ecx = 1 /*0x1*/;
  [[fallthrough]];
  case 0x00428352:
L_0x00428352:
    // 00428352  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00428354  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00428355  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00428356  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00428357  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00428358  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00428359  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042835a  c3                     -ret 
    cpu.esp += 4;
    return;
  default:
    NFS2_ASSERT(false);
  }
}

/* align: skip 0x8d 0x40 0x00 0x8b 0xc9 */
void Application::sub_428360(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (tuningOnEnter(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 00428360  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00428361  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00428362  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00428363  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00428364  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00428366  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00428368  e873feffff             -call 0x4281e0
    cpu.esp -= 4;
    sub_4281e0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042836d  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 0042836f  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00428371  7534                   -jne 0x4283a7
    if (!cpu.flags.zf)
    {
        goto L_0x004283a7;
    }
    // 00428373  ba78715300             -mov edx, 0x537178
    cpu.edx = 5468536 /*0x537178*/;
    // 00428378  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 0042837a  e8c1a60100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042837f  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00428381  7407                   -je 0x42838a
    if (cpu.flags.zf)
    {
        goto L_0x0042838a;
    }
    // 00428383  c74030b07f4200         -mov dword ptr [eax + 0x30], 0x427fb0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(48) /* 0x30 */) = 4358064 /*0x427fb0*/;
L_0x0042838a:
    // 0042838a  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 0042838c  ba84715300             -mov edx, 0x537184
    cpu.edx = 5468548 /*0x537184*/;
    // 00428391  e88af8ffff             -call 0x427c20
    cpu.esp -= 4;
    sub_427c20(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00428396  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 00428398  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 0042839a  e8a1a60100             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042839f  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004283a1  7404                   -je 0x4283a7
    if (cpu.flags.zf)
    {
        goto L_0x004283a7;
    }
    // 004283a3  80480510               -or byte ptr [eax + 5], 0x10
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(5) /* 0x5 */) |= x86::reg8(x86::sreg8(16 /*0x10*/));
L_0x004283a7:
    // 004283a7  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 004283a9  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004283aa  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004283ab  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004283ac  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004283ad  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8b 0xc0 */
void Application::sub_4283b0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (tuningOnExit(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 004283b0  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004283b1  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004283b2  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004283b4  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 004283b6  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 004283b8  891548305500           -mov dword ptr [0x553048], edx
    app->getMemory<x86::reg32>(x86::reg32(5582920) /* 0x553048 */) = cpu.edx;
    // 004283be  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004283bf  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004283c0  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 */
void Application::sub_4283d0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004283d0  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004283d1  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004283d3  e8f8af0700             -call 0x4a33d0
    cpu.esp -= 4;
    sub_4a33d0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004283d8  833d8ce8550000         +cmp dword ptr [0x55e88c], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5630092) /* 0x55e88c */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004283df  7407                   -je 0x4283e8
    if (cpu.flags.zf)
    {
        goto L_0x004283e8;
    }
    // 004283e1  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 004283e6  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004283e7  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004283e8:
    // 004283e8  e873f80800             -call 0x4b7c60
    cpu.esp -= 4;
    sub_4b7c60(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004283ed  e8deaf0700             -call 0x4a33d0
    cpu.esp -= 4;
    sub_4a33d0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004283f2  833d8ce8550000         +cmp dword ptr [0x55e88c], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5630092) /* 0x55e88c */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004283f9  7407                   -je 0x428402
    if (cpu.flags.zf)
    {
        goto L_0x00428402;
    }
    // 004283fb  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 00428400  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00428401  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x00428402:
    // 00428402  e889410000             -call 0x42c590
    cpu.esp -= 4;
    nfs3hp::decompiled::resetHandlingTunings(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00428407  e8c4af0700             -call 0x4a33d0
    cpu.esp -= 4;
    sub_4a33d0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042840c  833d8ce8550000         +cmp dword ptr [0x55e88c], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5630092) /* 0x55e88c */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00428413  7407                   -je 0x42841c
    if (cpu.flags.zf)
    {
        goto L_0x0042841c;
    }
    // 00428415  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 0042841a  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042841b  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x0042841c:
    // 0042841c  e8df420000             -call 0x42c700
    cpu.esp -= 4;
    nfs3hp::raceload::loadRaceCars(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00428421  e8aaaf0700             -call 0x4a33d0
    cpu.esp -= 4;
    sub_4a33d0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00428426  833d8ce8550000         +cmp dword ptr [0x55e88c], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5630092) /* 0x55e88c */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0042842d  7407                   -je 0x428436
    if (cpu.flags.zf)
    {
        goto L_0x00428436;
    }
    // 0042842f  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 00428434  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00428435  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x00428436:
    // 00428436  e8b5430000             -call 0x42c7f0
    cpu.esp -= 4;
    nfs3hp::raceload::setTimeStep(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0042843b  e890af0700             -call 0x4a33d0
    cpu.esp -= 4;
    sub_4a33d0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00428440  833d8ce8550000         +cmp dword ptr [0x55e88c], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5630092) /* 0x55e88c */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00428447  7407                   -je 0x428450
    if (cpu.flags.zf)
    {
        goto L_0x00428450;
    }
    // 00428449  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 0042844e  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042844f  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x00428450:
    // 00428450  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00428452  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00428453  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 */
void Application::sub_428460(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00428460  0000                   -add byte ptr [eax], al
    (app->getMemory<x86::reg8>(cpu.eax)) += x86::reg8(x86::sreg8(cpu.al));
    // 00428462  0000                   -add byte ptr [eax], al
    (app->getMemory<x86::reg8>(cpu.eax)) += x86::reg8(x86::sreg8(cpu.al));
    // 00428464  0000                   -add byte ptr [eax], al
    (app->getMemory<x86::reg8>(cpu.eax)) += x86::reg8(x86::sreg8(cpu.al));
    // 00428466  0000                   -add byte ptr [eax], al
    (app->getMemory<x86::reg8>(cpu.eax)) += x86::reg8(x86::sreg8(cpu.al));
    // 00428468  0000                   -add byte ptr [eax], al
    (app->getMemory<x86::reg8>(cpu.eax)) += x86::reg8(x86::sreg8(cpu.al));
    // 0042846a  0000                   -add byte ptr [eax], al
    (app->getMemory<x86::reg8>(cpu.eax)) += x86::reg8(x86::sreg8(cpu.al));
    // 0042846c  8d442000               -lea eax, [eax]
    cpu.eax = x86::reg32(cpu.eax);
    // 00428470  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00428471  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00428473  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00428474  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 0x8b 0xdb */
void Application::sub_428480(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00428480  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00428481  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00428482  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00428483  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00428484  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00428486  b9c0000000             -mov ecx, 0xc0
    cpu.ecx = 192 /*0xc0*/;
    // 0042848b  8b149548fc5e00         -mov edx, dword ptr [edx*4 + 0x5efc48]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(6224968) /* 0x5efc48 */ + cpu.edx * 4);
    // 00428492  89c7                   -mov edi, eax
    cpu.edi = cpu.eax;
    // 00428494  8db224020000           -lea esi, [edx + 0x224]
    cpu.esi = x86::reg32(cpu.edx + x86::reg32(548) /* 0x224 */);
    // 0042849a  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 0042849b  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 0042849d  c1e902                 -shr ecx, 2
    cpu.ecx >>= 2 /*0x2*/ % 32;
    // 004284a0  f2a5                   -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004284a2  8ac8                   -mov cl, al
    cpu.cl = cpu.al;
    // 004284a4  80e103                 +and cl, 3
    cpu.clear_co();
    cpu.set_szp((cpu.cl &= x86::reg8(x86::sreg8(3 /*0x3*/))));
    // 004284a7  f2a4                   -repne movsb byte ptr es:[edi], byte ptr [esi]
    while (cpu.ecx)
    {
        app->getMemory<x86::reg8>(cpu.ees + cpu.edi) = app->getMemory<x86::reg8>(cpu.esi);
        if (cpu.flags.df)
        {
            cpu.edi -= 1;
            cpu.esi -= 1;
        }
        else
        {
            cpu.edi += 1;
            cpu.esi += 1;
        }
        --cpu.ecx;
        if (cpu.flags.zf)
            break;
    }
    // 004284a9  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004284aa  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004284ab  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004284ac  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004284ad  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004284ae  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x90 */
void Application::sub_4284b0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004284b0  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004284b1  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004284b2  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004284b4  8b8828050000           -mov ecx, dword ptr [eax + 0x528]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(1320) /* 0x528 */);
    // 004284ba  8b89c4010000           -mov ecx, dword ptr [ecx + 0x1c4]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(452) /* 0x1c4 */);
    // 004284c0  890a                   -mov dword ptr [edx], ecx
    app->getMemory<x86::reg32>(cpu.edx) = cpu.ecx;
    // 004284c2  8b8028050000           -mov eax, dword ptr [eax + 0x528]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(1320) /* 0x528 */);
    // 004284c8  8b90c8010000           -mov edx, dword ptr [eax + 0x1c8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(456) /* 0x1c8 */);
    // 004284ce  8913                   -mov dword ptr [ebx], edx
    app->getMemory<x86::reg32>(cpu.ebx) = cpu.edx;
    // 004284d0  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004284d1  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004284d2  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x90 */
void Application::sub_4284e0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004284e0  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004284e1  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004284e2  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004284e3  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004284e5  83ec1c                 -sub esp, 0x1c
    (cpu.esp) -= x86::reg32(x86::sreg32(28 /*0x1c*/));
    // 004284e8  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 004284ea  89cf                   -mov edi, ecx
    cpu.edi = cpu.ecx;
    // 004284ec  83b8dc07000008         +cmp dword ptr [eax + 0x7dc], 8
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(2012) /* 0x7dc */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(8 /*0x8*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004284f3  0f8deb000000           -jge 0x4285e4
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004285e4;
    }
    // 004284f9  d9ee                   +fldz 
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = 0.0;
    // 004284fb  d85d14                 +fcomp dword ptr [ebp + 0x14]
    cpu.fpu.compare(fpu1, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(20) /* 0x14 */)));
    // 004284fe  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00428500  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 00428501  7607                   -jbe 0x42850a
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x0042850a;
    }
    // 00428503  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
    // 00428505  8945ec                 -mov dword ptr [ebp - 0x14], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */) = cpu.eax;
    // 00428508  eb35                   -jmp 0x42853f
    goto L_0x0042853f;
L_0x0042850a:
    // 0042850a  d94514                 +fld dword ptr [ebp + 0x14]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu2 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(20) /* 0x14 */));
    // 0042850d  dd55e4                 +fst qword ptr [ebp - 0x1c]
    app->getMemory<double>(cpu.ebp + x86::reg32(-28) /* -0x1c */) = double(fpu2);
    // 00428510  dc1d98715300           +fcomp qword ptr [0x537198]
    cpu.fpu.compare(fpu2, x86::Float(app->getMemory<double>(x86::reg32(5468568) /* 0x537198 */)));
    // 00428516  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00428518  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 00428519  760f                   -jbe 0x42852a
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x0042852a;
    }
    // 0042851b  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
    // 0042851d  b900002440             -mov ecx, 0x40240000
    cpu.ecx = 1076101120 /*0x40240000*/;
    // 00428522  8945f4                 -mov dword ptr [ebp - 0xc], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.eax;
    // 00428525  894df8                 -mov dword ptr [ebp - 8], ecx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.ecx;
    // 00428528  eb0c                   -jmp 0x428536
    goto L_0x00428536;
L_0x0042852a:
    // 0042852a  8b45e4                 -mov eax, dword ptr [ebp - 0x1c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-28) /* -0x1c */);
    // 0042852d  8945f4                 -mov dword ptr [ebp - 0xc], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.eax;
    // 00428530  8b45e8                 -mov eax, dword ptr [ebp - 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-24) /* -0x18 */);
    // 00428533  8945f8                 -mov dword ptr [ebp - 8], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.eax;
L_0x00428536:
    // 00428536  8b45f4                 -mov eax, dword ptr [ebp - 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 00428539  8945ec                 -mov dword ptr [ebp - 0x14], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */) = cpu.eax;
    // 0042853c  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
L_0x0042853f:
    // 0042853f  8945f0                 -mov dword ptr [ebp - 0x10], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = cpu.eax;
    // 00428542  8b8edc070000           -mov ecx, dword ptr [esi + 0x7dc]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(2012) /* 0x7dc */);
    // 00428548  8d048d00000000         -lea eax, [ecx*4]
    cpu.eax = x86::reg32(cpu.ecx * 4);
    // 0042854f  29c8                   -sub eax, ecx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.ecx));
    // 00428551  8994c6e0070000         -mov dword ptr [esi + eax*8 + 0x7e0], edx
    app->getMemory<x86::reg32>(cpu.esi + x86::reg32(2016) /* 0x7e0 */ + cpu.eax * 8) = cpu.edx;
    // 00428558  8b96dc070000           -mov edx, dword ptr [esi + 0x7dc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(2012) /* 0x7dc */);
    // 0042855e  8d049500000000         -lea eax, [edx*4]
    cpu.eax = x86::reg32(cpu.edx * 4);
    // 00428565  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 00428567  899cc6e4070000         -mov dword ptr [esi + eax*8 + 0x7e4], ebx
    app->getMemory<x86::reg32>(cpu.esi + x86::reg32(2020) /* 0x7e4 */ + cpu.eax * 8) = cpu.ebx;
    // 0042856e  8b96dc070000           -mov edx, dword ptr [esi + 0x7dc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(2012) /* 0x7dc */);
    // 00428574  8d049500000000         -lea eax, [edx*4]
    cpu.eax = x86::reg32(cpu.edx * 4);
    // 0042857b  dd45ec                 -fld qword ptr [ebp - 0x14]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu3 = x86::Float(app->getMemory<double>(cpu.ebp + x86::reg32(-20) /* -0x14 */));
    // 0042857e  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 00428580  dc0da0715300           -fmul qword ptr [0x5371a0]
    x86::Float fpu4 = cpu.fpu.mul(fpu3, x86::Float(app->getMemory<double>(x86::reg32(5468576) /* 0x5371a0 */)));
    // 00428586  89bcc6e8070000         -mov dword ptr [esi + eax*8 + 0x7e8], edi
    app->getMemory<x86::reg32>(cpu.esi + x86::reg32(2024) /* 0x7e8 */ + cpu.eax * 8) = cpu.edi;
    // 0042858d  8b96dc070000           -mov edx, dword ptr [esi + 0x7dc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(2012) /* 0x7dc */);
    // 00428593  8d049500000000         -lea eax, [edx*4]
    cpu.eax = x86::reg32(cpu.edx * 4);
    // 0042859a  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 0042859c  8b5510                 -mov edx, dword ptr [ebp + 0x10]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(16) /* 0x10 */);
    // 0042859f  8994c6ec070000         -mov dword ptr [esi + eax*8 + 0x7ec], edx
    app->getMemory<x86::reg32>(cpu.esi + x86::reg32(2028) /* 0x7ec */ + cpu.eax * 8) = cpu.edx;
    // 004285a6  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 004285a9  db1c24                 -fistp dword ptr [esp]
    app->getMemory<x86::reg32>(cpu.esp) = x86::reg32(cpu.fpu.toInteger<x86::sreg32>(fpu4));
    // 004285ac  58                     -pop eax
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004285ad  8b8edc070000           -mov ecx, dword ptr [esi + 0x7dc]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(2012) /* 0x7dc */);
    // 004285b3  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004285b5  8d048d00000000         -lea eax, [ecx*4]
    cpu.eax = x86::reg32(cpu.ecx * 4);
    // 004285bc  29c8                   -sub eax, ecx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.ecx));
    // 004285be  8994c6f0070000         -mov dword ptr [esi + eax*8 + 0x7f0], edx
    app->getMemory<x86::reg32>(cpu.esi + x86::reg32(2032) /* 0x7f0 */ + cpu.eax * 8) = cpu.edx;
    // 004285c5  8b96dc070000           -mov edx, dword ptr [esi + 0x7dc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(2012) /* 0x7dc */);
    // 004285cb  8d049500000000         -lea eax, [edx*4]
    cpu.eax = x86::reg32(cpu.edx * 4);
    // 004285d2  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 004285d4  8b5518                 -mov edx, dword ptr [ebp + 0x18]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(24) /* 0x18 */);
    // 004285d7  8994c6f4070000         -mov dword ptr [esi + eax*8 + 0x7f4], edx
    app->getMemory<x86::reg32>(cpu.esi + x86::reg32(2036) /* 0x7f4 */ + cpu.eax * 8) = cpu.edx;
    // 004285de  ff86dc070000           -inc dword ptr [esi + 0x7dc]
    (app->getMemory<x86::reg32>(cpu.esi + x86::reg32(2012) /* 0x7dc */))++;
    }
L_0x004285e4:
    // 004285e4  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004285e6  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004285e7  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004285e8  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004285e9  c20c00                 -ret 0xc
    cpu.esp += 4+12 /*0xc*/;
    return;
}

/* align: skip 0x8d 0x44 0x20 0x00 */
void Application::sub_4285f0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004285f0  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004285f1  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004285f2  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004285f4  0524020000             -add eax, 0x224
    (cpu.eax) += x86::reg32(x86::sreg32(548 /*0x224*/));
    // 004285f9  c7400400000000         -mov dword ptr [eax + 4], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */) = 0 /*0x0*/;
    // 00428600  c7400800000000         -mov dword ptr [eax + 8], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */) = 0 /*0x0*/;
    // 00428607  c7400c00000000         -mov dword ptr [eax + 0xc], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */) = 0 /*0x0*/;
    // 0042860e  c7401000000000         -mov dword ptr [eax + 0x10], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(16) /* 0x10 */) = 0 /*0x0*/;
    // 00428615  c7401400020000         -mov dword ptr [eax + 0x14], 0x200
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */) = 512 /*0x200*/;
    // 0042861c  c7403c00000000         -mov dword ptr [eax + 0x3c], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(60) /* 0x3c */) = 0 /*0x0*/;
    // 00428623  c7404000000000         -mov dword ptr [eax + 0x40], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(64) /* 0x40 */) = 0 /*0x0*/;
    // 0042862a  c7404400000000         -mov dword ptr [eax + 0x44], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(68) /* 0x44 */) = 0 /*0x0*/;
    // 00428631  c7404c00000000         -mov dword ptr [eax + 0x4c], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(76) /* 0x4c */) = 0 /*0x0*/;
    // 00428638  c7405400000000         -mov dword ptr [eax + 0x54], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(84) /* 0x54 */) = 0 /*0x0*/;
    // 0042863f  c7405c00000000         -mov dword ptr [eax + 0x5c], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(92) /* 0x5c */) = 0 /*0x0*/;
    // 00428646  c7406400000000         -mov dword ptr [eax + 0x64], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(100) /* 0x64 */) = 0 /*0x0*/;
    // 0042864d  c7404800000000         -mov dword ptr [eax + 0x48], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(72) /* 0x48 */) = 0 /*0x0*/;
    // 00428654  c7405000000000         -mov dword ptr [eax + 0x50], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(80) /* 0x50 */) = 0 /*0x0*/;
    // 0042865b  c7405800000000         -mov dword ptr [eax + 0x58], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(88) /* 0x58 */) = 0 /*0x0*/;
    // 00428662  c7406000000000         -mov dword ptr [eax + 0x60], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(96) /* 0x60 */) = 0 /*0x0*/;
    // 00428669  c7406800000000         -mov dword ptr [eax + 0x68], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(104) /* 0x68 */) = 0 /*0x0*/;
    // 00428670  31d2                   +xor edx, edx
    cpu.clear_co();
    cpu.set_szp((cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx))));
    // 00428672  c70000000000           -mov dword ptr [eax], 0
    app->getMemory<x86::reg32>(cpu.eax) = 0 /*0x0*/;
    // 00428678  eb05                   -jmp 0x42867f
    goto L_0x0042867f;
L_0x0042867a:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 0042867a  83fa08                 +cmp edx, 8
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(8 /*0x8*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0042867d  7d13                   -jge 0x428692
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00428692;
    }
L_0x0042867f:
    // 0042867f  42                     +inc edx
    {
        x86::reg32& tmp = cpu.edx;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 00428680  c744901800000000       -mov dword ptr [eax + edx*4 + 0x18], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */ + cpu.edx * 4) = 0 /*0x0*/;
    // 00428688  c744907000000000       -mov dword ptr [eax + edx*4 + 0x70], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(112) /* 0x70 */ + cpu.edx * 4) = 0 /*0x0*/;
    // 00428690  ebe8                   -jmp 0x42867a
    goto L_0x0042867a;
L_0x00428692:
    // 00428692  c7809800000000000000   -mov dword ptr [eax + 0x98], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(152) /* 0x98 */) = 0 /*0x0*/;
    // 0042869c  c7809c00000000000000   -mov dword ptr [eax + 0x9c], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(156) /* 0x9c */) = 0 /*0x0*/;
    // 004286a6  c780a000000000000000   -mov dword ptr [eax + 0xa0], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(160) /* 0xa0 */) = 0 /*0x0*/;
    // 004286b0  c780a800000000000000   -mov dword ptr [eax + 0xa8], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(168) /* 0xa8 */) = 0 /*0x0*/;
    // 004286ba  c780ac00000000000000   -mov dword ptr [eax + 0xac], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(172) /* 0xac */) = 0 /*0x0*/;
    // 004286c4  c780b000000000000000   -mov dword ptr [eax + 0xb0], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(176) /* 0xb0 */) = 0 /*0x0*/;
    // 004286ce  c780b400000000000000   -mov dword ptr [eax + 0xb4], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(180) /* 0xb4 */) = 0 /*0x0*/;
    // 004286d8  c780b800000000000000   -mov dword ptr [eax + 0xb8], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(184) /* 0xb8 */) = 0 /*0x0*/;
    // 004286e2  c780bc00000000000000   -mov dword ptr [eax + 0xbc], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(188) /* 0xbc */) = 0 /*0x0*/;
    // 004286ec  c7809400000000000000   -mov dword ptr [eax + 0x94], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(148) /* 0x94 */) = 0 /*0x0*/;
    // 004286f6  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004286f7  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004286f8  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x90 */
void Application::sub_428700(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00428700  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00428701  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00428702  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00428703  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00428704  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00428705  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00428706  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00428708  8b1d98fd5e00           -mov ebx, dword ptr [0x5efd98]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(6225304) /* 0x5efd98 */);
    // 0042870e  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 00428710  8b8020020000           -mov eax, dword ptr [eax + 0x220]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(544) /* 0x220 */);
    // 00428716  8b4818                 -mov ecx, dword ptr [eax + 0x18]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */);
    // 00428719  a19cfd5e00             -mov eax, dword ptr [0x5efd9c]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(6225308) /* 0x5efd9c */);
    // 0042871e  891485c8fa5e00         -mov dword ptr [eax*4 + 0x5efac8], edx
    app->getMemory<x86::reg32>(x86::reg32(6224584) /* 0x5efac8 */ + cpu.eax * 4) = cpu.edx;
    // 00428725  891485c8fc5e00         -mov dword ptr [eax*4 + 0x5efcc8], edx
    app->getMemory<x86::reg32>(x86::reg32(6225096) /* 0x5efcc8 */ + cpu.eax * 4) = cpu.edx;
    // 0042872c  89148588fc5e00         -mov dword ptr [eax*4 + 0x5efc88], edx
    app->getMemory<x86::reg32>(x86::reg32(6225032) /* 0x5efc88 */ + cpu.eax * 4) = cpu.edx;
    // 00428733  c7820002000000000000   -mov dword ptr [edx + 0x200], 0
    app->getMemory<x86::reg32>(cpu.edx + x86::reg32(512) /* 0x200 */) = 0 /*0x0*/;
    // 0042873d  c782f4010000ffffffff   -mov dword ptr [edx + 0x1f4], 0xffffffff
    app->getMemory<x86::reg32>(cpu.edx + x86::reg32(500) /* 0x1f4 */) = 4294967295 /*0xffffffff*/;
    // 00428747  8b359cfd5e00           -mov esi, dword ptr [0x5efd9c]
    cpu.esi = app->getMemory<x86::reg32>(x86::reg32(6225308) /* 0x5efd9c */);
    // 0042874d  8982f0010000           -mov dword ptr [edx + 0x1f0], eax
    app->getMemory<x86::reg32>(cpu.edx + x86::reg32(496) /* 0x1f0 */) = cpu.eax;
    // 00428753  46                     -inc esi
    (cpu.esi)++;
    // 00428754  8b8220020000           -mov eax, dword ptr [edx + 0x220]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(544) /* 0x220 */);
    // 0042875a  c782f8010000ffffffff   -mov dword ptr [edx + 0x1f8], 0xffffffff
    app->getMemory<x86::reg32>(cpu.edx + x86::reg32(504) /* 0x1f8 */) = 4294967295 /*0xffffffff*/;
    // 00428764  89359cfd5e00           -mov dword ptr [0x5efd9c], esi
    app->getMemory<x86::reg32>(x86::reg32(6225308) /* 0x5efd9c */) = cpu.esi;
    // 0042876a  8b4014                 -mov eax, dword ptr [eax + 0x14]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */);
    // 0042876d  8dbae4010000           -lea edi, [edx + 0x1e4]
    cpu.edi = x86::reg32(cpu.edx + x86::reg32(484) /* 0x1e4 */);
    // 00428773  e8380b0100             -call 0x4392b0
    cpu.esp -= 4;
    nfs3hp::load::carFolder(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00428778  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 0042877a  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
L_0x0042877b:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 0042877b  8a06                   -mov al, byte ptr [esi]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi);
    // 0042877d  8807                   -mov byte ptr [edi], al
    app->getMemory<x86::reg8>(cpu.edi) = cpu.al;
    // 0042877f  3c00                   +cmp al, 0
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
    // 00428781  7410                   -je 0x428793
    if (cpu.flags.zf)
    {
        goto L_0x00428793;
    }
    // 00428783  8a4601                 -mov al, byte ptr [esi + 1]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi + x86::reg32(1) /* 0x1 */);
    // 00428786  83c602                 -add esi, 2
    (cpu.esi) += x86::reg32(x86::sreg32(2 /*0x2*/));
    // 00428789  884701                 -mov byte ptr [edi + 1], al
    app->getMemory<x86::reg8>(cpu.edi + x86::reg32(1) /* 0x1 */) = cpu.al;
    // 0042878c  83c702                 -add edi, 2
    (cpu.edi) += x86::reg32(x86::sreg32(2 /*0x2*/));
    // 0042878f  3c00                   +cmp al, 0
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
    // 00428791  75e8                   -jne 0x42877b
    if (!cpu.flags.zf)
    {
        goto L_0x0042877b;
    }
L_0x00428793:
    // 00428793  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00428794  f6c101                 +test cl, 1
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.cl & 1 /*0x1*/));
    // 00428797  0f84c4000000           -je 0x428861
    if (cpu.flags.zf)
    {
        goto L_0x00428861;
    }
    // 0042879d  a1a4fd5e00             -mov eax, dword ptr [0x5efda4]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(6225316) /* 0x5efda4 */);
    // 004287a2  8982f4010000           -mov dword ptr [edx + 0x1f4], eax
    app->getMemory<x86::reg32>(cpu.edx + x86::reg32(500) /* 0x1f4 */) = cpu.eax;
    // 004287a8  8b3da4fd5e00           -mov edi, dword ptr [0x5efda4]
    cpu.edi = app->getMemory<x86::reg32>(x86::reg32(6225316) /* 0x5efda4 */);
    // 004287ae  89148548fa5e00         -mov dword ptr [eax*4 + 0x5efa48], edx
    app->getMemory<x86::reg32>(x86::reg32(6224456) /* 0x5efa48 */ + cpu.eax * 4) = cpu.edx;
    // 004287b5  8b1d98fd5e00           -mov ebx, dword ptr [0x5efd98]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(6225304) /* 0x5efd98 */);
    // 004287bb  8aa200020000           -mov ah, byte ptr [edx + 0x200]
    cpu.ah = app->getMemory<x86::reg8>(cpu.edx + x86::reg32(512) /* 0x200 */);
    // 004287c1  47                     -inc edi
    (cpu.edi)++;
    // 004287c2  80cc04                 -or ah, 4
    cpu.ah |= x86::reg8(x86::sreg8(4 /*0x4*/));
    // 004287c5  893da4fd5e00           -mov dword ptr [0x5efda4], edi
    app->getMemory<x86::reg32>(x86::reg32(6225316) /* 0x5efda4 */) = cpu.edi;
    // 004287cb  88a200020000           -mov byte ptr [edx + 0x200], ah
    app->getMemory<x86::reg8>(cpu.edx + x86::reg32(512) /* 0x200 */) = cpu.ah;
    // 004287d1  f6c108                 +test cl, 8
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.cl & 8 /*0x8*/));
    // 004287d4  7440                   -je 0x428816
    if (cpu.flags.zf)
    {
        goto L_0x00428816;
    }
    // 004287d6  a188fd5e00             -mov eax, dword ptr [0x5efd88]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(6225288) /* 0x5efd88 */);
    // 004287db  89148588fa5e00         -mov dword ptr [eax*4 + 0x5efa88], edx
    app->getMemory<x86::reg32>(x86::reg32(6224520) /* 0x5efa88 */ + cpu.eax * 4) = cpu.edx;
    // 004287e2  a178305500             -mov eax, dword ptr [0x553078]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5582968) /* 0x553078 */);
    // 004287e7  89148508fc5e00         -mov dword ptr [eax*4 + 0x5efc08], edx
    app->getMemory<x86::reg32>(x86::reg32(6224904) /* 0x5efc08 */ + cpu.eax * 4) = cpu.edx;
    // 004287ee  8a8200020000           -mov al, byte ptr [edx + 0x200]
    cpu.al = app->getMemory<x86::reg8>(cpu.edx + x86::reg32(512) /* 0x200 */);
    // 004287f4  0c20                   +or al, 0x20
    cpu.clear_co();
    cpu.set_szp((cpu.al |= x86::reg8(x86::sreg8(32 /*0x20*/))));
    // 004287f6  8b3578305500           -mov esi, dword ptr [0x553078]
    cpu.esi = app->getMemory<x86::reg32>(x86::reg32(5582968) /* 0x553078 */);
    // 004287fc  888200020000           -mov byte ptr [edx + 0x200], al
    app->getMemory<x86::reg8>(cpu.edx + x86::reg32(512) /* 0x200 */) = cpu.al;
    // 00428802  a188fd5e00             -mov eax, dword ptr [0x5efd88]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(6225288) /* 0x5efd88 */);
    // 00428807  46                     +inc esi
    {
        x86::reg32& tmp = cpu.esi;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 00428808  40                     +inc eax
    {
        x86::reg32& tmp = cpu.eax;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 00428809  893578305500           -mov dword ptr [0x553078], esi
    app->getMemory<x86::reg32>(x86::reg32(5582968) /* 0x553078 */) = cpu.esi;
    // 0042880f  a388fd5e00             -mov dword ptr [0x5efd88], eax
    app->getMemory<x86::reg32>(x86::reg32(6225288) /* 0x5efd88 */) = cpu.eax;
    // 00428814  eb45                   -jmp 0x42885b
    goto L_0x0042885b;
L_0x00428816:
    // 00428816  a1a0fd5e00             -mov eax, dword ptr [0x5efda0]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(6225312) /* 0x5efda0 */);
    // 0042881b  8982f8010000           -mov dword ptr [edx + 0x1f8], eax
    app->getMemory<x86::reg32>(cpu.edx + x86::reg32(504) /* 0x1f8 */) = cpu.eax;
    // 00428821  89148548fc5e00         -mov dword ptr [eax*4 + 0x5efc48], edx
    app->getMemory<x86::reg32>(x86::reg32(6224968) /* 0x5efc48 */ + cpu.eax * 4) = cpu.edx;
    // 00428828  a174305500             -mov eax, dword ptr [0x553074]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5582964) /* 0x553074 */);
    // 0042882d  89148508fd5e00         -mov dword ptr [eax*4 + 0x5efd08], edx
    app->getMemory<x86::reg32>(x86::reg32(6225160) /* 0x5efd08 */ + cpu.eax * 4) = cpu.edx;
    // 00428834  8aa200020000           -mov ah, byte ptr [edx + 0x200]
    cpu.ah = app->getMemory<x86::reg8>(cpu.edx + x86::reg32(512) /* 0x200 */);
    // 0042883a  80cc01                 -or ah, 1
    cpu.ah |= x86::reg8(x86::sreg8(1 /*0x1*/));
    // 0042883d  8b3da0fd5e00           -mov edi, dword ptr [0x5efda0]
    cpu.edi = app->getMemory<x86::reg32>(x86::reg32(6225312) /* 0x5efda0 */);
    // 00428843  88a200020000           -mov byte ptr [edx + 0x200], ah
    app->getMemory<x86::reg8>(cpu.edx + x86::reg32(512) /* 0x200 */) = cpu.ah;
    // 00428849  a174305500             -mov eax, dword ptr [0x553074]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5582964) /* 0x553074 */);
    // 0042884e  47                     -inc edi
    (cpu.edi)++;
    // 0042884f  40                     -inc eax
    (cpu.eax)++;
    // 00428850  893da0fd5e00           -mov dword ptr [0x5efda0], edi
    app->getMemory<x86::reg32>(x86::reg32(6225312) /* 0x5efda0 */) = cpu.edi;
    // 00428856  a374305500             -mov dword ptr [0x553074], eax
    app->getMemory<x86::reg32>(x86::reg32(5582964) /* 0x553074 */) = cpu.eax;
L_0x0042885b:
    // 0042885b  891d98fd5e00           -mov dword ptr [0x5efd98], ebx
    app->getMemory<x86::reg32>(x86::reg32(6225304) /* 0x5efd98 */) = cpu.ebx;
L_0x00428861:
    // 00428861  8b1d98fd5e00           -mov ebx, dword ptr [0x5efd98]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(6225304) /* 0x5efd98 */);
    // 00428867  f6c102                 +test cl, 2
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.cl & 2 /*0x2*/));
    // 0042886a  7464                   -je 0x4288d0
    if (cpu.flags.zf)
    {
        goto L_0x004288d0;
    }
    // 0042886c  89149d08fb5e00         -mov dword ptr [ebx*4 + 0x5efb08], edx
    app->getMemory<x86::reg32>(x86::reg32(6224648) /* 0x5efb08 */ + cpu.ebx * 4) = cpu.edx;
    // 00428873  808a0002000002         -or byte ptr [edx + 0x200], 2
    app->getMemory<x86::reg8>(cpu.edx + x86::reg32(512) /* 0x200 */) |= x86::reg8(x86::sreg8(2 /*0x2*/));
    // 0042887a  a194fd5e00             -mov eax, dword ptr [0x5efd94]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(6225300) /* 0x5efd94 */);
    // 0042887f  89148588fb5e00         -mov dword ptr [eax*4 + 0x5efb88], edx
    app->getMemory<x86::reg32>(x86::reg32(6224776) /* 0x5efb88 */ + cpu.eax * 4) = cpu.edx;
    // 00428886  8aa200020000           -mov ah, byte ptr [edx + 0x200]
    cpu.ah = app->getMemory<x86::reg8>(cpu.edx + x86::reg32(512) /* 0x200 */);
    // 0042888c  8b3594fd5e00           -mov esi, dword ptr [0x5efd94]
    cpu.esi = app->getMemory<x86::reg32>(x86::reg32(6225300) /* 0x5efd94 */);
    // 00428892  80cc08                 -or ah, 8
    cpu.ah |= x86::reg8(x86::sreg8(8 /*0x8*/));
    // 00428895  8b3da0fd5e00           -mov edi, dword ptr [0x5efda0]
    cpu.edi = app->getMemory<x86::reg32>(x86::reg32(6225312) /* 0x5efda0 */);
    // 0042889b  88a200020000           -mov byte ptr [edx + 0x200], ah
    app->getMemory<x86::reg8>(cpu.edx + x86::reg32(512) /* 0x200 */) = cpu.ah;
    // 004288a1  a1a0fd5e00             -mov eax, dword ptr [0x5efda0]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(6225312) /* 0x5efda0 */);
    // 004288a6  43                     -inc ebx
    (cpu.ebx)++;
    // 004288a7  8982f8010000           -mov dword ptr [edx + 0x1f8], eax
    app->getMemory<x86::reg32>(cpu.edx + x86::reg32(504) /* 0x1f8 */) = cpu.eax;
    // 004288ad  46                     -inc esi
    (cpu.esi)++;
    // 004288ae  89148548fc5e00         -mov dword ptr [eax*4 + 0x5efc48], edx
    app->getMemory<x86::reg32>(x86::reg32(6224968) /* 0x5efc48 */ + cpu.eax * 4) = cpu.edx;
    // 004288b5  47                     -inc edi
    (cpu.edi)++;
    // 004288b6  8a8200020000           -mov al, byte ptr [edx + 0x200]
    cpu.al = app->getMemory<x86::reg8>(cpu.edx + x86::reg32(512) /* 0x200 */);
    // 004288bc  893594fd5e00           -mov dword ptr [0x5efd94], esi
    app->getMemory<x86::reg32>(x86::reg32(6225300) /* 0x5efd94 */) = cpu.esi;
    // 004288c2  0c01                   -or al, 1
    cpu.al |= x86::reg8(x86::sreg8(1 /*0x1*/));
    // 004288c4  893da0fd5e00           -mov dword ptr [0x5efda0], edi
    app->getMemory<x86::reg32>(x86::reg32(6225312) /* 0x5efda0 */) = cpu.edi;
    // 004288ca  888200020000           -mov byte ptr [edx + 0x200], al
    app->getMemory<x86::reg8>(cpu.edx + x86::reg32(512) /* 0x200 */) = cpu.al;
L_0x004288d0:
    // 004288d0  f6c104                 +test cl, 4
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.cl & 4 /*0x4*/));
    // 004288d3  742d                   -je 0x428902
    if (cpu.flags.zf)
    {
        goto L_0x00428902;
    }
    // 004288d5  89149d08fb5e00         -mov dword ptr [ebx*4 + 0x5efb08], edx
    app->getMemory<x86::reg32>(x86::reg32(6224648) /* 0x5efb08 */ + cpu.ebx * 4) = cpu.edx;
    // 004288dc  808a0002000002         -or byte ptr [edx + 0x200], 2
    app->getMemory<x86::reg8>(cpu.edx + x86::reg32(512) /* 0x200 */) |= x86::reg8(x86::sreg8(2 /*0x2*/));
    // 004288e3  a18cfd5e00             -mov eax, dword ptr [0x5efd8c]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(6225292) /* 0x5efd8c */);
    // 004288e8  89148548fb5e00         -mov dword ptr [eax*4 + 0x5efb48], edx
    app->getMemory<x86::reg32>(x86::reg32(6224712) /* 0x5efb48 */ + cpu.eax * 4) = cpu.edx;
    // 004288ef  808a0002000010         -or byte ptr [edx + 0x200], 0x10
    app->getMemory<x86::reg8>(cpu.edx + x86::reg32(512) /* 0x200 */) |= x86::reg8(x86::sreg8(16 /*0x10*/));
    // 004288f6  a18cfd5e00             -mov eax, dword ptr [0x5efd8c]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(6225292) /* 0x5efd8c */);
    // 004288fb  40                     -inc eax
    (cpu.eax)++;
    // 004288fc  43                     -inc ebx
    (cpu.ebx)++;
    // 004288fd  a38cfd5e00             -mov dword ptr [0x5efd8c], eax
    app->getMemory<x86::reg32>(x86::reg32(6225292) /* 0x5efd8c */) = cpu.eax;
L_0x00428902:
    // 00428902  f6c108                 +test cl, 8
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.cl & 8 /*0x8*/));
    // 00428905  7430                   -je 0x428937
    if (cpu.flags.zf)
    {
        goto L_0x00428937;
    }
    // 00428907  f6c101                 +test cl, 1
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.cl & 1 /*0x1*/));
    // 0042890a  752b                   -jne 0x428937
    if (!cpu.flags.zf)
    {
        goto L_0x00428937;
    }
    // 0042890c  89149d08fb5e00         -mov dword ptr [ebx*4 + 0x5efb08], edx
    app->getMemory<x86::reg32>(x86::reg32(6224648) /* 0x5efb08 */ + cpu.ebx * 4) = cpu.edx;
    // 00428913  808a0002000002         -or byte ptr [edx + 0x200], 2
    app->getMemory<x86::reg8>(cpu.edx + x86::reg32(512) /* 0x200 */) |= x86::reg8(x86::sreg8(2 /*0x2*/));
    // 0042891a  a188fd5e00             -mov eax, dword ptr [0x5efd88]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(6225288) /* 0x5efd88 */);
    // 0042891f  89148588fa5e00         -mov dword ptr [eax*4 + 0x5efa88], edx
    app->getMemory<x86::reg32>(x86::reg32(6224520) /* 0x5efa88 */ + cpu.eax * 4) = cpu.edx;
    // 00428926  808a0002000020         -or byte ptr [edx + 0x200], 0x20
    app->getMemory<x86::reg8>(cpu.edx + x86::reg32(512) /* 0x200 */) |= x86::reg8(x86::sreg8(32 /*0x20*/));
    // 0042892d  8d4801                 -lea ecx, [eax + 1]
    cpu.ecx = x86::reg32(cpu.eax + x86::reg32(1) /* 0x1 */);
    // 00428930  43                     -inc ebx
    (cpu.ebx)++;
    // 00428931  890d88fd5e00           -mov dword ptr [0x5efd88], ecx
    app->getMemory<x86::reg32>(x86::reg32(6225288) /* 0x5efd88 */) = cpu.ecx;
L_0x00428937:
    // 00428937  8b8220020000           -mov eax, dword ptr [edx + 0x220]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(544) /* 0x220 */);
    // 0042893d  8b3530dc6f00           -mov esi, dword ptr [0x6fdc30]
    cpu.esi = app->getMemory<x86::reg32>(x86::reg32(7330864) /* 0x6fdc30 */);
    // 00428943  3b7014                 +cmp esi, dword ptr [eax + 0x14]
    {
        x86::reg32 tmp1 = cpu.esi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00428946  7510                   -jne 0x428958
    if (!cpu.flags.zf)
    {
        goto L_0x00428958;
    }
    // 00428948  833db8d36f0002         +cmp dword ptr [0x6fd3b8], 2
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(7328696) /* 0x6fd3b8 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(2 /*0x2*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0042894f  7507                   -jne 0x428958
    if (!cpu.flags.zf)
    {
        goto L_0x00428958;
    }
    // 00428951  808a0002000080         -or byte ptr [edx + 0x200], 0x80
    app->getMemory<x86::reg8>(cpu.edx + x86::reg32(512) /* 0x200 */) |= x86::reg8(x86::sreg8(128 /*0x80*/));
L_0x00428958:
    // 00428958  891d98fd5e00           -mov dword ptr [0x5efd98], ebx
    app->getMemory<x86::reg32>(x86::reg32(6225304) /* 0x5efd98 */) = cpu.ebx;
    // 0042895e  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0042895f  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00428960  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00428961  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00428962  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00428963  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00428964  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 0x8b 0xdb */
void Application::sub_428970(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00428970  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00428971  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00428972  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00428973  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00428975  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00428977  c780e400000000000000   -mov dword ptr [eax + 0xe4], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(228) /* 0xe4 */) = 0 /*0x0*/;
    // 00428981  c780e800000000000000   -mov dword ptr [eax + 0xe8], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(232) /* 0xe8 */) = 0 /*0x0*/;
    // 0042898b  c780ec00000000000000   -mov dword ptr [eax + 0xec], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(236) /* 0xec */) = 0 /*0x0*/;
    // 00428995  c780f804000000000000   -mov dword ptr [eax + 0x4f8], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(1272) /* 0x4f8 */) = 0 /*0x0*/;
    // 0042899f  c780fc04000000000000   -mov dword ptr [eax + 0x4fc], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(1276) /* 0x4fc */) = 0 /*0x0*/;
    // 004289a9  c7800005000000000000   -mov dword ptr [eax + 0x500], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(1280) /* 0x500 */) = 0 /*0x0*/;
    // 004289b3  c780e004000000000000   -mov dword ptr [eax + 0x4e0], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(1248) /* 0x4e0 */) = 0 /*0x0*/;
    // 004289bd  c780e404000000000000   -mov dword ptr [eax + 0x4e4], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(1252) /* 0x4e4 */) = 0 /*0x0*/;
    // 004289c7  c780e804000000000000   -mov dword ptr [eax + 0x4e8], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(1256) /* 0x4e8 */) = 0 /*0x0*/;
    // 004289d1  c7802405000000000000   -mov dword ptr [eax + 0x524], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(1316) /* 0x524 */) = 0 /*0x0*/;
    // 004289db  ffb0bc000000           -push dword ptr [eax + 0xbc]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(188) /* 0xbc */);
    cpu.esp -= 4;
    // 004289e1  8b401c                 -mov eax, dword ptr [eax + 0x1c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(28) /* 0x1c */);
    // 004289e4  ba20000000             -mov edx, 0x20
    cpu.edx = 32 /*0x20*/;
    // 004289e9  e8c258feff             -call 0x40e2b0
    cpu.esp -= 4;
    nfs3hp::aiplan::roadSliceIndex(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004289ee  898138060000           -mov dword ptr [ecx + 0x638], eax
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(1592) /* 0x638 */) = cpu.eax;
    // 004289f4  8d8168010000           -lea eax, [ecx + 0x168]
    cpu.eax = x86::reg32(cpu.ecx + x86::reg32(360) /* 0x168 */);
    // 004289fa  e80d7d0b00             -call 0x4e070c
    cpu.esp -= 4;
    nfs3hp::fillZero(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004289ff  66c781640100000100     -mov word ptr [ecx + 0x164], 1
    app->getMemory<x86::reg16>(cpu.ecx + x86::reg32(356) /* 0x164 */) = 1 /*0x1*/;
    // 00428a08  c7816801000000000000   -mov dword ptr [ecx + 0x168], 0
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(360) /* 0x168 */) = 0 /*0x0*/;
    // 00428a12  c7816c01000000000000   -mov dword ptr [ecx + 0x16c], 0
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(364) /* 0x16c */) = 0 /*0x0*/;
    // 00428a1c  c6818b00000000         -mov byte ptr [ecx + 0x8b], 0
    app->getMemory<x86::reg8>(cpu.ecx + x86::reg32(139) /* 0x8b */) = 0 /*0x0*/;
    // 00428a23  c7818401000000000000   -mov dword ptr [ecx + 0x184], 0
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(388) /* 0x184 */) = 0 /*0x0*/;
    // 00428a2d  c7819c09000000000000   -mov dword ptr [ecx + 0x99c], 0
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(2460) /* 0x99c */) = 0 /*0x0*/;
    // 00428a37  c781a009000000000000   -mov dword ptr [ecx + 0x9a0], 0
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(2464) /* 0x9a0 */) = 0 /*0x0*/;
    // 00428a41  c781d408000000000000   -mov dword ptr [ecx + 0x8d4], 0
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(2260) /* 0x8d4 */) = 0 /*0x0*/;
    // 00428a4b  c781d008000000000000   -mov dword ptr [ecx + 0x8d0], 0
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(2256) /* 0x8d0 */) = 0 /*0x0*/;
    // 00428a55  c7811c09000000000000   -mov dword ptr [ecx + 0x91c], 0
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(2332) /* 0x91c */) = 0 /*0x0*/;
    // 00428a5f  c7812009000000000000   -mov dword ptr [ecx + 0x920], 0
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(2336) /* 0x920 */) = 0 /*0x0*/;
    // 00428a69  c7812409000000000000   -mov dword ptr [ecx + 0x924], 0
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(2340) /* 0x924 */) = 0 /*0x0*/;
    // 00428a73  a1c8fd5e00             -mov eax, dword ptr [0x5efdc8]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(6225352) /* 0x5efdc8 */);
    // 00428a78  c7812809000000000000   -mov dword ptr [ecx + 0x928], 0
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(2344) /* 0x928 */) = 0 /*0x0*/;
    // 00428a82  898174010000           -mov dword ptr [ecx + 0x174], eax
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(372) /* 0x174 */) = cpu.eax;
    // 00428a88  8aa121060000           -mov ah, byte ptr [ecx + 0x621]
    cpu.ah = app->getMemory<x86::reg8>(cpu.ecx + x86::reg32(1569) /* 0x621 */);
    // 00428a8e  c7812c09000000000000   -mov dword ptr [ecx + 0x92c], 0
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(2348) /* 0x92c */) = 0 /*0x0*/;
    // 00428a98  80e4bf                 -and ah, 0xbf
    cpu.ah &= x86::reg8(x86::sreg8(191 /*0xbf*/));
    // 00428a9b  88a121060000           -mov byte ptr [ecx + 0x621], ah
    app->getMemory<x86::reg8>(cpu.ecx + x86::reg32(1569) /* 0x621 */) = cpu.ah;
    // 00428aa1  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00428aa3  c781c808000000000000   -mov dword ptr [ecx + 0x8c8], 0
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(2248) /* 0x8c8 */) = 0 /*0x0*/;
    // 00428aad  e8ed1c0800             -call 0x4aa79f
    cpu.esp -= 4;
    nfs3hp::handling::resetDriveState(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00428ab2  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00428ab4  e8f78afdff             -call 0x4015b0
    cpu.esp -= 4;
    nfs3hp::airace::stopIfCopNear(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00428ab9  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00428abb  e860410000             -call 0x42cc20
    cpu.esp -= 4;
    nfs3hp::raceload::countLaps(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00428ac0  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00428ac2  e849430000             -call 0x42ce10
    cpu.esp -= 4;
    nfs3hp::raceload::carRaceDistance(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00428ac7  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00428ac8  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00428ac9  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00428aca  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x40 0x00 0x8b 0xc9 */
void Application::sub_428ad0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00428ad0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00428ad1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00428ad2  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00428ad3  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00428ad4  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00428ad5  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00428ad7  81ecb0000000           -sub esp, 0xb0
    (cpu.esp) -= x86::reg32(x86::sreg32(176 /*0xb0*/));
    // 00428add  83ed76                 -sub ebp, 0x76
    (cpu.ebp) -= x86::reg32(x86::sreg32(118 /*0x76*/));
    // 00428ae0  89456e                 -mov dword ptr [ebp + 0x6e], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(110) /* 0x6e */) = cpu.eax;
    // 00428ae3  89d3                   -mov ebx, edx
    cpu.ebx = cpu.edx;
    // 00428ae5  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 00428ae7  ffb58e000000           -push dword ptr [ebp + 0x8e]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(142) /* 0x8e */);
    cpu.esp -= 4;
    // 00428aed  e8be57feff             -call 0x40e2b0
    cpu.esp -= 4;
    nfs3hp::aiplan::roadSliceIndex(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00428af2  89c7                   -mov edi, eax
    cpu.edi = cpu.eax;
    // 00428af4  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 00428af6  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 00428af8  e82357feff             -call 0x40e220
    cpu.esp -= 4;
    nfs3hp::aiplan::nodeHasLane(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00428afd  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00428aff  0f8448020000           -je 0x428d4d
    if (cpu.flags.zf)
    {
        goto L_0x00428d4d;
    }
    // 00428b05  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
L_0x00428b07:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00428b07  3b159cfd5e00           +cmp edx, dword ptr [0x5efd9c]
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(6225308) /* 0x5efd9c */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00428b0d  0f8d82000000           -jge 0x428b95
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00428b95;
    }
    // 00428b13  8b0495c8fa5e00         -mov eax, dword ptr [edx*4 + 0x5efac8]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(6224584) /* 0x5efac8 */ + cpu.edx * 4);
    // 00428b1a  8b701c                 -mov esi, dword ptr [eax + 0x1c]
    cpu.esi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(28) /* 0x1c */);
    // 00428b1d  8b8838060000           -mov ecx, dword ptr [eax + 0x638]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(1592) /* 0x638 */);
    // 00428b23  3b456e                 +cmp eax, dword ptr [ebp + 0x6e]
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(110) /* 0x6e */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00428b26  0f8463000000           -je 0x428b8f
    if (cpu.flags.zf)
    {
        goto L_0x00428b8f;
    }
    // 00428b2c  80b88800000000         +cmp byte ptr [eax + 0x88], 0
    {
        x86::reg8 tmp1 = app->getMemory<x86::reg8>(cpu.eax + x86::reg32(136) /* 0x88 */);
        x86::reg8 tmp2 = x86::reg8(x86::sreg8(0 /*0x0*/));
        x86::reg8 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 7);
        cpu.flags.of ^= 1 & (result >> 7);
        cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
        cpu.set_szp(result);
    }
    // 00428b33  0f8556000000           -jne 0x428b8f
    if (!cpu.flags.zf)
    {
        goto L_0x00428b8f;
    }
    // 00428b39  80b88900000000         +cmp byte ptr [eax + 0x89], 0
    {
        x86::reg8 tmp1 = app->getMemory<x86::reg8>(cpu.eax + x86::reg32(137) /* 0x89 */);
        x86::reg8 tmp2 = x86::reg8(x86::sreg8(0 /*0x0*/));
        x86::reg8 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 7);
        cpu.flags.of ^= 1 & (result >> 7);
        cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
        cpu.set_szp(result);
    }
    // 00428b40  744d                   -je 0x428b8f
    if (cpu.flags.zf)
    {
        goto L_0x00428b8f;
    }
    // 00428b42  39f9                   +cmp ecx, edi
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.edi));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00428b44  740c                   -je 0x428b52
    if (cpu.flags.zf)
    {
        goto L_0x00428b52;
    }
    // 00428b46  8d41ff                 -lea eax, [ecx - 1]
    cpu.eax = x86::reg32(cpu.ecx + x86::reg32(-1) /* -0x1 */);
    // 00428b49  39c7                   +cmp edi, eax
    {
        x86::reg32 tmp1 = cpu.edi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.eax));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00428b4b  7405                   -je 0x428b52
    if (cpu.flags.zf)
    {
        goto L_0x00428b52;
    }
    // 00428b4d  41                     -inc ecx
    (cpu.ecx)++;
    // 00428b4e  39f9                   +cmp ecx, edi
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.edi));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00428b50  753d                   -jne 0x428b8f
    if (!cpu.flags.zf)
    {
        goto L_0x00428b8f;
    }
L_0x00428b52:
    // 00428b52  39f3                   +cmp ebx, esi
    {
        x86::reg32 tmp1 = cpu.ebx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.esi));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00428b54  7507                   -jne 0x428b5d
    if (!cpu.flags.zf)
    {
        goto L_0x00428b5d;
    }
    // 00428b56  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
    // 00428b58  e9f0010000             -jmp 0x428d4d
    goto L_0x00428d4d;
L_0x00428b5d:
    // 00428b5d  8d46ff                 -lea eax, [esi - 1]
    cpu.eax = x86::reg32(cpu.esi + x86::reg32(-1) /* -0x1 */);
    // 00428b60  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00428b62  7d06                   -jge 0x428b6a
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00428b6a;
    }
    // 00428b64  030540d95d00           -add eax, dword ptr [0x5dd940]
    (cpu.eax) += x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(6150464) /* 0x5dd940 */)));
L_0x00428b6a:
    // 00428b6a  39c3                   +cmp ebx, eax
    {
        x86::reg32 tmp1 = cpu.ebx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.eax));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00428b6c  7507                   -jne 0x428b75
    if (!cpu.flags.zf)
    {
        goto L_0x00428b75;
    }
    // 00428b6e  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
    // 00428b70  e9d8010000             -jmp 0x428d4d
    goto L_0x00428d4d;
L_0x00428b75:
    // 00428b75  8d4601                 -lea eax, [esi + 1]
    cpu.eax = x86::reg32(cpu.esi + x86::reg32(1) /* 0x1 */);
    // 00428b78  8b3540d95d00           -mov esi, dword ptr [0x5dd940]
    cpu.esi = app->getMemory<x86::reg32>(x86::reg32(6150464) /* 0x5dd940 */);
    // 00428b7e  39f0                   +cmp eax, esi
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
    // 00428b80  7c02                   -jl 0x428b84
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x00428b84;
    }
    // 00428b82  29f0                   -sub eax, esi
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.esi));
L_0x00428b84:
    // 00428b84  39c3                   +cmp ebx, eax
    {
        x86::reg32 tmp1 = cpu.ebx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.eax));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00428b86  7507                   -jne 0x428b8f
    if (!cpu.flags.zf)
    {
        goto L_0x00428b8f;
    }
L_0x00428b88:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00428b88  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
    // 00428b8a  e9be010000             -jmp 0x428d4d
    goto L_0x00428d4d;
L_0x00428b8f:
    // 00428b8f  42                     +inc edx
    {
        x86::reg32& tmp = cpu.edx;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 00428b90  e972ffffff             -jmp 0x428b07
    goto L_0x00428b07;
L_0x00428b95:
    // 00428b95  8d04dd00000000         -lea eax, [ebx*8]
    cpu.eax = x86::reg32(cpu.ebx * 8);
    // 00428b9c  8d1403                 -lea edx, [ebx + eax]
    cpu.edx = x86::reg32(cpu.ebx + cpu.eax * 1);
    // 00428b9f  a148d95d00             -mov eax, dword ptr [0x5dd948]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(6150472) /* 0x5dd948 */);
    // 00428ba4  c1e202                 -shl edx, 2
    cpu.edx <<= 2 /*0x2*/ % 32;
    // 00428ba7  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 00428ba9  8b5015                 -mov edx, dword ptr [eax + 0x15]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(21) /* 0x15 */);
    // 00428bac  c1fa18                 -sar edx, 0x18
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (24 /*0x18*/ % 32));
    // 00428baf  c1e209                 -shl edx, 9
    cpu.edx <<= 9 /*0x9*/ % 32;
    // 00428bb2  895572                 -mov dword ptr [ebp + 0x72], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(114) /* 0x72 */) = cpu.edx;
    // 00428bb5  dd05a8715300           -fld qword ptr [0x5371a8]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<double>(x86::reg32(5468584) /* 0x5371a8 */));
    // 00428bbb  db4572                 -fild dword ptr [ebp + 0x72]
    x86::Float fpu2 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(114) /* 0x72 */)));
    // 00428bbe  d8c9                   -fmul st(1)
    x86::Float fpu3 = cpu.fpu.mul(fpu2, x86::Float(fpu1));
    // 00428bc0  db00                   -fild dword ptr [eax]
    x86::Float fpu4 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.eax)));
    // 00428bc2  db4004                 -fild dword ptr [eax + 4]
    x86::Float fpu5 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */)));
    // 00428bc5  db4008                 -fild dword ptr [eax + 8]
    x86::Float fpu6 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */)));
    // 00428bc8  d9cb                   -fxch st(3)
    
    // 00428bca  d95d4a                 -fstp dword ptr [ebp + 0x4a]
    app->getMemory<float>(cpu.ebp + x86::reg32(74) /* 0x4a */) = float(fpu3);
    // 00428bcd  8b5016                 -mov edx, dword ptr [eax + 0x16]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(22) /* 0x16 */);
    // 00428bd0  c1fa18                 -sar edx, 0x18
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (24 /*0x18*/ % 32));
    // 00428bd3  c1e209                 -shl edx, 9
    cpu.edx <<= 9 /*0x9*/ % 32;
    // 00428bd6  895572                 -mov dword ptr [ebp + 0x72], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(114) /* 0x72 */) = cpu.edx;
    // 00428bd9  db4572                 -fild dword ptr [ebp + 0x72]
    x86::Float fpu7 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(114) /* 0x72 */)));
    // 00428bdc  d8cc                   -fmul st(4)
    x86::Float fpu8 = cpu.fpu.mul(fpu7, x86::Float(fpu1));
    // 00428bde  d95d4e                 -fstp dword ptr [ebp + 0x4e]
    app->getMemory<float>(cpu.ebp + x86::reg32(78) /* 0x4e */) = float(fpu8);
    // 00428be1  8b5017                 -mov edx, dword ptr [eax + 0x17]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(23) /* 0x17 */);
    // 00428be4  c1fa18                 -sar edx, 0x18
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (24 /*0x18*/ % 32));
    // 00428be7  c1e209                 -shl edx, 9
    cpu.edx <<= 9 /*0x9*/ % 32;
    // 00428bea  895572                 -mov dword ptr [ebp + 0x72], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(114) /* 0x72 */) = cpu.edx;
    // 00428bed  db4572                 -fild dword ptr [ebp + 0x72]
    x86::Float fpu9 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(114) /* 0x72 */)));
    // 00428bf0  d8cc                   -fmul st(4)
    x86::Float fpu10 = cpu.fpu.mul(fpu9, x86::Float(fpu1));
    // 00428bf2  d9ca                   -fxch st(2)
    
    // 00428bf4  d8cc                   -fmul st(4)
    x86::Float fpu11 = cpu.fpu.mul(fpu4, x86::Float(fpu1));
    // 00428bf6  d9ca                   -fxch st(2)
    
    // 00428bf8  d95d52                 -fstp dword ptr [ebp + 0x52]
    app->getMemory<float>(cpu.ebp + x86::reg32(82) /* 0x52 */) = float(fpu10);
    // 00428bfb  8b5011                 -mov edx, dword ptr [eax + 0x11]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(17) /* 0x11 */);
    // 00428bfe  c1fa18                 -sar edx, 0x18
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (24 /*0x18*/ % 32));
    // 00428c01  c1e209                 -shl edx, 9
    cpu.edx <<= 9 /*0x9*/ % 32;
    // 00428c04  895572                 -mov dword ptr [ebp + 0x72], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(114) /* 0x72 */) = cpu.edx;
    // 00428c07  db4572                 -fild dword ptr [ebp + 0x72]
    x86::Float fpu12 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(114) /* 0x72 */)));
    // 00428c0a  d8cc                   -fmul st(4)
    x86::Float fpu13 = cpu.fpu.mul(fpu12, x86::Float(fpu1));
    // 00428c0c  d9c9                   -fxch st(1)
    
    // 00428c0e  d8cc                   -fmul st(4)
    x86::Float fpu14 = cpu.fpu.mul(fpu5, x86::Float(fpu1));
    // 00428c10  d9c9                   -fxch st(1)
    
    // 00428c12  d95d62                 -fstp dword ptr [ebp + 0x62]
    app->getMemory<float>(cpu.ebp + x86::reg32(98) /* 0x62 */) = float(fpu13);
    // 00428c15  8b5012                 -mov edx, dword ptr [eax + 0x12]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(18) /* 0x12 */);
    // 00428c18  c1fa18                 -sar edx, 0x18
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (24 /*0x18*/ % 32));
    // 00428c1b  c1e209                 -shl edx, 9
    cpu.edx <<= 9 /*0x9*/ % 32;
    // 00428c1e  895572                 -mov dword ptr [ebp + 0x72], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(114) /* 0x72 */) = cpu.edx;
    // 00428c21  db4572                 -fild dword ptr [ebp + 0x72]
    x86::Float fpu15 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(114) /* 0x72 */)));
    // 00428c24  d8cc                   -fmul st(4)
    x86::Float fpu16 = cpu.fpu.mul(fpu15, x86::Float(fpu1));
    // 00428c26  d9cb                   -fxch st(3)
    
    // 00428c28  d8cc                   -fmul st(4)
    x86::Float fpu17 = cpu.fpu.mul(fpu6, x86::Float(fpu1));
    // 00428c2a  d9cb                   -fxch st(3)
    
    // 00428c2c  d95d66                 -fstp dword ptr [ebp + 0x66]
    app->getMemory<float>(cpu.ebp + x86::reg32(102) /* 0x66 */) = float(fpu16);
    // 00428c2f  8b4013                 -mov eax, dword ptr [eax + 0x13]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(19) /* 0x13 */);
    // 00428c32  c1f818                 -sar eax, 0x18
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (24 /*0x18*/ % 32));
    // 00428c35  c1e009                 -shl eax, 9
    cpu.eax <<= 9 /*0x9*/ % 32;
    // 00428c38  894572                 -mov dword ptr [ebp + 0x72], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(114) /* 0x72 */) = cpu.eax;
    // 00428c3b  db4572                 -fild dword ptr [ebp + 0x72]
    x86::Float fpu18 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(114) /* 0x72 */)));
    // 00428c3e  decc                   -fmulp st(4)
    x86::Float fpu19 = cpu.fpu.mul(fpu1, fpu18);
    // 00428c40  d9c9                   -fxch st(1)
    
    // 00428c42  d95d56                 -fstp dword ptr [ebp + 0x56]
    app->getMemory<float>(cpu.ebp + x86::reg32(86) /* 0x56 */) = float(fpu11);
    // 00428c45  8d454a                 -lea eax, [ebp + 0x4a]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(74) /* 0x4a */);
    // 00428c48  d95d5a                 -fstp dword ptr [ebp + 0x5a]
    app->getMemory<float>(cpu.ebp + x86::reg32(90) /* 0x5a */) = float(fpu14);
    // 00428c4b  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00428c4c  d95d5e                 -fstp dword ptr [ebp + 0x5e]
    app->getMemory<float>(cpu.ebp + x86::reg32(94) /* 0x5e */) = float(fpu17);
    // 00428c4f  8d554a                 -lea edx, [ebp + 0x4a]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(74) /* 0x4a */);
    // 00428c52  ffb58e000000           -push dword ptr [ebp + 0x8e]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(142) /* 0x8e */);
    cpu.esp -= 4;
    // 00428c58  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 00428c5d  d95d6a                 -fstp dword ptr [ebp + 0x6a]
    app->getMemory<float>(cpu.ebp + x86::reg32(106) /* 0x6a */) = float(fpu19);
    }
    // 00428c60  e8eb730b00             -call 0x4e0050
    cpu.esp -= 4;
    nfs3hp::vertices::scaleVectors(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00428c65  8d4562                 -lea eax, [ebp + 0x62]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(98) /* 0x62 */);
    // 00428c68  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00428c69  8d5562                 -lea edx, [ebp + 0x62]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(98) /* 0x62 */);
    // 00428c6c  ffb596000000           -push dword ptr [ebp + 0x96]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(150) /* 0x96 */);
    cpu.esp -= 4;
    // 00428c72  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 00428c77  8d75c6                 -lea esi, [ebp - 0x3a]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(-58) /* -0x3a */);
    // 00428c7a  e8d1730b00             -call 0x4e0050
    cpu.esp -= 4;
    nfs3hp::vertices::scaleVectors(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00428c7f  d9454a                 -fld dword ptr [ebp + 0x4a]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu20 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(74) /* 0x4a */));
    // 00428c82  d9454e                 -fld dword ptr [ebp + 0x4e]
    x86::Float fpu21 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(78) /* 0x4e */));
    // 00428c85  d94552                 -fld dword ptr [ebp + 0x52]
    x86::Float fpu22 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(82) /* 0x52 */));
    // 00428c88  ba01000000             -mov edx, 1
    cpu.edx = 1 /*0x1*/;
    // 00428c8d  8d453e                 -lea eax, [ebp + 0x3e]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(62) /* 0x3e */);
    // 00428c90  d9ca                   -fxch st(2)
    
    // 00428c92  d84562                 -fadd dword ptr [ebp + 0x62]
    x86::Float fpu23 = cpu.fpu.add(fpu20, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(98) /* 0x62 */)));
    // 00428c95  d9c9                   -fxch st(1)
    
    // 00428c97  d84566                 -fadd dword ptr [ebp + 0x66]
    x86::Float fpu24 = cpu.fpu.add(fpu21, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(102) /* 0x66 */)));
    // 00428c9a  d9ca                   -fxch st(2)
    
    // 00428c9c  d8456a                 -fadd dword ptr [ebp + 0x6a]
    x86::Float fpu25 = cpu.fpu.add(fpu22, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(106) /* 0x6a */)));
    // 00428c9f  d9c9                   -fxch st(1)
    
    // 00428ca1  d84556                 -fadd dword ptr [ebp + 0x56]
    x86::Float fpu26 = cpu.fpu.add(fpu23, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(86) /* 0x56 */)));
    // 00428ca4  d9ca                   -fxch st(2)
    
    // 00428ca6  d8455a                 -fadd dword ptr [ebp + 0x5a]
    x86::Float fpu27 = cpu.fpu.add(fpu24, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(90) /* 0x5a */)));
    // 00428ca9  d9c9                   -fxch st(1)
    
    // 00428cab  d8455e                 -fadd dword ptr [ebp + 0x5e]
    x86::Float fpu28 = cpu.fpu.add(fpu25, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(94) /* 0x5e */)));
    // 00428cae  d9ca                   -fxch st(2)
    
    // 00428cb0  d95d3e                 -fstp dword ptr [ebp + 0x3e]
    app->getMemory<float>(cpu.ebp + x86::reg32(62) /* 0x3e */) = float(fpu26);
    // 00428cb3  d95d42                 -fstp dword ptr [ebp + 0x42]
    app->getMemory<float>(cpu.ebp + x86::reg32(66) /* 0x42 */) = float(fpu27);
    // 00428cb6  d95d46                 -fstp dword ptr [ebp + 0x46]
    app->getMemory<float>(cpu.ebp + x86::reg32(70) /* 0x46 */) = float(fpu28);
    }
    // 00428cb9  e8e278ffff             -call 0x4205a0
    cpu.esp -= 4;
    nfs3hp::trackdata::snapToTrack(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00428cbe  837dda00               +cmp dword ptr [ebp - 0x26], 0
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
    // 00428cc2  0f84c0feffff           -je 0x428b88
    if (cpu.flags.zf)
    {
        goto L_0x00428b88;
    }
    // 00428cc8  837dde00               +cmp dword ptr [ebp - 0x22], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-34) /* -0x22 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00428ccc  750d                   -jne 0x428cdb
    if (!cpu.flags.zf)
    {
        goto L_0x00428cdb;
    }
    // 00428cce  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00428cd0  8d6576                 -lea esp, [ebp + 0x76]
    cpu.esp = x86::reg32(cpu.ebp + x86::reg32(118) /* 0x76 */);
    // 00428cd3  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00428cd4  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00428cd5  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00428cd6  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00428cd7  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00428cd8  c20c00                 -ret 0xc
    cpu.esp += 4+12 /*0xc*/;
    return;
L_0x00428cdb:
    // 00428cdb  ba01000000             -mov edx, 1
    cpu.edx = 1 /*0x1*/;
    // 00428ce0  8d45c6                 -lea eax, [ebp - 0x3a]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-58) /* -0x3a */);
    // 00428ce3  e8f87affff             -call 0x4207e0
    cpu.esp -= 4;
    nfs3hp::trackdata::positionSurface(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00428ce8  a840                   +test al, 0x40
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.al & 64 /*0x40*/));
    // 00428cea  754f                   -jne 0x428d3b
    if (!cpu.flags.zf)
    {
        goto L_0x00428d3b;
    }
    // 00428cec  a880                   +test al, 0x80
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.al & 128 /*0x80*/));
    // 00428cee  754b                   -jne 0x428d3b
    if (!cpu.flags.zf)
    {
        goto L_0x00428d3b;
    }
    // 00428cf0  a83f                   +test al, 0x3f
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.al & 63 /*0x3f*/));
    // 00428cf2  7447                   -je 0x428d3b
    if (cpu.flags.zf)
    {
        goto L_0x00428d3b;
    }
    // 00428cf4  83e03f                 -and eax, 0x3f
    cpu.eax &= x86::reg32(x86::sreg32(63 /*0x3f*/));
    // 00428cf7  83f80e                 +cmp eax, 0xe
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
    // 00428cfa  743f                   -je 0x428d3b
    if (cpu.flags.zf)
    {
        goto L_0x00428d3b;
    }
    // 00428cfc  837dda00               +cmp dword ptr [ebp - 0x26], 0
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
    // 00428d00  740c                   -je 0x428d0e
    if (cpu.flags.zf)
    {
        goto L_0x00428d0e;
    }
    // 00428d02  8b45e2                 -mov eax, dword ptr [ebp - 0x1e]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-30) /* -0x1e */);
    // 00428d05  8b00                   -mov eax, dword ptr [eax]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax);
    // 00428d07  c1f810                 -sar eax, 0x10
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (16 /*0x10*/ % 32));
    // 00428d0a  01c0                   +add eax, eax
    {
        x86::reg32& tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.eax));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 00428d0c  eb1c                   -jmp 0x428d2a
    goto L_0x00428d2a;
L_0x00428d0e:
    // 00428d0e  8b55d6                 -mov edx, dword ptr [ebp - 0x2a]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-42) /* -0x2a */);
    // 00428d11  8d04d500000000         -lea eax, [edx*8]
    cpu.eax = x86::reg32(cpu.edx * 8);
    // 00428d18  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 00428d1a  8b1548d95d00           -mov edx, dword ptr [0x5dd948]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(6150472) /* 0x5dd948 */);
    // 00428d20  8b44820e               -mov eax, dword ptr [edx + eax*4 + 0xe]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(14) /* 0xe */ + cpu.eax * 4);
    // 00428d24  c1f818                 -sar eax, 0x18
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (24 /*0x18*/ % 32));
    // 00428d27  c1e009                 +shl eax, 9
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
L_0x00428d2a:
    // 00428d2a  894572                 -mov dword ptr [ebp + 0x72], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(114) /* 0x72 */) = cpu.eax;
    // 00428d2d  db4572                 +fild dword ptr [ebp + 0x72]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu29 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(114) /* 0x72 */)));
    // 00428d30  dc1db0715300           +fcomp qword ptr [0x5371b0]
    cpu.fpu.compare(fpu29, x86::Float(app->getMemory<double>(x86::reg32(5468592) /* 0x5371b0 */)));
    // 00428d36  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 00428d38  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 00428d39  730d                   -jae 0x428d48
    if (!cpu.flags.cf)
    {
        goto L_0x00428d48;
    }
L_0x00428d3b:
    // 00428d3b  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00428d3d  8d6576                 -lea esp, [ebp + 0x76]
    cpu.esp = x86::reg32(cpu.ebp + x86::reg32(118) /* 0x76 */);
    // 00428d40  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00428d41  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00428d42  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00428d43  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00428d44  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00428d45  c20c00                 -ret 0xc
    cpu.esp += 4+12 /*0xc*/;
    return;
L_0x00428d48:
    // 00428d48  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
L_0x00428d4d:
    // 00428d4d  8d6576                 -lea esp, [ebp + 0x76]
    cpu.esp = x86::reg32(cpu.ebp + x86::reg32(118) /* 0x76 */);
    // 00428d50  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00428d51  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00428d52  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00428d53  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00428d54  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00428d55  c20c00                 -ret 0xc
    cpu.esp += 4+12 /*0xc*/;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8b 0xd2 */
void Application::sub_428d60(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00428d60  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00428d61  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00428d62  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00428d63  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00428d64  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00428d65  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00428d67  83ec30                 -sub esp, 0x30
    (cpu.esp) -= x86::reg32(x86::sreg32(48 /*0x30*/));
    // 00428d6a  8945f4                 -mov dword ptr [ebp - 0xc], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.eax;
    // 00428d6d  8955f0                 -mov dword ptr [ebp - 0x10], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = cpu.edx;
    // 00428d70  8d7ddc                 -lea edi, [ebp - 0x24]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(-36) /* -0x24 */);
    // 00428d73  be60844200             -mov esi, 0x428460
    cpu.esi = 4359264 /*0x428460*/;
    // 00428d78  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 00428d7a  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00428d7b  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00428d7c  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00428d7d  8955f8                 -mov dword ptr [ebp - 8], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.edx;
    // 00428d80  8b55e4                 -mov edx, dword ptr [ebp - 0x1c]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-28) /* -0x1c */);
    // 00428d83  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00428d84  8b4de0                 -mov ecx, dword ptr [ebp - 0x20]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-32) /* -0x20 */);
    // 00428d87  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00428d88  8b5ddc                 -mov ebx, dword ptr [ebp - 0x24]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-36) /* -0x24 */);
    // 00428d8b  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 00428d8d  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00428d8e  8b45f4                 -mov eax, dword ptr [ebp - 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 00428d91  be0a000000             -mov esi, 0xa
    cpu.esi = 10 /*0xa*/;
    // 00428d96  e835fdffff             -call 0x428ad0
    cpu.esp -= 4;
    sub_428ad0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00428d9b  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00428d9d  0f85a0010000           -jne 0x428f43
    if (!cpu.flags.zf)
    {
        goto L_0x00428f43;
    }
L_0x00428da3:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00428da3  4e                     -dec esi
    (cpu.esi)--;
    // 00428da4  83feff                 +cmp esi, -1
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
    // 00428da7  0f8496010000           -je 0x428f43
    if (cpu.flags.zf)
    {
        goto L_0x00428f43;
    }
    // 00428dad  8b55f8                 -mov edx, dword ptr [ebp - 8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 00428db0  8d04d500000000         -lea eax, [edx*8]
    cpu.eax = x86::reg32(cpu.edx * 8);
    // 00428db7  01c2                   -add edx, eax
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.eax));
    // 00428db9  a148d95d00             -mov eax, dword ptr [0x5dd948]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(6150472) /* 0x5dd948 */);
    // 00428dbe  c1e202                 -shl edx, 2
    cpu.edx <<= 2 /*0x2*/ % 32;
    // 00428dc1  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 00428dc3  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00428dc5  8a5013                 -mov dl, byte ptr [eax + 0x13]
    cpu.dl = app->getMemory<x86::reg8>(cpu.eax + x86::reg32(19) /* 0x13 */);
    // 00428dc8  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
    // 00428dca  89d7                   -mov edi, edx
    cpu.edi = cpu.edx;
    // 00428dcc  80e20f                 -and dl, 0xf
    cpu.dl &= x86::reg8(x86::sreg8(15 /*0xf*/));
    // 00428dcf  88d3                   -mov bl, dl
    cpu.bl = cpu.dl;
    // 00428dd1  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00428dd3  8a5017                 -mov dl, byte ptr [eax + 0x17]
    cpu.dl = app->getMemory<x86::reg8>(cpu.eax + x86::reg32(23) /* 0x17 */);
    // 00428dd6  c1e20f                 -shl edx, 0xf
    cpu.edx <<= 15 /*0xf*/ % 32;
    // 00428dd9  8955fc                 -mov dword ptr [ebp - 4], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.edx;
    // 00428ddc  c1ff04                 -sar edi, 4
    cpu.edi = x86::reg32(x86::sreg32(cpu.edi) >> (4 /*0x4*/ % 32));
    // 00428ddf  dd05b8715300           -fld qword ptr [0x5371b8]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<double>(x86::reg32(5468600) /* 0x5371b8 */));
    // 00428de5  db45fc                 -fild dword ptr [ebp - 4]
    x86::Float fpu2 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 00428de8  d8c9                   -fmul st(1)
    x86::Float fpu3 = cpu.fpu.mul(fpu2, x86::Float(fpu1));
    // 00428dea  83e70f                 -and edi, 0xf
    cpu.edi &= x86::reg32(x86::sreg32(15 /*0xf*/));
    // 00428ded  8a401b                 -mov al, byte ptr [eax + 0x1b]
    cpu.al = app->getMemory<x86::reg8>(cpu.eax + x86::reg32(27) /* 0x1b */);
    // 00428df0  d95dec                 -fstp dword ptr [ebp - 0x14]
    app->getMemory<float>(cpu.ebp + x86::reg32(-20) /* -0x14 */) = float(fpu3);
    // 00428df3  25ff000000             -and eax, 0xff
    cpu.eax &= x86::reg32(x86::sreg32(255 /*0xff*/));
    // 00428df8  c1e00f                 -shl eax, 0xf
    cpu.eax <<= 15 /*0xf*/ % 32;
    // 00428dfb  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 00428dfe  db45fc                 -fild dword ptr [ebp - 4]
    x86::Float fpu4 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 00428e01  dec9                   -fmulp st(1)
    x86::Float fpu5 = cpu.fpu.mul(fpu1, fpu4);
    // 00428e03  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 00428e05  d95de8                 -fstp dword ptr [ebp - 0x18]
    app->getMemory<float>(cpu.ebp + x86::reg32(-24) /* -0x18 */) = float(fpu5);
    // 00428e08  39df                   +cmp edi, ebx
    {
        x86::reg32 tmp1 = cpu.edi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ebx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    }
    // 00428e0a  7e04                   -jle 0x428e10
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00428e10;
    }
    // 00428e0c  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 00428e0e  eb02                   -jmp 0x428e12
    goto L_0x00428e12;
L_0x00428e10:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00428e10  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
L_0x00428e12:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00428e12  39c1                   +cmp ecx, eax
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
    // 00428e14  0f8ded000000           -jge 0x428f07
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00428f07;
    }
    // 00428e1a  39d9                   +cmp ecx, ebx
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ebx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00428e1c  7f6a                   -jg 0x428e88
    if (!cpu.flags.zf && (cpu.flags.sf == cpu.flags.of))
    {
        goto L_0x00428e88;
    }
    // 00428e1e  894dfc                 -mov dword ptr [ebp - 4], ecx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.ecx;
    // 00428e21  d945e8                 -fld dword ptr [ebp - 0x18]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu6 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-24) /* -0x18 */));
    // 00428e24  db45fc                 -fild dword ptr [ebp - 4]
    x86::Float fpu7 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 00428e27  d8c9                   -fmul st(1)
    x86::Float fpu8 = cpu.fpu.mul(fpu7, x86::Float(fpu6));
    // 00428e29  d9c9                   -fxch st(1)
    
    // 00428e2b  dc0dc0715300           -fmul qword ptr [0x5371c0]
    x86::Float fpu9 = cpu.fpu.mul(fpu6, x86::Float(app->getMemory<double>(x86::reg32(5468608) /* 0x5371c0 */)));
    // 00428e31  8b45e4                 -mov eax, dword ptr [ebp - 0x1c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-28) /* -0x1c */);
    // 00428e34  8b55e0                 -mov edx, dword ptr [ebp - 0x20]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-32) /* -0x20 */);
    // 00428e37  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00428e38  dec1                   -faddp st(1)
    x86::Float fpu10 = cpu.fpu.add(fpu8, fpu9);
    // 00428e3a  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00428e3b  d95ddc                 -fstp dword ptr [ebp - 0x24]
    app->getMemory<float>(cpu.ebp + x86::reg32(-36) /* -0x24 */) = float(fpu10);
    // 00428e3e  8b45dc                 -mov eax, dword ptr [ebp - 0x24]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-36) /* -0x24 */);
    // 00428e41  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00428e42  8b55f8                 -mov edx, dword ptr [ebp - 8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 00428e45  8b45f4                 -mov eax, dword ptr [ebp - 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    }
    // 00428e48  e883fcffff             -call 0x428ad0
    cpu.esp -= 4;
    sub_428ad0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00428e4d  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00428e4f  7437                   -je 0x428e88
    if (cpu.flags.zf)
    {
        goto L_0x00428e88;
    }
    // 00428e51  d945dc                 -fld dword ptr [ebp - 0x24]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu11 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-36) /* -0x24 */));
    // 00428e54  dc0dc8715300           -fmul qword ptr [0x5371c8]
    x86::Float fpu12 = cpu.fpu.mul(fpu11, x86::Float(app->getMemory<double>(x86::reg32(5468616) /* 0x5371c8 */)));
    // 00428e5a  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 00428e5d  db1c24                 -fistp dword ptr [esp]
    app->getMemory<x86::reg32>(cpu.esp) = x86::reg32(cpu.fpu.toInteger<x86::sreg32>(fpu12));
    // 00428e60  58                     -pop eax
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00428e61  d945e0                 -fld dword ptr [ebp - 0x20]
    x86::Float fpu13 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-32) /* -0x20 */));
    // 00428e64  dc0dc8715300           -fmul qword ptr [0x5371c8]
    x86::Float fpu14 = cpu.fpu.mul(fpu13, x86::Float(app->getMemory<double>(x86::reg32(5468616) /* 0x5371c8 */)));
    // 00428e6a  8945d0                 -mov dword ptr [ebp - 0x30], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-48) /* -0x30 */) = cpu.eax;
    // 00428e6d  83ec04                 +sub esp, 4
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
    // 00428e70  db1c24                 +fistp dword ptr [esp]
    app->getMemory<x86::reg32>(cpu.esp) = x86::reg32(cpu.fpu.toInteger<x86::sreg32>(fpu14));
    // 00428e73  58                     -pop eax
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00428e74  d945e4                 +fld dword ptr [ebp - 0x1c]
    x86::Float fpu15 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-28) /* -0x1c */));
    // 00428e77  dc0dc8715300           +fmul qword ptr [0x5371c8]
    x86::Float fpu16 = cpu.fpu.mul(fpu15, x86::Float(app->getMemory<double>(x86::reg32(5468616) /* 0x5371c8 */)));
    // 00428e7d  8d5dd0                 -lea ebx, [ebp - 0x30]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-48) /* -0x30 */);
    // 00428e80  8b55f8                 -mov edx, dword ptr [ebp - 8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    cpu.fpu.count += 1;
    cpu.fpu.st(0) = fpu16;
    }
    // 00428e83  e9d8000000             -jmp 0x428f60
    goto L_0x00428f60;
L_0x00428e88:
    // 00428e88  39f9                   +cmp ecx, edi
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.edi));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00428e8a  7f6b                   -jg 0x428ef7
    if (!cpu.flags.zf && (cpu.flags.sf == cpu.flags.of))
    {
        goto L_0x00428ef7;
    }
    // 00428e8c  894dfc                 -mov dword ptr [ebp - 4], ecx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.ecx;
    // 00428e8f  db45fc                 -fild dword ptr [ebp - 4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu17 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 00428e92  d9e0                   -fchs 
    x86::Float fpu18 = -fpu17;
    // 00428e94  d945ec                 -fld dword ptr [ebp - 0x14]
    x86::Float fpu19 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-20) /* -0x14 */));
    // 00428e97  d9c9                   -fxch st(1)
    
    // 00428e99  d8c9                   -fmul st(1)
    x86::Float fpu20 = cpu.fpu.mul(fpu18, x86::Float(fpu19));
    // 00428e9b  d9c9                   -fxch st(1)
    
    // 00428e9d  dc0dc0715300           -fmul qword ptr [0x5371c0]
    x86::Float fpu21 = cpu.fpu.mul(fpu19, x86::Float(app->getMemory<double>(x86::reg32(5468608) /* 0x5371c0 */)));
    // 00428ea3  8b55e4                 -mov edx, dword ptr [ebp - 0x1c]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-28) /* -0x1c */);
    // 00428ea6  8b45e0                 -mov eax, dword ptr [ebp - 0x20]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-32) /* -0x20 */);
    // 00428ea9  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00428eaa  dee9                   -fsubp st(1)
    x86::Float fpu22 = cpu.fpu.sub(fpu20, fpu21);
    // 00428eac  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00428ead  d95ddc                 -fstp dword ptr [ebp - 0x24]
    app->getMemory<float>(cpu.ebp + x86::reg32(-36) /* -0x24 */) = float(fpu22);
    // 00428eb0  8b55dc                 -mov edx, dword ptr [ebp - 0x24]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-36) /* -0x24 */);
    // 00428eb3  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00428eb4  8b45f4                 -mov eax, dword ptr [ebp - 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 00428eb7  8b55f8                 -mov edx, dword ptr [ebp - 8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    }
    // 00428eba  e811fcffff             -call 0x428ad0
    cpu.esp -= 4;
    sub_428ad0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00428ebf  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00428ec1  7434                   -je 0x428ef7
    if (cpu.flags.zf)
    {
        goto L_0x00428ef7;
    }
    // 00428ec3  d945dc                 -fld dword ptr [ebp - 0x24]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu23 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-36) /* -0x24 */));
    // 00428ec6  dc0dc8715300           -fmul qword ptr [0x5371c8]
    x86::Float fpu24 = cpu.fpu.mul(fpu23, x86::Float(app->getMemory<double>(x86::reg32(5468616) /* 0x5371c8 */)));
    // 00428ecc  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 00428ecf  db1c24                 -fistp dword ptr [esp]
    app->getMemory<x86::reg32>(cpu.esp) = x86::reg32(cpu.fpu.toInteger<x86::sreg32>(fpu24));
    // 00428ed2  58                     -pop eax
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00428ed3  d945e0                 -fld dword ptr [ebp - 0x20]
    x86::Float fpu25 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-32) /* -0x20 */));
    // 00428ed6  dc0dc8715300           -fmul qword ptr [0x5371c8]
    x86::Float fpu26 = cpu.fpu.mul(fpu25, x86::Float(app->getMemory<double>(x86::reg32(5468616) /* 0x5371c8 */)));
    // 00428edc  8945d0                 -mov dword ptr [ebp - 0x30], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-48) /* -0x30 */) = cpu.eax;
    // 00428edf  83ec04                 +sub esp, 4
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
    // 00428ee2  db1c24                 +fistp dword ptr [esp]
    app->getMemory<x86::reg32>(cpu.esp) = x86::reg32(cpu.fpu.toInteger<x86::sreg32>(fpu26));
    // 00428ee5  58                     -pop eax
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00428ee6  d945e4                 +fld dword ptr [ebp - 0x1c]
    x86::Float fpu27 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-28) /* -0x1c */));
    // 00428ee9  dc0dc8715300           +fmul qword ptr [0x5371c8]
    x86::Float fpu28 = cpu.fpu.mul(fpu27, x86::Float(app->getMemory<double>(x86::reg32(5468616) /* 0x5371c8 */)));
    // 00428eef  8d5dd0                 -lea ebx, [ebp - 0x30]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-48) /* -0x30 */);
    // 00428ef2  8b55f8                 -mov edx, dword ptr [ebp - 8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    cpu.fpu.count += 1;
    cpu.fpu.st(0) = fpu28;
    }
    // 00428ef5  eb69                   -jmp 0x428f60
    goto L_0x00428f60;
L_0x00428ef7:
    // 00428ef7  41                     -inc ecx
    (cpu.ecx)++;
    // 00428ef8  39df                   +cmp edi, ebx
    {
        x86::reg32 tmp1 = cpu.edi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ebx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00428efa  0f8e10ffffff           -jle 0x428e10
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00428e10;
    }
    // 00428f00  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 00428f02  e90bffffff             -jmp 0x428e12
    goto L_0x00428e12;
L_0x00428f07:
    // 00428f07  833dc0d46f0000         +cmp dword ptr [0x6fd4c0], 0
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
    // 00428f0e  7410                   -je 0x428f20
    if (cpu.flags.zf)
    {
        goto L_0x00428f20;
    }
    // 00428f10  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 00428f13  48                     -dec eax
    (cpu.eax)--;
    // 00428f14  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00428f16  7d18                   -jge 0x428f30
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00428f30;
    }
    // 00428f18  030540d95d00           +add eax, dword ptr [0x5dd940]
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
    // 00428f1e  eb10                   -jmp 0x428f30
    goto L_0x00428f30;
L_0x00428f20:
    // 00428f20  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 00428f23  8b3d40d95d00           -mov edi, dword ptr [0x5dd940]
    cpu.edi = app->getMemory<x86::reg32>(x86::reg32(6150464) /* 0x5dd940 */);
    // 00428f29  40                     -inc eax
    (cpu.eax)++;
    // 00428f2a  39f8                   +cmp eax, edi
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
    // 00428f2c  7c02                   -jl 0x428f30
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x00428f30;
    }
    // 00428f2e  29f8                   -sub eax, edi
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edi));
L_0x00428f30:
    // 00428f30  8945f8                 -mov dword ptr [ebp - 8], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.eax;
    // 00428f33  31c9                   +xor ecx, ecx
    cpu.clear_co();
    cpu.set_szp((cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx))));
    // 00428f35  894de0                 -mov dword ptr [ebp - 0x20], ecx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-32) /* -0x20 */) = cpu.ecx;
    // 00428f38  894de4                 -mov dword ptr [ebp - 0x1c], ecx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-28) /* -0x1c */) = cpu.ecx;
    // 00428f3b  894ddc                 -mov dword ptr [ebp - 0x24], ecx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-36) /* -0x24 */) = cpu.ecx;
    // 00428f3e  e960feffff             -jmp 0x428da3
    goto L_0x00428da3;
L_0x00428f43:
    // 00428f43  d9ee                   -fldz 
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu29 = 0.0;
    // 00428f45  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 00428f48  db1c24                 -fistp dword ptr [esp]
    app->getMemory<x86::reg32>(cpu.esp) = x86::reg32(cpu.fpu.toInteger<x86::sreg32>(fpu29));
    // 00428f4b  58                     -pop eax
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00428f4c  d9ee                   -fldz 
    x86::Float fpu30 = 0.0;
    // 00428f4e  8d5dd0                 -lea ebx, [ebp - 0x30]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-48) /* -0x30 */);
    // 00428f51  8b55f0                 -mov edx, dword ptr [ebp - 0x10]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 00428f54  8945d0                 -mov dword ptr [ebp - 0x30], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-48) /* -0x30 */) = cpu.eax;
    // 00428f57  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 00428f5a  db1c24                 -fistp dword ptr [esp]
    app->getMemory<x86::reg32>(cpu.esp) = x86::reg32(cpu.fpu.toInteger<x86::sreg32>(fpu30));
    // 00428f5d  58                     -pop eax
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00428f5e  d9ee                   -fldz 
    x86::Float fpu31 = 0.0;
    cpu.fpu.count += 1;
    cpu.fpu.st(0) = fpu31;
    }
L_0x00428f60:
    // 00428f60  8945d4                 -mov dword ptr [ebp - 0x2c], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-44) /* -0x2c */) = cpu.eax;
    // 00428f63  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 00428f66  db1c24                 -fistp dword ptr [esp]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu32 = cpu.fpu.st(0);
    app->getMemory<x86::reg32>(cpu.esp) = x86::reg32(cpu.fpu.toInteger<x86::sreg32>(fpu32));
    // 00428f69  58                     -pop eax
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00428f6a  8b0dc0d46f00           -mov ecx, dword ptr [0x6fd4c0]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(7328960) /* 0x6fd4c0 */);
    // 00428f70  8945d8                 -mov dword ptr [ebp - 0x28], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-40) /* -0x28 */) = cpu.eax;
    // 00428f73  8b45f4                 -mov eax, dword ptr [ebp - 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    cpu.fpu.count -= 1;
    }
    // 00428f76  e8257b0700             -call 0x4a0aa0
    cpu.esp -= 4;
    sub_4a0aa0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00428f7b  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00428f7d  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00428f7e  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00428f7f  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00428f80  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00428f81  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00428f82  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_428f90: native, nfs3hp::racestart::respawnCar */

/* sub_429100: native, nfs3hp::racestart::resetCar */

/* sub_429260: native, nfs3hp::racestart::stuckCheck */

/* align: skip 0x8d 0x40 0x00 0x8b 0xc9 */
void Application::sub_429490(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00429490  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00429491  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00429493  c7808401000000000000   -mov dword ptr [eax + 0x184], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(388) /* 0x184 */) = 0 /*0x0*/;
    // 0042949d  c780c005000000000000   -mov dword ptr [eax + 0x5c0], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(1472) /* 0x5c0 */) = 0 /*0x0*/;
    // 004294a7  c780c405000000000000   -mov dword ptr [eax + 0x5c4], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(1476) /* 0x5c4 */) = 0 /*0x0*/;
    // 004294b1  c780d408000000000000   -mov dword ptr [eax + 0x8d4], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(2260) /* 0x8d4 */) = 0 /*0x0*/;
    // 004294bb  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004294bc  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_4294c0: native, nfs3hp::racestart::clearRespawn */

/* sub_4294e0: native, nfs3hp::racestart::shakeAmplitude */

/* sub_4295a0: native, nfs3hp::racestart::startShake */

/* sub_4296c0: native, nfs3hp::racestart::startIdleShake */

/* sub_429790: native, nfs3hp::racestart::shakeWave */

/* sub_4297d0: native, nfs3hp::racestart::objectContacts */

/* sub_429880: native, nfs3hp::racestart::wheelSlip */

/* sub_4299a0: native, nfs3hp::racestart::wheelCells */

/* sub_429b40: native, nfs3hp::racestart::wheelSurface */

/* sub_429ba0: native, nfs3hp::racestart::endSkidMark */

/* sub_429d20: native, nfs3hp::racestart::extendSkidMark */

/* sub_429f10: native, nfs3hp::racestart::skidSounds */

/* sub_42a130: native, nfs3hp::racestart::wheelSpray */

/* sub_42a280: native, nfs3hp::racestart::surfaceEffects */

/* sub_42a480: native, nfs3hp::racestart::wheelSkid */

/* sub_42a560: native, nfs3hp::racestart::wheelEffects */

/* sub_42a7d0: native, nfs3hp::racestart::updateShake */

/* sub_42ac40: native, nfs3hp::racestart::crashEffects */

/* sub_42b480: native, nfs3hp::racestart::respawnEffects */

/* sub_42b660: native, nfs3hp::racestart::stopCarEffects */

/* sub_42b780: native, nfs3hp::racestart::carEffects */

/* sub_42b7b0: native, nfs3hp::racestart::airborneSpin */

/* sub_42b900: native, nfs3hp::racestart::updateCar */

/* sub_42ba00: native, nfs3hp::racestart::defaultGridPlace */

/* sub_42bb80: native, nfs3hp::racestart::loadStartGrid */

/* sub_42bc70: native, nfs3hp::racestart::gridPlace */

/* sub_42bcb0: native, nfs3hp::racestart::placeOnGrid */

/* sub_42c2a0: native, nfs3hp::raceload::loadCarPerformance */

/* sub_42c350: native, nfs3hp::raceload::loadRaceCar */

/* sub_42c400: native, nfs3hp::raceload::setCarHandlers */

/* sub_42c520: native, nfs3hp::raceload::freeCarShapes */

/* sub_42c530: native, nfs3hp::raceload::restartRaceCars */

/* sub_42c590: native, nfs3hp::decompiled::resetHandlingTunings */

/* sub_42c660: native, nfs3hp::raceload::clearCarSlots */

/* sub_42c680: native, nfs3hp::raceload::clearRaceCounts */

/* sub_42c6d0: native, nfs3hp::raceload::clearCarList */

/* sub_42c700: native, nfs3hp::raceload::loadRaceCars */

}
