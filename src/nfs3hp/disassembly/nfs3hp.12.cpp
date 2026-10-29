#include "nfs3hp.h"
#include <lib/thread.h>

namespace nfs3hp
{
// Port (tools/apply_native_frontend.py): defined in native_frontend_tracks.cpp.
bool locationOnExit(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_tracks.cpp.
bool locationOnFrame(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_tracks.cpp.
bool locationOnEnter(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_options.cpp.
bool advancedIntensityMoved(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_options.cpp.
bool advancedOnFrame(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_options.cpp.
bool advancedOnExit(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_options.cpp.
bool advancedOnEnter(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_options.cpp.
bool graphicsOnFrame(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_options.cpp.
bool graphicsOnExit(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_native_frontend.py): defined in native_frontend_options.cpp.
bool graphicsOnEnter(win32::WinApplication* app, x86::CPU& cpu);
// Port (tools/apply_full_colour.py): defined in nfs3hp_main.cpp.
x86::reg32 shownDepth(x86::reg32 depth);
// Port (tools/apply_widescreen.py): defined in nfs3hp_main.cpp.
void dynamicFullscreenLabel(win32::WinApplication* app, x86::reg32 entry);

/* sub_4451d0: native, nfs3hp::port::dialogs::entryUnderMouse */

/* sub_4452d0: native, nfs3hp::port::dialogs::placeEntries */

/* sub_445380: native, nfs3hp::port::dialogs::drawList */

/* sub_445520: native, nfs3hp::port::dialogs::listKey */

/* sub_445680: native, nfs3hp::port::dialogs::listPass */

/* sub_445750: native, nfs3hp::port::dialogs::openList */

/* sub_445ac0: native, nfs3hp::port::dialogs::drawDialogHelp */

/* sub_445de0: native, nfs3hp::port::dialogs::loadDialogArt */

/* sub_445e60: native, nfs3hp::port::dialogs::dialogKey */

/* sub_445f00: native, nfs3hp::frontend::dialogFadedIn */

/* sub_445f10: native, nfs3hp::port::dialogs::closeDialog */

/* sub_445f50: native, nfs3hp::port::dialogs::dialogPass */

/* sub_446060: native, nfs3hp::load::readReplayInfo */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 */
void Application::sub_4461d0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004461d0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004461d1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004461d2  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004461d3  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004461d4  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004461d5  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004461d7  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 004461d9  e882ac0900             -call 0x4e0e60
    cpu.esp -= 4;
    nfs3hp::ea::fileExists(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004461de  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004461e0  0f84f1000000           -je 0x4462d7
    if (cpu.flags.zf)
    {
        goto L_0x004462d7;
    }
    // 004461e6  ba10000000             -mov edx, 0x10
    cpu.edx = 16 /*0x10*/;
    // 004461eb  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004461ed  e8eead0900             -call 0x4e0fe0
    cpu.esp -= 4;
    nfs3hp::ea::loadFileQuietly(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004461f2  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004461f4  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 004461f6  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004461f8  0f84d9000000           -je 0x4462d7
    if (cpu.flags.zf)
    {
        goto L_0x004462d7;
    }
    // 004461fe  8b807a180000           -mov eax, dword ptr [eax + 0x187a]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6266) /* 0x187a */);
    // 00446204  c1f810                 -sar eax, 0x10
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (16 /*0x10*/ % 32));
    // 00446207  8bb442bc180000         -mov esi, dword ptr [edx + eax*2 + 0x18bc]
    cpu.esi = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(6332) /* 0x18bc */ + cpu.eax * 2);
    // 0044620e  c1fe10                 -sar esi, 0x10
    cpu.esi = x86::reg32(x86::sreg32(cpu.esi) >> (16 /*0x10*/ % 32));
    // 00446211  83fe08                 +cmp esi, 8
    {
        x86::reg32 tmp1 = cpu.esi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(8 /*0x8*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00446214  0f8fb6000000           -jg 0x4462d0
    if (!cpu.flags.zf && (cpu.flags.sf == cpu.flags.of))
    {
        goto L_0x004462d0;
    }
    // 0044621a  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 0044621c  0f8cae000000           -jl 0x4462d0
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004462d0;
    }
    // 00446222  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 00446224  e8671e0300             -call 0x478090
    cpu.esp -= 4;
    sub_478090(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00446229  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0044622b  0f849f000000           -je 0x4462d0
    if (cpu.flags.zf)
    {
        goto L_0x004462d0;
    }
    // 00446231  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 00446233  e8c81e0300             -call 0x478100
    cpu.esp -= 4;
    sub_478100(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00446238  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0044623a  0f8490000000           -je 0x4462d0
    if (cpu.flags.zf)
    {
        goto L_0x004462d0;
    }
    // 00446240  8b9a30190000           -mov ebx, dword ptr [edx + 0x1930]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(6448) /* 0x1930 */);
    // 00446246  85db                   +test ebx, ebx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & cpu.ebx));
    // 00446248  7507                   -jne 0x446251
    if (!cpu.flags.zf)
    {
        goto L_0x00446251;
    }
    // 0044624a  bb90010000             -mov ebx, 0x190
    cpu.ebx = 400 /*0x190*/;
    // 0044624f  eb05                   -jmp 0x446256
    goto L_0x00446256;
L_0x00446251:
    // 00446251  bb91010000             -mov ebx, 0x191
    cpu.ebx = 401 /*0x191*/;
L_0x00446256:
    // 00446256  8b91b4190000           -mov edx, dword ptr [ecx + 0x19b4]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(6580) /* 0x19b4 */);
    // 0044625c  8d049500000000         -lea eax, [edx*4]
    cpu.eax = x86::reg32(cpu.edx * 4);
    // 00446263  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 00446265  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 00446268  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 0044626a  c1e003                 -shl eax, 3
    cpu.eax <<= 3 /*0x3*/ % 32;
    // 0044626d  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 0044626f  8b9401001a0000         -mov edx, dword ptr [ecx + eax + 0x1a00]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(6656) /* 0x1a00 */ + cpu.eax * 1);
    // 00446276  b8d7000000             -mov eax, 0xd7
    cpu.eax = 215 /*0xd7*/;
    // 0044627b  e8d0b50800             -call 0x4d1850
    cpu.esp -= 4;
    nfs3hp::port::text::languageText(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00446280  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00446281  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 00446283  e8c8b50800             -call 0x4d1850
    cpu.esp -= 4;
    nfs3hp::port::text::languageText(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00446288  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00446289  68cc8b5300             -push 0x538bcc
    app->getMemory<x86::reg32>(cpu.esp-4) = 5475276 /*0x538bcc*/;
    cpu.esp -= 4;
    // 0044628e  680c8d5500             -push 0x558d0c
    app->getMemory<x86::reg32>(cpu.esp-4) = 5606668 /*0x558d0c*/;
    cpu.esp -= 4;
    // 00446293  e8f8930900             -call 0x4df690
    cpu.esp -= 4;
    nfs3hp::watcom::sprintf(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00446298  83c410                 -add esp, 0x10
    (cpu.esp) += x86::reg32(x86::sreg32(16 /*0x10*/));
    // 0044629b  8d4666                 -lea eax, [esi + 0x66]
    cpu.eax = x86::reg32(cpu.esi + x86::reg32(102) /* 0x66 */);
    // 0044629e  e8adb50800             -call 0x4d1850
    cpu.esp -= 4;
    nfs3hp::port::text::languageText(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004462a3  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004462a4  68c08b5300             -push 0x538bc0
    app->getMemory<x86::reg32>(cpu.esp-4) = 5475264 /*0x538bc0*/;
    cpu.esp -= 4;
    // 004462a9  68848d5500             -push 0x558d84
    app->getMemory<x86::reg32>(cpu.esp-4) = 5606788 /*0x558d84*/;
    cpu.esp -= 4;
    // 004462ae  e8dd930900             -call 0x4df690
    cpu.esp -= 4;
    nfs3hp::watcom::sprintf(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004462b3  83c40c                 -add esp, 0xc
    (cpu.esp) += x86::reg32(x86::sreg32(12 /*0xc*/));
    // 004462b6  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004462b8  e8932fffff             -call 0x439250
    cpu.esp -= 4;
    nfs3hp::load::carName(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004462bd  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004462be  68c08b5300             -push 0x538bc0
    app->getMemory<x86::reg32>(cpu.esp-4) = 5475264 /*0x538bc0*/;
    cpu.esp -= 4;
    // 004462c3  68fc8d5500             -push 0x558dfc
    app->getMemory<x86::reg32>(cpu.esp-4) = 5606908 /*0x558dfc*/;
    cpu.esp -= 4;
    // 004462c8  e8c3930900             -call 0x4df690
    cpu.esp -= 4;
    nfs3hp::watcom::sprintf(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004462cd  83c40c                 -add esp, 0xc
    (cpu.esp) += x86::reg32(x86::sreg32(12 /*0xc*/));
L_0x004462d0:
    // 004462d0  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004462d2  e8b9b50900             -call 0x4e1890
    cpu.esp -= 4;
    nfs3hp::ea::purgememadr(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x004462d7:
    // 004462d7  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004462d8  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004462d9  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004462da  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004462db  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004462dc  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x40 0x00 */
void Application::sub_4462e0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004462e0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004462e1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004462e2  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004462e3  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004462e4  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004462e5  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004462e7  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 004462e9  e872ab0900             -call 0x4e0e60
    cpu.esp -= 4;
    nfs3hp::ea::fileExists(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004462ee  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004462f0  0f8415010000           -je 0x44640b
    if (cpu.flags.zf)
    {
        goto L_0x0044640b;
    }
    // 004462f6  ba10000000             -mov edx, 0x10
    cpu.edx = 16 /*0x10*/;
    // 004462fb  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004462fd  e8deac0900             -call 0x4e0fe0
    cpu.esp -= 4;
    nfs3hp::ea::loadFileQuietly(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00446302  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 00446304  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00446306  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00446308  0f84fd000000           -je 0x44640b
    if (cpu.flags.zf)
    {
        goto L_0x0044640b;
    }
    // 0044630e  8b80ca180000           -mov eax, dword ptr [eax + 0x18ca]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6346) /* 0x18ca */);
    // 00446314  c1f810                 -sar eax, 0x10
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (16 /*0x10*/ % 32));
    // 00446317  8b1c8504d05500         -mov ebx, dword ptr [eax*4 + 0x55d004]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(5623812) /* 0x55d004 */ + cpu.eax * 4);
    // 0044631e  83fb08                 +cmp ebx, 8
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
    // 00446321  0f8ddd000000           -jge 0x446404
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00446404;
    }
    // 00446327  85db                   +test ebx, ebx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & cpu.ebx));
    // 00446329  0f8cd5000000           -jl 0x446404
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x00446404;
    }
    // 0044632f  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 00446331  e85a1d0300             -call 0x478090
    cpu.esp -= 4;
    sub_478090(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00446336  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00446338  0f84c6000000           -je 0x446404
    if (cpu.flags.zf)
    {
        goto L_0x00446404;
    }
    // 0044633e  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 00446340  e8bb1d0300             -call 0x478100
    cpu.esp -= 4;
    sub_478100(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00446345  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00446347  0f84b7000000           -je 0x446404
    if (cpu.flags.zf)
    {
        goto L_0x00446404;
    }
    // 0044634d  8bb230190000           -mov esi, dword ptr [edx + 0x1930]
    cpu.esi = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(6448) /* 0x1930 */);
    // 00446353  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 00446355  7507                   -jne 0x44635e
    if (!cpu.flags.zf)
    {
        goto L_0x0044635e;
    }
    // 00446357  be90010000             -mov esi, 0x190
    cpu.esi = 400 /*0x190*/;
    // 0044635c  eb05                   -jmp 0x446363
    goto L_0x00446363;
L_0x0044635e:
    // 0044635e  be91010000             -mov esi, 0x191
    cpu.esi = 401 /*0x191*/;
L_0x00446363:
    // 00446363  8b91b4190000           -mov edx, dword ptr [ecx + 0x19b4]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(6580) /* 0x19b4 */);
    // 00446369  8d049500000000         -lea eax, [edx*4]
    cpu.eax = x86::reg32(cpu.edx * 4);
    // 00446370  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 00446372  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 00446375  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 00446377  c1e003                 -shl eax, 3
    cpu.eax <<= 3 /*0x3*/ % 32;
    // 0044637a  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 0044637c  8b9401001a0000         -mov edx, dword ptr [ecx + eax + 0x1a00]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(6656) /* 0x1a00 */ + cpu.eax * 1);
    // 00446383  b8d6000000             -mov eax, 0xd6
    cpu.eax = 214 /*0xd6*/;
    // 00446388  e8c3b40800             -call 0x4d1850
    cpu.esp -= 4;
    nfs3hp::port::text::languageText(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0044638d  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 0044638e  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 00446390  e8bbb40800             -call 0x4d1850
    cpu.esp -= 4;
    nfs3hp::port::text::languageText(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00446395  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00446396  68cc8b5300             -push 0x538bcc
    app->getMemory<x86::reg32>(cpu.esp-4) = 5475276 /*0x538bcc*/;
    cpu.esp -= 4;
    // 0044639b  680c8d5500             -push 0x558d0c
    app->getMemory<x86::reg32>(cpu.esp-4) = 5606668 /*0x558d0c*/;
    cpu.esp -= 4;
    // 004463a0  e8eb920900             -call 0x4df690
    cpu.esp -= 4;
    nfs3hp::watcom::sprintf(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004463a5  83c410                 -add esp, 0x10
    (cpu.esp) += x86::reg32(x86::sreg32(16 /*0x10*/));
    // 004463a8  8d4366                 -lea eax, [ebx + 0x66]
    cpu.eax = x86::reg32(cpu.ebx + x86::reg32(102) /* 0x66 */);
    // 004463ab  e8a0b40800             -call 0x4d1850
    cpu.esp -= 4;
    nfs3hp::port::text::languageText(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004463b0  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004463b1  68c08b5300             -push 0x538bc0
    app->getMemory<x86::reg32>(cpu.esp-4) = 5475264 /*0x538bc0*/;
    cpu.esp -= 4;
    // 004463b6  68848d5500             -push 0x558d84
    app->getMemory<x86::reg32>(cpu.esp-4) = 5606788 /*0x558d84*/;
    cpu.esp -= 4;
    // 004463bb  e8d0920900             -call 0x4df690
    cpu.esp -= 4;
    nfs3hp::watcom::sprintf(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004463c0  83c40c                 -add esp, 0xc
    (cpu.esp) += x86::reg32(x86::sreg32(12 /*0xc*/));
    // 004463c3  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004463c5  e8862effff             -call 0x439250
    cpu.esp -= 4;
    nfs3hp::load::carName(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004463ca  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004463cb  68c08b5300             -push 0x538bc0
    app->getMemory<x86::reg32>(cpu.esp-4) = 5475264 /*0x538bc0*/;
    cpu.esp -= 4;
    // 004463d0  68fc8d5500             -push 0x558dfc
    app->getMemory<x86::reg32>(cpu.esp-4) = 5606908 /*0x558dfc*/;
    cpu.esp -= 4;
    // 004463d5  e8b6920900             -call 0x4df690
    cpu.esp -= 4;
    nfs3hp::watcom::sprintf(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004463da  8b810c190000           -mov eax, dword ptr [ecx + 0x190c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(6412) /* 0x190c */);
    // 004463e0  83c40c                 -add esp, 0xc
    (cpu.esp) += x86::reg32(x86::sreg32(12 /*0xc*/));
    // 004463e3  c1f810                 -sar eax, 0x10
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (16 /*0x10*/ % 32));
    // 004463e6  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004463e7  b8f0000000             -mov eax, 0xf0
    cpu.eax = 240 /*0xf0*/;
    // 004463ec  e85fb40800             -call 0x4d1850
    cpu.esp -= 4;
    nfs3hp::port::text::languageText(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004463f1  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004463f2  68d48b5300             -push 0x538bd4
    app->getMemory<x86::reg32>(cpu.esp-4) = 5475284 /*0x538bd4*/;
    cpu.esp -= 4;
    // 004463f7  68748e5500             -push 0x558e74
    app->getMemory<x86::reg32>(cpu.esp-4) = 5607028 /*0x558e74*/;
    cpu.esp -= 4;
    // 004463fc  e88f920900             -call 0x4df690
    cpu.esp -= 4;
    nfs3hp::watcom::sprintf(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00446401  83c410                 -add esp, 0x10
    (cpu.esp) += x86::reg32(x86::sreg32(16 /*0x10*/));
L_0x00446404:
    // 00446404  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00446406  e885b40900             -call 0x4e1890
    cpu.esp -= 4;
    nfs3hp::ea::purgememadr(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x0044640b:
    // 0044640b  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0044640c  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0044640d  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0044640e  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0044640f  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446410  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x8d 0x40 0x00 */
void Application::sub_446420(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00446420  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00446421  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00446422  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00446423  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00446424  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00446425  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00446427  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00446429  e832aa0900             -call 0x4e0e60
    cpu.esp -= 4;
    nfs3hp::ea::fileExists(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0044642e  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00446430  0f84c7000000           -je 0x4464fd
    if (cpu.flags.zf)
    {
        goto L_0x004464fd;
    }
    // 00446436  ba10000000             -mov edx, 0x10
    cpu.edx = 16 /*0x10*/;
    // 0044643b  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 0044643d  e89eab0900             -call 0x4e0fe0
    cpu.esp -= 4;
    nfs3hp::ea::loadFileQuietly(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00446442  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 00446444  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 00446446  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00446448  0f84af000000           -je 0x4464fd
    if (cpu.flags.zf)
    {
        goto L_0x004464fd;
    }
    // 0044644e  8b986c190000           -mov ebx, dword ptr [eax + 0x196c]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6508) /* 0x196c */);
    // 00446454  83fb08                 +cmp ebx, 8
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
    // 00446457  0f8f99000000           -jg 0x4464f6
    if (!cpu.flags.zf && (cpu.flags.sf == cpu.flags.of))
    {
        goto L_0x004464f6;
    }
    // 0044645d  85db                   +test ebx, ebx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & cpu.ebx));
    // 0044645f  0f8c91000000           -jl 0x4464f6
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x004464f6;
    }
    // 00446465  e8261c0300             -call 0x478090
    cpu.esp -= 4;
    sub_478090(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0044646a  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0044646c  0f8484000000           -je 0x4464f6
    if (cpu.flags.zf)
    {
        goto L_0x004464f6;
    }
    // 00446472  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 00446474  e8871c0300             -call 0x478100
    cpu.esp -= 4;
    sub_478100(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00446479  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0044647b  7479                   -je 0x4464f6
    if (cpu.flags.zf)
    {
        goto L_0x004464f6;
    }
    // 0044647d  8b8ab4190000           -mov ecx, dword ptr [edx + 0x19b4]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(6580) /* 0x19b4 */);
    // 00446483  8d048d00000000         -lea eax, [ecx*4]
    cpu.eax = x86::reg32(cpu.ecx * 4);
    // 0044648a  29c8                   -sub eax, ecx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.ecx));
    // 0044648c  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 0044648f  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00446491  c1e003                 -shl eax, 3
    cpu.eax <<= 3 /*0x3*/ % 32;
    // 00446494  01c8                   -add eax, ecx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.ecx));
    // 00446496  8b8c02001a0000         -mov ecx, dword ptr [edx + eax + 0x1a00]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(6656) /* 0x1a00 */ + cpu.eax * 1);
    // 0044649d  8d4366                 -lea eax, [ebx + 0x66]
    cpu.eax = x86::reg32(cpu.ebx + x86::reg32(102) /* 0x66 */);
    // 004464a0  e8abb30800             -call 0x4d1850
    cpu.esp -= 4;
    nfs3hp::port::text::languageText(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004464a5  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004464a6  68c08b5300             -push 0x538bc0
    app->getMemory<x86::reg32>(cpu.esp-4) = 5475264 /*0x538bc0*/;
    cpu.esp -= 4;
    // 004464ab  680c8d5500             -push 0x558d0c
    app->getMemory<x86::reg32>(cpu.esp-4) = 5606668 /*0x558d0c*/;
    cpu.esp -= 4;
    // 004464b0  e8db910900             -call 0x4df690
    cpu.esp -= 4;
    nfs3hp::watcom::sprintf(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004464b5  83c40c                 -add esp, 0xc
    (cpu.esp) += x86::reg32(x86::sreg32(12 /*0xc*/));
    // 004464b8  b805000000             -mov eax, 5
    cpu.eax = 5 /*0x5*/;
    // 004464bd  e88eb30800             -call 0x4d1850
    cpu.esp -= 4;
    nfs3hp::port::text::languageText(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004464c2  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004464c3  8b9a74190000           -mov ebx, dword ptr [edx + 0x1974]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(6516) /* 0x1974 */);
    // 004464c9  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004464ca  68c48b5300             -push 0x538bc4
    app->getMemory<x86::reg32>(cpu.esp-4) = 5475268 /*0x538bc4*/;
    cpu.esp -= 4;
    // 004464cf  68848d5500             -push 0x558d84
    app->getMemory<x86::reg32>(cpu.esp-4) = 5606788 /*0x558d84*/;
    cpu.esp -= 4;
    // 004464d4  e8b7910900             -call 0x4df690
    cpu.esp -= 4;
    nfs3hp::watcom::sprintf(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004464d9  83c410                 -add esp, 0x10
    (cpu.esp) += x86::reg32(x86::sreg32(16 /*0x10*/));
    // 004464dc  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004464de  e86d2dffff             -call 0x439250
    cpu.esp -= 4;
    nfs3hp::load::carName(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004464e3  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004464e4  68c08b5300             -push 0x538bc0
    app->getMemory<x86::reg32>(cpu.esp-4) = 5475264 /*0x538bc0*/;
    cpu.esp -= 4;
    // 004464e9  68fc8d5500             -push 0x558dfc
    app->getMemory<x86::reg32>(cpu.esp-4) = 5606908 /*0x558dfc*/;
    cpu.esp -= 4;
    // 004464ee  e89d910900             -call 0x4df690
    cpu.esp -= 4;
    nfs3hp::watcom::sprintf(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004464f3  83c40c                 -add esp, 0xc
    (cpu.esp) += x86::reg32(x86::sreg32(12 /*0xc*/));
L_0x004464f6:
    // 004464f6  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004464f8  e893b30900             -call 0x4e1890
    cpu.esp -= 4;
    nfs3hp::ea::purgememadr(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x004464fd:
    // 004464fd  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004464fe  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004464ff  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446500  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446501  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446502  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x90 */
void Application::sub_446510(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00446510  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00446511  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00446513  81ec00010000           -sub esp, 0x100
    (cpu.esp) -= x86::reg32(x86::sreg32(256 /*0x100*/));
    // 00446519  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 0044651a  68342f7a00             -push 0x7a2f34
    app->getMemory<x86::reg32>(cpu.esp-4) = 8007476 /*0x7a2f34*/;
    cpu.esp -= 4;
    // 0044651f  68dc8b5300             -push 0x538bdc
    app->getMemory<x86::reg32>(cpu.esp-4) = 5475292 /*0x538bdc*/;
    cpu.esp -= 4;
    // 00446524  8d8500ffffff           -lea eax, [ebp - 0x100]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-256) /* -0x100 */);
    // 0044652a  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 0044652b  e860910900             -call 0x4df690
    cpu.esp -= 4;
    nfs3hp::watcom::sprintf(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00446530  83c410                 -add esp, 0x10
    (cpu.esp) += x86::reg32(x86::sreg32(16 /*0x10*/));
    // 00446533  8d8500ffffff           -lea eax, [ebp - 0x100]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-256) /* -0x100 */);
    // 00446539  e822a90900             -call 0x4e0e60
    cpu.esp -= 4;
    nfs3hp::ea::fileExists(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0044653e  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00446540  7405                   -je 0x446547
    if (cpu.flags.zf)
    {
        goto L_0x00446547;
    }
    // 00446542  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
L_0x00446547:
    // 00446547  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00446549  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0044654a  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x40 0x00 0x8b 0xc9 */
void Application::sub_446550(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00446550  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00446551  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00446552  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00446553  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00446554  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00446555  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00446556  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00446558  81ec00010000           -sub esp, 0x100
    (cpu.esp) -= x86::reg32(x86::sreg32(256 /*0x100*/));
    // 0044655e  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 0044655f  68342f7a00             -push 0x7a2f34
    app->getMemory<x86::reg32>(cpu.esp-4) = 8007476 /*0x7a2f34*/;
    cpu.esp -= 4;
    // 00446564  68dc8b5300             -push 0x538bdc
    app->getMemory<x86::reg32>(cpu.esp-4) = 5475292 /*0x538bdc*/;
    cpu.esp -= 4;
    // 00446569  8d8500ffffff           -lea eax, [ebp - 0x100]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-256) /* -0x100 */);
    // 0044656f  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00446570  bb10000000             -mov ebx, 0x10
    cpu.ebx = 16 /*0x10*/;
    // 00446575  baf0200000             -mov edx, 0x20f0
    cpu.edx = 8432 /*0x20f0*/;
    // 0044657a  e811910900             -call 0x4df690
    cpu.esp -= 4;
    nfs3hp::watcom::sprintf(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0044657f  83c410                 -add esp, 0x10
    (cpu.esp) += x86::reg32(x86::sreg32(16 /*0x10*/));
    // 00446582  b8e88b5300             -mov eax, 0x538be8
    cpu.eax = 5475304 /*0x538be8*/;
    // 00446587  31f6                   -xor esi, esi
    cpu.esi ^= x86::reg32(x86::sreg32(cpu.esi));
    // 00446589  e892b00900             -call 0x4e1620
    cpu.esp -= 4;
    nfs3hp::ea::reservememadr(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0044658e  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00446590  89c7                   -mov edi, eax
    cpu.edi = cpu.eax;
    // 00446592  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00446594  743a                   -je 0x4465d0
    if (cpu.flags.zf)
    {
        goto L_0x004465d0;
    }
    // 00446596  bbf0200000             -mov ebx, 0x20f0
    cpu.ebx = 8432 /*0x20f0*/;
    // 0044659b  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 0044659d  b840bb6f00             -mov eax, 0x6fbb40
    cpu.eax = 7322432 /*0x6fbb40*/;
    // 004465a2  e8493f0a00             -call 0x4ea4f0
    cpu.esp -= 4;
    nfs3hp::ea::memmove(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004465a7  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004465a9  e8621a0300             -call 0x478010
    cpu.esp -= 4;
    sub_478010(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004465ae  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004465b0  7417                   -je 0x4465c9
    if (cpu.flags.zf)
    {
        goto L_0x004465c9;
    }
    // 004465b2  bbf0200000             -mov ebx, 0x20f0
    cpu.ebx = 8432 /*0x20f0*/;
    // 004465b7  8d8500ffffff           -lea eax, [ebp - 0x100]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-256) /* -0x100 */);
    // 004465bd  89ca                   -mov edx, ecx
    cpu.edx = cpu.ecx;
    // 004465bf  be01000000             -mov esi, 1
    cpu.esi = 1 /*0x1*/;
    // 004465c4  e817850a00             -call 0x4eeae0
    cpu.esp -= 4;
    nfs3hp::load::savefileadr(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x004465c9:
    // 004465c9  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 004465cb  e8c0b20900             -call 0x4e1890
    cpu.esp -= 4;
    nfs3hp::ea::purgememadr(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x004465d0:
    // 004465d0  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004465d2  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004465d4  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004465d5  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004465d6  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004465d7  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004465d8  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004465d9  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004465da  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x40 0x00 0x8b 0xc9 */
void Application::sub_4465e0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004465e0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004465e1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004465e2  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004465e3  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004465e4  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004465e5  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004465e6  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004465e8  81ec8c170000           -sub esp, 0x178c
    (cpu.esp) -= x86::reg32(x86::sreg32(6028 /*0x178c*/));
    // 004465ee  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 004465f0  b9db050000             -mov ecx, 0x5db
    cpu.ecx = 1499 /*0x5db*/;
    // 004465f5  8dbd74e8ffff           -lea edi, [ebp - 0x178c]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(-6028) /* -0x178c */);
    // 004465fb  be4cbb6f00             -mov esi, 0x6fbb4c
    cpu.esi = 7322444 /*0x6fbb4c*/;
    // 00446600  f3a5                   -rep movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00446602  8d7dec                 -lea edi, [ebp - 0x14]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(-20) /* -0x14 */);
    // 00446605  bedcd26f00             -mov esi, 0x6fd2dc
    cpu.esi = 7328476 /*0x6fd2dc*/;
    // 0044660a  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 0044660b  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 0044660c  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 0044660d  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 0044660f  8d7de0                 -lea edi, [ebp - 0x20]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(-32) /* -0x20 */);
    // 00446612  be48d36f00             -mov esi, 0x6fd348
    cpu.esi = 7328584 /*0x6fd348*/;
    // 00446617  8955fc                 -mov dword ptr [ebp - 4], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.edx;
    // 0044661a  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 0044661b  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 0044661c  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 0044661d  e83ea80900             -call 0x4e0e60
    cpu.esp -= 4;
    nfs3hp::ea::fileExists(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00446622  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00446624  746a                   -je 0x446690
    if (cpu.flags.zf)
    {
        goto L_0x00446690;
    }
    // 00446626  ba10000000             -mov edx, 0x10
    cpu.edx = 16 /*0x10*/;
    // 0044662b  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 0044662d  e8aea90900             -call 0x4e0fe0
    cpu.esp -= 4;
    nfs3hp::ea::loadFileQuietly(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00446632  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 00446634  8945f8                 -mov dword ptr [ebp - 8], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.eax;
    // 00446637  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00446639  7452                   -je 0x44668d
    if (cpu.flags.zf)
    {
        goto L_0x0044668d;
    }
    // 0044663b  e8501a0300             -call 0x478090
    cpu.esp -= 4;
    sub_478090(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00446640  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00446642  7441                   -je 0x446685
    if (cpu.flags.zf)
    {
        goto L_0x00446685;
    }
    // 00446644  bbf0200000             -mov ebx, 0x20f0
    cpu.ebx = 8432 /*0x20f0*/;
    // 00446649  ba40bb6f00             -mov edx, 0x6fbb40
    cpu.edx = 7322432 /*0x6fbb40*/;
    // 0044664e  b9db050000             -mov ecx, 0x5db
    cpu.ecx = 1499 /*0x5db*/;
    // 00446653  bf4cbb6f00             -mov edi, 0x6fbb4c
    cpu.edi = 7322444 /*0x6fbb4c*/;
    // 00446658  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 0044665a  8db574e8ffff           -lea esi, [ebp - 0x178c]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(-6028) /* -0x178c */);
    // 00446660  e88b3e0a00             -call 0x4ea4f0
    cpu.esp -= 4;
    nfs3hp::ea::memmove(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00446665  f3a5                   -rep movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00446667  8d75ec                 -lea esi, [ebp - 0x14]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(-20) /* -0x14 */);
    // 0044666a  bfdcd26f00             -mov edi, 0x6fd2dc
    cpu.edi = 7328476 /*0x6fd2dc*/;
    // 0044666f  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00446670  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00446671  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00446672  b901000000             -mov ecx, 1
    cpu.ecx = 1 /*0x1*/;
    // 00446677  8d75e0                 -lea esi, [ebp - 0x20]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(-32) /* -0x20 */);
    // 0044667a  bf48d36f00             -mov edi, 0x6fd348
    cpu.edi = 7328584 /*0x6fd348*/;
    // 0044667f  894dfc                 -mov dword ptr [ebp - 4], ecx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.ecx;
    // 00446682  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00446683  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00446684  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
L_0x00446685:
    // 00446685  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 00446688  e803b20900             -call 0x4e1890
    cpu.esp -= 4;
    nfs3hp::ea::purgememadr(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x0044668d:
    // 0044668d  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
L_0x00446690:
    // 00446690  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00446692  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446693  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446694  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446695  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446696  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446697  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446698  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x90 */
void Application::sub_4466a0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004466a0  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004466a1  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004466a2  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004466a3  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004466a4  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004466a5  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004466a7  81ec84170000           -sub esp, 0x1784
    (cpu.esp) -= x86::reg32(x86::sreg32(6020 /*0x1784*/));
    // 004466ad  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004466af  b9db050000             -mov ecx, 0x5db
    cpu.ecx = 1499 /*0x5db*/;
    // 004466b4  8dbd7ce8ffff           -lea edi, [ebp - 0x1784]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(-6020) /* -0x1784 */);
    // 004466ba  be4cbb6f00             -mov esi, 0x6fbb4c
    cpu.esi = 7322444 /*0x6fbb4c*/;
    // 004466bf  f3a5                   -rep movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004466c1  8d7df4                 -lea edi, [ebp - 0xc]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 004466c4  bedcd26f00             -mov esi, 0x6fd2dc
    cpu.esi = 7328476 /*0x6fd2dc*/;
    // 004466c9  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004466ca  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004466cb  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004466cc  8d7de8                 -lea edi, [ebp - 0x18]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(-24) /* -0x18 */);
    // 004466cf  be48d36f00             -mov esi, 0x6fd348
    cpu.esi = 7328584 /*0x6fd348*/;
    // 004466d4  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004466d5  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004466d6  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004466d7  e844c10200             -call 0x472820
    cpu.esp -= 4;
    nfs3hp::load::saveConfig(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004466dc  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004466de  e86d140300             -call 0x477b50
    cpu.esp -= 4;
    sub_477b50(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004466e3  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004466e5  7445                   -je 0x44672c
    if (cpu.flags.zf)
    {
        goto L_0x0044672c;
    }
    // 004466e7  b9db050000             -mov ecx, 0x5db
    cpu.ecx = 1499 /*0x5db*/;
    // 004466ec  8db57ce8ffff           -lea esi, [ebp - 0x1784]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(-6020) /* -0x1784 */);
    // 004466f2  bf4cbb6f00             -mov edi, 0x6fbb4c
    cpu.edi = 7322444 /*0x6fbb4c*/;
    // 004466f7  f3a5                   -rep movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004466f9  8d75f4                 -lea esi, [ebp - 0xc]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 004466fc  bfdcd26f00             -mov edi, 0x6fd2dc
    cpu.edi = 7328476 /*0x6fd2dc*/;
    // 00446701  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00446702  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00446703  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00446704  8d75e8                 -lea esi, [ebp - 0x18]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(-24) /* -0x18 */);
    // 00446707  bf48d36f00             -mov edi, 0x6fd348
    cpu.edi = 7328584 /*0x6fd348*/;
    // 0044670c  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 0044670d  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 0044670e  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 0044670f  a1aad46f00             -mov eax, dword ptr [0x6fd4aa]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(7328938) /* 0x6fd4aa */);
    // 00446714  c1f810                 -sar eax, 0x10
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (16 /*0x10*/ % 32));
    // 00446717  e8e4870800             -call 0x4cef00
    cpu.esp -= 4;
    sub_4cef00(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0044671c  98                     -cwde 
    cpu.eax = x86::reg32(static_cast<x86::sreg16>(cpu.ax));
    // 0044671d  a3b4d26f00             -mov dword ptr [0x6fd2b4], eax
    app->getMemory<x86::reg32>(x86::reg32(7328436) /* 0x6fd2b4 */) = cpu.eax;
    // 00446722  a350bb6f00             -mov dword ptr [0x6fbb50], eax
    app->getMemory<x86::reg32>(x86::reg32(7322448) /* 0x6fbb50 */) = cpu.eax;
    // 00446727  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
L_0x0044672c:
    // 0044672c  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 0044672e  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0044672f  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446730  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446731  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446732  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446733  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 */
void Application::sub_446740(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00446740  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00446741  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00446743  81ec00010000           -sub esp, 0x100
    (cpu.esp) -= x86::reg32(x86::sreg32(256 /*0x100*/));
    // 00446749  68ec8b5300             -push 0x538bec
    app->getMemory<x86::reg32>(cpu.esp-4) = 5475308 /*0x538bec*/;
    cpu.esp -= 4;
    // 0044674e  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 0044674f  68342f7a00             -push 0x7a2f34
    app->getMemory<x86::reg32>(cpu.esp-4) = 8007476 /*0x7a2f34*/;
    cpu.esp -= 4;
    // 00446754  68f08b5300             -push 0x538bf0
    app->getMemory<x86::reg32>(cpu.esp-4) = 5475312 /*0x538bf0*/;
    cpu.esp -= 4;
    // 00446759  8d8500ffffff           -lea eax, [ebp - 0x100]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-256) /* -0x100 */);
    // 0044675f  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00446760  e82b8f0900             -call 0x4df690
    cpu.esp -= 4;
    nfs3hp::watcom::sprintf(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00446765  83c414                 -add esp, 0x14
    (cpu.esp) += x86::reg32(x86::sreg32(20 /*0x14*/));
    // 00446768  8d8500ffffff           -lea eax, [ebp - 0x100]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-256) /* -0x100 */);
    // 0044676e  e8eda60900             -call 0x4e0e60
    cpu.esp -= 4;
    nfs3hp::ea::fileExists(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00446773  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00446775  7405                   -je 0x44677c
    if (cpu.flags.zf)
    {
        goto L_0x0044677c;
    }
    // 00446777  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
L_0x0044677c:
    // 0044677c  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 0044677e  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0044677f  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_446780: native, nfs3hp::load::saveGhostAs */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 0x8b 0xdb */
void Application::sub_446800(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00446800  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00446801  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00446802  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00446803  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00446804  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00446805  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00446806  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00446808  81ec8c170000           -sub esp, 0x178c
    (cpu.esp) -= x86::reg32(x86::sreg32(6028 /*0x178c*/));
    // 0044680e  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 00446810  b9db050000             -mov ecx, 0x5db
    cpu.ecx = 1499 /*0x5db*/;
    // 00446815  8dbd74e8ffff           -lea edi, [ebp - 0x178c]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(-6028) /* -0x178c */);
    // 0044681b  be4cbb6f00             -mov esi, 0x6fbb4c
    cpu.esi = 7322444 /*0x6fbb4c*/;
    // 00446820  f3a5                   -rep movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00446822  8d7dec                 -lea edi, [ebp - 0x14]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(-20) /* -0x14 */);
    // 00446825  bedcd26f00             -mov esi, 0x6fd2dc
    cpu.esi = 7328476 /*0x6fd2dc*/;
    // 0044682a  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 0044682b  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 0044682c  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 0044682d  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 0044682f  8d7de0                 -lea edi, [ebp - 0x20]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(-32) /* -0x20 */);
    // 00446832  be48d36f00             -mov esi, 0x6fd348
    cpu.esi = 7328584 /*0x6fd348*/;
    // 00446837  8955fc                 -mov dword ptr [ebp - 4], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.edx;
    // 0044683a  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 0044683b  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 0044683c  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 0044683d  e81ea60900             -call 0x4e0e60
    cpu.esp -= 4;
    nfs3hp::ea::fileExists(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00446842  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00446844  746a                   -je 0x4468b0
    if (cpu.flags.zf)
    {
        goto L_0x004468b0;
    }
    // 00446846  ba10000000             -mov edx, 0x10
    cpu.edx = 16 /*0x10*/;
    // 0044684b  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 0044684d  e88ea70900             -call 0x4e0fe0
    cpu.esp -= 4;
    nfs3hp::ea::loadFileQuietly(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00446852  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 00446854  8945f8                 -mov dword ptr [ebp - 8], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */) = cpu.eax;
    // 00446857  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00446859  7452                   -je 0x4468ad
    if (cpu.flags.zf)
    {
        goto L_0x004468ad;
    }
    // 0044685b  e830180300             -call 0x478090
    cpu.esp -= 4;
    sub_478090(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00446860  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00446862  7441                   -je 0x4468a5
    if (cpu.flags.zf)
    {
        goto L_0x004468a5;
    }
    // 00446864  bbf0200000             -mov ebx, 0x20f0
    cpu.ebx = 8432 /*0x20f0*/;
    // 00446869  ba40bb6f00             -mov edx, 0x6fbb40
    cpu.edx = 7322432 /*0x6fbb40*/;
    // 0044686e  b9db050000             -mov ecx, 0x5db
    cpu.ecx = 1499 /*0x5db*/;
    // 00446873  bf4cbb6f00             -mov edi, 0x6fbb4c
    cpu.edi = 7322444 /*0x6fbb4c*/;
    // 00446878  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 0044687a  8db574e8ffff           -lea esi, [ebp - 0x178c]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(-6028) /* -0x178c */);
    // 00446880  e86b3c0a00             -call 0x4ea4f0
    cpu.esp -= 4;
    nfs3hp::ea::memmove(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00446885  f3a5                   -rep movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00446887  8d75ec                 -lea esi, [ebp - 0x14]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(-20) /* -0x14 */);
    // 0044688a  bfdcd26f00             -mov edi, 0x6fd2dc
    cpu.edi = 7328476 /*0x6fd2dc*/;
    // 0044688f  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00446890  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00446891  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00446892  b901000000             -mov ecx, 1
    cpu.ecx = 1 /*0x1*/;
    // 00446897  8d75e0                 -lea esi, [ebp - 0x20]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(-32) /* -0x20 */);
    // 0044689a  bf48d36f00             -mov edi, 0x6fd348
    cpu.edi = 7328584 /*0x6fd348*/;
    // 0044689f  894dfc                 -mov dword ptr [ebp - 4], ecx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.ecx;
    // 004468a2  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004468a3  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004468a4  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
L_0x004468a5:
    // 004468a5  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 004468a8  e8e3af0900             -call 0x4e1890
    cpu.esp -= 4;
    nfs3hp::ea::purgememadr(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x004468ad:
    // 004468ad  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
L_0x004468b0:
    // 004468b0  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 004468b2  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004468b3  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004468b4  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004468b5  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004468b6  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004468b7  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004468b8  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x90 */
void Application::sub_4468c0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004468c0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004468c1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004468c2  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004468c3  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004468c4  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004468c5  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004468c6  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004468c8  81ec00010000           -sub esp, 0x100
    (cpu.esp) -= x86::reg32(x86::sreg32(256 /*0x100*/));
    // 004468ce  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004468cf  68342f7a00             -push 0x7a2f34
    app->getMemory<x86::reg32>(cpu.esp-4) = 8007476 /*0x7a2f34*/;
    cpu.esp -= 4;
    // 004468d4  68048c5300             -push 0x538c04
    app->getMemory<x86::reg32>(cpu.esp-4) = 5475332 /*0x538c04*/;
    cpu.esp -= 4;
    // 004468d9  8d8500ffffff           -lea eax, [ebp - 0x100]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-256) /* -0x100 */);
    // 004468df  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004468e0  bb10000000             -mov ebx, 0x10
    cpu.ebx = 16 /*0x10*/;
    // 004468e5  baf0200000             -mov edx, 0x20f0
    cpu.edx = 8432 /*0x20f0*/;
    // 004468ea  e8a18d0900             -call 0x4df690
    cpu.esp -= 4;
    nfs3hp::watcom::sprintf(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004468ef  83c410                 -add esp, 0x10
    (cpu.esp) += x86::reg32(x86::sreg32(16 /*0x10*/));
    // 004468f2  b8e88b5300             -mov eax, 0x538be8
    cpu.eax = 5475304 /*0x538be8*/;
    // 004468f7  31f6                   -xor esi, esi
    cpu.esi ^= x86::reg32(x86::sreg32(cpu.esi));
    // 004468f9  e822ad0900             -call 0x4e1620
    cpu.esp -= 4;
    nfs3hp::ea::reservememadr(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004468fe  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00446900  89c7                   -mov edi, eax
    cpu.edi = cpu.eax;
    // 00446902  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00446904  743a                   -je 0x446940
    if (cpu.flags.zf)
    {
        goto L_0x00446940;
    }
    // 00446906  bbf0200000             -mov ebx, 0x20f0
    cpu.ebx = 8432 /*0x20f0*/;
    // 0044690b  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 0044690d  b840bb6f00             -mov eax, 0x6fbb40
    cpu.eax = 7322432 /*0x6fbb40*/;
    // 00446912  e8d93b0a00             -call 0x4ea4f0
    cpu.esp -= 4;
    nfs3hp::ea::memmove(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00446917  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00446919  e8f2160300             -call 0x478010
    cpu.esp -= 4;
    sub_478010(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0044691e  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00446920  7417                   -je 0x446939
    if (cpu.flags.zf)
    {
        goto L_0x00446939;
    }
    // 00446922  bbf0200000             -mov ebx, 0x20f0
    cpu.ebx = 8432 /*0x20f0*/;
    // 00446927  8d8500ffffff           -lea eax, [ebp - 0x100]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-256) /* -0x100 */);
    // 0044692d  89ca                   -mov edx, ecx
    cpu.edx = cpu.ecx;
    // 0044692f  be01000000             -mov esi, 1
    cpu.esi = 1 /*0x1*/;
    // 00446934  e8a7810a00             -call 0x4eeae0
    cpu.esp -= 4;
    nfs3hp::load::savefileadr(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00446939:
    // 00446939  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 0044693b  e850af0900             -call 0x4e1890
    cpu.esp -= 4;
    nfs3hp::ea::purgememadr(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00446940:
    // 00446940  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 00446942  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00446944  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446945  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446946  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446947  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446948  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446949  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0044694a  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x40 0x00 0x8b 0xc9 */
void Application::sub_446950(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00446950  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00446951  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00446953  81ec00010000           -sub esp, 0x100
    (cpu.esp) -= x86::reg32(x86::sreg32(256 /*0x100*/));
    // 00446959  68108c5300             -push 0x538c10
    app->getMemory<x86::reg32>(cpu.esp-4) = 5475344 /*0x538c10*/;
    cpu.esp -= 4;
    // 0044695e  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 0044695f  68342f7a00             -push 0x7a2f34
    app->getMemory<x86::reg32>(cpu.esp-4) = 8007476 /*0x7a2f34*/;
    cpu.esp -= 4;
    // 00446964  68f08b5300             -push 0x538bf0
    app->getMemory<x86::reg32>(cpu.esp-4) = 5475312 /*0x538bf0*/;
    cpu.esp -= 4;
    // 00446969  8d8500ffffff           -lea eax, [ebp - 0x100]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-256) /* -0x100 */);
    // 0044696f  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00446970  e81b8d0900             -call 0x4df690
    cpu.esp -= 4;
    nfs3hp::watcom::sprintf(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00446975  83c414                 -add esp, 0x14
    (cpu.esp) += x86::reg32(x86::sreg32(20 /*0x14*/));
    // 00446978  8d8500ffffff           -lea eax, [ebp - 0x100]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-256) /* -0x100 */);
    // 0044697e  e8dda40900             -call 0x4e0e60
    cpu.esp -= 4;
    nfs3hp::ea::fileExists(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00446983  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00446985  7405                   -je 0x44698c
    if (cpu.flags.zf)
    {
        goto L_0x0044698c;
    }
    // 00446987  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
L_0x0044698c:
    // 0044698c  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 0044698e  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0044698f  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_446990: native, nfs3hp::load::loadKeptReplay */

/* sub_446a10: native, nfs3hp::load::saveReplayAs */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 0x8b 0xdb */
void Application::sub_446a90(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00446a90  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00446a91  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00446a93  81ec00010000           -sub esp, 0x100
    (cpu.esp) -= x86::reg32(x86::sreg32(256 /*0x100*/));
    // 00446a99  68148c5300             -push 0x538c14
    app->getMemory<x86::reg32>(cpu.esp-4) = 5475348 /*0x538c14*/;
    cpu.esp -= 4;
    // 00446a9e  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00446a9f  68342f7a00             -push 0x7a2f34
    app->getMemory<x86::reg32>(cpu.esp-4) = 8007476 /*0x7a2f34*/;
    cpu.esp -= 4;
    // 00446aa4  68f08b5300             -push 0x538bf0
    app->getMemory<x86::reg32>(cpu.esp-4) = 5475312 /*0x538bf0*/;
    cpu.esp -= 4;
    // 00446aa9  8d8500ffffff           -lea eax, [ebp - 0x100]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-256) /* -0x100 */);
    // 00446aaf  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00446ab0  e8db8b0900             -call 0x4df690
    cpu.esp -= 4;
    nfs3hp::watcom::sprintf(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00446ab5  83c414                 -add esp, 0x14
    (cpu.esp) += x86::reg32(x86::sreg32(20 /*0x14*/));
    // 00446ab8  8d8500ffffff           -lea eax, [ebp - 0x100]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-256) /* -0x100 */);
    // 00446abe  e89da30900             -call 0x4e0e60
    cpu.esp -= 4;
    nfs3hp::ea::fileExists(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00446ac3  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00446ac5  7405                   -je 0x446acc
    if (cpu.flags.zf)
    {
        goto L_0x00446acc;
    }
    // 00446ac7  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
L_0x00446acc:
    // 00446acc  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00446ace  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446acf  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip  */
void Application::sub_446ad0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00446ad0  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00446ad1  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00446ad2  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00446ad3  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00446ad5  8b15c0915500           -mov edx, dword ptr [0x5591c0]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5607872) /* 0x5591c0 */);
    // 00446adb  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 00446add  7506                   -jne 0x446ae5
    if (!cpu.flags.zf)
    {
        goto L_0x00446ae5;
    }
    // 00446adf  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00446ae1  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446ae2  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446ae3  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446ae4  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x00446ae5:
    // 00446ae5  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 00446ae7  ba108c5300             -mov edx, 0x538c10
    cpu.edx = 5475344 /*0x538c10*/;
    // 00446aec  e8af0a0000             -call 0x4475a0
    cpu.esp -= 4;
    nfs3hp::load::listReplays(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00446af1  a1c0915500             -mov eax, dword ptr [0x5591c0]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5607872) /* 0x5591c0 */);
    // 00446af6  b902000000             -mov ecx, 2
    cpu.ecx = 2 /*0x2*/;
    // 00446afb  8b504c                 -mov edx, dword ptr [eax + 0x4c]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(76) /* 0x4c */);
    // 00446afe  890dbc915500           -mov dword ptr [0x5591bc], ecx
    app->getMemory<x86::reg32>(x86::reg32(5607868) /* 0x5591bc */) = cpu.ecx;
    // 00446b04  e897060000             -call 0x4471a0
    cpu.esp -= 4;
    sub_4471a0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00446b09  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00446b0b  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446b0c  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446b0d  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446b0e  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x90 */
void Application::sub_446b10(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00446b10  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00446b11  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00446b12  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00446b13  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00446b15  8b15c0915500           -mov edx, dword ptr [0x5591c0]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5607872) /* 0x5591c0 */);
    // 00446b1b  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 00446b1d  7506                   -jne 0x446b25
    if (!cpu.flags.zf)
    {
        goto L_0x00446b25;
    }
    // 00446b1f  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00446b21  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446b22  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446b23  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446b24  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x00446b25:
    // 00446b25  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 00446b27  ba188c5300             -mov edx, 0x538c18
    cpu.edx = 5475352 /*0x538c18*/;
    // 00446b2c  e86f0a0000             -call 0x4475a0
    cpu.esp -= 4;
    nfs3hp::load::listReplays(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00446b31  a1c0915500             -mov eax, dword ptr [0x5591c0]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5607872) /* 0x5591c0 */);
    // 00446b36  b903000000             -mov ecx, 3
    cpu.ecx = 3 /*0x3*/;
    // 00446b3b  8b504c                 -mov edx, dword ptr [eax + 0x4c]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(76) /* 0x4c */);
    // 00446b3e  890dbc915500           -mov dword ptr [0x5591bc], ecx
    app->getMemory<x86::reg32>(x86::reg32(5607868) /* 0x5591bc */) = cpu.ecx;
    // 00446b44  e857060000             -call 0x4471a0
    cpu.esp -= 4;
    sub_4471a0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00446b49  b802000000             -mov eax, 2
    cpu.eax = 2 /*0x2*/;
    // 00446b4e  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446b4f  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446b50  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446b51  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x8b 0xc0 */
void Application::sub_446b60(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00446b60  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00446b61  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00446b62  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00446b63  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00446b65  8b15c0915500           -mov edx, dword ptr [0x5591c0]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5607872) /* 0x5591c0 */);
    // 00446b6b  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 00446b6d  7506                   -jne 0x446b75
    if (!cpu.flags.zf)
    {
        goto L_0x00446b75;
    }
    // 00446b6f  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00446b71  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446b72  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446b73  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446b74  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x00446b75:
    // 00446b75  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 00446b77  ba148c5300             -mov edx, 0x538c14
    cpu.edx = 5475348 /*0x538c14*/;
    // 00446b7c  e81f0a0000             -call 0x4475a0
    cpu.esp -= 4;
    nfs3hp::load::listReplays(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00446b81  a1c0915500             -mov eax, dword ptr [0x5591c0]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5607872) /* 0x5591c0 */);
    // 00446b86  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 00446b88  8b504c                 -mov edx, dword ptr [eax + 0x4c]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(76) /* 0x4c */);
    // 00446b8b  890dbc915500           -mov dword ptr [0x5591bc], ecx
    app->getMemory<x86::reg32>(x86::reg32(5607868) /* 0x5591bc */) = cpu.ecx;
    // 00446b91  e80a060000             -call 0x4471a0
    cpu.esp -= 4;
    sub_4471a0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00446b96  b802000000             -mov eax, 2
    cpu.eax = 2 /*0x2*/;
    // 00446b9b  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446b9c  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446b9d  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446b9e  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x90 */
void Application::sub_446ba0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00446ba0  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00446ba1  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00446ba2  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00446ba3  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00446ba5  8b15c0915500           -mov edx, dword ptr [0x5591c0]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5607872) /* 0x5591c0 */);
    // 00446bab  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 00446bad  7506                   -jne 0x446bb5
    if (!cpu.flags.zf)
    {
        goto L_0x00446bb5;
    }
    // 00446baf  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00446bb1  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446bb2  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446bb3  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446bb4  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x00446bb5:
    // 00446bb5  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 00446bb7  baec8b5300             -mov edx, 0x538bec
    cpu.edx = 5475308 /*0x538bec*/;
    // 00446bbc  e8df090000             -call 0x4475a0
    cpu.esp -= 4;
    nfs3hp::load::listReplays(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00446bc1  a1c0915500             -mov eax, dword ptr [0x5591c0]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5607872) /* 0x5591c0 */);
    // 00446bc6  b901000000             -mov ecx, 1
    cpu.ecx = 1 /*0x1*/;
    // 00446bcb  8b504c                 -mov edx, dword ptr [eax + 0x4c]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(76) /* 0x4c */);
    // 00446bce  890dbc915500           -mov dword ptr [0x5591bc], ecx
    app->getMemory<x86::reg32>(x86::reg32(5607868) /* 0x5591bc */) = cpu.ecx;
    // 00446bd4  e8c7050000             -call 0x4471a0
    cpu.esp -= 4;
    sub_4471a0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00446bd9  b802000000             -mov eax, 2
    cpu.eax = 2 /*0x2*/;
    // 00446bde  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446bdf  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446be0  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446be1  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x8b 0xc0 */
void Application::sub_446bf0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00446bf0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00446bf1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00446bf2  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00446bf3  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00446bf4  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00446bf6  b841000000             -mov eax, 0x41
    cpu.eax = 65 /*0x41*/;
    // 00446bfb  b901000000             -mov ecx, 1
    cpu.ecx = 1 /*0x1*/;
    // 00446c00  bb00040000             -mov ebx, 0x400
    cpu.ebx = 1024 /*0x400*/;
    // 00446c05  e846ac0800             -call 0x4d1850
    cpu.esp -= 4;
    nfs3hp::port::text::languageText(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00446c0a  a3a0116600             -mov dword ptr [0x6611a0], eax
    app->getMemory<x86::reg32>(x86::reg32(6689184) /* 0x6611a0 */) = cpu.eax;
    // 00446c0f  b8c7010000             -mov eax, 0x1c7
    cpu.eax = 455 /*0x1c7*/;
    // 00446c14  baa0116600             -mov edx, 0x6611a0
    cpu.edx = 6689184 /*0x6611a0*/;
    // 00446c19  e832ac0800             -call 0x4d1850
    cpu.esp -= 4;
    nfs3hp::port::text::languageText(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00446c1e  6a00                   -push 0
    app->getMemory<x86::reg32>(cpu.esp-4) = 0 /*0x0*/;
    cpu.esp -= 4;
    // 00446c20  a3a4116600             -mov dword ptr [0x6611a4], eax
    app->getMemory<x86::reg32>(x86::reg32(6689188) /* 0x6611a4 */) = cpu.eax;
    // 00446c25  b802000000             -mov eax, 2
    cpu.eax = 2 /*0x2*/;
    // 00446c2a  e851deffff             -call 0x444a80
    cpu.esp -= 4;
    nfs3hp::frontend::dialogOpenMessage(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00446c2f  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446c30  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446c31  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446c32  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446c33  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 */
void Application::sub_446c50(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
  goto start;
dynamic_jump:
  switch(cpu.ip)
  {
start:
    // 00446c50  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00446c51  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00446c52  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00446c53  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00446c54  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00446c55  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00446c56  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00446c58  81ecfc000000           -sub esp, 0xfc
    (cpu.esp) -= x86::reg32(x86::sreg32(252 /*0xfc*/));
    // 00446c5e  81ed7a010000           -sub ebp, 0x17a
    (cpu.ebp) -= x86::reg32(x86::sreg32(378 /*0x17a*/));
    // 00446c64  8b15c0915500           -mov edx, dword ptr [0x5591c0]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5607872) /* 0x5591c0 */);
    // 00446c6a  bb02000000             -mov ebx, 2
    cpu.ebx = 2 /*0x2*/;
    // 00446c6f  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 00446c71  7507                   -jne 0x446c7a
    if (!cpu.flags.zf)
    {
        goto L_0x00446c7a;
    }
    // 00446c73  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
    // 00446c75  e9fb010000             -jmp 0x446e75
    goto L_0x00446e75;
L_0x00446c7a:
    // 00446c7a  8b7a4c                 -mov edi, dword ptr [edx + 0x4c]
    cpu.edi = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(76) /* 0x4c */);
    // 00446c7d  8b4a48                 -mov ecx, dword ptr [edx + 0x48]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(72) /* 0x48 */);
    // 00446c80  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 00446c82  39cf                   +cmp edi, ecx
    {
        x86::reg32 tmp1 = cpu.edi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ecx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00446c84  0f8de9010000           -jge 0x446e73
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00446e73;
    }
    // 00446c8a  85ff                   +test edi, edi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edi & cpu.edi));
    // 00446c8c  7d0f                   -jge 0x446c9d
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00446c9d;
    }
    // 00446c8e  31d0                   -xor eax, edx
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00446c90  8da57a010000           -lea esp, [ebp + 0x17a]
    cpu.esp = x86::reg32(cpu.ebp + x86::reg32(378) /* 0x17a */);
    // 00446c96  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446c97  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446c98  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446c99  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446c9a  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446c9b  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446c9c  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x00446c9d:
    // 00446c9d  8b4270                 -mov eax, dword ptr [edx + 0x70]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(112) /* 0x70 */);
    // 00446ca0  8b14f8                 -mov edx, dword ptr [eax + edi*8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + cpu.edi * 8);
    // 00446ca3  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00446ca4  68342f7a00             -push 0x7a2f34
    app->getMemory<x86::reg32>(cpu.esp-4) = 8007476 /*0x7a2f34*/;
    cpu.esp -= 4;
    // 00446ca9  681c8c5300             -push 0x538c1c
    app->getMemory<x86::reg32>(cpu.esp-4) = 5475356 /*0x538c1c*/;
    cpu.esp -= 4;
    // 00446cae  8d457e                 -lea eax, [ebp + 0x7e]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(126) /* 0x7e */);
    // 00446cb1  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00446cb2  e8d9890900             -call 0x4df690
    cpu.esp -= 4;
    nfs3hp::watcom::sprintf(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00446cb7  a1bc915500             -mov eax, dword ptr [0x5591bc]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5607868) /* 0x5591bc */);
    // 00446cbc  83c410                 -add esp, 0x10
    (cpu.esp) += x86::reg32(x86::sreg32(16 /*0x10*/));
    // 00446cbf  83f803                 +cmp eax, 3
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
    // 00446cc2  0f87ab010000           -ja 0x446e73
    if (!cpu.flags.cf && !cpu.flags.zf)
    {
        goto L_0x00446e73;
    }
    // 00446cc8  ff2485346c4400         -jmp dword ptr [eax*4 + 0x446c34]
    cpu.ip = app->getMemory<x86::reg32>(4484148 + cpu.eax * 4); goto dynamic_jump;
  case 0x00446ccf:
    // 00446ccf  b843010000             -mov eax, 0x143
    cpu.eax = 323 /*0x143*/;
    // 00446cd4  e877ab0800             -call 0x4d1850
    cpu.esp -= 4;
    nfs3hp::port::text::languageText(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00446cd9  8b3dc0915500           -mov edi, dword ptr [0x5591c0]
    cpu.edi = app->getMemory<x86::reg32>(x86::reg32(5607872) /* 0x5591c0 */);
    // 00446cdf  8b574c                 -mov edx, dword ptr [edi + 0x4c]
    cpu.edx = app->getMemory<x86::reg32>(cpu.edi + x86::reg32(76) /* 0x4c */);
    // 00446ce2  8b7f70                 -mov edi, dword ptr [edi + 0x70]
    cpu.edi = app->getMemory<x86::reg32>(cpu.edi + x86::reg32(112) /* 0x70 */);
    // 00446ce5  8b3cd7                 -mov edi, dword ptr [edi + edx*8]
    cpu.edi = app->getMemory<x86::reg32>(cpu.edi + cpu.edx * 8);
    // 00446ce8  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 00446cea  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 00446cec  e81f760a00             -call 0x4ee310
    cpu.esp -= 4;
    nfs3hp::watcom::strcmp(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00446cf1  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00446cf3  7507                   -jne 0x446cfc
    if (!cpu.flags.zf)
    {
        goto L_0x00446cfc;
    }
    // 00446cf5  30e4                   +xor ah, ah
    cpu.clear_co();
    cpu.set_szp((cpu.ah ^= x86::reg8(x86::sreg8(cpu.ah))));
    // 00446cf7  88657e                 -mov byte ptr [ebp + 0x7e], ah
    app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(126) /* 0x7e */) = cpu.ah;
    // 00446cfa  eb30                   -jmp 0x446d2c
    goto L_0x00446d2c;
L_0x00446cfc:
    // 00446cfc  807d7e00               +cmp byte ptr [ebp + 0x7e], 0
    {
        x86::reg8 tmp1 = app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(126) /* 0x7e */);
        x86::reg8 tmp2 = x86::reg8(x86::sreg8(0 /*0x0*/));
        x86::reg8 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 7);
        cpu.flags.of ^= 1 & (result >> 7);
        cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
        cpu.set_szp(result);
    }
    // 00446d00  742a                   -je 0x446d2c
    if (cpu.flags.zf)
    {
        goto L_0x00446d2c;
    }
    // 00446d02  be148c5300             -mov esi, 0x538c14
    cpu.esi = 5475348 /*0x538c14*/;
    // 00446d07  8d7d7e                 -lea edi, [ebp + 0x7e]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(126) /* 0x7e */);
    // 00446d0a  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00446d0b  2bc9                   +sub ecx, ecx
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
    // 00446d0d  49                     +dec ecx
    {
        x86::reg32& tmp = cpu.ecx;
        cpu.flags.of = 1 & (tmp >> 31);
        tmp--;
        cpu.flags.of &= ~(1 & (tmp >> 31));
        cpu.set_szp(tmp);
    }
    // 00446d0e  b000                   -mov al, 0
    cpu.al = 0 /*0x0*/;
    // 00446d10  f2ae                   -repne scasb al, byte ptr es:[edi]
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
    // 00446d12  4f                     -dec edi
    (cpu.edi)--;
L_0x00446d13:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00446d13  8a06                   -mov al, byte ptr [esi]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi);
    // 00446d15  8807                   -mov byte ptr [edi], al
    app->getMemory<x86::reg8>(cpu.edi) = cpu.al;
    // 00446d17  3c00                   +cmp al, 0
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
    // 00446d19  7410                   -je 0x446d2b
    if (cpu.flags.zf)
    {
        goto L_0x00446d2b;
    }
    // 00446d1b  8a4601                 -mov al, byte ptr [esi + 1]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi + x86::reg32(1) /* 0x1 */);
    // 00446d1e  83c602                 -add esi, 2
    (cpu.esi) += x86::reg32(x86::sreg32(2 /*0x2*/));
    // 00446d21  884701                 -mov byte ptr [edi + 1], al
    app->getMemory<x86::reg8>(cpu.edi + x86::reg32(1) /* 0x1 */) = cpu.al;
    // 00446d24  83c702                 -add edi, 2
    (cpu.edi) += x86::reg32(x86::sreg32(2 /*0x2*/));
    // 00446d27  3c00                   +cmp al, 0
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
    // 00446d29  75e8                   -jne 0x446d13
    if (!cpu.flags.zf)
    {
        goto L_0x00446d13;
    }
L_0x00446d2b:
    // 00446d2b  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
L_0x00446d2c:
    // 00446d2c  8d457e                 -lea eax, [ebp + 0x7e]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(126) /* 0x7e */);
    // 00446d2f  e85cfcffff             -call 0x446990
    cpu.esp -= 4;
    nfs3hp::load::loadKeptReplay(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00446d34  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00446d36  740a                   -je 0x446d42
    if (cpu.flags.zf)
    {
        goto L_0x00446d42;
    }
    // 00446d38  bb07000000             -mov ebx, 7
    cpu.ebx = 7 /*0x7*/;
    // 00446d3d  e931010000             -jmp 0x446e73
    goto L_0x00446e73;
L_0x00446d42:
    // 00446d42  e8a9feffff             -call 0x446bf0
    cpu.esp -= 4;
    sub_446bf0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00446d47  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 00446d49  8da57a010000           -lea esp, [ebp + 0x17a]
    cpu.esp = x86::reg32(cpu.ebp + x86::reg32(378) /* 0x17a */);
    // 00446d4f  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446d50  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446d51  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446d52  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446d53  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446d54  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446d55  c3                     -ret 
    cpu.esp += 4;
    return;
  case 0x00446d56:
    // 00446d56  807d7e00               +cmp byte ptr [ebp + 0x7e], 0
    {
        x86::reg8 tmp1 = app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(126) /* 0x7e */);
        x86::reg8 tmp2 = x86::reg8(x86::sreg8(0 /*0x0*/));
        x86::reg8 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 7);
        cpu.flags.of ^= 1 & (result >> 7);
        cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
        cpu.set_szp(result);
    }
    // 00446d5a  742a                   -je 0x446d86
    if (cpu.flags.zf)
    {
        goto L_0x00446d86;
    }
    // 00446d5c  be108c5300             -mov esi, 0x538c10
    cpu.esi = 5475344 /*0x538c10*/;
    // 00446d61  8d7d7e                 -lea edi, [ebp + 0x7e]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(126) /* 0x7e */);
    // 00446d64  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00446d65  2bc9                   +sub ecx, ecx
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
    // 00446d67  49                     +dec ecx
    {
        x86::reg32& tmp = cpu.ecx;
        cpu.flags.of = 1 & (tmp >> 31);
        tmp--;
        cpu.flags.of &= ~(1 & (tmp >> 31));
        cpu.set_szp(tmp);
    }
    // 00446d68  b000                   -mov al, 0
    cpu.al = 0 /*0x0*/;
    // 00446d6a  f2ae                   -repne scasb al, byte ptr es:[edi]
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
    // 00446d6c  4f                     -dec edi
    (cpu.edi)--;
L_0x00446d6d:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00446d6d  8a06                   -mov al, byte ptr [esi]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi);
    // 00446d6f  8807                   -mov byte ptr [edi], al
    app->getMemory<x86::reg8>(cpu.edi) = cpu.al;
    // 00446d71  3c00                   +cmp al, 0
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
    // 00446d73  7410                   -je 0x446d85
    if (cpu.flags.zf)
    {
        goto L_0x00446d85;
    }
    // 00446d75  8a4601                 -mov al, byte ptr [esi + 1]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi + x86::reg32(1) /* 0x1 */);
    // 00446d78  83c602                 -add esi, 2
    (cpu.esi) += x86::reg32(x86::sreg32(2 /*0x2*/));
    // 00446d7b  884701                 -mov byte ptr [edi + 1], al
    app->getMemory<x86::reg8>(cpu.edi + x86::reg32(1) /* 0x1 */) = cpu.al;
    // 00446d7e  83c702                 -add edi, 2
    (cpu.edi) += x86::reg32(x86::sreg32(2 /*0x2*/));
    // 00446d81  3c00                   +cmp al, 0
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
    // 00446d83  75e8                   -jne 0x446d6d
    if (!cpu.flags.zf)
    {
        goto L_0x00446d6d;
    }
L_0x00446d85:
    // 00446d85  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
L_0x00446d86:
    // 00446d86  8d457e                 -lea eax, [ebp + 0x7e]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(126) /* 0x7e */);
    // 00446d89  e872faffff             -call 0x446800
    cpu.esp -= 4;
    sub_446800(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00446d8e  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00446d90  7414                   -je 0x446da6
    if (cpu.flags.zf)
    {
        goto L_0x00446da6;
    }
    // 00446d92  bb06000000             -mov ebx, 6
    cpu.ebx = 6 /*0x6*/;
    // 00446d97  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 00446d99  8da57a010000           -lea esp, [ebp + 0x17a]
    cpu.esp = x86::reg32(cpu.ebp + x86::reg32(378) /* 0x17a */);
    // 00446d9f  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446da0  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446da1  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446da2  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446da3  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446da4  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446da5  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x00446da6:
    // 00446da6  e845feffff             -call 0x446bf0
    cpu.esp -= 4;
    sub_446bf0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00446dab  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 00446dad  8da57a010000           -lea esp, [ebp + 0x17a]
    cpu.esp = x86::reg32(cpu.ebp + x86::reg32(378) /* 0x17a */);
    // 00446db3  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446db4  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446db5  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446db6  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446db7  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446db8  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446db9  c3                     -ret 
    cpu.esp += 4;
    return;
  case 0x00446dba:
    // 00446dba  807d7e00               +cmp byte ptr [ebp + 0x7e], 0
    {
        x86::reg8 tmp1 = app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(126) /* 0x7e */);
        x86::reg8 tmp2 = x86::reg8(x86::sreg8(0 /*0x0*/));
        x86::reg8 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 7);
        cpu.flags.of ^= 1 & (result >> 7);
        cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
        cpu.set_szp(result);
    }
    // 00446dbe  742a                   -je 0x446dea
    if (cpu.flags.zf)
    {
        goto L_0x00446dea;
    }
    // 00446dc0  be188c5300             -mov esi, 0x538c18
    cpu.esi = 5475352 /*0x538c18*/;
    // 00446dc5  8d7d7e                 -lea edi, [ebp + 0x7e]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(126) /* 0x7e */);
    // 00446dc8  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00446dc9  2bc9                   +sub ecx, ecx
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
    // 00446dcb  49                     +dec ecx
    {
        x86::reg32& tmp = cpu.ecx;
        cpu.flags.of = 1 & (tmp >> 31);
        tmp--;
        cpu.flags.of &= ~(1 & (tmp >> 31));
        cpu.set_szp(tmp);
    }
    // 00446dcc  b000                   -mov al, 0
    cpu.al = 0 /*0x0*/;
    // 00446dce  f2ae                   -repne scasb al, byte ptr es:[edi]
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
    // 00446dd0  4f                     -dec edi
    (cpu.edi)--;
L_0x00446dd1:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00446dd1  8a06                   -mov al, byte ptr [esi]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi);
    // 00446dd3  8807                   -mov byte ptr [edi], al
    app->getMemory<x86::reg8>(cpu.edi) = cpu.al;
    // 00446dd5  3c00                   +cmp al, 0
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
    // 00446dd7  7410                   -je 0x446de9
    if (cpu.flags.zf)
    {
        goto L_0x00446de9;
    }
    // 00446dd9  8a4601                 -mov al, byte ptr [esi + 1]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi + x86::reg32(1) /* 0x1 */);
    // 00446ddc  83c602                 -add esi, 2
    (cpu.esi) += x86::reg32(x86::sreg32(2 /*0x2*/));
    // 00446ddf  884701                 -mov byte ptr [edi + 1], al
    app->getMemory<x86::reg8>(cpu.edi + x86::reg32(1) /* 0x1 */) = cpu.al;
    // 00446de2  83c702                 -add edi, 2
    (cpu.edi) += x86::reg32(x86::sreg32(2 /*0x2*/));
    // 00446de5  3c00                   +cmp al, 0
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
    // 00446de7  75e8                   -jne 0x446dd1
    if (!cpu.flags.zf)
    {
        goto L_0x00446dd1;
    }
L_0x00446de9:
    // 00446de9  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
L_0x00446dea:
    // 00446dea  8d457e                 -lea eax, [ebp + 0x7e]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(126) /* 0x7e */);
    // 00446ded  e8eef7ffff             -call 0x4465e0
    cpu.esp -= 4;
    sub_4465e0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00446df2  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00446df4  7414                   -je 0x446e0a
    if (cpu.flags.zf)
    {
        goto L_0x00446e0a;
    }
    // 00446df6  bb06000000             -mov ebx, 6
    cpu.ebx = 6 /*0x6*/;
    // 00446dfb  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 00446dfd  8da57a010000           -lea esp, [ebp + 0x17a]
    cpu.esp = x86::reg32(cpu.ebp + x86::reg32(378) /* 0x17a */);
    // 00446e03  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446e04  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446e05  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446e06  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446e07  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446e08  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446e09  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x00446e0a:
    // 00446e0a  e8e1fdffff             -call 0x446bf0
    cpu.esp -= 4;
    sub_446bf0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00446e0f  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 00446e11  8da57a010000           -lea esp, [ebp + 0x17a]
    cpu.esp = x86::reg32(cpu.ebp + x86::reg32(378) /* 0x17a */);
    // 00446e17  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446e18  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446e19  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446e1a  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446e1b  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446e1c  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446e1d  c3                     -ret 
    cpu.esp += 4;
    return;
  case 0x00446e1e:
    // 00446e1e  807d7e00               +cmp byte ptr [ebp + 0x7e], 0
    {
        x86::reg8 tmp1 = app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(126) /* 0x7e */);
        x86::reg8 tmp2 = x86::reg8(x86::sreg8(0 /*0x0*/));
        x86::reg8 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 7);
        cpu.flags.of ^= 1 & (result >> 7);
        cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
        cpu.set_szp(result);
    }
    // 00446e22  742a                   -je 0x446e4e
    if (cpu.flags.zf)
    {
        goto L_0x00446e4e;
    }
    // 00446e24  beec8b5300             -mov esi, 0x538bec
    cpu.esi = 5475308 /*0x538bec*/;
    // 00446e29  8d7d7e                 -lea edi, [ebp + 0x7e]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(126) /* 0x7e */);
    // 00446e2c  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00446e2d  2bc9                   +sub ecx, ecx
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
    // 00446e2f  49                     +dec ecx
    {
        x86::reg32& tmp = cpu.ecx;
        cpu.flags.of = 1 & (tmp >> 31);
        tmp--;
        cpu.flags.of &= ~(1 & (tmp >> 31));
        cpu.set_szp(tmp);
    }
    // 00446e30  b000                   -mov al, 0
    cpu.al = 0 /*0x0*/;
    // 00446e32  f2ae                   -repne scasb al, byte ptr es:[edi]
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
    // 00446e34  4f                     -dec edi
    (cpu.edi)--;
L_0x00446e35:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00446e35  8a06                   -mov al, byte ptr [esi]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi);
    // 00446e37  8807                   -mov byte ptr [edi], al
    app->getMemory<x86::reg8>(cpu.edi) = cpu.al;
    // 00446e39  3c00                   +cmp al, 0
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
    // 00446e3b  7410                   -je 0x446e4d
    if (cpu.flags.zf)
    {
        goto L_0x00446e4d;
    }
    // 00446e3d  8a4601                 -mov al, byte ptr [esi + 1]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi + x86::reg32(1) /* 0x1 */);
    // 00446e40  83c602                 -add esi, 2
    (cpu.esi) += x86::reg32(x86::sreg32(2 /*0x2*/));
    // 00446e43  884701                 -mov byte ptr [edi + 1], al
    app->getMemory<x86::reg8>(cpu.edi + x86::reg32(1) /* 0x1 */) = cpu.al;
    // 00446e46  83c702                 -add edi, 2
    (cpu.edi) += x86::reg32(x86::sreg32(2 /*0x2*/));
    // 00446e49  3c00                   +cmp al, 0
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
    // 00446e4b  75e8                   -jne 0x446e35
    if (!cpu.flags.zf)
    {
        goto L_0x00446e35;
    }
L_0x00446e4d:
    // 00446e4d  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
L_0x00446e4e:
    // 00446e4e  8d457e                 -lea eax, [ebp + 0x7e]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(126) /* 0x7e */);
    // 00446e51  e84af8ffff             -call 0x4466a0
    cpu.esp -= 4;
    sub_4466a0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00446e56  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00446e58  7414                   -je 0x446e6e
    if (cpu.flags.zf)
    {
        goto L_0x00446e6e;
    }
    // 00446e5a  bb06000000             -mov ebx, 6
    cpu.ebx = 6 /*0x6*/;
    // 00446e5f  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 00446e61  8da57a010000           -lea esp, [ebp + 0x17a]
    cpu.esp = x86::reg32(cpu.ebp + x86::reg32(378) /* 0x17a */);
    // 00446e67  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446e68  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446e69  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446e6a  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446e6b  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446e6c  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446e6d  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x00446e6e:
    // 00446e6e  e87dfdffff             -call 0x446bf0
    cpu.esp -= 4;
    sub_446bf0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00446e73:
    // 00446e73  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
L_0x00446e75:
    // 00446e75  8da57a010000           -lea esp, [ebp + 0x17a]
    cpu.esp = x86::reg32(cpu.ebp + x86::reg32(378) /* 0x17a */);
    // 00446e7b  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446e7c  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446e7d  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446e7e  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446e7f  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446e80  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446e81  c3                     -ret 
    cpu.esp += 4;
    return;
  default:
    NFS2_ASSERT(false);
  }
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 */
void Application::sub_446ea0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
  goto start;
dynamic_jump:
  switch(cpu.ip)
  {
start:
    // 00446ea0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00446ea1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00446ea2  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00446ea3  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00446ea4  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00446ea5  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00446ea6  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00446ea8  a1c0915500             -mov eax, dword ptr [0x5591c0]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5607872) /* 0x5591c0 */);
    // 00446ead  8b504c                 -mov edx, dword ptr [eax + 0x4c]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(76) /* 0x4c */);
    // 00446eb0  3b5048                 +cmp edx, dword ptr [eax + 0x48]
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.eax + x86::reg32(72) /* 0x48 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00446eb3  7c0d                   -jl 0x446ec2
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x00446ec2;
    }
    // 00446eb5  30e4                   +xor ah, ah
    cpu.clear_co();
    cpu.set_szp((cpu.ah ^= x86::reg8(x86::sreg8(cpu.ah))));
    // 00446eb7  8825a0106600           -mov byte ptr [0x6610a0], ah
    app->getMemory<x86::reg8>(x86::reg32(6688928) /* 0x6610a0 */) = cpu.ah;
    // 00446ebd  e924010000             -jmp 0x446fe6
    goto L_0x00446fe6;
L_0x00446ec2:
    // 00446ec2  8b4070                 -mov eax, dword ptr [eax + 0x70]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(112) /* 0x70 */);
    // 00446ec5  8b1cd0                 -mov ebx, dword ptr [eax + edx*8]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.eax + cpu.edx * 8);
    // 00446ec8  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00446ec9  68342f7a00             -push 0x7a2f34
    app->getMemory<x86::reg32>(cpu.esp-4) = 8007476 /*0x7a2f34*/;
    cpu.esp -= 4;
    // 00446ece  681c8c5300             -push 0x538c1c
    app->getMemory<x86::reg32>(cpu.esp-4) = 5475356 /*0x538c1c*/;
    cpu.esp -= 4;
    // 00446ed3  68a0106600             -push 0x6610a0
    app->getMemory<x86::reg32>(cpu.esp-4) = 6688928 /*0x6610a0*/;
    cpu.esp -= 4;
    // 00446ed8  e8b3870900             -call 0x4df690
    cpu.esp -= 4;
    nfs3hp::watcom::sprintf(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00446edd  a1bc915500             -mov eax, dword ptr [0x5591bc]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5607868) /* 0x5591bc */);
    // 00446ee2  83c410                 -add esp, 0x10
    (cpu.esp) += x86::reg32(x86::sreg32(16 /*0x10*/));
    // 00446ee5  83f803                 +cmp eax, 3
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
    // 00446ee8  0f87eb000000           -ja 0x446fd9
    if (!cpu.flags.cf && !cpu.flags.zf)
    {
        goto L_0x00446fd9;
    }
    // 00446eee  ff2485846e4400         -jmp dword ptr [eax*4 + 0x446e84]
    cpu.ip = app->getMemory<x86::reg32>(4484740 + cpu.eax * 4); goto dynamic_jump;
  case 0x00446ef5:
    // 00446ef5  be148c5300             -mov esi, 0x538c14
    cpu.esi = 5475348 /*0x538c14*/;
    // 00446efa  bfa0106600             -mov edi, 0x6610a0
    cpu.edi = 6688928 /*0x6610a0*/;
    // 00446eff  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00446f00  2bc9                   +sub ecx, ecx
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
    // 00446f02  49                     +dec ecx
    {
        x86::reg32& tmp = cpu.ecx;
        cpu.flags.of = 1 & (tmp >> 31);
        tmp--;
        cpu.flags.of &= ~(1 & (tmp >> 31));
        cpu.set_szp(tmp);
    }
    // 00446f03  b000                   -mov al, 0
    cpu.al = 0 /*0x0*/;
    // 00446f05  f2ae                   -repne scasb al, byte ptr es:[edi]
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
    // 00446f07  4f                     -dec edi
    (cpu.edi)--;
L_0x00446f08:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00446f08  8a06                   -mov al, byte ptr [esi]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi);
    // 00446f0a  8807                   -mov byte ptr [edi], al
    app->getMemory<x86::reg8>(cpu.edi) = cpu.al;
    // 00446f0c  3c00                   +cmp al, 0
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
    // 00446f0e  7410                   -je 0x446f20
    if (cpu.flags.zf)
    {
        goto L_0x00446f20;
    }
    // 00446f10  8a4601                 -mov al, byte ptr [esi + 1]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi + x86::reg32(1) /* 0x1 */);
    // 00446f13  83c602                 -add esi, 2
    (cpu.esi) += x86::reg32(x86::sreg32(2 /*0x2*/));
    // 00446f16  884701                 -mov byte ptr [edi + 1], al
    app->getMemory<x86::reg8>(cpu.edi + x86::reg32(1) /* 0x1 */) = cpu.al;
    // 00446f19  83c702                 -add edi, 2
    (cpu.edi) += x86::reg32(x86::sreg32(2 /*0x2*/));
    // 00446f1c  3c00                   +cmp al, 0
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
    // 00446f1e  75e8                   -jne 0x446f08
    if (!cpu.flags.zf)
    {
        goto L_0x00446f08;
    }
L_0x00446f20:
    // 00446f20  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446f21  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 00446f23  ba148c5300             -mov edx, 0x538c14
    cpu.edx = 5475348 /*0x538c14*/;
    // 00446f28  e99d000000             -jmp 0x446fca
    goto L_0x00446fca;
  case 0x00446f2d:
    // 00446f2d  be108c5300             -mov esi, 0x538c10
    cpu.esi = 5475344 /*0x538c10*/;
    // 00446f32  bfa0106600             -mov edi, 0x6610a0
    cpu.edi = 6688928 /*0x6610a0*/;
    // 00446f37  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00446f38  2bc9                   +sub ecx, ecx
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
    // 00446f3a  49                     +dec ecx
    {
        x86::reg32& tmp = cpu.ecx;
        cpu.flags.of = 1 & (tmp >> 31);
        tmp--;
        cpu.flags.of &= ~(1 & (tmp >> 31));
        cpu.set_szp(tmp);
    }
    // 00446f3b  b000                   -mov al, 0
    cpu.al = 0 /*0x0*/;
    // 00446f3d  f2ae                   -repne scasb al, byte ptr es:[edi]
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
    // 00446f3f  4f                     -dec edi
    (cpu.edi)--;
L_0x00446f40:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00446f40  8a06                   -mov al, byte ptr [esi]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi);
    // 00446f42  8807                   -mov byte ptr [edi], al
    app->getMemory<x86::reg8>(cpu.edi) = cpu.al;
    // 00446f44  3c00                   +cmp al, 0
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
    // 00446f46  7410                   -je 0x446f58
    if (cpu.flags.zf)
    {
        goto L_0x00446f58;
    }
    // 00446f48  8a4601                 -mov al, byte ptr [esi + 1]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi + x86::reg32(1) /* 0x1 */);
    // 00446f4b  83c602                 -add esi, 2
    (cpu.esi) += x86::reg32(x86::sreg32(2 /*0x2*/));
    // 00446f4e  884701                 -mov byte ptr [edi + 1], al
    app->getMemory<x86::reg8>(cpu.edi + x86::reg32(1) /* 0x1 */) = cpu.al;
    // 00446f51  83c702                 -add edi, 2
    (cpu.edi) += x86::reg32(x86::sreg32(2 /*0x2*/));
    // 00446f54  3c00                   +cmp al, 0
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
    // 00446f56  75e8                   -jne 0x446f40
    if (!cpu.flags.zf)
    {
        goto L_0x00446f40;
    }
L_0x00446f58:
    // 00446f58  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446f59  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 00446f5b  ba108c5300             -mov edx, 0x538c10
    cpu.edx = 5475344 /*0x538c10*/;
    // 00446f60  eb68                   -jmp 0x446fca
    goto L_0x00446fca;
  case 0x00446f62:
    // 00446f62  be188c5300             -mov esi, 0x538c18
    cpu.esi = 5475352 /*0x538c18*/;
    // 00446f67  bfa0106600             -mov edi, 0x6610a0
    cpu.edi = 6688928 /*0x6610a0*/;
    // 00446f6c  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00446f6d  2bc9                   +sub ecx, ecx
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
    // 00446f6f  49                     +dec ecx
    {
        x86::reg32& tmp = cpu.ecx;
        cpu.flags.of = 1 & (tmp >> 31);
        tmp--;
        cpu.flags.of &= ~(1 & (tmp >> 31));
        cpu.set_szp(tmp);
    }
    // 00446f70  b000                   -mov al, 0
    cpu.al = 0 /*0x0*/;
    // 00446f72  f2ae                   -repne scasb al, byte ptr es:[edi]
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
    // 00446f74  4f                     -dec edi
    (cpu.edi)--;
L_0x00446f75:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00446f75  8a06                   -mov al, byte ptr [esi]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi);
    // 00446f77  8807                   -mov byte ptr [edi], al
    app->getMemory<x86::reg8>(cpu.edi) = cpu.al;
    // 00446f79  3c00                   +cmp al, 0
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
    // 00446f7b  7410                   -je 0x446f8d
    if (cpu.flags.zf)
    {
        goto L_0x00446f8d;
    }
    // 00446f7d  8a4601                 -mov al, byte ptr [esi + 1]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi + x86::reg32(1) /* 0x1 */);
    // 00446f80  83c602                 -add esi, 2
    (cpu.esi) += x86::reg32(x86::sreg32(2 /*0x2*/));
    // 00446f83  884701                 -mov byte ptr [edi + 1], al
    app->getMemory<x86::reg8>(cpu.edi + x86::reg32(1) /* 0x1 */) = cpu.al;
    // 00446f86  83c702                 -add edi, 2
    (cpu.edi) += x86::reg32(x86::sreg32(2 /*0x2*/));
    // 00446f89  3c00                   +cmp al, 0
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
    // 00446f8b  75e8                   -jne 0x446f75
    if (!cpu.flags.zf)
    {
        goto L_0x00446f75;
    }
L_0x00446f8d:
    // 00446f8d  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446f8e  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 00446f90  ba188c5300             -mov edx, 0x538c18
    cpu.edx = 5475352 /*0x538c18*/;
    // 00446f95  eb33                   -jmp 0x446fca
    goto L_0x00446fca;
  case 0x00446f97:
    // 00446f97  beec8b5300             -mov esi, 0x538bec
    cpu.esi = 5475308 /*0x538bec*/;
    // 00446f9c  bfa0106600             -mov edi, 0x6610a0
    cpu.edi = 6688928 /*0x6610a0*/;
    // 00446fa1  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00446fa2  2bc9                   +sub ecx, ecx
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
    // 00446fa4  49                     +dec ecx
    {
        x86::reg32& tmp = cpu.ecx;
        cpu.flags.of = 1 & (tmp >> 31);
        tmp--;
        cpu.flags.of &= ~(1 & (tmp >> 31));
        cpu.set_szp(tmp);
    }
    // 00446fa5  b000                   -mov al, 0
    cpu.al = 0 /*0x0*/;
    // 00446fa7  f2ae                   -repne scasb al, byte ptr es:[edi]
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
    // 00446fa9  4f                     -dec edi
    (cpu.edi)--;
L_0x00446faa:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00446faa  8a06                   -mov al, byte ptr [esi]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi);
    // 00446fac  8807                   -mov byte ptr [edi], al
    app->getMemory<x86::reg8>(cpu.edi) = cpu.al;
    // 00446fae  3c00                   +cmp al, 0
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
    // 00446fb0  7410                   -je 0x446fc2
    if (cpu.flags.zf)
    {
        goto L_0x00446fc2;
    }
    // 00446fb2  8a4601                 -mov al, byte ptr [esi + 1]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi + x86::reg32(1) /* 0x1 */);
    // 00446fb5  83c602                 -add esi, 2
    (cpu.esi) += x86::reg32(x86::sreg32(2 /*0x2*/));
    // 00446fb8  884701                 -mov byte ptr [edi + 1], al
    app->getMemory<x86::reg8>(cpu.edi + x86::reg32(1) /* 0x1 */) = cpu.al;
    // 00446fbb  83c702                 -add edi, 2
    (cpu.edi) += x86::reg32(x86::sreg32(2 /*0x2*/));
    // 00446fbe  3c00                   +cmp al, 0
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
    // 00446fc0  75e8                   -jne 0x446faa
    if (!cpu.flags.zf)
    {
        goto L_0x00446faa;
    }
L_0x00446fc2:
    // 00446fc2  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446fc3  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 00446fc5  baec8b5300             -mov edx, 0x538bec
    cpu.edx = 5475308 /*0x538bec*/;
L_0x00446fca:
    // 00446fca  e8d1b80900             -call 0x4e28a0
    cpu.esp -= 4;
    nfs3hp::watcom::unlink(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00446fcf  a1c0915500             -mov eax, dword ptr [0x5591c0]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5607872) /* 0x5591c0 */);
    // 00446fd4  e8c7050000             -call 0x4475a0
    cpu.esp -= 4;
    nfs3hp::load::listReplays(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00446fd9:
    // 00446fd9  a1c0915500             -mov eax, dword ptr [0x5591c0]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5607872) /* 0x5591c0 */);
    // 00446fde  8b504c                 -mov edx, dword ptr [eax + 0x4c]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(76) /* 0x4c */);
    // 00446fe1  e8ba010000             -call 0x4471a0
    cpu.esp -= 4;
    sub_4471a0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00446fe6:
    // 00446fe6  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446fe7  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446fe8  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446fe9  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446fea  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446feb  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00446fec  c3                     -ret 
    cpu.esp += 4;
    return;
  default:
    NFS2_ASSERT(false);
  }
}

/* align: skip 0x8d 0x40 0x00 */
void Application::sub_446ff0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00446ff0  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00446ff1  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00446ff2  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00446ff4  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00446ff6  e8c5d6ffff             -call 0x4446c0
    cpu.esp -= 4;
    nfs3hp::frontend::dialogFocusedButton(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00446ffb  c60200                 -mov byte ptr [edx], 0
    app->getMemory<x86::reg8>(cpu.edx) = 0 /*0x0*/;
    // 00446ffe  83f903                 +cmp ecx, 3
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
    // 00447001  7417                   -je 0x44701a
    if (cpu.flags.zf)
    {
        goto L_0x0044701a;
    }
    // 00447003  83f901                 +cmp ecx, 1
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
    // 00447006  7515                   -jne 0x44701d
    if (!cpu.flags.zf)
    {
        goto L_0x0044701d;
    }
    // 00447008  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0044700a  7609                   -jbe 0x447015
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x00447015;
    }
    // 0044700c  39c8                   +cmp eax, ecx
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
    // 0044700e  740a                   -je 0x44701a
    if (cpu.flags.zf)
    {
        goto L_0x0044701a;
    }
    // 00447010  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00447012  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00447013  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00447014  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x00447015:
    // 00447015  e886feffff             -call 0x446ea0
    cpu.esp -= 4;
    sub_446ea0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x0044701a:
    // 0044701a  c60201                 -mov byte ptr [edx], 1
    app->getMemory<x86::reg8>(cpu.edx) = 1 /*0x1*/;
L_0x0044701d:
    // 0044701d  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 0044701f  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00447020  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00447021  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x8b 0xc0 */
void Application::sub_447030(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00447030  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00447031  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00447032  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00447033  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00447034  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00447035  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00447036  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00447038  a1c0915500             -mov eax, dword ptr [0x5591c0]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5607872) /* 0x5591c0 */);
    // 0044703d  8b704c                 -mov esi, dword ptr [eax + 0x4c]
    cpu.esi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(76) /* 0x4c */);
    // 00447040  3b7048                 +cmp esi, dword ptr [eax + 0x48]
    {
        x86::reg32 tmp1 = cpu.esi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.eax + x86::reg32(72) /* 0x48 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00447043  7c0a                   -jl 0x44704f
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x0044704f;
    }
    // 00447045  30e4                   +xor ah, ah
    cpu.clear_co();
    cpu.set_szp((cpu.ah ^= x86::reg8(x86::sreg8(cpu.ah))));
    // 00447047  8825a0106600           -mov byte ptr [0x6610a0], ah
    app->getMemory<x86::reg8>(x86::reg32(6688928) /* 0x6610a0 */) = cpu.ah;
    // 0044704d  eb79                   -jmp 0x4470c8
    goto L_0x004470c8;
L_0x0044704f:
    // 0044704f  8b4070                 -mov eax, dword ptr [eax + 0x70]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(112) /* 0x70 */);
    // 00447052  bfa0106600             -mov edi, 0x6610a0
    cpu.edi = 6688928 /*0x6610a0*/;
    // 00447057  8b34f0                 -mov esi, dword ptr [eax + esi*8]
    cpu.esi = app->getMemory<x86::reg32>(cpu.eax + cpu.esi * 8);
    // 0044705a  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
L_0x0044705b:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 0044705b  8a06                   -mov al, byte ptr [esi]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi);
    // 0044705d  8807                   -mov byte ptr [edi], al
    app->getMemory<x86::reg8>(cpu.edi) = cpu.al;
    // 0044705f  3c00                   +cmp al, 0
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
    // 00447061  7410                   -je 0x447073
    if (cpu.flags.zf)
    {
        goto L_0x00447073;
    }
    // 00447063  8a4601                 -mov al, byte ptr [esi + 1]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi + x86::reg32(1) /* 0x1 */);
    // 00447066  83c602                 -add esi, 2
    (cpu.esi) += x86::reg32(x86::sreg32(2 /*0x2*/));
    // 00447069  884701                 -mov byte ptr [edi + 1], al
    app->getMemory<x86::reg8>(cpu.edi + x86::reg32(1) /* 0x1 */) = cpu.al;
    // 0044706c  83c702                 -add edi, 2
    (cpu.edi) += x86::reg32(x86::sreg32(2 /*0x2*/));
    // 0044706f  3c00                   +cmp al, 0
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
    // 00447071  75e8                   -jne 0x44705b
    if (!cpu.flags.zf)
    {
        goto L_0x0044705b;
    }
L_0x00447073:
    // 00447073  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00447074  b844010000             -mov eax, 0x144
    cpu.eax = 324 /*0x144*/;
    // 00447079  e8d2a70800             -call 0x4d1850
    cpu.esp -= 4;
    nfs3hp::port::text::languageText(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0044707e  a3a8116600             -mov dword ptr [0x6611a8], eax
    app->getMemory<x86::reg32>(x86::reg32(6689192) /* 0x6611a8 */) = cpu.eax;
    // 00447083  b8c4000000             -mov eax, 0xc4
    cpu.eax = 196 /*0xc4*/;
    // 00447088  893dac116600           -mov dword ptr [0x6611ac], edi
    app->getMemory<x86::reg32>(x86::reg32(6689196) /* 0x6611ac */) = cpu.edi;
    // 0044708e  e8bda70800             -call 0x4d1850
    cpu.esp -= 4;
    nfs3hp::port::text::languageText(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00447093  a3b0116600             -mov dword ptr [0x6611b0], eax
    app->getMemory<x86::reg32>(x86::reg32(6689200) /* 0x6611b0 */) = cpu.eax;
    // 00447098  b8c5000000             -mov eax, 0xc5
    cpu.eax = 197 /*0xc5*/;
    // 0044709d  e8aea70800             -call 0x4d1850
    cpu.esp -= 4;
    nfs3hp::port::text::languageText(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004470a2  68f06f4400             -push 0x446ff0
    app->getMemory<x86::reg32>(cpu.esp-4) = 4485104 /*0x446ff0*/;
    cpu.esp -= 4;
    // 004470a7  6a00                   -push 0
    app->getMemory<x86::reg32>(cpu.esp-4) = 0 /*0x0*/;
    cpu.esp -= 4;
    // 004470a9  b9b0116600             -mov ecx, 0x6611b0
    cpu.ecx = 6689200 /*0x6611b0*/;
    // 004470ae  6a01                   -push 1
    app->getMemory<x86::reg32>(cpu.esp-4) = 1 /*0x1*/;
    cpu.esp -= 4;
    // 004470b0  bb02000000             -mov ebx, 2
    cpu.ebx = 2 /*0x2*/;
    // 004470b5  baa8116600             -mov edx, 0x6611a8
    cpu.edx = 6689192 /*0x6611a8*/;
    // 004470ba  6a00                   -push 0
    app->getMemory<x86::reg32>(cpu.esp-4) = 0 /*0x0*/;
    cpu.esp -= 4;
    // 004470bc  a3b4116600             -mov dword ptr [0x6611b4], eax
    app->getMemory<x86::reg32>(x86::reg32(6689204) /* 0x6611b4 */) = cpu.eax;
    // 004470c1  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 004470c3  e808d6ffff             -call 0x4446d0
    cpu.esp -= 4;
    nfs3hp::frontend::dialogOpenQuestion(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x004470c8:
    // 004470c8  b802000000             -mov eax, 2
    cpu.eax = 2 /*0x2*/;
    // 004470cd  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004470ce  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004470cf  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004470d0  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004470d1  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004470d2  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004470d3  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 */
void Application::sub_4470e0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004470e0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004470e1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004470e2  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004470e3  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004470e4  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004470e5  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004470e6  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004470e8  81ec04010000           -sub esp, 0x104
    (cpu.esp) -= x86::reg32(x86::sreg32(260 /*0x104*/));
    // 004470ee  8b7804                 -mov edi, dword ptr [eax + 4]
    cpu.edi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 004470f1  8b7006                 -mov esi, dword ptr [eax + 6]
    cpu.esi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6) /* 0x6 */);
    // 004470f4  b8e0010000             -mov eax, 0x1e0
    cpu.eax = 480 /*0x1e0*/;
    // 004470f9  e852a70800             -call 0x4d1850
    cpu.esp -= 4;
    nfs3hp::port::text::languageText(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004470fe  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004470ff  68248c5300             -push 0x538c24
    app->getMemory<x86::reg32>(cpu.esp-4) = 5475364 /*0x538c24*/;
    cpu.esp -= 4;
    // 00447104  8d85fcfeffff           -lea eax, [ebp - 0x104]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-260) /* -0x104 */);
    // 0044710a  b912000000             -mov ecx, 0x12
    cpu.ecx = 18 /*0x12*/;
    // 0044710f  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00447110  c1ff10                 -sar edi, 0x10
    cpu.edi = x86::reg32(x86::sreg32(cpu.edi) >> (16 /*0x10*/ % 32));
    // 00447113  e878850900             -call 0x4df690
    cpu.esp -= 4;
    nfs3hp::watcom::sprintf(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00447118  83c40c                 -add esp, 0xc
    (cpu.esp) += x86::reg32(x86::sreg32(12 /*0xc*/));
    // 0044711b  c1fe10                 -sar esi, 0x10
    cpu.esi = x86::reg32(x86::sreg32(cpu.esi) >> (16 /*0x10*/ % 32));
    // 0044711e  83c70a                 -add edi, 0xa
    (cpu.edi) += x86::reg32(x86::sreg32(10 /*0xa*/));
    // 00447121  68ffbe5aff             -push 0xff5abeff
    app->getMemory<x86::reg32>(cpu.esp-4) = 4284137215 /*0xff5abeff*/;
    cpu.esp -= 4;
    // 00447126  89f3                   -mov ebx, esi
    cpu.ebx = cpu.esi;
    // 00447128  89fa                   -mov edx, edi
    cpu.edx = cpu.edi;
    // 0044712a  6a03                   -push 3
    app->getMemory<x86::reg32>(cpu.esp-4) = 3 /*0x3*/;
    cpu.esp -= 4;
    // 0044712c  8d85fcfeffff           -lea eax, [ebp - 0x104]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-260) /* -0x104 */);
    // 00447132  83c619                 -add esi, 0x19
    (cpu.esi) += x86::reg32(x86::sreg32(25 /*0x19*/));
    // 00447135  e856b00000             -call 0x452190
    cpu.esp -= 4;
    nfs3hp::port::text::drawMenuText(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0044713a  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 0044713c  83c70a                 +add edi, 0xa
    {
        x86::reg32& tmp1 = cpu.edi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(10 /*0xa*/));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 0044713f  8955fc                 -mov dword ptr [ebp - 4], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.edx;
    // 00447142  eb2a                   -jmp 0x44716e
    goto L_0x0044716e;
L_0x00447144:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00447144  68fd9d64ff             -push 0xff649dfd
    app->getMemory<x86::reg32>(cpu.esp-4) = 4284784125 /*0xff649dfd*/;
    cpu.esp -= 4;
    // 00447149  b912000000             -mov ecx, 0x12
    cpu.ecx = 18 /*0x12*/;
    // 0044714e  050c8d5500             -add eax, 0x558d0c
    (cpu.eax) += x86::reg32(x86::sreg32(5606668 /*0x558d0c*/));
    // 00447153  6a03                   -push 3
    app->getMemory<x86::reg32>(cpu.esp-4) = 3 /*0x3*/;
    cpu.esp -= 4;
    // 00447155  89f3                   -mov ebx, esi
    cpu.ebx = cpu.esi;
    // 00447157  89fa                   -mov edx, edi
    cpu.edx = cpu.edi;
    // 00447159  e832b00000             -call 0x452190
    cpu.esp -= 4;
    nfs3hp::port::text::drawMenuText(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x0044715e:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 0044715e  8b5dfc                 -mov ebx, dword ptr [ebp - 4]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00447161  43                     -inc ebx
    (cpu.ebx)++;
    // 00447162  83c614                 -add esi, 0x14
    (cpu.esi) += x86::reg32(x86::sreg32(20 /*0x14*/));
    // 00447165  895dfc                 -mov dword ptr [ebp - 4], ebx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.ebx;
    // 00447168  837dfc0a               +cmp dword ptr [ebp - 4], 0xa
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(10 /*0xa*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0044716c  7d18                   -jge 0x447186
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00447186;
    }
L_0x0044716e:
    // 0044716e  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00447171  c1e003                 -shl eax, 3
    cpu.eax <<= 3 /*0x3*/ % 32;
    // 00447174  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 00447176  c1e004                 -shl eax, 4
    cpu.eax <<= 4 /*0x4*/ % 32;
    // 00447179  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 0044717b  80b80c8d550000         +cmp byte ptr [eax + 0x558d0c], 0
    {
        x86::reg8 tmp1 = app->getMemory<x86::reg8>(cpu.eax + x86::reg32(5606668) /* 0x558d0c */);
        x86::reg8 tmp2 = x86::reg8(x86::sreg8(0 /*0x0*/));
        x86::reg8 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 7);
        cpu.flags.of ^= 1 & (result >> 7);
        cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
        cpu.set_szp(result);
    }
    // 00447182  75c0                   -jne 0x447144
    if (!cpu.flags.zf)
    {
        goto L_0x00447144;
    }
    // 00447184  ebd8                   -jmp 0x44715e
    goto L_0x0044715e;
L_0x00447186:
    // 00447186  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00447188  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00447189  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0044718a  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0044718b  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0044718c  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0044718d  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0044718e  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x90 */
void Application::sub_4471a0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
  goto start;
dynamic_jump:
  switch(cpu.ip)
  {
start:
    // 004471a0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004471a1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004471a2  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004471a3  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004471a4  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004471a5  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004471a7  81ecfc000000           -sub esp, 0xfc
    (cpu.esp) -= x86::reg32(x86::sreg32(252 /*0xfc*/));
    // 004471ad  81ed7a010000           -sub ebp, 0x17a
    (cpu.ebp) -= x86::reg32(x86::sreg32(378 /*0x17a*/));
    // 004471b3  bab0040000             -mov edx, 0x4b0
    cpu.edx = 1200 /*0x4b0*/;
    // 004471b8  b80c8d5500             -mov eax, 0x558d0c
    cpu.eax = 5606668 /*0x558d0c*/;
    // 004471bd  e84a950900             -call 0x4e070c
    cpu.esp -= 4;
    nfs3hp::fillZero(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004471c2  8b15c0915500           -mov edx, dword ptr [0x5591c0]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5607872) /* 0x5591c0 */);
    // 004471c8  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 004471ca  0f847e010000           -je 0x44734e
    if (cpu.flags.zf)
    {
        goto L_0x0044734e;
    }
    // 004471d0  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004471d2  8b524c                 -mov edx, dword ptr [edx + 0x4c]
    cpu.edx = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(76) /* 0x4c */);
    // 004471d5  3b5048                 +cmp edx, dword ptr [eax + 0x48]
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.eax + x86::reg32(72) /* 0x48 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004471d8  0f8d70010000           -jge 0x44734e
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x0044734e;
    }
    // 004471de  8b584c                 -mov ebx, dword ptr [eax + 0x4c]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(76) /* 0x4c */);
    // 004471e1  85db                   +test ebx, ebx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & cpu.ebx));
    // 004471e3  0f8c65010000           -jl 0x44734e
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x0044734e;
    }
    // 004471e9  89da                   -mov edx, ebx
    cpu.edx = cpu.ebx;
    // 004471eb  8b4070                 -mov eax, dword ptr [eax + 0x70]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(112) /* 0x70 */);
    // 004471ee  8b34d0                 -mov esi, dword ptr [eax + edx*8]
    cpu.esi = app->getMemory<x86::reg32>(cpu.eax + cpu.edx * 8);
    // 004471f1  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004471f2  68342f7a00             -push 0x7a2f34
    app->getMemory<x86::reg32>(cpu.esp-4) = 8007476 /*0x7a2f34*/;
    cpu.esp -= 4;
    // 004471f7  681c8c5300             -push 0x538c1c
    app->getMemory<x86::reg32>(cpu.esp-4) = 5475356 /*0x538c1c*/;
    cpu.esp -= 4;
    // 004471fc  8d457e                 -lea eax, [ebp + 0x7e]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(126) /* 0x7e */);
    // 004471ff  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 00447200  e88b840900             -call 0x4df690
    cpu.esp -= 4;
    nfs3hp::watcom::sprintf(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00447205  a1bc915500             -mov eax, dword ptr [0x5591bc]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5607868) /* 0x5591bc */);
    // 0044720a  83c410                 -add esp, 0x10
    (cpu.esp) += x86::reg32(x86::sreg32(16 /*0x10*/));
    // 0044720d  83f803                 +cmp eax, 3
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
    // 00447210  0f8738010000           -ja 0x44734e
    if (!cpu.flags.cf && !cpu.flags.zf)
    {
        goto L_0x0044734e;
    }
    // 00447216  ff248590714400         -jmp dword ptr [eax*4 + 0x447190]
    cpu.ip = app->getMemory<x86::reg32>(4485520 + cpu.eax * 4); goto dynamic_jump;
  case 0x0044721d:
    // 0044721d  b843010000             -mov eax, 0x143
    cpu.eax = 323 /*0x143*/;
    // 00447222  e829a60800             -call 0x4d1850
    cpu.esp -= 4;
    nfs3hp::port::text::languageText(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00447227  8b15c0915500           -mov edx, dword ptr [0x5591c0]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5607872) /* 0x5591c0 */);
    // 0044722d  8b7a4c                 -mov edi, dword ptr [edx + 0x4c]
    cpu.edi = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(76) /* 0x4c */);
    // 00447230  8b5270                 -mov edx, dword ptr [edx + 0x70]
    cpu.edx = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(112) /* 0x70 */);
    // 00447233  8b3cfa                 -mov edi, dword ptr [edx + edi*8]
    cpu.edi = app->getMemory<x86::reg32>(cpu.edx + cpu.edi * 8);
    // 00447236  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 00447238  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 0044723a  e8d1700a00             -call 0x4ee310
    cpu.esp -= 4;
    nfs3hp::watcom::strcmp(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0044723f  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00447241  7507                   -jne 0x44724a
    if (!cpu.flags.zf)
    {
        goto L_0x0044724a;
    }
    // 00447243  30e4                   +xor ah, ah
    cpu.clear_co();
    cpu.set_szp((cpu.ah ^= x86::reg8(x86::sreg8(cpu.ah))));
    // 00447245  88657e                 -mov byte ptr [ebp + 0x7e], ah
    app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(126) /* 0x7e */) = cpu.ah;
    // 00447248  eb30                   -jmp 0x44727a
    goto L_0x0044727a;
L_0x0044724a:
    // 0044724a  807d7e00               +cmp byte ptr [ebp + 0x7e], 0
    {
        x86::reg8 tmp1 = app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(126) /* 0x7e */);
        x86::reg8 tmp2 = x86::reg8(x86::sreg8(0 /*0x0*/));
        x86::reg8 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 7);
        cpu.flags.of ^= 1 & (result >> 7);
        cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
        cpu.set_szp(result);
    }
    // 0044724e  742a                   -je 0x44727a
    if (cpu.flags.zf)
    {
        goto L_0x0044727a;
    }
    // 00447250  be148c5300             -mov esi, 0x538c14
    cpu.esi = 5475348 /*0x538c14*/;
    // 00447255  8d7d7e                 -lea edi, [ebp + 0x7e]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(126) /* 0x7e */);
    // 00447258  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00447259  2bc9                   +sub ecx, ecx
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
    // 0044725b  49                     +dec ecx
    {
        x86::reg32& tmp = cpu.ecx;
        cpu.flags.of = 1 & (tmp >> 31);
        tmp--;
        cpu.flags.of &= ~(1 & (tmp >> 31));
        cpu.set_szp(tmp);
    }
    // 0044725c  b000                   -mov al, 0
    cpu.al = 0 /*0x0*/;
    // 0044725e  f2ae                   -repne scasb al, byte ptr es:[edi]
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
    // 00447260  4f                     -dec edi
    (cpu.edi)--;
L_0x00447261:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00447261  8a06                   -mov al, byte ptr [esi]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi);
    // 00447263  8807                   -mov byte ptr [edi], al
    app->getMemory<x86::reg8>(cpu.edi) = cpu.al;
    // 00447265  3c00                   +cmp al, 0
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
    // 00447267  7410                   -je 0x447279
    if (cpu.flags.zf)
    {
        goto L_0x00447279;
    }
    // 00447269  8a4601                 -mov al, byte ptr [esi + 1]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi + x86::reg32(1) /* 0x1 */);
    // 0044726c  83c602                 -add esi, 2
    (cpu.esi) += x86::reg32(x86::sreg32(2 /*0x2*/));
    // 0044726f  884701                 -mov byte ptr [edi + 1], al
    app->getMemory<x86::reg8>(cpu.edi + x86::reg32(1) /* 0x1 */) = cpu.al;
    // 00447272  83c702                 -add edi, 2
    (cpu.edi) += x86::reg32(x86::sreg32(2 /*0x2*/));
    // 00447275  3c00                   +cmp al, 0
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
    // 00447277  75e8                   -jne 0x447261
    if (!cpu.flags.zf)
    {
        goto L_0x00447261;
    }
L_0x00447279:
    // 00447279  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
L_0x0044727a:
    // 0044727a  8d457e                 -lea eax, [ebp + 0x7e]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(126) /* 0x7e */);
    // 0044727d  e8deedffff             -call 0x446060
    cpu.esp -= 4;
    nfs3hp::load::readReplayInfo(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00447282  8da57a010000           -lea esp, [ebp + 0x17a]
    cpu.esp = x86::reg32(cpu.ebp + x86::reg32(378) /* 0x17a */);
    // 00447288  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00447289  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0044728a  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0044728b  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0044728c  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0044728d  c3                     -ret 
    cpu.esp += 4;
    return;
  case 0x0044728e:
    // 0044728e  807d7e00               +cmp byte ptr [ebp + 0x7e], 0
    {
        x86::reg8 tmp1 = app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(126) /* 0x7e */);
        x86::reg8 tmp2 = x86::reg8(x86::sreg8(0 /*0x0*/));
        x86::reg8 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 7);
        cpu.flags.of ^= 1 & (result >> 7);
        cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
        cpu.set_szp(result);
    }
    // 00447292  742a                   -je 0x4472be
    if (cpu.flags.zf)
    {
        goto L_0x004472be;
    }
    // 00447294  be108c5300             -mov esi, 0x538c10
    cpu.esi = 5475344 /*0x538c10*/;
    // 00447299  8d7d7e                 -lea edi, [ebp + 0x7e]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(126) /* 0x7e */);
    // 0044729c  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 0044729d  2bc9                   +sub ecx, ecx
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
    // 0044729f  49                     +dec ecx
    {
        x86::reg32& tmp = cpu.ecx;
        cpu.flags.of = 1 & (tmp >> 31);
        tmp--;
        cpu.flags.of &= ~(1 & (tmp >> 31));
        cpu.set_szp(tmp);
    }
    // 004472a0  b000                   -mov al, 0
    cpu.al = 0 /*0x0*/;
    // 004472a2  f2ae                   -repne scasb al, byte ptr es:[edi]
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
    // 004472a4  4f                     -dec edi
    (cpu.edi)--;
L_0x004472a5:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004472a5  8a06                   -mov al, byte ptr [esi]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi);
    // 004472a7  8807                   -mov byte ptr [edi], al
    app->getMemory<x86::reg8>(cpu.edi) = cpu.al;
    // 004472a9  3c00                   +cmp al, 0
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
    // 004472ab  7410                   -je 0x4472bd
    if (cpu.flags.zf)
    {
        goto L_0x004472bd;
    }
    // 004472ad  8a4601                 -mov al, byte ptr [esi + 1]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi + x86::reg32(1) /* 0x1 */);
    // 004472b0  83c602                 -add esi, 2
    (cpu.esi) += x86::reg32(x86::sreg32(2 /*0x2*/));
    // 004472b3  884701                 -mov byte ptr [edi + 1], al
    app->getMemory<x86::reg8>(cpu.edi + x86::reg32(1) /* 0x1 */) = cpu.al;
    // 004472b6  83c702                 -add edi, 2
    (cpu.edi) += x86::reg32(x86::sreg32(2 /*0x2*/));
    // 004472b9  3c00                   +cmp al, 0
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
    // 004472bb  75e8                   -jne 0x4472a5
    if (!cpu.flags.zf)
    {
        goto L_0x004472a5;
    }
L_0x004472bd:
    // 004472bd  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
L_0x004472be:
    // 004472be  8d457e                 -lea eax, [ebp + 0x7e]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(126) /* 0x7e */);
    // 004472c1  e81af0ffff             -call 0x4462e0
    cpu.esp -= 4;
    sub_4462e0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004472c6  8da57a010000           -lea esp, [ebp + 0x17a]
    cpu.esp = x86::reg32(cpu.ebp + x86::reg32(378) /* 0x17a */);
    // 004472cc  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004472cd  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004472ce  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004472cf  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004472d0  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004472d1  c3                     -ret 
    cpu.esp += 4;
    return;
  case 0x004472d2:
    // 004472d2  807d7e00               +cmp byte ptr [ebp + 0x7e], 0
    {
        x86::reg8 tmp1 = app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(126) /* 0x7e */);
        x86::reg8 tmp2 = x86::reg8(x86::sreg8(0 /*0x0*/));
        x86::reg8 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 7);
        cpu.flags.of ^= 1 & (result >> 7);
        cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
        cpu.set_szp(result);
    }
    // 004472d6  742a                   -je 0x447302
    if (cpu.flags.zf)
    {
        goto L_0x00447302;
    }
    // 004472d8  be188c5300             -mov esi, 0x538c18
    cpu.esi = 5475352 /*0x538c18*/;
    // 004472dd  8d7d7e                 -lea edi, [ebp + 0x7e]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(126) /* 0x7e */);
    // 004472e0  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004472e1  2bc9                   +sub ecx, ecx
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
    // 004472e3  49                     +dec ecx
    {
        x86::reg32& tmp = cpu.ecx;
        cpu.flags.of = 1 & (tmp >> 31);
        tmp--;
        cpu.flags.of &= ~(1 & (tmp >> 31));
        cpu.set_szp(tmp);
    }
    // 004472e4  b000                   -mov al, 0
    cpu.al = 0 /*0x0*/;
    // 004472e6  f2ae                   -repne scasb al, byte ptr es:[edi]
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
    // 004472e8  4f                     -dec edi
    (cpu.edi)--;
L_0x004472e9:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004472e9  8a06                   -mov al, byte ptr [esi]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi);
    // 004472eb  8807                   -mov byte ptr [edi], al
    app->getMemory<x86::reg8>(cpu.edi) = cpu.al;
    // 004472ed  3c00                   +cmp al, 0
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
    // 004472ef  7410                   -je 0x447301
    if (cpu.flags.zf)
    {
        goto L_0x00447301;
    }
    // 004472f1  8a4601                 -mov al, byte ptr [esi + 1]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi + x86::reg32(1) /* 0x1 */);
    // 004472f4  83c602                 -add esi, 2
    (cpu.esi) += x86::reg32(x86::sreg32(2 /*0x2*/));
    // 004472f7  884701                 -mov byte ptr [edi + 1], al
    app->getMemory<x86::reg8>(cpu.edi + x86::reg32(1) /* 0x1 */) = cpu.al;
    // 004472fa  83c702                 -add edi, 2
    (cpu.edi) += x86::reg32(x86::sreg32(2 /*0x2*/));
    // 004472fd  3c00                   +cmp al, 0
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
    // 004472ff  75e8                   -jne 0x4472e9
    if (!cpu.flags.zf)
    {
        goto L_0x004472e9;
    }
L_0x00447301:
    // 00447301  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
L_0x00447302:
    // 00447302  8d457e                 -lea eax, [ebp + 0x7e]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(126) /* 0x7e */);
    // 00447305  e8c6eeffff             -call 0x4461d0
    cpu.esp -= 4;
    sub_4461d0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0044730a  8da57a010000           -lea esp, [ebp + 0x17a]
    cpu.esp = x86::reg32(cpu.ebp + x86::reg32(378) /* 0x17a */);
    // 00447310  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00447311  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00447312  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00447313  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00447314  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00447315  c3                     -ret 
    cpu.esp += 4;
    return;
  case 0x00447316:
    // 00447316  807d7e00               +cmp byte ptr [ebp + 0x7e], 0
    {
        x86::reg8 tmp1 = app->getMemory<x86::reg8>(cpu.ebp + x86::reg32(126) /* 0x7e */);
        x86::reg8 tmp2 = x86::reg8(x86::sreg8(0 /*0x0*/));
        x86::reg8 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 7);
        cpu.flags.of ^= 1 & (result >> 7);
        cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
        cpu.set_szp(result);
    }
    // 0044731a  742a                   -je 0x447346
    if (cpu.flags.zf)
    {
        goto L_0x00447346;
    }
    // 0044731c  beec8b5300             -mov esi, 0x538bec
    cpu.esi = 5475308 /*0x538bec*/;
    // 00447321  8d7d7e                 -lea edi, [ebp + 0x7e]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(126) /* 0x7e */);
    // 00447324  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00447325  2bc9                   +sub ecx, ecx
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
    // 00447327  49                     +dec ecx
    {
        x86::reg32& tmp = cpu.ecx;
        cpu.flags.of = 1 & (tmp >> 31);
        tmp--;
        cpu.flags.of &= ~(1 & (tmp >> 31));
        cpu.set_szp(tmp);
    }
    // 00447328  b000                   -mov al, 0
    cpu.al = 0 /*0x0*/;
    // 0044732a  f2ae                   -repne scasb al, byte ptr es:[edi]
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
    // 0044732c  4f                     -dec edi
    (cpu.edi)--;
L_0x0044732d:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 0044732d  8a06                   -mov al, byte ptr [esi]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi);
    // 0044732f  8807                   -mov byte ptr [edi], al
    app->getMemory<x86::reg8>(cpu.edi) = cpu.al;
    // 00447331  3c00                   +cmp al, 0
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
    // 00447333  7410                   -je 0x447345
    if (cpu.flags.zf)
    {
        goto L_0x00447345;
    }
    // 00447335  8a4601                 -mov al, byte ptr [esi + 1]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi + x86::reg32(1) /* 0x1 */);
    // 00447338  83c602                 -add esi, 2
    (cpu.esi) += x86::reg32(x86::sreg32(2 /*0x2*/));
    // 0044733b  884701                 -mov byte ptr [edi + 1], al
    app->getMemory<x86::reg8>(cpu.edi + x86::reg32(1) /* 0x1 */) = cpu.al;
    // 0044733e  83c702                 -add edi, 2
    (cpu.edi) += x86::reg32(x86::sreg32(2 /*0x2*/));
    // 00447341  3c00                   +cmp al, 0
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
    // 00447343  75e8                   -jne 0x44732d
    if (!cpu.flags.zf)
    {
        goto L_0x0044732d;
    }
L_0x00447345:
    // 00447345  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
L_0x00447346:
    // 00447346  8d457e                 -lea eax, [ebp + 0x7e]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(126) /* 0x7e */);
    // 00447349  e8d2f0ffff             -call 0x446420
    cpu.esp -= 4;
    sub_446420(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x0044734e:
    // 0044734e  8da57a010000           -lea esp, [ebp + 0x17a]
    cpu.esp = x86::reg32(cpu.ebp + x86::reg32(378) /* 0x17a */);
    // 00447354  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00447355  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00447356  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00447357  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00447358  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00447359  c3                     -ret 
    cpu.esp += 4;
    return;
  default:
    NFS2_ASSERT(false);
  }
}

/* align: skip 0x8d 0x44 0x20 0x00 */
void Application::sub_447370(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
  goto start;
dynamic_jump:
  switch(cpu.ip)
  {
start:
    // 00447370  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00447371  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00447372  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00447373  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00447374  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00447375  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00447377  ba2c8c5300             -mov edx, 0x538c2c
    cpu.edx = 5475372 /*0x538c2c*/;
    // 0044737c  e8bfb6ffff             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00447381  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00447383  7413                   -je 0x447398
    if (cpu.flags.zf)
    {
        goto L_0x00447398;
    }
    // 00447385  803d0c8d550000         +cmp byte ptr [0x558d0c], 0
    {
        x86::reg8 tmp1 = app->getMemory<x86::reg8>(x86::reg32(5606668) /* 0x558d0c */);
        x86::reg8 tmp2 = x86::reg8(x86::sreg8(0 /*0x0*/));
        x86::reg8 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 7);
        cpu.flags.of ^= 1 & (result >> 7);
        cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
        cpu.set_szp(result);
    }
    // 0044738c  7506                   -jne 0x447394
    if (!cpu.flags.zf)
    {
        goto L_0x00447394;
    }
    // 0044738e  80480510               +or byte ptr [eax + 5], 0x10
    cpu.clear_co();
    cpu.set_szp((app->getMemory<x86::reg8>(cpu.eax + x86::reg32(5) /* 0x5 */) |= x86::reg8(x86::sreg8(16 /*0x10*/))));
    // 00447392  eb04                   -jmp 0x447398
    goto L_0x00447398;
L_0x00447394:
    // 00447394  806005ef               -and byte ptr [eax + 5], 0xef
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(5) /* 0x5 */) &= x86::reg8(x86::sreg8(239 /*0xef*/));
L_0x00447398:
    // 00447398  8b15c4915500           -mov edx, dword ptr [0x5591c4]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5607876) /* 0x5591c4 */);
    // 0044739e  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 004473a0  7454                   -je 0x4473f6
    if (cpu.flags.zf)
    {
        goto L_0x004473f6;
    }
    // 004473a2  8a7a04                 -mov bh, byte ptr [edx + 4]
    cpu.bh = app->getMemory<x86::reg8>(cpu.edx + x86::reg32(4) /* 0x4 */);
    // 004473a5  80e7fe                 -and bh, 0xfe
    cpu.bh &= x86::reg8(x86::sreg8(254 /*0xfe*/));
    // 004473a8  a1c0915500             -mov eax, dword ptr [0x5591c0]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5607872) /* 0x5591c0 */);
    // 004473ad  887a04                 -mov byte ptr [edx + 4], bh
    app->getMemory<x86::reg8>(cpu.edx + x86::reg32(4) /* 0x4 */) = cpu.bh;
    // 004473b0  83784800               +cmp dword ptr [eax + 0x48], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(72) /* 0x48 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004473b4  7437                   -je 0x4473ed
    if (cpu.flags.zf)
    {
        goto L_0x004473ed;
    }
    // 004473b6  8b5848                 -mov ebx, dword ptr [eax + 0x48]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(72) /* 0x48 */);
    // 004473b9  3b584c                 +cmp ebx, dword ptr [eax + 0x4c]
    {
        x86::reg32 tmp1 = cpu.ebx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.eax + x86::reg32(76) /* 0x4c */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004473bc  7e2f                   -jle 0x4473ed
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004473ed;
    }
    // 004473be  833dbc91550000         +cmp dword ptr [0x5591bc], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5607868) /* 0x5591bc */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004473c5  752f                   -jne 0x4473f6
    if (!cpu.flags.zf)
    {
        goto L_0x004473f6;
    }
    // 004473c7  b843010000             -mov eax, 0x143
    cpu.eax = 323 /*0x143*/;
    // 004473cc  e87fa40800             -call 0x4d1850
    cpu.esp -= 4;
    nfs3hp::port::text::languageText(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004473d1  8b0dc0915500           -mov ecx, dword ptr [0x5591c0]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(5607872) /* 0x5591c0 */);
    // 004473d7  8b514c                 -mov edx, dword ptr [ecx + 0x4c]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(76) /* 0x4c */);
    // 004473da  8b4970                 -mov ecx, dword ptr [ecx + 0x70]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(112) /* 0x70 */);
    // 004473dd  8b0cd1                 -mov ecx, dword ptr [ecx + edx*8]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ecx + cpu.edx * 8);
    // 004473e0  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004473e2  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004473e4  e8276f0a00             -call 0x4ee310
    cpu.esp -= 4;
    nfs3hp::watcom::strcmp(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004473e9  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004473eb  7509                   -jne 0x4473f6
    if (!cpu.flags.zf)
    {
        goto L_0x004473f6;
    }
L_0x004473ed:
    // 004473ed  a1c4915500             -mov eax, dword ptr [0x5591c4]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5607876) /* 0x5591c4 */);
    // 004473f2  80480401               -or byte ptr [eax + 4], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(4) /* 0x4 */) |= x86::reg8(x86::sreg8(1 /*0x1*/));
L_0x004473f6:
    // 004473f6  8b3dc8915500           -mov edi, dword ptr [0x5591c8]
    cpu.edi = app->getMemory<x86::reg32>(x86::reg32(5607880) /* 0x5591c8 */);
    // 004473fc  85ff                   +test edi, edi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edi & cpu.edi));
    // 004473fe  7420                   -je 0x447420
    if (cpu.flags.zf)
    {
        goto L_0x00447420;
    }
    // 00447400  a1c0915500             -mov eax, dword ptr [0x5591c0]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5607872) /* 0x5591c0 */);
    // 00447405  8b5048                 -mov edx, dword ptr [eax + 0x48]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(72) /* 0x48 */);
    // 00447408  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 0044740a  7405                   -je 0x447411
    if (cpu.flags.zf)
    {
        goto L_0x00447411;
    }
    // 0044740c  3b504c                 +cmp edx, dword ptr [eax + 0x4c]
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.eax + x86::reg32(76) /* 0x4c */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0044740f  7f0b                   -jg 0x44741c
    if (!cpu.flags.zf && (cpu.flags.sf == cpu.flags.of))
    {
        goto L_0x0044741c;
    }
L_0x00447411:
    // 00447411  a1c8915500             -mov eax, dword ptr [0x5591c8]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5607880) /* 0x5591c8 */);
    // 00447416  80480401               +or byte ptr [eax + 4], 1
    cpu.clear_co();
    cpu.set_szp((app->getMemory<x86::reg8>(cpu.eax + x86::reg32(4) /* 0x4 */) |= x86::reg8(x86::sreg8(1 /*0x1*/))));
    // 0044741a  eb04                   -jmp 0x447420
    goto L_0x00447420;
L_0x0044741c:
    // 0044741c  806704fe               -and byte ptr [edi + 4], 0xfe
    app->getMemory<x86::reg8>(cpu.edi + x86::reg32(4) /* 0x4 */) &= x86::reg8(x86::sreg8(254 /*0xfe*/));
L_0x00447420:
    // 00447420  a1bc915500             -mov eax, dword ptr [0x5591bc]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5607868) /* 0x5591bc */);
    // 00447425  83f803                 +cmp eax, 3
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
    // 00447428  772f                   -ja 0x447459
    if (!cpu.flags.cf && !cpu.flags.zf)
    {
        goto L_0x00447459;
    }
    // 0044742a  ff24855c734400         -jmp dword ptr [eax*4 + 0x44735c]
    cpu.ip = app->getMemory<x86::reg32>(4485980 + cpu.eax * 4); goto dynamic_jump;
  case 0x00447431:
    // 00447431  b83f010000             -mov eax, 0x13f
    cpu.eax = 319 /*0x13f*/;
    // 00447436  eb13                   -jmp 0x44744b
    goto L_0x0044744b;
  case 0x00447438:
    // 00447438  b841010000             -mov eax, 0x141
    cpu.eax = 321 /*0x141*/;
    // 0044743d  eb0c                   -jmp 0x44744b
    goto L_0x0044744b;
  case 0x0044743f:
    // 0044743f  b842010000             -mov eax, 0x142
    cpu.eax = 322 /*0x142*/;
    // 00447444  eb05                   -jmp 0x44744b
    goto L_0x0044744b;
  case 0x00447446:
    // 00447446  b840010000             -mov eax, 0x140
    cpu.eax = 320 /*0x140*/;
L_0x0044744b:
    // 0044744b  e800a40800             -call 0x4d1850
    cpu.esp -= 4;
    nfs3hp::port::text::languageText(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00447450  8b0dc0915500           -mov ecx, dword ptr [0x5591c0]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(5607872) /* 0x5591c0 */);
    // 00447456  89413c                 -mov dword ptr [ecx + 0x3c], eax
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(60) /* 0x3c */) = cpu.eax;
L_0x00447459:
    // 00447459  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 0044745b  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0044745c  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0044745d  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0044745e  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0044745f  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00447460  c3                     -ret 
    cpu.esp += 4;
    return;
  default:
    NFS2_ASSERT(false);
  }
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x8d 0x40 0x00 */
void Application::sub_447470(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00447470  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00447471  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00447472  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00447473  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00447474  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00447476  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00447478  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 0044747a  b80c8d5500             -mov eax, 0x558d0c
    cpu.eax = 5606668 /*0x558d0c*/;
    // 0044747f  8915c0915500           -mov dword ptr [0x5591c0], edx
    app->getMemory<x86::reg32>(x86::reg32(5607872) /* 0x5591c0 */) = cpu.edx;
    // 00447485  bab0040000             -mov edx, 0x4b0
    cpu.edx = 1200 /*0x4b0*/;
    // 0044748a  e87d920900             -call 0x4e070c
    cpu.esp -= 4;
    nfs3hp::fillZero(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0044748f  ba2c8c5300             -mov edx, 0x538c2c
    cpu.edx = 5475372 /*0x538c2c*/;
    // 00447494  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00447496  e8a5b5ffff             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0044749b  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0044749d  7407                   -je 0x4474a6
    if (cpu.flags.zf)
    {
        goto L_0x004474a6;
    }
    // 0044749f  c74054e0704400         -mov dword ptr [eax + 0x54], 0x4470e0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(84) /* 0x54 */) = 4485344 /*0x4470e0*/;
L_0x004474a6:
    // 004474a6  ba3c8c5300             -mov edx, 0x538c3c
    cpu.edx = 5475388 /*0x538c3c*/;
    // 004474ab  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004474ad  e88eb5ffff             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004474b2  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004474b4  740c                   -je 0x4474c2
    if (cpu.flags.zf)
    {
        goto L_0x004474c2;
    }
    // 004474b6  a3c0915500             -mov dword ptr [0x5591c0], eax
    app->getMemory<x86::reg32>(x86::reg32(5607872) /* 0x5591c0 */) = cpu.eax;
    // 004474bb  c74074a0714400         -mov dword ptr [eax + 0x74], 0x4471a0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(116) /* 0x74 */) = 4485536 /*0x4471a0*/;
L_0x004474c2:
    // 004474c2  ba448c5300             -mov edx, 0x538c44
    cpu.edx = 5475396 /*0x538c44*/;
    // 004474c7  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004474c9  e872b5ffff             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004474ce  a3c4915500             -mov dword ptr [0x5591c4], eax
    app->getMemory<x86::reg32>(x86::reg32(5607876) /* 0x5591c4 */) = cpu.eax;
    // 004474d3  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004474d5  7407                   -je 0x4474de
    if (cpu.flags.zf)
    {
        goto L_0x004474de;
    }
    // 004474d7  c7406430704400         -mov dword ptr [eax + 0x64], 0x447030
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(100) /* 0x64 */) = 4485168 /*0x447030*/;
L_0x004474de:
    // 004474de  ba508c5300             -mov edx, 0x538c50
    cpu.edx = 5475408 /*0x538c50*/;
    // 004474e3  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004474e5  e856b5ffff             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004474ea  a3c8915500             -mov dword ptr [0x5591c8], eax
    app->getMemory<x86::reg32>(x86::reg32(5607880) /* 0x5591c8 */) = cpu.eax;
    // 004474ef  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004474f1  7407                   -je 0x4474fa
    if (cpu.flags.zf)
    {
        goto L_0x004474fa;
    }
    // 004474f3  c74064506c4400         -mov dword ptr [eax + 0x64], 0x446c50
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(100) /* 0x64 */) = 4484176 /*0x446c50*/;
L_0x004474fa:
    // 004474fa  ba588c5300             -mov edx, 0x538c58
    cpu.edx = 5475416 /*0x538c58*/;
    // 004474ff  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00447501  e83ab5ffff             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00447506  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00447508  7407                   -je 0x447511
    if (cpu.flags.zf)
    {
        goto L_0x00447511;
    }
    // 0044750a  c74064d06a4400         -mov dword ptr [eax + 0x64], 0x446ad0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(100) /* 0x64 */) = 4483792 /*0x446ad0*/;
L_0x00447511:
    // 00447511  ba6c8c5300             -mov edx, 0x538c6c
    cpu.edx = 5475436 /*0x538c6c*/;
    // 00447516  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00447518  e823b5ffff             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0044751d  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0044751f  7407                   -je 0x447528
    if (cpu.flags.zf)
    {
        goto L_0x00447528;
    }
    // 00447521  c74064106b4400         -mov dword ptr [eax + 0x64], 0x446b10
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(100) /* 0x64 */) = 4483856 /*0x446b10*/;
L_0x00447528:
    // 00447528  ba7c8c5300             -mov edx, 0x538c7c
    cpu.edx = 5475452 /*0x538c7c*/;
    // 0044752d  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 0044752f  e80cb5ffff             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00447534  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00447536  7407                   -je 0x44753f
    if (cpu.flags.zf)
    {
        goto L_0x0044753f;
    }
    // 00447538  c74064a06b4400         -mov dword ptr [eax + 0x64], 0x446ba0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(100) /* 0x64 */) = 4484000 /*0x446ba0*/;
L_0x0044753f:
    // 0044753f  ba888c5300             -mov edx, 0x538c88
    cpu.edx = 5475464 /*0x538c88*/;
    // 00447544  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00447546  e8f5b4ffff             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0044754b  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0044754d  7407                   -je 0x447556
    if (cpu.flags.zf)
    {
        goto L_0x00447556;
    }
    // 0044754f  c74064606b4400         -mov dword ptr [eax + 0x64], 0x446b60
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(100) /* 0x64 */) = 4483936 /*0x446b60*/;
L_0x00447556:
    // 00447556  8b0dc0915500           -mov ecx, dword ptr [0x5591c0]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(5607872) /* 0x5591c0 */);
    // 0044755c  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    // 0044755e  740c                   -je 0x44756c
    if (cpu.flags.zf)
    {
        goto L_0x0044756c;
    }
    // 00447560  ba148c5300             -mov edx, 0x538c14
    cpu.edx = 5475348 /*0x538c14*/;
    // 00447565  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00447567  e834000000             -call 0x4475a0
    cpu.esp -= 4;
    nfs3hp::load::listReplays(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x0044756c:
    // 0044756c  a1c0915500             -mov eax, dword ptr [0x5591c0]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5607872) /* 0x5591c0 */);
    // 00447571  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
    // 00447573  8b504c                 -mov edx, dword ptr [eax + 0x4c]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(76) /* 0x4c */);
    // 00447576  891dbc915500           -mov dword ptr [0x5591bc], ebx
    app->getMemory<x86::reg32>(x86::reg32(5607868) /* 0x5591bc */) = cpu.ebx;
    // 0044757c  e81ffcffff             -call 0x4471a0
    cpu.esp -= 4;
    sub_4471a0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00447581  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00447583  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00447584  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00447585  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00447586  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00447587  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8b 0xd2 */
void Application::sub_447590(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00447590  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00447591  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00447593  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00447595  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00447596  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_4475a0: native, nfs3hp::load::listReplays */

/* align: skip 0x8d 0x40 0x00 */
void Application::sub_447800(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00447800  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00447801  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00447802  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00447803  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00447804  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00447806  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00447808  89d6                   -mov esi, edx
    cpu.esi = cpu.edx;
    // 0044780a  e8b1ceffff             -call 0x4446c0
    cpu.esp -= 4;
    nfs3hp::frontend::dialogFocusedButton(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0044780f  c60200                 -mov byte ptr [edx], 0
    app->getMemory<x86::reg8>(cpu.edx) = 0 /*0x0*/;
    // 00447812  83f903                 +cmp ecx, 3
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
    // 00447815  7512                   -jne 0x447829
    if (!cpu.flags.zf)
    {
        goto L_0x00447829;
    }
L_0x00447817:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00447817  a1e8915500             -mov eax, dword ptr [0x5591e8]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5607912) /* 0x5591e8 */);
    // 0044781c  e80f020000             -call 0x447a30
    cpu.esp -= 4;
    sub_447a30(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00447821  c60200                 -mov byte ptr [edx], 0
    app->getMemory<x86::reg8>(cpu.edx) = 0 /*0x0*/;
    // 00447824  e982000000             -jmp 0x4478ab
    goto L_0x004478ab;
L_0x00447829:
    // 00447829  83f901                 +cmp ecx, 1
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
    // 0044782c  0f8579000000           -jne 0x4478ab
    if (!cpu.flags.zf)
    {
        goto L_0x004478ab;
    }
    // 00447832  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00447834  760b                   -jbe 0x447841
    if (cpu.flags.cf || cpu.flags.zf)
    {
        goto L_0x00447841;
    }
    // 00447836  39c8                   +cmp eax, ecx
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
    // 00447838  74dd                   -je 0x447817
    if (cpu.flags.zf)
    {
        goto L_0x00447817;
    }
    // 0044783a  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 0044783c  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0044783d  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0044783e  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0044783f  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00447840  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x00447841:
    // 00447841  b8d4915500             -mov eax, 0x5591d4
    cpu.eax = 5607892 /*0x5591d4*/;
    // 00447846  ff15cc915500           -call dword ptr [0x5591cc]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(5607884) /* 0x5591cc */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0044784c  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0044784e  7423                   -je 0x447873
    if (cpu.flags.zf)
    {
        goto L_0x00447873;
    }
    // 00447850  bad4915500             -mov edx, 0x5591d4
    cpu.edx = 5607892 /*0x5591d4*/;
    // 00447855  b842000000             -mov eax, 0x42
    cpu.eax = 66 /*0x42*/;
    // 0044785a  bb00010000             -mov ebx, 0x100
    cpu.ebx = 256 /*0x100*/;
    // 0044785f  8915b8116600           -mov dword ptr [0x6611b8], edx
    app->getMemory<x86::reg32>(x86::reg32(6689208) /* 0x6611b8 */) = cpu.edx;
    // 00447865  e8e69f0800             -call 0x4d1850
    cpu.esp -= 4;
    nfs3hp::port::text::languageText(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0044786a  6a00                   -push 0
    app->getMemory<x86::reg32>(cpu.esp-4) = 0 /*0x0*/;
    cpu.esp -= 4;
    // 0044786c  bab8116600             -mov edx, 0x6611b8
    cpu.edx = 6689208 /*0x6611b8*/;
    // 00447871  eb26                   -jmp 0x447899
    goto L_0x00447899;
L_0x00447873:
    // 00447873  b9d4915500             -mov ecx, 0x5591d4
    cpu.ecx = 5607892 /*0x5591d4*/;
    // 00447878  b843000000             -mov eax, 0x43
    cpu.eax = 67 /*0x43*/;
    // 0044787d  bb00010000             -mov ebx, 0x100
    cpu.ebx = 256 /*0x100*/;
    // 00447882  bab8116600             -mov edx, 0x6611b8
    cpu.edx = 6689208 /*0x6611b8*/;
    // 00447887  890db8116600           -mov dword ptr [0x6611b8], ecx
    app->getMemory<x86::reg32>(x86::reg32(6689208) /* 0x6611b8 */) = cpu.ecx;
    // 0044788d  e8be9f0800             -call 0x4d1850
    cpu.esp -= 4;
    nfs3hp::port::text::languageText(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00447892  6a00                   -push 0
    app->getMemory<x86::reg32>(cpu.esp-4) = 0 /*0x0*/;
    cpu.esp -= 4;
    // 00447894  b901000000             -mov ecx, 1
    cpu.ecx = 1 /*0x1*/;
L_0x00447899:
    // 00447899  a3bc116600             -mov dword ptr [0x6611bc], eax
    app->getMemory<x86::reg32>(x86::reg32(6689212) /* 0x6611bc */) = cpu.eax;
    // 0044789e  b802000000             -mov eax, 2
    cpu.eax = 2 /*0x2*/;
    // 004478a3  e8d8d1ffff             -call 0x444a80
    cpu.esp -= 4;
    nfs3hp::frontend::dialogOpenMessage(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004478a8  c60600                 -mov byte ptr [esi], 0
    app->getMemory<x86::reg8>(cpu.esi) = 0 /*0x0*/;
L_0x004478ab:
    // 004478ab  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 004478ad  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004478ae  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004478af  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004478b0  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004478b1  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x8b 0xc0 */
void Application::sub_4478c0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004478c0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004478c1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004478c2  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004478c3  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004478c4  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004478c5  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004478c7  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 004478ca  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 004478cc  8955fc                 -mov dword ptr [ebp - 4], edx
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.edx;
    // 004478cf  e8eccdffff             -call 0x4446c0
    cpu.esp -= 4;
    nfs3hp::frontend::dialogFocusedButton(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004478d4  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 004478d6  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 004478d8  c60200                 -mov byte ptr [edx], 0
    app->getMemory<x86::reg8>(cpu.edx) = 0 /*0x0*/;
    // 004478db  e830d3ffff             -call 0x444c10
    cpu.esp -= 4;
    nfs3hp::frontend::dialogEditText(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004478e0  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004478e2  83f903                 +cmp ecx, 3
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
    // 004478e5  7409                   -je 0x4478f0
    if (cpu.flags.zf)
    {
        goto L_0x004478f0;
    }
    // 004478e7  83f901                 +cmp ecx, 1
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
    // 004478ea  750f                   -jne 0x4478fb
    if (!cpu.flags.zf)
    {
        goto L_0x004478fb;
    }
    // 004478ec  39cb                   +cmp ebx, ecx
    {
        x86::reg32 tmp1 = cpu.ebx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.ecx));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004478ee  750b                   -jne 0x4478fb
    if (!cpu.flags.zf)
    {
        goto L_0x004478fb;
    }
L_0x004478f0:
    // 004478f0  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 004478f3  c60001                 -mov byte ptr [eax], 1
    app->getMemory<x86::reg8>(cpu.eax) = 1 /*0x1*/;
    // 004478f6  e90d010000             -jmp 0x447a08
    goto L_0x00447a08;
L_0x004478fb:
    // 004478fb  83f901                 +cmp ecx, 1
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
    // 004478fe  0f8504010000           -jne 0x447a08
    if (!cpu.flags.zf)
    {
        goto L_0x00447a08;
    }
    // 00447904  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 00447906  740a                   -je 0x447912
    if (cpu.flags.zf)
    {
        goto L_0x00447912;
    }
    // 00447908  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 0044790a  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 0044790c  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0044790d  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0044790e  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0044790f  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00447910  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00447911  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x00447912:
    // 00447912  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 00447914  0f84ee000000           -je 0x447a08
    if (cpu.flags.zf)
    {
        goto L_0x00447a08;
    }
    // 0044791a  803a00                 +cmp byte ptr [edx], 0
    {
        x86::reg8 tmp1 = app->getMemory<x86::reg8>(cpu.edx);
        x86::reg8 tmp2 = x86::reg8(x86::sreg8(0 /*0x0*/));
        x86::reg8 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 7);
        cpu.flags.of ^= 1 & (result >> 7);
        cpu.flags.of &= (1 & (tmp1 >> 7)) != (1 & (tmp2 >> 7));
        cpu.set_szp(result);
    }
    // 0044791d  0f84e5000000           -je 0x447a08
    if (cpu.flags.zf)
    {
        goto L_0x00447a08;
    }
    // 00447923  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 00447925  ff15d0915500           -call dword ptr [0x5591d0]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(5607888) /* 0x5591d0 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0044792b  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0044792d  7561                   -jne 0x447990
    if (!cpu.flags.zf)
    {
        goto L_0x00447990;
    }
    // 0044792f  bfd4915500             -mov edi, 0x5591d4
    cpu.edi = 5607892 /*0x5591d4*/;
    // 00447934  89d6                   -mov esi, edx
    cpu.esi = cpu.edx;
    // 00447936  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
L_0x00447937:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00447937  8a06                   -mov al, byte ptr [esi]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi);
    // 00447939  8807                   -mov byte ptr [edi], al
    app->getMemory<x86::reg8>(cpu.edi) = cpu.al;
    // 0044793b  3c00                   +cmp al, 0
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
    // 0044793d  7410                   -je 0x44794f
    if (cpu.flags.zf)
    {
        goto L_0x0044794f;
    }
    // 0044793f  8a4601                 -mov al, byte ptr [esi + 1]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi + x86::reg32(1) /* 0x1 */);
    // 00447942  83c602                 -add esi, 2
    (cpu.esi) += x86::reg32(x86::sreg32(2 /*0x2*/));
    // 00447945  884701                 -mov byte ptr [edi + 1], al
    app->getMemory<x86::reg8>(cpu.edi + x86::reg32(1) /* 0x1 */) = cpu.al;
    // 00447948  83c702                 -add edi, 2
    (cpu.edi) += x86::reg32(x86::sreg32(2 /*0x2*/));
    // 0044794b  3c00                   +cmp al, 0
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
    // 0044794d  75e8                   -jne 0x447937
    if (!cpu.flags.zf)
    {
        goto L_0x00447937;
    }
L_0x0044794f:
    // 0044794f  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00447950  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 00447952  ff15cc915500           -call dword ptr [0x5591cc]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(5607884) /* 0x5591cc */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00447958  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0044795a  7407                   -je 0x447963
    if (cpu.flags.zf)
    {
        goto L_0x00447963;
    }
    // 0044795c  b842000000             -mov eax, 0x42
    cpu.eax = 66 /*0x42*/;
    // 00447961  eb05                   -jmp 0x447968
    goto L_0x00447968;
L_0x00447963:
    // 00447963  b843000000             -mov eax, 0x43
    cpu.eax = 67 /*0x43*/;
L_0x00447968:
    // 00447968  bb00010000             -mov ebx, 0x100
    cpu.ebx = 256 /*0x100*/;
    // 0044796d  bac0116600             -mov edx, 0x6611c0
    cpu.edx = 6689216 /*0x6611c0*/;
    // 00447972  e8d99e0800             -call 0x4d1850
    cpu.esp -= 4;
    nfs3hp::port::text::languageText(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00447977  6a00                   -push 0
    app->getMemory<x86::reg32>(cpu.esp-4) = 0 /*0x0*/;
    cpu.esp -= 4;
    // 00447979  a3c0116600             -mov dword ptr [0x6611c0], eax
    app->getMemory<x86::reg32>(x86::reg32(6689216) /* 0x6611c0 */) = cpu.eax;
    // 0044797e  b802000000             -mov eax, 2
    cpu.eax = 2 /*0x2*/;
    // 00447983  893dc4116600           -mov dword ptr [0x6611c4], edi
    app->getMemory<x86::reg32>(x86::reg32(6689220) /* 0x6611c4 */) = cpu.edi;
    // 00447989  e8f2d0ffff             -call 0x444a80
    cpu.esp -= 4;
    nfs3hp::frontend::dialogOpenMessage(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0044798e  eb72                   -jmp 0x447a02
    goto L_0x00447a02;
L_0x00447990:
    // 00447990  b83c000000             -mov eax, 0x3c
    cpu.eax = 60 /*0x3c*/;
    // 00447995  e8b69e0800             -call 0x4d1850
    cpu.esp -= 4;
    nfs3hp::port::text::languageText(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0044799a  a3c8116600             -mov dword ptr [0x6611c8], eax
    app->getMemory<x86::reg32>(x86::reg32(6689224) /* 0x6611c8 */) = cpu.eax;
    // 0044799f  b8c4000000             -mov eax, 0xc4
    cpu.eax = 196 /*0xc4*/;
    // 004479a4  bfd4915500             -mov edi, 0x5591d4
    cpu.edi = 5607892 /*0x5591d4*/;
    // 004479a9  e8a29e0800             -call 0x4d1850
    cpu.esp -= 4;
    nfs3hp::port::text::languageText(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004479ae  a3cc116600             -mov dword ptr [0x6611cc], eax
    app->getMemory<x86::reg32>(x86::reg32(6689228) /* 0x6611cc */) = cpu.eax;
    // 004479b3  b8c5000000             -mov eax, 0xc5
    cpu.eax = 197 /*0xc5*/;
    // 004479b8  89d6                   -mov esi, edx
    cpu.esi = cpu.edx;
    // 004479ba  e8919e0800             -call 0x4d1850
    cpu.esp -= 4;
    nfs3hp::port::text::languageText(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004479bf  a3d0116600             -mov dword ptr [0x6611d0], eax
    app->getMemory<x86::reg32>(x86::reg32(6689232) /* 0x6611d0 */) = cpu.eax;
    // 004479c4  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
L_0x004479c5:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004479c5  8a06                   -mov al, byte ptr [esi]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi);
    // 004479c7  8807                   -mov byte ptr [edi], al
    app->getMemory<x86::reg8>(cpu.edi) = cpu.al;
    // 004479c9  3c00                   +cmp al, 0
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
    // 004479cb  7410                   -je 0x4479dd
    if (cpu.flags.zf)
    {
        goto L_0x004479dd;
    }
    // 004479cd  8a4601                 -mov al, byte ptr [esi + 1]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi + x86::reg32(1) /* 0x1 */);
    // 004479d0  83c602                 -add esi, 2
    (cpu.esi) += x86::reg32(x86::sreg32(2 /*0x2*/));
    // 004479d3  884701                 -mov byte ptr [edi + 1], al
    app->getMemory<x86::reg8>(cpu.edi + x86::reg32(1) /* 0x1 */) = cpu.al;
    // 004479d6  83c702                 -add edi, 2
    (cpu.edi) += x86::reg32(x86::sreg32(2 /*0x2*/));
    // 004479d9  3c00                   +cmp al, 0
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
    // 004479db  75e8                   -jne 0x4479c5
    if (!cpu.flags.zf)
    {
        goto L_0x004479c5;
    }
L_0x004479dd:
    // 004479dd  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004479de  6800784400             -push 0x447800
    app->getMemory<x86::reg32>(cpu.esp-4) = 4487168 /*0x447800*/;
    cpu.esp -= 4;
    // 004479e3  6a00                   -push 0
    app->getMemory<x86::reg32>(cpu.esp-4) = 0 /*0x0*/;
    cpu.esp -= 4;
    // 004479e5  6a00                   -push 0
    app->getMemory<x86::reg32>(cpu.esp-4) = 0 /*0x0*/;
    cpu.esp -= 4;
    // 004479e7  b9cc116600             -mov ecx, 0x6611cc
    cpu.ecx = 6689228 /*0x6611cc*/;
    // 004479ec  bb02000000             -mov ebx, 2
    cpu.ebx = 2 /*0x2*/;
    // 004479f1  6a00                   -push 0
    app->getMemory<x86::reg32>(cpu.esp-4) = 0 /*0x0*/;
    cpu.esp -= 4;
    // 004479f3  bac8116600             -mov edx, 0x6611c8
    cpu.edx = 6689224 /*0x6611c8*/;
    // 004479f8  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 004479fd  e8ceccffff             -call 0x4446d0
    cpu.esp -= 4;
    nfs3hp::frontend::dialogOpenQuestion(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00447a02:
    // 00447a02  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00447a05  c60000                 -mov byte ptr [eax], 0
    app->getMemory<x86::reg8>(cpu.eax) = 0 /*0x0*/;
L_0x00447a08:
    // 00447a08  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00447a0a  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 00447a0c  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00447a0d  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00447a0e  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00447a0f  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00447a10  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00447a11  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 */
void Application::sub_447a30(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
  goto start;
dynamic_jump:
  switch(cpu.ip)
  {
start:
    // 00447a30  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00447a31  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00447a32  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00447a33  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00447a34  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00447a35  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00447a36  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00447a38  a3e8915500             -mov dword ptr [0x5591e8], eax
    app->getMemory<x86::reg32>(x86::reg32(5607912) /* 0x5591e8 */) = cpu.eax;
    // 00447a3d  83f803                 +cmp eax, 3
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
    // 00447a40  0f878a000000           -ja 0x447ad0
    if (!cpu.flags.cf && !cpu.flags.zf)
    {
        goto L_0x00447ad0;
    }
    // 00447a46  ff2485147a4400         -jmp dword ptr [eax*4 + 0x447a14]
    cpu.ip = app->getMemory<x86::reg32>(4487700 + cpu.eax * 4); goto dynamic_jump;
  case 0x00447a4d:
    // 00447a4d  b83d000000             -mov eax, 0x3d
    cpu.eax = 61 /*0x3d*/;
    // 00447a52  ba50654400             -mov edx, 0x446550
    cpu.edx = 4482384 /*0x446550*/;
    // 00447a57  b910654400             -mov ecx, 0x446510
    cpu.ecx = 4482320 /*0x446510*/;
    // 00447a5c  eb5c                   -jmp 0x447aba
    goto L_0x00447aba;
  case 0x00447a5e:
    // 00447a5e  b83e000000             -mov eax, 0x3e
    cpu.eax = 62 /*0x3e*/;
    // 00447a63  bbc0684400             -mov ebx, 0x4468c0
    cpu.ebx = 4483264 /*0x4468c0*/;
    // 00447a68  be50694400             -mov esi, 0x446950
    cpu.esi = 4483408 /*0x446950*/;
    // 00447a6d  e8de9d0800             -call 0x4d1850
    cpu.esp -= 4;
    nfs3hp::port::text::languageText(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00447a72  a3dc116600             -mov dword ptr [0x6611dc], eax
    app->getMemory<x86::reg32>(x86::reg32(6689244) /* 0x6611dc */) = cpu.eax;
    // 00447a77  891dcc915500           -mov dword ptr [0x5591cc], ebx
    app->getMemory<x86::reg32>(x86::reg32(5607884) /* 0x5591cc */) = cpu.ebx;
    // 00447a7d  8935d0915500           -mov dword ptr [0x5591d0], esi
    app->getMemory<x86::reg32>(x86::reg32(5607888) /* 0x5591d0 */) = cpu.esi;
    // 00447a83  eb4b                   -jmp 0x447ad0
    goto L_0x00447ad0;
  case 0x00447a85:
    // 00447a85  b840000000             -mov eax, 0x40
    cpu.eax = 64 /*0x40*/;
    // 00447a8a  bf106a4400             -mov edi, 0x446a10
    cpu.edi = 4483600 /*0x446a10*/;
    // 00447a8f  e8bc9d0800             -call 0x4d1850
    cpu.esp -= 4;
    nfs3hp::port::text::languageText(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00447a94  a3dc116600             -mov dword ptr [0x6611dc], eax
    app->getMemory<x86::reg32>(x86::reg32(6689244) /* 0x6611dc */) = cpu.eax;
    // 00447a99  b8906a4400             -mov eax, 0x446a90
    cpu.eax = 4483728 /*0x446a90*/;
    // 00447a9e  893dcc915500           -mov dword ptr [0x5591cc], edi
    app->getMemory<x86::reg32>(x86::reg32(5607884) /* 0x5591cc */) = cpu.edi;
    // 00447aa4  a3d0915500             -mov dword ptr [0x5591d0], eax
    app->getMemory<x86::reg32>(x86::reg32(5607888) /* 0x5591d0 */) = cpu.eax;
    // 00447aa9  eb25                   -jmp 0x447ad0
    goto L_0x00447ad0;
  case 0x00447aab:
    // 00447aab  b83f000000             -mov eax, 0x3f
    cpu.eax = 63 /*0x3f*/;
    // 00447ab0  ba80674400             -mov edx, 0x446780
    cpu.edx = 4482944 /*0x446780*/;
    // 00447ab5  b940674400             -mov ecx, 0x446740
    cpu.ecx = 4482880 /*0x446740*/;
L_0x00447aba:
    // 00447aba  e8919d0800             -call 0x4d1850
    cpu.esp -= 4;
    nfs3hp::port::text::languageText(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00447abf  a3dc116600             -mov dword ptr [0x6611dc], eax
    app->getMemory<x86::reg32>(x86::reg32(6689244) /* 0x6611dc */) = cpu.eax;
    // 00447ac4  8915cc915500           -mov dword ptr [0x5591cc], edx
    app->getMemory<x86::reg32>(x86::reg32(5607884) /* 0x5591cc */) = cpu.edx;
    // 00447aca  890dd0915500           -mov dword ptr [0x5591d0], ecx
    app->getMemory<x86::reg32>(x86::reg32(5607888) /* 0x5591d0 */) = cpu.ecx;
L_0x00447ad0:
    // 00447ad0  b8f9000000             -mov eax, 0xf9
    cpu.eax = 249 /*0xf9*/;
    // 00447ad5  befcd26f00             -mov esi, 0x6fd2fc
    cpu.esi = 7328508 /*0x6fd2fc*/;
    // 00447ada  e8719d0800             -call 0x4d1850
    cpu.esp -= 4;
    nfs3hp::port::text::languageText(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00447adf  a3d4116600             -mov dword ptr [0x6611d4], eax
    app->getMemory<x86::reg32>(x86::reg32(6689236) /* 0x6611d4 */) = cpu.eax;
    // 00447ae4  b8c6000000             -mov eax, 0xc6
    cpu.eax = 198 /*0xc6*/;
    // 00447ae9  bfd4915500             -mov edi, 0x5591d4
    cpu.edi = 5607892 /*0x5591d4*/;
    // 00447aee  e85d9d0800             -call 0x4d1850
    cpu.esp -= 4;
    nfs3hp::port::text::languageText(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00447af3  a3d8116600             -mov dword ptr [0x6611d8], eax
    app->getMemory<x86::reg32>(x86::reg32(6689240) /* 0x6611d8 */) = cpu.eax;
    // 00447af8  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
L_0x00447af9:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00447af9  8a06                   -mov al, byte ptr [esi]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi);
    // 00447afb  8807                   -mov byte ptr [edi], al
    app->getMemory<x86::reg8>(cpu.edi) = cpu.al;
    // 00447afd  3c00                   +cmp al, 0
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
    // 00447aff  7410                   -je 0x447b11
    if (cpu.flags.zf)
    {
        goto L_0x00447b11;
    }
    // 00447b01  8a4601                 -mov al, byte ptr [esi + 1]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi + x86::reg32(1) /* 0x1 */);
    // 00447b04  83c602                 -add esi, 2
    (cpu.esi) += x86::reg32(x86::sreg32(2 /*0x2*/));
    // 00447b07  884701                 -mov byte ptr [edi + 1], al
    app->getMemory<x86::reg8>(cpu.edi + x86::reg32(1) /* 0x1 */) = cpu.al;
    // 00447b0a  83c702                 -add edi, 2
    (cpu.edi) += x86::reg32(x86::sreg32(2 /*0x2*/));
    // 00447b0d  3c00                   +cmp al, 0
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
    // 00447b0f  75e8                   -jne 0x447af9
    if (!cpu.flags.zf)
    {
        goto L_0x00447af9;
    }
L_0x00447b11:
    // 00447b11  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00447b12  68c0784400             -push 0x4478c0
    app->getMemory<x86::reg32>(cpu.esp-4) = 4487360 /*0x4478c0*/;
    cpu.esp -= 4;
    // 00447b17  6a00                   -push 0
    app->getMemory<x86::reg32>(cpu.esp-4) = 0 /*0x0*/;
    cpu.esp -= 4;
    // 00447b19  6a0a                   -push 0xa
    app->getMemory<x86::reg32>(cpu.esp-4) = 10 /*0xa*/;
    cpu.esp -= 4;
    // 00447b1b  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00447b1c  b9d4116600             -mov ecx, 0x6611d4
    cpu.ecx = 6689236 /*0x6611d4*/;
    // 00447b21  bb02000000             -mov ebx, 2
    cpu.ebx = 2 /*0x2*/;
    // 00447b26  6a00                   -push 0
    app->getMemory<x86::reg32>(cpu.esp-4) = 0 /*0x0*/;
    cpu.esp -= 4;
    // 00447b28  badc116600             -mov edx, 0x6611dc
    cpu.edx = 6689244 /*0x6611dc*/;
    // 00447b2d  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 00447b32  e8e9d0ffff             -call 0x444c20
    cpu.esp -= 4;
    nfs3hp::frontend::dialogOpenEdit(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00447b37  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00447b38  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00447b39  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00447b3a  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00447b3b  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00447b3c  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00447b3d  c3                     -ret 
    cpu.esp += 4;
    return;
  default:
    NFS2_ASSERT(false);
  }
}

/* sub_447b40: native, nfs3hp::frontend::forceCancelKey */

/* sub_447b60: native, nfs3hp::frontend::forceStrengthMoved */

/* sub_447c40: native, nfs3hp::frontend::forceRoadEffectsMoved */

/* sub_447c70: native, nfs3hp::frontend::forceCollisionMoved */

/* sub_447ca0: native, nfs3hp::frontend::forceEngineMoved */

/* sub_447cd0: native, nfs3hp::frontend::forceBodyRollMoved */

/* sub_447d50: native, nfs3hp::frontend::forceRoadGripMoved */

/* sub_447dd0: native, nfs3hp::frontend::forceOnEnter */

/* sub_4481c0: native, nfs3hp::frontend::forceOnExit */

/* align: skip 0x00 0x00 */
void Application::sub_448210(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00448210  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00448211  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00448212  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00448213  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00448215  89c7                   -mov edi, eax
    cpu.edi = cpu.eax;
    // 00448217  89d6                   -mov esi, edx
    cpu.esi = cpu.edx;
    // 00448219  8b1518925500           -mov edx, dword ptr [0x559218]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5607960) /* 0x559218 */);
    // 0044821f  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 00448221  c1e004                 -shl eax, 4
    cpu.eax <<= 4 /*0x4*/ % 32;
    // 00448224  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 00448226  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 00448229  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 0044822b  ba20126600             -mov edx, 0x661220
    cpu.edx = 6689312 /*0x661220*/;
    // 00448230  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 00448233  01c2                   -add edx, eax
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.eax));
    // 00448235  833d1892550014         +cmp dword ptr [0x559218], 0x14
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5607960) /* 0x559218 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(20 /*0x14*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0044823c  7d75                   -jge 0x4482b3
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004482b3;
    }
    // 0044823e  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = shownDepth(cpu.ecx); /* port: the depth a race is drawn in */
    cpu.esp -= 4;
    // 0044823f  893a                   -mov dword ptr [edx], edi
    app->getMemory<x86::reg32>(cpu.edx) = cpu.edi;
    // 00448241  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00448242  897204                 -mov dword ptr [edx + 4], esi
    app->getMemory<x86::reg32>(cpu.edx + x86::reg32(4) /* 0x4 */) = cpu.esi;
    // 00448245  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00448246  8b4510                 -mov eax, dword ptr [ebp + 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(16) /* 0x10 */);
    // 00448249  895a08                 -mov dword ptr [edx + 8], ebx
    app->getMemory<x86::reg32>(cpu.edx + x86::reg32(8) /* 0x8 */) = cpu.ebx;
    // 0044824c  68488d5300             -push 0x538d48
    app->getMemory<x86::reg32>(cpu.esp-4) = 5475656 /*0x538d48*/;
    cpu.esp -= 4;
    // 00448251  8d7a14                 -lea edi, [edx + 0x14]
    cpu.edi = x86::reg32(cpu.edx + x86::reg32(20) /* 0x14 */);
    // 00448254  894a0c                 -mov dword ptr [edx + 0xc], ecx
    app->getMemory<x86::reg32>(cpu.edx + x86::reg32(12) /* 0xc */) = cpu.ecx;
    // 00448257  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00448258  894210                 -mov dword ptr [edx + 0x10], eax
    app->getMemory<x86::reg32>(cpu.edx + x86::reg32(16) /* 0x10 */) = cpu.eax;
    // 0044825b  e830740900             -call 0x4df690
    cpu.esp -= 4;
    nfs3hp::watcom::sprintf(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00448260  8b4a10                 -mov ecx, dword ptr [edx + 0x10]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(16) /* 0x10 */);
    // 00448263  83c414                 -add esp, 0x14
    (cpu.esp) += x86::reg32(x86::sreg32(20 /*0x14*/));
    // 00448266  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    // 00448268  7427                   -je 0x448291
    if (cpu.flags.zf)
    {
        goto L_0x00448291;
    }
    // 0044826a  be588d5300             -mov esi, 0x538d58
    cpu.esi = 5475672 /*0x538d58*/;
    // 0044826f  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00448270  2bc9                   +sub ecx, ecx
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
    // 00448272  49                     +dec ecx
    {
        x86::reg32& tmp = cpu.ecx;
        cpu.flags.of = 1 & (tmp >> 31);
        tmp--;
        cpu.flags.of &= ~(1 & (tmp >> 31));
        cpu.set_szp(tmp);
    }
    // 00448273  b000                   -mov al, 0
    cpu.al = 0 /*0x0*/;
    // 00448275  f2ae                   -repne scasb al, byte ptr es:[edi]
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
    // 00448277  4f                     -dec edi
    (cpu.edi)--;
L_0x00448278:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00448278  8a06                   -mov al, byte ptr [esi]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi);
    // 0044827a  8807                   -mov byte ptr [edi], al
    app->getMemory<x86::reg8>(cpu.edi) = cpu.al;
    // 0044827c  3c00                   +cmp al, 0
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
    // 0044827e  7410                   -je 0x448290
    if (cpu.flags.zf)
    {
        goto L_0x00448290;
    }
    // 00448280  8a4601                 -mov al, byte ptr [esi + 1]
    cpu.al = app->getMemory<x86::reg8>(cpu.esi + x86::reg32(1) /* 0x1 */);
    // 00448283  83c602                 -add esi, 2
    (cpu.esi) += x86::reg32(x86::sreg32(2 /*0x2*/));
    // 00448286  884701                 -mov byte ptr [edi + 1], al
    app->getMemory<x86::reg8>(cpu.edi + x86::reg32(1) /* 0x1 */) = cpu.al;
    // 00448289  83c702                 -add edi, 2
    (cpu.edi) += x86::reg32(x86::sreg32(2 /*0x2*/));
    // 0044828c  3c00                   +cmp al, 0
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
    // 0044828e  75e8                   -jne 0x448278
    if (!cpu.flags.zf)
    {
        goto L_0x00448278;
    }
L_0x00448290:
    // 00448290  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
L_0x00448291:
    // 00448291  8b1518925500           -mov edx, dword ptr [0x559218]
    dynamicFullscreenLabel(app, cpu.edx); /* port: Dynamic Fullscreen named in the list */
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5607960) /* 0x559218 */);
    // 00448297  66a118925500           -mov ax, word ptr [0x559218]
    cpu.ax = app->getMemory<x86::reg16>(x86::reg32(5607960) /* 0x559218 */);
    // 0044829d  8d5a01                 -lea ebx, [edx + 1]
    cpu.ebx = x86::reg32(cpu.edx + x86::reg32(1) /* 0x1 */);
    // 004482a0  05a8070000             -add eax, 0x7a8
    (cpu.eax) += x86::reg32(x86::sreg32(1960 /*0x7a8*/));
    // 004482a5  891d18925500           -mov dword ptr [0x559218], ebx
    app->getMemory<x86::reg32>(x86::reg32(5607960) /* 0x559218 */) = cpu.ebx;
    // 004482ab  66890455ec915500       -mov word ptr [edx*2 + 0x5591ec], ax
    app->getMemory<x86::reg16>(x86::reg32(5607916) /* 0x5591ec */ + cpu.edx * 2) = cpu.ax;
L_0x004482b3:
    // 004482b3  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004482b4  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004482b5  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004482b6  c20400                 -ret 4
    cpu.esp += 4+4 /*0x4*/;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x90 */
void Application::sub_4482c0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004482c0  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004482c1  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004482c2  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004482c4  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 004482c6  b8ec915500             -mov eax, 0x5591ec
    cpu.eax = 5607916 /*0x5591ec*/;
    // 004482cb  891518925500           -mov dword ptr [0x559218], edx
    app->getMemory<x86::reg32>(x86::reg32(5607960) /* 0x559218 */) = cpu.edx;
    // 004482d1  ba2a000000             -mov edx, 0x2a
    cpu.edx = 42 /*0x2a*/;
    // 004482d6  e831840900             -call 0x4e070c
    cpu.esp -= 4;
    nfs3hp::fillZero(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004482db  b810824400             -mov eax, 0x448210
    cpu.eax = 4489744 /*0x448210*/;
    // 004482e0  e8ab6a0700             -call 0x4bed90
    cpu.esp -= 4;
    nfs3hp::graphics::listScreenModes(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004482e5  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004482e6  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004482e7  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8b 0xd2 */
void Application::sub_4482f0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004482f0  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004482f1  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004482f2  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004482f3  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004482f5  e8c6ffffff             -call 0x4482c0
    cpu.esp -= 4;
    sub_4482c0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004482fa  a114bc6f00             -mov eax, dword ptr [0x6fbc14]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(7322644) /* 0x6fbc14 */);
    // 004482ff  3b0518925500           +cmp eax, dword ptr [0x559218]
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(5607960) /* 0x559218 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00448305  7c08                   -jl 0x44830f
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x0044830f;
    }
    // 00448307  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 00448309  890d14bc6f00           -mov dword ptr [0x6fbc14], ecx
    app->getMemory<x86::reg32>(x86::reg32(7322644) /* 0x6fbc14 */) = cpu.ecx;
L_0x0044830f:
    // 0044830f  8b1514bc6f00           -mov edx, dword ptr [0x6fbc14]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(7322644) /* 0x6fbc14 */);
    // 00448315  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 00448317  c1e004                 -shl eax, 4
    cpu.eax <<= 4 /*0x4*/ % 32;
    // 0044831a  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 0044831c  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 0044831f  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 00448321  8b048520126600         -mov eax, dword ptr [eax*4 + 0x661220]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(6689312) /* 0x661220 */ + cpu.eax * 4);
    // 00448328  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00448329  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0044832a  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0044832b  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x44 0x20 0x00 */
void Application::sub_448330(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00448330  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00448331  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00448332  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00448333  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00448334  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00448335  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00448337  81ec14010000           -sub esp, 0x114
    (cpu.esp) -= x86::reg32(x86::sreg32(276 /*0x114*/));
    // 0044833d  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 0044833f  8b0d18925500           -mov ecx, dword ptr [0x559218]
    cpu.ecx = app->getMemory<x86::reg32>(x86::reg32(5607960) /* 0x559218 */);
    // 00448345  3b0d14bc6f00           +cmp ecx, dword ptr [0x6fbc14]
    {
        x86::reg32 tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(7322644) /* 0x6fbc14 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0044834b  7f08                   -jg 0x448355
    if (!cpu.flags.zf && (cpu.flags.sf == cpu.flags.of))
    {
        goto L_0x00448355;
    }
    // 0044834d  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
    // 0044834f  891d14bc6f00           -mov dword ptr [0x6fbc14], ebx
    app->getMemory<x86::reg32>(x86::reg32(7322644) /* 0x6fbc14 */) = cpu.ebx;
L_0x00448355:
    // 00448355  8b3514bc6f00           -mov esi, dword ptr [0x6fbc14]
    cpu.esi = app->getMemory<x86::reg32>(x86::reg32(7322644) /* 0x6fbc14 */);
    // 0044835b  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 0044835d  c1e004                 -shl eax, 4
    cpu.eax <<= 4 /*0x4*/ % 32;
    // 00448360  01f0                   -add eax, esi
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.esi));
    // 00448362  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 00448365  01f0                   -add eax, esi
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.esi));
    // 00448367  b945000000             -mov ecx, 0x45
    cpu.ecx = 69 /*0x45*/;
    // 0044836c  8dbdecfeffff           -lea edi, [ebp - 0x114]
    cpu.edi = x86::reg32(cpu.ebp + x86::reg32(-276) /* -0x114 */);
    // 00448372  8d348520126600         -lea esi, [eax*4 + 0x661220]
    cpu.esi = x86::reg32(x86::reg32(6689312) /* 0x661220 */ + cpu.eax * 4);
    // 00448379  f3a5                   -rep movsd dword ptr es:[edi], dword ptr [esi]
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
    // 0044837b  b945000000             -mov ecx, 0x45
    cpu.ecx = 69 /*0x45*/;
    // 00448380  8db5ecfeffff           -lea esi, [ebp - 0x114]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(-276) /* -0x114 */);
    // 00448386  89d7                   -mov edi, edx
    cpu.edi = cpu.edx;
    // 00448388  f3a5                   -rep movsd dword ptr es:[edi], dword ptr [esi]
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
    // 0044838a  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 0044838c  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 0044838e  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0044838f  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00448390  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00448391  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00448392  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00448393  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 */
void Application::sub_4483a0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004483a0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004483a1  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004483a2  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004483a3  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004483a4  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004483a6  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 004483a8  e813ffffff             -call 0x4482c0
    cpu.esp -= 4;
    sub_4482c0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004483ad  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
L_0x004483af:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004483af  3b1518925500           +cmp edx, dword ptr [0x559218]
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(5607960) /* 0x559218 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004483b5  7d30                   -jge 0x4483e7
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x004483e7;
    }
    // 004483b7  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004483b9  c1e004                 -shl eax, 4
    cpu.eax <<= 4 /*0x4*/ % 32;
    // 004483bc  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 004483be  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 004483c1  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 004483c3  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 004483c6  3b9820126600           +cmp ebx, dword ptr [eax + 0x661220]
    {
        x86::reg32 tmp1 = cpu.ebx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6689312) /* 0x661220 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004483cc  7516                   -jne 0x4483e4
    if (!cpu.flags.zf)
    {
        goto L_0x004483e4;
    }
    // 004483ce  8b8024126600           -mov eax, dword ptr [eax + 0x661224]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(6689316) /* 0x661224 */);
    // 004483d4  891514bc6f00           -mov dword ptr [0x6fbc14], edx
    app->getMemory<x86::reg32>(x86::reg32(7322644) /* 0x6fbc14 */) = cpu.edx;
    // 004483da  a318bc6f00             -mov dword ptr [0x6fbc18], eax
    app->getMemory<x86::reg32>(x86::reg32(7322648) /* 0x6fbc18 */) = cpu.eax;
    // 004483df  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004483e0  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004483e1  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004483e2  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004483e3  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004483e4:
    // 004483e4  42                     +inc edx
    {
        x86::reg32& tmp = cpu.edx;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 004483e5  ebc8                   -jmp 0x4483af
    goto L_0x004483af;
L_0x004483e7:
    // 004483e7  a124126600             -mov eax, dword ptr [0x661224]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(6689316) /* 0x661224 */);
    // 004483ec  31ff                   -xor edi, edi
    cpu.edi ^= x86::reg32(x86::sreg32(cpu.edi));
    // 004483ee  a318bc6f00             -mov dword ptr [0x6fbc18], eax
    app->getMemory<x86::reg32>(x86::reg32(7322648) /* 0x6fbc18 */) = cpu.eax;
    // 004483f3  893d14bc6f00           -mov dword ptr [0x6fbc14], edi
    app->getMemory<x86::reg32>(x86::reg32(7322644) /* 0x6fbc14 */) = cpu.edi;
    // 004483f9  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004483fa  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004483fb  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004483fc  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004483fd  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_448400: native, nfs3hp::frontend::displayModeName */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x90 */
void Application::sub_448430(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (graphicsOnFrame(app, cpu)) /* port: native (tools/apply_native_frontend.py) */
    {
        return;
    }
    // 00448430  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00448431  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00448433  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00448435  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00448436  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 */
void Application::sub_448440(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (graphicsOnEnter(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 00448440  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00448441  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00448442  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00448443  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00448444  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00448445  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00448446  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00448448  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 0044844a  e871feffff             -call 0x4482c0
    cpu.esp -= 4;
    sub_4482c0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0044844f  a114bc6f00             -mov eax, dword ptr [0x6fbc14]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(7322644) /* 0x6fbc14 */);
    // 00448454  3b0518925500           +cmp eax, dword ptr [0x559218]
    {
        x86::reg32 tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(5607960) /* 0x559218 */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0044845a  7c08                   -jl 0x448464
    if (cpu.flags.sf != cpu.flags.of)
    {
        goto L_0x00448464;
    }
    // 0044845c  31c9                   -xor ecx, ecx
    cpu.ecx ^= x86::reg32(x86::sreg32(cpu.ecx));
    // 0044845e  890d14bc6f00           -mov dword ptr [0x6fbc14], ecx
    app->getMemory<x86::reg32>(x86::reg32(7322644) /* 0x6fbc14 */) = cpu.ecx;
L_0x00448464:
    // 00448464  b910000000             -mov ecx, 0x10
    cpu.ecx = 16 /*0x10*/;
    // 00448469  bfb0276600             -mov edi, 0x6627b0
    cpu.edi = 6694832 /*0x6627b0*/;
    // 0044846e  be10bc6f00             -mov esi, 0x6fbc10
    cpu.esi = 7322640 /*0x6fbc10*/;
    // 00448473  ba608d5300             -mov edx, 0x538d60
    cpu.edx = 5475680 /*0x538d60*/;
    // 00448478  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 0044847a  f3a5                   -rep movsd dword ptr es:[edi], dword ptr [esi]
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
    // 0044847c  e8bfa5ffff             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00448481  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00448483  740d                   -je 0x448492
    if (cpu.flags.zf)
    {
        goto L_0x00448492;
    }
    // 00448485  f605583a7a0006         +test byte ptr [0x7a3a58], 6
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(x86::reg32(8010328) /* 0x7a3a58 */) & 6 /*0x6*/));
    // 0044848c  7404                   -je 0x448492
    if (cpu.flags.zf)
    {
        goto L_0x00448492;
    }
    // 0044848e  80480401               -or byte ptr [eax + 4], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(4) /* 0x4 */) |= x86::reg8(x86::sreg8(1 /*0x1*/));
L_0x00448492:
    // 00448492  ba6c8d5300             -mov edx, 0x538d6c
    cpu.edx = 5475692 /*0x538d6c*/;
    // 00448497  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 00448499  e8a2a5ffff             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0044849e  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004484a0  740f                   -je 0x4484b1
    if (cpu.flags.zf)
    {
        goto L_0x004484b1;
    }
    // 004484a2  f605583a7a0006         +test byte ptr [0x7a3a58], 6
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(x86::reg32(8010328) /* 0x7a3a58 */) & 6 /*0x6*/));
    // 004484a9  7406                   -je 0x4484b1
    if (cpu.flags.zf)
    {
        goto L_0x004484b1;
    }
    // 004484ab  668148040110           -or word ptr [eax + 4], 0x1001
    app->getMemory<x86::reg16>(cpu.eax + x86::reg32(4) /* 0x4 */) |= x86::reg16(x86::sreg16(4097 /*0x1001*/));
L_0x004484b1:
    // 004484b1  ba7c8d5300             -mov edx, 0x538d7c
    cpu.edx = 5475708 /*0x538d7c*/;
    // 004484b6  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 004484b8  e883a5ffff             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004484bd  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004484bf  740d                   -je 0x4484ce
    if (cpu.flags.zf)
    {
        goto L_0x004484ce;
    }
    // 004484c1  833db0d36f0001         +cmp dword ptr [0x6fd3b0], 1
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
    // 004484c8  7e04                   -jle 0x4484ce
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x004484ce;
    }
    // 004484ca  80480401               -or byte ptr [eax + 4], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(4) /* 0x4 */) |= x86::reg8(x86::sreg8(1 /*0x1*/));
L_0x004484ce:
    // 004484ce  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 004484d0  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004484d1  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004484d2  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004484d3  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004484d4  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004484d5  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004484d6  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 */
void Application::sub_4484e0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (graphicsOnExit(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 004484e0  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004484e1  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004484e2  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004484e3  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004484e4  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004484e5  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004484e7  8b5018                 -mov edx, dword ptr [eax + 0x18]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */);
    // 004484ea  8b4016                 -mov eax, dword ptr [eax + 0x16]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(22) /* 0x16 */);
    // 004484ed  c1fa10                 -sar edx, 0x10
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (16 /*0x10*/ % 32));
    // 004484f0  c1f810                 -sar eax, 0x10
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (16 /*0x10*/ % 32));
    // 004484f3  01c2                   -add edx, eax
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.eax));
    // 004484f5  8d049500000000         -lea eax, [edx*4]
    cpu.eax = x86::reg32(cpu.edx * 4);
    // 004484fc  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 004484fe  c1e004                 -shl eax, 4
    cpu.eax <<= 4 /*0x4*/ % 32;
    // 00448501  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 00448503  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 00448506  05e04e6000             -add eax, 0x604ee0
    (cpu.eax) += x86::reg32(x86::sreg32(6311648 /*0x604ee0*/));
    // 0044850b  833805                 +cmp dword ptr [eax], 5
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
    // 0044850e  7526                   -jne 0x448536
    if (!cpu.flags.zf)
    {
        goto L_0x00448536;
    }
    // 00448510  ba848d5300             -mov edx, 0x538d84
    cpu.edx = 5475716 /*0x538d84*/;
    // 00448515  8b4010                 -mov eax, dword ptr [eax + 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(16) /* 0x10 */);
    // 00448518  e8a3a4ffff             -call 0x4429c0
    cpu.esp -= 4;
    nfs3hp::port::menus::codelinkMatches(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0044851d  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0044851f  7415                   -je 0x448536
    if (cpu.flags.zf)
    {
        goto L_0x00448536;
    }
    // 00448521  b910000000             -mov ecx, 0x10
    cpu.ecx = 16 /*0x10*/;
    // 00448526  bf10bc6f00             -mov edi, 0x6fbc10
    cpu.edi = 7322640 /*0x6fbc10*/;
    // 0044852b  beb0276600             -mov esi, 0x6627b0
    cpu.esi = 6694832 /*0x6627b0*/;
    // 00448530  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
    // 00448532  f3a5                   -rep movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00448534  eb25                   -jmp 0x44855b
    goto L_0x0044855b;
L_0x00448536:
    // 00448536  e885fdffff             -call 0x4482c0
    cpu.esp -= 4;
    sub_4482c0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0044853b  8b1514bc6f00           -mov edx, dword ptr [0x6fbc14]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(7322644) /* 0x6fbc14 */);
    // 00448541  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 00448543  c1e004                 -shl eax, 4
    cpu.eax <<= 4 /*0x4*/ % 32;
    // 00448546  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 00448548  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 0044854b  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 0044854d  8b048524126600         -mov eax, dword ptr [eax*4 + 0x661224]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(6689316) /* 0x661224 */ + cpu.eax * 4);
    // 00448554  a318bc6f00             -mov dword ptr [0x6fbc18], eax
    app->getMemory<x86::reg32>(x86::reg32(7322648) /* 0x6fbc18 */) = cpu.eax;
    // 00448559  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
L_0x0044855b:
    // 0044855b  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0044855c  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0044855d  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0044855e  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0044855f  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00448560  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x8d 0x40 0x00 */
void Application::sub_448570(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (advancedIntensityMoved(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 00448570  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00448571  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00448572  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00448573  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00448575  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00448577  ba0f000000             -mov edx, 0xf
    cpu.edx = 15 /*0xf*/;
    // 0044857c  e8df200000             -call 0x44a660
    cpu.esp -= 4;
    nfs3hp::frontend::menuShownNow(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00448581  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00448583  740f                   -je 0x448594
    if (cpu.flags.zf)
    {
        goto L_0x00448594;
    }
    // 00448585  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00448587  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00448589  e822440200             -call 0x46c9b0
    cpu.esp -= 4;
    nfs3hp::frontend::sliderValue(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0044858e  d91d38bc6f00           -fstp dword ptr [0x6fbc38]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = cpu.fpu.st(0);
    app->getMemory<float>(x86::reg32(7322680) /* 0x6fbc38 */) = float(fpu1);
    cpu.fpu.count -= 1;
    }
L_0x00448594:
    // 00448594  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00448595  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00448596  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00448597  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8b 0xd2 */
void Application::sub_4485a0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (advancedOnFrame(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 004485a0  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004485a1  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004485a2  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004485a3  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004485a5  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 004485a7  ba9c8d5300             -mov edx, 0x538d9c
    cpu.edx = 5475740 /*0x538d9c*/;
    // 004485ac  e88fa4ffff             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004485b1  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004485b3  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004485b5  741c                   -je 0x4485d3
    if (cpu.flags.zf)
    {
        goto L_0x004485d3;
    }
    // 004485b7  833d683a7a0000         +cmp dword ptr [0x7a3a68], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(8010344) /* 0x7a3a68 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004485be  740f                   -je 0x4485cf
    if (cpu.flags.zf)
    {
        goto L_0x004485cf;
    }
    // 004485c0  833d34bc6f0000         +cmp dword ptr [0x6fbc34], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(7322676) /* 0x6fbc34 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004485c7  7406                   -je 0x4485cf
    if (cpu.flags.zf)
    {
        goto L_0x004485cf;
    }
    // 004485c9  806004fe               +and byte ptr [eax + 4], 0xfe
    cpu.clear_co();
    cpu.set_szp((app->getMemory<x86::reg8>(cpu.eax + x86::reg32(4) /* 0x4 */) &= x86::reg8(x86::sreg8(254 /*0xfe*/))));
    // 004485cd  eb04                   -jmp 0x4485d3
    goto L_0x004485d3;
L_0x004485cf:
    // 004485cf  804a0401               -or byte ptr [edx + 4], 1
    app->getMemory<x86::reg8>(cpu.edx + x86::reg32(4) /* 0x4 */) |= x86::reg8(x86::sreg8(1 /*0x1*/));
L_0x004485d3:
    // 004485d3  bab08d5300             -mov edx, 0x538db0
    cpu.edx = 5475760 /*0x538db0*/;
    // 004485d8  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004485da  e861a4ffff             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004485df  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004485e1  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004485e3  7420                   -je 0x448605
    if (cpu.flags.zf)
    {
        goto L_0x00448605;
    }
    // 004485e5  833d683a7a0000         +cmp dword ptr [0x7a3a68], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(8010344) /* 0x7a3a68 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004485ec  7411                   -je 0x4485ff
    if (cpu.flags.zf)
    {
        goto L_0x004485ff;
    }
    // 004485ee  833d34bc6f0000         +cmp dword ptr [0x6fbc34], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(7322676) /* 0x6fbc34 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004485f5  7408                   -je 0x4485ff
    if (cpu.flags.zf)
    {
        goto L_0x004485ff;
    }
    // 004485f7  66816004feef           +and word ptr [eax + 4], 0xeffe
    cpu.clear_co();
    cpu.set_szp((app->getMemory<x86::reg16>(cpu.eax + x86::reg32(4) /* 0x4 */) &= x86::reg16(x86::sreg16(61438 /*0xeffe*/))));
    // 004485fd  eb06                   -jmp 0x448605
    goto L_0x00448605;
L_0x004485ff:
    // 004485ff  66814a040110           -or word ptr [edx + 4], 0x1001
    app->getMemory<x86::reg16>(cpu.edx + x86::reg32(4) /* 0x4 */) |= x86::reg16(x86::sreg16(4097 /*0x1001*/));
L_0x00448605:
    // 00448605  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00448607  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00448608  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00448609  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0044860a  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x40 0x00 0x8b 0xc9 */
void Application::sub_448610(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (advancedOnEnter(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 00448610  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00448611  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00448612  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00448613  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00448614  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00448615  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00448616  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00448618  81ec14010000           -sub esp, 0x114
    (cpu.esp) -= x86::reg32(x86::sreg32(276 /*0x114*/));
    // 0044861e  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 00448620  b910000000             -mov ecx, 0x10
    cpu.ecx = 16 /*0x10*/;
    // 00448625  bfb0276600             -mov edi, 0x6627b0
    cpu.edi = 6694832 /*0x6627b0*/;
    // 0044862a  be10bc6f00             -mov esi, 0x6fbc10
    cpu.esi = 7322640 /*0x6fbc10*/;
    // 0044862f  f3a5                   -rep movsd dword ptr es:[edi], dword ptr [esi]
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
    // 00448631  8db5ecfeffff           -lea esi, [ebp - 0x114]
    cpu.esi = x86::reg32(cpu.ebp + x86::reg32(-276) /* -0x114 */);
    // 00448637  ba7c8d5300             -mov edx, 0x538d7c
    cpu.edx = 5475708 /*0x538d7c*/;
    // 0044863c  e8effcffff             -call 0x448330
    cpu.esp -= 4;
    sub_448330(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00448641  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 00448643  e8f8a3ffff             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00448648  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0044864a  740d                   -je 0x448659
    if (cpu.flags.zf)
    {
        goto L_0x00448659;
    }
    // 0044864c  833db0d36f0001         +cmp dword ptr [0x6fd3b0], 1
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
    // 00448653  7e04                   -jle 0x448659
    if (cpu.flags.zf || (cpu.flags.sf != cpu.flags.of))
    {
        goto L_0x00448659;
    }
    // 00448655  80480401               -or byte ptr [eax + 4], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(4) /* 0x4 */) |= x86::reg8(x86::sreg8(1 /*0x1*/));
L_0x00448659:
    // 00448659  bac48d5300             -mov edx, 0x538dc4
    cpu.edx = 5475780 /*0x538dc4*/;
    // 0044865e  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 00448660  e8dba3ffff             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00448665  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00448667  7413                   -je 0x44867c
    if (cpu.flags.zf)
    {
        goto L_0x0044867c;
    }
    // 00448669  833d4cbb6f0001         +cmp dword ptr [0x6fbb4c], 1
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(7322444) /* 0x6fbb4c */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1 /*0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00448670  7506                   -jne 0x448678
    if (!cpu.flags.zf)
    {
        goto L_0x00448678;
    }
    // 00448672  806005ef               +and byte ptr [eax + 5], 0xef
    cpu.clear_co();
    cpu.set_szp((app->getMemory<x86::reg8>(cpu.eax + x86::reg32(5) /* 0x5 */) &= x86::reg8(x86::sreg8(239 /*0xef*/))));
    // 00448676  eb04                   -jmp 0x44867c
    goto L_0x0044867c;
L_0x00448678:
    // 00448678  80480510               -or byte ptr [eax + 5], 0x10
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(5) /* 0x5 */) |= x86::reg8(x86::sreg8(16 /*0x10*/));
L_0x0044867c:
    // 0044867c  f605583a7a0006         +test byte ptr [0x7a3a58], 6
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg8>(app->getMemory<x86::reg8>(x86::reg32(8010328) /* 0x7a3a58 */) & 6 /*0x6*/));
    // 00448683  7554                   -jne 0x4486d9
    if (!cpu.flags.zf)
    {
        goto L_0x004486d9;
    }
    // 00448685  bad08d5300             -mov edx, 0x538dd0
    cpu.edx = 5475792 /*0x538dd0*/;
    // 0044868a  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 0044868c  e8afa3ffff             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00448691  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00448693  7406                   -je 0x44869b
    if (cpu.flags.zf)
    {
        goto L_0x0044869b;
    }
    // 00448695  668148040110           -or word ptr [eax + 4], 0x1001
    app->getMemory<x86::reg16>(cpu.eax + x86::reg32(4) /* 0x4 */) |= x86::reg16(x86::sreg16(4097 /*0x1001*/));
L_0x0044869b:
    // 0044869b  bae48d5300             -mov edx, 0x538de4
    cpu.edx = 5475812 /*0x538de4*/;
    // 004486a0  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 004486a2  e899a3ffff             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004486a7  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004486a9  7404                   -je 0x4486af
    if (cpu.flags.zf)
    {
        goto L_0x004486af;
    }
    // 004486ab  80480401               -or byte ptr [eax + 4], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(4) /* 0x4 */) |= x86::reg8(x86::sreg8(1 /*0x1*/));
L_0x004486af:
    // 004486af  baf08d5300             -mov edx, 0x538df0
    cpu.edx = 5475824 /*0x538df0*/;
    // 004486b4  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 004486b6  e885a3ffff             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004486bb  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004486bd  7406                   -je 0x4486c5
    if (cpu.flags.zf)
    {
        goto L_0x004486c5;
    }
    // 004486bf  668148040110           -or word ptr [eax + 4], 0x1001
    app->getMemory<x86::reg16>(cpu.eax + x86::reg32(4) /* 0x4 */) |= x86::reg16(x86::sreg16(4097 /*0x1001*/));
L_0x004486c5:
    // 004486c5  ba0c8e5300             -mov edx, 0x538e0c
    cpu.edx = 5475852 /*0x538e0c*/;
    // 004486ca  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 004486cc  e86fa3ffff             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004486d1  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004486d3  7404                   -je 0x4486d9
    if (cpu.flags.zf)
    {
        goto L_0x004486d9;
    }
    // 004486d5  80480401               -or byte ptr [eax + 4], 1
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(4) /* 0x4 */) |= x86::reg8(x86::sreg8(1 /*0x1*/));
L_0x004486d9:
    // 004486d9  ba208e5300             -mov edx, 0x538e20
    cpu.edx = 5475872 /*0x538e20*/;
    // 004486de  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 004486e0  e85ba3ffff             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004486e5  ba2c8e5300             -mov edx, 0x538e2c
    cpu.edx = 5475884 /*0x538e2c*/;
    // 004486ea  a3f0276600             -mov dword ptr [0x6627f0], eax
    app->getMemory<x86::reg32>(x86::reg32(6694896) /* 0x6627f0 */) = cpu.eax;
    // 004486ef  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 004486f1  e84aa3ffff             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004486f6  8b35f0276600           -mov esi, dword ptr [0x6627f0]
    cpu.esi = app->getMemory<x86::reg32>(x86::reg32(6694896) /* 0x6627f0 */);
    // 004486fc  a3f4276600             -mov dword ptr [0x6627f4], eax
    app->getMemory<x86::reg32>(x86::reg32(6694900) /* 0x6627f4 */) = cpu.eax;
    // 00448701  85f6                   +test esi, esi
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.esi & cpu.esi));
    // 00448703  7423                   -je 0x448728
    if (cpu.flags.zf)
    {
        goto L_0x00448728;
    }
    // 00448705  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00448707  741f                   -je 0x448728
    if (cpu.flags.zf)
    {
        goto L_0x00448728;
    }
    // 00448709  83bdfcfeffff00         +cmp dword ptr [ebp - 0x104], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-260) /* -0x104 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00448710  750c                   -jne 0x44871e
    if (!cpu.flags.zf)
    {
        goto L_0x0044871e;
    }
    // 00448712  804e0401               -or byte ptr [esi + 4], 1
    app->getMemory<x86::reg8>(cpu.esi + x86::reg32(4) /* 0x4 */) |= x86::reg8(x86::sreg8(1 /*0x1*/));
    // 00448716  668148040110           +or word ptr [eax + 4], 0x1001
    cpu.clear_co();
    cpu.set_szp((app->getMemory<x86::reg16>(cpu.eax + x86::reg32(4) /* 0x4 */) |= x86::reg16(x86::sreg16(4097 /*0x1001*/))));
    // 0044871c  eb0a                   -jmp 0x448728
    goto L_0x00448728;
L_0x0044871e:
    // 0044871e  806604fe               -and byte ptr [esi + 4], 0xfe
    app->getMemory<x86::reg8>(cpu.esi + x86::reg32(4) /* 0x4 */) &= x86::reg8(x86::sreg8(254 /*0xfe*/));
    // 00448722  66816004feef           -and word ptr [eax + 4], 0xeffe
    app->getMemory<x86::reg16>(cpu.eax + x86::reg32(4) /* 0x4 */) &= x86::reg16(x86::sreg16(61438 /*0xeffe*/));
L_0x00448728:
    // 00448728  ba3c8e5300             -mov edx, 0x538e3c
    cpu.edx = 5475900 /*0x538e3c*/;
    // 0044872d  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 0044872f  e80ca3ffff             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00448734  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00448736  7422                   -je 0x44875a
    if (cpu.flags.zf)
    {
        goto L_0x0044875a;
    }
    // 00448738  f605583a7a0040         +test byte ptr [0x7a3a58], 0x40
    cpu.clear_co();
    // Port: alpha intensity capability reported present.
    cpu.set_szp(static_cast<x86::reg8>(64 /*0x40, port: was the 0x7a3a58 probe*/));
    // 0044873f  7506                   -jne 0x448747
    if (!cpu.flags.zf)
    {
        goto L_0x00448747;
    }
    // 00448741  80480401               +or byte ptr [eax + 4], 1
    cpu.clear_co();
    cpu.set_szp((app->getMemory<x86::reg8>(cpu.eax + x86::reg32(4) /* 0x4 */) |= x86::reg8(x86::sreg8(1 /*0x1*/))));
    // 00448745  eb13                   -jmp 0x44875a
    goto L_0x0044875a;
L_0x00448747:
    // 00448747  d90538bc6f00           -fld dword ptr [0x6fbc38]
    {  // x87 stack in locals (codegen/fpu_stack.py)
    x86::Float fpu1 = x86::Float(app->getMemory<float>(x86::reg32(7322680) /* 0x6fbc38 */));
    // 0044874d  ba70854400             -mov edx, 0x448570
    cpu.edx = 4490608 /*0x448570*/;
    // 00448752  d95854                 -fstp dword ptr [eax + 0x54]
    app->getMemory<float>(cpu.eax + x86::reg32(84) /* 0x54 */) = float(fpu1);
    }
    // 00448755  e866430200             -call 0x46cac0
    cpu.esp -= 4;
    nfs3hp::frontend::sliderSetOnMove(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x0044875a:
    // 0044875a  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 0044875c  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 0044875e  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0044875f  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00448760  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00448761  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00448762  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00448763  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00448764  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 0x8b 0xdb */
void Application::sub_448770(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (advancedOnExit(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 00448770  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00448771  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00448772  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00448773  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00448774  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00448775  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00448777  8b5018                 -mov edx, dword ptr [eax + 0x18]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */);
    // 0044877a  8b4016                 -mov eax, dword ptr [eax + 0x16]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(22) /* 0x16 */);
    // 0044877d  c1fa10                 -sar edx, 0x10
    cpu.edx = x86::reg32(x86::sreg32(cpu.edx) >> (16 /*0x10*/ % 32));
    // 00448780  c1f810                 -sar eax, 0x10
    cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> (16 /*0x10*/ % 32));
    // 00448783  01c2                   -add edx, eax
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.eax));
    // 00448785  8d049500000000         -lea eax, [edx*4]
    cpu.eax = x86::reg32(cpu.edx * 4);
    // 0044878c  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 0044878e  c1e004                 -shl eax, 4
    cpu.eax <<= 4 /*0x4*/ % 32;
    // 00448791  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 00448793  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 00448796  05e04e6000             -add eax, 0x604ee0
    (cpu.eax) += x86::reg32(x86::sreg32(6311648 /*0x604ee0*/));
    // 0044879b  833805                 +cmp dword ptr [eax], 5
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
    // 0044879e  7526                   -jne 0x4487c6
    if (!cpu.flags.zf)
    {
        goto L_0x004487c6;
    }
    // 004487a0  ba4c8e5300             -mov edx, 0x538e4c
    cpu.edx = 5475916 /*0x538e4c*/;
    // 004487a5  8b4010                 -mov eax, dword ptr [eax + 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(16) /* 0x10 */);
    // 004487a8  e813a2ffff             -call 0x4429c0
    cpu.esp -= 4;
    nfs3hp::port::menus::codelinkMatches(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004487ad  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004487af  7415                   -je 0x4487c6
    if (cpu.flags.zf)
    {
        goto L_0x004487c6;
    }
    // 004487b1  b910000000             -mov ecx, 0x10
    cpu.ecx = 16 /*0x10*/;
    // 004487b6  bf10bc6f00             -mov edi, 0x6fbc10
    cpu.edi = 7322640 /*0x6fbc10*/;
    // 004487bb  beb0276600             -mov esi, 0x6627b0
    cpu.esi = 6694832 /*0x6627b0*/;
    // 004487c0  31c0                   +xor eax, eax
    cpu.clear_co();
    cpu.set_szp((cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax))));
    // 004487c2  f3a5                   -rep movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004487c4  eb02                   -jmp 0x4487c8
    goto L_0x004487c8;
L_0x004487c6:
    // 004487c6  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
L_0x004487c8:
    // 004487c8  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004487c9  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004487ca  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004487cb  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004487cc  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004487cd  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x00 0x00 */
void Application::sub_4487d0(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (locationOnFrame(app, cpu)) /* port: native (tools/apply_native_frontend.py) */
    {
        return;
    }
    // 004487d0  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004487d1  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004487d3  e828e3fdff             -call 0x426b00
    cpu.esp -= 4;
    sub_426b00(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004487d8  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 004487da  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004487db  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x44 0x20 0x00 */
void Application::sub_4487e0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (locationOnEnter(app, cpu.sync())) /* port: native (tools/apply_native_frontend.py) */
    {
        cpu.reload();
        return;
    }
    // 004487e0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004487e1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004487e2  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004487e3  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004487e4  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004487e5  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004487e6  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004487e8  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 004487ea  ba688e5300             -mov edx, 0x538e68
    cpu.edx = 5475944 /*0x538e68*/;
    // 004487ef  e84ca2ffff             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004487f4  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004487f6  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004487f8  741a                   -je 0x448814
    if (cpu.flags.zf)
    {
        goto L_0x00448814;
    }
    // 004487fa  8b1db8d36f00           -mov ebx, dword ptr [0x6fd3b8]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(7328696) /* 0x6fd3b8 */);
    // 00448800  83fb01                 +cmp ebx, 1
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
    // 00448803  7405                   -je 0x44880a
    if (cpu.flags.zf)
    {
        goto L_0x0044880a;
    }
    // 00448805  83fb02                 +cmp ebx, 2
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
    // 00448808  7506                   -jne 0x448810
    if (!cpu.flags.zf)
    {
        goto L_0x00448810;
    }
L_0x0044880a:
    // 0044880a  804a0401               +or byte ptr [edx + 4], 1
    cpu.clear_co();
    cpu.set_szp((app->getMemory<x86::reg8>(cpu.edx + x86::reg32(4) /* 0x4 */) |= x86::reg8(x86::sreg8(1 /*0x1*/))));
    // 0044880e  eb04                   -jmp 0x448814
    goto L_0x00448814;
L_0x00448810:
    // 00448810  806004fe               -and byte ptr [eax + 4], 0xfe
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(4) /* 0x4 */) &= x86::reg8(x86::sreg8(254 /*0xfe*/));
L_0x00448814:
    // 00448814  ba808e5300             -mov edx, 0x538e80
    cpu.edx = 5475968 /*0x538e80*/;
    // 00448819  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 0044881b  e820a2ffff             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00448820  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 00448822  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00448824  741a                   -je 0x448840
    if (cpu.flags.zf)
    {
        goto L_0x00448840;
    }
    // 00448826  8b3db8d36f00           -mov edi, dword ptr [0x6fd3b8]
    cpu.edi = app->getMemory<x86::reg32>(x86::reg32(7328696) /* 0x6fd3b8 */);
    // 0044882c  83ff01                 +cmp edi, 1
    {
        x86::reg32 tmp1 = cpu.edi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1 /*0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0044882f  7405                   -je 0x448836
    if (cpu.flags.zf)
    {
        goto L_0x00448836;
    }
    // 00448831  83ff02                 +cmp edi, 2
    {
        x86::reg32 tmp1 = cpu.edi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(2 /*0x2*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00448834  7506                   -jne 0x44883c
    if (!cpu.flags.zf)
    {
        goto L_0x0044883c;
    }
L_0x00448836:
    // 00448836  804a0401               +or byte ptr [edx + 4], 1
    cpu.clear_co();
    cpu.set_szp((app->getMemory<x86::reg8>(cpu.edx + x86::reg32(4) /* 0x4 */) |= x86::reg8(x86::sreg8(1 /*0x1*/))));
    // 0044883a  eb04                   -jmp 0x448840
    goto L_0x00448840;
L_0x0044883c:
    // 0044883c  806004fe               -and byte ptr [eax + 4], 0xfe
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(4) /* 0x4 */) &= x86::reg8(x86::sreg8(254 /*0xfe*/));
L_0x00448840:
    // 00448840  ba988e5300             -mov edx, 0x538e98
    cpu.edx = 5475992 /*0x538e98*/;
    // 00448845  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00448847  e8f4a1ffff             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0044884c  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 0044884e  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00448850  741a                   -je 0x44886c
    if (cpu.flags.zf)
    {
        goto L_0x0044886c;
    }
    // 00448852  8b35b8d36f00           -mov esi, dword ptr [0x6fd3b8]
    cpu.esi = app->getMemory<x86::reg32>(x86::reg32(7328696) /* 0x6fd3b8 */);
    // 00448858  83fe01                 +cmp esi, 1
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
    // 0044885b  7405                   -je 0x448862
    if (cpu.flags.zf)
    {
        goto L_0x00448862;
    }
    // 0044885d  83fe02                 +cmp esi, 2
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
    // 00448860  7506                   -jne 0x448868
    if (!cpu.flags.zf)
    {
        goto L_0x00448868;
    }
L_0x00448862:
    // 00448862  804a0401               +or byte ptr [edx + 4], 1
    cpu.clear_co();
    cpu.set_szp((app->getMemory<x86::reg8>(cpu.edx + x86::reg32(4) /* 0x4 */) |= x86::reg8(x86::sreg8(1 /*0x1*/))));
    // 00448866  eb04                   -jmp 0x44886c
    goto L_0x0044886c;
L_0x00448868:
    // 00448868  806004fe               -and byte ptr [eax + 4], 0xfe
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(4) /* 0x4 */) &= x86::reg8(x86::sreg8(254 /*0xfe*/));
L_0x0044886c:
    // 0044886c  bab08e5300             -mov edx, 0x538eb0
    cpu.edx = 5476016 /*0x538eb0*/;
    // 00448871  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00448873  e8c8a1ffff             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00448878  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 0044887a  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0044887c  741a                   -je 0x448898
    if (cpu.flags.zf)
    {
        goto L_0x00448898;
    }
    // 0044887e  8b1db8d36f00           -mov ebx, dword ptr [0x6fd3b8]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(7328696) /* 0x6fd3b8 */);
    // 00448884  83fb01                 +cmp ebx, 1
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
    // 00448887  7405                   -je 0x44888e
    if (cpu.flags.zf)
    {
        goto L_0x0044888e;
    }
    // 00448889  83fb02                 +cmp ebx, 2
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
    // 0044888c  7506                   -jne 0x448894
    if (!cpu.flags.zf)
    {
        goto L_0x00448894;
    }
L_0x0044888e:
    // 0044888e  804a0401               +or byte ptr [edx + 4], 1
    cpu.clear_co();
    cpu.set_szp((app->getMemory<x86::reg8>(cpu.edx + x86::reg32(4) /* 0x4 */) |= x86::reg8(x86::sreg8(1 /*0x1*/))));
    // 00448892  eb04                   -jmp 0x448898
    goto L_0x00448898;
L_0x00448894:
    // 00448894  806004fe               -and byte ptr [eax + 4], 0xfe
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(4) /* 0x4 */) &= x86::reg8(x86::sreg8(254 /*0xfe*/));
L_0x00448898:
    // 00448898  bac48e5300             -mov edx, 0x538ec4
    cpu.edx = 5476036 /*0x538ec4*/;
    // 0044889d  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 0044889f  e89ca1ffff             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004488a4  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004488a6  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004488a8  741a                   -je 0x4488c4
    if (cpu.flags.zf)
    {
        goto L_0x004488c4;
    }
    // 004488aa  8b3db8d36f00           -mov edi, dword ptr [0x6fd3b8]
    cpu.edi = app->getMemory<x86::reg32>(x86::reg32(7328696) /* 0x6fd3b8 */);
    // 004488b0  83ff01                 +cmp edi, 1
    {
        x86::reg32 tmp1 = cpu.edi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1 /*0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004488b3  7405                   -je 0x4488ba
    if (cpu.flags.zf)
    {
        goto L_0x004488ba;
    }
    // 004488b5  83ff02                 +cmp edi, 2
    {
        x86::reg32 tmp1 = cpu.edi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(2 /*0x2*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004488b8  7506                   -jne 0x4488c0
    if (!cpu.flags.zf)
    {
        goto L_0x004488c0;
    }
L_0x004488ba:
    // 004488ba  804a0401               +or byte ptr [edx + 4], 1
    cpu.clear_co();
    cpu.set_szp((app->getMemory<x86::reg8>(cpu.edx + x86::reg32(4) /* 0x4 */) |= x86::reg8(x86::sreg8(1 /*0x1*/))));
    // 004488be  eb04                   -jmp 0x4488c4
    goto L_0x004488c4;
L_0x004488c0:
    // 004488c0  806004fe               -and byte ptr [eax + 4], 0xfe
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(4) /* 0x4 */) &= x86::reg8(x86::sreg8(254 /*0xfe*/));
L_0x004488c4:
    // 004488c4  badc8e5300             -mov edx, 0x538edc
    cpu.edx = 5476060 /*0x538edc*/;
    // 004488c9  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004488cb  e870a1ffff             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004488d0  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004488d2  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004488d4  741a                   -je 0x4488f0
    if (cpu.flags.zf)
    {
        goto L_0x004488f0;
    }
    // 004488d6  8b35b8d36f00           -mov esi, dword ptr [0x6fd3b8]
    cpu.esi = app->getMemory<x86::reg32>(x86::reg32(7328696) /* 0x6fd3b8 */);
    // 004488dc  83fe01                 +cmp esi, 1
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
    // 004488df  7405                   -je 0x4488e6
    if (cpu.flags.zf)
    {
        goto L_0x004488e6;
    }
    // 004488e1  83fe02                 +cmp esi, 2
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
    // 004488e4  7506                   -jne 0x4488ec
    if (!cpu.flags.zf)
    {
        goto L_0x004488ec;
    }
L_0x004488e6:
    // 004488e6  804a0401               +or byte ptr [edx + 4], 1
    cpu.clear_co();
    cpu.set_szp((app->getMemory<x86::reg8>(cpu.edx + x86::reg32(4) /* 0x4 */) |= x86::reg8(x86::sreg8(1 /*0x1*/))));
    // 004488ea  eb04                   -jmp 0x4488f0
    goto L_0x004488f0;
L_0x004488ec:
    // 004488ec  806004fe               -and byte ptr [eax + 4], 0xfe
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(4) /* 0x4 */) &= x86::reg8(x86::sreg8(254 /*0xfe*/));
L_0x004488f0:
    // 004488f0  baf08e5300             -mov edx, 0x538ef0
    cpu.edx = 5476080 /*0x538ef0*/;
    // 004488f5  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004488f7  e844a1ffff             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004488fc  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004488fe  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00448900  741a                   -je 0x44891c
    if (cpu.flags.zf)
    {
        goto L_0x0044891c;
    }
    // 00448902  8b1db8d36f00           -mov ebx, dword ptr [0x6fd3b8]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(7328696) /* 0x6fd3b8 */);
    // 00448908  83fb01                 +cmp ebx, 1
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
    // 0044890b  7405                   -je 0x448912
    if (cpu.flags.zf)
    {
        goto L_0x00448912;
    }
    // 0044890d  83fb02                 +cmp ebx, 2
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
    // 00448910  7506                   -jne 0x448918
    if (!cpu.flags.zf)
    {
        goto L_0x00448918;
    }
L_0x00448912:
    // 00448912  804a0401               +or byte ptr [edx + 4], 1
    cpu.clear_co();
    cpu.set_szp((app->getMemory<x86::reg8>(cpu.edx + x86::reg32(4) /* 0x4 */) |= x86::reg8(x86::sreg8(1 /*0x1*/))));
    // 00448916  eb04                   -jmp 0x44891c
    goto L_0x0044891c;
L_0x00448918:
    // 00448918  806004fe               -and byte ptr [eax + 4], 0xfe
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(4) /* 0x4 */) &= x86::reg8(x86::sreg8(254 /*0xfe*/));
L_0x0044891c:
    // 0044891c  ba088f5300             -mov edx, 0x538f08
    cpu.edx = 5476104 /*0x538f08*/;
    // 00448921  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00448923  e818a1ffff             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00448928  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 0044892a  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0044892c  741a                   -je 0x448948
    if (cpu.flags.zf)
    {
        goto L_0x00448948;
    }
    // 0044892e  8b3db8d36f00           -mov edi, dword ptr [0x6fd3b8]
    cpu.edi = app->getMemory<x86::reg32>(x86::reg32(7328696) /* 0x6fd3b8 */);
    // 00448934  83ff01                 +cmp edi, 1
    {
        x86::reg32 tmp1 = cpu.edi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1 /*0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00448937  7405                   -je 0x44893e
    if (cpu.flags.zf)
    {
        goto L_0x0044893e;
    }
    // 00448939  83ff02                 +cmp edi, 2
    {
        x86::reg32 tmp1 = cpu.edi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(2 /*0x2*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0044893c  7506                   -jne 0x448944
    if (!cpu.flags.zf)
    {
        goto L_0x00448944;
    }
L_0x0044893e:
    // 0044893e  804a0401               +or byte ptr [edx + 4], 1
    cpu.clear_co();
    cpu.set_szp((app->getMemory<x86::reg8>(cpu.edx + x86::reg32(4) /* 0x4 */) |= x86::reg8(x86::sreg8(1 /*0x1*/))));
    // 00448942  eb04                   -jmp 0x448948
    goto L_0x00448948;
L_0x00448944:
    // 00448944  806004fe               -and byte ptr [eax + 4], 0xfe
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(4) /* 0x4 */) &= x86::reg8(x86::sreg8(254 /*0xfe*/));
L_0x00448948:
    // 00448948  ba208f5300             -mov edx, 0x538f20
    cpu.edx = 5476128 /*0x538f20*/;
    // 0044894d  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 0044894f  e8eca0ffff             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00448954  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 00448956  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00448958  741a                   -je 0x448974
    if (cpu.flags.zf)
    {
        goto L_0x00448974;
    }
    // 0044895a  8b35b8d36f00           -mov esi, dword ptr [0x6fd3b8]
    cpu.esi = app->getMemory<x86::reg32>(x86::reg32(7328696) /* 0x6fd3b8 */);
    // 00448960  83fe01                 +cmp esi, 1
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
    // 00448963  7405                   -je 0x44896a
    if (cpu.flags.zf)
    {
        goto L_0x0044896a;
    }
    // 00448965  83fe02                 +cmp esi, 2
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
    // 00448968  7506                   -jne 0x448970
    if (!cpu.flags.zf)
    {
        goto L_0x00448970;
    }
L_0x0044896a:
    // 0044896a  804a0401               +or byte ptr [edx + 4], 1
    cpu.clear_co();
    cpu.set_szp((app->getMemory<x86::reg8>(cpu.edx + x86::reg32(4) /* 0x4 */) |= x86::reg8(x86::sreg8(1 /*0x1*/))));
    // 0044896e  eb04                   -jmp 0x448974
    goto L_0x00448974;
L_0x00448970:
    // 00448970  806004fe               -and byte ptr [eax + 4], 0xfe
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(4) /* 0x4 */) &= x86::reg8(x86::sreg8(254 /*0xfe*/));
L_0x00448974:
    // 00448974  ba388f5300             -mov edx, 0x538f38
    cpu.edx = 5476152 /*0x538f38*/;
    // 00448979  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 0044897b  e8c0a0ffff             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00448980  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 00448982  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00448984  741a                   -je 0x4489a0
    if (cpu.flags.zf)
    {
        goto L_0x004489a0;
    }
    // 00448986  8b1db8d36f00           -mov ebx, dword ptr [0x6fd3b8]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(7328696) /* 0x6fd3b8 */);
    // 0044898c  83fb01                 +cmp ebx, 1
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
    // 0044898f  7405                   -je 0x448996
    if (cpu.flags.zf)
    {
        goto L_0x00448996;
    }
    // 00448991  83fb02                 +cmp ebx, 2
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
    // 00448994  7506                   -jne 0x44899c
    if (!cpu.flags.zf)
    {
        goto L_0x0044899c;
    }
L_0x00448996:
    // 00448996  804a0401               +or byte ptr [edx + 4], 1
    cpu.clear_co();
    cpu.set_szp((app->getMemory<x86::reg8>(cpu.edx + x86::reg32(4) /* 0x4 */) |= x86::reg8(x86::sreg8(1 /*0x1*/))));
    // 0044899a  eb04                   -jmp 0x4489a0
    goto L_0x004489a0;
L_0x0044899c:
    // 0044899c  806004fe               -and byte ptr [eax + 4], 0xfe
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(4) /* 0x4 */) &= x86::reg8(x86::sreg8(254 /*0xfe*/));
L_0x004489a0:
    // 004489a0  ba508f5300             -mov edx, 0x538f50
    cpu.edx = 5476176 /*0x538f50*/;
    // 004489a5  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004489a7  e894a0ffff             -call 0x442a40
    cpu.esp -= 4;
    nfs3hp::frontend::menuFindItem(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004489ac  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 004489ae  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004489b0  741a                   -je 0x4489cc
    if (cpu.flags.zf)
    {
        goto L_0x004489cc;
    }
    // 004489b2  8b3db8d36f00           -mov edi, dword ptr [0x6fd3b8]
    cpu.edi = app->getMemory<x86::reg32>(x86::reg32(7328696) /* 0x6fd3b8 */);
    // 004489b8  83ff01                 +cmp edi, 1
    {
        x86::reg32 tmp1 = cpu.edi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(1 /*0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004489bb  7405                   -je 0x4489c2
    if (cpu.flags.zf)
    {
        goto L_0x004489c2;
    }
    // 004489bd  83ff02                 +cmp edi, 2
    {
        x86::reg32 tmp1 = cpu.edi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(2 /*0x2*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004489c0  7506                   -jne 0x4489c8
    if (!cpu.flags.zf)
    {
        goto L_0x004489c8;
    }
L_0x004489c2:
    // 004489c2  804a0401               +or byte ptr [edx + 4], 1
    cpu.clear_co();
    cpu.set_szp((app->getMemory<x86::reg8>(cpu.edx + x86::reg32(4) /* 0x4 */) |= x86::reg8(x86::sreg8(1 /*0x1*/))));
    // 004489c6  eb04                   -jmp 0x4489cc
    goto L_0x004489cc;
L_0x004489c8:
    // 004489c8  806004fe               -and byte ptr [eax + 4], 0xfe
    app->getMemory<x86::reg8>(cpu.eax + x86::reg32(4) /* 0x4 */) &= x86::reg8(x86::sreg8(254 /*0xfe*/));
L_0x004489cc:
    // 004489cc  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 004489ce  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004489cf  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004489d0  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004489d1  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004489d2  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004489d3  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004489d4  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 0x8b 0xdb */
void Application::sub_4489e0(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (locationOnExit(app, cpu)) /* port: native (tools/apply_native_frontend.py) */
    {
        return;
    }
    // 004489e0  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004489e1  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 004489e3  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 004489e5  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004489e6  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_448f00: native, nfs3hp::port::menus::keywordIndex */

/* sub_448f50: native, nfs3hp::port::menus::storeString */

/* sub_448fd0: native, nfs3hp::port::menus::widgetType */

/* sub_449020: native, nfs3hp::port::menus::widgetName */

/* sub_449060: native, nfs3hp::port::menus::initItem */

/* sub_4490e0: native, nfs3hp::port::menus::sectionType */

/* sub_449130: native, nfs3hp::port::menus::parseInt */

/* sub_449170: native, nfs3hp::port::menus::parseLong */

/* sub_4491b0: native, nfs3hp::port::menus::parseFloat */

/* sub_449240: native, nfs3hp::port::menus::setField */

/* sub_4493b0: native, nfs3hp::port::menus::readEntry */

/* sub_449510: native, nfs3hp::port::menus::loadMenus */

/* sub_4498a0: native, nfs3hp::port::menus::checkMenuFile */

/* sub_449960: native, nfs3hp::port::menus::checkMenuFiles */

/* sub_449990: native, nfs3hp::port::menus::callOnLoad */

/* sub_4499b0: native, nfs3hp::port::loop::itemUsable */

/* sub_4499f0: native, nfs3hp::port::loop::keyAllowed */

/* sub_449a60: native, nfs3hp::decompiled::resetMenuHelp */

/* sub_449aa0: native, nfs3hp::port::loop::drawHelp */

/* sub_449df0: native, nfs3hp::port::loop::keysTaken */

/* sub_449e50: native, nfs3hp::port::loop::selectable */

/* sub_449ea0: native, nfs3hp::port::loop::pointAtSelected */

/* sub_449f30: native, nfs3hp::port::loop::selectPrevious */

/* sub_44a0c0: native, nfs3hp::port::loop::selectNext */

/* sub_44a240: native, nfs3hp::port::loop::escapeButton */

/* sub_44a2d0: native, nfs3hp::port::loop::handleKey */

/* sub_44a440: native, nfs3hp::port::loop::selectedIndex */

/* sub_44a470: native, nfs3hp::port::loop::selectItem */

/* sub_44a4f0: native, nfs3hp::port::loop::drawItems */

}
