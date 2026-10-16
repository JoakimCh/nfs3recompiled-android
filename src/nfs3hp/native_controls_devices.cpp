#include "native_guest.h"

#include <initializer_list>
#include <iterator>

/* The control sets the game makes for the devices it knows by name.
 * disassemble_nfs3hp.py binds each address to the function of that name here
 * (CONTROLS_DEVICES_NATIVES), and the generated code calls it by name.
 *
 * A control set is 13 dwords, one an action -- steering either way, the
 * pedals, the hand brake, the gears, the view and the rest -- each the
 * device's number in its top four bits and what of it works the action
 * below: an axis's half (0x80ff01 and 0x7f0001 the first axis, 0x180ff01 and
 * 0x17f0001 the second, 0x280ff01 and 0x27f0001 the third), a button (2 +
 * 0x100 times its number), a key.  One player's set is at 0x6fd20c; when two
 * play on one screen, the first's is at 0x6fd240 and the second's after it.
 * The keyboard's defaults, the one player's and the two players' together,
 * are data in the code at 0x490430 and 0x490464 (which the disassembly takes
 * for a function, sub_490430: it is never called).
 *
 * Written as their code is: each push and pop to the guest's stack, each call
 * with the return address's slot, the frame's sets in the guest's memory,
 * the registers as the code leaves them.  The copy into the players' sets
 * (0x4ea4f0, the game's memmove: from eax to edx, ebx bytes) stays the game's
 * code, called by address.  tools/game_checks holds each against its
 * generated code. */
