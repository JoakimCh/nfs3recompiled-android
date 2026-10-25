#include "native_guest.h"

/* EA's formats and keys under the menus: a shape located in its file
 * (cmn\locatshp.c), the keys (win\key.c: a key's character, the key hook's
 * key, inkey, the game's keys flushed), the packed data (cmn\unpack.c,
 * cmn\loadpack.c: unpack, unpacksize, loadpackadr), and between them in the
 * code the secondary timer's end (win\lowtimer.c: a callback removed, the
 * thread stopped).  disassemble_nfs3hp.py binds each address to the
 * function of that name here (EA_FORMATS_NATIVES), and the generated code
 * calls it by name.  tools/game_checks holds each against its generated code.
 *
 * A shape file ("SHPI") has its count at +8 and from +0x10 an entry of 8
 * bytes for each shape: its name, four characters, and where the shape is
 * from the file's start.
 *
 * The keys: their state a byte each by scan code at 0x564818 (Ctrl's
 * 0x564835, the Shifts' 0x564842 and 0x56484e, Alt's 0x564850); Ctrl+Esc
 * leaving the game when 0x564810 is set; Caps Lock's state at 0x564814,
 * flipped by its scan code (0x3a).  A scan code's character is in one of
 * five tables of 0x5b bytes -- plain (0x564898), shifted (0x5648f3), with
 * Caps Lock (0x56494e), with Ctrl (0x5649a9), with Alt (0x564a04) -- and
 * one of 0x80 or more is a key of its own: shifted up a byte (0x90 on
 * without their top bit).  The key hook (0x5651d0, set by the window's
 * code) hands back the next key, 0 for none.
 *
 * Packed data starts with its code -- 0x10, 0x18, 0x30, 0x32, 0x34, 0x46 or
 * 0x4a and that plus 1 -- then 0xfb (or 0x32), then its size unpacked in
 * three bytes, big-endian; each code's own unpacker (0x5102a4, 0x510760,
 * 0x50ed50, 0x510870, 0x510110) unpacks it from eax to edx.  A code not known
 * is an Error when the game's errors are on ([0x56440c] for unpack).
 *
 * The secondary timer: a thread (0x4f27a0, its id at 0x5652ac, 0 once it
 * has ended, its record at 0x9f0c20) that calls the eight callbacks of
 * 0x9f0c00 in turn, under the lock at 0x9f0c34 (0 when there is no timer).
 *
 * Written as their code is: each push and pop to the guest's stack, each call
 * with the return address's slot, the frame's locals in the guest's memory,
 * the registers as the code leaves them.  The waits' loops have the
 * generated code's safepoints.  The key hook is called through its slot,
 * Windows' functions through their imports' slots; every other function of
 * the game's by address, the unpackers and the menus' key taken (0x4cc970)
 * too; this file's own directly. */
