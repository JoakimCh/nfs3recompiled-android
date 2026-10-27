#include "nfs3hp.h"
#include <lib/thread.h>

namespace nfs3hp
{
// Port (tools/apply_native_loading.py): defined in native_loading.cpp.
bool frd(win32::WinApplication* app, x86::CPU& cpu);

/* sub_418d00: native, nfs3hp::load::swapBigEndian */

/* sub_418d40: native, nfs3hp::load::newFileNode */

/* sub_418d70: native, nfs3hp::load::freeFileNode */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 0x8b 0xdb */
void Application::sub_418db0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00418db0  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00418db1  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00418db3  83782800               +cmp dword ptr [eax + 0x28], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(40) /* 0x28 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00418db7  7507                   -jne 0x418dc0
    if (!cpu.flags.zf)
    {
        goto L_0x00418dc0;
    }
    // 00418db9  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 00418dbe  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00418dbf  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x00418dc0:
    // 00418dc0  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00418dc2  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00418dc3  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_418dd0: native, nfs3hp::load::findFileNode */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x54 0x22 0x00 */
void Application::sub_418e00(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00418e00  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00418e01  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00418e02  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00418e03  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00418e05  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00418e07  8b5028                 -mov edx, dword ptr [eax + 0x28]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(40) /* 0x28 */);
L_0x00418e0a:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00418e0a  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 00418e0c  7407                   -je 0x418e15
    if (cpu.flags.zf)
    {
        goto L_0x00418e15;
    }
    // 00418e0e  89d1                   -mov ecx, edx
    cpu.ecx = cpu.edx;
    // 00418e10  8b5228                 -mov edx, dword ptr [edx + 0x28]
    cpu.edx = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(40) /* 0x28 */);
    // 00418e13  ebf5                   -jmp 0x418e0a
    goto L_0x00418e0a;
L_0x00418e15:
    // 00418e15  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00418e17  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00418e18  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00418e19  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00418e1a  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x40 0x00 0x8b 0xc9 */