namespace nfs3hp
{
namespace watcom
{
void strstr(win32::WinApplication* app, x86::CPU& cpu);
}

namespace controls
{

namespace
{

using guest::at;
using guest::byte;
using guest::put;
using x86::reg32;

constexpr reg32 kSingleControls = 0x6fd20c;   // the one player's set
constexpr reg32 kSplitControls = 0x6fd240;    // the two players' on one screen, one after the other
constexpr reg32 kSecondControls = 0x6fd274;
constexpr reg32 kSetBytes = 0x34;             // 13 actions
constexpr reg32 kSplitMode = 1;               // the mode two play on one screen in
// Controllers: 0x88 bytes each from 0x6fc970: its kind (a DirectInput
// joystick's subtype: 2 a joystick, 4 a game pad), its name, its buttons (a
// bit each), whether it has a second axis.
constexpr reg32 kControllers = 0x6fc970;
constexpr reg32 kControllerName = 0x6fc974;
constexpr reg32 kControllerButtons = 0x6fc9a8;
constexpr reg32 kControllerAxes = 0x6fc9b0;
constexpr reg32 kJoystick = 2, kGamePad = 4;
// The keyboard's defaults (in the code's bytes).
constexpr reg32 kKeyboardSingle = 0x490430, kKeyboardSplit = 0x490464;
constexpr reg32 kCopy = 0x4ea4f0;             // memmove: from eax to edx, ebx bytes
// What of a controller works an action: below its number's four bits.
constexpr reg32 kFirstHigh = 0x80ff01, kFirstLow = 0x7f0001;    // the first axis's halves
constexpr reg32 kSecondLow = 0x17f0001, kSecondHigh = 0x180ff01;  // the second's
constexpr reg32 kButton0 = 2;                                 // + 0x100 a button
constexpr reg32 kKey = 0x45001204;                            // a key: 'E' (0x12), whatever the device

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

/* push the registers named, push ebp, mov ebp, esp, sub esp, `locals`; leave
 * it the other way round. */
void enter(win32::WinApplication* app, x86::CPU& cpu, std::initializer_list<reg32*> saved, reg32 locals)
{
    for (reg32* r : saved)
        push(app, cpu, *r);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.esp -= locals;
}

void leave(win32::WinApplication* app, x86::CPU& cpu, std::initializer_list<reg32*> saved)
{
    cpu.esp = cpu.ebp;
    cpu.ebp = pop(app, cpu);
    for (auto r = std::rbegin(saved); r != std::rend(saved); ++r)
        **r = pop(app, cpu);
    cpu.esp += 4;
}

/* rep movsd: ecx dwords from esi to edi. */
void copyDwords(win32::WinApplication* app, x86::CPU& cpu)
{
    const reg32 step = cpu.flags.df ? reg32(-4) : 4;
    for (; cpu.ecx != 0; --cpu.ecx)
    {
        put(app, cpu.edi, at(app, cpu.esi));
        cpu.esi += step;
        cpu.edi += step;
    }
}

/* ecx * 0x11 as the code makes it (shl 4, add): a controller's 0x88 bytes
 * over 8. */
reg32 seventeen(reg32 n)
{
    return (n << 4) + n;
}

}  // namespace

void controlsFor(win32::WinApplication* app, x86::CPU& cpu);
void setControls(win32::WinApplication* app, x86::CPU& cpu);
void controllerNamed(win32::WinApplication* app, x86::CPU& cpu);
void knownControllerControls(win32::WinApplication* app, x86::CPU& cpu);
void sideWinderGamePadControls(win32::WinApplication* app, x86::CPU& cpu);
void gravisGripControls(win32::WinApplication* app, x86::CPU& cpu);
void wingManForceControls(win32::WinApplication* app, x86::CPU& cpu);
void combatStickControls(win32::WinApplication* app, x86::CPU& cpu);
void sideWinderProControls(win32::WinApplication* app, x86::CPU& cpu);
void sideWinderWheelControls(win32::WinApplication* app, x86::CPU& cpu);
void steeringWheelControls(win32::WinApplication* app, x86::CPU& cpu);
void keyboardControls(win32::WinApplication* app, x86::CPU& cpu);
void gamePadControls(win32::WinApplication* app, x86::CPU& cpu);
void joystickControls(win32::WinApplication* app, x86::CPU& cpu);
void otherControllerControls(win32::WinApplication* app, x86::CPU& cpu);

/* 0x4904d0: the players' control sets in mode eax: the two players' on one
 * screen in mode 1, else the one player's. */
void controlsFor(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.eax = cpu.eax == kSplitMode ? kSplitControls : kSingleControls;
    cpu.ebp = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x4904f0: every player's controls in mode eax as they start: each player's
 * controller's -- its own player's: the first's, and in mode 1 the second's
 * -- by its name if the game knows it, else by its kind; the keyboard's for
 * a player with none, both players' in mode 1 when the first has none (and
 * then no more). */
void defaultControls(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.edx, &cpu.esi, &cpu.edi}, 0);
    auto done = [&] { leave(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.edx, &cpu.esi, &cpu.edi}); };
    cpu.ecx = cpu.eax;
    cpu.esi = 0;
    cpu.ebx = 0;
    for (;;)
    {
        cpu.eax = cpu.ecx == kSplitMode ? 2 : 1;
        if (x86::sreg32(cpu.esi) >= x86::sreg32(cpu.eax))
            return done();
        cpu.edi = seventeen(cpu.ebx) << 3;
        cpu.edx = at(app, cpu.edi + kControllers);
        if (cpu.edx != 0)
        {
            cpu.edx = cpu.ebx;
            cpu.eax = cpu.ecx;
            if (!direct(app, cpu, knownControllerControls))
                return;
            if (cpu.eax == 0)
            {
                cpu.eax = at(app, cpu.edi + kControllers);
                void (*byKind)(win32::WinApplication*, x86::CPU&) = cpu.eax == kGamePad   ? gamePadControls
                                                                    : cpu.eax == kJoystick ? joystickControls
                                                                                           : otherControllerControls;
                cpu.edx = cpu.ebx;
                cpu.eax = cpu.ecx;
                if (!direct(app, cpu, byKind))
                    return;
            }
        }
        else
        {
            if (cpu.ebx == 0)
                cpu.edx = 2;
            cpu.eax = cpu.ecx;
            if (!direct(app, cpu, keyboardControls))
                return;
            if (cpu.ecx == kSplitMode)
                return done();
        }
        ++cpu.ebx;
        ++cpu.esi;
    }
}

/* 0x4905b0: the control set at edx made the players' in mode eax: in mode 1
 * the first's (ebx 0), the second's (1) or -- two sets at edx -- both
 * (another); else the one player's. */