namespace nfs3hp
{
namespace ea
{

namespace
{

using guest::at;
using guest::byte;
using guest::put;
using x86::reg32;
using x86::reg8;

// Where an Error is from: the file, the function, the line.
constexpr reg32 kWhereFile = 0x552190, kWhereFunction = 0x552194, kWhereLine = 0x552198;
// The game's errors on.
constexpr reg32 kErrorsFatal = 0x56440c;
// The keys: Ctrl, the left and right Shifts, Alt held; Ctrl+Esc leaving the
// game; Caps Lock on.
constexpr reg32 kCtrlHeld = 0x564835, kLeftShiftHeld = 0x564842, kRightShiftHeld = 0x56484e;
constexpr reg32 kAltHeld = 0x564850, kCtrlEscapeQuits = 0x564810, kCapsLock = 0x564814;
constexpr reg32 kCapsLockKey = 0x3a, kEscapeKey = 1;
// The characters by scan code: plain, shifted, with Caps Lock, Ctrl, Alt.
constexpr reg32 kPlainKeys = 0x564898, kShiftedKeys = 0x5648f3, kCapsKeys = 0x56494e;
constexpr reg32 kCtrlKeys = 0x5649a9, kAltKeys = 0x564a04;
// The key hook.
constexpr reg32 kKeyHook = 0x5651d0;
// The secondary timer: its callbacks, its lock, its thread's record and id.
constexpr reg32 kTimerCallbacks = 0x9f0c00, kLastTimerCallback = 0x9f0c1c, kTimerLock = 0x9f0c34;
constexpr reg32 kTimerThread = 0x9f0c20, kTimerThreadId = 0x5652ac;
constexpr reg32 kTimerSlots = 8;
// The game's strings: win\key.c's, cmn\unpack.c's, cmn\loadpack.c's.
constexpr reg32 kKeyC = 0x54c660, kInkeyName = 0x54c66c, kInkeyLine = 0x1da;
constexpr reg32 kUnpackC = 0x54cb68, kUnpackName = 0x54cb78, kUnpackInvalid = 0x54cb80, kUnpackLine = 0x6d;
constexpr reg32 kUnpackSizeName = 0x54cba4, kUnpackSizeInvalid = 0x54cbb0, kUnpackSizeLine = 0xc9;
constexpr reg32 kLoadpackC = 0x54cc34, kLoadpackName = 0x54cc44, kLoadpackLine = 0xaf, kLoadpackLine2 = 0xb6;
// The packed data's marks.
constexpr reg8 kPackMark = 0xfb, kOtherPackMark = 0x32;
// Windows' functions, by their imports' slots.
constexpr reg32 kEnterCriticalSection = 0x5344b8, kLeaveCriticalSection = 0x534588;
// The game's functions, by address.
constexpr reg32 kError = 0x401010, kSleep = 0x4df8e0, kOnThread = 0x4df930, kSignalEvent = 0x4dfb30;
constexpr reg32 kExit = 0x4dfd04, kLoadFile = 0x4e0ec0, kMemBlockSize = 0x4e15d0, kReserve = 0x4e1620;
constexpr reg32 kPurge = 0x4e1890, kRunSystemTasks = 0x4e7630, kMoveMemory = 0x4ea4f0, kFreeLock = 0x4eb360;
constexpr reg32 kCheckSurfaceUnlocked = 0x501010, kTakeKey = 0x4cc970;
// The unpackers, by code.
constexpr reg32 kUnpack10 = 0x5102a4, kUnpack18 = 0x510760, kUnpack30 = 0x50ed50, kUnpack46 = 0x510870;
constexpr reg32 kUnpack4a = 0x510110;

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

/* A Windows function, through its import's slot. */
bool windows(win32::WinApplication* app, x86::CPU& cpu, reg32 slot)
{
    return byAddress(app, cpu, at(app, slot));
}

/* mov ecx, n; mov eax, [at]; bswap eax; neg ecx; lea ecx, [ecx*8 + 0x20];
 * shr eax, cl: the big-endian number of n bytes at `at` in eax, ecx the
 * shift. */
void bigEndian(win32::WinApplication* app, x86::CPU& cpu, reg32 address, reg32 bytes)
{
    cpu.eax = __builtin_bswap32(at(app, address));
    cpu.ecx = 0x20 - 8 * bytes;
    cpu.eax >>= cpu.cl & 0x1f;
}

/* The Error of a code not known with `format`, the data's two first bytes
 * (big-endian) its argument: ecx left 0x10, the shift. */
bool invalidPackCode(win32::WinApplication* app, x86::CPU& cpu, reg32 data, reg32 format)
{
    bigEndian(app, cpu, data, 2);
    push(app, cpu, cpu.eax);
    push(app, cpu, format);
    if (!byAddress(app, cpu, kError))
        return false;
    cpu.esp += 8;
    return true;
}

}  // namespace

void stopLowTimer(win32::WinApplication* app, x86::CPU& cpu);
void unpackQuietly(win32::WinApplication* app, x86::CPU& cpu);
void unpackSizeQuietly(win32::WinApplication* app, x86::CPU& cpu);

/* 0x4ef270: the shape named [edx] (four characters) in the shape file at
 * eax -- the last of that name -- or 0: eax the shape's address, edx left
 * at the entry the search stopped at. */
void locateShape(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    cpu.ebx = cpu.eax;
    cpu.eax = at(app, cpu.eax + 8);
    cpu.ecx = at(app, cpu.edx);
    const auto leave = [&] {
        cpu.ecx = pop(app, cpu);
        cpu.ebx = pop(app, cpu);
        cpu.esp += 4;
    };
    if (cpu.eax == 0)
    {
        cpu.eax = 0;
        return leave();
    }
    cpu.edx = cpu.eax * 8;
    cpu.edx += cpu.ebx;
    do
    {
        cpu.edx -= 8;
        --cpu.eax;
    } while (cpu.eax != 0 && cpu.ecx != at(app, cpu.edx + 0x10));
    cpu.eax <<= 3;
    cpu.eax += cpu.ebx;
    if (cpu.ecx != at(app, cpu.eax + 0x10))
    {
        cpu.eax = 0;
        return leave();
    }
    cpu.eax = at(app, cpu.eax + 0x14);
    cpu.eax += cpu.ebx;
    leave();
}

/* 0x4f0010: the character of scan code eax as the keys held say -- Alt's,
 * Ctrl's, Shift's, Caps Lock's or the plain one; 0x80 to 0x8f shifted up a
 * byte, 0x90 on without their top bit and shifted up a byte.  Caps Lock's
 * own key flips its state, 0 back; Ctrl+Esc leaves the game (exit 0) when
 * 0x564810 says so, and gives Ctrl's character if it comes back. */
void keyCharacter(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    cpu.ebx = cpu.eax;
    cpu.eax = 0;
    const auto leave = [&] {
        cpu.ecx = pop(app, cpu);
        cpu.ebx = pop(app, cpu);
        cpu.esp += 4;
    };
    if (cpu.ebx == kCapsLockKey)
    {
        cpu.ecx = at(app, kCapsLock) == 0 ? 1 : 0;
        put(app, kCapsLock, cpu.ecx);
        return leave();
    }
    if (byte(app, kAltHeld) != 0)
        cpu.ecx = kAltKeys;
    else if (byte(app, kCtrlHeld) != 0)
    {
        if (at(app, kCtrlEscapeQuits) != 0 && cpu.ebx == kEscapeKey)
        {
            cpu.eax = 0;
            if (!byAddress(app, cpu, kExit))
                return;
        }
        else
            cpu.ecx = kCtrlKeys;
    }
    else if (byte(app, kLeftShiftHeld) != 0 || byte(app, kRightShiftHeld) != 0)
        cpu.ecx = kShiftedKeys;
    else if (at(app, kCapsLock) != 0)
        cpu.ecx = kCapsKeys;
    else
        cpu.ecx = kPlainKeys;
    cpu.eax = cpu.ecx + cpu.ebx;
    cpu.al = byte(app, cpu.eax);
    cpu.eax &= 0xff;
    if (cpu.eax >= 0x80)
    {
        if (cpu.eax >= 0x90)
            cpu.eax &= 0x7f;
        cpu.eax <<= 8;
    }
    leave();
}

/* 0x4f0100: the key hook's next key (0x5651d0), 0 for none or without a
 * hook. */
void keyFromHook(win32::WinApplication* app, x86::CPU& cpu)
{
    if (at(app, kKeyHook) == 0)
    {
        cpu.eax = 0;
        cpu.esp += 4;
        return;
    }
    if (!byAddress(app, cpu, at(app, kKeyHook)))
        return;
    cpu.esp += 4;
}

/* 0x4f0120: inkey -- win\key.c's, files not to be touched with a surface
 * locked (checkSurfaceUnlocked) -- then the game's tasks run (0x4e7630)
 * until the key hook gives a key: eax it. */
void inkey(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.ebx);
    cpu.edx = kKeyC;
    cpu.ecx = kInkeyName;
    cpu.ebx = kInkeyLine;
    put(app, kWhereFile, cpu.edx);
    put(app, kWhereFunction, cpu.ecx);
    cpu.eax = cpu.ecx;
    put(app, kWhereLine, cpu.ebx);
    if (!byAddress(app, cpu, kCheckSurfaceUnlocked))
        return;
    cpu.ebx = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    do
    {
        if (app->contextWanted())
            app->yieldContext(cpu);
        cpu.eax = 0;
        if (!byAddress(app, cpu, kRunSystemTasks) || !direct(app, cpu, keyFromHook))
            return;
    } while (cpu.eax == 0);
    cpu.esp += 4;
}

/* 0x4f0240: the keys the menus have (0x4cc970) taken until there are none. */
void flushKeys(win32::WinApplication* app, x86::CPU& cpu)
{
    do
    {
        if (app->contextWanted())
            app->yieldContext(cpu);
        if (!byAddress(app, cpu, kTakeKey))
            return;
    } while (cpu.eax != 0);
    cpu.esp += 4;
}

/* 0x4f2560: the packed data at eax unpacked to edx by its code's unpacker
 * (ebx 1 for those that take it; 0x4a's its size); eax the size unpacked,
 * 0 for a code not known -- without an Error. */
void unpackQuietly(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.esi);
    cpu.esi = cpu.eax;
    cpu.ah = byte(app, cpu.eax + 1);
    cpu.ebx = 0;
    const auto leave = [&] {
        cpu.eax = cpu.ebx;
        cpu.esi = pop(app, cpu);
        cpu.ebx = pop(app, cpu);
        cpu.esp += 4;
    };
    // One of the unpackers: eax the data, ebx 1 or as it is; its result.
    const auto unpacker = [&](reg32 target, bool one) {
        if (one)
            cpu.ebx = 1;
        cpu.eax = cpu.esi;
        if (!byAddress(app, cpu, target))
            return;
        cpu.ebx = cpu.eax;
        leave();
    };
    if (cpu.ah != kPackMark && byte(app, cpu.esi + 1) != kOtherPackMark)
        return leave();
    cpu.al = byte(app, cpu.esi);
    cpu.al &= 0xfe;
    if (cpu.al < 0x32)
    {
        if (cpu.al >= 0x18)
        {
            if (cpu.al == 0x18)
                return unpacker(kUnpack18, true);
            if (cpu.al == 0x30)
                return unpacker(kUnpack30, true);
            return leave();
        }
        if (cpu.al == 0x10)
            return unpacker(kUnpack10, true);
        return leave();
    }
    if (cpu.al == 0x32)
        return unpacker(kUnpack30, true);
    if (cpu.al < 0x46)
    {
        if (cpu.al == 0x34)
            return unpacker(kUnpack30, true);
        return leave();
    }
    if (cpu.al == 0x46)
        return unpacker(kUnpack46, false);
    if (cpu.al != 0x4a)
        return leave();
    push(app, cpu, cpu.ecx);
    bigEndian(app, cpu, cpu.esi + 2, 3);
    cpu.ebx = cpu.eax;
    cpu.eax = cpu.esi;
    if (!byAddress(app, cpu, kUnpack4a))
        return;
    cpu.ecx = pop(app, cpu);
    leave();
}

