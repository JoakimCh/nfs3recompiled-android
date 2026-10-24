#include "nfs3hp.h"
#include <lib/thread.h>

namespace nfs3hp
{

/* sub_4e4ec0: native, nfs3hp::snd::streamOpenQuietly */

/* sub_4e4ee0: native, nfs3hp::snd::streamOpenNext */

/* sub_4e4f00: native, nfs3hp::snd::streamOpenNextQuietly */

/* sub_4e4f20: native, nfs3hp::snd::streamContinue */

/* sub_4e4f40: native, nfs3hp::snd::streamContinueQuietly */

/* sub_4e4f60: native, nfs3hp::snd::streamSwitch */

/* sub_4e4f80: native, nfs3hp::snd::streamSwitchQuietly */

/* sub_4e4fa0: native, nfs3hp::snd::streamQueueFile */

/* sub_4e4fc0: native, nfs3hp::snd::streamQueueFileQuietly */

/* sub_4e4fe0: native, nfs3hp::snd::streamRestart */

/* sub_4e5000: native, nfs3hp::snd::streamRestartQuietly */

/* sub_4e5020: native, nfs3hp::snd::streamSeek */

/* sub_4e5040: native, nfs3hp::snd::streamSeekQuietly */

/* sub_4e5060: native, nfs3hp::snd::streamReadOn */

/* sub_4e5080: native, nfs3hp::snd::streamReadOnQuietly */

/* sub_4e50a0: native, nfs3hp::snd::streamStopAt */

/* sub_4e50c0: native, nfs3hp::snd::streamStopAtQuietly */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8b 0xd2 */
void Application::sub_4e50e0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004e50e0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004e50e1  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004e50e2  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004e50e3  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004e50e4  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 004e50e6  31f6                   -xor esi, esi
    cpu.esi ^= x86::reg32(x86::sreg32(cpu.esi));
    // 004e50e8  8b80ac000000           -mov eax, dword ptr [eax + 0xac]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(172) /* 0xac */);
    // 004e50ee  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004e50ef  ff15b8445300           -call dword ptr [0x5344b8]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(5457080) /* 0x5344b8 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e50f5  837b7800               +cmp dword ptr [ebx + 0x78], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(120) /* 0x78 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004e50f9  7425                   -je 0x4e5120
    if (cpu.flags.zf)
    {
        goto L_0x004e5120;
    }
L_0x004e50fb:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004e50fb  46                     -inc esi
    (cpu.esi)++;
    // 004e50fc  8b4378                 -mov eax, dword ptr [ebx + 0x78]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(120) /* 0x78 */);
    // 004e50ff  8b9098000000           -mov edx, dword ptr [eax + 0x98]
    cpu.edx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(152) /* 0x98 */);
    // 004e5105  895378                 -mov dword ptr [ebx + 0x78], edx
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(120) /* 0x78 */) = cpu.edx;
    // 004e5108  e813190000             -call 0x4e6a20
    cpu.esp -= 4;
    nfs3hp::snd::freeCommandBlock(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e510d  837b7800               +cmp dword ptr [ebx + 0x78], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(120) /* 0x78 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004e5111  75e8                   -jne 0x4e50fb
    if (!cpu.flags.zf)
    {
        goto L_0x004e50fb;
    }
    // 004e5113  8d8000000000           -lea eax, [eax]
    cpu.eax = x86::reg32(cpu.eax);
    // 004e5119  8d9200000000           -lea edx, [edx]
    cpu.edx = x86::reg32(cpu.edx);
    // 004e511f  90                     -nop 
    ;
L_0x004e5120:
    // 004e5120  8b4378                 -mov eax, dword ptr [ebx + 0x78]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(120) /* 0x78 */);
    // 004e5123  89437c                 -mov dword ptr [ebx + 0x7c], eax
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(124) /* 0x7c */) = cpu.eax;
    // 004e5126  8b83ac000000           -mov eax, dword ptr [ebx + 0xac]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(172) /* 0xac */);
    // 004e512c  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004e512d  ff1588455300           -call dword ptr [0x534588]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(5457288) /* 0x534588 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e5133  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004e5135  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e5136  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e5137  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e5138  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e5139  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 */
