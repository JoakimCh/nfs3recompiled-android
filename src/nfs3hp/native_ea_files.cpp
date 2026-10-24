#include "native_guest.h"

/* EA's files (win\fileio.c, win\file.c, win\blockio.c): the handles the game
 * opens its files by -- whole, mapped into memory, or a buffer of its own
 * taken as one -- read, written and sought a block at a time under the lock
 * of the drive each is on, their errors reported; the drives, paths and
 * directories they are on; and the memory pages EA's library takes from
 * Windows (win\touchmem.c).  disassemble_nfs3hp.py binds each address to the
 * function of that name here (EA_FILES_NATIVES), and the generated code calls
 * it by name.  tools/game_checks holds each against its generated code.
 *
 * The handles are a table (its address at 0x5645a0, [0x56459c] of them, 0x40
 * unless the game asks for more) of 0x20 bytes each: +0 in use, +1 its
 * drive (1 for A:, the lock of 0x9ef760 by it), +2 a read under way, +4 the
 * Windows file, +8 how it was opened (1 read, 2 write, 4 and 8 the others'
 * sharing, 0x10 and 0x20 how it is created, 0x100 to 0x400 Windows' flags for
 * it, 0x800 mapped), +0xc the block it is read and written by, +0x10 its
 * mapping, +0x14 where it is mapped (or the buffer taken as a file), +0x18
 * where it is, +0x1c how long.  A handle given out is the slot's index, its
 * bits flipped.  The table is taken under its own lock (0x564598); a handle
 * is read, written and sought under its drive's.  A file not found may be in
 * the game's archive ([0x564504], its directory read into [0x564584], looked
 * up by [0x564588]): the archive opened instead, at the file's place in it.
 *
 * Its errors go to fileReport (0x501050), which prints a report as its
 * level and the game's way of reporting ([0x56789c]) say; a file not opened
 * while [0x56440c] is set ends the game (Error).
 *
 * Written as their code is: each push and pop to the guest's stack, each call
 * with the return address's slot, the frame's locals in the guest's memory,
 * the registers as the code leaves them, a string's length as repne scasb
 * leaves it.  Windows' functions are called through their imports' slots;
 * Error, the runtime's, and every other function of the game's by address --
 * openHandle (0x4e28d0) and virtualAllocPages (0x501110) too, which other
 * natives' checks stand in for. */
