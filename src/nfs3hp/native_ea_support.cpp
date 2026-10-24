#include "native_guest.h"

/* EA's trace and log, files loaded whole into memory, and .viv archives.  disassemble_nfs3hp.py binds each
 * address to the function of that name here (EA_SUPPORT_NATIVES), and the
 * generated code calls it by name.  tools/game_checks holds each against its
 * generated code.
 *
 * The trace: EA's monochrome monitor, text written straight into a
 * second display's text page of 80 by 25 cells of two bytes (the character,
 * its attribute) -- the page at 0x5644d0 (0xb0000 + 0x8000 a page, as
 * monoPage sets it), the cursor's byte offset into it at 0x5644d4, the top
 * row of the scrolling window at 0x5644d8, the attribute written at 0x5644d9,
 * the tab's width at 0x5644da.  It only writes while the trace's level
 * (0x5644c8) is 2 or more, under a lock of its own (0x5644c4, made as it is
 * first wanted, 0x4eb2e0).  The text understands backspace, tab, newline
 * (scrolling the window at the bottom), 0x0b (to the window's top) and 0x0c
 * (the page cleared), and 0x0e, the attribute in the byte after it.  The
 * game's own trace (0x42d510) was compiled out: an empty function.
 *
 * Files loaded whole (cmn\loadfile.c, loadfileadr): a file of the game's
 * (0x4e28d0 opens it, by name, in an archive or not, its size and handle) read
 * into a block allocated for it, the sound's stream topped up first; the
 * load's hook (0x567868), if one is set, may make another block of it.
 * Whether a file is there asks the same open, its complaint at a missing file
 * (0x56440c) off.
 *
 * A .viv archive ("BIGF", big-endian): its header -- 'BIGF', its size, the
 * files' count at 8, the header's size at 0xc -- and after it, from 0x10, each
 * file's offset and size and its name, ended.  openViv reads the header whole
 * into a block (byte-swapping the first, count and size words), findInViv
 * looks a file's name, without its path, up in it.
 *
 * Written as their code is: each push and pop to the guest's stack, each call
 * with the return address's slot, the frame's locals in the guest's memory,
 * the registers as the code leaves them.  The text's switch on the control
 * byte goes by the targets nfs3.exe's table at 0x4e0a48 holds.  Every other
 * function of the game's, and Windows' through its imports, is called by
 * address. */
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

// The trace's: its level, its lock; the monitor's page, the cursor, the
// window's top row, the attribute, the tab's width.
constexpr reg32 kTraceLevel = 0x5644c8, kTraceLock = 0x5644c4;
constexpr reg32 kMonoPage = 0x5644d0, kMonoCursor = 0x5644d4;
constexpr reg32 kMonoTop = 0x5644d8, kMonoAttribute = 0x5644d9, kMonoTab = 0x5644da;
constexpr reg32 kRowBytes = 0xa0, kPageBytes = 0xfa0, kLastRow = 0xf00;
// EA's random numbers' six words (snd::eaRandom draws from them).
constexpr reg32 kRandom = 0x5644e0;
// The loads': whether a missing file is complained of; the last file's size;
// the load's hook; what the load's block size is handed.
constexpr reg32 kComplain = 0x56440c, kLoadedSize = 0x5643f8;
constexpr reg32 kLoadHook = 0x567868, kLoadSomething = 0x567860;
constexpr reg32 kWhere = 0x552190, kWhereFunction = 0x552194, kWhereLine = 0x552198;
constexpr reg32 kLoadFile = 0x549928, kLoadFunction = 0x549938;
// The archive's: fopen's mode "rb", the block's name "".
constexpr reg32 kReadBinary = 0x5376e4, kNoName = 0x537690;
// What is called by address.
constexpr reg32 kEnterCriticalSection = 0x5344b8, kLeaveCriticalSection = 0x534588;
constexpr reg32 kNewLock = 0x4eb2e0, kVsprintf = 0x4df674, kMoveMemory = 0x4ea4f0, kFillZero = 0x4e070c;
constexpr reg32 kOpen = 0x4e28d0, kClose = 0x4e2da0, kRead = 0x4e2de0;
constexpr reg32 kTopUp = 0x4ff7c0, kTopUpEnd = 0x4ff7e0, kLoadBlockSize = 0x4ff820, kLoadFlags = 0x4ff830;
constexpr reg32 kAllocate = 0x4e1620, kFree = 0x4e1890, kLoadWhole = 0x4e0ec0;
constexpr reg32 kFopen = 0x4edfe8, kFclose = 0x4ee100, kFseek = 0x4e9088, kFread = 0x4e9200;
constexpr reg32 kMemset = 0x4e0640, kStrrchr = 0x4ee2f0, kStrncpy = 0x4e0e30, kStricmp = 0x4e9ec0;

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