void setControls(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.ecx = cpu.eax;
    cpu.eax = cpu.edx;
    if (cpu.ecx == kSplitMode)
    {
        if (cpu.ebx == 0)
        {
            cpu.ebx = kSetBytes;
            cpu.edx = kSplitControls;
        }
        else if (cpu.ebx == 1)
        {
            cpu.ebx = kSetBytes;
            cpu.edx = kSecondControls;
        }
        else
        {
            cpu.ebx = 2 * kSetBytes;
            cpu.edx = kSplitControls;
        }
    }
    else
    {
        cpu.ebx = kSetBytes;
        cpu.edx = kSingleControls;
    }
    if (!byAddress(app, cpu, kCopy))
        return;
    cpu.ebp = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x490610: whether controller eax's name has the text at edx in it. */
void controllerNamed(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.ecx = cpu.eax;
    cpu.eax = (seventeen(cpu.eax) << 3) + kControllerName;
    if (!direct(app, cpu, watcom::strstr))
        return;
    if (cpu.eax != 0)
        cpu.eax = 1;
    cpu.ebp = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x490640: controller edx's controls in mode eax if the game knows it by its
 * name: whether it did. */
void knownControllerControls(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.ebx, &cpu.ecx}, 0);
    cpu.ebx = cpu.eax;
    cpu.ecx = cpu.edx;
    static void (*const known[])(win32::WinApplication*, x86::CPU&) = {
        sideWinderGamePadControls, gravisGripControls, wingManForceControls, sideWinderProControls,
        sideWinderWheelControls,   steeringWheelControls, combatStickControls};
    bool first = true;
    for (auto controls : known)
    {
        if (!first)
        {
            cpu.edx = cpu.ecx;
            cpu.eax = cpu.ebx;
        }
        first = false;
        if (!direct(app, cpu, controls))
            return;
        if (cpu.eax != 0)
        {
            cpu.eax = 1;
            break;
        }
    }
    leave(app, cpu, {&cpu.ebx, &cpu.ecx});
}

namespace
{

/* A known controller's set: the 13 actions' codes (below the device's four
 * bits; kKey as it is), controller edx's name to have `name` in it, made the
 * players' in mode eax -- the second's in mode 1 for any controller but the
 * first.  Whether it was that controller. */
void namedControls(win32::WinApplication* app, x86::CPU& cpu, const reg32 (&codes)[13], reg32 name)
{
    enter(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.esi}, kSetBytes);
    const reg32 ebp = cpu.ebp;
    cpu.esi = cpu.eax;
    cpu.ecx = cpu.edx;
    cpu.eax = cpu.edx << 28;
    for (reg32 i = 0; i < 12; ++i)
    {
        if (codes[i] == kKey)
            put(app, ebp - kSetBytes + 4 * i, kKey);
        else
        {
            cpu.edx = cpu.eax + codes[i];
            put(app, ebp - kSetBytes + 4 * i, cpu.edx);
        }
    }
    cpu.eax += codes[12];
    cpu.edx = name;
    put(app, ebp - 4, cpu.eax);
    cpu.eax = cpu.ecx;
    if (!direct(app, cpu, controllerNamed))
        return;
    if (cpu.eax != 0)
    {
        cpu.ebx = cpu.ecx != 0 ? 1 : 0;
        cpu.edx = ebp - kSetBytes;
        cpu.eax = cpu.esi;
        if (!direct(app, cpu, setControls))
            return;
        cpu.eax = 1;
    }
    leave(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.esi});
}

}  // namespace

/* 0x4906b0: a "Microsoft SideWinder game pad"'s set: steering on its first
 * axis, its buttons. */
void sideWinderGamePadControls(win32::WinApplication* app, x86::CPU& cpu)
{
    static const reg32 codes[13] = {kFirstHigh, kFirstLow, 0x2, 0x102, 0x202, 0x702, 0x602,
                                    0x302, 0x402, kKey, 0x902, 0x802, 0x502};
    namedControls(app, cpu, codes, 0x53bbe0);
}

/* 0x490770: a "Gravis GrIP"'s. */
void gravisGripControls(win32::WinApplication* app, x86::CPU& cpu)
{
    static const reg32 codes[13] = {kFirstHigh, kFirstLow, 0x2, 0x102, 0x202, 0x502, 0x402,
                                    0x302, 0x702, kKey, 0x902, 0x802, 0x602};
    namedControls(app, cpu, codes, 0x53bc00);
}

