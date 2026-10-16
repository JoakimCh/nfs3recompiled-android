#include "native_controls_host.h"
#include "native_guest.h"

#include <cstdint>
#include <initializer_list>
#include <iterator>

/* The game's side of DirectInput: the devices found and opened, the mouse, the
 * keyboard and the joysticks read, their force-feedback effects.
 * disassemble_nfs3hp.py binds each address to the function of that name here
 * (CONTROLS_INPUT_NATIVES), and the generated code calls it by name.
 *
 * Written as their code is, as native_frontend_text.cpp's: each push and pop
 * to the guest's stack, each call with the return address's slot, the
 * frames' locals in the guest's memory, the registers as the code leaves
 * them.  What the game asked of DirectInput -- DirectInputCreateA and each
 * method of its objects -- it asks of the port (controls::directInput,
 * native_controls_host.h), with the arguments the game's code pushes: there
 * is no DirectInput behind it, only the port's pads, mouse and keyboard.
 * Win32 is called through the imports' slots, the window's message
 * handlers' table and the pointer's placing by address.  tools/game_checks holds each against its generated code.
 *
 * The devices: 0 to 15 the joysticks, 0x10 all of them, 0x11 the mouse, 0x12
 * the keyboard, 0x13 every one.  A joystick's record, 0x88 bytes from
 * 0x5f1ff8: its kind (1 a stick, 2 a wheel, 4 a gamepad; bit 3 force
 * feedback), its product's name at 4, the buttons it has at 0x38 (a bit
 * each), its hats at 0x3c, its axes at 0x40, at 0x48 each axis's dead zone
 * and 100 less its saturation, in percent.  An effect's record, 0x88 bytes
 * from 0x5f28f0: the DIEFFECT DirectInput is handed, its type's parameters
 * at 0x34, its envelope's at 0x68, its direction at 0x78, whether it plays
 * at 0x80, its type at 0x84. */
namespace nfs3hp
{
void fillZero(win32::WinApplication* app, x86::CPU& cpu);
void AcquireWindow(win32::WinApplication* app, x86::CPU& cpu);

namespace watcom
{
void strncpy(win32::WinApplication* app, x86::CPU& cpu);
}

namespace controls
{

namespace
{

using guest::at;
using guest::byte;
using guest::put;
using guest::putByte;
using x86::reg32;
using x86::sreg32;

// DirectInput's objects: itself, the mouse's and the keyboard's devices, the
// mouse's event, the window's WM_SETCURSOR handler before ours.
constexpr reg32 kDirectInput = 0x554ee4, kMouse = 0x554ee8, kKeyboard = 0x554eec;
constexpr reg32 kMouseEvent = 0x554ef0, kOldSetCursor = 0x554ef4;
constexpr reg32 kJoystickCount = 0x554ef8, kEffectCount = 0x554efc;
constexpr reg32 kJoysticksLooked = 0x554f00;  // EnumDevices asked once
// The joysticks: their devices, 16; their records.
constexpr reg32 kJoysticks = 0x5f1fb8;
constexpr reg32 kJoystickRecords = 0x5f1ff8, kJoystickBytes = 0x88, kAllJoystickBytes = 0x880;
constexpr reg32 kJoystickName = 0x5f1ffc, kJoystickNameEnd = 0x5f202d;
constexpr reg32 kJoystickButtons = 0x5f2030, kJoystickHats = 0x5f2034, kJoystickAxes = 0x5f2038;
constexpr reg32 kJoystickResolution = 0x5f203c;  // 0x4b each
constexpr reg32 kJoystickDeadZone = 0x5f2040, kJoystickSaturation = 0x5f2044;  // 8 bytes an axis
// The effects: their objects, 30; their records; the axes they all share.
constexpr reg32 kEffects = 0x5f2878, kEffectRecords = 0x5f28f0;
constexpr reg32 kEffectAxes = 0x5f1fb0;
constexpr reg32 kEffectFlags = 0x5f28f4, kEffectDuration = 0x5f28f8, kEffectPeriod = 0x5f28fc;
constexpr reg32 kEffectGain = 0x5f2900, kEffectTrigger = 0x5f2904, kEffectRepeat = 0x5f2908;
constexpr reg32 kEffectAxisCount = 0x5f290c, kEffectAxisList = 0x5f2910, kEffectDirections = 0x5f2914;
constexpr reg32 kEffectEnvelope = 0x5f2918, kEffectParameterBytes = 0x5f291c, kEffectParameters = 0x5f2920;
constexpr reg32 kEffectEnvelopeValues = 0x5f2958, kEffectDirection = 0x5f2968, kEffectDirection2 = 0x5f296c;
constexpr reg32 kEffectPlaying = 0x5f2970, kEffectType = 0x5f2974;
// The game's tables: the effects' GUIDs by type, the hats' offsets, the axes'
// offsets, createEffect's jump table by type.
constexpr reg32 kEffectGuids = 0x434ea0, kHatOffsets = 0x434ed4, kAxisOffsets = 0x434ef4;
constexpr reg32 kParameterSizes = 0x435ed8;
// The mouse: the pointer's bounds and where it is, its buttons -- held in
// the low byte, let go since in the next -- its wheel, whether the buttons
// are swapped; the game's handler of the buttons let go.
constexpr reg32 kPointerLeft = 0x5f38e0, kPointerTop = 0x5f38e4;
constexpr reg32 kPointerRight = 0x5f38e8, kPointerBottom = 0x5f38ec;
constexpr reg32 kPointerX = 0x5f38f0, kPointerY = 0x5f38f4;
constexpr reg32 kButtons = 0x5f38f8, kButtonsLetGo = 0x5f38f9, kWheel = 0x5f38fc;
constexpr reg32 kButtonsSwapped = 0x5f3900;
constexpr reg32 kButtonHandler = 0x56446c;
// DirectInput's GUIDs and formats.
constexpr reg32 kSysMouse = 0x56b908, kDevice2Interface = 0x56b918;
constexpr reg32 kMouseFormat = 0x52f020, kJoystickFormat = 0x52f300;
// What is called.
constexpr reg32 kCloseHandle = 0x534488, kCreateEvent = 0x534494, kGetModuleHandle = 0x53454c;
constexpr reg32 kSetCursor = 0x534780, kShowCursor = 0x534794, kSwapMouseButton = 0x53479c;
constexpr reg32 kMessageHandler = 0x4cc660, kSetMessageHandler = 0x4cc6d0;  // the window's, by message
constexpr reg32 kPlacePointer = 0x435230;
constexpr reg32 kSetCursorMessage = 0x20;
// IDirectInputA's methods.
constexpr reg32 kRelease = 8, kCreateDevice = 0xc, kEnumDevices = 0x10;
// IDirectInputDevice2A's.
constexpr reg32 kQueryInterface = 0, kGetCapabilities = 0xc, kGetProperty = 0x14, kSetProperty = 0x18;
constexpr reg32 kAcquire = 0x1c, kUnacquire = 0x20, kGetDeviceState = 0x24, kGetDeviceData = 0x28;
constexpr reg32 kSetDataFormat = 0x2c, kSetEventNotification = 0x30, kSetCooperativeLevel = 0x34;
constexpr reg32 kGetObjectInfo = 0x38, kCreateEffect = 0x48, kSendForceFeedbackCommand = 0x58, kPoll = 0x64;
// IDirectInputEffect's.
constexpr reg32 kSetParameters = 0x18, kStart = 0x1c, kStop = 0x20, kDownload = 0x28, kUnload = 0x2c;
// The devices.
constexpr reg32 kAllJoysticks = 0x10, kTheMouse = 0x11, kTheKeyboard = 0x12, kEveryDevice = 0x13;
constexpr reg32 kInputLost = 0x8007001e, kNotAcquired = 0x8007000c;

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

void putHalf(win32::WinApplication* app, reg32 address, x86::reg16 value)
{
    app->getMemory<x86::reg16>(address) = value;
}

/* A call as the code makes it: the return address's slot, and esp as the
 * callee leaves it.  False when the game stopped in it. */
bool direct(win32::WinApplication* app, x86::CPU& cpu, void (*function)(win32::WinApplication*, x86::CPU&))
{
    cpu.esp -= 4;
    function(app, cpu);
    return !cpu.terminate;
}

using controls::directInput;
using controls::kCreate;
using controls::Object;

bool byAddress(win32::WinApplication* app, x86::CPU& cpu, reg32 target)
{
    cpu.esp -= 4;
    app->dynamic_call(target, cpu);
    return !cpu.terminate;
}

/* push ebp, mov ebp, esp after the registers named, and sub esp, `locals`;
 * mov esp, ebp and the pops the other way round, ret `popped`. */
void enter(win32::WinApplication* app, x86::CPU& cpu, std::initializer_list<reg32*> saved, reg32 locals)
{
    for (reg32* r : saved)
        push(app, cpu, *r);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.esp -= locals;
}

void leave(win32::WinApplication* app, x86::CPU& cpu, std::initializer_list<reg32*> saved, reg32 popped = 0)
{
    cpu.esp = cpu.ebp;
    cpu.ebp = pop(app, cpu);
    for (auto r = std::rbegin(saved); r != std::rend(saved); ++r)
        **r = pop(app, cpu);
    cpu.esp += 4 + popped;
}

/* rep movsd, then rep movsb of what is left: ecx bytes from esi to edi. */
void copyBytes(win32::WinApplication* app, x86::CPU& cpu)
{
    cpu.eax = cpu.ecx;
    cpu.ecx >>= 2;
    for (; cpu.ecx != 0; --cpu.ecx, cpu.esi += 4, cpu.edi += 4)
        put(app, cpu.edi, at(app, cpu.esi));
    cpu.cl = cpu.al;
    cpu.cl &= 3;
    for (; cpu.ecx != 0; --cpu.ecx, ++cpu.esi, ++cpu.edi)
        putByte(app, cpu.edi, byte(app, cpu.esi));
}

/* An effect's or a joystick's record: its number times 0x88, as the code
 * makes it (shl 4, add, shl 3). */
reg32 times17(reg32 n)
{
    return (n << 4) + n;
}

}  // namespace

void openMouse(win32::WinApplication* app, x86::CPU& cpu);
void setPointerBounds(win32::WinApplication* app, x86::CPU& cpu);
void describeJoystick(win32::WinApplication* app, x86::CPU& cpu);
void readAxisZone(win32::WinApplication* app, x86::CPU& cpu);
void resetForceFeedback(win32::WinApplication* app, x86::CPU& cpu);
void stopEffects(win32::WinApplication* app, x86::CPU& cpu);
void startEffect(win32::WinApplication* app, x86::CPU& cpu);
void downloadEffect(win32::WinApplication* app, x86::CPU& cpu);
void unloadEffect(win32::WinApplication* app, x86::CPU& cpu);
void setCooperativeLevel(win32::WinApplication* app, x86::CPU& cpu);
void acquireDevice(win32::WinApplication* app, x86::CPU& cpu);
void acquireResult(win32::WinApplication* app, x86::CPU& cpu);
void effectPlaying(win32::WinApplication* app, x86::CPU& cpu);
void axisProperty(win32::WinApplication* app, x86::CPU& cpu);

/* 0x434f20: DirectInput started, where it is not: the joysticks' records
 * cleared, their devices and the effects' none, DirectInputCreateA asked for
 * version 5, and the mouse opened (openMouse).  Nothing kept if it fails. */
void startDirectInput(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.edx, &cpu.esi, &cpu.edi}, 0);
    if (at(app, kDirectInput) == 0)
    {
        cpu.edx = kAllJoystickBytes;
        cpu.eax = kJoystickRecords;
        if (!direct(app, cpu, fillZero))
            return;
        cpu.edx = 0;
        do
        {
            cpu.eax = cpu.edx;
            cpu.ebx = 0x4b;
            cpu.eax <<= 4;
            cpu.ecx = 0;
            cpu.eax += cpu.edx;
            put(app, kJoysticks + cpu.edx * 4, cpu.ecx);
            ++cpu.edx;
            put(app, kJoystickResolution + cpu.eax * 8, cpu.ebx);
        } while (sreg32(cpu.edx) < 0x10);
        cpu.eax = 1;
        cpu.esi = 0;
        put(app, kEffects - 4 + cpu.eax * 4, cpu.esi);
        while (sreg32(cpu.eax) < 0x1e)
        {
            ++cpu.eax;
            cpu.esi = 0;
            put(app, kEffects - 4 + cpu.eax * 4, cpu.esi);
        }
        cpu.edi = 0;
        push(app, cpu, cpu.edi);
        push(app, cpu, kDirectInput);
        push(app, cpu, 0x500);
        push(app, cpu, cpu.edi);
        put(app, kJoystickCount, cpu.edi);
        if (!byAddress(app, cpu, at(app, kGetModuleHandle)))
            return;
        push(app, cpu, cpu.eax);
        if (!directInput(app, cpu, Object::DirectInput, kCreate))
            return;
        if (cpu.eax != 0)
            put(app, kDirectInput, cpu.edi);
        else if (!direct(app, cpu, openMouse))
            return;
    }
    leave(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.edx, &cpu.esi, &cpu.edi});
}

