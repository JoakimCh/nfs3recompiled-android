/* src/nfs3hp/native_game.cpp against the game's generated code, on the
 * desktop, without the game.
 *
 * The game's code for the natives is made afresh from nfs3hp/nfs3.exe by the
 * port's own generator, without the hooks of the tree's copy (generate.py),
 * and built with the port's headers.  Two guest memories hold the same state:
 * the game's data as it loads, what the natives read and write of it made up
 * for every case, buffers, and the stack.  A function runs generated on one
 * and natively on the other, and then they are compared: every call out in
 * order -- the game's own functions, Win32's through its imports, eacsnd's and
 * the renderer's through the pointers the game keeps, the game's callbacks --
 * with what it was handed (its registers and stack words, and what a pointer
 * into the caller's frame points at); the registers the function's caller
 * counts on (kPromises), and eax where it gives something back; the MMX
 * registers; and every byte the functions touch, the stack from the arguments
 * up.  The stack below them
 * is the functions' own and nobody else's.  Every so often all of both
 * memories are compared, for a write anywhere else.
 *
 * What is called is a stand-in, the same for both runs, which keeps to the
 * real one's convention -- Watcom's, which keeps every register but eax and
 * those it is handed an argument in, cdecl or stdcall, which may leave eax,
 * ecx and edx -- and changes what it may, now and then, as
 * the real one might.  The stand-ins' results come from the case's seed and
 * the call's place in the case, the same for both runs as long as both make
 * the same calls; a case may pick a call that stops the game (cpu.terminate),
 * and from there on neither run may do anything.  The functions under test
 * call each other as they do, generated on one side and native on the other.
 *
 * See run.sh. */
#include "nfs3hp.h"
#include <lib/memmap.h>
#include <SDL3/SDL.h>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <random>
#include <string>
#include <vector>
#include <sys/mman.h>

namespace x86
{
void assertLog(const char* file, int line, const char* expr)
{
    std::printf("assert %s:%d %s\n", file, line, expr);
}
}

/* What src/lib/cpu.cpp wants of SDL. */
extern "C"
{
Uint64 SDL_GetPerformanceCounter(void) { return 0; }
Uint64 SDL_GetPerformanceFrequency(void) { return 1; }
const char* SDL_getenv(const char* name) { return std::getenv(name); }
int SDL_strcmp(const char* a, const char* b) { return std::strcmp(a, b); }
}

struct GameSegment
{
    x86::reg32 address, length;
    const x86::reg8* bytes;
};
extern const GameSegment kGameSegments[];
extern const unsigned kGameSegmentCount;

namespace nfs3hp
{
/* native_vertices.cpp's [COMM] trace, which Error calls first: nothing here. */
void commMessageTrace(win32::WinApplication*, x86::CPU&) {}
}