void Application::sub_4e5140(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004e5140  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004e5141  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004e5142  89d6                   -mov esi, edx
    cpu.esi = cpu.edx;
    // 004e5144  89da                   -mov edx, ebx
    cpu.edx = cpu.ebx;
    // 004e5146  89c3                   -mov ebx, eax
    cpu.ebx = cpu.eax;
    // 004e5148  8b8884000000           -mov ecx, dword ptr [eax + 0x84]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(132) /* 0x84 */);
    // 004e514e  89483c                 -mov dword ptr [eax + 0x3c], ecx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(60) /* 0x3c */) = cpu.ecx;
    // 004e5151  8b8888000000           -mov ecx, dword ptr [eax + 0x88]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(136) /* 0x88 */);
    // 004e5157  894804                 -mov dword ptr [eax + 4], ecx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */) = cpu.ecx;
    // 004e515a  8b8888000000           -mov ecx, dword ptr [eax + 0x88]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(136) /* 0x88 */);
    // 004e5160  8bb884000000           -mov edi, dword ptr [eax + 0x84]
    cpu.edi = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(132) /* 0x84 */);
    // 004e5166  01f9                   -add ecx, edi
    (cpu.ecx) += x86::reg32(x86::sreg32(cpu.edi));
    // 004e5168  894808                 -mov dword ptr [eax + 8], ecx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(8) /* 0x8 */) = cpu.ecx;
    // 004e516b  8b4804                 -mov ecx, dword ptr [eax + 4]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(4) /* 0x4 */);
    // 004e516e  894818                 -mov dword ptr [eax + 0x18], ecx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */) = cpu.ecx;
    // 004e5171  8b4818                 -mov ecx, dword ptr [eax + 0x18]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(24) /* 0x18 */);
    // 004e5174  894814                 -mov dword ptr [eax + 0x14], ecx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */) = cpu.ecx;
    // 004e5177  8b4814                 -mov ecx, dword ptr [eax + 0x14]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(20) /* 0x14 */);
    // 004e517a  89480c                 -mov dword ptr [eax + 0xc], ecx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */) = cpu.ecx;
    // 004e517d  8b480c                 -mov ecx, dword ptr [eax + 0xc]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(12) /* 0xc */);
    // 004e5180  894810                 -mov dword ptr [eax + 0x10], ecx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(16) /* 0x10 */) = cpu.ecx;
    // 004e5183  c780bc00000000000000   -mov dword ptr [eax + 0xbc], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(188) /* 0xbc */) = 0 /*0x0*/;
    // 004e518d  8b88bc000000           -mov ecx, dword ptr [eax + 0xbc]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(188) /* 0xbc */);
    // 004e5193  8988b8000000           -mov dword ptr [eax + 0xb8], ecx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(184) /* 0xb8 */) = cpu.ecx;
    // 004e5199  c7402800000000         -mov dword ptr [eax + 0x28], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(40) /* 0x28 */) = 0 /*0x0*/;
    // 004e51a0  c7404000000000         -mov dword ptr [eax + 0x40], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(64) /* 0x40 */) = 0 /*0x0*/;
    // 004e51a7  c7405c00000000         -mov dword ptr [eax + 0x5c], 0
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(92) /* 0x5c */) = 0 /*0x0*/;
    // 004e51ae  c7405401000000         -mov dword ptr [eax + 0x54], 1
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(84) /* 0x54 */) = 1 /*0x1*/;
    // 004e51b5  89506c                 -mov dword ptr [eax + 0x6c], edx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(108) /* 0x6c */) = cpu.edx;
    // 004e51b8  897068                 -mov dword ptr [eax + 0x68], esi
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(104) /* 0x68 */) = cpu.esi;
    // 004e51bb  8b15b8455600           -mov edx, dword ptr [0x5645b8]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5653944) /* 0x5645b8 */);
    // 004e51c1  8b8aac000000           -mov ecx, dword ptr [edx + 0xac]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(172) /* 0xac */);
    // 004e51c7  8988ac000000           -mov dword ptr [eax + 0xac], ecx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(172) /* 0xac */) = cpu.ecx;
    // 004e51cd  8b8aa8000000           -mov ecx, dword ptr [edx + 0xa8]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(168) /* 0xa8 */);
    // 004e51d3  8988a8000000           -mov dword ptr [eax + 0xa8], ecx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(168) /* 0xa8 */) = cpu.ecx;
    // 004e51d9  8db88c000000           -lea edi, [eax + 0x8c]
    cpu.edi = x86::reg32(cpu.eax + x86::reg32(140) /* 0x8c */);
    // 004e51df  8db28c000000           -lea esi, [edx + 0x8c]
    cpu.esi = x86::reg32(cpu.edx + x86::reg32(140) /* 0x8c */);
    // 004e51e5  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004e51e6  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004e51e7  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004e51e8  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004e51e9  a5                     -movsd dword ptr es:[edi], dword ptr [esi]
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
    // 004e51ea  8b8aa4000000           -mov ecx, dword ptr [edx + 0xa4]
    cpu.ecx = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(164) /* 0xa4 */);
    // 004e51f0  8988a4000000           -mov dword ptr [eax + 0xa4], ecx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(164) /* 0xa4 */) = cpu.ecx;
    // 004e51f6  8b82ac000000           -mov eax, dword ptr [edx + 0xac]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(172) /* 0xac */);
    // 004e51fc  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004e51fd  ff15b8445300           -call dword ptr [0x5344b8]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(5457080) /* 0x5344b8 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e5203  a1b8455600             -mov eax, dword ptr [0x5645b8]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5653944) /* 0x5645b8 */);
    // 004e5208  83787000               +cmp dword ptr [eax + 0x70], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(112) /* 0x70 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004e520c  7412                   -je 0x4e5220
    if (cpu.flags.zf)
    {
        goto L_0x004e5220;
    }
