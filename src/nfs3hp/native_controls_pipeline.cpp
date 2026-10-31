#include "native_guest.h"
#include <lib/touch_input.h>

/* The controls read and turned into the players' actions every frame of a
 * race.  disassemble_nfs3hp.py binds each address to the function of that
 * name here (CONTROLS_PIPELINE_NATIVES), and the generated code calls it by
 * name.  tools/game_checks holds each against its generated code.
 *
 * A control is a dword as the control sets have it (native_controls_
 * devices.cpp): its device's number in the top four bits, its kind in the low
 * byte -- 0 none, 1 an axis's half, 2 a button, 3 a hat's direction, 4 a key
 * -- and what of the device between.  As a race starts, the players' sets are
 * laid out by action into the race's table at 0x79c340: 12 actions the first
 * player's, 12 the second's (two on one screen), then the 32 function keys';
 * each joystick a control is on goes into the list at 0x5eff20 (device
 * numbers, bytes, up to a negative one).  Every frame each joystick listed is
 * read into its 0x84 bytes from 0x5eff30, and each player's actions made
 * four bytes at 0x79c338 (the second's at 0x79c33c): the steering, -0x7f
 * left to 0x7f right, the throttle, the brake, 0 to 0xff, and a bit each of 8
 * more actions; the function keys' 32 bits go into a ring of 32 at 0x79c2b8.
 * The four bytes are handed on to the race's queue of inputs (0x4c6530, the
 * network's 0x4c60c0), which feeds the cars.
 *
 * Written as their code is: each push and pop to the guest's stack, each call
 * with the return address's slot, the frame's locals in the guest's memory,
 * the registers as the code leaves them.  The kinds' functions are called
 * through the code's table at 0x554e34 as the code calls them; the joysticks'
 * reading (0x4358f0), the device sets (0x4904d0), the keys' state (0x4eb1c0)
 * and the queue are called by address. */
namespace nfs3hp
{
void fillZero(win32::WinApplication* app, x86::CPU& cpu);  // 0x4e070c, native_game.cpp

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

// The joysticks read: their list (bytes, up to a negative one), each one's
// 0x84 bytes -- a DIJOYSTATE, x at 0, y at 4, the buttons' bytes at 0x30;
// its axes at 0x50, its buttons as bits at 0x70, its hats at 0x74.
constexpr reg32 kPolled = 0x5eff20;
constexpr reg32 kJoysticks = 0x5eff30;
constexpr reg32 kJoystickBytes = 0x84;
constexpr reg32 kAllJoysticksBytes = 0x840;
constexpr reg32 kJoystickButtons = 0x5eff60, kJoystickAxes = 0x5eff80, kJoystickHats = 0x5effa4;
constexpr reg32 kJoystickHeld = 0x70;
// A joystick's arrows: the keys a joystick works when the race's menus are
// up -- 4 left, 8 right, 1 up, 2 down, 0x10 a button (Enter).
constexpr reg32 kJoystickArrows = 0x5f0770;
constexpr reg32 kLeftKey = 0x4b, kRightKey = 0x4d, kUpKey = 0x48, kDownKey = 0x50, kEnterKey = 0x1c;
constexpr reg32 kTabKey = 0xf;
// The keys' state, a byte each by scan code; the one keyDown clears.
constexpr reg32 kKeys = 0x564818;
constexpr reg32 kClearedKey = 0x56484f;
// The kinds' functions, by a control's kind.
constexpr reg32 kKinds = 0x554e34;
constexpr reg32 kAxis = 1, kKey = 4;
// The race's actions: each slot a control, from 0x79c340 -- the first
// player's 12, the second's 12, the 32 function keys' from 0x79c3a0 -- and
// the players' four bytes each from 0x79c338.
constexpr reg32 kSlots = 0x79c340, kSlotsBytes = 0x160;
constexpr reg32 kActions = 0x79c338, kSecondActions = 0x79c33c;
constexpr reg32 kFunctionKeys = 0x79c3a0, kFunctionKeyCount = 0x20;
constexpr reg32 kFunctionKeyRing = 0x79c2b8, kFunctionKeyFrame = 0x79c4ac;
constexpr reg32 kHeldBefore = 0x79c1b0, kHeldBeforeBytes = 8;
constexpr reg32 kFunctionKeyRingBytes = 0x80, kOtherRing = 0x79c238;
// Three function keys' slots that are number keys chosen in the options.
constexpr reg32 kNumberSlots[] = {0x79c3a8, 0x79c3ac, 0x79c3b0};
constexpr reg32 kNumberKeys[] = {0x6fbc04, 0x6fbc08, 0x6fbc0c};
// The race.
constexpr reg32 kGameMode = 0x6fd3b0;        // 1: two players on one screen
constexpr reg32 kSplitMode = 1;
constexpr reg32 kReplay = 0x6fd3a0;          // more than 1: a replay
constexpr reg32 kRaceMenu = 0x7d36a0;        // nonzero: the race's menus up
constexpr reg32 kRaceMenuToo = 0x7d36a8;
constexpr reg32 kReplayFrames = 0x560104;
constexpr reg32 kQueueStopped = 0x560108;
constexpr reg32 kPlayer = 0x6fd4f4;          // this machine's player
constexpr reg32 kSwapped = 0x6fd4c4;         // steering's halves the other way round
// What is called by address.
constexpr reg32 kReadJoystick = 0x4358f0, kControlsFor = 0x4904d0, kKeyState = 0x4eb1c0;
constexpr reg32 kQueueInput = 0x4c6530, kSendInput = 0x4c60c0;

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

/* movsx of a control's low byte: its kind. */
reg32 kindOf(reg32 control)
{
    return reg32(sreg32(control << 24) >> 24);
}

/* pop ebp, pop edx, ret: the end the control's functions share. */
void popEbpEdx(win32::WinApplication* app, x86::CPU& cpu)
{
    cpu.ebp = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.esp += 4;
}

/* pop ebp, pop edx, pop ecx, ret. */
void popEbpEdxEcx(win32::WinApplication* app, x86::CPU& cpu)
{
    cpu.ebp = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.esp += 4;
}

}  // namespace