namespace
{

constexpr x86::reg32 kMemory = 0x1000000;

/* Where things are, in both memories. */
constexpr x86::reg32 kLow = 0, kLowEnd = 0x10000;              // where a null buffer is written
constexpr x86::reg32 kHeap = 0x100000, kHeapEnd = 0x200000;    // VirtualAlloc's: 8 slots
constexpr x86::reg32 kSlotSize = 0x20000;
constexpr x86::reg32 kHarness = 0x600000, kHarnessEnd = 0x640000;
constexpr x86::reg32 kStrings = 0x600000;      // 64 strings of 0x40 bytes
constexpr x86::reg32 kElements = 0x602000;     // qsort's and bsearch's: up to 0xd000 bytes
constexpr x86::reg32 kKey = 0x60f000;          // bsearch's key
constexpr x86::reg32 kAboutRecord = 0x610000;  // what THRASH_about hands back
constexpr x86::reg32 kSamples = 0x620000;      // iSNDconvertsample's source and destination
constexpr x86::reg32 kTexts = 0x634000;        // the string functions': 32 strings of 0x100, in pairs
constexpr x86::reg32 kBuffers = 0x636000;      // what they write: 16 of 0x200
constexpr x86::reg32 kThread = 0x63c000;       // the runtime's per-thread data
constexpr x86::reg32 kSlotsTaken = 0x63e000;   // VirtualAlloc's slots in use, a bit each
constexpr x86::reg32 kHandleTable = 0x63e100;  // the runtime's handles' HANDLEs: 32 of them
constexpr x86::reg32 kGrownTable = 0x63e200;   // where _nrealloc moves them to
constexpr x86::reg32 kStreams = 0x638000;      // 8 of 0x40: a FILE, its __stream_link at +0x20
constexpr x86::reg32 kIobLinks = 0x638200;     // __iob's first three's links, 0x20 each
constexpr x86::reg32 kStreamBuffers = 0x639000;  // the 11's buffers, 0x400 each
constexpr x86::reg32 kStackLow = 0xef0000, kStackHigh = 0xf00000;
/* The MMX functions' (native_mmx.cpp), in kSamples: what they read, what they
 * write -- the accumulator, the output -- with room before each for what
 * their loops' ends reach back to; their volumes, positions and decoders'
 * states. */
constexpr x86::reg32 kMmxSource = kSamples + 0x200, kMmxTarget = kSamples + 0x4200;
constexpr x86::reg32 kMmxOutput = kSamples + 0x8200, kMmxState = kSamples + 0xc000;

/* The game's, as native_game.cpp names them. */
constexpr x86::reg32 kWhere = 0x552190, kCalledFrom = 0x55219c, kErrorUnderWay = 0x5521a8;
constexpr x86::reg32 kDebugStop = 0x55e8c0;
constexpr x86::reg32 kErrorPrintOk = 0x564400, kErrorOk = 0x564404, kErrorWhere = 0x564408;
constexpr x86::reg32 kRendererIs3dfx = 0x564410, kErrorFilter = 0x564414, kErrorLock = 0x564418;
constexpr x86::reg32 kErrorBefore = 0x56441c, kDebugOutput = 0x5643fc, kRendererModule = 0x564a6c;
constexpr x86::reg32 kErrorText = 0x56e010;
constexpr x86::reg32 kSoundModule = 0x9ef600, kSoundOptions = 0x9ef608, kSoundFunctions = 0x9ef61c;
constexpr x86::reg32 kWindow = 0x9f3d24, kSoundLock = 0xa09b04, kSoundTick = 0xa09b08;
constexpr x86::reg32 kThrashSlots = 0x9ef900, kThrashSlotsEnd = 0x9ef988;
constexpr x86::reg32 kThreadData = 0x9f642c;  // the Watcom runtime's: its single thread's data
constexpr x86::reg32 kXaNibbles = 0xa0bea0;   // the XA decoders' nibbles, shifted: 16 dwords for each shift

/* The runtime's near heap, as native_watcom_heap.cpp has it (kGameHeap). */
constexpr x86::reg32 kHeapFirst = 0x566f4c, kHeapRover = 0x566f50, kHeapLargestBefore = 0x566f54;
constexpr x86::reg32 kHeapFreeRover = 0x9f3800, kHeapClean = 0xa0b140;
constexpr x86::reg32 kHeapEnabled = 0x56af68, kHeapBrk = 0x5677f8, kHeapBlockSize = 0x56af6c;
constexpr x86::reg32 kHeapAccess = 0x567780, kHeapRelease = 0x567788;
constexpr x86::reg32 kNullAccess = 0x4ff0f4;  // __NullAccessRtn: the lock while there is one thread

/* The runtime's handles, as native_watcom.cpp has them: __OSHandles,
 * __NFiles, __io_mode and the game's 20 modes it points at; the file's lock;
 * the default windowing's hooks. */
constexpr x86::reg32 kOsHandles = 0x56acbc, kFileCount = 0x56ad94, kIoModes = 0x56ade8, kGameIoModes = 0x56ad98;
constexpr x86::reg32 kAccessFile = 0x567768, kReleaseFile = 0x56776c;
constexpr x86::reg32 kIsWindowedHandle = 0x5677b0, kWindowsStdin = 0x5677d8, kWindowsStdout = 0x5677dc;

/* The runtime's streams, as native_watcom.cpp has them: __OpenStreams, their
 * links' list; the streams' lock; __iob, stdin, stdout and stderr first. */
constexpr x86::reg32 kOpenStreams = 0x9f38a0, kAccessIob = 0x567778, kReleaseIob = 0x56777c;
constexpr x86::reg32 kIob = 0x566f58;  // 0x1a bytes each
constexpr x86::reg32 kClosedStreams = 0x9f38a4;
/* Opening and closing's: __NHandles and __NTGetFakeHandle's last; what
 * calls __allocPOSIXHandle and __freePOSIXHandle, and the handles' lock; the
 * default windowing's other hooks; _commode, _fmode, the umask. */
constexpr x86::reg32 kHandleCount = 0x56acc0, kFakeHandle = 0x56acc4;
constexpr x86::reg32 kAllocHandle = 0x567770, kFreeHandle = 0x567774;
constexpr x86::reg32 kAccessHandles = 0x567798, kReleaseHandles = 0x56779c;
constexpr x86::reg32 kRemoveWindowedHandle = 0x5677b4, kNewWindow = 0x5677b8, kDestroyWindow = 0x5677bc;
constexpr x86::reg32 kCommitMode = 0x568260, kFileMode = 0x567164, kUmask = 0x56ae60;

/* The runtime's time zone, as native_watcom.cpp has it: timezone,
 * __dst_adjust, tzname[1] and daylight saving's rules, a struct tm each. */
constexpr x86::reg32 kTimezone = 0x568b94, kDstAdjust = 0x568b9c, kDstName = 0x568b90;
constexpr x86::reg32 kDstStart = 0x568a40, kDstEnd = 0x568a64;

/* The functions qsort and bsearch are handed: stand-ins (kPointers) by where
 * none of the game's are. */
constexpr x86::reg32 kByDword = 0xfff000, kByByte = 0xfff004, kAtRandom = 0xfff008;

/* What the functions write, and the stack from the arguments up: compared. */
const std::pair<x86::reg32, x86::reg32> kWindows[] = {
    {kLow, kLowEnd}, {kHeap, kHeapEnd}, {kHarness, kHarnessEnd}, {0x552000, 0x553000}, {0x55e000, 0x55f000},
    {0x564000, 0x565000}, {0x566000, 0x568000}, {0x568000, 0x569000}, {0x56a000, 0x56b000}, {0x56e000, 0x56f000},
    {0x9ef000, 0x9f0000},
    {0x9f3000, 0x9f4000}, {0x9f6000, 0x9f7000}, {0xa09000, 0xa0a000}, {0xa0b000, 0xa0d000}, {kStackLow, kStackHigh},
};

/* The stand-ins' own addresses, for what is called through a pointer. */
constexpr x86::reg32 kStandIns = 0xe00000;  // + 0x10 each of kPointers
constexpr x86::reg32 kNamed = 0xe80000;     // + 0x10 each name GetProcAddress was asked for

enum Convention
{
    kWatcom,   // register arguments; every register kept but those of `clobbers`
    kCdecl,    // arguments on the stack, left there
    kStdcall,  // arguments on the stack, taken off
};

enum Register : unsigned
{
    kEax = 1, kEcx = 2, kEdx = 4, kEbx = 8,
};
constexpr unsigned kScratch = kEax | kEcx | kEdx;

enum Effect
{
    kNothing,
    kText,          // vsprintf: text at eax, its length back
    kPrint,         // sprintf: text at its first argument, its length back
    kLoad,          // LoadLibraryA: a module, or none
    kLookUp,        // GetProcAddress: a stand-in by name, or none
    kVersion,       // iSNDdllversion: 16.3 mostly
    kAbout,         // THRASH_about: kAboutRecord, or none
    kBox,           // MessageBoxA: OK or Cancel
    kMainThread,    // whether this is the main thread
    kAllocate,      // VirtualAlloc: a free slot, filled with samples, or none
    kFree,          // VirtualFree: a slot VirtualAlloc gave, free again
    kDecode,        // a decoder: samples into the buffer
    kFilter,        // the game's say on an error: now and then 0
    kLock,          // the game's lock: a critical section, or none
    kCompare,       // a comparison of qsort's or bsearch's: by kByDword, kByByte or kAtRandom
    kSucceed,       // a Windows function's BOOL: now and then FALSE
    kLastError,     // GetLastError: an error the runtime turns into errno one way or another
    kAttributes,    // GetFileAttributesA: a file's attributes, or -1
    kDirectory,     // GetCurrentDirectoryA: a path into the buffer, if it fits, and its length
    kDiskFree,      // GetDiskFreeSpaceA: its four dwords, or FALSE
    kFind,          // FindFirstFileA: WIN32_FIND_DATA, its attributes first, or -1
    kSeek,          // SetFilePointer: a place, or -1
    kRead,          // ReadFile: bytes into the buffer, and how many; or FALSE
    kWrite,         // WriteFile: how many, all of them mostly; or FALSE
    kFileType,      // GetFileType: unknown, disk, character or pipe
    kWindowed,      // _WindowsIsWindowedHandle: a window, or none
    kTransfer,      // _WindowsStdin and _WindowsStdout: how many, -1 now and then
    kLocalTime,     // GetLocalTime: a SYSTEMTIME, sensible mostly
    kZone,          // __tzset: the zone as it was, or another
    kMathResult,    // __reporterror: what _matherr gives back, onto the x87's stack
    kCharacter,     // getche: a byte, or -1
    kOpenFile,      // CreateFileA: a HANDLE, or -1
    kEvent,         // CreateEventA: a HANDLE, or 0
    kHandle,        // __allocPOSIXHandle: a handle -- of the 20 mostly, past them, -1
    kReallocate,    // _nrealloc: the handles' table moved, or 0
    kTmpName,       // __MkTmpFile: a name into the buffer
};

struct StandIn
{
    x86::reg32 address;
    const char* name;
    Convention convention;
    unsigned registers;  // how many of eax, edx, ebx, ecx it takes
    unsigned words;      // stack words it takes
    unsigned clobbers;   // registers it may leave otherwise
    int through;         // where the words of `deref` are read: a register (0-3) or 4 + a stack word, -1 none
    unsigned deref;      // how many
    Effect effect;
    /* It formats: the format in edx and a va_list's address in ebx (1), or
     * the format on the stack and its arguments after it (2).  The arguments
     * the format takes, as many words as it has conversions, are logged too. */
    int formats = 0;
};

/* The game's own functions the code under test calls. */
const StandIn kGameFunctions[] = {
    {0x4df674, "vsprintf", kWatcom, 3, 0, kEax | kEdx | kEbx, 2, 1, kText, 1},
    {0x4df690, "sprintf", kCdecl, 0, 5, kScratch, -1, 0, kPrint},
    {0x4ff014, "vfprintf", kWatcom, 3, 0, kEax | kEdx | kEbx, 2, 1, kNothing, 1},
    {0x4df930, "main thread", kWatcom, 1, 0, kEax, -1, 0, kMainThread},
    {0x4dfd04, "exit", kWatcom, 1, 0, kEax, -1, 0, kNothing},
    {0x4ffb64, "stop buffer", kWatcom, 1, 0, kEax, -1, 0, kNothing},
    {0x4ffce0, "buffer position", kWatcom, 3, 0, kEax | kEdx | kEbx, -1, 0, kNothing},
    {0x500864, "mix", kWatcom, 2, 0, kEax | kEdx, -1, 0, kNothing},
    {0x4e08f0, "trace", kCdecl, 0, 2, kScratch, -1, 0, kNothing, 2},
    {0x5008a0, "8 bits", kCdecl, 0, 3, kScratch, -1, 0, kDecode},
    {0x500b10, "16 bits", kCdecl, 0, 3, kScratch, -1, 0, kDecode},
    {0x500990, "XA, two channels", kCdecl, 0, 1, kScratch, 4, 7, kDecode},
    {0x500b90, "XA, one channel", kCdecl, 0, 1, kScratch, 4, 5, kDecode},
    {0x500910, "into the destination", kCdecl, 0, 3, kScratch, -1, 0, kNothing},
    {0x500c80, "the game's tick", kWatcom, 0, 0, kEax, -1, 0, kNothing},
    {0x515c2c, "__tzset", kWatcom, 0, 0, 0, -1, 0, kZone},
    {0x5243a7, "__reporterror", kWatcom, 2, 0, kEax | kEdx, 1, 2, kMathResult},  // the argument, a double
    {0x522e60, "getche", kWatcom, 0, 0, kEax, -1, 0, kCharacter},
    {0x5185c0, "_nrealloc", kWatcom, 2, 0, kEax | kEdx, -1, 0, kReallocate},
    {0x4ee168, "__MkTmpFile", kWatcom, 2, 0, kEax | kEdx, -1, 0, kTmpName},
};

/* What is called through a pointer: the game's imports, by their slots, and
 * its callbacks. */
const StandIn kPointers[] = {
    {0x534488, "CloseHandle", kStdcall, 0, 1, kScratch, -1, 0, kSucceed},
    {0x534490, "CreateDirectoryA", kStdcall, 0, 2, kScratch, -1, 0, kSucceed},
    {0x534494, "CreateEventA", kStdcall, 0, 4, kScratch, -1, 0, kEvent},
    {0x534498, "CreateFileA", kStdcall, 0, 7, kScratch, 7, 3, kOpenFile},  // its SECURITY_ATTRIBUTES
    {0x5344a8, "DebugBreak", kStdcall, 0, 0, kScratch, -1, 0, kNothing},
    {0x5344b0, "DeleteFileA", kStdcall, 0, 1, kScratch, -1, 0, kSucceed},
    {0x5344b8, "EnterCriticalSection", kStdcall, 0, 1, kScratch, -1, 0, kNothing},
    {0x5344c0, "ExitProcess", kStdcall, 0, 1, kScratch, -1, 0, kNothing},
    {0x5344cc, "FindFirstFileA", kStdcall, 0, 2, kScratch, -1, 0, kFind},
    {0x5344d4, "FlushFileBuffers", kStdcall, 0, 1, kScratch, -1, 0, kSucceed},
    {0x534500, "GetCurrentDirectoryA", kStdcall, 0, 2, kScratch, -1, 0, kDirectory},
    {0x534514, "GetDiskFreeSpaceA", kStdcall, 0, 5, kScratch, 4, 1, kDiskFree},  // the root's "X:\\"
    {0x534520, "GetFileAttributesA", kStdcall, 0, 1, kScratch, -1, 0, kAttributes},
    {0x53452c, "GetFileType", kStdcall, 0, 1, kScratch, -1, 0, kFileType},
    {0x534534, "GetLastError", kStdcall, 0, 0, kScratch, -1, 0, kLastError},
    {0x534538, "GetLocalTime", kStdcall, 0, 1, kScratch, -1, 0, kLocalTime},
    {0x534558, "GetProcAddress", kStdcall, 0, 2, kScratch, -1, 0, kLookUp},
    {0x534588, "LeaveCriticalSection", kStdcall, 0, 1, kScratch, -1, 0, kNothing},
    {0x53458c, "LoadLibraryA", kStdcall, 0, 1, kScratch, -1, 0, kLoad},
    {0x53459c, "OutputDebugStringA", kStdcall, 0, 1, kScratch, -1, 0, kNothing},
    {0x5345b0, "ReadFile", kStdcall, 0, 5, kScratch, -1, 0, kRead},
    {0x5345b4, "RemoveDirectoryA", kStdcall, 0, 1, kScratch, -1, 0, kSucceed},
    {0x5345d4, "SetCurrentDirectoryA", kStdcall, 0, 1, kScratch, -1, 0, kSucceed},
    {0x5345ec, "SetFileAttributesA", kStdcall, 0, 2, kScratch, -1, 0, kSucceed},
    {0x5345f0, "SetFilePointer", kStdcall, 0, 4, kScratch, -1, 0, kSeek},
    {0x534624, "VirtualAlloc", kStdcall, 0, 4, kScratch, -1, 0, kAllocate},
    {0x534628, "VirtualFree", kStdcall, 0, 3, kScratch, -1, 0, kFree},
    {0x534640, "WriteFile", kStdcall, 0, 5, kScratch, -1, 0, kWrite},
    {0x534764, "MessageBoxA", kStdcall, 0, 4, kScratch, -1, 0, kBox},
    {0x534794, "ShowCursor", kStdcall, 0, 1, kScratch, -1, 0, kNothing},
    {kErrorFilter, "the error filter", kWatcom, 1, 0, kScratch, -1, 0, kFilter},
    {kErrorLock, "the error lock", kWatcom, 0, 0, kScratch, -1, 0, kLock},
    {kErrorBefore, "before the box", kWatcom, 0, 0, kScratch, -1, 0, kNothing},
    {kErrorOk, "OK pressed", kWatcom, 0, 0, kScratch, -1, 0, kNothing},
    {kSoundTick, "a tick of the game's", kWatcom, 0, 0, kScratch, -1, 0, kNothing},
    {kHeapAccess, "the heap's lock taken", kWatcom, 0, 0, 0, -1, 0, kNothing},
    {kHeapRelease, "the heap's lock given back", kWatcom, 0, 0, 0, -1, 0, kNothing},
    {kAccessFile, "the file's lock taken", kWatcom, 1, 0, 0, -1, 0, kNothing},
    {kReleaseFile, "the file's lock given back", kWatcom, 1, 0, 0, -1, 0, kNothing},
    {kAccessIob, "the streams' lock taken", kWatcom, 1, 0, 0, -1, 0, kNothing},
    {kReleaseIob, "the streams' lock given back", kWatcom, 1, 0, 0, -1, 0, kNothing},
    {kAccessHandles, "the handles' lock taken", kWatcom, 1, 0, 0, -1, 0, kNothing},
    {kReleaseHandles, "the handles' lock given back", kWatcom, 1, 0, 0, -1, 0, kNothing},
    {kAllocHandle, "__allocPOSIXHandle", kWatcom, 1, 0, kEax, -1, 0, kHandle},
    {kFreeHandle, "__freePOSIXHandle", kWatcom, 1, 0, kEax, -1, 0, kNothing},
    {kRemoveWindowedHandle, "_WindowsRemoveWindowedHandle", kWatcom, 1, 0, kEax, -1, 0, kNothing},
    {kNewWindow, "_WindowsNewWindow", kCdecl, 4, 3, 0, -1, 0, kNothing},
    {kDestroyWindow, "_WindowsCloseWindow", kWatcom, 1, 0, kEax, -1, 0, kNothing},
    {kIsWindowedHandle, "_WindowsIsWindowedHandle", kWatcom, 1, 0, kEax, -1, 0, kWindowed},
    {kWindowsStdin, "_WindowsStdin", kWatcom, 3, 0, kEax | kEdx | kEbx, -1, 0, kTransfer},
    {kWindowsStdout, "_WindowsStdout", kWatcom, 3, 0, kEax | kEdx | kEbx, -1, 0, kTransfer},
    {kByDword, "compared by dwords", kWatcom, 2, 0, kEax | kEdx, -1, 0, kCompare},
    {kByByte, "compared by bytes", kWatcom, 2, 0, kEax | kEdx, -1, 0, kCompare},
    {kAtRandom, "compared at random", kWatcom, 2, 0, kEax | kEdx, -1, 0, kCompare},
};
constexpr unsigned kPointerCount = sizeof kPointers / sizeof kPointers[0];

x86::reg32 standInFor(x86::reg32 slot)
{
    for (unsigned i = 0; i < kPointerCount; ++i)
        if (kPointers[i].address == slot)
            return kStandIns + 0x10 * i;
    std::abort();
}

/* The names GetProcAddress was asked for, in the order first asked: stdcall
 * stand-ins, their words from the name's @. */
std::vector<std::string> g_names;

x86::reg32 namedStandIn(const std::string& name)
{
    auto found = std::find(g_names.begin(), g_names.end(), name);
    if (found == g_names.end())
        found = g_names.insert(g_names.end(), name);
    return kNamed + 0x10 * x86::reg32(found - g_names.begin());
}

struct Call
{
    x86::reg32 id;
    std::vector<x86::reg32> words;
    bool operator==(const Call& o) const { return id == o.id && words == o.words; }
};

/* The case: its seed, the call the game stops at, if any, and whether
 * GetProcAddress may not find a name. */
std::uint64_t g_seed = 0;
long g_stopAt = -1;
bool g_lookupFails = false;

std::uint64_t mix(std::uint64_t x)
{
    x += 0x9e3779b97f4a7c15ull;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ull;
    x = (x ^ (x >> 27)) * 0x94d049bb133111ebull;
    return x ^ (x >> 31);
}

typedef void (*Function)(win32::WinApplication*, x86::CPU&);

struct Tested
{
    x86::reg32 address;
    const char* name;
    Function generated;
    Function native;
};

const Tested kTested[] = {
#include "game_tested.inc"
};

/* What the runtime's heap is to a function's cases. */
enum HeapUse
{
    kNoHeap,
    kStirred,   // the runtime's heap stirred before each case (stirHeap)
    kRestored,  // and its list as it was after: what it leaves is not what the game would
};

/* What each function promises its caller of the registers, and so what is
 * compared: the game's own callers are Watcom code, which counts on every
 * register it handed no argument in -- of these functions' registers, all
 * but eax; eacsnd calls the lambdas stdcall or cdecl, and counts on ebx, esi,
 * edi and ebp.  eax where there is a result. */
struct Promise
{
    const char* name;
    bool watcom;
    bool result;
    unsigned arguments = 0;  // registers it is handed arguments in -- eax, edx, ebx, ecx -- the caller's no longer
    bool fpu = false;        // the x87's stack and control word compared too
    HeapUse heap = kNoHeap;
};

const Promise kPromises[] = {
    {"Error", true, false},
    {"Message", true, true},
    {"AcquireWindow", true, true},
    {"iSNDloaddll", true, true},
    {"SNDcaps", true, true},
    {"Is3DSoundAvailable", true, true},
    {"audiofocushandler", true, false},
    {"SoundServeHandler", true, false},
    {"THRASH_opendll", true, true},
    {"AcquireSoundDataLambda", false, false},
    {"StopSoundBufferLambda", false, false},
    {"AcquireSoundBufferPositionLambda", false, false},
    {"TickSoundLambda", false, false},
    {"PrintSoundLambda", false, false},
    {"TraceSoundLambda", false, false},
    {"abortmessagewrapper", false, false},
    {"iSNDconvertsample", false, true},
    // The Watcom runtime's (native_watcom.cpp).
    {"watcom::CHP", true, false, 0, true},
    {"watcom::GetThreadPtr", true, true},
    {"watcom::NullAccess", true, false},
    {"watcom::memset", true, true, 3},
    {"watcom::STOSB", true, true},
    {"watcom::STOSD", true, true},
    {"watcom::strcmp", true, true, 2},
    {"watcom::strncmp", true, true, 3},
    {"watcom::stricmp", true, true, 2},
    {"watcom::strncpy", true, true, 3},
    {"watcom::strncat", true, true, 3},
    {"watcom::strrchr", true, true, 2},
    {"watcom::strstr", true, true, 2},
    {"watcom::setbits", true, false, 2},
    {"watcom::strtok", true, true, 2},
    {"watcom::strupr", true, true, 1},
    {"watcom::toupper", true, true, 1},
    {"watcom::tolower", true, true, 1},
    {"watcom::atoi", true, true, 1},
    {"watcom::atol", true, true, 1},
    {"watcom::initrandnext", true, true},
    {"watcom::rand", true, true},
    {"watcom::srand", true, false, 1},
    {"watcom::set_errno", true, true, 1},
    {"watcom::set_ERANGE", true, true},
    {"watcom::set_doserrno", true, true, 1},
    {"watcom::set_errno_dos", true, true, 1},
    {"watcom::set_errno_nt", true, true},
    {"watcom::unlink", true, true, 1},
    {"watcom::remove", true, true, 1},
    {"watcom::mkdir", true, true, 1},
    {"watcom::rmdir", true, true, 1},
    {"watcom::chdir", true, true, 1},
    {"watcom::chmod", true, true, 2},
    {"watcom::access", true, true, 2},
    {"watcom::getcwd", true, true, 2},
    {"watcom::getdiskfree", true, true, 2},
    {"watcom::fixed_GetFileAttributesA", true, true, 1},
    {"watcom::GetIOMode", true, true, 1},
    {"watcom::SetIOMode", true, true, 2},
    {"watcom::isatty", true, true, 1},
    {"watcom::lseek", true, true, 3},
    {"watcom::tell", true, true, 1},
    {"watcom::qread", true, true, 3},
    {"watcom::qwrite", true, true, 3},
    {"watcom::leapyear", true, true, 1},
    {"watcom::brktime", true, true, 4},
    {"watcom::time_less", true, true, 2},
    {"watcom::calc_yday", true, true, 2},
    {"watcom::check_order", true, true, 3},
    {"watcom::isindst", true, true, 1},
    {"watcom::mktime", true, true, 1},
    {"watcom::getctime", true, true, 1},
    {"watcom::time", true, true, 1},
    {"watcom::localtime_", true, true, 2},
    {"watcom::localtime", true, true, 1},
    {"watcom::IF_DATAN2", true, true, 0, true},
    {"watcom::floor", true, true, 0, true},
    {"watcom::ceil", true, true, 0, true},
    {"watcom::modf", true, true, 0, true},
    {"watcom::control87", true, true, 2, true},
    {"watcom::IF_DEXP", true, true, 0, true},
    {"watcom::exp", true, true, 0, true},
    {"watcom::IF_DACOS", true, true, 0, true},
    {"watcom::DSQRT", true, true, 0, true},
    {"watcom::math87_err", true, true, 0, true},
    {"watcom::set_EDOM", true, true},
    {"watcom::med3", true, true, 4},
    {"watcom::byteswap", true, true},  // esi, edi and ecx its arguments, all it leaves as qsort expects
    {"watcom::qsort", true, false, 4},
    {"watcom::bsearch", true, true, 4},
    {"watcom::fsync", true, true, 1},
    {"watcom::chktty", true, true, 1},
    {"watcom::ioalloc", true, true, 1},
    {"watcom::flush", true, true, 1},
    {"watcom::fputc", true, true, 2},
    {"watcom::fputs", true, true, 2},
    {"watcom::fwrite", true, true, 4},
    {"watcom::flushall_", true, true, 1},
    {"watcom::flushall", true, true},
    {"watcom::fflush", true, true, 1},
    {"watcom::update_buffer", true, true, 2},
    {"watcom::reset_buffer", true, true, 1},
    {"watcom::fill_buffer", true, true, 1},
    {"watcom::filbuf", true, true, 1},
    {"watcom::fgetc", true, true, 1},
    {"watcom::fread", true, true, 4},
    {"watcom::fgets", true, true, 3},
    {"watcom::fseek", true, true, 3},
    {"watcom::ftell", true, true, 1},
    {"watcom::GetNTAccessAttr", true, true, 3},
    {"watcom::GetNTShareAttr", true, true, 2},
    {"watcom::handlesFull", true, true},
    {"watcom::NTGetFakeHandle", true, true},
    {"watcom::allocPOSIXHandle", true, true, 1},
    {"watcom::freePOSIXHandle", true, true, 1},
    {"watcom::close", true, true, 1},
    {"watcom::sopen_", true, true, 4},
    {"watcom::sopen", true, true},
    {"watcom::open_flags", true, true, 2},
    {"watcom::doopen", true, true, 4},
    {"watcom::allocfp", true, true, 1},
    {"watcom::freefp", true, true, 1},
    {"watcom::doclose", true, true, 2},
    {"watcom::shutdown_stream", true, true, 2},
    {"watcom::fclose", true, true, 1},
    {"watcom::fsopen", true, true, 3},
    {"watcom::fopen", true, true, 2},
    // Its heap (native_watcom_heap.cpp).
    {"watcom::nmalloc", true, true, 1, false, kStirred},
    {"watcom::nfree", true, false, 1, false, kStirred},
    {"watcom::MemAllocator", true, true, 3, false, kStirred},
    {"watcom::MemFree", true, false, 3, false, kStirred},
    {"watcom::LinkUpNewNHeap", true, true, 1, false, kRestored},
    {"watcom::AdjustAmount", true, true, 1},
    {"watcom::CreateNewNHeap", true, true, 1, false, kStirred},
    {"watcom::ExpandDGROUP", true, true, 1, false, kStirred},
    {"watcom::nmemneed", true, true, 1},
    {"watcom::nheapshrink", true, true, 0, false, kStirred},
    {"watcom::ReturnMemToSystem", true, true, 1, false, kRestored},
    {"watcom::ReleaseNHeap", true, true, 1, false, kRestored},
    // The game's MMX code (native_mmx.cpp): the SND library's routines keep
    // every register; the memmove's copy leaves eax, edx and ebx where it got
    // to, and keeps ecx.  The MMX registers are compared for all.
    {"mmx::copySwapped", true, true},
    {"mmx::copy", true, true},
    {"mmx::addMono8", true, true},
    {"mmx::addStereo8", true, true},
    {"mmx::addMono16", true, true},
    {"mmx::addStereo16", true, true},
    {"mmx::outputMono8", true, true},
    {"mmx::outputStereo8", true, true},
    {"mmx::outputStereo16", true, true},
    {"mmx::clear", true, true},
    {"mmx::emms", true, true},
    {"mmx::outputMono16", true, true},
    {"mmx::interpolateMono8", true, true},
    {"mmx::interpolateStereo8", true, true},
    {"mmx::interpolateMono16", true, true},
    {"mmx::interpolateStereo16", true, true},
    {"mmx::xaMono", true, true},
    {"mmx::xaStereo", true, true},
};

const Promise* promiseOf(const char* name)
{
    for (const Promise& p : kPromises)
        if (std::strcmp(p.name, name) == 0)
            return &p;
    return nullptr;
}

/* A float's bits of every kind: ordinary, tiny, huge, denormal, zero,
 * infinite, NaN quiet and signalling. */
x86::reg32 anyFloatBits(std::uint64_t r)
{
    const x86::reg32 low = x86::reg32(r >> 8);
    switch (r % 8)
    {
    case 0: return low;
    case 1: return (low & 0x80000000) | (low & 0x7fffff);              // zero or denormal
    case 2: return (low & 0x80000000) | 0x7f800000;                    // infinite
    case 3: return 0x7f800000 | (low & 0x3fffff) | 1;                  // signalling NaN
    case 4: return (low & 0x80000000) | 0x7fc00000 | (low & 0x3fffff); // quiet NaN
    default:
    {
        const float f = float(int(low % 20001) - 10000) * 0.37f;
        x86::reg32 bits;
        std::memcpy(&bits, &f, 4);
        return bits;
    }
    }
}

/* A Windows error, as GetLastError has one: the ones __set_errno_dos looks
 * for, one of the first 20 it has a table for, one past them, or anything. */
x86::reg32 anError(x86::reg32 r)
{
    static const x86::reg32 named[] = {0x7b, 0xce, 0xb7};
    switch (r % 4)
    {
    case 0: return named[(r >> 2) % 3];
    case 1: return r >> 8;
    default: return (r >> 8) % 0x16;
    }
}

/* A byte of a file: anything, but a '\r', a '\n' or a ^Z often, which text
 * streams make something of. */
x86::reg8 fileByte(std::uint64_t bits)
{
    return bits % 6 == 0 ? x86::reg8("\r\n\x1a"[(bits >> 8) % 3]) : x86::reg8(bits >> 16);
}

}  // namespace

