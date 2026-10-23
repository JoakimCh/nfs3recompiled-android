#include "native_guest.h"

/* The race's queue of inputs: each player's four bytes by frame, handed to
 * the cars and to the other machines in a network race, and the edges of the
 * keys and actions the race's screens ask about.  disassemble_nfs3hp.py binds
 * each address to the function of that name here (CONTROLS_QUEUE_NATIVES),
 * and the generated code calls it by name.  tools/game_checks holds each
 * against its generated code.
 *
 * The queue is a ring of 128 frames for each of 8 players: a player's four
 * bytes (native_controls_pipeline.cpp's: the steering, the throttle, the
 * brake, 8 actions' bits) at 0x7d3714 + player * 0x200 + (frame & 0x7f) * 4,
 * a dword at 0x7d4714 on the same way saying the slot holds them, and each
 * player's frames queued so far at 0x7d5718 + player * 4 -- the next frame
 * queued goes to that count's slot.  Frames taken by the race so far are at
 * 0x7d5714: each frame of the race takes one frame's slots of every player
 * into 0x7d36f0 (player * 4) and frees them, and each car copies its own
 * player's four bytes from there into 0x79c4a8, which its code reads.  How
 * far the queue may run ahead of the frames taken (its lead, 0x7d573c, and
 * a remote player's, 0x7d5738, 0x7d3710) the race's mode sets: one frame
 * ahead of what is taken in one player's race, more over the network.  The
 * frames the race may run, 0x560104, counted up as frames are queued.
 *
 * Written as their code is: each push and pop to the guest's stack, each call
 * with the return address's slot, the frame's locals in the guest's memory,
 * the registers as the code leaves them, a dword copied as the code copies
 * it (movsd, then movsb for none).  The two switches on the race's mode go by
 * the targets nfs3.exe's tables hold (0x4c6514, 0x4c6a2c, 0x4c6acc).  The
 * network's packets sent (0x4a60e0), a machine's player found (0x4a6650), and
 * the critical section's Windows functions are called by address. */
