#include <winapi/dinput.h>
#include <x86.h>

namespace win32 { namespace dinput
{

HRESULT DirectInputCreateA(WinApplication* app, x86::CPU& cpu,
                           HINSTANCE hinst, DWORD dwVersion, LPVOID lplpDirectInput,
                           LPVOID punkOuter)
{
    NFS2_USE(app);
    NFS2_USE(cpu);
    NFS2_USE(hinst);
    NFS2_USE(dwVersion);
    NFS2_USE(lplpDirectInput);
    NFS2_USE(punkOuter);
    return 0x80004001;  // E_NOTIMPL
}

}}
