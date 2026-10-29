#include "nfs3hp.h"
#include <lib/thread.h>

namespace nfs3hp
{

/* sub_5304ae: native, nfs3hp::dead::stub_0x5304ae */

/* sub_530503: native, nfs3hp::dead::stub_0x530503 */

/* sub_53054a: native, nfs3hp::dead::stub_0x53054a */

/* sub_530591: native, nfs3hp::dead::stub_0x530591 */

/* sub_5305d8: native, nfs3hp::dead::stub_0x5305d8 */

/* sub_53061f: native, nfs3hp::dead::stub_0x53061f */

/* sub_530666: native, nfs3hp::dead::stub_0x530666 */

/* sub_5306b1: native, nfs3hp::dead::stub_0x5306b1 */

/* sub_5306fc: native, nfs3hp::dead::stub_0x5306fc */

/* align: skip  */
void Application::sub_530747(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00530747  833d38d2560000         +cmp dword ptr [0x56d238], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5689912) /* 0x56d238 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0053074e  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 0053074f  8bec                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00530751  751f                   -jne 0x530772
    if (!cpu.flags.zf)
    {
        goto L_0x00530772;
    }
    // 00530753  6838d25600             -push 0x56d238
    app->getMemory<x86::reg32>(cpu.esp-4) = 5689912 /*0x56d238*/;
    cpu.esp -= 4;
    // 00530758  68d4be5600             -push 0x56bed4
    app->getMemory<x86::reg32>(cpu.esp-4) = 5684948 /*0x56bed4*/;
    cpu.esp -= 4;
    // 0053075d  e8b6ebffff             -call 0x52f318
    cpu.esp -= 4;
    sub_52f318(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00530762  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00530764  740c                   -je 0x530772
    if (cpu.flags.zf)
    {
        goto L_0x00530772;
    }
    // 00530766  c70538d25600ffffffff   -mov dword ptr [0x56d238], 0xffffffff
    app->getMemory<x86::reg32>(x86::reg32(5689912) /* 0x56d238 */) = 4294967295 /*0xffffffff*/;
    // 00530770  eb23                   -jmp 0x530795
    goto L_0x00530795;
L_0x00530772:
    // 00530772  833d38d25600ff         +cmp dword ptr [0x56d238], -1
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5689912) /* 0x56d238 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(-1 /*-0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00530779  b849000080             -mov eax, 0x80000049
    cpu.eax = 2147483721 /*0x80000049*/;
    // 0053077e  7415                   -je 0x530795
    if (cpu.flags.zf)
    {
        goto L_0x00530795;
    }
    // 00530780  ff7518                 -push dword ptr [ebp + 0x18]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(24) /* 0x18 */);
    cpu.esp -= 4;
    // 00530783  ff7514                 -push dword ptr [ebp + 0x14]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(20) /* 0x14 */);
    cpu.esp -= 4;
    // 00530786  ff7510                 -push dword ptr [ebp + 0x10]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(16) /* 0x10 */);
    cpu.esp -= 4;
    // 00530789  ff750c                 -push dword ptr [ebp + 0xc]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(12) /* 0xc */);
    cpu.esp -= 4;
    // 0053078c  ff7508                 -push dword ptr [ebp + 8]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(8) /* 0x8 */);
    cpu.esp -= 4;
    // 0053078f  ff1538d25600           -call dword ptr [0x56d238]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(5689912) /* 0x56d238 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00530795:
    // 00530795  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00530796  c21400                 -ret 0x14
    cpu.esp += 4+20 /*0x14*/;
    return;
}

/* sub_530799: native, nfs3hp::dead::stub_0x530799 */

/* sub_5307eb: native, nfs3hp::dead::stub_0x5307eb */