/* 0x490830: a "Logitech WingMan Force"'s: the pedals on its third axis's
 * halves. */
void wingManForceControls(win32::WinApplication* app, x86::CPU& cpu)
{
    static const reg32 codes[13] = {kFirstHigh, kFirstLow, 0x27f0001, 0x280ff01, 0x2, 0x102, 0x302,
                                    0x202, 0x802, 0x402, 0x702, 0x602, 0x502};
    namedControls(app, cpu, codes, 0x53bc0c);
}

/* 0x4908f0: a "CH F-16 Combat Stick"'s: the throttle on its second axis. */
void combatStickControls(win32::WinApplication* app, x86::CPU& cpu)
{
    static const reg32 codes[13] = {kFirstHigh, kFirstLow, kSecondLow, 0x2, kSecondHigh, 0x602, 0x702,
                                    0x402, 0x102, 0x302, 0x202, 0x802, 0x502};
    namedControls(app, cpu, codes, 0x53bc24);
}

/* 0x4909b0: a "Microsoft 3D SideWinder Pro"'s. */
void sideWinderProControls(win32::WinApplication* app, x86::CPU& cpu)
{
    static const reg32 codes[13] = {kFirstHigh, kFirstLow, 0x702, 0x602, 0x2, 0x202, 0x502,
                                    0x102, 0x802, kKey, 0x902, 0x402, 0x302};
    namedControls(app, cpu, codes, 0x53bc3c);
}

/* 0x490a70: a "Microsoft SideWinder Force Feedback Wheel"'s: the pedals on
 * its second axis. */
void sideWinderWheelControls(win32::WinApplication* app, x86::CPU& cpu)
{
    static const reg32 codes[13] = {kFirstHigh, kFirstLow, kSecondLow, kSecondHigh, 0x2, 0x702, 0x602,
                                    0x302, 0x102, kKey, 0x202, 0x402, 0x502};
    namedControls(app, cpu, codes, 0x53bc58);
}

/* 0x490b30: a "CH Steering Wheel"'s: the keyboard's set, and over it
 * steering and the pedals on its axes -- buttons 2 and 3 for the pedals
 * without a second -- the hand brake and the view on its first two buttons,
 * as it has them.  Whether it was one.  Its set is found from the
 * player's by the controller's number, the second player's past the one
 * player's when one plays (as the other kinds' are). */
void steeringWheelControls(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.esi, &cpu.edi}, 0);
    auto done = [&] { leave(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.esi, &cpu.edi}); };
    cpu.edi = cpu.eax;
    cpu.ecx = cpu.edx;
    if (!direct(app, cpu, controlsFor))
        return;
    cpu.edx = 0x53bc84;
    cpu.esi = cpu.eax;
    cpu.eax = cpu.ecx;
    if (!direct(app, cpu, controllerNamed))
        return;
    if (cpu.eax == 0)
        return done();
    cpu.edx = cpu.ecx;
    cpu.eax = cpu.edx * kSetBytes;
    cpu.esi += cpu.eax;
    if (cpu.ecx != 0)
        cpu.edx = 1;
    cpu.eax = cpu.edi;
    if (!direct(app, cpu, keyboardControls))
        return;
    cpu.eax = seventeen(cpu.ecx);
    if (at(app, cpu.eax * 8 + kControllerAxes) != 0)
    {
        cpu.eax = cpu.ecx << 28;
        cpu.edx = cpu.eax + kFirstHigh;
        cpu.eax += kFirstLow;
        put(app, cpu.esi, cpu.edx);
        put(app, cpu.esi + 4, cpu.eax);
    }
    cpu.eax = cpu.ecx << 4;
    cpu.edx = (cpu.ecx + cpu.eax) << 3;
    cpu.eax = cpu.ecx;
    cpu.ebx = at(app, cpu.edx + kControllerAxes);
    cpu.eax <<= 28;
    if (cpu.ebx != 0)
    {
        cpu.edx = cpu.eax + kSecondLow;
        cpu.eax += kSecondHigh;
    }
    else
    {
        cpu.edx = cpu.eax + 0x202;
        cpu.eax += 0x302;
    }
    put(app, cpu.esi + 8, cpu.edx);
    put(app, cpu.esi + 0xc, cpu.eax);
    cpu.eax = seventeen(cpu.ecx);
    if (byte(app, cpu.eax * 8 + kControllerButtons) & 1)
    {
        cpu.eax = (cpu.ecx << 28) + kButton0;
        put(app, cpu.esi + 0x10, cpu.eax);
    }
    cpu.eax = seventeen(cpu.ecx);
    if (byte(app, cpu.eax * 8 + kControllerButtons) & 2)
    {
        cpu.eax = (cpu.ecx << 28) + 0x102;
        put(app, cpu.esi + 0x1c, cpu.eax);
    }
    cpu.ebx = cpu.ecx != 0 ? 1 : 0;
    cpu.edx = cpu.esi;
    cpu.eax = cpu.edi;
    if (!direct(app, cpu, setControls))
        return;
    cpu.eax = 1;
    done();
}

