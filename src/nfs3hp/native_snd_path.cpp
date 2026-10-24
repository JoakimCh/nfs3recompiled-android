#include "native_snd.h"

/* EA's Pathfinder (cmn\spathold.c), native (native_snd.h says how): music
 * as a map of nodes, each a stretch of the stream's file, that the game steers
 * by events and a controller's value.  The map: 'PFDx', its version (0), the
 * node to start at (+5), its nodes' count (+6), the events' count (+7), the
 * rows' count (+0xb), then the nodes of 0x1c bytes -- their row (+0), their
 * branches' count (+1), the branches of 3 bytes from +4: the controller's
 * range (signed bytes) and the node it leads to -- then the rows of node
 * numbers by event, then each node's offset in the file, big-endian.
 *
 * Its state at 0x5645c0..0x56480c: 0x5645c0 the buffered time it asks for,
 * 0x5645c2 the time it waits for, 0x5645c4 the node playing, 0x5645c6 the
 * controller, 0x5645c8 the streamer's ends to wait for, 0x5645cc the rows,
 * 0x5645d0 the offsets, 0x5645d4 the file's name; 0x564654/0x564656 the event
 * and its kind, 0x564658/0x56465a the event after it, 0x56465c the map,
 * 0x564660 its nodes, 0x564664 the CD stream. */