namespace nfs3hp
{
namespace ea
{

namespace
{

using guest::at;
using guest::byte;
using guest::put;
using guest::putByte;
using x86::reg32;
using x86::reg8;
using x86::sreg32;

// Where an Error is from: the file, the function, the line.
constexpr reg32 kWhereFile = 0x552190, kWhereFunction = 0x552194, kWhereLine = 0x552198;
// A file not opened ends the game, when set.
constexpr reg32 kErrorsFatal = 0x56440c;
// Whether the functions called on the main thread are checked for a surface
// locked.
constexpr reg32 kSurfaceCheck = 0x564364;
// The archive: its name, its directory read in, how much of it, the function
// that looks a file up in it, the file's length it found.
constexpr reg32 kArchiveName = 0x564504, kArchiveDirectory = 0x564584, kArchiveLookup = 0x564588;
constexpr reg32 kArchiveFoundLength = 0x56458c, kArchiveDirectoryBytes = 0x564590;
// The reports' level, the table's lock, the handles, the drives' locks.
constexpr reg32 kReportLevel = 0x564594, kHandlesLock = 0x564598, kHandleCount = 0x56459c, kHandles = 0x5645a0;
constexpr reg32 kDriveLocks = 0x9ef760, kDriveLocksBytes = 0x80;
// The reports' way out: none, OutputDebugString, stdout, the game's log.
constexpr reg32 kReportOutput = 0x56789c, kStdout = 0x566f72;
// Windows' page, and how much memory there is to touch.
constexpr reg32 kPageSize = 0x5678a0, kPhysicalMemory = 0x5678a4;
// The handles' fields.
constexpr reg32 kSlotShift = 5, kSlotBytes = 0x20, kDefaultHandles = 0x40, kDefaultBlock = 0x4000;
constexpr reg32 kNoDiskSector = 0x800, kMapped = 0x800, kOpenFlags = 0x205;
// The game's strings: win\fileio.c's, win\file.c's, win\touchmem.c's, win\blockio.c's.
constexpr reg32 kFileioC = 0x54a148, kOpenHandleName = 0x54a158, kOpenFailed = 0x54a164, kInfoFailed = 0x54a188;
constexpr reg32 kOpenHandleWName = 0x54a1ac, kOpenMapHandleName = 0x54a1b8, kOpenHandleAName = 0x54a1c8;
constexpr reg32 kMapInfoFailed = 0x54a1d4, kMapOpenFailed = 0x54a1fc;
constexpr reg32 kLibCloseHandleName = 0x54a228, kCloseHandleName = 0x54a238, kReadHandleName = 0x54a244;
constexpr reg32 kWriteHandleName = 0x54a250, kSeekHandleName = 0x54a25c, kVolumeFailed = 0x54a268;
constexpr reg32 kNoPath = 0x54a294, kFileC = 0x54a298, kSetDirectoryName = 0x54a2a4, kSetDirectoryFailed = 0x54a2b4;
constexpr reg32 kGetDirectoryName = 0x54a2d4, kGetDirectoryFailed = 0x54a2e4, kCreateFileFailed = 0x54a320;
constexpr reg32 kDriveRoot = 0x54a340, kDiskFreeFailed = 0x54a344, kReadFileFailed = 0x54a36c;
constexpr reg32 kWriteFileFailed = 0x54a38c, kSetFilePointerFailed = 0x54a3ac;
constexpr reg32 kSurfaceLocked = 0x54e42c, kTouchmemC = 0x54e454, kTouchMemPagesName = 0x54e464;
constexpr reg32 kTouchMemFirst = 0x54e474, kBlockioC = 0x54e49c, kOpenBlockHandleName = 0x54e4ac;
constexpr reg32 kBlockOpenFailed = 0x54e4bc, kBlockInfoFailed = 0x54e4e4, kBlockHandleFileName = 0x54e50c;
constexpr reg32 kBlockFileUnsupported = 0x54e51c, kReadBlockHandleName = 0x54e548, kBlockReadFailed = 0x54e558;
constexpr reg32 kSeekBlockHandleName = 0x54e578, kBlockSeekFailed = 0x54e588;
// Windows' functions, by their imports' slots.
constexpr reg32 kCloseHandle = 0x534488, kCreateFileA = 0x534498, kCreateFileMappingA = 0x53449c;
constexpr reg32 kDeleteFileA = 0x5344b0, kEnterCriticalSection = 0x5344b8, kFindClose = 0x5344c8;
constexpr reg32 kFindFirstFileA = 0x5344cc, kGetCurrentDirectoryA = 0x534500, kGetDiskFreeSpaceA = 0x534514;
constexpr reg32 kGetFileSize = 0x534524, kGetFullPathNameA = 0x534530, kGetLastError = 0x534534;
constexpr reg32 kGetLogicalDriveStringsA = 0x53453c, kGetLogicalDrives = 0x534540, kGetSystemInfo = 0x534560;
constexpr reg32 kGetVolumeInformationA = 0x534578, kLeaveCriticalSection = 0x534588, kMapViewOfFile = 0x534590;
constexpr reg32 kOutputDebugStringA = 0x53459c, kReadFile = 0x5345b0, kSetCurrentDirectoryA = 0x5345d4;
constexpr reg32 kSetFilePointer = 0x5345f0, kSetLastError = 0x5345f4, kUnmapViewOfFile = 0x534620;
constexpr reg32 kVirtualAlloc = 0x534624, kVirtualFree = 0x534628, kWriteFile = 0x534640, kCharUpperA = 0x5346f8;
constexpr reg32 kIoPending = 0x3e5;
// The game's functions, by address.
constexpr reg32 kError = 0x401010, kVsprintf = 0x4df674, kMessage = 0x4df6c0, kSleep = 0x4df8e0;
constexpr reg32 kOnMainThread = 0x4df930, kFillZero = 0x4e070c, kTrace = 0x4e08f0, kStricmp = 0x4e9ec0;
constexpr reg32 kMoveMemory = 0x4ea4f0, kNewLock = 0x4eb2e0, kFreeLock = 0x4eb360, kFflush = 0x4f7d70;
constexpr reg32 kSurfaceLockedNow = 0x4f9070, kPhysicalMemorySize = 0x5221f0;
constexpr reg32 kOpenHandle = 0x4e28d0, kVirtualAllocPages = 0x501110;

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

/* sub ecx, ecx; dec ecx; xor eax, eax; repne scasb; not ecx; dec ecx: the
 * length of the string at edi in ecx, edi past its end, eax 0. */
void stringLength(win32::WinApplication* app, x86::CPU& cpu)
{
    cpu.ecx = 0xffffffff;
    cpu.eax = 0;
    while (cpu.ecx != 0)
    {
        --cpu.ecx;
        const reg8 c = byte(app, cpu.edi);
        ++cpu.edi;
        if (c == cpu.al)
            break;
    }
    cpu.ecx = ~cpu.ecx;
    --cpu.ecx;
}

/* push edi; then two bytes a turn from esi to edi to the string's end; pop
 * edi: esi and al as the copy leaves them. */
void copyString(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.edi);
    for (;;)
    {
        cpu.al = byte(app, cpu.esi);
        putByte(app, cpu.edi, cpu.al);
        if (cpu.al == 0)
            break;
        cpu.al = byte(app, cpu.esi + 1);
        cpu.esi += 2;
        putByte(app, cpu.edi + 1, cpu.al);
        cpu.edi += 2;
        if (cpu.al == 0)
            break;
    }
    cpu.edi = pop(app, cpu);
}

/* cdq; idiv `divisor`: eax the quotient, edx the remainder -- worked in 64
 * bits, as the generated code does. */
void idivide(x86::CPU& cpu, reg32 divisor)
{
    const x86::sreg64 dividend = x86::sreg32(cpu.eax);
    const x86::sreg64 by = sreg32(divisor);
    cpu.eax = reg32(x86::reg64(dividend / by));
    cpu.edx = reg32(x86::reg64(dividend % by));
}

/* GetLastError's error reported (fileReport, level 1) with `format`. */
bool reportLastError(win32::WinApplication* app, x86::CPU& cpu, reg32 format);

/* The lock of drive eax (by its index, as the code reads it), entered or
 * left: the lock pushed from `reg`. */
bool driveLock(win32::WinApplication* app, x86::CPU& cpu, reg32& reg, reg32 drive, reg32 slot)
{
    reg = at(app, drive * 4 + kDriveLocks);
    push(app, cpu, reg);
    return windows(app, cpu, slot);
}

}  // namespace

void initHandlesDefault(win32::WinApplication* app, x86::CPU& cpu);
void openHandle(win32::WinApplication* app, x86::CPU& cpu);
void openHandleErrorsAs(win32::WinApplication* app, x86::CPU& cpu);
void openHandleToWrite(win32::WinApplication* app, x86::CPU& cpu);
void openMapHandle(win32::WinApplication* app, x86::CPU& cpu);
void closeHandle(win32::WinApplication* app, x86::CPU& cpu);
void readHandle(win32::WinApplication* app, x86::CPU& cpu);
void writeHandle(win32::WinApplication* app, x86::CPU& cpu);
void seekHandle(win32::WinApplication* app, x86::CPU& cpu);
void isSlash(win32::WinApplication* app, x86::CPU& cpu);
void notSlash(win32::WinApplication* app, x86::CPU& cpu);
void volumeRoot(win32::WinApplication* app, x86::CPU& cpu);
void fullPathName(win32::WinApplication* app, x86::CPU& cpu);
void logicalDrives(win32::WinApplication* app, x86::CPU& cpu);
void driveOfPath(win32::WinApplication* app, x86::CPU& cpu);
void driveLetter(win32::WinApplication* app, x86::CPU& cpu);
void diskFreeBytes(win32::WinApplication* app, x86::CPU& cpu);
void driveNumber(win32::WinApplication* app, x86::CPU& cpu);
void setDirectory(win32::WinApplication* app, x86::CPU& cpu);
void getDirectory(win32::WinApplication* app, x86::CPU& cpu);
void handlesReady(win32::WinApplication* app, x86::CPU& cpu);
void initHandles(win32::WinApplication* app, x86::CPU& cpu);
void closeAllHandles(win32::WinApplication* app, x86::CPU& cpu);
void takeHandleSlot(win32::WinApplication* app, x86::CPU& cpu);
void deleteFile(win32::WinApplication* app, x86::CPU& cpu);
void openFileHandle(win32::WinApplication* app, x86::CPU& cpu);
void handleInfo(win32::WinApplication* app, x86::CPU& cpu);
void readHandleBytes(win32::WinApplication* app, x86::CPU& cpu);
void writeHandleBytes(win32::WinApplication* app, x86::CPU& cpu);
void seekHandleTo(win32::WinApplication* app, x86::CPU& cpu);
void handlePosition(win32::WinApplication* app, x86::CPU& cpu);
void closeHandleSlot(win32::WinApplication* app, x86::CPU& cpu);
void lockHandleDrive(win32::WinApplication* app, x86::CPU& cpu);
void unlockHandleDrive(win32::WinApplication* app, x86::CPU& cpu);
void openMemoryHandle(win32::WinApplication* app, x86::CPU& cpu);
void handleMemory(win32::WinApplication* app, x86::CPU& cpu);
void checkSurfaceUnlocked(win32::WinApplication* app, x86::CPU& cpu);
void fileReport(win32::WinApplication* app, x86::CPU& cpu);
void virtualAllocPages(win32::WinApplication* app, x86::CPU& cpu);
void virtualFreePages(win32::WinApplication* app, x86::CPU& cpu);
void touchMemoryPages(win32::WinApplication* app, x86::CPU& cpu);
void openBlockHandle(win32::WinApplication* app, x86::CPU& cpu);
void blockHandleFile(win32::WinApplication* app, x86::CPU& cpu);
void closeBlockHandle(win32::WinApplication* app, x86::CPU& cpu);
void readBlockHandle(win32::WinApplication* app, x86::CPU& cpu);
void seekBlockHandle(win32::WinApplication* app, x86::CPU& cpu);

namespace
{

bool reportLastError(win32::WinApplication* app, x86::CPU& cpu, reg32 format)
{
    if (!windows(app, cpu, kGetLastError))
        return false;
    cpu.eax &= 0xffff;
    push(app, cpu, cpu.eax);
    push(app, cpu, format);
    push(app, cpu, 1);
    push(app, cpu, kReportLevel);
    return direct(app, cpu, fileReport);
}

/* Where an Error is from, as the code sets it. */
void where(win32::WinApplication* app, reg32 file, reg32 function, reg32 line)
{
    put(app, kWhereFile, file);
    put(app, kWhereFunction, function);
    put(app, kWhereLine, line);
}

}  // namespace

/* 0x4e28c0: the handles' table made anew, of the default 0x40 (initHandles
 * with 0).  No caller in the game. */
void initHandlesDefault(win32::WinApplication* app, x86::CPU& cpu)
{
    cpu.eax = 0;
    initHandles(app, cpu);
}

/* 0x4e28d0, EA's openhandle: the file named eax opened to read (0x205), its
 * handle to [edx], its length to [ecx], where it starts in it to [ebx] (0;
 * either pointer may be 0).  Not found, it is looked for in the archive: the
 * archive opened, its directory read in, the file looked up and sought, its
 * place in the archive to [ebx] and its length (as the lookup found it) to
 * [ecx].  1 if opened, else 0 -- and with [0x56440c] set, an Error. */
void openHandle(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.esp -= 0x14;
    const reg32 f = cpu.esp;
    const auto leave = [&] {
        cpu.eax = at(app, f + 0x10);
        cpu.esp = f + 0x14;
        cpu.ebp = pop(app, cpu);
        cpu.edi = pop(app, cpu);
        cpu.esi = pop(app, cpu);
        cpu.esp += 4;
    };
    put(app, f + 0xc, cpu.eax);
    cpu.esi = cpu.edx;
    cpu.ebp = cpu.ebx;
    cpu.edi = cpu.ecx;
    cpu.edx = kOpenFlags;
    cpu.ebx = kFileioC;
    cpu.eax = kOpenHandleName;
    cpu.ecx = 0;
    put(app, f + 8, cpu.edx);
    put(app, f + 0x10, cpu.ecx);
    put(app, kWhereFile, cpu.ebx);
    cpu.edx = 0x9b;
    put(app, kWhereFunction, cpu.eax);
    put(app, kWhereLine, cpu.edx);
    if (!direct(app, cpu, checkSurfaceUnlocked))
        return;
    if (cpu.ebp == 0)
        cpu.ebp = f + 4;
    if (cpu.edi == 0)
        cpu.edi = f;
    cpu.edx = at(app, f + 8);
    cpu.eax = at(app, f + 0xc);
    cpu.ecx = cpu.esi;
    put(app, cpu.edi, 0);
    cpu.ebx = 0;
    put(app, cpu.ebp, 0);
    if (!direct(app, cpu, openFileHandle))
        return;
    if (cpu.eax != 0)
    {
        cpu.ecx = 1;
        push(app, cpu, 0);
        cpu.eax = at(app, cpu.esi);
        cpu.ebx = 0;
        cpu.edx = 0;
        put(app, f + 0x10, cpu.ecx);
        cpu.ecx = cpu.edi;
        if (!direct(app, cpu, handleInfo))
            return;
        if (cpu.eax != 0)
            return leave();
        if (at(app, kErrorsFatal) != 0)
        {
            cpu.ebp = kFileioC;
            cpu.ecx = at(app, f + 0xc);
            cpu.eax = kOpenHandleName;
            push(app, cpu, cpu.ecx);
            cpu.edx = 0xc1;
            put(app, kWhereFile, cpu.ebp);
            push(app, cpu, kInfoFailed);
            put(app, kWhereFunction, cpu.eax);
            put(app, kWhereLine, cpu.edx);
            if (!byAddress(app, cpu, kError))
                return;
            cpu.esp += 8;
        }
        cpu.eax = at(app, cpu.esi);
        if (!direct(app, cpu, closeHandleSlot))
            return;
        cpu.ebx = 0;
        put(app, cpu.esi, 0);
        put(app, f + 0x10, cpu.ebx);
        put(app, cpu.edi, 0);
        return leave();
    }
    if (at(app, kArchiveLookup) != 0 && byte(app, kArchiveName) != 0)
    {
        cpu.edx = at(app, f + 8);
        cpu.eax = kArchiveName;
        cpu.ecx = cpu.esi;
        cpu.ebx = 0;
        if (!direct(app, cpu, openFileHandle))
            return;
        if (cpu.eax != 0)
        {
            cpu.ebx = at(app, kArchiveDirectoryBytes);
            cpu.edx = at(app, kArchiveDirectory);
            cpu.eax = at(app, cpu.esi);
            if (!direct(app, cpu, readHandleBytes))
                return;
            put(app, kArchiveDirectoryBytes, cpu.eax);
            if (cpu.eax != 0)
            {
                cpu.edx = at(app, f + 0xc);
                cpu.eax = at(app, kArchiveDirectory);
                if (!byAddress(app, cpu, at(app, kArchiveLookup)))
                    return;
                put(app, cpu.ebp, cpu.eax);
                if (cpu.eax != 0)
                {
                    cpu.edx = cpu.eax;
                    cpu.eax = at(app, cpu.esi);
                    if (!direct(app, cpu, seekHandleTo))
                        return;
                    if (cpu.eax != 0)
                    {
                        cpu.eax = at(app, kArchiveFoundLength);
                        cpu.ecx = 1;
                        cpu.eax = at(app, cpu.eax);
                        put(app, f + 0x10, cpu.ecx);
                        put(app, cpu.edi, cpu.eax);
                        return leave();
                    }
                }
            }
            cpu.ecx = at(app, f + 0x10);
            if (cpu.ecx == 0)
            {
                cpu.eax = at(app, cpu.esi);
                if (!direct(app, cpu, closeHandleSlot))
                    return;
                put(app, cpu.esi, cpu.ecx);
            }
        }
    }
    if (at(app, f + 0x10) == 0 && at(app, kErrorsFatal) != 0)
    {
        cpu.edi = kFileioC;
        cpu.edx = at(app, f + 0xc);
        cpu.ebp = kOpenHandleName;
        push(app, cpu, cpu.edx);
        cpu.eax = 0xba;
        put(app, kWhereFile, cpu.edi);
        push(app, cpu, kOpenFailed);
        put(app, kWhereFunction, cpu.ebp);
        put(app, kWhereLine, cpu.eax);
        if (!byAddress(app, cpu, kError))
            return;
        cpu.esp += 8;
    }
    leave();
}

/* 0x4e2ab0: openHandle with [0x56440c] -- an Error if it fails -- as the
 * stack's word says for the call; the word taken off. */
void openHandleErrorsAs(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    cpu.edi = at(app, cpu.esp + 0xc);
    cpu.esi = at(app, kErrorsFatal);
    put(app, kErrorsFatal, cpu.edi);
    if (!byAddress(app, cpu, kOpenHandle))
        return;
    put(app, kErrorsFatal, cpu.esi);
    cpu.edi = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.esp += 4 + 4;
}

/* 0x4e2ae0, EA's openhandlew: the file named eax opened to write -- made
 * anew (0x232) -- its handle to [edx], its length to [ecx] and 0 to [ebx]
 * (either pointer may be 0).  1 if opened, else 0; a file opened that tells
 * nothing of itself closed again. */
void openHandleToWrite(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.esp -= 0xc;
    const reg32 f = cpu.esp;
    const auto leave = [&] {
        cpu.eax = at(app, f + 8);
        put(app, cpu.eax, 0);
        cpu.eax = cpu.ebp;
        cpu.esp = f + 0xc;
        cpu.ebp = pop(app, cpu);
        cpu.edi = pop(app, cpu);
        cpu.esi = pop(app, cpu);
        cpu.esp += 4;
    };
    cpu.ebp = cpu.eax;
    cpu.edi = cpu.edx;
    put(app, f + 8, cpu.ebx);
    cpu.esi = cpu.ecx;
    if (cpu.ebx == 0)
    {
        cpu.eax = f + 4;
        put(app, f + 8, cpu.eax);
    }
    if (cpu.esi == 0)
        cpu.esi = f;
    cpu.ecx = kFileioC;
    cpu.ebx = kOpenHandleWName;
    cpu.eax = 0xdf;
    cpu.edx = 0x232;
    put(app, kWhereFile, cpu.ecx);
    put(app, kWhereLine, cpu.eax);
    cpu.eax = cpu.ebx;
    put(app, kWhereFunction, cpu.ebx);
    if (!direct(app, cpu, checkSurfaceUnlocked))
        return;
    cpu.ecx = cpu.edi;
    cpu.eax = cpu.ebp;
    cpu.ebx = 0;
    if (!direct(app, cpu, openFileHandle))
        return;
    if (cpu.eax == 0)
    {
        put(app, cpu.edi, cpu.eax);
        cpu.ebp = 0;
        put(app, cpu.esi, cpu.eax);
        return leave();
    }
    push(app, cpu, 0);
    cpu.ecx = cpu.esi;
    cpu.eax = at(app, cpu.edi);
    cpu.ebx = 0;
    cpu.edx = 0;
    cpu.ebp = 1;
    if (!direct(app, cpu, handleInfo))
        return;
    if (cpu.eax != 0)
        return leave();
    cpu.eax = at(app, cpu.edi);
    if (!direct(app, cpu, closeHandleSlot))
        return;
    put(app, cpu.edi, 0);
    cpu.ebp = 0;
    put(app, cpu.esi, 0);
    leave();
}

/* 0x4e2ba0, EA's openmaphandle: the file named eax opened mapped into memory
 * (0x805), its handle to [edx], its length to [ecx], 0 to [ebx]; where it is
 * mapped back, or 0.  Not found, it is looked for in the archive as
 * openHandle does: the archive's memory and the file's place in it.  No
 * caller in the game. */
void openMapHandle(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.esp -= 0x14;
    const reg32 f = cpu.esp;
    const auto leave = [&] {
        cpu.eax = at(app, f + 0xc);
        cpu.esp = f + 0x14;
        cpu.ebp = pop(app, cpu);
        cpu.edi = pop(app, cpu);
        cpu.esi = pop(app, cpu);
        cpu.esp += 4;
    };
    // An Error with the name: the format, the line.
    const auto error = [&](reg32 file, reg32 function, reg32 format, reg32 line) {
        push(app, cpu, cpu.ebp);
        push(app, cpu, format);
        where(app, file, function, line);
        if (!byAddress(app, cpu, kError))
            return false;
        cpu.esp += 8;
        return true;
    };
    cpu.ebp = cpu.eax;
    cpu.esi = cpu.edx;
    put(app, f + 0x10, cpu.ebx);
    cpu.edi = cpu.ecx;
    cpu.edx = 0x805;
    cpu.ebx = kFileioC;
    cpu.eax = kOpenMapHandleName;
    cpu.ecx = 0;
    put(app, f + 8, cpu.edx);
    put(app, f + 0xc, cpu.ecx);
    put(app, kWhereFile, cpu.ebx);
    put(app, kWhereFunction, cpu.eax);
    cpu.edx = 0x141;
    cpu.eax = kOpenHandleAName;
    cpu.ecx = at(app, f + 0x10);
    put(app, kWhereLine, cpu.edx);
    if (!direct(app, cpu, checkSurfaceUnlocked))
        return;
    if (cpu.ecx == 0)
    {
        cpu.eax = f + 4;
        put(app, f + 0x10, cpu.eax);
    }
    if (cpu.edi == 0)
        cpu.edi = f;
    cpu.eax = at(app, f + 0x10);
    cpu.edx = at(app, f + 8);
    cpu.ecx = cpu.esi;
    put(app, cpu.edi, 0);
    cpu.ebx = 0;
    put(app, cpu.eax, 0);
    cpu.eax = cpu.ebp;
    if (!direct(app, cpu, openFileHandle))
        return;
    if (cpu.eax != 0)
    {
        push(app, cpu, 0);
        cpu.ecx = cpu.edi;
        cpu.eax = at(app, cpu.esi);
        cpu.ebx = 0;
        cpu.edx = 0;
        if (!direct(app, cpu, handleInfo))
            return;
        if (cpu.eax != 0)
        {
            cpu.eax = at(app, cpu.esi);
            if (!direct(app, cpu, handleMemory))
                return;
            put(app, f + 0xc, cpu.eax);
            return leave();
        }
        if (at(app, kErrorsFatal) != 0)
        {
            cpu.ecx = kFileioC;
            push(app, cpu, cpu.ebp);
            cpu.ebx = kOpenMapHandleName;
            cpu.eax = 0x150;
            push(app, cpu, kMapInfoFailed);
            put(app, kWhereFile, cpu.ecx);
            put(app, kWhereFunction, cpu.ebx);
            put(app, kWhereLine, cpu.eax);
            if (!byAddress(app, cpu, kError))
                return;
            cpu.esp += 8;
        }
        cpu.eax = at(app, cpu.esi);
        if (!direct(app, cpu, closeHandleSlot))
            return;
        put(app, cpu.esi, 0);
        put(app, cpu.edi, 0);
        return leave();
    }
    if (at(app, kArchiveLookup) != 0 && byte(app, kArchiveName) != 0)
    {
        cpu.edx = at(app, f + 8);
        cpu.eax = kArchiveName;
        cpu.ecx = cpu.esi;
        cpu.ebx = 0;
        if (!direct(app, cpu, openFileHandle))
            return;
        if (cpu.eax != 0)
        {
            cpu.eax = at(app, cpu.esi);
            if (!direct(app, cpu, handleMemory))
                return;
            cpu.edx = cpu.ebp;
            cpu.esi = cpu.eax;
            if (!byAddress(app, cpu, at(app, kArchiveLookup)))
                return;
            cpu.edx = at(app, f + 0x10);
            put(app, cpu.edx, cpu.eax);
            cpu.eax += cpu.esi;
            put(app, f + 0xc, cpu.eax);
            cpu.eax = at(app, kArchiveFoundLength);
            cpu.eax = at(app, cpu.eax);
            put(app, cpu.edi, cpu.eax);
            if (at(app, cpu.edx) != 0 || at(app, kErrorsFatal) == 0)
                return leave();
            cpu.esi = kFileioC;
            cpu.edi = kOpenMapHandleName;
            cpu.eax = 0x15f;
            if (!error(cpu.esi, cpu.edi, kMapOpenFailed, cpu.eax))
                return;
            return leave();
        }
    }
    if (at(app, kErrorsFatal) != 0)
    {
        cpu.edi = kFileioC;
        cpu.eax = kOpenMapHandleName;
        cpu.edx = 0x162;
        if (!error(cpu.edi, cpu.eax, kMapOpenFailed, cpu.edx))
            return;
    }
    leave();
}

/* 0x4e2da0, EA's closehandle: handle eax closed (closeHandleSlot); 1 if it
 * was open. */
void closeHandle(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.esi);
    cpu.edx = cpu.eax;
    cpu.ecx = kFileioC;
    cpu.ebx = kLibCloseHandleName;
    cpu.esi = 0x19d;
    cpu.eax = kCloseHandleName;
    put(app, kWhereFile, cpu.ecx);
    put(app, kWhereFunction, cpu.ebx);
    put(app, kWhereLine, cpu.esi);
    if (!direct(app, cpu, checkSurfaceUnlocked))
        return;
    cpu.eax = cpu.edx;
    if (!direct(app, cpu, closeHandleSlot))
        return;
    cpu.esi = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4;
}