/* align: skip  */
void Application::sub_53083d(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0053083d  833d44d2560000         +cmp dword ptr [0x56d244], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5689924) /* 0x56d244 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00530844  751f                   -jne 0x530865
    if (!cpu.flags.zf)
    {
        goto L_0x00530865;
    }
    // 00530846  6844d25600             -push 0x56d244
    app->getMemory<x86::reg32>(cpu.esp-4) = 5689924 /*0x56d244*/;
    cpu.esp -= 4;
    // 0053084b  6804bf5600             -push 0x56bf04
    app->getMemory<x86::reg32>(cpu.esp-4) = 5684996 /*0x56bf04*/;
    cpu.esp -= 4;
    // 00530850  e8c3eaffff             -call 0x52f318
    cpu.esp -= 4;
    sub_52f318(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00530855  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00530857  740c                   -je 0x530865
    if (cpu.flags.zf)
    {
        goto L_0x00530865;
    }
    // 00530859  c70544d25600ffffffff   -mov dword ptr [0x56d244], 0xffffffff
    app->getMemory<x86::reg32>(x86::reg32(5689924) /* 0x56d244 */) = 4294967295 /*0xffffffff*/;
    // 00530863  eb20                   -jmp 0x530885
    goto L_0x00530885;
L_0x00530865:
    // 00530865  833d44d25600ff         +cmp dword ptr [0x56d244], -1
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5689924) /* 0x56d244 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(-1 /*-0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0053086c  b849000080             -mov eax, 0x80000049
    cpu.eax = 2147483721 /*0x80000049*/;
    // 00530871  7412                   -je 0x530885
    if (cpu.flags.zf)
    {
        goto L_0x00530885;
    }
    // 00530873  ff74240c               -push dword ptr [esp + 0xc]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(12) /* 0xc */);
    cpu.esp -= 4;
    // 00530877  ff74240c               -push dword ptr [esp + 0xc]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(12) /* 0xc */);
    cpu.esp -= 4;
    // 0053087b  ff74240c               -push dword ptr [esp + 0xc]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(12) /* 0xc */);
    cpu.esp -= 4;
    // 0053087f  ff1544d25600           -call dword ptr [0x56d244]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(5689924) /* 0x56d244 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00530885:
    // 00530885  c20c00                 -ret 0xc
    cpu.esp += 4+12 /*0xc*/;
    return;
}

/* sub_530888: native, nfs3hp::dead::stub_0x530888 */

/* sub_5308d3: native, nfs3hp::dead::stub_0x5308d3 */

/* sub_53091e: native, nfs3hp::dead::stub_0x53091e */

/* sub_53096d: native, nfs3hp::dead::stub_0x53096d */

/* sub_5309b8: native, nfs3hp::dead::stub_0x5309b8 */

/* sub_530a03: native, nfs3hp::dead::stub_0x530a03 */

/* align: skip  */
void Application::sub_530a4e(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00530a4e  833d60d2560000         +cmp dword ptr [0x56d260], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5689952) /* 0x56d260 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00530a55  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00530a56  8bec                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00530a58  751f                   -jne 0x530a79
    if (!cpu.flags.zf)
    {
        goto L_0x00530a79;
    }
    // 00530a5a  6860d25600             -push 0x56d260
    app->getMemory<x86::reg32>(cpu.esp-4) = 5689952 /*0x56d260*/;
    cpu.esp -= 4;
    // 00530a5f  687cbf5600             -push 0x56bf7c
    app->getMemory<x86::reg32>(cpu.esp-4) = 5685116 /*0x56bf7c*/;
    cpu.esp -= 4;
    // 00530a64  e8afe8ffff             -call 0x52f318
    cpu.esp -= 4;
    sub_52f318(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00530a69  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00530a6b  740c                   -je 0x530a79
    if (cpu.flags.zf)
    {
        goto L_0x00530a79;
    }
    // 00530a6d  c70560d25600ffffffff   -mov dword ptr [0x56d260], 0xffffffff
    app->getMemory<x86::reg32>(x86::reg32(5689952) /* 0x56d260 */) = 4294967295 /*0xffffffff*/;
    // 00530a77  eb26                   -jmp 0x530a9f
    goto L_0x00530a9f;
L_0x00530a79:
    // 00530a79  833d60d25600ff         +cmp dword ptr [0x56d260], -1
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5689952) /* 0x56d260 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(-1 /*-0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00530a80  b849000080             -mov eax, 0x80000049
    cpu.eax = 2147483721 /*0x80000049*/;
    // 00530a85  7418                   -je 0x530a9f
    if (cpu.flags.zf)
    {
        goto L_0x00530a9f;
    }
    // 00530a87  ff751c                 -push dword ptr [ebp + 0x1c]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(28) /* 0x1c */);
    cpu.esp -= 4;
    // 00530a8a  ff7518                 -push dword ptr [ebp + 0x18]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(24) /* 0x18 */);
    cpu.esp -= 4;
    // 00530a8d  ff7514                 -push dword ptr [ebp + 0x14]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(20) /* 0x14 */);
    cpu.esp -= 4;
    // 00530a90  ff7510                 -push dword ptr [ebp + 0x10]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(16) /* 0x10 */);
    cpu.esp -= 4;
    // 00530a93  ff750c                 -push dword ptr [ebp + 0xc]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(12) /* 0xc */);
    cpu.esp -= 4;
    // 00530a96  ff7508                 -push dword ptr [ebp + 8]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(8) /* 0x8 */);
    cpu.esp -= 4;
    // 00530a99  ff1560d25600           -call dword ptr [0x56d260]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(5689952) /* 0x56d260 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00530a9f:
    // 00530a9f  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00530aa0  c21800                 -ret 0x18
    cpu.esp += 4+24 /*0x18*/;
    return;
}