void clearJoysticks(win32::WinApplication* app, x86::CPU& cpu);
void readJoysticks(win32::WinApplication* app, x86::CPU& cpu);
void pollJoystick(win32::WinApplication* app, x86::CPU& cpu);
void buttonHeld(win32::WinApplication* app, x86::CPU& cpu);
void hatPointing(win32::WinApplication* app, x86::CPU& cpu);
void axisAmount(win32::WinApplication* app, x86::CPU& cpu);
void keyHeld(win32::WinApplication* app, x86::CPU& cpu);
void controlHeld(win32::WinApplication* app, x86::CPU& cpu);
void controlHeldNo(win32::WinApplication* app, x86::CPU& cpu);
void controlHeldYes(win32::WinApplication* app, x86::CPU& cpu);
void controlHeldByKind(win32::WinApplication* app, x86::CPU& cpu);
void noControl(win32::WinApplication* app, x86::CPU& cpu);
void bindPlayersControls(win32::WinApplication* app, x86::CPU& cpu);
void startRaceControls(win32::WinApplication* app, x86::CPU& cpu);
void readRaceControls(win32::WinApplication* app, x86::CPU& cpu);
void bindControl(win32::WinApplication* app, x86::CPU& cpu);
void bindFunctionKeys(win32::WinApplication* app, x86::CPU& cpu);
void queueRaceControls(win32::WinApplication* app, x86::CPU& cpu);

/* 0x431580: no joystick read: their states cleared, their list empty. */
void clearJoysticks(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.edx = kAllJoysticksBytes;
    cpu.eax = kJoysticks;
    if (!direct(app, cpu, fillZero))
        return;
    putByte(app, kPolled, 0xff);
    popEbpEdx(app, cpu);
}

/* 0x4315a0: each joystick listed read into its state (0x4358f0), cleared if
 * it gives none; and, when the race's menus are up or a replay plays and Tab
 * is not held, the first joystick read made the menus' arrows and Enter
 * (0x5f0770): its x or y off its middle, a button held.  A joystick read
 * after the arrows were set adds none. */