namespace
{

/* readHandle and writeHandle: `name` checked for a surface locked, then
 * handle eax's bytes read or written. */
void transferHandle(win32::WinApplication* app, x86::CPU& cpu, reg32 name, reg32 line,
                    void (*transfer)(win32::WinApplication*, x86::CPU&))
{
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.ecx = cpu.eax;
    cpu.esi = kFileioC;
    cpu.edi = name;
    cpu.ebp = line;
    put(app, kWhereFile, cpu.esi);
    put(app, kWhereFunction, cpu.edi);
    cpu.eax = cpu.edi;
    put(app, kWhereLine, cpu.ebp);
    if (!direct(app, cpu, checkSurfaceUnlocked))
        return;
    cpu.eax = cpu.ecx;
    if (!direct(app, cpu, transfer))
        return;
    cpu.ebp = pop(app, cpu);
    cpu.edi = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.esp += 4;
}

}  // namespace

/* 0x4e2de0, EA's readhandle: ebx bytes of handle eax read to edx
 * (readHandleBytes); how many back. */
void readHandle(win32::WinApplication* app, x86::CPU& cpu)
{
    transferHandle(app, cpu, kReadHandleName, 0x1d4, readHandleBytes);
}

/* 0x4e2e20, EA's writehandle: ebx bytes at edx written to handle eax
 * (writeHandleBytes); how many back. */
void writeHandle(win32::WinApplication* app, x86::CPU& cpu)
{
    transferHandle(app, cpu, kWriteHandleName, 0x1dd, writeHandleBytes);
}

/* 0x4e2e60, EA's seekhandle: handle eax sought to edx; where it is then, or
 * 0 if it is not open. */
void seekHandle(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    cpu.ecx = cpu.eax;
    cpu.ebx = kFileioC;
    cpu.esi = kSeekHandleName;
    cpu.edi = 0x219;
    put(app, kWhereFile, cpu.ebx);
    put(app, kWhereFunction, cpu.esi);
    cpu.eax = cpu.esi;
    put(app, kWhereLine, cpu.edi);
    if (!direct(app, cpu, checkSurfaceUnlocked))
        return;
    cpu.eax = cpu.ecx;
    if (!direct(app, cpu, seekHandleTo))
        return;
    if (cpu.eax != 0)
    {
        cpu.eax = cpu.ecx;
        if (!direct(app, cpu, handlePosition))
            return;
    }
    cpu.edi = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x4e2eb0: 1 if al is a slash, \ or /, else 0. */
void isSlash(win32::WinApplication* app, x86::CPU& cpu)
{
    if (cpu.al != '\\' && cpu.al != '/')
        return notSlash(app, cpu);
    cpu.eax = 1;
    cpu.esp += 4;
}

/* 0x4e2ebe: isSlash's way out with 0 -- an entry of its own, as handlesReady
 * jumps to it: eax 0. */
void notSlash(win32::WinApplication*, x86::CPU& cpu)
{
    cpu.eax = 0;
    cpu.esp += 4;
}

/* 0x4e2ed0: the root of path eax to edx: the path copied (at most 0x104
 * bytes) and cut after the share of a \\server\share, or else after its
 * first slash -- or its last character, with none. */
void volumeRoot(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    const auto leave = [&] {
        putByte(app, cpu.edx + 1, 0);
        cpu.ebp = pop(app, cpu);
        cpu.edi = pop(app, cpu);
        cpu.esi = pop(app, cpu);
        cpu.ecx = pop(app, cpu);
        cpu.ebx = pop(app, cpu);
        cpu.esp += 4;
    };
    // isSlash of the byte at `at`.
    const auto slash = [&](reg32 at) {
        cpu.eax = 0;
        cpu.al = byte(app, at);
        return direct(app, cpu, isSlash);
    };
    cpu.ebp = cpu.eax;
    cpu.esi = cpu.edx;
    cpu.edi = cpu.eax;
    putByte(app, cpu.edx, 0);
    stringLength(app, cpu);
    ++cpu.ecx;
    if (cpu.ecx < 0x104)
    {
        cpu.edi = cpu.ebp;
        stringLength(app, cpu);
        cpu.ebx = cpu.ecx + 1;
    }
    else
    {
        cpu.ebx = 0x104;
    }
    cpu.edx = cpu.esi;
    cpu.eax = cpu.ebp;
    if (!byAddress(app, cpu, kMoveMemory))
        return;
    cpu.ah = byte(app, cpu.esi);
    cpu.edx = cpu.esi;
    // A \\ looked for, a byte on at a time.
    if (cpu.ah != 0)
    {
        for (;;)
        {
            if (!slash(cpu.edx))
                return;
            if (cpu.eax != 0)
            {
                if (!slash(cpu.edx + 1))
                    return;
                if (cpu.eax != 0)
                    break;
            }
            cpu.bl = byte(app, cpu.edx + 1);
            ++cpu.edx;
            if (cpu.bl == 0)
                break;
        }
    }
    if (byte(app, cpu.edx) == 0)
    {
        // None: cut after the first slash.
        cpu.cl = byte(app, cpu.esi);
        cpu.edx = cpu.esi;
        if (cpu.cl == 0)
            return leave();
        for (;;)
        {
            if (!slash(cpu.edx))
                return;
            if (cpu.eax != 0)
                return leave();
            cpu.al = byte(app, cpu.edx + 1);
            ++cpu.edx;
            if (cpu.al == 0)
                return leave();
        }
    }
    // The server's name passed over, then the share's.
    cpu.ch = byte(app, cpu.edx + 2);
    cpu.edx += 2;
    if (cpu.ch != 0)
    {
        for (;;)
        {
            if (!slash(cpu.edx))
                return;
            if (cpu.eax != 0)
                break;
            cpu.ah = byte(app, cpu.edx + 1);
            ++cpu.edx;
            if (cpu.ah == 0)
                break;
        }
    }
    if (byte(app, cpu.edx) != 0)
        ++cpu.edx;
    cpu.ecx = 0;
    for (;;)
    {
        cpu.bh = byte(app, cpu.edx);
        if (cpu.cl == cpu.bh)
            break;
        cpu.eax = 0;
        cpu.al = cpu.bh;
        if (!direct(app, cpu, isSlash))
            return;
        if (cpu.eax != 0)
            break;
        ++cpu.edx;
    }
    leave();
}

/* 0x4e2fd0: the full path of path eax to edx (ebx bytes there): 1 if it
 * was found -- the path in capitals where its volume does not keep their
 * case, and the file's name as the directory has it where the volume keeps
 * no Unicode names -- else 0, the path copied as it is (at most 0x104
 * bytes); 0 too, reported, if its volume tells nothing. */
void fullPathName(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.esp -= 0x250;
    const reg32 f = cpu.esp;
    const auto leave = [&](reg32 result) {
        cpu.eax = result;
        cpu.esp = f + 0x250;
        cpu.ebp = pop(app, cpu);
        cpu.edi = pop(app, cpu);
        cpu.esi = pop(app, cpu);
        cpu.ecx = pop(app, cpu);
        cpu.esp += 4;
    };
    cpu.esi = cpu.eax;
    cpu.ebp = cpu.edx;
    cpu.eax = f + 0x24c;
    push(app, cpu, cpu.eax);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.esi);
    if (!windows(app, cpu, kGetFullPathNameA))
        return;
    if (cpu.eax == 0)
    {
        cpu.edi = cpu.esi;
        stringLength(app, cpu);
        ++cpu.ecx;
        if (cpu.ecx < 0x104)
        {
            cpu.edi = cpu.esi;
            stringLength(app, cpu);
            cpu.ebx = cpu.ecx + 1;
        }
        else
        {
            cpu.ebx = 0x104;
        }
        cpu.edx = cpu.ebp;
        cpu.eax = cpu.esi;
        if (!byAddress(app, cpu, kMoveMemory))
            return;
        return leave(0);
    }
    cpu.edx = f + 0x140;
    cpu.eax = cpu.ebp;
    if (!direct(app, cpu, volumeRoot))
        return;
    push(app, cpu, 0);
    push(app, cpu, 0);
    push(app, cpu, f + 0x244);
    cpu.eax = f + 0x248;
    push(app, cpu, cpu.eax);
    push(app, cpu, 0);
    push(app, cpu, 0);
    push(app, cpu, 0);
    cpu.eax = f + 0x140;
    push(app, cpu, cpu.eax);
    if (!windows(app, cpu, kGetVolumeInformationA))
        return;
    if (cpu.eax == 0)
    {
        if (!reportLastError(app, cpu, kVolumeFailed))
            return;
        cpu.esp += 0x10;
        return leave(0);
    }
    if ((byte(app, f + 0x244) & 2) == 0)
    {
        push(app, cpu, cpu.ebp);
        if (!windows(app, cpu, kCharUpperA))
            return;
    }
    if ((byte(app, f + 0x244) & 4) == 0)
    {
        cpu.eax = f;
        push(app, cpu, cpu.eax);
        push(app, cpu, cpu.esi);
        if (!windows(app, cpu, kFindFirstFileA))
            return;
        if (cpu.eax != 0xffffffff)
        {
            push(app, cpu, cpu.eax);
            cpu.esi = f + 0x2c;
            if (!windows(app, cpu, kFindClose))
                return;
            cpu.edi = at(app, f + 0x24c);
            copyString(app, cpu);
        }
    }
    leave(1);
}

/* 0x4e3110: GetLogicalDrives' bits, ecx and edx kept.  No caller in the
 * game. */