namespace nfs3hp
{
namespace controls
{

namespace
{

using guest::at;
using guest::byte;
using guest::put;
using guest::putByte;
using x86::reg32;
using x86::reg8;
using x86::sreg32;

// The race's frame as its screens see it (0x79c4ac as the frame began); the
// actions' and the function keys' rings of 32 frames of bits; a function
// key's frames held unchanged.
constexpr reg32 kScreenFrame = 0x7d3688;
constexpr reg32 kActionRing = 0x79c238, kFunctionKeyRing = 0x79c2b8;
constexpr reg32 kRepeatFrames = 0x79c4b0;
// The keys' state, a byte each by scan code, and whether each was pressed
// already, a byte each (0xff) up to 0x80.
constexpr reg32 kKeys = 0x564818, kKeysPressed = 0x79c1b8, kKeyCount = 0x80;
// The car's four bytes, taken from the queue; its buttons' byte; the
// players' buttons held the frame before, a byte each.
constexpr reg32 kCarControls = 0x79c4a8, kCarButtons = 0x79c4ab;
constexpr reg32 kButtonsBefore = 0x79c1b0;
// The buttons that count once as pressed, not while held: 0x02, 0x10, 0x20,
// 0x40, 0x80; and those a frame repeated for a player missing keeps.
constexpr reg32 kPressedButtons = 0xf2, kRepeatedButtons = 0x8d;
constexpr reg32 kMenuUp = 0x10, kMenuDown = 0x20;
// The queue.
constexpr reg32 kQueue = 0x7d3714, kQueueButtons = 0x7d3717, kQueued = 0x7d4714;
constexpr reg32 kFramesTaken = 0x7d5714, kFramesQueued = 0x7d5718, kSecondQueued = 0x7d571c;
constexpr reg32 kTaken = 0x7d36f0;
constexpr reg32 kRemoteLead = 0x7d3710, kRemoteDelay = 0x7d5738, kQueueLead = 0x7d573c, kLag = 0x7d5740;
constexpr reg32 kFrameMask = 0x7f, kPlayerShift = 9;
// The race.
constexpr reg32 kGameMode = 0x6fd3b0;        // 0 one player, 1 two on one screen, 2-4 over a network
constexpr reg32 kReplay = 0x6fd3a0;          // more than 1: a replay
constexpr reg32 kPlayer = 0x6fd4f4;          // this machine's player
constexpr reg32 kPlayers = 0x6fd514;
constexpr reg32 kOwnOnly = 0x6fd50c;         // nonzero: only this machine's player queued here
constexpr reg32 kRaceFrames = 0x560104;      // the frames the race may run
constexpr reg32 kQueueStopped = 0x560108;
constexpr reg32 kStarting = 0x56010c;
constexpr reg32 kTakingPackets = 0x560100;
// The network: its kind (1 the host's side or a client's of one, 2 two
// machines), this machine its host, the connection lost; its lock; the
// packet of this machine's input -- 6, its lead, its four bytes; the packet
// being built, its length and its start.
constexpr reg32 kNetworkKind = 0x7a22e4, kNetworkHost = 0x7a22da;
constexpr reg32 kConnectionLost = 0x7a22dc, kConnectionLostToo = 0x7a22de;
constexpr reg32 kNetworkLock = 0x7d36d8;
constexpr reg32 kInputPacket = 0x7d36e4, kInputPacketLead = 0x7d36e5, kInputPacketControls = 0x7d36e6;
constexpr reg32 kInputPacketType = 6, kInputPacketBytes = 6, kAllInputsBytes = 0x21;
constexpr reg32 kPacketLength = 0x7d36d0, kPacketStart = 0x7d36d4;
// What is called by address.
constexpr reg32 kEnterCriticalSection = 0x5344b8, kLeaveCriticalSection = 0x534588;
constexpr reg32 kSend = 0x4a60e0, kPlayerOf = 0x4a6650;

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

/* The four bytes from esi to edi, as the code copies them. */
void copyFour(win32::WinApplication* app, x86::CPU& cpu)
{
    cpu.ecx = 4;
    copyBytes(app, cpu);
}

/* pop ebp, pop edi, pop esi, pop ecx, pop ebx, ret. */
void popEbpEdiEsiEcxEbx(win32::WinApplication* app, x86::CPU& cpu)
{
    cpu.ebp = pop(app, cpu);
    cpu.edi = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4;
}

/* pop ebp, pop edi, pop esi, pop edx, pop ecx, pop ebx, ret. */
void popEbpEdiEsiEdxEcxEbx(win32::WinApplication* app, x86::CPU& cpu)
{
    cpu.ebp = pop(app, cpu);
    cpu.edi = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4;
}

/* pop ebp, pop esi, pop ecx, pop ebx, ret. */
void popEbpEsiEcxEbx(win32::WinApplication* app, x86::CPU& cpu)
{
    cpu.ebp = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4;
}

}  // namespace

void takeCarControls(win32::WinApplication* app, x86::CPU& cpu);
void stepMenuChoice(win32::WinApplication* app, x86::CPU& cpu);
void stepMenuChoiceOfThree(win32::WinApplication* app, x86::CPU& cpu);
void actionPressed(win32::WinApplication* app, x86::CPU& cpu);
void functionKeyPressed(win32::WinApplication* app, x86::CPU& cpu);
void pressFunctionKey(win32::WinApplication* app, x86::CPU& cpu);
void functionKeyRepeats(win32::WinApplication* app, x86::CPU& cpu);
void keyPressed(win32::WinApplication* app, x86::CPU& cpu);
void firstFunctionKeyHeld(win32::WinApplication* app, x86::CPU& cpu);
void appendToPacket(win32::WinApplication* app, x86::CPU& cpu);
void sendOwnInput(win32::WinApplication* app, x86::CPU& cpu);
void receiveInput(win32::WinApplication* app, x86::CPU& cpu);
void queueInput(win32::WinApplication* app, x86::CPU& cpu);
void queueRemoteInput(win32::WinApplication* app, x86::CPU& cpu);
void takeQueuedFrame(win32::WinApplication* app, x86::CPU& cpu);
void takenControls(win32::WinApplication* app, x86::CPU& cpu);
void repeatMissingInputs(win32::WinApplication* app, x86::CPU& cpu);
void syncFrame(win32::WinApplication* app, x86::CPU& cpu);
void framesTaken(win32::WinApplication* app, x86::CPU& cpu);
void framesQueued(win32::WinApplication* app, x86::CPU& cpu);
void queueLead(win32::WinApplication* app, x86::CPU& cpu);
void noteLag(win32::WinApplication* app, x86::CPU& cpu);
void setQueueDelays(win32::WinApplication* app, x86::CPU& cpu);
void queueFull(win32::WinApplication* app, x86::CPU& cpu);

/* 0x48f6a0: the car of player eax given its four bytes for the frame
 * (0x79c4a8, from those taken, takenControls); of its buttons, those of
 * 0xf2 count only the frame they are pressed -- held the frame before
 * (0x79c1b0 by player), they are cleared.  eax left the buttons of 0xf2
 * held. */
void takeCarControls(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.ecx = cpu.eax;
    cpu.edx = kCarControls;
    if (!direct(app, cpu, takenControls))
        return;
    cpu.edx = 0;
    cpu.al = byte(app, kCarButtons);
    cpu.dl = byte(app, cpu.ecx + kButtonsBefore);
    cpu.al &= kPressedButtons;
    cpu.edx = ~cpu.edx;
    putByte(app, cpu.ecx + kButtonsBefore, cpu.al);
    putByte(app, kCarButtons, byte(app, kCarButtons) & cpu.dl);
    cpu.ebp = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x48f6e0: choice al of edx stepped by the first player's buttons: one on
 * with 0x10 if not the last (edx less one, which edx is left), one back with
 * 0x20 if not the first. */
void stepMenuChoice(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.ah = byte(app, kCarButtons);
    if (cpu.ah & kMenuUp)
    {
        cpu.ecx = 0;
        --cpu.edx;
        cpu.cl = cpu.al;
        if (sreg32(cpu.ecx) < sreg32(cpu.edx))
            ++cpu.al;
    }
    else if ((cpu.ah & kMenuDown) && cpu.al != 0)
    {
        --cpu.al;
    }
    cpu.ebp = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x48f710: choice al of three stepped by the first player's buttons: 0x10
 * 0 to 1, 1 to 2; 0x20 1 to 0, any past 1 to 1. */
void stepMenuChoiceOfThree(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.ah = byte(app, kCarButtons);
    if (cpu.ah & kMenuUp)
    {
        if (cpu.al == 0)
            cpu.al = 1;
        else if (cpu.al == 1)
            cpu.al = 2;
    }
    else if (cpu.ah & kMenuDown)
    {
        if (cpu.al == 1)
            cpu.al = 0;
        else if (cpu.al > 1)
            cpu.al = 1;
    }
    cpu.ebp = pop(app, cpu);
    cpu.esp += 4;
}

namespace
{

/* actionPressed and functionKeyPressed: 1 if bit al of the ring's slot for
 * the screens' frame is set -- and, edx nonzero, was not the frame before --
 * else 0; edx left the bit. */
void bitPressed(win32::WinApplication* app, x86::CPU& cpu, reg32 ring)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.ebx = cpu.edx;
    cpu.edx = 1;
    cpu.esi = at(app, kScreenFrame);
    cpu.cl = cpu.al;
    cpu.esi &= 0x1f;
    cpu.edx <<= cpu.cl & 0x1f;
    cpu.eax = cpu.esi * 4;
    bool pressed;
    if (cpu.ebx != 0)
    {
        cpu.ecx = at(app, cpu.eax + ring);
        cpu.eax = at(app, kScreenFrame);
        --cpu.eax;
        cpu.eax &= 0x1f;
        cpu.eax = at(app, cpu.eax * 4 + ring);
        cpu.edx &= cpu.ecx;
        cpu.eax = ~cpu.eax;
        pressed = (cpu.edx & cpu.eax) != 0;
    }
    else
    {
        pressed = (at(app, cpu.eax + ring) & cpu.edx) != 0;
    }
    cpu.eax = pressed ? 1 : 0;
    popEbpEsiEcxEbx(app, cpu);
}

}  // namespace

/* 0x48f740: whether action al (a bit of the actions' ring, 0x79c238) is held
 * at the screens' frame (edx 0), or was pressed in it (edx nonzero). */
void actionPressed(win32::WinApplication* app, x86::CPU& cpu)
{
    bitPressed(app, cpu, kActionRing);
}

/* 0x48f7b0: whether function key al (a bit of their ring, 0x79c2b8) is held
 * at the screens' frame (edx 0), or was pressed in it (edx nonzero). */
void functionKeyPressed(win32::WinApplication* app, x86::CPU& cpu)
{
    bitPressed(app, cpu, kFunctionKeyRing);
}

/* 0x48f820: function key al held at the screens' frame and the one before:
 * held, not pressed, so that it counts as pressed no more.  eax left its
 * bit. */
void pressFunctionKey(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.ebx = at(app, kScreenFrame);
    cpu.cl = cpu.al;
    cpu.edx = cpu.ebx - 1;
    cpu.eax = 1;
    cpu.edx &= 0x1f;
    cpu.eax <<= cpu.cl & 0x1f;
    put(app, cpu.edx * 4 + kFunctionKeyRing, at(app, cpu.edx * 4 + kFunctionKeyRing) | cpu.eax);
    cpu.edx = cpu.ebx;
    cpu.edx &= 0x1f;
    put(app, cpu.edx * 4 + kFunctionKeyRing, at(app, cpu.edx * 4 + kFunctionKeyRing) | cpu.eax);
    cpu.ebp = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x48f860: 1 if function key al is held at the screens' frame and the
 * function keys changed since the frame before, or have not for more than
 * edx frames (counted at 0x79c4b0, from 0 again as it answers 1); else 0. */
void functionKeyRepeats(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.esi = at(app, kRepeatFrames);
    cpu.ecx = at(app, kScreenFrame);
    cpu.ecx &= 0x1f;
    cpu.ebx = cpu.ecx * 4;
    cpu.cl = cpu.al;
    cpu.eax = 1;
    cpu.eax <<= cpu.cl & 0x1f;
    bool repeats = false;
    if ((at(app, cpu.ebx + kFunctionKeyRing) & cpu.eax) != 0)
    {
        cpu.eax = at(app, kScreenFrame);
        cpu.ecx = cpu.eax - 1;
        cpu.eax &= 0x1f;
        cpu.ecx &= 0x1f;
        cpu.eax = at(app, cpu.eax * 4 + kFunctionKeyRing);
        if (cpu.eax != at(app, cpu.ecx * 4 + kFunctionKeyRing))
        {
            repeats = true;
        }
        else
        {
            cpu.eax = cpu.esi;
            ++cpu.esi;
            repeats = sreg32(cpu.eax) > sreg32(cpu.edx);
        }
    }
    if (repeats)
    {
        cpu.eax = 1;
        cpu.esi = 0;
    }
    else
    {
        cpu.eax = 0;
    }
    put(app, kRepeatFrames, cpu.esi);
    popEbpEsiEcxEbx(app, cpu);
}

/* 0x48f8d0: whether key eax (a scan code under 0x80) is held (edx 0), or was
 * pressed since it was last asked (edx nonzero): its byte at 0x79c1b8 0xff
 * as it says so, cleared once the key is let go. */
void keyPressed(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    const auto answer = [&](reg32 result) {
        cpu.eax = result;
        cpu.ebp = pop(app, cpu);
        cpu.ebx = pop(app, cpu);
        cpu.esp += 4;
    };
    if (sreg32(cpu.eax) >= sreg32(kKeyCount))
        return answer(0);
    cpu.bl = byte(app, cpu.eax + kKeys);
    cpu.bh = byte(app, cpu.eax + kKeysPressed);
    cpu.bh &= cpu.bl;
    putByte(app, cpu.eax + kKeysPressed, cpu.bh);
    if (cpu.edx == 0)
        return answer(cpu.bl != 0 ? 1 : 0);
    if (cpu.bl == 0 || cpu.bh != 0)
        return answer(0);
    putByte(app, cpu.eax + kKeysPressed, 0xff);
    answer(1);
}

/* 0x48f920: whether the first function key (bit 0, no key's -- only what
 * pressFunctionKey sets) is held at the screens' frame. */
void firstFunctionKeyHeld(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.eax = at(app, kScreenFrame);
    cpu.eax &= 0x1f;
    cpu.eax = at(app, cpu.eax * 4 + kFunctionKeyRing);
    cpu.eax &= 1;
    cpu.ebp = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x4c6080: a packet's ebx bytes but its first (its type) at edx appended to
 * the packet being built ([0x7d36d4] on, [0x7d36d0] long so far).  eax and
 * edx left the bytes appended, ebx the packet's start. */
void appendToPacket(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.esi = cpu.edx;
    cpu.edi = at(app, kPacketLength);
    cpu.edx = cpu.ebx - 1;
    ++cpu.esi;
    cpu.ebx = at(app, kPacketStart);
    cpu.ecx = cpu.edx;
    cpu.edi += cpu.ebx;
    copyBytes(app, cpu);
    put(app, kPacketLength, at(app, kPacketLength) + cpu.edx);
    cpu.ebp = pop(app, cpu);
    cpu.edi = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x4c60c0: this machine's four bytes at eax in a race over the network.
 * The host of several (0x7a22e4 1, 0x7a22da set) queues them under the
 * network's lock and, unless only its own are queued here, sends every
 * player's for the frame -- those missing repeated (repeatMissingInputs) --
 * as a packet of 6 and 32 bytes.  Otherwise they are queued (only this
 * machine's queued here: nothing more), and sent as a packet of 6, the
 * queue's lead and the four bytes -- a client of a host's sent even if they
 * were not queued, which it leaves to the host. */
void sendOwnInput(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.esp -= 0x24;
    const reg32 ebp = cpu.ebp;
    cpu.esi = cpu.eax;
    const auto leave = [&] {
        cpu.esp = cpu.ebp;
        popEbpEdiEsiEdxEcxEbx(app, cpu);
    };
    if (at(app, kNetworkKind) == 1 && app->getMemory<x86::reg16>(kNetworkHost) != 0)
    {
        cpu.ecx = at(app, kNetworkLock);
        cpu.ah = kInputPacketType;
        push(app, cpu, cpu.ecx);
        putByte(app, ebp - 0x24, cpu.ah);
        if (!byAddress(app, cpu, at(app, kEnterCriticalSection)))
            return;
        cpu.eax = at(app, kPlayer);
        cpu.edx = cpu.esi;
        if (!direct(app, cpu, queueInput))
            return;
        if (cpu.eax == 0)
        {
            cpu.ebx = at(app, kNetworkLock);
            push(app, cpu, cpu.ebx);
            if (!byAddress(app, cpu, at(app, kLeaveCriticalSection)))
                return;
            return leave();
        }
        if (at(app, kOwnOnly) != 0)
        {
            cpu.edi = at(app, kNetworkLock);
            push(app, cpu, cpu.edi);
            if (!byAddress(app, cpu, at(app, kLeaveCriticalSection)))
                return;
            return leave();
        }
        cpu.eax = ebp - 0x23;
        if (!direct(app, cpu, repeatMissingInputs))
            return;
        cpu.eax = at(app, kNetworkLock);
        push(app, cpu, cpu.eax);
        cpu.ebx = kAllInputsBytes;
        if (!byAddress(app, cpu, at(app, kLeaveCriticalSection)))
            return;
        cpu.edx = ebp - 0x24;
    }
    else
    {
        cpu.edx = at(app, kOwnOnly);
        if (cpu.edx != 0)
        {
            cpu.eax = at(app, kPlayer);
            cpu.edx = cpu.esi;
            if (!direct(app, cpu, queueInput))
                return;
            return leave();
        }
        if (!direct(app, cpu, queueLead))
            return;
        cpu.ecx = at(app, kNetworkKind);
        putByte(app, kInputPacketLead, cpu.al);
        if (cpu.ecx == 0)
        {
            cpu.eax = at(app, kPlayer);
            cpu.edx = cpu.esi;
            if (!direct(app, cpu, queueInput))
                return;
            if (cpu.eax == 0)
                return leave();
        }
        cpu.dl = kInputPacketType;
        cpu.ecx = 4;
        cpu.edi = kInputPacketControls;
        cpu.ebx = kInputPacketBytes;
        putByte(app, kInputPacket, cpu.dl);
        copyBytes(app, cpu);
        cpu.edx = kInputPacket;
    }
    cpu.eax = 0;
    if (!byAddress(app, cpu, kSend))
        return;
    leave();
}

/* 0x4c61e0: a packet of 6 at edx from machine eax, while packets are taken
 * (0x560100).  A client of a host's queues every player's four bytes from
 * it, the last player's first; otherwise the sender's lag (its second byte)
 * is noted, and its four bytes queued for its player -- the host's, under
 * the network's lock, by the player the machine is (0x4a6650), filling a
 * gap; two machines', for the other player.  ebx and edx left as the code
 * leaves them. */
void receiveInput(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.esi = cpu.eax;
    const auto leave = [&] {
        cpu.ebp = pop(app, cpu);
        cpu.edi = pop(app, cpu);
        cpu.esi = pop(app, cpu);
        cpu.ecx = pop(app, cpu);
        cpu.esp += 4;
    };
    if (at(app, kTakingPackets) == 0)
        return leave();
    if (app->getMemory<x86::reg16>(kNetworkHost) == 0 && at(app, kNetworkKind) == 1)
    {
        cpu.ebx = at(app, kPlayers);
        cpu.esi = cpu.edx;
        for (;;)
        {
            --cpu.ebx;
            if (sreg32(cpu.ebx) < 0)
                return leave();
            cpu.edx = cpu.ebx * 4;
            cpu.eax = cpu.esi + 1;
            cpu.edx += cpu.eax;
            cpu.eax = cpu.ebx;
            if (!direct(app, cpu, queueInput))
                return;
        }
    }
    cpu.eax = reg32(sreg32(x86::sreg8(byte(app, cpu.edx + 1))));
    if (!direct(app, cpu, noteLag))
        return;
    cpu.ebx = cpu.edx + 2;
    cpu.edi = at(app, kNetworkKind);
    if (cpu.edi == 1)
    {
        cpu.eax = at(app, kNetworkLock);
        push(app, cpu, cpu.eax);
        if (!byAddress(app, cpu, at(app, kEnterCriticalSection)))
            return;
        cpu.eax = cpu.esi;
        if (!byAddress(app, cpu, kPlayerOf))
            return;
        cpu.edx = cpu.ebx;
        cpu.eax = reg32(sreg32(x86::sreg16(cpu.ax)));
        if (!direct(app, cpu, queueRemoteInput))
            return;
        cpu.edx = at(app, kNetworkLock);
        push(app, cpu, cpu.edx);
        if (!byAddress(app, cpu, at(app, kLeaveCriticalSection)))
            return;
        return leave();
    }
    cpu.ecx = at(app, kPlayer);
    cpu.edx = cpu.ebx;
    cpu.eax = cpu.ecx == 0 ? 1 : 0;
    if (!direct(app, cpu, queueInput))
        return;
    leave();
}

/* 0x4c6530: player eax's four bytes at edx queued for its next frame, if the
 * queue is not too far ahead (queueFull) and that frame's slot is free; 1 if
 * they were, else 0.  The connection lost stops the queue; a slot not free
 * in a race over the network loses it.  The frames the race may run counted
 * by the mode: one each in one player's race; one for each of the second
 * player's on one screen; over the network, this machine's alone queued
 * here, one for each of its own; the host's side, one for each of player 0's
 * on a client; otherwise the fewer of the first two players' frames, less
 * one. */
void queueInput(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.esp -= 8;
    const reg32 ebp = cpu.ebp;
    const auto answer = [&](reg32 result) {
        cpu.eax = result;
        cpu.esp = cpu.ebp;
        popEbpEdiEsiEcxEbx(app, cpu);
    };
    cpu.ebx = cpu.eax;
    cpu.eax <<= 2;
    cpu.cx = app->getMemory<x86::reg16>(kConnectionLost);
    cpu.edi = at(app, cpu.eax + kFramesQueued);
    put(app, ebp - 4, cpu.eax);
    cpu.edi &= kFrameMask;
    if (cpu.cx != 0)
    {
        cpu.edx = 1;
        put(app, kQueueStopped, cpu.edx);
        return answer(0);
    }
    cpu.eax = cpu.ebx;
    if (!direct(app, cpu, queueFull))
        return;
    if (cpu.eax != 0)
        return answer(0);
    cpu.eax = cpu.ebx;
    cpu.edi <<= 2;
    cpu.eax <<= kPlayerShift;
    cpu.ecx = cpu.eax + cpu.edi;
    cpu.esi = at(app, cpu.ecx + kQueued);
    put(app, ebp - 8, cpu.ecx);
    if (cpu.esi != 0)
    {
        if (sreg32(at(app, kGameMode)) > 1)
        {
            cpu.esi = 1;
            app->getMemory<x86::reg16>(kConnectionLostToo) = cpu.si;
            app->getMemory<x86::reg16>(kConnectionLost) = cpu.si;
        }
        return answer(0);
    }
    cpu.ecx = 4;
    cpu.eax += kQueue;
    cpu.esi = cpu.edx;
    cpu.edi += cpu.eax;
    copyBytes(app, cpu);
    cpu.eax = at(app, ebp - 8);
    cpu.edi = 1;
    put(app, cpu.eax + kQueued, cpu.edi);
    cpu.eax = at(app, ebp - 4);
    put(app, cpu.eax + kFramesQueued, at(app, cpu.eax + kFramesQueued) + cpu.edi);
    cpu.eax = at(app, kGameMode);
    if (cpu.eax > 4)
        return answer(1);
    // The table at 0x4c6514, by the mode.
    static const reg32 targets[5] = {0x4c6689, 0x4c6672, 0x4c6608, 0x4c6608, 0x4c6608};
    switch (targets[cpu.eax])
    {
    case 0x4c6689:
        put(app, kRaceFrames, at(app, kRaceFrames) + cpu.edi);
        return answer(1);
    case 0x4c6672:
        if (cpu.ebx == 0)
            return answer(1);
        put(app, kRaceFrames, at(app, kRaceFrames) + 1);
        return answer(1);
    default:
        break;
    }
    if (at(app, kOwnOnly) != 0 && cpu.ebx == at(app, kPlayer))
    {
        put(app, kRaceFrames, at(app, kRaceFrames) + 1);
        return answer(1);
    }
    cpu.eax = at(app, kNetworkKind);
    if (cpu.eax == 1)
    {
        if (cpu.ebx != 0)
            return answer(1);
        if (at(app, kPlayer) == 0)
            return answer(1);
        put(app, kRaceFrames, at(app, kRaceFrames) + cpu.eax);
        return answer(1);
    }
    cpu.edx = at(app, kFramesQueued);
    cpu.eax = at(app, kSecondQueued);
    if (sreg32(cpu.edx) < sreg32(cpu.eax))
        cpu.eax = cpu.edx;
    --cpu.eax;
    put(app, kRaceFrames, cpu.eax);
    answer(1);
}

/* 0x4c66a0: a remote player eax's four bytes at edx queued on the host,
 * unless the queue is too far ahead or the slot is taken.  A player more
 * than its lead (0x7d3710) ahead of player 0 has a frame dropped first: its
 * count one back, its frames from player 0's on moved back by one. */
void queueRemoteInput(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.esp -= 8;
    const reg32 ebp = cpu.ebp;
    const auto leave = [&] {
        cpu.esp = cpu.ebp;
        popEbpEdiEsiEcxEbx(app, cpu);
    };
    cpu.ebx = cpu.eax;
    put(app, ebp - 4, cpu.edx);
    cpu.edx = cpu.eax * 4;
    cpu.ecx = at(app, cpu.edx + kFramesQueued);
    if (!direct(app, cpu, queueFull))
        return;
    cpu.ecx &= kFrameMask;
    if (cpu.eax != 0)
        return leave();
    cpu.esi = cpu.ebx;
    cpu.esi <<= kPlayerShift;
    cpu.eax = at(app, cpu.esi + cpu.ecx * 4 + kQueued);
    if (cpu.eax != 0)
        return leave();
    cpu.esi = at(app, kRemoteLead);
    cpu.eax = at(app, kFramesQueued);
    cpu.edi = at(app, cpu.edx + kFramesQueued);
    cpu.eax += cpu.esi;
    if (sreg32(cpu.eax) < sreg32(cpu.edi))
    {
        cpu.eax = cpu.edi - 1;
        put(app, cpu.edx + kFramesQueued, cpu.eax);
        cpu.edx = at(app, kFramesQueued);
        for (;;)
        {
            cpu.eax = cpu.ebx * 4;
            cpu.ecx = at(app, cpu.eax + kFramesQueued);
            if (sreg32(cpu.edx) >= sreg32(cpu.ecx))
                break;
            cpu.eax = cpu.edx + 1;
            cpu.eax &= kFrameMask;
            cpu.esi = cpu.eax * 4;
            cpu.ecx = 4;
            cpu.eax = cpu.ebx;
            cpu.edi = cpu.edx;
            cpu.eax <<= kPlayerShift;
            cpu.edi &= kFrameMask;
            cpu.eax += kQueue;
            cpu.edi <<= 2;
            cpu.esi += cpu.eax;
            cpu.edi += cpu.eax;
            ++cpu.edx;
            copyBytes(app, cpu);
        }
        cpu.ecx &= kFrameMask;
    }
    cpu.edx = cpu.ebx;
    cpu.eax = kQueue;
    cpu.edx <<= kPlayerShift;
    cpu.ecx <<= 2;
    cpu.eax += cpu.edx;
    put(app, ebp - 8, cpu.ecx);
    cpu.edi = cpu.ecx + cpu.eax;
    cpu.esi = at(app, ebp - 4);
    copyFour(app, cpu);
    cpu.edx += at(app, ebp - 8);
    cpu.edi = 1;
    put(app, cpu.edx + kQueued, cpu.edi);
    put(app, cpu.ebx * 4 + kFramesQueued, at(app, cpu.ebx * 4 + kFramesQueued) + cpu.edi);
    leave();
}

/* 0x4c67a0: frame eax taken from the queue, but in a replay: each player's
 * four bytes into 0x7d36f0 (only this machine's player's if only its own are
 * queued here), every player's slot freed, the frames taken counted. */
void takeQueuedFrame(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.ebx = cpu.eax;
    cpu.edx = at(app, kReplay);
    cpu.ebx &= kFrameMask;
    if (sreg32(cpu.edx) <= 1)
    {
        for (cpu.edx = 0; sreg32(cpu.edx) < sreg32(at(app, kPlayers)); ++cpu.edx)
        {
            if (at(app, kOwnOnly) != 0 && cpu.edx != at(app, kPlayer))
                continue;
            cpu.eax = cpu.edx;
            cpu.esi = kQueue;
            cpu.eax <<= kPlayerShift;
            cpu.esi += cpu.eax;
            cpu.eax = cpu.ebx * 4;
            cpu.edi = kTaken;
            cpu.esi += cpu.eax;
            cpu.eax = cpu.edx * 4;
            cpu.ecx = 4;
            cpu.edi += cpu.eax;
            copyBytes(app, cpu);
        }
        for (cpu.eax = 0; sreg32(cpu.eax) < sreg32(at(app, kPlayers));)
        {
            cpu.esi = cpu.eax;
            cpu.ecx = 0;
            cpu.esi <<= kPlayerShift;
            ++cpu.eax;
            put(app, cpu.esi + cpu.ebx * 4 + kQueued, cpu.ecx);
        }
        put(app, kFramesTaken, at(app, kFramesTaken) + 1);
    }
    cpu.ebp = pop(app, cpu);
    cpu.edi = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x4c6840: player eax's four bytes taken for the frame (0x7d36f0) copied
 * to edx. */
void takenControls(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.esi = kTaken;
    cpu.ecx = 4;
    cpu.eax <<= 2;
    cpu.edi = cpu.edx;
    cpu.esi += cpu.eax;
    copyBytes(app, cpu);
    cpu.ebp = pop(app, cpu);
    cpu.edi = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x4c6870: player 0's last frame queued made every player's: a player
 * whose slot for it is free has it queued with the four bytes of its frame
 * before, the buttons that count once as pressed cleared (0x8d kept); each
 * player's four bytes for it copied to eax, a dword each.  The frames the
 * race may run counted. */
void repeatMissingInputs(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.esp -= 0xc;
    const reg32 ebp = cpu.ebp;
    put(app, ebp - 4, cpu.eax);
    cpu.ebx = at(app, kFramesQueued);
    --cpu.ebx;
    cpu.edx = 0;
    cpu.ebx &= kFrameMask;
    for (; sreg32(cpu.edx) < sreg32(at(app, kPlayers)); ++cpu.edx)
    {
        cpu.edi = cpu.edx;
        cpu.eax = cpu.ebx * 4;
        cpu.edi <<= kPlayerShift;
        cpu.edi += cpu.eax;
        if (at(app, cpu.edi + kQueued) == 0)
        {
            cpu.eax = at(app, cpu.edx * 4 + kFramesQueued);
            ++cpu.eax;
            cpu.ecx = 1;
            put(app, cpu.edx * 4 + kFramesQueued, cpu.eax);
            put(app, cpu.edi + kQueued, cpu.ecx);
            cpu.ecx = 4;
            cpu.eax = cpu.ebx != 0 ? cpu.ebx - 1 : kFrameMask;
            cpu.eax &= kFrameMask;
            cpu.esi = cpu.eax * 4;
            cpu.eax = cpu.edx;
            cpu.eax <<= kPlayerShift;
            put(app, ebp - 0xc, cpu.eax);
            cpu.eax = kQueue;
            cpu.eax += at(app, ebp - 0xc);
            cpu.edi = cpu.ebx * 4;
            cpu.esi += cpu.eax;
            put(app, ebp - 8, cpu.edi);
            cpu.edi += cpu.eax;
            copyBytes(app, cpu);
            cpu.eax = at(app, ebp - 0xc);
            cpu.eax += at(app, ebp - 8);
            putByte(app, cpu.eax + kQueueButtons, byte(app, cpu.eax + kQueueButtons) & kRepeatedButtons);
        }
        cpu.eax = cpu.edx;
        cpu.esi = kQueue;
        cpu.eax <<= kPlayerShift;
        cpu.esi += cpu.eax;
        cpu.eax = cpu.ebx * 4;
        cpu.edi = at(app, ebp - 4);
        cpu.esi += cpu.eax;
        cpu.eax = cpu.edx * 4;
        cpu.ecx = 4;
        cpu.edi += cpu.eax;
        copyBytes(app, cpu);
    }
    put(app, kRaceFrames, at(app, kRaceFrames) + 1);
    cpu.esp = cpu.ebp;
    popEbpEdiEsiEdxEcxEbx(app, cpu);
}

/* 0x4c6970: the frame the machines are to meet at, sent over the network:
 * player 0's frames queued and two more; 0 on a client of a host's. */
void syncFrame(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    if (at(app, kPlayer) != 0 && at(app, kNetworkKind) != 0)
        cpu.eax = 0;
    else
        cpu.eax = at(app, kFramesQueued) + 2;
    cpu.ebp = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x4c69a0: the frames taken from the queue. */
void framesTaken(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.eax = at(app, kFramesTaken);
    cpu.ebp = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x4c69b0: player 0's frames queued. */
void framesQueued(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.eax = at(app, kFramesQueued);
    cpu.ebp = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x4c69c0: in al, the queue's lead sent with this machine's input: on two
 * machines (0x7a22e4 0) the other player's frames queued less this
 * machine's player's, else player 0's frames queued less those taken -- a
 * byte, the rest of eax as it was there. */
void queueLead(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    if (at(app, kNetworkKind) == 0)
    {
        cpu.eax = at(app, kPlayer) == 0 ? 1 : 0;
        cpu.edx = at(app, kPlayer);
        cpu.al = byte(app, cpu.eax * 4 + kFramesQueued);
        cpu.al -= byte(app, cpu.edx * 4 + kFramesQueued);
    }
    else
    {
        cpu.dl = byte(app, kFramesTaken);
        cpu.al = byte(app, kFramesQueued);
        cpu.al -= cpu.dl;
    }
    cpu.ebp = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x4c6a10: a machine's lag eax noted: the byte at 0x7d5740 the greatest
 * yet; eax left it (eax itself if greater). */
void noteLag(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.edx = 0;
    cpu.dl = byte(app, kLag);
    if (sreg32(cpu.eax) <= sreg32(cpu.edx))
        cpu.eax = cpu.edx;
    putByte(app, kLag, cpu.al);
    cpu.ebp = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x4c6a40: the queue's delays by the race's mode -- the lead it may run
 * ahead of the frames taken (0x7d573c), the delay a remote player's may
 * (0x7d5738), the lead a remote player may have on player 0 (0x7d3710):
 * 4 ahead on one machine, two players 4 and 4; over the network 8 and 0x10
 * (mode 2), and in mode 4 by the network's kind: 8, 0x10 and 2; 0x20, 0x20
 * and 4; 0x10, 0x20 and 0x10.  Any other mode leaves them. */
void setQueueDelays(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.edx = at(app, kQueueLead);
    cpu.ecx = at(app, kRemoteDelay);
    cpu.ebx = at(app, kRemoteLead);
    cpu.eax = at(app, kGameMode);
    if (cpu.eax <= 4)
    {
        // The table at 0x4c6a2c, by the mode.
        static const reg32 targets[5] = {0x4c6aaf, 0x4c6aaf, 0x4c6a79, 0x4c6aa6, 0x4c6a69};
        switch (targets[cpu.eax])
        {
        case 0x4c6a69:
            cpu.edx = at(app, kNetworkKind);
            if (cpu.edx == 1)
            {
                cpu.ebx = 2;
                cpu.ecx = 0x10;
                cpu.edx = 8;
            }
            else if (cpu.edx == 2)
            {
                cpu.edx = 0x20;
                cpu.ebx = 4;
                cpu.ecx = cpu.edx;
            }
            else
            {
                cpu.edx = 0x10;
                cpu.ecx = 0x20;
                cpu.ebx = cpu.edx;
            }
            break;
        case 0x4c6a79:
            cpu.ecx = 0x10;
            cpu.edx = 8;
            break;
        case 0x4c6aa6:
            cpu.edx = 4;
            cpu.ecx = cpu.edx;
            break;
        case 0x4c6aaf:
            cpu.edx = 4;
            break;
        }
    }
    put(app, kRemoteLead, cpu.ebx);
    put(app, kRemoteDelay, cpu.ecx);
    put(app, kQueueLead, cpu.edx);
    cpu.ebp = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x4c6ae0: 1 if player eax's queue is as far ahead of the frames taken as
 * it may be (the lead, 0x7d573c), so that no more is queued, else 0.  One
 * player's race asks of player 0's frames only, two on one screen of the
 * first's (the second's always 0).  Over the network: with only this
 * machine's queued here, 0 -- the code compares the frames and goes on
 * whatever they say; the host's side (kind 1) with player 0 on it, also as
 * the race starts, and its lag (0x7d5740) halved instead of the answer while
 * more than the remote delay; otherwise, this machine's player only, its lag
 * halved over 4 instead, and the fewer of the first two players' frames
 * compared. */
void queueFull(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.bl = byte(app, kLag);
    cpu.esi = at(app, kQueueLead);
    cpu.edx = at(app, kGameMode);
    const auto answer = [&](reg32 result) {
        cpu.eax = result;
        put(app, kQueueLead, cpu.esi);
        putByte(app, kLag, cpu.bl);
        popEbpEdiEsiEdxEcxEbx(app, cpu);
    };
    // Player 0's frames as far ahead of those taken as the lead allows.
    const auto aheadOfTaken = [&] {
        cpu.eax = at(app, kFramesTaken);
        cpu.edx = at(app, kFramesQueued);
        cpu.eax += cpu.esi;
        return answer(sreg32(cpu.eax) > sreg32(cpu.edx) ? 0 : 1);
    };
    if (cpu.edx > 4)
        return answer(0);
    // The table at 0x4c6acc, by the mode.
    static const reg32 targets[5] = {0x4c6c26, 0x4c6c22, 0x4c6b0a, 0x4c6b0a, 0x4c6b0a};
    switch (targets[cpu.edx])
    {
    case 0x4c6c22:
        if (cpu.eax != 0)
            return answer(0);
        return aheadOfTaken();
    case 0x4c6c26:
        return aheadOfTaken();
    default:
        break;
    }
    cpu.ecx = at(app, kRemoteDelay);
    cpu.edx = at(app, kFramesTaken);
    cpu.edi = at(app, kOwnOnly);
    cpu.edx += cpu.ecx;
    cpu.ecx = cpu.eax * 4;
    if (cpu.edi != 0)
    {
        // cmp edx, [ecx + 0x7d5718], its answer not looked at.
        return answer(0);
    }
    cpu.edi = at(app, kNetworkKind);
    if (cpu.edi == 1)
    {
        if (at(app, kPlayer) != 0)
            return answer(0);
        if (at(app, kStarting) != 0 && cpu.eax != 0)
        {
            cpu.eax = cpu.edi;
            return answer(cpu.eax);
        }
        if (cpu.eax == 0)
        {
            cpu.edi = at(app, kRemoteDelay);
            cpu.al = cpu.bl;
            if (sreg32(cpu.eax) > sreg32(cpu.edi))
            {
                cpu.eax = reg32(sreg32(cpu.eax) >> 1);
                cpu.bl = cpu.al;
                return answer(1);
            }
        }
        return aheadOfTaken();
    }
    cpu.edi = at(app, kPlayer);
    if (cpu.eax != cpu.edi)
        return answer(0);
    cpu.eax ^= cpu.edi;
    cpu.al = cpu.bl;
    if (sreg32(cpu.eax) > 4)
    {
        cpu.bl >>= 1;
        return answer(1);
    }
    if (sreg32(cpu.edx) <= sreg32(at(app, cpu.ecx + kFramesQueued)))
        return answer(1);
    cpu.edx = at(app, kFramesQueued);
    cpu.eax = at(app, kSecondQueued);
    if (sreg32(cpu.edx) > sreg32(cpu.eax))
        cpu.edx = cpu.eax;
    cpu.eax = at(app, kFramesTaken);
    cpu.eax += cpu.esi;
    answer(sreg32(cpu.edx) < sreg32(cpu.eax) ? 0 : 1);
}

}  // namespace controls
}  // namespace nfs3hp