/* sub_530aa3: native, nfs3hp::dead::stub_0x530aa3 */

/* sub_530af8: native, nfs3hp::dead::stub_0x530af8 */

/* align: skip  */
void Application::sub_530b4d(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00530b4d  833d6cd2560000         +cmp dword ptr [0x56d26c], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5689964) /* 0x56d26c */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00530b54  751f                   -jne 0x530b75
    if (!cpu.flags.zf)
    {
        goto L_0x00530b75;
    }
    // 00530b56  686cd25600             -push 0x56d26c
    app->getMemory<x86::reg32>(cpu.esp-4) = 5689964 /*0x56d26c*/;
    cpu.esp -= 4;
    // 00530b5b  68a0bf5600             -push 0x56bfa0
    app->getMemory<x86::reg32>(cpu.esp-4) = 5685152 /*0x56bfa0*/;
    cpu.esp -= 4;
    // 00530b60  e8b3e7ffff             -call 0x52f318
    cpu.esp -= 4;
    sub_52f318(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00530b65  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00530b67  740c                   -je 0x530b75
    if (cpu.flags.zf)
    {
        goto L_0x00530b75;
    }
    // 00530b69  c7056cd25600ffffffff   -mov dword ptr [0x56d26c], 0xffffffff
    app->getMemory<x86::reg32>(x86::reg32(5689964) /* 0x56d26c */) = 4294967295 /*0xffffffff*/;
    // 00530b73  eb1c                   -jmp 0x530b91
    goto L_0x00530b91;
L_0x00530b75:
    // 00530b75  833d6cd25600ff         +cmp dword ptr [0x56d26c], -1
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5689964) /* 0x56d26c */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(-1 /*-0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00530b7c  b849000080             -mov eax, 0x80000049
    cpu.eax = 2147483721 /*0x80000049*/;
    // 00530b81  740e                   -je 0x530b91
    if (cpu.flags.zf)
    {
        goto L_0x00530b91;
    }
    // 00530b83  ff742408               -push dword ptr [esp + 8]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(8) /* 0x8 */);
    cpu.esp -= 4;
    // 00530b87  ff742408               -push dword ptr [esp + 8]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(8) /* 0x8 */);
    cpu.esp -= 4;
    // 00530b8b  ff156cd25600           -call dword ptr [0x56d26c]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(5689964) /* 0x56d26c */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00530b91:
    // 00530b91  c20800                 -ret 8
    cpu.esp += 4+8 /*0x8*/;
    return;
}

/* sub_530b94: native, nfs3hp::dead::stub_0x530b94 */

/* sub_530bdb: native, nfs3hp::dead::stub_0x530bdb */

/* sub_530c22: native, nfs3hp::dead::stub_0x530c22 */

/* sub_530c6d: native, nfs3hp::dead::stub_0x530c6d */

/* sub_530cb8: native, nfs3hp::dead::stub_0x530cb8 */

/* sub_530cff: native, nfs3hp::dead::stub_0x530cff */

/* sub_530d46: native, nfs3hp::dead::stub_0x530d46 */

/* sub_530d8d: native, nfs3hp::dead::stub_0x530d8d */

/* sub_530dd8: native, nfs3hp::dead::stub_0x530dd8 */

/* sub_530e23: native, nfs3hp::dead::stub_0x530e23 */

/* sub_530e6e: native, nfs3hp::dead::stub_0x530e6e */

/* sub_530eb9: native, nfs3hp::dead::stub_0x530eb9 */

/* sub_530f04: native, nfs3hp::dead::stub_0x530f04 */

/* sub_530f4f: native, nfs3hp::dead::stub_0x530f4f */