/* 0x434fd0: DirectInput stopped: the mouse let go and released (its event's
 * handle closed, though kept), the keyboard, each joystick, then DirectInput
 * itself; no joysticks. */
void stopDirectInput(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.edx, &cpu.esi, &cpu.edi}, 0);
    if (at(app, kDirectInput) != 0)
    {
        if (at(app, kMouse) != 0)
        {
            cpu.ebx = at(app, kMouseEvent);
            if (cpu.ebx != 0)
            {
                push(app, cpu, cpu.ebx);
                if (!byAddress(app, cpu, at(app, kCloseHandle)))
                    return;
            }
            cpu.eax = at(app, kMouse);
            push(app, cpu, cpu.eax);
            cpu.edx = at(app, cpu.eax);
            if (!directInput(app, cpu, Object::Device, kUnacquire))
                return;
            cpu.eax = at(app, kMouse);
            push(app, cpu, cpu.eax);
            cpu.edx = at(app, cpu.eax);
            cpu.edi = 0;
            if (!directInput(app, cpu, Object::Device, kRelease))
                return;
            put(app, kMouse, cpu.edi);
        }
        cpu.eax = at(app, kKeyboard);
        if (cpu.eax != 0)
        {
            push(app, cpu, cpu.eax);
            cpu.edx = at(app, cpu.eax);
            if (!directInput(app, cpu, Object::Device, kUnacquire))
                return;
            cpu.eax = at(app, kKeyboard);
            push(app, cpu, cpu.eax);
            cpu.edx = at(app, cpu.eax);
            if (!directInput(app, cpu, Object::Device, kRelease))
                return;
            cpu.edx = 0;
            put(app, kKeyboard, cpu.edx);
        }
        cpu.esi = 0;
        do
        {
            cpu.ebx = cpu.esi * 4;
            cpu.ecx = at(app, cpu.ebx + kJoysticks);
            if (cpu.ecx != 0)
            {
                push(app, cpu, cpu.ecx);
                cpu.edx = at(app, cpu.ecx);
                if (!directInput(app, cpu, Object::Device, kUnacquire))
                    return;
                cpu.eax = at(app, cpu.ebx + kJoysticks);
                push(app, cpu, cpu.eax);
                cpu.edx = at(app, cpu.eax);
                cpu.edi = 0;
                if (!directInput(app, cpu, Object::Device, kRelease))
                    return;
                put(app, cpu.ebx + kJoysticks, cpu.edi);
            }
            ++cpu.esi;
        } while (sreg32(cpu.esi) < 0x10);
        cpu.eax = at(app, kDirectInput);
        push(app, cpu, cpu.eax);
        cpu.edx = at(app, cpu.eax);
        if (!directInput(app, cpu, Object::DirectInput, kRelease))
            return;
        cpu.eax = 0;
        put(app, kDirectInput, cpu.eax);
    }
    cpu.edx = 0;
    put(app, kJoystickCount, cpu.edx);
    leave(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.edx, &cpu.esi, &cpu.edi});
}

/* 0x4350a0: the mouse opened, DirectInput started first if it is not: the
 * buttons' swap asked of Windows (and put back), the device made, its
 * format the mouse's, exclusive in the foreground, an event for its data
 * and a buffer of 32 events, the window's WM_SETCURSOR handler ours
 * (hideCursor, the old one kept); then acquired, the buttons and the wheel
 * none, the pointer's bounds the 640 by 480 screen.  1, or 0 when it fails. */
void openMouse(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.edx, &cpu.esi}, 0x14);
    const reg32 ebp = cpu.ebp;
    auto done = [&] { leave(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.edx, &cpu.esi}); };
    if (at(app, kDirectInput) == 0)
    {
        if (!direct(app, cpu, startDirectInput))
            return;
        if (at(app, kDirectInput) == 0)
        {
            cpu.eax = 0;
            return done();
        }
    }
    cpu.ebx = at(app, kMouse);
    if (cpu.ebx == 0)
    {
        push(app, cpu, 1);
        if (!byAddress(app, cpu, at(app, kSwapMouseButton)))
            return;
        if (cpu.eax != 0)
            put(app, kButtonsSwapped, 1);
        else
        {
            push(app, cpu, cpu.ebx);
            put(app, kButtonsSwapped, cpu.ebx);
            if (!byAddress(app, cpu, at(app, kSwapMouseButton)))
                return;
        }
        // CreateDevice(DirectInput, GUID_SysMouse, &the mouse, none)
        push(app, cpu, 0);
        push(app, cpu, kMouse);
        cpu.eax = at(app, kDirectInput);
        push(app, cpu, kSysMouse);
        cpu.edx = at(app, cpu.eax);
        push(app, cpu, cpu.eax);
        if (!directInput(app, cpu, Object::DirectInput, kCreateDevice))
            return;
        if (cpu.eax != 0)
        {
            cpu.eax = 0;
            return done();
        }
        push(app, cpu, kMouseFormat);
        cpu.eax = at(app, kMouse);
        push(app, cpu, cpu.eax);
        cpu.edx = at(app, cpu.eax);
        if (!directInput(app, cpu, Object::Device, kSetDataFormat))
            return;
        if (cpu.eax != 0)
        {
            cpu.eax = 0;
            return done();
        }
        cpu.edx = 5;  // DISCL_EXCLUSIVE | DISCL_FOREGROUND
        cpu.eax = kTheMouse;
        if (!direct(app, cpu, setCooperativeLevel))
            return;
        if (cpu.eax == 0)
            return done();
        for (int i = 0; i < 4; ++i)
            push(app, cpu, 0);
        if (!byAddress(app, cpu, at(app, kCreateEvent)))
            return;
        put(app, kMouseEvent, cpu.eax);
        if (cpu.eax == 0)
            return done();
        push(app, cpu, cpu.eax);
        cpu.edx = at(app, kMouse);
        push(app, cpu, cpu.edx);
        cpu.ecx = at(app, cpu.edx);
        if (!directInput(app, cpu, Object::Device, kSetEventNotification))
            return;
        if (cpu.eax != 0)
        {
            cpu.eax = 0;
            return done();
        }
        // SetProperty(the mouse, DIPROP_BUFFERSIZE, {0x14, 0x10, 0, DIPH_DEVICE, 32})
        cpu.eax = 0x14;
        cpu.edx = 0x10;
        cpu.esi = 0x20;
        cpu.ecx = 0;
        put(app, ebp - 0x14, cpu.eax);
        put(app, ebp - 0xc, cpu.ecx);
        put(app, ebp - 8, cpu.ecx);
        cpu.ecx = ebp - 0x14;
        put(app, ebp - 0x10, cpu.edx);
        push(app, cpu, cpu.ecx);
        cpu.eax = at(app, kMouse);
        put(app, ebp - 4, cpu.esi);
        push(app, cpu, 1);
        cpu.edx = at(app, cpu.eax);
        push(app, cpu, cpu.eax);
        if (!directInput(app, cpu, Object::Device, kSetProperty))
            return;
        if (cpu.eax != 0)
        {
            cpu.eax = 0;
            return done();
        }
        push(app, cpu, cpu.esi);
        if (!byAddress(app, cpu, kMessageHandler))
            return;
        push(app, cpu, 0x436930);  // hideCursor
        push(app, cpu, cpu.esi);
        put(app, kOldSetCursor, cpu.eax);
        if (!byAddress(app, cpu, kSetMessageHandler))
            return;
    }
    if (at(app, kMouse) != 0)
    {
        cpu.eax = kTheMouse;
        if (!direct(app, cpu, acquireDevice))
            return;
    }
    cpu.ecx = 0x1e0;
    cpu.ebx = 0x280;
    cpu.eax = 0;
    cpu.edx = 0;
    put(app, kButtons, cpu.eax);
    put(app, kWheel, cpu.eax);
    if (!direct(app, cpu, setPointerBounds))
        return;
    cpu.eax = 1;
    done();
}

/* 0x4352d0: the pointer's bounds -- eax left, edx top, ebx right, ecx
 * bottom -- and the pointer put back inside them (placePointer), where
 * there is a mouse. */