namespace win32
{

/* A guest memory of its own, and its own log of calls out. */
class CheckApp : public WinApplication
{
public:
    CheckApp(bool generated) : WinApplication("game_checks", 0, {}), generated(generated) {}
    bool generated;
    std::vector<Call> calls;

    x86::reg32& word(x86::reg32 address) { return reinterpret_cast<x86::reg32&>(*&getMemory<x86::reg8>(address)); }

    x86::reg32 random(x86::reg32 id)
    {
        return x86::reg32(mix(g_seed ^ (std::uint64_t(calls.size()) << 32) ^ id));
    }

    std::uint64_t random64(x86::reg32 id)
    {
        return mix(g_seed ^ (std::uint64_t(calls.size()) << 32) ^ id ^ 0x5555);
    }

    /* Text of `length` at `at`, made from `r`. */
    void text(x86::reg32 at, x86::reg32 length, std::uint64_t r)
    {
        for (x86::reg32 i = 0; i < length; ++i)
        {
            r = mix(r);
            getMemory<x86::reg8>(at + i) = x86::reg8(' ' + r % 95);
        }
        getMemory<x86::reg8>(at + length) = 0;
    }

    /* Samples into a buffer, made from `r`: at most kSlotSize bytes, and only
     * into memory that is compared. */
    void samples(x86::reg32 at, x86::reg32 count, std::uint64_t r)
    {
        count = std::min<x86::reg32>(count, 0x800);
        if (!((at >= kHeap && at + 4 * count <= kHeapEnd) || (at >= kHarness && at + 4 * count <= kHarnessEnd)
              || at + 4 * count <= kLowEnd))
            return;
        for (x86::reg32 i = 0; i < count; ++i)
        {
            r = mix(r);
            word(at + 4 * i) = anyFloatBits(r);
        }
    }

    void standIn(const StandIn& s, x86::reg32 id, x86::CPU& cpu)
    {
        const x86::reg32 esp = cpu.esp;
        std::vector<x86::reg32> words;
        const x86::reg32 registers[] = {cpu.eax, cpu.edx, cpu.ebx, cpu.ecx};
        for (unsigned i = 0; i < s.registers; ++i)
            words.push_back(registers[i]);
        for (unsigned i = 0; i < s.words; ++i)
            words.push_back(word(esp + 4 + 4 * i));
        if (s.through >= 0)
        {
            const x86::reg32 from = s.through < 4 ? registers[s.through] : word(esp + 4 + 4 * (s.through - 4));
            for (unsigned i = 0; i < s.deref; ++i)
                words.push_back(word(from + 4 * i));
        }
        if (s.formats != 0)
        {
            const x86::reg32 format = s.formats == 1 ? registers[1] : word(esp + 4);
            const x86::reg32 arguments = s.formats == 1 ? word(registers[2]) : esp + 8;
            unsigned count = 0;
            for (x86::reg32 at = format; at < format + 0x400 && getMemory<char>(at) != 0; ++at)
                if (getMemory<char>(at) == '%')
                {
                    if (getMemory<char>(at + 1) == '%')
                        ++at;
                    else
                        ++count;
                }
            for (unsigned i = 0; i < count && i < 8; ++i)
                words.push_back(word(arguments + 4 * i));
        }
        if (s.effect == kCompare)
            words.push_back(esp);  // where the runtime's frame has it
        calls.push_back({id, words});
        if (long(calls.size()) - 1 == g_stopAt)
        {
            cpu.terminate = true;
            return;
        }
        const x86::reg32 r = random(id);
        x86::reg32 result = r;
        switch (s.effect)
        {
        case kText:
            result = r % 0x100;
            text(cpu.eax, result, random64(id));
            break;
        case kPrint:
            result = r % 0x70;  // within the caller's buffer
            text(words[0], result, random64(id));
            break;
        case kLoad:
            result = r % 8 != 0 ? 0x7700 + (r >> 8) % 0x10 * 0x10 : 0;
            break;
        case kLookUp:
        {
            const std::string name = &getMemory<char>(words[1]);
            result = g_lookupFails && r % 16 == 0 ? 0 : namedStandIn(name);
            break;
        }
        case kVersion:
            result = r % 6 != 0 ? 0x100003 : r % 2 ? 0x100002 : r;
            break;
        case kAbout:
            result = r % 6 != 0 ? kAboutRecord : 0;
            break;
        case kBox:
            result = r % 3 != 0 ? 1 : 2;
            break;
        case kMainThread:
            result = r & 1;
            break;
        case kAllocate:
        {
            // A slot no one has, if the size fits one: the first free from
            // one picked at random.
            const x86::reg32 taken = word(kSlotsTaken);
            result = 0;
            if (r % 25 != 0 && words[1] != 0 && words[1] <= kSlotSize && taken != 0xff)
            {
                x86::reg32 slot = (r >> 8) % 8;
                while (taken >> slot & 1)
                    slot = (slot + 1) % 8;
                word(kSlotsTaken) = taken | 1u << slot;
                result = kHeap + kSlotSize * slot;
                samples(result, kSlotSize / 4, random64(id));
            }
            break;
        }
        case kFree:
        {
            // Only where a slot VirtualAlloc gave starts.
            const x86::reg32 slot = (words[0] - kHeap) / kSlotSize;
            result = 0;
            if (r % 25 != 0 && words[0] >= kHeap && words[0] < kHeapEnd && (words[0] - kHeap) % kSlotSize == 0
                && (word(kSlotsTaken) >> slot & 1))
            {
                word(kSlotsTaken) &= ~(1u << slot);
                result = 1;
            }
            break;
        }
        case kDecode:
        {
            // the buffer: the third argument, or the record's last word
            const x86::reg32 buffer = s.deref ? words.back() : words[2];
            const x86::reg32 count = s.deref ? words[1] : words[0];
            samples(buffer, count, random64(id));
            break;
        }
        case kFilter:
            result = r % 3 != 0 ? r | 1 : 0;
            break;
        case kLock:
            result = r % 2 != 0 ? 0x630000 + (r >> 8) % 0x100 * 0x10 : 0;
            break;
        case kSucceed:
            result = r % 5 != 0 ? 1 : 0;
            break;
        case kLastError:
            result = anError(r);
            break;
        case kAttributes:
            result = r % 5 != 0 ? (r >> 8) & 0x1ff : 0xffffffff;
            break;
        case kDirectory:
        {
            // The path as long as it is, up to past MAX_PATH; into the
            // buffer if it fits, else how much it would take; or nothing.
            const x86::reg32 length = 1 + (r >> 8) % 0x120;
            if (r % 9 == 0)
            {
                result = 0;
            }
            else if (length < words[0])
            {
                text(words[1], length, random64(id));
                result = length;
            }
            else
            {
                result = length + 1;
            }
            break;
        }
        case kDiskFree:
            result = r % 5 != 0 ? 1 : 0;
            if (result != 0)
                for (unsigned i = 1; i <= 4; ++i)
                    word(words[i]) = random(id + i);
            break;
        case kFind:
            result = r % 5 != 0 ? 0x7f00 + (r >> 8) % 0x100 : 0xffffffff;
            if (result != 0xffffffff)
                for (x86::reg32 i = 0; i < 0x140; i += 4)
                    word(words[1] + i) = i == 0 ? (r >> 8) & 0x1ff : random(id + i);
            break;
        case kLocalTime:
        {
            // Year, month, day of the week, day, hour, minute, second,
            // millisecond: in range mostly, anything now and then.
            static const x86::reg32 ranges[] = {200, 12, 7, 31, 24, 60, 60, 1000};
            for (unsigned i = 0; i < 8; ++i)
            {
                const x86::reg32 v = random(id + 3 * i);
                const x86::reg32 in = i == 0 ? 1900 + v % ranges[0] : (i == 1 || i == 3 ? 1 : 0) + v % ranges[i];
                getMemory<x86::reg16>(words[0] + 2 * i) = x86::reg16(r % 9 != 0 ? in : v >> 8);
            }
            break;
        }
        case kZone:
            if (r % 3 == 0)
            {
                word(kTimezone) = x86::reg32(x86::sreg32(random(id + 1) % 100801) - 50400);
                word(kDstAdjust) = random(id + 2) % 4 != 0 ? 3600 : random(id + 3) % 7201;
            }
            break;
        case kMathResult:
            cpu.fpu.count += 1;
            cpu.fpu.st(0) = r % 5 != 0 ? x86::Float(double(x86::sreg32(r)) / 7.0) : x86::Float(r % 2 ? INFINITY : NAN);
            break;
        case kSeek:
            // A place: near the start often, for fseek within a buffer.
            result = r % 6 == 0 ? 0xffffffff : r % 3 == 0 ? (r >> 8) % 0x800 : r >> 4;
            break;
        case kCharacter:
            result = r % 6 != 0 ? (r >> 8) & 0xff : 0xffffffff;
            break;
        case kOpenFile:
            result = r % 5 != 0 ? 0x7000 + (r >> 8) % 0x100 * 4 : 0xffffffff;
            break;
        case kEvent:
            result = r % 3 != 0 ? 0x7400 + (r >> 8) % 0x100 * 4 : 0;
            break;
        case kHandle:
            result = r % 8 != 0 ? (r >> 8) % 20 : (r >> 3) % 2 ? 20 + (r >> 8) % 3 : 0xffffffff;
            break;
        case kReallocate:
            // Where they were, moved; or nothing.
            result = r % 5 != 0 ? kGrownTable : 0;
            if (result != 0)
                for (x86::reg32 i = 0; i < std::min<x86::reg32>(words[1], 0x100); i += 4)
                    word(kGrownTable + i) = word(words[0] + i);
            break;
        case kTmpName:
            text(words[0], 8 + r % 24, random64(id));
            break;
        case kRead:
        case kTransfer:
        {
            // How many: as many as asked for mostly, fewer, none; read
            // ones written into the buffer.
            const x86::reg32 asked = std::min<x86::reg32>(words[2], 0x10000);
            const x86::reg32 count = r % 3 != 0 ? asked : (r >> 4) % 3 == 0 ? 0 : (r >> 8) % (asked + 1);
            const bool failed = r % 6 == 0;
            if (!failed && (s.effect == kRead || s.address == kWindowsStdin))
            {
                std::uint64_t bits = random64(id);
                for (x86::reg32 i = 0; i < count; ++i)
                    getMemory<x86::reg8>(words[1] + i) = fileByte(bits = mix(bits));
            }
            if (s.effect == kRead)
            {
                if (!failed)
                    word(words[3]) = count;
                result = failed ? 0 : 1;
            }
            else
            {
                result = failed ? 0xffffffff : count;
            }
            break;
        }
        case kWrite:
        {
            const x86::reg32 asked = std::min<x86::reg32>(words[2], 0x10000);
            result = r % 6 != 0 ? 1 : 0;
            // All of it mostly; fewer, none now and then -- a disk full.
            if (result != 0)
                word(words[3]) = r % 4 != 0 ? words[2] : (r >> 4) % 3 == 0 ? 0 : (r >> 8) % (asked + 1);
            break;
        }
        case kFileType:
            result = (r >> 8) % 4;
            break;
        case kWindowed:
            result = r % 2 != 0 ? 0x77000 + (r >> 8) % 0x100 * 4 : 0;
            break;
        case kCompare:
            // The first dwords' difference, signed and as it wraps; the first
            // bytes' order; or anything.
            if (s.address == kByDword)
            {
                result = word(words[0]) - word(words[1]);
            }
            else if (s.address == kByByte)
            {
                const x86::reg8 a = getMemory<x86::reg8>(words[0]), b = getMemory<x86::reg8>(words[1]);
                result = a < b ? 0xffffffff : a > b ? 1 : 0;
            }
            else
            {
                result = r % 3 == 0 ? 0 : r % 3 == 1 ? r | 0x80000000 : (r >> 1) | 1;
            }
            break;
        case kNothing:
            break;
        }
        // What it may leave otherwise, it does now and then.
        const x86::reg32 more = random(id ^ 0xabcd);
        if (s.clobbers & kEax)
            cpu.eax = s.effect != kNothing || more % 4 != 0 ? result : cpu.eax;
        if ((s.clobbers & kEcx) && (more >> 2) % 4 != 0)
            cpu.ecx = more ^ 0x11111111;
        if ((s.clobbers & kEdx) && (more >> 4) % 4 != 0)
            cpu.edx = more ^ 0x22222222;
        if ((s.clobbers & kEbx) && (more >> 6) % 4 != 0)
            cpu.ebx = more ^ 0x33333333;
        cpu.esp = esp + 4 + (s.convention == kStdcall ? 4 * s.words : 0);
    }