/* 0x4f2620: unpack -- the packed data at eax unpacked to edx (0x4f2560); a
 * code not known an Error ("unpack - INVALID PACK CODE") when the game's
 * errors are on and the data looks packed (a code of 0x10 to 0x7f, 0xfb).
 * eax and edx the size unpacked, or 0. */
void unpack(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ebp);
    cpu.ebx = cpu.eax;
    if (!direct(app, cpu, unpackQuietly))
        return;
    cpu.edx = cpu.eax;
    const auto leave = [&] {
        cpu.eax = cpu.edx;
        cpu.ebp = pop(app, cpu);
        cpu.ebx = pop(app, cpu);
        cpu.esp += 4;
    };
    if (cpu.eax != 0 || at(app, kErrorsFatal) == 0)
        return leave();
    cpu.ah = byte(app, cpu.ebx);
    if (cpu.ah < 0x10 || cpu.ah >= 0x80 || byte(app, cpu.ebx + 1) != kPackMark)
        return leave();
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.ecx);
    cpu.esi = kUnpackC;
    cpu.edi = kUnpackName;
    cpu.ebp = kUnpackLine;
    cpu.eax = cpu.ebx;
    put(app, kWhereFile, cpu.esi);
    put(app, kWhereFunction, cpu.edi);
    put(app, kWhereLine, cpu.ebp);
    if (!invalidPackCode(app, cpu, cpu.eax, kUnpackInvalid))
        return;
    cpu.ecx = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.edi = pop(app, cpu);
    leave();
}