void logicalDrives(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    if (!windows(app, cpu, kGetLogicalDrives))
        return;
    cpu.edx = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x4e3120: the drive of path eax: its full path (or the directory's, not
 * found) cut to its root at edx, looked for among Windows' drives; the
 * drive's letter, or that of the first after the last there is, or 0 past
 * Z.  Its buffers Windows' pages (virtualAllocPages).  No caller in the
 * game. */
void driveOfPath(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.esp -= 0xc;
    const reg32 f = cpu.esp;
    cpu.ebp = cpu.eax;
    cpu.esi = cpu.edx;
    cpu.edx = 0x1000;
    push(app, cpu, 0);
    put(app, f, cpu.edx);
    if (!windows(app, cpu, kSetLastError))
        return;
    cpu.eax = f;
    cpu.ebx = 0xfff;
    if (!byAddress(app, cpu, kVirtualAllocPages))
        return;
    cpu.ecx = cpu.eax;
    put(app, f + 4, cpu.eax);
    cpu.edx = cpu.eax;
    cpu.eax = cpu.ebp;
    if (!direct(app, cpu, fullPathName))
        return;
    if (cpu.eax == 0)
    {
        cpu.eax = cpu.ecx;
        if (!direct(app, cpu, getDirectory))
            return;
    }
    cpu.eax = at(app, f + 4);
    cpu.edx = cpu.esi;
    cpu.ecx = at(app, f + 4);
    if (!direct(app, cpu, volumeRoot))
        return;
    push(app, cpu, cpu.ecx);
    push(app, cpu, 0);
    if (!windows(app, cpu, kGetLogicalDriveStringsA))
        return;
    cpu.ecx = cpu.eax;
    cpu.ebx = cpu.eax;
    if (sreg32(cpu.eax) > 0xfff)
    {
        cpu.eax = at(app, f + 4);
        if (!direct(app, cpu, virtualFreePages))
            return;
        ++cpu.ecx;
        cpu.eax = f;
        put(app, f, cpu.ecx);
        if (!byAddress(app, cpu, kVirtualAllocPages))
            return;
        put(app, f + 4, cpu.eax);
    }
    cpu.edi = at(app, f + 4);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebx);
    if (!windows(app, cpu, kGetLogicalDriveStringsA))
        return;
    cpu.ebx = cpu.edi;
    stringLength(app, cpu);
    if (!windows(app, cpu, kGetLogicalDrives))
        return;
    cpu.ebp = cpu.eax;
    cpu.eax = 0;
    put(app, f + 8, cpu.eax);
    cpu.eax = cpu.ebx;
    if (byte(app, cpu.eax) != 0)
    {
        for (;;)
        {
            cpu.cl = byte(app, f + 8);
            cpu.eax = 1;
            cpu.eax <<= cpu.cl & 0x1f;
            if ((cpu.ebp & cpu.eax) != 0)
            {
                cpu.edx = cpu.esi;
                cpu.eax = cpu.ebx;
                if (!byAddress(app, cpu, kStricmp))
                    return;
                if (cpu.eax == 0)
                    break;
                cpu.edi = cpu.ebx;
                stringLength(app, cpu);
                ++cpu.ecx;
                cpu.ebx += cpu.ecx;
            }
            cpu.edx = at(app, f + 8);
            ++cpu.edx;
            put(app, f + 8, cpu.edx);
            if (sreg32(cpu.edx) >= 0x20)
                break;
            if (byte(app, cpu.ebx) == 0)
                break;
        }
    }
    cpu.eax = at(app, f + 4);
    cpu.ebx = at(app, f + 8);
    if (!direct(app, cpu, virtualFreePages))
        return;
    cpu.eax = sreg32(cpu.ebx) >= 0x20 ? 0 : cpu.ebx + 'A';
    cpu.esp = f + 0xc;
    cpu.ebp = pop(app, cpu);
    cpu.edi = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x4e3250: the drive letter of path eax (none, "": the directory's), from
 * its full path -- in capitals -- if it starts X:; 0 if not, or if the path
 * has a |. */
void driveLetter(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.esi);
    cpu.esp -= 0x10c;
    const reg32 f = cpu.esp;
    const auto leave = [&] {
        cpu.esp = f + 0x10c;
        cpu.esi = pop(app, cpu);
        cpu.edx = pop(app, cpu);
        cpu.ecx = pop(app, cpu);
        cpu.esp += 4;
    };
    cpu.ecx = cpu.eax;
    cpu.dl = '|';
    cpu.esi = cpu.eax;
    // strchr's, two bytes a turn.
    for (;;)
    {
        cpu.al = byte(app, cpu.esi);
        if (cpu.al == cpu.dl)
            break;
        if (cpu.al == 0)
        {
            cpu.esi = 0;
            break;
        }
        ++cpu.esi;
        cpu.al = byte(app, cpu.esi);
        if (cpu.al == cpu.dl)
            break;
        ++cpu.esi;
        if (cpu.al == 0)
        {
            cpu.esi = 0;
            break;
        }
    }
    put(app, f + 0x108, cpu.esi);
    if (cpu.esi != 0)
    {
        cpu.eax = 0;
        return leave();
    }
    if (cpu.ecx == 0)
        cpu.ecx = kNoPath;
    cpu.eax = f + 0x108;
    push(app, cpu, cpu.eax);
    cpu.eax = f;
    push(app, cpu, cpu.eax);
    push(app, cpu, 0x105);
    push(app, cpu, cpu.ecx);
    if (!windows(app, cpu, kGetFullPathNameA))
        return;
    cpu.esi = cpu.eax;
    cpu.eax = f;
    push(app, cpu, cpu.eax);
    if (!windows(app, cpu, kCharUpperA))
        return;
    if (sreg32(cpu.esi) <= 1 || byte(app, f + 1) != ':')
    {
        cpu.eax = 0;
        return leave();
    }
    cpu.eax = 0;
    cpu.al = byte(app, f);
    leave();
}

/* 0x4e32e0: the bytes free on the volume whose root is at eax -- the
 * clusters free, their sectors, the sectors' bytes -- or 0.  No caller in the
 * game. */
void diskFreeBytes(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    cpu.esp -= 0x10;
    const reg32 f = cpu.esp;
    cpu.ebx = cpu.eax;
    push(app, cpu, 0);
    if (!windows(app, cpu, kSetLastError))
        return;
    for (const reg32 out : {f + 0xc, f + 8, f + 4, f})
    {
        cpu.eax = out;
        push(app, cpu, cpu.eax);
    }
    push(app, cpu, cpu.ebx);
    if (!windows(app, cpu, kGetDiskFreeSpaceA))
        return;
    if (cpu.eax != 0)
    {
        cpu.eax = at(app, f + 8);
        cpu.eax *= at(app, f);
        cpu.eax *= at(app, f + 4);
    }
    cpu.esp = f + 0x10;
    cpu.edx = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x4e3330: the drive of path eax by its number, 1 for A: (driveLetter); 0
 * for none. */
void driveNumber(win32::WinApplication* app, x86::CPU& cpu)
{
    if (!direct(app, cpu, driveLetter))
        return;
    if (cpu.eax != 0)
        cpu.eax -= 0x40;
    cpu.esp += 4;
}

/* 0x4e3340, EA's setdirectory: the current directory set to path eax; an
 * Error if it cannot be.  SetCurrentDirectory's answer back. */
void setDirectory(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    cpu.ebx = cpu.eax;
    push(app, cpu, 0);
    if (!windows(app, cpu, kSetLastError))
        return;
    push(app, cpu, cpu.ebx);
    if (!windows(app, cpu, kSetCurrentDirectoryA))
        return;
    if (cpu.eax == 0)
    {
        push(app, cpu, cpu.esi);
        cpu.edx = kFileC;
        push(app, cpu, cpu.ebx);
        cpu.ecx = kSetDirectoryName;
        cpu.esi = 0xe0;
        push(app, cpu, kSetDirectoryFailed);
        where(app, cpu.edx, cpu.ecx, cpu.esi);
        if (!byAddress(app, cpu, kError))
            return;
        cpu.esp += 8;
        cpu.esi = pop(app, cpu);
    }
    cpu.edx = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x4e33a0, EA's getdirectory: the current directory to eax (0x1ff bytes
 * there); an Error if it cannot be had or is longer.  Its length back. */
void getDirectory(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    cpu.ebx = cpu.eax;
    push(app, cpu, 0);
    if (!windows(app, cpu, kSetLastError))
        return;
    push(app, cpu, cpu.ebx);
    push(app, cpu, 0x1ff);
    if (!windows(app, cpu, kGetCurrentDirectoryA))
        return;
    cpu.ebx = cpu.eax;
    if (cpu.eax == 0 || cpu.eax > 0x1ff)
    {
        push(app, cpu, cpu.esi);
        cpu.edx = kFileC;
        push(app, cpu, cpu.ebx);
        cpu.ecx = kGetDirectoryName;
        cpu.esi = 0xe9;
        push(app, cpu, kGetDirectoryFailed);
        where(app, cpu.edx, cpu.ecx, cpu.esi);
        if (!byAddress(app, cpu, kError))
            return;
        cpu.esp += 8;
        cpu.esi = pop(app, cpu);
    }
    cpu.edx = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x4e3410: 1 if the handles' table is made, else 0 (notSlash's way out).
 * No caller in the game. */
void handlesReady(win32::WinApplication* app, x86::CPU& cpu)
{
    if (at(app, kHandles) == 0)
        return notSlash(app, cpu);
    cpu.eax = 1;
    cpu.esp += 4;
}

/* 0x4e3430: the handles' table made anew for eax handles (0: 0x40): its
 * lock made the first time, the table there closed (closeAllHandles -- which
 * frees the lock, left 0 for the rest), Windows' pages taken for it under
 * the lock, it and the drives' locks cleared. */
void initHandles(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    cpu.esp -= 4;
    const reg32 f = cpu.esp;
    cpu.ebx = cpu.eax;
    if (at(app, kHandlesLock) == 0)
    {
        if (!byAddress(app, cpu, kNewLock))
            return;
        put(app, kHandlesLock, cpu.eax);
    }
    if (at(app, kHandles) != 0 && !direct(app, cpu, closeAllHandles))
        return;
    cpu.esi = at(app, kHandlesLock);
    push(app, cpu, cpu.esi);
    if (!windows(app, cpu, kEnterCriticalSection))
        return;
    if (cpu.ebx == 0)
        cpu.ebx = kDefaultHandles;
    cpu.eax = cpu.ebx << kSlotShift;
    put(app, f, cpu.eax);
    cpu.eax = f;
    if (!byAddress(app, cpu, kVirtualAllocPages))
        return;
    put(app, kHandles, cpu.eax);
    put(app, kHandleCount, cpu.ebx);
    if (cpu.eax != 0)
    {
        cpu.edx = at(app, f);
        if (!byAddress(app, cpu, kFillZero))
            return;
        cpu.edx = kDriveLocksBytes;
        cpu.eax = kDriveLocks;
        if (!byAddress(app, cpu, kFillZero))
            return;
    }
    cpu.edi = at(app, kHandlesLock);
    push(app, cpu, cpu.edi);
    if (!windows(app, cpu, kLeaveCriticalSection))
        return;
    cpu.esp = f + 4;
    cpu.edi = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x4e34c0: the handles' table gone, if there is one: every handle open
 * closed under its lock, its pages given back, the drives' locks and its own
 * freed. */
void closeAllHandles(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.ebp);
    const auto leave = [&] {
        cpu.ebp = pop(app, cpu);
        cpu.edx = pop(app, cpu);
        cpu.ecx = pop(app, cpu);
        cpu.esp += 4;
    };
    if (at(app, kHandles) == 0)
        return leave();
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.ebx);
    cpu.ecx = at(app, kHandlesLock);
    push(app, cpu, cpu.ecx);
    if (!windows(app, cpu, kEnterCriticalSection))
        return;
    cpu.ebx = at(app, kHandleCount);
    cpu.edx = 0;
    if (sreg32(cpu.ebx) > 0)
    {
        cpu.ecx = 0;
        do
        {
            cpu.eax = at(app, kHandles);
            if (byte(app, cpu.ecx + cpu.eax) != 0)
            {
                cpu.eax = ~cpu.edx;
                if (!direct(app, cpu, closeHandleSlot))
                    return;
            }
            cpu.esi = at(app, kHandleCount);
            ++cpu.edx;
            cpu.ecx += kSlotBytes;
        } while (sreg32(cpu.edx) < sreg32(cpu.esi));
    }
    cpu.eax = at(app, kHandles);
    if (!direct(app, cpu, virtualFreePages))
        return;
    cpu.edi = 0;
    cpu.edx = 0;
    put(app, kHandles, cpu.edi);
    cpu.ecx = 0;
    cpu.ebx = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.edi = pop(app, cpu);
    do
    {
        cpu.ebp = at(app, cpu.edx + kDriveLocks);
        if (cpu.ecx != cpu.ebp)
        {
            cpu.eax = cpu.ebp;
            if (!byAddress(app, cpu, kFreeLock))
                return;
            put(app, cpu.edx + kDriveLocks, cpu.ecx);
        }
        cpu.edx += 4;
    } while (cpu.edx != kDriveLocksBytes);
    cpu.eax = at(app, kHandlesLock);
    push(app, cpu, cpu.eax);
    if (!windows(app, cpu, kLeaveCriticalSection))
        return;
    cpu.eax = at(app, kHandlesLock);
    cpu.edx = 0;
    if (!byAddress(app, cpu, kFreeLock))
        return;
    put(app, kHandlesLock, cpu.edx);
    leave();
}

/* 0x4e3570: a slot of the table taken, under its lock (the table made
 * first if there is none): the first not in use, cleared, in use; its
 * index back -- the count of handles, none free. */
void takeHandleSlot(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.ebp);
    if (at(app, kHandles) == 0)
    {
        cpu.eax = 0;
        if (!direct(app, cpu, initHandles))
            return;
    }
    cpu.ecx = at(app, kHandlesLock);
    push(app, cpu, cpu.ecx);
    if (!windows(app, cpu, kEnterCriticalSection))
        return;
    cpu.esi = at(app, kHandleCount);
    cpu.ebx = 0;
    if (sreg32(cpu.esi) > 0)
    {
        cpu.edx = at(app, kHandles);
        cpu.esi <<= kSlotShift;
        cpu.eax = 0;
        while (byte(app, cpu.edx + cpu.eax) != 0)
        {
            cpu.eax += kSlotBytes;
            ++cpu.ebx;
            if (sreg32(cpu.eax) >= sreg32(cpu.esi))
                break;
        }
    }
    if (sreg32(cpu.ebx) < sreg32(at(app, kHandleCount)))
    {
        cpu.esi = cpu.ebx;
        cpu.eax = at(app, kHandles);
        cpu.esi <<= kSlotShift;
        cpu.edx = kSlotBytes;
        cpu.eax += cpu.esi;
        if (!byAddress(app, cpu, kFillZero))
            return;
        cpu.eax = at(app, kHandles);
        putByte(app, cpu.esi + cpu.eax, 1);
    }
    cpu.ebp = at(app, kHandlesLock);
    push(app, cpu, cpu.ebp);
    if (!windows(app, cpu, kLeaveCriticalSection))
        return;
    cpu.eax = cpu.ebx;
    cpu.ebp = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x4e3600: the file named eax deleted; DeleteFile's answer back. */
void deleteFile(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    cpu.ebx = cpu.eax;
    push(app, cpu, 0);
    if (!windows(app, cpu, kSetLastError))
        return;
    push(app, cpu, cpu.ebx);
    if (!windows(app, cpu, kDeleteFileA))
        return;
    cpu.edx = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x4e3620: the file named eax opened as the flags edx say, in a slot of
 * the table (takeHandleSlot), its handle to [ecx] (0 till then): under its
 * drive's lock -- made the first time -- the file made or opened, its block
 * ebx rounded up to the volume's sectors (none asked, or no sector told:
 * 0x4000; no volume told: 0x800 sectors), its length; mapped into memory if
 * asked (0x800, kept only if it is).  1 if opened; else 0 and reported. */
void openFileHandle(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.esp -= 0x12c;
    const reg32 f = cpu.esp;
    put(app, f + 0x11c, cpu.eax);
    put(app, f + 0x128, cpu.edx);
    put(app, f + 0x120, cpu.ebx);
    put(app, f + 0x118, cpu.ecx);
    if (!direct(app, cpu, takeHandleSlot))
        return;
    cpu.ebx = 0x80;
    cpu.ebp = 0;
    cpu.esi = cpu.eax;
    push(app, cpu, cpu.ebp);
    cpu.edi = 0;
    put(app, cpu.ecx, cpu.ebp);
    if (!windows(app, cpu, kSetLastError))
        return;
    cpu.ecx = cpu.esi;
    put(app, f + 0x124, cpu.ebp);
    const auto leave = [&] {
        cpu.eax = cpu.ebp;
        cpu.esp = f + 0x12c;
        cpu.ebp = pop(app, cpu);
        cpu.edi = pop(app, cpu);
        cpu.esi = pop(app, cpu);
        cpu.esp += 4;
    };
    if (sreg32(cpu.ecx) < 0 || sreg32(cpu.esi) >= sreg32(at(app, kHandleCount)))
        return leave();
    const reg8 flags = byte(app, f + 0x128);
    if (flags & 1)
        cpu.edi = 0x80000000;  // GENERIC_READ
    if (flags & 2)
        cpu.edi |= 0x40000000;  // GENERIC_WRITE
    if (flags & 4)
        putByte(app, f + 0x124, byte(app, f + 0x124) | 1);  // FILE_SHARE_READ
    if (flags & 8)
        putByte(app, f + 0x124, byte(app, f + 0x124) | 2);  // FILE_SHARE_WRITE
    cpu.ah = byte(app, f + 0x128);
    // How it is made: CREATE_NEW 1, CREATE_ALWAYS 2, OPEN_EXISTING 3, TRUNCATE_EXISTING 5.
    if (cpu.ah & 0x10)
    {
        cpu.ebp = (cpu.ah & 0x20) ? 2 : 1;
    }
    else
    {
        cpu.eax = (cpu.ah & 0x20) ? 5 : 3;
        cpu.ebp = cpu.eax;
    }
    const reg8 attributes = byte(app, f + 0x129);
    if (attributes & 1)
        cpu.ebx |= 0x20000000;  // FILE_FLAG_NO_BUFFERING
    if (attributes & 2)
        cpu.ebx |= 0x8000000;  // FILE_FLAG_SEQUENTIAL_SCAN
    if (attributes & 4)
        cpu.ebx |= 0x80000000;  // FILE_FLAG_WRITE_THROUGH
    cpu.edx = cpu.esi;
    cpu.eax = at(app, kHandles);
    cpu.edx <<= kSlotShift;
    cpu.ecx = at(app, f + 0x128);
    put(app, cpu.edx + cpu.eax + 8, cpu.ecx);
    cpu.eax = at(app, f + 0x11c);
    if (!direct(app, cpu, driveNumber))
        return;
    cpu.ecx = at(app, kHandles);
    cpu.edx += cpu.ecx;
    put(app, f + 0x114, cpu.eax);
    putByte(app, cpu.edx + 1, cpu.al);
    cpu.edx = cpu.eax * 4;
    cpu.eax = at(app, cpu.edx + kDriveLocks);
    if (cpu.eax == 0)
    {
        if (!byAddress(app, cpu, kNewLock))
            return;
        put(app, cpu.edx + kDriveLocks, cpu.eax);
    }
    cpu.eax = at(app, f + 0x114);
    if (!driveLock(app, cpu, cpu.edx, cpu.eax, kEnterCriticalSection))
        return;
    for (const reg32 out : {f + 0x110, f + 0x10c, f + 0x108, f + 0x104, f})
    {
        cpu.eax = out;
        push(app, cpu, cpu.eax);
    }
    if (!windows(app, cpu, kGetDiskFreeSpaceA))
        return;
    if (cpu.eax == 0)
        put(app, f + 0x108, kNoDiskSector);
    push(app, cpu, 0);
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ebp);
    push(app, cpu, 0);
    cpu.ebx = at(app, f + 0x124);
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.edi);
    cpu.edi = at(app, f + 0x11c);
    cpu.ebx = cpu.esi;
    push(app, cpu, cpu.edi);
    cpu.ebx <<= kSlotShift;
    if (!windows(app, cpu, kCreateFileA))
        return;
    cpu.ebp = at(app, kHandles);
    cpu.ebp += cpu.ebx;
    put(app, cpu.ebp + 4, cpu.eax);
    if (cpu.eax == 0xffffffff)
    {
        if (!reportLastError(app, cpu, kCreateFileFailed))
            return;
        cpu.eax = at(app, kHandles);
        cpu.ebp = 0;
        cpu.esp += 0x10;
        putByte(app, cpu.ebx + cpu.eax, 0);
    }
    else
    {
        cpu.edx = at(app, f + 0x120);
        bool blockSet = false;
        if (cpu.edx != 0)
        {
            cpu.ecx = at(app, f + 0x108);
            if (cpu.ecx != 0)
            {
                if (cpu.edx > cpu.ecx)
                {
                    cpu.eax = cpu.edx + cpu.ecx - 1;
                    cpu.edx = 0;
                    const reg32 quotient = cpu.eax / cpu.ecx;
                    cpu.edx = cpu.eax % cpu.ecx;
                    cpu.eax = quotient * cpu.ecx;
                    put(app, cpu.ebp + 0xc, cpu.eax);
                }
                else
                {
                    put(app, cpu.ebp + 0xc, cpu.ecx);
                }
                blockSet = true;
            }
        }
        if (!blockSet)
        {
            cpu.eax = cpu.esi;
            cpu.edx = at(app, kHandles);
            cpu.eax <<= kSlotShift;
            put(app, cpu.edx + cpu.eax + 0xc, kDefaultBlock);
        }
        cpu.edi = cpu.esi;
        cpu.eax = at(app, kHandles);
        cpu.edi <<= kSlotShift;
        push(app, cpu, 0);
        cpu.ebp = at(app, cpu.edi + cpu.eax + 4);
        push(app, cpu, cpu.ebp);
        if (!windows(app, cpu, kGetFileSize))
            return;
        cpu.ebx = cpu.eax;
        cpu.eax = at(app, kHandles);
        cpu.eax += cpu.edi;
        cpu.dl = byte(app, f + 0x129);
        put(app, cpu.eax + 0x1c, cpu.ebx);
        bool unmapped = true;
        if (cpu.dl & (kMapped >> 8))
        {
            if (byte(app, f + 0x128) & 2)
            {
                cpu.edi = 2;            // FILE_MAP_WRITE
                cpu.eax = 0x8000004;    // SEC_COMMIT | PAGE_READWRITE
            }
            else
            {
                cpu.edi = 4;            // FILE_MAP_READ
                cpu.eax = 0x8000002;    // SEC_COMMIT | PAGE_READONLY
            }
            push(app, cpu, 0);
            push(app, cpu, 0);
            push(app, cpu, 0);
            cpu.ebx = cpu.esi;
            push(app, cpu, cpu.eax);
            cpu.eax = at(app, kHandles);
            cpu.ebx <<= kSlotShift;
            push(app, cpu, 0);
            cpu.edx = at(app, cpu.ebx + cpu.eax + 4);
            push(app, cpu, cpu.edx);
            if (!windows(app, cpu, kCreateFileMappingA))
                return;
            cpu.edx = cpu.eax;
            cpu.eax = at(app, kHandles);
            cpu.eax += cpu.ebx;
            cpu.ecx = cpu.edx;
            put(app, cpu.eax + 0x10, cpu.edx);
            if (cpu.ecx != 0)
            {
                cpu.ebp = at(app, cpu.eax + 0x1c);
                push(app, cpu, cpu.ebp);
                push(app, cpu, 0);
                push(app, cpu, 0);
                push(app, cpu, cpu.edi);
                push(app, cpu, cpu.edx);
                if (!windows(app, cpu, kMapViewOfFile))
                    return;
                cpu.edx = at(app, kHandles);
                put(app, cpu.edx + cpu.ebx + 0x14, cpu.eax);
            }
            cpu.edx = cpu.esi;
            cpu.eax = at(app, kHandles);
            cpu.edx <<= kSlotShift;
            cpu.eax += cpu.edx;
            unmapped = at(app, cpu.eax + 0x14) == 0;
        }
        if (unmapped)
            putByte(app, cpu.eax + 9, byte(app, cpu.eax + 9) & ~(kMapped >> 8));
        cpu.ebx = cpu.esi;
        cpu.eax = at(app, f + 0x118);
        cpu.ebx = ~cpu.ebx;
        put(app, cpu.eax, cpu.esi);
        cpu.ebp = 1;
        put(app, cpu.eax, cpu.ebx);
    }
    cpu.eax = at(app, f + 0x114);
    if (!driveLock(app, cpu, cpu.esi, cpu.eax, kLeaveCriticalSection))
        return;
    leave();
}