/* sub_530f9a: native, nfs3hp::dead::stub_0x530f9a */

/* sub_530fe5: native, nfs3hp::dead::stub_0x530fe5 */

/* sub_531030: native, nfs3hp::dead::stub_0x531030 */

/* sub_53107b: native, nfs3hp::dead::stub_0x53107b */

/* align: skip  */
void Application::sub_5310be(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 005310be  833db8d2560000         +cmp dword ptr [0x56d2b8], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5690040) /* 0x56d2b8 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 005310c5  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 005310c6  8bec                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 005310c8  751f                   -jne 0x5310e9
    if (!cpu.flags.zf)
    {
        goto L_0x005310e9;
    }
    // 005310ca  68b8d25600             -push 0x56d2b8
    app->getMemory<x86::reg32>(cpu.esp-4) = 5690040 /*0x56d2b8*/;
    cpu.esp -= 4;
    // 005310cf  6814c15600             -push 0x56c114
    app->getMemory<x86::reg32>(cpu.esp-4) = 5685524 /*0x56c114*/;
    cpu.esp -= 4;
    // 005310d4  e83fe2ffff             -call 0x52f318
    cpu.esp -= 4;
    sub_52f318(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 005310d9  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 005310db  740c                   -je 0x5310e9
    if (cpu.flags.zf)
    {
        goto L_0x005310e9;
    }
    // 005310dd  c705b8d25600ffffffff   -mov dword ptr [0x56d2b8], 0xffffffff
    app->getMemory<x86::reg32>(x86::reg32(5690040) /* 0x56d2b8 */) = 4294967295 /*0xffffffff*/;
    // 005310e7  eb23                   -jmp 0x53110c
    goto L_0x0053110c;
L_0x005310e9:
    // 005310e9  833db8d25600ff         +cmp dword ptr [0x56d2b8], -1
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5690040) /* 0x56d2b8 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(-1 /*-0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 005310f0  b849000080             -mov eax, 0x80000049
    cpu.eax = 2147483721 /*0x80000049*/;
    // 005310f5  7415                   -je 0x53110c
    if (cpu.flags.zf)
    {
        goto L_0x0053110c;
    }
    // 005310f7  ff7518                 -push dword ptr [ebp + 0x18]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(24) /* 0x18 */);
    cpu.esp -= 4;
    // 005310fa  ff7514                 -push dword ptr [ebp + 0x14]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(20) /* 0x14 */);
    cpu.esp -= 4;
    // 005310fd  ff7510                 -push dword ptr [ebp + 0x10]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(16) /* 0x10 */);
    cpu.esp -= 4;
    // 00531100  ff750c                 -push dword ptr [ebp + 0xc]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(12) /* 0xc */);
    cpu.esp -= 4;
    // 00531103  ff7508                 -push dword ptr [ebp + 8]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(8) /* 0x8 */);
    cpu.esp -= 4;
    // 00531106  ff15b8d25600           -call dword ptr [0x56d2b8]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(5690040) /* 0x56d2b8 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x0053110c:
    // 0053110c  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0053110d  c21400                 -ret 0x14
    cpu.esp += 4+20 /*0x14*/;
    return;
}

/* sub_531110: native, nfs3hp::dead::stub_0x531110 */

/* sub_531168: native, nfs3hp::dead::stub_0x531168 */