/* 0x4f26a0: the size the packed data at eax unpacks to (its three bytes
 * past the code and the mark), 0 for a code not known -- without an Error. */
void unpackSizeQuietly(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    cpu.edx = cpu.eax;
    cpu.ah = byte(app, cpu.eax + 1);
    cpu.ecx = 0;
    const auto leave = [&] {
        cpu.eax = cpu.ecx;
        cpu.edx = pop(app, cpu);
        cpu.ecx = pop(app, cpu);
        cpu.esp += 4;
    };
    const auto size = [&] {
        bigEndian(app, cpu, cpu.edx + 2, 3);
        cpu.ecx = cpu.eax;
        leave();
    };
    if (cpu.ah != kPackMark && byte(app, cpu.edx + 1) != kOtherPackMark)
        return leave();
    cpu.al = byte(app, cpu.edx);
    cpu.al &= 0xfe;
    if (cpu.al < 0x32)
    {
        if (cpu.al >= 0x18)
            return cpu.al == 0x18 || cpu.al == 0x30 ? size() : leave();
        return cpu.al == 0x10 ? size() : leave();
    }
    if (cpu.al == 0x32)
        return size();
    if (cpu.al < 0x46)
        return cpu.al == 0x34 ? size() : leave();
    if (cpu.al == 0x46)
        return size();
    return cpu.al == 0x4a ? size() : leave();
}