void readJoysticks(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.edx = 0;
    cpu.ebx = kPolled;
    put(app, kJoystickArrows, cpu.edx);
    for (;; ++cpu.ebx)
    {
        cpu.ecx = kindOf(byte(app, cpu.ebx));
        if (sreg32(cpu.ecx) <= -1)
            break;
        cpu.eax = cpu.ecx;
        cpu.eax <<= 5;
        cpu.eax += cpu.ecx;
        cpu.edx = kJoysticks;
        cpu.eax <<= 2;
        cpu.edx += cpu.eax;
        cpu.eax = cpu.ecx;
        if (!byAddress(app, cpu, kReadJoystick))
            return;
        cpu.edx = cpu.eax;
        if (cpu.eax == 0)
        {
            // None read: its state cleared.
            cpu.edx = kindOf(byte(app, cpu.ebx));
            cpu.eax = cpu.edx;
            cpu.eax <<= 5;
            cpu.eax += cpu.edx;
            cpu.eax <<= 2;
            cpu.edx = kJoystickBytes;
            cpu.eax += kJoysticks;
            if (!direct(app, cpu, fillZero))
                return;
            continue;
        }
        if (at(app, kRaceMenu) == 0 && sreg32(at(app, kReplay)) < 2)
            continue;
        if (at(app, kJoystickArrows) != 0)
            continue;
        cpu.eax = kTabKey;
        if (!byAddress(app, cpu, kKeyState))
            return;
        if (cpu.eax != 0)
            continue;
        cpu.eax = at(app, cpu.edx);
        if (sreg32(cpu.eax) < 0x7f)
            putByte(app, kJoystickArrows, byte(app, kJoystickArrows) | 4);
        else if (sreg32(cpu.eax) > 0x17d)
            putByte(app, kJoystickArrows, byte(app, kJoystickArrows) | 8);
        cpu.esi = at(app, cpu.edx + 4);
        if (sreg32(cpu.esi) < 0x7f)
            putByte(app, kJoystickArrows, byte(app, kJoystickArrows) | 1);
        else if (sreg32(cpu.esi) > 0x7f)
            putByte(app, kJoystickArrows, byte(app, kJoystickArrows) | 2);
        if (at(app, cpu.edx + kJoystickHeld) != 0)
            putByte(app, kJoystickArrows, byte(app, kJoystickArrows) | 0x10);
    }
    cpu.ebp = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x431690: joystick eax put on the list of those read, if it is not on it
 * already. */
void pollJoystick(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.edx = cpu.eax;
    cpu.eax = kPolled;
    for (;; ++cpu.eax)
    {
        cpu.ecx = kindOf(byte(app, cpu.eax));
        if (sreg32(cpu.ecx) <= -1 || cpu.ecx == cpu.edx)
            break;
    }
    if (sreg32(kindOf(byte(app, cpu.eax))) < 0)
    {
        putByte(app, cpu.eax + 1, 0xff);
        putByte(app, cpu.eax, cpu.dl);
    }
    popEbpEdxEcx(app, cpu);
}

/* 0x4316c0: 0xff if control eax's button is held on its joystick, else 0. */
void buttonHeld(win32::WinApplication* app, x86::CPU& cpu)
{
    if(win32::touchinput::matches(cpu.eax,[app](reg32 address){return reg32(app->getMemory<reg32>(address));})) {
        cpu.eax=0xff;cpu.esp+=4;return;
    }

    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.edx = cpu.eax;
    cpu.eax >>= 0x1c;
    cpu.edx <<= 4;
    cpu.ecx = cpu.eax;
    cpu.eax <<= 5;
    cpu.edx >>= 0xc;
    cpu.eax += cpu.ecx;
    cpu.eax = byte(app, cpu.edx + cpu.eax * 4 + kJoystickButtons) != 0 ? 0xff : 0;
    popEbpEdxEcx(app, cpu);
}

/* 0x4316f0: 0xff if control eax's hat points its direction, else 0. */
void hatPointing(win32::WinApplication* app, x86::CPU& cpu)
{
    if(win32::touchinput::matches(cpu.eax,[app](reg32 address){return reg32(app->getMemory<reg32>(address));})) {
        cpu.eax=0xff;cpu.esp+=4;return;
    }

    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.edx = cpu.eax;
    cpu.eax >>= 0x1c;
    cpu.ecx = cpu.eax;
    cpu.eax <<= 5;
    cpu.ecx += cpu.eax;
    cpu.eax = cpu.edx;
    cpu.eax <<= 4;
    cpu.eax >>= 0x18;
    cpu.ecx <<= 2;
    cpu.eax <<= 2;
    cpu.ecx += cpu.eax;
    cpu.eax = cpu.edx;
    cpu.eax <<= 0xc;
    cpu.edx = at(app, cpu.ecx + kJoystickHats);
    cpu.eax >>= 0x14;
    cpu.eax = cpu.eax == cpu.edx ? 0xff : 0;
    popEbpEdxEcx(app, cpu);
}

/* 0x431740: how far control eax's axis is into its half, 0 to 0xff: the
 * axis's value over 0x100 from the half's start (bits 16-23) towards its end
 * (bits 8-15) doubled, 0xff past the end, 0 short of the start.  A half
 * starting at 0 gives the value undoubled, as does one ending at 0 from
 * 0xff -- the whole axis, a pedal's. */
void axisAmount(win32::WinApplication* app, x86::CPU& cpu)
{
    if(win32::touchinput::matches(cpu.eax,[app](reg32 address){return reg32(app->getMemory<reg32>(address));})) {
        cpu.eax=0xff;cpu.esp+=4;return;
    }

    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.ecx = cpu.eax;
    cpu.eax >>= 0x1c;
    cpu.edx = cpu.eax;
    cpu.eax <<= 5;
    cpu.edx += cpu.eax;
    cpu.eax = cpu.ecx;
    cpu.eax <<= 4;
    cpu.edx <<= 2;
    cpu.eax >>= 0x1c;
    cpu.eax = at(app, cpu.edx + cpu.eax * 4 + kJoystickAxes);
    cpu.edx = cpu.ecx;
    cpu.edx <<= 8;
    cpu.ecx <<= 0x10;
    cpu.edx >>= 0x18;
    cpu.ecx >>= 0x18;
    cpu.eax = reg32(sreg32(cpu.eax) >> 8);
    const auto none = [&] {
        cpu.eax = 0;
        popEbpEdxEcx(app, cpu);
    };
    if (sreg32(cpu.edx) < sreg32(cpu.ecx))
    {
        // The half rising from edx to ecx.
        if (sreg32(cpu.eax) < sreg32(cpu.edx))
            return none();
        if (sreg32(cpu.eax) > sreg32(cpu.ecx))
        {
            cpu.eax = 0xff;
            return popEbpEdxEcx(app, cpu);
        }
        if (cpu.edx == 0)
            return popEbpEdxEcx(app, cpu);
        cpu.eax -= cpu.edx;
        cpu.eax += cpu.eax;
        return popEbpEdxEcx(app, cpu);
    }
    if (cpu.edx == cpu.ecx)
        return none();
    // The half falling from edx to ecx.
    if (sreg32(cpu.eax) < sreg32(cpu.ecx))
    {
        cpu.eax = 0xff;
        return popEbpEdxEcx(app, cpu);
    }
    if (sreg32(cpu.eax) > sreg32(cpu.edx))
        return none();
    cpu.ecx = cpu.edx;
    cpu.ecx -= cpu.eax;
    cpu.eax = cpu.ecx;
    if (cpu.edx == 0xff)
        return popEbpEdxEcx(app, cpu);
    cpu.eax = cpu.ecx + cpu.ecx;
    popEbpEdxEcx(app, cpu);
}

/* 0x4317d0: 0xff if control eax's key is held, else 0.  Held, it clears
 * the state of key 0x37 (the keypad's *, Print Screen's) as it answers --
 * whichever key it is. */
void keyHeld(win32::WinApplication* app, x86::CPU& cpu)
{
    if(win32::touchinput::matches(cpu.eax,[app](reg32 address){return reg32(app->getMemory<reg32>(address));})) {
        cpu.eax=0xff;cpu.esp+=4;putByte(app,kClearedKey,0);return;
    }

    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.eax <<= 8;
    cpu.eax >>= 0x10;
    cpu.eax &= 0xff;
    if (byte(app, cpu.eax + kKeys) == 0)
    {
        cpu.eax = 0;
        return popEbpEdx(app, cpu);
    }
    cpu.dh = 0;
    cpu.eax = 0xff;
    putByte(app, kClearedKey, cpu.dh);
    popEbpEdx(app, cpu);
}

/* 0x431800: 0xff if control eax is held, else 0: a key held, or one of the
 * menus' arrows or Enter a joystick works (0x5f0770); an axis more than half
 * into its half; the others by their kind's function (0x554e34) --
 * controlHeldByKind, which the code jumps on to. */
void controlHeld(win32::WinApplication* app, x86::CPU& cpu)
{
    if(win32::touchinput::matches(cpu.eax,[app](reg32 address){return reg32(app->getMemory<reg32>(address));})) {
        cpu.eax=0xff;cpu.esp+=4;return;
    }

    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.edx = cpu.eax;
    cpu.edx = kindOf(cpu.edx);
    if (cpu.edx != kKey)
        return controlHeldByKind(app, cpu);
    cpu.eax <<= 8;
    cpu.eax >>= 0x10;
    cpu.dl = byte(app, cpu.eax + kKeys);
    if (cpu.dl != 0)
        return controlHeldYes(app, cpu);
    if (at(app, kJoystickArrows) == 0)
        return controlHeldNo(app, cpu);
    const reg8 arrows = byte(app, kJoystickArrows);
    if ((cpu.eax == kLeftKey && (arrows & 4)) || (cpu.eax == kRightKey && (arrows & 8))
        || (cpu.eax == kUpKey && (arrows & 1)) || (cpu.eax == kDownKey && (arrows & 2))
        || (cpu.eax == kEnterKey && (arrows & 0x10)))
        return controlHeldYes(app, cpu);
    controlHeldNo(app, cpu);
}

/* 0x431880: controlHeld's end, not held: 0, its frame left.  An entry of its
 * own in the disassembly, jumped to from controlHeldByKind. */
void controlHeldNo(win32::WinApplication* app, x86::CPU& cpu)
{
    cpu.eax = 0;
    popEbpEdx(app, cpu);
}

/* 0x431885: controlHeld's end, held: 0xff, its frame left.  An entry of its
 * own in the disassembly, which nothing jumps to by it. */
void controlHeldYes(win32::WinApplication* app, x86::CPU& cpu)
{
    cpu.eax = 0xff;
    popEbpEdx(app, cpu);
}

/* 0x43188d: controlHeld for control eax of a kind edx not a key, in its
 * frame: an axis held more than half into its half, the others what their
 * kind's function says. */
void controlHeldByKind(win32::WinApplication* app, x86::CPU& cpu)
{
    if (cpu.edx == kAxis)
    {
        if (!direct(app, cpu, axisAmount))
            return;
        if (sreg32(cpu.eax) <= 0x80)
            return controlHeldNo(app, cpu);
        cpu.eax = 0xff;
        return popEbpEdx(app, cpu);
    }
    if (!byAddress(app, cpu, at(app, kKinds + cpu.edx * 4)))
        return;
    popEbpEdx(app, cpu);
}

/* 0x4318b0: no control: 0. */
void noControl(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.eax = 0;
    cpu.ebp = pop(app, cpu);
    cpu.esp += 4;
}

namespace
{

/* mov eax, slot; mov edx, [from]; call bindControl -- in either order. */
bool bind(win32::WinApplication* app, x86::CPU& cpu, reg32 slot, reg32 from)
{
    cpu.edx = at(app, from);
    cpu.eax = slot;
    return direct(app, cpu, bindControl);
}

/* The rest of a player's set at `set` bound from slot `first`: the
 * throttle, the brake and the rest, two of them into the function keys'
 * slots -- in the code's order, the last two either way round. */
bool bindPlayerRest(win32::WinApplication* app, x86::CPU& cpu, reg32 first, reg32 set, bool lastSwapped)
{
    const reg32 slots[] = {2, 3, 0x2d, 0x2e, 6, 7, 8, 9, 5};
    const reg32 from[] = {8, 0xc, 0x24, 0x1c, 0x10, 0x20, 0x14, 0x18, 0x28};
    for (int i = 0; i < 9; ++i)
    {
        const reg32 slot = slots[i] < 0x2d ? first + slots[i] : slots[i] + (first ? 2 : 0);
        if (!bind(app, cpu, slot, set + from[i]))
            return false;
    }
    if (lastSwapped)
        return bind(app, cpu, first + 0xa, set + 0x30) && bind(app, cpu, first + 0xb, set + 0x2c);
    return bind(app, cpu, first + 0xb, set + 0x2c) && bind(app, cpu, first + 0xa, set + 0x30);
}

}  // namespace

/* 0x48f1f0: the race's table of actions (0x79c340) made from the players'
 * control sets (0x4904d0, by the mode): each player's 12 -- the steering's
 * halves the other way round if 0x6fd4c4 says so -- and their 4 function
 * keys; three function keys the number keys the options chose. */
void bindPlayersControls(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.eax = at(app, kGameMode);
    if (!byAddress(app, cpu, kControlsFor))
        return;
    cpu.edx = at(app, kGameMode);
    cpu.ebx = cpu.eax;
    cpu.ecx = cpu.eax;
    if (cpu.edx == kSplitMode)
    {
        cpu.edi = at(app, kSwapped);
        cpu.esi = 0;
        if (cpu.edi != 0)
        {
            if (!bind(app, cpu, 1, cpu.eax + 4))
                return;
            if (!bind(app, cpu, 0, cpu.ebx))
                return;
        }
        else
        {
            if (!bind(app, cpu, 0, cpu.eax + 4))
                return;
            if (!bind(app, cpu, 1, cpu.ebx))
                return;
        }
        cpu.eax = cpu.esi * 4;
        cpu.ebx = cpu.ecx + cpu.eax;
        if (!bindPlayerRest(app, cpu, 0, cpu.ebx, false))
            return;
        // The second player's, 13 slots on.
        cpu.esi = 0xd;
        cpu.eax = at(app, kSwapped);
        cpu.ebx = cpu.ecx + 0x34;
        if (cpu.eax != 0)
        {
            if (!bind(app, cpu, cpu.esi, cpu.ebx + 4))
                return;
            if (!bind(app, cpu, 0xc, cpu.ebx))
                return;
        }
        else
        {
            if (!bind(app, cpu, 0xc, cpu.ebx + 4))
                return;
            if (!bind(app, cpu, cpu.esi, cpu.ebx))
                return;
        }
        cpu.eax = cpu.esi * 4;
        cpu.ecx += cpu.eax;
        if (!bindPlayerRest(app, cpu, 0xc, cpu.ecx, false))
            return;
    }
    else
    {
        if (at(app, kSwapped) != 0)
        {
            if (!bind(app, cpu, 1, cpu.eax + 4))
                return;
            if (!bind(app, cpu, 0, cpu.ebx))
                return;
        }
        else
        {
            if (!bind(app, cpu, 0, cpu.eax + 4))
                return;
            if (!bind(app, cpu, 1, cpu.ebx))
                return;
        }
        if (!bindPlayerRest(app, cpu, 0, cpu.ecx, true))
            return;
    }
    // The number keys: the options' number less one, 9 for none, the key 2 on (1 to 0).
    for (int i = 0; i < 3; ++i)
    {
        cpu.eax = at(app, kNumberKeys[i]);
        if (cpu.eax != 0)
            --cpu.eax;
        else
            cpu.eax = 9;
        cpu.eax <<= 8;
        cpu.eax += 0x204;
        put(app, kNumberSlots[i], cpu.eax);
    }
    cpu.ebp = pop(app, cpu);
    cpu.edi = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x48f4f0: the race's controls as it starts: no joystick read, the
 * actions' table, the players' buttons held before, the function keys' ring
 * and another cleared; then the players' controls and the function keys
 * bound. */
void startRaceControls(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    if (!direct(app, cpu, clearJoysticks))
        return;
    const reg32 cleared[][2] = {{kSlotsBytes, kSlots},
                                {kHeldBeforeBytes, kHeldBefore},
                                {kFunctionKeyRingBytes, kFunctionKeyRing},
                                {kFunctionKeyRingBytes, kOtherRing}};
    for (const auto& c : cleared)
    {
        cpu.edx = c[0];
        cpu.eax = c[1];
        if (!direct(app, cpu, fillZero))
            return;
    }
    if (!direct(app, cpu, bindPlayersControls))
        return;
    if (!direct(app, cpu, bindFunctionKeys))
        return;
    popEbpEdx(app, cpu);
}

/* 0x48f550: a frame of the race's controls: the joysticks read; each
 * player's four bytes (0x79c338, the second's on) made from the table of
 * actions -- the steering the right half's amount less the left's, halved;
 * the throttle's, the brake's amounts; a bit each of the next 8 held -- then
 * the function keys' 32 bits into their ring; and handed on
 * (queueRaceControls). */
void readRaceControls(win32::WinApplication* app, x86::CPU& cpu)
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
    if (!direct(app, cpu, readJoysticks))
        return;
    cpu.ebx = kActions;
    cpu.esi = kKinds;
    cpu.edx = kSlots;
    cpu.edi = 0;
    // call [esi + kind*4] with eax the control at edx + `offset`.
    auto byKind = [&](reg32 offset) {
        cpu.eax = at(app, cpu.edx + offset);
        cpu.eax = kindOf(cpu.eax);
        cpu.eax <<= 2;
        cpu.ecx = cpu.esi + cpu.eax;
        cpu.eax = at(app, cpu.edx + offset);
        return byAddress(app, cpu, at(app, cpu.ecx));
    };
    for (;;)
    {
        // The steering, the throttle, the brake.
        if (!byKind(0))
            return;
        put(app, ebp - 0xc, cpu.eax);
        if (!byKind(4))
            return;
        cpu.eax -= at(app, ebp - 0xc);
        cpu.eax = reg32(sreg32(cpu.eax) >> 1);
        putByte(app, cpu.ebx, cpu.al);
        if (!byKind(8))
            return;
        putByte(app, cpu.ebx + 1, cpu.al);
        cpu.eax = at(app, cpu.edx + 0xc);
        cpu.eax = kindOf(cpu.eax);
        cpu.edx += 4;
        cpu.eax <<= 2;
        cpu.ecx = cpu.esi + cpu.eax;
        cpu.eax = at(app, cpu.edx + 8);
        cpu.edx += 4;
        if (!byAddress(app, cpu, at(app, cpu.ecx)))
            return;
        putByte(app, cpu.ebx + 2, cpu.al);
        cpu.eax = 0;
        cpu.edx += 4;
        put(app, ebp - 8, cpu.eax);
        cpu.ah = 0;
        cpu.edx += 4;
        putByte(app, ebp - 4, cpu.ah);
        // The next 8 as bits.
        for (;;)
        {
            cpu.eax = at(app, cpu.edx);
            cpu.eax = kindOf(cpu.eax);
            if (cpu.eax != 0)
            {
                cpu.eax <<= 2;
                cpu.ecx = cpu.esi + cpu.eax;
                cpu.eax = at(app, cpu.edx);
                if (!byAddress(app, cpu, at(app, cpu.ecx)))
                    return;
                if (cpu.eax != 0)
                {
                    cpu.cl = byte(app, ebp - 8);
                    cpu.al = 1;
                    cpu.al = reg8(cpu.al << (cpu.cl & 0x1f));
                    putByte(app, ebp - 4, byte(app, ebp - 4) | cpu.al);
                }
            }
            cpu.eax = at(app, ebp - 8);
            ++cpu.eax;
            cpu.edx += 4;
            put(app, ebp - 8, cpu.eax);
            if (sreg32(at(app, ebp - 8)) >= 8)
                break;
        }
        cpu.ebx += 4;
        cpu.al = byte(app, ebp - 4);
        cpu.ecx = at(app, kGameMode);
        putByte(app, cpu.ebx - 1, cpu.al);
        if (cpu.ecx != kSplitMode)
        {
            cpu.edx += 0x30;
            break;
        }
        cpu.edi += cpu.ecx;
        if (sreg32(cpu.edi) >= 2)
            break;
    }
    // The function keys, a bit each.
    cpu.ebx = 0;
    cpu.esi = 0;
    for (;;)
    {
        cpu.eax = at(app, cpu.edx);
        cpu.eax = kindOf(cpu.eax);
        cpu.ebx >>= 1;
        if (cpu.eax != 0)
        {
            cpu.eax = at(app, cpu.edx);
            if (!direct(app, cpu, controlHeld))
                return;
            if (cpu.eax != 0)
                cpu.ebx |= 0x80000000;
        }
        ++cpu.esi;
        cpu.edx += 4;
        if (sreg32(cpu.esi) >= sreg32(kFunctionKeyCount))
            break;
    }
    cpu.eax = at(app, kFunctionKeyFrame);
    ++cpu.eax;
    cpu.edx = cpu.eax;
    cpu.edx &= 0x1f;
    put(app, kFunctionKeyFrame, cpu.eax);
    put(app, cpu.edx * 4 + kFunctionKeyRing, cpu.ebx);
    if (!direct(app, cpu, queueRaceControls))
        return;
    cpu.esp = cpu.ebp;
    cpu.ebp = pop(app, cpu);
    cpu.edi = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x48f940: control edx made the action eax's in the race's table, and its
 * joystick, if it is on one, read every frame. */
void bindControl(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    put(app, cpu.eax * 4 + kSlots, cpu.edx);
    cpu.eax = cpu.edx;
    cpu.eax = kindOf(cpu.eax);
    if (cpu.eax != 0 && cpu.eax != kKey)
    {
        cpu.eax = cpu.edx;
        cpu.eax >>= 0x1c;
        if (!direct(app, cpu, pollJoystick))
            return;
    }
    cpu.ebp = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x48f970: the function keys' own keys (0x79c3a0 on, the first none): Esc,
 * Tab, F3, F5 to F9, F11, F12, the keypad's + and -. */
void bindFunctionKeys(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.edx = 0x104;
    cpu.ecx = 0x5804;
    cpu.ebx = 0x5704;
    cpu.esi = 0x4e04;
    cpu.edi = 0x4a04;
    cpu.eax = 0xf04;
    put(app, kFunctionKeys + 0x04, cpu.edx);
    put(app, kFunctionKeys + 0x1c, cpu.ecx);
    put(app, kFunctionKeys + 0x20, cpu.ebx);
    put(app, kFunctionKeys + 0x3c, cpu.esi);
    put(app, kFunctionKeys + 0x40, cpu.edi);
    put(app, kFunctionKeys + 0x38, cpu.eax);
    cpu.edx = 0x3d04;
    cpu.ecx = 0x3f04;
    cpu.ebx = 0x4004;
    cpu.esi = 0x4104;
    cpu.edi = 0x4204;
    cpu.eax = 0x4304;
    put(app, kFunctionKeys + 0x24, cpu.edx);
    put(app, kFunctionKeys + 0x30, cpu.ecx);
    put(app, kFunctionKeys + 0x34, cpu.ebx);
    put(app, kFunctionKeys + 0x2c, cpu.esi);
    put(app, kFunctionKeys + 0x50, cpu.edi);
    cpu.edx = 0;
    put(app, kFunctionKeys + 0x48, cpu.eax);
    put(app, kFunctionKeys, cpu.edx);
    cpu.ebp = pop(app, cpu);
    cpu.edi = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x48fa10: the players' four bytes handed on to the race's queue of
 * inputs, which the cars take theirs from a frame at a time: both players'
 * on one screen (the second's only if the first's was taken), this
 * machine's player's alone, or -- in a race over the network -- sent too
 * (0x4c60c0).  Not while the queue is stopped; in a replay only the frames
 * counted, while the race's menus are not up. */
void queueRaceControls(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    if (sreg32(at(app, kReplay)) > 1)
    {
        if (at(app, kRaceMenu) == 0 && at(app, kRaceMenuToo) == 0)
            put(app, kReplayFrames, at(app, kReplayFrames) + 1);
        return popEbpEdx(app, cpu);
    }
    if (at(app, kQueueStopped) != 0)
        return popEbpEdx(app, cpu);
    cpu.eax = at(app, kGameMode);
    if (cpu.eax == kSplitMode)
    {
        cpu.edx = kActions;
        cpu.eax = 0;
        if (!byAddress(app, cpu, kQueueInput))
            return;
        if (cpu.eax == 0)
            return popEbpEdx(app, cpu);
        cpu.edx = kSecondActions;
        cpu.eax = 1;
        if (!byAddress(app, cpu, kQueueInput))
            return;
        return popEbpEdx(app, cpu);
    }
    if (cpu.eax == 0)
    {
        cpu.edx = kActions;
        cpu.eax = at(app, kPlayer);
        if (!byAddress(app, cpu, kQueueInput))
            return;
        return popEbpEdx(app, cpu);
    }
    cpu.eax = kActions;
    if (!byAddress(app, cpu, kSendInput))
        return;
    popEbpEdx(app, cpu);
}

}  // namespace controls
}  // namespace nfs3hp