/* align: skip  */
void Application::sub_5311c0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 005311c0  833dc4d2560000         +cmp dword ptr [0x56d2c4], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5690052) /* 0x56d2c4 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 005311c7  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 005311c8  8bec                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 005311ca  751f                   -jne 0x5311eb
    if (!cpu.flags.zf)
    {
        goto L_0x005311eb;
    }
    // 005311cc  68c4d25600             -push 0x56d2c4
    app->getMemory<x86::reg32>(cpu.esp-4) = 5690052 /*0x56d2c4*/;
    cpu.esp -= 4;
    // 005311d1  684cc15600             -push 0x56c14c
    app->getMemory<x86::reg32>(cpu.esp-4) = 5685580 /*0x56c14c*/;
    cpu.esp -= 4;
    // 005311d6  e83de1ffff             -call 0x52f318
    cpu.esp -= 4;
    sub_52f318(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 005311db  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 005311dd  740c                   -je 0x5311eb
    if (cpu.flags.zf)
    {
        goto L_0x005311eb;
    }
    // 005311df  c705c4d25600ffffffff   -mov dword ptr [0x56d2c4], 0xffffffff
    app->getMemory<x86::reg32>(x86::reg32(5690052) /* 0x56d2c4 */) = 4294967295 /*0xffffffff*/;
    // 005311e9  eb23                   -jmp 0x53120e
    goto L_0x0053120e;
L_0x005311eb:
    // 005311eb  833dc4d25600ff         +cmp dword ptr [0x56d2c4], -1
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5690052) /* 0x56d2c4 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(-1 /*-0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 005311f2  b849000080             -mov eax, 0x80000049
    cpu.eax = 2147483721 /*0x80000049*/;
    // 005311f7  7415                   -je 0x53120e
    if (cpu.flags.zf)
    {
        goto L_0x0053120e;
    }
    // 005311f9  ff7518                 -push dword ptr [ebp + 0x18]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(24) /* 0x18 */);
    cpu.esp -= 4;
    // 005311fc  ff7514                 -push dword ptr [ebp + 0x14]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(20) /* 0x14 */);
    cpu.esp -= 4;
    // 005311ff  ff7510                 -push dword ptr [ebp + 0x10]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(16) /* 0x10 */);
    cpu.esp -= 4;
    // 00531202  ff750c                 -push dword ptr [ebp + 0xc]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(12) /* 0xc */);
    cpu.esp -= 4;
    // 00531205  ff7508                 -push dword ptr [ebp + 8]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(8) /* 0x8 */);
    cpu.esp -= 4;
    // 00531208  ff15c4d25600           -call dword ptr [0x56d2c4]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(5690052) /* 0x56d2c4 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x0053120e:
    // 0053120e  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 0053120f  c21400                 -ret 0x14
    cpu.esp += 4+20 /*0x14*/;
    return;
}

/* sub_531212: native, nfs3hp::dead::stub_0x531212 */

/* sub_531264: native, nfs3hp::dead::stub_0x531264 */

/* sub_5312b6: native, nfs3hp::dead::stub_0x5312b6 */

/* sub_5312fd: native, nfs3hp::dead::stub_0x5312fd */

/* sub_531344: native, nfs3hp::dead::stub_0x531344 */

/* align: skip  */
void Application::sub_53138f(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 0053138f  833ddcd2560000         +cmp dword ptr [0x56d2dc], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5690076) /* 0x56d2dc */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00531396  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00531397  8bec                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00531399  751f                   -jne 0x5313ba
    if (!cpu.flags.zf)
    {
        goto L_0x005313ba;
    }
    // 0053139b  68dcd25600             -push 0x56d2dc
    app->getMemory<x86::reg32>(cpu.esp-4) = 5690076 /*0x56d2dc*/;
    cpu.esp -= 4;
    // 005313a0  68b8c15600             -push 0x56c1b8
    app->getMemory<x86::reg32>(cpu.esp-4) = 5685688 /*0x56c1b8*/;
    cpu.esp -= 4;
    // 005313a5  e86edfffff             -call 0x52f318
    cpu.esp -= 4;
    sub_52f318(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 005313aa  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 005313ac  740c                   -je 0x5313ba
    if (cpu.flags.zf)
    {
        goto L_0x005313ba;
    }
    // 005313ae  c705dcd25600ffffffff   -mov dword ptr [0x56d2dc], 0xffffffff
    app->getMemory<x86::reg32>(x86::reg32(5690076) /* 0x56d2dc */) = 4294967295 /*0xffffffff*/;
    // 005313b8  eb26                   -jmp 0x5313e0
    goto L_0x005313e0;
L_0x005313ba:
    // 005313ba  833ddcd25600ff         +cmp dword ptr [0x56d2dc], -1
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5690076) /* 0x56d2dc */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(-1 /*-0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 005313c1  b849000080             -mov eax, 0x80000049
    cpu.eax = 2147483721 /*0x80000049*/;
    // 005313c6  7418                   -je 0x5313e0
    if (cpu.flags.zf)
    {
        goto L_0x005313e0;
    }
    // 005313c8  ff751c                 -push dword ptr [ebp + 0x1c]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(28) /* 0x1c */);
    cpu.esp -= 4;
    // 005313cb  ff7518                 -push dword ptr [ebp + 0x18]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(24) /* 0x18 */);
    cpu.esp -= 4;
    // 005313ce  ff7514                 -push dword ptr [ebp + 0x14]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(20) /* 0x14 */);
    cpu.esp -= 4;
    // 005313d1  ff7510                 -push dword ptr [ebp + 0x10]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(16) /* 0x10 */);
    cpu.esp -= 4;
    // 005313d4  ff750c                 -push dword ptr [ebp + 0xc]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(12) /* 0xc */);
    cpu.esp -= 4;
    // 005313d7  ff7508                 -push dword ptr [ebp + 8]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(8) /* 0x8 */);
    cpu.esp -= 4;
    // 005313da  ff15dcd25600           -call dword ptr [0x56d2dc]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(5690076) /* 0x56d2dc */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x005313e0:
    // 005313e0  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 005313e1  c21800                 -ret 0x18
    cpu.esp += 4+24 /*0x18*/;
    return;
}