/* 0x4e3980: what handle eax is: how it was opened to [edx], its block to
 * [ebx], its length to [ecx], and the bytes free on its drive to the stack's
 * word (each pointer may be 0) -- the clusters free by the sectors' bytes,
 * not by the cluster's: 0 back, reported, if the drive tells nothing.  1 if
 * told, 0 if the handle is not open; the word taken off. */
void handleInfo(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.esp -= 0x20;
    const reg32 f = cpu.esp;
    const auto leave = [&](reg32 result) {
        cpu.eax = result;
        cpu.esp = f + 0x20;
        cpu.ebp = pop(app, cpu);
        cpu.edi = pop(app, cpu);
        cpu.esi = pop(app, cpu);
        cpu.esp += 4 + 4;
    };
    cpu.esi = cpu.edx;
    cpu.ebp = cpu.ebx;
    cpu.edi = cpu.ecx;
    cpu.edx = 1;
    cpu.ecx = at(app, kHandles);
    cpu.ebx = cpu.eax;
    put(app, f + 0x14, cpu.edx);
    cpu.ebx = ~cpu.ebx;
    if (cpu.ecx == 0 || sreg32(cpu.ebx) < 0 || sreg32(cpu.ebx) >= sreg32(at(app, kHandleCount)))
        return leave(0);
    cpu.eax = cpu.ebx << kSlotShift;
    put(app, f + 0x18, cpu.eax);
    cpu.eax += cpu.ecx;
    if (byte(app, cpu.eax) == 0)
        return leave(0);
    cpu.al = byte(app, cpu.eax + 1);
    cpu.eax &= 0xff;
    cpu.ecx = at(app, cpu.eax * 4 + kDriveLocks);
    push(app, cpu, cpu.ecx);
    put(app, f + 0x1c, cpu.eax);
    if (!windows(app, cpu, kEnterCriticalSection))
        return;
    push(app, cpu, 0);
    if (!windows(app, cpu, kSetLastError))
        return;
    if (cpu.esi != 0)
    {
        cpu.edx = at(app, f + 0x18);
        cpu.eax = at(app, kHandles);
        cpu.eax += cpu.edx;
        cpu.eax = at(app, cpu.eax + 8);
        put(app, cpu.esi, cpu.eax);
    }
    if (cpu.ebp != 0)
    {
        cpu.eax = cpu.ebx;
        cpu.esi = at(app, kHandles);
        cpu.eax <<= kSlotShift;
        cpu.eax = at(app, cpu.esi + cpu.eax + 0xc);
        put(app, cpu.ebp, cpu.eax);
    }
    if (cpu.edi != 0)
    {
        cpu.eax = cpu.ebx;
        cpu.ebx = at(app, kHandles);
        cpu.eax <<= kSlotShift;
        cpu.eax = at(app, cpu.ebx + cpu.eax + 0x1c);
        put(app, cpu.edi, cpu.eax);
    }
    if (at(app, f + 0x30) != 0)
    {
        // " :\" made the drive's root.
        cpu.esi = kDriveRoot;
        cpu.edi = f + 0x10;
        copyString(app, cpu);
        cpu.al = byte(app, f + 0x1c);
        cpu.al += 0x40;
        putByte(app, f + 0x10, cpu.al);
        for (const reg32 out : {f + 0xc, f + 8, f + 4, f})
        {
            cpu.eax = out;
            push(app, cpu, cpu.eax);
        }
        cpu.eax = f + 0x10;
        push(app, cpu, cpu.eax);
        if (!windows(app, cpu, kGetDiskFreeSpaceA))
            return;
        if (cpu.eax != 0)
        {
            cpu.eax = at(app, f + 8);
            cpu.eax *= at(app, f + 4);
            cpu.ebx = at(app, f + 0x30);
            put(app, cpu.ebx, cpu.eax);
        }
        else
        {
            if (!windows(app, cpu, kGetLastError))
                return;
            cpu.eax &= 0xffff;
            push(app, cpu, cpu.eax);
            push(app, cpu, kDiskFreeFailed);
            push(app, cpu, 1);
            push(app, cpu, kReportLevel);
            cpu.ebx = 0;
            if (!direct(app, cpu, fileReport))
                return;
            cpu.esp += 0x10;
            put(app, f + 0x14, cpu.ebx);
        }
    }
    cpu.eax = at(app, f + 0x1c);
    if (!driveLock(app, cpu, cpu.edi, cpu.eax, kLeaveCriticalSection))
        return;
    leave(at(app, f + 0x14));
}