/* The trace's lock, made the first time it is wanted. */
bool makeLock(win32::WinApplication* app, x86::CPU& cpu)
{
    if (!byAddress(app, cpu, kNewLock))
        return false;
    put(app, kTraceLock, cpu.eax);
    return true;
}

/* The lock's address pushed from `reg` and EnterCriticalSection or
 * LeaveCriticalSection called with it. */
bool lockCall(win32::WinApplication* app, x86::CPU& cpu, reg32& reg, reg32 slot)
{
    reg = at(app, kTraceLock);
    push(app, cpu, reg);
    return byAddress(app, cpu, at(app, slot));
}

}  // namespace

void gameTrace(win32::WinApplication* app, x86::CPU& cpu);
void openViv(win32::WinApplication* app, x86::CPU& cpu);
void closeViv(win32::WinApplication* app, x86::CPU& cpu);
void findInViv(win32::WinApplication* app, x86::CPU& cpu);
void findVivEntry(win32::WinApplication* app, x86::CPU& cpu);
void monoPrintf(win32::WinApplication* app, x86::CPU& cpu);
void monoPrintfAt(win32::WinApplication* app, x86::CPU& cpu);
void monoWrite(win32::WinApplication* app, x86::CPU& cpu);
void monoScroll(win32::WinApplication* app, x86::CPU& cpu);
void monoClear(win32::WinApplication* app, x86::CPU& cpu);
void monoSetTop(win32::WinApplication* app, x86::CPU& cpu);
void monoSetAttribute(win32::WinApplication* app, x86::CPU& cpu);
void monoSetTab(win32::WinApplication* app, x86::CPU& cpu);
void monoPage(win32::WinApplication* app, x86::CPU& cpu);
void monoNoCursor(win32::WinApplication* app, x86::CPU& cpu);
void seedRandom(win32::WinApplication* app, x86::CPU& cpu);
void fileExists(win32::WinApplication* app, x86::CPU& cpu);
void loadFile(win32::WinApplication* app, x86::CPU& cpu);
void loadFileQuietly(win32::WinApplication* app, x86::CPU& cpu);

/* 0x42d510: the game's own trace (a level, a channel, a format and its
 * arguments on the stack), compiled out -- push ebp, mov ebp, esp, pop ebp. */