/* sub_5313e4: native, nfs3hp::dead::stub_0x5313e4 */

/* align: skip  */
void Application::sub_531439(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00531439  833de4d2560000         +cmp dword ptr [0x56d2e4], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5690084) /* 0x56d2e4 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00531440  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00531441  8bec                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00531443  751f                   -jne 0x531464
    if (!cpu.flags.zf)
    {
        goto L_0x00531464;
    }
    // 00531445  68e4d25600             -push 0x56d2e4
    app->getMemory<x86::reg32>(cpu.esp-4) = 5690084 /*0x56d2e4*/;
    cpu.esp -= 4;
    // 0053144a  68e8c15600             -push 0x56c1e8
    app->getMemory<x86::reg32>(cpu.esp-4) = 5685736 /*0x56c1e8*/;
    cpu.esp -= 4;
    // 0053144f  e8c4deffff             -call 0x52f318
    cpu.esp -= 4;
    sub_52f318(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00531454  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00531456  740c                   -je 0x531464
    if (cpu.flags.zf)
    {
        goto L_0x00531464;
    }
    // 00531458  c705e4d25600ffffffff   -mov dword ptr [0x56d2e4], 0xffffffff
    app->getMemory<x86::reg32>(x86::reg32(5690084) /* 0x56d2e4 */) = 4294967295 /*0xffffffff*/;
    // 00531462  eb2f                   -jmp 0x531493
    goto L_0x00531493;
L_0x00531464:
    // 00531464  833de4d25600ff         +cmp dword ptr [0x56d2e4], -1
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5690084) /* 0x56d2e4 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(-1 /*-0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 0053146b  b849000080             -mov eax, 0x80000049
    cpu.eax = 2147483721 /*0x80000049*/;
    // 00531470  7421                   -je 0x531493
    if (cpu.flags.zf)
    {
        goto L_0x00531493;
    }
    // 00531472  ff7528                 -push dword ptr [ebp + 0x28]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(40) /* 0x28 */);
    cpu.esp -= 4;
    // 00531475  ff7524                 -push dword ptr [ebp + 0x24]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(36) /* 0x24 */);
    cpu.esp -= 4;
    // 00531478  ff7520                 -push dword ptr [ebp + 0x20]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(32) /* 0x20 */);
    cpu.esp -= 4;
    // 0053147b  ff751c                 -push dword ptr [ebp + 0x1c]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(28) /* 0x1c */);
    cpu.esp -= 4;
    // 0053147e  ff7518                 -push dword ptr [ebp + 0x18]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(24) /* 0x18 */);
    cpu.esp -= 4;
    // 00531481  ff7514                 -push dword ptr [ebp + 0x14]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(20) /* 0x14 */);
    cpu.esp -= 4;
    // 00531484  ff7510                 -push dword ptr [ebp + 0x10]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(16) /* 0x10 */);
    cpu.esp -= 4;
    // 00531487  ff750c                 -push dword ptr [ebp + 0xc]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(12) /* 0xc */);
    cpu.esp -= 4;
    // 0053148a  ff7508                 -push dword ptr [ebp + 8]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(8) /* 0x8 */);
    cpu.esp -= 4;
    // 0053148d  ff15e4d25600           -call dword ptr [0x56d2e4]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(5690084) /* 0x56d2e4 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00531493:
    // 00531493  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00531494  c22400                 -ret 0x24
    cpu.esp += 4+36 /*0x24*/;
    return;
}

/* sub_531497: native, nfs3hp::dead::stub_0x531497 */

/* sub_5314f5: native, nfs3hp::dead::stub_0x5314f5 */

/* sub_531553: native, nfs3hp::dead::stub_0x531553 */