/* 0x4e3ae0: ebx bytes of handle eax read to edx -- no more than are left of
 * it -- a block at a time, from its memory if it is mapped, under its
 * drive's lock (+2 set while; cleared from elsewhere, the read stops); a
 * read pending waited for.  How many were read back (0 if it is not open,
 * or reported on an error). */
void readHandleBytes(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.esp -= 0x1c;
    const reg32 f = cpu.esp;
    const auto leave = [&](reg32 result) {
        cpu.eax = result;
        cpu.esp = f + 0x1c;
        cpu.ebp = pop(app, cpu);
        cpu.edi = pop(app, cpu);
        cpu.esi = pop(app, cpu);
        cpu.ecx = pop(app, cpu);
        cpu.esp += 4;
    };
    cpu.ebp = cpu.edx;
    cpu.edi = cpu.ebx;
    cpu.ebx = at(app, kHandles);
    put(app, f + 0xc, cpu.eax);
    cpu.ecx = cpu.eax;
    cpu.edx = 0;
    cpu.ecx = ~cpu.ecx;
    put(app, f + 0x18, cpu.edx);
    put(app, f + 0xc, cpu.ecx);
    if (cpu.ebx == 0 || sreg32(cpu.ecx) < 0 || sreg32(cpu.ecx) >= sreg32(at(app, kHandleCount)))
        return leave(0);
    cpu.esi = cpu.ecx << kSlotShift;
    cpu.eax = cpu.ebx + cpu.esi;
    if (byte(app, cpu.eax) == 0)
        return leave(0);
    cpu.al = byte(app, cpu.eax + 1);
    cpu.eax &= 0xff;
    cpu.ecx = at(app, cpu.eax * 4 + kDriveLocks);
    push(app, cpu, cpu.ecx);
    put(app, f + 8, cpu.eax);
    if (!windows(app, cpu, kEnterCriticalSection))
        return;
    push(app, cpu, 0);
    if (!windows(app, cpu, kSetLastError))
        return;
    cpu.eax = at(app, kHandles);
    cpu.eax += cpu.esi;
    cpu.edx = at(app, cpu.eax + 0x18);
    cpu.ebx = at(app, cpu.eax + 0x1c);
    if (sreg32(cpu.edx) > sreg32(cpu.ebx))
        put(app, cpu.eax + 0x18, cpu.ebx);
    cpu.edx = at(app, f + 0xc);
    cpu.eax = at(app, kHandles);
    cpu.edx <<= kSlotShift;
    cpu.eax += cpu.edx;
    cpu.edx = at(app, cpu.eax + 0x18);
    cpu.esi = at(app, cpu.eax + 0x1c);
    cpu.edx += cpu.edi;
    if (sreg32(cpu.edx) > sreg32(cpu.esi))
    {
        cpu.edi = cpu.esi;
        cpu.edi -= at(app, cpu.eax + 0x18);
    }
    cpu.eax = at(app, f + 0xc);
    cpu.edx = at(app, kHandles);
    cpu.eax <<= kSlotShift;
    cpu.esi = at(app, cpu.edx + cpu.eax + 0xc);
    putByte(app, cpu.edx + cpu.eax + 2, 1);
    if (cpu.edi != 0)
    {
        put(app, f + 0x14, cpu.eax);
        put(app, f + 0x10, cpu.eax);
        put(app, f, cpu.eax);
        for (;;)
        {
            cpu.ecx = at(app, f + 0x10);
            cpu.eax = at(app, kHandles);
            cpu.eax += cpu.ecx;
            if (byte(app, cpu.eax + 2) == 0)
                break;
            if (cpu.esi > cpu.edi)
                cpu.esi = cpu.edi;
            cpu.ebx = at(app, f + 0x14);
            cpu.eax = at(app, kHandles);
            cpu.eax += cpu.ebx;
            cpu.edx = at(app, cpu.eax + 0x14);
            bool done = true;
            if (cpu.edx != 0)
            {
                cpu.eax = at(app, cpu.eax + 0x18);
                cpu.ebx = cpu.esi;
                cpu.eax += cpu.edx;
                cpu.edx = cpu.ebp;
                if (!byAddress(app, cpu, kMoveMemory))
                    return;
                cpu.eax = 0;
                put(app, f + 4, cpu.esi);
                if (!byAddress(app, cpu, kSleep))
                    return;
            }
            else
            {
                push(app, cpu, cpu.edx);
                cpu.edx = f + 4;
                push(app, cpu, cpu.edx);
                push(app, cpu, cpu.esi);
                push(app, cpu, cpu.ebp);
                cpu.ecx = at(app, cpu.eax + 4);
                push(app, cpu, cpu.ecx);
                if (!windows(app, cpu, kReadFile))
                    return;
                if (cpu.eax == 0)
                {
                    if (!windows(app, cpu, kGetLastError))
                        return;
                    if (cpu.eax != kIoPending)
                    {
                        cpu.eax &= 0xffff;
                        push(app, cpu, cpu.eax);
                        push(app, cpu, kReadFileFailed);
                        push(app, cpu, 1);
                        push(app, cpu, kReportLevel);
                        cpu.ebx = 0;
                        if (!direct(app, cpu, fileReport))
                            return;
                        cpu.esp += 0x10;
                        put(app, f + 0x18, cpu.ebx);
                        break;
                    }
                    cpu.eax = 1;
                    if (!byAddress(app, cpu, kSleep))
                        return;
                    done = false;
                }
            }
            if (done)
            {
                cpu.eax = at(app, f);
                cpu.edx = at(app, kHandles);
                cpu.edx += cpu.eax;
                cpu.eax = at(app, f + 4);
                cpu.ecx = at(app, cpu.edx + 0x18);
                cpu.ecx += cpu.eax;
                put(app, cpu.edx + 0x18, cpu.ecx);
                cpu.ebx = at(app, f + 0x18);
                cpu.eax = at(app, f + 4);
                cpu.ebx += cpu.eax;
                cpu.ebp += cpu.eax;
                cpu.eax = cpu.ecx;
                cpu.ecx = at(app, cpu.edx + 0x1c);
                put(app, f + 0x18, cpu.ebx);
                if (sreg32(cpu.eax) > sreg32(cpu.ecx))
                    put(app, cpu.edx + 0x18, cpu.ecx);
                cpu.ebx = at(app, f + 4);
                if (cpu.esi > cpu.ebx)
                    break;  // fewer than asked: the end
                cpu.edi -= cpu.ebx;
            }
            if (cpu.edi == 0)
                break;
        }
    }
    cpu.eax = at(app, f + 0xc);
    cpu.edx = at(app, kHandles);
    cpu.eax <<= kSlotShift;
    putByte(app, cpu.edx + cpu.eax + 2, 0);
    cpu.eax = at(app, f + 8);
    if (!driveLock(app, cpu, cpu.edx, cpu.eax, kLeaveCriticalSection))
        return;
    leave(at(app, f + 0x18));
}

/* 0x4e3cc0: ebx bytes at edx written to handle eax a block at a time -- to
 * its memory if it is mapped, no more than its length there -- under its
 * drive's lock, its length grown as it is written past; a write pending
 * waited for.  How many were written back (0 if it is not open, or reported
 * on an error). */
void writeHandleBytes(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.esp -= 0x10;
    const reg32 f = cpu.esp;
    const auto leave = [&](reg32 result) {
        cpu.eax = result;
        cpu.esp = f + 0x10;
        cpu.ebp = pop(app, cpu);
        cpu.edi = pop(app, cpu);
        cpu.esi = pop(app, cpu);
        cpu.ecx = pop(app, cpu);
        cpu.esp += 4;
    };
    cpu.ebp = cpu.edx;
    cpu.edi = cpu.ebx;
    cpu.ecx = at(app, kHandles);
    cpu.ebx = cpu.eax;
    cpu.edx = 0;
    cpu.ebx = ~cpu.ebx;
    put(app, f + 8, cpu.edx);
    if (cpu.ecx == 0 || sreg32(cpu.ebx) < 0 || sreg32(cpu.ebx) >= sreg32(at(app, kHandleCount)))
        return leave(0);
    cpu.esi = cpu.ebx << kSlotShift;
    cpu.eax = cpu.ecx + cpu.esi;
    if (byte(app, cpu.eax) == 0)
        return leave(0);
    cpu.al = byte(app, cpu.eax + 1);
    cpu.eax &= 0xff;
    cpu.edx = at(app, cpu.eax * 4 + kDriveLocks);
    push(app, cpu, cpu.edx);
    put(app, f + 4, cpu.eax);
    if (!windows(app, cpu, kEnterCriticalSection))
        return;
    push(app, cpu, 0);
    if (!windows(app, cpu, kSetLastError))
        return;
    cpu.eax = at(app, kHandles);
    cpu.eax += cpu.esi;
    cpu.edx = at(app, cpu.eax + 0x18);
    cpu.ecx = at(app, cpu.eax + 0x1c);
    if (sreg32(cpu.edx) > sreg32(cpu.ecx))
        put(app, cpu.eax + 0x18, cpu.ecx);
    cpu.edx = cpu.ebx;
    cpu.eax = at(app, kHandles);
    cpu.edx <<= kSlotShift;
    cpu.eax += cpu.edx;
    cpu.edx = at(app, cpu.eax + 0x14);
    cpu.esi = at(app, cpu.eax + 0xc);
    if (cpu.edx != 0)
    {
        cpu.edx = at(app, cpu.eax + 0x18);
        cpu.ecx = at(app, cpu.eax + 0x1c);
        cpu.edx += cpu.edi;
        if (sreg32(cpu.edx) > sreg32(cpu.ecx))
        {
            cpu.edi = cpu.ecx;
            cpu.edi -= at(app, cpu.eax + 0x18);
        }
    }
    cpu.ebx <<= kSlotShift;
    put(app, f + 0xc, cpu.ebx);
    while (cpu.edi != 0)
    {
        if (cpu.esi > cpu.edi)
            cpu.esi = cpu.edi;
        cpu.ecx = at(app, f + 0xc);
        cpu.eax = at(app, kHandles);
        cpu.eax += cpu.ecx;
        cpu.ebx = at(app, cpu.eax + 0x14);
        if (cpu.ebx != 0)
        {
            cpu.ecx = at(app, cpu.eax + 0x18);
            cpu.edx = cpu.ebx + cpu.ecx;
            cpu.eax = cpu.ebp;
            cpu.ebx = cpu.esi;
            if (!byAddress(app, cpu, kMoveMemory))
                return;
            cpu.eax = 0;
            put(app, f, cpu.esi);
            if (!byAddress(app, cpu, kSleep))
                return;
        }
        else
        {
            push(app, cpu, cpu.ebx);
            cpu.edx = f;
            push(app, cpu, cpu.edx);
            push(app, cpu, cpu.esi);
            push(app, cpu, cpu.ebp);
            cpu.edx = at(app, cpu.eax + 4);
            push(app, cpu, cpu.edx);
            if (!windows(app, cpu, kWriteFile))
                return;
            if (cpu.eax == 0)
            {
                if (!windows(app, cpu, kGetLastError))
                    return;
                if (cpu.eax != kIoPending)
                {
                    cpu.eax &= 0xffff;
                    push(app, cpu, cpu.eax);
                    push(app, cpu, kWriteFileFailed);
                    push(app, cpu, 1);
                    push(app, cpu, kReportLevel);
                    if (!direct(app, cpu, fileReport))
                        return;
                    cpu.esp += 0x10;
                    put(app, f + 8, cpu.ebx);
                    break;
                }
                cpu.eax = 1;
                if (!byAddress(app, cpu, kSleep))
                    return;
                continue;
            }
        }
        cpu.ebx = at(app, f + 0xc);
        cpu.edx = at(app, kHandles);
        cpu.edx += cpu.ebx;
        cpu.eax = at(app, f);
        put(app, cpu.edx + 0x18, at(app, cpu.edx + 0x18) + cpu.eax);
        cpu.ebx = at(app, f + 8);
        cpu.eax = at(app, f);
        cpu.ebx += cpu.eax;
        cpu.ebp += cpu.eax;
        put(app, f + 8, cpu.ebx);
        if (cpu.esi > cpu.eax)
            cpu.edi = 0;  // fewer than asked: no more
        else
            cpu.edi -= cpu.eax;
        cpu.ebx = at(app, f + 0xc);
        cpu.eax = at(app, kHandles);
        cpu.eax += cpu.ebx;
        cpu.edx = at(app, cpu.eax + 0x18);
        if (sreg32(cpu.edx) > sreg32(at(app, cpu.eax + 0x1c)))
            put(app, cpu.eax + 0x1c, cpu.edx);
    }
    cpu.eax = at(app, f + 4);
    if (!driveLock(app, cpu, cpu.ebx, cpu.eax, kLeaveCriticalSection))
        return;
    leave(at(app, f + 8));
}