L_0x004e520e:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004e520e  8b4070                 -mov eax, dword ptr [eax + 0x70]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(112) /* 0x70 */);
    // 004e5211  83787000               +cmp dword ptr [eax + 0x70], 0
    {
        x86::reg32 tmp1 = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(112) /* 0x70 */);
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(0 /*0x0*/));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    // 004e5215  75f7                   -jne 0x4e520e
    if (!cpu.flags.zf)
    {
        goto L_0x004e520e;
    }
    // 004e5217  8d8000000000           -lea eax, [eax]
    cpu.eax = x86::reg32(cpu.eax);
    // 004e521d  8d5200                 -lea edx, [edx]
    cpu.edx = x86::reg32(cpu.edx);
L_0x004e5220:
    // 004e5220  895870                 -mov dword ptr [eax + 0x70], ebx
    app->getMemory<x86::reg32>(cpu.eax + x86::reg32(112) /* 0x70 */) = cpu.ebx;
    // 004e5223  c7437000000000         -mov dword ptr [ebx + 0x70], 0
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(112) /* 0x70 */) = 0 /*0x0*/;
    // 004e522a  a1b8455600             -mov eax, dword ptr [0x5645b8]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5653944) /* 0x5645b8 */);
    // 004e522f  8b80ac000000           -mov eax, dword ptr [eax + 0xac]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(172) /* 0xac */);
    // 004e5235  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004e5236  ff1588455300           -call dword ptr [0x534588]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(5457288) /* 0x534588 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e523c  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 004e523e  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e523f  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e5240  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 0x8d 0x40 0x00 */
void Application::sub_4e5250(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004e5250  56                     -push esi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.esi;
    cpu.esp -= 4;
    // 004e5251  57                     -push edi
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edi;
    cpu.esp -= 4;
    // 004e5252  55                     -push ebp
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebp;
    cpu.esp -= 4;
    // 004e5253  83ec04                 -sub esp, 4
    (cpu.esp) -= x86::reg32(x86::sreg32(4 /*0x4*/));
    // 004e5256  89c5                   -mov ebp, eax
    cpu.ebp = cpu.eax;
    // 004e5258  891424                 -mov dword ptr [esp], edx
    app->getMemory<x86::reg32>(cpu.esp) = cpu.edx;
    // 004e525b  89ce                   -mov esi, ecx
    cpu.esi = cpu.ecx;
    // 004e525d  89d9                   -mov ecx, ebx
    cpu.ecx = cpu.ebx;
    // 004e525f  66f7c3ff0f             +test bx, 0xfff
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg16>(cpu.bx & 4095 /*0xfff*/));
    // 004e5264  740c                   -je 0x4e5272
    if (cpu.flags.zf)
    {
        goto L_0x004e5272;
    }
    // 004e5266  8d8b00100000           -lea ecx, [ebx + 0x1000]
    cpu.ecx = x86::reg32(cpu.ebx + x86::reg32(4096) /* 0x1000 */);
    // 004e526c  81e100f0ff7f           -and ecx, 0x7ffff000
    cpu.ecx &= x86::reg32(x86::sreg32(2147479552 /*0x7ffff000*/));
