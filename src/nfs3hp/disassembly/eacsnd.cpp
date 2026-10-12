#include "eacsnd.h"
#include <x86.h>
#include <winapi/wrapper.h>

namespace nfs3hp
{
void iSNDdirectcaps(win32::WinApplication* app, x86::CPU& cpu);
void iSNDdirectcreate3dbuf(win32::WinApplication* app, x86::CPU& cpu);
void iSNDdirectplay3d(win32::WinApplication* app, x86::CPU& cpu);
void iSNDdirectpos3d(win32::WinApplication* app, x86::CPU& cpu);
void iSNDdirectrate(win32::WinApplication* app, x86::CPU& cpu);
void iSNDdirectrecordpacket(win32::WinApplication* app, x86::CPU& cpu);
void iSNDdirectrecordstart(win32::WinApplication* app, x86::CPU& cpu);
void iSNDdirectrecordstop(win32::WinApplication* app, x86::CPU& cpu);
void iSNDdirectremovebuf(win32::WinApplication* app, x86::CPU& cpu);
void iSNDdirectserve(win32::WinApplication* app, x86::CPU& cpu);
void iSNDdirectsetfunctions(win32::WinApplication* app, x86::CPU& cpu);
void iSNDdirectstart(win32::WinApplication* app, x86::CPU& cpu);
void iSNDdirectstop(win32::WinApplication* app, x86::CPU& cpu);
void iSNDdirectstopbuf(win32::WinApplication* app, x86::CPU& cpu);
void iSNDdirectvol(win32::WinApplication* app, x86::CPU& cpu);
void iSNDdllversion(win32::WinApplication* app, x86::CPU& cpu);
}

namespace eacsnd
{

win32::Library s_library = win32::Library("eacsnd.dll");
win32::Library* s_registry = &(s_library
        .registerSymbol("_iSNDdirectcaps@4", &nfs3hp::iSNDdirectcaps)
        .registerSymbol("_iSNDdirectcreate3dbuf@28", &nfs3hp::iSNDdirectcreate3dbuf)
        .registerSymbol("_iSNDdirectplay3d@28", &nfs3hp::iSNDdirectplay3d)
        .registerSymbol("_iSNDdirectpos3d@12", &nfs3hp::iSNDdirectpos3d)
        .registerSymbol("_iSNDdirectrate@8", &nfs3hp::iSNDdirectrate)
        .registerSymbol("_iSNDdirectrecordpacket@4", &nfs3hp::iSNDdirectrecordpacket)
        .registerSymbol("_iSNDdirectrecordstart@16", &nfs3hp::iSNDdirectrecordstart)
        .registerSymbol("_iSNDdirectrecordstop@0", &nfs3hp::iSNDdirectrecordstop)
        .registerSymbol("_iSNDdirectremovebuf@4", &nfs3hp::iSNDdirectremovebuf)
        .registerSymbol("_iSNDdirectserve@0", &nfs3hp::iSNDdirectserve)
        .registerSymbol("_iSNDdirectsetfunctions@32", &nfs3hp::iSNDdirectsetfunctions)
        .registerSymbol("_iSNDdirectstart@8", &nfs3hp::iSNDdirectstart)
        .registerSymbol("_iSNDdirectstop@0", &nfs3hp::iSNDdirectstop)
        .registerSymbol("_iSNDdirectstopbuf@4", &nfs3hp::iSNDdirectstopbuf)
        .registerSymbol("_iSNDdirectvol@8", &nfs3hp::iSNDdirectvol)
        .registerSymbol("_iSNDdllversion@0", &nfs3hp::iSNDdllversion)

    );
}
