#include "native_guest.h"

/* EA's network layer under the menus: packets sent, NET and CONN, the queues, LAYER.  disassemble_nfs3hp.py binds each address to the function of that
 * name here (EA_NET_NATIVES), and the generated code calls it by name.
 * tools/game_checks holds each against its generated code.
 *
 * The game's side (0x49ecb0 to 0x4a6690): the network's state is at
 * 0x7a2274 to 0x7a25b4 -- the machines in the game (their count in
 * 0x7a2274's high word, their connections from 0x7a21f0 on, machine 0 this
 * one), the player each machine is (8 words at 0x7a227a), what each player's
 * machine is doing (8 words at 0x7a22ca), the network's kind (0x7a22e4: 1 a
 * host's network, 2 two machines over a modem or cable, whose packets go
 * through the link's function at 0x7a21b8), this machine the host
 * (0x7a22da), the connection lost (0x7a22dc, 0x7a22de), the game under way
 * (0x7a22e0 3), and 7 connections of 0x6c bytes from 0x7a22e8 -- the host's
 * to a client, or a client's (the first) to its host.  A packet goes to one
 * machine's connection, or to all of them, tried again 9 times (a sleep a
 * little longer each time) before the connection counts as lost; a machine
 * lost while the game is under way is told to the others (packet 0xe).  The
 * game's NET object is at 0x7a0390 (its functions at [+4], a player's check
 * at [+8], its game at [+0xc]); the game's sessions, 0x2c bytes each, at
 * 0x55e734 ([0x55e718] of them, the current one's id at 0x55e71c).
 *
 * EA's side: NET_ (0x4f4f50 to 0x4f5040) traces its call when [0x566de0]
 * says so, and calls the NET object's function; CONN (cmn\connect.c) closes
 * and restores the connections, kept in the queues at 0x9f260c and 0x9f2628
 * (0x9f25f0: the players NET_endgame looks for); a connection's +4 is its
 * functions (+8 send, +0xc whether it counts, +0x10 close), +0x10 it open,
 * +0x24 it up, +0x30 the queue of its layers.  The queues (cmn\queue.c) are
 * 0x1c bytes: +0 how many, +4 flags (1 changed, 2 its lock its own), +8 the
 * first element, +0xc the last, +0x10 and +0x14 a priority's function and
 * its argument, +0x18 the lock (a critical section; 0 an uninitialized
 * queue, reported); an element's first dword is the next.  LAYER
 * (cmn\layer.c) hands a packet -- pieces of {length, address} -- down a
 * connection's layers from the top, each layer's packer (+4, its data +0xc)
 * calling the next; under the last the pieces are gathered into one block
 * ('FILTER') and sent by the connection's own send.
 *
 * Not network code, but in the range: EA's unpackers that the game's
 * unpacker (0x4f2560) picks by a file's first two bytes -- Huffman with
 * runs (0x30fb to 0x35fb, the 0x32fb and 0x34fb kinds delta coded after),
 * runs of bytes and nibbles (0x4afb), DXT1 blocks to 16-bit pixels (0x18fb)
 * and byte pairs (0x46fb, 0x47fb), the last with its tables in its own frame
 * and their addresses at 0xa0b030 to 0xa0b040.
 *
 * Written as their code is: each push and pop to the guest's stack, each call
 * with the return address's slot, the frame's locals in the guest's memory,
 * the registers as the code leaves them, bytes copied as the code copies
 * them (movsd, then movsb for the rest).  The run's jump table (0x510100) is
 * followed by the targets nfs3.exe's table holds.  Windows' functions are
 * called through their imports' slots; the connections', NET's, the link's
 * and the layers' functions through the pointers the game keeps; every other
 * function of the game's by address -- the packet sent (0x4a60e0) and a
 * machine's number (0x4a6650) too, which other natives' checks stand in for.
 * Huffman's (0x50ed50), a knot of jumps, is written with them, a label at
 * each target. */