L_0x004e5272:
    // 004e5272  bad0a35400             -mov edx, 0x54a3d0
    cpu.edx = 5546960 /*0x54a3d0*/;
    // 004e5277  bb48a75400             -mov ebx, 0x54a748
    cpu.ebx = 5547848 /*0x54a748*/;
    // 004e527c  bfcd040000             -mov edi, 0x4cd
    cpu.edi = 1229 /*0x4cd*/;
    // 004e5281  b8f8a45400             -mov eax, 0x54a4f8
    cpu.eax = 5547256 /*0x54a4f8*/;
    // 004e5286  891590215500           -mov dword ptr [0x552190], edx
    app->getMemory<x86::reg32>(x86::reg32(5579152) /* 0x552190 */) = cpu.edx;
    // 004e528c  891d94215500           -mov dword ptr [0x552194], ebx
    app->getMemory<x86::reg32>(x86::reg32(5579156) /* 0x552194 */) = cpu.ebx;
    // 004e5292  89f3                   -mov ebx, esi
    cpu.ebx = cpu.esi;
    // 004e5294  89ca                   -mov edx, ecx
    cpu.edx = cpu.ecx;
    // 004e5296  893d98215500           -mov dword ptr [0x552198], edi
    app->getMemory<x86::reg32>(x86::reg32(5579160) /* 0x552198 */) = cpu.edi;
    // 004e529c  e87fc3ffff             -call 0x4e1620
    cpu.esp -= 4;
    nfs3hp::ea::reservememadr(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e52a1  89c7                   -mov edi, eax
    cpu.edi = cpu.eax;
    // 004e52a3  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004e52a5  0f8486000000           -je 0x4e5331
    if (cpu.flags.zf)
    {
        goto L_0x004e5331;
    }
L_0x004e52ab:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004e52ab  b8d0a35400             -mov eax, 0x54a3d0
    cpu.eax = 5546960 /*0x54a3d0*/;
    // 004e52b0  ba48a75400             -mov edx, 0x54a748
    cpu.edx = 5547848 /*0x54a748*/;
    // 004e52b5  bbd3040000             -mov ebx, 0x4d3
    cpu.ebx = 1235 /*0x4d3*/;
    // 004e52ba  a390215500             -mov dword ptr [0x552190], eax
    app->getMemory<x86::reg32>(x86::reg32(5579152) /* 0x552190 */) = cpu.eax;
    // 004e52bf  891594215500           -mov dword ptr [0x552194], edx
    app->getMemory<x86::reg32>(x86::reg32(5579156) /* 0x552194 */) = cpu.edx;
    // 004e52c5  891d98215500           -mov dword ptr [0x552198], ebx
    app->getMemory<x86::reg32>(x86::reg32(5579160) /* 0x552198 */) = cpu.ebx;
    // 004e52cb  bac0000000             -mov edx, 0xc0
    cpu.edx = 192 /*0xc0*/;
    // 004e52d0  b858a75400             -mov eax, 0x54a758
    cpu.eax = 5547864 /*0x54a758*/;
    // 004e52d5  89f3                   -mov ebx, esi
    cpu.ebx = cpu.esi;
    // 004e52d7  e844c3ffff             -call 0x4e1620
    cpu.esp -= 4;
    nfs3hp::ea::reservememadr(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e52dc  bac0000000             -mov edx, 0xc0
    cpu.edx = 192 /*0xc0*/;
    // 004e52e1  89c6                   -mov esi, eax
    cpu.esi = cpu.eax;
    // 004e52e3  e824b4ffff             -call 0x4e070c
    cpu.esp -= 4;
    nfs3hp::fillZero(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e52e8  89be88000000           -mov dword ptr [esi + 0x88], edi
    app->getMemory<x86::reg32>(cpu.esi + x86::reg32(136) /* 0x88 */) = cpu.edi;
    // 004e52ee  898e84000000           -mov dword ptr [esi + 0x84], ecx
    app->getMemory<x86::reg32>(cpu.esi + x86::reg32(132) /* 0x84 */) = cpu.ecx;
    // 004e52f4  bb00100000             -mov ebx, 0x1000
    cpu.ebx = 4096 /*0x1000*/;
    // 004e52f9  89ca                   -mov edx, ecx
    cpu.edx = cpu.ecx;
    // 004e52fb  89f8                   -mov eax, edi
    cpu.eax = cpu.edi;
    // 004e52fd  e89ebe0100             -call 0x5011a0
    cpu.esp -= 4;
    nfs3hp::ea::touchMemoryPages(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e5302  bb00100000             -mov ebx, 0x1000
    cpu.ebx = 4096 /*0x1000*/;
    // 004e5307  bac0000000             -mov edx, 0xc0
    cpu.edx = 192 /*0xc0*/;
    // 004e530c  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004e530e  b9c0000000             -mov ecx, 0xc0
    cpu.ecx = 192 /*0xc0*/;
    // 004e5313  e888be0100             -call 0x5011a0
    cpu.esp -= 4;
    nfs3hp::ea::touchMemoryPages(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e5318  8b1c24                 -mov ebx, dword ptr [esp]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    // 004e531b  89ea                   -mov edx, ebp
    cpu.edx = cpu.ebp;
    // 004e531d  89f0                   -mov eax, esi
    cpu.eax = cpu.esi;
    // 004e531f  e81cfeffff             -call 0x4e5140
    cpu.esp -= 4;
    sub_4e5140(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e5324  83c404                 -add esp, 4
    (cpu.esp) += x86::reg32(x86::sreg32(4 /*0x4*/));
    // 004e5327  5d                     -pop ebp
    cpu.ebp = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e5328  5f                     -pop edi
    cpu.edi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e5329  5e                     -pop esi
    cpu.esi = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e532a  8d8000000000           -lea eax, [eax]
    cpu.eax = x86::reg32(cpu.eax);
    // 004e5330  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004e5331:
    // 004e5331  b8d0a35400             -mov eax, 0x54a3d0
    cpu.eax = 5546960 /*0x54a3d0*/;
    // 004e5336  ba48a75400             -mov edx, 0x54a748
    cpu.edx = 5547848 /*0x54a748*/;
    // 004e533b  bbcf040000             -mov ebx, 0x4cf
    cpu.ebx = 1231 /*0x4cf*/;
    // 004e5340  6804a55400             -push 0x54a504
    app->getMemory<x86::reg32>(cpu.esp-4) = 5547268 /*0x54a504*/;
    cpu.esp -= 4;
    // 004e5345  a390215500             -mov dword ptr [0x552190], eax
    app->getMemory<x86::reg32>(x86::reg32(5579152) /* 0x552190 */) = cpu.eax;
    // 004e534a  891594215500           -mov dword ptr [0x552194], edx
    app->getMemory<x86::reg32>(x86::reg32(5579156) /* 0x552194 */) = cpu.edx;
    // 004e5350  891d98215500           -mov dword ptr [0x552198], ebx
    app->getMemory<x86::reg32>(x86::reg32(5579160) /* 0x552198 */) = cpu.ebx;
    // 004e5356  e8b5bcf1ff             -call 0x401010
    cpu.esp -= 4;
    nfs3hp::Error(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e535b  83c404                 +add esp, 4
    {
        x86::reg32& tmp1 = cpu.esp;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(4 /*0x4*/));
        x86::reg32 result = tmp1 + tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) == (1 & (tmp2 >> 31));
        cpu.flags.cf = result < tmp1;
        tmp1 = result;
        cpu.set_szp(tmp1);
    }
    // 004e535e  e948ffffff             -jmp 0x4e52ab
    goto L_0x004e52ab;
}

/* sub_4e53c0: native, nfs3hp::snd::streamReaderThread */

/* sub_4e6660: native, nfs3hp::snd::passFreedChunks */

/* sub_4e66e0: native, nfs3hp::snd::roomAhead */

/* sub_4e6710: native, nfs3hp::snd::roomToEnd */

/* sub_4e6720: native, nfs3hp::snd::roomAtStart */

/* sub_4e6740: native, nfs3hp::snd::getStreamChunk */

/* sub_4e68a0: native, nfs3hp::snd::freeStreamChunk */

/* sub_4e68c0: native, nfs3hp::snd::streamBytesRead */

/* align: skip 0x8d 0x40 0x00 0x8b 0xc9 */
void Application::sub_4e68d0(WinApplication* app, x86::CPU& cpu)
{
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004e68d0  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004e68d2  7406                   -je 0x4e68da
    if (cpu.flags.zf)
    {
        goto L_0x004e68da;
    }
    // 004e68d4  8b80bc000000           -mov eax, dword ptr [eax + 0xbc]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(188) /* 0xbc */);
L_0x004e68da:
    // 004e68da  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_4e68e0: native, nfs3hp::snd::readerIdle */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x92 0x00 0x00 0x00 0x00 */
void Application::sub_4e6910(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004e6910  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004e6911  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004e6912  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004e6913  8b1db8455600           -mov ebx, dword ptr [0x5645b8]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(5653944) /* 0x5645b8 */);
    // 004e6919  8b83ac000000           -mov eax, dword ptr [ebx + 0xac]
    cpu.eax = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(172) /* 0xac */);
    // 004e691f  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004e6920  ff15b8445300           -call dword ptr [0x5344b8]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(5457080) /* 0x5344b8 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e6926  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
L_0x004e6928:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004e6928  8983b4000000           -mov dword ptr [ebx + 0xb4], eax
    app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(180) /* 0xb4 */) = cpu.eax;
    // 004e692e  8b5b70                 -mov ebx, dword ptr [ebx + 0x70]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(112) /* 0x70 */);
    // 004e6931  85db                   +test ebx, ebx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.ebx & cpu.ebx));
    // 004e6933  75f3                   -jne 0x4e6928
    if (!cpu.flags.zf)
    {
        goto L_0x004e6928;
    }
    // 004e6935  8b1db8455600           -mov ebx, dword ptr [0x5645b8]
    cpu.ebx = app->getMemory<x86::reg32>(x86::reg32(5653944) /* 0x5645b8 */);
    // 004e693b  8b9bac000000           -mov ebx, dword ptr [ebx + 0xac]
    cpu.ebx = app->getMemory<x86::reg32>(cpu.ebx + x86::reg32(172) /* 0xac */);
    // 004e6941  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004e6942  ff1588455300           -call dword ptr [0x534588]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(5457288) /* 0x534588 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e6948  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e6949  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e694a  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e694b  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_4e6950: native, nfs3hp::snd::readerWaits */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x52 0x00 */
void Application::sub_4e6960(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004e6960  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004e6961  89c1                   -mov ecx, eax
    cpu.ecx = cpu.eax;
    // 004e6963  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004e6965  31d2                   -xor edx, edx
    cpu.edx ^= x86::reg32(x86::sreg32(cpu.edx));
    // 004e6967  83f8ff                 +cmp eax, -1
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
    // 004e696a  7408                   -je 0x4e6974
    if (cpu.flags.zf)
    {
        goto L_0x004e6974;
    }
    // 004e696c  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004e696e  740d                   -je 0x4e697d
    if (cpu.flags.zf)
    {
        goto L_0x004e697d;
    }
L_0x004e6970:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004e6970  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004e6972  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e6973  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004e6974:
    // 004e6974  ba01000000             -mov edx, 1
    cpu.edx = 1 /*0x1*/;
    // 004e6979  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004e697b  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e697c  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004e697d:
    // 004e697d  e85effffff             -call 0x4e68e0
    cpu.esp -= 4;
    nfs3hp::snd::readerIdle(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e6982  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004e6984  74ea                   -je 0x4e6970
    if (cpu.flags.zf)
    {
        goto L_0x004e6970;
    }
    // 004e6986  89c8                   -mov eax, ecx
    cpu.eax = cpu.ecx;
    // 004e6988  e833ffffff             -call 0x4e68c0
    cpu.esp -= 4;
    nfs3hp::snd::streamBytesRead(app, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e698d  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004e698f  75df                   -jne 0x4e6970
    if (!cpu.flags.zf)
    {
        goto L_0x004e6970;
    }
    // 004e6991  ba01000000             -mov edx, 1
    cpu.edx = 1 /*0x1*/;
    // 004e6996  89d0                   -mov eax, edx
    cpu.eax = cpu.edx;
    // 004e6998  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e6999  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 */
void Application::sub_4e69a0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004e69a0  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004e69a1  8b15b8455600           -mov edx, dword ptr [0x5645b8]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5653944) /* 0x5645b8 */);
    // 004e69a7  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 004e69a9  7502                   -jne 0x4e69ad
    if (!cpu.flags.zf)
    {
        goto L_0x004e69ad;
    }
    // 004e69ab  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e69ac  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004e69ad:
    // 004e69ad  c7423001000000         -mov dword ptr [edx + 0x30], 1
    app->getMemory<x86::reg32>(cpu.edx + x86::reg32(48) /* 0x30 */) = 1 /*0x1*/;
    // 004e69b4  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e69b5  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 0x8d 0x54 0x22 0x00 */
void Application::sub_4e69c0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004e69c0  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004e69c1  8b15b8455600           -mov edx, dword ptr [0x5645b8]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5653944) /* 0x5645b8 */);
    // 004e69c7  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 004e69c9  7502                   -jne 0x4e69cd
    if (!cpu.flags.zf)
    {
        goto L_0x004e69cd;
    }
    // 004e69cb  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e69cc  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004e69cd:
    // 004e69cd  c7423000000000         -mov dword ptr [edx + 0x30], 0
    app->getMemory<x86::reg32>(cpu.edx + x86::reg32(48) /* 0x30 */) = 0 /*0x0*/;
    // 004e69d4  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e69d5  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_4e69e0: native, nfs3hp::snd::chainCommandBlocks */

/* sub_4e6a20: native, nfs3hp::snd::freeCommandBlock */

/* sub_4e6a70: native, nfs3hp::snd::commandBlocksFree */

/* align: skip 0x8d 0x80 0x00 0x00 0x00 0x00 */
void Application::sub_4e6ad0(WinApplication* __restrict app, x86::CPU& cpu_)
{
  x86::Local cpu(cpu_);
  NFS2_USE(cpu);
  NFS2_USE(app);
    // 004e6ad0  53                     -push ebx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ebx;
    cpu.esp -= 4;
    // 004e6ad1  52                     -push edx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.edx;
    cpu.esp -= 4;
    // 004e6ad2  8b15b8455600           -mov edx, dword ptr [0x5645b8]
    cpu.edx = app->getMemory<x86::reg32>(x86::reg32(5653944) /* 0x5645b8 */);
    // 004e6ad8  31db                   -xor ebx, ebx
    cpu.ebx ^= x86::reg32(x86::sreg32(cpu.ebx));
    // 004e6ada  85d2                   +test edx, edx
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.edx & cpu.edx));
    // 004e6adc  7505                   -jne 0x4e6ae3
    if (!cpu.flags.zf)
    {
        goto L_0x004e6ae3;
    }
    // 004e6ade  31c0                   -xor eax, eax
    cpu.eax ^= x86::reg32(x86::sreg32(cpu.eax));
    // 004e6ae0  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e6ae1  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e6ae2  c3                     -ret 
    cpu.esp += 4;
    return;
L_0x004e6ae3:
    // 004e6ae3  51                     -push ecx
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.ecx;
    cpu.esp -= 4;
    // 004e6ae4  8b82ac000000           -mov eax, dword ptr [edx + 0xac]
    cpu.eax = app->getMemory<x86::reg32>(cpu.edx + x86::reg32(172) /* 0xac */);
    // 004e6aea  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004e6aeb  ff15b8445300           -call dword ptr [0x5344b8]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(5457080) /* 0x5344b8 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e6af1  a1b8455600             -mov eax, dword ptr [0x5645b8]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5653944) /* 0x5645b8 */);
    // 004e6af6  8b4074                 -mov eax, dword ptr [eax + 0x74]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(116) /* 0x74 */);
    // 004e6af9  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004e6afb  7413                   -je 0x4e6b10
    if (cpu.flags.zf)
    {
        goto L_0x004e6b10;
    }
L_0x004e6afd:
    if (app->contextWanted()) app->yieldContext(cpu); /* safepoint */
    // 004e6afd  8b8098000000           -mov eax, dword ptr [eax + 0x98]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(152) /* 0x98 */);
    // 004e6b03  43                     -inc ebx
    (cpu.ebx)++;
    // 004e6b04  85c0                   +test eax, eax
    cpu.clear_co();
    cpu.set_szp(static_cast<x86::reg32>(cpu.eax & cpu.eax));
    // 004e6b06  75f5                   -jne 0x4e6afd
    if (!cpu.flags.zf)
    {
        goto L_0x004e6afd;
    }
    // 004e6b08  8d8000000000           -lea eax, [eax]
    cpu.eax = x86::reg32(cpu.eax);
    // 004e6b0e  8bd2                   -mov edx, edx
    cpu.edx = cpu.edx;
L_0x004e6b10:
    // 004e6b10  a1b8455600             -mov eax, dword ptr [0x5645b8]
    cpu.eax = app->getMemory<x86::reg32>(x86::reg32(5653944) /* 0x5645b8 */);
    // 004e6b15  8b80ac000000           -mov eax, dword ptr [eax + 0xac]
    cpu.eax = app->getMemory<x86::reg32>(cpu.eax + x86::reg32(172) /* 0xac */);
    // 004e6b1b  50                     -push eax
    app->getMemory<x86::reg32>(cpu.esp-4) = cpu.eax;
    cpu.esp -= 4;
    // 004e6b1c  ff1588455300           -call dword ptr [0x534588]
    cpu.ip = app->getMemory<x86::reg32>(x86::reg32(5457288) /* 0x534588 */);
    cpu.esp -= 4;
    app->dynamic_call(cpu.ip, cpu.sync());
    cpu.reload();
    if (cpu.terminate) return;
    // 004e6b22  89d8                   -mov eax, ebx
    cpu.eax = cpu.ebx;
    // 004e6b24  59                     -pop ecx
    cpu.ecx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e6b25  5a                     -pop edx
    cpu.edx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e6b26  5b                     -pop ebx
    cpu.ebx = app->getMemory<x86::reg32>(cpu.esp);
    cpu.esp += 4;
    // 004e6b27  c3                     -ret 
    cpu.esp += 4;
    return;
}