void setPointerBounds(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    if (at(app, kMouse) != 0)
    {
        put(app, kPointerLeft, cpu.eax);
        put(app, kPointerTop, cpu.edx);
        put(app, kPointerRight, cpu.ebx);
        cpu.edx = at(app, kPointerY);
        cpu.eax = at(app, kPointerX);
        put(app, kPointerBottom, cpu.ecx);
        if (!byAddress(app, cpu, kPlacePointer))
            return;
    }
    cpu.ebp = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x435310: the mouse read -- what it has buffered, up to 32 events: the
 * pointer moved within its bounds, the wheel, buttons 0 to 3 pressed and let
 * go (swapped as Windows has them) -- into [eax] the buttons, [edx] x, [ebx]
 * y, [ecx] the wheel, where not 0; the game's handler called with those let
 * go.  Lost or not acquired, the mouse is acquired again, and what it had
 * handed back. */
void readMouse(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.esi, &cpu.edi}, 0x208);
    const reg32 ebp = cpu.ebp;
    auto done = [&] { leave(app, cpu, {&cpu.esi, &cpu.edi}); };
    put(app, ebp - 4, cpu.eax);
    cpu.esi = cpu.edx;
    cpu.edi = cpu.ebx;
    cpu.ebx = cpu.ecx;
    cpu.edx = 0x20;
    cpu.ecx = at(app, kMouse);
    put(app, ebp - 8, cpu.edx);
    if (cpu.ecx == 0)
        return done();
    // GetDeviceData(the mouse, 0x10, the frame's events, &32, 0)
    push(app, cpu, 0);
    cpu.edx = ebp - 8;
    push(app, cpu, cpu.edx);
    cpu.edx = ebp - 0x208;
    cpu.eax = 0;
    push(app, cpu, cpu.edx);
    put(app, kWheel, cpu.eax);
    push(app, cpu, 0x10);
    cpu.eax = cpu.ecx;
    cpu.ecx = at(app, cpu.ecx);
    push(app, cpu, cpu.eax);
    if (!directInput(app, cpu, Object::Device, kGetDeviceData))
        return;
    if (cpu.eax != 0)
    {
        cpu.edx = 0;
        cpu.ecx = at(app, ebp - 4);
        put(app, kButtons, cpu.edx);
        if (cpu.ecx != 0)
            put(app, cpu.ecx, cpu.edx);
        if (cpu.ebx != 0)
        {
            cpu.edx = at(app, kWheel);
            put(app, cpu.ebx, cpu.edx);
        }
        if (cpu.esi != 0)
        {
            cpu.edx = at(app, kPointerX);
            put(app, cpu.esi, cpu.edx);
        }
        if (cpu.edi != 0)
        {
            cpu.edx = at(app, kPointerY);
            put(app, cpu.edi, cpu.edx);
        }
        if (cpu.eax == kNotAcquired || cpu.eax == kInputLost)
        {
            cpu.eax = kTheMouse;
            if (!direct(app, cpu, acquireDevice))
                return;
        }
        return done();
    }
    cpu.eax = at(app, kButtons);
    cpu.eax &= 0xf;
    cpu.edx = 0;
    put(app, kButtons, cpu.eax);
    // Each event: its offset in DIMOUSESTATE at 0, its data at 4.
    for (; cpu.edx < at(app, ebp - 8); ++cpu.edx)
    {
        cpu.ecx = cpu.edx << 4;
        cpu.eax = at(app, cpu.ecx + ebp - 0x208);
        if (cpu.eax == 0 || cpu.eax == 4)
        {
            const reg32 place = cpu.eax == 0 ? kPointerX : kPointerY;
            const reg32 low = cpu.eax == 0 ? kPointerLeft : kPointerTop;
            const reg32 high = cpu.eax == 0 ? kPointerRight : kPointerBottom;
            cpu.eax = at(app, cpu.ecx + ebp - 0x204);
            cpu.ecx = at(app, place);
            cpu.ecx += cpu.eax;
            put(app, place, cpu.ecx);
            cpu.eax = cpu.ecx;
            cpu.ecx = at(app, low);
            if (sreg32(cpu.eax) < sreg32(cpu.ecx))
                put(app, place, cpu.ecx);
            else
            {
                cpu.ecx = at(app, high);
                if (sreg32(cpu.eax) > sreg32(cpu.ecx))
                    put(app, place, cpu.ecx);
            }
            continue;
        }
        if (cpu.eax == 8)
        {
            cpu.eax = at(app, cpu.ecx + ebp - 0x204);
            put(app, kWheel, cpu.eax);
            continue;
        }
        if (at(app, kButtonsSwapped) != 0)
        {
            if (cpu.eax == 0xc)
                cpu.eax = 0xd;
            else if (cpu.eax == 0xd)
                cpu.eax = 0xc;
            else if (cpu.eax == 0xe)
                cpu.eax = 0xf;
            else if (cpu.eax == 0xf)
                cpu.eax = 0xe;
        }
        cpu.ecx = cpu.edx << 4;
        if (cpu.eax >= 0xc && cpu.eax <= 0xf)
        {
            const x86::reg8 bit = x86::reg8(1 << (cpu.eax - 0xc));
            if (byte(app, cpu.ecx + ebp - 0x204) & 0x80)
                putByte(app, kButtons, byte(app, kButtons) | bit);
            else
            {
                putByte(app, kButtons, byte(app, kButtons) ^ bit);
                putByte(app, kButtonsLetGo, byte(app, kButtonsLetGo) | bit);
            }
        }
    }
    if (at(app, ebp - 4) != 0)
    {
        cpu.edx = at(app, ebp - 4);
        cpu.eax = at(app, kButtons);
        put(app, cpu.edx, cpu.eax);
    }
    if (cpu.ebx != 0)
    {
        cpu.eax = at(app, kWheel);
        put(app, cpu.ebx, cpu.eax);
    }
    if (cpu.esi != 0)
    {
        cpu.eax = at(app, kPointerX);
        put(app, cpu.esi, cpu.eax);
    }
    if (cpu.edi != 0)
    {
        cpu.eax = at(app, kPointerY);
        put(app, cpu.edi, cpu.eax);
    }
    if (at(app, kButtonHandler) != 0 && (byte(app, kButtonsLetGo) & 0xf) != 0)
    {
        cpu.eax = at(app, kButtons);
        cpu.eax &= 0xf00;
        if (!byAddress(app, cpu, at(app, kButtonHandler)))
            return;
    }
    done();
}

/* 0x435600: the joysticks, looked for once -- EnumDevices for the attached
 * ones (joystickFound), each described (describeJoystick) -- and acquired,
 * their force feedback reset, when there are any.  How many there are; 0
 * when DirectInput will not start. */
void findJoysticks(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.ecx, &cpu.edx, &cpu.esi, &cpu.edi}, 0);
    bool look = true;
    if (at(app, kDirectInput) == 0)
    {
        if (!direct(app, cpu, startDirectInput))
            return;
        if (at(app, kDirectInput) == 0)
        {
            cpu.eax = 0;
            return leave(app, cpu, {&cpu.ecx, &cpu.edx, &cpu.esi, &cpu.edi});
        }
    }
    else if (at(app, kJoysticksLooked) != 0)
        look = false;
    if (look)
    {
        cpu.esi = 1;
        cpu.edi = at(app, kJoystickCount);
        put(app, kJoysticksLooked, cpu.esi);
        if (cpu.edi == 0)
        {
            // EnumDevices(DirectInput, DIDEVTYPE_JOYSTICK, joystickFound, DirectInput, DIEDFL_ATTACHEDONLY)
            push(app, cpu, cpu.esi);
            cpu.eax = at(app, kDirectInput);
            push(app, cpu, cpu.eax);
            push(app, cpu, 0x436980);  // joystickFound
            push(app, cpu, 4);
            cpu.edx = at(app, cpu.eax);
            push(app, cpu, cpu.eax);
            if (!directInput(app, cpu, Object::DirectInput, kEnumDevices))
                return;
            cpu.eax = kAllJoysticks;
            if (!direct(app, cpu, describeJoystick))
                return;
        }
        if (at(app, kJoystickCount) != 0)
        {
            cpu.eax = kAllJoysticks;
            if (!direct(app, cpu, acquireDevice))
                return;
            if (!direct(app, cpu, resetForceFeedback))
                return;
        }
    }
    cpu.eax = at(app, kJoystickCount);
    leave(app, cpu, {&cpu.ecx, &cpu.edx, &cpu.esi, &cpu.edi});
}

/* 0x435690: joystick eax described, where it is not yet -- acquired; whether
 * it has force feedback, the buttons (up to 32), hats (4) and axes (8) it
 * has, by asking for each object's info, and each axis's dead zone and
 * saturation (readAxisZone).  Its record, or 0; 0x10 every joystick. */
void describeJoystick(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.edx, &cpu.esi, &cpu.edi}, 0x190);
    const reg32 ebp = cpu.ebp;
    auto done = [&] { leave(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.edx, &cpu.esi, &cpu.edi}); };
    put(app, ebp - 4, cpu.eax);
    // The axes' offsets in DIJOYSTATE, to the frame.
    cpu.ecx = 8;
    cpu.edi = ebp - 0x28;
    cpu.esi = kAxisOffsets;
    for (; cpu.ecx != 0; --cpu.ecx, cpu.esi += 4, cpu.edi += 4)
        put(app, cpu.edi, at(app, cpu.esi));
    if (sreg32(cpu.eax) > 0x10 || sreg32(cpu.eax) < 0)
    {
        cpu.eax = 0;
        return done();
    }
    if (cpu.eax == kAllJoysticks)
    {
        cpu.ebx = 0xf;
        do
        {
            cpu.eax = cpu.ebx;
            if (!direct(app, cpu, describeJoystick))
                return;
            --cpu.ebx;
        } while (sreg32(cpu.ebx) > 0);
        cpu.eax = 0;
        if (!direct(app, cpu, describeJoystick))
            return;
        return done();
    }
    if (at(app, kDirectInput) == 0)
    {
        if (!direct(app, cpu, startDirectInput))
            return;
        if (at(app, kDirectInput) == 0)
        {
            cpu.eax = 0;
            return done();
        }
    }
    cpu.esi = at(app, ebp - 4);
    cpu.esi <<= 2;
    cpu.eax = at(app, cpu.esi + kJoysticks);
    if (cpu.eax == 0)
        return done();
    cpu.edx = at(app, ebp - 4);
    cpu.ebx = cpu.edx;
    cpu.ebx <<= 4;
    cpu.ebx += cpu.edx;
    cpu.eax = at(app, ebp - 4);
    cpu.ebx <<= 3;
    if (!direct(app, cpu, acquireDevice))
        return;
    if (at(app, cpu.ebx + kJoystickButtons) == 0 && at(app, cpu.ebx + kJoystickAxes) == 0)
    {
        // GetCapabilities(the joystick, a DIDEVCAPS of 0x2c at [ebp - 0x54])
        cpu.ecx = ebp - 0x54;
        cpu.edi = 0x2c;
        push(app, cpu, cpu.ecx);
        cpu.eax = at(app, cpu.esi + kJoysticks);
        put(app, ebp - 0x54, cpu.edi);
        push(app, cpu, cpu.eax);
        cpu.edx = at(app, cpu.eax);
        if (!directInput(app, cpu, Object::Device, kGetCapabilities))
            return;
        if (cpu.eax != 0)
        {
            cpu.eax = 0;
            return done();
        }
        if (byte(app, ebp - 0x4f) & 1)  // DIDC_FORCEFEEDBACK
            putByte(app, cpu.ebx + kJoystickRecords, byte(app, cpu.ebx + kJoystickRecords) | 8);
        // Each object: GetObjectInfo(the joystick, a DIDEVICEOBJECTINSTANCE of
        // 0x13c at [ebp - 0x190], its offset, DIPH_BYOFFSET).
        cpu.eax = 0x13c;
        cpu.esi = 0;
        cpu.ebx = 0;
        put(app, ebp - 0x190, cpu.eax);
        // The buttons: at 0x30 on.
        while (cpu.esi < at(app, ebp - 0x44) && sreg32(cpu.ebx) < 0x20)
        {
            push(app, cpu, 1);
            cpu.ecx = cpu.ebx + 0x30;
            cpu.eax = at(app, ebp - 4);
            push(app, cpu, cpu.ecx);
            cpu.ecx = ebp - 0x190;
            cpu.eax = at(app, cpu.eax * 4 + kJoysticks);
            push(app, cpu, cpu.ecx);
            cpu.edx = at(app, cpu.eax);
            push(app, cpu, cpu.eax);
            if (!directInput(app, cpu, Object::Device, kGetObjectInfo))
                return;
            if (cpu.eax == 0)
            {
                cpu.edx = at(app, ebp - 4);
                cpu.eax = cpu.edx;
                cpu.eax <<= 4;
                cpu.cl = cpu.bl;
                cpu.eax += cpu.edx;
                cpu.edx = 1;
                cpu.edx <<= cpu.cl & 31;
                cpu.ecx = at(app, cpu.eax * 8 + kJoystickButtons);
                cpu.ecx |= cpu.edx;
                ++cpu.esi;
                put(app, cpu.eax * 8 + kJoystickButtons, cpu.ecx);
            }
            ++cpu.ebx;
        }
        // The hats: at 0x20 on.
        cpu.ebx = 0;
        cpu.esi = 0;
        while (cpu.esi < at(app, ebp - 0x40) && sreg32(cpu.ebx) < 4)
        {
            cpu.edx = cpu.ebx * 4;
            push(app, cpu, 1);
            cpu.edx += 0x20;
            cpu.eax = at(app, ebp - 4);
            push(app, cpu, cpu.edx);
            cpu.edx = ebp - 0x190;
            cpu.eax = at(app, cpu.eax * 4 + kJoysticks);
            push(app, cpu, cpu.edx);
            cpu.ecx = at(app, cpu.eax);
            push(app, cpu, cpu.eax);
            if (!directInput(app, cpu, Object::Device, kGetObjectInfo))
                return;
            if (cpu.eax == 0)
            {
                cpu.edx = at(app, ebp - 4);
                cpu.eax = cpu.edx;
                cpu.eax <<= 4;
                cpu.cl = cpu.bl;
                cpu.eax += cpu.edx;
                cpu.edx = 1;
                cpu.edx <<= cpu.cl & 31;
                cpu.ecx = at(app, cpu.eax * 8 + kJoystickHats);
                cpu.ecx |= cpu.edx;
                ++cpu.esi;
                put(app, cpu.eax * 8 + kJoystickHats, cpu.ecx);
            }
            ++cpu.ebx;
        }
        // The axes: at the frame's offsets; each one's zones.
        cpu.esi = 0;
        put(app, ebp - 8, cpu.esi);
        while (cpu.esi < at(app, ebp - 0x48) && sreg32(at(app, ebp - 8)) < 8)
        {
            cpu.ecx = at(app, ebp - 8);
            push(app, cpu, 1);
            cpu.ebx = at(app, ebp + cpu.ecx * 4 - 0x28);
            cpu.eax = at(app, ebp - 4);
            push(app, cpu, cpu.ebx);
            cpu.ecx = ebp - 0x190;
            cpu.eax = at(app, cpu.eax * 4 + kJoysticks);
            push(app, cpu, cpu.ecx);
            cpu.edx = at(app, cpu.eax);
            push(app, cpu, cpu.eax);
            if (!directInput(app, cpu, Object::Device, kGetObjectInfo))
                return;
            if (cpu.eax == 0)
            {
                cpu.edx = at(app, ebp - 4);
                cpu.eax = cpu.edx;
                cpu.eax <<= 4;
                cpu.eax += cpu.edx;
                cpu.cl = byte(app, ebp - 8);
                cpu.edx = 1;
                cpu.edi = at(app, cpu.eax * 8 + kJoystickAxes);
                cpu.edx <<= cpu.cl & 31;
                cpu.ebx = 0;
                cpu.edi |= cpu.edx;
                cpu.edx = at(app, ebp - 8);
                put(app, cpu.eax * 8 + kJoystickAxes, cpu.edi);
                cpu.eax = at(app, ebp - 4);
                if (!direct(app, cpu, readAxisZone))
                    return;
                cpu.ebx = 1;
                cpu.edx = at(app, ebp - 8);
                cpu.eax = at(app, ebp - 4);
                ++cpu.esi;
                if (!direct(app, cpu, readAxisZone))
                    return;
            }
            put(app, ebp - 8, at(app, ebp - 8) + 1);
        }
        cpu.ebx = at(app, ebp - 4);
        cpu.eax = cpu.ebx;
        cpu.eax <<= 4;
        cpu.eax += cpu.ebx;
    }
    else
    {
        cpu.edx = at(app, ebp - 4);
        cpu.eax = cpu.edx;
        cpu.eax <<= 4;
        cpu.eax += cpu.edx;
    }
    cpu.eax <<= 3;
    cpu.eax += kJoystickRecords;
    done();
}