/* 0x4f2710: unpacksize -- the size the packed data at eax unpacks to
 * (0x4f26a0); a code not known an Error ("unpacksize - INVALID PACK CODE")
 * where the data looks packed (a code of 0x10 to 0x7f, 0xfb). */
void unpacksize(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.edx);
    cpu.edx = cpu.eax;
    if (!direct(app, cpu, unpackSizeQuietly))
        return;
    cpu.ebx = cpu.eax;
    const auto leave = [&] {
        cpu.eax = cpu.ebx;
        cpu.edx = pop(app, cpu);
        cpu.ebx = pop(app, cpu);
        cpu.esp += 4;
    };
    if (cpu.eax != 0)
        return leave();
    cpu.ah = byte(app, cpu.edx);
    if (cpu.ah < 0x10 || cpu.ah >= 0x80 || byte(app, cpu.edx + 1) != kPackMark)
        return leave();
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.ecx);
    cpu.ecx = kUnpackC;
    cpu.esi = kUnpackSizeName;
    cpu.edi = kUnpackSizeLine;
    cpu.eax = cpu.edx;
    put(app, kWhereFile, cpu.ecx);
    put(app, kWhereFunction, cpu.esi);
    put(app, kWhereLine, cpu.edi);
    if (!invalidPackCode(app, cpu, cpu.eax, kUnpackSizeInvalid))
        return;
    cpu.ecx = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.edi = pop(app, cpu);
    leave();
}

/* 0x4f2830: the secondary timer stopped (win\lowtimer.c; its exit
 * function): its lock taken and done with ([0x9f0c34] 0), its thread woken
 * to end (its event set), and -- but on that thread itself -- waited for
 * until it has ended ([0x5652ac] 0). */
