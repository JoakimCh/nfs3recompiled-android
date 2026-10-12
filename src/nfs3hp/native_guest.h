#ifndef NFS3HP_NATIVE_GUEST_H
#define NFS3HP_NATIVE_GUEST_H

#include <lib/winapp.h>
#include <initializer_list>
#include <type_traits>

/* What the game's own functions that are native (native_game.cpp,
 * native_watcom.cpp) need of the guest: its memory, and its code called as
 * the game's code calls it. */
namespace nfs3hp
{
namespace guest
{

inline x86::reg32 at(win32::WinApplication* app, x86::reg32 address)
{
    return app->getMemory<x86::reg32>(address);
}

inline void put(win32::WinApplication* app, x86::reg32 address, x86::reg32 value)
{
    app->getMemory<x86::reg32>(address) = value;
}

inline x86::reg8 byte(win32::WinApplication* app, x86::reg32 address)
{
    return app->getMemory<x86::reg8>(address);
}

inline void putByte(win32::WinApplication* app, x86::reg32 address, x86::reg8 value)
{
    app->getMemory<x86::reg8>(address) = value;
}

typedef void (*Native)(win32::WinApplication*, x86::CPU&);

/* A call as the game's code makes one: `arguments` pushed below esp, the
 * return address's slot below them, and esp back where it was after it --
 * where a stdcall callee's ret leaves it, and a cdecl one's caller puts it.
 * False when the game stopped in it, with everything left as it is. */
template <typename Target>
bool through(win32::WinApplication* app, x86::CPU& cpu, Target target, std::initializer_list<x86::reg32> arguments)
{
    const x86::reg32 esp = cpu.esp;
    x86::reg32 slot = esp - 4 * x86::reg32(arguments.size());
    cpu.esp = slot - 4;
    for (const x86::reg32 argument : arguments)
    {
        put(app, slot, argument);
        slot += 4;
    }
    if constexpr (std::is_same_v<Target, Native>)
        target(app, cpu);
    else
        app->dynamic_call(target, cpu);
    if (cpu.terminate)
        return false;
    cpu.esp = esp;
    return true;
}

inline bool call(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 target,
                 std::initializer_list<x86::reg32> arguments = {})
{
    return through(app, cpu, target, arguments);
}

inline bool call(win32::WinApplication* app, x86::CPU& cpu, Native target,
                 std::initializer_list<x86::reg32> arguments = {})
{
    return through(app, cpu, target, arguments);
}

}  // namespace guest
}  // namespace nfs3hp

#endif