/* 0x4e3e60: handle eax sought to edx, kept within its length, under its
 * drive's lock -- the file itself too unless it is mapped; then 1 back.  A
 * mapped one gives back what the stack's word held there (the code's
 * local, never set).  0 if it is not open. */
void seekHandleTo(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.esp -= 4;
    const reg32 f = cpu.esp;
    const auto leave = [&] {
        cpu.esp = f + 4;
        cpu.ebp = pop(app, cpu);
        cpu.edi = pop(app, cpu);
        cpu.esi = pop(app, cpu);
        cpu.ebx = pop(app, cpu);
        cpu.esp += 4;
    };
    cpu.ebp = cpu.edx;
    cpu.ebx = cpu.eax;
    cpu.edx = at(app, kHandles);
    cpu.ebx = ~cpu.ebx;
    if (cpu.edx == 0 || sreg32(cpu.ebx) < 0 || sreg32(cpu.ebx) >= sreg32(at(app, kHandleCount)))
    {
        cpu.eax = 0;
        return leave();
    }
    cpu.esi = cpu.ebx << kSlotShift;
    cpu.edi = cpu.edx + cpu.esi;
    if (byte(app, cpu.edi) == 0)
    {
        cpu.eax = 0;
        return leave();
    }
    push(app, cpu, cpu.ecx);
    cpu.edi = byte(app, cpu.edi + 1);
    cpu.eax = at(app, cpu.edi * 4 + kDriveLocks);
    push(app, cpu, cpu.eax);
    if (!windows(app, cpu, kEnterCriticalSection))
        return;
    push(app, cpu, 0);
    if (!windows(app, cpu, kSetLastError))
        return;
    cpu.eax = at(app, kHandles);
    cpu.eax += cpu.esi;
    cpu.esi = cpu.ebp;
    cpu.edx = at(app, cpu.eax + 0x1c);
    put(app, cpu.eax + 0x18, cpu.ebp);
    if (sreg32(cpu.esi) > sreg32(cpu.edx))
        put(app, cpu.eax + 0x18, cpu.edx);
    else if (sreg32(cpu.esi) < 0)
        put(app, cpu.eax + 0x18, 0);
    cpu.eax = at(app, kHandles);
    cpu.ebx <<= kSlotShift;
    cpu.eax += cpu.ebx;
    cpu.esi = at(app, cpu.eax + 0x14);
    if (cpu.esi == 0)
    {
        push(app, cpu, cpu.esi);
        push(app, cpu, cpu.esi);
        cpu.ebp = at(app, cpu.eax + 0x18);
        push(app, cpu, cpu.ebp);
        cpu.edx = at(app, cpu.eax + 4);
        push(app, cpu, cpu.edx);
        if (!windows(app, cpu, kSetFilePointer))
            return;
        cpu.ecx = 1;
        cpu.esi = at(app, kHandles);
        put(app, f, cpu.ecx);
        put(app, cpu.esi + cpu.ebx + 0x18, cpu.eax);
    }
    if (!driveLock(app, cpu, cpu.ebx, cpu.edi, kLeaveCriticalSection))
        return;
    cpu.eax = at(app, f);
    cpu.ecx = pop(app, cpu);
    leave();
}

/* 0x4e3f30: where handle eax is: the file asked unless it is mapped (an
 * error reported, 0); 0 if it is not open. */
void handlePosition(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.ebp);
    const auto leave = [&] {
        cpu.ebp = pop(app, cpu);
        cpu.esi = pop(app, cpu);
        cpu.edx = pop(app, cpu);
        cpu.ebx = pop(app, cpu);
        cpu.esp += 4;
    };
    cpu.esi = cpu.eax;
    cpu.edx = at(app, kHandles);
    cpu.esi = ~cpu.esi;
    if (cpu.edx == 0 || sreg32(cpu.esi) < 0 || sreg32(cpu.esi) >= sreg32(at(app, kHandleCount)))
    {
        cpu.eax = 0;
        return leave();
    }
    cpu.ebx = cpu.esi;
    cpu.eax = cpu.edx;
    cpu.ebx <<= kSlotShift;
    if (byte(app, cpu.ebx + cpu.eax) == 0)
    {
        cpu.eax = 0;
        return leave();
    }
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ecx);
    push(app, cpu, 0);
    if (!windows(app, cpu, kSetLastError))
        return;
    cpu.eax = at(app, kHandles);
    cpu.eax += cpu.ebx;
    cpu.edi = at(app, cpu.eax + 0x14);
    if (cpu.edi == 0)
    {
        push(app, cpu, 1);  // FILE_CURRENT
        push(app, cpu, cpu.edi);
        push(app, cpu, cpu.edi);
        cpu.ebp = at(app, cpu.eax + 4);
        push(app, cpu, cpu.ebp);
        if (!windows(app, cpu, kSetFilePointer))
            return;
        cpu.edx = at(app, kHandles);
        put(app, cpu.edx + cpu.ebx + 0x18, cpu.eax);
        if (cpu.eax == 0xffffffff)
        {
            if (!reportLastError(app, cpu, kSetFilePointerFailed))
                return;
            cpu.eax = at(app, kHandles);
            cpu.esp += 0x10;
            put(app, cpu.ebx + cpu.eax + 0x18, cpu.edi);
        }
    }
    cpu.eax = at(app, kHandles);
    cpu.esi <<= kSlotShift;
    cpu.eax = at(app, cpu.esi + cpu.eax + 0x18);
    cpu.ecx = pop(app, cpu);
    cpu.edi = pop(app, cpu);
    leave();
}

/* 0x4e3fe0: handle eax closed under its drive's lock: its mapping and view
 * (asked whatever +0x10 holds but -1), its file (but -1), its slot free.
 * 1 back, 0 if it was not open. */
void closeHandleSlot(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.ebp);
    const auto leave = [&] {
        cpu.ebp = pop(app, cpu);
        cpu.esi = pop(app, cpu);
        cpu.edx = pop(app, cpu);
        cpu.ebx = pop(app, cpu);
        cpu.esp += 4;
    };
    cpu.ebx = cpu.eax;
    cpu.edx = at(app, kHandles);
    cpu.ebx = ~cpu.ebx;
    if (cpu.edx == 0 || sreg32(cpu.ebx) < 0 || sreg32(cpu.ebx) >= sreg32(at(app, kHandleCount)))
    {
        cpu.eax = 0;
        return leave();
    }
    cpu.esi = cpu.ebx << kSlotShift;
    cpu.eax = cpu.edx + cpu.esi;
    if (byte(app, cpu.eax) == 0)
    {
        cpu.eax = 0;
        return leave();
    }
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ecx);
    cpu.edi = byte(app, cpu.eax + 1);
    if (!driveLock(app, cpu, cpu.ebp, cpu.edi, kEnterCriticalSection))
        return;
    push(app, cpu, 0);
    if (!windows(app, cpu, kSetLastError))
        return;
    cpu.eax = at(app, kHandles);
    cpu.eax += cpu.esi;
    if (at(app, cpu.eax + 0x10) != 0xffffffff)
    {
        cpu.ecx = at(app, cpu.eax + 0x14);
        push(app, cpu, cpu.ecx);
        if (!windows(app, cpu, kUnmapViewOfFile))
            return;
        cpu.eax = at(app, kHandles);
        cpu.ebp = at(app, cpu.esi + cpu.eax + 0x10);
        push(app, cpu, cpu.ebp);
        if (!windows(app, cpu, kCloseHandle))
            return;
    }
    cpu.esi = cpu.ebx;
    cpu.eax = at(app, kHandles);
    cpu.esi <<= kSlotShift;
    cpu.eax += cpu.esi;
    cpu.edx = at(app, cpu.eax + 4);
    if (cpu.edx != 0xffffffff)
    {
        push(app, cpu, cpu.edx);
        if (!windows(app, cpu, kCloseHandle))
            return;
    }
    cpu.esi = at(app, cpu.edi * 4 + kDriveLocks);
    push(app, cpu, cpu.esi);
    cpu.ebx <<= kSlotShift;
    if (!windows(app, cpu, kLeaveCriticalSection))
        return;
    cpu.eax = at(app, kHandles);
    putByte(app, cpu.ebx + cpu.eax, 0);
    cpu.eax = 1;
    cpu.ecx = pop(app, cpu);
    cpu.edi = pop(app, cpu);
    leave();
}

namespace
{

/* lockHandleDrive and unlockHandleDrive: handle eax's drive's lock entered
 * or left; 1, or 0 if it is not open. */
void handleDriveLock(win32::WinApplication* app, x86::CPU& cpu, reg32 slot)
{
    push(app, cpu, cpu.edx);
    cpu.edx = at(app, kHandles);
    cpu.eax = ~cpu.eax;
    if (cpu.edx == 0 || sreg32(cpu.eax) < 0 || sreg32(cpu.eax) >= sreg32(at(app, kHandleCount)))
    {
        cpu.eax = 0;
        cpu.edx = pop(app, cpu);
        cpu.esp += 4;
        return;
    }
    cpu.eax <<= kSlotShift;
    cpu.eax += cpu.edx;
    if (byte(app, cpu.eax) == 0)
    {
        cpu.eax = 0;
        cpu.edx = pop(app, cpu);
        cpu.esp += 4;
        return;
    }
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.ebx);
    cpu.al = byte(app, cpu.eax + 1);
    cpu.eax &= 0xff;
    if (!driveLock(app, cpu, cpu.ebx, cpu.eax, slot))
        return;
    cpu.eax = 1;
    cpu.ebx = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.esp += 4;
}

}  // namespace

/* 0x4e40a0: handle eax's drive's lock entered; 1, or 0 if it is not
 * open. */
void lockHandleDrive(win32::WinApplication* app, x86::CPU& cpu)
{
    handleDriveLock(app, cpu, kEnterCriticalSection);
}

/* 0x4e40f0: handle eax's drive's lock left; 1, or 0 if it is not open. */
void unlockHandleDrive(win32::WinApplication* app, x86::CPU& cpu)
{
    handleDriveLock(app, cpu, kLeaveCriticalSection);
}

/* 0x4e4140: edx bytes at eax taken as a file, mapped (0x800) on drive ebx
 * -- its lock made the first time -- read and written by blocks of ecx (0:
 * 0x4000), no file nor mapping (-1); its handle to the stack's word.  1 if
 * a slot was free, else 0; the word taken off. */
void openMemoryHandle(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.esp -= 4;
    const reg32 f = cpu.esp;
    cpu.edi = cpu.eax;
    cpu.ebp = cpu.edx;
    if (!direct(app, cpu, takeHandleSlot))
        return;
    cpu.edx = cpu.eax;
    cpu.esi = 0;
    if (sreg32(cpu.eax) >= 0 && sreg32(cpu.eax) < sreg32(at(app, kHandleCount)))
    {
        cpu.esi = cpu.ebx * 4;
        if (at(app, cpu.esi + kDriveLocks) == 0)
        {
            if (!byAddress(app, cpu, kNewLock))
                return;
            put(app, cpu.esi + kDriveLocks, cpu.eax);
        }
        cpu.eax = cpu.edx << kSlotShift;
        put(app, f, cpu.eax);
        cpu.esi = at(app, f);
        cpu.eax = at(app, kHandles);
        cpu.eax += cpu.esi;
        put(app, cpu.eax + 4, 0xffffffff);
        put(app, cpu.eax + 8, kMapped);
        putByte(app, cpu.eax + 1, cpu.bl);
        if (cpu.ecx == 0)
            cpu.ecx = kDefaultBlock;
        cpu.ebx = cpu.edx;
        cpu.eax = at(app, kHandles);
        cpu.ebx <<= kSlotShift;
        put(app, cpu.ebx + cpu.eax + 0x10, 0xffffffff);
        put(app, cpu.ebx + cpu.eax + 0x18, 0);
        put(app, cpu.ebx + cpu.eax + 0xc, cpu.ecx);
        put(app, cpu.ebx + cpu.eax + 0x14, cpu.edi);
        put(app, cpu.ebx + cpu.eax + 0x1c, cpu.ebp);
        cpu.edi = cpu.edx;
        cpu.eax = at(app, f + 0x14);
        cpu.edi = ~cpu.edi;
        put(app, cpu.eax, cpu.edx);
        cpu.esi = 1;
        put(app, cpu.eax, cpu.edi);
    }
    cpu.eax = cpu.esi;
    cpu.esp = f + 4;
    cpu.ebp = pop(app, cpu);
    cpu.edi = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.esp += 4 + 4;
}

/* 0x4e41f0: where handle eax is in memory (mapped, or a buffer taken as a
 * file), 0 if not -- or if it is not open. */
void handleMemory(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.edx);
    cpu.edx = at(app, kHandles);
    cpu.eax = ~cpu.eax;
    if (cpu.edx == 0 || sreg32(cpu.eax) < 0 || sreg32(cpu.eax) >= sreg32(at(app, kHandleCount)))
    {
        cpu.eax = 0;
    }
    else
    {
        cpu.edx = cpu.eax;
        cpu.eax = at(app, kHandles);
        cpu.edx <<= kSlotShift;
        cpu.eax += cpu.edx;
        cpu.eax = byte(app, cpu.eax) == 0 ? 0 : at(app, cpu.eax + 0x14);
    }
    cpu.edx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x501010: on the main thread, with the check on ([0x564364]) and a
 * surface locked, an Error naming function eax -- files are not to be
 * touched then -- and 0; else 1. */
