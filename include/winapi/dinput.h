#ifndef dinput_H_
#define dinput_H_

#include <x86.h>
#include <lib/winapp.h>
#include <winapi/types.h>

namespace win32 { namespace dinput
{

/* The game's import of DINPUT.dll.  Nothing calls it: what the game asked of
 * DirectInput its natives ask of the port (nfs3hp/native_controls_host.h),
 * and there is no DirectInput behind that.  It answers E_NOTIMPL. */
HRESULT DirectInputCreateA(WinApplication* app, x86::CPU& cpu,
                           HINSTANCE hinst, DWORD dwVersion, LPVOID lplpDirectInput,
                           LPVOID punkOuter);

}}

#endif