/* 0x4358f0: joystick eax read into the DIJOYSTATE at edx -- polled, its
 * state taken -- and made the game's after it: the axes copied to 0x50, the
 * buttons pressed as bits at 0x70, the 4 hats' directions at 0x74 (1 up to
 * 8 round from north, 0 centred or none).  The state, or 0; lost or not
 * acquired, the joystick acquired again. */
void readJoystick(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.esi, &cpu.edi}, 4);
    const reg32 ebp = cpu.ebp;
    auto done = [&] { leave(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.esi, &cpu.edi}); };
    cpu.esi = cpu.eax;
    cpu.ebx = cpu.edx;
    cpu.edi = cpu.edx;
    if (sreg32(cpu.eax) >= 0x10 || sreg32(cpu.eax) < 0)
    {
        cpu.eax = 0;
        return done();
    }
    cpu.eax <<= 2;
    cpu.edx = at(app, cpu.eax + kJoysticks);
    put(app, ebp - 4, cpu.eax);
    if (cpu.edx == 0 || cpu.ebx == 0)
    {
        cpu.eax = 0;
        return done();
    }
    cpu.eax = cpu.edx;
    push(app, cpu, cpu.eax);
    cpu.edx = at(app, cpu.edx);
    if (!directInput(app, cpu, Object::Device, kPoll))
        return;
    if (cpu.eax != 0)
    {
        if (cpu.eax == kInputLost || cpu.eax == kNotAcquired)
        {
            cpu.eax = cpu.esi;
            if (!direct(app, cpu, acquireDevice))
                return;
        }
        cpu.eax = 0;
        return done();
    }
    push(app, cpu, cpu.ebx);
    cpu.eax = at(app, ebp - 4);
    push(app, cpu, 0x50);
    cpu.eax = at(app, cpu.eax + kJoysticks);
    push(app, cpu, cpu.eax);
    cpu.edx = at(app, cpu.eax);
    if (!directInput(app, cpu, Object::Device, kGetDeviceState))
        return;
    if (cpu.eax != 0)
    {
        if (cpu.eax == kInputLost)
        {
            cpu.eax = cpu.esi;
            if (!direct(app, cpu, acquireDevice))
                return;
        }
        cpu.eax = 0;
        return done();
    }
    cpu.eax = at(app, cpu.ebx);
    put(app, cpu.ebx + 0x70, 0);
    put(app, cpu.ebx + 0x50, cpu.eax);
    for (reg32 i = 4; i < 0x20; i += 4)
    {
        cpu.eax = at(app, cpu.ebx + i);
        put(app, cpu.ebx + 0x50 + i, cpu.eax);
    }
    cpu.eax = 0;
    do
    {
        cpu.edx = cpu.edi + cpu.eax;
        if (byte(app, cpu.edx + 0x30) & 0x80)
        {
            cpu.edx = 1;
            cpu.cl = cpu.al;
            cpu.edx <<= cpu.cl & 31;
            put(app, cpu.edi + 0x70, at(app, cpu.edi + 0x70) | cpu.edx);
        }
        ++cpu.eax;
    } while (sreg32(cpu.eax) < 0x20);
    cpu.edx = 0;
    do
    {
        cpu.eax = cpu.esi;
        cpu.eax <<= 4;
        cpu.cl = cpu.dl;
        cpu.ebx = cpu.esi + cpu.eax;
        cpu.eax = 1;
        cpu.ebx <<= 3;
        cpu.eax <<= cpu.cl & 31;
        bool centred = true;
        if (at(app, cpu.ebx + kJoystickHats) & cpu.eax)
        {
            cpu.eax = cpu.edx * 4;
            cpu.eax += cpu.edi;
            cpu.ebx = at(app, cpu.eax + 0x20);
            if (cpu.ebx < 0xffff)
            {
                centred = false;
                static const reg32 kDirections[] = {0, 0x1194, 0x2328, 0x34bc, 0x4650, 0x57e4, 0x6978, 0x7b0c};
                reg32 direction = 0;
                for (reg32 i = 0; i < 8; ++i)
                    if (cpu.ebx == kDirections[i])
                    {
                        direction = i + 1;
                        break;
                    }
                put(app, cpu.eax + 0x74, direction);
            }
        }
        if (centred)
            put(app, cpu.edi + cpu.edx * 4 + 0x74, 0);
        ++cpu.edx;
    } while (sreg32(cpu.edx) < 4);
    cpu.eax = cpu.edi;
    done();
}

/* 0x435ae0: joystick eax's axis edx's dead zone (ebx 0) or saturation (ebx
 * 1) asked of DirectInput (axisProperty), in percent, kept in its record --
 * the saturation as 100 less it.  What was kept. */
void readAxisZone(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.ecx, &cpu.esi, &cpu.edi}, 4);
    const reg32 ebp = cpu.ebp;
    cpu.esi = cpu.eax;
    put(app, ebp - 4, cpu.edx);
    cpu.edi = cpu.ebx;
    push(app, cpu, 0);
    cpu.ecx = cpu.ebx;
    cpu.ebx = 1;
    if (!direct(app, cpu, axisProperty))
        return;
    cpu.ebx = cpu.eax;
    cpu.edx = cpu.eax;
    cpu.eax = cpu.esi;
    cpu.eax <<= 4;
    cpu.eax += cpu.esi;
    cpu.esi = at(app, ebp - 4);
    cpu.eax <<= 3;
    cpu.esi <<= 3;
    cpu.eax += cpu.esi;
    if (cpu.edi == 0)
        put(app, cpu.eax + kJoystickDeadZone, cpu.ebx);
    else
    {
        cpu.edx = 0x64;
        cpu.edx -= cpu.ebx;
        put(app, cpu.eax + kJoystickSaturation, cpu.edx);
    }
    cpu.eax = cpu.edx;
    leave(app, cpu, {&cpu.ecx, &cpu.esi, &cpu.edi});
}

/* 0x435b40: joystick eax's axis edx's dead zone (ebx 0) or saturation (ebx
 * 1, ecx as 100 less it) set to ecx percent (axisProperty). */
void setAxisZone(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    if (cpu.ebx == 1)
    {
        cpu.esi = 0x64;
        cpu.esi -= cpu.ecx;
        cpu.ecx = cpu.esi;
    }
    push(app, cpu, cpu.ecx);
    cpu.ecx = cpu.ebx;
    cpu.ebx = 0;
    if (!direct(app, cpu, axisProperty))
        return;
    cpu.ebp = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x435b60: the joysticks with force feedback reset (DISFFC_RESET), looked
 * for first when there are none. */
void resetForceFeedback(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.edx, &cpu.esi}, 0);
    if (at(app, kJoystickCount) == 0 && !direct(app, cpu, findJoysticks))
        return;
    for (cpu.ebx = 0; sreg32(cpu.ebx) < sreg32(at(app, kJoystickCount)); ++cpu.ebx)
    {
        cpu.ecx = cpu.ebx * 4;
        cpu.esi = at(app, cpu.ecx + kJoysticks);
        if (cpu.esi == 0)
            continue;
        cpu.eax = times17(cpu.ebx);
        if (byte(app, cpu.eax * 8 + kJoystickRecords) & 8)
        {
            push(app, cpu, 1);
            cpu.edx = at(app, cpu.esi);
            push(app, cpu, cpu.esi);
            if (!directInput(app, cpu, Object::Device, kSendForceFeedbackCommand))
                return;
        }
    }
    leave(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.edx, &cpu.esi});
}

/* 0x435bc0: joystick eax's autocentring on (edx not 0) or off, where it has
 * force feedback; 0x10 or 0x13 every joystick. */
void setAutocenter(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.esi, &cpu.edi}, 0x14);
    const reg32 ebp = cpu.ebp;
    cpu.ebx = cpu.edx;
    if (cpu.eax == kAllJoysticks || cpu.eax == kEveryDevice)
    {
        cpu.ecx = 0;
        do
        {
            cpu.edx = cpu.ebx;
            cpu.eax = cpu.ecx;
            if (!direct(app, cpu, setAutocenter))
                return;
            ++cpu.ecx;
        } while (sreg32(cpu.ecx) < 0x10);
    }
    else if (sreg32(cpu.eax) < 0x10 && sreg32(cpu.eax) >= 0 && at(app, cpu.eax * 4 + kJoysticks) != 0)
    {
        cpu.edx = times17(cpu.eax);
        if (byte(app, cpu.edx * 8 + kJoystickRecords) & 8)
        {
            // SetProperty(the joystick, DIPROP_AUTOCENTER, {0x14, 0x10, 0, DIPH_DEVICE, on})
            cpu.ecx = 0x14;
            cpu.esi = 0x10;
            cpu.edi = 0;
            put(app, ebp - 0x14, cpu.ecx);
            put(app, ebp - 0x10, cpu.esi);
            put(app, ebp - 0xc, cpu.edi);
            put(app, ebp - 8, cpu.edi);
            put(app, ebp - 4, cpu.ebx != 0 ? 1 : cpu.edi);
            cpu.edx = ebp - 0x14;
            push(app, cpu, cpu.edx);
            cpu.eax = at(app, cpu.eax * 4 + kJoysticks);
            push(app, cpu, 9);
            cpu.ecx = at(app, cpu.eax);
            push(app, cpu, cpu.eax);
            if (!directInput(app, cpu, Object::Device, kSetProperty))
                return;
        }
    }
    leave(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.esi, &cpu.edi});
}