namespace nfs3hp
{
namespace ea
{

namespace
{

using guest::at;
using guest::byte;
using guest::put;
using guest::putByte;
using x86::reg16;
using x86::reg32;
using x86::reg8;
using x86::sreg32;

// Where an Error is from: the file, the function, the line.
constexpr reg32 kWhereFile = 0x552190, kWhereFunction = 0x552194, kWhereLine = 0x552198;
// The game's network: its sessions -- how many, the current one's id, the
// first one's id and its flag (0x2c bytes each) -- the game ending, its lock;
// the link's id.
constexpr reg32 kSessionCount = 0x55e718, kSessionId = 0x55e71c, kSessionIds = 0x55e734, kSessionFlags = 0x55e738;
constexpr reg32 kEnding = 0x55e860, kEndingLock = 0x55e864, kLinkId = 0x55ecb0;
// The NET object; the connections left (7 of them), the links open.
constexpr reg32 kNet = 0x7a0390, kPendingPlayers = 0x7a02e8, kLinksOpen = 0x7a01e0;
// The link's: its broadcast's buffer, its port, its function.
constexpr reg32 kLinkBroadcast = 0x7a20a0, kLinkPort = 0x7a215c, kLinkSend = 0x7a21b8;
// The machines' connections, their count (the high word), the players' machines.
constexpr reg32 kMachines = 0x7a21f0, kMachineCount = 0x7a2274, kMachinePlayers = 0x7a227a;
constexpr reg32 kSetUp = 0x7a2276, kInputNotSent = 0x7a2290, kStateBlock = 0x7a2294, kStateChanged = 0x7a2296;
constexpr reg32 kPlayerStates = 0x7a22ba, kMachineStates = 0x7a22ca;
constexpr reg32 kNetworkHost = 0x7a22da, kConnectionLost = 0x7a22dc, kConnectionLostToo = 0x7a22de;
constexpr reg32 kGameState = 0x7a22e0, kNetworkKind = 0x7a22e4, kConnections = 0x7a22e8;
constexpr reg32 kConnectionCount = 7, kConnectionUp = 0x24, kConnectionOpen = 0x10;
constexpr reg32 kOwnOnly = 0x6fd50c;
// The packets: a machine left (0xe), the network closed (4), the input (6).
constexpr reg32 kMachineLeftPacket = 0xe, kClosedPacket = 4, kInputPacket = 6;
// EA's: the trace's level; the connections restored; the open connections.
constexpr reg32 kTraceLevel = 0x566de0, kRestoring = 0x566df4, kOpenCount = 0x566df8;
// The queues: the players, the connections, those closing.
constexpr reg32 kPlayersQueue = 0x9f25f0, kConnectionsQueue = 0x9f260c, kClosingQueue = 0x9f2628;
// The byte pairs' tables and where they write.
constexpr reg32 kPairOut = 0xa0b030, kPairLeft = 0xa0b034, kPairIn = 0xa0b038, kPairRight = 0xa0b03c;
constexpr reg32 kPairKind = 0xa0b040;
// The game's strings: NET's, CONN's, the queues', LAYER's.
constexpr reg32 kShutGameName = 0x54d138, kEndGameName = 0x54d158, kKillPlayerName = 0x54d174;
constexpr reg32 kConnectC = 0x54d194, kRestoreName = 0x54d1a4, kNotRemoved = 0x54d1b4;
constexpr reg32 kQueueC = 0x54fbb8, kUninitialized = 0x54fbcc, kQfreeName = 0x54fc00, kQremoveName = 0x54fc34;
constexpr reg32 kQlengthName = 0x54fc3c, kQpositionName = 0x54fc44, kQfindindexName = 0x54fc78;
constexpr reg32 kLayerC = 0x550194, kLayerSendName = 0x5501a0, kFilterName = 0x5501ac;
constexpr reg32 kCallPackerName = 0x5501cc, kFindFailed = 0x5501e0;
// Windows' functions, by their imports' slots.
constexpr reg32 kEnterCriticalSection = 0x5344b8, kLeaveCriticalSection = 0x534588;
// The game's functions, by address.
constexpr reg32 kError = 0x401010, kCloseMessages = 0x42d7f0, kFreeNetworkLocks = 0x49a4d0, kSend = 0x4a60e0;
constexpr reg32 kMachineNumber = 0x4a6650, kSleep = 0x4df8e0, kMemset = 0x4e0640, kFillZero = 0x4e070c;
constexpr reg32 kAllocate = 0x4e1620, kFree = 0x4e1890, kTimers = 0x4e7630, kMoveMemory = 0x4ea4f0;
constexpr reg32 kFreeLock = 0x4eb360, kRemoveTask = 0x4f29b0, kNetMessage = 0x512180;
constexpr reg32 kConnectionTask = 0x4f5110;

void push(win32::WinApplication* app, x86::CPU& cpu, reg32 value)
{
    cpu.esp -= 4;
    put(app, cpu.esp, value);
}

reg32 pop(win32::WinApplication* app, x86::CPU& cpu)
{
    const reg32 value = at(app, cpu.esp);
    cpu.esp += 4;
    return value;
}

reg16 word16(win32::WinApplication* app, reg32 address)
{
    return app->getMemory<reg16>(address);
}

void putWord16(win32::WinApplication* app, reg32 address, reg16 value)
{
    app->getMemory<reg16>(address) = value;
}

/* A call as the code makes it: the return address's slot, and esp as the
 * callee leaves it.  False when the game stopped in it. */
bool direct(win32::WinApplication* app, x86::CPU& cpu, void (*function)(win32::WinApplication*, x86::CPU&))
{
    cpu.esp -= 4;
    function(app, cpu);
    return !cpu.terminate;
}

bool byAddress(win32::WinApplication* app, x86::CPU& cpu, reg32 target)
{
    cpu.esp -= 4;
    app->dynamic_call(target, cpu);
    return !cpu.terminate;
}

/* A Windows function, through its import's slot. */
bool windows(win32::WinApplication* app, x86::CPU& cpu, reg32 slot)
{
    return byAddress(app, cpu, at(app, slot));
}

/* push edi; mov eax, ecx; shr ecx, 2; rep movsd; mov cl, al; and cl, 3;
 * rep movsb; pop edi: ecx bytes from esi to edi, esi past them, edi as it
 * was, eax the count, ecx 0. */
void copyBytes(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.edi);
    cpu.eax = cpu.ecx;
    cpu.ecx >>= 2;
    for (; cpu.ecx != 0; --cpu.ecx)
    {
        put(app, cpu.edi, at(app, cpu.esi));
        cpu.edi += 4;
        cpu.esi += 4;
    }
    cpu.cl = cpu.al;
    cpu.cl &= 3;
    for (; cpu.ecx != 0; --cpu.ecx)
    {
        putByte(app, cpu.edi, byte(app, cpu.esi));
        ++cpu.edi;
        ++cpu.esi;
    }
    cpu.edi = pop(app, cpu);
}

/* lea eax, [reg*4]; sub eax, reg; shl eax, 2; mov edx, eax; shl eax, 3;
 * add eax, edx: reg * 0x6c, a connection's offset, edx its twelfth. */
void connectionOffset(x86::CPU& cpu, reg32 index)
{
    cpu.eax = index * 4;
    cpu.eax -= index;
    cpu.eax <<= 2;
    cpu.edx = cpu.eax;
    cpu.eax <<= 3;
    cpu.eax += cpu.edx;
}

/* lea eax, [reg*4]; sub eax, reg; shl eax, 3; add eax, reg; add eax, eax;
 * add eax, 0xa: the sleep before try reg + 1, 50 * reg + 10. */
void retryWait(x86::CPU& cpu, reg32 index)
{
    cpu.eax = index * 4;
    cpu.eax -= index;
    cpu.eax <<= 3;
    cpu.eax += index;
    cpu.eax += cpu.eax;
}

/* mov edx, eax; shl eax, 2; sub eax, edx; shl eax, 2; sub eax, edx: eax * 11,
 * a session's dword index (0x2c bytes each). */
void sessionOffset(x86::CPU& cpu, reg32& scratch)
{
    scratch = cpu.eax;
    cpu.eax <<= 2;
    cpu.eax -= scratch;
    cpu.eax <<= 2;
    cpu.eax -= scratch;
}

/* An Error, as the queues and CONN report one: where it is from, and the
 * words the code pushed for it taken off after. */
bool error(win32::WinApplication* app, x86::CPU& cpu, reg32 words)
{
    if (!byAddress(app, cpu, kError))
        return false;
    cpu.esp += 4 * words;
    return true;
}

}  // namespace

void dropMachine(win32::WinApplication* app, x86::CPU& cpu);
void announceMachineLeft(win32::WinApplication* app, x86::CPU& cpu);
void endNetworkGame(win32::WinApplication* app, x86::CPU& cpu);
void sessionIndex(win32::WinApplication* app, x86::CPU& cpu);
void forgetPendingPlayer(win32::WinApplication* app, x86::CPU& cpu);
void sendOverLink(win32::WinApplication* app, x86::CPU& cpu);
void sendPacket(win32::WinApplication* app, x86::CPU& cpu);
void resetNetwork(win32::WinApplication* app, x86::CPU& cpu);
void closeNetwork(win32::WinApplication* app, x86::CPU& cpu);
void machineNumber(win32::WinApplication* app, x86::CPU& cpu);
void playerMachine(win32::WinApplication* app, x86::CPU& cpu);
void netTrace(win32::WinApplication* app, x86::CPU& cpu);
void netShutGame(win32::WinApplication* app, x86::CPU& cpu);
void netEndGame(win32::WinApplication* app, x86::CPU& cpu);
void netKillPlayer(win32::WinApplication* app, x86::CPU& cpu);
void netCheckPlayer(win32::WinApplication* app, x86::CPU& cpu);
void connRestore(win32::WinApplication* app, x86::CPU& cpu);
void connSend(win32::WinApplication* app, x86::CPU& cpu);
void connClose(win32::WinApplication* app, x86::CPU& cpu);
void qnth(win32::WinApplication* app, x86::CPU& cpu);
void qunlink(win32::WinApplication* app, x86::CPU& cpu);
void qfree(win32::WinApplication* app, x86::CPU& cpu);
void qremove(win32::WinApplication* app, x86::CPU& cpu);
void qlength(win32::WinApplication* app, x86::CPU& cpu);
void qposition(win32::WinApplication* app, x86::CPU& cpu);
void qfindindex(win32::WinApplication* app, x86::CPU& cpu);
void huffUnpack(win32::WinApplication* app, x86::CPU& cpu);
void runUnpack(win32::WinApplication* app, x86::CPU& cpu);
void dxtBlock(win32::WinApplication* app, x86::CPU& cpu);
void dxtUnpack(win32::WinApplication* app, x86::CPU& cpu);
void pairExpand(win32::WinApplication* app, x86::CPU& cpu);
void pairUnpack(win32::WinApplication* app, x86::CPU& cpu);
void layerSend(win32::WinApplication* app, x86::CPU& cpu);
void layerCallPacker(win32::WinApplication* app, x86::CPU& cpu);
void layerPackFromTop(win32::WinApplication* app, x86::CPU& cpu);
void layerFree(win32::WinApplication* app, x86::CPU& cpu);
void layerSendPacket(win32::WinApplication* app, x86::CPU& cpu);

/* 0x49ecb0: the connection eax dropped, if it is one and open: closed
 * (connClose), its player killed in the NET game (netKillPlayer, its +0x34),
 * the machines' states changed and the links open one fewer. */
void dropMachine(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.edx = cpu.eax;
    if (cpu.eax != 0 && at(app, cpu.eax + kConnectionOpen) != 0)
    {
        if (!direct(app, cpu, connClose))
            return;
        cpu.eax = kNet;
        cpu.edx += 0x34;
        if (!direct(app, cpu, netKillPlayer))
            return;
        cpu.ebx = at(app, kLinksOpen);
        cpu.edx = 1;
        --cpu.ebx;
        putWord16(app, kStateChanged, cpu.dx);
        put(app, kLinksOpen, cpu.ebx);
    }
    cpu.ebp = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x49ecf0: machine eax gone: its pending player forgotten
 * (forgetPendingPlayer, its connection's +0x34); then, unless the game is
 * ending and for machines 0 to 7, under the ending's lock, a machine whose
 * state was 0 marked 2 and the others told: packet 0xe, the 8 machines'
 * states after it, 0x12 bytes, sent to all. */
void announceMachineLeft(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.esp -= 0x14;
    const auto leave = [&] {
        cpu.esp = cpu.ebp;
        cpu.ebp = pop(app, cpu);
        cpu.edi = pop(app, cpu);
        cpu.esi = pop(app, cpu);
        cpu.edx = pop(app, cpu);
        cpu.ecx = pop(app, cpu);
        cpu.ebx = pop(app, cpu);
        cpu.esp += 4;
    };
    cpu.ebx = cpu.eax;
    cpu.eax = at(app, cpu.eax * 4 + kMachines);
    cpu.eax += 0x34;
    if (!direct(app, cpu, forgetPendingPlayer))
        return;
    if (at(app, kEnding) != 0 || sreg32(cpu.ebx) > 7 || sreg32(cpu.ebx) < 0)
        return leave();
    cpu.ecx = at(app, kEndingLock);
    push(app, cpu, cpu.ecx);
    if (!windows(app, cpu, kEnterCriticalSection))
        return;
    cpu.eax = cpu.ebx + cpu.ebx;
    if (word16(app, cpu.eax + kMachineStates) != 0)
    {
        cpu.esi = at(app, kEndingLock);
        push(app, cpu, cpu.esi);
        if (!windows(app, cpu, kLeaveCriticalSection))
            return;
        return leave();
    }
    putWord16(app, cpu.eax + kMachineStates, 2);
    cpu.ebx = at(app, kEndingLock);
    push(app, cpu, cpu.ebx);
    cpu.esi = kMachineStates;
    cpu.edi = cpu.ebp - 0x12;
    if (!windows(app, cpu, kLeaveCriticalSection))
        return;
    cpu.ah = kMachineLeftPacket;
    cpu.ecx = 0x10;
    cpu.ebx = 0x12;
    cpu.edx = cpu.ebp - 0x14;
    putByte(app, cpu.ebp - 0x14, cpu.ah);
    copyBytes(app, cpu);
    cpu.ecx = 1;
    cpu.eax = 0;
    putWord16(app, kStateChanged, cpu.cx);
    if (!byAddress(app, cpu, kSend))
        return;
    leave();
}

/* 0x49eed0: the network game ended, if under way (state 3) on a host's
 * network: the host's connections dropped (dropMachine); with the game
 * ending and the session's flag, the NET game shut (netShutGame, 1); with
 * the flag, the NET game ended (netEndGame); the game no longer ending. */
void endNetworkGame(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    if (at(app, kGameState) == 3)
    {
        if (at(app, kNetworkKind) != 2)
        {
            if (word16(app, kNetworkHost) != 0)
            {
                for (cpu.edx = 0; sreg32(cpu.edx) < sreg32(kConnectionCount); ++cpu.edx)
                {
                    cpu.eax = cpu.edx * 4;
                    cpu.eax -= cpu.edx;
                    cpu.eax <<= 2;
                    cpu.ecx = cpu.eax;
                    cpu.eax <<= 3;
                    cpu.eax += cpu.ecx;
                    if (at(app, cpu.eax + kConnections + kConnectionOpen) != 0)
                    {
                        cpu.eax += kConnections;
                        if (!direct(app, cpu, dropMachine))
                            return;
                    }
                }
                if (at(app, kEnding) != 0)
                {
                    cpu.eax = at(app, kSessionId);
                    if (!direct(app, cpu, sessionIndex))
                        return;
                    sessionOffset(cpu, cpu.edx);
                    if (at(app, cpu.eax * 4 + kSessionFlags) != 0)
                    {
                        cpu.edx = 1;
                        cpu.eax = kNet;
                        if (!direct(app, cpu, netShutGame))
                            return;
                    }
                }
            }
            cpu.eax = at(app, kSessionId);
            if (!direct(app, cpu, sessionIndex))
                return;
            sessionOffset(cpu, cpu.edx);
            if (at(app, cpu.eax * 4 + kSessionFlags) != 0)
            {
                cpu.eax = kNet;
                if (!direct(app, cpu, netEndGame))
                    return;
            }
        }
        cpu.ecx = 0;
        put(app, kEnding, cpu.ecx);
    }
    cpu.ebp = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x49f1c0: the index of the session whose id is eax, of [0x55e718], or -1. */
void sessionIndex(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.ebx = cpu.eax;
    cpu.eax = 0xffffffff;
    for (cpu.edx = 0; sreg32(cpu.edx) < sreg32(at(app, kSessionCount)); ++cpu.edx)
    {
        cpu.eax = cpu.edx * 4;
        cpu.eax -= cpu.edx;
        cpu.eax <<= 2;
        cpu.eax -= cpu.edx;
        if (cpu.ebx == at(app, cpu.eax * 4 + kSessionIds))
        {
            cpu.eax = cpu.edx;
            break;
        }
        cpu.eax = 0xffffffff;
    }
    cpu.ebp = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x49f550: the player at eax forgotten among the 7 pending (0x7a02e8)
 * unless the current session's flag is set: each pending one the NET
 * object's check (netCheckPlayer) says it is, cleared. */
void forgetPendingPlayer(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.esi = cpu.eax;
    cpu.eax = at(app, kSessionId);
    if (!direct(app, cpu, sessionIndex))
        return;
    sessionOffset(cpu, cpu.ecx);
    if (at(app, cpu.eax * 4 + kSessionFlags) == 0)
    {
        for (cpu.ecx = 0; sreg32(cpu.ecx) < sreg32(kConnectionCount); ++cpu.ecx)
        {
            cpu.edi = cpu.ecx * 4;
            cpu.ebx = at(app, cpu.edi + kPendingPlayers);
            if (cpu.ebx == 0)
                continue;
            cpu.eax = kNet;
            cpu.edx = cpu.esi;
            if (!direct(app, cpu, netCheckPlayer))
                return;
            if (cpu.eax != 0)
            {
                cpu.eax = 0;
                put(app, cpu.edi + kPendingPlayers, cpu.eax);
            }
        }
    }
    cpu.ebp = pop(app, cpu);
    cpu.edi = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x4a5d10: a packet sent over the two machines' link (the network's kind
 * 2): edx it, ebx its length, to machine eax -- its +0x34 byte the
 * address, 0xb0 -- or with eax 0 to all, 0xc0 and the broadcast's buffer;
 * the link's function at 0x7a21b8 called (cdecl, 7 words). */
void sendOverLink(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.esp -= 4;
    cpu.ecx = cpu.eax;
    if (cpu.eax == 0)
    {
        push(app, cpu, cpu.ebx);
        push(app, cpu, cpu.edx);
        push(app, cpu, 1);
        push(app, cpu, kLinkBroadcast);
        push(app, cpu, 0xc0);
        cpu.edx = at(app, kLinkPort);
        push(app, cpu, cpu.edx);
        cpu.ecx = at(app, kLinkId);
        push(app, cpu, cpu.ecx);
    }
    else
    {
        push(app, cpu, cpu.ebx);
        cpu.eax = 0;
        push(app, cpu, cpu.edx);
        cpu.al = byte(app, cpu.ecx + 0x34);
        push(app, cpu, 1);
        put(app, cpu.ebp - 4, cpu.eax);
        cpu.eax = cpu.ebp - 4;
        push(app, cpu, cpu.eax);
        push(app, cpu, 0xb0);
        cpu.ebx = at(app, kLinkPort);
        push(app, cpu, cpu.ebx);
        cpu.esi = at(app, kLinkId);
        push(app, cpu, cpu.esi);
    }
    if (!byAddress(app, cpu, at(app, kLinkSend)))
        return;
    cpu.esp += 0x1c;
    cpu.esp = cpu.ebp;
    cpu.ebp = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x4a60e0: a packet sent -- edx it, ebx its length -- to the connection eax,
 * or with eax 0 to all; nothing once the connection is lost.  Over the link
 * (the network's kind 2) by sendOverLink.  A client's (or anyone's to all
 * on a network of kind 0) goes to its host's connection (0x7a22e8): sent,
 * [0x7a2290] is 0; not sent, the input's packet (6) on a host's network
 * leaves [0x7a2290] 1, anything else is tried 9 times more, a sleep before
 * each, and then the connection counts as lost.  A host's to one machine is
 * tried as long as its connection is up, to all to each of the 7 up; a
 * machine still not reached is announced gone while the game is under way
 * (announceMachineLeft, by its number), and otherwise the connection counts
 * as lost. */
void sendPacket(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.esp -= 0xc;
    const auto leave = [&] {
        cpu.esp = cpu.ebp;
        cpu.ebp = pop(app, cpu);
        cpu.edi = pop(app, cpu);
        cpu.esi = pop(app, cpu);
        cpu.ecx = pop(app, cpu);
        cpu.esp += 4;
    };
    // The connection counts as lost.
    const auto lost = [&] {
        cpu.edx = 1;
        putWord16(app, kConnectionLostToo, cpu.dx);
        putWord16(app, kConnectionLost, cpu.dx);
        leave();
    };
    cpu.edi = cpu.eax;
    cpu.ecx = cpu.edx;
    cpu.esi = cpu.ebx;
    if (word16(app, kConnectionLost) != 0)
        return leave();
    cpu.edx = at(app, kNetworkKind);
    if (cpu.edx == 2)
    {
        cpu.edx = cpu.ecx;
        if (!direct(app, cpu, sendOverLink))
            return;
        return leave();
    }
    if (word16(app, kNetworkHost) == 0 || cpu.edx == 0)
    {
        if (at(app, kConnections + kConnectionUp) == 0)
            return leave();
        cpu.eax = kConnections;
        cpu.ebx = cpu.esi;
        cpu.edx = cpu.ecx;
        if (!direct(app, cpu, connSend))
            return;
        if (cpu.eax != 0)
        {
            cpu.edi = 0;
            put(app, kInputNotSent, cpu.edi);
            return leave();
        }
        cpu.ah = byte(app, cpu.ecx);
        if (cpu.ah == kInputPacket)
        {
            cpu.eax = at(app, kNetworkKind);
            if (cpu.eax == 1)
            {
                put(app, kInputNotSent, cpu.eax);
                return leave();
            }
        }
        for (cpu.edi = 0; at(app, kConnections + kConnectionUp) != 0 && word16(app, kConnectionLost) == 0;)
        {
            retryWait(cpu, cpu.edi);
            cpu.ebx = cpu.esi;
            cpu.eax += 0xa;
            cpu.edx = cpu.ecx;
            if (!byAddress(app, cpu, kSleep))
                return;
            cpu.eax = kConnections;
            if (!direct(app, cpu, connSend))
                return;
            if (cpu.eax != 0)
            {
                cpu.esi = 0;
                put(app, kInputNotSent, cpu.esi);
                return leave();
            }
            ++cpu.edi;
            if (sreg32(cpu.edi) >= 9)
                break;
        }
        return lost();
    }
    if (cpu.eax != 0)
    {
        if (at(app, cpu.eax + kConnectionUp) == 0)
            return leave();
        cpu.ebx = cpu.esi;
        cpu.edx = cpu.ecx;
        cpu.eax = cpu.edi;
        if (!direct(app, cpu, connSend))
            return;
        if (cpu.eax != 0)
            return leave();
        put(app, cpu.ebp - 8, cpu.eax);
        while (at(app, cpu.edi + kConnectionUp) != 0 && word16(app, kConnectionLost) == 0)
        {
            cpu.edx = at(app, cpu.ebp - 8);
            retryWait(cpu, cpu.edx);
            cpu.ebx = cpu.esi;
            cpu.eax += 0xa;
            cpu.edx = cpu.ecx;
            if (!byAddress(app, cpu, kSleep))
                return;
            cpu.eax = cpu.edi;
            if (!direct(app, cpu, connSend))
                return;
            if (cpu.eax != 0)
                return leave();
            put(app, cpu.ebp - 8, at(app, cpu.ebp - 8) + 1);
            if (sreg32(at(app, cpu.ebp - 8)) >= 9)
                break;
        }
        if (at(app, kGameState) != 3)
            return lost();
        cpu.eax = cpu.edi;
        if (!byAddress(app, cpu, kMachineNumber))
            return;
        cpu.eax = reg32(sreg32(x86::sreg16(cpu.ax)));
        if (!direct(app, cpu, announceMachineLeft))
            return;
        return leave();
    }
    // To all: each connection up, di its index.
    cpu.edi ^= cpu.eax;
    for (;;)
    {
        connectionOffset(cpu, reg32(sreg32(x86::sreg16(cpu.di))));
        if (at(app, cpu.eax + kConnections + kConnectionUp) != 0)
        {
            cpu.eax += kConnections;
            cpu.ebx = cpu.esi;
            cpu.edx = cpu.ecx;
            if (!direct(app, cpu, connSend))
                return;
            if (cpu.eax == 0)
            {
                put(app, cpu.ebp - 0xc, cpu.eax);
                put(app, cpu.ebp - 4, cpu.eax);
                bool sent = false;
                for (;;)
                {
                    cpu.edx = reg32(sreg32(x86::sreg16(cpu.di)));
                    cpu.eax = cpu.edx * 4;
                    cpu.eax -= cpu.edx;
                    cpu.eax <<= 2;
                    cpu.ebx = cpu.eax * 8;
                    cpu.ebx += cpu.eax;
                    if (at(app, cpu.ebx + kConnections + kConnectionUp) == 0 || word16(app, kConnectionLost) != 0)
                        break;
                    cpu.edx = at(app, cpu.ebp - 4);
                    retryWait(cpu, cpu.edx);
                    cpu.eax += 0xa;
                    if (!byAddress(app, cpu, kSleep))
                        return;
                    cpu.eax = kConnections;
                    cpu.edx = cpu.ecx;
                    cpu.eax += cpu.ebx;
                    cpu.ebx = cpu.esi;
                    if (!direct(app, cpu, connSend))
                        return;
                    sent = cpu.eax != 0;
                    if (sent)
                        break;
                    put(app, cpu.ebp - 4, at(app, cpu.ebp - 4) + 1);
                    if (sreg32(at(app, cpu.ebp - 4)) >= 9)
                        break;
                }
                if (!sent && at(app, cpu.ebp - 0xc) == 0)
                {
                    if (at(app, kGameState) == 3)
                    {
                        connectionOffset(cpu, reg32(sreg32(x86::sreg16(cpu.di))));
                        cpu.eax += kConnections;
                        if (!byAddress(app, cpu, kMachineNumber))
                            return;
                        cpu.eax = reg32(sreg32(x86::sreg16(cpu.ax)));
                        if (!direct(app, cpu, announceMachineLeft))
                            return;
                    }
                    else
                    {
                        cpu.edx = 1;
                        putWord16(app, kConnectionLostToo, cpu.dx);
                        putWord16(app, kConnectionLost, cpu.dx);
                    }
                }
            }
        }
        ++cpu.edi;
        if (x86::sreg16(cpu.di) >= 7)
            return leave();
    }
}

/* 0x4a6390: the network's state made anew: set up, the state's block (0x26
 * bytes), the players' and the machines' states (0x10 bytes each) zeroed,
 * this machine the host, the connection not lost, no game under way; with
 * eax nonzero, the second lost flag cleared too.  edx left 0. */
void resetNetwork(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.ecx = cpu.eax;
    cpu.edx = 1;
    cpu.eax = kStateBlock;
    putWord16(app, kSetUp, cpu.dx);
    cpu.edx = 0x26;
    if (!byAddress(app, cpu, kFillZero))
        return;
    cpu.edx = 0x10;
    cpu.eax = kPlayerStates;
    cpu.ebx = 1;
    if (!byAddress(app, cpu, kFillZero))
        return;
    cpu.edx = 0x10;
    cpu.eax = kMachineStates;
    cpu.esi = 0;
    if (!byAddress(app, cpu, kFillZero))
        return;
    putWord16(app, kNetworkHost, cpu.bx);
    cpu.edx = 0;
    putWord16(app, kConnectionLost, cpu.si);
    put(app, kGameState, cpu.edx);
    if (cpu.ecx != 0)
    {
        cpu.edi = 0;
        putWord16(app, kConnectionLostToo, cpu.di);
    }
    cpu.ebp = pop(app, cpu);
    cpu.edi = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x4a65e0: the network closed: the game's timers stopped; a host tells the
 * others (packet 4, 4 bytes); the connections restored
 * (connRestore); the timers stopped again; the network game ended
 * (endNetworkGame), the race's messages closed, the network's locks freed
 * (0x49a4d0); the network's state made anew (resetNetwork, 0), and only
 * this machine's player queued no longer (0x6fd50c, resetNetwork's edx).
 * The packet: 4, the byte the frame held there (never written, a game bug
 * kept), the word 0xc. */
void closeNetwork(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.esp -= 4;
    cpu.eax = 0;
    if (!byAddress(app, cpu, kTimers))
        return;
    if (word16(app, kNetworkHost) != 0)
    {
        cpu.ah = kClosedPacket;
        cpu.ebx = 0xc;
        cpu.edx = cpu.ebp - 4;
        putByte(app, cpu.ebp - 4, cpu.ah);
        putWord16(app, cpu.ebp - 2, cpu.bx);
        cpu.ebx = 4;
        cpu.eax = 0;
        if (!byAddress(app, cpu, kSend))
            return;
    }
    if (!direct(app, cpu, connRestore))
        return;
    cpu.eax = 0;
    if (!byAddress(app, cpu, kTimers))
        return;
    if (!direct(app, cpu, endNetworkGame))
        return;
    if (!byAddress(app, cpu, kCloseMessages))
        return;
    if (!byAddress(app, cpu, kFreeNetworkLocks))
        return;
    cpu.eax = 0;
    cpu.edx = 0;
    if (!direct(app, cpu, resetNetwork))
        return;
    put(app, kOwnOnly, cpu.edx);
    cpu.esp = cpu.ebp;
    cpu.ebp = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x4a6650: the number of the machine whose connection is eax -- 1 up to
 * the machines' count (0x7a2274's high word) -- or -1; -1 for eax 0. */
void machineNumber(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.edx = cpu.eax;
    cpu.eax = 0xffffffff;
    if (cpu.edx != 0)
    {
        for (cpu.eax = 1;; ++cpu.eax)
        {
            cpu.ecx = reg32(sreg32(at(app, kMachineCount)) >> 16);
            if (sreg32(cpu.eax) >= sreg32(cpu.ecx))
            {
                cpu.eax = 0xffffffff;
                break;
            }
            if (cpu.edx == at(app, cpu.eax * 4 + kMachines))
                break;
        }
    }
    cpu.ebp = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x4a6690: the machine whose player is ax, of the 8 (0x7a227a), or -1. */
void playerMachine(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.edx = cpu.eax;
    cpu.eax = 0;
    while (cpu.dx != word16(app, cpu.eax * 2 + kMachinePlayers))
    {
        ++cpu.eax;
        if (sreg32(cpu.eax) >= 8)
        {
            cpu.eax = 0xffffffff;
            break;
        }
    }
    cpu.ebp = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x4f4c50: NET's trace of the call named eax, when [0x566de0] is 1 or
 * more: the network's message (0x512180) with 0, 0 on the stack. */
void netTrace(win32::WinApplication* app, x86::CPU& cpu)
{
    if (sreg32(at(app, kTraceLevel)) < 1)
    {
        cpu.esp += 4;
        return;
    }
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.ebx);
    push(app, cpu, 0);
    cpu.ecx = 0;
    push(app, cpu, 0);
    cpu.ebx = 0;
    cpu.edx = 0;
    if (!byAddress(app, cpu, kNetMessage))
        return;
    cpu.ebx = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.esp += 4;
}

namespace
{

/* The NET object eax's function at `slot` of its functions (+4), traced as
 * `name` first: push ebx; push ecx; ... pop ecx; pop ebx; ret. */
void netCall(win32::WinApplication* app, x86::CPU& cpu, reg32 name, reg32 slot)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    cpu.ecx = cpu.eax;
    cpu.eax = name;
    if (!direct(app, cpu, netTrace))
        return;
    cpu.ebx = at(app, cpu.ecx + 4);
    cpu.eax = cpu.ecx;
    if (!byAddress(app, cpu, at(app, cpu.ebx + slot)))
        return;
    cpu.ecx = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4;
}

}  // namespace

/* 0x4f4f50, EA's NET_shutgame: the NET object eax's game shut, edx how
 * (its function +0x24). */
void netShutGame(win32::WinApplication* app, x86::CPU& cpu)
{
    netCall(app, cpu, kShutGameName, 0x24);
}

/* 0x4f4f90, EA's NET_endgame: the NET object eax's game ended (its function
 * +0x2c) -- 1 without it when the object is not among the players' queue's
 * (0x9f25f0). */
void netEndGame(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    cpu.ecx = cpu.eax;
    cpu.eax = kEndGameName;
    if (!direct(app, cpu, netTrace))
        return;
    cpu.edx = cpu.ecx;
    cpu.eax = kPlayersQueue;
    if (!direct(app, cpu, qposition))
        return;
    if (cpu.eax == 0xffffffff)
        cpu.eax = 1;
    else
    {
        cpu.edx = at(app, cpu.ecx + 4);
        cpu.eax = cpu.ecx;
        if (!byAddress(app, cpu, at(app, cpu.edx + 0x2c)))
            return;
    }
    cpu.edx = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x4f4ff0, EA's NET_killplayer: the player edx killed in the NET object
 * eax's game (its function +0x34). */
void netKillPlayer(win32::WinApplication* app, x86::CPU& cpu)
{
    netCall(app, cpu, kKillPlayerName, 0x34);
}

/* 0x4f5040: whether the player edx is the NET object eax's: its check's
 * function (+8, its +0x40) asked with the object's game (+0xc).  No trace. */
void netCheckPlayer(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ecx);
    cpu.ecx = at(app, cpu.eax + 8);
    cpu.eax = at(app, cpu.eax + 0xc);
    if (!byAddress(app, cpu, at(app, cpu.ecx + 0x40)))
        return;
    cpu.ecx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x4f5280, EA's CONN_restore: when connections are restored
 * ([0x566df4]), each closing connection (0x9f2628) closed (connClose) as
 * long as there is a first, then each connection (0x9f260c): closed and, if
 * its close left it in the list, removed -- an Error when it was there to
 * remove ("NOT REMOVED FROM LIST BY CLOSE"). */
void connRestore(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    const auto leave = [&] {
        cpu.ebp = pop(app, cpu);
        cpu.edi = pop(app, cpu);
        cpu.esi = pop(app, cpu);
        cpu.edx = pop(app, cpu);
        cpu.ecx = pop(app, cpu);
        cpu.ebx = pop(app, cpu);
        cpu.esp += 4;
    };
    if (at(app, kRestoring) == 0)
        return leave();
    cpu.ebx = kClosingQueue;
    cpu.ecx = 0;
    for (;;)
    {
        cpu.edx = cpu.ecx;
        cpu.eax = cpu.ebx;
        if (!direct(app, cpu, qfindindex))
            return;
        if (cpu.eax == 0)
            break;
        if (!direct(app, cpu, connClose))
            return;
    }
    cpu.esi = kConnectionsQueue;
    cpu.edi = kConnectC;
    cpu.ebp = kRestoreName;
    cpu.ebx = 0;
    for (;;)
    {
        cpu.edx = cpu.ebx;
        cpu.eax = cpu.esi;
        if (!direct(app, cpu, qfindindex))
            return;
        cpu.ecx = cpu.eax;
        if (cpu.eax == 0)
            return leave();
        if (!direct(app, cpu, connClose))
            return;
        cpu.edx = cpu.ecx;
        cpu.eax = cpu.esi;
        if (!direct(app, cpu, qremove))
            return;
        if (cpu.eax == 0)
            continue;
        push(app, cpu, cpu.ecx);
        cpu.eax = 0xdb;
        put(app, kWhereFile, cpu.edi);
        push(app, cpu, kNotRemoved);
        put(app, kWhereFunction, cpu.ebp);
        put(app, kWhereLine, cpu.eax);
        if (!error(app, cpu, 2))
            return;
    }
}

/* 0x4f5310: a packet -- edx it, ebx its length -- sent on the connection
 * eax through its layers (layerSendPacket, one piece). */
void connSend(win32::WinApplication* app, x86::CPU& cpu)
{
    cpu.esp -= 8;
    put(app, cpu.esp + 4, cpu.edx);
    put(app, cpu.esp, cpu.ebx);
    cpu.ebx = cpu.esp;
    cpu.edx = 1;
    if (!direct(app, cpu, layerSendPacket))
        return;
    cpu.esp += 8;
    cpu.esp += 4;
}

/* 0x4f5330: the connection eax closed, if it is one and open: its close
 * (+0x10 of its functions); closed, one that counts (its functions' +0xc)
 * makes one open connection fewer, the last taking the connections' task
 * (0x4f5110) off (0x4f29b0); its layers freed (layerFree).  What the close
 * gave back, or 0. */
void connClose(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.edx);
    cpu.edx = cpu.eax;
    if (cpu.eax == 0 || at(app, cpu.eax + kConnectionOpen) == 0)
    {
        cpu.eax = 0;
        cpu.edx = pop(app, cpu);
        cpu.esp += 4;
        return;
    }
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.ecx);
    cpu.ecx = at(app, cpu.eax + 4);
    if (!byAddress(app, cpu, at(app, cpu.ecx + 0x10)))
        return;
    cpu.ecx = cpu.eax;
    if (cpu.eax != 0)
    {
        cpu.eax = at(app, cpu.edx + 4);
        if (at(app, cpu.eax + 0xc) != 0)
        {
            cpu.esi = at(app, kOpenCount);
            if (cpu.esi != 0)
            {
                cpu.edi = cpu.esi - 1;
                put(app, kOpenCount, cpu.edi);
                if (cpu.edi == 0)
                {
                    cpu.eax = kConnectionTask;
                    if (!byAddress(app, cpu, kRemoveTask))
                        return;
                }
            }
        }
    }
    cpu.eax = cpu.edx;
    if (!direct(app, cpu, layerFree))
        return;
    cpu.eax = cpu.ecx;
    cpu.ecx = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.edi = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x50dc00: the element edx after the first of the queue whose first
 * element's address is at eax, or 0 past the last (the list walked as qnth
 * would). */
void qnth(win32::WinApplication* app, x86::CPU& cpu)
{
    cpu.eax = at(app, cpu.eax);
    if (cpu.eax != 0)
    {
        for (;;)
        {
            --cpu.edx;
            if (cpu.edx == 0xffffffff)
                break;
            cpu.eax = at(app, cpu.eax);
            if (cpu.eax == 0)
                break;
        }
    }
    cpu.esp += 4;
}

/* 0x50dc20: the element edx taken out of the queue eax, its lock not taken
 * (qremove's): the count one fewer, the first or the last moved past it;
 * taken out, its next 0 and the queue's flag 1 (changed) set.  1 if it was
 * there, else 0. */
void qunlink(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    const auto leave = [&] {
        if (cpu.ebx != 0)
        {
            put(app, cpu.edx, 0);
            putByte(app, cpu.ecx + 4, byte(app, cpu.ecx + 4) | 1);
        }
        cpu.eax = cpu.ebx;
        cpu.ebp = pop(app, cpu);
        cpu.edi = pop(app, cpu);
        cpu.esi = pop(app, cpu);
        cpu.ecx = pop(app, cpu);
        cpu.ebx = pop(app, cpu);
        cpu.esp += 4;
    };
    cpu.ecx = cpu.eax;
    cpu.ebx = 0;
    if (cpu.edx == 0)
        return leave();
    cpu.esi = at(app, cpu.eax);
    if (cpu.esi == 0)
        return leave();
    cpu.edi = at(app, cpu.eax + 8);
    if (cpu.edx == cpu.edi)
    {
        cpu.ebx = 1;
        cpu.eax = cpu.esi;
        cpu.eax -= cpu.ebx;
        cpu.esi = at(app, cpu.ecx + 0xc);
        put(app, cpu.ecx, cpu.eax);
        if (cpu.edi == cpu.esi)
        {
            put(app, cpu.ecx + 8, 0);
            cpu.eax = at(app, cpu.ecx + 8);
            put(app, cpu.ecx + 0xc, cpu.eax);
        }
        else
        {
            cpu.eax = at(app, cpu.edi);
            put(app, cpu.ecx + 8, cpu.eax);
        }
        return leave();
    }
    cpu.ebp = at(app, cpu.edi);
    cpu.eax = cpu.edi;
    if (cpu.ebp != 0)
    {
        while (cpu.edx != at(app, cpu.eax))
        {
            cpu.eax = at(app, cpu.eax);
            if (at(app, cpu.eax) == 0)
                break;
        }
    }
    cpu.esi = at(app, cpu.eax);
    if (cpu.esi != 0 && cpu.edx == cpu.esi)
    {
        cpu.ebx = 1;
        put(app, cpu.ecx, at(app, cpu.ecx) - cpu.ebx);
        cpu.esi = at(app, cpu.esi);
        put(app, cpu.eax, cpu.esi);
        if (cpu.edx == at(app, cpu.ecx + 0xc))
            put(app, cpu.ecx + 0xc, cpu.eax);
    }
    leave();
}

namespace
{

/* What the queues report of a queue eax uninitialized: its address, the
 * function's name and Error's three words. */
bool uninitialized(win32::WinApplication* app, x86::CPU& cpu, reg32 name, reg32 line, reg32& nameReg,
                   reg32& fileReg, reg32& lineReg)
{
    push(app, cpu, cpu.eax);
    nameReg = name;
    fileReg = kQueueC;
    push(app, cpu, nameReg);
    lineReg = line;
    put(app, kWhereFile, fileReg);
    push(app, cpu, kUninitialized);
    put(app, kWhereFunction, nameReg);
    put(app, kWhereLine, lineReg);
    return error(app, cpu, 3);
}

}  // namespace

/* 0x50dde0, EA's qfree: the queue eax's lock let go -- freed (0x4eb360) if it
 * is its own (flag 2) -- and 0; an Error for a queue uninitialized. */
void qfree(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.edx);
    cpu.edx = cpu.eax;
    if (at(app, cpu.eax + 0x18) == 0)
    {
        push(app, cpu, cpu.edi);
        push(app, cpu, cpu.esi);
        push(app, cpu, cpu.ebx);
        if (!uninitialized(app, cpu, kQfreeName, 0xf0, cpu.esi, cpu.ebx, cpu.edi))
            return;
        cpu.ebx = pop(app, cpu);
        cpu.esi = pop(app, cpu);
        cpu.edi = pop(app, cpu);
    }
    if ((byte(app, cpu.edx + 4) & 2) != 0)
    {
        cpu.eax = at(app, cpu.edx + 0x18);
        if (!byAddress(app, cpu, kFreeLock))
            return;
    }
    put(app, cpu.edx + 0x18, 0);
    cpu.edx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x50e150, EA's qremove: the element edx taken out of the queue eax under
 * its lock (qunlink); 1 if it was there.  Asked for none, what eax gives
 * back is edi as the caller had it. */
void qremove(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.ebx = cpu.eax;
    cpu.esi = cpu.edx;
    cpu.edx = at(app, cpu.eax + 0x18);
    push(app, cpu, cpu.edx);
    if (!windows(app, cpu, kEnterCriticalSection))
        return;
    if (at(app, cpu.ebx + 0x18) == 0)
    {
        push(app, cpu, cpu.ebx);
        cpu.eax = kQremoveName;
        cpu.ebp = kQueueC;
        push(app, cpu, cpu.eax);
        cpu.edx = 0x21c;
        put(app, kWhereFile, cpu.ebp);
        push(app, cpu, kUninitialized);
        put(app, kWhereFunction, cpu.eax);
        put(app, kWhereLine, cpu.edx);
        if (!error(app, cpu, 3))
            return;
    }
    if (cpu.esi != 0)
    {
        cpu.edx = cpu.esi;
        cpu.eax = cpu.ebx;
        if (!direct(app, cpu, qunlink))
            return;
        cpu.edi = cpu.eax;
    }
    cpu.ecx = at(app, cpu.ebx + 0x18);
    push(app, cpu, cpu.ecx);
    if (!windows(app, cpu, kLeaveCriticalSection))
        return;
    cpu.eax = cpu.edi;
    cpu.ebp = pop(app, cpu);
    cpu.edi = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x50e1d0, EA's qlength: how many elements the queue eax holds; an Error
 * for a queue uninitialized. */
void qlength(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.edx);
    cpu.edx = cpu.eax;
    if (at(app, cpu.eax + 0x18) == 0)
    {
        push(app, cpu, cpu.edi);
        push(app, cpu, cpu.esi);
        push(app, cpu, cpu.ebx);
        if (!uninitialized(app, cpu, kQlengthName, 0x245, cpu.esi, cpu.ebx, cpu.edi))
            return;
        cpu.ebx = pop(app, cpu);
        cpu.esi = pop(app, cpu);
        cpu.edi = pop(app, cpu);
    }
    cpu.eax = at(app, cpu.edx);
    cpu.edx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x50e220, EA's qposition: under the queue eax's lock, the index of the
 * element edx, or -1.  A queue with a priority's function (+0x10, its
 * argument +0x14) is looked through only as far as the elements whose
 * priority is not above edx's. */
void qposition(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.esp -= 4;
    const reg32 f = cpu.esp;
    cpu.edi = cpu.eax;
    cpu.ebp = cpu.edx;
    cpu.edx = at(app, cpu.eax + 0x18);
    push(app, cpu, cpu.edx);
    if (!windows(app, cpu, kEnterCriticalSection))
        return;
    cpu.ecx = at(app, cpu.edi + 0x18);
    cpu.ebx = 0;
    if (cpu.ecx == 0)
    {
        push(app, cpu, cpu.edi);
        cpu.eax = kQpositionName;
        cpu.esi = kQueueC;
        push(app, cpu, cpu.eax);
        cpu.edx = 0x271;
        put(app, kWhereFile, cpu.esi);
        push(app, cpu, kUninitialized);
        put(app, kWhereFunction, cpu.eax);
        put(app, kWhereLine, cpu.edx);
        if (!error(app, cpu, 3))
            return;
    }
    bool found = false;
    if (cpu.ebp != 0)
    {
        cpu.esi = at(app, cpu.edi + 0x10);
        cpu.ecx = at(app, cpu.edi + 8);
        if (cpu.esi != 0)
        {
            cpu.eax = cpu.ebp;
            cpu.edx = at(app, cpu.edi + 0x14);
            if (!byAddress(app, cpu, cpu.esi))
                return;
        }
        else
            cpu.eax = 0;
        put(app, f, cpu.eax);
        while (cpu.ecx != 0 && cpu.ecx != cpu.ebp)
        {
            if (cpu.esi != 0)
            {
                cpu.eax = cpu.ecx;
                cpu.edx = at(app, cpu.edi + 0x14);
                if (!byAddress(app, cpu, cpu.esi))
                    return;
                if (cpu.eax > at(app, f))
                    break;
            }
            cpu.ecx = at(app, cpu.ecx);
            ++cpu.ebx;
        }
        found = cpu.ecx == cpu.ebp;
    }
    if (!found)
        cpu.ebx = 0xffffffff;
    cpu.ecx = at(app, cpu.edi + 0x18);
    push(app, cpu, cpu.ecx);
    if (!windows(app, cpu, kLeaveCriticalSection))
        return;
    cpu.eax = cpu.ebx;
    cpu.esp += 4;
    cpu.ebp = pop(app, cpu);
    cpu.edi = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x50e470, EA's qfindindex: under the queue eax's lock, its element edx
 * (qnth past the first), or 0. */
void qfindindex(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.ebp);
    cpu.ebx = cpu.eax;
    cpu.esi = cpu.edx;
    cpu.edx = at(app, cpu.eax + 0x18);
    push(app, cpu, cpu.edx);
    if (!windows(app, cpu, kEnterCriticalSection))
        return;
    if (at(app, cpu.ebx + 0x18) == 0)
    {
        push(app, cpu, cpu.edi);
        push(app, cpu, cpu.ebx);
        cpu.ebp = kQfindindexName;
        cpu.edi = kQueueC;
        push(app, cpu, cpu.ebp);
        cpu.eax = 0x30f;
        put(app, kWhereFile, cpu.edi);
        push(app, cpu, kUninitialized);
        put(app, kWhereFunction, cpu.ebp);
        put(app, kWhereLine, cpu.eax);
        if (!error(app, cpu, 3))
            return;
        cpu.edi = pop(app, cpu);
    }
    cpu.edx = at(app, cpu.ebx + 8);
    if (cpu.edx == 0)
        cpu.esi = 0;
    else if (cpu.esi != 0)
    {
        cpu.edx = cpu.esi - 1;
        cpu.eax = at(app, cpu.ebx + 8);
        if (!direct(app, cpu, qnth))
            return;
        cpu.esi = cpu.eax;
    }
    else
        cpu.esi = cpu.edx;
    cpu.ecx = at(app, cpu.ebx + 0x18);
    push(app, cpu, cpu.ecx);
    if (!windows(app, cpu, kLeaveCriticalSection))
        return;
    cpu.eax = cpu.esi;
    cpu.ebp = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x5123b0, EA's LAYER_send: the edx pieces at ebx ({length, address} each)
 * gathered into one block ('FILTER', the game's allocation) and sent by the
 * connection eax's own send (+8 of its functions: the block, its length);
 * the block freed, and what the send gave back. */
void layerSend(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.esp -= 0xc;
    const reg32 f = cpu.esp;
    put(app, f + 4, cpu.eax);
    put(app, f + 8, cpu.edx);
    cpu.ecx = cpu.ebx;
    cpu.eax = 0;
    cpu.ebp = 0;
    if (sreg32(cpu.edx) > 0)
    {
        cpu.edi = at(app, f + 8);
        cpu.esi = cpu.ebx;
        do
        {
            cpu.ebx = at(app, cpu.esi);
            cpu.esi += 8;
            ++cpu.eax;
            cpu.ebp += cpu.ebx;
        } while (sreg32(cpu.eax) < sreg32(cpu.edi));
    }
    cpu.eax = kLayerC;
    cpu.edx = kLayerSendName;
    cpu.ebx = 0x2d;
    put(app, kWhereFile, cpu.eax);
    put(app, kWhereFunction, cpu.edx);
    put(app, kWhereLine, cpu.ebx);
    cpu.eax = kFilterName;
    cpu.edx = cpu.ebp;
    cpu.ebx = 0;
    if (!byAddress(app, cpu, kAllocate))
        return;
    put(app, f, cpu.eax);
    cpu.esi = cpu.eax;
    cpu.eax = at(app, f + 8);
    cpu.edi = 0;
    if (sreg32(cpu.eax) > 0)
    {
        do
        {
            cpu.edx = cpu.esi;
            cpu.ebx = at(app, cpu.ecx);
            cpu.eax = at(app, cpu.ecx + 4);
            cpu.ecx += 8;
            if (!byAddress(app, cpu, kMoveMemory))
                return;
            ++cpu.edi;
            cpu.edx = at(app, cpu.ecx - 8);
            cpu.ebx = at(app, f + 8);
            cpu.esi += cpu.edx;
        } while (sreg32(cpu.edi) < sreg32(cpu.ebx));
    }
    cpu.ecx = at(app, f + 4);
    cpu.edx = at(app, f);
    cpu.ecx = at(app, cpu.ecx + 4);
    cpu.eax = at(app, f + 4);
    cpu.ebx = cpu.ebp;
    if (!byAddress(app, cpu, at(app, cpu.ecx + 8)))
        return;
    cpu.ecx = cpu.eax;
    cpu.eax = at(app, f);
    if (!byAddress(app, cpu, kFree))
        return;
    cpu.eax = cpu.ecx;
    cpu.esp += 0xc;
    cpu.ebp = pop(app, cpu);
    cpu.edi = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x512530, EA's LAYER_callpacker: the packet -- ebx pieces at ecx -- on
 * the connection eax handed to layer edx of the queue on the stack (its
 * index noted at the queue's +0x1c): its packer (+4, with its data +0xc,
 * the queue on the stack) -- an Error, and the packer read from an element
 * 0, when qfindindex finds none.  Past the layers, sent (layerSend).  The
 * stack's word taken off. */
void layerCallPacker(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.esi = cpu.eax;
    cpu.edi = cpu.ebx;
    cpu.ebx = at(app, cpu.esp + 0x10);
    bool layer = false;
    if (sreg32(cpu.edx) >= 0)
    {
        cpu.eax = cpu.ebx;
        if (!direct(app, cpu, qlength))
            return;
        layer = cpu.edx < cpu.eax;
    }
    if (layer)
    {
        cpu.eax = cpu.ebx;
        put(app, cpu.ebx + 0x1c, cpu.edx);
        if (!direct(app, cpu, qfindindex))
            return;
        cpu.ebp = cpu.eax;
        if (cpu.eax == 0)
        {
            cpu.edx = kLayerC;
            cpu.eax = kCallPackerName;
            push(app, cpu, kFindFailed);
            put(app, kWhereFile, cpu.edx);
            cpu.edx = 0x63;
            put(app, kWhereFunction, cpu.eax);
            put(app, kWhereLine, cpu.edx);
            if (!error(app, cpu, 1))
                return;
        }
        push(app, cpu, cpu.ebx);
        cpu.eax = cpu.esi;
        cpu.edx = at(app, cpu.ebp + 0xc);
        cpu.ebx = cpu.edi;
        if (!byAddress(app, cpu, at(app, cpu.ebp + 4)))
            return;
    }
    else
    {
        cpu.ebx = cpu.ecx;
        cpu.edx = cpu.edi;
        cpu.eax = cpu.esi;
        if (!direct(app, cpu, layerSend))
            return;
    }
    cpu.ebp = pop(app, cpu);
    cpu.edi = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.esp += 4 + 4;
}

/* 0x512630: the packet -- edx pieces at ebx -- on the connection eax handed
 * to the top layer of the queue ecx (layerCallPacker, its last). */
void layerPackFromTop(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.esi);
    cpu.esi = cpu.eax;
    cpu.eax = cpu.ecx;
    push(app, cpu, cpu.ecx);
    if (!direct(app, cpu, qlength))
        return;
    --cpu.eax;
    cpu.ecx = cpu.ebx;
    cpu.ebx = cpu.edx;
    cpu.edx = cpu.eax;
    cpu.eax = cpu.esi;
    if (!direct(app, cpu, layerCallPacker))
        return;
    cpu.esi = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x5126c0: the connection eax's queue of layers (+0x30), if any, let go
 * (qfree), freed and forgotten. */
void layerFree(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    cpu.edx = cpu.eax;
    cpu.ecx = at(app, cpu.eax + 0x30);
    if (cpu.ecx != 0)
    {
        cpu.eax = cpu.ecx;
        if (!direct(app, cpu, qfree))
            return;
        cpu.eax = at(app, cpu.edx + 0x30);
        if (!byAddress(app, cpu, kFree))
            return;
        put(app, cpu.edx + 0x30, 0);
    }
    cpu.edx = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x512770: the packet -- edx pieces at ebx -- sent on the connection eax
 * if it is one and up (+0x24), down its layers (layerPackFromTop); else 0. */
void layerSendPacket(win32::WinApplication* app, x86::CPU& cpu)
{
    if (cpu.eax == 0 || at(app, cpu.eax + kConnectionUp) == 0)
    {
        cpu.eax = 0;
        cpu.esp += 4;
        return;
    }
    push(app, cpu, cpu.ecx);
    cpu.ecx = at(app, cpu.eax + 0x30);
    if (!direct(app, cpu, layerPackFromTop))
        return;
    cpu.ecx = pop(app, cpu);
    cpu.esp += 4;
}

namespace
{

/* mov ecx, n; mov eax, [address]; bswap eax; neg ecx; lea ecx, [ecx*8 +
 * 0x20]; shr eax, cl: the n bytes at address, big-endian; ecx the shift. */
void bigEndian(win32::WinApplication* app, x86::CPU& cpu, reg32 address, reg32 n)
{
    cpu.ecx = n;
    cpu.eax = at(app, address);
    cpu.eax = (cpu.eax >> 24) | (cpu.eax >> 8 & 0xff00) | (cpu.eax << 8 & 0xff0000) | (cpu.eax << 24);
    cpu.ecx = 0 - cpu.ecx;
    cpu.ecx = cpu.ecx * 8 + 0x20;
    cpu.eax >>= cpu.cl & 31;
}

}  // namespace

/* 0x510110: EA's runs unpacked (0x4afb; 0x4b31 with a 16-bit length) from
 * eax to edx; the length unpacked, as the header says.  Each code byte: its
 * low 6 bits a count, its top 2 what of: 0 bytes copied, 1 a byte given
 * filled, 2 the last byte filled again (0 before any), 3 a byte given and
 * then nibbles, two to a byte, each under its high nibble.  The fills by the
 * game's memset (0x4e0640); the run's table (0x510100) followed by its
 * targets. */
void runUnpack(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.esp -= 0x14;
    const reg32 f = cpu.esp;
    // The frame: where it reads, what is left, the length, where it writes,
    // the byte filled.
    constexpr reg32 kIn = 0, kTotal = 4, kLeft = 8, kOut = 0xc, kFill = 0x10;
    cpu.ebp = cpu.eax;
    cpu.ah = 0;
    cpu.ecx = 2;
    putByte(app, f + kFill, cpu.ah);
    cpu.eax = cpu.ebp;
    put(app, f + kOut, cpu.edx);
    bigEndian(app, cpu, cpu.eax, 2);
    cpu.edx = cpu.eax;
    cpu.eax = cpu.ebp + 2;
    if (cpu.edx == 0x4b31)
    {
        bigEndian(app, cpu, cpu.eax, 2);
        cpu.ebp += 4;
    }
    else
    {
        bigEndian(app, cpu, cpu.eax, 3);
        cpu.ebp += 5;
    }
    put(app, f + kLeft, cpu.eax);
    put(app, f + kIn, cpu.ebp);
    cpu.eax = at(app, f + kLeft);
    put(app, f + kTotal, cpu.eax);
    if (sreg32(cpu.eax) > 0)
    {
        do
        {
            cpu.eax = at(app, f + kIn);
            cpu.al = byte(app, cpu.eax);
            cpu.ah = cpu.al;
            cpu.ah &= 0x3f;
            cpu.ebp = cpu.ah;
            cpu.ebx = at(app, f + kIn);
            cpu.eax &= 0xff;
            ++cpu.ebx;
            cpu.eax = reg32(sreg32(cpu.eax) >> 6);
            put(app, f + kIn, cpu.ebx);
            if (cpu.eax > 3)
                continue;
            static const reg32 targets[] = {0x51019d, 0x5101ff, 0x51020b, 0x510232};
            static_assert(sizeof targets == 0x10, "the run's table at 0x510100");
            switch (targets[cpu.eax])
            {
            case 0x51019d:
                cpu.edi = at(app, f + kOut);
                cpu.ecx = cpu.ebp;
                cpu.esi = cpu.ebx;
                cpu.edx = at(app, f + kLeft);
                copyBytes(app, cpu);
                cpu.eax = at(app, f + kOut);
                cpu.edi = cpu.ebx + cpu.ebp;
                cpu.edx -= cpu.ebp;
                put(app, f + kIn, cpu.edi);
                cpu.eax += cpu.ebp;
                put(app, f + kLeft, cpu.edx);
                put(app, f + kOut, cpu.eax);
                break;
            case 0x5101ff:
                cpu.ecx = cpu.ebx + 1;
                cpu.al = byte(app, cpu.ebx);
                put(app, f + kIn, cpu.ecx);
                putByte(app, f + kFill, cpu.al);
                [[fallthrough]];
            case 0x51020b:
                cpu.eax = at(app, f + kOut);
                cpu.edx = 0;
                cpu.ebx = cpu.ebp;
                cpu.dl = byte(app, f + kFill);
                cpu.esi = at(app, f + kLeft);
                if (!byAddress(app, cpu, kMemset))
                    return;
                cpu.ebx = at(app, f + kOut);
                cpu.esi -= cpu.ebp;
                cpu.ebx += cpu.ebp;
                put(app, f + kLeft, cpu.esi);
                put(app, f + kOut, cpu.ebx);
                break;
            case 0x510232:
                cpu.edx = at(app, f + kOut);
                cpu.esi = cpu.ebx + 1;
                cpu.ah = byte(app, cpu.ebx);
                put(app, f + kIn, cpu.esi);
                cpu.edi = cpu.edx + 1;
                putByte(app, cpu.edx, cpu.ah);
                cpu.edx = at(app, f + kLeft);
                cpu.ah &= 0xf0;
                put(app, f + kOut, cpu.edi);
                cpu.edx -= cpu.ebp;
                --cpu.ebp;
                put(app, f + kLeft, cpu.edx);
                while (sreg32(cpu.ebp) > 0)
                {
                    cpu.edx = at(app, f + kIn);
                    cpu.al = byte(app, cpu.edx);
                    cpu.edx = 0;
                    cpu.ecx = 0;
                    cpu.dl = cpu.al;
                    cpu.cl = cpu.ah;
                    cpu.edx = reg32(sreg32(cpu.edx) >> 4);
                    cpu.edx |= cpu.ecx;
                    cpu.ecx = at(app, f + kOut);
                    cpu.ebx = at(app, f + kOut);
                    --cpu.ebp;
                    putByte(app, cpu.ecx, cpu.dl);
                    cpu.ecx = at(app, f + kIn);
                    ++cpu.ebx;
                    ++cpu.ecx;
                    put(app, f + kOut, cpu.ebx);
                    put(app, f + kIn, cpu.ecx);
                    if (sreg32(cpu.ebp) > 0)
                    {
                        cpu.al &= 0xf;
                        cpu.esi = cpu.ebx + 1;
                        --cpu.ebp;
                        cpu.al |= cpu.ah;
                        put(app, f + kOut, cpu.esi);
                        putByte(app, cpu.ebx, cpu.al);
                    }
                }
                break;
            }
        } while (sreg32(at(app, f + kLeft)) > 0);
    }
    cpu.eax = at(app, f + kTotal);
    cpu.esp += 0x14;
    cpu.ebp = pop(app, cpu);
    cpu.edi = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4;
}

namespace
{

/* lea eax, [r*4]; add eax, r; add eax, eax; mov edx, eax; shl eax, 4; add
 * eax, edx; mov edx, eax; shl eax, 8; add eax, edx: r * 0xaaaa -- two
 * thirds of a channel, 16 bits up -- edx left r * 0xaa. */
void twoThirds(x86::CPU& cpu, reg32 r)
{
    cpu.eax = r * 4;
    cpu.eax += r;
    cpu.eax += cpu.eax;
    cpu.edx = cpu.eax;
    cpu.eax <<= 4;
    cpu.eax += cpu.edx;
    cpu.edx = cpu.eax;
    cpu.eax <<= 8;
    cpu.eax += cpu.edx;
}

/* A row of the block: the byte at `codes` of 2-bit indices into the frame's
 * four colours, 4 pixels at esi. */
void dxtRow(win32::WinApplication* app, x86::CPU& cpu, reg32 f, reg32 codes, reg32 at)
{
    cpu.eax = 0;
    cpu.al = byte(app, codes);
    cpu.edx = cpu.eax;
    cpu.edx &= 3;
    cpu.dx = word16(app, f + cpu.edx * 2);
    putWord16(app, at, cpu.dx);
    cpu.edx = cpu.eax;
    cpu.edx >>= 2;
    cpu.edx &= 3;
    cpu.dx = word16(app, f + cpu.edx * 2);
    putWord16(app, at + 2, cpu.dx);
    cpu.edx = cpu.eax;
    cpu.edx >>= 4;
    cpu.edx &= 3;
    cpu.dx = word16(app, f + cpu.edx * 2);
    cpu.eax >>= 6;
    putWord16(app, at + 4, cpu.dx);
    cpu.ax = word16(app, f + cpu.eax * 2);
    putWord16(app, at + 6, cpu.ax);
}

}  // namespace

/* 0x510420: a DXT1 block at ebx unpacked to 4 rows of 4 16-bit pixels at
 * eax, edx bytes apart: its two colours (5-6-5), and between them two
 * thirds and a third of the way -- or, with the first not above the
 * second, half way and 0. */
void dxtBlock(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.esp -= 0x20;
    const reg32 f = cpu.esp;
    // The frame: the four colours; the channels -- the first's green, blue,
    // red, the second's red, green, blue in the order the code keeps them.
    constexpr reg32 kColours = 0, kSum = 8, kBlue1 = 0xc, kRed1 = 0x10, kRed0 = 0x14, kGreen0 = 0x18;
    constexpr reg32 kBlue0 = 0x1c;
    cpu.esi = cpu.eax;
    cpu.edi = cpu.edx;
    cpu.ecx = 2;
    cpu.eax = cpu.ebx;
    cpu.eax = at(app, cpu.ecx + cpu.eax - 4);
    cpu.ecx = 0 - cpu.ecx;
    cpu.ecx = cpu.ecx * 8 + 0x20;
    cpu.eax >>= cpu.cl & 31;
    cpu.ecx = 2;
    cpu.edx = cpu.eax;
    putWord16(app, f + kColours, cpu.ax);
    cpu.eax = cpu.ebx + 2;
    cpu.eax = at(app, cpu.ecx + cpu.eax - 4);
    cpu.ecx = 0 - cpu.ecx;
    cpu.ecx = cpu.ecx * 8 + 0x20;
    cpu.eax >>= cpu.cl & 31;
    cpu.ebp = cpu.edx;
    putWord16(app, f + kColours + 2, cpu.ax);
    cpu.ecx = cpu.eax;
    cpu.ebp &= 0x7e0;
    cpu.ecx &= 0x1f;
    put(app, f + kGreen0, cpu.ebp);
    put(app, f + kBlue1, cpu.ecx);
    cpu.ebp = cpu.eax;
    cpu.ecx = cpu.edx;
    cpu.ebp &= 0xf800;
    cpu.ecx &= 0x1f;
    put(app, f + kRed1, cpu.ebp);
    put(app, f + kBlue0, cpu.ecx);
    cpu.ebp = cpu.edx;
    cpu.ecx = cpu.eax;
    cpu.ebp &= 0xf800;
    cpu.ecx &= 0x7e0;
    put(app, f + kRed0, cpu.ebp);
    if (cpu.edx > cpu.eax)
    {
        // Two thirds of the first and a third of the second, then the other
        // way round.
        twoThirds(cpu, cpu.ebp);
        cpu.ebp = at(app, f + kRed1) * 0x5556;
        cpu.ebp += cpu.eax;
        twoThirds(cpu, at(app, f + kGreen0));
        put(app, f + kSum, cpu.eax);
        cpu.eax = cpu.ecx * 0x5556;
        cpu.eax += at(app, f + kSum);
        cpu.ebp >>= 0x10;
        cpu.eax >>= 0x10;
        cpu.ebp &= 0xf800;
        cpu.eax &= 0x7e0;
        cpu.edx = at(app, f + kBlue0);
        cpu.ebp |= cpu.eax;
        twoThirds(cpu, cpu.edx);
        cpu.edx = at(app, f + kBlue1) * 0x5556;
        cpu.eax += cpu.edx;
        cpu.eax >>= 0x10;
        cpu.eax &= 0x1f;
        cpu.eax |= cpu.ebp;
        putWord16(app, f + kColours + 4, cpu.ax);
        cpu.ebp = at(app, f + kRed0) * 0x5556;
        twoThirds(cpu, at(app, f + kRed1));
        cpu.edx = at(app, f + kGreen0);
        cpu.eax += cpu.ebp;
        cpu.ebp = cpu.edx * 0x5556;
        cpu.eax >>= 0x10;
        cpu.eax &= 0xf800;
        put(app, f + kSum, cpu.eax);
        twoThirds(cpu, cpu.ecx);
        cpu.eax += cpu.ebp;
        cpu.eax >>= 0x10;
        cpu.ecx = at(app, f + kSum);
        cpu.eax &= 0x7e0;
        cpu.ecx |= cpu.eax;
        cpu.ebp = at(app, f + kBlue0) * 0x5556;
        twoThirds(cpu, at(app, f + kBlue1));
        cpu.eax += cpu.ebp;
        cpu.eax >>= 0x10;
        cpu.eax &= 0x1f;
        cpu.eax |= cpu.ecx;
        putWord16(app, f + kColours + 6, cpu.ax);
    }
    else
    {
        // Half way, and 0.
        cpu.eax = at(app, f + kRed1);
        cpu.edx = cpu.ebp;
        cpu.eax <<= 0xf;
        cpu.edx <<= 0xf;
        cpu.edx += cpu.eax;
        cpu.eax = at(app, f + kGreen0);
        cpu.ecx <<= 0xf;
        cpu.eax <<= 0xf;
        cpu.edx >>= 0x10;
        cpu.eax += cpu.ecx;
        cpu.edx &= 0xf800;
        cpu.eax >>= 0x10;
        cpu.ecx = cpu.edx;
        cpu.eax &= 0x7e0;
        cpu.edx = at(app, f + kBlue0);
        cpu.ecx |= cpu.eax;
        cpu.eax = at(app, f + kBlue1);
        cpu.edx <<= 0xf;
        cpu.eax <<= 0xf;
        cpu.eax += cpu.edx;
        cpu.eax >>= 0x10;
        cpu.eax &= 0x1f;
        cpu.edx = 0;
        cpu.eax |= cpu.ecx;
        putWord16(app, f + kColours + 6, cpu.dx);
        putWord16(app, f + kColours + 4, cpu.ax);
    }
    dxtRow(app, cpu, f, cpu.ebx + 4, cpu.esi);
    cpu.esi += cpu.edi;
    dxtRow(app, cpu, f, cpu.ebx + 5, cpu.esi);
    cpu.esi += cpu.edi;
    dxtRow(app, cpu, f, cpu.ebx + 6, cpu.esi);
    dxtRow(app, cpu, f, cpu.ebx + 7, cpu.edi + cpu.esi);
    cpu.esp += 0x20;
    cpu.ebp = pop(app, cpu);
    cpu.edi = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x510760: EA's DXT1 image (0x18fb) unpacked from eax to edx: its length
 * unpacked (3 bytes, big-endian, at +2) and its width (2 bytes at +6), the
 * blocks after them a row of blocks at a time (dxtBlock).  With ebx 0 only
 * the length; the length either way. */
void dxtUnpack(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.esp -= 0x14;
    const reg32 f = cpu.esp;
    // The frame: a row of blocks' bytes, the rest of its 4 rows', the
    // length, the bytes so far, the width.
    constexpr reg32 kBlockRow = 0, kRowsAfter = 4, kTotal = 8, kDone = 0xc, kWidth = 0x10;
    cpu.edi = cpu.eax;
    bigEndian(app, cpu, cpu.eax + 2, 3);
    cpu.ecx = 2;
    cpu.ebp = cpu.eax;
    put(app, f + kTotal, cpu.eax);
    cpu.eax = cpu.edi + 6;
    cpu.esi = cpu.edx;
    bigEndian(app, cpu, cpu.eax, 2);
    put(app, f + kWidth, cpu.eax);
    if (cpu.ebx != 0)
    {
        cpu.edx = 0;
        cpu.edi += 8;
        put(app, f + kDone, cpu.edx);
        if (sreg32(cpu.ebp) > 0)
        {
            cpu.ebp = cpu.eax + cpu.eax;
            cpu.ecx = cpu.eax * 4;
            cpu.ecx -= cpu.eax;
            cpu.ecx += cpu.ecx;
            cpu.eax <<= 3;
            put(app, f + kRowsAfter, cpu.ecx);
            put(app, f + kBlockRow, cpu.eax);
            do
            {
                cpu.ebx = at(app, f + kWidth);
                cpu.ecx = 0;
                if (sreg32(cpu.ebx) > 0)
                {
                    do
                    {
                        cpu.ebx = cpu.edi;
                        cpu.edx = cpu.ebp;
                        cpu.eax = cpu.esi;
                        if (!direct(app, cpu, dxtBlock))
                            return;
                        cpu.ecx += 4;
                        cpu.eax = at(app, f + kWidth);
                        cpu.esi += 8;
                        cpu.edi += 8;
                    } while (sreg32(cpu.ecx) < sreg32(cpu.eax));
                }
                cpu.ecx = at(app, f + kRowsAfter);
                cpu.eax = at(app, f + kBlockRow);
                cpu.ebx = at(app, f + kDone);
                cpu.edx = at(app, f + kTotal);
                cpu.ebx += cpu.eax;
                cpu.esi += cpu.ecx;
                put(app, f + kDone, cpu.ebx);
            } while (sreg32(cpu.ebx) < sreg32(cpu.edx));
        }
    }
    cpu.eax = at(app, f + kTotal);
    cpu.esp += 0x14;
    cpu.ebp = pop(app, cpu);
    cpu.edi = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x510820: the byte al written out ([0xa0b030] on), or -- its kind
 * ([0xa0b040]) not 0 -- the pair it stands for: its first byte expanded
 * ([0xa0b034]) and then its second ([0xa0b03c]). */
void pairExpand(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    for (;;)
    {
        cpu.edx = 0;
        cpu.ecx = at(app, kPairKind);
        cpu.dl = cpu.al;
        if (byte(app, cpu.ecx + cpu.edx) == 0)
            break;
        cpu.eax = at(app, kPairLeft);
        cpu.al = byte(app, cpu.edx + cpu.eax);
        cpu.eax &= 0xff;
        if (!direct(app, cpu, pairExpand))
            return;
        cpu.eax = at(app, kPairRight);
        cpu.al = byte(app, cpu.edx + cpu.eax);
        cpu.eax &= 0xff;
    }
    cpu.edx = at(app, kPairOut);
    ++cpu.edx;
    putByte(app, cpu.edx - 1, cpu.al);
    put(app, kPairOut, cpu.edx);
    cpu.edx = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x510870: EA's byte pairs (0x46fb; 0x47fb with 3 bytes more) unpacked
 * from eax to edx; the length unpacked, as the header says (0 for eax 0).
 * After the length: the escape, the pairs' count and each pair's byte and
 * its two (into tables in the frame, their addresses at 0xa0b034 to
 * 0xa0b040); then bytes -- one of no pair as it is, a pair's expanded
 * (pairExpand), the escape and the byte after it as that byte, the escape
 * and 0 the end.  Where it read to is left at 0xa0b038. */
void pairUnpack(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.ebp);
    cpu.esp -= 0x304;
    const reg32 f = cpu.esp;
    // The frame: the pairs' first bytes, their second, the bytes' kinds (0
    // none, 1 the escape, 0xff a pair), the length.
    constexpr reg32 kLeft = 0, kRight = 0x100, kKinds = 0x200, kTotal = 0x300;
    put(app, kPairOut, cpu.edx);
    cpu.edx = 0;
    put(app, f + kTotal, cpu.edx);
    cpu.edx = f + kKinds;
    put(app, kPairKind, cpu.edx);
    cpu.edx = f + kLeft;
    put(app, kPairLeft, cpu.edx);
    cpu.edx = f + kRight;
    cpu.ecx = cpu.eax;
    put(app, kPairRight, cpu.edx);
    if (cpu.eax != 0)
    {
        cpu.edx = 0;
        cpu.ecx = cpu.eax + 1;
        cpu.dl = byte(app, cpu.eax);
        cpu.eax = 0;
        cpu.edx <<= 8;
        cpu.al = byte(app, cpu.ecx);
        cpu.edx += cpu.eax;
        ++cpu.ecx;
        if (cpu.edx == 0x47fb)
            cpu.ecx += 3;
        push(app, cpu, cpu.esi);
        cpu.eax = 0;
        cpu.edx = 0;
        cpu.al = byte(app, cpu.ecx);
        cpu.dl = byte(app, cpu.ecx + 1);
        put(app, f + kTotal, cpu.eax);
        cpu.eax <<= 8;
        cpu.eax += cpu.edx;
        put(app, f + kTotal, cpu.eax);
        ++cpu.ecx;
        cpu.edx = at(app, f + kTotal);
        cpu.eax = 0;
        cpu.edx <<= 8;
        cpu.al = byte(app, cpu.ecx + 1);
        ++cpu.ecx;
        cpu.edx += cpu.eax;
        ++cpu.ecx;
        put(app, f + kTotal, cpu.edx);
        cpu.edx = 0;
        do
        {
            cpu.eax = at(app, kPairKind);
            cpu.esi = cpu.eax + cpu.edx;
            ++cpu.edx;
            putByte(app, cpu.esi, 0);
        } while (sreg32(cpu.edx) < 0x100);
        ++cpu.ecx;
        cpu.edx = 0;
        cpu.dl = byte(app, cpu.ecx - 1);
        ++cpu.ecx;
        putByte(app, cpu.edx + cpu.eax, 1);
        cpu.ebp = byte(app, cpu.ecx - 1);
        cpu.eax = 0;
        if (sreg32(cpu.ebp) > 0)
        {
            push(app, cpu, cpu.edi);
            push(app, cpu, cpu.ebx);
            do
            {
                cpu.edx = 0;
                cpu.ebx = at(app, kPairLeft);
                cpu.dl = byte(app, cpu.ecx);
                cpu.esi = cpu.ecx + 1;
                cpu.edi = cpu.ebx + cpu.edx;
                cpu.ecx = cpu.esi + 1;
                cpu.bl = byte(app, cpu.esi);
                cpu.esi = cpu.ecx;
                putByte(app, cpu.edi, cpu.bl);
                cpu.edi = at(app, kPairRight);
                cpu.bl = byte(app, cpu.esi);
                putByte(app, cpu.edx + cpu.edi, cpu.bl);
                cpu.ebx = at(app, kPairKind);
                ++cpu.eax;
                ++cpu.ecx;
                putByte(app, cpu.edx + cpu.ebx, 0xff);
            } while (sreg32(cpu.eax) < sreg32(cpu.ebp));
            cpu.ebx = pop(app, cpu);
            cpu.edi = pop(app, cpu);
        }
        put(app, kPairIn, cpu.ecx);
        cpu.esi = pop(app, cpu);
        for (;;)
        {
            cpu.ecx = at(app, kPairIn);
            cpu.edx = 0;
            cpu.eax = at(app, kPairKind);
            cpu.dl = byte(app, cpu.ecx);
            cpu.al = byte(app, cpu.edx + cpu.eax);
            ++cpu.ecx;
            if (cpu.al == 0)
            {
                cpu.eax = at(app, kPairOut);
                ++cpu.eax;
                put(app, kPairIn, cpu.ecx);
                putByte(app, cpu.eax - 1, cpu.dl);
                put(app, kPairOut, cpu.eax);
                continue;
            }
            put(app, kPairIn, cpu.ecx);
            if (x86::sreg8(cpu.al) < 0)
            {
                cpu.eax = at(app, kPairLeft);
                cpu.al = byte(app, cpu.edx + cpu.eax);
                cpu.eax &= 0xff;
                if (!direct(app, cpu, pairExpand))
                    return;
                cpu.eax = at(app, kPairRight);
                cpu.al = byte(app, cpu.edx + cpu.eax);
                cpu.eax &= 0xff;
                if (!direct(app, cpu, pairExpand))
                    return;
                continue;
            }
            cpu.edx = 0;
            cpu.dl = byte(app, cpu.ecx);
            ++cpu.ecx;
            if (cpu.edx == 0)
                break;
            cpu.eax = at(app, kPairOut);
            ++cpu.eax;
            put(app, kPairIn, cpu.ecx);
            putByte(app, cpu.eax - 1, cpu.dl);
            put(app, kPairOut, cpu.eax);
        }
    }
    cpu.eax = at(app, f + kTotal);
    put(app, kPairIn, cpu.ecx);
    cpu.esp += 0x304;
    cpu.ebp = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x50ed50: EA's Huffman with runs (0x30fb, 0x32fb and 0x34fb -- each with
 * the packed length too when odd) unpacked from eax to edx, its tables read
 * first when ebx is not 0; the length unpacked, as the header says (0 for
 * eax 0).  The bits are read from the top, 16 at a time into [esp+0x534]:
 * the clue byte; how many codes of each length, from 1 bit until they fill
 * the code space; the symbols, each as how many not yet taken to skip; then
 * codes -- up to 8 bits looked up by their first byte, longer ones by the
 * limits of each length -- each a byte, or the clue's code: then a count, a
 * run of the byte before that long, or with 0 a bit: 1 the end, 0 a byte as
 * it is.  The counts are 2 + n bits after n 0s and a 1 (3 + n where the
 * next 16 bits are all 0), less 4.  0x32fb's bytes are the sums of those
 * unpacked, 0x34fb's the sums of their sums.  A 16-bit code's offset
 * ([esp+0x4c0]) is where a run's long count keeps where it reads: kept, the
 * game's own clash.  Written with its jumps, as the code goes. */
void huffUnpack(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.esp -= 0x544;
    const reg32 f = cpu.esp;
    // The frame: the symbols taken, the first byte's lookup -- its symbol and
    // its length (0x40 a longer code, 0x60 the clue's) -- the symbols in
    // their codes' order; by length (+ 4 * length) the codes' counts, their
    // limits (16 bits, left-justified), their first's offset in the symbols;
    // and the rest, as their names say.
    constexpr reg32 kUsed = 0, kLookupSymbols = 0x100, kLookupLengths = 0x200, kSymbols = 0x300, kRunSource = 0x4c0;
    constexpr reg32 kStart = 0x4c4, kType = 0x4c8, kLength = 0x4cc, kClueLength = 0x4d0, kDest = 0x4d4;
    constexpr reg32 kNextLength = 0x4d8, kLongest = 0x4dc, kSymbolIndex = 0x4e0, kTotal = 0x4e4, kLowBits = 0x4e8;
    constexpr reg32 kTableLength = 0x4ec, kLeft = 0x4f0, kSymbol = 0x4f4, kSymbolLength = 0x4f8, kSymbolAt = 0x4fc;
    constexpr reg32 kLookup = 0x500, kRun = 0x504, kRunLow = 0x508, kHighBits = 0x50c, kCountWord = 0x510;
    constexpr reg32 kRunWord = 0x514, kShift = 0x518, kLengthOffset = 0x51c, kTableOffset = 0x520;
    constexpr reg32 kTableShift = 0x524, kCountSource = 0x528, kSymbolSource = 0x52c, kSource = 0x530, kWord = 0x534;
    constexpr reg32 kBit = 0x538, kLiteral = 0x53c, kClue = 0x540;
    constexpr reg32 kTypeHigh = kType + 1;
    constexpr reg32 kCounts = 0x400, kLimits = 0x440, kOffsets = 0x480;
    put(app, f + kStart, cpu.edx);
    put(app, f + kDest, cpu.edx);
    cpu.edx = 0;
    put(app, f + kLength, cpu.edx);
    if (cpu.eax == 0)
        goto l50ffb0;
    cpu.ecx = 0;
    cpu.cl = byte(app, cpu.eax);
    cpu.dl = byte(app, cpu.eax + 0x1);
    cpu.ecx <<= 8;
    cpu.edx |= cpu.ecx;
    cpu.eax += 2;
    put(app, f + kWord, cpu.edx);
    cpu.esi = cpu.edx;
    cpu.edx = 0;
    put(app, f + kSource, cpu.eax);
    cpu.dl = byte(app, cpu.eax);
    cpu.eax = at(app, f + kWord);
    cpu.edi = 0;
    cpu.eax <<= 8;
    cpu.ecx = at(app, f + kSource);
    cpu.edx |= cpu.eax;
    cpu.esi <<= 0x10;
    put(app, f + kWord, cpu.edx);
    cpu.edx = at(app, f + kSource);
    cpu.eax = 0;
    cpu.ecx += 2;
    cpu.al = byte(app, cpu.edx + 0x1);
    cpu.edx = at(app, f + kWord);
    cpu.esi >>= 0x10;
    cpu.edx <<= 8;
    put(app, f + kType, cpu.esi);
    cpu.eax |= cpu.edx;
    put(app, f + kSource, cpu.ecx);
    put(app, f + kWord, cpu.eax);
    cpu.esi = cpu.eax;
    cpu.ah = byte(app, f + kTypeHigh);
    cpu.esi <<= 0x10;
    if ((cpu.ah & 1) != 0)
        goto l50efeb;
l50ee03:
    cpu.dl = byte(app, f + kTypeHigh);
    cpu.ebp = cpu.esi;
    cpu.edi -= 8;
    cpu.dl &= 0xfe;
    cpu.ebp >>= 0x18;
    cpu.esi <<= 8;
    putByte(app, f + kTypeHigh, cpu.dl);
    if (sreg32(cpu.edi) < 0)
        goto l50f060;
l50ee27:
    cpu.eax = cpu.esi;
    cpu.edi -= 0x10;
    cpu.eax >>= 0x10;
    cpu.esi <<= 0x10;
    put(app, f + kLength, cpu.eax);
    if (sreg32(cpu.edi) < 0)
        goto l50f0be;
l50ee41:
    cpu.eax = cpu.ebp;
    cpu.ecx = at(app, f + kLength);
    cpu.eax <<= 0x10;
    cpu.ecx |= cpu.eax;
    put(app, f + kLength, cpu.ecx);
    if (cpu.ebx != 0)
        goto l50f11c;
l50ee5e:
    cpu.eax = f + kLookupSymbols;
    cpu.ebx = f + kLookupLengths;
    put(app, f + kLookup, cpu.eax);
l50ee73:
    cpu.eax = cpu.esi;
    cpu.eax >>= 0x18;
    cpu.al = byte(app, cpu.ebx + cpu.eax);
    cpu.eax &= 0xff;
    cpu.edi -= cpu.eax;
    if (sreg32(cpu.edi) < 0)
        goto l50ef58;
l50ee8a:
    cpu.edx = cpu.esi;
    cpu.ecx = at(app, f + kLookup);
    cpu.edx >>= 0x18;
    cpu.edx += cpu.ecx;
    cpu.ah = byte(app, cpu.edx);
    cpu.cl = cpu.al;
    cpu.edx = at(app, f + kDest);
    cpu.esi <<= cpu.cl & 31;
    putByte(app, cpu.edx, cpu.ah);
    cpu.edx = cpu.esi;
    cpu.ebp = at(app, f + kDest);
    cpu.edx >>= 0x18;
    ++cpu.ebp;
    cpu.eax = cpu.ebx + cpu.edx;
    put(app, f + kDest, cpu.ebp);
    cpu.al = byte(app, cpu.eax);
    cpu.eax &= 0xff;
    cpu.edi -= cpu.eax;
    if (sreg32(cpu.edi) < 0)
        goto l50ef58;
    cpu.edx += at(app, f + kLookup);
    cpu.ah = byte(app, cpu.edx);
    cpu.cl = cpu.al;
    cpu.esi <<= cpu.cl & 31;
    cpu.edx = cpu.esi;
    ++cpu.ebp;
    cpu.edx >>= 0x18;
    putByte(app, cpu.ebp - 0x1, cpu.ah);
    cpu.eax = cpu.ebx + cpu.edx;
    put(app, f + kDest, cpu.ebp);
    cpu.al = byte(app, cpu.eax);
    cpu.eax &= 0xff;
    cpu.edi -= cpu.eax;
    if (sreg32(cpu.edi) < 0)
        goto l50ef58;
    cpu.edx += at(app, f + kLookup);
    cpu.ah = byte(app, cpu.edx);
    cpu.cl = cpu.al;
    cpu.esi <<= cpu.cl & 31;
    cpu.edx = cpu.esi;
    ++cpu.ebp;
    cpu.edx >>= 0x18;
    putByte(app, cpu.ebp - 0x1, cpu.ah);
    cpu.eax = cpu.ebx + cpu.edx;
    put(app, f + kDest, cpu.ebp);
    cpu.al = byte(app, cpu.eax);
    cpu.eax &= 0xff;
    cpu.edi -= cpu.eax;
    if (sreg32(cpu.edi) < 0)
        goto l50ef58;
    cpu.edx += at(app, f + kLookup);
    cpu.ah = byte(app, cpu.edx);
    cpu.cl = cpu.al;
    cpu.esi <<= cpu.cl & 31;
    putByte(app, cpu.ebp, cpu.ah);
    cpu.eax = cpu.esi;
    ++cpu.ebp;
    cpu.eax >>= 0x18;
    put(app, f + kDest, cpu.ebp);
    cpu.al = byte(app, cpu.ebx + cpu.eax);
    cpu.eax &= 0xff;
    cpu.edi -= cpu.eax;
    if (sreg32(cpu.edi) >= 0)
        goto l50ee8a;
l50ef58:
    cpu.edi += 0x10;
    if (sreg32(cpu.edi) < 0)
        goto l50faa5;
    cpu.eax = at(app, f + kLookup);
    cpu.esi >>= 0x18;
    cpu.edx = at(app, f + kDest);
    cpu.al = byte(app, cpu.esi + cpu.eax);
    putByte(app, cpu.edx, cpu.al);
    cpu.edx = at(app, f + kSource);
    cpu.eax = 0;
    cpu.al = byte(app, cpu.edx);
    cpu.edx = at(app, f + kWord);
    cpu.edx <<= 8;
    cpu.eax |= cpu.edx;
    put(app, f + kWord, cpu.eax);
    cpu.eax = at(app, f + kSource);
    cpu.edx = 0;
    cpu.dl = byte(app, cpu.eax + 0x1);
    cpu.eax = at(app, f + kWord);
    cpu.ecx = 0x10;
    cpu.eax <<= 8;
    cpu.ecx -= cpu.edi;
    cpu.edx |= cpu.eax;
    cpu.eax = at(app, f + kDest);
    put(app, f + kWord, cpu.edx);
    cpu.edx = at(app, f + kSource);
    ++cpu.eax;
    cpu.esi = at(app, f + kWord);
    put(app, f + kDest, cpu.eax);
    cpu.edx += 2;
    cpu.esi <<= cpu.cl & 31;
    put(app, f + kSource, cpu.edx);
    goto l50ee73;
l50efeb:
    cpu.eax = at(app, f + kWord);
    cpu.edx = 0;
    cpu.eax <<= 8;
    cpu.dl = byte(app, cpu.ecx);
    cpu.edx |= cpu.eax;
    put(app, f + kWord, cpu.edx);
    cpu.eax = 0;
    cpu.edx <<= 8;
    cpu.al = byte(app, cpu.ecx + 0x1);
    cpu.eax |= cpu.edx;
    cpu.esi = cpu.ecx + 0x2;
    put(app, f + kWord, cpu.eax);
    cpu.edx = 0;
    cpu.eax <<= 8;
    cpu.dl = byte(app, cpu.esi);
    put(app, f + kSource, cpu.esi);
    cpu.edx |= cpu.eax;
    cpu.edi = cpu.esi;
    put(app, f + kWord, cpu.edx);
    cpu.edi += 2;
    cpu.eax = at(app, f + kWord);
    cpu.edx = 0;
    cpu.eax <<= 8;
    cpu.dl = byte(app, cpu.esi + 0x1);
    put(app, f + kSource, cpu.edi);
    cpu.edx |= cpu.eax;
    cpu.edi = 8;
    cpu.esi = cpu.edx;
    put(app, f + kWord, cpu.edx);
    cpu.esi <<= 8;
    goto l50ee03;
l50f060:
    cpu.eax = at(app, f + kSource);
    cpu.edx = 0;
    cpu.dl = byte(app, cpu.eax);
    cpu.eax = at(app, f + kWord);
    cpu.eax <<= 8;
    cpu.edx |= cpu.eax;
    cpu.eax = at(app, f + kSource);
    put(app, f + kWord, cpu.edx);
    cpu.edx = 0;
    cpu.ecx = cpu.edi;
    cpu.dl = byte(app, cpu.eax + 0x1);
    cpu.eax = at(app, f + kWord);
    cpu.ecx = 0 - cpu.ecx;
    cpu.eax <<= 8;
    cpu.edi += 0x10;
    cpu.edx |= cpu.eax;
    cpu.eax = at(app, f + kSource);
    put(app, f + kWord, cpu.edx);
    cpu.esi = cpu.edx;
    cpu.eax += 2;
    cpu.esi <<= cpu.cl & 31;
    put(app, f + kSource, cpu.eax);
    goto l50ee27;
l50f0be:
    cpu.eax = at(app, f + kSource);
    cpu.edx = 0;
    cpu.dl = byte(app, cpu.eax);
    cpu.eax = at(app, f + kWord);
    cpu.eax <<= 8;
    cpu.edx |= cpu.eax;
    put(app, f + kWord, cpu.edx);
    cpu.edx = at(app, f + kSource);
    cpu.eax = 0;
    cpu.ecx = cpu.edi;
    cpu.al = byte(app, cpu.edx + 0x1);
    cpu.edx = at(app, f + kWord);
    cpu.ecx = 0 - cpu.ecx;
    cpu.edx <<= 8;
    cpu.edi += 0x10;
    cpu.eax |= cpu.edx;
    cpu.edx = at(app, f + kSource);
    put(app, f + kWord, cpu.eax);
    cpu.esi = cpu.eax;
    cpu.edx += 2;
    cpu.esi <<= cpu.cl & 31;
    put(app, f + kSource, cpu.edx);
    goto l50ee41;
l50f11c:
    cpu.eax = cpu.esi;
    cpu.edi -= 8;
    cpu.eax >>= 0x18;
    cpu.esi <<= 8;
    putByte(app, f + kClue, cpu.al);
    if (sreg32(cpu.edi) < 0)
        goto l50f51a;
l50f136:
    cpu.eax = 1;
    cpu.edx = 0xf;
    cpu.ecx = 4;
    cpu.ebp = 0;
    put(app, f + kNextLength, cpu.eax);
    put(app, f + kShift, cpu.edx);
    put(app, f + kLengthOffset, cpu.ecx);
    put(app, f + kTotal, cpu.ebp);
l50f163:
    cpu.ebp += cpu.ebp;
    cpu.ebx = at(app, f + kTotal);
    cpu.eax = cpu.ebp;
    cpu.edx = at(app, f + kLengthOffset);
    cpu.eax -= cpu.ebx;
    put(app, f + cpu.edx + kOffsets, cpu.eax);
    if (sreg32(cpu.esi) < 0)
        goto l50f578;
    cpu.eax = cpu.esi;
    cpu.eax >>= 0x10;
    if (cpu.eax == 0)
        goto l50f651;
    cpu.eax = 2;
l50f198:
    cpu.esi += cpu.esi;
    ++cpu.eax;
    if (sreg32(cpu.esi) >= 0)
        goto l50f198;
    cpu.edx = cpu.eax - 0x1;
    cpu.edi -= cpu.edx;
    cpu.esi += cpu.esi;
    if (sreg32(cpu.edi) < 0)
        goto l50f5ee;
l50f1ae:
    cpu.edx = at(app, f + kWord);
    cpu.edx <<= 8;
    put(app, f + kCountWord, cpu.edx);
    cpu.edx = at(app, f + kSource);
    cpu.edx += 2;
    put(app, f + kCountSource, cpu.edx);
    if (sreg32(cpu.eax) <= sreg32(0x10))
        goto l50f79e;
    cpu.ecx = 0x20;
    cpu.ebx = cpu.eax - 0x10;
    cpu.edx = cpu.esi;
    cpu.ecx -= cpu.ebx;
    cpu.edx >>= cpu.cl & 31;
    cpu.cl = cpu.bl;
    cpu.edi -= cpu.ebx;
    cpu.esi <<= cpu.cl & 31;
    if (sreg32(cpu.edi) < 0)
        goto l50f6ce;
l50f1f5:
    cpu.ebx = cpu.esi;
    cpu.edi -= 0x10;
    cpu.esi <<= 0x10;
    cpu.ebx >>= 0x10;
    if (sreg32(cpu.edi) < 0)
        goto l50f726;
l50f208:
    cpu.cl = cpu.al;
    cpu.edx <<= 0x10;
    cpu.eax = 1;
    cpu.edx |= cpu.ebx;
l50f214:
    cpu.eax <<= cpu.cl & 31;
    cpu.edx += cpu.eax;
l50f218:
    cpu.edx -= 4;
    cpu.ebx = at(app, f + kTotal);
    cpu.eax = at(app, f + kLengthOffset);
    cpu.ebp += cpu.edx;
    cpu.ecx = 0;
    cpu.ebx += cpu.edx;
    put(app, f + cpu.eax + kCounts, cpu.edx);
    put(app, f + kTotal, cpu.ebx);
    if (cpu.edx == 0)
        goto l50f254;
    cpu.cl = byte(app, f + kShift);
    cpu.eax = cpu.ebp;
    cpu.eax <<= cpu.cl & 31;
    cpu.ecx = cpu.eax;
    cpu.ecx &= 0xffff;
l50f254:
    cpu.eax = at(app, f + kLengthOffset);
    put(app, f + cpu.eax + kLimits, cpu.ecx);
    cpu.eax = at(app, f + kShift);
    --cpu.eax;
    cpu.ebx = at(app, f + kLengthOffset);
    put(app, f + kShift, cpu.eax);
    cpu.eax = at(app, f + kNextLength);
    cpu.ebx += 4;
    ++cpu.eax;
    put(app, f + kLengthOffset, cpu.ebx);
    put(app, f + kNextLength, cpu.eax);
    if (cpu.edx == 0)
        goto l50f163;
    if (cpu.ecx != 0)
        goto l50f163;
    --cpu.eax;
    cpu.edx = 0xffffffff;
    put(app, f + kLongest, cpu.eax);
    put(app, f + cpu.eax * 4 + kLimits, cpu.edx);
    cpu.edx = 0x10;
    cpu.eax = cpu.esp;
l50f2bc:
    cpu.eax += 0x10;
    put(app, cpu.eax - 0xc, cpu.ecx);
    put(app, cpu.eax - 0x8, cpu.ecx);
    put(app, cpu.eax - 0x4, cpu.ecx);
    put(app, cpu.eax - 0x10, cpu.ecx);
    --cpu.edx;
    if (cpu.edx != 0)
        goto l50f2bc;
    cpu.ebx = at(app, f + kTotal);
    cpu.al = 0xff;
    put(app, f + kSymbolIndex, cpu.edx);
    if (sreg32(cpu.ebx) <= 0)
        goto l50f3e2;
l50f2e6:
    if (sreg32(cpu.esi) < 0)
        goto l50f81e;
    cpu.edx = cpu.esi;
    cpu.edx >>= 0x10;
    if (cpu.edx == 0)
        goto l50f8f2;
    cpu.edx = 2;
l50f300:
    cpu.esi += cpu.esi;
    ++cpu.edx;
    if (sreg32(cpu.esi) >= 0)
        goto l50f300;
    cpu.ecx = cpu.edx - 0x1;
    cpu.edi -= cpu.ecx;
    cpu.esi += cpu.esi;
    if (sreg32(cpu.edi) < 0)
        goto l50f894;
l50f316:
    cpu.ecx = at(app, f + kSource);
    cpu.ebp = at(app, f + kWord);
    cpu.ecx += 2;
    cpu.ebp <<= 8;
    put(app, f + kSymbolSource, cpu.ecx);
    if (sreg32(cpu.edx) <= sreg32(0x10))
        goto l50fa09;
    cpu.ecx = cpu.edx - 0x10;
    put(app, f + kHighBits, cpu.ecx);
    cpu.ecx = 0x20;
    cpu.ecx -= at(app, f + kHighBits);
    cpu.ebx = cpu.esi;
    cpu.ebx >>= cpu.cl & 31;
    cpu.cl = byte(app, f + kHighBits);
    cpu.esi <<= cpu.cl & 31;
    cpu.edi -= at(app, f + kHighBits);
    if (sreg32(cpu.edi) < 0)
        goto l50f96f;
l50f36c:
    cpu.ecx = cpu.esi;
    cpu.edi -= 0x10;
    cpu.ecx >>= 0x10;
    cpu.esi <<= 0x10;
    put(app, f + kLowBits, cpu.ecx);
    if (sreg32(cpu.edi) < 0)
        goto l50f9af;
l50f386:
    cpu.ecx = at(app, f + kLowBits);
    cpu.ebx <<= 0x10;
    cpu.ebx |= cpu.ecx;
l50f392:
    cpu.cl = cpu.dl;
    cpu.edx = 1;
    cpu.edx <<= cpu.cl & 31;
    cpu.ebx += cpu.edx;
l50f39d:
    cpu.ebx -= 4;
    ++cpu.ebx;
    cpu.ecx = 0;
l50f3a3:
    ++cpu.al;
    cpu.edx = 0;
    cpu.dl = cpu.al;
    if (cpu.cl != byte(app, f + kUsed + cpu.edx))
        goto l50f3af;
    --cpu.ebx;
l50f3af:
    if (cpu.ebx != 0)
        goto l50f3a3;
    cpu.edx = 0;
    cpu.dl = cpu.al;
    putByte(app, f + kUsed + cpu.edx, 1);
    cpu.edx = at(app, f + kSymbolIndex);
    cpu.ecx = at(app, f + kTotal);
    cpu.ebp = cpu.edx + 0x1;
    putByte(app, f + kSymbols + cpu.edx, cpu.al);
    put(app, f + kSymbolIndex, cpu.ebp);
    if (sreg32(cpu.ebp) < sreg32(cpu.ecx))
        goto l50f2e6;
l50f3e2:
    cpu.edx = f + kLookupLengths;
    cpu.ebx = 0x40404040;
    cpu.ecx = 0x10;
l50f3f3:
    cpu.edx += 0x10;
    put(app, cpu.edx - 0xc, cpu.ebx);
    put(app, cpu.edx - 0x8, cpu.ebx);
    put(app, cpu.edx - 0x4, cpu.ebx);
    put(app, cpu.edx - 0x10, cpu.ebx);
    --cpu.ecx;
    if (cpu.ecx != 0)
        goto l50f3f3;
    cpu.eax = f + kSymbols;
    cpu.ebx = f + kLookupSymbols;
    cpu.edx = f + kLookupLengths;
    put(app, f + kSymbolAt, cpu.eax);
    cpu.eax = 1;
    cpu.ecx = at(app, f + kLongest);
    put(app, f + kTableLength, cpu.eax);
    if (sreg32(cpu.ecx) < sreg32(cpu.eax))
        goto l50ee5e;
    cpu.ecx = 7;
    cpu.eax = 4;
    put(app, f + kTableShift, cpu.ecx);
    put(app, f + kTableOffset, cpu.eax);
l50f454:
    cpu.eax = at(app, f + kTableOffset);
    cpu.eax = at(app, f + cpu.eax + kCounts);
    cpu.ebp = at(app, f + kTableLength);
    put(app, f + kLeft, cpu.eax);
    if (sreg32(cpu.ebp) >= sreg32(9))
        goto l50ee5e;
    cpu.cl = byte(app, f + kTableShift);
    cpu.ebp = 1;
    cpu.ebp <<= cpu.cl & 31;
l50f487:
    cpu.eax = at(app, f + kLeft);
    --cpu.eax;
    put(app, f + kLeft, cpu.eax);
    if (cpu.eax == 0xffffffff)
        goto l50fa62;
    cpu.ecx = at(app, f + kSymbolAt);
    cpu.eax = 0;
    cpu.al = byte(app, cpu.ecx);
    ++cpu.ecx;
    put(app, f + kSymbol, cpu.eax);
    cpu.eax = at(app, f + kTableLength);
    put(app, f + kSymbolAt, cpu.ecx);
    put(app, f + kSymbolLength, cpu.eax);
    cpu.eax = 0;
    cpu.ecx = at(app, f + kSymbol);
    cpu.al = byte(app, f + kClue);
    if (cpu.eax != cpu.ecx)
        goto l50f4f4;
    cpu.eax = at(app, f + kTableLength);
    put(app, f + kClueLength, cpu.eax);
    put(app, f + kSymbolLength, 0x60);
l50f4f4:
    cpu.eax = 0;
    if (sreg32(cpu.ebp) <= 0)
        goto l50f487;
l50f4fa:
    ++cpu.ebx;
    cpu.cl = byte(app, f + kSymbol);
    ++cpu.edx;
    putByte(app, cpu.ebx - 0x1, cpu.cl);
    cpu.cl = byte(app, f + kSymbolLength);
    ++cpu.eax;
    putByte(app, cpu.edx - 0x1, cpu.cl);
    if (sreg32(cpu.eax) < sreg32(cpu.ebp))
        goto l50f4fa;
    goto l50f487;
l50f51a:
    cpu.eax = at(app, f + kSource);
    cpu.edx = 0;
    cpu.dl = byte(app, cpu.eax);
    cpu.eax = at(app, f + kWord);
    cpu.ebx = at(app, f + kSource);
    cpu.eax <<= 8;
    cpu.ecx = cpu.edi;
    cpu.edx |= cpu.eax;
    cpu.eax = at(app, f + kSource);
    put(app, f + kWord, cpu.edx);
    cpu.edx = 0;
    cpu.ecx = 0 - cpu.ecx;
    cpu.dl = byte(app, cpu.eax + 0x1);
    cpu.eax = at(app, f + kWord);
    cpu.ebx += 2;
    cpu.eax <<= 8;
    cpu.edi += 0x10;
    cpu.edx |= cpu.eax;
    put(app, f + kSource, cpu.ebx);
    cpu.esi = cpu.edx;
    put(app, f + kWord, cpu.edx);
    cpu.esi <<= cpu.cl & 31;
    goto l50f136;
l50f578:
    cpu.edx = cpu.esi;
    cpu.edi -= 3;
    cpu.esi <<= 3;
    cpu.edx >>= 0x1d;
    if (sreg32(cpu.edi) >= 0)
        goto l50f218;
    cpu.eax = at(app, f + kSource);
    cpu.ecx = 0;
    cpu.cl = byte(app, cpu.eax);
    cpu.eax = at(app, f + kWord);
    cpu.eax <<= 8;
    cpu.ecx |= cpu.eax;
    cpu.eax = at(app, f + kSource);
    put(app, f + kWord, cpu.ecx);
    cpu.ecx = 0;
    cpu.cl = byte(app, cpu.eax + 0x1);
    cpu.eax = at(app, f + kWord);
    cpu.eax <<= 8;
    cpu.ecx |= cpu.eax;
    put(app, f + kWord, cpu.ecx);
    cpu.eax = at(app, f + kSource);
    cpu.esi = at(app, f + kWord);
    cpu.ecx = cpu.edi;
    cpu.eax += 2;
    cpu.ecx = 0 - cpu.ecx;
    put(app, f + kSource, cpu.eax);
    cpu.edi += 0x10;
    cpu.esi <<= cpu.cl & 31;
    goto l50f218;
l50f5ee:
    cpu.edx = at(app, f + kSource);
    cpu.ecx = 0;
    cpu.cl = byte(app, cpu.edx);
    cpu.edx = at(app, f + kWord);
    cpu.edx <<= 8;
    cpu.ecx |= cpu.edx;
    cpu.edx = at(app, f + kSource);
    put(app, f + kWord, cpu.ecx);
    cpu.ecx = 0;
    cpu.cl = byte(app, cpu.edx + 0x1);
    cpu.edx = at(app, f + kWord);
    cpu.ebx = at(app, f + kSource);
    cpu.edx <<= 8;
    cpu.ebx += 2;
    cpu.ecx |= cpu.edx;
    put(app, f + kSource, cpu.ebx);
    put(app, f + kWord, cpu.ecx);
    cpu.ecx = cpu.edi;
    cpu.esi = at(app, f + kWord);
    cpu.ecx = 0 - cpu.ecx;
    cpu.edi += 0x10;
    cpu.esi <<= cpu.cl & 31;
    goto l50f1ae;
l50f651:
    cpu.eax = 2;
l50f656:
    cpu.edx = cpu.esi;
    ++cpu.eax;
    --cpu.edi;
    cpu.edx >>= 0x1f;
    cpu.esi += cpu.esi;
    if (sreg32(cpu.edi) < 0)
        goto l50f66c;
    if (cpu.edx == 0)
        goto l50f656;
    goto l50f1ae;
l50f66c:
    cpu.ebx = at(app, f + kSource);
    cpu.ecx = 0;
    cpu.cl = byte(app, cpu.ebx);
    cpu.ebx = at(app, f + kWord);
    cpu.ebx <<= 8;
    cpu.ecx |= cpu.ebx;
    put(app, f + kWord, cpu.ecx);
    cpu.ecx = at(app, f + kSource);
    cpu.ebx = 0;
    cpu.bl = byte(app, cpu.ecx + 0x1);
    cpu.ecx = at(app, f + kWord);
    cpu.ecx <<= 8;
    cpu.ebx |= cpu.ecx;
    cpu.ecx = cpu.edi;
    cpu.esi = cpu.ebx;
    cpu.ecx = 0 - cpu.ecx;
    cpu.esi <<= cpu.cl & 31;
    cpu.ecx = at(app, f + kSource);
    put(app, f + kWord, cpu.ebx);
    cpu.ecx += 2;
    cpu.edi += 0x10;
    put(app, f + kSource, cpu.ecx);
    if (cpu.edx == 0)
        goto l50f656;
    goto l50f1ae;
l50f6ce:
    cpu.ebx = at(app, f + kSource);
    cpu.ecx = 0;
    cpu.cl = byte(app, cpu.ebx);
    cpu.ebx = at(app, f + kCountWord);
    cpu.ebx |= cpu.ecx;
    cpu.ecx = at(app, f + kSource);
    put(app, f + kWord, cpu.ebx);
    cpu.ebx = 0;
    cpu.bl = byte(app, cpu.ecx + 0x1);
    cpu.ecx = at(app, f + kWord);
    cpu.ecx <<= 8;
    cpu.ebx |= cpu.ecx;
    cpu.ecx = cpu.edi;
    cpu.esi = cpu.ebx;
    cpu.ecx = 0 - cpu.ecx;
    put(app, f + kWord, cpu.ebx);
    cpu.esi <<= cpu.cl & 31;
    cpu.ecx = at(app, f + kCountSource);
    cpu.edi += 0x10;
    put(app, f + kSource, cpu.ecx);
    goto l50f1f5;
l50f726:
    cpu.esi = at(app, f + kSource);
    cpu.ecx = 0;
    cpu.cl = byte(app, cpu.esi);
    put(app, f + kHighBits, cpu.ecx);
    cpu.ecx = at(app, f + kWord);
    cpu.esi = at(app, f + kHighBits);
    cpu.ecx <<= 8;
    cpu.esi |= cpu.ecx;
    put(app, f + kWord, cpu.esi);
    cpu.esi = at(app, f + kSource);
    cpu.ecx = 0;
    cpu.cl = byte(app, cpu.esi + 0x1);
    put(app, f + kHighBits, cpu.ecx);
    cpu.ecx = at(app, f + kWord);
    cpu.esi = at(app, f + kHighBits);
    cpu.ecx <<= 8;
    cpu.esi |= cpu.ecx;
    cpu.ecx = cpu.edi;
    cpu.ecx = 0 - cpu.ecx;
    put(app, f + kWord, cpu.esi);
    cpu.esi <<= cpu.cl & 31;
    cpu.ecx = at(app, f + kSource);
    cpu.ecx += 2;
    cpu.edi += 0x10;
    put(app, f + kSource, cpu.ecx);
    goto l50f208;
l50f79e:
    cpu.ecx = 0x20;
    cpu.edx = cpu.esi;
    cpu.ecx -= cpu.eax;
    cpu.edx >>= cpu.cl & 31;
    cpu.cl = cpu.al;
    cpu.edi -= cpu.eax;
    cpu.esi <<= cpu.cl & 31;
    if (sreg32(cpu.edi) < 0)
        goto l50f7bf;
    cpu.cl = cpu.al;
    cpu.eax = 1;
    goto l50f214;
l50f7bf:
    cpu.ebx = at(app, f + kSource);
    cpu.ecx = 0;
    cpu.cl = byte(app, cpu.ebx);
    cpu.ebx = at(app, f + kCountWord);
    cpu.ebx |= cpu.ecx;
    cpu.ecx = at(app, f + kSource);
    put(app, f + kWord, cpu.ebx);
    cpu.ebx = 0;
    cpu.bl = byte(app, cpu.ecx + 0x1);
    cpu.ecx = at(app, f + kWord);
    cpu.ecx <<= 8;
    cpu.ebx |= cpu.ecx;
    cpu.ecx = cpu.edi;
    cpu.esi = cpu.ebx;
    cpu.ecx = 0 - cpu.ecx;
    put(app, f + kWord, cpu.ebx);
    cpu.esi <<= cpu.cl & 31;
    cpu.ecx = at(app, f + kCountSource);
    cpu.edi += 0x10;
    put(app, f + kSource, cpu.ecx);
    cpu.cl = cpu.al;
    cpu.eax = 1;
    goto l50f214;
l50f81e:
    cpu.ebx = cpu.esi;
    cpu.edi -= 3;
    cpu.esi <<= 3;
    cpu.ebx >>= 0x1d;
    if (sreg32(cpu.edi) >= 0)
        goto l50f39d;
    cpu.edx = at(app, f + kSource);
    cpu.ecx = 0;
    cpu.cl = byte(app, cpu.edx);
    cpu.edx = at(app, f + kWord);
    cpu.edx <<= 8;
    cpu.ecx |= cpu.edx;
    cpu.edx = at(app, f + kSource);
    put(app, f + kWord, cpu.ecx);
    cpu.ecx = 0;
    cpu.cl = byte(app, cpu.edx + 0x1);
    cpu.edx = at(app, f + kWord);
    cpu.ebp = at(app, f + kSource);
    cpu.edx <<= 8;
    cpu.ebp += 2;
    cpu.ecx |= cpu.edx;
    put(app, f + kSource, cpu.ebp);
    put(app, f + kWord, cpu.ecx);
    cpu.ecx = cpu.edi;
    cpu.esi = at(app, f + kWord);
    cpu.ecx = 0 - cpu.ecx;
    cpu.edi += 0x10;
    cpu.esi <<= cpu.cl & 31;
    goto l50f39d;
l50f894:
    cpu.ebx = at(app, f + kSource);
    cpu.ecx = 0;
    cpu.cl = byte(app, cpu.ebx);
    cpu.ebx = at(app, f + kWord);
    cpu.ebx <<= 8;
    cpu.ecx |= cpu.ebx;
    put(app, f + kWord, cpu.ecx);
    cpu.ecx = at(app, f + kSource);
    cpu.ebx = 0;
    cpu.bl = byte(app, cpu.ecx + 0x1);
    cpu.ecx = at(app, f + kWord);
    cpu.ebp = at(app, f + kSource);
    cpu.ecx <<= 8;
    cpu.ebp += 2;
    cpu.ebx |= cpu.ecx;
    put(app, f + kSource, cpu.ebp);
    put(app, f + kWord, cpu.ebx);
    cpu.ecx = cpu.edi;
    cpu.esi = cpu.ebx;
    cpu.ecx = 0 - cpu.ecx;
    cpu.edi += 0x10;
    cpu.esi <<= cpu.cl & 31;
    goto l50f316;
l50f8f2:
    cpu.edx = 2;
l50f8f7:
    cpu.ebp = cpu.esi;
    ++cpu.edx;
    --cpu.edi;
    cpu.ebp >>= 0x1f;
    cpu.esi += cpu.esi;
    if (sreg32(cpu.edi) < 0)
        goto l50f90d;
    if (cpu.ebp == 0)
        goto l50f8f7;
    goto l50f316;
l50f90d:
    cpu.ecx = at(app, f + kSource);
    cpu.ebx = 0;
    cpu.bl = byte(app, cpu.ecx);
    cpu.ecx = at(app, f + kWord);
    cpu.ecx <<= 8;
    cpu.ebx |= cpu.ecx;
    cpu.ecx = at(app, f + kSource);
    put(app, f + kWord, cpu.ebx);
    cpu.ebx = 0;
    cpu.bl = byte(app, cpu.ecx + 0x1);
    cpu.ecx = at(app, f + kWord);
    cpu.ecx <<= 8;
    cpu.ebx |= cpu.ecx;
    put(app, f + kWord, cpu.ebx);
    cpu.ecx = cpu.edi;
    cpu.esi = cpu.ebx;
    cpu.ebx = at(app, f + kSource);
    cpu.ecx = 0 - cpu.ecx;
    cpu.edi += 0x10;
    cpu.ebx += 2;
    cpu.esi <<= cpu.cl & 31;
    put(app, f + kSource, cpu.ebx);
    if (cpu.ebp == 0)
        goto l50f8f7;
    goto l50f316;
l50f96f:
    cpu.esi = at(app, f + kSource);
    cpu.ecx = 0;
    cpu.cl = byte(app, cpu.esi);
    cpu.ecx |= cpu.ebp;
    cpu.esi = byte(app, cpu.esi + 0x1);
    put(app, f + kWord, cpu.ecx);
    cpu.ecx <<= 8;
    cpu.esi |= cpu.ecx;
    cpu.ecx = cpu.edi;
    cpu.ecx = 0 - cpu.ecx;
    put(app, f + kWord, cpu.esi);
    cpu.esi <<= cpu.cl & 31;
    cpu.ecx = at(app, f + kSymbolSource);
    cpu.edi += 0x10;
    put(app, f + kSource, cpu.ecx);
    goto l50f36c;
l50f9af:
    cpu.ecx = at(app, f + kWord);
    cpu.esi = at(app, f + kSource);
    cpu.ecx <<= 8;
    cpu.esi = byte(app, cpu.esi);
    cpu.esi |= cpu.ecx;
    cpu.ebp = at(app, f + kSource);
    put(app, f + kWord, cpu.esi);
    cpu.ebp += 2;
    cpu.ecx = at(app, f + kWord);
    cpu.esi = at(app, f + kSource);
    cpu.ecx <<= 8;
    cpu.esi = byte(app, cpu.esi + 0x1);
    put(app, f + kSource, cpu.ebp);
    cpu.esi |= cpu.ecx;
    cpu.ecx = cpu.edi;
    put(app, f + kWord, cpu.esi);
    cpu.ecx = 0 - cpu.ecx;
    cpu.edi += 0x10;
    cpu.esi <<= cpu.cl & 31;
    goto l50f386;
l50fa09:
    cpu.ecx = 0x20;
    cpu.ebx = cpu.esi;
    cpu.ecx -= cpu.edx;
    cpu.ebx >>= cpu.cl & 31;
    cpu.cl = cpu.dl;
    cpu.edi -= cpu.edx;
    cpu.esi <<= cpu.cl & 31;
    if (sreg32(cpu.edi) >= 0)
        goto l50f392;
    cpu.esi = at(app, f + kSource);
    cpu.ecx = 0;
    cpu.cl = byte(app, cpu.esi);
    cpu.ecx |= cpu.ebp;
    cpu.esi = byte(app, cpu.esi + 0x1);
    put(app, f + kWord, cpu.ecx);
    cpu.ecx <<= 8;
    cpu.esi |= cpu.ecx;
    cpu.ecx = cpu.edi;
    cpu.ecx = 0 - cpu.ecx;
    put(app, f + kWord, cpu.esi);
    cpu.esi <<= cpu.cl & 31;
    cpu.ecx = at(app, f + kSymbolSource);
    cpu.edi += 0x10;
    put(app, f + kSource, cpu.ecx);
    goto l50f392;
l50fa62:
    cpu.ebp = at(app, f + kTableOffset);
    cpu.eax = at(app, f + kTableShift);
    cpu.ecx = at(app, f + kTableLength);
    cpu.ebp += 4;
    --cpu.eax;
    ++cpu.ecx;
    put(app, f + kTableOffset, cpu.ebp);
    put(app, f + kTableShift, cpu.eax);
    cpu.ebp = at(app, f + kLongest);
    put(app, f + kTableLength, cpu.ecx);
    if (sreg32(cpu.ecx) <= sreg32(cpu.ebp))
        goto l50f454;
    goto l50ee5e;
l50faa5:
    cpu.edi -= 0x10;
    cpu.edi += cpu.eax;
    if (cpu.eax == 0x60)
        goto l50fb17;
    cpu.eax = 8;
    cpu.edx = cpu.esi;
    cpu.ecx = 0x20;
    cpu.edx >>= 0x10;
l50fabe:
    ++cpu.eax;
    cpu.ebp = at(app, f + cpu.ecx + kLimits + 4);
    cpu.ecx += 4;
    if (reg32(cpu.edx) >= reg32(cpu.ebp))
        goto l50fabe;
l50facd:
    cpu.ecx = 0x20;
    cpu.edx = cpu.esi;
    cpu.ecx -= cpu.eax;
    cpu.edx >>= cpu.cl & 31;
    cpu.cl = cpu.al;
    cpu.edi -= cpu.eax;
    cpu.esi <<= cpu.cl & 31;
    cpu.ecx = at(app, f + cpu.eax * 4 + kOffsets);
    cpu.eax = cpu.edx;
    cpu.eax -= cpu.ecx;
    cpu.dl = byte(app, f + kClue);
    cpu.al = byte(app, f + kSymbols + cpu.eax);
    if (cpu.al == cpu.dl)
        goto l50fb20;
    if (sreg32(cpu.edi) < 0)
        goto l50fb20;
    cpu.edx = at(app, f + kDest);
    putByte(app, cpu.edx, cpu.al);
    cpu.eax = cpu.edx + 0x1;
    put(app, f + kDest, cpu.eax);
    goto l50ee73;
l50fb17:
    cpu.eax = at(app, f + kClueLength);
    goto l50facd;
l50fb20:
    if (sreg32(cpu.edi) < 0)
        goto l50fb45;
l50fb24:
    if (cpu.al == byte(app, f + kClue))
        goto l50fba8;
    cpu.edx = at(app, f + kDest);
    cpu.ebp = cpu.edx + 0x1;
    putByte(app, cpu.edx, cpu.al);
    put(app, f + kDest, cpu.ebp);
    goto l50ee73;
l50fb45:
    cpu.edx = at(app, f + kSource);
    cpu.ecx = 0;
    cpu.cl = byte(app, cpu.edx);
    cpu.edx = at(app, f + kWord);
    cpu.edx <<= 8;
    cpu.ecx |= cpu.edx;
    cpu.edx = at(app, f + kSource);
    put(app, f + kWord, cpu.ecx);
    cpu.ecx = 0;
    cpu.cl = byte(app, cpu.edx + 0x1);
    cpu.edx = at(app, f + kWord);
    cpu.ebp = at(app, f + kSource);
    cpu.edx <<= 8;
    cpu.ebp += 2;
    cpu.ecx |= cpu.edx;
    put(app, f + kSource, cpu.ebp);
    put(app, f + kWord, cpu.ecx);
    cpu.ecx = cpu.edi;
    cpu.esi = at(app, f + kWord);
    cpu.ecx = 0 - cpu.ecx;
    cpu.edi += 0x10;
    cpu.esi <<= cpu.cl & 31;
    goto l50fb24;
l50fba8:
    cpu.edx = at(app, f + kDest);
    if (sreg32(cpu.esi) < 0)
        goto l50fcae;
    cpu.eax = cpu.esi;
    cpu.eax >>= 0x10;
    if (cpu.eax == 0)
        goto l50fd8d;
    cpu.eax = 2;
l50fbc9:
    cpu.esi += cpu.esi;
    ++cpu.eax;
    if (sreg32(cpu.esi) >= 0)
        goto l50fbc9;
    cpu.ecx = cpu.eax - 0x1;
    cpu.edi -= cpu.ecx;
    cpu.esi += cpu.esi;
    if (sreg32(cpu.edi) < 0)
        goto l50fd39;
l50fbdf:
    cpu.ecx = at(app, f + kWord);
    cpu.ecx <<= 8;
    put(app, f + kRunWord, cpu.ecx);
    cpu.ecx = at(app, f + kSource);
    cpu.ecx += 2;
    put(app, f + kRunSource, cpu.ecx);
    if (sreg32(cpu.eax) <= sreg32(0x10))
        goto l50fed0;
    cpu.ecx = cpu.eax - 0x10;
    put(app, f + kHighBits, cpu.ecx);
    cpu.ecx = 0x20;
    cpu.ecx -= at(app, f + kHighBits);
    cpu.ebp = cpu.esi;
    cpu.ebp >>= cpu.cl & 31;
    cpu.cl = byte(app, f + kHighBits);
    cpu.esi <<= cpu.cl & 31;
    cpu.edi -= at(app, f + kHighBits);
    put(app, f + kRun, cpu.ebp);
    if (sreg32(cpu.edi) < 0)
        goto l50fe19;
l50fc43:
    cpu.ecx = cpu.esi;
    cpu.edi -= 0x10;
    cpu.ecx >>= 0x10;
    cpu.esi <<= 0x10;
    put(app, f + kRunLow, cpu.ecx);
    if (sreg32(cpu.edi) < 0)
        goto l50fe6e;
l50fc5d:
    cpu.ecx = at(app, f + kRun);
    cpu.ebp = at(app, f + kRunLow);
    cpu.ecx <<= 0x10;
    cpu.ebp |= cpu.ecx;
    cpu.cl = cpu.al;
    cpu.eax = 1;
    cpu.eax <<= cpu.cl & 31;
    cpu.eax += cpu.ebp;
l50fc7b:
    cpu.eax -= 4;
    put(app, f + kRun, cpu.eax);
l50fc85:
    cpu.ebp = at(app, f + kRun);
    if (cpu.ebp == 0)
        goto l50ff5b;
    cpu.cl = byte(app, cpu.edx - 0x1);
    cpu.eax = cpu.edx + cpu.ebp;
l50fc9a:
    ++cpu.edx;
    putByte(app, cpu.edx - 0x1, cpu.cl);
    if (reg32(cpu.edx) < reg32(cpu.eax))
        goto l50fc9a;
    put(app, f + kDest, cpu.edx);
    goto l50ee73;
l50fcae:
    cpu.eax = cpu.esi;
    cpu.edi -= 3;
    cpu.eax >>= 0x1d;
    cpu.esi <<= 3;
    put(app, f + kRun, cpu.eax);
    if (sreg32(cpu.edi) < 0)
        goto l50fcce;
    put(app, f + kRun, reg32(at(app, f + kRun) - 4));
    goto l50fc85;
l50fcce:
    cpu.ecx = at(app, f + kSource);
    cpu.eax = 0;
    cpu.al = byte(app, cpu.ecx);
    cpu.ecx = at(app, f + kWord);
    cpu.ecx <<= 8;
    cpu.eax |= cpu.ecx;
    put(app, f + kWord, cpu.eax);
    cpu.eax = at(app, f + kSource);
    cpu.ecx = 0;
    cpu.cl = byte(app, cpu.eax + 0x1);
    cpu.eax = at(app, f + kWord);
    cpu.eax <<= 8;
    cpu.ecx |= cpu.eax;
    put(app, f + kWord, cpu.ecx);
    cpu.eax = at(app, f + kSource);
    cpu.esi = at(app, f + kWord);
    cpu.ecx = cpu.edi;
    cpu.eax += 2;
    cpu.ecx = 0 - cpu.ecx;
    put(app, f + kSource, cpu.eax);
    cpu.edi += 0x10;
    cpu.esi <<= cpu.cl & 31;
    put(app, f + kRun, reg32(at(app, f + kRun) - 4));
    goto l50fc85;
l50fd39:
    cpu.esi = at(app, f + kSource);
    cpu.ecx = 0;
    cpu.cl = byte(app, cpu.esi);
    cpu.esi = at(app, f + kWord);
    cpu.ebp = at(app, f + kSource);
    cpu.esi <<= 8;
    cpu.ebp += 2;
    cpu.ecx |= cpu.esi;
    cpu.esi = at(app, f + kSource);
    put(app, f + kWord, cpu.ecx);
    cpu.ecx <<= 8;
    cpu.esi = byte(app, cpu.esi + 0x1);
    put(app, f + kSource, cpu.ebp);
    cpu.esi |= cpu.ecx;
    cpu.ecx = cpu.edi;
    put(app, f + kWord, cpu.esi);
    cpu.ecx = 0 - cpu.ecx;
    cpu.edi += 0x10;
    cpu.esi <<= cpu.cl & 31;
    goto l50fbdf;
l50fd8d:
    cpu.eax = 2;
    cpu.ebp = 0;
l50fd94:
    cpu.ecx = cpu.esi;
    ++cpu.eax;
    --cpu.edi;
    cpu.ecx >>= 0x1f;
    cpu.esi += cpu.esi;
    put(app, f + kBit, cpu.ecx);
    if (sreg32(cpu.edi) < 0)
        goto l50fdb6;
    if (cpu.ebp == at(app, f + kBit))
        goto l50fd94;
    goto l50fbdf;
l50fdb6:
    cpu.ecx = at(app, f + kWord);
    cpu.esi = at(app, f + kSource);
    cpu.ecx <<= 8;
    cpu.esi = byte(app, cpu.esi);
    cpu.esi |= cpu.ecx;
    put(app, f + kWord, cpu.esi);
    cpu.ecx = at(app, f + kWord);
    cpu.esi = at(app, f + kSource);
    cpu.ecx <<= 8;
    cpu.esi = byte(app, cpu.esi + 0x1);
    cpu.esi |= cpu.ecx;
    cpu.ecx = cpu.edi;
    cpu.ecx = 0 - cpu.ecx;
    put(app, f + kWord, cpu.esi);
    cpu.esi <<= cpu.cl & 31;
    cpu.ecx = at(app, f + kSource);
    cpu.ecx += 2;
    cpu.edi += 0x10;
    put(app, f + kSource, cpu.ecx);
    if (cpu.ebp == at(app, f + kBit))
        goto l50fd94;
    goto l50fbdf;
l50fe19:
    cpu.esi = at(app, f + kSource);
    cpu.ecx = 0;
    cpu.cl = byte(app, cpu.esi);
    cpu.esi = at(app, f + kRunWord);
    cpu.esi |= cpu.ecx;
    put(app, f + kWord, cpu.esi);
    cpu.ecx = at(app, f + kWord);
    cpu.esi = at(app, f + kSource);
    cpu.ecx <<= 8;
    cpu.esi = byte(app, cpu.esi + 0x1);
    cpu.esi |= cpu.ecx;
    cpu.ecx = cpu.edi;
    cpu.ecx = 0 - cpu.ecx;
    put(app, f + kWord, cpu.esi);
    cpu.esi <<= cpu.cl & 31;
    cpu.ecx = at(app, f + kRunSource);
    cpu.edi += 0x10;
    put(app, f + kSource, cpu.ecx);
    goto l50fc43;
l50fe6e:
    cpu.ecx = at(app, f + kWord);
    cpu.esi = at(app, f + kSource);
    cpu.ecx <<= 8;
    cpu.esi = byte(app, cpu.esi);
    cpu.esi |= cpu.ecx;
    put(app, f + kWord, cpu.esi);
    cpu.esi = at(app, f + kSource);
    cpu.ecx = 0;
    cpu.cl = byte(app, cpu.esi + 0x1);
    cpu.esi = at(app, f + kWord);
    cpu.ebp = at(app, f + kSource);
    cpu.esi <<= 8;
    cpu.ebp += 2;
    cpu.ecx |= cpu.esi;
    put(app, f + kSource, cpu.ebp);
    put(app, f + kWord, cpu.ecx);
    cpu.ecx = cpu.edi;
    cpu.esi = at(app, f + kWord);
    cpu.ecx = 0 - cpu.ecx;
    cpu.edi += 0x10;
    cpu.esi <<= cpu.cl & 31;
    goto l50fc5d;
l50fed0:
    cpu.ecx = 0x20;
    cpu.ebp = cpu.esi;
    cpu.ecx -= cpu.eax;
    cpu.edi -= cpu.eax;
    cpu.ebp >>= cpu.cl & 31;
    cpu.cl = cpu.al;
    put(app, f + kRun, cpu.ebp);
    cpu.esi <<= cpu.cl & 31;
    if (sreg32(cpu.edi) < 0)
        goto l50ff01;
l50feec:
    cpu.cl = cpu.al;
    cpu.eax = 1;
    cpu.eax <<= cpu.cl & 31;
    cpu.eax += at(app, f + kRun);
    goto l50fc7b;
l50ff01:
    cpu.esi = at(app, f + kSource);
    cpu.ecx = 0;
    cpu.cl = byte(app, cpu.esi);
    cpu.esi = at(app, f + kRunWord);
    cpu.esi |= cpu.ecx;
    put(app, f + kWord, cpu.esi);
    cpu.esi = at(app, f + kSource);
    cpu.ecx = 0;
    cpu.cl = byte(app, cpu.esi + 0x1);
    cpu.esi = at(app, f + kWord);
    cpu.esi <<= 8;
    cpu.ecx |= cpu.esi;
    put(app, f + kWord, cpu.ecx);
    cpu.ecx = cpu.edi;
    cpu.esi = at(app, f + kWord);
    cpu.ecx = 0 - cpu.ecx;
    cpu.esi <<= cpu.cl & 31;
    cpu.ecx = at(app, f + kRunSource);
    cpu.edi += 0x10;
    put(app, f + kSource, cpu.ecx);
    goto l50feec;
l50ff5b:
    cpu.ebp = cpu.esi;
    --cpu.edi;
    cpu.ebp >>= 0x1f;
    cpu.esi += cpu.esi;
    if (sreg32(cpu.edi) < 0)
        goto l50ffc2;
l50ff67:
    if (cpu.ebp == 0)
        goto l510020;
    cpu.edi = at(app, f + kStart);
    cpu.ebx = at(app, f + kLength);
    cpu.esi = at(app, f + kType);
    cpu.edi += cpu.ebx;
    if (cpu.esi != 0x32fb)
        goto l5100b0;
    cpu.eax = at(app, f + kStart);
    cpu.ebx = cpu.edi;
    cpu.ecx = 0;
    if (reg32(cpu.edi) <= reg32(cpu.eax))
        goto l50ffb0;
l50ffa1:
    cpu.edx = 0;
    cpu.dl = byte(app, cpu.eax);
    ++cpu.eax;
    cpu.ecx += cpu.edx;
    putByte(app, cpu.eax - 0x1, cpu.cl);
    if (reg32(cpu.eax) < reg32(cpu.ebx))
        goto l50ffa1;
    ;
l50ffb0:
    cpu.eax = at(app, f + kLength);
    cpu.esp += 0x544;
    cpu.ebp = pop(app, cpu);
    cpu.edi = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.esp += 4;
    return;
l50ffc2:
    cpu.eax = at(app, f + kSource);
    cpu.edx = 0;
    cpu.dl = byte(app, cpu.eax);
    cpu.eax = at(app, f + kWord);
    cpu.eax <<= 8;
    cpu.edx |= cpu.eax;
    cpu.eax = at(app, f + kSource);
    put(app, f + kWord, cpu.edx);
    cpu.edx = 0;
    cpu.ecx = cpu.edi;
    cpu.dl = byte(app, cpu.eax + 0x1);
    cpu.eax = at(app, f + kWord);
    cpu.ecx = 0 - cpu.ecx;
    cpu.eax <<= 8;
    cpu.edi += 0x10;
    cpu.edx |= cpu.eax;
    cpu.eax = at(app, f + kSource);
    put(app, f + kWord, cpu.edx);
    cpu.esi = cpu.edx;
    cpu.eax += 2;
    cpu.esi <<= cpu.cl & 31;
    put(app, f + kSource, cpu.eax);
    goto l50ff67;
l510020:
    cpu.eax = cpu.esi;
    cpu.edi -= 8;
    cpu.eax >>= 0x18;
    cpu.esi <<= 8;
    putByte(app, f + kLiteral, cpu.al);
    if (sreg32(cpu.edi) < 0)
        goto l510055;
l510036:
    cpu.edx = at(app, f + kDest);
    cpu.al = byte(app, f + kLiteral);
    cpu.ecx = cpu.edx + 0x1;
    putByte(app, cpu.edx, cpu.al);
    put(app, f + kDest, cpu.ecx);
    goto l50ee73;
l510055:
    cpu.eax = at(app, f + kSource);
    cpu.edx = 0;
    cpu.dl = byte(app, cpu.eax);
    cpu.eax = at(app, f + kWord);
    cpu.eax <<= 8;
    cpu.edx |= cpu.eax;
    cpu.eax = at(app, f + kSource);
    put(app, f + kWord, cpu.edx);
    cpu.edx = 0;
    cpu.dl = byte(app, cpu.eax + 0x1);
    cpu.eax = at(app, f + kWord);
    cpu.eax <<= 8;
    cpu.ecx = cpu.edi;
    cpu.edx |= cpu.eax;
    cpu.ecx = 0 - cpu.ecx;
    put(app, f + kWord, cpu.edx);
    cpu.esi = cpu.edx;
    cpu.edx = at(app, f + kSource);
    cpu.edi += 0x10;
    cpu.edx += 2;
    cpu.esi <<= cpu.cl & 31;
    put(app, f + kSource, cpu.edx);
    goto l510036;
l5100b0:
    if (cpu.esi != 0x34fb)
        goto l50ffb0;
    cpu.eax = at(app, f + kStart);
    cpu.esi = cpu.edi;
    cpu.edx = 0;
    cpu.ecx = 0;
    if (reg32(cpu.edi) <= reg32(cpu.eax))
        goto l50ffb0;
l5100d1:
    cpu.ebx = 0;
    cpu.bl = byte(app, cpu.eax);
    cpu.ecx += cpu.ebx;
    ++cpu.eax;
    cpu.edx += cpu.ecx;
    putByte(app, cpu.eax - 0x1, cpu.dl);
    if (reg32(cpu.eax) < reg32(cpu.esi))
        goto l5100d1;
    cpu.eax = at(app, f + kLength);
    cpu.esp += 0x544;
    cpu.ebp = pop(app, cpu);
    cpu.edi = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.esp += 4;
    return;

}

}  // namespace ea
}  // namespace nfs3hp