/* 0x490c40: the keyboard's controls in mode eax: in mode 1 the two players'
 * defaults for both when edx is 2, else the one player's for the second
 * player; else the one player's for the one player. */
void keyboardControls(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.esp -= 0x9c;
    cpu.ebp -= 0xb2;  // the frame's sets at ebp+0x16 (two) and ebp+0x7e (one)
    cpu.ecx = kSetBytes / 4;
    cpu.edi = cpu.ebp + 0x7e;
    cpu.esi = kKeyboardSingle;
    copyDwords(app, cpu);
    cpu.ecx = 2 * kSetBytes / 4;
    cpu.edi = cpu.ebp + 0x16;
    cpu.esi = kKeyboardSplit;
    copyDwords(app, cpu);
    if (cpu.eax == kSplitMode)
    {
        if (cpu.edx == 2)
        {
            cpu.ebx = cpu.edx;
            cpu.edx = cpu.ebp + 0x16;
        }
        else
        {
            cpu.edx = cpu.ebp + 0x7e;
            cpu.ebx = cpu.eax;
        }
    }
    else
    {
        cpu.edx = cpu.ebp + 0x7e;
        cpu.ebx = 0;
    }
    if (!direct(app, cpu, setControls))
        return;
    cpu.esp = cpu.ebp + 0xb2;
    cpu.ebp = pop(app, cpu);
    cpu.edi = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4;
}

namespace
{

/* The start of the controls of a controller of a kind (edx) in mode eax: the
 * keyboard's set, its player's -- found by the controller's number from the
 * players' -- to ebx. */
bool kindControls(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.esi}, 0);
    cpu.esi = cpu.eax;
    cpu.ecx = cpu.edx;
    if (!direct(app, cpu, controlsFor))
        return false;
    cpu.ebx = cpu.eax;
    cpu.eax = cpu.edx * kSetBytes;
    cpu.ebx += cpu.eax;
    if (cpu.edx != 0)
        cpu.edx = 1;
    cpu.eax = cpu.esi;
    return direct(app, cpu, keyboardControls);
}

/* The controller's first axis steering, if it has a second (its set at ebx). */
void axisSteering(win32::WinApplication* app, x86::CPU& cpu)
{
    cpu.eax = seventeen(cpu.ecx);
    if (at(app, cpu.eax * 8 + kControllerAxes) != 0)
    {
        cpu.eax = cpu.ecx << 28;
        cpu.edx = cpu.eax + kFirstHigh;
        cpu.eax += kFirstLow;
        put(app, cpu.ebx, cpu.edx);
        put(app, cpu.ebx + 4, cpu.eax);
    }
}

/* And its second the pedals. */
void axisPedals(win32::WinApplication* app, x86::CPU& cpu)
{
    cpu.eax = seventeen(cpu.ecx);
    if (at(app, cpu.eax * 8 + kControllerAxes) != 0)
    {
        cpu.eax = cpu.ecx << 28;
        cpu.edx = cpu.eax + kSecondLow;
        cpu.eax += kSecondHigh;
        put(app, cpu.ebx + 8, cpu.edx);
        put(app, cpu.ebx + 0xc, cpu.eax);
    }
}

/* Its button `code` to the action at `slot`, if it has that button: bit
 * `mask` of its buttons' byte `part`. */