namespace
{

/* 0x435c60, 0x435cc0, 0x435d90: a force-feedback command to joystick eax,
 * where it has force feedback; 0x10 or 0x13 every joystick. */
void sendCommand(win32::WinApplication* app, x86::CPU& cpu, reg32 command,
                 void (*self)(win32::WinApplication*, x86::CPU&))
{
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    if (cpu.eax == kAllJoysticks || cpu.eax == kEveryDevice)
    {
        cpu.edx = 0;
        do
        {
            cpu.eax = cpu.edx;
            if (!direct(app, cpu, self))
                return;
            ++cpu.edx;
        } while (sreg32(cpu.edx) < 0x10);
    }
    else if (sreg32(cpu.eax) < 0x10 && sreg32(cpu.eax) >= 0)
    {
        cpu.edx = cpu.eax * 4;
        if (at(app, cpu.edx + kJoysticks) != 0)
        {
            cpu.ecx = cpu.eax;
            cpu.eax <<= 4;
            cpu.eax += cpu.ecx;
            if (byte(app, cpu.eax * 8 + kJoystickRecords) & 8)
            {
                push(app, cpu, command);
                cpu.eax = at(app, cpu.edx + kJoysticks);
                push(app, cpu, cpu.eax);
                cpu.edx = at(app, cpu.eax);
                if (!directInput(app, cpu, Object::Device, kSendForceFeedbackCommand))
                    return;
            }
        }
    }
    cpu.ebp = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.esp += 4;
}

}  // namespace

/* 0x435c60: joystick eax's effects paused (DISFFC_PAUSE). */
void pauseEffects(win32::WinApplication* app, x86::CPU& cpu)
{
    sendCommand(app, cpu, 4, pauseEffects);
}

/* 0x435cc0: joystick eax's effects going on (DISFFC_CONTINUE). */
void continueEffects(win32::WinApplication* app, x86::CPU& cpu)
{
    sendCommand(app, cpu, 8, continueEffects);
}

/* 0x435d20: joystick eax's effects stopped (stopEffects) and its actuators
 * on (DISFFC_SETACTUATORSON). */
void actuatorsOn(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    if (cpu.eax == kAllJoysticks || cpu.eax == kEveryDevice)
    {
        cpu.edx = 0;
        do
        {
            cpu.eax = cpu.edx;
            if (!direct(app, cpu, actuatorsOn))
                return;
            ++cpu.edx;
        } while (sreg32(cpu.edx) < 0x10);
    }
    else if (sreg32(cpu.eax) < 0x10 && sreg32(cpu.eax) >= 0)
    {
        cpu.ecx = cpu.eax * 4;
        if (at(app, cpu.ecx + kJoysticks) != 0)
        {
            cpu.edx = times17(cpu.eax);
            if (byte(app, cpu.edx * 8 + kJoystickRecords) & 8)
            {
                if (!direct(app, cpu, stopEffects))
                    return;
                push(app, cpu, 0x10);
                cpu.eax = at(app, cpu.ecx + kJoysticks);
                push(app, cpu, cpu.eax);
                cpu.edx = at(app, cpu.eax);
                if (!directInput(app, cpu, Object::Device, kSendForceFeedbackCommand))
                    return;
            }
        }
    }
    cpu.ebp = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x435d90: joystick eax's actuators off (DISFFC_SETACTUATORSOFF). */
void actuatorsOff(win32::WinApplication* app, x86::CPU& cpu)
{
    sendCommand(app, cpu, 0x20, actuatorsOff);
}

/* 0x435df0: joystick eax's force-feedback gain set to edx percent (100 most,
 * 0 for less than none), the effects unloaded around it and downloaded
 * again; 0x10 or 0x13 every joystick. */
void setGain(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.esi, &cpu.edi}, 0x14);
    const reg32 ebp = cpu.ebp;
    cpu.ecx = cpu.eax;
    cpu.ebx = cpu.edx;
    if (cpu.eax == kAllJoysticks || cpu.eax == kEveryDevice)
    {
        cpu.ecx = 0;
        do
        {
            cpu.edx = cpu.ebx;
            cpu.eax = cpu.ecx;
            if (!direct(app, cpu, setGain))
                return;
            ++cpu.ecx;
        } while (sreg32(cpu.ecx) < 0x10);
    }
    else if (sreg32(cpu.ecx) < 0x10 && sreg32(cpu.ecx) >= 0 && at(app, cpu.ecx * 4 + kJoysticks) != 0)
    {
        cpu.eax = times17(cpu.ecx);
        if (byte(app, cpu.eax * 8 + kJoystickRecords) & 8)
        {
            // SetProperty(the joystick, DIPROP_FFGAIN, {0x14, 0x10, 0, DIPH_DEVICE, percent * 100})
            cpu.edi = 0x10;
            cpu.esi = 0x14;
            cpu.eax = 0;
            put(app, ebp - 0x10, cpu.edi);
            put(app, ebp - 0xc, cpu.eax);
            put(app, ebp - 8, cpu.eax);
            put(app, ebp - 0x14, cpu.esi);
            if (sreg32(cpu.ebx) > 0x64)
                put(app, ebp - 4, 0x2710);
            else
            {
                if (sreg32(cpu.ebx) >= 0)
                {
                    cpu.eax = cpu.ebx * 4;
                    cpu.eax -= cpu.ebx;
                    cpu.eax <<= 3;
                    cpu.eax += cpu.ebx;
                    cpu.eax <<= 2;
                }
                put(app, ebp - 4, cpu.eax);
            }
            for (cpu.ebx = 0; sreg32(cpu.ebx) < sreg32(at(app, kEffectCount)); ++cpu.ebx)
            {
                cpu.eax = reg32(sreg32(x86::sreg16(cpu.bx)));
                if (!direct(app, cpu, unloadEffect))
                    return;
            }
            cpu.edx = ebp - 0x14;
            push(app, cpu, cpu.edx);
            cpu.eax = at(app, cpu.ecx * 4 + kJoysticks);
            push(app, cpu, 7);
            cpu.ecx = at(app, cpu.eax);
            push(app, cpu, cpu.eax);
            cpu.ebx = 0;
            if (!directInput(app, cpu, Object::Device, kSetProperty))
                return;
            for (; sreg32(cpu.ebx) < sreg32(at(app, kEffectCount)); ++cpu.ebx)
            {
                cpu.eax = reg32(sreg32(x86::sreg16(cpu.bx)));
                if (!direct(app, cpu, downloadEffect))
                    return;
            }
        }
    }
    leave(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.esi, &cpu.edi});
}

/* 0x435f10: an effect made on joystick eax from the description at edx --
 * its type at 0, its type's parameters (0x30 bytes) at 4, its duration in
 * ms (0xffffff for ever) at 0x34, gain at 0x38, axes (0 x, 1 y, else both)
 * at 0x3c, trigger button (-1 none) at 0x40, repeat at 0x44, direction in
 * degrees at 0x48 -- into the next effect's record, created (and unloaded
 * straight away).  Its number, or -1: no room for it, no force feedback, a
 * type past 12, or DirectInput would not. */
void createEffect(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.esi, &cpu.edi}, 0);
    auto done = [&] { leave(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.esi, &cpu.edi}); };
    auto none = [&] {
        cpu.eax = 0xffffffff;
        done();
    };
    cpu.ebx = cpu.eax;
    if (sreg32(at(app, kEffectCount)) >= 0x1e || sreg32(cpu.eax) >= 0x10 || sreg32(cpu.eax) < 0
        || at(app, cpu.eax * 4 + kJoysticks) == 0)
        return none();
    cpu.eax <<= 4;
    cpu.eax += cpu.ebx;
    if (!(byte(app, cpu.eax * 8 + kJoystickRecords) & 8))
        return none();
    // The duration, in microseconds.
    cpu.edi = at(app, cpu.edx + 0x34);
    if (cpu.edi == 0xffffff)
        cpu.esi = 0xffffffff;
    else
    {
        cpu.eax = cpu.edi * 4;
        cpu.eax -= cpu.edi;
        cpu.eax <<= 3;
        cpu.eax += cpu.edi;
        cpu.eax <<= 3;
        cpu.esi = cpu.eax * 4;
        cpu.esi += cpu.eax;
    }
    cpu.ecx = at(app, kEffectCount);
    cpu.eax = times17(cpu.ecx);
    put(app, cpu.eax * 8 + kEffectDuration, cpu.esi);
    cpu.ecx = at(app, cpu.edx + 0x38);
    put(app, cpu.eax * 8 + kEffectGain, cpu.ecx);
    cpu.eax = at(app, cpu.edx + 0x40);
    cpu.esi = cpu.eax == 0xffffffff ? cpu.eax : cpu.eax + 0x30;
    cpu.eax = at(app, kEffectCount);
    cpu.ecx = times17(cpu.eax);
    cpu.ecx <<= 3;
    put(app, cpu.ecx + kEffectTrigger, cpu.esi);
    cpu.eax = at(app, cpu.edx + 0x44);
    put(app, cpu.ecx + kEffectRepeat, cpu.eax);
    cpu.esi = at(app, cpu.edx + 0x48);
    cpu.eax = cpu.esi * 4;
    cpu.eax -= cpu.esi;
    cpu.eax <<= 3;
    cpu.eax += cpu.esi;
    cpu.eax <<= 2;
    put(app, cpu.ecx + kEffectDirection, cpu.eax);
    // Its axes: x, y, or both.
    cpu.esi = at(app, cpu.edx + 0x3c);
    if (cpu.esi == 0)
    {
        cpu.eax = kEffectAxes;
        cpu.edi = 1;
        put(app, cpu.ecx + kEffectAxisList, cpu.eax);
        put(app, kEffectAxes, cpu.esi);
        put(app, cpu.ecx + kEffectAxisCount, cpu.edi);
    }
    else if (cpu.esi == 1)
    {
        cpu.eax = kEffectAxes;
        put(app, cpu.ecx + kEffectAxisCount, cpu.esi);
        put(app, cpu.ecx + kEffectAxisList, cpu.eax);
        put(app, kEffectAxes, 4);
    }
    else
    {
        cpu.edi = kEffectAxes;
        cpu.esi = 2;
        put(app, cpu.ecx + kEffectAxisList, cpu.edi);
        cpu.eax = 0;
        put(app, cpu.ecx + kEffectAxisCount, cpu.esi);
        cpu.ecx = 4;
        put(app, kEffectAxes, cpu.eax);
        put(app, kEffectAxes + 4, cpu.ecx);
    }
    // Its type's parameters, to the record.
    cpu.ecx = at(app, kEffectCount);
    cpu.eax = times17(cpu.ecx);
    cpu.eax <<= 3;
    cpu.esi = cpu.edx + 4;
    cpu.eax += kEffectRecords;
    cpu.ecx = 0x30;
    cpu.edi = cpu.eax + 0x34;
    push(app, cpu, cpu.edi);
    copyBytes(app, cpu);
    cpu.edi = pop(app, cpu);
    // The rest of the DIEFFECT.
    cpu.ecx = at(app, kEffectCount);
    cpu.eax = times17(cpu.ecx);
    cpu.esi = 0x34;
    cpu.eax <<= 3;
    cpu.edi = 0x22;  // DIEFF_OBJECTOFFSETS | DIEFF_POLAR
    put(app, cpu.eax + kEffectRecords, cpu.esi);
    cpu.ecx = 0x7d0;
    put(app, cpu.eax + kEffectFlags, cpu.edi);
    put(app, cpu.eax + kEffectPeriod, cpu.ecx);
    cpu.edi = 0;
    put(app, cpu.eax + kEffectDirection2, cpu.edi);
    cpu.ecx = kEffectRecords;
    put(app, cpu.eax + kEffectEnvelope, cpu.edi);
    cpu.ecx += cpu.eax;
    put(app, cpu.eax + kEffectPlaying, cpu.edi);
    cpu.esi += cpu.ecx;
    cpu.ecx += 0x78;
    put(app, cpu.eax + kEffectParameters, cpu.esi);
    put(app, cpu.eax + kEffectDirections, cpu.ecx);
    put(app, cpu.eax + kEffectParameters, cpu.esi);
    cpu.ecx = at(app, cpu.edx);
    put(app, cpu.eax + kEffectType, cpu.ecx);
    if (cpu.ecx > 0xc)
        return none();
    // The parameters' size by the type, as the game's jump table has it.
    switch (at(app, kParameterSizes + cpu.ecx * 4))
    {
    case 0x436103:  // a constant force
        cpu.ecx = at(app, kEffectCount);
        cpu.eax = times17(cpu.ecx);
        put(app, cpu.eax * 8 + kEffectParameterBytes, 4);
        break;
    case 0x43611d:  // a ramp
        put(app, cpu.eax + kEffectParameterBytes, 8);
        break;
    case 0x436129:  // a square wave
        put(app, cpu.eax + kEffectParameterBytes, 0x10);
        break;
    case 0x436135:  // the other waves
        cpu.ecx = at(app, kEffectCount);
        cpu.eax = times17(cpu.ecx);
        put(app, cpu.eax * 8 + kEffectParameterBytes, 0x10);
        break;
    case 0x43614f:  // a condition
        cpu.ecx = at(app, kEffectCount);
        cpu.eax = times17(cpu.ecx);
        put(app, cpu.eax * 8 + kEffectParameterBytes, 0x18);
        break;
    default:  // 0x436169: a condition on each of two axes
        put(app, cpu.eax + kEffectParameterBytes, 0x30);
        break;
    }
    // CreateEffect(the joystick, its type's GUID, the record, &the effect, none)
    cpu.eax = at(app, kEffectCount);
    cpu.eax <<= 2;
    push(app, cpu, 0);
    cpu.eax += kEffects;
    cpu.ecx = at(app, kEffectCount);
    push(app, cpu, cpu.eax);
    cpu.eax = times17(cpu.ecx);
    cpu.eax <<= 3;
    cpu.eax += kEffectRecords;
    push(app, cpu, cpu.eax);
    cpu.eax = at(app, cpu.edx);
    cpu.edi = at(app, cpu.eax * 4 + kEffectGuids);
    cpu.ebx = at(app, cpu.ebx * 4 + kJoysticks);
    push(app, cpu, cpu.edi);
    cpu.esi = at(app, cpu.ebx);
    push(app, cpu, cpu.ebx);
    if (!directInput(app, cpu, Object::Device, kCreateEffect))
        return;
    if (cpu.eax != 0)
        return none();
    cpu.eax = reg32(sreg32(at(app, kEffectCount - 2)) >> 16);
    if (!direct(app, cpu, unloadEffect))
        return;
    cpu.eax = at(app, kEffectCount);
    cpu.edx = cpu.eax + 1;
    put(app, kEffectCount, cpu.edx);
    done();
}