/* sub_5315a2: native, nfs3hp::dead::stub_0x5315a2 */

/* sub_5315f1: native, nfs3hp::dead::stub_0x5315f1 */

/* sub_531640: native, nfs3hp::dead::stub_0x531640 */

/* sub_531692: native, nfs3hp::dead::stub_0x531692 */

/* sub_5316e4: native, nfs3hp::dead::stub_0x5316e4 */

/* sub_531736: native, nfs3hp::dead::stub_0x531736 */

/* sub_531781: native, nfs3hp::dead::stub_0x531781 */

/* sub_5317cc: native, nfs3hp::dead::stub_0x5317cc */

/* sub_531817: native, nfs3hp::dead::stub_0x531817 */

/* sub_53186c: native, nfs3hp::dead::stub_0x53186c */

/* sub_5318b7: native, nfs3hp::dead::stub_0x5318b7 */

/* sub_531902: native, nfs3hp::dead::stub_0x531902 */

/* sub_53194d: native, nfs3hp::dead::stub_0x53194d */

/* sub_531998: native, nfs3hp::dead::stub_0x531998 */

/* sub_5319e7: native, nfs3hp::dead::stub_0x5319e7 */

/* sub_531a2a: native, nfs3hp::dead::stub_0x531a2a */

/* sub_531a6d: native, nfs3hp::dead::stub_0x531a6d */

/* sub_531ab4: native, nfs3hp::dead::stub_0x531ab4 */

/* sub_531af7: native, nfs3hp::dead::stub_0x531af7 */

/* sub_531b42: native, nfs3hp::dead::stub_0x531b42 */

/* sub_531b8d: native, nfs3hp::dead::stub_0x531b8d */

/* sub_531bd8: native, nfs3hp::dead::stub_0x531bd8 */

/* sub_531c27: native, nfs3hp::dead::stub_0x531c27 */

/* sub_531c7c: native, nfs3hp::dead::stub_0x531c7c */

/* sub_531cd1: native, nfs3hp::dead::stub_0x531cd1 */

/* sub_531d26: native, nfs3hp::dead::stub_0x531d26 */

/* sub_531d6d: native, nfs3hp::dead::stub_0x531d6d */

/* sub_531db8: native, nfs3hp::dead::stub_0x531db8 */

/* sub_531e0a: native, nfs3hp::dead::stub_0x531e0a */

/* sub_531e51: native, nfs3hp::dead::stub_0x531e51 */

/* sub_531ea3: native, nfs3hp::dead::stub_0x531ea3 */

/* sub_531eea: native, nfs3hp::dead::stub_0x531eea */

/* align: skip  */
void Application::sub_531f31(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00531f31  833d74d3560000         +cmp dword ptr [0x56d374], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5690228) /* 0x56d374 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00531f38  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 00531f39  8bec                   -mov ebp, esp
    cpu.ebp = cpu.esp;
    // 00531f3b  751f                   -jne 0x531f5c
    if (!cpu.flags.zf)
    {
        goto L_0x00531f5c;
    }
    // 00531f3d  6874d35600             -push 0x56d374
    app->getMemory<x86::reg32>(cpu.esp-4) = 5690228 /*0x56d374*/;
    cpu.esp -= 4;
    // 00531f42  68a8c45600             -push 0x56c4a8
    app->getMemory<x86::reg32>(cpu.esp-4) = 5686440 /*0x56c4a8*/;
    cpu.esp -= 4;
    // 00531f47  e8ccd3ffff             -call 0x52f318
    cpu.esp -= 4;
    sub_52f318(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 00531f4c  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 00531f4e  740c                   -je 0x531f5c
    if (cpu.flags.zf)
    {
        goto L_0x00531f5c;
    }
    // 00531f50  c70574d35600ffffffff   -mov dword ptr [0x56d374], 0xffffffff
    app->getMemory<x86::reg32>(x86::reg32(5690228) /* 0x56d374 */) = 4294967295 /*0xffffffff*/;
    // 00531f5a  eb20                   -jmp 0x531f7c
    goto L_0x00531f7c;
L_0x00531f5c:
    // 00531f5c  833d74d35600ff         +cmp dword ptr [0x56d374], -1
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5690228) /* 0x56d374 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(-1 /*-0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00531f63  b849000080             -mov eax, 0x80000049
    cpu.eax = 2147483721 /*0x80000049*/;
    // 00531f68  7412                   -je 0x531f7c
    if (cpu.flags.zf)
    {
        goto L_0x00531f7c;
    }
    // 00531f6a  ff7514                 -push dword ptr [ebp + 0x14]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(20) /* 0x14 */);
    cpu.esp -= 4;
    // 00531f6d  ff7510                 -push dword ptr [ebp + 0x10]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(16) /* 0x10 */);
    cpu.esp -= 4;
    // 00531f70  ff750c                 -push dword ptr [ebp + 0xc]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(12) /* 0xc */);
    cpu.esp -= 4;
    // 00531f73  ff7508                 -push dword ptr [ebp + 8]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.ebp + x86::reg32(8) /* 0x8 */);
    cpu.esp -= 4;
    // 00531f76  ff1574d35600           -call dword ptr [0x56d374]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(5690228) /* 0x56d374 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x00531f7c:
    // 00531f7c  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 00531f7d  c21000                 -ret 0x10
    cpu.esp += 4+16 /*0x10*/;
    return;
}

