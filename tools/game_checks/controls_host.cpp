#include "native_controls_host.h"

/* game_checks' answer to what the natives ask of DirectInput: the game's code
 * made each call through the object's table of methods, and DirectInputCreateA
 * through its thunk, so the checks make them so -- each native against its
 * generated code, whatever the call does.  The port's own answer, with no
 * DirectInput behind it, is src/nfs3hp/native_controls_host.cpp. */
namespace nfs3hp
{
namespace controls
{

namespace
{
constexpr x86::reg32 kDirectInputCreate = 0x533ee0;
}

bool directInput(win32::WinApplication* app, x86::CPU& cpu, Object, x86::reg32 method)
{
    x86::reg32 target = kDirectInputCreate;
    if (method != kCreate)
    {
        const x86::reg32 object = app->getMemory<x86::reg32>(cpu.esp);
        target = app->getMemory<x86::reg32>(app->getMemory<x86::reg32>(object) + method);
    }
    cpu.esp -= 4;
    app->dynamic_call(target, cpu);
    return !cpu.terminate;
}

}  // namespace controls
}  // namespace nfs3hp