/* 0x4361e0: effect ax started, once; whether it plays as DirectInput says. */
void startEffect(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    if (x86::sreg16(cpu.ax) >= 0)
    {
        push(app, cpu, 0);
        cpu.ebx = reg32(sreg32(x86::sreg16(cpu.ax)));
        push(app, cpu, 1);
        cpu.eax = at(app, cpu.ebx * 4 + kEffects);
        push(app, cpu, cpu.eax);
        cpu.edx = at(app, cpu.eax);
        if (!directInput(app, cpu, Object::Effect, kStart))
            return;
        cpu.edx = cpu.eax;
        cpu.eax = times17(cpu.ebx);
        cpu.eax <<= 3;
        if (cpu.edx == 0)
            put(app, cpu.eax + kEffectPlaying, 1);
        else
        {
            cpu.ecx = 0;
            put(app, cpu.eax + kEffectPlaying, cpu.ecx);
        }
    }
    cpu.ebp = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x436230: effect ax stopped; it plays no more. */
void stopEffect(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    if (x86::sreg16(cpu.ax) >= 0)
    {
        cpu.ebx = reg32(sreg32(x86::sreg16(cpu.ax)));
        cpu.eax = at(app, cpu.ebx * 4 + kEffects);
        push(app, cpu, cpu.eax);
        cpu.edx = at(app, cpu.eax);
        if (!directInput(app, cpu, Object::Effect, kStop))
            return;
        cpu.eax = cpu.ebx;
        cpu.eax <<= 4;
        cpu.edx = cpu.ebx;
        cpu.eax += cpu.ebx;
        cpu.edx ^= cpu.ebx;
        put(app, cpu.eax * 8 + kEffectPlaying, cpu.edx);
    }
    cpu.ebp = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x436270: joystick eax's effects all stopped (DISFFC_STOPALL), where it
 * has force feedback, and none of the 30 plays; 0x10 or 0x13 each joystick
 * there is. */
void stopEffects(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.edx, &cpu.esi}, 0);
    if (cpu.eax == kAllJoysticks || cpu.eax == kEveryDevice)
    {
        for (cpu.edx = 0; sreg32(cpu.edx) < sreg32(at(app, kJoystickCount)); ++cpu.edx)
        {
            cpu.eax = cpu.edx;
            if (!direct(app, cpu, stopEffects))
                return;
        }
    }
    else if (sreg32(cpu.eax) < 0x10 && sreg32(cpu.eax) >= 0)
    {
        cpu.ecx = cpu.eax * 4;
        cpu.ebx = at(app, cpu.ecx + kJoysticks);
        if (cpu.ebx != 0)
        {
            cpu.edx = cpu.eax;
            cpu.eax <<= 4;
            cpu.eax += cpu.edx;
            if (byte(app, cpu.eax * 8 + kJoystickRecords) & 8)
            {
                push(app, cpu, 2);
                cpu.edx = at(app, cpu.ebx);
                push(app, cpu, cpu.ebx);
                if (!directInput(app, cpu, Object::Device, kSendForceFeedbackCommand))
                    return;
                cpu.edx = 0;
                do
                {
                    cpu.eax = times17(cpu.edx);
                    cpu.esi = 0;
                    ++cpu.edx;
                    put(app, cpu.eax * 8 + kEffectPlaying, cpu.esi);
                } while (sreg32(cpu.edx) < 0x1e);
            }
        }
    }
    leave(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.edx, &cpu.esi});
}

namespace
{

/* 0x4362f0, 0x436310: a method of effect ax's. */
void effectMethod(win32::WinApplication* app, x86::CPU& cpu, reg32 method)
{
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    if (x86::sreg16(cpu.ax) >= 0)
    {
        cpu.eax = reg32(sreg32(x86::sreg16(cpu.ax)));
        cpu.eax = at(app, cpu.eax * 4 + kEffects);
        push(app, cpu, cpu.eax);
        cpu.edx = at(app, cpu.eax);
        if (!directInput(app, cpu, Object::Effect, method))
            return;
    }
    cpu.ebp = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.esp += 4;
}

}  // namespace

/* 0x4362f0: effect ax downloaded to its joystick. */
void downloadEffect(win32::WinApplication* app, x86::CPU& cpu)
{
    effectMethod(app, cpu, kDownload);
}

/* 0x436310: effect ax unloaded from its joystick. */
void unloadEffect(win32::WinApplication* app, x86::CPU& cpu)
{
    effectMethod(app, cpu, kUnload);
}

/* 0x436330: effect ax changed where it is asked to -- [ebx] its direction in
 * degrees (0 to 360), [ecx] its duration in ms (1500 most, 0xffffff for
 * ever), and the stack's: [first] its gain in percent, the type's
 * parameters at the second, [third] its trigger button (-1 none), its
 * envelope's 4 words at the fourth -- the arguments made DirectInput's as it
 * goes; what changed set (SetParameters), and with edx 1 or 2 started if it
 * does not play, with 3 downloaded (3 also when nothing changed, 1 started).
 * Whether anything changed; 0 for no effect. */
void updateEffect(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.esi, &cpu.edi}, 0xc);
    const reg32 ebp = cpu.ebp;
    auto done = [&] { leave(app, cpu, {&cpu.esi, &cpu.edi}, 0x10); };
    // The effect: the word at [ebp - 4], from the dword at [ebp - 6].
    auto effect = [&] { return reg32(sreg32(at(app, ebp - 6)) >> 16); };
    cpu.edi = at(app, ebp + 0x10);
    putHalf(app, ebp - 4, cpu.ax);
    put(app, ebp - 8, cpu.edx);
    cpu.edx = 0;
    if (x86::sreg16(cpu.ax) < 0)
    {
        cpu.eax = 0;
        return done();
    }
    if (cpu.ebx != 0)
    {
        cpu.esi = at(app, cpu.ebx);
        if (sreg32(cpu.esi) > 0x168)
            put(app, cpu.ebx, 0x168);
        else if (sreg32(cpu.esi) < 0)
            put(app, cpu.ebx, cpu.edx);
        cpu.esi = at(app, cpu.ebx);
        cpu.eax = cpu.esi * 4;
        cpu.eax -= cpu.esi;
        cpu.eax <<= 3;
        cpu.eax += cpu.esi;
        cpu.esi = at(app, ebp - 6);
        cpu.eax <<= 2;
        cpu.esi = reg32(sreg32(cpu.esi) >> 16);
        put(app, cpu.ebx, cpu.eax);
        cpu.eax = times17(cpu.esi);
        cpu.eax <<= 3;
        cpu.esi = at(app, cpu.eax + kEffectDirection);
        if (cpu.esi != at(app, cpu.ebx))
        {
            cpu.ebx = at(app, cpu.ebx);
            cpu.dl |= 0x40;  // DIEP_DIRECTION
            put(app, cpu.eax + kEffectDirection, cpu.ebx);
        }
    }
    if (cpu.ecx != 0)
    {
        cpu.ebx = at(app, cpu.ecx);
        if (cpu.ebx == 0xffffff)
            put(app, cpu.ecx, 0xffffffff);
        else
        {
            if (cpu.ebx > 0x5dc)
                put(app, cpu.ecx, 0x5dc);
            cpu.ebx = at(app, cpu.ecx);
            cpu.eax = cpu.ebx * 4;
            cpu.eax -= cpu.ebx;
            cpu.eax <<= 3;
            cpu.eax += cpu.ebx;
            cpu.eax <<= 3;
            cpu.ebx = cpu.eax;
            cpu.eax <<= 2;
            cpu.eax += cpu.ebx;
            put(app, cpu.ecx, cpu.eax);
        }
        cpu.ebx = effect();
        cpu.eax = times17(cpu.ebx);
        cpu.eax <<= 3;
        cpu.esi = at(app, cpu.ecx);
        if (cpu.esi != at(app, cpu.eax + kEffectDuration))
        {
            cpu.dl |= 1;  // DIEP_DURATION
            put(app, cpu.eax + kEffectDuration, cpu.esi);
        }
    }
    if (cpu.edi != 0)
    {
        cpu.ecx = at(app, cpu.edi);
        cpu.eax = cpu.ecx * 4;
        cpu.eax -= cpu.ecx;
        cpu.eax <<= 3;
        cpu.ecx += cpu.eax;
        cpu.ecx <<= 2;
        if (cpu.ecx > 0x2710)
            cpu.ecx = 0x2710;
        cpu.ebx = effect();
        cpu.eax = times17(cpu.ebx);
        cpu.eax <<= 3;
        if (cpu.ecx != at(app, cpu.eax + kEffectGain))
        {
            cpu.dl |= 4;  // DIEP_GAIN
            put(app, cpu.eax + kEffectGain, cpu.ecx);
        }
    }
    if (at(app, ebp + 0x14) != 0)
    {
        cpu.ecx = effect();
        cpu.eax = times17(cpu.ecx);
        cpu.ebx = kEffectRecords;
        cpu.eax <<= 3;
        cpu.ebx += cpu.eax;
        cpu.edi = at(app, ebp + 0x14);
        cpu.ebx += 0x34;
        cpu.ecx = at(app, cpu.eax + kEffectParameterBytes);
        cpu.esi = cpu.ebx;
        put(app, ebp - 0xc, cpu.eax);
        cpu.eax = 0;
        // repe cmpsb: the parameters against the record's.
        bool same = true, below = false;
        while (cpu.ecx != 0)
        {
            const x86::reg8 a = byte(app, cpu.esi), b = byte(app, cpu.edi);
            ++cpu.esi;
            ++cpu.edi;
            --cpu.ecx;
            same = a == b;
            below = a < b;
            if (!same)
                break;
        }
        if (!same)
            cpu.eax = below ? 0xffffffff : 1;
        if (cpu.eax != 0)
        {
            cpu.ecx = at(app, ebp - 0xc);
            cpu.esi = at(app, ebp + 0x14);
            cpu.edi = cpu.ebx;
            cpu.ecx = at(app, cpu.ecx + kEffectParameterBytes);
            cpu.dh |= 1;  // DIEP_TYPESPECIFICPARAMS
            push(app, cpu, cpu.edi);
            copyBytes(app, cpu);
            cpu.edi = pop(app, cpu);
        }
    }
    cpu.edi = at(app, ebp + 0x18);
    if (cpu.edi != 0)
    {
        cpu.ecx = at(app, cpu.edi);
        if (sreg32(cpu.ecx) < 0x20)
        {
            if (cpu.ecx != 0xffffffff)
                cpu.ecx += 0x30;
            cpu.ebx = effect();
            cpu.eax = times17(cpu.ebx);
            cpu.dl |= 8;  // DIEP_TRIGGERBUTTON
            put(app, cpu.eax * 8 + kEffectTrigger, cpu.ecx);
        }
    }
    cpu.esi = at(app, ebp + 0x1c);
    if (cpu.esi != 0)
    {
        cpu.ecx = effect();
        cpu.eax = times17(cpu.ecx);
        cpu.eax <<= 3;
        cpu.edi = at(app, cpu.esi);
        bool same = false;
        if (cpu.edi == at(app, cpu.eax + kEffectEnvelopeValues))
        {
            cpu.esi = at(app, cpu.esi + 4);
            if (cpu.esi == at(app, cpu.eax + kEffectEnvelopeValues + 4))
            {
                cpu.ebx = at(app, ebp + 0x1c);
                cpu.ecx = at(app, cpu.eax + kEffectEnvelopeValues + 8);
                if (cpu.ecx == at(app, cpu.ebx + 8))
                {
                    cpu.ebx = at(app, cpu.ebx + 0xc);
                    same = cpu.ebx == at(app, cpu.eax + kEffectEnvelopeValues + 0xc);
                }
            }
        }
        if (!same)
        {
            cpu.ecx = effect();
            cpu.eax = times17(cpu.ecx);
            for (reg32 i = 0; i < 0x10; i += 4)
            {
                cpu.ecx = at(app, ebp + 0x1c);
                cpu.ecx = at(app, cpu.ecx + i);
                if (i == 0xc)
                    cpu.dl |= 0x80;  // DIEP_ENVELOPE
                put(app, cpu.eax * 8 + kEffectEnvelopeValues + i, cpu.ecx);
            }
        }
    }
    if (cpu.edx == 0)
    {
        if (at(app, ebp - 8) == 1)
        {
            cpu.edx = effect();
            cpu.eax = cpu.edx;
            if (!direct(app, cpu, effectPlaying))
                return;
            if (cpu.eax == 0)
            {
                cpu.eax = cpu.edx;
                if (!direct(app, cpu, startEffect))
                    return;
            }
        }
        if (at(app, ebp - 8) == 3)
        {
            cpu.eax = effect();
            if (!direct(app, cpu, downloadEffect))
                return;
        }
        cpu.eax = 0;
        return done();
    }
    // SetParameters(the effect, its record, what changed)
    cpu.eax = effect();
    push(app, cpu, cpu.edx);
    cpu.edx = cpu.eax;
    cpu.ecx = at(app, cpu.eax * 4 + kEffects);
    cpu.eax <<= 4;
    cpu.eax += cpu.edx;
    cpu.eax <<= 3;
    cpu.eax += kEffectRecords;
    push(app, cpu, cpu.eax);
    cpu.ebx = at(app, cpu.ecx);
    push(app, cpu, cpu.ecx);
    if (!directInput(app, cpu, Object::Effect, kSetParameters))
        return;
    cpu.eax = at(app, ebp - 8);
    if (cpu.eax == 1 || cpu.eax == 2)
    {
        cpu.edx = effect();
        cpu.eax = cpu.edx;
        if (!direct(app, cpu, effectPlaying))
            return;
        if (cpu.eax == 0)
        {
            cpu.eax = cpu.edx;
            if (!direct(app, cpu, startEffect))
                return;
        }
        else if (at(app, ebp - 8) == 3)
        {
            cpu.eax = cpu.edx;
            if (!direct(app, cpu, downloadEffect))
                return;
        }
    }
    cpu.eax = 1;
    done();
}