/* sub_4e6b30: native, nfs3hp::snd::takeCommandBlock */

/* sub_4e6be0: native, nfs3hp::snd::pathStep */

/* sub_4e6d68: native, nfs3hp::snd::pathTask */

/* sub_4e6d94: native, nfs3hp::snd::pathHook */

/* sub_4e6dc8: native, nfs3hp::snd::SNDpathinit */

/* sub_4e6f0c: native, nfs3hp::snd::SNDpathstartstream */

/* sub_4e705c: native, nfs3hp::snd::SNDpathcontrol */

/* sub_4e70fc: native, nfs3hp::snd::SNDpathevent */

/* sub_4e7208: native, nfs3hp::snd::SNDpatheventinterrupt */

/* sub_4e7388: native, nfs3hp::snd::SNDpathrestore */

/* sub_4e73d0: native, nfs3hp::snd::SNDmastervol */

/* sub_4e7470: native, nfs3hp::snd::SNDstreamautovol */

/* sub_4e74f0: native, nfs3hp::snd::SNDstreamgetvol */

/* sub_4e7520: native, nfs3hp::snd::addSystemTask */

/* sub_4e75e0: native, nfs3hp::snd::removeSystemTask */

/* sub_4e7630: native, nfs3hp::snd::runSystemTasks */

