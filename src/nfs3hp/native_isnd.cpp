#include "isnd.h"
#include <lib/winapp.h>
#include <x86.h>

/* eacsnd's twelve exports native_sound.cpp leaves: the version, the game's
 * functions, recording, and the 3D buffers -- the functions at the bottom,
 * which disassemble_nfs3hp.py binds to the exports of those names, eacsnd
 * having no generated code -- with eacsnd's own data in guest memory as the
 * one copy.
 *
 * Each does what eacsnd's code does on the port: the same memory written in the
 * same order, the game's functions called with the same arguments at the same
 * stack addresses, the same result, the stack and ebx, esi, edi and ebp left as
 * a stdcall function leaves them.  The scratch registers and flags eacsnd
 * happened to leave are nobody's business: the game calls these through stdcall
 * pointers.
 *
 * eacsnd's other way, with DirectSound made (isnd::kDirectSoundMade) and 3D
 * buffers asked for (isnd::kIs3d), is not here: only eacsnd's start sets those,
 * and the port's start is native_sound.cpp's, which sets neither.  Should
 * either be set all the same, the sound* function steps aside before it has
 * done anything, and the export fails (notNative).
 *
 * tools/sound_checks compares the sound* functions with eacsnd's generated
 * code, made afresh from the DLL, on random states. */