    /* A function GetProcAddress gave: stdcall, its words from its name's @. */
    void named(x86::reg32 index, x86::CPU& cpu)
    {
        const std::string& name = g_names[index];
        const size_t at = name.rfind('@');
        const x86::reg32 words = at == std::string::npos ? 0 : x86::reg32(std::atoi(name.c_str() + at + 1)) / 4;
        Effect effect = kNothing;
        if (name == "_iSNDdllversion@0")
            effect = kVersion;
        else if (name == "_THRASH_about@0")
            effect = kAbout;
        const StandIn s = {kNamed + 0x10 * index, name.c_str(), kStdcall, 0, words, kScratch, -1, 0, effect};
        standIn(s, s.address, cpu);
    }
};

CheckApp* g_running = nullptr;

WinApplication::WinApplication(const char*, x86::reg32, const std::vector<Section>&)
{
    void* memory = mmap(nullptr, kMemory, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (memory == MAP_FAILED)
        std::abort();
    m_memory = static_cast<x86::reg8*>(memory);
}

WinApplication::~WinApplication() {}

int WinApplication::s_traceApi = 0;
bool WinApplication::readTraceApi() { return false; }
void WinApplication::traceCall(const Method&, x86::reg32) {}
void WinApplication::yieldContext(const x86::CPU&) {}

void WinApplication::dynamicCallElsewhere(x86::reg32 address, x86::CPU& cpu)
{
    CheckApp* app = static_cast<CheckApp*>(this);
    if (address == 0)
    {
        // A pointer the game never set, as the game calls it: the end of it.
        app->calls.push_back({0, {}});
        cpu.terminate = true;
        return;
    }
    for (const StandIn& s : kGameFunctions)
        if (s.address == address)
        {
            app->standIn(s, address, cpu);
            return;
        }
    if (address >= kStandIns && address < kStandIns + 0x10 * kPointerCount && (address & 0xf) == 0)
    {
        app->standIn(kPointers[(address - kStandIns) / 0x10], address, cpu);
        return;
    }
    if (address >= kNamed && address < kNamed + 0x10 * x86::reg32(g_names.size()) && (address & 0xf) == 0)
    {
        app->named((address - kNamed) / 0x10, cpu);
        return;
    }
    for (const Tested& t : kTested)
        if (t.address == address)
        {
            (app->generated ? t.generated : t.native)(this, cpu);
            return;
        }
    std::printf("a call to %08x, no stand-in there (%s, %zu calls)\n", unsigned(address),
                app->generated ? "generated" : "native", app->calls.size());
    std::exit(2);
}

void MemMap::usedRanges(std::vector<std::pair<x86::reg32, x86::reg32>>& ranges)
{
    ranges.assign(1, {0, kMemory});
}

}  // namespace win32

/* The game's functions the generated code calls by address: their stand-ins. */
#define STAND_IN(a)                                                                      \
    void nfs3hp::Application::sub_##a(WinApplication* app, x86::CPU& cpu)               \
    {                                                                                    \
        app->dynamic_call(0x##a, cpu);                                                   \
    }
#include "game_called.inc"

namespace
{

using win32::CheckApp;

std::mt19937 g_random(1998);

x86::reg32 random32()
{
    return x86::reg32(g_random());
}

x86::reg32 below(x86::reg32 n)
{
    return x86::reg32(g_random() % n);
}

bool chance(int percent)
{
    return int(g_random() % 100) < percent;
}

x86::reg8* bytes(win32::WinApplication& app, x86::reg32 at)
{
    return &app.getMemory<x86::reg8>(at);
}

struct Counts
{
    unsigned cases = 0, stopped = 0, failed = 0;
};

const char* g_name = "";
unsigned g_case = 0;

bool report(Counts& counts, const char* what)
{
    if (++counts.failed <= 10)
        std::printf("  %s case %u: %s\n", g_name, g_case, what);
    return false;
}

/* The first byte of [from, to) where the two memories differ, or `to`. */
x86::reg32 firstDifference(win32::WinApplication& a, win32::WinApplication& b, x86::reg32 from, x86::reg32 to)
{
    if (to <= from || std::memcmp(bytes(a, from), bytes(b, from), to - from) == 0)
        return to;
    for (x86::reg32 at = from; at < to; ++at)
        if (*bytes(a, at) != *bytes(b, at))
            return at;
    return to;
}

void copyWindows(win32::WinApplication& to, win32::WinApplication& from)
{
    for (const auto& w : kWindows)
        std::memcpy(bytes(to, w.first), bytes(from, w.first), w.second - w.first);
}

x86::reg32 aString()
{
    return kStrings + 0x40 * below(64);
}

/* A Float's bits, as hex: the 80 of the x87's, or the double's. */
std::string floatBits(const x86::Float& f)
{
#ifdef WITH_PEDANTIC_FPU
    const x86::IEEEf80Data& d = f.f80value.data;
    const unsigned words[] = {d.data5, d.data4, d.data3, d.data2, d.data1};
#else
    const double value = f;
    std::uint64_t bits;
    std::memcpy(&bits, &value, 8);
    const unsigned words[] = {unsigned(bits >> 48), unsigned(bits >> 32 & 0xffff), unsigned(bits >> 16 & 0xffff),
                              unsigned(bits & 0xffff)};
#endif
    std::string text;
    char word[8];
    for (const unsigned w : words)
    {
        std::snprintf(word, sizeof word, "%04x", w);
        text += word;
    }
    return text;
}

/* A double of every kind: an integer and a half, a fraction, huge, tiny,
 * denormal, zero, infinite, NaN -- of either sign. */
double anyDouble()
{
    double value;
    switch (below(8))
    {
    case 0: { std::uint64_t bits = std::uint64_t(random32()) << 32 | random32(); std::memcpy(&value, &bits, 8); return value; }
    case 1: value = double(x86::sreg32(random32()) >> below(31)) + 0.5 * below(3); break;
    case 2: value = std::ldexp(double(random32()), int(below(140)) - 70); break;
    case 3: value = double(below(5)) * 0.25; break;
    case 4: value = std::ldexp(1.0 + double(below(1000)) / 1000.0, int(below(2100)) - 1075); break;
    case 5: value = chance(50) ? INFINITY : NAN; break;
    default: value = double(x86::sreg32(random32() >> below(32))) * 0.37; break;
    }
    return chance(50) ? -value : value;
}

x86::reg32 textString(x86::reg32 i)
{
    return kTexts + 0x100 * i;
}

x86::reg32 aText()
{
    return textString(below(32));
}

x86::reg32 aBuffer()
{
    return kBuffers + 0x200 * below(16);
}

/* The string functions' strings, made up again for each case: in pairs, the
 * second the first with a change -- a letter's case, a byte, the end moved --
 * of letters, digits, signs, spaces and bytes above 0x7f, as the case picks
 * its alphabet. */
void makeText(CheckApp& g)
{
    static const char* const alphabets[] = {"abcAB", "aA bB,;", "0123456789+- \t", "xyzXYZ\x80\xc1\xff",
                                            "the quick brown fox", "aaaa", " \t\n\v\f\r19-"};
    const char* alphabet = alphabets[below(7)];
    const x86::reg32 size = x86::reg32(std::strlen(alphabet));
    for (x86::reg32 i = 0; i < 32; i += 2)
    {
        const x86::reg32 length = chance(10) ? 0 : 1 + below(chance(70) ? 12 : 0xf0);
        x86::reg8 first[0x100], second[0x100];
        for (x86::reg32 j = 0; j < length; ++j)
            first[j] = chance(95) ? x86::reg8(alphabet[below(size)]) : x86::reg8(1 + below(255));
        first[length] = 0;
        std::memcpy(second, first, length + 1);
        x86::reg32 end = length;
        switch (below(6))
        {
        case 0: break;
        case 1: if (length) second[below(length)] ^= 0x20; break;
        case 2: if (length) second[below(length)] = x86::reg8(1 + below(255)); break;
        case 3: end = below(length + 1); second[end] = 0; break;
        case 4: if (length < 0xf0) { second[length] = x86::reg8(alphabet[below(size)]); second[length + 1] = 0; } break;
        default: if (length) second[length - 1] = x86::reg8(0x80 | random32()); break;
        }
        std::memcpy(&g.getMemory<x86::reg8>(textString(i)), first, 0x100);
        std::memcpy(&g.getMemory<x86::reg8>(textString(i + 1)), second, 0x100);
    }
    for (x86::reg32 at = kBuffers; at < kBuffers + 0x2000; at += 4)
        g.word(at) = chance(30) ? 0 : random32();
}

/* A copy of a string of kTexts into a buffer, for the functions that write. */
x86::reg32 copied(CheckApp& g, x86::reg32 from)
{
    const x86::reg32 buffer = aBuffer();
    std::memcpy(&g.getMemory<x86::reg8>(buffer), &g.getMemory<x86::reg8>(from), 0x100);
    return buffer;
}

/* The runtime's heap's miniheaps, in the list's order: each in a slot of
 * VirtualAlloc's. */
std::vector<x86::reg32> miniheaps(CheckApp& g)
{
    std::vector<x86::reg32> heaps;
    for (x86::reg32 heap = g.word(kHeapFirst); heap >= kHeap && heap < kHeapEnd && heaps.size() < 8;
         heap = g.word(heap + 8))
        heaps.push_back(heap);
    return heaps;
}

/* The miniheap a block is in, or 0. */
x86::reg32 heapHolding(CheckApp& g, x86::reg32 block)
{
    for (const x86::reg32 heap : miniheaps(g))
        if (heap <= block && block < heap + g.word(heap))
            return heap;
    return 0;
}

/* The blocks the heap gave the generated _nmalloc and __MemAllocator, for
 * the cases that give them back; one given back is off the list, whether the
 * case got that far or not. */
std::vector<x86::reg32> g_blocks;

x86::reg32 takeBlock()
{
    const size_t at = below(x86::reg32(g_blocks.size()));
    const x86::reg32 block = g_blocks[at];
    g_blocks.erase(g_blocks.begin() + at);
    return block;
}

/* An amount to ask the heap for: mostly a few bytes, up to most of a slot;
 * none, or more than there is. */
x86::reg32 anAmount()
{
    switch (below(10))
    {
    case 0: return chance(30) ? 0 : chance(50) ? 0xffffffd0 + below(0x10) : random32();
    case 1: return 1 + below(0x18000);
    case 2: case 3: return 1 + below(0x2000);
    default: return 1 + below(0x100);
    }
}

const Tested& testedNamed(const char* name)
{
    for (const Tested& t : kTested)
        if (std::strcmp(t.name, name) == 0)
            return t;
    std::abort();
}

/* The rover on a miniheap given back -- as __ReturnMemToSystem leaves it when
 * that was the only one -- is where the game would fault, its memory gone;
 * here it is not, and what the heap does with it next would only spoil it.
 * The heap starts afresh instead. */
void keepHeapSound(CheckApp& g)
{
    const x86::reg32 rover = g.word(kHeapRover);
    const std::vector<x86::reg32> heaps = miniheaps(g);
    if (rover == 0 || std::find(heaps.begin(), heaps.end(), rover) != heaps.end())
        return;
    for (const x86::reg32 at : {kHeapFirst, kHeapRover, kHeapLargestBefore, kHeapFreeRover})
        g.word(at) = 0;
    g_blocks.clear();
}

/* The heap as the game's use leaves it: before each case of a function of
 * the heap's, a few blocks taken or given back by the generated _nmalloc and
 * _nfree, two dozen held at most -- miniheaps full, empty and in between. */
void stirHeap(CheckApp& g)
{
    const Tested& nmalloc = testedNamed("watcom::nmalloc");
    const Tested& nfree = testedNamed("watcom::nfree");
    for (x86::reg32 i = below(6); i > 0; --i)
    {
        x86::CPU cpu{};
        cpu.esp = kStackHigh - 0x100;
        if (!g_blocks.empty() && (g_blocks.size() > 24 || chance(50)))
        {
            cpu.eax = takeBlock();
            nfree.generated(&g, cpu);
        }
        else
        {
            cpu.eax = anAmount();
            nmalloc.generated(&g, cpu);
            if (!cpu.terminate && cpu.eax != 0)
                g_blocks.push_back(cpu.eax);
        }
        keepHeapSound(g);
    }
}

/* A struct tm as the time functions are handed one: sensible, or its
 * fields out of their ranges -- months past 11, seconds past 59, negative
 * ones -- or anything. */
void makeTm(CheckApp& g, x86::reg32 tm)
{
    static const x86::reg32 ranges[] = {60, 60, 24, 31, 12, 70, 7, 366};
    for (x86::reg32 i = 0; i < 8; ++i)
    {
        x86::reg32 v = below(ranges[i]) + (i == 3 ? 1 : 0) + (i == 5 ? 70 : 0);
        if (chance(15))
            v = x86::reg32(x86::sreg32(below(2 * ranges[i] * 30)) - x86::sreg32(ranges[i] * 30));
        else if (chance(3))
            v = random32();
        g.word(tm + 4 * i) = v;
    }
    g.word(tm + 0x20) = chance(40) ? 0xffffffff : chance(50) ? 0 : chance(80) ? 1 : random32();
}

/* A daylight saving rule, a struct tm of __tzset's: Mm.w.d (isdst 0) --
 * month, week 1 to 5, weekday -- or Jn (1) or n (2), a day of the year; and
 * a time of day.  Its month near its range, which the runtime indexes by. */
void makeRule(CheckApp& g, x86::reg32 rule)
{
    g.word(rule + 0x20) = chance(60) ? 0 : chance(50) ? 1 : chance(80) ? 2 : random32();
    g.word(rule + 0x10) = chance(95) ? below(12) : below(14) - 1;
    g.word(rule + 0xc) = chance(90) ? 1 + below(5) : below(8);
    g.word(rule + 0x18) = chance(90) ? below(7) : random32();
    g.word(rule + 0x1c) = chance(90) ? below(367) : random32();
    g.word(rule + 8) = chance(90) ? below(24) : below(30);
    g.word(rule + 4) = below(60);
    g.word(rule + 0) = below(60);
}

/* A stream as the runtime has one: open for writing mostly, for reading, or
 * both; buffered fully, by lines, not at all, or none of them yet, or more
 * than one; text or binary, dirty, a tty's, at its end, in error -- and now
 * and then bits no flag has.  Its buffer made or not yet, of a byte or a
 * few, of 0x86, of most of 1K, and part full, or full; its orientation none,
 * bytes or wide characters, and committed on a flush now and then. */
void makeStream(CheckApp& g, x86::reg32 fp, x86::reg32 link, x86::reg32 buffer, x86::reg32 handle)
{
    static const x86::reg32 bufferings[] = {0, 0x100, 0x200, 0x400};
    static const x86::reg32 sizes[] = {1, 2, 3, 0x10, 0x86, 0x200, 0x3f0};
    x86::reg32 flag = chance(75) ? 2 : chance(50) ? 1 : 3;
    flag |= chance(90) ? bufferings[below(4)] : random32() & 0x700;
    for (const x86::reg32 bit : {0x4u, 0x8u, 0x10u, 0x20u, 0x40u, 0x80u, 0x800u, 0x1000u, 0x2000u, 0x4000u})
        if (chance(bit == 0x40 || bit == 0x1000 ? 50 : bit == 0x8 || bit == 0x2000 ? 25 : bit == 0x800 ? 5 : 10))
            flag |= bit;
    if (chance(5))
        flag |= random32() & 0xffff8000;
    const bool made = chance(80);
    const x86::reg32 size = made || chance(30) ? (chance(60) ? sizes[below(7)] : 1 + below(0x3f0)) : 0;
    const x86::reg32 count = !made || size == 0 ? 0 : chance(92) ? below(size) : size;
    for (x86::reg32 at = buffer; at < buffer + 0x400; at += 4)
        g.word(at) = random32();
    for (x86::reg32 at = buffer + below(16); at < buffer + 0x400; at += 1 + below(16))
        g.getMemory<x86::reg8>(at) = x86::reg8("\r\n\x1a"[below(3)]);
    for (x86::reg32 at = fp; at < fp + 0x20; at += 4)
        g.word(at) = random32();
    g.word(fp) = !made ? 0 : buffer + ((flag & 2) ? count : below(size - count + 1));
    g.word(fp + 4) = count;
    g.word(fp + 8) = link;
    g.word(fp + 0xc) = flag;
    g.word(fp + 0x10) = handle;
    g.word(fp + 0x14) = size;
    g.word(link) = 0;
    g.word(link + 4) = fp;
    g.word(link + 8) = made ? buffer : 0;
    g.word(link + 0xc) = chance(60) ? 0 : chance(75) ? 1 : chance(70) ? 2 : random32();
    g.word(link + 0x10) = (chance(20) ? 1 : 0) | (chance(5) ? random32() & ~1u : 0);
}

/* A handle: one of the 20 mostly, the first three often; 20 itself, which
 * the runtime takes, ones past it, negative ones. */
x86::reg32 aHandle()
{
    static const x86::reg32 picks[] = {20, 21, 0xffffffff, 0, 1, 2, 3, 5, 9, 19};
    return chance(40) ? picks[below(10)] : chance(10) ? random32() : below(20);
}

/* A stream: the harness's, or stdout or stderr, stdin now and then. */
x86::reg32 aStream()
{
    return chance(15) ? kIob + 0x1a * (1 + below(2)) : chance(5) ? kIob : kStreams + 0x40 * below(8);
}

/* The heap afresh, empty, VirtualAlloc's slots all free: for the buffers the
 * streams' functions take that nobody gives back. */
void freshHeap(CheckApp& g)
{
    for (const x86::reg32 at : {kHeapFirst, kHeapRover, kHeapLargestBefore, kHeapFreeRover})
        g.word(at) = 0;
    g.word(kSlotsTaken) = 0;
    g_blocks.clear();
}

/* What the case starts from, on `g`: what the functions read of the game. */
void makeState(CheckApp& g)
{
    // Where an error is from: a file, a function, a line -- or none.
    for (const x86::reg32 where : {kWhere, kCalledFrom})
    {
        g.word(where) = chance(where == kWhere ? 75 : 30) ? aString() : 0;
        g.word(where + 4) = aString();
        g.word(where + 8) = below(2000);
    }
    g.word(kErrorUnderWay) = chance(15) ? 1 + below(3) : 0;
    g.word(kDebugOutput) = chance(25) ? random32() | 1 : 0;
    g.word(kDebugStop) = chance(30) ? 1 : 0;
    g.word(kErrorFilter) = chance(35) ? standInFor(kErrorFilter) : 0;
    g.word(kErrorWhere) = chance(65) ? 1 : 0;
    g.word(kErrorLock) = chance(40) ? standInFor(kErrorLock) : 0;
    g.word(kErrorBefore) = chance(40) ? standInFor(kErrorBefore) : 0;
    g.word(kErrorPrintOk) = chance(50) ? 1 : 0;
    g.word(kErrorOk) = chance(60) ? standInFor(kErrorOk) : 0;
    g.text(kErrorText, below(0x200), random32());
    g.word(kWindow) = chance(85) ? 0x9000 + below(0x100) : 0;

    // iSND: loaded or not, its functions found or not.
    g.word(kSoundModule) = chance(50) ? 0x7700 + below(0x10) * 0x10 : 0;
    g.word(kSoundOptions) = random32();
    static const char* const soundNames[] = {
        "_iSNDdirectcaps@4", "_iSNDdirectstart@8", "_iSNDdirectstop@0", "_iSNDdirectrecordstart@16",
        "_iSNDdirectrecordpacket@4", "_iSNDdirectrecordstop@0", "_iSNDdirectserve@0", "_iSNDdirectvol@8",
        "_iSNDdirectpos3d@12", "_iSNDdirectrate@8", "_iSNDdirectcreate3dbuf@28", "_iSNDdirectremovebuf@4",
        "_iSNDdirectplay3d@28", "_iSNDdirectstopbuf@4",
    };
    for (x86::reg32 i = 0; i < 14; ++i)
        g.word(kSoundFunctions + 4 * i) = chance(97) ? namedStandIn(soundNames[i]) : 0;
    g.word(kSoundLock) = 0x640000 - 0x100 + below(0x10) * 0x10;
    // The game's tick, another, or none yet (SNDcaps sets it; called, the game ends).
    g.word(kSoundTick) = chance(40) ? standInFor(kSoundTick) : chance(60) ? 0x500c80 : 0;

    // THRASH: the renderer's functions, and what its about says.
    g.word(kRendererModule) = random32();
    g.word(kRendererIs3dfx) = below(3);
    for (x86::reg32 at = kThrashSlots; at < kThrashSlotsEnd; at += 4)
        g.word(at) = random32();
    g.word(0x9ef96c) = chance(80) ? namedStandIn("_THRASH_setstate@8") : 0;
    g.word(0x9ef980) = chance(80) ? namedStandIn("_THRASH_about@0") : 0;
    g.word(kAboutRecord) = chance(60) ? 0x33444658 : random32();
    g.word(kAboutRecord + 8) = chance(60) ? 0x68 : chance(50) ? 0x67 : random32();

    // The Watcom runtime's: its thread's data -- rand's seed, where strtok
    // goes on -- and the strings for its string functions.
    makeText(g);
    g.word(kThreadData) = kThread;
    g.word(kThread + 0xc) = random32();
    g.word(kThread + 0x10) = chance(50) ? 0 : copied(g, aText()) + below(8);

    // Its heap, as the cases before left it: its lock the runtime's own -- a
    // bare ret -- or a stand-in; growing, but now and then not; VirtualAlloc's
    // slots its miniheaps', the rest free.
    g.word(kHeapAccess) = chance(50) ? standInFor(kHeapAccess) : kNullAccess;
    g.word(kHeapRelease) = chance(50) ? standInFor(kHeapRelease) : kNullAccess;
    g.word(kHeapEnabled) = chance(97) ? 1 : 0;
    g.word(kHeapBrk) = chance(97) ? 0 : 0xfffffffe;
    g.word(kHeapBlockSize) = 0x10000;
    g.getMemory<x86::reg8>(kHeapClean) = chance(50) ? 1 : 0;
    // Its time zone: west or east, daylight saving's hour or another, its
    // rules -- Mm.w.d, Jn or n -- northern or southern, or no daylight saving
    // at all.
    g.word(kTimezone) = chance(80) ? x86::reg32(3600 * (x86::sreg32(below(25)) - 12)) : random32();
    g.word(kDstAdjust) = chance(80) ? 3600 : below(7201);
    g.word(kDstName) = chance(25) ? kStrings : aString();  // kStrings' first is ""
    for (const x86::reg32 rule : {kDstStart, kDstEnd})
        makeRule(g, rule);

    // Its handles: __OSHandles' HANDLEs, the game's modes -- the first three's
    // isatty asked or not yet -- the file's lock the runtime's own or a
    // stand-in, and now and then the default windowing's hooks, which the
    // game has none of.
    g.word(kOsHandles) = kHandleTable;
    const bool handlesTaken = chance(40);  // none free
    for (x86::reg32 i = 0; i < 32; ++i)
        g.word(kHandleTable + 4 * i) = !handlesTaken && chance(15) ? 0 : random32() | 1;
    g.word(kFileCount) = 20;
    g.word(kIoModes) = kGameIoModes;
    for (x86::reg32 i = 0; i < 20; ++i)
        g.word(kGameIoModes + 4 * i) = random32() & 0xffff;
    g.word(kAccessFile) = chance(50) ? standInFor(kAccessFile) : kNullAccess;
    g.word(kReleaseFile) = chance(50) ? standInFor(kReleaseFile) : kNullAccess;
    const bool windowed = chance(15);
    g.word(kIsWindowedHandle) = windowed ? standInFor(kIsWindowedHandle) : 0;
    g.word(kWindowsStdin) = windowed && chance(70) ? standInFor(kWindowsStdin) : 0;
    g.word(kWindowsStdout) = windowed && chance(70) ? standInFor(kWindowsStdout) : 0;
    for (const x86::reg32 hook : {kRemoveWindowedHandle, kNewWindow, kDestroyWindow})
        g.word(hook) = windowed && chance(70) ? standInFor(hook) : 0;

    // Its streams: the harness's eight and __iob's first three, theirs
    // 0, 1 and 2 mostly; __OpenStreams some of them, in any order;
    // the streams' lock the runtime's own or a stand-in.
    std::vector<x86::reg32> links, closed;
    for (x86::reg32 i = 0; i < 11; ++i)
    {
        const x86::reg32 fp = i < 8 ? kStreams + 0x40 * i : kIob + 0x1a * (i - 8);
        const x86::reg32 link = i < 8 ? fp + 0x20 : kIobLinks + 0x20 * (i - 8);
        // A stream's handle one isatty can take, which looks at none: of
        // the 20, 20 itself, 21 or -1.
        static const x86::reg32 handles[] = {20, 21, 0xffffffff};
        const x86::reg32 handle = chance(95) ? below(20) : handles[below(3)];
        makeStream(g, fp, link, kStreamBuffers + 0x400 * i, i < 8 || chance(10) ? handle : i - 8);
        if (chance(70))
            links.insert(links.begin() + below(x86::reg32(links.size()) + 1), link);
        else if (chance(50))
            closed.insert(closed.begin() + below(x86::reg32(closed.size()) + 1), link);
    }
    if (chance(10))
        links.clear();
    if (chance(30))
        closed.clear();
    for (const auto* list : {&links, &closed})
    {
        g.word(list == &links ? kOpenStreams : kClosedStreams) = list->empty() ? 0 : list->front();
        for (size_t i = 0; i + 1 < list->size(); ++i)
            g.word((*list)[i]) = (*list)[i + 1];
    }
    // The rest of __iob in use or free, all of it now and then.
    const bool iobTaken = chance(30);
    for (x86::reg32 i = 3; i < 20; ++i)
        g.word(kIob + 0x1a * i + 0xc) = iobTaken || chance(50) ? (random32() & ~3u) | (1 + below(3)) : 0;
    g.word(kAccessIob) = chance(50) ? standInFor(kAccessIob) : kNullAccess;
    g.word(kReleaseIob) = chance(50) ? standInFor(kReleaseIob) : kNullAccess;

    // Opening and closing's: __OSHandles 20 long mostly; the handles' lock
    // the runtime's or a stand-in; __allocPOSIXHandle and __freePOSIXHandle
    // stand-ins where the runtime calls them through; _commode, _fmode and
    // the umask as the game has them, or otherwise.
    g.word(kHandleCount) = chance(60) ? 20 : chance(60) ? 19 + below(3) : below(33);
    g.word(kFakeHandle) = 0x80000000 + below(8);
    g.word(kAccessHandles) = chance(50) ? standInFor(kAccessHandles) : kNullAccess;
    g.word(kReleaseHandles) = chance(50) ? standInFor(kReleaseHandles) : kNullAccess;
    g.word(kAllocHandle) = standInFor(kAllocHandle);
    g.word(kFreeHandle) = standInFor(kFreeHandle);
    g.word(kCommitMode) = chance(80) ? 0 : chance(80) ? 1 : random32();
    g.word(kFileMode) = chance(60) ? 0x100 : chance(80) ? 0x200 : random32();
    g.word(kUmask) = chance(70) ? 0 : chance(50) ? 0x80 : random32() & 0x1ff;

    x86::reg32 taken = 0;
    for (const x86::reg32 heap : miniheaps(g))
        taken |= 1u << (heap - kHeap) / kSlotSize;
    g.word(kSlotsTaken) = taken;
}

/* A string to look for in the string at `in`, written into a buffer: a piece
 * of it, a byte of it, nothing, or anything. */
x86::reg32 lookedFor(CheckApp& g, x86::reg32 in)
{
    const x86::reg32 buffer = aBuffer();
    x86::reg32 length = 0;
    while (g.getMemory<x86::reg8>(in + length) != 0)
        ++length;
    x86::reg32 from = in, count = 0;
    switch (below(5))
    {
    case 0: break;
    case 1: count = length ? 1 : 0; from = in + (length ? below(length) : 0); break;
    case 2: from = in + below(length + 1); count = below(length - (from - in) + 1); break;
    case 3: from = textString(below(32)); count = below(6); break;
    default: from = in + below(length + 1); count = below(length - (from - in) + 1); break;
    }
    for (x86::reg32 i = 0; i < count; ++i)
        g.getMemory<x86::reg8>(buffer + i) = g.getMemory<x86::reg8>(from + i);
    g.getMemory<x86::reg8>(buffer + count) = 0;
    if (count != 0 && chance(20))
        g.getMemory<x86::reg8>(buffer + below(count)) ^= 1;
    return buffer;
}

/* qsort's and bsearch's elements: `n` of `size` bytes at `base`, anything
 * but their keys -- the first dword or the first byte, as `function`
 * compares them -- which are from a few values, for ties, mostly the same,
 * or anything; or in its order, for bsearch. */
void makeElements(CheckApp& g, x86::reg32 base, x86::reg32 n, x86::reg32 size, x86::reg32 function, bool sorted)
{
    for (x86::reg32 at = kElements; at < base + n * size + 8; at += 4)
        g.word(at) = random32();
    const x86::reg32 kind = below(3);
    x86::reg32 key = function == kByByte ? below(0x40) : random32() >> (8 + below(20));
    for (x86::reg32 i = 0; i < n; ++i)
    {
        if (sorted)
            key += below(3);
        else
            key = kind == 0 ? below(4) : kind == 1 ? (chance(85) ? 1 : below(3)) : random32();
        if (function == kByByte)
            g.getMemory<x86::reg8>(base + i * size) = x86::reg8(std::min<x86::reg32>(key, 0xff));
        else
            g.word(base + i * size) = key;
    }
}

/* The Watcom runtime's functions' registers -- eax, edx, ebx, ecx -- and the
 * x87 for __CHP; `stack` the words on the stack. */
void makeWatcomArguments(CheckApp& g, const std::string& name, x86::CPU& cpu, x86::reg32* stack)
{
    const x86::reg32 i = below(32);
    static const char* const x87[] = {"CHP", "IF_DATAN2", "floor", "ceil", "modf", "control87", "IF_DEXP", "exp",
                                      "IF_DACOS", "DSQRT", "math87_err"};
    if (std::find_if(std::begin(x87), std::end(x87), [&](const char* n) { return name == n; }) != std::end(x87))
    {
        // The x87: a control word of every precision and rounding, a stack
        // of one to six, doubles of every kind on it.
        static const x86::reg16 precisions[] = {0x000, 0x200, 0x300};
        cpu.fpu.setControl(x86::reg16(0x7f | precisions[below(3)] | below(4) << 10 | (random32() & 0x1000)));
        cpu.fpu.count = name == "CHP" ? 1 + below(8) : 2 + below(5);
        for (x86::Float& f : cpu.fpu.regs)
            f = x86::Float(anyDouble());
        g.getMemory<x86::reg8>(0x567858) = 0;  // __chipbug: no Pentium with the FDIV bug
    }
    if (name == "IF_DACOS")
    {
        // Mostly in [-1, 1], 1 and -1 and 0 themselves; past them; anything.
        static const double edges[] = {1.0, -1.0, 0.0, -0.0, 1.0000001, -0.9999999};
        cpu.fpu.st(0) = x86::Float(chance(60) ? double(x86::sreg32(random32() % 2000001) - 1000000) / 1e6
                                   : chance(50) ? edges[below(6)] : anyDouble());
    }
    else if (name == "IF_DEXP" || name == "DSQRT")
    {
        // For exp either side of its limits, +-709.78; for sqrt below 0.
        if (name == "IF_DEXP" && chance(50))
            cpu.fpu.st(0) = x86::Float(double(x86::sreg32(random32() % 1600001) - 800000) / 1000.0);
        cpu.eax = chance(50) ? (random32() & 0xffffff00) | (chance(50) ? 3 : 1) : random32();
    }
    else if (name == "control87")
    {
        cpu.eax = random32();
        cpu.edx = chance(20) ? 0 : chance(30) ? 0xffff : random32() >> below(32);
        g.getMemory<x86::reg8>(0x5644c0) = chance(80) ? 3 : 0;  // _8087
    }
    else if (name == "floor" || name == "ceil" || name == "exp" || name == "modf" || name == "math87_err")
    {
        // A double on the stack -- for exp either side of its limits -- and
        // modf's pointer, or __math87_err's function.
        double value = anyDouble();
        if (name == "exp" && chance(50))
            value = double(x86::sreg32(random32() % 1600001) - 800000) / 1000.0;
        std::uint64_t bits;
        std::memcpy(&bits, &value, 8);
        stack[0] = x86::reg32(bits);
        stack[1] = x86::reg32(bits >> 32);
        if (name == "modf")
            stack[2] = aBuffer();
        else if (name == "math87_err")
            stack[2] = chance(80) ? below(8) : random32();
    }
    else if (name == "memset")
    {
        cpu.eax = aBuffer() + below(0x40);
        cpu.edx = random32();
        cpu.ebx = chance(10) ? 0 : below(chance(80) ? 0x40 : 0x1c0);
    }
    else if (name == "STOSB" || name == "STOSD")
    {
        cpu.eax = aBuffer() + below(0x40);
        cpu.edx = random32();
        cpu.ecx = chance(10) ? 0 : below(name == "STOSB" ? 0x1c0 : 0x70);
    }
    else if (name == "strcmp" || name == "stricmp" || name == "strncmp")
    {
        cpu.eax = textString(i);
        cpu.edx = chance(10) ? cpu.eax : chance(70) ? textString(i ^ 1) : aText();
        if (chance(50))
            std::swap(cpu.eax, cpu.edx);
        cpu.ebx = chance(10) ? 0 : chance(10) ? 0xffffffff : below(0x20);
    }
    else if (name == "strncpy" || name == "strncat")
    {
        cpu.eax = name == "strncat" ? copied(g, aText()) : aBuffer();
        cpu.edx = aText();
        cpu.ebx = chance(10) ? 0 : chance(10) ? 0xffffffff : below(0x100);
        if (name == "strncpy")
            cpu.ebx = std::min<x86::reg32>(cpu.ebx, 0x1f0);
    }
    else if (name == "strrchr")
    {
        cpu.eax = aText();
        const x86::reg32 length = x86::reg32(std::strlen(&g.getMemory<char>(cpu.eax)));
        cpu.edx = (random32() & 0xffffff00) | (chance(80) ? g.getMemory<x86::reg8>(cpu.eax + below(length + 1)) : below(256));
    }
    else if (name == "strstr")
    {
        cpu.eax = aText();
        cpu.edx = lookedFor(g, cpu.eax);
    }
    else if (name == "setbits" || name == "strtok")
    {
        static const char* const parts[] = {" ", " ,;", "\t\n ", "a", "", "0123456789", "Aa"};
        const x86::reg32 at = aBuffer() + 0x1c0;
        std::strcpy(&g.getMemory<char>(at), chance(70) ? parts[below(7)] : &g.getMemory<char>(textString(i) + below(4)));
        cpu.edx = at;
        cpu.eax = name == "setbits" ? aBuffer() + below(0x40) : chance(30) ? 0 : copied(g, aText());
    }
    else if (name == "strupr")
    {
        cpu.eax = copied(g, aText());
    }
    else if (name == "toupper" || name == "tolower")
    {
        cpu.eax = chance(70) ? below(256) : random32();
    }
    else if (name == "atoi" || name == "atol")
    {
        static const char* const numbers[] = {"0", "123", "-45", "+67", "  89x", "\t\n-2147483648", "4294967297",
                                              "99999999999", " - 5", "--3", "\xff" "5", "12\xff" "3", "", "+", "007"};
        const x86::reg32 at = aBuffer();
        std::strcpy(&g.getMemory<char>(at), chance(60) ? numbers[below(15)] : &g.getMemory<char>(aText()));
        cpu.eax = at;
    }
    else if (name == "srand")
    {
        cpu.eax = random32();
    }
    else if (name == "qsort" || name == "bsearch" || name == "med3")
    {
        // An array: of dwords mostly, aligned mostly; short, middling or long
        // -- either side of 16, 30 and 43 -- compared by its keys, or at random.
        static const x86::reg32 sizes[] = {4, 4, 4, 8, 12, 16, 1, 2, 3, 5, 6, 7, 20, 0};
        const x86::reg32 size = sizes[below(14)];
        const x86::reg32 base = kElements + (chance(25) ? 1 + below(3) : 0);
        static const x86::reg32 from[] = {0, 2, 2, 16, 30, 43, 43, 43, 43, 243};
        static const x86::reg32 more[] = {2, 14, 14, 14, 13, 200, 200, 200, 200, 1500};
        const x86::reg32 pick = below(10);
        x86::reg32 n = from[pick] + below(more[pick]);
        n = std::min<x86::reg32>(n, size == 0 ? 15 : 0xcff0 / size);
        const x86::reg32 function = chance(10) ? kAtRandom : size >= 4 && chance(75) ? kByDword : kByByte;
        makeElements(g, base, n, size, function, name == "bsearch" && chance(80));
        cpu.ecx = standInFor(function);
        if (name == "qsort")
        {
            cpu.eax = base;
            cpu.edx = n;
            cpu.ebx = size;
        }
        else if (name == "med3")
        {
            cpu.eax = base + below(n + 1) * size;
            cpu.edx = base + below(n + 1) * size;
            cpu.ebx = base + below(n + 1) * size;
        }
        else
        {
            // The key an element's, or one near them.
            const x86::reg32 element = base + below(n + 1) * size;
            g.word(kKey) = chance(60) ? g.word(element) : g.word(element) + below(3) - 1;
            cpu.eax = kKey;
            cpu.edx = base;
            cpu.ebx = n;
            cpu.ecx = size;
            stack[0] = standInFor(function);
        }
    }
    else if (name == "set_errno" || name == "set_doserrno")
    {
        cpu.eax = chance(70) ? below(20) : random32();
    }
    else if (name == "set_errno_dos")
    {
        cpu.eax = anError(random32());
    }
    else if (name == "unlink" || name == "remove" || name == "mkdir" || name == "rmdir" || name == "chdir"
             || name == "chmod" || name == "access" || name == "fixed_GetFileAttributesA")
    {
        // A path -- kStrings' have a * or a ? in them now and then -- and a mode.
        cpu.eax = aString();
        cpu.edx = name == "access" ? below(8) : random32();
    }
    else if (name == "getcwd")
    {
        // A buffer, short or long enough, or none.
        cpu.eax = chance(30) ? 0 : aBuffer();
        cpu.edx = chance(80) ? below(0x140) : random32() >> below(32);
        if (cpu.eax != 0)
            cpu.edx = std::min<x86::reg32>(cpu.edx, 0x1ff);
    }
    else if (name == "getdiskfree")
    {
        cpu.eax = chance(30) ? 0 : chance(80) ? 1 + below(26) : random32();
        cpu.edx = aBuffer();
    }
    else if (name == "lseek" || name == "tell" || name == "qread" || name == "qwrite" || name == "GetIOMode"
             || name == "fsync")
    {
        cpu.eax = aHandle();
        if (name == "lseek")
        {
            cpu.edx = chance(30) ? 0 : chance(50) ? below(0x1000) : random32();
            cpu.ebx = chance(80) ? below(3) : random32();
        }
        else if (name == "qread" || name == "qwrite")
        {
            cpu.edx = aBuffer();
            cpu.ebx = chance(10) ? 0 : below(0x200);
        }
    }
    else if (name == "fputc" || name == "fputs" || name == "fwrite" || name == "fflush" || name == "flush"
             || name == "ioalloc" || name == "chktty" || name == "flushall_" || name == "flushall")
    {
        // A stream -- for __ioalloc its buffer not made yet, mostly -- and
        // the heap now and then afresh; the default windowing now and then,
        // for __qwrite's nothing written that is no ENOSPC of its own.
        if (chance(10))
            freshHeap(g);
        if (chance(20))
        {
            g.word(kIsWindowedHandle) = standInFor(kIsWindowedHandle);
            g.word(kWindowsStdout) = standInFor(kWindowsStdout);
        }
        const x86::reg32 fp = aStream();
        if (name == "ioalloc" && chance(80))
        {
            g.word(g.word(fp + 8) + 8) = 0;
            if (chance(70))
                g.word(fp + 0x14) = 0;
        }
        cpu.eax = fp;
        if (name == "fputc")
        {
            // A character: a newline often, with bits above it now and then.
            cpu.eax = chance(20) ? '\n' : chance(5) ? (random32() & ~0xffu) | '\n' : chance(80) ? below(256) : random32();
            cpu.edx = fp;
        }
        else if (name == "fputs")
        {
            cpu.eax = aText();
            cpu.edx = fp;
        }
        else if (name == "fwrite")
        {
            // Up to 2K, a byte at a time or more; none, by n or by size; or
            // n times size 0 as it wraps.
            cpu.eax = chance(50) ? aText() : aBuffer();
            cpu.edx = chance(40) ? 1 : 1 + below(16);
            cpu.ebx = chance(30) ? 1 + below(8) : below(0x80);
            if (chance(5))
                cpu.edx = 0;
            else if (chance(5))
            {
                const bool half = chance(50);
                cpu.edx = half ? 0x80000000 : 4;
                cpu.ebx = half ? 2 : 0x40000000;
            }
            cpu.ecx = fp;
        }
        else if (name == "fflush")
        {
            cpu.eax = chance(25) ? 0 : fp;
        }
        else if (name == "flushall_")
        {
            static const x86::reg32 masks[] = {1, 2, 3, 0x40, 0x1000, 0x2000, 0xffffffff, 0};
            cpu.eax = chance(70) ? masks[below(8)] : random32();
        }
    }
    else if (name == "fgetc" || name == "filbuf" || name == "fill_buffer" || name == "fread" || name == "fgets"
             || name == "fseek" || name == "ftell" || name == "update_buffer" || name == "reset_buffer")
    {
        // A stream open for reading mostly -- stdin often -- and the heap
        // now and then afresh.
        if (chance(10))
            freshHeap(g);
        const x86::reg32 fp = chance(15) ? kIob : aStream();
        if (chance(name == "fseek" || name == "ftell" ? 50 : 80))
            g.word(fp + 0xc) = (g.word(fp + 0xc) | 1) & (chance(50) ? ~2u : ~0u);
        cpu.eax = fp;
        if (name == "fread")
        {
            // Up to 2K, into a buffer with room for it, as for fwrite.
            cpu.eax = kBuffers + 0x200 * below(12);
            cpu.edx = chance(40) ? 1 : 1 + below(16);
            cpu.ebx = chance(30) ? 1 + below(8) : below(0x80);
            if (chance(5))
                cpu.edx = 0;
            else if (chance(5))
            {
                const bool half = chance(50);
                cpu.edx = half ? 0x80000000 : 4;
                cpu.ebx = half ? 2 : 0x40000000;
            }
            cpu.ecx = fp;
        }
        else if (name == "fgets")
        {
            // Room for a few bytes or a line, for none, or less than none.
            cpu.eax = kBuffers + 0x200 * below(15);
            cpu.edx = chance(10) ? below(2) : chance(5) ? 0xfffffffe + below(2) : 1 + below(0x200);
            cpu.ebx = fp;
            // The dword of its frame fgetc's result goes into: for none, -1
            // as often as not.
            g.word(cpu.esp - 0x14) = chance(50) ? 0xffffffff : random32();
        }
        else if (name == "fseek")
        {
            // Near where the buffer has it, from any whence, or anywhere.
            cpu.edx = chance(40) ? x86::reg32(x86::sreg32(below(0x800)) - 0x400)
                      : chance(30) ? below(0x800) : chance(50) ? 0 : random32();
            cpu.ebx = chance(90) ? below(3) : chance(50) ? 3 + below(5) : random32();
        }
        else if (name == "update_buffer")
        {
            cpu.eax = chance(80) ? x86::reg32(x86::sreg32(below(0x800)) - 0x400) : random32();
            cpu.edx = fp;
        }
    }
    else if (name == "fopen" || name == "fsopen" || name == "open_flags" || name == "doopen" || name == "sopen"
             || name == "sopen_" || name == "allocfp" || name == "freefp" || name == "doclose"
             || name == "shutdown_stream" || name == "fclose" || name == "close" || name == "handlesFull"
             || name == "allocPOSIXHandle" || name == "freePOSIXHandle" || name == "NTGetFakeHandle"
             || name == "GetNTAccessAttr" || name == "GetNTShareAttr")
    {
        // A path -- "con" now and then -- a mode string, open's flags and
        // sharing, a stream, a handle; the heap now and then afresh.
        if (chance(10))
            freshHeap(g);
        static const char* const modes[] = {"r", "w", "a", "r+", "w+", "a+", "rb", "wb", "ab", "rt", "r+b", "wb+",
                                            "rc", "wn", "a+c", "rbt", "r++b", "a++c", "wcn", "rbx", "x", "", "R", "wtc"};
        static const char* const consoles[] = {"con", "CON", "Con", "con:"};
        const x86::reg32 path = chance(85) ? aString() : aBuffer() + 0x1e0;
        if (path >= kBuffers)
            std::strcpy(&g.getMemory<char>(path), consoles[below(4)]);
        const x86::reg32 mode = aBuffer() + 0x1f0;
        std::strcpy(&g.getMemory<char>(mode), modes[below(24)]);
        static const x86::reg32 sharings[] = {0, 0x10, 0x20, 0x30, 0x40, 0x50};
        const x86::reg32 shflag = chance(90) ? sharings[below(6)] : random32();
        x86::reg32 oflag = below(4) | (chance(30) ? 0x10 : 0) | (chance(50) ? 0x20 : 0) | (chance(30) ? 0x40 : 0)
                           | (chance(20) ? 0x80 : 0) | (chance(40) ? 0x100 : 0) | (chance(40) ? 0x200 : 0)
                           | (chance(20) ? 0x400 : 0);
        if (chance(5))
            oflag = random32();
        const x86::reg32 permission = chance(70) ? 0x180 : chance(50) ? 0x100 : random32();
        const x86::reg32 fp = aStream();
        if (name == "fopen" || name == "fsopen" || name == "open_flags")
        {
            // _fsopen's sharing one of the five: for another __GetNTShareAttr
            // leaves CreateFileA's as the frame had it, which only the game's
            // code before it in the stack says -- and the game opens with 0.
            cpu.eax = name == "open_flags" ? mode : path;
            cpu.edx = name == "open_flags" ? (chance(90) ? aBuffer() : 0) : mode;
            cpu.ebx = sharings[below(5)];
        }
        else if (name == "doopen")
        {
            static const char firsts[] = "rwaRWAx";
            cpu.eax = path;
            cpu.edx = (random32() & 0xffffff00) | x86::reg8(firsts[below(7)]);
            cpu.ebx = chance(90) ? below(4) | (chance(30) ? 0x40 : 0) | (chance(30) ? 0x80 : 0) : random32();
            cpu.ecx = chance(70) ? below(2) : random32();
            stack[0] = shflag;
            stack[1] = fp;
        }
        else if (name == "sopen")
        {
            stack[0] = path;
            stack[1] = oflag;
            stack[2] = shflag;
            stack[3] = permission;
        }
        else if (name == "sopen_")
        {
            // The va_list: a dword of a buffer, pointing at the permissions.
            const x86::reg32 args = aBuffer() + 0x1c0;
            g.word(args) = args + 4;
            g.word(args + 4) = permission;
            cpu.eax = path;
            cpu.edx = oflag;
            cpu.ebx = shflag;
            cpu.ecx = args;
        }
        else if (name == "freefp" || name == "fclose" || name == "doclose" || name == "shutdown_stream")
        {
            // fclose and __freefp look for the stream: one not open now and then.
            cpu.eax = (name == "fclose" || name == "freefp") && chance(10) ? aBuffer() : fp;
            cpu.edx = chance(70) ? 1 : chance(50) ? 0 : random32();
        }
        else if (name == "close")
        {
            cpu.eax = aHandle();
        }
        else if (name == "allocPOSIXHandle")
        {
            cpu.eax = random32();
        }
        else if (name == "freePOSIXHandle")
        {
            cpu.eax = chance(80) ? below(34) : chance(50) ? 0xffffffff : random32();
        }
        else if (name == "GetNTAccessAttr" || name == "GetNTShareAttr")
        {
            cpu.eax = name == "GetNTAccessAttr" ? (chance(80) ? below(4) : random32())
                                                : (chance(80) ? below(8) << 4 | below(4) : random32());
            cpu.edx = aBuffer();
            cpu.ebx = cpu.edx + 4;
        }
        else
        {
            cpu.eax = random32();
        }
    }
    else if (name == "SetIOMode" || name == "isatty")
    {
        // Neither looks at the handle: one of the 20, or 20 itself.
        cpu.eax = below(21);
        cpu.edx = chance(20) ? 0 : random32();
    }
    else if (name == "leapyear")
    {
        cpu.eax = chance(80) ? 1600 + below(1000) : random32();
    }
    else if (name == "brktime")
    {
        // Days since 1900, 1970's mostly; a time_t; a zone either side of the
        // seconds' turning point; a struct tm.
        cpu.eax = chance(70) ? 0x63df : below(0x10000);
        cpu.edx = chance(30) ? below(0x15180) : random32();
        cpu.ebx = chance(70) ? x86::reg32(3600 * (x86::sreg32(below(25)) - 12)) : random32();
        cpu.ecx = aBuffer();
    }
    else if (name == "time_less")
    {
        // Two times of day, often the same in part.
        cpu.eax = aBuffer();
        cpu.edx = cpu.eax + 0x40;
        for (const x86::reg32 tm : {cpu.eax, cpu.edx})
            for (x86::reg32 i = 0; i < 3; ++i)
                g.word(tm + 4 * i) = chance(10) ? random32() : below(3);
    }
    else if (name == "calc_yday" || name == "check_order")
    {
        cpu.eax = aBuffer();
        cpu.edx = cpu.eax + 0x40;
        makeRule(g, cpu.eax);
        makeRule(g, cpu.edx);
        const x86::reg32 year = chance(90) ? 70 + below(70) : below(200);
        if (name == "calc_yday")
            cpu.edx = year;
        else
            cpu.ebx = year;
    }
    else if (name == "isindst")
    {
        // A struct tm as mktime and _localtime leave one: in range, and
        // its month near it, which the runtime indexes by.
        cpu.eax = aBuffer();
        makeTm(g, cpu.eax);
        g.word(cpu.eax + 0x10) = chance(95) ? below(12) : below(14) - 1;
        g.word(cpu.eax + 0x14) = chance(90) ? 70 + below(70) : below(200);
        // Now and then on the day of the year a rule's Jn or n says, or
        // either side of it, in a leap year as often as not.
        if (chance(30))
        {
            g.word(cpu.eax + 0x1c) = g.word((chance(50) ? kDstStart : kDstEnd) + 0x1c) + below(3) - 1;
            if (chance(50))
                g.word(cpu.eax + 0x14) = 72 + 4 * below(17);
        }
    }
    else if (name == "mktime" || name == "getctime")
    {
        // For mktime now and then a day either side of 1970's first, where a
        // zone west still has a time_t.
        cpu.eax = aBuffer();
        makeTm(g, cpu.eax);
        if (name == "mktime" && chance(15))
        {
            const bool before = chance(50);
            g.word(cpu.eax + 0x14) = before ? 69 : 70;
            g.word(cpu.eax + 0x10) = before ? 11 : 0;
            g.word(cpu.eax + 0xc) = before ? 31 : 1;
            g.word(cpu.eax + 8) = below(24);
        }
    }
    else if (name == "time")
    {
        cpu.eax = chance(30) ? 0 : aBuffer();
    }
    else if (name == "localtime" || name == "localtime_")
    {
        // A time_t, and for _localtime a struct tm.
        cpu.eax = aBuffer();
        g.word(cpu.eax) = chance(70) ? 0x30000000 + below(0x20000000) : random32();
        cpu.edx = cpu.eax + 0x40;
    }
    else if (name == "byteswap")
    {
        // Two places -- apart, the same, or overlapping -- and a count.
        for (x86::reg32 at = kElements; at < kElements + 0x300; at += 4)
            g.word(at) = random32();
        cpu.esi = kElements + below(0x100);
        cpu.edi = chance(20) ? cpu.esi : kElements + below(0x200);
        cpu.ecx = chance(10) ? 0 : below(0x80);
    }
    else if (name == "nmalloc" || name == "CreateNewNHeap" || name == "ExpandDGROUP" || name == "nmemneed")
    {
        cpu.eax = anAmount();
    }
    else if (name == "nfree")
    {
        // A block it gave, none, or memory no miniheap has.
        cpu.eax = !g_blocks.empty() && chance(85) ? takeBlock() : chance(50) ? 0 : aBuffer() + below(0x200);
    }
    else if (name == "MemAllocator")
    {
        // An amount from a miniheap -- none where there is none; edx the segment, anything.
        const std::vector<x86::reg32> heaps = miniheaps(g);
        cpu.edx = random32();
        if (!heaps.empty())
        {
            cpu.ebx = heaps[below(x86::reg32(heaps.size()))];
            cpu.eax = anAmount();
        }
        else
        {
            cpu.eax = 0;
        }
    }
    else if (name == "MemFree")
    {
        // A block it gave and its miniheap, or none.
        cpu.edx = random32();
        cpu.eax = !g_blocks.empty() && chance(90) ? takeBlock() : 0;
        if (cpu.eax != 0)
        {
            cpu.ebx = heapHolding(g, cpu.eax);
            if (cpu.ebx == 0)
                cpu.eax = 0;
        }
    }
    else if (name == "AdjustAmount")
    {
        cpu.eax = aBuffer() + 4 * below(0x10);
        g.word(cpu.eax) = chance(70) ? anAmount() : random32();
        // _amblksiz other than 64K: anything, a few bytes, odd past a page, all but 4 GB.
        if (chance(40))
        {
            const x86::reg32 sizes[] = {random32() >> below(32), below(0x40), 0x1000 * below(0x100) + 1,
                                        0xffffffff - below(0x2000)};
            g.word(kHeapBlockSize) = sizes[below(4)];
        }
    }
    else if (name == "LinkUpNewNHeap")
    {
        // A slot no miniheap has, or memory of the harness's if none is free,
        // its length as __CreateNewNHeap writes it.
        const x86::reg32 taken = g.word(kSlotsTaken);
        x86::reg32 heap = kSamples;
        if (taken != 0xff)
        {
            x86::reg32 slot = below(8);
            while (taken >> slot & 1)
                slot = (slot + 1) % 8;
            heap = kHeap + kSlotSize * slot;
        }
        g.word(heap) = 0x1000 * (1 + below(0x14)) - 4;
        cpu.eax = heap;
    }
    else if (name == "ReturnMemToSystem" || name == "ReleaseNHeap")
    {
        const std::vector<x86::reg32> heaps = miniheaps(g);
        cpu.eax = heaps.empty() ? 0 : heaps[below(x86::reg32(heaps.size()))];
    }
}

/* `from` to `to` made up, a dword at a time: now and then, words at either
 * end of their range, for the saturations. */
void makeSamples(CheckApp& g, x86::reg32 from, x86::reg32 to)
{
    const int loud = chance(50) ? 0 : 25;
    for (x86::reg32 at = from & ~3u; at < to; at += 4)
    {
        g.word(at) = random32();
        if (loud && chance(loud))
            g.getMemory<x86::reg16>(at + 2 * below(2)) = x86::reg16(chance(50) ? 0x7fff - below(2) : 0x8000 + below(2));
    }
}

/* An MMX register's 64 bits: their lanes at their ends now and then. */
x86::reg64 anMmxValue()
{
    static const x86::reg64 edges[] = {0, ~0ull, 0x7fff7fff7fff7fffull, 0x8000800080008000ull, 0x0000ffff0000ffffull,
                                       0x8080808080808080ull};
    return chance(20) ? edges[below(6)] : random32() | x86::reg64(random32()) << 32;
}

/* A count about a block's size: none, a few, whole blocks, one either side,
 * any; a few below 0 now and then, which the x86's signed loops take as
 * their code says. */
x86::reg32 aCount(x86::reg32 block, x86::reg32 most)
{
    if (chance(15))
        return below(2 * block + 2);
    if (chance(6))
        return 0 - (1 + below(2 * block));
    if (chance(30))
        return block * (1 + below(most / block)) + below(3) - 1;
    return 1 + below(most);
}

/* The MMX functions' arguments -- cdecl but for the memmove's copy, in eax,
 * edx and ebx -- their buffers made up, and the MMX registers, which they read
 * before they set some. */
void makeMmxArguments(CheckApp& g, const std::string& name, x86::CPU& cpu, x86::reg32* stack)
{
    cpu.mmx.mm0 = x86::from_reg64(anMmxValue());
    cpu.mmx.mm1 = x86::from_reg64(anMmxValue());
    cpu.mmx.mm2 = x86::from_reg64(anMmxValue());
    cpu.mmx.mm3 = x86::from_reg64(anMmxValue());
    cpu.mmx.mm4 = x86::from_reg64(anMmxValue());
    cpu.mmx.mm5 = x86::from_reg64(anMmxValue());
    cpu.mmx.mm6 = x86::from_reg64(anMmxValue());
    cpu.mmx.mm7 = x86::from_reg64(anMmxValue());
    makeSamples(g, kMmxState, kMmxState + 0x200);
    const auto frames = [](x86::reg32 count, x86::reg32 block) {
        // As many as a count's loops reach, below 0 and over included.
        return (x86::sreg32(count) < 0 ? 0 - count : count) + 2 * block + 1;
    };
    if (name.compare(0, 3, "add") == 0)
    {
        // (volumes, count, source, accumulator)
        const x86::reg32 block = name == "addStereo16" ? 8 : 4;
        const x86::reg32 count = aCount(block, 0x200);
        const x86::reg32 size = name == "addMono8" ? 1 : name == "addStereo16" ? 4 : 2;
        stack[0] = kMmxState + 8 * below(0x30);
        stack[1] = count;
        stack[2] = kMmxSource + below(0x100);
        stack[3] = kMmxTarget + below(0x100);
        makeSamples(g, stack[2], stack[2] + size * frames(count, block) + 8);
        makeSamples(g, stack[3], stack[3] + 4 * frames(count, block) + 8);
    }
    else if (name.compare(0, 6, "output") == 0)
    {
        // (frames, accumulator, output), from the end: stereo 16 frames at a time.
        const x86::reg32 count = aCount(16, 0x200);
        stack[0] = count;
        stack[1] = kMmxTarget + 0x100 + 4 * below(0x40);
        stack[2] = kMmxOutput + 0x100 + below(0x100);
        makeSamples(g, stack[1] - 0x100, stack[1] + 4 * frames(count, 16));
        makeSamples(g, stack[2] - 0x100, stack[2] + 4 * frames(count, 16));
    }
    else if (name == "clear")
    {
        // (accumulator, dwords): 16 at a time while more than 15 are left
        stack[0] = kMmxTarget + below(0x100);
        stack[1] = aCount(16, 0x400);
        makeSamples(g, stack[0], stack[0] + 4 * frames(stack[1], 16));
    }
    else if (name.compare(0, 11, "interpolate") == 0)
    {
        // (frames, source, output, the whole position's dword, the fraction's,
        // the step's whole, its fraction): positions from 0x200, steps of up
        // to 8 and back by 1, never before the source.
        static const x86::reg32 fractions[] = {0, 0xffffffff, 0x80000000, 0xffff, 0x10000, 1};
        stack[0] = chance(10) ? below(3) : chance(5) ? 0 - (1 + below(4)) : 1 + below(0x100);
        stack[1] = kMmxSource + below(0x100);
        stack[2] = kMmxOutput + below(0x100);
        stack[3] = kMmxState + 0x80 + 4 * below(8);
        stack[4] = kMmxState + 0xa0 + 4 * below(8);
        stack[5] = chance(70) ? below(3) : chance(50) ? 0xffffffff : below(8);
        stack[6] = chance(25) ? fractions[below(6)] : random32();
        g.word(stack[3]) = 0x200 + below(0x100);
        g.word(stack[4]) = chance(25) ? fractions[below(6)] : random32();
        makeSamples(g, stack[1], stack[1] + 4 * (0x300 + 0x100 * 8) + 8);
        makeSamples(g, stack[2], stack[2] + 4 * 0x100 + 8);
    }
    else if (name.compare(0, 2, "xa") == 0)
    {
        // (the decoder's state): samples left, the history, the source and
        // the output; whole blocks of 28 samples, 15 bytes each in mono, 30 in
        // stereo; the table of nibbles the game makes, made up.
        const bool stereo = name == "xaStereo";
        const x86::reg32 state = kMmxState + 0x100 + 4 * below(8);
        const x86::reg32 samples = chance(10) ? 0 : chance(5) ? 0 - below(100) - 1 : chance(30) ? 28 * (1 + below(12))
                                                                                                 : 1 + below(28 * 12);
        const x86::reg32 blocks = x86::sreg32(samples) > 0 ? (samples + 27) / 28 : 0;
        const x86::reg32 source = kMmxSource + below(0x100), target = kMmxTarget + below(0x100);
        g.word(state) = samples;
        g.word(state + (stereo ? 0xc : 8)) = source;
        g.word(state + (stereo ? 0x10 : 0xc)) = target;
        makeSamples(g, source, source + (stereo ? 30 : 15) * blocks + 8);
        makeSamples(g, target, target + (stereo ? 0x70 : 0x38) * blocks + 8);
        for (x86::reg32 at = kXaNibbles; at < kXaNibbles + 0x400; at += 4)
            g.word(at) = random32();
        stack[0] = state;
    }
    else if (name == "copy" || name == "copySwapped")
    {
        // eax to, edx from, ebx bytes -- the other way round for copySwapped:
        // aligned any way, into another buffer or over the source either side.
        const x86::reg32 count = chance(20) ? below(0x24) : chance(15) ? 0x60 + below(0x40) : chance(5)
                                     ? 0 - (1 + below(8)) : chance(10) ? 0x80 * (1 + below(8)) + below(3) - 1
                                     : below(0x900);
        const x86::reg32 from = kMmxSource + 0x100 + below(0x100);
        const x86::reg32 to = chance(25) ? from + below(0x100) - 0x80 : kMmxTarget + below(0x100);
        makeSamples(g, from - 0x100, from + 0x100 + (x86::sreg32(count) < 0 ? 0 : count));
        if (to >= kMmxTarget)
            makeSamples(g, to, to + 0x10 + (x86::sreg32(count) < 0 ? 0 : count));
        cpu.eax = name == "copy" ? to : from;
        cpu.edx = name == "copy" ? from : to;
        cpu.ebx = count;
    }
}

/* The function's arguments, on the stack at esp + 4 on, and its registers. */
void makeArguments(CheckApp& g, const Tested& t, x86::reg32 esp, x86::CPU& cpu)
{
    x86::reg32 a[9];
    for (x86::reg32& w : a)
        w = random32();
    const std::string name = t.name;
    if (name == "Error" || name == "Message" || name == "PrintSoundLambda" || name == "TraceSoundLambda"
        || name == "abortmessagewrapper")
    {
        a[0] = chance(10) ? 0 : aString();
    }
    else if (name == "THRASH_opendll")
    {
        cpu.eax = aString();
    }
    else if (name == "audiofocushandler")
    {
        cpu.eax = chance(50) ? 0 : random32();
    }
    else if (name == "iSNDconvertsample")
    {
        static const x86::reg32 representations[] = {0, 2, 3, 3, 1, 4};
        static const x86::reg32 channelCounts[] = {1, 1, 2, 2, 0, 3};
        const x86::reg32 frames = chance(8) ? 0 : chance(5) ? 0xffffffff : 1 + below(0x400);
        const x86::reg32 span = frames == 0xffffffff ? 1 : frames + 1;
        a[0] = kSamples + 4 * below(0x100);
        a[1] = chance(95) ? representations[below(6)] : random32();
        a[2] = chance(95) ? channelCounts[below(6)] : random32();
        a[3] = below(span);
        a[4] = chance(40) ? 0 : chance(10) ? 0xffffffff : a[3] + below(span - a[3]);
        a[5] = frames;
        a[6] = kSamples + 0x8000 + 4 * below(0x100);
        a[7] = chance(80) ? 0 : below(3);
        a[8] = chance(85) ? 1 : below(3);
    }
    if (name.compare(0, 8, "watcom::") == 0)
        makeWatcomArguments(g, name.substr(8), cpu, a);
    if (name.compare(0, 5, "mmx::") == 0)
        makeMmxArguments(g, name.substr(5), cpu, a);
    for (x86::reg32 i = 0; i < 9; ++i)
        g.word(esp + 4 + 4 * i) = a[i];
}

bool compareRuns(const Tested& t, CheckApp& g, CheckApp& n, const x86::CPU& generatedCpu,
                 const x86::CPU& nativeCpu, x86::reg32 esp, Counts& counts);

/* One case of one function: the state made up on `g`, copied to `n`, then
 * both run and compared. */
bool runCase(const Tested& t, CheckApp& g, CheckApp& n, Counts& counts)
{
    ++counts.cases;
    const Promise& p = *promiseOf(t.name);
    g_seed = mix(random32() | std::uint64_t(random32()) << 32);
    g_stopAt = -1;
    makeState(g);
    if (p.heap != kNoHeap)
        stirHeap(g);
    for (x86::reg32 at = kStackLow; at < kStackHigh; at += 4)
        g.word(at) = random32();
    const x86::reg32 esp = kStackHigh - 0x1000 - 4 * below(64);
    g.word(esp) = 0xdead0000;  // the return address's slot

    x86::CPU cpu{};
    cpu.eax = random32();
    cpu.ebx = random32();
    cpu.ecx = random32();
    cpu.edx = random32();
    cpu.esi = random32();
    cpu.edi = random32();
    cpu.ebp = random32();
    cpu.esp = esp;
    makeArguments(g, t, esp, cpu);

    // The heap's list, for those that leave it as the game would not.
    std::vector<std::pair<x86::reg32, x86::reg32>> list;
    if (p.heap == kRestored)
    {
        for (const x86::reg32 at : {kHeapFirst, kHeapRover, kHeapLargestBefore, kHeapFreeRover})
            list.push_back({at, g.word(at)});
        for (const x86::reg32 heap : miniheaps(g))
            for (const x86::reg32 at : {heap + 4, heap + 8})
                list.push_back({at, g.word(at)});
    }

    g_stopAt = chance(15) ? long(below(p.heap != kNoHeap || chance(50) ? 8 : 40)) : -1;
    g_lookupFails = chance(30);

    copyWindows(n, g);
    g.calls.clear();
    n.calls.clear();

    x86::CPU nativeCpu = cpu, generatedCpu = cpu;
    win32::g_running = &n;
    t.native(&n, nativeCpu);
    win32::g_running = &g;
    t.generated(&g, generatedCpu);

    const bool alike = compareRuns(t, g, n, generatedCpu, nativeCpu, esp, counts);
    for (const auto& word : list)
        g.word(word.first) = word.second;
    if ((p.name == std::string("watcom::nmalloc") || p.name == std::string("watcom::MemAllocator")
         || (p.name == std::string("watcom::getcwd") && cpu.eax == 0))
        && !generatedCpu.terminate && generatedCpu.eax != 0)
        g_blocks.push_back(generatedCpu.eax);
    keepHeapSound(g);
    return alike;
}

/* The two runs of a case, alike or not. */
bool compareRuns(const Tested& t, CheckApp& g, CheckApp& n, const x86::CPU& generatedCpu,
                 const x86::CPU& nativeCpu, x86::reg32 esp, Counts& counts)
{
    char what[400];
    const bool stopped = generatedCpu.terminate;
    if (stopped)
        ++counts.stopped;
    if (nativeCpu.terminate != generatedCpu.terminate)
        return report(counts, "stopped in one run only");
    if (!(g.calls == n.calls))
    {
        int at = std::snprintf(what, sizeof what, "calls out: %zu generated, %zu native", g.calls.size(),
                               n.calls.size());
        for (size_t i = 0; i < g.calls.size() && i < n.calls.size(); ++i)
            if (!(g.calls[i] == n.calls[i]))
            {
                const Call& a = g.calls[i];
                const Call& b = n.calls[i];
                at += std::snprintf(what + at, sizeof what - at, "; call %zu: %08x (", i, a.id);
                for (size_t j = 0; j < a.words.size() && j < 8; ++j)
                    at += std::snprintf(what + at, sizeof what - at, " %08x", a.words[j]);
                at += std::snprintf(what + at, sizeof what - at, ") generated, %08x (", b.id);
                for (size_t j = 0; j < b.words.size() && j < 8; ++j)
                    at += std::snprintf(what + at, sizeof what - at, " %08x", b.words[j]);
                std::snprintf(what + at, sizeof what - at, ") native");
                break;
            }
        return report(counts, what);
    }
    if (!stopped)
    {
        const Promise& p = *promiseOf(t.name);
        const bool kept[] = {false, !p.watcom || p.arguments < 2, !p.watcom || p.arguments < 3,
                             p.watcom && p.arguments < 4};  // eax, edx, ebx, ecx as handed over
        const struct { const char* name; x86::reg32 g, n; bool compared; } registers[] = {
            {"eax", generatedCpu.eax, nativeCpu.eax, p.result}, {"ebx", generatedCpu.ebx, nativeCpu.ebx, kept[2]},
            {"ecx", generatedCpu.ecx, nativeCpu.ecx, kept[3]}, {"edx", generatedCpu.edx, nativeCpu.edx, kept[1] && p.watcom},
            {"esi", generatedCpu.esi, nativeCpu.esi, true}, {"edi", generatedCpu.edi, nativeCpu.edi, true},
            {"ebp", generatedCpu.ebp, nativeCpu.ebp, true}, {"esp", generatedCpu.esp, nativeCpu.esp, true},
        };
        for (const auto& r : registers)
            if (r.compared && r.g != r.n)
            {
                std::snprintf(what, sizeof what, "%s %08x generated, %08x native", r.name, r.g, r.n);
                return report(counts, what);
            }
        const x86::regmmx* const mmx[2][8] = {
            {&generatedCpu.mmx.mm0, &generatedCpu.mmx.mm1, &generatedCpu.mmx.mm2, &generatedCpu.mmx.mm3,
             &generatedCpu.mmx.mm4, &generatedCpu.mmx.mm5, &generatedCpu.mmx.mm6, &generatedCpu.mmx.mm7},
            {&nativeCpu.mmx.mm0, &nativeCpu.mmx.mm1, &nativeCpu.mmx.mm2, &nativeCpu.mmx.mm3, &nativeCpu.mmx.mm4,
             &nativeCpu.mmx.mm5, &nativeCpu.mmx.mm6, &nativeCpu.mmx.mm7}};
        for (unsigned i = 0; i < 8; ++i)
            if (x86::reg64(*mmx[0][i]) != x86::reg64(*mmx[1][i]))
            {
                std::snprintf(what, sizeof what, "mm%u %016llx generated, %016llx native", i,
                              (unsigned long long)x86::reg64(*mmx[0][i]), (unsigned long long)x86::reg64(*mmx[1][i]));
                return report(counts, what);
            }
        if (generatedCpu.fpu.count != nativeCpu.fpu.count)
            return report(counts, "the FPU's stack left otherwise");
        if (p.fpu)
        {
            if (generatedCpu.fpu.control.word != nativeCpu.fpu.control.word)
                return report(counts, "the FPU's control word left otherwise");
            if (generatedCpu.fpu.status.word != nativeCpu.fpu.status.word)
                return report(counts, "the FPU's status word left otherwise");
            for (x86::reg32 i = 0; i < 8; ++i)
                if (floatBits(generatedCpu.fpu.regs[i]) != floatBits(nativeCpu.fpu.regs[i]))
                {
                    std::snprintf(what, sizeof what, "the FPU's register %u: %s generated, %s native", unsigned(i),
                                  floatBits(generatedCpu.fpu.regs[i]).c_str(), floatBits(nativeCpu.fpu.regs[i]).c_str());
                    return report(counts, what);
                }
        }
    }
    for (const auto& w : kWindows)
    {
        const x86::reg32 from = w.first == kStackLow ? esp : w.first;
        const x86::reg32 at = firstDifference(g, n, from, w.second);
        if (at != w.second)
        {
            std::snprintf(what, sizeof what, "memory at %08x: %02x generated, %02x native", at, *bytes(g, at),
                          *bytes(n, at));
            return report(counts, what);
        }
    }
    return true;
}

}  // namespace

int main(int argc, char** argv)
{
    const unsigned cases = argc > 1 ? unsigned(std::strtoul(argv[1], nullptr, 10)) : 20000;
    // mutations.py's: stop at the first case that fails, and check one function.
    const bool stopAtFirst = argc > 2 && std::strcmp(argv[2], "--first") == 0;
    const char* only = argc > 3 ? argv[3] : nullptr;
    CheckApp g(true), n(false);
    for (CheckApp* app : {&g, &n})
    {
        for (unsigned i = 0; i < kGameSegmentCount; ++i)
            std::memcpy(bytes(*app, kGameSegments[i].address), kGameSegments[i].bytes, kGameSegments[i].length);
        // The imports' slots point at their stand-ins.
        for (unsigned i = 0; i < kPointerCount; ++i)
            if (kPointers[i].address < 0x535000)
                app->word(kPointers[i].address) = kStandIns + 0x10 * i;
        for (x86::reg32 i = 0; i < 64; ++i)
            app->text(kStrings + 0x40 * i, i % 0x3f, mix(i));
    }
    // native_game.cpp's strings are where it says.
    if (std::strcmp(&g.getMemory<char>(0x549c60), "eacsnd.dll") != 0
        || std::strcmp(&g.getMemory<char>(0x54d3a0), "%sa") != 0)
    {
        std::printf("the game's data is not where native_game.cpp has it\n");
        return 2;
    }
    // Nor the runtime's heap where native_watcom_heap.cpp has it: an empty
    // heap, growing by 64K, its lock a bare ret.
    if (g.word(kHeapFirst) != 0 || g.word(kHeapEnabled) != 1 || g.word(kHeapBlockSize) != 0x10000
        || g.word(kHeapAccess) != kNullAccess || g.word(kHeapRelease) != kNullAccess)
    {
        std::printf("the game's data is not where native_watcom_heap.cpp has it\n");
        return 2;
    }

    for (const Tested& t : kTested)
        if (!promiseOf(t.name))
        {
            std::printf("%s: no promise of its registers here\n", t.name);
            return 2;
        }

    bool failed = false;
    for (const Tested& t : kTested)
    {
        if (only && std::strcmp(only, t.name) != 0)
            continue;
        Counts counts;
        g_name = t.name;
        for (g_case = 0; g_case < cases; ++g_case)
        {
            if (!runCase(t, g, n, counts) && stopAtFirst)
                return 1;
            // Both memories alike again, the dead stack included, for the next case.
            copyWindows(n, g);
            if (g_case % 2000 == 1999 || g_case + 1 == cases)
            {
                const x86::reg32 at = firstDifference(g, n, 0, kMemory);
                if (at != kMemory)
                {
                    std::printf("  %s: memory at %08x written outside the windows\n", t.name, at);
                    ++counts.failed;
                    std::memcpy(bytes(n, 0), bytes(g, 0), kMemory);
                }
            }
        }
        std::printf("%-34s %7u cases, %5u stopped the game -- %u failed\n", t.name, counts.cases, counts.stopped,
                    counts.failed);
        failed = failed || counts.failed != 0;
    }
    std::printf(failed ? "FAILED\n" : "all alike\n");
    return failed ? 1 : 0;
}