/* sub_4e7720: native, nfs3hp::snd::waitSystemTasks */

/* sub_4e7750: native, nfs3hp::snd::SNDstreamsetup */

/* sub_4e784c: native, nfs3hp::snd::SNDstreamrestore */

/* sub_4e78a0: native, nfs3hp::snd::SNDstreamqueue */

/* sub_4e7a14: native, nfs3hp::snd::SNDstreaminterrupt */

/* sub_4e7b28: native, nfs3hp::snd::SNDstreampurge */

/* sub_4e7c58: native, nfs3hp::snd::SNDstreamchunksleft */

/* sub_4e7ce0: native, nfs3hp::snd::SNDstreambuftime */

/* sub_4e7dd0: native, nfs3hp::snd::streamToppedUp */

/* sub_4e7df4: native, nfs3hp::snd::iSNDstreamchecktopup */

/* sub_4e7e98: native, nfs3hp::snd::iSNDstreamsetbuftime */

/* sub_4e7f30: native, nfs3hp::snd::parseStreamChunk */

/* sub_4e7ff8: native, nfs3hp::snd::dropQueuedChunks */

/* sub_4e8078: native, nfs3hp::snd::queueDataChunk */

/* sub_4e80cc: native, nfs3hp::snd::iSNDparseheader */