void gameTrace(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.ebp = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x43b830: the .viv archive named eax opened, its FILE to [edx]: its header's
 * size (big-endian at 0xc) read, a block of it and 0x30 more allocated and
 * cleared, the header read into it whole and its first word, the files'
 * count (8) and the header's size (0xc) byte-swapped.  The block, or 0 --
 * the file closed and [edx] 0 when there is no block. */
void openViv(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.esp -= 4;
    const reg32 size = cpu.ebp - 4;
    const auto leave = [&] {
        cpu.esp = cpu.ebp;
        cpu.ebp = pop(app, cpu);
        cpu.edi = pop(app, cpu);
        cpu.esi = pop(app, cpu);
        cpu.ecx = pop(app, cpu);
        cpu.ebx = pop(app, cpu);
        cpu.esp += 4;
    };
    cpu.edi = cpu.edx;
    cpu.edx = kReadBinary;
    if (!byAddress(app, cpu, kFopen))
        return;
    put(app, cpu.edi, cpu.eax);
    if (cpu.eax == 0)
        return leave();
    cpu.edx = 0xc;
    cpu.ebx = 0;
    if (!byAddress(app, cpu, kFseek))
        return;
    cpu.ebx = 1;
    cpu.edx = 4;
    cpu.eax = size;
    cpu.ecx = at(app, cpu.edi);
    if (!byAddress(app, cpu, kFread))
        return;
    cpu.eax = at(app, size);
    cpu.edx = at(app, size);
    cpu.eax &= 0xff;
    cpu.edx &= 0xff00;
    cpu.eax <<= 0x18;
    cpu.edx <<= 8;
    cpu.edx |= cpu.eax;
    cpu.eax = at(app, size);
    cpu.eax &= 0xff0000;
    cpu.eax >>= 8;
    cpu.edx |= cpu.eax;
    cpu.eax = at(app, size);
    cpu.eax &= 0xff000000;
    cpu.eax >>= 0x18;
    cpu.ebx = 0x10;
    cpu.edx |= cpu.eax;
    cpu.eax = kNoName;
    put(app, size, cpu.edx);
    cpu.edx += 0x30;
    if (!byAddress(app, cpu, kAllocate))
        return;
    cpu.esi = cpu.eax;
    if (cpu.eax == 0)
    {
        cpu.eax = at(app, cpu.edi);
        if (!byAddress(app, cpu, kFclose))
            return;
        cpu.eax = 0;
        put(app, cpu.edi, cpu.esi);
        return leave();
    }
    cpu.ebx = at(app, size);
    cpu.edx = 0;
    cpu.ebx += 0x30;
    if (!byAddress(app, cpu, kMemset))
        return;
    cpu.eax = at(app, cpu.edi);
    cpu.ebx = 0;
    cpu.edx = 0;
    if (!byAddress(app, cpu, kFseek))
        return;
    cpu.edx = at(app, size);
    cpu.ebx = 1;
    cpu.eax = cpu.esi;
    cpu.ecx = at(app, cpu.edi);
    cpu.edx += 0x30;
    if (!byAddress(app, cpu, kFread))
        return;
    // The first word: edx the low bytes, eax the high, into eax.
    cpu.edx = at(app, cpu.esi);
    cpu.eax = at(app, cpu.esi);
    cpu.edx &= 0xff;
    cpu.eax &= 0xff00;
    cpu.edx <<= 0x18;
    cpu.eax <<= 8;
    cpu.edx |= cpu.eax;
    cpu.eax = at(app, cpu.esi);
    cpu.eax &= 0xff0000;
    cpu.eax >>= 8;
    cpu.eax |= cpu.edx;
    cpu.edx = at(app, cpu.esi);
    cpu.edx &= 0xff000000;
    cpu.edx >>= 0x18;
    cpu.eax |= cpu.edx;
    put(app, cpu.esi, cpu.eax);
    // The header's size.
    cpu.edx = at(app, cpu.esi + 0xc);
    cpu.eax = at(app, cpu.esi + 0xc);
    cpu.edx &= 0xff;
    cpu.eax &= 0xff00;
    cpu.edx <<= 0x18;
    cpu.eax <<= 8;
    cpu.edx |= cpu.eax;
    cpu.eax = at(app, cpu.esi + 0xc);
    cpu.eax &= 0xff0000;
    cpu.eax >>= 8;
    cpu.edx |= cpu.eax;
    cpu.eax = at(app, cpu.esi + 0xc);
    cpu.eax &= 0xff000000;
    cpu.eax >>= 0x18;
    cpu.edx |= cpu.eax;
    put(app, cpu.esi + 0xc, cpu.edx);
    // The files' count.
    cpu.eax = at(app, cpu.esi + 8);
    cpu.edx = at(app, cpu.esi + 8);
    cpu.eax &= 0xff;
    cpu.edx &= 0xff00;
    cpu.eax <<= 0x18;
    cpu.edx <<= 8;
    cpu.edx |= cpu.eax;
    cpu.eax = at(app, cpu.esi + 8);
    cpu.eax &= 0xff0000;
    cpu.eax >>= 8;
    cpu.edx |= cpu.eax;
    cpu.eax = at(app, cpu.esi + 8);
    cpu.eax &= 0xff000000;
    cpu.eax >>= 0x18;
    cpu.edx |= cpu.eax;
    cpu.eax = cpu.esi;
    put(app, cpu.esi + 8, cpu.edx);
    leave();
}

/* 0x43b9b0: the archive's block eax freed and its FILE at [edx] closed, [edx]
 * 0. */
void closeViv(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    if (!byAddress(app, cpu, kFree))
        return;
    cpu.eax = at(app, cpu.edx);
    if (!byAddress(app, cpu, kFclose))
        return;
    put(app, cpu.edx, 0);
    cpu.ebp = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x43b9d0: the file named edx -- its path after the last backslash, 0x1d
 * bytes of it -- looked up in the archive's header eax (findVivEntry): its
 * offset to [ebx], its size to [ecx]. */
void findInViv(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.esp -= 0x24;
    cpu.edi = cpu.eax;
    cpu.esi = cpu.edx;
    put(app, cpu.ebp - 4, cpu.ebx);
    cpu.edx = '\\';
    cpu.eax = cpu.esi;
    if (!byAddress(app, cpu, kStrrchr))
        return;
    cpu.edx = cpu.eax != 0 ? cpu.eax + 1 : cpu.esi;
    cpu.ebx = 0x1d;
    cpu.eax = cpu.ebp - 0x24;
    if (!byAddress(app, cpu, kStrncpy))
        return;
    cpu.ebx = at(app, cpu.ebp - 4);
    cpu.edx = cpu.ebp - 0x24;
    cpu.eax = cpu.edi;
    if (!direct(app, cpu, findVivEntry))
        return;
    cpu.esp = cpu.ebp;
    cpu.ebp = pop(app, cpu);
    cpu.edi = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x4679f0: the file named edx (case aside, _stricmp) looked for among the
 * [eax + 8] entries of the archive's header eax, from 0x10 on -- each its
 * offset and size, big-endian, and its name, ended.  Found, its offset
 * byte-swapped to [ebx] and its size to [ecx]; else both 0.  ecx left the
 * entry's, edx the size's or the last _stricmp's. */
void findVivEntry(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.esp -= 0xc;
    const reg32 header = cpu.ebp - 4, name = cpu.ebp - 8, wanted = cpu.ebp - 0xc;
    put(app, header, cpu.eax);
    put(app, wanted, cpu.edx);
    cpu.esi = cpu.ecx;
    cpu.ecx = cpu.eax + 0x10;
    cpu.edi = 0;
    for (;;)
    {
        cpu.eax = at(app, header);
        if (cpu.edi >= at(app, cpu.eax + 8))
        {
            put(app, cpu.ebx, 0);
            put(app, cpu.esi, 0);
            break;
        }
        cpu.eax = cpu.ecx + 8;
        put(app, name, cpu.eax);
        cpu.edx = cpu.eax;
        cpu.eax = at(app, wanted);
        if (!byAddress(app, cpu, kStricmp))
            return;
        if (cpu.eax != 0)
        {
            cpu.ecx = at(app, name);
            while (byte(app, cpu.ecx) != 0)
                ++cpu.ecx;
            ++cpu.edi;
            ++cpu.ecx;
            continue;
        }
        // The offset and the size, each: edx the low bytes, eax the high.
        for (const reg32 offset : {0u, 4u})
        {
            const reg32 from = cpu.ecx + offset, to = offset == 0 ? cpu.ebx : cpu.esi;
            cpu.edx = at(app, from);
            cpu.eax = at(app, from);
            cpu.edx &= 0xff;
            cpu.eax &= 0xff00;
            cpu.edx <<= 0x18;
            cpu.eax <<= 8;
            cpu.edx |= cpu.eax;
            cpu.eax = at(app, from);
            cpu.eax &= 0xff0000;
            cpu.eax >>= 8;
            cpu.edx |= cpu.eax;
            cpu.eax = at(app, from);
            cpu.eax &= 0xff000000;
            cpu.eax >>= 0x18;
            cpu.edx |= cpu.eax;
            put(app, to, cpu.edx);
        }
        break;
    }
    cpu.esp = cpu.ebp;
    cpu.ebp = pop(app, cpu);
    cpu.edi = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x4e08f0: EA's trace, printf's way (the format and its arguments on the
 * stack), written to the monochrome monitor (monoWrite) under the trace's
 * lock -- formatted into 0x100 bytes of the frame (vsprintf) -- while the
 * trace's level is 2 or more. */
void monoPrintf(win32::WinApplication* app, x86::CPU& cpu)
{
    cpu.esp -= 0x104;
    if (sreg32(at(app, kTraceLevel)) >= 2)
    {
        if (at(app, kTraceLock) == 0 && !makeLock(app, cpu))
            return;
        push(app, cpu, cpu.edi);
        push(app, cpu, cpu.esi);
        push(app, cpu, cpu.edx);
        push(app, cpu, cpu.ecx);
        push(app, cpu, cpu.ebx);
        if (!lockCall(app, cpu, cpu.ebx, kEnterCriticalSection))
            return;
        cpu.eax = cpu.esp + 0x120;
        cpu.ebx = cpu.esp + 0x114;
        cpu.edx = at(app, cpu.esp + 0x11c);
        put(app, cpu.esp + 0x114, cpu.eax);
        cpu.eax = cpu.esp + 0x14;
        cpu.esi = 0;
        if (!byAddress(app, cpu, kVsprintf))
            return;
        cpu.eax = cpu.esp + 0x14;
        put(app, cpu.esp + 0x114, cpu.esi);
        if (!direct(app, cpu, monoWrite))
            return;
        if (!lockCall(app, cpu, cpu.edi, kLeaveCriticalSection))
            return;
        cpu.ebx = pop(app, cpu);
        cpu.ecx = pop(app, cpu);
        cpu.edx = pop(app, cpu);
        cpu.esi = pop(app, cpu);
        cpu.edi = pop(app, cpu);
    }
    cpu.esp += 0x104;
    cpu.esp += 4;
}

/* 0x4e0980: monoPrintf at column [esp+4] and row [esp+8] (the cursor moved
 * there if they are on the page, 80 by 25), the format after them. */
void monoPrintfAt(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.ebp);
    cpu.esp -= 0x104;
    cpu.esi = at(app, cpu.esp + 0x114);
    cpu.ebx = at(app, cpu.esp + 0x118);
    if (sreg32(at(app, kTraceLevel)) >= 2)
    {
        if (at(app, kTraceLock) == 0 && !makeLock(app, cpu))
            return;
        push(app, cpu, cpu.edi);
        push(app, cpu, cpu.edx);
        push(app, cpu, cpu.ecx);
        if (!lockCall(app, cpu, cpu.edi, kEnterCriticalSection))
            return;
        if (sreg32(cpu.esi) >= 0 && sreg32(cpu.esi) < 0x50 && sreg32(cpu.ebx) >= 0 && sreg32(cpu.ebx) < 0x19)
        {
            cpu.eax = cpu.ebx * 4;
            cpu.eax += cpu.ebx;
            cpu.eax <<= 4;
            cpu.eax += cpu.esi;
            cpu.eax += cpu.eax;
            put(app, kMonoCursor, cpu.eax);
        }
        cpu.eax = cpu.esp + 0x12c;
        cpu.ebx = cpu.esp + 0x10c;
        cpu.edx = at(app, cpu.esp + 0x128);
        put(app, cpu.esp + 0x10c, cpu.eax);
        cpu.eax = cpu.esp + 0xc;
        cpu.ebp = 0;
        if (!byAddress(app, cpu, kVsprintf))
            return;
        cpu.eax = cpu.esp + 0xc;
        put(app, cpu.esp + 0x10c, cpu.ebp);
        if (!direct(app, cpu, monoWrite))
            return;
        if (!lockCall(app, cpu, cpu.eax, kLeaveCriticalSection))
            return;
        cpu.ecx = pop(app, cpu);
        cpu.edx = pop(app, cpu);
        cpu.edi = pop(app, cpu);
    }
    cpu.esp += 0x104;
    cpu.ebp = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x4e0a60: the text at eax written at the monitor's cursor, while the
 * trace's level is 2 or more: each byte from 0x20 a cell in the attribute
 * (the window scrolled first if the cursor is past the page); 8 a cell back,
 * 9 on to the next tab, 0xa the next row's start (scrolled), 0xb the window's
 * top, 0xc the page cleared and the window's top; 0x0e the next byte the
 * attribute.  eax left as the cells' last made it. */
void monoWrite(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.esp -= 4;
    cpu.esi = at(app, kMonoCursor);
    cpu.edx = cpu.eax;
    const auto leave = [&] {
        cpu.esi = at(app, kMonoCursor);
        cpu.esp += 4;
        cpu.ebp = pop(app, cpu);
        cpu.edi = pop(app, cpu);
        cpu.esi = pop(app, cpu);
        cpu.edx = pop(app, cpu);
        cpu.ecx = pop(app, cpu);
        cpu.ebx = pop(app, cpu);
        cpu.esp += 4;
    };
    if (sreg32(at(app, kTraceLevel)) < 2)
        return leave();
    // repne scasb for the ending: ecx its length.
    cpu.edi = cpu.eax;
    cpu.ecx = 0;
    --cpu.ecx;
    cpu.eax = 0;
    do
    {
        --cpu.ecx;
    } while (byte(app, cpu.edi++) != cpu.al && cpu.ecx != 0);
    cpu.ecx = ~cpu.ecx;
    --cpu.ecx;
    cpu.bl = 0;
    put(app, cpu.esp, cpu.ecx);
    cpu.edi = 0;
    if (sreg32(cpu.ecx) <= 0)
        return leave();
    cpu.ecx = cpu.edx;
    for (;;)
    {
        if (cpu.bl == 0x0e)
        {
            cpu.eax = 0;
            cpu.al = byte(app, cpu.ecx);
            cpu.bl = 0;
            if (!direct(app, cpu, monoSetAttribute))
                return;
        }
        else
        {
            cpu.bl = byte(app, cpu.ecx);
            cpu.esi = at(app, kMonoCursor);
            if (cpu.bl >= 0x20)
            {
                if (!direct(app, cpu, monoScroll))
                    return;
                cpu.esi = at(app, kMonoCursor);
                cpu.ah = 0;
                cpu.dh = 0;
                cpu.al = byte(app, kMonoAttribute);
                cpu.dl = cpu.bl;
                cpu.esi += 2;
                cpu.eax <<= 8;
                cpu.eax += cpu.edx;
                cpu.edx = at(app, kMonoPage);
                put(app, kMonoCursor, cpu.esi);
                app->getMemory<x86::reg16>(cpu.edx + cpu.esi - 2) = x86::reg16(cpu.eax);
            }
            else
            {
                cpu.al = cpu.bl;
                cpu.al -= 8;
                if (cpu.al <= 4)
                {
                    cpu.eax &= 0xff;
                    // The table at 0x4e0a48: 0x4e0b10, 0x4e0b30, 0x4e0b86, 0x4e0bc0, 0x4e0be5.
                    switch (cpu.eax)
                    {
                    case 0:  // backspace
                        if (sreg32(cpu.esi) >= 2)
                        {
                            cpu.esi -= 2;
                            put(app, kMonoCursor, cpu.esi);
                        }
                        break;
                    case 1:  // tab
                    {
                        if (byte(app, kMonoTab) <= 1)
                            break;
                        cpu.ebp = kRowBytes;
                        cpu.edx = cpu.esi;
                        cpu.eax = cpu.esi;
                        cpu.edx = reg32(sreg32(cpu.edx) >> 31);
                        cpu.eax = reg32(sreg32(cpu.esi) / sreg32(cpu.ebp));
                        cpu.edx = reg32(sreg32(cpu.esi) % sreg32(cpu.ebp));
                        cpu.ebp *= cpu.eax;
                        cpu.edx = cpu.esi;
                        cpu.edx -= cpu.ebp;
                        cpu.eax = cpu.edx;
                        cpu.edx = reg32(sreg32(cpu.edx) >> 31);
                        cpu.eax -= cpu.edx;
                        cpu.eax = reg32(sreg32(cpu.eax) >> 1);
                        cpu.edx = cpu.eax;
                        cpu.esi = byte(app, kMonoTab);
                        cpu.edx = reg32(sreg32(cpu.edx) >> 31);
                        const sreg32 column = sreg32(cpu.eax);
                        cpu.eax = reg32(column / sreg32(cpu.esi));
                        cpu.edx = reg32(column % sreg32(cpu.esi));
                        ++cpu.eax;
                        cpu.eax *= cpu.esi;
                        cpu.eax += cpu.eax;
                        cpu.esi = cpu.eax + cpu.ebp;
                        put(app, kMonoCursor, cpu.esi);
                        break;
                    }
                    case 2:  // newline
                    {
                        cpu.eax = cpu.esi;
                        cpu.edx = cpu.esi;
                        cpu.esi = kRowBytes;
                        cpu.edx = reg32(sreg32(cpu.edx) >> 31);
                        const sreg32 cursor = sreg32(cpu.eax);
                        cpu.eax = reg32(cursor / sreg32(cpu.esi));
                        cpu.edx = reg32(cursor % sreg32(cpu.esi));
                        cpu.esi = cpu.eax + 1;
                        cpu.esi *= kRowBytes;
                        put(app, kMonoCursor, cpu.esi);
                        if (!direct(app, cpu, monoScroll))
                            return;
                        cpu.esi = at(app, kMonoCursor);
                        break;
                    }
                    case 3:  // the window's top
                        cpu.esi = byte(app, kMonoTop);
                        cpu.esi *= kRowBytes;
                        put(app, kMonoCursor, cpu.esi);
                        break;
                    case 4:  // the page cleared
                        if (!direct(app, cpu, monoClear))
                            return;
                        cpu.esi = byte(app, kMonoTop);
                        cpu.esi *= kRowBytes;
                        put(app, kMonoCursor, cpu.esi);
                        break;
                    }
                }
            }
        }
        cpu.ebp = at(app, cpu.esp);
        ++cpu.edi;
        ++cpu.ecx;
        if (sreg32(cpu.edi) >= sreg32(cpu.ebp))
            return leave();
    }
}

/* 0x4e0c10: the cursor past the page: the window's rows below its top moved
 * up one (0x4ea4f0), the last cleared (0x4e070c), the cursor at its start. */
void monoScroll(win32::WinApplication* app, x86::CPU& cpu)
{
    if (sreg32(at(app, kMonoCursor)) < sreg32(kPageBytes))
    {
        cpu.esp += 4;
        return;
    }
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.ebx);
    cpu.edx = 0;
    cpu.ecx = 0x19;
    cpu.dl = byte(app, kMonoTop);
    cpu.ecx -= cpu.edx;
    cpu.eax = cpu.edx * 4;
    --cpu.ecx;
    cpu.eax += cpu.edx;
    cpu.ebx = cpu.ecx * 4;
    cpu.eax <<= 5;
    cpu.ebx += cpu.ecx;
    cpu.ecx = at(app, kMonoPage);
    ++cpu.edx;
    cpu.ecx += cpu.eax;
    cpu.eax = cpu.edx * 4;
    cpu.esi = at(app, kMonoPage);
    cpu.eax += cpu.edx;
    cpu.ebx <<= 5;
    cpu.eax <<= 5;
    cpu.edx = cpu.ecx;
    cpu.eax += cpu.esi;
    if (!byAddress(app, cpu, kMoveMemory))
        return;
    cpu.eax = at(app, kMonoPage);
    cpu.edx = kRowBytes;
    cpu.eax += kLastRow;
    cpu.edi = kLastRow;
    if (!byAddress(app, cpu, kFillZero))
        return;
    put(app, kMonoCursor, cpu.edi);
    cpu.ebx = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.edi = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x4e0ca0: the monitor's page cleared, a dword at a time, under the trace's
 * lock, while the trace's level is 2 or more.  The cursor stays. */
void monoClear(win32::WinApplication* app, x86::CPU& cpu)
{
    if (sreg32(at(app, kTraceLevel)) < 2)
    {
        cpu.esp += 4;
        return;
    }
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.ecx);
    if (at(app, kTraceLock) == 0 && !makeLock(app, cpu))
        return;
    push(app, cpu, cpu.ebx);
    if (!lockCall(app, cpu, cpu.ebx, kEnterCriticalSection))
        return;
    cpu.eax = 0;
    cpu.ebx = pop(app, cpu);
    do
    {
        cpu.edx = at(app, kMonoPage);
        put(app, cpu.edx + cpu.eax, 0);
        cpu.eax += 4;
    } while (sreg32(cpu.eax) < sreg32(kPageBytes));
    if (!lockCall(app, cpu, cpu.esi, kLeaveCriticalSection))
        return;
    cpu.ecx = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x4e0d00: the scrolling window's top row eax (0 to 24, else as it was),
 * under the trace's lock.  No caller in the game. */
void monoSetTop(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    cpu.ebx = cpu.eax;
    if (at(app, kTraceLock) == 0 && !makeLock(app, cpu))
        return;
    if (!lockCall(app, cpu, cpu.ecx, kEnterCriticalSection))
        return;
    if (sreg32(cpu.ebx) >= 0 && sreg32(cpu.ebx) <= 0x18)
        putByte(app, kMonoTop, cpu.bl);
    if (!lockCall(app, cpu, cpu.ebx, kLeaveCriticalSection))
        return;
    cpu.edx = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x4e0d50: the attribute the monitor's text is written in, al. */
void monoSetAttribute(win32::WinApplication* app, x86::CPU& cpu)
{
    putByte(app, kMonoAttribute, cpu.al);
    cpu.esp += 4;
}

/* 0x4e0d60: the tab's width, al, if eax is 1 or more.  No caller. */
void monoSetTab(win32::WinApplication* app, x86::CPU& cpu)
{
    if (sreg32(cpu.eax) >= 1)
        putByte(app, kMonoTab, cpu.al);
    cpu.esp += 4;
}

/* 0x4e0d70: the monitor's page eax: 0xb0000 + eax * 0x8000.  No caller. */
void monoPage(win32::WinApplication* app, x86::CPU& cpu)
{
    cpu.eax <<= 0xf;
    cpu.eax += 0xb0000;
    put(app, kMonoPage, cpu.eax);
    cpu.esp += 4;
}

/* 0x4e0d80: the bytes at eax and edx 0 -- a cursor's column and row asked of
 * a monitor that has none, it seems.  No caller: dead. */
void monoNoCursor(win32::WinApplication* app, x86::CPU& cpu)
{
    putByte(app, cpu.eax, 0);
    putByte(app, cpu.edx, 0);
    cpu.esp += 4;
}

/* 0x4e0dee: EA's random numbers (snd::eaRandom, 0x4e0d88, just before it)
 * seeded from eax: their six words at 0x5644e0, each the one before plus a
 * constant.  Not the trace's: it only follows it in the library. */
void seedRandom(win32::WinApplication* app, x86::CPU& cpu)
{
    static const reg32 steps[] = {0xf22d0e56, 0x96041893, 0x3df3b646, 0x40dde76d, 0x97327ae1, 0xd1a9fbe7};
    for (reg32 i = 0; i < 6; ++i)
    {
        cpu.eax += steps[i];
        put(app, kRandom + 4 * i, cpu.eax);
    }
    cpu.esp += 4;
}

/* 0x4e0e60: whether the file named eax is there: opened (0x4e28d0) with the
 * complaint at a missing one off, closed again; 1, or 0. */
void fileExists(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.esi);
    cpu.esp -= 0xc;
    cpu.ecx = cpu.esp + 8;
    cpu.ebx = cpu.esp + 4;
    cpu.edx = 0;
    cpu.esi = at(app, kComplain);
    put(app, kComplain, cpu.edx);
    cpu.edx = cpu.esp;
    if (!byAddress(app, cpu, kOpen))
        return;
    cpu.ecx = at(app, cpu.esp);
    if (cpu.ecx != 0)
    {
        cpu.eax = cpu.ecx;
        cpu.ebx = 1;
        if (!byAddress(app, cpu, kClose))
            return;
        put(app, cpu.esp, cpu.ebx);
    }
    cpu.eax = at(app, cpu.esp);
    put(app, kComplain, cpu.esi);
    cpu.esp += 0xc;
    cpu.esi = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x4e0ec0 (loadfileadr, cmn\loadfile.c): the file named eax loaded whole
 * into a block allocated with flags edx -- the sound's stream topped up
 * before (0x4ff7c0), the more so the bigger the file; its size kept at
 * 0x5643f8.  The load's hook (0x567868), if set, is handed the block, the
 * name and the flags, and what it gives back is the block (none: the block
 * freed).  The block, or 0. */
void loadFile(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.esp -= 0xc;
    const auto leave = [&] {
        cpu.esp += 0xc;
        cpu.ebp = pop(app, cpu);
        cpu.edi = pop(app, cpu);
        cpu.esi = pop(app, cpu);
        cpu.ecx = pop(app, cpu);
        cpu.ebx = pop(app, cpu);
        cpu.esp += 4;
    };
    cpu.edi = cpu.eax;
    cpu.ebp = cpu.edx;
    cpu.eax = 0x1f4;
    cpu.ecx = cpu.esp;
    cpu.ebx = cpu.esp + 4;
    cpu.edx = cpu.esp + 8;
    if (!byAddress(app, cpu, kTopUp))
        return;
    cpu.eax = cpu.edi;
    cpu.esi = 0;
    if (!byAddress(app, cpu, kOpen))
        return;
    if (cpu.eax == 0 || (cpu.edx = at(app, cpu.esp)) == 0)
    {
        // Not there, or empty: closed if it was opened.
        cpu.ecx = at(app, cpu.esp + 8);
        if (cpu.ecx != 0)
        {
            cpu.eax = cpu.ecx;
            if (!byAddress(app, cpu, kClose))
                return;
        }
        cpu.eax = cpu.esi;
        return leave();
    }
    cpu.ecx = 0x10e;
    cpu.eax = cpu.edx;
    cpu.edx = reg32(sreg32(cpu.edx) >> 31);
    const sreg32 size = sreg32(cpu.eax);
    cpu.eax = reg32(size / 0x10e);
    cpu.edx = reg32(size % 0x10e);
    cpu.ecx = cpu.eax;
    cpu.eax = at(app, cpu.esp + 8);
    if (!byAddress(app, cpu, kLoadFlags))
        return;
    cpu.esi = at(app, kLoadSomething);
    cpu.edx = cpu.eax;
    cpu.eax = cpu.esi;
    cpu.ebx = kLoadFile;
    if (!byAddress(app, cpu, kLoadBlockSize))
        return;
    cpu.eax += cpu.ecx;
    cpu.esi = kLoadFunction;
    if (!byAddress(app, cpu, kTopUp))
        return;
    cpu.eax = 0x4b;
    cpu.edx = at(app, cpu.esp);
    put(app, kWhere, cpu.ebx);
    put(app, kWhereLine, cpu.eax);
    cpu.ebx = cpu.ebp;
    cpu.eax = cpu.edi;
    put(app, kWhereFunction, cpu.esi);
    if (!byAddress(app, cpu, kAllocate))
        return;
    cpu.esi = cpu.eax;
    if (cpu.eax != 0)
    {
        cpu.ebx = at(app, cpu.esp);
        cpu.edx = cpu.eax;
        cpu.eax = at(app, cpu.esp + 8);
        if (!byAddress(app, cpu, kRead))
            return;
        cpu.eax = at(app, cpu.esp);
        put(app, kLoadedSize, cpu.eax);
    }
    cpu.eax = at(app, cpu.esp + 8);
    if (!byAddress(app, cpu, kClose) || !byAddress(app, cpu, kTopUpEnd))
        return;
    if (at(app, kLoadHook) != 0 && cpu.esi != 0)
    {
        cpu.ebx = cpu.ebp;
        cpu.edx = cpu.edi;
        cpu.eax = cpu.esi;
        if (!byAddress(app, cpu, at(app, kLoadHook)))
            return;
        cpu.edx = cpu.eax;
        if (cpu.eax == 0)
        {
            cpu.eax = cpu.esi;
            if (!byAddress(app, cpu, kFree))
                return;
        }
        cpu.esi = cpu.edx;
    }
    cpu.eax = cpu.esi;
    leave();
}

/* 0x4e0fe0: loadFile (by address) with the complaint at a missing file off. */
void loadFileQuietly(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    cpu.ebx = 0;
    cpu.ecx = at(app, kComplain);
    put(app, kComplain, cpu.ebx);
    if (!byAddress(app, cpu, kLoadWhole))
        return;
    put(app, kComplain, cpu.ecx);
    cpu.ecx = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4;
}

}  // namespace ea
}  // namespace nfs3hp