namespace nfs3hp
{
namespace snd
{

namespace
{

constexpr reg32 kBufTime = 0x5645c0, kWaitTime = 0x5645c2, kNode = 0x5645c4, kController = 0x5645c6;
constexpr reg32 kEnds = 0x5645c8, kRows = 0x5645cc, kOffsets = 0x5645d0, kName = 0x5645d4;
constexpr reg32 kEvent = 0x564654, kEventKind = 0x564656, kNextEvent = 0x564658, kNextKind = 0x56465a;
constexpr reg32 kMap = 0x56465c, kNodes = 0x564660, kPathStream = 0x564664;
constexpr reg32 kPathRestore = 0xa09b2c;
constexpr reg32 kTopupHook = 0x56480c;
constexpr reg32 kPathFile = 0x54a8b8;
constexpr reg32 kPathTask = 0x4e6d68, kPathHook = 0x4e6d94, kPathRestoreFunction = 0x4e7388;

/* The node playing's offset in the file. */
reg32 nodeOffset(App* app, reg32 node)
{
    const reg32 v = at(app, at(app, kOffsets) + 4 * node);
    return v >> 24 | (v >> 8 & 0xff00) | (v << 8 & 0xff0000) | v << 24;
}

reg32 playing(App* app) { return reg32(shalf(app, kNode)); }

/* The node event `event` leads to from the node playing. */
reg32 nodeAfter(App* app, reg32 event)
{
    const reg32 row = byte(app, at(app, kNodes) + playing(app) * 0x1c);
    return byte(app, at(app, kRows) + reg32(mul(i32(byte(app, at(app, kMap) + 7)), i32(row))) + event);
}

/* No event, none after it. */
void clearEvents(App* app)
{
    putHalf(app, kEvent, 0xffff);
    putHalf(app, kEventKind, 0);
    putHalf(app, kNextEvent, 0xffff);
    putHalf(app, kNextKind, 0);
}

}  // namespace

/* 0x4e6be0: on to the next node -- the event's, or the branch the controller
 * falls in -- and its stretch queued; the task gone once a node without
 * branches plays with no event.  eax the node's offset among the nodes (or
 * removeSystemTask's). */
void pathStep(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(3);
    if (shalf(app, kEvent) >= 0)
    {
        putHalf(app, kNode, reg16(nodeAfter(app, reg32(shalf(app, kEvent)))));
        put(app, kEvent, at(app, kNextEvent));
        putHalf(app, kNextEvent, 0xffff);
        putHalf(app, kNextKind, 0);
    }
    else
    {
        const reg32 node = at(app, kNodes) + playing(app) * 0x1c;
        const i32 controller = sbyte(app, kController);
        for (reg32 i = 0; i < byte(app, node + 1); ++i)
        {
            const reg32 branch = node + 3 * i;
            if (controller >= sbyte(app, branch + 4) && controller <= sbyte(app, branch + 5))
            {
                putHalf(app, kNode, byte(app, branch + 6));
                break;
            }
        }
    }
    put(app, kEnds, at(app, kEnds) + 1);
    if (!callWith(app, cpu, 0x4e78a0, kName, nodeOffset(app, playing(app))))
        return;
    reg32 result = playing(app) * 0x1c;
    if (byte(app, at(app, kNodes) + result + 1) == 0 && shalf(app, kEvent) < 0)
    {
        cpu.ecx = 0;
        if (!callWith(app, cpu, 0x4e75e0, kPathTask))
            return;
        result = cpu.eax;
        put(app, kTopupHook, 0);
    }
    kept.ret(cpu, result);
}

/* 0x4e6d68: Pathfinder's system task: once the streamer has seen the ends
 * waited for and holds less than the time wanted, the next node.  0. */
void pathTask(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    reg32 ends;
    if (!call(app, cpu, 0x4e8320))
        return;
    ends = cpu.eax;
    if (i32(ends) < s32(app, kEnds))
    {
        kept.ret(cpu, 0);
        return;
    }
    const reg32 wanted = half(app, kWaitTime);
    cpu.edx = wanted;
    if (!call(app, cpu, 0x4e7ce0))
        return;
    if (i32(cpu.eax) < i32(wanted) && !call(app, cpu, 0x4e6be0))
        return;
    kept.ret(cpu, 0);
    cpu.edx = wanted;
}

/* 0x4e6d94: Pathfinder's top-up hook: the time to wait for, the time asked
 * for plus eax.  The time asked for. */
void pathHook(App* app, CPU& cpu)
{
    putHalf(app, kWaitTime, reg16(cpu.eax == 0 ? half(app, kBufTime) : cpu.eax + half(app, kBufTime)));
    cpu.eax = half(app, kBufTime);
    cpu.esp += 4;
}

/* 0x4e6dc8 (SNDpathinit): Pathfinder set up on map eax.  0; -14 before
 * SNDinit, -1 when set up already, -7 for no map, -11 for its version. */
void SNDpathinit(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 map = cpu.eax;
    cpu.esp = kept.frame(5);
    if (byte(app, kInited) == 0)
    {
        kept.ret(cpu, 0xfffffff2);
        return;
    }
    if (at(app, kMap) != 0)
    {
        if (!fail(app, cpu, kept.frame(5), kPathFile, 0x54a8c8, 0xed, {0x54a8d4}))
            return;
        kept.ret(cpu, 0xffffffff);
        return;
    }
    put(app, kMap, map);
    if (at(app, map) != 0x78444650)
    {
        if (!fail(app, cpu, kept.frame(6), kPathFile, 0x54a8c8, 0xf9, {0x54a91c}))
            return;
        kept.ret(cpu, 0xfffffff9);
        return;
    }
    if (byte(app, map + 4) != 0)
    {
        if (!fail(app, cpu, kept.frame(5), kPathFile, 0x54a8c8, 0x103, {0x54a950}))
            return;
        kept.ret(cpu, 0xfffffff5);
        return;
    }
    put(app, kNodes, map + 0xc);
    const reg32 rows = map + 0xc + byte(app, map + 6) * 0x1c;
    put(app, kRows, rows);
    put(app, kPathRestore, kPathRestoreFunction);
    put(app, kOffsets, rows + byte(app, map + 0xb) * byte(app, map + 7));
    kept.ret(cpu, 0);
}

/* 0x4e6f0c (SNDpathstartstream): the music started on CD stream eax from
 * file edx, its first node's stretch queued, time ebx buffered ahead;
 * Pathfinder's task and hook set.  0, -14 before SNDinit or SNDpathinit.
 * ebx and edx left as the calls leave them. */
void SNDpathstartstream(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 stream = cpu.eax, name = cpu.edx, time = cpu.ebx;
    const reg32 f = kept.frame(3, 0x10);
    cpu.esp = f;
    if (byte(app, kInited) == 0)
    {
        kept.ret(cpu, 0xfffffff2);
        return;
    }
    if (at(app, kPathRestore) == 0)
    {
        if (!fail(app, cpu, f, kPathFile, 0x54a98c, 0x1a5, {0x54a9a0}))
            return;
        kept.ret(cpu, 0xfffffff2);
        return;
    }
    put(app, kPathStream, stream);
    putHalf(app, kBufTime, reg16(time));
    putHalf(app, kWaitTime, reg16(time));
    putHalf(app, kEvent, 0xffff);
    putHalf(app, kEventKind, 0);
    putHalf(app, kNextEvent, 0xffff);
    putHalf(app, kNextKind, 0);
    cpu.esp = f - 4;
    putByte(app, kController, 0);
    putHalf(app, kNode, byte(app, at(app, kMap) + 5));
    if (!call(app, cpu, 0x4e8320))
        return;
    put(app, kEnds, cpu.eax);
    for (reg32 i = 0;; ++i)
    {
        const reg8 c = byte(app, name + i);
        putByte(app, kName + i, c);
        if (c == 0)
            break;
    }
    put(app, kEnds, at(app, kEnds) + 1);
    if (!callWith(app, cpu, 0x4e9b20, f) || !callWith(app, cpu, 0x4e7750, at(app, kPathStream), f))
        return;
    cpu.ebx = 1;
    if (!callWith(app, cpu, 0x4e78a0, name, nodeOffset(app, playing(app))))
        return;
    cpu.ebp = kPathHook;
    if (!callWith(app, cpu, 0x4e7520, kPathTask, 0))
        return;
    put(app, kTopupHook, kPathHook);
    const reg32 ebx = cpu.ebx, edx = cpu.edx;
    kept.ret(cpu, 0);
    cpu.ebx = ebx;
    cpu.edx = edx;
}

/* 0x4e705c (SNDpathcontrol): the controller to eax (0..127).  0; -14 before
 * SNDinit or SNDpathinit, -8 out of range. */
void SNDpathcontrol(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 value = cpu.eax;
    cpu.esp = kept.frame(2);
    if (byte(app, kInited) == 0)
    {
        kept.ret(cpu, 0xfffffff2);
        return;
    }
    if (at(app, kPathRestore) == 0)
    {
        if (!fail(app, cpu, kept.frame(2), kPathFile, 0x54a9d4, 0x23a, {0x54a9e4}))
            return;
        kept.ret(cpu, 0xfffffff2);
        return;
    }
    if (i32(value) < 0 || i32(value) > 0x7f)
    {
        if (!fail(app, cpu, kept.frame(5), kPathFile, 0x54a9d4, 0x243, {0x54aa14}))
            return;
        kept.ret(cpu, 0xfffffff8);
        return;
    }
    putByte(app, kController, reg8(value));
    kept.ret(cpu, 0);
}

/* 0x4e70fc (SNDpathevent): event eax of kind edx: kind 1 at once (the one
 * after it dropped), another after an event of kind 1, else in its place.
 * 0; -14 before SNDinit or SNDpathinit (edx left 0x2d0 by the error's line),
 * -8 for no such event. */
void SNDpathevent(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 event = cpu.eax, kind = cpu.edx;
    cpu.esp = kept.frame(3);
    if (byte(app, kInited) == 0)
    {
        kept.ret(cpu, 0xfffffff2);
        return;
    }
    if (at(app, kPathRestore) == 0)
    {
        if (!fail(app, cpu, kept.frame(3), kPathFile, 0x54aa48, 0x2d0, {0x54aa58}))
            return;
        kept.ret(cpu, 0xfffffff2);
        cpu.edx = 0x2d0;
        return;
    }
    if (i32(event) < 0 || i32(event) >= i32(byte(app, at(app, kMap) + 7)))
    {
        if (!fail(app, cpu, kept.frame(5), kPathFile, 0x54aa48, 0x2d9, {0x54aa84}))
            return;
        kept.ret(cpu, 0xfffffff8);
        return;
    }
    if (kind == 1)
    {
        putHalf(app, kEvent, reg16(event));
        putHalf(app, kEventKind, reg16(kind));
        putHalf(app, kNextEvent, 0xffff);
        putHalf(app, kNextKind, 0);
    }
    else if (half(app, kEventKind) == 1)
    {
        putHalf(app, kNextEvent, reg16(event));
        putHalf(app, kNextKind, reg16(kind));
    }
    else
    {
        putHalf(app, kEvent, reg16(event));
        putHalf(app, kEventKind, reg16(kind));
    }
    kept.ret(cpu, 0);
}

/* 0x4e7208 (SNDpatheventinterrupt): the stream cut over at once to the node
 * event eax leads to.  0; -14 before SNDinit or SNDpathinit, -8 for no such
 * event, -18 when the streamer would not. */
void SNDpatheventinterrupt(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 event = cpu.eax;
    cpu.esp = kept.frame(4);
    if (byte(app, kInited) == 0)
    {
        kept.ret(cpu, 0xfffffff2);
        return;
    }
    if (at(app, kPathRestore) == 0)
    {
        if (!fail(app, cpu, kept.frame(4), kPathFile, 0x54aaa8, 0x303, {0x54aac0}))
            return;
        kept.ret(cpu, 0xfffffff2);
        return;
    }
    if (i32(event) < 0 || i32(event) >= i32(byte(app, at(app, kMap) + 7)))
    {
        if (!fail(app, cpu, kept.frame(6), kPathFile, 0x54aaa8, 0x30c, {0x54aaf8}))
            return;
        kept.ret(cpu, 0xfffffff8);
        return;
    }
    if (!call(app, cpu, 0x500e20))
        return;
    const reg32 node = nodeAfter(app, event);
    cpu.ebx = node;
    if (!callWith(app, cpu, 0x4e7a14, kName, nodeOffset(app, node)))
        return;
    if (cpu.eax != 0)
    {
        if (!call(app, cpu, 0x500e7c))
            return;
        kept.ret(cpu, 0xffffffee);
        return;
    }
    if (!call(app, cpu, 0x4e8320))
        return;
    put(app, kEnds, cpu.eax);
    putHalf(app, kNode, reg16(node));
    clearEvents(app);
    if (!call(app, cpu, 0x500e7c))
        return;
    kept.ret(cpu, 0);
}

/* 0x4e7388 (SNDpathrestore): Pathfinder done with: the streamer restored,
 * its task and hook gone.  0, -14 when not set up. */
void SNDpathrestore(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    if (byte(app, kInited) == 0 || at(app, kPathRestore) == 0)
    {
        kept.ret(cpu, 0xfffffff2);
        return;
    }
    cpu.esp = kept.frame(1);
    if (!call(app, cpu, 0x4e784c))
        return;
    cpu.ecx = 0;
    if (!callWith(app, cpu, 0x4e75e0, kPathTask))
        return;
    put(app, kMap, 0);
    put(app, kTopupHook, 0);
    put(app, kPathRestore, 0);
    kept.ret(cpu, 0);
}

}  // namespace snd
}  // namespace nfs3hp