void stopLowTimer(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    const auto leave = [&] {
        cpu.edx = pop(app, cpu);
        cpu.ecx = pop(app, cpu);
        cpu.ebx = pop(app, cpu);
        cpu.esp += 4;
    };
    cpu.edx = at(app, kTimerLock);
    if (cpu.edx == 0)
        return leave();
    push(app, cpu, cpu.edx);
    cpu.ebx = cpu.edx;
    if (!windows(app, cpu, kEnterCriticalSection))
        return;
    cpu.ecx = 0;
    cpu.eax = at(app, kTimerThreadId);
    put(app, kTimerLock, cpu.ecx);
    if (!byAddress(app, cpu, kSignalEvent))
        return;
    push(app, cpu, cpu.ebx);
    if (!windows(app, cpu, kLeaveCriticalSection))
        return;
    cpu.eax = cpu.ebx;
    if (!byAddress(app, cpu, kFreeLock))
        return;
    cpu.eax = kTimerThread;
    if (!byAddress(app, cpu, kOnThread))
        return;
    if (cpu.eax != 0)
        return leave();
    cpu.ebx = 0;
    for (;;)
    {
        if (app->contextWanted())
            app->yieldContext(cpu);
        if (cpu.ebx == at(app, kTimerThreadId))
            return leave();
        cpu.eax = cpu.ebx;
        if (!byAddress(app, cpu, kSleep))
            return;
    }
}

/* 0x4f29b0: the secondary timer's callback eax removed (win\lowtimer.c),
 * those after it moved down a slot, under its lock; the timer stopped
 * (0x4f2830) when none is left.  Nothing without a timer. */
void removeLowTimer(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.esi);
    cpu.ebx = cpu.eax;
    const auto leave = [&] {
        cpu.esi = pop(app, cpu);
        cpu.edx = pop(app, cpu);
        cpu.ecx = pop(app, cpu);
        cpu.ebx = pop(app, cpu);
        cpu.esp += 4;
    };
    cpu.edx = at(app, kTimerLock);
    if (cpu.edx == 0)
        return leave();
    push(app, cpu, cpu.edx);
    if (!windows(app, cpu, kEnterCriticalSection))
        return;
    cpu.esi = at(app, kTimerCallbacks);
    cpu.edx = 0;
    cpu.eax = 0;
    if (cpu.ebx != cpu.esi)
    {
        do
        {
            cpu.eax += 4;
            ++cpu.edx;
        } while (x86::sreg32(cpu.eax) < 0x20 && cpu.ebx != at(app, cpu.eax + kTimerCallbacks));
    }
    if (x86::sreg32(cpu.edx) < x86::sreg32(kTimerSlots))
    {
        cpu.eax = cpu.edx * 4;
        if (cpu.ebx == at(app, cpu.eax + kTimerCallbacks))
        {
            if (x86::sreg32(cpu.edx) < 7)
            {
                do
                {
                    cpu.eax += 4;
                    cpu.edx = at(app, cpu.eax + kTimerCallbacks);
                    put(app, cpu.eax + kTimerCallbacks - 4, cpu.edx);
                } while (x86::sreg32(cpu.eax) < 0x1c);
            }
            cpu.eax = 0;
            put(app, kLastTimerCallback, cpu.eax);
        }
    }
    cpu.edx = at(app, kTimerLock);
    push(app, cpu, cpu.edx);
    if (!windows(app, cpu, kLeaveCriticalSection))
        return;
    cpu.ecx = at(app, kTimerCallbacks);
    cpu.eax = 0;
    if (cpu.ecx != 0)
        return leave();
    for (;;)
    {
        cpu.eax += 4;
        if (x86::sreg32(cpu.eax) >= 0x20)
            break;
        if (at(app, cpu.eax + kTimerCallbacks) != 0)
            return leave();
    }
    if (!direct(app, cpu, stopLowTimer))
        return;
    leave();
}