/* 0x436610: device eax's cooperative level with the game's window edx;
 * 0x10 each joystick's.  1, or 0 where DirectInput would not or there is no
 * window; 1 for a device that is not there. */
void setCooperativeLevel(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.esi, &cpu.edi}, 0);
    auto done = [&] { leave(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.esi, &cpu.edi}); };
    cpu.esi = cpu.eax;
    cpu.ebx = cpu.edx;
    if (!direct(app, cpu, AcquireWindow))
        return;
    if (cpu.eax == 0)
        return done();
    // SetCooperativeLevel(the device, the window, the flags)
    if (sreg32(cpu.esi) < 0x10)
    {
        cpu.esi <<= 2;
        cpu.edx = at(app, cpu.esi + kJoysticks);
        if (cpu.edx != 0)
        {
            push(app, cpu, cpu.ebx);
            cpu.edi = at(app, cpu.edx);
            if (!direct(app, cpu, AcquireWindow))
                return;
            push(app, cpu, cpu.eax);
            cpu.ecx = at(app, cpu.esi + kJoysticks);
            push(app, cpu, cpu.ecx);
            if (!directInput(app, cpu, Object::Device, kSetCooperativeLevel))
                return;
            if (cpu.eax != 0)
            {
                cpu.eax = 0;
                return done();
            }
        }
    }
    else if (cpu.esi == kAllJoysticks)
    {
        cpu.esi = 0;
        do
        {
            cpu.edx = cpu.ebx;
            cpu.eax = cpu.esi;
            if (!direct(app, cpu, setCooperativeLevel))
                return;
            ++cpu.esi;
        } while (sreg32(cpu.esi) < 0x10);
    }
    else if (cpu.esi == kTheMouse)
    {
        cpu.eax = at(app, kMouse);
        push(app, cpu, cpu.ebx);
        cpu.esi = at(app, cpu.eax);
        if (!direct(app, cpu, AcquireWindow))
            return;
        push(app, cpu, cpu.eax);
        cpu.ebx = at(app, kMouse);
        push(app, cpu, cpu.ebx);
        if (!directInput(app, cpu, Object::Device, kSetCooperativeLevel))
            return;
        if (cpu.eax != 0)
        {
            cpu.eax = 0;
            return done();
        }
    }
    else if (cpu.esi == kTheKeyboard)
    {
        cpu.eax = at(app, kKeyboard);
        push(app, cpu, cpu.ebx);
        cpu.esi = at(app, cpu.eax);
        if (!direct(app, cpu, AcquireWindow))
            return;
        push(app, cpu, cpu.eax);
        cpu.edi = at(app, kKeyboard);
        push(app, cpu, cpu.edi);
        if (!directInput(app, cpu, Object::Device, kSetCooperativeLevel))
            return;
        if (cpu.eax != 0)
        {
            cpu.eax = 0;
            return done();
        }
    }
    cpu.eax = 1;
    done();
}

/* 0x4366e0: device eax acquired, where DirectInput is started and the device
 * is there: whether it is (acquireResult); 0x10 how many joysticks are,
 * 0x13 the mouse's, the keyboard's and that added up; 0 past 0x13. */
void acquireDevice(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.edx, &cpu.esi, &cpu.edi}, 0);
    auto done = [&] { leave(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.edx, &cpu.esi, &cpu.edi}); };
    // Acquire(the device), what it hands back made whether (acquireResult).
    auto acquire = [&](reg32 device) {
        push(app, cpu, device);
        cpu.edx = at(app, device);
        if (!directInput(app, cpu, Object::Device, kAcquire))
            return false;
        cpu.edx = cpu.ebx;
        return direct(app, cpu, acquireResult);
    };
    cpu.ebx = cpu.eax;
    cpu.edx = at(app, kDirectInput);
    cpu.esi = 0;
    if (cpu.edx == 0)
    {
        cpu.eax = cpu.esi;
        return done();
    }
    if (cpu.eax == kEveryDevice)
    {
        cpu.eax = kTheMouse;
        if (!direct(app, cpu, acquireDevice))
            return;
        cpu.ebx = cpu.eax;
        cpu.eax = kTheKeyboard;
        if (!direct(app, cpu, acquireDevice))
            return;
        cpu.ebx += cpu.eax;
        cpu.eax = kAllJoysticks;
        if (!direct(app, cpu, acquireDevice))
            return;
        cpu.eax += cpu.ebx;
        return done();
    }
    if (cpu.eax == kTheMouse)
    {
        cpu.ecx = at(app, kMouse);
        if (cpu.ecx == 0)
        {
            cpu.eax = cpu.esi;
            return done();
        }
        if (!acquire(cpu.ecx))
            return;
        return done();
    }
    if (cpu.eax == kTheKeyboard)
    {
        cpu.edi = at(app, kKeyboard);
        if (cpu.edi == 0)
        {
            cpu.eax = cpu.esi;
            return done();
        }
        if (!acquire(cpu.edi))
            return;
        return done();
    }
    if (cpu.eax == kAllJoysticks)
    {
        cpu.ebx ^= cpu.eax;
        do
        {
            cpu.eax = cpu.ebx * 4;
            cpu.edx = at(app, cpu.eax + kJoysticks);
            if (cpu.edx != 0)
            {
                cpu.eax = cpu.edx;
                if (!acquire(cpu.eax))
                    return;
                if (cpu.eax != 0)
                    ++cpu.esi;
            }
            ++cpu.ebx;
        } while (sreg32(cpu.ebx) < 0x10);
        cpu.eax = cpu.esi;
        return done();
    }
    if (sreg32(cpu.ebx) > 0x13)
    {
        cpu.eax = 0;
        return done();
    }
    cpu.eax = cpu.ebx * 4;
    cpu.ecx = at(app, cpu.eax + kJoysticks);
    if (cpu.ecx == 0)
    {
        cpu.eax = cpu.esi;
        return done();
    }
    if (!acquire(cpu.ecx))
        return;
    done();
}

/* 0x436800: device eax let go (Unacquire), where it is there; 0x10 each
 * joystick, 0x13 the mouse, the keyboard and the joysticks. */
void unacquireDevice(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.edx, &cpu.esi}, 0);
    auto unacquire = [&](reg32 device) {
        push(app, cpu, device);
        cpu.edx = at(app, device);
        return directInput(app, cpu, Object::Device, kUnacquire);
    };
    cpu.edx = cpu.eax;
    if (cpu.eax == kEveryDevice)
    {
        for (const reg32 device : {kTheMouse, kTheKeyboard, kAllJoysticks})
        {
            cpu.eax = device;
            if (!direct(app, cpu, unacquireDevice))
                return;
        }
    }
    else if (cpu.eax == kAllJoysticks)
    {
        cpu.edx ^= cpu.eax;
        do
        {
            cpu.eax = cpu.edx;
            if (!direct(app, cpu, unacquireDevice))
                return;
            ++cpu.edx;
        } while (sreg32(cpu.edx) < 0x10);
        return leave(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.edx, &cpu.esi});
    }
    if (cpu.edx == kTheMouse)
    {
        cpu.edx = at(app, kMouse);
        if (cpu.edx != 0)
        {
            cpu.eax = cpu.edx;
            if (!unacquire(cpu.eax))
                return;
        }
    }
    else if (cpu.edx == kTheKeyboard)
    {
        cpu.ecx = at(app, kKeyboard);
        if (cpu.ecx != 0 && !unacquire(cpu.ecx))
            return;
    }
    else if (sreg32(cpu.edx) >= 0 && sreg32(cpu.edx) < 0x10)
    {
        cpu.eax = cpu.edx * 4;
        cpu.esi = at(app, cpu.eax + kJoysticks);
        if (cpu.esi != 0 && !unacquire(cpu.esi))
            return;
    }
    leave(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.edx, &cpu.esi});
}

/* 0x4368c0: whether Acquire's HRESULT eax says the device is acquired: 1 for
 * DI_OK and S_FALSE (already), 0 for anything else. */
