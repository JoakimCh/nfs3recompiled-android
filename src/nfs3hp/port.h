#ifndef NFS3HP_PORT_H
#define NFS3HP_PORT_H

#include "native_guest.h"

#include <cstdint>
#include <cstring>
#include <initializer_list>

/* The port proper: the game's code rewritten as C++ of its own -- functions
 * with arguments and results, the game's records as structs, its variables
 * by name -- rather than the x86's registers and flat memory.
 *
 * While code that is still the game's (generated or register-level natives)
 * shares the game's memory, a rewritten function keeps its data where the
 * game has it: Var and Table name a variable or a table by its address and
 * read or write it whole (the memory may be unaligned, so through memcpy).
 * It calls what is not rewritten yet through callGame, as Watcom's
 * convention has it.  Called by the game's code, it is entered through an
 * adapter that takes its arguments from the registers and the stack and gives
 * back what Watcom's convention promises the caller: the result in eax, every
 * other register as it was (tools/game_checks holds port:: functions to
 * that, besides memory and the calls they make; the callers' reading of the
 * registers was checked for the sound module: none reads more). */
namespace nfs3hp
{
namespace port
{

using App = win32::WinApplication;
using CPU = x86::CPU;
using reg32 = x86::reg32;
using std::int16_t;
using std::int32_t;
using std::int8_t;
using std::uint16_t;
using std::uint32_t;
using std::uint8_t;

/* A variable of the game's, by its address. */
template <class T>
struct Var
{
    reg32 at;
    T operator()(App* app) const { return app->getMemory<T>(at); }
    void set(App* app, T value) const { app->getMemory<T>(at) = value; }
};

/* A table of the game's records (or values), by its address; `stride` when
 * its entries lie further apart than the record is long. */
template <class T>
struct Table
{
    reg32 at;
    reg32 stride = sizeof(T);
    reg32 address(int32_t i) const { return at + reg32(i) * stride; }
    T operator()(App* app, int32_t i) const
    {
        T value;
        std::memcpy(&value, &app->getMemory<uint8_t>(address(i)), sizeof(T));
        return value;
    }
    void set(App* app, int32_t i, const T& value) const
    {
        std::memcpy(&app->getMemory<uint8_t>(address(i)), &value, sizeof(T));
    }
};

/* A record of the game's at an address (on the game's stack, say), read and
 * written whole. */
template <class T>
T load(App* app, reg32 at)
{
    T value;
    std::memcpy(&value, &app->getMemory<uint8_t>(at), sizeof(T));
    return value;
}

template <class T>
void store(App* app, reg32 at, const T& value)
{
    std::memcpy(&app->getMemory<uint8_t>(at), &value, sizeof(T));
}

/* Watcom's register arguments of a call. */
struct Args
{
    reg32 eax = 0, edx = 0, ebx = 0, ecx = 0;
};

/* A call into the game's code (what is not rewritten yet) as Watcom makes
 * it: the register arguments, `stack` pushed, from the game's stack at esp.
 * Its eax; false when the game stops. */
inline bool callGame(App* app, CPU& cpu, reg32 esp, reg32 target, Args a, std::initializer_list<reg32> stack,
                     reg32& result)
{
    cpu.esp = esp;
    cpu.eax = a.eax;
    cpu.edx = a.edx;
    cpu.ebx = a.ebx;
    cpu.ecx = a.ecx;
    if (!guest::call(app, cpu, target, stack))
        return false;
    result = cpu.eax;
    return true;
}

inline bool callGame(App* app, CPU& cpu, reg32 esp, reg32 target, Args a = {}, std::initializer_list<reg32> stack = {})
{
    reg32 ignored;
    return callGame(app, cpu, esp, target, a, stack, ignored);
}

/* The adapter's two ends: the caller's registers and stack on the way in,
 * and on the way out its result in eax, every other register as it was, esp
 * past the return address and `popped` (a stdcall's words). */
struct Entry
{
    reg32 eax, ebx, ecx, edx, esi, edi, ebp, esp;
    explicit Entry(const CPU& c)
        : eax(c.eax), ebx(c.ebx), ecx(c.ecx), edx(c.edx), esi(c.esi), edi(c.edi), ebp(c.ebp), esp(c.esp)
    {
    }
    /* The i-th stack argument (0 the first). */
    reg32 arg(App* app, int i) const { return app->getMemory<reg32>(esp + 4 + 4 * reg32(i)); }
    /* esp as the game's code has it after `pushes` registers and `locals`
     * bytes: where its records on the stack are. */
    reg32 frame(reg32 pushes, reg32 locals = 0) const { return esp - 4 * pushes - locals; }
    void back(CPU& c, reg32 result, reg32 popped = 0) const
    {
        c.eax = result;
        c.ebx = ebx;
        c.ecx = ecx;
        c.edx = edx;
        c.esi = esi;
        c.edi = edi;
        c.ebp = ebp;
        c.esp = esp + 4 + popped;
    }
};

}  // namespace port
}  // namespace nfs3hp

#endif