void checkSurfaceUnlocked(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    const auto leave = [&] {
        cpu.eax = cpu.edx;
        cpu.edx = pop(app, cpu);
        cpu.ecx = pop(app, cpu);
        cpu.esp += 4;
    };
    cpu.ecx = cpu.eax;
    cpu.eax = 0;
    cpu.edx = 1;
    if (!byAddress(app, cpu, kOnMainThread))
        return;
    if (cpu.eax == 0 || at(app, kSurfaceCheck) == 0)
        return leave();
    if (!byAddress(app, cpu, kSurfaceLockedNow))
        return;
    if (cpu.eax == 0)
        return leave();
    push(app, cpu, cpu.ecx);
    push(app, cpu, kSurfaceLocked);
    cpu.edx = 0;
    if (!byAddress(app, cpu, kError))
        return;
    cpu.esp += 8;
    leave();
}

/* 0x501050: cdecl (level's threshold, level, format, ...): EA's report --
 * unless the level is above the threshold's -- formatted (1K at most) and
 * sent the way [0x56789c] says: 1 OutputDebugString, 2 printed (Message as
 * its format, stdout flushed), 3 the game's log; anything else nowhere. */
void fileReport(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    cpu.esp -= 0x404;
    const reg32 f = cpu.esp;
    const auto leave = [&] {
        cpu.esp = f + 0x404;
        cpu.edx = pop(app, cpu);
        cpu.ecx = pop(app, cpu);
        cpu.ebx = pop(app, cpu);
        cpu.esp += 4;
    };
    cpu.eax = at(app, f + 0x414);
    if (cpu.eax != 0)
    {
        cpu.edx = at(app, f + 0x418);
        if (sreg32(cpu.edx) > sreg32(at(app, cpu.eax)))
            return leave();
    }
    cpu.eax = f + 0x420;
    cpu.ebx = f + 0x400;
    cpu.edx = at(app, f + 0x41c);
    put(app, f + 0x400, cpu.eax);
    cpu.eax = f;
    cpu.ecx = 0;
    if (!byAddress(app, cpu, kVsprintf))
        return;
    cpu.eax = at(app, kReportOutput);
    put(app, f + 0x400, cpu.ecx);
    if (cpu.eax < 2)
    {
        if (cpu.eax != 1)
            return leave();
        cpu.eax = f;
        push(app, cpu, cpu.eax);
        if (!windows(app, cpu, kOutputDebugStringA))
            return;
        return leave();
    }
    if (cpu.eax == 2)
    {
        cpu.eax = f;
        push(app, cpu, cpu.eax);
        if (!byAddress(app, cpu, kMessage))
            return;
        cpu.esp += 4;
        cpu.eax = kStdout;
        if (!byAddress(app, cpu, kFflush))
            return;
        return leave();
    }
    if (cpu.eax != 3)
        return leave();
    cpu.eax = f;
    push(app, cpu, cpu.eax);
    if (!byAddress(app, cpu, kTrace))
        return;
    cpu.esp += 4;
    leave();
}

/* 0x501110: Windows' pages for the bytes [eax] -- rounded up to whole pages
 * there (the page's size asked of Windows the first time) -- committed, read
 * and written; their address, or 0. */
void virtualAllocPages(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    cpu.esp -= 0x24;
    const reg32 f = cpu.esp;
    cpu.ebx = cpu.eax;
    cpu.edx = at(app, kPageSize);
    cpu.esi = 0;
    cpu.edi = 0;
    if (cpu.edx == 0)
    {
        cpu.eax = f;
        push(app, cpu, cpu.eax);
        if (!windows(app, cpu, kGetSystemInfo))
            return;
        cpu.eax = at(app, f + 4);
        put(app, kPageSize, cpu.eax);
    }
    cpu.ecx = at(app, kPageSize);
    cpu.edx = at(app, cpu.ebx);
    cpu.edx += cpu.ecx;
    --cpu.edx;
    cpu.eax = cpu.edx;
    idivide(cpu, cpu.ecx);
    cpu.eax *= cpu.ecx;
    push(app, cpu, 4);       // PAGE_READWRITE
    push(app, cpu, 0x3000);  // MEM_COMMIT | MEM_RESERVE
    put(app, cpu.ebx, cpu.eax);
    cpu.eax += cpu.esi;
    push(app, cpu, cpu.eax);
    push(app, cpu, 0);
    if (!windows(app, cpu, kVirtualAlloc))
        return;
    cpu.eax += cpu.edi;
    cpu.esp = f + 0x24;
    cpu.edi = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x501180: Windows' pages at eax given back (MEM_RELEASE); ecx and edx
 * kept. */
void virtualFreePages(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, 0x8000);
    push(app, cpu, 0);
    push(app, cpu, cpu.eax);
    if (!windows(app, cpu, kVirtualFree))
        return;
    cpu.edx = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x5011a0, EA's touchmempages: the pages of edx bytes from eax -- no more
 * than the memory there is ([0x5678a4], asked of the game the first time)
 * -- gone over to have them in memory; its loops count, but touch nothing.
 * An Error if the page's size is not known yet (initmemman not called). */
void touchMemoryPages(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.esp -= 4;
    const reg32 f = cpu.esp;
    cpu.esi = at(app, kPageSize);
    cpu.ecx = cpu.eax;
    if (cpu.esi == 0)
    {
        cpu.ebx = kTouchmemC;
        cpu.edi = kTouchMemPagesName;
        cpu.ebp = 0x32;
        push(app, cpu, kTouchMemFirst);
        where(app, cpu.ebx, cpu.edi, cpu.ebp);
        if (!byAddress(app, cpu, kError))
            return;
        cpu.esp += 4;
    }
    if (at(app, kPhysicalMemory) == 0)
    {
        if (!byAddress(app, cpu, kPhysicalMemorySize))
            return;
        put(app, kPhysicalMemory, cpu.eax);
    }
    cpu.ebx = at(app, kPhysicalMemory);
    cpu.esi = at(app, kPageSize);
    if (sreg32(cpu.edx) > sreg32(cpu.ebx))
        cpu.edx = cpu.ebx;
    if (sreg32(cpu.edx) >= sreg32(cpu.esi))
    {
        cpu.ebx = cpu.ecx + cpu.esi - 1;
        cpu.eax = cpu.esi - 1;
        cpu.edi = ~cpu.eax;
        cpu.ebx &= cpu.edi;
        cpu.edi = cpu.ebx - cpu.ecx;
        cpu.edx -= cpu.edi;
        cpu.edx += cpu.eax;
        cpu.eax = cpu.edx;
        idivide(cpu, cpu.esi);
        cpu.edi = 0;
        put(app, f, cpu.eax);
        if (sreg32(cpu.eax) > 0)
        {
            do
            {
                cpu.edx = cpu.ebx;
                cpu.eax = 0;
                if (cpu.ebx >= cpu.ecx)
                {
                    do
                    {
                        ++cpu.eax;
                        cpu.edx -= cpu.esi;
                    } while (sreg32(cpu.eax) < 0x20 && cpu.edx >= cpu.ecx);
                }
                cpu.eax = at(app, f);
                ++cpu.edi;
                cpu.ebx += cpu.esi;
            } while (sreg32(cpu.edi) < sreg32(cpu.eax));
        }
    }
    put(app, kPageSize, cpu.esi);
    cpu.esp = f + 4;
    cpu.ebp = pop(app, cpu);
    cpu.edi = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x501270, EA's openblockhandle: the file named eax opened to read
 * (0x205), its handle to [edx], its block to the stack's word, its length to
 * [ecx] and 0 to [ebx].  1 if opened, else 0 -- an Error with [0x56440c]
 * set; the word taken off. */
void openBlockHandle(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.esp -= 4;
    const reg32 f = cpu.esp;
    const auto leave = [&](reg32 result) {
        cpu.eax = result;
        cpu.esp = f + 4;
        cpu.ebp = pop(app, cpu);
        cpu.edi = pop(app, cpu);
        cpu.esi = pop(app, cpu);
        cpu.esp += 4 + 4;
    };
    cpu.edi = cpu.eax;
    cpu.esi = cpu.edx;
    put(app, f, cpu.ebx);
    cpu.ebp = cpu.ecx;
    cpu.ecx = cpu.edx;
    cpu.ebx = 0;
    cpu.edx = kOpenFlags;
    if (!direct(app, cpu, openFileHandle))
        return;
    if (cpu.eax == 0)
    {
        if (at(app, kErrorsFatal) != 0)
        {
            cpu.edx = kBlockioC;
            push(app, cpu, cpu.edi);
            cpu.ecx = kOpenBlockHandleName;
            cpu.ebx = 0x52;
            push(app, cpu, kBlockOpenFailed);
            where(app, cpu.edx, cpu.ecx, cpu.ebx);
            if (!byAddress(app, cpu, kError))
                return;
            cpu.esp += 8;
        }
        put(app, cpu.esi, 0);
        return leave(0);
    }
    push(app, cpu, 0);
    cpu.ebx = at(app, f + 0x14);
    cpu.ecx = cpu.ebp;
    cpu.eax = at(app, cpu.esi);
    cpu.edx = 0;
    if (!direct(app, cpu, handleInfo))
        return;
    if (cpu.eax != 0)
    {
        cpu.eax = at(app, f);
        put(app, cpu.eax, 0);
        return leave(1);
    }
    if (at(app, kErrorsFatal) != 0)
    {
        cpu.ecx = kBlockioC;
        push(app, cpu, cpu.edi);
        cpu.ebx = kOpenBlockHandleName;
        cpu.ebp = 0x58;
        push(app, cpu, kBlockInfoFailed);
        where(app, cpu.ecx, cpu.ebx, cpu.ebp);
        if (!byAddress(app, cpu, kError))
            return;
        cpu.esp += 8;
    }
    cpu.eax = at(app, cpu.esi);
    if (!direct(app, cpu, closeHandleSlot))
        return;
    put(app, cpu.esi, 0);
    leave(0);
}

/* 0x501360, EA's blockhandlefile: not supported -- an Error, and 0.  No
 * caller in the game. */
void blockHandleFile(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    cpu.edx = kBlockioC;
    cpu.ecx = kBlockHandleFileName;
    cpu.ebx = 0x66;
    push(app, cpu, kBlockFileUnsupported);
    where(app, cpu.edx, cpu.ecx, cpu.ebx);
    if (!byAddress(app, cpu, kError))
        return;
    cpu.esp += 4;
    cpu.eax = 0;
    cpu.edx = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x5013a0, EA's closeblockhandle: closeHandleSlot, jumped to. */
void closeBlockHandle(win32::WinApplication* app, x86::CPU& cpu)
{
    closeHandleSlot(app, cpu);
}

/* 0x5013b0, EA's readblockhandle: ebx blocks of handle eax read to edx
 * (readHandleBytes); the bytes read back, 0 if the handle tells nothing
 * (an Error with [0x56440c] set). */
void readBlockHandle(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.esp -= 8;
    const reg32 f = cpu.esp;
    const auto leave = [&] {
        cpu.eax = cpu.edi;
        cpu.esp = f + 8;
        cpu.ebp = pop(app, cpu);
        cpu.edi = pop(app, cpu);
        cpu.esi = pop(app, cpu);
        cpu.ecx = pop(app, cpu);
        cpu.esp += 4;
    };
    cpu.esi = cpu.eax;
    put(app, f + 4, cpu.edx);
    cpu.ebp = cpu.ebx;
    cpu.edi = 0;
    cpu.ebx = f;
    push(app, cpu, cpu.edi);
    cpu.ecx = 0;
    cpu.edx = 0;
    if (!direct(app, cpu, handleInfo))
        return;
    if (cpu.eax == 0)
    {
        if (at(app, kErrorsFatal) != 0)
        {
            cpu.ecx = kBlockioC;
            cpu.ebx = kReadBlockHandleName;
            cpu.esi = 0xd6;
            push(app, cpu, kBlockReadFailed);
            where(app, cpu.ecx, cpu.ebx, cpu.esi);
            if (!byAddress(app, cpu, kError))
                return;
            cpu.esp += 4;
        }
        return leave();
    }
    cpu.ebx = at(app, f);
    cpu.ebx *= cpu.ebp;
    cpu.edx = at(app, f + 4);
    cpu.eax = cpu.esi;
    if (!direct(app, cpu, readHandleBytes))
        return;
    cpu.edx = at(app, kErrorsFatal);
    cpu.edi = cpu.eax;
    leave();
}

/* 0x501450, EA's seekblockhandle: handle eax sought to edx (seekHandleTo)
 * -- an Error if it is not open -- and where it is back (handlePosition).  No
 * caller in the game. */
void seekBlockHandle(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ecx);
    cpu.ecx = cpu.eax;
    if (!direct(app, cpu, seekHandleTo))
        return;
    if (cpu.eax == 0)
    {
        push(app, cpu, cpu.esi);
        push(app, cpu, cpu.ebx);
        cpu.edx = kBlockioC;
        cpu.ebx = kSeekBlockHandleName;
        cpu.esi = 0x115;
        push(app, cpu, kBlockSeekFailed);
        where(app, cpu.edx, cpu.ebx, cpu.esi);
        if (!byAddress(app, cpu, kError))
            return;
        cpu.esp += 4;
        cpu.ebx = pop(app, cpu);
        cpu.esi = pop(app, cpu);
    }
    cpu.eax = cpu.ecx;
    if (!direct(app, cpu, handlePosition))
        return;
    cpu.ecx = pop(app, cpu);
    cpu.esp += 4;
}

}  // namespace ea
}  // namespace nfs3hp