void acquireResult(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    if (cpu.eax == 0)
        cpu.eax = 1;
    else if (cpu.eax != 1)
        cpu.eax = 0;
    cpu.ebp = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x4368f0: whether effect ax plays: 0 for none, and for one whose type is
 * 0 (a constant force). */
void effectPlaying(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    if (x86::sreg16(cpu.ax) < 0)
        cpu.eax = 0;
    else
    {
        cpu.edx = reg32(sreg32(x86::sreg16(cpu.ax)));
        cpu.eax = times17(cpu.edx);
        cpu.eax <<= 3;
        cpu.eax = at(app, cpu.eax + kEffectType) == 0 ? 0 : at(app, cpu.eax + kEffectPlaying);
    }
    cpu.ebp = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x436930: the window's WM_SETCURSOR handler while the mouse is open
 * (stdcall, 6 words): the one before it called with them, then no cursor
 * (SetCursor(0), ShowCursor(FALSE)).  1. */
void hideCursor(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    const reg32 ebp = cpu.ebp;
    if (at(app, kOldSetCursor) != 0)
    {
        cpu.ecx = at(app, ebp + 0x28);
        push(app, cpu, cpu.ecx);
        cpu.ebx = at(app, ebp + 0x24);
        push(app, cpu, cpu.ebx);
        cpu.esi = at(app, ebp + 0x20);
        push(app, cpu, cpu.esi);
        cpu.edi = at(app, ebp + 0x1c);
        push(app, cpu, cpu.edi);
        cpu.eax = at(app, ebp + 0x18);
        push(app, cpu, cpu.eax);
        cpu.edx = at(app, ebp + 0x14);
        push(app, cpu, cpu.edx);
        if (!byAddress(app, cpu, at(app, kOldSetCursor)))
            return;
    }
    push(app, cpu, 0);
    if (!byAddress(app, cpu, at(app, kSetCursor)))
        return;
    push(app, cpu, 0);
    if (!byAddress(app, cpu, at(app, kShowCursor)))
        return;
    cpu.eax = 1;
    cpu.ebp = pop(app, cpu);
    cpu.edi = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4 + 0x18;
}

/* 0x436980: EnumDevices' callback (stdcall: the DIDEVICEINSTANCE, the
 * DirectInput it was handed) for each joystick attached: the next record
 * named after its product, its kind from its subtype (a wheel 2, a gamepad
 * 4, else 1); the device made, its format a joystick's, its
 * IDirectInputDevice2 kept, exclusive in the background -- one more
 * joystick.  1 to go on, 0 to stop when the cooperative level fails. */
void joystickFound(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.ebx, &cpu.esi, &cpu.edi}, 4);
    const reg32 ebp = cpu.ebp;
    auto done = [&] { leave(app, cpu, {&cpu.ebx, &cpu.esi, &cpu.edi}, 8); };
    // Its record's name: the product's, 0x32 characters, ended.
    cpu.edx = at(app, kJoystickCount);
    cpu.eax = times17(cpu.edx);
    cpu.eax <<= 3;
    cpu.dl = 0;
    putByte(app, cpu.eax + kJoystickName, cpu.dl);
    cpu.eax += kJoystickRecords;
    cpu.edi = cpu.eax + 4;
    cpu.ecx = 0xffffffff;
    cpu.eax = 0;
    while (cpu.ecx != 0)
    {
        const x86::reg8 b = byte(app, cpu.edi);
        ++cpu.edi;
        --cpu.ecx;
        if (b == cpu.al)
            break;
    }
    cpu.ecx = ~cpu.ecx;
    --cpu.ecx;
    cpu.edx = at(app, kJoystickCount);
    cpu.eax = cpu.edx;
    cpu.ebx = 0x32;
    cpu.eax <<= 4;
    cpu.ebx -= cpu.ecx;
    cpu.eax += cpu.edx;
    cpu.ecx = at(app, ebp + 0x14);
    cpu.eax <<= 3;
    cpu.ecx += 0x12c;  // tszProductName
    cpu.eax += kJoystickRecords;
    cpu.edx = cpu.ecx;
    cpu.eax += 4;
    if (!direct(app, cpu, watcom::strncpy))
        return;
    cpu.edx = at(app, kJoystickCount);
    cpu.eax = cpu.edx;
    cpu.eax <<= 4;
    cpu.ecx = at(app, ebp + 0x14);
    cpu.edx += cpu.eax;
    cpu.bl = 0;
    cpu.edx <<= 3;
    cpu.eax = 0;
    putByte(app, cpu.edx + kJoystickNameEnd, cpu.bl);
    cpu.ax = app->getMemory<x86::reg16>(cpu.ecx + 0x24);  // dwDevType's subtype
    cpu.eax = reg32(sreg32(cpu.eax) >> 8);
    cpu.eax &= 0xff;
    cpu.esi = at(app, ebp + 0x18);
    if (cpu.al == 4)  // DIDEVTYPEJOYSTICK_GAMEPAD
        put(app, cpu.edx + kJoystickRecords, 4);
    else if (cpu.al == 6)  // DIDEVTYPEJOYSTICK_WHEEL
        put(app, cpu.edx + kJoystickRecords, 2);
    else
    {
        cpu.edx = at(app, kJoystickCount);
        cpu.eax = times17(cpu.edx);
        put(app, cpu.eax * 8 + kJoystickRecords, 1);
    }
    // CreateDevice(DirectInput, its guidInstance, &[ebp - 4], none)
    push(app, cpu, 0);
    cpu.eax = ebp - 4;
    push(app, cpu, cpu.eax);
    cpu.eax = at(app, ebp + 0x14);
    cpu.eax += 4;
    push(app, cpu, cpu.eax);
    cpu.edx = at(app, cpu.esi);
    push(app, cpu, cpu.esi);
    if (!directInput(app, cpu, Object::DirectInput, kCreateDevice))
        return;
    if (cpu.eax != 0)
    {
        cpu.eax = 1;
        return done();
    }
    // Released, it goes on to the next.
    auto release = [&](reg32* r) {
        *r = at(app, ebp - 4);
        cpu.eax = at(app, ebp - 4);
        push(app, cpu, *r);
        cpu.eax = at(app, cpu.eax);
        if (!directInput(app, cpu, Object::Device, kRelease))
            return false;
        cpu.eax = 1;
        return true;
    };
    push(app, cpu, kJoystickFormat);
    cpu.edx = at(app, ebp - 4);
    cpu.eax = at(app, ebp - 4);
    push(app, cpu, cpu.edx);
    cpu.eax = at(app, cpu.eax);
    if (!directInput(app, cpu, Object::Device, kSetDataFormat))
        return;
    if (cpu.eax != 0)
    {
        if (!release(&cpu.ecx))
            return;
        return done();
    }
    // QueryInterface(the device, IID_IDirectInputDevice2A, &the joystick's)
    cpu.eax = at(app, ebp - 4);
    cpu.edx = at(app, cpu.eax);
    cpu.eax = at(app, kJoystickCount);
    cpu.eax <<= 2;
    cpu.eax += kJoysticks;
    push(app, cpu, cpu.eax);
    push(app, cpu, kDevice2Interface);
    cpu.ebx = at(app, ebp - 4);
    push(app, cpu, cpu.ebx);
    if (!directInput(app, cpu, Object::Device, kQueryInterface))
        return;
    if (cpu.eax != 0)
    {
        if (!release(&cpu.esi))
            return;
        return done();
    }
    cpu.edx = 9;  // DISCL_EXCLUSIVE | DISCL_BACKGROUND
    cpu.eax = at(app, kJoystickCount);
    if (!direct(app, cpu, setCooperativeLevel))
        return;
    if (cpu.eax == 0)
        return done();
    if (!release(&cpu.edi))
        return;
    put(app, kJoystickCount, at(app, kJoystickCount) + cpu.eax);
    done();
}

/* 0x436b10: joystick eax's dead zone (ecx 0) or saturation (ecx not 0) of
 * axis edx -- 8 the whole device -- asked for (ebx not 0) or set to the
 * stack's percent (0 to 100) (stdcall, 1 word).  In percent, or -1 for no
 * such joystick or axis, or what DirectInput would not. */
void axisProperty(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.esi, &cpu.edi}, 0x14);
    const reg32 ebp = cpu.ebp;
    auto done = [&] { leave(app, cpu, {&cpu.esi, &cpu.edi}, 4); };
    cpu.esi = cpu.eax;
    cpu.eax = cpu.edx;
    cpu.edx = at(app, ebp + 0x10);
    if (sreg32(cpu.esi) >= 0x10 || sreg32(cpu.esi) < 0 || sreg32(cpu.eax) > 8)
    {
        cpu.eax = 0xffffffff;
        return done();
    }
    cpu.edi = cpu.esi;
    cpu.edi <<= 2;
    if (at(app, cpu.edi + kJoysticks) == 0)
    {
        cpu.eax = 0xffffffff;
        return done();
    }
    if (cpu.esi == kAllJoysticks || cpu.esi == kEveryDevice)
    {
        // Never: esi is a joystick's here.
        push(app, cpu, cpu.edx);
        cpu.edx = cpu.eax;
        cpu.eax = cpu.esi;
        if (!direct(app, cpu, axisProperty))
            return;
        return done();
    }
    // {0x14, 0x10, the axis's offset in DIJOYSTATE, DIPH_BYOFFSET} or the device's.
    put(app, ebp - 0x14, 0x14);
    put(app, ebp - 0x10, 0x10);
    if (cpu.eax == 8)
    {
        cpu.eax = 0;
        put(app, ebp - 8, cpu.eax);
        put(app, ebp - 0xc, cpu.eax);
    }
    else
    {
        cpu.eax = at(app, cpu.eax * 4 + kHatOffsets);
        put(app, ebp - 0xc, cpu.eax);
        put(app, ebp - 8, 1);
    }
    // DIPROP_DEADZONE (5) or DIPROP_SATURATION (6).
    if (cpu.ebx != 0)
    {
        cpu.eax = ebp - 0x14;
        cpu.edx = at(app, cpu.esi * 4 + kJoysticks);
        push(app, cpu, cpu.eax);
        cpu.edx = at(app, cpu.edx);
        cpu.eax = cpu.ecx == 0 ? 5 : 6;
        push(app, cpu, cpu.eax);
        cpu.ecx = at(app, cpu.esi * 4 + kJoysticks);
        push(app, cpu, cpu.ecx);
        if (!directInput(app, cpu, Object::Device, kGetProperty))
            return;
    }
    else
    {
        if (sreg32(cpu.edx) < 0)
            cpu.edx = 0;
        else if (sreg32(cpu.edx) > 0x64)
            cpu.edx = 0x64;
        cpu.eax = cpu.edx * 4;
        cpu.eax -= cpu.edx;
        cpu.eax <<= 3;
        cpu.eax += cpu.edx;
        cpu.eax <<= 2;
        cpu.edx = at(app, cpu.esi * 4 + kJoysticks);
        put(app, ebp - 4, cpu.eax);
        cpu.eax = ebp - 0x14;
        cpu.edx = at(app, cpu.edx);
        push(app, cpu, cpu.eax);
        cpu.eax = cpu.ecx == 0 ? 5 : 6;
        push(app, cpu, cpu.eax);
        cpu.ebx = at(app, cpu.esi * 4 + kJoysticks);
        push(app, cpu, cpu.ebx);
        if (!directInput(app, cpu, Object::Device, kSetProperty))
            return;
    }
    if (sreg32(cpu.eax) < 0)
    {
        cpu.eax = 0xffffffff;
        return done();
    }
    cpu.eax = at(app, ebp - 4);
    cpu.edx = cpu.eax;
    cpu.ecx = 0x64;
    cpu.edx = reg32(sreg32(cpu.edx) >> 31);
    const std::int64_t dividend = std::int64_t(sreg32(cpu.eax));
    cpu.eax = reg32(sreg32(dividend / 0x64));
    cpu.edx = reg32(sreg32(dividend % 0x64));
    done();
}

}  // namespace controls
}  // namespace nfs3hp