/* 0x4f2e20: loadpackadr -- the file named eax loaded (loadFile, edx its
 * memory's flags) and, if packed (unpacksize), unpacked: its packed bytes
 * copied to a block of their own (flags edx but 0x10) and the file's freed,
 * a block of the size unpacked (flags edx) unpacked into, the copy freed.
 * eax the file as loaded, the block unpacked, or 0 where a block was not
 * had; edx as the code leaves it. */
void loadpackadr(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.esp -= 0x10;
    const reg32 frame = cpu.esp;
    // The frame: the packed size's block, the size unpacked, the result, the
    // block to free.
    const reg32 packedBytes = frame, unpackedBytes = frame + 4, result = frame + 8, toFree = frame + 0xc;
    const auto leave = [&] {
        cpu.eax = at(app, result);
        cpu.esp += 0x10;
        cpu.ebp = pop(app, cpu);
        cpu.edi = pop(app, cpu);
        cpu.esi = pop(app, cpu);
        cpu.ecx = pop(app, cpu);
        cpu.ebx = pop(app, cpu);
        cpu.esp += 4;
    };
    cpu.edi = cpu.eax;
    cpu.ebp = cpu.edx;
    cpu.edx = 0;
    put(app, result, cpu.edx);
    cpu.edx = cpu.ebp;
    if (!byAddress(app, cpu, kLoadFile))
        return;
    cpu.ecx = cpu.eax;
    put(app, toFree, cpu.eax);
    if (cpu.eax == 0)
        return leave();
    if (!direct(app, cpu, unpacksize))
        return;
    put(app, unpackedBytes, cpu.eax);
    if (cpu.eax == 0)
    {
        put(app, result, cpu.ecx);
        return leave();
    }
    cpu.esi = kLoadpackC;
    cpu.eax = cpu.ecx;
    cpu.edx = kLoadpackLine;
    if (!byAddress(app, cpu, kMemBlockSize))
        return;
    cpu.ebx = cpu.ebp;
    put(app, packedBytes, cpu.eax);
    put(app, kWhereLine, cpu.edx);
    cpu.bl ^= 0x10;
    cpu.eax = kLoadpackName;
    cpu.edx = at(app, packedBytes);
    put(app, kWhereFunction, cpu.eax);
    cpu.eax = cpu.edi;
    put(app, kWhereFile, cpu.esi);
    if (!byAddress(app, cpu, kReserve))
        return;
    cpu.esi = cpu.eax;
    if (cpu.eax != 0)
    {
        cpu.ebx = at(app, packedBytes);
        cpu.edx = cpu.eax;
        cpu.eax = cpu.ecx;
        put(app, toFree, cpu.esi);
        if (!byAddress(app, cpu, kMoveMemory))
            return;
        cpu.ebx = kLoadpackName;
        cpu.eax = cpu.ecx;
        cpu.edx = at(app, unpackedBytes);
        if (!byAddress(app, cpu, kPurge))
            return;
        cpu.ecx = kLoadpackC;
        cpu.eax = kLoadpackLine2;
        put(app, kWhereFunction, cpu.ebx);
        put(app, kWhereLine, cpu.eax);
        cpu.ebx = cpu.ebp;
        cpu.eax = cpu.edi;
        put(app, kWhereFile, cpu.ecx);
        if (!byAddress(app, cpu, kReserve))
            return;
        put(app, result, cpu.eax);
        if (cpu.eax != 0)
        {
            cpu.edx = cpu.eax;
            cpu.eax = cpu.esi;
            if (!direct(app, cpu, unpack))
                return;
        }
    }
    cpu.edx = at(app, toFree);
    if (cpu.edx == 0)
        return leave();
    cpu.eax = cpu.edx;
    if (!byAddress(app, cpu, kPurge))
        return;
    leave();
}

}  // namespace ea
}  // namespace nfs3hp