void Application::sub_418e20(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00418e20  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00418e21  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00418e22  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00418e24  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00418e26  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 00418e28  e883ffffff             -call 0x418db0
    cpu.esp -= 4;
    sub_418db0(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00418e2d  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00418e2f  752a                   -jne 0x418e5b
    if (!cpu.flags.zf)
    {
        goto L_0x00418e5b;
    }
    // 00418e31  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00418e33  e828000000             -call 0x418e60
    cpu.esp -= 4;
    sub_418e60(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00418e38  8b5028                 -mov edx, dword ptr [eax + 0x28]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(40) /* 0x28 */);
    // 00418e3b  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 00418e3d  741c                   -je 0x418e5b
    if (cpu.flags.zf)
    {
        goto L_0x00418e5b;
    }
    // 00418e3f  8b4a28                 -mov ecx, dword ptr [edx + 0x28]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(40) /* 0x28 */);
    // 00418e42  894828                 -mov dword ptr [eax + 0x28], ecx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(40) /* 0x28 */) = cpu.ecx;
    // 00418e45  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    // 00418e47  7403                   -je 0x418e4c
    if (cpu.flags.zf)
    {
        goto L_0x00418e4c;
    }
    // 00418e49  89412c                 -mov dword ptr [ecx + 0x2c], eax
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(44) /* 0x2c */) = cpu.eax;
L_0x00418e4c:
    // 00418e4c  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 00418e4e  e81dffffff             -call 0x418d70
    cpu.esp -= 4;
    nfs3hp::load::freeFileNode(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00418e53  b801000000             -mov eax, 1
    cpu.eax = 1 /*0x1*/;
    // 00418e58  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00418e59  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00418e5a  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x00418e5b:
    // 00418e5b  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00418e5d  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00418e5e  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00418e5f  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip  */
void Application::sub_418e60(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00418e60  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00418e61  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00418e62  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00418e63  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00418e65  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 00418e67  89d1                   -mov ecx, edx
    cpu.ecx = cpu.edx;
L_0x00418e69:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00418e69  8b5128                 -mov edx, dword ptr [ecx + 0x28]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(40) /* 0x28 */);
    // 00418e6c  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 00418e6e  7410                   -je 0x418e80
    if (cpu.flags.zf)
    {
        goto L_0x00418e80;
    }
    // 00418e70  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 00418e72  e849100d00             -call 0x4e9ec0
    cpu.esp -= 4;
    nfs3hp::watcom::stricmp(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00418e77  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00418e79  7405                   -je 0x418e80
    if (cpu.flags.zf)
    {
        goto L_0x00418e80;
    }
    // 00418e7b  8b4928                 -mov ecx, dword ptr [ecx + 0x28]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(40) /* 0x28 */);
    // 00418e7e  ebe9                   -jmp 0x418e69
    goto L_0x00418e69;
L_0x00418e80:
    // 00418e80  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00418e82  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00418e83  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00418e84  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00418e85  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_418e90: native, nfs3hp::load::insertFileNode */

/* sub_418f00: native, nfs3hp::load::newEmptyFileNode */

/* sub_418f40: native, nfs3hp::load::freeFileNodes */

/* sub_418f70: native, nfs3hp::load::countFileNodes */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x8d 0x40 0x00 */
void Application::sub_418fa0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00418fa0  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00418fa1  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00418fa2  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00418fa4  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 00418fa6  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 00418fa8  85c9                   +test ecx, ecx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ecx & cpu.ecx));
    // 00418faa  7422                   -je 0x418fce
    if (cpu.flags.zf)
    {
        goto L_0x00418fce;
    }
    // 00418fac  8b5104                 -mov edx, dword ptr [ecx + 4]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(4) /* 0x4 */);
    // 00418faf  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 00418fb1  741b                   -je 0x418fce
    if (cpu.flags.zf)
    {
        goto L_0x00418fce;
    }
    // 00418fb3  e868feffff             -call 0x418e20
    cpu.esp -= 4;
    sub_418e20(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00418fb8  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 00418fba  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00418fbc  740b                   -je 0x418fc9
    if (cpu.flags.zf)
    {
        goto L_0x00418fc9;
    }
    // 00418fbe  8b4104                 -mov eax, dword ptr [ecx + 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(4) /* 0x4 */);
    // 00418fc1  e83afeffff             -call 0x418e00
    cpu.esp -= 4;
    sub_418e00(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00418fc6  894108                 -mov dword ptr [ecx + 8], eax
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(8) /* 0x8 */) = cpu.eax;
L_0x00418fc9:
    // 00418fc9  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 00418fcb  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00418fcc  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00418fcd  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x00418fce:
    // 00418fce  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 00418fd0  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00418fd1  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00418fd2  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_418fe0: native, nfs3hp::load::findCachedFile */

/* sub_419000: native, nfs3hp::load::addCachedFile */

/* sub_419080: native, nfs3hp::load::newFileCache */

/* sub_4190e0: native, nfs3hp::load::freeFileCache */

/* sub_419120: native, nfs3hp::load::bigHeaderSize */

/* sub_4191b0: native, nfs3hp::load::cachedDataSize */

/* sub_4191e0: native, nfs3hp::load::writeBigFile */

/* sub_419460: native, nfs3hp::load::packFileCache */

/* sub_419510: native, nfs3hp::load::readBigFile */

/* sub_4195f0: native, nfs3hp::load::openFileCache */

/* sub_419660: native, nfs3hp::track::tintColours */

/* sub_419720: native, nfs3hp::track::tintObjectList */

/* sub_419750: native, nfs3hp::track::tintTrack */

/* sub_4197c0: native, nfs3hp::track::greyColours */

/* sub_419840: native, nfs3hp::track::greyObjectList */

/* sub_419870: native, nfs3hp::track::greyTrack */

/* sub_4198e0: native, nfs3hp::track::readObjectList */

/* sub_419ab0: native, nfs3hp::track::readLights */

/* sub_419b60: native, nfs3hp::track::newArena */

/* sub_419b90: native, nfs3hp::track::freeArena */

/* sub_419bc0: native, nfs3hp::track::arenaTake */

/* sub_419bf0: native, nfs3hp::track::frdRead */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 */
void Application::sub_419c20(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    if (frd(app, cpu.sync())) /* port: native (tools/apply_native_loading.py) */
    {
        cpu.reload();
        return;
    }
    // 00419c20  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 00419c21  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 00419c22  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 00419c23  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 00419c24  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 00419c25  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00419c26  89e5                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00419c28  83ec24                 -sub esp, 0x24
    (cpu.esp) -= x86::reg32(x86::sreg32(36 /*0x24*/));
    // 00419c2b  b8646c5300             -mov eax, 0x536c64
    cpu.eax = 5467236 /*0x536c64*/;
    // 00419c30  ba10000000             -mov edx, 0x10
    cpu.edx = 16 /*0x10*/;
    // 00419c35  e8663c0000             -call 0x41d8a0
    cpu.esp -= 4;
    nfs3hp::load::trackFilePath(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00419c3a  e881720c00             -call 0x4e0ec0
    cpu.esp -= 4;
    nfs3hp::ea::loadFile(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00419c3f  ba04000000             -mov edx, 4
    cpu.edx = 4 /*0x4*/;
    // 00419c44  a378d05d00             -mov dword ptr [0x5dd078], eax
    app->getMemory<x86::reg32>(x86::reg32(6148216) /* 0x5dd078 */) = cpu.eax;
    // 00419c49  a37cd05d00             -mov dword ptr [0x5dd07c], eax
    app->getMemory<x86::reg32>(x86::reg32(6148220) /* 0x5dd07c */) = cpu.eax;
    // 00419c4e  8d45e8                 -lea eax, [ebp - 0x18]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-24) /* -0x18 */);
    // 00419c51  e89affffff             -call 0x419bf0
    cpu.esp -= 4;
    nfs3hp::track::frdRead(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00419c56  ba08000000             -mov edx, 8
    cpu.edx = 8 /*0x8*/;
    // 00419c5b  8d45dc                 -lea eax, [ebp - 0x24]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-36) /* -0x24 */);
    // 00419c5e  e88dffffff             -call 0x419bf0
    cpu.esp -= 4;
    nfs3hp::track::frdRead(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00419c63  ba08000000             -mov edx, 8
    cpu.edx = 8 /*0x8*/;
    // 00419c68  8d45dc                 -lea eax, [ebp - 0x24]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-36) /* -0x24 */);
    // 00419c6b  e880ffffff             -call 0x419bf0
    cpu.esp -= 4;
    nfs3hp::track::frdRead(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00419c70  ba08000000             -mov edx, 8
    cpu.edx = 8 /*0x8*/;
    // 00419c75  8d45dc                 -lea eax, [ebp - 0x24]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-36) /* -0x24 */);
    // 00419c78  e873ffffff             -call 0x419bf0
    cpu.esp -= 4;
    nfs3hp::track::frdRead(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00419c7d  ba04000000             -mov edx, 4
    cpu.edx = 4 /*0x4*/;
    // 00419c82  b83cd85d00             -mov eax, 0x5dd83c
    cpu.eax = 6150204 /*0x5dd83c*/;
    // 00419c87  31ff                   -xor edi, edi
    cpu.edi ^= x86::reg32(x86::sreg32(cpu.edi));
L_0x00419c89:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00419c89  e862ffffff             -call 0x419bf0
    cpu.esp -= 4;
    nfs3hp::track::frdRead(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00419c8e  3b3d3cd85d00           +cmp edi, dword ptr [0x5dd83c]
    {
        x86::reg32 tmp1 = cpu.edi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(6150204) /* 0x5dd83c */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00419c94  0f8f87020000           -jg 0x419f21
    if (!cpu.flags.zf && (cpu.flags.sf == cpu.flags.of))
    {
        goto L_0x00419f21;
    }
    // 00419c9a  8d0cbd00000000         -lea ecx, [edi*4]
    cpu.ecx = x86::reg32(cpu.edi * 4);
    // 00419ca1  29f9                   -sub ecx, edi
    (cpu.ecx) -= x86::reg32(x86::sreg32(cpu.edi));
    // 00419ca3  c1e103                 -shl ecx, 3
    cpu.ecx <<= 3 /*0x3*/ % 32;
    // 00419ca6  29f9                   -sub ecx, edi
    (cpu.ecx) -= x86::reg32(x86::sreg32(cpu.edi));
    // 00419ca8  bb70135700             -mov ebx, 0x571370
    cpu.ebx = 5706608 /*0x571370*/;
    // 00419cad  c1e106                 -shl ecx, 6
    cpu.ecx <<= 6 /*0x6*/ % 32;
    // 00419cb0  01cb                   -add ebx, ecx
    (cpu.ebx) += x86::reg32(x86::sreg32(cpu.ecx));
    // 00419cb2  ba0c000000             -mov edx, 0xc
    cpu.edx = 12 /*0xc*/;
    // 00419cb7  8d4378                 -lea eax, [ebx + 0x78]
    cpu.eax = x86::reg32(cpu.ebx + x86::reg32(120) /* 0x78 */);
    // 00419cba  e831ffffff             -call 0x419bf0
    cpu.esp -= 4;
    nfs3hp::track::frdRead(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00419cbf  ba30000000             -mov edx, 0x30
    cpu.edx = 48 /*0x30*/;
    // 00419cc4  8d8384000000           -lea eax, [ebx + 0x84]
    cpu.eax = x86::reg32(cpu.ebx + x86::reg32(132) /* 0x84 */);
    // 00419cca  e821ffffff             -call 0x419bf0
    cpu.esp -= 4;
    nfs3hp::track::frdRead(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00419ccf  ba04000000             -mov edx, 4
    cpu.edx = 4 /*0x4*/;
    // 00419cd4  8d4358                 -lea eax, [ebx + 0x58]
    cpu.eax = x86::reg32(cpu.ebx + x86::reg32(88) /* 0x58 */);
    // 00419cd7  e814ffffff             -call 0x419bf0
    cpu.esp -= 4;
    nfs3hp::track::frdRead(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00419cdc  ba14000000             -mov edx, 0x14
    cpu.edx = 20 /*0x14*/;
    // 00419ce1  8d435c                 -lea eax, [ebx + 0x5c]
    cpu.eax = x86::reg32(cpu.ebx + x86::reg32(92) /* 0x5c */);
    // 00419ce4  e807ffffff             -call 0x419bf0
    cpu.esp -= 4;
    nfs3hp::track::frdRead(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00419ce9  8b81c8135700           -mov eax, dword ptr [ecx + 0x5713c8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(5706696) /* 0x5713c8 */);
    // 00419cef  8d348500000000         -lea esi, [eax*4]
    cpu.esi = x86::reg32(cpu.eax * 4);
    // 00419cf6  29c6                   -sub esi, eax
    (cpu.esi) -= x86::reg32(x86::sreg32(cpu.eax));
    // 00419cf8  c1e602                 -shl esi, 2
    cpu.esi <<= 2 /*0x2*/ % 32;
    // 00419cfb  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00419cfd  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 00419cff  e8bcfeffff             -call 0x419bc0
    cpu.esp -= 4;
    nfs3hp::track::arenaTake(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00419d04  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 00419d06  8981e0135700           -mov dword ptr [ecx + 0x5713e0], eax
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(5706720) /* 0x5713e0 */) = cpu.eax;
    // 00419d0c  e8dffeffff             -call 0x419bf0
    cpu.esp -= 4;
    nfs3hp::track::frdRead(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00419d11  8bb1c8135700           -mov esi, dword ptr [ecx + 0x5713c8]
    cpu.esi = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(5706696) /* 0x5713c8 */);
    // 00419d17  c1e602                 -shl esi, 2
    cpu.esi <<= 2 /*0x2*/ % 32;
    // 00419d1a  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00419d1c  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 00419d1e  e89dfeffff             -call 0x419bc0
    cpu.esp -= 4;
    nfs3hp::track::arenaTake(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00419d23  89f2                   -mov edx, esi
    cpu.edx = cpu.esi;
    // 00419d25  8981e4135700           -mov dword ptr [ecx + 0x5713e4], eax
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(5706724) /* 0x5713e4 */) = cpu.eax;
    // 00419d2b  e8c0feffff             -call 0x419bf0
    cpu.esp -= 4;
    nfs3hp::track::frdRead(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00419d30  bab0040000             -mov edx, 0x4b0
    cpu.edx = 1200 /*0x4b0*/;
    // 00419d35  8d83b4000000           -lea eax, [ebx + 0xb4]
    cpu.eax = x86::reg32(cpu.ebx + x86::reg32(180) /* 0xb4 */);
    // 00419d3b  e8b0feffff             -call 0x419bf0
    cpu.esp -= 4;
    nfs3hp::track::frdRead(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00419d40  ba04000000             -mov edx, 4
    cpu.edx = 4 /*0x4*/;
    // 00419d45  8d8384050000           -lea eax, [ebx + 0x584]
    cpu.eax = x86::reg32(cpu.ebx + x86::reg32(1412) /* 0x584 */);
    // 00419d4b  e8a0feffff             -call 0x419bf0
    cpu.esp -= 4;
    nfs3hp::track::frdRead(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00419d50  ba04000000             -mov edx, 4
    cpu.edx = 4 /*0x4*/;
    // 00419d55  8d8388050000           -lea eax, [ebx + 0x588]
    cpu.eax = x86::reg32(cpu.ebx + x86::reg32(1416) /* 0x588 */);
    // 00419d5b  e890feffff             -call 0x419bf0
    cpu.esp -= 4;
    nfs3hp::track::frdRead(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00419d60  ba04000000             -mov edx, 4
    cpu.edx = 4 /*0x4*/;
    // 00419d65  8d8390050000           -lea eax, [ebx + 0x590]
    cpu.eax = x86::reg32(cpu.ebx + x86::reg32(1424) /* 0x590 */);
    // 00419d6b  e880feffff             -call 0x419bf0
    cpu.esp -= 4;
    nfs3hp::track::frdRead(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00419d70  ba04000000             -mov edx, 4
    cpu.edx = 4 /*0x4*/;
    // 00419d75  8d8398050000           -lea eax, [ebx + 0x598]
    cpu.eax = x86::reg32(cpu.ebx + x86::reg32(1432) /* 0x598 */);
    // 00419d7b  e870feffff             -call 0x419bf0
    cpu.esp -= 4;
    nfs3hp::track::frdRead(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00419d80  ba04000000             -mov edx, 4
    cpu.edx = 4 /*0x4*/;
    // 00419d85  8d83a0050000           -lea eax, [ebx + 0x5a0]
    cpu.eax = x86::reg32(cpu.ebx + x86::reg32(1440) /* 0x5a0 */);
    // 00419d8b  e860feffff             -call 0x419bf0
    cpu.esp -= 4;
    nfs3hp::track::frdRead(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00419d90  ba04000000             -mov edx, 4
    cpu.edx = 4 /*0x4*/;
    // 00419d95  8d83a8050000           -lea eax, [ebx + 0x5a8]
    cpu.eax = x86::reg32(cpu.ebx + x86::reg32(1448) /* 0x5a8 */);
    // 00419d9b  e850feffff             -call 0x419bf0
    cpu.esp -= 4;
    nfs3hp::track::frdRead(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00419da0  ba04000000             -mov edx, 4
    cpu.edx = 4 /*0x4*/;
    // 00419da5  8d83b0050000           -lea eax, [ebx + 0x5b0]
    cpu.eax = x86::reg32(cpu.ebx + x86::reg32(1456) /* 0x5b0 */);
    // 00419dab  e840feffff             -call 0x419bf0
    cpu.esp -= 4;
    nfs3hp::track::frdRead(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00419db0  ba04000000             -mov edx, 4
    cpu.edx = 4 /*0x4*/;
    // 00419db5  8d83b8050000           -lea eax, [ebx + 0x5b8]
    cpu.eax = x86::reg32(cpu.ebx + x86::reg32(1464) /* 0x5b8 */);
    // 00419dbb  e830feffff             -call 0x419bf0
    cpu.esp -= 4;
    nfs3hp::track::frdRead(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00419dc0  8b81f8185700           -mov eax, dword ptr [ecx + 0x5718f8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(5708024) /* 0x5718f8 */);
    // 00419dc6  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00419dc8  c1e003                 -shl eax, 3
    cpu.eax <<= 3 /*0x3*/ % 32;
    // 00419dcb  e8f0fdffff             -call 0x419bc0
    cpu.esp -= 4;
    nfs3hp::track::arenaTake(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00419dd0  8981fc185700           -mov dword ptr [ecx + 0x5718fc], eax
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(5708028) /* 0x5718fc */) = cpu.eax;
    // 00419dd6  8b8100195700           -mov eax, dword ptr [ecx + 0x571900]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(5708032) /* 0x571900 */);
    // 00419ddc  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00419dde  c1e003                 -shl eax, 3
    cpu.eax <<= 3 /*0x3*/ % 32;
    // 00419de1  e8dafdffff             -call 0x419bc0
    cpu.esp -= 4;
    nfs3hp::track::arenaTake(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00419de6  8b9108195700           -mov edx, dword ptr [ecx + 0x571908]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(5708040) /* 0x571908 */);
    // 00419dec  898104195700           -mov dword ptr [ecx + 0x571904], eax
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(5708036) /* 0x571904 */) = cpu.eax;
    // 00419df2  8d049500000000         -lea eax, [edx*4]
    cpu.eax = x86::reg32(cpu.edx * 4);
    // 00419df9  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 00419dfb  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 00419dfe  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00419e00  e8bbfdffff             -call 0x419bc0
    cpu.esp -= 4;
    nfs3hp::track::arenaTake(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00419e05  8b9110195700           -mov edx, dword ptr [ecx + 0x571910]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(5708048) /* 0x571910 */);
    // 00419e0b  89810c195700           -mov dword ptr [ecx + 0x57190c], eax
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(5708044) /* 0x57190c */) = cpu.eax;
    // 00419e11  8d049500000000         -lea eax, [edx*4]
    cpu.eax = x86::reg32(cpu.edx * 4);
    // 00419e18  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 00419e1a  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 00419e1d  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00419e1f  e89cfdffff             -call 0x419bc0
    cpu.esp -= 4;
    nfs3hp::track::arenaTake(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00419e24  8b9118195700           -mov edx, dword ptr [ecx + 0x571918]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(5708056) /* 0x571918 */);
    // 00419e2a  898114195700           -mov dword ptr [ecx + 0x571914], eax
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(5708052) /* 0x571914 */) = cpu.eax;
    // 00419e30  8d049500000000         -lea eax, [edx*4]
    cpu.eax = x86::reg32(cpu.edx * 4);
    // 00419e37  01d0                   -add eax, edx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edx));
    // 00419e39  c1e002                 -shl eax, 2
    cpu.eax <<= 2 /*0x2*/ % 32;
    // 00419e3c  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00419e3e  e87dfdffff             -call 0x419bc0
    cpu.esp -= 4;
    nfs3hp::track::arenaTake(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00419e43  89811c195700           -mov dword ptr [ecx + 0x57191c], eax
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(5708060) /* 0x57191c */) = cpu.eax;
    // 00419e49  8b8120195700           -mov eax, dword ptr [ecx + 0x571920]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(5708064) /* 0x571920 */);
    // 00419e4f  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00419e51  c1e004                 -shl eax, 4
    cpu.eax <<= 4 /*0x4*/ % 32;
    // 00419e54  e867fdffff             -call 0x419bc0
    cpu.esp -= 4;
    nfs3hp::track::arenaTake(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00419e59  898124195700           -mov dword ptr [ecx + 0x571924], eax
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(5708068) /* 0x571924 */) = cpu.eax;
    // 00419e5f  8b8128195700           -mov eax, dword ptr [ecx + 0x571928]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(5708072) /* 0x571928 */);
    // 00419e65  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00419e67  c1e004                 -shl eax, 4
    cpu.eax <<= 4 /*0x4*/ % 32;
    // 00419e6a  e851fdffff             -call 0x419bc0
    cpu.esp -= 4;
    nfs3hp::track::arenaTake(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00419e6f  8b91f8185700           -mov edx, dword ptr [ecx + 0x5718f8]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(5708024) /* 0x5718f8 */);
    // 00419e75  89812c195700           -mov dword ptr [ecx + 0x57192c], eax
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(5708076) /* 0x57192c */) = cpu.eax;
    // 00419e7b  c1e203                 -shl edx, 3
    cpu.edx <<= 3 /*0x3*/ % 32;
    // 00419e7e  8b81fc185700           -mov eax, dword ptr [ecx + 0x5718fc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(5708028) /* 0x5718fc */);
    // 00419e84  e867fdffff             -call 0x419bf0
    cpu.esp -= 4;
    nfs3hp::track::frdRead(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00419e89  8b9100195700           -mov edx, dword ptr [ecx + 0x571900]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(5708032) /* 0x571900 */);
    // 00419e8f  8b8104195700           -mov eax, dword ptr [ecx + 0x571904]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(5708036) /* 0x571904 */);
    // 00419e95  c1e203                 -shl edx, 3
    cpu.edx <<= 3 /*0x3*/ % 32;
    // 00419e98  e853fdffff             -call 0x419bf0
    cpu.esp -= 4;
    nfs3hp::track::frdRead(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00419e9d  8b9108195700           -mov edx, dword ptr [ecx + 0x571908]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(5708040) /* 0x571908 */);
    // 00419ea3  8d049500000000         -lea eax, [edx*4]
    cpu.eax = x86::reg32(cpu.edx * 4);
    // 00419eaa  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 00419eac  8d148500000000         -lea edx, [eax*4]
    cpu.edx = x86::reg32(cpu.eax * 4);
    // 00419eb3  8b810c195700           -mov eax, dword ptr [ecx + 0x57190c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(5708044) /* 0x57190c */);
    // 00419eb9  e832fdffff             -call 0x419bf0
    cpu.esp -= 4;
    nfs3hp::track::frdRead(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00419ebe  8b9110195700           -mov edx, dword ptr [ecx + 0x571910]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(5708048) /* 0x571910 */);
    // 00419ec4  8d049500000000         -lea eax, [edx*4]
    cpu.eax = x86::reg32(cpu.edx * 4);
    // 00419ecb  01c2                   -add edx, eax
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.eax));
    // 00419ecd  c1e202                 -shl edx, 2
    cpu.edx <<= 2 /*0x2*/ % 32;
    // 00419ed0  8b8114195700           -mov eax, dword ptr [ecx + 0x571914]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(5708052) /* 0x571914 */);
    // 00419ed6  e815fdffff             -call 0x419bf0
    cpu.esp -= 4;
    nfs3hp::track::frdRead(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00419edb  8b9118195700           -mov edx, dword ptr [ecx + 0x571918]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(5708056) /* 0x571918 */);
    // 00419ee1  8d049500000000         -lea eax, [edx*4]
    cpu.eax = x86::reg32(cpu.edx * 4);
    // 00419ee8  01c2                   -add edx, eax
    (cpu.edx) += x86::reg32(x86::sreg32(cpu.eax));
    // 00419eea  c1e202                 -shl edx, 2
    cpu.edx <<= 2 /*0x2*/ % 32;
    // 00419eed  8b811c195700           -mov eax, dword ptr [ecx + 0x57191c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(5708060) /* 0x57191c */);
    // 00419ef3  e8f8fcffff             -call 0x419bf0
    cpu.esp -= 4;
    nfs3hp::track::frdRead(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00419ef8  8b9120195700           -mov edx, dword ptr [ecx + 0x571920]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(5708064) /* 0x571920 */);
    // 00419efe  8b8124195700           -mov eax, dword ptr [ecx + 0x571924]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(5708068) /* 0x571924 */);
    // 00419f04  c1e204                 -shl edx, 4
    cpu.edx <<= 4 /*0x4*/ % 32;
    // 00419f07  e8e4fcffff             -call 0x419bf0
    cpu.esp -= 4;
    nfs3hp::track::frdRead(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00419f0c  8b9128195700           -mov edx, dword ptr [ecx + 0x571928]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(5708072) /* 0x571928 */);
    // 00419f12  8b812c195700           -mov eax, dword ptr [ecx + 0x57192c]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(5708076) /* 0x57192c */);
    // 00419f18  c1e204                 +shl edx, 4
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
    // 00419f1b  47                     +inc edi
    {
        x86::reg32& tmp = cpu.edi;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 00419f1c  e968fdffff             -jmp 0x419c89
    goto L_0x00419c89;
L_0x00419f21:
    // 00419f21  31f6                   -xor esi, esi
    cpu.esi ^= x86::reg32(x86::sreg32(cpu.esi));
L_0x00419f23:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00419f23  3b353cd85d00           +cmp esi, dword ptr [0x5dd83c]
    {
        x86::reg32 tmp1 = cpu.esi;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(6150204) /* 0x5dd83c */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00419f29  0f8f4b010000           -jg 0x41a07a
    if (!cpu.flags.zf && (cpu.flags.sf == cpu.flags.of))
    {
        goto L_0x0041a07a;
    }
    // 00419f2f  8d14b500000000         -lea edx, [esi*4]
    cpu.edx = x86::reg32(cpu.esi * 4);
    // 00419f36  29f2                   -sub edx, esi
    (cpu.edx) -= x86::reg32(x86::sreg32(cpu.esi));
    // 00419f38  c1e203                 -shl edx, 3
    cpu.edx <<= 3 /*0x3*/ % 32;
    // 00419f3b  29f2                   -sub edx, esi
    (cpu.edx) -= x86::reg32(x86::sreg32(cpu.esi));
    // 00419f3d  b870135700             -mov eax, 0x571370
    cpu.eax = 5706608 /*0x571370*/;
    // 00419f42  c1e206                 -shl edx, 6
    cpu.edx <<= 6 /*0x6*/ % 32;
    // 00419f45  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
    // 00419f47  01d0                   +add eax, edx
    {
        x86::reg32& tmp1 = cpu.eax;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.edx));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 00419f49  891d80d05d00           -mov dword ptr [0x5dd080], ebx
    app->getMemory<x86::reg32>(x86::reg32(6148224) /* 0x5dd080 */) = cpu.ebx;
    // 00419f4f  8945fc                 -mov dword ptr [ebp - 4], eax
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */) = cpu.eax;
    // 00419f52  e910000000             -jmp 0x419f67
    goto L_0x00419f67;
L_0x00419f57:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00419f57  89819c135700           -mov dword ptr [ecx + 0x57139c], eax
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(5706652) /* 0x57139c */) = cpu.eax;
L_0x00419f5d:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 00419f5d  43                     -inc ebx
    (cpu.ebx)++;
    // 00419f5e  83fb0b                 +cmp ebx, 0xb
    {
        x86::reg32 tmp1 = cpu.ebx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(11 /*0xb*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00419f61  0f8d0d010000           -jge 0x41a074
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x0041a074;
    }
L_0x00419f67:
    // 00419f67  8d0cb500000000         -lea ecx, [esi*4]
    cpu.ecx = x86::reg32(cpu.esi * 4);
    // 00419f6e  29f1                   -sub ecx, esi
    (cpu.ecx) -= x86::reg32(x86::sreg32(cpu.esi));
    // 00419f70  c1e103                 -shl ecx, 3
    cpu.ecx <<= 3 /*0x3*/ % 32;
    // 00419f73  29f1                   -sub ecx, esi
    (cpu.ecx) -= x86::reg32(x86::sreg32(cpu.esi));
    // 00419f75  b870135700             -mov eax, 0x571370
    cpu.eax = 5706608 /*0x571370*/;
    // 00419f7a  c1e106                 -shl ecx, 6
    cpu.ecx <<= 6 /*0x6*/ % 32;
    // 00419f7d  8d3c9d00000000         -lea edi, [ebx*4]
    cpu.edi = x86::reg32(cpu.ebx * 4);
    // 00419f84  01c8                   -add eax, ecx
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.ecx));
    // 00419f86  ba04000000             -mov edx, 4
    cpu.edx = 4 /*0x4*/;
    // 00419f8b  01f8                   -add eax, edi
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.edi));
    // 00419f8d  01f9                   -add ecx, edi
    (cpu.ecx) += x86::reg32(x86::sreg32(cpu.edi));
    // 00419f8f  e85cfcffff             -call 0x419bf0
    cpu.esp -= 4;
    nfs3hp::track::frdRead(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00419f94  8b8170135700           -mov eax, dword ptr [ecx + 0x571370]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(5706608) /* 0x571370 */);
    // 00419f9a  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00419f9c  74b9                   -je 0x419f57
    if (cpu.flags.zf)
    {
        goto L_0x00419f57;
    }
    // 00419f9e  01c0                   -add eax, eax
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.eax));
    // 00419fa0  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 00419fa2  c1e003                 -shl eax, 3
    cpu.eax <<= 3 /*0x3*/ % 32;
    // 00419fa5  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 00419fa7  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 00419fa9  e812fcffff             -call 0x419bc0
    cpu.esp -= 4;
    nfs3hp::track::arenaTake(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00419fae  89819c135700           -mov dword ptr [ecx + 0x57139c], eax
    app->getMemory<x86::reg32>(cpu.ecx + x86::reg32(5706652) /* 0x57139c */) = cpu.eax;
    // 00419fb4  8b45fc                 -mov eax, dword ptr [ebp - 4]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-4) /* -0x4 */);
    // 00419fb7  8b4c072c               -mov ecx, dword ptr [edi + eax + 0x2c]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.edi + x86::reg32(44) /* 0x2c */ + cpu.eax * 1);
    // 00419fbb  83fb06                 +cmp ebx, 6
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
    // 00419fbe  7d27                   -jge 0x419fe7
    if (cpu.flags.sf == cpu.flags.of)
    {
        goto L_0x00419fe7;
    }
    // 00419fc0  ba04000000             -mov edx, 4
    cpu.edx = 4 /*0x4*/;
    // 00419fc5  8d45ec                 -lea eax, [ebp - 0x14]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-20) /* -0x14 */);
    // 00419fc8  e823fcffff             -call 0x419bf0
    cpu.esp -= 4;
    nfs3hp::track::frdRead(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00419fcd  8b45ec                 -mov eax, dword ptr [ebp - 0x14]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-20) /* -0x14 */);
    // 00419fd0  01c0                   -add eax, eax
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.eax));
    // 00419fd2  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 00419fd4  c1e003                 -shl eax, 3
    cpu.eax <<= 3 /*0x3*/ % 32;
    // 00419fd7  29d0                   +sub eax, edx
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
    // 00419fd9  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 00419fdb  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 00419fdd  e80efcffff             -call 0x419bf0
    cpu.esp -= 4;
    nfs3hp::track::frdRead(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00419fe2  e976ffffff             -jmp 0x419f5d
    goto L_0x00419f5d;
L_0x00419fe7:
    // 00419fe7  7527                   -jne 0x41a010
    if (!cpu.flags.zf)
    {
        goto L_0x0041a010;
    }
    // 00419fe9  ba04000000             -mov edx, 4
    cpu.edx = 4 /*0x4*/;
    // 00419fee  8d45f0                 -lea eax, [ebp - 0x10]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 00419ff1  e8fafbffff             -call 0x419bf0
    cpu.esp -= 4;
    nfs3hp::track::frdRead(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00419ff6  8b45f0                 -mov eax, dword ptr [ebp - 0x10]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-16) /* -0x10 */);
    // 00419ff9  01c0                   -add eax, eax
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.eax));
    // 00419ffb  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 00419ffd  c1e003                 -shl eax, 3
    cpu.eax <<= 3 /*0x3*/ % 32;
    // 0041a000  29d0                   +sub eax, edx
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
    // 0041a002  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 0041a004  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 0041a006  e8e5fbffff             -call 0x419bf0
    cpu.esp -= 4;
    nfs3hp::track::frdRead(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0041a00b  e94dffffff             -jmp 0x419f5d
    goto L_0x00419f5d;
L_0x0041a010:
    // 0041a010  ba04000000             -mov edx, 4
    cpu.edx = 4 /*0x4*/;
    // 0041a015  8d45e4                 -lea eax, [ebp - 0x1c]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-28) /* -0x1c */);
    // 0041a018  e8d3fbffff             -call 0x419bf0
    cpu.esp -= 4;
    nfs3hp::track::frdRead(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x0041a01d:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 0041a01d  8b7de4                 -mov edi, dword ptr [ebp - 0x1c]
    cpu.edi = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-28) /* -0x1c */);
    // 0041a020  4f                     -dec edi
    (cpu.edi)--;
    // 0041a021  897de4                 -mov dword ptr [ebp - 0x1c], edi
    app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-28) /* -0x1c */) = cpu.edi;
    // 0041a024  83ffff                 +cmp edi, -1
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
    // 0041a027  0f8430ffffff           -je 0x419f5d
    if (cpu.flags.zf)
    {
        goto L_0x00419f5d;
    }
    // 0041a02d  ba04000000             -mov edx, 4
    cpu.edx = 4 /*0x4*/;
    // 0041a032  8d45f4                 -lea eax, [ebp - 0xc]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 0041a035  e8b6fbffff             -call 0x419bf0
    cpu.esp -= 4;
    nfs3hp::track::frdRead(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0041a03a  8b55f4                 -mov edx, dword ptr [ebp - 0xc]
    cpu.edx = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-12) /* -0xc */);
    // 0041a03d  83fa01                 +cmp edx, 1
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
    // 0041a040  75db                   -jne 0x41a01d
    if (!cpu.flags.zf)
    {
        goto L_0x0041a01d;
    }
    // 0041a042  ba04000000             -mov edx, 4
    cpu.edx = 4 /*0x4*/;
    // 0041a047  8d45f8                 -lea eax, [ebp - 8]
    cpu.eax = x86::reg32(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 0041a04a  e8a1fbffff             -call 0x419bf0
    cpu.esp -= 4;
    nfs3hp::track::frdRead(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0041a04f  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 0041a052  01c0                   -add eax, eax
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.eax));
    // 0041a054  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 0041a056  c1e003                 -shl eax, 3
    cpu.eax <<= 3 /*0x3*/ % 32;
    // 0041a059  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 0041a05b  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 0041a05d  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 0041a05f  e88cfbffff             -call 0x419bf0
    cpu.esp -= 4;
    nfs3hp::track::frdRead(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0041a064  8b45f8                 -mov eax, dword ptr [ebp - 8]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(-8) /* -0x8 */);
    // 0041a067  01c0                   -add eax, eax
    (cpu.eax) += x86::reg32(x86::sreg32(cpu.eax));
    // 0041a069  89c2                   -mov edx, eax
    cpu.edx = cpu.eax;
    // 0041a06b  c1e003                 -shl eax, 3
    cpu.eax <<= 3 /*0x3*/ % 32;
    // 0041a06e  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 0041a070  01c1                   +add ecx, eax
    {
        x86::reg32& tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.eax));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 0041a072  eba9                   -jmp 0x41a01d
    goto L_0x0041a01d;
L_0x0041a074:
    // 0041a074  46                     +inc esi
    {
        x86::reg32& tmp = cpu.esi;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 0041a075  e9a9feffff             -jmp 0x419f23
    goto L_0x00419f23;
L_0x0041a07a:
    // 0041a07a  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
L_0x0041a07c:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 0041a07c  3b153cd85d00           +cmp edx, dword ptr [0x5dd83c]
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(app->getMemory<x86::reg32>(x86::reg32(6150204) /* 0x5dd83c */)));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0041a082  7f47                   -jg 0x41a0cb
    if (!cpu.flags.zf && (cpu.flags.sf == cpu.flags.of))
    {
        goto L_0x0041a0cb;
    }
    // 0041a084  8d049500000000         -lea eax, [edx*4]
    cpu.eax = x86::reg32(cpu.edx * 4);
    // 0041a08b  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 0041a08d  c1e003                 -shl eax, 3
    cpu.eax <<= 3 /*0x3*/ % 32;
    // 0041a090  29d0                   -sub eax, edx
    (cpu.eax) -= x86::reg32(x86::sreg32(cpu.edx));
    // 0041a092  b970135700             -mov ecx, 0x571370
    cpu.ecx = 5706608 /*0x571370*/;
    // 0041a097  c1e006                 -shl eax, 6
    cpu.eax <<= 6 /*0x6*/ % 32;
    // 0041a09a  01c1                   +add ecx, eax
    {
        x86::reg32& tmp1 = cpu.ecx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(cpu.eax));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 0041a09c  8d8164050000           -lea eax, [ecx + 0x564]
    cpu.eax = x86::reg32(cpu.ecx + x86::reg32(1380) /* 0x564 */);
    // 0041a0a2  e839f8ffff             -call 0x4198e0
    cpu.esp -= 4;
    nfs3hp::track::readObjectList(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0041a0a7  8d816c050000           -lea eax, [ecx + 0x56c]
    cpu.eax = x86::reg32(cpu.ecx + x86::reg32(1388) /* 0x56c */);
    // 0041a0ad  e82ef8ffff             -call 0x4198e0
    cpu.esp -= 4;
    nfs3hp::track::readObjectList(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0041a0b2  8d8174050000           -lea eax, [ecx + 0x574]
    cpu.eax = x86::reg32(cpu.ecx + x86::reg32(1396) /* 0x574 */);
    // 0041a0b8  e823f8ffff             -call 0x4198e0
    cpu.esp -= 4;
    nfs3hp::track::readObjectList(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0041a0bd  8d817c050000           -lea eax, [ecx + 0x57c]
    cpu.eax = x86::reg32(cpu.ecx + x86::reg32(1404) /* 0x57c */);
    // 0041a0c3  42                     +inc edx
    {
        x86::reg32& tmp = cpu.edx;
        cpu.flags.of = ~(1 & (tmp >> 31));
        tmp++;
        cpu.flags.of &= 1 & (tmp >> 31);
        cpu.set_szp(tmp);
    }
    // 0041a0c4  e817f8ffff             -call 0x4198e0
    cpu.esp -= 4;
    nfs3hp::track::readObjectList(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0041a0c9  ebb1                   -jmp 0x41a07c
    goto L_0x0041a07c;
L_0x0041a0cb:
    // 0041a0cb  b870d05d00             -mov eax, 0x5dd070
    cpu.eax = 6148208 /*0x5dd070*/;
    // 0041a0d0  e80bf8ffff             -call 0x4198e0
    cpu.esp -= 4;
    nfs3hp::track::readObjectList(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0041a0d5  e8d6f9ffff             -call 0x419ab0
    cpu.esp -= 4;
    nfs3hp::track::readLights(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0041a0da  8b1d7cd05d00           -mov ebx, dword ptr [0x5dd07c]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(6148220) /* 0x5dd07c */);
    // 0041a0e0  85db                   +test ebx, ebx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & cpu.ebx));
    // 0041a0e2  7407                   -je 0x41a0eb
    if (cpu.flags.zf)
    {
        goto L_0x0041a0eb;
    }
    // 0041a0e4  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 0041a0e6  e8a5770c00             -call 0x4e1890
    cpu.esp -= 4;
    nfs3hp::ea::purgememadr(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x0041a0eb:
    // 0041a0eb  89ec                   -mov esp, ebp
    cpu.esp = cpu.ebp;
    // 0041a0ed  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0041a0ee  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0041a0ef  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0041a0f0  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0041a0f1  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0041a0f2  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0041a0f3  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_41a100: native, nfs3hp::track::loadGeometry */

/* sub_41a120: native, nfs3hp::track::projectedTriangle */

/* sub_41a360: native, nfs3hp::vertices::projectedTriangle */

/* sub_41a3e0: native, nfs3hp::track::shadeVertex */

/* sub_41a550: native, nfs3hp::vertices::trackVertices */

/* sub_41a800: native, nfs3hp::track::setShadeDistances */

/* sub_41a8d0: native, nfs3hp::track::viewObjectVertices */

/* sub_41a970: native, nfs3hp::vertices::objectVerticesColoured */

/* sub_41a9b0: native, nfs3hp::track::viewTurnedObjectVertices */

/* sub_41aa60: native, nfs3hp::track::modelByDistance */

/* sub_41aab0: native, nfs3hp::vertices::groundDistanceOf */

/* sub_41aaf0: native, nfs3hp::track::viewOnBlock */

/* sub_41ab40: native, nfs3hp::track::lightObjectPolygons */

/* sub_41ae90: native, nfs3hp::vertices::trackPolygons */

/* sub_41b300: native, nfs3hp::vertices::trackRecords */

/* sub_41b640: native, nfs3hp::vertices::objectRecords */

/* sub_41b8c0: native, nfs3hp::track::bracketList */

/* sub_41b9b0: native, nfs3hp::render::viewPass */

/* sub_41bb50: native, nfs3hp::track::ambientSounds */

/* sub_41bc20: native, nfs3hp::track::ambientWanted */

/* sub_41bc50: native, nfs3hp::track::pointBehindView */

/* sub_41bc90: native, nfs3hp::track::litBoxOutside */

/* sub_41bf30: native, nfs3hp::vertices::boxOutside */

/* sub_41c1a0: native, nfs3hp::track::flushBuckets */

/* sub_41c310: native, nfs3hp::track::headlightsOnObjects */

/* sub_41c670: native, nfs3hp::track::headlightsOnBlock */

/* sub_41c9f0: native, nfs3hp::track::blockLights */

/* sub_41ca40: native, nfs3hp::track::drawObjectList */

/* sub_41cdc0: native, nfs3hp::track::drawTrack */

/* sub_41d210: native, nfs3hp::track::ambientSource */

/* sub_41d310: native, nfs3hp::track::selectView */

/* sub_41d350: native, nfs3hp::track::objectAnimation */

/* sub_41d510: native, nfs3hp::track::turnFromAngles */

/* sub_41d5a0: native, nfs3hp::track::turnFromPitchYaw */

/* sub_41d610: native, nfs3hp::track::setViewDistance */

/* sub_41d620: native, nfs3hp::render::viewDistances */

/* sub_41d870: native, nfs3hp::track::nextViewDistance */

/* sub_41d8a0: native, nfs3hp::load::trackFilePath */

/* sub_41d8d0: native, nfs3hp::load::trackFolderPath */

/* sub_41d900: native, nfs3hp::track::modelsUnlimited */

/* sub_41d960: native, nfs3hp::render::raceViews */

/* sub_41da40: native, nfs3hp::track::freeAt */

/* sub_41da60: native, nfs3hp::track::unloadTrack */

/* sub_41daa0: native, nfs3hp::track::newPool */

/* sub_41dae0: native, nfs3hp::track::newObjectPool */

/* sub_41db00: native, nfs3hp::track::freeTrackKinds */

/* sub_41db10: native, nfs3hp::track::loadTextures */

/* sub_41dbc0: native, nfs3hp::load::loadTrackTextures */

/* sub_41dc60: native, nfs3hp::track::takeTextures */

/* sub_41dcc0: native, nfs3hp::track::loadCollisions */

/* sub_41de10: native, nfs3hp::track::freeCollisions */

/* sub_41de40: native, nfs3hp::track::clearObjectStates */

/* sub_41de80: native, nfs3hp::track::resetTrackViews */

/* sub_41dea0: native, nfs3hp::track::resetViewsOuter */

/* sub_41deb0: native, nfs3hp::track::resetViews */

/* sub_41df10: native, nfs3hp::render::viewRecord */

/* sub_41e070: native, nfs3hp::track::blockInView */

/* sub_41e0f0: native, nfs3hp::vertices::nearestBlock */

/* sub_41e180: native, nfs3hp::trackdata::loadCcmPoints */

/* sub_41e2c0: native, nfs3hp::trackdata::freeCcmPoints */

/* sub_41e2f0: native, nfs3hp::trackdata::loadSimHeights */

/* sub_41e340: native, nfs3hp::trackdata::freeSimHeights */

/* sub_41e370: native, nfs3hp::trackdata::openTrackNodes */

/* sub_41e3b0: native, nfs3hp::trackdata::closeTrackNodes */

}