namespace nfs3hp
{

namespace
{

x86::reg32 at(win32::WinApplication* app, x86::reg32 address)
{
    return app->getMemory<x86::reg32>(address);
}

void put(win32::WinApplication* app, x86::reg32 address, x86::reg32 value)
{
    app->getMemory<x86::reg32>(address) = value;
}

bool flag(win32::WinApplication* app, x86::reg32 address)
{
    return app->getMemory<x86::reg8>(address) != 0;
}

/* A stdcall export's return: the result in eax, the return address and the
 * arguments off the stack. */
bool returned(x86::CPU& cpu, x86::reg32 result, x86::reg32 argumentBytes)
{
    cpu.eax = result;
    cpu.esp += 4 + argumentBytes;
    return true;
}

/* A call out, with its arguments already pushed and esp at them: the return
 * address's slot taken, as a call takes it, though nothing is written there --
 * the generated code does not write it either.  False when the game is to
 * stop, and every function on the way out stops where it is. */
bool callOut(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 address)
{
    cpu.esp -= 4;
    app->dynamic_call(address, cpu);
    return !cpu.terminate;
}

/* A COM object's Release, IUnknown's third method: stdcall (this). */
bool release(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 object)
{
    cpu.esp -= 4;
    put(app, cpu.esp, object);
    return callOut(app, cpu, at(app, at(app, object) + 8));
}

x86::reg32 buffer(x86::reg32 index)
{
    return isnd::kBuffers + index * isnd::kBufferBytes;
}

/* iSNDdllversion(): 16.3, and the card's formats to be asked again. */
bool versionNative(win32::WinApplication* app, x86::CPU& cpu)
{
    put(app, isnd::kCapsKept, isnd::kFailure);
    return returned(cpu, isnd::kVersion, 0);
}

/* iSNDdirectsetfunctions(eight functions): kept, in their order. */
bool setFunctionsNative(win32::WinApplication* app, x86::CPU& cpu)
{
    for (x86::reg32 i = 0; i < 8; ++i)
        put(app, isnd::kFunctionMix + 4 * i, at(app, cpu.esp + 4 + 4 * i));
    return returned(cpu, 0, 0x20);
}

/* Recording: eacsnd has none to start, and nothing to hand over or stop. */
bool recordStartNative(win32::WinApplication*, x86::CPU& cpu)
{
    return returned(cpu, isnd::kFailure, 0x10);
}

bool recordPacketNative(win32::WinApplication*, x86::CPU& cpu)
{
    return returned(cpu, 0, 4);
}

bool recordStopNative(win32::WinApplication*, x86::CPU& cpu)
{
    return returned(cpu, 0, 0);
}

/* iSNDdirectvol(buffer, volume): the volume's byte kept. */
bool volumeNative(win32::WinApplication* app, x86::CPU& cpu)
{
    if (flag(app, isnd::kDirectSoundMade))
        return false;
    const x86::reg32 record = buffer(at(app, cpu.esp + 4));
    app->getMemory<x86::reg8>(record + isnd::kBufferVolume) = x86::reg8(at(app, cpu.esp + 8));
    return returned(cpu, 0, 8);
}

/* iSNDdirectrate(buffer, rate): the rate's word kept. */
bool rateNative(win32::WinApplication* app, x86::CPU& cpu)
{
    if (flag(app, isnd::kDirectSoundMade))
        return false;
    const x86::reg32 rate = at(app, cpu.esp + 8);
    const x86::reg32 record = buffer(at(app, cpu.esp + 4));
    app->getMemory<x86::reg16>(record + isnd::kBufferRate) = x86::reg16(rate);
    return returned(cpu, 0, 8);
}

/* iSNDdirectpos3d(buffer, a, b): the game's function asked where (a, b) is,
 * into three floats on the stack, which are scaled for DirectSound in the
 * x87's arithmetic -- for nothing, with no DirectSound, but as eacsnd does --
 * and the two words kept. */
bool positionNative(win32::WinApplication* app, x86::CPU& cpu)
{
    if (flag(app, isnd::kDirectSoundMade))
        return false;
    cpu.esp -= 0x14;
    const x86::reg32 position = cpu.esp;
    cpu.esp -= 4;
    put(app, cpu.esp, position);
    const x86::reg32 b = at(app, cpu.esp + 0x24);
    cpu.esp -= 4;
    put(app, cpu.esp, b);
    const x86::reg32 a = at(app, cpu.esp + 0x24);
    cpu.esp -= 4;
    put(app, cpu.esp, a);
    if (!callOut(app, cpu, at(app, isnd::kFunctionBufferPosition)))
        return true;

    const x86::reg32 esp = cpu.esp;
    const x86::Float x = x86::Float(app->getMemory<float>(esp));
    const x86::reg32 index = at(app, esp + 0x18);
    const x86::Float scale = x86::Float(app->getMemory<double>(isnd::kPositionScale));
    const x86::Float scaledX = x86::Float(x) * x86::Float(scale);
    app->getMemory<float>(esp) = float(x86::Float(scaledX));
    const x86::Float y = x86::Float(app->getMemory<float>(esp + 4));
    const x86::Float scaledY = x86::Float(y) * x86::Float(scale);
    app->getMemory<float>(esp + 4) = float(x86::Float(scaledY));
    const x86::Float z = x86::Float(app->getMemory<float>(esp + 8));
    const x86::Float scaledZ = scale * z;
    const x86::reg32 record = buffer(index);
    app->getMemory<float>(esp + 8) = float(x86::Float(scaledZ));
    app->getMemory<x86::reg16>(record + isnd::kBufferPositionA) = x86::reg16(at(app, esp + 0x1c));
    app->getMemory<x86::reg16>(record + isnd::kBufferPositionB) = x86::reg16(at(app, esp + 0x20));
    cpu.eax = 0;
    cpu.esp = esp + 0x14 + 4 + 0xc;
    return true;
}

/* iSNDdirectcreate3dbuf(seven): no slot -- 0 -- without both 3D buffers and
 * DirectSound. */
bool createBufferNative(win32::WinApplication* app, x86::CPU& cpu)
{
    if (flag(app, isnd::kIs3d) && flag(app, isnd::kDirectSoundMade))
        return false;
    return returned(cpu, 0, 0x1c);
}

/* iSNDdirectremovebuf(slot): -1 without 3D buffers; with them and no
 * DirectSound, the slot freed.  ebx is pushed and popped on that way, as
 * eacsnd does. */
bool removeBufferNative(win32::WinApplication* app, x86::CPU& cpu)
{
    if (!flag(app, isnd::kIs3d))
        return returned(cpu, isnd::kFailure, 4);
    if (flag(app, isnd::kDirectSoundMade))
        return false;
    const x86::reg32 esp = cpu.esp;
    put(app, esp - 4, cpu.ebx);
    const x86::reg32 slot = isnd::kSlots + at(app, esp + 4) * isnd::kSlotBytes;
    put(app, slot + isnd::kSlotId, 0);
    cpu.ebx = at(app, esp - 4);
    return returned(cpu, 0, 4);
}

/* iSNDdirectplay3d(slot, buffer, looping, rate, volume, a, b) without 3D
 * buffers: eacsnd jumps straight to its way out of a failure, which clears the
 * buffer record esi points at -- but esi is only set on the way that plays, so
 * the record it clears is wherever the caller's esi points.  Its two objects
 * there, the one that plays unless it is the slot's own, and the 3D one, are
 * released first, and -1 returned.  As eacsnd does, to the byte. */
bool playBufferNative(win32::WinApplication* app, x86::CPU& cpu)
{
    if (flag(app, isnd::kIs3d))
        return false;
    const x86::reg32 entry = cpu.esp;
    put(app, entry - 4, cpu.ebx);
    put(app, entry - 8, cpu.esi);
    put(app, entry - 0xc, cpu.edi);
    put(app, entry - 0x10, cpu.ebp);
    cpu.esp = entry - 0x10 - 0x64;

    /* esi as a call leaves it: a stdcall function keeps it, but it is what
     * eacsnd reads again after each. */
    const x86::reg32 active = at(app, cpu.esi + isnd::kBufferActive);
    if (active != 0 && active != at(app, cpu.esi + isnd::kBufferMain))
    {
        if (!release(app, cpu, active))
            return true;
    }
    const x86::reg32 object3d = at(app, cpu.esi + isnd::kBuffer3d);
    if (object3d != 0)
    {
        if (!release(app, cpu, object3d))
            return true;
    }
    put(app, cpu.esi + isnd::kBufferMain, 0);
    put(app, cpu.esi + isnd::kBufferActive, 0);
    put(app, cpu.esi + isnd::kBuffer3d, 0);

    const x86::reg32 frame = cpu.esp + 0x64;
    cpu.ebp = at(app, frame);
    cpu.edi = at(app, frame + 4);
    cpu.esi = at(app, frame + 8);
    cpu.ebx = at(app, frame + 0xc);
    cpu.esp = frame + 0x10;
    return returned(cpu, isnd::kFailure, 0x1c);
}

/* iSNDdirectstopbuf(buffer) with no DirectSound: the record's three objects
 * forgotten, and the game told through its own function (kFunctionStopBuffer)
 * that the buffer stopped. */
bool stopBufferNative(win32::WinApplication* app, x86::CPU& cpu)
{
    if (flag(app, isnd::kDirectSoundMade))
        return false;
    const x86::reg32 entry = cpu.esp;
    put(app, entry - 4, cpu.ebx);
    put(app, entry - 8, cpu.edi);
    cpu.esp = entry - 8;
    const x86::reg32 record = buffer(at(app, entry + 4));
    put(app, record + isnd::kBufferMain, 0);
    const x86::reg32 index = at(app, entry + 4);
    put(app, record + isnd::kBufferActive, 0);
    cpu.esp -= 4;
    put(app, cpu.esp, index);
    put(app, record + isnd::kBuffer3d, 0);
    if (!callOut(app, cpu, at(app, isnd::kFunctionStopBuffer)))
        return true;

    cpu.edi = at(app, cpu.esp);
    cpu.ebx = at(app, cpu.esp + 4);
    cpu.esp += 8;
    return returned(cpu, 0, 4);
}

}

bool soundVersion(win32::WinApplication* app, x86::CPU& cpu)
{
    return versionNative(app, cpu);
}

bool soundSetFunctions(win32::WinApplication* app, x86::CPU& cpu)
{
    return setFunctionsNative(app, cpu);
}

bool soundRecordStart(win32::WinApplication* app, x86::CPU& cpu)
{
    return recordStartNative(app, cpu);
}

bool soundRecordPacket(win32::WinApplication* app, x86::CPU& cpu)
{
    return recordPacketNative(app, cpu);
}

bool soundRecordStop(win32::WinApplication* app, x86::CPU& cpu)
{
    return recordStopNative(app, cpu);
}

bool soundVolume(win32::WinApplication* app, x86::CPU& cpu)
{
    return volumeNative(app, cpu);
}

bool soundPosition(win32::WinApplication* app, x86::CPU& cpu)
{
    return positionNative(app, cpu);
}

bool soundRate(win32::WinApplication* app, x86::CPU& cpu)
{
    return rateNative(app, cpu);
}

bool soundCreateBuffer(win32::WinApplication* app, x86::CPU& cpu)
{
    return createBufferNative(app, cpu);
}

bool soundRemoveBuffer(win32::WinApplication* app, x86::CPU& cpu)
{
    return removeBufferNative(app, cpu);
}

bool soundPlayBuffer(win32::WinApplication* app, x86::CPU& cpu)
{
    return playBufferNative(app, cpu);
}

bool soundStopBuffer(win32::WinApplication* app, x86::CPU& cpu)
{
    return stopBufferNative(app, cpu);
}

namespace
{

/* eacsnd's ways with DirectSound made or 3D buffers asked for, which nothing
 * on the port takes (see the top), and of which no code is left: should one
 * be taken all the same, the export fails as eacsnd's do -- -1, its arguments
 * off the stack -- and says so once. */
void notNative(x86::CPU& cpu, x86::reg32 argumentBytes)
{
    NFS2_ASSERT(false && "eacsnd with DirectSound: not native");
    cpu.eax = isnd::kFailure;
    cpu.esp += 4 + argumentBytes;
}

}

/* eacsnd's exports of these names (disassemble_nfs3hp.py). */
void iSNDdllversion(win32::WinApplication* app, x86::CPU& cpu)
{
    soundVersion(app, cpu);
}

void iSNDdirectsetfunctions(win32::WinApplication* app, x86::CPU& cpu)
{
    soundSetFunctions(app, cpu);
}

void iSNDdirectrecordstart(win32::WinApplication* app, x86::CPU& cpu)
{
    soundRecordStart(app, cpu);
}

void iSNDdirectrecordpacket(win32::WinApplication* app, x86::CPU& cpu)
{
    soundRecordPacket(app, cpu);
}

void iSNDdirectrecordstop(win32::WinApplication* app, x86::CPU& cpu)
{
    soundRecordStop(app, cpu);
}

void iSNDdirectvol(win32::WinApplication* app, x86::CPU& cpu)
{
    if (!soundVolume(app, cpu))
        notNative(cpu, 8);
}

void iSNDdirectpos3d(win32::WinApplication* app, x86::CPU& cpu)
{
    if (!soundPosition(app, cpu))
        notNative(cpu, 0xc);
}

void iSNDdirectrate(win32::WinApplication* app, x86::CPU& cpu)
{
    if (!soundRate(app, cpu))
        notNative(cpu, 8);
}

void iSNDdirectcreate3dbuf(win32::WinApplication* app, x86::CPU& cpu)
{
    if (!soundCreateBuffer(app, cpu))
        notNative(cpu, 0x1c);
}

void iSNDdirectremovebuf(win32::WinApplication* app, x86::CPU& cpu)
{
    if (!soundRemoveBuffer(app, cpu))
        notNative(cpu, 4);
}

void iSNDdirectplay3d(win32::WinApplication* app, x86::CPU& cpu)
{
    if (!soundPlayBuffer(app, cpu))
        notNative(cpu, 0x1c);
}

void iSNDdirectstopbuf(win32::WinApplication* app, x86::CPU& cpu)
{
    if (!soundStopBuffer(app, cpu))
        notNative(cpu, 4);
}

}