/* sub_4e8258: native, nfs3hp::snd::queueLoopChunk */

/* sub_4e82c4: native, nfs3hp::snd::streamSeekChunk */

/* sub_4e82ec: native, nfs3hp::snd::streamEndChunk */

/* sub_4e8320: native, nfs3hp::snd::streamEndsSeen */

/* sub_4e8328: native, nfs3hp::snd::nextStreamChunk */

/* sub_4e85a8: native, nfs3hp::snd::iSNDstreamservice */

/* sub_4e8944: native, nfs3hp::snd::resetStreamer */

/* sub_4e89f8: native, nfs3hp::snd::iSNDstreamstart */

/* sub_4e8b60: native, nfs3hp::snd::SNDstreamvol */

/* sub_4e8bd0: native, nfs3hp::snd::removeBankPatches */

/* sub_4e8c1c: native, nfs3hp::snd::removeAllBanks */

/* sub_4e8c28: native, nfs3hp::snd::SNDbankremove */

/* sub_4e8d20: native, nfs3hp::snd::SNDbankadd */

/* sub_4e8db0: native, nfs3hp::snd::SNDbankheadersize */

/* sub_4e8e20: native, nfs3hp::snd::SNDbankheadercopy */

/* sub_4e8f28: native, nfs3hp::port::SNDangle */

/* sub_4e8fd0: native, nfs3hp::snd::SNDstatus */

/* sub_4e9010: native, nfs3hp::snd::SNDstopall */

/* sub_4e9030: native, nfs3hp::watcom::update_buffer */

/* sub_4e9070: native, nfs3hp::watcom::reset_buffer */

/* sub_4e9088: native, nfs3hp::watcom::fseek */

/* sub_4e9200: native, nfs3hp::watcom::fread */

/* sub_4e9420: native, nfs3hp::snd::SNDautovol */

/* sub_4e9540: native, nfs3hp::snd::setSoundVolume */

/* sub_4e95fc: native, nfs3hp::snd::SNDvol */

/* sub_4e9670: native, nfs3hp::snd::SNDstop */

/* sub_4e9710: native, nfs3hp::snd::setSoundBend */

/* sub_4e97e4: native, nfs3hp::snd::SNDpitchbend */

/* sub_4e9850: native, nfs3hp::snd::SNDpos3d */

/* sub_4e9950: native, nfs3hp::snd::SNDpan */

}
