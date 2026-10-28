#include "nfs3hp.h"
#include <lib/thread.h>

namespace nfs3hp
{
// Port (tools/apply_native_frontend.py): defined in native_frontend_cars.cpp.
bool tuningCopyAdvanced(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_cars.cpp.
bool tuningAdvancedDiffers(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_movie.py): defined in native_movie.cpp.
bool madShowFrame(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_view_angle.py): defined in nfs3hp_main.cpp.
x86::reg32 viewAngleFor(win32::WinApplication* app, x86::reg32 angle);
// Port (tools/apply_widescreen.py): defined in nfs3hp_main.cpp.
x86::reg32 widescreenHalfAngle(win32::WinApplication* app, x86::reg32 half, x86::reg32 vertical);
float zoomHalfWidth(win32::WinApplication* app);

/* sub_4d66f0: native, nfs3hp::port::shapes::shapeSize */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 */
void Application::sub_4d6730(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004d6730  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004d6731  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004d6732  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004d6733  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004d6735  83ec4c                 -sub esp, 0x4c
    (cpu.esp) -= x86::reg32(x86::sreg32(76 /*0x4c*/));
    // 004d6738  8945f8                 -mov dword ptr [ebp - 8], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.eax;
    // 004d673b  8955c4                 -mov dword ptr [ebp - 0x3c], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-60) /* -0x3c */) = cpu.edx;
    // 004d673e  895dc8                 -mov dword ptr [ebp - 0x38], ebx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-56) /* -0x38 */) = cpu.ebx;
    // 004d6741  8b4510                 -mov eax, dword ptr [ebp + 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(16) /* 0x10 */);
    // 004d6744  d94514                 -fld dword ptr [ebp + 0x14]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(20) /* 0x14 */));
    // 004d6747  8945b8                 -mov dword ptr [ebp - 0x48], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-72) /* -0x48 */) = cpu.eax;
    // 004d674a  dc0d5c965400           -fmul qword ptr [0x54965c]
    x86::Float fpu2 = cpu.fpu.mul(fpu1, x86::Float(app->getMemory<double>(x86::reg32(5543516) /* 0x54965c */)));
    // 004d6750  db45b8                 -fild dword ptr [ebp - 0x48]
    x86::Float fpu3 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-72) /* -0x48 */)));
    // 004d6753  dc0d64965400           -fmul qword ptr [0x549664]
    x86::Float fpu4 = cpu.fpu.mul(fpu3, x86::Float(app->getMemory<double>(x86::reg32(5543524) /* 0x549664 */)));
    // 004d6759  8b1534925500           -mov edx, dword ptr [0x559234]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5607988) /* 0x559234 */);
    // 004d675f  d9c9                   -fxch st(1)
    
    // 004d6761  d95df4                 -fstp dword ptr [ebp - 0xc]
    app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */) = float(fpu2);
    // 004d6764  d95dfc                 -fstp dword ptr [ebp - 4]
    app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = float(fpu4);
    // 004d6767  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    }
    // 004d6769  0f85f7040000           -jne 0x4d6c66
    if (!cpu.flags.zf)
    {
        goto L_0x004d6c66;
    }
    // 004d676f  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004d6772  8b5df8                 -mov ebx, dword ptr [ebp - 8]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004d6775  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 004d6778  01d8                   -add eax, ebx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.ebx));
    // 004d677a  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 004d677d  8b90ca488b00           -mov edx, dword ptr [eax + 0x8b48ca]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(9128138) /* 0x8b48ca */);
    // 004d6783  c1fa10                 -sar edx, 0x10
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (16 /*0x10*/ % 32));
    // 004d6786  8955f0                 -mov dword ptr [ebp - 0x10], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = cpu.edx;
    // 004d6789  83faff                 +cmp edx, -1
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
    // 004d678c  7513                   -jne 0x4d67a1
    if (!cpu.flags.zf)
    {
        goto L_0x004d67a1;
    }
    // 004d678e  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004d678f  6830965400             -push 0x549630
    app->getMemory<x86::reg32>(cpu.esp-4) = 5543472 /*0x549630*/;
    cpu.esp -= 4;
    // 004d6794  e8676df5ff             -call 0x42d500
    cpu.esp -= 4;
    nfs3hp::raceload::emptyHook(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d6799  83c408                 +add esp, 8
    {
        x86::reg32& tmp1 = cpu.esp;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(8 /*0x8*/));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 004d679c  e9c5040000             -jmp 0x4d6c66
    goto L_0x004d6c66;
L_0x004d67a1:
    // 004d67a1  df80c4488b00           -fild word ptr [eax + 0x8b48c4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu5 = x86::Float(x86::sreg16(app->getMemory<x86::reg16>(cpu.eax + x86::reg32(9128132) /* 0x8b48c4 */)));
    // 004d67a7  8b90c4488b00           -mov edx, dword ptr [eax + 0x8b48c4]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(9128132) /* 0x8b48c4 */);
    // 004d67ad  d945f4                 -fld dword ptr [ebp - 0xc]
    x86::Float fpu6 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */));
    // 004d67b0  d9c9                   -fxch st(1)
    
    // 004d67b2  d8c9                   -fmul st(1)
    x86::Float fpu7 = cpu.fpu.mul(fpu5, x86::Float(fpu6));
    // 004d67b4  c1fa10                 -sar edx, 0x10
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (16 /*0x10*/ % 32));
    // 004d67b7  f7da                   -neg edx
    cpu.edx = ~cpu.edx + 1;
    // 004d67b9  8955b8                 -mov dword ptr [ebp - 0x48], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-72) /* -0x48 */) = cpu.edx;
    // 004d67bc  db45b8                 -fild dword ptr [ebp - 0x48]
    x86::Float fpu8 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-72) /* -0x48 */)));
    // 004d67bf  deca                   -fmulp st(2)
    x86::Float fpu9 = cpu.fpu.mul(fpu6, fpu8);
    // 004d67c1  d9056c965400           -fld dword ptr [0x54966c]
    x86::Float fpu10 = x86::Float(app->getMemory<float>(x86::reg32(5543532) /* 0x54966c */));
    // 004d67c7  d9c9                   -fxch st(1)
    
    // 004d67c9  d8c9                   -fmul st(1)
    x86::Float fpu11 = cpu.fpu.mul(fpu7, x86::Float(fpu10));
    // 004d67cb  d9ca                   -fxch st(2)
    
    // 004d67cd  dec9                   -fmulp st(1)
    x86::Float fpu12 = cpu.fpu.mul(fpu10, fpu9);
    // 004d67cf  d905a83a5600           -fld dword ptr [0x563aa8]
    x86::Float fpu13 = x86::Float(app->getMemory<float>(x86::reg32(5651112) /* 0x563aa8 */));
    // 004d67d5  d905ac3a5600           -fld dword ptr [0x563aac]
    x86::Float fpu14 = x86::Float(app->getMemory<float>(x86::reg32(5651116) /* 0x563aac */));
    // 004d67db  894db8                 -mov dword ptr [ebp - 0x48], ecx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-72) /* -0x48 */) = cpu.ecx;
    // 004d67de  d9c9                   -fxch st(1)
    
    // 004d67e0  d91d183b5600           -fstp dword ptr [0x563b18]
    app->getMemory<float>(x86::reg32(5651224) /* 0x563b18 */) = float(fpu13);
    // 004d67e6  d91d1c3b5600           -fstp dword ptr [0x563b1c]
    app->getMemory<float>(x86::reg32(5651228) /* 0x563b1c */) = float(fpu14);
    // 004d67ec  31f6                   -xor esi, esi
    cpu.esi ^= x86::reg32(x86::sreg32(cpu.esi));
    // 004d67ee  d9051c3b5600           -fld dword ptr [0x563b1c]
    x86::Float fpu15 = x86::Float(app->getMemory<float>(x86::reg32(5651228) /* 0x563b1c */));
    // 004d67f4  8b15183b5600           -mov edx, dword ptr [0x563b18]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5651224) /* 0x563b18 */);
    // 004d67fa  8915f83a5600           -mov dword ptr [0x563af8], edx
    app->getMemory<x86::reg32>(x86::reg32(5651192) /* 0x563af8 */) = cpu.edx;
    // 004d6800  d91dfc3a5600           -fstp dword ptr [0x563afc]
    app->getMemory<float>(x86::reg32(5651196) /* 0x563afc */) = float(fpu15);
    // 004d6806  8975dc                 -mov dword ptr [ebp - 0x24], esi
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-36) /* -0x24 */) = cpu.esi;
    // 004d6809  d905fc3a5600           -fld dword ptr [0x563afc]
    x86::Float fpu16 = x86::Float(app->getMemory<float>(x86::reg32(5651196) /* 0x563afc */));
    // 004d680f  8b15f83a5600           -mov edx, dword ptr [0x563af8]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5651192) /* 0x563af8 */);
    // 004d6815  8915d83a5600           -mov dword ptr [0x563ad8], edx
    app->getMemory<x86::reg32>(x86::reg32(5651160) /* 0x563ad8 */) = cpu.edx;
    // 004d681b  d91ddc3a5600           -fstp dword ptr [0x563adc]
    app->getMemory<float>(x86::reg32(5651164) /* 0x563adc */) = float(fpu16);
    // 004d6821  d905d83a5600           -fld dword ptr [0x563ad8]
    x86::Float fpu17 = x86::Float(app->getMemory<float>(x86::reg32(5651160) /* 0x563ad8 */));
    // 004d6827  d905dc3a5600           -fld dword ptr [0x563adc]
    x86::Float fpu18 = x86::Float(app->getMemory<float>(x86::reg32(5651164) /* 0x563adc */));
    // 004d682d  db45b8                 -fild dword ptr [ebp - 0x48]
    x86::Float fpu19 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-72) /* -0x48 */)));
    // 004d6830  dee4                   -fsubrp st(4)
    x86::Float fpu20 = cpu.fpu.sub(fpu19, x86::Float(fpu11));
    // 004d6832  d9c9                   -fxch st(1)
    
    // 004d6834  d91db83a5600           -fstp dword ptr [0x563ab8]
    app->getMemory<float>(x86::reg32(5651128) /* 0x563ab8 */) = float(fpu17);
    // 004d683a  df80c8488b00           -fild word ptr [eax + 0x8b48c8]
    x86::Float fpu21 = x86::Float(x86::sreg16(app->getMemory<x86::reg16>(cpu.eax + x86::reg32(9128136) /* 0x8b48c8 */)));
    // 004d6840  dec3                   -faddp st(3)
    x86::Float fpu22 = cpu.fpu.add(fpu20, fpu21);
    // 004d6842  d91dbc3a5600           -fstp dword ptr [0x563abc]
    app->getMemory<float>(x86::reg32(5651132) /* 0x563abc */) = float(fpu18);
    // 004d6848  d9c9                   -fxch st(1)
    
    // 004d684a  d95dc0                 -fstp dword ptr [ebp - 0x40]
    app->getMemory<float>(cpu.ebp + x86::reg32(-64) /* -0x40 */) = float(fpu22);
    // 004d684d  df80ca488b00           -fild word ptr [eax + 0x8b48ca]
    x86::Float fpu23 = x86::Float(x86::sreg16(app->getMemory<x86::reg16>(cpu.eax + x86::reg32(9128138) /* 0x8b48ca */)));
    // 004d6853  dec1                   -faddp st(1)
    x86::Float fpu24 = cpu.fpu.add(fpu12, fpu23);
    // 004d6855  b8ffffffff             -mov eax, 0xffffffff
    cpu.eax = 4294967295 /*0xffffffff*/;
    // 004d685a  d95dcc                 -fstp dword ptr [ebp - 0x34]
    app->getMemory<float>(cpu.ebp + x86::reg32(-52) /* -0x34 */) = float(fpu24);
    // 004d685d  a3203b5600             -mov dword ptr [0x563b20], eax
    app->getMemory<x86::reg32>(x86::reg32(5651232) /* 0x563b20 */) = cpu.eax;
    // 004d6862  a3003b5600             -mov dword ptr [0x563b00], eax
    app->getMemory<x86::reg32>(x86::reg32(5651200) /* 0x563b00 */) = cpu.eax;
    // 004d6867  a3e03a5600             -mov dword ptr [0x563ae0], eax
    app->getMemory<x86::reg32>(x86::reg32(5651168) /* 0x563ae0 */) = cpu.eax;
    // 004d686c  a3c03a5600             -mov dword ptr [0x563ac0], eax
    app->getMemory<x86::reg32>(x86::reg32(5651136) /* 0x563ac0 */) = cpu.eax;
    }
L_0x004d6871:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004d6871  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004d6874  8b7df8                 -mov edi, dword ptr [ebp - 8]
    cpu.edi = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004d6877  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 004d687a  01f8                   -add eax, edi
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edi));
    // 004d687c  8b0485c2488b00         -mov eax, dword ptr [eax*4 + 0x8b48c2]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(9128130) /* 0x8b48c2 */ + cpu.eax * 4);
    // 004d6883  8b55dc                 -mov edx, dword ptr [ebp - 0x24]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-36) /* -0x24 */);
    // 004d6886  c1f810                 -sar eax, 0x10
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (16 /*0x10*/ % 32));
    // 004d6889  39d0                   +cmp eax, edx
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
    // 004d688b  0f8ed5030000           -jle 0x4d6c66
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004d6c66;
    }
    // 004d6891  8955b8                 -mov dword ptr [ebp - 0x48], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-72) /* -0x48 */) = cpu.edx;
    // 004d6894  d945f4                 -fld dword ptr [ebp - 0xc]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu25 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */));
    // 004d6897  db45b8                 -fild dword ptr [ebp - 0x48]
    x86::Float fpu26 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-72) /* -0x48 */)));
    // 004d689a  d8c9                   -fmul st(1)
    x86::Float fpu27 = cpu.fpu.mul(fpu26, x86::Float(fpu25));
    // 004d689c  d845c0                 -fadd dword ptr [ebp - 0x40]
    x86::Float fpu28 = cpu.fpu.add(fpu27, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-64) /* -0x40 */)));
    // 004d689f  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 004d68a1  d955e8                 -fst dword ptr [ebp - 0x18]
    app->getMemory<float>(cpu.ebp + x86::reg32(-24) /* -0x18 */) = float(fpu28);
    // 004d68a4  8b45e8                 -mov eax, dword ptr [ebp - 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-24) /* -0x18 */);
    // 004d68a7  dec1                   -faddp st(1)
    x86::Float fpu29 = cpu.fpu.add(fpu25, fpu28);
    // 004d68a9  8945bc                 -mov dword ptr [ebp - 0x44], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-68) /* -0x44 */) = cpu.eax;
    // 004d68ac  d95dd8                 -fstp dword ptr [ebp - 0x28]
    app->getMemory<float>(cpu.ebp + x86::reg32(-40) /* -0x28 */) = float(fpu29);
    // 004d68af  8b45d8                 -mov eax, dword ptr [ebp - 0x28]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-40) /* -0x28 */);
    // 004d68b2  894de4                 -mov dword ptr [ebp - 0x1c], ecx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-28) /* -0x1c */) = cpu.ecx;
    // 004d68b5  8945d0                 -mov dword ptr [ebp - 0x30], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-48) /* -0x30 */) = cpu.eax;
    }
L_0x004d68b8:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004d68b8  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004d68bb  8b5df8                 -mov ebx, dword ptr [ebp - 8]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004d68be  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 004d68c1  01d8                   -add eax, ebx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.ebx));
    // 004d68c3  8b0485c4488b00         -mov eax, dword ptr [eax*4 + 0x8b48c4]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(9128132) /* 0x8b48c4 */ + cpu.eax * 4);
    // 004d68ca  8b75e4                 -mov esi, dword ptr [ebp - 0x1c]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-28) /* -0x1c */);
    // 004d68cd  c1f810                 -sar eax, 0x10
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (16 /*0x10*/ % 32));
    // 004d68d0  39f0                   +cmp eax, esi
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
    // 004d68d2  0f8e86030000           -jle 0x4d6c5e
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004d6c5e;
    }
    // 004d68d8  8975b8                 -mov dword ptr [ebp - 0x48], esi
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-72) /* -0x48 */) = cpu.esi;
    // 004d68db  d945f4                 -fld dword ptr [ebp - 0xc]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu30 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */));
    // 004d68de  db45b8                 -fild dword ptr [ebp - 0x48]
    x86::Float fpu31 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-72) /* -0x48 */)));
    // 004d68e1  d8c9                   -fmul st(1)
    x86::Float fpu32 = cpu.fpu.mul(fpu31, x86::Float(fpu30));
    // 004d68e3  d845cc                 -fadd dword ptr [ebp - 0x34]
    x86::Float fpu33 = cpu.fpu.add(fpu32, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-52) /* -0x34 */)));
    // 004d68e6  d955d4                 -fst dword ptr [ebp - 0x2c]
    app->getMemory<float>(cpu.ebp + x86::reg32(-44) /* -0x2c */) = float(fpu33);
    // 004d68e9  dec1                   -faddp st(1)
    x86::Float fpu34 = cpu.fpu.add(fpu30, fpu33);
    // 004d68eb  ff75fc                 -push dword ptr [ebp - 4]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    cpu.esp -= 4;
    // 004d68ee  d95dec                 -fstp dword ptr [ebp - 0x14]
    app->getMemory<float>(cpu.ebp + x86::reg32(-20) /* -0x14 */) = float(fpu34);
    }
    // 004d68f1  e85a400100             -call 0x4ea950
    cpu.esp -= 4;
    sub_4ea950(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d68f6  8b45c4                 -mov eax, dword ptr [ebp - 0x3c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-60) /* -0x3c */);
    // 004d68f9  d84dbc                 -fmul dword ptr [ebp - 0x44]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu35 = cpu.fpu.st(0);
    x86::Float fpu36 = cpu.fpu.mul(fpu35, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-68) /* -0x44 */)));
    // 004d68fc  8945b8                 -mov dword ptr [ebp - 0x48], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-72) /* -0x48 */) = cpu.eax;
    // 004d68ff  db45b8                 -fild dword ptr [ebp - 0x48]
    x86::Float fpu37 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-72) /* -0x48 */)));
    // 004d6902  d95db4                 -fstp dword ptr [ebp - 0x4c]
    app->getMemory<float>(cpu.ebp + x86::reg32(-76) /* -0x4c */) = float(fpu37);
    // 004d6905  d845b4                 -fadd dword ptr [ebp - 0x4c]
    x86::Float fpu38 = cpu.fpu.add(fpu36, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-76) /* -0x4c */)));
    // 004d6908  ff75fc                 -push dword ptr [ebp - 4]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    cpu.esp -= 4;
    // 004d690b  d95db8                 -fstp dword ptr [ebp - 0x48]
    app->getMemory<float>(cpu.ebp + x86::reg32(-72) /* -0x48 */) = float(fpu38);
    cpu.fpu.count -= 1;
    }
    // 004d690e  e81d400100             -call 0x4ea930
    cpu.esp -= 4;
    sub_4ea930(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d6913  d84dd4                 -fmul dword ptr [ebp - 0x2c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu39 = cpu.fpu.st(0);
    x86::Float fpu40 = cpu.fpu.mul(fpu39, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-44) /* -0x2c */)));
    // 004d6916  d86db8                 -fsubr dword ptr [ebp - 0x48]
    x86::Float fpu41 = cpu.fpu.sub(x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-72) /* -0x48 */)), fpu40);
    // 004d6919  ff75fc                 -push dword ptr [ebp - 4]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    cpu.esp -= 4;
    // 004d691c  d91db03a5600           -fstp dword ptr [0x563ab0]
    app->getMemory<float>(x86::reg32(5651120) /* 0x563ab0 */) = float(fpu41);
    cpu.fpu.count -= 1;
    }
    // 004d6922  e829400100             -call 0x4ea950
    cpu.esp -= 4;
    sub_4ea950(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d6927  d84dd0                 -fmul dword ptr [ebp - 0x30]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu42 = cpu.fpu.st(0);
    x86::Float fpu43 = cpu.fpu.mul(fpu42, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-48) /* -0x30 */)));
    // 004d692a  d845b4                 -fadd dword ptr [ebp - 0x4c]
    x86::Float fpu44 = cpu.fpu.add(fpu43, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-76) /* -0x4c */)));
    // 004d692d  ff75fc                 -push dword ptr [ebp - 4]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    cpu.esp -= 4;
    // 004d6930  d95db8                 -fstp dword ptr [ebp - 0x48]
    app->getMemory<float>(cpu.ebp + x86::reg32(-72) /* -0x48 */) = float(fpu44);
    cpu.fpu.count -= 1;
    }
    // 004d6933  e8f83f0100             -call 0x4ea930
    cpu.esp -= 4;
    sub_4ea930(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d6938  d84dd4                 -fmul dword ptr [ebp - 0x2c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu45 = cpu.fpu.st(0);
    x86::Float fpu46 = cpu.fpu.mul(fpu45, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-44) /* -0x2c */)));
    // 004d693b  d86db8                 -fsubr dword ptr [ebp - 0x48]
    x86::Float fpu47 = cpu.fpu.sub(x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-72) /* -0x48 */)), fpu46);
    // 004d693e  ff75fc                 -push dword ptr [ebp - 4]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    cpu.esp -= 4;
    // 004d6941  d91dd03a5600           -fstp dword ptr [0x563ad0]
    app->getMemory<float>(x86::reg32(5651152) /* 0x563ad0 */) = float(fpu47);
    cpu.fpu.count -= 1;
    }
    // 004d6947  e804400100             -call 0x4ea950
    cpu.esp -= 4;
    sub_4ea950(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d694c  d84dd8                 -fmul dword ptr [ebp - 0x28]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu48 = cpu.fpu.st(0);
    x86::Float fpu49 = cpu.fpu.mul(fpu48, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-40) /* -0x28 */)));
    // 004d694f  d845b4                 -fadd dword ptr [ebp - 0x4c]
    x86::Float fpu50 = cpu.fpu.add(fpu49, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-76) /* -0x4c */)));
    // 004d6952  ff75fc                 -push dword ptr [ebp - 4]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    cpu.esp -= 4;
    // 004d6955  d95db8                 -fstp dword ptr [ebp - 0x48]
    app->getMemory<float>(cpu.ebp + x86::reg32(-72) /* -0x48 */) = float(fpu50);
    cpu.fpu.count -= 1;
    }
    // 004d6958  e8d33f0100             -call 0x4ea930
    cpu.esp -= 4;
    sub_4ea930(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d695d  d84dec                 -fmul dword ptr [ebp - 0x14]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu51 = cpu.fpu.st(0);
    x86::Float fpu52 = cpu.fpu.mul(fpu51, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-20) /* -0x14 */)));
    // 004d6960  d86db8                 -fsubr dword ptr [ebp - 0x48]
    x86::Float fpu53 = cpu.fpu.sub(x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-72) /* -0x48 */)), fpu52);
    // 004d6963  ff75fc                 -push dword ptr [ebp - 4]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    cpu.esp -= 4;
    // 004d6966  d91df03a5600           -fstp dword ptr [0x563af0]
    app->getMemory<float>(x86::reg32(5651184) /* 0x563af0 */) = float(fpu53);
    cpu.fpu.count -= 1;
    }
    // 004d696c  e8df3f0100             -call 0x4ea950
    cpu.esp -= 4;
    sub_4ea950(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d6971  d84de8                 -fmul dword ptr [ebp - 0x18]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu54 = cpu.fpu.st(0);
    x86::Float fpu55 = cpu.fpu.mul(fpu54, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-24) /* -0x18 */)));
    // 004d6974  d845b4                 -fadd dword ptr [ebp - 0x4c]
    x86::Float fpu56 = cpu.fpu.add(fpu55, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-76) /* -0x4c */)));
    // 004d6977  ff75fc                 -push dword ptr [ebp - 4]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    cpu.esp -= 4;
    // 004d697a  d95db8                 -fstp dword ptr [ebp - 0x48]
    app->getMemory<float>(cpu.ebp + x86::reg32(-72) /* -0x48 */) = float(fpu56);
    cpu.fpu.count -= 1;
    }
    // 004d697d  e8ae3f0100             -call 0x4ea930
    cpu.esp -= 4;
    sub_4ea930(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d6982  d84dec                 -fmul dword ptr [ebp - 0x14]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu57 = cpu.fpu.st(0);
    x86::Float fpu58 = cpu.fpu.mul(fpu57, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-20) /* -0x14 */)));
    // 004d6985  d86db8                 -fsubr dword ptr [ebp - 0x48]
    x86::Float fpu59 = cpu.fpu.sub(x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-72) /* -0x48 */)), fpu58);
    // 004d6988  ff75fc                 -push dword ptr [ebp - 4]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    cpu.esp -= 4;
    // 004d698b  d91d103b5600           -fstp dword ptr [0x563b10]
    app->getMemory<float>(x86::reg32(5651216) /* 0x563b10 */) = float(fpu59);
    cpu.fpu.count -= 1;
    }
    // 004d6991  e89a3f0100             -call 0x4ea930
    cpu.esp -= 4;
    sub_4ea930(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d6996  8b45c8                 -mov eax, dword ptr [ebp - 0x38]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-56) /* -0x38 */);
    // 004d6999  d84dbc                 -fmul dword ptr [ebp - 0x44]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu60 = cpu.fpu.st(0);
    x86::Float fpu61 = cpu.fpu.mul(fpu60, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-68) /* -0x44 */)));
    // 004d699c  8945b8                 -mov dword ptr [ebp - 0x48], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-72) /* -0x48 */) = cpu.eax;
    // 004d699f  db45b8                 -fild dword ptr [ebp - 0x48]
    x86::Float fpu62 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-72) /* -0x48 */)));
    // 004d69a2  d95de0                 -fstp dword ptr [ebp - 0x20]
    app->getMemory<float>(cpu.ebp + x86::reg32(-32) /* -0x20 */) = float(fpu62);
    // 004d69a5  d845e0                 -fadd dword ptr [ebp - 0x20]
    x86::Float fpu63 = cpu.fpu.add(fpu61, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-32) /* -0x20 */)));
    // 004d69a8  ff75fc                 -push dword ptr [ebp - 4]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    cpu.esp -= 4;
    // 004d69ab  d95db8                 -fstp dword ptr [ebp - 0x48]
    app->getMemory<float>(cpu.ebp + x86::reg32(-72) /* -0x48 */) = float(fpu63);
    cpu.fpu.count -= 1;
    }
    // 004d69ae  e89d3f0100             -call 0x4ea950
    cpu.esp -= 4;
    sub_4ea950(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d69b3  d84dd4                 -fmul dword ptr [ebp - 0x2c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu64 = cpu.fpu.st(0);
    x86::Float fpu65 = cpu.fpu.mul(fpu64, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-44) /* -0x2c */)));
    // 004d69b6  d845b8                 -fadd dword ptr [ebp - 0x48]
    x86::Float fpu66 = cpu.fpu.add(fpu65, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-72) /* -0x48 */)));
    // 004d69b9  ff75fc                 -push dword ptr [ebp - 4]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    cpu.esp -= 4;
    // 004d69bc  d91db43a5600           -fstp dword ptr [0x563ab4]
    app->getMemory<float>(x86::reg32(5651124) /* 0x563ab4 */) = float(fpu66);
    cpu.fpu.count -= 1;
    }
    // 004d69c2  e8693f0100             -call 0x4ea930
    cpu.esp -= 4;
    sub_4ea930(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d69c7  d84dd0                 -fmul dword ptr [ebp - 0x30]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu67 = cpu.fpu.st(0);
    x86::Float fpu68 = cpu.fpu.mul(fpu67, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-48) /* -0x30 */)));
    // 004d69ca  d845e0                 -fadd dword ptr [ebp - 0x20]
    x86::Float fpu69 = cpu.fpu.add(fpu68, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-32) /* -0x20 */)));
    // 004d69cd  ff75fc                 -push dword ptr [ebp - 4]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    cpu.esp -= 4;
    // 004d69d0  d95db8                 -fstp dword ptr [ebp - 0x48]
    app->getMemory<float>(cpu.ebp + x86::reg32(-72) /* -0x48 */) = float(fpu69);
    cpu.fpu.count -= 1;
    }
    // 004d69d3  e8783f0100             -call 0x4ea950
    cpu.esp -= 4;
    sub_4ea950(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d69d8  d84dd4                 -fmul dword ptr [ebp - 0x2c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu70 = cpu.fpu.st(0);
    x86::Float fpu71 = cpu.fpu.mul(fpu70, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-44) /* -0x2c */)));
    // 004d69db  d845b8                 -fadd dword ptr [ebp - 0x48]
    x86::Float fpu72 = cpu.fpu.add(fpu71, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-72) /* -0x48 */)));
    // 004d69de  ff75fc                 -push dword ptr [ebp - 4]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    cpu.esp -= 4;
    // 004d69e1  d91dd43a5600           -fstp dword ptr [0x563ad4]
    app->getMemory<float>(x86::reg32(5651156) /* 0x563ad4 */) = float(fpu72);
    cpu.fpu.count -= 1;
    }
    // 004d69e7  e8443f0100             -call 0x4ea930
    cpu.esp -= 4;
    sub_4ea930(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d69ec  d84dd8                 -fmul dword ptr [ebp - 0x28]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu73 = cpu.fpu.st(0);
    x86::Float fpu74 = cpu.fpu.mul(fpu73, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-40) /* -0x28 */)));
    // 004d69ef  d845e0                 -fadd dword ptr [ebp - 0x20]
    x86::Float fpu75 = cpu.fpu.add(fpu74, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-32) /* -0x20 */)));
    // 004d69f2  ff75fc                 -push dword ptr [ebp - 4]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    cpu.esp -= 4;
    // 004d69f5  d95db8                 -fstp dword ptr [ebp - 0x48]
    app->getMemory<float>(cpu.ebp + x86::reg32(-72) /* -0x48 */) = float(fpu75);
    cpu.fpu.count -= 1;
    }
    // 004d69f8  e8533f0100             -call 0x4ea950
    cpu.esp -= 4;
    sub_4ea950(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d69fd  d84dec                 -fmul dword ptr [ebp - 0x14]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu76 = cpu.fpu.st(0);
    x86::Float fpu77 = cpu.fpu.mul(fpu76, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-20) /* -0x14 */)));
    // 004d6a00  d845b8                 -fadd dword ptr [ebp - 0x48]
    x86::Float fpu78 = cpu.fpu.add(fpu77, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-72) /* -0x48 */)));
    // 004d6a03  d91df43a5600           -fstp dword ptr [0x563af4]
    app->getMemory<float>(x86::reg32(5651188) /* 0x563af4 */) = float(fpu78);
    // 004d6a09  ff75fc                 -push dword ptr [ebp - 4]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    cpu.esp -= 4;
    cpu.fpu.count -= 1;
    }
    // 004d6a0c  e81f3f0100             -call 0x4ea930
    cpu.esp -= 4;
    sub_4ea930(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d6a11  d84de8                 -fmul dword ptr [ebp - 0x18]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu79 = cpu.fpu.st(0);
    x86::Float fpu80 = cpu.fpu.mul(fpu79, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-24) /* -0x18 */)));
    // 004d6a14  d845e0                 -fadd dword ptr [ebp - 0x20]
    x86::Float fpu81 = cpu.fpu.add(fpu80, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-32) /* -0x20 */)));
    // 004d6a17  ff75fc                 -push dword ptr [ebp - 4]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    cpu.esp -= 4;
    // 004d6a1a  d95db8                 -fstp dword ptr [ebp - 0x48]
    app->getMemory<float>(cpu.ebp + x86::reg32(-72) /* -0x48 */) = float(fpu81);
    cpu.fpu.count -= 1;
    }
    // 004d6a1d  e82e3f0100             -call 0x4ea950
    cpu.esp -= 4;
    sub_4ea950(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d6a22  d84dec                 -fmul dword ptr [ebp - 0x14]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu82 = cpu.fpu.st(0);
    x86::Float fpu83 = cpu.fpu.mul(fpu82, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-20) /* -0x14 */)));
    // 004d6a25  8b45f0                 -mov eax, dword ptr [ebp - 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 004d6a28  8b7df0                 -mov edi, dword ptr [ebp - 0x10]
    cpu.edi = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 004d6a2b  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 004d6a2e  beb03a5600             -mov esi, 0x563ab0
    cpu.esi = 5651120 /*0x563ab0*/;
    // 004d6a33  29f8                   -sub eax, edi
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edi));
    // 004d6a35  d845b8                 -fadd dword ptr [ebp - 0x48]
    x86::Float fpu84 = cpu.fpu.add(fpu83, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-72) /* -0x48 */)));
    // 004d6a38  8b148590508b00         -mov edx, dword ptr [eax*4 + 0x8b5090]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(9130128) /* 0x8b5090 */ + cpu.eax * 4);
    // 004d6a3f  8d4701                 -lea eax, [edi + 1]
    cpu.eax = x86::reg32(cpu.edi + x86::reg32(1) /* 0x1 */);
    // 004d6a42  d91d143b5600           -fstp dword ptr [0x563b14]
    app->getMemory<float>(x86::reg32(5651220) /* 0x563b14 */) = float(fpu84);
    // 004d6a48  8945f0                 -mov dword ptr [ebp - 0x10], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = cpu.eax;
    // 004d6a4b  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 004d6a50  bfc43a5600             -mov edi, 0x563ac4
    cpu.edi = 5651140 /*0x563ac4*/;
    cpu.fpu.count -= 1;
    }
    // 004d6a55  e8a6aef5ff             -call 0x431900
    cpu.esp -= 4;
    nfs3hp::graphics::setRenderState(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d6a5a  8b460c                 -mov eax, dword ptr [esi + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 004d6a5d  8b0df8347d00           -mov ecx, dword ptr [0x7d34f8]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205560) /* 0x7d34f8 */);
    // 004d6a63  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004d6a68  7558                   -jne 0x4d6ac2
    if (!cpu.flags.zf)
    {
        goto L_0x004d6ac2;
    }
    // 004d6a6a  39c8                   +cmp eax, ecx
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
    // 004d6a6c  7d54                   -jge 0x4d6ac2
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004d6ac2;
    }
    // 004d6a6e  8b4604                 -mov eax, dword ptr [esi + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 004d6a71  bb00000000             -mov ebx, 0
    cpu.ebx = 0 /*0x0*/;
    // 004d6a76  8b0d04357d00           -mov ecx, dword ptr [0x7d3504]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205572) /* 0x7d3504 */);
    // 004d6a7c  8b1500357d00           -mov edx, dword ptr [0x7d3500]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205568) /* 0x7d3500 */);
    // 004d6a82  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004d6a87  750d                   -jne 0x4d6a96
    if (!cpu.flags.zf)
    {
        goto L_0x004d6a96;
    }
    // 004d6a89  39c8                   +cmp eax, ecx
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
    // 004d6a8b  7c09                   -jl 0x4d6a96
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004d6a96;
    }
    // 004d6a8d  39d0                   +cmp eax, edx
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
    // 004d6a8f  7e09                   -jle 0x4d6a9a
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004d6a9a;
    }
    // 004d6a91  83cb04                 +or ebx, 4
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(4 /*0x4*/))));
    // 004d6a94  eb04                   -jmp 0x4d6a9a
    goto L_0x004d6a9a;
L_0x004d6a96:
    // 004d6a96  83cb08                 -or ebx, 8
    cpu.ebx |= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 004d6a99  90                     -nop 
    ;
L_0x004d6a9a:
    // 004d6a9a  8b06                   -mov eax, dword ptr [esi]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi);
    // 004d6a9c  90                     -nop 
    ;
    // 004d6a9d  8b0dfc347d00           -mov ecx, dword ptr [0x7d34fc]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205564) /* 0x7d34fc */);
    // 004d6aa3  8b150c357d00           -mov edx, dword ptr [0x7d350c]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205580) /* 0x7d350c */);
    // 004d6aa9  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004d6aae  750d                   -jne 0x4d6abd
    if (!cpu.flags.zf)
    {
        goto L_0x004d6abd;
    }
    // 004d6ab0  39c8                   +cmp eax, ecx
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
    // 004d6ab2  7c09                   -jl 0x4d6abd
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004d6abd;
    }
    // 004d6ab4  39d0                   +cmp eax, edx
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
    // 004d6ab6  7e0f                   -jle 0x4d6ac7
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004d6ac7;
    }
    // 004d6ab8  83cb02                 +or ebx, 2
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(2 /*0x2*/))));
    // 004d6abb  eb0a                   -jmp 0x4d6ac7
    goto L_0x004d6ac7;
L_0x004d6abd:
    // 004d6abd  83cb01                 +or ebx, 1
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(1 /*0x1*/))));
    // 004d6ac0  eb05                   -jmp 0x4d6ac7
    goto L_0x004d6ac7;
L_0x004d6ac2:
    // 004d6ac2  bb10000000             -mov ebx, 0x10
    cpu.ebx = 16 /*0x10*/;
L_0x004d6ac7:
    // 004d6ac7  881f                   -mov byte ptr [edi], bl
    app->getMemory<x86::reg8>(cpu.edi) = cpu.bl;
    // 004d6ac9  bfe43a5600             -mov edi, 0x563ae4
    cpu.edi = 5651172 /*0x563ae4*/;
    // 004d6ace  bed03a5600             -mov esi, 0x563ad0
    cpu.esi = 5651152 /*0x563ad0*/;
    // 004d6ad3  8b460c                 -mov eax, dword ptr [esi + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 004d6ad6  8b0df8347d00           -mov ecx, dword ptr [0x7d34f8]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205560) /* 0x7d34f8 */);
    // 004d6adc  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004d6ae1  7558                   -jne 0x4d6b3b
    if (!cpu.flags.zf)
    {
        goto L_0x004d6b3b;
    }
    // 004d6ae3  39c8                   +cmp eax, ecx
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
    // 004d6ae5  7d54                   -jge 0x4d6b3b
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004d6b3b;
    }
    // 004d6ae7  8b4604                 -mov eax, dword ptr [esi + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 004d6aea  bb00000000             -mov ebx, 0
    cpu.ebx = 0 /*0x0*/;
    // 004d6aef  8b0d04357d00           -mov ecx, dword ptr [0x7d3504]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205572) /* 0x7d3504 */);
    // 004d6af5  8b1500357d00           -mov edx, dword ptr [0x7d3500]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205568) /* 0x7d3500 */);
    // 004d6afb  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004d6b00  750d                   -jne 0x4d6b0f
    if (!cpu.flags.zf)
    {
        goto L_0x004d6b0f;
    }
    // 004d6b02  39c8                   +cmp eax, ecx
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
    // 004d6b04  7c09                   -jl 0x4d6b0f
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004d6b0f;
    }
    // 004d6b06  39d0                   +cmp eax, edx
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
    // 004d6b08  7e09                   -jle 0x4d6b13
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004d6b13;
    }
    // 004d6b0a  83cb04                 +or ebx, 4
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(4 /*0x4*/))));
    // 004d6b0d  eb04                   -jmp 0x4d6b13
    goto L_0x004d6b13;
L_0x004d6b0f:
    // 004d6b0f  83cb08                 -or ebx, 8
    cpu.ebx |= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 004d6b12  90                     -nop 
    ;
L_0x004d6b13:
    // 004d6b13  8b06                   -mov eax, dword ptr [esi]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi);
    // 004d6b15  90                     -nop 
    ;
    // 004d6b16  8b0dfc347d00           -mov ecx, dword ptr [0x7d34fc]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205564) /* 0x7d34fc */);
    // 004d6b1c  8b150c357d00           -mov edx, dword ptr [0x7d350c]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205580) /* 0x7d350c */);
    // 004d6b22  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004d6b27  750d                   -jne 0x4d6b36
    if (!cpu.flags.zf)
    {
        goto L_0x004d6b36;
    }
    // 004d6b29  39c8                   +cmp eax, ecx
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
    // 004d6b2b  7c09                   -jl 0x4d6b36
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004d6b36;
    }
    // 004d6b2d  39d0                   +cmp eax, edx
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
    // 004d6b2f  7e0f                   -jle 0x4d6b40
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004d6b40;
    }
    // 004d6b31  83cb02                 +or ebx, 2
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(2 /*0x2*/))));
    // 004d6b34  eb0a                   -jmp 0x4d6b40
    goto L_0x004d6b40;
L_0x004d6b36:
    // 004d6b36  83cb01                 +or ebx, 1
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(1 /*0x1*/))));
    // 004d6b39  eb05                   -jmp 0x4d6b40
    goto L_0x004d6b40;
L_0x004d6b3b:
    // 004d6b3b  bb10000000             -mov ebx, 0x10
    cpu.ebx = 16 /*0x10*/;
L_0x004d6b40:
    // 004d6b40  881f                   -mov byte ptr [edi], bl
    app->getMemory<x86::reg8>(cpu.edi) = cpu.bl;
    // 004d6b42  bf043b5600             -mov edi, 0x563b04
    cpu.edi = 5651204 /*0x563b04*/;
    // 004d6b47  bef03a5600             -mov esi, 0x563af0
    cpu.esi = 5651184 /*0x563af0*/;
    // 004d6b4c  8b460c                 -mov eax, dword ptr [esi + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 004d6b4f  8b0df8347d00           -mov ecx, dword ptr [0x7d34f8]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205560) /* 0x7d34f8 */);
    // 004d6b55  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004d6b5a  7558                   -jne 0x4d6bb4
    if (!cpu.flags.zf)
    {
        goto L_0x004d6bb4;
    }
    // 004d6b5c  39c8                   +cmp eax, ecx
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
    // 004d6b5e  7d54                   -jge 0x4d6bb4
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004d6bb4;
    }
    // 004d6b60  8b4604                 -mov eax, dword ptr [esi + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 004d6b63  bb00000000             -mov ebx, 0
    cpu.ebx = 0 /*0x0*/;
    // 004d6b68  8b0d04357d00           -mov ecx, dword ptr [0x7d3504]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205572) /* 0x7d3504 */);
    // 004d6b6e  8b1500357d00           -mov edx, dword ptr [0x7d3500]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205568) /* 0x7d3500 */);
    // 004d6b74  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004d6b79  750d                   -jne 0x4d6b88
    if (!cpu.flags.zf)
    {
        goto L_0x004d6b88;
    }
    // 004d6b7b  39c8                   +cmp eax, ecx
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
    // 004d6b7d  7c09                   -jl 0x4d6b88
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004d6b88;
    }
    // 004d6b7f  39d0                   +cmp eax, edx
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
    // 004d6b81  7e09                   -jle 0x4d6b8c
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004d6b8c;
    }
    // 004d6b83  83cb04                 +or ebx, 4
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(4 /*0x4*/))));
    // 004d6b86  eb04                   -jmp 0x4d6b8c
    goto L_0x004d6b8c;
L_0x004d6b88:
    // 004d6b88  83cb08                 -or ebx, 8
    cpu.ebx |= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 004d6b8b  90                     -nop 
    ;
L_0x004d6b8c:
    // 004d6b8c  8b06                   -mov eax, dword ptr [esi]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi);
    // 004d6b8e  90                     -nop 
    ;
    // 004d6b8f  8b0dfc347d00           -mov ecx, dword ptr [0x7d34fc]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205564) /* 0x7d34fc */);
    // 004d6b95  8b150c357d00           -mov edx, dword ptr [0x7d350c]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205580) /* 0x7d350c */);
    // 004d6b9b  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004d6ba0  750d                   -jne 0x4d6baf
    if (!cpu.flags.zf)
    {
        goto L_0x004d6baf;
    }
    // 004d6ba2  39c8                   +cmp eax, ecx
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
    // 004d6ba4  7c09                   -jl 0x4d6baf
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004d6baf;
    }
    // 004d6ba6  39d0                   +cmp eax, edx
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
    // 004d6ba8  7e0f                   -jle 0x4d6bb9
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004d6bb9;
    }
    // 004d6baa  83cb02                 +or ebx, 2
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(2 /*0x2*/))));
    // 004d6bad  eb0a                   -jmp 0x4d6bb9
    goto L_0x004d6bb9;
L_0x004d6baf:
    // 004d6baf  83cb01                 +or ebx, 1
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(1 /*0x1*/))));
    // 004d6bb2  eb05                   -jmp 0x4d6bb9
    goto L_0x004d6bb9;
L_0x004d6bb4:
    // 004d6bb4  bb10000000             -mov ebx, 0x10
    cpu.ebx = 16 /*0x10*/;
L_0x004d6bb9:
    // 004d6bb9  881f                   -mov byte ptr [edi], bl
    app->getMemory<x86::reg8>(cpu.edi) = cpu.bl;
    // 004d6bbb  bf243b5600             -mov edi, 0x563b24
    cpu.edi = 5651236 /*0x563b24*/;
    // 004d6bc0  be103b5600             -mov esi, 0x563b10
    cpu.esi = 5651216 /*0x563b10*/;
    // 004d6bc5  8b460c                 -mov eax, dword ptr [esi + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 004d6bc8  8b0df8347d00           -mov ecx, dword ptr [0x7d34f8]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205560) /* 0x7d34f8 */);
    // 004d6bce  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004d6bd3  7558                   -jne 0x4d6c2d
    if (!cpu.flags.zf)
    {
        goto L_0x004d6c2d;
    }
    // 004d6bd5  39c8                   +cmp eax, ecx
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
    // 004d6bd7  7d54                   -jge 0x4d6c2d
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004d6c2d;
    }
    // 004d6bd9  8b4604                 -mov eax, dword ptr [esi + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 004d6bdc  bb00000000             -mov ebx, 0
    cpu.ebx = 0 /*0x0*/;
    // 004d6be1  8b0d04357d00           -mov ecx, dword ptr [0x7d3504]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205572) /* 0x7d3504 */);
    // 004d6be7  8b1500357d00           -mov edx, dword ptr [0x7d3500]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205568) /* 0x7d3500 */);
    // 004d6bed  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004d6bf2  750d                   -jne 0x4d6c01
    if (!cpu.flags.zf)
    {
        goto L_0x004d6c01;
    }
    // 004d6bf4  39c8                   +cmp eax, ecx
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
    // 004d6bf6  7c09                   -jl 0x4d6c01
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004d6c01;
    }
    // 004d6bf8  39d0                   +cmp eax, edx
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
    // 004d6bfa  7e09                   -jle 0x4d6c05
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004d6c05;
    }
    // 004d6bfc  83cb04                 +or ebx, 4
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(4 /*0x4*/))));
    // 004d6bff  eb04                   -jmp 0x4d6c05
    goto L_0x004d6c05;
L_0x004d6c01:
    // 004d6c01  83cb08                 -or ebx, 8
    cpu.ebx |= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 004d6c04  90                     -nop 
    ;
L_0x004d6c05:
    // 004d6c05  8b06                   -mov eax, dword ptr [esi]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi);
    // 004d6c07  90                     -nop 
    ;
    // 004d6c08  8b0dfc347d00           -mov ecx, dword ptr [0x7d34fc]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205564) /* 0x7d34fc */);
    // 004d6c0e  8b150c357d00           -mov edx, dword ptr [0x7d350c]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205580) /* 0x7d350c */);
    // 004d6c14  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004d6c19  750d                   -jne 0x4d6c28
    if (!cpu.flags.zf)
    {
        goto L_0x004d6c28;
    }
    // 004d6c1b  39c8                   +cmp eax, ecx
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
    // 004d6c1d  7c09                   -jl 0x4d6c28
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004d6c28;
    }
    // 004d6c1f  39d0                   +cmp eax, edx
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
    // 004d6c21  7e0f                   -jle 0x4d6c32
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004d6c32;
    }
    // 004d6c23  83cb02                 +or ebx, 2
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(2 /*0x2*/))));
    // 004d6c26  eb0a                   -jmp 0x4d6c32
    goto L_0x004d6c32;
L_0x004d6c28:
    // 004d6c28  83cb01                 +or ebx, 1
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(1 /*0x1*/))));
    // 004d6c2b  eb05                   -jmp 0x4d6c32
    goto L_0x004d6c32;
L_0x004d6c2d:
    // 004d6c2d  bb10000000             -mov ebx, 0x10
    cpu.ebx = 16 /*0x10*/;
L_0x004d6c32:
    // 004d6c32  881f                   -mov byte ptr [edi], bl
    app->getMemory<x86::reg8>(cpu.edi) = cpu.bl;
    // 004d6c34  f605583a7a0002         +test byte ptr [0x7a3a58], 2
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(x86::reg32(8010328) /* 0x7a3a58 */) & 2 /*0x2*/));
    // 004d6c3b  7519                   -jne 0x4d6c56
    if (!cpu.flags.zf)
    {
        goto L_0x004d6c56;
    }
    // 004d6c3d  b9103b5600             -mov ecx, 0x563b10
    cpu.ecx = 5651216 /*0x563b10*/;
    // 004d6c42  bbf03a5600             -mov ebx, 0x563af0
    cpu.ebx = 5651184 /*0x563af0*/;
    // 004d6c47  bad03a5600             -mov edx, 0x563ad0
    cpu.edx = 5651152 /*0x563ad0*/;
    // 004d6c4c  b8b03a5600             -mov eax, 0x563ab0
    cpu.eax = 5651120 /*0x563ab0*/;
    // 004d6c51  e88aa6feff             -call 0x4c12e0
    cpu.esp -= 4;
    nfs3hp::vertices::clipQuad(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x004d6c56:
    // 004d6c56  ff45e4                 +inc dword ptr [ebp - 0x1c]
    {
        auto tmp = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-28) /* -0x1c */);
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 004d6c59  e95afcffff             -jmp 0x4d68b8
    goto L_0x004d68b8;
L_0x004d6c5e:
    // 004d6c5e  ff45dc                 +inc dword ptr [ebp - 0x24]
    {
        auto tmp = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-36) /* -0x24 */);
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 004d6c61  e90bfcffff             -jmp 0x4d6871
    goto L_0x004d6871;
L_0x004d6c66:
    // 004d6c66  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004d6c68  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d6c69  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d6c6a  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d6c6b  c20800                 -ret 8
    cpu.esp += 4+8 /*0x8*/;
    return;
}

/* align: skip 0x8b 0xc0 */
void Application::sub_4d6c70(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004d6c70  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004d6c71  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004d6c72  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004d6c73  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004d6c75  83ec3c                 -sub esp, 0x3c
    (cpu.esp) -= x86::reg32(x86::sreg32(60 /*0x3c*/));
    // 004d6c78  89d7                   -mov edi, edx
    cpu.edi = cpu.edx;
    // 004d6c7a  89de                   -mov esi, ebx
    cpu.esi = cpu.ebx;
    // 004d6c7c  894dd4                 -mov dword ptr [ebp - 0x2c], ecx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-44) /* -0x2c */) = cpu.ecx;
    // 004d6c7f  8b5510                 -mov edx, dword ptr [ebp + 0x10]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(16) /* 0x10 */);
    // 004d6c82  8955cc                 -mov dword ptr [ebp - 0x34], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-52) /* -0x34 */) = cpu.edx;
    // 004d6c85  db45cc                 -fild dword ptr [ebp - 0x34]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-52) /* -0x34 */)));
    // 004d6c88  dc0d74965400           -fmul qword ptr [0x549674]
    x86::Float fpu2 = cpu.fpu.mul(fpu1, x86::Float(app->getMemory<double>(x86::reg32(5543540) /* 0x549674 */)));
    // 004d6c8e  8b1534925500           -mov edx, dword ptr [0x559234]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5607988) /* 0x559234 */);
    // 004d6c94  d95de0                 -fstp dword ptr [ebp - 0x20]
    app->getMemory<float>(cpu.ebp + x86::reg32(-32) /* -0x20 */) = float(fpu2);
    // 004d6c97  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    }
    // 004d6c99  0f8542040000           -jne 0x4d70e1
    if (!cpu.flags.zf)
    {
        goto L_0x004d70e1;
    }
    // 004d6c9f  8d0c8500000000         -lea ecx, [eax*4]
    cpu.ecx = x86::reg32(cpu.eax * 4);
    // 004d6ca6  01c1                   -add ecx, eax
    (cpu.ecx) += x86::reg32(x86::sreg32(cpu.eax));
    // 004d6ca8  c1e102                 -shl ecx, 2
    cpu.ecx <<= 2 /*0x2*/ % 32;
    // 004d6cab  8b91ca488b00           -mov edx, dword ptr [ecx + 0x8b48ca]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(9128138) /* 0x8b48ca */);
    // 004d6cb1  c1fa10                 -sar edx, 0x10
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (16 /*0x10*/ % 32));
    // 004d6cb4  83faff                 +cmp edx, -1
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
    // 004d6cb7  7518                   -jne 0x4d6cd1
    if (!cpu.flags.zf)
    {
        goto L_0x004d6cd1;
    }
    // 004d6cb9  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004d6cba  6830965400             -push 0x549630
    app->getMemory<x86::reg32>(cpu.esp-4) = 5543472 /*0x549630*/;
    cpu.esp -= 4;
    // 004d6cbf  e83c68f5ff             -call 0x42d500
    cpu.esp -= 4;
    nfs3hp::raceload::emptyHook(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d6cc4  83c408                 +add esp, 8
    {
        x86::reg32& tmp1 = cpu.esp;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(8 /*0x8*/));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 004d6cc7  e854940100             -call 0x4f0120
    cpu.esp -= 4;
    nfs3hp::ea::inkey(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d6ccc  e910040000             -jmp 0x4d70e1
    goto L_0x004d70e1;
L_0x004d6cd1:
    // 004d6cd1  8b99c2488b00           -mov ebx, dword ptr [ecx + 0x8b48c2]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(9128130) /* 0x8b48c2 */);
    // 004d6cd7  c1fb10                 -sar ebx, 0x10
    cpu.ebx = x86::reg32(x86::sreg32(cpu.ebx) >> (16 /*0x10*/ % 32));
    // 004d6cda  c1e305                 -shl ebx, 5
    cpu.ebx <<= 5 /*0x5*/ % 32;
    // 004d6cdd  89da                   -mov edx, ebx
    cpu.edx = cpu.ebx;
    // 004d6cdf  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 004d6ce1  c1fa1f                 -sar edx, 0x1f
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (31 /*0x1f*/ % 32));
    // 004d6ce4  2bc2                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 004d6ce6  d1f8                   -sar eax, 1
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (1 /*0x1*/ % 32));
    // 004d6ce8  8b55d4                 -mov edx, dword ptr [ebp - 0x2c]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-44) /* -0x2c */);
    // 004d6ceb  29c2                   -sub edx, eax
    (cpu.edx) -= x86::reg32(x86::sreg32(cpu.eax));
    // 004d6ced  8b81c6488b00           -mov eax, dword ptr [ecx + 0x8b48c6]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(9128134) /* 0x8b48c6 */);
    // 004d6cf3  c1f810                 -sar eax, 0x10
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (16 /*0x10*/ % 32));
    // 004d6cf6  01c2                   -add edx, eax
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.eax));
    // 004d6cf8  8955cc                 -mov dword ptr [ebp - 0x34], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-52) /* -0x34 */) = cpu.edx;
    // 004d6cfb  8b91c4488b00           -mov edx, dword ptr [ecx + 0x8b48c4]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(9128132) /* 0x8b48c4 */);
    // 004d6d01  c1fa10                 -sar edx, 0x10
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (16 /*0x10*/ % 32));
    // 004d6d04  8955c8                 -mov dword ptr [ebp - 0x38], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-56) /* -0x38 */) = cpu.edx;
    // 004d6d07  f7da                   -neg edx
    cpu.edx = ~cpu.edx + 1;
    // 004d6d09  8955d0                 -mov dword ptr [ebp - 0x30], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-48) /* -0x30 */) = cpu.edx;
    // 004d6d0c  db45d0                 -fild dword ptr [ebp - 0x30]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu3 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-48) /* -0x30 */)));
    // 004d6d0f  d80d7c965400           -fmul dword ptr [0x54967c]
    x86::Float fpu4 = cpu.fpu.mul(fpu3, x86::Float(app->getMemory<float>(x86::reg32(5543548) /* 0x54967c */)));
    // 004d6d15  d80d80965400           -fmul dword ptr [0x549680]
    x86::Float fpu5 = cpu.fpu.mul(fpu4, x86::Float(app->getMemory<float>(x86::reg32(5543552) /* 0x549680 */)));
    // 004d6d1b  ff75e0                 -push dword ptr [ebp - 0x20]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-32) /* -0x20 */);
    cpu.esp -= 4;
    // 004d6d1e  d905ac3a5600           -fld dword ptr [0x563aac]
    x86::Float fpu6 = x86::Float(app->getMemory<float>(x86::reg32(5651116) /* 0x563aac */));
    // 004d6d24  8b15a83a5600           -mov edx, dword ptr [0x563aa8]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5651112) /* 0x563aa8 */);
    // 004d6d2a  8915183b5600           -mov dword ptr [0x563b18], edx
    app->getMemory<x86::reg32>(x86::reg32(5651224) /* 0x563b18 */) = cpu.edx;
    // 004d6d30  d9151c3b5600           -fst dword ptr [0x563b1c]
    app->getMemory<float>(x86::reg32(5651228) /* 0x563b1c */) = float(fpu6);
    // 004d6d36  8b15183b5600           -mov edx, dword ptr [0x563b18]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5651224) /* 0x563b18 */);
    // 004d6d3c  8915f83a5600           -mov dword ptr [0x563af8], edx
    app->getMemory<x86::reg32>(x86::reg32(5651192) /* 0x563af8 */) = cpu.edx;
    // 004d6d42  d915fc3a5600           -fst dword ptr [0x563afc]
    app->getMemory<float>(x86::reg32(5651196) /* 0x563afc */) = float(fpu6);
    // 004d6d48  8b15f83a5600           -mov edx, dword ptr [0x563af8]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5651192) /* 0x563af8 */);
    // 004d6d4e  8915d83a5600           -mov dword ptr [0x563ad8], edx
    app->getMemory<x86::reg32>(x86::reg32(5651160) /* 0x563ad8 */) = cpu.edx;
    // 004d6d54  d91ddc3a5600           -fstp dword ptr [0x563adc]
    app->getMemory<float>(x86::reg32(5651164) /* 0x563adc */) = float(fpu6);
    // 004d6d5a  d905d83a5600           -fld dword ptr [0x563ad8]
    x86::Float fpu7 = x86::Float(app->getMemory<float>(x86::reg32(5651160) /* 0x563ad8 */));
    // 004d6d60  d905dc3a5600           -fld dword ptr [0x563adc]
    x86::Float fpu8 = x86::Float(app->getMemory<float>(x86::reg32(5651164) /* 0x563adc */));
    // 004d6d66  895dd0                 -mov dword ptr [ebp - 0x30], ebx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-48) /* -0x30 */) = cpu.ebx;
    // 004d6d69  d9c9                   -fxch st(1)
    
    // 004d6d6b  d91db83a5600           -fstp dword ptr [0x563ab8]
    app->getMemory<float>(x86::reg32(5651128) /* 0x563ab8 */) = float(fpu7);
    // 004d6d71  db45d0                 -fild dword ptr [ebp - 0x30]
    x86::Float fpu9 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-48) /* -0x30 */)));
    // 004d6d74  01c0                   -add eax, eax
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.eax));
    // 004d6d76  db45cc                 -fild dword ptr [ebp - 0x34]
    x86::Float fpu10 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-52) /* -0x34 */)));
    // 004d6d79  d95df0                 -fstp dword ptr [ebp - 0x10]
    app->getMemory<float>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = float(fpu10);
    // 004d6d7c  8945d0                 -mov dword ptr [ebp - 0x30], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-48) /* -0x30 */) = cpu.eax;
    // 004d6d7f  d845f0                 -fadd dword ptr [ebp - 0x10]
    x86::Float fpu11 = cpu.fpu.add(fpu9, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-16) /* -0x10 */)));
    // 004d6d82  d9c9                   -fxch st(1)
    
    // 004d6d84  d91dbc3a5600           -fstp dword ptr [0x563abc]
    app->getMemory<float>(x86::reg32(5651132) /* 0x563abc */) = float(fpu8);
    // 004d6d8a  db45d0                 -fild dword ptr [ebp - 0x30]
    x86::Float fpu12 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-48) /* -0x30 */)));
    // 004d6d8d  8b45c8                 -mov eax, dword ptr [ebp - 0x38]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-56) /* -0x38 */);
    // 004d6d90  dee9                   -fsubp st(1)
    x86::Float fpu13 = cpu.fpu.sub(fpu11, fpu12);
    // 004d6d92  c1e005                 -shl eax, 5
    cpu.eax <<= 5 /*0x5*/ % 32;
    // 004d6d95  d95de8                 -fstp dword ptr [ebp - 0x18]
    app->getMemory<float>(cpu.ebp + x86::reg32(-24) /* -0x18 */) = float(fpu13);
    // 004d6d98  8945d0                 -mov dword ptr [ebp - 0x30], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-48) /* -0x30 */) = cpu.eax;
    // 004d6d9b  baf0302020             -mov edx, 0x202030f0
    cpu.edx = 538980592 /*0x202030f0*/;
    // 004d6da0  db45d0                 -fild dword ptr [ebp - 0x30]
    x86::Float fpu14 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-48) /* -0x30 */)));
    // 004d6da3  8915203b5600           -mov dword ptr [0x563b20], edx
    app->getMemory<x86::reg32>(x86::reg32(5651232) /* 0x563b20 */) = cpu.edx;
    // 004d6da9  8b81c8488b00           -mov eax, dword ptr [ecx + 0x8b48c8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(9128136) /* 0x8b48c8 */);
    // 004d6daf  8915003b5600           -mov dword ptr [0x563b00], edx
    app->getMemory<x86::reg32>(x86::reg32(5651200) /* 0x563b00 */) = cpu.edx;
    // 004d6db5  c1f810                 -sar eax, 0x10
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (16 /*0x10*/ % 32));
    // 004d6db8  df81ca488b00           -fild word ptr [ecx + 0x8b48ca]
    x86::Float fpu15 = x86::Float(x86::sreg16(app->getMemory<x86::reg16>(cpu.ecx + x86::reg32(9128138) /* 0x8b48ca */)));
    // 004d6dbe  01c0                   -add eax, eax
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.eax));
    // 004d6dc0  dec2                   -faddp st(2)
    x86::Float fpu16 = cpu.fpu.add(fpu5, fpu15);
    // 004d6dc2  8945d0                 -mov dword ptr [ebp - 0x30], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-48) /* -0x30 */) = cpu.eax;
    // 004d6dc5  d9c9                   -fxch st(1)
    
    // 004d6dc7  d95df4                 -fstp dword ptr [ebp - 0xc]
    app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */) = float(fpu16);
    // 004d6dca  d845f4                 -fadd dword ptr [ebp - 0xc]
    x86::Float fpu17 = cpu.fpu.add(fpu14, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */)));
    // 004d6dcd  8915e03a5600           -mov dword ptr [0x563ae0], edx
    app->getMemory<x86::reg32>(x86::reg32(5651168) /* 0x563ae0 */) = cpu.edx;
    // 004d6dd3  db45d0                 -fild dword ptr [ebp - 0x30]
    x86::Float fpu18 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-48) /* -0x30 */)));
    // 004d6dd6  dee9                   -fsubp st(1)
    x86::Float fpu19 = cpu.fpu.sub(fpu17, fpu18);
    // 004d6dd8  8915c03a5600           -mov dword ptr [0x563ac0], edx
    app->getMemory<x86::reg32>(x86::reg32(5651136) /* 0x563ac0 */) = cpu.edx;
    // 004d6dde  d95dec                 -fstp dword ptr [ebp - 0x14]
    app->getMemory<float>(cpu.ebp + x86::reg32(-20) /* -0x14 */) = float(fpu19);
    }
    // 004d6de1  e86a3b0100             -call 0x4ea950
    cpu.esp -= 4;
    sub_4ea950(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d6de6  ff75e0                 -push dword ptr [ebp - 0x20]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-32) /* -0x20 */);
    cpu.esp -= 4;
    // 004d6de9  d95dfc                 -fstp dword ptr [ebp - 4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu20 = cpu.fpu.st(0);
    app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = float(fpu20);
    cpu.fpu.count -= 1;
    }
    // 004d6dec  e83f3b0100             -call 0x4ea930
    cpu.esp -= 4;
    sub_4ea930(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d6df1  d945f0                 -fld dword ptr [ebp - 0x10]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu21 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-16) /* -0x10 */));
    // 004d6df4  d84dfc                 -fmul dword ptr [ebp - 4]
    x86::Float fpu22 = cpu.fpu.mul(fpu21, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 004d6df7  d945f4                 -fld dword ptr [ebp - 0xc]
    x86::Float fpu23 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */));
    // 004d6dfa  d9ca                   -fxch st(2)
    
    // 004d6dfc  d95df8                 -fstp dword ptr [ebp - 8]
    x86::Float fpu24 = cpu.fpu.st(0);
    app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = float(fpu24);
    // 004d6dff  d9c9                   -fxch st(1)
    
    // 004d6e01  d84df8                 -fmul dword ptr [ebp - 8]
    x86::Float fpu25 = cpu.fpu.mul(fpu23, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    // 004d6e04  d945e8                 -fld dword ptr [ebp - 0x18]
    x86::Float fpu26 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-24) /* -0x18 */));
    // 004d6e07  d84dfc                 -fmul dword ptr [ebp - 4]
    x86::Float fpu27 = cpu.fpu.mul(fpu26, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 004d6e0a  897dd0                 -mov dword ptr [ebp - 0x30], edi
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-48) /* -0x30 */) = cpu.edi;
    // 004d6e0d  d945ec                 -fld dword ptr [ebp - 0x14]
    x86::Float fpu28 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-20) /* -0x14 */));
    // 004d6e10  d84df8                 -fmul dword ptr [ebp - 8]
    x86::Float fpu29 = cpu.fpu.mul(fpu28, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    // 004d6e13  db45d0                 -fild dword ptr [ebp - 0x30]
    x86::Float fpu30 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-48) /* -0x30 */)));
    // 004d6e16  d9c0                   -fld st(0)
    x86::Float fpu31 = x86::Float(fpu30);
    // 004d6e18  d9cd                   -fxch st(5)
    
    // 004d6e1a  d95dd8                 -fstp dword ptr [ebp - 0x28]
    app->getMemory<float>(cpu.ebp + x86::reg32(-40) /* -0x28 */) = float(fpu22);
    // 004d6e1d  d9c9                   -fxch st(1)
    
    // 004d6e1f  d95de4                 -fstp dword ptr [ebp - 0x1c]
    app->getMemory<float>(cpu.ebp + x86::reg32(-28) /* -0x1c */) = float(fpu29);
    // 004d6e22  dec1                   -faddp st(1)
    x86::Float fpu32 = cpu.fpu.add(fpu27, fpu30);
    // 004d6e24  d9ca                   -fxch st(2)
    
    // 004d6e26  d845d8                 -fadd dword ptr [ebp - 0x28]
    x86::Float fpu33 = cpu.fpu.add(fpu31, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-40) /* -0x28 */)));
    // 004d6e29  d9c2                   -fld st(2)
    x86::Float fpu34 = x86::Float(fpu32);
    // 004d6e2b  d9c9                   -fxch st(1)
    
    // 004d6e2d  d955dc                 -fst dword ptr [ebp - 0x24]
    app->getMemory<float>(cpu.ebp + x86::reg32(-36) /* -0x24 */) = float(fpu33);
    // 004d6e30  d9c9                   -fxch st(1)
    
    // 004d6e32  d8e2                   -fsub st(2)
    x86::Float fpu35 = cpu.fpu.sub(fpu34, x86::Float(fpu25));
    // 004d6e34  d9cb                   -fxch st(3)
    
    // 004d6e36  d865e4                 -fsub dword ptr [ebp - 0x1c]
    x86::Float fpu36 = cpu.fpu.sub(fpu32, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-28) /* -0x1c */)));
    // 004d6e39  d9c9                   -fxch st(1)
    
    // 004d6e3b  dee2                   -fsubrp st(2)
    x86::Float fpu37 = cpu.fpu.sub(fpu33, x86::Float(fpu25));
    // 004d6e3d  d9ca                   -fxch st(2)
    
    // 004d6e3f  d91dd03a5600           -fstp dword ptr [0x563ad0]
    app->getMemory<float>(x86::reg32(5651152) /* 0x563ad0 */) = float(fpu35);
    // 004d6e45  d9c9                   -fxch st(1)
    
    // 004d6e47  d91df03a5600           -fstp dword ptr [0x563af0]
    app->getMemory<float>(x86::reg32(5651184) /* 0x563af0 */) = float(fpu36);
    // 004d6e4d  d91db03a5600           -fstp dword ptr [0x563ab0]
    app->getMemory<float>(x86::reg32(5651120) /* 0x563ab0 */) = float(fpu37);
    // 004d6e53  d945f8                 -fld dword ptr [ebp - 8]
    x86::Float fpu38 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */));
    // 004d6e56  d945f0                 -fld dword ptr [ebp - 0x10]
    x86::Float fpu39 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-16) /* -0x10 */));
    // 004d6e59  d8c9                   -fmul st(1)
    x86::Float fpu40 = cpu.fpu.mul(fpu39, x86::Float(fpu38));
    // 004d6e5b  d945fc                 -fld dword ptr [ebp - 4]
    x86::Float fpu41 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */));
    // 004d6e5e  d945f4                 -fld dword ptr [ebp - 0xc]
    x86::Float fpu42 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */));
    // 004d6e61  d8c9                   -fmul st(1)
    x86::Float fpu43 = cpu.fpu.mul(fpu42, x86::Float(fpu41));
    // 004d6e63  d945e8                 -fld dword ptr [ebp - 0x18]
    x86::Float fpu44 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-24) /* -0x18 */));
    // 004d6e66  decc                   -fmulp st(4)
    x86::Float fpu45 = cpu.fpu.mul(fpu38, fpu44);
    // 004d6e68  d945ec                 -fld dword ptr [ebp - 0x14]
    x86::Float fpu46 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-20) /* -0x14 */));
    // 004d6e6b  deca                   -fmulp st(2)
    x86::Float fpu47 = cpu.fpu.mul(fpu41, fpu46);
    // 004d6e6d  d945dc                 -fld dword ptr [ebp - 0x24]
    x86::Float fpu48 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-36) /* -0x24 */));
    // 004d6e70  b9000000a0             -mov ecx, 0xa0000000
    cpu.ecx = 2684354560 /*0xa0000000*/;
    // 004d6e75  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 004d6e7a  bfc43a5600             -mov edi, 0x563ac4
    cpu.edi = 5651140 /*0x563ac4*/;
    // 004d6e7f  8975d0                 -mov dword ptr [ebp - 0x30], esi
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-48) /* -0x30 */) = cpu.esi;
    // 004d6e82  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 004d6e84  db45d0                 -fild dword ptr [ebp - 0x30]
    x86::Float fpu49 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-48) /* -0x30 */)));
    // 004d6e87  beb03a5600             -mov esi, 0x563ab0
    cpu.esi = 5651120 /*0x563ab0*/;
    // 004d6e8c  d9c9                   -fxch st(1)
    
    // 004d6e8e  d865e4                 -fsub dword ptr [ebp - 0x1c]
    x86::Float fpu50 = cpu.fpu.sub(fpu48, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-28) /* -0x1c */)));
    // 004d6e91  890d203b5600           -mov dword ptr [0x563b20], ecx
    app->getMemory<x86::reg32>(x86::reg32(5651232) /* 0x563b20 */) = cpu.ecx;
    // 004d6e97  890d003b5600           -mov dword ptr [0x563b00], ecx
    app->getMemory<x86::reg32>(x86::reg32(5651200) /* 0x563b00 */) = cpu.ecx;
    // 004d6e9d  890de03a5600           -mov dword ptr [0x563ae0], ecx
    app->getMemory<x86::reg32>(x86::reg32(5651168) /* 0x563ae0 */) = cpu.ecx;
    // 004d6ea3  890dc03a5600           -mov dword ptr [0x563ac0], ecx
    app->getMemory<x86::reg32>(x86::reg32(5651136) /* 0x563ac0 */) = cpu.ecx;
    // 004d6ea9  d9c1                   -fld st(1)
    x86::Float fpu51 = x86::Float(fpu49);
    // 004d6eab  d9c9                   -fxch st(1)
    
    // 004d6ead  d91d103b5600           -fstp dword ptr [0x563b10]
    app->getMemory<float>(x86::reg32(5651216) /* 0x563b10 */) = float(fpu50);
    // 004d6eb3  d9cd                   -fxch st(5)
    
    // 004d6eb5  dec1                   -faddp st(1)
    x86::Float fpu52 = cpu.fpu.add(fpu49, fpu45);
    // 004d6eb7  d9cc                   -fxch st(4)
    
    // 004d6eb9  dec3                   -faddp st(3)
    x86::Float fpu53 = cpu.fpu.add(fpu40, fpu51);
    // 004d6ebb  d9c2                   -fld st(2)
    x86::Float fpu54 = x86::Float(fpu53);
    // 004d6ebd  d9c4                   -fld st(4)
    x86::Float fpu55 = x86::Float(fpu52);
    // 004d6ebf  d8c2                   -fadd st(2)
    x86::Float fpu56 = cpu.fpu.add(fpu55, x86::Float(fpu43));
    // 004d6ec1  d9cd                   -fxch st(5)
    
    // 004d6ec3  d8c3                   -fadd st(3)
    x86::Float fpu57 = cpu.fpu.add(fpu52, x86::Float(fpu47));
    // 004d6ec5  d9c9                   -fxch st(1)
    
    // 004d6ec7  dec2                   -faddp st(2)
    x86::Float fpu58 = cpu.fpu.add(fpu43, fpu54);
    // 004d6ec9  d9cc                   -fxch st(4)
    
    // 004d6ecb  d91dd43a5600           -fstp dword ptr [0x563ad4]
    app->getMemory<float>(x86::reg32(5651156) /* 0x563ad4 */) = float(fpu56);
    // 004d6ed1  d9cb                   -fxch st(3)
    
    // 004d6ed3  d91df43a5600           -fstp dword ptr [0x563af4]
    app->getMemory<float>(x86::reg32(5651188) /* 0x563af4 */) = float(fpu57);
    // 004d6ed9  dec1                   -faddp st(1)
    x86::Float fpu59 = cpu.fpu.add(fpu53, fpu47);
    // 004d6edb  d9c9                   -fxch st(1)
    
    // 004d6edd  d91db43a5600           -fstp dword ptr [0x563ab4]
    app->getMemory<float>(x86::reg32(5651124) /* 0x563ab4 */) = float(fpu58);
    // 004d6ee3  d91d143b5600           -fstp dword ptr [0x563b14]
    app->getMemory<float>(x86::reg32(5651220) /* 0x563b14 */) = float(fpu59);
    cpu.fpu.count -= 1;
    }
    // 004d6ee9  e812aaf5ff             -call 0x431900
    cpu.esp -= 4;
    nfs3hp::graphics::setRenderState(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d6eee  8b460c                 -mov eax, dword ptr [esi + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 004d6ef1  8b0df8347d00           -mov ecx, dword ptr [0x7d34f8]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205560) /* 0x7d34f8 */);
    // 004d6ef7  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004d6efc  7558                   -jne 0x4d6f56
    if (!cpu.flags.zf)
    {
        goto L_0x004d6f56;
    }
    // 004d6efe  39c8                   +cmp eax, ecx
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
    // 004d6f00  7d54                   -jge 0x4d6f56
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004d6f56;
    }
    // 004d6f02  8b4604                 -mov eax, dword ptr [esi + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 004d6f05  bb00000000             -mov ebx, 0
    cpu.ebx = 0 /*0x0*/;
    // 004d6f0a  8b0d04357d00           -mov ecx, dword ptr [0x7d3504]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205572) /* 0x7d3504 */);
    // 004d6f10  8b1500357d00           -mov edx, dword ptr [0x7d3500]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205568) /* 0x7d3500 */);
    // 004d6f16  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004d6f1b  750d                   -jne 0x4d6f2a
    if (!cpu.flags.zf)
    {
        goto L_0x004d6f2a;
    }
    // 004d6f1d  39c8                   +cmp eax, ecx
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
    // 004d6f1f  7c09                   -jl 0x4d6f2a
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004d6f2a;
    }
    // 004d6f21  39d0                   +cmp eax, edx
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
    // 004d6f23  7e09                   -jle 0x4d6f2e
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004d6f2e;
    }
    // 004d6f25  83cb04                 +or ebx, 4
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(4 /*0x4*/))));
    // 004d6f28  eb04                   -jmp 0x4d6f2e
    goto L_0x004d6f2e;
L_0x004d6f2a:
    // 004d6f2a  83cb08                 -or ebx, 8
    cpu.ebx |= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 004d6f2d  90                     -nop 
    ;
L_0x004d6f2e:
    // 004d6f2e  8b06                   -mov eax, dword ptr [esi]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi);
    // 004d6f30  90                     -nop 
    ;
    // 004d6f31  8b0dfc347d00           -mov ecx, dword ptr [0x7d34fc]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205564) /* 0x7d34fc */);
    // 004d6f37  8b150c357d00           -mov edx, dword ptr [0x7d350c]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205580) /* 0x7d350c */);
    // 004d6f3d  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004d6f42  750d                   -jne 0x4d6f51
    if (!cpu.flags.zf)
    {
        goto L_0x004d6f51;
    }
    // 004d6f44  39c8                   +cmp eax, ecx
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
    // 004d6f46  7c09                   -jl 0x4d6f51
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004d6f51;
    }
    // 004d6f48  39d0                   +cmp eax, edx
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
    // 004d6f4a  7e0f                   -jle 0x4d6f5b
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004d6f5b;
    }
    // 004d6f4c  83cb02                 +or ebx, 2
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(2 /*0x2*/))));
    // 004d6f4f  eb0a                   -jmp 0x4d6f5b
    goto L_0x004d6f5b;
L_0x004d6f51:
    // 004d6f51  83cb01                 +or ebx, 1
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(1 /*0x1*/))));
    // 004d6f54  eb05                   -jmp 0x4d6f5b
    goto L_0x004d6f5b;
L_0x004d6f56:
    // 004d6f56  bb10000000             -mov ebx, 0x10
    cpu.ebx = 16 /*0x10*/;
L_0x004d6f5b:
    // 004d6f5b  881f                   -mov byte ptr [edi], bl
    app->getMemory<x86::reg8>(cpu.edi) = cpu.bl;
    // 004d6f5d  bfe43a5600             -mov edi, 0x563ae4
    cpu.edi = 5651172 /*0x563ae4*/;
    // 004d6f62  bed03a5600             -mov esi, 0x563ad0
    cpu.esi = 5651152 /*0x563ad0*/;
    // 004d6f67  8b460c                 -mov eax, dword ptr [esi + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 004d6f6a  8b0df8347d00           -mov ecx, dword ptr [0x7d34f8]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205560) /* 0x7d34f8 */);
    // 004d6f70  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004d6f75  7558                   -jne 0x4d6fcf
    if (!cpu.flags.zf)
    {
        goto L_0x004d6fcf;
    }
    // 004d6f77  39c8                   +cmp eax, ecx
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
    // 004d6f79  7d54                   -jge 0x4d6fcf
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004d6fcf;
    }
    // 004d6f7b  8b4604                 -mov eax, dword ptr [esi + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 004d6f7e  bb00000000             -mov ebx, 0
    cpu.ebx = 0 /*0x0*/;
    // 004d6f83  8b0d04357d00           -mov ecx, dword ptr [0x7d3504]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205572) /* 0x7d3504 */);
    // 004d6f89  8b1500357d00           -mov edx, dword ptr [0x7d3500]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205568) /* 0x7d3500 */);
    // 004d6f8f  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004d6f94  750d                   -jne 0x4d6fa3
    if (!cpu.flags.zf)
    {
        goto L_0x004d6fa3;
    }
    // 004d6f96  39c8                   +cmp eax, ecx
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
    // 004d6f98  7c09                   -jl 0x4d6fa3
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004d6fa3;
    }
    // 004d6f9a  39d0                   +cmp eax, edx
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
    // 004d6f9c  7e09                   -jle 0x4d6fa7
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004d6fa7;
    }
    // 004d6f9e  83cb04                 +or ebx, 4
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(4 /*0x4*/))));
    // 004d6fa1  eb04                   -jmp 0x4d6fa7
    goto L_0x004d6fa7;
L_0x004d6fa3:
    // 004d6fa3  83cb08                 -or ebx, 8
    cpu.ebx |= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 004d6fa6  90                     -nop 
    ;
L_0x004d6fa7:
    // 004d6fa7  8b06                   -mov eax, dword ptr [esi]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi);
    // 004d6fa9  90                     -nop 
    ;
    // 004d6faa  8b0dfc347d00           -mov ecx, dword ptr [0x7d34fc]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205564) /* 0x7d34fc */);
    // 004d6fb0  8b150c357d00           -mov edx, dword ptr [0x7d350c]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205580) /* 0x7d350c */);
    // 004d6fb6  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004d6fbb  750d                   -jne 0x4d6fca
    if (!cpu.flags.zf)
    {
        goto L_0x004d6fca;
    }
    // 004d6fbd  39c8                   +cmp eax, ecx
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
    // 004d6fbf  7c09                   -jl 0x4d6fca
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004d6fca;
    }
    // 004d6fc1  39d0                   +cmp eax, edx
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
    // 004d6fc3  7e0f                   -jle 0x4d6fd4
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004d6fd4;
    }
    // 004d6fc5  83cb02                 +or ebx, 2
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(2 /*0x2*/))));
    // 004d6fc8  eb0a                   -jmp 0x4d6fd4
    goto L_0x004d6fd4;
L_0x004d6fca:
    // 004d6fca  83cb01                 +or ebx, 1
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(1 /*0x1*/))));
    // 004d6fcd  eb05                   -jmp 0x4d6fd4
    goto L_0x004d6fd4;
L_0x004d6fcf:
    // 004d6fcf  bb10000000             -mov ebx, 0x10
    cpu.ebx = 16 /*0x10*/;
L_0x004d6fd4:
    // 004d6fd4  881f                   -mov byte ptr [edi], bl
    app->getMemory<x86::reg8>(cpu.edi) = cpu.bl;
    // 004d6fd6  bf043b5600             -mov edi, 0x563b04
    cpu.edi = 5651204 /*0x563b04*/;
    // 004d6fdb  bef03a5600             -mov esi, 0x563af0
    cpu.esi = 5651184 /*0x563af0*/;
    // 004d6fe0  8b460c                 -mov eax, dword ptr [esi + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 004d6fe3  8b0df8347d00           -mov ecx, dword ptr [0x7d34f8]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205560) /* 0x7d34f8 */);
    // 004d6fe9  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004d6fee  7558                   -jne 0x4d7048
    if (!cpu.flags.zf)
    {
        goto L_0x004d7048;
    }
    // 004d6ff0  39c8                   +cmp eax, ecx
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
    // 004d6ff2  7d54                   -jge 0x4d7048
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004d7048;
    }
    // 004d6ff4  8b4604                 -mov eax, dword ptr [esi + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 004d6ff7  bb00000000             -mov ebx, 0
    cpu.ebx = 0 /*0x0*/;
    // 004d6ffc  8b0d04357d00           -mov ecx, dword ptr [0x7d3504]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205572) /* 0x7d3504 */);
    // 004d7002  8b1500357d00           -mov edx, dword ptr [0x7d3500]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205568) /* 0x7d3500 */);
    // 004d7008  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004d700d  750d                   -jne 0x4d701c
    if (!cpu.flags.zf)
    {
        goto L_0x004d701c;
    }
    // 004d700f  39c8                   +cmp eax, ecx
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
    // 004d7011  7c09                   -jl 0x4d701c
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004d701c;
    }
    // 004d7013  39d0                   +cmp eax, edx
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
    // 004d7015  7e09                   -jle 0x4d7020
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004d7020;
    }
    // 004d7017  83cb04                 +or ebx, 4
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(4 /*0x4*/))));
    // 004d701a  eb04                   -jmp 0x4d7020
    goto L_0x004d7020;
L_0x004d701c:
    // 004d701c  83cb08                 -or ebx, 8
    cpu.ebx |= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 004d701f  90                     -nop 
    ;
L_0x004d7020:
    // 004d7020  8b06                   -mov eax, dword ptr [esi]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi);
    // 004d7022  90                     -nop 
    ;
    // 004d7023  8b0dfc347d00           -mov ecx, dword ptr [0x7d34fc]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205564) /* 0x7d34fc */);
    // 004d7029  8b150c357d00           -mov edx, dword ptr [0x7d350c]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205580) /* 0x7d350c */);
    // 004d702f  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004d7034  750d                   -jne 0x4d7043
    if (!cpu.flags.zf)
    {
        goto L_0x004d7043;
    }
    // 004d7036  39c8                   +cmp eax, ecx
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
    // 004d7038  7c09                   -jl 0x4d7043
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004d7043;
    }
    // 004d703a  39d0                   +cmp eax, edx
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
    // 004d703c  7e0f                   -jle 0x4d704d
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004d704d;
    }
    // 004d703e  83cb02                 +or ebx, 2
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(2 /*0x2*/))));
    // 004d7041  eb0a                   -jmp 0x4d704d
    goto L_0x004d704d;
L_0x004d7043:
    // 004d7043  83cb01                 +or ebx, 1
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(1 /*0x1*/))));
    // 004d7046  eb05                   -jmp 0x4d704d
    goto L_0x004d704d;
L_0x004d7048:
    // 004d7048  bb10000000             -mov ebx, 0x10
    cpu.ebx = 16 /*0x10*/;
L_0x004d704d:
    // 004d704d  881f                   -mov byte ptr [edi], bl
    app->getMemory<x86::reg8>(cpu.edi) = cpu.bl;
    // 004d704f  bf243b5600             -mov edi, 0x563b24
    cpu.edi = 5651236 /*0x563b24*/;
    // 004d7054  be103b5600             -mov esi, 0x563b10
    cpu.esi = 5651216 /*0x563b10*/;
    // 004d7059  8b460c                 -mov eax, dword ptr [esi + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 004d705c  8b0df8347d00           -mov ecx, dword ptr [0x7d34f8]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205560) /* 0x7d34f8 */);
    // 004d7062  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004d7067  7558                   -jne 0x4d70c1
    if (!cpu.flags.zf)
    {
        goto L_0x004d70c1;
    }
    // 004d7069  39c8                   +cmp eax, ecx
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
    // 004d706b  7d54                   -jge 0x4d70c1
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004d70c1;
    }
    // 004d706d  8b4604                 -mov eax, dword ptr [esi + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 004d7070  bb00000000             -mov ebx, 0
    cpu.ebx = 0 /*0x0*/;
    // 004d7075  8b0d04357d00           -mov ecx, dword ptr [0x7d3504]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205572) /* 0x7d3504 */);
    // 004d707b  8b1500357d00           -mov edx, dword ptr [0x7d3500]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205568) /* 0x7d3500 */);
    // 004d7081  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004d7086  750d                   -jne 0x4d7095
    if (!cpu.flags.zf)
    {
        goto L_0x004d7095;
    }
    // 004d7088  39c8                   +cmp eax, ecx
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
    // 004d708a  7c09                   -jl 0x4d7095
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004d7095;
    }
    // 004d708c  39d0                   +cmp eax, edx
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
    // 004d708e  7e09                   -jle 0x4d7099
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004d7099;
    }
    // 004d7090  83cb04                 +or ebx, 4
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(4 /*0x4*/))));
    // 004d7093  eb04                   -jmp 0x4d7099
    goto L_0x004d7099;
L_0x004d7095:
    // 004d7095  83cb08                 -or ebx, 8
    cpu.ebx |= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 004d7098  90                     -nop 
    ;
L_0x004d7099:
    // 004d7099  8b06                   -mov eax, dword ptr [esi]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi);
    // 004d709b  90                     -nop 
    ;
    // 004d709c  8b0dfc347d00           -mov ecx, dword ptr [0x7d34fc]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205564) /* 0x7d34fc */);
    // 004d70a2  8b150c357d00           -mov edx, dword ptr [0x7d350c]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205580) /* 0x7d350c */);
    // 004d70a8  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004d70ad  750d                   -jne 0x4d70bc
    if (!cpu.flags.zf)
    {
        goto L_0x004d70bc;
    }
    // 004d70af  39c8                   +cmp eax, ecx
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
    // 004d70b1  7c09                   -jl 0x4d70bc
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004d70bc;
    }
    // 004d70b3  39d0                   +cmp eax, edx
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
    // 004d70b5  7e0f                   -jle 0x4d70c6
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004d70c6;
    }
    // 004d70b7  83cb02                 +or ebx, 2
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(2 /*0x2*/))));
    // 004d70ba  eb0a                   -jmp 0x4d70c6
    goto L_0x004d70c6;
L_0x004d70bc:
    // 004d70bc  83cb01                 +or ebx, 1
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(1 /*0x1*/))));
    // 004d70bf  eb05                   -jmp 0x4d70c6
    goto L_0x004d70c6;
L_0x004d70c1:
    // 004d70c1  bb10000000             -mov ebx, 0x10
    cpu.ebx = 16 /*0x10*/;
L_0x004d70c6:
    // 004d70c6  881f                   -mov byte ptr [edi], bl
    app->getMemory<x86::reg8>(cpu.edi) = cpu.bl;
    // 004d70c8  b9103b5600             -mov ecx, 0x563b10
    cpu.ecx = 5651216 /*0x563b10*/;
    // 004d70cd  bbf03a5600             -mov ebx, 0x563af0
    cpu.ebx = 5651184 /*0x563af0*/;
    // 004d70d2  bad03a5600             -mov edx, 0x563ad0
    cpu.edx = 5651152 /*0x563ad0*/;
    // 004d70d7  b8b03a5600             -mov eax, 0x563ab0
    cpu.eax = 5651120 /*0x563ab0*/;
    // 004d70dc  e8ffa1feff             -call 0x4c12e0
    cpu.esp -= 4;
    nfs3hp::vertices::clipQuad(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x004d70e1:
    // 004d70e1  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004d70e3  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d70e4  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d70e5  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d70e6  c20400                 -ret 4
    cpu.esp += 4+4 /*0x4*/;
    return;
}

/* sub_4d70f0: native, nfs3hp::port::shapes::drawShapeQuad */

/* sub_4d7160: native, nfs3hp::port::shapes::drawArtShape */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x90 */
void Application::sub_4d7560(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004d7560  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004d7561  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004d7562  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004d7563  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004d7564  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004d7566  83ec1c                 -sub esp, 0x1c
    (cpu.esp) -= x86::reg32(x86::sreg32(28 /*0x1c*/));
    // 004d7569  8945ec                 -mov dword ptr [ebp - 0x14], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */) = cpu.eax;
    // 004d756c  8955e8                 -mov dword ptr [ebp - 0x18], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-24) /* -0x18 */) = cpu.edx;
    // 004d756f  895de4                 -mov dword ptr [ebp - 0x1c], ebx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-28) /* -0x1c */) = cpu.ebx;
    // 004d7572  f605583a7a0002         +test byte ptr [0x7a3a58], 2
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(x86::reg32(8010328) /* 0x7a3a58 */) & 2 /*0x2*/));
    // 004d7579  0f8506040000           -jne 0x4d7985
    if (!cpu.flags.zf)
    {
        goto L_0x004d7985;
    }
    // 004d757f  833d3492550000         +cmp dword ptr [0x559234], 0
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
    // 004d7586  0f85f9030000           -jne 0x4d7985
    if (!cpu.flags.zf)
    {
        goto L_0x004d7985;
    }
    // 004d758c  8b55ec                 -mov edx, dword ptr [ebp - 0x14]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */);
    // 004d758f  8d049500000000         -lea eax, [edx*4]
    cpu.eax = x86::reg32(cpu.edx * 4);
    // 004d7596  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 004d7598  8b0485ca488b00         -mov eax, dword ptr [eax*4 + 0x8b48ca]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(9128138) /* 0x8b48ca */ + cpu.eax * 4);
    // 004d759f  c1f810                 -sar eax, 0x10
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (16 /*0x10*/ % 32));
    // 004d75a2  8945f4                 -mov dword ptr [ebp - 0xc], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.eax;
    // 004d75a5  83f8ff                 +cmp eax, -1
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
    // 004d75a8  7518                   -jne 0x4d75c2
    if (!cpu.flags.zf)
    {
        goto L_0x004d75c2;
    }
    // 004d75aa  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004d75ab  6830965400             -push 0x549630
    app->getMemory<x86::reg32>(cpu.esp-4) = 5543472 /*0x549630*/;
    cpu.esp -= 4;
    // 004d75b0  e84b5ff5ff             -call 0x42d500
    cpu.esp -= 4;
    nfs3hp::raceload::emptyHook(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d75b5  83c408                 +add esp, 8
    {
        x86::reg32& tmp1 = cpu.esp;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(8 /*0x8*/));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 004d75b8  e8638b0100             -call 0x4f0120
    cpu.esp -= 4;
    nfs3hp::ea::inkey(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d75bd  e9c3030000             -jmp 0x4d7985
    goto L_0x004d7985;
L_0x004d75c2:
    // 004d75c2  d905a83a5600           -fld dword ptr [0x563aa8]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(x86::reg32(5651112) /* 0x563aa8 */));
    // 004d75c8  d905ac3a5600           -fld dword ptr [0x563aac]
    x86::Float fpu2 = x86::Float(app->getMemory<float>(x86::reg32(5651116) /* 0x563aac */));
    // 004d75ce  beffffffff             -mov esi, 0xffffffff
    cpu.esi = 4294967295 /*0xffffffff*/;
    // 004d75d3  d9c9                   -fxch st(1)
    
    // 004d75d5  d91d183b5600           -fstp dword ptr [0x563b18]
    app->getMemory<float>(x86::reg32(5651224) /* 0x563b18 */) = float(fpu1);
    // 004d75db  d91d1c3b5600           -fstp dword ptr [0x563b1c]
    app->getMemory<float>(x86::reg32(5651228) /* 0x563b1c */) = float(fpu2);
    // 004d75e1  8945f0                 -mov dword ptr [ebp - 0x10], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = cpu.eax;
    // 004d75e4  d9051c3b5600           -fld dword ptr [0x563b1c]
    x86::Float fpu3 = x86::Float(app->getMemory<float>(x86::reg32(5651228) /* 0x563b1c */));
    // 004d75ea  a1183b5600             -mov eax, dword ptr [0x563b18]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5651224) /* 0x563b18 */);
    // 004d75ef  a3f83a5600             -mov dword ptr [0x563af8], eax
    app->getMemory<x86::reg32>(x86::reg32(5651192) /* 0x563af8 */) = cpu.eax;
    // 004d75f4  d91dfc3a5600           -fstp dword ptr [0x563afc]
    app->getMemory<float>(x86::reg32(5651196) /* 0x563afc */) = float(fpu3);
    // 004d75fa  8935203b5600           -mov dword ptr [0x563b20], esi
    app->getMemory<x86::reg32>(x86::reg32(5651232) /* 0x563b20 */) = cpu.esi;
    // 004d7600  8935003b5600           -mov dword ptr [0x563b00], esi
    app->getMemory<x86::reg32>(x86::reg32(5651200) /* 0x563b00 */) = cpu.esi;
    // 004d7606  8935e03a5600           -mov dword ptr [0x563ae0], esi
    app->getMemory<x86::reg32>(x86::reg32(5651168) /* 0x563ae0 */) = cpu.esi;
    // 004d760c  8935c03a5600           -mov dword ptr [0x563ac0], esi
    app->getMemory<x86::reg32>(x86::reg32(5651136) /* 0x563ac0 */) = cpu.esi;
    // 004d7612  d905fc3a5600           -fld dword ptr [0x563afc]
    x86::Float fpu4 = x86::Float(app->getMemory<float>(x86::reg32(5651196) /* 0x563afc */));
    // 004d7618  a1f83a5600             -mov eax, dword ptr [0x563af8]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5651192) /* 0x563af8 */);
    // 004d761d  a3d83a5600             -mov dword ptr [0x563ad8], eax
    app->getMemory<x86::reg32>(x86::reg32(5651160) /* 0x563ad8 */) = cpu.eax;
    // 004d7622  d915dc3a5600           -fst dword ptr [0x563adc]
    app->getMemory<float>(x86::reg32(5651164) /* 0x563adc */) = float(fpu4);
    // 004d7628  a1d83a5600             -mov eax, dword ptr [0x563ad8]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5651160) /* 0x563ad8 */);
    // 004d762d  a3b83a5600             -mov dword ptr [0x563ab8], eax
    app->getMemory<x86::reg32>(x86::reg32(5651128) /* 0x563ab8 */) = cpu.eax;
    // 004d7632  d91dbc3a5600           -fstp dword ptr [0x563abc]
    app->getMemory<float>(x86::reg32(5651132) /* 0x563abc */) = float(fpu4);
    }
L_0x004d7638:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004d7638  8b55ec                 -mov edx, dword ptr [ebp - 0x14]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */);
    // 004d763b  8d1c9500000000         -lea ebx, [edx*4]
    cpu.ebx = x86::reg32(cpu.edx * 4);
    // 004d7642  01d3                   -add ebx, edx
    (cpu.ebx) += x86::reg32(x86::sreg32(cpu.edx));
    // 004d7644  c1e302                 -shl ebx, 2
    cpu.ebx <<= 2 /*0x2*/ % 32;
    // 004d7647  8b83cc488b00           -mov eax, dword ptr [ebx + 0x8b48cc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(9128140) /* 0x8b48cc */);
    // 004d764d  8b4df0                 -mov ecx, dword ptr [ebp - 0x10]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 004d7650  c1f810                 -sar eax, 0x10
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (16 /*0x10*/ % 32));
    // 004d7653  39c8                   +cmp eax, ecx
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
    // 004d7655  0f8ef3020000           -jle 0x4d794e
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004d794e;
    }
    // 004d765b  8b55f4                 -mov edx, dword ptr [ebp - 0xc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 004d765e  8b75e4                 -mov esi, dword ptr [ebp - 0x1c]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-28) /* -0x1c */);
    // 004d7661  bf0000803f             -mov edi, 0x3f800000
    cpu.edi = 1065353216 /*0x3f800000*/;
    // 004d7666  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 004d7668  8d049500000000         -lea eax, [edx*4]
    cpu.eax = x86::reg32(cpu.edx * 4);
    // 004d766f  893d283b5600           -mov dword ptr [0x563b28], edi
    app->getMemory<x86::reg32>(x86::reg32(5651240) /* 0x563b28 */) = cpu.edi;
    // 004d7675  893dc83a5600           -mov dword ptr [0x563ac8], edi
    app->getMemory<x86::reg32>(x86::reg32(5651144) /* 0x563ac8 */) = cpu.edi;
    // 004d767b  890d083b5600           -mov dword ptr [0x563b08], ecx
    app->getMemory<x86::reg32>(x86::reg32(5651208) /* 0x563b08 */) = cpu.ecx;
    // 004d7681  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 004d7683  890de83a5600           -mov dword ptr [0x563ae8], ecx
    app->getMemory<x86::reg32>(x86::reg32(5651176) /* 0x563ae8 */) = cpu.ecx;
    // 004d7689  890dec3a5600           -mov dword ptr [0x563aec], ecx
    app->getMemory<x86::reg32>(x86::reg32(5651180) /* 0x563aec */) = cpu.ecx;
    // 004d768f  8b148594508b00         -mov edx, dword ptr [eax*4 + 0x8b5094]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(9130132) /* 0x8b5094 */ + cpu.eax * 4);
    // 004d7696  890dcc3a5600           -mov dword ptr [0x563acc], ecx
    app->getMemory<x86::reg32>(x86::reg32(5651148) /* 0x563acc */) = cpu.ecx;
    // 004d769c  c1fa10                 -sar edx, 0x10
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (16 /*0x10*/ % 32));
    // 004d769f  893d2c3b5600           -mov dword ptr [0x563b2c], edi
    app->getMemory<x86::reg32>(x86::reg32(5651244) /* 0x563b2c */) = cpu.edi;
    // 004d76a5  c1e205                 -shl edx, 5
    cpu.edx <<= 5 /*0x5*/ % 32;
    // 004d76a8  893d0c3b5600           -mov dword ptr [0x563b0c], edi
    app->getMemory<x86::reg32>(x86::reg32(5651212) /* 0x563b0c */) = cpu.edi;
    // 004d76ae  83c220                 -add edx, 0x20
    (cpu.edx) += x86::reg32(x86::sreg32(32 /*0x20*/));
    // 004d76b1  bfc43a5600             -mov edi, 0x563ac4
    cpu.edi = 5651140 /*0x563ac4*/;
    // 004d76b6  8955fc                 -mov dword ptr [ebp - 4], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.edx;
    // 004d76b9  8b93be488b00           -mov edx, dword ptr [ebx + 0x8b48be]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(9128126) /* 0x8b48be */);
    // 004d76bf  8b5de8                 -mov ebx, dword ptr [ebp - 0x18]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-24) /* -0x18 */);
    // 004d76c2  c1fa10                 -sar edx, 0x10
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (16 /*0x10*/ % 32));
    // 004d76c5  df048594508b00         -fild word ptr [eax*4 + 0x8b5094]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu5 = x86::Float(x86::sreg16(app->getMemory<x86::reg16>(x86::reg32(9130132) /* 0x8b5094 */ + cpu.eax * 4)));
    // 004d76cc  01da                   -add edx, ebx
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.ebx));
    // 004d76ce  db45fc                 -fild dword ptr [ebp - 4]
    x86::Float fpu6 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 004d76d1  8955fc                 -mov dword ptr [ebp - 4], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.edx;
    // 004d76d4  8b5df4                 -mov ebx, dword ptr [ebp - 0xc]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 004d76d7  db45fc                 -fild dword ptr [ebp - 4]
    x86::Float fpu7 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 004d76da  8b148596508b00         -mov edx, dword ptr [eax*4 + 0x8b5096]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(9130134) /* 0x8b5096 */ + cpu.eax * 4);
    // 004d76e1  43                     -inc ebx
    (cpu.ebx)++;
    // 004d76e2  c1fa10                 -sar edx, 0x10
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (16 /*0x10*/ % 32));
    // 004d76e5  dee1                   -fsubrp st(1)
    x86::Float fpu8 = cpu.fpu.sub(fpu7, x86::Float(fpu6));
    // 004d76e7  895df4                 -mov dword ptr [ebp - 0xc], ebx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.ebx;
    // 004d76ea  d915103b5600           -fst dword ptr [0x563b10]
    app->getMemory<float>(x86::reg32(5651216) /* 0x563b10 */) = float(fpu8);
    // 004d76f0  c1e205                 -shl edx, 5
    cpu.edx <<= 5 /*0x5*/ % 32;
    // 004d76f3  d915b03a5600           -fst dword ptr [0x563ab0]
    app->getMemory<float>(x86::reg32(5651120) /* 0x563ab0 */) = float(fpu8);
    // 004d76f9  01f2                   -add edx, esi
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.esi));
    // 004d76fb  beb03a5600             -mov esi, 0x563ab0
    cpu.esi = 5651120 /*0x563ab0*/;
    // 004d7700  8955fc                 -mov dword ptr [ebp - 4], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.edx;
    // 004d7703  d8c1                   -fadd st(1)
    x86::Float fpu9 = cpu.fpu.add(fpu8, x86::Float(fpu5));
    // 004d7705  db45fc                 -fild dword ptr [ebp - 4]
    x86::Float fpu10 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 004d7708  d9c9                   -fxch st(1)
    
    // 004d770a  d91df03a5600           -fstp dword ptr [0x563af0]
    app->getMemory<float>(x86::reg32(5651184) /* 0x563af0 */) = float(fpu9);
    // 004d7710  d91dd43a5600           -fstp dword ptr [0x563ad4]
    app->getMemory<float>(x86::reg32(5651156) /* 0x563ad4 */) = float(fpu10);
    // 004d7716  8b148590508b00         -mov edx, dword ptr [eax*4 + 0x8b5090]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(9130128) /* 0x8b5090 */ + cpu.eax * 4);
    // 004d771d  d905f03a5600           -fld dword ptr [0x563af0]
    x86::Float fpu11 = x86::Float(app->getMemory<float>(x86::reg32(5651184) /* 0x563af0 */));
    // 004d7723  d905d43a5600           -fld dword ptr [0x563ad4]
    x86::Float fpu12 = x86::Float(app->getMemory<float>(x86::reg32(5651156) /* 0x563ad4 */));
    // 004d7729  d9c0                   -fld st(0)
    x86::Float fpu13 = x86::Float(fpu12);
    // 004d772b  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 004d7730  d9ca                   -fxch st(2)
    
    // 004d7732  d91dd03a5600           -fstp dword ptr [0x563ad0]
    app->getMemory<float>(x86::reg32(5651152) /* 0x563ad0 */) = float(fpu11);
    // 004d7738  d9c9                   -fxch st(1)
    
    // 004d773a  dec2                   -faddp st(2)
    x86::Float fpu14 = cpu.fpu.add(fpu5, fpu13);
    // 004d773c  d91db43a5600           -fstp dword ptr [0x563ab4]
    app->getMemory<float>(x86::reg32(5651124) /* 0x563ab4 */) = float(fpu12);
    // 004d7742  d915143b5600           -fst dword ptr [0x563b14]
    app->getMemory<float>(x86::reg32(5651220) /* 0x563b14 */) = float(fpu14);
    // 004d7748  d91df43a5600           -fstp dword ptr [0x563af4]
    app->getMemory<float>(x86::reg32(5651188) /* 0x563af4 */) = float(fpu14);
    }
    // 004d774e  e8ada1f5ff             -call 0x431900
    cpu.esp -= 4;
    nfs3hp::graphics::setRenderState(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d7753  8b460c                 -mov eax, dword ptr [esi + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 004d7756  8b0df8347d00           -mov ecx, dword ptr [0x7d34f8]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205560) /* 0x7d34f8 */);
    // 004d775c  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004d7761  7558                   -jne 0x4d77bb
    if (!cpu.flags.zf)
    {
        goto L_0x004d77bb;
    }
    // 004d7763  39c8                   +cmp eax, ecx
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
    // 004d7765  7d54                   -jge 0x4d77bb
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004d77bb;
    }
    // 004d7767  8b4604                 -mov eax, dword ptr [esi + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 004d776a  bb00000000             -mov ebx, 0
    cpu.ebx = 0 /*0x0*/;
    // 004d776f  8b0d04357d00           -mov ecx, dword ptr [0x7d3504]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205572) /* 0x7d3504 */);
    // 004d7775  8b1500357d00           -mov edx, dword ptr [0x7d3500]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205568) /* 0x7d3500 */);
    // 004d777b  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004d7780  750d                   -jne 0x4d778f
    if (!cpu.flags.zf)
    {
        goto L_0x004d778f;
    }
    // 004d7782  39c8                   +cmp eax, ecx
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
    // 004d7784  7c09                   -jl 0x4d778f
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004d778f;
    }
    // 004d7786  39d0                   +cmp eax, edx
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
    // 004d7788  7e09                   -jle 0x4d7793
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004d7793;
    }
    // 004d778a  83cb04                 +or ebx, 4
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(4 /*0x4*/))));
    // 004d778d  eb04                   -jmp 0x4d7793
    goto L_0x004d7793;
L_0x004d778f:
    // 004d778f  83cb08                 -or ebx, 8
    cpu.ebx |= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 004d7792  90                     -nop 
    ;
L_0x004d7793:
    // 004d7793  8b06                   -mov eax, dword ptr [esi]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi);
    // 004d7795  90                     -nop 
    ;
    // 004d7796  8b0dfc347d00           -mov ecx, dword ptr [0x7d34fc]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205564) /* 0x7d34fc */);
    // 004d779c  8b150c357d00           -mov edx, dword ptr [0x7d350c]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205580) /* 0x7d350c */);
    // 004d77a2  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004d77a7  750d                   -jne 0x4d77b6
    if (!cpu.flags.zf)
    {
        goto L_0x004d77b6;
    }
    // 004d77a9  39c8                   +cmp eax, ecx
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
    // 004d77ab  7c09                   -jl 0x4d77b6
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004d77b6;
    }
    // 004d77ad  39d0                   +cmp eax, edx
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
    // 004d77af  7e0f                   -jle 0x4d77c0
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004d77c0;
    }
    // 004d77b1  83cb02                 +or ebx, 2
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(2 /*0x2*/))));
    // 004d77b4  eb0a                   -jmp 0x4d77c0
    goto L_0x004d77c0;
L_0x004d77b6:
    // 004d77b6  83cb01                 +or ebx, 1
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(1 /*0x1*/))));
    // 004d77b9  eb05                   -jmp 0x4d77c0
    goto L_0x004d77c0;
L_0x004d77bb:
    // 004d77bb  bb10000000             -mov ebx, 0x10
    cpu.ebx = 16 /*0x10*/;
L_0x004d77c0:
    // 004d77c0  881f                   -mov byte ptr [edi], bl
    app->getMemory<x86::reg8>(cpu.edi) = cpu.bl;
    // 004d77c2  bfe43a5600             -mov edi, 0x563ae4
    cpu.edi = 5651172 /*0x563ae4*/;
    // 004d77c7  bed03a5600             -mov esi, 0x563ad0
    cpu.esi = 5651152 /*0x563ad0*/;
    // 004d77cc  8b460c                 -mov eax, dword ptr [esi + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 004d77cf  8b0df8347d00           -mov ecx, dword ptr [0x7d34f8]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205560) /* 0x7d34f8 */);
    // 004d77d5  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004d77da  7558                   -jne 0x4d7834
    if (!cpu.flags.zf)
    {
        goto L_0x004d7834;
    }
    // 004d77dc  39c8                   +cmp eax, ecx
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
    // 004d77de  7d54                   -jge 0x4d7834
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004d7834;
    }
    // 004d77e0  8b4604                 -mov eax, dword ptr [esi + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 004d77e3  bb00000000             -mov ebx, 0
    cpu.ebx = 0 /*0x0*/;
    // 004d77e8  8b0d04357d00           -mov ecx, dword ptr [0x7d3504]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205572) /* 0x7d3504 */);
    // 004d77ee  8b1500357d00           -mov edx, dword ptr [0x7d3500]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205568) /* 0x7d3500 */);
    // 004d77f4  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004d77f9  750d                   -jne 0x4d7808
    if (!cpu.flags.zf)
    {
        goto L_0x004d7808;
    }
    // 004d77fb  39c8                   +cmp eax, ecx
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
    // 004d77fd  7c09                   -jl 0x4d7808
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004d7808;
    }
    // 004d77ff  39d0                   +cmp eax, edx
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
    // 004d7801  7e09                   -jle 0x4d780c
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004d780c;
    }
    // 004d7803  83cb04                 +or ebx, 4
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(4 /*0x4*/))));
    // 004d7806  eb04                   -jmp 0x4d780c
    goto L_0x004d780c;
L_0x004d7808:
    // 004d7808  83cb08                 -or ebx, 8
    cpu.ebx |= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 004d780b  90                     -nop 
    ;
L_0x004d780c:
    // 004d780c  8b06                   -mov eax, dword ptr [esi]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi);
    // 004d780e  90                     -nop 
    ;
    // 004d780f  8b0dfc347d00           -mov ecx, dword ptr [0x7d34fc]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205564) /* 0x7d34fc */);
    // 004d7815  8b150c357d00           -mov edx, dword ptr [0x7d350c]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205580) /* 0x7d350c */);
    // 004d781b  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004d7820  750d                   -jne 0x4d782f
    if (!cpu.flags.zf)
    {
        goto L_0x004d782f;
    }
    // 004d7822  39c8                   +cmp eax, ecx
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
    // 004d7824  7c09                   -jl 0x4d782f
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004d782f;
    }
    // 004d7826  39d0                   +cmp eax, edx
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
    // 004d7828  7e0f                   -jle 0x4d7839
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004d7839;
    }
    // 004d782a  83cb02                 +or ebx, 2
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(2 /*0x2*/))));
    // 004d782d  eb0a                   -jmp 0x4d7839
    goto L_0x004d7839;
L_0x004d782f:
    // 004d782f  83cb01                 +or ebx, 1
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(1 /*0x1*/))));
    // 004d7832  eb05                   -jmp 0x4d7839
    goto L_0x004d7839;
L_0x004d7834:
    // 004d7834  bb10000000             -mov ebx, 0x10
    cpu.ebx = 16 /*0x10*/;
L_0x004d7839:
    // 004d7839  881f                   -mov byte ptr [edi], bl
    app->getMemory<x86::reg8>(cpu.edi) = cpu.bl;
    // 004d783b  bf043b5600             -mov edi, 0x563b04
    cpu.edi = 5651204 /*0x563b04*/;
    // 004d7840  bef03a5600             -mov esi, 0x563af0
    cpu.esi = 5651184 /*0x563af0*/;
    // 004d7845  8b460c                 -mov eax, dword ptr [esi + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 004d7848  8b0df8347d00           -mov ecx, dword ptr [0x7d34f8]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205560) /* 0x7d34f8 */);
    // 004d784e  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004d7853  7558                   -jne 0x4d78ad
    if (!cpu.flags.zf)
    {
        goto L_0x004d78ad;
    }
    // 004d7855  39c8                   +cmp eax, ecx
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
    // 004d7857  7d54                   -jge 0x4d78ad
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004d78ad;
    }
    // 004d7859  8b4604                 -mov eax, dword ptr [esi + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 004d785c  bb00000000             -mov ebx, 0
    cpu.ebx = 0 /*0x0*/;
    // 004d7861  8b0d04357d00           -mov ecx, dword ptr [0x7d3504]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205572) /* 0x7d3504 */);
    // 004d7867  8b1500357d00           -mov edx, dword ptr [0x7d3500]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205568) /* 0x7d3500 */);
    // 004d786d  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004d7872  750d                   -jne 0x4d7881
    if (!cpu.flags.zf)
    {
        goto L_0x004d7881;
    }
    // 004d7874  39c8                   +cmp eax, ecx
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
    // 004d7876  7c09                   -jl 0x4d7881
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004d7881;
    }
    // 004d7878  39d0                   +cmp eax, edx
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
    // 004d787a  7e09                   -jle 0x4d7885
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004d7885;
    }
    // 004d787c  83cb04                 +or ebx, 4
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(4 /*0x4*/))));
    // 004d787f  eb04                   -jmp 0x4d7885
    goto L_0x004d7885;
L_0x004d7881:
    // 004d7881  83cb08                 -or ebx, 8
    cpu.ebx |= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 004d7884  90                     -nop 
    ;
L_0x004d7885:
    // 004d7885  8b06                   -mov eax, dword ptr [esi]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi);
    // 004d7887  90                     -nop 
    ;
    // 004d7888  8b0dfc347d00           -mov ecx, dword ptr [0x7d34fc]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205564) /* 0x7d34fc */);
    // 004d788e  8b150c357d00           -mov edx, dword ptr [0x7d350c]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205580) /* 0x7d350c */);
    // 004d7894  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004d7899  750d                   -jne 0x4d78a8
    if (!cpu.flags.zf)
    {
        goto L_0x004d78a8;
    }
    // 004d789b  39c8                   +cmp eax, ecx
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
    // 004d789d  7c09                   -jl 0x4d78a8
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004d78a8;
    }
    // 004d789f  39d0                   +cmp eax, edx
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
    // 004d78a1  7e0f                   -jle 0x4d78b2
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004d78b2;
    }
    // 004d78a3  83cb02                 +or ebx, 2
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(2 /*0x2*/))));
    // 004d78a6  eb0a                   -jmp 0x4d78b2
    goto L_0x004d78b2;
L_0x004d78a8:
    // 004d78a8  83cb01                 +or ebx, 1
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(1 /*0x1*/))));
    // 004d78ab  eb05                   -jmp 0x4d78b2
    goto L_0x004d78b2;
L_0x004d78ad:
    // 004d78ad  bb10000000             -mov ebx, 0x10
    cpu.ebx = 16 /*0x10*/;
L_0x004d78b2:
    // 004d78b2  881f                   -mov byte ptr [edi], bl
    app->getMemory<x86::reg8>(cpu.edi) = cpu.bl;
    // 004d78b4  bf243b5600             -mov edi, 0x563b24
    cpu.edi = 5651236 /*0x563b24*/;
    // 004d78b9  be103b5600             -mov esi, 0x563b10
    cpu.esi = 5651216 /*0x563b10*/;
    // 004d78be  8b460c                 -mov eax, dword ptr [esi + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 004d78c1  8b0df8347d00           -mov ecx, dword ptr [0x7d34f8]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205560) /* 0x7d34f8 */);
    // 004d78c7  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004d78cc  7558                   -jne 0x4d7926
    if (!cpu.flags.zf)
    {
        goto L_0x004d7926;
    }
    // 004d78ce  39c8                   +cmp eax, ecx
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
    // 004d78d0  7d54                   -jge 0x4d7926
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004d7926;
    }
    // 004d78d2  8b4604                 -mov eax, dword ptr [esi + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 004d78d5  bb00000000             -mov ebx, 0
    cpu.ebx = 0 /*0x0*/;
    // 004d78da  8b0d04357d00           -mov ecx, dword ptr [0x7d3504]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205572) /* 0x7d3504 */);
    // 004d78e0  8b1500357d00           -mov edx, dword ptr [0x7d3500]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205568) /* 0x7d3500 */);
    // 004d78e6  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004d78eb  750d                   -jne 0x4d78fa
    if (!cpu.flags.zf)
    {
        goto L_0x004d78fa;
    }
    // 004d78ed  39c8                   +cmp eax, ecx
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
    // 004d78ef  7c09                   -jl 0x4d78fa
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004d78fa;
    }
    // 004d78f1  39d0                   +cmp eax, edx
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
    // 004d78f3  7e09                   -jle 0x4d78fe
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004d78fe;
    }
    // 004d78f5  83cb04                 +or ebx, 4
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(4 /*0x4*/))));
    // 004d78f8  eb04                   -jmp 0x4d78fe
    goto L_0x004d78fe;
L_0x004d78fa:
    // 004d78fa  83cb08                 -or ebx, 8
    cpu.ebx |= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 004d78fd  90                     -nop 
    ;
L_0x004d78fe:
    // 004d78fe  8b06                   -mov eax, dword ptr [esi]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi);
    // 004d7900  90                     -nop 
    ;
    // 004d7901  8b0dfc347d00           -mov ecx, dword ptr [0x7d34fc]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205564) /* 0x7d34fc */);
    // 004d7907  8b150c357d00           -mov edx, dword ptr [0x7d350c]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205580) /* 0x7d350c */);
    // 004d790d  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004d7912  750d                   -jne 0x4d7921
    if (!cpu.flags.zf)
    {
        goto L_0x004d7921;
    }
    // 004d7914  39c8                   +cmp eax, ecx
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
    // 004d7916  7c09                   -jl 0x4d7921
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004d7921;
    }
    // 004d7918  39d0                   +cmp eax, edx
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
    // 004d791a  7e0f                   -jle 0x4d792b
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004d792b;
    }
    // 004d791c  83cb02                 +or ebx, 2
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(2 /*0x2*/))));
    // 004d791f  eb0a                   -jmp 0x4d792b
    goto L_0x004d792b;
L_0x004d7921:
    // 004d7921  83cb01                 +or ebx, 1
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(1 /*0x1*/))));
    // 004d7924  eb05                   -jmp 0x4d792b
    goto L_0x004d792b;
L_0x004d7926:
    // 004d7926  bb10000000             -mov ebx, 0x10
    cpu.ebx = 16 /*0x10*/;
L_0x004d792b:
    // 004d792b  881f                   -mov byte ptr [edi], bl
    app->getMemory<x86::reg8>(cpu.edi) = cpu.bl;
    // 004d792d  b9103b5600             -mov ecx, 0x563b10
    cpu.ecx = 5651216 /*0x563b10*/;
    // 004d7932  bbf03a5600             -mov ebx, 0x563af0
    cpu.ebx = 5651184 /*0x563af0*/;
    // 004d7937  bad03a5600             -mov edx, 0x563ad0
    cpu.edx = 5651152 /*0x563ad0*/;
    // 004d793c  b8b03a5600             -mov eax, 0x563ab0
    cpu.eax = 5651120 /*0x563ab0*/;
    // 004d7941  e89a99feff             -call 0x4c12e0
    cpu.esp -= 4;
    nfs3hp::vertices::clipQuad(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d7946  ff45f0                 +inc dword ptr [ebp - 0x10]
    {
        auto tmp = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 004d7949  e9eafcffff             -jmp 0x4d7638
    goto L_0x004d7638;
L_0x004d794e:
    // 004d794e  31ff                   -xor edi, edi
    cpu.edi ^= x86::reg32(x86::sreg32(cpu.edi));
    // 004d7950  bb0000803f             -mov ebx, 0x3f800000
    cpu.ebx = 1065353216 /*0x3f800000*/;
    // 004d7955  893dec3a5600           -mov dword ptr [0x563aec], edi
    app->getMemory<x86::reg32>(x86::reg32(5651180) /* 0x563aec */) = cpu.edi;
    // 004d795b  893dcc3a5600           -mov dword ptr [0x563acc], edi
    app->getMemory<x86::reg32>(x86::reg32(5651148) /* 0x563acc */) = cpu.edi;
    // 004d7961  893dc83a5600           -mov dword ptr [0x563ac8], edi
    app->getMemory<x86::reg32>(x86::reg32(5651144) /* 0x563ac8 */) = cpu.edi;
    // 004d7967  891d2c3b5600           -mov dword ptr [0x563b2c], ebx
    app->getMemory<x86::reg32>(x86::reg32(5651244) /* 0x563b2c */) = cpu.ebx;
    // 004d796d  891d0c3b5600           -mov dword ptr [0x563b0c], ebx
    app->getMemory<x86::reg32>(x86::reg32(5651212) /* 0x563b0c */) = cpu.ebx;
    // 004d7973  891d083b5600           -mov dword ptr [0x563b08], ebx
    app->getMemory<x86::reg32>(x86::reg32(5651208) /* 0x563b08 */) = cpu.ebx;
    // 004d7979  891de83a5600           -mov dword ptr [0x563ae8], ebx
    app->getMemory<x86::reg32>(x86::reg32(5651176) /* 0x563ae8 */) = cpu.ebx;
    // 004d797f  893d283b5600           -mov dword ptr [0x563b28], edi
    app->getMemory<x86::reg32>(x86::reg32(5651240) /* 0x563b28 */) = cpu.edi;
L_0x004d7985:
    // 004d7985  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004d7987  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d7988  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d7989  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d798a  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d798b  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_4d7990: native, nfs3hp::port::shapes::drawShape */

/* sub_4d79b0: native, nfs3hp::port::obj3d::drawLogo */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x90 */
void Application::sub_4d7cc0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004d7cc0  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004d7cc1  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004d7cc2  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004d7cc3  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004d7cc5  83ec1c                 +sub esp, 0x1c
    {
        x86::reg32& tmp1 = cpu.esp;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(28 /*0x1c*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 004d7cc8  d94510                 +fld dword ptr [ebp + 0x10]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(16) /* 0x10 */));
    // 004d7ccb  d80584965400           +fadd dword ptr [0x549684]
    x86::Float fpu2 = cpu.fpu.add(fpu1, x86::Float(app->getMemory<float>(x86::reg32(5543556) /* 0x549684 */)));
    // 004d7cd1  d9ee                   +fldz 
    x86::Float fpu3 = 0.0;
    // 004d7cd3  d9c9                   +fxch st(1)
    
    // 004d7cd5  d95dfc                 +fstp dword ptr [ebp - 4]
    app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = float(fpu2);
    // 004d7cd8  d85dfc                 +fcomp dword ptr [ebp - 4]
    cpu.fpu.compare(fpu3, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 004d7cdb  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 004d7cdd  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 004d7cde  7308                   -jae 0x4d7ce8
    if (!cpu.flags.cf)
    {
        goto L_0x004d7ce8;
    }
    // 004d7ce0  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004d7ce3  8945ec                 -mov dword ptr [ebp - 0x14], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */) = cpu.eax;
    // 004d7ce6  eb08                   -jmp 0x4d7cf0
    goto L_0x004d7cf0;
L_0x004d7ce8:
    // 004d7ce8  d945fc                 +fld dword ptr [ebp - 4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu4 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */));
    // 004d7ceb  d9e0                   +fchs 
    x86::Float fpu5 = -fpu4;
    // 004d7ced  d95dec                 +fstp dword ptr [ebp - 0x14]
    app->getMemory<float>(cpu.ebp + x86::reg32(-20) /* -0x14 */) = float(fpu5);
    }
L_0x004d7cf0:
    // 004d7cf0  d945ec                 +fld dword ptr [ebp - 0x14]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu6 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-20) /* -0x14 */));
    // 004d7cf3  d80d88965400           +fmul dword ptr [0x549688]
    x86::Float fpu7 = cpu.fpu.mul(fpu6, x86::Float(app->getMemory<float>(x86::reg32(5543560) /* 0x549688 */)));
    // 004d7cf9  d80d8c965400           +fmul dword ptr [0x54968c]
    x86::Float fpu8 = cpu.fpu.mul(fpu7, x86::Float(app->getMemory<float>(x86::reg32(5543564) /* 0x54968c */)));
    // 004d7cff  dc0d94965400           +fmul qword ptr [0x549694]
    x86::Float fpu9 = cpu.fpu.mul(fpu8, x86::Float(app->getMemory<double>(x86::reg32(5543572) /* 0x549694 */)));
    // 004d7d05  d94514                 +fld dword ptr [ebp + 0x14]
    x86::Float fpu10 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(20) /* 0x14 */));
    // 004d7d08  d9ee                   +fldz 
    x86::Float fpu11 = 0.0;
    // 004d7d0a  d9c9                   +fxch st(1)
    
    // 004d7d0c  d805a4965400           +fadd dword ptr [0x5496a4]
    x86::Float fpu12 = cpu.fpu.add(fpu10, x86::Float(app->getMemory<float>(x86::reg32(5543588) /* 0x5496a4 */)));
    // 004d7d12  d9ca                   +fxch st(2)
    
    // 004d7d14  dc2d9c965400           +fsubr qword ptr [0x54969c]
    x86::Float fpu13 = cpu.fpu.sub(x86::Float(app->getMemory<double>(x86::reg32(5543580) /* 0x54969c */)), fpu9);
    // 004d7d1a  d9ca                   +fxch st(2)
    
    // 004d7d1c  d95df4                 +fstp dword ptr [ebp - 0xc]
    app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */) = float(fpu12);
    // 004d7d1f  d9c9                   +fxch st(1)
    
    // 004d7d21  dd5de4                 +fstp qword ptr [ebp - 0x1c]
    app->getMemory<double>(cpu.ebp + x86::reg32(-28) /* -0x1c */) = double(fpu13);
    // 004d7d24  d85df4                 +fcomp dword ptr [ebp - 0xc]
    cpu.fpu.compare(fpu11, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */)));
    // 004d7d27  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 004d7d29  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 004d7d2a  7308                   -jae 0x4d7d34
    if (!cpu.flags.cf)
    {
        goto L_0x004d7d34;
    }
    // 004d7d2c  8b45f4                 -mov eax, dword ptr [ebp - 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 004d7d2f  8945f0                 -mov dword ptr [ebp - 0x10], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = cpu.eax;
    // 004d7d32  eb08                   -jmp 0x4d7d3c
    goto L_0x004d7d3c;
L_0x004d7d34:
    // 004d7d34  d945f4                 -fld dword ptr [ebp - 0xc]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu14 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */));
    // 004d7d37  d9e0                   -fchs 
    x86::Float fpu15 = -fpu14;
    // 004d7d39  d95df0                 -fstp dword ptr [ebp - 0x10]
    app->getMemory<float>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = float(fpu15);
    }
L_0x004d7d3c:
    // 004d7d3c  d945f0                 -fld dword ptr [ebp - 0x10]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu16 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-16) /* -0x10 */));
    // 004d7d3f  d80d88965400           -fmul dword ptr [0x549688]
    x86::Float fpu17 = cpu.fpu.mul(fpu16, x86::Float(app->getMemory<float>(x86::reg32(5543560) /* 0x549688 */)));
    // 004d7d45  d80da8965400           -fmul dword ptr [0x5496a8]
    x86::Float fpu18 = cpu.fpu.mul(fpu17, x86::Float(app->getMemory<float>(x86::reg32(5543592) /* 0x5496a8 */)));
    // 004d7d4b  dc0d94965400           -fmul qword ptr [0x549694]
    x86::Float fpu19 = cpu.fpu.mul(fpu18, x86::Float(app->getMemory<double>(x86::reg32(5543572) /* 0x549694 */)));
    // 004d7d51  dc6de4                 -fsubr qword ptr [ebp - 0x1c]
    x86::Float fpu20 = cpu.fpu.sub(x86::Float(app->getMemory<double>(cpu.ebp + x86::reg32(-28) /* -0x1c */)), fpu19);
    cpu.fpu.count += 1;
    cpu.fpu.st(0) = fpu20;
    }
    // 004d7d54  e8fd7f0000             -call 0x4dfd56
    cpu.esp -= 4;
    nfs3hp::watcom::CHP(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d7d59  db5df8                 -fistp dword ptr [ebp - 8]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu21 = cpu.fpu.st(0);
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = x86::reg32(cpu.fpu.toInteger<x86::sreg32>(fpu21));
    // 004d7d5c  837df800               +cmp dword ptr [ebp - 8], 0
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
    cpu.fpu.count -= 1;
    }
    // 004d7d60  7d05                   -jge 0x4d7d67
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004d7d67;
    }
    // 004d7d62  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 004d7d64  894df8                 -mov dword ptr [ebp - 8], ecx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.ecx;
L_0x004d7d67:
    // 004d7d67  8b5518                 -mov edx, dword ptr [ebp + 0x18]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(24) /* 0x18 */);
    // 004d7d6a  0faf55f8               -imul edx, dword ptr [ebp - 8]
    cpu.edx = x86::reg32(x86::sreg64(x86::sreg32(cpu.edx)) * x86::sreg64(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */))));
    // 004d7d6e  b9ff000000             -mov ecx, 0xff
    cpu.ecx = 255 /*0xff*/;
    // 004d7d73  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004d7d75  c1fa1f                 -sar edx, 0x1f
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (31 /*0x1f*/ % 32));
    // 004d7d78  f7f9                   -idiv ecx
    {
        x86::sreg64 tmp = x86::sreg64(cpu.edx_eax);
        x86::sreg32 d = x86::sreg32(cpu.ecx);
        cpu.edx_eax = x86::reg64(tmp / d);
        cpu.edx = x86::reg32(tmp % d);
    }
    // 004d7d7a  c1e018                 -shl eax, 0x18
    cpu.eax <<= 24 /*0x18*/ % 32;
    // 004d7d7d  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004d7d7f  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d7d80  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d7d81  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d7d82  c20c00                 -ret 0xc
    cpu.esp += 4+12 /*0xc*/;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 0x8b 0xdb */
void Application::sub_4d7d90(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004d7d90  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004d7d91  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004d7d92  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004d7d93  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004d7d95  83ec18                 -sub esp, 0x18
    (cpu.esp) -= x86::reg32(x86::sreg32(24 /*0x18*/));
    // 004d7d98  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 004d7d9a  89df                   -mov edi, ebx
    cpu.edi = cpu.ebx;
    // 004d7d9c  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004d7d9e  89cb                   -mov ebx, ecx
    cpu.ebx = cpu.ecx;
    // 004d7da0  8b5520                 -mov edx, dword ptr [ebp + 0x20]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(32) /* 0x20 */);
    // 004d7da3  8945f8                 -mov dword ptr [ebp - 8], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.eax;
    // 004d7da6  8b4514                 -mov eax, dword ptr [ebp + 0x14]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(20) /* 0x14 */);
    // 004d7da9  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 004d7dac  db45fc                 -fild dword ptr [ebp - 4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 004d7daf  8b4518                 -mov eax, dword ptr [ebp + 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(24) /* 0x18 */);
    // 004d7db2  d955f0                 -fst dword ptr [ebp - 0x10]
    app->getMemory<float>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = float(fpu1);
    // 004d7db5  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 004d7db8  d9451c                 -fld dword ptr [ebp + 0x1c]
    x86::Float fpu2 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(28) /* 0x1c */));
    // 004d7dbb  d9c9                   -fxch st(1)
    
    // 004d7dbd  d8c9                   -fmul st(1)
    x86::Float fpu3 = cpu.fpu.mul(fpu1, x86::Float(fpu2));
    // 004d7dbf  db45fc                 -fild dword ptr [ebp - 4]
    x86::Float fpu4 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 004d7dc2  d955f4                 -fst dword ptr [ebp - 0xc]
    app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */) = float(fpu4);
    // 004d7dc5  deca                   -fmulp st(2)
    x86::Float fpu5 = cpu.fpu.mul(fpu2, fpu4);
    // 004d7dc7  d905a83a5600           -fld dword ptr [0x563aa8]
    x86::Float fpu6 = x86::Float(app->getMemory<float>(x86::reg32(5651112) /* 0x563aa8 */));
    // 004d7dcd  d9c0                   -fld st(0)
    x86::Float fpu7 = x86::Float(fpu6);
    // 004d7dcf  d905ac3a5600           -fld dword ptr [0x563aac]
    x86::Float fpu8 = x86::Float(app->getMemory<float>(x86::reg32(5651116) /* 0x563aac */));
    // 004d7dd5  d9c2                   -fld st(2)
    x86::Float fpu9 = x86::Float(fpu6);
    // 004d7dd7  d905ac3a5600           -fld dword ptr [0x563aac]
    x86::Float fpu10 = x86::Float(app->getMemory<float>(x86::reg32(5651116) /* 0x563aac */));
    // 004d7ddd  d9cb                   -fxch st(3)
    
    // 004d7ddf  d91db83a5600           -fstp dword ptr [0x563ab8]
    app->getMemory<float>(x86::reg32(5651128) /* 0x563ab8 */) = float(fpu7);
    // 004d7de5  d9c3                   -fld st(3)
    x86::Float fpu11 = x86::Float(fpu6);
    // 004d7de7  d9ca                   -fxch st(2)
    
    // 004d7de9  d91dbc3a5600           -fstp dword ptr [0x563abc]
    app->getMemory<float>(x86::reg32(5651132) /* 0x563abc */) = float(fpu8);
    // 004d7def  d905ac3a5600           -fld dword ptr [0x563aac]
    x86::Float fpu12 = x86::Float(app->getMemory<float>(x86::reg32(5651116) /* 0x563aac */));
    // 004d7df5  d9c9                   -fxch st(1)
    
    // 004d7df7  d91dd83a5600           -fstp dword ptr [0x563ad8]
    app->getMemory<float>(x86::reg32(5651160) /* 0x563ad8 */) = float(fpu9);
    // 004d7dfd  d9ca                   -fxch st(2)
    
    // 004d7dff  d91ddc3a5600           -fstp dword ptr [0x563adc]
    app->getMemory<float>(x86::reg32(5651164) /* 0x563adc */) = float(fpu10);
    // 004d7e05  d91df83a5600           -fstp dword ptr [0x563af8]
    app->getMemory<float>(x86::reg32(5651192) /* 0x563af8 */) = float(fpu11);
    // 004d7e0b  d91dfc3a5600           -fstp dword ptr [0x563afc]
    app->getMemory<float>(x86::reg32(5651196) /* 0x563afc */) = float(fpu12);
    // 004d7e11  d91d183b5600           -fstp dword ptr [0x563b18]
    app->getMemory<float>(x86::reg32(5651224) /* 0x563b18 */) = float(fpu6);
    // 004d7e17  a1ac3a5600             -mov eax, dword ptr [0x563aac]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5651116) /* 0x563aac */);
    // 004d7e1c  a31c3b5600             -mov dword ptr [0x563b1c], eax
    app->getMemory<x86::reg32>(x86::reg32(5651228) /* 0x563b1c */) = cpu.eax;
    // 004d7e21  897dfc                 -mov dword ptr [ebp - 4], edi
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.edi;
    // 004d7e24  89d1                   -mov ecx, edx
    cpu.ecx = cpu.edx;
    // 004d7e26  db45fc                 -fild dword ptr [ebp - 4]
    x86::Float fpu13 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 004d7e29  db45f8                 -fild dword ptr [ebp - 8]
    x86::Float fpu14 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    // 004d7e2c  d91d103b5600           -fstp dword ptr [0x563b10]
    app->getMemory<float>(x86::reg32(5651216) /* 0x563b10 */) = float(fpu14);
    // 004d7e32  d91dd43a5600           -fstp dword ptr [0x563ad4]
    app->getMemory<float>(x86::reg32(5651156) /* 0x563ad4 */) = float(fpu13);
    // 004d7e38  81e1000000ff           -and ecx, 0xff000000
    cpu.ecx &= x86::reg32(x86::sreg32(4278190080 /*0xff000000*/));
    // 004d7e3e  d905103b5600           -fld dword ptr [0x563b10]
    x86::Float fpu15 = x86::Float(app->getMemory<float>(x86::reg32(5651216) /* 0x563b10 */));
    // 004d7e44  c1e918                 -shr ecx, 0x18
    cpu.ecx >>= 24 /*0x18*/ % 32;
    // 004d7e47  d905d43a5600           -fld dword ptr [0x563ad4]
    x86::Float fpu16 = x86::Float(app->getMemory<float>(x86::reg32(5651156) /* 0x563ad4 */));
    // 004d7e4d  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004d7e4e  d91db43a5600           -fstp dword ptr [0x563ab4]
    app->getMemory<float>(x86::reg32(5651124) /* 0x563ab4 */) = float(fpu16);
    // 004d7e54  ff35b43a5600           -push dword ptr [0x563ab4]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(x86::reg32(5651124) /* 0x563ab4 */);
    cpu.esp -= 4;
    // 004d7e5a  d91db03a5600           -fstp dword ptr [0x563ab0]
    app->getMemory<float>(x86::reg32(5651120) /* 0x563ab0 */) = float(fpu15);
    // 004d7e60  ff35b03a5600           -push dword ptr [0x563ab0]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(x86::reg32(5651120) /* 0x563ab0 */);
    cpu.esp -= 4;
    // 004d7e66  d805103b5600           -fadd dword ptr [0x563b10]
    x86::Float fpu17 = cpu.fpu.add(fpu3, x86::Float(app->getMemory<float>(x86::reg32(5651216) /* 0x563b10 */)));
    // 004d7e6c  d905d43a5600           -fld dword ptr [0x563ad4]
    x86::Float fpu18 = x86::Float(app->getMemory<float>(x86::reg32(5651156) /* 0x563ad4 */));
    // 004d7e72  d9c9                   -fxch st(1)
    
    // 004d7e74  d915f03a5600           -fst dword ptr [0x563af0]
    app->getMemory<float>(x86::reg32(5651184) /* 0x563af0 */) = float(fpu17);
    // 004d7e7a  d9c9                   -fxch st(1)
    
    // 004d7e7c  dec2                   -faddp st(2)
    x86::Float fpu19 = cpu.fpu.add(fpu5, fpu18);
    // 004d7e7e  d91dd03a5600           -fstp dword ptr [0x563ad0]
    app->getMemory<float>(x86::reg32(5651152) /* 0x563ad0 */) = float(fpu17);
    // 004d7e84  d915143b5600           -fst dword ptr [0x563b14]
    app->getMemory<float>(x86::reg32(5651220) /* 0x563b14 */) = float(fpu19);
    // 004d7e8a  d91df43a5600           -fstp dword ptr [0x563af4]
    app->getMemory<float>(x86::reg32(5651188) /* 0x563af4 */) = float(fpu19);
    }
    // 004d7e90  e82bfeffff             -call 0x4d7cc0
    cpu.esp -= 4;
    sub_4d7cc0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d7e95  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004d7e96  81e2ffffff00           -and edx, 0xffffff
    cpu.edx &= x86::reg32(x86::sreg32(16777215 /*0xffffff*/));
    // 004d7e9c  ff35d43a5600           -push dword ptr [0x563ad4]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(x86::reg32(5651156) /* 0x563ad4 */);
    cpu.esp -= 4;
    // 004d7ea2  8d3c02                 -lea edi, [edx + eax]
    cpu.edi = x86::reg32(cpu.edx + cpu.eax * 1);
    // 004d7ea5  ff35d03a5600           -push dword ptr [0x563ad0]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(x86::reg32(5651152) /* 0x563ad0 */);
    cpu.esp -= 4;
    // 004d7eab  893dc03a5600           -mov dword ptr [0x563ac0], edi
    app->getMemory<x86::reg32>(x86::reg32(5651136) /* 0x563ac0 */) = cpu.edi;
    // 004d7eb1  e80afeffff             -call 0x4d7cc0
    cpu.esp -= 4;
    sub_4d7cc0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d7eb6  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004d7eb7  ff35f43a5600           -push dword ptr [0x563af4]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(x86::reg32(5651188) /* 0x563af4 */);
    cpu.esp -= 4;
    // 004d7ebd  8d3c02                 -lea edi, [edx + eax]
    cpu.edi = x86::reg32(cpu.edx + cpu.eax * 1);
    // 004d7ec0  ff35f03a5600           -push dword ptr [0x563af0]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(x86::reg32(5651184) /* 0x563af0 */);
    cpu.esp -= 4;
    // 004d7ec6  893de03a5600           -mov dword ptr [0x563ae0], edi
    app->getMemory<x86::reg32>(x86::reg32(5651168) /* 0x563ae0 */) = cpu.edi;
    // 004d7ecc  e8effdffff             -call 0x4d7cc0
    cpu.esp -= 4;
    sub_4d7cc0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d7ed1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004d7ed2  895dfc                 -mov dword ptr [ebp - 4], ebx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.ebx;
    // 004d7ed5  ff35143b5600           -push dword ptr [0x563b14]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(x86::reg32(5651220) /* 0x563b14 */);
    cpu.esp -= 4;
    // 004d7edb  8d3c02                 -lea edi, [edx + eax]
    cpu.edi = x86::reg32(cpu.edx + cpu.eax * 1);
    // 004d7ede  ff35103b5600           -push dword ptr [0x563b10]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(x86::reg32(5651216) /* 0x563b10 */);
    cpu.esp -= 4;
    // 004d7ee4  893d003b5600           -mov dword ptr [0x563b00], edi
    app->getMemory<x86::reg32>(x86::reg32(5651200) /* 0x563b00 */) = cpu.edi;
    // 004d7eea  e8d1fdffff             -call 0x4d7cc0
    cpu.esp -= 4;
    sub_4d7cc0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d7eef  db45fc                 -fild dword ptr [ebp - 4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu20 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 004d7ef2  d9c0                   -fld st(0)
    x86::Float fpu21 = x86::Float(fpu20);
    // 004d7ef4  d905ac965400           -fld dword ptr [0x5496ac]
    x86::Float fpu22 = x86::Float(app->getMemory<float>(x86::reg32(5543596) /* 0x5496ac */));
    // 004d7efa  d9c9                   -fxch st(1)
    
    // 004d7efc  d8c9                   -fmul st(1)
    x86::Float fpu23 = cpu.fpu.mul(fpu21, x86::Float(fpu22));
    // 004d7efe  01c2                   -add edx, eax
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.eax));
    // 004d7f00  8b4510                 -mov eax, dword ptr [ebp + 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(16) /* 0x10 */);
    // 004d7f03  d9ca                   -fxch st(2)
    
    // 004d7f05  d845f0                 -fadd dword ptr [ebp - 0x10]
    x86::Float fpu24 = cpu.fpu.add(fpu20, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-16) /* -0x10 */)));
    // 004d7f08  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 004d7f0b  d8c9                   -fmul st(1)
    x86::Float fpu25 = cpu.fpu.mul(fpu24, x86::Float(fpu22));
    // 004d7f0d  db45fc                 -fild dword ptr [ebp - 4]
    x86::Float fpu26 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 004d7f10  d9c0                   -fld st(0)
    x86::Float fpu27 = x86::Float(fpu26);
    // 004d7f12  d845f4                 -fadd dword ptr [ebp - 0xc]
    x86::Float fpu28 = cpu.fpu.add(fpu27, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */)));
    // 004d7f15  d9c9                   -fxch st(1)
    
    // 004d7f17  d8cb                   -fmul st(3)
    x86::Float fpu29 = cpu.fpu.mul(fpu26, x86::Float(fpu22));
    // 004d7f19  d9c9                   -fxch st(1)
    
    // 004d7f1b  decb                   -fmulp st(3)
    x86::Float fpu30 = cpu.fpu.mul(fpu22, fpu28);
    // 004d7f1d  bfc43a5600             -mov edi, 0x563ac4
    cpu.edi = 5651140 /*0x563ac4*/;
    // 004d7f22  8915203b5600           -mov dword ptr [0x563b20], edx
    app->getMemory<x86::reg32>(x86::reg32(5651232) /* 0x563b20 */) = cpu.edx;
    // 004d7f28  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 004d7f2a  d9cb                   -fxch st(3)
    
    // 004d7f2c  d91d283b5600           -fstp dword ptr [0x563b28]
    app->getMemory<float>(x86::reg32(5651240) /* 0x563b28 */) = float(fpu23);
    // 004d7f32  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 004d7f37  beb03a5600             -mov esi, 0x563ab0
    cpu.esi = 5651120 /*0x563ab0*/;
    // 004d7f3c  8b0d283b5600           -mov ecx, dword ptr [0x563b28]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(5651240) /* 0x563b28 */);
    // 004d7f42  890dc83a5600           -mov dword ptr [0x563ac8], ecx
    app->getMemory<x86::reg32>(x86::reg32(5651144) /* 0x563ac8 */) = cpu.ecx;
    // 004d7f48  d915083b5600           -fst dword ptr [0x563b08]
    app->getMemory<float>(x86::reg32(5651208) /* 0x563b08 */) = float(fpu25);
    // 004d7f4e  d91de83a5600           -fstp dword ptr [0x563ae8]
    app->getMemory<float>(x86::reg32(5651176) /* 0x563ae8 */) = float(fpu25);
    // 004d7f54  d9c9                   -fxch st(1)
    
    // 004d7f56  d915ec3a5600           -fst dword ptr [0x563aec]
    app->getMemory<float>(x86::reg32(5651180) /* 0x563aec */) = float(fpu29);
    // 004d7f5c  d91dcc3a5600           -fstp dword ptr [0x563acc]
    app->getMemory<float>(x86::reg32(5651148) /* 0x563acc */) = float(fpu29);
    // 004d7f62  d9152c3b5600           -fst dword ptr [0x563b2c]
    app->getMemory<float>(x86::reg32(5651244) /* 0x563b2c */) = float(fpu30);
    // 004d7f68  d91d0c3b5600           -fstp dword ptr [0x563b0c]
    app->getMemory<float>(x86::reg32(5651212) /* 0x563b0c */) = float(fpu30);
    }
    // 004d7f6e  e88d99f5ff             -call 0x431900
    cpu.esp -= 4;
    nfs3hp::graphics::setRenderState(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d7f73  8b460c                 -mov eax, dword ptr [esi + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 004d7f76  8b0df8347d00           -mov ecx, dword ptr [0x7d34f8]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205560) /* 0x7d34f8 */);
    // 004d7f7c  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004d7f81  7558                   -jne 0x4d7fdb
    if (!cpu.flags.zf)
    {
        goto L_0x004d7fdb;
    }
    // 004d7f83  39c8                   +cmp eax, ecx
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
    // 004d7f85  7d54                   -jge 0x4d7fdb
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004d7fdb;
    }
    // 004d7f87  8b4604                 -mov eax, dword ptr [esi + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 004d7f8a  bb00000000             -mov ebx, 0
    cpu.ebx = 0 /*0x0*/;
    // 004d7f8f  8b0d04357d00           -mov ecx, dword ptr [0x7d3504]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205572) /* 0x7d3504 */);
    // 004d7f95  8b1500357d00           -mov edx, dword ptr [0x7d3500]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205568) /* 0x7d3500 */);
    // 004d7f9b  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004d7fa0  750d                   -jne 0x4d7faf
    if (!cpu.flags.zf)
    {
        goto L_0x004d7faf;
    }
    // 004d7fa2  39c8                   +cmp eax, ecx
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
    // 004d7fa4  7c09                   -jl 0x4d7faf
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004d7faf;
    }
    // 004d7fa6  39d0                   +cmp eax, edx
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
    // 004d7fa8  7e09                   -jle 0x4d7fb3
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004d7fb3;
    }
    // 004d7faa  83cb04                 +or ebx, 4
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(4 /*0x4*/))));
    // 004d7fad  eb04                   -jmp 0x4d7fb3
    goto L_0x004d7fb3;
L_0x004d7faf:
    // 004d7faf  83cb08                 -or ebx, 8
    cpu.ebx |= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 004d7fb2  90                     -nop 
    ;
L_0x004d7fb3:
    // 004d7fb3  8b06                   -mov eax, dword ptr [esi]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi);
    // 004d7fb5  90                     -nop 
    ;
    // 004d7fb6  8b0dfc347d00           -mov ecx, dword ptr [0x7d34fc]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205564) /* 0x7d34fc */);
    // 004d7fbc  8b150c357d00           -mov edx, dword ptr [0x7d350c]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205580) /* 0x7d350c */);
    // 004d7fc2  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004d7fc7  750d                   -jne 0x4d7fd6
    if (!cpu.flags.zf)
    {
        goto L_0x004d7fd6;
    }
    // 004d7fc9  39c8                   +cmp eax, ecx
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
    // 004d7fcb  7c09                   -jl 0x4d7fd6
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004d7fd6;
    }
    // 004d7fcd  39d0                   +cmp eax, edx
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
    // 004d7fcf  7e0f                   -jle 0x4d7fe0
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004d7fe0;
    }
    // 004d7fd1  83cb02                 +or ebx, 2
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(2 /*0x2*/))));
    // 004d7fd4  eb0a                   -jmp 0x4d7fe0
    goto L_0x004d7fe0;
L_0x004d7fd6:
    // 004d7fd6  83cb01                 +or ebx, 1
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(1 /*0x1*/))));
    // 004d7fd9  eb05                   -jmp 0x4d7fe0
    goto L_0x004d7fe0;
L_0x004d7fdb:
    // 004d7fdb  bb10000000             -mov ebx, 0x10
    cpu.ebx = 16 /*0x10*/;
L_0x004d7fe0:
    // 004d7fe0  881f                   -mov byte ptr [edi], bl
    app->getMemory<x86::reg8>(cpu.edi) = cpu.bl;
    // 004d7fe2  bfe43a5600             -mov edi, 0x563ae4
    cpu.edi = 5651172 /*0x563ae4*/;
    // 004d7fe7  bed03a5600             -mov esi, 0x563ad0
    cpu.esi = 5651152 /*0x563ad0*/;
    // 004d7fec  8b460c                 -mov eax, dword ptr [esi + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 004d7fef  8b0df8347d00           -mov ecx, dword ptr [0x7d34f8]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205560) /* 0x7d34f8 */);
    // 004d7ff5  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004d7ffa  7558                   -jne 0x4d8054
    if (!cpu.flags.zf)
    {
        goto L_0x004d8054;
    }
    // 004d7ffc  39c8                   +cmp eax, ecx
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
    // 004d7ffe  7d54                   -jge 0x4d8054
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004d8054;
    }
    // 004d8000  8b4604                 -mov eax, dword ptr [esi + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 004d8003  bb00000000             -mov ebx, 0
    cpu.ebx = 0 /*0x0*/;
    // 004d8008  8b0d04357d00           -mov ecx, dword ptr [0x7d3504]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205572) /* 0x7d3504 */);
    // 004d800e  8b1500357d00           -mov edx, dword ptr [0x7d3500]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205568) /* 0x7d3500 */);
    // 004d8014  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004d8019  750d                   -jne 0x4d8028
    if (!cpu.flags.zf)
    {
        goto L_0x004d8028;
    }
    // 004d801b  39c8                   +cmp eax, ecx
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
    // 004d801d  7c09                   -jl 0x4d8028
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004d8028;
    }
    // 004d801f  39d0                   +cmp eax, edx
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
    // 004d8021  7e09                   -jle 0x4d802c
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004d802c;
    }
    // 004d8023  83cb04                 +or ebx, 4
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(4 /*0x4*/))));
    // 004d8026  eb04                   -jmp 0x4d802c
    goto L_0x004d802c;
L_0x004d8028:
    // 004d8028  83cb08                 -or ebx, 8
    cpu.ebx |= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 004d802b  90                     -nop 
    ;
L_0x004d802c:
    // 004d802c  8b06                   -mov eax, dword ptr [esi]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi);
    // 004d802e  90                     -nop 
    ;
    // 004d802f  8b0dfc347d00           -mov ecx, dword ptr [0x7d34fc]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205564) /* 0x7d34fc */);
    // 004d8035  8b150c357d00           -mov edx, dword ptr [0x7d350c]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205580) /* 0x7d350c */);
    // 004d803b  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004d8040  750d                   -jne 0x4d804f
    if (!cpu.flags.zf)
    {
        goto L_0x004d804f;
    }
    // 004d8042  39c8                   +cmp eax, ecx
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
    // 004d8044  7c09                   -jl 0x4d804f
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004d804f;
    }
    // 004d8046  39d0                   +cmp eax, edx
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
    // 004d8048  7e0f                   -jle 0x4d8059
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004d8059;
    }
    // 004d804a  83cb02                 +or ebx, 2
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(2 /*0x2*/))));
    // 004d804d  eb0a                   -jmp 0x4d8059
    goto L_0x004d8059;
L_0x004d804f:
    // 004d804f  83cb01                 +or ebx, 1
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(1 /*0x1*/))));
    // 004d8052  eb05                   -jmp 0x4d8059
    goto L_0x004d8059;
L_0x004d8054:
    // 004d8054  bb10000000             -mov ebx, 0x10
    cpu.ebx = 16 /*0x10*/;
L_0x004d8059:
    // 004d8059  881f                   -mov byte ptr [edi], bl
    app->getMemory<x86::reg8>(cpu.edi) = cpu.bl;
    // 004d805b  bf043b5600             -mov edi, 0x563b04
    cpu.edi = 5651204 /*0x563b04*/;
    // 004d8060  bef03a5600             -mov esi, 0x563af0
    cpu.esi = 5651184 /*0x563af0*/;
    // 004d8065  8b460c                 -mov eax, dword ptr [esi + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 004d8068  8b0df8347d00           -mov ecx, dword ptr [0x7d34f8]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205560) /* 0x7d34f8 */);
    // 004d806e  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004d8073  7558                   -jne 0x4d80cd
    if (!cpu.flags.zf)
    {
        goto L_0x004d80cd;
    }
    // 004d8075  39c8                   +cmp eax, ecx
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
    // 004d8077  7d54                   -jge 0x4d80cd
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004d80cd;
    }
    // 004d8079  8b4604                 -mov eax, dword ptr [esi + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 004d807c  bb00000000             -mov ebx, 0
    cpu.ebx = 0 /*0x0*/;
    // 004d8081  8b0d04357d00           -mov ecx, dword ptr [0x7d3504]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205572) /* 0x7d3504 */);
    // 004d8087  8b1500357d00           -mov edx, dword ptr [0x7d3500]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205568) /* 0x7d3500 */);
    // 004d808d  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004d8092  750d                   -jne 0x4d80a1
    if (!cpu.flags.zf)
    {
        goto L_0x004d80a1;
    }
    // 004d8094  39c8                   +cmp eax, ecx
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
    // 004d8096  7c09                   -jl 0x4d80a1
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004d80a1;
    }
    // 004d8098  39d0                   +cmp eax, edx
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
    // 004d809a  7e09                   -jle 0x4d80a5
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004d80a5;
    }
    // 004d809c  83cb04                 +or ebx, 4
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(4 /*0x4*/))));
    // 004d809f  eb04                   -jmp 0x4d80a5
    goto L_0x004d80a5;
L_0x004d80a1:
    // 004d80a1  83cb08                 -or ebx, 8
    cpu.ebx |= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 004d80a4  90                     -nop 
    ;
L_0x004d80a5:
    // 004d80a5  8b06                   -mov eax, dword ptr [esi]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi);
    // 004d80a7  90                     -nop 
    ;
    // 004d80a8  8b0dfc347d00           -mov ecx, dword ptr [0x7d34fc]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205564) /* 0x7d34fc */);
    // 004d80ae  8b150c357d00           -mov edx, dword ptr [0x7d350c]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205580) /* 0x7d350c */);
    // 004d80b4  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004d80b9  750d                   -jne 0x4d80c8
    if (!cpu.flags.zf)
    {
        goto L_0x004d80c8;
    }
    // 004d80bb  39c8                   +cmp eax, ecx
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
    // 004d80bd  7c09                   -jl 0x4d80c8
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004d80c8;
    }
    // 004d80bf  39d0                   +cmp eax, edx
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
    // 004d80c1  7e0f                   -jle 0x4d80d2
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004d80d2;
    }
    // 004d80c3  83cb02                 +or ebx, 2
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(2 /*0x2*/))));
    // 004d80c6  eb0a                   -jmp 0x4d80d2
    goto L_0x004d80d2;
L_0x004d80c8:
    // 004d80c8  83cb01                 +or ebx, 1
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(1 /*0x1*/))));
    // 004d80cb  eb05                   -jmp 0x4d80d2
    goto L_0x004d80d2;
L_0x004d80cd:
    // 004d80cd  bb10000000             -mov ebx, 0x10
    cpu.ebx = 16 /*0x10*/;
L_0x004d80d2:
    // 004d80d2  881f                   -mov byte ptr [edi], bl
    app->getMemory<x86::reg8>(cpu.edi) = cpu.bl;
    // 004d80d4  bf243b5600             -mov edi, 0x563b24
    cpu.edi = 5651236 /*0x563b24*/;
    // 004d80d9  be103b5600             -mov esi, 0x563b10
    cpu.esi = 5651216 /*0x563b10*/;
    // 004d80de  8b460c                 -mov eax, dword ptr [esi + 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(12) /* 0xc */);
    // 004d80e1  8b0df8347d00           -mov ecx, dword ptr [0x7d34f8]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205560) /* 0x7d34f8 */);
    // 004d80e7  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004d80ec  7558                   -jne 0x4d8146
    if (!cpu.flags.zf)
    {
        goto L_0x004d8146;
    }
    // 004d80ee  39c8                   +cmp eax, ecx
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
    // 004d80f0  7d54                   -jge 0x4d8146
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004d8146;
    }
    // 004d80f2  8b4604                 -mov eax, dword ptr [esi + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 004d80f5  bb00000000             -mov ebx, 0
    cpu.ebx = 0 /*0x0*/;
    // 004d80fa  8b0d04357d00           -mov ecx, dword ptr [0x7d3504]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205572) /* 0x7d3504 */);
    // 004d8100  8b1500357d00           -mov edx, dword ptr [0x7d3500]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205568) /* 0x7d3500 */);
    // 004d8106  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004d810b  750d                   -jne 0x4d811a
    if (!cpu.flags.zf)
    {
        goto L_0x004d811a;
    }
    // 004d810d  39c8                   +cmp eax, ecx
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
    // 004d810f  7c09                   -jl 0x4d811a
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004d811a;
    }
    // 004d8111  39d0                   +cmp eax, edx
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
    // 004d8113  7e09                   -jle 0x4d811e
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004d811e;
    }
    // 004d8115  83cb04                 +or ebx, 4
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(4 /*0x4*/))));
    // 004d8118  eb04                   -jmp 0x4d811e
    goto L_0x004d811e;
L_0x004d811a:
    // 004d811a  83cb08                 -or ebx, 8
    cpu.ebx |= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 004d811d  90                     -nop 
    ;
L_0x004d811e:
    // 004d811e  8b06                   -mov eax, dword ptr [esi]
    cpu.eax = app->getMemory<x86::reg32>(cpu.esi);
    // 004d8120  90                     -nop 
    ;
    // 004d8121  8b0dfc347d00           -mov ecx, dword ptr [0x7d34fc]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(8205564) /* 0x7d34fc */);
    // 004d8127  8b150c357d00           -mov edx, dword ptr [0x7d350c]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205580) /* 0x7d350c */);
    // 004d812d  a900000080             +test eax, 0x80000000
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & 2147483648 /*0x80000000*/));
    // 004d8132  750d                   -jne 0x4d8141
    if (!cpu.flags.zf)
    {
        goto L_0x004d8141;
    }
    // 004d8134  39c8                   +cmp eax, ecx
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
    // 004d8136  7c09                   -jl 0x4d8141
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004d8141;
    }
    // 004d8138  39d0                   +cmp eax, edx
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
    // 004d813a  7e0f                   -jle 0x4d814b
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004d814b;
    }
    // 004d813c  83cb02                 +or ebx, 2
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(2 /*0x2*/))));
    // 004d813f  eb0a                   -jmp 0x4d814b
    goto L_0x004d814b;
L_0x004d8141:
    // 004d8141  83cb01                 +or ebx, 1
    cpu.clear_co();
    cpu.set_szp((cpu.ebx |= x86::reg32(x86::sreg32(1 /*0x1*/))));
    // 004d8144  eb05                   -jmp 0x4d814b
    goto L_0x004d814b;
L_0x004d8146:
    // 004d8146  bb10000000             -mov ebx, 0x10
    cpu.ebx = 16 /*0x10*/;
L_0x004d814b:
    // 004d814b  881f                   -mov byte ptr [edi], bl
    app->getMemory<x86::reg8>(cpu.edi) = cpu.bl;
    // 004d814d  b9103b5600             -mov ecx, 0x563b10
    cpu.ecx = 5651216 /*0x563b10*/;
    // 004d8152  bbf03a5600             -mov ebx, 0x563af0
    cpu.ebx = 5651184 /*0x563af0*/;
    // 004d8157  bad03a5600             -mov edx, 0x563ad0
    cpu.edx = 5651152 /*0x563ad0*/;
    // 004d815c  b8b03a5600             -mov eax, 0x563ab0
    cpu.eax = 5651120 /*0x563ab0*/;
    // 004d8161  bf0000803f             -mov edi, 0x3f800000
    cpu.edi = 1065353216 /*0x3f800000*/;
    // 004d8166  e87591feff             -call 0x4c12e0
    cpu.esp -= 4;
    nfs3hp::vertices::clipQuad(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d816b  893d2c3b5600           -mov dword ptr [0x563b2c], edi
    app->getMemory<x86::reg32>(x86::reg32(5651244) /* 0x563b2c */) = cpu.edi;
    // 004d8171  893d0c3b5600           -mov dword ptr [0x563b0c], edi
    app->getMemory<x86::reg32>(x86::reg32(5651212) /* 0x563b0c */) = cpu.edi;
    // 004d8177  893d083b5600           -mov dword ptr [0x563b08], edi
    app->getMemory<x86::reg32>(x86::reg32(5651208) /* 0x563b08 */) = cpu.edi;
    // 004d817d  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 004d817f  893de83a5600           -mov dword ptr [0x563ae8], edi
    app->getMemory<x86::reg32>(x86::reg32(5651176) /* 0x563ae8 */) = cpu.edi;
    // 004d8185  8915283b5600           -mov dword ptr [0x563b28], edx
    app->getMemory<x86::reg32>(x86::reg32(5651240) /* 0x563b28 */) = cpu.edx;
    // 004d818b  8915ec3a5600           -mov dword ptr [0x563aec], edx
    app->getMemory<x86::reg32>(x86::reg32(5651180) /* 0x563aec */) = cpu.edx;
    // 004d8191  8915cc3a5600           -mov dword ptr [0x563acc], edx
    app->getMemory<x86::reg32>(x86::reg32(5651148) /* 0x563acc */) = cpu.edx;
    // 004d8197  8915c83a5600           -mov dword ptr [0x563ac8], edx
    app->getMemory<x86::reg32>(x86::reg32(5651144) /* 0x563ac8 */) = cpu.edx;
    // 004d819d  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004d819f  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d81a0  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d81a1  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d81a2  c21400                 -ret 0x14
    cpu.esp += 4+20 /*0x14*/;
    return;
}

/* sub_4d81b0: native, nfs3hp::port::draw2d::drawShadedRectangle */

/* sub_4d8550: native, nfs3hp::port::draw2d::gradientRectangle */

/* sub_4d8570: native, nfs3hp::port::fields::drawShadedTriangle */

/* sub_4d8860: native, nfs3hp::port::draw2d::drawShadedBox */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x90 */
void Application::sub_4d88c0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004d88c0  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004d88c1  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004d88c2  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004d88c3  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004d88c5  8b7520                 -mov esi, dword ptr [ebp + 0x20]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(32) /* 0x20 */);
    // 004d88c8  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004d88c9  8b7d1c                 -mov edi, dword ptr [ebp + 0x1c]
    cpu.edi = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(28) /* 0x1c */);
    // 004d88cc  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004d88cd  8b7518                 -mov esi, dword ptr [ebp + 0x18]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(24) /* 0x18 */);
    // 004d88d0  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004d88d1  8b7d14                 -mov edi, dword ptr [ebp + 0x14]
    cpu.edi = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(20) /* 0x14 */);
    // 004d88d4  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004d88d5  8b7510                 -mov esi, dword ptr [ebp + 0x10]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(16) /* 0x10 */);
    // 004d88d8  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004d88d9  e892fcffff             -call 0x4d8570
    cpu.esp -= 4;
    nfs3hp::port::fields::drawShadedTriangle(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d88de  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d88df  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d88e0  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d88e1  c21400                 -ret 0x14
    cpu.esp += 4+20 /*0x14*/;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 */
void Application::sub_4d88f0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004d88f0  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004d88f1  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004d88f2  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004d88f3  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004d88f5  8b751c                 -mov esi, dword ptr [ebp + 0x1c]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(28) /* 0x1c */);
    // 004d88f8  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004d88f9  8b7d18                 -mov edi, dword ptr [ebp + 0x18]
    cpu.edi = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(24) /* 0x18 */);
    // 004d88fc  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004d88fd  8b7514                 -mov esi, dword ptr [ebp + 0x14]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(20) /* 0x14 */);
    // 004d8900  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004d8901  8b7d10                 -mov edi, dword ptr [ebp + 0x10]
    cpu.edi = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(16) /* 0x10 */);
    // 004d8904  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004d8905  e8a6f8ffff             -call 0x4d81b0
    cpu.esp -= 4;
    nfs3hp::port::draw2d::drawShadedRectangle(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004d890a  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d890b  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d890c  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d890d  c21000                 -ret 0x10
    cpu.esp += 4+16 /*0x10*/;
    return;
}

/* sub_4d8910: native, nfs3hp::port::draw2d::filledRectangle */

/* sub_4d8930: native, nfs3hp::port::draw2d::frame */

/* sub_4d89f0: native, nfs3hp::port::draw2d::drawPanel */

/* sub_4d8aa0: native, nfs3hp::port::fields::drawFrameAt */

/* sub_4d8ac0: native, nfs3hp::port::draw2d::drawFieldBox */

/* sub_4d8b80: native, nfs3hp::port::draw2d::drawTileRectangle */

/* sub_4d8ed0: native, nfs3hp::port::draw2d::drawLine */

/* sub_4d9120: native, nfs3hp::graphics::takeWindowAndClear */

/* sub_4d9140: native, nfs3hp::graphics::flipAndWaitFrames */

/* align: skip 0x8d 0x44 0x20 0x00 */
void Application::sub_4d9180(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004d9180  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004d9181  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004d9182  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004d9183  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004d9184  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004d9185  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004d9187  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 004d918a  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 004d918c  89d3                   -mov ebx, edx
    cpu.ebx = cpu.edx;
    // 004d918e  81fa00010000           +cmp edx, 0x100
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(256 /*0x100*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004d9194  0f849b000000           -je 0x4d9235
    if (cpu.flags.zf)
    {
        goto L_0x004d9235;
    }
    // 004d919a  25000000ff             -and eax, 0xff000000
    cpu.eax &= x86::reg32(x86::sreg32(4278190080 /*0xff000000*/));
    // 004d919f  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 004d91a2  83fa40                 +cmp edx, 0x40
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(64 /*0x40*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004d91a5  7529                   -jne 0x4d91d0
    if (!cpu.flags.zf)
    {
        goto L_0x004d91d0;
    }
    // 004d91a7  89cb                   -mov ebx, ecx
    cpu.ebx = cpu.ecx;
    // 004d91a9  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004d91ab  89ca                   -mov edx, ecx
    cpu.edx = cpu.ecx;
    // 004d91ad  8b4dfc                 -mov ecx, dword ptr [ebp - 4]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004d91b0  81e20000fc00           -and edx, 0xfc0000
    cpu.edx &= x86::reg32(x86::sreg32(16515072 /*0xfc0000*/));
    // 004d91b6  81e300fc0000           -and ebx, 0xfc00
    cpu.ebx &= x86::reg32(x86::sreg32(64512 /*0xfc00*/));
    // 004d91bc  25fc000000             -and eax, 0xfc
    cpu.eax &= x86::reg32(x86::sreg32(252 /*0xfc*/));
    // 004d91c1  c1fa02                 -sar edx, 2
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (2 /*0x2*/ % 32));
    // 004d91c4  c1fb02                 -sar ebx, 2
    cpu.ebx = x86::reg32(x86::sreg32(cpu.ebx) >> (2 /*0x2*/ % 32));
    // 004d91c7  01ca                   -add edx, ecx
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.ecx));
    // 004d91c9  c1f802                 -sar eax, 2
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (2 /*0x2*/ % 32));
    // 004d91cc  01da                   +add edx, ebx
    {
        x86::reg32& tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ebx));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 004d91ce  eb63                   -jmp 0x4d9233
    goto L_0x004d9233;
L_0x004d91d0:
    // 004d91d0  89ca                   -mov edx, ecx
    cpu.edx = cpu.ecx;
    // 004d91d2  c1fa10                 -sar edx, 0x10
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (16 /*0x10*/ % 32));
    // 004d91d5  81e2ff000000           -and edx, 0xff
    cpu.edx &= x86::reg32(x86::sreg32(255 /*0xff*/));
    // 004d91db  0fafd3                 -imul edx, ebx
    cpu.edx = x86::reg32(x86::sreg64(x86::sreg32(cpu.edx)) * x86::sreg64(x86::sreg32(cpu.ebx)));
    // 004d91de  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004d91e0  c1fa1f                 -sar edx, 0x1f
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (31 /*0x1f*/ % 32));
    // 004d91e3  c1e208                 +shl edx, 8
    {
        x86::reg8 tmp = 8 /*0x8*/ % 32;
        x86::reg32& op = cpu.edx;
        if (tmp)
        {
            cpu.flags.cf = 1 & (op >> (32 - tmp));
            cpu.set_szp((op <<= tmp));
            if (tmp == 1) cpu.flags.of = (cpu.flags.cf != (1 & (op >> (32 - 1))));
        }
    }
    // 004d91e6  1bc2                   -sbb eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx) + cpu.flags.cf);
    // 004d91e8  c1f808                 -sar eax, 8
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (8 /*0x8*/ % 32));
    // 004d91eb  89ca                   -mov edx, ecx
    cpu.edx = cpu.ecx;
    // 004d91ed  c1fa08                 -sar edx, 8
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (8 /*0x8*/ % 32));
    // 004d91f0  81e2ff000000           -and edx, 0xff
    cpu.edx &= x86::reg32(x86::sreg32(255 /*0xff*/));
    // 004d91f6  0fafd3                 -imul edx, ebx
    cpu.edx = x86::reg32(x86::sreg64(x86::sreg32(cpu.edx)) * x86::sreg64(x86::sreg32(cpu.ebx)));
    // 004d91f9  89c7                   -mov edi, eax
    cpu.edi = cpu.eax;
    // 004d91fb  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004d91fd  c1fa1f                 -sar edx, 0x1f
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (31 /*0x1f*/ % 32));
    // 004d9200  c1e208                 +shl edx, 8
    {
        x86::reg8 tmp = 8 /*0x8*/ % 32;
        x86::reg32& op = cpu.edx;
        if (tmp)
        {
            cpu.flags.cf = 1 & (op >> (32 - tmp));
            cpu.set_szp((op <<= tmp));
            if (tmp == 1) cpu.flags.of = (cpu.flags.cf != (1 & (op >> (32 - 1))));
        }
    }
    // 004d9203  1bc2                   -sbb eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx) + cpu.flags.cf);
    // 004d9205  c1f808                 -sar eax, 8
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (8 /*0x8*/ % 32));
    // 004d9208  89ca                   -mov edx, ecx
    cpu.edx = cpu.ecx;
    // 004d920a  81e2ff000000           -and edx, 0xff
    cpu.edx &= x86::reg32(x86::sreg32(255 /*0xff*/));
    // 004d9210  0fafd3                 -imul edx, ebx
    cpu.edx = x86::reg32(x86::sreg64(x86::sreg32(cpu.edx)) * x86::sreg64(x86::sreg32(cpu.ebx)));
    // 004d9213  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 004d9215  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004d9217  c1fa1f                 -sar edx, 0x1f
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (31 /*0x1f*/ % 32));
    // 004d921a  c1e208                 +shl edx, 8
    {
        x86::reg8 tmp = 8 /*0x8*/ % 32;
        x86::reg32& op = cpu.edx;
        if (tmp)
        {
            cpu.flags.cf = 1 & (op >> (32 - tmp));
            cpu.set_szp((op <<= tmp));
            if (tmp == 1) cpu.flags.of = (cpu.flags.cf != (1 & (op >> (32 - 1))));
        }
    }
    // 004d921d  1bc2                   -sbb eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx) + cpu.flags.cf);
    // 004d921f  c1f808                 -sar eax, 8
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (8 /*0x8*/ % 32));
    // 004d9222  89fa                   -mov edx, edi
    cpu.edx = cpu.edi;
    // 004d9224  8b4dfc                 -mov ecx, dword ptr [ebp - 4]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004d9227  c1e210                 -shl edx, 0x10
    cpu.edx <<= 16 /*0x10*/ % 32;
    // 004d922a  01d1                   -add ecx, edx
    (cpu.ecx) += x86::reg32(x86::sreg32(cpu.edx));
    // 004d922c  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 004d922e  c1e208                 -shl edx, 8
    cpu.edx <<= 8 /*0x8*/ % 32;
    // 004d9231  01ca                   -add edx, ecx
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.ecx));
L_0x004d9233:
    // 004d9233  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
L_0x004d9235:
    // 004d9235  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004d9237  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d9238  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d9239  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d923a  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d923b  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004d923c  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_4d9240: native, nfs3hp::port::draw2d::fontCharacter */

/* sub_4d9320: native, nfs3hp::port::draw2d::accentedCharacter */

/* sub_4d93a0: native, nfs3hp::port::draw2d::buildScreenFont */

/* sub_4d95c0: native, nfs3hp::port::draw2d::drawScreenCharacter */

/* sub_4d9b90: native, nfs3hp::port::draw2d::drawTurnedCharacter */

/* sub_4da120: native, nfs3hp::port::draw2d::drawTurnedText */

/* sub_4da1e0: native, nfs3hp::port::draw2d::drawTitleText */

/* sub_4da4a0: native, nfs3hp::port::draw2d::drawScreenText */

/* sub_4da560: native, nfs3hp::port::fields::drawCursor */

/* sub_4da8c0: native, nfs3hp::port::fields::drawCursorText */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x8d 0x40 0x00 */
void Application::sub_4daa10(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004daa10  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004daa11  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004daa12  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004daa13  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004daa14  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004daa15  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004daa16  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004daa18  83ec48                 -sub esp, 0x48
    (cpu.esp) -= x86::reg32(x86::sreg32(72 /*0x48*/));
    // 004daa1b  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 004daa1e  bb20000000             -mov ebx, 0x20
    cpu.ebx = 32 /*0x20*/;
    // 004daa23  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 004daa25  89da                   -mov edx, ebx
    cpu.edx = cpu.ebx;
    // 004daa27  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 004daa29  31f6                   -xor esi, esi
    cpu.esi ^= x86::reg32(x86::sreg32(cpu.esi));
    // 004daa2b  e860470100             -call 0x4ef190
    cpu.esp -= 4;
    sub_4ef190(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004daa30  8945f8                 -mov dword ptr [ebp - 8], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.eax;
    // 004daa33  31ff                   +xor edi, edi
    cpu.clear_co();
    cpu.set_szp((cpu.edi ^= x86::reg32(x86::sreg32(cpu.edi))));
    // 004daa35  eb59                   -jmp 0x4daa90
    goto L_0x004daa90;
L_0x004daa37:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004daa37  8b5806                 -mov ebx, dword ptr [eax + 6]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6) /* 0x6 */);
    // 004daa3a  8d04b500000000         -lea eax, [esi*4]
    cpu.eax = x86::reg32(cpu.esi * 4);
    // 004daa41  01f0                   -add eax, esi
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.esi));
    // 004daa43  8d0cfd00000000         -lea ecx, [edi*8]
    cpu.ecx = x86::reg32(cpu.edi * 8);
    // 004daa4a  c1e004                 -shl eax, 4
    cpu.eax <<= 4 /*0x4*/ % 32;
    // 004daa4d  01c8                   -add eax, ecx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.ecx));
    // 004daa4f  c1fb10                 -sar ebx, 0x10
    cpu.ebx = x86::reg32(x86::sreg32(cpu.ebx) >> (16 /*0x10*/ % 32));
    // 004daa52  89984c3d5600           -mov dword ptr [eax + 0x563d4c], ebx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(5651788) /* 0x563d4c */) = cpu.ebx;
    // 004daa58  8b4a08                 -mov ecx, dword ptr [edx + 8]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(8) /* 0x8 */);
    // 004daa5b  c1f910                 -sar ecx, 0x10
    cpu.ecx = x86::reg32(x86::sreg32(cpu.ecx) >> (16 /*0x10*/ % 32));
    // 004daa5e  8988503d5600           -mov dword ptr [eax + 0x563d50], ecx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(5651792) /* 0x563d50 */) = cpu.ecx;
    // 004daa64  8d04b500000000         -lea eax, [esi*4]
    cpu.eax = x86::reg32(cpu.esi * 4);
    // 004daa6b  01f0                   -add eax, esi
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.esi));
    // 004daa6d  c1e003                 -shl eax, 3
    cpu.eax <<= 3 /*0x3*/ % 32;
    // 004daa70  8d0cbd00000000         -lea ecx, [edi*4]
    cpu.ecx = x86::reg32(cpu.edi * 4);
    // 004daa77  05343b5600             -add eax, 0x563b34
    (cpu.eax) += x86::reg32(x86::sreg32(5651252 /*0x563b34*/));
    // 004daa7c  bb20000000             -mov ebx, 0x20
    cpu.ebx = 32 /*0x20*/;
    // 004daa81  01c8                   -add eax, ecx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.ecx));
    // 004daa83  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 004daa85  e8e6b5ffff             -call 0x4d6070
    cpu.esp -= 4;
    nfs3hp::port::shapes::shapeTexture(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x004daa8a:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004daa8a  47                     -inc edi
    (cpu.edi)++;
    // 004daa8b  83ff0a                 +cmp edi, 0xa
    {
        x86::reg32 tmp1 = cpu.edi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(10 /*0xa*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004daa8e  7d26                   -jge 0x4daab6
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004daab6;
    }
L_0x004daa90:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004daa90  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004daa91  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004daa92  68dc965400             -push 0x5496dc
    app->getMemory<x86::reg32>(cpu.esp-4) = 5543644 /*0x5496dc*/;
    cpu.esp -= 4;
    // 004daa97  8d45b8                 -lea eax, [ebp - 0x48]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-72) /* -0x48 */);
    // 004daa9a  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004daa9b  e8f04b0000             -call 0x4df690
    cpu.esp -= 4;
    nfs3hp::watcom::sprintf(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004daaa0  83c410                 -add esp, 0x10
    (cpu.esp) += x86::reg32(x86::sreg32(16 /*0x10*/));
    // 004daaa3  8d55b8                 -lea edx, [ebp - 0x48]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-72) /* -0x48 */);
    // 004daaa6  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004daaa9  e8c2470100             -call 0x4ef270
    cpu.esp -= 4;
    nfs3hp::ea::locateShape(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004daaae  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004daab0  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004daab2  7583                   -jne 0x4daa37
    if (!cpu.flags.zf)
    {
        goto L_0x004daa37;
    }
    // 004daab4  ebd4                   -jmp 0x4daa8a
    goto L_0x004daa8a;
L_0x004daab6:
    // 004daab6  46                     -inc esi
    (cpu.esi)++;
    // 004daab7  83fe0d                 +cmp esi, 0xd
    {
        x86::reg32 tmp1 = cpu.esi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(13 /*0xd*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004daaba  7d04                   -jge 0x4daac0
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004daac0;
    }
    // 004daabc  31ff                   +xor edi, edi
    cpu.clear_co();
    cpu.set_szp((cpu.edi ^= x86::reg32(x86::sreg32(cpu.edi))));
    // 004daabe  ebd0                   -jmp 0x4daa90
    goto L_0x004daa90;
L_0x004daac0:
    // 004daac0  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004daac3  e838540100             -call 0x4eff00
    cpu.esp -= 4;
    sub_4eff00(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004daac8  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004daaca  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004daacb  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004daacc  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004daacd  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004daace  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004daacf  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004daad0  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 */
void Application::sub_4dab10(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
  goto start;
dynamic_jump:
  switch(cpu.ip)
  {
start:
    // 004dab10  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004dab11  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004dab12  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004dab13  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004dab14  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004dab16  8b353c3d5600           -mov esi, dword ptr [0x563d3c]
    cpu.esi = app->getMemory<x86::reg32>(x86::reg32(5651772) /* 0x563d3c */);
    // 004dab1c  833d3492550000         +cmp dword ptr [0x559234], 0
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
    // 004dab23  742a                   -je 0x4dab4f
    if (cpu.flags.zf)
    {
        goto L_0x004dab4f;
    }
    // 004dab25  89f1                   -mov ecx, esi
    cpu.ecx = cpu.esi;
    // 004dab27  83fe0b                 +cmp esi, 0xb
    {
        x86::reg32 tmp1 = cpu.esi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(11 /*0xb*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004dab2a  7756                   -ja 0x4dab82
    if (!cpu.flags.cf && !cpu.flags.zf)
    {
        goto L_0x004dab82;
    }
    // 004dab2c  ff248dd4aa4d00         -jmp dword ptr [ecx*4 + 0x4daad4]
    cpu.ip = app->getMemory<x86::reg32>(5090004 + cpu.ecx * 4); goto dynamic_jump;
  case 0x004dab33:
    // 004dab33  c70007000000           -mov dword ptr [eax], 7
    app->getMemory<x86::reg32>(cpu.eax) = 7 /*0x7*/;
    // 004dab39  c70201000000           -mov dword ptr [edx], 1
    app->getMemory<x86::reg32>(cpu.edx) = 1 /*0x1*/;
    // 004dab3f  eb41                   -jmp 0x4dab82
    goto L_0x004dab82;
  case 0x004dab41:
    // 004dab41  c70010000000           -mov dword ptr [eax], 0x10
    app->getMemory<x86::reg32>(cpu.eax) = 16 /*0x10*/;
    // 004dab47  c70210000000           -mov dword ptr [edx], 0x10
    app->getMemory<x86::reg32>(cpu.edx) = 16 /*0x10*/;
    // 004dab4d  eb33                   -jmp 0x4dab82
    goto L_0x004dab82;
L_0x004dab4f:
    // 004dab4f  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 004dab51  7c05                   -jl 0x4dab58
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004dab58;
    }
    // 004dab53  83fe0d                 +cmp esi, 0xd
    {
        x86::reg32 tmp1 = cpu.esi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(13 /*0xd*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004dab56  7c0e                   -jl 0x4dab66
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004dab66;
    }
L_0x004dab58:
    // 004dab58  c70000000000           -mov dword ptr [eax], 0
    app->getMemory<x86::reg32>(cpu.eax) = 0 /*0x0*/;
    // 004dab5e  c70200000000           -mov dword ptr [edx], 0
    app->getMemory<x86::reg32>(cpu.edx) = 0 /*0x0*/;
    // 004dab64  eb1c                   -jmp 0x4dab82
    goto L_0x004dab82;
L_0x004dab66:
    // 004dab66  8d0cb500000000         -lea ecx, [esi*4]
    cpu.ecx = x86::reg32(cpu.esi * 4);
    // 004dab6d  01f1                   -add ecx, esi
    (cpu.ecx) += x86::reg32(x86::sreg32(cpu.esi));
    // 004dab6f  c1e104                 -shl ecx, 4
    cpu.ecx <<= 4 /*0x4*/ % 32;
    // 004dab72  8b994c3d5600           -mov ebx, dword ptr [ecx + 0x563d4c]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(5651788) /* 0x563d4c */);
    // 004dab78  8918                   -mov dword ptr [eax], ebx
    app->getMemory<x86::reg32>(cpu.eax) = cpu.ebx;
    // 004dab7a  8b81503d5600           -mov eax, dword ptr [ecx + 0x563d50]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(5651792) /* 0x563d50 */);
    // 004dab80  8902                   -mov dword ptr [edx], eax
    app->getMemory<x86::reg32>(cpu.edx) = cpu.eax;
  [[fallthrough]];
  case 0x004dab82:
L_0x004dab82:
    // 004dab82  89353c3d5600           -mov dword ptr [0x563d3c], esi
    app->getMemory<x86::reg32>(x86::reg32(5651772) /* 0x563d3c */) = cpu.esi;
    // 004dab88  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dab89  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dab8a  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dab8b  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dab8c  c3                     -ret 
    cpu.esp += 4;
    return;
  default:
    NFS2_ASSERT(false);
  }
}

/* sub_4dab90: native, nfs3hp::port::draw2d::drawPointer */

/* sub_4daf80: native, nfs3hp::port::draw2d::startScreens */

/* sub_4db000: native, nfs3hp::port::draw2d::drawTexturedQuad */

/* sub_4db380: native, nfs3hp::port::draw2d::drawShadedQuad */

/* align: skip 0x00 0x00 0x00 0x00 0x00 0x00 0x00 */
void Application::sub_4db750(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004db750  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004db751  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004db752  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004db753  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004db755  83ec28                 -sub esp, 0x28
    (cpu.esp) -= x86::reg32(x86::sreg32(40 /*0x28*/));
    // 004db758  8945f8                 -mov dword ptr [ebp - 8], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.eax;
    // 004db75b  89d6                   -mov esi, edx
    cpu.esi = cpu.edx;
    // 004db75d  89df                   -mov edi, ebx
    cpu.edi = cpu.ebx;
    // 004db75f  8a5d10                 -mov bl, byte ptr [ebp + 0x10]
    cpu.bl = app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(16) /* 0x10 */);
    // 004db762  837d1402               +cmp dword ptr [ebp + 0x14], 2
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(20) /* 0x14 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(2 /*0x2*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004db766  7502                   -jne 0x4db76a
    if (!cpu.flags.zf)
    {
        goto L_0x004db76a;
    }
    // 004db768  30db                   -xor bl, bl
    cpu.bl ^= x86::reg8(x86::sreg8(cpu.bl));
L_0x004db76a:
    // 004db76a  89fa                   -mov edx, edi
    cpu.edx = cpu.edi;
    // 004db76c  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004db76e  6800006041             -push 0x41600000
    app->getMemory<x86::reg32>(cpu.esp-4) = 1096810496 /*0x41600000*/;
    cpu.esp -= 4;
    // 004db773  e8a8b7fbff             -call 0x496f20
    cpu.esp -= 4;
    sub_496f20(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004db778  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004db77a  0f85c0000000           -jne 0x4db840
    if (!cpu.flags.zf)
    {
        goto L_0x004db840;
    }
    // 004db780  837df803               +cmp dword ptr [ebp - 8], 3
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(3 /*0x3*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004db784  0f8d97000000           -jge 0x4db821
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004db821;
    }
    // 004db78a  d906                   -fld dword ptr [esi]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.esi));
    // 004db78c  d807                   -fadd dword ptr [edi]
    x86::Float fpu2 = cpu.fpu.add(fpu1, x86::Float(app->getMemory<float>(cpu.edi)));
    // 004db78e  dd050c975400           -fld qword ptr [0x54970c]
    x86::Float fpu3 = x86::Float(app->getMemory<double>(x86::reg32(5543692) /* 0x54970c */));
    // 004db794  d9c9                   -fxch st(1)
    
    // 004db796  d8c9                   -fmul st(1)
    x86::Float fpu4 = cpu.fpu.mul(fpu2, x86::Float(fpu3));
    // 004db798  d95dd8                 -fstp dword ptr [ebp - 0x28]
    app->getMemory<float>(cpu.ebp + x86::reg32(-40) /* -0x28 */) = float(fpu4);
    // 004db79b  d94604                 -fld dword ptr [esi + 4]
    x86::Float fpu5 = x86::Float(app->getMemory<float>(cpu.esi + x86::reg32(4) /* 0x4 */));
    // 004db79e  d84704                 -fadd dword ptr [edi + 4]
    x86::Float fpu6 = cpu.fpu.add(fpu5, x86::Float(app->getMemory<float>(cpu.edi + x86::reg32(4) /* 0x4 */)));
    // 004db7a1  d8c9                   -fmul st(1)
    x86::Float fpu7 = cpu.fpu.mul(fpu6, x86::Float(fpu3));
    // 004db7a3  d95ddc                 -fstp dword ptr [ebp - 0x24]
    app->getMemory<float>(cpu.ebp + x86::reg32(-36) /* -0x24 */) = float(fpu7);
    // 004db7a6  d94608                 -fld dword ptr [esi + 8]
    x86::Float fpu8 = x86::Float(app->getMemory<float>(cpu.esi + x86::reg32(8) /* 0x8 */));
    // 004db7a9  d84708                 -fadd dword ptr [edi + 8]
    x86::Float fpu9 = cpu.fpu.add(fpu8, x86::Float(app->getMemory<float>(cpu.edi + x86::reg32(8) /* 0x8 */)));
    // 004db7ac  d8c9                   -fmul st(1)
    x86::Float fpu10 = cpu.fpu.mul(fpu9, x86::Float(fpu3));
    // 004db7ae  d95de0                 -fstp dword ptr [ebp - 0x20]
    app->getMemory<float>(cpu.ebp + x86::reg32(-32) /* -0x20 */) = float(fpu10);
    // 004db7b1  d9460c                 -fld dword ptr [esi + 0xc]
    x86::Float fpu11 = x86::Float(app->getMemory<float>(cpu.esi + x86::reg32(12) /* 0xc */));
    // 004db7b4  d8470c                 -fadd dword ptr [edi + 0xc]
    x86::Float fpu12 = cpu.fpu.add(fpu11, x86::Float(app->getMemory<float>(cpu.edi + x86::reg32(12) /* 0xc */)));
    // 004db7b7  d8c9                   -fmul st(1)
    x86::Float fpu13 = cpu.fpu.mul(fpu12, x86::Float(fpu3));
    // 004db7b9  d95de4                 -fstp dword ptr [ebp - 0x1c]
    app->getMemory<float>(cpu.ebp + x86::reg32(-28) /* -0x1c */) = float(fpu13);
    // 004db7bc  d94610                 -fld dword ptr [esi + 0x10]
    x86::Float fpu14 = x86::Float(app->getMemory<float>(cpu.esi + x86::reg32(16) /* 0x10 */));
    // 004db7bf  d84710                 -fadd dword ptr [edi + 0x10]
    x86::Float fpu15 = cpu.fpu.add(fpu14, x86::Float(app->getMemory<float>(cpu.edi + x86::reg32(16) /* 0x10 */)));
    // 004db7c2  d8c9                   -fmul st(1)
    x86::Float fpu16 = cpu.fpu.mul(fpu15, x86::Float(fpu3));
    // 004db7c4  d95de8                 -fstp dword ptr [ebp - 0x18]
    app->getMemory<float>(cpu.ebp + x86::reg32(-24) /* -0x18 */) = float(fpu16);
    // 004db7c7  d94614                 -fld dword ptr [esi + 0x14]
    x86::Float fpu17 = x86::Float(app->getMemory<float>(cpu.esi + x86::reg32(20) /* 0x14 */));
    // 004db7ca  d84714                 -fadd dword ptr [edi + 0x14]
    x86::Float fpu18 = cpu.fpu.add(fpu17, x86::Float(app->getMemory<float>(cpu.edi + x86::reg32(20) /* 0x14 */)));
    // 004db7cd  dec9                   -fmulp st(1)
    x86::Float fpu19 = cpu.fpu.mul(fpu3, fpu18);
    // 004db7cf  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 004db7d1  8b5514                 -mov edx, dword ptr [ebp + 0x14]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(20) /* 0x14 */);
    // 004db7d4  88d8                   -mov al, bl
    cpu.al = cpu.bl;
    // 004db7d6  81e1ff000000           -and ecx, 0xff
    cpu.ecx &= x86::reg32(x86::sreg32(255 /*0xff*/));
    // 004db7dc  8945f0                 -mov dword ptr [ebp - 0x10], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = cpu.eax;
    // 004db7df  01c8                   -add eax, ecx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.ecx));
    // 004db7e1  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004db7e2  d1f8                   -sar eax, 1
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (1 /*0x1*/ % 32));
    // 004db7e4  d95dec                 -fstp dword ptr [ebp - 0x14]
    app->getMemory<float>(cpu.ebp + x86::reg32(-20) /* -0x14 */) = float(fpu19);
    // 004db7e7  25ff000000             -and eax, 0xff
    cpu.eax &= x86::reg32(x86::sreg32(255 /*0xff*/));
    // 004db7ec  8d5dd8                 -lea ebx, [ebp - 0x28]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-40) /* -0x28 */);
    // 004db7ef  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 004db7f2  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004db7f3  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004db7f6  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 004db7f8  40                     -inc eax
    (cpu.eax)++;
    // 004db7f9  8b7514                 -mov esi, dword ptr [ebp + 0x14]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(20) /* 0x14 */);
    // 004db7fc  8945f4                 -mov dword ptr [ebp - 0xc], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.eax;
    }
    // 004db7ff  e84cffffff             -call 0x4db750
    cpu.esp -= 4;
    sub_4db750(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004db804  8b45f0                 -mov eax, dword ptr [ebp - 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 004db807  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004db808  8b4dfc                 -mov ecx, dword ptr [ebp - 4]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004db80b  8d55d8                 -lea edx, [ebp - 0x28]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-40) /* -0x28 */);
    // 004db80e  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004db80f  89fb                   -mov ebx, edi
    cpu.ebx = cpu.edi;
    // 004db811  8b45f4                 -mov eax, dword ptr [ebp - 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 004db814  e837ffffff             -call 0x4db750
    cpu.esp -= 4;
    sub_4db750(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004db819  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004db81b  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004db81c  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004db81d  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004db81e  c20800                 -ret 8
    cpu.esp += 4+8 /*0x8*/;
    return;
L_0x004db821:
    // 004db821  8b5514                 -mov edx, dword ptr [ebp + 0x14]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(20) /* 0x14 */);
    // 004db824  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004db825  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 004db827  88da                   -mov dl, bl
    cpu.dl = cpu.bl;
    // 004db829  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
    // 004db82b  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004db82d  88cb                   -mov bl, cl
    cpu.bl = cpu.cl;
    // 004db82f  89d1                   -mov ecx, edx
    cpu.ecx = cpu.edx;
    // 004db831  89fa                   -mov edx, edi
    cpu.edx = cpu.edi;
    // 004db833  e878b4feff             -call 0x4c6cb0
    cpu.esp -= 4;
    sub_4c6cb0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004db838  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004db83a  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004db83b  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004db83c  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004db83d  c20800                 -ret 8
    cpu.esp += 4+8 /*0x8*/;
    return;
L_0x004db840:
    // 004db840  8b4514                 -mov eax, dword ptr [ebp + 0x14]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(20) /* 0x14 */);
    // 004db843  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004db844  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 004db846  88d8                   -mov al, bl
    cpu.al = cpu.bl;
    // 004db848  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
    // 004db84a  89fa                   -mov edx, edi
    cpu.edx = cpu.edi;
    // 004db84c  88cb                   -mov bl, cl
    cpu.bl = cpu.cl;
    // 004db84e  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 004db850  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004db852  e859b4feff             -call 0x4c6cb0
    cpu.esp -= 4;
    sub_4c6cb0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004db857  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004db859  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004db85a  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004db85b  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004db85c  c20800                 -ret 8
    cpu.esp += 4+8 /*0x8*/;
    return;
}

/* align: skip 0x90 */
void Application::sub_4db860(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004db860  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004db861  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004db862  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004db863  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004db865  89d1                   -mov ecx, edx
    cpu.ecx = cpu.edx;
    // 004db867  83e00f                 -and eax, 0xf
    cpu.eax &= x86::reg32(x86::sreg32(15 /*0xf*/));
    // 004db86a  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004db86c  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 004db86f  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 004db871  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 004db874  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 004db876  bba07b8b00             -mov ebx, 0x8b7ba0
    cpu.ebx = 9141152 /*0x8b7ba0*/;
    // 004db87b  c1e004                 -shl eax, 4
    cpu.eax <<= 4 /*0x4*/ % 32;
    // 004db87e  89ca                   -mov edx, ecx
    cpu.edx = cpu.ecx;
    // 004db880  01c3                   -add ebx, eax
    (cpu.ebx) += x86::reg32(x86::sreg32(cpu.eax));
    // 004db882  8d049500000000         -lea eax, [edx*4]
    cpu.eax = x86::reg32(cpu.edx * 4);
    // 004db889  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 004db88b  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 004db88e  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 004db890  c744832c00000000       -mov dword ptr [ebx + eax*4 + 0x2c], 0
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(44) /* 0x2c */ + cpu.eax * 4) = 0 /*0x0*/;
    // 004db898  c744833000000000       -mov dword ptr [ebx + eax*4 + 0x30], 0
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(48) /* 0x30 */ + cpu.eax * 4) = 0 /*0x0*/;
    // 004db8a0  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004db8a1  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004db8a2  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004db8a3  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 */
void Application::sub_4db8b0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004db8b0  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004db8b1  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004db8b2  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004db8b3  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004db8b5  83ec18                 -sub esp, 0x18
    (cpu.esp) -= x86::reg32(x86::sreg32(24 /*0x18*/));
    // 004db8b8  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 004db8ba  89cf                   -mov edi, ecx
    cpu.edi = cpu.ecx;
    // 004db8bc  8b4d10                 -mov ecx, dword ptr [ebp + 0x10]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(16) /* 0x10 */);
    // 004db8bf  d903                   -fld dword ptr [ebx]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.ebx));
    // 004db8c1  d822                   -fsub dword ptr [edx]
    x86::Float fpu2 = cpu.fpu.sub(fpu1, x86::Float(app->getMemory<float>(cpu.edx)));
    // 004db8c3  d95de8                 -fstp dword ptr [ebp - 0x18]
    app->getMemory<float>(cpu.ebp + x86::reg32(-24) /* -0x18 */) = float(fpu2);
    // 004db8c6  d94304                 -fld dword ptr [ebx + 4]
    x86::Float fpu3 = x86::Float(app->getMemory<float>(cpu.ebx + x86::reg32(4) /* 0x4 */));
    // 004db8c9  d86204                 -fsub dword ptr [edx + 4]
    x86::Float fpu4 = cpu.fpu.sub(fpu3, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(4) /* 0x4 */)));
    // 004db8cc  8d45e8                 -lea eax, [ebp - 0x18]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-24) /* -0x18 */);
    // 004db8cf  d95dec                 -fstp dword ptr [ebp - 0x14]
    app->getMemory<float>(cpu.ebp + x86::reg32(-20) /* -0x14 */) = float(fpu4);
    // 004db8d2  d94308                 -fld dword ptr [ebx + 8]
    x86::Float fpu5 = x86::Float(app->getMemory<float>(cpu.ebx + x86::reg32(8) /* 0x8 */));
    // 004db8d5  d86208                 -fsub dword ptr [edx + 8]
    x86::Float fpu6 = cpu.fpu.sub(fpu5, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(8) /* 0x8 */)));
    // 004db8d8  8d5df4                 -lea ebx, [ebp - 0xc]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 004db8db  d95df0                 -fstp dword ptr [ebp - 0x10]
    app->getMemory<float>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = float(fpu6);
    }
    // 004db8de  e80dbafbff             -call 0x4972f0
    cpu.esp -= 4;
    nfs3hp::vertices::normalise(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004db8e3  89fa                   -mov edx, edi
    cpu.edx = cpu.edi;
    // 004db8e5  8d45e8                 -lea eax, [ebp - 0x18]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-24) /* -0x18 */);
    // 004db8e8  ddd8                   -fstp st(0)
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu7 = cpu.fpu.st(0);
    x86::Float fpu8 = x86::Float(fpu7);
    cpu.fpu.count -= 1;
    }
    // 004db8ea  e871480000             -call 0x4e0160
    cpu.esp -= 4;
    sub_4e0160(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004db8ef  dd0514975400           -fld qword ptr [0x549714]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu9 = x86::Float(app->getMemory<double>(x86::reg32(5543700) /* 0x549714 */));
    // 004db8f5  d945f4                 -fld dword ptr [ebp - 0xc]
    x86::Float fpu10 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */));
    // 004db8f8  d8c9                   -fmul st(1)
    x86::Float fpu11 = cpu.fpu.mul(fpu10, x86::Float(fpu9));
    // 004db8fa  d82e                   -fsubr dword ptr [esi]
    x86::Float fpu12 = cpu.fpu.sub(x86::Float(app->getMemory<float>(cpu.esi)), fpu11);
    // 004db8fc  d919                   -fstp dword ptr [ecx]
    app->getMemory<float>(cpu.ecx) = float(fpu12);
    // 004db8fe  d945f8                 -fld dword ptr [ebp - 8]
    x86::Float fpu13 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */));
    // 004db901  d8c9                   -fmul st(1)
    x86::Float fpu14 = cpu.fpu.mul(fpu13, x86::Float(fpu9));
    // 004db903  d86e04                 -fsubr dword ptr [esi + 4]
    x86::Float fpu15 = cpu.fpu.sub(x86::Float(app->getMemory<float>(cpu.esi + x86::reg32(4) /* 0x4 */)), fpu14);
    // 004db906  d95904                 -fstp dword ptr [ecx + 4]
    app->getMemory<float>(cpu.ecx + x86::reg32(4) /* 0x4 */) = float(fpu15);
    // 004db909  d945fc                 -fld dword ptr [ebp - 4]
    x86::Float fpu16 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */));
    // 004db90c  d8c9                   -fmul st(1)
    x86::Float fpu17 = cpu.fpu.mul(fpu16, x86::Float(fpu9));
    // 004db90e  d86e08                 -fsubr dword ptr [esi + 8]
    x86::Float fpu18 = cpu.fpu.sub(x86::Float(app->getMemory<float>(cpu.esi + x86::reg32(8) /* 0x8 */)), fpu17);
    // 004db911  d95908                 -fstp dword ptr [ecx + 8]
    app->getMemory<float>(cpu.ecx + x86::reg32(8) /* 0x8 */) = float(fpu18);
    // 004db914  d945f4                 -fld dword ptr [ebp - 0xc]
    x86::Float fpu19 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */));
    // 004db917  d8c9                   -fmul st(1)
    x86::Float fpu20 = cpu.fpu.mul(fpu19, x86::Float(fpu9));
    // 004db919  d806                   -fadd dword ptr [esi]
    x86::Float fpu21 = cpu.fpu.add(fpu20, x86::Float(app->getMemory<float>(cpu.esi)));
    // 004db91b  d9590c                 -fstp dword ptr [ecx + 0xc]
    app->getMemory<float>(cpu.ecx + x86::reg32(12) /* 0xc */) = float(fpu21);
    // 004db91e  d945f8                 -fld dword ptr [ebp - 8]
    x86::Float fpu22 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */));
    // 004db921  d8c9                   -fmul st(1)
    x86::Float fpu23 = cpu.fpu.mul(fpu22, x86::Float(fpu9));
    // 004db923  d84604                 -fadd dword ptr [esi + 4]
    x86::Float fpu24 = cpu.fpu.add(fpu23, x86::Float(app->getMemory<float>(cpu.esi + x86::reg32(4) /* 0x4 */)));
    // 004db926  d95910                 -fstp dword ptr [ecx + 0x10]
    app->getMemory<float>(cpu.ecx + x86::reg32(16) /* 0x10 */) = float(fpu24);
    // 004db929  d84dfc                 -fmul dword ptr [ebp - 4]
    x86::Float fpu25 = cpu.fpu.mul(fpu9, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 004db92c  d84608                 -fadd dword ptr [esi + 8]
    x86::Float fpu26 = cpu.fpu.add(fpu25, x86::Float(app->getMemory<float>(cpu.esi + x86::reg32(8) /* 0x8 */)));
    // 004db92f  d95914                 -fstp dword ptr [ecx + 0x14]
    app->getMemory<float>(cpu.ecx + x86::reg32(20) /* 0x14 */) = float(fpu26);
    // 004db932  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004db934  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004db935  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004db936  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    }
    // 004db937  c20400                 -ret 4
    cpu.esp += 4+4 /*0x4*/;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 */
void Application::sub_4db940(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004db940  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004db941  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004db942  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004db943  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004db945  83ec40                 -sub esp, 0x40
    (cpu.esp) -= x86::reg32(x86::sreg32(64 /*0x40*/));
    // 004db948  89d6                   -mov esi, edx
    cpu.esi = cpu.edx;
    // 004db94a  db03                   -fild dword ptr [ebx]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebx)));
    // 004db94c  83e00f                 -and eax, 0xf
    cpu.eax &= x86::reg32(x86::sreg32(15 /*0xf*/));
    // 004db94f  dd051c975400           -fld qword ptr [0x54971c]
    x86::Float fpu2 = x86::Float(app->getMemory<double>(x86::reg32(5543708) /* 0x54971c */));
    // 004db955  d9c9                   -fxch st(1)
    
    // 004db957  d8c9                   -fmul st(1)
    x86::Float fpu3 = cpu.fpu.mul(fpu1, x86::Float(fpu2));
    // 004db959  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004db95b  d95de4                 -fstp dword ptr [ebp - 0x1c]
    app->getMemory<float>(cpu.ebp + x86::reg32(-28) /* -0x1c */) = float(fpu3);
    // 004db95e  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 004db961  db4304                 -fild dword ptr [ebx + 4]
    x86::Float fpu4 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(4) /* 0x4 */)));
    // 004db964  d8c9                   -fmul st(1)
    x86::Float fpu5 = cpu.fpu.mul(fpu4, x86::Float(fpu2));
    // 004db966  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 004db968  d95de8                 -fstp dword ptr [ebp - 0x18]
    app->getMemory<float>(cpu.ebp + x86::reg32(-24) /* -0x18 */) = float(fpu5);
    // 004db96b  db4308                 -fild dword ptr [ebx + 8]
    x86::Float fpu6 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(8) /* 0x8 */)));
    // 004db96e  d8c9                   -fmul st(1)
    x86::Float fpu7 = cpu.fpu.mul(fpu6, x86::Float(fpu2));
    // 004db970  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 004db973  d95dec                 -fstp dword ptr [ebp - 0x14]
    app->getMemory<float>(cpu.ebp + x86::reg32(-20) /* -0x14 */) = float(fpu7);
    // 004db976  db01                   -fild dword ptr [ecx]
    x86::Float fpu8 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ecx)));
    // 004db978  d8c9                   -fmul st(1)
    x86::Float fpu9 = cpu.fpu.mul(fpu8, x86::Float(fpu2));
    // 004db97a  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 004db97c  bfa07b8b00             -mov edi, 0x8b7ba0
    cpu.edi = 9141152 /*0x8b7ba0*/;
    // 004db981  c1e004                 -shl eax, 4
    cpu.eax <<= 4 /*0x4*/ % 32;
    // 004db984  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 004db986  01c7                   -add edi, eax
    (cpu.edi) += x86::reg32(x86::sreg32(cpu.eax));
    // 004db988  8d049500000000         -lea eax, [edx*4]
    cpu.eax = x86::reg32(cpu.edx * 4);
    // 004db98f  d95dd8                 -fstp dword ptr [ebp - 0x28]
    app->getMemory<float>(cpu.ebp + x86::reg32(-40) /* -0x28 */) = float(fpu9);
    // 004db992  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 004db994  db4104                 -fild dword ptr [ecx + 4]
    x86::Float fpu10 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(4) /* 0x4 */)));
    // 004db997  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 004db99a  d8c9                   -fmul st(1)
    x86::Float fpu11 = cpu.fpu.mul(fpu10, x86::Float(fpu2));
    // 004db99c  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 004db99e  d95ddc                 -fstp dword ptr [ebp - 0x24]
    app->getMemory<float>(cpu.ebp + x86::reg32(-36) /* -0x24 */) = float(fpu11);
    // 004db9a1  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 004db9a4  db4108                 -fild dword ptr [ecx + 8]
    x86::Float fpu12 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(8) /* 0x8 */)));
    // 004db9a7  dec9                   -fmulp st(1)
    x86::Float fpu13 = cpu.fpu.mul(fpu2, fpu12);
    // 004db9a9  01c7                   +add edi, eax
    {
        x86::reg32& tmp1 = cpu.edi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.eax));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 004db9ab  d9ee                   +fldz 
    x86::Float fpu14 = 0.0;
    // 004db9ad  897dfc                 -mov dword ptr [ebp - 4], edi
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.edi;
    // 004db9b0  d9c9                   +fxch st(1)
    
    // 004db9b2  d95de0                 +fstp dword ptr [ebp - 0x20]
    app->getMemory<float>(cpu.ebp + x86::reg32(-32) /* -0x20 */) = float(fpu13);
    // 004db9b5  d85d14                 +fcomp dword ptr [ebp + 0x14]
    cpu.fpu.compare(fpu14, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(20) /* 0x14 */)));
    // 004db9b8  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 004db9ba  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 004db9bb  7607                   -jbe 0x4db9c4
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x004db9c4;
    }
    // 004db9bd  31d2                   +xor edx, edx
    cpu.clear_co();
    cpu.set_szp((cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx))));
    // 004db9bf  8955f8                 -mov dword ptr [ebp - 8], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.edx;
    // 004db9c2  eb06                   -jmp 0x4db9ca
    goto L_0x004db9ca;
L_0x004db9c4:
    // 004db9c4  8b4514                 -mov eax, dword ptr [ebp + 0x14]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(20) /* 0x14 */);
    // 004db9c7  8945f8                 -mov dword ptr [ebp - 8], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.eax;
L_0x004db9ca:
    // 004db9ca  d9e8                   +fld1 
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu15 = 1.0;
    // 004db9cc  d85df8                 +fcomp dword ptr [ebp - 8]
    cpu.fpu.compare(fpu15, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    // 004db9cf  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 004db9d1  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 004db9d2  7608                   -jbe 0x4db9dc
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x004db9dc;
    }
    // 004db9d4  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004db9d7  8945f4                 -mov dword ptr [ebp - 0xc], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.eax;
    // 004db9da  eb07                   -jmp 0x4db9e3
    goto L_0x004db9e3;
L_0x004db9dc:
    // 004db9dc  c745f40000803f         -mov dword ptr [ebp - 0xc], 0x3f800000
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = 1065353216 /*0x3f800000*/;
L_0x004db9e3:
    // 004db9e3  d945f4                 -fld dword ptr [ebp - 0xc]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu16 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */));
    // 004db9e6  dc0d24975400           -fmul qword ptr [0x549724]
    x86::Float fpu17 = cpu.fpu.mul(fpu16, x86::Float(app->getMemory<double>(x86::reg32(5543716) /* 0x549724 */)));
    // 004db9ec  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 004db9ef  db1c24                 -fistp dword ptr [esp]
    app->getMemory<x86::reg32>(cpu.esp) = x86::reg32(cpu.fpu.toInteger<x86::sreg32>(fpu17));
    // 004db9f2  58                     -pop eax
    cpu.eax = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004db9f3  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004db9f5  c1e003                 -shl eax, 3
    cpu.eax <<= 3 /*0x3*/ % 32;
    // 004db9f8  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 004db9fa  c1e004                 -shl eax, 4
    cpu.eax <<= 4 /*0x4*/ % 32;
    // 004db9fd  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 004db9ff  c1f810                 -sar eax, 0x10
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (16 /*0x10*/ % 32));
    // 004dba02  8b5d10                 -mov ebx, dword ptr [ebp + 0x10]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(16) /* 0x10 */);
    // 004dba05  8945f0                 -mov dword ptr [ebp - 0x10], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = cpu.eax;
    // 004dba08  85db                   +test ebx, ebx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & cpu.ebx));
    }
    // 004dba0a  7512                   -jne 0x4dba1e
    if (!cpu.flags.zf)
    {
        goto L_0x004dba1e;
    }
    // 004dba0c  8b55fc                 -mov edx, dword ptr [ebp - 4]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004dba0f  a184367d00             -mov eax, dword ptr [0x7d3684]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(8205956) /* 0x7d3684 */);
    // 004dba14  2b02                   -sub eax, dword ptr [edx]
    (cpu.eax) -= x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.edx)));
    // 004dba16  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004dba18  0f8e70010000           -jle 0x4dbb8e
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004dbb8e;
    }
L_0x004dba1e:
    // 004dba1e  8b55fc                 -mov edx, dword ptr [ebp - 4]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004dba21  a184367d00             -mov eax, dword ptr [0x7d3684]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(8205956) /* 0x7d3684 */);
    // 004dba26  8b7a2c                 -mov edi, dword ptr [edx + 0x2c]
    cpu.edi = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(44) /* 0x2c */);
    // 004dba29  8902                   -mov dword ptr [edx], eax
    app->getMemory<x86::reg32>(cpu.edx) = cpu.eax;
    // 004dba2b  85ff                   +test edi, edi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edi & cpu.edi));
    // 004dba2d  753e                   -jne 0x4dba6d
    if (!cpu.flags.zf)
    {
        goto L_0x004dba6d;
    }
    // 004dba2f  837d1000               +cmp dword ptr [ebp + 0x10], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(16) /* 0x10 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004dba33  0f8555010000           -jne 0x4dbb8e
    if (!cpu.flags.zf)
    {
        goto L_0x004dbb8e;
    }
    // 004dba39  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004dba3b  c7422c01000000         -mov dword ptr [edx + 0x2c], 1
    app->getMemory<x86::reg32>(cpu.edx + x86::reg32(44) /* 0x2c */) = 1 /*0x1*/;
    // 004dba42  8d75e4                 -lea esi, [ebp - 0x1c]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(-28) /* -0x1c */);
    // 004dba45  8d7804                 -lea edi, [eax + 4]
    cpu.edi = x86::reg32(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 004dba48  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004dba49  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004dba4a  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004dba4b  8d75e4                 -lea esi, [ebp - 0x1c]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(-28) /* -0x1c */);
    // 004dba4e  8d7810                 -lea edi, [eax + 0x10]
    cpu.edi = x86::reg32(cpu.eax + x86::reg32(16) /* 0x10 */);
    // 004dba51  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004dba52  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004dba53  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004dba54  8d75e4                 -lea esi, [ebp - 0x1c]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(-28) /* -0x1c */);
    // 004dba57  8d781c                 -lea edi, [eax + 0x1c]
    cpu.edi = x86::reg32(cpu.eax + x86::reg32(28) /* 0x1c */);
    // 004dba5a  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004dba5b  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004dba5c  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004dba5d  c7423001000000         -mov dword ptr [edx + 0x30], 1
    app->getMemory<x86::reg32>(cpu.edx + x86::reg32(48) /* 0x30 */) = 1 /*0x1*/;
    // 004dba64  c6422800               -mov byte ptr [edx + 0x28], 0
    app->getMemory<x86::reg8>(cpu.edx + x86::reg32(40) /* 0x28 */) = 0 /*0x0*/;
    // 004dba68  e921010000             -jmp 0x4dbb8e
    goto L_0x004dbb8e;
L_0x004dba6d:
    // 004dba6d  8d7a04                 -lea edi, [edx + 4]
    cpu.edi = x86::reg32(cpu.edx + x86::reg32(4) /* 0x4 */);
    // 004dba70  8d721c                 -lea esi, [edx + 0x1c]
    cpu.esi = x86::reg32(cpu.edx + x86::reg32(28) /* 0x1c */);
    // 004dba73  837d1000               +cmp dword ptr [ebp + 0x10], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(16) /* 0x10 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004dba77  0f8478000000           -je 0x4dbaf5
    if (cpu.flags.zf)
    {
        goto L_0x004dbaf5;
    }
    // 004dba7d  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004dba80  83783000               +cmp dword ptr [eax + 0x30], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(48) /* 0x30 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004dba84  755d                   -jne 0x4dbae3
    if (!cpu.flags.zf)
    {
        goto L_0x004dbae3;
    }
    // 004dba86  8d55e4                 -lea edx, [ebp - 0x1c]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-28) /* -0x1c */);
    // 004dba89  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004dba8b  68cdcc4c3e             -push 0x3e4ccccd
    app->getMemory<x86::reg32>(cpu.esp-4) = 1045220557 /*0x3e4ccccd*/;
    cpu.esp -= 4;
    // 004dba90  e88bb4fbff             -call 0x496f20
    cpu.esp -= 4;
    sub_496f20(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dba95  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004dba97  754a                   -jne 0x4dbae3
    if (!cpu.flags.zf)
    {
        goto L_0x004dbae3;
    }
    // 004dba99  8d45c0                 -lea eax, [ebp - 0x40]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-64) /* -0x40 */);
    // 004dba9c  8d4dd8                 -lea ecx, [ebp - 0x28]
    cpu.ecx = x86::reg32(cpu.ebp + x86::reg32(-40) /* -0x28 */);
    // 004dba9f  8d5de4                 -lea ebx, [ebp - 0x1c]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-28) /* -0x1c */);
    // 004dbaa2  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004dbaa3  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 004dbaa5  8d45e4                 -lea eax, [ebp - 0x1c]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-28) /* -0x1c */);
    // 004dbaa8  e803feffff             -call 0x4db8b0
    cpu.esp -= 4;
    sub_4db8b0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dbaad  6a02                   -push 2
    app->getMemory<x86::reg32>(cpu.esp-4) = 2 /*0x2*/;
    cpu.esp -= 4;
    // 004dbaaf  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004dbab2  8d5dc0                 -lea ebx, [ebp - 0x40]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-64) /* -0x40 */);
    // 004dbab5  89fa                   -mov edx, edi
    cpu.edx = cpu.edi;
    // 004dbab7  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 004dbab9  6a00                   -push 0
    app->getMemory<x86::reg32>(cpu.esp-4) = 0 /*0x0*/;
    cpu.esp -= 4;
    // 004dbabb  8a4828                 -mov cl, byte ptr [eax + 0x28]
    cpu.cl = app->getMemory<x86::reg8>(cpu.eax + x86::reg32(40) /* 0x28 */);
    // 004dbabe  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 004dbac0  e88bfcffff             -call 0x4db750
    cpu.esp -= 4;
    sub_4db750(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dbac5  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004dbac8  8d75c0                 -lea esi, [ebp - 0x40]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(-64) /* -0x40 */);
    // 004dbacb  8d7804                 -lea edi, [eax + 4]
    cpu.edi = x86::reg32(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 004dbace  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004dbacf  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004dbad0  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004dbad1  8d75cc                 -lea esi, [ebp - 0x34]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(-52) /* -0x34 */);
    // 004dbad4  8d7810                 -lea edi, [eax + 0x10]
    cpu.edi = x86::reg32(cpu.eax + x86::reg32(16) /* 0x10 */);
    // 004dbad7  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004dbad8  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004dbad9  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004dbada  8d75e4                 -lea esi, [ebp - 0x1c]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(-28) /* -0x1c */);
    // 004dbadd  8d781c                 -lea edi, [eax + 0x1c]
    cpu.edi = x86::reg32(cpu.eax + x86::reg32(28) /* 0x1c */);
    // 004dbae0  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004dbae1  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004dbae2  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
L_0x004dbae3:
    // 004dbae3  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004dbae6  c7402c00000000         -mov dword ptr [eax + 0x2c], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(44) /* 0x2c */) = 0 /*0x0*/;
    // 004dbaed  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004dbaef  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dbaf0  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dbaf1  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dbaf2  c20800                 -ret 8
    cpu.esp += 4+8 /*0x8*/;
    return;
L_0x004dbaf5:
    // 004dbaf5  8d55e4                 -lea edx, [ebp - 0x1c]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-28) /* -0x1c */);
    // 004dbaf8  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004dbafa  680000003f             -push 0x3f000000
    app->getMemory<x86::reg32>(cpu.esp-4) = 1056964608 /*0x3f000000*/;
    cpu.esp -= 4;
    // 004dbaff  e81cb4fbff             -call 0x496f20
    cpu.esp -= 4;
    sub_496f20(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dbb04  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004dbb06  0f8582000000           -jne 0x4dbb8e
    if (!cpu.flags.zf)
    {
        goto L_0x004dbb8e;
    }
    // 004dbb0c  8d45c0                 -lea eax, [ebp - 0x40]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-64) /* -0x40 */);
    // 004dbb0f  8d4dd8                 -lea ecx, [ebp - 0x28]
    cpu.ecx = x86::reg32(cpu.ebp + x86::reg32(-40) /* -0x28 */);
    // 004dbb12  8d5de4                 -lea ebx, [ebp - 0x1c]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-28) /* -0x1c */);
    // 004dbb15  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004dbb16  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 004dbb18  8d45e4                 -lea eax, [ebp - 0x1c]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-28) /* -0x1c */);
    // 004dbb1b  e890fdffff             -call 0x4db8b0
    cpu.esp -= 4;
    sub_4db8b0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dbb20  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004dbb23  83783000               +cmp dword ptr [eax + 0x30], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(48) /* 0x30 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004dbb27  741a                   -je 0x4dbb43
    if (cpu.flags.zf)
    {
        goto L_0x004dbb43;
    }
    // 004dbb29  8d4dd8                 -lea ecx, [ebp - 0x28]
    cpu.ecx = x86::reg32(cpu.ebp + x86::reg32(-40) /* -0x28 */);
    // 004dbb2c  8d5de4                 -lea ebx, [ebp - 0x1c]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-28) /* -0x1c */);
    // 004dbb2f  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004dbb30  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 004dbb32  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004dbb34  e877fdffff             -call 0x4db8b0
    cpu.esp -= 4;
    sub_4db8b0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dbb39  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004dbb3c  c7403000000000         -mov dword ptr [eax + 0x30], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(48) /* 0x30 */) = 0 /*0x0*/;
L_0x004dbb43:
    // 004dbb43  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 004dbb45  6a01                   -push 1
    app->getMemory<x86::reg32>(cpu.esp-4) = 1 /*0x1*/;
    cpu.esp -= 4;
    // 004dbb47  8a45f0                 -mov al, byte ptr [ebp - 0x10]
    cpu.al = app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 004dbb4a  8d5dc0                 -lea ebx, [ebp - 0x40]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-64) /* -0x40 */);
    // 004dbb4d  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004dbb4e  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004dbb51  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 004dbb53  8d5004                 -lea edx, [eax + 4]
    cpu.edx = x86::reg32(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 004dbb56  8a4828                 -mov cl, byte ptr [eax + 0x28]
    cpu.cl = app->getMemory<x86::reg8>(cpu.eax + x86::reg32(40) /* 0x28 */);
    // 004dbb59  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 004dbb5b  e8f0fbffff             -call 0x4db750
    cpu.esp -= 4;
    sub_4db750(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dbb60  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004dbb63  8d75c0                 -lea esi, [ebp - 0x40]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(-64) /* -0x40 */);
    // 004dbb66  8d7804                 -lea edi, [eax + 4]
    cpu.edi = x86::reg32(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 004dbb69  c7402c01000000         -mov dword ptr [eax + 0x2c], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(44) /* 0x2c */) = 1 /*0x1*/;
    // 004dbb70  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004dbb71  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004dbb72  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004dbb73  8d75cc                 -lea esi, [ebp - 0x34]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(-52) /* -0x34 */);
    // 004dbb76  8d7810                 -lea edi, [eax + 0x10]
    cpu.edi = x86::reg32(cpu.eax + x86::reg32(16) /* 0x10 */);
    // 004dbb79  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004dbb7a  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004dbb7b  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004dbb7c  8d75e4                 -lea esi, [ebp - 0x1c]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(-28) /* -0x1c */);
    // 004dbb7f  8d781c                 -lea edi, [eax + 0x1c]
    cpu.edi = x86::reg32(cpu.eax + x86::reg32(28) /* 0x1c */);
    // 004dbb82  8b55fc                 -mov edx, dword ptr [ebp - 4]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004dbb85  8a45f0                 -mov al, byte ptr [ebp - 0x10]
    cpu.al = app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 004dbb88  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004dbb89  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004dbb8a  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004dbb8b  884228                 -mov byte ptr [edx + 0x28], al
    app->getMemory<x86::reg8>(cpu.edx + x86::reg32(40) /* 0x28 */) = cpu.al;
L_0x004dbb8e:
    // 004dbb8e  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004dbb90  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dbb91  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dbb92  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dbb93  c20800                 -ret 8
    cpu.esp += 4+8 /*0x8*/;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x54 0x22 0x00 */
void Application::sub_4dbba0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004dbba0  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004dbba1  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004dbba2  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004dbba4  ba000d0000             -mov edx, 0xd00
    cpu.edx = 3328 /*0xd00*/;
    // 004dbba9  b8a07b8b00             -mov eax, 0x8b7ba0
    cpu.eax = 9141152 /*0x8b7ba0*/;
    // 004dbbae  e8594b0000             -call 0x4e070c
    cpu.esp -= 4;
    nfs3hp::fillZero(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dbbb3  e81878fcff             -call 0x4a33d0
    cpu.esp -= 4;
    sub_4a33d0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dbbb8  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dbbb9  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dbbba  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x40 0x00 0x8b 0xc9 */
void Application::sub_4dbbc0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004dbbc0  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004dbbc1  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004dbbc2  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004dbbc4  ba000d0000             -mov edx, 0xd00
    cpu.edx = 3328 /*0xd00*/;
    // 004dbbc9  b8a07b8b00             -mov eax, 0x8b7ba0
    cpu.eax = 9141152 /*0x8b7ba0*/;
    // 004dbbce  e8394b0000             -call 0x4e070c
    cpu.esp -= 4;
    nfs3hp::fillZero(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dbbd3  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dbbd4  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dbbd5  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x54 0x22 0x00 */
void Application::sub_4dbbe0(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004dbbe0  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004dbbe1  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004dbbe3  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dbbe4  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 */
void Application::sub_4dbbf0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004dbbf0  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004dbbf1  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004dbbf2  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004dbbf4  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004dbbf6  e8c51ff4ff             -call 0x41dbc0
    cpu.esp -= 4;
    nfs3hp::load::loadTrackTextures(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dbbfb  e8d077fcff             -call 0x4a33d0
    cpu.esp -= 4;
    sub_4a33d0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dbc00  833d8ce8550000         +cmp dword ptr [0x55e88c], 0
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
    // 004dbc07  7408                   -je 0x4dbc11
    if (cpu.flags.zf)
    {
        goto L_0x004dbc11;
    }
    // 004dbc09  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 004dbc0e  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dbc0f  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dbc10  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004dbc11:
    // 004dbc11  6800002042             -push 0x42200000
    app->getMemory<x86::reg32>(cpu.esp-4) = 1109393408 /*0x42200000*/;
    cpu.esp -= 4;
    // 004dbc16  e81596fbff             -call 0x495230
    cpu.esp -= 4;
    nfs3hp::graphics::drawLoadingProgress(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dbc1b  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004dbc1d  e81ec7f9ff             -call 0x478340
    cpu.esp -= 4;
    nfs3hp::load::loadHorizon(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dbc22  e8a977fcff             -call 0x4a33d0
    cpu.esp -= 4;
    sub_4a33d0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dbc27  833d8ce8550000         +cmp dword ptr [0x55e88c], 0
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
    // 004dbc2e  7408                   -je 0x4dbc38
    if (cpu.flags.zf)
    {
        goto L_0x004dbc38;
    }
    // 004dbc30  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 004dbc35  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dbc36  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dbc37  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004dbc38:
    // 004dbc38  6800002c42             -push 0x422c0000
    app->getMemory<x86::reg32>(cpu.esp-4) = 1110179840 /*0x422c0000*/;
    cpu.esp -= 4;
    // 004dbc3d  e8ee95fbff             -call 0x495230
    cpu.esp -= 4;
    nfs3hp::graphics::drawLoadingProgress(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dbc42  e8191df4ff             -call 0x41d960
    cpu.esp -= 4;
    nfs3hp::render::raceViews(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dbc47  e88477fcff             -call 0x4a33d0
    cpu.esp -= 4;
    sub_4a33d0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dbc4c  833d8ce8550000         +cmp dword ptr [0x55e88c], 0
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
    // 004dbc53  7408                   -je 0x4dbc5d
    if (cpu.flags.zf)
    {
        goto L_0x004dbc5d;
    }
    // 004dbc55  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 004dbc5a  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dbc5b  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dbc5c  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004dbc5d:
    // 004dbc5d  6800006842             -push 0x42680000
    app->getMemory<x86::reg32>(cpu.esp-4) = 1114112000 /*0x42680000*/;
    cpu.esp -= 4;
    // 004dbc62  e8c995fbff             -call 0x495230
    cpu.esp -= 4;
    nfs3hp::graphics::drawLoadingProgress(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dbc67  e8040cfeff             -call 0x4bc870
    cpu.esp -= 4;
    sub_4bc870(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dbc6c  e85f77fcff             -call 0x4a33d0
    cpu.esp -= 4;
    sub_4a33d0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dbc71  833d8ce8550000         +cmp dword ptr [0x55e88c], 0
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
    // 004dbc78  7408                   -je 0x4dbc82
    if (cpu.flags.zf)
    {
        goto L_0x004dbc82;
    }
    // 004dbc7a  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 004dbc7f  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dbc80  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dbc81  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004dbc82:
    // 004dbc82  6800007442             -push 0x42740000
    app->getMemory<x86::reg32>(cpu.esp-4) = 1114898432 /*0x42740000*/;
    cpu.esp -= 4;
    // 004dbc87  e8a495fbff             -call 0x495230
    cpu.esp -= 4;
    nfs3hp::graphics::drawLoadingProgress(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dbc8c  e82fc6f9ff             -call 0x4782c0
    cpu.esp -= 4;
    sub_4782c0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dbc91  e83a77fcff             -call 0x4a33d0
    cpu.esp -= 4;
    sub_4a33d0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dbc96  833d8ce8550000         +cmp dword ptr [0x55e88c], 0
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
    // 004dbc9d  7408                   -je 0x4dbca7
    if (cpu.flags.zf)
    {
        goto L_0x004dbca7;
    }
    // 004dbc9f  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 004dbca4  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dbca5  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dbca6  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004dbca7:
    // 004dbca7  6800008042             -push 0x42800000
    app->getMemory<x86::reg32>(cpu.esp-4) = 1115684864 /*0x42800000*/;
    cpu.esp -= 4;
    // 004dbcac  e87f95fbff             -call 0x495230
    cpu.esp -= 4;
    nfs3hp::graphics::drawLoadingProgress(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dbcb1  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 004dbcb3  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dbcb4  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dbcb5  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 */
void Application::sub_4dbcc0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004dbcc0  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004dbcc1  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004dbcc3  a140bc6f00             -mov eax, dword ptr [0x6fbc40]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(7322688) /* 0x6fbc40 */);
    // 004dbcc8  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004dbcca  760c                   -jbe 0x4dbcd8
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x004dbcd8;
    }
    // 004dbccc  83f801                 +cmp eax, 1
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
    // 004dbccf  7507                   -jne 0x4dbcd8
    if (!cpu.flags.zf)
    {
        goto L_0x004dbcd8;
    }
    // 004dbcd1  b84b000000             -mov eax, 0x4b
    cpu.eax = 75 /*0x4b*/;
    // 004dbcd6  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dbcd7  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004dbcd8:
    // 004dbcd8  b85a000000             -mov eax, 0x5a
    cpu.eax = viewAngleFor(app, 90 /*0x5a*/); /* port: View Angle's third choice */
    // 004dbcdd  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dbcde  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x90 */
void Application::sub_4dbce0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004dbce0  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004dbce1  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004dbce2  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004dbce3  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004dbce5  83ec18                 -sub esp, 0x18
    (cpu.esp) -= x86::reg32(x86::sreg32(24 /*0x18*/));
    // 004dbce8  8b7510                 -mov esi, dword ptr [ebp + 0x10]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(16) /* 0x10 */);
    // 004dbceb  8945ec                 -mov dword ptr [ebp - 0x14], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */) = cpu.eax;
    // 004dbcee  89d7                   -mov edi, edx
    cpu.edi = cpu.edx;
    // 004dbcf0  895df4                 -mov dword ptr [ebp - 0xc], ebx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.ebx;
    // 004dbcf3  894df0                 -mov dword ptr [ebp - 0x10], ecx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = cpu.ecx;
    // 004dbcf6  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 004dbcf8  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004dbcfa  c1fa1f                 -sar edx, 0x1f
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (31 /*0x1f*/ % 32));
    // 004dbcfd  2bc2                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 004dbcff  d1f8                   -sar eax, 1
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (1 /*0x1*/ % 32));
    // 004dbd01  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 004dbd03  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 004dbd06  29f0                   -sub eax, esi
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.esi));
    // 004dbd08  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 004dbd0b  8d1406                 -lea edx, [esi + eax]
    cpu.edx = x86::reg32(cpu.esi + cpu.eax * 1);
    // 004dbd0e  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004dbd10  c1fa1f                 -sar edx, 0x1f
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (31 /*0x1f*/ % 32));
    // 004dbd13  c1e204                 +shl edx, 4
    {
        x86::reg8 tmp = 4 /*0x4*/ % 32;
        x86::reg32& op = cpu.edx;
        if (tmp)
        {
            cpu.flags.cf = 1 & (op >> (32 - tmp));
            cpu.set_szp((op <<= tmp));
            if (tmp == 1) cpu.flags.of = (cpu.flags.cf != (1 & (op >> (32 - 1))));
        }
    }
    // 004dbd16  1bc2                   -sbb eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx) + cpu.flags.cf);
    // 004dbd18  c1f804                 -sar eax, 4
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (4 /*0x4*/ % 32));
    // 004dbd1b  8945e8                 -mov dword ptr [ebp - 0x18], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-24) /* -0x18 */) = cpu.eax;
    cpu.esi = widescreenHalfAngle(app, cpu.esi, cpu.eax); /* port: the horizontal angle the view's own shape asks for */
    // 004dbd1e  89fa                   -mov edx, edi
    cpu.edx = cpu.edi;
    // 004dbd20  8b45ec                 -mov eax, dword ptr [ebp - 0x14]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */);
    // 004dbd23  897dfc                 -mov dword ptr [ebp - 4], edi
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.edi;
    // 004dbd26  e855150200             -call 0x4fd280
    cpu.esp -= 4;
    sub_4fd280(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dbd2b  8b55e8                 -mov edx, dword ptr [ebp - 0x18]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-24) /* -0x18 */);
    // 004dbd2e  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004dbd30  8975f8                 -mov dword ptr [ebp - 8], esi
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.esi;
    // 004dbd33  e8b8160200             -call 0x4fd3f0
    cpu.esp -= 4;
    sub_4fd3f0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dbd38  8b5514                 -mov edx, dword ptr [ebp + 0x14]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(20) /* 0x14 */);
    // 004dbd3b  8b45e8                 -mov eax, dword ptr [ebp - 0x18]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-24) /* -0x18 */);
    // 004dbd3e  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004dbd3f  db45f8                 -fild dword ptr [ebp - 8]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    // 004dbd42  8945f8                 -mov dword ptr [ebp - 8], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.eax;
    // 004dbd45  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 004dbd48  db45f8                 -fild dword ptr [ebp - 8]
    x86::Float fpu2 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    // 004dbd4b  d91c24                 -fstp dword ptr [esp]
    app->getMemory<float>(cpu.esp) = float(fpu2);
    // 004dbd4e  8b45f0                 -mov eax, dword ptr [ebp - 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 004dbd51  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 004dbd54  8945f8                 -mov dword ptr [ebp - 8], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.eax;
    // 004dbd57  d91c24                 -fstp dword ptr [esp]
    app->getMemory<float>(cpu.esp) = float(fpu1);
    // 004dbd5a  db45f8                 -fild dword ptr [ebp - 8]
    x86::Float fpu3 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    // 004dbd5d  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 004dbd60  8b45f4                 -mov eax, dword ptr [ebp - 0xc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 004dbd63  d91c24                 -fstp dword ptr [esp]
    app->getMemory<float>(cpu.esp) = float(fpu3);
    // 004dbd66  8945f8                 -mov dword ptr [ebp - 8], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.eax;
    // 004dbd69  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 004dbd6c  db45f8                 -fild dword ptr [ebp - 8]
    x86::Float fpu4 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */)));
    // 004dbd6f  d91c24                 -fstp dword ptr [esp]
    app->getMemory<float>(cpu.esp) = float(fpu4);
    // 004dbd72  db45fc                 -fild dword ptr [ebp - 4]
    x86::Float fpu5 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 004dbd75  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 004dbd78  8b45ec                 -mov eax, dword ptr [ebp - 0x14]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */);
    // 004dbd7b  d91c24                 -fstp dword ptr [esp]
    app->getMemory<float>(cpu.esp) = float(fpu5);
    // 004dbd7e  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 004dbd81  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 004dbd84  db45fc                 -fild dword ptr [ebp - 4]
    x86::Float fpu6 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 004dbd87  d91c24                 -fstp dword ptr [esp]
    app->getMemory<float>(cpu.esp) = float(fpu6);
    }
    // 004dbd8a  e8d134feff             -call 0x4bf260
    cpu.esp -= 4;
    sub_4bf260(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dbd8f  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004dbd91  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dbd92  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dbd93  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dbd94  c20800                 -ret 8
    cpu.esp += 4+8 /*0x8*/;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 */
void Application::sub_4dbda0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004dbda0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004dbda1  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004dbda2  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004dbda3  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004dbda5  833db0d36f0001         +cmp dword ptr [0x6fd3b0], 1
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
    // 004dbdac  7518                   -jne 0x4dbdc6
    if (!cpu.flags.zf)
    {
        goto L_0x004dbdc6;
    }
    // 004dbdae  8b4004                 -mov eax, dword ptr [eax + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 004dbdb1  ba78000000             -mov edx, 0x78
    cpu.edx = 120 /*0x78*/;
    // 004dbdb6  c1e005                 -shl eax, 5
    cpu.eax <<= 5 /*0x5*/ % 32;
    // 004dbdb9  8b1dc4d46f00           -mov ebx, dword ptr [0x6fd4c4]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(7328964) /* 0x6fd4c4 */);
    // 004dbdbf  0580da7c00             +add eax, 0x7cda80
    {
        x86::reg32& tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(8182400 /*0x7cda80*/));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 004dbdc4  eb10                   -jmp 0x4dbdd6
    goto L_0x004dbdd6;
L_0x004dbdc6:
    // 004dbdc6  ba78000000             -mov edx, 0x78
    cpu.edx = 120 /*0x78*/;
    // 004dbdcb  b888db7c00             -mov eax, 0x7cdb88
    cpu.eax = 8182664 /*0x7cdb88*/;
    // 004dbdd0  8b1dc4d46f00           -mov ebx, dword ptr [0x6fd4c4]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(7328964) /* 0x6fd4c4 */);
L_0x004dbdd6:
    // 004dbdd6  e8452ffeff             -call 0x4bed20
    cpu.esp -= 4;
    sub_4bed20(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dbddb  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dbddc  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dbddd  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dbdde  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x90 */
void Application::sub_4dbde0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004dbde0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004dbde1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004dbde2  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004dbde3  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004dbde4  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004dbde5  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004dbde7  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 004dbde9  8b10                   -mov edx, dword ptr [eax]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax);
    // 004dbdeb  83fa01                 +cmp edx, 1
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
    // 004dbdee  7525                   -jne 0x4dbe15
    if (!cpu.flags.zf)
    {
        goto L_0x004dbe15;
    }
    // 004dbdf0  833dc4d46f0000         +cmp dword ptr [0x6fd4c4], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(7328964) /* 0x6fd4c4 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004dbdf7  7504                   -jne 0x4dbdfd
    if (!cpu.flags.zf)
    {
        goto L_0x004dbdfd;
    }
    // 004dbdf9  89d3                   -mov ebx, edx
    cpu.ebx = cpu.edx;
    // 004dbdfb  eb02                   -jmp 0x4dbdff
    goto L_0x004dbdff;
L_0x004dbdfd:
    // 004dbdfd  31db                   +xor ebx, ebx
    cpu.clear_co();
    cpu.set_szp((cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx))));
L_0x004dbdff:
    // 004dbdff  e8bcfeffff             -call 0x4dbcc0
    cpu.esp -= 4;
    sub_4dbcc0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dbe04  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004dbe06  b848db7c00             -mov eax, 0x7cdb48
    cpu.eax = 8182600 /*0x7cdb48*/;
    // 004dbe0b  e8102ffeff             -call 0x4bed20
    cpu.esp -= 4;
    sub_4bed20(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dbe10  e9cb000000             -jmp 0x4dbee0
    goto L_0x004dbee0;
L_0x004dbe15:
    // 004dbe15  833db0d36f0001         +cmp dword ptr [0x6fd3b0], 1
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
    // 004dbe1c  751d                   -jne 0x4dbe3b
    if (!cpu.flags.zf)
    {
        goto L_0x004dbe3b;
    }
    // 004dbe1e  8b1dc4d46f00           -mov ebx, dword ptr [0x6fd4c4]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(7328964) /* 0x6fd4c4 */);
    // 004dbe24  e897feffff             -call 0x4dbcc0
    cpu.esp -= 4;
    sub_4dbcc0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dbe29  8b7104                 -mov esi, dword ptr [ecx + 4]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(4) /* 0x4 */);
    // 004dbe2c  c1e605                 -shl esi, 5
    cpu.esi <<= 5 /*0x5*/ % 32;
    // 004dbe2f  81c680da7c00           +add esi, 0x7cda80
    {
        x86::reg32& tmp1 = cpu.esi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(8182400 /*0x7cda80*/));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 004dbe35  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004dbe37  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004dbe39  eb12                   -jmp 0x4dbe4d
    goto L_0x004dbe4d;
L_0x004dbe3b:
    // 004dbe3b  8b1dc4d46f00           -mov ebx, dword ptr [0x6fd4c4]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(7328964) /* 0x6fd4c4 */);
    // 004dbe41  e87afeffff             -call 0x4dbcc0
    cpu.esp -= 4;
    sub_4dbcc0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dbe46  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004dbe48  b888db7c00             -mov eax, 0x7cdb88
    cpu.eax = 8182664 /*0x7cdb88*/;
L_0x004dbe4d:
    // 004dbe4d  e8ce2efeff             -call 0x4bed20
    cpu.esp -= 4;
    sub_4bed20(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dbe52  8b4104                 -mov eax, dword ptr [ecx + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(4) /* 0x4 */);
    // 004dbe55  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 004dbe58  8bb0b8105e00           -mov esi, dword ptr [eax + 0x5e10b8]
    cpu.esi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164664) /* 0x5e10b8 */);
    // 004dbe5e  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 004dbe60  7404                   -je 0x4dbe66
    if (cpu.flags.zf)
    {
        goto L_0x004dbe66;
    }
    // 004dbe62  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004dbe64  eb06                   -jmp 0x4dbe6c
    goto L_0x004dbe6c;
L_0x004dbe66:
    // 004dbe66  8b80b0105e00           -mov eax, dword ptr [eax + 0x5e10b0]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164656) /* 0x5e10b0 */);
L_0x004dbe6c:
    // 004dbe6c  f74054ffffff7f         +test dword ptr [eax + 0x54], 0x7fffffff
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(app->getMemory<x86::reg32>(cpu.eax + x86::reg32(84) /* 0x54 */) & 2147483647 /*0x7fffffff*/));
    // 004dbe73  746b                   -je 0x4dbee0
    if (cpu.flags.zf)
    {
        goto L_0x004dbee0;
    }
    // 004dbe75  8b4104                 -mov eax, dword ptr [ecx + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(4) /* 0x4 */);
    // 004dbe78  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 004dbe7b  8b90b8105e00           -mov edx, dword ptr [eax + 0x5e10b8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164664) /* 0x5e10b8 */);
    // 004dbe81  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 004dbe83  7404                   -je 0x4dbe89
    if (cpu.flags.zf)
    {
        goto L_0x004dbe89;
    }
    // 004dbe85  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004dbe87  eb06                   -jmp 0x4dbe8f
    goto L_0x004dbe8f;
L_0x004dbe89:
    // 004dbe89  8b80b0105e00           -mov eax, dword ptr [eax + 0x5e10b0]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164656) /* 0x5e10b0 */);
L_0x004dbe8f:
    // 004dbe8f  d905ac005600           -fld dword ptr [0x5600ac]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(zoomHalfWidth(app)) /* port: a racing zoom camera's x scale is its y scale on a wide view */;
    // 004dbe95  d84854                 -fmul dword ptr [eax + 0x54]
    x86::Float fpu2 = cpu.fpu.mul(fpu1, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(84) /* 0x54 */)));
    // 004dbe98  8b4104                 -mov eax, dword ptr [ecx + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(4) /* 0x4 */);
    // 004dbe9b  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 004dbe9e  8b88b8105e00           -mov ecx, dword ptr [eax + 0x5e10b8]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164664) /* 0x5e10b8 */);
    // 004dbea4  d91d9c005600           -fstp dword ptr [0x56009c]
    app->getMemory<float>(x86::reg32(5636252) /* 0x56009c */) = float(fpu2);
    // 004dbeaa  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    }
    // 004dbeac  7404                   -je 0x4dbeb2
    if (cpu.flags.zf)
    {
        goto L_0x004dbeb2;
    }
    // 004dbeae  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004dbeb0  eb06                   -jmp 0x4dbeb8
    goto L_0x004dbeb8;
L_0x004dbeb2:
    // 004dbeb2  8b80b0105e00           -mov eax, dword ptr [eax + 0x5e10b0]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164656) /* 0x5e10b0 */);
L_0x004dbeb8:
    // 004dbeb8  d905b0005600           -fld dword ptr [0x5600b0]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu3 = x86::Float(app->getMemory<float>(x86::reg32(5636272) /* 0x5600b0 */));
    // 004dbebe  d9e0                   -fchs 
    x86::Float fpu4 = -fpu3;
    // 004dbec0  d84854                 -fmul dword ptr [eax + 0x54]
    x86::Float fpu5 = cpu.fpu.mul(fpu4, x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(84) /* 0x54 */)));
    // 004dbec3  dc0d2c975400           -fmul qword ptr [0x54972c]
    x86::Float fpu6 = cpu.fpu.mul(fpu5, x86::Float(app->getMemory<double>(x86::reg32(5543724) /* 0x54972c */)));
    // 004dbec9  8b1dc4d46f00           -mov ebx, dword ptr [0x6fd4c4]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(7328964) /* 0x6fd4c4 */);
    // 004dbecf  d91da0005600           -fstp dword ptr [0x5600a0]
    app->getMemory<float>(x86::reg32(5636256) /* 0x5600a0 */) = float(fpu6);
    // 004dbed5  85db                   +test ebx, ebx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & cpu.ebx));
    }
    // 004dbed7  7407                   -je 0x4dbee0
    if (cpu.flags.zf)
    {
        goto L_0x004dbee0;
    }
    // 004dbed9  80359f00560080         -xor byte ptr [0x56009f], 0x80
    app->getMemory<x86::reg8>(x86::reg32(5636255) /* 0x56009f */) ^= x86::reg8(x86::sreg8(128 /*0x80*/));
L_0x004dbee0:
    // 004dbee0  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dbee1  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dbee2  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dbee3  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dbee4  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dbee5  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_4dbef0: native, nfs3hp::vertices::objectVerticesList */

/* align: skip 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 */
void Application::sub_4dc0e0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004dc0e0  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004dc0e1  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004dc0e2  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004dc0e3  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004dc0e4  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004dc0e6  83ec0c                 -sub esp, 0xc
    (cpu.esp) -= x86::reg32(x86::sreg32(12 /*0xc*/));
    // 004dc0e9  89c7                   -mov edi, eax
    cpu.edi = cpu.eax;
    // 004dc0eb  89d1                   -mov ecx, edx
    cpu.ecx = cpu.edx;
    // 004dc0ed  895dfc                 -mov dword ptr [ebp - 4], ebx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.ebx;
    // 004dc0f0  bb10000000             -mov ebx, 0x10
    cpu.ebx = 16 /*0x10*/;
    // 004dc0f5  ba0c000000             -mov edx, 0xc
    cpu.edx = 12 /*0xc*/;
    // 004dc0fa  b834975400             -mov eax, 0x549734
    cpu.eax = 5543732 /*0x549734*/;
    // 004dc0ff  e81c550000             -call 0x4e1620
    cpu.esp -= 4;
    nfs3hp::ea::reservememadr(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dc104  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 004dc106  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004dc108  751a                   -jne 0x4dc124
    if (!cpu.flags.zf)
    {
        goto L_0x004dc124;
    }
    // 004dc10a  837dfc00               +cmp dword ptr [ebp - 4], 0
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
    // 004dc10e  740d                   -je 0x4dc11d
    if (cpu.flags.zf)
    {
        goto L_0x004dc11d;
    }
    // 004dc110  6838975400             -push 0x549738
    app->getMemory<x86::reg32>(cpu.esp-4) = 5543736 /*0x549738*/;
    cpu.esp -= 4;
    // 004dc115  e8f64ef2ff             -call 0x401010
    cpu.esp -= 4;
    nfs3hp::Error(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dc11a  83c404                 -add esp, 4
    (cpu.esp) += x86::reg32(x86::sreg32(4 /*0x4*/));
L_0x004dc11d:
    // 004dc11d  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
    // 004dc11f  e981000000             -jmp 0x4dc1a5
    goto L_0x004dc1a5;
L_0x004dc124:
    // 004dc124  85ff                   +test edi, edi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edi & cpu.edi));
    // 004dc126  7504                   -jne 0x4dc12c
    if (!cpu.flags.zf)
    {
        goto L_0x004dc12c;
    }
    // 004dc128  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    // 004dc12a  7408                   -je 0x4dc134
    if (cpu.flags.zf)
    {
        goto L_0x004dc134;
    }
L_0x004dc12c:
    // 004dc12c  85ff                   +test edi, edi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edi & cpu.edi));
    // 004dc12e  742b                   -je 0x4dc15b
    if (cpu.flags.zf)
    {
        goto L_0x004dc15b;
    }
    // 004dc130  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    // 004dc132  7427                   -je 0x4dc15b
    if (cpu.flags.zf)
    {
        goto L_0x004dc15b;
    }
L_0x004dc134:
    // 004dc134  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 004dc136  7407                   -je 0x4dc13f
    if (cpu.flags.zf)
    {
        goto L_0x004dc13f;
    }
    // 004dc138  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004dc13a  e851570000             -call 0x4e1890
    cpu.esp -= 4;
    nfs3hp::ea::purgememadr(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x004dc13f:
    // 004dc13f  837dfc00               +cmp dword ptr [ebp - 4], 0
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
    // 004dc143  740d                   -je 0x4dc152
    if (cpu.flags.zf)
    {
        goto L_0x004dc152;
    }
    // 004dc145  6858975400             -push 0x549758
    app->getMemory<x86::reg32>(cpu.esp-4) = 5543768 /*0x549758*/;
    cpu.esp -= 4;
    // 004dc14a  e8c14ef2ff             -call 0x401010
    cpu.esp -= 4;
    nfs3hp::Error(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dc14f  83c404                 -add esp, 4
    (cpu.esp) += x86::reg32(x86::sreg32(4 /*0x4*/));
L_0x004dc152:
    // 004dc152  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 004dc154  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004dc156  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dc157  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dc158  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dc159  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dc15a  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004dc15b:
    // 004dc15b  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    // 004dc15d  7412                   -je 0x4dc171
    if (cpu.flags.zf)
    {
        goto L_0x004dc171;
    }
    // 004dc15f  c7460400000000         -mov dword ptr [esi + 4], 0
    app->getMemory<x86::reg32>(cpu.esi + x86::reg32(4) /* 0x4 */) = 0 /*0x0*/;
    // 004dc166  c70601000000           -mov dword ptr [esi], 1
    app->getMemory<x86::reg32>(cpu.esi) = 1 /*0x1*/;
    // 004dc16c  894e08                 -mov dword ptr [esi + 8], ecx
    app->getMemory<x86::reg32>(cpu.esi + x86::reg32(8) /* 0x8 */) = cpu.ecx;
    // 004dc16f  eb32                   -jmp 0x4dc1a3
    goto L_0x004dc1a3;
L_0x004dc171:
    // 004dc171  8d5df4                 -lea ebx, [ebp - 0xc]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 004dc174  894df4                 -mov dword ptr [ebp - 0xc], ecx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.ecx;
    // 004dc177  894df8                 -mov dword ptr [ebp - 8], ecx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.ecx;
    // 004dc17a  8d5604                 -lea edx, [esi + 4]
    cpu.edx = x86::reg32(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 004dc17d  890e                   -mov dword ptr [esi], ecx
    app->getMemory<x86::reg32>(cpu.esi) = cpu.ecx;
    // 004dc17f  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 004dc181  894e08                 -mov dword ptr [esi + 8], ecx
    app->getMemory<x86::reg32>(cpu.esi + x86::reg32(8) /* 0x8 */) = cpu.ecx;
    // 004dc184  8d4df8                 -lea ecx, [ebp - 8]
    cpu.ecx = x86::reg32(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004dc187  e844670000             -call 0x4e28d0
    cpu.esp -= 4;
    nfs3hp::ea::openHandle(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dc18c  8b5604                 -mov edx, dword ptr [esi + 4]
    cpu.edx = app->getMemory<x86::reg32>(cpu.esi + x86::reg32(4) /* 0x4 */);
    // 004dc18f  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 004dc191  7510                   -jne 0x4dc1a3
    if (!cpu.flags.zf)
    {
        goto L_0x004dc1a3;
    }
    // 004dc193  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004dc195  e8f6560000             -call 0x4e1890
    cpu.esp -= 4;
    nfs3hp::ea::purgememadr(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dc19a  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 004dc19c  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004dc19e  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dc19f  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dc1a0  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dc1a1  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dc1a2  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004dc1a3:
    // 004dc1a3  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
L_0x004dc1a5:
    // 004dc1a5  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004dc1a7  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dc1a8  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dc1a9  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dc1aa  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dc1ab  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x44 0x20 0x00 */
void Application::sub_4dc1b0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004dc1b0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004dc1b1  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004dc1b2  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004dc1b3  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004dc1b5  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004dc1b7  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004dc1b9  741a                   -je 0x4dc1d5
    if (cpu.flags.zf)
    {
        goto L_0x004dc1d5;
    }
    // 004dc1bb  833800                 +cmp dword ptr [eax], 0
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
    // 004dc1be  750e                   -jne 0x4dc1ce
    if (!cpu.flags.zf)
    {
        goto L_0x004dc1ce;
    }
    // 004dc1c0  8b5804                 -mov ebx, dword ptr [eax + 4]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 004dc1c3  85db                   +test ebx, ebx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & cpu.ebx));
    // 004dc1c5  7407                   -je 0x4dc1ce
    if (cpu.flags.zf)
    {
        goto L_0x004dc1ce;
    }
    // 004dc1c7  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 004dc1c9  e8d26b0000             -call 0x4e2da0
    cpu.esp -= 4;
    nfs3hp::ea::closeHandle(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x004dc1ce:
    // 004dc1ce  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004dc1d0  e8bb560000             -call 0x4e1890
    cpu.esp -= 4;
    nfs3hp::ea::purgememadr(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x004dc1d5:
    // 004dc1d5  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dc1d6  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dc1d7  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dc1d8  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x90 */
void Application::sub_4dc1e0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004dc1e0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004dc1e1  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004dc1e2  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004dc1e3  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004dc1e5  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 004dc1e8  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004dc1ea  833800                 +cmp dword ptr [eax], 0
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
    // 004dc1ed  751b                   -jne 0x4dc20a
    if (!cpu.flags.zf)
    {
        goto L_0x004dc20a;
    }
    // 004dc1ef  bb04000000             -mov ebx, 4
    cpu.ebx = 4 /*0x4*/;
    // 004dc1f4  8d55fc                 -lea edx, [ebp - 4]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004dc1f7  8b4004                 -mov eax, dword ptr [eax + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 004dc1fa  e8e16b0000             -call 0x4e2de0
    cpu.esp -= 4;
    nfs3hp::ea::readHandle(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dc1ff  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004dc201  7513                   -jne 0x4dc216
    if (!cpu.flags.zf)
    {
        goto L_0x004dc216;
    }
    // 004dc203  e875680100             -call 0x4f2a7d
    cpu.esp -= 4;
    sub_4f2a7d(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dc208  eb0c                   -jmp 0x4dc216
    goto L_0x004dc216;
L_0x004dc20a:
    // 004dc20a  8b4008                 -mov eax, dword ptr [eax + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 004dc20d  8b00                   -mov eax, dword ptr [eax]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax);
    // 004dc20f  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 004dc212  83420804               -add dword ptr [edx + 8], 4
    (app->getMemory<x86::reg32>(cpu.edx + x86::reg32(8) /* 0x8 */)) += x86::reg32(x86::sreg32(4 /*0x4*/));
L_0x004dc216:
    // 004dc216  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004dc219  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004dc21b  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dc21c  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dc21d  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dc21e  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x90 */
void Application::sub_4dc220(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004dc220  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004dc221  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004dc222  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004dc223  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004dc225  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 004dc228  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004dc22a  833800                 +cmp dword ptr [eax], 0
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
    // 004dc22d  751b                   -jne 0x4dc24a
    if (!cpu.flags.zf)
    {
        goto L_0x004dc24a;
    }
    // 004dc22f  bb01000000             -mov ebx, 1
    cpu.ebx = 1 /*0x1*/;
    // 004dc234  8d55fc                 -lea edx, [ebp - 4]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004dc237  8b4004                 -mov eax, dword ptr [eax + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 004dc23a  e8a16b0000             -call 0x4e2de0
    cpu.esp -= 4;
    nfs3hp::ea::readHandle(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dc23f  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004dc241  7512                   -jne 0x4dc255
    if (!cpu.flags.zf)
    {
        goto L_0x004dc255;
    }
    // 004dc243  e835680100             -call 0x4f2a7d
    cpu.esp -= 4;
    sub_4f2a7d(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dc248  eb0b                   -jmp 0x4dc255
    goto L_0x004dc255;
L_0x004dc24a:
    // 004dc24a  8b4008                 -mov eax, dword ptr [eax + 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 004dc24d  8a00                   -mov al, byte ptr [eax]
    cpu.al = app->getMemory<x86::reg8>(cpu.eax);
    // 004dc24f  8845fc                 -mov byte ptr [ebp - 4], al
    app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.al;
    // 004dc252  ff4208                 -inc dword ptr [edx + 8]
    (app->getMemory<x86::reg32>(cpu.edx + x86::reg32(8) /* 0x8 */))++;
L_0x004dc255:
    // 004dc255  8a45fc                 -mov al, byte ptr [ebp - 4]
    cpu.al = app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004dc258  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004dc25a  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dc25b  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dc25c  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dc25d  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8b 0xc0 */
void Application::sub_4dc260(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004dc260  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004dc261  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004dc262  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004dc264  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 004dc267  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 004dc269  8955fc                 -mov dword ptr [ebp - 4], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.edx;
    // 004dc26c  833800                 +cmp dword ptr [eax], 0
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
    // 004dc26f  751e                   -jne 0x4dc28f
    if (!cpu.flags.zf)
    {
        goto L_0x004dc28f;
    }
    // 004dc271  bb04000000             -mov ebx, 4
    cpu.ebx = 4 /*0x4*/;
    // 004dc276  8d55fc                 -lea edx, [ebp - 4]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004dc279  8b4004                 -mov eax, dword ptr [eax + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 004dc27c  e89f6b0000             -call 0x4e2e20
    cpu.esp -= 4;
    nfs3hp::ea::writeHandle(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dc281  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004dc283  7516                   -jne 0x4dc29b
    if (!cpu.flags.zf)
    {
        goto L_0x004dc29b;
    }
    // 004dc285  e8f3670100             -call 0x4f2a7d
    cpu.esp -= 4;
    sub_4f2a7d(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dc28a  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004dc28c  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dc28d  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dc28e  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004dc28f:
    // 004dc28f  8b5008                 -mov edx, dword ptr [eax + 8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 004dc292  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004dc295  8902                   -mov dword ptr [edx], eax
    app->getMemory<x86::reg32>(cpu.edx) = cpu.eax;
    // 004dc297  83430804               -add dword ptr [ebx + 8], 4
    (app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(8) /* 0x8 */)) += x86::reg32(x86::sreg32(4 /*0x4*/));
L_0x004dc29b:
    // 004dc29b  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004dc29d  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dc29e  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dc29f  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip  */
void Application::sub_4dc2a0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004dc2a0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004dc2a1  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004dc2a2  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004dc2a4  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 004dc2a7  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 004dc2a9  8855fc                 -mov byte ptr [ebp - 4], dl
    app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.dl;
    // 004dc2ac  833800                 +cmp dword ptr [eax], 0
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
    // 004dc2af  751e                   -jne 0x4dc2cf
    if (!cpu.flags.zf)
    {
        goto L_0x004dc2cf;
    }
    // 004dc2b1  bb01000000             -mov ebx, 1
    cpu.ebx = 1 /*0x1*/;
    // 004dc2b6  8d55fc                 -lea edx, [ebp - 4]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004dc2b9  8b4004                 -mov eax, dword ptr [eax + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 004dc2bc  e85f6b0000             -call 0x4e2e20
    cpu.esp -= 4;
    nfs3hp::ea::writeHandle(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dc2c1  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004dc2c3  7515                   -jne 0x4dc2da
    if (!cpu.flags.zf)
    {
        goto L_0x004dc2da;
    }
    // 004dc2c5  e8b3670100             -call 0x4f2a7d
    cpu.esp -= 4;
    sub_4f2a7d(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dc2ca  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004dc2cc  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dc2cd  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dc2ce  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004dc2cf:
    // 004dc2cf  8b5008                 -mov edx, dword ptr [eax + 8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 004dc2d2  8a45fc                 -mov al, byte ptr [ebp - 4]
    cpu.al = app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004dc2d5  8802                   -mov byte ptr [edx], al
    app->getMemory<x86::reg8>(cpu.edx) = cpu.al;
    // 004dc2d7  ff4308                 -inc dword ptr [ebx + 8]
    (app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(8) /* 0x8 */))++;
L_0x004dc2da:
    // 004dc2da  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004dc2dc  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dc2dd  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dc2de  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x90 */
void Application::sub_4dc2e0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004dc2e0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004dc2e1  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004dc2e2  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004dc2e4  bb40420f00             -mov ebx, 0xf4240
    cpu.ebx = 1000000 /*0xf4240*/;
    // 004dc2e9  e812000000             -call 0x4dc300
    cpu.esp -= 4;
    sub_4dc300(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dc2ee  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dc2ef  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dc2f0  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x8d 0x40 0x00 */
void Application::sub_4dc300(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004dc300  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004dc301  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004dc302  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004dc303  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004dc304  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004dc306  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 004dc308  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004dc30a  833900                 +cmp dword ptr [ecx], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.ecx);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004dc30d  7537                   -jne 0x4dc346
    if (!cpu.flags.zf)
    {
        goto L_0x004dc346;
    }
    // 004dc30f  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004dc311  31f6                   -xor esi, esi
    cpu.esi ^= x86::reg32(x86::sreg32(cpu.esi));
    // 004dc313  31ff                   -xor edi, edi
    cpu.edi ^= x86::reg32(x86::sreg32(cpu.edi));
    // 004dc315  83fb01                 +cmp ebx, 1
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
    // 004dc318  7508                   -jne 0x4dc322
    if (!cpu.flags.zf)
    {
        goto L_0x004dc322;
    }
    // 004dc31a  c60000                 -mov byte ptr [eax], 0
    app->getMemory<x86::reg8>(cpu.eax) = 0 /*0x0*/;
    // 004dc31d  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dc31e  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dc31f  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dc320  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dc321  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004dc322:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004dc322  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004dc324  e8f7feffff             -call 0x4dc220
    cpu.esp -= 4;
    sub_4dc220(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dc329  8802                   -mov byte ptr [edx], al
    app->getMemory<x86::reg8>(cpu.edx) = cpu.al;
    // 004dc32b  84c0                   +test al, al
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.al & cpu.al));
    // 004dc32d  7505                   -jne 0x4dc334
    if (!cpu.flags.zf)
    {
        goto L_0x004dc334;
    }
    // 004dc32f  bf01000000             -mov edi, 1
    cpu.edi = 1 /*0x1*/;
L_0x004dc334:
    // 004dc334  46                     -inc esi
    (cpu.esi)++;
    // 004dc335  42                     -inc edx
    (cpu.edx)++;
    // 004dc336  39de                   +cmp esi, ebx
    {
        x86::reg32 tmp1 = cpu.esi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ebx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004dc338  7508                   -jne 0x4dc342
    if (!cpu.flags.zf)
    {
        goto L_0x004dc342;
    }
    // 004dc33a  c60200                 -mov byte ptr [edx], 0
    app->getMemory<x86::reg8>(cpu.edx) = 0 /*0x0*/;
    // 004dc33d  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dc33e  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dc33f  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dc340  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dc341  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004dc342:
    // 004dc342  85ff                   +test edi, edi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edi & cpu.edi));
    // 004dc344  74dc                   -je 0x4dc322
    if (cpu.flags.zf)
    {
        goto L_0x004dc322;
    }
L_0x004dc346:
    // 004dc346  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dc347  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dc348  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dc349  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dc34a  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x40 0x00 0x8b 0xc9 */
void Application::sub_4dc350(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004dc350  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004dc351  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004dc352  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004dc353  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004dc354  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004dc356  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 004dc359  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 004dc35c  833800                 +cmp dword ptr [eax], 0
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
    // 004dc35f  7513                   -jne 0x4dc374
    if (!cpu.flags.zf)
    {
        goto L_0x004dc374;
    }
    // 004dc361  8b4004                 -mov eax, dword ptr [eax + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 004dc364  e8776a0000             -call 0x4e2de0
    cpu.esp -= 4;
    nfs3hp::ea::readHandle(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dc369  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004dc36b  7524                   -jne 0x4dc391
    if (!cpu.flags.zf)
    {
        goto L_0x004dc391;
    }
    // 004dc36d  e80b670100             -call 0x4f2a7d
    cpu.esp -= 4;
    sub_4f2a7d(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dc372  eb1d                   -jmp 0x4dc391
    goto L_0x004dc391;
L_0x004dc374:
    // 004dc374  89d9                   -mov ecx, ebx
    cpu.ecx = cpu.ebx;
    // 004dc376  89d7                   -mov edi, edx
    cpu.edi = cpu.edx;
    // 004dc378  8b7008                 -mov esi, dword ptr [eax + 8]
    cpu.esi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */);
    // 004dc37b  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004dc37c  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004dc37e  c1e902                 -shr ecx, 2
    cpu.ecx >>= 2 /*0x2*/ % 32;
    // 004dc381  f2a5                   -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004dc383  8ac8                   -mov cl, al
    cpu.cl = cpu.al;
    // 004dc385  80e103                 +and cl, 3
    cpu.clear_co();
    cpu.set_szp((cpu.cl &= x86::reg8(x86::sreg8(3 /*0x3*/))));
    // 004dc388  f2a4                   -repne movsb byte ptr es:[edi], byte ptr [esi]
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
    // 004dc38a  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dc38b  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004dc38e  015808                 -add dword ptr [eax + 8], ebx
    (app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */)) += x86::reg32(x86::sreg32(cpu.ebx));
L_0x004dc391:
    // 004dc391  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004dc393  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dc394  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dc395  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dc396  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dc397  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_4dc3a0: native, nfs3hp::load::setSpecUsed */

/* sub_4dc3f0: native, nfs3hp::load::specUsed */

/* sub_4dc440: native, nfs3hp::load::specCarName */

/* sub_4dc490: native, nfs3hp::load::findSpec */

/* sub_4dc500: native, nfs3hp::load::freeSpecSlot */

/* align: skip 0x8d 0x40 0x00 0x8b 0xc9 */
void Application::sub_4dc550(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004dc550  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004dc551  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004dc552  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004dc553  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004dc555  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
    // 004dc557  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 004dc559  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004dc55b  7507                   -jne 0x4dc564
    if (!cpu.flags.zf)
    {
        goto L_0x004dc564;
    }
    // 004dc55d  b900928b00             -mov ecx, 0x8b9200
    cpu.ecx = 9146880 /*0x8b9200*/;
    // 004dc562  eb0a                   -jmp 0x4dc56e
    goto L_0x004dc56e;
L_0x004dc564:
    // 004dc564  83f801                 +cmp eax, 1
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
    // 004dc567  7505                   -jne 0x4dc56e
    if (!cpu.flags.zf)
    {
        goto L_0x004dc56e;
    }
    // 004dc569  b9a0888b00             -mov ecx, 0x8b88a0
    cpu.ecx = 9144480 /*0x8b88a0*/;
L_0x004dc56e:
    // 004dc56e  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    // 004dc570  741d                   -je 0x4dc58f
    if (cpu.flags.zf)
    {
        goto L_0x004dc58f;
    }
    // 004dc572  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 004dc574  7419                   -je 0x4dc58f
    if (cpu.flags.zf)
    {
        goto L_0x004dc58f;
    }
    // 004dc576  e815ffffff             -call 0x4dc490
    cpu.esp -= 4;
    nfs3hp::load::findSpec(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dc57b  83f8ff                 +cmp eax, -1
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
    // 004dc57e  740f                   -je 0x4dc58f
    if (cpu.flags.zf)
    {
        goto L_0x004dc58f;
    }
    // 004dc580  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004dc582  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 004dc585  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 004dc587  c1e004                 -shl eax, 4
    cpu.eax <<= 4 /*0x4*/ % 32;
    // 004dc58a  01c8                   -add eax, ecx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.ecx));
    // 004dc58c  8d5814                 -lea ebx, [eax + 0x14]
    cpu.ebx = x86::reg32(cpu.eax + x86::reg32(20) /* 0x14 */);
L_0x004dc58f:
    // 004dc58f  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 004dc591  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dc592  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dc593  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dc594  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_4dc5a0: native, nfs3hp::load::setSpec */

/* sub_4dc670: native, nfs3hp::load::defaultSpecs */

/* sub_4dc710: native, nfs3hp::load::refreshSpecs */

/* sub_4dc800: native, nfs3hp::load::specPath */

/* sub_4dc8b0: native, nfs3hp::load::readSpecs */

/* sub_4dc940: native, nfs3hp::load::loadPlayerSpecs */

/* sub_4dca50: native, nfs3hp::load::savePlayerSpecs */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x8b 0xc0 */
void Application::sub_4dcaf0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (tuningAdvancedDiffers(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 004dcaf0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004dcaf1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004dcaf2  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004dcaf3  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004dcaf4  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004dcaf5  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004dcaf7  83ec08                 -sub esp, 8
    (cpu.esp) -= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 004dcafa  8945f8                 -mov dword ptr [ebp - 8], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.eax;
    // 004dcafd  89d3                   -mov ebx, edx
    cpu.ebx = cpu.edx;
    // 004dcaff  30e4                   -xor ah, ah
    cpu.ah ^= x86::reg8(x86::sreg8(cpu.ah));
    // 004dcb01  8b55f8                 -mov edx, dword ptr [ebp - 8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004dcb04  8865fc                 -mov byte ptr [ebp - 4], ah
    app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.ah;
    // 004dcb07  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 004dcb09  743b                   -je 0x4dcb46
    if (cpu.flags.zf)
    {
        goto L_0x004dcb46;
    }
    // 004dcb0b  85db                   +test ebx, ebx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & cpu.ebx));
    // 004dcb0d  7437                   -je 0x4dcb46
    if (cpu.flags.zf)
    {
        goto L_0x004dcb46;
    }
    // 004dcb0f  31d2                   +xor edx, edx
    cpu.clear_co();
    cpu.set_szp((cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx))));
    // 004dcb11  eb06                   -jmp 0x4dcb19
    goto L_0x004dcb19;
L_0x004dcb13:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004dcb13  42                     -inc edx
    (cpu.edx)++;
    // 004dcb14  83fa32                 +cmp edx, 0x32
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(50 /*0x32*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004dcb17  7d2d                   -jge 0x4dcb46
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004dcb46;
    }
L_0x004dcb19:
    // 004dcb19  8d049500000000         -lea eax, [edx*4]
    cpu.eax = x86::reg32(cpu.edx * 4);
    // 004dcb20  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 004dcb22  c1e004                 -shl eax, 4
    cpu.eax <<= 4 /*0x4*/ % 32;
    // 004dcb25  8b4df8                 -mov ecx, dword ptr [ebp - 8]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004dcb28  8d3c03                 -lea edi, [ebx + eax]
    cpu.edi = x86::reg32(cpu.ebx + cpu.eax * 1);
    // 004dcb2b  8d3408                 -lea esi, [eax + ecx]
    cpu.esi = x86::reg32(cpu.eax + cpu.ecx * 1);
    // 004dcb2e  b930000000             -mov ecx, 0x30
    cpu.ecx = 48 /*0x30*/;
    // 004dcb33  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
    // 004dcb35  f3a6                   +repe cmpsb byte ptr [esi], byte ptr es:[edi]
    while (cpu.ecx)
    {
        {
            x86::reg8 tmp1 = app->getMemory<x86::reg8>(cpu.esi);
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
            cpu.esi -= 1;
        }
        else
        {
            cpu.edi += 1;
            cpu.esi += 1;
        }
        --cpu.ecx;
        if (!cpu.flags.zf)
            break;
    }
    // 004dcb37  7405                   -je 0x4dcb3e
    if (cpu.flags.zf)
    {
        goto L_0x004dcb3e;
    }
    // 004dcb39  19c0                   +sbb eax, eax
    {
        x86::reg32& tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.eax));
        const bool carry = cpu.flags.cf;
        x86::reg32 result = tmp1 - tmp2 - carry;
        cpu.flags.cf = tmp1 < tmp2 || (carry && tmp1 == tmp2);
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 004dcb3b  83d8ff                 -sbb eax, -1
    (cpu.eax) -= x86::reg32(x86::sreg32(-1 /*-0x1*/) + cpu.flags.cf);
L_0x004dcb3e:
    // 004dcb3e  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004dcb40  74d1                   -je 0x4dcb13
    if (cpu.flags.zf)
    {
        goto L_0x004dcb13;
    }
    // 004dcb42  c645fc01               -mov byte ptr [ebp - 4], 1
    app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = 1 /*0x1*/;
L_0x004dcb46:
    // 004dcb46  8a45fc                 -mov al, byte ptr [ebp - 4]
    cpu.al = app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004dcb49  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004dcb4b  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dcb4c  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dcb4d  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dcb4e  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dcb4f  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dcb50  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x8d 0x40 0x00 */
void Application::sub_4dcb60(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (tuningCopyAdvanced(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 004dcb60  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004dcb61  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004dcb62  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004dcb63  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004dcb64  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004dcb65  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004dcb67  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 004dcb6a  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 004dcb6c  8955fc                 -mov dword ptr [ebp - 4], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.edx;
    // 004dcb6f  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004dcb71  7439                   -je 0x4dcbac
    if (cpu.flags.zf)
    {
        goto L_0x004dcbac;
    }
    // 004dcb73  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 004dcb75  7435                   -je 0x4dcbac
    if (cpu.flags.zf)
    {
        goto L_0x004dcbac;
    }
    // 004dcb77  31d2                   +xor edx, edx
    cpu.clear_co();
    cpu.set_szp((cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx))));
    // 004dcb79  eb05                   -jmp 0x4dcb80
    goto L_0x004dcb80;
L_0x004dcb7b:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004dcb7b  83fa32                 +cmp edx, 0x32
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(50 /*0x32*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004dcb7e  7d2c                   -jge 0x4dcbac
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004dcbac;
    }
L_0x004dcb80:
    // 004dcb80  8d049500000000         -lea eax, [edx*4]
    cpu.eax = x86::reg32(cpu.edx * 4);
    // 004dcb87  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 004dcb89  8b75fc                 -mov esi, dword ptr [ebp - 4]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004dcb8c  c1e004                 -shl eax, 4
    cpu.eax <<= 4 /*0x4*/ % 32;
    // 004dcb8f  b930000000             -mov ecx, 0x30
    cpu.ecx = 48 /*0x30*/;
    // 004dcb94  01c6                   -add esi, eax
    (cpu.esi) += x86::reg32(x86::sreg32(cpu.eax));
    // 004dcb96  8d3c03                 -lea edi, [ebx + eax]
    cpu.edi = x86::reg32(cpu.ebx + cpu.eax * 1);
    // 004dcb99  42                     -inc edx
    (cpu.edx)++;
    // 004dcb9a  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004dcb9b  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004dcb9d  c1e902                 -shr ecx, 2
    cpu.ecx >>= 2 /*0x2*/ % 32;
    // 004dcba0  f2a5                   -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004dcba2  8ac8                   -mov cl, al
    cpu.cl = cpu.al;
    // 004dcba4  80e103                 +and cl, 3
    cpu.clear_co();
    cpu.set_szp((cpu.cl &= x86::reg8(x86::sreg8(3 /*0x3*/))));
    // 004dcba7  f2a4                   -repne movsb byte ptr es:[edi], byte ptr [esi]
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
    // 004dcba9  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dcbaa  ebcf                   -jmp 0x4dcb7b
    goto L_0x004dcb7b;
L_0x004dcbac:
    // 004dcbac  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004dcbae  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dcbaf  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dcbb0  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dcbb1  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dcbb2  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dcbb3  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 */
void Application::sub_4dcbc0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004dcbc0  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004dcbc1  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004dcbc2  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004dcbc3  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004dcbc4  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004dcbc5  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004dcbc7  a1bcd26f00             -mov eax, dword ptr [0x6fd2bc]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(7328444) /* 0x6fd2bc */);
    // 004dcbcc  e87fcef5ff             -call 0x439a50
    cpu.esp -= 4;
    nfs3hp::load::carRecord(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dcbd1  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004dcbd3  746b                   -je 0x4dcc40
    if (cpu.flags.zf)
    {
        goto L_0x004dcc40;
    }
    // 004dcbd5  a1bcd26f00             -mov eax, dword ptr [0x6fd2bc]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(7328444) /* 0x6fd2bc */);
    // 004dcbda  e841c9f5ff             -call 0x439520
    cpu.esp -= 4;
    nfs3hp::load::carId(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dcbdf  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004dcbe1  743c                   -je 0x4dcc1f
    if (cpu.flags.zf)
    {
        goto L_0x004dcc1f;
    }
    // 004dcbe3  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004dcbe5  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 004dcbe7  e864f9ffff             -call 0x4dc550
    cpu.esp -= 4;
    sub_4dc550(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dcbec  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004dcbee  740e                   -je 0x4dcbfe
    if (cpu.flags.zf)
    {
        goto L_0x004dcbfe;
    }
    // 004dcbf0  b91c000000             -mov ecx, 0x1c
    cpu.ecx = 28 /*0x1c*/;
    // 004dcbf5  bf0cd36f00             -mov edi, 0x6fd30c
    cpu.edi = 7328524 /*0x6fd30c*/;
    // 004dcbfa  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 004dcbfc  eb0f                   -jmp 0x4dcc0d
    goto L_0x004dcc0d;
L_0x004dcbfe:
    // 004dcbfe  b91c000000             -mov ecx, 0x1c
    cpu.ecx = 28 /*0x1c*/;
    // 004dcc03  be24d05500             -mov esi, 0x55d024
    cpu.esi = 5623844 /*0x55d024*/;
    // 004dcc08  bf0cd36f00             -mov edi, 0x6fd30c
    cpu.edi = 7328524 /*0x6fd30c*/;
L_0x004dcc0d:
    // 004dcc0d  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004dcc0e  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004dcc10  c1e902                 -shr ecx, 2
    cpu.ecx >>= 2 /*0x2*/ % 32;
    // 004dcc13  f2a5                   -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004dcc15  8ac8                   -mov cl, al
    cpu.cl = cpu.al;
    // 004dcc17  80e103                 +and cl, 3
    cpu.clear_co();
    cpu.set_szp((cpu.cl &= x86::reg8(x86::sreg8(3 /*0x3*/))));
    // 004dcc1a  f2a4                   -repne movsb byte ptr es:[edi], byte ptr [esi]
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
    // 004dcc1c  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dcc1d  eb40                   -jmp 0x4dcc5f
    goto L_0x004dcc5f;
L_0x004dcc1f:
    // 004dcc1f  b91c000000             -mov ecx, 0x1c
    cpu.ecx = 28 /*0x1c*/;
    // 004dcc24  be24d05500             -mov esi, 0x55d024
    cpu.esi = 5623844 /*0x55d024*/;
    // 004dcc29  bf0cd36f00             -mov edi, 0x6fd30c
    cpu.edi = 7328524 /*0x6fd30c*/;
    // 004dcc2e  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004dcc2f  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004dcc31  c1e902                 -shr ecx, 2
    cpu.ecx >>= 2 /*0x2*/ % 32;
    // 004dcc34  f2a5                   -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004dcc36  8ac8                   -mov cl, al
    cpu.cl = cpu.al;
    // 004dcc38  80e103                 +and cl, 3
    cpu.clear_co();
    cpu.set_szp((cpu.cl &= x86::reg8(x86::sreg8(3 /*0x3*/))));
    // 004dcc3b  f2a4                   -repne movsb byte ptr es:[edi], byte ptr [esi]
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
    // 004dcc3d  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dcc3e  eb1f                   -jmp 0x4dcc5f
    goto L_0x004dcc5f;
L_0x004dcc40:
    // 004dcc40  b91c000000             -mov ecx, 0x1c
    cpu.ecx = 28 /*0x1c*/;
    // 004dcc45  be24d05500             -mov esi, 0x55d024
    cpu.esi = 5623844 /*0x55d024*/;
    // 004dcc4a  bf0cd36f00             -mov edi, 0x6fd30c
    cpu.edi = 7328524 /*0x6fd30c*/;
    // 004dcc4f  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004dcc50  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004dcc52  c1e902                 -shr ecx, 2
    cpu.ecx >>= 2 /*0x2*/ % 32;
    // 004dcc55  f2a5                   -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004dcc57  8ac8                   -mov cl, al
    cpu.cl = cpu.al;
    // 004dcc59  80e103                 +and cl, 3
    cpu.clear_co();
    cpu.set_szp((cpu.cl &= x86::reg8(x86::sreg8(3 /*0x3*/))));
    // 004dcc5c  f2a4                   -repne movsb byte ptr es:[edi], byte ptr [esi]
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
    // 004dcc5e  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
L_0x004dcc5f:
    // 004dcc5f  a128d36f00             -mov eax, dword ptr [0x6fd328]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(7328552) /* 0x6fd328 */);
    // 004dcc64  e8e7cdf5ff             -call 0x439a50
    cpu.esp -= 4;
    nfs3hp::load::carRecord(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dcc69  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004dcc6b  0f8472000000           -je 0x4dcce3
    if (cpu.flags.zf)
    {
        goto L_0x004dcce3;
    }
    // 004dcc71  a128d36f00             -mov eax, dword ptr [0x6fd328]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(7328552) /* 0x6fd328 */);
    // 004dcc76  e8a5c8f5ff             -call 0x439520
    cpu.esp -= 4;
    nfs3hp::load::carId(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dcc7b  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004dcc7d  743f                   -je 0x4dccbe
    if (cpu.flags.zf)
    {
        goto L_0x004dccbe;
    }
    // 004dcc7f  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004dcc81  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 004dcc86  e8c5f8ffff             -call 0x4dc550
    cpu.esp -= 4;
    sub_4dc550(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dcc8b  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004dcc8d  740e                   -je 0x4dcc9d
    if (cpu.flags.zf)
    {
        goto L_0x004dcc9d;
    }
    // 004dcc8f  b91c000000             -mov ecx, 0x1c
    cpu.ecx = 28 /*0x1c*/;
    // 004dcc94  bf78d36f00             -mov edi, 0x6fd378
    cpu.edi = 7328632 /*0x6fd378*/;
    // 004dcc99  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 004dcc9b  eb0f                   -jmp 0x4dccac
    goto L_0x004dccac;
L_0x004dcc9d:
    // 004dcc9d  b91c000000             -mov ecx, 0x1c
    cpu.ecx = 28 /*0x1c*/;
    // 004dcca2  be24d05500             -mov esi, 0x55d024
    cpu.esi = 5623844 /*0x55d024*/;
    // 004dcca7  bf78d36f00             -mov edi, 0x6fd378
    cpu.edi = 7328632 /*0x6fd378*/;
L_0x004dccac:
    // 004dccac  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004dccad  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004dccaf  c1e902                 -shr ecx, 2
    cpu.ecx >>= 2 /*0x2*/ % 32;
    // 004dccb2  f2a5                   -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004dccb4  8ac8                   -mov cl, al
    cpu.cl = cpu.al;
    // 004dccb6  80e103                 +and cl, 3
    cpu.clear_co();
    cpu.set_szp((cpu.cl &= x86::reg8(x86::sreg8(3 /*0x3*/))));
    // 004dccb9  f2a4                   -repne movsb byte ptr es:[edi], byte ptr [esi]
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
    // 004dccbb  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dccbc  eb44                   -jmp 0x4dcd02
    goto L_0x004dcd02;
L_0x004dccbe:
    // 004dccbe  b91c000000             -mov ecx, 0x1c
    cpu.ecx = 28 /*0x1c*/;
    // 004dccc3  be24d05500             -mov esi, 0x55d024
    cpu.esi = 5623844 /*0x55d024*/;
    // 004dccc8  bf78d36f00             -mov edi, 0x6fd378
    cpu.edi = 7328632 /*0x6fd378*/;
    // 004dcccd  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004dccce  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004dccd0  c1e902                 -shr ecx, 2
    cpu.ecx >>= 2 /*0x2*/ % 32;
    // 004dccd3  f2a5                   -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004dccd5  8ac8                   -mov cl, al
    cpu.cl = cpu.al;
    // 004dccd7  80e103                 +and cl, 3
    cpu.clear_co();
    cpu.set_szp((cpu.cl &= x86::reg8(x86::sreg8(3 /*0x3*/))));
    // 004dccda  f2a4                   -repne movsb byte ptr es:[edi], byte ptr [esi]
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
    // 004dccdc  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dccdd  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dccde  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dccdf  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dcce0  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dcce1  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dcce2  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004dcce3:
    // 004dcce3  b91c000000             -mov ecx, 0x1c
    cpu.ecx = 28 /*0x1c*/;
    // 004dcce8  be24d05500             -mov esi, 0x55d024
    cpu.esi = 5623844 /*0x55d024*/;
    // 004dcced  bf78d36f00             -mov edi, 0x6fd378
    cpu.edi = 7328632 /*0x6fd378*/;
    // 004dccf2  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004dccf3  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004dccf5  c1e902                 -shr ecx, 2
    cpu.ecx >>= 2 /*0x2*/ % 32;
    // 004dccf8  f2a5                   -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004dccfa  8ac8                   -mov cl, al
    cpu.cl = cpu.al;
    // 004dccfc  80e103                 +and cl, 3
    cpu.clear_co();
    cpu.set_szp((cpu.cl &= x86::reg8(x86::sreg8(3 /*0x3*/))));
    // 004dccff  f2a4                   -repne movsb byte ptr es:[edi], byte ptr [esi]
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
    // 004dcd01  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
L_0x004dcd02:
    // 004dcd02  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dcd03  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dcd04  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dcd05  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dcd06  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dcd07  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 */
void Application::sub_4dcd10(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004dcd10  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004dcd11  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004dcd13  e8d8000000             -call 0x4dcdf0
    cpu.esp -= 4;
    sub_4dcdf0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dcd18  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dcd19  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_4dcd20: native, nfs3hp::load::loadWeatherShapes */

/* align: skip 0x8d 0x40 0x00 0x8b 0xc9 */
void Application::sub_4dcdd0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004dcdd0  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004dcdd1  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004dcdd3  833dccd46f0000         +cmp dword ptr [0x6fd4cc], 0
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
    // 004dcdda  7407                   -je 0x4dcde3
    if (cpu.flags.zf)
    {
        goto L_0x004dcde3;
    }
    // 004dcddc  a12ca28c00             -mov eax, dword ptr [0x8ca22c]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(9216556) /* 0x8ca22c */);
    // 004dcde1  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dcde2  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004dcde3:
    // 004dcde3  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 004dcde5  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dcde6  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 */
void Application::sub_4dcdf0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004dcdf0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004dcdf1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004dcdf2  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004dcdf3  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004dcdf4  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004dcdf5  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004dcdf6  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004dcdf8  83ec0c                 -sub esp, 0xc
    (cpu.esp) -= x86::reg32(x86::sreg32(12 /*0xc*/));
    // 004dcdfb  ba5c000000             -mov edx, 0x5c
    cpu.edx = 92 /*0x5c*/;
    // 004dce00  b82ca28c00             -mov eax, 0x8ca22c
    cpu.eax = 9216556 /*0x8ca22c*/;
    // 004dce05  e802390000             -call 0x4e070c
    cpu.esp -= 4;
    nfs3hp::fillZero(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dce0a  ba004b0000             -mov edx, 0x4b00
    cpu.edx = 19200 /*0x4b00*/;
    // 004dce0f  b8e80b8c00             -mov eax, 0x8c0be8
    cpu.eax = 9178088 /*0x8c0be8*/;
    // 004dce14  e8f3380000             -call 0x4e070c
    cpu.esp -= 4;
    nfs3hp::fillZero(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dce19  ba20030000             -mov edx, 0x320
    cpu.edx = 800 /*0x320*/;
    // 004dce1e  b8c0088c00             -mov eax, 0x8c08c0
    cpu.eax = 9177280 /*0x8c08c0*/;
    // 004dce23  e8e4380000             -call 0x4e070c
    cpu.esp -= 4;
    nfs3hp::fillZero(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dce28  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 004dce2a  891588425600           -mov dword ptr [0x564288], edx
    app->getMemory<x86::reg32>(x86::reg32(5653128) /* 0x564288 */) = cpu.edx;
    // 004dce30  89158c425600           -mov dword ptr [0x56428c], edx
    app->getMemory<x86::reg32>(x86::reg32(5653132) /* 0x56428c */) = cpu.edx;
    // 004dce36  8a15e8a18c00           -mov dl, byte ptr [0x8ca1e8]
    cpu.dl = app->getMemory<x86::reg8>(x86::reg32(9216488) /* 0x8ca1e8 */);
    // 004dce3c  b903000000             -mov ecx, 3
    cpu.ecx = 3 /*0x3*/;
    // 004dce41  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004dce43  c1fa1f                 -sar edx, 0x1f
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (31 /*0x1f*/ % 32));
    // 004dce46  f7f9                   -idiv ecx
    {
        x86::sreg64 tmp = x86::sreg64(cpu.edx_eax);
        x86::sreg32 d = x86::sreg32(cpu.ecx);
        cpu.edx_eax = x86::reg64(tmp / d);
        cpu.edx = x86::reg32(tmp % d);
    }
    // 004dce48  89152ca28c00           -mov dword ptr [0x8ca22c], edx
    app->getMemory<x86::reg32>(x86::reg32(9216556) /* 0x8ca22c */) = cpu.edx;
    // 004dce4e  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 004dce50  0f848e030000           -je 0x4dd1e4
    if (cpu.flags.zf)
    {
        goto L_0x004dd1e4;
    }
    // 004dce56  bb64000000             -mov ebx, 0x64
    cpu.ebx = 100 /*0x64*/;
    // 004dce5b  66a1eaa18c00           -mov ax, word ptr [0x8ca1ea]
    cpu.ax = app->getMemory<x86::reg16>(x86::reg32(9216490) /* 0x8ca1ea */);
    // 004dce61  8d0c9500000000         -lea ecx, [edx*4]
    cpu.ecx = x86::reg32(cpu.edx * 4);
    // 004dce68  66a33ca28c00           -mov word ptr [0x8ca23c], ax
    app->getMemory<x86::reg16>(x86::reg32(9216572) /* 0x8ca23c */) = cpu.ax;
    // 004dce6e  29d1                   -sub ecx, edx
    (cpu.ecx) -= x86::reg32(x86::sreg32(cpu.edx));
    // 004dce70  66a1eca18c00           -mov ax, word ptr [0x8ca1ec]
    cpu.ax = app->getMemory<x86::reg16>(x86::reg32(9216492) /* 0x8ca1ec */);
    // 004dce76  c1e102                 -shl ecx, 2
    cpu.ecx <<= 2 /*0x2*/ % 32;
    // 004dce79  66a33ea28c00           -mov word ptr [0x8ca23e], ax
    app->getMemory<x86::reg16>(x86::reg32(9216574) /* 0x8ca23e */) = cpu.ax;
    // 004dce7f  01d1                   -add ecx, edx
    (cpu.ecx) += x86::reg32(x86::sreg32(cpu.edx));
    // 004dce81  66a1eea18c00           -mov ax, word ptr [0x8ca1ee]
    cpu.ax = app->getMemory<x86::reg16>(x86::reg32(9216494) /* 0x8ca1ee */);
    // 004dce87  c1e102                 -shl ecx, 2
    cpu.ecx <<= 2 /*0x2*/ % 32;
    // 004dce8a  66a340a28c00           -mov word ptr [0x8ca240], ax
    app->getMemory<x86::reg16>(x86::reg32(9216576) /* 0x8ca240 */) = cpu.ax;
    // 004dce90  8b9198425600           -mov edx, dword ptr [ecx + 0x564298]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(5653144) /* 0x564298 */);
    // 004dce96  a184367d00             -mov eax, dword ptr [0x7d3684]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(8205956) /* 0x7d3684 */);
    // 004dce9b  c1e210                 -shl edx, 0x10
    cpu.edx <<= 16 /*0x10*/ % 32;
    // 004dce9e  a348a28c00             -mov dword ptr [0x8ca248], eax
    app->getMemory<x86::reg32>(x86::reg32(9216584) /* 0x8ca248 */) = cpu.eax;
    // 004dcea3  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004dcea5  c1fa1f                 -sar edx, 0x1f
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (31 /*0x1f*/ % 32));
    // 004dcea8  f7fb                   -idiv ebx
    {
        x86::sreg64 tmp = x86::sreg64(cpu.edx_eax);
        x86::sreg32 d = x86::sreg32(cpu.ebx);
        cpu.edx_eax = x86::reg64(tmp / d);
        cpu.edx = x86::reg32(tmp % d);
    }
    // 004dceaa  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004dceac  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 004dceaf  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 004dceb1  c1e003                 -shl eax, 3
    cpu.eax <<= 3 /*0x3*/ % 32;
    // 004dceb4  01c2                   -add edx, eax
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.eax));
    // 004dceb6  c1e205                 -shl edx, 5
    cpu.edx <<= 5 /*0x5*/ % 32;
    // 004dceb9  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004dcebb  c1fa1f                 -sar edx, 0x1f
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (31 /*0x1f*/ % 32));
    // 004dcebe  c1e210                 +shl edx, 0x10
    {
        x86::reg8 tmp = 16 /*0x10*/ % 32;
        x86::reg32& op = cpu.edx;
        if (tmp)
        {
            cpu.flags.cf = 1 & (op >> (32 - tmp));
            cpu.set_szp((op <<= tmp));
            if (tmp == 1) cpu.flags.of = (cpu.flags.cf != (1 & (op >> (32 - 1))));
        }
    }
    // 004dcec1  1bc2                   -sbb eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx) + cpu.flags.cf);
    // 004dcec3  c1f810                 -sar eax, 0x10
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (16 /*0x10*/ % 32));
    // 004dcec6  8b9194425600           -mov edx, dword ptr [ecx + 0x564294]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(5653140) /* 0x564294 */);
    // 004dcecc  891530a28c00           -mov dword ptr [0x8ca230], edx
    app->getMemory<x86::reg32>(x86::reg32(9216560) /* 0x8ca230 */) = cpu.edx;
    // 004dced2  8bb19c425600           -mov esi, dword ptr [ecx + 0x56429c]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(5653148) /* 0x56429c */);
    // 004dced8  a334a28c00             -mov dword ptr [0x8ca234], eax
    app->getMemory<x86::reg32>(x86::reg32(9216564) /* 0x8ca234 */) = cpu.eax;
    // 004dcedd  83fe01                 +cmp esi, 1
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
    // 004dcee0  7e04                   -jle 0x4dcee6
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004dcee6;
    }
    // 004dcee2  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004dcee4  eb05                   -jmp 0x4dceeb
    goto L_0x004dceeb;
L_0x004dcee6:
    // 004dcee6  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
L_0x004dceeb:
    // 004dceeb  8b152ca28c00           -mov edx, dword ptr [0x8ca22c]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(9216556) /* 0x8ca22c */);
    // 004dcef1  8d0c9500000000         -lea ecx, [edx*4]
    cpu.ecx = x86::reg32(cpu.edx * 4);
    // 004dcef8  29d1                   -sub ecx, edx
    (cpu.ecx) -= x86::reg32(x86::sreg32(cpu.edx));
    // 004dcefa  c1e102                 -shl ecx, 2
    cpu.ecx <<= 2 /*0x2*/ % 32;
    // 004dcefd  bb68010000             -mov ebx, 0x168
    cpu.ebx = 360 /*0x168*/;
    // 004dcf02  01d1                   -add ecx, edx
    (cpu.ecx) += x86::reg32(x86::sreg32(cpu.edx));
    // 004dcf04  a34ca28c00             -mov dword ptr [0x8ca24c], eax
    app->getMemory<x86::reg32>(x86::reg32(9216588) /* 0x8ca24c */) = cpu.eax;
    // 004dcf09  c1e102                 -shl ecx, 2
    cpu.ecx <<= 2 /*0x2*/ % 32;
    // 004dcf0c  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 004dcf0f  8b81a0425600           -mov eax, dword ptr [ecx + 0x5642a0]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(5653152) /* 0x5642a0 */);
    // 004dcf15  8b91a8425600           -mov edx, dword ptr [ecx + 0x5642a8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(5653160) /* 0x5642a8 */);
    // 004dcf1b  a354a28c00             -mov dword ptr [0x8ca254], eax
    app->getMemory<x86::reg32>(x86::reg32(9216596) /* 0x8ca254 */) = cpu.eax;
    // 004dcf20  8b81a4425600           -mov eax, dword ptr [ecx + 0x5642a4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(5653156) /* 0x5642a4 */);
    // 004dcf26  c1e210                 -shl edx, 0x10
    cpu.edx <<= 16 /*0x10*/ % 32;
    // 004dcf29  a358a28c00             -mov dword ptr [0x8ca258], eax
    app->getMemory<x86::reg32>(x86::reg32(9216600) /* 0x8ca258 */) = cpu.eax;
    // 004dcf2e  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004dcf30  c1fa1f                 -sar edx, 0x1f
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (31 /*0x1f*/ % 32));
    // 004dcf33  f7fb                   -idiv ebx
    {
        x86::sreg64 tmp = x86::sreg64(cpu.edx_eax);
        x86::sreg32 d = x86::sreg32(cpu.ebx);
        cpu.edx_eax = x86::reg64(tmp / d);
        cpu.edx = x86::reg32(tmp % d);
    }
    // 004dcf35  db45fc                 -fild dword ptr [ebp - 4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 004dcf38  d9e8                   -fld1 
    x86::Float fpu2 = 1.0;
    // 004dcf3a  def1                   -fdivrp st(1)
    x86::Float fpu3 = cpu.fpu.div(fpu2, x86::Float(fpu1));
    // 004dcf3c  8b91ac425600           -mov edx, dword ptr [ecx + 0x5642ac]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(5653164) /* 0x5642ac */);
    // 004dcf42  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 004dcf45  c1e210                 -shl edx, 0x10
    cpu.edx <<= 16 /*0x10*/ % 32;
    // 004dcf48  b90a000000             -mov ecx, 0xa
    cpu.ecx = 10 /*0xa*/;
    // 004dcf4d  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004dcf4f  c1fa1f                 -sar edx, 0x1f
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (31 /*0x1f*/ % 32));
    // 004dcf52  f7f9                   -idiv ecx
    {
        x86::sreg64 tmp = x86::sreg64(cpu.edx_eax);
        x86::sreg32 d = x86::sreg32(cpu.ecx);
        cpu.edx_eax = x86::reg64(tmp / d);
        cpu.edx = x86::reg32(tmp % d);
    }
    // 004dcf54  db45fc                 -fild dword ptr [ebp - 4]
    x86::Float fpu4 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 004dcf57  dc0db4975400           -fmul qword ptr [0x5497b4]
    x86::Float fpu5 = cpu.fpu.mul(fpu4, x86::Float(app->getMemory<double>(x86::reg32(5543860) /* 0x5497b4 */)));
    // 004dcf5d  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 004dcf60  db45fc                 -fild dword ptr [ebp - 4]
    x86::Float fpu6 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 004dcf63  dc0db4975400           -fmul qword ptr [0x5497b4]
    x86::Float fpu7 = cpu.fpu.mul(fpu6, x86::Float(app->getMemory<double>(x86::reg32(5543860) /* 0x5497b4 */)));
    // 004dcf69  31ff                   -xor edi, edi
    cpu.edi ^= x86::reg32(x86::sreg32(cpu.edi));
    // 004dcf6b  d9ca                   -fxch st(2)
    
    // 004dcf6d  d91d50a28c00           -fstp dword ptr [0x8ca250]
    app->getMemory<float>(x86::reg32(9216592) /* 0x8ca250 */) = float(fpu3);
    // 004dcf73  bb74a28c00             -mov ebx, 0x8ca274
    cpu.ebx = 9216628 /*0x8ca274*/;
    // 004dcf78  d95df4                 -fstp dword ptr [ebp - 0xc]
    app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */) = float(fpu5);
    // 004dcf7b  ba6ca28c00             -mov edx, 0x8ca26c
    cpu.edx = 9216620 /*0x8ca26c*/;
    // 004dcf80  8d45f4                 -lea eax, [ebp - 0xc]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 004dcf83  d95df8                 -fstp dword ptr [ebp - 8]
    app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = float(fpu7);
    }
    // 004dcf86  e8e5d90000             -call 0x4ea970
    cpu.esp -= 4;
    sub_4ea970(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dcf8b  686ca28c00             -push 0x8ca26c
    app->getMemory<x86::reg32>(cpu.esp-4) = 9216620 /*0x8ca26c*/;
    cpu.esp -= 4;
    // 004dcf90  ba6ca28c00             -mov edx, 0x8ca26c
    cpu.edx = 9216620 /*0x8ca26c*/;
    // 004dcf95  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 004dcf9a  ff75f8                 -push dword ptr [ebp - 8]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    cpu.esp -= 4;
    // 004dcf9d  893d70a28c00           -mov dword ptr [0x8ca270], edi
    app->getMemory<x86::reg32>(x86::reg32(9216624) /* 0x8ca270 */) = cpu.edi;
    // 004dcfa3  e8a8300000             -call 0x4e0050
    cpu.esp -= 4;
    nfs3hp::vertices::scaleVectors(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dcfa8  8b152ca28c00           -mov edx, dword ptr [0x8ca22c]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(9216556) /* 0x8ca22c */);
    // 004dcfae  8d0c9500000000         -lea ecx, [edx*4]
    cpu.ecx = x86::reg32(cpu.edx * 4);
    // 004dcfb5  29d1                   -sub ecx, edx
    (cpu.ecx) -= x86::reg32(x86::sreg32(cpu.edx));
    // 004dcfb7  c1e102                 -shl ecx, 2
    cpu.ecx <<= 2 /*0x2*/ % 32;
    // 004dcfba  01d1                   -add ecx, edx
    (cpu.ecx) += x86::reg32(x86::sreg32(cpu.edx));
    // 004dcfbc  c1e102                 -shl ecx, 2
    cpu.ecx <<= 2 /*0x2*/ % 32;
    // 004dcfbf  8b8190425600           -mov eax, dword ptr [ecx + 0x564290]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(5653136) /* 0x564290 */);
    // 004dcfc5  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004dcfc7  bb0a000000             -mov ebx, 0xa
    cpu.ebx = 10 /*0xa*/;
    // 004dcfcc  c1fa1f                 -sar edx, 0x1f
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (31 /*0x1f*/ % 32));
    // 004dcfcf  f7fb                   -idiv ebx
    {
        x86::sreg64 tmp = x86::sreg64(cpu.edx_eax);
        x86::sreg32 d = x86::sreg32(cpu.ebx);
        cpu.edx_eax = x86::reg64(tmp / d);
        cpu.edx = x86::reg32(tmp % d);
    }
    // 004dcfd1  bb64000000             -mov ebx, 0x64
    cpu.ebx = 100 /*0x64*/;
    // 004dcfd6  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 004dcfd9  8b81b0425600           -mov eax, dword ptr [ecx + 0x5642b0]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(5653168) /* 0x5642b0 */);
    // 004dcfdf  8b91c0425600           -mov edx, dword ptr [ecx + 0x5642c0]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(5653184) /* 0x5642c0 */);
    // 004dcfe5  a338a28c00             -mov dword ptr [0x8ca238], eax
    app->getMemory<x86::reg32>(x86::reg32(9216568) /* 0x8ca238 */) = cpu.eax;
    // 004dcfea  a184367d00             -mov eax, dword ptr [0x7d3684]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(8205956) /* 0x7d3684 */);
    // 004dcfef  c1e210                 -shl edx, 0x10
    cpu.edx <<= 16 /*0x10*/ % 32;
    // 004dcff2  a3e00b8c00             -mov dword ptr [0x8c0be0], eax
    app->getMemory<x86::reg32>(x86::reg32(9178080) /* 0x8c0be0 */) = cpu.eax;
    // 004dcff7  a3e40b8c00             -mov dword ptr [0x8c0be4], eax
    app->getMemory<x86::reg32>(x86::reg32(9178084) /* 0x8c0be4 */) = cpu.eax;
    // 004dcffc  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004dcffe  c1fa1f                 -sar edx, 0x1f
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (31 /*0x1f*/ % 32));
    // 004dd001  f7fb                   -idiv ebx
    {
        x86::sreg64 tmp = x86::sreg64(cpu.edx_eax);
        x86::sreg32 d = x86::sreg32(cpu.ebx);
        cpu.edx_eax = x86::reg64(tmp / d);
        cpu.edx = x86::reg32(tmp % d);
    }
    // 004dd003  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004dd005  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 004dd008  01c2                   -add edx, eax
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.eax));
    // 004dd00a  c1e202                 -shl edx, 2
    cpu.edx <<= 2 /*0x2*/ % 32;
    // 004dd00d  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004dd00f  c1fa1f                 -sar edx, 0x1f
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (31 /*0x1f*/ % 32));
    // 004dd012  c1e210                 +shl edx, 0x10
    {
        x86::reg8 tmp = 16 /*0x10*/ % 32;
        x86::reg32& op = cpu.edx;
        if (tmp)
        {
            cpu.flags.cf = 1 & (op >> (32 - tmp));
            cpu.set_szp((op <<= tmp));
            if (tmp == 1) cpu.flags.of = (cpu.flags.cf != (1 & (op >> (32 - 1))));
        }
    }
    // 004dd015  1bc2                   -sbb eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx) + cpu.flags.cf);
    // 004dd017  c1f810                 -sar eax, 0x10
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (16 /*0x10*/ % 32));
    // 004dd01a  db45fc                 -fild dword ptr [ebp - 4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu8 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 004dd01d  dc0db4975400           -fmul qword ptr [0x5497b4]
    x86::Float fpu9 = cpu.fpu.mul(fpu8, x86::Float(app->getMemory<double>(x86::reg32(5543860) /* 0x5497b4 */)));
    // 004dd023  db054ca28c00           -fild dword ptr [0x8ca24c]
    x86::Float fpu10 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(9216588) /* 0x8ca24c */)));
    // 004dd029  db0554a28c00           -fild dword ptr [0x8ca254]
    x86::Float fpu11 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(9216596) /* 0x8ca254 */)));
    // 004dd02f  893d44a28c00           -mov dword ptr [0x8ca244], edi
    app->getMemory<x86::reg32>(x86::reg32(9216580) /* 0x8ca244 */) = cpu.edi;
    // 004dd035  d9c9                   -fxch st(1)
    
    // 004dd037  d91d5ca28c00           -fstp dword ptr [0x8ca25c]
    app->getMemory<float>(x86::reg32(9216604) /* 0x8ca25c */) = float(fpu10);
    // 004dd03d  d91d64a28c00           -fstp dword ptr [0x8ca264]
    app->getMemory<float>(x86::reg32(9216612) /* 0x8ca264 */) = float(fpu11);
    // 004dd043  a378a28c00             -mov dword ptr [0x8ca278], eax
    app->getMemory<x86::reg32>(x86::reg32(9216632) /* 0x8ca278 */) = cpu.eax;
    // 004dd048  8b81b4425600           -mov eax, dword ptr [ecx + 0x5642b4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(5653172) /* 0x5642b4 */);
    // 004dd04e  d90564a28c00           -fld dword ptr [0x8ca264]
    x86::Float fpu12 = x86::Float(app->getMemory<float>(x86::reg32(9216612) /* 0x8ca264 */));
    // 004dd054  a37ca28c00             -mov dword ptr [0x8ca27c], eax
    app->getMemory<x86::reg32>(x86::reg32(9216636) /* 0x8ca27c */) = cpu.eax;
    // 004dd059  8b81bc425600           -mov eax, dword ptr [ecx + 0x5642bc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(5653180) /* 0x5642bc */);
    // 004dd05f  d981b8425600           -fld dword ptr [ecx + 0x5642b8]
    x86::Float fpu13 = x86::Float(app->getMemory<float>(cpu.ecx + x86::reg32(5653176) /* 0x5642b8 */));
    // 004dd065  a384a28c00             -mov dword ptr [0x8ca284], eax
    app->getMemory<x86::reg32>(x86::reg32(9216644) /* 0x8ca284 */) = cpu.eax;
    // 004dd06a  a158a28c00             -mov eax, dword ptr [0x8ca258]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(9216600) /* 0x8ca258 */);
    // 004dd06f  d91d80a28c00           -fstp dword ptr [0x8ca280]
    app->getMemory<float>(x86::reg32(9216640) /* 0x8ca280 */) = float(fpu13);
    // 004dd075  f7d8                   -neg eax
    cpu.eax = ~cpu.eax + 1;
    // 004dd077  d9c9                   -fxch st(1)
    
    // 004dd079  d9e0                   -fchs 
    x86::Float fpu14 = -fpu9;
    // 004dd07b  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 004dd07e  d91d70a28c00           -fstp dword ptr [0x8ca270]
    app->getMemory<float>(x86::reg32(9216624) /* 0x8ca270 */) = float(fpu14);
    // 004dd084  db45fc                 -fild dword ptr [ebp - 4]
    x86::Float fpu15 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 004dd087  d91d60a28c00           -fstp dword ptr [0x8ca260]
    app->getMemory<float>(x86::reg32(9216608) /* 0x8ca260 */) = float(fpu15);
    // 004dd08d  d82560a28c00           -fsub dword ptr [0x8ca260]
    x86::Float fpu16 = cpu.fpu.sub(fpu12, x86::Float(app->getMemory<float>(x86::reg32(9216608) /* 0x8ca260 */)));
    // 004dd093  8b152ca28c00           -mov edx, dword ptr [0x8ca22c]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(9216556) /* 0x8ca22c */);
    // 004dd099  d91d68a28c00           -fstp dword ptr [0x8ca268]
    app->getMemory<float>(x86::reg32(9216616) /* 0x8ca268 */) = float(fpu16);
    // 004dd09f  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    }
    // 004dd0a1  0f843d010000           -je 0x4dd1e4
    if (cpu.flags.zf)
    {
        goto L_0x004dd1e4;
    }
    // 004dd0a7  e82463fcff             -call 0x4a33d0
    cpu.esp -= 4;
    sub_4a33d0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dd0ac  31c9                   +xor ecx, ecx
    cpu.clear_co();
    cpu.set_szp((cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx))));
    // 004dd0ae  eb0c                   -jmp 0x4dd0bc
    goto L_0x004dd0bc;
L_0x004dd0b0:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004dd0b0  81f920030000           +cmp ecx, 0x320
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(800 /*0x320*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004dd0b6  0f8dfa000000           -jge 0x4dd1b6
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004dd1b6;
    }
L_0x004dd0bc:
    // 004dd0bc  e86fe10000             -call 0x4eb230
    cpu.esp -= 4;
    nfs3hp::ea::randomFraction(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dd0c1  d80d5ca28c00           -fmul dword ptr [0x8ca25c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu17 = cpu.fpu.st(0);
    x86::Float fpu18 = cpu.fpu.mul(fpu17, x86::Float(app->getMemory<float>(x86::reg32(9216604) /* 0x8ca25c */)));
    // 004dd0c7  d80dbc975400           -fmul dword ptr [0x5497bc]
    x86::Float fpu19 = cpu.fpu.mul(fpu18, x86::Float(app->getMemory<float>(x86::reg32(5543868) /* 0x5497bc */)));
    // 004dd0cd  8d148d00000000         -lea edx, [ecx*4]
    cpu.edx = x86::reg32(cpu.ecx * 4);
    // 004dd0d4  d8255ca28c00           -fsub dword ptr [0x8ca25c]
    x86::Float fpu20 = cpu.fpu.sub(fpu19, x86::Float(app->getMemory<float>(x86::reg32(9216604) /* 0x8ca25c */)));
    // 004dd0da  29ca                   -sub edx, ecx
    (cpu.edx) -= x86::reg32(x86::sreg32(cpu.ecx));
    // 004dd0dc  d91c95e8568c00         -fstp dword ptr [edx*4 + 0x8c56e8]
    app->getMemory<float>(x86::reg32(9197288) /* 0x8c56e8 */ + cpu.edx * 4) = float(fpu20);
    cpu.fpu.count -= 1;
    }
    // 004dd0e3  e848e10000             -call 0x4eb230
    cpu.esp -= 4;
    nfs3hp::ea::randomFraction(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dd0e8  d80d68a28c00           -fmul dword ptr [0x8ca268]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu21 = cpu.fpu.st(0);
    x86::Float fpu22 = cpu.fpu.mul(fpu21, x86::Float(app->getMemory<float>(x86::reg32(9216616) /* 0x8ca268 */)));
    // 004dd0ee  d80560a28c00           -fadd dword ptr [0x8ca260]
    x86::Float fpu23 = cpu.fpu.add(fpu22, x86::Float(app->getMemory<float>(x86::reg32(9216608) /* 0x8ca260 */)));
    // 004dd0f4  d91c95ec568c00         -fstp dword ptr [edx*4 + 0x8c56ec]
    app->getMemory<float>(x86::reg32(9197292) /* 0x8c56ec */ + cpu.edx * 4) = float(fpu23);
    cpu.fpu.count -= 1;
    }
    // 004dd0fb  e830e10000             -call 0x4eb230
    cpu.esp -= 4;
    nfs3hp::ea::randomFraction(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dd100  d80d5ca28c00           -fmul dword ptr [0x8ca25c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu24 = cpu.fpu.st(0);
    x86::Float fpu25 = cpu.fpu.mul(fpu24, x86::Float(app->getMemory<float>(x86::reg32(9216604) /* 0x8ca25c */)));
    // 004dd106  d80dbc975400           -fmul dword ptr [0x5497bc]
    x86::Float fpu26 = cpu.fpu.mul(fpu25, x86::Float(app->getMemory<float>(x86::reg32(5543868) /* 0x5497bc */)));
    // 004dd10c  d8255ca28c00           -fsub dword ptr [0x8ca25c]
    x86::Float fpu27 = cpu.fpu.sub(fpu26, x86::Float(app->getMemory<float>(x86::reg32(9216604) /* 0x8ca25c */)));
    // 004dd112  d91c95f0568c00         -fstp dword ptr [edx*4 + 0x8c56f0]
    app->getMemory<float>(x86::reg32(9197296) /* 0x8c56f0 */ + cpu.edx * 4) = float(fpu27);
    cpu.fpu.count -= 1;
    }
    // 004dd119  e812e10000             -call 0x4eb230
    cpu.esp -= 4;
    nfs3hp::ea::randomFraction(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dd11e  d80d5ca28c00           -fmul dword ptr [0x8ca25c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu28 = cpu.fpu.st(0);
    x86::Float fpu29 = cpu.fpu.mul(fpu28, x86::Float(app->getMemory<float>(x86::reg32(9216604) /* 0x8ca25c */)));
    // 004dd124  d80dbc975400           -fmul dword ptr [0x5497bc]
    x86::Float fpu30 = cpu.fpu.mul(fpu29, x86::Float(app->getMemory<float>(x86::reg32(5543868) /* 0x5497bc */)));
    // 004dd12a  d8255ca28c00           -fsub dword ptr [0x8ca25c]
    x86::Float fpu31 = cpu.fpu.sub(fpu30, x86::Float(app->getMemory<float>(x86::reg32(9216604) /* 0x8ca25c */)));
    // 004dd130  d91c95687c8c00         -fstp dword ptr [edx*4 + 0x8c7c68]
    app->getMemory<float>(x86::reg32(9206888) /* 0x8c7c68 */ + cpu.edx * 4) = float(fpu31);
    cpu.fpu.count -= 1;
    }
    // 004dd137  e8f4e00000             -call 0x4eb230
    cpu.esp -= 4;
    nfs3hp::ea::randomFraction(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dd13c  d80d68a28c00           -fmul dword ptr [0x8ca268]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu32 = cpu.fpu.st(0);
    x86::Float fpu33 = cpu.fpu.mul(fpu32, x86::Float(app->getMemory<float>(x86::reg32(9216616) /* 0x8ca268 */)));
    // 004dd142  d80560a28c00           -fadd dword ptr [0x8ca260]
    x86::Float fpu34 = cpu.fpu.add(fpu33, x86::Float(app->getMemory<float>(x86::reg32(9216608) /* 0x8ca260 */)));
    // 004dd148  bb000080bf             -mov ebx, 0xbf800000
    cpu.ebx = 3212836864 /*0xbf800000*/;
    // 004dd14d  d91c956c7c8c00         -fstp dword ptr [edx*4 + 0x8c7c6c]
    app->getMemory<float>(x86::reg32(9206892) /* 0x8c7c6c */ + cpu.edx * 4) = float(fpu34);
    cpu.fpu.count -= 1;
    }
    // 004dd154  e8d7e00000             -call 0x4eb230
    cpu.esp -= 4;
    nfs3hp::ea::randomFraction(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dd159  891c95e80b8c00         -mov dword ptr [edx*4 + 0x8c0be8], ebx
    app->getMemory<x86::reg32>(x86::reg32(9178088) /* 0x8c0be8 */ + cpu.edx * 4) = cpu.ebx;
    // 004dd160  d80d5ca28c00           -fmul dword ptr [0x8ca25c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu35 = cpu.fpu.st(0);
    x86::Float fpu36 = cpu.fpu.mul(fpu35, x86::Float(app->getMemory<float>(x86::reg32(9216604) /* 0x8ca25c */)));
    // 004dd166  891c95ec0b8c00         -mov dword ptr [edx*4 + 0x8c0bec], ebx
    app->getMemory<x86::reg32>(x86::reg32(9178092) /* 0x8c0bec */ + cpu.edx * 4) = cpu.ebx;
    // 004dd16d  d80dbc975400           -fmul dword ptr [0x5497bc]
    x86::Float fpu37 = cpu.fpu.mul(fpu36, x86::Float(app->getMemory<float>(x86::reg32(5543868) /* 0x5497bc */)));
    // 004dd173  891c9568318c00         -mov dword ptr [edx*4 + 0x8c3168], ebx
    app->getMemory<x86::reg32>(x86::reg32(9187688) /* 0x8c3168 */ + cpu.edx * 4) = cpu.ebx;
    // 004dd17a  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 004dd17c  891c956c318c00         -mov dword ptr [edx*4 + 0x8c316c], ebx
    app->getMemory<x86::reg32>(x86::reg32(9187692) /* 0x8c316c */ + cpu.edx * 4) = cpu.ebx;
    // 004dd183  30fc                   -xor ah, bh
    cpu.ah ^= x86::reg8(x86::sreg8(cpu.bh));
    // 004dd185  30db                   +xor bl, bl
    cpu.clear_co();
    cpu.set_szp((cpu.bl ^= x86::reg8(x86::sreg8(cpu.bl))));
    // 004dd187  882495f10b8c00         -mov byte ptr [edx*4 + 0x8c0bf1], ah
    app->getMemory<x86::reg8>(x86::reg32(9178097) /* 0x8c0bf1 */ + cpu.edx * 4) = cpu.ah;
    // 004dd18e  881c9571318c00         -mov byte ptr [edx*4 + 0x8c3171], bl
    app->getMemory<x86::reg8>(x86::reg32(9187697) /* 0x8c3171 */ + cpu.edx * 4) = cpu.bl;
    // 004dd195  41                     +inc ecx
    {
        x86::reg32& tmp = cpu.ecx;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 004dd196  881c95f00b8c00         -mov byte ptr [edx*4 + 0x8c0bf0], bl
    app->getMemory<x86::reg8>(x86::reg32(9178096) /* 0x8c0bf0 */ + cpu.edx * 4) = cpu.bl;
    // 004dd19d  d8255ca28c00           +fsub dword ptr [0x8ca25c]
    x86::Float fpu38 = cpu.fpu.sub(fpu37, x86::Float(app->getMemory<float>(x86::reg32(9216604) /* 0x8ca25c */)));
    // 004dd1a3  881c9570318c00         -mov byte ptr [edx*4 + 0x8c3170], bl
    app->getMemory<x86::reg8>(x86::reg32(9187696) /* 0x8c3170 */ + cpu.edx * 4) = cpu.bl;
    // 004dd1aa  d91c95707c8c00         +fstp dword ptr [edx*4 + 0x8c7c70]
    app->getMemory<float>(x86::reg32(9206896) /* 0x8c7c70 */ + cpu.edx * 4) = float(fpu38);
    cpu.fpu.count -= 1;
    }
    // 004dd1b1  e9fafeffff             -jmp 0x4dd0b0
    goto L_0x004dd0b0;
L_0x004dd1b6:
    // 004dd1b6  e81562fcff             -call 0x4a33d0
    cpu.esp -= 4;
    sub_4a33d0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dd1bb  31d2                   +xor edx, edx
    cpu.clear_co();
    cpu.set_szp((cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx))));
    // 004dd1bd  eb05                   -jmp 0x4dd1c4
    goto L_0x004dd1c4;
L_0x004dd1bf:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004dd1bf  83fa14                 +cmp edx, 0x14
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(20 /*0x14*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004dd1c2  7d20                   -jge 0x4dd1e4
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004dd1e4;
    }
L_0x004dd1c4:
    // 004dd1c4  89d1                   -mov ecx, edx
    cpu.ecx = cpu.edx;
    // 004dd1c6  8d049500000000         -lea eax, [edx*4]
    cpu.eax = x86::reg32(cpu.edx * 4);
    // 004dd1cd  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 004dd1cf  31d1                   -xor ecx, edx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 004dd1d1  31db                   +xor ebx, ebx
    cpu.clear_co();
    cpu.set_szp((cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx))));
    // 004dd1d3  890c85c8088c00         -mov dword ptr [eax*4 + 0x8c08c8], ecx
    app->getMemory<x86::reg32>(x86::reg32(9177288) /* 0x8c08c8 */ + cpu.eax * 4) = cpu.ecx;
    // 004dd1da  42                     +inc edx
    {
        x86::reg32& tmp = cpu.edx;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 004dd1db  891c85580a8c00         -mov dword ptr [eax*4 + 0x8c0a58], ebx
    app->getMemory<x86::reg32>(x86::reg32(9177688) /* 0x8c0a58 */ + cpu.eax * 4) = cpu.ebx;
    // 004dd1e2  ebdb                   -jmp 0x4dd1bf
    goto L_0x004dd1bf;
L_0x004dd1e4:
    // 004dd1e4  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004dd1e6  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dd1e7  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dd1e8  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dd1e9  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dd1ea  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dd1eb  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dd1ec  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x40 0x00 */
void Application::sub_4dd1f0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004dd1f0  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004dd1f1  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004dd1f2  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004dd1f4  f60584367d0001         +test byte ptr [0x7d3684], 1
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(x86::reg32(8205956) /* 0x7d3684 */) & 1 /*0x1*/));
    // 004dd1fb  742e                   -je 0x4dd22b
    if (cpu.flags.zf)
    {
        goto L_0x004dd22b;
    }
    // 004dd1fd  a184367d00             -mov eax, dword ptr [0x7d3684]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(8205956) /* 0x7d3684 */);
    // 004dd202  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 004dd205  e876510100             -call 0x4f2380
    cpu.esp -= 4;
    nfs3hp::load::fixedSine(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dd20a  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004dd20c  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 004dd20f  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 004dd211  c1e003                 -shl eax, 3
    cpu.eax <<= 3 /*0x3*/ % 32;
    // 004dd214  01c2                   -add edx, eax
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.eax));
    // 004dd216  c1e203                 -shl edx, 3
    cpu.edx <<= 3 /*0x3*/ % 32;
    // 004dd219  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004dd21b  c1fa1f                 -sar edx, 0x1f
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (31 /*0x1f*/ % 32));
    // 004dd21e  c1e210                 +shl edx, 0x10
    {
        x86::reg8 tmp = 16 /*0x10*/ % 32;
        x86::reg32& op = cpu.edx;
        if (tmp)
        {
            cpu.flags.cf = 1 & (op >> (32 - tmp));
            cpu.set_szp((op <<= tmp));
            if (tmp == 1) cpu.flags.of = (cpu.flags.cf != (1 & (op >> (32 - 1))));
        }
    }
    // 004dd221  1bc2                   -sbb eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx) + cpu.flags.cf);
    // 004dd223  c1f810                 -sar eax, 0x10
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (16 /*0x10*/ % 32));
    // 004dd226  a344a28c00             -mov dword ptr [0x8ca244], eax
    app->getMemory<x86::reg32>(x86::reg32(9216580) /* 0x8ca244 */) = cpu.eax;
L_0x004dd22b:
    // 004dd22b  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dd22c  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dd22d  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8b 0xc0 */
void Application::sub_4dd230(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004dd230  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004dd231  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004dd232  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004dd233  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004dd234  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004dd235  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004dd236  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004dd238  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004dd23a  8b0d2ca28c00           -mov ecx, dword ptr [0x8ca22c]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(9216556) /* 0x8ca22c */);
    // 004dd240  8b7004                 -mov esi, dword ptr [eax + 4]
    cpu.esi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 004dd243  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    // 004dd245  0f84d7000000           -je 0x4dd322
    if (cpu.flags.zf)
    {
        goto L_0x004dd322;
    }
    // 004dd24b  e8103bf4ff             -call 0x420d60
    cpu.esp -= 4;
    nfs3hp::trackdata::carFacingWay(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dd250  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004dd252  0f8598000000           -jne 0x4dd2f0
    if (!cpu.flags.zf)
    {
        goto L_0x004dd2f0;
    }
    // 004dd258  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
L_0x004dd25a:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004dd25a  3b1d34a28c00           +cmp ebx, dword ptr [0x8ca234]
    {
        x86::reg32 tmp1 = cpu.ebx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(9216564) /* 0x8ca234 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004dd260  0f8d8a000000           -jge 0x4dd2f0
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004dd2f0;
    }
    // 004dd266  8d04b500000000         -lea eax, [esi*4]
    cpu.eax = x86::reg32(cpu.esi * 4);
    // 004dd26d  01f0                   -add eax, esi
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.esi));
    // 004dd26f  c1e007                 -shl eax, 7
    cpu.eax <<= 7 /*0x7*/ % 32;
    // 004dd272  89c7                   -mov edi, eax
    cpu.edi = cpu.eax;
    // 004dd274  c1e704                 -shl edi, 4
    cpu.edi <<= 4 /*0x4*/ % 32;
    // 004dd277  29c7                   -sub edi, eax
    (cpu.edi) -= x86::reg32(x86::sreg32(cpu.eax));
    // 004dd279  8d049d00000000         -lea eax, [ebx*4]
    cpu.eax = x86::reg32(cpu.ebx * 4);
    // 004dd280  29d8                   -sub eax, ebx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.ebx));
    // 004dd282  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 004dd285  8d0c07                 -lea ecx, [edi + eax]
    cpu.ecx = x86::reg32(cpu.edi + cpu.eax * 1);
    // 004dd288  30e4                   +xor ah, ah
    cpu.clear_co();
    cpu.set_szp((cpu.ah ^= x86::reg8(x86::sreg8(cpu.ah))));
    // 004dd28a  88a1f10b8c00           -mov byte ptr [ecx + 0x8c0bf1], ah
    app->getMemory<x86::reg8>(cpu.ecx + x86::reg32(9178097) /* 0x8c0bf1 */) = cpu.ah;
    // 004dd290  e89bdf0000             -call 0x4eb230
    cpu.esp -= 4;
    nfs3hp::ea::randomFraction(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dd295  d80d5ca28c00           +fmul dword ptr [0x8ca25c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = cpu.fpu.st(0);
    x86::Float fpu2 = cpu.fpu.mul(fpu1, x86::Float(app->getMemory<float>(x86::reg32(9216604) /* 0x8ca25c */)));
    // 004dd29b  d80dc0975400           +fmul dword ptr [0x5497c0]
    x86::Float fpu3 = cpu.fpu.mul(fpu2, x86::Float(app->getMemory<float>(x86::reg32(5543872) /* 0x5497c0 */)));
    // 004dd2a1  d8255ca28c00           +fsub dword ptr [0x8ca25c]
    x86::Float fpu4 = cpu.fpu.sub(fpu3, x86::Float(app->getMemory<float>(x86::reg32(9216604) /* 0x8ca25c */)));
    // 004dd2a7  d84208                 +fadd dword ptr [edx + 8]
    x86::Float fpu5 = cpu.fpu.add(fpu4, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(8) /* 0x8 */)));
    // 004dd2aa  d999e8568c00           +fstp dword ptr [ecx + 0x8c56e8]
    app->getMemory<float>(cpu.ecx + x86::reg32(9197288) /* 0x8c56e8 */) = float(fpu5);
    cpu.fpu.count -= 1;
    }
    // 004dd2b0  e87bdf0000             -call 0x4eb230
    cpu.esp -= 4;
    nfs3hp::ea::randomFraction(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dd2b5  d80d68a28c00           +fmul dword ptr [0x8ca268]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu6 = cpu.fpu.st(0);
    x86::Float fpu7 = cpu.fpu.mul(fpu6, x86::Float(app->getMemory<float>(x86::reg32(9216616) /* 0x8ca268 */)));
    // 004dd2bb  d80560a28c00           +fadd dword ptr [0x8ca260]
    x86::Float fpu8 = cpu.fpu.add(fpu7, x86::Float(app->getMemory<float>(x86::reg32(9216608) /* 0x8ca260 */)));
    // 004dd2c1  d8420c                 +fadd dword ptr [edx + 0xc]
    x86::Float fpu9 = cpu.fpu.add(fpu8, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(12) /* 0xc */)));
    // 004dd2c4  d999ec568c00           +fstp dword ptr [ecx + 0x8c56ec]
    app->getMemory<float>(cpu.ecx + x86::reg32(9197292) /* 0x8c56ec */) = float(fpu9);
    cpu.fpu.count -= 1;
    }
    // 004dd2ca  e861df0000             -call 0x4eb230
    cpu.esp -= 4;
    nfs3hp::ea::randomFraction(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dd2cf  d80d5ca28c00           +fmul dword ptr [0x8ca25c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu10 = cpu.fpu.st(0);
    x86::Float fpu11 = cpu.fpu.mul(fpu10, x86::Float(app->getMemory<float>(x86::reg32(9216604) /* 0x8ca25c */)));
    // 004dd2d5  d80dc0975400           +fmul dword ptr [0x5497c0]
    x86::Float fpu12 = cpu.fpu.mul(fpu11, x86::Float(app->getMemory<float>(x86::reg32(5543872) /* 0x5497c0 */)));
    // 004dd2db  d8255ca28c00           +fsub dword ptr [0x8ca25c]
    x86::Float fpu13 = cpu.fpu.sub(fpu12, x86::Float(app->getMemory<float>(x86::reg32(9216604) /* 0x8ca25c */)));
    // 004dd2e1  d84210                 +fadd dword ptr [edx + 0x10]
    x86::Float fpu14 = cpu.fpu.add(fpu13, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(16) /* 0x10 */)));
    // 004dd2e4  43                     +inc ebx
    {
        x86::reg32& tmp = cpu.ebx;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 004dd2e5  d999f0568c00           +fstp dword ptr [ecx + 0x8c56f0]
    app->getMemory<float>(cpu.ecx + x86::reg32(9197296) /* 0x8c56f0 */) = float(fpu14);
    cpu.fpu.count -= 1;
    }
    // 004dd2eb  e96affffff             -jmp 0x4dd25a
    goto L_0x004dd25a;
L_0x004dd2f0:
    // 004dd2f0  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
L_0x004dd2f2:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004dd2f2  3b1578a28c00           +cmp edx, dword ptr [0x8ca278]
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(9216632) /* 0x8ca278 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004dd2f8  7d28                   -jge 0x4dd322
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004dd322;
    }
    // 004dd2fa  8d1cb500000000         -lea ebx, [esi*4]
    cpu.ebx = x86::reg32(cpu.esi * 4);
    // 004dd301  89d1                   -mov ecx, edx
    cpu.ecx = cpu.edx;
    // 004dd303  29f3                   -sub ebx, esi
    (cpu.ebx) -= x86::reg32(x86::sreg32(cpu.esi));
    // 004dd305  8d049500000000         -lea eax, [edx*4]
    cpu.eax = x86::reg32(cpu.edx * 4);
    // 004dd30c  c1e303                 -shl ebx, 3
    cpu.ebx <<= 3 /*0x3*/ % 32;
    // 004dd30f  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 004dd311  01f3                   -add ebx, esi
    (cpu.ebx) += x86::reg32(x86::sreg32(cpu.esi));
    // 004dd313  31d1                   -xor ecx, edx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 004dd315  c1e304                 +shl ebx, 4
    {
        x86::reg8 tmp = 4 /*0x4*/ % 32;
        x86::reg32& op = cpu.ebx;
        if (tmp)
        {
            cpu.flags.cf = 1 & (op >> (32 - tmp));
            cpu.set_szp((op <<= tmp));
            if (tmp == 1) cpu.flags.of = (cpu.flags.cf != (1 & (op >> (32 - 1))));
        }
    }
    // 004dd318  42                     +inc edx
    {
        x86::reg32& tmp = cpu.edx;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 004dd319  898c83c8088c00         -mov dword ptr [ebx + eax*4 + 0x8c08c8], ecx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(9177288) /* 0x8c08c8 */ + cpu.eax * 4) = cpu.ecx;
    // 004dd320  ebd0                   -jmp 0x4dd2f2
    goto L_0x004dd2f2;
L_0x004dd322:
    // 004dd322  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dd323  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dd324  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dd325  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dd326  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dd327  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dd328  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x90 */
void Application::sub_4dd330(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004dd330  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004dd331  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004dd332  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004dd333  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004dd334  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004dd335  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004dd336  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004dd338  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 004dd33b  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 004dd33d  a1f0a18c00             -mov eax, dword ptr [0x8ca1f0]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(9216496) /* 0x8ca1f0 */);
    // 004dd342  8b1df4a18c00           -mov ebx, dword ptr [0x8ca1f4]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(9216500) /* 0x8ca1f4 */);
    // 004dd348  8b1548a28c00           -mov edx, dword ptr [0x8ca248]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(9216584) /* 0x8ca248 */);
    // 004dd34e  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 004dd351  a184367d00             -mov eax, dword ptr [0x7d3684]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(8205956) /* 0x7d3684 */);
    // 004dd356  8b3df8a18c00           -mov edi, dword ptr [0x8ca1f8]
    cpu.edi = app->getMemory<x86::reg32>(x86::reg32(9216504) /* 0x8ca1f8 */);
    // 004dd35c  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 004dd35e  8b55fc                 -mov edx, dword ptr [ebp - 4]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004dd361  8b35fca18c00           -mov esi, dword ptr [0x8ca1fc]
    cpu.esi = app->getMemory<x86::reg32>(x86::reg32(9216508) /* 0x8ca1fc */);
    // 004dd367  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 004dd369  0f8453000000           -je 0x4dd3c2
    if (cpu.flags.zf)
    {
        goto L_0x004dd3c2;
    }
    // 004dd36f  85db                   +test ebx, ebx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & cpu.ebx));
    // 004dd371  744f                   -je 0x4dd3c2
    if (cpu.flags.zf)
    {
        goto L_0x004dd3c2;
    }
    // 004dd373  85ff                   +test edi, edi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edi & cpu.edi));
    // 004dd375  744b                   -je 0x4dd3c2
    if (cpu.flags.zf)
    {
        goto L_0x004dd3c2;
    }
    // 004dd377  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 004dd379  7447                   -je 0x4dd3c2
    if (cpu.flags.zf)
    {
        goto L_0x004dd3c2;
    }
    // 004dd37b  39d0                   +cmp eax, edx
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
    // 004dd37d  7c43                   -jl 0x4dd3c2
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004dd3c2;
    }
    // 004dd37f  39d8                   +cmp eax, ebx
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ebx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004dd381  7d15                   -jge 0x4dd398
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004dd398;
    }
    // 004dd383  89da                   -mov edx, ebx
    cpu.edx = cpu.ebx;
    // 004dd385  29c2                   -sub edx, eax
    (cpu.edx) -= x86::reg32(x86::sreg32(cpu.eax));
    // 004dd387  0fafd1                 -imul edx, ecx
    cpu.edx = x86::reg32(x86::sreg64(x86::sreg32(cpu.edx)) * x86::sreg64(x86::sreg32(cpu.ecx)));
    // 004dd38a  8b4dfc                 -mov ecx, dword ptr [ebp - 4]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004dd38d  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004dd38f  c1fa1f                 -sar edx, 0x1f
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (31 /*0x1f*/ % 32));
    // 004dd392  29cb                   -sub ebx, ecx
    (cpu.ebx) -= x86::reg32(x86::sreg32(cpu.ecx));
    // 004dd394  f7fb                   +idiv ebx
    {
        x86::sreg64 tmp = x86::sreg64(cpu.edx_eax);
        x86::sreg32 d = x86::sreg32(cpu.ebx);
        cpu.edx_eax = x86::reg64(tmp / d);
        cpu.edx = x86::reg32(tmp % d);
    }
    // 004dd396  eb2c                   -jmp 0x4dd3c4
    goto L_0x004dd3c4;
L_0x004dd398:
    // 004dd398  39f8                   +cmp eax, edi
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
    // 004dd39a  7d04                   -jge 0x4dd3a0
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004dd3a0;
    }
    // 004dd39c  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
    // 004dd39e  eb24                   -jmp 0x4dd3c4
    goto L_0x004dd3c4;
L_0x004dd3a0:
    // 004dd3a0  39f0                   +cmp eax, esi
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
    // 004dd3a2  7d14                   -jge 0x4dd3b8
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004dd3b8;
    }
    // 004dd3a4  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 004dd3a6  29c2                   -sub edx, eax
    (cpu.edx) -= x86::reg32(x86::sreg32(cpu.eax));
    // 004dd3a8  0fafd1                 -imul edx, ecx
    cpu.edx = x86::reg32(x86::sreg64(x86::sreg32(cpu.edx)) * x86::sreg64(x86::sreg32(cpu.ecx)));
    // 004dd3ab  29fe                   -sub esi, edi
    (cpu.esi) -= x86::reg32(x86::sreg32(cpu.edi));
    // 004dd3ad  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004dd3af  c1fa1f                 -sar edx, 0x1f
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (31 /*0x1f*/ % 32));
    // 004dd3b2  f7fe                   -idiv esi
    {
        x86::sreg64 tmp = x86::sreg64(cpu.edx_eax);
        x86::sreg32 d = x86::sreg32(cpu.esi);
        cpu.edx_eax = x86::reg64(tmp / d);
        cpu.edx = x86::reg32(tmp % d);
    }
    // 004dd3b4  29c1                   +sub ecx, eax
    {
        x86::reg32& tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.eax));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 004dd3b6  eb0a                   -jmp 0x4dd3c2
    goto L_0x004dd3c2;
L_0x004dd3b8:
    // 004dd3b8  a184367d00             -mov eax, dword ptr [0x7d3684]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(8205956) /* 0x7d3684 */);
    // 004dd3bd  a348a28c00             -mov dword ptr [0x8ca248], eax
    app->getMemory<x86::reg32>(x86::reg32(9216584) /* 0x8ca248 */) = cpu.eax;
L_0x004dd3c2:
    // 004dd3c2  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
L_0x004dd3c4:
    // 004dd3c4  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004dd3c6  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dd3c7  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dd3c8  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dd3c9  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dd3ca  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dd3cb  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dd3cc  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x40 0x00 */
void Application::sub_4dd3d0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004dd3d0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004dd3d1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004dd3d2  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004dd3d3  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004dd3d4  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004dd3d5  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004dd3d6  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004dd3d8  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 004dd3db  8b353aa28c00           -mov esi, dword ptr [0x8ca23a]
    cpu.esi = app->getMemory<x86::reg32>(x86::reg32(9216570) /* 0x8ca23a */);
    // 004dd3e1  8b1544a28c00           -mov edx, dword ptr [0x8ca244]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(9216580) /* 0x8ca244 */);
    // 004dd3e7  c1fe10                 -sar esi, 0x10
    cpu.esi = x86::reg32(x86::sreg32(cpu.esi) >> (16 /*0x10*/ % 32));
    // 004dd3ea  01d6                   -add esi, edx
    (cpu.esi) += x86::reg32(x86::sreg32(cpu.edx));
    // 004dd3ec  8b153ca28c00           -mov edx, dword ptr [0x8ca23c]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(9216572) /* 0x8ca23c */);
    // 004dd3f2  8b0d44a28c00           -mov ecx, dword ptr [0x8ca244]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(9216580) /* 0x8ca244 */);
    // 004dd3f8  c1fa10                 -sar edx, 0x10
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (16 /*0x10*/ % 32));
    // 004dd3fb  01ca                   -add edx, ecx
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.ecx));
    // 004dd3fd  8b0d3ea28c00           -mov ecx, dword ptr [0x8ca23e]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(9216574) /* 0x8ca23e */);
    // 004dd403  c1f910                 -sar ecx, 0x10
    cpu.ecx = x86::reg32(x86::sreg32(cpu.ecx) >> (16 /*0x10*/ % 32));
    // 004dd406  8d1c0e                 -lea ebx, [esi + ecx]
    cpu.ebx = x86::reg32(cpu.esi + cpu.ecx * 1);
    // 004dd409  895dfc                 -mov dword ptr [ebp - 4], ebx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.ebx;
    // 004dd40c  89d3                   -mov ebx, edx
    cpu.ebx = cpu.edx;
    // 004dd40e  29cb                   -sub ebx, ecx
    (cpu.ebx) -= x86::reg32(x86::sreg32(cpu.ecx));
    // 004dd410  39d6                   +cmp esi, edx
    {
        x86::reg32 tmp1 = cpu.esi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.edx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004dd412  7508                   -jne 0x4dd41c
    if (!cpu.flags.zf)
    {
        goto L_0x004dd41c;
    }
    // 004dd414  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    // 004dd416  0f848d000000           -je 0x4dd4a9
    if (cpu.flags.zf)
    {
        goto L_0x004dd4a9;
    }
L_0x004dd41c:
    // 004dd41c  39d6                   +cmp esi, edx
    {
        x86::reg32 tmp1 = cpu.esi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.edx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004dd41e  7e14                   -jle 0x4dd434
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004dd434;
    }
    // 004dd420  39d0                   +cmp eax, edx
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
    // 004dd422  7d06                   -jge 0x4dd42a
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004dd42a;
    }
    // 004dd424  030540d95d00           -add eax, dword ptr [0x5dd940]
    (cpu.eax) += x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(6150464) /* 0x5dd940 */)));
L_0x004dd42a:
    // 004dd42a  8b3d40d95d00           -mov edi, dword ptr [0x5dd940]
    cpu.edi = app->getMemory<x86::reg32>(x86::reg32(6150464) /* 0x5dd940 */);
    // 004dd430  01fb                   -add ebx, edi
    (cpu.ebx) += x86::reg32(x86::sreg32(cpu.edi));
    // 004dd432  01fa                   -add edx, edi
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.edi));
L_0x004dd434:
    // 004dd434  39f0                   +cmp eax, esi
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
    // 004dd436  7c04                   -jl 0x4dd43c
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004dd43c;
    }
    // 004dd438  39d0                   +cmp eax, edx
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
    // 004dd43a  7e07                   -jle 0x4dd443
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004dd443;
    }
L_0x004dd43c:
    // 004dd43c  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
    // 004dd43e  e96b000000             -jmp 0x4dd4ae
    goto L_0x004dd4ae;
L_0x004dd443:
    // 004dd443  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    // 004dd445  7462                   -je 0x4dd4a9
    if (cpu.flags.zf)
    {
        goto L_0x004dd4a9;
    }
    // 004dd447  3b45fc                 +cmp eax, dword ptr [ebp - 4]
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004dd44a  7e04                   -jle 0x4dd450
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004dd450;
    }
    // 004dd44c  39d8                   +cmp eax, ebx
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ebx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004dd44e  7c59                   -jl 0x4dd4a9
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004dd4a9;
    }
L_0x004dd450:
    // 004dd450  8b75fc                 -mov esi, dword ptr [ebp - 4]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004dd453  39f0                   +cmp eax, esi
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
    // 004dd455  7d29                   -jge 0x4dd480
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004dd480;
    }
    // 004dd457  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 004dd459  29c2                   -sub edx, eax
    (cpu.edx) -= x86::reg32(x86::sreg32(cpu.eax));
    // 004dd45b  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004dd45d  8b1534a28c00           -mov edx, dword ptr [0x8ca234]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(9216564) /* 0x8ca234 */);
    // 004dd463  0fafd0                 -imul edx, eax
    cpu.edx = x86::reg32(x86::sreg64(x86::sreg32(cpu.edx)) * x86::sreg64(x86::sreg32(cpu.eax)));
    // 004dd466  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004dd468  c1fa1f                 -sar edx, 0x1f
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (31 /*0x1f*/ % 32));
    // 004dd46b  f7f9                   -idiv ecx
    {
        x86::sreg64 tmp = x86::sreg64(cpu.edx_eax);
        x86::sreg32 d = x86::sreg32(cpu.ecx);
        cpu.edx_eax = x86::reg64(tmp / d);
        cpu.edx = x86::reg32(tmp % d);
    }
    // 004dd46d  8b1534a28c00           -mov edx, dword ptr [0x8ca234]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(9216564) /* 0x8ca234 */);
    // 004dd473  29c2                   -sub edx, eax
    (cpu.edx) -= x86::reg32(x86::sreg32(cpu.eax));
    // 004dd475  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004dd477  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004dd479  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dd47a  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dd47b  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dd47c  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dd47d  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dd47e  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dd47f  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004dd480:
    // 004dd480  39d8                   +cmp eax, ebx
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ebx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004dd482  7e25                   -jle 0x4dd4a9
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004dd4a9;
    }
    // 004dd484  8b1534a28c00           -mov edx, dword ptr [0x8ca234]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(9216564) /* 0x8ca234 */);
    // 004dd48a  29d8                   -sub eax, ebx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.ebx));
    // 004dd48c  0fafd0                 -imul edx, eax
    cpu.edx = x86::reg32(x86::sreg64(x86::sreg32(cpu.edx)) * x86::sreg64(x86::sreg32(cpu.eax)));
    // 004dd48f  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004dd491  c1fa1f                 -sar edx, 0x1f
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (31 /*0x1f*/ % 32));
    // 004dd494  f7f9                   -idiv ecx
    {
        x86::sreg64 tmp = x86::sreg64(cpu.edx_eax);
        x86::sreg32 d = x86::sreg32(cpu.ecx);
        cpu.edx_eax = x86::reg64(tmp / d);
        cpu.edx = x86::reg32(tmp % d);
    }
    // 004dd496  8b1534a28c00           -mov edx, dword ptr [0x8ca234]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(9216564) /* 0x8ca234 */);
    // 004dd49c  29c2                   -sub edx, eax
    (cpu.edx) -= x86::reg32(x86::sreg32(cpu.eax));
    // 004dd49e  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004dd4a0  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004dd4a2  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dd4a3  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dd4a4  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dd4a5  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dd4a6  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dd4a7  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dd4a8  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004dd4a9:
    // 004dd4a9  a134a28c00             -mov eax, dword ptr [0x8ca234]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(9216564) /* 0x8ca234 */);
L_0x004dd4ae:
    // 004dd4ae  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004dd4b0  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dd4b1  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dd4b2  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dd4b3  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dd4b4  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dd4b5  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dd4b6  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 */
void Application::sub_4dd4c0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004dd4c0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004dd4c1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004dd4c2  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004dd4c3  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004dd4c4  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004dd4c6  89d1                   -mov ecx, edx
    cpu.ecx = cpu.edx;
    // 004dd4c8  833d34a28c0000         +cmp dword ptr [0x8ca234], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(9216564) /* 0x8ca234 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004dd4cf  742c                   -je 0x4dd4fd
    if (cpu.flags.zf)
    {
        goto L_0x004dd4fd;
    }
    // 004dd4d1  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004dd4d3  7428                   -je 0x4dd4fd
    if (cpu.flags.zf)
    {
        goto L_0x004dd4fd;
    }
    // 004dd4d5  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004dd4d7  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 004dd4da  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 004dd4dc  c1e003                 -shl eax, 3
    cpu.eax <<= 3 /*0x3*/ % 32;
    // 004dd4df  01c2                   -add edx, eax
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.eax));
    // 004dd4e1  c1e202                 -shl edx, 2
    cpu.edx <<= 2 /*0x2*/ % 32;
    // 004dd4e4  8b1d34a28c00           -mov ebx, dword ptr [0x8ca234]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(9216564) /* 0x8ca234 */);
    // 004dd4ea  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004dd4ec  c1fa1f                 -sar edx, 0x1f
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (31 /*0x1f*/ % 32));
    // 004dd4ef  f7fb                   -idiv ebx
    {
        x86::sreg64 tmp = x86::sreg64(cpu.edx_eax);
        x86::sreg32 d = x86::sreg32(cpu.ebx);
        cpu.edx_eax = x86::reg64(tmp / d);
        cpu.edx = x86::reg32(tmp % d);
    }
    // 004dd4f1  89048d88425600         -mov dword ptr [ecx*4 + 0x564288], eax
    app->getMemory<x86::reg32>(x86::reg32(5653128) /* 0x564288 */ + cpu.ecx * 4) = cpu.eax;
    // 004dd4f8  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dd4f9  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dd4fa  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dd4fb  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dd4fc  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004dd4fd:
    // 004dd4fd  31f6                   -xor esi, esi
    cpu.esi ^= x86::reg32(x86::sreg32(cpu.esi));
    // 004dd4ff  89348d88425600         -mov dword ptr [ecx*4 + 0x564288], esi
    app->getMemory<x86::reg32>(x86::reg32(5653128) /* 0x564288 */ + cpu.ecx * 4) = cpu.esi;
    // 004dd506  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dd507  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dd508  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dd509  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dd50a  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x40 0x00 0x8b 0xc9 */
void Application::sub_4dd510(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004dd510  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004dd511  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004dd512  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004dd513  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004dd514  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004dd515  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004dd516  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004dd518  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004dd51a  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 004dd51d  8b88b8105e00           -mov ecx, dword ptr [eax + 0x5e10b8]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164664) /* 0x5e10b8 */);
    // 004dd523  31f6                   -xor esi, esi
    cpu.esi ^= x86::reg32(x86::sreg32(cpu.esi));
    // 004dd525  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    // 004dd527  740a                   -je 0x4dd533
    if (cpu.flags.zf)
    {
        goto L_0x004dd533;
    }
    // 004dd529  7404                   -je 0x4dd52f
    if (cpu.flags.zf)
    {
        goto L_0x004dd52f;
    }
    // 004dd52b  8b01                   -mov eax, dword ptr [ecx]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx);
    // 004dd52d  eb14                   -jmp 0x4dd543
    goto L_0x004dd543;
L_0x004dd52f:
    // 004dd52f  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
    // 004dd531  eb10                   -jmp 0x4dd543
    goto L_0x004dd543;
L_0x004dd533:
    // 004dd533  8bb8b0105e00           -mov edi, dword ptr [eax + 0x5e10b0]
    cpu.edi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164656) /* 0x5e10b0 */);
    // 004dd539  85ff                   +test edi, edi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edi & cpu.edi));
    // 004dd53b  7404                   -je 0x4dd541
    if (cpu.flags.zf)
    {
        goto L_0x004dd541;
    }
    // 004dd53d  8b07                   -mov eax, dword ptr [edi]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edi);
    // 004dd53f  eb02                   -jmp 0x4dd543
    goto L_0x004dd543;
L_0x004dd541:
    // 004dd541  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
L_0x004dd543:
    // 004dd543  83f804                 +cmp eax, 4
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
    // 004dd546  7f3f                   -jg 0x4dd587
    if (!cpu.flags.zf && (cpu.flags.sf == cpu.flags.of))
    {
        goto L_0x004dd587;
    }
    // 004dd548  8d049500000000         -lea eax, [edx*4]
    cpu.eax = x86::reg32(cpu.edx * 4);
    // 004dd54f  8b88b8105e00           -mov ecx, dword ptr [eax + 0x5e10b8]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164664) /* 0x5e10b8 */);
    // 004dd555  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    // 004dd557  740a                   -je 0x4dd563
    if (cpu.flags.zf)
    {
        goto L_0x004dd563;
    }
    // 004dd559  7404                   -je 0x4dd55f
    if (cpu.flags.zf)
    {
        goto L_0x004dd55f;
    }
    // 004dd55b  8b01                   -mov eax, dword ptr [ecx]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx);
    // 004dd55d  eb14                   -jmp 0x4dd573
    goto L_0x004dd573;
L_0x004dd55f:
    // 004dd55f  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
    // 004dd561  eb10                   -jmp 0x4dd573
    goto L_0x004dd573;
L_0x004dd563:
    // 004dd563  8bb8b0105e00           -mov edi, dword ptr [eax + 0x5e10b0]
    cpu.edi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6164656) /* 0x5e10b0 */);
    // 004dd569  85ff                   +test edi, edi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edi & cpu.edi));
    // 004dd56b  7404                   -je 0x4dd571
    if (cpu.flags.zf)
    {
        goto L_0x004dd571;
    }
    // 004dd56d  8b07                   -mov eax, dword ptr [edi]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edi);
    // 004dd56f  eb02                   -jmp 0x4dd573
    goto L_0x004dd573;
L_0x004dd571:
    // 004dd571  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
L_0x004dd573:
    // 004dd573  83f802                 +cmp eax, 2
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
    // 004dd576  7c0f                   -jl 0x4dd587
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004dd587;
    }
    // 004dd578  833c95a0c4790000       +cmp dword ptr [edx*4 + 0x79c4a0], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(7980192) /* 0x79c4a0 */ + cpu.edx * 4);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004dd580  7405                   -je 0x4dd587
    if (cpu.flags.zf)
    {
        goto L_0x004dd587;
    }
    // 004dd582  be01000000             -mov esi, 1
    cpu.esi = 1 /*0x1*/;
L_0x004dd587:
    // 004dd587  8d049500000000         -lea eax, [edx*4]
    cpu.eax = x86::reg32(cpu.edx * 4);
    // 004dd58e  3bb0b4a28c00           +cmp esi, dword ptr [eax + 0x8ca2b4]
    {
        x86::reg32 tmp1 = cpu.esi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.eax + x86::reg32(9216692) /* 0x8ca2b4 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004dd594  7509                   -jne 0x4dd59f
    if (!cpu.flags.zf)
    {
        goto L_0x004dd59f;
    }
    // 004dd596  83b8f42f550000         +cmp dword ptr [eax + 0x552ff4], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(5582836) /* 0x552ff4 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004dd59d  7432                   -je 0x4dd5d1
    if (cpu.flags.zf)
    {
        goto L_0x004dd5d1;
    }
L_0x004dd59f:
    // 004dd59f  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
L_0x004dd5a1:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004dd5a1  3b1d34a28c00           +cmp ebx, dword ptr [0x8ca234]
    {
        x86::reg32 tmp1 = cpu.ebx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(9216564) /* 0x8ca234 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004dd5a7  7d28                   -jge 0x4dd5d1
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004dd5d1;
    }
    // 004dd5a9  8d049500000000         -lea eax, [edx*4]
    cpu.eax = x86::reg32(cpu.edx * 4);
    // 004dd5b0  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 004dd5b2  c1e007                 -shl eax, 7
    cpu.eax <<= 7 /*0x7*/ % 32;
    // 004dd5b5  89c7                   -mov edi, eax
    cpu.edi = cpu.eax;
    // 004dd5b7  c1e704                 -shl edi, 4
    cpu.edi <<= 4 /*0x4*/ % 32;
    // 004dd5ba  29c7                   -sub edi, eax
    (cpu.edi) -= x86::reg32(x86::sreg32(cpu.eax));
    // 004dd5bc  8d049d00000000         -lea eax, [ebx*4]
    cpu.eax = x86::reg32(cpu.ebx * 4);
    // 004dd5c3  29d8                   -sub eax, ebx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.ebx));
    // 004dd5c5  30c9                   +xor cl, cl
    cpu.clear_co();
    cpu.set_szp((cpu.cl ^= x86::reg8(x86::sreg8(cpu.cl))));
    // 004dd5c7  43                     +inc ebx
    {
        x86::reg32& tmp = cpu.ebx;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 004dd5c8  888c87f10b8c00         -mov byte ptr [edi + eax*4 + 0x8c0bf1], cl
    app->getMemory<x86::reg8>(cpu.edi + x86::reg32(9178097) /* 0x8c0bf1 */ + cpu.eax * 4) = cpu.cl;
    // 004dd5cf  ebd0                   -jmp 0x4dd5a1
    goto L_0x004dd5a1;
L_0x004dd5d1:
    // 004dd5d1  893495b4a28c00         -mov dword ptr [edx*4 + 0x8ca2b4], esi
    app->getMemory<x86::reg32>(x86::reg32(9216692) /* 0x8ca2b4 */ + cpu.edx * 4) = cpu.esi;
    // 004dd5d8  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dd5d9  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dd5da  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dd5db  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dd5dc  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dd5dd  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dd5de  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x90 */
void Application::sub_4dd5e0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004dd5e0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004dd5e1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004dd5e2  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004dd5e3  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004dd5e4  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004dd5e5  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004dd5e7  83ec2c                 -sub esp, 0x2c
    (cpu.esp) -= x86::reg32(x86::sreg32(44 /*0x2c*/));
    // 004dd5ea  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 004dd5ec  8955e8                 -mov dword ptr [ebp - 0x18], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-24) /* -0x18 */) = cpu.edx;
    // 004dd5ef  8b4004                 -mov eax, dword ptr [eax + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 004dd5f2  8945f8                 -mov dword ptr [ebp - 8], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.eax;
    // 004dd5f5  8d148500000000         -lea edx, [eax*4]
    cpu.edx = x86::reg32(cpu.eax * 4);
    // 004dd5fc  a184367d00             -mov eax, dword ptr [0x7d3684]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(8205956) /* 0x7d3684 */);
    // 004dd601  2b82e00b8c00           -sub eax, dword ptr [edx + 0x8c0be0]
    (cpu.eax) -= x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.edx + x86::reg32(9178080) /* 0x8c0be0 */)));
    // 004dd607  83f801                 +cmp eax, 1
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
    // 004dd60a  0f8e16030000           -jle 0x4dd926
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004dd926;
    }
    // 004dd610  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004dd612  e84937f4ff             -call 0x420d60
    cpu.esp -= 4;
    nfs3hp::trackdata::carFacingWay(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dd617  8945ec                 -mov dword ptr [ebp - 0x14], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */) = cpu.eax;
    // 004dd61a  a184367d00             -mov eax, dword ptr [0x7d3684]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(8205956) /* 0x7d3684 */);
    // 004dd61f  8982e00b8c00           -mov dword ptr [edx + 0x8c0be0], eax
    app->getMemory<x86::reg32>(cpu.edx + x86::reg32(9178080) /* 0x8c0be0 */) = cpu.eax;
    // 004dd625  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
L_0x004dd627:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004dd627  3b1578a28c00           +cmp edx, dword ptr [0x8ca278]
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(9216632) /* 0x8ca278 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004dd62d  7d38                   -jge 0x4dd667
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004dd667;
    }
    // 004dd62f  8b4df8                 -mov ecx, dword ptr [ebp - 8]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004dd632  8d1c8d00000000         -lea ebx, [ecx*4]
    cpu.ebx = x86::reg32(cpu.ecx * 4);
    // 004dd639  29cb                   -sub ebx, ecx
    (cpu.ebx) -= x86::reg32(x86::sreg32(cpu.ecx));
    // 004dd63b  8d049500000000         -lea eax, [edx*4]
    cpu.eax = x86::reg32(cpu.edx * 4);
    // 004dd642  c1e303                 -shl ebx, 3
    cpu.ebx <<= 3 /*0x3*/ % 32;
    // 004dd645  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 004dd647  01cb                   -add ebx, ecx
    (cpu.ebx) += x86::reg32(x86::sreg32(cpu.ecx));
    // 004dd649  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 004dd64c  c1e304                 -shl ebx, 4
    cpu.ebx <<= 4 /*0x4*/ % 32;
    // 004dd64f  01d8                   -add eax, ebx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.ebx));
    // 004dd651  8bb8c8088c00           -mov edi, dword ptr [eax + 0x8c08c8]
    cpu.edi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(9177288) /* 0x8c08c8 */);
    // 004dd657  85ff                   +test edi, edi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edi & cpu.edi));
    // 004dd659  7409                   -je 0x4dd664
    if (cpu.flags.zf)
    {
        goto L_0x004dd664;
    }
    // 004dd65b  8d4fff                 -lea ecx, [edi - 1]
    cpu.ecx = x86::reg32(cpu.edi + x86::reg32(-1) /* -0x1 */);
    // 004dd65e  8988c8088c00           -mov dword ptr [eax + 0x8c08c8], ecx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(9177288) /* 0x8c08c8 */) = cpu.ecx;
L_0x004dd664:
    // 004dd664  42                     +inc edx
    {
        x86::reg32& tmp = cpu.edx;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 004dd665  ebc0                   -jmp 0x4dd627
    goto L_0x004dd627;
L_0x004dd667:
    // 004dd667  8b5df8                 -mov ebx, dword ptr [ebp - 8]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004dd66a  8d049d00000000         -lea eax, [ebx*4]
    cpu.eax = x86::reg32(cpu.ebx * 4);
    // 004dd671  01d8                   -add eax, ebx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.ebx));
    // 004dd673  c1e007                 -shl eax, 7
    cpu.eax <<= 7 /*0x7*/ % 32;
    // 004dd676  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 004dd678  c1e004                 -shl eax, 4
    cpu.eax <<= 4 /*0x4*/ % 32;
    // 004dd67b  bae8568c00             -mov edx, 0x8c56e8
    cpu.edx = 9197288 /*0x8c56e8*/;
    // 004dd680  29d8                   -sub eax, ebx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.ebx));
    // 004dd682  bb6ca28c00             -mov ebx, 0x8ca26c
    cpu.ebx = 9216620 /*0x8ca26c*/;
    // 004dd687  01c2                   -add edx, eax
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.eax));
    // 004dd689  a134a28c00             -mov eax, dword ptr [0x8ca234]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(9216564) /* 0x8ca234 */);
    // 004dd68e  89d1                   -mov ecx, edx
    cpu.ecx = cpu.edx;
    // 004dd690  e81b290000             -call 0x4dffb0
    cpu.esp -= 4;
    nfs3hp::vertices::addVectors(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dd695  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
L_0x004dd697:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004dd697  3b5de8                 +cmp ebx, dword ptr [ebp - 0x18]
    {
        x86::reg32 tmp1 = cpu.ebx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-24) /* -0x18 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004dd69a  0f8d86020000           -jge 0x4dd926
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004dd926;
    }
    // 004dd6a0  8b55f8                 -mov edx, dword ptr [ebp - 8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004dd6a3  8d049500000000         -lea eax, [edx*4]
    cpu.eax = x86::reg32(cpu.edx * 4);
    // 004dd6aa  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 004dd6ac  c1e007                 -shl eax, 7
    cpu.eax <<= 7 /*0x7*/ % 32;
    // 004dd6af  89c7                   -mov edi, eax
    cpu.edi = cpu.eax;
    // 004dd6b1  c1e704                 -shl edi, 4
    cpu.edi <<= 4 /*0x4*/ % 32;
    // 004dd6b4  29c7                   -sub edi, eax
    (cpu.edi) -= x86::reg32(x86::sreg32(cpu.eax));
    // 004dd6b6  8d049d00000000         -lea eax, [ebx*4]
    cpu.eax = x86::reg32(cpu.ebx * 4);
    // 004dd6bd  b9e80b8c00             -mov ecx, 0x8c0be8
    cpu.ecx = 9178088 /*0x8c0be8*/;
    // 004dd6c2  29d8                   -sub eax, ebx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.ebx));
    // 004dd6c4  01f9                   -add ecx, edi
    (cpu.ecx) += x86::reg32(x86::sreg32(cpu.edi));
    // 004dd6c6  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 004dd6c9  81c7e8568c00           -add edi, 0x8c56e8
    (cpu.edi) += x86::reg32(x86::sreg32(9197288 /*0x8c56e8*/));
    // 004dd6cf  01c1                   -add ecx, eax
    (cpu.ecx) += x86::reg32(x86::sreg32(cpu.eax));
    // 004dd6d1  8d1407                 -lea edx, [edi + eax]
    cpu.edx = x86::reg32(cpu.edi + cpu.eax * 1);
    // 004dd6d4  a12ca28c00             -mov eax, dword ptr [0x8ca22c]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(9216556) /* 0x8ca22c */);
    // 004dd6d9  83f802                 +cmp eax, 2
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
    // 004dd6dc  7551                   -jne 0x4dd72f
    if (!cpu.flags.zf)
    {
        goto L_0x004dd72f;
    }
    // 004dd6de  80790800               +cmp byte ptr [ecx + 8], 0
    {
        x86::reg8 tmp1 = app->getMemory<x86::reg8>(cpu.ecx + x86::reg32(8) /* 0x8 */);
        x86::reg8 tmp2 = x86::reg8(x86::sreg8(0 /*0x0*/));
        x86::reg8 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 7);
        cpu.flags.of ^= 1 & (result >> 7);
        cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
        cpu.set_szp(result);
    }
    // 004dd6e2  754b                   -jne 0x4dd72f
    if (!cpu.flags.zf)
    {
        goto L_0x004dd72f;
    }
    // 004dd6e4  89df                   -mov edi, ebx
    cpu.edi = cpu.ebx;
    // 004dd6e6  a184367d00             -mov eax, dword ptr [0x7d3684]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(8205956) /* 0x7d3684 */);
    // 004dd6eb  c1e708                 -shl edi, 8
    cpu.edi <<= 8 /*0x8*/ % 32;
    // 004dd6ee  c1e008                 -shl eax, 8
    cpu.eax <<= 8 /*0x8*/ % 32;
    // 004dd6f1  01c7                   -add edi, eax
    (cpu.edi) += x86::reg32(x86::sreg32(cpu.eax));
    // 004dd6f3  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 004dd6f5  e8864c0100             -call 0x4f2380
    cpu.esp -= 4;
    nfs3hp::load::fixedSine(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dd6fa  c1f804                 -sar eax, 4
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (4 /*0x4*/ % 32));
    // 004dd6fd  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 004dd700  db45fc                 -fild dword ptr [ebp - 4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 004dd703  dc0dc4975400           -fmul qword ptr [0x5497c4]
    x86::Float fpu2 = cpu.fpu.mul(fpu1, x86::Float(app->getMemory<double>(x86::reg32(5543876) /* 0x5497c4 */)));
    // 004dd709  d902                   -fld dword ptr [edx]
    x86::Float fpu3 = x86::Float(app->getMemory<float>(cpu.edx));
    // 004dd70b  d9c9                   -fxch st(1)
    
    // 004dd70d  d8c1                   -fadd st(1)
    x86::Float fpu4 = cpu.fpu.add(fpu2, x86::Float(fpu3));
    // 004dd70f  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 004dd711  ddd9                   -fstp st(1)
    x86::Float fpu5 = x86::Float(fpu4);
    // 004dd713  d91a                   -fstp dword ptr [edx]
    app->getMemory<float>(cpu.edx) = float(fpu5);
    }
    // 004dd715  e8d64c0100             -call 0x4f23f0
    cpu.esp -= 4;
    nfs3hp::load::fixedCosine(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dd71a  c1f804                 +sar eax, 4
    {
        x86::reg8 tmp = 4 /*0x4*/ % 32;
        x86::reg32& op = cpu.eax;
        if (tmp)
        {
            cpu.flags.cf = 1 & (x86::sreg32(op) >> (tmp - 1));
            if (tmp == 1) cpu.flags.of = 0;
            cpu.set_szp((op = x86::reg32(x86::sreg32(op) >> tmp)));
        }
    }
    // 004dd71d  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 004dd720  db45fc                 +fild dword ptr [ebp - 4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu6 = x86::Float(x86::sreg32(app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */)));
    // 004dd723  dc0dc4975400           +fmul qword ptr [0x5497c4]
    x86::Float fpu7 = cpu.fpu.mul(fpu6, x86::Float(app->getMemory<double>(x86::reg32(5543876) /* 0x5497c4 */)));
    // 004dd729  d84208                 +fadd dword ptr [edx + 8]
    x86::Float fpu8 = cpu.fpu.add(fpu7, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(8) /* 0x8 */)));
    // 004dd72c  d95a08                 +fstp dword ptr [edx + 8]
    app->getMemory<float>(cpu.edx + x86::reg32(8) /* 0x8 */) = float(fpu8);
    }
L_0x004dd72f:
    // 004dd72f  d902                   +fld dword ptr [edx]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu9 = x86::Float(app->getMemory<float>(cpu.edx));
    // 004dd731  d94204                 +fld dword ptr [edx + 4]
    x86::Float fpu10 = x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(4) /* 0x4 */));
    // 004dd734  d94208                 +fld dword ptr [edx + 8]
    x86::Float fpu11 = x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(8) /* 0x8 */));
    // 004dd737  d9ca                   +fxch st(2)
    
    // 004dd739  d86608                 +fsub dword ptr [esi + 8]
    x86::Float fpu12 = cpu.fpu.sub(fpu9, x86::Float(app->getMemory<float>(cpu.esi + x86::reg32(8) /* 0x8 */)));
    // 004dd73c  d9c9                   +fxch st(1)
    
    // 004dd73e  d8660c                 +fsub dword ptr [esi + 0xc]
    x86::Float fpu13 = cpu.fpu.sub(fpu10, x86::Float(app->getMemory<float>(cpu.esi + x86::reg32(12) /* 0xc */)));
    // 004dd741  d9ca                   +fxch st(2)
    
    // 004dd743  d86610                 +fsub dword ptr [esi + 0x10]
    x86::Float fpu14 = cpu.fpu.sub(fpu11, x86::Float(app->getMemory<float>(cpu.esi + x86::reg32(16) /* 0x10 */)));
    // 004dd746  d9c9                   +fxch st(1)
    
    // 004dd748  d95dd4                 +fstp dword ptr [ebp - 0x2c]
    app->getMemory<float>(cpu.ebp + x86::reg32(-44) /* -0x2c */) = float(fpu12);
    // 004dd74b  d9c9                   +fxch st(1)
    
    // 004dd74d  d95dd8                 +fstp dword ptr [ebp - 0x28]
    app->getMemory<float>(cpu.ebp + x86::reg32(-40) /* -0x28 */) = float(fpu13);
    // 004dd750  d95ddc                 +fstp dword ptr [ebp - 0x24]
    app->getMemory<float>(cpu.ebp + x86::reg32(-36) /* -0x24 */) = float(fpu14);
    // 004dd753  d945d8                 +fld dword ptr [ebp - 0x28]
    x86::Float fpu15 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-40) /* -0x28 */));
    // 004dd756  d81d60a28c00           +fcomp dword ptr [0x8ca260]
    cpu.fpu.compare(fpu15, x86::Float(app->getMemory<float>(x86::reg32(9216608) /* 0x8ca260 */)));
    // 004dd75c  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 004dd75e  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 004dd75f  0f8262000000           -jb 0x4dd7c7
    if (cpu.flags.cf)
    {
        goto L_0x004dd7c7;
    }
    // 004dd765  d945d8                 +fld dword ptr [ebp - 0x28]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu16 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-40) /* -0x28 */));
    // 004dd768  d81d64a28c00           +fcomp dword ptr [0x8ca264]
    cpu.fpu.compare(fpu16, x86::Float(app->getMemory<float>(x86::reg32(9216612) /* 0x8ca264 */)));
    // 004dd76e  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 004dd770  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 004dd771  7754                   -ja 0x4dd7c7
    if (!cpu.flags.cf && !cpu.flags.zf)
    {
        goto L_0x004dd7c7;
    }
    // 004dd773  d9ee                   +fldz 
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu17 = 0.0;
    // 004dd775  d85dd4                 +fcomp dword ptr [ebp - 0x2c]
    cpu.fpu.compare(fpu17, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-44) /* -0x2c */)));
    // 004dd778  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 004dd77a  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 004dd77b  760a                   -jbe 0x4dd787
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x004dd787;
    }
    // 004dd77d  d945d4                 +fld dword ptr [ebp - 0x2c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu18 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-44) /* -0x2c */));
    // 004dd780  d9e0                   +fchs 
    x86::Float fpu19 = -fpu18;
    // 004dd782  d95df4                 +fstp dword ptr [ebp - 0xc]
    app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */) = float(fpu19);
    }
    // 004dd785  eb06                   -jmp 0x4dd78d
    goto L_0x004dd78d;
L_0x004dd787:
    // 004dd787  8b45d4                 -mov eax, dword ptr [ebp - 0x2c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-44) /* -0x2c */);
    // 004dd78a  8945f4                 -mov dword ptr [ebp - 0xc], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */) = cpu.eax;
L_0x004dd78d:
    // 004dd78d  d945f4                 +fld dword ptr [ebp - 0xc]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu20 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */));
    // 004dd790  d81d5ca28c00           +fcomp dword ptr [0x8ca25c]
    cpu.fpu.compare(fpu20, x86::Float(app->getMemory<float>(x86::reg32(9216604) /* 0x8ca25c */)));
    // 004dd796  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 004dd798  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 004dd799  772c                   -ja 0x4dd7c7
    if (!cpu.flags.cf && !cpu.flags.zf)
    {
        goto L_0x004dd7c7;
    }
    // 004dd79b  d9ee                   +fldz 
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu21 = 0.0;
    // 004dd79d  d85ddc                 +fcomp dword ptr [ebp - 0x24]
    cpu.fpu.compare(fpu21, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-36) /* -0x24 */)));
    // 004dd7a0  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 004dd7a2  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 004dd7a3  760a                   -jbe 0x4dd7af
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x004dd7af;
    }
    // 004dd7a5  d945dc                 +fld dword ptr [ebp - 0x24]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu22 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-36) /* -0x24 */));
    // 004dd7a8  d9e0                   +fchs 
    x86::Float fpu23 = -fpu22;
    // 004dd7aa  d95df0                 +fstp dword ptr [ebp - 0x10]
    app->getMemory<float>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = float(fpu23);
    }
    // 004dd7ad  eb06                   -jmp 0x4dd7b5
    goto L_0x004dd7b5;
L_0x004dd7af:
    // 004dd7af  8b45dc                 -mov eax, dword ptr [ebp - 0x24]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-36) /* -0x24 */);
    // 004dd7b2  8945f0                 -mov dword ptr [ebp - 0x10], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = cpu.eax;
L_0x004dd7b5:
    // 004dd7b5  d945f0                 +fld dword ptr [ebp - 0x10]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu24 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-16) /* -0x10 */));
    // 004dd7b8  d81d5ca28c00           +fcomp dword ptr [0x8ca25c]
    cpu.fpu.compare(fpu24, x86::Float(app->getMemory<float>(x86::reg32(9216604) /* 0x8ca25c */)));
    // 004dd7be  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 004dd7c0  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 004dd7c1  0f8659010000           -jbe 0x4dd920
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x004dd920;
    }
L_0x004dd7c7:
    // 004dd7c7  8a45ec                 -mov al, byte ptr [ebp - 0x14]
    cpu.al = app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-20) /* -0x14 */);
    // 004dd7ca  884108                 -mov byte ptr [ecx + 8], al
    app->getMemory<x86::reg8>(cpu.ecx + x86::reg32(8) /* 0x8 */) = cpu.al;
    // 004dd7cd  d945d4                 +fld dword ptr [ebp - 0x2c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu25 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-44) /* -0x2c */));
    // 004dd7d0  d81d5ca28c00           +fcomp dword ptr [0x8ca25c]
    cpu.fpu.compare(fpu25, x86::Float(app->getMemory<float>(x86::reg32(9216604) /* 0x8ca25c */)));
    // 004dd7d6  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 004dd7d8  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 004dd7d9  7611                   -jbe 0x4dd7ec
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x004dd7ec;
    }
    // 004dd7db  c6410900               -mov byte ptr [ecx + 9], 0
    app->getMemory<x86::reg8>(cpu.ecx + x86::reg32(9) /* 0x9 */) = 0 /*0x0*/;
    // 004dd7df  d9055ca28c00           +fld dword ptr [0x8ca25c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu26 = x86::Float(app->getMemory<float>(x86::reg32(9216604) /* 0x8ca25c */));
    // 004dd7e5  d9e0                   +fchs 
    x86::Float fpu27 = -fpu26;
    // 004dd7e7  d95dd4                 +fstp dword ptr [ebp - 0x2c]
    app->getMemory<float>(cpu.ebp + x86::reg32(-44) /* -0x2c */) = float(fpu27);
    }
    // 004dd7ea  eb1c                   -jmp 0x4dd808
    goto L_0x004dd808;
L_0x004dd7ec:
    // 004dd7ec  d9055ca28c00           +fld dword ptr [0x8ca25c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu28 = x86::Float(app->getMemory<float>(x86::reg32(9216604) /* 0x8ca25c */));
    // 004dd7f2  d9e0                   +fchs 
    x86::Float fpu29 = -fpu28;
    // 004dd7f4  d85dd4                 +fcomp dword ptr [ebp - 0x2c]
    cpu.fpu.compare(fpu29, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-44) /* -0x2c */)));
    // 004dd7f7  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 004dd7f9  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 004dd7fa  763a                   -jbe 0x4dd836
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x004dd836;
    }
    // 004dd7fc  c6410900               -mov byte ptr [ecx + 9], 0
    app->getMemory<x86::reg8>(cpu.ecx + x86::reg32(9) /* 0x9 */) = 0 /*0x0*/;
    // 004dd800  a15ca28c00             -mov eax, dword ptr [0x8ca25c]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(9216604) /* 0x8ca25c */);
    // 004dd805  8945d4                 -mov dword ptr [ebp - 0x2c], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-44) /* -0x2c */) = cpu.eax;
L_0x004dd808:
    // 004dd808  e823da0000             -call 0x4eb230
    cpu.esp -= 4;
    nfs3hp::ea::randomFraction(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dd80d  d80d68a28c00           +fmul dword ptr [0x8ca268]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu30 = cpu.fpu.st(0);
    x86::Float fpu31 = cpu.fpu.mul(fpu30, x86::Float(app->getMemory<float>(x86::reg32(9216616) /* 0x8ca268 */)));
    // 004dd813  d80560a28c00           +fadd dword ptr [0x8ca260]
    x86::Float fpu32 = cpu.fpu.add(fpu31, x86::Float(app->getMemory<float>(x86::reg32(9216608) /* 0x8ca260 */)));
    // 004dd819  d95dd8                 +fstp dword ptr [ebp - 0x28]
    app->getMemory<float>(cpu.ebp + x86::reg32(-40) /* -0x28 */) = float(fpu32);
    cpu.fpu.count -= 1;
    }
    // 004dd81c  e80fda0000             -call 0x4eb230
    cpu.esp -= 4;
    nfs3hp::ea::randomFraction(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dd821  d80d5ca28c00           +fmul dword ptr [0x8ca25c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu33 = cpu.fpu.st(0);
    x86::Float fpu34 = cpu.fpu.mul(fpu33, x86::Float(app->getMemory<float>(x86::reg32(9216604) /* 0x8ca25c */)));
    // 004dd827  d80dcc975400           +fmul dword ptr [0x5497cc]
    x86::Float fpu35 = cpu.fpu.mul(fpu34, x86::Float(app->getMemory<float>(x86::reg32(5543884) /* 0x5497cc */)));
    // 004dd82d  d8255ca28c00           +fsub dword ptr [0x8ca25c]
    x86::Float fpu36 = cpu.fpu.sub(fpu35, x86::Float(app->getMemory<float>(x86::reg32(9216604) /* 0x8ca25c */)));
    // 004dd833  d95ddc                 +fstp dword ptr [ebp - 0x24]
    app->getMemory<float>(cpu.ebp + x86::reg32(-36) /* -0x24 */) = float(fpu36);
    cpu.fpu.count -= 1;
    }
L_0x004dd836:
    // 004dd836  d945dc                 +fld dword ptr [ebp - 0x24]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu37 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-36) /* -0x24 */));
    // 004dd839  d81d5ca28c00           +fcomp dword ptr [0x8ca25c]
    cpu.fpu.compare(fpu37, x86::Float(app->getMemory<float>(x86::reg32(9216604) /* 0x8ca25c */)));
    // 004dd83f  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 004dd841  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 004dd842  7611                   -jbe 0x4dd855
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x004dd855;
    }
    // 004dd844  c6410900               -mov byte ptr [ecx + 9], 0
    app->getMemory<x86::reg8>(cpu.ecx + x86::reg32(9) /* 0x9 */) = 0 /*0x0*/;
    // 004dd848  d9055ca28c00           +fld dword ptr [0x8ca25c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu38 = x86::Float(app->getMemory<float>(x86::reg32(9216604) /* 0x8ca25c */));
    // 004dd84e  d9e0                   +fchs 
    x86::Float fpu39 = -fpu38;
    // 004dd850  d95ddc                 +fstp dword ptr [ebp - 0x24]
    app->getMemory<float>(cpu.ebp + x86::reg32(-36) /* -0x24 */) = float(fpu39);
    }
    // 004dd853  eb1c                   -jmp 0x4dd871
    goto L_0x004dd871;
L_0x004dd855:
    // 004dd855  d9055ca28c00           +fld dword ptr [0x8ca25c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu40 = x86::Float(app->getMemory<float>(x86::reg32(9216604) /* 0x8ca25c */));
    // 004dd85b  d9e0                   +fchs 
    x86::Float fpu41 = -fpu40;
    // 004dd85d  d85ddc                 +fcomp dword ptr [ebp - 0x24]
    cpu.fpu.compare(fpu41, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-36) /* -0x24 */)));
    // 004dd860  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 004dd862  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 004dd863  763a                   -jbe 0x4dd89f
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x004dd89f;
    }
    // 004dd865  c6410900               -mov byte ptr [ecx + 9], 0
    app->getMemory<x86::reg8>(cpu.ecx + x86::reg32(9) /* 0x9 */) = 0 /*0x0*/;
    // 004dd869  a15ca28c00             -mov eax, dword ptr [0x8ca25c]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(9216604) /* 0x8ca25c */);
    // 004dd86e  8945dc                 -mov dword ptr [ebp - 0x24], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-36) /* -0x24 */) = cpu.eax;
L_0x004dd871:
    // 004dd871  e8bad90000             -call 0x4eb230
    cpu.esp -= 4;
    nfs3hp::ea::randomFraction(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dd876  d80d68a28c00           +fmul dword ptr [0x8ca268]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu42 = cpu.fpu.st(0);
    x86::Float fpu43 = cpu.fpu.mul(fpu42, x86::Float(app->getMemory<float>(x86::reg32(9216616) /* 0x8ca268 */)));
    // 004dd87c  d80560a28c00           +fadd dword ptr [0x8ca260]
    x86::Float fpu44 = cpu.fpu.add(fpu43, x86::Float(app->getMemory<float>(x86::reg32(9216608) /* 0x8ca260 */)));
    // 004dd882  d95dd8                 +fstp dword ptr [ebp - 0x28]
    app->getMemory<float>(cpu.ebp + x86::reg32(-40) /* -0x28 */) = float(fpu44);
    cpu.fpu.count -= 1;
    }
    // 004dd885  e8a6d90000             -call 0x4eb230
    cpu.esp -= 4;
    nfs3hp::ea::randomFraction(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dd88a  d80d5ca28c00           +fmul dword ptr [0x8ca25c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu45 = cpu.fpu.st(0);
    x86::Float fpu46 = cpu.fpu.mul(fpu45, x86::Float(app->getMemory<float>(x86::reg32(9216604) /* 0x8ca25c */)));
    // 004dd890  d80dcc975400           +fmul dword ptr [0x5497cc]
    x86::Float fpu47 = cpu.fpu.mul(fpu46, x86::Float(app->getMemory<float>(x86::reg32(5543884) /* 0x5497cc */)));
    // 004dd896  d8255ca28c00           +fsub dword ptr [0x8ca25c]
    x86::Float fpu48 = cpu.fpu.sub(fpu47, x86::Float(app->getMemory<float>(x86::reg32(9216604) /* 0x8ca25c */)));
    // 004dd89c  d95ddc                 +fstp dword ptr [ebp - 0x24]
    app->getMemory<float>(cpu.ebp + x86::reg32(-36) /* -0x24 */) = float(fpu48);
    cpu.fpu.count -= 1;
    }
L_0x004dd89f:
    // 004dd89f  d945d8                 +fld dword ptr [ebp - 0x28]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu49 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-40) /* -0x28 */));
    // 004dd8a2  d81d64a28c00           +fcomp dword ptr [0x8ca264]
    cpu.fpu.compare(fpu49, x86::Float(app->getMemory<float>(x86::reg32(9216612) /* 0x8ca264 */)));
    // 004dd8a8  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 004dd8aa  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 004dd8ab  760b                   -jbe 0x4dd8b8
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x004dd8b8;
    }
    // 004dd8ad  c6410900               -mov byte ptr [ecx + 9], 0
    app->getMemory<x86::reg8>(cpu.ecx + x86::reg32(9) /* 0x9 */) = 0 /*0x0*/;
    // 004dd8b1  a160a28c00             -mov eax, dword ptr [0x8ca260]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(9216608) /* 0x8ca260 */);
    // 004dd8b6  eb17                   -jmp 0x4dd8cf
    goto L_0x004dd8cf;
L_0x004dd8b8:
    // 004dd8b8  d945d8                 +fld dword ptr [ebp - 0x28]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu50 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-40) /* -0x28 */));
    // 004dd8bb  d81d60a28c00           +fcomp dword ptr [0x8ca260]
    cpu.fpu.compare(fpu50, x86::Float(app->getMemory<float>(x86::reg32(9216608) /* 0x8ca260 */)));
    // 004dd8c1  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 004dd8c3  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 004dd8c4  7340                   -jae 0x4dd906
    if (!cpu.flags.cf)
    {
        goto L_0x004dd906;
    }
    // 004dd8c6  c6410900               -mov byte ptr [ecx + 9], 0
    app->getMemory<x86::reg8>(cpu.ecx + x86::reg32(9) /* 0x9 */) = 0 /*0x0*/;
    // 004dd8ca  a164a28c00             -mov eax, dword ptr [0x8ca264]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(9216612) /* 0x8ca264 */);
L_0x004dd8cf:
    // 004dd8cf  8945d8                 -mov dword ptr [ebp - 0x28], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-40) /* -0x28 */) = cpu.eax;
    // 004dd8d2  e859d90000             -call 0x4eb230
    cpu.esp -= 4;
    nfs3hp::ea::randomFraction(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dd8d7  d80d5ca28c00           +fmul dword ptr [0x8ca25c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu51 = cpu.fpu.st(0);
    x86::Float fpu52 = cpu.fpu.mul(fpu51, x86::Float(app->getMemory<float>(x86::reg32(9216604) /* 0x8ca25c */)));
    // 004dd8dd  d80dcc975400           +fmul dword ptr [0x5497cc]
    x86::Float fpu53 = cpu.fpu.mul(fpu52, x86::Float(app->getMemory<float>(x86::reg32(5543884) /* 0x5497cc */)));
    // 004dd8e3  d8255ca28c00           +fsub dword ptr [0x8ca25c]
    x86::Float fpu54 = cpu.fpu.sub(fpu53, x86::Float(app->getMemory<float>(x86::reg32(9216604) /* 0x8ca25c */)));
    // 004dd8e9  d95dd4                 +fstp dword ptr [ebp - 0x2c]
    app->getMemory<float>(cpu.ebp + x86::reg32(-44) /* -0x2c */) = float(fpu54);
    cpu.fpu.count -= 1;
    }
    // 004dd8ec  e83fd90000             -call 0x4eb230
    cpu.esp -= 4;
    nfs3hp::ea::randomFraction(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dd8f1  d80d5ca28c00           +fmul dword ptr [0x8ca25c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu55 = cpu.fpu.st(0);
    x86::Float fpu56 = cpu.fpu.mul(fpu55, x86::Float(app->getMemory<float>(x86::reg32(9216604) /* 0x8ca25c */)));
    // 004dd8f7  d80dcc975400           +fmul dword ptr [0x5497cc]
    x86::Float fpu57 = cpu.fpu.mul(fpu56, x86::Float(app->getMemory<float>(x86::reg32(5543884) /* 0x5497cc */)));
    // 004dd8fd  d8255ca28c00           +fsub dword ptr [0x8ca25c]
    x86::Float fpu58 = cpu.fpu.sub(fpu57, x86::Float(app->getMemory<float>(x86::reg32(9216604) /* 0x8ca25c */)));
    // 004dd903  d95ddc                 +fstp dword ptr [ebp - 0x24]
    app->getMemory<float>(cpu.ebp + x86::reg32(-36) /* -0x24 */) = float(fpu58);
    cpu.fpu.count -= 1;
    }
L_0x004dd906:
    // 004dd906  d94608                 +fld dword ptr [esi + 8]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu59 = x86::Float(app->getMemory<float>(cpu.esi + x86::reg32(8) /* 0x8 */));
    // 004dd909  d845d4                 +fadd dword ptr [ebp - 0x2c]
    x86::Float fpu60 = cpu.fpu.add(fpu59, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-44) /* -0x2c */)));
    // 004dd90c  d91a                   +fstp dword ptr [edx]
    app->getMemory<float>(cpu.edx) = float(fpu60);
    // 004dd90e  d9460c                 +fld dword ptr [esi + 0xc]
    x86::Float fpu61 = x86::Float(app->getMemory<float>(cpu.esi + x86::reg32(12) /* 0xc */));
    // 004dd911  d845d8                 +fadd dword ptr [ebp - 0x28]
    x86::Float fpu62 = cpu.fpu.add(fpu61, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-40) /* -0x28 */)));
    // 004dd914  d95a04                 +fstp dword ptr [edx + 4]
    app->getMemory<float>(cpu.edx + x86::reg32(4) /* 0x4 */) = float(fpu62);
    // 004dd917  d94610                 +fld dword ptr [esi + 0x10]
    x86::Float fpu63 = x86::Float(app->getMemory<float>(cpu.esi + x86::reg32(16) /* 0x10 */));
    // 004dd91a  d845dc                 +fadd dword ptr [ebp - 0x24]
    x86::Float fpu64 = cpu.fpu.add(fpu63, x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-36) /* -0x24 */)));
    // 004dd91d  d95a08                 +fstp dword ptr [edx + 8]
    app->getMemory<float>(cpu.edx + x86::reg32(8) /* 0x8 */) = float(fpu64);
    }
L_0x004dd920:
    // 004dd920  43                     +inc ebx
    {
        x86::reg32& tmp = cpu.ebx;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 004dd921  e971fdffff             -jmp 0x4dd697
    goto L_0x004dd697;
L_0x004dd926:
    // 004dd926  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004dd928  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dd929  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dd92a  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dd92b  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dd92c  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dd92d  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8b 0xc0 */
void Application::sub_4dd930(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004dd930  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004dd931  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004dd932  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004dd933  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004dd934  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004dd935  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004dd936  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004dd938  83ec34                 -sub esp, 0x34
    (cpu.esp) -= x86::reg32(x86::sreg32(52 /*0x34*/));
    // 004dd93b  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 004dd93d  8b15a0367d00           -mov edx, dword ptr [0x7d36a0]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(8205984) /* 0x7d36a0 */);
    // 004dd943  8b7804                 -mov edi, dword ptr [eax + 4]
    cpu.edi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 004dd946  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 004dd948  0f85e2010000           -jne 0x4ddb30
    if (!cpu.flags.zf)
    {
        goto L_0x004ddb30;
    }
    // 004dd94e  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
L_0x004dd950:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004dd950  3b0d78a28c00           +cmp ecx, dword ptr [0x8ca278]
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(9216632) /* 0x8ca278 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004dd956  0f8dd4010000           -jge 0x4ddb30
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004ddb30;
    }
    // 004dd95c  8d1cbd00000000         -lea ebx, [edi*4]
    cpu.ebx = x86::reg32(cpu.edi * 4);
    // 004dd963  29fb                   -sub ebx, edi
    (cpu.ebx) -= x86::reg32(x86::sreg32(cpu.edi));
    // 004dd965  c1e303                 -shl ebx, 3
    cpu.ebx <<= 3 /*0x3*/ % 32;
    // 004dd968  8d048d00000000         -lea eax, [ecx*4]
    cpu.eax = x86::reg32(cpu.ecx * 4);
    // 004dd96f  01fb                   -add ebx, edi
    (cpu.ebx) += x86::reg32(x86::sreg32(cpu.edi));
    // 004dd971  01c8                   -add eax, ecx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.ecx));
    // 004dd973  c1e304                 -shl ebx, 4
    cpu.ebx <<= 4 /*0x4*/ % 32;
    // 004dd976  83bc83c8088c0000       +cmp dword ptr [ebx + eax*4 + 0x8c08c8], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(9177288) /* 0x8c08c8 */ + cpu.eax * 4);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004dd97e  0f85a6010000           -jne 0x4ddb2a
    if (!cpu.flags.zf)
    {
        goto L_0x004ddb2a;
    }
    // 004dd984  8d5dcc                 -lea ebx, [ebp - 0x34]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-52) /* -0x34 */);
    // 004dd987  8d451c                 -lea eax, [ebp + 0x1c]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(28) /* 0x1c */);
    // 004dd98a  8d5644                 -lea edx, [esi + 0x44]
    cpu.edx = x86::reg32(cpu.esi + x86::reg32(68) /* 0x44 */);
    // 004dd98d  d900                   -fld dword ptr [eax]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(cpu.eax));
    // 004dd98f  d80a                   -fmul dword ptr [edx]
    x86::Float fpu2 = cpu.fpu.mul(fpu1, x86::Float(app->getMemory<float>(cpu.edx)));
    // 004dd991  d900                   -fld dword ptr [eax]
    x86::Float fpu3 = x86::Float(app->getMemory<float>(cpu.eax));
    // 004dd993  d84a04                 -fmul dword ptr [edx + 4]
    x86::Float fpu4 = cpu.fpu.mul(fpu3, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(4) /* 0x4 */)));
    // 004dd996  d900                   -fld dword ptr [eax]
    x86::Float fpu5 = x86::Float(app->getMemory<float>(cpu.eax));
    // 004dd998  d84a08                 -fmul dword ptr [edx + 8]
    x86::Float fpu6 = cpu.fpu.mul(fpu5, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(8) /* 0x8 */)));
    // 004dd99b  d9ca                   -fxch st(2)
    
    // 004dd99d  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu7 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 004dd9a0  d84a0c                 -fmul dword ptr [edx + 0xc]
    x86::Float fpu8 = cpu.fpu.mul(fpu7, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(12) /* 0xc */)));
    // 004dd9a3  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu9 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 004dd9a6  d84a10                 -fmul dword ptr [edx + 0x10]
    x86::Float fpu10 = cpu.fpu.mul(fpu9, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(16) /* 0x10 */)));
    // 004dd9a9  d94004                 -fld dword ptr [eax + 4]
    x86::Float fpu11 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(4) /* 0x4 */));
    // 004dd9ac  d84a14                 -fmul dword ptr [edx + 0x14]
    x86::Float fpu12 = cpu.fpu.mul(fpu11, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(20) /* 0x14 */)));
    // 004dd9af  d9ca                   -fxch st(2)
    
    // 004dd9b1  dec3                   -faddp st(3)
    x86::Float fpu13 = cpu.fpu.add(fpu2, fpu8);
    // 004dd9b3  dec3                   -faddp st(3)
    x86::Float fpu14 = cpu.fpu.add(fpu4, fpu10);
    // 004dd9b5  dec3                   -faddp st(3)
    x86::Float fpu15 = cpu.fpu.add(fpu6, fpu12);
    // 004dd9b7  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu16 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 004dd9ba  d84a18                 -fmul dword ptr [edx + 0x18]
    x86::Float fpu17 = cpu.fpu.mul(fpu16, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(24) /* 0x18 */)));
    // 004dd9bd  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu18 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 004dd9c0  d84a1c                 -fmul dword ptr [edx + 0x1c]
    x86::Float fpu19 = cpu.fpu.mul(fpu18, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(28) /* 0x1c */)));
    // 004dd9c3  d94008                 -fld dword ptr [eax + 8]
    x86::Float fpu20 = x86::Float(app->getMemory<float>(cpu.eax + x86::reg32(8) /* 0x8 */));
    // 004dd9c6  d84a20                 -fmul dword ptr [edx + 0x20]
    x86::Float fpu21 = cpu.fpu.mul(fpu20, x86::Float(app->getMemory<float>(cpu.edx + x86::reg32(32) /* 0x20 */)));
    // 004dd9c9  d9ca                   -fxch st(2)
    
    // 004dd9cb  dec3                   -faddp st(3)
    x86::Float fpu22 = cpu.fpu.add(fpu13, fpu17);
    // 004dd9cd  dec3                   -faddp st(3)
    x86::Float fpu23 = cpu.fpu.add(fpu14, fpu19);
    // 004dd9cf  dec3                   -faddp st(3)
    x86::Float fpu24 = cpu.fpu.add(fpu15, fpu21);
    // 004dd9d1  8d400c                 -lea eax, [eax + 0xc]
    cpu.eax = x86::reg32(cpu.eax + x86::reg32(12) /* 0xc */);
    // 004dd9d4  d91b                   -fstp dword ptr [ebx]
    app->getMemory<float>(cpu.ebx) = float(fpu22);
    // 004dd9d6  d95b04                 -fstp dword ptr [ebx + 4]
    app->getMemory<float>(cpu.ebx + x86::reg32(4) /* 0x4 */) = float(fpu23);
    // 004dd9d9  d95b08                 -fstp dword ptr [ebx + 8]
    app->getMemory<float>(cpu.ebx + x86::reg32(8) /* 0x8 */) = float(fpu24);
    // 004dd9dc  d945cc                 -fld dword ptr [ebp - 0x34]
    x86::Float fpu25 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-52) /* -0x34 */));
    // 004dd9df  d84638                 -fadd dword ptr [esi + 0x38]
    x86::Float fpu26 = cpu.fpu.add(fpu25, x86::Float(app->getMemory<float>(cpu.esi + x86::reg32(56) /* 0x38 */)));
    // 004dd9e2  d945d0                 -fld dword ptr [ebp - 0x30]
    x86::Float fpu27 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-48) /* -0x30 */));
    // 004dd9e5  d9c9                   -fxch st(1)
    
    // 004dd9e7  d95dcc                 -fstp dword ptr [ebp - 0x34]
    app->getMemory<float>(cpu.ebp + x86::reg32(-52) /* -0x34 */) = float(fpu26);
    // 004dd9ea  d8463c                 -fadd dword ptr [esi + 0x3c]
    x86::Float fpu28 = cpu.fpu.add(fpu27, x86::Float(app->getMemory<float>(cpu.esi + x86::reg32(60) /* 0x3c */)));
    // 004dd9ed  d945d4                 -fld dword ptr [ebp - 0x2c]
    x86::Float fpu29 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-44) /* -0x2c */));
    // 004dd9f0  d9c9                   -fxch st(1)
    
    // 004dd9f2  d95dd0                 -fstp dword ptr [ebp - 0x30]
    app->getMemory<float>(cpu.ebp + x86::reg32(-48) /* -0x30 */) = float(fpu28);
    // 004dd9f5  d84640                 -fadd dword ptr [esi + 0x40]
    x86::Float fpu30 = cpu.fpu.add(fpu29, x86::Float(app->getMemory<float>(cpu.esi + x86::reg32(64) /* 0x40 */)));
    // 004dd9f8  d95dd4                 -fstp dword ptr [ebp - 0x2c]
    app->getMemory<float>(cpu.ebp + x86::reg32(-44) /* -0x2c */) = float(fpu30);
    // 004dd9fb  8b5dd4                 -mov ebx, dword ptr [ebp - 0x2c]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-44) /* -0x2c */);
    // 004dd9fe  f7c3ffffff7f           +test ebx, 0x7fffffff
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & 2147483647 /*0x7fffffff*/));
    }
    // 004dda04  740c                   -je 0x4dda12
    if (cpu.flags.zf)
    {
        goto L_0x004dda12;
    }
    // 004dda06  d945d4                 +fld dword ptr [ebp - 0x2c]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu31 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-44) /* -0x2c */));
    // 004dda09  d9e8                   +fld1 
    x86::Float fpu32 = 1.0;
    // 004dda0b  def1                   +fdivrp st(1)
    x86::Float fpu33 = cpu.fpu.div(fpu32, x86::Float(fpu31));
    // 004dda0d  dd5de0                 +fstp qword ptr [ebp - 0x20]
    app->getMemory<double>(cpu.ebp + x86::reg32(-32) /* -0x20 */) = double(fpu33);
    }
    // 004dda10  eb0d                   -jmp 0x4dda1f
    goto L_0x004dda1f;
L_0x004dda12:
    // 004dda12  31f6                   -xor esi, esi
    cpu.esi ^= x86::reg32(x86::sreg32(cpu.esi));
    // 004dda14  b8e0ffef40             -mov eax, 0x40efffe0
    cpu.eax = 1089470432 /*0x40efffe0*/;
    // 004dda19  8975e0                 -mov dword ptr [ebp - 0x20], esi
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-32) /* -0x20 */) = cpu.esi;
    // 004dda1c  8945e4                 -mov dword ptr [ebp - 0x1c], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-28) /* -0x1c */) = cpu.eax;
L_0x004dda1f:
    // 004dda1f  a17ca28c00             -mov eax, dword ptr [0x8ca27c]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(9216636) /* 0x8ca27c */);
    // 004dda24  dd45e0                 -fld qword ptr [ebp - 0x20]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu34 = x86::Float(app->getMemory<double>(cpu.ebp + x86::reg32(-32) /* -0x20 */));
    // 004dda27  c1f802                 -sar eax, 2
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (2 /*0x2*/ % 32));
    // 004dda2a  d95df4                 -fstp dword ptr [ebp - 0xc]
    app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */) = float(fpu34);
    // 004dda2d  83f801                 +cmp eax, 1
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
    }
    // 004dda30  7e04                   -jle 0x4dda36
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004dda36;
    }
    // 004dda32  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 004dda34  eb05                   -jmp 0x4dda3b
    goto L_0x004dda3b;
L_0x004dda36:
    // 004dda36  bb01000000             -mov ebx, 1
    cpu.ebx = 1 /*0x1*/;
L_0x004dda3b:
    // 004dda3b  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 004dda3d  e846330000             -call 0x4e0d88
    cpu.esp -= 4;
    nfs3hp::port::eaRandom(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dda42  f7f3                   -div ebx
    {
        x86::reg64 tmp = cpu.edx_eax;
        x86::reg32 d = cpu.ebx;
        cpu.edx_eax /= d;
        cpu.edx = tmp % d;
    }
    // 004dda44  d945f4                 -fld dword ptr [ebp - 0xc]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu35 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-12) /* -0xc */));
    // 004dda47  d945cc                 -fld dword ptr [ebp - 0x34]
    x86::Float fpu36 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-52) /* -0x34 */));
    // 004dda4a  d8c9                   -fmul st(1)
    x86::Float fpu37 = cpu.fpu.mul(fpu36, x86::Float(fpu35));
    // 004dda4c  d945d0                 -fld dword ptr [ebp - 0x30]
    x86::Float fpu38 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-48) /* -0x30 */));
    // 004dda4f  8d34bd00000000         -lea esi, [edi*4]
    cpu.esi = x86::reg32(cpu.edi * 4);
    // 004dda56  deca                   -fmulp st(2)
    x86::Float fpu39 = cpu.fpu.mul(fpu35, fpu38);
    // 004dda58  29fe                   -sub esi, edi
    (cpu.esi) -= x86::reg32(x86::sreg32(cpu.edi));
    // 004dda5a  c1e603                 -shl esi, 3
    cpu.esi <<= 3 /*0x3*/ % 32;
    // 004dda5d  01fe                   -add esi, edi
    (cpu.esi) += x86::reg32(x86::sreg32(cpu.edi));
    // 004dda5f  8d048d00000000         -lea eax, [ecx*4]
    cpu.eax = x86::reg32(cpu.ecx * 4);
    // 004dda66  8b1d7ca28c00           -mov ebx, dword ptr [0x8ca27c]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(9216636) /* 0x8ca27c */);
    // 004dda6c  01c8                   -add eax, ecx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.ecx));
    // 004dda6e  c1e604                 -shl esi, 4
    cpu.esi <<= 4 /*0x4*/ % 32;
    // 004dda71  29d3                   +sub ebx, edx
    {
        x86::reg32& tmp1 = cpu.ebx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.edx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 004dda73  d99c86c0088c00         +fstp dword ptr [esi + eax*4 + 0x8c08c0]
    app->getMemory<float>(cpu.esi + x86::reg32(9177280) /* 0x8c08c0 */ + cpu.eax * 4) = float(fpu37);
    // 004dda7a  d99c86c4088c00         +fstp dword ptr [esi + eax*4 + 0x8c08c4]
    app->getMemory<float>(cpu.esi + x86::reg32(9177284) /* 0x8c08c4 */ + cpu.eax * 4) = float(fpu39);
    // 004dda81  899c86c8088c00         -mov dword ptr [esi + eax*4 + 0x8c08c8], ebx
    app->getMemory<x86::reg32>(cpu.esi + x86::reg32(9177288) /* 0x8c08c8 */ + cpu.eax * 4) = cpu.ebx;
    }
    // 004dda88  e8a3d70000             -call 0x4eb230
    cpu.esp -= 4;
    nfs3hp::ea::randomFraction(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dda8d  d80d80a28c00           +fmul dword ptr [0x8ca280]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu40 = cpu.fpu.st(0);
    x86::Float fpu41 = cpu.fpu.mul(fpu40, x86::Float(app->getMemory<float>(x86::reg32(9216640) /* 0x8ca280 */)));
    // 004dda93  d90580a28c00           +fld dword ptr [0x8ca280]
    x86::Float fpu42 = x86::Float(app->getMemory<float>(x86::reg32(9216640) /* 0x8ca280 */));
    // 004dda99  dc0dd4975400           +fmul qword ptr [0x5497d4]
    x86::Float fpu43 = cpu.fpu.mul(fpu42, x86::Float(app->getMemory<double>(x86::reg32(5543892) /* 0x5497d4 */)));
    // 004dda9f  d9c9                   +fxch st(1)
    
    // 004ddaa1  d955fc                 +fst dword ptr [ebp - 4]
    app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = float(fpu41);
    // 004ddaa4  d9c9                   +fxch st(1)
    
    // 004ddaa6  dd5dd8                 +fstp qword ptr [ebp - 0x28]
    app->getMemory<double>(cpu.ebp + x86::reg32(-40) /* -0x28 */) = double(fpu43);
    // 004ddaa9  dc5dd8                 +fcomp qword ptr [ebp - 0x28]
    cpu.fpu.compare(fpu41, x86::Float(app->getMemory<double>(cpu.ebp + x86::reg32(-40) /* -0x28 */)));
    // 004ddaac  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 004ddaae  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    cpu.fpu.count -= 1;
    }
    // 004ddaaf  730e                   -jae 0x4ddabf
    if (!cpu.flags.cf)
    {
        goto L_0x004ddabf;
    }
    // 004ddab1  8b45d8                 -mov eax, dword ptr [ebp - 0x28]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-40) /* -0x28 */);
    // 004ddab4  8945e8                 -mov dword ptr [ebp - 0x18], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-24) /* -0x18 */) = cpu.eax;
    // 004ddab7  8b45dc                 -mov eax, dword ptr [ebp - 0x24]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-36) /* -0x24 */);
    // 004ddaba  8945ec                 -mov dword ptr [ebp - 0x14], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */) = cpu.eax;
    // 004ddabd  eb21                   -jmp 0x4ddae0
    goto L_0x004ddae0;
L_0x004ddabf:
    // 004ddabf  d945fc                 +fld dword ptr [ebp - 4]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu44 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-4) /* -0x4 */));
    // 004ddac2  d81d80a28c00           +fcomp dword ptr [0x8ca280]
    cpu.fpu.compare(fpu44, x86::Float(app->getMemory<float>(x86::reg32(9216640) /* 0x8ca280 */)));
    // 004ddac8  dfe0                   -fnstsw ax
    cpu.ax = cpu.fpu.status.word;
    // 004ddaca  9e                     +sahf 
    cpu.flags.lo = 0x02 | (cpu.ah & 0xD7);
    }
    // 004ddacb  7607                   -jbe 0x4ddad4
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x004ddad4;
    }
    // 004ddacd  a180a28c00             -mov eax, dword ptr [0x8ca280]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(9216640) /* 0x8ca280 */);
    // 004ddad2  eb03                   -jmp 0x4ddad7
    goto L_0x004ddad7;
L_0x004ddad4:
    // 004ddad4  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
L_0x004ddad7:
    // 004ddad7  8945f8                 -mov dword ptr [ebp - 8], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.eax;
    // 004ddada  d945f8                 -fld dword ptr [ebp - 8]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu45 = x86::Float(app->getMemory<float>(cpu.ebp + x86::reg32(-8) /* -0x8 */));
    // 004ddadd  dd5de8                 -fstp qword ptr [ebp - 0x18]
    app->getMemory<double>(cpu.ebp + x86::reg32(-24) /* -0x18 */) = double(fpu45);
    }
L_0x004ddae0:
    // 004ddae0  8d04bd00000000         -lea eax, [edi*4]
    cpu.eax = x86::reg32(cpu.edi * 4);
    // 004ddae7  29f8                   -sub eax, edi
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edi));
    // 004ddae9  c1e003                 -shl eax, 3
    cpu.eax <<= 3 /*0x3*/ % 32;
    // 004ddaec  8d1407                 -lea edx, [edi + eax]
    cpu.edx = x86::reg32(cpu.edi + cpu.eax * 1);
    // 004ddaef  8d048d00000000         -lea eax, [ecx*4]
    cpu.eax = x86::reg32(cpu.ecx * 4);
    // 004ddaf6  01c8                   -add eax, ecx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.ecx));
    // 004ddaf8  c1e204                 -shl edx, 4
    cpu.edx <<= 4 /*0x4*/ % 32;
    // 004ddafb  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 004ddafe  dd45e8                 -fld qword ptr [ebp - 0x18]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu46 = x86::Float(app->getMemory<double>(cpu.ebp + x86::reg32(-24) /* -0x18 */));
    // 004ddb01  01c2                   +add edx, eax
    {
        x86::reg32& tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.eax));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 004ddb03  d95df0                 +fstp dword ptr [ebp - 0x10]
    app->getMemory<float>(cpu.ebp + x86::reg32(-16) /* -0x10 */) = float(fpu46);
    // 004ddb06  8b45f0                 -mov eax, dword ptr [ebp - 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 004ddb09  8982cc088c00           -mov dword ptr [edx + 0x8c08cc], eax
    app->getMemory<x86::reg32>(cpu.edx + x86::reg32(9177292) /* 0x8c08cc */) = cpu.eax;
    }
    // 004ddb0f  e81cd70000             -call 0x4eb230
    cpu.esp -= 4;
    nfs3hp::ea::randomFraction(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004ddb14  d99ad0088c00           +fstp dword ptr [edx + 0x8c08d0]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu47 = cpu.fpu.st(0);
    app->getMemory<float>(cpu.edx + x86::reg32(9177296) /* 0x8c08d0 */) = float(fpu47);
    // 004ddb1a  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 004ddb1f  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004ddb21  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ddb22  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ddb23  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ddb24  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ddb25  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ddb26  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    cpu.fpu.count -= 1;
    }
    // 004ddb27  c20c00                 -ret 0xc
    cpu.esp += 4+12 /*0xc*/;
    return;
L_0x004ddb2a:
    // 004ddb2a  41                     +inc ecx
    {
        x86::reg32& tmp = cpu.ecx;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 004ddb2b  e920feffff             -jmp 0x4dd950
    goto L_0x004dd950;
L_0x004ddb30:
    // 004ddb30  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 004ddb32  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004ddb34  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ddb35  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ddb36  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ddb37  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ddb38  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ddb39  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004ddb3a  c20c00                 -ret 0xc
    cpu.esp += 4+12 /*0xc*/;
    return;
}

/* sub_4ddb40: native, nfs3hp::render::sparks */

/* sub_4de070: native, nfs3hp::render::smoke */

/* sub_4de700: native, nfs3hp::render::streaks */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x8d 0x40 0x00 */
void Application::sub_4dece0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004dece0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004dece1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004dece2  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004dece3  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004dece4  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004dece5  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004dece7  83ec14                 -sub esp, 0x14
    (cpu.esp) -= x86::reg32(x86::sreg32(20 /*0x14*/));
    // 004decea  89f1                   -mov ecx, esi
    cpu.ecx = cpu.esi;
    // 004decec  89c7                   -mov edi, eax
    cpu.edi = cpu.eax;
    // 004decee  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 004decf0  8d75f4                 -lea esi, [ebp - 0xc]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 004decf3  8955fc                 -mov dword ptr [ebp - 4], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.edx;
    // 004decf6  e875d1fdff             -call 0x4bbe70
    cpu.esp -= 4;
    sub_4bbe70(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004decfb  833f00                 +cmp dword ptr [edi], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.edi);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004decfe  7509                   -jne 0x4ded09
    if (!cpu.flags.zf)
    {
        goto L_0x004ded09;
    }
    // 004ded00  833d2ca28c0000         +cmp dword ptr [0x8ca22c], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(9216556) /* 0x8ca22c */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004ded07  750b                   -jne 0x4ded14
    if (!cpu.flags.zf)
    {
        goto L_0x004ded14;
    }
L_0x004ded09:
    // 004ded09  8d7dec                 -lea edi, [ebp - 0x14]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(-20) /* -0x14 */);
    // 004ded0c  8d75f4                 -lea esi, [ebp - 0xc]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 004ded0f  e9c3000000             -jmp 0x4dedd7
    goto L_0x004dedd7;
L_0x004ded14:
    // 004ded14  8b4704                 -mov eax, dword ptr [edi + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edi + x86::reg32(4) /* 0x4 */);
    // 004ded17  833c85f42f550000       +cmp dword ptr [eax*4 + 0x552ff4], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5582836) /* 0x552ff4 */ + cpu.eax * 4);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004ded1f  7407                   -je 0x4ded28
    if (cpu.flags.zf)
    {
        goto L_0x004ded28;
    }
    // 004ded21  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 004ded23  e808e5ffff             -call 0x4dd230
    cpu.esp -= 4;
    sub_4dd230(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x004ded28:
    // 004ded28  8b4704                 -mov eax, dword ptr [edi + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edi + x86::reg32(4) /* 0x4 */);
    // 004ded2b  e8703ef4ff             -call 0x422ba0
    cpu.esp -= 4;
    nfs3hp::carstate::cameraCar(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004ded30  8b401c                 -mov eax, dword ptr [eax + 0x1c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(28) /* 0x1c */);
    // 004ded33  e898e6ffff             -call 0x4dd3d0
    cpu.esp -= 4;
    sub_4dd3d0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004ded38  e8f3e5ffff             -call 0x4dd330
    cpu.esp -= 4;
    sub_4dd330(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004ded3d  8b1d30bc6f00           -mov ebx, dword ptr [0x6fbc30]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(7322672) /* 0x6fbc30 */);
    // 004ded43  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004ded45  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 004ded47  83fb01                 +cmp ebx, 1
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
    // 004ded4a  7509                   -jne 0x4ded55
    if (!cpu.flags.zf)
    {
        goto L_0x004ded55;
    }
    // 004ded4c  c1fa1f                 -sar edx, 0x1f
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (31 /*0x1f*/ % 32));
    // 004ded4f  2bc2                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 004ded51  d1f8                   -sar eax, 1
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (1 /*0x1*/ % 32));
    // 004ded53  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
L_0x004ded55:
    // 004ded55  833d30bc6f0002         +cmp dword ptr [0x6fbc30], 2
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(7322672) /* 0x6fbc30 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(2 /*0x2*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004ded5c  7511                   -jne 0x4ded6f
    if (!cpu.flags.zf)
    {
        goto L_0x004ded6f;
    }
    // 004ded5e  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 004ded60  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004ded62  c1fa1f                 -sar edx, 0x1f
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (31 /*0x1f*/ % 32));
    // 004ded65  c1e202                 +shl edx, 2
    {
        x86::reg8 tmp = 2 /*0x2*/ % 32;
        x86::reg32& op = cpu.edx;
        if (tmp)
        {
            cpu.flags.cf = 1 & (op >> (32 - tmp));
            cpu.set_szp((op <<= tmp));
            if (tmp == 1) cpu.flags.of = (cpu.flags.cf != (1 & (op >> (32 - 1))));
        }
    }
    // 004ded68  1bc2                   -sbb eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx) + cpu.flags.cf);
    // 004ded6a  c1f802                 -sar eax, 2
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (2 /*0x2*/ % 32));
    // 004ded6d  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
L_0x004ded6f:
    // 004ded6f  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 004ded71  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 004ded73  e868e8ffff             -call 0x4dd5e0
    cpu.esp -= 4;
    sub_4dd5e0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004ded78  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 004ded7a  e821d0ffff             -call 0x4dbda0
    cpu.esp -= 4;
    sub_4dbda0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004ded7f  a12ca28c00             -mov eax, dword ptr [0x8ca22c]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(9216556) /* 0x8ca22c */);
    // 004ded84  83f801                 +cmp eax, 1
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
    // 004ded87  7241                   -jb 0x4dedca
    if (cpu.flags.cf)
    {
        goto L_0x004dedca;
    }
    // 004ded89  7607                   -jbe 0x4ded92
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x004ded92;
    }
    // 004ded8b  83f802                 +cmp eax, 2
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
    // 004ded8e  742a                   -je 0x4dedba
    if (cpu.flags.zf)
    {
        goto L_0x004dedba;
    }
    // 004ded90  eb38                   -jmp 0x4dedca
    goto L_0x004dedca;
L_0x004ded92:
    // 004ded92  8b4704                 -mov eax, dword ptr [edi + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edi + x86::reg32(4) /* 0x4 */);
    // 004ded95  e876e7ffff             -call 0x4dd510
    cpu.esp -= 4;
    sub_4dd510(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004ded9a  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 004ded9c  740f                   -je 0x4dedad
    if (cpu.flags.zf)
    {
        goto L_0x004dedad;
    }
    // 004ded9e  8d5dfc                 -lea ebx, [ebp - 4]
    cpu.ebx = x86::reg32(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004deda1  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 004deda3  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 004deda5  8d75f4                 -lea esi, [ebp - 0xc]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 004deda8  e853f9ffff             -call 0x4de700
    cpu.esp -= 4;
    nfs3hp::render::streaks(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x004dedad:
    // 004dedad  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004dedb0  8b5704                 -mov edx, dword ptr [edi + 4]
    cpu.edx = app->getMemory<x86::reg32>(cpu.edi + x86::reg32(4) /* 0x4 */);
    // 004dedb3  e808e7ffff             -call 0x4dd4c0
    cpu.esp -= 4;
    sub_4dd4c0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dedb8  eb10                   -jmp 0x4dedca
    goto L_0x004dedca;
L_0x004dedba:
    // 004dedba  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 004dedbc  740c                   -je 0x4dedca
    if (cpu.flags.zf)
    {
        goto L_0x004dedca;
    }
    // 004dedbe  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 004dedc0  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 004dedc2  8d75f4                 -lea esi, [ebp - 0xc]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 004dedc5  e8a6f2ffff             -call 0x4de070
    cpu.esp -= 4;
    nfs3hp::render::smoke(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x004dedca:
    // 004dedca  8d75f4                 -lea esi, [ebp - 0xc]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 004dedcd  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 004dedcf  8d7dec                 -lea edi, [ebp - 0x14]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(-20) /* -0x14 */);
    // 004dedd2  e809d0ffff             -call 0x4dbde0
    cpu.esp -= 4;
    sub_4dbde0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x004dedd7:
    // 004dedd7  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004dedd8  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004dedd9  8d75ec                 -lea esi, [ebp - 0x14]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(-20) /* -0x14 */);
    // 004deddc  89cf                   -mov edi, ecx
    cpu.edi = cpu.ecx;
    // 004dedde  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004deddf  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004dede0  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004dede2  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004dede4  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dede5  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dede6  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dede7  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dede8  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dede9  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 */
void Application::sub_4dedf0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004dedf0  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004dedf1  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004dedf2  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004dedf3  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004dedf5  83ec08                 -sub esp, 8
    (cpu.esp) -= x86::reg32(x86::sreg32(8 /*0x8*/));
    // 004dedf8  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 004dedfa  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 004dedfc  e81fd1fdff             -call 0x4bbf20
    cpu.esp -= 4;
    sub_4bbf20(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dee01  833e00                 +cmp dword ptr [esi], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.esi);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004dee04  7509                   -jne 0x4dee0f
    if (!cpu.flags.zf)
    {
        goto L_0x004dee0f;
    }
    // 004dee06  833d2ca28c0000         +cmp dword ptr [0x8ca22c], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(9216556) /* 0x8ca22c */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004dee0d  7505                   -jne 0x4dee14
    if (!cpu.flags.zf)
    {
        goto L_0x004dee14;
    }
L_0x004dee0f:
    // 004dee0f  8d75f8                 -lea esi, [ebp - 8]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004dee12  eb49                   -jmp 0x4dee5d
    goto L_0x004dee5d;
L_0x004dee14:
    // 004dee14  833d30bc6f0002         +cmp dword ptr [0x6fbc30], 2
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(7322672) /* 0x6fbc30 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(2 /*0x2*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004dee1b  7517                   -jne 0x4dee34
    if (!cpu.flags.zf)
    {
        goto L_0x004dee34;
    }
    // 004dee1d  8d75f8                 -lea esi, [ebp - 8]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004dee20  e89bd1fdff             -call 0x4bbfc0
    cpu.esp -= 4;
    sub_4bbfc0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dee25  8d75f8                 -lea esi, [ebp - 8]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004dee28  89d7                   -mov edi, edx
    cpu.edi = cpu.edx;
    // 004dee2a  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004dee2b  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004dee2c  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004dee2e  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004dee30  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dee31  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dee32  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dee33  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004dee34:
    // 004dee34  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004dee36  e865cfffff             -call 0x4dbda0
    cpu.esp -= 4;
    sub_4dbda0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dee3b  a12ca28c00             -mov eax, dword ptr [0x8ca22c]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(9216556) /* 0x8ca22c */);
    // 004dee40  83f801                 +cmp eax, 1
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
    // 004dee43  720e                   -jb 0x4dee53
    if (cpu.flags.cf)
    {
        goto L_0x004dee53;
    }
    // 004dee45  7605                   -jbe 0x4dee4c
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x004dee4c;
    }
    // 004dee47  83f802                 +cmp eax, 2
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
    // 004dee4a  7507                   -jne 0x4dee53
    if (!cpu.flags.zf)
    {
        goto L_0x004dee53;
    }
L_0x004dee4c:
    // 004dee4c  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004dee4e  e8edecffff             -call 0x4ddb40
    cpu.esp -= 4;
    nfs3hp::render::sparks(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x004dee53:
    // 004dee53  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004dee55  8d75f8                 -lea esi, [ebp - 8]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004dee58  e883cfffff             -call 0x4dbde0
    cpu.esp -= 4;
    sub_4dbde0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x004dee5d:
    // 004dee5d  e85ed1fdff             -call 0x4bbfc0
    cpu.esp -= 4;
    sub_4bbfc0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dee62  8d75f8                 -lea esi, [ebp - 8]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004dee65  89d7                   -mov edi, edx
    cpu.edi = cpu.edx;
    // 004dee67  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004dee68  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004dee69  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004dee6b  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004dee6d  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dee6e  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dee6f  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004dee70  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 */
void Application::sub_4dee80(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004dee80  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004dee81  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004dee82  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004dee83  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004dee84  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004dee85  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004dee86  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004dee88  81ecd0000000           -sub esp, 0xd0
    (cpu.esp) -= x86::reg32(x86::sreg32(208 /*0xd0*/));
    // 004dee8e  81ed82000000           -sub ebp, 0x82
    (cpu.ebp) -= x86::reg32(x86::sreg32(130 /*0x82*/));
    // 004dee94  89457e                 -mov dword ptr [ebp + 0x7e], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */) = cpu.eax;
    // 004dee97  e8e4cb0000             -call 0x4eba80
    cpu.esp -= 4;
    sub_4eba80(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004dee9c  8b15c0a28c00           -mov edx, dword ptr [0x8ca2c0]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(9216704) /* 0x8ca2c0 */);
    // 004deea2  31f6                   -xor esi, esi
    cpu.esi ^= x86::reg32(x86::sreg32(cpu.esi));
    // 004deea4  39d0                   +cmp eax, edx
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
    // 004deea6  0f848c000000           -je 0x4def38
    if (cpu.flags.zf)
    {
        goto L_0x004def38;
    }
    // 004deeac  e8cfcb0000             -call 0x4eba80
    cpu.esp -= 4;
    sub_4eba80(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004deeb1  b96c000000             -mov ecx, 0x6c
    cpu.ecx = 108 /*0x6c*/;
    // 004deeb6  bb07100000             -mov ebx, 0x1007
    cpu.ebx = 4103 /*0x1007*/;
    // 004deebb  a3c0a28c00             -mov dword ptr [0x8ca2c0], eax
    app->getMemory<x86::reg32>(x86::reg32(9216704) /* 0x8ca2c0 */) = cpu.eax;
    // 004deec0  e8cbcb0000             -call 0x4eba90
    cpu.esp -= 4;
    sub_4eba90(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004deec5  8b35d4a28c00           -mov esi, dword ptr [0x8ca2d4]
    cpu.esi = app->getMemory<x86::reg32>(x86::reg32(9216724) /* 0x8ca2d4 */);
    // 004deecb  894db2                 -mov dword ptr [ebp - 0x4e], ecx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-78) /* -0x4e */) = cpu.ecx;
    // 004deece  895db6                 -mov dword ptr [ebp - 0x4a], ebx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-74) /* -0x4a */) = cpu.ebx;
    // 004deed1  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 004deed3  7509                   -jne 0x4deede
    if (!cpu.flags.zf)
    {
        goto L_0x004deede;
    }
    // 004deed5  c7451a40400000         -mov dword ptr [ebp + 0x1a], 0x4040
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(26) /* 0x1a */) = 16448 /*0x4040*/;
    // 004deedc  eb07                   -jmp 0x4deee5
    goto L_0x004deee5;
L_0x004deede:
    // 004deede  c7451a80400000         -mov dword ptr [ebp + 0x1a], 0x4080
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(26) /* 0x1a */) = 16512 /*0x4080*/;
L_0x004deee5:
    // 004deee5  b920000000             -mov ecx, 0x20
    cpu.ecx = 32 /*0x20*/;
    // 004deeea  bb04000000             -mov ebx, 4
    cpu.ebx = 4 /*0x4*/;
    // 004deeef  6a00                   -push 0
    app->getMemory<x86::reg32>(cpu.esp-4) = 0 /*0x0*/;
    cpu.esp -= 4;
    // 004deef1  be59555932             -mov esi, 0x32595559
    cpu.esi = 844715353 /*0x32595559*/;
    // 004deef6  8b15d0a28c00           -mov edx, dword ptr [0x8ca2d0]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(9216720) /* 0x8ca2d0 */);
    // 004deefc  68c8a28c00             -push 0x8ca2c8
    app->getMemory<x86::reg32>(cpu.esp-4) = 9216712 /*0x8ca2c8*/;
    cpu.esp -= 4;
    // 004def01  8955be                 -mov dword ptr [ebp - 0x42], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-66) /* -0x42 */) = cpu.edx;
    // 004def04  894dfa                 -mov dword ptr [ebp - 6], ecx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-6) /* -0x6 */) = cpu.ecx;
    // 004def07  8b15c4a28c00           -mov edx, dword ptr [0x8ca2c4]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(9216708) /* 0x8ca2c4 */);
    // 004def0d  895dfe                 -mov dword ptr [ebp - 2], ebx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-2) /* -0x2 */) = cpu.ebx;
    // 004def10  8955ba                 -mov dword ptr [ebp - 0x46], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-70) /* -0x46 */) = cpu.edx;
    // 004def13  8d55b2                 -lea edx, [ebp - 0x4e]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-78) /* -0x4e */);
    // 004def16  897502                 -mov dword ptr [ebp + 2], esi
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(2) /* 0x2 */) = cpu.esi;
    // 004def19  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004def1a  8b08                   -mov ecx, dword ptr [eax]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax);
    // 004def1c  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004def1d  ff5118                 -call dword ptr [ecx + 0x18]
    cpu.ip = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(24) /* 0x18 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004def20  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004def22  740f                   -je 0x4def33
    if (cpu.flags.zf)
    {
        goto L_0x004def33;
    }
L_0x004def24:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004def24  c705d4a28c0002000000   -mov dword ptr [0x8ca2d4], 2
    app->getMemory<x86::reg32>(x86::reg32(9216724) /* 0x8ca2d4 */) = 2 /*0x2*/;
    // 004def2e  e9a5020000             -jmp 0x4df1d8
    goto L_0x004df1d8;
L_0x004def33:
    // 004def33  be01000000             -mov esi, 1
    cpu.esi = 1 /*0x1*/;
L_0x004def38:
    // 004def38  e8e3bd0000             -call 0x4ead20
    cpu.esp -= 4;
    sub_4ead20(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004def3d  833dd4a28c0001         +cmp dword ptr [0x8ca2d4], 1
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(9216724) /* 0x8ca2d4 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1 /*0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004def44  7561                   -jne 0x4defa7
    if (!cpu.flags.zf)
    {
        goto L_0x004defa7;
    }
    // 004def46  8b15d8a28c00           -mov edx, dword ptr [0x8ca2d8]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(9216728) /* 0x8ca2d8 */);
    // 004def4c  a17c715600             -mov eax, dword ptr [0x56717c]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5665148) /* 0x56717c */);
    // 004def51  39d0                   +cmp eax, edx
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
    // 004def53  7452                   -je 0x4defa7
    if (cpu.flags.zf)
    {
        goto L_0x004defa7;
    }
    // 004def55  8b0dcca28c00           -mov ecx, dword ptr [0x8ca2cc]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(9216716) /* 0x8ca2cc */);
    // 004def5b  a3d8a28c00             -mov dword ptr [0x8ca2d8], eax
    app->getMemory<x86::reg32>(x86::reg32(9216728) /* 0x8ca2d8 */) = cpu.eax;
    // 004def60  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    // 004def62  7507                   -jne 0x4def6b
    if (!cpu.flags.zf)
    {
        goto L_0x004def6b;
    }
    // 004def64  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 004def69  eb05                   -jmp 0x4def70
    goto L_0x004def70;
L_0x004def6b:
    // 004def6b  b802000000             -mov eax, 2
    cpu.eax = 2 /*0x2*/;
L_0x004def70:
    // 004def70  8b0dc4a28c00           -mov ecx, dword ptr [0x8ca2c4]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(9216708) /* 0x8ca2c4 */);
    // 004def76  0fafc8                 -imul ecx, eax
    cpu.ecx = x86::reg32(x86::sreg64(x86::sreg32(cpu.ecx)) * x86::sreg64(x86::sreg32(cpu.eax)));
    // 004def79  0faf05d0a28c00         -imul eax, dword ptr [0x8ca2d0]
    cpu.eax = x86::reg32(x86::sreg64(x86::sreg32(cpu.eax)) * x86::sreg64(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(9216720) /* 0x8ca2d0 */))));
    // 004def80  8b1ddca28c00           -mov ebx, dword ptr [0x8ca2dc]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(9216732) /* 0x8ca2dc */);
    // 004def86  6a01                   -push 1
    app->getMemory<x86::reg32>(cpu.esp-4) = 1 /*0x1*/;
    cpu.esp -= 4;
    // 004def88  01d9                   -add ecx, ebx
    (cpu.ecx) += x86::reg32(x86::sreg32(cpu.ebx));
    // 004def8a  8b1de0a28c00           -mov ebx, dword ptr [0x8ca2e0]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(9216736) /* 0x8ca2e0 */);
    // 004def90  8b15dca28c00           -mov edx, dword ptr [0x8ca2dc]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(9216732) /* 0x8ca2dc */);
    // 004def96  01c3                   -add ebx, eax
    (cpu.ebx) += x86::reg32(x86::sreg32(cpu.eax));
    // 004def98  a1e0a28c00             -mov eax, dword ptr [0x8ca2e0]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(9216736) /* 0x8ca2e0 */);
    // 004def9d  be01000000             -mov esi, 1
    cpu.esi = 1 /*0x1*/;
    // 004defa2  e899e50100             -call 0x4fd540
    cpu.esp -= 4;
    sub_4fd540(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x004defa7:
    // 004defa7  e8e4bd0000             -call 0x4ead90
    cpu.esp -= 4;
    sub_4ead90(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004defac  a1c8a28c00             -mov eax, dword ptr [0x8ca2c8]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(9216712) /* 0x8ca2c8 */);
    // 004defb1  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004defb2  8b10                   -mov edx, dword ptr [eax]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax);
    // 004defb4  ff5260                 -call dword ptr [edx + 0x60]
    cpu.ip = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(96) /* 0x60 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004defb7  3dc2017688             +cmp eax, 0x887601c2
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(2289435074 /*0x887601c2*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004defbc  752c                   -jne 0x4defea
    if (!cpu.flags.zf)
    {
        goto L_0x004defea;
    }
    // 004defbe  a1c8a28c00             -mov eax, dword ptr [0x8ca2c8]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(9216712) /* 0x8ca2c8 */);
    // 004defc3  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004defc4  8b10                   -mov edx, dword ptr [eax]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax);
    // 004defc6  ff526c                 -call dword ptr [edx + 0x6c]
    cpu.ip = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(108) /* 0x6c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004defc9  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004defcb  7418                   -je 0x4defe5
    if (cpu.flags.zf)
    {
        goto L_0x004defe5;
    }
    // 004defcd  3d4b027688             +cmp eax, 0x8876024b
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(2289435211 /*0x8876024b*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004defd2  0f854cffffff           -jne 0x4def24
    if (!cpu.flags.zf)
    {
        goto L_0x004def24;
    }
    // 004defd8  8da582000000           -lea esp, [ebp + 0x82]
    cpu.esp = x86::reg32(cpu.ebp + x86::reg32(130) /* 0x82 */);
    // 004defde  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004defdf  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004defe0  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004defe1  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004defe2  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004defe3  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004defe4  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004defe5:
    // 004defe5  be01000000             -mov esi, 1
    cpu.esi = 1 /*0x1*/;
L_0x004defea:
    // 004defea  6a00                   -push 0
    app->getMemory<x86::reg32>(cpu.esp-4) = 0 /*0x0*/;
    cpu.esp -= 4;
    // 004defec  6a00                   -push 0
    app->getMemory<x86::reg32>(cpu.esp-4) = 0 /*0x0*/;
    cpu.esp -= 4;
    // 004defee  8d4db2                 -lea ecx, [ebp - 0x4e]
    cpu.ecx = x86::reg32(cpu.ebp + x86::reg32(-78) /* -0x4e */);
    // 004deff1  b86c000000             -mov eax, 0x6c
    cpu.eax = 108 /*0x6c*/;
    // 004deff6  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004deff7  8945b2                 -mov dword ptr [ebp - 0x4e], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-78) /* -0x4e */) = cpu.eax;
    // 004deffa  a1c8a28c00             -mov eax, dword ptr [0x8ca2c8]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(9216712) /* 0x8ca2c8 */);
    // 004defff  6a00                   -push 0
    app->getMemory<x86::reg32>(cpu.esp-4) = 0 /*0x0*/;
    cpu.esp -= 4;
    // 004df001  8b10                   -mov edx, dword ptr [eax]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax);
    // 004df003  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004df004  ff5264                 -call dword ptr [edx + 0x64]
    cpu.ip = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(100) /* 0x64 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004df007  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004df009  742c                   -je 0x4df037
    if (cpu.flags.zf)
    {
        goto L_0x004df037;
    }
    // 004df00b  3dc2017688             +cmp eax, 0x887601c2
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(2289435074 /*0x887601c2*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004df010  750d                   -jne 0x4df01f
    if (!cpu.flags.zf)
    {
        goto L_0x004df01f;
    }
    // 004df012  8da582000000           -lea esp, [ebp + 0x82]
    cpu.esp = x86::reg32(cpu.ebp + x86::reg32(130) /* 0x82 */);
    // 004df018  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df019  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df01a  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df01b  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df01c  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df01d  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df01e  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004df01f:
    // 004df01f  3d1c027688             +cmp eax, 0x8876021c
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(2289435164 /*0x8876021c*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004df024  0f85fafeffff           -jne 0x4def24
    if (!cpu.flags.zf)
    {
        goto L_0x004def24;
    }
    // 004df02a  8da582000000           -lea esp, [ebp + 0x82]
    cpu.esp = x86::reg32(cpu.ebp + x86::reg32(130) /* 0x82 */);
    // 004df030  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df031  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df032  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df033  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df034  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df035  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df036  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004df037:
    // 004df037  a1d0a28c00             -mov eax, dword ptr [0x8ca2d0]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(9216720) /* 0x8ca2d0 */);
    // 004df03c  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004df03e  c1fa1f                 -sar edx, 0x1f
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (31 /*0x1f*/ % 32));
    // 004df041  2bc2                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 004df043  d1f8                   -sar eax, 1
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (1 /*0x1*/ % 32));
    // 004df045  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 004df047  89c7                   -mov edi, eax
    cpu.edi = cpu.eax;
L_0x004df049:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004df049  3b0dc4a28c00           +cmp ecx, dword ptr [0x8ca2c4]
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(9216708) /* 0x8ca2c4 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004df04f  7d22                   -jge 0x4df073
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004df073;
    }
    // 004df051  8b45c2                 -mov eax, dword ptr [ebp - 0x3e]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-62) /* -0x3e */);
    // 004df054  0fafc1                 -imul eax, ecx
    cpu.eax = x86::reg32(x86::sreg64(x86::sreg32(cpu.eax)) * x86::sreg64(x86::sreg32(cpu.ecx)));
    // 004df057  8b55d6                 -mov edx, dword ptr [ebp - 0x2a]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-42) /* -0x2a */);
    // 004df05a  01c2                   -add edx, eax
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.eax));
    // 004df05c  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004df05e  0fafc7                 -imul eax, edi
    cpu.eax = x86::reg32(x86::sreg64(x86::sreg32(cpu.eax)) * x86::sreg64(x86::sreg32(cpu.edi)));
    // 004df061  8b5d7e                 -mov ebx, dword ptr [ebp + 0x7e]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(126) /* 0x7e */);
    // 004df064  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 004df067  01d8                   +add eax, ebx
    {
        x86::reg32& tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ebx));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 004df069  89fb                   -mov ebx, edi
    cpu.ebx = cpu.edi;
    // 004df06b  41                     +inc ecx
    {
        x86::reg32& tmp = cpu.ecx;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 004df06c  e81be90100             -call 0x4fd98c
    cpu.esp -= 4;
    sub_4fd98c(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004df071  ebd6                   -jmp 0x4df049
    goto L_0x004df049;
L_0x004df073:
    // 004df073  6a00                   -push 0
    app->getMemory<x86::reg32>(cpu.esp-4) = 0 /*0x0*/;
    cpu.esp -= 4;
    // 004df075  a1c8a28c00             -mov eax, dword ptr [0x8ca2c8]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(9216712) /* 0x8ca2c8 */);
    // 004df07a  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004df07b  8b10                   -mov edx, dword ptr [eax]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax);
    // 004df07d  ff9280000000           -call dword ptr [edx + 0x80]
    cpu.ip = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(128) /* 0x80 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004df083  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004df085  7418                   -je 0x4df09f
    if (cpu.flags.zf)
    {
        goto L_0x004df09f;
    }
    // 004df087  3dc2017688             +cmp eax, 0x887601c2
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(2289435074 /*0x887601c2*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004df08c  0f8592feffff           -jne 0x4def24
    if (!cpu.flags.zf)
    {
        goto L_0x004def24;
    }
    // 004df092  8da582000000           -lea esp, [ebp + 0x82]
    cpu.esp = x86::reg32(cpu.ebp + x86::reg32(130) /* 0x82 */);
    // 004df098  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df099  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df09a  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df09b  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df09c  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df09d  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df09e  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004df09f:
    // 004df09f  833dd4a28c0000         +cmp dword ptr [0x8ca2d4], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(9216724) /* 0x8ca2d4 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004df0a6  7408                   -je 0x4df0b0
    if (cpu.flags.zf)
    {
        goto L_0x004df0b0;
    }
    // 004df0a8  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 004df0aa  0f8428010000           -je 0x4df1d8
    if (cpu.flags.zf)
    {
        goto L_0x004df1d8;
    }
L_0x004df0b0:
    // 004df0b0  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 004df0b2  89456a                 -mov dword ptr [ebp + 0x6a], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(106) /* 0x6a */) = cpu.eax;
    // 004df0b5  894566                 -mov dword ptr [ebp + 0x66], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(102) /* 0x66 */) = cpu.eax;
    // 004df0b8  a1d0a28c00             -mov eax, dword ptr [0x8ca2d0]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(9216720) /* 0x8ca2d0 */);
    // 004df0bd  48                     -dec eax
    (cpu.eax)--;
    // 004df0be  89456e                 -mov dword ptr [ebp + 0x6e], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(110) /* 0x6e */) = cpu.eax;
    // 004df0c1  a1c4a28c00             -mov eax, dword ptr [0x8ca2c4]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(9216708) /* 0x8ca2c4 */);
    // 004df0c6  48                     -dec eax
    (cpu.eax)--;
    // 004df0c7  8b0dcca28c00           -mov ecx, dword ptr [0x8ca2cc]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(9216716) /* 0x8ca2cc */);
    // 004df0cd  894572                 -mov dword ptr [ebp + 0x72], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(114) /* 0x72 */) = cpu.eax;
    // 004df0d0  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    // 004df0d2  7507                   -jne 0x4df0db
    if (!cpu.flags.zf)
    {
        goto L_0x004df0db;
    }
    // 004df0d4  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 004df0d9  eb05                   -jmp 0x4df0e0
    goto L_0x004df0e0;
L_0x004df0db:
    // 004df0db  b802000000             -mov eax, 2
    cpu.eax = 2 /*0x2*/;
L_0x004df0e0:
    // 004df0e0  8b15e0a28c00           -mov edx, dword ptr [0x8ca2e0]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(9216736) /* 0x8ca2e0 */);
    // 004df0e6  895556                 -mov dword ptr [ebp + 0x56], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(86) /* 0x56 */) = cpu.edx;
    // 004df0e9  8b15dca28c00           -mov edx, dword ptr [0x8ca2dc]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(9216732) /* 0x8ca2dc */);
    // 004df0ef  89555a                 -mov dword ptr [ebp + 0x5a], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(90) /* 0x5a */) = cpu.edx;
    // 004df0f2  8b15d0a28c00           -mov edx, dword ptr [0x8ca2d0]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(9216720) /* 0x8ca2d0 */);
    // 004df0f8  0fafd0                 -imul edx, eax
    cpu.edx = x86::reg32(x86::sreg64(x86::sreg32(cpu.edx)) * x86::sreg64(x86::sreg32(cpu.eax)));
    // 004df0fb  0faf05c4a28c00         -imul eax, dword ptr [0x8ca2c4]
    cpu.eax = x86::reg32(x86::sreg64(x86::sreg32(cpu.eax)) * x86::sreg64(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(9216708) /* 0x8ca2c4 */))));
    // 004df102  8b4d56                 -mov ecx, dword ptr [ebp + 0x56]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(86) /* 0x56 */);
    // 004df105  01d1                   -add ecx, edx
    (cpu.ecx) += x86::reg32(x86::sreg32(cpu.edx));
    // 004df107  8b555a                 -mov edx, dword ptr [ebp + 0x5a]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(90) /* 0x5a */);
    // 004df10a  01c2                   -add edx, eax
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.eax));
    // 004df10c  894d5e                 -mov dword ptr [ebp + 0x5e], ecx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(94) /* 0x5e */) = cpu.ecx;
    // 004df10f  895562                 -mov dword ptr [ebp + 0x62], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(98) /* 0x62 */) = cpu.edx;
    // 004df112  e859c90000             -call 0x4eba70
    cpu.esp -= 4;
    nfs3hp::AcquireWindow(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004df117  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 004df119  8d4556                 -lea eax, [ebp + 0x56]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(86) /* 0x56 */);
    // 004df11c  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004df11d  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004df11e  2eff1500475300         -call dword ptr cs:[0x534700]
    cpu.ip = app->getMemory<x86::reg32>(cpu.ecs + x86::reg32(5457664) /* 0x534700 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004df125  8d455e                 -lea eax, [ebp + 0x5e]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(94) /* 0x5e */);
    // 004df128  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004df129  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004df12a  2eff1500475300         -call dword ptr cs:[0x534700]
    cpu.ip = app->getMemory<x86::reg32>(cpu.ecs + x86::reg32(5457664) /* 0x534700 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004df131  e85abd0000             -call 0x4eae90
    cpu.esp -= 4;
    sub_4eae90(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004df136  8b3dd4a28c00           -mov edi, dword ptr [0x8ca2d4]
    cpu.edi = app->getMemory<x86::reg32>(x86::reg32(9216724) /* 0x8ca2d4 */);
    // 004df13c  8b5834                 -mov ebx, dword ptr [eax + 0x34]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(52) /* 0x34 */);
    // 004df13f  85ff                   +test edi, edi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edi & cpu.edi));
    // 004df141  7537                   -jne 0x4df17a
    if (!cpu.flags.zf)
    {
        goto L_0x004df17a;
    }
    // 004df143  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004df144  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004df145  8d5566                 -lea edx, [ebp + 0x66]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(102) /* 0x66 */);
    // 004df148  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004df149  8b15c8a28c00           -mov edx, dword ptr [0x8ca2c8]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(9216712) /* 0x8ca2c8 */);
    // 004df14f  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004df150  8d5556                 -lea edx, [ebp + 0x56]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(86) /* 0x56 */);
    // 004df153  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004df154  8b03                   -mov eax, dword ptr [ebx]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx);
    // 004df156  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004df157  ff5014                 -call dword ptr [eax + 0x14]
    cpu.ip = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004df15a  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004df15c  0f8476000000           -je 0x4df1d8
    if (cpu.flags.zf)
    {
        goto L_0x004df1d8;
    }
    // 004df162  3dc2017688             +cmp eax, 0x887601c2
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(2289435074 /*0x887601c2*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004df167  0f85b7fdffff           -jne 0x4def24
    if (!cpu.flags.zf)
    {
        goto L_0x004def24;
    }
    // 004df16d  8da582000000           -lea esp, [ebp + 0x82]
    cpu.esp = x86::reg32(cpu.ebp + x86::reg32(130) /* 0x82 */);
    // 004df173  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df174  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df175  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df176  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df177  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df178  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df179  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004df17a:
    // 004df17a  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 004df17c  745a                   -je 0x4df1d8
    if (cpu.flags.zf)
    {
        goto L_0x004df1d8;
    }
    // 004df17e  8d4576                 -lea eax, [ebp + 0x76]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(118) /* 0x76 */);
    // 004df181  be01000000             -mov esi, 1
    cpu.esi = 1 /*0x1*/;
    // 004df186  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004df187  897576                 -mov dword ptr [ebp + 0x76], esi
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(118) /* 0x76 */) = cpu.esi;
    // 004df18a  89757a                 -mov dword ptr [ebp + 0x7a], esi
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(122) /* 0x7a */) = cpu.esi;
    // 004df18d  6a04                   -push 4
    app->getMemory<x86::reg32>(cpu.esp-4) = 4 /*0x4*/;
    cpu.esp -= 4;
    // 004df18f  8b13                   -mov edx, dword ptr [ebx]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebx);
    // 004df191  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004df192  ff5274                 -call dword ptr [edx + 0x74]
    cpu.ip = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(116) /* 0x74 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004df195  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004df197  7534                   -jne 0x4df1cd
    if (!cpu.flags.zf)
    {
        goto L_0x004df1cd;
    }
    // 004df199  c7451e38000000         -mov dword ptr [ebp + 0x1e], 0x38
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(30) /* 0x1e */) = 56 /*0x38*/;
    // 004df1a0  8d551e                 -lea edx, [ebp + 0x1e]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(30) /* 0x1e */);
    // 004df1a3  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004df1a4  6800480800             -push 0x84800
    app->getMemory<x86::reg32>(cpu.esp-4) = 542720 /*0x84800*/;
    cpu.esp -= 4;
    // 004df1a9  8d5556                 -lea edx, [ebp + 0x56]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(86) /* 0x56 */);
    // 004df1ac  a1c8a28c00             -mov eax, dword ptr [0x8ca2c8]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(9216712) /* 0x8ca2c8 */);
    // 004df1b1  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004df1b2  89754e                 -mov dword ptr [ebp + 0x4e], esi
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(78) /* 0x4e */) = cpu.esi;
    // 004df1b5  89753e                 -mov dword ptr [ebp + 0x3e], esi
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(62) /* 0x3e */) = cpu.esi;
    // 004df1b8  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004df1b9  8d5566                 -lea edx, [ebp + 0x66]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(102) /* 0x66 */);
    // 004df1bc  897542                 -mov dword ptr [ebp + 0x42], esi
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(66) /* 0x42 */) = cpu.esi;
    // 004df1bf  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004df1c0  8b08                   -mov ecx, dword ptr [eax]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax);
    // 004df1c2  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004df1c3  ff9184000000           -call dword ptr [ecx + 0x84]
    cpu.ip = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(132) /* 0x84 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004df1c9  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004df1cb  740b                   -je 0x4df1d8
    if (cpu.flags.zf)
    {
        goto L_0x004df1d8;
    }
L_0x004df1cd:
    // 004df1cd  3dc2017688             +cmp eax, 0x887601c2
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(2289435074 /*0x887601c2*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004df1d2  0f854cfdffff           -jne 0x4def24
    if (!cpu.flags.zf)
    {
        goto L_0x004def24;
    }
L_0x004df1d8:
    // 004df1d8  8da582000000           -lea esp, [ebp + 0x82]
    cpu.esp = x86::reg32(cpu.ebp + x86::reg32(130) /* 0x82 */);
    // 004df1de  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df1df  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df1e0  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df1e1  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df1e2  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df1e3  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df1e4  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 0x8b 0xdb */
void Application::sub_4df1f0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004df1f0  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004df1f1  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004df1f2  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004df1f3  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004df1f5  81ecd8020000           -sub esp, 0x2d8
    (cpu.esp) -= x86::reg32(x86::sreg32(728 /*0x2d8*/));
    // 004df1fb  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 004df1fd  e80e010000             -call 0x4df310
    cpu.esp -= 4;
    sub_4df310(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004df202  8b4510                 -mov eax, dword ptr [ebp + 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(16) /* 0x10 */);
    // 004df205  8935e0a28c00           -mov dword ptr [0x8ca2e0], esi
    app->getMemory<x86::reg32>(x86::reg32(9216736) /* 0x8ca2e0 */) = cpu.esi;
    // 004df20b  8915dca28c00           -mov dword ptr [0x8ca2dc], edx
    app->getMemory<x86::reg32>(x86::reg32(9216732) /* 0x8ca2dc */) = cpu.edx;
    // 004df211  891dd0a28c00           -mov dword ptr [0x8ca2d0], ebx
    app->getMemory<x86::reg32>(x86::reg32(9216720) /* 0x8ca2d0 */) = cpu.ebx;
    // 004df217  890dc4a28c00           -mov dword ptr [0x8ca2c4], ecx
    app->getMemory<x86::reg32>(x86::reg32(9216708) /* 0x8ca2c4 */) = cpu.ecx;
    // 004df21d  31ff                   -xor edi, edi
    cpu.edi ^= x86::reg32(x86::sreg32(cpu.edi));
    // 004df21f  ba02000000             -mov edx, 2
    cpu.edx = 2 /*0x2*/;
    // 004df224  8b4d14                 -mov ecx, dword ptr [ebp + 0x14]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(20) /* 0x14 */);
    // 004df227  893dd8a28c00           -mov dword ptr [0x8ca2d8], edi
    app->getMemory<x86::reg32>(x86::reg32(9216728) /* 0x8ca2d8 */) = cpu.edi;
    // 004df22d  893dc0a28c00           -mov dword ptr [0x8ca2c0], edi
    app->getMemory<x86::reg32>(x86::reg32(9216704) /* 0x8ca2c0 */) = cpu.edi;
    // 004df233  a3cca28c00             -mov dword ptr [0x8ca2cc], eax
    app->getMemory<x86::reg32>(x86::reg32(9216716) /* 0x8ca2cc */) = cpu.eax;
    // 004df238  8915d4a28c00           -mov dword ptr [0x8ca2d4], edx
    app->getMemory<x86::reg32>(x86::reg32(9216724) /* 0x8ca2d4 */) = cpu.edx;
    // 004df23e  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    // 004df240  0f8561000000           -jne 0x4df2a7
    if (!cpu.flags.zf)
    {
        goto L_0x004df2a7;
    }
    // 004df246  e845c80000             -call 0x4eba90
    cpu.esp -= 4;
    sub_4eba90(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004df24b  bb6c010000             -mov ebx, 0x16c
    cpu.ebx = 364 /*0x16c*/;
    // 004df250  8d9528fdffff           -lea edx, [ebp - 0x2d8]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-728) /* -0x2d8 */);
    // 004df256  899d94feffff           -mov dword ptr [ebp - 0x16c], ebx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-364) /* -0x16c */) = cpu.ebx;
    // 004df25c  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004df25d  8d9594feffff           -lea edx, [ebp - 0x16c]
    cpu.edx = x86::reg32(cpu.ebp + x86::reg32(-364) /* -0x16c */);
    // 004df263  899d28fdffff           -mov dword ptr [ebp - 0x2d8], ebx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-728) /* -0x2d8 */) = cpu.ebx;
    // 004df269  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004df26a  8b08                   -mov ecx, dword ptr [eax]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax);
    // 004df26c  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004df26d  ff512c                 -call dword ptr [ecx + 0x2c]
    cpu.ip = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(44) /* 0x2c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004df270  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004df272  7533                   -jne 0x4df2a7
    if (!cpu.flags.zf)
    {
        goto L_0x004df2a7;
    }
    // 004df274  8aa599feffff           -mov ah, byte ptr [ebp - 0x167]
    cpu.ah = app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-359) /* -0x167 */);
    // 004df27a  f6c420                 +test ah, 0x20
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.ah & 32 /*0x20*/));
    // 004df27d  7411                   -je 0x4df290
    if (cpu.flags.zf)
    {
        goto L_0x004df290;
    }
    // 004df27f  f6c440                 +test ah, 0x40
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.ah & 64 /*0x40*/));
    // 004df282  740c                   -je 0x4df290
    if (cpu.flags.zf)
    {
        goto L_0x004df290;
    }
    // 004df284  c705d4a28c0001000000   -mov dword ptr [0x8ca2d4], 1
    app->getMemory<x86::reg32>(x86::reg32(9216724) /* 0x8ca2d4 */) = 1 /*0x1*/;
    // 004df28e  eb17                   -jmp 0x4df2a7
    goto L_0x004df2a7;
L_0x004df290:
    // 004df290  8ab599feffff           -mov dh, byte ptr [ebp - 0x167]
    cpu.dh = app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(-359) /* -0x167 */);
    // 004df296  f6c601                 +test dh, 1
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.dh & 1 /*0x1*/));
    // 004df299  740c                   -je 0x4df2a7
    if (cpu.flags.zf)
    {
        goto L_0x004df2a7;
    }
    // 004df29b  f6c602                 +test dh, 2
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(cpu.dh & 2 /*0x2*/));
    // 004df29e  7407                   -je 0x4df2a7
    if (cpu.flags.zf)
    {
        goto L_0x004df2a7;
    }
    // 004df2a0  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 004df2a2  a3d4a28c00             -mov dword ptr [0x8ca2d4], eax
    app->getMemory<x86::reg32>(x86::reg32(9216724) /* 0x8ca2d4 */) = cpu.eax;
L_0x004df2a7:
    // 004df2a7  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004df2a9  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df2aa  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df2ab  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df2ac  c20800                 -ret 8
    cpu.esp += 4+8 /*0x8*/;
    return;
}

/* align: skip 0x90 */
void Application::sub_4df2b0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (madShowFrame(app, cpu.sync())) /* port: native (tools/apply_native_movie.py) */
    {
        cpu.reload();
        return;
    }
    // 004df2b0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004df2b1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004df2b2  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004df2b3  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004df2b4  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004df2b5  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004df2b6  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004df2b8  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 004df2ba  833dd4a28c0002         +cmp dword ptr [0x8ca2d4], 2
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(9216724) /* 0x8ca2d4 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(2 /*0x2*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004df2c1  7405                   -je 0x4df2c8
    if (cpu.flags.zf)
    {
        goto L_0x004df2c8;
    }
    // 004df2c3  e8b8fbffff             -call 0x4dee80
    cpu.esp -= 4;
    sub_4dee80(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x004df2c8:
    // 004df2c8  833dd4a28c0002         +cmp dword ptr [0x8ca2d4], 2
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(9216724) /* 0x8ca2d4 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(2 /*0x2*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004df2cf  752e                   -jne 0x4df2ff
    if (!cpu.flags.zf)
    {
        goto L_0x004df2ff;
    }
    // 004df2d1  e84aba0000             -call 0x4ead20
    cpu.esp -= 4;
    sub_4ead20(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004df2d6  8b35cca28c00           -mov esi, dword ptr [0x8ca2cc]
    cpu.esi = app->getMemory<x86::reg32>(x86::reg32(9216716) /* 0x8ca2cc */);
    // 004df2dc  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004df2dd  8b3dc4a28c00           -mov edi, dword ptr [0x8ca2c4]
    cpu.edi = app->getMemory<x86::reg32>(x86::reg32(9216708) /* 0x8ca2c4 */);
    // 004df2e3  8b0dd0a28c00           -mov ecx, dword ptr [0x8ca2d0]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(9216720) /* 0x8ca2d0 */);
    // 004df2e9  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004df2ea  8b15dca28c00           -mov edx, dword ptr [0x8ca2dc]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(9216732) /* 0x8ca2dc */);
    // 004df2f0  a1e0a28c00             -mov eax, dword ptr [0x8ca2e0]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(9216736) /* 0x8ca2e0 */);
    // 004df2f5  e896e90100             -call 0x4fdc90
    cpu.esp -= 4;
    sub_4fdc90(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004df2fa  e891ba0000             -call 0x4ead90
    cpu.esp -= 4;
    sub_4ead90(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x004df2ff:
    // 004df2ff  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df300  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df301  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df302  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df303  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df304  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004df305  c3                     -ret 
    cpu.esp += 4;
    return;
}

}