/* sub_531f80: native, nfs3hp::dead::stub_0x531f80 */

/* sub_531fcf: native, nfs3hp::dead::stub_0x531fcf */

/* sub_53201e: native, nfs3hp::dead::stub_0x53201e */

/* sub_532069: native, nfs3hp::dead::stub_0x532069 */

/* sub_5320d0: native, nfs3hp::dead::stub_0x5320d0 */

/* sub_532117: native, nfs3hp::dead::stub_0x532117 */

/* align: skip  */
void Application::sub_532162(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 00532162  833d90d3560000         +cmp dword ptr [0x56d390], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5690256) /* 0x56d390 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00532169  751f                   -jne 0x53218a
    if (!cpu.flags.zf)
    {
        goto L_0x0053218a;
    }
    // 0053216b  6890d35600             -push 0x56d390
    app->getMemory<x86::reg32>(cpu.esp-4) = 5690256 /*0x56d390*/;
    cpu.esp -= 4;
    // 00532170  6834c55600             -push 0x56c534
    app->getMemory<x86::reg32>(cpu.esp-4) = 5686580 /*0x56c534*/;
    cpu.esp -= 4;
    // 00532175  e89ed1ffff             -call 0x52f318
    cpu.esp -= 4;
    sub_52f318(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 0053217a  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 0053217c  740c                   -je 0x53218a
    if (cpu.flags.zf)
    {
        goto L_0x0053218a;
    }
    // 0053217e  c70590d35600ffffffff   -mov dword ptr [0x56d390], 0xffffffff
    app->getMemory<x86::reg32>(x86::reg32(5690256) /* 0x56d390 */) = 4294967295 /*0xffffffff*/;
    // 00532188  eb20                   -jmp 0x5321aa
    goto L_0x005321aa;
L_0x0053218a:
    // 0053218a  833d90d35600ff         +cmp dword ptr [0x56d390], -1
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(x86::reg32(5690256) /* 0x56d390 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(-1 /*-0x1*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 00532191  b849000080             -mov eax, 0x80000049
    cpu.eax = 2147483721 /*0x80000049*/;
    // 00532196  7412                   -je 0x5321aa
    if (cpu.flags.zf)
    {
        goto L_0x005321aa;
    }
    // 00532198  ff74240c               -push dword ptr [esp + 0xc]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(12) /* 0xc */);
    cpu.esp -= 4;
    // 0053219c  ff74240c               -push dword ptr [esp + 0xc]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(12) /* 0xc */);
    cpu.esp -= 4;
    // 005321a0  ff74240c               -push dword ptr [esp + 0xc]
    app->getMemory<x86::reg32>(cpu.esp-4) = app->getMemory<x86::reg32>(cpu.esp + x86::reg32(12) /* 0xc */);
    cpu.esp -= 4;
    // 005321a4  ff1590d35600           -call dword ptr [0x56d390]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(5690256) /* 0x56d390 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
L_0x005321aa:
    // 005321aa  c20c00                 -ret 0xc
    cpu.esp += 4+12 /*0xc*/;
    return;
}

/* sub_5321ad: native, nfs3hp::dead::stub_0x5321ad */

/* sub_532205: native, nfs3hp::dead::stub_0x532205 */

/* sub_532254: native, nfs3hp::dead::stub_0x532254 */

/* sub_5322a3: native, nfs3hp::dead::stub_0x5322a3 */

}
