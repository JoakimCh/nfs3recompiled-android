#include "port_snd.h"

#include <cstdint>

/* EA's Pathfinder (cmn\spathold.c), rewritten (port_snd.h says how): music as
 * a map of nodes, each a stretch of the stream's file, that the game steers by
 * events and a controller's value.  The map: 'PFDx', its version (0), the node
 * to start at, its nodes' count, the events' count, the rows' count, then the
 * nodes -- their row, their branches' count, the branches: the controller's
 * range (signed bytes) and the node it leads to -- then the rows of node
 * numbers by event, then each node's offset in the file, big-endian.
 *
 * Pathfinder's state lies where the game has it (0x5645c0..0x56480c); the
 * stream it queues the stretches on is the CD stream's (native_snd_cdstream.cpp,
 * called by address), and its system task and top-up hook are the game's code's
 * for the stream to call.  Each function is here as C++ and as the adapter
 * around it the game's code calls; the adapters give back what the game's
 * callers read of the registers besides eax: SNDpathstartstream's ebx and edx
 * (the music's start passes them up), SNDpathevent's edx past an error. */
namespace nfs3hp
{
namespace port
{

namespace
{

#pragma pack(push, 1)

struct Branch
{
    int8_t low, high;         // the controller's range
    uint8_t node;             // the node it leads to
};

struct Node
{
    uint8_t row;              // its row of the events' table
    uint8_t branches;         // how many
    uint8_t other2[2];
    // The branches, 3 bytes each, from +4.
};
static_assert(sizeof(Node) == 4, "a node's head");

/* An event and its kind. */
struct Event
{
    int16_t event;            // -1 none
    uint16_t kind;
};

#pragma pack(pop)

constexpr reg32 kNodeSize = 0x1c;
constexpr Event kNoEvent{-1, 0};

constexpr Var<uint16_t> kBufTime{0x5645c0};        // the buffered time it asks for
constexpr Var<uint16_t> kWaitTime{0x5645c2};       // and the time it waits for
constexpr Var<int16_t> kNode{0x5645c4};            // the node playing
constexpr Var<int8_t> kController{0x5645c6};
constexpr Var<int32_t> kEnds{0x5645c8};            // the streamer's ends to wait for
constexpr Var<reg32> kRows{0x5645cc}, kOffsets{0x5645d0};
constexpr reg32 kNameAt = 0x5645d4;                // the file's name
constexpr Var<Event> kCurrent{0x564654}, kNext{0x564658};
constexpr Var<reg32> kMap{0x56465c}, kNodes{0x564660}, kPathStream{0x564664};
constexpr Var<reg32> kPathRestore{0xa09b2c};
constexpr Var<reg32> kTopupHook{0x56480c};

// Its errors' source, and the functions' names.
constexpr reg32 kPathFile = 0x54a8b8;
constexpr Where kInitError{kPathFile, 0x54a8c8}, kStartError{kPathFile, 0x54a98c};
constexpr Where kControlError{kPathFile, 0x54a9d4}, kEventError{kPathFile, 0x54aa48};
constexpr Where kInterruptError{kPathFile, 0x54aaa8};

// Its own functions the game's code calls, and what it calls of the stream's.
constexpr reg32 kPathTask = 0x4e6d68, kPathHook = 0x4e6d94, kPathRestoreFunction = 0x4e7388;
constexpr reg32 kStreamEnds = 0x4e8320, kBuffered = 0x4e7ce0, kQueueFile = 0x4e78a0, kInterruptFile = 0x4e7a14;
constexpr reg32 kStreamSetup = 0x4e7750, kStreamRestore = 0x4e784c;
constexpr reg32 kAddSystemTask = 0x4e7520, kRemoveSystemTask = 0x4e75e0;

// Its answers: before SNDinit or SNDpathinit; set up already; the map's magic
// and version; the streamer would not.
constexpr int32_t kNoPathfinder = -14, kSetUp = -1, kNoMap = -7, kBadVersion = -11, kStreamerRefused = -18;
constexpr reg32 kMagic = 0x78444650;  // 'PFDx'

/* A call with eax and edx, the other registers as they are. */
bool callWith(App* app, CPU& cpu, reg32 esp, reg32 target, reg32 eax, reg32 edx, reg32& result)
{
    return callGame(app, cpu, esp, target, {eax, edx, cpu.ebx, cpu.ecx}, {}, result);
}

bool callWith(App* app, CPU& cpu, reg32 esp, reg32 target, reg32 eax, reg32 edx)
{
    reg32 ignored;
    return callWith(app, cpu, esp, target, eax, edx, ignored);
}

uint8_t byteAt(App* app, reg32 at) { return app->getMemory<uint8_t>(at); }

/* The node `node`'s offset in the file (big-endian in the map). */
reg32 nodeOffset(App* app, reg32 node)
{
    const reg32 v = app->getMemory<reg32>(kOffsets(app) + 4 * node);
    return v >> 24 | (v >> 8 & 0xff00) | (v << 8 & 0xff0000) | v << 24;
}

reg32 nodeAt(App* app, reg32 node) { return kNodes(app) + node * kNodeSize; }

/* The node playing. */
reg32 playing(App* app) { return reg32(int32_t(kNode(app))); }

/* The node event `event` leads to from the node playing. */
reg32 nodeAfter(App* app, reg32 event)
{
    const reg32 row = record<Node>(app, nodeAt(app, playing(app))).row;
    return byteAt(app, kRows(app) + reg32(imul(int32_t(byteAt(app, kMap(app) + 7)), int32_t(row))) + event);
}

/* No event, none after it. */
void clearEvents(App* app)
{
    kCurrent.set(app, kNoEvent);
    kNext.set(app, kNoEvent);
}

/* 0x4e6be0's: on to the next node -- the event's, or the branch the controller
 * falls in -- and its stretch queued; the task gone once a node without
 * branches plays with no event.  The node's offset among the nodes (or
 * removeSystemTask's). */
Result stepOn(App* app, CPU& cpu, reg32 esp)
{
    const reg32 f = esp - 3 * 4;
    if (kCurrent(app).event >= 0)
    {
        kNode.set(app, int16_t(nodeAfter(app, reg32(int32_t(kCurrent(app).event)))));
        kCurrent.set(app, kNext(app));
        kNext.set(app, kNoEvent);
    }
    else
    {
        const reg32 node = nodeAt(app, playing(app));
        const int32_t controller = kController(app);
        for (reg32 i = 0; i < record<Node>(app, node).branches; ++i)
        {
            const Branch& branch = record<Branch>(app, node + sizeof(Node) + sizeof(Branch) * i);
            if (controller >= branch.low && controller <= branch.high)
            {
                kNode.set(app, int16_t(branch.node));
                break;
            }
        }
    }
    kEnds.set(app, kEnds(app) + 1);
    if (!callWith(app, cpu, f, kQueueFile, kNameAt, nodeOffset(app, playing(app))))
        return {};
    reg32 result = playing(app) * kNodeSize;
    if (record<Node>(app, kNodes(app) + result).branches == 0 && kCurrent(app).event < 0)
    {
        if (!callGame(app, cpu, f, kRemoveSystemTask, {kPathTask, cpu.edx, cpu.ebx, 0}, {}, result))
            return {};
        kTopupHook.set(app, 0);
    }
    return int32_t(result);
}

/* 0x4e6d68's: Pathfinder's system task: once the streamer has seen the ends
 * waited for and holds less than the time wanted, the next node.  0. */
Result runPathTask(App* app, CPU& cpu, reg32 esp)
{
    reg32 ends;
    if (!callGame(app, cpu, esp, kStreamEnds, {}, {}, ends))
        return {};
    if (int32_t(ends) < kEnds(app))
        return 0;
    const reg32 wanted = kWaitTime(app);
    reg32 buffered;
    if (!callWith(app, cpu, esp, kBuffered, ends, wanted, buffered))
        return {};
    if (int32_t(buffered) < int32_t(wanted) && !stepOn(app, cpu, esp - 4))
        return {};
    return 0;
}

/* 0x4e6d94's: Pathfinder's top-up hook: the time to wait for is the time
 * asked for plus `extra` (that alone for none).  The time asked for. */
reg32 topUpHook(App* app, reg32 extra)
{
    kWaitTime.set(app, uint16_t(extra == 0 ? kBufTime(app) : extra + kBufTime(app)));
    return kBufTime(app);
}

/* 0x4e6dc8's (SNDpathinit): Pathfinder set up on map `map`.  0; -14 before
 * SNDinit, -1 when set up already, -7 for no map, -11 for its version. */
Result pathInit(App* app, CPU& cpu, reg32 esp, reg32 map)
{
    if (kInited(app) == 0)
        return kNoPathfinder;
    if (kMap(app) != 0)
    {
        if (!fail(app, cpu, esp - 5 * 4, kInitError, 0xed, {0x54a8d4}))
            return {};
        return kSetUp;
    }
    kMap.set(app, map);
    if (app->getMemory<reg32>(map) != kMagic)
    {
        if (!fail(app, cpu, esp - 6 * 4, kInitError, 0xf9, {0x54a91c}))
            return {};
        return kNoMap;
    }
    if (byteAt(app, map + 4) != 0)
    {
        if (!fail(app, cpu, esp - 5 * 4, kInitError, 0x103, {0x54a950}))
            return {};
        return kBadVersion;
    }
    kNodes.set(app, map + 0xc);
    const reg32 rows = map + 0xc + byteAt(app, map + 6) * kNodeSize;
    kRows.set(app, rows);
    kPathRestore.set(app, kPathRestoreFunction);
    kOffsets.set(app, rows + byteAt(app, map + 0xb) * byteAt(app, map + 7));
    return 0;
}

/* 0x4e6f0c's (SNDpathstartstream): the music started on CD stream `stream`
 * from the file named `name`, its first node's stretch queued, `time` buffered
 * ahead; Pathfinder's task and hook set.  0, -14 before SNDinit or
 * SNDpathinit. */
Result startPathStream(App* app, CPU& cpu, reg32 esp, reg32 stream, reg32 name, reg32 time)
{
    const reg32 f = esp - 3 * 4 - 0x10;
    if (kInited(app) == 0)
        return kNoPathfinder;
    if (kPathRestore(app) == 0)
    {
        if (!fail(app, cpu, f, kStartError, 0x1a5, {0x54a9a0}))
            return {};
        return kNoPathfinder;
    }
    kPathStream.set(app, stream);
    kBufTime.set(app, uint16_t(time));
    kWaitTime.set(app, uint16_t(time));
    clearEvents(app);
    kController.set(app, 0);
    kNode.set(app, int16_t(byteAt(app, kMap(app) + 5)));
    reg32 ends;
    if (!callGame(app, cpu, f - 4, kStreamEnds, {}, {}, ends))
        return {};
    kEnds.set(app, int32_t(ends));
    for (reg32 i = 0;; ++i)
    {
        const uint8_t c = byteAt(app, name + i);
        app->getMemory<uint8_t>(kNameAt + i) = c;
        if (c == 0)
            break;
    }
    kEnds.set(app, kEnds(app) + 1);
    // The play's options made on the stack, for the stream's setup.
    playDefaults(record<PlayOptions>(app, f));
    if (!callWith(app, cpu, f - 4, kStreamSetup, kPathStream(app), f)
        || !callGame(app, cpu, f - 4, kQueueFile, {name, nodeOffset(app, playing(app)), 1, cpu.ecx})
        || !callGame(app, cpu, f - 4, kAddSystemTask, {kPathTask, 0, 1, cpu.ecx}))
        return {};
    kTopupHook.set(app, kPathHook);
    return 0;
}

/* 0x4e705c's (SNDpathcontrol): the controller to `value` (0 to 127).  0; -14
 * before SNDinit or SNDpathinit, -8 out of range. */
Result pathControl(App* app, CPU& cpu, reg32 esp, int32_t value)
{
    if (kInited(app) == 0)
        return kNoPathfinder;
    if (kPathRestore(app) == 0)
    {
        if (!fail(app, cpu, esp - 2 * 4, kControlError, 0x23a, {0x54a9e4}))
            return {};
        return kNoPathfinder;
    }
    if (value < 0 || value > 0x7f)
    {
        if (!fail(app, cpu, esp - 5 * 4, kControlError, 0x243, {0x54aa14}))
            return {};
        return kNoSound;
    }
    kController.set(app, int8_t(value));
    return 0;
}

/* 0x4e70fc's (SNDpathevent): event `event` of kind `kind`: kind 1 at once
 * (the one after it dropped), another after an event of kind 1, else in its
 * place.  0; -14 before SNDinit or SNDpathinit, -8 for no such event. */
Result pathEvent(App* app, CPU& cpu, reg32 esp, int32_t event, int32_t kind)
{
    if (kInited(app) == 0)
        return kNoPathfinder;
    if (kPathRestore(app) == 0)
    {
        if (!fail(app, cpu, esp - 3 * 4, kEventError, 0x2d0, {0x54aa58}))
            return {};
        return kNoPathfinder;
    }
    if (event < 0 || event >= int32_t(byteAt(app, kMap(app) + 7)))
    {
        if (!fail(app, cpu, esp - 5 * 4, kEventError, 0x2d9, {0x54aa84}))
            return {};
        return kNoSound;
    }
    const Event asked{int16_t(event), uint16_t(kind)};
    if (kind == 1)
    {
        kCurrent.set(app, asked);
        kNext.set(app, kNoEvent);
    }
    else if (kCurrent(app).kind == 1)
        kNext.set(app, asked);
    else
        kCurrent.set(app, asked);
    return 0;
}

/* 0x4e7208's (SNDpatheventinterrupt): the stream cut over at once to the
 * node event `event` leads to.  0; -14 before SNDinit or SNDpathinit, -8 for
 * no such event, -18 when the streamer would not. */
Result pathEventInterrupt(App* app, CPU& cpu, reg32 esp, int32_t event)
{
    const reg32 f = esp - 4 * 4;
    if (kInited(app) == 0)
        return kNoPathfinder;
    if (kPathRestore(app) == 0)
    {
        if (!fail(app, cpu, f, kInterruptError, 0x303, {0x54aac0}))
            return {};
        return kNoPathfinder;
    }
    if (event < 0 || event >= int32_t(byteAt(app, kMap(app) + 7)))
    {
        if (!fail(app, cpu, esp - 6 * 4, kInterruptError, 0x30c, {0x54aaf8}))
            return {};
        return kNoSound;
    }
    if (!enterAudio(app, cpu, f - 4))
        return {};
    const reg32 node = nodeAfter(app, reg32(event));
    reg32 refused;
    if (!callGame(app, cpu, f, kInterruptFile, {kNameAt, nodeOffset(app, node), node, cpu.ecx}, {}, refused))
        return {};
    if (refused != 0)
    {
        if (!leaveAudio(app, cpu, f - 4))
            return {};
        return kStreamerRefused;
    }
    reg32 ends;
    if (!callGame(app, cpu, f, kStreamEnds, {}, {}, ends))
        return {};
    kEnds.set(app, int32_t(ends));
    kNode.set(app, int16_t(node));
    clearEvents(app);
    if (!leaveAudio(app, cpu, f - 4))
        return {};
    return 0;
}

/* 0x4e7388's (SNDpathrestore): Pathfinder done with: the streamer restored,
 * its task and hook gone.  0, -14 when not set up. */
Result pathRestore(App* app, CPU& cpu, reg32 esp)
{
    if (kInited(app) == 0 || kPathRestore(app) == 0)
        return kNoPathfinder;
    const reg32 f = esp - 4;
    if (!callGame(app, cpu, f, kStreamRestore))
        return {};
    if (!callGame(app, cpu, f, kRemoveSystemTask, {kPathTask, cpu.edx, cpu.ebx, 0}))
        return {};
    kMap.set(app, 0);
    kTopupHook.set(app, 0);
    kPathRestore.set(app, 0);
    return 0;
}

}  // namespace

/* The game's entries: each its adapter -- the game's registers and stack in,
 * the result in eax out -- around what it does. */

void pathStep(App* app, CPU& cpu)
{
    const Entry e(cpu);
    e.finish(cpu, stepOn(app, cpu, e.esp));
}

void pathTask(App* app, CPU& cpu)
{
    const Entry e(cpu);
    e.finish(cpu, runPathTask(app, cpu, e.esp));
}

void pathHook(App* app, CPU& cpu)
{
    const Entry e(cpu);
    e.back(cpu, topUpHook(app, e.eax));
}

void SNDpathinit(App* app, CPU& cpu)
{
    const Entry e(cpu);
    e.finish(cpu, pathInit(app, cpu, e.esp, e.eax));
}

/* The stream eax from the file edx, time ebx buffered ahead.  ebx and edx are
 * left as the calls leave them once it is done: 1, and the system task's. */
void SNDpathstartstream(App* app, CPU& cpu)
{
    const Entry e(cpu);
    const Result r = startPathStream(app, cpu, e.esp, e.eax, e.edx, e.ebx);
    if (!r)
        return;
    const reg32 ebx = cpu.ebx, edx = cpu.edx;
    e.back(cpu, reg32(*r));
    if (*r == 0)
    {
        cpu.ebx = ebx;
        cpu.edx = edx;
    }
}

void SNDpathcontrol(App* app, CPU& cpu)
{
    const Entry e(cpu);
    e.finish(cpu, pathControl(app, cpu, e.esp, int32_t(e.eax)));
}

/* Past an error for Pathfinder not set up, edx is left the error's line. */
void SNDpathevent(App* app, CPU& cpu)
{
    const Entry e(cpu);
    const bool notSetUp = kInited(app) != 0 && kPathRestore(app) == 0;
    const Result r = pathEvent(app, cpu, e.esp, int32_t(e.eax), int32_t(e.edx));
    if (!r)
        return;
    e.back(cpu, reg32(*r));
    if (notSetUp)
        cpu.edx = 0x2d0;
}

void SNDpatheventinterrupt(App* app, CPU& cpu)
{
    const Entry e(cpu);
    e.finish(cpu, pathEventInterrupt(app, cpu, e.esp, int32_t(e.eax)));
}

void SNDpathrestore(App* app, CPU& cpu)
{
    const Entry e(cpu);
    e.finish(cpu, pathRestore(app, cpu, e.esp));
}

}  // namespace port
}  // namespace nfs3hp