void button(win32::WinApplication* app, x86::CPU& cpu, reg32 part, x86::reg8 mask, reg32 code, reg32 slot)
{
    cpu.eax = seventeen(cpu.ecx);
    if (byte(app, cpu.eax * 8 + kControllerButtons + part) & mask)
    {
        cpu.eax = (cpu.ecx << 28) + code;
        put(app, cpu.ebx + slot, cpu.eax);
    }
}

/* Two buttons to the actions at 0x14 and 0x18 (the gears), if it has both:
 * the buttons' byte read into `held` (dl or dh). */
void buttonPair(win32::WinApplication* app, x86::CPU& cpu, x86::reg8& held, x86::reg8 first, x86::reg8 second,
                reg32 code)
{
    cpu.eax = seventeen(cpu.ecx) << 3;
    held = byte(app, cpu.eax + kControllerButtons);
    if ((held & first) && (held & second))
    {
        cpu.eax = cpu.ecx << 28;
        cpu.edx = cpu.eax + code;
        cpu.eax += code + 0x100;
        put(app, cpu.ebx + 0x14, cpu.edx);
        put(app, cpu.ebx + 0x18, cpu.eax);
    }
}

void kindDone(win32::WinApplication* app, x86::CPU& cpu)
{
    cpu.ebp = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4;
}

}  // namespace

/* 0x490cb0: a game pad's controls (kind 4), controller edx's in mode eax:
 * the keyboard's set, and over it steering on its first axis if it has a
 * second, the pedals and the hand brake on buttons 0 to 2, the gears on 3
 * and 4 if it has both, the others on 5 to 9 -- those it has. */
void gamePadControls(win32::WinApplication* app, x86::CPU& cpu)
{
    if (!kindControls(app, cpu))
        return;
    axisSteering(app, cpu);
    button(app, cpu, 0, 1, 0x2, 8);
    button(app, cpu, 0, 2, 0x102, 0xc);
    button(app, cpu, 0, 4, 0x202, 0x10);
    buttonPair(app, cpu, cpu.dh, 8, 0x10, 0x302);
    button(app, cpu, 0, 0x20, 0x502, 0x1c);
    button(app, cpu, 0, 0x40, 0x602, 0x20);
    button(app, cpu, 0, 0x80, 0x702, 0x28);
    button(app, cpu, 1, 1, 0x802, 0x2c);
    button(app, cpu, 1, 2, 0x902, 0x30);
    kindDone(app, cpu);
}

/* 0x490e30: a joystick's (kind 2): the keyboard's set, and over it steering
 * and the pedals on its axes if it has a second, the hand brake and the view
 * on buttons 0 and 1, the gears on 2 and 3 if it has both, the others on
 * 4, 7, 8 and 9 -- those it has. */
void joystickControls(win32::WinApplication* app, x86::CPU& cpu)
{
    if (!kindControls(app, cpu))
        return;
    axisSteering(app, cpu);
    axisPedals(app, cpu);
    button(app, cpu, 0, 1, 0x2, 0x10);
    button(app, cpu, 0, 2, 0x102, 0x1c);
    buttonPair(app, cpu, cpu.dl, 4, 8, 0x202);
    button(app, cpu, 0, 0x10, 0x402, 0x20);
    button(app, cpu, 0, 0x80, 0x702, 0x28);
    button(app, cpu, 1, 1, 0x802, 0x2c);
    button(app, cpu, 1, 2, 0x902, 0x30);
    kindDone(app, cpu);
}

/* 0x490fa0: any other controller's: as a joystick's, the others on buttons 4
 * to 7. */
void otherControllerControls(win32::WinApplication* app, x86::CPU& cpu)
{
    if (!kindControls(app, cpu))
        return;
    axisSteering(app, cpu);
    axisPedals(app, cpu);
    button(app, cpu, 0, 1, 0x2, 0x10);
    button(app, cpu, 0, 2, 0x102, 0x1c);
    buttonPair(app, cpu, cpu.dl, 4, 8, 0x202);
    button(app, cpu, 0, 0x10, 0x402, 0x20);
    button(app, cpu, 0, 0x20, 0x502, 0x28);
    button(app, cpu, 0, 0x40, 0x602, 0x2c);
    button(app, cpu, 0, 0x80, 0x702, 0x30);
    kindDone(app, cpu);
}

}  // namespace controls
}  // namespace nfs3hp
